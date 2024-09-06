#ifndef _REG_PWM_H_
#define _REG_PWM_H_

#include "chip.h"

/* ========================================================================== */
/* ====================    Pulse Width Modulation (PWM)   =================== */
/* ========================================================================== */
typedef struct {
  __IO uint32_t                          tmr0_ld_value;                //0x00000000
  __IO uint32_t Reserved_00000004;                    //0x00000004
  __IO uint32_t                          tmr0_cnt_value;               //0x00000008
  __IO uint32_t Reserved_0000000C;                    //0x0000000C
  __IO uint32_t                          tmr0_cfg;                     //0x00000010
  __IO uint32_t                          tmr0_int_ctrl;                //0x00000014
  __IO uint32_t                          tmr0_cnt_read;                //0x00000018
  __IO uint32_t Reserved_0000001C;                    //0x0000001C
  __IO uint32_t                          tmr1_ld_value;                //0x00000020
  __IO uint32_t Reserved_00000024;                    //0x00000024
  __IO uint32_t                          tmr1_cnt_value;               //0x00000028
  __IO uint32_t Reserved_0000002C;                    //0x0000002C
  __IO uint32_t                          tmr1_cfg;                     //0x00000030
  __IO uint32_t                          tmr1_int_ctrl;                //0x00000034
  __IO uint32_t                          tmr1_cnt_read;                //0x00000038
  __IO uint32_t Reserved_0000003C;                    //0x0000003C
  __IO uint32_t                          tmr2_ld_value;                //0x00000040
  __IO uint32_t Reserved_00000044;                    //0x00000044
  __IO uint32_t                          tmr2_cnt_value;               //0x00000048
  __IO uint32_t Reserved_0000004C;                    //0x0000004C
  __IO uint32_t                          tmr2_cfg;                     //0x00000050
  __IO uint32_t                          tmr2_int_ctrl;                //0x00000054
  __IO uint32_t                          tmr2_cnt_read;                //0x00000058
  __IO uint32_t Reserved_0000005C[41];                //0x0000005C
  __IO uint32_t                          pwm0_sta_val;                 //0x00000100
  __IO uint32_t                          pwm0_end_val;                 //0x00000104
  __IO uint32_t                          pwm0_step_cfg0;               //0x00000108
  __IO uint32_t                          pwm0_step_cfg1;               //0x0000010C
  __IO uint32_t                          pwm0_cfg;                     //0x00000110
  __IO uint32_t                          pwm0_int_ctrl;                //0x00000114
  __IO uint32_t                          pwm0_end_val_use;             //0x00000118
  __IO uint32_t                          pwm0_step_cnt;                //0x0000011C
  __IO uint32_t                          pwm1_sta_val;                 //0x00000120
  __IO uint32_t                          pwm1_end_val;                 //0x00000124
  __IO uint32_t                          pwm1_step_cfg0;               //0x00000128
  __IO uint32_t                          pwm1_step_cfg1;               //0x0000012C
  __IO uint32_t                          pwm1_cfg;                     //0x00000130
  __IO uint32_t                          pwm1_int_ctrl;                //0x00000134
  __IO uint32_t                          pwm1_end_val_use;             //0x00000138
  __IO uint32_t                          pwm1_step_cnt;                //0x0000013C
  __IO uint32_t                          pwm2_sta_val;                 //0x00000140
  __IO uint32_t                          pwm2_end_val;                 //0x00000144
  __IO uint32_t                          pwm2_step_cfg0;               //0x00000148
  __IO uint32_t                          pwm2_step_cfg1;               //0x0000014C
  __IO uint32_t                          pwm2_cfg;                     //0x00000150
  __IO uint32_t                          pwm2_int_ctrl;                //0x00000154
  __IO uint32_t                          pwm2_end_val_use;             //0x00000158
  __IO uint32_t                          pwm2_step_cnt;                //0x0000015C
} AIC_PWM_TypeDef;

static AIC_PWM_TypeDef * const AIC_PWM    = ((AIC_PWM_TypeDef *)AIC_PWM_BASE);
static AIC_PWM_TypeDef * const AIC_AONPWM = ((AIC_PWM_TypeDef *)AIC_AONPWM_BASE);

//tmr0_ld_value
#define PWM_TMR_LD_VALUE(n)             (((n)&0xFFFFFFFF)<<0)
#define PWM_TMR_LD_VALUE_LSB            (0)
#define PWM_TMR_LD_VALUE_MASK           (0xFFFFFFFF<<0)

//tmr0_cnt_value
#define PWM_TMR_CNT_VALUE(n)            (((n)&0xFFFFFFFF)<<0)
#define PWM_TMR_CNT_VALUE_LSB           (0)
#define PWM_TMR_CNT_VALUE_MASK          (0xFFFFFFFF<<0)

//tmr0_cfg
#define PWM_TMR_MODE                    (1<<0)
#define PWM_TMR_MODE_POS                (0)
#define PWM_TMR_RUN                     (1<<1)
#define PWM_TMR_RUN_POS                 (1)

//tmr0_int_ctrl
#define PWM_TMR_INT_EN                  (1<<0)
#define PWM_TMR_INT_EN_POS              (0)
#define PWM_TMR_INT_RAW                 (1<<1)
#define PWM_TMR_INT_RAW_POS             (1)
#define PWM_TMR_INT_STATUS              (1<<2)
#define PWM_TMR_INT_STATUS_POS          (2)
#define PWM_TMR_INT_CLR                 (1<<3)
#define PWM_TMR_INT_CLR_POS             (3)

//tmr0_cnt_read
#define PWM_TMR_CNT_READ(n)             (((n)&0xFFFFFFFF)<<0)
#define PWM_TMR_CNT_READ_LSB            (0)
#define PWM_TMR_CNT_READ_MASK           (0xFFFFFFFF<<0)

//tmr1_ld_value
//#define PWM_TMR_LD_VALUE(n)      (((n)&0xFFFFFFFF)<<0)

//tmr1_cnt_value
//#define PWM_TMR_CNT_VALUE(n)     (((n)&0xFFFFFFFF)<<0)

//tmr1_cfg
//#define PWM_TMR_MODE             (1<<0)
//#define PWM_TMR_RUN              (1<<1)

//tmr1_int_ctrl
//#define PWM_TMR_INT_EN           (1<<0)
//#define PWM_TMR_INT_RAW          (1<<1)
//#define PWM_TMR_INT_STATUS       (1<<2)
//#define PWM_TMR_INT_CLR          (1<<3)

//tmr1_cnt_read
//#define PWM_TMR_CNT_READ(n)      (((n)&0xFFFFFFFF)<<0)

//tmr2_ld_value
//#define PWM_TMR_LD_VALUE(n)      (((n)&0xFFFFFFFF)<<0)

//tmr2_cnt_value
//#define PWM_TMR_CNT_VALUE(n)     (((n)&0xFFFFFFFF)<<0)

//tmr2_cfg
//#define PWM_TMR_MODE             (1<<0)
//#define PWM_TMR_RUN              (1<<1)

//tmr2_int_ctrl
//#define PWM_TMR_INT_EN           (1<<0)
//#define PWM_TMR_INT_RAW          (1<<1)
//#define PWM_TMR_INT_STATUS       (1<<2)
//#define PWM_TMR_INT_CLR          (1<<3)

//tmr2_cnt_read
#define PWM_TMR2_CNT_READ(n)            (((n)&0xFFFFFFFF)<<0)
#define PWM_TMR2_CNT_READ_LSB           (0)
#define PWM_TMR2_CNT_READ_MASK          (0xFFFFFFFF<<0)

//pwm0_sta_val
#define PWM_PWM_STA_VAL(n)              (((n)&0xFFFFFFFF)<<0)
#define PWM_PWM_STA_VAL_LSB             (0)
#define PWM_PWM_STA_VAL_MASK            (0xFFFFFFFF<<0)

//pwm0_end_val
#define PWM_PWM_END_VAL(n)              (((n)&0xFFFFFFFF)<<0)
#define PWM_PWM_END_VAL_LSB             (0)
#define PWM_PWM_END_VAL_MASK            (0xFFFFFFFF<<0)

//pwm0_step_cfg0
#define PWM_PWM_STEP_CYC(n)             (((n)&0xFFFF)<<0)
#define PWM_PWM_STEP_CYC_LSB            (0)
#define PWM_PWM_STEP_CYC_MASK           (0xFFFF<<0)
#define PWM_PWM_STEP_NUM(n)             (((n)&0xFFFF)<<16)
#define PWM_PWM_STEP_NUM_LSB            (16)
#define PWM_PWM_STEP_NUM_MASK           (0xFFFF<<16)

//pwm0_step_cfg1
#define PWM_PWM_STEP_VALUE(n)           (((n)&0xFFFFFFFF)<<0)
#define PWM_PWM_STEP_VALUE_LSB          (0)
#define PWM_PWM_STEP_VALUE_MASK         (0xFFFFFFFF<<0)

//pwm0_cfg
#define PWM_PWM_RUN                     (1<<0)
#define PWM_PWM_RUN_POS                 (0)
#define PWM_PWM_INC_MODE                (1<<1)
#define PWM_PWM_INC_MODE_POS            (1)
#define PWM_PWM_DEFAULT_VAL             (1<<2)
#define PWM_PWM_DEFAULT_VAL_POS         (2)
#define PWM_PWM_TMR_SEL(n)              (((n)&3)<<16)
#define PWM_PWM_TMR_SEL_LSB             (16)
#define PWM_PWM_TMR_SEL_MASK            (3<<16)
#define PWM_PWM_UPDATE                  (1<<31)
#define PWM_PWM_UPDATE_POS              (31)

//pwm0_int_ctrl
#define PWM_PWM_INT_EN                  (1<<0)
#define PWM_PWM_INT_EN_POS              (0)
#define PWM_PWM_INT_RAW                 (1<<1)
#define PWM_PWM_INT_RAW_POS             (1)
#define PWM_PWM_INT_STATUS              (1<<2)
#define PWM_PWM_INT_STATUS_POS          (2)
#define PWM_PWM_INT_CLR                 (1<<3)
#define PWM_PWM_INT_CLR_POS             (3)

//pwm0_end_val_use
#define PWM_PWM_END_VAL_USE(n)          (((n)&0xFFFFFFFF)<<0)
#define PWM_PWM_END_VAL_USE_LSB         (0)
#define PWM_PWM_END_VAL_USE_MASK        (0xFFFFFFFF<<0)

//pwm0_step_cnt
#define PWM_PWM_STEP_CYC_CNT(n)         (((n)&0xFFFF)<<0)
#define PWM_PWM_STEP_CYC_CNT_LSB        (0)
#define PWM_PWM_STEP_CYC_CNT_MASK       (0xFFFF<<0)
#define PWM_PWM_STEP_NUM_CNT(n)         (((n)&0xFFFF)<<16)
#define PWM_PWM_STEP_NUM_CNT_LSB        (16)
#define PWM_PWM_STEP_NUM_CNT_MASK       (0xFFFF<<16)

//pwm1_sta_val
//#define PWM_PWM_STA_VAL(n)       (((n)&0xFFFFFFFF)<<0)

//pwm1_end_val
//#define PWM_PWM_END_VAL(n)       (((n)&0xFFFFFFFF)<<0)

//pwm1_step_cfg0
//#define PWM_PWM_STEP_CYC(n)      (((n)&0xFFFF)<<0)
//#define PWM_PWM_STEP_NUM(n)      (((n)&0xFFFF)<<16)

//pwm1_step_cfg1
//#define PWM_PWM_STEP_VALUE(n)    (((n)&0xFFFFFFFF)<<0)

//pwm1_cfg
//#define PWM_PWM_RUN              (1<<0)
//#define PWM_PWM_INC_MODE         (1<<1)
//#define PWM_PWM_DEFAULT_VAL      (1<<2)
//#define PWM_PWM_TMR_SEL(n)       (((n)&3)<<16)
//#define PWM_PWM_UPDATE           (1<<31)

//pwm1_int_ctrl
//#define PWM_PWM_INT_EN           (1<<0)
//#define PWM_PWM_INT_RAW          (1<<1)
//#define PWM_PWM_INT_STATUS       (1<<2)
//#define PWM_PWM_INT_CLR          (1<<3)

//pwm1_end_val_use
//#define PWM_PWM_END_VAL_USE(n)   (((n)&0xFFFFFFFF)<<0)

//pwm1_step_cnt
//#define PWM_PWM_STEP_CYC_CNT(n)  (((n)&0xFFFF)<<0)
//#define PWM_PWM_STEP_NUM_CNT(n)  (((n)&0xFFFF)<<16)

//pwm2_sta_val
//#define PWM_PWM_STA_VAL(n)       (((n)&0xFFFFFFFF)<<0)

//pwm2_end_val
//#define PWM_PWM_END_VAL(n)       (((n)&0xFFFFFFFF)<<0)

//pwm2_step_cfg0
//#define PWM_PWM_STEP_CYC(n)      (((n)&0xFFFF)<<0)
//#define PWM_PWM_STEP_NUM(n)      (((n)&0xFFFF)<<16)

//pwm2_step_cfg1
//#define PWM_PWM_STEP_VALUE(n)    (((n)&0xFFFFFFFF)<<0)

//pwm2_cfg
//#define PWM_PWM_RUN              (1<<0)
//#define PWM_PWM_INC_MODE         (1<<1)
//#define PWM_PWM_DEFAULT_VAL      (1<<2)
//#define PWM_PWM_TMR_SEL(n)       (((n)&3)<<16)
//#define PWM_PWM_UPDATE           (1<<31)

//pwm2_int_ctrl
//#define PWM_PWM_INT_EN           (1<<0)
//#define PWM_PWM_INT_RAW          (1<<1)
//#define PWM_PWM_INT_STATUS       (1<<2)
//#define PWM_PWM_INT_CLR          (1<<3)

//pwm2_end_val_use
//#define PWM_PWM_END_VAL_USE(n)   (((n)&0xFFFFFFFF)<<0)

//pwm2_step_cnt
//#define PWM_PWM_STEP_CYC_CNT(n)  (((n)&0xFFFF)<<0)
//#define PWM_PWM_STEP_NUM_CNT(n)  (((n)&0xFFFF)<<16)

#endif /* _REG_PWM_H_ */
