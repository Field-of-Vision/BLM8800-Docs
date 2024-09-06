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


#ifndef _SMARTCONFIG_TASK_H_
#define _SMARTCONFIG_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup SMARTCONFIGTASK Task
 * @ingroup SMARTCONFIG
 * @brief Smart Config Profile Task.
 *
 * The SMARTCONFIGTASK is responsible for handling the messages coming in and out of the
 * @ref SMARTCONFIG collector block of the BLE Host.
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
/// Messages for Smart Config Profile
enum smartconfig_msg_id
{
    SMARTCONFIG_WIFI_STATE_SERVICE_CHANGED = TASK_FIRST_MSG(TASK_ID_SMARTCONFIG),

    SMARTCONFIG_AP_INFO_RECEIVED,

    SMARTCONFIG_SEND_WIFI_STATE_NOTIFICATION,

    SMARTCONFIG_SEND_WIFI_STATE_INDICATION,

    SMARTCONFIG_TIME_STATE_SERVICE_CHANGED,

    SMARTCONFIG_TIME_STATE_SENT,

    SMARTCONFIG_TIME_INFO_RECEIVED,

    SMARTCONFIG_SEND_TIME_STATE_NOTIFICATION,

    SMARTCONFIG_SEND_TIME_STATE_INDICATION,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

struct ble_smartconfig_notif_config
{
    bool ntf_en;
};

struct ble_smartconfig_rx_data_ind
{
    /// Rx Data Length
    uint16_t length;
    /// Rx Data
    uint8_t  data[0];
};

struct ble_smartconfig_data_sent_ind
{
    /// Status of the send indicate
    uint8_t status;
};

struct ble_smartconfig_send_data_req
{
    /// Connection Index
    uint8_t conidx;
    /// Data Length
    uint32_t    length;
    /// Data
    uint8_t     value[__ARRAY_EMPTY];
};


/// @} SMARTCONFIGTASK

#endif /* _SMARTCONFIG_TASK_H_ */

