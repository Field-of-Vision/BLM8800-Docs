/**
 ****************************************************************************************
 *
 * @file app.c
 *
 * @brief Application entry point
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

#include "rwip_config.h"             // SW configuration

#if (BLE_APP_PRESENT)
#include <string.h>

#include "app_task.h"                // Application task Definition
#include "app.h"                     // Application Definition
#include "gap.h"                     // GAP Definition
#include "gapm.h"                    // GAP Manager Definition
#include "gapm_task.h"               // GAP Manager Task API
#include "gapc_task.h"               // GAP Controller Task API

#include "co_bt.h"                   // Common BT Definition
#include "co_math.h"                 // Common Maths Definition

#if (BLE_APP_SEC)
#include "app_sec.h"                 // Application security Definition
#endif // (BLE_APP_SEC)

#if (BLE_APP_HT)
#include "app_ht.h"                  // Health Thermometer Application Definitions
#endif //(BLE_APP_HT)

#if (BLE_APP_HR)
#include "app_hrps.h"
#endif

#if (BLE_APP_DIS)
#include "app_dis.h"                 // Device Information Service Application Definitions
#endif //(BLE_APP_DIS)

#if (BLE_APP_BATT)
#include "app_batt.h"                // Battery Application Definitions
#endif //(BLE_APP_BATT)

#if (BLE_APP_HID)
#include "app_hid.h"                 // HID Application Definitions
#endif //(BLE_APP_HID)

#if (BLE_APP_SMARTCONFIG)
#include "app_smartconfig.h"         // Smart Config Application Definitions
#endif //(BLE_APP_SMARTCONFIG)


#include "rtos.h"
#include "ke_timer.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// Default Device Name
#if (BLE_APP_SMARTCONFIG)
#define APP_DFLT_DEVICE_NAME            ("BLE_SMARTCONFIG")
#elif (BLE_APP_HID)
#define APP_DFLT_DEVICE_NAME            ("AIC_BLE_HID")
#else
#define APP_DFLT_DEVICE_NAME            ("AIC_BLE")
#endif
#define APP_DFLT_DEVICE_NAME_LEN        (sizeof(APP_DFLT_DEVICE_NAME))

uint8_t ble_enabled = 0;

#if (BLE_APP_HT) || (BLE_APP_HID)
static const uint8_t adv_data_uuid[] = {
    03, GAP_AD_TYPE_COMPLETE_LIST_16_BIT_UUID,
#if (BLE_APP_HT)
    ATT_SVC_HEALTH_THERMOM & 0xFF,
    ATT_SVC_HEALTH_THERMOM >> 8,
#endif //(BLE_APP_HT)
#if (BLE_APP_HID)
    ATT_SVC_HID & 0xFF,
    ATT_SVC_HID >> 8,
#endif //(BLE_APP_HID)
};
#endif //(BLE_APP_HT || BLE_APP_HID)

static const uint8_t adv_data_appeareance[] = {
    03, GAP_AD_TYPE_APPEARANCE,
#if (BLE_APP_HT)
    GAPC_APPEARANCE_GENERIC_THERMOMETER & 0xFF,
    GAPC_APPEARANCE_GENERIC_THERMOMETER >> 8,
#elif (BLE_APP_HID)
    GAPC_APPEARANCE_HID_MOUSE & 0xFF,
    GAPC_APPEARANCE_HID_MOUSE >> 8,
#else
    GAPC_APPEARANCE_UNKNOWN & 0xFF,
    GAPC_APPEARANCE_UNKNOWN >> 8,
#endif //(BLE_APP_HID)
};

#define APP_ADV_DATA_APPEARANCE_LEN  (4)

/**
 * Default Scan response data
 * --------------------------------------------------------------------------------------
 * x09                             - Length
 * xFF                             - Vendor specific advertising type
 * x00\x60\x41\x49\x43\x42\x4C\x45 - "AICBLE"
 * --------------------------------------------------------------------------------------
 */
#define APP_SCNRSP_DATA         "\x09\xFF\x00\x60\x41\x49\x43\x42\x4C\x45"
#define APP_SCNRSP_DATA_LEN     (10)


/**
 * Advertising Parameters
 */
#if (BLE_APP_HID)
/// Default Advertising duration - 30s (in multiple of 10ms)
#define APP_DFLT_ADV_DURATION   (3000)
#endif //(BLE_APP_HID)
/// Advertising channel map - 37, 38, 39
#define APP_ADV_CHMAP           (0x07)
/// Advertising minimum interval - 100ms (160*0.625ms)
#define APP_ADV_INT_MIN         (160)
/// Advertising maximum interval - 100ms (160*0.625ms)
#define APP_ADV_INT_MAX         (160)
/// Fast advertising interval
#define APP_ADV_FAST_INT        (32)

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
#define APP_BLE_USE_OPLIST          1
/*
 * LOCAL VARIABLES DEFINITIONS
 ****************************************************************************************
 */

/// Application Task Descriptor
extern const struct ke_task_desc TASK_DESC_APP;

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Application Environment Structure
struct app_env_tag app_env;
struct ble_app_user_info ble_user_info;
list_node_t ble_app_oplist;
app_user_msg_cb app_user_cb_p[APP_USER_CB_MAX] = {0,};

/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */
void app_user_set_msg_cb(enum APP_USER_CB_REG_T user_id,app_user_msg_cb func)
{
    app_user_cb_p[user_id] = func;
}

void app_user_cb_poll(uint16_t event,uint8_t *buff)
{
    uint8_t i;
    for (i=0; i<APP_USER_CB_MAX; i++){
        if (app_user_cb_p[i]){
            app_user_cb_p[i](event,buff);
        }
    }
}

static void appm_build_adv_data(uint16_t max_length, uint16_t *p_length, uint8_t *p_buf)
{
    // Remaining Length
    uint8_t rem_len = max_length;
    uint8_t len = 0;
    #if (BLE_APP_HT) || (BLE_APP_HID)
    // Set list of UUIDs
    len = sizeof(adv_data_uuid);
    memcpy(p_buf, adv_data_uuid, len);
    *p_length += len;
    p_buf += len;
    #endif

    // Set appearance
    len = sizeof(adv_data_appeareance);
    memcpy(p_buf, adv_data_appeareance, len);
    *p_length += len;
    p_buf += len;

    // Sanity check
    ASSERT_ERR(rem_len >= max_length);

    // Get remaining space in the Advertising Data - 2 bytes are used for name length/flag
    rem_len -= *p_length;

    // Check if additional data can be added to the Advertising data - 2 bytes needed for type and length
    if (rem_len > 2)
    {
        uint8_t dev_name_length = co_min(app_env.dev_name_len, (rem_len - 2));

        // Device name length
        *p_buf = dev_name_length + 1;
        // Device name flag (check if device name is complete or not)
        *(p_buf + 1) = (dev_name_length == app_env.dev_name_len) ? '\x09' : '\x08';
        // Copy device name
        memcpy(p_buf + 2, app_env.dev_name, dev_name_length);

        // Update advertising data length
        *p_length += (dev_name_length + 2);
    }
}

static void appm_start_advertising(void)
{
    // Prepare the GAPM_ACTIVITY_START_CMD message
    struct gapm_activity_start_cmd *p_cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_START_CMD,
                                                         TASK_GAPM, TASK_APP,
                                                         gapm_activity_start_cmd);

    p_cmd->operation = GAPM_START_ACTIVITY;
    p_cmd->actv_idx = app_env.adv_actv_idx;
    if (ble_user_info.adv_duration) {
        p_cmd->u_param.adv_add_param.duration = ble_user_info.adv_duration;
    } else {
        p_cmd->u_param.adv_add_param.duration = 0;
    }
    p_cmd->u_param.adv_add_param.max_adv_evt = 0;

#if APP_BLE_USE_OPLIST
    app_ble_oplist_insert(GAPM_START_ACTIVITY,APP_ADV_STATE_STARTING,0,p_cmd);
#else
    // Keep the current operation
    app_env.adv_state = APP_ADV_STATE_STARTING;
    // And the next expected operation code for the command completed event
    app_env.adv_op = GAPM_START_ACTIVITY;

    // Send the message
    ke_msg_send(p_cmd);
#endif
}


static void appm_stop_advertising(void)
{
    // Prepare the GAPM_ACTIVITY_STOP_CMD message
    struct gapm_activity_stop_cmd *cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_STOP_CMD,
                                                      TASK_GAPM, TASK_APP,
                                                      gapm_activity_stop_cmd);

    // Fill the allocated kernel message
    cmd->operation = GAPM_STOP_ACTIVITY;
    cmd->actv_idx = app_env.adv_actv_idx;

#if APP_BLE_USE_OPLIST
    app_ble_oplist_insert(GAPM_STOP_ACTIVITY,APP_ADV_STATE_STOPPING,0,cmd);
#else
    // Update advertising state
    app_env.adv_state = APP_ADV_STATE_STOPPING;
    // And the next expected operation code for the command completed event
    app_env.adv_op = GAPM_STOP_ACTIVITY;

    // Send the message
    ke_msg_send(cmd);
#endif
}

static void appm_set_adv_data(void)
{
    // Prepare the GAPM_SET_ADV_DATA_CMD message
    struct gapm_set_adv_data_cmd *p_cmd = KE_MSG_ALLOC_DYN(GAPM_SET_ADV_DATA_CMD,
                                                           TASK_GAPM, TASK_APP,
                                                           gapm_set_adv_data_cmd,
                                                           ADV_DATA_LEN);

    // Fill the allocated kernel message
    p_cmd->operation = GAPM_SET_ADV_DATA;
    p_cmd->actv_idx = app_env.adv_actv_idx;

    p_cmd->length = 0;
    if (ble_user_info.adv_data_len) {
        p_cmd->length = ble_user_info.adv_data_len;
        memcpy(&p_cmd->data[0], ble_user_info.adv_data, p_cmd->length);
    } else {
    // GAP will use 3 bytes for the AD Type
        appm_build_adv_data(ADV_DATA_LEN - 3, &p_cmd->length, &p_cmd->data[0]);
    }
#if APP_BLE_USE_OPLIST
    app_ble_oplist_insert(GAPM_SET_ADV_DATA,APP_ADV_STATE_SETTING_ADV_DATA,0,p_cmd);
#else
    // Send the message
    ke_msg_send(p_cmd);

    // Update advertising state
    app_env.adv_state = APP_ADV_STATE_SETTING_ADV_DATA;
    // And the next expected operation code for the command completed event
    app_env.adv_op = GAPM_SET_ADV_DATA;
#endif
}

static void appm_set_scan_rsp_data(void)
{
    // Prepare the GAPM_SET_ADV_DATA_CMD message
    struct gapm_set_adv_data_cmd *p_cmd = KE_MSG_ALLOC_DYN(GAPM_SET_ADV_DATA_CMD,
                                                           TASK_GAPM, TASK_APP,
                                                           gapm_set_adv_data_cmd,
                                                           ADV_DATA_LEN);

    // Fill the allocated kernel message
    p_cmd->operation = GAPM_SET_SCAN_RSP_DATA;
    p_cmd->actv_idx = app_env.adv_actv_idx;

    TRACE("%s, scan_res_len = %d\n",__func__,ble_user_info.scan_res_len);
    if (ble_user_info.scan_res_len) {
        p_cmd->length = ble_user_info.scan_res_len;
        memcpy(&p_cmd->data[0], ble_user_info.scan_res, p_cmd->length);
    } else {
        p_cmd->length = APP_SCNRSP_DATA_LEN;
        memcpy(&p_cmd->data[0], APP_SCNRSP_DATA, APP_SCNRSP_DATA_LEN);
    }
#if APP_BLE_USE_OPLIST
    app_ble_oplist_insert(GAPM_SET_SCAN_RSP_DATA,APP_ADV_STATE_SETTING_SCAN_RSP_DATA,0,p_cmd);
#else
    // Send the message
    ke_msg_send(p_cmd);

    // Update advertising state
    app_env.adv_state = APP_ADV_STATE_SETTING_SCAN_RSP_DATA;
    // And the next expected operation code for the command completed event
    app_env.adv_op = GAPM_SET_SCAN_RSP_DATA;
#endif
}

static void appm_update_adv_data(void)
{
    // Prepare the GAPM_SET_ADV_DATA_CMD message
    struct gapm_set_adv_data_cmd *p_cmd = KE_MSG_ALLOC_DYN(GAPM_SET_ADV_DATA_CMD,
                                                           TASK_GAPM, TASK_APP,
                                                           gapm_set_adv_data_cmd,
                                                           ADV_DATA_LEN);

    // Fill the allocated kernel message
    p_cmd->operation = GAPM_SET_ADV_DATA;
    p_cmd->actv_idx = app_env.adv_actv_idx;

    p_cmd->length = 0;
    if (ble_user_info.adv_data_len) {
        p_cmd->length = ble_user_info.adv_data_len;
        memcpy(&p_cmd->data[0], ble_user_info.adv_data, p_cmd->length);
    } else {
    // GAP will use 3 bytes for the AD Type
        appm_build_adv_data(ADV_DATA_LEN - 3, &p_cmd->length, &p_cmd->data[0]);
    }
#if APP_BLE_USE_OPLIST == 1
    app_ble_oplist_insert(GAPM_SET_ADV_DATA,APP_ADV_STATE_UPDATE_ADV_DATA,app_env.adv_state,p_cmd);
#else
    // Update advertising state
    app_env.adv_state_prv = app_env.adv_state;
    app_env.adv_state = APP_ADV_STATE_UPDATE_ADV_DATA;
    // And the next expected operation code for the command completed event
    app_env.adv_op = GAPM_SET_ADV_DATA;

    // Send the message
    ke_msg_send(p_cmd);
#endif
}

static void appm_update_adv_scan_res(void)
{
    // Prepare the GAPM_SET_ADV_DATA_CMD message
    struct gapm_set_adv_data_cmd *p_cmd = KE_MSG_ALLOC_DYN(GAPM_SET_ADV_DATA_CMD,
                                                           TASK_GAPM, TASK_APP,
                                                           gapm_set_adv_data_cmd,
                                                           ADV_DATA_LEN);

    // Fill the allocated kernel message
    p_cmd->operation = GAPM_SET_SCAN_RSP_DATA;
    p_cmd->actv_idx = app_env.adv_actv_idx;

    TRACE("%s, scan_res_len = %d\n",__func__,ble_user_info.scan_res_len);
    if (ble_user_info.scan_res_len) {
        p_cmd->length = ble_user_info.scan_res_len;
        memcpy(&p_cmd->data[0], ble_user_info.scan_res, p_cmd->length);
    } else {
        p_cmd->length = APP_SCNRSP_DATA_LEN;
        memcpy(&p_cmd->data[0], APP_SCNRSP_DATA, APP_SCNRSP_DATA_LEN);
    }
#if APP_BLE_USE_OPLIST
    app_ble_oplist_insert(GAPM_SET_SCAN_RSP_DATA,APP_ADV_STATE_UPDATE_ADV_SCAN_RES,app_env.adv_state,p_cmd);
#else
    // Send the message
    ke_msg_send(p_cmd);

    // Update advertising state
    app_env.adv_state = APP_ADV_STATE_UPDATE_ADV_SCAN_RES;
    // And the next expected operation code for the command completed event
    app_env.adv_op = GAPM_SET_SCAN_RSP_DATA;
#endif
}

static void appm_send_gapm_reset_cmd(void)
{
    // Reset the stack
    struct gapm_reset_cmd *p_cmd = KE_MSG_ALLOC(GAPM_RESET_CMD,
                                                TASK_GAPM, TASK_APP,
                                                gapm_reset_cmd);

    p_cmd->operation = GAPM_RESET;

    ke_msg_send(p_cmd);
}

void appm_set_phy(uint8_t conidx)
{
    struct gapc_set_phy_cmd *cmd = KE_MSG_ALLOC(GAPC_SET_PHY_CMD,
                                                KE_BUILD_ID(TASK_GAPC, conidx), KE_BUILD_ID(TASK_APP, conidx),
                                                gapc_set_phy_cmd);

    cmd->operation = GAPC_SET_PHY;
    cmd->tx_phy = GAP_PHY_LE_CODED;
    cmd->rx_phy = GAP_PHY_LE_CODED;
    cmd->phy_opt = GAPC_PHY_OPT_LE_CODED_500K_RATE;

    // Send the message
    ke_msg_send(cmd);
}

void appm_set_pkt_len(uint8_t conidx)
{
    struct gapc_set_le_pkt_size_cmd *cmd = KE_MSG_ALLOC(GAPC_SET_LE_PKT_SIZE_CMD,
                                                KE_BUILD_ID(TASK_GAPC, conidx), KE_BUILD_ID(TASK_APP, conidx),
                                                gapc_set_le_pkt_size_cmd);

    cmd->operation = GAPC_SET_LE_PKT_SIZE;
    cmd->tx_octets = 251;//80;
    cmd->tx_time = 0x1150;

    // Send the message
    ke_msg_send(cmd);
}

/*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void appm_init()
{
    // Reset the application manager environment
    memset(&app_env, 0, sizeof(app_env));

#if APP_BLE_USE_OPLIST
    app_ble_oplist_init();
#endif
    // Create APP task
    ke_task_create(TASK_APP, &TASK_DESC_APP);

    for(uint8_t i = 0;i < APP_IDX_MAX;i++){
        // Initialize Task state
        ke_state_set(KE_BUILD_ID(TASK_APP,i), APPM_INIT);
    }


    // Get the Device Name to add in the Advertising Data (Default one or NVDS one)
    {
        // Get default Device Name (No name if not enough space)
        if (ble_user_info.dev_name_len) {
            memcpy(app_env.dev_name, ble_user_info.dev_name, ble_user_info.dev_name_len);
            app_env.dev_name_len = ble_user_info.dev_name_len;
        } else {
            memcpy(app_env.dev_name, APP_DFLT_DEVICE_NAME, APP_DFLT_DEVICE_NAME_LEN);
            app_env.dev_name_len = APP_DFLT_DEVICE_NAME_LEN;
        }
    }

    /*------------------------------------------------------
     * INITIALIZE ALL MODULES
     *------------------------------------------------------*/
    if(ble_user_info.user_app_callback->app_on_init) {
        ble_user_info.user_app_callback->app_on_init();
    }
}

bool appm_add_svc(void)
{
    if (ble_user_info.user_app_callback->app_on_add_svc) {
        return ble_user_info.user_app_callback->app_on_add_svc();
    } else {
        return false;
    }
}

void appm_disconnect(uint8_t conidx)
{
    struct gapc_disconnect_cmd *cmd = KE_MSG_ALLOC(GAPC_DISCONNECT_CMD,
                                                   KE_BUILD_ID(TASK_GAPC, conidx),  KE_BUILD_ID(TASK_APP, conidx),
                                                   gapc_disconnect_cmd);

    cmd->operation = GAPC_DISCONNECT;
    cmd->reason    = CO_ERROR_REMOTE_USER_TERM_CON;

    // Send the message
    ke_msg_send(cmd);
}

static void appm_create_advertising(void)
{
    if (app_env.adv_state == APP_ADV_STATE_IDLE)
    {
        // Prepare the GAPM_ACTIVITY_CREATE_CMD message
        struct gapm_activity_create_adv_cmd *p_cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_CREATE_CMD,
                                                                  TASK_GAPM, TASK_APP,
                                                                  gapm_activity_create_adv_cmd);

        // Set operation code
        p_cmd->operation = GAPM_CREATE_ADV_ACTIVITY;

        if (ble_user_info.user_adv_param) {
            p_cmd->own_addr_type = ble_user_info.own_addr_type;
            p_cmd->adv_param.disc_mode = ble_user_info.adv_param.disc_mode;
            p_cmd->adv_param.type = ble_user_info.adv_param.type;
            p_cmd->adv_param.prop = ble_user_info.adv_param.prop;
            p_cmd->adv_param.filter_pol = ble_user_info.adv_param.filter_pol;
            p_cmd->adv_param.max_tx_pwr = ble_user_info.adv_param.max_tx_pwr;
            p_cmd->adv_param.prim_cfg.chnl_map = ble_user_info.adv_param.prim_cfg.chnl_map;
            p_cmd->adv_param.prim_cfg.phy = ble_user_info.adv_param.prim_cfg.phy;
            p_cmd->adv_param.prim_cfg.adv_intv_max = ble_user_info.adv_param.prim_cfg.adv_intv_max;
            p_cmd->adv_param.prim_cfg.adv_intv_min = ble_user_info.adv_param.prim_cfg.adv_intv_min;
            p_cmd->adv_param.second_cfg.adv_sid = ble_user_info.adv_param.second_cfg.adv_sid;
            p_cmd->adv_param.second_cfg.phy = ble_user_info.adv_param.second_cfg.phy;
            p_cmd->adv_param.second_cfg.max_skip = ble_user_info.adv_param.second_cfg.max_skip;
            p_cmd->adv_param.period_cfg.adv_intv_max = ble_user_info.adv_param.period_cfg.adv_intv_max;
            p_cmd->adv_param.period_cfg.adv_intv_min = ble_user_info.adv_param.period_cfg.adv_intv_min;
        } else {
            // Fill the allocated kernel message
            p_cmd->own_addr_type = GAPM_STATIC_ADDR;
            p_cmd->adv_param.type = GAPM_ADV_TYPE_LEGACY;
            p_cmd->adv_param.prop = GAPM_ADV_PROP_UNDIR_CONN_MASK;
            p_cmd->adv_param.filter_pol = ADV_ALLOW_SCAN_ANY_CON_ANY;
            p_cmd->adv_param.prim_cfg.chnl_map = APP_ADV_CHMAP;
            p_cmd->adv_param.prim_cfg.phy = GAP_PHY_LE_1MBPS;

            #if (BLE_APP_HID)
            p_cmd->adv_param.disc_mode = GAPM_ADV_MODE_LIM_DISC;

            /*
             * If the peripheral is already bonded with a central device, use the direct advertising
             * procedure (BD Address of the peer device is stored in NVDS.
             */
            if (app_sec_get_bond_status())
            {
    //            // BD Address of the peer device
    //            struct gap_bdaddr peer_bd_addr;
    //            // Length
    //            uint8_t length = NVDS_LEN_PEER_BD_ADDRESS;
    //
    //            // Get the BD Address of the peer device in NVDS
    //            if (nvds_get(NVDS_TAG_PEER_BD_ADDRESS, &length, (uint8_t *)&peer_bd_addr) != NVDS_OK)
    //            {
    //                // The address of the bonded peer device should be present in the database
    //                ASSERT_ERR(0);
    //            }
    //
    //            // Set the DIRECT ADVERTISING mode
    //            cmd->op.code = GAPM_ADV_DIRECT;
    //            // Copy the BD address of the peer device and the type of address
    //            memcpy(&cmd->info.direct, &peer_bd_addr, NVDS_LEN_PEER_BD_ADDRESS);

                p_cmd->adv_param.prim_cfg.adv_intv_min = APP_ADV_FAST_INT;
                p_cmd->adv_param.prim_cfg.adv_intv_max = APP_ADV_FAST_INT;
            }
            else
            {
                p_cmd->adv_param.prim_cfg.adv_intv_min = APP_ADV_INT_MIN;
                p_cmd->adv_param.prim_cfg.adv_intv_max = APP_ADV_INT_MAX;
            }
            #else //(BLE_APP_HID)
            p_cmd->adv_param.disc_mode = GAPM_ADV_MODE_GEN_DISC;
            p_cmd->adv_param.prim_cfg.adv_intv_min = APP_ADV_INT_MIN;
            p_cmd->adv_param.prim_cfg.adv_intv_max = APP_ADV_INT_MAX;
            #endif //(BLE_APP_HID)
        }
#if APP_BLE_USE_OPLIST
        app_ble_oplist_insert(GAPM_CREATE_ADV_ACTIVITY,APP_ADV_STATE_CREATING,0,p_cmd);
#else
        // Send the message
        ke_msg_send(p_cmd);

        // Keep the current operation
        app_env.adv_state = APP_ADV_STATE_CREATING;
        // And the next expected operation code for the command completed event
        app_env.adv_op = GAPM_CREATE_ADV_ACTIVITY;
#endif
    }
}


void appm_delete_advertising(void)
{
    // Prepare the GAPM_ACTIVITY_CREATE_CMD message
    struct gapm_activity_delete_cmd *p_cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_DELETE_CMD,
                                                              TASK_GAPM, TASK_APP,
                                                              gapm_activity_delete_cmd);

    // Set operation code
    p_cmd->operation = GAPM_DELETE_ACTIVITY;
    p_cmd->actv_idx =app_env.adv_actv_idx;
#if APP_BLE_USE_OPLIST
    app_ble_oplist_insert(GAPM_DELETE_ACTIVITY,0,0,p_cmd);
#else
    // Send the message
    ke_msg_send(p_cmd);

    // Keep the current operation
    // And the next expected operation code for the command completed event
    app_env.adv_op = GAPM_DELETE_ACTIVITY;
#endif
}

void appm_adv_fsm_next(void)
{
    TRACE("%s,adv_state %x\n",__func__,app_env.adv_state);
    switch (app_env.adv_state)
    {
        case (APP_ADV_STATE_IDLE):
        {
            // Create advertising
            appm_create_advertising();
        } break;

        case (APP_ADV_STATE_CREATING):
        {
            // Set advertising data
            appm_set_adv_data();
        } break;

        case (APP_ADV_STATE_SETTING_ADV_DATA):
        {
            // Set scan response data
            appm_set_scan_rsp_data();
        } break;

        case (APP_ADV_STATE_CREATED):
        case (APP_ADV_STATE_SETTING_SCAN_RSP_DATA):
        {
            // Start advertising activity
            appm_start_advertising();
        } break;

        case (APP_ADV_STATE_STARTING):
        {
            // Go to started state
            app_env.adv_state = APP_ADV_STATE_STARTED;
            app_user_cb_poll(APP_ADV_STARTED,NULL);
        } break;

        case (APP_ADV_STATE_STARTED):
        {
            // Stop advertising activity
            appm_stop_advertising();
        } break;

        case (APP_ADV_STATE_STOPPING):
        {
            // Go created state
            #if PLF_AON_SUPPORT
            app_env.adv_state = APP_ADV_STATE_CREATING;
            #else
            app_env.adv_state = APP_ADV_STATE_CREATED;
            #endif
            app_user_cb_poll(APP_ADV_STOPED,NULL);
        } break;
        case (APP_ADV_STATE_UPDATE_ADV_DATA):
        {
            app_env.adv_state = app_env.adv_state_prv;
            app_user_cb_poll(APP_ADV_DATA_UPDATED,NULL);
            break;
        }
        case (APP_ADV_STATE_UPDATE_ADV_SCAN_RES):
        {
            app_env.adv_state = app_env.adv_state_prv;
            app_user_cb_poll(APP_ADV_SCAN_RES_UPDATED,NULL);
            break;
        }
        default:
        {
            ASSERT_ERR(0);
        } break;
    }
    app_ble_check_oplist();
}

void appm_update_param(struct gapc_conn_param *conn_param,uint8_t conidx)
{
    // Prepare the GAPC_PARAM_UPDATE_CMD message
    struct gapc_param_update_cmd *cmd = KE_MSG_ALLOC(GAPC_PARAM_UPDATE_CMD,
                                                     KE_BUILD_ID(TASK_GAPC, conidx), KE_BUILD_ID(TASK_APP, conidx),
                                                     gapc_param_update_cmd);

    cmd->operation  = GAPC_UPDATE_PARAMS;
    cmd->intv_min   = conn_param->intv_min;
    cmd->intv_max   = conn_param->intv_max;
    cmd->latency    = conn_param->latency;
    cmd->time_out   = conn_param->time_out;

    // not used by a slave device
    cmd->ce_len_min = 0xFFFF;
    cmd->ce_len_max = 0xFFFF;

    // Send the message
    ke_msg_send(cmd);
}

uint8_t appm_get_dev_name(uint8_t* name)
{
    // copy name to provided pointer
    memcpy(name, app_env.dev_name, app_env.dev_name_len);
    // return name length
    return app_env.dev_name_len;
}

void appm_update_adv_state(bool start)
{
    if (start == true) {
        if (app_env.adv_state == APP_ADV_STATE_STARTED) {
            dbg_test_print("%s already started\r\n", __func__);
            return;
        }
    } else {
        if (app_env.adv_state != APP_ADV_STATE_STARTED) {
            dbg_test_print("%s already stoppped\r\n", __func__);
            return;
        }
    }
    // Start or stop advertising
    appm_adv_fsm_next();
}

static void appm_stop_scan(void)
{
    // Prepare the GAPM_ACTIVITY_STOP_CMD message
    struct gapm_activity_stop_cmd *cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_STOP_CMD,
                                                      TASK_GAPM, TASK_APP,
                                                      gapm_activity_stop_cmd);

    // Fill the allocated kernel message
    cmd->operation = GAPM_STOP_ACTIVITY;
    cmd->actv_idx = app_env.scan_actv_idx;

    // Update scan state
    app_env.scan_state = APP_SCAN_STATE_STOPPING;
    // And the next expected operation code for the command completed event
    app_env.scan_op = GAPM_STOP_ACTIVITY;
    dbg("%s scan_op 0x%x\n",__func__,app_env.scan_op);
    // Send the message
    ke_msg_send(cmd);
}

static void appm_start_scan(void)
{
    // Prepare the GAPM_ACTIVITY_START_CMD message
    struct gapm_activity_start_cmd *p_cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_START_CMD,
                                                         TASK_GAPM, TASK_APP,
                                                         gapm_activity_start_cmd);

    p_cmd->operation = GAPM_START_ACTIVITY;
    p_cmd->actv_idx = app_env.scan_actv_idx;

    if (ble_user_info.scan_duration) {
        p_cmd->u_param.scan_param.duration = ble_user_info.scan_duration;
    } else {
        p_cmd->u_param.scan_param.duration = 0;
    }

    if(ble_user_info.scan_param.type){
        p_cmd->u_param.scan_param.type = ble_user_info.scan_param.type;
    }else{
        p_cmd->u_param.scan_param.type = GAPM_SCAN_TYPE_OBSERVER;
    }
    p_cmd->u_param.scan_param.prop = GAPM_SCAN_PROP_PHY_1M_BIT|GAPM_SCAN_PROP_ACTIVE_1M_BIT;
    
    if(ble_user_info.scan_param.scan_param_1m.scan_intv){
        p_cmd->u_param.scan_param.scan_param_1m.scan_wd = ble_user_info.scan_param.scan_param_1m.scan_wd;
        p_cmd->u_param.scan_param.scan_param_1m.scan_intv = ble_user_info.scan_param.scan_param_1m.scan_intv;
    }else{
        p_cmd->u_param.scan_param.scan_param_1m.scan_wd = 0x10;
        p_cmd->u_param.scan_param.scan_param_1m.scan_intv = 0xa0;
    }
    if(p_cmd->u_param.scan_param.prop & GAPM_SCAN_PROP_ACTIVE_CODED_BIT){
        p_cmd->u_param.scan_param.scan_param_coded.scan_intv = 0xa0;
        p_cmd->u_param.scan_param.scan_param_coded.scan_wd = 0x20;
    }

    // Keep the current operation
    app_env.scan_state = APP_SCAN_STATE_STARTING;
    // And the next expected operation code for the command completed event
    app_env.scan_op = GAPM_START_ACTIVITY;
    dbg("%s scan_op 0x%x\n",__func__,app_env.scan_op);
    // Send the message
    ke_msg_send(p_cmd);
}

static void appm_set_aic_ext_scan(bool enable)
{
    struct hci_le_set_aic_ext_scan_cmd *cmd =
            KE_MSG_ALLOC(GAPM_SET_AIC_EXT_SCAN_CMD, TASK_GAPM, TASK_APP,  hci_le_set_aic_ext_scan_cmd);
    /* fill up the parameters */
    cmd->ext_adv_report_to_legacy_en = enable;
    /* send the message indication */
    ke_msg_send(cmd);
}

static void appm_create_scan(void)
{
    if (app_env.scan_state == APP_SCAN_STATE_IDLE)
    {
        // Prepare the GAPM_ACTIVITY_CREATE_CMD message
        struct gapm_activity_create_cmd *p_cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_CREATE_CMD,
                                                                  TASK_GAPM, TASK_APP,
                                                                  gapm_activity_create_cmd);

        // Set operation code
        p_cmd->operation = GAPM_CREATE_SCAN_ACTIVITY;

        if (ble_user_info.user_adv_param) {
            p_cmd->own_addr_type = ble_user_info.own_addr_type;
        } else {
            // Fill the allocated kernel message
            p_cmd->own_addr_type = GAPM_STATIC_ADDR;
        }

        // Send the message
        ke_msg_send(p_cmd);

        // Keep the current operation
        app_env.scan_state = APP_SCAN_STATE_CREATING;
        // And the next expected operation code for the command completed event
        app_env.scan_op = GAPM_CREATE_SCAN_ACTIVITY;
        dbg("%s scan_op 0x%x\n",__func__,app_env.scan_op);
    }
}

void appm_set_whitelist(struct white_list* wl ,uint8_t num)
{
    ASSERT_ERR(num <= 0xa);
    struct gapm_list_set_wl_cmd *req = KE_MSG_ALLOC_DYN(GAPM_LIST_SET_CMD,
                                                  TASK_GAPM, TASK_APP,
                                                  gapm_list_set_wl_cmd, (sizeof(struct gap_bdaddr)*num));

    // Fill message
    req->operation = GAPM_SET_WL;
    req->size = num;
    memcpy(&req->wl_info,wl,(sizeof(struct gap_bdaddr)*num));
    TRACE("BLE: %s  ,num = %d\n", __func__,num);
    //ble_user_info.scan_param.type = GAPM_SCAN_TYPE_SEL_OBSERVER;
    // Send the message
    ke_msg_send(req);
}

void appm_scan_fsm_next(void)
{
    dbg("%s, state 0x%x\n",__func__,app_env.scan_state);
    switch (app_env.scan_state)
    {
        case (APP_SCAN_STATE_IDLE):
        {
            // Create scan
            appm_create_scan();
        } break;

        case (APP_SCAN_STATE_CREATING):
        case (APP_SCAN_STATE_CREATED):
        {
            appm_set_aic_ext_scan(false);
            // Set scan param and enable
            appm_start_scan();
        } break;

        case (APP_SCAN_STATE_STARTING):
        {
            // Go to started state
            app_env.scan_state = APP_SCAN_STATE_STARTED;
            app_user_cb_poll(APP_SCAN_STARTED,NULL);
        } break;

        case (APP_SCAN_STATE_STARTED):
        {
            // Stop advertising activity
            appm_stop_scan();
        } break;

        case (APP_SCAN_STATE_STOPPING):
        {
            // Go created state
            app_env.scan_state = APP_SCAN_STATE_CREATED;
            app_user_cb_poll(APP_SCAN_STOPED,NULL);
        } break;
        default:
        {
            ASSERT_ERR(0);
        } break;
    }
}

void appm_update_scan_state(bool start)
{
    if (start == true) {
        if (app_env.scan_state == APP_SCAN_STATE_STARTED) {
            dbg_test_print("%s already started\r\n", __func__);
            return;
        }
    } else {
        if (app_env.scan_state != APP_SCAN_STATE_STARTED) {
            dbg_test_print("%s already stoppped\r\n", __func__);
            return;
        }
    }
    // Start or stop advertising
    appm_scan_fsm_next();
}

static void appm_stop_initiating(void)
{
    // Prepare the GAPM_ACTIVITY_STOP_CMD message
    struct gapm_activity_stop_cmd *cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_STOP_CMD,
                                                      TASK_GAPM, TASK_APP,
                                                      gapm_activity_stop_cmd);

    // Fill the allocated kernel message
    cmd->operation = GAPM_STOP_ACTIVITY;
    cmd->actv_idx = app_env.init_actv_idx;

    // Update scan state
    app_env.init_state = APP_INIT_STATE_STOPPING;
    // And the next expected operation code for the command completed event
    app_env.init_op = GAPM_STOP_ACTIVITY;
    dbg("%s init_op 0x%x\n",__func__,app_env.init_op);
    // Send the message
    ke_msg_send(cmd);
}

static void appm_start_initiating(void)
{
    // Prepare the GAPM_ACTIVITY_START_CMD message
    struct gapm_activity_start_cmd *p_cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_START_CMD,
                                                         TASK_GAPM, TASK_APP,
                                                         gapm_activity_start_cmd);

    p_cmd->operation = GAPM_START_ACTIVITY;
    p_cmd->actv_idx = app_env.init_actv_idx;

    p_cmd->u_param.init_param.type = GAPM_INIT_TYPE_DIRECT_CONN_EST;
    p_cmd->u_param.init_param.prop = GAPM_INIT_PROP_1M_BIT|GAPM_INIT_PROP_2M_BIT|GAPM_INIT_PROP_CODED_BIT;
    p_cmd->u_param.init_param.conn_to = 0;//no timeout

    p_cmd->u_param.init_param.scan_param_1m.scan_intv = 0xc0;  //120ms = 0xc0 * 0.625
    p_cmd->u_param.init_param.scan_param_1m.scan_wd = 0x30;    //30ms = 0x30 * 0.625
    p_cmd->u_param.init_param.conn_param_1m.conn_intv_min = 0x6; //10ms
    p_cmd->u_param.init_param.conn_param_1m.conn_intv_max = 0x6; //10ms
    p_cmd->u_param.init_param.conn_param_1m.conn_latency = 0;
    p_cmd->u_param.init_param.conn_param_1m.supervision_to = 50;
    p_cmd->u_param.init_param.conn_param_1m.ce_len_min = 0;
    p_cmd->u_param.init_param.conn_param_1m.ce_len_max = 0;

    p_cmd->u_param.init_param.conn_param_2m.conn_intv_min = 0x6; //10ms
    p_cmd->u_param.init_param.conn_param_2m.conn_intv_max = 0x6; //10ms
    p_cmd->u_param.init_param.conn_param_2m.conn_latency = 0;
    p_cmd->u_param.init_param.conn_param_2m.supervision_to = 50;
    p_cmd->u_param.init_param.conn_param_2m.ce_len_min = 0;
    p_cmd->u_param.init_param.conn_param_2m.ce_len_max = 0;

    p_cmd->u_param.init_param.scan_param_coded.scan_intv = 0xc0;  //120ms = 0xc0 * 0.625
    p_cmd->u_param.init_param.scan_param_coded.scan_wd = 0x30;    //30ms = 0x30 * 0.625
    p_cmd->u_param.init_param.conn_param_coded.conn_intv_min = 0x6; //10ms
    p_cmd->u_param.init_param.conn_param_coded.conn_intv_max = 0x6; //10ms
    p_cmd->u_param.init_param.conn_param_coded.conn_latency = 0;
    p_cmd->u_param.init_param.conn_param_coded.supervision_to = 50;
    p_cmd->u_param.init_param.conn_param_coded.ce_len_min = 0;
    p_cmd->u_param.init_param.conn_param_coded.ce_len_max = 0;

    p_cmd->u_param.init_param.peer_addr.addr_type = ble_user_info.peer_addr_type;
    memcpy(&p_cmd->u_param.init_param.peer_addr.addr.addr[0], &ble_user_info.peer_addr.addr[0], BD_ADDR_LEN);


    // Keep the current operation
    app_env.init_state = APP_INIT_STATE_STARING;
    // And the next expected operation code for the command completed event
    app_env.init_op = GAPM_START_ACTIVITY;
    dbg("%s init_op 0x%x\n",__func__,app_env.init_op);
    // Send the message
    ke_msg_send(p_cmd);
}

static void appm_create_initiating(void)
{
    if (app_env.init_state == APP_INIT_STATE_IDLE)
    {
        // Prepare the GAPM_ACTIVITY_CREATE_CMD message
        struct gapm_activity_create_cmd *p_cmd = KE_MSG_ALLOC(GAPM_ACTIVITY_CREATE_CMD,
                                                                  TASK_GAPM, TASK_APP,
                                                                  gapm_activity_create_cmd);

        // Set operation code
        p_cmd->operation = GAPM_CREATE_INIT_ACTIVITY;

        if (ble_user_info.user_adv_param) {
            p_cmd->own_addr_type = ble_user_info.own_addr_type;
        } else {
            // Fill the allocated kernel message
            p_cmd->own_addr_type = GAPM_STATIC_ADDR;
        }

        // Send the message
        ke_msg_send(p_cmd);

        // Keep the current operation
        app_env.init_state = APP_SCAN_STATE_CREATING;
        // And the next expected operation code for the command completed event
        app_env.init_op = GAPM_CREATE_INIT_ACTIVITY;
        dbg("%s init_op 0x%x\n",__func__,app_env.init_op);
    }
}

void appm_init_fsm_next(void)
{
    dbg("%s, state 0x%x\n",__func__,app_env.init_state);
    switch (app_env.init_state)
    {
        case (APP_INIT_STATE_IDLE):
        {
            // Create init
            appm_create_initiating();
        } break;

        case (APP_INIT_STATE_CREATING):
        case (APP_INIT_STATE_CREATED):
        {
            // Set init param and connecting peer device
            appm_start_initiating();
        } break;

        case (APP_INIT_STATE_STARING):
        {
            // Go to started state
            app_env.init_state = APP_INIT_STATE_STARTED;
            app_user_cb_poll(APP_INIT_STARTED,NULL);
        } break;

        case (APP_INIT_STATE_STARTED):
        {
            // Stop init activity
            appm_stop_initiating();
            app_user_cb_poll(APP_INIT_CACELED,NULL);
        } break;

        case (APP_INIT_STATE_STOPPING):
        {
            // Go created state
            app_env.init_state = APP_INIT_STATE_CREATED;
        } break;
        default:
        {
            ASSERT_ERR(0);
        } break;
    }
}

void appm_update_init_state(bool start)
{
    if (start == true) {
        if (app_env.init_state == APP_INIT_STATE_STARTED) {
            dbg_test_print("%s already started\r\n", __func__);
            return;
        }
    } else {
        if (app_env.init_state != APP_INIT_STATE_STARTED) {
            dbg_test_print("%s already stoppped\r\n", __func__);
            return;
        }
    }
    // Start or stop initiating
    appm_init_fsm_next();
}

/**
 ****************************************************************************************
 * @brief Handles ready indication from the GAP. - Reset the stack
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
void ble_enable(void)
{
    // Application has not been initialized
    for(uint8_t i = 0;i < APP_IDX_MAX;i++){
        ASSERT_ERR(ke_state_get(KE_BUILD_ID(TASK_APP,i)) == APPM_INIT);
    }

    ble_enabled = 1;

    appm_send_gapm_reset_cmd();
}

void ble_disable()
{
    if (app_env.adv_state == APP_ADV_STATE_STARTED) {
        appm_update_adv_state(false);
    }
    for(uint8_t i = 0;i < APP_IDX_MAX;i++){
        if(ke_state_get(KE_BUILD_ID(TASK_APP,i)) == APPM_CONNECTED){
            appm_disconnect(i);
        }
    }
    if (app_env.scan_state == APP_ADV_STATE_STARTED) {
        appm_stop_scan();
    }
}

bool ble_activity_enabled()
{
    bool app_connected = false;
    for(uint8_t i = 0;i < APP_IDX_MAX;i++){
        if(ke_state_get(KE_BUILD_ID(TASK_APP,i)) == APPM_CONNECTED){
            app_connected=true;
        }
    }

    if ((app_env.adv_state != APP_ADV_STATE_STARTED)
        && app_connected == false) {
       return false;
    } else {
        return true;
    }
}

void ble_disabled()
{
    ble_enabled = 0;
}

uint8_t appm_set_dev_name(char* name, uint8_t len)
{
    app_env.dev_name_len = co_min(len, APP_DEVICE_NAME_MAX_LEN);
    memcpy(app_env.dev_name, name, app_env.dev_name_len);
    return app_env.dev_name_len;
}

void appm_set_dev_appearance(uint16_t appearance)
{
    app_env.appearance = appearance;
}

void appm_set_dev_info(struct gapc_set_dev_info_req_ind const *param, uint8_t* status)
{
    switch (param->req)
    {
        case GAPC_DEV_NAME:
        {
            appm_set_dev_name((char *)param->info.name.value, param->info.name.length);
            *status = GAP_ERR_NO_ERROR;
        }
        break;
        case GAPC_DEV_APPEARANCE:
        {
            appm_set_dev_appearance(param->info.appearance);
            *status = GAP_ERR_NO_ERROR;
        }
        break;
        default:
        {
            *status = GAP_ERR_REJECTED;
        }
        break;
    }
}

void app_ble_env_init()
{
    memset(&ble_user_info, 0, sizeof(ble_user_info));
}

void app_ble_register_callbak(struct app_callbacks *ble_app_callbak)
{
    ble_user_info.user_app_callback = ble_app_callbak;
}

void app_ble_addr_init(uint8_t *addr, uint8_t own_addr_type)
{
    memcpy(&ble_user_info.own_addr.addr[0], &addr[0], BD_ADDR_LEN);
    ble_user_info.own_addr_type = own_addr_type;
}

void app_ble_peer_addr_init(uint8_t *addr, uint8_t peer_addr_type)
{
    memcpy(&ble_user_info.peer_addr.addr[0], &addr[0], BD_ADDR_LEN);
    ble_user_info.peer_addr_type = peer_addr_type;
}

void app_ble_set_dev_name(char* name, uint8_t len)
{
    ASSERT_WARN(len <= APP_DEVICE_NAME_MAX_LEN);
    ble_user_info.dev_name_len = co_min(len, APP_DEVICE_NAME_MAX_LEN);
    memcpy(ble_user_info.dev_name, name, ble_user_info.dev_name_len);
}

uint8_t app_ble_set_adv_params(struct gapm_adv_create_param* params, uint16_t adv_duration)
{
    uint8_t ret = CO_ERROR_NO_ERROR;

    ble_user_info.user_adv_param = true;
    if (params->type > GAPM_ADV_TYPE_PERIODIC) {
        dbg("type err %d\r\n", params->type);
        return CO_ERROR_UNSUPPORTED;
    }
    if (params->disc_mode >= GAPM_ADV_MODE_MAX) {
        dbg("disc_mode err %d\r\n", params->disc_mode);
        return CO_ERROR_UNSUPPORTED;
    }
    if (params->filter_pol > ADV_ALLOW_SCAN_WLST_CON_WLST)
    {
        dbg("filter_pol err %d\r\n", params->filter_pol);
        return CO_ERROR_UNSUPPORTED;
    }
    ble_user_info.adv_duration = adv_duration;
    ble_user_info.adv_param.type = params->type;
    ble_user_info.adv_param.disc_mode = params->disc_mode;
    ble_user_info.adv_param.prop = params->prop;
    ble_user_info.adv_param.max_tx_pwr = params->max_tx_pwr;
    ble_user_info.adv_param.filter_pol = params->filter_pol;
    ble_user_info.adv_param.peer_addr.addr_type = params->peer_addr.addr_type;
    memcpy(&params->peer_addr.addr.addr[0], &ble_user_info.adv_param.peer_addr.addr.addr[0], BD_ADDR_LEN);
    ble_user_info.adv_param.prim_cfg.adv_intv_min  = params->prim_cfg.adv_intv_min;
    ble_user_info.adv_param.prim_cfg.adv_intv_max  = params->prim_cfg.adv_intv_max;
    ble_user_info.adv_param.prim_cfg.chnl_map  = params->prim_cfg.chnl_map;
    ble_user_info.adv_param.prim_cfg.phy  = params->prim_cfg.phy;
    ble_user_info.adv_param.second_cfg.max_skip  = params->second_cfg.max_skip;
    ble_user_info.adv_param.second_cfg.phy  = params->second_cfg.phy;
    ble_user_info.adv_param.second_cfg.adv_sid  = params->second_cfg.adv_sid;
    ble_user_info.adv_param.period_cfg.adv_intv_min  = params->period_cfg.adv_intv_min;
    ble_user_info.adv_param.period_cfg.adv_intv_max  = params->period_cfg.adv_intv_max;
    return ret;
}

void app_ble_set_adv_data(uint8_t *buf, uint16_t buf_len)
{
    ASSERT_WARN(buf_len <= ADV_DATA_LEN);
    ble_user_info.adv_data_len = co_min(buf_len, ADV_DATA_LEN);
    memcpy(ble_user_info.adv_data, buf, ble_user_info.adv_data_len);
}

void app_ble_set_scan_response_data(uint8_t *buf, uint16_t buf_len)
{
    ASSERT_WARN(buf_len <= ADV_DATA_LEN);
    ble_user_info.scan_res_len = co_min(buf_len, ADV_DATA_LEN);
    memcpy(ble_user_info.scan_res, buf, ble_user_info.scan_res_len);
}

void app_ble_set_ad_filter(struct ble_ad_filter *ad_filter)
{
    memcpy(&ble_user_info.ad_data_filter, (uint8_t *)ad_filter, sizeof(struct ble_ad_filter));
    TRACE("ad filter len = %d, ad_type = 0x%x\n",ble_user_info.ad_data_filter.len,ble_user_info.ad_data_filter.ad_type);
}

uint8_t app_ble_update_adv_data(void)
{
    if (app_env.adv_state == APP_ADV_STATE_STARTED) {
        appm_update_adv_data();
        return CO_ERROR_NO_ERROR;
    } else if (app_env.adv_state == APP_ADV_STATE_CREATED){
        appm_update_adv_data();
        return CO_ERROR_NO_ERROR;
    } else {
        return CO_ERROR_UNSUPPORTED;
    }
}

uint8_t app_ble_update_adv_scan_res(void)
{
    if (app_env.adv_state == APP_ADV_STATE_STARTED) {
        appm_update_adv_scan_res();
        return CO_ERROR_NO_ERROR;
    } else if (app_env.adv_state == APP_ADV_STATE_CREATED){
        appm_update_adv_scan_res();
        return CO_ERROR_NO_ERROR;
    } else {
        return CO_ERROR_UNSUPPORTED;
    }
}

uint8_t app_ble_update_adv_params(uint32_t adv_intv_min, uint32_t adv_intv_max)
{
    if (app_env.adv_state == APP_ADV_STATE_STARTED) {
        dbg("error, adv already started, please stop adv\r\n");
        return CO_ERROR_UNSUPPORTED;
    } else if ((adv_intv_max < adv_intv_min) || (adv_intv_max < 0x20) || (adv_intv_max < 0x20)) {
        dbg("intv error, adv intv is %d %d\r\n", adv_intv_max, adv_intv_min);
        return CO_ERROR_UNSUPPORTED;
    } else {
        ble_user_info.adv_param.prim_cfg.adv_intv_min = adv_intv_min;
        ble_user_info.adv_param.prim_cfg.adv_intv_max = adv_intv_max;
        appm_delete_advertising();
        return CO_ERROR_NO_ERROR;
    }
}

uint8_t app_ble_restart_adv(void)
{
    if (app_env.adv_state == APP_ADV_STATE_STARTED) {
        dbg("error, adv already started, please stop adv\r\n");
        return CO_ERROR_UNSUPPORTED;
    } else {
        appm_delete_advertising();
        return CO_ERROR_NO_ERROR;
    }
}

uint8_t app_ble_start_init()
{
    if (app_env.init_state == APP_INIT_STATE_STARTED) {
        dbg("error, init already started\r\n");
        return CO_ERROR_UNSUPPORTED;
    } else {
        appm_init_fsm_next();
        return CO_ERROR_NO_ERROR;
    }
}

uint8_t app_ble_stop_init()
{
    if (app_env.init_state == APP_INIT_STATE_STARTED) {
        appm_stop_initiating();
        return CO_ERROR_NO_ERROR;
    } else {
        dbg("error, init not started\r\n");
        return CO_ERROR_UNSUPPORTED;
    }
}

uint8_t app_ble_start_scan()
{
    if (app_env.scan_state == APP_SCAN_STATE_STARTED) {
        dbg("error, scan already started\r\n");
        return CO_ERROR_UNSUPPORTED;
    } else {
        appm_scan_fsm_next();
        return CO_ERROR_NO_ERROR;
    }
}

uint8_t app_ble_stop_scan()
{
    if (app_env.scan_state == APP_SCAN_STATE_STARTED) {
        appm_stop_scan();
        return CO_ERROR_NO_ERROR;
    } else {
        dbg("error, scan not started\r\n");
        return CO_ERROR_UNSUPPORTED;
    }
}

uint8_t app_ble_start_adv()
{
    if (app_env.adv_state == APP_ADV_STATE_STARTED) {
        dbg("error, adv already started\r\n");
        return CO_ERROR_UNSUPPORTED;
    } else {
        appm_adv_fsm_next();
        return CO_ERROR_NO_ERROR;
    }
}

uint8_t app_ble_stop_adv()
{
    if (app_env.adv_state == APP_ADV_STATE_STARTED) {
        appm_stop_advertising();
        return CO_ERROR_NO_ERROR;
    } else {
        dbg("error, adv not started\r\n");
        return CO_ERROR_UNSUPPORTED;
    }
}

uint8_t app_ble_disconnect(uint8_t conidx)
{
    if (ke_state_get(KE_BUILD_ID(TASK_APP,conidx)) == APPM_CONNECTED) {
        appm_disconnect(conidx);
        return CO_ERROR_NO_ERROR;
    } else {
        dbg("error, no connection\r\n");
        return CO_ERROR_UNSUPPORTED;
    }
}

uint8_t app_ble_update_con_params(uint8_t conidx,uint16_t conn_intv_min, uint16_t conn_intv_max,
                        uint16_t conn_latency, uint16_t time_out)
{
    if (ke_state_get(KE_BUILD_ID(TASK_APP,conidx)) == APPM_CONNECTED) {
        struct gapc_conn_param conn_param;
        conn_param.intv_min = conn_intv_min;
        conn_param.intv_max = conn_intv_max;
        conn_param.latency  = conn_latency;
        conn_param.time_out = time_out;
        appm_update_param(&conn_param,conidx);
        return CO_ERROR_NO_ERROR;
    } else {
        dbg("error, no connection\r\n");
        return CO_ERROR_UNSUPPORTED;
    }
}

void app_ble_update_addr(uint8_t *addr)
{
    memcpy(&ble_user_info.own_addr.addr[0], addr, BD_ADDR_LEN);
    gapm_set_bdaddr(addr);
}

void app_ble_oplist_init(void)
{
    co_dl_list_init(&ble_app_oplist);
}

void app_ble_check_oplist(void)
{
    if(!co_dl_list_is_empty(&ble_app_oplist) && app_env.adv_op == GAPM_NO_OP){
        BleAppOp *op = (BleAppOp *)co_dl_list_remove_list_head(&ble_app_oplist);
        // Send the message
        ke_msg_send(op->node.data);
        app_env.adv_op = op->opType;
        if(op->adv_state){
            app_env.adv_state = op->adv_state;
        }
        if(op->adv_state_prv){
            app_env.adv_state_prv = op->adv_state_prv;
        }
        //TRACE("OUT: %x ,%x ,%x\n",op->opType,op->adv_state,op->adv_state_prv);
        rtos_free(op);
    }
}

void app_ble_oplist_insert(uint8_t optype ,uint8_t adv_state ,uint8_t adv_state_prv ,void *cmdptr)
{
    BleAppOp *op = (BleAppOp *)rtos_malloc(sizeof(BleAppOp));
    if(!cmdptr || optype == 0 || !op){
        ASSERT_ERR(0);
    }
    //TRACE("IN: %x ,%x\n",optype,adv_state);

    op->opType = optype;
    op->adv_state = adv_state;
    op->adv_state_prv = adv_state_prv;
    op->node.data = cmdptr;

    co_dl_list_insert_tail(&ble_app_oplist,&op->node);
    app_ble_check_oplist();
}

bool app_env_check(void)
{
    bool ret = true;
    bool app_connected = false;
    for(uint8_t i = 0;i < APP_IDX_MAX;i++){
        if(ke_state_get(KE_BUILD_ID(TASK_APP,i)) == APPM_CONNECTED){
            app_connected=true;
        }
    }

    if (app_connected == true) {
        ret = false;
    }

    return ret;
}

#endif //(BLE_APP_PRESENT)

/// @} APP
