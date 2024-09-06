#ifndef _BLETASK_H_
#define _BLETASK_H_

#define BT_TASK_SUSPEND_VALUE_1  1
#define BT_TASK_SUSPEND_VALUE_2  2
#define BT_TASK_SUSPEND_VALUE_3  3

enum BleTaskInitMode {
    INIT_NORMAL,
    INIT_CONSOLE,
};
void ble_task_set_need_pon(bool need_pon);
int ble_task_init(enum BleTaskInitMode init_mode);
int ble_task_deinit(void);
int ble_task_delete(void);

void ble_task_resume(bool isr,uint32_t value);
uint32_t ble_task_suspend(void);
void ble_task_queue_notify(bool isr);
void ble_task_set_max_priority(void);
void ble_task_set_default_priority(void);
#if PLF_AIC8800
void ble_task_save(void);
void ble_task_restore(void);
#endif /* PLF_AIC8800 */
#endif

