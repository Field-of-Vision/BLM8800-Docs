/***
 * bt_task_msg.h
 */

#ifndef BT_TASK_MSG_H
#define BT_TASK_MSG_H

enum APP_BT_HANDLER_REG_T {
    HANDLER_REG_0 = 0,
    HANDLER_REG_1,
    HANDLER_REG_2,
    HANDLER_REG_3,
    HANDLER_REG_4,
    HANDLER_REG_5,
    HANDLER_REG_MAX
};

typedef void (*APP_BT_HANDLER)(void);


int app_bt_handler_register(enum APP_BT_HANDLER_REG_T user, APP_BT_HANDLER handler);
void handler_reg_list_poll(void);

#endif /* BT_TASK_MSG_H */

