#ifndef _REG_ANAREG_H_
#define _REG_ANAREG_H_

#include "chip.h"

/* ================================================================================ */
/* ================                     ANAREG0                    ================ */
/* ================================================================================ */
typedef struct {
  __IO uint32_t                          flash_pad_pull;               //0x00000000
} AIC_ANAREG0_TypeDef;

static AIC_ANAREG0_TypeDef * const AIC_ANAREG0 = ((AIC_ANAREG0_TypeDef *)AIC_ANAR0_BASE);

//flash_pad_pull
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_PULL_DN(n)      (((n)&15)<<0)
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_PULL_DN_LSB     (0)
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_PULL_DN_MASK    (15<<0)
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_PULL_UP(n)      (((n)&15)<<4)
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_PULL_UP_LSB     (4)
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_PULL_UP_MASK    (15<<4)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CS_PULL_DN      (1<<8)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CS_PULL_DN_POS  (8)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CS_PULL_UP      (1<<9)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CS_PULL_UP_POS  (9)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CLK_PULL_DN      (1<<10)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CLK_PULL_DN_POS  (10)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CLK_PULL_UP      (1<<11)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CLK_PULL_UP_POS  (11)

/* ================================================================================ */
/* ================                     ANAREG1                    ================ */
/* ================================================================================ */
typedef struct {
  __IO uint32_t                          gpioa_cfg;                    //0x00000000
  __IO uint32_t                          gpiob_cfg1;                   //0x00000004
  __IO uint32_t                          gpiob_cfg2;                   //0x00000008
  __IO uint32_t                          agpio_cfg;                    //0x0000000C
  __IO uint32_t Reserved_00000010[2];                 //0x00000010
  __IO uint32_t                          ana_port_ctrl;                //0x00000018
  __IO uint32_t                          misc_reg;                     //0x0000001C
  __IO uint32_t                          flash_ctrl;                   //0x00000020
  __IO uint32_t                          ana_bit_rd_back;              //0x00000024
} AIC_ANAREG1_TypeDef;

static AIC_ANAREG1_TypeDef * const AIC_ANAREG1 = ((AIC_ANAREG1_TypeDef *)AIC_ANAR1_BASE);

//gpioa_cfg
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IBIT(n)      (((n)&7)<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IBIT_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IBIT_MASK    (7<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_PULL_UP_SEL(n)      (((n)&7)<<3)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_PULL_UP_SEL_LSB     (3)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_PULL_UP_SEL_MASK    (7<<3)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_SLEW_RATE(n)      (((n)&0x3F)<<6)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_SLEW_RATE_LSB     (6)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_SLEW_RATE_MASK    (0x3F<<6)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IE      (1<<12)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IE_POS  (12)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_MUX_EN      (1<<13)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_MUX_EN_POS  (13)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_MUX_ENB      (1<<14)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_MUX_ENB_POS  (14)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_WAKEUP_POLARITY(n)      (((n)&0xFFFF)<<16)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_WAKEUP_POLARITY_LSB     (16)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_WAKEUP_POLARITY_MASK    (0xFFFF<<16)

//gpiob_cfg1
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IBIT(n)      (((n)&3)<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IBIT_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IBIT_MASK    (3<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_PULL_UP_SEL(n)      (((n)&3)<<2)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_PULL_UP_SEL_LSB     (2)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_PULL_UP_SEL_MASK    (3<<2)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_EN      (1<<5)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_EN_POS  (5)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_ENB      (1<<6)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_ENB_POS  (6)
#define ANALOG_REG1_RF_CFG_GPIOB_FUNC_MUX_SEL      (1<<7)
#define ANALOG_REG1_RF_CFG_GPIOB_FUNC_MUX_SEL_POS  (7)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_WAKEUP_POLARITY(n)      (((n)&0xFF)<<8)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_WAKEUP_POLARITY_LSB     (8)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_WAKEUP_POLARITY_MASK    (0xFF<<8)
#define ANALOG_REG1_RF_CFG_GPIOB_PULL_UP_INT(n)      (((n)&0xFF)<<16)
#define ANALOG_REG1_RF_CFG_GPIOB_PULL_UP_INT_LSB     (16)
#define ANALOG_REG1_RF_CFG_GPIOB_PULL_UP_INT_MASK    (0xFF<<16)
#define ANALOG_REG1_RF_CFG_GPIOB_PULL_DN_INT(n)      (((n)&0xFF)<<24)
#define ANALOG_REG1_RF_CFG_GPIOB_PULL_DN_INT_LSB     (24)
#define ANALOG_REG1_RF_CFG_GPIOB_PULL_DN_INT_MASK    (0xFF<<24)

//gpiob_cfg2
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_SLEW_RATE(n)      (((n)&15)<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_SLEW_RATE_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_SLEW_RATE_MASK    (15<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IE(n)      (((n)&3)<<4)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IE_LSB     (4)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IE_MASK    (3<<4)

//agpio_cfg
#define ANALOG_REG1_RF_CFG_ANA_AGPIO_IBIT      (1<<0)
#define ANALOG_REG1_RF_CFG_ANA_AGPIO_IBIT_POS  (0)
#define ANALOG_REG1_RF_CFG_ANA_AGPIO_IE      (1<<8)
#define ANALOG_REG1_RF_CFG_ANA_AGPIO_IE_POS  (8)

//ana_port_ctrl
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_USB      (1<<0)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_USB_POS  (0)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_PCIE      (1<<1)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_PCIE_POS  (1)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_IREF_IO      (1<<2)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_IREF_IO_POS  (2)
#define ANALOG_REG1_RF_CFG_ANA_PU_IREF_IO      (1<<5)
#define ANALOG_REG1_RF_CFG_ANA_PU_IREF_IO_POS  (5)
#define ANALOG_REG1_RF_CFG_ANA_IREF_IO_START_ENB      (1<<6)
#define ANALOG_REG1_RF_CFG_ANA_IREF_IO_START_ENB_POS  (6)
#define ANALOG_REG1_RF_CFG_ANA_PMIC_INT_PULL_DN      (1<<7)
#define ANALOG_REG1_RF_CFG_ANA_PMIC_INT_PULL_DN_POS  (7)
#define ANALOG_REG1_RF_CFG_ANA_PMIC_INT_PULL_UP      (1<<8)
#define ANALOG_REG1_RF_CFG_ANA_PMIC_INT_PULL_UP_POS  (8)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_PCIE_PLL      (1<<9)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_PCIE_PLL_POS  (9)
#define ANALOG_REG1_RF_CFG_ANA_GPIO_VIO13_SLEEP_MODE      (1<<10)
#define ANALOG_REG1_RF_CFG_ANA_GPIO_VIO13_SLEEP_MODE_POS  (10)
#define ANALOG_REG1_RF_CFG_ANA_IO_TEST_BIT(n)      (((n)&15)<<11)
#define ANALOG_REG1_RF_CFG_ANA_IO_TEST_BIT_LSB     (11)
#define ANALOG_REG1_RF_CFG_ANA_IO_TEST_BIT_MASK    (15<<11)

//misc_reg
#define ANALOG_REG1_RF_CFG_ANA_IO_RSVD_BIT(n)      (((n)&0xFF)<<0)
#define ANALOG_REG1_RF_CFG_ANA_IO_RSVD_BIT_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_IO_RSVD_BIT_MASK    (0xFF<<0)
#define ANALOG_REG1_RF_CFG_ANA_XTAL2AUD_IBIT      (1<<8)
#define ANALOG_REG1_RF_CFG_ANA_XTAL2AUD_IBIT_POS  (8)
#define ANALOG_REG1_RF_CFG_XTAL2AUD_EN      (1<<9)
#define ANALOG_REG1_RF_CFG_XTAL2AUD_EN_POS  (9)
#define ANALOG_REG1_RF_CFG_ANA_PWRKEY2AUD_I      (1<<10)
#define ANALOG_REG1_RF_CFG_ANA_PWRKEY2AUD_I_POS  (10)
#define ANALOG_REG1_RF_CFG_ANA_PWRKEY2AUD_OEN      (1<<11)
#define ANALOG_REG1_RF_CFG_ANA_PWRKEY2AUD_OEN_POS  (11)
#define ANALOG_REG1_RF_PMU_PSI_SLV_RDATA_WAIT_TIMEOUT_ERR      (1<<12)
#define ANALOG_REG1_RF_PMU_PSI_SLV_RDATA_WAIT_TIMEOUT_ERR_POS  (12)
#define ANALOG_REG1_RF_PSI_MST_SIG_EVENT(n)      (((n)&0xFF)<<13)
#define ANALOG_REG1_RF_PSI_MST_SIG_EVENT_LSB     (13)
#define ANALOG_REG1_RF_PSI_MST_SIG_EVENT_MASK    (0xFF<<13)
#define ANALOG_REG1_RF_CFG_ANA_RSVD_BIT_CORE(n)      (((n)&15)<<21)
#define ANALOG_REG1_RF_CFG_ANA_RSVD_BIT_CORE_LSB     (21)
#define ANALOG_REG1_RF_CFG_ANA_RSVD_BIT_CORE_MASK    (15<<21)
#define ANALOG_REG1_RF_CFG_BT_BBPLL_AUTO_PU      (1<<25)
#define ANALOG_REG1_RF_CFG_BT_BBPLL_AUTO_PU_POS  (25)
#define ANALOG_REG1_RF_CFG_ANA_CHIP_SLEEP_I_EN      (1<<26)
#define ANALOG_REG1_RF_CFG_ANA_CHIP_SLEEP_I_EN_POS  (26)

//flash_ctrl
#define ANALOG_REG1_RF_CFG_ANA_FLS_IE      (1<<0)
#define ANALOG_REG1_RF_CFG_ANA_FLS_IE_POS  (0)
#define ANALOG_REG1_RF_CFG_ANA_FLS_IBIT      (1<<1)
#define ANALOG_REG1_RF_CFG_ANA_FLS_IBIT_POS  (1)
#define ANALOG_REG1_RF_CFG_ANA_FLS_PULL_UP_SEL      (1<<2)
#define ANALOG_REG1_RF_CFG_ANA_FLS_PULL_UP_SEL_POS  (2)
#define ANALOG_REG1_RF_CFG_ANA_FLS_SLEW_RATE(n)      (((n)&3)<<3)
#define ANALOG_REG1_RF_CFG_ANA_FLS_SLEW_RATE_LSB     (3)
#define ANALOG_REG1_RF_CFG_ANA_FLS_SLEW_RATE_MASK    (3<<3)
#define ANALOG_REG1_RF_CFG_ANA_FLS_MS      (1<<5)
#define ANALOG_REG1_RF_CFG_ANA_FLS_MS_POS  (5)

//ana_bit_rd_back
#define ANALOG_REG1_RF_PMU_RSVD_READ_BIT_RTC1(n)      (((n)&15)<<0)
#define ANALOG_REG1_RF_PMU_RSVD_READ_BIT_RTC1_LSB     (0)
#define ANALOG_REG1_RF_PMU_RSVD_READ_BIT_RTC1_MASK    (15<<0)
#define ANALOG_REG1_RF_PMU_RSVD_READ_BIT_CORE(n)      (((n)&15)<<4)
#define ANALOG_REG1_RF_PMU_RSVD_READ_BIT_CORE_LSB     (4)
#define ANALOG_REG1_RF_PMU_RSVD_READ_BIT_CORE_MASK    (15<<4)
#define ANALOG_REG1_RF_IO_RSVD_READ_BIT(n)      (((n)&15)<<8)
#define ANALOG_REG1_RF_IO_RSVD_READ_BIT_LSB     (8)
#define ANALOG_REG1_RF_IO_RSVD_READ_BIT_MASK    (15<<8)


__STATIC_INLINE uint8_t anareg1_gpiob_func_mux_sel_getb(void)
{
    return ((AIC_ANAREG1->gpiob_cfg1 & ANALOG_REG1_RF_CFG_GPIOB_FUNC_MUX_SEL) >> ANALOG_REG1_RF_CFG_GPIOB_FUNC_MUX_SEL_POS);
}

__STATIC_INLINE void anareg1_gpiob_func_mux_sel_setb(void)
{
    AIC_ANAREG1->gpiob_cfg1 |= ANALOG_REG1_RF_CFG_GPIOB_FUNC_MUX_SEL;
}

__STATIC_INLINE void anareg1_gpiob_func_mux_sel_clrb(void)
{
    AIC_ANAREG1->gpiob_cfg1 &= ~ANALOG_REG1_RF_CFG_GPIOB_FUNC_MUX_SEL;
}

__STATIC_INLINE uint8_t anareg1_gpiob_pull_up_int_getb(int gp_idx)
{
    return ((AIC_ANAREG1->gpiob_cfg1 & ANALOG_REG1_RF_CFG_GPIOB_PULL_UP_INT(0x01UL << gp_idx)) >> (ANALOG_REG1_RF_CFG_GPIOB_PULL_UP_INT_LSB + gp_idx));
}

__STATIC_INLINE void anareg1_gpiob_pull_up_int_setb(int gp_idx)
{
    AIC_ANAREG1->gpiob_cfg1 |= ANALOG_REG1_RF_CFG_GPIOB_PULL_UP_INT(0x01UL << gp_idx);
}

__STATIC_INLINE void anareg1_gpiob_pull_up_int_clrb(int gp_idx)
{
    AIC_ANAREG1->gpiob_cfg1 &= ~(ANALOG_REG1_RF_CFG_GPIOB_PULL_UP_INT(0x01UL << gp_idx));
}

__STATIC_INLINE uint8_t anareg1_gpiob_pull_dn_int_getb(int gp_idx)
{
    return ((AIC_ANAREG1->gpiob_cfg1 & ANALOG_REG1_RF_CFG_GPIOB_PULL_DN_INT(0x01UL << gp_idx)) >> (ANALOG_REG1_RF_CFG_GPIOB_PULL_DN_INT_LSB + gp_idx));
}

__STATIC_INLINE void anareg1_gpiob_pull_dn_int_setb(int gp_idx)
{
    AIC_ANAREG1->gpiob_cfg1 |= ANALOG_REG1_RF_CFG_GPIOB_PULL_DN_INT(0x01UL << gp_idx);
}

__STATIC_INLINE void anareg1_gpiob_pull_dn_int_clrb(int gp_idx)
{
    AIC_ANAREG1->gpiob_cfg1 &= ~(ANALOG_REG1_RF_CFG_GPIOB_PULL_DN_INT(0x01UL << gp_idx));
}


#endif /* _REG_ANAREG_H_ */
