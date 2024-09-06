#include "tgt_cfg_bt.h"
#if APP_SUPPORT_HID == 1
#include "aic_adp_api.h"
#include "rtos.h"
#include "app_bt.h"

BOOL app_hid_key_handle(uint32_t key)
{
    BOOL ret = FALSE;

    switch(key){
        case APP_KEY_VOLSUB|APP_KEY_PRESS:
            break;
        case APP_KEY_VOLADD|APP_KEY_DOUBLE_CLICK:
            break;
        default:
            break;
    }
    return ret;
}

void app_hid_msg_handle(AIC_EVENT *event)
{
    AIC_ADP_HID_EVENT *aic_hid_msg = (AIC_ADP_HID_EVENT *)event->Param;

    TRACE("APP:app_hid_msg_handle\n");

    switch(event->EventId){
        case AIC_ADP_HID_CONNECTED:

        break;
        case AIC_ADP_HID_DISCONNECTED:

        break;
    }
}


#endif
