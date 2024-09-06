/**
 ****************************************************************************************
 *
 * @file pwm_api.c
 *
 * @brief-channal
 * ------------------PWM_CHANNAL_TABLE----------------
 * |    PWMx     |   PWM0    |   PWM1    |   PWM2    |
 * |    GPIOA    |    PA4    |    PA5    |   PA14    |
 * |    GPIOB    |    PB0    |    PB1    |    PB2    |
 * ---------------------------------------------------
 * In a PWM-CHANNAL, e.g. PWM0, PA4 and PB0 cann`t be used at the same time. Only one can be use!
 * -----------------AONPWM_CHANNAL_TABLE--------------------
 * |    PWMx     |   AONPWM0   |   AONPWM1   |   AONPWM2   |
 * |    GPIOA    |     PA6     |     PA7     |     PA9     |
 * ---------------------------------------------------------
 *
 * @brief-frequency
 * -----------------------------------PWM_FREQUENCY_EXAMPLE_TABLE---------------------------------
 * |    tmr_cnt     |   0xffffffff   |   4290,000000   |   26,000000   |   260000   |    1300    |
 * |    preiod(s)   |     165.19     |       165       |       1       |    0.01    |   0.00005  |
 * |    freq(Hz)    |     0.00605    |     0.00606     |       1       |     100    |     20K    |
 * -----------------------------------------------------------------------------------------------
 * PWM-TIMER-CLK is fixed at 26M. Only timer-count(tmr_cnt) and duty(dty_cnt) can be adjust.
 *
 ****************************************************************************************
 */

/*
 * INCLUDES
 ****************************************************************************************
 */
#include "pwm_api.h"

void pwm_channal_init(int pwm_gpidx)
{
    switch(pwm_gpidx) {
        case(PWM0_CHANNAL_PA4):
            iomux_gpioa_config_sel_setf(4, 5);
            break;
        case(PWM1_CHANNAL_PA5):
            iomux_gpioa_config_sel_setf(5, 5);
            break;
        case(PWM2_CHANNAL_PA14):
            iomux_gpioa_config_sel_setf(14, 6);
            break;
        case(PWM0_CHANNAL_PB0):
            iomux_gpiob_config_sel_setf(0, 4);
            break;
        case(PWM1_CHANNAL_PB1):
            iomux_gpiob_config_sel_setf(1, 4);
            break;
        case(PWM2_CHANNAL_PB2):
            iomux_gpiob_config_sel_setf(2, 4);
            break;
        default:
            break;
    }
}

void pwm_tim_init(uint32_t tmr_cnt)
{
    AIC_PWM->tmr0_ld_value = PWM_TMR_LD_VALUE(tmr_cnt-1);
    AIC_PWM->tmr0_cfg = PWM_TMR_MODE | PWM_TMR_RUN;
}

void pwm_enable(int pwm_chan, uint32_t tmr_cnt, uint32_t dty_cnt)
{
    switch(pwm_chan) {
        case(PWM_CHANNAL_0):
            AIC_PWM->pwm0_sta_val = PWM_PWM_STA_VAL(tmr_cnt-1);
            AIC_PWM->pwm0_end_val = PWM_PWM_END_VAL(tmr_cnt - dty_cnt);
            AIC_PWM->pwm0_step_cfg0 = PWM_PWM_STEP_CYC(0x0004) | PWM_PWM_STEP_NUM(0x0004);
            AIC_PWM->pwm0_step_cfg1 = PWM_PWM_STEP_VALUE(CNT_STABLE);
            AIC_PWM->pwm0_cfg = PWM_PWM_RUN | PWM_PWM_INC_MODE | PWM_PWM_UPDATE;
            AIC_PWM->pwm0_int_ctrl  = PWM_PWM_INT_EN;
            break;
        case(PWM_CHANNAL_1):
            AIC_PWM->pwm1_sta_val = PWM_PWM_STA_VAL(tmr_cnt-1);
            AIC_PWM->pwm1_end_val = PWM_PWM_END_VAL(tmr_cnt - dty_cnt);
            AIC_PWM->pwm1_step_cfg0 = PWM_PWM_STEP_CYC(0x0004) | PWM_PWM_STEP_NUM(0x0004);
            AIC_PWM->pwm1_step_cfg1 = PWM_PWM_STEP_VALUE(CNT_STABLE);
            AIC_PWM->pwm1_cfg = PWM_PWM_RUN | PWM_PWM_INC_MODE | PWM_PWM_UPDATE;
            AIC_PWM->pwm1_int_ctrl  = PWM_PWM_INT_EN;
            break;
        case(PWM_CHANNAL_2):
            AIC_PWM->pwm2_sta_val = PWM_PWM_STA_VAL(tmr_cnt-1);
            AIC_PWM->pwm2_end_val = PWM_PWM_END_VAL(tmr_cnt - dty_cnt);
            AIC_PWM->pwm2_step_cfg0 = PWM_PWM_STEP_CYC(0x0004) | PWM_PWM_STEP_NUM(0x0004);
            AIC_PWM->pwm2_step_cfg1 = PWM_PWM_STEP_VALUE(CNT_STABLE);
            AIC_PWM->pwm2_cfg = PWM_PWM_RUN | PWM_PWM_INC_MODE | PWM_PWM_UPDATE;
            AIC_PWM->pwm2_int_ctrl  = PWM_PWM_INT_EN;
            break;
        default:
            break;
    }
}

void aonpwm_channal_init(int pwm_gpidx)
{
    switch(pwm_gpidx) {
        case(AONPWM0_CHANNAL_PA6):
            iomux_gpioa_config_sel_setf(6, 4);
            break;
        case(AONPWM1_CHANNAL_PA7):
            iomux_gpioa_config_sel_setf(7, 4);
            break;
        case(AONPWM2_CHANNAL_PA9):
            iomux_gpioa_config_sel_setf(9, 4);
            break;
        default:
            break;
    }
}

void aonpwm_tim_init(uint32_t tmr_cnt)
{
    AIC_AONPWM->tmr0_ld_value = PWM_TMR_LD_VALUE(tmr_cnt-1);
    AIC_AONPWM->tmr0_cfg = PWM_TMR_MODE | PWM_TMR_RUN;
}

void aonpwm_enable(int pwm_chan, uint32_t tmr_cnt, uint32_t dty_cnt)
{
    switch(pwm_chan) {
        case(AONPwM_CHANNAL_0):
            AIC_AONPWM->pwm0_sta_val = PWM_PWM_STA_VAL(tmr_cnt-1);
            AIC_AONPWM->pwm0_end_val = PWM_PWM_END_VAL(tmr_cnt - dty_cnt);
            AIC_AONPWM->pwm0_step_cfg0 = PWM_PWM_STEP_CYC(0x0004) | PWM_PWM_STEP_NUM(0x0004);
            AIC_AONPWM->pwm0_step_cfg1 = PWM_PWM_STEP_VALUE(CNT_STABLE);
            AIC_AONPWM->pwm0_cfg = PWM_PWM_RUN | PWM_PWM_INC_MODE | PWM_PWM_UPDATE;
            AIC_AONPWM->pwm0_int_ctrl  = PWM_PWM_INT_EN;
            break;
        case(AONPwM_CHANNAL_1):
            AIC_AONPWM->pwm1_sta_val = PWM_PWM_STA_VAL(tmr_cnt-1);
            AIC_AONPWM->pwm1_end_val = PWM_PWM_END_VAL(tmr_cnt - dty_cnt);
            AIC_AONPWM->pwm1_step_cfg0 = PWM_PWM_STEP_CYC(0x0004) | PWM_PWM_STEP_NUM(0x0004);
            AIC_AONPWM->pwm1_step_cfg1 = PWM_PWM_STEP_VALUE(CNT_STABLE);
            AIC_AONPWM->pwm1_cfg = PWM_PWM_RUN | PWM_PWM_INC_MODE | PWM_PWM_UPDATE;
            AIC_AONPWM->pwm1_int_ctrl  = PWM_PWM_INT_EN;
            break;
        case(AONPWM_CHANNAL_2):
            AIC_AONPWM->pwm2_sta_val = PWM_PWM_STA_VAL(tmr_cnt-1);
            AIC_AONPWM->pwm2_end_val = PWM_PWM_END_VAL(tmr_cnt - dty_cnt);
            AIC_AONPWM->pwm2_step_cfg0 = PWM_PWM_STEP_CYC(0x0004) | PWM_PWM_STEP_NUM(0x0004);
            AIC_AONPWM->pwm2_step_cfg1 = PWM_PWM_STEP_VALUE(CNT_STABLE);
            AIC_AONPWM->pwm2_cfg = PWM_PWM_RUN | PWM_PWM_INC_MODE | PWM_PWM_UPDATE;
            AIC_AONPWM->pwm2_int_ctrl  = PWM_PWM_INT_EN;
            break;
        default:
            break;
    }
}

