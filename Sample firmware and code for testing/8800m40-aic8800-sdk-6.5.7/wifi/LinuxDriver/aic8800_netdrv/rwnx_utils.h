/**
 * rwnx_ipc_utils.h
 *
 * IPC utility function declarations
 *
 * Copyright (C) RivieraWaves 2012-2019
 */
#ifndef _RWNX_IPC_UTILS_H_
#define _RWNX_IPC_UTILS_H_

#include <linux/dma-mapping.h>
#include <linux/dmapool.h>
#include <linux/skbuff.h>
#include "aicwf_debug.h"

#include <linux/version.h>
#include <linux/types.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)
#include <linux/bits.h>
#else
#include <linux/bitops.h>
#endif

#define RWNX_FN_ENTRY_STR ">>> %s()\n", __func__

#define   SYSCTRL_MISC_CNTL_ADDR       0x009000E0
#define   BOOTROM_ENABLE               BIT(4)
#define   FPGA_B_RESET                 BIT(1)
#define   SOFT_RESET                   BIT(0)


#define MAC_ADDR_LEN 6

#ifdef CONFIG_RWNX_TL4
typedef uint16_t u8_l;
typedef int16_t s8_l;
typedef uint16_t bool_l;
#else
typedef uint8_t u8_l;
typedef int8_t s8_l;
typedef bool bool_l;
#endif
typedef uint16_t u16_l;
typedef int16_t s16_l;
typedef uint32_t u32_l;
typedef int32_t s32_l;
typedef uint64_t u64_l;


#ifdef CONFIG_RWNX_FULLMAC
/**
 * struct rwnx_hw_txstatus - Bitfield of confirmation status
 *
 * @tx_done: packet has been processed by the firmware.
 * @retry_required: packet has been transmitted but not acknoledged.
 * Driver must repush it.
 * @sw_retry_required: packet has not been transmitted (FW wasn't able to push
 * it when it received it: not active channel ...). Driver must repush it.
 * @acknowledged: packet has been acknowledged by peer
 */
union rwnx_hw_txstatus {
    struct {
        u32 tx_done            : 1;
        u32 retry_required     : 1;
        u32 sw_retry_required  : 1;
        u32 acknowledged       : 1;
        u32 reserved           :28;
    };
    u32 value;
};

/**
 * struct tx_cfm_tag - Structure indicating the status and other
 * information about the transmission
 *
 * @pn: PN that was used for the transmission
 * @sn: Sequence number of the packet
 * @timestamp: Timestamp of first transmission of this MPDU
 * @credits: Number of credits to be reallocated for the txq that push this
 * buffer (can be 0 or 1)
 * @ampdu_size: Size of the ampdu in which the frame has been transmitted if
 * this was the last frame of the a-mpdu, and 0 if the frame is not the last
 * frame on a a-mdpu.
 * 1 means that the frame has been transmitted as a singleton.
 * @amsdu_size: Size, in bytes, allowed to create a-msdu.
 * @status: transmission status
 */
struct tx_cfm_tag
{
    u16_l pn[4];
    u16_l sn;
    u16_l timestamp;
    s8_l credits;
    u8_l ampdu_size;
#ifdef CONFIG_RWNX_SPLIT_TX_BUF
    u16_l amsdu_size;
#endif
    union rwnx_hw_txstatus status;
};

/**
 * struct rwnx_hw_txhdr - Hardware part of tx header
 *
 * @cfm: Information updated by fw/hardware after sending a frame
 */
struct rwnx_hw_txhdr {
    struct tx_cfm_tag cfm;
};
#endif /* CONFIG_RWNX_FULLMAC */


#endif
