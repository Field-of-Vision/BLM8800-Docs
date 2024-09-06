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


#ifndef _AUDTRANSMITS_TASK_H_
#define _AUDTRANSMITS_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup AUDTRANSMITS_TASK Task
 * @ingroup AUDTRANSMITS
 * @brief Aud Transmit Server Profile Task.
 *
 * The AUDTRANSMITS_TASK is responsible for handling the messages coming in and out of the
 * @ref AUDTRANSMITS collector block of the BLE Host.
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

/*
 * DEFINES
 ****************************************************************************************
 */
/// Messages for Aud Transmit Server Profile
enum audtransmits_msg_id
{
    AUDTRANSMITS_AUD_INFO_SERVICE_CHANGED = TASK_FIRST_MSG(TASK_ID_AUDTRANSMITS),

    AUDTRANSMITS_DATA_SEND_SERVICE_CHANGED,

    AUDTRANSMITS_AUD_CTRL_RECEIVED,

    AUDTRANSMITS_AUD_DATA_RECEIVED,

    AUDTRANSMITS_SEND_AUD_INFO_NOTIFICATION,

    AUDTRANSMITS_SEND_AUD_INFO_INDICATION,

    AUDTRANSMITS_SEND_AUD_DATA_NOTIFICATION,

    AUDTRANSMITS_SEND_AUD_DATA_INDICATION,

    AUDTRANSMITS_AUD_INFO_SENT,

    AUDTRANSMITS_AUD_DATA_SENT,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

struct audtransmits_notif_config
{
    bool ntf_en;
};

struct audtransmits_rx_data_ind
{
    /// Rx Data Length
    uint16_t length;
    /// Rx Data
    uint8_t  data[0];
};

struct audtransmits_data_sent_ind
{
    /// Status of the send indicate
    uint8_t status;
};

struct audtransmits_send_data_req
{
    /// Connection Index
    uint8_t conidx;
    /// Data Length
    uint32_t    length;
    /// Data
    uint8_t     value[__ARRAY_EMPTY];
};


/// @} AUDTRANSMITS_TASK

#endif /* _AUDTRANSMITS_TASK_H_ */

