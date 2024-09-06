#ifndef __APPOTABOX_H
#define __APPOTABOX_H
#include "tgt_cfg_bt.h"
#if PLF_BT_OTA == 1
#include "aic_adp_api.h"

enum {
    OTA_INFO_HEADER = (0x01UL << 0),
    OTA_DATA_HEADER = (0x01UL << 1),
};

enum APP_OTA_ACCESS{
    OTA_BY_SPP = 1,
    OTA_BY_VENDOR,
    OTA_BY_BLE,
};
void app_ota_set_access(enum APP_OTA_ACCESS access);
enum APP_OTA_ACCESS app_ota_get_access(void);
void app_ota_init(void);
void app_ota_msg_handle(AIC_EVENT *Event);
uint8_t app_ota_send_data(uint8_t *data, uint16_t len, uint8_t header);
void app_ota_receive_data(uint8_t *rxbuf, uint16_t len);
#if APP_SUPPORT_OTA_BOX
void app_ota_connect_device(BT_ADDR * bdaddr);
void app_ota_clean_addr_list(void);
void app_ota_connect_by_list_id(uint8_t id);
void app_ota_add_addr_list(BT_ADDR *ota_addr);
#endif
#endif
#endif
