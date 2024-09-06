/**
 ****************************************************************************************
 *
 * @file app_Audtransmits.h
 *
 * @brief Aud transmit Server Application entry point
 *
 * Copyright (C) AIC
 *
 *
 ****************************************************************************************
 */

#ifndef APP_UDFS_H_
#define APP_UDFS_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 *
 * @brief Aud transmit Server Application entry point.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW configuration

#if (BLE_APP_UDFS)

#include <stdint.h>          // Standard Integer Definition
#include "ke_task.h"
#include "udfs.h"

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif


#define INVALID_CONNECTION_INDEX                            0xFF
#define APP_UDFS_MAX_SERVICE                                20

/*
 * STRUCTURES DEFINITION
 ****************************************************************************************
 */


/*
 * GLOBAL VARIABLES DECLARATIONS
 ****************************************************************************************
 */

/*
 * FUNCTIONS DECLARATION
 ****************************************************************************************
 */
void app_udfs_db_cfg_init(void);

void app_udfs_init(void);

void app_udfs_enable_prf(uint8_t conidx);

int app_udf_add_udfs(struct udfs_db_cfg * database_cfg);

void app_udfs_disconnected(uint8_t conidx);

void app_udfs_update_rd_value(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length);

void app_udfs_send_notification(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length);

void app_udfs_send_indication(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length);

#ifdef __cplusplus
    }
#endif

#endif //(BLE_APP_UDFS)

/// @} APP

#endif // APP_UDFS_H_
