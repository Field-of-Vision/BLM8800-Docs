/**
 ******************************************************************************
 *
 * @file rwnx_rx.h
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ******************************************************************************
 */
#ifndef _RWNX_RX_H_
#define _RWNX_RX_H_

enum rx_status_bits
{
    /// The buffer can be forwarded to the networking stack
    RX_STAT_FORWARD = 1 << 0,
    /// A new buffer has to be allocated
    RX_STAT_ALLOC = 1 << 1,
    /// The buffer has to be deleted
    RX_STAT_DELETE = 1 << 2,
    /// The length of the buffer has to be updated
    RX_STAT_LEN_UPDATE = 1 << 3,
    /// The length in the Ethernet header has to be updated
    RX_STAT_ETH_LEN_UPDATE = 1 << 4,
    /// Simple copy
    RX_STAT_COPY = 1 << 5,
    /// Spurious frame (inform upper layer and discard)
    RX_STAT_SPURIOUS = 1 << 6,
    /// packet for monitor interface
    RX_STAT_MONITOR = 1 << 7,
};


/*
 * Decryption status subfields.
 * {
 */
#define RWNX_RX_HD_DECR_UNENC           0 // Frame unencrypted
#define RWNX_RX_HD_DECR_ICVFAIL         1 // WEP/TKIP ICV failure
#define RWNX_RX_HD_DECR_CCMPFAIL        2 // CCMP failure
#define RWNX_RX_HD_DECR_AMSDUDISCARD    3 // A-MSDU discarded at HW
#define RWNX_RX_HD_DECR_NULLKEY         4 // NULL key found
#define RWNX_RX_HD_DECR_WEPSUCCESS      5 // Security type WEP
#define RWNX_RX_HD_DECR_TKIPSUCCESS     6 // Security type TKIP
#define RWNX_RX_HD_DECR_CCMPSUCCESS     7 // Security type CCMP (or WPI)
// @}


/// Structure containing information about the received frame (length, timestamp, rate, etc.)
struct rx_vector
{
    /// Total length of the received MPDU
    uint16_t            frmlen;
    /// AMPDU status information
    uint16_t            ampdu_stat_info;
    /// TSF Low
    uint32_t            tsflo;
    /// TSF High
    uint32_t            tsfhi;
    /// Contains the bytes 4 - 1 of Receive Vector 1
    uint32_t            recvec1a;
    /// Contains the bytes 8 - 5 of Receive Vector 1
    uint32_t            recvec1b;
    /// Contains the bytes 12 - 9 of Receive Vector 1
    uint32_t            recvec1c;
    /// Contains the bytes 16 - 13 of Receive Vector 1
    uint32_t            recvec1d;
    /// Contains the bytes 4 - 1 of Receive Vector 2
    uint32_t            recvec2a;
    ///  Contains the bytes 8 - 5 of Receive Vector 2
    uint32_t            recvec2b;
    /// MPDU status information
    uint32_t            statinfo;
};

/// Structure containing the information about the PHY channel that was used for this RX
struct phy_channel_info
{
    /// PHY channel information 1
    uint32_t info1;
    /// PHY channel information 2
    uint32_t info2;
};

/// Structure containing the information about the received payload
struct rx_info
{
    /// Rx header descriptor (this element MUST be the first of the structure)
    struct rx_vector vect;
    /// Structure containing the information about the PHY channel that was used for this RX
    struct phy_channel_info phy_info;
    /// Word containing some SW flags about the RX packet
    uint32_t flags;
    #if NX_AMSDU_DEAGG
    /// Array of host buffer identifiers for the other A-MSDU subframes
    uint32_t amsdu_hostids[NX_MAX_MSDU_PER_RX_AMSDU - 1];
    #endif
    /// Spare room for LMAC FW to write a pattern when last DMA is sent
    uint32_t pattern;

    uint16_t reserved[2];
};

#if PLF_RSSI_DATAPKT
int8_t data_pkt_rssi_get(void);
#endif /* PLF_RSSI_DATAPKT */

#if !defined(CFG_DEVICE_IPC)
/**
 * @brief: data rate parsing enable or not
 * @param[in] en: none-zero for enable
 */
void data_rate_parsing_config(uint8_t en);

/**
 * @brief: data rate saved
 *  +-------+------------+---------+-------+-
 *  |  desc |  bandwidth | format  |  MSC  |
 *  +-------+------------+---------+-------+-
 *  |  bit  |    8~15    |   4~7   |  0~3  |
 *  +-------+------------+---------+-------+-
 * bandwidth: 1:40M,0:20M. format: 0:legacy, 2:HT, 4:VHT,5:HE
 * @param[in] none
 */
uint16_t data_rate_get(void);
#endif

#if (PLF_AIC8800) || (PLF_AIC8800M40)
#define AICWF_RX_REORDER 1
#define AICWF_RWNX_TIMER_EN 1
#else
#define AICWF_RX_REORDER 0
#define AICWF_RWNX_TIMER_EN 0
#endif

#if (AICWF_RWNX_TIMER_EN)
typedef void (*rwnx_timer_cb_t)(void * arg);

enum rwnx_timer_state_e {
    RWNX_TIMER_STATE_FREE   = 0,
    RWNX_TIMER_STATE_POST   = 1,
    RWNX_TIMER_STATE_STOP   = 2,
};

enum rwnx_timer_action_e {
    RWNX_TIMER_ACTION_CREATE    = 0,
    RWNX_TIMER_ACTION_START     = 1,
    RWNX_TIMER_ACTION_RESTART   = 2,
    RWNX_TIMER_ACTION_STOP      = 3,
    RWNX_TIMER_ACTION_DELETE    = 4,
};

struct rwnx_timer_node_s {
    struct co_list_hdr hdr;
    rwnx_timer_cb_t cb;
    void *arg;
    uint32_t expired_ms; // remained
    enum rwnx_timer_state_e state;
    bool periodic;
    bool auto_load;
};

typedef struct rwnx_timer_node_s * rwnx_timer_handle;
#endif

#if (AICWF_RX_REORDER)
#define MAX_REORD_RXFRAME       250
#define REORDER_UPDATE_TIME     50
#define AICWF_REORDER_WINSIZE   16
#define SN_LESS(a, b)           (((a-b)&0x800) != 0)
#define SN_EQUAL(a, b)          (a == b)

struct reord_ctrl {
    uint8_t enable;
    uint8_t wsize_b;
    uint16_t ind_sn;
    uint16_t list_cnt;
    struct co_list reord_list;
    rtos_mutex reord_list_lock;
    #if (AICWF_RWNX_TIMER_EN)
    rwnx_timer_handle reord_timer;
    #else
    TimerHandle_t reord_timer;
    #endif
};

struct reord_ctrl_info {
    struct co_list_hdr hdr;
    uint8_t mac_addr[6];
    struct reord_ctrl preorder_ctrl[8];
};

struct fhost_rx_buf_tag;

struct recv_msdu {
    struct co_list_hdr hdr;
    struct fhost_rx_buf_tag *rx_buf;
    uint16_t buf_len;
    uint16_t seq_num;
    uint8_t  tid;
    uint8_t  forward;
    //struct reord_ctrl *preorder_ctrl;
};
#endif

uint8_t rwnx_rxdataind(void *pthis, void *hostid);
void rwnx_reord_init(void);
void reord_deinit_sta_by_mac(const uint8_t *mac_addr);

#if NX_UF_EN
uint8_t rwnx_unsup_rx_vec_ind(void *pthis, void *hostid);
#endif

#endif /* _RWNX_RX_H_ */
