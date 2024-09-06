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
#include "fmacfw_api.h"

#if defined(CFG_WIFI_RAM_VER) && !defined(CFG_FLASH_FW)

/**
 * Macros
 */

/**
 * Consts
 */
const uint32_t fmacfw_8800mc[] = {
    // TBD:
};

/**
 * Functions
 */
void fmacfw_iram_init(void)
{
    uint32_t *src = (uint32_t *)fmacfw_8800mc, *dst = (uint32_t *)__fmacfw_rom_start__;
    uint32_t idx;
    for (idx = 0; idx < sizeof(fmacfw_8800mc) / sizeof(uint32_t); idx++) {
        *dst = *src;
        dst++;
        src++;
    }
}
#endif
