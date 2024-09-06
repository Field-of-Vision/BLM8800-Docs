/**
 ****************************************************************************************
 *
 * @file smartconfig.h
 *
 * @brief Header file - Smart Config Profile Server.
 *
 * Copyright (C) AIC
 *
 *
 ****************************************************************************************
 */

#ifndef _SMARTCONFIG_H_
#define _SMARTCONFIG_H_

/**
 ****************************************************************************************
 * @addtogroup SmartConfig Profile Server
 * @ingroup SmartConfig
 * @brief SmartConfig Profile Server
 *
 * Datapath Profile Server provides functionalities to upper layer module
 * application. The device using this profile takes the role of Datapath Server.
 *
 * The interface of this role to the Application is:
 *  - Enable the profile role (from APP)
 *  - Disable the profile role (from APP)
 *  - Send data to peer device via notifications  (from APP)
 *  - Receive data from peer device via write no response (from APP)
 *
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"

#if (BLE_SMARTCONFIG)
#include "prf_types.h"
#include "prf.h"
#include "smartconfig_task.h"
#include "attm.h"
#include "prf_utils.h"


/*
 * DEFINES
 ****************************************************************************************
 */
#define SMARTCONFIG_MAX_LEN            (200)

/*
 * DEFINES
 ****************************************************************************************
 */
/// Possible states of the SMARTCONFIG task
enum
{
    /// Idle state
    SMARTCONFIG_IDLE,
    /// Connected state
    SMARTCONFIG_BUSY,

    /// Number of defined states.
    SMARTCONFIG_STATE_MAX,
};

///Attributes State Machine
enum
{
    SMARTCONFIG_IDX_SVC,

    SMARTCONFIG_IDX_WIFI_STATE_CHAR,
    SMARTCONFIG_IDX_WIFI_STATE_VAL,
    SMARTCONFIG_IDX_WIFI_STATE_NTF_CFG,

    SMARTCONFIG_IDX_AP_INFO_CHAR,
    SMARTCONFIG_IDX_AP_INFO_VAL,

    SMARTCONFIG_IDX_TIME_STATE_CHAR,
    SMARTCONFIG_IDX_TIME_STATE_VAL,
    SMARTCONFIG_IDX_TIME_STATE_NTF_CFG,

    SMARTCONFIG_IDX_TIME_INFO_CHAR,
    SMARTCONFIG_IDX_TIME_INFO_VAL,

    SMARTCONFIG_IDX_NB,
};


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Datapath Profile Server environment variable
struct smartconfig_env_tag
{
    /// profile environment
    prf_env_t   prf_env;
    /// Notification configuration
    uint8_t     wifi_state_ntf_cfg;
    /// Notification configuration
    uint8_t     time_ntf_cfg;
    /// Service Start Handle
    uint16_t    shdl;
    /// State of different task instances
    ke_state_t  state;
};


/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Retrieve HRP service profile interface
 *
 * @return HRP service profile interface
 ****************************************************************************************
 */
const struct prf_task_cbs* smartconfig_prf_itf_get(void);


/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * Initialize task handler
 *
 * @param task_desc Task descriptor to fill
 ****************************************************************************************
 */
void smartconfig_task_init(struct ke_task_desc *task_desc);



#endif /* #if (BLE_SMARTCONFIG) */

/// @} SMARTCONFIG

#endif /* _SMARTCONFIG_H_ */

