/**
 ****************************************************************************************
 *
 * @file pwm_api.c
 *
 * @brief-channal
 * ------------------PWM_CHANNAL_TABLE----------------
 * |    PWMx     |   PWM0    |   PWM1    |   PWM2    |
 * |    GPIOA    |    PA6    |    PA7    |   PA8     |
 * |    GPIOA    |    PB12   |    PA13   |   PA14    |
 * ---------------------------------------------------
 * @brief-frequency, range 1Hz ~ 16K Hz
 * In a PWM-CHANNAL, e.g. PWM0, PA6 and PA12 cann`t be used at the same time. Only one can be use!
 *
 * -----------------------------------AONPWM_CHANNAL_TABLE--------------------------------------------
 * |    PWMx     |   AONPWM0   |   AONPWM1   |   AONPWM2   |   AONPWM3   |   AONPWM4   |   AONPWM5   |
 * |    GPIOB    |     PA3     |     PA4     |     PA5     |     PB13    |     PB14    |     PB15    |
 * ---------------------------------------------------------------------------------------------------
 *
 * @brief-frequency: range 1Hz ~ 2.5M Hz
 * PWM-TIMER-CLK is fixed at 26M. Only timer-count(mod_cnt) and duty(duty_cnt) can be adjust.
 *
 ******************************************************************************************************
 */

/*
 * INCLUDES
 ******************************************************************************************************
 */
#include "pwm_api.h"
#include "dbg.h"

void pwm_channal_init(int pwm_gpidx)
{
    switch(pwm_gpidx) {
        case(PWM0_CHANNAL_PA6):
            iomux_gpio_config_sel_setf(6, 5);
            break;
        case(PWM1_CHANNAL_PA7):
            iomux_gpio_config_sel_setf(7, 5);
            break;
        case(PWM2_CHANNAL_PA8):
            iomux_gpio_config_sel_setf(8, 5);
            break;
        case(PWM0_CHANNAL_PA12):
            iomux_gpio_config_sel_setf(12, 4);
            break;
        case(PWM1_CHANNAL_PA13):
            iomux_gpio_config_sel_setf(13, 4);
            break;
        case(PWM2_CHANNAL_PA14):
            iomux_gpio_config_sel_setf(14, 4);
            break;
        default:
            break;
    }
    cpusysctrl_pclkme_set(CSC_PCLKME_PWM_EN_BIT);
    cpusysctrl_oclkme_set(CSC_OCLKME_PWM_EN_BIT);
}

void pwm_enable(int pwm_gpidx, uint32_t freq_hz, uint32_t duty_ratio)
{
    uint32_t reg_val = 0;
    uint32_t mod_cnt = 1;
    uint32_t duty_cnt = 1;
    uint8_t prescale_coefficient = 0; // 0 : 32k

    prescale_coefficient = 0; // 0 : 32k

    if (freq_hz >= (32000 / 0xFF)) { // 125 ~ 16K
        mod_cnt = (32000 / freq_hz - 1);
        duty_cnt = ((mod_cnt + 1) * duty_ratio / 100);
        prescale_coefficient = 0; // 0 : 32k
    } else if (freq_hz >= (32)) { // 32  ~ 124
        prescale_coefficient = 0x04; // 0x4 : 6400
        mod_cnt = (6400 / freq_hz - 1);
        duty_cnt = ((mod_cnt + 1) * duty_ratio / 100);
    }  else if (freq_hz >= (15)) { // 15  ~ 31
        prescale_coefficient = 0xF; // 0xF : 2000
        mod_cnt = (2000 / freq_hz - 1);
        duty_cnt = ((mod_cnt + 1) * duty_ratio / 100);
    }   else if (freq_hz >= (10)) { // 10  ~ 15
        prescale_coefficient = 0x4F; // 0x4F : 400
        mod_cnt = (400 / freq_hz - 1);
        duty_cnt = ((mod_cnt + 1) * duty_ratio / 100);
    } else {
        prescale_coefficient = 0x7F; // 0x7F : 251
        mod_cnt = (251 / freq_hz - 1);
        duty_cnt = ((mod_cnt + 1) * duty_ratio / 100);
    }

    //dbg("PWM %x %x %x\r\n", mod_cnt, duty_cnt, prescale_coefficient);
    switch(pwm_gpidx) {
        case(PWM0_CHANNAL_PA6):
        case(PWM0_CHANNAL_PA12):
            AIC_PWM->PWM0_CNT |= PWM_PWM0_MOD(mod_cnt);
            AIC_PWM->PWM0_CNT |= PWM_PWM0_DUTY(duty_cnt);
            reg_val = AIC_PWM->PWM_CTRL & ~(PWM_PWM0_MODE_SEL|PWM_PWM0_RUN);
            AIC_PWM->PWM_CTRL = reg_val | (PWM_PWM0_MODE_SEL|PWM_PWM0_RUN);
            AIC_PWM->PWM0_PRESCALE = PWM_PWM_PRESCALE(prescale_coefficient);
            break;
        case(PWM1_CHANNAL_PA7):
        case(PWM1_CHANNAL_PA13):
            AIC_PWM->PWM1_CNT |= PWM_PWM1_MOD(mod_cnt);
            AIC_PWM->PWM1_CNT |= PWM_PWM1_DUTY(duty_cnt);
            reg_val = AIC_PWM->PWM_CTRL & ~(PWM_PWM1_MODE_SEL|PWM_PWM1_RUN);
            AIC_PWM->PWM_CTRL = reg_val | (PWM_PWM1_MODE_SEL|PWM_PWM1_RUN);
            AIC_PWM->PWM1_PRESCALE = PWM_PWM_PRESCALE(prescale_coefficient);
            break;
        case(PWM2_CHANNAL_PA8):
        case(PWM2_CHANNAL_PA14):
            AIC_PWM->PWM2_CNT |= PWM_PWM2_MOD(mod_cnt);
            AIC_PWM->PWM2_CNT |= PWM_PWM2_DUTY(duty_cnt);
            reg_val = AIC_PWM->PWM_CTRL & ~(PWM_PWM2_MODE_SEL|PWM_PWM2_RUN);
            AIC_PWM->PWM_CTRL = reg_val | (PWM_PWM2_MODE_SEL|PWM_PWM2_RUN);
            AIC_PWM->PWM2_PRESCALE = PWM_PWM_PRESCALE(prescale_coefficient);
            break;
        default:
            break;
    }
}

void pwm_set_duty(int pwm_gpidx, uint32_t freq_hz, uint32_t duty_ratio)
{
    uint32_t reg_val = 0;
    uint32_t mod_cnt = 1;
    uint32_t duty_cnt = 1;

    if (freq_hz >= (32000 / 0xFF)) { // 125 ~ 16K
        mod_cnt = (32000 / freq_hz - 1);
        duty_cnt = ((mod_cnt + 1) * duty_ratio / 100);
    } else if (freq_hz >= (10)) { // 10  ~ 124
        mod_cnt = (400 / freq_hz - 1);
        duty_cnt = ((mod_cnt + 1) * duty_ratio / 100);
    } else {
        mod_cnt = (251 / freq_hz - 1);
        duty_cnt = ((mod_cnt + 1) * duty_ratio / 100);
    }

    switch(pwm_gpidx) {
        case(PWM0_CHANNAL_PA6):
        case(PWM0_CHANNAL_PA12):
            reg_val = AIC_PWM->PWM0_CNT & ~(PWM_PWM0_DUTY(0xff));
            AIC_PWM->PWM0_CNT = reg_val | PWM_PWM0_DUTY(duty_cnt);
            break;
        case(PWM1_CHANNAL_PA7):
        case(PWM1_CHANNAL_PA13):
            reg_val = AIC_PWM->PWM1_CNT & ~(PWM_PWM1_DUTY(0xff));
            AIC_PWM->PWM1_CNT = reg_val | PWM_PWM1_DUTY(duty_cnt);
            break;
        case(PWM2_CHANNAL_PA8):
        case(PWM2_CHANNAL_PA14):
            reg_val = AIC_PWM->PWM2_CNT & ~(PWM_PWM2_DUTY(0xff));
            AIC_PWM->PWM2_CNT = reg_val | PWM_PWM2_DUTY(duty_cnt);
            break;
        default:
            break;
    }
}

void pwm_channal_deinit(int pwm_gpidx)
{
    switch(pwm_gpidx) {
        case(PWM0_CHANNAL_PA6):
            iomux_gpio_config_sel_setf(6, 0);
            AIC_PWM->PWM_CTRL &= (~PWM_PWM0_RUN);
            break;
        case(PWM1_CHANNAL_PA7):
            iomux_gpio_config_sel_setf(7, 0);
            AIC_PWM->PWM_CTRL &= (~PWM_PWM1_RUN);
            break;
        case(PWM2_CHANNAL_PA8):
            iomux_gpio_config_sel_setf(8, 0);
            AIC_PWM->PWM_CTRL &= (~PWM_PWM2_RUN);
            break;
        case(PWM0_CHANNAL_PA12):
            iomux_gpio_config_sel_setf(12, 0);
            AIC_PWM->PWM_CTRL &= (~PWM_PWM0_RUN);
            break;
        case(PWM1_CHANNAL_PA13):
            iomux_gpio_config_sel_setf(13, 0);
            AIC_PWM->PWM_CTRL &= (~PWM_PWM1_RUN);
            break;
        case(PWM2_CHANNAL_PA14):
            iomux_gpio_config_sel_setf(14, 0);
            AIC_PWM->PWM_CTRL &= (~PWM_PWM2_RUN);
            break;
        default:
            break;
    }
}

void aonpwm_channal_init(int pwm_gpidx)
{
#if PLF_PMIC_VER_LITE
    switch(pwm_gpidx) {
        case(AONPWM0_CHANNAL_PB3):
            iomux_gpiob_config_sel_setf(3, AIC1000LITE_IOMUX_PAD_GPIO_3_SEL_FUN_PWM_0_SEL);
            break;
        case(AONPWM1_CHANNAL_PB4):
            iomux_gpiob_config_sel_setf(4, AIC1000LITE_IOMUX_PAD_GPIO_4_SEL_FUN_PWM_1_SEL);
            break;
        case(AONPWM2_CHANNAL_PB5):
            iomux_gpiob_config_sel_setf(5, AIC1000LITE_IOMUX_PAD_GPIO_5_SEL_FUN_PWM_2_SEL);
            break;
        case(AONPWM3_CHANNAL_PB13):
            iomux_gpiob_config_sel_setf(13, AIC1000LITE_IOMUX_PAD_GPIO_13_SEL_FUN_PWM_3_SEL);
            break;
        case(AONPWM4_CHANNAL_PB14):
            iomux_gpiob_config_sel_setf(14, AIC1000LITE_IOMUX_PAD_GPIO_14_SEL_FUN_PWM_4_SEL);
            break;
        case(AONPWM5_CHANNAL_PB15):
            iomux_gpiob_config_sel_setf(15, AIC1000LITE_IOMUX_PAD_GPIO_15_SEL_FUN_PWM_5_SEL);
            break;
        default:
            break;
    }

    // hclk divider, 26M
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteSysctrl->hclk_div),
        (AIC1000LITE_SYS_CTRL_CFG_HCLK_DIV_DENOM(0x1) | AIC1000LITE_SYS_CTRL_CFG_HCLK_DIV_UPDATE));
    // hclk sel
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteSysctrl->clk_sel),
        (AIC1000LITE_SYS_CTRL_CFG_CLK_PWM_SEL), (AIC1000LITE_SYS_CTRL_CFG_CLK_PWM_SEL));
#endif
}

void aonpwm_enable(int pwm_gpidx, uint32_t freq_hz, uint32_t duty_ratio)
{
#if PLF_PMIC_VER_LITE
    uint32_t tmr_ld_value_addr = 0;
    uint32_t tmr_ld_value = 0;
    uint32_t tmr_cfg_addr = 0;
    uint32_t tmr_cfg = 0;
    uint32_t pwm_start_val_addr = 0;
    uint32_t pwm_start_val = 0;
    uint32_t pwm_end_val_addr = 0;
    uint32_t pwm_end_val = 0;
    uint32_t pwm_cfg_addr = 0;
    uint32_t pwm_cfg = 0;
    uint32_t mod_cnt = 1;
    uint32_t duty_cnt = 1;

    mod_cnt = (26000000 / freq_hz);
    duty_cnt = ((mod_cnt) * duty_ratio / 100);

    switch (pwm_gpidx) {
        case AONPWM0_CHANNAL_PB3:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr0_ld_value);
            tmr_ld_value = mod_cnt - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr0_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_start_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm0_sta_val);
            pwm_start_val = mod_cnt - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm0_end_val);
            pwm_end_val = (mod_cnt - 1 - duty_cnt);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm0_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
                        AIC1000LITE_LED_PWM_PWM_TMR_SEL(0) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case AONPWM1_CHANNAL_PB4:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr1_ld_value);
            tmr_ld_value = mod_cnt - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr1_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_start_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm1_sta_val);
            pwm_start_val = mod_cnt - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm1_end_val);
            pwm_end_val = (mod_cnt - 1 - duty_cnt);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm1_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
                        AIC1000LITE_LED_PWM_PWM_TMR_SEL(1) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case AONPWM2_CHANNAL_PB5:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr2_ld_value);
            tmr_ld_value = mod_cnt - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr2_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_start_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm2_sta_val);
            pwm_start_val = mod_cnt - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm2_end_val);
            pwm_end_val = (mod_cnt - 1 - duty_cnt);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm2_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
                        AIC1000LITE_LED_PWM_PWM_TMR_SEL(2) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case AONPWM3_CHANNAL_PB13:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr0_ld_value);
            tmr_ld_value = mod_cnt - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr0_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_start_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm3_sta_val);
            pwm_start_val = mod_cnt - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm3_end_val);
            pwm_end_val = (mod_cnt - 1 - duty_cnt);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm3_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
                        AIC1000LITE_LED_PWM_PWM_TMR_SEL(0) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case AONPWM4_CHANNAL_PB14:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr1_ld_value);
            tmr_ld_value = mod_cnt - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr1_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_start_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm4_sta_val);
            pwm_start_val = mod_cnt - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm4_end_val);
            pwm_end_val = (mod_cnt - 1 - duty_cnt);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm4_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
                        AIC1000LITE_LED_PWM_PWM_TMR_SEL(1) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case AONPWM5_CHANNAL_PB15:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr2_ld_value);
            tmr_ld_value = mod_cnt - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr2_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_start_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm5_sta_val);
            pwm_start_val = mod_cnt - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm5_end_val);
            pwm_end_val = (mod_cnt - 1 - duty_cnt);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm5_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
                        AIC1000LITE_LED_PWM_PWM_TMR_SEL(2) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        default:
            break;
    }
    // cfg timer, counter=ld_value->0,ld_value->0,ld_value->0,...
    PMIC_MEM_WRITE(tmr_ld_value_addr, tmr_ld_value);
    PMIC_MEM_WRITE(tmr_cfg_addr,tmr_cfg);

    // cfg pwm, [start, end) is high
    PMIC_MEM_WRITE(pwm_start_val_addr, pwm_start_val);
    PMIC_MEM_WRITE(pwm_end_val_addr, pwm_end_val);
    PMIC_MEM_WRITE(pwm_cfg_addr,pwm_cfg); // sel tmr x, default val: high
#endif
}

void aonpwm_channal_deinit(int pwm_gpidx)
{
#if PLF_PMIC_VER_LITE
    switch(pwm_gpidx) {
        case(AONPWM0_CHANNAL_PB3):
            iomux_gpiob_config_sel_setf(3, AIC1000LITE_IOMUX_PAD_GPIO_3_SEL_FUN_GPIO_3_SEL);
            PMIC_MEM_WRITE((unsigned int)(&aic1000liteLedPwm->pwm0_cfg), 0);
            break;
        case(AONPWM1_CHANNAL_PB4):
            iomux_gpiob_config_sel_setf(4, AIC1000LITE_IOMUX_PAD_GPIO_4_SEL_FUN_GPIO_4_SEL);
            PMIC_MEM_WRITE((unsigned int)(&aic1000liteLedPwm->pwm1_cfg), 0);
            break;
        case(AONPWM2_CHANNAL_PB5):
            iomux_gpiob_config_sel_setf(5, AIC1000LITE_IOMUX_PAD_GPIO_5_SEL_FUN_GPIO_5_SEL);
            PMIC_MEM_WRITE((unsigned int)(&aic1000liteLedPwm->pwm2_cfg), 0);
            break;
        case(AONPWM3_CHANNAL_PB13):
            iomux_gpiob_config_sel_setf(13, AIC1000LITE_IOMUX_PAD_GPIO_13_SEL_FUN_GPIO_13_SEL);
            PMIC_MEM_WRITE((unsigned int)(&aic1000liteLedPwm->pwm3_cfg), 0);
            break;
        case(AONPWM4_CHANNAL_PB14):
            iomux_gpiob_config_sel_setf(14, AIC1000LITE_IOMUX_PAD_GPIO_14_SEL_FUN_GPIO_14_SEL);
            PMIC_MEM_WRITE((unsigned int)(&aic1000liteLedPwm->pwm4_cfg), 0);
            break;
        case(AONPWM5_CHANNAL_PB15):
            iomux_gpiob_config_sel_setf(15, AIC1000LITE_IOMUX_PAD_GPIO_15_SEL_FUN_GPIO_15_SEL);
            PMIC_MEM_WRITE((unsigned int)(&aic1000liteLedPwm->pwm5_cfg), 0);
            break;
        default:
            break;
    }
#endif
}


