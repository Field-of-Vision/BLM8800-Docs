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
#ifndef _FMACFW_API_H_
#define _FMACFW_API_H_

/**
 * Includes
 */
#include "co_int.h"

/**
 * Macros
 */
#define FMACFW_CFG_BASE_OFST  (0x00164)
#if defined(CFG_WIFI_RAM_VER)
#define FMACFW_CFG_BASE_ADDR  ((uint32_t)__fmacfw_rom_start__ + FMACFW_CFG_BASE_OFST)
#else
#define FMACFW_CFG_BASE_ADDR  (0x10000 + FMACFW_CFG_BASE_OFST)
#endif

/**
 * TypeDefs
 */

/**
 * Consts
 */
#if defined(CFG_WIFI_RAM_VER)
extern const uint32_t __fmacfw_rom_start__[];
#else
extern const uint32_t __rom_patch_mem_start__[];
#endif

/**
 * Functions
 */
#if defined(CFG_WIFI_RAM_VER) && !defined(CFG_FLASH_FW)
void fmacfw_iram_init(void);
#endif

uint32_t wifi_debug_mask_get(void);
void wifi_debug_mask_set(uint32_t dbg_msk);

#endif /* _FMACFW_API_H_ */
