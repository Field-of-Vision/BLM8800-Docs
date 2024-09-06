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

#include "sysctrl_api.h"
#include "sleep_api.h"
#include <string.h>

#ifdef CFG_TEST_GPIO_IRQ

/*
 * MACROS
 ****************************************************************************************
 */
#define GPIO_INDEX              12
#define GPIO_INDEX_1            13
#define GPIOB_INDEX             2
#define DELAY_IN_MS             200
#define MAX_LOOP_CNT            8
#define USE_LP_TICKER           0
#define HIB_SLEEP_EN            (0 && (PLF_AIC8800) && defined(CFG_RTOS))
#define DEEP_SLEEP_EN           (0 && (PLF_AIC8800MC || PLF_AIC8800M40) && defined(CFG_RTOS))

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
int app_gpio_cnt = 0;
#if HIB_SLEEP_EN
uint32_t rtos_ticks[2] = {0,}; // [0]: last tick, [1]: curr_tick
PRIVATE_HOST_DECLARE(G3USER, int, app_gpio_cnt);
PRIVATE_HOST_ARRAY_DECLARE(G3USER, int, 2, rtos_ticks);
#endif

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

void gpio_irq_test_handler(int event)
{
    if (GPIOIRQ_CB_EVENT(event) == GPIOIRQ_EVENT_EDGE_RISE) {
        dbg("gpio_irq_test_handler\n");
    }
}

void gpiob_irq_test_handler(int event)
{
    if (GPIOIRQ_CB_EVENT(event) == GPIOIRQ_EVENT_EDGE_BOTH) {
        #if (HIB_SLEEP_EN || DEEP_SLEEP_EN)
        user_sleep_allow(0);
        #endif
        dbg("GPIOB irq_test_handler\n");
    } else {
        dbg("irq event: %x\n", event);
    }
}

#if HIB_SLEEP_EN
/**
 * Save user data
 */
void user_data_save(void)
{
    backup_app_gpio_cnt = app_gpio_cnt;
    memcpy(&backup_rtos_ticks[0], &rtos_ticks[0], sizeof(rtos_ticks));
}

/**
 * Restore user data
 */
void user_data_restore(void)
{
    app_gpio_cnt = backup_app_gpio_cnt;
    memcpy(&rtos_ticks[0], &backup_rtos_ticks[0], sizeof(rtos_ticks));
}
#endif

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void gpio_irq_test(void)
{
    UART_PRINT("\nGPIO irq test start\n");

    /* Set iomux & direction */
    gpioa_init(GPIO_INDEX);
    gpioa_dir_out(GPIO_INDEX);

    gpioa_irq_init(GPIO_INDEX_1, GPIOIRQ_TYPE_EDGE_RISE, gpio_irq_test_handler);
    #if (PLF_AIC8800)
    gpiob_irq_init(GPIOB_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpiob_irq_test_handler,0);
    #elif (PLF_AIC8800MC || PLF_AIC8800M40)
    gpiob_irq_init(GPIOB_INDEX, GPIOIRQ_TYPE_EDGE_BOTH, gpiob_irq_test_handler);
    #endif

    #if HIB_SLEEP_EN
    // gpiob as wake src
    gpiob_force_pull_dn_enable(GPIOB_INDEX);
    pmic_clock_set_for_gpiob();
    if (sleep_level_get() < PM_LEVEL_DEEP_SLEEP) {
        user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, 0);
        sleep_level_set(PM_LEVEL_HIBERNATE);
        user_sleep_allow(1);
    } else {
        uint32_t irq_hist = gpiob_irq_history_get();
        if (irq_hist & (0x01UL << GPIOB_INDEX)) {
            gpiob_irq_history_clear(irq_hist);
            user_sleep_allow(0);
            dbg("hist=0x%x\n",irq_hist);
        }
    }
    #endif
    #if (DEEP_SLEEP_EN)
    // gpiob as wake src
    gpiob_force_pull_dn_enable(GPIOB_INDEX);
    if (sleep_level_get() < PM_LEVEL_DEEP_SLEEP) {
        user_sleep_wakesrc_set(WAKESRC_GPIOB, 1, WAKEGPIO_ARG(WAKEGPIO_MUX_0, 2));
        sleep_level_set(PM_LEVEL_DEEP_SLEEP);
        user_sleep_allow(1);
    }
    #endif

#ifndef CFG_RTOS
    TIMER_INIT();
#endif /* !CFG_RTOS */

    for (;;) {
        if (app_gpio_cnt & 0x01) {
            gpioa_set(GPIO_INDEX);
        } else {
            gpioa_clr(GPIO_INDEX);
        }
        #ifdef CFG_RTOS
        uint32_t cur_tick = rtos_now(false);
        UART_PRINT("i=%d,systick=%d\n",app_gpio_cnt,cur_tick);
        #if HIB_SLEEP_EN
        rtos_ticks[0] = rtos_ticks[1];
        rtos_ticks[1] = cur_tick;
        UART_PRINT("rtos_ticks=%d,%d\n", rtos_ticks[0], rtos_ticks[1]);
        //uart_wait_tx_done();
        #endif
        #endif /* CFG_RTOS */
        app_gpio_cnt++;
        if (app_gpio_cnt >= MAX_LOOP_CNT) {
            break;
        }
#ifdef CFG_RTOS
        rtos_task_suspend(DELAY_IN_MS);
#else  /* CFG_RTOS */
        simple_delay_ms(DELAY_IN_MS);
#endif /* CFG_RTOS */
    }

    #if (DEEP_SLEEP_EN)
    while (1) {
        UART_PRINT("delay 5\n");
        rtos_task_suspend(5000);
    }
    #endif

    UART_PRINT("\nGPIO irq test done\n");
    #ifdef CFG_RTOS
    rtos_task_wait_notification(-1);
    #endif /* CFG_RTOS */
}

#endif /* CFG_TEST_GPIO_IRQ */
