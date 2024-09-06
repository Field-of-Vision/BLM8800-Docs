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

#if (BLE_UDF_CLIENT)
#include "gap.h"
#include "gattc_task.h"
#include "attm.h"
#include "gapc_task.h"
#include "udfc.h"
#include "udfc_task.h"
#include "prf_utils.h"
#include "ke_mem.h"
#include "ble_utils.h"


/**
 ****************************************************************************************
 * @brief Initialization of the UDFC module.
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
static uint8_t udfc_init(struct prf_task_env* env, uint16_t* start_hdl,
    uint16_t app_task, uint8_t sec_lvl, void* params)
{
    uint8_t idx;

    dbg("%s \r\n", __func__);

    //-------------------- allocate memory required for the profile  ---------------------
    // Allocate SMARTCONFIG required environment variable
    struct udfc_env_tag* udfc_env =
            (struct udfc_env_tag* ) ke_malloc(sizeof(struct udfc_env_tag), KE_MEM_ATT_DB);

    // Initialize SMARTCONFIG environment
    env->env = (prf_env_t*) udfc_env;

    udfc_env->prf_env.app_task = app_task
            | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
    udfc_env->prf_env.prf_task = env->task | PERM(PRF_MI, ENABLE);

    // initialize environment variable
    env->id = TASK_ID_UDFC;
    udfc_task_init(&(env->desc));

    for(idx = 0; idx < UDFC_IDX_MAX ; idx++)
    {
        udfc_env->env[idx] = NULL;
        // service is ready, go into an Idle state
        ke_state_set(KE_BUILD_ID(env->task, idx), UDFC_FREE);
    }

    return GAP_ERR_NO_ERROR;
}

/**
 ****************************************************************************************
 * @brief Destruction of the UDFC module - due to a reset for instance.
 * This function clean-up allocated memory (attribute database is destroyed by another
 * procedure)
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 ****************************************************************************************
 */
static void udfc_destroy(struct prf_task_env* env)
{
    uint8_t idx;
    struct udfc_env_tag* udfc_env = (struct udfc_env_tag*) env->env;

    // cleanup environment variable for each task instances
    for(idx = 0; idx < UDFC_IDX_MAX ; idx++)
    {
        if(udfc_env->env[idx] != NULL)
        {
            for(uint8_t i = 0; i < MAX_DISCOVERD_SCV_NUM; i++){
                if(udfc_env->env[idx]->ats.scv_info[i] != NULL){
                    ke_free(udfc_env->env[idx]->ats.scv_info[i]);
                }
            }
            ke_free(udfc_env->env[idx]);
        }
    }

    // free profile environment variables
    env->env = NULL;
    ke_free(udfc_env);
}

/**
 ****************************************************************************************
 * @brief Handles Connection creation
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 ****************************************************************************************
 */
static void udfc_create(struct prf_task_env* env, uint8_t conidx)
{
    TRACE("%s ,id = %x\n",__func__,KE_BUILD_ID(env->task, conidx));
    ke_state_set(KE_BUILD_ID(env->task, conidx), UDFC_IDLE);
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
static void udfc_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    struct udfc_env_tag* udfc_env = (struct udfc_env_tag*) env->env;

    // clean-up environment variable allocated for task instance
    if(udfc_env->env[conidx] != NULL)
    {
        for(uint8_t i = 0; i < MAX_DISCOVERD_SCV_NUM; i++){
            if(udfc_env->env[conidx]->ats.scv_info[i] != NULL){
                ke_free(udfc_env->env[conidx]->ats.scv_info[i]);
                udfc_env->env[conidx]->ats.scv_info[i] = NULL;
            }
        }
        ke_free(udfc_env->env[conidx]);
        udfc_env->env[conidx] = NULL;
    }

    /* Put SCPP Client in Free state */
    ke_state_set(KE_BUILD_ID(env->task, conidx), UDFC_FREE);
}


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// UDFC Task interface required by profile manager
const struct prf_task_cbs udfc_itf =
{
    (prf_init_fnct) udfc_init,
    udfc_destroy,
    udfc_create,
    udfc_cleanup,
};

/*
 * EXPORTED FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

const struct prf_task_cbs* udfc_prf_itf_get(void)
{
   return &udfc_itf;
}

void udfc_enable_rsp_send(struct udfc_env_tag *udfc_env, uint8_t conidx, uint8_t status)
{
    //send APP the details of the discovered attributes on SCPPC
    struct udfc_enable_rsp * rsp = KE_MSG_ALLOC(UDFC_ENABLE_RSP,
                                                 prf_dst_task_get(&(udfc_env->prf_env) ,conidx),
                                                 prf_src_task_get(&(udfc_env->prf_env) ,conidx),
                                                 udfc_enable_rsp);

    rsp->status = status;
    rsp->conidx = conidx;
    TRACE("BLE: %s status = %x desc_id %x,src_id %x,\n",__func__,status,prf_dst_task_get(&(udfc_env->prf_env) ,conidx),prf_src_task_get(&(udfc_env->prf_env) ,conidx));
    if (status == GAP_ERR_NO_ERROR)
    {
        rsp->ats = &udfc_env->env[conidx]->ats;

        for(uint8_t svc_idx = 0; svc_idx < udfc_env->env[conidx]->ats.nb_svc; svc_idx++){
            bool need_register = false;
            struct prf_disc_sdp_svc_info *svc_info = udfc_env->env[conidx]->ats.scv_info[svc_idx];
            struct prf_svc prf_scv_info;
            prf_scv_info.shdl = svc_info->start_hdl;
            prf_scv_info.ehdl = svc_info->end_hdl;

            for(uint8_t char_idx = 0; char_idx < svc_info->num_of_char; char_idx++ ){
                if(svc_info->info[char_idx].desc_hdl!= ATT_INVALID_HANDLE){
                    TRACE("BLE: svc_idx %d, char_idx %d ,desc_hdl %d\n",\
                        svc_idx,char_idx,svc_info->info[char_idx].desc_hdl);
                    need_register = true;
                }
            }
            if(need_register){
                prf_register_atthdl2gatt(&(udfc_env->prf_env), conidx, &prf_scv_info);
            }
        }
    }
    else
    {
        memset(&rsp->ats, 0 , sizeof(rsp->ats));
    }

    ke_msg_send(rsp);
}


#endif /* BLE_UDF_CLIENT */

/// @} UDFC

