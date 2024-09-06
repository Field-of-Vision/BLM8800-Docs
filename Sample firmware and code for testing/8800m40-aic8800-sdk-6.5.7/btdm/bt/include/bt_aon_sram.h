/**
 ****************************************************************************************
 *
 * @file bt_aon_sram.h
 *
 * @brief Header file for always-on bt_aon
 *
 * Copyright (C) RivieraWaves 2017-2048
 *
 ****************************************************************************************
 */
#ifndef __BT_AON_SRAM_H__
#define  __BT_AON_SRAM_H__
#include "tgt_cfg_bt.h"
#include "bt_types_def.h"

enum host_deepsleep_status {
    // CPU need powerdown
    POWER_ALIVE  = 0,
    // CPU no need powerdown
    POWER_DOWN = 1,
};

#if (PLF_AIC8800)
#if PLF_AON_SUPPORT == 1

enum host_aon_sram_id {
    HOST_AON_ID_BT,
#if PLF_BLE_ONLY == 0
    HOST_AON_ID_CMGR,
    HOST_AON_ID_AVDEV,
    HOST_AON_ID_A2DP,
    HOST_AON_ID_AVRCP,
    HOST_AON_ID_AVCTP,
    HOST_AON_ID_HF,
    HOST_AON_ID_AVDTP,
    HOST_AON_ID_APP_BT_DEVICE,
    HOST_AON_ID_TWS,
    HOST_AON_ID_HOST_STATIC,
#endif
#if PLF_BLE_STACK
    //HOST_AON_ID_BLE_PARAM,
    HOST_AON_ID_BLE_KE_TASK_ENV,
    HOST_AON_ID_BLE_KE_ENV,
    //HOST_AON_ID_BLE_APP_ENV,
    HOST_AON_ID_BLE_KE_EVENT,
    HOST_AON_ID_BLE_GAPM,
    //HOST_AON_ID_BLE_PRF_ENV,
    HOST_AON_ID_BLE_GATTM,
    HOST_AON_ID_BLE_L2CM,
#endif
    HOST_AON_ID_NUM,
};

enum app_aon_sram_id {
    APP_AON_ID_APP_STATIC,
    APP_AON_ID_NUM,
};

//extern HOST_AON_STRUCT *host_aon;
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
extern void pm_bt_save(void);
extern void pm_bt_restore(void);

#if PLF_BLE_ONLY == 0
extern void pm_cmgr_save(void);
extern void pm_cmgr_restore(void);

extern void pm_avdev_save(void);
extern void pm_avdev_restore(void);

extern void pm_a2dp_save(void);
extern void pm_a2dp_restore(void);

extern void pm_avrcp_save(void);
extern void pm_avrcp_restore(void);

extern void pm_avctp_save(void);
extern void pm_avctp_restore(void);

extern void pm_hf_save(void);
extern void pm_hf_restore(void);

extern void pm_avdtp_save(void);
extern void pm_avdtp_restore(void);

extern void pm_app_bt_dev_t_save(void);
extern void pm_app_bt_dev_t_restore(void);

extern void pm_tws_save(void);
extern void pm_tws_restore(void);

extern void pm_host_static_save(void);
extern void pm_host_static_restore(void);
#endif

extern void pm_app_static_save(void *aon_app_static);
extern void pm_app_static_restore(void *aon_app_static);

#if PLF_BLE_STACK
extern void pm_ble_ke_task_env_save(void);
extern void pm_ble_ke_task_env_restore(void);

extern void pm_ble_ke_env_save(void);
extern void pm_ble_ke_env_restore(void);

extern void pm_ble_ke_event_env_save(void);
extern void pm_ble_ke_event_env_restore(void);

extern void pm_ble_gapm_env_save(void);
extern void pm_ble_gapm_env_restore(void);

extern void pm_ble_gattm_env_save(void);
extern void pm_ble_gattm_env_restore(void);

extern void pm_ble_l2cm_env_save(void);
extern void pm_ble_l2cm_env_restore(void);
#endif

void host_aon_sram_hi_mux_to_cpu_sys(void);
void host_aon_sram_hi_mux_to_aon(void);
void host_aon_sram_init(void);
void host_aon_sram_save(enum host_aon_sram_id id);
void host_aon_sram_restore(enum host_aon_sram_id id);
void host_aon_sram_save_all(void);
bool host_aon_sram_restore_all(void);
uint32_t host_power_on_mode(void);
void host_aon_deepsleep_status_set(enum host_deepsleep_status mode);
enum host_deepsleep_status host_aon_deepsleep_status_get(void);
bool aon_sram_hi_using_by_aon_get(void);
void cpup_ready_set(bool ready);
void aon_power_on_cpup_set(bool power_on);
bool aon_power_on_cpup_get(void);
void aon_power_on_cpus_req_set(bool power_on);
bool aon_power_on_cpus_req_get(void);
void host_aon_interface_init(void);

#endif
#elif (PLF_AIC8800MC) || (PLF_AIC8800M40)
void host_aon_deepsleep_status_set(enum host_deepsleep_status mode);
#endif
#endif
