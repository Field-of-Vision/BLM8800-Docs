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
#ifndef _WDT_API_H_
#define _WDT_API_H_

/**
 * Includes
 */

/**
 * Macros
 */

/**
 * TypeDefs
 */
enum wdt_reboot_type {
    WDT_LOOP_FOREVER  = 0,
    WDT_CPUSYS_REBOOT = 1,
    WDT_PMIC_REBOOT   = 2,
};

/**
 * Functions
 */

void wdt_init(unsigned int seconds);
void wdt_kick(void);
void wdt_stop(void);
unsigned int wdt_get_pmic_reboot_delay(void);

#endif /* _WDT_API_H_ */
