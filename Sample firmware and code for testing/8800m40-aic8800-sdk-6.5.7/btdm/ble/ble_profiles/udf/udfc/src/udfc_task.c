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

#if (BLE_UDF_CLIENT)
#include "gap.h"
#include "gattc_task.h"
#include "gapc_task.h"
#include "attm.h"
#include "udfc.h"
#include "udfc_task.h"

#include "prf_utils.h"

#include "ke_mem.h"
#include "ble_utils.h"


/*
 * GLOBAL VARIABLES DEFINITIONS
 ****************************************************************************************
 */


/*
 * GLOBAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref UDFC_ENABLE_REQ message.
 * The handler enables the Scan Parameters Profile Client Role.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int udfc_enable_req_handler(ke_msg_id_t const msgid,
                                   struct udfc_enable_req const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id)
{
    // Status
    uint8_t status = GAP_ERR_NO_ERROR;

    uint8_t state = ke_state_get(dest_id);
    uint8_t conidx = KE_IDX_GET(dest_id);
    // service Client Role Task Environment
    struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
    TRACE("BLE: %s , state = %x ,ptr = 0x%x, id = %x,conidx = %x\n",__func__,state,udfc_env->env[conidx],dest_id,conidx);
    ASSERT_INFO(udfc_env != NULL, dest_id, src_id);
    if((state == UDFC_IDLE) && (udfc_env->env[conidx] == NULL))
    {
        // allocate environment variable for task instance
        udfc_env->env[conidx] = (struct udfc_cnx_env*) ke_malloc(sizeof(struct udfc_cnx_env),KE_MEM_ATT_DB);
        memset(udfc_env->env[conidx], 0, sizeof(struct udfc_cnx_env));
        TRACE("BLE: %s , con_type %x\n",__func__,param->con_type);

        //Config connection, start discovering
        if(param->con_type == PRF_CON_DISCOVERY)
        {
            //start discovering profile on peer
            prf_disc_svc_all_send(&(udfc_env->prf_env), conidx, ATT_UUID_16_LEN);

            // Go to DISCOVERING state
            ke_state_set(dest_id, UDFC_BUSY);
            udfc_env->env[conidx]->operation = UDFC_OP_DISCOVER;
        }
    }
    else if(state != UDFC_FREE)
    {
        status = PRF_ERR_REQ_DISALLOWED;
    }

    // send an error if request fails
    if(status != GAP_ERR_NO_ERROR)
    {
        udfc_enable_rsp_send(udfc_env, conidx, status);
    }

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref UDFC_DISCOVER_REQ message.
 * The handler enables the Scan Parameters Profile Client Role.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int udfc_discover_req_handler(ke_msg_id_t const msgid,
                                   struct udfc_enable_req const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id)
{
    // Status
    uint8_t status = GAP_ERR_NO_ERROR;

    uint8_t state = ke_state_get(dest_id);
    uint8_t conidx = KE_IDX_GET(dest_id);
    // service Client Role Task Environment
    struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
    TRACE("BLE: %s , state = %x ,ptr = 0x%x, id = %x,conidx = %x\n",__func__,state,udfc_env->env[conidx],dest_id,conidx);
    ASSERT_INFO(udfc_env != NULL, dest_id, src_id);
    if(state == UDFC_IDLE)
    {
        // allocate environment variable for task instance
        if(udfc_env->env[conidx]){
            TRACE("BLE: %s , con_type %x\n",__func__,param->con_type);
            //Config connection, start discovering
            if(param->con_type == PRF_CON_DISCOVERY)
            {
                //start discovering profile on peer
                prf_disc_svc_all_send(&(udfc_env->prf_env), conidx, ATT_UUID_16_LEN);

                // Go to DISCOVERING state
                ke_state_set(dest_id, UDFC_BUSY);
                udfc_env->env[conidx]->operation = UDFC_OP_DISCOVER;
            }
        }else{
            status = PRF_ERR_REQ_DISALLOWED;
        }

    }
    else if(state != UDFC_FREE)
    {
        status = PRF_ERR_REQ_DISALLOWED;
    }

    // send an error if request fails
    if(status != GAP_ERR_NO_ERROR)
    {
        udfc_enable_rsp_send(udfc_env, conidx, status);
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
    TRACE("BLE: udfc sdp svc ind state %x ,id = %x\n",state ,dest_id);
    if(state == UDFC_BUSY)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        uint8_t num_of_char = 0;
        // Get the address of the environment
        struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
        TRACE("BLE: conidx = %x, start_hdl 0x%x ,end_hdl = 0x%x, service uuid = ",conidx,ind->start_hdl ,ind->end_hdl);
        for(uint8_t i=0;i<ind->uuid_len;i++){
            TRACE("0x%x ",ind->uuid[i]);
        }
        TRACE("\n");
        ASSERT_INFO(udfc_env != NULL, dest_id, src_id);
        ASSERT_INFO(udfc_env->env[conidx] != NULL, dest_id, src_id);

        num_of_char = prf_pre_extract_all_svc_info(ind);
        if(num_of_char){
            uint8_t nb_svc = udfc_env->env[conidx]->ats.nb_svc;
            if(udfc_env->env[conidx]->ats.scv_info[nb_svc] == NULL){
                udfc_env->env[conidx]->ats.scv_info[nb_svc] = 
                    (struct prf_disc_sdp_svc_info *)ke_malloc((sizeof(struct prf_disc_sdp_svc_info) + num_of_char*sizeof(struct prf_disc_sdp_att_info)), KE_MEM_ATT_DB);
                memset(udfc_env->env[conidx]->ats.scv_info[nb_svc],0,(sizeof(struct prf_disc_sdp_svc_info) + num_of_char*sizeof(struct prf_disc_sdp_att_info)));
                udfc_env->env[conidx]->ats.scv_info[nb_svc]->start_hdl = ind->start_hdl;
                udfc_env->env[conidx]->ats.scv_info[nb_svc]->end_hdl = ind->end_hdl;
                udfc_env->env[conidx]->ats.scv_info[nb_svc]->uuid_len = ind->uuid_len;
                memcpy(udfc_env->env[conidx]->ats.scv_info[nb_svc]->uuid,ind->uuid,ind->uuid_len);
                udfc_env->env[conidx]->ats.scv_info[nb_svc]->num_of_char = num_of_char;
                prf_extract_all_svc_info(ind,udfc_env->env[conidx]->ats.scv_info[nb_svc]->info);
            }
        }
        TRACE("BLE: num_of_char = %d",num_of_char);
        udfc_env->env[conidx]->ats.nb_svc++;
    }

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref UDFC_AUD_CTRL_WR_REQ message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int udfc_wr_req_handler(ke_msg_id_t const msgid,
                                             struct udfc_send_data_req const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t status = PRF_ERR_REQ_DISALLOWED;

    if(state == UDFC_IDLE)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
        ASSERT_INFO(udfc_env != NULL, dest_id, src_id);

        // environment variable not ready
        if(udfc_env->env[conidx] == NULL)
        {
            status = PRF_APP_ERROR;
        }
        else
        {
            uint16_t handle = param->handle;
            status = PRF_ERR_INEXISTENT_HDL;

            if(handle != ATT_INVALID_HANDLE)
            {
                status = GAP_ERR_NO_ERROR;

                // Send GATT Write Request
                prf_gatt_write(&udfc_env->prf_env, conidx, handle, (uint8_t*)param->value, param->length, GATTC_WRITE);
                // store context of request and go into busy state
                udfc_env->env[conidx]->operation = UDFC_OP_WR;
                ke_state_set(dest_id, UDFC_BUSY);
            }
        }
    }
    // process message later
    else if (state == UDFC_BUSY)
    {
        status = GAP_ERR_NO_ERROR;
        msg_status = KE_MSG_SAVED;
    }

    // request cannot be performed
    if(status != GAP_ERR_NO_ERROR)
    {
        struct udfc_data_sent_ind * rsp = KE_MSG_ALLOC(UDFC_WR_RSP,
                src_id, dest_id, udfc_data_sent_ind);
        rsp->handle = param->handle;
        // set error status
        rsp->status = status;
        ke_msg_send(rsp);
    }

    return (msg_status);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref UDFC_AUD_DATA_WR_REQ message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int udfc_wr_nores_req_handler(ke_msg_id_t const msgid,
                                             struct udfc_send_data_req const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t status = PRF_ERR_REQ_DISALLOWED;

    if(state == UDFC_IDLE)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
        ASSERT_INFO(udfc_env != NULL, dest_id, src_id);

        // environment variable not ready
        if(udfc_env->env[conidx] == NULL)
        {
            status = PRF_APP_ERROR;
        }
        else
        {
            uint16_t handle = param->handle;
            status = PRF_ERR_INEXISTENT_HDL;

            if(handle != ATT_INVALID_HANDLE)
            {
                status = GAP_ERR_NO_ERROR;

                // Send GATT Write Request
                prf_gatt_write(&udfc_env->prf_env, conidx, handle, (uint8_t*)param->value, param->length, GATTC_WRITE_NO_RESPONSE);
                // store context of request and go into busy state
                udfc_env->env[conidx]->operation = UDFC_OP_WR_NORES;
                ke_state_set(dest_id, UDFC_BUSY);
            }
        }
    }
    // process message later
    else if (state == UDFC_BUSY)
    {
        status = GAP_ERR_NO_ERROR;
        msg_status = KE_MSG_SAVED;
    }

    // request cannot be performed
    if(status != GAP_ERR_NO_ERROR)
    {
        struct udfc_data_sent_ind * rsp = KE_MSG_ALLOC(UDFC_WR_NORES_RSP,
                src_id, dest_id, udfc_data_sent_ind);
        // set error status
        rsp->handle = param->handle;
        rsp->status = status;
        ke_msg_send(rsp);
    }

    return (msg_status);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref UDFC_AUD_CTRL_WR_REQ message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int udfc_rd_req_handler(ke_msg_id_t const msgid,
                                             struct udfc_send_data_req const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t status = PRF_ERR_REQ_DISALLOWED;

    if(state == UDFC_IDLE)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
        ASSERT_INFO(udfc_env != NULL, dest_id, src_id);

        // environment variable not ready
        if(udfc_env->env[conidx] == NULL)
        {
            status = PRF_APP_ERROR;
        }
        else
        {
            uint16_t handle = param->handle;
            status = PRF_ERR_INEXISTENT_HDL;

            if(handle != ATT_INVALID_HANDLE)
            {
                status = GAP_ERR_NO_ERROR;
                // Send GATT Read Request
                prf_read_char_send(&udfc_env->prf_env,conidx,0,0,handle);
                // store context of request and go into busy state
                udfc_env->env[conidx]->operation = UDFC_OP_RD;
                ke_state_set(dest_id, UDFC_BUSY);
            }
        }
    }
    // process message later
    else if (state == UDFC_BUSY)
    {
        status = GAP_ERR_NO_ERROR;
        msg_status = KE_MSG_SAVED;
    }

    // request cannot be performed
    if(status != GAP_ERR_NO_ERROR)
    {
        struct gattc_read_ind * rsp = KE_MSG_ALLOC(UDFC_RD_RSP,
                src_id, dest_id, gattc_read_ind);
        // set error status
        rsp->handle = 0;
        rsp->offset = status;
        rsp->length = 0;
        ke_msg_send(rsp);
    }

    return (msg_status);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref UDFC_AUD_INFO_NTF_CFG_REQ message.
 * It allows configuration of the peer ntf/stop characteristic for a specified characteristic.
 * Will return an error code if that cfg char does not exist.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int udfc_ntf_cfg_req_handler(ke_msg_id_t const msgid,
                                                  struct udfc_notif_config const *param,
                                                  ke_task_id_t const dest_id,
                                                  ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t status = PRF_ERR_REQ_DISALLOWED;

    if(state == UDFC_IDLE)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
        ASSERT_INFO(udfc_env != NULL, dest_id, src_id);

        // environment variable not ready
        if(udfc_env->env[conidx] == NULL)
        {
            status = PRF_APP_ERROR;
        }
        else
        {
            uint16_t handle = param->handle;
            status = PRF_ERR_INEXISTENT_HDL;

            if(handle != ATT_INVALID_HANDLE)
            {
                status = GAP_ERR_NO_ERROR;
                enum prf_cli_conf cfg;
                if(param->ntf_en){
                    cfg = PRF_CLI_START_NTF;
                }else{
                    cfg = PRF_CLI_STOP_NTFIND;
                }
                // Send GATT Write Request
                prf_gatt_write_ntf_ind(&udfc_env->prf_env, conidx, handle, cfg);
                // store context of request and go into busy state
                udfc_env->env[conidx]->operation = UDFC_OP_WR_NTF_CFG;
                ke_state_set(dest_id, UDFC_BUSY);
            }
        }
    }
    // process message later
    else if (state == UDFC_BUSY)
    {
        status = GAP_ERR_NO_ERROR;
        msg_status = KE_MSG_SAVED;
    }

    // request cannot be performed
    if(status != GAP_ERR_NO_ERROR)
    {
        struct udfc_data_sent_ind * rsp = KE_MSG_ALLOC(UDFC_NTF_CFG_RSP,
                src_id, dest_id, udfc_data_sent_ind);
        // set error status
        rsp->handle = param->handle;
        rsp->status = status;
        ke_msg_send(rsp);
    }

    return (msg_status);
}


/**
 ****************************************************************************************
 * @brief Handles reception of the @ref UDFC_AUD_DATA_NTF_CFG_REQ message.
 * It allows configuration of the peer ntf/stop characteristic for a specified characteristic.
 * Will return an error code if that cfg char does not exist.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int udfc_ind_cfg_req_handler(ke_msg_id_t const msgid,
                                                  struct udfc_indication_config const *param,
                                                  ke_task_id_t const dest_id,
                                                  ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t status = PRF_ERR_REQ_DISALLOWED;

    if(state == UDFC_IDLE)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
        ASSERT_INFO(udfc_env != NULL, dest_id, src_id);

        // environment variable not ready
        if(udfc_env->env[conidx] == NULL)
        {
            status = PRF_APP_ERROR;
        }
        else
        {
            uint16_t handle = param->handle;
            status = PRF_ERR_INEXISTENT_HDL;

            if(handle != ATT_INVALID_HANDLE)
            {
                enum prf_cli_conf cfg;
                if(param->ind_en){
                    cfg = PRF_CLI_START_IND;
                }else{
                    cfg = PRF_CLI_STOP_NTFIND;
                }
                status = GAP_ERR_NO_ERROR;
                // Send GATT Write Request
                prf_gatt_write_ntf_ind(&udfc_env->prf_env, conidx, handle, cfg);
                // store context of request and go into busy state
                udfc_env->env[conidx]->operation = UDFC_OP_WR_IND_CFG;
                ke_state_set(dest_id, UDFC_BUSY);
            }
        }
    }
    // process message later
    else if (state == UDFC_BUSY)
    {
        status = GAP_ERR_NO_ERROR;
        msg_status = KE_MSG_SAVED;
    }

    // request cannot be performed
    if(status != GAP_ERR_NO_ERROR)
    {
        struct udfc_data_sent_ind * rsp = KE_MSG_ALLOC(UDFC_INDICATION_CFG_RSP,
                src_id, dest_id, udfc_data_sent_ind);
        // set error status
        rsp->handle = param->handle;
        rsp->status = status;
        ke_msg_send(rsp);
    }

    return (msg_status);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATTC_READ_IND message.
 * Generic event received after every simple read command sent to peer server.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
__STATIC int gattc_read_ind_handler(ke_msg_id_t const msgid,
                                    struct gattc_read_ind const *param,
                                    ke_task_id_t const dest_id,
                                    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);

    if(state == UDFC_BUSY)
    {
        // Retrieve environment data
        struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
        uint8_t conidx = KE_IDX_GET(dest_id);

        struct gattc_read_ind * rsp = KE_MSG_ALLOC_DYN(UDFC_RD_RSP,
                prf_dst_task_get(&(udfc_env->prf_env), conidx), dest_id, gattc_read_ind,param->length);
        rsp->handle = param->handle;
        rsp->offset = param->offset;
        rsp->length = param->length;
        memcpy(rsp->value,param->value,rsp->length);
        ke_msg_send(rsp);

        // operation is over - go back to idle state
        udfc_env->env[conidx]->operation = UDFC_OP_NONE;
        ke_state_set(dest_id, UDFC_IDLE);
    }

    return (KE_MSG_CONSUMED);
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
    struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
    TRACE("BLE: udfc cmp state %x,id = %x\n",state ,dest_id);
    // sanity check
    if((state == UDFC_BUSY) && (udfc_env->env[conidx] != NULL)
            && (udfc_env->env[conidx]->operation != UDFC_OP_NONE))
    {
        TRACE("BLE: udfc cmp operation %x\n",udfc_env->env[conidx]->operation );
        switch(udfc_env->env[conidx]->operation)
        {
            case UDFC_OP_DISCOVER:
            {
                uint8_t status = param->status;
                //prf_gatt_send_exchange_mtu(&udfc_env->prf_env,conidx,512);

                if (param->status == ATT_ERR_NO_ERROR)
                {
                    // check characteristic validity
                    if(udfc_env->env[conidx]->ats.nb_svc > 0)
                    {
                        TRACE("BLE: udfc discovered svc = %d\n",udfc_env->env[conidx]->ats.nb_svc);
                        status = GAP_ERR_NO_ERROR;
                    }
                    // no services found
                    else
                    {
                        status = PRF_ERR_STOP_DISC_CHAR_MISSING;
                    }
                }
                udfc_enable_rsp_send(udfc_env, conidx, status);
                if(status == GAP_ERR_NO_ERROR){
                    struct udfc_data_sent_ind * rsp = KE_MSG_ALLOC(UDFC_REG_NTF_PROCESS_DONE,
                            prf_dst_task_get(&(udfc_env->prf_env), conidx), dest_id, udfc_data_sent_ind);
                    // set error status
                    rsp->status =param->status;
                    rsp->conidx = conidx;
                    ke_msg_send(rsp);
                }
            }break;
            case UDFC_OP_WR_NTF_CFG:
            {
                struct udfc_data_sent_ind * rsp = KE_MSG_ALLOC(UDFC_NTF_CFG_RSP,
                        prf_dst_task_get(&(udfc_env->prf_env), conidx), dest_id, udfc_data_sent_ind);
                // set error status
                rsp->status =param->status;
                rsp->conidx = conidx;

                ke_msg_send(rsp);
            }break;
            case UDFC_OP_WR_IND_CFG:
            {
                struct udfc_data_sent_ind * rsp = KE_MSG_ALLOC(UDFC_INDICATION_CFG_RSP,
                        prf_dst_task_get(&(udfc_env->prf_env), conidx), dest_id, udfc_data_sent_ind);
                rsp->status =param->status;
                rsp->conidx = conidx;

                ke_msg_send(rsp);
            }break;
            case UDFC_OP_WR:
            {
                struct udfc_data_sent_ind * rsp = KE_MSG_ALLOC(UDFC_WR_RSP,
                        prf_dst_task_get(&(udfc_env->prf_env), conidx), dest_id, udfc_data_sent_ind);
                rsp->status =param->status;
                rsp->conidx = conidx;

                ke_msg_send(rsp);
            }break;
            case UDFC_OP_WR_NORES:
            {
                struct udfc_data_sent_ind * rsp = KE_MSG_ALLOC(UDFC_WR_NORES_RSP,
                        prf_dst_task_get(&(udfc_env->prf_env), conidx), dest_id, udfc_data_sent_ind);
                rsp->status =param->status;
                rsp->conidx = conidx;

                ke_msg_send(rsp);
            }break;
            case UDFC_OP_RD:
            {
                struct gattc_read_ind * rsp = KE_MSG_ALLOC(UDFC_RD_RSP,
                        prf_dst_task_get(&(udfc_env->prf_env), conidx), dest_id, gattc_read_ind);
                rsp->handle = 0;
                rsp->offset = 0;
                rsp->length = 0;
                ke_msg_send(rsp);
            }break;
            default:
            {
                // Not Expected at all
                ASSERT_ERR(0);
            }break;
        }

        // operation is over - go back to idle state
        udfc_env->env[conidx]->operation = UDFC_OP_NONE;
        ke_state_set(dest_id, UDFC_IDLE);
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

    if(state != UDFC_FREE)
    {
        // Retrieve environment data
        struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);
        uint8_t conidx = KE_IDX_GET(dest_id);

        // inform application 

        if (udfc_env->env[conidx] != NULL)
        {
                switch (param->type)
                {
                    case (GATTC_NOTIFY):
                    {
                        // Send an indication to the application
                        struct udfc_rx_data_ind *ind = KE_MSG_ALLOC_DYN(UDFC_NTF_IND,
                                prf_dst_task_get(&udfc_env->prf_env, conidx),
                                prf_src_task_get(&udfc_env->prf_env, conidx),
                                udfc_rx_data_ind,
                                param->length);
                        ind->conidx = conidx;
                        ind->handle = param->handle;
                        ind->length = param->length;
                        memcpy((uint8_t *)(ind->data), &(param->value), param->length);
                        
                        // Send the message
                        ke_msg_send(ind);
                    } break;
                    case (GATTC_INDICATE):
                    {
                        // confirm that indication has been correctly received
                        struct gattc_event_cfm * cfm = KE_MSG_ALLOC(GATTC_EVENT_CFM, src_id, dest_id, gattc_event_cfm);
                        cfm->handle = param->handle;
                        ke_msg_send(cfm);
            
                        // Check if we were waiting for the indication
                        //if (udfc_env->env[conidx]->operation != 0)
                        {
                            // Send an indication to the application
                            struct udfc_rx_data_ind *ind = KE_MSG_ALLOC_DYN(UDFC_INDICATION_IND,
                                    prf_dst_task_get(&udfc_env->prf_env, conidx),
                                    prf_src_task_get(&udfc_env->prf_env, conidx),
                                    udfc_rx_data_ind,
                                    param->length);
                            ind->handle = param->handle;
                            ind->length = param->length;
                            ind->conidx = conidx;
                            memcpy((uint8_t *)(ind->data), &(param->value), param->length);
                            
                            // Send the message
                            ke_msg_send(ind);
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
KE_MSG_HANDLER_TAB(udfc)
{
    {UDFC_ENABLE_REQ,               (ke_msg_func_t)udfc_enable_req_handler},
    {UDFC_DISCOVER_REQ,             (ke_msg_func_t)udfc_discover_req_handler},
    {GATTC_SDP_SVC_IND,             (ke_msg_func_t)gattc_sdp_svc_ind_handler},
    {UDFC_WR_REQ,                   (ke_msg_func_t)udfc_wr_req_handler},
    {UDFC_WR_NORES_REQ,             (ke_msg_func_t)udfc_wr_nores_req_handler},
    {UDFC_RD_REQ,                   (ke_msg_func_t)udfc_rd_req_handler},
    {UDFC_NTF_CFG_REQ,              (ke_msg_func_t)udfc_ntf_cfg_req_handler},
    {UDFC_INDICATION_CFG_REQ,       (ke_msg_func_t)udfc_ind_cfg_req_handler},
    {GATTC_CMP_EVT,                 (ke_msg_func_t)gattc_cmp_evt_handler},
    {GATTC_EVENT_IND,               (ke_msg_func_t)gattc_event_ind_handler},
    {GATTC_EVENT_REQ_IND,           (ke_msg_func_t)gattc_event_ind_handler},
    {GATTC_READ_IND,                (ke_msg_func_t)gattc_read_ind_handler},
};

void udfc_task_init(struct ke_task_desc *task_desc)
{
    // Get the address of the environment
    struct udfc_env_tag *udfc_env = PRF_ENV_GET(UDFC, udfc);

    task_desc->msg_handler_tab = udfc_msg_handler_tab;
    task_desc->msg_cnt         = ARRAY_LEN(udfc_msg_handler_tab);
    task_desc->state           = udfc_env->state;
    task_desc->idx_max         = UDFC_IDX_MAX;
}

#endif /* #if (BLE_UDF_CLIENT) */

/// @} UDFCTASK
