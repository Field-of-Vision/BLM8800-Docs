/**
 ****************************************************************************************
 *
 * @file smartconfig_task.h
 *
 * @brief Header file - SmartConfig Profile Task.
 *
 * Copyright (C) AIC
 *
 *
 ****************************************************************************************
 */


#ifndef _UDFC_TASK_H_
#define _UDFC_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup UDFCTASK Task
 * @ingroup UDFC
 * @brief User defined client Profile Task.
 *
 * The UDFCTASK is responsible for handling the messages coming in and out of the
 * @ref udfc collector block of the BLE Host.
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "rwip_task.h" // Task definitions
#include "prf_types.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define MAX_DISCOVERD_SCV_NUM   10

/// Messages for User Defined Profile
enum udfc_msg_id
{
    UDFC_ENABLE_REQ = TASK_FIRST_MSG(TASK_ID_UDFC),
    UDFC_DISCOVER_REQ,
    UDFC_ENABLE_RSP,
    UDFC_REG_NTF_PROCESS_DONE,

    UDFC_WR_REQ,
    UDFC_WR_RSP,

    UDFC_WR_NORES_REQ,
    UDFC_WR_NORES_RSP,

    UDFC_RD_REQ,
    UDFC_RD_RSP,

    UDFC_NTF_CFG_REQ,
    UDFC_NTF_CFG_RSP,

    UDFC_INDICATION_CFG_REQ,
    UDFC_INDICATION_CFG_RSP,

    UDFC_NTF_IND,
    UDFC_INDICATION_IND,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
 * APIs Structure
 ****************************************************************************************
 */

///Structure containing the characteristics handles, value handles and descriptors
struct discovered_svc_content
{
    uint8_t nb_svc;
    /// service info
    struct prf_disc_sdp_svc_info *scv_info[MAX_DISCOVERD_SCV_NUM];
};


/// Parameters of the @ref SCPPC_ENABLE_REQ message
struct udfc_enable_req
{
    ///Connection type
    uint8_t con_type;
};

/// Parameters of the @ref SCPPC_ENABLE_RSP message
struct udfc_enable_rsp
{
    uint8_t conidx;
    ///status
    uint8_t status;
    ///Existing handle values ats
    struct discovered_svc_content *ats;
};

struct udfc_notif_config
{
    uint8_t conidx;
    uint16_t handle;
    bool ntf_en;
};

struct udfc_indication_config
{
    uint8_t conidx;
    uint16_t handle;
    bool ind_en;
};

struct udfc_rx_data_ind
{
    uint8_t conidx;
    uint16_t handle;
    /// Rx Data Length
    uint16_t length;
    /// Rx Data
    uint8_t  data[0];
};

struct udfc_data_sent_ind
{
    uint8_t conidx;
    uint16_t handle;
    /// Status of the send indicate
    uint8_t status;
};

struct udfc_send_data_req
{
    uint8_t conidx;
    uint16_t handle;
    /// Data Length
    uint32_t    length;
    /// Data
    uint8_t     value[__ARRAY_EMPTY];
};


/// @} UDFCTASK

#endif /* _UDFC_TASK_H_ */

