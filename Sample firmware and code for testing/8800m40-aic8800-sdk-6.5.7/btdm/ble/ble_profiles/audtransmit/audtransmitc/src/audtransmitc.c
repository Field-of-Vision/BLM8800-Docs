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

#if (BLE_AUDTRANSMIT_CLIENT)
#include "gap.h"
#include "gattc_task.h"
#include "attm.h"
#include "gapc_task.h"
#include "audtransmitc.h"
#include "audtransmitc_task.h"
#include "prf_utils.h"
#include "ke_mem.h"
#include "ble_utils.h"


/**
 ****************************************************************************************
 * @brief Initialization of the AUDTRANSMITC module.
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
static uint8_t audtransmitc_init(struct prf_task_env* env, uint16_t* start_hdl,
    uint16_t app_task, uint8_t sec_lvl, void* params)
{
    uint8_t idx;

    dbg("%s \r\n", __func__);

    //-------------------- allocate memory required for the profile  ---------------------
    // Allocate SMARTCONFIG required environment variable
    struct audtransmitc_env_tag* audtransmitc_env =
            (struct audtransmitc_env_tag* ) ke_malloc(sizeof(struct audtransmitc_env_tag), KE_MEM_ATT_DB);

    // Initialize SMARTCONFIG environment
    env->env = (prf_env_t*) audtransmitc_env;

    audtransmitc_env->prf_env.app_task = app_task
            | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
    audtransmitc_env->prf_env.prf_task = env->task | PERM(PRF_MI, ENABLE);

    // initialize environment variable
    env->id = TASK_ID_AUDTRANSMITC;
    audtransmitc_task_init(&(env->desc));

    for(idx = 0; idx < AUDTRANSMITC_IDX_MAX ; idx++)
    {
        audtransmitc_env->env[idx] = NULL;
        // service is ready, go into an Idle state
        ke_state_set(KE_BUILD_ID(env->task, idx), AUDTRANSMITC_FREE);
    }

    return GAP_ERR_NO_ERROR;
}

/**
 ****************************************************************************************
 * @brief Destruction of the AUDTRANSMITC module - due to a reset for instance.
 * This function clean-up allocated memory (attribute database is destroyed by another
 * procedure)
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 ****************************************************************************************
 */
static void audtransmitc_destroy(struct prf_task_env* env)
{
    uint8_t idx;
    struct audtransmitc_env_tag* audtransmitc_env = (struct audtransmitc_env_tag*) env->env;

    // cleanup environment variable for each task instances
    for(idx = 0; idx < AUDTRANSMITC_IDX_MAX ; idx++)
    {
        if(audtransmitc_env->env[idx] != NULL)
        {
            ke_free(audtransmitc_env->env[idx]);
        }
    }

    // free profile environment variables
    env->env = NULL;
    ke_free(audtransmitc_env);
}

/**
 ****************************************************************************************
 * @brief Handles Connection creation
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 ****************************************************************************************
 */
static void audtransmitc_create(struct prf_task_env* env, uint8_t conidx)
{
    TRACE("%s ,id = %x\n",__func__,KE_BUILD_ID(env->task, conidx));
    ke_state_set(KE_BUILD_ID(env->task, conidx), AUDTRANSMITC_IDLE);
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
static void audtransmitc_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    struct audtransmitc_env_tag* audtransmitc_env = (struct audtransmitc_env_tag*) env->env;

    // clean-up environment variable allocated for task instance
    if(audtransmitc_env->env[conidx] != NULL)
    {
        ke_free(audtransmitc_env->env[conidx]);
        audtransmitc_env->env[conidx] = NULL;
    }

    /* Put SCPP Client in Free state */
    ke_state_set(KE_BUILD_ID(env->task, conidx), AUDTRANSMITC_FREE);
}


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// AUDTRANSMITC Task interface required by profile manager
const struct prf_task_cbs audtransmitc_itf =
{
    (prf_init_fnct) audtransmitc_init,
    audtransmitc_destroy,
    audtransmitc_create,
    audtransmitc_cleanup,
};

/*
 * EXPORTED FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

const struct prf_task_cbs* audtransmitc_prf_itf_get(void)
{
   return &audtransmitc_itf;
}

void audtransmitc_enable_rsp_send(struct audtransmitc_env_tag *audtransmitc_env, uint8_t conidx, uint8_t status)
{
    //send APP the details of the discovered attributes on SCPPC
    struct audtransmitc_enable_rsp * rsp = KE_MSG_ALLOC(AUDTRANSMITC_ENABLE_RSP,
                                                 prf_dst_task_get(&(audtransmitc_env->prf_env) ,conidx),
                                                 prf_src_task_get(&(audtransmitc_env->prf_env) ,conidx),
                                                 audtransmitc_enable_rsp);

    rsp->status = status;
    TRACE("BLE: %s status = %x desc_id %x,src_id %x,\n",__func__,status,prf_dst_task_get(&(audtransmitc_env->prf_env) ,conidx),prf_src_task_get(&(audtransmitc_env->prf_env) ,conidx));
    if (status == GAP_ERR_NO_ERROR)
    {
        rsp->ats = audtransmitc_env->env[conidx]->ats;

        // If Scan Refresh Char. has been discovered
        if (audtransmitc_env->env[conidx]->ats.chars[AUDTRANSMITC_CHAR_DATA_RECV].char_hdl != ATT_INVALID_HANDLE)
        {
            TRACE("BLE: %s Register AudTransmitC task in gatt for notifications %x\n",__func__,\
                audtransmitc_env->env[conidx]->ats.chars[AUDTRANSMITC_CHAR_DATA_RECV].char_hdl);
            // Register AudTransmitC task in gatt for notifications
            prf_register_atthdl2gatt(&(audtransmitc_env->prf_env), conidx, &audtransmitc_env->env[conidx]->ats.svc);
        }
    }
    else
    {
        memset(&rsp->ats, 0 , sizeof(rsp->ats));
    }

    ke_msg_send(rsp);
}


#endif /* BLE_AUDTRANSMIT_CLIENT */

/// @} AUDTRANSMITC

