/**
 ****************************************************************************************
 *
 * @file gpadc_api.c
 *
 * @brief GPADC API functions
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "gpio_api.h"
#include "gpadc_api.h"
#include "msadc_api.h"
#include "sysctrl_api.h"
#include "reg_anareg.h"
#include "arch.h"
#if PLF_PMIC
#include "pmic_api.h"
#endif
#include "dbg.h"

void gpadc_init(int gpbidx)
{
    unsigned int reg_val;
    if ((gpbidx == 2) || (gpbidx == 3)) {
        // mux en
        reg_val = AIC_ANAREG1->gpiob_cfg1 & ~(ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_EN | ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_ENB);
        AIC_ANAREG1->gpiob_cfg1 = reg_val | ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_EN;
        // mux gpio
        //gpiob_init(gpbidx);
        //gpiob_dir_in(gpbidx);
        //gpiob_force_pull_none_enable(gpbidx);
        gpiob_force_oen_enable(gpbidx);
    }
}

void gpadc_free(int gpbidx)
{
    if ((gpbidx >= 2) && (gpbidx <= 3)) {
        unsigned int reg_val;
        // mux en
        reg_val = AIC_ANAREG1->gpiob_cfg1 & ~(ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_EN);
        reg_val = AIC_ANAREG1->gpiob_cfg1 | (ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_ENB);
        AIC_ANAREG1->gpiob_cfg1 = reg_val | 0;
        //gpiob_deinit(gpbidx);
        //gpiob_force_oen_disable(gpbidx); // TODO:
    }
}

int gpadc_read(int gpbidx)
{
    int volt_mv = 0;
    if (gpbidx == 2) {
        volt_mv = msadc_volt_measure(MSADC_VOLT_GPB2);
    } else if (gpbidx == 3) {
        volt_mv = msadc_volt_measure(MSADC_VOLT_GPB3);
    }
    return volt_mv;
}

void gpadc_diff_init()
{
    int gpidx_p = GPADC_DIFF_CH_0 * 2;
    int gpidx_n = gpidx_p + 1;
    gpadc_init(gpidx_p);
    gpadc_init(gpidx_n);
}

void gpadc_diff_free()
{
    int gpidx_p = GPADC_DIFF_CH_0 * 2;
    int gpidx_n = gpidx_p + 1;
    gpadc_free(gpidx_p);
    gpadc_free(gpidx_n);
}

// Wait for verity...
int gpadc_diff_read(int negflag)
{
    int volt_val;
    volt_val = (int)msadc_volt_measure(MSADC_VOLT_GPB23DIFF);

    if(negflag == GPADC_DIFF_P2N)
        volt_val = -volt_val;

    return volt_val;
}

