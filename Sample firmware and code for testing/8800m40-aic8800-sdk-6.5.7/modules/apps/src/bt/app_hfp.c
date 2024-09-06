#include "tgt_cfg_bt.h"
#if APP_SUPPORT_HFP == 1
#include "aic_adp_api.h"
#include "rtos.h"
#include "app_bt.h"
#include "app_hfp.h"
#include "app_a2dp.h"
#if APP_SUPPORT_TWS == 1
#include "app_tws.h"
#endif
#include "bt_task_msg.h"
#include "time_api.h"

#define CFG_CUR_TIME_INFORMER   0
#if CFG_CUR_TIME_INFORMER
#include "uart1_api.h"
#endif

/* hfp */
app_hfp_state_t s_hfp_state = APP_IDLE;
uint16_t  s_hfp_scocodec = MEDIA_SCO_CODEC_NONE;
TimerHandle_t app_hfp_cclk_check_timer_handle = NULL;
int at_cclk_acked = 0;

#if SCO_LOOPBACK_TEST == 1
ScoSendData_t tmpdata;
#else
HF_SENDBUFF_T hf_sendbuff;
#endif

void app_hfp_cclk_check_timer( TimerHandle_t xTimer )
{
    if (!at_cclk_acked) {
        TRACE("APP:cclk_check is error\n");
    } else {
        uint32_t tv_sec, tv_usec;
        struct tm tim_st;
        char buffer[48] = {0,};
        aic_time_get(SINCE_EPOCH, &tv_sec, &tv_usec);
        gmtime_offset_r((const time_t *)&tv_sec, &tim_st, 8);
        dbg_snprintf(buffer, sizeof(buffer), "BJ TIME: %d-%02d-%02d %02d:%02d:%02d\r\n",
            tim_st.tm_year + YEAR0,tim_st.tm_mon + 1,tim_st.tm_mday,tim_st.tm_hour,tim_st.tm_min,tim_st.tm_sec);
        uart_puts(buffer);
        #if CFG_CUR_TIME_INFORMER
        uart1_puts(buffer);
        #endif
    }
    #if CFG_CUR_TIME_INFORMER
    rtos_timer_start(app_hfp_cclk_check_timer_handle, 0, false);
    #endif
}

int app_hfp_send_at_cclk(BT_ADDR bdaddr)
{
    aic_adp_hfp_send_at_cclk(bdaddr);
    if(app_hfp_cclk_check_timer_handle == NULL)
        app_hfp_cclk_check_timer_handle = rtos_timer_create("cclk ckeck timer",1000,pdFALSE,\
                                                     NULL,app_hfp_cclk_check_timer);
    rtos_timer_start(app_hfp_cclk_check_timer_handle, 0, false);
    return 0;
}

int app_hfp_siri_report(BT_ADDR bdaddr)
{
    aic_adp_hfp_send_siri_report(bdaddr);
    return 0;
}

int app_hfp_siri_voiceRecognition(BT_ADDR bdaddr)
{
    aic_adp_hfp_send_voice_recognition(bdaddr, 1);
    return 0;
}

app_hfp_state_t app_get_hfp_state(void)
{
    return s_hfp_state;
}


void app_set_hfp_state(app_hfp_state_t state)
{
    if((state == APP_CALL_ACTIVE && s_hfp_state == APP_PLAY_SCO)
     ||(state == APP_CALL_OUTGOING && s_hfp_state == APP_PLAY_SCO)){
        state = APP_PLAY_SCO;
    }
    TRACE("APP:set hfp state = %d\n",state);
    s_hfp_state = state;
}

uint16_t app_get_hfp_scocodec(void)
{
    return s_hfp_scocodec;
}


void app_set_hfp_scocodec(uint16_t scocodec)
{
    TRACE("APP:set hfp scocodec = %d\n",scocodec);
    s_hfp_scocodec = scocodec;
}

void app_set_hfp_volume(BT_ADDR *bdaddr,S8 volume)
{
    APP_DEVLIST *tmp = NULL;
    tmp = app_bt_get_mgr_devinfo(*bdaddr);

    btdev_info* dev_info = aic_adp_get_devinfo_by_addr(bdaddr);
    if(tmp && dev_info){
        tmp->peer_volume_hfp = dev_info->peer_hfp_vol = volume;
    }
}

S8 app_get_hfp_volume(BT_ADDR *bdaddr)
{
    U8 volume = 15;
    btdev_info* dev_info = aic_adp_get_devinfo_by_addr(bdaddr);
    if(dev_info){
        if(dev_info->peer_hfp_vol == 0){
            volume = 15;
        }else{
            if(dev_info->peer_hfp_vol > 0 && dev_info->peer_hfp_vol <= 15){
                volume = dev_info->peer_hfp_vol;
            }else{
                volume = dev_info->peer_hfp_vol = 15;
            }
        }
    }
    TRACE("APP:app_get_hfp_volume %d\n",volume);
    return volume;
}

void app_hfp_stop(void)
{
    TRACE("APP:app_hfp_stop.\n");
    if(app_get_hfp_state()== APP_PLAY_SCO)
        app_media_play(AUD_BT_SCO ,MC_STOP,0,true);
    app_set_hfp_state(APP_CONNECTED);
}

void app_hfp_play(BT_ADDR bdaddr)
{
    uint16_t scohandle = 0;
    uint16_t negotiated_codec = 0;
    MediaCommonStruct tmp;
    TRACE("APP:app_hfp_play.\n");

    memset((U8*)&tmp, 0, sizeof(MediaCommonStruct));
    scohandle = aic_adp_hfp_get_scohandle_by_addr(bdaddr);
    if(scohandle){
        app_set_hfp_state(APP_PLAY_SCO);
        negotiated_codec = aic_adp_hfp_get_negotiated_codec_by_addr(bdaddr);
        switch (negotiated_codec)
        {
            case MEDIA_SCO_CODEC_CVSD:
                tmp.p.voc_ctrl.scocodec = MEDIA_SCO_CODEC_CVSD;
                break;
            case MEDIA_SCO_CODEC_MSBC:
                tmp.p.voc_ctrl.scocodec = MEDIA_SCO_CODEC_MSBC;
                break;
            default:
                tmp.p.voc_ctrl.scocodec = MEDIA_SCO_CODEC_CVSD;
                break;
        }
#if APP_SUPPORT_TWS == 1
        if(tws_app_get_role() == TWS_MASTER)
            app_media_play(AUD_BT_SCO ,MC_OPEN,&tmp,false);
        else{
            app_media_play(AUD_BT_SCO ,MC_PLAY,&tmp,true);
        }
#else
        {
            app_media_play(AUD_BT_SCO ,MC_PLAY,&tmp,true);
        }
#endif
    }
}

void app_handle_hfp_connect_status(AIC_EVENT *event)
{
    AIC_ADP_HFP_EVENT *aic_hfp_msg = (AIC_ADP_HFP_EVENT *)event->Param;
    app_connect_manager * app_bt_con = NULL;

    app_bt_con = app_bt_get_con_ptr_by_addr(&aic_hfp_msg->bdaddr);
    if(!app_bt_con ){
        app_bt_con = app_bt_get_unused_con_ptr();
        if(!app_bt_con){
            TRACE("APP:app hfp get con ptr error\n");
            ASSERT_ERR(0);
        }
        memcpy(app_bt_con->remotedev_addr.addr,aic_hfp_msg->bdaddr.addr, BD_ADDR_SIZE);
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
        case AIC_ADP_HFP_CONNECTED:
            {
                btdev_info* dev_info = aic_adp_get_devinfo_by_addr(&aic_hfp_msg->bdaddr);

                if(aic_hfp_msg->p.conP.reason){
                    return;
                }
                if(dev_info){
                    dev_info->hf_state = 1;
                }
                app_bt_con->profile.hfp_connect = CONNECTED;
                memcpy(app_bt_con->remotedev_addr.addr, aic_hfp_msg->bdaddr.addr, BD_ADDR_SIZE);
                app_bt_con->reconnect.connect_retry_cnt = 0;

                switch(app_bt_con->reconnect.reconnect_mode){
                    case RECONNECT_POWERON:
                        if(app_bt_con->profile.a2dp_connect != CONNECTED){
                            app_bt_connect_a2dp(&app_bt_con->remotedev_addr);
                        }
                        break;
                    case RECONNECT_AFTER_DISC:
                        if(app_bt_con->profile.a2dp_connect != CONNECTED){
                            app_bt_connect_a2dp(&app_bt_con->remotedev_addr);
                        }
                        break;
                    default:
                        app_bt_con->reconnect.reconnect_mode = RECONNECT_IDLE;
                        break;
                }
            }
            break;
        case AIC_ADP_HFP_DISCONNECTED:
            {
                app_bt_con->profile.hfp_connect = DISCONNECTED;

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
#if APP_SUPPORT_HFG == 1
                        if(aic_hfp_msg->p.discP.reason == BT_CONNECTION_TIMEOUT){
                            app_bt_con->profile.hfp_connect = CONNECT_IDLE;
                            break;
                        }
#endif
                        if(aic_hfp_msg->p.discP.reason == BT_CONNECTION_TIMEOUT){
                            app_bt_con->reconnect.reconnect_mode = RECONNECT_AFTER_DISC;
                            TRACE("APP:hfp start reconnect\n");
#if PLF_AON_SUPPORT
                            app_bt_start_reconnect(&app_bt_con->reconnect.connect_timer_handle,app_bt_con->reconnect.cb_param,APP_RECONNECT_TIME);
#else
                            app_bt_start_reconnect(app_bt_con->reconnect.connect_timer_handle ,APP_RECONNECT_TIME);
#endif
                        }else{
                            app_bt_con->profile.hfp_connect = CONNECT_IDLE;
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



void app_hfp_state_machine(AIC_EVENT *event)
{
    AIC_ADP_HFP_EVENT *aic_hfp_msg = (AIC_ADP_HFP_EVENT *)event->Param;
    switch(event->EventId)
    {
        case AIC_ADP_HFP_CONNECTED:
            if(app_get_hfp_state() == APP_IDLE)
            {
                app_set_hfp_state(APP_CONNECTED);
            }
            break;
        case AIC_ADP_HFP_DISCONNECTED:
            {
                app_set_hfp_state(APP_IDLE);
                app_set_hfp_scocodec(MEDIA_SCO_CODEC_NONE);
            }
            break;
        case AIC_ADP_HFP_AUDIO_CONNECTED:
            {
                uint16_t scohandle = 0;
                uint16_t negotiated_codec = 0;

                scohandle = aic_adp_hfp_get_scohandle_by_addr(aic_hfp_msg->bdaddr);
                if(scohandle){
                    negotiated_codec = aic_adp_hfp_get_negotiated_codec_by_addr(aic_hfp_msg->bdaddr);
                    switch (negotiated_codec)
                    {
                        case MEDIA_SCO_CODEC_CVSD:
                            app_set_hfp_scocodec(MEDIA_SCO_CODEC_CVSD);
                            break;
                        case MEDIA_SCO_CODEC_MSBC:
                            app_set_hfp_scocodec(MEDIA_SCO_CODEC_MSBC);
                            break;
                        default:
                            app_set_hfp_scocodec(MEDIA_SCO_CODEC_CVSD);
                            break;
                    }
                }
            }
            break;
        case AIC_ADP_HFP_AUDIO_DISCONNECTED:
            {
                app_set_hfp_scocodec(MEDIA_SCO_CODEC_NONE);
            }
            break;
        case AIC_ADP_HFP_CALL_STATUS_IND:
            {
                bt_hfp_adp_call_status call_state = aic_hfp_msg->p.callP.callS;
                if(call_state == BT_CALL_STATUS_ACTIVE){
                    app_set_hfp_state(APP_CALL_ACTIVE);
                }else{
                    //app_set_hfp_state(APP_CONNECTED);
                }
            }
            break;
        case AIC_ADP_HFP_CALLSETUP_STATUS_IND:
            {
                bt_hfp_adp_call_status call_state = aic_hfp_msg->p.callsetupP.callS;
                switch(call_state){
                    case BT_CALL_STATUS_INCOMING:
                        app_set_hfp_state(APP_CALL_INCOMING);
                        break;
                    case BT_CALL_STATUS_OUTGOING:
                    case BT_CALL_STATUS_ALERT:
                        app_set_hfp_state(APP_CALL_OUTGOING);
                        break;
                    case BT_CALL_STATUS_NONE:
                        break;
                    default:
                        break;
                }
            }
            break;
        case AIC_ADP_HFP_CALLHOLD_STATUS_IND:
            {
                bt_hfp_adp_callhold_status hfp_call_hold = aic_hfp_msg->p.callholdP.callholdS;
                TRACE("APP:hfp_call_hold = %d\n",hfp_call_hold);
            }
            break;

        default:
            break;
    }
}

BOOL app_hfp_key_handle(uint32_t key)
{
    BOOL ret = FALSE;
    APP_DEVLIST * hfp_devinfo = NULL;

    hfp_devinfo = aic_adp_get_hfp_current_devinfo();
    if(hfp_devinfo == NULL){
        return ret;
    }

    switch(key){
        case APP_KEY_PLAY|APP_KEY_PRESS:
            {
                TRACE("APP:hfp state %d ,call status %d\n",hfp_devinfo->hfp_state,hfp_devinfo->hfp_call_status);
                if(hfp_devinfo->hfp_state == HFP_ADP_STATE_CONNECTED){
                    if(hfp_devinfo->hfp_call_status == BT_CALL_STATUS_ACTIVE ||
                       hfp_devinfo->hfp_call_status == BT_CALL_STATUS_OUTGOING ||
                       hfp_devinfo->hfp_call_status == BT_CALL_STATUS_ALERT ||
                       aic_adp_hfp_get_voicerecognition_state(hfp_devinfo->bdaddr)){
                            aic_adp_hfp_call_release(hfp_devinfo->bdaddr);
                            ret = TRUE;
                    }else if(hfp_devinfo->hfp_call_status == BT_CALL_STATUS_INCOMING){
                            aic_adp_hfp_call_answer(hfp_devinfo->bdaddr);
                            ret = TRUE;
                    }
                }
            }
            break;
        case APP_KEY_VOLADD|APP_KEY_PRESS:
        case APP_KEY_VOLADD|APP_KEY_HOLD:
        case APP_KEY_VOLSUB|APP_KEY_PRESS:
        case APP_KEY_VOLSUB|APP_KEY_HOLD:
            TRACE("APP:hfp state %d ,call status %d\n",hfp_devinfo->hfp_state,hfp_devinfo->hfp_call_status);
            if(hfp_devinfo->hfp_call_status != BT_CALL_STATUS_NONE){
                aic_adp_hfp_send_volume(hfp_devinfo->bdaddr ,app_get_hfp_volume(&hfp_devinfo->bdaddr));
                ret = TRUE;
            }
            break;
        case APP_KEY_PLAY|APP_KEY_DOUBLE_CLICK:
            if(hfp_devinfo->hfp_call_status == BT_CALL_STATUS_INCOMING)
            {
                aic_adp_hfp_call_release(hfp_devinfo->bdaddr);
                ret = TRUE;
            }
            else if(hfp_devinfo->hfp_call_status == BT_CALL_STATUS_NONE)
            {
                aic_adp_hfp_call_redial(hfp_devinfo->bdaddr);
                ret = TRUE;
            }
            break;
        case APP_KEY_PLAY|APP_KEY_HOLD:
            if(hfp_devinfo->hfp_call_status == BT_CALL_STATUS_INCOMING)
            {
                aic_adp_hfp_call_release(hfp_devinfo->bdaddr);
                ret = TRUE;
            }
            else if(hfp_devinfo->hfp_call_status == BT_CALL_STATUS_NONE)
            {
                app_hfp_siri_voiceRecognition(hfp_devinfo->bdaddr);
                ret = TRUE;
            }
            break;
        default:
            break;
    }
    return ret;
}

void app_hfp_msg_handle(AIC_EVENT *event)
{
    AIC_ADP_HFP_EVENT *aic_hfp_msg = (AIC_ADP_HFP_EVENT *)event->Param;
    app_hfp_state_machine(event);

    switch(event->EventId)
    {
        case AIC_ADP_HFP_CONNECTED:
            TRACE("APP:app_hfp_connect , result = %d\n",aic_hfp_msg->p.conP.reason);

            if(aic_hfp_msg->p.conP.reason == BT_NO_ERROR){
                if(aic_hfp_msg->role == HANDSFREE){
#if APP_SUPPORT_NREC_OFF == 1
                    aic_adp_hfp_disable_NREC(aic_hfp_msg->bdaddr);
#endif
                    aic_adp_hfp_set_battery_level(7);
                    aic_adp_hfp_send_volume(aic_hfp_msg->bdaddr ,app_get_hfp_volume(&aic_hfp_msg->bdaddr));
                    app_hfp_siri_report(aic_hfp_msg->bdaddr);
                    app_hfp_send_at_cclk(aic_hfp_msg->bdaddr);
                }else{
#if APP_SUPPORT_HFG && PLF_USB_BT
                    usb_bt_msg_queue_write(USB_BT_CONNECTED,0,0);
#endif
                }
            }
            app_bt_handler_register(HANDLER_REG_3,aic_adp_hfp_battery_report_proc);
            app_handle_hfp_connect_status(event);
            break;
        case AIC_ADP_HFP_DISCONNECTED:
            {
                uint8_t discReason = (uint8_t)aic_hfp_msg->p.discP.reason;
                TRACE("APP:app_hfp_disconnect , reason = %d\n",discReason);

                if(aic_hfp_msg->role == HANDSFREE){
                    app_hfp_stop();
                }else{
#if APP_SUPPORT_HFG && PLF_USB_BT
                    usb_bt_msg_queue_write(USB_BT_DISCONNECTED,0,0);
#endif
                }
                app_bt_handler_register(HANDLER_REG_3,NULL);
                app_handle_hfp_connect_status(event);
            }
            break;
        case AIC_ADP_HFP_AUDIO_CONNECTED:
            TRACE("APP:hfp_sco_connect\n");
#if defined(HFP_1_6_ENABLE)
            TRACE("APP:hfp_codec_type = %d\n",aic_hfp_msg->p.scoP.negotiated_codec);
#endif
#if PLF_USB_BT == 0
            if(aic_hfp_msg->role == HANDSFREE){
                aic_adp_hfp_send_volume(aic_hfp_msg->bdaddr ,app_get_hfp_volume(&aic_hfp_msg->bdaddr));
            }
            if(aic_hfp_msg->p.scoP.reason == BT_NO_ERROR)
                app_hfp_play(aic_hfp_msg->bdaddr);
#endif
            break;
        case AIC_ADP_HFP_AUDIO_DISCONNECTED:
#if PLF_USB_BT == 0
            app_hfp_stop();
#endif
            break;
        case AIC_ADP_HFP_AUDIO_DATA_SENT:

            break;
        case AIC_ADP_HFP_AUDIO_DATA_IND:
            {
                AIC_ADP_HFP_AUDIO_DATA *audiodata = (AIC_ADP_HFP_AUDIO_DATA *)aic_hfp_msg->p.dataindP.buff;
                AIC_ADP_HFP_AUDIO_DATA sendaudiodata;

                //TRACE("APP:sco data ind data = 0x%x ,len = %d\n",audiodata->data,audiodata->len);
#if PLF_USB_BT
                usb_bt_dongle_data_recv(audiodata->data ,audiodata->len);
                uint32_t idx = hf_sendbuff.idx % HF_SENDBUFF_MEMPOOL_NUM;
                usb_bt_dongle_data_send(&hf_sendbuff.mempool[idx].buffer[0], audiodata->len);
                hf_sendbuff.mempool[idx].len = audiodata->len;
                sendaudiodata.data = hf_sendbuff.mempool[idx].buffer;
                sendaudiodata.len = hf_sendbuff.mempool[idx].len;
                //TRACE("APP:sco send data = 0x%x ,len = %d\n",sendaudiodata.data,sendaudiodata.len);
                if(sendaudiodata.len)
                    aic_adp_hfp_send_sco_data(aic_hfp_msg->bdaddr,&sendaudiodata);
                hf_sendbuff.idx++;
#else
                AppReceive_ScoData(audiodata->data ,audiodata->len);
                #if SCO_LOOPBACK_TEST == 1
                memcpy(tmpdata.buffer, audiodata->data ,audiodata->len);
                tmpdata.len = audiodata->len;
                sendaudiodata.data = tmpdata.buffer;
                sendaudiodata.len = tmpdata.len;
                TRACE("APP:sco send data = 0x%x ,len = %d\n",sendaudiodata.data,sendaudiodata.len);
                if(sendaudiodata.len)
                    aic_adp_hfp_send_sco_data(aic_hfp_msg->bdaddr,&sendaudiodata);
                #else
                uint32_t idx = hf_sendbuff.idx % HF_SENDBUFF_MEMPOOL_NUM;
                AppPrepareSend_ScoData(&hf_sendbuff.mempool[idx].buffer[0], audiodata->len);
                hf_sendbuff.mempool[idx].len = audiodata->len;
                sendaudiodata.data = hf_sendbuff.mempool[idx].buffer;
                sendaudiodata.len = hf_sendbuff.mempool[idx].len;
                //TRACE("APP:sco send data = 0x%x ,len = %d\n",sendaudiodata.data,sendaudiodata.len);
                if(sendaudiodata.len)
                    aic_adp_hfp_send_sco_data(aic_hfp_msg->bdaddr,&sendaudiodata);
                hf_sendbuff.idx++;
                #endif
#endif
            }
            break;
        case AIC_ADP_HFP_CALL_STATUS_IND:
            {
                bt_hfp_adp_call_status call_state = aic_hfp_msg->p.callP.callS;
                if(call_state == BT_CALL_STATUS_ACTIVE){
                    //stop playing internal audio of (ring and phone call number),and then start sco playing
                }
            }
            break;
        case AIC_ADP_HFP_CALLSETUP_STATUS_IND:
            {
                bt_hfp_adp_call_status call_state = aic_hfp_msg->p.callsetupP.callS;
                TRACE("APP:call_setup_state = %d\n",call_state);
            }
            break;
        case AIC_ADP_HFP_CALLHOLD_STATUS_IND:
            {
                bt_hfp_adp_callhold_status hfp_call_hold = aic_hfp_msg->p.callholdP.callholdS;
                TRACE("APP:hfp_call_hold = %d\n",hfp_call_hold);
            }
            break;
        case AIC_ADP_HFP_RING_IND:

            break;
        case AIC_ADP_HFP_SIRI_STATUS:
            TRACE("APP: siri status = %d\n",aic_hfp_msg->p.siriP.siriS);
            break;
        case AIC_ADP_HFP_CURRENT_CALL_NUM:

            break;
        case AIC_ADP_HFP_SPEAKER_VOLUME:
            {
                U8 volume = (U8)aic_hfp_msg->p.volP.volume;
                TRACE("APP:HFP_SPEAKER_VOLUME = %d\n",volume);
                app_set_hfp_volume(&aic_hfp_msg->bdaddr,volume);
#if APP_SUPPORT_TWS == 0
                app_bt_local_volume_handle(1,app_get_hfp_volume(&aic_hfp_msg->bdaddr));
#endif
            }
            break;
        case AIC_ADP_HFP_COMMON_AT_RESULT_IND:
            {
                U8 *at_resualt_string = (U8 *)aic_hfp_msg->p.atP.at_result;
                // example: +CCLK:"21/01/12, 11:59:13"
                struct tm timer = {0,};
                time_t gmt;
                timer.tm_year = 2000 + (at_resualt_string[7] - '0') * 10 + (at_resualt_string[8] - '0') - YEAR0;
                timer.tm_mon  = (at_resualt_string[10] - '0') * 10 + (at_resualt_string[11] - '0');
                timer.tm_mday = (at_resualt_string[13] - '0') * 10 + (at_resualt_string[14] - '0');
                timer.tm_hour = (at_resualt_string[17] - '0') * 10 + (at_resualt_string[18] - '0');
                timer.tm_min  = (at_resualt_string[20] - '0') * 10 + (at_resualt_string[21] - '0');
                timer.tm_sec  = (at_resualt_string[23] - '0') * 10 + (at_resualt_string[24] - '0');
                gmt = mk_gmtime_offset_r(&timer, 8);
                aic_time_update((uint32_t)gmt, 0);
                TRACE("APP:at result = %s\n",at_resualt_string);
                TRACE("APP:time = %d-%02d-%02d %02d:%02d:%02d %d\n",timer.tm_year+YEAR0,timer.tm_mon+1,timer.tm_mday,
                        timer.tm_hour,timer.tm_min,timer.tm_sec,(uint32_t)gmt);
                at_cclk_acked = 1;
            }
        default:
            break;
    }
}




#endif
