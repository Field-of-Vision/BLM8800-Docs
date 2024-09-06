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
#include "wdt_api.h"
#include "lp_ticker_api.h"
#include "us_ticker_api.h"
#include "dbg.h"
#if (PLF_PMIC)
#include "pmic_api.h"
#endif

#ifdef CFG_RTOS
#include "rtos_al.h"
#endif /* CFG_RTOS */

#if (PLF_MODULE_SOFTWDG)
#include "softwdg.h"
#endif

#ifdef CFG_TEST_WDT

/*
 * MACROS
 ****************************************************************************************
 */
#define DELAY_IN_MS             5000
#define USE_LP_TICKER           0
#define TEST_SOFTWDG_EN         (defined(CFG_RTOS) && PLF_MODULE_SOFTWDG && 0)

#define UART_PRINT              dbg
#if USE_LP_TICKER
#define TIMER_INIT              do {} while (0) //lp_ticker_init called in SystemInit
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

#if (TEST_SOFTWDG_EN)
void my_softwdg_cb(void)
{
    UART_PRINT("cb: TIMEOUT!!!\n");
    #if (PLF_PMIC)
    pmic_chip_reboot(wdt_get_pmic_reboot_delay());
    #endif
}
#endif

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void wdt_test(void)
{
    unsigned int i = 0;
    #if (TEST_SOFTWDG_EN)
    int ret;
    softwdg_node_t *node;
    #endif

    UART_PRINT("\nWDT test start\n");

    #if (TEST_SOFTWDG_EN)
    node = (softwdg_node_t *)rtos_malloc(sizeof(softwdg_node_t));
    if (node == NULL) {
        UART_PRINT("alloc fail\n");
        return;
    }
    node->name = "TEST_WDT";
    node->cnt = 0;
    node->max = 16;
    node->cb = my_softwdg_cb;
    ret = softwdg_register(node);
    if (ret) {
        UART_PRINT("fail to register softwdg, ret=%d\n", ret);
        return;
    }
    i = 1;
    for (;;) {
        rtos_task_suspend(SOFTWDG_TUCNT2MS(i));
        softwdg_kick(node);
        UART_PRINT("kick softwdg, tu cnt=%d\n", i);
        i = i * 2;
    }
    rtos_free(node);
    node = NULL;
    #else
    #ifndef CFG_RTOS
    TIMER_INIT();
    #endif /* !CFG_RTOS */
    wdt_init(1);

    for (;;) {
        #ifdef CFG_RTOS
        rtos_task_suspend(DELAY_IN_MS);
        #else  /* CFG_RTOS */
        simple_delay_ms(DELAY_IN_MS);
        #endif /* CFG_RTOS */
        wdt_kick();
        UART_PRINT("Counter: %08x\n", i++);
    }
    #endif

    UART_PRINT("\nWDT test done\n");
}

#endif /* CFG_TEST_WDT */
