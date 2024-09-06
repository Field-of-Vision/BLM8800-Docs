#ifndef __APP_BLE_ONLY_H__
#define __APP_BLE_ONLY_H__
#include "tgt_cfg_bt.h"
#if PLF_BLE_ONLY == 1 || PLF_BTDM
#include "rtos.h"
#include "app.h"
#include "att.h"
#if (BLE_APP_SEC)
#include "app_sec.h"                 // Application security Definition
#endif // (BLE_APP_SEC)

#if (BLE_APP_DIS)
#include "app_dis.h"
#endif //(BLE_APP_DIS)               // Device Information Definitions

#if (BLE_APP_BATT)
#include "app_batt.h"                // Battery Application Definitions
#endif //(BLE_APP_DIS)

#if (BLE_APP_HID)
#include "app_hid.h"                 // HID Application Definitions
#endif //(BLE_APP_HID)

#if (BLE_APP_SMARTCONFIG)
#include "app_smartconfig.h"         // Smart Config Application Definitions
#endif //(BLE_APP_SMARTCONFIG)

#if (BLE_APP_AUDTRANSMITS)
#include "app_audtransmits.h"        // Aud Transmit Server Application Definitions
#endif //(BLE_APP_AUDTRANSMITS)

#if (BLE_APP_AUDTRANSMITC)
#include "app_audtransmitc.h"        // Aud Transmit Client Application Definitions
#endif //(BLE_APP_AUDTRANSMITC)

#if (BLE_APP_AUDTRANSMITS || BLE_APP_AUDTRANSMITC)
#include "app_ble_audtransmit.h"
#endif

#if (BLE_APP_UDFS)
#include "app_udfs.h"        // User Defined Server Application Definitions
#endif //(BLE_APP_UDFS)

#if (BLE_APP_UDFC)
#include "app_udfc.h"        // User Defined Client Application Definitions
#endif //(BLE_APP_UDFC)

#define APP_UPDATE_DATA          ("BLE_UPDATE_ADV_DATA")
#define APP_UPDATE_DATA_LEN      sizeof(APP_UPDATE_DATA)

/// Advertising channel map - 37, 38, 39
#define APP_ADV_CHMAP           (0x07)
/// Advertising minimum interval - 100ms (160*0.625ms)
#define APP_ADV_INT_MIN         (160)
/// Advertising maximum interval - 100ms (160*0.625ms)
#define APP_ADV_INT_MAX         (160)
/// Fast advertising interval
#define APP_ADV_FAST_INT        (32)

void app_ble_init(void);

#if PLF_CONSOLE
void app_ble_test_command_add(void);
#endif
#endif
#endif /* AICBT_H */
