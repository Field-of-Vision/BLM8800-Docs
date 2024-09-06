#include "tgt_cfg_bt.h"
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC ==1 ||APP_SUPPORT_A2DP_SOURCE == 1
#include "rtos.h"
#include "app_bt.h"
#include "app_a2dp.h"
#if APP_SUPPORT_A2DP_SOURCE == 1
#include "app_a2dp_source.h"
#endif
#if APP_SUPPORT_TWS == 1
#include "app_tws.h"
#endif
#include "aic_adp_api.h"


app_a2dp_state_t t_a2dp_state = A2DP_IDLE;



app_a2dp_state_t app_get_a2dp_state(void)
{
    return t_a2dp_state;
}

void app_set_a2dp_state(app_a2dp_state_t state)
{
    APP_BT_MGR *app_bt_manager_ptr = aic_adp_get_app_bt_mgr_ptr();

    if (t_a2dp_state == state){
        return;
    }

    if(state == A2DP_PLAY){
        app_bt_set_scan_mode(BT_NOSCAN);
    }
    else if(t_a2dp_state == A2DP_PLAY && state != A2DP_PLAY){
        if(app_bt_manager_ptr->connect_index == 1){
#if APP_SUPPORT_TWS == 1
            if(tws_app_get_role() == TWS_SLAVE){
                app_bt_set_scan_mode(BT_NOSCAN);
            }else
#endif
            {
                #if APP_SUPPORT_LINK_ONE_ONLY == 1
                app_bt_set_scan_mode(BT_NOSCAN);
                #else
                app_bt_set_scan_mode(BT_CONNECTABLE);
                #endif
            }
        }else if(app_bt_manager_ptr->connect_index >= 2){
            app_bt_set_scan_mode(BT_NOSCAN);
        }
    }
    TRACE("APP:set a2dp state = %d\n",state);
    t_a2dp_state = state;
}


AUD_SAMPRATE_T bt_parse_sbc_sample_rate(uint8_t samp_rate)
{
    AUD_SAMPRATE_T sample_rate = AUD_SAMPRATE_44100;
    samp_rate = samp_rate & A2DP_CSIE_SAMP_FREQ_MSK;

    switch (samp_rate)
    {
        case A2DP_CSIE_SAMP_FREQ_16:
            sample_rate = AUD_SAMPRATE_16000;
            break;
        case A2DP_CSIE_SAMP_FREQ_32:
            sample_rate = AUD_SAMPRATE_32000;
            break;
        case A2DP_CSIE_SAMP_FREQ_48:
            sample_rate = AUD_SAMPRATE_48000;
            break;
        case A2DP_CSIE_SAMP_FREQ_44:
            sample_rate = AUD_SAMPRATE_44100;
            break;
        default:
            ASSERT_ERR(0);
            break;
    }
    return sample_rate;
}

void app_a2dp_pause(void)
{
    TRACE("APP:app_a2dp_pause.\n");
    if(app_get_a2dp_state() == A2DP_PLAY){
        app_media_play(AUD_BT_A2DP ,MC_STOP,0,true);
        app_set_a2dp_state(A2DP_CONNECTED);
    }
}

void app_a2dp_play(BT_ADDR bdaddr)
{
    A2DP_AUDIO_CAP *audio_cap = NULL;
    MediaCommonStruct audio_param;
    memset((U8*)&audio_param, 0, sizeof(MediaCommonStruct));
    audio_cap = aic_adp_a2dp_get_audio_cap_by_addr(bdaddr);
    TRACE("APP:app_a2dp_play audio_cap = 0x%x\n",audio_cap);
    if(audio_cap){
        audio_param.p.aud_ctrl.a2dpcodec = audio_cap->codec_type;
        audio_param.p.aud_ctrl.samplerate = bt_parse_sbc_sample_rate(audio_cap->sample_rate_bit);
        //TODO add channel parsing
        audio_param.p.aud_ctrl.channel = audio_cap->channel;
        audio_param.p.aud_ctrl.numBlocks = audio_cap->numBlocks;
        audio_param.p.aud_ctrl.numSubBands = audio_cap->numSubBands;
        audio_param.p.aud_ctrl.dpll_mode = AUD_DPLL_NORMAL;
#if APP_SUPPORT_TWS == 1
        if(tws_app_get_role() >= TWS_NOROLE){
            app_media_play(AUD_BT_A2DP,MC_OPEN,&audio_param,true);
        }else{
            app_media_play(AUD_BT_A2DP ,MC_STOP,0,false);
            app_media_play(AUD_BT_A2DP ,MC_OPEN,&audio_param,true);
        }
#else
#if APP_SUPPORT_MULTIPLE_PHONE == 1
        if(app_get_a2dp_state() == A2DP_PLAY)
            app_media_play(AUD_BT_A2DP ,MC_STOP,0,true);
#endif
        app_media_play(AUD_BT_A2DP,MC_OPEN,&audio_param,true);
#endif
        app_set_a2dp_state(A2DP_PLAY);
    }
}


void app_handle_a2dp_connect_status(AIC_EVENT *event)
{
    AIC_ADP_A2DP_EVENT *aic_a2dp_msg = (AIC_ADP_A2DP_EVENT *)event->Param;
    app_connect_manager * app_bt_con = NULL;

    app_bt_con = app_bt_get_con_ptr_by_addr(&aic_a2dp_msg->bdaddr);
    if(!app_bt_con ){
        app_bt_con = app_bt_get_unused_con_ptr();
        if(!app_bt_con){
            TRACE("APP:app a2dp get con ptr error\n");
            ASSERT_ERR(0);
        }
        memcpy(app_bt_con->remotedev_addr.addr,aic_a2dp_msg->bdaddr.addr, BD_ADDR_SIZE);
    }

    if(app_bt_con->reconnect.connect_timer_handle){
#if PLF_AON_SUPPORT
        co_timer_stop(app_bt_con->reconnect.connect_timer_handle);
#else
        rtos_timer_stop(app_bt_con->reconnect.connect_timer_handle,0);
#endif
        app_bt_con->reconnect.connect_timer_cb = NULL;
    }

    switch(event->EventId){
        case AIC_ADP_A2DP_STREAM_OPEN:
            {
                btdev_info* dev_info = aic_adp_get_devinfo_by_addr(&aic_a2dp_msg->bdaddr);
                if(dev_info){
                    A2DP_AUDIO_CAP *audio_cap = (A2DP_AUDIO_CAP *)aic_a2dp_msg->p.signalingP.audioCodecP;
                    dev_info->a2dp_state = 1;
                    dev_info->a2dp_codectype = audio_cap->codec_type;
                    dev_info->a2dp_role = aic_a2dp_msg->role;
                }
                app_bt_con->profile.a2dp_connect = CONNECTED;
                memcpy(app_bt_con->remotedev_addr.addr, aic_a2dp_msg->bdaddr.addr, BD_ADDR_SIZE);
                app_bt_con->reconnect.connect_retry_cnt = 0;

                switch(app_bt_con->reconnect.reconnect_mode){
                    case RECONNECT_POWERON:
                        if(app_bt_con->profile.hfp_connect != CONNECTED){
                            app_bt_connect_hfp(&app_bt_con->remotedev_addr);
                        }
                        break;
                    case RECONNECT_AFTER_DISC:
                        if(app_bt_con->profile.hfp_connect != CONNECTED){
                            app_bt_connect_hfp(&app_bt_con->remotedev_addr);
                        }
                        break;
                    default:
                        app_bt_con->reconnect.reconnect_mode = RECONNECT_IDLE;
                        break;
                }
            }
            break;
        case AIC_ADP_A2DP_STREAM_CLOSED:
            {
                app_bt_con->profile.a2dp_connect = DISCONNECTED;
                switch(app_bt_con->reconnect.reconnect_mode){
                    case RECONNECT_POWERON:
                        app_bt_con->reconnect.reconnect_mode = RECONNECT_IDLE;
                        break;
                    case RECONNECT_AFTER_DISC:
                        if(app_bt_con->reconnect.connect_retry_cnt < APP_RECONNECT_NUM){
#if PLF_AON_SUPPORT
                            app_bt_start_reconnect(&app_bt_con->reconnect.connect_timer_handle,app_bt_con->reconnect.cb_param
                                                  ,APP_RECONNECT_INCREASE_TIME*app_bt_con->reconnect.connect_retry_cnt + APP_RECONNECT_TIME);
#else
                            app_bt_start_reconnect(app_bt_con->reconnect.connect_timer_handle
                                                  ,APP_RECONNECT_INCREASE_TIME*app_bt_con->reconnect.connect_retry_cnt + APP_RECONNECT_TIME);
#endif
                            app_bt_con->reconnect.connect_retry_cnt++;
                        }else{
                            app_bt_con->reconnect.reconnect_mode = RECONNECT_IDLE;
                            #if APP_SUPPORT_TWS == 1
                            app_tws_power_down();
                            #endif
                        }
                        break;
                    default:
                        if(aic_a2dp_msg->p.disc_reason == BT_CONNECTION_TIMEOUT){
                            app_bt_con->reconnect.reconnect_mode = RECONNECT_AFTER_DISC;
                            TRACE("APP:a2dp start reconnect\n");
#if PLF_AON_SUPPORT
                            app_bt_start_reconnect(&app_bt_con->reconnect.connect_timer_handle, app_bt_con->reconnect.cb_param, APP_RECONNECT_TIME);
#else
                            app_bt_start_reconnect(app_bt_con->reconnect.connect_timer_handle ,APP_RECONNECT_TIME);
#endif
                        }else{
                            app_bt_con->profile.a2dp_connect = CONNECT_IDLE;
                        }
                        break;
                }
            }
            break;
        default:
            break;
    }
    app_bt_report_connect_internal_audio(app_bt_con);
}

void app_a2dp_state_machine(AIC_EVENT *event)
{
    //AIC_ADP_A2DP_EVENT *aic_a2dp_msg = (AIC_ADP_A2DP_EVENT *)event->Param;

    switch(event->EventId){
        case AIC_ADP_A2DP_STREAM_OPEN:
            if(app_get_a2dp_state() == A2DP_IDLE){
                app_set_a2dp_state(A2DP_CONNECTED);
            }
            break;
        case AIC_ADP_A2DP_STREAM_CLOSED:
            if(app_get_a2dp_state() != A2DP_PLAY)
                app_set_a2dp_state(A2DP_IDLE);
            break;
        default:
            break;
    }
}

void app_a2dp_msg_handle(AIC_EVENT *event)
{
    AIC_ADP_A2DP_EVENT *aic_a2dp_msg = (AIC_ADP_A2DP_EVENT *)event->Param;
    app_a2dp_state_machine(event);

    switch(event->EventId) {
        case AIC_ADP_A2DP_STREAM_OPEN:
            {
                if(aic_a2dp_msg->role == BT_A2DP_SOURCE){
                    #if APP_SUPPORT_A2DP_SOURCE == 1
                    #endif
                }else{
                    #if APP_SUPPORT_AVRCP == 1
                    aic_adp_avrcp_connect(aic_a2dp_msg->bdaddr);
                    #endif

                }
                app_handle_a2dp_connect_status(event);
            }
            break;
        case AIC_ADP_A2DP_STREAM_STARTED:
            {
                A2DP_AUDIO_CAP *audio_cap = (A2DP_AUDIO_CAP *)aic_a2dp_msg->p.signalingP.audioCodecP;
                TRACE("APP:a2dp_stream_started role = %d, codec_type = %d , sample_rate_bit = %d\n",aic_a2dp_msg->role,audio_cap->codec_type, audio_cap->sample_rate_bit);
                if(aic_a2dp_msg->role == BT_A2DP_SOURCE){
#if APP_SUPPORT_A2DP_SOURCE == 1
                    app_a2dp_source_sbc_data_send_timer_begin();
#endif
                }else{
                    app_a2dp_play(aic_a2dp_msg->bdaddr);
                }
            }
            break;
        case AIC_ADP_A2DP_STREAM_SUSPENDED:
            {
                TRACE("APP:a2dp_stream_suspended role = %d\n",aic_a2dp_msg->role);
                if(aic_a2dp_msg->role == BT_A2DP_SINK){
                    app_a2dp_pause();
                }
            }
            break;
        case AIC_ADP_A2DP_STREAM_CLOSED:
            {
                TRACE("APP:a2dp_stream_closed role = %d\n",aic_a2dp_msg->role);
                if(aic_a2dp_msg->role == BT_A2DP_SINK){
                    app_a2dp_pause();
                }
                app_handle_a2dp_connect_status(event);
            }
            break;

        case AIC_ADP_A2DP_STREAM_PACKET_SENT:
            TRACE("APP:a2dp source data send succ!\n");
            if(aic_a2dp_msg->role == BT_A2DP_SOURCE){
#if APP_SUPPORT_A2DP_SOURCE == 1
                app_a2dp_source_sbc_data_send_timer_begin();
#endif
            }
            break;
        case AIC_ADP_A2DP_STREAM_DATA_IND:
            {
                A2DP_AUDIO_CAP *audio_cap = (A2DP_AUDIO_CAP *)aic_a2dp_msg->p.mediaP.audioCodecP;
                A2DP_AUDIO_DATA *audio_data = (A2DP_AUDIO_DATA *)aic_a2dp_msg->p.mediaP.audioDataP;

                if(app_get_a2dp_state() == A2DP_PLAY){
                    AppReceive_A2dpData(((unsigned char *)audio_data->data)+ audio_data->headerlen ,
                                                          audio_data->datalen - audio_data->headerlen,
                                                          audio_cap->sbc_frame_number ,
                                                          bt_parse_sbc_sample_rate(audio_cap->sample_rate_bit));
                }else{
                    TRACE("APP:free a2dp stream data\n");
                }
            }
            break;
        default:
            break;
    }

}

#endif


