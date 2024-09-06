 /**
 *******************************************************************************
 *
 * @file fhost_example.c
 *
 * @brief Definition of an example application task for Fully Hosted firmware.
 *
 * Copyright (C) RivieraWaves 2019-2019
 *
 *******************************************************************************
 */

#include "fhost.h"
#include "netdb.h"
#include "fhost_config.h"
#include "fhost_cntrl.h"
#include "rwnx_msg_tx.h"
#include "wlan_if.h"
#include "sleep_api.h"
#include "sysctrl_api.h"
#include "system.h"
#include "console.h"

#define TEST_SOFTAP     0
#define TEST_CONNECT    0
#define TEST_SCAN       1
#define TEST_MONITOR   (0 && NX_FHOST_MONITOR)
#define TRACE_APP(...)  do {} while (0)
#define CONFIG_AUTO_PING    0

/**
 *******************************************************************************
 * @defgroup FHOST_EXAMPLE FHOST_EXAMPLE
 * @ingroup FHOST
 * @{
 *
 * This module contains code of an example application.\n
 * Each application needs to define a few mandatory functions:
 * - fhost_application_init: Called during firmware intialization to prepare
 *   the application task.\n
 *   In this example the function creates a single task.
 *
 * - fhost_config_get_next_item: Used by control task to retrieve runtime
 *   configuration of the wifi firmware.\n
 *   In this example the configuration is read from variable @ref example_config
 *
 * This example application is very basic:
 * - First it connect to an Access Point.
 *   Credentials/config of the AP are hardcoded in @ref example_ap_cfg.
 * - Then a DHCP procedure is started to retrieve an IP address.
 * - Finally it connects to a website (forismatic) to retrieve a random quote
 *
 *******************************************************************************
 */

#ifdef CFG_SOFTAP
extern int ps_sta_connected;
extern uint8_t is_ap;
#endif

#if (TEST_SCAN || TEST_MONITOR)
/// Link parameters
static struct fhost_cntrl_link *cntrl_link;

#endif /* TEST_SCAN */

/******************************************************************************
 * Application code:
 *****************************************************************************/

/**
 * Show system clocks
 */
int do_show_clocks(int argc, char * const argv[])
{
    #if (PLF_AIC8800)
    dbg("F:%dM,H:%dM,P:%dM,FL:%dM\n",
               DSPSysCoreClock/1000000,SystemCoreClock/1000000,PeripheralClock/1000000,sysctrl_clock_get(PER_FLASH)/1000000);
    #else
    dbg("H:%dM,P:%dM,PSR:%dM,FL:%dM\n",
        SystemCoreClock/1000000,PeripheralClock/1000000,FlashMem2XClock/1000000,sysctrl_clock_get(PER_FLASH)/1000000);
    #endif
    return 0;
}

#if TEST_CONNECT
/**
 ******************************************************************************
 * @brief Connect to forismatic website and retrieve a quote
 *
 * After resolving website address, a socket is created to send an http
 * request. The response is then parsed and the quote is displayed using
 * @ref dbg.
 * POSIX function are used for DNS and sockets.
 *
 * @note Since the application doesn't configured any DNS nor gateway it is
 * expected that the DHCP had provided such information.
 *
 * @note This function is provided just for the sake of having a complete
 * application example. The http request part shoul be considered as prototype
 * code.
 *
 * @return 0 on success and != 0 if error occured
 ******************************************************************************
 */
static int example_connect_website()
{
    char host[] = "api.forismatic.com";
    char query[] = "\
GET /api/1.0/?method=getQuote&format=text&lang=en HTTP/1.1\r\n\
Host: api.forismatic.com\r\n\
\r\n";
    char *resp_buf = NULL;
    char *resp_ptr;
    int resp_buf_len = 1024;
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    int sock = -1;
    int to_sent, sent, bytes, resp_len;

    resp_buf = rtos_malloc(resp_buf_len);
    if (!resp_buf)
        return -1;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_NUMERICSERV;

    if (getaddrinfo(host, "80", &hints, &res))
    {
        return -1;
    }
    else
    {
        // create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
            goto error;

        // and it to the host address
        if (connect(sock, res->ai_addr, res->ai_addrlen) < 0)
            goto error;

        freeaddrinfo(res);
        res = NULL;
    }

    // Send the query
    sent = 0;
    to_sent = strlen(query);
    while (to_sent > sent)
    {
        bytes = send(sock, &query[sent], to_sent - sent, 0);
        if (bytes < 0)
            goto error;
        sent += bytes;
    }

    // Receive the response
    bytes = recv(sock, resp_buf, resp_buf_len, 0);
    if (bytes < 0)
        goto error;
    resp_len = bytes;


    // Extract quote from the response
    resp_ptr = strstr(resp_buf, "\r\n");
    if (!resp_ptr)
    {
         goto invalid_response;
    }
    else if (strncmp(&resp_ptr[-2], "OK", 2))
    {
        resp_ptr[0] = '\0';
        TRACE_APP(ERR, "%s", TR_STR_8(resp_buf));
        goto invalid_response;
    }
    else
    {
        char *quote_len_str;
        int quote_len;
        resp_ptr = strstr(resp_buf, "\r\n\r\n");
        if (!resp_ptr)
            goto invalid_response;

        resp_ptr += 4;
        quote_len_str = resp_ptr;
        resp_ptr = strstr(resp_ptr, "\r\n");
        resp_ptr[0] = '\0';
        resp_ptr += 2;
        quote_len = strtol(quote_len_str, NULL, 16);

        // If quote is too long to fit in resp_buff, truncate it
        if (quote_len - 1> resp_buf_len)
            quote_len = resp_buf_len - 1;

        resp_len -= (resp_ptr - resp_buf);
        memmove(resp_buf, resp_ptr, resp_len);
        quote_len -= resp_len;

        if (quote_len > 0)
        {
            bytes = recv(sock, &resp_buf[resp_len], quote_len, MSG_DONTWAIT);
            if (bytes >= 0)
                resp_len += bytes;
        }
        resp_buf[resp_len] = '\0';

        TRACE_APP(INF, "quote received: %s", TR_STR_8(resp_buf));
        dbg("%s", resp_buf);
    }

  invalid_response:
    // flush socket
    while (bytes > 0)
        bytes = recv(sock, resp_buf, resp_buf_len, MSG_DONTWAIT);

    rtos_free(resp_buf);
    close(sock);
    return 0;

  error:
    TRACE_APP(ERR, "Connection to website failed");
    if (resp_buf)
        rtos_free(resp_buf);

    if (sock > 0)
        close(sock);

    if (res)
        freeaddrinfo(res);

    return -1;
}
#endif /* TEST_CONNECT */

#if (TEST_SCAN)
int time_interval = 2000; //ms
uint8_t chan_cnt_saved_2g4 = 0, chan_cnt_saved_5g = 0;
extern struct me_chan_config_req fhost_chan;

int do_set_scanparam(int argc, char * const argv[])
{
    int ret = 0;
    int band_type = (int)console_cmd_strtoul(argv[1], NULL, 10);
    int time_interv = (int)console_cmd_strtoul(argv[2], NULL, 10);
    time_interval = time_interv;
    if (band_type == 0) { // stop
    } else if (band_type == 1) { // 2.4g
        dbg("scan @ 2.4G band, interval=%d\n", time_interval);
        fhost_chan.chan2G4_cnt = chan_cnt_saved_2g4;
        fhost_chan.chan5G_cnt = 0;
    } else if (band_type == 2) { // 5g
        dbg("scan @ 5G band, interval=%d\n", time_interval);
        fhost_chan.chan2G4_cnt = 0;
        fhost_chan.chan5G_cnt = chan_cnt_saved_5g;
    } else if (band_type == 3) { // 2.4g+5g
        dbg("scan @ 2.4G+5G band, interval=%d\n", time_interval);
        fhost_chan.chan2G4_cnt = chan_cnt_saved_2g4;
        fhost_chan.chan5G_cnt = chan_cnt_saved_5g;
    } else {
        dbg("invalid band_type: %d\n", band_type);
    }
    return ret;
}
#endif

#if (TEST_MONITOR)
/**
 ****************************************************************************************
 * @brief callback function
 *
 * Extract received packet informations (frame length, type, mac addr ...) in monitor mode
 *
 * @param[in] info  RX Frame information.
 * @param[in] arg   Not used
 ****************************************************************************************
 */
static void example_monitor_callback(struct fhost_frame_info *info, void *arg)
{
    if (info->payload == NULL) {
        dbg("Unsupported frame: length = %d\r\n", info->length);
    } else {
        struct mac_hdr *hdr = (struct mac_hdr *)info->payload;
        uint8_t *adr1 = ((uint8_t *)(hdr->addr1.array));
        uint8_t *adr2 = ((uint8_t *)(hdr->addr2.array));
        uint8_t *adr3 = ((uint8_t *)(hdr->addr3.array));
        dbg("a1=%02x:%02x:%02x:%02x:%02x:%02x a2=%02x:%02x:%02x:%02x:%02x:%02x "
            "a3=%02x:%02x:%02x:%02x:%02x:%02x fc=%04X SN:%d len=%d rssi=%d\n",
            adr1[0], adr1[1], adr1[2], adr1[3], adr1[4], adr1[5],
            adr2[0], adr2[1], adr2[2], adr2[3], adr2[4], adr2[5],
            adr3[0], adr3[1], adr3[2], adr3[3], adr3[4], adr3[5],
            hdr->fctl, hdr->seq >> 4, info->length, info->rssi);
    }
}
#endif

/*
 * Entry point of this example application
 */
static RTOS_TASK_FCT(fhost_example_task)
{
#if TEST_SOFTAP
    uint8_t band = 0;       // 0: 2.4G, 1: 5G
    char *ssid = "MySSID";
    char *pw = "passwd";    // NULL for open
    #if (CONFIG_AUTO_PING)
    char *ping_params =
        #if PLF_HW_PXP
        "-r 50 "
        #endif
        "192.168.66.100";
    #endif

    //is_ap = 1;
    do {
        int ret;
        ret = wlan_start_ap(band, (uint8_t *)ssid, (uint8_t *)pw);
        if (ret) {
            dbg("AP start err: %d\n", ret);
            break;
        }

        #if (CONFIG_AUTO_PING)
        while (!ps_sta_connected) {
            #if (PLF_HW_PXP == 1)
            rtos_task_suspend(5);
            #else /* PLF_HW_PXP */
            rtos_task_suspend(200);
            #endif /* PLF_HW_PXP */
        }
        dbg("ps STA found, do ping\n");

        ret = fhost_console_ping(ping_params);
        if (ret) {
            dbg("ping err: %d\n", ret);
            break;
        }
        #endif
    } while (0);
#elif TEST_CONNECT
    if (!wlan_connected) {
        char *ssid = "MySSID", *pw = "passwd";

        #if PLF_HW_PXP
        rtos_task_suspend(5);   // wait for AP starting
        #endif /* PLF_HW_PXP */

        if (0 == wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, 0)) {
            wlan_connected = 1;
        }

        #if CONFIG_SLEEP_LEVEL == 1
        sleep_level_set(PM_LEVEL_LIGHT_SLEEP);
        #elif CONFIG_SLEEP_LEVEL == 2
        sleep_level_set(PM_LEVEL_DEEP_SLEEP);
        #elif CONFIG_SLEEP_LEVEL == 3
        sleep_level_set(PM_LEVEL_HIBERNATE);
        #endif
        user_sleep_allow(1);

        #if !(PLF_HW_PXP)
        // Get quote from a website
        example_connect_website();
        #endif /* !PLF_HW_PXP */
    } else {
        fhost_sta_recover_connection();
    }
#elif TEST_SCAN
    int nb_res;
    struct mac_scan_result result;
    unsigned int fvif_idx = 0;

    ipc_host_cntrl_start();

    cntrl_link = fhost_cntrl_cfgrwnx_link_open();
    if (cntrl_link == NULL) {
        dbg(D_ERR "Failed to open link with control task\n");
        ASSERT_ERR(0);
    }
    // Reset STA interface (this will end previous wpa_supplicant task)
    if (fhost_set_vif_type(cntrl_link, fvif_idx, VIF_UNKNOWN, false) ||
        fhost_set_vif_type(cntrl_link, fvif_idx, VIF_STA, false)) {
        fhost_cntrl_cfgrwnx_link_close(cntrl_link);
        return;
   }

    for (;;) {
        rtos_task_suspend(time_interval);
        nb_res = fhost_scan(cntrl_link, fvif_idx, NULL);
        dbg("Got %d scan results\n", nb_res);

        nb_res = 0;
        while(fhost_get_scan_results(cntrl_link, nb_res++, 1, &result)) {
            result.ssid.array[result.ssid.length] = '\0'; // set ssid string ending
            dbg("(%3d dBm) CH=%3d BSSID=%02x:%02x:%02x:%02x:%02x:%02x "
                #if (PLF_AIC8800)
                "Format %x "
                #endif
                "SSID=%s\n",
                (int8_t)result.rssi, phy_freq_to_channel(result.chan->band, result.chan->freq),
                ((uint8_t *)result.bssid.array)[0], ((uint8_t *)result.bssid.array)[1],
                ((uint8_t *)result.bssid.array)[2], ((uint8_t *)result.bssid.array)[3],
                ((uint8_t *)result.bssid.array)[4], ((uint8_t *)result.bssid.array)[5],
                #if (PLF_AIC8800)
                result.format,
                #endif
                (char *)result.ssid.array);
        }
    }
    fhost_cntrl_cfgrwnx_link_close(cntrl_link);

    while (1);
#elif TEST_MONITOR
    do {
        struct fhost_vif_monitor_cfg cfg;
        struct mac_chan_def *chan;
        unsigned int fvif_idx = 0;
        ipc_host_cntrl_start();
        fhost_cntrl_mm_set_filter(0X3503848C);
        cntrl_link = fhost_cntrl_cfgrwnx_link_open();
        if (cntrl_link == NULL) {
            dbg(D_ERR "Failed to open link with control task\n");
            ASSERT_ERR(0);
        }
        // frequency
        cfg.chan.prim20_freq = 2437; // ch 6
        chan = fhost_chan_get(cfg.chan.prim20_freq);
        if (chan == NULL) {
            dbg("Invalid freq %d\n", cfg.chan.prim20_freq);
            break;
        }
        cfg.chan.band = chan->band;
        cfg.chan.tx_power = chan->tx_power;
        // by default 20Mhz bandwidth
        cfg.chan.type = PHY_CHNL_BW_20;
        cfg.chan.center1_freq = cfg.chan.prim20_freq;
        cfg.chan.center2_freq = 0;
        if (fhost_set_vif_type(cntrl_link, fvif_idx, VIF_MONITOR, false)) {
            dbg("Error while enabling monitor mode\n");
            break;
        }
        cfg.uf = true;
        cfg.cb = example_monitor_callback;
        cfg.cb_arg = NULL;
        if (fhost_cntrl_monitor_cfg(cntrl_link, fvif_idx, &cfg)) {
            dbg("Error while configuring monitor mode\n");
            break;
        }
        // wait 10s
        rtos_task_suspend(10000);
        // stop monitor
        if (fhost_set_vif_type(cntrl_link, fvif_idx, VIF_UNKNOWN, false)) {
            dbg("Error while disabling monitor mode\n");
            break;
        }
    } while (0);
#else
#error "invalid test"
#endif

    rtos_task_delete(NULL);
}

/******************************************************************************
 * Fhost FW interfaces:
 * These are the functions required by the fhost FW that are specific to the
 * final application.
 *****************************************************************************/
/*
 * fhost_application_init: Must initialize the minimum for the application to
 *                         start.
 * In this example only create a new task with the entry point set to the
 * 'fhost_example_task'. The rest on the initialization will be done in this
 * function.
 */
int fhost_application_init(void)
{
    if (rtos_task_create(fhost_example_task, "Example task", APPLICATION_TASK,
                         512, NULL, RTOS_TASK_PRIORITY(1), NULL))
        return 1;

    console_cmd_add("clk", "- show cur clk",         1, 1, do_show_clocks);

    #if (TEST_SCAN)
    chan_cnt_saved_2g4 = fhost_chan.chan2G4_cnt;
    chan_cnt_saved_5g  = fhost_chan.chan5G_cnt;
    console_cmd_add("scanparam", "band interval - set scan params", 3, 3, do_set_scanparam);
    #endif
    return 0;
}


/**
 * @}
 */


