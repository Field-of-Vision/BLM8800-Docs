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
  __IO uint32_t                          gpioa_ibit;                   //0x00000000
  __IO uint32_t                          gpioa_slew_rate;              //0x00000004
  __IO uint32_t                          gpioa_ie;                     //0x00000008
  __IO uint32_t                          gpiob_ibit;                   //0x0000000C
  __IO uint32_t                          gpiob_slew_rata;              //0x00000010
  __IO uint32_t                          gpiob_ie;                     //0x00000014
  __IO uint32_t                          ana_port_ctrl;                //0x00000018
  __IO uint32_t                          misc_reg;                     //0x0000001C
  __IO uint32_t                          flash_ctrl;                   //0x00000020
} AIC_ANAREG1_TypeDef;

static AIC_ANAREG1_TypeDef * const AIC_ANAREG1 = ((AIC_ANAREG1_TypeDef *)AIC_ANAR1_BASE);

//gpioa_ibit
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IBIT(n)      (((n)&7)<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IBIT_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IBIT_MASK    (7<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_WAKEUP_POLARITY(n)      (((n)&0xFFFF)<<16)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_WAKEUP_POLARITY_LSB     (16)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_WAKEUP_POLARITY_MASK    (0xFFFF<<16)

//gpioa_slew_rate
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_SLEW_RATE(n)      (((n)&0x3F)<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_SLEW_RATE_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_SLEW_RATE_MASK    (0x3F<<0)

//gpioa_ie
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IE(n)      (((n)&3)<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IE_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_IE_MASK    (3<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_PULL_UP_SEL(n)      (((n)&7)<<16)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_PULL_UP_SEL_LSB     (16)
#define ANALOG_REG1_RF_CFG_ANA_GPIOA_PULL_UP_SEL_MASK    (7<<16)

//gpiob_ibit
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IBIT      (1<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IBIT_POS  (0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_WAKEUP_POLARITY(n)      (((n)&15)<<28)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_WAKEUP_POLARITY_LSB     (28)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_WAKEUP_POLARITY_MASK    (15<<28)

//gpiob_slew_rata
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_SLEW_RATE(n)      (((n)&3)<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_SLEW_RATE_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_SLEW_RATE_MASK    (3<<0)

//gpiob_ie
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IE      (1<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_IE_POS  (0)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_PULL_UP_SEL      (1<<16)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_PULL_UP_SEL_POS  (16)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_ENB      (1<<17)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_ENB_POS  (17)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_EN      (1<<18)
#define ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_EN_POS  (18)

//ana_port_ctrl
#define ANALOG_REG1_RF_CFG_ANA_TEST_BIT(n)      (((n)&15)<<0)
#define ANALOG_REG1_RF_CFG_ANA_TEST_BIT_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_TEST_BIT_MASK    (15<<0)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_USB      (1<<4)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_USB_POS  (4)
#define ANALOG_REG1_RF_CFG_ANA_IO_IREF_CURRENT_START_ENB      (1<<5)
#define ANALOG_REG1_RF_CFG_ANA_IO_IREF_CURRENT_START_ENB_POS  (5)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_IREF_IO      (1<<6)
#define ANALOG_REG1_RF_CFG_ANA_TEST_ENABLE_IREF_IO_POS  (6)
#define ANALOG_REG1_RF_CFG_ANA_TESTPORT_IQ_ENB      (1<<7)
#define ANALOG_REG1_RF_CFG_ANA_TESTPORT_IQ_ENB_POS  (7)
#define ANALOG_REG1_RF_CFG_ANA_TESTPORT_IQ_EN      (1<<8)
#define ANALOG_REG1_RF_CFG_ANA_TESTPORT_IQ_EN_POS  (8)
#define ANALOG_REG1_RF_CFG_ANA_PU_IREF_IO      (1<<9)
#define ANALOG_REG1_RF_CFG_ANA_PU_IREF_IO_POS  (9)
#define ANALOG_REG1_RF_CFG_ANA_GPIO_VIO13_SLEEP_MODE      (1<<11)
#define ANALOG_REG1_RF_CFG_ANA_GPIO_VIO13_SLEEP_MODE_POS  (11)
#define ANALOG_REG1_RF_CFG_ANA_IO_TEST_ENABLE_BBPLL      (1<<12)
#define ANALOG_REG1_RF_CFG_ANA_IO_TEST_ENABLE_BBPLL_POS  (12)

//misc_reg
#define ANALOG_REG1_RF_CFG_ANA_IO_RSVD_BIT(n)      (((n)&0xFF)<<0)
#define ANALOG_REG1_RF_CFG_ANA_IO_RSVD_BIT_LSB     (0)
#define ANALOG_REG1_RF_CFG_ANA_IO_RSVD_BIT_MASK    (0xFF<<0)
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

#endif /* _REG_ANAREG_H_ */
