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

#if (BLE_AUDTRANSMIT_SERVER)
#include "gap.h"
#include "gattc_task.h"
#include "attm.h"
#include "gapc_task.h"
#include "audtransmits.h"
#include "audtransmits_task.h"
#include "prf_utils.h"
#include "ke_mem.h"
#include "ble_utils.h"


/*
 * AUDTRANSMIT CMD PROFILE ATTRIBUTES
 ****************************************************************************************
 */
#define audtransmits_service_uuid_128_content                {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x01,0xfe,0x00,0x00}
#define audtransmits_aud_info_val_uuid_128_content           {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x02,0xfe,0x00,0x00}
#define audtransmits_aud_control_val_uuid_128_content        {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x03,0xfe,0x00,0x00}
#define audtransmits_aud_data_send_val_uuid_128_content      {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x04,0xfe,0x00,0x00}
#define audtransmits_aud_data_recv_val_uuid_128_content      {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x05,0xfe,0x00,0x00}

#define ATT_DECL_PRIMARY_SERVICE_UUID           {0x00, 0x28}
#define ATT_DECL_CHARACTERISTIC_UUID            {0x03, 0x28}
#define ATT_DESC_CLIENT_CHAR_CFG_UUID           {0x02, 0x29}

static const uint8_t AUDTRANSMITS_SERVICE_UUID_128[ATT_UUID_128_LEN]    = audtransmits_service_uuid_128_content;

/// Full AUDTRANSMITS_SERVICE Database Description - Used to add attributes into the database
const struct attm_desc_128 audtransmits_att_db[AUDTRANSMITS_IDX_NB] =
{
    // Service Declaration
    [AUDTRANSMITS_IDX_SVC]                  =   {ATT_DECL_PRIMARY_SERVICE_UUID, PERM(RD, ENABLE), 0, 0},

    // Command TX Characteristic Declaration
    [AUDTRANSMITS_IDX_AUD_INFO_CHAR]        =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Command TX Characteristic Value
    [AUDTRANSMITS_IDX_AUD_INFO_VAL]         =   {audtransmits_aud_info_val_uuid_128_content, PERM(NTF, ENABLE) | PERM(IND, ENABLE) | PERM(RD, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), AUDTRANSMITS_MAX_LEN},
    // Command TX Characteristic - Client Characteristic Configuration Descriptor
    [AUDTRANSMITS_IDX_AUD_INFO_NTF_CFG]     =   {ATT_DESC_CLIENT_CHAR_CFG_UUID, PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE), 0, 0},

    // Command RX Characteristic Declaration
    [AUDTRANSMITS_IDX_AUD_CTRL_CHAR]        =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Command RX Characteristic Value
    [AUDTRANSMITS_IDX_AUD_CTRL_VAL]         =   {audtransmits_aud_control_val_uuid_128_content,
        PERM(WRITE_REQ, ENABLE)| PERM(WRITE_COMMAND, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), AUDTRANSMITS_MAX_LEN},

    // Data TX Characteristic Declaration
    [AUDTRANSMITS_IDX_DATA_SEND_CHAR]       =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Data TX Characteristic Value
    [AUDTRANSMITS_IDX_DATA_SEND_VAL]        =   {audtransmits_aud_data_send_val_uuid_128_content, PERM(NTF, ENABLE) | PERM(IND, ENABLE) | PERM(RD, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), AUDTRANSMITS_MAX_LEN},
    // Data TX Characteristic - Client Characteristic Configuration Descriptor
    [AUDTRANSMITS_IDX_DATA_SEND_NTF_CFG]    =   {ATT_DESC_CLIENT_CHAR_CFG_UUID, PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE), 0, 0},

    // Data RX Characteristic Declaration
    [AUDTRANSMITS_IDX_DATA_RECV_CHAR]       =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Data RX Characteristic Value
    [AUDTRANSMITS_IDX_DATA_RECV_VAL]        =   {audtransmits_aud_data_recv_val_uuid_128_content,
        PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), AUDTRANSMITS_MAX_LEN},
};

/**
 ****************************************************************************************
 * @brief Initialization of the Audtransmits module.
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
static uint8_t audtransmits_init(struct prf_task_env* env, uint16_t* start_hdl,
    uint16_t app_task, uint8_t sec_lvl, void* params)
{
    dbg("BLE: %s \r\n", __func__);

    uint8_t status = 0;

    //Add Service Into Database
    status = attm_svc_create_db_128(start_hdl, AUDTRANSMITS_SERVICE_UUID_128, NULL,
            AUDTRANSMITS_IDX_NB, NULL, env->task, &audtransmits_att_db[0],
            (sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS))| PERM(SVC_MI, DISABLE)
            | PERM_VAL(SVC_UUID_LEN, PERM_UUID_128));
    dbg("BLE:%s status = %x\r\n", __func__,status);

    //-------------------- allocate memory required for the profile  ---------------------
    if (status == ATT_ERR_NO_ERROR)
    {
        // Allocate SMARTCONFIG required environment variable
        struct audtransmits_env_tag* audtransmits =
                (struct audtransmits_env_tag* ) ke_malloc(sizeof(struct audtransmits_env_tag), KE_MEM_ATT_DB);

        // Initialize SMARTCONFIG environment
        env->env = (prf_env_t*) audtransmits;
        audtransmits->shdl = *start_hdl;

        audtransmits->prf_env.app_task = app_task
                | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
        // Mono Instantiated task
        audtransmits->prf_env.prf_task = env->task | PERM(PRF_MI, DISABLE);

        // initialize environment variable
        env->id = TASK_ID_AUDTRANSMITS;
        audtransmits_task_init(&(env->desc));

        /* Put HRS in Idle state */
        ke_state_set(env->task, AUDTRANSMITS_IDLE);
    }

    return (status);
}

/**
 ****************************************************************************************
 * @brief Destruction of the AUDTRANSMITS module - due to a reset for instance.
 * This function clean-up allocated memory (attribute database is destroyed by another
 * procedure)
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 ****************************************************************************************
 */
static void audtransmits_destroy(struct prf_task_env* env)
{
    struct audtransmits_env_tag* audtransmits_env = (struct audtransmits_env_tag*) env->env;

    // free profile environment variables
    env->env = NULL;
    ke_free(audtransmits_env);
}

/**
 ****************************************************************************************
 * @brief Handles Connection creation
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 ****************************************************************************************
 */
static void audtransmits_create(struct prf_task_env* env, uint8_t conidx)
{
    //struct audtransmits_env_tag* audtransmits_env = (struct audtransmits_env_tag*) env->env;
    //struct prf_svc audtransmits_svc = {audtransmits_env->shdl, audtransmits_env->shdl + AUDTRANSMITS_IDX_NB};
    //prf_register_atthdl2gatt(env->env, conidx, &audtransmits_svc);
    ke_state_set(KE_BUILD_ID(env->task, conidx), AUDTRANSMITS_IDLE);
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
static void audtransmits_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    /* Nothing to do */
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// SMARTCONFIG Task interface required by profile manager
const struct prf_task_cbs audtransmits_itf =
{
    (prf_init_fnct) audtransmits_init,
    audtransmits_destroy,
    audtransmits_create,
    audtransmits_cleanup,
};

/*
 * EXPORTED FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

const struct prf_task_cbs* audtransmits_prf_itf_get(void)
{
   return &audtransmits_itf;
}


#endif /* BLE_AUDTRANSMIT_SERVER */

/// @} AUDTRANSMITS

