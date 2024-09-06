#include "app_ota_box.h"
#if PLF_BT_OTA
#include "dbg.h"
#include "co_main.h"
#include "app_bt_queue.h"
#include "flash_api_btdm.h"
#include "aic_ota.h"
#if PLF_PMIC
#include "pmic_api.h"
#endif

#define OTA_PRINT(fmt, ...)       //dbg(fmt, ##__VA_ARGS__)
enum APP_OTA_ACCESS app_ota_access;

#if APP_SUPPORT_OTA_BOX
#include "ff.h"
#include "system.h"


#define SDCARD_DRIVE_ID         "SD:"
#define APP_OTA_SEND_LEN        512
#define APP_OTA_SEND_NUM        1
#define APP_OTA_READ_LEN        APP_OTA_SEND_LEN*APP_OTA_SEND_NUM
#define AIC_OTA_ADDR_LIST_NUM   10
#define AIC_OTA_RESEND_TIME     10

static BT_ADDR aic_ota_addr_list[AIC_OTA_ADDR_LIST_NUM];
static uint8_t aic_ota_addr_num = 0;
const BT_ADDR aic_bt_addr = {{00,00,00,0x88,0x88,0x33}};
static uint8_t send_buff[APP_OTA_READ_LEN] = {0,};
static uint32_t send_len = 0;
static uint32_t total_send_len = 0;
char *fsid    = SDCARD_DRIVE_ID "/";
char *otafile = SDCARD_DRIVE_ID "/otadir/ota.bin";
FATFS fs;
FIL fh;
FILINFO fi;
static co_timer *app_ota_resend_timer = NULL;

bool app_ota_check_aic_addr(BT_ADDR *ota_addr)
{
    if(ota_addr->addr[5] == aic_bt_addr.addr[5]
    && ota_addr->addr[4] == aic_bt_addr.addr[4]
    && ota_addr->addr[3] == aic_bt_addr.addr[3])
       return TRUE;
    else
       return FALSE;
}

void app_ota_add_addr_list(BT_ADDR *ota_addr)
{
    for(uint8_t i=0;i<AIC_OTA_ADDR_LIST_NUM;i++){
        if(memcmp(ota_addr->addr,aic_bt_addr.addr,6) == 0){
            return;
        }
    }
    memcpy(aic_ota_addr_list[aic_ota_addr_num++].addr,ota_addr->addr,6);
}

void app_ota_clean_addr_list(void)
{
    memset((uint8_t *)aic_ota_addr_list,0,(AIC_OTA_ADDR_LIST_NUM*6));
}

void app_ota_show_addr_list(void)
{
    if(aic_ota_addr_num){
        TRACE("APP: ota addr list :\n");
        for(uint8_t i=0;i<aic_ota_addr_num;i++){
            BT_ADDR *oaddr = &aic_ota_addr_list[i];
            TRACE("LIST ID %d,addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",i,oaddr->addr[5],\
            oaddr->addr[4],oaddr->addr[3],oaddr->addr[2],oaddr->addr[1],oaddr->addr[0]);
        }
    }
}


void app_ota_connect_device(BT_ADDR * bdaddr)
{
    TRACE("APP:test connect addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",bdaddr->addr[0],bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
    aic_adp_test_connect(bdaddr);
}

void app_ota_connect_by_list_id(uint8_t id)
{
    app_ota_connect_device(&aic_ota_addr_list[id]);
}

void app_ota_disconnect_device(void)
{
    aic_adp_test_disconnect();
}

int app_ota_update_bin_init(void)
{
    int err;

    do {
        uint8_t mode = FA_READ;

        OTA_PRINT("mount: %s\r\n",fsid);
        err = f_mount(&fs, fsid, 0);
        if (err) {
            OTA_PRINT("Fail to mount, err=%d\r\n", err);
            break;
        }

        OTA_PRINT("stat: %s\r\n",otafile);
        err = f_stat(otafile, &fi);
        if (err == FR_NO_FILE) {
            OTA_PRINT("Not Exist\r\n");
            break;
        } else if (err) {
            OTA_PRINT("Fail to stat, err=%d\r\n", err);
            break;
        }
        OTA_PRINT("stat: file size %d, file name %s, date %d,time %d\r\n",fi.fsize,fi.fname,fi.fdate,fi.ftime);
        OTA_PRINT("open: %s\r\n",otafile);
        err = f_open(&fh, otafile, mode);
        if (err) {
            OTA_PRINT("Fail to open, err=%d\r\n", err);
            break;
        }

        OTA_PRINT("lseek to 0, cur=%d\r\n",f_tell(&fh));
        err = f_lseek(&fh, 0);
        if (err) {
            OTA_PRINT("Fail to lseek, err=%d\r\n", err);
            break;
        }
        OTA_PRINT("cur=%d\r\n",f_tell(&fh));

    } while (0);

    return err;
}

int app_ota_update_bin_end(void)
{
    int err;

    do {
        OTA_PRINT("close\r\n");
        err = f_close(&fh);
        if (err) {
            OTA_PRINT("Fail to open, err=%d\r\n", err);
            break;
        }

        OTA_PRINT("unmount: %s\r\n",fsid);
        err = f_mount(NULL, fsid, 0);
        if (err) {
            OTA_PRINT("Fail to unmount, err=%d\r\n", err);
            break;
        }
    } while (0);
    return err;
}

uint32_t app_ota_update_bin_get_size(void)
{
    return fi.fsize;
}

uint32_t app_ota_update_bin_read(char * rd_buff)
{
    int err;
    uint32_t num = 0;

    OTA_PRINT("read\r\n");
    err = f_read(&fh, rd_buff, APP_OTA_READ_LEN, &num);
    if (err) {
        OTA_PRINT("Fail to read, err=%d, num=%d\r\n", err, num);
    }
    OTA_PRINT("cur=%d,num=%d\r\n",f_tell(&fh),num);
    #if 0
    OTA_PRINT("Read text from file: %s\r\n num %d\r\n", otafile,num);
    for(int i = 0; i <num;i++){
        OTA_PRINT("%x ",rd_buff[i]);
    }
    OTA_PRINT("\r\n");
    #endif
    return num;
}

static void app_ota_bin_send_timer(void *cb_param)
{
    uint32_t num = (uint32_t)cb_param;
    app_bt_ota_send_data(num);
}

void app_ota_resend_update_bin(uint32_t num)
{
    uint8_t ret = 0;
    TRACE("ota_send_timer len = %x\n",num);
    app_ota_resend_timer = NULL;

    ret = app_ota_send_data(send_buff,num,OTA_DATA_HEADER);
    TRACE("APP:ret t= %x\n",ret);
    if(ret == BTDEF_PENDING){
        //send ok
    }else if(ret == BTDEF_IS_USEING){
        //buffer is full,delay some time then send it.
        if(app_ota_resend_timer == NULL){
            co_timer_start(&app_ota_resend_timer,AIC_OTA_RESEND_TIME,(void *)num,app_ota_bin_send_timer,0);
        }
    }else{
        //error occured
    }
}

#endif

void app_ota_set_access(enum APP_OTA_ACCESS access)
{
    app_ota_access = access;
}

enum APP_OTA_ACCESS app_ota_get_access(void)
{
    return app_ota_access;
}

uint8_t app_ota_send_data(uint8_t *data, uint16_t len, uint8_t header)
{
    return aic_adp_test_send_data(data,len,header);
}

void app_ota_receive_data(uint8_t *rxbuf, uint16_t len)
{
    static uint32_t total_len = 0;
    static uint32_t received_len = 0;

    OTA_PRINT("APP:OTA in len = %d,header = 0x%x\n",len,rxbuf[0]);
    //OTA_PRINT("%x,%x,%x,%x,%x\n",rxbuf[1],rxbuf[2],rxbuf[3],rxbuf[4],rxbuf[5]);
    switch(app_ota_get_access())
    {
        case OTA_BY_SPP:
            {
                received_len +=len;
                ota_write((const uint8_t *)rxbuf, len);
                if(received_len == total_len){
                    TRACE("APP: OTA BIN received success\n");
                    received_len = 0;
                    total_len = 0;
                    ota_end();
                    pmic_chip_reboot(0xF);
                }
            }
            break;
        case OTA_BY_VENDOR:
            {
                if(rxbuf[0] == OTA_INFO_HEADER){
                    uint32_t ota_addr;
                    total_len = (uint32_t)(rxbuf[1]) | ((uint32_t)(rxbuf[2])<<8) | ((uint32_t)(rxbuf[3])<<16) | ((uint32_t)(rxbuf[4])<<24);
                    TRACE("APP: OTA BIN total len = %d\n",total_len);
                    #ifndef CFG_LZMA_APP
                    ota_addr = OTA_ADDR + OTA_INFO_SIZE;
                    #else
                    ota_addr = OTA_ADDR;
                    #endif
                    ota_start(ota_addr, total_len);
                }else if(rxbuf[0] == OTA_DATA_HEADER){
                    received_len +=(len-1);
                    ota_write((const uint8_t *)&rxbuf[1], (len-1));
                    if(received_len == total_len){
                        TRACE("APP: OTA BIN received success\n");
                        received_len = 0;
                        total_len = 0;
                        ota_end();
                        pmic_chip_reboot(0xF);
                    }
                }else{
                    OTA_PRINT("APP:OTA error\n");
                }
            }
            break;
        case OTA_BY_BLE:
            break;
        default:
            {
                if(rxbuf[0] == OTA_INFO_HEADER){
                    uint32_t ota_addr;
                    total_len = (uint32_t)(rxbuf[1]) | ((uint32_t)(rxbuf[2])<<8) | ((uint32_t)(rxbuf[3])<<16) | ((uint32_t)(rxbuf[4])<<24);
                    TRACE("APP: OTA BIN total len = %d\n",total_len);
                    #ifndef CFG_LZMA_APP
                    ota_addr = OTA_ADDR + OTA_INFO_SIZE;
                    #else
                    ota_addr = OTA_ADDR;
                    #endif
                    ota_start(ota_addr, total_len);
                    app_ota_set_access(OTA_BY_SPP);
                }
            }
            break;
    }
}

void app_ota_msg_handle(AIC_EVENT *Event)
{
    AIC_ADP_TEST_EVENT *aic_ota_msg = (AIC_ADP_TEST_EVENT *)Event->Param;

    switch(Event->EventId){
        case AIC_ADP_TEST_CONNECTED_CNF:
            TRACE("APP:ota_connect_cnf reason = %d\n",aic_ota_msg->testparam);
            app_ota_set_access(OTA_BY_VENDOR);
            break;
        case AIC_ADP_TEST_DISCONNECTED:
            TRACE("APP:ota_disconnect reason = %d\n",aic_ota_msg->testparam);
            app_ota_set_access(OTA_BY_VENDOR);
            break;
#if APP_SUPPORT_OTA_BOX
        case AIC_ADP_TEST_INQUIRY_RESULT:
            if(app_ota_check_aic_addr(&aic_ota_msg->bdaddr)){
                app_ota_add_addr_list(&aic_ota_msg->bdaddr);
            }
            break;
        case AIC_ADP_TEST_INQUIRY_COMPLETE:
            app_ota_show_addr_list();
            break;
        case AIC_ADP_TEST_INQUIRY_CANCELED:
            app_ota_show_addr_list();
            break;
#endif
        case AIC_ADP_TEST_L2CAP_CONNECTD:
            TRACE("APP:ota l2cap connect\n");
#if APP_SUPPORT_OTA_BOX
            uint8_t ret = 0;
            uint32_t file_size = 0;

            file_size = app_ota_update_bin_get_size();
            TRACE("APP:OTA bin size %d\n",file_size);
            memset(send_buff,0,APP_OTA_READ_LEN);
            send_len = 0;
            send_buff[0] = (uint8_t)((0x000000ff&file_size));
            send_buff[1] = (uint8_t)((0x0000ff00&file_size)>>8);
            send_buff[2] = (uint8_t)((0x00ff0000&file_size)>>16);
            send_buff[3] = (uint8_t)((0xff000000&file_size)>>24);
            ret = app_ota_send_data(send_buff,4,OTA_INFO_HEADER);
            TRACE("APP:ret = %x\n",ret);
#else

#endif
            break;
        case AIC_ADP_TEST_L2CAP_DISCONNECTD:
            TRACE("APP:ota l2cap disconnect reason = 0x%x\n",aic_ota_msg->testparam);
#if APP_SUPPORT_OTA_BOX

#else

#endif
            break;
        case AIC_ADP_TEST_L2CAP_DATA_SENT:
            {
                TestTxDone *tx_done = (TestTxDone *)aic_ota_msg->testparam;
                OTA_PRINT("APP:OTA out len = %d,data addr = 0x%x\n",tx_done->len,tx_done->txbuf);
                //OTA_PRINT("%x,%x,%x,%x,%x\n",tx_done->txbuf[0],tx_done->txbuf[1],tx_done->txbuf[2],tx_done->txbuf[3],tx_done->txbuf[4]);
#if APP_SUPPORT_OTA_BOX
                uint8_t ret = 0;
                uint32_t num = app_ota_update_bin_read(send_buff);
                if(num){
                    if(num == APP_OTA_READ_LEN){
                        ret = app_ota_send_data(send_buff,APP_OTA_READ_LEN,OTA_DATA_HEADER);
                        TRACE("APP:ret 0= %x\n",ret);
                    }else{
                        ret = app_ota_send_data(send_buff,num,OTA_DATA_HEADER);
                        TRACE("APP:ret 1= %x\n",ret);
                    }
                    if(ret == BTDEF_PENDING){
                        //send ok
                        total_send_len+=num;
                        if(total_send_len == app_ota_update_bin_get_size()){
                            TRACE("APP:ota update success\n");
                            app_ota_update_bin_end();
                            app_ota_disconnect_device();
                        }
                    }else if(ret == BTDEF_IS_USEING){
                        //buffer is full,delay some time then send it.
                        if(app_ota_resend_timer == NULL){
                            co_timer_start(&app_ota_resend_timer,AIC_OTA_RESEND_TIME,(void *)num,app_ota_bin_send_timer,0);
                        }
                    }else{
                        //error occured
                    }
                }else{
                    //read error occured or read end
                }
#endif
            }
            break;
        case AIC_ADP_TEST_L2CAP_DATA_IND:
            {
                TestRxDone *rx_done = (TestRxDone *)aic_ota_msg->testparam;
                app_ota_receive_data(rx_done->rxbuf,rx_done->len);
            }
            break;
        default:
            break;
    }
}

void app_ota_init(void)
{
#if APP_SUPPORT_OTA_BOX
    app_ota_update_bin_init();
#endif
}
#endif
