/**
 ****************************************************************************************
 *
 * @file gpio_api.c
 *
 * @brief GPIO API functions
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "gpio_api.h"
#include "reg_gpio.h"
#include "reg_iomux.h"
#include "arch.h"
#if PLF_PMIC
#include "pmic_api.h"
#endif
#include "reg_sysctrl.h"
#include "reg_anareg.h"

typedef struct {
    AIC_IOMUX_TypeDef iomux;
    struct {
        __IO uint32_t MR;
        __IO uint32_t VR;
        __IO uint32_t DR;
        __IO uint32_t TELR;
        __IO uint32_t TER;
        __IO uint32_t TLR;
        __IO uint32_t ICR;
        __IO uint32_t TIR;
        __IO uint32_t FR;
    } gpioa;
    struct {
        __IO uint32_t MR;
        __IO uint32_t VR;
        __IO uint32_t DR;
        __IO uint32_t TELR;
        __IO uint32_t TER;
        __IO uint32_t TLR;
        __IO uint32_t ICR;
        __IO uint32_t TIR;
        __IO uint32_t FR;
    } gpiob;
} gpio_registers_t;

gpio_registers_t gpio_registiers = {{{{0,},},},};

void gpioa_init(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    // iomux
    if ((gpidx < 2) || ((gpidx > 7) && (gpidx < 10))) {
        iomux_gpioa_config_sel_setf(gpidx, 1);
    } else if (gpidx < 16) {
        iomux_gpioa_config_sel_setf(gpidx, 0);
    } else if ((gpidx == 16) || (gpidx == 17)) {
        AIC_CPUSYSCTRL->cfg_usb_gpio |= CPU_SYS_CTRL_CFG_USB_GPIO_MODE;
    }
    // mask
    AIC_GPIOA->MR |=  gpmsk;
}

void gpioa_deinit(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    // mask
    AIC_GPIOA->MR &= ~gpmsk;
}

void gpioa_dir_in(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    AIC_GPIOA->DR &= ~gpmsk;
}

void gpioa_dir_out(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    AIC_GPIOA->DR |=  gpmsk;
}

void gpioa_set(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    AIC_GPIOA->VR |=  gpmsk;
}

void gpioa_clr(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    AIC_GPIOA->VR &= ~gpmsk;
}

int gpioa_get(int gpidx)
{
    int val;
    unsigned int gpmsk = 0x01UL << gpidx;
    val = (AIC_GPIOA->VR & gpmsk) ? 1 : 0;
    return val;
}

void gpioa_force_pull_up_enable(int gpidx)
{
    if (gpidx < 16) {
        iomux_gpioa_config_pull_dn_setf(gpidx, 0);
        iomux_gpioa_config_pull_up_setf(gpidx, 1);
        iomux_gpioa_config_pull_frc_setf(gpidx, 1);
    }
    if ((gpidx == 16) || (gpidx == 17)) {
        AIC_CPUSYSCTRL->cfg_usb_gpio |= CPU_SYS_CTRL_CFG_USB_GPIO_PULLUP(0x1 << (gpidx - 16));
    }
}

void gpioa_force_pull_dn_enable(int gpidx)
{
    if (gpidx < 16) {
        iomux_gpioa_config_pull_up_setf(gpidx, 0);
        iomux_gpioa_config_pull_dn_setf(gpidx, 1);
        iomux_gpioa_config_pull_frc_setf(gpidx, 1);
    }
    if ((gpidx == 16) || (gpidx == 17)) {
        AIC_CPUSYSCTRL->cfg_usb_gpio |= CPU_SYS_CTRL_CFG_USB_GPIO_PULLDOWN(0x1 << (gpidx - 16));
    }
}

void gpioa_force_pull_none_enable(int gpidx)
{
    if (gpidx < 16) {
        iomux_gpioa_config_pull_dn_setf(gpidx, 0);
        iomux_gpioa_config_pull_up_setf(gpidx, 0);
        iomux_gpioa_config_pull_frc_setf(gpidx, 1);
    }
}

void gpioa_force_pull_up_dn_disable(int gpidx)
{
    if (gpidx < 16) {
        iomux_gpioa_config_pull_up_setf(gpidx, 0);
        iomux_gpioa_config_pull_dn_setf(gpidx, 0);
        iomux_gpioa_config_pull_frc_setf(gpidx, 0);
    }
    if ((gpidx == 16) || (gpidx == 17)) {
        AIC_CPUSYSCTRL->cfg_usb_gpio &= ~ CPU_SYS_CTRL_CFG_USB_GPIO_PULLDOWN(0x1 << (gpidx - 16));
        AIC_CPUSYSCTRL->cfg_usb_gpio &= ~ CPU_SYS_CTRL_CFG_USB_GPIO_PULLUP(0x1 << (gpidx - 16));
    }
}

gpio_irq_handler_t gpioa_irq_handler[GPIOA_IDX_MAX] = {NULL};

void gpioa_isr(void);

void gpioa_irq_en_set(int gpidx, int enable)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    if (enable) {
        //AIC_GPIOA->IRR = gpmsk;
        AIC_GPIOA->ICR |=  gpmsk; // int en
    } else {
        AIC_GPIOA->ICR &= ~gpmsk; // int disable
    }
}

void gpioa_irq_init(int gpidx, int type, gpio_irq_handler_t handler)
{
    unsigned int reg_val;
    unsigned int gpmsk = 0x01UL << gpidx;
    gpioa_init(gpidx);
    gpioa_dir_in(gpidx);
    AIC_GPIOA->TIR |=  gpmsk; // input en
    AIC_GPIOA->TELR   &= ~gpmsk; // edge
    if (type == GPIOIRQ_TYPE_EDGE_BOTH) {
        AIC_GPIOA->TER |=  gpmsk; // both edge
    } else {
        AIC_GPIOA->TER &= ~gpmsk; // not both edge
        if (type == GPIOIRQ_TYPE_EDGE_RISE) {
            AIC_GPIOA->TLR |=  gpmsk; // rising edge
        } else {
            AIC_ANAREG1->gpioa_cfg |= ANALOG_REG1_RF_CFG_ANA_GPIOA_WAKEUP_POLARITY(1 << gpidx);
            AIC_GPIOA->TLR &= ~gpmsk; // falling edge
        }
    }
    AIC_GPIOA->IRR  =  gpmsk; // int clr
    AIC_GPIOA->ICR |=  gpmsk; // int en
    reg_val = AIC_GPIOA->FR & ~(0x07UL << (gpidx & ~0x03UL));
    AIC_GPIOA->FR = reg_val |  (0x07UL << (gpidx & ~0x03UL)); // filter
    gpioa_irq_handler[gpidx] = handler;
    if (!NVIC_GetEnableIRQ(GPIOA_IRQn)) {
        NVIC_SetVector(GPIOA_IRQn, (uint32_t)gpioa_isr);
        NVIC_SetPriority(GPIOA_IRQn, __NVIC_PRIO_LOWEST);
        NVIC_EnableIRQ(GPIOA_IRQn);
    }
}

void gpioa_irq_deinit(int gpidx)
{
    if (gpidx < GPIOA_IDX_MAX) {
        unsigned int gpmsk = 0x01UL << gpidx;
        gpioa_irq_handler[gpidx] = NULL;
        AIC_GPIOA->ICR &= ~gpmsk; // int dis
        gpioa_deinit(gpidx);
    }
}

void gpioa_isr(void)
{
    unsigned int int_status = AIC_GPIOA->ISR;
    while (int_status) {
        int bit = 31 - __CLZ(int_status);
        if (bit >= GPIOA_IDX_MAX) {
            // error occors
            break;
        }
        AIC_GPIOA->IRR = (0x01UL << bit);
        __ISB();
        if (gpioa_irq_handler[bit]) {
            int event = GPIOIRQ_EVENT_EDGE_FALL;
            if (AIC_GPIOA->TER & (0x01UL << bit)) {
                event = GPIOIRQ_EVENT_EDGE_BOTH;
            } else if (AIC_GPIOA->TLR & (0x01UL << bit)) {
                event = GPIOIRQ_EVENT_EDGE_RISE;
            }
            gpioa_irq_handler[bit](GPIOIRQ_CB_PARAM(bit, event)); // pass gpio num to cb func
        }
        int_status = AIC_GPIOA->ISR;
    }
}

void gpiob_init(int gpidx)
{
    if (gpidx < GPIOB_IDX_MAX) {
        unsigned int gpmsk = 0x01UL << gpidx;
        // iomux
        iomux_gpiob_config_sel_setf(gpidx, 0);
        // mask
        AIC_GPIOB->MR |=  gpmsk;
    }
}

void gpiob_deinit(int gpidx)
{
    if (gpidx < GPIOB_IDX_MAX) {
        unsigned int gpmsk = 0x01UL << gpidx;
        // mask
        AIC_GPIOB->MR &= ~gpmsk;
    }
}

void gpiob_dir_in(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    AIC_GPIOB->DR &= ~gpmsk;
}

void gpiob_dir_out(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    AIC_GPIOB->DR |=  gpmsk;
}

void gpiob_set(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    AIC_GPIOB->VR |=  gpmsk;
}

void gpiob_clr(int gpidx)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    AIC_GPIOB->VR &= ~gpmsk;
}

int gpiob_get(int gpidx)
{
    int val;
    unsigned int gpmsk = 0x01UL << gpidx;
    val = (AIC_GPIOB->VR & gpmsk) ? 1 : 0;
    return val;
}

void gpiob_force_pull_up_enable(int gpidx)
{
    if (gpidx < GPIOB_IDX_MAX) {
        iomux_gpiob_config_pull_dn_setf(gpidx, 0);
        iomux_gpiob_config_pull_up_setf(gpidx, 1);
        iomux_gpiob_config_pull_frc_setf(gpidx, 1);
    }
}

void gpiob_force_pull_dn_enable(int gpidx)
{
    if (gpidx < GPIOB_IDX_MAX) {
        iomux_gpiob_config_pull_up_setf(gpidx, 0);
        iomux_gpiob_config_pull_dn_setf(gpidx, 1);
        iomux_gpiob_config_pull_frc_setf(gpidx, 1);
    }
}

void gpiob_force_pull_none_enable(int gpidx)
{
    if (gpidx < GPIOB_IDX_MAX) {
        iomux_gpiob_config_pull_dn_setf(gpidx, 0);
        iomux_gpiob_config_pull_up_setf(gpidx, 0);
        iomux_gpiob_config_pull_frc_setf(gpidx, 1);
    }
}

void gpiob_force_pull_up_dn_disable(int gpidx)
{
    if (gpidx < GPIOB_IDX_MAX) {
        iomux_gpiob_config_pull_up_setf(gpidx, 0);
        iomux_gpiob_config_pull_dn_setf(gpidx, 0);
        iomux_gpiob_config_pull_frc_setf(gpidx, 0);
    }
}

void gpiob_force_oen_enable(int gpidx)
{
    if (gpidx < GPIOB_IDX_MAX) {
        iomux_gpiob_config_pull_frc_setf(gpidx, 1);
        iomux_gpiob_config_oen_reg_setf(gpidx, 1);
        iomux_gpiob_config_oen_frc_setf(gpidx, 1);
    }
}

void gpiob_force_oen_disable(int gpidx)
{
    if (gpidx < GPIOB_IDX_MAX) {
        iomux_gpiob_config_pull_frc_setf(gpidx, 0);
        iomux_gpiob_config_oen_reg_setf(gpidx, 0);
        iomux_gpiob_config_oen_frc_setf(gpidx, 0);
    }
}

gpio_irq_handler_t gpiob_irq_handler[GPIOB_IDX_MAX] = {NULL};

void gpiob_isr(void);

void gpiob_irq_en_set(int gpidx, int enable)
{
    unsigned int gpmsk = 0x01UL << gpidx;
    if (enable) {
        //AIC_GPIOB->IRR = gpmsk;
        AIC_GPIOB->ICR |=  gpmsk; // int en
    } else {
        AIC_GPIOB->ICR &= ~gpmsk; // int disable
    }
}

void gpiob_irq_init(int gpidx, int type, gpio_irq_handler_t handler)
{
    unsigned int reg_val;
    unsigned int gpmsk = 0x01UL << gpidx;
    gpiob_init(gpidx);
    gpiob_dir_in(gpidx);
    AIC_GPIOB->TIR |=  gpmsk; // input en
    AIC_GPIOB->TELR   &= ~gpmsk; // edge
    if (type == GPIOIRQ_TYPE_EDGE_BOTH) {
        AIC_GPIOB->TER |=  gpmsk; // both edge
    } else {
        AIC_GPIOB->TER &= ~gpmsk; // not both edge
        if (type == GPIOIRQ_TYPE_EDGE_RISE) {
            AIC_GPIOB->TLR |=  gpmsk; // rising edge
        } else {
            AIC_ANAREG1->gpiob_cfg1 |= ANALOG_REG1_RF_CFG_ANA_GPIOB_WAKEUP_POLARITY(1 << gpidx);
            AIC_GPIOB->TLR &= ~gpmsk; // falling edge
        }
    }
    AIC_GPIOB->IRR  =  gpmsk; // int clr
    AIC_GPIOB->ICR |=  gpmsk; // int en
    reg_val = AIC_GPIOB->FR & ~(0x07UL << (gpidx & ~0x03UL));
    AIC_GPIOB->FR = reg_val |  (0x07UL << (gpidx & ~0x03UL)); // filter
    gpiob_irq_handler[gpidx] = handler;
    if (!NVIC_GetEnableIRQ(GPIOB_IRQn)) {
        NVIC_SetVector(GPIOB_IRQn, (uint32_t)gpiob_isr);
        NVIC_SetPriority(GPIOB_IRQn, __NVIC_PRIO_LOWEST);
        NVIC_EnableIRQ(GPIOB_IRQn);
    }
}

void gpiob_irq_deinit(int gpidx)
{
    if (gpidx < GPIOB_IDX_MAX) {
        unsigned int gpmsk = 0x01UL << gpidx;
        gpiob_irq_handler[gpidx] = NULL;
        AIC_GPIOB->ICR &= ~gpmsk; // int dis
        gpiob_deinit(gpidx);
    }
}

void gpiob_isr(void)
{
    unsigned int int_status = AIC_GPIOB->ISR;
    while (int_status) {
        int bit = 31 - __CLZ(int_status);
        if (bit >= GPIOB_IDX_MAX) {
            // error occors
            break;
        }
        AIC_GPIOB->IRR = (0x01UL << bit);
        __ISB();
        if (gpiob_irq_handler[bit]) {
            int event = GPIOIRQ_EVENT_EDGE_FALL;
            if (AIC_GPIOB->TER & (0x01UL << bit)) {
                event = GPIOIRQ_EVENT_EDGE_BOTH;
            } else if (AIC_GPIOB->TLR & (0x01UL << bit)) {
                event = GPIOIRQ_EVENT_EDGE_RISE;
            }
            gpiob_irq_handler[bit](GPIOIRQ_CB_PARAM(bit, event)); // pass gpio num to cb func
        }
        int_status = AIC_GPIOB->ISR;
    }
}

__RAMTEXT void gpio_regs_save(void)
{
    int idx;
    #if PLF_PMIC
    pmic_gpio_hold_config(1);
    #endif
    // sel analog, avoid leakage of electricity
    anareg1_gpiob_func_mux_sel_setb();
    for (idx = 0; idx < GPIOA_IDX_MAX; idx++) {
        gpio_registiers.iomux.pad_gpioa_cfg_reg[idx] = AIC_IOMUX->pad_gpioa_cfg_reg[idx];
        gpio_registiers.iomux.pad_agpio_cfg_reg[idx] = AIC_IOMUX->pad_agpio_cfg_reg[idx];
        if (idx < GPIOB_IDX_MAX) {
            gpio_registiers.iomux.pad_gpiob_cfg_reg[idx] = AIC_IOMUX->pad_gpiob_cfg_reg[idx];
        }
    }
    gpio_registiers.gpioa.MR   = AIC_GPIOA->MR;
    gpio_registiers.gpioa.VR   = AIC_GPIOA->VR;
    gpio_registiers.gpioa.DR   = AIC_GPIOA->DR;
    gpio_registiers.gpioa.TELR = AIC_GPIOA->TELR;
    gpio_registiers.gpioa.TER  = AIC_GPIOA->TER;
    gpio_registiers.gpioa.TLR  = AIC_GPIOA->TLR;
    gpio_registiers.gpioa.ICR  = AIC_GPIOA->ICR;
    gpio_registiers.gpioa.TIR  = AIC_GPIOA->TIR;
    gpio_registiers.gpioa.FR   = AIC_GPIOA->FR;
    gpio_registiers.gpiob.MR   = AIC_GPIOB->MR;
    gpio_registiers.gpiob.VR   = AIC_GPIOB->VR;
    gpio_registiers.gpiob.DR   = AIC_GPIOB->DR;
    gpio_registiers.gpiob.TELR = AIC_GPIOB->TELR;
    gpio_registiers.gpiob.TER  = AIC_GPIOB->TER;
    gpio_registiers.gpiob.TLR  = AIC_GPIOB->TLR;
    gpio_registiers.gpiob.ICR  = AIC_GPIOB->ICR;
    gpio_registiers.gpiob.TIR  = AIC_GPIOB->TIR;
    gpio_registiers.gpiob.FR   = AIC_GPIOB->FR;
}

__RAMTEXT void gpio_regs_recover(void)
{
    int idx;
    for (idx = 0; idx < GPIOA_IDX_MAX; idx++) {
        AIC_IOMUX->pad_gpioa_cfg_reg[idx] = gpio_registiers.iomux.pad_gpioa_cfg_reg[idx];
        AIC_IOMUX->pad_agpio_cfg_reg[idx] = gpio_registiers.iomux.pad_agpio_cfg_reg[idx];
        if (idx < GPIOB_IDX_MAX) {
            AIC_IOMUX->pad_gpiob_cfg_reg[idx] = gpio_registiers.iomux.pad_gpiob_cfg_reg[idx];
        }
    }
    AIC_GPIOA->MR   = gpio_registiers.gpioa.MR;
    AIC_GPIOA->VR   = gpio_registiers.gpioa.VR;
    AIC_GPIOA->DR   = gpio_registiers.gpioa.DR;
    AIC_GPIOA->TELR = gpio_registiers.gpioa.TELR;
    AIC_GPIOA->TER  = gpio_registiers.gpioa.TER;
    AIC_GPIOA->TLR  = gpio_registiers.gpioa.TLR;
    AIC_GPIOA->ICR  = gpio_registiers.gpioa.ICR;
    AIC_GPIOA->TIR  = gpio_registiers.gpioa.TIR;
    AIC_GPIOA->FR   = gpio_registiers.gpioa.FR;
    AIC_GPIOB->MR   = gpio_registiers.gpiob.MR;
    AIC_GPIOB->VR   = gpio_registiers.gpiob.VR;
    AIC_GPIOB->DR   = gpio_registiers.gpiob.DR;
    AIC_GPIOB->TELR = gpio_registiers.gpiob.TELR;
    AIC_GPIOB->TER  = gpio_registiers.gpiob.TER;
    AIC_GPIOB->TLR  = gpio_registiers.gpiob.TLR;
    AIC_GPIOB->ICR  = gpio_registiers.gpiob.ICR;
    AIC_GPIOB->TIR  = gpio_registiers.gpiob.TIR;
    AIC_GPIOB->FR   = gpio_registiers.gpiob.FR;
    // recover sel
    anareg1_gpiob_func_mux_sel_clrb();
    #if PLF_PMIC
    pmic_gpio_hold_config(0);
    #endif
}
