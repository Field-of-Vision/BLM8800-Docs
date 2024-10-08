#ifndef WIFI_MIC_CONFIG_H
#define WIFI_MIC_CONFIG_H

#include <stdint.h>

uint8_t wifi_mic_config_band_get(void);
uint16_t wifi_mic_config_bcn_interval_get(void);
uint32_t wifi_mic_config_pariring_timeout_get(void);
#ifdef CFG_WIFI_ENGINEERING_MODE
bool wifi_mic_config_enable_em_chan_get(void);
uint8_t wifi_mic_config_em_chan_index_get(void);
#endif
uint8_t wifi_mic_config_mic_tx_pwr_mode_get(void);
uint8_t wifi_mic_config_channel_get(void);
uint8_t *wifi_mic_config_mic_rx_mac_addr_get(void);
uint8_t *wifi_mic_config_mic_tx_mac_addr_get(void);
uint32_t wifi_mic_config_samprate_get(void);
uint16_t wifi_mic_config_tx2rx_air_pkt_size_ms_get(void);
uint16_t wifi_mic_config_tx2rx_air_pkt_size_get(void);
uint8_t wifi_mic_config_mic_tx_num_get(void);
uint8_t wifi_mic_config_mic_tx_capture_in_ch_num_get(void);
uint8_t wifi_mic_config_mic_tx_capture_out_ch_num_get(void);
uint8_t wifi_mic_config_mic_tx_playback_ch_num_get(void);
uint8_t wifi_mic_config_mic_rx_playback_ch_num_get(void);
uint16_t wifi_mic_config_mic_tx_capture_frame_size_ms_get(void);
uint16_t wifi_mic_config_mic_tx_playback_frame_size_ms_get(void);
uint16_t wifi_mic_config_mic_rx_playback_frame_size_ms_get(void);
uint16_t wifi_mic_config_mic_tx_capture_frame_size_get(void);
uint16_t wifi_mic_config_mic_tx_playback_frame_size_get(void);
uint16_t wifi_mic_config_mic_rx_playback_frame_size_get(void);
uint16_t wifi_mic_config_mic_tx_capture_ring_buffer_size_ms_get(void);
uint16_t wifi_mic_config_mic_tx_playback_ring_buffer_size_ms_get(void);
uint16_t wifi_mic_config_mic_rx_playback_ring_buffer_size_ms_get(void);
uint16_t wifi_mic_config_mic_rx_playback_start_level_size_ms_get(void);
uint32_t wifi_mic_config_mic_tx_capture_ring_buffer_size_get(void);
uint32_t wifi_mic_config_mic_tx_playback_ring_buffer_size_get(void);
uint32_t wifi_mic_config_mic_rx_playback_ring_buffer_size_get(void);
uint32_t wifi_mic_config_mic_rx_playback_start_level_size_get(void);
uint32_t wifi_mic_config_sta_check_period_ms_get(void);

#endif
