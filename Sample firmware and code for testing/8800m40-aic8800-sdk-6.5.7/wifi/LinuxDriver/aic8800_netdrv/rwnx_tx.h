/**
 ******************************************************************************
 *
 * @file rwnx_tx.h
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ******************************************************************************
 */
#ifndef _RWNX_TX_H_
#define _RWNX_TX_H_

#include <linux/ieee80211.h>
#include <linux/netdevice.h>
#include <net/cfg80211.h>
#include "rwnx_utils.h"
#include "rwnx_main.h"
#include "rwnx_utils.h"
#include "ipc_shared.h"
#include "rwnx_txq.h"


#define RWNX_TX_LIFETIME_MS             1000
#define RWNX_SWTXHDR_ALIGN_SZ           4
#define RWNX_SWTXHDR_ALIGN_MSK (RWNX_SWTXHDR_ALIGN_SZ - 1)
#define RWNX_SWTXHDR_ALIGN_PADS(x) \
                    ((RWNX_SWTXHDR_ALIGN_SZ - ((x) & RWNX_SWTXHDR_ALIGN_MSK)) \
                     & RWNX_SWTXHDR_ALIGN_MSK)

/**
 * struct rwnx_txhdr - Stucture to control transimission of packet
 * (Added in skb headroom)
 *
 * @sw_hdr: Information from driver
 * @cache_guard:
 * @hw_hdr: Information for/from hardware
 */
struct rwnx_txhdr {
    struct rwnx_sw_txhdr *sw_hdr;
    char cache_guard[L1_CACHE_BYTES];
    struct rwnx_hw_txhdr hw_hdr;
};

#ifdef CONFIG_VNET_MODE
int rwnx_start_xmit(struct sk_buff *skb, struct net_device *dev);
#elif defined(CONFIG_RAWDATA_MODE)
int rwnx_tx_data(struct sk_buff *skb);
#endif

typedef struct _aicwf_custom_msg_cmd_cfm aicwf_custom_msg_cmd_cfm;
void rwnx_tx_msg_cfm_ready(void);
int rwnx_tx_msg_result(char *result);
int rwnx_tx_msg_queue_work(  char *result);
int rwnx_tx_msg(u8 * msg, u16 msg_len, aicwf_custom_msg_cmd_cfm *cfm, char *result);

#endif /* _RWNX_TX_H_ */
