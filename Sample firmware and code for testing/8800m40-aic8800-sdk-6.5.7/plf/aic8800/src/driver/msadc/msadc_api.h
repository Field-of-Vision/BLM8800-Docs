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
#ifndef _MSADC_API_H_
#define _MSADC_API_H_

/**
 * Includes
 */
#include "reg_msadc.h"

/**
 * TypeDefs
 */
enum {
    MSADC_VOLT_VBAT         = 0,
    MSADC_VOLT_VIO          = 1,
    MSADC_VOLT_DCDC_VCORE   = 2,
};

enum {
    MSADC_TEMP_CHIP = 0,
    MSADC_TEMP_PA   = 1,
};

/**
 * Functions
 */

/**
 * @brief Measure voltages
 * &param vst   Voltage sense type
 * @return      Voltage value in mV
 */
int msadc_volt_measure(int vst);

/**
 * @brief Measure temperatures
 * &param tst   Temperature sense type
 * @return      Temperature degree value in C
 */
int msadc_temp_measure(int tst);

#endif /* _MSADC_API_H_ */
