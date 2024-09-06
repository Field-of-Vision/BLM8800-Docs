#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "wifi_voice_config.h"
#include "mac.h"
#include "sleep_api.h"

#define WIFI_SWITCH_CHANNEL_EN    0

#define DATA_STOP_CHECK_PERIOD_MS           (2 * 1000)
#define MSG_QUEUE_ELT_NB                    20

#define USER_CMD_MAX_SIZE                   32

bool wifi_voice_switch_channel_en_get(void)
{
    return WIFI_SWITCH_CHANNEL_EN;
}

uint32_t wifi_voice_config_data_stop_check_period_ms_get(void)
{
    return DATA_STOP_CHECK_PERIOD_MS;
}

uint32_t wifi_voice_config_msg_queue_elt_nb_get(void)
{
    return MSG_QUEUE_ELT_NB;
}

uint32_t wifi_voice_config_user_cmd_max_size_get(void)
{
    return USER_CMD_MAX_SIZE;
}

