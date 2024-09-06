/*
 * Copyright (C) 2018-2021 AICSemi Ltd.
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

#ifndef _HW_CFG_H_
#define _HW_CFG_H_
#include "plf.h"

/**
 * Pin PWRKEY pulled up always or not
 *  if always pulled up, power on the chip after VBAT valid
 *  if used as a key, long-press to power off the chip, short press to power on
 */
#define CONFIG_PWRKEY_PULLED_UP_ALWAYS  1

/**
 * System initial clock configure
 *  use values under CLK_CFG_MAX defined in sysctrl_api.h
 */
#define CONFIG_INITIAL_SYSTEM_CLOCK     CLK_CFG_S160P80PS320F80

/**
 * Low power clock selection
 *  Current support:
 *   1) LPCLK_SEL_RC_256K
 *   2) LPCLK_SEL_LPO_26M
 */
#define CONFIG_LPCLK_SELECT             LPCLK_SEL_LPO_26M

/**
 * Chip VIO selection
 *  Current support:
 *   1) VIO_SEL_1V8_LDO_AVDD18
 *   2) VIO_SEL_3V3_LDO_PA
 *   3) VIO_SEL_EXTERNAL
 */
#define CONFIG_VIO_SELECT               VIO_SEL_3V3_LDO_PA

/**
 * Chip VFLASH selection
 *  Current support:
 *   1) VFLASH_SEL_HIGH_VOLT
 *   2) VFLASH_SEL_LOW_VOLT
 */
#define CONFIG_VFLASH_SELECT            VFLASH_SEL_LOW_VOLT

/**
 * Chip VRF selection
 *  Current support:
 *   1) VRF_SEL_DCDC_MODE
 *   2) VRF_SEL_LDO_MODE
 */
#define CONFIG_VRF_SELECT               VRF_SEL_DCDC_MODE

/**
 * Low power voltage configure
 */
#define CONFIG_LP_PMIC_VCORE_DROP_ENABLE    0
#define CONFIG_LP_PMIC_VIO_SLP_PD_ENABLE    1

/**
 * USB dm volt calibration
 */
#define CONFIG_USB_DM_VOLT_CALIB_ENABLE     0

#endif /* _HW_CFG_H_ */
