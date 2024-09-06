/**
 ****************************************************************************************
 *
 * @file app_smartconfig.c
 *
 * @brief Smartconfig Application entry point
 *
 * Copyright (C) AIC
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APP
 * @{
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW configuration

#if (BLE_APP_SMARTCONFIG)

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app.h"
#include "app_task.h"
#include "app_smartconfig.h"
#include "smartconfig_task.h"
#include "co_bt.h"
#include "prf_types.h"
#include "prf_utils.h"
#include "arch.h"
#include "prf.h"
#include "string.h"
#include "ble_utils.h"

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
#define BLE_SMARTCONFIG_TEST                    (0)
static struct app_smartconfig_env_tag app_smartconfig_env;

static app_smartconfig_recv_ap_info_cb recv_ap_info_callback = NULL;
static app_smartconfig_recv_state_info_cb recv_state_info_callback = NULL;

struct ble_smartconfig_wifi_state {
    char state[DATA_BUF_SIZE];
    uint8_t len;
};

static struct ble_smartconfig_wifi_state wifi_state;

#if BLE_SMARTCONFIG_TEST
static struct ble_smartconfig smartconfig_result;

#define APP_RSP            ("successful")
#define APP_RSP_LEN        (sizeof(APP_RSP))

int app_smartconfig_ap_info_received(uint8_t* data, uint32_t length)
{
    int i = 0;
    uint8_t index = 0;
    dbg("%s recv ap info %d\r\n", __func__, length);
    for (i = 0; i < length; i++) {
        if((i%8 == 0))
            dbg("  ");
        dbg("%02x ", data[i]);
        if((i+1)%16 == 0)
        dbg("\n");
    }
    dbg("\n");

    for (i = 0; i < length; i++) {
        if (data[i] == '\n') {
            memcpy(&smartconfig_result.ssid[0], &data[0], i);
            index = i + 1;
            break;
        }
    }

    for (i = index; i < length; i++) {
            memcpy(&smartconfig_result.pwd[0], &data[index], length - index);
    }

    dbg("ssid %s\r\n", smartconfig_result.ssid);
    dbg("pwd %s\r\n", smartconfig_result.pwd);
    memcpy(&wifi_state.state[0], APP_RSP, APP_RSP_LEN);
    wifi_state.len = APP_RSP_LEN;
    return NO_ERROR;
}
#endif

int app_smartconfig_time_info_received(uint8_t* data, uint32_t length)
{
    if (recv_state_info_callback) {
        recv_state_info_callback(data, length);
    }
    return NO_ERROR;
}

void app_smartconfig_init(void)
{
    dbg("%s\n", __func__);
    memset(&app_smartconfig_env, 0, sizeof(app_smartconfig_env));
    memset(&wifi_state, 0, sizeof(wifi_state));
    //recv_ap_info_callback = NULL;
    //recv_state_info_callback = NULL;
}

void app_smartconfig_add_smartconfig(void)
{
    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,
                                                  TASK_GAPM, TASK_APP,
                                                  gapm_profile_task_add_cmd, 0);

    // Fill message
    req->operation = GAPM_PROFILE_TASK_ADD;
    #if 0
    req->sec_lvl = PERM(SVC_AUTH, ENABLE);
    #else
    req->sec_lvl     = PERM(SVC_AUTH, NO_AUTH);
    #endif
    req->prf_task_id = TASK_ID_SMARTCONFIG;
    req->app_task = TASK_APP;
    req->start_hdl = 0;

    // Send the message
    ke_msg_send(req);
}

void app_smartconfig_enable_prf(uint8_t conidx)
{
    app_smartconfig_env.conidx = conidx;
}

void app_smartconfig_disconnected(void)
{
    dbg("%s\n", __func__);
    app_smartconfig_env.conidx = INVALID_CONNECTION_INDEX;
    app_smartconfig_env.wifi_state_ntf_en = false;
    app_smartconfig_env.time_state_ntf_en = false;
    recv_ap_info_callback = NULL;
    recv_state_info_callback = NULL;
}

void app_smartconfig_register_ap_info_cb(app_smartconfig_recv_ap_info_cb callback)
{
    recv_ap_info_callback = callback;
}

void app_smartconfig_register_state_info_cb(app_smartconfig_recv_state_info_cb callback)
{
    recv_state_info_callback = callback;
}

void app_smartconfig_send_wifi_state_notification(uint8_t* data, uint32_t length)
{
    dbg("%s %d\r\n", __func__, length);
    struct ble_smartconfig_send_data_req * req = KE_MSG_ALLOC_DYN(SMARTCONFIG_SEND_WIFI_STATE_NOTIFICATION,
                                                prf_get_task_from_id(TASK_ID_SMARTCONFIG),
                                                TASK_APP,
                                                ble_smartconfig_send_data_req,
                                                length);
    req->conidx = app_smartconfig_env.conidx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_smartconfig_send_wifi_state_indication(uint8_t* data, uint32_t length)
{

    struct ble_smartconfig_send_data_req * req = KE_MSG_ALLOC_DYN(SMARTCONFIG_SEND_WIFI_STATE_INDICATION,
                                                prf_get_task_from_id(TASK_ID_SMARTCONFIG),
                                                TASK_APP,
                                                ble_smartconfig_send_data_req,
                                                length);
    req->conidx = app_smartconfig_env.conidx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_smartconfig_send_time_state_notification(uint8_t* data, uint32_t length)
{
    struct ble_smartconfig_send_data_req * req = KE_MSG_ALLOC_DYN(SMARTCONFIG_SEND_TIME_STATE_NOTIFICATION,
                                                prf_get_task_from_id(TASK_ID_SMARTCONFIG),
                                                TASK_APP,
                                                ble_smartconfig_send_data_req,
                                                length);
    req->conidx = app_smartconfig_env.conidx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_smartconfig_send_time_state_indication(uint8_t* data, uint32_t length)
{
    struct ble_smartconfig_send_data_req * req = KE_MSG_ALLOC_DYN(SMARTCONFIG_SEND_TIME_STATE_INDICATION,
                                                prf_get_task_from_id(TASK_ID_SMARTCONFIG),
                                                TASK_APP,
                                                ble_smartconfig_send_data_req,
                                                length);
    req->conidx = app_smartconfig_env.conidx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */

static int app_smartconfig_wifi_state_service_changed_handler(ke_msg_id_t const msgid,
                              struct ble_smartconfig_notif_config *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    app_smartconfig_env.wifi_state_ntf_en = param->ntf_en;
    if (wifi_state.len) {
        app_smartconfig_send_wifi_state_notification((uint8_t *)&wifi_state.state[0], wifi_state.len);
    }

    return (KE_MSG_CONSUMED);
}

static int app_smartconfig_time_state_service_changed_handler(ke_msg_id_t const msgid,
                              struct ble_smartconfig_notif_config *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    app_smartconfig_env.time_state_ntf_en = param->ntf_en;
    return (KE_MSG_CONSUMED);
}

static int app_smartconfig_time_state_sent_handler(ke_msg_id_t const msgid,
                              struct ble_smartconfig_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    return (KE_MSG_CONSUMED);
}

static int app_smartconfig_ap_info_received_handler(ke_msg_id_t const msgid,
                              struct ble_smartconfig_rx_data_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
#if BLE_SMARTCONFIG_TEST
    app_smartconfig_ap_info_received(param->data, param->length);
#endif //(BLE_SMARTCONFIG_TEST)
    if (recv_ap_info_callback != NULL)
    {
        recv_ap_info_callback(param->data, param->length);
    }
    return (KE_MSG_CONSUMED);
}

static int app_smartconfig_time_info_received_handler(ke_msg_id_t const msgid,
                              struct ble_smartconfig_rx_data_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    app_smartconfig_time_info_received(param->data, param->length);
    return (KE_MSG_CONSUMED);
}


static int app_smartconfig_dflt_msg_handler(ke_msg_id_t const msgid,
                              void const *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    // Do nothing
    return (KE_MSG_CONSUMED);
}

void app_smartconfig_send_rsp(uint8_t* data, uint32_t length)
{
    memset(&wifi_state, 0, sizeof(wifi_state));
    if (app_smartconfig_env.wifi_state_ntf_en) {
        app_smartconfig_send_wifi_state_notification(data, length);
    } else {
        wifi_state.len = length;
        memcpy(&wifi_state.state[0], data, length);
    }
}

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler app_smartconfig_msg_handler_list[] =
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,                    (ke_msg_func_t)app_smartconfig_dflt_msg_handler},

    {SMARTCONFIG_WIFI_STATE_SERVICE_CHANGED,    (ke_msg_func_t)app_smartconfig_wifi_state_service_changed_handler},
    {SMARTCONFIG_TIME_STATE_SERVICE_CHANGED,    (ke_msg_func_t)app_smartconfig_time_state_service_changed_handler},
    {SMARTCONFIG_TIME_STATE_SENT,               (ke_msg_func_t)app_smartconfig_time_state_sent_handler},
    {SMARTCONFIG_AP_INFO_RECEIVED,              (ke_msg_func_t)app_smartconfig_ap_info_received_handler},
    {SMARTCONFIG_TIME_INFO_RECEIVED,            (ke_msg_func_t)app_smartconfig_time_info_received_handler},
};

const struct app_subtask_handlers app_smartconfig_handlers = APP_HANDLERS(app_smartconfig);

#endif //BLE_APP_SMARTCONFIG

/// @} APP
