#ifndef APP_TWS_H
#define APP_TWS_H
#include <stdint.h>
#include "tgt_cfg_bt.h"

#if APP_SUPPORT_TWS == 1
#include "aic_adp_api.h"

#define TWS_SERVER_PORT         0x01
#define TWS_CLIENT_PORT         0x02

typedef enum {
    TWS_OTA_PARAM     = 71,
    TWS_MIN_APP_PARAM = 72,
    TWS_KEY_PARAM,
    TWS_LINK_CONTROL_PARAM,
    TWS_MSS_PARAM,
    TWS_POWERD_PARAM,
    TWS_SET_VOLUME_PARAM,
    TWS_MAX_APP_PARAM ,
}APP_TWS_USER_PARAM;

typedef enum {
    STATE_IDLE,
    STATE_ADV_EN,
    STATE_SCAN_EN,
}APP_TWS_BLE_STATE;

typedef enum {
    STATE_PD_IDLE,
    STATE_PD_PENDING,
}APP_TWS_POWER_DOWN_STATE;

typedef enum {
    WEAR_OFF,
    WEAR_ON,
}APP_TWS_WEAR_STATE;

#define APP_TWS_LEN_5            5
#define APP_TWS_LEN_3            3
#define APP_TWS_LEN_2            2

void app_connect_tws_test(void);
void app_tws_default_connect(void);
BOOL app_tws_key_handle(uint32_t key);
void app_tws_msg_handle(AIC_EVENT *event);
void app_tws_init(void);
BOOL app_tws_send_data(uint8_t* ptrData, uint16_t length);
void app_tws_set_ble_state(APP_TWS_BLE_STATE state);
APP_TWS_BLE_STATE app_tws_get_ble_state(void);
void app_bt_disconnect_tws(void);
void app_tws_begin_mss(void);
void app_tws_power_down(void);
void app_tws_volume_sync_handle(uint8_t mode,uint8_t volume);
void app_tws_wearing_state_handle(uint32_t state);
#endif
#endif
