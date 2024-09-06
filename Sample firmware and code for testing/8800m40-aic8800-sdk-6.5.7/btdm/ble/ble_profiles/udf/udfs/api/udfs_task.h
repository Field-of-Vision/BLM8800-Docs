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


#ifndef _UDFS_TASK_H_
#define _UDFS_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup UDFS_TASK Task
 * @ingroup UDFS
 * @brief Aud Transmit Server Profile Task.
 *
 * The UDFS_TASK is responsible for handling the messages coming in and out of the
 * @ref UDFS collector block of the BLE Host.
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
enum udfs_msg_id
{
    UDFS_WR_RECEIVED = TASK_FIRST_MSG(TASK_ID_UDFS),

    UDFS_RD_VALUE_UPDATE,

    UDFS_NTF_IND_SERVICE_CHANGED,

    UDFS_SEND_NOTIFICATION,

    UDFS_SEND_INDICATION,

    UDFS_NTF_SENT,

    UDFS_IND_SENT,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

struct udfs_ntf_ind_config
{
    uint8_t conidx;
    uint16_t prf_user_id;
    uint16_t att_idx;
    enum prf_cli_conf ntf_ind_en;
};

struct udfs_rx_data_ind
{
    uint8_t conidx;
    uint16_t prf_user_id;
    uint16_t att_idx;
    /// Rx Data Length
    uint16_t length;
    /// Rx Data
    uint8_t  data[__ARRAY_EMPTY];
};

struct udfs_data_sent_ind
{
    uint8_t conidx;
    uint16_t prf_user_id;
    uint16_t att_idx;
    /// Status of the send indicate
    uint8_t status;
};

struct udfs_send_data_req
{
    /// Connection Index
    uint8_t conidx;
    uint16_t prf_user_id;
    uint16_t att_idx;
    /// Data Length
    uint32_t    length;
    /// Data
    uint8_t     value[__ARRAY_EMPTY];
};

struct udfs_read_data_req
{
    /// Connection Index
    uint8_t conidx;
    uint16_t prf_user_id;
    uint16_t att_idx;
    /// Data Length
    uint32_t    length;
    /// Data
    uint8_t*     value;
};

/// @} UDFS_TASK

#endif /* _UDFS_TASK_H_ */

