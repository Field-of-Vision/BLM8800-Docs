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

#ifndef APP_AUDTRANSMITC_H_
#define APP_AUDTRANSMITC_H_

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

#if (BLE_APP_AUDTRANSMITC)

#include <stdint.h>          // Standard Integer Definition
#include "ke_task.h"

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

enum aud_client_state {
    C_STATE_IDLE,
    C_STATE_PLAY,
};

struct audtransmitc_state {
    uint16_t codec_type;
    enum aud_client_state state;
};

#define INVALID_CONNECTION_INDEX                            0xFF

/*
 * STRUCTURES DEFINITION
 ****************************************************************************************
 */
/// Smartconfig Application Module Environment Structure
struct app_audtransmitc_env_tag
{
    /// Connection handle
    uint8_t conidx;
    struct audtransmitc_state client_aud_status;
};

/*
 * GLOBAL VARIABLES DECLARATIONS
 ****************************************************************************************
 */
/// Table of message handlers
extern const struct app_subtask_handlers app_audtransmitc_handlers;

typedef void(*app_audtransmitc_recv_aud_info_cb)(uint8_t *data, uint32_t length);
typedef void(*app_audtransmitc_recv_aud_data_cb)(uint8_t *data, uint32_t length);

/*
 * FUNCTIONS DECLARATION
 ****************************************************************************************
 */
void app_audtransmitc_init(void);

void app_audtransmitc_enable_prf(uint8_t conidx);

void app_audtransmit_add_audtransmitc(void);

void app_audtransmitc_disconnected(void);

void app_audtransmitc_aud_ctrl_wr_req(uint8_t* data, uint32_t length);

void app_audtransmitc_aud_data_wr_req(uint8_t* data, uint32_t length);

void app_audtransmitc_aud_info_ntf_cfg_req(bool ntf_en);

void app_audtransmitc_aud_data_ntf_cfg_req(bool ntf_en);

void app_audtransmitc_register_aud_info_cb(app_audtransmitc_recv_aud_info_cb callback);

void app_audtransmitc_register_aud_data_cb(app_audtransmitc_recv_aud_data_cb callback);

void app_audtransmitc_set_status(uint16_t codec_type,uint8_t state);

#ifdef __cplusplus
    }
#endif

#endif //(BLE_APP_AUDTRANSMITC)

/// @} APP

#endif // APP_AUDTRANSMITC_H_
