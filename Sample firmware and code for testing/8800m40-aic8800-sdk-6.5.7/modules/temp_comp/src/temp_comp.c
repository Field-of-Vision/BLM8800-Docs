/*
 * Copyright (C) 2018-2023 AICSemi Ltd.
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

/**
 * Includes
 */
#include "rtos_al.h"
#include "rtos.h"
#include "dbg.h"
#include "temp_comp.h"
#include "msadc_api.h"
#include "rf_config.h"
#include "rwnx_msg_tx.h"
#include "co_math.h"

/**
 * Macros
 */
// temperature compensation timer period in second
#ifndef TEMP_COMP_TIMER_PERIOD_SEC
#define TEMP_COMP_TIMER_PERIOD_SEC      30
#endif
#define TEMP_COMP_DBG_PRINT(fmt, ...)   do {} while(0)//dbg(fmt, ##__VA_ARGS__)//

/**
 * TypeDefs
 */

/**
 * Variables
 */
temp_comp_env_t temp_comp_env = {
    #if (PLF_AIC8800)
    .degree_calib = 35,
    #else
    NULL,
    #endif
};

/**
 * Functions
 */
static int temp_comp_check(int8_t degree)
{
    int ret = 0;
    if (co_abs(degree - temp_comp_env.degree_last) >= 8) {
        temp_comp_env.degree_last = degree;
        ret = 1;
    }
    return ret;
}

static void temp_comp_process(int8_t degree)
{
    TEMP_COMP_DBG_PRINT("pll recalib\n");
    rf_pll_recalib();
    #if (PLF_AIC8800 && PLF_WIFI_STACK && defined(CONFIG_RWNX_LWIP))
    {
        rwnx_txpwr_comp_t txpwr_comp;
        int8_t txpwr_idx_comp_5g;
        if (degree >= temp_comp_env.degree_calib) {
            txpwr_idx_comp_5g = (degree - temp_comp_env.degree_calib) >> 4;
            if (txpwr_idx_comp_5g > 1) {
                txpwr_idx_comp_5g = 1;
            }
        } else {
            txpwr_idx_comp_5g = ((temp_comp_env.degree_calib - degree) >> 4) * -1;
        }
        txpwr_comp.pwridx_comp_5g = txpwr_idx_comp_5g;
        rwnx_set_txpwr_comp_8800(&txpwr_comp);
    }
    #endif
}
void temp_comp_timer_handler(void const *param)
{
    int degree_curr;
    degree_curr = msadc_temp_measure(MSADC_TEMP_CHIP);
    TEMP_COMP_DBG_PRINT("t=%d C\n", degree_curr);
    if (temp_comp_check(degree_curr)) {
        temp_comp_process(degree_curr);
    }
}

void temp_comp_init(void)
{
    if (temp_comp_env.tmr_hdl == NULL) {
        TimerHandle_t temp_timer = rtos_timer_create("temp_timer", TEMP_COMP_TIMER_PERIOD_SEC*1000, pdTRUE, NULL,
                                                    (TimerCallbackFunction_t)temp_comp_timer_handler);
        if (!temp_timer) {
            dbg("temp_timer create fail\n");
            return;
        }
        temp_comp_env.tmr_hdl = temp_timer;
        temp_comp_env.degree_last = temp_comp_env.degree_boot = msadc_temp_measure(MSADC_TEMP_CHIP);
        TEMP_COMP_DBG_PRINT("degree_boot=%d\n", temp_comp_env.degree_boot);
    } else {
        dbg("temp_comp already inited\n");
    }
}

void temp_comp_deinit(void)
{
    if (temp_comp_env.tmr_hdl) {
        int ret = rtos_timer_delete(temp_comp_env.tmr_hdl, 0);
        if (ret) {
            dbg("temp_timer delete fail, ret=%d\n", ret);
        } else {
            temp_comp_env.tmr_hdl = NULL;
        }
    }
}

void temp_comp_start(void)
{
    if (temp_comp_env.tmr_hdl) {
        int ret = rtos_timer_start(temp_comp_env.tmr_hdl, 0, false);
        if (ret) {
            dbg("temp_timer start fail, ret=%d\n", ret);
        }
    }
}

void temp_comp_stop(void)
{
    if (temp_comp_env.tmr_hdl) {
        int ret = rtos_timer_stop(temp_comp_env.tmr_hdl, 0);
        if (ret) {
            dbg("temp_timer start fail, ret=%d\n", ret);
        }
    }
}
