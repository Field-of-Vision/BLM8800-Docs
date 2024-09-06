/**
 ****************************************************************************************
 *
 * @file fhost_rx.h
 *
 * @brief Definitions of the fully hosted RX task.
 *
 * Copyright (C) RivieraWaves 2017-2019
 *
 ****************************************************************************************
 */

#ifndef _FHOST_RX_H_
#define _FHOST_RX_H_

/**
 ****************************************************************************************
 * @defgroup FHOST_RX FHOST_RX
 * @ingroup FHOST
 * @brief Fully Hosted RX task implementation.
 * This module creates a task that will be used to handle the RX descriptors passed by
 * the WiFi task.
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "net_def.h"
#include "rtos.h"
#include "cfgrwnx.h"
#include "co_math.h"
#include "co_list.h"
#include "rwnx_utils.h"
#include "rwnx_rx.h"
#if defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF)
#include "hostif_cfg.h"
#include "hostif.h"
#endif

#if (defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF) || (PLF_AIC8800 && defined(CFG_WIFI_HIB)))
#define FHOST_RX_REORDER 0
#else /* CONFIG_RWNX_LWIP && CFG_HOSTIF */
#define FHOST_RX_REORDER 1
#endif /* CONFIG_RWNX_LWIP && CFG_HOSTIF */

#if defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF)
#define FHOST_OR_HOSTIF 0
#else /* CONFIG_RWNX_LWIP && CFG_HOSTIF */
#define FHOST_OR_HOSTIF 1
#endif /* CONFIG_RWNX_LWIP && CFG_HOSTIF */

/// Maximum number MSDUs supported in one received A-MSDU
#define NX_MAX_MSDU_PER_RX_AMSDU 8

/// Decryption status mask.
#define RX_HD_DECRSTATUS 0x0000007C

/// Decryption type offset
#define RX_HD_DECRTYPE_OFT 2
/// Frame decrypted using WEP.
#define RX_HD_DECR_WEP (0x01 << RX_HD_DECRTYPE_OFT)
/// Frame decrypted using TKIP.
#define RX_HD_DECR_TKIP (0x02 << RX_HD_DECRTYPE_OFT)
/// Frame decrypted using CCMP 128bits.
#define RX_HD_DECR_CCMP128 (0x03 << RX_HD_DECRTYPE_OFT)
/// Frame decrypted using WAPI.
#define RX_HD_DECR_WAPI (0x07 << RX_HD_DECRTYPE_OFT)

/// Packet contains an A-MSDU
#define RX_FLAGS_IS_AMSDU_BIT         CO_BIT(0)
/// Packet contains a 802.11 MPDU
#define RX_FLAGS_IS_MPDU_BIT          CO_BIT(1)
/// Packet contains 4 addresses
#define RX_FLAGS_4_ADDR_BIT           CO_BIT(2)
/// Packet is a Mesh Beacon received from an unknown Mesh STA
#define RX_FLAGS_NEW_MESH_PEER_BIT    CO_BIT(3)
#define RX_FLAGS_NEED_TO_REORD_BIT    CO_BIT(5)
#define RX_FLAGS_MONITOR_BIT          CO_BIT(7) //add by aic
#define RX_FLAGS_CSI_BIT              CO_BIT(9) //add by aic

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// FHOST RX environment structure
struct fhost_rx_buf_tag
{
    union {
        net_buf_rx_t net_buf;
        struct co_list_hdr hdr;
        #if (AICWF_RX_REORDER)
        uint8_t reord_magic;
        #endif
    } net_hdr;

    /// Structure containing the information about the received payload
    struct rx_info info;
    /// Payload buffer space
    uint32_t payload[CO_ALIGN4_HI(FHOST_RX_BUF_SIZE)/sizeof(uint32_t)];
};
#define IPC_DATA_HDR_LEN    offsetof(struct fhost_rx_buf_tag, info)

#if NX_UF_EN
/// Structure for receive Vector 1
struct rx_vector_1
{
    /// Contains the bytes 4 - 1 of Receive Vector 1
    uint32_t            recvec1a;
    /// Contains the bytes 8 - 5 of Receive Vector 1
    uint32_t            recvec1b;
    /// Contains the bytes 12 - 9 of Receive Vector 1
    uint32_t            recvec1c;
    /// Contains the bytes 16 - 13 of Receive Vector 1
    uint32_t            recvec1d;
};

struct rx_vector_desc
{
    /// Structure containing the information about the PHY channel that was used for this RX
    struct phy_channel_info phy_info;

    /// Structure containing the rx vector 1
    struct rx_vector_1 rx_vec_1;

    /// Used to mark a valid rx vector
    uint32_t pattern;
};
/// FHOST UF environment structure
struct fhost_rx_uf_buf_tag
{
    struct co_list_hdr hdr;
    struct rx_vector_desc rx_vector;

    /// Payload buffer space (empty in case of UF buffer)
    uint32_t payload[0];
};

/// Structure used, when receiving UF, for the buffer elements exchanged between the FHOST RX and the MAC thread
struct fhost_rx_uf_buf_desc_tag
{
    /// Id of the RX buffer
    uint32_t host_id;
};
#endif // NX_UF_EN

/// Structure used for the inter-task communication
struct fhost_rx_msg_tag
{
    /// RX descriptor structure
    //struct rxu_stat_val desc;
};

#define IS_QOS_DATA(frame_cntrl) ((frame_cntrl & MAC_FCTRL_TYPESUBTYPE_MASK) == MAC_FCTRL_QOS_DATA)

#if FHOST_RX_REORDER || ((defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF)) && !(AICWF_RX_REORDER))
#define RX_REORDER_START_FLAG (0x01)
#define NEED_REPLENISH_RX_BUF (0x10)

#define MAX_SEQNO_BY_TWO            2048
#define SEQNO_MASK                  0x0FFF
#define SEQNO_ADD(seq1, seq2) (((seq1) + (seq2)) & SEQNO_MASK)

/* This function checks whether seq1 is less than or equal to seq2 */
INLINE bool seqno_leq(uint16_t seq1, uint16_t seq2)
{
    if(((seq1 <= seq2) && ((seq2 - seq1) < MAX_SEQNO_BY_TWO)) ||
       ((seq1 > seq2) && ((seq1 - seq2) > MAX_SEQNO_BY_TWO)))
    {
        return true;
    }

    return false;
}

/* This function checks whether seq1 is less than seq2 */
INLINE bool seqno_lt(uint16_t seq1, uint16_t seq2)
{
    if(((seq1 < seq2) && ((seq2 - seq1) < MAX_SEQNO_BY_TWO)) ||
       ((seq1 > seq2) && ((seq1 - seq2) > MAX_SEQNO_BY_TWO)))
    {
        return true;
    }

    return false;
}

/* This function checks whether seq1 is greater than or equal to seq2 */
INLINE bool seqno_geq(uint16_t seq1, uint16_t seq2)
{
    return seqno_leq(seq2, seq1);
}

/* This function checks whether seq1 is greater than seq2 */
INLINE bool seqno_gt(uint16_t seq1, uint16_t seq2)
{
    return seqno_lt(seq2, seq1);
}
#endif /* FHOST_RX_REORDER */

/// FHOST RX environment structure
struct fhost_rx_env_tag
{
    #if FHOST_RX_REORDER || (defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF))
    struct co_list rx_reorder_list;
    rtos_semaphore rx_reorder_lock;
    TimerHandle_t  rx_reorder_timer;
    #endif /* FHOST_RX_REORDER */
    uint32_t  flags;
    uint16_t  next_rx_seq_no;
	#ifdef CFG_HOSTAPD
    /// Management frame Callback function pointer
    cb_fhost_rx mgmt_cb[NX_VIRT_DEV_MAX];
    /// Management Callback parameter
    void *mgmt_cb_arg[NX_VIRT_DEV_MAX];
	#else
    /// Management frame Callback function pointer
    cb_fhost_rx mgmt_cb;
    /// Management Callback parameter
    void *mgmt_cb_arg;
	#endif
    /// Monitor Callback function pointer
    cb_fhost_rx monitor_cb;
    /// Monitor Callback parameter
    void *monitor_cb_arg;
};

/// Structure used for the buffer elements exchanged between the FHOST RX and the MAC thread
struct fhost_rx_buf_desc_tag
{
    /// Id of the RX buffer
    uint32_t host_id;
    /// Address of the payload inside the buffer
    uint32_t addr;
};
struct rx_leg_vect
{
    uint8_t    dyn_bw_in_non_ht     : 1;
    uint8_t    chn_bw_in_non_ht     : 2;
    uint8_t    rsvd_nht             : 4;
    uint8_t    lsig_valid           : 1;
} __PACKED;

struct rx_ht_vect
{
    uint16_t   sounding             : 1;
    uint16_t   smoothing            : 1;
    uint16_t   short_gi             : 1;
    uint16_t   aggregation          : 1;
    uint16_t   stbc                 : 1;
    uint16_t   num_extn_ss          : 2;
    uint16_t   lsig_valid           : 1;
    uint16_t   mcs                  : 7;
    uint16_t   fec                  : 1;
    uint16_t   length               :16;
} __PACKED;

struct rx_vht_vect
{
    uint8_t   sounding              : 1;
    uint8_t   beamformed            : 1;
    uint8_t   short_gi              : 1;
    uint8_t   rsvd_vht1             : 1;
    uint8_t   stbc                  : 1;
    uint8_t   doze_not_allowed      : 1;
    uint8_t   first_user            : 1;
    uint8_t   rsvd_vht2             : 1;
    uint16_t  partial_aid           : 9;
    uint16_t  group_id              : 6;
    uint16_t  rsvd_vht3             : 1;
    uint32_t  mcs                   : 4;
    uint32_t  nss                   : 3;
    uint32_t  fec                   : 1;
    uint32_t  length                :20;
    uint32_t  rsvd_vht4             : 4;
} __PACKED;
struct rx_he_vect
{
    uint8_t   sounding              : 1;
    uint8_t   beamformed            : 1;
    uint8_t   gi_type               : 2;
    uint8_t   stbc                  : 1;
    uint8_t   rsvd_he1              : 3;

    uint8_t   uplink_flag           : 1;
    uint8_t   beam_change           : 1;
    uint8_t   dcm                   : 1;
    uint8_t   he_ltf_type           : 2;
    uint8_t   doppler               : 1;
    uint8_t   rsvd_he2              : 2;

    uint8_t   bss_color             : 6;
    uint8_t   rsvd_he3              : 2;

    uint8_t   txop_duration         : 7;
    uint8_t   rsvd_he4              : 1;

    uint8_t   pe_duration           : 4;
    uint8_t   spatial_reuse         : 4;

    uint8_t  rsvd_he5               : 8;

    uint32_t  mcs                   : 4;
    uint32_t  nss                   : 3;
    uint32_t  fec                   : 1;
    uint32_t  length                :20;
    uint32_t  rsvd_he6              : 4;
}__PACKED;

struct hw_rx_vector_1 {
    uint8_t     format_mod         : 4;
    uint8_t     ch_bw              : 3;
    uint8_t     pre_type           : 1;
    uint8_t     antenna_set        : 8;
    int32_t     rssi_leg           : 8;
    uint32_t    leg_length         :12;
    uint32_t    leg_rate           : 4;
    int32_t     rssi1              : 8;

    union
    {
        struct rx_leg_vect leg;
        struct rx_ht_vect ht;
        struct rx_vht_vect vht;
        struct rx_he_vect he;
    };
} __PACKED;

struct hw_rx_vector_2 {
    /** Receive Vector 2a */
    uint32_t    rcpi1              : 8;
    uint32_t    rcpi2              : 8;
    uint32_t    rcpi3              : 8;
    uint32_t    rcpi4              : 8;

    /** Receive Vector 2b */
    uint32_t    evm1               : 8;
    uint32_t    evm2               : 8;
    uint32_t    evm3               : 8;
    uint32_t    evm4               : 8;
} __PACKED;

struct hw_rxhdr {
    /** Total length for the MPDU transfer */
    uint32_t len                   :16;

    uint32_t reserved              : 8;

    /** AMPDU Status Information */
    uint32_t mpdu_cnt              : 6;
    uint32_t ampdu_cnt             : 2;

    /** TSF Low */
    uint32_t tsf_lo;
    /** TSF High */
    uint32_t tsf_hi;

    /** Receive Vector 1 */
    struct hw_rx_vector_1 rx_vect1;
    /** Receive Vector 2 */
    struct hw_rx_vector_2 rx_vect2;
#if 0
    /** Status **/
    uint32_t    rx_vect2_valid     : 1;
    uint32_t    resp_frame         : 1;
    /** Decryption Status */
    uint32_t    decr_status        : 3;
    uint32_t    rx_fifo_oflow      : 1;

    /** Frame Unsuccessful */
    uint32_t    undef_err          : 1;
    uint32_t    phy_err            : 1;
    uint32_t    fcs_err            : 1;
    uint32_t    addr_mismatch      : 1;
    uint32_t    ga_frame           : 1;
    uint32_t    current_ac         : 2;

    uint32_t    frm_successful_rx  : 1;
    /** Descriptor Done  */
    uint32_t    desc_done_rx       : 1;
    /** Key Storage RAM Index */
    uint32_t    key_sram_index     : 10;
    /** Key Storage RAM Index Valid */
    uint32_t    key_sram_v         : 1;
    uint32_t    type               : 2;
    uint32_t    subtype            : 4;
#endif
}__PACKED;

#if NX_UF_EN
struct uf_rx_vector_1 {
    uint8_t     format_mod         : 4;
    uint8_t     ch_bw              : 3;
    uint8_t     pre_type           : 1;
    uint8_t     antenna_set        : 8;
    int32_t     rssi_leg           : 8;
    uint32_t    leg_length         :12;
    uint32_t    leg_rate           : 4;
    int32_t     rssi1              : 8;

    union
    {
        struct rx_leg_vect leg;
        struct rx_ht_vect ht;
        struct rx_vht_vect vht;
        struct rx_he_vect he;
    };
} __PACKED;

__INLINE uint32_t hal_desc_get_vht_length(struct rx_vector_1 *rx_vec_1)
{
    uint32_t length;

    length = ((((rx_vec_1->recvec1d) & 0xF) << 16) | (((rx_vec_1->recvec1c) & 0xFFFF0000) >> 16));

    return length;
}
#endif /* NX_UF_EN */

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
/// FHOST RX environment
extern struct fhost_rx_env_tag fhost_rx_env;

/*
 * FUNCTIONS
 ****************************************************************************************
 */
#if 0
/**
 ****************************************************************************************
 * @brief Initialization of the RX task.
 * This function initializes the different data structures used for the RX and creates the
 * RTOS task dedicated to the RX processing.
 *
 * @return 0 on success and != 0 if error occurred.
 ****************************************************************************************
 */
int fhost_rx_init(void);
#endif

/**
 ****************************************************************************************
 * @brief Set the callback to call when receiving management frames (i.e. they have
 * not been processed by the wifi task).
 *
 * @attention The callback is called with a @ref fhost_frame_info parameter that is only
 * valid during the callback. If needed the callback is responsible to save the frame for
 * futher processing.
 *
 * @param[in] cb   Callback function pointer
 * @param[in] arg  Callback parameter (NULL if not needed)
 ****************************************************************************************
 */
void fhost_rx_set_mgmt_cb(uint8_t fhost_vif_idx, cb_fhost_rx cb, void *arg);

/**
 ****************************************************************************************
 * @brief Set the callback to call when receiving packets in monitor mode.
 *
 * @attention The callback is called with a @ref fhost_frame_info parameter that is only
 * valid during the callback. If needed the callback is responsible to save the frame for
 * futher processing.
 *
 * @param[in] cb   Callback function pointer
 * @param[in] arg  Callback parameter (NULL if not needed)
 ****************************************************************************************
 */
void fhost_rx_set_monitor_cb(cb_fhost_rx cb, void *arg);
uint8_t machdr_len_get(uint16_t frame_cntl);
void fhost_rx_buf_push(void *net_buf);
void fhost_rx_buf_forward(struct fhost_rx_buf_tag *buf);
void fhost_rx_buf_forward_no_free(struct fhost_rx_buf_tag *buf);
#if (defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF) && defined(CFG_SOFTAP))
int fhost_rxbuf_send_type(struct fhost_rx_buf_tag *buf, struct mac_addr *da, uint8_t *machdr_len);
#endif
void fhost_rx_monitor_cb(void *buf, bool uf);
int e2a_data_send(uint8_t *mac80211_data, uint32_t length);
#ifdef CFG_HOSTIF_OPT
int e2a_data_send_direct(uint8_t *mac80211_data, uint32_t length);
#endif

#if NX_CSI
void fhost_rx_set_csi_cb(cb_fhost_rx cb, void *arg);
void fhost_rx_csi_cb(void *buf);
#endif
#if NX_UF_EN
void fhost_rx_uf_buf_push(struct fhost_rx_uf_buf_tag *);
#endif /* NX_UF_EN */

/// @}

#endif // _FHOST_RX_H_
