#ifndef AICADPA2DP
#define AICADPA2DP
#include "aic_adp_type.h"



#define A2DP_CSIE_SAMP_FREQ_MSK    0xF0    /* b7-b4 sampling frequency */
#define A2DP_CSIE_SAMP_FREQ_16     0x80    /* b7:16  kHz */
#define A2DP_CSIE_SAMP_FREQ_32     0x40    /* b6:32  kHz */
#define A2DP_CSIE_SAMP_FREQ_44     0x20    /* b5:44.1kHz */
#define A2DP_CSIE_SAMP_FREQ_48     0x10    /* b4:48  kHz */
#define A2DP_CSIE_SAMP_FREQ_96     0xF0 

#define A2DP_SBC_CHANNEL_MODE_MSK    0x0F
#define A2DP_SBC_BLOCK_LENGTH_MSK    0xF0
#define A2DP_SBC_SUBBANDS_MSK        0x0C

typedef U8 bt_a2dp_adp_state;
#define A2DP_ADP_STATE_IDLE                    0
#define A2DP_ADP_STATE_CLOSE                   1
#define A2DP_ADP_STATE_PENDING                 2
#define A2DP_ADP_STATE_CONNECTED               3
#define A2DP_ADP_STATE_OPEN                    4
#define A2DP_ADP_STATE_PLAY                    5
#define A2DP_ADP_STATE_PAUSE                   6
#define A2DP_ADP_STATE_STOP                    7

typedef U8 CodecType;

#define AVDTP_CODEC_TYPE_SBC           0x00
#define AVDTP_CODEC_TYPE_MPEG_AUDIO    0x01
#define AVDTP_CODEC_TYPE_MPEG_AAC      0x02
#define AVDTP_CODEC_TYPE_ATRAC         0x04
#define AVDTP_CODEC_TYPE_NON_A2DP      0xFF

typedef struct _A2DP_AUDIO_CAP{
    CodecType codec_type;
    U8 sample_rate_bit;
    U8 sbc_frame_number;
    U8 channel;
    U8 numBlocks;//used for SBC (4, 8, 12, or 16)
    U8 numSubBands;//used for SBC (4 or 8)
}A2DP_AUDIO_CAP;

typedef struct _A2DP_AUDIO_DATA{
    U8 *data;
    U16 datalen;
    U16 headerlen;
}A2DP_AUDIO_DATA;

typedef uint8_t AdpAvdtpCodecType;

typedef enum {
    BT_A2DP_SOURCE = 0,
    BT_A2DP_SINK
}BT_A2DP_ROLE;

typedef struct {
    A2DP_AUDIO_CAP *audioCodecP;
}A2dp_Signaling_t;

typedef struct {
    A2DP_AUDIO_CAP *audioCodecP;
    A2DP_AUDIO_DATA *audioDataP;
}A2dp_Media_t;

typedef struct _AIC_ADP_A2DP_EVENT_{
    BT_ADDR bdaddr;
    BT_A2DP_ROLE role;
    union {
        A2dp_Signaling_t signalingP;
        A2dp_Media_t mediaP;
        bt_err_type disc_reason;
    }p;
}AIC_ADP_A2DP_EVENT;

void aic_adp_a2dp_source_start(void);
void aic_adp_a2dp_source_suspend(void);
Status_BTDef aic_adp_a2dp_send_sbc_data(BT_ADDR bdaddr,U8       * data,U16     dataLen,U16 frameSize);

void aic_adp_a2dp_support_cb(void);//contend protection
void aic_adp_a2dp_register_source(void);
void aic_adp_a2dp_register_sink_sbc(void);
void aic_adp_a2dp_register_sink_aac(void);
void aic_adp_a2dp_source_init(void);
void aic_adp_a2dp_init(void);

Status_BTDef aic_adp_a2dp_connect(BT_ADDR bdaddr);
Status_BTDef aic_adp_a2dp_disconnect(BT_ADDR bdaddr);
A2DP_AUDIO_CAP *aic_adp_a2dp_get_audio_cap_by_addr(BT_ADDR bdaddr);
Status_BTDef aic_adp_a2dp_source_connect(BT_ADDR bdaddr);



#endif
