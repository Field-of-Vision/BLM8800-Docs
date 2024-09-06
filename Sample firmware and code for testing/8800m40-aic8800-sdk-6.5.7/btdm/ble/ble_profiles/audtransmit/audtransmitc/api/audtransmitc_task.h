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


#ifndef _AUDTRANSMITC_TASK_H_
#define _AUDTRANSMITC_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup AUDTRANSMITCTASK Task
 * @ingroup AUDTRANSMITC
 * @brief Aud Transmit client Profile Task.
 *
 * The AUDTRANSMITCTASK is responsible for handling the messages coming in and out of the
 * @ref audtransmitc collector block of the BLE Host.
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
/// Messages for Smart Config Profile
enum audtransmitc_msg_id
{
    AUDTRANSMITC_ENABLE_REQ = TASK_FIRST_MSG(TASK_ID_AUDTRANSMITC),

    AUDTRANSMITC_ENABLE_RSP,
    AUDTRANSMITC_REG_NTF_PROCESS_DONE,

    AUDTRANSMITC_AUD_CTRL_WR_REQ,
    AUDTRANSMITC_AUD_CTRL_WR_RSP,

    AUDTRANSMITC_AUD_DATA_WR_REQ,
    AUDTRANSMITC_AUD_DATA_WR_RSP,

    AUDTRANSMITC_AUD_INFO_NTF_CFG_REQ,
    AUDTRANSMITC_AUD_INFO_NTF_CFG_RSP,

    AUDTRANSMITC_AUD_DATA_NTF_CFG_REQ,
    AUDTRANSMITC_AUD_DATA_NTF_CFG_RSP,

    AUDTRANSMITC_AUD_INFO_IND,
    AUDTRANSMITC_AUD_DATA_IND,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Characteristics
enum audtransmitc_char
{
    AUDTRANSMITC_CHAR_AUD_INFO,
    AUDTRANSMITC_CHAR_AUD_CTRL,
    AUDTRANSMITC_CHAR_DATA_SEND,
    AUDTRANSMITC_CHAR_DATA_RECV,
    AUDTRANSMITC_CHAR_MAX,
};


/// Characteristic descriptors
enum audtransmitc_desc
{
    AUDTRANSMITC_DESC_AUD_INFO_CFG,
    AUDTRANSMITC_DESC_DATA_SEND_CFG,
    AUDTRANSMITC_DESC_MAX,
};

/*
 * APIs Structure
 ****************************************************************************************
 */

///Structure containing the characteristics handles, value handles and descriptors
struct atcs_content
{
    /// service info
    struct prf_svc svc;

    /// characteristic info:
    struct prf_char_inf chars[AUDTRANSMITC_CHAR_MAX];

    /// Descriptor handles:
    struct prf_char_desc_inf descs[AUDTRANSMITC_DESC_MAX];
};

/// Parameters of the @ref SCPPC_ENABLE_REQ message
struct audtransmitc_enable_req
{
    ///Connection type
    uint8_t con_type;
    ///Existing handle values ats
    struct atcs_content ats;
};

/// Parameters of the @ref SCPPC_ENABLE_RSP message
struct audtransmitc_enable_rsp
{
    ///status
    uint8_t status;
    ///Existing handle values ats
    struct atcs_content ats;
};

struct audtransmitc_notif_config
{
    bool ntf_en;
};

struct audtransmitc_rx_data_ind
{
    /// Rx Data Length
    uint16_t length;
    /// Rx Data
    uint8_t  data[0];
};

struct audtransmitc_data_sent_ind
{
    /// Status of the send indicate
    uint8_t status;
};

struct audtransmitc_send_data_req
{
    /// Data Length
    uint32_t    length;
    /// Data
    uint8_t     value[__ARRAY_EMPTY];
};


/// @} AUDTRANSMITCTASK

#endif /* _AUDTRANSMITC_TASK_H_ */

