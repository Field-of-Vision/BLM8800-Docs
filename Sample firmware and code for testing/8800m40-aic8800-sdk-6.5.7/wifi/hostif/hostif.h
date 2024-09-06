/**
 * @file: hostif.h
 */
#ifndef _HOSTIF_H_
#define _HOSTIF_H_

#include "chip.h"
#include "plf.h"
#include "co_math.h"
#if defined(CFG_DEVICE_IPC)
#include "devipc_cmd.h"
#endif

/** VNET filter type */
#define VNET_FILTER_DIRECT 0
#define VNET_FILTER_SHARED 1


/**
 * Enums
 */

/** Host type define */
typedef enum
{
    SDIO_HOST,
    USB_HOST,
    NUM_HOST_TYPE

} HOST_TYPE_T;

/** Host mode define */
typedef enum
{
    HOST_WLAN_MODE,
    HOST_VNET_MODE,
    HOST_RAWDATA_MODE,
    NUM_HOST_MODE
} HOST_MODE_T;

/** Host error type define */
typedef enum
{
    HOST_NO_ERROR       = 0,
    HOST_NOT_READY      = 1,
    HOST_TX_TIMEOUT     = 2,
    HOST_MEM_ALLOC_FAIL = 3,

    HOST_HW_ERROR       = CO_BIT(15)

} HOST_ERROR_T;

typedef enum {
    HOSTIF_MSG_RXC = 0,
    HOSTIF_MSG_TXC,
    DEVIPC_CUST_MSG_RXC,
    DEVIPC_CUST_MSG_IND,
    HOSTIF_DATA_RXC,
    HOSTIF_DATA_TXC,
    HOSTIF_READY,
    HOSTIF_INIT_DONE,
    HOSTIF_BLE_INIT_DONE,
    HOSTIF_BLE_DEINIT_DONE,
    HOSTIF_DEINIT_DONE,
    HOSTIF_MSG_MAX
} HOSTIF_MSG_ID_T;

/**
 * Structs
 */

/** This struct define a host supported operations collection. */
typedef struct
{
    void (*replenish_rxq)(void);
    void (*pop_front_txq)(void);
    void (*send)(uint8_t *data);
} host_interface_ops;

/** This struct define a host interface structure. */
typedef struct host_interface_s
{
    /** Flag indicating if rx data header is omitted */
    bool rdh_omitted;
    const host_interface_ops *ops;

} host_interface_t;

/// Generic Message format
struct hostif_msg {
    /// ID of the message
    uint16_t id;
    /// Length, in bytes, of the message
    uint16_t len;
    /// Pointer to the message
    void *data;
};

/**
 * Host buffer defination as below:
 * +-----------+
 * | host_type |  <--------------------------- start
 * +-----------+
 * | data_len  |
 * +-----------+
 * | b |   d   |  <--------------------------- data
 * | u |   a   |                ^           ^
 * | f |   t   |                | data_len  |
 * | f |   a   |                V           |  buff_size
 * | e |-------|  ----------------          |
 * | r |   .   |                            V
 * |   |   .   |  ----------------------------
 * +-----------+
 *
 */
typedef struct
{
    /** - Host type */
    uint16_t type;
    /** - Actual data length */
    uint16_t data_len;
    /** - Data start */
    uint32_t data[1];
} host_buffer_t;

#define HOST_BUFFER_HDR_LEN         offsetof(host_buffer_t, data)

/**
 * Inline funcs
 */

__INLINE void * hostb_buf2data(host_buffer_t const *buf)
{
    return (void *)(((uint8_t *)buf) + HOST_BUFFER_HDR_LEN);
}

__INLINE host_buffer_t * hostb_data2buf(void const *data_ptr)
{
    return (host_buffer_t *)(((uint8_t *)data_ptr) - HOST_BUFFER_HDR_LEN);
}

/**
 * Host data defination as below:
 * +--------------+
 * | payload_len  |  <--------------- header
 * +--------------+
 * | payload_type |
 * +--------------+
 * | reserved     |
 * +--------------+
 * |              |  <--------------- payload
 * |              |                ^
 * |              |                |
 * | payload      |                |  payload_len
 * |              |                |
 * |              |                V
 * |              |  ----------------
 * +--------------+
 *
 */
typedef struct
{
    /** - Payload len */
    uint16_t plen;
    /** - Payload type */
    uint8_t ptype;
    /** - Reserved */
    uint8_t reserved;
    /** - Payload start */
    uint32_t payload[1];
} host_data_t;

#define HOST_DATA_HDR_LEN       offsetof(host_data_t, payload)

__INLINE void * hostd_data2payload(host_data_t const *hdata)
{
    return (void *)(((uint8_t *)hdata) + HOST_DATA_HDR_LEN);
}

__INLINE host_data_t * hostd_payload2data(void const *pld_ptr)
{
    return (host_data_t *)(((uint8_t *)pld_ptr) - HOST_DATA_HDR_LEN);
}

enum {
    HOSTD_TYPE_DATA         = 0x00,
    HOSTD_TYPE_DATA1        = 0x01,

    HOSTD_TYPE_CFG          = 0x10,
    HOSTD_TYPE_CFG_CMD_RSP  = 0x11,
    HOSTD_TYPE_CFG_DATA_CFM = 0x12
};

#define IS_HOSTD_CFG_TYPE(type)     (((type) & 0x10) ? 1 : 0)

typedef void (*host_rxc_msg_handler_t)(uint8_t *raw_data, uint32_t length); // raw data with no header

/**
 * Funcs
 */

/**
 * If this api isn't called, msg will be handled internal(see: custom_msg_state)
 */
void host_rxc_msg_handler_register(host_rxc_msg_handler_t handler);
void process_host_rxc_msg(struct hostif_msg *msg);
void process_host_txc_msg(struct hostif_msg *msg);
void process_host_rxc_data(struct hostif_msg *msg);
#if defined(CFG_DEVICE_IPC)
void process_devipc_rxc_custom_msg(struct hostif_msg *msg);
void process_devipc_ind_custom_msg(struct hostif_msg *msg);
#endif
void process_host_if_ready(struct hostif_msg *msg);
void process_host_if_init_done(struct hostif_msg *msg);
void host_if_sdio_ioen_loop(uint32_t timeout_us, void *func_cb);
void host_if_usb_init_done(void);
#if (PLF_WIFI_STACK)
void host_if_pd_wificore(void);
void host_if_pu_wificore(void);
#endif
void init_host(int is_repower);
void host_if_repower(void);
void host_if_poweroff(void);
void host_if_stop(void);
void host_if_sw_init_sdio(void);
void host_if_hw_init_sdio(void);
void host_if_stop_sdio(void);
void host_if_deinit_sdio(void);
void host_if_sw_init_usb(void);
void host_if_hw_init_usb(void);
void host_if_stop_usb(void);
void host_if_deinit_usb(void);
void host_if_ready_indicate(HOST_TYPE_T type);
void host_if_init_done_indicate(HOST_TYPE_T type);
void host_if_ble_init_done_indicate(void);
void host_if_ble_deinit_done_indicate(void);
void host_if_rawdata_rx_callback(unsigned char *rx_data, unsigned int rx_len);
#ifdef CONFIG_RWNX_LWIP
void host_if_rxc_data_handler(unsigned char *rx_data, unsigned int rx_len);
#endif

/**
 * @brief       Send raw data to host
 * @param[in]   tx_data Data address to send
 * @param[in]   tx_len Byte length to send
 * @return      Error code, -1: failed to alloc host buff, inform app to resend
 *                           0: success
 *                           1: success, resend internally
 */
int host_if_data_send(unsigned char *tx_data, unsigned int tx_len);
void host_if_register(const host_interface_t *host_if);
void host_if_unregister(void);
void host_send(uint16_t type, uint8_t *data);
void host_rx_msg_comp(uint8_t *rxbuf);
void host_tx_msg_comp(void);
void host_rx_data_comp(void *rxbuf);
#if defined(CFG_DEVICE_IPC)
void devipc_custmsg_rx_comp(uint8_t *rxbuf);
void host_if_indicate_custmsg(dbg_custom_msg_ind_t *ind);
#endif

/*
** alloc buffer for host, message_t reserved
*/
void *host_buffer_alloc(uint16_t type, uint16_t size);
/*
** free buffer for host, message_t reserved
*/
void host_buffer_free(void *data);
#ifdef CFG_HOSTIF_OPT
/*
** For data from ipc
** free buffer to ipc_shared_env.rx_e2a_hostbuf_free_list
*/
void host_buffer_free_data_direct(void *data);
#endif /* CFG_HOSTIF_OPT */

#if defined(CFG_DEVICE_IPC)
int hostif_ipc_cntrl_init(uint32_t ipc_irq_prio);
#endif

int hostif_application_init(void);
const host_interface_t *get_host_interface(void);

#endif /* _HOSTIF_H_ */
