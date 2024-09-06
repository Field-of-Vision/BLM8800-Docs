#ifndef _REG_IOMUX_H_
#define _REG_IOMUX_H_

#include "chip.h"

/* ================================================================================ */
/* ================                      IOMUX                     ================ */
/* ================================================================================ */
typedef struct {
  union {
    __IO uint32_t pad_gpioa_cfg_reg[16]; //0x00000000
    struct {
      __IO uint32_t                     pad_gpioa_0_cfg_reg;          //0x00000000
      __IO uint32_t                     pad_gpioa_1_cfg_reg;          //0x00000004
      __IO uint32_t                     pad_gpioa_2_cfg_reg;          //0x00000008
      __IO uint32_t                     pad_gpioa_3_cfg_reg;          //0x0000000C
      __IO uint32_t                     pad_gpioa_4_cfg_reg;          //0x00000010
      __IO uint32_t                     pad_gpioa_5_cfg_reg;          //0x00000014
      __IO uint32_t                     pad_gpioa_6_cfg_reg;          //0x00000018
      __IO uint32_t                     pad_gpioa_7_cfg_reg;          //0x0000001C
      __IO uint32_t                     pad_gpioa_8_cfg_reg;          //0x00000020
      __IO uint32_t                     pad_gpioa_9_cfg_reg;          //0x00000024
      __IO uint32_t                     pad_gpioa_10_cfg_reg;         //0x00000028
      __IO uint32_t                     pad_gpioa_11_cfg_reg;         //0x0000002C
      __IO uint32_t                     pad_gpioa_12_cfg_reg;         //0x00000030
      __IO uint32_t                     pad_gpioa_13_cfg_reg;         //0x00000034
      __IO uint32_t                     pad_gpioa_14_cfg_reg;         //0x00000038
      __IO uint32_t                     pad_gpioa_15_cfg_reg;         //0x0000003C
    };
  };
  union {
    __IO uint32_t pad_gpiob_cfg_reg[4]; //0x00000040
    struct {
      __IO uint32_t                     pad_gpiob_0_cfg_reg;          //0x00000040
      __IO uint32_t                     pad_gpiob_1_cfg_reg;          //0x00000044
      __IO uint32_t                     pad_gpiob_2_cfg_reg;          //0x00000048
      __IO uint32_t                     pad_gpiob_3_cfg_reg;          //0x0000004C
    };
  };
} AIC_IOMUX_TypeDef;

static AIC_IOMUX_TypeDef * const AIC_IOMUX = ((AIC_IOMUX_TypeDef *)AIC_IOMUX_BASE);

//pad_gpioa_0_cfg_reg
#define IOMUX_PAD_GPIOA_0_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_0_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_0_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_0_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_0_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_0_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_0_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_0_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_0_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_0_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_0_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_0_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_0_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_0_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_0_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_0_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_0_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_0_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_0_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_0_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_0_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_0_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_0_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_0_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_0_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_CPU_P_SWCLK_SEL (0<<0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_GPIOA_0_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_GPIOA_0_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_I2CM_SCL_SEL (2<<0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_DEBUG_CLK_SEL (3<<0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_I2S_LRCK_0_SEL (4<<0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_PCM_FSYNC_SEL (5<<0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_SPI_LCD_SCK_SEL (6<<0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_TPORTS0_SEL (7<<0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_PSI_M_SCL_SEL (8<<0)
#define IOMUX_PAD_GPIOA_0_SEL_FUN_WF_EXT_PA_CTRL_0_SEL (9<<0)

//pad_gpioa_1_cfg_reg
#define IOMUX_PAD_GPIOA_1_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_1_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_1_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_1_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_1_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_1_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_1_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_1_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_1_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_1_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_1_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_1_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_1_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_1_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_1_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_1_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_1_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_1_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_1_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_1_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_1_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_1_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_1_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_1_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_1_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_CPU_P_SWD_SEL (0<<0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_GPIOA_1_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_GPIOA_1_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_I2CM_SDA_SEL (2<<0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_AON_UART_TX_SEL (3<<0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_I2S_BCK_0_SEL (4<<0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_PCM_CLK_SEL (5<<0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_SPI_LCD_CSN_0_SEL (6<<0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_TPORTS1_SEL (7<<0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_PSI_M_SDA_SEL (8<<0)
#define IOMUX_PAD_GPIOA_1_SEL_FUN_WF_EXT_PA_CTRL_1_SEL (9<<0)

//pad_gpioa_2_cfg_reg
#define IOMUX_PAD_GPIOA_2_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_2_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_2_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_2_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_2_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_2_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_2_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_2_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_2_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_2_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_2_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_2_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_2_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_2_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_2_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_2_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_2_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_2_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_2_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_2_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_2_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_2_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_2_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_2_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_2_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_GPIOA_2_SEL (0<<0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_UART0_RX_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_UART0_RX_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_UART1_RX_SEL (2<<0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_I2CM_SCL_SEL (3<<0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_I2S_DAT_IN_0_SEL (4<<0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_PCM_DIN_SEL (5<<0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_SPI_LCD_DI_SEL (6<<0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_TPORTS2_SEL (7<<0)
#define IOMUX_PAD_GPIOA_2_SEL_FUN_WF_EXT_PA_CTRL_2_SEL (9<<0)

//pad_gpioa_3_cfg_reg
#define IOMUX_PAD_GPIOA_3_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_3_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_3_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_3_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_3_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_3_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_3_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_3_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_3_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_3_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_3_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_3_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_3_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_3_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_3_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_3_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_3_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_3_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_3_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_3_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_3_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_3_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_3_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_3_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_3_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_GPIOA_3_SEL (0<<0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_UART0_TX_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_UART0_TX_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_UART1_TX_SEL (2<<0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_I2CM_SDA_SEL (3<<0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_I2S_DAT_OUT_0_SEL (4<<0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_PCM_DOUT_SEL (5<<0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_SPI_LCD_DO_SEL (6<<0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_TPORTS3_SEL (7<<0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_MBIST_CLOCK_SEL (8<<0)
#define IOMUX_PAD_GPIOA_3_SEL_FUN_WF_EXT_PA_CTRL_3_SEL (9<<0)

//pad_gpioa_4_cfg_reg
#define IOMUX_PAD_GPIOA_4_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_4_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_4_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_4_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_4_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_4_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_4_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_4_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_4_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_4_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_4_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_4_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_4_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_4_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_4_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_4_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_4_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_4_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_4_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_4_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_4_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_4_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_4_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_4_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_4_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_GPIOA_4_SEL (0<<0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_UART0_CTS_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_UART0_CTS_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_UART1_CTS_SEL (2<<0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_UART1_RX_SEL (3<<0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_CODEC_MCLK_SEL (4<<0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_PWM_0_SEL (5<<0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_SPI_LCD_CD_SEL (6<<0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_TPORTS4_SEL (7<<0)
#define IOMUX_PAD_GPIOA_4_SEL_FUN_DFT_JTAG_TCK_SEL (8<<0)

//pad_gpioa_5_cfg_reg
#define IOMUX_PAD_GPIOA_5_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_5_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_5_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_5_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_5_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_5_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_5_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_5_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_5_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_5_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_5_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_5_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_5_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_5_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_5_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_5_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_5_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_5_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_5_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_5_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_5_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_5_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_5_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_5_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_5_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_GPIOA_5_SEL (0<<0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_UART0_RTS_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_UART0_RTS_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_UART1_RTS_SEL (2<<0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_UART1_TX_SEL (3<<0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_DEBUG_CLK_SEL (4<<0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_PWM_1_SEL (5<<0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_SPI_LCD_FMARK_SEL (6<<0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_TPORTS5_SEL (7<<0)
#define IOMUX_PAD_GPIOA_5_SEL_FUN_DFT_JTAG_TRST_SEL (8<<0)

//pad_gpioa_6_cfg_reg
#define IOMUX_PAD_GPIOA_6_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_6_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_6_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_6_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_6_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_6_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_6_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_6_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_6_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_6_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_6_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_6_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_6_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_6_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_6_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_6_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_6_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_6_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_6_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_6_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_6_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_6_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_6_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_6_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_6_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_6_SEL_FUN_GPIOA_6_SEL (0<<0)
#define IOMUX_PAD_GPIOA_6_SEL_FUN_I2CM_SCL_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_6_SEL_FUN_I2CM_SCL_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_6_SEL_FUN_UART2_RX_SEL (2<<0)
#define IOMUX_PAD_GPIOA_6_SEL_FUN_UART1_CTS_SEL (3<<0)
#define IOMUX_PAD_GPIOA_6_SEL_FUN_AON_PWM_0_SEL (4<<0)
#define IOMUX_PAD_GPIOA_6_SEL_FUN_I2S_BCK_0_SEL (5<<0)
#define IOMUX_PAD_GPIOA_6_SEL_FUN_SPI_LCD_CSN_1_SEL (6<<0)
#define IOMUX_PAD_GPIOA_6_SEL_FUN_TPORTS6_SEL (7<<0)

//pad_gpioa_7_cfg_reg
#define IOMUX_PAD_GPIOA_7_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_7_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_7_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_7_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_7_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_7_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_7_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_7_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_7_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_7_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_7_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_7_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_7_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_7_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_7_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_7_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_7_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_7_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_7_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_7_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_7_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_7_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_7_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_7_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_7_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_7_SEL_FUN_GPIOA_7_SEL (0<<0)
#define IOMUX_PAD_GPIOA_7_SEL_FUN_I2CM_SDA_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_7_SEL_FUN_I2CM_SDA_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_7_SEL_FUN_UART2_TX_SEL (2<<0)
#define IOMUX_PAD_GPIOA_7_SEL_FUN_UART1_RTS_SEL (3<<0)
#define IOMUX_PAD_GPIOA_7_SEL_FUN_AON_PWM_1_SEL (4<<0)
#define IOMUX_PAD_GPIOA_7_SEL_FUN_I2S_LRCK_0_SEL (5<<0)
#define IOMUX_PAD_GPIOA_7_SEL_FUN_SPI_LCD_CSN_2_SEL (6<<0)
#define IOMUX_PAD_GPIOA_7_SEL_FUN_TPORTS7_SEL (7<<0)

//pad_gpioa_8_cfg_reg
#define IOMUX_PAD_GPIOA_8_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_8_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_8_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_8_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_8_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_8_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_8_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_8_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_8_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_8_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_8_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_8_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_8_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_8_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_8_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_8_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_8_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_8_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_8_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_8_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_8_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_8_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_8_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_8_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_8_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_8_SEL_FUN_UART0_RX_SEL (0<<0)
#define IOMUX_PAD_GPIOA_8_SEL_FUN_GPIOA_8_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_8_SEL_FUN_GPIOA_8_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_8_SEL_FUN_UART2_CTS_SEL (2<<0)

//pad_gpioa_9_cfg_reg
#define IOMUX_PAD_GPIOA_9_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOA_9_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOA_9_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOA_9_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOA_9_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOA_9_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOA_9_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_9_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_9_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_9_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOA_9_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOA_9_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_9_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_9_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOA_9_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOA_9_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOA_9_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOA_9_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_9_ANA_LSB       (4)
#define IOMUX_PAD_GPIOA_9_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOA_9_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_9_SEL_LSB       (0)
#define IOMUX_PAD_GPIOA_9_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOA_9_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_9_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_9_SEL_FUN_UART0_TX_SEL (0<<0)
#define IOMUX_PAD_GPIOA_9_SEL_FUN_GPIOA_9_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_9_SEL_FUN_GPIOA_9_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_9_SEL_FUN_UART2_RTS_SEL (2<<0)
#define IOMUX_PAD_GPIOA_9_SEL_FUN_AON_PWM_2_SEL (4<<0)
#define IOMUX_PAD_GPIOA_9_SEL_FUN_I2S_DAT_OUT_0_SEL (5<<0)
#define IOMUX_PAD_GPIOA_9_SEL_FUN_SPI_LCD_CSN_3_SEL (6<<0)
#define IOMUX_PAD_GPIOA_9_SEL_FUN_TPORTS9_SEL (7<<0)

//pad_gpioa_10_cfg_reg
#define IOMUX_PAD_GPIOA_10_OEN_FRC      (1<<28)
#define IOMUX_PAD_GPIOA_10_OEN_FRC_POS  (28)
#define IOMUX_PAD_GPIOA_10_OUT_FRC      (1<<24)
#define IOMUX_PAD_GPIOA_10_OUT_FRC_POS  (24)
#define IOMUX_PAD_GPIOA_10_OUT_REG      (1<<20)
#define IOMUX_PAD_GPIOA_10_OUT_REG_POS  (20)
#define IOMUX_PAD_GPIOA_10_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_10_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_10_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_10_OEN_REG      (1<<17)
#define IOMUX_PAD_GPIOA_10_OEN_REG_POS  (17)
#define IOMUX_PAD_GPIOA_10_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_10_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_10_PULL_UP      (1<<9)
#define IOMUX_PAD_GPIOA_10_PULL_UP_POS  (9)
#define IOMUX_PAD_GPIOA_10_PULL_DN      (1<<8)
#define IOMUX_PAD_GPIOA_10_PULL_DN_POS  (8)
#define IOMUX_PAD_GPIOA_10_ANA(n)       (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_10_ANA_LSB      (4)
#define IOMUX_PAD_GPIOA_10_ANA_MASK     (15<<4)
#define IOMUX_PAD_GPIOA_10_SEL(n)       (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_10_SEL_LSB      (0)
#define IOMUX_PAD_GPIOA_10_SEL_MASK     (15<<0)
#define IOMUX_PAD_GPIOA_10_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_10_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_GPIOA_10_SEL (0<<0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_UART1_RX_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_UART1_RX_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_SPI_LCD_SCK_SEL (2<<0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_PSI_M_SCL_SEL (3<<0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_SDMMC_DATA_2_SEL (4<<0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_I2S_BCK_1_SEL (5<<0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_UART2_RX_SEL (6<<0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_TPORTS10_SEL (7<<0)
#define IOMUX_PAD_GPIOA_10_SEL_FUN_DFT_JTAG_TMS_SEL (8<<0)

//pad_gpioa_11_cfg_reg
#define IOMUX_PAD_GPIOA_11_OEN_FRC      (1<<28)
#define IOMUX_PAD_GPIOA_11_OEN_FRC_POS  (28)
#define IOMUX_PAD_GPIOA_11_OUT_FRC      (1<<24)
#define IOMUX_PAD_GPIOA_11_OUT_FRC_POS  (24)
#define IOMUX_PAD_GPIOA_11_OUT_REG      (1<<20)
#define IOMUX_PAD_GPIOA_11_OUT_REG_POS  (20)
#define IOMUX_PAD_GPIOA_11_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_11_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_11_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_11_OEN_REG      (1<<17)
#define IOMUX_PAD_GPIOA_11_OEN_REG_POS  (17)
#define IOMUX_PAD_GPIOA_11_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_11_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_11_PULL_UP      (1<<9)
#define IOMUX_PAD_GPIOA_11_PULL_UP_POS  (9)
#define IOMUX_PAD_GPIOA_11_PULL_DN      (1<<8)
#define IOMUX_PAD_GPIOA_11_PULL_DN_POS  (8)
#define IOMUX_PAD_GPIOA_11_ANA(n)       (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_11_ANA_LSB      (4)
#define IOMUX_PAD_GPIOA_11_ANA_MASK     (15<<4)
#define IOMUX_PAD_GPIOA_11_SEL(n)       (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_11_SEL_LSB      (0)
#define IOMUX_PAD_GPIOA_11_SEL_MASK     (15<<0)
#define IOMUX_PAD_GPIOA_11_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_11_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_GPIOA_11_SEL (0<<0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_UART1_TX_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_UART1_TX_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_SPI_LCD_CSN_0_SEL (2<<0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_PSI_M_SDA_SEL (3<<0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_SDMMC_DATA_3_SEL (4<<0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_I2S_LRCK_1_SEL (5<<0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_UART2_TX_SEL (6<<0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_TPORTS11_SEL (7<<0)
#define IOMUX_PAD_GPIOA_11_SEL_FUN_DFT_JTAG_TDI_SEL (8<<0)

//pad_gpioa_12_cfg_reg
#define IOMUX_PAD_GPIOA_12_OEN_FRC      (1<<28)
#define IOMUX_PAD_GPIOA_12_OEN_FRC_POS  (28)
#define IOMUX_PAD_GPIOA_12_OUT_FRC      (1<<24)
#define IOMUX_PAD_GPIOA_12_OUT_FRC_POS  (24)
#define IOMUX_PAD_GPIOA_12_OUT_REG      (1<<20)
#define IOMUX_PAD_GPIOA_12_OUT_REG_POS  (20)
#define IOMUX_PAD_GPIOA_12_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_12_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_12_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_12_OEN_REG      (1<<17)
#define IOMUX_PAD_GPIOA_12_OEN_REG_POS  (17)
#define IOMUX_PAD_GPIOA_12_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_12_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_12_PULL_UP      (1<<9)
#define IOMUX_PAD_GPIOA_12_PULL_UP_POS  (9)
#define IOMUX_PAD_GPIOA_12_PULL_DN      (1<<8)
#define IOMUX_PAD_GPIOA_12_PULL_DN_POS  (8)
#define IOMUX_PAD_GPIOA_12_ANA(n)       (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_12_ANA_LSB      (4)
#define IOMUX_PAD_GPIOA_12_ANA_MASK     (15<<4)
#define IOMUX_PAD_GPIOA_12_SEL(n)       (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_12_SEL_LSB      (0)
#define IOMUX_PAD_GPIOA_12_SEL_MASK     (15<<0)
#define IOMUX_PAD_GPIOA_12_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_12_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_12_SEL_FUN_GPIOA_12_SEL (0<<0)
#define IOMUX_PAD_GPIOA_12_SEL_FUN_UART1_CTS_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_12_SEL_FUN_UART1_CTS_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_12_SEL_FUN_SPI_LCD_DI_SEL (2<<0)
#define IOMUX_PAD_GPIOA_12_SEL_FUN_PCM_FSYNC_SEL (3<<0)
#define IOMUX_PAD_GPIOA_12_SEL_FUN_SDMMC_CMD_SEL (4<<0)
#define IOMUX_PAD_GPIOA_12_SEL_FUN_I2S_DAT_IN_1_SEL (5<<0)
#define IOMUX_PAD_GPIOA_12_SEL_FUN_UART2_CTS_SEL (6<<0)
#define IOMUX_PAD_GPIOA_12_SEL_FUN_TPORTS14_SEL (7<<0)

//pad_gpioa_13_cfg_reg
#define IOMUX_PAD_GPIOA_13_OEN_FRC      (1<<28)
#define IOMUX_PAD_GPIOA_13_OEN_FRC_POS  (28)
#define IOMUX_PAD_GPIOA_13_OUT_FRC      (1<<24)
#define IOMUX_PAD_GPIOA_13_OUT_FRC_POS  (24)
#define IOMUX_PAD_GPIOA_13_OUT_REG      (1<<20)
#define IOMUX_PAD_GPIOA_13_OUT_REG_POS  (20)
#define IOMUX_PAD_GPIOA_13_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_13_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_13_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_13_OEN_REG      (1<<17)
#define IOMUX_PAD_GPIOA_13_OEN_REG_POS  (17)
#define IOMUX_PAD_GPIOA_13_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_13_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_13_PULL_UP      (1<<9)
#define IOMUX_PAD_GPIOA_13_PULL_UP_POS  (9)
#define IOMUX_PAD_GPIOA_13_PULL_DN      (1<<8)
#define IOMUX_PAD_GPIOA_13_PULL_DN_POS  (8)
#define IOMUX_PAD_GPIOA_13_ANA(n)       (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_13_ANA_LSB      (4)
#define IOMUX_PAD_GPIOA_13_ANA_MASK     (15<<4)
#define IOMUX_PAD_GPIOA_13_SEL(n)       (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_13_SEL_LSB      (0)
#define IOMUX_PAD_GPIOA_13_SEL_MASK     (15<<0)
#define IOMUX_PAD_GPIOA_13_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_13_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_13_SEL_FUN_GPIOA_13_SEL (0<<0)
#define IOMUX_PAD_GPIOA_13_SEL_FUN_UART1_RTS_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_13_SEL_FUN_UART1_RTS_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_13_SEL_FUN_SPI_LCD_DO_SEL (2<<0)
#define IOMUX_PAD_GPIOA_13_SEL_FUN_PCM_CLK_SEL (3<<0)
#define IOMUX_PAD_GPIOA_13_SEL_FUN_SDMMC_CLK_SEL (4<<0)
#define IOMUX_PAD_GPIOA_13_SEL_FUN_CODEC_MCLK_SEL (5<<0)
#define IOMUX_PAD_GPIOA_13_SEL_FUN_UART2_RTS_SEL (6<<0)
#define IOMUX_PAD_GPIOA_13_SEL_FUN_TPORTS15_SEL (7<<0)

//pad_gpioa_14_cfg_reg
#define IOMUX_PAD_GPIOA_14_OEN_FRC      (1<<28)
#define IOMUX_PAD_GPIOA_14_OEN_FRC_POS  (28)
#define IOMUX_PAD_GPIOA_14_OUT_FRC      (1<<24)
#define IOMUX_PAD_GPIOA_14_OUT_FRC_POS  (24)
#define IOMUX_PAD_GPIOA_14_OUT_REG      (1<<20)
#define IOMUX_PAD_GPIOA_14_OUT_REG_POS  (20)
#define IOMUX_PAD_GPIOA_14_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_14_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_14_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_14_OEN_REG      (1<<17)
#define IOMUX_PAD_GPIOA_14_OEN_REG_POS  (17)
#define IOMUX_PAD_GPIOA_14_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_14_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_14_PULL_UP      (1<<9)
#define IOMUX_PAD_GPIOA_14_PULL_UP_POS  (9)
#define IOMUX_PAD_GPIOA_14_PULL_DN      (1<<8)
#define IOMUX_PAD_GPIOA_14_PULL_DN_POS  (8)
#define IOMUX_PAD_GPIOA_14_ANA(n)       (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_14_ANA_LSB      (4)
#define IOMUX_PAD_GPIOA_14_ANA_MASK     (15<<4)
#define IOMUX_PAD_GPIOA_14_SEL(n)       (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_14_SEL_LSB      (0)
#define IOMUX_PAD_GPIOA_14_SEL_MASK     (15<<0)
#define IOMUX_PAD_GPIOA_14_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_14_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_GPIOA_14_SEL (0<<0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_I2CM_SCL_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_I2CM_SCL_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_SPI_LCD_CD_SEL (2<<0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_PCM_DIN_SEL (3<<0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_SDMMC_DATA_0_SEL (4<<0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_I2S_DAT_OUT_1_SEL (5<<0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_PWM_2_SEL (6<<0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_TPORTS12_SEL (7<<0)
#define IOMUX_PAD_GPIOA_14_SEL_FUN_DFT_JTAG_TDO_SEL (8<<0)

//pad_gpioa_15_cfg_reg
#define IOMUX_PAD_GPIOA_15_OEN_FRC      (1<<28)
#define IOMUX_PAD_GPIOA_15_OEN_FRC_POS  (28)
#define IOMUX_PAD_GPIOA_15_OUT_FRC      (1<<24)
#define IOMUX_PAD_GPIOA_15_OUT_FRC_POS  (24)
#define IOMUX_PAD_GPIOA_15_OUT_REG      (1<<20)
#define IOMUX_PAD_GPIOA_15_OUT_REG_POS  (20)
#define IOMUX_PAD_GPIOA_15_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOA_15_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOA_15_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOA_15_OEN_REG      (1<<17)
#define IOMUX_PAD_GPIOA_15_OEN_REG_POS  (17)
#define IOMUX_PAD_GPIOA_15_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOA_15_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOA_15_PULL_UP      (1<<9)
#define IOMUX_PAD_GPIOA_15_PULL_UP_POS  (9)
#define IOMUX_PAD_GPIOA_15_PULL_DN      (1<<8)
#define IOMUX_PAD_GPIOA_15_PULL_DN_POS  (8)
#define IOMUX_PAD_GPIOA_15_ANA(n)       (((n)&15)<<4)
#define IOMUX_PAD_GPIOA_15_ANA_LSB      (4)
#define IOMUX_PAD_GPIOA_15_ANA_MASK     (15<<4)
#define IOMUX_PAD_GPIOA_15_SEL(n)       (((n)&15)<<0)
#define IOMUX_PAD_GPIOA_15_SEL_LSB      (0)
#define IOMUX_PAD_GPIOA_15_SEL_MASK     (15<<0)
#define IOMUX_PAD_GPIOA_15_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOA_15_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOA_15_SEL_FUN_GPIOA_15_SEL (0<<0)
#define IOMUX_PAD_GPIOA_15_SEL_FUN_I2CM_SDA_SEL      (1<<0)
#define IOMUX_PAD_GPIOA_15_SEL_FUN_I2CM_SDA_SEL_POS  (0)
#define IOMUX_PAD_GPIOA_15_SEL_FUN_SPI_LCD_FMARK_SEL (2<<0)
#define IOMUX_PAD_GPIOA_15_SEL_FUN_PCM_DOUT_SEL (3<<0)
#define IOMUX_PAD_GPIOA_15_SEL_FUN_SDMMC_DATA_1_SEL (4<<0)
#define IOMUX_PAD_GPIOA_15_SEL_FUN_I2S_DAT_IN_0_SEL (5<<0)
#define IOMUX_PAD_GPIOA_15_SEL_FUN_DEBUG_CLK_SEL (6<<0)
#define IOMUX_PAD_GPIOA_15_SEL_FUN_TPORTS13_SEL (7<<0)

//pad_gpiob_0_cfg_reg
#define IOMUX_PAD_GPIOB_0_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOB_0_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOB_0_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOB_0_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOB_0_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOB_0_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOB_0_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOB_0_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOB_0_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOB_0_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOB_0_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOB_0_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOB_0_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOB_0_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOB_0_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOB_0_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOB_0_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOB_0_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOB_0_ANA_LSB       (4)
#define IOMUX_PAD_GPIOB_0_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOB_0_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOB_0_SEL_LSB       (0)
#define IOMUX_PAD_GPIOB_0_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOB_0_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOB_0_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOB_0_SEL_FUN_GPIOA_16_SEL (0<<0)
#define IOMUX_PAD_GPIOB_0_SEL_FUN_PCM_FSYNC_SEL      (1<<0)
#define IOMUX_PAD_GPIOB_0_SEL_FUN_PCM_FSYNC_SEL_POS  (0)
#define IOMUX_PAD_GPIOB_0_SEL_FUN_TPORTS0_SEL (2<<0)
#define IOMUX_PAD_GPIOB_0_SEL_FUN_UART1_RX_SEL (3<<0)
#define IOMUX_PAD_GPIOB_0_SEL_FUN_PWM_0_SEL (4<<0)
#define IOMUX_PAD_GPIOB_0_SEL_FUN_SPI_LCD_CSN_1_SEL (5<<0)

//pad_gpiob_1_cfg_reg
#define IOMUX_PAD_GPIOB_1_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOB_1_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOB_1_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOB_1_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOB_1_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOB_1_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOB_1_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOB_1_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOB_1_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOB_1_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOB_1_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOB_1_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOB_1_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOB_1_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOB_1_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOB_1_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOB_1_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOB_1_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOB_1_ANA_LSB       (4)
#define IOMUX_PAD_GPIOB_1_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOB_1_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOB_1_SEL_LSB       (0)
#define IOMUX_PAD_GPIOB_1_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOB_1_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOB_1_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOB_1_SEL_FUN_GPIOA_17_SEL (0<<0)
#define IOMUX_PAD_GPIOB_1_SEL_FUN_PCM_CLK_SEL      (1<<0)
#define IOMUX_PAD_GPIOB_1_SEL_FUN_PCM_CLK_SEL_POS  (0)
#define IOMUX_PAD_GPIOB_1_SEL_FUN_TPORTS1_SEL (2<<0)
#define IOMUX_PAD_GPIOB_1_SEL_FUN_UART1_TX_SEL (3<<0)
#define IOMUX_PAD_GPIOB_1_SEL_FUN_PWM_1_SEL (4<<0)
#define IOMUX_PAD_GPIOB_1_SEL_FUN_SPI_LCD_CSN_2_SEL (5<<0)

//pad_gpiob_2_cfg_reg
#define IOMUX_PAD_GPIOB_2_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOB_2_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOB_2_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOB_2_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOB_2_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOB_2_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOB_2_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOB_2_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOB_2_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOB_2_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOB_2_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOB_2_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOB_2_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOB_2_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOB_2_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOB_2_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOB_2_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOB_2_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOB_2_ANA_LSB       (4)
#define IOMUX_PAD_GPIOB_2_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOB_2_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOB_2_SEL_LSB       (0)
#define IOMUX_PAD_GPIOB_2_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOB_2_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOB_2_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOB_2_SEL_FUN_GPIOA_18_SEL (0<<0)
#define IOMUX_PAD_GPIOB_2_SEL_FUN_PCM_DIN_SEL      (1<<0)
#define IOMUX_PAD_GPIOB_2_SEL_FUN_PCM_DIN_SEL_POS  (0)
#define IOMUX_PAD_GPIOB_2_SEL_FUN_TPORTS2_SEL (2<<0)
#define IOMUX_PAD_GPIOB_2_SEL_FUN_UART1_CTS_SEL (3<<0)
#define IOMUX_PAD_GPIOB_2_SEL_FUN_PWM_2_SEL (4<<0)
#define IOMUX_PAD_GPIOB_2_SEL_FUN_SPI_LCD_CSN_3_SEL (5<<0)

//pad_gpiob_3_cfg_reg
#define IOMUX_PAD_GPIOB_3_OEN_FRC       (1<<28)
#define IOMUX_PAD_GPIOB_3_OEN_FRC_POS   (28)
#define IOMUX_PAD_GPIOB_3_OUT_FRC       (1<<24)
#define IOMUX_PAD_GPIOB_3_OUT_FRC_POS   (24)
#define IOMUX_PAD_GPIOB_3_OUT_REG       (1<<20)
#define IOMUX_PAD_GPIOB_3_OUT_REG_POS   (20)
#define IOMUX_PAD_GPIOB_3_DRV_STRENGTH(n)      (((n)&3)<<18)
#define IOMUX_PAD_GPIOB_3_DRV_STRENGTH_LSB     (18)
#define IOMUX_PAD_GPIOB_3_DRV_STRENGTH_MASK    (3<<18)
#define IOMUX_PAD_GPIOB_3_OEN_REG       (1<<17)
#define IOMUX_PAD_GPIOB_3_OEN_REG_POS   (17)
#define IOMUX_PAD_GPIOB_3_PULL_FRC      (1<<16)
#define IOMUX_PAD_GPIOB_3_PULL_FRC_POS  (16)
#define IOMUX_PAD_GPIOB_3_PULL_UP       (1<<9)
#define IOMUX_PAD_GPIOB_3_PULL_UP_POS   (9)
#define IOMUX_PAD_GPIOB_3_PULL_DN       (1<<8)
#define IOMUX_PAD_GPIOB_3_PULL_DN_POS   (8)
#define IOMUX_PAD_GPIOB_3_ANA(n)        (((n)&15)<<4)
#define IOMUX_PAD_GPIOB_3_ANA_LSB       (4)
#define IOMUX_PAD_GPIOB_3_ANA_MASK      (15<<4)
#define IOMUX_PAD_GPIOB_3_SEL(n)        (((n)&15)<<0)
#define IOMUX_PAD_GPIOB_3_SEL_LSB       (0)
#define IOMUX_PAD_GPIOB_3_SEL_MASK      (15<<0)
#define IOMUX_PAD_GPIOB_3_SEL_MASK (15<<0)
#define IOMUX_PAD_GPIOB_3_SEL_SHIFT (0)
#define IOMUX_PAD_GPIOB_3_SEL_FUN_GPIOA_19_SEL (0<<0)
#define IOMUX_PAD_GPIOB_3_SEL_FUN_PCM_DOUT_SEL      (1<<0)
#define IOMUX_PAD_GPIOB_3_SEL_FUN_PCM_DOUT_SEL_POS  (0)
#define IOMUX_PAD_GPIOB_3_SEL_FUN_TPORTS3_SEL (2<<0)
#define IOMUX_PAD_GPIOB_3_SEL_FUN_UART1_RTS_SEL (3<<0)
#define IOMUX_PAD_GPIOB_3_SEL_FUN_TPORTS8_SEL (7<<0)

__STATIC_INLINE uint8_t iomux_gpioa_config_sel_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] & IOMUX_PAD_GPIOA_0_SEL_MASK) >> IOMUX_PAD_GPIOA_0_SEL_LSB);
}

__STATIC_INLINE void iomux_gpioa_config_sel_setf(int gp_idx, uint8_t sel_val)
{
    uint32_t local_val = AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] & ~IOMUX_PAD_GPIOA_0_SEL_MASK;
    AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] = local_val | ((sel_val << IOMUX_PAD_GPIOA_0_SEL_LSB) & IOMUX_PAD_GPIOA_0_SEL_MASK);
}

__STATIC_INLINE uint8_t iomux_gpioa_config_pull_dn_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] & IOMUX_PAD_GPIOA_0_PULL_DN) >> IOMUX_PAD_GPIOA_0_PULL_DN_POS);
}

__STATIC_INLINE void iomux_gpioa_config_pull_dn_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOA_0_PULL_DN;
    } else {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOA_0_PULL_DN;
    }
}

__STATIC_INLINE uint8_t iomux_gpioa_config_pull_up_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] & IOMUX_PAD_GPIOA_0_PULL_UP) >> IOMUX_PAD_GPIOA_0_PULL_UP_POS);
}

__STATIC_INLINE void iomux_gpioa_config_pull_up_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOA_0_PULL_UP;
    } else {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOA_0_PULL_UP;
    }
}

__STATIC_INLINE uint8_t iomux_gpioa_config_pull_frc_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] & IOMUX_PAD_GPIOA_0_PULL_FRC) >> IOMUX_PAD_GPIOA_0_PULL_FRC_POS);
}

__STATIC_INLINE void iomux_gpioa_config_pull_frc_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOA_0_PULL_FRC;
    } else {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOA_0_PULL_FRC;
    }
}

__STATIC_INLINE uint8_t iomux_gpioa_config_oen_reg_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] & IOMUX_PAD_GPIOA_0_OEN_REG) >> IOMUX_PAD_GPIOA_0_OEN_REG_POS);
}

__STATIC_INLINE void iomux_gpioa_config_oen_reg_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOA_0_OEN_REG;
    } else {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOA_0_OEN_REG;
    }
}

__STATIC_INLINE uint8_t iomux_gpioa_config_out_reg_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] & IOMUX_PAD_GPIOA_0_OUT_REG) >> IOMUX_PAD_GPIOA_0_OUT_REG_POS);
}

__STATIC_INLINE void iomux_gpioa_config_out_reg_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOA_0_OUT_REG;
    } else {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOA_0_OUT_REG;
    }
}

__STATIC_INLINE uint8_t iomux_gpioa_config_out_frc_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] & IOMUX_PAD_GPIOA_0_OUT_FRC) >> IOMUX_PAD_GPIOA_0_OUT_FRC_POS);
}

__STATIC_INLINE void iomux_gpioa_config_out_frc_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOA_0_OUT_FRC;
    } else {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOA_0_OUT_FRC;
    }
}

__STATIC_INLINE uint8_t iomux_gpioa_config_oen_frc_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] & IOMUX_PAD_GPIOA_0_OEN_FRC) >> IOMUX_PAD_GPIOA_0_OEN_FRC_POS);
}

__STATIC_INLINE void iomux_gpioa_config_oen_frc_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOA_0_OEN_FRC;
    } else {
        AIC_IOMUX->pad_gpioa_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOA_0_OEN_FRC;
    }
}

__STATIC_INLINE uint8_t iomux_gpiob_config_sel_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] & IOMUX_PAD_GPIOB_0_SEL_MASK) >> IOMUX_PAD_GPIOB_0_SEL_LSB);
}

__STATIC_INLINE void iomux_gpiob_config_sel_setf(int gp_idx, uint8_t sel_val)
{
    uint32_t local_val = AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] & ~IOMUX_PAD_GPIOB_0_SEL_MASK;
    AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] = local_val | ((sel_val << IOMUX_PAD_GPIOB_0_SEL_LSB) & IOMUX_PAD_GPIOB_0_SEL_MASK);
}

__STATIC_INLINE uint8_t iomux_gpiob_config_pull_dn_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] & IOMUX_PAD_GPIOB_0_PULL_DN) >> IOMUX_PAD_GPIOB_0_PULL_DN_POS);
}

__STATIC_INLINE void iomux_gpiob_config_pull_dn_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOB_0_PULL_DN;
    } else {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOB_0_PULL_DN;
    }
}

__STATIC_INLINE uint8_t iomux_gpiob_config_pull_up_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] & IOMUX_PAD_GPIOB_0_PULL_UP) >> IOMUX_PAD_GPIOB_0_PULL_UP_POS);
}

__STATIC_INLINE void iomux_gpiob_config_pull_up_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOB_0_PULL_UP;
    } else {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOB_0_PULL_UP;
    }
}

__STATIC_INLINE uint8_t iomux_gpiob_config_pull_frc_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] & IOMUX_PAD_GPIOB_0_PULL_FRC) >> IOMUX_PAD_GPIOB_0_PULL_FRC_POS);
}

__STATIC_INLINE void iomux_gpiob_config_pull_frc_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOB_0_PULL_FRC;
    } else {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOB_0_PULL_FRC;
    }
}

__STATIC_INLINE uint8_t iomux_gpiob_config_oen_reg_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] & IOMUX_PAD_GPIOB_0_OEN_REG) >> IOMUX_PAD_GPIOB_0_OEN_REG_POS);
}

__STATIC_INLINE void iomux_gpiob_config_oen_reg_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOB_0_OEN_REG;
    } else {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOB_0_OEN_REG;
    }
}

__STATIC_INLINE uint8_t iomux_gpiob_config_out_reg_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] & IOMUX_PAD_GPIOB_0_OUT_REG) >> IOMUX_PAD_GPIOB_0_OUT_REG_POS);
}

__STATIC_INLINE void iomux_gpiob_config_out_reg_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOB_0_OUT_REG;
    } else {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOB_0_OUT_REG;
    }
}

__STATIC_INLINE uint8_t iomux_gpiob_config_out_frc_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] & IOMUX_PAD_GPIOB_0_OUT_FRC) >> IOMUX_PAD_GPIOB_0_OUT_FRC_POS);
}

__STATIC_INLINE void iomux_gpiob_config_out_frc_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOB_0_OUT_FRC;
    } else {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOB_0_OUT_FRC;
    }
}

__STATIC_INLINE uint8_t iomux_gpiob_config_oen_frc_getf(int gp_idx)
{
    return ((AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] & IOMUX_PAD_GPIOB_0_OEN_FRC) >> IOMUX_PAD_GPIOB_0_OEN_FRC_POS);
}

__STATIC_INLINE void iomux_gpiob_config_oen_frc_setf(int gp_idx, uint8_t bit_val)
{
    if (bit_val) {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] |=  IOMUX_PAD_GPIOB_0_OEN_FRC;
    } else {
        AIC_IOMUX->pad_gpiob_cfg_reg[gp_idx] &= ~IOMUX_PAD_GPIOB_0_OEN_FRC;
    }
}

#endif // _REG_IOMUX_H_