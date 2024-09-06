#include "rtos.h"
#include "ble_task_msg.h"
#include "ble_task.h"
#include "aic_ble_adp_api.h"
#include "app_ble_only.h"


APP_BLE_HANDLER ble_handler_register_list[BLE_HANDLER_REG_MAX] = {0};

int app_ble_handler_register(enum APP_BLE_HANDLER_REG_T user, APP_BLE_HANDLER handler)
{
    ble_handler_register_list[user]= handler;
    return 0;
}

void ble_handler_reg_list_poll(void)
{
    uint8_t i;
    for (i=0; i<BLE_HANDLER_REG_MAX; i++){
        if (ble_handler_register_list[i]){
            ble_handler_register_list[i]();
        }
    }
}
