#ifndef _BT_AUDIO_PLAYER_H_
#define _BT_AUDIO_PLAYER_H_

#include <stdint.h>
#include <stdbool.h>
#include "audio_types.h"
#include "app_media.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /* Number of blocks used to encode the stream (4, 8, 12, or 16) */
    uint8_t   numBlocks;

    /* The number of subbands in the stream (4 or 8) */
    uint8_t   numSubBands;

    /* The number of channels in the stream (calculated from channelMode) */
    uint8_t   numChannels;

    /* numBlocks, numSubbands, numChannels have been configed */
    bool      inited;
}A2DP_SBC_CFG_T;

extern A2DP_SBC_CFG_T a2dp_sbc_cfg;

void bt_audio_set_codec_type(uint8_t codec_type);
uint8_t bt_audio_get_codec_type(void);
void bt_audio_set_sample_rate(AUD_SAMPRATE_T sample_rate);
AUD_SAMPRATE_T bt_audio_get_sample_rate(void);
int bt_audio_buffer_write(uint8_t *data, uint32_t len, uint8_t frame_num,AUD_SAMPRATE_T samplerate);
int bt_audio_player(MediaControlType cmd, MediaCommonStruct* param);
int bt_audio_init(void);
int bt_audio_deinit(void);
int bt_audio_send_prestart_command(void);
void bt_audio_clean_sync_param(void);
void bt_audio_set_local_speed_mode(AUD_SPEED_MODE speed_mode);
AUD_SPEED_MODE bt_audio_get_local_speed_mode(void);
void bt_audio_check_process_lost_num(bool contin,bool lost);
uint32_t bt_audio_get_inbuffer_frame_num(void);


#ifdef __cplusplus
}
#endif

#endif

