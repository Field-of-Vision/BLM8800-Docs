#ifndef _MSADC_API_H_
#define _MSADC_API_H_

#include "compiler.h"
#include <stdint.h>
#include "plf.h"

#define MSADC_SEPARATE_API_EN   0

// pmu_dcdc_rf_ctrl1: [5:0]
//#define CAL_AVDD13_REG_VALUE_MAX            (1<<6)-1
//#define CAL_AVDD13_REG_VALUE_MIN            (1<<0)-1
#define CAL_AVDD13_REG_REF_VAL_BASE         25
#define CAL_AVDD13_REG_REF_VAL_OFFSET_UP    7
#define CAL_AVDD13_REG_REF_VAL_OFFSET_DOWN  -13
#define CAL_AVDD13_REG_REF_VAL_MAX          CAL_AVDD13_REG_REF_VAL_BASE + CAL_AVDD13_REG_REF_VAL_OFFSET_UP
#define CAL_AVDD13_REG_REF_VAL_MIN          CAL_AVDD13_REG_REF_VAL_BASE + CAL_AVDD13_REG_REF_VAL_OFFSET_DOWN
#define CAL_AVDD13_TARGET                   1300 // set vrf 1.3V for mcu mode

// pmu_ldo_vcore08_ctrl: [4:0]
//#define CAL_VCORE_REG_REF_VAL_MAX           (1<<5)-1
//#define CAL_VCORE_REG_REF_VAL_MIN           (1<<0)-1
#define CAL_VCORE_REG_REF_VAL_BASE          0x16
#define CAL_VCORE_REG_REF_VAL_OFFSET_UP     9
#define CAL_VCORE_REG_REF_VAL_OFFSET_DOWN   -9
#define CAL_VCORE_REG_REF_VAL_MAX           CAL_VCORE_REG_REF_VAL_BASE + CAL_VCORE_REG_REF_VAL_OFFSET_UP
#define CAL_VCORE_REG_REF_VAL_MIN           CAL_VCORE_REG_REF_VAL_BASE + CAL_VCORE_REG_REF_VAL_OFFSET_DOWN
#define CAL_VCORE_TARGET                    800

#define CAL_USB_DM_TARGET                   -880
#define CAL_USB_IDAC_BIT_DEFAULT            0xB
#define CAL_USB_IDAC_BIT_LOW                0x4
#define CAL_USB_IDAC_BIT_HIGH               0xC

/**
 * TypeDefs
 */
enum {
    MSADC_VOLT_VBAT     = 0,
    MSADC_VOLT_VRTC0    = 1,
    MSADC_VOLT_VCORE    = 2,
    MSADC_VOLT_AVDD33   = 3,
    MSADC_VOLT_AVDD18   = 4,
    MSADC_VOLT_AVDD13   = 5,
    MSADC_VOLT_GPB2     = 6,
    MSADC_VOLT_GPB3     = 7,
    MSADC_VOLT_GPB23DIFF= 8,
};

enum msadc_temp_mode {
    MSADC_TEMP_CHIP = 0,
    MSADC_TEMP_PA   = 1
};

// APIs
void msadc_basic_config(void);
void msadc_ts_config(void);
void msadc_ad_config(void);
void msadc_vddsense_off(void);
uint32_t msadc_ms(void);
#if 0
float msadc_pa_sense(void);
#endif

#if (MSADC_SEPARATE_API_EN)
/*      separate function version      */
float msadc_ms_temp_sense0(void);
float msadc_ms_temp_sense1(void);
#if 0
float msadc_ms_pa_current(void);
#endif
float msadc_ms_vbat(void);
float msadc_avdd33(void);
float msadc_avdd18(void);
float msadc_avdd13(void);
float msadc_ms_vrtc0(void);
float msadc_ms_vcore(void);
float msadc_gpiob23_diff(void);
float msadc_gpiob3(void);
float msadc_gpiob2(void);
/*      separate function version      */
#endif

/*        calibration function         */
// cal_avdd13
void msadc_cal_avdd13(void);

// cal_vcore
void msadc_cal_vcore(void);

// cal_usb_dm
void msadc_cal_usb_dm(void);

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
