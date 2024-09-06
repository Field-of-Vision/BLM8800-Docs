#include "tgt_cfg_bt.h"
#if APP_SUPPORT_AVRCP == 1
#include "rtos.h"
#include "app_bt.h"
#include "aic_adp_api.h"


void app_set_avrcp_volume(BT_ADDR *bdaddr,S8 volume)
{
    APP_DEVLIST *tmp = NULL;
    tmp = app_bt_get_mgr_devinfo(*bdaddr);

    btdev_info* dev_info = aic_adp_get_devinfo_by_addr(bdaddr);
    if(tmp && dev_info){
        dev_info->peer_a2dp_vol = (((int)volume&0x7f)<<4)/128;
        if (dev_info->peer_a2dp_vol > AUD_VOLUME_LEVEL_15 - AUD_VOLUME_LEVEL_0){
            dev_info->peer_a2dp_vol = AUD_VOLUME_LEVEL_15 - AUD_VOLUME_LEVEL_0;
        }else if (dev_info->peer_a2dp_vol < AUD_VOLUME_LEVEL_0 - AUD_VOLUME_LEVEL_0){
            dev_info->peer_a2dp_vol = AUD_VOLUME_LEVEL_0 - AUD_VOLUME_LEVEL_0;
        }
        tmp->peer_volume_a2dp = dev_info->peer_a2dp_vol;
        TRACE("APP:app_set_avrcp_volume %d\n",(dev_info->peer_a2dp_vol));
    }
}

U8 app_get_avrcp_volume(BT_ADDR *bdaddr)
{
    U8 volume = 0x7f;
    btdev_info* dev_info = aic_adp_get_devinfo_by_addr(bdaddr);
    if(dev_info){
        if(dev_info->peer_a2dp_vol == 0){
            volume = 0x3f;
        }else{
            if(dev_info->peer_a2dp_vol > (AUD_VOLUME_LEVEL_0 - AUD_VOLUME_LEVEL_0)&& dev_info->peer_a2dp_vol <= (AUD_VOLUME_LEVEL_15 - AUD_VOLUME_LEVEL_0)){
                volume = 8*(dev_info->peer_a2dp_vol+1) - 1;
            }else{
                dev_info->peer_a2dp_vol = AUD_VOLUME_LEVEL_15 - AUD_VOLUME_LEVEL_0;
                volume = 8*(dev_info->peer_a2dp_vol+1) - 1;
            }
        }
    }
    TRACE("APP:app_get_avrcp_volume %d,0x%x\n",(dev_info->peer_a2dp_vol),volume);
    return volume;
}

void app_avrcp_report_volume_to_phone(BT_ADDR bdaddr,          U8 volume)
{
    TRACE("APP:report local volume 0x%x\n",volume);
    aic_adp_avrcp_send_volume_report(bdaddr,volume);
}

BOOL app_avrcp_key_handle(uint32_t key)
{
    BOOL ret = FALSE;
    APP_DEVLIST * a2dp_devinfo = NULL;

    a2dp_devinfo = aic_adp_get_a2dp_current_devinfo();
    if(a2dp_devinfo == NULL){
        TRACE("APP:a2dp_devinfo error!\n");
        return ret;
    }

    switch(key){
        case APP_KEY_PLAY|APP_KEY_PRESS:
            TRACE("APP:a2dp_state %d\n",a2dp_devinfo->a2dp_state);
            if(a2dp_devinfo->a2dp_state == A2DP_ADP_STATE_PAUSE || a2dp_devinfo->a2dp_state == A2DP_ADP_STATE_OPEN){
                aic_adp_avrcp_send_key_play(a2dp_devinfo->bdaddr);
                ret = TRUE;
            }else if(a2dp_devinfo->a2dp_state == A2DP_ADP_STATE_PLAY){
                aic_adp_avrcp_send_key_pause(a2dp_devinfo->bdaddr);
                ret = TRUE;
            }else{
                TRACE("APP:a2dp status error!");
            }
            break;
#if 1
        case APP_KEY_VOLADD|APP_KEY_PRESS:
        case APP_KEY_VOLADD|APP_KEY_HOLD:
        case APP_KEY_VOLSUB|APP_KEY_PRESS:
        case APP_KEY_VOLSUB|APP_KEY_HOLD:
            app_avrcp_report_volume_to_phone(a2dp_devinfo->bdaddr,app_get_avrcp_volume(&a2dp_devinfo->bdaddr));
            ret = TRUE;
            break;
#else
        case (APP_KEY_VOLADD|APP_KEY_PRESS):
        case (APP_KEY_VOLADD|APP_KEY_HOLD):
            aic_adp_avrcp_send_key_volume_up(a2dp_devinfo->bdaddr);
            ret = TRUE;
            break;
        case APP_KEY_VOLSUB|APP_KEY_PRESS:
        case APP_KEY_VOLSUB|APP_KEY_HOLD:
            aic_adp_avrcp_send_key_volume_down(a2dp_devinfo->bdaddr);
            ret = TRUE;
            break;
#endif
        case APP_KEY_NEXT|APP_KEY_PRESS:
            aic_adp_avrcp_send_key_forward(a2dp_devinfo->bdaddr);
            ret = TRUE;
            break;
        case APP_KEY_PREV|APP_KEY_PRESS:
            aic_adp_avrcp_send_key_backward(a2dp_devinfo->bdaddr);
            ret = TRUE;
            break;
        case APP_KEY_NEXT|APP_KEY_HOLD:
            //reserved
            break;
        case APP_KEY_PREV|APP_KEY_HOLD:
            //reserved
            break;
        case APP_KEY_NEXT|APP_KEY_UP:
            //reserved
            break;
        case APP_KEY_PREV|APP_KEY_UP:
            //reserved
            break;
        default:
            break;
    }
    return ret;
}

void app_avrcp_msg_handle(AIC_EVENT *event)
{
    AIC_ADP_AVRCP_EVENT *aic_avrcp_msg = (AIC_ADP_AVRCP_EVENT *)event->Param;
    switch(event->EventId)
    {
        case AIC_ADP_AVRCP_CONNECT:
            {
                BOOL support = false;
                TRACE("APP:app_avrcp_connect!\n");
#if APP_SUPPORT_IPHONE_VOLUME_SYNC == 1
                support = true;
#endif
                aic_adp_avrcp_support_volume_sync(support);
            }
            break;
        case AIC_ADP_AVRCP_DISCONNECT:
            TRACE("APP:app_avrcp_disconnect\n");
            break;

        case AIC_ADP_AVRCP_PANEL_PRESS:
            {
                bt_avrcpPanelOp op = (bt_avrcpPanelOp)aic_avrcp_msg->avrcpparam;
                TRACE("APP:TG panel press op = %x\n", op);

                switch(op)
                {
                    case APP_AVRCP_PANEL_VOLUME_UP:
                        TRACE("APP:avrcp_key_volume_up\n");
                        break;
                    case APP_AVRCP_PANEL_VOLUME_DOWN:
                        TRACE("APP: avrcp_key_volume_down\n");
                        break;
                    case APP_AVRCP_PANEL_PLAY:
                        TRACE("APP:avrcp start stream \n");
                        //aic_adp_a2dp_source_start();
                        break;
                    case APP_AVRCP_PANEL_PAUSE:
                        TRACE("APP:acrcp stop stream \n");
                        //aic_adp_a2dp_source_suspend();
                        break;
                    default :
                        break;
                }
            }
            break;

        case AIC_ADP_AVRCP_ADV_VOLUME_CHANGE:
            TRACE("APP:avrcp_volume_change vol =%d \n",aic_avrcp_msg->avrcpparam);
            app_set_avrcp_volume(&aic_avrcp_msg->bdaddr,(U8)aic_avrcp_msg->avrcpparam);
#if APP_SUPPORT_TWS == 0
            app_bt_local_volume_handle(0,app_get_avrcp_volume(&aic_avrcp_msg->bdaddr));
#endif
            break;
        case AIC_ADP_AVRCP_ADV_PLAYSTAUTS_CHANGE:
            TRACE("APP:avrcp_play_status states=%x \n",(uint8_t)aic_avrcp_msg->avrcpparam); 
            break;
        default:
            break;
    }
}
#endif
