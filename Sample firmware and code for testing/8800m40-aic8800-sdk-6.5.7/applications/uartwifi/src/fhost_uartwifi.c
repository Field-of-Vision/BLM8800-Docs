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
#include <strings.h>
#include "api.h"
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
#include "fhost_smartconf.h"
#include "sleep_api.h"
#include "flash_api_wifi.h"
#include "stdio_uart.h"
#include "fhost_command_common.h"
#if PLF_FATFS
#include "ff.h"
#endif /* PLF_FATFS */
#include "fhost_mdns.h"
#include "dns.h"

/// Console task message queue size
#define FHOST_CONSOLE_QUEUE_SIZE    10

typedef struct{
    int socket;
    int type;
    int used;
    char svr_addr[16];
    char svr_port;
    char local_port;
    rtos_task_handle handle;
}tcp_udp_socket_t;
#define SOCKET_NUM 4
#define RECV_LIMIT 1460
#define SEND_LIMIT 1460

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
tcp_udp_socket_t nw_sock[SOCKET_NUM];

/// Master message queue
static rtos_queue console_queue;

/// Link to control task
static struct fhost_cntrl_link *console_cntrl_link;

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

    nb_res = fhost_scan(console_cntrl_link, fvif_idx, NULL);
    dbg("Got %d scan results\n", nb_res);

    nb_res = 0;
    while(fhost_get_scan_results(console_cntrl_link, nb_res++, 1, &result)) {
        if (result.ssid.length < MAC_SSID_LEN)
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

static RTOS_TASK_FCT(tcp_udp_recv_task)
{
    uint32_t index, size = 0;
    uint8_t  recv_buf[RECV_LIMIT+1];

    index = (int)env;
    while(1) {
        if(nw_sock[index].type == 0) { //TCP
            size = recv(nw_sock[index].socket, recv_buf, RECV_LIMIT, 0);
            if(size <= 0){
                close(nw_sock[index].socket);
                break;
            }
        } else if(nw_sock[index].type == 1) { //UDP
            size = recv(nw_sock[index].socket, recv_buf, RECV_LIMIT, 0);
            if(size <= 0) {
                close(nw_sock[index].socket);
                break;
            }
        }
        recv_buf[size] = 0;
        dbg("Receive %d bytes, %s\r\n", size, recv_buf);
    }
    dbg("End task: tcp_udp_recv_task\r\n");
    rtos_task_delete(NULL);
}
static int do_create_client(int argc, char * const argv[])
{
    int index;
    rtos_task_handle handle;
    struct sockaddr_in sock_addr;
    struct sockaddr_in udp_local_addr;
    struct sockaddr_in udp_dest_addr;
    int sock = -1;
    uint32_t svr_addr = 0;
    uint16_t svr_port = 0;
    uint32_t local_addr = 0;
    uint16_t local_port = 0;

    for(index=0; index<SOCKET_NUM; index++)
        if(nw_sock[index].used == 0)
            break;

    if(index == SOCKET_NUM) {
        return ERR_CMD_ABORT;
    }

    if(argc < 3){
        dbg("Please set server ip and server port!\r\n");
        return ERR_WRONG_ARGS;
    }
    ipaddr_aton(argv[2], (ip_addr_t *)&svr_addr);
    memcpy(nw_sock[index].svr_addr, argv[2], strlen(argv[2]));
    svr_port = atoi(argv[3]);
    nw_sock[index].svr_port = svr_port;

    if(5 == argc) {
        local_port = atoi(argv[4]);
    }

    // create socket
    if(!strcmp(argv[1], "TCP")){
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            dbg("open socket error: %d\r\n", sock);
            return ERR_CMD_FAIL;
        }
        nw_sock[index].socket = sock;
        nw_sock[index].type = 0; //TCP
        nw_sock[index].used = 1;
        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = svr_addr;
        sock_addr.sin_port = htons(svr_port);
        if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0){
            dbg("socket connect error\r\n");
            return ERR_CMD_FAIL;
        }
    }else if(!strcmp(argv[1], "UDP")){
        sock = socket(PF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            dbg("open socket error: %d\r\n", sock);
            return ERR_CMD_FAIL;
        }
        nw_sock[index].socket = sock;
        nw_sock[index].type = 1; //UDP
        nw_sock[index].used = 1;
        memset(&udp_local_addr, 0, sizeof(udp_local_addr));
        net_if_get_ip(net_if_find_from_wifi_idx(0), &local_addr, NULL,NULL);
        udp_local_addr.sin_family = AF_INET;
        udp_local_addr.sin_addr.s_addr = local_addr;
        udp_local_addr.sin_port = htons(local_port);
        if (bind(sock, (struct sockaddr *)&udp_local_addr, sizeof(udp_local_addr)) < 0) {
            dbg("socket bind error\r\n");
            return ERR_CMD_FAIL;
        }
        memset(&udp_dest_addr, 0, sizeof(udp_dest_addr));
        udp_dest_addr.sin_family = AF_INET;
        udp_dest_addr.sin_addr.s_addr = svr_addr;
        udp_dest_addr.sin_port = htons(svr_port);
        if (connect(sock, (struct sockaddr *)&udp_dest_addr, sizeof(udp_dest_addr)) < 0){
            dbg("socket connect error\r\n");
            return ERR_CMD_FAIL;
        }
    }else{
        return ERR_WRONG_ARGS;
    }

    if(0 != rtos_task_create(tcp_udp_recv_task, "TCP/UDP task", TCPUDP_FIRST_TASK+index,
                             512, (void *)index, RTOS_TASK_PRIORITY(1), &handle)) {
        return ERR_CMD_ABORT;
    }
    nw_sock[index].handle = handle;
    return ERR_NONE;
}
static int do_nw_send(int argc, char * const argv[])
{
    unsigned int index, total_len, size = 0;
    unsigned char *buf;

    if(argc < 3){
        dbg("Please set socket index!\r\n");
        return ERR_WRONG_ARGS;
    }

    index = atoi(argv[1]);
    total_len = atoi(argv[2]);

    if(nw_sock[index].used != 1){
        dbg("Socket not in use!\r\n");
        return ERR_CMD_ABORT;
    }

    if(total_len > 1460){
        dbg("Send data len longger than %d!\r\n", 1460);
        return ERR_WRONG_ARGS;
    }

    buf = (unsigned char *)rtos_malloc(total_len);
    if(!buf) {
        return ERR_CMD_ABORT;
    }

    for(uint32_t i = 0; i < total_len; i++) {
        buf[i] = (i & 0xFF);
    }
    if(nw_sock[index].type == 0) {
        size = send(nw_sock[index].socket, buf, total_len, 0);
        dbg("TCP send size %d\r\n", size);
    }else if(nw_sock[index].type == 1) {
        size = send(nw_sock[index].socket, buf, total_len, 0);
        dbg("UDP send size %d\r\n", size);
    }

    rtos_free(buf);
    buf= NULL;

    if(size == total_len) {
        return ERR_NONE;
    } else {
        return ERR_CMD_FAIL;
    }
}
static int do_nw_stop(int argc, char * const argv[])
{
    uint32_t index;
    if(argc < 2){
        dbg("Please set socket index!\r\n");
        return ERR_WRONG_ARGS;
    }

    index = atoi(argv[1]);

    if(nw_sock[index].used != 1){
        dbg("Socket not in use!\r\n");
        return ERR_CMD_ABORT;
    }
    nw_sock[index].used = 0;
    close(nw_sock[index].socket);
    rtos_task_delete(nw_sock[index].handle);
    return ERR_NONE;
}
static int do_nw_link(int argc, char * const argv[])
{
    int i, n=0;

    for(i=0; i<SOCKET_NUM; i++)
        if(nw_sock[i].used == 1)
            n++;

    dbg("Link cnt %d\r\n", n);

    for(i=0; i<SOCKET_NUM; i++) {
        if(nw_sock[i].used == 1)
            dbg("%d,%s,%s,%d,%d\r\n", i, nw_sock[i].type ? "UDP":"TCP", nw_sock[i].svr_addr, \
                nw_sock[i].svr_port, nw_sock[i].local_port);
    }

    return ERR_NONE;
}

static int do_nw_dns(int argc, char * const argv[])
{
    ip_addr_t addr;
    int ret;

    if(wlan_connected == 0) {
        dbg("Err: Connect first\r\n");
        return ERR_CMD_ABORT;
    }
    ret = netconn_gethostbyname(argv[1], &addr);
    if(ret != 0){
        return ERR_CMD_FAIL;
    }

    dbg("  %s <-> %s\r\n", argv[1], inet_ntoa(addr));
    return ERR_NONE;
}
static int do_nw_set_dns_server(int argc, char * const argv[])
{
    const ip_addr_t *addr0;
    ip_addr_t addr;
    uint32_t  dns_server;

    if(wlan_connected == 0) {
        dbg("Err: Connect first\r\n");
        return ERR_CMD_ABORT;
    }

    addr0 = dns_getserver(0);
    if(*argv[1] == '?') {
        dbg("DNS server: %s\r\n", inet_ntoa(*addr0));
        return ERR_NONE;
    }

    if(atoi(argv[1])) {
        if(argc < 3) {
            return ERR_WRONG_ARGS;
        }
        fhost_nw_parse_ip4(argv[2], &dns_server, NULL);
        ip_addr_set_ip4_u32(&addr, dns_server);
        dns_setserver(0, &addr);
        flash_wifi_lwip_dnsserv_write(dns_server);
        dbg("New DNS server: %s\r\n", inet_ntoa(addr));
    }

    return ERR_NONE;
}

#if PLF_PING
static int do_uart_ping(int argc, char * const argv[])
{
    char ping_params[64] = {0};
    unsigned int idx = 0, tok = 0;
    if (argc < 2) {
        dbg ("Usage:\n  ping dst_ip|stop ID\n");
        return ERR_WRONG_ARGS;
    }

    if (!netif_is_up(net_if_find_from_wifi_idx(fhost_vif_idx)))  {
        dbg ("Usage:\n Connect first\n");
        return ERR_CMD_ABORT;
    }

    memcpy(&(ping_params[idx]), argv[1], strlen(argv[1]));
    idx += strlen(argv[1]);

    if (argc >= 3) {
        memcpy(&(ping_params[idx]), " -d ", 4);
        idx += 4;
        memcpy(&(ping_params[idx]), argv[2], strlen(argv[2]));
        idx += strlen(argv[2]);
    }

    if (argc >= 4) {
        memcpy(&(ping_params[idx]), " -r ", 4);
        idx += 4;
        memcpy(&(ping_params[idx]), argv[3], strlen(argv[3]));
        idx += strlen(argv[3]);
    }

    if (argc >= 5) {
        memcpy(&(ping_params[idx]), " -s ", 4);
        idx += 4;
        memcpy(&(ping_params[idx]), argv[4], strlen(argv[4]));
        idx += strlen(argv[4]);
    }

    if (argc >= 6) {
        tok = console_cmd_strtoul(argv[5], NULL, 10);
        if(!tok)
            memcpy(&(ping_params[idx]), " -G", 3);
    }
    dbg("ping_params %s\r\n", ping_params);
    fhost_console_ping(ping_params);

    return ERR_NONE;
}
#endif /* PLF_PING */
#if PLF_IPERF
static int do_uart_iperf(int argc, char * const argv[])
{
    char iperf_params[64] = {0};
    unsigned int idx = 0;
    if (argc < 2) {
        dbg ("Usage:\n  iperf ...\n");
        return ERR_WRONG_ARGS;
    }

    if (!netif_is_up(net_if_find_from_wifi_idx(fhost_vif_idx)))  {
        dbg ("Usage:\n Connect first\n");
        return ERR_CMD_ABORT;
    }


    uint8_t argv_index = 1;

    if(!strcmp(argv[argv_index], "STOP")) {
        fhost_iperf_sigkill_handler(iperf_task_handle);
        return ERR_NONE;
    }
    if(!strcmp(argv[argv_index++], "U")) {
        memcpy(&(iperf_params[idx]), "-u ", 3);
        idx += 3;
    }
    if(!strcmp(argv[argv_index], "S")) {
        memcpy(&(iperf_params[idx]), "-s", 2);
        idx += 2;
        argv_index++;
    }
    if(!strcmp(argv[argv_index], "C")) {
        memcpy(&(iperf_params[idx]), "-c ", 3);
        idx += 3;
        argv_index++;
        memcpy(&(iperf_params[idx]), argv[argv_index], strlen(argv[argv_index]));
        idx += strlen(argv[argv_index++]);
        memcpy(&(iperf_params[idx]), " -t ", 4);
        idx += 4;
        memcpy(&(iperf_params[idx]), argv[argv_index], strlen(argv[argv_index]));
        idx += strlen(argv[argv_index++]);
        if(!strcmp(argv[1], "U")) {
            memcpy(&(iperf_params[idx]), " -b ", 4);
            idx += 4;
            memcpy(&(iperf_params[idx]), argv[argv_index], strlen(argv[argv_index]));
            idx += strlen(argv[argv_index++]);
        }
    }
    memcpy(&(iperf_params[idx]), " -i ", 4);
    idx += 4;
    dbg("argv_index %d %s \r\n", argv_index, argv[argv_index]);
    memcpy(&(iperf_params[idx]), argv[argv_index], strlen(argv[argv_index]));
    idx += strlen(argv[argv_index++]);

    dbg("iperf_params %s\r\n", iperf_params);
    fhost_console_iperf(iperf_params);

    return ERR_NONE;
}
#endif /* PLF_IPERF */

static int do_fixed_ip(int argc, char * const argv[])
{
    uint8_t enable;

    if(1 == wlan_connected){
        return ERR_CMD_ABORT;
    }

    enable = atoi(argv[1]);
    is_fixed_ip = enable;
    if(enable == 1) {
        fixed_ip   = inet_addr(argv[2]);
        fixed_mask = inet_addr(argv[3]);
        fixed_gw   = inet_addr(argv[4]);
    }

    return ERR_NONE;
}

#if PLF_FATFS
static int do_fatfs_operation(int argc, char * const argv[])
{
    int oper;
    int err;
    unsigned int num;
    static char *fsid = NULL;
    FATFS fs;
    FIL fh;
    FILINFO fi;
    DIR d;
    char fileName[128];
    char dirName[128];
    char read_text[64];
    oper = console_cmd_strtoul(argv[1], NULL, 10);
    switch (oper) {
    case 0: // mount
        if (strncasecmp(argv[2], "USB:/", 3)) {
            fsid = "USB:/";
        } else if (strncasecmp(argv[2], "SD:/", 2)) {
            fsid = "SD:/";
        }
        if (fsid) {
            dbg("mount: %s\r\n", fsid);
            err = f_mount(&fs, fsid, 0);
            if (err) {
                dbg("Fail to mount, err=%d\r\n", err);
                return ERR_CMD_ABORT;
            }
        }
        break;
    case 1: // umount
        if (fsid) {
            dbg("umount: %s\r\n", fsid);
            err = f_mount(NULL, fsid, 0);
            if (err) {
                dbg("Fail to umount, err=%d\r\n", err);
                return ERR_CMD_ABORT;
            }
        }
        break;
    case 2: // list dir
        dbg_snprintf(dirName, sizeof(dirName), "%s%s", fsid, argv[2]);
        dbg("list dir: %s\r\n", dirName);
        err = f_opendir(&d, dirName);
        if (err) {
            dbg("Fail to open dir: %s\n", dirName);
        }
        while (1) {
            DIR sub_d;
            int idx = 0;
            err = f_readdir(&d, &fi);
            if ((err != FR_OK) || (fi.fname[0] == 0)) {
                break;
            }
            dbg_snprintf(fileName, sizeof(fileName), "%s/%s", dirName, fi.fname);
            err = f_opendir(&sub_d, fileName);
            if (err != FR_NO_PATH) {
                strcat(fileName, "/");
                f_closedir(&sub_d);
            }
            dbg("[%d]: %s\n", idx, fileName);
        }
        f_closedir(&d);
        break;
    case 3: // read file
        dbg_snprintf(fileName, sizeof(fileName), "%s%s", fsid, argv[2]);
        dbg("read file: %s\r\n", fileName);
        err = f_stat(fileName, &fi);
        if (err == FR_NO_FILE) {
            dbg("File not exist: %s\r\n", fileName);
            return ERR_WRONG_ARGS;
        } else if (err) {
            dbg("Fail to stat, err=%d\r\n", err);
            return ERR_CMD_ABORT;
        }
        //dbg("open file: %s\r\n", fileName);
        err = f_open(&fh, fileName, FA_READ);
        if (err) {
            dbg("Fail to open, err=%d\r\n", err);
            return ERR_CMD_ABORT;
        }
        err = f_read(&fh, read_text, sizeof(read_text), &num);
        if (err) {
            dbg("Fail to read, err=%d, num=%d\r\n", err, num);
            f_close(&fh);
            return ERR_CMD_ABORT;
        }
        dbg("Read text:\r\n%s\r\n", read_text);
        f_close(&fh);
        break;
    default:
        break;
    }
    return ERR_NONE;
}
#endif /* PLF_FATFS */

/*
* @brief    config uart parameters
* @param    [in] baudrate
* @param    [in] databits, valid value: 5/6/7/8
* @param    [in] parity, 0/1: None, 2: odd, 3: even
* @param    [in] stopbits, valid value: 1/2
*/
static int do_uart_cfg(int argc, char * const argv[])
{
    uint32_t baudrate, databits, parity, stopbits;
    if(*argv[1] == '?') {
        baudrate = stdio_uart_baud_get();
        stdio_uart_format_get(&databits, &parity, &stopbits);
        dbg("baud: %d\r\ndata: %x\r\npari: %x\r\nstop: %x\r\n",
            baudrate, databits, parity, stopbits);
        return ERR_NONE;
    }
    if (argc < 5) {
        return ERR_WRONG_ARGS;
    }
    baudrate = console_cmd_strtoul(argv[1], NULL, 10);
    databits = console_cmd_strtoul(argv[2], NULL, 10);
    parity   = console_cmd_strtoul(argv[3], NULL, 10);
    stopbits = console_cmd_strtoul(argv[4], NULL, 10);
    stdio_uart_baud_set(baudrate);
    stdio_uart_format_set(databits, parity, stopbits);
    return ERR_NONE;
}

#ifdef CFG_SOFTAP
int do_ap_dhcps(int argc, char * const argv[])
{
    unsigned int ap_lease_time = 0;
    unsigned int ap_dhcp_start = 0;
    unsigned int ap_dhcp_end = 0;
    uint8_t enable;
    enable = atoi(argv[1]);

    if (enable) {
        ap_lease_time = (uint16_t)console_cmd_strtoul(argv[2], NULL, 10);
        fhost_nw_parse_ip4(argv[3], (uint32_t *)&ap_dhcp_start, NULL);
        fhost_nw_parse_ip4(argv[4], (uint32_t *)&ap_dhcp_end, NULL);
    }
    flash_wifi_lwip_dhcps_write(ap_lease_time, ap_dhcp_start, ap_dhcp_end);

    return ERR_NONE;
}
#endif /* CFG_SOFTAP */
int do_set_name(int argc, char * const argv[])
{
    if (VIF_STA == vif_info_tab[0].type) {
        memset(vif_info_tab[0].u.sta.vif_name, 0, 32);
        memcpy(vif_info_tab[0].u.sta.vif_name, argv[1], strlen(argv[1]));
        dbg("vif_name %s \r\n", vif_info_tab[0].u.sta.vif_name);
    } else {
        return ERR_CMD_ABORT;
    }

    return ERR_NONE;
}

#if LWIP_IGMP
int do_mdns(int argc, char * const argv[])
{
    if(atoi(argv[1])) {
        if (argc < 4) {
            return ERR_WRONG_ARGS;
        }
        fhost_mdns_set_param(argv[2], argv[3], atoi(argv[4]));
        fhost_mdns_start();
    } else {
        fhost_mdns_stop();
    }

    return ERR_NONE;
}
#endif

static void fhost_command_add(void)
{
    console_cmd_add("SLPLVL",   "Set system sleep level",   2, 2, do_sleep_level);
    console_cmd_add("USRWUSRC", "Set user wakeup source",   3, 4, do_user_wakeup_source);
    console_cmd_add("USRSLP",   "Allow user sleep",         2, 2, do_user_sleep);
    console_cmd_add("WSCAN",    "WiFi scan fvif_idx",       2, 2, do_scan);
    console_cmd_add("WMAC",     "WiFi get/set mac address", 2, 2, do_mac);
    console_cmd_add("WFIXIP",   "WiFi fix IP",              2, 5, do_fixed_ip);
    console_cmd_add("RESTORE",  "Clean flash info",         1, 1, do_restore);
    console_cmd_add("HEAP",     "Show remain heap",         1, 1, do_show_heap);
    console_cmd_add("TXPWR",    "Set rf tx powers",         3, 3, do_set_power);
#ifdef CFG_SOFTAP
    console_cmd_add("WCAP",     "Wifi create AP",           5, 9, do_create_ap);
    console_cmd_add("WAPSTART", "WiFi start ap",            3, 4, do_start_ap);
    console_cmd_add("WAPSTOP",  "WiFi stop ap",             1, 1, do_stop_ap);
    console_cmd_add("WAPDHCPS", "WiFi ap DHCP range",       2, 6, do_ap_dhcps);
#endif /* CFG_SOFTAP */
    console_cmd_add("WSETNAME", "STA set host name ",       2, 2, do_set_name);
    #if LWIP_IGMP
    console_cmd_add("WMDNS",    "mDNS ",                    2, 5, do_mdns);
    #endif
    console_cmd_add("WAUTOCNCT","STA connect AP auto",      3, 3, do_auto_connect);
    console_cmd_add("WSTACNCT", "WiFi STA connect",         1, 4, do_connect);
    console_cmd_add("WSDISCNCT","WiFi STA disconnect",      1, 1, do_disconnect);
#if NX_SMARTCONFIG
    console_cmd_add("WSMRTCONF","WiFi smartconfig",         1, 1, do_smartconf);
    console_cmd_add("WSSTOPSC",  "WiFi stop smartconf",     1, 1, do_stop_smartconf);
#endif /* NX_SMARTCONFIG */
#if PLF_PING
    console_cmd_add("WPING",    "WiFi ping dst_ip",         2, 7, do_uart_ping);
#endif /* PLF_PING */
#if PLF_IPERF
    console_cmd_add("WIPERF",    "Iperf",                   2, 7, do_uart_iperf);
#endif /* PLF_IPERF */
    console_cmd_add("NCRECLNT", "Create TCP/UDP client",    3, 5, do_create_client);
    console_cmd_add("NSEND",    "Send TCP/UDP data",        3, 3, do_nw_send);
    console_cmd_add("NSTOP",    "Stop TCP/UDP connection",  2, 3, do_nw_stop);
    console_cmd_add("NLINK",    "TCP/UDP Link status",      1, 1, do_nw_link);
    console_cmd_add("NDNS",     "DNS",                      2, 2, do_nw_dns);
    console_cmd_add("NDNSSERVER","Set DNS server",          2, 4, do_nw_set_dns_server);
#if PLF_FATFS
    console_cmd_add("FATFS",    "File system",              2, 3, do_fatfs_operation);
#endif /* PLF_FATFS */
#ifdef CFG_WPS
    console_cmd_add("WSWPS",    "WPS",                      1, 1, do_wps_pbc);
#endif /* CFG_WPS */
    console_cmd_add("UART",     "Uart config",              2, 5, do_uart_cfg);
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
static RTOS_TASK_FCT(fhost_uartwifi_task)
{
    struct fhost_msg msg;

    sta_auto_connect();

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
    if (rtos_task_create(fhost_uartwifi_task, "CONSOLE", APPLICATION_TASK,
                         512, NULL, RTOS_TASK_PRIORITY(1), NULL)) {
        return 1;
    }

    if (rtos_queue_create(sizeof(struct fhost_msg), FHOST_CONSOLE_QUEUE_SIZE, &console_queue))
        return 2;

    console_ntf_register(fhost_console_resume);

    fhost_command_add();

    return 0;
}

