#include "plf.h"
#include "rtos.h"
#include <string.h>
#include <stdint.h>
#include "app_media_mgr.h"
#if PLF_BT_STACK == 1
#include "tgt_cfg_bt.h"
#if PLF_BLE_ONLY == 0
#include "app_bt_queue.h"
#include "app_bt.h"
#include "app_a2dp.h"
#include "app_hfp.h"
#include "bt_task_msg.h"
#include "bt_task.h"
#endif
#endif
static rtos_queue app_play_media_queue = NULL;
static AUD_REQ_MODE last_mode = AUD_NULL;
static MediaControlType last_cmd = MC_NULL;
static AUD_REQ_MODE playing_mode = AUD_NULL;
static MediaControlType playing_cmd = MC_NULL;

#if (PLF_AUD_USED == 1)
bool app_media_mgr_send_command(AUD_REQ_MODE mode,MediaControlType cmd, MediaCommonStruct* param)
{
    return AppSend_Mode_MediaCommand(mode,cmd,param);
}

bool app_media_mgr_set_command(MediaControlType cmd, MediaCommonStruct* param)
{
    return AppSend_MediaCommand(cmd,param);
}

#else
bool app_media_mgr_send_command(AUD_REQ_MODE mode,MediaControlType cmd, MediaCommonStruct* param)
{
    bool ret = true;
    return ret;
}

bool app_media_mgr_set_command(MediaControlType cmd, MediaCommonStruct* param)
{
    bool ret = true;
    return ret;
}

#endif
int app_media_queue_cnt(void)
{
    return rtos_queue_cnt(app_play_media_queue);
}

void app_media_enqueue(APP_AUDIO_MSG_T* msg, bool isr)
{
    rtos_queue_write(app_play_media_queue, msg, 0, isr);
}

int app_media_queue_peek(APP_AUDIO_MSG_T* msg)
{
    int res = 0;
    res = rtos_queue_peek(app_play_media_queue, msg, 0, false);
    return res;
}

int app_media_queue_get(APP_AUDIO_MSG_T* msg)
{
    int res = 0;
    res = rtos_queue_read(app_play_media_queue, msg, 0, false);
    return res;
}

void app_media_queue_clean(void)
{
    rtos_queue_reset(app_play_media_queue);
}

void app_media_set_playing_mode(AUD_REQ_MODE mode,MediaControlType cmd)
{
    if(cmd == MC_STOP){
        if(playing_mode == mode){
            playing_mode = AUD_NULL;
            playing_cmd = MC_NULL;
            TRACE("set_playing mode=0x%x,cmd=0x%x\n",mode,cmd);
        }
        return;
    }
    playing_mode = mode;
    playing_cmd = cmd;
    TRACE("set_playing mode=0x%x,cmd=0x%x\n",mode,cmd);
}

AUD_REQ_MODE app_media_get_playing_mode(void)
{
    return playing_mode;
}

void app_media_set_last_param(AUD_REQ_MODE mode,MediaControlType cmd)
{
    last_mode = mode;
    last_cmd = cmd;
    TRACE("set_last_param mode=0x%x,cmd=0x%x\n",mode,cmd);
}

MODE_PRIORITY app_media_get_mode_priorty(AUD_REQ_MODE mode)
{
    MODE_PRIORITY ret = MODE_PRIORITY_MIN;

    switch(mode){
        case AUD_INTERNAL:
            ret = MODE_PRIORITY_INTERNAL;
            break;
        case AUD_BT_A2DP:
            ret = MODE_PRIORITY_BT_A2DP;
            break;
        case AUD_BT_SCO:
            ret = MODE_PRIORITY_BT_SCO;
            break;
        case AUD_WIFI:
            ret = MODE_PRIORITY_WIFI;
            break;
        default:
            break;
    }
    return ret;
}

int app_media_check_next_playing_mode_priorty(AUD_REQ_MODE mode,MediaControlType cmd)
{
    int ret = 0;
    MODE_PRIORITY current = MODE_PRIORITY_MIN;
    MODE_PRIORITY next = MODE_PRIORITY_MIN;
    APP_AUDIO_MSG_T msg;

    if((cmd != MC_PLAY && cmd != MC_OPEN && cmd != MC_STOP && cmd != MC_REPLAY) || playing_mode == AUD_NULL){
        return ret;
    }

    current = app_media_get_mode_priorty(playing_mode);
    next = app_media_get_mode_priorty(mode);
    if(current < next){
        memset(&msg, 0, sizeof(APP_AUDIO_MSG_T));
        TRACE("current %d< next %d\n",current,next);
        msg.mode = playing_mode;
        msg.cmd = MC_REPLAY;
        app_media_enqueue(&msg, false);
        ret = 0;
    }else if(current > next){
        TRACE("current %d> next %d\n",current,next);
        ret = 1;
        if(cmd == MC_STOP){
            int res = 0;
            res = app_media_queue_get(&msg);
            TRACE("drop stop %d\n",res);
        }
    }else{
        TRACE("current %d== next %d\n",current,next);
        ret = 0;
    }
    return ret;
}


void app_media_play_in_order(void)
{
    int res = 0;
    APP_AUDIO_MSG_T msg;

    if(last_mode == AUD_NULL && last_cmd == MC_NULL){
        res = app_media_queue_peek(&msg);
        if(res == 0){
            if(app_media_check_next_playing_mode_priorty(msg.mode,msg.cmd)){
                return;
            }
            res = app_media_queue_get(&msg);
            switch(msg.mode){
#if PLF_BT_STACK == 1
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC ==1 ||APP_SUPPORT_A2DP_SOURCE == 1
                case AUD_BT_A2DP:
                    {
                        switch(msg.cmd){
                            case MC_OPEN:
                            case MC_PLAY:
                            case MC_STOP:
                                app_media_set_playing_mode(msg.mode,msg.cmd);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
#endif
#if APP_SUPPORT_HFP == 1
                case AUD_BT_SCO:
                    {
                        switch(msg.cmd){
                            case MC_OPEN:
                                app_media_set_playing_mode(msg.mode,msg.cmd);
                                break;
                            case MC_PLAY:
                                {
                                    MediaCommonStruct tmp;
                                    tmp.p.sync_ctrl.start_trig_num = (2600000);// 2600000 : 100ms //min trigger num ;//min trigger num
                                    app_media_mgr_set_command(MC_SET_TRIGNUM,&tmp);
                                    app_media_set_playing_mode(msg.mode,msg.cmd);
                                }
                                break;
                            case MC_STOP:
                                app_media_set_playing_mode(msg.mode,msg.cmd);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
#endif
#if (PLF_BT_PROMPT == 1)
                case AUD_INTERNAL:
                    {
                        switch(msg.cmd){
                            case MC_PLAY:
                                {
                                    app_media_set_last_param(msg.mode,msg.cmd);
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    break;
#endif
#endif
#if PLF_WIFI_STACK == 1
                case AUD_WIFI:
                    {
                        switch(msg.cmd){
                            case MC_OPEN:
                            case MC_PLAY:
                            case MC_STOP:
                                app_media_set_playing_mode(msg.mode,msg.cmd);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
#endif
                default:
                    break;
            }
            app_media_mgr_send_command(msg.mode,msg.cmd,&msg.param);
        }
    }

}

#if PLF_AUD_USED
void app_media_play(AUD_REQ_MODE mode,MediaControlType cmd, MediaCommonStruct* param, bool in_order)
{
    APP_AUDIO_MSG_T msg;
    int cnt = 0;
    int res = 0;
    memset(&msg, 0, sizeof(APP_AUDIO_MSG_T));
    msg.mode = mode;
    msg.cmd = cmd;
    TRACE("app_media_play mode=0x%x, cmd=0x%x\n",mode,cmd);
    if(param)
        memcpy(&msg.param,param,sizeof(MediaCommonStruct));
    if(in_order == false){
        app_media_queue_clean();
        app_media_set_last_param(AUD_NULL,MC_NULL);
    }
    cnt = app_media_queue_cnt();
    app_media_enqueue(&msg, false);
    if(cnt && (cmd == MC_STOP || cmd == MC_PAUSE || cmd == MC_CLOSE \
            || cmd == MC_PRELOAD_PLAY || cmd == MC_TRIGNUM_PLAY)){
        for(uint8_t i = 0 ; i < cnt ; i++){
            res = app_media_queue_get(&msg);
            if(!res){
                app_media_enqueue(&msg, false);
            }
        }
    }
    app_audio_task_notify();
}
#else
void app_media_play(AUD_REQ_MODE mode,MediaControlType cmd, MediaCommonStruct* param, bool in_order)
{

}
#endif

void app_media_play_internalaudio(PROMPT_ID_ENUM audio_id)
{
#if (PLF_BT_PROMPT == 1)
    MediaCommonStruct param;
    TRACE("internalaudio id = %d\n",audio_id);
    param.p.internal_aud.audio_id = audio_id;
    app_media_play(AUD_INTERNAL,MC_PLAY,&param,true);
#endif
}

void app_media_mgr_init(void)
{
    int res = 0;

    if (app_play_media_queue == NULL) {
        res = rtos_queue_create(sizeof(APP_AUDIO_MSG_T), 10, &app_play_media_queue);
        if (0 != res) {
            ASSERT_ERR(0);
        }
    } else {
        ASSERT_ERR(0);
    }
    app_audio_handler_register(app_media_play_in_order);
}

