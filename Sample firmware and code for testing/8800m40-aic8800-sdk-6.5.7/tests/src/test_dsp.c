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
#include <stdbool.h>
#include "rtos.h"
#include "dsp_api.h"
#include "dsp_task.h"
#include "dbg.h"

#ifdef CFG_TEST_DSP

int16_t x_16bit[56];
int16_t y_16bit[56];

void dsp_test(void)
{
    TRACE("\ndsp test start\n");

    dsp_task_init();

    while (1) {
        struct dsp_msg_elt *msg;
        msg = dsp_a2e_msg_malloc();
        if (msg == NULL) {
            TRACE("msg malloc fail\n");
            TRACE("dsp test end\n");
            return;
        } else {
            TRACE("msg malloc success\n");
        }

        struct dsp_msg_smlald_56p param;
        param.a2e_data_len = 56 * sizeof(int16_t) * 2;
        param.e2a_data_len = sizeof(int64_t);
        dsp_a2e_msg_build(msg, DSP_MSG_SMLALD_56P, &param, sizeof(struct dsp_msg_smlald_56p));
        dsp_a2e_msg_send(msg);

        rtos_task_suspend(100);

        while (1) {
            struct dsp_data_elt *data;
            data = dsp_a2e_data_malloc(DSP_DATA_SMLALD_56P);
            if (data == NULL) {
                TRACE("data malloc fail\n");
            } else {
                TRACE("data malloc success\n");
                TRACE("data_ptr:%X\n", (uint32_t)data->data_ptr);
                uint16_t offset = 0;
                for (int i = 0; i < 56; i++) {
                    x_16bit[i] = 1;
                    y_16bit[i] = 1;
                }
                dsp_a2e_data_build(data, (uint8_t *)&x_16bit[0], offset, sizeof(x_16bit), false);
                offset += sizeof(x_16bit);
                dsp_a2e_data_build(data, (uint8_t *)&y_16bit[0], offset, sizeof(y_16bit), false);
                offset += sizeof(y_16bit);
                dsp_a2e_data_send(data);
            }

            rtos_task_suspend(1000);
        }
    }
}

#endif /* CFG_TEST_DSP */
