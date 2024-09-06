#include "plf.h"
#if PLF_BT_STACK == 1
#if PLF_BLE_ONLY == 1
#include "app_ble_only.h"
#if (BLE_APP_AUDTRANSMITS || BLE_APP_AUDTRANSMITC)
#include <string.h>
#include "flash_api_btdm.h"
#include "ble_task_msg.h"
#include "sleep_api.h"
#include "app_media.h"
#include "app_media_mgr.h"
#include "co_main.h"

static struct aud_state_t local_aud_state;
static BleBuff_t ble_buff;
static co_timer *app_ble_data_send_timer = NULL;
static void app_ble_data_send_timer_stop(void);
static void app_ble_data_send_timer_init(void);

void app_ble_set_local_aud_state(uint16_t codec_type,uint8_t state)
{
    local_aud_state.codec_type = codec_type;
    local_aud_state.state = state;
}

enum codec_state app_ble_get_local_aud_state(void)
{
    return local_aud_state.state;
}

void app_ble_aud_stop(void)
{
    TRACE("APP:app_ble_aud_stop.\n");
    app_ble_set_local_aud_state(MEDIA_SCO_CODEC_NONE,STATE_IDLE);
    app_media_play(AUD_BT_SCO ,MC_STOP,0,true);
    app_ble_data_send_timer_stop();
}

void app_ble_aud_play(uint16_t codec_type)
{
    MediaCommonStruct tmp;
    TRACE("APP:app_ble_aud_play.\n");
    memset((U8*)&tmp, 0, sizeof(MediaCommonStruct));

    app_ble_set_local_aud_state(codec_type,STATE_PLAY);
    switch (codec_type)
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
    tmp.p.voc_ctrl.dpll_mode = AUD_DPLL_NORMAL;
    app_media_play(AUD_BT_SCO ,MC_PLAY,&tmp,false);
    app_ble_data_send_timer_init();
    memset((U8*)&tmp, 0, sizeof(MediaCommonStruct));
    tmp.p.vol_ctrl.vol_in.vol_level = 0xa;
    tmp.p.vol_ctrl.vol_out.extera12dB = 0;
    tmp.p.vol_ctrl.vol_out.extera6dB = 1;
    tmp.p.vol_ctrl.vol_out.vol_level = 0x2f;
    app_media_mgr_set_command(MC_SETVOLUME,&tmp);
}

#if BLE_APP_AUDTRANSMITS
void app_ats_recv_aud_ctrl_handler(uint8_t *data, uint32_t length)
{
    struct aud_state_t *tmp;
    if(length == sizeof(struct aud_state_t)){
        tmp = (struct aud_state_t *)data;
        TRACE("BLE_APP: recv_aud_ctrl state %x,codec_type %x\n",tmp->state,tmp->codec_type);
        switch(tmp->state){
            case STATE_IDLE:
                {
                    if(app_ble_get_local_aud_state() == STATE_PLAY){
                        app_ble_aud_stop();
                    }
                }
                break;
            case STATE_PLAY:
                {
                    if(app_ble_get_local_aud_state() == STATE_IDLE){
                        app_ble_aud_play(tmp->codec_type);
                    }
                }
                break;
            default:
                break;
        }
    }
}

void app_ats_recv_aud_data_handler(uint8_t *data, uint32_t length)
{
    AppReceive_ScoData(data ,length);
}

void app_ats_sent_aud_info_handler(uint8_t state)
{

}

void app_ats_sent_aud_data_handler(uint8_t state)
{
    if(state){
        TRACE("BLE_APP: sent_aud_data state %x\n",state);
    }
    ble_buff.buff_count++;
    TRACE("Sd num = %x\n",ble_buff.buff_count);
}


void app_ats_send_aud_info(uint16_t codec_type,uint8_t state)
{
    struct aud_state_t tmp;
    tmp.codec_type = codec_type;
    tmp.state = state;
    TRACE("BLE_APP: send_aud_info state %x,codec_type %x\n",tmp.state,tmp.codec_type);
    app_audtransmits_send_aud_info((uint8_t *)&tmp,sizeof(tmp));
    if(state == STATE_PLAY){
        app_ble_aud_play(codec_type);
    }else{
        app_ble_aud_stop();
    }
}

void app_ats_send_aud_data(void)
{
    BleSendData_t * send_ptr;
    int get_len = 0;
    TRACE("S num = %x\n",ble_buff.buff_count);
    if(ble_buff.buff_count){
        send_ptr = &ble_buff.mempool[ble_buff.idx];
        ble_buff.idx++;
        if(ble_buff.idx == BLE_SENDBUFF_MEMPOOL_NUM){
            ble_buff.idx = 0;
        }
        if(send_ptr){
            send_ptr->len = 240;
            get_len = AppPrepareSend_ScoData(send_ptr->buffer, send_ptr->len);
            if(get_len){
                app_audtransmits_send_aud_data(send_ptr->buffer,get_len);
                ble_buff.buff_count--;
            }
        }
    }
}

#endif
#if BLE_APP_AUDTRANSMITC
void app_atc_recv_aud_info_handler(uint8_t *data, uint32_t length)
{
    struct aud_state_t *tmp;
    TRACE("BLE_APP: recv_aud_info length %x\n",length);
    if(length == sizeof(struct aud_state_t)){
        tmp = (struct aud_state_t *)data;
        TRACE("BLE_APP: recv_aud_info state %x,codec_type %x\n",tmp->state,tmp->codec_type);
        switch(tmp->state){
            case STATE_IDLE:
                {
                    if(app_ble_get_local_aud_state() == STATE_PLAY){
                        app_ble_aud_stop();
                    }
                }
                break;
            case STATE_PLAY:
                {
                    if(app_ble_get_local_aud_state() == STATE_IDLE){
                        app_ble_aud_play(tmp->codec_type);
                    }
                }
                break;
            default:
                break;
        }
    }
}


void app_atc_recv_aud_data_handler(uint8_t *data, uint32_t length)
{
    AppReceive_ScoData(data ,length);
}

void app_atc_send_aud_ctrl(uint16_t codec_type,uint8_t state)
{
    struct aud_state_t tmp;
    tmp.codec_type = codec_type;
    tmp.state = state;
    TRACE("BLE_APP: send_aud_ctrl state %x,codec_type %x\n",tmp.state,tmp.codec_type);
    app_audtransmitc_aud_ctrl_wr_req((uint8_t *)&tmp,sizeof(tmp));
    if(state == STATE_PLAY){
        app_ble_aud_play(codec_type);
    }else{
        app_ble_aud_stop();
    }
}


void app_atc_send_aud_data(void)
{

}

#endif

static void app_ble_data_send_timer_hanlder(void *cb_param)
{
    app_ble_data_send_timer_notify();
}

static void app_ble_data_send_timer_start(void)
{
    if(app_ble_data_send_timer == NULL){
        co_timer_start(&app_ble_data_send_timer,BLE_DATA_SEND_TIME_INTERVAL,NULL,app_ble_data_send_timer_hanlder,1);
    }
}

static void app_ble_data_send_timer_init_hanlder(void *cb_param)
{
    app_ble_data_send_timer = NULL;
    app_ble_data_send_timer_start();
}



void app_ble_audtransmit_timer_notify_handler(void)
{
    #if BLE_APP_AUDTRANSMITS
    app_ats_send_aud_data();
    #endif
    #if BLE_APP_AUDTRANSMITC
    app_atc_send_aud_data();
    #endif
}

static void app_ble_data_send_timer_stop(void)
{
    if(app_ble_data_send_timer){
        co_timer_stop(app_ble_data_send_timer);
        app_ble_data_send_timer = NULL;
    }
}

static void app_ble_data_send_timer_init(void)
{
    if(app_ble_data_send_timer == NULL){
        co_timer_start(&app_ble_data_send_timer,1000,NULL,app_ble_data_send_timer_init_hanlder,0);
    }
}

void app_ble_audtransmit_init(void)
{
    memset(&ble_buff,0,sizeof(ble_buff));
    ble_buff.buff_count = BLE_SENDBUFF_MEMPOOL_NUM;
    TRACE("BLE_APP: %s\n",__func__);
    #if BLE_APP_AUDTRANSMITS
    app_audtransmits_register_aud_info_sent_cb(app_ats_sent_aud_info_handler);
    app_audtransmits_register_aud_data_sent_cb(app_ats_sent_aud_data_handler);
    app_audtransmits_register_aud_ctrl_recv_cb(app_ats_recv_aud_ctrl_handler);
    app_audtransmits_register_aud_data_recv_cb(app_ats_recv_aud_data_handler);
    #endif
    #if BLE_APP_AUDTRANSMITC
    app_audtransmitc_register_aud_info_cb(app_atc_recv_aud_info_handler);
    app_audtransmitc_register_aud_data_cb(app_atc_recv_aud_data_handler);
    #endif
}

#endif
#endif
#endif
