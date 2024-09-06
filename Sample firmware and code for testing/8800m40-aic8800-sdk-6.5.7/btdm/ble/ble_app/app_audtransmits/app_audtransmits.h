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

#ifndef APP_AUDTRANSMITS_H_
#define APP_AUDTRANSMITS_H_

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

#if (BLE_APP_AUDTRANSMITS)

#include <stdint.h>          // Standard Integer Definition
#include "ke_task.h"

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    NO_ERROR = 0,
    AUD_INFO_ERR,
    AUD_DATA_ERR,
};
    
enum aud_server_state {
    S_STATE_IDLE,
    S_STATE_PLAY,
};

struct audtransmits_state {
    uint16_t codec_type;
    enum aud_server_state state;
};

#define INVALID_CONNECTION_INDEX                            0xFF

/*
 * STRUCTURES DEFINITION
 ****************************************************************************************
 */
/// Smartconfig Application Module Environment Structure
struct app_audtransmits_env_tag
{
    /// Connection handle
    uint8_t conidx;
    uint8_t aud_info_ntf_en;
    uint8_t aud_data_ntf_en;
};

/*
 * GLOBAL VARIABLES DECLARATIONS
 ****************************************************************************************
 */
/// Table of message handlers
extern const struct app_subtask_handlers app_audtransmits_handlers;

typedef void(*app_audtransmits_sent_aud_info_cb)(uint8_t state);
typedef void(*app_audtransmits_sent_aud_data_cb)(uint8_t state);

typedef void(*app_audtransmits_recv_aud_ctrl_cb)(uint8_t *data, uint32_t length);
typedef void(*app_audtransmits_recv_aud_data_cb)(uint8_t *data, uint32_t length);

/*
 * FUNCTIONS DECLARATION
 ****************************************************************************************
 */
void app_audtransmits_init(void);

void app_audtransmits_enable_prf(uint8_t conidx);

void app_audtransmit_add_audtransmits(void);

void app_audtransmits_disconnected(void);

void app_audtransmits_send_aud_info(uint8_t* data, uint32_t length);

void app_audtransmits_send_aud_data(uint8_t* data, uint32_t length);

void app_audtransmits_register_aud_info_sent_cb(app_audtransmits_sent_aud_info_cb callback);

void app_audtransmits_register_aud_data_sent_cb(app_audtransmits_sent_aud_data_cb callback);

void app_audtransmits_register_aud_ctrl_recv_cb(app_audtransmits_recv_aud_ctrl_cb callback);

void app_audtransmits_register_aud_data_recv_cb(app_audtransmits_recv_aud_data_cb callback);

void app_audtransmits_set_status(uint16_t codec_type,uint8_t state);

#ifdef __cplusplus
    }
#endif

#endif //(BLE_APP_AUDTRANSMITS)

/// @} APP

#endif // APP_AUDTRANSMITS_H_
