/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
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
#include "reg_timer.h"
#include "us_ticker_api.h"
#include "sysctrl_api.h"
#include "system.h"

static bool us_ticker_inited = false;

#define US_TICKER_TIMER         (&(AIC_TIM0->TMR[2]))
#define US_TICKER_TIMER_IRQn    TIMER02_IRQn
#define US_TICKER_ISR_FUNC      TIMER02_IRQHandler
//#define US_TICKER_TIMER         (&(AIC_TIM0->TMR[0]))
//#define US_TICKER_TIMER_IRQn    TIMER00_IRQn
#define US_TICKER_CLOCK_SOURCE  (40000000U)
#define US_TICKER_HZ            (1000000U)

const ticker_info_t* us_ticker_get_info()
{
    static const ticker_info_t info = {
        1000000,    // 1 MHz
             32     // 32 bit counter
    };
    return &info;
}

/** US Ticker Interrupt Handler
 *
 * This function handles the us ticker interrupt.
 */
void US_TICKER_ISR_FUNC(void)
{
    uint32_t status = AIC_TIM0->tmr_int_status;
    // match interrupt
    if (status & TIMER_CFG_TMR_MATCH2_INT_STATUS) {
        AIC_TIM0->tmr_int_status = TIMER_CFG_TMR_MATCH2_INT_STATUS;
        us_ticker_irq_handler();
    }
}

void us_ticker_init(void)
{
    uint32_t reg_val;
    if (us_ticker_inited) {
        /* calling init again should cancel current interrupt */
        us_ticker_disable_interrupt();
        return;
    }
    us_ticker_inited = true;

    reg_val = AIC_TIM0->tmr_cfg;
    if ((reg_val & TIMER_CFG_TMR_RUN) == 0x00UL) {  // Init if disabled
        uint32_t clk_div;
        cpusysctrl_pclkme_set(CPU_SYS_CTRL_PCLK_TIMER0_MANUAL_ENABLE); // clk en
        clk_div = US_TICKER_CLOCK_SOURCE / US_TICKER_HZ - 1;
        AIC_TIM0->tmr_rtc_clk_div = TIMER_CFG_TMR_RTC_CLK_DIV_UPDATE | TIMER_CFG_TMR_RTC_CLK_DIV(clk_div); //1us;
        //AIC_TIM0->tmr_pr = 1;
        AIC_TIM0->tmr_cfg |= TIMER_CFG_TMR_RUN;     // enable us ticker
    }

    NVIC_SetPriority(US_TICKER_TIMER_IRQn, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

uint32_t us_ticker_read() {
    return AIC_TIM0->tmr_pc;
}

void us_ticker_set_interrupt(timestamp_t timestamp)
{
    // set match value
    AIC_TIM0->tmr_mr2 = (uint32_t)timestamp;
    // enable match interrupt
    AIC_TIM0->tmr_int_mask_enable = TIMER_CFG_TMR_MATCH2_INT_MASK_ENABLE;
}

void us_ticker_fire_interrupt(void)
{
    NVIC_SetPendingIRQ(US_TICKER_TIMER_IRQn);
}

void us_ticker_disable_interrupt(void)
{
    AIC_TIM0->tmr_int_mask_clear = TIMER_CFG_TMR_MATCH2_INT_MASK_CLEAR;
}

void us_ticker_clear_interrupt(void)
{
    AIC_TIM0->tmr_int_status = TIMER_CFG_TMR_MATCH2_INT_STATUS;
}

void us_ticker_free(void)
{
    if (!us_ticker_inited) {
        return;
    }
    us_ticker_inited = false;

    AIC_TIM0->tmr_int_mask_clear = TIMER_CFG_TMR_MATCH2_INT_MASK_CLEAR;
    NVIC_DisableIRQ(US_TICKER_TIMER_IRQn);
}
