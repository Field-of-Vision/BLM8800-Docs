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

#ifndef _UDFS_H_
#define _UDFS_H_

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

#if (BLE_UDF_SERVER)
#include "prf_types.h"
#include "prf.h"
#include "udfs_task.h"
#include "attm.h"
#include "prf_utils.h"


/*
 * DEFINES
 ****************************************************************************************
 */
#define UDFS_MAX_LEN            (200)
#define UDFS_MAX_CONN_IDX       BLE_CONNECTION_MAX
/*
 * DEFINES
 ****************************************************************************************
 */
/// Possible states of the UDF task
enum
{
    /// Idle state
    UDFS_IDLE,
    /// Connected state
    UDFS_BUSY,

    /// Number of defined states.
    UDFS_STATE_MAX,
};

enum udfs_operation
{
    /// No operation
    UDFS_OP_NONE = 0,

    /// Send Notification
    UDFC_OP_SD_NTF,
    /// Send Indication
    UDFC_OP_SD_IND,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Datapath Profile Server environment variable
struct udfs_env_tag
{
    /// profile environment
    prf_env_t   prf_env;
    /// Service Start Handle
    uint16_t    shdl;
    /// User define prf id
    uint16_t prf_user_id;
    /// State of different task instances
    ke_state_t  state;
    /// on-going operation
    uint8_t operation;
    /// Number of att
    uint8_t att_num;
    /// Attribute database
    struct attm_desc_128* att_db;
};

struct udfs_db_cfg
{
    uint16_t prf_user_id;
    /// Servece uuid
    uint8_t uuid[16];
    /// Number of att
    uint8_t att_num;
    /// Start hdl
    uint16_t start_hdl;
    /// Attribute database
    struct attm_desc_128* att_db;
    /// Service perm
    uint8_t svc_perm;
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
const struct prf_task_cbs* udfs_prf_itf_get(void);


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

void udfs_task_init(struct ke_task_desc *task_desc,struct udfs_env_tag* udfs_env);



#endif /* #if (BLE_UDF_SERVER) */

/// @} UDFS

#endif /* _UDFS_H_ */

