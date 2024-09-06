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
#ifndef _RF_CONFIG_H_
#define _RF_CONFIG_H_

/**
 * Includes
 */
#include "reg_wlan_rf.h"
#include "reg_wcnaon.h"

/**
 * Functions
 */
extern int wifi_rf_config(void);
extern void rf_pll_recalib(void);

#endif /* _RF_CONFIG_H_ */
