#ifndef _REG_TIMER_H_
#define _REG_TIMER_H_

#include "chip.h"

/**
 * Timer registers
 */
typedef struct {
  __IO uint32_t                          tmr_cfg;                      //0x00000000
  __IO uint32_t                          tmr_pr;                       //0x00000004
  __IO uint32_t                          tmr_pc;                       //0x00000008
  __IO uint32_t                          tmr_mr0;                      //0x0000000C
  __IO uint32_t                          tmr_mr1;                      //0x00000010
  __IO uint32_t                          tmr_mr2;                      //0x00000014
  __IO uint32_t                          tmr_delta0;                   //0x00000018
  __IO uint32_t                          tmr_delta1;                   //0x0000001C
  __IO uint32_t                          tmr_delta2;                   //0x00000020
  __IO uint32_t                          tmr_rtc_clk_div;              //0x00000024
  __IO uint32_t                          tmr_int_mask_enable;          //0x00000028
  __IO uint32_t                          tmr_int_mask_clear;           //0x0000002C
  __IO uint32_t                          tmr_int_raw;                  //0x00000030
  __IO uint32_t                          tmr_int_status;               //0x00000034
} AIC_TIM_TypeDef;

/**
 * Timer Peripherals
 */
static AIC_TIM_TypeDef    * const AIC_TIM0 = ((AIC_TIM_TypeDef    *)AIC_TIM0_BASE);
static AIC_TIM_TypeDef    * const AIC_TIM1 = ((AIC_TIM_TypeDef    *)AIC_TIM1_BASE);

//tmr_cfg
#define TIMER_CFG_TMR_RUN               (1<<0)
#define TIMER_CFG_TMR_RUN_POS           (0)
#define TIMER_CFG_TMR_RESET             (1<<1)
#define TIMER_CFG_TMR_RESET_POS         (1)

//tmr_pr
#define TIMER_CFG_TMR_PR(n)             (((n)&0xFFFFFFFF)<<0)
#define TIMER_CFG_TMR_PR_LSB            (0)
#define TIMER_CFG_TMR_PR_MASK           (0xFFFFFFFF<<0)

//tmr_pc
#define TIMER_CFG_TMR_PC(n)             (((n)&0xFFFFFFFF)<<0)
#define TIMER_CFG_TMR_PC_LSB            (0)
#define TIMER_CFG_TMR_PC_MASK           (0xFFFFFFFF<<0)

//tmr_mr0
#define TIMER_CFG_TMR_MR0(n)            (((n)&0xFFFFFFFF)<<0)
#define TIMER_CFG_TMR_MR0_LSB           (0)
#define TIMER_CFG_TMR_MR0_MASK          (0xFFFFFFFF<<0)

//tmr_mr1
#define TIMER_CFG_TMR_MR1(n)            (((n)&0xFFFFFFFF)<<0)
#define TIMER_CFG_TMR_MR1_LSB           (0)
#define TIMER_CFG_TMR_MR1_MASK          (0xFFFFFFFF<<0)

//tmr_mr2
#define TIMER_CFG_TMR_MR2(n)            (((n)&0xFFFFFFFF)<<0)
#define TIMER_CFG_TMR_MR2_LSB           (0)
#define TIMER_CFG_TMR_MR2_MASK          (0xFFFFFFFF<<0)

//tmr_delta0
#define TIMER_CFG_TMR_DELTA0(n)         (((n)&0xFFFFFFFF)<<0)
#define TIMER_CFG_TMR_DELTA0_LSB        (0)
#define TIMER_CFG_TMR_DELTA0_MASK       (0xFFFFFFFF<<0)

//tmr_delta1
#define TIMER_CFG_TMR_DELTA1(n)         (((n)&0xFFFFFFFF)<<0)
#define TIMER_CFG_TMR_DELTA1_LSB        (0)
#define TIMER_CFG_TMR_DELTA1_MASK       (0xFFFFFFFF<<0)

//tmr_delta2
#define TIMER_CFG_TMR_DELTA2(n)         (((n)&0xFFFFFFFF)<<0)
#define TIMER_CFG_TMR_DELTA2_LSB        (0)
#define TIMER_CFG_TMR_DELTA2_MASK       (0xFFFFFFFF<<0)

//tmr_rtc_clk_div
#define TIMER_CFG_TMR_RTC_CLK_DIV(n)      (((n)&0xFFFF)<<0)
#define TIMER_CFG_TMR_RTC_CLK_DIV_LSB     (0)
#define TIMER_CFG_TMR_RTC_CLK_DIV_MASK    (0xFFFF<<0)
#define TIMER_CFG_TMR_RTC_CLK_DIV_UPDATE      (1<<16)
#define TIMER_CFG_TMR_RTC_CLK_DIV_UPDATE_POS  (16)

//tmr_int_mask_enable
#define TIMER_CFG_TMR_MATCH0_INT_MASK_ENABLE      (1<<0)
#define TIMER_CFG_TMR_MATCH0_INT_MASK_ENABLE_POS  (0)
#define TIMER_CFG_TMR_MATCH1_INT_MASK_ENABLE      (1<<1)
#define TIMER_CFG_TMR_MATCH1_INT_MASK_ENABLE_POS  (1)
#define TIMER_CFG_TMR_MATCH2_INT_MASK_ENABLE      (1<<2)
#define TIMER_CFG_TMR_MATCH2_INT_MASK_ENABLE_POS  (2)

//tmr_int_mask_clear
#define TIMER_CFG_TMR_MATCH0_INT_MASK_CLEAR      (1<<0)
#define TIMER_CFG_TMR_MATCH0_INT_MASK_CLEAR_POS  (0)
#define TIMER_CFG_TMR_MATCH1_INT_MASK_CLEAR      (1<<1)
#define TIMER_CFG_TMR_MATCH1_INT_MASK_CLEAR_POS  (1)
#define TIMER_CFG_TMR_MATCH2_INT_MASK_CLEAR      (1<<2)
#define TIMER_CFG_TMR_MATCH2_INT_MASK_CLEAR_POS  (2)

//tmr_int_raw
#define TIMER_CFG_TMR_MATCH0_INT_RAW      (1<<0)
#define TIMER_CFG_TMR_MATCH0_INT_RAW_POS  (0)
#define TIMER_CFG_TMR_MATCH1_INT_RAW      (1<<1)
#define TIMER_CFG_TMR_MATCH1_INT_RAW_POS  (1)
#define TIMER_CFG_TMR_MATCH2_INT_RAW      (1<<2)
#define TIMER_CFG_TMR_MATCH2_INT_RAW_POS  (2)

//tmr_int_status
#define TIMER_CFG_TMR_MATCH0_INT_STATUS      (1<<0)
#define TIMER_CFG_TMR_MATCH0_INT_STATUS_POS  (0)
#define TIMER_CFG_TMR_MATCH1_INT_STATUS      (1<<1)
#define TIMER_CFG_TMR_MATCH1_INT_STATUS_POS  (1)
#define TIMER_CFG_TMR_MATCH2_INT_STATUS      (1<<2)
#define TIMER_CFG_TMR_MATCH2_INT_STATUS_POS  (2)

/**
 * AON Timer registers
 */
typedef struct {
  __IO uint32_t CTL;            /* 0x000: Control */
  __IO uint32_t TD;             /* 0x004: Tick Divider */
  __IO uint32_t IC;             /* 0x008: Interrupt Control */
  __I  uint32_t IS;             /* 0x00C: Interrupt Status */
  __IO uint32_t TCL;            /* 0x010: Timer Counter low-32bit */
  __IO uint32_t TCH;            /* 0x014: Timer Counter high-16bit */
       uint32_t RESERVED0[2U];
  struct {
    __IO uint32_t L;            /* 0x020: Match Register low-32bit */
    __IO uint32_t H;            /* 0x024: Match Register high-16bit */
  } MR[4];
} AIC_AONTIM_TypeDef;

/**
 * Timer Peripherals
 */
static AIC_AONTIM_TypeDef * const AIC_TIM2 = ((AIC_AONTIM_TypeDef *)AIC_TIM2_BASE);

#endif /* _REG_TIMER_H_ */
