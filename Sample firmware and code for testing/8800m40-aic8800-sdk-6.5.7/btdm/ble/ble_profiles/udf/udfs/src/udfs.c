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

#if (BLE_UDF_SERVER)
#include "gap.h"
#include "gattc_task.h"
#include "attm.h"
#include "gapc_task.h"
#include "udfs.h"
#include "udfs_task.h"
#include "prf_utils.h"
#include "ke_mem.h"
#include "ble_utils.h"


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
static uint8_t udfs_init(struct prf_task_env* env, uint16_t* start_hdl,
    uint16_t app_task, uint8_t sec_lvl, void* params)
{
    uint8_t status = ATT_ERR_APP_ERROR;

    struct udfs_db_cfg *db_cfg = (struct udfs_db_cfg *)params;

    dbg("BLE: %s \r\n", __func__);
    if(!db_cfg){
        return status;
    }

    //Add Service Into Database
    status = attm_svc_create_db_128(start_hdl, db_cfg->uuid, NULL,
            db_cfg->att_num, NULL, env->task, db_cfg->att_db,
            (sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS))| PERM(SVC_MI, ENABLE)
            | PERM_VAL(SVC_UUID_LEN, PERM_UUID_128));
    dbg("BLE:%s status = %x\r\n", __func__,status);

    //-------------------- allocate memory required for the profile  ---------------------
    if (status == ATT_ERR_NO_ERROR)
    {
        // Allocate SMARTCONFIG required environment variable
        struct udfs_env_tag* udfs =
                (struct udfs_env_tag* ) ke_malloc(sizeof(struct udfs_env_tag), KE_MEM_ATT_DB);

        // Initialize SMARTCONFIG environment
        env->env = (prf_env_t*) udfs;
        udfs->shdl = *start_hdl;

        udfs->prf_env.app_task = app_task
                | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
        // Mono Instantiated task
        udfs->prf_env.prf_task = env->task | PERM(PRF_MI, ENABLE);
        udfs->att_num = db_cfg->att_num;
        udfs->att_db = db_cfg->att_db;
        udfs->prf_user_id = db_cfg->prf_user_id;

        // initialize environment variable
        env->id = TASK_ID_UDFS+db_cfg->prf_user_id;
        udfs_task_init(&(env->desc),udfs);

        /* Put HRS in Idle state */
        ke_state_set(env->task, UDFS_IDLE);
    }

    return (status);
}

/**
 ****************************************************************************************
 * @brief Destruction of the UDFS module - due to a reset for instance.
 * This function clean-up allocated memory (attribute database is destroyed by another
 * procedure)
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 ****************************************************************************************
 */
static void udfs_destroy(struct prf_task_env* env)
{
    struct udfs_env_tag* udfs_env = (struct udfs_env_tag*) env->env;

    // free profile environment variables
    env->env = NULL;
    ke_free(udfs_env);
}

/**
 ****************************************************************************************
 * @brief Handles Connection creation
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 ****************************************************************************************
 */
static void udfs_create(struct prf_task_env* env, uint8_t conidx)
{
    //struct udfs_env_tag* udfs_env = (struct udfs_env_tag*) env->env;
    //struct prf_svc udfs_svc = {udfs_env->shdl, udfs_env->shdl + UDFS_IDX_NB};
    //prf_register_atthdl2gatt(env->env, conidx, &udfs_svc);
    ke_state_set(KE_BUILD_ID(env->task, conidx), UDFS_IDLE);
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
static void udfs_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    /* Nothing to do */
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// SMARTCONFIG Task interface required by profile manager
const struct prf_task_cbs udfs_itf =
{
    (prf_init_fnct) udfs_init,
    udfs_destroy,
    udfs_create,
    udfs_cleanup,
};

/*
 * EXPORTED FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

const struct prf_task_cbs* udfs_prf_itf_get(void)
{
   return &udfs_itf;
}


#endif /* BLE_UDF_SERVER */

/// @} UDFS

