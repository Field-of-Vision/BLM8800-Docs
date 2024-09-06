#ifndef __PWM_API_H_
#define __PWM_API_H__

#include "reg_sysctrl.h"
#include "reg_iomux.h"
#include "reg_pwm.h"

enum PWM_CHANNAL_GPIO{
    PWM0_CHANNAL_PA6,
    PWM1_CHANNAL_PA7,
    PWM2_CHANNAL_PA8,
    PWM0_CHANNAL_PA12,
    PWM1_CHANNAL_PA13,
    PWM2_CHANNAL_PA14,
    AONPWM0_CHANNAL_PB3,
    AONPWM1_CHANNAL_PB4,
    AONPWM2_CHANNAL_PB5,
    AONPWM3_CHANNAL_PB13,
    AONPWM4_CHANNAL_PB14,
    AONPWM5_CHANNAL_PB15
};


void pwm_channal_init(int pwm_gpidx);
void pwm_enable(int pwm_gpidx, uint32_t freq_hz, uint32_t duty_ratio);
void pwm_set_duty(int pwm_gpidx, uint32_t freq_hz, uint32_t duty_ratio);
void pwm_channal_deinit(int pwm_gpidx);
void aonpwm_channal_init(int pwm_gpidx);
void aonpwm_enable(int pwm_gpidx, uint32_t freq_hz, uint32_t duty_ratio);
void aonpwm_channal_deinit(int pwm_gpidx);

#endif

