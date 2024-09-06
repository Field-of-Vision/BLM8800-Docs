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
#ifndef _TEMP_COMP_H_
#define _TEMP_COMP_H_

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
typedef struct {
    TimerHandle_t tmr_hdl;
    int8_t degree_calib;
    int8_t degree_boot;
    int8_t degree_last;
} temp_comp_env_t;

/**
 * Functions
 */

/**
 * @brief       Init temp comp process
 */
void temp_comp_init(void);

/**
 * @brief       Deinit temp comp process
 */
void temp_comp_deinit(void);

/**
 * @brief       Start temp comp timer
 */
void temp_comp_start(void);

/**
 * @brief       Stop temp comp timer
 */
void temp_comp_stop(void);

#endif /* _TEMP_COMP_H_ */
