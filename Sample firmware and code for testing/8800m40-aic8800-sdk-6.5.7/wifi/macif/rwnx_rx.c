/**
 ******************************************************************************
 *
 * @file rwnx_rx.c
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ******************************************************************************
 */

#include "rwnx_utils.h"
#if !defined(CFG_DEVICE_IPC)
#include "fhost.h"
#include "fhost_rx.h"
//#include "fhost_tx.h"
//#include "fhost_cntrl.h"
#endif
#include "rwnx_rx.h"
#include "mac_frame.h"
#if defined(CONFIG_RWNX_LWIP)
#include "wlan_if.h"
#endif
#include "rawdata_if.h"
#include "fhost_config.h"
#include "rtos_al.h"
#include "co_endian.h"
#include <string.h>
//#include "dma_generic.h"
//#include "dma_api.h"

/// Offset of the VIF index field
#define RX_FLAGS_VIF_INDEX_OFT  8
/// Mask of the VIF index field
#define RX_FLAGS_VIF_INDEX_MSK  (0xFF << RX_FLAGS_VIF_INDEX_OFT)
/// Offset of the STA index field
#define RX_FLAGS_STA_INDEX_OFT  16
/// Mask of the STA index field
#define RX_FLAGS_STA_INDEX_MSK  (0xFF << RX_FLAGS_STA_INDEX_OFT)
/// Offset of the destination STA index field
#define RX_FLAGS_DST_INDEX_OFT  24
/// Mask of the destination STA index field
#define RX_FLAGS_DST_INDEX_MSK  (0xFF << RX_FLAGS_DST_INDEX_OFT)

/// Bitmask indicating that a received packet is not a MSDU
#define RX_FLAGS_NON_MSDU_MSK        (RX_FLAGS_IS_AMSDU_BIT | RX_FLAGS_IS_MPDU_BIT |     \
                                      RX_FLAGS_4_ADDR_BIT | RX_FLAGS_NEW_MESH_PEER_BIT)

#if PLF_RSSI_DATAPKT
static int8_t rssi_saved = 0;
static int8_t sta_rssi_saved[NX_REMOTE_STA_MAX] = {0x7F};
#endif /* PLF_RSSI_DATAPKT */
#if NX_CSI
uint32_t recvec_saved[6] = { 0 };
#endif /* NX_CSI */
#if !defined(CFG_DEVICE_IPC)
static uint16_t datarate_saved = 0;
#endif

#if PLF_RSSI_DATAPKT
int8_t data_pkt_rssi_get(void)
{
    return rssi_saved;
}

int8_t sta_data_pkt_rssi_get(uint8_t *mac_addr)
{
    uint8_t index = fhost_search_itf_idx(VIF_AP);
    struct vif_info_tag *mac_vif = NULL;

    if (index >= NX_VIRT_DEV_MAX) {
        return 0x7F;
    }

    mac_vif = fhost_env.vif[index].mac_vif;
    if (mac_vif && (VIF_AP == mac_vif->type)) {
        struct mac_addr mac;
        MAC_ADDR_CPY(mac.array, mac_addr);
        uint8_t staid = vif_mgmt_get_staid(mac_vif, &mac);
        if(staid < NX_REMOTE_STA_MAX) {
            return sta_rssi_saved[staid];
        }
    }
    return 0x7F;
}
void sta_data_pkt_rssi_set(uint8_t *addr, int8_t rssi)
{
    uint8_t index = fhost_search_itf_idx(VIF_AP);
    struct vif_info_tag *mac_vif = NULL;

    if (index >= NX_VIRT_DEV_MAX) {
        return;
    }

    mac_vif = fhost_env.vif[index].mac_vif;
    if (mac_vif && (VIF_AP == mac_vif->type)) {
        struct mac_addr mac;
        MAC_ADDR_CPY(mac.array, addr);
        uint8_t staid = vif_mgmt_get_staid(mac_vif, &mac);
        if(staid < NX_REMOTE_STA_MAX) {
            sta_rssi_saved[staid] = rssi;
        }
    }
}
#endif /* PLF_RSSI_DATAPKT */

#if !defined(CFG_DEVICE_IPC)
void data_rate_parsing_config(uint8_t en)
{
    fhost_usr_cfg.parse_rx_datarate_en = en;
}

uint16_t data_rate_get(void)
{
    return datarate_saved;
}

#if defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF)
#ifndef CGF_HOSTIF_OPT
uint32_t host_e2a_data_wait_ms = 0;
#endif
int rwnx_rxbuf_filtered(struct fhost_rx_buf_tag *rx_buf)
{
    int is_filtered = 0; // none-zero means the rx pkt buf handled by MCU
    struct mac_hdr *machdr_ptr = (struct mac_hdr *)rx_buf->payload;
    // process data frame
    if ((machdr_ptr->fctl & MAC_FCTRL_TYPE_MASK) == MAC_FCTRL_DATA_T) {
        uint8_t *data = (uint8_t *)rx_buf->payload;
        uint16_t prot_type = 0;
        uint8_t protocol = 0;
        uint16_t port_num = 0;
        uint16_t prot_type_offset, protocol_offset, port_num_offset;
        prot_type_offset = machdr_len_get(machdr_ptr->fctl);
        switch (rx_buf->info.vect.statinfo & RX_HD_DECRSTATUS)
        {
            case RX_HD_DECR_CCMP128:
            case RX_HD_DECR_TKIP:
                prot_type_offset += MAC_IV_LEN + MAC_EIV_LEN;
                break;
            case RX_HD_DECR_WEP:
                prot_type_offset += MAC_IV_LEN;
                break;
            default:
                break;
        }
        protocol_offset = port_num_offset = prot_type_offset;
        prot_type_offset += offsetof(struct llc_snap, proto_id);
        //memcpy(&prot_type, &data[prot_type_offset], 2);
        prot_type = (data[prot_type_offset + 1] << 8) | data[prot_type_offset];

        if (co_ntohs(prot_type) == LLC_ETHERTYPE_EAP_T) { // eapol packet
            is_filtered = 1;
        } else if (co_ntohs(prot_type) == LLC_ETHERTYPE_IP) { // ip packet
            struct co_list *used_list;
            ip_packet_filter_t *filter;
            rtos_mutex_lock(user_filter.list_mutex, -1);
            used_list = &user_filter.used_list;
            filter = (ip_packet_filter_t *)co_list_pick(used_list);
            if (filter) {
                port_num_offset += 30;
                protocol_offset += 17;
                port_num  = (data[port_num_offset + 1] << 8) | data[port_num_offset];
                protocol = data[protocol_offset];
            }
            while (filter) {
                //dbg("F %02X %02X\r\n", filter->destination_port, filter->protocol);
                if ((filter->protocol == protocol) && (filter->dst_port == co_ntohs(port_num))) {
                    is_filtered = 1;
                    break;
                }
                filter = (ip_packet_filter_t *)co_list_next((struct co_list_hdr *)filter);
            }
            rtos_mutex_unlock(user_filter.list_mutex);
        }
    } else {
        is_filtered = 1; // filter mgmt/ctrl frame, such as Beacon/ProbeRsp etc.
    }
    return is_filtered;
}

/**
 * rwnx_rxbuf_filtered() - filter rx pkg
 *
 * @rx_buf:  rx pkg buffer
 * @ return:
 *           VNET_TRANSFER_MCU_HOST    -> send to mcu & linux-host
 *           VNET_TRANSFER_MCU_ONLY    -> send to mcu only
 *           VNET_TRANSFER_HOST_ONLY   -> send to linux-host only
 *           VNET_TRANSFER_RESEND_ONLY -> resend (AP-mode)
 *
 * This function distinguish whether send the pkg to mcu or linux-host or mcu & linux-host.
 */
int rwnx_rxbuf_shared_filtered(struct fhost_rx_buf_tag *rx_buf, struct mac_addr *da, uint8_t *machdr_len)
{
    int is_filtered = VNET_TRANSFER_HOST_ONLY;
    struct mac_hdr *machdr_ptr = (struct mac_hdr *)rx_buf->payload;
    // process data frame
    if ((machdr_ptr->fctl & MAC_FCTRL_TYPE_MASK) == MAC_FCTRL_DATA_T) {
        #ifdef CFG_SOFTAP
        if (wlan_get_softap_status()) {
            int vif_idx;
            struct fhost_vif_tag *fhost_vif;
            struct rx_info *info =&rx_buf->info;
            vif_idx = (info->flags & RX_FLAGS_VIF_INDEX_MSK) >> RX_FLAGS_VIF_INDEX_OFT;
            fhost_vif = fhost_from_mac_vif(vif_idx);
            if (fhost_vif == NULL) {
                dbg("rxdata invalid vif_idx=%x\n", vif_idx);
                //fhost_rx_buf_push(buf);
                return -1;
            }
            *machdr_len = MAC_SHORT_MAC_HDR_LEN + MAC_HDR_QOS_CTRL_LEN;
            if (machdr_ptr->fctl & MAC_FCTRL_ORDER) {
                *machdr_len += MAC_HTCTRL_LEN;
            }

            #if 0
            dbg("%s:\n", __func__);
            char *data = *da;
            dbg("da: %x.%x.%x.%x.%x.%x\n", data[0], data[1], data[2], data[3], data[4], data[5]);
            #endif

            // Judge whether broadcast or unicast pkt inside the BSS.
            if (fhost_vif->mac_vif && fhost_vif->mac_vif->type == VIF_AP) {
                if (MAC_ADDR_GROUP(da)) {
                    /* broadcast pkt need to be forwared to upper layer and resent
                       on wireless interface */
                    //dbg("broadcast\n");
                    is_filtered = VNET_TRANSFER_MCU_HOST;
                    goto finish;
                } else {
                    /* unicast pkt for STA inside the BSS, no need to forward to upper
                       layer simply resend on wireless interface */
                    int dst_idx = (info->flags & RX_FLAGS_DST_INDEX_MSK) >> RX_FLAGS_DST_INDEX_OFT;
                    if (dst_idx != INVALID_STA_IDX) {
                        uint8_t staid = vif_mgmt_get_staid(fhost_vif->mac_vif, da);
                        if(staid < NX_REMOTE_STA_MAX) {
                            struct sta_info_tag *sta = vif_mgmt_get_sta_by_staid(staid);
                            if (sta && sta->valid) {
                                //dbg("unicast pkt sta\n");
                                is_filtered = VNET_TRANSFER_RESEND_ONLY;
                                goto finish;
                            }
                        }
                    }
                }
            }

            // Judge whether send to host or resend.
            fhost_vif = fhost_env.mac2fhost_vif[vif_idx];
            if (MAC_ADDR_CMP(da, &fhost_vif->mac_addr)) {
                is_filtered = VNET_TRANSFER_HOST_ONLY;
            } else {
                is_filtered = VNET_TRANSFER_RESEND_ONLY;
            }

            // If is_filtered == VNET_TRANSFER_HOST_ONLY, continue to filter below.
            if (is_filtered != VNET_TRANSFER_HOST_ONLY) {
                goto finish;
            }
        }
        #endif /* CFG_SOFTAP */

        uint8_t *data = (uint8_t *)rx_buf->payload;
        uint16_t prot_type = 0;
        uint8_t  protocol = 0;
        uint16_t des_port_num = 0;
        uint16_t src_port_num = 0;
        //uint16_t arp_type = 0;
        uint16_t prot_type_offset, protocol_offset, port_num_offset;
        prot_type_offset = machdr_len_get(machdr_ptr->fctl);
        switch (rx_buf->info.vect.statinfo & RX_HD_DECRSTATUS)
        {
            case RX_HD_DECR_CCMP128:
            case RX_HD_DECR_TKIP:
                prot_type_offset += MAC_IV_LEN + MAC_EIV_LEN;
                break;
            case RX_HD_DECR_WEP:
                prot_type_offset += MAC_IV_LEN;
                break;
            default:
                break;
        }
        protocol_offset = port_num_offset = prot_type_offset;
        ////dbg("base offset; %d\n", protocol_offset);
        prot_type_offset += offsetof(struct llc_snap, proto_id);
        ////dbg("prot_type_offset: %d\n", prot_type_offset);
        //memcpy(&prot_type, &data[prot_type_offset], 2);
        prot_type = (data[prot_type_offset + 1] << 8) | data[prot_type_offset];

        if (co_ntohs(prot_type) == LLC_ETHERTYPE_EAP_T) { // eapol packet
            is_filtered = VNET_TRANSFER_MCU_ONLY;
        } else if (co_ntohs(prot_type) == LLC_ETHERTYPE_IP) { // ip packet
            uint8_t icmp_type = 0;
            uint32_t ip_addr = 0;
            struct co_list *used_list;
            ip_packet_filter_t *filter;

            // ICMP
            protocol_offset += 17;
            protocol = data[protocol_offset];
            if (protocol == 1) {
                icmp_type = data[protocol_offset + 11];
                //dbg("ICMP_type: %x\n", icmp_type);
                if (icmp_type == 8) { // icmp request
                    is_filtered = VNET_TRANSFER_MCU_ONLY;
                } else {
                    is_filtered = VNET_TRANSFER_MCU_HOST;
                }
                return is_filtered;
            }

            rtos_mutex_lock(user_filter.list_mutex, -1);
            used_list = &user_filter.used_list;
            filter = (ip_packet_filter_t *)co_list_pick(used_list);
            if (filter) {
                port_num_offset += 30;
                //protocol_offset += 17;
                //protocol = data[protocol_offset];

                src_port_num = data[port_num_offset - 1] | (data[port_num_offset - 2] << 8);
                des_port_num = data[port_num_offset + 1] | (data[port_num_offset] << 8);
                //dbg("des_port_num: %d, %x\n", co_ntohs(des_port_num), des_port_num);
                //dbg("src_port_num: %d, %x\n", co_ntohs(src_port_num), src_port_num);

                ip_addr = data[protocol_offset + 3] | data[protocol_offset + 4]<<8 |
                          data[protocol_offset + 5]<<16 | data[protocol_offset + 6]<<24;
            }
            while (filter) {
                if (PACKET_FILTER_MASK_SRC_IP == filter->filter_mask) {
                    if (filter->src_ipaddr == ip_addr) {
                        is_filtered = VNET_TRANSFER_MCU_ONLY;
                        break;
                    }
                } else if ((PACKET_FILTER_MASK_SRC_IP|PACKET_FILTER_MASK_SRC_PORT) == filter->filter_mask) {
                    if ((filter->src_ipaddr == ip_addr) && (filter->src_port == src_port_num)) {
                        is_filtered = VNET_TRANSFER_MCU_ONLY;
                        break;
                    }
                } else if ((PACKET_FILTER_MASK_PROTOCOL|PACKET_FILTER_MASK_SRC_PORT) == filter->filter_mask) {
                    if ((filter->protocol == protocol) && (filter->src_port == src_port_num)) {
                        is_filtered = VNET_TRANSFER_MCU_ONLY;
                        break;
                    }
                } else if ((PACKET_FILTER_MASK_PROTOCOL|PACKET_FILTER_MASK_DST_PORT) == filter->filter_mask) {
                    if ((filter->protocol == protocol) && (filter->dst_port == des_port_num)) {
                        is_filtered = VNET_TRANSFER_MCU_ONLY;
                        break;
                    }
                } else if ((PACKET_FILTER_MASK_SRC_IP|PACKET_FILTER_MASK_PROTOCOL|PACKET_FILTER_MASK_SRC_PORT)
                            == filter->filter_mask) {
                    if ((filter->src_ipaddr == ip_addr) && (filter->protocol == protocol) && (filter->src_port == src_port_num)) {
                        is_filtered = VNET_TRANSFER_MCU_ONLY;
                        break;
                    }
                } else if (PACKET_FILTER_MASK_SHARE_DNS_PORT == filter->filter_mask) {
                    if (filter->src_port == src_port_num) {
                        is_filtered = VNET_TRANSFER_MCU_HOST;
                        break;
                    }
                } else {
                    //
                }
                filter = (ip_packet_filter_t *)co_list_next((struct co_list_hdr *)filter);
            }
            rtos_mutex_unlock(user_filter.list_mutex);
        }else if (co_ntohs(prot_type) == LLC_ETHERTYPE_ARP) { // arp packet
            //arp_type = (data[prot_type_offset + 9] << 8) | (data[prot_type_offset + 8]);
            //dbg("arp_type: %x\n", arp_type);
            is_filtered = VNET_TRANSFER_MCU_HOST;
        }
    } else {
        // filter mgmt/ctrl frame, such as Beacon/ProbeRsp etc.
        is_filtered = VNET_TRANSFER_MCU_ONLY;
    }

finish:
    return is_filtered;
}

void send_pkg_to_host(struct rx_info *info)
{
    #ifdef CFG_HOSTIF_OPT
    //forwards rx dscr & 802.11 data to host for reorder
    e2a_data_send_direct((uint8_t *)info, (sizeof(struct rx_info) + info->vect.frmlen));

    #else /* CFG_HOSTIF_OPT */
    //dbg("%s %d\r\n", __func__, (sizeof(struct rx_info) + info->vect.frmlen));
    //dump((uint8_t *)info, 64);
    do {
        //forwards rx dscr & 802.11 data to host for reorder
        int ret = e2a_data_send((uint8_t *)info, (sizeof(struct rx_info) + info->vect.frmlen));
        if (ret < 0) {
            rtos_task_suspend(1);
            host_e2a_data_wait_ms++;
            if (host_e2a_data_wait_ms > 100) {
                dbg("e2a_d:%x\n", host_e2a_data_wait_ms);
                host_e2a_data_wait_ms = 0;
                break; // drop current pkt
            }
        } else {
            host_e2a_data_wait_ms = 0;
            break;
        }
    } while (1);
    #endif /* CFG_HOSTIF_OPT */
}
#endif

#if (AICWF_RWNX_TIMER_EN)
#define DBG_TIMER(...) do {} while (0)
#define WRN_TIMER(...) do {} while (0)
#define RWNX_TIMER_COUNT    10

struct rwnx_timer_tag {
    struct co_list free_list;
    struct co_list post_list;
    struct co_list stop_list;
    rtos_queue task_queue;
    rtos_mutex task_mutex;
    rtos_task_handle task_handle;
};

struct rwnx_timer_msg_s {
    rwnx_timer_handle hdl;
    enum rwnx_timer_action_e action;
};

struct rwnx_timer_node_s rwnx_timer_node_pool[RWNX_TIMER_COUNT];
struct rwnx_timer_tag rwnx_timer_env;

bool rwnx_timer_cmp(struct co_list_hdr const *elementA,
                    struct co_list_hdr const *elementB)
{
    const rwnx_timer_handle hdlA = (rwnx_timer_handle)elementA;
    const rwnx_timer_handle hdlB = (rwnx_timer_handle)elementB;
    bool ret = false;
    if ((int)(hdlA->expired_ms - hdlB->expired_ms) < 0) {
        ret = true;
    }
    return ret;
}

void rwnx_timer_task(void *arg)
{
    struct rwnx_timer_tag *timer_env = arg;
    rwnx_timer_handle timer_hdl = NULL;
    int ret, next_to_ms = -1;
    uint32_t cur_time_ms;
    struct rwnx_timer_msg_s msg;
    #ifdef CONFIG_RWNX_TIMER_TASK_TS
    uint32_t start_time = 0;
    uint32_t end_time = 0;
    static volatile uint8_t tmr_count = 0;
    #endif
    while (1) {
        DBG_TIMER("bef rd, next_to_ms=%d\n",next_to_ms);
        ret = rtos_queue_read(timer_env->task_queue, &msg, next_to_ms, false);
        #ifdef CONFIG_RWNX_TIMER_TASK_TS
        tmr_count++;
        start_time = rtos_now(0);
        dbg("tmr_in:%u/%u\n", start_time, tmr_count);
        #endif
        timer_hdl = msg.hdl;
        cur_time_ms = rtos_now(false);
        DBG_TIMER("aft rd, timer_hdl=%p, ret=%x\n",timer_hdl,ret);
        rtos_mutex_lock(timer_env->task_mutex, -1);
        if (ret == 0) { // create/delete/start/stop action
            if (msg.action == RWNX_TIMER_ACTION_CREATE) {
                if (timer_hdl->state == RWNX_TIMER_STATE_FREE) {
                    if (timer_hdl->auto_load) {
                        co_list_insert(&timer_env->post_list, &timer_hdl->hdr, rwnx_timer_cmp);
                        timer_hdl->state = RWNX_TIMER_STATE_POST;
                    } else {
                        //co_list_push_back(&timer_env->stop_list, &timer_hdl->hdr);
                        co_list_insert(&timer_env->stop_list, &timer_hdl->hdr, rwnx_timer_cmp);
                        timer_hdl->state = RWNX_TIMER_STATE_STOP;
                    }
                } else {
                    WRN_TIMER("rwnx_timer created but not free: [%p] %x\n", timer_hdl, timer_hdl->state);
                }
            } else if (msg.action == RWNX_TIMER_ACTION_START) {
                if (timer_hdl->state == RWNX_TIMER_STATE_STOP) {
                    co_list_extract(&timer_env->stop_list, &timer_hdl->hdr);
                    co_list_insert(&timer_env->post_list, &timer_hdl->hdr, rwnx_timer_cmp);
                    timer_hdl->state = RWNX_TIMER_STATE_POST;
                } else {
                    WRN_TIMER("rwnx_timer: try to start none-stoped one: [%p] %x\n", timer_hdl, timer_hdl->state);
                }
            } else if (msg.action == RWNX_TIMER_ACTION_RESTART) {
                if (timer_hdl->state == RWNX_TIMER_STATE_POST) {
                    co_list_extract(&timer_env->post_list, &timer_hdl->hdr);
                    co_list_insert(&timer_env->post_list, &timer_hdl->hdr, rwnx_timer_cmp);
                    msg.action = RWNX_TIMER_ACTION_START;
                } else {
                    WRN_TIMER("rwnx_timer: try to restart none-posting one: [%p] %x\n", timer_hdl, timer_hdl->state);
                }
            } else if (msg.action == RWNX_TIMER_ACTION_STOP) {
                if (timer_hdl->state == RWNX_TIMER_STATE_POST) {
                    co_list_extract(&timer_env->post_list, &timer_hdl->hdr);
                    co_list_insert(&timer_env->stop_list, &timer_hdl->hdr, rwnx_timer_cmp);
                    timer_hdl->state = RWNX_TIMER_STATE_STOP;
                } else {
                    WRN_TIMER("rwnx_timer: try to stop none-post one: [%p] %x\n", timer_hdl, timer_hdl->state);
                }
            } else if (msg.action == RWNX_TIMER_ACTION_DELETE) {
                if (timer_hdl->state == RWNX_TIMER_STATE_POST) {
                    co_list_extract(&timer_env->post_list, &timer_hdl->hdr);
                    co_list_push_back(&timer_env->free_list, &timer_hdl->hdr);
                    timer_hdl->state = RWNX_TIMER_STATE_FREE;
                } else if (timer_hdl->state == RWNX_TIMER_STATE_STOP) {
                    co_list_extract(&timer_env->stop_list, &timer_hdl->hdr);
                    co_list_push_back(&timer_env->free_list, &timer_hdl->hdr);
                    timer_hdl->state = RWNX_TIMER_STATE_FREE;
                } else {
                    WRN_TIMER("rwnx_timer: try to delete free one: [%p] %x\n", timer_hdl, timer_hdl->state);
                }
            } else {
                WRN_TIMER("rwnx_timer action invalid, [%p] %x\n", timer_hdl, msg.action);
            }
        } else if (ret == 1) { // timed-out, callback funcs
            #if 1
            do {
                timer_hdl = (rwnx_timer_handle)co_list_pick(&timer_env->post_list);
                if (timer_hdl) {
                    if (timer_hdl->expired_ms <= cur_time_ms) {
                        timer_hdl = (rwnx_timer_handle)co_list_pop_front(&timer_env->post_list);
                        co_list_insert(&timer_env->stop_list, &timer_hdl->hdr, rwnx_timer_cmp);
                        timer_hdl->state = RWNX_TIMER_STATE_STOP;
                        DBG_TIMER("rwnx_timer process1: %p\n",timer_hdl);
                        (timer_hdl->cb)(timer_hdl->arg); // callback func
                    } else {
                        break;
                    }
                }
            } while (timer_hdl);
            #endif
        } /* else if (ret != TX_QUEUE_EMPTY) {
            WRN_TIMER("rwnx_timer queue read fail, ret = %x\n", ret);
            if (ret == TX_QUEUE_ERROR) {
                WRN_TIMER("TX_QUEUE_ERROR\n");
                break;
            }
        } */
        #if 1
        do {
            timer_hdl = (rwnx_timer_handle)co_list_pick(&timer_env->post_list);
            if (timer_hdl) {
                if (timer_hdl->expired_ms <= cur_time_ms) {
                    timer_hdl = (rwnx_timer_handle)co_list_pop_front(&timer_env->post_list);
                    co_list_insert(&timer_env->stop_list, &timer_hdl->hdr, rwnx_timer_cmp);
                    timer_hdl->state = RWNX_TIMER_STATE_STOP;
                    DBG_TIMER("rwnx_timer process2: %p, %d<=%d\n",timer_hdl,timer_hdl->expired_ms,cur_time_ms);
                    (timer_hdl->cb)(timer_hdl->arg); // callback func
                } else {
                    break;
                }
            }
        } while (timer_hdl);
        #endif
        timer_hdl = (rwnx_timer_handle)co_list_pick(&timer_env->post_list);
        if (timer_hdl == NULL) {
            next_to_ms = -1;
        } else {
            next_to_ms = (int)(timer_hdl->expired_ms - cur_time_ms);
            if (next_to_ms <= 0) {
                WRN_TIMER("expired timer is not processed, %x, %x\n", timer_hdl->expired_ms, cur_time_ms);
                next_to_ms = 1;
            }
        }
        rtos_mutex_unlock(timer_env->task_mutex);

        #ifdef CONFIG_RWNX_TIMER_TASK_TS
        end_time = rtos_now(0);
        dbg("tmr_out:%u/%u\n", end_time, tmr_count);
        #endif
    }
}

void rwnx_timer_init(void)
{
    int ret, idx;
    struct rwnx_timer_tag *timer_env = &rwnx_timer_env;
    rwnx_timer_handle timer_hdl;
    co_list_init(&timer_env->free_list);
    for (idx = 0; idx < RWNX_TIMER_COUNT; idx++) {
        struct rwnx_timer_node_s timer_node_void = {{NULL},};
        timer_hdl = &rwnx_timer_node_pool[idx];
        *timer_hdl = timer_node_void;
        co_list_push_back(&timer_env->free_list, &timer_hdl->hdr);
    }
    co_list_init(&timer_env->post_list);
    co_list_init(&timer_env->stop_list);
    ret = rtos_queue_create(sizeof(struct rwnx_timer_msg_s), RWNX_TIMER_COUNT * 10, &timer_env->task_queue);
    if (ret < 0) {
        WRN_TIMER("rwnx_timer queue create fail\n");
        return;
    }
    ret = rtos_mutex_create(&timer_env->task_mutex);
    if (ret < 0) {
        WRN_TIMER("rwnx_timer mutex create fail\n");
        return;
    }
    ret = rtos_task_create(rwnx_timer_task, "rwnx_timer_task",
                           67, 1024,
                           (void*)timer_env, RTOS_TASK_PRIORITY(1),
                           &timer_env->task_handle);
    if (ret < 0) {
        WRN_TIMER("rwnx_timer_task create fail\n");
        return;
    }
}

void rwnx_timer_deinit(void)
{
    ///TBD:
}

int rwnx_timer_create(rwnx_timer_handle *timer_ptr, uint32_t period_ms,
                      void *arg, rwnx_timer_cb_t cb,
                      bool auto_load, bool periodic)
{
    int ret = 0;
    rwnx_timer_handle timer_hdl = NULL;
    struct rwnx_timer_tag *timer_env = &rwnx_timer_env;
    struct rwnx_timer_msg_s msg;
    rtos_mutex_lock(timer_env->task_mutex, -1);
    do {
        timer_hdl = (rwnx_timer_handle)co_list_pop_front(&timer_env->free_list);
        if (timer_hdl == NULL) {
            WRN_TIMER("rwnx_timer create fail\n");
            ret = -1;
            break;
        }
        timer_hdl->cb = cb;
        timer_hdl->arg = arg;
        timer_hdl->expired_ms = rtos_now(false) + period_ms;
        timer_hdl->periodic = periodic;
        timer_hdl->auto_load = auto_load;
        msg.action = RWNX_TIMER_ACTION_CREATE;
        msg.hdl = timer_hdl;
        DBG_TIMER("rwnx_timer_create, timer_hdl=%p, ms=%d\n",timer_hdl,timer_hdl->expired_ms);
        ret = rtos_queue_write(timer_env->task_queue, &msg, 0, false); // to be confirmed
        if (ret) {
            WRN_TIMER("rwnx_timer_create queue write fail, ret=%x\n", ret);
            co_list_push_back(&timer_env->free_list, &timer_hdl->hdr);
            ret = -2;
            break;
        }
        *timer_ptr = timer_hdl;
    } while (0);
    rtos_mutex_unlock(timer_env->task_mutex);
    return ret;
}

int rwnx_timer_start(rwnx_timer_handle timer_hdl, uint32_t period_ms, bool lock)
{
    int ret = 0;
    if ((timer_hdl < &rwnx_timer_node_pool[0]) || (timer_hdl > &rwnx_timer_node_pool[RWNX_TIMER_COUNT - 1])) {
        WRN_TIMER("rwnx_timer_start invalid handle=%p\n", timer_hdl);
        ret = -1; // invalid ptr
    } else {
        struct rwnx_timer_tag *timer_env = &rwnx_timer_env;
        struct rwnx_timer_msg_s msg;
        if (lock) {
            rtos_mutex_lock(timer_env->task_mutex, -1);
        }
        timer_hdl->expired_ms = rtos_now(false) + period_ms;
        msg.action = RWNX_TIMER_ACTION_START;
        msg.hdl = timer_hdl;
        DBG_TIMER("rwnx_timer_start, timer_hdl=%p, ms=%d\n",timer_hdl,timer_hdl->expired_ms);
        ret = rtos_queue_write(timer_env->task_queue, &msg, 0, false); // to be confirmed
        if (ret) {
            WRN_TIMER("rwnx_timer_start queue write fail, ret=%x\n", ret);
            ret = -2;
        }
        if (lock) {
            rtos_mutex_unlock(timer_env->task_mutex);
        }
    }
    return ret;
}

int rwnx_timer_restart(rwnx_timer_handle timer_hdl, uint32_t period_ms)
{
    int ret = 0;
    if ((timer_hdl < &rwnx_timer_node_pool[0]) || (timer_hdl > &rwnx_timer_node_pool[RWNX_TIMER_COUNT - 1])) {
        WRN_TIMER("rwnx_timer_start invalid handle=%p\n", timer_hdl);
        ret = -1; // invalid ptr
    } else {
        struct rwnx_timer_tag *timer_env = &rwnx_timer_env;
        struct rwnx_timer_msg_s msg;
        rtos_mutex_lock(timer_env->task_mutex, -1);
        timer_hdl->expired_ms = rtos_now(false) + period_ms;
        //if (msg.action != RWNX_TIMER_ACTION_RESTART) {
            msg.action = RWNX_TIMER_ACTION_RESTART;
            msg.hdl = timer_hdl;
            DBG_TIMER("rwnx_timer_restart, timer_hdl=%p, ms=%d\n",timer_hdl,timer_hdl->expired_ms);
            ret = rtos_queue_write(timer_env->task_queue, &msg, 0, false); // to be confirmed
            if (ret) {
                WRN_TIMER("rwnx_timer_start queue write fail, ret=%x\n", ret);
                ret = -2;
            }
        //}
        rtos_mutex_unlock(timer_env->task_mutex);
    }
    return ret;
}

int rwnx_timer_stop(rwnx_timer_handle timer_hdl)
{
    int ret = 0;
    if ((timer_hdl < &rwnx_timer_node_pool[0]) || (timer_hdl > &rwnx_timer_node_pool[RWNX_TIMER_COUNT - 1])) {
        WRN_TIMER("rwnx_timer_stop invalid handle=%p\n", timer_hdl);
        ret = -1; // invalid ptr
    } else {
        struct rwnx_timer_tag *timer_env = &rwnx_timer_env;
        struct rwnx_timer_msg_s msg;
        rtos_mutex_lock(timer_env->task_mutex, -1);
        msg.action = RWNX_TIMER_ACTION_STOP;
        msg.hdl = timer_hdl;
        DBG_TIMER("rwnx_timer_stop, timer_hdl=%p\n",timer_hdl);
        ret = rtos_queue_write(timer_env->task_queue, &msg, 0, false); // to be confirmed
        if (ret) {
            WRN_TIMER("rwnx_timer_stop queue write fail, ret=%x\n", ret);
            ret = -2;
        }
        rtos_mutex_unlock(timer_env->task_mutex);
    }
    return ret;
}

int rwnx_timer_delete(rwnx_timer_handle timer_hdl)
{
    int ret = 0;
    if ((timer_hdl < &rwnx_timer_node_pool[0]) || (timer_hdl > &rwnx_timer_node_pool[RWNX_TIMER_COUNT - 1])) {
        WRN_TIMER("rwnx_timer_delete invalid handle=%p\n", timer_hdl);
        ret = -1; // invalid ptr
    } else {
        struct rwnx_timer_tag *timer_env = &rwnx_timer_env;
        struct rwnx_timer_msg_s msg;
        rtos_mutex_lock(timer_env->task_mutex, -1);
        msg.action = RWNX_TIMER_ACTION_DELETE;
        msg.hdl = timer_hdl;
        DBG_TIMER("rwnx_timer_delete, timer_hdl=%p\n",timer_hdl);
        ret = rtos_queue_write(timer_env->task_queue, &msg, 0, false); // to be confirmed
        if (ret) {
            WRN_TIMER("rwnx_timer_stop queue write fail, ret=%x\n", ret);
            ret = -2;
        }
        rtos_mutex_unlock(timer_env->task_mutex);
    }
    return ret;
}

bool rwnx_timer_is_posted(rwnx_timer_handle timer_hdl)
{
    bool posted = false;
    if ((timer_hdl < &rwnx_timer_node_pool[0]) || (timer_hdl > &rwnx_timer_node_pool[RWNX_TIMER_COUNT - 1])) {
        WRN_TIMER("rwnx_timer_is_posted invalid handle=%p\n", timer_hdl);
    } else {
        struct rwnx_timer_tag *timer_env = &rwnx_timer_env;
        rtos_mutex_lock(timer_env->task_mutex, -1);
        if (timer_hdl->state == RWNX_TIMER_STATE_POST) {
            posted = true;
        }
        rtos_mutex_unlock(timer_env->task_mutex);
    }
    return posted;
}
#endif


#if (AICWF_RX_REORDER)
#define WRN_REORD(...) do {} while (0)
#define DBG_REORD(...) do {} while (0)
struct co_list stas_reord_list;
rtos_mutex stas_reord_lock;

void reord_rxframe_free(struct recv_msdu *rxframe)
{
    rtos_free(rxframe->rx_buf);
    rtos_free(rxframe);
}

struct recv_msdu *reord_rxframe_alloc(struct fhost_rx_buf_tag *buf, uint16_t seq_num, uint8_t tid, uint8_t forward)
{
    struct recv_msdu *rxframe;
    struct fhost_rx_buf_tag *rx_buf;
    //uint8_t *data = (uint8_t *)buf;
    uint16_t buf_len = sizeof(struct fhost_rx_buf_tag);//sizeof(struct rx_info) + (*data | (*(data + 1) << 8));
    rxframe = rtos_malloc(sizeof(struct recv_msdu));
    if (rxframe == NULL) {
        dbg("rxframe alloc fail\n");
        fhost_rx_buf_push(buf);
        return NULL;
    }
    rx_buf = rtos_malloc(buf_len);
    if (rx_buf == NULL) {
        rtos_free(rxframe);
        fhost_rx_buf_push(buf);
        dbg("rxframe buf alloc fail\n");
        return NULL;
    }
    #if 1
    memcpy(rx_buf, buf, buf_len);
    #else
    dma_desc_t dma_desc = {0};
    memset(&dma_desc, 0, (sizeof(dma_desc_t)));
    dma_desc.SAR = (uint32_t)buf;
    dma_desc.DAR = (uint32_t)rx_buf;
    dma_desc_length_set(&dma_desc, buf_len);
    dma_desc.LNAR = 0;

    dma_push(&dma_desc, &dma_desc, DMA_CHANNEL_WIFI_DATA_RX);
    dma_lli_poll(DMA_CHANNEL_WIFI_DATA_RX);
    dma_ch_int_clear(DMA_CHANNEL_WIFI_DATA_RX);
    #endif
    rxframe->rx_buf = rx_buf;
    rxframe->buf_len = buf_len;
    rxframe->seq_num = seq_num;
    rxframe->tid = tid;
    rxframe->forward = forward;

    fhost_rx_buf_push(buf);
    return rxframe;
}

int reord_single_frame_ind(struct recv_msdu *prframe)
{
    DBG_REORD("reord_single_frame_ind:[%x]%d\n", prframe->tid, prframe->seq_num);
    if (prframe->forward) {
        prframe->rx_buf->net_hdr.reord_magic = 0xEA;
        fhost_rx_buf_forward(prframe->rx_buf);
    } else {
        rtos_free(prframe->rx_buf);
    }
    rtos_free(prframe);
    return 0;
}


struct reord_ctrl_info *reord_init_sta(const uint8_t *mac_addr)
{
    int i, ret;
    struct reord_ctrl *preorder_ctrl = NULL;
    struct reord_ctrl_info *reord_info;
    //char reord_list_lock_name[32];
    WRN_REORD("reord_init_sta %02x:%02x:%02x\n", mac_addr[0], mac_addr[1], mac_addr[2]);
    reord_info = rtos_malloc(sizeof(struct reord_ctrl_info));
    if (!reord_info) {
        WRN_REORD("reord_info alloc fail\n");
        return NULL;
    }
    memcpy(reord_info->mac_addr, mac_addr, 6);
    for (i = 0; i < 8; i++) {
        //memset(reord_list_lock_name, 0, sizeof(reord_list_lock_name));
        //dbg_snprintf(reord_list_lock_name, "reord_list_lock%d", i);
        preorder_ctrl = &reord_info->preorder_ctrl[i];
        preorder_ctrl->enable = true;
        preorder_ctrl->wsize_b = AICWF_REORDER_WINSIZE;
        preorder_ctrl->ind_sn = 0xffff;
        preorder_ctrl->list_cnt = 0;
        co_list_init(&preorder_ctrl->reord_list);
        ret = rtos_mutex_create(&preorder_ctrl->reord_list_lock);
        if (ret) {
            WRN_REORD("reord_ctrl[%x] mutex create fail\n", i);
            continue;
        }
        preorder_ctrl->reord_timer = NULL;
    }
    return reord_info;
}

int reord_flush_tid(uint8_t *mac, uint8_t tid)
{
    struct reord_ctrl_info *reord_info;
    struct reord_ctrl *preorder_ctrl = NULL;
    struct recv_msdu *prframe;
    //int ret;
    rtos_mutex_lock(stas_reord_lock, -1);
    reord_info = (struct reord_ctrl_info *)co_list_pick(&stas_reord_list);
    while (reord_info) {
        if (memcmp(mac, reord_info->mac_addr, 6/*ETH_ALEN*/) == 0) {
            preorder_ctrl = &reord_info->preorder_ctrl[tid];
            break;
        }
        reord_info = (struct reord_ctrl_info *)co_list_next(&reord_info->hdr);
    }
    rtos_mutex_unlock(stas_reord_lock);
    if ((NULL == preorder_ctrl) || (false == preorder_ctrl->enable)) { // not found or disabled
        return 0;
    }
    rtos_mutex_lock(preorder_ctrl->reord_list_lock, -1);
    do {
        prframe = (struct recv_msdu*)co_list_pop_front(&preorder_ctrl->reord_list);
        if (prframe == NULL) {
            break;
        }
        reord_single_frame_ind(prframe);
    } while (1);
    WRN_REORD("reord flush:tid=%d", tid);
    preorder_ctrl->enable = false;
    preorder_ctrl->ind_sn = 0xffff;
    preorder_ctrl->list_cnt = 0;
    rtos_mutex_unlock(preorder_ctrl->reord_list_lock);
    //rtos_mutex_delete(preorder_ctrl->reord_list_lock);
    if (preorder_ctrl->reord_timer) {
        #if (AICWF_RWNX_TIMER_EN)
        rwnx_timer_delete(preorder_ctrl->reord_timer);
        #else
        rtos_timer_delete(preorder_ctrl->reord_timer, 0);
        #endif
        preorder_ctrl->reord_timer = NULL;
    }
    return 0;
}

void reord_deinit_sta(struct reord_ctrl_info *reord_info)
{
    int idx;
    uint8_t *mac_addr = &reord_info->mac_addr[0];
    WRN_REORD("reord_deinit_sta %02x:%02x:%02x\n", mac_addr[0], mac_addr[1], mac_addr[2]);
    for (idx = 0; idx < 8; idx++) {
        struct reord_ctrl *preorder_ctrl = &reord_info->preorder_ctrl[idx];
        struct recv_msdu *prframe;
        preorder_ctrl->enable = false;
        rtos_mutex_lock(preorder_ctrl->reord_list_lock, -1);
        do {
            prframe = (struct recv_msdu*)co_list_pop_front(&preorder_ctrl->reord_list);
            if (prframe) {
                reord_rxframe_free(prframe);
            }
        } while (prframe);
        rtos_mutex_unlock(preorder_ctrl->reord_list_lock);
        rtos_mutex_delete(preorder_ctrl->reord_list_lock);
        if (preorder_ctrl->reord_timer) {
            #if (AICWF_RWNX_TIMER_EN)
            rwnx_timer_delete(preorder_ctrl->reord_timer);
            #else
            rtos_timer_delete(preorder_ctrl->reord_timer, 0);
            #endif
            preorder_ctrl->reord_timer = NULL;
        }
    }
    rtos_free(reord_info);
}

void reord_deinit_sta_by_mac(const uint8_t *mac_addr)
{
    struct reord_ctrl_info *reord_info = NULL;

    if(mac_addr != NULL)
        dbg("reord_deinit_sta mac  %02x:%02x:%02x\n",mac_addr[0], mac_addr[1], mac_addr[2]);

    rtos_mutex_lock(stas_reord_lock, -1);
    while(1) {
        reord_info = (struct reord_ctrl_info *)co_list_pick(&stas_reord_list);
        while (reord_info) {

            if(mac_addr == NULL)
                break;

            dbg("reord_deinit_sta_mac find %02x:%02x:%02x\n", reord_info->mac_addr[0], reord_info->mac_addr[1],
                                                                         reord_info->mac_addr[2]);
            if (memcmp(mac_addr, reord_info->mac_addr, 6/*ETH_ALEN*/) == 0) {
                break;
            }
            reord_info = (struct reord_ctrl_info *)co_list_next(&reord_info->hdr);
        }

        if(reord_info != NULL )
        {
            co_list_extract(&stas_reord_list, &reord_info->hdr);
            reord_deinit_sta(reord_info);
            if(mac_addr != NULL)
                break;
        } else {
            break;
        }
    };
    rtos_mutex_unlock(stas_reord_lock);
}

bool reord_rxframes_process(struct reord_ctrl *preorder_ctrl, int bforced)
{
    //struct list_head *phead, *plist;
    struct recv_msdu *prframe;
    bool bPktInBuf = false;
    uint16_t prev_sn = preorder_ctrl->ind_sn;
    if (co_list_is_empty(&preorder_ctrl->reord_list)) {
        return false;
    }
    prframe = (struct recv_msdu *)co_list_pick(&preorder_ctrl->reord_list);
    if (bforced == true && prframe != NULL) {
        preorder_ctrl->ind_sn = prframe->seq_num;
        DBG_REORD("reord force ind_sn=%d,%d\n", preorder_ctrl->ind_sn,prframe->buf_len);
    }
    while (prframe) {
        if (!SN_LESS(preorder_ctrl->ind_sn, prframe->seq_num)) {
            if (SN_EQUAL(preorder_ctrl->ind_sn, prframe->seq_num)) {
                preorder_ctrl->ind_sn = (preorder_ctrl->ind_sn + 1) & 0xFFF;
            }
        } else {
            bPktInBuf = true;
            break;
        }
        prframe = (struct recv_msdu *)co_list_next(&prframe->hdr);
    }
    if (prev_sn != preorder_ctrl->ind_sn) {
        DBG_REORD("reord process set ind_sn=%d\n", preorder_ctrl->ind_sn);
    }
    return bPktInBuf;
}

void reord_rxframes_ind(struct reord_ctrl *preorder_ctrl)
{
    struct co_list *reord_list;
    struct recv_msdu *prframe;
    reord_list = &preorder_ctrl->reord_list;
    rtos_mutex_lock(preorder_ctrl->reord_list_lock, -1);
    if (co_list_is_empty(reord_list)) {
        rtos_mutex_unlock(preorder_ctrl->reord_list_lock);
        return;
    }
    do {
        prframe = (struct recv_msdu *)co_list_pick(reord_list);
        if (!prframe) {
            break;
        } else if (SN_LESS(preorder_ctrl->ind_sn, prframe->seq_num)){
            break;
        }
        co_list_pop_front(reord_list);
        //co_list_extract(reord_list, &prframe->rxframe_list);
        //dbg("single_frame_ind\r\n");
        reord_single_frame_ind(prframe);
        preorder_ctrl->list_cnt--;
    } while (1);
    rtos_mutex_unlock(preorder_ctrl->reord_list_lock);
}

int reord_need_check(struct reord_ctrl *preorder_ctrl, uint16_t seq_num)
{
    uint8_t wsize = preorder_ctrl->wsize_b;
    uint16_t wend = (preorder_ctrl->ind_sn + wsize -1) & 0xFFF;
    if (preorder_ctrl->ind_sn == 0xFFFF) {
        preorder_ctrl->ind_sn = seq_num;
        DBG_REORD("reord chk&set 1 ind_sn=%d\n",preorder_ctrl->ind_sn);
    }
    if (SN_LESS(seq_num, preorder_ctrl->ind_sn)) {
        return -1;
    }
    if (SN_EQUAL(seq_num, preorder_ctrl->ind_sn)) {
        preorder_ctrl->ind_sn = (preorder_ctrl->ind_sn + 1) & 0xFFF;
    } else if (SN_LESS(wend, seq_num)) {
        if (seq_num >= (wsize-1))
            preorder_ctrl->ind_sn = seq_num-(wsize-1);
        else
            preorder_ctrl->ind_sn = 0xFFF - (wsize - (seq_num + 1)) + 1;
    }
    DBG_REORD("reord chk&set 2 ind_sn=%d\n",preorder_ctrl->ind_sn);
    return 0;
}

int reord_rxframe_enqueue(struct reord_ctrl *preorder_ctrl, struct recv_msdu *prframe)
{
    struct co_list *preord_list = &preorder_ctrl->reord_list;
    struct recv_msdu *plframe = (struct recv_msdu *)co_list_pick(preord_list);
    int idx = 0;
    DBG_REORD("reord_enq,sn=%d\n",prframe->seq_num);
    while (plframe) {
        DBG_REORD(" (%d)->%d,%d\n",idx++,plframe->seq_num,plframe->buf_len);
        if (SN_LESS(plframe->seq_num, prframe->seq_num)) {
            plframe = (struct recv_msdu *)co_list_next(&plframe->hdr);
            continue;
        } else if (SN_EQUAL(plframe->seq_num, prframe->seq_num)) {
            WRN_REORD("reord dup, drop sn=%d\n",prframe->seq_num);
            return -1;
        } else {
            break;
        }
    }
    if (plframe) {
        DBG_REORD("reord insert, sn_new=%d bef sn_old=%d\n",prframe->seq_num, plframe->seq_num);
        co_list_insert_before(preord_list, &plframe->hdr, &prframe->hdr);
    } else {
        DBG_REORD("reord push back, sn_new=%d\n",prframe->seq_num);
        co_list_push_back(preord_list, &prframe->hdr);
    }
    preorder_ctrl->list_cnt++;
    return 0;
}

void reord_timeout_worker(struct reord_ctrl *preorder_ctrl)
{
    reord_rxframes_ind(preorder_ctrl);
}

void reord_timeout_handler(void *arg)
{
    struct reord_ctrl *preorder_ctrl = (struct reord_ctrl *)arg;
    DBG_REORD("reord TO\n");
    rtos_mutex_lock(preorder_ctrl->reord_list_lock, -1);
    bool bRet = reord_rxframes_process(preorder_ctrl, true);
    rtos_mutex_unlock(preorder_ctrl->reord_list_lock);
    if (bRet == true) {
        #if (AICWF_RWNX_TIMER_EN)
        if (preorder_ctrl->reord_timer) {
            DBG_REORD("reord_timeout_handler, start timer,ind_sn=%d,cnt=%d\n",preorder_ctrl->ind_sn,preorder_ctrl->list_cnt);
            rwnx_timer_start(preorder_ctrl->reord_timer, REORDER_UPDATE_TIME, false);
        } else {
            WRN_REORD("reord_timeout_handler, null timer handle\n");
        }
        #else
        if (preorder_ctrl->reord_timer) {
            rtos_timer_stop(preorder_ctrl->reord_timer, 0);
            rtos_timer_delete(preorder_ctrl->reord_timer, 0);
            preorder_ctrl->reord_timer = NULL;
        } else {
            WRN_REORD("reord_timeout_handler, null timer handle\n");
        }
        preorder_ctrl->reord_timer = rtos_timer_create("reord_timer",
                                REORDER_UPDATE_TIME, 1, NULL, reord_timeout_handler);
        if (!preorder_ctrl->reord_timer) {
            WRN_REORD("[TO] reord_ctrl timer create fail\n");
        }
        #endif
    }
    reord_timeout_worker(preorder_ctrl);
}

int reord_process_unit(struct fhost_rx_buf_tag *buf, uint16_t seq_num, uint8_t *macaddr, uint8_t tid, uint8_t forward)
{
    int ret;
    struct recv_msdu *pframe;
    struct reord_ctrl *preorder_ctrl = NULL;
    struct reord_ctrl_info *reord_info = NULL;

    #ifdef CONFIG_REORD_PROCESS_UNIT_TS
    uint32_t start_time = 0;
    uint32_t end_time = 0;
    static volatile uint8_t reord_count = 0;
    #endif

    #ifdef CONFIG_REORD_PROCESS_UNIT_TS
    reord_count++;
    start_time = rtos_now(0);
    dbg("reo_in:%u/%u\n", start_time, reord_count);
    #endif

    pframe = reord_rxframe_alloc(buf, seq_num, tid, forward);
    if (pframe == NULL) {
        dbg("reord rxframe alloc fail\n");
        return -1;
    }
    rtos_mutex_lock(stas_reord_lock, -1);
    reord_info = (struct reord_ctrl_info *)co_list_pick(&stas_reord_list);
    while (reord_info) {
        if (memcmp(macaddr, reord_info->mac_addr, 6) == 0) {
            preorder_ctrl = &reord_info->preorder_ctrl[tid];
            break;
        }
        reord_info = (struct reord_ctrl_info *)co_list_next(&reord_info->hdr);
    }
    if (preorder_ctrl == NULL) {
        reord_info = reord_init_sta(macaddr);
        if (!reord_info) {
            dbg("reord init fail\n");
            rtos_mutex_unlock(stas_reord_lock);
            return -1;
        }
        co_list_push_back(&stas_reord_list, &reord_info->hdr);
        preorder_ctrl = &reord_info->preorder_ctrl[tid];
    } else {
        if (preorder_ctrl->enable == false) {
            preorder_ctrl->enable = true;
            preorder_ctrl->ind_sn = 0xffff;
            preorder_ctrl->wsize_b = AICWF_REORDER_WINSIZE;
            DBG_REORD("reord reset [%x],ind_sn=%d,wsize_b=%d\n",tid,preorder_ctrl->ind_sn,preorder_ctrl->wsize_b);
        }
    }
    rtos_mutex_unlock(stas_reord_lock);
    rtos_mutex_lock(preorder_ctrl->reord_list_lock, -1);
    if (preorder_ctrl->enable == false) {
        preorder_ctrl->ind_sn = seq_num;
        DBG_REORD("reord_ctrl en=false,seq_num=%d\n", seq_num);
        reord_single_frame_ind(pframe);
        preorder_ctrl->ind_sn = (preorder_ctrl->ind_sn + 1) & (4096 - 1);
        DBG_REORD("reord set [%x],ind_sn=%d\n",tid,preorder_ctrl->ind_sn);
        rtos_mutex_unlock(preorder_ctrl->reord_list_lock);
        return 0;
    }
    if (reord_need_check(preorder_ctrl, pframe->seq_num)) {
        DBG_REORD("reord_need_check, seq_num=%d\n", pframe->seq_num);
        reord_single_frame_ind(pframe);
        rtos_mutex_unlock(preorder_ctrl->reord_list_lock);
        return 0;
    }
    if (reord_rxframe_enqueue(preorder_ctrl, pframe)) {
        rtos_mutex_unlock(preorder_ctrl->reord_list_lock);
        reord_rxframe_free(pframe);
        return -1;
    }
    ret = reord_rxframes_process(preorder_ctrl, false);
    rtos_mutex_unlock(preorder_ctrl->reord_list_lock);
    if (ret == true) {
        #if (AICWF_RWNX_TIMER_EN)
        if (preorder_ctrl->reord_timer) {
            if (!rwnx_timer_is_posted(preorder_ctrl->reord_timer)) {
                WRN_REORD("reord_process_unit, start timer,ind_sn=%d,cnt=%d\n", preorder_ctrl->ind_sn,preorder_ctrl->list_cnt);
                rwnx_timer_start(preorder_ctrl->reord_timer, REORDER_UPDATE_TIME, true);
            } else {
                #if 0
                DBG_REORD("reord_process_unit, restart timer,ind_sn=%d,cnt=%d\n",preorder_ctrl->ind_sn,preorder_ctrl->list_cnt);
                rwnx_timer_restart(preorder_ctrl->reord_timer, REORDER_UPDATE_TIME);
                #else
                DBG_REORD("reord_process_unit, timer posted,ind_sn=%d,cnt=%d\n",preorder_ctrl->ind_sn,preorder_ctrl->list_cnt);
                #endif
            }
        } else {
            DBG_REORD("reord_process_unit, create timer\n");
            rwnx_timer_create(&preorder_ctrl->reord_timer, REORDER_UPDATE_TIME,
                              preorder_ctrl, reord_timeout_handler,
                              true, false);
        }
        #else
        if (preorder_ctrl->reord_timer) {
            rtos_timer_stop(preorder_ctrl->reord_timer, 0);
            rtos_timer_delete(preorder_ctrl->reord_timer, 0);
            preorder_ctrl->reord_timer = NULL;
        }
        preorder_ctrl->reord_timer  = rtos_timer_create("reord_timer",
                                                        REORDER_UPDATE_TIME, 1, NULL, reord_timeout_handler);
        if (ret) {
            WRN_REORD("reord_ctrl timer create fail\n");
        }
        #endif
    } else {
        if (preorder_ctrl->reord_timer) {
            #if (AICWF_RWNX_TIMER_EN)
            if (rwnx_timer_is_posted(preorder_ctrl->reord_timer)) {
                DBG_REORD("reord_process_unit, stop timer,ind_sn=%d,cnt=%d\n",preorder_ctrl->ind_sn,preorder_ctrl->list_cnt);
                rwnx_timer_stop(preorder_ctrl->reord_timer);
            } else {
                DBG_REORD("reord timer stoped\n");
            }
            #else
            rtos_timer_stop(preorder_ctrl->reord_timer, 0);
            rtos_timer_delete(preorder_ctrl->reord_timer, 0);
            preorder_ctrl->reord_timer = NULL;
            #endif
        }
    }
    reord_rxframes_ind(preorder_ctrl);

    #ifdef CONFIG_REORD_PROCESS_UNIT_TS
    end_time = rtos_now(0);
    dbg("reo_out:%u/%u\n", end_time, reord_count);
    #endif

    return 0;
}

extern int fhost_rx_data_resend(net_if_t *net_if, struct fhost_rx_buf_tag *buf,
                         struct mac_addr *da, struct mac_addr *sa, uint8_t machdr_len);
int rwnx_rxdataind_aicwf(struct fhost_rx_buf_tag *buf)
{
    uint8_t *frame = (uint8_t *)buf->payload;
    struct mac_hdr *machdr_ptr = (struct mac_hdr *)frame;
    struct rx_info *info =&buf->info;
    uint8_t mac_hdr_len = MAC_SHORT_MAC_HDR_LEN;
    struct llc_snap *snap_hdr;
    uint16_t eth_type, *qos;
    struct mac_addr *da, *sa;
    int need_reord, vif_idx;
    uint8_t macaddr[6] = {0,};
    uint8_t tid = 0;
    struct fhost_vif_tag *fhost_vif;
    bool resend = false, forward = true;

    //if ((info->flags & RX_FLAGS_UPLOAD_BIT) == 0) {
    //    WRN_REORD("rxdata not upload\n");
    //    return -1;
    //}
    if (info->flags & RX_FLAGS_NON_MSDU_MSK) {
        buf->net_hdr.reord_magic = 0;
        fhost_rx_buf_forward(buf);
        return 0;
    }
    need_reord = (info->flags & RX_FLAGS_NEED_TO_REORD_BIT);
    vif_idx = (info->flags & RX_FLAGS_VIF_INDEX_MSK) >> RX_FLAGS_VIF_INDEX_OFT;
    fhost_vif = fhost_from_mac_vif(vif_idx);
    if (fhost_vif == NULL) {
        dbg("rxdata invalid vif_idx=%x\n", vif_idx);
        fhost_rx_buf_push(buf);
        return -2;
    }
    if (IS_QOS_DATA(machdr_ptr->fctl)) {
        mac_hdr_len += MAC_HDR_QOS_CTRL_LEN;
    }
    if (machdr_ptr->fctl & MAC_FCTRL_ORDER) {
        mac_hdr_len += MAC_HTCTRL_LEN;
    }
    switch (info->vect.statinfo & RX_HD_DECRSTATUS) {
        case RX_HD_DECR_CCMP128:
        case RX_HD_DECR_TKIP:
            mac_hdr_len += MAC_IV_LEN + MAC_EIV_LEN;
            break;
        case RX_HD_DECR_WEP:
            mac_hdr_len += MAC_IV_LEN;
            break;
        default:
            break;
    }
    snap_hdr = (struct llc_snap *)(frame + mac_hdr_len);
    eth_type = snap_hdr->proto_id;
    if (machdr_ptr->fctl & MAC_FCTRL_TODS) {// Get DA
        da = &machdr_ptr->addr3;
        sa = &machdr_ptr->addr2;
    } else {
        da = &machdr_ptr->addr1;
        sa = &machdr_ptr->addr3;
    }
    //data_pkt_rssi_set(sa, (int8_t)((info->vect.recvec1b >> 8) & 0xFF));
    if (fhost_vif->mac_vif && fhost_vif->mac_vif->type == VIF_AP) {
        if (MAC_ADDR_GROUP(da)) {
            /* broadcast pkt need to be forwared to upper layer and resent
               on wireless interface */
            resend = true;
        } else {
            /* unicast pkt for STA inside the BSS, no need to forward to upper
               layer simply resend on wireless interface */
            int dst_idx = (info->flags & RX_FLAGS_DST_INDEX_MSK) >> RX_FLAGS_DST_INDEX_OFT;
            if (dst_idx != INVALID_STA_IDX) {
                uint8_t staid = vif_mgmt_get_staid(fhost_vif->mac_vif, da);
                if(staid < NX_REMOTE_STA_MAX) {
                    struct sta_info_tag *sta = vif_mgmt_get_sta_by_staid(staid);
                    if (sta && sta->valid) {
                        resend = true;
                        forward = false;
                    }
                }
            }
        }
    }
    //dbg("Rx %d %x\r\n", (machdr_ptr->seq >> MAC_SEQCTRL_NUM_OFT), need_reord);
    if (resend) {
        int ret;
        if (machdr_ptr->fctl & MAC_FCTRL_FROMDS) {// Get SA
            sa = &machdr_ptr->addr3;
        } else {
            sa = &machdr_ptr->addr2;
        }
        ret = fhost_rx_data_resend(&fhost_vif->net_if, buf, da, sa, mac_hdr_len);
        if (ret) {
            WRN_REORD("rxdata resend fail: ret=%d\n", ret);
        }
    }
    if (machdr_ptr->fctl & MAC_FCTRL_TODS) {
        memcpy(macaddr, &machdr_ptr->addr2, 6);
    } else if (machdr_ptr->fctl & MAC_FCTRL_FROMDS) {
        memcpy(macaddr, &machdr_ptr->addr1, 6);
    }
    qos = &((struct mac_hdr_qos *)machdr_ptr)->qos;
    tid = (*qos & MAC_QOSCTRL_UP_MSK);
    if (forward) {
        if (!IS_QOS_DATA(machdr_ptr->fctl) || (co_ntohs(eth_type) == LLC_ETHERTYPE_EAP_T) || MAC_ADDR_GROUP(da)) {
            buf->net_hdr.reord_magic = 0;
            fhost_rx_buf_forward(buf);
        } else {
            uint8_t staid = vif_mgmt_get_staid(fhost_vif->mac_vif, (struct mac_addr*)macaddr);
            if(staid < NX_REMOTE_STA_MAX) {
                struct sta_info_tag *sta = vif_mgmt_get_sta_by_staid(staid);
                if (sta)
                    sta->last_active_time_us = rtos_now(0);
            }
            if (need_reord) {
                uint16_t seq_num = machdr_ptr->seq >> MAC_SEQCTRL_NUM_OFT;
                DBG_REORD("reord1:[%x]%d,%d\n",tid,seq_num,sizeof(struct rx_info) + info->vect.frmlen);
                reord_process_unit(buf, seq_num, macaddr, tid, 1);
            } else {
                reord_flush_tid(macaddr, tid);
                buf->net_hdr.reord_magic = 0;
                fhost_rx_buf_forward(buf);
            }
        }
    } else {
        if (need_reord) {
            uint16_t seq_num = machdr_ptr->seq >> MAC_SEQCTRL_NUM_OFT;
            WRN_REORD("reord0:[%x]%d,%d\n",tid,seq_num,sizeof(struct rx_info) + info->vect.frmlen);
            reord_process_unit(buf, seq_num, macaddr, tid, 0);
        } else {
            fhost_rx_buf_push(buf);
            reord_flush_tid(macaddr, tid);
        }
    }
    return 0;
}

void rwnx_reord_init(void)
{
    int ret;
    co_list_init(&stas_reord_list);
    ret = rtos_mutex_create(&stas_reord_lock);
    if (ret < 0) {
        WRN_REORD("reord mutex create fail\n");
    }
    #if (AICWF_RWNX_TIMER_EN)
    rwnx_timer_init();
    #endif
}

void rwnx_reord_deinit(void)
{
    struct reord_ctrl_info *reord_info;
    do {
        reord_info = (struct reord_ctrl_info *)co_list_pop_front(&stas_reord_list);
        if (reord_info) {
            reord_deinit_sta(reord_info);
        }
    } while (reord_info);
    rtos_mutex_delete(stas_reord_lock);
}
#endif

/*
 * @Brief: This interface is for 8800MC only.
 */
#if !(AICWF_RX_REORDER)
int rwnx_rxdataind_aicwf_simple(struct fhost_rx_buf_tag *buf,
                                         struct mac_hdr *machdr_ptr,
                                         struct rx_info *info)
{
    uint8_t *frame_tmp = NULL;
    //dbg("R %d, %x \r\n", (machdr_ptr->seq >> 4), (machdr_ptr->fctl));
    if(IS_QOS_DATA(machdr_ptr->fctl) && (info->flags & RX_FLAGS_NEED_TO_REORD_BIT)) {
        uint16_t rx_seq_no = (machdr_ptr->seq >> 4);

        if((fhost_rx_env.flags & RX_REORDER_START_FLAG) != RX_REORDER_START_FLAG) {
            fhost_rx_env.flags |= RX_REORDER_START_FLAG;
            //dbg("first %d\r\n", rx_seq_no);
            fhost_rx_buf_forward(buf);
            fhost_rx_env.next_rx_seq_no = SEQNO_ADD(rx_seq_no, 1);
            return 0;
        }
        // Reorder
        rtos_mutex_lock(fhost_rx_env.rx_reorder_lock, -1);
        if ((rx_seq_no != 1) || ((rx_seq_no == 1) && (0 != fhost_rx_env.next_rx_seq_no))) {
            //dbg("New ARR\r\n");
AGAIN:
            //dbg("N %d\r\n", fhost_rx_env.next_rx_seq_no);
            if(rx_seq_no == fhost_rx_env.next_rx_seq_no) {
                // Forward the buffer to the networking stack
                fhost_rx_buf_forward(buf);
                fhost_rx_env.next_rx_seq_no = SEQNO_ADD(rx_seq_no, 1);
                rtos_timer_restart(fhost_rx_env.rx_reorder_timer, 0, false);
                //dbg("R1 %d\r\n", sys_now());

                buf = (struct fhost_rx_buf_tag *)co_list_pick(&fhost_rx_env.rx_reorder_list); // pick first
                if(!buf) {
                    //fhost_rx_env.flags &= ~(RX_REORDER_START_FLAG);
                    rtos_mutex_unlock(fhost_rx_env.rx_reorder_lock);
                    return 0;
                }
                frame_tmp = (uint8_t *)buf->payload;
                machdr_ptr = (struct mac_hdr *)frame_tmp;
                rx_seq_no = (machdr_ptr->seq >> 4);
                if(rx_seq_no == fhost_rx_env.next_rx_seq_no) {
                    co_list_pop_front(&fhost_rx_env.rx_reorder_list); // pop it
                    goto AGAIN;
                }
            } else {
                //dbg("*Next %d, %d\r\n", fhost_rx_env.next_rx_seq_no, rx_seq_no);
                if(seqno_gt(rx_seq_no, fhost_rx_env.next_rx_seq_no)) {

                    // Insert List
                    insert_rx_buf_reorder_list(buf);

                    //dbg("Now %d, cnt %d\r\n", (uint32_t)(sys_now()),  co_list_cnt(&fhost_rx_env.rx_reorder_list));
                    if(co_list_cnt(&fhost_rx_env.rx_reorder_list) > NX_REORD_BUF_SIZE) {
                        struct fhost_rx_buf_tag * buf1 = ( struct fhost_rx_buf_tag *)co_list_pop_front(&fhost_rx_env.rx_reorder_list);
                        machdr_ptr = (struct mac_hdr *)buf1->payload;
                        rx_seq_no = (machdr_ptr->seq >> 4);
                        fhost_rx_buf_forward(buf1);
                        fhost_rx_env.next_rx_seq_no = SEQNO_ADD(rx_seq_no, 1);
                        rtos_timer_restart(fhost_rx_env.rx_reorder_timer, 0, false);
                        //dbg("R2 %d, %d\r\n", sys_now(), ret);

                        buf = (struct fhost_rx_buf_tag *)co_list_pop_front(&fhost_rx_env.rx_reorder_list); // pop front
                        if(buf) {
                            frame_tmp = (uint8_t *)buf->payload;
                            machdr_ptr = (struct mac_hdr *)frame_tmp;
                            rx_seq_no = (machdr_ptr->seq >> 4);
                            goto AGAIN;
                        }
                    }
                    rtos_mutex_unlock(fhost_rx_env.rx_reorder_lock);
                    return 0;
                } else {
                    fhost_rx_buf_forward(buf);
                    //fhost_rx_buf_push(buf);
                    //dbg("discard, %d, %d, %d\r\n", rx_seq_no, fhost_rx_env.next_rx_seq_no, sys_now());
                    //fhost_rx_env.last_rx_seq_no = rx_seq_no;
                }
            }
        }else {
            //Flush reorder list
            flush_rx_buf_reorder_list();
            fhost_rx_buf_forward(buf);
            fhost_rx_env.next_rx_seq_no = SEQNO_ADD(rx_seq_no, 1);
        }
        rtos_mutex_unlock(fhost_rx_env.rx_reorder_lock);
    } else {
        fhost_rx_buf_forward(buf);
    }

    return 0;
}
#endif

/**
 * rwnx_rxdataind - Process rx buffer
 *
 * @pthis: Pointer to the object attached to the IPC structure
 *         (points to struct rwnx_hw is this case)
 * @hostid: Address of the RX descriptor
 *
 * This function is called for each buffer received by the fw
 *
 */
uint8_t rwnx_rxdataind(void *pthis, void *hostid)
{
    struct fhost_rx_buf_tag *buf = (struct fhost_rx_buf_tag *)hostid;
    struct rx_info *info =&buf->info;
    struct hw_rxhdr *rxhdr = (struct hw_rxhdr *)CPU2HW(&(info->vect.frmlen));

    if(RX_BUFFER_READY != info->pattern) {
        fhost_rx_buf_push(buf);
        return 1;
    }
    if (info->flags & RX_FLAGS_MONITOR_BIT) {
        fhost_rx_monitor_cb(buf, false);
        fhost_rx_buf_push(buf);
        return 0;
    }
    #if PLF_RSSI_DATAPKT
    rssi_saved = (int8_t)(rxhdr->rx_vect1.rssi1);
    #endif /* PLF_RSSI_DATAPKT */

    #if NX_CSI
    //dbg("Phy info %x %x \r\n", info->phy_info.info1, info->phy_info.info2);
    //dbg("Rx vect : \r\n");
    //csi_dump_buf(&info->vect.recvec1a, 6);
    //memcpy(recvec_saved, &info->vect.recvec1a, 6 * 4);
    if (info->flags & RX_FLAGS_CSI_BIT) {
        fhost_rx_csi_cb(buf);
        fhost_rx_buf_push(buf);
        return 0;
    }
    #endif /* NX_CSI */

    struct fhost_rx_buf_tag *rx_buf = (struct fhost_rx_buf_tag *)buf;
    uint8_t *frame = (uint8_t *)rx_buf->payload;
    struct mac_hdr *machdr_ptr = (struct mac_hdr *)frame;
    struct mac_addr da, sa;

    if (machdr_ptr->fctl & MAC_FCTRL_TODS) {
        MAC_ADDR_CPY(&da, &machdr_ptr->addr3);
        MAC_ADDR_CPY(&sa, &machdr_ptr->addr2);
    } else {
        MAC_ADDR_CPY(&da, &machdr_ptr->addr1);
        MAC_ADDR_CPY(&sa, &machdr_ptr->addr3);
    }

    if (fhost_usr_cfg.parse_rx_datarate_en) {
        uint16_t *p_local_mac_addr = (uint16_t *)fhost_config_value_get(FHOST_CFG_MAC_ADDR); // get value in RAM

        if (((machdr_ptr->fctl & MAC_FCTRL_TYPE_MASK) == MAC_FCTRL_DATA_T) && ((MAC_ADDR_CMP(&da, p_local_mac_addr)))) {
            if (0 == rxhdr->rx_vect1.format_mod) { // leg
                datarate_saved = rxhdr->rx_vect1.leg_rate;
            } else if (2 == rxhdr->rx_vect1.format_mod) { // HT
                datarate_saved = (2 << 4) | rxhdr->rx_vect1.ht.mcs;
            } else if (4 == rxhdr->rx_vect1.format_mod) { // VHT
                datarate_saved = (4 << 4) | rxhdr->rx_vect1.vht.mcs;
            } else if (5 == rxhdr->rx_vect1.format_mod) { // HE
                datarate_saved = (5 << 4) | rxhdr->rx_vect1.he.mcs;
            }
            if (1 == rxhdr->rx_vect1.ch_bw) { //40M
                datarate_saved |= (1 << 8);
            }
            //dbg("datarate_saved: %x\r\n", datarate_saved);
        }
    }
    #if PLF_RSSI_DATAPKT
    #ifdef CFG_SOFTAP
    sta_data_pkt_rssi_set((uint8_t *)sa.array, (int8_t)(rxhdr->rx_vect1.rssi1));
    #endif
    #endif /* PLF_RSSI_DATAPKT */

    #if FHOST_OR_HOSTIF
    wifi_raw_data_handler_t handler = get_rawdata_if_rx_data_cb();
    if (handler) {
        handler(frame, info->vect.frmlen);
        fhost_rx_buf_push(buf);
        return 0;
    }

    #if NX_BEACONING
    uint8_t fhost_vif_idx = fhost_search_itf_idx(VIF_AP);
    if (fhost_vif_idx < NX_VIRT_DEV_MAX) {
        struct vif_info_tag *mac_vif = fhost_to_mac_vif(fhost_vif_idx);
        if (mac_vif && (VIF_AP == mac_vif->type)) {
            struct mac_addr mac;
            MAC_ADDR_CPY(mac.array, machdr_ptr->addr2.array);
            uint8_t staid = vif_mgmt_get_staid(mac_vif, &mac);
            if(staid < NX_REMOTE_STA_MAX) {
                struct sta_info_tag *sta = vif_mgmt_get_sta_by_addr((const struct mac_addr *)&mac);
                if (sta)
                    sta->last_active_time_us = sys_now();
            }
        }
    }
    #endif /* NX_BEACONING */

    #if !(AICWF_RX_REORDER)
    rwnx_rxdataind_aicwf_simple(buf, machdr_ptr, info);
    #else
    rwnx_rxdataind_aicwf(buf);
    #endif

    #else /* FHOST_OR_HOSTIF */
    #if defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF)

    if (hostif_filter_type_get() == VNET_FILTER_DIRECT) {    // If Use this filter, mcu don`t think about reorder!
        if ((hostif_mode_get() == HOST_VNET_MODE) &&
            (get_hostif_wlan_status() == HOSTIF_ST_AWAKE) &&
            (!rwnx_rxbuf_filtered(buf))) {
            /* If not use AP, the pkt send to HOST or MCU by filter.*/
            #ifndef CFG_SOFTAP
            send_pkg_to_host(info);                         // Only STA mode
            #ifndef CFG_HOSTIF_OPT
            fhost_rx_buf_push(buf); // VNET_FILTER_DIRECT: Host reorder.
            #endif /* CFG_HOSTIF_OPT */

            /* If use AP, broadcast and unicast should send to HOST and MCU both. */
            #else /* CFG_SOFTAP */
            if (!wlan_get_softap_status()) {                // STA mode
                send_pkg_to_host(info);
                #ifndef CFG_HOSTIF_OPT
                fhost_rx_buf_push(buf);
                #endif
            } else {                                        // AP mode
                uint8_t machdr_len;
                int pkt_type = fhost_rxbuf_send_type(buf, &da, (uint8_t *)&machdr_len);
                //dbg("pkt_type: %d\n", pkt_type);
                if (pkt_type == VNET_TRANSFER_MCU_HOST) {
                    #ifndef CFG_HOSTIF_OPT
                    send_pkg_to_host(info);
                    // If AIC8800M/M40, "fhost_rx_buf_forward" will not resend inside!
                    #if !(PLF_AIC8800MC)
                    fhost_rx_data_resend(NULL, buf, &da, &sa, machdr_len);
                    #endif
                    fhost_rx_buf_forward(buf);
                    #else
                    fhost_rx_buf_forward_no_free(buf);
                    send_pkg_to_host(info);
                    #endif
                } else if (pkt_type == VNET_TRANSFER_RESEND_ONLY) {
                    fhost_rx_data_resend(NULL, buf, &da, &sa, machdr_len);
                    fhost_rx_buf_push(buf);
                } else if (pkt_type == VNET_TRANSFER_HOST_ONLY) {
                    send_pkg_to_host(info);
                    #ifndef CFG_HOSTIF_OPT
                    fhost_rx_buf_push(buf);
                    #endif
                } else if (pkt_type == -1) {
                    dbg("pkt type err\n");
                    fhost_rx_buf_push(buf);
                }
            }
            #endif /* CFG_SOFTAP */
            return 0;
        }
    }
    else if (hostif_filter_type_get() == VNET_FILTER_SHARED) { // If Use this filter, mcu need think about reorder!
        if ((hostif_mode_get() == HOST_VNET_MODE) && (get_hostif_wlan_status() == HOSTIF_ST_AWAKE)) {
            uint8_t machdr_len;
            uint8_t filter_result = rwnx_rxbuf_shared_filtered(buf, &da, &machdr_len);
            //dbg("filter_result: %d\n", filter_result);
            if (filter_result == VNET_TRANSFER_MCU_HOST) {
                #ifndef CFG_HOSTIF_OPT
                send_pkg_to_host(info);
                #if !(AICWF_RX_REORDER)
                rwnx_rxdataind_aicwf_simple(buf, machdr_ptr, info);
                #else
                rwnx_rxdataind_aicwf(buf);
                #endif /* AICWF_RX_REORDER */

                #else /* CFG_HOSTIF_OPT */
                /**
                 * In ipc-rx-no-copy mode, if the pkt is VNET_TRANSFER_MCU_HOST,
                 * we don`t think MCU need to reorder.
                 **/
                fhost_rx_buf_forward_no_free(buf);
                send_pkg_to_host(info);
                #endif /* CFG_HOSTIF_OPT */
            } else if (filter_result == VNET_TRANSFER_MCU_ONLY) {
                #if !(AICWF_RX_REORDER)
                rwnx_rxdataind_aicwf_simple(buf, machdr_ptr, info);
                #else
                rwnx_rxdataind_aicwf(buf);
                #endif /* AICWF_RX_REORDER */
            } else if (filter_result == VNET_TRANSFER_HOST_ONLY) {
                send_pkg_to_host(info);
                #ifndef CFG_HOSTIF_OPT
                fhost_rx_buf_push(buf);
                #endif
            }
            #ifdef CFG_SOFTAP
            else if (filter_result == VNET_TRANSFER_RESEND_ONLY) {
                fhost_rx_data_resend(NULL, buf, &da, &sa, machdr_len);
                fhost_rx_buf_push(buf);
            }
            #endif
            else {
                dbg("filter result err.\n");
                fhost_rx_buf_push(buf);
            }
        } else {
            // hostif is not AWAKE.
            #if !(AICWF_RX_REORDER)
            rwnx_rxdataind_aicwf_simple(buf, machdr_ptr, info);
            #else
            rwnx_rxdataind_aicwf(buf);
            #endif /* AICWF_RX_REORDER */
        }
        return 0;

    }
    #endif /* CONFIG_RWNX_LWIP && CFG_HOSTIF */

    // Forward the buffer to the networking stack
    fhost_rx_buf_forward(buf);

    #endif /* FHOST_OR_HOSTIF */
    return 0;
}

#if NX_UF_EN
uint8_t rwnx_unsup_rx_vec_ind(void *pthis, void *hostid)
{
    struct fhost_rx_uf_buf_tag *buf = (struct fhost_rx_uf_buf_tag *)hostid;
    struct rx_vector_desc *rx_vector =(struct rx_vector_desc *)(&(buf->rx_vector));

    //dbg("%s, %x, %x\r\n", __func__, rx_vector, rx_vector->pattern);

    if(RX_UF_VEC_VALID_PATTERN != rx_vector->pattern) {
        return 1;
    }

    fhost_rx_monitor_cb(rx_vector, true);

    // Push back the RX buffer to the MAC
    rx_vector->pattern = RX_BUFFER_PUSHED;
    fhost_rx_uf_buf_push(buf);

    return 0;
}
#endif /* NX_UF_EN */
#endif /* !CFG_DEVICE_IPC */
