#ifndef _DUAL_DCDC_COMMON_H_
#define _DUAL_DCDC_COMMON_H_

#include "chip.h"

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// =============================================================================
// DUAL_DCDC_COMMON_T
// =============================================================================
typedef struct {
  __IO uint32_t                          dcdc_ref_clk_div;             //0x00000000
  __IO uint32_t                          dcdc_clk_ctrl0;               //0x00000004
  __IO uint32_t                          dcdc_clk_ctrl1;               //0x00000008
  __IO uint32_t                          dcdc_clk_ctrl2;               //0x0000000C
  __IO uint32_t                          dcdc_clk_ctrl3;               //0x00000010
} HWP_DUAL_DCDC_COMMON_T;

static HWP_DUAL_DCDC_COMMON_T * const AIC_DCDC_COMMON = ((HWP_DUAL_DCDC_COMMON_T *)AIC_DCDC_COMMON_BASE);

//dcdc_ref_clk_div
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_DENOM(n)      (((n)&0x7F)<<0)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_DENOM_LSB     (0)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_DENOM_MASK    (0x7F<<0)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_UPDATE      (1<<7)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_UPDATE_POS  (7)

//dcdc_clk_ctrl0
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_SEL(n)      (((n)&3)<<0)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_SEL_LSB     (0)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_SEL_MASK    (3<<0)

//dcdc_clk_ctrl1
#define DUAL_DCDC_COMMON_RG_DCDC_RF_CLK_OFFSET(n)      (((n)&15)<<0)
#define DUAL_DCDC_COMMON_RG_DCDC_RF_CLK_OFFSET_LSB     (0)
#define DUAL_DCDC_COMMON_RG_DCDC_RF_CLK_OFFSET_MASK    (15<<0)
#define DUAL_DCDC_COMMON_RG_DCDC_AUD_CLK_OFFSET(n)      (((n)&15)<<4)
#define DUAL_DCDC_COMMON_RG_DCDC_AUD_CLK_OFFSET_LSB     (4)
#define DUAL_DCDC_COMMON_RG_DCDC_AUD_CLK_OFFSET_MASK    (15<<4)

//dcdc_clk_ctrl2
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_DENOM_TX(n)      (((n)&0x7F)<<0)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_DENOM_TX_LSB     (0)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_DENOM_TX_MASK    (0x7F<<0)
#define DUAL_DCDC_COMMON_RG_TX_ON_REF_CLK_ENABLE      (1<<7)
#define DUAL_DCDC_COMMON_RG_TX_ON_REF_CLK_ENABLE_POS  (7)

//dcdc_clk_ctrl3
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_DENOM_RX(n)      (((n)&0x7F)<<0)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_DENOM_RX_LSB     (0)
#define DUAL_DCDC_COMMON_RG_DCDC_REF_CLK_DIV_DENOM_RX_MASK    (0x7F<<0)
#define DUAL_DCDC_COMMON_RG_RX_ON_REF_CLK_ENABLE      (1<<7)
#define DUAL_DCDC_COMMON_RG_RX_ON_REF_CLK_ENABLE_POS  (7)

#endif
