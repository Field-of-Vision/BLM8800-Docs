#include "plf.h"
#if PLF_M2D_BLE
#include "app_m2d_ble.h"
#include "app_ble_only.h"
#include "flash_api_btdm.h"
#include "ble_task_msg.h"
#include "co_main.h"
#include "console.h"
#include "pmic_api.h"
#include "app_ble_queue.h"
#include "gpio_api.h"

#define USER_FLASH_ADDR             (0x081E3000)
#define M2D_BLOCK_BIT_NUM           (32)
#define M2D_MINI_BLOCK_SIZE         (256)
#define M2D_BLOCK_BIT_ADDR          (USER_FLASH_ADDR)
#define M2D_BLOCK_DATA_ADDR         (USER_FLASH_ADDR+0x1000)
#define M2D_BLOCK_BIT_FLASH_SIZE    (4096)
#define M2D_BLOCK_DATA_FLASH_SIZE   (M2D_BLOCK_BIT_NUM*8*M2D_MINI_BLOCK_SIZE)
#define M2D_REBOOT_TIME              3600000

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif /* max */

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif /* min */

extern uint8_t ble_addr[6];

static uint8_t Tmall_Genie_Wake_Word[16] = {0x00,0x01,0x02,0x01,0x05,0x03,0xff,0x00,0x01,
                                            0xff,0xff,0xff,0xff,0xff,0xff,
                                            0x00};

typedef struct {
    ble_ad_filter_t ad_filter;
    white_list_t wl;
}ble_m2d_flash_t;

typedef struct {
    uint8_t used_block_bit[M2D_BLOCK_BIT_NUM];
    ble_m2d_flash_t m2d_flash;
}m2d_block_info_t;

m2d_block_info_t m2d_info;

static co_timer *ble_delay_init_timer = NULL;
static co_timer *app_m2d_reboot_timer = NULL;

void m2d_set_tmall_genie_wakeup_word(void)
{
    Tmall_Genie_Wake_Word[9]  = ble_addr[5];
    Tmall_Genie_Wake_Word[10] = ble_addr[4];
    Tmall_Genie_Wake_Word[11] = ble_addr[3];
    Tmall_Genie_Wake_Word[12] = ble_addr[2];
    Tmall_Genie_Wake_Word[13] = ble_addr[1];
    Tmall_Genie_Wake_Word[14] = ble_addr[0];
    TRACE("Tmall Genie Word is : ");
    for(uint8_t i = 0; i < 16; i++){
        TRACE("0x%x ",Tmall_Genie_Wake_Word[i]);
    }
    TRACE("\n");
}

uint8_t *m2d_get_tmall_genie_wakeup_word(void)
{
    return Tmall_Genie_Wake_Word;
}

void m2d_flash_block_bit_read(void *buf, unsigned int len)
{
    unsigned int length = min(len, M2D_BLOCK_BIT_FLASH_SIZE);
    flash_read((void *)M2D_BLOCK_BIT_ADDR, length, buf);
}

void m2d_flash_block_bit_write(void *buf, unsigned int len)
{
    unsigned int length = min(len, M2D_BLOCK_BIT_FLASH_SIZE);
    flash_write((void *)M2D_BLOCK_BIT_ADDR, length, buf);
    flash_cache_invalid_range((void *)M2D_BLOCK_BIT_ADDR, length);
}

void m2d_flash_block_bit_erase(void)
{
    flash_erase((void *)M2D_BLOCK_BIT_ADDR, M2D_BLOCK_BIT_FLASH_SIZE);
    flash_cache_invalid_range((void *)M2D_BLOCK_BIT_ADDR, M2D_BLOCK_BIT_FLASH_SIZE);
}

void m2d_flash_block_data_read(void *buf, unsigned int len, unsigned int addr_offset)
{
    unsigned int length = min(len, M2D_MINI_BLOCK_SIZE);
    unsigned int addr = (M2D_BLOCK_DATA_ADDR+(M2D_MINI_BLOCK_SIZE*addr_offset));
    flash_read((void *)addr, length, buf);
}

void m2d_flash_block_data_write(void *buf, unsigned int len, unsigned int addr_offset)
{
    unsigned int length = min(len, M2D_MINI_BLOCK_SIZE);
    unsigned int addr = (M2D_BLOCK_DATA_ADDR+(M2D_MINI_BLOCK_SIZE*addr_offset));
    int ret = 0;
    ret = flash_write((void *)addr, length, buf);
    if(ret){
        TRACE("flash write fail %d\n",ret);
    }
    flash_cache_invalid_range((void *)addr, length);
}

void m2d_flash_block_data_erase(void)
{
    flash_erase((void *)M2D_BLOCK_DATA_ADDR, M2D_BLOCK_DATA_FLASH_SIZE);
    flash_cache_invalid_range((void *)M2D_BLOCK_DATA_ADDR, M2D_BLOCK_DATA_FLASH_SIZE);
}

int app_m2d_wl_addr_check(bd_addr_t bdaddr)
{
    int ret = 0;

    if(m2d_info.m2d_flash.wl.wl_bdaddr.addr[0] == bdaddr.addr[5]
    && m2d_info.m2d_flash.wl.wl_bdaddr.addr[1] == bdaddr.addr[4]
    && m2d_info.m2d_flash.wl.wl_bdaddr.addr[2] == bdaddr.addr[3]
    && m2d_info.m2d_flash.wl.wl_bdaddr.addr[3] == bdaddr.addr[2]
    && m2d_info.m2d_flash.wl.wl_bdaddr.addr[4] == bdaddr.addr[1]
    && m2d_info.m2d_flash.wl.wl_bdaddr.addr[5] == bdaddr.addr[0]){
        ret = 1;
    }
    return ret;
}

static void app_m2d_reboot_timer_hanlder(void *cb_param)
{
    TRACE("%s\n",__func__);
    pmic_chip_reboot(0xF);
}

static void app_m2d_reboot_timer_start(uint32_t delay)
{
    TRACE("%s ,handle 0x%x,%d\n",__func__,app_m2d_reboot_timer,delay);
    if(app_m2d_reboot_timer == NULL){
        if(delay){
            co_timer_start(&app_m2d_reboot_timer,delay,NULL,app_m2d_reboot_timer_hanlder,0);
        }else{
            co_timer_start(&app_m2d_reboot_timer,M2D_REBOOT_TIME,NULL,app_m2d_reboot_timer_hanlder,0);
        }
    }
}

void app_ble_m2d_init(void)
{
    unsigned int offset = 0;
    uint8_t do_break = 0;

    memset(&m2d_info,0xff,sizeof(m2d_block_info_t));
    m2d_flash_block_bit_read(&m2d_info.used_block_bit[0],M2D_BLOCK_BIT_NUM);
    for(uint8_t i = 0; i < M2D_BLOCK_BIT_NUM; i++){
        for(uint8_t j = 0; j < 8; j++){
            uint8_t ubbit = m2d_info.used_block_bit[i];
            if((ubbit<<j) & 0x80){
                do_break = 1;
                break;
            }else{
                offset++;
            }
        }
        if(do_break){
            break;
        }
    }
    TRACE("%s ,do_break %d,offset %d\n",__func__,do_break,offset);
    memset(&m2d_info,0xff,sizeof(m2d_block_info_t));
    if(offset){
        m2d_flash_block_data_read(&m2d_info.m2d_flash,sizeof(m2d_block_info_t),(offset-1));
        TRACE("ble m2d read user data ,len = %d\n",m2d_info.m2d_flash.ad_filter.len);
        if(m2d_info.m2d_flash.ad_filter.len <= ADV_DATA_LEN
        && m2d_info.m2d_flash.ad_filter.len >0){
            //use flash value
        }else{
            #if 0
            //use default value
            m2d_info.m2d_flash.ad_filter.len = 3;
            m2d_info.m2d_flash.ad_filter.ad_type = 0xff;
            m2d_info.m2d_flash.ad_filter.data[0] = 0;
            m2d_info.m2d_flash.ad_filter.data[1] = 1;
            #endif
        }
    }else{
        #if 0
        //use default value
        m2d_info.m2d_flash.ad_filter.len = 3;
        m2d_info.m2d_flash.ad_filter.ad_type = 0xff;
        m2d_info.m2d_flash.ad_filter.data[0] = 0;
        m2d_info.m2d_flash.ad_filter.data[1] = 1;
        #endif
    }
    if(offset >= (M2D_BLOCK_BIT_NUM*8 - 56)){
        m2d_flash_block_bit_erase();
        m2d_flash_block_data_erase();
        memset(&m2d_info.used_block_bit[0],0xff,M2D_BLOCK_BIT_NUM);
        m2d_info.used_block_bit[0] = 0x7f;
        m2d_flash_block_bit_write(&m2d_info.used_block_bit[0],M2D_BLOCK_BIT_NUM);
        m2d_flash_block_data_write((void*)&m2d_info.m2d_flash,sizeof(ble_m2d_flash_t),0);
    }
    app_ble_set_ad_filter(&m2d_info.m2d_flash.ad_filter);
    app_m2d_reboot_timer_start(0);
    m2d_set_tmall_genie_wakeup_word();
}

void app_ble_delay_init_timer(void *cb_param)
{
    app_ble_scan_msg_start();
}

void app_ble_start_delay_init(void)
{
    if(ble_delay_init_timer == NULL){
        if(m2d_info.m2d_flash.wl.wl_bdaddr_type != 0xff){
            TRACE("flash white list rd done\n");
            TRACE("wl addr_type 0x%x\n",m2d_info.m2d_flash.wl.wl_bdaddr_type);
            TRACE("wl addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",m2d_info.m2d_flash.wl.wl_bdaddr.addr[0],
                                                            m2d_info.m2d_flash.wl.wl_bdaddr.addr[1],
                                                            m2d_info.m2d_flash.wl.wl_bdaddr.addr[2],
                                                            m2d_info.m2d_flash.wl.wl_bdaddr.addr[3],
                                                            m2d_info.m2d_flash.wl.wl_bdaddr.addr[4],
                                                            m2d_info.m2d_flash.wl.wl_bdaddr.addr[5]);
            appm_set_whitelist(&m2d_info.m2d_flash.wl,1);
        }
        co_timer_start(&ble_delay_init_timer, 2000, NULL, app_ble_delay_init_timer,0);
    }
}
#endif
