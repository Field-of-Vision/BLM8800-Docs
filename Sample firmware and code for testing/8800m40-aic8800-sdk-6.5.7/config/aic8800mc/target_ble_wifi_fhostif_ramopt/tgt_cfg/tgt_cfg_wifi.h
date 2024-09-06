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

#define FHOST_CONSOLE_LOW_POWER_CASE 1
#define FHOST_CONSOLE_MQTT_CASE      0

/**
 * Hostif mode selection, match with host driver
 *  Current support:
 *   1) HOST_VNET_MODE
 *   2) HOST_RAWDATA_MODE
 */
#define CONFIG_HOSTIF_MODE  HOST_VNET_MODE

/**
 * Hostif rx pkt filter mode
 *  Current support:
 *   1) VNET_FILTER_DIRECT
 *   2) VNET_FILTER_SHARED
 */
#define CONFIG_HOSTIF_FILTER_MODE VNET_FILTER_DIRECT

/**
 * Hostif total buf number
 */
#define CONFIG_HOSTIF_BUF_NUM_TOTAL         19

/**
 * Hostif rx buf number threshhold
 */
#define CONFIG_HOSTIF_RX_BUF_NUM_THRESHOLD  10

/**
 * WiFi RF optimization
 *  RF_OPT0: for anti-interference
 *  RF_OPT1: for long distance
 */
#define CONFIG_WIFI_RF_OPT0 0
#define CONFIG_WIFI_RF_OPT1 0

/**
 * WiFi TX adaptivity enabled or not
 */
#define CONFIG_WIFI_TX_ADAPTIVITY_ENABLE    0

/**
 * WiFi tx power level
 *  3-group at 2.4GHz: 11b/11ag, 11n/11ac, 11ax
 */
#define CONFIG_WIFI_TXPWR_LVL_ENABLE    1
#define CONFIG_WIFI_TXPWR_LVL_11B_11AG_2G4 \
    { 17,   17,   17,   17,   15,   15,   15,   15,   15,   15,   14,   14}
    //1M,   2M,   5M5,  11M,  6M,   9M,   12M,  18M,  24M,  36M,  48M,  54M
#define CONFIG_WIFI_TXPWR_LVL_11N_11AC_2G4 \
    { 15,   15,   15,   15,   15,   14,   14,   14,   13,   13}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9
#define CONFIG_WIFI_TXPWR_LVL_11AX_2G4 \
    { 15,   15,   15,   15,   15,   14,   14,   14,   13,   13,   13,   13}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9, MCS10,MCS11

/**
 * WiFi tx power offset
 *  3-group at 2.4GHz: chan1~4, chan5~9, chan10~13
 */
#define CONFIG_WIFI_TXPWR_OFST_ENABLE       0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_1_4     0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_5_9     0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_10_13   0

/**
 * WiFi tx power loss
 */
#define CONFIG_WIFI_TXPWR_LOSS_ENABLE       0
#define CONFIG_WIFI_TXPWR_LOSS_VALUE        2

/**
 * WiFi stack params
 *  CONFIG_WIFI_BCN_LINKLOSS_THD: beacon count threshold for linkloss detection
 *  CONFIG_WIFI_PS_KEEP_ALIVE_TIME_US: max tx time interval for keep alive in ps mode
 *  CONFIG_WIFI_ACTIVE_SCAN_TIME_US: active scan time period at a channel
 *  CONFIG_WIFI_PASSIVE_SCAN_TIME_US: passive scan time period at a channel
 *  CONFIG_WIFI_LP_WAKEUP_OFFSET_US: pre time offset before wcn wakeup
 *  CONFIG_WIFI_LOG_DEBUG_MASK: fw log debug mask
 */
#define CONFIG_WIFI_BCN_LINKLOSS_THD        100
#define CONFIG_WIFI_PS_KEEP_ALIVE_TIME_US   150000000
#define CONFIG_WIFI_ACTIVE_SCAN_TIME_US     30000
#define CONFIG_WIFI_PASSIVE_SCAN_TIME_US    110000
#define CONFIG_WIFI_LP_WAKEUP_OFFSET_US     2000
#define CONFIG_WIFI_LOG_DEBUG_MASK          0x8d08

#endif /* _TARGET_CONFIG_WIFI_H_ */