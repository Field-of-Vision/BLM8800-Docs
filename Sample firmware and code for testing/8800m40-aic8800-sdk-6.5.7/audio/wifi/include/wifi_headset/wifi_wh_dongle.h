#ifndef WIFI_WH_DONGLE_H
#define WIFI_WH_DONGLE_H

#include "wifi_voice.h"

int wifi_wh_dongle_init(void);
int wifi_wh_dongle_deinit(void);
void wifi_wh_dongle_led_handler_register(wifi_voice_led_handler_t handler);
void wifi_wh_dongle_mix_handler_register(wifi_voice_mix_handler_t handler);

#endif
