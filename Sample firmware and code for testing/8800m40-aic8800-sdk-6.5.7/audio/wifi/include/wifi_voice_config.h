#ifndef WIFI_VOICE_CONFIG_H
#define WIFI_VOICE_CONFIG_H

#include <stdint.h>
#include <stdbool.h>

bool wifi_voice_switch_channel_en_get(void);
uint32_t wifi_voice_config_data_stop_check_period_ms_get(void);
uint32_t wifi_voice_config_msg_queue_elt_nb_get(void);
uint32_t wifi_voice_config_user_cmd_max_size_get(void);

#endif
