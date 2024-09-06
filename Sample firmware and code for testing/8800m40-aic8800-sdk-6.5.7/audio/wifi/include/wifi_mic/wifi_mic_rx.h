#ifndef WIFI_MIC_RX_H
#define WIFI_MIC_RX_H

#include "wifi_voice.h"

int wifi_mic_rx_init(void);
int wifi_mic_rx_deinit(void);
int wifi_mic_rx_playback(MediaControlType cmd, MediaCommonStruct* param);
void wifi_mic_rx_led_handler_register(wifi_voice_led_handler_t handler);
void wifi_mic_rx_mix_handler_register(wifi_voice_mix_handler_t handler);
void wifi_mic_rx_force_pairing(void);

#endif
