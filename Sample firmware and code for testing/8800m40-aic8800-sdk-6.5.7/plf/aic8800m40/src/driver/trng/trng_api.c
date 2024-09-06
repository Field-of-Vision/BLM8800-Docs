/**
 ****************************************************************************************
 *
 * @file trng_api.c
 *
 * @brief TRNG API functions
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "trng_api.h"
#include "reg_trng.h"
#include "reg_sysctrl.h"
#include "ll.h"
#include "reg_access.h"
//#include "dbg_assert.h"

#define __USE_TRNG_ISR  0

#if __USE_TRNG_ISR
void TRNG_IRQHandler(void)
{
    // clear interrupt
    unsigned int trng_data = AIC_TRNG->trng_data;
    trng_data = trng_data; // fix warning
    ASSERT_WARN((AIC_TRNG->trng_status & (TRNG_SSECSQ | TRNG_SSEISQ)) == 0x00UL);
}
#endif

void trng_init(void)
{
    // clk en if required
    cpusysctrl_pclkme_set(CPU_SYS_CTRL_PCLK_TRNG_MANUAL_ENABLE);
    #if __USE_TRNG_ISR
    NVIC_SetPriority(TRNG_IRQn, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(TRNG_IRQn);
    #endif
}

void trng_free(void)
{
    // clk dis
    #if __USE_TRNG_ISR
    NVIC_DisableIRQ(TRNG_IRQn);
    #endif
}

unsigned int trng_get_word(void)
{
    unsigned int data;
    #if 1
    volatile uint32_t *reg_addr;
    reg_addr = &AIC_CPUSYSCTRL->cfg_cpu_p_rxev;
    //reg_addr = &AIC_CPUSYSCTRL->cfg_cpu_s0_rxev;
    REG_PL_WR(reg_addr, REG_PL_RD(reg_addr) | CPU_SYS_CTRL_CFG_CPU_P_RXEV_TRNG_EN);

    AIC_TRNG->trng_en |= (TRNG_STRNGENQ | TRNG_STRNGIEQ);
    __DSB();
    while (!(AIC_TRNG->trng_status & TRNG_SDRDYQ)) {
        __WFE();
    }
    // read data to clear trng int
    data = AIC_TRNG->trng_data;
    REG_PL_WR(reg_addr, REG_PL_RD(reg_addr) & ~CPU_SYS_CTRL_CFG_CPU_P_RXEV_TRNG_EN);
    #else
    #if !(__USE_TRNG_ISR)
    unsigned int status;
    #endif

    AIC_TRNG->trng_en |= (TRNG_STRNGENQ | TRNG_STRNGIEQ);

    #if __USE_TRNG_ISR
    critical_section_start();
    do {
        __WFI();
    } while (!(AIC_TRNG->trng_status & TRNG_SDRDYQ));
    critical_section_end();
    data = AIC_TRNG->trng_data;

    #else
    do {
        __WFE();
        status = AIC_TRNG->trng_status;
        ASSERT_WARN((status & (TRNG_SSECSQ | TRNG_SSEISQ)) == 0x00UL);
    } while (!(status & TRNG_SDRDYQ));
    // read data to clear trng int, make sure do it before ClearPendingIRQ
    data = AIC_TRNG->trng_data;
    __DSB();
    NVIC_ClearPendingIRQ(TRNG_IRQn);
    #endif
    #endif

    return data;
}
