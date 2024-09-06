/**
 ****************************************************************************************
 *
 * @file arch_main.c
 *
 * @brief Main loop of the application.
 *
 ****************************************************************************************
 */

/*
 * INCLUDES
 ****************************************************************************************
 */

#include "plf.h"       // SW configuration

#include "arch.h"      // architectural platform definitions
#include <stdlib.h>    // standard lib functions
#include <stddef.h>    // standard definitions
#include <stdint.h>    // standard integer definition
#include <stdbool.h>   // boolean definition
#include "boot.h"      // boot definition
#include "time_api.h"
#include "sysctrl_api.h"

#include "dbg.h"

#include "stdio_uart.h"
#include "system.h"

#if (PLF_CONSOLE)
#include "console.h"
#endif /* PLF_CONSOLE */

#if PLF_TEST
#include "test_main.h"
#endif /* PLF_TEST */

#if PLF_PMIC
#include "pwrkey_api.h"
#endif

#ifdef CFG_RTOS
#include "rtos.h"
#endif
#if defined(CFG_VER_STR)
#include "sdk_version.h"
#endif
#if PLF_BT_TESTMODE
#include "pmic_api.h"
#include "bt_aic8800_drvif.h"
#endif

/*
 * DEFINES
 ****************************************************************************************
 */


/*
 * STRUCTURE DEFINITIONS
 ****************************************************************************************
 */


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
syscfg_predefined_t const syscfg_predefined = {
    #if PLF_PMIC_LDO_VCORE
    .pmic_vcore_dcdc_off = 1,
    #elif PLF_PMIC_DCDC_VCORE
    .pmic_vcore_ldo_off  = 1,
    #endif
    .pmic_vrtc09_ldo_off = 0,
    #if PLF_PMIC_VER_AUD
    // dcdc_pa_volatage, 340 means 3.40V, resolution is 0.05V.
    #if PLF_WIFI_STACK || PLF_RF_MODE_BT_COMBO || PLF_RF_MODE_BTWIFI_COMBO
    .pmic_dcdc_pa_voltage = 340,
    #else
    .pmic_dcdc_pa_voltage = 180,
    #endif
    #else /* PLF_PMIC_VER_AUD */
    .pmic_dcdc_pa_voltage = 340,
    #endif /* PLF_PMIC_VER_AUD */
    .pmic_lpo_512k_sel = CONFIG_LP_CLOCK_LPO_512K_ENABLE,
    .pmic_vcore_dcdc_drop_en = CONFIG_LP_PMIC_VCORE_DCDC_DROP_ENABLE,
    .pmic_vcore_ldo_drop_en = CONFIG_LP_PMIC_VCORE_LDO_DROP_ENABLE,
    .pmic_vrtc_ldo_drop_en = CONFIG_LP_PMIC_VRTC_LDO_DROP_ENABLE,
    .pmic_vrf_dcdc_drop_en = CONFIG_LP_PMIC_VRF_DCDC_DROP_ENABLE,
    .pmic_vio_slp_pd_en = CONFIG_LP_PMIC_VIO_SLP_PD_ENABLE,
    .sys_initial_clk_cfg = CONFIG_INITIAL_SYSTEM_CLOCK,
    .sys_vio_sel = CONFIG_VIO_SELECT,
};

/*
 * LOCAL FUNCTION DECLARATIONS
 ****************************************************************************************
 */

void ChipIdCheck(void)
{
#if PLF_PMIC
    if (ChipIdGet(4) != 0x1000) {
        dbg("ChipIdCheck failed, env['PMIC_VER'] may not match chip\n");
        ASSERT_ERR(0);
    }
    #if PLF_PMIC_VER_AUD
    if (ChipIdGet(2) != 0x0A) {
        dbg("ChipIdCheck failed, env['PMIC_VER'] may not match chip\n");
        ASSERT_ERR(0);
    }
    #endif
#endif
}

#if defined(CFG_WIFI_TESTMODE) || PLF_BT_TESTMODE
typedef void (*boot_func_t)(void);
static void boot_to(unsigned int addr)
{
    __disable_irq();
    ((boot_func_t)addr)();
}
void boot_go(uint32_t addr)
{
    boot_to(*(uint32_t *)(addr + 4));
    return;
}
#endif /* CFG_WIFI_TESTMODE */

/*
 * MAIN FUNCTION
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief RW main function.
 *
 * This function is called right after the booting process has completed.
 *
 * @return status   exit status
 ****************************************************************************************
 */
void rw_main(void)
{
    /*
     ************************************************************************************
     * Platform initialization
     ************************************************************************************
     */
    #if !defined(CFG_TEST_BOOTLOADER)
    // Update system clocks
    SystemCoreClockUpdate();
    #endif
#if PLF_BT_TESTMODE
    uint32_t boot_addr = PMIC_MEM_READ((unsigned int)0x50018c00);
    PMIC_MEM_MASK_WRITE((unsigned int)0x50018c00, 0, 0xffffffff);
    if (boot_addr != 0 && ((boot_addr&0x80000000)))
    {
        bt_drv_non_signaling_test_iram_init();
        boot_go(boot_addr & 0x7fffffff);
    }
#endif

    // Initialize stdio uart
    stdio_uart_init();

    // finally start interrupt handling
    GLOBAL_INT_START();

    #if PLF_PMIC
    pwrkey_poweron_check();
    #endif

    ChipIdCheck();

    #if defined(CFG_VER_STR)
    dbg("\nVer: %s\nsdk build: %s\nusr build: %s\n", sdk_version_str, sdk_build_date, usr_build_date);
    #else
    dbg("\r\nhost_wb start\r\n");
    #endif

    #if !defined(CFG_TEST_BOOTLOADER)
    aic_time_init(0, 0);
    #endif

    #ifndef CFG_RTOS
    // Initialize console
    #if (PLF_CONSOLE)
    console_init();
    #endif
    #if PLF_TEST
    test_main();
    #endif /* PLF_TEST */

    /*
     ************************************************************************************
     * Main loop
     ************************************************************************************
     */

    while(1)
    {
        // schedule all pending console commands
        #if (PLF_CONSOLE)
        console_schedule();
        #endif

        GLOBAL_INT_DISABLE();
        #if (PLF_CONSOLE)
        if (console_buf_empty() == 1)
        #endif
        {
            // Wait for interrupt
            __WFI();
        }
        GLOBAL_INT_RESTORE();
    }
    #else

    rtos_main();

    #endif
}

#if PLF_STDLIB
int main(void)
{
    rw_main();
    return 0;
}
#endif
