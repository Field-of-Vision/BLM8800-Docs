/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
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
#include "dbg.h"
#include "console.h"
#include "gpadc_api.h"

#ifdef CFG_TEST_GPADC

/*
 * MACROS
 ****************************************************************************************
 */

#define UART_PRINT              dbg
#define CONFIG_USB_PU_CMD_EN    (PLF_AIC8800 && 0)
#define CONFIG_HIGH_ACC_MODE_EN 0

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTIONS
 ****************************************************************************************
 */
#if (PLF_AIC8800)
static int do_measure_gpadc(int argc, char * const argv[])
{
    int volt_mv, temp_c;
    volt_mv = gpadc_measure(GPADC_TYPE_VBAT);
    UART_PRINT("GPADC VBAT voltage is %dmV\n", volt_mv);
    temp_c = gpadc_measure(GPADC_TYPE_TEMP0);
    UART_PRINT("Chip Temperature is %d C\n", temp_c);
    return 0;
}

static int do_conf_gpadc(int argc, char * const argv[])
{
    int func = (int)console_cmd_strtoul(argv[1], NULL, 10);
    if (func == 1) { // gpadc
        int doinit = (int)console_cmd_strtoul(argv[2], NULL, 10);
        int gpbidx = (int)console_cmd_strtoul(argv[3], NULL, 10);
        if (doinit) {
            UART_PRINT("Init GPADC %d\n", gpbidx);
            gpadc_init(gpbidx);
        } else {
            UART_PRINT("Free GPADC %d\n", gpbidx);
            gpadc_free(gpbidx);
        }
    } else if (func == 2) { // gpadc diff chan
        int doinit = (int)console_cmd_strtoul(argv[2], NULL, 10);
        int gpbdiffch = (int)console_cmd_strtoul(argv[3], NULL, 10);
        if (doinit) {
            UART_PRINT("Init GPADC diff chan %d\n", gpbdiffch);
            gpadc_diff_init(gpbdiffch);
        } else {
            UART_PRINT("Free GPADC diff chan %d\n", gpbdiffch);
            gpadc_diff_free(gpbdiffch);
        }
    } else {
        UART_PRINT("Unsupported func %d\n", func);
    }
    return 0;
}

static int do_read_gpadc(int argc, char * const argv[])
{
    int volt_mv;
    int gpbidx = (int)console_cmd_strtoul(argv[1], NULL, 10);
    volt_mv = gpadc_read(gpbidx);
    UART_PRINT("GPADC %d voltage is %dmV\n", gpbidx, volt_mv);
    return 0;
}

static int do_read_gpadc_diff_chan(int argc, char * const argv[])
{
    int volt_mv;
    int gpbdiffch = (int)console_cmd_strtoul(argv[1], NULL, 10);
    if (gpbdiffch < GPADC_DIFF_CH_NUM) {
        int negflag = (int)console_cmd_strtoul(argv[2], NULL, 10);
        #if (CONFIG_HIGH_ACC_MODE_EN == 0)
        volt_mv = gpadc_diff_read(gpbdiffch, negflag);
        UART_PRINT("GPADC diff chan %d voltage is %dmV\n", gpbdiffch, volt_mv);
        #else
        volt_mv = gpadc_diff_read_ham(gpbdiffch, negflag);
        UART_PRINT("GPADC diff chan %d ham voltage is %d(%d.%02dmV)\n",
            gpbdiffch, volt_mv, volt_mv / 100, ((volt_mv < 0) ? (-volt_mv) : volt_mv) % 100);
        #endif
    } else {
        UART_PRINT("GPADC diff chan %d invalid!\n", gpbdiffch);
    }
    return 0;
}
#endif

#if (PLF_AIC8800MC) || (PLF_AIC8800M40)
static int do_read_gpadc(int argc, char * const argv[])
{
    int volt_mv;
    int gpbidx = (int)console_cmd_strtoul(argv[1], NULL, 10);
    gpadc_init(gpbidx);
    volt_mv = gpadc_read(gpbidx);
    gpadc_free(gpbidx);
    UART_PRINT("GPADC %d voltage is %d mV\n", gpbidx, volt_mv);

    return 0;
}

static int do_read_diff(int argc, char * const argv[])
{
    int volt_mv;
    gpadc_diff_init();
    volt_mv = gpadc_diff_read(GPADC_DIFF_N2P);
    gpadc_diff_free();
    UART_PRINT("Diff voltage is %d mV\n", volt_mv);

    return 0;
}
#endif

#if (CONFIG_USB_PU_CMD_EN)
#include "pmic_api.h"
/**
 * Note: for application with usb, more accurate gpadc diff chan is recommended
 */
static int do_usb_hal_init(int argc, char * const argv[])
{
    // power up usb & usb_pll
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteAnalogReg->por_ctrl),
        (AIC1000LITE_ANALOG_REG_CFG_RTC_USB_PLL_PU | AIC1000LITE_ANALOG_REG_CFG_RTC_USB_PU |
        AIC1000LITE_ANALOG_REG_CFG_RTC_USBPLL_CLK_EN),
        (AIC1000LITE_ANALOG_REG_CFG_RTC_USB_PLL_PU | AIC1000LITE_ANALOG_REG_CFG_RTC_USB_PU |
        AIC1000LITE_ANALOG_REG_CFG_RTC_USBPLL_CLK_EN));
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteAnalogReg->cfg_ana_usb_ctrl0),
        (AIC1000LITE_ANALOG_REG_CFG_ANA_USB_ISET_HS_DISCONNECT(6)),
        (AIC1000LITE_ANALOG_REG_CFG_ANA_USB_ISET_HS_DISCONNECT(7)));
    return 0;
}
#endif

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void gpadc_test(void)
{
    UART_PRINT("\nGPADC test start\n");
    #if (PLF_AIC8800)
    gpadc_samplerate_set(GPADC_SAMPLERATE_MID);
    console_cmd_add("measure", "do_measure_gpadc", 1, 1, do_measure_gpadc);
    console_cmd_add("conf", "do_conf_gpadc", 4, 4, do_conf_gpadc);
    console_cmd_add("read", "do_read_gpadc", 2, 2, do_read_gpadc);
    console_cmd_add("diffchread", "do_read_gpadc_diff_chan", 3, 3, do_read_gpadc_diff_chan);
    #elif (PLF_AIC8800MC) || (PLF_AIC8800M40)
    console_cmd_add("read", "do_read_gpadc", 2, 2, do_read_gpadc);
    console_cmd_add("diff", "do_read_diff", 1, 1, do_read_diff);
    #endif

    #if (CONFIG_USB_PU_CMD_EN)
    console_cmd_add("usbinit", "do_usb_hal_init", 1, 1, do_usb_hal_init);
    #endif

    UART_PRINT("\nGPADC test done\n");
}

#endif /* CFG_TEST_GPADC */
