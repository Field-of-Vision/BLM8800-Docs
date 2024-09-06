#ifndef _BT_VOICE_PLAYER_H_
#define _BT_VOICE_PLAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "app_media.h"

void sco_clean_sync_param(void);
uint32_t sco_get_input_frame_num(void);
uint32_t sco_get_cacheing_0_num(void);
uint32_t sco_get_drop_frame_num(void);
void bt_voice_ds_buffer_clean(void);
int bt_voice_ds_buffer_write(uint8_t *buf, uint32_t len);
int bt_voice_us_buffer_write(uint8_t *buf, uint32_t len);
int bt_voice_prepare_us_frame(uint8_t *buf, uint32_t len);
int bt_voice_init(void);
int bt_voice_deinit(void);
void bt_voice_us_soft_mute_set(bool mute);
void bt_voice_ds_soft_mute_set(bool mute);
uint16_t bt_voice_get_codec_type(void);
void bt_voice_set_codec_type(uint16_t codec_type);
void bt_voice_set_playback_ch_num(AUD_CH_NUM_T ch_num);
AUD_CH_NUM_T bt_voice_get_playback_ch_num(void);
void bt_voice_set_capture_ch_num(AUD_CH_NUM_T ch_num);
AUD_CH_NUM_T bt_voice_get_capture_ch_num(void);
AUD_SAMPRATE_T bt_voice_get_device_sample_rate(void);
AUD_SAMPRATE_T bt_voice_get_codec_sample_rate(void);
int bt_voice_player(MediaControlType cmd, MediaCommonStruct* param);

#ifdef __cplusplus
}
#endif

#endif

