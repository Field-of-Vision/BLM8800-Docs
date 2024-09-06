#ifndef WIFI_WH_HEADSET_H
#define WIFI_WH_HEADSET_H

#include <stdint.h>
#include "rtos.h"
#include "ring_buffer.h"
#include "app_media.h"
#include "wifi_voice.h"

int wifi_wh_headset_playback_ring_buffer_lock(void);
int wifi_wh_headset_playback_ring_buffer_unlock(void);
int wifi_wh_headset_capture_ring_buffer_lock(void);
int wifi_wh_headset_capture_ring_buffer_unlock(void);
ring_buffer_t *wifi_wh_headset_playback_ring_buffer_get(void);
ring_buffer_t *wifi_wh_headset_capture_ring_buffer_get(void);
void wifi_wh_headset_capture_data_ready(int timeout, bool isr);
uint32_t wifi_wh_headset_playback_handler(uint8_t *buf, uint32_t len);
uint32_t wifi_wh_headset_capture_handler(uint8_t *buf, uint32_t len);
int wifi_wh_headset_init(void);
int wifi_wh_headset_deinit(void);
int wifi_wh_headset(MediaControlType cmd, MediaCommonStruct* param);
void wifi_wh_headset_led_handler_register(wifi_voice_led_handler_t handler);

#endif
