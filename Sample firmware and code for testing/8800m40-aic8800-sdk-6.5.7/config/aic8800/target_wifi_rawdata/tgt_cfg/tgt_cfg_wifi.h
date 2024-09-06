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
 * WiFi RF configuration
 */
#define CONFIG_WIFI_RF_SWITCH_ENABLE        0

/**
 * WiFi TX adaptivity enabled or not
 */
#define CONFIG_WIFI_TX_ADAPTIVITY_ENABLE    0

/**
 * WiFi tx power index, 2 methods supported
 * 1) [TXPWR_IDX_ENABLE=1] Rate groups: dsss, lowrate/64qam/256qam/1024qam at 2.4GHz/5GHz
 * 2) [TXPWR_IDX_ENABLE=2] Every rate is controlled accurately
 *  3-group at 2.4GHz: 11b/11ag, 11n/11ac, 11ax
 *  3-group at 5GHz: 11ag, 11n/11ac, 11ax
 */
#define CONFIG_WIFI_TXPWR_IDX_ENABLE            2
// [TXPWR_IDX_ENABLE=1]
#define CONFIG_WIFI_TXPWR_IDX_DSSS              9
#define CONFIG_WIFI_TXPWR_IDX_OFDM_LOWRATE_2G4  8
#define CONFIG_WIFI_TXPWR_IDX_OFDM_64QAM_2G4    8
#define CONFIG_WIFI_TXPWR_IDX_OFDM_256QAM_2G4   8
#define CONFIG_WIFI_TXPWR_IDX_OFDM_1024QAM_2G4  8
#define CONFIG_WIFI_TXPWR_IDX_OFDM_LOWRATE_5G   10
#define CONFIG_WIFI_TXPWR_IDX_OFDM_64QAM_5G     9
#define CONFIG_WIFI_TXPWR_IDX_OFDM_256QAM_5G    9
#define CONFIG_WIFI_TXPWR_IDX_OFDM_1024QAM_5G   8
// [TXPWR_IDX_ENABLE=2]
#define CONFIG_WIFI_TXPWR_IDX_11B_11AG_2G4 \
    { 9,    9,    9,    9,    8,    8,    8,    8,    8,    8,    8,    8}
    //1M,   2M,   5M5,  11M,  6M,   9M,   12M,  18M,  24M,  36M,  48M,  54M
#define CONFIG_WIFI_TXPWR_IDX_11N_11AC_2G4 \
    { 8,    8,    8,    8,    8,    8,    8,    8,    8,    8}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9
#define CONFIG_WIFI_TXPWR_IDX_11AX_2G4 \
    { 8,    8,    8,    8,    8,    8,    8,    8,    8,    8,    8,    8}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9, MCS10,MCS11
#define CONFIG_WIFI_TXPWR_IDX_11AG_5G \
    { 10,   10,   10,   10,   10,   10,   9,    9}
    //6M,   9M,   12M,  18M,  24M,  36M,  48M,  54M
#define CONFIG_WIFI_TXPWR_IDX_11N_11AC_5G \
    { 10,   10,   10,   10,   10,   9,    9,    9,    9,    9}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9
#define CONFIG_WIFI_TXPWR_IDX_11AX_5G \
    { 10,   10,   10,   10,   10,   9,    9,    9,    9,    9,    8,    8}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9, MCS10,MCS11

/**
 * WiFi tx power offset
 *  3-group at 2.4GHz: chan1~4, chan5~9, chan10~13
 *  4-group at 5GHz: chan36~64, chan100~120, chan122~140, chan142~165
 */
#define CONFIG_WIFI_TXPWR_OFST_ENABLE       0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_1_4     0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_5_9     0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_10_13   0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_36_64   0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_100_120 0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_122_140 0
#define CONFIG_WIFI_TXPWR_OFST_CHAN_142_165 0

/**
 * WiFi stack params
 *  CONFIG_WIFI_BCN_LINKLOSS_THD: beacon count threshold for linkloss detection
 *  CONFIG_WIFI_PS_KEEP_ALIVE_TIME_US: max tx time interval for keep alive in ps mode
 *  CONFIG_WIFI_ACTIVE_SCAN_TIME_US: active scan time period at a channel
 *  CONFIG_WIFI_PASSIVE_SCAN_TIME_US: passive scan time period at a channel
 *  CONFIG_WIFI_LOG_DEBUG_MASK: fw log debug mask
 */
#define CONFIG_WIFI_BCN_LINKLOSS_THD        100
#define CONFIG_WIFI_PS_KEEP_ALIVE_TIME_US   150000000
#define CONFIG_WIFI_ACTIVE_SCAN_TIME_US     30000
#define CONFIG_WIFI_PASSIVE_SCAN_TIME_US    110000
#define CONFIG_WIFI_LOG_DEBUG_MASK          0x8d08

/**
 * WiFi country code string
 */
#define CONFIG_WIFI_COUNTRY_CODE            "00"

#endif /* _TARGET_CONFIG_WIFI_H_ */
