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
/* Part Number */
#define ARM_V6M_CM0P_PARTNO     0xC60
#define ARM_V7M_CM4F_PARTNO     0xC24
#define ARM_CPUP_REVISION       0x01

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
    unsigned int cpu_id = SCB->CPUID;
    if (ARM_V7M_CM4F_PARTNO == ((cpu_id & SCB_CPUID_PARTNO_Msk) >> SCB_CPUID_PARTNO_Pos)) {
        if (ARM_CPUP_REVISION == ((SCB->CPUID & SCB_CPUID_REVISION_Msk) >> SCB_CPUID_REVISION_Pos)) {
            reg_addr = &AIC_CPUSYSCTRL->cfg_cpu_p_rxev;
        } else {
            reg_addr = &AIC_CPUSYSCTRL->cfg_cpu_s0_rxev;
        }
    } else {
        reg_addr = &AIC_CPUSYSCTRL->cfg_cpu_s1_rxev;
    }
    REG_PL_WR(reg_addr, REG_PL_RD(reg_addr) | (0x01UL << 6));

    AIC_TRNG->trng_en |= (TRNG_STRNGENQ | TRNG_STRNGIEQ);
    __DSB();
    while (!(AIC_TRNG->trng_status & TRNG_SDRDYQ)) {
        __WFE();
    }
    // read data to clear trng int
    data = AIC_TRNG->trng_data;
    REG_PL_WR(reg_addr, REG_PL_RD(reg_addr) & ~(0x01UL << 6));
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
