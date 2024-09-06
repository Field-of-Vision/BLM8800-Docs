#ifndef __PWM_API_H_
#define __PWM_API_H__

#include "reg_sysctrl.h"
#include "reg_iomux.h"
#include "reg_pwm.h"

enum PWM_COUNT_MODE{
    CNT_UP     = 0x00000000+40,
    CNT_DOWN   = 0x80000000+40,
    CNT_STABLE = 0x00000000+0
};

enum PWM_CHANNAL{
    PWM_CHANNAL_0,
    PWM_CHANNAL_1,
    PWM_CHANNAL_2,
    AONPWM_CHANNAL_0,
    AONPWM_CHANNAL_1,
    AONPWM_CHANNAL_2
};

enum PWM_CHANNAL_GPIO{
    PWM0_CHANNAL_PA0,
    PWM1_CHANNAL_PA1,
    PWM2_CHANNAL_PA2,
    PWM0_CHANNAL_PA13,
    PWM1_CHANNAL_PA14,
    PWM2_CHANNAL_PA15,
    PWM0_CHANNAL_PB4,
    PWM1_CHANNAL_PB5,
    PWM2_CHANNAL_PB6,
    AONPWM0_CHANNAL_PB0,
    AONPWM1_CHANNAL_PB1,
    AONPWM2_CHANNAL_PB2,
    AONPWM0_CHANNAL_PA7,
    AONPWM1_CHANNAL_PA9,
    AONPWM2_CHANNAL_PA12
};

void pwm_channal_init(int pwm_gpidx);
void pwm_tim_init(uint32_t tmr_cnt);
void pwm_enable(int pwm_chan, uint32_t tmr_cnt, uint32_t dty_cnt);
void aonpwm_channal_init(int pwm_gpidx);
void aonpwm_tim_init(uint32_t tmr_cnt);
void aonpwm_enable(int pwm_chan, uint32_t tmr_cnt, uint32_t dty_cnt);

#endif
