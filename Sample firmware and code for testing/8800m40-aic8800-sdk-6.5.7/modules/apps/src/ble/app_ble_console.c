#include "tgt_cfg_bt.h"
#if PLF_BT_STACK == 1
#include <string.h>
#if (PLF_CONSOLE)
#include "console.h"
#if PLF_BLE_ONLY == 1
#include "ble_task.h"
#endif
#endif // (PLF_CONSOLE)
#include "app_ble_queue.h"
#include "app_ble_only.h"
#include "co_main.h"
#include "sleep_api.h"
#include "flash_api_btdm.h"
#if PLF_M2D_BLE
#include "app_m2d_ble.h"
#endif
#if PLF_M2D_OTA
#include "m2d_ota.h"
#endif

#if (PLF_CONSOLE)
extern uint8_t ble_addr[6];
extern uint8_t bt_addr[6];

static int app_ble_scan_stop(int argc, char * const argv[])
{
    dbg("%s\r\n", __func__);
    app_ble_scan_msg_stop();
    return ERR_NONE;
}

static int app_ble_scan_start(int argc, char * const argv[])
{
    dbg("%s\r\n", __func__);
    app_ble_scan_msg_start();
    return ERR_NONE;
}

static int app_ble_adv_data_set(int argc, char * const argv[])
{
    unsigned char data[31] = {0};
    unsigned int idx = 0, j = 2;
    unsigned int len = 0;

    if ((argc < 1)) {
        dbg ("Usage: [len] [data0] [data1] ...\n");
        return 1;
    }

    len = console_cmd_strtoul(argv[1], NULL, 10);
    dbg ("%s  len = %d, data: ",__func__,len);
    while(j <= argc) {
        data[idx] = console_cmd_strtoul(argv[j], NULL, 16);
        dbg ("0x%x ",data[idx]);
        idx ++;
        j++;
    }
    dbg ("\n");
    if(len)
        app_ble_adv_data_set_msg_send(len,data);
    return ERR_NONE;
}

static int app_ble_adv_scan_res_set(int argc, char * const argv[])
{
    unsigned char data[31] = {0};
    unsigned int idx = 0, j = 2;
    unsigned int len = 0;

    if ((argc < 1)) {
        dbg ("Usage: [len] [data0] [data1] ...\n");
        return 1;
    }

    len = console_cmd_strtoul(argv[1], NULL, 10);
    dbg ("%s  len = %d, data: ",__func__,len);
    while(j <= argc) {
        data[idx] = console_cmd_strtoul(argv[j], NULL, 16);
        dbg ("0x%x ",data[idx]);
        idx ++;
        j++;
    }
    dbg ("\n");
    if(len)
        app_ble_adv_scan_res_set_msg_send(len,data);
    return ERR_NONE;
}

static int app_ble_adv_data_update(int argc, char * const argv[])
{
    unsigned char data[31] = {0};
    unsigned int idx = 0, j = 2;
    unsigned int len = 0;

    if ((argc < 1)) {
        dbg ("Usage: [len] [data0] [data1] ...\n");
        return 1;
    }

    len = console_cmd_strtoul(argv[1], NULL, 10);
    dbg ("%s  len = %d, data: ",__func__,len);
    while(j <= argc) {
        data[idx] = console_cmd_strtoul(argv[j], NULL, 16);
        dbg ("0x%x ",data[idx]);
        idx ++;
        j++;
    }
    dbg ("\n");
    if(len)
        app_ble_adv_data_update_msg_send(len,data);
    return ERR_NONE;
}

static int app_ble_adv_scan_res_update(int argc, char * const argv[])
{
    unsigned char data[31] = {0};
    unsigned int idx = 0, j = 2;
    unsigned int len = 0;

    if ((argc < 1)) {
        dbg ("Usage: [len] [data0] [data1] ...\n");
        return 1;
    }

    len = console_cmd_strtoul(argv[1], NULL, 10);
    dbg ("%s  len = %d, data: ",__func__,len);
    while(j <= argc) {
        data[idx] = console_cmd_strtoul(argv[j], NULL, 16);
        dbg ("0x%x ",data[idx]);
        idx ++;
        j++;
    }
    dbg ("\n");
    if(len)
        app_ble_adv_scan_res_update_msg_send(len,data);
    return ERR_NONE;
}

static int app_ble_adv_param_update(int argc, char * const argv[])
{
    unsigned int adv_intv_min;
    unsigned int adv_intv_max;
    if (argc < 3) {
        return ERR_WRONG_ARGS;
    }

    adv_intv_min = console_cmd_strtoul(argv[1], NULL, 10);
    adv_intv_max  = console_cmd_strtoul(argv[2], NULL, 10);

    app_ble_adv_param_update_msg_send(adv_intv_min,adv_intv_max);

    return ERR_NONE;
}

static int app_ble_adv_stop(int argc, char * const argv[])
{
    dbg("%s\r\n", __func__);
    app_ble_adv_stop_msg_send();
    return ERR_NONE;
}

static int app_ble_adv_start(int argc, char * const argv[])
{
    dbg("%s\r\n", __func__);
    app_ble_adv_start_msg_send();
    return ERR_NONE;
}

static int app_ble_adv_restart(int argc, char * const argv[])
{
    dbg("%s\r\n", __func__);
    app_ble_adv_restart_msg_send();
    return ERR_NONE;
}

static int app_ble_discon(int argc, char * const argv[])
{
    unsigned int conidx = 0;
    dbg("%s\r\n", __func__);

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);

    app_ble_disconnect_msg_send(conidx);
    return ERR_NONE;
}

static int app_ble_con_param_update(int argc, char * const argv[])
{
    unsigned int conidx;
    unsigned int adv_intv_min;
    unsigned int adv_intv_max;
    unsigned int conn_latency;
    unsigned int time_out;

    if (argc < 6) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    adv_intv_min = console_cmd_strtoul(argv[2], NULL, 10);
    adv_intv_max  = console_cmd_strtoul(argv[3], NULL, 10);
    conn_latency = console_cmd_strtoul(argv[4], NULL, 10);
    time_out  = console_cmd_strtoul(argv[5], NULL, 10);

    app_ble_con_param_msg_send(conidx,adv_intv_min,adv_intv_max,conn_latency,time_out);
    return ERR_NONE;
}

static int app_ble_onoff_control(int argc, char * const argv[])
{
    unsigned int on_off;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    on_off = console_cmd_strtoul(argv[1], NULL, 10);
    if (on_off > 1) {
        return ERR_WRONG_ARGS;
    }
#if PLF_BLE_ONLY
    if(on_off){
        ble_task_set_need_pon(true);
        ble_task_init(INIT_CONSOLE);
    }else{
        ble_task_deinit();
    }
#endif
    return ERR_NONE;
}

#if (BLE_APP_BATT)
static int app_batt_set(int argc, char * const argv[])
{
    uint8_t data = app_batt_get_lvl();
    dbg("%s set %d\r\n", __func__, data);
    app_batt_send_lvl(data);
    return ERR_NONE;
}
#endif // (BLE_APP_BATT)

static int app_ble_user_sleep(int argc, char * const argv[])
{
    unsigned int sleep;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    sleep = console_cmd_strtoul(argv[1], NULL, 10);
    if (sleep > 1) {
        return ERR_WRONG_ARGS;
    }

    if (sleep) {
        user_sleep_allow(1);
    } else {
        user_sleep_allow(0);
    }
    return ERR_NONE;
}

static int app_ble_sleep_level(int argc, char * const argv[])
{
    unsigned int level;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    if(*argv[1] == '?') {
        dbg("%d\n", sleep_level_get());
        return ERR_NONE;
    }

    level = console_cmd_strtoul(argv[1], NULL, 10);
    if (level >= PM_LEVEL_LEVEL_NUM) {
        return ERR_WRONG_ARGS;
    }

    sleep_level_set(level);

    return ERR_NONE;
}

static int app_ble_user_wakeup_source(int argc, char * const argv[])
{
    int src, en, arg = 0;

    if (argc < 3) {
        return ERR_WRONG_ARGS;
    }

    src = console_cmd_strtoul(argv[1], NULL, 10);
    if (src >= WAKESRC_NUM_MAX) {
        return ERR_WRONG_ARGS;
    }
    en  = console_cmd_strtoul(argv[2], NULL, 10);
    if (src == WAKESRC_TIMER) {
        if (argc < 4) {
            return ERR_WRONG_ARGS;
        }
        arg = console_cmd_strtoul(argv[3], NULL, 10);
    }

    user_sleep_wakesrc_set(src, en, arg);

    return ERR_NONE;
}

static int app_ble_del_bond(int argc, char * const argv[])
{
    unsigned int conidx;
    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 0);
    dbg("%s conidx %d\r\n", __func__,conidx);
    
    app_ble_del_bond_msg_send(conidx);
    return ERR_NONE;
}

static int app_ble_enable_dut(int argc, char * const argv[])
{
    app_ble_enter_dut_msg_send();
    return ERR_NONE;
}

static int app_ble_enable_non_signaling_test(int argc, char * const argv[])
{
    app_ble_enter_non_signaling_test_msg_send();
    return ERR_NONE;
}

static int app_ble_scan_en(int argc, char * const argv[])
{
    unsigned int scan_en;
    unsigned int dut = 0;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    scan_en = console_cmd_strtoul(argv[1], NULL, 0);
    if (scan_en > 0x03) {
        return ERR_WRONG_ARGS;
    }
    dut = console_cmd_strtoul(argv[2], NULL, 10);
    TRACE("scan_en %d,dut %d\n",scan_en,dut);
    app_ble_wr_scan_en(scan_en);

    return ERR_NONE;
}

static int app_ble_addr_rdwr(int argc, char * const argv[])
{
    if ((argc < 2) || ((strlen(argv[1]) == 1) && (argv[1][0] == '?'))) { // read
        struct bd_addr user_addr;
        if (flash_btdm_le_rand_addr_read(&user_addr.addr[0]) == INFO_READ_DONE) {
            memcpy(&ble_addr[0], &user_addr.addr[0], BD_ADDR_LEN);
        } else {
            dbg("no ble addr in flash, use default\r\n");
        }
        dbg("read ble addr: %02x%02x%02x%02x%02x%02x\r\n",
            ble_addr[0], ble_addr[1], ble_addr[2], ble_addr[3], ble_addr[4], ble_addr[5]);
    } else { // write
        char str0[8 + 1];
        char *str1;
        unsigned char addr[6];
        uint32_t addr0, addr1;
        if (strlen(argv[1]) != 12) {
            return -1;
        }
        str1 = &argv[1][0];
        memcpy(str0, &argv[1][4], 8);
        str0[8] = '\0';
        str1[4] = '\0';
        addr0 = console_cmd_strtoul(str0, NULL, 16);
        addr1 = console_cmd_strtoul(str1, NULL, 16) & 0x0000ffff;
        addr[0] = (unsigned char)(addr1 >> 8);
        addr[1] = (unsigned char)(addr1 >> 0);
        addr[2] = (unsigned char)(addr0 >> 24);
        addr[3] = (unsigned char)(addr0 >> 16);
        addr[4] = (unsigned char)(addr0 >> 8);
        addr[5] = (unsigned char)(addr0 >> 0);
        memcpy(&ble_addr[0], &addr[0], BD_ADDR_LEN);
        flash_btdm_le_rand_addr_write(addr);
        dbg("write ble addr: %04x%08x\r\n", addr1, addr0);
    }
    return 0;
}

static int app_ble_data_send_ctrl(int argc, char * const argv[])
{
    unsigned int codec_type;
    unsigned int state = 0;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    codec_type = console_cmd_strtoul(argv[1], NULL, 10);
    state = console_cmd_strtoul(argv[2], NULL, 10);
    TRACE("codec_type %d,state %d\n",codec_type,state);
    app_ble_data_send_start(codec_type,state);
    return ERR_NONE;
}

#if PLF_M2D_BLE
static int app_ble_m2d_flash_erase(int argc, char * const argv[])
{
    TRACE("%s\n",__func__);
    m2d_flash_block_bit_erase();
    m2d_flash_block_data_erase();
    return ERR_NONE;
}
#endif

#if PLF_M2D_OTA
static int  m2d_ota_img_info_update(int argc, char * const argv[])
{
    m2d_ota_updata_img_info();
    dbg("img_info OK!\r\n");
    return ERR_NONE;
}
#endif

static int do_show_heap(int argc, char * const argv[])
{
    int total, used, free, max_used;

    rtos_heap_info(&total, &free, &max_used);
    used = total - free;
    max_used = total - max_used;
    dbg("RTOS HEAP: free=%d used=%d max_used=%d/%d\n",
                free, used, max_used, total);

    return ERR_NONE;
}

#if BLE_APP_UDFC
static int app_ble_connect(int argc, char * const argv[])
{
    unsigned int addr_type;
    unsigned char addr[6];

    if (argc < 8) {
        return ERR_WRONG_ARGS;
    }

    addr_type = console_cmd_strtoul(argv[1], NULL, 10);
    addr[0] = console_cmd_strtoul(argv[2], NULL, 16);
    addr[1] = console_cmd_strtoul(argv[3], NULL, 16);
    addr[2] = console_cmd_strtoul(argv[4], NULL, 16);
    addr[3] = console_cmd_strtoul(argv[5], NULL, 16);
    addr[4] = console_cmd_strtoul(argv[6], NULL, 16);
    addr[5] = console_cmd_strtoul(argv[7], NULL, 16);

    app_ble_udfc_connect(addr,addr_type);

    return ERR_NONE;
}

static int app_ble_connect_cancel(int argc, char * const argv[])
{
    app_ble_udfc_connect_cancel();

    return ERR_NONE;
}

static int app_ble_write(int argc, char * const argv[])
{
    unsigned char data[200] = {0};
    unsigned int idx = 0, j = 4;
    unsigned int len = 0;
    unsigned int handle = 0;
    unsigned int conidx = 0;

    if (argc < 5) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    handle = console_cmd_strtoul(argv[2], NULL, 10);
    len = console_cmd_strtoul(argv[3], NULL, 10);
    dbg ("%s conidx = %x handle = 0x%x len = %d, data: ",__func__,conidx,handle,len);
    while(j <= argc) {
        data[idx] = console_cmd_strtoul(argv[j], NULL, 16);
        dbg ("0x%x ",data[idx]);
        idx ++;
        j++;
    }
    dbg ("\n");
    if(handle && len){
        app_ble_udfc_write(conidx,handle,len,data);
    }

    return ERR_NONE;
}

static int app_ble_write_no_response(int argc, char * const argv[])
{
    unsigned char data[200] = {0};
    unsigned int idx = 0, j = 4;
    unsigned int len = 0;
    unsigned int handle = 0;
    unsigned int conidx = 0;

    if (argc < 5) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    handle = console_cmd_strtoul(argv[2], NULL, 10);
    len = console_cmd_strtoul(argv[3], NULL, 10);
    dbg ("%s conidx = %x handle = 0x%x len = %d, data: ",__func__,conidx,handle,len);
    while(j <= argc) {
        data[idx] = console_cmd_strtoul(argv[j], NULL, 16);
        dbg ("0x%x ",data[idx]);
        idx ++;
        j++;
    }
    dbg ("\n");
    if(handle && len){
        app_ble_udfc_write_no_response(conidx,handle,len,data);
    }

    return ERR_NONE;
}

static int app_ble_read(int argc, char * const argv[])
{
    unsigned int handle = 0;
    unsigned int conidx = 0;
    if (argc < 3) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    handle = console_cmd_strtoul(argv[2], NULL, 10);
    dbg ("%s conidx = %x,handle = 0x%x \n ",__func__,conidx,handle);
    if(handle){
        app_ble_udfc_read(conidx,handle);
    }
    return ERR_NONE;
}

static int app_ble_notification_cfg(int argc, char * const argv[])
{
    unsigned int cfg = 0;
    unsigned int handle = 0;
    unsigned int conidx = 0;
    if (argc < 3) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    handle = console_cmd_strtoul(argv[2], NULL, 10);
    cfg = console_cmd_strtoul(argv[3], NULL, 10);
    dbg ("%s conidx = %x,handle = 0x%x ,cfg = %x\n ",__func__,conidx,handle,cfg);

    if(handle){
        app_ble_udfc_notification_cfg(conidx,handle,cfg);
    }

    return ERR_NONE;
}

static int app_ble_indication_cfg(int argc, char * const argv[])
{
    unsigned int cfg = 0;
    unsigned int handle = 0;
    unsigned int conidx = 0;
    if (argc < 3) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    handle = console_cmd_strtoul(argv[2], NULL, 10);
    cfg = console_cmd_strtoul(argv[3], NULL, 10);

    if(handle){
        app_ble_udfc_indication_cfg(conidx,handle,cfg);
    }

    return ERR_NONE;
}

static int app_ble_discover(int argc, char * const argv[])
{
    unsigned int conidx = 0;
    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    dbg ("%s conidx = %x \n ",__func__,conidx);
    app_ble_udfc_discover(conidx);
    return ERR_NONE;
}

#endif

#if BLE_APP_UDFS
static int app_ble_update_read_value(int argc, char * const argv[])
{
    unsigned char data[200] = {0};
    unsigned int idx = 0, j = 5;
    unsigned int conidx = 0;
    unsigned int prf_user_id = 0;
    unsigned int att_idx = 0;
    unsigned int len = 0;

    if (argc < 6) {
        return ERR_WRONG_ARGS;
    }

    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    prf_user_id = console_cmd_strtoul(argv[2], NULL, 10);
    att_idx = console_cmd_strtoul(argv[3], NULL, 10);
    len = console_cmd_strtoul(argv[4], NULL, 10);
    dbg ("%s len = %d, data: ",__func__,len);
    while(j <= argc) {
        data[idx] = console_cmd_strtoul(argv[j], NULL, 16);
        dbg ("0x%x ",data[idx]);
        idx ++;
        j++;
    }
    dbg ("\n");
    if(len){
        app_ble_udfs_update_read_value(conidx,prf_user_id,att_idx,data,len);
    }

    return ERR_NONE;
}

static int app_ble_send_notification(int argc, char * const argv[])
{
    unsigned char data[200] = {0};
    unsigned int idx = 0, j = 5;
    unsigned int conidx = 0;
    unsigned int prf_user_id = 0;
    unsigned int att_idx = 0;
    unsigned int len = 0;

    if (argc < 6) {
        return ERR_WRONG_ARGS;
    }

    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    prf_user_id = console_cmd_strtoul(argv[2], NULL, 10);
    att_idx = console_cmd_strtoul(argv[3], NULL, 10);
    len = console_cmd_strtoul(argv[4], NULL, 10);
    dbg ("%s len = %d, data: ",__func__,len);
    while(j <= argc) {
        data[idx] = console_cmd_strtoul(argv[j], NULL, 16);
        dbg ("0x%x ",data[idx]);
        idx ++;
        j++;
    }
    dbg ("\n");
    if(len){
        app_ble_udfs_send_notification(conidx,prf_user_id,att_idx,data,len);
    }

    return ERR_NONE;
}

static int app_ble_send_indication(int argc, char * const argv[])
{
    unsigned char data[200] = {0};
    unsigned int idx = 0, j = 5;
    unsigned int conidx = 0;
    unsigned int prf_user_id = 0;
    unsigned int att_idx = 0;
    unsigned int len = 0;

    if (argc < 6) {
        return ERR_WRONG_ARGS;
    }

    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    prf_user_id = console_cmd_strtoul(argv[2], NULL, 10);
    att_idx = console_cmd_strtoul(argv[3], NULL, 10);
    len = console_cmd_strtoul(argv[4], NULL, 10);
    dbg ("%s len = %d, data: ",__func__,len);
    while(j <= argc) {
        data[idx] = console_cmd_strtoul(argv[j], NULL, 16);
        dbg ("0x%x ",data[idx]);
        idx ++;
        j++;
    }
    dbg ("\n");
    if(len){
        app_ble_udfs_send_indication(conidx,prf_user_id,att_idx,data,len);
    }

    return ERR_NONE;
}

static int app_ble_send_dbinit(int argc, char * const argv[])
{
    app_ble_udfs_send_db_init();
    dbg("%s\n",__func__);
    return ERR_NONE;
}
#endif
static int app_ble_send_exchange_mtu(int argc, char * const argv[])
{
    unsigned int conidx = 0;
    unsigned int mtu = 0;

    if (argc < 3) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    mtu = console_cmd_strtoul(argv[2], NULL, 10);
    dbg("%s,conidx %d, mtu %d\n",__func__,conidx,mtu);
    app_ble_exchange_mtu(conidx,mtu);
    return ERR_NONE;
}

static int app_ble_set_stack_print(int argc, char * const argv[])
{
    unsigned int print_level = 0;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }
    print_level = console_cmd_strtoul(argv[1], NULL, 16);
    dbg("%s,print_level %x\n",__func__,print_level);
    app_ble_set_print(print_level);
    return ERR_NONE;
}

static int app_ble_send_start_bonding(int argc, char * const argv[])
{
    unsigned int conidx = 0;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }
    conidx = console_cmd_strtoul(argv[1], NULL, 10);
    dbg("%s,conidx %d\n",__func__,conidx);
    app_ble_start_bonding(conidx);
    return ERR_NONE;
}


void app_ble_test_command_add(void)
{
    console_cmd_add("heap",     "- Show heap info eg: heap", 1, 1, do_show_heap);
    console_cmd_add("ble_scan_stop", "eg:ble_scan_stop", 1, 1, app_ble_scan_stop);
    console_cmd_add("ble_scan_start", "eg:ble_scan_start", 1, 1, app_ble_scan_start);
    console_cmd_add("ble_adv_data_set", "eg:ble_adv_data_set <len> <data0> <data1> <....>  ", 1, 32, app_ble_adv_data_set);
    console_cmd_add("ble_adv_scan_res_set", "eg:ble_adv_scan_res_set <len> <data0> <data1> <....>  ", 1, 32, app_ble_adv_scan_res_set);
    console_cmd_add("ble_adv_data_update", "eg:ble_adv_data_update <len> <data0> <data1> <....>  ", 1, 32, app_ble_adv_data_update);
    console_cmd_add("ble_adv_scan_res_update", "eg:ble_adv_scan_res_update <len> <data0> <data1> <....>  ", 1, 32, app_ble_adv_scan_res_update);
    console_cmd_add("ble_adv_param", "eg:ble_adv_param <adv_intv_min> <adv_intv_max>", 1, 3, app_ble_adv_param_update);
    console_cmd_add("ble_adv_stop", "eg:ble_adv_stop", 1, 1, app_ble_adv_stop);
    console_cmd_add("ble_adv_start", "eg:ble_adv_start", 1, 1, app_ble_adv_start);
    console_cmd_add("ble_adv_restart", "eg:ble_adv_restart", 1, 1, app_ble_adv_restart);
    console_cmd_add("ble_discon", "eg:ble disconnet:ble_discon <conidx>", 1, 2, app_ble_discon);
    console_cmd_add("ble_con_param", "ble con param update  eg: ble_con_param <conidx> <adv_intv_min> <adv_intv_max> <conn_latency> <time_out>", 1, 6, app_ble_con_param_update);
    console_cmd_add("ble_on", "ble_on/off  eg: ble_on <1/0>", 2, 2, app_ble_onoff_control);
    console_cmd_add("ble_data_send", "eg:ble_data_send  <codec_type> <on/off>", 2, 3, app_ble_data_send_ctrl);
#if (BLE_APP_BATT)
    console_cmd_add("batt_set", "batt set", 1, 1, app_batt_set);
#endif // (BLE_APP_BATT)
    console_cmd_add("ble_del_bond", "ble delete bond   eg:ble_del_bond <conidx>", 1, 2, app_ble_del_bond);
    console_cmd_add("ble_usrslp", "Allow user sleep   eg: ble_usrslp <1/0>", 2, 2, app_ble_user_sleep);
    console_cmd_add("ble_slplvl", "Set system sleep level   eg: ble_slplvl <1/2/3>", 2, 2, app_ble_sleep_level);
    console_cmd_add("ble_usrwusrc", "Set user wakeup source", 3, 4, app_ble_user_wakeup_source);
    console_cmd_add("ble_addr", "rdwr ble addr", 1, 2, app_ble_addr_rdwr);
    console_cmd_add("dut", "enter dut   eg: dut", 1, 1, app_ble_enable_dut);
    console_cmd_add("non_signaling_test", "enter non_signaling_test   eg: non_signaling_test", 1, 1, app_ble_enable_non_signaling_test);
    console_cmd_add("scan_en", "egscan_en <scan_type> <is_dut>", 2, 3, app_ble_scan_en);
#if PLF_M2D_BLE
    console_cmd_add("m2d_erase", "eg:m2d_erase", 1, 1, app_ble_m2d_flash_erase);
#endif
#if PLF_M2D_OTA
    console_cmd_add("m2d_img", "eg:m2d_img : update current img info for bootloader", 1, 1, m2d_ota_img_info_update);
#endif
#if BLE_APP_UDFC
    console_cmd_add("ble_conn", "ble connect  eg: ble_conn <addr_type> <addr0> <addr1> <addr2> <addr3> <addr4> <addr5>", 1, 8, app_ble_connect);
    console_cmd_add("ble_conn_cancel", "ble connect   eg: ble_conn_cancel", 1, 1, app_ble_connect_cancel);
    console_cmd_add("ble_wr", "ble write   eg: ble_wr <conidx> <handle> <len> <data0> <data1> ....", 1, 200, app_ble_write);
    console_cmd_add("ble_wr_nores", "ble write no response   eg: ble_wr_nores <conidx> <handle> <len> <data0> <data1> ....", 1, 200, app_ble_write_no_response);
    console_cmd_add("ble_rd", "ble read   eg:  ble_rd <conidx> <handle>", 1, 3, app_ble_read);
    console_cmd_add("ble_ntf_cfg", "ble set notification cfg   eg: ble_ntf_cfg <conidx> <handle> <1/0>", 1, 4, app_ble_notification_cfg);
    console_cmd_add("ble_ind_cfg", "ble set indication cfg   eg: ble_ind_cfg <conidx> <handle> <1/0>", 1, 4, app_ble_indication_cfg);
    console_cmd_add("ble_discover", "ble_discover   eg: ble_discover <conidx>", 1, 2, app_ble_discover);
#endif
#if BLE_APP_UDFS
    console_cmd_add("ble_updata_rdval", "ble update read value   eg: ble_updata_rdval <conidx> <prf_user_id> <att_idx> <len> <data0> <data1> ....", 1, 200, app_ble_update_read_value);
    console_cmd_add("ble_sd_ntf", "ble send notification   eg: ble_sd_ntf <conidx> <prf_user_id> <att_idx> <len> <data0> <data1> ....", 1, 200, app_ble_send_notification);
    console_cmd_add("ble_sd_ind", "ble send indication   eg: ble_sd_ind <conidx> <prf_user_id> <att_idx> <len> <data0> <data1> ....", 1, 200, app_ble_send_indication);
    console_cmd_add("ble_sd_dbinit", "ble delay add profile   eg: ble_sd_dbinit ", 1, 1, app_ble_send_dbinit);
#endif
    console_cmd_add("ble_exchangemtu", "ble send exchange mtu   eg: ble_exchangemtu <conidx> <mtu> ", 1, 3, app_ble_send_exchange_mtu);
    console_cmd_add("ble_setprint", "ble set stack print level   eg: ble_setprint <level> ", 1, 3, app_ble_set_stack_print);
    console_cmd_add("ble_startbonding", "ble start bonding  eg: ble_startbonding <conidx> ", 1, 2, app_ble_send_start_bonding);
}
#endif // (PLF_CONSOLE)


#endif
