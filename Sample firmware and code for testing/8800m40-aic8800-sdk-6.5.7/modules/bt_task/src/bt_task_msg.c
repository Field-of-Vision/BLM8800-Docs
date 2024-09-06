#include "bt_task_msg.h"
#include "aic_adp_api.h"
#if PLF_BLE_STACK
#include "aicble.h"
#endif

#include "app_bt.h"

APP_BT_HANDLER handler_register_list[HANDLER_REG_MAX] = {0};

int app_bt_handler_register(enum APP_BT_HANDLER_REG_T user, APP_BT_HANDLER handler)
{
    handler_register_list[user]= handler;
    return 0;
}

void handler_reg_list_poll(void)
{
    uint8_t i;
    for (i=0; i<HANDLER_REG_MAX; i++){
        if (handler_register_list[i]){
            handler_register_list[i]();
        }
    }
}

