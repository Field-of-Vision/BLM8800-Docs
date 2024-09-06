#ifndef __APP_BT_H__
#define __APP_BT_H__
#include "rtos.h"
#include "aic_adp_api.h"
#include "app_media.h"
#include "app_bt_queue.h"
#include "co_message.h"
#include "app_media_mgr.h"
#include "co_main.h"
#if PLF_LED_MODULE
#include "led.h"
#endif
#if PLF_KEY_MODULE
#include "key.h"
#endif
#if PLF_LS_MODULE
#include "light_sensor.h"
#endif
#if APP_SUPPORT_HFG && PLF_USB_BT
#include "usb_bt.h"
#include "usb_bt_dongle.h"
#endif
#if PLF_BT_OTA
#include "app_ota_box.h"
#endif

#define APP_RECONNECT_INCREASE_TIME 3000    //increase reconnect times when reconnect timer run sometimes
#define APP_RECONNECT_TIME 3000             //base reconnect timer times
#define APP_RECONNECT_NUM  3                //max reconnect num for reconnect timer ,30 is total 3 min. (APP_RECONNECT_INCREASE_TIME*(N-1)+APP_RECONNECT_INCREASE_TIME*(N+1))

typedef enum {
    RECONNECT_IDLE,
    RECONNECT_POWERON,
    RECONNECT_AFTER_DISC,
}app_reconnect_mode;


typedef enum {
    CONNECT_IDLE,
    CONNECTED,
    DISCONNECTED,
}app_connect_status;

typedef enum{
    BT_CLOSED,
    BT_CLOSE_PENDING,
    BT_ACTIVE_PENDING,
    BT_ACTIVED,
    BT_SCAN,
    BT_INQUIRY_PENDNG,
    BT_CONNECTED,
}app_bt_state_t;

typedef enum {
    KEY_HFP = 0,
    KEY_HSP,
    KEY_AVRCP,
    KEY_HID,
    KEY_SPP,
    KEY_TWS,
    KEY_MAX_MODULE
}aic_bt_key_module;

typedef struct{
    app_reconnect_mode reconnect_mode;
    uint8_t connect_retry_cnt;
#if PLF_AON_SUPPORT
    co_timer * connect_timer_handle;
    co_timer_callback connect_timer_cb;
    void * cb_param;
#else
    TimerHandle_t connect_timer_handle;
    TimerCallbackFunction_t connect_timer_cb;
#endif
}app_reconnect_struct;

typedef struct{
    app_connect_status hfp_connect;
    app_connect_status hsp_connect;
    app_connect_status a2dp_connect;
    bool all_connected;
}app_profile_connect;

typedef struct {
    app_reconnect_struct reconnect;
    app_profile_connect profile;
    BT_ADDR remotedev_addr;
}app_connect_manager;

typedef BOOL (*app_bt_key_handle_cb)(uint32_t key);

typedef struct {
    aic_bt_key_module module;
    app_bt_key_handle_cb callback;
}app_bt_key_handler;


extern app_connect_manager *app_con_ptr[LINK_MAX];
extern char bt_local_name[32];
app_connect_manager *app_bt_get_unused_con_ptr(void);

app_connect_manager *app_bt_get_con_ptr_by_addr(BT_ADDR * bdaddr);

void app_bt_set_scan_mode(AppBtScanMode mode);

/*************************************************************/
/*   @func :  app_bt_open_aic_vender_adv                     */
/*   @brief:  only used for two aic device connection process*/
/*            used by AIC Vendor-Defined BLE ADV and SCAN.   */
/*************************************************************/
void app_bt_open_aic_vender_adv(void);

void app_bt_start_pd_timer(void);

void app_bt_init(void);

void app_bt_connect_init(void);

void app_bt_connect(void);

#if PLF_AON_SUPPORT
void app_bt_connect_timer(void *cb_param);

void app_bt_start_reconnect(co_timer **timer, void *cb_param, uint32_t t);
#else
void app_bt_connect_timer( TimerHandle_t xTimer );

void app_bt_start_reconnect( TimerHandle_t xTimer ,uint32_t t);
#endif

void app_bt_disconnect_all(void);

void app_bt_report_connect_internal_audio(app_connect_manager * app_bt_con);

void app_bt_wearing_state_hanlde(uint32_t state);

BOOL app_bt_key_handle(uint32_t key);
#if APP_SUPPORT_HID == 1
BOOL app_hid_key_handle(uint32_t key);

void app_hid_msg_handle(AIC_EVENT *event);
#endif

void app_console_command_add(void);

void app_bt_volume_absolute_mute(void);

void app_bt_local_volume_handle(uint8_t mode, uint8_t volume);

void app_bt_set_pass_key(char * passkey, uint8_t len);

#endif /* AICBT_H */
