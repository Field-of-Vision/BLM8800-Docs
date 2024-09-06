 /**
 *******************************************************************************
 *
 * @file fhostif_example.c
 *
 * @brief Definition of an example application task for Fully Hosted firmware
 *  with USB/SDIO interface.
 *
 * Copyright (C) RivieraWaves 2019-2021
 *
 *******************************************************************************
 */

#include "rtos_al.h"
#include "hostif.h"
#include "hostif_cfg.h"
#include "fhostif_cmd.h"
#include "fhost.h"
#include "fhost_tx.h"
#include "fhost_cntrl.h"
#include "fhost_config.h"
#if PLF_CONSOLE
#include "console.h"
#include "command.h"
#endif
#include "fhost_command_common.h"
#if PLF_IPERF
#include "fhost_iperf.h"
#endif
#include "wlan_if.h"
#include "sleep_api.h"
#include "gpio_api.h"
#include "pmic_api.h"

#if PLF_BLE_ONLY
#include "ble_task.h"
#include "rwapp_config.h"
#endif

#ifdef CFG_HOSTIF

typedef void (*hostif_rxdata_cb_t)(unsigned char *, unsigned int);

hostif_rxdata_cb_t hostif_rxdata_cb_func = NULL;

/// Master message queue
static rtos_queue hostif_queue;

#if PLF_BLE_ONLY
uint8_t ble_status = BLE_STATUS_DEFAULT;
#endif
/******************************************************************************
 * Application code:
 *****************************************************************************/

void hostif_post_msg(struct hostif_msg *msg)
{
    int ret;
    //dbg("hostif_post_msg,%x,%p\r\n",msg->id,msg->data);
    //dbg("Qcnt %d\r\n", rtos_queue_cnt(hostif_queue));
    ret = rtos_queue_write(hostif_queue, msg, 0, true);
    if (ret) {
        dbg("error: queue is full\n");
        // if queue is full, drop pkg and free buff.
        host_buffer_t *host_buf = (host_buffer_t *)msg->data;
        host_data_t *host_data = hostb_buf2data(host_buf);
        host_buffer_free(host_data);
    }
}

/**
 * This is the callback function. When wlan connect or disconnect, it will
 * be called.
 */
static void fhostif_get_mac_status(wifi_mac_status_e st)
{
    hostif_status_e hostif_st;
    hostif_st = get_hostif_wlan_status();
    if (WIFI_MAC_STATUS_DISCONNECTED == st) {
        if(HOSTIF_ST_AWAKE == hostif_st || HOSTIF_ST_IDLE == hostif_st)
            // Send disconnect msg to host.
            custom_msg_disconnect_status_ind_handler(hostif_type_get());

    } else if (WIFI_MAC_STATUS_IP_OBTAINED == st) {
        if(HOSTIF_ST_AWAKE == hostif_st || HOSTIF_ST_IDLE == hostif_st) {
            struct custom_msg_connect_ind ind;
            net_if_get_ip(net_if_find_from_wifi_idx(0), &ind.ip, &ind.mk, &ind.gw);
            // Send connect msg to host.
            custom_msg_connect_status_ind_handler(hostif_type_get(), &ind);
        }
    }
}

#if PLF_BLE_ONLY
static void process_host_ble_init_ready(struct hostif_msg *msg)
{
    // Send ble-open msg to host.
    ble_status = BLE_STATUS_INIT;
    dbg("ble_status: %d\n", ble_status);
    custom_msg_ble_status_ind_handler(hostif_type_get(), 1);
}

static void process_host_ble_deinit_ready(struct hostif_msg *msg)
{
    // Send ble-close msg to host.
    ble_status = BLE_STATUS_DEINIT;
    dbg("ble_status: %d\n", ble_status);
    custom_msg_ble_status_ind_handler(hostif_type_get(), 0);
}
#endif

/**
 * Callback handler for rx data
 */
void host_if_rawdata_rx_callback(unsigned char *rx_data, unsigned int rx_len)
{
    if (hostif_rxdata_cb_func) {
        hostif_rxdata_cb_func(rx_data, rx_len);
    } else {
        unsigned int dump_len;
        dbg("host data recv, rx_len=%d\r\n", rx_len);
        if (rx_len > 16) {
            dump_len = 16;
        } else {
            dump_len = rx_len;
        }
        dump_mem((uint32_t)rx_data, dump_len, 1, false);
        // send data back
        dbg("host data send, tx_len=%d\r\n", rx_len);
        host_if_data_send(rx_data, rx_len);
    }
}

/*
 * Entry point of this example application
 */
static RTOS_TASK_FCT(hostif_task)
{
    struct hostif_msg msg;
    // register callback for wlan-conn and wlan-disconn.
    fhost_get_mac_status_register(fhostif_get_mac_status);

    for (;;) {
        rtos_queue_read(hostif_queue, &msg, -1, false);
        //dbg("got msg: %x,%p\r\n",msg.id,msg.data);

        switch (msg.id) {
        case HOSTIF_MSG_RXC:
            process_host_rxc_msg(&msg);
            break;
        case HOSTIF_MSG_TXC:
            process_host_txc_msg(&msg);
            break;
        case HOSTIF_DATA_RXC:
            process_host_rxc_data(&msg);
            break;
        case HOSTIF_READY:
            dbg("host_if_ready\n");
            process_host_if_ready(&msg);
            break;
        #if PLF_BLE_ONLY
        case HOSTIF_BLE_INIT_DONE:
            process_host_ble_init_ready(&msg);
            break;
        case HOSTIF_BLE_DEINIT_DONE:
            process_host_ble_deinit_ready(&msg);
            break;
        #endif /* PLF_BLE_ONLY */
        default:
            break;
        }
    }

    rtos_task_delete(NULL);
}

#if PLF_CONSOLE
int host_poweron(int argc, char * const argv[])
{
    host_if_repower();
    dbg("hostif repower\r\n");
    return 0;
}

int host_poweroff(int argc, char * const argv[])
{
    host_if_poweroff();
    dbg("hostif poweroff\r\n");
    return 0;
}

int wifi_poweron(int argc, char * const argv[])
{
    // TBD:
    //host_if_pu_wificore();
    dbg("wifi repower\r\n");
    return 0;
}

int wifi_poweroff(int argc, char * const argv[])
{
    host_if_pd_wificore();
    dbg("wifi poweroff\r\n");
    return 0;
}

#if FHOST_CONSOLE_LOW_POWER_CASE
int do_set_deepsleep_param(int argc, char * const argv[])
{
    unsigned int listen_interval = console_cmd_strtoul(argv[1], NULL, 10);

    set_deepsleep_param(listen_interval, 1);

    return ERR_NONE;
}

int do_enter_hibernate(int argc, char * const argv[])
{
    uint32_t level = PM_LEVEL_HIBERNATE;

    if (argc > 1) {
        level = console_cmd_strtoul(argv[1], NULL, 10);
    }
    sleep_level_set(level);
    user_sleep_allow(1);

    return ERR_NONE;
}

void console_gpio_irq_handler(int event)
{
    user_sleep_allow(0);
    dbg("GPIO irq handler\n");
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
#endif

int do_tasklist(int argc, char * const argv[])
{
    uint32_t buf_size = command_strtoul(argv[1], NULL, 0);
    if(rtos_task_list(buf_size) == 0)
        return 0;
    else
        return -1;
}
#endif

#if PLF_BLE_ONLY && PLF_BLE_STACK && BLE_APP_SMARTCONFIG
#define DATA_BUF_SIZE 32
struct ble_smartconfig {
    char ssid[DATA_BUF_SIZE];
    char pwd[DATA_BUF_SIZE];
    char time[DATA_BUF_SIZE];
};

rtos_semaphore ble_smartconfig_sema;
struct ble_smartconfig ble_smartconfig_result;
#define APP_SUCCESS_RSP         ("successful")
#define APP_FAILED_RSP          ("failed")
#define HOST_RSP                ("disconnect")
#define HOST_RSP_LEN            sizeof(HOST_RSP)

typedef void(*app_smartconfig_recv_ap_info_cb)(uint8_t *data, uint32_t length);
typedef void(*app_smartconfig_recv_state_info_cb)(uint8_t *data, uint32_t length);
extern void app_smartconfig_send_rsp(uint8_t* data, uint32_t length);
extern void app_smartconfig_register_ap_info_cb(app_smartconfig_recv_ap_info_cb callback);
extern void app_smartconfig_register_state_info_cb(app_smartconfig_recv_state_info_cb callback);
void blewifi_config_ap_info_received(uint8_t* data, uint32_t length)
{
    int i = 0;
    uint8_t index = 0;

    dbg("%s recv ap info %d\r\n", __func__, length);

    memset(ble_smartconfig_result.ssid, 0, DATA_BUF_SIZE);
    memset(ble_smartconfig_result.pwd, 0, DATA_BUF_SIZE);
    for (i = 0; i < length; i++) {
        if (data[i] == '\n') {
            memcpy(&ble_smartconfig_result.ssid[0], &data[0], i);
            index = i + 1;
            break;
        }
    }
    for (i = index; i < length; i++) {
        memcpy(&ble_smartconfig_result.pwd[0], &data[index], length - index);
    }

    dbg("ssid: %s\r\n", ble_smartconfig_result.ssid);
    dbg("pwd : %s\r\n", ble_smartconfig_result.pwd);
    rtos_semaphore_signal(ble_smartconfig_sema, true);

    return;
}

void blewifi_config_state_info_received(uint8_t* data, uint32_t length)
{
    if (memcmp(data, HOST_RSP, HOST_RSP_LEN) == 0) {
        dbg("disconnect\r\n");
        ble_task_deinit();
    }
}


int sta_do_connect()
{
    int ret = 0;
    uint8_t rsp[20];
    ret = wlan_start_sta((uint8_t *)ble_smartconfig_result.ssid,
                         (uint8_t *)ble_smartconfig_result.pwd, 10000);
    if (ret == 0) {
        dbg("connect success\r\n");
        memcpy(&rsp[0], APP_SUCCESS_RSP, sizeof(APP_SUCCESS_RSP));
        app_smartconfig_send_rsp(rsp,  sizeof(APP_SUCCESS_RSP));

    } else {
        dbg("connect fail %d\r\n", ret);
        memcpy(&rsp[0], APP_FAILED_RSP, sizeof(APP_FAILED_RSP));
        app_smartconfig_send_rsp(rsp,  sizeof(APP_FAILED_RSP));
    }
    return ret;
}

static RTOS_TASK_FCT(blewifi_smartconfig_example_task)
{
    if (WLAN_CONNECTED == wlan_get_connect_status()) {
        dbg("WLAN is CONNECT, disconnect WLAN first.\n");
        wlan_disconnect_sta(0);
        rtos_task_suspend(500);
    }

    app_smartconfig_register_ap_info_cb(blewifi_config_ap_info_received);
    app_smartconfig_register_state_info_cb(blewifi_config_state_info_received);
    int ret = rtos_semaphore_create(&ble_smartconfig_sema, 1, 0);
    if (ret) {
        dbg("sema create fail: %d\r\n", ret);
    }

    #if 1
    int nb_res;
    struct mac_scan_result result;
    struct fhost_cntrl_link *fhostif_cntrl_link;
    ipc_host_cntrl_start();

    fhostif_cntrl_link = fhost_cntrl_cfgrwnx_link_open();
    if (fhostif_cntrl_link == NULL) {
        dbg(D_ERR "Failed to open link with control task\n");
        ASSERT_ERR(0);
    }
    // Reset STA interface (this will end previous wpa_supplicant task)
    if (fhost_set_vif_type(fhostif_cntrl_link, 0, VIF_UNKNOWN, false) ||
        fhost_set_vif_type(fhostif_cntrl_link, 0, VIF_STA, false)) {

        fhost_cntrl_cfgrwnx_link_close(fhostif_cntrl_link);
        return;
    }

    nb_res = fhost_scan(fhostif_cntrl_link, 0, NULL);
    dbg("Got %d scan results\n", nb_res);

    nb_res = 0;
    while(fhost_get_scan_results(fhostif_cntrl_link, nb_res++, 1, &result)) {
        result.ssid.array[result.ssid.length] = '\0'; // set ssid string ending
        dbg("(%3d dBm) CH=%3d BSSID=%02x:%02x:%02x:%02x:%02x:%02x SSID=%s\n",
            (int8_t)result.rssi, phy_freq_to_channel(result.chan->band, result.chan->freq),
            ((uint8_t *)result.bssid.array)[0], ((uint8_t *)result.bssid.array)[1],
            ((uint8_t *)result.bssid.array)[2], ((uint8_t *)result.bssid.array)[3],
            ((uint8_t *)result.bssid.array)[4], ((uint8_t *)result.bssid.array)[5],
            (char *)result.ssid.array);
    }
    fhost_cntrl_cfgrwnx_link_close(fhostif_cntrl_link);
    #endif

    dbg("wait for connect...\r\n");
    rtos_semaphore_wait(ble_smartconfig_sema, -1);
    sta_do_connect();

    dbg("Exit blewifi smartconfig task.\n");
    rtos_task_delete(NULL);
}

int do_blewifi_config(int argc, char * const argv[])
{
    if (rtos_task_create(blewifi_smartconfig_example_task, "blewifi_config", SMARTCONF_TASK,
                         512, NULL, RTOS_TASK_PRIORITY(1), NULL))
        return -1;
    return 0;
}
#endif /* PLF_BLE_ONLY && PLF_BLE_STACK && BLE_APP_SMARTCONFIG */

#define RAWDATA_TRANSFER 0
#if RAWDATA_TRANSFER
int host_perf_tx(int argc, char * const argv[])
{
    unsigned char * txbuff = NULL;
    unsigned int total_size = 0, success_cnt = 0, speed = 0, time_ad_ms = 0;
    unsigned int block_n = 0, block = 0;
    int i, retry_cnt = 0, delay_ms = 2;

    #if PLF_STDLIB
    sscanf(argv[1], "%u", &block);
    sscanf(argv[2], "%u", &block_n);
    if (argc > 3) {
        sscanf(argv[3], "%u", &delay_ms);
    }
    #else
    block = command_strtoul(argv[1], NULL, 0);
    block_n = command_strtoul(argv[2], NULL, 0);
    if (argc > 3) {
        delay_ms = command_strtoul(argv[3], NULL, 0);
    }
    #endif
    dbg("block:%u block_n:%u\r\n", block, block_n);

    txbuff = rtos_malloc(block);

    if (txbuff == NULL) {
        dbg(D_ERR "msg alloc err\r\n");
        return -1;
    }

    for (i = 1; i < block; i++)
        txbuff[i] = i & 0xff;

    txbuff[0] = 0x80; // 1st byte as seq_no
    txbuff[1] = 'S';  // 2nd byte as trans flag (start flag)

    speed = rtos_now(false);

    for (i = 0; i < block_n; i++) {
        int ret;
        if (i == 1) {
            txbuff[1] = 'I'; // in progress flag
        }
        if (i == (block_n - 1)) {
            txbuff[1] = 'E'; // end flag
        }
        ret = host_if_data_send(txbuff, block);
        if (ret) {
            dbg("send [%d] seq=%d res=%d\n", i, txbuff[0], ret);
            retry_cnt = 0;
            if (ret < 0) {
                for (retry_cnt = 1; retry_cnt < 16; retry_cnt++) {
                    // delay & retry
                    rtos_task_suspend(delay_ms);
                    ret = host_if_data_send(txbuff, block);
                    if (ret >= 0) {
                        dbg("resend [%d] ok cnt=%d\n", i, retry_cnt);
                        break;
                    }
                }
            }
            if (retry_cnt < 16) {
                dbg("resend [%d] %d times res=%d total delay %dms\n", i, retry_cnt, ret, delay_ms * retry_cnt);
                success_cnt++;
            } else {
                dbg("give up [%d]\n", i);;
            }
        } else {
            success_cnt++;
        }
        txbuff[0]++;
    }

    time_ad_ms = rtos_now(false) - speed;
    if (!time_ad_ms) {
        time_ad_ms = 1;
    }
    total_size = success_cnt * block;
    speed = total_size * 1000.0 / 1024.0 / time_ad_ms;

    dbg("success: %d, fail: %d\r\n", success_cnt, block_n - success_cnt);
    dbg("total_size: %d, time_ad: %d\r\n", total_size, time_ad_ms);
    dbg("speed is %ld KB/S\r\n", speed);

    rtos_free(txbuff);
    return 0;
}

void perf_rx_callback(unsigned char *rx_data, unsigned int rx_len)
{
    static int dbg_rxdata_cnt = 0;
    static unsigned char dbg_rxdata_seq = 0;
    static uint32_t dbg_start_ms = 0;
    static uint32_t dbg_rxdata_sz = 0;
    dbg_rxdata_cnt++;
    dbg_rxdata_sz += rx_len;
    if ((unsigned char)(dbg_rxdata_seq + 0x1) != rx_data[0]) {
        dbg("last_seq=%d, cur_seq=%d, cnt=%d\n", dbg_rxdata_seq, rx_data[0], dbg_rxdata_cnt);
    }
    dbg_rxdata_seq =  rx_data[0];
    if ((char)rx_data[1] == 'S') {
        dbg_start_ms = rtos_now(false);
        dbg("[%d] start\n", dbg_start_ms);
    } else if ((char)rx_data[1] == 'E') {
        uint32_t dbg_end_ms = rtos_now(false);
        uint32_t dbg_cost_ms = 1, speed;
        if (dbg_end_ms - dbg_start_ms) {
            dbg_cost_ms = dbg_end_ms - dbg_start_ms;
        }
        speed = dbg_rxdata_sz * 1000.0 / 1024 / dbg_cost_ms;
        dbg("[%d] end, cnt=%d, cost=%dms\n", dbg_end_ms, dbg_rxdata_cnt, dbg_cost_ms);
        dbg("rx %d bytes, speed %d KB/s\n", dbg_rxdata_sz, speed);
        dbg_rxdata_cnt = 0;
        dbg_rxdata_seq = 0;
        dbg_rxdata_sz = 0;
    }
}

int host_perf_rx(int argc, char * const argv[])
{
    unsigned int rx_en;
    #if PLF_STDLIB
    sscanf(argv[1], "%u", &rx_en);
    #else
    rx_en = command_strtoul(argv[1], NULL, 0);
    #endif
    if (rx_en) {
        hostif_rxdata_cb_func = perf_rx_callback;
    } else {
        hostif_rxdata_cb_func = NULL;
    }
    return 0;
}
#endif

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

int do_reboot(int argc, char * const argv[])
{
    pmic_chip_reboot(0xF);
    return 0;
}

/******************************************************************************
 * Hostif interfaces:
 * These are the functions required by the hostif that are specific to the
 * final application.
 *****************************************************************************/

int fhost_application_init(void)
{
    if (rtos_queue_create(sizeof(struct hostif_msg), 128, &hostif_queue)) {
        return 1;
    }

    if (rtos_task_create(hostif_task, "Hostif task", APP_HOSTIF_TASK,
                         512, NULL, RTOS_TASK_PRIORITY(3), NULL))
        return 2;

    #if PLF_CONSOLE
    console_cmd_add("connect", "0/1 ssid <pwd>", 1, 4, do_connect);
    console_cmd_add("disconnect", "- Disconnect Station", 1, 1, do_disconnect);
    #if NX_BEACONING
    console_cmd_add("startap", "band ssid <pwd>", 3, 4, do_start_ap);
    console_cmd_add("stopap", "- Stop AP", 1, 1, do_stop_ap);
    #endif
    console_cmd_add("hpon", "host pon",  1, 1, host_poweron);
    console_cmd_add("hpof", "host poff", 1, 1, host_poweroff);
    console_cmd_add("wpon", "wifi pon",  1, 1, wifi_poweron);
    console_cmd_add("wpof", "wifi poff", 1, 1, wifi_poweroff);
    #if (FHOST_CONSOLE_LOW_POWER_CASE)
    console_cmd_add("setdsparam", "listen_interval", 2, 2, do_set_deepsleep_param);
    console_cmd_add("hib", "slplvl", 1, 2, do_enter_hibernate);
    console_cmd_add("gpb2wu", "Set gpiob2 wakeup",  1, 1, do_gpiob2_wakeup);
    #endif
    #if (configUSE_TRACE_FACILITY == 1)
    console_cmd_add("task",     "- Show task info", 1, 1, do_show_task);
    #endif
    console_cmd_add("heap",     "- Show heap info", 1, 1, do_show_heap);
    #endif

    #if PLF_BLE_ONLY && PLF_BLE_STACK && BLE_APP_SMARTCONFIG
    console_cmd_add("blewifi_cfg", "- ble smartconfig wifi", 1, 1, do_blewifi_config);
    #endif

    #if RAWDATA_TRANSFER
    console_cmd_add("perftx", "blk blk_n - host perf tx test", 3, 4, host_perf_tx);
    console_cmd_add("perfrx", "0/1 - host perf rx dis/en", 2, 2, host_perf_rx);
    #endif

    #if PLF_IPERF
    console_cmd_add("iperf", "<-s|-c|-h> [options]", 1, 20, do_iperf);
    #endif /* PLF_IPERF */

	console_cmd_add("reboot",   "Software Reboot",                  1, 1, do_reboot);
	console_cmd_add("mac",     "?/[hex_str]",    2, 2, do_mac);
	console_cmd_add("blink_magic",     "?/[hex_str]",    2, 2, do_blink_magic);
	
    return 0;
}
#endif /* CFG_HOSTIF */
/**
 * @}
 */


