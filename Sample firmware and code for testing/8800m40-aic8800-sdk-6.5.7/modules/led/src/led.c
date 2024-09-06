#include "rtos.h"
#include "pmic_api.h"
#include "reg_sysctrl.h"
#include "reg_iomux.h"
#include "led.h"
#include "reg_pwm.h"

#define LED_DEBUG_PRINTF(fmt, ...)       dbg(fmt, ##__VA_ARGS__)

#define LED_GPIOA_ID_BASE                0xa0
#define LED_GPIOB_ID_BASE                0x00

static LED_MODE led_current_mode = LED_NULL;
uint8_t led_colour_bond_list[LED_MAX_COLOUR];

#if PLF_PMIC_VER_LITE
static uint32_t led_get_gpiob_sel_pwm_num(uint32_t gpiob_index)
{
    uint32_t sel_pwm_num = 0;
    switch(gpiob_index)
    {
        case 3:
            sel_pwm_num = 0;
            break;
        case 4:
            sel_pwm_num = 1;
            break;
        case 5:
            sel_pwm_num = 2;
            break;
        case 13:
            sel_pwm_num = 3;
            break;
        case 14:
            sel_pwm_num = 4;
            break;
        case 15:
            sel_pwm_num = 5;
            break;
        default:
            ASSERT_ERR(0);
            break;
    }
    return sel_pwm_num;
}
static uint32_t led_get_gpiob_sel_fun(uint32_t gpiob_index)
{
    uint32_t sel_fun = 0;
    switch(gpiob_index)
    {
        case 3:
            sel_fun = AIC1000LITE_IOMUX_PAD_GPIO_3_SEL_FUN_PWM_0_SEL;
            break;
        case 4:
            sel_fun = AIC1000LITE_IOMUX_PAD_GPIO_4_SEL_FUN_PWM_1_SEL;
            break;
        case 5:
            sel_fun = AIC1000LITE_IOMUX_PAD_GPIO_5_SEL_FUN_PWM_2_SEL;
            break;
        case 13:
            sel_fun = AIC1000LITE_IOMUX_PAD_GPIO_13_SEL_FUN_PWM_3_SEL;
            break;
        case 14:
            sel_fun = AIC1000LITE_IOMUX_PAD_GPIO_14_SEL_FUN_PWM_4_SEL;
            break;
        case 15:
            sel_fun = AIC1000LITE_IOMUX_PAD_GPIO_15_SEL_FUN_PWM_5_SEL;
            break;
        default:
            ASSERT_ERR(0);
            break;
    }
    return sel_fun;
}
#endif
#if PLF_PMIC_VER_AUD
static uint32_t led_get_gpiob_sel_fun(uint32_t gpiob_index)
{
    uint32_t sel_fun = 0;
    switch(gpiob_index)
    {
        case 0:
            sel_fun = AIC1000AUD_IOMUX_PAD_GPIO_0_SEL_FUN_PWM_0_SEL;
            break;
        case 1:
            sel_fun = AIC1000AUD_IOMUX_PAD_GPIO_1_SEL_FUN_PWM_1_SEL;
            break;
        case 2:
            sel_fun = AIC1000AUD_IOMUX_PAD_GPIO_2_SEL_FUN_PWM_0_SEL;
            break;
        case 3:
            sel_fun = AIC1000AUD_IOMUX_PAD_GPIO_3_SEL_FUN_PWM_1_SEL;
            break;
        case 6:
            sel_fun = AIC1000AUD_IOMUX_PAD_GPIO_6_SEL_FUN_PWM_0_SEL;
            break;
        case 7:
            sel_fun = AIC1000AUD_IOMUX_PAD_GPIO_7_SEL_FUN_PWM_1_SEL;
            break;
        case 8:
            sel_fun = AIC1000AUD_IOMUX_PAD_GPIO_8_SEL_FUN_PWM_0_SEL;
            break;
        case 9:
            sel_fun = AIC1000AUD_IOMUX_PAD_GPIO_9_SEL_FUN_PWM_1_SEL;
            break;
        default:
            ASSERT_ERR(0);
            break;
    }
    return sel_fun;
}
#endif

static void led_set_gpioa_pwm(uint8_t duty,uint8_t mod,uint32_t gpioa_index,uint8_t is_low)
{
    gpioa_index = (gpioa_index &(~LED_GPIOA_ID_BASE));
    LED_DEBUG_PRINTF("gpioa_index %x,is_low %x\n",gpioa_index,is_low);

    if(mod == 0 && duty == 0){
        LED_DEBUG_PRINTF("\n a led close\n");
        switch(gpioa_index){
            case 12:
                AIC_PWM->PWM_CTRL |= (~PWM_PWM0_RUN);
                break;
            case 13:
                AIC_PWM->PWM_CTRL |= (~PWM_PWM1_RUN);
                break;
            case 14:
                AIC_PWM->PWM_CTRL |= (~PWM_PWM2_RUN);
                break;
            default:
                ASSERT_ERR(0);
                break;
        }
        return;
    }

    if(is_low){
        //gpioa can not low it.
    }
    switch(gpioa_index){
        case 12:
            AIC_PWM->PWM0_PRESCALE = PWM_PWM_PRESCALE(0xFF);
            AIC_PWM->PWM0_CNT |= PWM_PWM0_MOD(mod);//0x3F
            AIC_PWM->PWM0_CNT |= PWM_PWM0_DUTY(duty);//0x7F
            AIC_PWM->PWM_CTRL |= PWM_PWM0_MODE_SEL;
            AIC_PWM->PWM_CTRL |= PWM_PWM0_RUN;
            break;
        case 13:
            AIC_PWM->PWM1_PRESCALE = PWM_PWM_PRESCALE(0xFF);
            AIC_PWM->PWM1_CNT |= PWM_PWM1_MOD(mod);//0x3F
            AIC_PWM->PWM1_CNT |= PWM_PWM1_DUTY(duty);//0x7F
            AIC_PWM->PWM_CTRL |= PWM_PWM1_MODE_SEL;
            AIC_PWM->PWM_CTRL |= PWM_PWM1_RUN;
            break;
        case 14:
            AIC_PWM->PWM2_PRESCALE = PWM_PWM_PRESCALE(0xFF);
            AIC_PWM->PWM2_CNT |= PWM_PWM2_MOD(mod);//0x3F
            AIC_PWM->PWM2_CNT |= PWM_PWM2_DUTY(duty);//0x7F
            AIC_PWM->PWM_CTRL |= PWM_PWM2_MODE_SEL;
            AIC_PWM->PWM_CTRL |= PWM_PWM2_RUN;
            break;
        default:
            ASSERT_ERR(0);
            break;
    }

}

static void led_set_pwm(uint32_t tmr_cnt_total, uint32_t tmr_cnt_high, uint32_t gpiob_index, uint8_t is_low)
{
    uint32_t cfg_id = gpiob_index%2;
    uint32_t tmr_ld_value_addr;
    uint32_t tmr_ld_value;
    uint32_t tmr_cfg_addr;
    uint32_t tmr_cfg;
    uint32_t pwm_sta_val_addr;
    uint32_t pwm_sta_val;
    uint32_t pwm_end_val_addr;
    uint32_t pwm_end_val;
    uint32_t pwm_cfg_addr;
    uint32_t pwm_cfg;

#if PLF_PMIC_VER_LITE
    cfg_id = led_get_gpiob_sel_pwm_num(gpiob_index);
#endif
#if PLF_PMIC_VER_AUD
    cfg_id = gpiob_index%2;
#endif

    LED_DEBUG_PRINTF("gpiob_index %x,is_low %x,cfg_id %x\n",gpiob_index,is_low,cfg_id);
    if(tmr_cnt_total == 0 && tmr_cnt_high == 0){
        LED_DEBUG_PRINTF("\nled close\n");
#if PLF_PMIC_VER_AUD
        if(cfg_id == 0){
            pwm_cfg_addr = (unsigned int)(&aic1000audLedPwm->pwm0_cfg);
            pwm_cfg = AIC1000AUD_LED_PWM_PWM_UPDATE;
        }else if(cfg_id == 1){
            pwm_cfg_addr = (unsigned int)(&aic1000audLedPwm->pwm1_cfg);
            pwm_cfg = AIC1000AUD_LED_PWM_PWM_UPDATE;
        }else{
            ASSERT_ERR(0);
        }
        PMIC_MEM_WRITE(pwm_cfg_addr,pwm_cfg);
#endif
#if PLF_PMIC_VER_LITE
        switch(cfg_id){
            case 0:
                pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm0_cfg);
                pwm_cfg = AIC1000LITE_LED_PWM_PWM_UPDATE;
                break;
            case 1:
                pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm1_cfg);
                pwm_cfg = AIC1000LITE_LED_PWM_PWM_UPDATE;
                break;
            case 2:
                pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm2_cfg);
                pwm_cfg = AIC1000LITE_LED_PWM_PWM_UPDATE;
                break;
            case 3:
                pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm3_cfg);
                pwm_cfg = AIC1000LITE_LED_PWM_PWM_UPDATE;
                break;
            case 4:
                pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm4_cfg);
                pwm_cfg = AIC1000LITE_LED_PWM_PWM_UPDATE;
                break;
            case 5:
                pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm5_cfg);
                pwm_cfg = AIC1000LITE_LED_PWM_PWM_UPDATE;
                break;
            default:
                ASSERT_ERR(0);
                break;
        }
        PMIC_MEM_WRITE(pwm_cfg_addr,pwm_cfg);
#endif
        return;
    }

#if PLF_PMIC_VER_LITE
    // hclk divider, 26M
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteSysctrl->hclk_div),
        (AIC1000LITE_SYS_CTRL_CFG_HCLK_DIV_DENOM(0x1) | AIC1000LITE_SYS_CTRL_CFG_HCLK_DIV_UPDATE));
    // hclk sel
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteSysctrl->clk_sel),
        (AIC1000LITE_SYS_CTRL_CFG_CLK_PWM_SEL), (AIC1000LITE_SYS_CTRL_CFG_CLK_PWM_SEL));

    // gpiob iomux
    iomux_gpiob_config_sel_setf(gpiob_index, led_get_gpiob_sel_fun(gpiob_index));

    switch(cfg_id){
        case 0:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr0_ld_value);
            tmr_ld_value = tmr_cnt_total - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr0_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_sta_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm0_sta_val);
            pwm_sta_val = tmr_cnt_total - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm0_end_val);
            pwm_end_val = (tmr_cnt_total - 1 - tmr_cnt_high);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm0_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
            AIC1000LITE_LED_PWM_PWM_TMR_SEL(0) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case 1:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr1_ld_value);
            tmr_ld_value = tmr_cnt_total - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr1_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_sta_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm1_sta_val);
            pwm_sta_val = tmr_cnt_total - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm1_end_val);
            pwm_end_val = (tmr_cnt_total - 1 - tmr_cnt_high);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm1_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
            AIC1000LITE_LED_PWM_PWM_TMR_SEL(1) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case 2:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr2_ld_value);
            tmr_ld_value = tmr_cnt_total - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr2_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_sta_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm2_sta_val);
            pwm_sta_val = tmr_cnt_total - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm2_end_val);
            pwm_end_val = (tmr_cnt_total - 1 - tmr_cnt_high);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm2_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
            AIC1000LITE_LED_PWM_PWM_TMR_SEL(2) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case 3:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr0_ld_value);
            tmr_ld_value = tmr_cnt_total - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr0_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_sta_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm3_sta_val);
            pwm_sta_val = tmr_cnt_total - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm3_end_val);
            pwm_end_val = (tmr_cnt_total - 1 - tmr_cnt_high);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm3_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
            AIC1000LITE_LED_PWM_PWM_TMR_SEL(0) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case 4:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr1_ld_value);
            tmr_ld_value = tmr_cnt_total - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr1_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_sta_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm4_sta_val);
            pwm_sta_val = tmr_cnt_total - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm4_end_val);
            pwm_end_val = (tmr_cnt_total - 1 - tmr_cnt_high);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm4_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
            AIC1000LITE_LED_PWM_PWM_TMR_SEL(1) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        case 5:
            tmr_ld_value_addr = (unsigned int)(&aic1000liteLedPwm->tmr2_ld_value);
            tmr_ld_value = tmr_cnt_total - 1;
            tmr_cfg_addr = (unsigned int)(&aic1000liteLedPwm->tmr2_cfg);
            tmr_cfg = (AIC1000LITE_LED_PWM_TMR_MODE | AIC1000LITE_LED_PWM_TMR_RUN);
            pwm_sta_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm5_sta_val);
            pwm_sta_val = tmr_cnt_total - 1;
            pwm_end_val_addr = (unsigned int)(&aic1000liteLedPwm->pwm5_end_val);
            pwm_end_val = (tmr_cnt_total - 1 - tmr_cnt_high);
            pwm_cfg_addr = (unsigned int)(&aic1000liteLedPwm->pwm5_cfg);
            pwm_cfg = (AIC1000LITE_LED_PWM_PWM_RUN | /*AIC1000LITE_LED_PWM_PWM_DEFAULT_VAL |*/
            AIC1000LITE_LED_PWM_PWM_TMR_SEL(2) | AIC1000LITE_LED_PWM_PWM_UPDATE);
            break;
        default:
            ASSERT_ERR(0);
            break;
    }
    // cfg timer, counter=ld_value->0,ld_value->0,ld_value->0,...
    PMIC_MEM_WRITE(tmr_ld_value_addr, tmr_ld_value);
    PMIC_MEM_WRITE(tmr_cfg_addr,tmr_cfg);

    // cfg pwm, [start, end) is high
    PMIC_MEM_WRITE(pwm_sta_val_addr, pwm_sta_val);
    PMIC_MEM_WRITE(pwm_end_val_addr, pwm_end_val);
    PMIC_MEM_WRITE(pwm_cfg_addr,pwm_cfg); // sel tmr x, default val: high
#endif
#if PLF_PMIC_VER_AUD
    // hclk divider, 26M
    PMIC_MEM_WRITE((unsigned int)(&aic1000audSysctrl->pclk_div),
        (AIC1000AUD_SYS_CTRL_CFG_PCLK_DIV_DENOM(0x01) | AIC1000AUD_SYS_CTRL_CFG_PCLK_DIV_UPDATE));
    // hclk sel
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000audSysctrl->clk_sel),
        (AIC1000AUD_SYS_CTRL_CFG_CLK_PWM_SEL), (AIC1000AUD_SYS_CTRL_CFG_CLK_PWM_SEL));

    // gpiob iomux
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000audIomux->GPCFG[gpiob_index]),
        led_get_gpiob_sel_fun(gpiob_index), AIC1000AUD_IOMUX_PAD_GPIO_SEL(0xF));

    if(cfg_id == 0){
        tmr_ld_value_addr = (unsigned int)(&aic1000audLedPwm->tmr0_ld_value);
        tmr_ld_value = tmr_cnt_total - 1;
        tmr_cfg_addr = (unsigned int)(&aic1000audLedPwm->tmr0_cfg);
        tmr_cfg = (AIC1000AUD_LED_PWM_TMR_MODE | AIC1000AUD_LED_PWM_TMR_RUN);
        pwm_sta_val_addr = (unsigned int)(&aic1000audLedPwm->pwm0_sta_val);
        pwm_sta_val = tmr_cnt_total - 1;
        pwm_end_val_addr = (unsigned int)(&aic1000audLedPwm->pwm0_end_val);
        pwm_end_val = (tmr_cnt_total - 1 - tmr_cnt_high);
        pwm_cfg_addr = (unsigned int)(&aic1000audLedPwm->pwm0_cfg);
        pwm_cfg = (AIC1000AUD_LED_PWM_PWM_RUN | /*AIC1000AUD_LED_PWM_PWM_DEFAULT_VAL |*/
        AIC1000AUD_LED_PWM_PWM_TMR_SEL(0) | AIC1000AUD_LED_PWM_PWM_UPDATE); // must sel tmr0, default val: high
    }else if(cfg_id == 1){
        tmr_ld_value_addr = (unsigned int)(&aic1000audLedPwm->tmr1_ld_value);
        tmr_ld_value = tmr_cnt_total - 1;
        tmr_cfg_addr = (unsigned int)(&aic1000audLedPwm->tmr1_cfg);
        tmr_cfg = (AIC1000AUD_LED_PWM_TMR_MODE | AIC1000AUD_LED_PWM_TMR_RUN);
        pwm_sta_val_addr = (unsigned int)(&aic1000audLedPwm->pwm1_sta_val);
        pwm_sta_val = tmr_cnt_total - 1;
        pwm_end_val_addr = (unsigned int)(&aic1000audLedPwm->pwm1_end_val);
        pwm_end_val = (tmr_cnt_total - 1 - tmr_cnt_high);
        pwm_cfg_addr = (unsigned int)(&aic1000audLedPwm->pwm1_cfg);
        pwm_cfg = (AIC1000AUD_LED_PWM_PWM_RUN | /*AIC1000AUD_LED_PWM_PWM_DEFAULT_VAL |*/
        AIC1000AUD_LED_PWM_PWM_TMR_SEL(1) | AIC1000AUD_LED_PWM_PWM_UPDATE); // must sel tmr0, default val: high
    }else{
        ASSERT_ERR(0);
    }
    if(is_low){
        pwm_sta_val = (tmr_cnt_total - 1 - tmr_cnt_high);
        pwm_end_val = 0;
    }
    LED_DEBUG_PRINTF("LED: pwm_cfg 0x%x\n",pwm_cfg);
    // cfg timer, counter=ld_value->0,ld_value->0,ld_value->0,...
    PMIC_MEM_WRITE(tmr_ld_value_addr, tmr_ld_value);
    PMIC_MEM_WRITE(tmr_cfg_addr,tmr_cfg);

    // cfg pwm, [start, end) is high
    PMIC_MEM_WRITE(pwm_sta_val_addr, pwm_sta_val);
    PMIC_MEM_WRITE(pwm_end_val_addr, pwm_end_val);
    PMIC_MEM_WRITE(pwm_cfg_addr,pwm_cfg); // must sel tmr0, default val: high
#endif
}

static void led_clear_mode(void)
{
    LED_DEBUG_PRINTF("LED: %s %d\n",__func__,led_current_mode);
    switch(led_current_mode){
        case LED_NULL:
            break;
        case LED_POWEROFF:
            break;
        case LED_POWERON:
            break;
        case LED_LOW_POWER:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_RED],0);
            }else{
                led_set_pwm(0,0,led_colour_bond_list[LED_RED],0);
            }
            break;
        case LED_WIFI_IDLE:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_BULE],0);
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_RED] ,1);
            }else{
                led_set_pwm(0,0,led_colour_bond_list[LED_BULE],0);
                led_set_pwm(0,0,led_colour_bond_list[LED_RED] ,1);
            }
            break;
        case LED_WIFI_PARING:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }else{
                led_set_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }
            break;
        case LED_WIFI_CONNECT:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }else{
                led_set_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }
            break;
        case LED_WIFI_STA_CONNECTED:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }else{
                led_set_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }
            break;
        case LED_BT_IDLE:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_BULE],0);
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_RED] ,1);
            }else{
                led_set_pwm(0,0,led_colour_bond_list[LED_BULE],0);
                led_set_pwm(0,0,led_colour_bond_list[LED_RED] ,1);
            }
            break;
        case LED_BT_SCAN:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }else{
                led_set_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }
            break;
        case LED_BT_CONNECT:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                led_set_gpioa_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }else{
                led_set_pwm(0,0,led_colour_bond_list[LED_BULE],0);
            }
            break;
        default:
            ASSERT_ERR(0);
            break;
    }
}

static void led_set_mode(LED_MODE mode)
{
    uint32_t tmr_cnt_total,tmr_cnt_high;

    LED_DEBUG_PRINTF("LED: led_current_mode = %d,mode = %d\n",led_current_mode,mode);
    if(led_current_mode != mode){
        if(led_current_mode != LED_NULL){
            led_clear_mode();
        }
        led_current_mode = mode;
    }

    switch(mode){
        case LED_NULL:
            break;
        case LED_POWEROFF:
            break;
        case LED_POWERON:
            break;
        case LED_LOW_POWER:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                tmr_cnt_total = GPIOA_DIPLOID_NUM/4;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_RED],0);
            }else{
                tmr_cnt_total = DIPLOID_NUM/4;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_RED],0);
            }
            break;
        case LED_WIFI_IDLE:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                tmr_cnt_total = GPIOA_DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_BULE],0);
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_RED] ,1);
            }else{
                tmr_cnt_total = DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_BULE],0);
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_RED] ,1);
            }
            break;
        case LED_WIFI_PARING:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                tmr_cnt_total = GPIOA_DIPLOID_NUM/4;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_BULE],0);
            }else{
                tmr_cnt_total = DIPLOID_NUM/4;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_BULE],0);
            }
            break;
        case LED_WIFI_CONNECT:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                tmr_cnt_total = GPIOA_DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_BULE],0);
            }else{
                tmr_cnt_total = DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_BULE],0);
            }
            break;
        case LED_WIFI_STA_CONNECTED:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                tmr_cnt_total = GPIOA_DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total;
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_BULE],0);
            }else{
                tmr_cnt_total = DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total-1;
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_BULE],0);
            }
            break;
        case LED_BT_IDLE:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                tmr_cnt_total = GPIOA_DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_BULE],0);
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_RED] ,1);
            }else{
                tmr_cnt_total = DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_BULE],0);
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_RED] ,1);
            }
            break;
        case LED_BT_SCAN:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                tmr_cnt_total = GPIOA_DIPLOID_NUM/4;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_BULE],0);
            }else{
                tmr_cnt_total = DIPLOID_NUM/4;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_BULE],0);
            }
            break;
        case LED_BT_CONNECT:
            if(led_colour_bond_list[LED_RED]&LED_GPIOA_ID_BASE){
                tmr_cnt_total = GPIOA_DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_gpioa_pwm(tmr_cnt_high,tmr_cnt_total,led_colour_bond_list[LED_BULE],0);
            }else{
                tmr_cnt_total = DIPLOID_NUM/2;
                tmr_cnt_high = tmr_cnt_total/2;
                led_set_pwm(tmr_cnt_total,tmr_cnt_high,led_colour_bond_list[LED_BULE],0);
            }
            break;
        default:
            ASSERT_ERR(0);
            break;
    }
}

static bool led_handle_process(CO_EVENT *evt)
{
    led_set_mode(evt->EvtId);
    return 0;
}

void led_set_pattern(LED_MODE mode)
{
    int res = 0;
    CO_MODUAL_EVENT msg;
    msg.mod_id = CO_MODUAL_LED;
    msg.mod_evt.EvtId = mode;
    res = co_event_send(&msg, false);
    ASSERT_ERR(res == 0 || res == 1);
}

static void led_register_gpiob_index(uint32_t gpiob_index,enum LED_COLOUR colour_id)
{
    if(led_colour_bond_list[colour_id] == 0){
        LED_DEBUG_PRINTF("LED: led_reg gpiob = %x,colour_id = %d\n",gpiob_index,colour_id);
        led_colour_bond_list[colour_id] = LED_GPIOB_ID_BASE|gpiob_index;
    }else{
        LED_DEBUG_PRINTF("LED: led_regb error %x\n",colour_id);
    }
}

static void led_register_gpioa_index(uint32_t gpioa_index,enum LED_COLOUR colour_id)
{
    if(led_colour_bond_list[colour_id] == 0){
        LED_DEBUG_PRINTF("LED: led_reg gpioa = %x,colour_id = %d\n",gpioa_index,colour_id);
        led_colour_bond_list[colour_id] = LED_GPIOA_ID_BASE|gpioa_index;
    }else{
        LED_DEBUG_PRINTF("LED: led_rega error %x\n",colour_id);
    }
    iomux_gpio_config_sel_setf(gpioa_index, 4);
    cpusysctrl_pclkme_set(CSC_PCLKME_PWM_EN_BIT);
    cpusysctrl_oclkme_set(CSC_OCLKME_PWM_EN_BIT);
}

void led_register_gpio_pin(PinName pin,enum LED_COLOUR colour_id)
{
    uint8_t pin_type = PIN_TYPE(pin);
    uint8_t pin_idx = PIN_IDX(pin);

    if (pin_type == PIN_TYPE_A) {
        led_register_gpioa_index(pin_idx,colour_id);
    } else if (pin_type == PIN_TYPE_B) {
        led_register_gpiob_index(pin_idx,colour_id);
    }
}

void led_init(void)
{
    co_main_evt_handler_rigister(CO_MODUAL_LED, led_handle_process);
}
