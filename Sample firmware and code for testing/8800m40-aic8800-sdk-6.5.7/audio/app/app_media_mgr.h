#ifndef _APP_MEDIA_MGR_H_
#define _APP_MEDIA_MGR_H_
#include "app_audio.h"

typedef enum{
    MODE_PRIORITY_MIN,
    MODE_PRIORITY_WIFI,
    MODE_PRIORITY_BT_A2DP,
    MODE_PRIORITY_BT_SCO,
    MODE_PRIORITY_INTERNAL,
    MODE_PRIORITY_MAX,
}MODE_PRIORITY;

void app_media_set_last_param(AUD_REQ_MODE mode,MediaControlType cmd);
void app_media_play(AUD_REQ_MODE mode,MediaControlType cmd, MediaCommonStruct* param, bool in_order);
void app_media_play_internalaudio(PROMPT_ID_ENUM audio_id);
void app_media_mgr_init(void);
bool app_media_mgr_set_command(MediaControlType cmd, MediaCommonStruct* param);
bool app_media_mgr_send_command(AUD_REQ_MODE mode,MediaControlType cmd, MediaCommonStruct* param);
AUD_REQ_MODE app_media_get_playing_mode(void);

#endif
