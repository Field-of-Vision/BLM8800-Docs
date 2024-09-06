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

#ifndef _TARGET_CONFIG_WIFI_H_
#define _TARGET_CONFIG_WIFI_H_
#include "plf.h"

/**
 * Hostif mode selection, match with host driver
 *  Current support:
 *   1) HOST_WLAN_MODE
 *   2) HOST_VNET_MODE
 *   3) HOST_RAWDATA_MODE
 */
#define CONFIG_HOSTIF_MODE  HOST_WLAN_MODE

/**
 * Hostif total buf number
 */
#define CONFIG_HOSTIF_BUF_NUM_TOTAL         10

#endif /* _TARGET_CONFIG_WIFI_H_ */
