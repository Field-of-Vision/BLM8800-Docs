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
 * Pin PWRKEY as device mode PWREN
 */
#define CONFIG_PWRKEY_DEV_MODE_PWREN    1

/**
 * System initial clock configure
 *  use values under CLK_CFG_MAX defined in sysctrl_api.h
 */
#define CONFIG_INITIAL_SYSTEM_CLOCK     CLK_CFG_D240S240P120F60

/**
 * Chip VIO selection
 *  Current support:
 *   1) VIO_SEL_INTERNAL
 *   2) VIO_SEL_EXTERNAL
 */
#define CONFIG_VIO_SELECT               VIO_SEL_INTERNAL

/**
 * User defined low power configure
 */
#define CONFIG_LP_CLOCK_LPO_512K_ENABLE         PLF_LPO_512K
#define CONFIG_LP_PMIC_VCORE_DCDC_DROP_ENABLE   PLF_DCDC_CORE_DROP
#define CONFIG_LP_PMIC_VCORE_LDO_DROP_ENABLE    PLF_LDO_VCORE09_DROP
#define CONFIG_LP_PMIC_VRTC_LDO_DROP_ENABLE     PLF_LDO_VRTC09_DROP
#define CONFIG_LP_PMIC_VRF_DCDC_DROP_ENABLE     PLF_DCDC_RF_DROP
#define CONFIG_LP_PMIC_VIO_SLP_PD_ENABLE        1

#endif /* _HW_CFG_H_ */
