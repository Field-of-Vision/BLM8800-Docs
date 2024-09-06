/**
 ****************************************************************************************
 *
 * @file app_console.c
 *
 * @brief Implementation of the fully hosted console task.
 *
 * Copyright (C) RivieraWaves 2017-2018
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APP_CONSOLE
 * @{
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "tgt_cfg_bt.h"
#if PLF_BT_STACK == 1
#if PLF_BLE_ONLY == 0
#if PLF_CONSOLE
#include <stdlib.h>
#include "rtos.h"
#include "dbg_assert.h"
#include "console.h"
#include "command.h"
#include "app_bt_queue.h"
#include "app_bt.h"
#if APP_SUPPORT_A2DP_SOURCE == 1
#include "app_a2dp_source.h"
#endif
#if APP_SUPPORT_HFG == 1
#include "app_hfg.h"
#endif
#include "sleep_api.h"
#if APP_SUPPORT_OTA_BOX
#include "app_ota_box.h"
#endif
#if APP_SUPPORT_SPP
#include "app_spp.h"
#endif

#if APP_SUPPORT_TWS == 1
static int  app_tws_sync_control(int argc, char * const argv[])
{
    unsigned int on_off;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    on_off = console_cmd_strtoul(argv[1], NULL, 10);
    if (on_off > 1) {
        return ERR_WRONG_ARGS;
    }

    if(on_off){
        app_bt_tws_sync_control(1);
    }else{
        app_bt_tws_sync_control(0);
    }

    return ERR_NONE;
}

static int  app_tws_mss_control(int argc, char * const argv[])
{
    app_bt_tws_mss_control();

    return ERR_NONE;
}

static int  app_tws_stop_local_sync_control(int argc, char * const argv[])
{
    app_bt_tws_stop_local_sync_control();

    return ERR_NONE;
}

static int  app_tws_reset(int argc, char * const argv[])
{
    app_bt_tws_reset();

    return ERR_NONE;
}

static int  app_tws_disc(int argc, char * const argv[])
{
    app_bt_tws_disc();

    return ERR_NONE;
}

static int  app_tws_visible_reopen(int argc, char * const argv[])
{
    app_bt_tws_visible_reopen();

    return ERR_NONE;
}
#endif
static int  app_key_enter(int argc, char * const argv[])
{
    unsigned int key;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    key = console_cmd_strtoul(argv[1], NULL, 10);

    app_bt_send_key(key);
    return ERR_NONE;
}
#if FPGA == 0
static int app_erase_flash(int argc, char * const argv[])
{
    app_bt_erased_flash();
    return ERR_NONE;
}
#endif
static int app_enable_dut(int argc, char * const argv[])
{
    app_bt_dut_mode();
    return ERR_NONE;
}

static int app_enable_non_signaling_test(int argc, char * const argv[])
{
    app_bt_non_signaling_test_mode();
    return ERR_NONE;
}

static int app_onoff_bt_trace(int argc, char * const argv[])
{
    unsigned int on_off;
    unsigned int level;

    if (argc < 3) {
        return ERR_WRONG_ARGS;
    }

    on_off = console_cmd_strtoul(argv[1], NULL, 10);
    if (on_off > 1) {
        return ERR_WRONG_ARGS;
    }

    level = console_cmd_strtoul(argv[2], NULL, 16);
    TRACE("level 0x%x\n",level);

    if(on_off){
        aic_change_host_log_level(TRUE,level);
    }else{
        aic_change_host_log_level(FALSE,level);
    }

    return ERR_NONE;
}

static int app_scan_en(int argc, char * const argv[])
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
    app_bt_wr_scan_en(scan_en,dut);

    return ERR_NONE;
}

static int app_inquiry_dev(int argc, char * const argv[])
{
    unsigned int len;
    unsigned int maxResp;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    len = console_cmd_strtoul(argv[1], NULL, 10);
    maxResp = console_cmd_strtoul(argv[2], NULL, 10);
    TRACE("inquiry_dev len %d,maxResp %d\n",len,maxResp);
    app_bt_inquiry_dev(len,maxResp);
#if APP_SUPPORT_OTA_BOX
    app_ota_clean_addr_list();
#endif
    return ERR_NONE;
}

static int app_inquiry_cancel(int argc, char * const argv[])
{
    TRACE("inquiry_cancel\n");
    app_bt_inquiry_cancel();
    return ERR_NONE;
}

static int app_disc_all_link(int argc, char * const argv[])
{
    TRACE("app_disc_all_link\n");
    app_bt_disconnect_all_acl();
    return ERR_NONE;
}

#if APP_SUPPORT_OTA_BOX
static int app_ota_connect(int argc, char * const argv[])
{
    BT_ADDR ota_addr;

    if (argc < 7) {
        return ERR_WRONG_ARGS;
    }

    ota_addr.addr[0] = (uint8_t)console_cmd_strtoul(argv[1], NULL, 16);
    ota_addr.addr[1] = (uint8_t)console_cmd_strtoul(argv[2], NULL, 16);
    ota_addr.addr[2] = (uint8_t)console_cmd_strtoul(argv[3], NULL, 16);
    ota_addr.addr[3] = (uint8_t)console_cmd_strtoul(argv[4], NULL, 16);
    ota_addr.addr[4] = (uint8_t)console_cmd_strtoul(argv[5], NULL, 16);
    ota_addr.addr[5] = (uint8_t)console_cmd_strtoul(argv[6], NULL, 16);

    app_bt_ota_connect(&ota_addr);
    return ERR_NONE;
}

static int app_ota_connect_by_id(int argc, char * const argv[])
{
    unsigned int id;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }
    id = (uint8_t)console_cmd_strtoul(argv[1], NULL, 10);
    dbg("select %d\n",id);
    app_bt_ota_connect_by_id(id);
    return ERR_NONE;
}

#endif

#if APP_SUPPORT_A2DP_SOURCE == 1
static int app_a2dp_source_control(int argc, char * const argv[])
{
    unsigned int on_off;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    on_off = console_cmd_strtoul(argv[1], NULL, 10);
    if (on_off > 2) {
        return ERR_WRONG_ARGS;
    }

    switch(on_off){
        case 0:
            app_a2dp_source_connect_default_device();
            break;
        case 1:
            app_a2dp_source_start();
            break;
        case 2:
            app_a2dp_source_suspend();
            break;
        default:
            break;
    }

    return ERR_NONE;
}
#endif

#if APP_SUPPORT_HFG == 1
static int app_hfg_control(int argc, char * const argv[])
{
    unsigned int value;

    if (argc < 2) {
        return ERR_WRONG_ARGS;
    }

    value = console_cmd_strtoul(argv[1], NULL, 10);
    if (value > 2) {
        return ERR_WRONG_ARGS;
    }

    switch(value){
        case 0:
            {
                BT_ADDR con_addr;
                con_addr.addr[0] = (uint8_t)console_cmd_strtoul(argv[2], NULL, 16);
                con_addr.addr[1] = (uint8_t)console_cmd_strtoul(argv[3], NULL, 16);
                con_addr.addr[2] = (uint8_t)console_cmd_strtoul(argv[4], NULL, 16);
                con_addr.addr[3] = (uint8_t)console_cmd_strtoul(argv[5], NULL, 16);
                con_addr.addr[4] = (uint8_t)console_cmd_strtoul(argv[6], NULL, 16);
                con_addr.addr[5] = (uint8_t)console_cmd_strtoul(argv[7], NULL, 16);
                app_hfg_set_def_device(con_addr);
                app_hfg_connect_def_device();
            }
            break;
        case 1:
            app_hfg_connect_sco();
            break;
        case 2:
            app_hfg_disconnect_sco();
            break;
        default:
            break;
    }

    return ERR_NONE;
}
#endif

static int app_user_sleep(int argc, char * const argv[])
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

static int app_sleep_level(int argc, char * const argv[])
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

static int app_user_wakeup_source(int argc, char * const argv[])
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

static int app_user_set_pass_key(int argc, char * const argv[])
{
    char * passkey;
    uint8_t passkey_len = 0;

    if (argc > 2) {
        return ERR_WRONG_ARGS;
    }

    passkey = argv[1];
    dbg("%s,%s\n",__func__,passkey);
    passkey_len = strlen(passkey);
    dbg("passkey_len %d\n",passkey_len);

    if(passkey_len>0){
        app_bt_set_pass_key(passkey,passkey_len);
    }else{
        return ERR_WRONG_ARGS;
    }
    return ERR_NONE;
}

static int app_change_loacl_name(int argc, char * const argv[])
{
    char * local_name;
    uint8_t local_name_len = 0;

    if (argc > 2) {
        return ERR_WRONG_ARGS;
    }

    local_name = argv[1];
    dbg("%s,%s\n",__func__,local_name);
    local_name_len = strlen(local_name);
    dbg("local_name_len %d\n",local_name_len);

    if(local_name_len>0){
        app_bt_change_local_name(local_name,local_name_len+1);
    }else{
        return ERR_WRONG_ARGS;
    }
    return ERR_NONE;
}
#if MAX_THROUGHPUT_TEST == 1
static int app_spp_connect_device(int argc, char * const argv[])
{
    uint8_t conidx;
    BT_ADDR addr;

    if (argc > 8) {
        return ERR_WRONG_ARGS;
    }

    conidx = console_cmd_strtoul(argv[1], NULL, 16);
    addr.addr[0] = console_cmd_strtoul(argv[2], NULL, 16);
    addr.addr[1] = console_cmd_strtoul(argv[3], NULL, 16);
    addr.addr[2] = console_cmd_strtoul(argv[4], NULL, 16);
    addr.addr[3] = console_cmd_strtoul(argv[5], NULL, 16);
    addr.addr[4] = console_cmd_strtoul(argv[6], NULL, 16);
    addr.addr[5] = console_cmd_strtoul(argv[7], NULL, 16);

    dbg("%s: %02x:%02x:%02x:%02x:%02x:%02x\n",__func__,addr.addr[0],addr.addr[1],addr.addr[2],addr.addr[3],addr.addr[4],addr.addr[5]);

    app_spp_connect(conidx, &addr);
    return ERR_NONE;
}

static int app_spp_throughput_start(int argc, char * const argv[])
{
    unsigned int on_off;
    uint8_t local_name_len = 0;

    if (argc > 2) {
        return ERR_WRONG_ARGS;
    }

    on_off = console_cmd_strtoul(argv[1], NULL, 10);
    dbg("%s,on_off = %d\n",__func__,on_off);

    if(on_off){
        app_spp_register_tx_done(app_spp_send_test_data);
        app_bt_spp_throughput_start();
    }else{
        app_spp_register_tx_done(NULL);
    }
    return ERR_NONE;
}
#endif
void app_console_command_add(void)
{
#if APP_SUPPORT_TWS == 1
    console_cmd_add("tws_sync", "tws_sync_control <on/off>", 2, 2, app_tws_sync_control);
    console_cmd_add("tws_mss", "tws_mss", 1, 1, app_tws_mss_control);
    console_cmd_add("tws_stop", "tws_stop", 1, 1, app_tws_stop_local_sync_control);
    console_cmd_add("tws_reset", "tws_reset", 1, 1, app_tws_reset);
    console_cmd_add("tws_disc", "tws_disc", 1, 1, app_tws_disc);
    console_cmd_add("tws_vr", "tws_vr  :tws_visible_reopen", 1, 1, app_tws_visible_reopen);
#endif
    console_cmd_add("key", "key <value>  :app key enter", 2, 2, app_key_enter);
#if FPGA == 0
    console_cmd_add("erased", "erased  :erased flash", 1, 1, app_erase_flash);
#endif
    console_cmd_add("dut", "dut  :enter dut", 1, 1, app_enable_dut);
    console_cmd_add("non_signaling_test", "non_signaling_test  :enter non_signaling_test", 1, 1, app_enable_non_signaling_test);
    console_cmd_add("bt_trace", "bt_trace <on/off> <level>", 3, 3, app_onoff_bt_trace);
    console_cmd_add("scan_en", "scan_en <scan_type> <is_dut>", 3, 3, app_scan_en);
    console_cmd_add("inquiry", "inquiry <len> <maxResp>", 3, 3, app_inquiry_dev);
    console_cmd_add("inquiry_cancel", "inquiry_cancel", 1, 1, app_inquiry_cancel);
    console_cmd_add("bt_disc", "bt_disc", 1, 1, app_disc_all_link);
#if APP_SUPPORT_A2DP_SOURCE == 1
    console_cmd_add("source_control", "source_control <value>", 2, 2, app_a2dp_source_control);
#endif
#if APP_SUPPORT_HFG == 1
    console_cmd_add("hfg_control", "hfg_control <value>:0:connect 1:sco connect 2:sco disconnect\n    eg:hfg_control 0 xx xx xx xx xx xx\n",\
                    2, 8, app_hfg_control);
#endif
    console_cmd_add("bt_usrslp", "bt_usrslp <of/off>  :Allow user sleep", 2, 2, app_user_sleep);
    console_cmd_add("bt_slplvl", "bt_slplvl <sleep_level>  :Set system sleep level", 2, 2, app_sleep_level);
    console_cmd_add("bt_usrwusrc", "bt_usrwusrc <src> <en> <arg>  :Set user wakeup source", 3, 4, app_user_wakeup_source);
#if APP_SUPPORT_OTA_BOX
    console_cmd_add("bt_otac", "bt_otac <addr[0]> <addr[1]> <addr[2]> <addr[3]> <addr[4]> <addr[5]>  :ota connect by bt addr", 7, 7, app_ota_connect);
    console_cmd_add("bt_otac_id", "bt_otac_id <addr_list_id>  :ota connect by id", 2, 2, app_ota_connect_by_id);
#endif
    console_cmd_add("bt_passkey", "bt_passkey xxxxxx  : xxxxxx is the passkey print in phone", 2, 2, app_user_set_pass_key);
    console_cmd_add("bt_local_name", "bt_local_name xxxxxx  : xxxxxx is the name string", 2, 2, app_change_loacl_name);
#if MAX_THROUGHPUT_TEST == 1
    console_cmd_add("bt_spp_connect", "bt_spp_connect <conidx> <addr> ", 8, 8, app_spp_connect_device);
    console_cmd_add("bt_spp_tp_start", "bt_spp_tp_start 1/0 ", 2, 2, app_spp_throughput_start);
#endif
}
#endif
#endif
#endif
