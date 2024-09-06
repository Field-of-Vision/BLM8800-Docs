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

#if (BLE_APP_AUDTRANSMITC)

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app.h"
#include "app_task.h"
#include "app_audtransmitc.h"
#include "audtransmitc_task.h"
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
static struct app_audtransmitc_env_tag app_audtransmitc_env;

static app_audtransmitc_recv_aud_info_cb recv_aud_info_callback = NULL;
static app_audtransmitc_recv_aud_data_cb recv_aud_data_callback = NULL;

void app_audtransmitc_init(void)
{
    //uint8_t peer_ble_addr[6] = {
    //    0xff,0xff,0xff,0xff,0xff,0xff
    //};

    TRACE("BLE: %s\n", __func__);
    memset(&app_audtransmitc_env, 0, sizeof(app_audtransmitc_env));
    //app_ble_peer_addr_init(peer_ble_addr,ADDR_PUBLIC);
}

void app_audtransmit_add_audtransmitc(void)
{
    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,
                                                  TASK_GAPM, TASK_APP,
                                                  gapm_profile_task_add_cmd, 0);

    // Fill message
    req->operation = GAPM_PROFILE_TASK_ADD;
    #if 0
    req->sec_lvl = PERM(SVC_AUTH, ENABLE);
    #else
    req->sec_lvl     = PERM(SVC_AUTH, NO_AUTH)|PERM(SVC_MI, ENABLE);
    #endif
    req->prf_task_id = TASK_ID_AUDTRANSMITC;
    req->app_task = TASK_APP;
    req->start_hdl = 0;
    TRACE("BLE: %s  ,sec_lvl = 0x%x\n", __func__,req->sec_lvl);
    // Send the message
    ke_msg_send(req);
}

void app_audtransmitc_enable_prf(uint8_t conidx)
{
    TRACE("BLE: %s,%x\n", __func__,conidx);

    app_audtransmitc_env.conidx = conidx;
    // Allocate the message
    struct audtransmitc_enable_req * req = KE_MSG_ALLOC(AUDTRANSMITC_ENABLE_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_AUDTRANSMITC), conidx),
                                                KE_BUILD_ID(TASK_APP,conidx),
                                                audtransmitc_enable_req);

    req->con_type = PRF_CON_DISCOVERY;
    // Send the message
    ke_msg_send(req);
}

void app_audtransmitc_disconnected(void)
{
    TRACE("BLE: %s\n", __func__);
    app_audtransmitc_env.conidx = INVALID_CONNECTION_INDEX;
    app_audtransmitc_env.client_aud_status.codec_type = 0;
    app_audtransmitc_env.client_aud_status.state = C_STATE_IDLE;
}

void app_audtransmitc_register_aud_info_cb(app_audtransmitc_recv_aud_info_cb callback)
{
    recv_aud_info_callback = callback;
    TRACE("BLE: %s 0x%x\n", __func__,recv_aud_info_callback);
}

void app_audtransmitc_register_aud_data_cb(app_audtransmitc_recv_aud_data_cb callback)
{
    recv_aud_data_callback = callback;
    TRACE("BLE: %s 0x%x\n", __func__,recv_aud_data_callback);
}

void app_audtransmitc_aud_ctrl_wr_req(uint8_t* data, uint32_t length)
{
    dbg("%s %d\r\n", __func__, length);
    struct audtransmitc_send_data_req * req = KE_MSG_ALLOC_DYN(AUDTRANSMITC_AUD_CTRL_WR_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_AUDTRANSMITC), app_audtransmitc_env.conidx),
                                                TASK_APP,
                                                audtransmitc_send_data_req,
                                                length);
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_audtransmitc_aud_data_wr_req(uint8_t* data, uint32_t length)
{

    struct audtransmitc_send_data_req * req = KE_MSG_ALLOC_DYN(AUDTRANSMITC_AUD_DATA_WR_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_AUDTRANSMITC), app_audtransmitc_env.conidx),
                                                TASK_APP,
                                                audtransmitc_send_data_req,
                                                length);
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_audtransmitc_aud_info_ntf_cfg_req(bool ntf_en)
{
    struct audtransmitc_notif_config * req = KE_MSG_ALLOC(AUDTRANSMITC_AUD_INFO_NTF_CFG_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_AUDTRANSMITC), app_audtransmitc_env.conidx),
                                                KE_BUILD_ID(TASK_APP,app_audtransmitc_env.conidx),
                                                audtransmitc_notif_config);
    req->ntf_en = ntf_en;

    ke_msg_send(req);
}

void app_audtransmitc_aud_data_ntf_cfg_req(bool ntf_en)
{
    struct audtransmitc_notif_config * req = KE_MSG_ALLOC(AUDTRANSMITC_AUD_DATA_NTF_CFG_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_AUDTRANSMITC), app_audtransmitc_env.conidx),
                                                KE_BUILD_ID(TASK_APP,app_audtransmitc_env.conidx),
                                                audtransmitc_notif_config);
    req->ntf_en = ntf_en;

    ke_msg_send(req);
}

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */

static int app_audtransmitc_enable_rsp_handler(ke_msg_id_t const msgid,
                              struct audtransmitc_enable_rsp *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s ,%x\n", __func__,param->status);
    return (KE_MSG_CONSUMED);
}

static int app_audtransmitc_reg_ntf_done_handler(ke_msg_id_t const msgid,
                              struct audtransmitc_enable_rsp *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s ,%x\n", __func__,param->status);
    app_audtransmitc_aud_info_ntf_cfg_req(true);
    app_audtransmitc_aud_data_ntf_cfg_req(true);
    return (KE_MSG_CONSUMED);
}

static int app_audtransmitc_aud_ctrl_wr_rsp_handler(ke_msg_id_t const msgid,
                              struct audtransmitc_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s ,%x\n", __func__,param->status);
    return (KE_MSG_CONSUMED);
}

static int app_audtransmitc_aud_data_wr_rsp_handler(ke_msg_id_t const msgid,
                              struct audtransmitc_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s ,%x\n", __func__,param->status);
    return (KE_MSG_CONSUMED);
}

static int app_audtransmitc_aud_info_ntf_cfg_rsp_handler(ke_msg_id_t const msgid,
                              struct audtransmitc_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s ,%x\n", __func__,param->status);
    return (KE_MSG_CONSUMED);
}

static int app_audtransmitc_aud_data_ntf_cfg_rsp_handler(ke_msg_id_t const msgid,
                              struct audtransmitc_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s ,%x\n", __func__,param->status);
    return (KE_MSG_CONSUMED);
}

static int app_audtransmitc_aud_info_ind_handler(ke_msg_id_t const msgid,
                              struct audtransmitc_rx_data_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    TRACE("%s ,len %d,0x%x\n", __func__,param->length,recv_aud_info_callback);
    if (recv_aud_info_callback != NULL) {
        recv_aud_info_callback(param->data, param->length);
    }
    return (KE_MSG_CONSUMED);
}

static int app_audtransmitc_aud_data_ind_handler(ke_msg_id_t const msgid,
                              struct audtransmitc_rx_data_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    //TRACE("%s ,len %d,0x%x\n", __func__,param->length,recv_aud_data_callback);
    if (recv_aud_data_callback != NULL) {
        recv_aud_data_callback(param->data, param->length);
    }
    return (KE_MSG_CONSUMED);
}


static int app_audtransmitc_dflt_msg_handler(ke_msg_id_t const msgid,
                              void const *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    // Do nothing
    return (KE_MSG_CONSUMED);
}

void app_audtransmitc_set_status(uint16_t codec_type,uint8_t state)
{
    app_audtransmitc_env.client_aud_status.codec_type = codec_type;
    app_audtransmitc_env.client_aud_status.state = state;
    TRACE("%s ,codec_type %x ,state %x\n",__func__,codec_type,state);
}
/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler app_audtransmitc_msg_handler_list[] =
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,                    (ke_msg_func_t)app_audtransmitc_dflt_msg_handler},

    {AUDTRANSMITC_ENABLE_RSP,                   (ke_msg_func_t)app_audtransmitc_enable_rsp_handler},
    {AUDTRANSMITC_REG_NTF_PROCESS_DONE,         (ke_msg_func_t)app_audtransmitc_reg_ntf_done_handler},
    {AUDTRANSMITC_AUD_CTRL_WR_RSP,              (ke_msg_func_t)app_audtransmitc_aud_ctrl_wr_rsp_handler},
    {AUDTRANSMITC_AUD_DATA_WR_RSP,              (ke_msg_func_t)app_audtransmitc_aud_data_wr_rsp_handler},
    {AUDTRANSMITC_AUD_INFO_NTF_CFG_RSP,         (ke_msg_func_t)app_audtransmitc_aud_info_ntf_cfg_rsp_handler},
    {AUDTRANSMITC_AUD_DATA_NTF_CFG_RSP,         (ke_msg_func_t)app_audtransmitc_aud_data_ntf_cfg_rsp_handler},
    {AUDTRANSMITC_AUD_INFO_IND,                 (ke_msg_func_t)app_audtransmitc_aud_info_ind_handler},
    {AUDTRANSMITC_AUD_DATA_IND,                 (ke_msg_func_t)app_audtransmitc_aud_data_ind_handler},
};

const struct app_subtask_handlers app_audtransmitc_handlers = APP_HANDLERS(app_audtransmitc);

#endif //BLE_APP_SMARTCONFIG

/// @} APP
