#include "tgt_cfg_bt.h"
#if APP_SUPPORT_HSP == 1 
#include "aic_adp_api.h"
#include "rtos.h"
#include "app_bt.h"

BOOL app_hsp_key_handle(uint32_t key)
{
    BOOL ret = FALSE;
    APP_DEVLIST * hfp_devinfo = NULL;

    hfp_devinfo = aic_adp_get_hsp_current_devinfo();
    if(hfp_devinfo == NULL){
        return ret;
    }

    switch(key){
        case APP_KEY_PLAY|APP_KEY_PRESS:
            
            break;
        case APP_KEY_VOLADD|APP_KEY_PRESS:
        case APP_KEY_VOLADD|APP_KEY_HOLD:
        case APP_KEY_VOLSUB|APP_KEY_PRESS:
        case APP_KEY_VOLSUB|APP_KEY_HOLD:

            break;
        case APP_KEY_PLAY|APP_KEY_DOUBLE_CLICK:
            break;
        case APP_KEY_PLAY|APP_KEY_HOLD:
            break;
        default:
            break;
    }
    return ret;
}


void app_hsp_msg_handle(AIC_EVENT *event)
{
    AIC_ADP_HFP_EVENT *aic_hfp_msg = (AIC_ADP_HFP_EVENT *)event->Param;

    TRACE("APP:app_hsp_msg_handle event = %d",event->EventId);

    switch(event->EventId)
    {
        case AIC_ADP_HSP_CONNECTED:
            if(aic_hfp_msg->hfpparam == 0){

            }
            break;
        case AIC_ADP_HSP_DISCONNECTED:
            if(aic_hfp_msg->hfpparam == 0){

            }else{

            }
            break;
        case AIC_ADP_HSP_AUDIO_CONNECTED:
            if(aic_hfp_msg->hfpparam == 0){

            }else{

            }
            break;
        case AIC_ADP_HSP_AUDIO_DISCONNECTED:
            if(aic_hfp_msg->hfpparam == 0){

            }else{

            }
            break;
        case AIC_ADP_HSP_AUDIO_DATA_SENT:

            break;
        case AIC_ADP_HSP_AUDIO_DATA_IND:
            {
                AIC_ADP_HFP_AUDIO_DATA *audiodata = (AIC_ADP_HFP_AUDIO_DATA *)aic_hfp_msg->hfpparam;
                //aic_adp_hfp_send_sco_data(Chan, &hf_sendbuff_ctrl.mempool[idx].packet);
            }
            break;
        case AIC_ADP_HSP_RING_IND:

            break;
        case AIC_ADP_HSP_SPEAKER_VOLUME:
            {
                U8 volume = (uint8_t)aic_hfp_msg->hfpparam;

            }
            break;

    }
}

#endif
