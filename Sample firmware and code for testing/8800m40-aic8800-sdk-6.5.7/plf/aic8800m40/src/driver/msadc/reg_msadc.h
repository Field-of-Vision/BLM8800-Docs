#ifndef _REG_MSADC_H_
#define _REG_MSADC_H_

#include "chip.h"

/* ========================================================================== */
/* ==============================    MSADC    =============================== */
/* ========================================================================== */
typedef struct {
  __IO uint32_t                  cfg_msadc_mode;               //0x00000000
  __IO uint32_t                  cfg_msadc_sw_ctrl0;           //0x00000004
  __IO uint32_t                  cfg_msadc_sw_ctrl1;           //0x00000008
  __IO uint32_t                  cfg_msadc_ana_ctrl0;          //0x0000000C
  __I  uint32_t                  cfg_msadc_ro_acc;             //0x00000010
  __I  uint32_t                  cfg_msadc_ro_test_acc_0;      //0x00000014
  __I  uint32_t                  cfg_msadc_ro_test_acc_1;      //0x00000018
  __IO uint32_t                  cfg_msadc_int_raw;            //0x0000001C
  __IO uint32_t                  cfg_msadc_int_status;         //0x00000020
  __IO uint32_t                  cfg_msadc_int_mask;           //0x00000024
} AIC_MSADC_TypeDef;

static AIC_MSADC_TypeDef * const AIC_MSADC = ((AIC_MSADC_TypeDef *)AIC_MSADC_BASE);


//cfg_msadc_mode
#define MSADC_REG_CFG_MSADC_MODE        (1<<0)
#define MSADC_REG_CFG_MSADC_MODE_POS    (0)
#define MSADC_REG_CFG_MSADC_HW_TEST_CHANNEL      (1<<1)
#define MSADC_REG_CFG_MSADC_HW_TEST_CHANNEL_POS  (1)

//cfg_msadc_sw_ctrl0
#define MSADC_REG_CFG_MSADC_SW_START_PULSE      (1<<0)
#define MSADC_REG_CFG_MSADC_SW_START_PULSE_POS  (0)
#define MSADC_REG_CFG_MSADC_SW_STOP_PULSE      (1<<1)
#define MSADC_REG_CFG_MSADC_SW_STOP_PULSE_POS  (1)
#define MSADC_REG_CFG_MSADC_SW_CLEAR_PULSE      (1<<2)
#define MSADC_REG_CFG_MSADC_SW_CLEAR_PULSE_POS  (2)

//cfg_msadc_sw_ctrl1
#define MSADC_REG_CFG_MSADC_SW_MUX_BITS(n)      (((n)&15)<<0)
#define MSADC_REG_CFG_MSADC_SW_MUX_BITS_LSB     (0)
#define MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK    (15<<0)
#define MSADC_REG_CFG_MSADC_TEST_0_MUX_BITS(n)      (((n)&15)<<4)
#define MSADC_REG_CFG_MSADC_TEST_0_MUX_BITS_LSB     (4)
#define MSADC_REG_CFG_MSADC_TEST_0_MUX_BITS_MASK    (15<<4)
#define MSADC_REG_CFG_MSADC_TEST_1_MUX_BITS(n)      (((n)&15)<<8)
#define MSADC_REG_CFG_MSADC_TEST_1_MUX_BITS_LSB     (8)
#define MSADC_REG_CFG_MSADC_TEST_1_MUX_BITS_MASK    (15<<8)
#define MSADC_REG_CFG_MSADC_WAIT_CNT(n)      (((n)&15)<<12)
#define MSADC_REG_CFG_MSADC_WAIT_CNT_LSB     (12)
#define MSADC_REG_CFG_MSADC_WAIT_CNT_MASK    (15<<12)
#define MSADC_REG_CFG_MSADC_WINDOW(n)      (((n)&0xFFF)<<16)
#define MSADC_REG_CFG_MSADC_WINDOW_LSB     (16)
#define MSADC_REG_CFG_MSADC_WINDOW_MASK    (0xFFF<<16)
#define MSADC_REG_CFG_MSADC_SW_DIFF_MODE      (1<<28)
#define MSADC_REG_CFG_MSADC_SW_DIFF_MODE_POS  (28)

//cfg_msadc_ana_ctrl0
#define MSADC_REG_CFG_ANA_MSADC_CHNP_SEL      (1<<0)
#define MSADC_REG_CFG_ANA_MSADC_CHNP_SEL_POS  (0)
#define MSADC_REG_CFG_ANA_MSADC_CMP_BIT      (1<<1)
#define MSADC_REG_CFG_ANA_MSADC_CMP_BIT_POS  (1)
#define MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT(n)      (((n)&0xFF)<<2)
#define MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT_LSB     (2)
#define MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT_MASK    (0xFF<<2)
#define MSADC_REG_CFG_ANA_MSADC_SDM_MODE      (1<<10)
#define MSADC_REG_CFG_ANA_MSADC_SDM_MODE_POS  (10)
#define MSADC_REG_CFG_ANA_MSADC_TEST_MODE      (1<<11)
#define MSADC_REG_CFG_ANA_MSADC_TEST_MODE_POS  (11)
#define MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT(n)      (((n)&7)<<12)
#define MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT_LSB     (12)
#define MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT_MASK    (7<<12)
#define MSADC_REG_CFG_ANA_MSADC_CHOP_EN      (1<<15)
#define MSADC_REG_CFG_ANA_MSADC_CHOP_EN_POS  (15)
#define MSADC_REG_CFG_ANA_MSADC_SDM_GAIN_BIT      (1<<16)
#define MSADC_REG_CFG_ANA_MSADC_SDM_GAIN_BIT_POS  (16)
#define MSADC_REG_CFG_ANA_MSADC_DEM_EN(n)      (((n)&3)<<17)
#define MSADC_REG_CFG_ANA_MSADC_DEM_EN_LSB     (17)
#define MSADC_REG_CFG_ANA_MSADC_DEM_EN_MASK    (3<<17)
#define MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN      (1<<19)
#define MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN_POS  (19)
#define MSADC_REG_CFG_ANA_MSADC_TS_MODE      (1<<20)
#define MSADC_REG_CFG_ANA_MSADC_TS_MODE_POS  (20)
#define MSADC_REG_CFG_ANA_MSADC_RSVD_BIT(n)      (((n)&15)<<21)
#define MSADC_REG_CFG_ANA_MSADC_RSVD_BIT_LSB     (21)
#define MSADC_REG_CFG_ANA_MSADC_RSVD_BIT_MASK    (15<<21)
#define MSADC_REG_CFG_ANA_MSADC_DITHER_MODE(n)      (((n)&3)<<25)
#define MSADC_REG_CFG_ANA_MSADC_DITHER_MODE_LSB     (25)
#define MSADC_REG_CFG_ANA_MSADC_DITHER_MODE_MASK    (3<<25)
#define MSADC_REG_CFG_ANA_MSADC_VCOM_BIT(n)      (((n)&3)<<27)
#define MSADC_REG_CFG_ANA_MSADC_VCOM_BIT_LSB     (27)
#define MSADC_REG_CFG_ANA_MSADC_VCOM_BIT_MASK    (3<<27)

//cfg_msadc_ro_acc
#define MSADC_REG_RO_MSADC_DAT_ACC(n)      (((n)&0x3FFFFF)<<0)
#define MSADC_REG_RO_MSADC_DAT_ACC_LSB     (0)
#define MSADC_REG_RO_MSADC_DAT_ACC_MASK    (0x3FFFFF<<0)

//cfg_msadc_ro_test_acc_0
#define MSADC_REG_RO_MSADC_TEST_ACC_0(n)      (((n)&0x3FFFFF)<<0)
#define MSADC_REG_RO_MSADC_TEST_ACC_0_LSB     (0)
#define MSADC_REG_RO_MSADC_TEST_ACC_0_MASK    (0x3FFFFF<<0)

//cfg_msadc_ro_test_acc_1
#define MSADC_REG_RO_MSADC_TEST_ACC_1(n)      (((n)&0x3FFFFF)<<0)
#define MSADC_REG_RO_MSADC_TEST_ACC_1_LSB     (0)
#define MSADC_REG_RO_MSADC_TEST_ACC_1_MASK    (0x3FFFFF<<0)

//cfg_msadc_int_raw
#define MSADC_REG_MASDC_INT_RAW         (1<<0)
#define MSADC_REG_MASDC_INT_RAW_POS     (0)

//cfg_msadc_int_status
#define MSADC_REG_MSADC_INT_STATUS      (1<<0)
#define MSADC_REG_MSADC_INT_STATUS_POS  (0)

//cfg_msadc_int_mask
#define MSADC_REG_CFG_MSADC_INT_MASK      (1<<0)
#define MSADC_REG_CFG_MSADC_INT_MASK_POS  (0)

#endif /* _REG_MSADC_H_ */
