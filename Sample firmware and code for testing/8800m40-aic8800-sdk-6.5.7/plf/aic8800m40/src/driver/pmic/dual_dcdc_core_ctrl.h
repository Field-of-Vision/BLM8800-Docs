#ifndef _DUAL_DCDC_CORE_CTRL_H_
#define _DUAL_DCDC_CORE_CTRL_H_

#include "chip.h"

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// =============================================================================
// DUAL_DCDC_CORE_CTRL_T
// =============================================================================
typedef struct {
  __IO uint32_t                          dcdc_clk_ctrl0;               //0x00000000
  __IO uint32_t                          dcdc_clk_ctrl1;               //0x00000004
  __IO uint32_t                          dcdc_clk_ctrl2;               //0x00000008
  __IO uint32_t                          dcdc_clk_ctrl3;               //0x0000000C
  __IO uint32_t                          dcdc_clk_ctrl4;               //0x00000010
  __IO uint32_t                          dcdc_clk_ctrl5;               //0x00000014
  __IO uint32_t                          dcdc_clk_ctrl6;               //0x00000018
  __IO uint32_t                          dcdc_clk_ctrl7;               //0x0000001C
  __IO uint32_t Reserved_00000020[4];                 //0x00000020
  __IO uint32_t                          dcdc_ctrl_cfg0;               //0x00000030
  __IO uint32_t                          dcdc_ctrl_cfg1;               //0x00000034
  __IO uint32_t                          dcdc_ctrl_cfg2;               //0x00000038
  __IO uint32_t                          dcdc_ctrl_cfg3;               //0x0000003C
  __IO uint32_t                          dcdc_ctrl_cfg4;               //0x00000040
  __IO uint32_t                          dcdc_ctrl_cfg5;               //0x00000044
  __IO uint32_t                          dcdc_ctrl_cfg6;               //0x00000048
  __IO uint32_t                          dcdc_ctrl_cfg7;               //0x0000004C
  __IO uint32_t                          dcdc_ctrl_cfg8;               //0x00000050
  __IO uint32_t                          dcdc_ctrl_cfg9;               //0x00000054
  __IO uint32_t                          dcdc_ctrl_cfg10;              //0x00000058
  __IO uint32_t                          dcdc_ctrl_cfg11;              //0x0000005C
  __IO uint32_t                          dcdc_ctrl_cfg12;              //0x00000060
  __IO uint32_t                          dcdc_ctrl_cfg13;              //0x00000064
  __IO uint32_t                          dcdc_ctrl_cfg14;              //0x00000068
  __IO uint32_t                          dcdc_ctrl_cfg15;              //0x0000006C
  __IO uint32_t                          dcdc_ctrl_cfg16;              //0x00000070
  __IO uint32_t                          dcdc_ctrl_cfg17;              //0x00000074
  __IO uint32_t                          dcdc_ctrl_cfg18;              //0x00000078
  __IO uint32_t                          dcdc_ctrl_cfg19;              //0x0000007C
  __IO uint32_t                          dcdc_ctrl_cfg20;              //0x00000080
  __IO uint32_t                          dcdc_ctrl_cfg21;              //0x00000084
  __IO uint32_t                          dcdc_ctrl_cfg22;              //0x00000088
  __IO uint32_t                          dcdc_ctrl_cfg23;              //0x0000008C
  __IO uint32_t                          dcdc_ctrl_cfg24;              //0x00000090
  __IO uint32_t                          dcdc_ctrl_cfg25;              //0x00000094
  __IO uint32_t                          dcdc_ctrl_cfg26;              //0x00000098
  __IO uint32_t                          dcdc_ctrl_cfg27;              //0x0000009C
  __IO uint32_t                          dcdc_ctrl_cfg28;              //0x000000A0
  __IO uint32_t                          dcdc_ctrl_cfg29;              //0x000000A4
  __IO uint32_t                          dcdc_ctrl_cfg30;              //0x000000A8
  __IO uint32_t                          dcdc_ctrl_cfg31;              //0x000000AC
  __IO uint32_t                          dcdc_ctrl_cfg32;              //0x000000B0
  __IO uint32_t                          dcdc_ctrl_cfg33;              //0x000000B4
  __IO uint32_t                          dcdc_ctrl_cfg34;              //0x000000B8
  __IO uint32_t                          dcdc_ctrl_cfg35;              //0x000000BC
  __IO uint32_t                          dcdc_ctrl_cfg36;              //0x000000C0
  __IO uint32_t                          dcdc_ctrl_cfg37;              //0x000000C4
  __IO uint32_t                          dcdc_ctrl_cfg38;              //0x000000C8
  __IO uint32_t                          dcdc_ctrl_cfg39;              //0x000000CC
  __IO uint32_t                          dcdc_ctrl_cfg40;              //0x000000D0
  __IO uint32_t                          dcdc_ctrl_cfg41;              //0x000000D4
  __IO uint32_t                          dcdc_ctrl_cfg42;              //0x000000D8
  __IO uint32_t                          dcdc_ctrl_cfg43;              //0x000000DC
  __IO uint32_t                          dcdc_status;                  //0x000000E0
} HWP_DUAL_DCDC_CORE_CTRL_T;

static HWP_DUAL_DCDC_CORE_CTRL_T * const AIC_DCDC_CORECTRL = ((HWP_DUAL_DCDC_CORE_CTRL_T *)AIC_DCDC_CORECTRL_BASE);

//dcdc_clk_ctrl0
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_LPO_INV_EN      (1<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_LPO_INV_EN_POS  (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_EN      (1<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_EN_POS  (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_LPO_SEL      (1<<3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_LPO_SEL_POS  (3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_OUT_DLY_DEEPSLEEP_EN      (1<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_OUT_DLY_DEEPSLEEP_EN_POS  (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_UPDN_DEEPSLEEP_EN      (1<<5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_UPDN_DEEPSLEEP_EN_POS  (5)

//dcdc_clk_ctrl1
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_DENOM(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_DENOM_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_DENOM_MASK    (0x3F<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_DENOM_UPDATE      (1<<6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_DENOM_UPDATE_POS  (6)

//dcdc_clk_ctrl2
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD0_DENOM(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD0_DENOM_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD0_DENOM_MASK    (0x3F<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD0_DENOM_UPDATE      (1<<6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD0_DENOM_UPDATE_POS  (6)

//dcdc_clk_ctrl3
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD1_DENOM(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD1_DENOM_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD1_DENOM_MASK    (0x3F<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD1_DENOM_UPDATE      (1<<6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD1_DENOM_UPDATE_POS  (6)

//dcdc_clk_ctrl4
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD2_DENOM(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD2_DENOM_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD2_DENOM_MASK    (0x3F<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD2_DENOM_UPDATE      (1<<6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD2_DENOM_UPDATE_POS  (6)

//dcdc_clk_ctrl5
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD3_DENOM(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD3_DENOM_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD3_DENOM_MASK    (0x3F<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD3_DENOM_UPDATE      (1<<6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MOD3_DENOM_UPDATE_POS  (6)

//dcdc_clk_ctrl6
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SMPL_MODE(n)      (((n)&3)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SMPL_MODE_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SMPL_MODE_MASK    (3<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_DN_SEL      (1<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_DN_SEL_POS  (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_LPO_DENOM(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_LPO_DENOM_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_LPO_DENOM_MASK    (7<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_LPO_DENOM_UPDATE      (1<<7)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_LPO_DENOM_UPDATE_POS  (7)

//dcdc_clk_ctrl7
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_DN_PHASE(n)      (((n)&3)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_DN_PHASE_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_DN_PHASE_MASK    (3<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_UP_PHASE(n)      (((n)&3)<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_UP_PHASE_LSB     (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_UP_PHASE_MASK    (3<<2)

//dcdc_ctrl_cfg0
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_BYPASS      (1<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_BYPASS_POS  (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_AUTO_ENABLE_MODE      (1<<1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_AUTO_ENABLE_MODE_POS  (1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NS_AUTO_TRACK_EN      (1<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NS_AUTO_TRACK_EN_POS  (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_SEL      (1<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_SEL_POS  (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_OFFSET_L(n)      (((n)&7)<<5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_OFFSET_L_LSB     (5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_OFFSET_L_MASK    (7<<5)

//dcdc_ctrl_cfg1
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_OFFSET_H(n)      (((n)&0x7F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_OFFSET_H_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_OFFSET_H_MASK    (0x7F<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_OFFSET_UPDATE      (1<<7)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_OFFSET_UPDATE_POS  (7)

//dcdc_ctrl_cfg2
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CNT_MODE_TH(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CNT_MODE_TH_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CNT_MODE_TH_MASK    (0xFF<<0)

//dcdc_ctrl_cfg3
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CNT_MODE1_TH(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CNT_MODE1_TH_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CNT_MODE1_TH_MASK    (0xFF<<0)

//dcdc_ctrl_cfg4
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_INT_UP_TH(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_INT_UP_TH_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_INT_UP_TH_MASK    (0xFF<<0)

//dcdc_ctrl_cfg5
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_INT_DN_TH(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_INT_DN_TH_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_INT_DN_TH_MASK    (0xFF<<0)

//dcdc_ctrl_cfg6
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGP_TH0(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGP_TH0_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGP_TH0_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGP_TH1(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGP_TH1_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGP_TH1_MASK    (7<<4)

//dcdc_ctrl_cfg7
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGP_TH2(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGP_TH2_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGP_TH2_MASK    (7<<0)

//dcdc_ctrl_cfg8
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGN_TH0(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGN_TH0_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGN_TH0_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGN_TH1(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGN_TH1_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGN_TH1_MASK    (7<<4)

//dcdc_ctrl_cfg9
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGN_TH2(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGN_TH2_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FLAGN_TH2_MASK    (7<<0)

//dcdc_ctrl_cfg10
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_CLK_DIV(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_CLK_DIV_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_CLK_DIV_MASK    (0xFF<<0)

//dcdc_ctrl_cfg11
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_CNT_VTH1(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_CNT_VTH1_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_CNT_VTH1_MASK    (0xFF<<0)

//dcdc_ctrl_cfg12
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_CNT_VTH2(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_CNT_VTH2_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_CNT_VTH2_MASK    (0xFF<<0)

//dcdc_ctrl_cfg13
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_CNT_VTH3(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_CNT_VTH3_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_CNT_VTH3_MASK    (0xFF<<0)

//dcdc_ctrl_cfg14
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_HIGH_CNT_VTH(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_HIGH_CNT_VTH_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_HIGH_CNT_VTH_MASK    (0x3F<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYSCOMP_HIGH_DET_BPS      (1<<6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYSCOMP_HIGH_DET_BPS_POS  (6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_DET_MODE      (1<<7)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PFM_LOW_DET_MODE_POS  (7)

//dcdc_ctrl_cfg15
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE0(n)      (((n)&3)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE0_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE0_MASK    (3<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE1(n)      (((n)&3)<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE1_LSB     (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE1_MASK    (3<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE2(n)      (((n)&3)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE2_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE2_MASK    (3<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE3(n)      (((n)&3)<<6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE3_LSB     (6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NLG_SCALE3_MASK    (3<<6)

//dcdc_ctrl_cfg16
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KS(n)      (((n)&15)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KS_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KS_MASK    (15<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KP(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KP_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KP_MASK    (7<<4)

//dcdc_ctrl_cfg17
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KZ(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KZ_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KZ_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KW_L(n)      (((n)&15)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KW_L_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KW_L_MASK    (15<<4)

//dcdc_ctrl_cfg18
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KW_H(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KW_H_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KW_H_MASK    (0x3F<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KW_UPDATE      (1<<7)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_KW_UPDATE_POS  (7)

//dcdc_ctrl_cfg19
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DIFF_VTH_SEL(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DIFF_VTH_SEL_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DIFF_VTH_SEL_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FP_INT(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FP_INT_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FP_INT_MASK    (7<<4)

//dcdc_ctrl_cfg20
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FP_GAIN(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FP_GAIN_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FP_GAIN_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_W_STEP(n)      (((n)&3)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_W_STEP_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_W_STEP_MASK    (3<<4)

//dcdc_ctrl_cfg21
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VX_INT_VTH(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VX_INT_VTH_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VX_INT_VTH_MASK    (7<<0)

//dcdc_ctrl_cfg22
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_ADD2D_INIT(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_ADD2D_INIT_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_ADD2D_INIT_MASK    (0xFF<<0)

//dcdc_ctrl_cfg23
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_ADD3D_INIT(n)      (((n)&0xFF)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_ADD3D_INIT_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_ADD3D_INIT_MASK    (0xFF<<0)

//dcdc_ctrl_cfg24
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_GAIN3(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_GAIN3_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_GAIN3_MASK    (0x3F<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_GAIN3_DEEPSLEEP(n)      (((n)&0x3F)<<8)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_GAIN3_DEEPSLEEP_LSB     (8)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_GAIN3_DEEPSLEEP_MASK    (0x3F<<8)

//dcdc_ctrl_cfg25
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DOUT_PW_LIM(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DOUT_PW_LIM_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DOUT_PW_LIM_MASK    (0x3F<<0)

//dcdc_ctrl_cfg26
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DOUT_OFFSET(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DOUT_OFFSET_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DOUT_OFFSET_MASK    (0x3F<<0)

//dcdc_ctrl_cfg27
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DOUT1_OFFSET(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DOUT1_OFFSET_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DOUT1_OFFSET_MASK    (0x3F<<0)

//dcdc_ctrl_cfg28
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP0_DOUT(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP0_DOUT_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP0_DOUT_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP1_DOUT(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP1_DOUT_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP1_DOUT_MASK    (7<<4)

//dcdc_ctrl_cfg29
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP2_DOUT(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP2_DOUT_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP2_DOUT_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP3_DOUT(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP3_DOUT_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP3_DOUT_MASK    (7<<4)

//dcdc_ctrl_cfg30
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP4_DOUT(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP4_DOUT_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP4_DOUT_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP5_DOUT(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP5_DOUT_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP5_DOUT_MASK    (7<<4)

//dcdc_ctrl_cfg31
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP6_DOUT(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP6_DOUT_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP6_DOUT_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP7_DOUT(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP7_DOUT_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP7_DOUT_MASK    (7<<4)

//dcdc_ctrl_cfg32
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP8_DOUT(n)      (((n)&7)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP8_DOUT_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP8_DOUT_MASK    (7<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP9_DOUT(n)      (((n)&7)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP9_DOUT_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SS_STEP9_DOUT_MASK    (7<<4)

//dcdc_ctrl_cfg33
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MODE_INIT(n)      (((n)&3)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MODE_INIT_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MODE_INIT_MASK    (3<<0)

//dcdc_ctrl_cfg34
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MODE(n)      (((n)&3)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MODE_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MODE_MASK    (3<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MODE_FORCE      (1<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_CLK_MODE_FORCE_POS  (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NS_HYS_GAIN      (1<<3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_NS_HYS_GAIN_POS  (3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PU_LPO_SW_MODE      (1<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PU_LPO_SW_MODE_POS  (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PU_LPO_SW      (1<<5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_PU_LPO_SW_POS  (5)

//dcdc_ctrl_cfg35
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE0(n)      (((n)&3)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE0_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE0_MASK    (3<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE1(n)      (((n)&3)<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE1_LSB     (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE1_MASK    (3<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE2(n)      (((n)&3)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE2_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE2_MASK    (3<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE3(n)      (((n)&3)<<6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE3_LSB     (6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_VTH_SCALE3_MASK    (3<<6)

//dcdc_ctrl_cfg36
#define DUAL_DCDC_CORE_CTRL_RG_TPORTS_SEL(n)      (((n)&15)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_TPORTS_SEL_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_TPORTS_SEL_MASK    (15<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_ADC_GAIN_NORM(n)      (((n)&3)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_ADC_GAIN_NORM_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_ADC_GAIN_NORM_MASK    (3<<4)

//dcdc_ctrl_cfg37
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_GAIN3_LIMIT_VTH(n)      (((n)&0x3F)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_GAIN3_LIMIT_VTH_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_GAIN3_LIMIT_VTH_MASK    (0x3F<<0)

//dcdc_ctrl_cfg38
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DEEPSLEEP_SW_MODE      (1<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DEEPSLEEP_SW_MODE_POS  (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DEEPSLEEP_SW      (1<<1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DEEPSLEEP_SW_POS  (1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_MODE_SW_MODE      (1<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_MODE_SW_MODE_POS  (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_MODE_SW      (1<<3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_HYS_PFM_MODE_SW_POS  (3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FORCE_RES_ON_SW_MODE      (1<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FORCE_RES_ON_SW_MODE_POS  (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FORCE_RES_ON      (1<<5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_FORCE_RES_ON_POS  (5)

//dcdc_ctrl_cfg39
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_EN_PMOS(n)      (((n)&15)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_EN_PMOS_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_EN_PMOS_MASK    (15<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_EN_NMOS(n)      (((n)&15)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_EN_NMOS_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_EN_NMOS_MASK    (15<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_EN_NMOS_PMOS_SW_MODE      (1<<8)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_EN_NMOS_PMOS_SW_MODE_POS  (8)

//dcdc_ctrl_cfg40
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_FLAG_TH(n)      (((n)&15)<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_FLAG_TH_LSB     (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_FLAG_TH_MASK    (15<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_FLAG_SEL      (1<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DCM_FLAG_SEL_POS  (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_MODE_FLAG_FRC_EN      (1<<5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_MODE_FLAG_FRC_EN_POS  (5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_MODE_FLAG_FRC_VALUE      (1<<6)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_MODE_FLAG_FRC_VALUE_POS  (6)

//dcdc_ctrl_cfg41
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_TX_ON_DCM_ENABLE      (1<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_TX_ON_DCM_ENABLE_POS  (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_TX_ON_DCM_CLK_MODE(n)      (((n)&3)<<1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_TX_ON_DCM_CLK_MODE_LSB     (1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_TX_ON_DCM_CLK_MODE_MASK    (3<<1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_RX_ON_DCM_ENABLE      (1<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_RX_ON_DCM_ENABLE_POS  (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_RX_ON_DCM_CLK_MODE(n)      (((n)&3)<<5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_RX_ON_DCM_CLK_MODE_LSB     (5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_RX_ON_DCM_CLK_MODE_MASK    (3<<5)

//dcdc_ctrl_cfg42
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_TX_ON_MODE_FLAG_ENABLE      (1<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_TX_ON_MODE_FLAG_ENABLE_POS  (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_TX_ON_MODE_FLAG      (1<<1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_TX_ON_MODE_FLAG_POS  (1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_RX_ON_MODE_FLAG_ENABLE      (1<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_RX_ON_MODE_FLAG_ENABLE_POS  (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_RX_ON_MODE_FLAG      (1<<3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_RX_ON_MODE_FLAG_POS  (3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_DLY_MODE(n)      (((n)&3)<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_DLY_MODE_LSB     (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_CLK_DLY_MODE_MASK    (3<<4)

//dcdc_ctrl_cfg43
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DPWM_FRC_ON_DEEPSLEEP      (1<<0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DPWM_FRC_ON_DEEPSLEEP_POS  (0)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DPWM_FRC_ON_NORM      (1<<1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DPWM_FRC_ON_NORM_POS  (1)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DPWM_FRC_ON_SW_MODE      (1<<2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_DPWM_FRC_ON_SW_MODE_POS  (2)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SDM_QUANT_BYPASS      (1<<3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_SDM_QUANT_BYPASS_POS  (3)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_GAIN3_DITHER_EN      (1<<4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_GAIN3_DITHER_EN_POS  (4)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_GAIN3_DITHER_GAIN(n)      (((n)&7)<<5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_GAIN3_DITHER_GAIN_LSB     (5)
#define DUAL_DCDC_CORE_CTRL_RG_DCDC_GAIN3_DITHER_GAIN_MASK    (7<<5)

//dcdc_status
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_MODE_FLAG      (1<<0)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_MODE_FLAG_POS  (0)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_PW_LIM      (1<<1)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_PW_LIM_POS  (1)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_DCM_CLK_MODE(n)      (((n)&3)<<2)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_DCM_CLK_MODE_LSB     (2)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_DCM_CLK_MODE_MASK    (3<<2)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_HYS_PFM_MODE      (1<<4)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_HYS_PFM_MODE_POS  (4)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_SS_WIN_END      (1<<5)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_SS_WIN_END_POS  (5)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_SS_FAIL_FLAG      (1<<6)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_SS_FAIL_FLAG_POS  (6)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_IN(n)      (((n)&0x3FF)<<8)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_IN_LSB     (8)
#define DUAL_DCDC_CORE_CTRL_RO_DCDC_IN_MASK    (0x3FF<<8)

#endif
