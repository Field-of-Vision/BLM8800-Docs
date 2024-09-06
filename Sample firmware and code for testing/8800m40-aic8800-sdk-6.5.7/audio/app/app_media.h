#ifndef _APP_MEDIA_H_
#define _APP_MEDIA_H_

#include <stdbool.h>
#include <stdint.h>
#include "plf.h"
#include "audio_types.h"
#include "audio_tws.h"
#if PLF_BT_STACK || PLF_AUDIO
#include "prompt.h"
#endif

typedef enum{
    AUD_COMMON,
    AUD_INTERNAL,
    AUD_MUSIC,
    AUD_RECORD,
    AUD_FM,
    AUD_BT_A2DP,
    AUD_BT_SCO,
    AUD_BLE,
    AUD_LINEIN,
    AUD_WIFI,
    AUD_MAX,
    AUD_NULL = 0xFF
}AUD_REQ_MODE;

typedef uint8_t MediaA2dpCodecType;
#define MEDIA_CODEC_TYPE_SBC           0x00
#define MEDIA_CODEC_TYPE_MPEG1_2_AUDIO 0x01
#define MEDIA_CODEC_TYPE_MPEG2_4_AAC   0x02
#define MEDIA_CODEC_TYPE_ATRAC         0x04
#define MEDIA_CODEC_TYPE_NON_A2DP      0xFF

typedef uint16_t MediaScoCodecType;
#define MEDIA_SCO_CODEC_NONE          0x0000
#define MEDIA_SCO_CODEC_CVSD          0x0001
#define MEDIA_SCO_CODEC_MSBC          0x0002

typedef struct{
    uint8_t mute;
    uint8_t extera6dB;  //vol_level + 6dB
    uint8_t extera12dB; //vol_level + 12dB
    uint8_t vol_level;  //min 0:-26dB max 0x3f:5.5dB (0~63) level+1=0.5db
    int vol_up_down;    //val* 1 = val * 0.5dB
}SysVolumeOut;

typedef struct{
    uint8_t mute;
    uint8_t vol_level;  //min 1:-12dB max 0xf:16dB (0~15) level+1=2db
    int vol_up_down;    //val* 1 = val * 2dB
}SysVolumeIn;

typedef struct{
    SysVolumeOut vol_out;
    SysVolumeIn  vol_in;
}MediaVolumeCtrl;

typedef struct{
    MediaA2dpCodecType a2dpcodec;
    uint8_t numBlocks;//used for SBC (4, 8, 12, or 16)
    uint8_t numSubBands;//used for SBC (4 or 8)
    AUD_DPLL_MODE dpll_mode;
    AUD_CH_NUM_T channel;
    AUD_SAMPRATE_T samplerate;
}MediaAudioCtrl;

typedef struct{
    MediaScoCodecType  scocodec;
    AUD_DPLL_MODE dpll_mode;
    AUD_CH_NUM_T channel;
    AUD_SAMPRATE_T samplerate;
}MediaVoiceCtrl;

typedef struct{
    MediaSyncParamStruct sync_param;
    uint32_t start_trig_num;
    uint32_t trig_time_delta;
    bool   need_clean;
}MediaSyncCtrl;

typedef struct{
    uint8_t audio_id;
    uint8_t times;
}MediaInternalAudCtrl;

typedef struct{
    union {
        MediaVolumeCtrl vol_ctrl;
        MediaAudioCtrl aud_ctrl;
        MediaVoiceCtrl voc_ctrl;
        MediaSyncCtrl sync_ctrl;
        MediaInternalAudCtrl internal_aud;
        uint8_t stream_bit;
    }p;
}MediaCommonStruct;


/*****
start of MediaControlType
******/
typedef uint8_t MediaControlType;
enum{
    MC_NULL     = 0x00,
    MC_OPEN           ,
    MC_CLOSE          ,
    MC_PLAY           ,
    MC_SUSPEND        ,
    MC_REPLAY         ,
    MC_PAUSE          ,
    MC_STOP           ,
    MC_MUTE           ,
    MC_PRELOAD_PLAY   ,
    MC_SET_TRIGNUM    ,
    MC_SYNC_PARAM     ,
    MC_TRIGNUM_PLAY   ,
    MC_SETVOLUME      ,//set volume
    MC_DONE           ,
};
/*****
end of MediaControlType
******/

int AudSend_Common_Command(AUD_REQ_MODE mode, MediaControlType cmd, MediaCommonStruct* param);
int AppSend_Mode_MediaCommand(AUD_REQ_MODE mode,MediaControlType cmd, MediaCommonStruct* param);
int AppSend_PlayInternalAudio(PROMPT_ID_ENUM audio_id, uint8_t times);
void AppSend_StopInternalAudio(void);
#if (PLF_BT_STACK == 1)
int AppReceive_A2dpData(uint8_t *buf, uint32_t len ,uint8_t sbc_frame_num ,AUD_SAMPRATE_T samplerate);
int AppReceive_ScoData(uint8_t *buf, uint32_t len);
int AppPrepareSend_ScoData(uint8_t *buf, uint32_t len);
#endif
int AppSend_MediaCommand(MediaControlType cmd, MediaCommonStruct* param);

#endif
