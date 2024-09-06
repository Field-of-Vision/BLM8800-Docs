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
#include <stdint.h>
#include <string.h>
#include "dsp_api.h"

#ifdef CFG_RTOS
#include "rtos.h"

static rtos_task_handle dsp_task_handle = NULL;
static bool dsp_task_inited = false;

static void dsp_task_suspend(void)
{
    // wait for notification
    rtos_task_wait_notification(-1);
}

static void dsp_task_resume(bool isr)
{
    // Notify the dsp task
    rtos_task_notify_setvalue(dsp_task_handle, 0, isr);
}

static RTOS_TASK_FCT(dsp_task_routine)
{
    for (;;) {
        dsp_task_suspend();

        dsp_schedule();
    }
}

int dsp_task_init(void)
{
    if (dsp_task_inited == true) {
        return 0;
    }

    dsp_init();

    dsp_ntf_register(dsp_task_resume);

    if (rtos_task_create(dsp_task_routine, "DSP", DSP_TASK,
                         TASK_STACK_SIZE_DSP, NULL, TASK_PRIORITY_DSP, &dsp_task_handle)) {
        return -1;
    }

    dsp_task_inited = true;

    return 0;
}
#endif
