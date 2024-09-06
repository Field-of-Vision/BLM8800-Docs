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
#include "trng_api.h"
#include "lp_ticker_api.h"
#include "us_ticker_api.h"
#include "dbg.h"

#ifdef CFG_RTOS
#include "rtos_al.h"
#endif /* CFG_RTOS */

#ifdef CFG_TEST_TRNG

/*
 * MACROS
 ****************************************************************************************
 */
#define GET_COUNT_MAX           8
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

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void trng_test(void)
{
    unsigned int data;

    UART_PRINT("\nTRNG test start\n");

#ifndef CFG_RTOS
    TIMER_INIT();
#endif /* !CFG_RTOS */
    trng_init();

    for (int i = 0; i < GET_COUNT_MAX; i++) {
        data = trng_get_word();
        UART_PRINT("get word %d: %08x\r\n", i, data);
    }

    UART_PRINT("\nTRNG test done\n");
    #ifdef CFG_RTOS
    rtos_task_wait_notification(-1);
    #endif /* CFG_RTOS */
}

#endif /* CFG_TEST_TRNG */
