/**
 ****************************************************************************************
 *
 * @file rwapp_config.h
 *
 * @brief Application configuration definition
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */


#ifndef _RWAPP_CONFIG_H_
#define _RWAPP_CONFIG_H_

/**
 ****************************************************************************************
 * @addtogroup app
 * @brief Application configuration definition
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
/// Default state when stack is running , it will be in adv/scan/init/none state
#if defined(BLE_DFT_ADV)
    #define BLE_DFT_STATE_ADV                    1
#else //BLE_DFT_ADV
    #define BLE_DFT_STATE_ADV                    0
#endif //BLE_DFT_ADV

#if defined(BLE_DFT_SCAN)
    #define BLE_DFT_STATE_SCAN                   1
#else //BLE_DFT_SCAN
    #define BLE_DFT_STATE_SCAN                   0
#endif //BLE_DFT_SCAN

#if defined(BLE_DFT_INIT)
    #define BLE_DFT_STATE_INIT                   1
#else //BLE_DFT_INIT
    #define BLE_DFT_STATE_INIT                   0
#endif //BLE_DFT_INIT

/******************************************************************************************/
/* -------------------------   BLE APPLICATION SETTINGS      -----------------------------*/
/******************************************************************************************/

/// Health Thermometer Application
#if defined(CFG_APP_HT)
#define BLE_APP_HT           1
#else // defined(CFG_APP_HT)
#define BLE_APP_HT           0
#endif // defined(CFG_APP_HT)

#if defined(CFG_APP_HR)
#define BLE_APP_HR           1
#else
#define BLE_APP_HR           0
#endif

/// HID Application
#if defined(CFG_APP_HID)
#define BLE_APP_HID          1
#else // defined(CFG_APP_HID)
#define BLE_APP_HID          0
#endif // defined(CFG_APP_HID)

/// DIS Application
#if defined(CFG_APP_DIS)
#define BLE_APP_DIS          1
#else // defined(CFG_APP_DIS)
#define BLE_APP_DIS          0
#endif // defined(CFG_APP_DIS)

/// Audio Application
#if defined(CFG_APP_AM0)
#define BLE_APP_AM0          1
#else // defined(CFG_APP_AM0)
#define BLE_APP_AM0          0
#endif // defined(CFG_APP_AM0)

/// Battery Service Application
#if (BLE_APP_HID)
#define BLE_APP_BATT          1
#else
#define BLE_APP_BATT          0
#endif // (BLE_APP_HID)

/// Smart Config Application
#if defined(CFG_APP_SMARTCONFIG)
#define BLE_APP_SMARTCONFIG           1
#else // defined(CFG_APP_SMARTCONFIG)
#define BLE_APP_SMARTCONFIG           0
#endif // defined(CFG_APP_SMARTCONFIG)

/// Aud Transmit Server Application
#if defined(CFG_APP_AUDTRANSMITS)
#define BLE_APP_AUDTRANSMITS           1
#else // defined(CFG_APP_AUDTRANSMITS)
#define BLE_APP_AUDTRANSMITS           0
#endif // defined(CFG_APP_AUDTRANSMITS)

/// Aud Transmit Client Application
#if defined(CFG_APP_AUDTRANSMITC)
#define BLE_APP_AUDTRANSMITC           1
#else // defined(CFG_APP_AUDTRANSMITC)
#define BLE_APP_AUDTRANSMITC           0
#endif // defined(CFG_APP_AUDTRANSMITC)

/// User Defined Server Application
#if defined(CFG_APP_UDFS)
#define BLE_APP_UDFS                   1
#else // defined(CFG_APP_UDFS)
#define BLE_APP_UDFS                   0
#endif // defined(CFG_APP_UDFS)

/// User Defined Client Application
#if defined(CFG_APP_UDFC)
#define BLE_APP_UDFC                   1
#else // defined(CFG_APP_UDFC)
#define BLE_APP_UDFC                   0
#endif // defined(CFG_APP_UDFC)

/// Security Application
#if (defined(CFG_APP_SEC) || BLE_APP_HID || BLE_APP_AM0)
#define BLE_APP_SEC          1
#else //(defined(CFG_APP_SEC) || BLE_APP_HID || BLE_APP_AM0)
#define BLE_APP_SEC          0
#endif //(defined(CFG_APP_SEC) || BLE_APP_HID || BLE_APP_AM0)

/// Secure Connection
#if (BLE_APP_AM0)
#define BLE_APP_SEC_CON      1
#else //(BLE_APP_AM0)
#define BLE_APP_SEC_CON      0
#endif ////(BLE_APP_AM0)

/// Hearing Aid Service Configuration
#if (BLE_APP_AM0)
#define AM0_APP_OPTIONAL_CHARACTERISTICS        0
/// Default Settings for Optional Characteristics
/// Specification Default Value
#define AM0_APP_DEFAULT_TREBLE                  0
#define AM0_APP_DEFAULT_BASS                    0
/// Following have no specification Defaults - as application dependent.
/// Please change to suit product.
#define AM0_APP_DEFAULT_MIXED_VOL_STEP          5
#define AM0_APP_DEFAULT_MIXED_VOL               10
#define AM0_APP_DEFAULT_MIC_VOL_STEP            8
#define AM0_APP_DEFAULT_STREAM_VOL_STEP         7
#define AM0_APP_DEFAULT_MIC_SENSITIVITY         127
#define AM0_APP_DEFAULT_SENSITIVITY_STEP        12
/// Default is to have no active streaming program id.
#define AM0_APP_DEFAULT_ACT_STREAM_PROG_ID      0
#else
#define AM0_APP_OPTIONAL_CHARACTERISTICS        0
#endif //BLE_APP_AM0

/// @} rwapp_config

#endif /* _RWAPP_CONFIG_H_ */
