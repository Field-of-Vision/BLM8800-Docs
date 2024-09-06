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
#include <string.h>
#include "dbg.h"
#include "system.h"
#include "sysctrl_api.h"

#ifdef CFG_RTOS
#include "rtos_al.h"
#endif /* CFG_RTOS */

#ifdef CFG_TEST_CLKSW

/*
 * MACROS
 ****************************************************************************************
 */
#define UART_PRINT              dbg

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */


/*
 * FUNCTIONS
 ****************************************************************************************
 */
void print_clk_info(void)
{
    #if (PLF_AIC8800)
    UART_PRINT("F:%dM,H:%dM,P:%dM,FL:%dM\n",
               DSPSysCoreClock/1000000,SystemCoreClock/1000000,PeripheralClock/1000000,sysctrl_clock_get(PER_FLASH)/1000000);
    #elif (PLF_AIC8800MC)
    UART_PRINT("H:%dM,P:%dM,PSR:%dM,FL:%dM\n",
               SystemCoreClock/1000000,PeripheralClock/1000000,FlashMem2XClock/1000000,sysctrl_clock_get(PER_FLASH)/1000000);
    #endif
}

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void clksw_test(void)
{
    int idx;

    UART_PRINT("\nClkSw test start\n");

    print_clk_info();
#ifdef CFG_RTOS
    rtos_task_suspend(2);
#endif /* CFG_RTOS */

    for (idx = 0; idx < CLK_CFG_MAX; idx++) {
        UART_PRINT("cfg clk: %d\n", idx);
        // change clock
        sysctrl_clock_cfg(idx);
        SystemCoreClockUpdate();
        print_clk_info();
#ifdef CFG_RTOS
        rtos_task_suspend(2);
#endif /* CFG_RTOS */
    }

    UART_PRINT("\nClkSw test done\n");
}

#endif /* CFG_TEST_CLKSW */
