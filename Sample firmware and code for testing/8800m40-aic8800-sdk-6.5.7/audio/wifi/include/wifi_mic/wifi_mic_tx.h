#ifndef WIFI_MIC_TX_H
#define WIFI_MIC_TX_H

#include <stdint.h>
#include "rtos.h"
#include "ring_buffer.h"
#include "app_media.h"
#include "wifi_voice.h"

void wifi_mic_tx_led_handler_register(wifi_voice_led_handler_t handler);
int wifi_mic_tx_playback_ring_buffer_lock(void);
int wifi_mic_tx_playback_ring_buffer_unlock(void);
int wifi_mic_tx_capture_ring_buffer_lock(void);
int wifi_mic_tx_capture_ring_buffer_unlock(void);
ring_buffer_t *wifi_mic_tx_playback_ring_buffer_get(void);
ring_buffer_t *wifi_mic_tx_capture_ring_buffer_get(void);
void wifi_mic_tx_capture_data_ready(int timeout, bool isr);
uint32_t wifi_mic_tx_playback_handler(uint8_t *buf, uint32_t len);
uint32_t wifi_mic_tx_capture_handler(uint8_t *buf, uint32_t len);
int wifi_mic_tx_playback(MediaControlType cmd, MediaCommonStruct* param);
int wifi_mic_tx_capture(MediaControlType cmd, MediaCommonStruct* param);
int wifi_mic_tx_playback_data_write(uint8_t *buf, uint32_t len);
int wifi_mic_tx_init(void);
int wifi_mic_tx_deinit(void);
void wifi_mic_tx_force_pairing(void);

#endif
