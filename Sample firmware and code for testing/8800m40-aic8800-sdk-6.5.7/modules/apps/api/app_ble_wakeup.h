#ifndef APP_BLE_WAKEUP_H_
#define APP_BLE_WAKEUP_H_
#include "plf.h"
#if PLF_BLE_WAKEUP == 1

#define BLE_WAKEUP_MAGIC_NUM            0x53454C42// MAGIC will check that the data in memory has been correctly written through android or linux USB driver
#define BLE_WAKEUP_INPUT_PARAM_ADDR     0x0015FF00// Input Addr for android or linux usb driver.
#define BLE_AD_FILTER_NUM_MAX           5// Max AD Filetr num
#define MAX_GPIO_TRIGGER_NUM            2// Max user config num of gpio
#define MAX_ROLE_COMBO_IDX_NUM          2// Max ad role type combo num , number of enum GPIO_TRIGGER_BIT

#define AD_ROLE_FLAG          0x0f
#define ROLE_COMBO_IDX_FLAG   0xf0

enum AD_ROLE_TYPE {
    ROLE_ONLY,
    ROLE_COMBO,
};

enum ROLE_COMBO_IDX {
    COMBO_0 = 0,
    COMBO_1 = 1,
};

enum GPIO_TRIGGER_BIT {
    TG_IDX_0 = (1<<0),
    TG_IDX_1 = (1<<1),
};

typedef struct {
    uint32_t ad_data_mask;
    uint8_t gpio_trigger_idx;
    uint8_t ad_role;
    uint8_t ad_len;  // id list, any match cause reboot
    uint8_t ad_type;
    uint8_t ad_data[31];
} wakeup_ad_filter_t;


typedef struct {
    uint32_t magic_num; // "BLES" = 0x53454C42
    uint32_t delay_scan_to; // timeout for start scan in ms
    uint32_t reboot_to; // timeout for reboot in ms
    uint32_t gpio_num[MAX_GPIO_TRIGGER_NUM];
    uint32_t gpio_dft_lvl[MAX_GPIO_TRIGGER_NUM];
    wakeup_ad_filter_t ad_filter[BLE_AD_FILTER_NUM_MAX];
} ble_wakeup_param_t;

extern uint8_t ble_combo_num[MAX_ROLE_COMBO_IDX_NUM];
ble_wakeup_param_t *app_ble_wakeup_get_param(void);
void app_ble_delay_scan_start(void);
void app_ble_wakeup_notify(uint8_t gpio_num_idx);
void app_ble_wakeup_init(void);
#endif
#endif//APP_BLE_WAKEUP_H_
