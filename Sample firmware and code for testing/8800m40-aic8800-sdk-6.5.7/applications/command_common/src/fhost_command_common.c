/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdlib.h>
#include <strings.h>
#include "rtos.h"
#include "mac.h"
#include "fhost.h"
#include "fhost_wpa.h"
#include "fhost_cntrl.h"
#include "fhost_config.h"
#include "fhost_iperf.h"
#include "fhost_ping.h"
#include "dbg_assert.h"
#include "rwnx_utils.h"
#include "rwnx_msg_tx.h"
#include "net_al.h"
#include "console.h"
#include "wlan_if.h"
#include "command.h"
#include "fhost_tx.h"
#include "fhost_smartconf.h"
#include "fhost_command_common.h"
#include "flash_api_wifi.h"
#include "sleep_api.h"

uint8_t fhost_vif_idx = 0;

#ifdef CFG_SOFTAP
int ps_sta_connected = 0;
#endif
uint8_t is_ap = 0;
#define PW_LEN  64

static void fhost_nw_upper(char *str, char *stop)
{
    char *ptr = str;
    char c;

    if (stop)
    {
        c = *stop;
        *stop = 0;
    }
    while (*ptr)
    {
        if ((*ptr >= 'a') && (*ptr <= 'z'))
            *ptr -= 'a' - 'A';
        ptr++;
    }

    if (stop)
        *stop = c;
}

int do_sleep_level(int argc, char * const argv[])
{
    unsigned int level;

    if(*argv[1] == '?') {
        dbg("%d\r\n", sleep_level_get());
        return ERR_NONE;
    }

    level = console_cmd_strtoul(argv[1], NULL, 10);
    if (level >= PM_LEVEL_LEVEL_NUM) {
        return ERR_WRONG_ARGS;
    }

    sleep_level_set(level);

    return ERR_NONE;
}

int do_user_wakeup_source(int argc, char * const argv[])
{
    int src, en, arg = 0;

    src = console_cmd_strtoul(argv[1], NULL, 10);
    if (src >= WAKESRC_NUM_MAX) {
        return ERR_WRONG_ARGS;
    }
    en  = console_cmd_strtoul(argv[2], NULL, 10);
    if (src == WAKESRC_TIMER) {
        if (argc < 4) {
            return ERR_WRONG_ARGS;
        }
        arg = console_cmd_strtoul(argv[3], NULL, 10);
    }

    user_sleep_wakesrc_set(src, en, arg);

    return ERR_NONE;
}

int do_user_sleep(int argc, char * const argv[])
{
    int slp_en = (int)console_cmd_strtoul(argv[1], NULL, 10);
    user_sleep_allow((slp_en) ? 1 : 0);
    return ERR_NONE;
}

int do_restore(int argc, char * const argv[]){
    flash_wifi_info_remove_all();

    return ERR_NONE;
}

int do_show_heap(int argc, char * const argv[])
{
    int total, used, free, max_used;

    rtos_heap_info(&total, &free, &max_used);
    used = total - free;
    max_used = total - max_used;
    dbg("RTOS HEAP: free=%d used=%d max_used=%d/%d\n",
                free, used, max_used, total);

    return ERR_NONE;
}

#if (configUSE_TRACE_FACILITY == 1)
int do_show_task(int argc, char * const argv[])
{
    rtos_task_info();
    return 0;
}
#endif

int do_set_power(int argc, char * const argv[])
{
    unsigned int fvif_idx;
    unsigned int tx_pwr_lvl;
    int in_pwr_lvl;

    if (argc != 3) {
        dbg("Usage:\n  AT+TXPWR=idx power_level\n");
        return ERR_WRONG_ARGS;
    }

    fvif_idx = console_cmd_strtoul(argv[1], NULL, 10);
    if (fvif_idx >= NX_VIRT_DEV_MAX) {
        dbg("invalid fvif index\n");
        return ERR_WRONG_ARGS;
    }
    in_pwr_lvl = (int)console_cmd_strtoul(argv[2], NULL, 10);
    if ((in_pwr_lvl < -100) || (in_pwr_lvl > 50)) {
        dbg("invalid tx power\n");
        return ERR_WRONG_ARGS;
    }
    tx_pwr_lvl = (unsigned int)in_pwr_lvl;
    fhost_cntrl_cfgrwnx_set_tx_power(fvif_idx,tx_pwr_lvl);

    return ERR_NONE;
}

int do_mac(int argc, char * const argv[])
{
    uint8_t *mdata, mac[12];

    if(*argv[1] == '?') {
        #if (!PLF_HW_PXP)
        if (flash_wifi_sta_macaddr_read(mac) == INFO_READ_DONE) {
            set_mac_address(mac);
        }
        #endif
        mdata = get_mac_address();
        dbg("%02x:%02x:%02x:%02x:%02x:%02x\r\n",
            mdata[0], mdata[1], mdata[2], mdata[3], mdata[4], mdata[5]);
        return ERR_NONE;
    }

    if(1 == wlan_connected) {
        return ERR_CMD_ABORT;
    }

    if(strlen(argv[1]) != 12) {
        return ERR_WRONG_ARGS;
    }

    mdata = (uint8_t *)argv[1];
    for(uint8_t i = 0; i < 12; i++){
        if(mdata[i] >= 0x41 && mdata[i] <= 0x46)// switch 'A' to 'a'
            mdata[i] += 0x20;
        if(mdata[i] >= 0x61 && mdata[i] <= 0x66)//switch "ab" to 0xab
            mac[i] = mdata[i] - 0x57;
        if(mdata[i] >= 0x30 && mdata[i] <= 0x39)
            mac[i] = mdata[i] - 0x30;
        if(i%2 == 1)
            mac[i/2] = mac[i-1] << 4 | mac[i];
    }
    if((!MAC_ADDR_VALID(mac)) && (!MAC_ADDR_GROUP(mac))) {
        return ERR_WRONG_ARGS;
    }
    set_mac_address(mac);
    #if (!PLF_HW_PXP)
    flash_wifi_sta_macaddr_write(mac);
    #endif

    return ERR_NONE;
}

int do_blink_magic(int argc, char * const argv[])
{
	char *ptr;
    uint8_t mdata;

    if(*argv[1] == '?')
	{
        mdata = get_blink_magic();
        dbg("%02x\r\n", mdata);
        return ERR_NONE;
    }
	
    if(strlen(argv[1]) != 2)
	{
        return ERR_WRONG_ARGS;
    }

	mdata = strtol(argv[1], &ptr, 16);
    set_blink_magic(&mdata);

    return ERR_NONE;
}

#ifdef CFG_WPS
int do_wps_pbc (int argc, char * const argv[])
{
    wlan_start_wps();

    return ERR_NONE;
}
#endif /* CFG_WPS */

#if defined(CFG_P2P)
int do_start_p2p(int argc, char * const argv[])
{
    dbg("start p2p\n");
    wlan_start_p2p();
    return 0;
}
#endif /* CFG_P2P */

int do_auto_connect (int argc, char * const argv[])
{
    if (argc != 3) {
        dbg("Usage:\n  AT+WAUTOCNCT=mode <frcd_ap/auto_cnct>\n");
        return ERR_WRONG_ARGS;
    }

    if (strncasecmp(argv[1], "AP", 2) == 0) {
        unsigned int ap_config;
        unsigned int forced_ap_mode;
        if (flash_wifi_ap_config_read(&ap_config)) {
            dbg("flash read err\n");
            return ERR_CMD_FAIL;
        }
        forced_ap_mode = console_cmd_strtoul(argv[2],NULL,10);
        if (forced_ap_mode) {
            ap_config |=  WIFI_AP_CONFIG_FORCED_AP_MODE_EN;
        } else {
            ap_config &= ~WIFI_AP_CONFIG_FORCED_AP_MODE_EN;
        }
        flash_wifi_ap_config_write(&ap_config);
    } else if (strncasecmp(argv[1], "STA", 3) == 0) {
        unsigned int sta_config;
        unsigned int auto_connect;
        if (flash_wifi_sta_config_read(&sta_config)) {
            dbg("flash read err\n");
            return ERR_CMD_FAIL;
        }
        auto_connect = console_cmd_strtoul(argv[2],NULL,10);
        if (auto_connect > 1) {
            dbg("invalid auto_cnct parameter\n");
            return ERR_WRONG_ARGS;
        }
        if (auto_connect) {
            sta_config |=  WIFI_STA_CONFIG_STA_AUTO_CONNECT_EN;
        } else {
            sta_config &= ~WIFI_STA_CONFIG_STA_AUTO_CONNECT_EN;
        }
        flash_wifi_sta_config_write(&sta_config);
    } else {
        dbg("invalid mode\n");
        return ERR_WRONG_ARGS;
    }

    return ERR_NONE;
}

int do_connect (int argc, char * const argv[])
{
    uint8_t *ssid = NULL, *pw = NULL;
    uint8_t len = 0;
    int flash_ssid_rd_flag = 0;
    int flash_wr_flag = 0;
    unsigned char macaddr_flash[MAC_ADDR_LEN];

    if (argc == 1) {
        flash_ssid_rd_flag = 1;
    } else if (argc >= 3) {
        if (strlen(argv[1]) == 1) {
            flash_wr_flag = argv[1][0] - '0';
        } else {
            flash_wr_flag = 0x10;
        }
    }
    if ((argc == 2) || (flash_wr_flag & ~0x0FUL)) {
        dbg("Usage:\n  connect 0/1 ssid <pwd>\n");
        return ERR_WRONG_ARGS;
    }
    #if (!PLF_HW_PXP)
    if (flash_wifi_sta_macaddr_read(macaddr_flash) == INFO_READ_DONE) {
        // MAC Address
        set_mac_address(macaddr_flash);
    } else if (flash_ssid_rd_flag) {
        dbg("Wifi flash macaddr read err\n");
        return ERR_CMD_FAIL;
    } else if (flash_wr_flag == 2) {
        set_mac_address(NULL);
    }
    #endif
    is_ap = 0;
    // SSID
    ssid = rtos_malloc(MAC_SSID_LEN+1);
    if(!ssid)
        return ERR_CMD_FAIL;
    pw = rtos_malloc(PW_LEN+1);
    if(!pw) {
        rtos_free(ssid);
        ssid = NULL;
        return ERR_CMD_FAIL;
    }
    if (flash_ssid_rd_flag) {
        if(flash_wifi_sta_ssidpw_read((char *)ssid, (char *)pw) != INFO_READ_DONE) {
            rtos_free(ssid);
            ssid = NULL;
            rtos_free(pw);
            pw = NULL;
            return ERR_CMD_FAIL;
        }
    } else {
        len = ((strlen(argv[2]) + 1) > MAC_SSID_LEN) ? MAC_SSID_LEN : (strlen(argv[2]) + 1);
        memcpy(ssid, argv[2], len);
        if (argc > 3) {  // <Password>
            len = ((strlen(argv[3]) + 1) > PW_LEN) ? PW_LEN : (strlen(argv[3]) + 1);
            memcpy(pw, argv[3], len);
        } else {
            pw[0] = '\0';
        }
    }

    if(wlan_connected) {
        dbg("wlan already connected.\r\n");
        return ERR_CMD_ABORT;
    }

    if (0 == wlan_start_sta(ssid, pw, 0)) {
        wlan_connected = 1;
    }

    struct connected_ap_info_t *info;
    wlan_get_sta_connected_ap_info(&info);
    dbg("BSSID %04x:%04x:%04x,band %d, Freq %d, ssid %s\r\n", info->bssid.array[0],info->bssid.array[1],info->bssid.array[2], info->band, info->freq, info->ssid);

    if (flash_wr_flag == 1) {
        #if (!PLF_HW_PXP)
        flash_wifi_sta_ssidpw_write((char *)ssid, (char *)pw);
        #endif
    }

    rtos_free(ssid);
    ssid = NULL;
    rtos_free(pw);
    pw = NULL;

    return ERR_NONE;
}

void set_wlan_status_callback(wifi_mac_status_e st)
{
    if (WIFI_MAC_STATUS_DISCONNECTED == st) {
        dbg("STA disconnect from AP.\n");
    } else if (WIFI_MAC_STATUS_CONNECTED == st) {
        dbg("STA connect to AP.\n");
    } else if (WIFI_MAC_STATUS_IP_OBTAINED == st) {
        dbg("STA get ip.\n");
    }
}

int do_connect_cb(int argc, char * const argv[])
{
    // Change to your ssid and passward.
    char *ssid = "AP-ssid";
    char *pw = "passward";

    // set callback func.
    fhost_get_mac_status_register(set_wlan_status_callback);
    // start sta connect.
    wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, 15000);

    return ERR_NONE;
}

int do_auto_reconnect(int argc, char * const argv[])
{
    // Change to your ssid and passward.
    char *ssid = "AP-ssid";
    char *pw = "passward";

    wlan_sta_auto_reconnect((uint8_t *)ssid, (uint8_t *)pw, 3, 20000, set_wlan_status_callback);
    return ERR_NONE;
}

int do_disconnect (int argc, char * const argv[])
{
    #ifdef CFG_HOSTAPD
    wlan_disconnect_sta(fhost_search_itf_idx(VIF_STA));
    #else
    wlan_disconnect_sta(fhost_vif_idx);
    #endif

    return ERR_NONE;
}

#ifdef CFG_SOFTAP
void wlan_softap_event_test(wlan_softap_event_e event, uint8_t *device_mac)
{
    uint8_t *p_mac = (uint8_t *)device_mac;

    if (event == ASSOC_IND_EVENT) {
        dbg("%02X:%02X:%02X:%02X:%02X:%02X Joined\n", p_mac[0], p_mac[1], p_mac[2], p_mac[3], p_mac[4], p_mac[5]);
    } else if (event == DISASSOC_IND_EVENT) {
        dbg("%02X:%02X:%02X:%02X:%02X:%02X Leaved\n", p_mac[0], p_mac[1], p_mac[2], p_mac[3], p_mac[4], p_mac[5]);
    }
}


int do_start_ap (int argc, char * const argv[])
{
    uint8_t *ssid = NULL, *pw = NULL;
    uint8_t len = 0, band = 0;

    if (argc < 3) {
        dbg("Usage:\n  startap band ssid <pwd>\n");
        return ERR_WRONG_ARGS;
    }

    is_ap = 1;

    wlan_softap_event_register(wlan_softap_event_test);

    // band
    band = console_cmd_strtoul(argv[1], NULL, 10);

    // SSID
    ssid = rtos_malloc(MAC_SSID_LEN+1);
    if(!ssid)
        return ERR_CMD_FAIL;
    memset(ssid, 0, MAC_SSID_LEN+1);
    len = (strlen(argv[2]) > MAC_SSID_LEN) ? MAC_SSID_LEN : strlen(argv[2]);
    memcpy(ssid, argv[2], len);

    //<Password>
    if(argc > 3)
    {
        pw = rtos_malloc(PW_LEN+1);
        if(!pw) {
            rtos_free(ssid);
            ssid = NULL;
            return ERR_CMD_FAIL;
        }
        memset(pw, 0, PW_LEN+1);
        len = (strlen(argv[3]) > PW_LEN) ? PW_LEN : strlen(argv[3]);
        memcpy(pw, argv[3], len);
    }

    wlan_start_ap(band, ssid, pw);

    rtos_free(ssid);
    ssid = NULL;
    rtos_free(pw);
    pw = NULL;

    return ERR_NONE;
}

int do_stop_ap (int argc, char * const argv[])
{
    wlan_stop_ap();

    return ERR_NONE;
}

int do_ap_associated_sta_info(int argc, char * const argv[])
{
    int fhost_vif_idx = 0;

    fhost_vif_idx = console_cmd_strtoul(argv[1], NULL, 10);
    if (fhost_vif_idx >= NX_VIRT_DEV_MAX) {
        dbg("invalid fvif index\n");
        return ERR_NONE;
    }
    int32_t cnt = wlan_ap_get_associated_sta_cnt(fhost_vif_idx);
    if(cnt == -1) {
        dbg("Warning: softAP don`t start.\n");
        return ERR_NONE;
    }
    if(cnt == 0) {
        dbg("None associated sta.\n");
        return ERR_NONE;
    }
    dbg("Associated sta cnt: %d\n", cnt);

    int index = 0;
    void *sta_list = wlan_ap_get_associated_sta_list(fhost_vif_idx);
    struct co_list_hdr *list_hdr = co_list_pick(sta_list);
    while(list_hdr != NULL) {
        struct sta_info_tag *sta = (struct sta_info_tag *)list_hdr;
        dbg("STA[%d] = %x:%x:%x, rssi: %3d dBm%\n", index, sta->mac_addr.array[0], sta->mac_addr.array[1],
        sta->mac_addr.array[2], sta_data_pkt_rssi_get((uint8_t *)sta->mac_addr.array));
        list_hdr = co_list_next(list_hdr);
        index ++;
    }

    return ERR_NONE;
}
#endif /* CFG_SOFTAP */

#ifdef CFG_SOFTAP
#if NX_BEACONING
static struct fhost_cntrl_link *ap_link;
#include "dhcps.h"
#endif
/**
 ****************************************************************************************
 * @brief Process function for 'ap' command
 *
 * Start an AP
 * @verbatim
   ap [-i <itf>] -s <SSID> -f <freq>[+-@] [-a <akm>[,<akm 2>]] [-k <key>]
      [-b bcn_int[,dtim_period]] [-u <unicast cipher>[,<unicast cipher 2>]]
      [-g <group cipher>] [-m <mfp: 0|1|2>]
   @endverbatim
 * The '+/-' after the frequency allow to configure a 40MHz channel with the secondary
 * channel being the upper/lower one. The '@' allow to configure a 80 MHz channel, this
 * is only allowed for valid primary channel and center freq is automatically computed.
 *
 * @param[in] params  Connection parameters
 * @return 0 on success and !=0 if error occurred
 ****************************************************************************************
 */
int do_create_ap (int argc, char * const argv[])
{
#if NX_BEACONING
    struct fhost_vif_ap_cfg cfg;
    int fhost_vif_idx = 0;//fhost_search_first_valid_itf();
    char option;
    char *cfg_val;
    uint32_t cipher;

    if ((argc < 5) || (argc > 9)) {
        dbg("Usage:\n  AT+WCAP ssid  pwd  center_frequency  cipher_suite  hidden_ssid  <group cipher_type> <mfp_feature> <dtim> <beacon_interval>\n");
        return ERR_WRONG_ARGS;
    }

    memset(&cfg, 0, sizeof(cfg));
//cfg ssid
    size_t ssid_len = strlen(argv[1]);
    if (ssid_len > sizeof(cfg.ssid.array))
    {
        dbg("Invalid SSID\r\n");
        return ERR_CMD_FAIL;
    }
    memcpy(cfg.ssid.array, argv[1], ssid_len);
    cfg.ssid.length = ssid_len;
//cfg key
    size_t key_len = strlen(argv[2]);
    if ((key_len + 1) > sizeof(cfg.key))
    {
        dbg("Invalid Key\r\n");
        return ERR_CMD_FAIL;
    }
    strcpy(cfg.key, argv[2]);
//cfg freq_feature
    int len = strlen(argv[3]) - 1;
    char freq_feature = *(argv[3] + len);

    struct mac_chan_def *chan = NULL;
    int offset = 0;
    if (freq_feature == '+')
    {
        offset = 10;
        cfg.chan.type = PHY_CHNL_BW_40;
    }
    else if (freq_feature == '-')
    {
        offset = -10;
        cfg.chan.type = PHY_CHNL_BW_40;
    }
    else if (freq_feature == '@')
    {
        cfg.chan.type = PHY_CHNL_BW_80;
    }
    else
    {
        cfg.chan.type = PHY_CHNL_BW_20;
    }

    cfg.chan.prim20_freq = atoi(argv[3]);
    chan = fhost_chan_get(cfg.chan.prim20_freq);
    if (!chan)
    {
        dbg("Invalid channel\n");
        return ERR_CMD_FAIL;
    }

    if (cfg.chan.prim20_freq >= PHY_FREQ_5G)
        cfg.chan.band = PHY_BAND_5G;
    else
        cfg.chan.band = PHY_BAND_2G4;

    if (cfg.chan.type == PHY_CHNL_BW_80)
    {
        if ((cfg.chan.prim20_freq < 5180) ||
            (cfg.chan.prim20_freq > 5805))
        {
            dbg("Invalid primary for 80MHz channel\n");
            return ERR_CMD_FAIL;
        }
        offset = (cfg.chan.prim20_freq - 5180) % 80;
        if (offset < 20)
            offset = 30;
        else if (offset < 40)
            offset = 10;
        else if (offset < 60)
            offset = -10;
        else
            offset = -30;
    }
    cfg.chan.center1_freq = cfg.chan.prim20_freq + offset;
//cfg cipher suite
    fhost_nw_upper(argv[4], NULL);
    if (strncmp(argv[4], "OPEN", 4) == 0)
    {
        cfg.akm |= CO_BIT(MAC_AKM_NONE);
    }
    else if (strncmp(argv[4], "WEP", 4) == 0)
    {
        cfg.akm |= CO_BIT(MAC_AKM_PRE_RSN);
    }
    else if (strncmp(argv[4], "WPA", 3) == 0)
    {
        cfg.akm |= CO_BIT(MAC_AKM_PRE_RSN) | CO_BIT(MAC_AKM_PSK);
    }
    else if (strncmp(argv[4], "RSN", 3) == 0)
    {
        cfg.akm |= CO_BIT(MAC_AKM_PSK);
    }
    else if (strncmp(argv[4], "SAE", 3) == 0)
    {
        cfg.akm |= CO_BIT(MAC_AKM_SAE);
    }
    else
    {
        dbg("The following AKM are supported [%s]:\n"
                    "OPEN: For open AP\n"
                    "WEP: For AP with WEP security\n"
                    "WPA: For AP with WPA/PSK security (pre WPA2)\n"
                    "RSN: For AP with WPA2/PSK security\n"
                    "SAE: For AP with WPA3/PSK security\n", argv[4]);
        return ERR_CMD_FAIL;
    }
//cfg unicast_cipher_suite group_cipher_suite or bcn_interval or mpf_feature
    if(argc >= 6){
        option = *(argv[5]);
        cfg_val = (char *)(argv[5] + 1);
        if(option == 'g')
        {
            cipher = 0;
            if(((cfg.akm & CO_BIT(MAC_AKM_PRE_RSN)) == 0) && ((cfg.akm & CO_BIT(MAC_AKM_PSK)) != 0))
            {
                fhost_nw_upper(cfg_val,NULL);
                dbg("cipher type %s\n",cfg_val);
                if (strncmp(cfg_val, "CCMP", 4) == 0)
                {
                    cipher |= CO_BIT(MAC_CIPHER_CCMP);
                }
                else if (strncmp(cfg_val, "TKIP", 4) == 0)
                {
                    cipher |= CO_BIT(MAC_CIPHER_TKIP);
                }
                else
                {
                    dbg("The following cipher are supported [%s]:\n"
                            "CCMP, TKIP", cfg_val);
                    return ERR_CMD_FAIL;
                }
                cfg.group_cipher = cipher;
            }
            else
            {
                dbg("akm %s cannot cfg groupkey",argv[4]);
                return ERR_CMD_FAIL;
            }
        }
        else if(option == 'm')
        {
            cfg.mfp = atoi(cfg_val);
        }
        else if(option == 'b')
        {
            cfg.bcn_interval = atoi(cfg_val);
        }
        else if(option == 'd')
        {
            cfg.dtim_period = atoi(cfg_val);
        }
        else
        {
            dbg("Invalid additional feature: %s\n",argv[5]);
            return ERR_CMD_FAIL;
        }
    }

    if(argc >= 7){
        option = *(argv[6]);
        cfg_val = (char *)(argv[6] + 1);
        if(option == 'm')
        {
            cfg.mfp = atoi(cfg_val);
        }
        else if(option == 'b')
        {
            cfg.bcn_interval = atoi(cfg_val);
        }
        else if(option == 'd')
        {
            cfg.dtim_period = atoi(cfg_val);
        }
        else
        {
            dbg("Invalid additional feature: %s\n",argv[6]);
            return ERR_CMD_FAIL;
        }
    }

    if(argc >= 8){
        option = *(argv[7]);
        cfg_val = (char *)(argv[7] + 1);
        if(option == 'b')
        {
            cfg.bcn_interval = atoi(cfg_val);
        }
        else if(option == 'd')
        {
        cfg.dtim_period = atoi(cfg_val);
        }
        else
        {
            dbg("Invalid additional feature: %s\n",argv[7]);
            return ERR_CMD_FAIL;
        }
    }
    if(argc == 9){
        option = *(argv[8]);
        cfg_val = (char *)(argv[8] + 1);
        if(option == 'd')
        {
        cfg.dtim_period = atoi(cfg_val);
        }
        else
        {
            dbg("Invalid additional feature: %s\n",argv[8]);
            return ERR_CMD_FAIL;
        }
    }

    if (fhost_vif_idx < 0)
        return ERR_CMD_FAIL;

    if ((cfg.ssid.length == 0) || (cfg.chan.prim20_freq == 0))
        return ERR_WRONG_ARGS;

    // try to select the best AKM if not set
    if (cfg.akm == 0)
    {
        if (strlen(cfg.key) == 0)
            cfg.akm = CO_BIT(MAC_AKM_NONE);
        else if (strlen(cfg.key) == 5)
            cfg.akm = CO_BIT(MAC_AKM_PRE_RSN);
        else
            cfg.akm = CO_BIT(MAC_AKM_PSK);
    }
    cfg.enable_he = (uint8_t)fhost_config_value_get(FHOST_CFG_HE);
    ipc_host_cntrl_start();

    struct fhost_vif_tag *fhost_vif;

    ap_link = fhost_cntrl_cfgrwnx_link_open();
    if (ap_link == NULL) {
        dbg(D_ERR "Failed to open link with control task\n");
        ASSERT_ERR(0);
    }

    // (Re)Set interface type to AP
    if (fhost_set_vif_type(ap_link, fhost_vif_idx, VIF_UNKNOWN, false) ||
        fhost_set_vif_type(ap_link, fhost_vif_idx, VIF_AP, false))
        return ERR_CMD_FAIL;
    fhost_cntrl_cfgrwnx_link_close(ap_link);

    fhost_vif = &fhost_env.vif[fhost_vif_idx];
    MAC_ADDR_CPY(&(vif_info_tab[fhost_vif_idx].mac_addr), &(fhost_vif->mac_addr));

    if (fhost_ap_cfg(fhost_vif_idx, &cfg))
    {
        dbg("Failed to start AP, check your configuration");
        return ERR_CMD_FAIL;
    }

    net_if_t *net_if = fhost_to_net_if(fhost_vif_idx);
    if (net_if == NULL) {
        dbg("[AIC] net_if_find_from_wifi_idx fail\r\n");
        return 1;
    }
    uint32_t ip_mask = 0x00FFFFFF;
    uint32_t ip_addr = get_ap_ip_addr();
    net_if_set_ip(net_if, ip_addr, ip_mask, 0);

    //set up DHCP server
    dhcpServerStart(net_if);

    // Now that we got an IP address use this interface as default
    net_if_set_default(net_if);

    dbg("DHCPS init: ip=%d.%d.%d.%d\r\n",
          (ip_addr)&0xFF, (ip_addr>>8)&0xFF, (ip_addr>>16)&0xFF, (ip_addr>>24)&0xFF);

#endif // NX_BEACONING

    is_ap = 1;

    return ERR_NONE;
}
#endif /* CFG_SOFTAP */

#if NX_SMARTCONFIG
extern uint8_t disconnected_by_user;
/**
 ****************************************************************************************
 * @brief Process function for 'smartconf' command
 *
 * smartconf command allows to set the SSID and password and associate automatically
 * to an AP .
 * Wi-Fi enabled device such as a smartphone sends to the Wi-Fi Access Point(AP) the SSID
 * and password encoded into the Length field of a sequence UDP packets, then the smartconf
 * can reach packets, decode the ssid & pwd and connect to the AP

 * @return 0 on success and !=0 if error occurred
 ****************************************************************************************
 */
int do_smartconf(int argc, char * const argv[])
{
    fhost_vif_idx = 0;

    if(!disconnected_by_user) {
        set_mac_address(NULL);
        ipc_host_cntrl_start();
    }

    if (fhost_smartconf_start(fhost_vif_idx, NULL))
    {
        dbg("Fhost smartconf init failed\n");
        return ERR_CMD_ABORT;
    }

    return ERR_NONE;
}

int do_stop_smartconf(int argc, char * const argv[])
{
    if(fhost_smartconf_stop()) {
        return ERR_CMD_ABORT;
    }
    return ERR_NONE;
}
#endif /* NX_SMARTCONFIG */

#if PLF_PING
/// Handle of the ping task
static rtos_task_handle ping_task_handle;
#endif /* PLF_PING */
/**
 ****************************************************************************************
 * @brief Convert string containing ip address
 *
 * The string may should be of the form a.b.c.d/e (/e being optional)
 *
 * @param[in]  str   String to parse
 * @parse[out] ip    Updated with the numerical value of the ip address
 * @parse[out] mask  Updated with the numerical value of the network mask
 *                   (or 32 if not present)
 * @return 0 if string contained what looks like a valid ip address and -1 otherwise
 ****************************************************************************************
 */
int fhost_nw_parse_ip4(char *str, uint32_t *ip, uint32_t *mask)
{
    char *token;
    uint32_t a, i, j;

    #define check_is_num(_str)  for (j = 0 ; j < strlen(_str); j++) {  \
            if (_str[j] < '0' || _str[j] > '9')                        \
                return -1;                                             \
        }

    // Check if mask is present
    token = strchr(str, '/');
    if (token && mask) {
        *token++ = '\0';
        check_is_num(token);
        a = atoi(token);
        if (a == 0 || a > 32)
            return -1;
        *mask = (1<<a) - 1;
    }
    else if (mask)
    {
        *mask = 0xffffffff;
    }

    // parse the ip part
    *ip = 0;
    for (i = 0; i < 4; i ++)
    {
        if (i < 3)
        {
            token = strchr(str, '.');
            if (!token)
                return -1;
            *token++ = '\0';
        }
        check_is_num(str);
        a = atoi(str);
        if (a > 255)
            return -1;
        str = token;
        *ip += (a << (i * 8));
    }

    return 0;
}

/**
 ****************************************************************************************
 * @brief Extract token from parameter list
 *
 * Extract the first parameter of the string. Parameters are separatd with space unless
 * it starts with " (or ') in which case it extract the token until " (or ') is reached.
 * " (or ') are then removed from the token.
 *
 * @param[in, out] params Pointer to parameters string to parse. Updated with remaining
 *                        parameters to parse.
 * @return pointer on first parameter
 ****************************************************************************************
 */
char *fhost_nw_next_token(char **params)
{
    char *ptr = *params, *next;
    char sep = ' ';

    if (!ptr)
        return NULL;

    if ((ptr[0] == '"') || (ptr[0] == '\''))
    {
        sep = ptr[0];
        ptr++;
    }

    next = strchr(ptr, sep);
    if (next)
    {
        *next++ = '\0';
        while (*next == ' ')
            next++;
        if (*next == '\0')
            next = NULL;
    }
    *params = next;
    return ptr;
}

#if PLF_PING
/**
 ****************************************************************************************
 * @brief Process function for 'ping' command
 *
 * Ping command can be used to test the reachability of a host on an IP network.
 *
 *  ping <dst_ip> [-s pksize] [-r rate] [-d duration] [-Q tos]
 *  ping stop <id1> [<id2> ... <id8>]
 *
 * Note that -s, -r, -d, -t are options for ping command. We could choose any of them to
 * configure. If not configured, it will set the default values at layer @ref net_tg_al.
 *
 * @param[in] params ping command above
 *
 * @return 0 on success and !=0 if error occurred
 ****************************************************************************************
 */
int fhost_console_ping(char *params)
{
    char *token, *next = params;
    uint32_t rip = 0;
    token = fhost_nw_next_token(&next);
    u32_t rate = 0, pksize = 0, duration = 0, tos = 0;
    //struct fhost_task_msg_id *task_hdl_msg_ptr;
    bool background = false;
    struct fhost_ping_task_args args;

    if (!strcmp("stop", token))
    {
        u32_t stream_id;
        struct fhost_ping_stream* ping_stream;
        int ret = FHOST_NW_SUCCESS;

        token = fhost_nw_next_token(&next);
        if (!token)
        {
            dbg("No ping id\n");
            return FHOST_NW_ERROR;
        }

        stream_id = atoi(token);
        ping_stream = fhost_ping_find_stream_profile(stream_id);

        if (ping_stream)
        {
            if (ping_stream->background)
            {
                //task_hdl_msg_ptr = fhost_search_task_hdl_msg(ping_stream->ping_handle);
                //task_hdl_msg_ptr->msg_id = ipc_msg.id;
                ret = FHOST_NW_NO_RESP;
            }
            fhost_ping_stop(ping_stream);
        }
        else
        {
            dbg("Invalid stream_id %d, no stream associated\r\n", stream_id);
            ret = FHOST_NW_ERROR;
        }

        return ret;
    }
    else
    {
        do
        {
            // Handle all options of ping command
            if (token[0] == '-')
            {
                switch(token[1])
                {
                    case ('s'):
                        token = fhost_nw_next_token(&next);
                        if (!token)
                        {
                            dbg("No packet size\n");
                            return FHOST_NW_ERROR;
                        }
                        pksize = atoi(token);
                        break;
                    case ('r'):
                        token = fhost_nw_next_token(&next);
                        if (!token)
                        {
                            dbg("No rate\n");
                            return FHOST_NW_ERROR;
                        }
                        rate = atoi(token);
                        break;
                    case ('d'):
                        token = fhost_nw_next_token(&next);
                        if (!token)
                        {
                            dbg("No duration\n");
                            return FHOST_NW_ERROR;
                        }
                        duration = atoi(token);
                        break;
                    case ('Q'):
                        token = fhost_nw_next_token(&next);
                        if (!token)
                        {
                            dbg("No ToS\n");
                            return FHOST_NW_ERROR;
                        }
                        tos = atoi(token);
                        break;
                    case ('G'):
                        background = true;
                        break;
                    default:
                        dbg("Argument -%c not supported\n", token[1]);
                        return FHOST_NW_ERROR;
                }
            }
            // If it's neither options, nor IP address, then the input is wrong
            else if (fhost_nw_parse_ip4(token, &rip, NULL))
            {
                dbg("Invalid input of ping %s\n", token);
                return FHOST_NW_ERROR;
            }
        } while ((token = fhost_nw_next_token(&next)));

        // IP destination should be set by the command
        if (rip == 0)
        {
            dbg("No IP address, %s\n", token);
            return FHOST_NW_ERROR;
        }
        args.rip = rip;
        args.rate = rate;
        args.pksize = pksize;
        args.duration = duration;
        args.tos = tos;
        args.background = background;
        if ((ping_task_handle = fhost_ping_start(&args)))
        {
            //task_hdl_msg_ptr->msg_id = ipc_msg.id;
        }
        else
        {
            dbg("Send ping error\n");
            return FHOST_NW_ERROR;
        }

        if (background)
            return FHOST_NW_SUCCESS;
        else
            return FHOST_NW_NO_RESP;
    }
}
#endif /* PLF_PING */
#if PLF_IPERF
rtos_task_handle iperf_task_handle = NULL;
uint8_t remote_address[16] = {0};
/*
 * IPERF FUNCTION
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Process function for 'iperf' command
 *
 * Start an iperf server on the specified port.
 *
 * @param[in] params Port number
 * @return 0 on success and !=0 if error occurred
 ****************************************************************************************
 */
int fhost_console_iperf(char *params)
{
    char conv, *token, *substr, *next = params;
    struct fhost_iperf_settings iperf_settings;
    bool client_server_set = 0;
    int ret;

    fhost_iperf_settings_init(&iperf_settings);

    while ((token = fhost_nw_next_token(&next)))
    {
        if (token[0] != '-')
        {
            dbg("iperf: invalid option %s\n", token);
            return FHOST_NW_ERROR;
        }

        //TODO[AAL]: Add support long options

        switch(token[1])
        {
            case ('b'): // UDP bandwidth
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing bandwidth\n");
                    return FHOST_NW_ERROR;
                }

                iperf_settings.udprate = atoi (token);
                conv = token[strlen(token) - 1];

                /* convert according to [Gg Mm Kk] */
                switch (conv)
                {
                    case 'G':
                    case 'g':
                        iperf_settings.udprate *= 1000;
                    case 'M':
                    case 'm':
                        iperf_settings.udprate *= 1000;
                    case 'K':
                    case 'k':
                        iperf_settings.udprate *= 1000;
                    default: break;
                }

                iperf_settings.flags.is_udp = true;
                iperf_settings.flags.is_bw_set = true;
                // if -l has already been processed, is_buf_len_set is true so don't overwrite that value.
                if (!iperf_settings.flags.is_buf_len_set)
                {
                    iperf_settings.buf_len = FHOST_IPERF_DEFAULT_UDPBUFLEN;
                }
                break;
            }
            case ('c'): // Client mode with server host to connect to
            {
                if (client_server_set)
                {
                    dbg("iperf: Client/Server mode already set\n");
                    return FHOST_NW_ERROR;
                }
                iperf_settings.flags.is_server = 0;
                client_server_set = true;

                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing host\n");
                    return FHOST_NW_ERROR;
                }

                memcpy(remote_address, token, strlen(token));

                if (fhost_nw_parse_ip4(token, &iperf_settings.host_ip, NULL))
                {
                    dbg("iperf: invalid host IP\n");
                    return FHOST_NW_ERROR;
                }
                break;
            }
            case ('f'): // format to print in
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing format\n");
                    return FHOST_NW_ERROR;
                }
                iperf_settings.format = token[0];
                break;
            }
            case ('i'): // Interval between periodic reports
            {
                uint32_t interval = 0;
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing interval\n");
                    return FHOST_NW_ERROR;
                }

                substr = strchr(token, '.');

                if (substr)
                {
                    *substr++ = '\0';
                    interval += atoi(substr);
                }

                interval += atoi(token) * 10;
                #if (PLF_HW_PXP != 1)
                if (interval < 5)
                {
                    dbg("iperf: interval must be greater than or equal to 0.5. Interval set to 0.5\n");
                    interval = 5;
                }
                #endif /* !PLF_HW_PXP */

                iperf_settings.interval.sec = interval / 10;
                iperf_settings.interval.usec = 100000 * (interval - (iperf_settings.interval.sec * 10));
                break;
            }
            case ('l'): //Length of each buffer
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing buffer length\n");
                    return FHOST_NW_ERROR;
                }

                iperf_settings.buf_len = atoi( token );
                iperf_settings.flags.is_buf_len_set = true;
                if (iperf_settings.flags.is_udp && iperf_settings.buf_len < (int) sizeof( struct iperf_UDP_datagram ))
                {
                    iperf_settings.buf_len = sizeof( struct iperf_UDP_datagram );
                    dbg("iperf: buffer length must be greater than or equal to %d in UDP\n",
                                sizeof(struct iperf_UDP_datagram));
                }
                break;
            }
            case ('n'): // amount mode (instead of time mode)
            {
                iperf_settings.flags.is_time_mode = false;
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing amount (-n)\n");
                    return FHOST_NW_ERROR;
                }
                iperf_settings.amount = atoi( token );
                break;
            }
            case ('p'): //server port
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing server port\n");
                    return FHOST_NW_ERROR;
                }
                iperf_settings.port = atoi( token );
                break;
            }
            case ('s'): // server mode
            {
                if (client_server_set)
                {
                    dbg("iperf: Client/Server already set\n");
                    return FHOST_NW_ERROR;
                }
                iperf_settings.flags.is_server = 1;
                client_server_set = true;
                break;
            }
            case ('t'): // time mode (instead of amount mode)
            {
                iperf_settings.flags.is_time_mode = true;
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing time\n");
                    return FHOST_NW_ERROR;
                }
                iperf_settings.amount = 0;
                substr = strchr(token, '.');
                if (substr)
                {
                    *substr++ = '\0';
                    iperf_settings.amount += atoi(substr);
                }

                iperf_settings.amount += atoi(token) * 10;
                break;
            }
            case ('u'): // UDP instead of TCP
            {
                // if -b has already been processed, UDP rate will be non-zero, so don't overwrite that value
                if (!iperf_settings.flags.is_udp)
                {
                    iperf_settings.flags.is_udp = true;
                    iperf_settings.udprate = FHOST_IPERF_DEFAULT_UDPRATE;
                }

                // if -l has already been processed, is_buf_len_set is true, so don't overwrite that value.
                if (!iperf_settings.flags.is_buf_len_set)
                {
                    iperf_settings.buf_len = FHOST_IPERF_DEFAULT_UDPBUFLEN;
                }
                break;
            }
            case ('S'): // IP type-of-service
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing TOS\n");
                    return FHOST_NW_ERROR;
                }
                // the zero base allows the user to specify
                // hexadecimals: "0x#"
                // octals: "0#"
                // decimal numbers: "#"
                iperf_settings.tos = strtol( token, NULL, 0 );
                break;
            }
            case ('T'): // TTL
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("iperf: missing TTL\n");
                    return FHOST_NW_ERROR;
                }
                iperf_settings.ttl = atoi(token);
                break;
            }
            case ('X'): // Peer version detect
            {
                iperf_settings.flags.is_peer_ver = true;
                break;
            }
            case ('h'): // Long Help
            {
                uart_puts(iperf_long_help);
                return FHOST_NW_SUCCESS;
            }
            default: // Short Help
            {
                dbg(iperf_short_help);
                return FHOST_NW_SUCCESS;
            }
        }
    };

    if (!client_server_set)
    {
        dbg("iperf: missing option -s or -c\n");
        dbg(iperf_short_help);
        return FHOST_NW_ERROR;
    }
    ret = fhost_iperf_start(&iperf_settings, &iperf_task_handle);
    if (ret) {
        dbg("iperf_start, ret=%d\n", ret);
        return FHOST_NW_ERROR;
    }
    return FHOST_NW_SUCCESS;
}
#endif /* PLF_IPERF */

int sta_auto_connect(void)
{
    uint8_t *ssid = NULL, *pw = NULL;
    unsigned int ap_config, sta_config;
    int ret;

    ret = flash_wifi_ap_config_read(&ap_config);
    if (ret < 0) {
        dbg("Wifi ap_config read err: %d\n", ret);
        return -1;
    } else if (ret > 0) {
        // flag never set
        ap_config = 0;
    }
    ret = flash_wifi_sta_config_read(&sta_config);
    if (ret < 0) {
        dbg("Wifi sta_config read err: %d\n", ret);
        return -1;
    } else if (ret > 0) {
        // flag never set
        sta_config = 0;
    }
    if (((ap_config & WIFI_AP_CONFIG_FORCED_AP_MODE_EN) == 0) && (sta_config & WIFI_STA_CONFIG_STA_AUTO_CONNECT_EN)) {
        // SSID
        ssid = rtos_malloc(MAC_SSID_LEN+1);
        if(!ssid)
            return -1;
        //<Password>
        pw = rtos_malloc(PW_LEN+1);
        if(!pw) {
            rtos_free(ssid);
            ssid = NULL;
            return -1;
        }
        ret = flash_wifi_sta_ssidpw_read((char *)ssid, (char *)pw);
        if (ret) {
            dbg("WiFi sta_ssid_pw read err: %d\n", ret);
            return -1;
        }
        if (0 == wlan_start_sta(ssid, pw, 0)) {
            wlan_connected = 1;
        }
        rtos_free(ssid);
        ssid = NULL;
        rtos_free(pw);
        pw = NULL;
    }
    return 0;
}

