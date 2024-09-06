/**
 ****************************************************************************************
 *
 * @file system.h
 *
 ****************************************************************************************
 */

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "chip.h"

/*
 * DEFINES
 ****************************************************************************************
 */
/* Metal ID */
#define METAL_ID_U01                0x01
#define METAL_ID_U02                0x03

typedef struct {
    uint8_t pmic_vcore_drop_en;
    uint8_t pmic_vrtc08_ldo_off;
    uint8_t pmic_vio_slp_pd_en;
    uint8_t pmic_lp_clk_sel;
    uint8_t sys_initial_clk_cfg;
    uint8_t sys_vio_sel;
    uint8_t sys_vflash_sel;
    uint8_t sys_vrf_sel;
    uint8_t sys_hib_lowramret_en;
} syscfg_predefined_t;

/*
 * EXPORTED VARIABLE DECLARATION
 ****************************************************************************************
 */

extern uint32_t SystemCoreClock;        /*!< System Clock Frequency (Hclk)      */
extern uint32_t PeripheralClock;        /*!< Peripheral Clock Frequency (Pclk)  */
extern uint32_t FlashMem2XClock;        /*!< Flash mem_2x Clock Frequency       */
extern syscfg_predefined_t const syscfg_predefined;

/*
 * EXPORTED FUNCTION DECLARATION
 ****************************************************************************************
 */

void SystemCoreClockUpdate(void);
void SystemInit(void);
void SystemCoreReset(void);
uint32_t ChipIdGet(int ch);
uint8_t ChipRomVerGet(void);

#endif // _SYSTEM_H_
