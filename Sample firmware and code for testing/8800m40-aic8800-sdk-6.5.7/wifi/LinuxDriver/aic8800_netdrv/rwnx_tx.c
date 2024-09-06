/**
 ******************************************************************************
 *
 * @file rwnx_tx.c
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ******************************************************************************
 */
#include <linux/dma-mapping.h>
#include <linux/etherdevice.h>
#include <net/sock.h>

#include "rwnx_defs.h"
#include "rwnx_tx.h"
#include "rwnx_main.h"
#include "aicwf_txrxif.h"
#ifdef AICWF_SDIO_SUPPORT
#include "aicwf_sdio.h"
#endif

#ifdef CONFIG_VNET_MODE
extern aicwf_cmd_mgr g_cmd_mgr;
extern aicwf_custom_msg_vnet g_custom_msg_vnet;
netdev_tx_t rwnx_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
    int ret;
    //printk("rwnx_start_xmit %d \r\n",  skb->len);
    if (g_custom_msg_vnet.wlan_status == WLAN_DISCONNECT &&
            g_custom_msg_vnet.ap_status_cfm.status == AIC_AP_CLOSE) {
        txrx_err("wlan is not connected=%d\n", g_custom_msg_vnet.wlan_status);
        aicwf_dev_skb_free(skb);
        return NETDEV_TX_OK;
    }
    #ifdef AICWF_USB_SUPPORT
    ret = aicwf_frame_tx((void *)(g_rwnx_plat->usbdev), skb);
    #endif

    #ifdef AICWF_SDIO_SUPPORT
    ret = aicwf_frame_tx((void *)(g_rwnx_plat->sdiodev), skb);
    #endif

    if (ret) {
        txrx_err("frame_tx ret=%d\n", ret);
        //return NETDEV_TX_BUSY;
    }

    return NETDEV_TX_OK;
}

#elif defined(CONFIG_RAWDATA_MODE)
int rwnx_tx_data(struct sk_buff *skb)
{
    int ret;
    #ifdef AICWF_USB_SUPPORT
    ret = aicwf_frame_tx((void *)(g_rwnx_plat->usbdev), skb);
    #endif

    #ifdef AICWF_SDIO_SUPPORT
    ret = aicwf_frame_tx((void *)(g_rwnx_plat->sdiodev), skb);
    #endif

    return ret;
}
#endif

#define HOST_DATA_HDR_LEN   (offsetof(host_data_t, payload))
void rwnx_tx_msg_send(u8 * msg,  u16 msg_len, int waitcfm)
{
    void *p_dev = NULL;
    u8_l type = 0;
    char *buf = NULL;
    struct aicwf_bus *bus = NULL;
    host_data_t *p_host_data = NULL;

    if (!msg) {
        return;
    }

    #ifdef AICWF_SDIO_SUPPORT
    p_dev = g_rwnx_plat->sdiodev;
    bus   = g_rwnx_plat->sdiodev->bus_if;
    type  = SDIO_TYPE_CFG;
    if (!waitcfm) {
        while(g_rwnx_plat->sdiodev->tx_priv->cmd_txstate == true)
            msleep(10);
    }
    #endif
    #ifdef AICWF_USB_SUPPORT
    p_dev = g_rwnx_plat->usbdev;
    bus   = g_rwnx_plat->usbdev->bus_if;
    type  = USB_TYPE_CFG;
    #endif

    buf = bus->cmd_buf;
    memset(buf, 0, CMD_BUF_MAX);

    p_host_data = (host_data_t *)(buf);
    p_host_data->plen  = (msg_len + 4);
    p_host_data->ptype = type;
    #ifdef AICWF_SDIO_SUPPORT
    if (g_rwnx_plat->sdiodev->chipid == PRODUCT_ID_AIC8800M40) {
        p_host_data->reserved = crc8_ponl_107(&buf[0], 3); // crc8
    }
    #endif

    memcpy((buf + HOST_DATA_HDR_LEN), msg, msg_len);
    aicwf_msg_tx(p_dev, buf, (msg_len + 8));
}

int rwnx_tx_msg_result(char *result)
{
    switch(g_cmd_mgr.cfm_id) {
        case CUST_CMD_CONNECT_IND:
            sprintf(result, "MSG: %x, ssid: %s, rssi: %d, ip: %08x, gw: %08x, mk: %08x\r\n", CUST_CMD_CONNECT_IND,
                g_custom_msg_vnet.connect_ind.ussid, g_custom_msg_vnet.connect_ind.rssi,
                g_custom_msg_vnet.connect_ind.ip, g_custom_msg_vnet.connect_ind.gw, g_custom_msg_vnet.connect_ind.mk);
            break;
        case CUST_CMD_DISCONNECT_IND:
            sprintf(result, "CFM-MSG: %x, disconnect\r\n", CUST_CMD_DISCONNECT_IND);
            break;
        case CUST_CMD_OPEN_BLE_IND:
            sprintf(result, "CFM-MSG: %x, ble task init\r\n", CUST_CMD_OPEN_BLE_IND);
            break;
        case CUST_CMD_CLOSE_BLE_IND:
            sprintf(result, "CFM-MSG: %x, ble task delete\r\n", CUST_CMD_CLOSE_BLE_IND);
            break;
        case CUST_CMD_ENTER_SLEEP_CFM:
            sprintf(result, "CFM-MSG: %x, enter sleep\r\n", CUST_CMD_ENTER_SLEEP_CFM);
            break;
        case CUST_CMD_GET_MAC_ADDR_CFM:
            sprintf(result, "CFM-MSG: %x, mac: %x.%x.%x.%x.%x.%x\r\n", CUST_CMD_GET_MAC_ADDR_CFM,
                g_custom_msg_vnet.macaddr_cfm.mac_addr[0], g_custom_msg_vnet.macaddr_cfm.mac_addr[1],
                g_custom_msg_vnet.macaddr_cfm.mac_addr[2], g_custom_msg_vnet.macaddr_cfm.mac_addr[3],
                g_custom_msg_vnet.macaddr_cfm.mac_addr[4], g_custom_msg_vnet.macaddr_cfm.mac_addr[5]);
            break;
        case CUST_CMD_GET_WLAN_STATUS_CFM:
            if (g_custom_msg_vnet.wlan_status == WLAN_CONNECTED) {
                if (g_custom_msg_vnet.connect_ind.ip) {
                    sprintf(result, "CFM-MSG: %x, ssid: %s, rssi: %d, ip: %x, gw: %x, mk: %x\r\n", CUST_CMD_GET_WLAN_STATUS_CFM,
                        g_custom_msg_vnet.connect_ind.ussid, g_custom_msg_vnet.connect_ind.rssi,
                        g_custom_msg_vnet.connect_ind.ip, g_custom_msg_vnet.connect_ind.gw, g_custom_msg_vnet.connect_ind.mk);
                } else {
                    sprintf(result, "CFM-MSG: %x, ssid: %s, rssi: %d, ip: %x, gw: %x, mk: %x\r\n", CUST_CMD_GET_WLAN_STATUS_CFM,
                        g_custom_msg_vnet.get_wlan_cfm.ussid, g_custom_msg_vnet.get_wlan_cfm.rssi,
                        g_custom_msg_vnet.get_wlan_cfm.ip, g_custom_msg_vnet.get_wlan_cfm.gw, g_custom_msg_vnet.connect_ind.mk);
                }
            } else {
                sprintf(result, "CFM-MSG: %x, disconnect\r\n", CUST_CMD_GET_WLAN_STATUS_CFM);
            }
            break;
        case CUST_CMD_START_AP_CFM:
            sprintf(result, "CFM-MSG: %x, start AP\r\n", CUST_CMD_START_AP_CFM);
            break;
        case CUST_CMD_START_AP_IND:
            if(g_custom_msg_vnet.ap_status_cfm.status == AIC_AP_START) {
                sprintf(result, "CFM-MSG: %x, start AP success, ip: %08x, gw: %08x, mk: %08x\r\n", CUST_CMD_START_AP_IND,
                    g_custom_msg_vnet.ap_status_cfm.ip, g_custom_msg_vnet.ap_status_cfm.gw, g_custom_msg_vnet.ap_status_cfm.mk);
            } else if(g_custom_msg_vnet.ap_status_cfm.status == AIC_AP_CLOSE) {
                sprintf(result, "CFM-MSG: %x, start AP fail\r\n", CUST_CMD_START_AP_IND);
            }
            break;
        case CUST_CMD_CHANGE_AP_MODE_CFM:
            if(g_custom_msg_vnet.aic_mode_status == AIC_MODE_AP_CONFIG) {
                sprintf(result, "CFM-MSG: %x, AIC_MODE_AP_CONFIG\r\n", CUST_CMD_CHANGE_AP_MODE_CFM);
            } else if(g_custom_msg_vnet.aic_mode_status == AIC_MODE_AP_DIRECT) {
                sprintf(result, "CFM-MSG: %x, AIC_MODE_AP_DIRECT\r\n", CUST_CMD_CHANGE_AP_MODE_CFM);
            }
            break;
        case CUST_CMD_STOP_AP_CFM:
            sprintf(result, "CFM-MSG: %x, stop AP\r\n", CUST_CMD_STOP_AP_CFM);
            break;
        case CUST_CMD_STOP_AP_IND:
            sprintf(result, "CFM-MSG: %x, stop AP success\r\n", CUST_CMD_STOP_AP_IND);
            break;
        case CUST_CMD_SCAN_WIFI_CFM:
            sprintf(result, "CFM-MSG: %x, start scan\r\n", CUST_CMD_SCAN_WIFI_CFM);
            break;
        //case CUST_CMD_SCAN_WIFI_IND:
        //    break;
        case CUST_CMD_HOST_SET_WLAN_IP_CFM:
            sprintf(result, "CFM-MSG: %x, set wlan ip success\r\n", CUST_CMD_HOST_SET_WLAN_IP_CFM);
            break;
        default:
            printk("msg cfm id err\n");
    }

    //printk("result: %ld\n", strlen(result));
    return strlen(result);
}

void rwnx_tx_msg_cfm_ready(void)
{
    complete(&g_cmd_mgr.complete);
}

int rwnx_tx_msg(u8 * msg, u16 msg_len, aicwf_custom_msg_cmd_cfm *cfm, char *result)
{
    int ret = 0;
    if (!msg) {
        printk("%s: warning msg is null.\n", __func__);
        ret = -2;
        return ret;
    }

    if (cfm->waitcfm == AICWF_CMD_WAITCFM) {

        g_cmd_mgr.cfm_id = cfm->cfm_id;
        init_completion(&g_cmd_mgr.complete);
        rwnx_tx_msg_send(msg, msg_len, AICWF_CMD_WAITCFM);

        // The len of result-buff is PRIVATE_COMMAND_DEF_LEN.
        memset(result, 0, PRIVATE_COMMAND_DEF_LEN);
        if ((wait_for_completion_timeout(&g_cmd_mgr.complete, msecs_to_jiffies(AICWF_CMDCFM_TIMEOUT)) == 0)) {
            printk("%s: cmd confirm timeout.\n", __func__);
            ret = -3;
        } else {
            // receive cmd-cfm result
            ret = rwnx_tx_msg_result(result);
        }
        g_cmd_mgr.cfm_id = 0;

    } else if (cfm->waitcfm == AICWF_CMD_NOWAITCFM) {
        // cmd send direct.
        rwnx_tx_msg_send(msg, msg_len, AICWF_CMD_NOWAITCFM);
    } else {
        printk("waitcfm param err\n");
        ret = -1;
    }

    return ret;
}

