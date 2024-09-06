/**
 ****************************************************************************************
 *
 * @file fhostif_cmd.h
 *
 * @brief Declares the host command parsing and handling functions
 *
 * Copyright (C) AICSemi 2018-2021
 *
 ****************************************************************************************
 */

#ifndef _FHOSTIF_CMD_H_
#define _FHOSTIF_CMD_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "cmsis_compiler.h"
#include "host_cmd.h"


/*
 * TYPE DEFINITIONS AND MACROS
 ****************************************************************************************
 */
#define SSID_LEN    32
#define PASS_LEN    64

/// Messages related to Custom msg Task
enum CUSTOM_MSG_TAG
{
    /// Memory read request
    CUSTOM_MSG_CONNECT_REQ = LMAC_FIRST_MSG(TASK_CUSTOM),
    CUSTOM_MSG_CONNECT_CFM,
    CUSTOM_MSG_CONNECT_RESULT_CFM,
    CUSTOM_MSG_CONNECT_IND,
    CUSTOM_MSG_DISCONNECT_REQ,
    CUSTOM_MSG_DISCONNECT_CFM,
    CUSTOM_MSG_DISCONNECT_IND,
    CUSTOM_MSG_OPEN_BLE_REQ,
    CUSTOM_MSG_OPEN_BLE_CFM,
    CUSTOM_MSG_OPEN_BLE_IND,
    CUSTOM_MSG_CLOSE_BLE_REQ,
    CUSTOM_MSG_CLOSE_BLE_CFM,
    CUSTOM_MSG_CLOSE_BLE_IND,
    CUSTOM_MSG_ENTER_SLEEP_REQ,
    CUSTOM_MSG_ENTER_SLEEP_CFM,
    CUSTOM_MSG_EXIT_SLEEP_REQ,
    CUSTOM_MSG_EXIT_SLEEP_CFM,
    CUSTOM_MSG_SET_MAC_ADDR_REQ,
    CUSTOM_MSG_GET_MAC_ADDR_REQ,
    CUSTOM_MSG_GET_MAC_ADDR_CFM,
    CUSTOM_MSG_GET_WLAN_STATUS_REQ,
    CUSTOM_MSG_GET_WLAN_STATUS_CFM,
    CUSTOM_MSG_GET_VNET_SETTING_REQ,
    CUSTOM_MSG_GET_VNET_SETTING_CFM,
    CUSTOM_MSG_START_AP_REQ,
    CUSTOM_MSG_START_AP_CFM,
    CUSTOM_MSG_START_AP_IND,
    CUSTOM_MSG_ASSOC_AP_IND,
    CUSTOM_MSG_DISASSOC_AP_IND,
    CUSTOM_MSG_CHANGE_AP_MODE_REQ,
    CUSTOM_MSG_CHANGE_AP_MODE_CFM,
    CUSTOM_MSG_STOP_AP_REQ,
    CUSTOM_MSG_STOP_AP_CFM,
    CUSTOM_MSG_STOP_AP_IND,
    CUSTOM_MSG_SCAN_WIFI_REQ,
    CUSTOM_MSG_SCAN_WIFI_CFM,
    CUSTOM_MSG_SCAN_WIFI_IND,
    CUSTOM_MSG_WIFI_FAIL_IND,
    CUSTOM_MSG_HOST_OTA_REQ,
    CUSTOM_MSG_HOST_OTA_CFM,
    CUSTOM_MSG_HOST_KEEP_ALIVE_REQ,
    CUSTOM_MSG_HOST_KEEP_ALIVE_CFM,
    CUSTOM_MSG_HOST_SET_WLAN_IP_REQ,
    CUSTOM_MSG_HOST_SET_WLAN_IP_CFM,

    CUSTOM_MSG_MAX = LMAC_FIRST_MSG(TASK_CUSTOM) + 50,
};

/// wlan connect failure result
enum WLAN_CONN_FAIL_RESULT
{
    WLAN_CONN_FAIL,
    WLAN_PSWD_WRONG,
};

enum AP_STATUS
{
    AIC_AP_START,       // AIC AP is START
    AIC_AP_CLOSE,       // AIC AP is CLOSE
};

/// ap mode status
enum AP_MODE_STATUS
{
    AIC_AP_MODE_CONFIG = 2,    // start ap to config network
    AIC_AP_MODE_DIRECT,        // start ap to transfer data between linux-host and AIC-MCU
};

/// ble status
enum BLE_STATUS
{
    BLE_STATUS_DEFAULT,
    BLE_STATUS_INIT,
    BLE_STATUS_DEINIT,
};

/// OTA_STEP and error code
enum OTA_STEP
{
    OTA_STEP_FLASH_ERASE,
    OTA_STEP_FR_PKG_WRITE,
    OTA_STEP_LT_PKG_WRITE,
    OTA_STEP_HEADER_WRITE,
    OTA_STEP_LZMA_CHECK,
};

enum OTA_STEP_STATUS
{
    OTA_STEP_FLASH_ERASE_OK,
    OTA_STEP_FLASH_ERASE_ERR,
    OTA_STEP_FR_PKG_WRITE_OK,
    OTA_STEP_FR_PKG_WRITE_ERR,
    OTA_STEP_LT_PKG_WRITE_OK,
    OTA_STEP_LT_PKG_WRITE_ERR,
    OTA_STEP_BIN_FILE_CRC_ERR,
    OTA_STEP_BIN_VERSION_ERR,
    OTA_STEP_HEADER_WRITE_OK,
    OTA_STEP_HEADER_WRITE_ERR,
    OTA_STEP_LZMA_CRC_CHECK_OK,
    OTA_STEP_LZMA_CRC_CHECK_ERR,
};

/// msg-id for wifi noblock task
typedef enum WIFI_PROCESS_TYPE
{
    WIFI_DEFAULT,
    WIFI_STA_CONNECT,
    WIFI_STA_DISCONNECT,
    WIFI_AP_START,
    WIFI_AP_STOP,
    WIFI_SCANNING,
} wifi_process_t;

struct wifi_noblock_msg
{
    uint32_t id;
    uint8_t *ssid;
    uint8_t *pw;
    union {
        uint32_t band;
        uint32_t timeouts;
    };
};

/// Structure about REQ
struct custom_msg_connect_req
{
    uint8_t ssid[SSID_LEN];
    uint8_t pw[PASS_LEN];
};

struct custom_msg_start_ap_req
{
    uint8_t band;
    uint8_t ssid[SSID_LEN];
    uint8_t pw[PASS_LEN];
};

struct custom_msg_host_ota_req
{
    uint32_t ota_step;
    union {
        struct file_info
        {
            uint32_t file_size;
            uint32_t file_crc;
        } ota_file_info;
        struct pkg_info
        {
            uint32_t flash_addr;
            uint32_t flash_size;
            uint8_t  pkg_buf[1024];
        } ota_pkg_info;
    } ota_msg;
};

/// Structure about CFM and IND
struct custom_msg_common
{
    int8_t status;
};

struct custom_msg_connect_ind
{
    uint8_t  ussid[SSID_LEN];
    int8_t   rssi;
    uint32_t ip;
    uint32_t mk;
    uint32_t gw;
};

struct custom_msg_mac_addr_cfm
{
    uint8_t chip_mac_addr[6];
};

struct custom_msg_wlan_status_cfm
{
    uint8_t  status;
    int8_t   rssi;
    uint8_t  ussid[SSID_LEN];
    uint32_t ip;
    uint32_t mk;
    uint32_t gw;
};

struct custom_msg_ap_status_cfm
{
    uint8_t  status;
    uint32_t ip;
    uint32_t gw;
    uint32_t mask;
};

struct custom_msg_ap_assoc_sta_ind
{
    uint8_t sta_addr[6];
};

/**
 * Brief: common wifi encryption brief description
 * -----------------------------------------
 * |----- akm -----|------- methods -------|
 * |--Dec--|--Hex--|-----------------------|
 * |   1   |   1   |     no encryption     |
 * |   8   |   8   |       WPA2-PSK        |
 * |   8   |   8   |      WPA/WPA2-PSK     |
 * |  512  |  200  |       WPA3-SAE        |
 * |  520  |  208  |    WPA2-PSK/WPA3-SAE  |
 * | 524288|  8000 |        WAPI-PSK       |
 * |   4   |   4
|  WPA/WPA2-Enterprise |
 * |   64  |   40  |     WPA2-Enterprise   |
 * -----------------------------------------
 **/
struct custom_msg_scan_wifi_result_cfm
{
    uint8_t  scan_num;
    int8_t   rssi;
    uint8_t  bssid[6];
    uint8_t  ssid[SSID_LEN];
    uint32_t akm;
    int      channal;
};

struct custom_msg_host_set_wlan_ip
{
    uint8_t ip[16];
    uint8_t gw[16];
};

/**
 * Brief: the setting about aic8800x vnet mode. Aic8800x will
 *        offer its status to host after host insmod driver.
 **/
struct custom_msg_aic8800x_vnet_setting_cfm
{
    uint8_t ble_enable;
    uint8_t lzma_enable;
    uint16_t filter_mode;
    uint32_t upgrade_addr;
    uint32_t keep_alive;
};

/*
 * VARIABLE
 ****************************************************************************************
 */
#if PLF_BLE_ONLY
extern uint8_t ble_status;
#endif

wifi_process_t wifi_process;
const struct ke_state_handler custom_msg_handler;

/*
 * FUNCTIONS
 ****************************************************************************************
 */
int custom_msg_connect_status_ind_handler(uint16_t const host_type, void *param);
int custom_msg_disconnect_status_ind_handler(uint16_t const host_type);
void custom_msg_ble_status_ind_handler(uint16_t const host_type, uint32_t st);
extern void set_mac_address(uint8_t *addr);
extern uint8_t* get_mac_address(void);

#endif /* _FHOSTIF_CMD_H_ */

