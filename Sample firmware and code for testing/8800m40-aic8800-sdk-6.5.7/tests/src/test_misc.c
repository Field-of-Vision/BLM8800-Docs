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
#include "pmic_api.h"
#include "console.h"

#ifdef CFG_RTOS
#include "rtos_al.h"
#endif /* CFG_RTOS */

#ifdef CFG_TEST_MISC

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

int do_reboot(int argc, char * const argv[])
{
    UART_PRINT("Chip reboot...\n");
    pmic_chip_reboot(0xF);
    return 0;
}

int do_bor(int argc, char * const argv[])
{
    int ret = 0;
    if (argc > 2) {
        unsigned int vbit = console_cmd_strtoul(argv[1], NULL, 16);
        unsigned int repow = console_cmd_strtoul(argv[2], NULL, 10);
        pmic_bor_config(vbit, repow);
        UART_PRINT("Set BOR vbit:0x%x, repow:%x\n", vbit, repow);
    } else {
        UART_PRINT("Wrong args\n");
        ret = -1;
    }
    return ret;
}

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void misc_test(void)
{
    UART_PRINT("\nMisc test start\n");

    console_cmd_add("reboot",   "Software Reboot",                  1, 1, do_reboot);
    console_cmd_add("bor",      " vbit repow\t- Set BOR Params",    3, 3, do_bor);

    UART_PRINT("\nMisc test done\n");
}

#endif /* CFG_TEST_MISC */
