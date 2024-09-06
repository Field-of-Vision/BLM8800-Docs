#ifndef _WLAN_IF_H_
#define _WLAN_IF_H_

#include "mac.h"

/**
 * @brief Define STA whether connect to WLAN(ap)
 */
enum WLAN_STATUS {
    WLAN_DISCONNECT = 0,
    WLAN_CONNECTED,
    WLAN_SCANNING,
    WLAN_CONNECTING,
};

struct connected_ap_info_t
{
    /// SSID
    uint8_t ssid[32];

    /// BSSID.
    struct mac_addr bssid;

    /// Frequency of the operational channel in Hz
    uint16_t freq;

    uint8_t width;

    uint8_t band;

    // 0:bg, 1:n/ac, 2:ax
    uint8_t format;

    // unit: bps
    uint32_t max_rate;
};

struct sta_auto_reconnect_param
{
    uint8_t  *ssid;
    uint8_t  *pw;
    uint32_t retry_times;
    uint32_t timeouts;
    void     *func;
};

/**
 ****************************************************************************************
 * @brief ************************* Part of WLAN-STA-API ********************************
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief * wlan_start_sta : Start STA to connect to router, until obtain IP address
 *                           or timeout
 *
 * @param[in]  ssid:        router name, type: uint8_t ssid[32], (expected 1..31)
 * @param[in]  pw:          router's password (if open, set NULL), type: uint8_t pw[64]
 *                          (expected 8..63)
 * @param[in]  timeout_ms:  unit(ms) (if no timeout, set -1)
 *
 * @return value:
 *             0:           start ap success
 *            -1:           vif param wrong, or wpa fail
 *            -2:           start contrl task fail
 *            -3:           malloc buffer faid
 *            -4:           can`t find vif_idx
 *            -5:           start net fail
 *            -6:           dhcp fail
 *           -11:           can't find ssid
 *           -12:           password is wrong
 *           -13:           other err
 ****************************************************************************************
 */
int wlan_start_sta(uint8_t *ssid, uint8_t *pw, int timeout_ms);

/**
 ****************************************************************************************
 * @brief * wlan_sta_auto_reconnect : Start STA to connect to router and return
 *                                    immediately. It supports retry connect.
 *
 * @param[in]  ssid:        router name, type: uint8_t ssid[32], (expected 1..31)
 * @param[in]  pw:          router's password (if open, set NULL), type: uint8_t pw[64]
 *                          (expected 8..63)
 * @param[]in  retry_times: if set 0, it only try a time.
 * @param[in]  timeout_ms:  unit(ms) (if no timeout, set -1)
 * @param[in]  func:        callback functions
 *
 * @return value:
 *             0:           start task success
 *            -1:           task is exist already
 *            -2:           buff is null
 *            -3:           start task fail
 ****************************************************************************************
 */
int wlan_sta_auto_reconnect(uint8_t *ssid, uint8_t *pw,
                                    uint32_t retry_times, uint32_t timeouts, void *func);

/**
 ****************************************************************************************
 * @brief * wlan_disconnect_sta : STA disconnect
 *
 * @param[in]  idx:         set 0 default
 * @return value:
 *             0: success
 *             1: fail
 ****************************************************************************************
 */
int wlan_disconnect_sta(uint8_t idx);

/**
 ****************************************************************************************
 * @brief * wlan_dhcp : run dhcp client, if using 'wlan_start_sta', no need to call it
 *
 * @param[in]  net_if:
 * @return value:
 *             0: success
 *            -1: fail
 ****************************************************************************************
 */
int wlan_dhcp(net_if_t *net_if);

/**
 ****************************************************************************************
 * @brief * wlan_get_sta_connect_ssid : It can be used only after connect to router.
 *
 * @param[out]  ssid:        sta connected wlan ssid, type: uint8_t ssid[32]
 * @return value:
 *             0: success
 *            -1: fail, because don`t connect to router
 ****************************************************************************************
 */
int wlan_get_sta_connect_ssid(uint8_t *ssid);

/**
 ****************************************************************************************
 * @brief * wlan_get_connect_status : get STA connect status
 *
 * @param[in]  none
 * @return value:
 *             0: disconnect
 *             1: connected
 ****************************************************************************************
 */
int wlan_get_connect_status(void);

/**
 ****************************************************************************************
 * @brief * All the bellow API related to AP should be called before 'wlan_start_sta'
 *          Pay attention to THIS BREIF! If not, the interface don`t work!!!
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief * wlan_set_dhcp_timeout : set the max time to wait dhcp obtained
 *
 * @param[in]  value_s: second, default 30s
 ****************************************************************************************
 */
void wlan_set_dhcp_timeout(uint8_t value_s);

/**
 ****************************************************************************************
 * @brief * wlan_fixed_dhcp : fix dhcp for STA
 *
 * @param[in]  ip:                ip_addr
 * @param[in]  gw:                gateway
 * @param[in]  mask:              subnet_mask
 * @return value:
 *             0: success
 *            -1: fail, sta already connected route(ap)
 ****************************************************************************************
 */
int wlan_fixed_dhcp(uint32_t ip, uint32_t gw, uint32_t mask);

/**
 ****************************************************************************************
 * @brief * set_sta_connect_chan_num :
 *                          Must set channel num before calling 'wlan_start_sta',
 *                          if kowns the router's channel num.
 *
 * @param[in]  chan_num:    channel number
 ****************************************************************************************
 */
void set_sta_connect_chan_num(uint32_t chan_num);

/**
 ****************************************************************************************
 * @brief * set_sta_connect_bssid :
 *                          Must set bssid before calling 'wlan_start_sta',
 *                          if kowns the router's mac address.
 *
 * @param[in]  addr:    mac addr of router
 ****************************************************************************************
 */
void set_sta_connect_bssid(uint8_t *addr);

/**
 ****************************************************************************************
 * @brief * set_sta_support_wep :
 *                          Must set bssid before calling 'wlan_start_sta'
 *
 * @param[in]  0: not support, 1: support
 ****************************************************************************************
 */
void set_sta_support_wep(uint8_t val);

/**
 ****************************************************************************************
 * @brief * set_user_sta_reconnect_scan_limit :
 *                Must set_user_sta_reconnect_scan_limit before calling 'wlan_start_sta',
 *                          default: 3.
 *
 * @param[in]  times for scanning after passive disconnect.
 ****************************************************************************************
 */
void set_user_sta_reconnect_scan_limit(uint8_t value);

/**
 ****************************************************************************************
 * @brief * set_sta_not_autoconnect :
 *                          Must set channel num after calling 'wlan_start_sta'. This
 *                          interface is limit to set sta only, not for sta+ap.
 *
 * @param[in]  vif_idx:     default 0
 * @return value:
 *         other: fail
 *             0: success
 ****************************************************************************************
 */
int set_sta_not_autoconnect(int vif_idx);

/**
 ****************************************************************************************
 * @brief * wlan_get_sta_connected_ap_info :
 *                          Must set channel num after calling 'wlan_start_sta'.
 *
 * @param[in]  connected_ap_info_t:     struct about connected ap info
 * @return value:
 *            -1: fail
 *             0: success
 ****************************************************************************************
 */
int wlan_get_sta_connected_ap_info(struct connected_ap_info_t **info);

/**
 ****************************************************************************************
 * @brief ************************* Part of WLAN-AP-API *********************************
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief * wlan_start_ap : Create softAP
 *
 * @param[in]  band:        0 -> 2.4G
 *                          1 -> 5G
 *             ssid:        name
 *             pw:          password(if open, set NULL)
 * @return value:
 *            -1: fail
 *             0: success
 ****************************************************************************************
 */
int wlan_start_ap(uint8_t band, uint8_t *ssid, uint8_t *pw);

/**
****************************************************************************************
* @brief * wlan_stop_ap : Stop softAP
*
* @param[]  none
* @return value:
*            -1: fail
*             0: success
****************************************************************************************
*/
int wlan_stop_ap(void);

/**
 ****************************************************************************************
 * @brief * wlan_get_softap_status : get AP start status
 *
 * @param[]  none
 * @return value:
 *             0: stop
 *             1: start
 ****************************************************************************************
 */
int wlan_get_softap_status(void);

/**
 ****************************************************************************************
 * @brief * wlan_ap_switch_channel : softAP switch to specified channel
 *
 * @param[in]  chan_num:      channel number
 * @return value:
 *            -1: fail
 *             0: success
 ****************************************************************************************
 */
int wlan_ap_switch_channel(uint8_t chan_num);

/**
 ****************************************************************************************
 * @brief * wlan_ap_disassociate_sta : softAP disassociate specified STA
 *
 * @param[in]  macaddr:       mac address of specified STA
 * @return value:
 *            -1: fail
 *             0: success
 ****************************************************************************************
 */
int wlan_ap_disassociate_sta(struct mac_addr *macaddr);

/**
 ****************************************************************************************
 * @brief * wlan_ap_get_associated_sta_cnt : After starting softAP, get associated_sta
 *                                           number. Maximum of associated_sta is 10.
 *
 * @param[]  none
 * @return value:
 *         if -1:             fail, softAP don`t start
 *         else :             associated_sta number
 ****************************************************************************************
 */
int32_t wlan_ap_get_associated_sta_cnt(uint8_t fhost_vif_idx);

/**
 ****************************************************************************************
 * @brief * wlan_ap_get_associated_sta_list : After starting softAP, get associated_sta
 *                                            list.
 *
 * @param[]  none
 * @return value:
 *          if 0:             NULL, fail, softAP don`t start
 *          else:             list
 ****************************************************************************************
 */
void *wlan_ap_get_associated_sta_list(uint8_t fhost_vif_idx);

/**
 ****************************************************************************************
 * @brief * get_ap_ip_addr : Get softAP ip address, if softAP is not start, it is default
 *                           value.
 *
 * @param[]  none
 * @return value:             ap_ip_addr
 ****************************************************************************************
 */
uint32_t get_ap_ip_addr(void);

/**
 ****************************************************************************************
 * @brief * get_ap_subnet_mask : Get softAP ip subnet mask, if softAP is not start, it is
 *                               default value.
 *
 * @param[]  none
 * @return value:             ap_subnet_mask
 ****************************************************************************************
 */
uint32_t get_ap_subnet_mask(void);

/**
 ****************************************************************************************
 * @brief * All the bellow API related to AP should be called before 'wlan_start_ap'
 *          Pay attention to THIS BREIF! If not, the interface don`t work!!!
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief * set_ap_ip_addr : Set IP start address for softAP
 *
 * @param[in]  new_ip_addr:      IP address
 *                               If not set, default: 192.168.88.24
 ****************************************************************************************
 */
void set_ap_ip_addr(uint32_t new_ip_addr);

/**
 ****************************************************************************************
 * @brief * set_ap_subnet_mask : Set subnet mask for softAP
 *
 * @param[in]  new_mask:         subnet mask
 *                               If not set, default: 255.255.255.0 -> 0x00FFFFFF
 ****************************************************************************************
 */
void set_ap_subnet_mask(uint32_t new_mask);

/**
 ****************************************************************************************
 * @brief * set_ap_bcn_interval : Set Beacon interval for softAP
 *
 * @param[in]  bcn_interval_ms:  beacon interval(unit:ms)
 *                               Default: 100
 ****************************************************************************************
 */
void set_ap_bcn_interval(uint32_t bcn_interval_ms);

/**
 ****************************************************************************************
 * @brief * set_ap_channel_num : Set channel number for softAP, if not set, auto select
 *
 * @param[in]  num:              channel number
 *                               2.4G(1~14), 5G(depend on 'fhost_chan')
 ****************************************************************************************
 */
void set_ap_channel_num(uint8_t num);

/**
 ****************************************************************************************
 * @brief * get_ap_channel_num : Get channel number for softAP, if not set, the value is 0
 *
 * @return value:                channel number
 *                               2.4G(1~14), 5G(depend on 'fhost_chan')
 ****************************************************************************************
 */
uint8_t get_ap_channel_num(void);

/**
 ****************************************************************************************
 * @brief * set_ap_hidden_ssid : Set hidden ssid for softAP
 *
 * @param[in]  val:               0 -> unhidden, default
 *                                1 -> hidden
 ****************************************************************************************
 */
void set_ap_hidden_ssid(uint8_t val);

/**
 ****************************************************************************************
 * @brief * set_ap_enable_he_rate : Enable HE rate for softAP
 *
 * @param[in]  en:                1 -> enable
 *                                0 -> diable, default
 ****************************************************************************************
 */
void set_ap_enable_he_rate(uint8_t en);

/**
 ****************************************************************************************
 * @brief * set_ap_allow_sta_inactivity_s : Set max inactivity time for connected STA (if
 *                                          long time not receive/transmit, send a NULL
 *                                          frame to detect it. If detected fail,
 *                                          disassociate it).
 *
 * @param[in]  s:                 second, default 60s
 ****************************************************************************************
 */
void set_ap_allow_sta_inactivity_s(uint8_t s);

/**
 ****************************************************************************************
 * @brief * set_ap_enable_ht_40 : Set bandwidth for softAP
 *
 * @param[in]  enable:            0 -> 20M, default
 *                                1 -> 40M
 ****************************************************************************************
 */
void set_ap_enable_ht_40(uint8_t enable);

/**
 ****************************************************************************************
 * @brief * sta_data_pkt_rssi_get : get_associated_sta_rssi
 *
 * @param[in]  mac addr of sta
 *
 ****************************************************************************************
 */
int8_t sta_data_pkt_rssi_get(uint8_t *mac_addr);

/**
 ****************************************************************************************
 * @brief * wlan_start_wps : Start push button WPS
 *
 * @param[]  none
 * @return value:
 *             0: success
 *         other: fail
 ****************************************************************************************
 */
int wlan_start_wps(void);

typedef enum wlan_softap_event      {
    ASSOC_IND_EVENT,
    DISASSOC_IND_EVENT,
} wlan_softap_event_e;
typedef void (*wlan_softap_event_func_t)(wlan_softap_event_e event, uint8_t *device_mac);
void wlan_softap_event_register(wlan_softap_event_func_t func);

/**
 ****************************************************************************************
 * @brief * fhost_get_scan_status_register, get scan start & channel switch status
 *          set this callback api before calling "do_scan"
 *
 * @param[]  uint32_t st, bit31(wifi_scan_status_e), bit0 ~ bit30(channel freq)
 ****************************************************************************************
 */
typedef enum wifi_scan_status    {
    WIFI_SCAN_STARTED,
    WIFI_SCAN_CH_SWITCH,
}wifi_scan_status_e;
typedef void (*fhost_scan_status_get_func_t)(uint32_t st);
void fhost_get_scan_status_register(fhost_scan_status_get_func_t func);

/**
 ****************************************************************************************
 * @brief * wlan_ap_generate_ssid_pw_for_pairing & wlan_sta_auto_pairing are used as pairing
 *
 * @param[]  out: ssid, pw
 *           in : times: paring retry times
 * @return value: 0: success
 ****************************************************************************************
 */
int wlan_ap_generate_ssid_pw_for_pairing(char *ssid, char *pw);
int wlan_sta_auto_pairing(char *ssid, char *pw, int8_t times);

int wlan_start_p2p(void);

/**
 ****************************************************************************************
 * @brief *********************** Part of SDK-Inside-API ********************************
 *        *** Pay attention to THIS BREIF! If it isn`t necessary, please don`t use!!! ***
 ****************************************************************************************
 */
uint8_t *get_selected_channel_numbers(uint8_t band);
uint32_t get_sta_connect_chan_freq(void);


#if (PLF_BT_STACK || PLF_BLE_STACK) && (PLF_WIFI_STACK)
__WEAK void wb_coex_wifi_on_set(int on);
__WEAK void wb_coex_wifi_connected_set(int connected);
__WEAK int wb_coex_bt_connected_get(void);
__WEAK int wb_coex_bt_a2dp_on_get(void);
__WEAK int wb_coex_bt_sco_on_get(void);
#endif
uint8_t fhost_search_itf_idx(uint8_t type);
uint8_t fhost_search_first_valid_itf(void);

extern uint8_t is_fixed_ip;
extern uint32_t fixed_ip, fixed_gw, fixed_mask;
extern uint8_t disconnected_by_user;
#endif /* _WLAN_IF_H_ */
