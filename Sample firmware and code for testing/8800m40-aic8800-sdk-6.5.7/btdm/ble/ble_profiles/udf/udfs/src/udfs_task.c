/**
 ****************************************************************************************
 *
 * @file udfs_task.c
 *
 * @brief Aud Transmit Profile Server Task Implementation.
 *
 * Copyright (C) AIC
 *
 *
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @addtogroup UDFS_TASK
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_UDF_SERVER)
#include "gap.h"
#include "gattc_task.h"
#include "gapc_task.h"
#include "attm.h"
#include "udfs.h"
#include "udfs_task.h"
#include "gapm.h"
#include "prf_utils.h"

#include "ke_mem.h"
#include "ble_utils.h"
#include "app.h"

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
    ke_task_id_t prf_task = gapm_get_id_from_task(dest_id);
    struct udfs_env_tag *udfs_env = (struct udfs_env_tag *)prf_env_get(KE_TYPE_GET(prf_task));
    uint8_t conidx = KE_IDX_GET(src_id);
    uint8_t status = GAP_ERR_NO_ERROR;
    uint16_t att_desc_client_char_cfg_uuid = ATT_DESC_CLIENT_CHAR_CFG;

    //Send write response
    struct gattc_write_cfm *cfm = KE_MSG_ALLOC(
            GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm);
    cfm->handle = param->handle;
    cfm->status = status;
    ke_msg_send(cfm);

    TRACE("BLE_TASK: write env %x, prf_task %x,dest_id %x,src_id %x\n",udfs_env,prf_task,dest_id,src_id);
    if (udfs_env != NULL)
    {
        if(!udfs_env->att_db){
            ASSERT_ERR(0);
        }
        if ((udfs_env->att_db[param->handle - udfs_env->shdl].perm & PERM(WRITE_REQ, ENABLE)) ||
            (udfs_env->att_db[param->handle - udfs_env->shdl].perm & PERM(WRITE_COMMAND, ENABLE))) {
            if (!memcmp(&att_desc_client_char_cfg_uuid, udfs_env->att_db[param->handle - udfs_env->shdl].uuid, 2)) {
                uint16_t value = 0x0000;
                memcpy(&value, &(param->value), sizeof(uint16_t));

                if (status == GAP_ERR_NO_ERROR)
                {
                    struct udfs_ntf_ind_config * ind = KE_MSG_ALLOC(UDFS_NTF_IND_SERVICE_CHANGED,
                            prf_dst_task_get(&udfs_env->prf_env, conidx),
                            prf_src_task_get(&udfs_env->prf_env, conidx),
                            udfs_ntf_ind_config);
                    ind->conidx = conidx;
                    ind->att_idx = (param->handle - udfs_env->shdl);
                    ind->ntf_ind_en = value;
                    ind->prf_user_id = udfs_env->prf_user_id;
                    app_user_cb_poll(UDFS_NTF_IND_SERVICE_CHANGED,(uint8_t *)ind);
                    KE_MSG_FREE(ind);
                }
            } else {
                //inform APP of data
                struct udfs_rx_data_ind * ind = KE_MSG_ALLOC_DYN(UDFS_WR_RECEIVED,
                        prf_dst_task_get(&udfs_env->prf_env, conidx),
                        prf_src_task_get(&udfs_env->prf_env, conidx),
                        udfs_rx_data_ind,
                        param->length);
                ind->conidx = conidx;
                ind->att_idx = (param->handle - udfs_env->shdl);
                ind->length = param->length;
                memcpy((uint8_t *)(ind->data), &(param->value), param->length);
                ind->prf_user_id = udfs_env->prf_user_id;
                app_user_cb_poll(UDFS_WR_RECEIVED,(uint8_t *)ind);
                KE_MSG_FREE(ind);
            }
        }
        else {
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
    ke_task_id_t prf_task = gapm_get_id_from_task(dest_id);
    struct udfs_env_tag *udfs_env = (struct udfs_env_tag *)prf_env_get(KE_TYPE_GET(prf_task));
    uint8_t state = ke_state_get(dest_id);
    uint8_t conidx = KE_IDX_GET(dest_id);
    TRACE("BLE_TASK: udfs cmp env %x,prf_task %x,dest_id %x,src_id %x\n",udfs_env,prf_task,dest_id,src_id);

    // notification or write request has been sent out
    if ((GATTC_NOTIFY == param->operation) || (GATTC_INDICATE == param->operation))
    {
        if((state == UDFS_BUSY) && (udfs_env->operation != UDFS_OP_NONE))
        {
            //TRACE("BLE: udfs cmp operation %x\n",udfs_env->operation );
            switch(udfs_env->operation)
            {
                case UDFC_OP_SD_NTF:
                    {
                        struct udfs_data_sent_ind * ind = KE_MSG_ALLOC(UDFS_NTF_SENT,
                                prf_dst_task_get(&udfs_env->prf_env, conidx),
                                prf_src_task_get(&udfs_env->prf_env, conidx),
                                udfs_data_sent_ind);
                        ind->conidx = conidx;
                        ind->prf_user_id = udfs_env->prf_user_id;
                        ind->att_idx = param->seq_num;
                        ind->status = param->status;
                        app_user_cb_poll(UDFS_NTF_SENT,(uint8_t *)ind);
                        KE_MSG_FREE(ind);
                    }
                    break;
                case UDFC_OP_SD_IND:
                    {
                        struct udfs_data_sent_ind * ind = KE_MSG_ALLOC(UDFS_IND_SENT,
                                prf_dst_task_get(&udfs_env->prf_env, conidx),
                                prf_src_task_get(&udfs_env->prf_env, conidx),
                                udfs_data_sent_ind);
                        ind->conidx = conidx;
                        ind->prf_user_id = udfs_env->prf_user_id;
                        ind->att_idx = param->seq_num;
                        ind->status = param->status;
                        app_user_cb_poll(UDFS_IND_SENT,(uint8_t *)ind);
                        KE_MSG_FREE(ind);

                    }
                    break;
                default:
                    break;
            }
            // operation is over - go back to idle state
            udfs_env->operation = UDFS_OP_NONE;
            ke_state_set(dest_id, UDFS_IDLE);
        }
    }
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
    ke_task_id_t prf_task = gapm_get_id_from_task(dest_id);
    struct udfs_env_tag *udfs_env = (struct udfs_env_tag *)prf_env_get(KE_TYPE_GET(prf_task));
    uint8_t att_idx = param->handle - udfs_env->shdl;
    uint8_t conidx = KE_IDX_GET(dest_id);

    uint8_t value_size = 0;
    uint8_t status = ATT_ERR_NO_ERROR;
    uint8_t value[UDFS_MAX_LEN];
    struct udfs_read_data_req rd_data;
    TRACE("BLE_TASK: udfs read env %x,prf_task %x,dest_id %x,src_id %x\n",udfs_env,prf_task,dest_id,src_id);
    TRACE("BLE_TASK: read idx %x\n",att_idx);
    rd_data.conidx = conidx;
    rd_data.att_idx= att_idx;
    rd_data.prf_user_id = udfs_env->prf_user_id;
    rd_data.length = 0;
    rd_data.value = value;

    app_user_cb_poll(UDFS_RD_VALUE_UPDATE,(uint8_t *)&rd_data);
    value_size = rd_data.length;

    // Send data to peer device
    struct gattc_read_cfm* cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm, value_size);
    cfm->length = value_size;
    memcpy(cfm->value, value, value_size);
    cfm->handle = param->handle;
    cfm->status = status;

    // Send value to peer device.
    ke_msg_send(cfm);

    ke_state_set(dest_id, UDFS_IDLE);

    return (KE_MSG_CONSUMED);
}

static void send_notifiction(struct udfs_env_tag* udfs,uint8_t conidx, uint16_t att_id, const uint8_t* ptrData, uint32_t length)
{
    uint16_t handle_offset = att_id;
    struct udfs_env_tag *udfs_env = udfs;

    if (!udfs_env)
    {
        ASSERT_ERR(0);
    }
    udfs_env->operation = UDFC_OP_SD_NTF;

    if (0xFFFF != handle_offset)
    {
        prf_src_task_get(&udfs_env->prf_env, conidx);
        // Allocate the GATT notification message
        struct gattc_send_evt_cmd *report_ntf = KE_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,
                KE_BUILD_ID(TASK_GATTC, conidx), prf_src_task_get(&udfs_env->prf_env, conidx),
                gattc_send_evt_cmd, length);

        // Fill in the parameter structure
        report_ntf->operation = GATTC_NOTIFY;
        report_ntf->handle    = udfs_env->shdl + handle_offset;
        // pack measured value in database
        report_ntf->length    = length;
        report_ntf->seq_num = handle_offset;
        memcpy(report_ntf->value, ptrData, length);
        // send notification to peer device
        ke_msg_send(report_ntf);
    }
}

static void send_indication(struct udfs_env_tag* udfs,uint8_t conidx, uint16_t att_id, const uint8_t* ptrData, uint32_t length)
{
    uint16_t handle_offset = att_id;
    struct udfs_env_tag *udfs_env = udfs;
    
    if (!udfs_env)
    {
        ASSERT_ERR(0);
    }
    udfs_env->operation = UDFC_OP_SD_IND;

    if (0xFFFF != handle_offset)
    {
        // Allocate the GATT notification message
        struct gattc_send_evt_cmd *report_ntf = KE_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,
                KE_BUILD_ID(TASK_GATTC, conidx), prf_src_task_get(&udfs_env->prf_env, conidx),
                gattc_send_evt_cmd, length);

        // Fill in the parameter structure
        report_ntf->operation = GATTC_INDICATE;
        report_ntf->handle    = udfs_env->shdl + handle_offset;
        // pack measured value in database
        report_ntf->length    = length;
        report_ntf->seq_num = handle_offset;
        memcpy(report_ntf->value, ptrData, length);
        // send notification to peer device
        ke_msg_send(report_ntf);
    }
}

__STATIC int send_notification_handler(ke_msg_id_t const msgid,
                                      struct udfs_send_data_req const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    ke_task_id_t prf_task = gapm_get_id_from_task(dest_id);
    struct udfs_env_tag* udfs = (struct udfs_env_tag *)prf_env_get(KE_TYPE_GET(prf_task));
    TRACE("BLE_TASK: send_notification_handler env %x,prf_task %x,dest_id %x,src_id %x\n",udfs,prf_task,dest_id,src_id);

    if(udfs){
        if(state == UDFS_IDLE){
            send_notifiction(udfs,param->conidx, param->att_idx, param->value, param->length);
            ke_state_set(dest_id, UDFS_BUSY);
        }
        // process message later
        else if (state == UDFS_BUSY)
        {
            msg_status = KE_MSG_SAVED;
        }
    }

    return (msg_status);
}

__STATIC int send_indication_handler(ke_msg_id_t const msgid,
                                      struct udfs_send_data_req const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    ke_task_id_t prf_task = gapm_get_id_from_task(dest_id);
    struct udfs_env_tag* udfs = (struct udfs_env_tag *)prf_env_get(KE_TYPE_GET(prf_task));
    TRACE("BLE_TASK: send_indication_handler env %x,prf_task %x,dest_id %x,src_id %x\n",udfs,prf_task,dest_id,src_id);

    if(udfs){
        if(state == UDFS_IDLE){
            send_indication(udfs,param->conidx, param->att_idx, param->value, param->length);
            ke_state_set(dest_id, UDFS_BUSY);
        }
        // process message later
        else if (state == UDFS_BUSY)
        {
            msg_status = KE_MSG_SAVED;
        }
    }
    return (msg_status);
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
    uint16_t att_desc_client_char_cfg_uuid = ATT_DESC_CLIENT_CHAR_CFG;
    //Send write response
    cfm = KE_MSG_ALLOC(GATTC_ATT_INFO_CFM, src_id, dest_id, gattc_att_info_cfm);
    cfm->handle = param->handle;

    //struct udfs_env_tag *udfs_env = PRF_ENV_GET(UDFS, udfs);
    ke_task_id_t prf_task = gapm_get_id_from_task(dest_id);
    struct udfs_env_tag* udfs_env = (struct udfs_env_tag *)prf_env_get(KE_TYPE_GET(prf_task));
    TRACE("BLE_TASK: gattc_att_info_req_ind_handler env %x,prf_task %x,dest_id %x,src_id %x\n",udfs_env,prf_task,dest_id,src_id);

    if(!udfs_env || !udfs_env->att_db){
        ASSERT_ERR(0);
    }

    if (!memcmp(&att_desc_client_char_cfg_uuid, udfs_env->att_db[param->handle - udfs_env->shdl].uuid, 2))
    {
        // CCC attribute length = 2
        cfm->length = 2;
        cfm->status = GAP_ERR_NO_ERROR;
    } else if ((udfs_env->att_db[param->handle - udfs_env->shdl].perm & PERM(WRITE_REQ, ENABLE)) ||
            (udfs_env->att_db[param->handle - udfs_env->shdl].perm & PERM(WRITE_COMMAND, ENABLE)))
    {
        // force length to zero to reject any write starting from something != 0
        cfm->length = 0;
        cfm->status = GAP_ERR_NO_ERROR;
    } else
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
KE_MSG_HANDLER_TAB(udfs)
{
    {GATTC_WRITE_REQ_IND,                           (ke_msg_func_t) gattc_write_req_ind_handler},
    {GATTC_CMP_EVT,                                 (ke_msg_func_t) gattc_cmp_evt_handler},
    {GATTC_READ_REQ_IND,                            (ke_msg_func_t) gattc_read_req_ind_handler},
    {UDFS_SEND_NOTIFICATION,                        (ke_msg_func_t) send_notification_handler},
    {UDFS_SEND_INDICATION,                          (ke_msg_func_t) send_indication_handler},
    {GATTC_ATT_INFO_REQ_IND,                        (ke_msg_func_t) gattc_att_info_req_ind_handler },
};

void udfs_task_init(struct ke_task_desc *task_desc,struct udfs_env_tag* udfs_env)
{
    // Get the address of the environment

    task_desc->msg_handler_tab = udfs_msg_handler_tab;
    task_desc->msg_cnt         = ARRAY_LEN(udfs_msg_handler_tab);
    task_desc->state           = &(udfs_env->state);
    task_desc->idx_max         = UDFS_MAX_CONN_IDX;
}

#endif /* #if (BLE_UDF_SERVER) */

/// @} UDFSTASK
