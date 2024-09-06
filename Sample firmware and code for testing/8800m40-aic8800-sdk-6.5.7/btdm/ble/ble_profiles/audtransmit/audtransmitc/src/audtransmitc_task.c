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

#if (BLE_AUDTRANSMIT_CLIENT)
#include "gap.h"
#include "gattc_task.h"
#include "gapc_task.h"
#include "attm.h"
#include "audtransmitc.h"
#include "audtransmitc_task.h"

#include "prf_utils.h"

#include "ke_mem.h"
#include "ble_utils.h"


/*
 * GLOBAL VARIABLES DEFINITIONS
 ****************************************************************************************
 */

#define ATT_CHAR_AUD_TRANSMIT_SERVICE    0Xfe01
#define ATT_CHAR_AUD_INFO                0Xfe02
#define ATT_CHAR_AUD_CTRL                0Xfe03
#define ATT_CHAR_DATA_SEND               0Xfe04
#define ATT_CHAR_DATA_RECV               0Xfe05


/// State machine used to retrieve Service characteristics information
const struct prf_char_def audtransmitc_atcs_char[AUDTRANSMITC_CHAR_MAX] =
{
    [AUDTRANSMITC_CHAR_AUD_INFO]      = {ATT_CHAR_AUD_INFO,
                                         ATT_MANDATORY,
                                         ATT_CHAR_PROP_NTF},
    [AUDTRANSMITC_CHAR_AUD_CTRL]      = {ATT_CHAR_AUD_CTRL,
                                         ATT_OPTIONAL,
                                         ATT_CHAR_PROP_WR_NO_RESP | ATT_CHAR_PROP_WR},
    [AUDTRANSMITC_CHAR_DATA_SEND]     = {ATT_CHAR_DATA_SEND,
                                         ATT_MANDATORY,
                                         ATT_CHAR_PROP_NTF},
    [AUDTRANSMITC_CHAR_DATA_RECV]     = {ATT_CHAR_DATA_RECV,
                                         ATT_OPTIONAL,
                                         ATT_CHAR_PROP_WR_NO_RESP | ATT_CHAR_PROP_WR},

};

/// State machine used to retrieve Service characteristic description information
const struct prf_char_desc_def audtransmitc_atcs_char_desc[AUDTRANSMITC_DESC_MAX] =
{
    [AUDTRANSMITC_DESC_AUD_INFO_CFG]   = {ATT_DESC_CLIENT_CHAR_CFG, ATT_MANDATORY, AUDTRANSMITC_CHAR_AUD_INFO},
    [AUDTRANSMITC_DESC_DATA_SEND_CFG]  = {ATT_DESC_CLIENT_CHAR_CFG, ATT_MANDATORY, AUDTRANSMITC_CHAR_DATA_SEND},
};

/*
 * GLOBAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref AUDTRANSMITC_ENABLE_REQ message.
 * The handler enables the Scan Parameters Profile Client Role.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int audtransmitc_enable_req_handler(ke_msg_id_t const msgid,
                                   struct audtransmitc_enable_req const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id)
{
    // Status
    uint8_t status = GAP_ERR_NO_ERROR;

    uint8_t state = ke_state_get(dest_id);
    uint8_t conidx = KE_IDX_GET(dest_id);
    // Battery service Client Role Task Environment
    struct audtransmitc_env_tag *audtransmitc_env = PRF_ENV_GET(AUDTRANSMITC, audtransmitc);
    TRACE("BLE: %s , state = %x ,ptr = 0x%x, id = %x\n",__func__,state,audtransmitc_env->env[conidx],dest_id);
    ASSERT_INFO(audtransmitc_env != NULL, dest_id, src_id);
    if((state == AUDTRANSMITC_IDLE) && (audtransmitc_env->env[conidx] == NULL))
    {
        // allocate environment variable for task instance
        audtransmitc_env->env[conidx] = (struct audtransmitc_cnx_env*) ke_malloc(sizeof(struct audtransmitc_cnx_env),KE_MEM_ATT_DB);
        memset(audtransmitc_env->env[conidx], 0, sizeof(struct audtransmitc_cnx_env));
        TRACE("BLE: %s , con_type %x\n",__func__,param->con_type);

        //Config connection, start discovering
        if(param->con_type == PRF_CON_DISCOVERY)
        {
            //start discovering AUDTRANSMIT profile on peer
            prf_disc_svc_send(&(audtransmitc_env->prf_env), conidx, ATT_CHAR_AUD_TRANSMIT_SERVICE);
            //prf_disc_svc_all_send(&(audtransmitc_env->prf_env), conidx, ATT_UUID_16_LEN);

            // Go to DISCOVERING state
            ke_state_set(dest_id, AUDTRANSMITC_BUSY);
            audtransmitc_env->env[conidx]->operation = AUDTRANSMITC_OP_DISCOVER;
        }
        //normal connection, get saved att details
        else
        {
            audtransmitc_env->env[conidx]->nb_svc = 1;
            memcpy(&(audtransmitc_env->env[conidx]->ats), &(param->ats), sizeof(struct atcs_content));

            //send APP confirmation that can start normal connection to TH
            audtransmitc_enable_rsp_send(audtransmitc_env, conidx, GAP_ERR_NO_ERROR);
        }
    }
    else if(state != AUDTRANSMITC_FREE)
    {
        status = PRF_ERR_REQ_DISALLOWED;
    }

    // send an error if request fails
    if(status != GAP_ERR_NO_ERROR)
    {
        audtransmitc_enable_rsp_send(audtransmitc_env, conidx, status);
    }

    return (KE_MSG_CONSUMED);
}


/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATTC_SDP_SVC_IND_HANDLER message.
 * The handler stores the found service details for service discovery.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int gattc_sdp_svc_ind_handler(ke_msg_id_t const msgid,
                                             struct gattc_sdp_svc_ind const *ind,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);
    TRACE("BLE: audtransmitc sdp svc ind state %x ,id = %x\n",state ,dest_id);
    if(state == AUDTRANSMITC_BUSY)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct audtransmitc_env_tag *audtransmitc_env = PRF_ENV_GET(AUDTRANSMITC, audtransmitc);

        ASSERT_INFO(audtransmitc_env != NULL, dest_id, src_id);
        ASSERT_INFO(audtransmitc_env->env[conidx] != NULL, dest_id, src_id);

        if(audtransmitc_env->env[conidx]->nb_svc ==  0)
        {
            // Retrieve DIS characteristics
            prf_extract_svc_info(ind, AUDTRANSMITC_CHAR_MAX, &audtransmitc_atcs_char[0],
                    &(audtransmitc_env->env[conidx]->ats.chars[0]),
                    AUDTRANSMITC_DESC_MAX, &audtransmitc_atcs_char_desc[0],
                    &(audtransmitc_env->env[conidx]->ats.descs[0]));

            //Even if we get multiple responses we only store 1 range
            audtransmitc_env->env[conidx]->ats.svc.shdl = ind->start_hdl;
            audtransmitc_env->env[conidx]->ats.svc.ehdl = ind->end_hdl;
        }

        audtransmitc_env->env[conidx]->nb_svc++;
    }

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref AUDTRANSMITC_AUD_CTRL_WR_REQ message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int audtransmitc_aud_ctrl_wr_req_handler(ke_msg_id_t const msgid,
                                             struct audtransmitc_send_data_req const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t status = PRF_ERR_REQ_DISALLOWED;

    if(state == AUDTRANSMITC_IDLE)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct audtransmitc_env_tag *audtransmitc_env = PRF_ENV_GET(AUDTRANSMITC, audtransmitc);
        ASSERT_INFO(audtransmitc_env != NULL, dest_id, src_id);

        // environment variable not ready
        if(audtransmitc_env->env[conidx] == NULL)
        {
            status = PRF_APP_ERROR;
        }
        else
        {
            uint16_t handle = audtransmitc_env->env[conidx]->ats.chars[AUDTRANSMITC_CHAR_AUD_CTRL].val_hdl;
            status = PRF_ERR_INEXISTENT_HDL;

            if(handle != ATT_INVALID_HANDLE)
            {
                status = GAP_ERR_NO_ERROR;

                // Send GATT Write Request
                prf_gatt_write(&audtransmitc_env->prf_env, conidx, handle, (uint8_t*)param->value, param->length, GATTC_WRITE_NO_RESPONSE);
                // store context of request and go into busy state
                audtransmitc_env->env[conidx]->operation = AUDTRANSMITC_OP_WR_AUD_CTRL;
                ke_state_set(dest_id, AUDTRANSMITC_BUSY);
            }
        }
    }
    // process message later
    else if (state == AUDTRANSMITC_BUSY)
    {
        status = GAP_ERR_NO_ERROR;
        msg_status = KE_MSG_SAVED;
    }

    // request cannot be performed
    if(status != GAP_ERR_NO_ERROR)
    {
        struct audtransmitc_data_sent_ind * rsp = KE_MSG_ALLOC(AUDTRANSMITC_AUD_CTRL_WR_RSP,
                src_id, dest_id, audtransmitc_data_sent_ind);
        // set error status
        rsp->status = status;
        ke_msg_send(rsp);
    }

    return (msg_status);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref AUDTRANSMITC_AUD_DATA_WR_REQ message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int audtransmitc_aud_data_wr_req_handler(ke_msg_id_t const msgid,
                                             struct audtransmitc_send_data_req const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t status = PRF_ERR_REQ_DISALLOWED;

    if(state == AUDTRANSMITC_IDLE)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct audtransmitc_env_tag *audtransmitc_env = PRF_ENV_GET(AUDTRANSMITC, audtransmitc);
        ASSERT_INFO(audtransmitc_env != NULL, dest_id, src_id);

        // environment variable not ready
        if(audtransmitc_env->env[conidx] == NULL)
        {
            status = PRF_APP_ERROR;
        }
        else
        {
            uint16_t handle = audtransmitc_env->env[conidx]->ats.chars[AUDTRANSMITC_CHAR_DATA_RECV].val_hdl;
            status = PRF_ERR_INEXISTENT_HDL;

            if(handle != ATT_INVALID_HANDLE)
            {
                status = GAP_ERR_NO_ERROR;

                // Send GATT Write Request
                prf_gatt_write(&audtransmitc_env->prf_env, conidx, handle, (uint8_t*)param->value, param->length, GATTC_WRITE_NO_RESPONSE);
                // store context of request and go into busy state
                audtransmitc_env->env[conidx]->operation = AUDTRANSMITC_OP_WR_AUD_DATA;
                ke_state_set(dest_id, AUDTRANSMITC_BUSY);
            }
        }
    }
    // process message later
    else if (state == AUDTRANSMITC_BUSY)
    {
        status = GAP_ERR_NO_ERROR;
        msg_status = KE_MSG_SAVED;
    }

    // request cannot be performed
    if(status != GAP_ERR_NO_ERROR)
    {
        struct audtransmitc_data_sent_ind * rsp = KE_MSG_ALLOC(AUDTRANSMITC_AUD_DATA_WR_RSP,
                src_id, dest_id, audtransmitc_data_sent_ind);
        // set error status
        rsp->status = status;
        ke_msg_send(rsp);
    }

    return (msg_status);
}


/**
 ****************************************************************************************
 * @brief Handles reception of the @ref AUDTRANSMITC_AUD_INFO_NTF_CFG_REQ message.
 * It allows configuration of the peer ntf/stop characteristic for a specified characteristic.
 * Will return an error code if that cfg char does not exist.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int audtransmitc_aud_info_ntf_cfg_req_handler(ke_msg_id_t const msgid,
                                                  struct audtransmitc_notif_config const *param,
                                                  ke_task_id_t const dest_id,
                                                  ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t status = PRF_ERR_REQ_DISALLOWED;

    if(state == AUDTRANSMITC_IDLE)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct audtransmitc_env_tag *audtransmitc_env = PRF_ENV_GET(AUDTRANSMITC, audtransmitc);
        ASSERT_INFO(audtransmitc_env != NULL, dest_id, src_id);

        // environment variable not ready
        if(audtransmitc_env->env[conidx] == NULL)
        {
            status = PRF_APP_ERROR;
        }
        else
        {
            uint16_t handle = audtransmitc_env->env[conidx]->ats.descs[AUDTRANSMITC_DESC_AUD_INFO_CFG].desc_hdl;
            status = PRF_ERR_INEXISTENT_HDL;

            if(handle != ATT_INVALID_HANDLE)
            {
                status = GAP_ERR_NO_ERROR;
                // Send GATT Write Request
                prf_gatt_write_ntf_ind(&audtransmitc_env->prf_env, conidx, handle, param->ntf_en);
                // store context of request and go into busy state
                audtransmitc_env->env[conidx]->operation = AUDTRANSMITC_OP_WR_AUD_INFO_NTF_CFG;
                ke_state_set(dest_id, AUDTRANSMITC_BUSY);
            }
        }
    }
    // process message later
    else if (state == AUDTRANSMITC_BUSY)
    {
        status = GAP_ERR_NO_ERROR;
        msg_status = KE_MSG_SAVED;
    }

    // request cannot be performed
    if(status != GAP_ERR_NO_ERROR)
    {
        struct audtransmitc_data_sent_ind * rsp = KE_MSG_ALLOC(AUDTRANSMITC_AUD_INFO_NTF_CFG_RSP,
                src_id, dest_id, audtransmitc_data_sent_ind);
        // set error status
        rsp->status = status;
        ke_msg_send(rsp);
    }

    return (msg_status);
}


/**
 ****************************************************************************************
 * @brief Handles reception of the @ref AUDTRANSMITC_AUD_DATA_NTF_CFG_REQ message.
 * It allows configuration of the peer ntf/stop characteristic for a specified characteristic.
 * Will return an error code if that cfg char does not exist.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int audtransmitc_aud_data_ntf_cfg_req_handler(ke_msg_id_t const msgid,
                                                  struct audtransmitc_notif_config const *param,
                                                  ke_task_id_t const dest_id,
                                                  ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t status = PRF_ERR_REQ_DISALLOWED;

    if(state == AUDTRANSMITC_IDLE)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct audtransmitc_env_tag *audtransmitc_env = PRF_ENV_GET(AUDTRANSMITC, audtransmitc);
        ASSERT_INFO(audtransmitc_env != NULL, dest_id, src_id);

        // environment variable not ready
        if(audtransmitc_env->env[conidx] == NULL)
        {
            status = PRF_APP_ERROR;
        }
        else
        {
            uint16_t handle = audtransmitc_env->env[conidx]->ats.descs[AUDTRANSMITC_DESC_DATA_SEND_CFG].desc_hdl;
            status = PRF_ERR_INEXISTENT_HDL;

            if(handle != ATT_INVALID_HANDLE)
            {
                status = GAP_ERR_NO_ERROR;
                // Send GATT Write Request
                prf_gatt_write_ntf_ind(&audtransmitc_env->prf_env, conidx, handle, param->ntf_en);
                // store context of request and go into busy state
                audtransmitc_env->env[conidx]->operation = AUDTRANSMITC_OP_WR_AUD_DATA_NTF_CFG;
                ke_state_set(dest_id, AUDTRANSMITC_BUSY);
            }
        }
    }
    // process message later
    else if (state == AUDTRANSMITC_BUSY)
    {
        status = GAP_ERR_NO_ERROR;
        msg_status = KE_MSG_SAVED;
    }

    // request cannot be performed
    if(status != GAP_ERR_NO_ERROR)
    {
        struct audtransmitc_data_sent_ind * rsp = KE_MSG_ALLOC(AUDTRANSMITC_AUD_DATA_NTF_CFG_RSP,
                src_id, dest_id, audtransmitc_data_sent_ind);
        // set error status
        rsp->status = status;
        ke_msg_send(rsp);
    }

    return (msg_status);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATTC_CMP_EVT message.
 * This generic event is received for different requests, so need to keep track.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int gattc_cmp_evt_handler(ke_msg_id_t const msgid, struct gattc_cmp_evt const *param,
                                ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);
    uint8_t conidx = KE_IDX_GET(dest_id);
    // Get the address of the environment
    struct audtransmitc_env_tag *audtransmitc_env = PRF_ENV_GET(AUDTRANSMITC, audtransmitc);
    TRACE("BLE: audtransmitc cmp state %x,id = %x\n",state ,dest_id);
    // sanity check
    if((state == AUDTRANSMITC_BUSY) && (audtransmitc_env->env[conidx] != NULL)
            && (audtransmitc_env->env[conidx]->operation != AUDTRANSMITC_OP_NONE))
    {
        TRACE("BLE: audtransmitc cmp operation %x\n",audtransmitc_env->env[conidx]->operation );
        switch(audtransmitc_env->env[conidx]->operation)
        {
            case AUDTRANSMITC_OP_DISCOVER:
            {
                uint8_t status = param->status;
                #if 0
                struct gattc_exc_mtu_cmd * exc_mtu = KE_MSG_ALLOC(GATTC_EXC_MTU_CMD,
                        KE_BUILD_ID(TASK_GATTC, conidx), dest_id,
                        gattc_exc_mtu_cmd);
                exc_mtu->operation = GATTC_MTU_EXCH;
                
                //send the message to GATT, which will send back the response when it gets it
                ke_msg_send(exc_mtu);
                #endif
                prf_gatt_send_exchange_mtu(&audtransmitc_env->prf_env,conidx,512);

                if (param->status == ATT_ERR_NO_ERROR)
                {
                    // check characteristic validity
                    if(audtransmitc_env->env[conidx]->nb_svc == 1)
                    {
                        status = prf_check_svc_char_validity(AUDTRANSMITC_CHAR_MAX, audtransmitc_env->env[conidx]->ats.chars, audtransmitc_atcs_char);

                        // check descriptor validity
                        if(status == GAP_ERR_NO_ERROR)
                        {
                            status = prf_check_svc_char_desc_validity(AUDTRANSMITC_DESC_MAX,
                                    audtransmitc_env->env[conidx]->ats.descs, audtransmitc_atcs_char_desc,
                                    audtransmitc_env->env[conidx]->ats.chars);
                        }
                    }
                    // invalid number of services
                    else if(audtransmitc_env->env[conidx]->nb_svc > 1)
                    {
                        status = PRF_ERR_MULTIPLE_SVC;
                    }
                    // no services found
                    else
                    {
                        status = PRF_ERR_STOP_DISC_CHAR_MISSING;
                    }
                }
                audtransmitc_enable_rsp_send(audtransmitc_env, conidx, status);
                if(status == GAP_ERR_NO_ERROR){
                    struct audtransmitc_data_sent_ind * rsp = KE_MSG_ALLOC(AUDTRANSMITC_REG_NTF_PROCESS_DONE,
                            prf_dst_task_get(&(audtransmitc_env->prf_env), conidx), dest_id, audtransmitc_data_sent_ind);
                    // set error status
                    rsp->status =param->status;

                    ke_msg_send(rsp);
                }
            }break;
            case AUDTRANSMITC_OP_WR_AUD_INFO_NTF_CFG:
            {
                struct audtransmitc_data_sent_ind * rsp = KE_MSG_ALLOC(AUDTRANSMITC_AUD_INFO_NTF_CFG_RSP,
                        prf_dst_task_get(&(audtransmitc_env->prf_env), conidx), dest_id, audtransmitc_data_sent_ind);
                // set error status
                rsp->status =param->status;

                ke_msg_send(rsp);
            }break;
            case AUDTRANSMITC_OP_WR_AUD_DATA_NTF_CFG:
            {
                struct audtransmitc_data_sent_ind * rsp = KE_MSG_ALLOC(AUDTRANSMITC_AUD_DATA_NTF_CFG_RSP,
                        prf_dst_task_get(&(audtransmitc_env->prf_env), conidx), dest_id, audtransmitc_data_sent_ind);
                // set error status
                rsp->status =param->status;

                ke_msg_send(rsp);
            }break;
            case AUDTRANSMITC_OP_WR_AUD_CTRL:
            {
                struct audtransmitc_data_sent_ind * rsp = KE_MSG_ALLOC(AUDTRANSMITC_AUD_CTRL_WR_RSP,
                        prf_dst_task_get(&(audtransmitc_env->prf_env), conidx), dest_id, audtransmitc_data_sent_ind);
                // set error status
                rsp->status =param->status;

                ke_msg_send(rsp);
            }break;
            case AUDTRANSMITC_OP_WR_AUD_DATA:
            {
                struct audtransmitc_data_sent_ind * rsp = KE_MSG_ALLOC(AUDTRANSMITC_AUD_DATA_WR_RSP,
                        prf_dst_task_get(&(audtransmitc_env->prf_env), conidx), dest_id, audtransmitc_data_sent_ind);
                // set error status
                rsp->status =param->status;

                ke_msg_send(rsp);
            }break;
            default:
            {
                // Not Expected at all
                ASSERT_ERR(0);
            }break;
        }

        // operation is over - go back to idle state
        audtransmitc_env->env[conidx]->operation = AUDTRANSMITC_OP_NONE;
        ke_state_set(dest_id, AUDTRANSMITC_IDLE);
    }

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATTC_EVENT_IND message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int gattc_event_ind_handler(ke_msg_id_t const msgid,
                                        struct gattc_event_ind const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);

    if(state != AUDTRANSMITC_FREE)
    {
        // Retrieve environment data
        struct audtransmitc_env_tag *audtransmitc_env = PRF_ENV_GET(AUDTRANSMITC, audtransmitc);
        uint8_t conidx = KE_IDX_GET(dest_id);

        // inform application 

        if (audtransmitc_env->env[conidx] != NULL)
        {
                switch (param->type)
                {
                    case (GATTC_NOTIFY):
                    {
            
                        if (param->handle == audtransmitc_env->env[conidx]->ats.chars[AUDTRANSMITC_CHAR_AUD_INFO].val_hdl)
                        {
                            // Send an indication to the application
                            struct audtransmitc_rx_data_ind *ind = KE_MSG_ALLOC_DYN(AUDTRANSMITC_AUD_INFO_IND,
                                    prf_dst_task_get(&audtransmitc_env->prf_env, conidx),
                                    prf_src_task_get(&audtransmitc_env->prf_env, conidx),
                                    audtransmitc_rx_data_ind,
                                    param->length);
                            ind->length = param->length;
                            memcpy((uint8_t *)(ind->data), &(param->value), param->length);
                            
                            // Send the message
                            ke_msg_send(ind);
                        }
                        else if (param->handle == audtransmitc_env->env[conidx]->ats.chars[AUDTRANSMITC_CHAR_DATA_SEND].val_hdl)
                        {
                            // Send an indication to the application
                            struct audtransmitc_rx_data_ind *ind = KE_MSG_ALLOC_DYN(AUDTRANSMITC_AUD_DATA_IND,
                                    prf_dst_task_get(&audtransmitc_env->prf_env, conidx),
                                    prf_src_task_get(&audtransmitc_env->prf_env, conidx),
                                    audtransmitc_rx_data_ind,
                                    param->length);
                            ind->length = param->length;
                            memcpy((uint8_t *)(ind->data), &(param->value), param->length);
                            
                            // Send the message
                            ke_msg_send(ind);
                        }
                        else
                        {
                            ASSERT_ERR(0);
                        }
                    } break;
            
                    case (GATTC_INDICATE):
                    {
                        // confirm that indication has been correctly received
                        struct gattc_event_cfm * cfm = KE_MSG_ALLOC(GATTC_EVENT_CFM, src_id, dest_id, gattc_event_cfm);
                        cfm->handle = param->handle;
                        ke_msg_send(cfm);
            
                        // Check if we were waiting for the indication
                        if (audtransmitc_env->env[conidx]->operation != 0)
                        {

                            // else drop the message
                        }
                        // else drop the message
                    } break;
            
                    default:
                    {
                        ASSERT_ERR(0);
                    } break;
                }
            // else ignore the message
        }
    }

    return (KE_MSG_CONSUMED);
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/* Default State handlers definition. */
KE_MSG_HANDLER_TAB(audtransmitc)
{
    {AUDTRANSMITC_ENABLE_REQ,               (ke_msg_func_t)audtransmitc_enable_req_handler},
    {GATTC_SDP_SVC_IND,                     (ke_msg_func_t)gattc_sdp_svc_ind_handler},
    {AUDTRANSMITC_AUD_CTRL_WR_REQ,          (ke_msg_func_t)audtransmitc_aud_ctrl_wr_req_handler},
    {AUDTRANSMITC_AUD_DATA_WR_REQ,          (ke_msg_func_t)audtransmitc_aud_data_wr_req_handler},
    {AUDTRANSMITC_AUD_INFO_NTF_CFG_REQ,     (ke_msg_func_t)audtransmitc_aud_info_ntf_cfg_req_handler},
    {AUDTRANSMITC_AUD_DATA_NTF_CFG_REQ,     (ke_msg_func_t)audtransmitc_aud_data_ntf_cfg_req_handler},
    {GATTC_CMP_EVT,                         (ke_msg_func_t)gattc_cmp_evt_handler},
    {GATTC_EVENT_IND,                       (ke_msg_func_t)gattc_event_ind_handler},
};

void audtransmitc_task_init(struct ke_task_desc *task_desc)
{
    // Get the address of the environment
    struct audtransmitc_env_tag *audtransmitc_env = PRF_ENV_GET(AUDTRANSMITC, audtransmitc);

    task_desc->msg_handler_tab = audtransmitc_msg_handler_tab;
    task_desc->msg_cnt         = ARRAY_LEN(audtransmitc_msg_handler_tab);
    task_desc->state           = audtransmitc_env->state;
    task_desc->idx_max         = AUDTRANSMITC_IDX_MAX;
}

#endif /* #if (BLE_AUDTRANSMIT_CLIENT) */

/// @} AUDTRANSMITCTASK
