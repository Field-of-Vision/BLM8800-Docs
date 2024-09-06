/**
 ****************************************************************************************
 *
 * @file app_sec.c
 *
 * @brief Application Security Entry Point
 *
 * Copyright (C) RivieraWaves 2009-2015
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"

#if (BLE_APP_SEC)

#include <string.h>
#include "ble_utils.h"
#include "co_math.h"
#include "gapc_task.h"      // GAP Controller Task API Definition
#include "gap.h"            // GAP Definition
#include "gapc.h"           // GAPC Definition
#include "prf_types.h"

#include "app.h"            // Application API Definition
#include "app_sec.h"        // Application Security API Definition
#include "app_task.h"       // Application Manager API Definition




#include "flash_api_btdm.h"

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Application Security Environment Structure
struct app_sec_env_tag app_sec_env;

/*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void app_sec_init()
{
    /*------------------------------------------------------
     * RETRIEVE BOND STATUS
     *------------------------------------------------------*/

    uint8_t bonded_status;
    flash_btdm_le_periph_bonded_read(&bonded_status);

    if (bonded_status == 0x1) {
        app_sec_env.bonded = true;
    } else {
        app_sec_env.bonded = false;
    }
    AICBLE_DBG(APP, INFO, "### bonded %d %d", bonded_status, app_sec_env.bonded);
}

bool app_sec_get_bond_status(void)
{
    return app_sec_env.bonded;
}


void app_sec_remove_bond(void)
{
    #if (BLE_APP_HID)
    uint8_t ntf_cfg = PRF_CLI_STOP_NTFIND;
    #endif //(BLE_APP_HID)

    // Check if we are well bonded
    if (app_sec_env.bonded == true)
    {
        // Update the environment variable
        app_sec_env.bonded = false;
        flash_btdm_le_periph_bonded_remove();
        flash_btdm_le_loc_irk_remove();
        #if (BLE_APP_HID)
        flash_btdm_le_mouse_ntf_cfg_write(&ntf_cfg);
        #endif //(BLE_APP_HID)
    }
}


void app_sec_send_security_req(uint8_t conidx)
{
    // Send security request
    struct gapc_security_cmd *cmd = KE_MSG_ALLOC(GAPC_SECURITY_CMD,
                                                 KE_BUILD_ID(TASK_GAPC, conidx), KE_BUILD_ID(TASK_APP, conidx),
                                                 gapc_security_cmd);

    cmd->operation = GAPC_SECURITY_REQ;

    #if (BLE_APP_HID || BLE_APP_HT)
    cmd->auth      = GAP_AUTH_REQ_MITM_BOND;
    #else
    cmd->auth      = GAP_AUTH_REQ_NO_MITM_BOND;//GAP_AUTH_REQ_NO_MITM_NO_BOND;
    #endif //(BLE_APP_HID || BLE_APP_HT)

    // Send the message
    ke_msg_send(cmd);
}

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */
static int gapc_bond_req_ind_handler(ke_msg_id_t const msgid,
                                     struct gapc_bond_req_ind const *param,
                                     ke_task_id_t const dest_id,
                                     ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);
    // Prepare the GAPC_BOND_CFM message
    struct gapc_bond_cfm *cfm = KE_MSG_ALLOC(GAPC_BOND_CFM,
                                             src_id, KE_BUILD_ID(TASK_APP,conidx),
                                             gapc_bond_cfm);

    AICBLE_DBG(APP, DEBUG, "request %d", param->request);

    switch (param->request)
    {
        case (GAPC_PAIRING_REQ):
        {
            cfm->request = GAPC_PAIRING_RSP;

            cfm->accept  = false;

            // Check if we are already bonded (Only one bonded connection is supported)
            if (!app_sec_env.bonded)
            {
                cfm->accept  = true;

                #if (BLE_APP_HID || BLE_APP_HT)
                // Pairing Features
                cfm->data.pairing_feat.auth      = GAP_AUTH_REQ_MITM_BOND;
                #else
                #if (BLE_APP_SEC_CON == 1)
                if (param->data.auth_req & GAP_AUTH_SEC_CON)
                {
                    cfm->data.pairing_feat.auth      = GAP_AUTH_REQ_SEC_CON_BOND;
                    app_env.sec_con_enabled = true;
                }
                else
                {
                    cfm->data.pairing_feat.auth      = GAP_AUTH_REQ_NO_MITM_BOND;
                    app_env.sec_con_enabled = false;
                }
                #else  // !(BLE_APP_SEC_CON)
                cfm->data.pairing_feat.auth      = GAP_AUTH_REQ_NO_MITM_BOND;
                app_env.sec_con_enabled = false;
                #endif // (BLE_APP_SEC_CON)
                #endif //(BLE_APP_HID || BLE_APP_HT)

                #if (BLE_APP_HT)
                cfm->data.pairing_feat.iocap     = GAP_IO_CAP_DISPLAY_ONLY;
                #else
                cfm->data.pairing_feat.iocap     = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
                #endif //(BLE_APP_HT)

                cfm->data.pairing_feat.key_size  = 16;
                cfm->data.pairing_feat.oob       = GAP_OOB_AUTH_DATA_NOT_PRESENT;
                cfm->data.pairing_feat.sec_req   = GAP_NO_SEC;
                #if 1
                cfm->data.pairing_feat.rkey_dist = GAP_KDIST_ENCKEY | GAP_KDIST_IDKEY;
                cfm->data.pairing_feat.ikey_dist = GAP_KDIST_ENCKEY | GAP_KDIST_IDKEY;
                #else
                cfm->data.pairing_feat.ikey_dist = GAP_KDIST_NONE;
                cfm->data.pairing_feat.rkey_dist = GAP_KDIST_ENCKEY;
                #endif // 
            }
        } break;

        case (GAPC_LTK_EXCH):
        {
            // Counter
            uint8_t counter;

            cfm->accept  = true;
            cfm->request = GAPC_LTK_EXCH;

            // Generate all the values
            cfm->data.ltk.ediv = (uint16_t)co_rand_word();

            for (counter = 0; counter < RAND_NB_LEN; counter++)
            {
                cfm->data.ltk.ltk.key[counter]    = (uint8_t)co_rand_word();
                cfm->data.ltk.randnb.nb[counter] = (uint8_t)co_rand_word();
            }

            for (counter = RAND_NB_LEN; counter < KEY_LEN; counter++)
            {
                cfm->data.ltk.ltk.key[counter]    = (uint8_t)co_rand_word();
            }


            AICBLE_DBG(APP, NOTICE, "ltk is:");
            AICBLE_DUMP(LTK,(uint8_t *)&cfm->data.ltk,sizeof(struct gapc_ltk));
            AICBLE_DBG(APP, NOTICE, "ediv is: %04x",cfm->data.ltk.ediv);
            AICBLE_DBG(APP, NOTICE, "randnb is:");
            AICBLE_DUMP(LTK,(uint8_t *)&cfm->data.ltk.randnb.nb,8);
#ifdef _BLE_NVDS_
#ifdef BLE_KEY_PRINT
            TRACE("<==============>LTK IS:");
            TRACE("<==============>EDIV IS: %04x:",cfm->data.ltk.ediv);
            TRACE("<==============>RANDOM IS:");
#endif
            memset(&ble_save_info,0,sizeof(BleDeviceinfo));
            memcpy(&ble_save_info.peer_bleAddr,(uint8_t *)gapc_get_bdaddr(0, SMPC_INFO_PEER),6);
            ble_save_info.EDIV=cfm->data.ltk.ediv;
            memcpy(&ble_save_info.RANDOM,(uint8_t *)&cfm->data.ltk.randnb.nb,8);
            memcpy(&ble_save_info.LTK,(uint8_t *)&cfm->data.ltk,16);
            ble_save_info.bonded=false;
#endif

            flash_btdm_le_ltk_write(&cfm->data.ltk);
        } break;


        case (GAPC_IRK_EXCH):
        {

            cfm->accept  = true;
            cfm->request = GAPC_IRK_EXCH;

            // Load IRK
            memcpy(cfm->data.irk.irk.key, app_env.loc_irk, KEY_LEN);

            // load device address
            cfm->data.irk.addr.addr_type = (cfm->data.irk.addr.addr.addr[5] & 0xC0) ? ADDR_RAND : ADDR_PUBLIC;
        } break;


        #if (BLE_APP_HT)
        case (GAPC_TK_EXCH):
        {
            // Generate a PIN Code- (Between 100000 and 999999)
            uint32_t pin_code = (100000 + (co_rand_word()%900000));

            cfm->accept  = true;
            cfm->request = GAPC_TK_EXCH;

            // Set the TK value
            memset(cfm->data.tk.key, 0, KEY_LEN);

            cfm->data.tk.key[0] = (uint8_t)((pin_code & 0x000000FF) >>  0);
            cfm->data.tk.key[1] = (uint8_t)((pin_code & 0x0000FF00) >>  8);
            cfm->data.tk.key[2] = (uint8_t)((pin_code & 0x00FF0000) >> 16);
            cfm->data.tk.key[3] = (uint8_t)((pin_code & 0xFF000000) >> 24);
        } break;
        #endif //(BLE_APP_HT)

        default:
        {
            ASSERT_ERR(0);
        } break;
    }

    // Send the message
    ke_msg_send(cfm);

    return (KE_MSG_CONSUMED);
}

static int gapc_bond_ind_handler(ke_msg_id_t const msgid,
                                 struct gapc_bond_ind const *param,
                                 ke_task_id_t const dest_id,
                                 ke_task_id_t const src_id)
{
    switch (param->info)
    {
        case (GAPC_PAIRING_SUCCEED):
        {
            // Update the bonding status in the environment
            app_sec_env.bonded = true;
#ifdef _BLE_NVDS_
            ble_save_info.bonded=true;
            if(!nv_record_blerec_add(&ble_save_info)){
            }
#endif

            // Update the bonding status in the environment

            flash_btdm_le_periph_bonded_write((uint8_t *)&app_sec_env.bonded);

        } break;

        case (GAPC_REPEATED_ATTEMPT):
        {
            int idx = KE_IDX_GET(src_id);
            appm_disconnect(idx);
        } break;

        case (GAPC_IRK_EXCH):
        {

        } break;

        case (GAPC_PAIRING_FAILED):
        {
            AICBLE_DBG(APP, WARN, "GAPC_PAIRING_FAILED!!!");
#ifdef _BLE_NVDS_
            app_sec_env.bonded = false;
#endif
            app_sec_send_security_req(0);
        } break;

        // In Secure Connections we get BOND_IND with SMPC calculated LTK
        case (GAPC_LTK_EXCH) :
        {
            #if (BLE_APP_SEC_CON)
            if (app_env.sec_con_enabled == true)
            {
                // Store LTK in flash
                flash_btdm_le_ltk_write(&param->data.ltk.ltk);
            }
            #endif // (BLE_APP_SEC_CON)
        }
        break;

        default:
        {
            ASSERT_ERR(0);
        } break;
    }

    return (KE_MSG_CONSUMED);
}

static int gapc_encrypt_req_ind_handler(ke_msg_id_t const msgid,
                                        struct gapc_encrypt_req_ind const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{
    struct gapc_ltk ltk;
    uint8_t conidx = KE_IDX_GET(src_id);

    // Prepare the GAPC_ENCRYPT_CFM message
    struct gapc_encrypt_cfm *cfm = KE_MSG_ALLOC(GAPC_ENCRYPT_CFM,
                                                src_id, KE_BUILD_ID(TASK_APP,conidx),
                                                gapc_encrypt_cfm);

    cfm->found    = false;

    if (app_sec_env.bonded)
    {
        //read ltk from flash
        flash_btdm_le_ltk_read(&ltk);
        // Check if the provided EDIV and Rand Nb values match with the stored values
        if ((param->ediv == ltk.ediv) &&
            !memcmp(&param->rand_nb.nb[0], &ltk.randnb.nb[0], sizeof(struct rand_nb)))
        {
            cfm->found    = true;
            cfm->key_size = 16;
            memcpy(&cfm->ltk, &ltk.ltk, sizeof(struct gap_sec_key));
        }

#ifdef _BLE_NVDS_
    struct gapc_ltk ltk;

    int ret;
    ret=nv_record_ble_record_find_ltk_through_ediv_and_random(param->ediv,&param->rand_nb.nb[0],ltk.ltk.key);
    if(!ret){
#ifdef BLE_KEY_PRINT
#endif
        memset(&ble_save_info,0,sizeof(BleDeviceinfo));
        memcpy(&ble_save_info.peer_bleAddr,(uint8_t *)gapc_get_bdaddr(0, SMPC_INFO_PEER),6);
        ble_save_info.EDIV=param->ediv;
        memcpy(&ble_save_info.RANDOM,(uint8_t *)&param->rand_nb.nb[0],sizeof(struct rand_nb));
        memcpy(&ble_save_info.LTK,(uint8_t *)ltk.ltk.key,sizeof(struct gap_sec_key));
        ble_save_info.bonded=true;
        if(!nv_record_blerec_add(&ble_save_info)){
            AICBLE_DBG(APP, WARN, "BLE NVDS RE_SETUP SUCCESS!!!");
        }
        cfm->found	  = true;
        cfm->key_size = 16;
        memcpy(&cfm->ltk, ltk.ltk.key, sizeof(struct gap_sec_key));
    }else{
        AICBLE_DBG(APP, WARN, ("FIND LTK failed!!!");
        ASSERT_ERR(0);
    }
#endif
    }

    AICBLE_DBG(APP, INFO, "app_sec_env.bonded %d", app_sec_env.bonded);
    /*
     * else the peer device is not known, an error should trigger a new pairing procedure.
     */

    // Send the message
    ke_msg_send(cfm);

    return (KE_MSG_CONSUMED);
}


static int gapc_encrypt_ind_handler(ke_msg_id_t const msgid,
                                    struct gapc_encrypt_ind const *param,
                                    ke_task_id_t const dest_id,
                                    ke_task_id_t const src_id)
{
    // encryption/ re-encryption succeeded

    #if 0
    // Need to Setup Authenicated Payload TO for the connection.
    struct gapc_set_le_ping_to_cmd *cmd = KE_MSG_ALLOC(GAPC_SET_LE_PING_TO_CMD,
                                                       KE_BUILD_ID(TASK_GAPC, KE_IDX_GET(src_id)), KE_BUILD_ID(TASK_APP,KE_IDX_GET(src_id)),
                                                       gapc_set_le_ping_to_cmd);

    // encryption/ re-encryption succeeded


    cmd->operation = GAPC_SET_LE_PING_TO;
    cmd->timeout = 1000; // 10 Sec

    // Send the message
    ke_msg_send(cmd);
    #endif //
    return (KE_MSG_CONSUMED);
}

static int app_sec_msg_dflt_handler(ke_msg_id_t const msgid,
                                    void *param,
                                    ke_task_id_t const dest_id,
                                    ke_task_id_t const src_id)
{
    // Drop the message

    return (KE_MSG_CONSUMED);
}

 /*
  * LOCAL VARIABLE DEFINITIONS
  ****************************************************************************************
  */

/// Default State handlers definition
const struct ke_msg_handler app_sec_msg_handler_list[] =
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,  (ke_msg_func_t)app_sec_msg_dflt_handler},

    {GAPC_BOND_REQ_IND,       (ke_msg_func_t)gapc_bond_req_ind_handler},
    {GAPC_BOND_IND,           (ke_msg_func_t)gapc_bond_ind_handler},

    {GAPC_ENCRYPT_REQ_IND,    (ke_msg_func_t)gapc_encrypt_req_ind_handler},
    {GAPC_ENCRYPT_IND,        (ke_msg_func_t)gapc_encrypt_ind_handler},
};

const struct app_subtask_handlers app_sec_handlers = {&app_sec_msg_handler_list[0], ARRAY_LEN(app_sec_msg_handler_list)};

#endif //(BLE_APP_SEC)

/// @} APP
