#include "rtos.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "plf.h"
#include "app_media.h"
#include "app_audio.h"
#include "app_media_mgr.h"
#if (PLF_ASIO == 1)
#include "asio.h"
#include "asio_src.h"
#endif
#if (PLF_BT_AUDIO == 1)
#include "bt_audio_player.h"
#if (PLF_BT_PROMPT == 1)
#include "bt_prompt_player.h"
#endif
#include "bt_voice_player.h"
#endif
#if (PLF_WIFI_STACK == 1) && (PLF_WIFI_AUDIO == 1)
#include "wifi_wh_headset.h"
#endif
#include "prompt.h"

uint8_t g_current_player = AUD_NULL;

int Aud_Open_Close(AUD_REQ_MODE mode, MediaControlType cmd, MediaCommonStruct* param)
{
    int status = 0;

    switch (mode) {
#if (PLF_BT_STACK == 1)
#if (PLF_BT_AUDIO == 1)
    case AUD_INTERNAL:
#if (PLF_BT_PROMPT == 1)
        status = bt_prompt_player(cmd, param);
#else
        status = 0;
#endif
        break;
    case AUD_BT_A2DP:
        status = bt_audio_player(cmd, param);
        break;
    case AUD_BT_SCO:
        status = bt_voice_player(cmd, param);
        break;
#endif
#endif
#if (PLF_WIFI_STACK == 1) && (PLF_WIFI_AUDIO == 1)
    case AUD_WIFI:
        status = wifi_wh_headset(cmd, param);
        break;
#endif
    default:
        break;
    }

    return status;
}

int AudSend_Common_Command(AUD_REQ_MODE mode, MediaControlType cmd, MediaCommonStruct* param)
{
    int status = 0;

    if (cmd != MC_SET_TRIGNUM && cmd != MC_SYNC_PARAM && cmd != MC_NULL)
        TRACE("%s gcp:%d mode:%d cmd:%d\n", __func__, g_current_player, mode, cmd);

    switch (cmd) {
    case MC_DONE: {
        app_media_set_last_param(AUD_NULL,MC_NULL);
        break;
    }
    case MC_STOP: {
        if (g_current_player != AUD_NULL) {
            status = Aud_Open_Close(g_current_player, cmd, param);
            if (0 == status) {
                g_current_player = AUD_NULL;
            }
        }
        break;
    }
    case MC_OPEN:
    case MC_PLAY: {
        if (g_current_player != mode) {
            status = Aud_Open_Close(g_current_player, MC_SUSPEND, param);
            if (0 == status) {
                g_current_player = AUD_NULL;
            }
        }
        status = Aud_Open_Close(mode, cmd, param);
        if (0 != status) {
            g_current_player = mode;
        }
        break;
    }
    case MC_REPLAY:
        if (g_current_player != mode) {
            status  = Aud_Open_Close(g_current_player, MC_STOP, param);
            if (0 == status) {
                g_current_player = AUD_NULL;
            }
        }
        status = Aud_Open_Close(mode, cmd, param);
        if (0 != status) {
            g_current_player = mode;
        }
        break;
    case MC_PRELOAD_PLAY: {
        if (g_current_player != mode) {
            status = Aud_Open_Close(g_current_player, MC_STOP, param);
            if (0 == status) {
                g_current_player = AUD_NULL;
            }
            TRACE("mode not match:%d/%d, MC_PRELOAD_PLAY fail\n", g_current_player, mode);
        } else {
            status = Aud_Open_Close(mode, cmd, param);
            if (0 != status) {
                g_current_player = mode;
            }
        }
        break;
    }
    case MC_SETVOLUME: {
        MediaVolumeCtrl* vol_ctrl = &param->p.vol_ctrl;
        //vol_out handle
        if(vol_ctrl->vol_out.mute) {
            asio_stream_mute(AUD_STREAM_PLAYBACK);
        } else {
            if(vol_ctrl->vol_out.vol_up_down != 0) {
                if(vol_ctrl->vol_out.vol_up_down > 0) {
                    uint8_t up_step = (uint8_t)vol_ctrl->vol_out.vol_up_down;
                    asio_stream_raw_digital_volume_up(AUD_STREAM_PLAYBACK,up_step);
                } else {
                    uint8_t down_step = (uint8_t)(0-vol_ctrl->vol_out.vol_up_down);
                    asio_stream_raw_digital_volume_down(AUD_STREAM_PLAYBACK,down_step);
                }
            } else {
                uint8_t vol_frac = 0;
                uint8_t vol_int = 0;
                vol_frac = vol_ctrl->vol_out.vol_level & 0x3F;
                if(vol_ctrl->vol_out.extera6dB) {
                    vol_int |= (1<<6);
                }
                if(vol_ctrl->vol_out.extera12dB) {
                    vol_int |= (1<<7);
                }
                TRACE("volume out %x,%x\n",vol_frac,vol_int);
                if(vol_int|vol_frac)
                    asio_stream_raw_digital_volume_set(AUD_STREAM_PLAYBACK,(vol_int|vol_frac));
                else
                    TRACE("volume out change error\n");
            }
        }

        //vol_in handle
        if(vol_ctrl->vol_in.mute) {
            asio_stream_mute(AUD_STREAM_CAPTURE);
        } else {
            if(vol_ctrl->vol_in.vol_up_down != 0) {
                if(vol_ctrl->vol_in.vol_up_down > 0) {
                    uint8_t up_step = (uint8_t)vol_ctrl->vol_in.vol_up_down;
                    asio_stream_raw_digital_volume_up(AUD_STREAM_CAPTURE,up_step);
                } else {
                    uint8_t down_step = (uint8_t)(0-vol_ctrl->vol_in.vol_up_down);
                    asio_stream_raw_digital_volume_down(AUD_STREAM_CAPTURE,down_step);
                }
            } else {
                uint8_t vol_frac = 0;
                vol_frac = vol_ctrl->vol_in.vol_level & 0x0F;
                TRACE("volume in %x\n",vol_frac);
                if(vol_frac)
                    asio_stream_raw_digital_volume_set(AUD_STREAM_CAPTURE,vol_frac);
                else
                    TRACE("volume in change error\n");
            }
        }
        break;
    }
#if (PLF_BT_AUDIO == 1 && !PLF_BLE_ONLY)
    case MC_TRIGNUM_PLAY: {
        if (g_current_player != mode) {
            status = Aud_Open_Close(g_current_player, MC_STOP, param);
            if (0 == status) {
                g_current_player = AUD_NULL;
            }
            TRACE("mode not match:%d/%d, MC_TRIGNUM_PLAY fail\n", g_current_player, mode);
        } else {
            status = Aud_Open_Close(mode, cmd, param);
            if (0 != status) {
                g_current_player = mode;
            }
        }
        break;
    }
    case MC_SET_TRIGNUM: {
        if (asio_src_get_trigger_status() == false) {
            asio_src_trigger_init(param->p.sync_ctrl.start_trig_num,param->p.sync_ctrl.trig_time_delta);
        } else {
            uint32_t input_fram_num = bt_audio_get_inbuffer_frame_num();
            asio_src_set_check_samplenum(true);
            switch (bt_audio_get_codec_type()) {
            case MEDIA_CODEC_TYPE_SBC:
                asio_src_set_input_sample_num(input_fram_num*128);
                break;
            case MEDIA_CODEC_TYPE_MPEG2_4_AAC:
                asio_src_set_input_sample_num(input_fram_num*1024);
                break;
            default: {
                uint32_t sco_input_frame_num = sco_get_input_frame_num()+param->p.sync_ctrl.sync_param.counterNum;
                uint32_t cacheing_0_num = sco_get_cacheing_0_num();
                //TRACE("APP:play sco\n");
                switch (bt_voice_get_codec_type()) {
                case MEDIA_SCO_CODEC_MSBC:
                    input_fram_num = (sco_input_frame_num + cacheing_0_num)*120;
                    asio_src_set_input_sample_num(input_fram_num);
                    break;
                case MEDIA_SCO_CODEC_CVSD:
                    input_fram_num = sco_input_frame_num*60 + cacheing_0_num*120;
                    asio_src_set_input_sample_num(input_fram_num);
                    break;
                default:
                    asio_src_set_input_sample_num(0);
                    break;
                }
            }
            break;
            }
        }
        break;
    }
    case MC_SYNC_PARAM:
        asio_src_handle_sync_param(&param->p.sync_ctrl.sync_param);
        break;
#endif
    default:
        break;
    }

    return 0;
}

#if (PLF_AUDIO == 1)
int AppSend_Mode_MediaCommand(AUD_REQ_MODE mode, MediaControlType cmd, MediaCommonStruct* param)
{
    APP_AUDIO_MSG_T msg;
    //no need to memset, msg will be initialized as follws
    //memset(&msg, 0, sizeof(APP_AUDIO_MSG_T));
    msg.mode = mode;
    msg.cmd = cmd;
    memcpy(&msg.param,param,sizeof(MediaCommonStruct));
    app_audio_send_msg(&msg, false);

    return 0;
}

void AppSend_StopInternalAudio(void)
{
    APP_AUDIO_MSG_T msg;

    TRACE("APP_MEDIA: media_StopInternalAudio.\n");
    memset(&msg, 0, sizeof(APP_AUDIO_MSG_T));
    msg.mode = AUD_INTERNAL;
    msg.cmd = MC_STOP;
    app_audio_send_msg(&msg, false);
}

int AppSend_PlayInternalAudio(PROMPT_ID_ENUM audio_id, uint8_t times)
{
    APP_AUDIO_MSG_T msg;

    TRACE("APP_MEDIA: media_PlayInternalAudio, audio_id=%d, times=%d, waitKey=%d\n",audio_id, times);
    memset(&msg, 0, sizeof(APP_AUDIO_MSG_T));
    msg.mode = AUD_INTERNAL;
    msg.cmd = MC_PLAY;
    msg.param.p.internal_aud.audio_id = audio_id;
    msg.param.p.internal_aud.times = times;
    app_audio_send_msg(&msg, false);

    return 0;
}
#else
int AppSend_Mode_MediaCommand(AUD_REQ_MODE mode, MediaControlType cmd, MediaCommonStruct* param)
{
    return 0;
}

void AppSend_StopInternalAudio(void)
{

}

int AppSend_PlayInternalAudio(PROMPT_ID_ENUM audio_id, uint8_t times)
{
    return 0;
}
#endif

#if (PLF_BT_STACK == 1) || (PLF_WIFI_STACK == 1)
#if (PLF_BT_AUDIO == 1) && (PLF_AUD_USED == 1)
int AppReceive_A2dpData(uint8_t *buf, uint32_t len, uint8_t sbc_frame_num, AUD_SAMPRATE_T samplerate)
{
    int ret = 0;

    bt_audio_buffer_write(buf, len, sbc_frame_num, samplerate);

    return ret;
}

int AppReceive_ScoData(uint8_t *buf, uint32_t len)
{
    int ret = 0;

    bt_voice_ds_buffer_write(buf, len);

    return ret;
}

int AppPrepareSend_ScoData(uint8_t *buf, uint32_t len)
{
    int ret = 0;

    ret = bt_voice_prepare_us_frame(buf, len);

    return ret;
}

#else
int AppReceive_A2dpData(uint8_t *buf, uint32_t len, uint8_t sbc_frame_num, AUD_SAMPRATE_T samplerate)
{
    return 0;
}

int AppReceive_ScoData(uint8_t *buf, uint32_t len)
{
    return 0;
}

int AppPrepareSend_ScoData(uint8_t *buf, uint32_t len)
{
    return 0;
}

#endif
#endif

int AppSend_MediaCommand(MediaControlType cmd, MediaCommonStruct* param)
{
    int ret = 0;

#if 0// APP_SUPPORT_FADE_INOUT==1
    //Wait fade out finished cbk, and send MC_STOP command
    if (MC_STOP == cmd  && no_fade != param) {
        AudSendFadeInOutReq(FALSE, param, NULL);
    }
#endif

    ret = AudSend_Common_Command(AUD_COMMON, cmd, param);

    return ret;
}


