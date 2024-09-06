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
#include "gpio_api.h"
#include "lp_ticker_api.h"
#include "us_ticker_api.h"
#include "dbg.h"

#ifdef CFG_RTOS
#include "rtos_al.h"
#endif /* CFG_RTOS */

#ifdef CFG_TEST_GPIO

/*
 * MACROS
 ****************************************************************************************
 */
#define GPIO_INDEX              12
#define DELAY_IN_MS             100
#define MAX_LOOP_CNT            0xFFFF
#define USE_LP_TICKER           0

#define UART_PRINT              dbg
#if USE_LP_TICKER
#define TIMER_INIT              lp_ticker_init
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
#ifndef CFG_RTOS
void simple_delay_ms(uint32_t delay)
{
    uint32_t delta_us = delay * 1000;
    uint32_t previous_us = TIMER_US_GET();
    while ((TIMER_US_GET() - previous_us) < delta_us);
}
#endif /* !CFG_RTOS */

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void gpio_test(void)
{
    int i = 0;
    UART_PRINT("\nGPIO test start\n");

    /* Set iomux & direction */
    gpioa_init(GPIO_INDEX);
    gpioa_dir_out(GPIO_INDEX);
#ifndef CFG_RTOS
    TIMER_INIT();
#endif /* !CFG_RTOS */

    for (;;) {
        if (i & 0x01) {
            gpioa_set(GPIO_INDEX);
        } else {
            gpioa_clr(GPIO_INDEX);
        }
#ifdef CFG_RTOS
        rtos_task_suspend(DELAY_IN_MS);
#else  /* CFG_RTOS */
        simple_delay_ms(DELAY_IN_MS);
#endif /* CFG_RTOS */
        UART_PRINT("i=%d\n",i);
        if (i++ > MAX_LOOP_CNT) {
            break;
        }
    }

    UART_PRINT("\nGPIO test done\n");
}

#endif /* CFG_TEST_GPIO */
