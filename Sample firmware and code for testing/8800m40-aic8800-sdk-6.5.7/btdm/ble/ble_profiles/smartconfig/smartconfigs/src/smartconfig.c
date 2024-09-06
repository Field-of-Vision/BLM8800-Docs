/**
 ****************************************************************************************
 *
 * @file smartconfig.c
 *
 * @brief Smart Config profile implementation.
 *
 * Copyright (C) AIC
 *
 *
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
#include "attm.h"
#include "smartconfig.h"
#include "smartconfig_task.h"
#include "prf_utils.h"
#include "ke_mem.h"
#include "ble_utils.h"


/*
 * SMART CONFIG CMD PROFILE ATTRIBUTES
 ****************************************************************************************
 */
#define smartconfig_service_uuid_128_content                {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0xe7,0xfe,0x00,0x00}
#define smartconfig_cmd_ap_info_val_uuid_128_content        {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0xc7,0xfe,0x00,0x00}
#define smartconfig_cmd_wifi_state_val_uuid_128_content     {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0xc8,0xfe,0x00,0x00}
#define smartconfig_time_state_char_val_uuid_128_content    {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0xc9,0xfe,0x00,0x00}
#define smartconfig_time_char_val_uuid_128_content          {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0xca,0xfe,0x00,0x00}

#define ATT_DECL_PRIMARY_SERVICE_UUID           {0x00, 0x28}
#define ATT_DECL_CHARACTERISTIC_UUID            {0x03, 0x28}
#define ATT_DESC_CLIENT_CHAR_CFG_UUID           {0x02, 0x29}

static const uint8_t SMARTCONFIG_SERVICE_UUID_128[ATT_UUID_128_LEN]    = smartconfig_service_uuid_128_content;

/// Full SMARTCONFIG SERVER Database Description - Used to add attributes into the database
const struct attm_desc_128 smartconfig_att_db[SMARTCONFIG_IDX_NB] =
{
    // Service Declaration
    [SMARTCONFIG_IDX_SVC]                =   {ATT_DECL_PRIMARY_SERVICE_UUID, PERM(RD, ENABLE), 0, 0},

    // Command TX Characteristic Declaration
    [SMARTCONFIG_IDX_WIFI_STATE_CHAR]        =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Command TX Characteristic Value
    [SMARTCONFIG_IDX_WIFI_STATE_VAL]         =   {smartconfig_cmd_wifi_state_val_uuid_128_content, PERM(NTF, ENABLE) | PERM(IND, ENABLE) | PERM(RD, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), SMARTCONFIG_MAX_LEN},
    // Command TX Characteristic - Client Characteristic Configuration Descriptor
    [SMARTCONFIG_IDX_WIFI_STATE_NTF_CFG]     =   {ATT_DESC_CLIENT_CHAR_CFG_UUID, PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE), 0, 0},

    // Command RX Characteristic Declaration
    [SMARTCONFIG_IDX_AP_INFO_CHAR]        =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Command RX Characteristic Value
    [SMARTCONFIG_IDX_AP_INFO_VAL]         =   {smartconfig_cmd_ap_info_val_uuid_128_content,
        PERM(WRITE_REQ, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), SMARTCONFIG_MAX_LEN},

    // Data TX Characteristic Declaration
    [SMARTCONFIG_IDX_TIME_STATE_CHAR]       =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Data TX Characteristic Value
    [SMARTCONFIG_IDX_TIME_STATE_VAL]        =   {smartconfig_time_state_char_val_uuid_128_content, PERM(NTF, ENABLE) | PERM(IND, ENABLE) | PERM(RD, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), SMARTCONFIG_MAX_LEN},
    // Data TX Characteristic - Client Characteristic Configuration Descriptor
    [SMARTCONFIG_IDX_TIME_STATE_NTF_CFG]    =   {ATT_DESC_CLIENT_CHAR_CFG_UUID, PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE), 0, 0},

    // Data RX Characteristic Declaration
    [SMARTCONFIG_IDX_TIME_INFO_CHAR]       =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Data RX Characteristic Value
    [SMARTCONFIG_IDX_TIME_INFO_VAL]        =   {smartconfig_time_char_val_uuid_128_content,
        PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), SMARTCONFIG_MAX_LEN},

};

/**
 ****************************************************************************************
 * @brief Initialization of the SMARTCONFIG module.
 * This function performs all the initializations of the Profile module.
 *  - Creation of database (if it's a service)
 *  - Allocation of profile required memory
 *  - Initialization of task descriptor to register application
 *      - Task State array
 *      - Number of tasks
 *      - Default task handler
 *
 * @param[out]    env        Collector or Service allocated environment data.
 * @param[in|out] start_hdl  Service start handle (0 - dynamically allocated), only applies for services.
 * @param[in]     app_task   Application task number.
 * @param[in]     sec_lvl    Security level (AUTH, EKS and MI field of @see enum attm_value_perm_mask)
 * @param[in]     param      Configuration parameters of profile collector or service (32 bits aligned)
 *
 * @return status code to know if profile initialization succeed or not.
 ****************************************************************************************
 */
static uint8_t smartconfig_init(struct prf_task_env* env, uint16_t* start_hdl,
    uint16_t app_task, uint8_t sec_lvl, void* params)
{
    dbg("%s \r\n", __func__);

    uint8_t status;

    //Add Service Into Database
    status = attm_svc_create_db_128(start_hdl, SMARTCONFIG_SERVICE_UUID_128, NULL,
            SMARTCONFIG_IDX_NB, NULL, env->task, &smartconfig_att_db[0],
            (sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS))| PERM(SVC_MI, DISABLE)
            | PERM_VAL(SVC_UUID_LEN, PERM_UUID_128));

    //-------------------- allocate memory required for the profile  ---------------------
    if (status == ATT_ERR_NO_ERROR)
    {
        // Allocate SMARTCONFIG required environment variable
        struct smartconfig_env_tag* smartconfig_env =
                (struct smartconfig_env_tag* ) ke_malloc(sizeof(struct smartconfig_env_tag), KE_MEM_ATT_DB);

        // Initialize SMARTCONFIG environment
        env->env = (prf_env_t*) smartconfig_env;
        smartconfig_env->shdl = *start_hdl;

        smartconfig_env->prf_env.app_task = app_task
                | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
        // Mono Instantiated task
        smartconfig_env->prf_env.prf_task = env->task | PERM(PRF_MI, DISABLE);

        // initialize environment variable
        env->id = TASK_ID_SMARTCONFIG;
        smartconfig_task_init(&(env->desc));

        /* Put HRS in Idle state */
        ke_state_set(env->task, SMARTCONFIG_IDLE);
    }

    return (status);
}

/**
 ****************************************************************************************
 * @brief Destruction of the SMARTCONFIG module - due to a reset for instance.
 * This function clean-up allocated memory (attribute database is destroyed by another
 * procedure)
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 ****************************************************************************************
 */
static void smartconfig_destroy(struct prf_task_env* env)
{
    struct smartconfig_env_tag* smartconfig_env = (struct smartconfig_env_tag*) env->env;

    // free profile environment variables
    env->env = NULL;
    ke_free(smartconfig_env);
}

/**
 ****************************************************************************************
 * @brief Handles Connection creation
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 ****************************************************************************************
 */
static void smartconfig_create(struct prf_task_env* env, uint8_t conidx)
{
    /* Nothing to do */
}

/**
 ****************************************************************************************
 * @brief Handles Disconnection
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 * @param[in]        reason     Detach reason
 ****************************************************************************************
 */
static void smartconfig_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    /* Nothing to do */
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// SMARTCONFIG Task interface required by profile manager
const struct prf_task_cbs smartconfig_itf =
{
    (prf_init_fnct) smartconfig_init,
    smartconfig_destroy,
    smartconfig_create,
    smartconfig_cleanup,
};

/*
 * EXPORTED FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

const struct prf_task_cbs* smartconfig_prf_itf_get(void)
{
   return &smartconfig_itf;
}


#endif /* BLE_SMARTCONFIG */

/// @} SMARTCONFIG

