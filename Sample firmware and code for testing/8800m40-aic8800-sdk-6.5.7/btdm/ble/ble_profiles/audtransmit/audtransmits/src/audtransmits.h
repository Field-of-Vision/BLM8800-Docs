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

#ifndef _AUDTRANSMITS_H_
#define _AUDTRANSMITS_H_

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

#if (BLE_AUDTRANSMIT_SERVER)
#include "prf_types.h"
#include "prf.h"
#include "audtransmits_task.h"
#include "attm.h"
#include "prf_utils.h"


/*
 * DEFINES
 ****************************************************************************************
 */
#define AUDTRANSMITS_MAX_LEN            (251)

/*
 * DEFINES
 ****************************************************************************************
 */
/// Possible states of the AUDTRANSMIT task
enum
{
    /// Idle state
    AUDTRANSMITS_IDLE,
    /// Connected state
    AUDTRANSMITS_BUSY,

    /// Number of defined states.
    AUDTRANSMITS_STATE_MAX,
};

enum audtransmits_operation
{
    /// No operation
    AUDTRANSMITS_OP_NONE = 0,

    /// Send Notification
    AUDTRANSMITC_OP_SD_AUD_INFO_NTF,
    AUDTRANSMITC_OP_SD_AUD_DATA_NTF,
    /// Send Indication
    AUDTRANSMITC_OP_SD_AUD_INFO_IND,
    AUDTRANSMITC_OP_SD_AUD_DATA_IND,
};

///Attributes State Machine
enum
{
    AUDTRANSMITS_IDX_SVC,

    AUDTRANSMITS_IDX_AUD_INFO_CHAR,
    AUDTRANSMITS_IDX_AUD_INFO_VAL,
    AUDTRANSMITS_IDX_AUD_INFO_NTF_CFG,

    AUDTRANSMITS_IDX_AUD_CTRL_CHAR,
    AUDTRANSMITS_IDX_AUD_CTRL_VAL,

    AUDTRANSMITS_IDX_DATA_SEND_CHAR,
    AUDTRANSMITS_IDX_DATA_SEND_VAL,
    AUDTRANSMITS_IDX_DATA_SEND_NTF_CFG,

    AUDTRANSMITS_IDX_DATA_RECV_CHAR,
    AUDTRANSMITS_IDX_DATA_RECV_VAL,

    AUDTRANSMITS_IDX_NB,
};


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Datapath Profile Server environment variable
struct audtransmits_env_tag
{
    /// profile environment
    prf_env_t   prf_env;
    /// Service Start Handle
    uint16_t    shdl;
    /// State of different task instances
    ke_state_t  state;
    /// Notification configuration
    uint8_t     aud_info_ntf_cfg;
    /// Notification configuration
    uint8_t     aud_data_ntf_cfg;
    /// on-going operation
    uint8_t operation;
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
const struct prf_task_cbs* audtransmits_prf_itf_get(void);


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
void audtransmits_task_init(struct ke_task_desc *task_desc);



#endif /* #if (BLE_AUDTRANSMIT_SERVER) */

/// @} AUDTRANSMITS

#endif /* _AUDTRANSMITS_H_ */

