#ifndef _RAWDATA_IF_H_
#define _RAWDATA_IF_H_

typedef void (*wifi_raw_data_handler_t)(uint8_t *data, uint32_t size);

typedef enum {
    RAWDATA_PM_LEVEL_ACTIVE       = 0,
    RAWDATA_PM_LEVEL_LIGHT_SLEEP  = 1,
    RAWDATA_PM_LEVEL_LEVEL_NUM
} RAWDATA_POWER_MODE_LEVEL_T;

/**
 ****************************************************************************************
 * @brief * rawdata_if_init : Initial basic interface as STA.
 *
 * @param[]  None
 ****************************************************************************************
 */
void rawdata_if_init(void);

/**
 ****************************************************************************************
 * @brief * rawdata_if_deinit : Deinitial interface
 *
 * @param[]  None
 ****************************************************************************************
 */
void rawdata_if_deinit(void);

/**
 ****************************************************************************************
 * @brief * rawdata_if_tx_data : TX raw data(802.11).
 *
 * @param[]  frame: data to tx
             frame_len : data length
 ****************************************************************************************
 */
int rawdata_if_tx_data(uint8_t *frame, uint16_t frame_len);
/**
 ****************************************************************************************
 * @brief * rawdata_if_set_channel : Select channel to tx/rx raw data.
 *
 * @param[]  ch_num: channel num (2.4G : 1 ~ 14, 5G : 36 ~ 165)
 ****************************************************************************************
 */
void rawdata_if_set_channel(uint8_t ch_num);
/**
 ****************************************************************************************
 * @brief * rawdata_if_set_bssid : Set peer entry mac address as bssid .
 *
 * @param[]  bssid
 ****************************************************************************************
 */
void rawdata_if_set_bssid(uint8_t *bssid);
/**
 ****************************************************************************************
 * @brief * rawdata_if_set_mac_addr : Set own mac address.
 *
 * @param[]  Notice: MUST called before 'rawdata_if_init'
 ****************************************************************************************
 */
void rawdata_if_set_mac_addr(uint8_t *macaddr);
/**
 ****************************************************************************************
 * @brief * rawdata_if_rx_data_cb_register : Register API to get rx data.
 *
 * @param[]  eg.
 *              static void raw_data_handler(uint8_t *data, uint32_t size)
 *              {
 *                  dump_buf(data, size);
 *              }
 *              rawdata_if_rx_data_cb_register(raw_data_handler);
 ****************************************************************************************
 */
void rawdata_if_rx_data_cb_register(wifi_raw_data_handler_t handler);

wifi_raw_data_handler_t get_rawdata_if_rx_data_cb(void);

void rawdata_if_set_fixed_rate(uint8_t format_idx, uint16_t rate_idx, uint8_t pre_type);

void rawdata_sleep_level_set(RAWDATA_POWER_MODE_LEVEL_T level);

#endif /* _RAWDATA_IF_H_ */
