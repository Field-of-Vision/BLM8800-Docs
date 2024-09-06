/**
 ****************************************************************************************
 *
 * @file aon_sram.h
 *
 * @brief Header file for always-on aon_sram module
 *
 * Copyright (C) RivieraWaves 2017-2018
 *
 ****************************************************************************************
 */

#ifndef __AON_SRAM_H__
#define  __AON_SRAM_H__
#include "tgt_cfg_bt.h"
#if PLF_AON_SUPPORT == 1
#include "rtos.h"
#include <stdint.h>
#include <string.h>
#if PLF_BLE_ONLY == 0
#include "aic_adp_api.h"
#include "app_a2dp.h"
#include "app_hfp.h"
#include "app_bt.h"
#include "bt_task_msg.h"

#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1 || APP_SUPPORT_A2DP_SOURCE == 1
extern app_a2dp_state_t t_a2dp_state;
#endif
#if APP_SUPPORT_HFP == 1
extern app_hfp_state_t s_hfp_state;
extern uint16_t  s_hfp_scocodec;
#endif
extern APP_BT_HANDLER handler_register_list[HANDLER_REG_MAX];
extern app_connect_manager app_bt_connect_struct[LINK_MAX];
extern app_connect_manager *app_con_ptr[LINK_MAX];
extern app_bt_state_t s_bt_state;
extern AppBtScanMode bt_scan_mode;

#if APP_SUPPORT_AES == 1
extern U32 secret_key[8];
#endif
extern U32 aic_host_log ;

typedef struct{
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1 || APP_SUPPORT_A2DP_SOURCE == 1
    app_a2dp_state_t t_a2dp_state;
#endif
#if APP_SUPPORT_HFP == 1
    app_hfp_state_t s_hfp_state;
    uint16_t s_hfp_scocodec;
#endif
    app_bt_state_t s_bt_state;
    AppBtScanMode bt_scan_mode;
    APP_BT_HANDLER handler_register_list[HANDLER_REG_MAX];
    app_connect_manager app_bt_connect_struct[LINK_MAX];
    app_connect_manager *app_con_ptr[LINK_MAX];
    U32 aic_host_log;
#if APP_SUPPORT_AES == 1
    U32 secret_key[8];
#endif
}AppBtStatic;
#endif

#if PLF_BLE_STACK == 1
#include "app.h"
#include "prf.h"
#include "ke_mem.h"
#if BLE_APP_HID
#include "prf_utils.h"
#include "bass.h"
#include "hogpd.h"
#endif
#if BLE_APP_SMARTCONFIG
#include "smartconfig.h"
#endif

extern uint8_t ble_enabled;

typedef struct
{
    struct prf_env_tag prf_env;
#if BLE_APP_HID
    struct bass_env_tag bass_env;
    struct hogpd_env_tag hogpd_env;
#endif
#if BLE_APP_SMARTCONFIG
    struct smartconfig_env_tag smartconfig_env;
#endif
}AppBlePrfEnv;

extern struct app_env_tag app_env;
extern struct ble_app_user_info aon_ble_app_user_info;
typedef struct{
    uint8_t aon_ble_enabled;
    AonBleAppEnv aon_ble_app_env;
    AonBleAppUserInfo aon_ble_app_user_info;
}AppBleStatic;
#endif

extern uint8_t bt_lp_level;
extern uint8_t bt_power_state;

typedef struct{
#if PLF_BLE_ONLY == 0
    AppBtStatic btstatic;
#endif
#if PLF_BLE_STACK == 1
    AppBleStatic blestatic;
    AppBlePrfEnv ble_prf_env;
#endif
    uint8_t bt_lp_level;
    uint8_t bt_power_state;
}AppStatic;

typedef struct
{
    uint32_t len;
    uint8_t app_static[__ARRAY_EMPTY];
}AonAppStatic;


#endif
#endif
