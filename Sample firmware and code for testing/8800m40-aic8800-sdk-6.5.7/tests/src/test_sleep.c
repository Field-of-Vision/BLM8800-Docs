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
#include "sleep_api.h"
#include "lp_ticker_api.h"
#include "us_ticker_api.h"
#include "dbg.h"

#ifdef CFG_RTOS
#include "rtos_al.h"
#else
#error "RTOS must be selected"
#endif /* !CFG_RTOS */

#include "sysctrl_api.h"

#if PLF_PMIC
#include "pmic_api.h"
#if (PLF_AIC8800 && PLF_PMIC_VER_LITE)
#include "aic1000Lite_led_pwm.h"
#include "aic1000Lite_psm.h"
#endif
#endif

#ifdef CFG_TEST_SLEEP

/*
 * MACROS
 ****************************************************************************************
 */
#define TEST_CLK_GATE           1
#define TEST_DEEP_SLEEP         2
#define TEST_HIBERNATE          3
#define TEST_ULP_0              4
#define TEST_ULP_1              5
#define TEST_POWER_OFF          6

#define CURRENT_TEST_MODE       TEST_DEEP_SLEEP

#define DELAY_IN_MS             100//2//
#define USER_SLEEP_IN_MS        2000//5//
#define MAX_LOOP_CNT            0x3FFFF
#define USE_LP_TICKER           1

#define UART_PRINT              dbg
#if USE_LP_TICKER
#define TIMER_INIT()            do {} while (0)
#define TIMER_US_GET            lp_ticker_read
#else  /* USE_LP_TICKER */
#define TIMER_INIT              us_ticker_init
#define TIMER_US_GET            us_ticker_read
#endif /* USE_LP_TICKER */

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void sleep_test(void)
{
    UART_PRINT("\nSleep test start\n");

    #if (CURRENT_TEST_MODE == TEST_CLK_GATE)
    UART_PRINT("cg cpu_sys\n");
    sleep_level_set(PM_LEVEL_LIGHT_SLEEP);

    #elif (CURRENT_TEST_MODE == TEST_DEEP_SLEEP)
    UART_PRINT("pd cpu_sys\n");
    sleep_level_set(PM_LEVEL_DEEP_SLEEP);

    #elif (CURRENT_TEST_MODE == TEST_HIBERNATE)
    UART_PRINT("pd vcore\n");
    sleep_level_set(PM_LEVEL_HIBERNATE);

    #elif (CURRENT_TEST_MODE == TEST_ULP_0)
    UART_PRINT("pd vrtc\n");
    sleep_level_set(PM_LEVEL_ULP_0);

    #elif (CURRENT_TEST_MODE == TEST_ULP_1)
    UART_PRINT("pd dcdc_rf\n");
    sleep_level_set(PM_LEVEL_ULP_1);

    #elif (CURRENT_TEST_MODE == TEST_POWER_OFF)
    UART_PRINT("pwr off\n");
    sleep_level_set(PM_LEVEL_POWER_OFF);
    #endif /* TEST_CLK_GATE */

    #if (CURRENT_TEST_MODE <= TEST_ULP_1)
    user_sleep_wakesrc_set(WAKESRC_TIMER, 1, USER_SLEEP_IN_MS);
    #endif

    #if 0
    aonsysctrl_cpupra_set(0x176000);
    #endif

    TIMER_INIT();

    UART_PRINT("delay 1,now=%d,us=%d\n",rtos_now(false),TIMER_US_GET());
    uart_wait_tx_done();
    rtos_task_suspend(DELAY_IN_MS);

    UART_PRINT("usr allow,now=%d,us=%d\n",rtos_now(false),TIMER_US_GET());
    uart_wait_tx_done();
    user_sleep_allow(1);


#if !(PLF_AIC8800)
    while (1) {
#endif
#if (CURRENT_TEST_MODE == TEST_CLK_GATE)
    {
        uint32_t idx = 0;
        for (; idx < MAX_LOOP_CNT; idx++) {
            UART_PRINT("delay 2\n");
            rtos_task_suspend(DELAY_IN_MS);
            UART_PRINT("idx=%d,now=%d,us=%d\n",idx,rtos_now(false),TIMER_US_GET());
        }
    }
#else  /* (CURRENT_TEST_MODE == TEST_CLK_GATE) */
    UART_PRINT("delay 2\n");
    uart_wait_tx_done();
    rtos_task_suspend(DELAY_IN_MS);
    //rtos_task_suspend(4000);
#endif /* (CURRENT_TEST_MODE == TEST_CLK_GATE) */
#if !(PLF_AIC8800)
    }
#endif

    UART_PRINT("\nSleep test done\n");
    rtos_task_wait_notification(-1);
}

#endif /* CFG_TEST_SLEEP */
