#include "app_tws.h"
#if APP_SUPPORT_TWS == 1
#include "rtos.h"
#include "app_a2dp.h"
#include "app_bt.h"
#include "app_hfp.h"
#include "app_avrcp.h"
#include "app_bt_queue.h"
#include "trigger_ticker_api.h"

#if PLF_PMIC_VER_LITE == 1
#define AUDIO_TWS_OFFSET        40
#define VOICE_TWS_MSBC_OFFSET   120
#define VOICE_TWS_CVSD_OFFSET   200
#elif PLF_PMIC_VER_AUD == 1
#define AUDIO_TWS_OFFSET        (42*2)
#define VOICE_TWS_MSBC_OFFSET   (42*2)
#define VOICE_TWS_CVSD_OFFSET   (42*2)
#endif

#if TWS_MSS_AUTO_TEST == 1
TimerHandle_t app_bt_tws_mss_timer = NULL;
#endif
extern uint8_t bt_addr[6];
APP_TWS_BLE_STATE app_ble_state = STATE_IDLE;
APP_TWS_POWER_DOWN_STATE app_tws_pd_state = STATE_PD_IDLE;
APP_TWS_WEAR_STATE app_tws_wearing_state = WEAR_OFF;

extern AUD_SAMPRATE_T bt_parse_sbc_sample_rate(uint8_t samp_rate);

int app_tws_calloc(U8 **tws_cmd,U16 len)
{
    *tws_cmd = (U8 *)rtos_malloc(len);
    TRACE("APP:tws malloc addr = 0x%x,len = %d\n ",(U32)*tws_cmd,len);
    return 0;
}

int app_tws_free(U8 *tws_cmd)
{
    TRACE("APP: tws free addr = 0x%x\n",(U32)tws_cmd);
    rtos_free((void *)tws_cmd);
    return 0;
}

void app_tws_set_ble_state(APP_TWS_BLE_STATE state)
{
    app_ble_state = state;
    TRACE("APP: tws ble state = 0x%x\n",state);
}

APP_TWS_BLE_STATE app_tws_get_ble_state(void)
{
    return app_ble_state;
}

void app_tws_set_pd_state(APP_TWS_POWER_DOWN_STATE state)
{
    app_tws_pd_state = state;
    TRACE("APP: app_tws_pd_state = 0x%x\n",app_tws_pd_state);
}

APP_TWS_POWER_DOWN_STATE app_tws_get_pd_state(void)
{
    return app_tws_pd_state;
}

APP_TWS_WEAR_STATE app_tws_get_wear_state(void)
{
    return app_tws_wearing_state;
}

void app_connect_tws_test(void)
{
#if TEST_MODE_ROLE_SEND == 1
    BT_ADDR temp_bdaddr = {{0xaa,0xc0,0x00,0x88,0x88,0x33}};
#else
    BT_ADDR temp_bdaddr = {{0xa9,0xc0,0x00,0x88,0x88,0x33}};
#endif
#if TWS_BLE_CONNECT == 1
    memcpy(temp_bdaddr.addr,bt_addr,sizeof(BT_ADDR));
    aic_adp_tws_start_adv(temp_bdaddr);
#else
    aic_adp_connect_tws_peer_device(&temp_bdaddr);
#endif
}


#if TWS_MSS_AUTO_TEST == 1
void app_tws_mss_test_timer( TimerHandle_t xTimer )
{
    app_bt_tws_mss_control();
}

void app_tws_create_mss_timer(void)
{
    if(app_bt_tws_mss_timer == NULL)
        app_bt_tws_mss_timer = rtos_timer_create("APP_TWS_MSS",      \
                                                     10000,      \
                                                     pdFALSE,\
                                                     NULL,\
                                                     app_tws_mss_test_timer);
}

void app_tws_start_mss(void)
{
    if(rtos_timer_change_period(app_bt_tws_mss_timer, 2000, 0) == 0){

    }
}
#endif

void app_tws_default_connect(void)
{
#if TEST_MODE_ROLE_SEND == 1
    #if TWS_BLE_CONNECT == 1
        #if FPGA == 1
                    app_connect_tws_test();
        #else
                    switch(tws_app_get_flash_role()){
                        case TWS_MASTER:
                            aic_adp_tws_set_scan_para(0);
                            app_tws_set_ble_state(STATE_SCAN_EN);
                            break;
                        case TWS_SLAVE:
                            app_connect_tws_test();
                            app_tws_set_ble_state(STATE_ADV_EN);
                            break;
                        case TWS_NOROLE:
                            app_connect_tws_test();
                            app_tws_set_ble_state(STATE_ADV_EN);
                            break;
                        default:
                            break;
                    }
        #endif
    #endif
#else
    #if TWS_BLE_CONNECT == 1
        #if FPGA == 1
                aic_adp_tws_set_scan_para(1);
        #else
                switch(tws_app_get_flash_role()){
                    case TWS_MASTER:
                        aic_adp_tws_set_scan_para(0);
                        app_tws_set_ble_state(STATE_SCAN_EN);
                        break;
                    case TWS_SLAVE:
                        app_connect_tws_test();
                        app_tws_set_ble_state(STATE_ADV_EN);
                        break;
                    case TWS_NOROLE:
                        aic_adp_tws_set_scan_para(1);
                        app_tws_set_ble_state(STATE_SCAN_EN);
                        break;
                    default:
                        break;
            }
        #endif
    #endif
#endif
}

BOOL app_tws_send_data(uint8_t* ptrData, uint16_t length)
{
    return aic_adp_send_data(ptrData, length);
}

void app_tws_pause_a2dp(void)
{
    TRACE("APP:app_a2dp_pause.\n");
    if(app_get_a2dp_state() == A2DP_PLAY){
        app_media_play(AUD_BT_A2DP ,MC_STOP,0,true);
        app_set_a2dp_state(A2DP_CONNECTED);
    }
}

void app_tws_play_a2dp(A2DP_AUDIO_CAP *audio_cap)
{
    MediaCommonStruct audio_param;
    memset((U8*)&audio_param, 0, sizeof(MediaCommonStruct));
    TRACE("APP:app_a2dp_tws_play audio_cap = 0x%x\n",audio_cap);
    if(audio_cap){
        audio_param.p.aud_ctrl.a2dpcodec = audio_cap->codec_type;
        audio_param.p.aud_ctrl.samplerate = bt_parse_sbc_sample_rate(audio_cap->sample_rate_bit);

        audio_param.p.aud_ctrl.channel = audio_cap->channel;
        audio_param.p.aud_ctrl.numBlocks = audio_cap->numBlocks;
        audio_param.p.aud_ctrl.numSubBands = audio_cap->numSubBands;
        audio_param.p.aud_ctrl.dpll_mode = AUD_DPLL_TWS;
        app_media_play(AUD_BT_A2DP ,MC_STOP,0,false);
        app_media_play(AUD_BT_A2DP ,MC_OPEN,&audio_param,true);
        app_set_a2dp_state(A2DP_PLAY);
    }
}

void app_tws_stop_hfp(void)
{
    TRACE("APP:app_hfp_stop.\n");
#if APP_SUPPORT_HFP == 1
    app_set_hfp_state(APP_CONNECTED);
#endif
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1
    if(app_get_a2dp_state() != A2DP_PLAY)
#endif
    {
        app_media_play(AUD_BT_SCO ,MC_STOP,0,true);
    }
}

void app_tws_play_hfp(uint16_t negotiated_codec)
{
    MediaCommonStruct tmp;
    TRACE("APP:app_hfp_play.\n");
    memset((U8*)&tmp, 0, sizeof(MediaCommonStruct));
#if APP_SUPPORT_HFP == 1
    app_set_hfp_state(APP_PLAY_SCO);
#endif
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
#if APP_SUPPORT_HFP == 1
    app_set_hfp_scocodec(tmp.p.voc_ctrl.scocodec);
#endif
    tmp.p.voc_ctrl.dpll_mode = AUD_DPLL_TWS;
    app_media_play(AUD_BT_SCO ,MC_OPEN,&tmp,false);
}

uint32_t app_tws_handle_trig_clk(rwip_time_t *bt_clk,uint32_t trig_num)
{
    uint32_t ret = 0;

    ret = ((trig_num - bt_clk->hs)*625 - bt_clk->hus)*13;// 20*24/37:40M-->26M   13:26M   20:40M
    return ret;
}
/*
      - 40 :will fix the time of trigger  -120 :fix msbc  -200 :fix cvsd
*/
uint32_t app_tws_handle_trig_clk_and_strboff(rwip_time_t *bt_clk,AppTwsMediaDataStruct * trig_num)// 20*24/37:40M-->26M   13:26M   20:40M
{
    uint32_t ret = 0;
    uint32_t fix_time_offset = AUDIO_TWS_OFFSET;
    if(app_get_a2dp_state() == A2DP_PLAY)
        fix_time_offset = AUDIO_TWS_OFFSET;
#if APP_SUPPORT_HFP == 1
    else if(app_get_hfp_state() == APP_PLAY_SCO){
        if(app_get_hfp_scocodec() == MEDIA_SCO_CODEC_MSBC)
            fix_time_offset = VOICE_TWS_MSBC_OFFSET;
        else
            fix_time_offset = VOICE_TWS_CVSD_OFFSET;
    }
#endif
    if(trig_num->current_clk >= bt_clk->hs){
            ret = ((trig_num->current_clk - bt_clk->hs)*625+trig_num->current_bt_counter-bt_clk->hus + trig_num->strb_cycle_offset*2 - fix_time_offset)*13;
    }else{
            ret = (trig_num->strb_cycle_offset*2 + trig_num->current_bt_counter - bt_clk->hus - (bt_clk->hs - trig_num->current_clk )*625 - fix_time_offset)*13;
    }
    return ret;
}

__FAST_CODE__ void app_tws_set_trig_num(AppTwsMediaDataStruct *trig_num)
{
    uint32_t protect;
    uint32_t adj_1,adj_2;
    MediaCommonStruct tmp;
    rwip_time_t bt_clk;
    memset((U8*)&tmp, 0, sizeof(MediaCommonStruct));
    trigger_ticker_init();
    TRACE("APP:trig btclk = 0x%x btcounter = 0x%x ,btcounteroff = 0x%x,strb_offset = %d,counter_num = %d\n",trig_num->current_clk,trig_num->current_bt_counter,\
        trig_num->current_bt_counter_offset,trig_num->strb_cycle_offset,trig_num->counterNum);

    tmp.p.sync_ctrl.sync_param.counterNum = trig_num->counterNum;
    protect = rtos_protect();
    adj_1 = trigger_ticker_read();
    bt_clk = aic_adp_get_native_clk_plus_offset();
    adj_2 = trigger_ticker_read();
    if(trig_num->strb_cycle_offset){
        tmp.p.sync_ctrl.trig_time_delta = adj_2+(adj_2-adj_1);
        tmp.p.sync_ctrl.start_trig_num = app_tws_handle_trig_clk_and_strboff(&bt_clk,trig_num);
    }else{
        tmp.p.sync_ctrl.start_trig_num = app_tws_handle_trig_clk(&bt_clk,trig_num->current_clk);
    }
    app_media_mgr_set_command(MC_SET_TRIGNUM,&tmp);
    rtos_unprotect(protect);
    trigger_ticker_free();
    TRACE("APP:triger hs = 0x%x hus = %d, %d,%d\n",bt_clk.hs ,bt_clk.hus,adj_1,adj_2);
    TRACE("APP:start_trig_num = %d\n",tmp.p.sync_ctrl.start_trig_num);
#if APP_SUPPORT_HFP == 1
    if(app_get_hfp_state()== APP_PLAY_SCO && app_get_a2dp_state() != A2DP_PLAY){
        if(tws_app_get_role() == TWS_MASTER)
            tmp.p.sync_ctrl.need_clean = true;
        else
            tmp.p.sync_ctrl.need_clean = false;
        app_media_play(AUD_BT_SCO,MC_PRELOAD_PLAY,&tmp,true);
    }
    else
#endif
    if(app_get_a2dp_state() == A2DP_PLAY && tws_app_get_role() == TWS_SLAVE)
    {
        app_media_play(AUD_BT_A2DP,MC_TRIGNUM_PLAY,&tmp,true);
    }
}

void app_tws_set_audio_sync_param(AppTwsMediaDataStruct *audio_sync)
{
    MediaCommonStruct tmp;
    if(!audio_sync)
        return;
    memset((U8*)&tmp, 0, sizeof(MediaCommonStruct));

    //TRACE("APP:ctNum = %d ,ct_lo = %d,btclk = 0x%x,bt_hus = %d,strb_cycle_offset = %d\n",audio_sync->counterNum, audio_sync->master_current_samplerate,audio_sync->current_clk,audio_sync->current_bt_counter,audio_sync->strb_cycle_offset);
    tmp.p.sync_ctrl.sync_param.current_clk = audio_sync->current_clk;
    tmp.p.sync_ctrl.sync_param.counterNum = audio_sync->counterNum;
    tmp.p.sync_ctrl.sync_param.master_current_samplerate = audio_sync->master_current_samplerate;
    tmp.p.sync_ctrl.sync_param.current_bt_counter = audio_sync->current_bt_counter;
    tmp.p.sync_ctrl.sync_param.strb_cycle_offset = audio_sync->strb_cycle_offset;
    tmp.p.sync_ctrl.sync_param.current_bt_counter_offset = audio_sync->current_bt_counter_offset;
    app_media_mgr_send_command(AUD_COMMON,MC_SYNC_PARAM,&tmp);
}

void app_bt_disconnect_tws(void)
{
    if(tws_app_get_role() == TWS_MASTER){
        aic_adp_disconnect_tws();
    }else if(tws_app_get_role() == TWS_SLAVE){
        U8 *tws_cmd = NULL;
        app_tws_calloc(&tws_cmd,APP_TWS_LEN_2);
        if(tws_cmd){
            BOOL ret = FALSE;
            tws_cmd[0] = TWS_LINK_CONTROL_PARAM;
            tws_cmd[1] = 0;
            ret = app_tws_send_data(tws_cmd,APP_TWS_LEN_2);
            if(ret == FALSE){
                app_tws_free(tws_cmd);
            }
        }
    }
}

void app_tws_begin_mss(void)
{
    if(tws_app_get_role() == TWS_MASTER){
        aic_adp_host_m_s_switch();
    }else if(tws_app_get_role() == TWS_SLAVE){
        U8 *tws_cmd = NULL;
        app_tws_calloc(&tws_cmd,APP_TWS_LEN_2);
        if(tws_cmd){
            BOOL ret = FALSE;
            tws_cmd[0] = TWS_MSS_PARAM;
            tws_cmd[1] = 1;
            ret = app_tws_send_data(tws_cmd,APP_TWS_LEN_2);
            if(ret == FALSE){
                app_tws_free(tws_cmd);
            }
        }
    }
}

void app_tws_power_down(void)
{
    switch(tws_app_get_role()){
        case TWS_MASTER:
        case TWS_SLAVE:
            {
                #if PLF_KEY_MODULE
                pwrdown_set_state(USER_POWER_DOWN);
                #endif
                if(app_tws_get_pd_state() == STATE_PD_IDLE){
                    U8 *tws_cmd = NULL;
                    app_tws_calloc(&tws_cmd,APP_TWS_LEN_2);
                    if(tws_cmd){
                        BOOL ret = FALSE;
                        tws_cmd[0] = TWS_POWERD_PARAM;
                        tws_cmd[1] = 1;
                        ret = app_tws_send_data(tws_cmd,APP_TWS_LEN_2);
                        if(ret == FALSE){
                            app_tws_free(tws_cmd);
                        }
                    }
                }else{
                    rtos_task_suspend(500);
                    if(tws_app_get_role() == TWS_MASTER){
                        app_bt_disconnect_all();
                    }
                    aic_adp_close_dev();
                    app_bt_start_pd_timer();
                }
            }
            break;
        default:
            break;
    }

}

void app_tws_wearing_state_handle(uint32_t state)
{
    if(state){
        app_tws_wearing_state = WEAR_ON;
        //on
        switch(tws_app_get_role()){
            case TWS_MASTER:
                
                break;
            case TWS_SLAVE:
                
                break;
            default:
                break;
        }
    }else{
        //off
        app_tws_wearing_state = WEAR_OFF;
        switch(tws_app_get_role()){
            case TWS_MASTER:
                app_bt_tws_mss_control();
                break;
            case TWS_SLAVE:
                
                break;
            default:
                break;
        }
    }
}

void app_tws_volume_sync_handle(uint8_t mode,uint8_t volume)
{
    TRACE("APP: mode %x,volume %x\n",mode,volume);
    switch(tws_app_get_role()){
        case TWS_MASTER:
            {
                U8 *tws_cmd = NULL;
                app_tws_calloc(&tws_cmd,APP_TWS_LEN_3);
                if(tws_cmd){
                    BOOL ret = FALSE;
                    tws_cmd[0] = TWS_SET_VOLUME_PARAM;
                    tws_cmd[1] = mode;
                    tws_cmd[2] = volume;
                    ret = app_tws_send_data(tws_cmd,APP_TWS_LEN_3);
                    if(ret == FALSE){
                        app_tws_free(tws_cmd);
                    }
                }
            }
            break;
        case TWS_SLAVE:
            {
                APP_DEVLIST * tmp_devinfo = NULL;
                app_bt_local_volume_handle(mode,volume);
                if(mode){
                    tmp_devinfo = aic_adp_get_hfp_current_devinfo();
                    if(tmp_devinfo == NULL){
                        return;
                    }
                    tmp_devinfo->peer_volume_hfp = volume;
                    app_set_hfp_volume(&tmp_devinfo->bdaddr,volume);
                }else{
                    tmp_devinfo = aic_adp_get_a2dp_current_devinfo();
                    if(tmp_devinfo == NULL){
                        return;
                    }
                    tmp_devinfo->peer_volume_a2dp = volume;
                    app_set_avrcp_volume(&tmp_devinfo->bdaddr,(8*(volume+1) - 1));
                }
            }
            break;
        default:
            break;
    }
}

BOOL app_tws_key_handle(uint32_t key)
{
    BOOL ret = FALSE;
    uint32_t send_key = 0;

    switch(key){
        case APP_KEY_PLAY|APP_KEY_PRESS:
            send_key = key;
            break;
        case APP_KEY_VOLADD|APP_KEY_PRESS:
        case APP_KEY_VOLADD|APP_KEY_HOLD:
            send_key = key;
        case APP_KEY_VOLSUB|APP_KEY_PRESS:
        case APP_KEY_VOLSUB|APP_KEY_HOLD:
            send_key = key;
            break;
        case APP_KEY_NEXT|APP_KEY_PRESS:
            send_key = key;
            break;
        case APP_KEY_PREV|APP_KEY_PRESS:
            send_key = key;
            break;
        case APP_KEY_NEXT|APP_KEY_HOLD:
            send_key = key;
            break;
        case APP_KEY_PREV|APP_KEY_HOLD:
            send_key = key;
            break;
        case APP_KEY_NEXT|APP_KEY_UP:
            send_key = key;
            break;
        case APP_KEY_PREV|APP_KEY_UP:
            send_key = key;
            break;
        case APP_KEY_PLAY|APP_KEY_DOUBLE_CLICK:
            send_key = key;
            break;
        case APP_KEY_GSENSOR|APP_KEY_PRESS:
            if(tws_app_get_role() == TWS_MASTER){
                uint32_t change_key;
                change_key = APP_KEY_VOLADD|APP_KEY_PRESS;
                app_bt_send_key(change_key);
            }else if(tws_app_get_role() == TWS_SLAVE){
                send_key = APP_KEY_VOLSUB|APP_KEY_PRESS;
            }
            break;
        case APP_KEY_GSENSOR|APP_KEY_DOUBLE_CLICK:
            if(tws_app_get_role() == TWS_MASTER){
                uint32_t change_key;
                change_key =  APP_KEY_PLAY|APP_KEY_PRESS;
                app_bt_send_key(change_key);
            }else if(tws_app_get_role() == TWS_SLAVE){
                send_key =  APP_KEY_PLAY|APP_KEY_PRESS;
            }
            break;
        case APP_KEY_GSENSOR|APP_KEY_TRIPLE_CLICK:
            if(tws_app_get_role() == TWS_MASTER){
                uint32_t change_key;
                change_key = APP_KEY_NEXT|APP_KEY_PRESS;
                app_bt_send_key(change_key);
            }else if(tws_app_get_role() == TWS_SLAVE){
                send_key = APP_KEY_PREV|APP_KEY_PRESS;
            }
            break;
        case APP_KEY_HOLD_2S:
            if(tws_app_get_role() == TWS_MASTER){
                uint32_t change_key;
                change_key = APP_KEY_PLAY|APP_KEY_HOLD;
                app_bt_send_key(change_key);
            }else if(tws_app_get_role() == TWS_SLAVE){
                send_key = APP_KEY_PLAY|APP_KEY_HOLD;
            }
            break;
        case APP_KEY_HOLD_5S:
            app_tws_power_down();
            break;
        default:
            break;
    }

    if(send_key && tws_app_get_role() == TWS_SLAVE){
        U8 *tws_cmd = NULL;
        ret = TRUE;
        app_tws_calloc(&tws_cmd,APP_TWS_LEN_5);
        if(tws_cmd){
            BOOL ret = FALSE;

            tws_cmd[0] = TWS_KEY_PARAM;
            tws_cmd[1] = (U8)( send_key&0x000000ff);
            tws_cmd[2] = (U8)((send_key&0x0000ff00)>>8);
            tws_cmd[3] = (U8)((send_key&0x00ff0000)>>16);
            tws_cmd[4] = (U8)((send_key&0xff000000)>>24);
            ret = app_tws_send_data(tws_cmd,APP_TWS_LEN_5);
            if(ret == FALSE){
                app_tws_free(tws_cmd);
            }
        }
    }
    return ret;
}

void app_tws_msg_handle(AIC_EVENT *event)
{

    switch(event->EventId){
        case AIC_ADP_TWS_CONNECTED_IND:
            {
                AIC_ADP_TWS_EVENT *aic_adp_tws_msg = (AIC_ADP_TWS_EVENT *)event->Param;
                TRACE("APP:app_tws_connect_ind .status = %d\n",aic_adp_tws_msg->p.conP.reason);
            }
            break;
        case AIC_ADP_TWS_CONNECTED_CNF:
            {
                AIC_ADP_TWS_EVENT *aic_adp_tws_msg = (AIC_ADP_TWS_EVENT *)event->Param;
                TRACE("APP:app_tws_connect_cnf .status = %d\n",aic_adp_tws_msg->p.conP.reason);
                if(aic_adp_tws_msg->p.conP.reason){
#if TWS_BLE_CONNECT == 1
                    aic_adp_tws_set_scan_para(0);
                    app_tws_set_ble_state(STATE_SCAN_EN);
#endif
                }else{
                    app_bt_connect();
                }
            }
            break;
        case AIC_ADP_TWS_DISCONNECTED:
            {
                AIC_ADP_TWS_EVENT *aic_adp_tws_msg = (AIC_ADP_TWS_EVENT *)event->Param;
                TRACE("APP:app_tws_disconnect ,reason = %d,last_role = %d\n",aic_adp_tws_msg->p.discP.reason,aic_adp_tws_msg->p.discP.last_role);
                if(tws_app_get_flash_role() < TWS_NOROLE){
                    switch(aic_adp_tws_msg->p.discP.last_role){
                        case TWS_SLAVE:
#if TWS_BLE_CONNECT == 1
                            app_tws_pause_a2dp();
                            app_tws_stop_hfp();
                            app_connect_tws_test();
                            app_tws_set_ble_state(STATE_ADV_EN);
#endif
                            break;
                        case TWS_MASTER:
#if TWS_BLE_CONNECT == 1
                            aic_adp_tws_set_scan_para(0);
                            app_tws_set_ble_state(STATE_SCAN_EN);
#endif
                            break;
                        default:
                            break;
                    }
                }else{
                    app_tws_default_connect();
                }
#if APP_SUPPORT_HFP == 1
                app_set_hfp_scocodec(MEDIA_SCO_CODEC_NONE);
#endif
            }
            break;
        case AIC_ADP_TWS_STREAM_STARTED:
            {
                AIC_ADP_A2DP_EVENT *aic_a2dp_msg = (AIC_ADP_A2DP_EVENT *)event->Param;
                A2DP_AUDIO_CAP *audio_cap = (A2DP_AUDIO_CAP *)aic_a2dp_msg->p.signalingP.audioCodecP;
                app_tws_play_a2dp(audio_cap);
            }
            break;
        case AIC_ADP_TWS_STREAM_SUSPENDED:
            {
                app_tws_pause_a2dp();
            }
            break;
        case AIC_ADP_TWS_STREAM_DATA_IND:
            {
                AIC_ADP_A2DP_EVENT *aic_a2dp_msg = (AIC_ADP_A2DP_EVENT *)event->Param;
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
        case AIC_ADP_TWS_SCO_CONNECT:
            {
                AIC_ADP_HFP_EVENT *aic_hfp_msg = (AIC_ADP_HFP_EVENT *)event->Param;
                TRACE("APP:hfp_sco_connect\n");
                TRACE("APP:hfp_codec_type = %d\n",aic_hfp_msg->p.scoP.negotiated_codec);
                app_tws_play_hfp((U16)aic_hfp_msg->p.scoP.negotiated_codec);
            }
            break;
        case AIC_ADP_TWS_SCO_DISCONNECT:
            {
                app_tws_stop_hfp();
            }
            break;
        case AIC_ADP_TWS_SCO_DATA_IND:
            {
                AIC_ADP_HFP_EVENT *aic_hfp_msg = (AIC_ADP_HFP_EVENT *)event->Param;
                AIC_ADP_HFP_AUDIO_DATA *audiodata = (AIC_ADP_HFP_AUDIO_DATA *)aic_hfp_msg->p.dataindP.buff;

                //TRACE("APP:sco_data_int len = %d\n",audiodata->len);
                AppReceive_ScoData(audiodata->data ,audiodata->len);
            }
            break;
        case AIC_ADP_TWS_TRIG_NUM:
            {
                AIC_ADP_TWS_EVENT *aic_adp_tws_msg = (AIC_ADP_TWS_EVENT *)event->Param;
                app_tws_set_trig_num((AppTwsMediaDataStruct *)aic_adp_tws_msg->p.trigP.tws_trig_data);
            }
            break;
        case AIC_ADP_TWS_AUDIO_SYNC_MSG:
            {
                AIC_ADP_TWS_EVENT *aic_adp_tws_msg = (AIC_ADP_TWS_EVENT *)event->Param;
                app_tws_set_audio_sync_param((AppTwsMediaDataStruct *)aic_adp_tws_msg->p.syncP.tws_sync_data);
            }
            break;
        case AIC_ADP_TWS_ADV_DATA:
            {
#if TWS_BLE_CONNECT == 1
                host_data_struct *rx_data = (host_data_struct *)event->Param;
                BT_ADDR remove_addr;

                memcpy(remove_addr.addr, &rx_data->data[26], 6);
                TRACE("APP:remove addr %x,%x,%x,%x,%x,%x\n",remove_addr.addr[0],remove_addr.addr[1],remove_addr.addr[2],\
                                                            remove_addr.addr[3],remove_addr.addr[4],remove_addr.addr[5]);
                aic_adp_tws_set_scan_disable();
                aic_adp_connect_tws_peer_device(&remove_addr);
#endif
            }
            break;
        case AIC_ADP_TWS_LOST_SEQUENCE:
            {
                app_bt_send_bt_audio_restart();
            }
            break;
        case AIC_ADP_TWS_DATA_SEND:
            {
                AIC_ADP_TWS_EVENT *aic_adp_tws_msg = (AIC_ADP_TWS_EVENT *)event->Param;
                host_data_struct *tx_done = (host_data_struct *)aic_adp_tws_msg->p.datasendP.buff;

                switch(tx_done->data[0]){
                    case TWS_KEY_PARAM:
                        if(APP_TWS_LEN_5 == tx_done->len){
                            app_tws_free(tx_done->data);
                        }
                        break;
                    case TWS_SET_VOLUME_PARAM:
                        if(APP_TWS_LEN_3 == tx_done->len){
                            app_tws_free(tx_done->data);
                        }
                        break;
                    case TWS_LINK_CONTROL_PARAM:
                        if(APP_TWS_LEN_2 == tx_done->len){
                            app_tws_free(tx_done->data);
                        }
                        break;
                    case TWS_MSS_PARAM:
                        if(APP_TWS_LEN_2 == tx_done->len){
                            app_tws_free(tx_done->data);
                        }
                        break;
                    case TWS_POWERD_PARAM:
                        if(APP_TWS_LEN_2 == tx_done->len){
                            app_tws_free(tx_done->data);
                            app_tws_set_pd_state(STATE_PD_PENDING);
                            app_tws_power_down();
                        }
                        break;
                    default:
                        break;
                }
            }
            break;
        case AIC_ADP_TWS_DATA_IND:
            {
                AIC_ADP_TWS_EVENT *aic_adp_tws_msg = (AIC_ADP_TWS_EVENT *)event->Param;
                host_data_struct *rx_done = (host_data_struct *)aic_adp_tws_msg->p.dataindP.buff;
#if 0
                TRACE("APP:tws rx len:%d ;data:%x,%x,%x,%x,%x\n",rx_done->len,rx_done->data[0],\
                    rx_done->data[1],rx_done->data[2],rx_done->data[3],rx_done->data[4]);
#endif
                #if PLF_BT_OTA
                if(app_ota_get_access() == OTA_BY_SPP){
                    app_ota_receive_data(rx_done->data,rx_done->len);
                    break;
                }
                #endif
                switch(rx_done->data[0])
                {
                    case TWS_KEY_PARAM:
                        if(APP_TWS_LEN_5 == rx_done->len){
                            uint32_t key = 0;
                            uint8_t *data = rx_done->data;
                            key = ((uint32_t)data[1])|(((uint32_t)data[2])<<8)|(((uint32_t)data[3])<<16)|(((uint32_t)data[4])<<24);
                            app_bt_send_key(key);
                        }
                        break;
                    case TWS_SET_VOLUME_PARAM:
                        if(APP_TWS_LEN_3 == rx_done->len){
                            #if APP_SUPPORT_TWS_LOCAL_VOL_SYNC == 1
                            app_tws_volume_sync_handle(rx_done->data[1],rx_done->data[2]);
                            #endif
                        }
                        break;
                    case TWS_LINK_CONTROL_PARAM:
                        if(APP_TWS_LEN_2 == rx_done->len){
                            if(rx_done->data[1] == 0){
                                aic_adp_disconnect_tws();
                            }
                        }
                        break;
                    case TWS_MSS_PARAM:
                        if(APP_TWS_LEN_2 == rx_done->len){
                            if(rx_done->data[1] == 1){
                                if(app_tws_get_wear_state() == WEAR_OFF)
                                    app_tws_begin_mss();
                            }
                        }
                        break;
                    case TWS_POWERD_PARAM:
                        if(APP_TWS_LEN_2 == rx_done->len){
                            if(rx_done->data[1] == 1){
                                app_tws_set_pd_state(STATE_PD_PENDING);
                                app_tws_power_down();
                            }
                        }
                        break;
                    case TWS_OTA_PARAM:
                        {
                            #if PLF_BT_OTA
                            app_ota_receive_data(&rx_done->data[1],(rx_done->len-1));
                            #endif
                        }
                        break;
                    default :
                        break;
                }
            }
            break;
        case AIC_ADP_TWS_MSS_COMPLETE:
            {
#if TWS_MSS_AUTO_TEST == 1
                app_tws_start_mss();
#endif
            }
            break;
        default:
            break;
    }
}

void app_tws_init(void)
{
#if TWS_MSS_AUTO_TEST == 1
    app_tws_create_mss_timer();
#endif
}
#endif
