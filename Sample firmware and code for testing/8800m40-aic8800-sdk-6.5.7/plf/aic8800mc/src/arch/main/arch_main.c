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
#include "gpio_api.h"

#include "dbg.h"

#include "stdio_uart.h"
#include "system.h"

#if (PLF_CONSOLE)
#include "console.h"
#endif /* PLF_CONSOLE */

#if PLF_TEST
#include "test_main.h"
#endif /* PLF_TEST */

#ifdef CFG_RTOS
#include "rtos.h"
#endif
#if defined(CFG_VER_STR)
#include "sdk_version.h"
#endif
#if defined(CFG_WIFI_TESTMODE)
#include "pmic_api.h"
#include "testmode_api.h"
#endif
#if PLF_BT_TESTMODE
#include "pmic_api.h"
#include "bt_aic8800mc_drvif.h"
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
    .pmic_vcore_drop_en = CONFIG_LP_PMIC_VCORE_DROP_ENABLE,
    .pmic_vrtc08_ldo_off = 0,
    .pmic_vio_slp_pd_en = CONFIG_LP_PMIC_VIO_SLP_PD_ENABLE,
    .pmic_lp_clk_sel = CONFIG_LPCLK_SELECT,
    .sys_initial_clk_cfg = CONFIG_INITIAL_SYSTEM_CLOCK,
    .sys_vio_sel = CONFIG_VIO_SELECT,
    .sys_vflash_sel = CONFIG_VFLASH_SELECT,
    .sys_vrf_sel = CONFIG_VRF_SELECT,
    .sys_hib_retram_en = 0,
    .sys_usb_cal_dm_en = CONFIG_USB_DM_VOLT_CALIB_ENABLE,
};

/*
 * LOCAL FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/* Save the CPU_SYS peripherals */
__RAMTEXT void back_up_cpusys_pers(void)
{
    // back up resources host used
    gpio_regs_save();
}

/* Restore the CPU_SYS peripherals */
__RAMTEXT void restore_cpusys_pers(void)
{
    // restore resources host used
    stdio_uart_recover();
    gpio_regs_recover();
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
    #ifndef CFG_TEST_MICROHOST
    #if !defined(CFG_TEST_BOOTLOADER)
    // Update system clocks
    SystemCoreClockUpdate();
    #endif

    #if defined(CFG_WIFI_TESTMODE) || PLF_BT_TESTMODE
    uint32_t boot_addr = PMIC_MEM_READ((unsigned int)&AIC_PMU_RTC0->rtc_rg_reserved0);
    PMIC_MEM_MASK_WRITE((unsigned int)&AIC_PMU_RTC0->rtc_rg_reserved0, 0, 0xffffffff);
    #if defined(CFG_WIFI_TESTMODE)
    if (boot_addr != 0 && ((boot_addr&0x80000000) == 0))
    {
        testmode_iram_init();
        boot_go(boot_addr);
    }
    #endif
    #if PLF_BT_TESTMODE
    if (boot_addr != 0 && ((boot_addr&0x80000000)))
    {
        bt_drv_non_signaling_test_iram_init();
        boot_go(boot_addr & 0x7fffffff);
    }
    #endif
    #endif

    // Initialize stdio uart
    stdio_uart_init();

    // finally start interrupt handling
    GLOBAL_INT_START();

    #if defined(CFG_VER_STR)
    dbg("\nVer: %s\nsdk build: %s\nusr build: %s\n", sdk_version_str, sdk_build_date, usr_build_date);
    #else
    dbg("\r\nhost_wb start\r\n");
    #endif

    #if !defined(CFG_TEST_BOOTLOADER)
    aic_time_init(0, 0);
    #endif

    #else /* CFG_TEST_MICROHOST */
    // Initialize stdio uart
    stdio_uart_recover();

    // finally start interrupt handling
    GLOBAL_INT_START();
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
