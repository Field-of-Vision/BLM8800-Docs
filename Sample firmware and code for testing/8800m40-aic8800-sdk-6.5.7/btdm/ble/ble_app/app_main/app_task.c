/**
 ****************************************************************************************
 *
 * @file appm_task.c
 *
 * @brief RW APP Task implementation
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APPTASK
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"          // SW configuration
#include "rwble_hl_config.h"

#if (BLE_APP_PRESENT)

#include "app_task.h"             // Application Manager Task API
#include "app.h"                  // Application Manager Definition
#include "gapc_task.h"            // GAP Controller Task API
#include "gapm_task.h"            // GAP Manager Task API
#include "arch.h"                 // Platform Definitions
#include <string.h>
#include "ble_utils.h"
#include "ke_timer.h"             // Kernel timer
#include "aicble.h"
#include "gattc_task.h"

#if (BLE_APP_SEC)
#include "app_sec.h"              // Security Module Definition
#endif //(BLE_APP_SEC)

#if (BLE_APP_HT)
#include "app_ht.h"               // Health Thermometer Module Definition
#include "htpt_task.h"
#endif //(BLE_APP_HT)

#if (BLE_APP_DIS)
#include "app_dis.h"              // Device Information Module Definition
#include "diss_task.h"
#endif //(BLE_APP_DIS)

#if (BLE_APP_BATT)
#include "app_batt.h"             // Battery Module Definition
#include "bass_task.h"
#endif //(BLE_APP_BATT)

#if (BLE_APP_HID)
#include "app_hid.h"              // HID Module Definition
#include "hogpd_task.h"
#endif //(BLE_APP_HID)

#if (BLE_APP_SMARTCONFIG)
#include "app_smartconfig.h"      // Smart Config Module Definition
#include "smartconfig_task.h"
#endif // (BLE_APP_SMARTCONFIG)

#if (BLE_APP_AUDTRANSMITS)
#include "app_audtransmits.h"     // Aud Transmit Server Module Definition
#include "audtransmits_task.h"
#endif // (BLE_APP_AUDTRANSMITS)

#if (BLE_APP_AUDTRANSMITC)
#include "app_audtransmitc.h"     // Aud Transmit Client Module Definition
#include "audtransmitc_task.h"
#endif // (BLE_APP_AUDTRANSMITC)

#if (BLE_APP_UDFS)
#include "app_udfs.h"     // Aud Transmit Server Module Definition
#include "udfs_task.h"
#endif // (BLE_APP_UDFS)

#if (BLE_APP_UDFC)
#include "app_udfc.h"     // Aud Transmit Client Module Definition
#include "udfc_task.h"
#endif // (BLE_APP_UDFC)

#include "flash_api_btdm.h"
#include "sleep_api.h"
#include "hw_cfg_api.h"
#if PLF_M2D_BLE
#include "app_m2d_ble.h"
#endif
#if PLF_BLE_WAKEUP
#include "app_ble_wakeup.h"
#endif
#include "app_ble_queue.h"
/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

static uint8_t app_get_handler(const struct app_subtask_handlers *handler_list_desc,
                               ke_msg_id_t msgid,
                               void *param,
                               ke_task_id_t src_id)
{
    // Counter
    uint8_t counter;

    // Get the message handler function by parsing the message table
    for (counter = handler_list_desc->msg_cnt; 0 < counter; counter--)
    {
        struct ke_msg_handler handler
                = (struct ke_msg_handler)(*(handler_list_desc->p_msg_handler_tab + counter - 1));

        if ((handler.id == msgid) ||
            (handler.id == KE_MSG_DEFAULT_HANDLER))
        {
            // If handler is NULL, message should not have been received in this state
            ASSERT_ERR(handler.func);

            return (uint8_t)(handler.func(msgid, param, TASK_APP, src_id));
        }
    }

    // If we are here no handler has been found, drop the message
    return (KE_MSG_CONSUMED);
}

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Handles GAPM_ACTIVITY_CREATED_IND event
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance.
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapm_activity_created_ind_handler(ke_msg_id_t const msgid,
                                             struct gapm_activity_created_ind const *p_param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    if (app_env.adv_state == APP_ADV_STATE_CREATING)
    {
        // Store the advertising activity index
        app_env.adv_actv_idx = p_param->actv_idx;
        dbg("%s ,adv_actv_idx = %x\n",__func__,app_env.adv_actv_idx);
    }

    if (app_env.scan_state == APP_SCAN_STATE_CREATING)
    {
        // Store the scan activity index
        app_env.scan_actv_idx = p_param->actv_idx;
        dbg("%s ,scan_actv_idx = %x\n",__func__,app_env.scan_actv_idx);
    }

    if (app_env.init_state == APP_INIT_STATE_CREATING)
    {
        // Store the init activity index
        app_env.init_actv_idx = p_param->actv_idx;
        dbg("%s ,init_actv_idx = %x\n",__func__,app_env.init_actv_idx);
    }

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles GAPM_ACTIVITY_STOPPED_IND event.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance.
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapm_activity_stopped_ind_handler(ke_msg_id_t const msgid,
                                             struct gapm_activity_stopped_ind const *p_param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    if (app_env.adv_state == APP_ADV_STATE_STARTED && p_param->actv_type == GAPM_ACTV_TYPE_ADV)
    {
        // Act as if activity had been stopped by the application
        app_env.adv_state = APP_ADV_STATE_STOPPING;
        dbg("## %s app_env.adv_state %d\r\n", __func__, app_env.adv_state);

        #if (!BLE_APP_SMARTCONFIG)
        // Perform next operation
        appm_adv_fsm_next();
        #else
        user_sleep_allow(0);
        #endif // !BLE_APP_SMARTCONFIG
    }
    if (app_env.scan_state == APP_SCAN_STATE_STARTED && p_param->actv_type == GAPM_ACTV_TYPE_SCAN)
    {
        // Act as if activity had been stopped by the application
        app_env.scan_state = APP_SCAN_STATE_STOPPING;
        dbg("## %s app_env.scan_state %d\r\n", __func__, app_env.scan_state);

    #if (!BLE_APP_SMARTCONFIG)
        // Perform next operation
        appm_scan_fsm_next();
    #else
        user_sleep_allow(0);
    #endif // !BLE_APP_SMARTCONFIG
    }

    if (app_env.adv_state == APP_ADV_STATE_STOPPING)
    {
        dbg("ble_callback 0x%x\r\n",ble_callback);
        if (ble_callback) {
            app_ble_adv_disabled_msg_send(p_param->reason);
        }
    }

    if (app_env.scan_state == APP_SCAN_STATE_STOPPING)
    {
        dbg("ble_callback 0x%x\r\n",ble_callback);
        if (ble_callback) {
            app_ble_scan_disabled_msg_send(p_param->reason);
        }
    }
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles GAPM_PROFILE_ADDED_IND event
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance.
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapm_profile_added_ind_handler(ke_msg_id_t const msgid,
                                          struct gapm_profile_added_ind *param,
                                          ke_task_id_t const dest_id,
                                          ke_task_id_t const src_id)
{
    // Current State
    ke_state_t state = ke_state_get(dest_id);
    dbg("%s\n",__func__);
    if (state == APPM_CREATE_DB || state == APPM_READY)
    {
        switch (param->prf_task_id)
        {
            default: /* Nothing to do */ break;
        }
    }
    else
    {
        ASSERT_INFO(0, state, src_id);
    }

    return KE_MSG_CONSUMED;
}

/**
 ****************************************************************************************
 * @brief Handles GAP manager command complete events.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapm_cmp_evt_handler(ke_msg_id_t const msgid,
                                struct gapm_cmp_evt const *param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id)
{
    uint8_t need_do_process = 0;
    uint8_t need_clean_op = 0;

    switch(param->operation)
    {
        // Reset completed
        case (GAPM_RESET):
        {

            if(param->status == GAP_ERR_NO_ERROR)
            {
                #if (BLE_APP_HID)
                app_hid_start_mouse();
                #endif //(BLE_APP_HID)

                // Set Device configuration
                struct gapm_set_dev_config_cmd* cmd = KE_MSG_ALLOC(GAPM_SET_DEV_CONFIG_CMD,
                                                                   TASK_GAPM, TASK_APP,
                                                                   gapm_set_dev_config_cmd);
                // Set the operation
                cmd->operation = GAPM_SET_DEV_CONFIG;
                // Set the device role - Peripheral
                cmd->role      = GAP_ROLE_ALL;

                #if (BLE_APP_SEC_CON)
                // The Max MTU is increased to support the Public Key exchange
                // HOWEVER, with secure connections enabled you cannot sniff the
                // LEAP and LEAS protocols
                cmd->max_mtu = 160;
                cmd->pairing_mode = GAPM_PAIRING_SEC_CON | GAPM_PAIRING_LEGACY;
                #else // !(BLE_APP_SEC_CON)
                // Do not support secure connections
                cmd->pairing_mode = GAPM_PAIRING_LEGACY;
                cmd->max_mtu = 512;
                //cmd->att_cfg = 0;
                cmd->att_cfg |= GAPM_MASK_ATT_SVC_CHG_EN;
                #endif //(BLE_APP_SEC_CON)

                // Set Data length parameters
                cmd->sugg_max_tx_octets = BLE_MIN_OCTETS;
                cmd->sugg_max_tx_time   = BLE_MIN_TIME;

                #if (BLE_APP_HID)
                // Enable Slave Preferred Connection Parameters present
                cmd->att_cfg |= GAPM_MASK_ATT_SLV_PREF_CON_PAR_EN;
                #endif //(BLE_APP_HID)

                // Host privacy enabled by default
                cmd->privacy_cfg = GAPM_PRIV_CFG_PRIV_ADDR_BIT;


                memcpy(&cmd->addr.addr[0], &ble_user_info.own_addr.addr[0], BD_ADDR_LEN);

                if (app_sec_get_bond_status()==true) {
                    flash_btdm_le_loc_irk_read((uint8_t *)&app_env.loc_irk);
                    memcpy(cmd->irk.key, app_env.loc_irk, 16);
                }
                else
                {
                    memset((void *)&cmd->irk.key[0], 0x00, KEY_LEN);
                }

                #if BLE_APP_AUDTRANSMITS || BLE_APP_AUDTRANSMITC
                cmd->tx_pref_phy = GAP_PHY_LE_CODED;
                cmd->rx_pref_phy = GAP_PHY_LE_CODED;
                #else
                cmd->tx_pref_phy = GAP_PHY_ANY;
                cmd->rx_pref_phy = GAP_PHY_ANY;
                #endif
                // Send message
                ke_msg_send(cmd);
            }
            else
            {
                ASSERT_ERR(0);
            }
        }
        break;

        case (GAPM_PROFILE_TASK_ADD):
        {
            if (app_sec_get_bond_status()==true)
            {
                flash_btdm_le_loc_irk_read((uint8_t *)&app_env.loc_irk);
                // Set the IRK in the GAP
                struct gapm_set_irk_cmd *cmd = KE_MSG_ALLOC(GAPM_SET_IRK_CMD,
                                                            TASK_GAPM, TASK_APP,
                                                            gapm_set_irk_cmd);
                ///  - GAPM_SET_IRK:
                cmd->operation = GAPM_SET_IRK;
                memcpy(&cmd->irk.key[0], &app_env.loc_irk[0], KEY_LEN);
                ke_msg_send(cmd);
            }
            else // Need to start the generation of new IRK
            {
                struct gapm_gen_rand_nb_cmd *cmd = KE_MSG_ALLOC(GAPM_GEN_RAND_NB_CMD,
                                                                TASK_GAPM, TASK_APP,
                                                                gapm_gen_rand_nb_cmd);
                cmd->operation   = GAPM_GEN_RAND_NB;
                app_env.rand_cnt = 1;
                ke_msg_send(cmd);
            }
        }
        break;

        case (GAPM_GEN_RAND_NB) :
        {
            if (app_env.rand_cnt == 1)
            {
                // Generate a second random number
                app_env.rand_cnt++;
                struct gapm_gen_rand_nb_cmd *cmd = KE_MSG_ALLOC(GAPM_GEN_RAND_NB_CMD,
                                                                TASK_GAPM, TASK_APP,
                                                                gapm_gen_rand_nb_cmd);
                cmd->operation = GAPM_GEN_RAND_NB;
                ke_msg_send(cmd);
            }
            else
            {
                struct gapm_set_irk_cmd *cmd = KE_MSG_ALLOC(GAPM_SET_IRK_CMD,
                                                        TASK_GAPM, TASK_APP,
                                                        gapm_set_irk_cmd);
                app_env.rand_cnt=0;
                ///  - GAPM_SET_IRK
                cmd->operation = GAPM_SET_IRK;
                memcpy(&cmd->irk.key[0], &app_env.loc_irk[0], KEY_LEN);
                ke_msg_send(cmd);
            }
        }
        break;

        case (GAPM_SET_IRK):
        {
            // ASSERT_INFO(param->status == GAP_ERR_NO_ERROR, param->operation, param->status);

            // If not Bonded already store the generated value in NVDS
            if (app_sec_get_bond_status()==false)
            {
                flash_btdm_le_loc_irk_write((uint8_t *)&app_env.loc_irk);
            }

            app_env.rand_cnt = 0;
            // Add the next requested service
            if (ke_state_get(TASK_APP) == APPM_CREATE_DB && !appm_add_svc())
            {
                bool ret = false;
                // Go to the ready state
                ke_state_set(TASK_APP, APPM_READY);
                if (ble_user_info.user_app_callback->app_on_init_complete) {
                    ret = ble_user_info.user_app_callback->app_on_init_complete();
                }
                if(!ret){
                    #if BLE_DFT_STATE_ADV
                    // No more service to add, start advertising
                    appm_update_adv_state(true);
                    #endif
                    #if BLE_DFT_STATE_SCAN
                    // No more service to add, start scan
                    appm_update_scan_state(true);
                    #endif
                    #if BLE_DFT_STATE_INIT
                    // No more service to add, start init
                    appm_update_init_state(true);
                    #endif
                }
            }
        }
        break;

        // Device Configuration updated
        case (GAPM_SET_DEV_CONFIG):
        {
            bool ret = false;
            ASSERT_INFO(param->status == GAP_ERR_NO_ERROR, param->operation, param->status);

            // Go to the create db state
            ke_state_set(TASK_APP, APPM_CREATE_DB);

            // Add the first required service in the database
            // and wait for the PROFILE_ADDED_IND
            ret = appm_add_svc();
            if(ret == false){
                if (ble_user_info.user_app_callback->app_on_init_complete) {
                    ble_user_info.user_app_callback->app_on_init_complete();
                }
            }
        }
        break;

        case (GAPM_CREATE_ADV_ACTIVITY):
        case (GAPM_CREATE_SCAN_ACTIVITY):
        case (GAPM_CREATE_INIT_ACTIVITY):
        case (GAPM_STOP_ACTIVITY):
        case (GAPM_START_ACTIVITY):
        case (GAPM_SET_ADV_DATA):
        case (GAPM_SET_SCAN_RSP_DATA):
        {
            dbg("%s op 0x%x, adv_op %x, scan_op %x,init_op %x\n",__func__,param->operation,app_env.adv_op,app_env.scan_op,app_env.init_op);
            if(app_env.adv_op != GAPM_NO_OP){
                if ((app_env.adv_op != param->operation) || (param->status != GAP_ERR_NO_ERROR)) {
                    ASSERT_INFO(app_env.adv_op == param->operation, app_env.adv_op, param->operation);
                    ASSERT_INFO(param->status == GAP_ERR_NO_ERROR, param->status, app_env.adv_op);
                    dbg("error, adv operation error, operation %x-%x, status %x\r\n", param->operation, app_env.adv_op, param->status);
                    if (ble_user_info.user_app_callback->app_on_adv_status) {
                        ble_user_info.user_app_callback->app_on_adv_status(param);
                    }
                    if(app_env.adv_op == param->operation){
                        need_clean_op |= 1;
                    }
                } else {
                    // Perform next operation
                    need_do_process |= 1;
                    need_clean_op |= 1;
                }
            }
            if(app_env.scan_op != GAPM_NO_OP){
                if ((app_env.scan_op != param->operation) || (param->status != GAP_ERR_NO_ERROR)) {
                    ASSERT_INFO(app_env.scan_op == param->operation, app_env.scan_op, param->operation);
                    ASSERT_INFO(param->status == GAP_ERR_NO_ERROR, param->status, app_env.scan_op);
                    dbg("error, scan operation error, operation %x-%x, status %x\r\n", param->operation, app_env.scan_op, param->status);
                    if(app_env.scan_op == param->operation){
                        need_clean_op |= (1<<1);
                    }
                } else {
                    // Perform next operation
                    need_do_process |= (1<<1);
                    need_clean_op |= (1<<1);
                }
            }
            if(app_env.init_op != GAPM_NO_OP){
                if ((app_env.init_op != param->operation) || (param->status != GAP_ERR_NO_ERROR)) {
                    ASSERT_INFO(app_env.init_op == param->operation, app_env.init_op, param->operation);
                    ASSERT_INFO(param->status == GAP_ERR_NO_ERROR, param->status, app_env.init_op);
                    dbg("error, init operation error, operation %x-%x, status %x\r\n", param->operation, app_env.init_op, param->status);
                    if(app_env.init_op == param->operation){
                        need_clean_op |= (1<<2);
                    }
                } else {
                    // Perform next operation
                    need_do_process |= (1<<2);
                    need_clean_op |= (1<<2);
                }
            }
        } break;
        case (GAPM_DELETE_ACTIVITY) :
        case (GAPM_DELETE_ALL_ACTIVITIES) :
        {
            // Re-Invoke Advertising
            if(app_env.adv_state != APP_ADV_STATE_IDLE){
                app_env.adv_state = APP_ADV_STATE_IDLE;
                need_do_process |= (1<<0);
                need_clean_op   |= (1<<0);
            }
            // Re-Invoke Scan
            if(app_env.adv_state != APP_SCAN_STATE_IDLE){
                app_env.adv_state = APP_SCAN_STATE_IDLE;
                need_do_process |= (1<<1);
                need_clean_op   |= (1<<1);
            }
        } break;


        default:
        {
            // Drop the message
            need_clean_op = 0;
        }
        break;
    }
    //dbg("%s ,op 0x%x,  0x%x,0x%x,%x\n",__func__,param->operation,need_clean_op,need_do_process,app_env.adv_state);
    if(need_clean_op){
        if(need_clean_op & (1<<2)){
            app_env.init_op = GAPM_NO_OP;
        }
        if(need_clean_op & (1<<1)){
            app_env.scan_op = GAPM_NO_OP;
        }
        if(need_clean_op & (1<<0)){
            app_env.adv_op = GAPM_NO_OP;
        }
    }
    if(need_do_process){
        if(need_do_process & (1<<2)){
            appm_init_fsm_next();
        }
        if(need_do_process & (1<<1)){
            appm_scan_fsm_next();
        }
        if(need_do_process & (1<<0)){
            appm_adv_fsm_next();
        }
    }else{
        app_ble_check_oplist();
    }
    if(param->operation == GAPM_START_ACTIVITY){
        //ke_timer_set(APP_TEST_TIMER, TASK_APP, 1000);
    }
    return (KE_MSG_CONSUMED);
}

static int gapc_get_dev_info_req_ind_handler(ke_msg_id_t const msgid,
        struct gapc_get_dev_info_req_ind const *param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id)
{
    switch(param->req)
    {
        case GAPC_DEV_NAME:
        {
            struct gapc_get_dev_info_cfm * cfm = KE_MSG_ALLOC_DYN(GAPC_GET_DEV_INFO_CFM,
                                                    src_id, dest_id,
                                                    gapc_get_dev_info_cfm, APP_DEVICE_NAME_MAX_LEN);
            cfm->req = param->req;
            cfm->info.name.length = appm_get_dev_name(cfm->info.name.value);

            // Send message
            ke_msg_send(cfm);
        } break;

        case GAPC_DEV_APPEARANCE:
        {
            // Allocate message
            struct gapc_get_dev_info_cfm *cfm = KE_MSG_ALLOC(GAPC_GET_DEV_INFO_CFM,
                                                             src_id, dest_id,
                                                             gapc_get_dev_info_cfm);
            cfm->req = param->req;
            // Set the device appearance
            #if (BLE_APP_HT)
            // Generic Thermometer
            cfm->info.appearance = GAPC_APPEARANCE_GENERIC_THERMOMETER;
            #elif (BLE_APP_HID)
            // HID Mouse
            cfm->info.appearance = GAPC_APPEARANCE_HID_MOUSE;
            #else
            // No appearance
            cfm->info.appearance = GAPC_APPEARANCE_UNKNOWN;
            #endif

            // Send message
            ke_msg_send(cfm);
        } break;

        case GAPC_DEV_SLV_PREF_PARAMS:
        {
            // Allocate message
            struct gapc_get_dev_info_cfm *cfm = KE_MSG_ALLOC(GAPC_GET_DEV_INFO_CFM,
                    src_id, dest_id,
                                                            gapc_get_dev_info_cfm);
            cfm->req = param->req;
            // Slave preferred Connection interval Min
            cfm->info.slv_pref_params.con_intv_min = 8;
            // Slave preferred Connection interval Max
            cfm->info.slv_pref_params.con_intv_max = 10;
            // Slave preferred Connection latency
            cfm->info.slv_pref_params.slave_latency  = 0;
            // Slave preferred Link supervision timeout
            cfm->info.slv_pref_params.conn_timeout    = 200;  // 2s (500*10ms)

            // Send message
            ke_msg_send(cfm);
        } break;

        default: /* Do Nothing */ break;
    }

    return (KE_MSG_CONSUMED);
}
/**
 ****************************************************************************************
 * @brief Handles GAPC_SET_DEV_INFO_REQ_IND message.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_set_dev_info_req_ind_handler(ke_msg_id_t const msgid,
        struct gapc_set_dev_info_req_ind const *param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id)
{
    uint8_t status = GAP_ERR_REJECTED;

    appm_set_dev_info(param, &status);

    // Set Device configuration
    struct gapc_set_dev_info_cfm* cfm = KE_MSG_ALLOC(GAPC_SET_DEV_INFO_CFM, src_id, dest_id,
                                                     gapc_set_dev_info_cfm);
    // Reject to change parameters
    cfm->status = status;
    cfm->req = param->req;
    // Send message
    ke_msg_send(cfm);

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles connection complete event from the GAP. Enable all required profiles
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_connection_req_ind_handler(ke_msg_id_t const msgid,
                                           struct gapc_connection_req_ind const *param,
                                           ke_task_id_t const dest_id,
                                           ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    // Check if the received Connection Handle was valid
    if (conidx != GAP_INVALID_CONIDX)
    {
        // Retrieve the connection info from the parameters
        app_env.conhdl[conidx] = param->conhdl;
        dbg("%s ,con_interval %d,con_latency %d,sup_to %d\n",__func__,param->con_interval,param->con_latency,param->sup_to);
        // Send connection confirmation
        struct gapc_connection_cfm *cfm = KE_MSG_ALLOC(GAPC_CONNECTION_CFM,
                KE_BUILD_ID(TASK_GAPC, conidx), TASK_APP,
                gapc_connection_cfm);

        #if(BLE_APP_SEC)
        cfm->auth      = app_sec_get_bond_status() ? GAP_AUTH_REQ_NO_MITM_BOND : GAP_AUTH_REQ_NO_MITM_NO_BOND; // TODO [FBE] restore valid data
        #else // !(BLE_APP_SEC)
        cfm->auth      = GAP_AUTH_REQ_NO_MITM_NO_BOND;
        #endif // (BLE_APP_SEC)
        // Send the message
        ke_msg_send(cfm);

        /*--------------------------------------------------------------
         * ENABLE REQUIRED PROFILES
         *--------------------------------------------------------------*/
        if (ble_user_info.user_app_callback->app_on_enable_prf) {
            ble_user_info.user_app_callback->app_on_enable_prf(conidx,param->role);
        }
        // We are now in connected State
        ke_state_set(KE_BUILD_ID(TASK_APP, conidx), APPM_CONNECTED);

        #if 0//(BLE_APP_SEC)
        if (app_sec_get_bond_status())
        {
            // Ask for the peer device to either start encryption
            app_sec_send_security_req(conidx);
        }
        #endif // (BLE_APP_SEC )

    }
    else
    {
        // No connection has been established, restart advertising
        appm_update_adv_state(true);
    }

    if (ble_user_info.user_app_callback->app_on_connection) {
        ble_user_info.user_app_callback->app_on_connection(conidx, param);
    }
    if (app_env.init_state == APP_INIT_STATE_STARTED) {
        app_env.init_state = APP_INIT_STATE_CREATED;
    }
    struct ble_connection_ind ind;
    ind.conidx = conidx;
    memcpy(&ind.ind,param,sizeof(struct gapc_connection_req_ind));
    app_user_cb_poll(GAPC_CONNECTION_REQ_IND,(uint8_t *)&ind);
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles connection complete event from the GAP. Enable all required profiles
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_param_update_req_ind_handler(ke_msg_id_t const msgid,
                                           struct gapc_param_update_req_ind const *param,
                                           ke_task_id_t const dest_id,
                                           ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    // Check if the received Connection Handle was valid
    if (conidx != GAP_INVALID_CONIDX)
    {
        struct ble_param_update_req_ind ind;
        ind.conidx = conidx;
        memcpy(&ind.rmt_req,param,sizeof(struct gapc_param_update_req_ind));
        app_user_cb_poll(GAPC_PARAM_UPDATE_REQ_IND,(uint8_t *)&ind);

        // Send connection confirmation
        struct gapc_param_update_cfm *cfm = KE_MSG_ALLOC(GAPC_PARAM_UPDATE_CFM,
                KE_BUILD_ID(TASK_GAPC, conidx), TASK_APP,
                gapc_param_update_cfm);

        cfm->accept = ind.usr_cfm.accept;//true;
        cfm->ce_len_min = ind.usr_cfm.ce_len_min;//2;
        cfm->ce_len_max = ind.usr_cfm.ce_len_max;//4;

        // Send message
        ke_msg_send(cfm);

    }
    else
    {
        // No connection has been established, restart advertising
        appm_update_adv_state(true);
    }

    if (ble_user_info.user_app_callback->app_on_update_params_request) {
        ble_user_info.user_app_callback->app_on_update_params_request(param);
    }

    return (KE_MSG_CONSUMED);
}

/**
****************************************************************************************
* @brief Handles connection param update complete event from the GAP. Enable all required profiles
*
* @param[in] msgid     Id of the message received.
* @param[in] param     Pointer to the parameters of the message.
* @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
* @param[in] src_id    ID of the sending task instance.
*
* @return If the message was consumed or not.
****************************************************************************************
*/
static int gapc_param_update_ind_handler(ke_msg_id_t const msgid,
                                          struct gapc_param_updated_ind const *param,
                                          ke_task_id_t const dest_id,
                                          ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);
    struct ble_param_updated_ind ind;
    TRACE("%s, conidx %d, con_interval %d,con_latency %d,sup_to %d\n",__func__,conidx,param->con_interval,param->con_latency,param->sup_to);
    ind.conidx = conidx;
    memcpy(&ind.ind,param,sizeof(struct gapc_param_updated_ind));
    app_user_cb_poll(GAPC_PARAM_UPDATED_IND,(uint8_t *)&ind);

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles GAP controller command complete events.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_cmp_evt_handler(ke_msg_id_t const msgid,
                                struct gapc_cmp_evt const *param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id)
{
    switch(param->operation)
    {
        case (GAPC_UPDATE_PARAMS):
        {
            if (param->status != GAP_ERR_NO_ERROR)
            {
                //uint8_t conidx = KE_IDX_GET(src_id);
//                appm_disconnect(conidx);
            }
        } break;

        default:
        {
        } break;
    }

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles disconnection complete event from the GAP.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_disconnect_ind_handler(ke_msg_id_t const msgid,
                                      struct gapc_disconnect_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);
    bool all_disconnected = true;
    // Go to the ready state
    ke_state_set(KE_BUILD_ID(TASK_APP, conidx), APPM_READY);

    #if (BLE_APP_HT)
    // Stop interval timer
    app_stop_timer();
    #endif //(BLE_APP_HT)

    if (ble_user_info.user_app_callback->app_on_disconnect) {
        ble_user_info.user_app_callback->app_on_disconnect(param,conidx);
    }

    app_env.conhdl[conidx] = 0;
    struct ble_disconnect_ind ind;
    ind.conidx = conidx;
    memcpy(&ind.ind,param,sizeof(struct gapc_disconnect_ind));
    app_user_cb_poll(GAPC_DISCONNECT_IND,(uint8_t *)&ind);

    for(uint8_t i = 0;i < APP_IDX_MAX;i++){
        if(ke_state_get(KE_BUILD_ID(TASK_APP,i)) == APPM_CONNECTED){
            all_disconnected = false;
        }
    }
    if(all_disconnected){
        if (ble_callback) {
            app_ble_con_disabled_msg_send(GAP_ERR_NO_ERROR);
        }
    }
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of all messages sent from the lower layers to the application
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int appm_msg_handler(ke_msg_id_t const msgid,
                            void *param,
                            ke_task_id_t const dest_id,
                            ke_task_id_t const src_id)
{
    // Retrieve identifier of the task from received message
    ke_task_id_t src_task_id = BLE_MSG_T(msgid);
    // Message policy
    uint8_t msg_pol = KE_MSG_CONSUMED;

    switch (src_task_id)
    {
        case (TASK_ID_GAPC):
        {
            #if (BLE_APP_SEC)
            if ((msgid >= GAPC_BOND_CMD) &&
                (msgid <= GAPC_SECURITY_IND))
            {
                // Call the Security Module
                msg_pol = app_get_handler(&app_sec_handlers, msgid, param, src_id);
            }
            #endif //(BLE_APP_SEC)
            // else drop the message
        } break;

        case (TASK_ID_GATTC):
        {
            // Service Changed - Drop
        } break;

        #if (BLE_APP_HT)
        case (TASK_ID_HTPT):
        {
            // Call the Health Thermometer Module
            msg_pol = app_get_handler(&app_ht_handlers, msgid, param, src_id);
        } break;
        #endif //(BLE_APP_HT)

        #if (BLE_APP_DIS)
        case (TASK_ID_DISS):
        {
            // Call the Device Information Module
            msg_pol = app_get_handler(&app_dis_handlers, msgid, param, src_id);
        } break;
        #endif //(BLE_APP_DIS)

        #if (BLE_APP_HID)
        case (TASK_ID_HOGPD):
        {
            // Call the HID Module
            msg_pol = app_get_handler(&app_hid_handlers, msgid, param, src_id);
        } break;
        #endif //(BLE_APP_HID)

        #if (BLE_APP_BATT)
        case (TASK_ID_BASS):
        {
            // Call the Battery Module
            msg_pol = app_get_handler(&app_batt_handlers, msgid, param, src_id);
        } break;
        #endif //(BLE_APP_BATT)

        #if (BLE_APP_SMARTCONFIG)
        case (TASK_ID_SMARTCONFIG):
        {
            // Call the Smart Config
            msg_pol = app_get_handler(&app_smartconfig_handlers, msgid, param, src_id);
        } break;
        #endif //(BLE_APP_SMARTCONFIG)

        #if (BLE_APP_AUDTRANSMITS)
        case (TASK_ID_AUDTRANSMITS):
        {
            // Call the Aud transmit Server
            msg_pol = app_get_handler(&app_audtransmits_handlers, msgid, param, src_id);
        } break;
        #endif //(BLE_APP_AUDTRANSMITS)

        #if (BLE_APP_AUDTRANSMITC)
        case (TASK_ID_AUDTRANSMITC):
        {
            // Call the Aud transmit Client
            msg_pol = app_get_handler(&app_audtransmitc_handlers, msgid, param, src_id);
        } break;
        #endif //(BLE_APP_AUDTRANSMITC)

        #if (BLE_APP_UDFC)
        case (TASK_ID_UDFC):
        {
            // Call the Aud transmit Client
            msg_pol = app_get_handler(&app_udfc_handlers, msgid, param, src_id);
        } break;
        #endif //(BLE_APP_UDFC)

        default:
        {
            #if (BLE_APP_HT)
            if (msgid == APP_HT_MEAS_INTV_TIMER)
            {
                msg_pol = app_get_handler(&app_ht_handlers, msgid, param, src_id);
            }
            #endif //(BLE_APP_HT)

            #if (BLE_APP_HID)
            if (msgid == APP_HID_MOUSE_TIMEOUT_TIMER || msgid == APP_HID_MOUSE_TEST_TIMER)
            {
                msg_pol = app_get_handler(&app_hid_handlers, msgid, param, src_id);
            }
            #endif //(BLE_APP_HID)
        } break;
    }

    return (msg_pol);
}

/**
 ****************************************************************************************
 * @brief Handles reception of random number generated message
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapm_gen_rand_nb_ind_handler(ke_msg_id_t const msgid, struct gapm_gen_rand_nb_ind *param,
                                        ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    if (app_env.rand_cnt==1)      // First part of IRK
    {
        memcpy(&app_env.loc_irk[0], &param->randnb.nb[0], 8);
    }
    else if (app_env.rand_cnt==2) // Second part of IRK
    {
        memcpy(&app_env.loc_irk[8], &param->randnb.nb[0], 8);
    }

    return KE_MSG_CONSUMED;
}

/**
 ****************************************************************************************
 * @brief Function called when the APP_HID_MOUSE_TEST_TIMER expires.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int app_test_timer_handler(ke_msg_id_t const msgid,
                                               void const *param,
                                               ke_task_id_t const dest_id,
                                               ke_task_id_t const src_id)
{
    uint32_t timer_val = 1000;
    dbg("%s ,%d\n",__func__,ke_time());
    ke_timer_set(APP_TEST_TIMER, TASK_APP, timer_val);

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Function called when the APP_HID_MOUSE_TEST_TIMER expires.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int app_adv_report_handler(ke_msg_id_t const msgid,
                                               struct gapm_ext_adv_report_ind *param,
                                               ke_task_id_t const dest_id,
                                               ke_task_id_t const src_id)
{
    #if 0//BLE_APP_UDFC
    dbg("%s \n",__func__);
    dbg("actv_idx %x, info %x\n",param->actv_idx,param->info);
    dbg("trans_addr.addr_type %x, addr %x,%x,%x,%x,%x,%x \n",param->trans_addr.addr_type,param->trans_addr.addr.addr[0],param->trans_addr.addr.addr[1]\
        ,param->trans_addr.addr.addr[2],param->trans_addr.addr.addr[3],param->trans_addr.addr.addr[4],param->trans_addr.addr.addr[5]);
    dbg("target_addr.addr_type %x, addr %x,%x,%x,%x,%x,%x \n",param->target_addr.addr_type,param->target_addr.addr.addr[0],param->target_addr.addr.addr[1]\
        ,param->target_addr.addr.addr[2],param->target_addr.addr.addr[3],param->target_addr.addr.addr[4],param->target_addr.addr.addr[5]);
    dbg("tx_pwr %x, rssi %d,phy_prim %x, phy_prim %x,phy_second %x,adv_sid %x,period_adv_intv %x\n"\
        ,param->tx_pwr,param->rssi,param->phy_prim,param->phy_second,param->adv_sid,param->period_adv_intv);
    dbg("length %d,data ",param->length);
    for(uint8_t i=0;i<param->length;i++){
        dbg("%x, ",param->data[i]);
    }
    dbg("\n ");
    #endif
    uint16_t total_len = param->length;
    uint8_t *data;
    uint8_t ele_len;
    uint8_t ele_type;
    uint8_t *ele_data;
    #if PLF_BLE_WAKEUP
    uint8_t ad_role_complete[MAX_ROLE_COMBO_IDX_NUM] = {0,0};
    uint8_t ad_role_combo_idx = 0xff;
    uint8_t gpio_trigger_idx[MAX_ROLE_COMBO_IDX_NUM] = {0,0};
    #endif
    data = param->data;
    while(total_len){
        ele_len = data[0];
        ele_type = data[1];
        ele_data = &data[2];
        //dbg("ele_type=0x%x,ele_len=%d\n",ele_type,ele_len);

        #if PLF_BLE_WAKEUP
        ble_wakeup_param_t *ble_wakeup_user = app_ble_wakeup_get_param();
        if(ble_wakeup_user->magic_num == BLE_WAKEUP_MAGIC_NUM){
            for(uint8_t i=0;i<BLE_AD_FILTER_NUM_MAX;i++){
                if(ble_wakeup_user->ad_filter[i].ad_len>0 && ble_wakeup_user->ad_filter[i].ad_data_mask){
                    if(ele_type == ble_wakeup_user->ad_filter[i].ad_type && ele_len == ble_wakeup_user->ad_filter[i].ad_len){
                        bool need_wakeup = true;
                        bool mask_is_valid = false;
                        uint32_t data_mask = ble_wakeup_user->ad_filter[i].ad_data_mask;
                        uint8_t ad_role = ble_wakeup_user->ad_filter[i].ad_role;
                        dbg("ele_type=0x%x,ele_len=%d,data_mask=0x%x,ad_role=%d\n",ele_type,ele_len,data_mask,ad_role);
                        for(uint8_t j=0;j<ele_len-1;j++){
                            if((data_mask<<j)&0x80000000){
                                mask_is_valid = true;
                                if(ele_data[j] != ble_wakeup_user->ad_filter[i].ad_data[j]){
                                    need_wakeup = false;
                                    dbg("ele_data[%d]:0x%x  ad_data[%d]:0x%x \n",j,ele_data[j],j,ble_wakeup_user->ad_filter[i].ad_data[j]);
                                }else{
                                    dbg("ele_data[%d]:0x%x  ad_data[%d]:0x%x \n",j,ele_data[j],j,ble_wakeup_user->ad_filter[i].ad_data[j]);
                                }
                            }
                        }
                        if((ad_role & AD_ROLE_FLAG) == ROLE_COMBO){
                            if(mask_is_valid && need_wakeup){
                                ad_role_combo_idx = (ad_role&ROLE_COMBO_IDX_FLAG)>>4;
                                gpio_trigger_idx[ad_role_combo_idx] = ble_wakeup_user->ad_filter[i].gpio_trigger_idx;
                                ad_role_complete[ad_role_combo_idx]++;
                            }else{
                                //ad_role_complete = 0;
                            }
                        }else{
                            if(mask_is_valid && need_wakeup){
                                dbg("wakeup\r\n");
                                app_ble_wakeup_notify(ble_wakeup_user->ad_filter[i].gpio_trigger_idx);
                                break;
                            }
                        }

                    }
                }
            }
            for(uint8_t idx=0;idx<MAX_ROLE_COMBO_IDX_NUM;idx++){
                if(ble_combo_num[idx] && (ad_role_complete[idx] == ble_combo_num[idx])){
                    dbg("combo wakeup idx %d\r\n",idx);
                    app_ble_wakeup_notify(gpio_trigger_idx[idx]);
                }
            }
        }
        #endif

        if(ele_type == 0x16 && ele_len >= 11 ){
            uint16_t uuid;
            uint16_t frame_cntl;
            uint16_t product_id;
            uint8_t frame_counter;
            uint16_t pair_id;
            uint16_t sn;


            uuid = (uint16_t)ele_data[0]|((uint16_t)ele_data[1]<<8);
            dbg("type= 0x16,uuid=0x%x\n",uuid);
            if(uuid == 0x1379){
                frame_cntl = (uint16_t)ele_data[2]|((uint16_t)ele_data[3]<<8);
                product_id = (uint16_t)ele_data[4]|((uint16_t)ele_data[5]<<8);
                frame_counter = ele_data[6];
                pair_id = (uint16_t)ele_data[7]|((uint16_t)ele_data[8]<<8);
                sn = (uint16_t)ele_data[9]|((uint16_t)ele_data[10]<<8);
                dbg("frame_cntl=0x%x,product_id=0x%x,frame_counter=0x%x,pair_id=0x%x,sn=0x%x,\n"\
                    ,frame_cntl,product_id,frame_counter,pair_id,sn);
                if(product_id == 0x0001){
                    uint16_t obj_id;
                    uint8_t obj_len;
                    uint8_t key_bit;
                    obj_id = (uint16_t)ele_data[11]|((uint16_t)ele_data[12]<<8);
                    obj_len = ele_data[13];
                    key_bit = ele_data[14];
                    dbg("obj_id=0x%x,obj_len=0x%x,key_bit=0x%x\n",obj_id,obj_len,key_bit);
                    switch(obj_id){
                        case 0x2001:
                            if(key_bit & (1<<0)){
                                //bit0 wakeup.
                            }
                            break;
                        case 0x2002:
                            //key
                            break;
                        default:
                            break;
                    }
                }
            }
        }else if(ele_type == 0x09){
            #if BLE_APP_AUDTRANSMITC
            if (ble_user_info.dev_name_len) {
                if(!memcmp(ble_user_info.dev_name , ele_data , ble_user_info.dev_name_len)){
                    TRACE("BLE: Aud Transmit name is received \n");
                    app_ble_stop_scan();
                    app_ble_peer_addr_init(param->trans_addr.addr.addr,param->trans_addr.addr_type);
                    app_ble_init_msg_start();
                }
            }
            #endif
        }

        #if PLF_M2D_BLE
        if(ble_user_info.ad_data_filter.len != 0 && ble_user_info.ad_data_filter.len <= ADV_DATA_LEN ){
            if(ele_type == ble_user_info.ad_data_filter.ad_type
             && ele_len == ble_user_info.ad_data_filter.len){
                TRACE("m2d adv data %x,%x    %x,%x,\n",ele_data[0],ele_data[1],ble_user_info.ad_data_filter.data[0],ble_user_info.ad_data_filter.data[1]);
                if(!memcmp(ele_data,ble_user_info.ad_data_filter.data,(ele_len-1))){
                    if(app_m2d_wl_addr_check(param->trans_addr.addr)){
#if 1
                        dbg("%s \n",__func__);
                        dbg("actv_idx %x, info %x\n",param->actv_idx,param->info);
                        dbg("trans_addr.addr_type %x, addr %x,%x,%x,%x,%x,%x \n",param->trans_addr.addr_type,param->trans_addr.addr.addr[0],param->trans_addr.addr.addr[1]\
                            ,param->trans_addr.addr.addr[2],param->trans_addr.addr.addr[3],param->trans_addr.addr.addr[4],param->trans_addr.addr.addr[5]);
                        dbg("target_addr.addr_type %x, addr %x,%x,%x,%x,%x,%x \n",param->target_addr.addr_type,param->target_addr.addr.addr[0],param->target_addr.addr.addr[1]\
                            ,param->target_addr.addr.addr[2],param->target_addr.addr.addr[3],param->target_addr.addr.addr[4],param->target_addr.addr.addr[5]);
                        dbg("tx_pwr %x, rssi %d,phy_prim %x, phy_prim %x,phy_second %x,adv_sid %x,period_adv_intv %x\n"\
                            ,param->tx_pwr,param->rssi,param->phy_prim,param->phy_second,param->adv_sid,param->period_adv_intv);
                        dbg("length %d,data %x,%x,%x,%x,%x,%x,%x\n",param->length,param->data[0],param->data[1],param->data[2],param->data[3],param->data[4],param->data[5],param->data[6]);
#endif
                        //do trigger
                        app_ble_stop_scan();
                        m2d_wakeup_trigger();
                    }
                }
            }else if(ele_type == 0x07 && ele_len == 0x11){
                uint8_t *wakeupword = m2d_get_tmall_genie_wakeup_word();
                if(!memcmp(ele_data,wakeupword,(ele_len-1))){
                    //do trigger
                    app_ble_stop_scan();
                    m2d_wakeup_trigger();
                }
            }
        }
        #endif
        if(total_len >= (ele_len+1)){
            total_len -= (ele_len+1);
            data += (ele_len+1);
        }else{
            return (KE_MSG_CONSUMED);
        }
    }
    app_user_cb_poll(GAPM_EXT_ADV_REPORT_IND,(uint8_t *)param);
    return (KE_MSG_CONSUMED);
}

static int app_exchanged_mtu_handler(ke_msg_id_t const msgid,
                                              struct gattc_mtu_changed_ind *param,
                                              ke_task_id_t const dest_id,
                                              ke_task_id_t const src_id)
{
   uint8_t conidx = KE_IDX_GET(src_id);

   TRACE("BLE: %s ,mtu %d\n",__func__,param->mtu);
   struct ble_mtu_changed_ind ind;
   ind.conidx = conidx;
   memcpy(&ind.mtu_ind,param,sizeof(struct gattc_mtu_changed_ind));
   app_user_cb_poll(GATTC_MTU_CHANGED_IND,(uint8_t *)&ind);
   return (KE_MSG_CONSUMED);
}

static int app_le_ptk_size_handler(ke_msg_id_t const msgid,
                                            struct gapc_le_pkt_size_ind *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);
    struct ble_le_pkt_size_ind ind;
    ind.conidx = conidx;
    memcpy(&ind.ind,param,sizeof(struct gapc_le_pkt_size_ind));
    app_user_cb_poll(GAPC_LE_PKT_SIZE_IND,(uint8_t *)&ind);
    return (KE_MSG_CONSUMED);
}


/*
 * GLOBAL VARIABLES DEFINITION
 ****************************************************************************************
 */

/* Default State handlers definition. */
KE_MSG_HANDLER_TAB(appm)
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,    (ke_msg_func_t)appm_msg_handler},

    // GAPM messages
    {GAPM_PROFILE_ADDED_IND,    (ke_msg_func_t)gapm_profile_added_ind_handler},
    {GAPM_ACTIVITY_CREATED_IND, (ke_msg_func_t)gapm_activity_created_ind_handler},
    {GAPM_ACTIVITY_STOPPED_IND, (ke_msg_func_t)gapm_activity_stopped_ind_handler},
    {GAPM_CMP_EVT,              (ke_msg_func_t)gapm_cmp_evt_handler},
    {GAPM_GEN_RAND_NB_IND,      (ke_msg_func_t)gapm_gen_rand_nb_ind_handler},

    // GAPC messages
    {GAPC_GET_DEV_INFO_REQ_IND, (ke_msg_func_t)gapc_get_dev_info_req_ind_handler},
    {GAPC_SET_DEV_INFO_REQ_IND, (ke_msg_func_t)gapc_set_dev_info_req_ind_handler},
    {GAPC_CONNECTION_REQ_IND,   (ke_msg_func_t)gapc_connection_req_ind_handler},
    {GAPC_PARAM_UPDATE_REQ_IND, (ke_msg_func_t)gapc_param_update_req_ind_handler},
    {GAPC_PARAM_UPDATED_IND,    (ke_msg_func_t)gapc_param_update_ind_handler},
    {GAPC_CMP_EVT,              (ke_msg_func_t)gapc_cmp_evt_handler},
    {GAPC_DISCONNECT_IND,       (ke_msg_func_t)gapc_disconnect_ind_handler},
    {APP_TEST_TIMER,            (ke_msg_func_t)app_test_timer_handler},
    {GAPM_EXT_ADV_REPORT_IND,   (ke_msg_func_t)app_adv_report_handler},
    {GATTC_MTU_CHANGED_IND,     (ke_msg_func_t)app_exchanged_mtu_handler},
    {GAPC_LE_PKT_SIZE_IND ,     (ke_msg_func_t)app_le_ptk_size_handler},
};

/* Defines the place holder for the states of all the task instances. */
ke_state_t appm_state[APP_IDX_MAX];

// Application task descriptor
const struct ke_task_desc TASK_DESC_APP = {appm_msg_handler_tab, appm_state, APP_IDX_MAX, ARRAY_LEN(appm_msg_handler_tab)};

#endif //(BLE_APP_PRESENT)

/// @} APPTASK
