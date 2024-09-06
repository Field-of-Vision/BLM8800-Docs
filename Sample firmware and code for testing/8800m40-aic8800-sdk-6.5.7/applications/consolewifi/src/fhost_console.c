/**
 ****************************************************************************************
 *
 * @file fhost_console.c
 *
 * @brief Implementation of the fully hosted console task.
 *
 * Copyright (C) RivieraWaves 2017-2018
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup FHOST_CONSOLE
 * @{
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdlib.h>
#include "rtos.h"
#include "mac.h"
#include "fhost.h"
#include "fhost_wpa.h"
#include "fhost_cntrl.h"
#include "fhost_config.h"
#include "fhost_iperf.h"
#include "dbg_assert.h"
#include "rwnx_utils.h"
#include "rwnx_msg_tx.h"
#include "net_al.h"
#include "console.h"
#include "wlan_if.h"
#include "command.h"
#include "fhost_tx.h"
#include "fhost_command_common.h"
#include "sysctrl_api.h"
#include "sleep_api.h"
#include "co_main.h"
#include "tgt_cfg_wifi.h"
#include "gpio_api.h"
#include "pmic_api.h"
#include "reg_anareg.h"

#if defined(CFG_MODULE_WEBCLIENT)
#include "aic_ota.h"
#include "webclient.h"
#endif
#if defined(CFG_WIFI_TESTMODE)
#include "pmic_api.h"
#endif
#if PLF_MODULE_TEMP_COMP
#include "temp_comp.h"
#endif /* PLF_MODULE_TEMP_COMP */
#if PLF_RSSI_DATAPKT
#include "rwnx_rx.h"
#endif

/// Console task message queue size
#define FHOST_CONSOLE_QUEUE_SIZE    10


/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
/// Master message queue
static rtos_queue console_queue;

/// Link to control task
static struct fhost_cntrl_link *console_cntrl_link;

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
static int fhost_network_parse_ip4(char *str, uint32_t *ip, uint32_t *mask)
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
 * @brief Find the interface index
 *
 * @param[in] name Name of the interace
 * @return Index of the FHOST wifi interface or -1 if interface doesn't exist.
 ****************************************************************************************
 */
static int fhost_console_search_itf(char *name)
{
    int fhost_vif_idx = fhost_vif_idx_from_name(name);

    if (fhost_vif_idx >= 0)
        return fhost_vif_idx;

    dbg("Cannot find interface %s\n", name);
    return -1;
}


#if PLF_IPERF
static int do_iperf(int argc, char * const argv[])
{
    char iperf_params[128] = {0};
    unsigned int idx = 0, j = 0;
    int ret;

    if ((argc < 1)) {
        dbg ("Usage:\n  iperf <-s|-c|-h> [options]\n");
        return 1;
    }

    if (!netif_is_up(net_if_find_from_wifi_idx(fhost_vif_idx)))  {
        dbg ("Usage:\n Connect AP first\n");
        return 1;
    }

    memcpy(&(iperf_params[idx]), argv[1], strlen(argv[1]));
    idx += strlen(argv[1]);

    if(strstr(iperf_params, "stop")) {
        dbg("Stop iperf task\n");
        fhost_iperf_sigkill_handler(iperf_task_handle);
        return 0;
    }

    j = 3;
    while(j <= argc) {
        iperf_params[idx] = ' ';
        idx ++;
        memcpy(&(iperf_params[idx]), argv[j - 1], strlen(argv[j - 1]));
        idx += strlen(argv[j - 1]);
        j++;
    }

    ret = fhost_console_iperf(iperf_params);
    if (ret) {
        dbg("iperf failed: %d\n", ret);
    }

    return 0;
}
#endif /* PLF_IPERF */
#if PLF_PING
static int do_ping(int argc, char * const argv[])
{
    char ping_params[64] = {0};
    unsigned int idx = 0, j = 0;
    if ((argc < 2)) {
        dbg ("Usage:\n  ping dst_ip|stop ID\n");
        return 1;
    }

    if (!netif_is_up(net_if_find_from_wifi_idx(fhost_vif_idx)))  {
        dbg ("Usage:\n Connect first\n");
        return 1;
    }

    memcpy(&(ping_params[idx]), argv[1], strlen(argv[1]));
    idx += strlen(argv[1]);
    j = 3;
    while(j <= argc) {
        ping_params[idx] = ' ';
        idx ++;
        memcpy(&(ping_params[idx]), argv[j - 1], strlen(argv[j - 1]));
        idx += strlen(argv[j - 1]);
        j++;
    }

    fhost_console_ping(ping_params);

    return 0;
}
#endif /* PLF_PING */

static void fhost_console_get_scan_status(uint32_t st)
{
   // dbg("ST %x\r\n", st);
}

/**
 ****************************************************************************************
 * @brief Process function for 'scan' command
 *
 * @param[in] params Not used
 * @return 0 on success and !=0 if error occurred
 ****************************************************************************************
 */
static int do_scan(int argc, char * const argv[])
{
    int nb_res;
    struct mac_scan_result result;
    unsigned int fvif_idx;

    if (argc < 2) {
        return -1;
    }
    fhost_get_scan_status_register(fhost_console_get_scan_status);

    fvif_idx = console_cmd_strtoul(argv[1], NULL, 10);
    if (fvif_idx >= NX_VIRT_DEV_MAX) {
        dbg("invalid fvif index\n");
        return -2;
    }
    ipc_host_cntrl_start();

    console_cntrl_link = fhost_cntrl_cfgrwnx_link_open();
    if (console_cntrl_link == NULL) {
        dbg(D_ERR "Failed to open link with control task\n");
        ASSERT_ERR(0);
    }
    // Reset STA interface (this will end previous wpa_supplicant task)
    if (fhost_set_vif_type(console_cntrl_link, fvif_idx, VIF_UNKNOWN, false) ||
        fhost_set_vif_type(console_cntrl_link, fvif_idx, VIF_STA, false)) {

        fhost_cntrl_cfgrwnx_link_close(console_cntrl_link);
        return -1;
   }

    nb_res = fhost_scan(console_cntrl_link, fvif_idx, NULL);
    dbg("Got %d scan results\n", nb_res);

    nb_res = 0;
    while(fhost_get_scan_results(console_cntrl_link, nb_res++, 1, &result)) {
        if (result.ssid.length < MAC_SSID_LEN)
            result.ssid.array[result.ssid.length] = '\0'; // set ssid string ending

        if(result.ssid.array[0] == '\0') {
            memcpy(result.ssid.array, "[Hidden ssid]", sizeof("[Hidden ssid]"));
            result.ssid.array[sizeof("[Hidden ssid]")] = '\0';
        }
        dbg("(%3d dBm) CH=%3d BSSID=%02x:%02x:%02x:%02x:%02x:%02x "
            #if (PLF_AIC8800) || (PLF_AIC8800MC)
            "Format=%02x akm =%x G=%x P=%x WG=%x WP=%x "
            #endif
            "SSID=%s\n",
            (int8_t)result.rssi, phy_freq_to_channel(result.chan->band, result.chan->freq),
            ((uint8_t *)result.bssid.array)[0], ((uint8_t *)result.bssid.array)[1],
            ((uint8_t *)result.bssid.array)[2], ((uint8_t *)result.bssid.array)[3],
            ((uint8_t *)result.bssid.array)[4], ((uint8_t *)result.bssid.array)[5],
            #if (PLF_AIC8800 || PLF_AIC8800MC)
            result.format, result.akm, result.group_cipher, result.pairwise_cipher, result.wpa_group_cipher, result.wpa_pairwise_cipher,
            #endif
            (char *)result.ssid.array);
    }

    fhost_cntrl_cfgrwnx_link_close(console_cntrl_link);
    return 0;
}


/**
 ****************************************************************************************
 * @brief Process function for 'super_scan' command
 *
 * @param[in] fvif_idx
 * @return 0 on success and !=0 if error occurred
 ****************************************************************************************
 */
static int do_super_scan(int argc, char * const argv[])
{
    int nb_res;
    struct mac_scan_result result;
    unsigned int fvif_idx = 0;

    fvif_idx = console_cmd_strtoul(argv[1], NULL, 10);
    if (fvif_idx >= NX_VIRT_DEV_MAX) {
        return ERR_WRONG_ARGS;
    }
    ipc_host_cntrl_start();

    console_cntrl_link = fhost_cntrl_cfgrwnx_link_open();
    if (console_cntrl_link == NULL) {
        dbg(D_ERR "Failed to open link with control task\n");
        ASSERT_ERR(0);
    }
    // Reset STA interface (this will end previous wpa_supplicant task)
    if (fhost_set_vif_type(console_cntrl_link, fvif_idx, VIF_UNKNOWN, false) ||
        fhost_set_vif_type(console_cntrl_link, fvif_idx, VIF_STA, false)) {

        fhost_cntrl_cfgrwnx_link_close(console_cntrl_link);
        return ERR_CMD_FAIL;
    }

    struct fhost_super_scan_t param;
    struct cfgrwnx_scan_ssid ssid;
    char *ssid_str = "AP-Test";
    uint8_t bssid_str[] = {0x00, 0xAA, 0xBB, 0xCC, 0x3d, 0x95};
    int freqs[] = {2437};
    ssid.len = strlen(ssid_str);
    ssid.ssid = (uint8_t *)ssid_str;
    memset(&param, 0, sizeof(param));
    param.band = -1;
    param.ssid_cnt = 1;
    param.ssids = &ssid;
    param.bssid = bssid_str;
    param.freqs = freqs;
    nb_res = fhost_super_scan(console_cntrl_link, fvif_idx, &param);
    dbg("Got %d scan results\n", nb_res);

    nb_res = 0;
    while(fhost_get_scan_results(console_cntrl_link, nb_res++, 1, &result)) {
        result.ssid.array[result.ssid.length] = '\0'; // set ssid string ending
        dbg("(%3d dBm) CH=%3d BSSID=%02x:%02x:%02x:%02x:%02x:%02x SSID=%s\n",
        (int8_t)result.rssi, phy_freq_to_channel(result.chan->band, result.chan->freq),
        ((uint8_t *)result.bssid.array)[0], ((uint8_t *)result.bssid.array)[1],
        ((uint8_t *)result.bssid.array)[2], ((uint8_t *)result.bssid.array)[3],
        ((uint8_t *)result.bssid.array)[4], ((uint8_t *)result.bssid.array)[5],
        (char *)result.ssid.array);
    }
    fhost_cntrl_cfgrwnx_link_close(console_cntrl_link);

    return ERR_NONE;
}

/**
 ****************************************************************************************
 * @brief Process function for 'status' command
 *
 * @param[in] params Optional command parameter
 *                   Valid parameter: "chan", "vif"
 *
 * @return FHOST_IPC_SUCCESS on success and FHOST_IPC_ERROR if error occurred
 ****************************************************************************************
 */
static int do_status(int argc, char * const argv[])
{
    struct fhost_status status;
    bool show_vif = true, show_chan = true;
    int i;

    if (argc > 1) {
        if (!strncmp("vif", argv[1], 3))
            show_chan = false;
        else if (!strncmp("chan", argv[1], 4))
            show_vif = false;
        else {
            dbg("invalid subcmd\n");
            return -1;
        }
    }

    fhost_get_status(&status);

    if (show_chan) {
        const struct mac_chan_def *chan_def;
        dbg("Available Channels:\n");

        for (chan_def = &(status.chan_2g4[0]), i = 0;
             i < (status.chan_2g4_cnt + status.chan_5g_cnt);
             chan_def++, i++) {
            if (i == status.chan_2g4_cnt)
                chan_def = &(status.chan_5g[0]);

            dbg("ch: %3d, freq: %dMhz, TX pwr: %2d dBm, flags: %s%s\n",
                phy_freq_to_channel(chan_def->band, chan_def->freq),
                chan_def->freq, chan_def->tx_power,
                chan_def->flags & CHAN_NO_IR ? "[NO_IR]" : "",
                chan_def->flags & CHAN_DISABLED ? "[DISABLED]" : "");
        }
        dbg("\n");
    }

    if (show_vif) {
        for (i = 0; i < status.vif_max_cnt; i++) {
            struct fhost_vif_status vif_status;
            char vif_name[4];
            fhost_get_vif_status(i, &vif_status);
            memset(vif_name, 0, sizeof(vif_name));
            fhost_vif_name(i, vif_name, sizeof(vif_name) - 1);
            dbg("[%d] %s: MAC=%02x:%02x:%02x:%02x:%02x:%02x ",
                i, vif_name[0] ? vif_name : "nul",
                vif_status.mac_addr[0], vif_status.mac_addr[1],
                vif_status.mac_addr[2], vif_status.mac_addr[3],
                vif_status.mac_addr[4], vif_status.mac_addr[5]);
            switch (vif_status.type) {
                case VIF_STA:
                    dbg("STA");
                    break;
                case VIF_IBSS:
                    dbg("IBSS");
                    break;
                case VIF_AP:
                    dbg("AP");
                    break;
                case VIF_MESH_POINT:
                    dbg("MESH");
                    break;
                case VIF_MONITOR:
                    dbg("MONITOR");
                    break;
                default:
                    dbg("INACTIVE\n");
                    break;
            }
            if (vif_status.type != VIF_UNKNOWN) {
                if (vif_status.chan.prim20_freq != 0) {
                    dbg(", Operating Channel: %dMHz@%dMHz\n",
                                vif_status.chan.prim20_freq,
                                (1 << vif_status.chan.type) * 20);
                } else {
                    dbg(", No Operating Channel\n");
                }
            }
        }
    }

    return 0;
}

/**
 ****************************************************************************************
 * @brief Process function for 'ip' command
 *
 * ip command can be used for.
 * - address managing:
   @verbatim
      ip show [itf-name]
      ip add <ip>/<mask> [gw] <itf-name>
      ip del <itf-name>
   @endverbatim
 *
 * @param[in] params Port number
 * @return 0 on success and !=0 if error occurred
 ****************************************************************************************
 */
static int do_ip(int argc, char * const argv[])
{
    int fhost_vif_idx = -1;
    if (argc < 2) {
        dbg("wrong # of args\n");
        return -1;
    }
    if (!strcmp("show", argv[1])) {
        int i = 0;
        int i_end = NX_VIRT_DEV_MAX;
        if (argc > 2) {
            fhost_vif_idx = fhost_console_search_itf(argv[2]);
            if (fhost_vif_idx < 0) {
                dbg("invalid itf\r\n");
                return -2;
            }
            i = fhost_vif_idx;
            i_end = fhost_vif_idx + 1;
        }
        for (; i < i_end; i++) {
            char ifname[NET_AL_MAX_IFNAME];
            char *state, *connected;
            struct fhost_vif_ip_addr_cfg ip_cfg;
            uint32_t ip, gw;
            const uint8_t *mac_addr;

            if (fhost_env.vif[i].mac_vif &&
                (fhost_env.vif[i].mac_vif->type != VIF_UNKNOWN)) {
                state = "UP";
                if (fhost_env.vif[i].mac_vif->active)
                    connected = ",CONNECTED";
                else
                    connected = "";
            } else {
                state = "DOWN";
                connected = "";
            }
            mac_addr = net_if_get_mac_addr(fhost_to_net_if(i));

            if (fhost_vif_name(i, ifname, NET_AL_MAX_IFNAME) < 0)
                return -3;

            if (fhost_get_vif_ip(i, &ip_cfg))
                return -4;

            ip = ip_cfg.ipv4.addr;
            gw = ip_cfg.ipv4.gw;
            dbg("[%d] %s: MAC=%02x:%02x:%02x:%02x:%02x:%02x ip=%d.%d.%d.%d/%d gw=%d.%d.%d.%d %s%s\n", i, ifname[0] ? ifname : "nul",
                mac_addr[0], mac_addr[1], mac_addr[2],
                mac_addr[3], mac_addr[4], mac_addr[5],
                ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff,
                32 - co_clz(ip_cfg.ipv4.mask),
                gw & 0xff, (gw >> 8) & 0xff, (gw >> 16) & 0xff, (gw >> 24) & 0xff,
                state, connected);
        }
    } else if (!strcmp("add", argv[1])) {
        struct fhost_vif_ip_addr_cfg ip_cfg;
        char *ip_str, *gw_str = NULL, *itf = NULL;

        memset(&ip_cfg, 0, sizeof(ip_cfg));
        ip_str = argv[2];
        if (argc == 4) {
            itf = argv[3];
        } else if (argc > 4) {
            gw_str = argv[3];
            itf = argv[4];
        }

        fhost_vif_idx = fhost_console_search_itf(itf);
        if (fhost_vif_idx < 0) {
            return -5;
        }

        ip_cfg.mode = IP_ADDR_STATIC_IPV4;
        if (fhost_network_parse_ip4(ip_str, &ip_cfg.ipv4.addr, &ip_cfg.ipv4.mask)) {
            return -6;
        }
        if (gw_str && fhost_network_parse_ip4(gw_str, &ip_cfg.ipv4.gw, NULL)) {
            return -7;
        }
        if (fhost_set_vif_ip(fhost_vif_idx, &ip_cfg))
            return -8;
        dbg("add ip=%s gw=%s itf=%s\r\n",ip_str, gw_str ? gw_str : "null", itf);
    } else if (!strcmp("del", argv[1])) {
        struct fhost_vif_ip_addr_cfg ip_cfg;
        char *itf = argv[2];
        fhost_vif_idx = fhost_console_search_itf(itf);
        if (fhost_vif_idx < 0)
            return -9;

        ip_cfg.mode = IP_ADDR_NONE;
        fhost_set_vif_ip(fhost_vif_idx, &ip_cfg);
        dbg("del itf=%s\r\n", itf);
    } else {
        dbg("invalid subcmd\n");
    }
    return 0;
}

static int do_wpa_cli(int argc, char * const argv[])
{
    int res, resp_len, fhost_vif_idx;
    char *resp, *cmd;

    #if 0
    if (strstr(params, "-i"))
    {
        // skip "-i"
        token = fhost_ipc_next_token(&next);
        token = fhost_ipc_next_token(&next);

        fhost_vif_idx = fhost_search_itf(token);
    }
    else
    {
        fhost_vif_idx = fhost_search_first_valid_itf();
    }
    #else
    fhost_vif_idx = 0;
    #endif

    if (fhost_vif_idx < 0)
        return -1;

    // convert command to upper case
    cmd = argv[1];

    resp_len = 256;//2048;
    resp = rtos_malloc(resp_len + 1);
    if (!resp)
        return -2;

    res = fhost_wpa_execute_cmd(fhost_vif_idx, resp, &resp_len, 10000, cmd);
    if (res >= 0)
    {
        resp[resp_len] = '\0';
        dbg("%s\n", resp);
        //dump_mem((uint32_t)resp, 32, 4, true);
        if (res > 0)
            res = -3;
        else
            res = 0;
    }
    else
    {
        dbg("wpa cmd res=%d, resp=%s\n", res, resp);
        res = -4;
    }

    rtos_free(resp);
    return res;
}

static int do_fixrate(int argc, char * const argv[])
{
    int fvif_idx = 0;
    uint8_t bw_input = 0;
    uint8_t frmt_input = 0;
    uint8_t rateidx_input = 11;
    uint8_t gi_pre_type   = 0;
    uint8_t sta_idx = 0;
    union fixed_rate_ctrl_info rate_info = {.value = 0};
    struct fhost_vif_tag *fhost_vif;
    struct vif_info_tag *mac_vif;

    fvif_idx = (int)console_cmd_strtoul(argv[1], NULL, 10);
    bw_input = (uint8_t)console_cmd_strtoul(argv[2], NULL, 10);
    frmt_input = (uint8_t)console_cmd_strtoul(argv[3], NULL, 10);
    rateidx_input = (uint8_t)console_cmd_strtoul(argv[4], NULL, 10);
    if (argc > 5) {
        gi_pre_type   = (uint8_t)console_cmd_strtoul(argv[5], NULL, 10);
    }

    if (fvif_idx >= NX_VIRT_DEV_MAX) {
        dbg("invalid fhost_vif_idx: %d\n", fvif_idx);
        return 1;
    }
    fhost_vif = &fhost_env.vif[fvif_idx];
    mac_vif = fhost_vif->mac_vif;
    if (fhost_vif->mac_vif == NULL) {
        dbg("mac_vif is NULL\n");
        return 2;
    }
    if (mac_vif->type == VIF_STA)
        sta_idx = mac_vif->u.sta.ap_id;
    else if (mac_vif->type == VIF_AP) { // for softAP, only support first sta
        struct sta_info_tag *sta = (struct sta_info_tag *)co_list_pick(&mac_vif->sta_list);
        if(!sta->valid) {
            return 3;
        }
        sta_idx = sta->staid;
    } else {
        dbg("unsupported vif_type: %d\n", mac_vif->type);
        return 4;
    }
    rate_info.bwTx = bw_input;
    rate_info.formatModTx = frmt_input;
    rate_info.mcsIndexTx = rateidx_input;
    rate_info.giAndPreTypeTx = gi_pre_type;

    fhost_cntrl_cfgrwnx_set_fixed_rate(sta_idx, &rate_info);

    return 0;
}

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
static struct fhost_cntrl_link *sta_link;

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
int do_ap(int argc, char * const argv[])
{
#if NX_BEACONING
    char ap_params[256] = {0};
    unsigned int idx = 0, j = 0;
    struct fhost_vif_ap_cfg cfg;
    int fhost_vif_idx = 0;//fhost_search_first_valid_itf();

    if ((argc < 1)) {
        dbg("Usage:\n  ap \n");
        return ERR_WRONG_ARGS;
    }

    j = 2;
    while(j <= argc) {
        memcpy(&(ap_params[idx]), argv[j - 1], strlen(argv[j - 1]));
        idx += strlen(argv[j - 1]);
        ap_params[idx] = ' ';
        idx ++;
        j++;
    }

    char *token, *next = ap_params;
    memset(&cfg, 0, sizeof(cfg));

    while ((token = fhost_nw_next_token(&next)))
    {
        char option;

        if ((token[0] != '-') | (token[2] != '\0'))
            return ERR_WRONG_ARGS;

        option = token[1];
        token = fhost_nw_next_token(&next);
        if (!token)
            return ERR_WRONG_ARGS;

        switch(option)
        {
            #if 0
            case 'i':
            {
                fhost_vif_idx = fhost_search_itf(token);
                if (fhost_vif_idx < 0)
                    return ERR_CMD_FAIL;
                break;
            }
            #endif
            case 's':
            {
                size_t ssid_len = strlen(token);
                if (ssid_len > sizeof(cfg.ssid.array))
                {
                    dbg("Invalid SSID\r\n");
                    return ERR_CMD_FAIL;
                }

                memcpy(cfg.ssid.array, token, ssid_len);
                cfg.ssid.length = ssid_len;
                break;
            }
            case 'k':
            {
                size_t key_len = strlen(token);
                if ((key_len + 1) > sizeof(cfg.key))
                {
                    dbg("Invalid Key\r\n");
                    return ERR_CMD_FAIL;
                }
                strcpy(cfg.key, token);
                break;
            }
            case 'f':
            {
                int len = strlen(token) - 1;
                struct mac_chan_def *chan = NULL;
                int offset = 0;
                if (token[len] == '+')
                {
                    token[len] = 0;
                    offset = 10;
                    cfg.chan.type = PHY_CHNL_BW_40;
                }
                else if (token[len] == '-')
                {
                    token[len] = 0;
                    offset = -10;
                    cfg.chan.type = PHY_CHNL_BW_40;
                }
                else if (token[len] == '@')
                {
                    token[len] = 0;
                    cfg.chan.type = PHY_CHNL_BW_80;
                }
                else
                {
                    cfg.chan.type = PHY_CHNL_BW_20;
                }

                cfg.chan.prim20_freq = atoi(token);
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
                break;
            }
            case 'a':
            {
                char *next_akm;
                fhost_nw_upper(token, NULL);
                next_akm = strchr(token, ',');
                while (token)
                {
                    if (strncmp(token, "OPEN", 4) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_NONE);
                    }
                    else if (strncmp(token, "WEP", 4) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_PRE_RSN);
                    }
                    else if (strncmp(token, "WPA", 3) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_PRE_RSN) | CO_BIT(MAC_AKM_PSK);
                    }
                    else if (strncmp(token, "RSN", 3) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_PSK);
                    }
                    else if (strncmp(token, "SAE", 3) == 0)
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
                                    "SAE: For AP with WPA3/PSK security\n", token);
                        if (strncmp(token, "HELP", 4) == 0)
                            return ERR_NONE;
                        else
                            return ERR_CMD_FAIL;
                    }

                    token = next_akm;
                    if (token)
                    {
                        token++;
                        next_akm = strchr(token, ',');
                    }
                }
                break;
            }
            case 'u':
            case 'g':
            {
                char *next_cipher;
                uint32_t cipher = 0;

                fhost_nw_upper(token, NULL);
                next_cipher = strchr(token, ',');
                while (token)
                {
                    if (strncmp(token, "CCMP", 4) == 0)
                    {
                        cipher |= CO_BIT(MAC_CIPHER_CCMP);
                    }
                    else if (strncmp(token, "TKIP", 4) == 0)
                    {
                        cipher |= CO_BIT(MAC_CIPHER_TKIP);
                    }
                    else if (strncmp(token, "WEP40", 5) == 0)
                    {
                        cipher |= CO_BIT(MAC_CIPHER_WEP40);
                    }
                    else if (strncmp(token, "WEP104", 6) == 0)
                    {
                        cipher |= CO_BIT(MAC_CIPHER_WEP104);
                    }
                    else if (strncmp(token, "SMS4", 4) == 0)
                    {
                        cipher |= CO_BIT(MAC_CIPHER_WPI_SMS4);
                    }
                    else
                    {
                        dbg("The following cipher are supported [%s]:\n"
                                    "CCMP, TKIP, WEP40, WEP104, SMS4", token);
                        if (strncmp(token, "HELP", 4) == 0)
                            return ERR_NONE;
                        else
                            return ERR_CMD_FAIL;
                    }

                    token = next_cipher;
                    if (token)
                    {
                        token++;
                        next_cipher = strchr(token, ',');
                    }
                }

                if (option == 'u')
                    cfg.unicast_cipher = cipher;
                else
                    cfg.group_cipher = cipher;

                break;
            }
            case 'b':
            {
                char *dtim = strchr(token, ',');
                if (dtim)
                {
                    *dtim++ = 0;
                    cfg.dtim_period = atoi(dtim);
                }
                cfg.bcn_interval = atoi(token);

                break;
            }
            case 'm':
            {
                cfg.mfp = atoi(token);
                break;
            }
            case 'h':
            {
                cfg.hidden_ssid = atoi(token);
                break;
            }
            default:
            {
                dbg("Invalid option %c\n", option);
                return ERR_WRONG_ARGS;
            }
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

    fhost_tx_task_init();

    dbg("DHCPS init: ip=%d.%d.%d.%d\r\n",
          (ip_addr)&0xFF, (ip_addr>>8)&0xFF, (ip_addr>>16)&0xFF, (ip_addr>>24)&0xFF);

#endif // NX_BEACONING


    return ERR_NONE;
}

/**
 ****************************************************************************************
 * @brief Convert string containing MAC address
 *
 * The string may should be of the form xx:xx:xx:xx:xx:xx
 *
 * @param[in]  str   String to parse
 * @param[out] addr  Updated with MAC address
 * @return 0 if string contained what looks like a valid MAC address and -1 otherwise
 ****************************************************************************************
 */
static int fhost_nw_parse_mac_addr(char *str, struct mac_addr *addr)
{
    char *ptr = str;
    uint32_t i;

    if (!str || strlen(str) < 17 || !addr)
        return -1;

    for (i = 0 ; i < 6 ; i++)
    {
        char *next;
        long int hex = strtol(ptr, &next, 16);
        if (((unsigned)hex > 255) || ((hex == 0) && (next == ptr)) ||
            ((i < 5) && (*next != ':')) ||
            ((i == 5) && (*next != '\0')))
            return -1;

        ((uint8_t *)addr)[i] = (uint8_t)hex;
        ptr = ++next;
    }

    return 0;
}

#ifdef CFG_WAPI
char wapi_cert_info[]  =
"-----BEGIN ASU CERTIFICATE-----\n"
"MIICMTCCAeWgAwIBAgIEICIDCTAMBggqgRzXYwEBAQUAMFQxFDASBgoJkiaJk/Is\n"
"ZAEZFgRXQVBJMQswCQYDVQQGEwJDTjENMAsGA1UEChMEMDAwMzEOMAwGA1UECxMF\n"
"QlJPTUUxEDAOBgNVBAMUB1dBUElfQVMwHhcNNzAwMTAxMDAwMTIyWhcNNzkxMjMw\n"
"MDAwMTIyWjBUMRQwEgYKCZImiZPyLGQBGRYEV0FQSTELMAkGA1UEBhMCQ04xDTAL\n"
"BgNVBAoTBDAwMDMxDjAMBgNVBAsTBUJST01FMRAwDgYDVQQDFAdXQVBJX0FTMEow\n"
"FAYHKoZIzj0CAQYJKoEc12MBAQIBAzIABJWIWXfzUdIn3J/CLAPeON2HJWftl7xd\n"
"AD5mRwMcwhTcMYwlaKppPwotgHRUHxe2kKOBsTCBrjAdBgNVHQ4EFgQUltILaDOM\n"
"KTnaeNzuN+nr95+YaEEwfwYDVR0jBHgwdoAUltILaDOMKTnaeNzuN+nr95+YaEGh\n"
"WKRWMFQxFDASBgoJkiaJk/IsZAEZFgRXQVBJMQswCQYDVQQGEwJDTjENMAsGA1UE\n"
"ChMEMDAwMzEOMAwGA1UECxMFQlJPTUUxEDAOBgNVBAMUB1dBUElfQVOCBCAiAwkw\n"
"DAYDVR0TBAUwAwEB/zAMBggqgRzXYwEBAQUAAzgAMDUCGQCsJCTUQ/zl3wEJ/pd4\n"
"mmRvXdDXYqGmpvMCGAu8/8r019/n+23hhIH0F9Z0FVQCmUSh7g==\n"
"-----END ASU CERTIFICATE-----\n"
"-----BEGIN USER CERTIFICATE-----\n"
"MIIBfjCCATKgAwIBAgIEIQAABDAMBggqgRzXYwEBAQUAMFQxFDASBgoJkiaJk/Is\n"
"ZAEZFgRXQVBJMQswCQYDVQQGEwJDTjENMAsGA1UEChMEMDAwMzEOMAwGA1UECxMF\n"
"QlJPTUUxEDAOBgNVBAMUB1dBUElfQVMwHhcNNzAwMTAxMDAxNzA0WhcNODAwMTAy\n"
"MDAxNzA0WjBVMRQwEgYKCZImiZPyLGQBGRYEV0FQSTELMAkGA1UEBhMCQ04xDTAL\n"
"BgNVBAoTBDAwMDMxDjAMBgNVBAsTBUJST01FMREwDwYDVQQDFAhBSUNAQVNVRTBK\n"
"MBQGByqGSM49AgEGCSqBHNdjAQECAQMyAAST3krxGExOcRKMZsUgY2dDQiGiaYXs\n"
"DYWg0NLg7LQbNeKffgOTNoOOmzKvLV5WzNUwDAYIKoEc12MBAQEFAAM4ADA1Ahh+\n"
"swb0hzMGHbDN0Bw+zDSSAeJgfZ8lp5oCGQCkC0pnJT48yjcIMHqBC3dMt7BbfhI1\n"
"YBY=\n"
"-----END USER CERTIFICATE-----\n"
"-----BEGIN EC PRIVATE KEY-----\n"
"MGACAQEEGEE4axpFnQUljqPIeK6qnxO7r8yy/mw+s6ALBgkqgRzXYwEBAgGhNAMy\n"
"AAST3krxGExOcRKMZsUgY2dDQiGiaYXsDYWg0NLg7LQbNeKffgOTNoOOmzKvLV5W\n"
"zNU=\n"
"-----END EC PRIVATE KEY-----\n";

int do_wapi_disconnect(int argc, char * const argv[])
{
    wlan_wapi_disconnect_sta(fhost_search_itf_idx(VIF_STA));

    return ERR_NONE;
}
#endif

int do_sta(int argc, char * const argv[])
{
    char sta_params[256] = {0};
    unsigned int idx = 0, j = 0;
    int fhost_vif_idx = fhost_search_first_valid_itf();
    struct fhost_vif_sta_cfg cfg;
    net_if_t *net_if = NULL;

    if ((argc < 1)) {
        dbg("Usage:\n  ap \n");
        return ERR_WRONG_ARGS;
    }

    j = 2;
    while(j <= argc) {
        memcpy(&(sta_params[idx]), argv[j - 1], strlen(argv[j - 1]));
        idx += strlen(argv[j - 1]);
        sta_params[idx] = ' ';
        idx ++;
        j++;
    }
    char *token, *next = sta_params;

    memset(&cfg, 0, sizeof(cfg));

    cfg.timeout_ms = 30000;
    while ((token = fhost_nw_next_token(&next)))
    {
        char option;

        if ((token[0] != '-') | (token[2] != '\0'))
            return ERR_WRONG_ARGS;

        option = token[1];
        token = fhost_nw_next_token(&next);
        if (!token)
            return ERR_WRONG_ARGS;

        switch(option)
        {
            #if 0
            case 'i':
            {
                cfg.fhost_vif_idx = fhost_search_itf(token);
                if (cfg.fhost_vif_idx < 0)
                    return FHOST_IPC_ERROR;
                break;
            }
            #endif
            case 's':
            {
                size_t ssid_len = strlen(token);
                if (ssid_len > sizeof(cfg.ssid.array))
                {
                    dbg("Invalid SSID\r\n");
                    return ERR_CMD_FAIL;
                }

                memcpy(cfg.ssid.array, token, ssid_len);
                cfg.ssid.array[ssid_len] = '\0';
                cfg.ssid.length = ssid_len;

                break;
            }
            case 'b':
            {
                if (fhost_nw_parse_mac_addr(token, &cfg.bssid))
                {
                    dbg("Invalid BSSID\r\n");
                    return ERR_CMD_FAIL;
                }
                break;
            }
            case 'k':
            {
                size_t key_len = strlen(token);
                if ((key_len + 1) > sizeof(cfg.key))
                {
                    dbg("Invalid Key\r\n");
                    return ERR_CMD_FAIL;
                }
                strcpy(cfg.key, token);
                break;
            }
            case 'f':
            {
                unsigned int i;
                char *next_freq = strchr(token, ',');
                for (i = 0 ; i <  CO_ARRAY_SIZE(cfg.freq); i++)
                {
                    cfg.freq[i] = atoi(token);
                    if (!next_freq)
                        break;
                    *next_freq++ = '\0';
                    token = next_freq;
                    next_freq = strchr(token, ',');
                }
                break;
            }
            case 'a':
            {
                char *next_akm;
                fhost_nw_upper(token, NULL);
                next_akm = strchr(token, ',');
                while (token)
                {
                    if (strncmp(token, "OPEN", 4) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_NONE);
                    }
                    else if (strncmp(token, "WEP", 3) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_NONE);
                    }
                    else if (strncmp(token, "PSK", 3) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_PSK);
                    }
                    else if (strncmp(token, "SAE", 3) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_SAE);
                    }
                    else if (strncmp(token, "CERT", 4) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_WAPI_CERT);
                    }
                    else if (strncmp(token, "WAPIPSK", 7) == 0)
                    {
                        cfg.akm |= CO_BIT(MAC_AKM_WAPI_PSK);
                    }
                    else
                    {
                        dbg("The following AKM are supported [%s]:\n"
                                    "OPEN: For open AP\n"
                                    "WEP: For AP configured with WEP\n"
                                    "PSK: For AP configured with a password and WPA/WPA2\n"
                                    "SAE: For AP configured with a password and WPA3\n", token);
                        if (strncmp(token, "HELP", 4) == 0)
                            return ERR_NONE;
                        else
                            return ERR_CMD_FAIL;
                    }

                    token = next_akm;
                    if (token)
                    {
                        token++;
                        next_akm = strchr(token, ',');
                    }
                }
                break;
            }
            case 't':
            {
                cfg.timeout_ms = atoi(token);
                break;
            }
            default:
                return ERR_WRONG_ARGS;
        }
    }

    if (cfg.ssid.length == 0)
        return ERR_WRONG_ARGS;
    ipc_host_cntrl_start();

    sta_link = fhost_cntrl_cfgrwnx_link_open();
    if (sta_link == NULL) {
        dbg(D_ERR "Failed to open link with control task\n");
        ASSERT_ERR(0);
    }

    // Reset STA interface (this will end previous wpa_supplicant task)
    if (fhost_set_vif_type(sta_link, fhost_vif_idx, VIF_UNKNOWN, false) ||
        fhost_set_vif_type(sta_link, fhost_vif_idx, VIF_STA, false)) {
        dbg("[AIC] fhost_set_vif_type fail\r\n");
        return ERR_CMD_FAIL;
    }
    fhost_cntrl_cfgrwnx_link_close(sta_link);

    if (fhost_sta_cfg(fhost_vif_idx, &cfg)) {
        dbg("[AIC] fhost_sta_cfg fail\r\n");
        return ERR_CMD_FAIL;
    }
    // Get the first network interface (created by CNTRL task).
    net_if = net_if_find_from_wifi_idx(fhost_vif_idx);
    if (net_if == NULL) {
        dbg("[AIC] net_if_find_from_wifi_idx fail\r\n");
        return 1;
    }
    if(!net_if_is_up(net_if)) {
        dbg("[AIC] netif_is_down\r\n");
        return -1;
    }

    // Start DHCP client to retrieve ip address
    if (wlan_dhcp(net_if) < 0) {

        #ifdef CFG_WAPI
        if (cfg.akm & (CO_BIT(MAC_AKM_WAPI_PSK) | CO_BIT(MAC_AKM_WAPI_CERT)))
            wlan_wapi_disconnect_sta((uint8_t)fhost_vif_idx);
        else
        #else
            wlan_disconnect_sta((uint8_t)fhost_vif_idx);
        #endif
        dbg("[AIC] dhcp fail\r\n");
        return -1;
    }

    // Now that we got an IP address use this interface as default
    net_if_set_default(net_if);

    return ERR_NONE;
}
#if FHOST_CONSOLE_LOW_POWER_CASE
#ifdef CONFIG_RWNX_LWIP
extern void tcpip_task_stop(void);
extern void tcpip_task_start(void);
#endif /* CONFIG_RWNX_LWIP */
int do_set_deepsleep_param(int argc, char * const argv[])
{
    unsigned int listen_interval = console_cmd_strtoul(argv[1], NULL, 10);

    set_deepsleep_param(listen_interval, 1);

    return ERR_NONE;
}

#define WAKEUP_IO_B0
#define WAKEUP_IO_B1
#define WAKEUP_IO_B2
#define WAKEUP_IO_B3
#define WAKEUP_IO_B4
#define WAKEUP_IO_A

#define CONSOLE_DEEPSLEEP_IO0_INDEX  0
#define CONSOLE_DEEPSLEEP_IO1_INDEX  1
#define CONSOLE_DEEPSLEEP_IO2_INDEX  2
#define CONSOLE_DEEPSLEEP_IO3_INDEX  3
#define CONSOLE_DEEPSLEEP_IO4_INDEX  4

#define CONSOLE_DEEPSLEEP_IOA_INDEX  2

rtos_queue irq_evt_queue = NULL;
static uint8_t irq_evt_handled = 0;
void gpio_irq_test_handler(int event)
{
    if (0 == irq_evt_handled) {
        uint32_t event_edge = GPIOIRQ_CB_EVENT(event);
        dbg("GPIO irq_test_handler %d\n", event_edge);
        rtos_queue_write(irq_evt_queue, &event_edge, 0, true);
    }
    user_sleep_allow(0);
}

static RTOS_TASK_FCT(irq_gpio_task)
{
    uint32_t event_edge = 0;

    for (;;) {
        if (!rtos_queue_read(irq_evt_queue, &event_edge, -1, false)) {
            if (irq_evt_handled) {
                continue;
            }
            dbg("event_edge = %d\r\n", event_edge);

            #if !(PLF_AIC8800)
            #if (PLF_AIC8800M40)
            // clr gpio wakeup cfg
            #ifdef WAKEUP_IO_B0
            gpiob_force_pull_none_enable(CONSOLE_DEEPSLEEP_IO0_INDEX);
            gpiob_irq_deinit(CONSOLE_DEEPSLEEP_IO0_INDEX);
            user_sleep_wakesrc_set(WAKESRC_GPIOB, 0, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO0_INDEX));
            #endif /* WAKEUP_IO_B0 */
            #ifdef WAKEUP_IO_B1
            gpiob_force_pull_none_enable(CONSOLE_DEEPSLEEP_IO1_INDEX);
            gpiob_irq_deinit(CONSOLE_DEEPSLEEP_IO1_INDEX);
            user_sleep_wakesrc_set(WAKESRC_GPIOB, 0, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO1_INDEX));
            #endif /* WAKEUP_IO_B1 */
            #ifdef WAKEUP_IO_B2
            gpiob_force_pull_none_enable(CONSOLE_DEEPSLEEP_IO2_INDEX);
            gpiob_irq_deinit(CONSOLE_DEEPSLEEP_IO2_INDEX);
            user_sleep_wakesrc_set(WAKESRC_GPIOB, 0, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO2_INDEX));
            #endif /* WAKEUP_IO_B2 */
            #ifdef WAKEUP_IO_B3
            gpiob_force_pull_none_enable(CONSOLE_DEEPSLEEP_IO3_INDEX);
            gpiob_irq_deinit(CONSOLE_DEEPSLEEP_IO3_INDEX);
            user_sleep_wakesrc_set(WAKESRC_GPIOB, 0, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO3_INDEX));
            #endif /* WAKEUP_IO_B3 */
            #ifdef WAKEUP_IO_B4
            gpiob_force_pull_none_enable(CONSOLE_DEEPSLEEP_IO4_INDEX);
            gpiob_irq_deinit(CONSOLE_DEEPSLEEP_IO4_INDEX);
            user_sleep_wakesrc_set(WAKESRC_GPIOB, 0, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO4_INDEX));
            #endif /* WAKEUP_IO_B4 */
            #ifdef WAKEUP_IO_A
            gpioa_force_pull_none_enable(CONSOLE_DEEPSLEEP_IOA_INDEX);
            gpioa_irq_deinit(CONSOLE_DEEPSLEEP_IOA_INDEX);
            user_sleep_wakesrc_set(WAKESRC_GPIOA, 0, WAKEGPIO_ARG(WAKEGPIO_MUX_0, CONSOLE_DEEPSLEEP_IOA_INDEX));
            #endif /* WAKEUP_IO_A */
            #endif /* PLF_AIC8800M40 */

            #if (PLF_AIC8800MC)
            #ifdef WAKEUP_IO_A
            gpioa_force_pull_none_enable(CONSOLE_DEEPSLEEP_IOA_INDEX);
            gpioa_irq_deinit(CONSOLE_DEEPSLEEP_IOA_INDEX);
            user_sleep_wakesrc_set(WAKESRC_GPIOA, 0, WAKEGPIO_ARG(WAKEGPIO_MUX_0, CONSOLE_DEEPSLEEP_IOA_INDEX));
            #endif /* WAKEUP_IO_A */
            #ifdef WAKEUP_IO_B2
            gpiob_force_pull_none_enable(CONSOLE_DEEPSLEEP_IO2_INDEX);
            gpiob_irq_deinit(CONSOLE_DEEPSLEEP_IO2_INDEX);
            user_sleep_wakesrc_set(WAKESRC_GPIOB, 0, WAKEGPIO_ARG(WAKEGPIO_MUX_1, CONSOLE_DEEPSLEEP_IO2_INDEX));
            #endif /* WAKEUP_IO_B2 */
            #ifdef WAKEUP_IO_B3
            gpiob_force_pull_none_enable(CONSOLE_DEEPSLEEP_IO3_INDEX);
            gpiob_irq_deinit(CONSOLE_DEEPSLEEP_IO3_INDEX);
            user_sleep_wakesrc_set(WAKESRC_GPIOB, 0, WAKEGPIO_ARG(WAKEGPIO_MUX_2, CONSOLE_DEEPSLEEP_IO3_INDEX));
            #endif /* WAKEUP_IO_B3 */
            #endif /* PLF_AIC8800MC */
            irq_evt_handled = 1;
            #endif /* !PLF_AIC8800 */

            // if deepsleep before wifi connected, powerup wifi after wakeup
            if ((0 == wlan_connected) && (PM_LEVEL_DEEP_SLEEP == sleep_level_get())) {
                int wifi_state = wifi_fw_is_active();
                if (wifi_state == 0)
                {
                    tcpip_task_start();
                    #if PLF_MODULE_TEMP_COMP
                    temp_comp_init();
                    temp_comp_start();
                    #endif /* PLF_MODULE_TEMP_COMP */
                    wifi_fw_repower(); // this api can't be called in isr
                }
                else {
                    dbg("wifi_st=%d\n", wifi_state);
                }
            }
            sys_restart_timeouts();
            sleep_level_set(PM_LEVEL_ACTIVE); // this api can't be called in isr
        }
    }
}

int do_enter_hibernate(int argc, char * const argv[])
{
    uint32_t level = PM_LEVEL_HIBERNATE;

    if (argc > 1) {
        level = console_cmd_strtoul(argv[1], NULL, 10);
    }

    sleep_level_set(level);
    if (level > PM_LEVEL_LIGHT_SLEEP) {
        #if !(PLF_AIC8800)
        #if (PLF_AIC8800M40)
        #ifdef WAKEUP_IO_B0
        // gpiob0 as wake src
        // EDGE_RISE => analog_pull_down
        anareg1_gpiob_pull_up_int_clrb(CONSOLE_DEEPSLEEP_IO0_INDEX);
        anareg1_gpiob_pull_dn_int_setb(CONSOLE_DEEPSLEEP_IO0_INDEX);
        //gpiob_force_pull_up_enable(CONSOLE_DEEPSLEEP_IO0_INDEX);
        gpiob_irq_init(CONSOLE_DEEPSLEEP_IO0_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpio_irq_test_handler);
        user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO0_INDEX));
        #endif /* WAKEUP_IO_B0 */
        #ifdef WAKEUP_IO_B1
        // gpiob1 as wake src
        // EDGE_RISE => analog_pull_down
        anareg1_gpiob_pull_up_int_clrb(CONSOLE_DEEPSLEEP_IO1_INDEX);
        anareg1_gpiob_pull_dn_int_setb(CONSOLE_DEEPSLEEP_IO1_INDEX);
        //gpiob_force_pull_up_enable(CONSOLE_DEEPSLEEP_IO1_INDEX);
        gpiob_irq_init(CONSOLE_DEEPSLEEP_IO1_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpio_irq_test_handler);
        user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO1_INDEX));
        #endif /* WAKEUP_IO_B1 */
        #ifdef WAKEUP_IO_B2
        // gpiob2 as wake src
        gpiob_force_pull_dn_enable(CONSOLE_DEEPSLEEP_IO2_INDEX);
        gpiob_irq_init(CONSOLE_DEEPSLEEP_IO2_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpio_irq_test_handler);
        user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO2_INDEX));
        #endif /* WAKEUP_IO_B2 */
        #ifdef WAKEUP_IO_B3
        // gpiob3 as wake src
        gpiob_force_pull_dn_enable(CONSOLE_DEEPSLEEP_IO3_INDEX);
        gpiob_irq_init(CONSOLE_DEEPSLEEP_IO3_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpio_irq_test_handler);
        user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO3_INDEX));
        #endif /* WAKEUP_IO_B3 */
        #ifdef WAKEUP_IO_B4
        // gpiob4 as wake src
        gpiob_force_pull_dn_enable(CONSOLE_DEEPSLEEP_IO4_INDEX);
        gpiob_irq_init(CONSOLE_DEEPSLEEP_IO4_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpio_irq_test_handler);
        user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_NUM_MAX, CONSOLE_DEEPSLEEP_IO4_INDEX));
        #endif /* WAKEUP_IO_B4 */
        #ifdef WAKEUP_IO_A
        // gpioa0 as wake src
        gpioa_force_pull_dn_enable(CONSOLE_DEEPSLEEP_IOA_INDEX);
        gpioa_irq_init(CONSOLE_DEEPSLEEP_IOA_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpio_irq_test_handler);
        user_sleep_wakesrc_set(WAKESRC_GPIOA, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_0, CONSOLE_DEEPSLEEP_IOA_INDEX));
        #endif /* WAKEUP_IO_A */
        #endif /* PLF_AIC8800M40 */
        
        #if (PLF_AIC8800MC)
        #ifdef WAKEUP_IO_A
        gpioa_force_pull_dn_enable(CONSOLE_DEEPSLEEP_IOA_INDEX);
        gpioa_irq_init(CONSOLE_DEEPSLEEP_IOA_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpio_irq_test_handler);
        user_sleep_wakesrc_set(WAKESRC_GPIOA, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_0, CONSOLE_DEEPSLEEP_IOA_INDEX));
        #endif /* WAKEUP_IO_A */
        #ifdef WAKEUP_IO_B2
        gpiob_force_pull_dn_enable(CONSOLE_DEEPSLEEP_IO2_INDEX);
        gpiob_irq_init(CONSOLE_DEEPSLEEP_IO2_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpio_irq_test_handler);
        user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_1, CONSOLE_DEEPSLEEP_IO2_INDEX));
        #endif /* WAKEUP_IO_B2 */
        #ifdef WAKEUP_IO_B3
        gpiob_force_pull_dn_enable(CONSOLE_DEEPSLEEP_IO3_INDEX);
        gpiob_irq_init(CONSOLE_DEEPSLEEP_IO3_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpio_irq_test_handler);
        user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_2, CONSOLE_DEEPSLEEP_IO3_INDEX));
        #endif /* WAKEUP_IO_B3 */
        #endif /* PLF_AIC8800MC */
        irq_evt_handled = 0;
        #endif /* !PLF_AIC8800 */

        if (0 == wlan_connected) {
            tcpip_task_stop();
            #if PLF_MODULE_TEMP_COMP
            temp_comp_deinit();
            #endif /* PLF_MODULE_TEMP_COMP */
            wifi_disconnected_sleep_allow(1);
        }

        if (rtos_task_get_handle("IRQ task") != NULL) {
            dbg("IRQ task has exist.\n");
            user_sleep_allow(1);
            return ERR_NONE;
        }

        if (rtos_queue_create(sizeof(uint32_t), 10, &irq_evt_queue)){
            return -1;
        }

        if (rtos_task_create(irq_gpio_task, "IRQ task", TCPUDP_FIRST_TASK, 256, NULL,
                               RTOS_TASK_PRIORITY(4), NULL)) {
            return -1;
        }

        user_sleep_allow(1);
    } else {
        user_sleep_allow(0);
    }

    return ERR_NONE;
}

uint32_t server_port = 6800;
uint8_t  server_addr_str[16] = {0};
uint16_t packet_len = 100;
uint16_t periodic_s = 15;
uint8_t  tcp_connected = 0;

#define TCP_RECV_LIMIT 1460
static int sock = -1;
#if (PLF_AIC8800)
static co_timer *co_tcp_timer = NULL;
#else
TimerHandle_t tcp_timer = NULL;
#endif

#if (PLF_AIC8800)
PRIVATE_HOST_DECLARE(G3USER, int, sock);
PRIVATE_HOST_DECLARE(G3USER, short, packet_len);
PRIVATE_HOST_DECLARE(G3USER, int, server_port);
PRIVATE_HOST_ARRAY_DECLARE(G3USER, char, 16, server_addr_str);
PRIVATE_HOST_DECLARE(G3USER, co_timer *, co_tcp_timer);

static co_timer *co_wakeup_timer = NULL;
void co_timer_handler(void *cb_param)
{
    dbg("co_timer_handler\r\n");
    wifi_fw_repower();
    //user_sleep_allow(0);
    //pmic_chip_reboot(0xF);
    return ;
}
void gpiob_irq_test_handler(int event)
{
    //if (GPIOIRQ_CB_EVENT(event) == GPIOIRQ_EVENT_EDGE_BOTH) {
        wifi_fw_repower();
        user_sleep_allow(0);
        dbg("GPIOB irq_test_handler\n");
    //}
}

int do_enter_hibernate_without_network (int argc, char * const argv[])
{
    //set_heart_beat_thresh(heart_beat_thresh);
    sleep_level_set(PM_LEVEL_ULP_1);

    // Timer wakeup
    if (co_wakeup_timer == NULL) {
        co_timer_start(&co_wakeup_timer, (periodic_s * 1000), NULL, co_timer_handler, 0);
        co_wakeup_timer = NULL;
    }

    // GPIOB4 wakeup src
    gpiob_irq_init(4, GPIOIRQ_TYPE_EDGE_RISE, gpiob_irq_test_handler,0);
    gpiob_force_pull_dn_enable(4); // gpiob as wake src
    pmic_clock_set_for_gpiob();
    user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, 0);

    wifi_disconnected_sleep_allow(1);

    user_sleep_allow(1);

    return ERR_NONE;
}

/**
 * Save user data
 */
void user_data_save(void)
{
    if (-1 == sock) {
        return;
    }
    if (0 == lwip_sockets_data_save(sock, backup_sock)) {
        backup_sock = sock;
    }
    backup_packet_len  = packet_len;
    backup_server_port = server_port;
    memcpy(backup_server_addr_str, server_addr_str, 16);
}
#endif

void console_gpio_irq_handler(int event)
{
    user_sleep_allow(0);
    dbg("GPIO irq handler\n");
}

int do_gpio_wakeup(int argc, char * const argv[])
{
    int ret = 0;
    do {
        uint32_t gpio_grp, gpio_idx, gpio_arg;
        #if (!PLF_AIC8800)
        uint32_t gpio_mux = WAKEGPIO_MUX_0;
        #endif
        gpio_grp = (int)console_cmd_strtoul(argv[1], NULL, 10);
        if (gpio_grp > WAKESRC_GPIOB) {
            ret = -1;
            break;
        }
        gpio_idx = (int)console_cmd_strtoul(argv[2], NULL, 10);
        if ((gpio_grp == WAKESRC_GPIOA) && (gpio_idx >= GPIOA_IDX_MAX)) {
            ret = -2;
            break;
        }
        if ((gpio_grp == WAKESRC_GPIOB) && (gpio_idx >= GPIOB_IDX_MAX)) {
            ret = -3;
            break;
        }
        #if (PLF_AIC8800)
        gpio_arg = gpio_idx;
        #else
        if (argc > 3) {
            gpio_mux = (int)console_cmd_strtoul(argv[3], NULL, 10);
            if (gpio_mux >= WAKEGPIO_MUX_NUM_MAX) {
                ret = -4;
                break;
            }
        }
        gpio_arg = WAKEGPIO_ARG(gpio_mux, gpio_idx);
        #endif
        if (gpio_grp == WAKESRC_GPIOA) {
            gpioa_irq_init(gpio_idx, GPIOIRQ_TYPE_EDGE_RISE, gpio_irq_test_handler);
        } else if (gpio_grp == WAKESRC_GPIOB) {
            #if (PLF_AIC8800)
            gpiob_irq_init(gpio_idx, GPIOIRQ_TYPE_EDGE_RISE, gpio_irq_test_handler, 0);
            #else
            gpiob_irq_init(gpio_idx, GPIOIRQ_TYPE_EDGE_RISE, gpio_irq_test_handler);
            #if (PLF_AIC8800M40)
            // EDGE_RISE => analog_pull_down
            anareg1_gpiob_pull_up_int_clrb(gpio_idx);
            anareg1_gpiob_pull_dn_int_setb(gpio_idx);
            #endif
            #endif
        }
        user_sleep_wakesrc_set(gpio_grp, 1, gpio_arg);
    } while (0);
    return ret;
}

int do_gpiob2_wakeup(int argc, char * const argv[])
{
    uint32_t gpio_grp = WAKESRC_GPIOB;
    uint32_t gpio_idx = 2;
    #if (!PLF_AIC8800)
    uint32_t gpio_mux = WAKEGPIO_MUX_0;
    #endif
    uint32_t gpio_arg;
    #if (PLF_AIC8800)
    gpio_arg = gpio_idx;
    #else
    gpio_arg = WAKEGPIO_ARG(gpio_mux, gpio_idx);
    #endif
    #if (PLF_AIC8800)
    gpiob_irq_init(gpio_idx, GPIOIRQ_TYPE_EDGE_RISE, console_gpio_irq_handler, 0);
    #else
    gpiob_irq_init(gpio_idx, GPIOIRQ_TYPE_EDGE_RISE, console_gpio_irq_handler);
    #endif
    gpiob_force_pull_dn_enable(gpio_idx);
    user_sleep_wakesrc_set(gpio_grp, 1, gpio_arg);
    return 0;
}

static RTOS_TASK_FCT(tcp_recv_task)
{
    int32_t size = 0;
    #define RECV_LIMIT 1460
    uint8_t  recv_buf[RECV_LIMIT+1];

    while (1) {
        size = recv(sock, recv_buf, RECV_LIMIT, 0);
        if(size <= 0){
            close(sock);
            sock = -1;
            break;
        }
        recv_buf[size] = 0;
        dbg("Receive %d bytes, %s\r\n", size, recv_buf);
    }
    #if (PLF_AIC8800)
    if (co_tcp_timer) {
        co_timer_stop(co_tcp_timer);
        co_tcp_timer = NULL;
        #if (PLF_AIC8800)
        backup_co_tcp_timer = NULL;
        #endif
    }
    #else
    if (tcp_timer) {
        rtos_timer_stop(tcp_timer, 0);
        rtos_timer_delete(tcp_timer, 0);
        tcp_timer = NULL;
    }
    #endif
    user_sleep_allow(0);
    dbg("End tcp_recv_task\r\n");
    rtos_task_delete(NULL);
}

int create_client (uint8_t new)
{
    struct sockaddr_in sock_addr;
    uint32_t svr_addr = 0;
    int no_delay = 1;
    //uint32_t keep_alive = 1;
    //uint16_t svr_port = 0;
    //const char *svr_addr_str = "192.168.3.26";

    if ((-1 != sock) || (!wlan_connected)) {
        return 0;
    }

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        dbg("open socket error: %d\r\n", sock);
        return -1;
    }
    if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const int *)&no_delay, sizeof(no_delay)) != 0) {
        dbg("setsockopt failed\n");
        close(sock);
        sock = -1;
        return -1;
    }

    if (new) {
        ipaddr_aton((const char *)server_addr_str, (ip_addr_t *)&svr_addr);
        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = svr_addr;
        sock_addr.sin_port = htons(server_port);
        if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0){
            dbg("socket connect error\r\n");
            return -1;
        }
        tcp_connected = 1;

        if(0 != rtos_task_create(tcp_recv_task, "TCP task", TCPUDP_FIRST_TASK,
                                 1024, NULL, RTOS_TASK_PRIORITY(1), NULL)) {
            return -1;
        }
    } else {
        #if (PLF_AIC8800)
        if (0 == lwip_sockets_data_restore(sock, backup_sock)) {
            tcp_connected = 1;

            if(0 != rtos_task_create(tcp_recv_task, "TCP task", TCPUDP_FIRST_TASK,
                                     1024, NULL, RTOS_TASK_PRIORITY(1), NULL)) {
                return -1;
            }
            return 0;
        } else {
            //TODO
        }
        #endif
    }

    return 0;
}
#if (PLF_AIC8800)
/**
 * Restore user data
 */
void user_data_restore(void)
{
    packet_len  = backup_packet_len;
    server_port = backup_server_port;
    memcpy(server_addr_str, backup_server_addr_str, 16);
    co_tcp_timer = backup_co_tcp_timer;

    // may receive tcp ack
    create_client(0);
}
#endif
static int tcp_send (void)
{
    unsigned int size = 0;
    unsigned char *buf;

    if (!wlan_connected) {
        return 0;
    }

    while (!net_if_is_up(&fhost_env.vif[0].net_if)){
        rtos_task_suspend(1);
    }

    if (!tcp_connected) {
        struct sockaddr_in sock_addr;
        uint32_t svr_addr = 0;
        dbg("%s %d\r\n", server_addr_str, server_port);
        ipaddr_aton((const char *)server_addr_str, (ip_addr_t *)&svr_addr);
        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = svr_addr;
        sock_addr.sin_port = htons(server_port);
        if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0){
            dbg("socket connect error\r\n");
            return -1;
        }
        tcp_connected = 1;
    }

    buf = (unsigned char *)rtos_malloc(packet_len);
    if(!buf) {
        return -1;
    }

    for(uint32_t i = 0; i < packet_len; i++) {
        buf[i] = (i & 0xFF);
    }

    dbg("###tcp_send\r\n");
    size = send(sock, buf, packet_len, 0);

    extern int errno;
    dbg("TCP send size %d %d errno %d\r\n", size, sock, errno);

    rtos_free(buf);
    buf= NULL;


    if(size == packet_len) {
        return 0;
    } else {
        close(sock);
        sock = -1;
        #if (PLF_AIC8800)
        if (co_tcp_timer) {
            co_timer_stop(co_tcp_timer);
            co_tcp_timer = NULL;
            #if (PLF_AIC8800)
            backup_co_tcp_timer = NULL;
            #endif
        }
        #else
        if (tcp_timer) {
            rtos_timer_stop(tcp_timer, 0);
            rtos_timer_delete(tcp_timer, 0);
            tcp_timer = NULL;
        }
        #endif
        return -1;
    }
}
extern void lwip_sockets_data_clear_unacked(void);
static void co_tcp_timer_handler(TimerHandle_t xTimer )
{
    dbg("co_tcp_timer_handler\r\n");
    sleep_prevent_set(SLEEP_PREVENT_TCP);
    #if (PLF_AIC8800)
    lwip_sockets_data_clear_unacked();
    #endif
    tcp_send();
    sleep_prevent_clr(SLEEP_PREVENT_TCP);
}

int fhost_console_tcpalive(char *params)
{
    char *token, *next = params;

    while ((token = fhost_nw_next_token(&next)))
    {
        if (token[0] != '-')
        {
            dbg("invalid option %s\n", token);
            return FHOST_NW_ERROR;
        }

        switch(token[1])
        {
            case ('s'): // Client mode with server host to connect to
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("missing host\n");
                    return FHOST_NW_ERROR;
                }

                memcpy(server_addr_str, token, strlen(token));

                /*if (fhost_nw_parse_ip4(token, &iperf_settings.host_ip, NULL))
                {
                    dbg("iperf: invalid host IP\n");
                    return FHOST_NW_ERROR;
                }*/
                break;
            }
            case ('l'): //Length of each buffer
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("missing buffer length\n");
                    return FHOST_NW_ERROR;
                }

                packet_len = atoi( token );
                break;
            }
            case ('p'): //server port
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg("missing server port\n");
                    return FHOST_NW_ERROR;
                }
                server_port = atoi( token );
                break;
            }
            case ('t'): // time mode (instead of amount mode)
            {
                if (!(token = fhost_nw_next_token(&next)))
                {
                    dbg(" missing time\n");
                    return FHOST_NW_ERROR;
                }

                periodic_s = atoi(token);
                break;
            }
            case ('h'): // Long Help
            {
                //uart_puts(iperf_long_help);
                return FHOST_NW_SUCCESS;
            }
            default: // Short Help
            {
                //dbg(iperf_short_help);
                return FHOST_NW_SUCCESS;
            }
        }
    };

    //create tcp connection
    create_client(1);
    tcp_send();

    // create co main timer
    #if (PLF_AIC8800)
    if (co_tcp_timer == NULL) {
        co_timer_start(&co_tcp_timer, (periodic_s * 1000), NULL, co_tcp_timer_handler, 1);
        #if (PLF_AIC8800)
        backup_co_tcp_timer = co_tcp_timer;
        #endif
    }
    #else
    if (tcp_timer == NULL) {
        int ret;
        tcp_timer = rtos_timer_create("tcp_timer", (periodic_s * 1000), pdTRUE, NULL, co_tcp_timer_handler);
        ret = rtos_timer_start(tcp_timer, 0, false);
        if (ret) {
            dbg("start timer failed: %d\n", ret);
        }
    }
    #endif

    return FHOST_NW_SUCCESS;
}
static int do_tcpalive (int argc, char * const argv[])
{
    char tcp_params[128] = {0};
    unsigned int idx = 0, j = 0;

    if ((argc < 1)) {
        dbg ("Usage:\n  iperf <-s|-c|-h> [options]\n");
        return 1;
    }

    if (!netif_is_up(net_if_find_from_wifi_idx(fhost_vif_idx)))  {
        dbg ("Usage:\n Connect AP first\n");
        return 1;
    }

    memcpy(&(tcp_params[idx]), argv[1], strlen(argv[1]));
    idx += strlen(argv[1]);

    j = 3;
    while(j <= argc) {
        tcp_params[idx] = ' ';
        idx ++;
        memcpy(&(tcp_params[idx]), argv[j - 1], strlen(argv[j - 1]));
        idx += strlen(argv[j - 1]);
        j++;
    }

    fhost_console_tcpalive(tcp_params);

    return 0;
}

#if !(PLF_AIC8800)
#include "sys/socket.h"
#include "lwip/sys.h"

#define SOCK_TARGET_HOST  "192.168.1.100"
#define SOCK_TARGET_PORT  8080
static int sock_tcp_wakeup = -1;
static uint8_t sock_buff[] = "AIC send data pkg in sleep mode..\n";
static void sock_timer_handler(TimerHandle_t xTimer)
{
    //dbg("co_sock_timer_handler\r\n");
    write(sock_tcp_wakeup, sock_buff, sizeof(sock_buff));
    return ;
}

/* This is a simple case about using special pkg to wakeup socket connect. */
static RTOS_TASK_FCT(tcp_wakeup_task)
{
    int     ret;
    int     opts;
    fd_set  readfds;
    fd_set  errofds;
    struct sockaddr_in addr;
    struct timeval    timeo;
    TimerHandle_t sock_timer = NULL;

    /* set up address to connect to */
    memset(&addr, 0, sizeof(addr));
    addr.sin_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SOCK_TARGET_PORT);
    addr.sin_addr.s_addr = inet_addr(SOCK_TARGET_HOST);

    /* connect */
    do {
        sock_tcp_wakeup = socket(AF_INET, SOCK_STREAM, 0);
        LWIP_ASSERT("sock >= 0", sock_tcp_wakeup >= 0);
        ret = connect(sock_tcp_wakeup, (struct sockaddr*)&addr, sizeof(addr));
        dbg("socket connect result [%d]\n", ret);
        if(ret != 0) {
            closesocket(sock_tcp_wakeup);
            return ;
        }
    } while (ret != 0);

    opts = fcntl(sock_tcp_wakeup, F_GETFL, 0);
    if(opts < 0) {
        dbg("SET F_GETFL error\n");
        return ;
    }
    if(fcntl(sock_tcp_wakeup, F_SETFL, opts) < 0) {
        dbg("SET F_SETFL error\n");
        return ;
    }

    sock_timer = rtos_timer_create("tcp_wakeup_timer", (5 * 1000), pdTRUE, NULL, sock_timer_handler);
    ret = rtos_timer_start(sock_timer, 0, false);
    if (ret) {
        dbg("start timer failed: %d\n", ret);
        closesocket(sock_tcp_wakeup);
        return ;
    }

    while(1) {
        FD_ZERO(&readfds);
        FD_SET(sock_tcp_wakeup, &readfds);
        FD_ZERO(&errofds);
        FD_SET(sock_tcp_wakeup, &errofds);

        timeo.tv_sec = 60;
        timeo.tv_usec = 0;
        //ret = select(sock + 1, &readfds, &writfds, &errofds, &timeo);
        ret = select(sock_tcp_wakeup + 1, &readfds, NULL, &errofds, &timeo);
        //dbg("select ret: %d\n", ret);

        if (ret == 0) {
            continue;
        } else if (ret < 0){
            dbg("Select err.. Exit %d\n", ret);
            break;
        } else {
            //
        }

        if (FD_ISSET(sock_tcp_wakeup, &errofds)) {
            dbg("Connect err.. Exit\n");
            break;
        }
        if (FD_ISSET(sock_tcp_wakeup, &readfds)) {
            dbg("FD_READ:\n");
            char buf[256];
            memset(buf, 0, sizeof(buf));
            ret = recv(sock_tcp_wakeup, buf, sizeof(buf), 0);
            if(ret <= 0){
               dbg("Recv err.. Exit\n");
                break;
            }
            dbg("GET data: %s\n", buf);

            if (strncmp(buf, "wakeup", strlen("wakeup")) == 0) {
                if (PM_LEVEL_ACTIVE != sleep_level_get()) {
                    sleep_level_set(PM_LEVEL_ACTIVE);
                    user_sleep_allow(0);
                    dbg("wake up, exit sleep\n");
                }
                break;
            }
        }
    }
    closesocket(sock_tcp_wakeup);
    ret = rtos_timer_stop(sock_timer, 0);
    if (ret) {
        dbg("stop timer failed: %d\n", ret);
    }
    rtos_timer_delete(sock_timer, 0);

    dbg("Exit tcp_wakeup_task.\n");
    rtos_task_delete(NULL);
    return ;
}

static int do_tcp_client_wakeup(int argc, char * const argv[])
{
    if (rtos_task_create(tcp_wakeup_task, "tcp_wakeup", TCP_WAKEUP_TASK,
        1024, NULL, RTOS_TASK_PRIORITY(1), NULL)) {
        return 1;
    }
    return 0;
}


#define SLEEP_WAKEUP_TIME 20
static uint32_t timer_cnt = 0;
static TimerHandle_t sleeptimer = NULL;
rtos_queue sleep_wakeup_timer_queue = NULL;

static void enter_sleep(void)
{
    dbg("enter sleep...\n");
    sleep_level_set(PM_LEVEL_DEEP_SLEEP);
    user_sleep_allow(1);
}
static void exit_sleep(void)
{
    user_sleep_allow(0);
    sleep_level_set(PM_LEVEL_ACTIVE);
    dbg("exit sleep...\n");
}

static void sleep_timer_handler(TimerHandle_t xTimer)
{
    int ret = rtos_queue_write(sleep_wakeup_timer_queue, &timer_cnt, 0, true);
    if (ret) {
        dbg("error: queue is full\n");
    }
    dbg("sleep-timer: %d\n", timer_cnt);
    timer_cnt++;
}

static RTOS_TASK_FCT(sleep_wakeup_task)
{
    int ret = 0, sign = 0;
    uint32_t time_cnt = 0;
    // DTIM 10. It`s necessary to set DTIM before connecting AP.
    set_deepsleep_param(10, 1);

    // Connect AP.
    char *ssid = "AP-ssid";
    char *pw = "AP-password";
    uint32_t timeout = 10000;
    ret = wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, timeout);
    if (ret) {
        dbg("Connect AP fail.\n");
        goto exit;
    }

    // create rtos timer
    sleeptimer = rtos_timer_create("sleep_wakeup_timer", (10 * 1000), pdTRUE, NULL, sleep_timer_handler);
    ret = rtos_timer_start(sleeptimer, 0, false);
    if (ret) {
        dbg("start timer failed: %d\n", ret);
        goto exit;
    }

    while(1) {
        if (!rtos_queue_read(sleep_wakeup_timer_queue, &time_cnt, -1, false)) {
            sign = time_cnt % 5;
            switch(sign) {
                case 1:
                    enter_sleep();
                    break;
                case 2:
                    dbg("In task2\n");
                    break;
                case 3:
                    dbg("In task3\n");
                    break;
                case 4:
                    // If use rtos_task_suspend, the timer will in disorder. Suggest prevent it before suspend.
                    // If have some important task to execute, you can prevent it first.
                    dbg("rtos suspend start.\n");
                    // PAY ATTENTION !!!
                    // SLEEP_PREVENT_TCP CANNOT UES FORMALLY.
                    // You need to define your enumeration value. This is a example only.
                    // This setting will prevent sleep.
                    sleep_prevent_set(SLEEP_PREVENT_TCP);
                    rtos_task_suspend(8000);
                    dbg("rtos suspend stop.\n");
                    // Wait dbg(uart0) finish print.
                    uart_wait_tx_done();
                    // This will clear prevent setting.
                    sleep_prevent_clr(SLEEP_PREVENT_TCP);
                    break;
                case 5:
                    exit_sleep();
                    break;
                default:
                    dbg("default situation %d\n", sign);
            }

            if (time_cnt == SLEEP_WAKEUP_TIME) {
                if (sleep_level_get() != PM_LEVEL_ACTIVE) {
                    user_sleep_allow(0);
                    sleep_level_set(PM_LEVEL_ACTIVE);
                    break;
                }
            }
        }
    }

    // Disconnect AP.
    wlan_disconnect_sta(0);

    ret = rtos_timer_stop(sleeptimer, 0);
    if (ret) {
        dbg("stop timer failed: %d\n", ret);
    }
    rtos_timer_delete(sleeptimer, 0);

exit:
    dbg("Exit sleep_wakeup_task.\n");
    rtos_queue_delete(sleep_wakeup_timer_queue);
    rtos_task_delete(NULL);
    return ;
}

static int do_timer_sleep_wakeup(int argc, char * const argv[])
{
    if (rtos_queue_create(sizeof(uint32_t), 10, &sleep_wakeup_timer_queue)){
        return -1;
    }
    if (rtos_task_create(sleep_wakeup_task, "sleep wakeup", SLEEP_WAKEUP_TASK,
                         512, NULL, RTOS_TASK_PRIORITY(1), NULL)) {
        return -1;
    }

    return 0;
}
#endif
#endif /* FHOST_CONSOLE_LOW_POWER_CASE */

#ifdef CFG_PRERELEASE_CODE
#include "fhost_console_prerelease.c"
#endif

#if FHOST_CONSOLE_MQTT_CASE
#include "mqttclient.h"

#ifndef MQTT_NETWORK_TYPE_NO_TLS
// 1. ca-cert.pem
const char *ca_cert = {
    "-----BEGIN CERTIFICATE-----\r\n"
    "MIIDjjCCAnagAwIBAgIUfyIdRmZdJuGmZ21iUpRU0domIc8wDQYJKoZIhvcNAQEL\r\n"
    "BQAwXzELMAkGA1UEBhMCQ04xEDAOBgNVBAgTB0JlaUppbmcxEDAOBgNVBAcTB0Jl\r\n"
    "aUppbmcxDTALBgNVBAoTBE8tQ0ExDjAMBgNVBAsTBU9VLUNBMQ0wCwYDVQQDEwRl\r\n"
    "bXF4MB4XDTIzMTEwMTExMzgwMFoXDTMzMTAyOTExMzgwMFowXzELMAkGA1UEBhMC\r\n"
    "Q04xEDAOBgNVBAgTB0JlaUppbmcxEDAOBgNVBAcTB0JlaUppbmcxDTALBgNVBAoT\r\n"
    "BE8tQ0ExDjAMBgNVBAsTBU9VLUNBMQ0wCwYDVQQDEwRlbXF4MIIBIjANBgkqhkiG\r\n"
    "9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvMbqwc4q2zayDwccVzH8JVAJDyiK+1YmP2AV\r\n"
    "mfkPC2LabYkhUFHnXkTogqEjxNdCZpbD+iV+2o4ka02JwZBGfWpqGMO//NiZ19cK\r\n"
    "oXYiXlXCi9jFAN2qGRT9hcLYBeZjrOVAFL314+swy5asJcT6CFUR9qkGYUuck4rx\r\n"
    "JLlMBdn5PKguEPiK/mxElwyuPVrWM0xUjYhzapUUgBEmvszlVUorsnQUw++24qGV\r\n"
    "Wd68PDdl99BIQ0o1LWa8MZW6kQXKGs79H5YOWl1VUF8q4/S3BX053jZhOQLd4hgV\r\n"
    "dTTt7DDc4713NEUMlianL54KyrtVDYYXaFFYR3sKo07XNagauQIDAQABo0IwQDAO\r\n"
    "BgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUY47qyE+v\r\n"
    "7utlcyCJN/CH90BiZhMwDQYJKoZIhvcNAQELBQADggEBADSPIJ+Qb6lT14FuvzU3\r\n"
    "4oviwCXTlZNi1qNnQ2AGN/oiJlKQ3NR6pM/XIfP/Wi138W1zR2GUhRQ0B1ABIcLK\r\n"
    "q/s/Jtrpr2Z4Aye7fUeQvxPfrEQzk2WD0Qx/IS8mV+2b7BupbpMWkoVE9tsf7Mz+\r\n"
    "Z7nNj3ocCvGjhh65pdnZx0/zIP7w/QNnyJwXce0begP4Gh6xtxavKd/QVYmfRUru\r\n"
    "JkssL6eTPHFXfXYR/QRfnMwVIjQTfQhUpccTafIrhxMZnHStpPv2kfWvLjqyjKzH\r\n"
    "nbi4+6RfBgW7dSLfELPB2CgoSo3Y0bgFn/vAlE+MwTNpM6YOesDiMvuXkBCyFc7T\r\n"
    "0Vk=\r\n"
    "-----END CERTIFICATE-----\r\n"
};

#ifdef MQTT_NETWORK_TYPE_TLS_TWO_WAY
// 2. client-cert.pem
const char *client_cert = {
    "-----BEGIN CERTIFICATE-----\r\n"
    "MIID3zCCAsegAwIBAgIUJtjFl0wd9bacRuIryf12Gp1JhdUwDQYJKoZIhvcNAQEL\r\n"
    "BQAwXzELMAkGA1UEBhMCQ04xEDAOBgNVBAgTB0JlaUppbmcxEDAOBgNVBAcTB0Jl\r\n"
    "aUppbmcxDTALBgNVBAoTBE8tQ0ExDjAMBgNVBAsTBU9VLUNBMQ0wCwYDVQQDEwRl\r\n"
    "bXF4MB4XDTIzMTEwMTExMzkwMFoXDTMzMTAyOTExMzkwMFowYzELMAkGA1UEBhMC\r\n"
    "Q04xEDAOBgNVBAgTB0JlaUppbmcxEDAOBgNVBAcTB0JlaUppbmcxDTALBgNVBAoT\r\n"
    "BE8tQ0ExDjAMBgNVBAsTBU9VLUNBMREwDwYDVQQDEwhlbXF4LXNlcjCCASIwDQYJ\r\n"
    "KoZIhvcNAQEBBQADggEPADCCAQoCggEBANp1IE4OvzD71wv1SntRJ0auz2+vpW3v\r\n"
    "0tQomVr3qKkV7pFNK1OWUf0DiXtWNJXRXcqfsWi6RJHVNDLzG/jmpBF5MaW4EsZc\r\n"
    "g3sHtOln5XdV2fGwZgkowqRCjs5UN5AZ3u2hi8m4joR8CA8TDuW3gz1wFMdb/v4s\r\n"
    "jAgEnfVryNLaYVwpyEbXmR8GsKt/x9LlOZHRCOlG1copDcuPCMDK4z0q0K+yngBc\r\n"
    "l8y7kafLBIYQ3mfYwZgoqoogSLpUSKQ9XNN6EEKw/hZ6CqHSWB/3C5tKcfOs/9zl\r\n"
    "Ub0e7LEJKAmJBY1ed/FGfTg+HqzkUhyLlQ51e96Mj3hcnwuy0CIBhaUCAwEAAaOB\r\n"
    "jjCBizAOBgNVHQ8BAf8EBAMCBaAwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUF\r\n"
    "BwMCMAwGA1UdEwEB/wQCMAAwHQYDVR0OBBYEFGLN7S8azRReq5E5ATEMch34Zh1G\r\n"
    "MB8GA1UdIwQYMBaAFGOO6shPr+7rZXMgiTfwh/dAYmYTMAwGA1UdEQQFMAOGASow\r\n"
    "DQYJKoZIhvcNAQELBQADggEBABzKAB9+AK0iczsFFUPNKrPQw+ffjVxN7AQ3zse4\r\n"
    "MASjo9VnRd7F83VIU9Fr8TmgBt8C5akCy9Uc1ZWYDBJi5UzxWfZ0AE0pN1ijzmF8\r\n"
    "W5nxCJT4hNuAMUrjTp0BVB7jMF0cfW/L2QKoV7m1IMgE4kJ3Xsm26nxOiBE97jra\r\n"
    "I4rCo/iHMWpO8Rs8JDq4E6y91emmD4QCUxsYQrZ4tTM3W3CJgbuM4jMUEbFcXSQc\r\n"
    "IVAnLKbJ9axBRIwVw+dWnCENfgXvZyM7O95LAH3crTA/NGgJIhaWslsYaXeAfUSY\r\n"
    "XnvQRGWaPJUfGvYQtgbcp8nd0Zru3pVuF6UpCz0k4d7hmRY=\r\n"
    "-----END CERTIFICATE-----\r\n"
};

// 3. client-key.pem
const char *client_key = {
    "-----BEGIN RSA PRIVATE KEY-----\r\n"
    "MIIEogIBAAKCAQEA2nUgTg6/MPvXC/VKe1EnRq7Pb6+lbe/S1CiZWveoqRXukU0r\r\n"
    "U5ZR/QOJe1Y0ldFdyp+xaLpEkdU0MvMb+OakEXkxpbgSxlyDewe06Wfld1XZ8bBm\r\n"
    "CSjCpEKOzlQ3kBne7aGLybiOhHwIDxMO5beDPXAUx1v+/iyMCASd9WvI0tphXCnI\r\n"
    "RteZHwawq3/H0uU5kdEI6UbVyikNy48IwMrjPSrQr7KeAFyXzLuRp8sEhhDeZ9jB\r\n"
    "mCiqiiBIulRIpD1c03oQQrD+FnoKodJYH/cLm0px86z/3OVRvR7ssQkoCYkFjV53\r\n"
    "8UZ9OD4erORSHIuVDnV73oyPeFyfC7LQIgGFpQIDAQABAoIBAEHImXTH/gzrGWPR\r\n"
    "dp9R3cjsJS0VsHQ9jrgyjZOWFmTsZM2+djiSgJf3M7Q/TlB7HopAsnS9+p4LnM9m\r\n"
    "49p84ZUdcLTdjFHNVA59UJ4kmjXoVVvxaZiCfLJoFIbPV3f+QmI+jlCtUcVVcDvR\r\n"
    "2l+UdmHO2YL7EftKQNS9Ry+7SFsttyvu6Ih4F40rqFZN8lHlgM8QLe0JfebLWGWO\r\n"
    "zVjR1JGAQwdPocbCOL72vIYXp0Jd+EZPfXwJUOt9MyYmY8sf6mz716yc8AuqjbjM\r\n"
    "GRPFE0FaDLTQxjEqnuGo/JFzWXRLHR1AgFylCrrVruilzkx1J+pJvB7kAvmXZYRN\r\n"
    "CK1bARUCgYEA4q/rj69NmSDcfYb0m/HUnylHyoj723NPj6fHVj01aovdLCoqIYPc\r\n"
    "3fsSe6TwbxR7MbabZm2Nam2ygCOdNHGoJovL1V3Q5t78visqgUXM1pzLSoINYrFi\r\n"
    "gjzNZ4LLM07BkN1uA92T+EvH7vmiIbTXJ1HKMHqiEMpWVqVWjhuajCsCgYEA9rTH\r\n"
    "CtkkiJ9JK4dcFp7LOGyl+fxQLi8js85A/6L/3JxUeNMsmvcVTEuGZ+RQ1LG9l/xP\r\n"
    "nDasQdNr65hk/lv3iB7yBoichkzSBqTxDd4ei4LRoOa6NMk5ufOJTy+ePAcV1u53\r\n"
    "/RWCFyGddJ2SwhNrrXL3qug25qQ9KlkR7ekJvW8CgYAEBdEtVJQQ8pdXFu0CU3FN\r\n"
    "fcMLYhDuHQa9auHLsvxerqq3HOxwedGSkuEKFqw5nGhvQmlRkQIgcF/pjDg+9QFh\r\n"
    "5bsxRx/s6OodSdDQSHfRGyk0YkhwhutTmlaezqBigbRHqNZJ9UWp81ZR9FYfOQFU\r\n"
    "bkwjPhngKGcN1JNLpEvCzwKBgA7/TlpKeP4VMM2EnQSDArebYzufKwCjvPfhQfJI\r\n"
    "ZmVy22+85qlE+/Z3YORP7NoBNBVZMT291RrrT1QzH3CXBqUvvGbJRzqi0OG2hTDi\r\n"
    "n9i7SyMM46Tx1qCHPYGi02uywpEeTg0EkbP2RywfqBxEMfeJVaT+GNhMg6tfXsen\r\n"
    "sv/hAoGAWw9ocR5HC0/ZQ7DITyaK2x52smpXndFb983IfCh7O8pyq6qiP9z/vJjs\r\n"
    "Vh/bSrhRbcK87NqBGP4Gg8pz2SXYBlzd2GSMCg+fyamHH5o0gXnKq1QwMdIlhY4G\r\n"
    "oUftGKNPShcYQ/4kouE6EQg5fSpNeDsj0l1oo1Ols4+HwemtMZY=\r\n"
    "-----END RSA PRIVATE KEY-----\r\n"
};
#endif /* MQTT_NETWORK_TYPE_TLS_TWO_WAY */
#endif /* MQTT_NETWORK_TYPE_NO_TLS */

static void topic1_handler(void* client, message_data_t* msg)
{
    (void) client;
    MQTT_LOG_I("-----------------------------------------------------------------------------------");
    MQTT_LOG_I("%s:%d %s()...\ntopic: %s\nmessage:%s",
                __FILE__, __LINE__, __FUNCTION__, msg->topic_name, (char*)msg->message->payload);
    MQTT_LOG_I("-----------------------------------------------------------------------------------");
}

mqtt_client_t *mqttclient;
static int do_setup_mqtt(int argc, char * const argv[])
{
    int ret = 0;
    mqtt_client_t *client = NULL;

    dbg("\n welcome to mqttclient test...\n");
    //mqtt_log_init();
    client = mqtt_lease();
    if(!client) {
        dbg("mqtt_lease fail.\n");
        return 0;
    }

    // View detailed descriptions and define in mqtt_config.h
    #ifndef MQTT_NETWORK_TYPE_NO_TLS
    // This port is for TLS.
    char *port = "8883";

    #ifdef MQTT_NETWORK_TYPE_TLS_TWO_WAY
    mqtt_set_client_cert(client, (char*)client_cert);
    mqtt_set_client_key(client, (char*)client_key);
    #endif /* MQTT_NETWORK_TYPE_TLS_TWO_WAY */
    mqtt_set_ca(client, (char*)ca_cert);

    #else /* MQTT_NETWORK_TYPE_NO_TLS */

    // This port is not TLS.
    char *port = "1883";
    #endif /* MQTT_NETWORK_TYPE_NO_TLS */

    char *ip = "192.168.124.5";
    char *sub_topic = "testtopic/1";
    dbg(" MQTT-IP: %s, port: %s\n", ip, port);
    mqtt_set_port(client, port);
    mqtt_set_host(client, ip);
    mqtt_set_client_id(client,"1044896071");
    mqtt_set_user_name(client, "571430");
    mqtt_set_password(client, "vzeOGJDEGDtE63sqoVm2CYIcGug=");
    mqtt_set_clean_session(client, 1);

    ret = mqtt_connect(client);
    if(ret) {
        dbg("mqtt_connect fail, ret: %d\n", ret);
        mqtt_release(client);
        return 0;
    }

    mqttclient = client;
    mqtt_subscribe(client, sub_topic, QOS0, NULL);
    mqtt_set_interceptor_handler(client, topic1_handler);     // set interceptor handler
    dbg(" Subscribe-topic: %s\n", sub_topic);
    rtos_task_suspend(2000);

    char buf[128];
    char *pub_topic = "testtopic/2";
    dbg_snprintf(buf, 128, "\"msg\": Hello 2023-12-29 AIC8800");

    mqtt_message_t msg;
    memset(&msg, 0, sizeof(msg));
    msg.qos = QOS1;
    msg.payload = (void *) buf;
    msg.payloadlen=strlen(buf);
    mqtt_publish(client, pub_topic, &msg);
    dbg(" Publish-topic: %s\n", pub_topic);
    dbg(" Publish-buff : %s\n", buf);

    rtos_task_suspend(2000);
    mqtt_publish(client, pub_topic, &msg);

    return ERR_NONE;
}

static int do_stop_mqtt(int argc, char * const argv[])
{
    // Make sure that mqtt client has started!
    mqtt_disconnect(mqttclient);
    mqtt_release(mqttclient);
    return ERR_NONE;
}
#endif /* FHOST_CONSOLE_MQTT_CASE */

#if defined(CFG_MODULE_WEBCLIENT)
#define GET_RESP_BUFSZ      1024
#define GET_HEADER_BUFSZ    1024

int webclient_ota_download(const char *uri)
{
    struct webclient_session* session = NULL;
    unsigned char* buffer = NULL;
    int index,ret = 0;
    int bytes_read,resp_status;
    int content_length = -1;
    uint32_t ota_addr;

    buffer = (unsigned char*)rtos_malloc(GET_RESP_BUFSZ);
    if (NULL == buffer) {
        dbg("no memory for receive buffer.\n");
        ret = -1;
        goto __exit;
    }

    //establish connection
    session = webclient_session_create(GET_HEADER_BUFSZ);
    if (NULL == session) {
        ret = -1;
        goto __exit;
    }

    /* build header for upload */
    webclient_header_fields_add(session, "Accept: text/xml,text/html,\r\n");

    //send GET request
    if ((resp_status = webclient_get(session, uri)) != 200 ) {
        dbg("webclient GET request failed, response(%d) error.\n", resp_status);
        ret = -1;
        goto __exit;
    }

    content_length = webclient_content_length_get(session);

    dbg("webclient get response data: content_length:%d\n", content_length);

    #ifndef CFG_LZMA_APP
    ota_addr = OTA_ADDR + OTA_INFO_SIZE;
    #else
    ota_addr = OTA_ADDR;
    #endif
    ota_start(ota_addr, content_length);

    if (content_length < 0) { /* chunked */
        dbg("webclient GET request type is chunked, aic not support chunked .\n");

        ret = -1;
        goto __exit;
    } else {
        int content_pos = 0;
        do {
            //TODO:
            bytes_read = webclient_read(session, (void *)buffer, content_length - content_pos > GET_RESP_BUFSZ ?
            GET_RESP_BUFSZ : content_length - content_pos);

            if (bytes_read  <= 0) {
                ret = -1;
                break;
            }
            //write data to flash
            ota_write(buffer, bytes_read);
            content_pos += bytes_read;
        } while (content_pos < content_length);
    }

    if (0 != ret) {
        dbg("request epoch time from remote server failed. \r\n");
    } else {
        dbg("sucess.\r\n");
        ota_end();
    }

    #ifndef CFG_LZMA_APP
    { // update image header
        struct image_header img_hdr = {0,};
        char *ver_str = "v0.1.1";
        int ver_len;
        unsigned int addr = OTA_ADDR;
        unsigned int size = content_length;
        img_hdr.magic   = IMAGE_HEADER_MAGIC;
        img_hdr.addr    = addr;
        img_hdr.size    = size;
        img_hdr.crc32   = flash_crc32((void *)addr, size);
        ver_len = strlen(ver_str) + 1;
        memcpy(img_hdr.version, ver_str, (ver_len < VER_BYTE_CNT) ? ver_len : VER_BYTE_CNT);
        flash_erase((void *)addr, IMAGE_INFO_SIZE);
        flash_write((void *)addr, sizeof(struct image_header), (char *)(&img_hdr));
        flash_cache_invalid_range((void *)addr, sizeof(struct image_header));
    }
    #endif

__exit:
    if (session) {
        rtos_free(session);
    }
    if (buffer) {
        rtos_free(buffer);
    }
    return ret;
}

static int do_webclient_ota(int argc, char * const argv[])
{
    webclient_ota_download(argv[1]);
    return ERR_NONE;
}

static int do_erase_upd(int argc, char * const argv[])
{
    int ret = 0;
    uint32_t addr = OTA_ADDR + OTA_INFO_SIZE;
    uint32_t img_len;
    uint32_t erase_len;
    struct image_header img_hdr = {0,};
    flash_read(OTA_ADDR, sizeof(struct image_header), &img_hdr);
    img_len = img_hdr.size;
    if (!img_len || (img_len > UPGRADE_IMAGE_MAX_SIZE)) {
        img_len = UPGRADE_IMAGE_MAX_SIZE;
    }
    erase_len = (img_len & 0xFFF) ? ((img_len + 0xFFF) & ~0xFFF) : img_len;
    do {
        uint32_t idx = 0;
        uint32_t len_64k = erase_len & ~0xFFFF;
        for (; idx < len_64k; idx += 0x10000) {
            ret = flash_erase((void*)(addr + idx), 0x10000);
            if (ret < 0) {
                dbg("er64k fail: %d\n", ret);
                break;
            }
            rtos_task_suspend(2);
        }
        if (ret < 0) {
            break;
        }
        for (; idx < erase_len; idx += 0x1000) {
            ret = flash_erase((void*)(addr + idx), 0x1000);
            if (ret < 0) {
                dbg("er4k fail: %d\n", ret);
                break;
            }
            rtos_task_suspend(2);
        }
        flash_cache_invalid_range((void *)addr, img_len);
    } while (0);
    return ERR_NONE;
}
#endif

int do_reboot(int argc, char * const argv[])
{
    pmic_chip_reboot(0xF);
    return 0;
}

#if defined(CFG_WIFI_TESTMODE)
static int do_enter_wifi_utm(int argc, char *argv[])
{
#if defined(CFG_AIC8800)
    PMIC_MEM_MASK_WRITE((unsigned int)0x50018c00, 0x00160000, 0xffffffff);
#endif
#if defined(CFG_AIC8800M40)
    PMIC_MEM_WRITE((unsigned int)&AIC_PMU_RTC0->rtc_rg_reserved0, 0x00160000);
#endif
#if defined(CFG_AIC8800MC)
    PMIC_MEM_WRITE((unsigned int)&AIC_PMU_RTC0->rtc_rg_reserved0, 0x00100000);
#endif
    pmic_chip_reboot(0xFF);
    return 0;
}
#endif

static int do_info(int argc, char * const argv[])
{
    int func = console_cmd_strtoul(argv[1], NULL, 10);
    if (func == 0) { // print cur info
        #if PLF_RSSI_DATAPKT
        int8_t rssi = data_pkt_rssi_get();
        dbg("DataRSSI=%d\n", rssi);
        #endif
        #if NX_BEACONING
        uint8_t ap_ch = get_ap_channel_num();
        dbg("ApChannel=%d\n", ap_ch);
        #endif
    }
    #if NX_BEACONING
    else if (func == 1) { // set ap chan
        if (argc > 2) {
            uint8_t ch = (uint8_t)console_cmd_strtoul(argv[2], NULL, 10);
            if (ch < 170) {
                set_ap_channel_num(ch);
                dbg("set ApChannel=%d\n", ch);
            } else {
                dbg("invalid chan_num: %d\n", ch);
            }
        } else {
            dbg("invalid args\n");
        }
    }
    #endif
    else {
        dbg("invalid func\n");
    }
    return 0;
}

static int do_agg_disable_cfg(int argc, char * const argv[])
{
    int ret = 0;
    uint8_t agg_tx_dis = console_cmd_strtoul(argv[1], NULL, 0);
    #if PLF_AIC8800MC || PLF_AIC8800M40 || defined(CFG_WIFI_RAM_VER)
    uint8_t agg_rx_dis = console_cmd_strtoul(argv[2], NULL, 0);
    #else
    uint8_t agg_rx_dis = 0; // no effect for non-CFG_WIFI_RAM_VER PLF_AIC8800
    #endif
    uint8_t sta_idx = 0xFF;
    if (argc > 3) {
        sta_idx = console_cmd_strtoul(argv[3], NULL, 0);
    }
    dbg("agg_disable: T%d, R%d, 0x%x\n", agg_tx_dis, agg_rx_dis, sta_idx);
    rwnx_set_disable_agg_req(agg_tx_dis, agg_rx_dis, sta_idx);
    return ret;
}

#if (PLF_AIC8800M40)
int do_hwconfig(int argc, char * const argv[])
{
    int ret = 0;
    uint32_t hwcfg_id = console_cmd_strtoul(argv[1], NULL, 10);
    if (hwcfg_id == ACS_TXOP_REQ) {
        if (argc == 6) {
            struct mm_set_acs_txop_req req;
            req.hwconfig_id = hwcfg_id;
            req.txop_bk = (uint16_t)console_cmd_strtoul(argv[2], NULL, 16);
            req.txop_be = (uint16_t)console_cmd_strtoul(argv[3], NULL, 16);
            req.txop_vi = (uint16_t)console_cmd_strtoul(argv[4], NULL, 16);
            req.txop_vo = (uint16_t)console_cmd_strtoul(argv[5], NULL, 16);
            ret = rwnx_send_vendor_hwconfig_req(&req);
        } else {
            dbg("invalid argc\n");
            ret = -2;
        }
    } else if (hwcfg_id == CHANNEL_ACCESS_REQ) {
        if (argc == 15) {
            struct mm_set_channel_access_req req;
            req.hwconfig_id = hwcfg_id;
            req.edca[0] = (uint32_t)console_cmd_strtoul(argv[2], NULL, 16);
            req.edca[1] = (uint32_t)console_cmd_strtoul(argv[3], NULL, 16);
            req.edca[2] = (uint32_t)console_cmd_strtoul(argv[4], NULL, 16);
            req.edca[3] = (uint32_t)console_cmd_strtoul(argv[5], NULL, 16);
            req.vif_idx     = (uint8_t)console_cmd_strtoul(argv[6], NULL, 10);
            req.retry_cnt   = (uint8_t)console_cmd_strtoul(argv[7], NULL, 10);
            req.rts_en      = (uint8_t)console_cmd_strtoul(argv[8], NULL, 10);
            req.long_nav_en = (uint8_t)console_cmd_strtoul(argv[9], NULL, 10);
            req.cfe_en      = (uint8_t)console_cmd_strtoul(argv[10], NULL, 10);
            req.rc_retry_cnt[0] = (uint8_t)console_cmd_strtoul(argv[11], NULL, 10);
            req.rc_retry_cnt[1] = (uint8_t)console_cmd_strtoul(argv[12], NULL, 10);
            req.rc_retry_cnt[2] = (uint8_t)console_cmd_strtoul(argv[13], NULL, 10);
            req.ccademod_th     =  (int8_t)console_cmd_strtoul(argv[14], NULL, 10);
            ret = rwnx_send_vendor_hwconfig_req(&req);
        } else {
            dbg("invalid argc\n");
            ret = -2;
        }
    } else if (hwcfg_id == MAC_TIMESCALE_REQ) {
        if (argc == 8) {
            struct mm_set_mac_timescale_req req;
            req.hwconfig_id = hwcfg_id;
            req.sifsA_time = (uint8_t)console_cmd_strtoul(argv[2], NULL, 10);
            req.sifsB_time = (uint8_t)console_cmd_strtoul(argv[3], NULL, 10);
            req.slot_time  = (uint8_t)console_cmd_strtoul(argv[4], NULL, 10);
            req.rx_startdelay_ofdm  = (uint8_t)console_cmd_strtoul(argv[5], NULL, 10);
            req.rx_startdelay_long  = (uint8_t)console_cmd_strtoul(argv[6], NULL, 10);
            req.rx_startdelay_short = (uint8_t)console_cmd_strtoul(argv[7], NULL, 10);
            ret = rwnx_send_vendor_hwconfig_req(&req);
        } else {
            dbg("invalid argc\n");
            ret = -2;
        }
    } else if (hwcfg_id == CCA_THRESHOLD_REQ) {
        if (argc == 7) {
            struct mm_set_cca_threshold_req req;
            req.hwconfig_id = hwcfg_id;
            req.auto_cca_en = (uint8_t)console_cmd_strtoul(argv[2], NULL, 10);
            req.cca20p_rise_th = (int8_t)console_cmd_strtoul(argv[3], NULL, 10);
            req.cca20s_rise_th = (int8_t)console_cmd_strtoul(argv[4], NULL, 10);
            req.cca20p_fall_th = (int8_t)console_cmd_strtoul(argv[5], NULL, 10);
            req.cca20s_fall_th = (int8_t)console_cmd_strtoul(argv[6], NULL, 10);
            ret = rwnx_send_vendor_hwconfig_req(&req);
        } else {
            dbg("invalid argc\n");
            ret = -2;
        }
    } else if (hwcfg_id == BWMODE_REQ) {
        if (argc == 3) {
            struct mm_set_bwmode_req req;
            req.hwconfig_id = hwcfg_id;
            req.bwmode = (uint8_t)console_cmd_strtoul(argv[2], NULL, 10);
            ret = rwnx_send_vendor_hwconfig_req(&req);
        } else {
            dbg("invalid argc\n");
            ret = -2;
        }
    } else if (hwcfg_id == CUSTOMIZED_FREQ_REQ) {
        if (argc == 10) {
            struct mm_set_customized_freq_req req;
            req.hwconfig_id = hwcfg_id;
            req.raw_freq[0] = (uint16_t)console_cmd_strtoul(argv[2], NULL, 10);
            req.raw_freq[1] = (uint16_t)console_cmd_strtoul(argv[3], NULL, 10);
            req.raw_freq[2] = (uint16_t)console_cmd_strtoul(argv[4], NULL, 10);
            req.raw_freq[3] = (uint16_t)console_cmd_strtoul(argv[5], NULL, 10);
            req.map_freq[0] = (uint16_t)console_cmd_strtoul(argv[6], NULL, 10);
            req.map_freq[1] = (uint16_t)console_cmd_strtoul(argv[7], NULL, 10);
            req.map_freq[2] = (uint16_t)console_cmd_strtoul(argv[8], NULL, 10);
            req.map_freq[3] = (uint16_t)console_cmd_strtoul(argv[9], NULL, 10);
            ret = rwnx_send_vendor_hwconfig_req(&req);
        } else {
            dbg("invalid argc\n");
            ret = -2;
        }
    } else {
        dbg("unsupported hwcfg_id: %d\n", hwcfg_id);
        ret = -1;
    }
    return ret;
}
#endif

static void fhost_command_add(void)
{
    RWNX_DBG(RWNX_FN_ENTRY_STR);
    console_cmd_add("reboot",   "Software Reboot",                  1, 1, do_reboot);

    console_cmd_add("heap",     "- Show heap info",                     1, 1, do_show_heap);
    #if (configUSE_TRACE_FACILITY == 1)
    console_cmd_add("task",     "- Show task info",                     1, 1, do_show_task);
    #endif
    console_cmd_add("slplvl",   "lvl - Set system sleep level",         2, 2, do_sleep_level);
    console_cmd_add("usrwusrc", "src en arg - Set user wakeup source",  3, 4, do_user_wakeup_source);
    console_cmd_add("usrslp",   "0/1 - Allow user sleep",               2, 2, do_user_sleep);
    #if NX_BEACONING
    console_cmd_add("startap", "band ssid <pwd>", 3, 4, do_start_ap);
    console_cmd_add("stopap", "- Stop AP", 1, 1, do_stop_ap);
    console_cmd_add("associnfo", " - ap associated sta info", 2, 2, do_ap_associated_sta_info);
    console_cmd_add("runap", "-s <SSID> -f <freq>[+-@] [-a <akm>[,<akm 2>]] [-k <key>] "
                         "[-b bcn_int[,dtim_period]] [-m <mfp: 0|1|2>] "
                         "[-u <unicast cipher>[,<unicast cipher 2>]] [-g <group cipher>] [-m <mfp: 0|1|2>] [-h hidden]", 1, 20, do_ap);
    #endif /* NX_BEACONING */
    console_cmd_add("runsta", "-s <SSID> [-k <key>] [-b <bssid>] "
                        "[-f <freq>[,freq]] [-a <akm>] [-t <timeout>]", 1, 20, do_sta);
    console_cmd_add("connect", "0/1 ssid <pwd>", 1, 4, do_connect);
    console_cmd_add("connect_cb", "- connect with callback", 1, 1, do_connect_cb);
    console_cmd_add("reconnect", "- sta auto reconnect ap", 1, 1, do_auto_reconnect);
    console_cmd_add("mac",     "?/[hex_str]",    2, 2, do_mac);
	console_cmd_add("blink_magic",     "?/[hex_str]",    2, 2, do_blink_magic);
    console_cmd_add("clrfi",   "- Clear Flash Info",  1, 1, do_restore);
    #if FHOST_CONSOLE_LOW_POWER_CASE
    #if (PLF_AIC8800)
    console_cmd_add("nonethib", "nonethib", 1, 2, do_enter_hibernate_without_network);
    #endif
    console_cmd_add("txpwr",    "- Set rf tx powers", 3, 3, do_set_power);
    console_cmd_add("setdsparam", "listen_interval", 2, 2, do_set_deepsleep_param);
    console_cmd_add("tcpalive", "<-s|-p|-l|-t|-h> [options]", 1, 50, do_tcpalive);
    #if !(PLF_AIC8800)
    console_cmd_add("tcpwakeup", "- Wakeup tcp client", 1, 1, do_tcp_client_wakeup);
    console_cmd_add("slpwu", "sleep and wakeup periodically", 1, 1, do_timer_sleep_wakeup);
    #endif
    console_cmd_add("hib", "slplvl", 1, 2, do_enter_hibernate);
    console_cmd_add("gpiowu", "grp idx <mux> - Set gpio wakeup source",  3, 4, do_gpio_wakeup);
    console_cmd_add("gpb2wu", "Set gpiob2 wakeup",  1, 1, do_gpiob2_wakeup);
    #endif /* FHOST_CONSOLE_LOW_POWER_CASE */
    #if NX_WPS
    console_cmd_add("wps", "- wps", 1, 1, do_wps_pbc);
    #endif /* NX_WPS */
    #if NX_P2P
    console_cmd_add("startp2p", "- p2p", 1, 1, do_start_p2p);
    #endif /* NX_P2P */
    console_cmd_add("disconnect", "- Disconnect Station", 1, 1, do_disconnect);
#ifdef CFG_WAPI
    console_cmd_add("wapidisconnect", "- WAPI Disconnect", 1, 1, do_wapi_disconnect);
#endif
    #if PLF_PING
    console_cmd_add("ping", "dst_ip|stop ID", 2, 20, do_ping);
    #endif /* PLF_PING */
    #if PLF_IPERF
    console_cmd_add("iperf", "<-s|-c|-h> [options]", 1, 20, do_iperf);
    #endif /* PLF_IPERF */

    console_cmd_add("scan", "fvif_idx", 2, 2, do_scan);
    console_cmd_add("super_scan", "fvif_idx", 2, 2, do_super_scan);
    console_cmd_add("status", "[chan|vif]", 1, 2, do_status);
    console_cmd_add("ip",   "show [itf]\n"
                            "   add <ip>/<mask> [gw] <itf>\n"
                            "   del <itf>", 2, 5, do_ip);
    console_cmd_add("wpa_cli", "[CMD]", 2, 2, do_wpa_cli);
    console_cmd_add("fixrate", "fvif_idx bw fmt rate_idx <gi_pre_type>", 5, 6, do_fixrate);
    #if NX_SMARTCONFIG
    console_cmd_add("smartconf",  "- Smart Config", 1, 1, do_smartconf);
    console_cmd_add("stopsc",  "- Stop Smart Config", 1, 1, do_stop_smartconf);
    #endif /* NX_SMARTCONFIG */
    #if FHOST_CONSOLE_MQTT_CASE
    console_cmd_add("mqtt", "setup mqtt", 1, 1, do_setup_mqtt);
    console_cmd_add("stopmqtt", "stop mqtt", 1, 1, do_stop_mqtt);
    #endif /* FHOST_CONSOLE_MQTT_CASE */
    #if defined(CFG_MODULE_WEBCLIENT)
    console_cmd_add("wcota", "web client ota", 2, 2, do_webclient_ota);
    console_cmd_add("erupd", "erase upd area", 1, 1, do_erase_upd);
    #endif
    #if defined(CFG_WIFI_TESTMODE)
    console_cmd_add("wutm",     " Enter wifi test mode",            1, 1, do_enter_wifi_utm);
    #endif
    console_cmd_add("info",     "0/1 <arg> - get/set info", 2, 3, do_info);
    console_cmd_add("aggdis",   "tx rx <idx> - agg disable", 3, 4, do_agg_disable_cfg);
    #if (PLF_AIC8800M40)
    console_cmd_add("hwcfg", "wifi hwconfig", 2, 15, do_hwconfig);
    #endif
    #ifdef CFG_PRERELEASE_CODE
    fhost_prerelease_command_add();
    #endif
}

/**
 ****************************************************************************************
 * @brief Request the RTOS to resume the console task.
 * This function sends a msg to console_queue to realize the resume.
 * Note that currently this function is supposed to be called from interrupt.
 *
 * @param[in] isr Indicates if called from ISR
 ****************************************************************************************
 */
static void fhost_console_resume(bool isr)
{
    int res;
    struct fhost_msg msg;

    msg.id   = FHOST_MSG_ID(FHOST_MSG_CONSOLE, 0);
    msg.len  = 0;
    msg.data = NULL;

    res = rtos_queue_write(console_queue, &msg, 0, isr);
    ASSERT_ERR(res == 0);
}

/**
 ****************************************************************************************
 * @brief console task implementation.
 ****************************************************************************************
 */
static RTOS_TASK_FCT(fhost_console_task)
{
    struct fhost_msg msg;

    for (;;) {
        rtos_queue_read(console_queue, &msg, -1, false);

        switch (FHOST_MSG_TYPE(msg.id)) {
        case FHOST_MSG_CONSOLE:
            console_schedule();
            break;
        default:
            break;
        }
    }
}

int fhost_application_init(void)
{
    RWNX_DBG(RWNX_FN_ENTRY_STR);

    // Initialize console
    console_init();

    // Create the console task
    if (rtos_task_create(fhost_console_task, "CONSOLE", APPLICATION_TASK,
                         1024, NULL, RTOS_TASK_PRIORITY(1), NULL)) {
        return 1;
    }

    if (rtos_queue_create(sizeof(struct fhost_msg), FHOST_CONSOLE_QUEUE_SIZE, &console_queue))
        return 2;

    console_ntf_register(fhost_console_resume);

    fhost_command_add();

    return 0;
}

