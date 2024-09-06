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

#ifndef _AUDTRANSMITC_H_
#define _AUDTRANSMITC_H_

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

#if (BLE_AUDTRANSMIT_CLIENT)
#include "prf_types.h"
#include "prf.h"
#include "audtransmitc_task.h"
#include "attm.h"
#include "prf_utils.h"


/*
 * DEFINES
 ****************************************************************************************
 */
#define AUDTRANSMITC_MAX_LEN            (251)
///Maximum number of Aud Transmit Client task instances
#define AUDTRANSMITC_IDX_MAX    (BLE_CONNECTION_MAX)

/*
 * DEFINES
 ****************************************************************************************
 */
/// Possible states of the AUDTRANSMITC task
enum audtransmitc_state
{
    /// Disconnected state
    AUDTRANSMITC_FREE,
    /// Idle state
    AUDTRANSMITC_IDLE,
    /// Connected state
    AUDTRANSMITC_BUSY,

    /// Number of defined states.
    AUDTRANSMITC_STATE_MAX,
};

enum audtransmitc_operation
{
    /// No operation
    AUDTRANSMITC_OP_NONE = 0,
    /// Discover peer service
    AUDTRANSMITC_OP_DISCOVER,
    /// Write Notification configuration
    AUDTRANSMITC_OP_WR_AUD_INFO_NTF_CFG,
    AUDTRANSMITC_OP_WR_AUD_DATA_NTF_CFG,

    AUDTRANSMITC_OP_WR_AUD_CTRL,
    AUDTRANSMITC_OP_WR_AUD_DATA,
};


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Environment variable for each Connections
struct audtransmitc_cnx_env
{
    ///AUDTRANSMITS characteristics
    struct atcs_content ats;
    /// on-going operation
    uint8_t operation;
    /// counter used to check service uniqueness
    uint8_t nb_svc;
};

/// Aud Transmit Profile Client environment variable
struct audtransmitc_env_tag
{
    /// profile environment
    prf_env_t prf_env;
    /// Environment variable pointer for each connections
    struct audtransmitc_cnx_env* env[AUDTRANSMITC_IDX_MAX];
    /// State of different task instances
    ke_state_t state[AUDTRANSMITC_IDX_MAX];
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
const struct prf_task_cbs* audtransmitc_prf_itf_get(void);


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
void audtransmitc_task_init(struct ke_task_desc *task_desc);

/**
 ****************************************************************************************
 * @brief Send AUDTRANSMIT ATT DB discovery results to SCPPC host.
 ****************************************************************************************
 */
void audtransmitc_enable_rsp_send(struct audtransmitc_env_tag *audtransmitc_env, uint8_t conidx, uint8_t status);


#endif /* #if (BLE_AUDTRANSMIT_CLIENT) */

/// @} AUDTRANSMIT

#endif /* _AUDTRANSMITC_H_ */

