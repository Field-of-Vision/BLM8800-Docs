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

#ifndef APP_UDFC_H_
#define APP_UDFC_H_

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

#if (BLE_APP_UDFC)

#include <stdint.h>          // Standard Integer Definition
#include "ke_task.h"
#include "udfc.h"
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif



#define INVALID_CONNECTION_INDEX                            0xFF

/*
 * STRUCTURES DEFINITION
 ****************************************************************************************
 */
/// Smartconfig Application Module Environment Structure
struct app_udfc_env_tag
{
    /// Connection handle
    uint8_t conidx[UDFC_IDX_MAX];
};



/*
 * GLOBAL VARIABLES DECLARATIONS
 ****************************************************************************************
 */
/// Table of message handlers
extern const struct app_subtask_handlers app_udfc_handlers;

/*
 * FUNCTIONS DECLARATION
 ****************************************************************************************
 */
void app_udfc_init(void);

void app_udf_add_udfc(void);

void app_udfc_enable_prf(uint8_t conidx);

void app_udfc_discover_svc(uint8_t conidx);

void app_udfc_disconnected(uint8_t conidx);

void app_udfc_wr_req(uint8_t conidx, uint16_t handle, uint8_t* data, uint32_t length);

void app_udfc_wr_nores_req(uint8_t conidx, uint16_t handle, uint8_t* data, uint32_t length);

void app_udfc_rd_req(uint8_t conidx, uint16_t handle);

void app_udfc_ntf_cfg_req(uint8_t conidx, uint16_t handle, bool ntf_en);

void app_udfc_ind_cfg_req(uint8_t conidx, uint16_t handle, bool ind_en);

#ifdef __cplusplus
    }
#endif

#endif //(BLE_APP_UDFC)

/// @} APP

#endif // APP_UDFC_H_
