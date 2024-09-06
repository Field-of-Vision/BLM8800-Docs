#ifndef _PMU_RTC0_H_
#define _PMU_RTC0_H_

#include "chip.h"

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// =============================================================================
// PMU_RTC0_T
// =============================================================================
typedef struct {
  __IO uint32_t                          pmu_rtc0_cfg0;                //0x00000000
  __IO uint32_t                          pmu_rtc0_cfg1;                //0x00000004
  __IO uint32_t                          pmu_rtc0_cfg2;                //0x00000008
  __IO uint32_t                          pmu_rtc0_cfg3;                //0x0000000C
  __IO uint32_t                          pmu_rtc0_cfg4;                //0x00000010
  __IO uint32_t                          pmu_rtc0_cfg5;                //0x00000014
  __IO uint32_t                          pmu_rtc0_cfg6;                //0x00000018
  __IO uint32_t                          pmu_rtc0_cfg7;                //0x0000001C
  __IO uint32_t                          pmu_rtc0_wdg4_cnt_ini;        //0x00000020
  __IO uint32_t                          rtc_rg_reserved0;             //0x00000024
  __IO uint32_t                          rtc_rg_reserved1;             //0x00000028
} HWP_PMU_RTC0_T;

static HWP_PMU_RTC0_T * const AIC_PMU_RTC0 = ((HWP_PMU_RTC0_T *)AIC_PMU_RTC0_BASE);


//pmu_rtc0_cfg0
#define PMU_RTC0_PMU_RTC0_RG_UPDATE      (1<<0)
#define PMU_RTC0_PMU_RTC0_RG_UPDATE_POS  (0)
#define PMU_RTC0_RTC_RG_PB_INT_DEBC_SEQ_PD_BYPASS0      (1<<1)
#define PMU_RTC0_RTC_RG_PB_INT_DEBC_SEQ_PD_BYPASS0_POS  (1)
#define PMU_RTC0_RTC_RG_PB_INT_DEBC_SEQ_PD_BYPASS1      (1<<2)
#define PMU_RTC0_RTC_RG_PB_INT_DEBC_SEQ_PD_BYPASS1_POS  (2)
#define PMU_RTC0_RTC_RG_GPIO_DEBC_SEQ_PD_BYPASS0      (1<<3)
#define PMU_RTC0_RTC_RG_GPIO_DEBC_SEQ_PD_BYPASS0_POS  (3)
#define PMU_RTC0_RTC_RG_GPIO_DEBC_SEQ_PD_BYPASS1      (1<<4)
#define PMU_RTC0_RTC_RG_GPIO_DEBC_SEQ_PD_BYPASS1_POS  (4)
#define PMU_RTC0_RTC_RG_BG_PD_SEQ_NUM(n)      (((n)&7)<<5)
#define PMU_RTC0_RTC_RG_BG_PD_SEQ_NUM_LSB     (5)
#define PMU_RTC0_RTC_RG_BG_PD_SEQ_NUM_MASK    (7<<5)
#define PMU_RTC0_RTC_RG_FORCE_PBINT_NEG_PWROFF      (1<<8)
#define PMU_RTC0_RTC_RG_FORCE_PBINT_NEG_PWROFF_POS  (8)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_OUT      (1<<9)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_OUT_POS  (9)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_CLR_EN      (1<<10)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_CLR_EN_POS  (10)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_HW_EN      (1<<11)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_HW_EN_POS  (11)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_SW_EN      (1<<12)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_SW_EN_POS  (12)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_TH(n)      (((n)&3)<<13)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_TH_LSB     (13)
#define PMU_RTC0_RTC_RG_CM_CO_XTAL_DET_TH_MASK    (3<<13)

//pmu_rtc0_cfg1
#define PMU_RTC0_RTC_RG_LDO_RF_PU_SEQ_NUM(n)      (((n)&31)<<0)
#define PMU_RTC0_RTC_RG_LDO_RF_PU_SEQ_NUM_LSB     (0)
#define PMU_RTC0_RTC_RG_LDO_RF_PU_SEQ_NUM_MASK    (31<<0)
#define PMU_RTC0_RTC_RG_LDO_VRTC08_PU_SEQ_NUM(n)      (((n)&31)<<5)
#define PMU_RTC0_RTC_RG_LDO_VRTC08_PU_SEQ_NUM_LSB     (5)
#define PMU_RTC0_RTC_RG_LDO_VRTC08_PU_SEQ_NUM_MASK    (31<<5)
#define PMU_RTC0_RTC_RG_VBAT_RSTN_TH(n)      (((n)&0xFF)<<10)
#define PMU_RTC0_RTC_RG_VBAT_RSTN_TH_LSB     (10)
#define PMU_RTC0_RTC_RG_VBAT_RSTN_TH_MASK    (0xFF<<10)
#define PMU_RTC0_RTC_RG_PBINT_LONG_RST_REPOWER_EN      (1<<18)
#define PMU_RTC0_RTC_RG_PBINT_LONG_RST_REPOWER_EN_POS  (18)
#define PMU_RTC0_RTC_RG_PBINT_LONG_RST_PD_EN      (1<<19)
#define PMU_RTC0_RTC_RG_PBINT_LONG_RST_PD_EN_POS  (19)
#define PMU_RTC0_RTC_RG_BOR_REPOWER_EN      (1<<20)
#define PMU_RTC0_RTC_RG_BOR_REPOWER_EN_POS  (20)
#define PMU_RTC0_RTC_RG_BOR_PWROFF_EN      (1<<21)
#define PMU_RTC0_RTC_RG_BOR_PWROFF_EN_POS  (21)
#define PMU_RTC0_RTC_RG_BOR_HIGH_DEGLITCH_TH(n)      (((n)&0xFF)<<22)
#define PMU_RTC0_RTC_RG_BOR_HIGH_DEGLITCH_TH_LSB     (22)
#define PMU_RTC0_RTC_RG_BOR_HIGH_DEGLITCH_TH_MASK    (0xFF<<22)
#define PMU_RTC0_RTC_RG_BOR_HIGH_DEGLITCH_EN      (1<<30)
#define PMU_RTC0_RTC_RG_BOR_HIGH_DEGLITCH_EN_POS  (30)
#define PMU_RTC0_RTC_RG_BOR_EN          (1<<31)
#define PMU_RTC0_RTC_RG_BOR_EN_POS      (31)

//pmu_rtc0_cfg2
#define PMU_RTC0_RTC_RG_LDO_RF_VBIT(n)      (((n)&15)<<0)
#define PMU_RTC0_RTC_RG_LDO_RF_VBIT_LSB     (0)
#define PMU_RTC0_RTC_RG_LDO_RF_VBIT_MASK    (15<<0)
#define PMU_RTC0_RTC_RG_PBINT_POR_TRIG_CNT_LOW_TH(n)      (((n)&0xFF)<<4)
#define PMU_RTC0_RTC_RG_PBINT_POR_TRIG_CNT_LOW_TH_LSB     (4)
#define PMU_RTC0_RTC_RG_PBINT_POR_TRIG_CNT_LOW_TH_MASK    (0xFF<<4)
#define PMU_RTC0_RTC_RG_PBINT_POR_TRIG_CNT_HIGH_TH(n)      (((n)&0xFF)<<12)
#define PMU_RTC0_RTC_RG_PBINT_POR_TRIG_CNT_HIGH_TH_LSB     (12)
#define PMU_RTC0_RTC_RG_PBINT_POR_TRIG_CNT_HIGH_TH_MASK    (0xFF<<12)
#define PMU_RTC0_RTC_RG_GPIO_CFG(n)      (((n)&15)<<20)
#define PMU_RTC0_RTC_RG_GPIO_CFG_LSB     (20)
#define PMU_RTC0_RTC_RG_GPIO_CFG_MASK    (15<<20)
#define PMU_RTC0_RTC_RG_CHARGER_ON_EN      (1<<24)
#define PMU_RTC0_RTC_RG_CHARGER_ON_EN_POS  (24)
#define PMU_RTC0_RTC_RG_CHARGER_ON_INV_SEL      (1<<25)
#define PMU_RTC0_RTC_RG_CHARGER_ON_INV_SEL_POS  (25)
#define PMU_RTC0_RTC_RG_PU_CLK_32K_RC_SW      (1<<26)
#define PMU_RTC0_RTC_RG_PU_CLK_32K_RC_SW_POS  (26)
#define PMU_RTC0_RTC_RG_PWR_ON_RDY_SW      (1<<27)
#define PMU_RTC0_RTC_RG_PWR_ON_RDY_SW_POS  (27)
#define PMU_RTC0_RTC_RG_DBG_MUX(n)      (((n)&15)<<28)
#define PMU_RTC0_RTC_RG_DBG_MUX_LSB     (28)
#define PMU_RTC0_RTC_RG_DBG_MUX_MASK    (15<<28)

//pmu_rtc0_cfg3
#define PMU_RTC0_RTC_RG_GPIO_POR_TRIG_CNT_LOW_TH(n)      (((n)&0xFF)<<0)
#define PMU_RTC0_RTC_RG_GPIO_POR_TRIG_CNT_LOW_TH_LSB     (0)
#define PMU_RTC0_RTC_RG_GPIO_POR_TRIG_CNT_LOW_TH_MASK    (0xFF<<0)
#define PMU_RTC0_RTC_RG_GPIO_POR_TRIG_CNT_HIGH_TH(n)      (((n)&0xFF)<<8)
#define PMU_RTC0_RTC_RG_GPIO_POR_TRIG_CNT_HIGH_TH_LSB     (8)
#define PMU_RTC0_RTC_RG_GPIO_POR_TRIG_CNT_HIGH_TH_MASK    (0xFF<<8)
#define PMU_RTC0_RTC_RG_WDG_RSTN_REPOWER_EN      (1<<16)
#define PMU_RTC0_RTC_RG_WDG_RSTN_REPOWER_EN_POS  (16)
#define PMU_RTC0_RTC_RG_WDG_RSTN_PD_EN      (1<<17)
#define PMU_RTC0_RTC_RG_WDG_RSTN_PD_EN_POS  (17)
#define PMU_RTC0_RTC_RG_PU_DCDC_LDO_MODE_SEL      (1<<18)
#define PMU_RTC0_RTC_RG_PU_DCDC_LDO_MODE_SEL_POS  (18)
#define PMU_RTC0_RTC_RG_ALM_POWER_ON_EN      (1<<19)
#define PMU_RTC0_RTC_RG_ALM_POWER_ON_EN_POS  (19)
#define PMU_RTC0_RTC_RG_AON_GPIO_PWR_ON_EN      (1<<20)
#define PMU_RTC0_RTC_RG_AON_GPIO_PWR_ON_EN_POS  (20)
#define PMU_RTC0_RTC_RG_AON_GPIO_PWR_OFF_EN      (1<<21)
#define PMU_RTC0_RTC_RG_AON_GPIO_PWR_OFF_EN_POS  (21)
#define PMU_RTC0_RTC_RG_POWER_OFF_PMU_RTC0_EN      (1<<22)
#define PMU_RTC0_RTC_RG_POWER_OFF_PMU_RTC0_EN_POS  (22)
#define PMU_RTC0_RTC_RG_GPIO_POWER_OFF_RTC0_EN      (1<<23)
#define PMU_RTC0_RTC_RG_GPIO_POWER_OFF_RTC0_EN_POS  (23)
#define PMU_RTC0_RTC_RG_WDG_RSTN_POWER_OFF_RTC0_EN      (1<<24)
#define PMU_RTC0_RTC_RG_WDG_RSTN_POWER_OFF_RTC0_EN_POS  (24)
#define PMU_RTC0_RTC_RG_LONG_PBINT_POWER_OFF_EN      (1<<25)
#define PMU_RTC0_RTC_RG_LONG_PBINT_POWER_OFF_EN_POS  (25)
#define PMU_RTC0_RTC_RG_PB_INT_LONG_RST_POWER_OFF_RTC0_EN      (1<<26)
#define PMU_RTC0_RTC_RG_PB_INT_LONG_RST_POWER_OFF_RTC0_EN_POS  (26)
#define PMU_RTC0_RTC_RG_DEVICE_SET      (1<<27)
#define PMU_RTC0_RTC_RG_DEVICE_SET_POS  (27)
#define PMU_RTC0_RTC_RG_RESETN_RTC_CNT      (1<<28)
#define PMU_RTC0_RTC_RG_RESETN_RTC_CNT_POS  (28)
#define PMU_RTC0_RTC_RG_PRESETN_RTC_CNT      (1<<29)
#define PMU_RTC0_RTC_RG_PRESETN_RTC_CNT_POS  (29)
#define PMU_RTC0_RTC_RG_WDG_RST_RTC_RF_EN      (1<<30)
#define PMU_RTC0_RTC_RG_WDG_RST_RTC_RF_EN_POS  (30)
#define PMU_RTC0_RTC_RG_AON_GPIO_NEG_CLR_EN      (1<<31)
#define PMU_RTC0_RTC_RG_AON_GPIO_NEG_CLR_EN_POS  (31)

//pmu_rtc0_cfg4
#define PMU_RTC0_RTC_RG_INT_EN          (1<<0)
#define PMU_RTC0_RTC_RG_INT_EN_POS      (0)
#define PMU_RTC0_RTC_RG_RTC_CNT_INT_EN      (1<<1)
#define PMU_RTC0_RTC_RG_RTC_CNT_INT_EN_POS  (1)
#define PMU_RTC0_RTC_RG_INT_MASK(n)      (((n)&31)<<2)
#define PMU_RTC0_RTC_RG_INT_MASK_LSB     (2)
#define PMU_RTC0_RTC_RG_INT_MASK_MASK    (31<<2)
#define PMU_RTC0_RTC_RG_RTC_CNT_IRQ_MASK      (1<<7)
#define PMU_RTC0_RTC_RG_RTC_CNT_IRQ_MASK_POS  (7)
#define PMU_RTC0_RTC_RG_INT_CLR1        (1<<8)
#define PMU_RTC0_RTC_RG_INT_CLR1_POS    (8)
#define PMU_RTC0_RTC_RG_INT_CLR2        (1<<9)
#define PMU_RTC0_RTC_RG_INT_CLR2_POS    (9)
#define PMU_RTC0_RTC_RG_INT_CLR3        (1<<10)
#define PMU_RTC0_RTC_RG_INT_CLR3_POS    (10)
#define PMU_RTC0_RTC_RG_INT_CLR4        (1<<11)
#define PMU_RTC0_RTC_RG_INT_CLR4_POS    (11)
#define PMU_RTC0_RTC_RG_INT_CLR5        (1<<12)
#define PMU_RTC0_RTC_RG_INT_CLR5_POS    (12)
#define PMU_RTC0_RTC_RG_RTC_CNT_IRQ_CLR      (1<<13)
#define PMU_RTC0_RTC_RG_RTC_CNT_IRQ_CLR_POS  (13)
#define PMU_RTC0_RTC_RG_INT_RAW_STATUS(n)      (((n)&31)<<14)
#define PMU_RTC0_RTC_RG_INT_RAW_STATUS_LSB     (14)
#define PMU_RTC0_RTC_RG_INT_RAW_STATUS_MASK    (31<<14)
#define PMU_RTC0_RTC_CNT_IRQ_RAW_STATUS      (1<<19)
#define PMU_RTC0_RTC_CNT_IRQ_RAW_STATUS_POS  (19)
#define PMU_RTC0_RTC_RG_INT_MASK_STATUS(n)      (((n)&31)<<20)
#define PMU_RTC0_RTC_RG_INT_MASK_STATUS_LSB     (20)
#define PMU_RTC0_RTC_RG_INT_MASK_STATUS_MASK    (31<<20)
#define PMU_RTC0_RTC_CNT_IRQ_MASK_STATUS      (1<<25)
#define PMU_RTC0_RTC_CNT_IRQ_MASK_STATUS_POS  (25)
#define PMU_RTC0_RTC_RG_GPIOA_HOLD(n)      (((n)&7)<<26)
#define PMU_RTC0_RTC_RG_GPIOA_HOLD_LSB     (26)
#define PMU_RTC0_RTC_RG_GPIOA_HOLD_MASK    (7<<26)
#define PMU_RTC0_RTC_RG_GPIOB_HOLD      (1<<29)
#define PMU_RTC0_RTC_RG_GPIOB_HOLD_POS  (29)
#define PMU_RTC0_RTC_RG_FLS_HOLD        (1<<30)
#define PMU_RTC0_RTC_RG_FLS_HOLD_POS    (30)

//pmu_rtc0_cfg5
#define PMU_RTC0_RTC_RG_RTC_CNT_LD_VALUE(n)      (((n)&0xFFFFFFFF)<<0)
#define PMU_RTC0_RTC_RG_RTC_CNT_LD_VALUE_LSB     (0)
#define PMU_RTC0_RTC_RG_RTC_CNT_LD_VALUE_MASK    (0xFFFFFFFF<<0)

//pmu_rtc0_cfg6
#define PMU_RTC0_RTC_CNT_VALUE(n)       (((n)&0xFFFFFFFF)<<0)
#define PMU_RTC0_RTC_CNT_VALUE_LSB      (0)
#define PMU_RTC0_RTC_CNT_VALUE_MASK     (0xFFFFFFFF<<0)

//pmu_rtc0_cfg7
#define PMU_RTC0_RTC_RG_RTC_CNT_ENABLE      (1<<0)
#define PMU_RTC0_RTC_RG_RTC_CNT_ENABLE_POS  (0)
#define PMU_RTC0_RTC_RG_RTC_CNT_LD_VLD      (1<<1)
#define PMU_RTC0_RTC_RG_RTC_CNT_LD_VLD_POS  (1)
#define PMU_RTC0_RTC_RG_RTC_CNT_MODE      (1<<2)
#define PMU_RTC0_RTC_RG_RTC_CNT_MODE_POS  (2)
#define PMU_RTC0_RTC_RG_BOR_LOW_DEGLITCH_TH(n)      (((n)&15)<<3)
#define PMU_RTC0_RTC_RG_BOR_LOW_DEGLITCH_TH_LSB     (3)
#define PMU_RTC0_RTC_RG_BOR_LOW_DEGLITCH_TH_MASK    (15<<3)
#define PMU_RTC0_RTC_RG_BOR_LOW_DEGLITCH_EN      (1<<7)
#define PMU_RTC0_RTC_RG_BOR_LOW_DEGLITCH_EN_POS  (7)
#define PMU_RTC0_RTC_RG_XTAL_40M_26M_SOFT_SEL      (1<<8)
#define PMU_RTC0_RTC_RG_XTAL_40M_26M_SOFT_SEL_POS  (8)
#define PMU_RTC0_RTC_RG_XTAL_40M_26M_HW_DETECT_HIGH_LATCH_CLR      (1<<9)
#define PMU_RTC0_RTC_RG_XTAL_40M_26M_HW_DETECT_HIGH_LATCH_CLR_POS  (9)
#define PMU_RTC0_XTAL_40M_26M_HW_DETECT_HIGH_LATCH      (1<<10)
#define PMU_RTC0_XTAL_40M_26M_HW_DETECT_HIGH_LATCH_POS  (10)
#define PMU_RTC0_RTC_RG_PB_INT_LONG_POR_SET_CLR      (1<<11)
#define PMU_RTC0_RTC_RG_PB_INT_LONG_POR_SET_CLR_POS  (11)
#define PMU_RTC0_RTC_RG_ALM_INT_SET_CLR      (1<<12)
#define PMU_RTC0_RTC_RG_ALM_INT_SET_CLR_POS  (12)
#define PMU_RTC0_RTC_RG_WDG_PWR_ON_SET_CLR      (1<<13)
#define PMU_RTC0_RTC_RG_WDG_PWR_ON_SET_CLR_POS  (13)
#define PMU_RTC0_RTC_RG_BOR_PWR_ON_SET_CLR      (1<<14)
#define PMU_RTC0_RTC_RG_BOR_PWR_ON_SET_CLR_POS  (14)
#define PMU_RTC0_RTC_RG_POR_CHIP_VBAT_FLAG      (1<<15)
#define PMU_RTC0_RTC_RG_POR_CHIP_VBAT_FLAG_POS  (15)
#define PMU_RTC0_RTC_RG_PWR_ON_SRC_STATUS(n)      (((n)&0xFF)<<16)
#define PMU_RTC0_RTC_RG_PWR_ON_SRC_STATUS_LSB     (16)
#define PMU_RTC0_RTC_RG_PWR_ON_SRC_STATUS_MASK    (0xFF<<16)
#define PMU_RTC0_RTC_RG_PBINT_DEBC_CNT_TH(n)      (((n)&0xFF)<<24)
#define PMU_RTC0_RTC_RG_PBINT_DEBC_CNT_TH_LSB     (24)
#define PMU_RTC0_RTC_RG_PBINT_DEBC_CNT_TH_MASK    (0xFF<<24)

//pmu_rtc0_wdg4_cnt_ini
#define PMU_RTC0_RTC_RG_WDG4_CNT_INI(n)      (((n)&0xFFFFFFFF)<<0)
#define PMU_RTC0_RTC_RG_WDG4_CNT_INI_LSB     (0)
#define PMU_RTC0_RTC_RG_WDG4_CNT_INI_MASK    (0xFFFFFFFF<<0)

#endif
