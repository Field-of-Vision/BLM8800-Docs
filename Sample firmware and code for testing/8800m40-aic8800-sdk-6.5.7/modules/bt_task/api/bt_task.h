#ifndef _BTTASK_H_
#define _BTTASK_H_

#define BT_TASK_SUSPEND_VALUE_1  1
#define BT_TASK_SUSPEND_VALUE_2  2
#define BT_TASK_SUSPEND_VALUE_3  3

int bt_task_init(void);
void bt_task_resume(bool isr,uint32_t value);
uint32_t bt_task_suspend(void);
void bt_task_queue_notify(bool isr);
void bt_task_set_max_priority(void);
void bt_task_set_default_priority(void);

#endif

