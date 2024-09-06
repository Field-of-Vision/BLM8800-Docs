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

#ifndef _TARGET_CONFIG_H_
#define _TARGET_CONFIG_H_
#include "plf.h"
// General paramter configuration
#if PLF_BLE_WAKEUP
#define FPGA                            1
#else
#define FPGA                            0
#endif
#define PXP                             0
//end

//bt use ble vendor api
#define BLE_VENDOR_SUPPORT              0

// tws ble adv or scan open/close
#if PLF_BLE_STACK
#define TWS_BLE_CONNECT                 0
#else
#define TWS_BLE_CONNECT                 1
#endif
//end

// macro for test case, user don't change it
#define SCO_LOOPBACK_TEST               0
#define MAX_THROUGHPUT_TEST             0
#define SCO_CVSD_PLC_TEST               0
#define TWS_MSS_AUTO_TEST               0
//end
/* TEST_MODE_ROLE_SEND
    ble=off    1 : link connect initiator                              role is MASTER ,without roleswitch
               0 : page/inquiry scan and waiting                       role is SLAVE  ,without roleswitch
    ble=on     1 : adv initiator  ,page/inquiry scan and waiting       role is SLAVE  ,without roleswitch
               0 : ble scan       ,link connect initiator              role is MASTER ,without roleswitch
*/
#define TEST_MODE_ROLE_SEND             0
#if PLF_AON_SUPPORT
#define AON_SUPPORT                     1
#else
#define AON_SUPPORT                     0
#endif

/*
 * set sleep level for BT/BLE
 * 0: sys_sleep_level = PM_LEVEL_ACTIVE           bt_lp_level = BT_LP_LEVEL_ACTIVE
 * 1: sys_sleep_level = PM_LEVEL_LIGHT_SLEEP      bt_lp_level = BT_LP_LEVEL_CLOCK_GATE2
 * 2: sys_sleep_level = PM_LEVEL_DEEP_SLEEP       bt_lp_level = BT_LP_LEVEL_POWER_OFF3
 * 3: sys_sleep_level = PM_LEVEL_HIBERNATE        bt_lp_level = BT_LP_LEVEL_HIBERNATE
*/
#define APP_SLEEP_LEVEL                 0

// General BT paramter configuration
#if PLF_BT_STACK == 1
#define APP_SUPPORT_DEEPSLEEP

#if defined(CFG_TWS_ROLE_MASTER)
    #undef TEST_MODE_ROLE_SEND
    #if TWS_BLE_CONNECT == 0
    #define TEST_MODE_ROLE_SEND             1//master
    #else
    #define TEST_MODE_ROLE_SEND             0//master
    #endif
    #define APP_SUPPORT_TWS                 1
    #define APP_SUPPORT_MULTIPLE_PHONE      0//if APP_SUPPORT_MULTIPLE_PHONE == 1 ,APP_SUPPORT_TWS = 0 .if APP_SUPPORT_TWS == 1,APP_SUPPORT_MULTIPLE_PHONE = 0
    #define APP_SUPPORT_LINK_ONE_ONLY       0
#elif defined(CFG_TWS_ROLE_SLAVE)
    #undef TEST_MODE_ROLE_SEND
    #if TWS_BLE_CONNECT == 0
    #define TEST_MODE_ROLE_SEND             0//slave
    #else
    #define TEST_MODE_ROLE_SEND             1//slave
    #endif
    #define APP_SUPPORT_TWS                 1
    #define APP_SUPPORT_MULTIPLE_PHONE      0//if APP_SUPPORT_MULTIPLE_PHONE == 1 ,APP_SUPPORT_TWS = 0 .if APP_SUPPORT_TWS == 1,APP_SUPPORT_MULTIPLE_PHONE = 0
    #define APP_SUPPORT_LINK_ONE_ONLY       0
#else
    #undef TEST_MODE_ROLE_SEND
    #define TEST_MODE_ROLE_SEND             0//slave
    #if PLF_AIC_VENDOR_ADV
    #undef TWS_BLE_CONNECT
    #undef BLE_VENDOR_SUPPORT
    #define BLE_VENDOR_SUPPORT              1//AIC VENDOR CONNECTION is support
    #define TWS_BLE_CONNECT                 1
    #endif
    #define APP_SUPPORT_TWS                 0
    #define APP_SUPPORT_MULTIPLE_PHONE      1//if APP_SUPPORT_MULTIPLE_PHONE == 1 ,APP_SUPPORT_TWS = 0 .if APP_SUPPORT_TWS == 1,APP_SUPPORT_MULTIPLE_PHONE = 0
    #if defined(CFG_LINK_ONE)
    #define APP_SUPPORT_LINK_ONE_ONLY       1//Used for test or Only one connected application scenario is required
    #else
    #define APP_SUPPORT_LINK_ONE_ONLY       0
    #endif
#endif

#if APP_SUPPORT_TWS == 1
    #define APP_SUPPORT_AES                 0
    #define APP_SUPPORT_TWS_LOCAL_VOL_SYNC  0
    #ifdef CFG_TWS_PLUS
    #define APP_SUPPORT_TWS_PLUS            1
    #else
    #define APP_SUPPORT_TWS_PLUS            0
    #endif
#else
    #define APP_SUPPORT_AES                 1
    #define APP_SUPPORT_TWS_LOCAL_VOL_SYNC  0
    #define APP_SUPPORT_TWS_PLUS            0
#endif

//BT profile configuration
#define APP_SUPPORT_A2DP_SBC            1
#ifdef A2DP_AAC_ENABLE
#define APP_SUPPORT_A2DP_AAC            1
#else
#define APP_SUPPORT_A2DP_AAC            0
#endif
#ifdef CFG_A2DP_SOURCE_SUPPORT
#define APP_SUPPORT_A2DP_SOURCE         1
#undef APP_SUPPORT_MULTIPLE_PHONE
#define APP_SUPPORT_MULTIPLE_PHONE      0
#else
#define APP_SUPPORT_A2DP_SOURCE         0
#endif
#define APP_SUPPORT_A2DP_CP             0
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1 || APP_SUPPORT_A2DP_SOURCE == 1
#define APP_SUPPORT_AVRCP               1
#else
#define APP_SUPPORT_AVRCP               0
#endif
#define APP_SUPPORT_HFP                 1
#define APP_SUPPORT_HSP                 0
#define APP_SUPPORT_HID                 0
#if APP_SUPPORT_HFP==1
#define APP_SUPPORT_NUMBER_VOICE        1
#define APP_SUPPORT_BTBATTERY           1
#define APP_SUPPORT_NREC_OFF            0
#define HFP_1_6_ENABLE
#else
#define APP_SUPPORT_NUMBER_VOICE        0
#define APP_SUPPORT_BTBATTERY           0
#define APP_SUPPORT_NREC_OFF            0
#endif
#if APP_SUPPORT_AVRCP == 1
#define APP_SUPPORT_IPHONE_VOLUME_SYNC  1
#else
#define APP_SUPPORT_IPHONE_VOLUME_SYNC  0
#endif
#if SCO_CVSD_PLC_TEST == 1 || MAX_THROUGHPUT_TEST == 1 || APP_SUPPORT_TWS_PLUS == 1
#define APP_SUPPORT_SPP                 1
#else
#define APP_SUPPORT_SPP                 0
#endif



#else
#define APP_SUPPORT_TWS                 0
#define APP_SUPPORT_MULTIPLE_PHONE      0
#define APP_SUPPORT_A2DP_SBC            0
#define APP_SUPPORT_A2DP_AAC            0
#define APP_SUPPORT_A2DP_SOURCE         0
#define APP_SUPPORT_A2DP_CP             0
#define APP_SUPPORT_AVRCP               0
#define APP_SUPPORT_HFP                 0
#define APP_SUPPORT_HSP                 0
#define APP_SUPPORT_HID                 0
#define APP_SUPPORT_BLE                 0
#define APP_SUPPORT_SPP                 0
#endif

#if PLF_HFG_SUPPORT
#undef APP_SUPPORT_HFP
#undef APP_SUPPORT_NUMBER_VOICE
#undef APP_SUPPORT_BTBATTERY
#undef APP_SUPPORT_NREC_OFF
#undef TWS_BLE_CONNECT
#define APP_SUPPORT_HFP                 1
#define APP_SUPPORT_NUMBER_VOICE        0
#define APP_SUPPORT_BTBATTERY           0
#define APP_SUPPORT_NREC_OFF            0
#define TWS_BLE_CONNECT                 0

#define APP_SUPPORT_HFG                 1
#else
#define APP_SUPPORT_HFG                 0
#endif

#ifdef CFG_A2DP_NOT_SUPPORT
#undef APP_SUPPORT_A2DP_SBC
#undef APP_SUPPORT_A2DP_AAC
#undef APP_SUPPORT_A2DP_SOURCE
#undef APP_SUPPORT_AVRCP
#define APP_SUPPORT_A2DP_SBC            0
#define APP_SUPPORT_A2DP_AAC            0
#define APP_SUPPORT_A2DP_SOURCE         0
#define APP_SUPPORT_AVRCP               0
#endif

#ifdef CFG_BT_OTA_BOX
#define APP_SUPPORT_OTA_BOX             1
#undef TEST_MODE_ROLE_SEND
#undef APP_SUPPORT_AES
#define TEST_MODE_ROLE_SEND             1
#define APP_SUPPORT_AES                 0
#else
#define APP_SUPPORT_OTA_BOX             0
#endif

#if (PLF_BLE_STACK && PLF_BTDM == 0) || APP_SUPPORT_OTA_BOX
#undef APP_SUPPORT_TWS
#define APP_SUPPORT_TWS                 0
#undef APP_SUPPORT_MULTIPLE_PHONE
#define APP_SUPPORT_MULTIPLE_PHONE      0
#undef APP_SUPPORT_A2DP_SBC
#define APP_SUPPORT_A2DP_SBC            0
#undef APP_SUPPORT_A2DP_AAC
#define APP_SUPPORT_A2DP_AAC            0
#undef APP_SUPPORT_A2DP_SOURCE
#define APP_SUPPORT_A2DP_SOURCE         0
#undef APP_SUPPORT_A2DP_CP
#define APP_SUPPORT_A2DP_CP             0
#undef APP_SUPPORT_AVRCP
#define APP_SUPPORT_AVRCP               0
#undef APP_SUPPORT_HFP
#define APP_SUPPORT_HFP                 0
#undef APP_SUPPORT_HSP
#define APP_SUPPORT_HSP                 0
#undef APP_SUPPORT_HID
#define APP_SUPPORT_HID                 0
#undef APP_SUPPORT_BLE
#define APP_SUPPORT_BLE                 0
#undef APP_SUPPORT_SPP
#define APP_SUPPORT_SPP                 0
#undef APP_SUPPORT_AES
#define APP_SUPPORT_AES                 0
#endif
//end

#define APP_VOLUME_MAX_IN_LEVEL         0xa//0xf
#define APP_VOLUME_MAX_OUT_LEVEL        0x3f

///patch en
/*
 *NOTE :
 *AICBT_PATCH_ASIC_U02_ENABLE = 1, asic rom patch for U02 enabled
 *AICBT_PATCH_FPGA_U02_ENABLE = 1, fpga rom patch for U02 enabled
 *AICBT_PATCH_ASIC_U02_ENABLE and AICBT_PATCH_FPGA_U02_ENABLE
 *CAN NOT be 1 at same time
 *but CAN both be 0.
 */

#define AICBT_PATCH_ASIC_U02_ENABLE      1
#define AICBT_PATCH_FPGA_U02_ENABLE      0
#if (CFG_ROM_VER == 2)
#define AICBT_PATCH_U02_ENABLE           (AICBT_PATCH_ASIC_U02_ENABLE || AICBT_PATCH_FPGA_U02_ENABLE)
#else
#define AICBT_PATCH_U02_ENABLE           0
#endif

#define AICBT_PATCH_ASIC_U03_ENABLE      1
#define AICBT_PATCH_FPGA_U03_ENABLE      0
#if (CFG_ROM_VER == 3)
#define AICBT_PATCH_U03_ENABLE           (AICBT_PATCH_ASIC_U03_ENABLE || AICBT_PATCH_FPGA_U03_ENABLE)
#else
#define AICBT_PATCH_U03_ENABLE           0
#endif

#if (CFG_ROM_VER == 255)
#define AICBT_PATCH_ENABLE               1
#else
#define AICBT_PATCH_ENABLE               (AICBT_PATCH_U02_ENABLE || AICBT_PATCH_U03_ENABLE)
#endif

#define AICBT_STACK_CFG \
    {\
        .support_sniff = 1,\
        .multiple_phone = 1,\
        .support_aon = 1,\
        .support_sleep = 1,\
        .rom_version = 3,\
        .tws_plus = 1,\
    }

#endif
