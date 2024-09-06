/**
 ****************************************************************************************
 *
 * @file udfc.h
 *
 * @brief Header file - user defined client Profile .
 *
 * Copyright (C) AIC
 *
 *
 ****************************************************************************************
 */

#ifndef _UDFC_H_
#define _UDFC_H_

/**
 ****************************************************************************************
 * @addtogroup User Defined Profile Client
 * @ingroup SmartConfig
 * @brief User Defined Profile Client
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

#if (BLE_UDF_CLIENT)
#include "prf_types.h"
#include "prf.h"
#include "udfc_task.h"
#include "attm.h"
#include "prf_utils.h"


/*
 * DEFINES
 ****************************************************************************************
 */
#define UDFC_MAX_LEN            (251)
///Maximum number of Aud Transmit Client task instances
#define UDFC_IDX_MAX    2//(BLE_CONNECTION_MAX)

/*
 * DEFINES
 ****************************************************************************************
 */
/// Possible states of the UDFC task
enum udfc_state
{
    /// Disconnected state
    UDFC_FREE,
    /// Idle state
    UDFC_IDLE,
    /// Connected state
    UDFC_BUSY,

    /// Number of defined states.
    UDFC_STATE_MAX,
};

enum udfc_operation
{
    /// No operation
    UDFC_OP_NONE = 0,
    /// Discover peer service
    UDFC_OP_DISCOVER,
    /// Write Notification configuration
    UDFC_OP_WR_NTF_CFG,
    /// Write Indication configuration
    UDFC_OP_WR_IND_CFG,
    /// Write 
    UDFC_OP_WR,
    /// Write No Responce
    UDFC_OP_WR_NORES,
    /// Read
    UDFC_OP_RD,
};


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Environment variable for each Connections
struct udfc_cnx_env
{
    ///discovered svc characteristics
    struct discovered_svc_content ats;
    /// on-going operation
    uint8_t operation;
};

/// Aud Transmit Profile Client environment variable
struct udfc_env_tag
{
    /// profile environment
    prf_env_t prf_env;
    /// Environment variable pointer for each connections
    struct udfc_cnx_env* env[UDFC_IDX_MAX];
    /// State of different task instances
    ke_state_t state[UDFC_IDX_MAX];
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
const struct prf_task_cbs* udfc_prf_itf_get(void);


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
void udfc_task_init(struct ke_task_desc *task_desc);

/**
 ****************************************************************************************
 * @brief Send UDF ATT DB discovery results to SCPPC host.
 ****************************************************************************************
 */
void udfc_enable_rsp_send(struct udfc_env_tag *udfc_env, uint8_t conidx, uint8_t status);


#endif /* #if (BLE_UDF_CLIENT) */

/// @} UDF

#endif /* _UDFC_H_ */

