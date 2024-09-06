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
#ifndef _TESTMODE_API_H_
#define _TESTMODE_API_H_

/**
 * Includes
 */
#include "co_int.h"

/**
 * Macros
 */

/**
 * TypeDefs
 */

/**
 * Consts
 */

/**
 * Functions
 */
#if defined(CFG_WIFI_TESTMODE)
void testmode_iram_init(void);
#endif /* CFG_WIFI_TESTMODE */


#endif /* _TESTMODE_API_H_ */

