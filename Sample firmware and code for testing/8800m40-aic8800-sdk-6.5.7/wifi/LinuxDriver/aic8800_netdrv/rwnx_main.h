/**
 ******************************************************************************
 *
 * @file rwnx_main.h
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ******************************************************************************
 */
#ifndef _RWNX_MAIN_H_
#define _RWNX_MAIN_H_

#include "rwnx_defs.h"
#include "rwnx_platform.h"

#define TASK_BASE_INDEX             12
#define TASK_CUSTOM                 (TASK_BASE_INDEX << 10)
#define APP_CMD_NUM_MAX             4
#define APP_CMD_BUF_MAX             128
#define AP_SSID_BUF_MAX             32
#define AP_PSWD_BUF_MAX             64
#define PLATFORM_PREPARE_TIMEOUT    2000
#define FASYNC_APP_TIMEOUT          100

#define PRIVATE_COMMAND_MAX_LEN     8192
#define PRIVATE_COMMAND_DEF_LEN     4096

// custom_msg cmd setting
#define AICWF_CMD_WAITCFM           1
#define AICWF_CMD_NOWAITCFM         0
#define AICWF_CMDCFM_TIMEOUT        2000

// cmd-table from app to netdrv
enum APPLICATION_CMD
{
    APP_CMD_CONNECT         = 1,
    APP_CMD_DISCONNECT      = 2,
    APP_CMD_OPEN_BLE        = 3,
    APP_CMD_CLOSE_BLE       = 4,
    APP_CMD_ENTER_SLEEP     = 5,
    APP_CMD_EXIT_SLEEP      = 6,
    APP_CMD_GET_MAC_ADDR    = 7,
    APP_CMD_GET_WLAN_STATUS = 8,
    APP_CMD_START_AP        = 9,
    APP_CMD_CHANGE_AP_MODE  = 10,
    APP_CMD_STOP_AP         = 11,
    APP_CMD_SCAN_WIFI       = 12,
    APP_CMD_HOST_OTA        = 13,
    APP_CMD_HOST_SET_IP     = 14,
};

// cmd-table from netdrv to mcu
enum CUSTOM_CMD_TAG
{
    CUST_CMD_CONNECT_REQ = TASK_CUSTOM,
    CUST_CMD_CONNECT_CFM,
    CUST_CMD_CONNECT_RESULT_CFM,
    CUST_CMD_CONNECT_IND,
    CUST_CMD_DISCONNECT_REQ,
    CUST_CMD_DISCONNECT_CFM,
    CUST_CMD_DISCONNECT_IND,
    CUST_CMD_OPEN_BLE_REQ,
    CUST_CMD_OPEN_BLE_CFM,
    CUST_CMD_OPEN_BLE_IND,
    CUST_CMD_CLOSE_BLE_REQ,
    CUST_CMD_CLOSE_BLE_CFM,
    CUST_CMD_CLOSE_BLE_IND,
    CUST_CMD_ENTER_SLEEP_REQ,
    CUST_CMD_ENTER_SLEEP_CFM,
    CUST_CMD_EXIT_SLEEP_REQ,
    CUST_CMD_EXIT_SLEEP_CFM,
    CUST_CMD_SET_MAC_ADDR_REQ,
    CUST_CMD_GET_MAC_ADDR_REQ,
    CUST_CMD_GET_MAC_ADDR_CFM,
    CUST_CMD_GET_WLAN_STATUS_REQ,
    CUST_CMD_GET_WLAN_STATUS_CFM,
    CUST_CMD_GET_VNET_SETTING_REQ,
    CUST_CMD_GET_VNET_SETTING_CFM,
    CUST_CMD_START_AP_REQ,
    CUST_CMD_START_AP_CFM,
    CUST_CMD_START_AP_IND,
    CUST_CMD_ASSOC_AP_IND,
    CUST_CMD_DISASSOC_AP_IND,
    CUST_CMD_CHANGE_AP_MODE_REQ,
    CUST_CMD_CHANGE_AP_MODE_CFM,
    CUST_CMD_STOP_AP_REQ,
    CUST_CMD_STOP_AP_CFM,
    CUST_CMD_STOP_AP_IND,
    CUST_CMD_SCAN_WIFI_REQ,
    CUST_CMD_SCAN_WIFI_CFM,
    CUST_CMD_SCAN_WIFI_IND,
    CUST_CMD_WIFI_FAIL_IND,
    CUST_CMD_HOST_OTA_REQ,
    CUST_CMD_HOST_OTA_CFM,
    CUST_CMD_HOST_KEEP_ALIVE_REQ,
    CUST_CMD_HOST_KEEP_ALIVE_CFM,
    CUST_CMD_HOST_SET_WLAN_IP_REQ,
    CUST_CMD_HOST_SET_WLAN_IP_CFM,

    CUST_CMD_MAX
};

// aic work mode status
enum AIC_MODE_STATUS
{
    AIC_MODE_IDLE,          // AIC doesn`t connect AP and start AP
    AIC_MODE_WLAN,          // AIC connect to AP
    AIC_MODE_AP_CONFIG,     // AIC start ap to config network
    AIC_MODE_AP_DIRECT,     // AIC start ap to transfer data between host and AIC
};

// wlan connect status about mcu
enum WLAN_STATUS
{
    WLAN_DISCONNECT,        // AIC-STA hasn`t connected AP
    WLAN_CONNECTED,         // AIC-STA has connected AP
};

// wlan connect failure result
enum WLAN_CONN_FAIL_RESULT
{
    WLAN_CONN_FAIL,         // AIC-STA failed to connect AP
    WLAN_PSWD_WRONG,        // AIC-STA failed to connect AP since passward wrong
};

// ap start status
enum AP_STATUS
{
    AIC_AP_START,           // AIC-AP is START
    AIC_AP_CLOSE,           // AIC-AP is CLOSE
};

// ble status
enum BLE_STATUS
{
    BLE_STATUS_DEFAULT,
    BLE_STATUS_INIT,
    BLE_STATUS_DEINIT,
};

// mcu pkg filter type
enum VNET_FILTER
{
    VNET_FILTER_DIRECT,     // AIC8800x filters protocol and dst_port only.
    VNET_FILTER_SHARED,     // AIC8800x support more combination types.
    VNET_FILTER_TYPE,
};

// host interface keep alive status
enum KEEP_ALIVE_STATUS
{
    KEEP_ALIVE_DISABLE,
    KEEP_ALIVE_ENABLE,
    KEEP_ALIVE_BREAK,
    KEEP_ALIVE_TYPE,
};

// record enum status for noblock task
enum WIFI_PROCESS_STATUS
{
    PROCESS_DEFAULT,
    PROCESS_START_STA,
    PROCESS_STOP_STA,
    PROCESS_START_AP,
    PROCESS_STOP_AP,
    PROCESS_SCANNING,
};

// data from mcu to netdrv
struct custom_msg_common
{
    int8_t status;
};

struct custom_msg_connect_ind
{
    uint8_t ussid[AP_SSID_BUF_MAX];
    int8_t  rssi;
    u32  ip;
    u32  mk;
    u32  gw;
};

struct custom_msg_mac_addr_cfm
{
    uint8_t mac_addr[6];
};

struct custom_msg_wlan_status_cfm
{
    uint8_t status;
    int8_t  rssi;
    uint8_t ussid[AP_SSID_BUF_MAX];
    u32  ip;
    u32  mk;
    u32  gw;
};

struct custom_msg_ap_status_cfm
{
    uint8_t  status;
    uint32_t ip;
    uint32_t gw;
    uint32_t mk;
};

struct custom_msg_ap_assoc_sta_ind
{
    uint8_t sub_sta_addr[6];
};

struct custom_msg_scan_wifi_result_cfm
{
    uint8_t  scan_num;
    int8_t   rssi;
    uint8_t  bssid[6];
    uint8_t  ssid[AP_SSID_BUF_MAX];
    uint32_t akm;
    int      channal;
};

// the setting about aic8800x vnet mode
struct custom_msg_aic8800x_vnet_setting_cfm
{
    uint8_t ble_enable;
    uint8_t lzma_enable;
    uint16_t filter_mode;
    uint32_t upgrade_addr;
    uint32_t keep_alive;
};

// cmd and data from netdrv to mcu
struct custom_msg_hdr
{
    u32_l rsv0;
    u16_l cmd_id;
    u16_l rsv[2];
    u16_l len;
};

struct custom_msg_common_req
{
    struct custom_msg_hdr hdr;
    uint32_t message;
};

struct custom_msg_connect_req
{
    struct custom_msg_hdr hdr;
    u8_l ssid[AP_SSID_BUF_MAX];
    u8_l pw[AP_PSWD_BUF_MAX];
};

struct custom_msg_set_mac_req
{
    struct custom_msg_hdr hdr;
    u8_l  mac_addr[6];
};

struct custom_msg_start_ap_req
{
    struct custom_msg_hdr hdr;
    u8_l band;
    u8_l ssid[AP_SSID_BUF_MAX];
    u8_l pw[AP_PSWD_BUF_MAX];
};

struct custom_msg_ctrl_ota_req
{
    struct custom_msg_hdr hdr;
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

struct custom_msg_keep_alive
{
    uint8_t status;
    bool first_time_check;
    int32_t local_count;
    int32_t alive_count;
    struct timer_list timer;
    struct work_struct work_queue;
};

struct custom_msg_host_set_wlan_ip
{
    struct  custom_msg_hdr hdr;
    uint8_t ip[16];
    uint8_t gw[16];
};

// custom_msg vnet status and information
typedef struct _aicwf_custom_msg_vnet {
    int8_t  ota_status;
    int8_t  wifi_proc_fail;
    int8_t  aic_mode_status;
    uint8_t wlan_status;
    uint8_t wlan_conn_fail_result;
    uint8_t ble_status;
    bool    comp_sign_get_mac_ready;
    bool    comp_sign_get_wlan_ready;
    struct custom_msg_keep_alive keep_alive;
    struct completion platform_get_mac_done;
    struct completion platform_get_wlan_done;
    struct custom_msg_mac_addr_cfm macaddr_cfm;
    struct custom_msg_connect_ind connect_ind;
    struct custom_msg_wlan_status_cfm get_wlan_cfm;
    struct custom_msg_ap_status_cfm ap_status_cfm;
    struct custom_msg_ap_assoc_sta_ind ap_assoc_sta_addr_ind;
    struct custom_msg_scan_wifi_result_cfm *scan_wifi_cfm_ptr;
    struct custom_msg_scan_wifi_result_cfm scan_wifi_cfm[32];
    struct custom_msg_aic8800x_vnet_setting_cfm vnet_setting_cfm;
} aicwf_custom_msg_vnet;

// custom_msg app cmd confirm information
typedef struct _aicwf_custom_msg_cmd_cfm
{
    int waitcfm;
    u16_l cfm_id;
} aicwf_custom_msg_cmd_cfm;

typedef struct _aicwf_cmd_mgr
{
    u16 cfm_id;
    struct completion complete;
} aicwf_cmd_mgr;

// custom_msg app cmd request information
typedef struct _aicwf_custom_msg_app_cmd {
    struct custom_msg_connect_req connect_req;
    struct custom_msg_hdr common_req;
    struct custom_msg_start_ap_req ap_req;
    struct custom_msg_host_set_wlan_ip set_ip;
    aicwf_custom_msg_cmd_cfm cmd_cfm;
    char   file_path[APP_CMD_BUF_MAX];
} aicwf_custom_msg_app_cmd;

typedef struct _android_wifi_priv_cmd {
    char *buf;
    int used_len;
    int total_len;
} android_wifi_priv_cmd;

#ifdef CONFIG_COMPAT
typedef struct _compat_android_wifi_priv_cmd {
    compat_caddr_t buf;
    int used_len;
    int total_len;
} compat_android_wifi_priv_cmd;
#endif /* CONFIG_COMPAT */

#if !defined(CONFIG_VNAT_MODE)
int nlaic_rx_rawdata(u8 *data, int len);
int rwnx_nlaic_init(struct rwnx_plat *rwnx_plat, void **platform_data);
void rwnx_nlaic_deinit(void);
#endif

#endif /* _RWNX_MAIN_H_ */
