/***
 * ble_task_msg.h
 */

#ifndef BLE_TASK_MSG_H
#define BLE_TASK_MSG_H

enum APP_BLE_HANDLER_REG_T {
    BLE_HANDLER_REG_0 = 0,
    BLE_HANDLER_REG_1,
    BLE_HANDLER_REG_MAX
};

typedef void (*APP_BLE_HANDLER)(void);

int app_ble_handler_register(enum APP_BLE_HANDLER_REG_T user, APP_BLE_HANDLER handler);
void ble_handler_reg_list_poll(void);
#endif /* BT_TASK_MSG_H */

