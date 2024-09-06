#ifndef _REG_ANAREG_H_
#define _REG_ANAREG_H_

#include "chip.h"

/* ================================================================================ */
/* ================                     ANAREG0                    ================ */
/* ================================================================================ */
typedef struct {
  __IO uint32_t                     asdma_pad_reg;                //0x00000000
  __IO uint32_t                     ddr_pad_reg;                  //0x00000004
  __IO uint32_t                     opi_pad_reg;                  //0x00000008
  __IO uint32_t                     flash_pad_reg;                //0x0000000C
  __IO uint32_t                     misc_reg0;                    //0x00000010
  __IO uint32_t                     misc_reg1;                    //0x00000014
  __IO uint32_t                     misc_reg2;                    //0x00000018
} AIC_ANAREG0_TypeDef;

static AIC_ANAREG0_TypeDef * const AIC_ANAREG0 = ((AIC_ANAREG0_TypeDef *)AIC_ANAR0_BASE);


//asdio_pad_reg
#define ANALOG_REG0_RF_CFG_ANA_ASDMA_DATA_SLEW_RATE(n) (((n)&0xFF)<<0)
#define ANALOG_REG0_RF_CFG_ANA_ASDMA_DATA_PULLUP_BIT(n) (((n)&0xFF)<<8)
#define ANALOG_REG0_RF_CFG_ANA_ASDMA_DATA_IBIT(n) (((n)&15)<<16)
#define ANALOG_REG0_RF_CFG_ANA_ASDMA_CMD_SLEW_RATE(n) (((n)&3)<<20)
#define ANALOG_REG0_RF_CFG_ANA_ASDMA_CMD_PULLUP_BIT(n) (((n)&3)<<22)
#define ANALOG_REG0_RF_CFG_ANA_ASDMA_CMD_IBIT (1<<24)
#define ANALOG_REG0_RF_CFG_ANA_ASDMA_CLK_SLEW_RATE(n) (((n)&3)<<25)
#define ANALOG_REG0_RF_CFG_ANA_ASDMA_CLK_PULLUP_BIT(n) (((n)&3)<<27)
#define ANALOG_REG0_RF_CFG_ANA_ASDMA_CLK_IBIT (1<<29)

//ddr_pad_reg
#define ANALOG_REG0_RF_CFG_ANA_DDR_DQ_IE(n) (((n)&0xFF)<<0)
#define ANALOG_REG0_RF_CFG_ANA_DDR_DQS_IE (1<<8)
#define ANALOG_REG0_RF_CFG_ANA_DDR_DM_IE (1<<9)
#define ANALOG_REG0_RF_CFG_ANA_DDR_CE_IE (1<<10)
#define ANALOG_REG0_RF_CFG_ANA_DDR_CLK_IE (1<<11)
#define ANALOG_REG0_RF_CFG_ANA_DDR_DRV(n) (((n)&31)<<12)
#define ANALOG_REG0_RF_CFG_ANA_DDR_PD (1<<17)
#define ANALOG_REG0_RF_CFG_ANA_DDR_PU (1<<18)
#define ANALOG_REG0_RF_CFG_ANA_DDR_PU_RX (1<<19)

//opi_pad_reg
#define ANALOG_REG0_RF_CFG_ANA_OPI_DQ_IE(n) (((n)&0xFF)<<0)
#define ANALOG_REG0_RF_CFG_ANA_OPI_DQS_IE (1<<8)
#define ANALOG_REG0_RF_CFG_ANA_OPI_DM_IE (1<<9)
#define ANALOG_REG0_RF_CFG_ANA_OPI_CE_IE (1<<10)
#define ANALOG_REG0_RF_CFG_ANA_OPI_CLK_IE (1<<11)
#define ANALOG_REG0_RF_CFG_ANA_OPI_DRV(n) (((n)&31)<<12)
#define ANALOG_REG0_RF_CFG_ANA_OPI_PD (1<<17)
#define ANALOG_REG0_RF_CFG_ANA_OPI_PU (1<<18)
#define ANALOG_REG0_RF_CFG_ANA_OPI_PU_RX (1<<19)
#define ANALOG_REG0_RF_CFG_ANA_OPI_CE_PD (1<<20)
#define ANALOG_REG0_RF_CFG_ANA_OPI_CE_PU (1<<21)

//flash_pad_reg
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_PULL_DN(n) (((n)&15)<<0)
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_PULL_UP(n) (((n)&15)<<4)
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_SLEW_RATE(n) (((n)&0xFF)<<8)
#define ANALOG_REG0_RF_CFG_ANA_FLS_SIO_IBIT(n) (((n)&15)<<16)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CS_PULL_DN (1<<20)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CS_PULL_UP (1<<21)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CS_SLEW_RATE(n) (((n)&3)<<22)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CS_IBIT (1<<24)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CLK_PULL_DN (1<<25)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CLK_PULL_UP (1<<26)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CLK_SLEW_RATE(n) (((n)&3)<<27)
#define ANALOG_REG0_RF_CFG_ANA_FLS_CLK_IBIT (1<<29)

//misc_reg0
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_DQ_I(n) (((n)&0xFF)<<0)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_DQ_C(n) (((n)&0xFF)<<8)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_DM_I (1<<16)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_DM_C (1<<17)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_CE_I (1<<18)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_CE_C (1<<19)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_DQS_I (1<<20)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_DQS_C (1<<21)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_CLK_I (1<<22)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_DDR_CLK_C (1<<23)

//misc_reg1
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_DQ_I(n) (((n)&0xFF)<<0)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_DQ_C(n) (((n)&0xFF)<<8)
#define ANALOG_REG0_RF_CFG_ANA_TEST_AC_ENABLE_MEM (1<<16)
#define ANALOG_REG0_RF_CFG_ANATEST_AC_ENABLE_RF (1<<17)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_RF (1<<18)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_DQS_I (1<<19)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_DQS_C (1<<20)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_DM_I (1<<21)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_DM_C (1<<22)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_CE_I (1<<23)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_CE_C (1<<24)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_CLK_I (1<<25)
#define ANALOG_REG0_RF_CFG_ANA_TEST_ENABLE_OPI_CLK_C (1<<26)


/* ================================================================================ */
/* ================                     ANAREG1                    ================ */
/* ================================================================================ */
typedef struct {
  __IO uint32_t                     psram_hold;                   //0x00000000
  __IO uint32_t                     agpio_ibit;                   //0x00000004
  __IO uint32_t                     agpio_oen_dly;                //0x00000008
  __IO uint32_t                     agpio_slew_rate;              //0x0000000C
  __IO uint32_t                     gpio_ibit;                    //0x00000010
  __IO uint32_t                     gpio_slew_rata;               //0x00000014
  __IO uint32_t                     gpio_mode;                    //0x00000018
  __IO uint32_t                     ana_port_ctrl;                //0x0000001C
  __IO uint32_t                     pad_hold;                     //0x00000020
  __IO uint32_t                     fls_ms;                       //0x00000024
  __IO uint32_t                     misc_reg;                     //0x00000028
} AIC_ANAREG1_TypeDef;

static AIC_ANAREG1_TypeDef * const AIC_ANAREG1 = ((AIC_ANAREG1_TypeDef *)AIC_ANAR1_BASE);


//psram_hold
#define ANALOG_REG1_RF_CFG_ANA_OPI_HOLD (1<<0)
#define ANALOG_REG1_RF_CFG_ANA_DDR_HOLD (1<<1)

//agpio_ibit
#define ANALOG_REG1_RF_CFG_ANA_AGPIO_IBIT(n) (((n)&0xFFFF)<<0)

//agpio_oen_dly
#define ANALOG_REG1_RF_CFG_ANA_AGPIO_OEN_DLY(n) (((n)&0xFFFFFFFF)<<0)

//agpio_slew_rate
#define ANALOG_REG1_RF_CFG_ANA_AGPIO_SLEW_RATE(n) (((n)&0xFFFFFFFF)<<0)

//gpio_ibit
#define ANALOG_REG1_RF_CFG_ANA_GPIO_IBIT(n) (((n)&0xFFFF)<<0)

//gpio_slew_rata
#define ANALOG_REG1_RF_CFG_ANA_GPIO_SLEW_RATE(n) (((n)&0xFFFFFFFF)<<0)

//gpio_mode
#define ANALOG_REG1_RF_CFG_ANA_GPIO_MS (1<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIO_XEN_MODE (1<<1)

//ana_port_ctrl
#define ANALOG_REG1_RF_CFG_ANA_ANAPORT_ENABLE(n) (((n)&7)<<0)
#define ANALOG_REG1_RF_CFG_ANA_PU_ANAPORT_V2I (1<<4)

//pad_hold
#define ANALOG_REG1_RF_CFG_ANA_GPIO0_HOLD (1<<0)
#define ANALOG_REG1_RF_CFG_ANA_GPIO1_HOLD (1<<1)
#define ANALOG_REG1_RF_CFG_ANA_GPIO2_HOLD (1<<2)
#define ANALOG_REG1_RF_CFG_ANA_GPIO3_HOLD (1<<3)
#define ANALOG_REG1_RF_CFG_ANA_ASDIO_HOLD (1<<4)
#define ANALOG_REG1_RF_CFG_ANA_AGPIO_HOLD (1<<5)
#define ANALOG_REG1_RF_CFG_ANA_FLS_HOLD (1<<6)

//fls_ms
#define ANALOG_REG1_RF_CFG_ANA_FLS_MS (1<<0)

#endif /* _REG_ANAREG_H_ */
