/**
 ****************************************************************************************
 *
 * @file smartconfig_task.c
 *
 * @brief Smart Config Profile Server Task Implementation.
 *
 * Copyright (C) AIC
 *
 *
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @addtogroup SMARTCONFIGTASK
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_SMARTCONFIG)
#include "gap.h"
#include "gattc_task.h"
#include "gapc_task.h"
#include "attm.h"
#include "smartconfig.h"
#include "smartconfig_task.h"

#include "prf_utils.h"

#include "ke_mem.h"
#include "ble_utils.h"

#define SMARTCONFIG_WIFI_INFO       0
#define SMARTCONFIG_TIME_INFO       1

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATTC_WRITE_REQ_IND message.
 * @param[in] msgid Id of the message received.
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance.
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int gattc_write_req_ind_handler(ke_msg_id_t const msgid,
                                      struct gattc_write_req_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    // Get the address of the environment
    struct smartconfig_env_tag *smartconfig_env = PRF_ENV_GET(SMARTCONFIG, smartconfig);
    uint8_t conidx = KE_IDX_GET(src_id);

    uint8_t status = GAP_ERR_NO_ERROR;

    //Send write response
    struct gattc_write_cfm *cfm = KE_MSG_ALLOC(
            GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm);
    cfm->handle = param->handle;
    cfm->status = status;
    ke_msg_send(cfm);
    TRACE("%s,handle 0x%x\n",__func__,param->handle);

    if (smartconfig_env != NULL)
    {
        if (param->handle == (smartconfig_env->shdl + SMARTCONFIG_IDX_WIFI_STATE_NTF_CFG))
        {
            uint16_t value = 0x0000;

            //Extract value before check
            memcpy(&value, &(param->value), sizeof(uint16_t));

            if (value == PRF_CLI_STOP_NTFIND)
            {
                smartconfig_env->wifi_state_ntf_cfg = false;
            }
            else if ((value == PRF_CLI_START_NTF) ||
                (value == PRF_CLI_START_IND))
            {
                smartconfig_env->wifi_state_ntf_cfg = true;
            }
            else
            {
                status = PRF_APP_ERROR;
            }

            if (status == GAP_ERR_NO_ERROR)
            {
                struct ble_smartconfig_notif_config * ind = KE_MSG_ALLOC(SMARTCONFIG_WIFI_STATE_SERVICE_CHANGED,
                        prf_dst_task_get(&smartconfig_env->prf_env, conidx),
                        prf_src_task_get(&smartconfig_env->prf_env, conidx),
                        ble_smartconfig_notif_config);

                ind->ntf_en = smartconfig_env->wifi_state_ntf_cfg;

                ke_msg_send(ind);
            }
        }
        else if (param->handle == (smartconfig_env->shdl + SMARTCONFIG_IDX_TIME_STATE_NTF_CFG))
        {
            uint16_t value = 0x0000;

            //Extract value before check
            memcpy(&value, &(param->value), sizeof(uint16_t));

            if (value == PRF_CLI_STOP_NTFIND)
            {
                smartconfig_env->time_ntf_cfg = false;
            }
            else if (value == PRF_CLI_START_NTF)
            {
                smartconfig_env->time_ntf_cfg = true;
            }
            else
            {
                status = PRF_APP_ERROR;
            }

            if (status == GAP_ERR_NO_ERROR)
            {
                //Inform APP of TX ccc change
                struct ble_smartconfig_notif_config * ind = KE_MSG_ALLOC(SMARTCONFIG_TIME_STATE_SERVICE_CHANGED,
                        prf_dst_task_get(&smartconfig_env->prf_env, conidx),
                        prf_src_task_get(&smartconfig_env->prf_env, conidx),
                        ble_smartconfig_notif_config);

                ind->ntf_en = smartconfig_env->time_ntf_cfg;

                ke_msg_send(ind);
            }
        }
        else if (param->handle == (smartconfig_env->shdl + SMARTCONFIG_IDX_AP_INFO_VAL))
        {
            //inform APP of data
            struct ble_smartconfig_rx_data_ind * ind = KE_MSG_ALLOC_DYN(SMARTCONFIG_AP_INFO_RECEIVED,
                    prf_dst_task_get(&smartconfig_env->prf_env, conidx),
                    prf_src_task_get(&smartconfig_env->prf_env, conidx),
                    ble_smartconfig_rx_data_ind,
                    sizeof(struct ble_smartconfig_rx_data_ind) + param->length);

            ind->length = param->length;
            memcpy((uint8_t *)(ind->data), &(param->value), param->length);

            ke_msg_send(ind);
        }
        else if (param->handle == (smartconfig_env->shdl + SMARTCONFIG_IDX_TIME_INFO_VAL))
        {
            //inform APP of data
            struct ble_smartconfig_rx_data_ind * ind = KE_MSG_ALLOC_DYN(SMARTCONFIG_TIME_INFO_RECEIVED,
                    prf_dst_task_get(&smartconfig_env->prf_env, conidx),
                    prf_src_task_get(&smartconfig_env->prf_env, conidx),
                    ble_smartconfig_rx_data_ind,
                    sizeof(struct ble_smartconfig_rx_data_ind) + param->length);

            ind->length = param->length;
            memcpy((uint8_t *)(ind->data), &(param->value), param->length);

            ke_msg_send(ind);
        }
        else
        {
            status = PRF_APP_ERROR;
        }
    }

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles @ref GATT_NOTIFY_CMP_EVT message meaning that a notification or an indication
 * has been correctly sent to peer device (but not confirmed by peer device).
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int gattc_cmp_evt_handler(ke_msg_id_t const msgid,  struct gattc_cmp_evt const *param,
                                 ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    // Get the address of the environment
    struct smartconfig_env_tag *smartconfig_env = PRF_ENV_GET(SMARTCONFIG, smartconfig);

    uint8_t conidx = KE_IDX_GET(dest_id);

    // notification or write request has been sent out
    if ((GATTC_NOTIFY == param->operation) || (GATTC_INDICATE == param->operation))
    {

        struct ble_smartconfig_data_sent_ind * ind = KE_MSG_ALLOC(SMARTCONFIG_TIME_STATE_SENT,
                prf_dst_task_get(&smartconfig_env->prf_env, conidx),
                prf_src_task_get(&smartconfig_env->prf_env, conidx),
                ble_smartconfig_data_sent_ind);

        ind->status = param->status;

        ke_msg_send(ind);

    }

    ke_state_set(dest_id, SMARTCONFIG_IDLE);

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATTC_READ_REQ_IND message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int gattc_read_req_ind_handler(ke_msg_id_t const msgid,
                                      struct gattc_read_req_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    // Get the address of the environment
    struct smartconfig_env_tag *smartconfig_env = PRF_ENV_GET(SMARTCONFIG, smartconfig);
    uint8_t att_idx = param->handle - smartconfig_env->shdl;

    uint8_t value_size = 0;
    uint8_t status = ATT_ERR_NO_ERROR;
    uint16_t ntf_cfg;
    uint8_t value[2];
    TRACE("%s,handle 0x%x,att_idx %d\n",__func__,param->handle,att_idx);

    switch(att_idx)
    {
        case SMARTCONFIG_IDX_WIFI_STATE_NTF_CFG:
            {
                // Fill data
                value_size = sizeof(uint16_t);
                if (smartconfig_env->wifi_state_ntf_cfg) {
                    ntf_cfg = 1;
                } else {
                    ntf_cfg = 0;
                }
                 memcpy(value, (uint8_t *)&ntf_cfg, value_size);
            } break;

            case SMARTCONFIG_IDX_TIME_STATE_NTF_CFG:
            {
                // Fill data
                value_size = sizeof(uint16_t);
                if (smartconfig_env->time_ntf_cfg) {
                    ntf_cfg = 1;
                } else {
                    ntf_cfg = 0;
                }
                memcpy(value, (uint8_t *)&ntf_cfg, value_size);
            } break;

            default:
            {
                status = ATT_ERR_REQUEST_NOT_SUPPORTED;
            } break;
    }

    // Send data to peer device
    struct gattc_read_cfm* cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm, value_size);
    cfm->length = value_size;
    memcpy(cfm->value, value, value_size);
    cfm->handle = param->handle;
    cfm->status = status;

    // Send value to peer device.
    ke_msg_send(cfm);

    ke_state_set(dest_id, SMARTCONFIG_IDLE);

    return (KE_MSG_CONSUMED);
}

extern struct app_smartconfig_env_tag app_smartconfig_env;
static void send_notifiction(uint8_t conidx, uint8_t contentType, const uint8_t* ptrData, uint32_t length)
{
    uint16_t handle_offset = 0xFFFF;
    struct smartconfig_env_tag *smartconfig_env = PRF_ENV_GET(SMARTCONFIG, smartconfig);

    if ((SMARTCONFIG_WIFI_INFO == contentType) &&
        (smartconfig_env->wifi_state_ntf_cfg))
    {
        handle_offset = SMARTCONFIG_IDX_WIFI_STATE_VAL;
    }
    else if ((SMARTCONFIG_TIME_INFO == contentType) &&
        (smartconfig_env->time_ntf_cfg))
    {
        handle_offset = SMARTCONFIG_IDX_TIME_STATE_VAL;
    }

    if (0xFFFF != handle_offset)
    {
        prf_src_task_get(&smartconfig_env->prf_env, conidx);
        // Allocate the GATT notification message
        struct gattc_send_evt_cmd *report_ntf = KE_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,
                KE_BUILD_ID(TASK_GATTC, conidx), prf_src_task_get(&smartconfig_env->prf_env, conidx),
                gattc_send_evt_cmd, length);

        // Fill in the parameter structure
        report_ntf->operation = GATTC_NOTIFY;
        report_ntf->handle    = smartconfig_env->shdl + handle_offset;
        // pack measured value in database
        report_ntf->length    = length;
        memcpy(report_ntf->value, ptrData, length);
        // send notification to peer device
        ke_msg_send(report_ntf);
    }
}

static void send_indication(uint8_t conidx, uint8_t contentType, const uint8_t* ptrData, uint32_t length)
{
    uint16_t handle_offset = 0xFFFF;
    struct smartconfig_env_tag *smartconfig_env = PRF_ENV_GET(SMARTCONFIG, smartconfig);

    if ((SMARTCONFIG_WIFI_INFO == contentType) &&
        (smartconfig_env->wifi_state_ntf_cfg))
    {
        handle_offset = SMARTCONFIG_IDX_WIFI_STATE_VAL;
    }
    else if ((SMARTCONFIG_TIME_INFO == contentType) &&
        (smartconfig_env->time_ntf_cfg))
    {
        handle_offset = SMARTCONFIG_IDX_TIME_STATE_VAL;
    }

    if (0xFFFF != handle_offset)
    {
        // Allocate the GATT notification message
        struct gattc_send_evt_cmd *report_ntf = KE_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,
                KE_BUILD_ID(TASK_GATTC, conidx), prf_src_task_get(&smartconfig_env->prf_env, conidx),
                gattc_send_evt_cmd, length);

        // Fill in the parameter structure
        report_ntf->operation = GATTC_INDICATE;
        report_ntf->handle    = smartconfig_env->shdl + handle_offset;
        // pack measured value in database
        report_ntf->length    = length;
        memcpy(report_ntf->value, ptrData, length);
        // send notification to peer device
        ke_msg_send(report_ntf);
    }
}

__STATIC int send_wifi_state_notification_handler(ke_msg_id_t const msgid,
                                      struct ble_smartconfig_send_data_req const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    send_notifiction(param->conidx, SMARTCONFIG_WIFI_INFO, param->value, param->length);
    return (KE_MSG_CONSUMED);
}

__STATIC int send_wifi_state_indication_handler(ke_msg_id_t const msgid,
                                      struct ble_smartconfig_send_data_req const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    send_indication(param->conidx, SMARTCONFIG_WIFI_INFO, param->value, param->length);
    return (KE_MSG_CONSUMED);
}

__STATIC int send_time_state_notification_handler(ke_msg_id_t const msgid,
                                      struct ble_smartconfig_send_data_req const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    send_notifiction(param->conidx, SMARTCONFIG_TIME_INFO, param->value, param->length);
    return (KE_MSG_CONSUMED);
}

__STATIC int send_time_state_indication_handler(ke_msg_id_t const msgid,
                                      struct ble_smartconfig_send_data_req const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    send_indication(param->conidx, SMARTCONFIG_TIME_INFO, param->value, param->length);
    return (KE_MSG_CONSUMED);
}


/**
 ****************************************************************************************
 * @brief Handles reception of the attribute info request message.
 *
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_att_info_req_ind_handler(ke_msg_id_t const msgid,
        struct gattc_att_info_req_ind *param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id)
{
    // Get the address of the environment
    struct gattc_att_info_cfm * cfm;

    //Send write response
    cfm = KE_MSG_ALLOC(GATTC_ATT_INFO_CFM, src_id, dest_id, gattc_att_info_cfm);
    cfm->handle = param->handle;

    struct smartconfig_env_tag *smartconfig_env = PRF_ENV_GET(SMARTCONFIG, smartconfig);

    if ((param->handle == (smartconfig_env->shdl + SMARTCONFIG_IDX_WIFI_STATE_NTF_CFG)) ||
        (param->handle == (smartconfig_env->shdl + SMARTCONFIG_IDX_TIME_STATE_NTF_CFG)))
    {
        // CCC attribute length = 2
        cfm->length = 2;
        cfm->status = GAP_ERR_NO_ERROR;
    }
    else if ((param->handle == (smartconfig_env->shdl + SMARTCONFIG_IDX_AP_INFO_VAL)) ||
        (param->handle == (smartconfig_env->shdl + SMARTCONFIG_IDX_TIME_INFO_VAL)))
    {
        // force length to zero to reject any write starting from something != 0
        cfm->length = 0;
        cfm->status = GAP_ERR_NO_ERROR;
    }
    else
    {
        cfm->length = 0;
        cfm->status = ATT_ERR_WRITE_NOT_PERMITTED;
    }

    ke_msg_send(cfm);

    return (KE_MSG_CONSUMED);
}


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/* Default State handlers definition. */
KE_MSG_HANDLER_TAB(smartconfig)
{
    {GATTC_WRITE_REQ_IND,                           (ke_msg_func_t) gattc_write_req_ind_handler},
    {GATTC_CMP_EVT,                                 (ke_msg_func_t) gattc_cmp_evt_handler},
    {GATTC_READ_REQ_IND,                            (ke_msg_func_t) gattc_read_req_ind_handler},
    {SMARTCONFIG_SEND_WIFI_STATE_NOTIFICATION,      (ke_msg_func_t) send_wifi_state_notification_handler},
    {SMARTCONFIG_SEND_WIFI_STATE_INDICATION,        (ke_msg_func_t) send_wifi_state_indication_handler},
    {SMARTCONFIG_SEND_TIME_STATE_NOTIFICATION,      (ke_msg_func_t) send_time_state_notification_handler},
    {SMARTCONFIG_SEND_TIME_STATE_INDICATION,        (ke_msg_func_t) send_time_state_indication_handler},
    {GATTC_ATT_INFO_REQ_IND,                        (ke_msg_func_t) gattc_att_info_req_ind_handler },
};

void smartconfig_task_init(struct ke_task_desc *task_desc)
{
    // Get the address of the environment
    struct smartconfig_env_tag *smartconfig_env = PRF_ENV_GET(SMARTCONFIG, smartconfig);

    task_desc->msg_handler_tab = smartconfig_msg_handler_tab;
    task_desc->msg_cnt         = ARRAY_LEN(smartconfig_msg_handler_tab);
    task_desc->state           = &(smartconfig_env->state);
    task_desc->idx_max         = 1;
}

#endif /* #if (BLE_SMARTCONFIG) */

/// @} SMARTCONFIGTASK
