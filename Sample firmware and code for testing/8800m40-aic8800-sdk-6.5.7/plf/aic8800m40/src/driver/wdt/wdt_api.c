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

/**
 * Includes
 */
#include "wdt_api.h"
#include "reg_wdt.h"
#include "reg_sysctrl.h"
#include "boot.h"
#include "dbg.h"
#include "ll.h"

/**
 * Macros
 */
#define WDT_IRQ_ENABLED         1
#define WDT_REBOOT_TYPE_SEL     WDT_LOOP_FOREVER
#define WDT_PMIC_REBOOT_DLY     0x1F

#if defined(CFG_TEST_BOOTLOADER)
#undef WDT_IRQ_ENABLED
#define WDT_IRQ_ENABLED         0
#endif

#if (WDT_IRQ_ENABLED == 1)
// treat wdt isr as NMI isr
#define wdt0_isr                NMI_Handler
#endif

/**
 * Functions
 */
#if (WDT_IRQ_ENABLED == 1)
void wdt0_isr(void);
#endif

void wdt_init(unsigned int seconds)
{
    unsigned int ticks = seconds << 15; // with 32768Hz freq
    //cpusysctrl_pclkme_set(CPU_SYS_CTRL_PCLK_WDG0_MANUAL_ENABLE);
    //cpusysctrl_oclkme_set(CSC_OCLKME_RTC_WDG0_EN_BIT | CSC_OCLKMD_RTC_ALWAYS_DIS_BIT);
    if (WDT_REBOOT_TYPE_SEL == WDT_CPUSYS_REBOOT) {
        aonsysctrl_wdtre_wdt0_rst_en_setb(); // wdt reset enable
    }
    AIC_CPUSYSCTRL->cfg_cpu_nmi_en = CPU_SYS_CTRL_CFG_CPU_P_NMI_EN;
    AIC_WDT0->LOAD = ticks;
    #if (WDT_IRQ_ENABLED == 0)
    AIC_WDT0->CTRL = WDG_WDG_RUN; // run
    #else
    AIC_WDT0->INT_CLR = WDG_WDG_INT_CLR; // int clear
    AIC_WDT0->CTRL = WDG_WDG_RUN | WDG_WDG_IRQ_EN; // irq_en, run
    /* Enable interrupt */
    NVIC_SetVector(WDT0_IRQn, (uint32_t)wdt0_isr);
    NVIC_SetPriority(WDT0_IRQn, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(WDT0_IRQn);
    #endif
}

void wdt_kick(void)
{
    AIC_WDT0->LOAD = AIC_WDT0->LOAD;
}

void wdt_pause(void)
{
    AIC_WDT0->CTRL &= ~WDG_WDG_RUN; // clr run
}

void wdt_continue(void)
{
    AIC_WDT0->CTRL |=  WDG_WDG_RUN; // set run
}

void wdt_stop(void)
{
    if (WDT_REBOOT_TYPE_SEL == WDT_CPUSYS_REBOOT) {
        aonsysctrl_wdtre_wdt0_rst_en_clrb(); // wdt reset disable
    }
    AIC_WDT0->CTRL = 0x00UL; // irq_dis, stop
    #if (WDT_IRQ_ENABLED == 1)
    /* Disable interrupt */
    NVIC_DisableIRQ(WDT0_IRQn);
    #endif
}

unsigned int wdt_get_pmic_reboot_delay(void)
{
    int ret = 0;
    if ((WDT_REBOOT_TYPE_SEL == WDT_PMIC_REBOOT) && WDT_PMIC_REBOOT_DLY) {
        ret = WDT_PMIC_REBOOT_DLY;
    }
    return ret;
}

#if (WDT_IRQ_ENABLED == 1)
void wdt0_isr(void)
{
    unsigned int regCTRL = __get_CONTROL();
    unsigned int regXPSR = __get_xPSR();
    unsigned int regPSP  = __get_PSP();
    unsigned int regMSP  = __get_MSP();
    unsigned int regPMSK = __get_PRIMASK();
    unsigned int regLR   = __get_LR();
    unsigned int int_raw = AIC_WDT0->INT_RAW;
    dbg("\nType:%x,INT:%x", WDT_REBOOT_TYPE_SEL, int_raw);
    dbg("\nCONTROL=%08x, xPSR   =%08x\n"
          "PSP    =%08x, MSP    =%08x\n"
          "PRIMASK=%08x, LR     =%08x\n",
          regCTRL, regXPSR, regPSP, regMSP, regPMSK, regLR);
    if (regMSP) {
        unsigned int addr = regMSP & ~0x0FUL;
        unsigned int cnt = ((unsigned int)__StackTop - addr) >> 2; // word cnt
        if (cnt > 128) {
            cnt = 128;
        }
        dbg("\nDumpMSP:\n");
        dump_mem(addr, cnt, 4, false);
    }
    if (regPSP) {
        unsigned int addr = regPSP & ~0x0FUL;
        dbg("\nDumpPSP:\n");
        dump_mem(addr, 128, 4, false);
    }
    if (int_raw & WDG_WDG_INT_RAW) {
        AIC_WDT0->INT_CLR = WDG_WDG_INT_CLR; // int clear
        if (WDT_REBOOT_TYPE_SEL == WDT_CPUSYS_REBOOT) {
            AIC_WDT0->CTRL = WDG_WDG_RUN; // stop, reset only if irq_en is false
            AIC_WDT0->LOAD = 0x00UL;
        }
    }
    #ifdef CFG_FHDLR
    panic();
    #endif
}
#endif
