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

#if (BLE_APP_AUDTRANSMITS)

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app.h"
#include "app_task.h"
#include "app_audtransmits.h"
#include "audtransmits_task.h"
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
static struct app_audtransmits_env_tag app_audtransmits_env;

static app_audtransmits_sent_aud_info_cb sent_aud_info_callback = NULL;
static app_audtransmits_sent_aud_data_cb sent_aud_data_callback = NULL;

static app_audtransmits_recv_aud_ctrl_cb recv_aud_ctrl_callback = NULL;
static app_audtransmits_recv_aud_data_cb recv_aud_data_callback = NULL;
static struct audtransmits_state server_aud_status;

void app_audtransmits_init(void)
{
    TRACE("BLE: %s\n", __func__);
    memset(&app_audtransmits_env, 0, sizeof(app_audtransmits_env));
}

void app_audtransmit_add_audtransmits(void)
{
    TRACE("BLE: %s\n", __func__);
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
    req->prf_task_id = TASK_ID_AUDTRANSMITS;
    req->app_task = TASK_APP;
    req->start_hdl = 0;

    // Send the message
    ke_msg_send(req);
}

void app_audtransmits_enable_prf(uint8_t conidx)
{
    app_audtransmits_env.conidx = conidx;
}

void app_audtransmits_disconnected(void)
{
    TRACE("BLE: %s\n", __func__);
    app_audtransmits_env.conidx = INVALID_CONNECTION_INDEX;
    app_audtransmits_env.aud_info_ntf_en = false;
    app_audtransmits_env.aud_data_ntf_en = false;
}

void app_audtransmits_register_aud_info_sent_cb(app_audtransmits_sent_aud_info_cb callback)
{
    sent_aud_info_callback = callback;
}

void app_audtransmits_register_aud_data_sent_cb(app_audtransmits_sent_aud_data_cb callback)
{
    sent_aud_data_callback = callback;
}

void app_audtransmits_register_aud_ctrl_recv_cb(app_audtransmits_recv_aud_ctrl_cb callback)
{
    recv_aud_ctrl_callback = callback;
}

void app_audtransmits_register_aud_data_recv_cb(app_audtransmits_recv_aud_data_cb callback)
{
    recv_aud_data_callback = callback;
}

void app_audtransmits_send_aud_info_notification(uint8_t* data, uint32_t length)
{
    dbg("%s %d\r\n", __func__, length);
    struct audtransmits_send_data_req * req = KE_MSG_ALLOC_DYN(AUDTRANSMITS_SEND_AUD_INFO_NOTIFICATION,
                                                prf_get_task_from_id(TASK_ID_AUDTRANSMITS),
                                                TASK_APP,
                                                audtransmits_send_data_req,
                                                length);
    req->conidx = app_audtransmits_env.conidx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_audtransmits_send_aud_info_indication(uint8_t* data, uint32_t length)
{

    struct audtransmits_send_data_req * req = KE_MSG_ALLOC_DYN(AUDTRANSMITS_SEND_AUD_INFO_INDICATION,
                                                prf_get_task_from_id(TASK_ID_AUDTRANSMITS),
                                                TASK_APP,
                                                audtransmits_send_data_req,
                                                length);
    req->conidx = app_audtransmits_env.conidx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_audtransmits_send_aud_data_notification(uint8_t* data, uint32_t length)
{
    struct audtransmits_send_data_req * req = KE_MSG_ALLOC_DYN(AUDTRANSMITS_SEND_AUD_DATA_NOTIFICATION,
                                                prf_get_task_from_id(TASK_ID_AUDTRANSMITS),
                                                TASK_APP,
                                                audtransmits_send_data_req,
                                                length);
    req->conidx = app_audtransmits_env.conidx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_audtransmits_send_aud_data_indication(uint8_t* data, uint32_t length)
{
    struct audtransmits_send_data_req * req = KE_MSG_ALLOC_DYN(AUDTRANSMITS_SEND_AUD_DATA_INDICATION,
                                                prf_get_task_from_id(TASK_ID_AUDTRANSMITS),
                                                TASK_APP,
                                                audtransmits_send_data_req,
                                                length);
    req->conidx = app_audtransmits_env.conidx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */

static int app_audtransmits_aud_info_service_changed_handler(ke_msg_id_t const msgid,
                              struct audtransmits_notif_config *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s ,%x\n", __func__,param->ntf_en);
    app_audtransmits_env.aud_info_ntf_en = param->ntf_en;
    if (server_aud_status.state == S_STATE_PLAY) {
        app_audtransmits_send_aud_info_notification((uint8_t *)&server_aud_status, sizeof(struct audtransmits_state));
    }

    return (KE_MSG_CONSUMED);
}

static int app_audtransmits_data_send_service_changed_handler(ke_msg_id_t const msgid,
                              struct audtransmits_notif_config *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s ,%x\n", __func__,param->ntf_en);
    app_audtransmits_env.aud_data_ntf_en = param->ntf_en;
    appm_set_phy(app_audtransmits_env.conidx);
    appm_set_pkt_len(app_audtransmits_env.conidx);
    app_ble_data_send_start(2,1);
    return (KE_MSG_CONSUMED);
}

static int app_audtransmits_aud_info_sent_handler(ke_msg_id_t const msgid,
                              struct audtransmits_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    if (sent_aud_info_callback != NULL) {
        sent_aud_info_callback(param->status);
    }
    return (KE_MSG_CONSUMED);
}

static int app_audtransmits_aud_data_sent_handler(ke_msg_id_t const msgid,
                              struct audtransmits_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    if (sent_aud_data_callback != NULL) {
        sent_aud_data_callback(param->status);
    }
    return (KE_MSG_CONSUMED);
}

static int app_audtransmits_aud_ctrl_received_handler(ke_msg_id_t const msgid,
                              struct audtransmits_rx_data_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s \n", __func__);
    if (recv_aud_ctrl_callback != NULL) {
        recv_aud_ctrl_callback(param->data, param->length);
    }
    return (KE_MSG_CONSUMED);
}

static int app_audtransmits_aud_data_received_handler(ke_msg_id_t const msgid,
                              struct audtransmits_rx_data_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s \n", __func__);
    if (recv_aud_data_callback != NULL) {
        recv_aud_data_callback(param->data, param->length);
    }
    return (KE_MSG_CONSUMED);
}


static int app_audtransmits_dflt_msg_handler(ke_msg_id_t const msgid,
                              void const *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    // Do nothing
    return (KE_MSG_CONSUMED);
}

void app_audtransmits_send_aud_info(uint8_t* data, uint32_t length)
{
    if (app_audtransmits_env.aud_info_ntf_en) {
        app_audtransmits_send_aud_info_notification(data, length);
    } else {
        TRACE("audtransmits send aud info error\n");
    }
}

void app_audtransmits_send_aud_data(uint8_t* data, uint32_t length)
{
    if (app_audtransmits_env.aud_data_ntf_en) {
        app_audtransmits_send_aud_data_notification(data, length);
    } else {
        TRACE("audtransmits send aud data error\n");
    }
}

void app_audtransmits_set_status(uint16_t codec_type,uint8_t state)
{
    server_aud_status.codec_type = codec_type;
    server_aud_status.state = state;
    TRACE("%s ,codec_type %x ,state %x\n",__func__,codec_type,state);
}
/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler app_audtransmits_msg_handler_list[] =
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,                    (ke_msg_func_t)app_audtransmits_dflt_msg_handler},

    {AUDTRANSMITS_AUD_INFO_SERVICE_CHANGED,     (ke_msg_func_t)app_audtransmits_aud_info_service_changed_handler},
    {AUDTRANSMITS_DATA_SEND_SERVICE_CHANGED,    (ke_msg_func_t)app_audtransmits_data_send_service_changed_handler},
    {AUDTRANSMITS_AUD_INFO_SENT,                (ke_msg_func_t)app_audtransmits_aud_info_sent_handler},
    {AUDTRANSMITS_AUD_DATA_SENT,                (ke_msg_func_t)app_audtransmits_aud_data_sent_handler},
    {AUDTRANSMITS_AUD_CTRL_RECEIVED,            (ke_msg_func_t)app_audtransmits_aud_ctrl_received_handler},
    {AUDTRANSMITS_AUD_DATA_RECEIVED,            (ke_msg_func_t)app_audtransmits_aud_data_received_handler},
};

const struct app_subtask_handlers app_audtransmits_handlers = APP_HANDLERS(app_audtransmits);

#endif //BLE_APP_SMARTCONFIG

/// @} APP
