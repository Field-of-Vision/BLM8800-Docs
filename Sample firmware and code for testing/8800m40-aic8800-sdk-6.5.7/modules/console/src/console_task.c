/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "console.h"
#include "command.h"
#include "stdio_uart.h"

#ifdef CFG_RTOS
#include "rtos.h"

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
/// Handle of the console task
static rtos_task_handle console_task_handle;
/// Indicates whether console task is suspended or not
static bool console_task_suspended;

/*
 * FUNCTIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Request the RTOS to suspend the console task.
 * This function will return only when the console task is resumed by the function @ref
 * console_task_resume
 ****************************************************************************************
 */
static void console_task_suspend(void)
{
    console_task_suspended = true;

    // wait for notification
    rtos_task_wait_notification(-1);
}

/**
 ****************************************************************************************
 * @brief Request the RTOS to resume the console task.
 * This function sends a msg to console_queue to realize the resume.
 * Note that currently this function is supposed to be called from interrupt.
 *
 * @param[in] isr Indicates if called from ISR
 ****************************************************************************************
 */
static void console_task_resume(bool isr)
{
    if (!console_task_suspended) {
        return;
    }
    console_task_suspended = false;

    // Notify the console task
    rtos_task_notify_setvalue(console_task_handle, 0, isr);
}

/**
 ****************************************************************************************
 * @brief console task implementation.
 ****************************************************************************************
 */
static RTOS_TASK_FCT(console_task_routine)
{
    for (;;) {
        console_schedule();

        if (console_buf_empty() == 1) {
            console_task_suspend();
        }
    }
}

int console_task_init(void)
{
    // Initialize console
    console_init();

    console_task_suspended = false;
    // Create the console task
    if (rtos_task_create(console_task_routine, "CONSOLE", CONSOLE_TASK,
                         TASK_STACK_SIZE_CONSOLE, NULL, TASK_PRIORITY_CONSOLE, &console_task_handle)) {
        return 1;
    }

    console_ntf_register(console_task_resume);

    return 0;
}

#endif
