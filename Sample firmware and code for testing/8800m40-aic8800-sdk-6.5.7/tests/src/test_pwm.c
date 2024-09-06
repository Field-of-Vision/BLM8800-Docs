/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "pmic_api.h"
#include "reg_sysctrl.h"
#include "reg_iomux.h"
#include "reg_pwm.h"
#include "plf.h"
#include "dbg.h"

#ifdef CFG_TEST_PWM

#include "pwm_api.h"
/*
 * MACROS
 ****************************************************************************************
 */
#define UART_PRINT              dbg
#define PWM_TIMER_CNT           1300
#define AONPWM_TIMER_CNT        2600

#define AON_PWM_FREQ            2600
#define AON_PWM_DUTY_RATIO      30

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void pwm_test(void)
{
    UART_PRINT("\nPWM test start\n");
    #if (PLF_AIC8800)
    pwm_channal_init(PWM0_CHANNAL_PA6);
    pwm_enable(PWM0_CHANNAL_PA6, 20, 10);
    aonpwm_channal_init(AONPWM0_CHANNAL_PB3);
    aonpwm_enable(AONPWM0_CHANNAL_PB3, AON_PWM_FREQ, AON_PWM_DUTY_RATIO);

    // change pwm duty test
    while(1) {

        for(int i=10; i<100; i+=1) {
            pwm_set_duty(PWM0_CHANNAL_PA6, 20, i);
            rtos_task_suspend(100);
        }
        for(int i=100; i>10; i-=1) {
            pwm_set_duty(PWM0_CHANNAL_PA6, 20, i);
            rtos_task_suspend(100);
        }
    }

    #if 0
    #if PLF_PMIC_VER_AUD
    // hclk divider, 26M
    PMIC_MEM_WRITE((unsigned int)(&aic1000audSysctrl->pclk_div),
        (AIC1000AUD_SYS_CTRL_CFG_PCLK_DIV_DENOM(0x1) | AIC1000AUD_SYS_CTRL_CFG_PCLK_DIV_UPDATE));
    // hclk sel
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000audSysctrl->clk_sel),
        (AIC1000AUD_SYS_CTRL_CFG_CLK_PWM_SEL), (AIC1000AUD_SYS_CTRL_CFG_CLK_PWM_SEL));

    // gpiob iomux
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000audIomux->GPCFG[0]),
        AIC1000AUD_IOMUX_PAD_GPIO_0_SEL_FUN_PWM_0_SEL, AIC1000AUD_IOMUX_PAD_GPIO_SEL(0xF));

    // cfg timer, counter=ld_value->0,ld_value->0,ld_value->0,...
    PMIC_MEM_WRITE((unsigned int)(&aic1000audLedPwm->tmr0_ld_value), tmr_cnt_total - 1);
    PMIC_MEM_WRITE((unsigned int)(&aic1000audLedPwm->tmr0_cfg),
        (AIC1000AUD_LED_PWM_TMR_MODE | AIC1000AUD_LED_PWM_TMR_RUN));

    // cfg pwm, [start, end) is high
    PMIC_MEM_WRITE((unsigned int)(&aic1000audLedPwm->pwm0_sta_val), tmr_cnt_total - 1);
    PMIC_MEM_WRITE((unsigned int)(&aic1000audLedPwm->pwm0_end_val), (tmr_cnt_total - 1 - tmr_cnt_high));
    PMIC_MEM_WRITE((unsigned int)(&aic1000audLedPwm->pwm0_cfg),
        (AIC1000AUD_LED_PWM_PWM_RUN | /*AIC1000AUD_LED_PWM_PWM_DEFAULT_VAL |*/
        AIC1000AUD_LED_PWM_PWM_TMR_SEL(0) | AIC1000AUD_LED_PWM_PWM_UPDATE)); // must sel tmr0, default val: high
    #endif
    #endif
    #endif

    #if (PLF_AIC8800MC)
    pwm_channal_init(PWM0_CHANNAL_PA4);
    pwm_channal_init(PWM1_CHANNAL_PA5);
    pwm_channal_init(PWM2_CHANNAL_PA14);
    pwm_tim_init(PWM_TIMER_CNT);
    pwm_enable(PWM_CHANNAL_0, PWM_TIMER_CNT, 200);
    pwm_enable(PWM_CHANNAL_1, PWM_TIMER_CNT, 600);
    pwm_enable(PWM_CHANNAL_2, PWM_TIMER_CNT, 1000);

    aonpwm_channal_init(AONPWM0_CHANNAL_PA6);
    aonpwm_channal_init(AONPWM1_CHANNAL_PA7);
    aonpwm_tim_init(AONPWM_TIMER_CNT);
    aonpwm_enable(AONPwM_CHANNAL_0, AONPWM_TIMER_CNT, 200);
    aonpwm_enable(AONPwM_CHANNAL_1, AONPWM_TIMER_CNT, 500);
    #endif

    #if (PLF_AIC8800M40)
    //pwm_channal_init(PWM0_CHANNAL_PA0);
    //pwm_channal_init(PWM1_CHANNAL_PA1);
    //pwm_channal_init(PWM2_CHANNAL_PA2);
    pwm_channal_init(PWM0_CHANNAL_PA13);
    pwm_channal_init(PWM1_CHANNAL_PA14);
    pwm_channal_init(PWM2_CHANNAL_PA15);
    pwm_tim_init(PWM_TIMER_CNT);
    pwm_enable(PWM_CHANNAL_0, PWM_TIMER_CNT, 200);
    pwm_enable(PWM_CHANNAL_1, PWM_TIMER_CNT, 600);
    pwm_enable(PWM_CHANNAL_2, PWM_TIMER_CNT, 1000);

    //aonpwm_channal_init(AONPWM0_CHANNAL_PB0);
    //aonpwm_channal_init(AONPWM1_CHANNAL_PB1);
    //aonpwm_channal_init(AONPWM2_CHANNAL_PB2);
    aonpwm_channal_init(AONPWM0_CHANNAL_PA7);
    //aonpwm_channal_init(AONPWM1_CHANNAL_PA9);
    aonpwm_channal_init(AONPWM2_CHANNAL_PA12);
    aonpwm_tim_init(AONPWM_TIMER_CNT);
    aonpwm_enable(AONPWM_CHANNAL_0, AONPWM_TIMER_CNT, 200);
    aonpwm_enable(AONPWM_CHANNAL_1, AONPWM_TIMER_CNT, 300);
    aonpwm_enable(AONPWM_CHANNAL_2, AONPWM_TIMER_CNT, 500);
    #endif

    UART_PRINT("\nPWM test done\n");
}

#endif /* CFG_TEST_PWM */
