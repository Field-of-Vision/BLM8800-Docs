/**
 ****************************************************************************************
 *
 * @file msadc_api.c
 *
 * @brief MSADC API functions
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "msadc_api.h"
#include "reg_msadc.h"
#include "reg_sysctrl.h"
#include "reg_wlan_rf.h"
#include "arch.h"
#if PLF_PMIC
#include "pmic_api.h"
#endif
#include "dbg.h"
#include "co_math.h"

#define MSADC_DEBUG_PRINTF(fmt, ...)       //do {} while(0) //dbg(fmt, ##__VA_ARGS__)

#define MSADC_CLK_DIV               0x4F
#define MSADC_ACC_MMODE             1
#if (MSADC_ACC_MMODE == 0)
#define MSADC_WINDOW                256
#define MSADC_DENOM_REC             8256
#elif (MSADC_ACC_MMODE == 1)
#define MSADC_WINDOW                512
#define MSADC_DENOM_REC             32896
#elif (MSADC_ACC_MMODE == 2)
#define MSADC_WINDOW                1024
#define MSADC_DENOM_REC             131328
#elif (MSADC_ACC_MMODE == 3)
#define MSADC_WINDOW                4032
#define MSADC_DENOM_REC             2033136
#else
#error "unsupported acc mode"
#endif
#define MSADC_CURR_DIVISOR          522

void msadc_basic_config(void)
{
    uint32_t reg_val;
    AIC_MSADC->cfg_msadc_mode = 0; // sw mode
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", &AIC_MSADC->cfg_msadc_mode, 0);
    AIC_CPUSYSCTRL->clk_msadc_div = CPU_SYS_CTRL_CFG_CLK_MSADC_DIV_DENOM(MSADC_CLK_DIV) |
                                    CPU_SYS_CTRL_CFG_CLK_MSADC_DIV_UPDATE;
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", &AIC_CPUSYSCTRL->clk_msadc_div,
                                    CPU_SYS_CTRL_CFG_CLK_MSADC_DIV_DENOM(MSADC_CLK_DIV) |
                                    CPU_SYS_CTRL_CFG_CLK_MSADC_DIV_UPDATE);
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_WINDOW_MASK;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val |  MSADC_REG_CFG_MSADC_WINDOW(MSADC_WINDOW);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", &AIC_MSADC->cfg_msadc_sw_ctrl1, reg_val |  MSADC_REG_CFG_MSADC_WINDOW(MSADC_WINDOW));
    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_CMP_BIT |
                                                 MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_CHOP_EN |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_GAIN_BIT |
                                                 MSADC_REG_CFG_ANA_MSADC_DEM_EN_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_RSVD_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_DITHER_MODE_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_VCOM_BIT_MASK);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val |  (0 |    // cmp_bit
                                                 MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT(0x2) |
                                                 MSADC_REG_CFG_ANA_MSADC_CHOP_EN |
                                                 0 |    // sdm_gain_bit
                                                 MSADC_REG_CFG_ANA_MSADC_DEM_EN(0x3) |
                                                 MSADC_REG_CFG_ANA_MSADC_RSVD_BIT(0x0) |
                                                 MSADC_REG_CFG_ANA_MSADC_DITHER_MODE(0x1) |
                                                 MSADC_REG_CFG_ANA_MSADC_VCOM_BIT(0x1));
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", &AIC_MSADC->cfg_msadc_ana_ctrl0, reg_val |  (0 |
                                                 MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT(0x2) |
                                                 MSADC_REG_CFG_ANA_MSADC_CHOP_EN |
                                                 0 |
                                                 MSADC_REG_CFG_ANA_MSADC_DEM_EN(0x3) |
                                                 MSADC_REG_CFG_ANA_MSADC_RSVD_BIT(0x0) |
                                                 MSADC_REG_CFG_ANA_MSADC_DITHER_MODE(0x1) |
                                                 MSADC_REG_CFG_ANA_MSADC_VCOM_BIT(0x1)));
}

void msadc_ts_config(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_MODE |
                                                 MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN |
                                                 MSADC_REG_CFG_ANA_MSADC_TS_MODE);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val |  (MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT(0x8C) |
                                                 0 | // sdm_mode
                                                 0 | // adc_ff_en
                                                 MSADC_REG_CFG_ANA_MSADC_TS_MODE); // ts_mode
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", &AIC_MSADC->cfg_msadc_ana_ctrl0, reg_val |  (MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT(0x8C) |
                                                 0 | // sdm_mode
                                                 0 | // adc_ff_en
                                                 MSADC_REG_CFG_ANA_MSADC_TS_MODE));
}

void msadc_ad_config(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_MODE |
                                                 MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN |
                                                 MSADC_REG_CFG_ANA_MSADC_TS_MODE);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val |  (MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT(0x79) |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_MODE | // sdm_mode
                                                 MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN | // adc_ff_en
                                                 0); // ts_mode
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", &AIC_MSADC->cfg_msadc_ana_ctrl0, reg_val |  (MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT(0x79) |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_MODE | // sdm_mode
                                                 MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN | // adc_ff_en
                                                 0));
}

uint32_t msadc_ms(void)
{
    uint32_t reg_val;
    AIC_MSADC->cfg_msadc_sw_ctrl0 = MSADC_REG_CFG_MSADC_SW_START_PULSE;
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", &AIC_MSADC->cfg_msadc_sw_ctrl0, MSADC_REG_CFG_MSADC_SW_START_PULSE);
    do {
        __NOP(); __NOP(); __NOP(); __NOP();
    } while (AIC_MSADC->cfg_msadc_int_raw != MSADC_REG_MASDC_INT_RAW);
    AIC_MSADC->cfg_msadc_int_raw = MSADC_REG_MASDC_INT_RAW;
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", &AIC_MSADC->cfg_msadc_int_raw, MSADC_REG_MASDC_INT_RAW);
    reg_val = AIC_MSADC->cfg_msadc_ro_acc;
    MSADC_DEBUG_PRINTF("rd       : [%p] = %08x\n", &AIC_MSADC->cfg_msadc_ro_acc, reg_val);
    return reg_val;
}

void msadc_vddsense_off(void) {
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL(0) | // avddsense_sel
                     0 | // pu_vrtc0sense
                     0), // pu_vbatsense
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL_MASK |
                     PMU_RTC1_RTC_RG_PU_VRTC0SENSE |
                     PMU_RTC1_RTC_RG_PU_VBATSENSE));
    #endif
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x, mask = %08x\n", (&AIC_PMU_RTC1->pmu_pd_ctrl1),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL(0) | // avddsense_sel
                     0 | // pu_vrtc0sense
                     0),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL_MASK |
                     PMU_RTC1_RTC_RG_PU_VRTC0SENSE |
                     PMU_RTC1_RTC_RG_PU_VBATSENSE));
    //msadc_param.mult = 1;
}

#if 0
float msadc_pa5g_sense(void)
{
    float vout0, vout1;
    wlan_rf_wf_pa_5g_isense_en_setf(1);
    wlan_rf_wf_pa_5g_isense_sel_ic_5u_setf(1);
    // TODO: sleep 100us
    vout0 = msadc_volt_sense(13, 2);
    wlan_rf_wf_pa_5g_isense_en_setf(1);
    wlan_rf_wf_pa_5g_isense_sel_ic_5u_setf(0);
    // TODO: sleep 100us
    vout1 = msadc_volt_sense(13, 2);
    wlan_rf_wf_pa_5g_isense_en_setf(0);
    return vout1/vout0 * MSADC_CURR_DIVISOR;
}

float msadc_pa24g_sense(void)
{
    float vout0, vout1;
    wlan_rf_wf_pa_24g_isense_en_setf(1);
    wlan_rf_wf_pa_24g_isense_sel_ic_5u_setf(1);
    // TODO: sleep 100us
    vout0 = msadc_volt_sense(13, 2);
    wlan_rf_wf_pa_24g_isense_en_setf(1);
    wlan_rf_wf_pa_24g_isense_sel_ic_5u_setf(0);
    // TODO: sleep 100us
    vout1 = msadc_volt_sense(13, 2);
    wlan_rf_wf_pa_24g_isense_en_setf(0);
    return vout1/vout0 * MSADC_CURR_DIVISOR;
}
#endif

/**
 * separate function version
 * for measure Temp, Temp@PA, avdd33, avdd18, avdd13, vbat, vrct1, vcore, i_pa
 */
void msadc_set_diff_mode(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_DIFF_MODE;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_DIFF_MODE;
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (reg_val | MSADC_REG_CFG_MSADC_SW_DIFF_MODE));

    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_TEST_MODE | MSADC_REG_CFG_ANA_MSADC_CHNP_SEL);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val | (0 | 0); // test_mode/chnp_sel
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_ana_ctrl0), (reg_val | (0 | 0)));
}
// single-ended positive port input
void msadc_set_se_p_mode(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_DIFF_MODE;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | 0;
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (reg_val | 0));
    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_TEST_MODE | MSADC_REG_CFG_ANA_MSADC_CHNP_SEL);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val | (0 | MSADC_REG_CFG_ANA_MSADC_CHNP_SEL); // test_mode/chnp_sel
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_ana_ctrl0), (reg_val | (0 | MSADC_REG_CFG_ANA_MSADC_CHNP_SEL)));
}
// single-ended negative port input
void msadc_set_se_n_mode(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_DIFF_MODE;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | 0;
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (reg_val | 0));
    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_TEST_MODE | MSADC_REG_CFG_ANA_MSADC_CHNP_SEL);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val | (0 | 0); // test_mode/chnp_sel
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_ana_ctrl0), (reg_val | (0 | 0)));
}
void msadc_set_selfcal_mode(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_DIFF_MODE;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_DIFF_MODE;
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (reg_val | MSADC_REG_CFG_MSADC_SW_DIFF_MODE));

    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_TEST_MODE | MSADC_REG_CFG_ANA_MSADC_CHNP_SEL);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val | (MSADC_REG_CFG_ANA_MSADC_TEST_MODE | 0);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_ana_ctrl0), (reg_val | MSADC_REG_CFG_ANA_MSADC_TEST_MODE | 0));
}

void msadc_input_sel_avdd33(void)
{
    uint32_t reg_val;
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL(3) | 0 | 0), // avddsense_sel/pu_vrtc0sense/pu_vbatsebse
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL_MASK | PMU_RTC1_RTC_RG_PU_VRTC0SENSE | PMU_RTC1_RTC_RG_PU_VBATSENSE));
    MSADC_DEBUG_PRINTF("rd aft wr: [%p] = %08x\n", (&AIC_PMU_RTC1->pmu_pd_ctrl1),
                        psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1)));
    #endif

    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15)));
    msadc_set_diff_mode();
    //msadc_param.mult = 4.0;
}
void msadc_input_sel_avdd18(void)
{
    uint32_t reg_val;
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL(2) | 0 | 0), // avddsense_sel/pu_vrtc0sense/pu_vbatsebse
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL_MASK | PMU_RTC1_RTC_RG_PU_VRTC0SENSE | PMU_RTC1_RTC_RG_PU_VBATSENSE));
    MSADC_DEBUG_PRINTF("rd aft wr: [%p] = %08x\n", (&AIC_PMU_RTC1->pmu_pd_ctrl1),
                        psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1)));
    #endif

    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15)));

    msadc_set_diff_mode();
    //msadc_param.mult = 2.0;
}

void msadc_input_sel_avdd13(void)
{
    uint32_t reg_val;
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL(1) | 0 | 0), // avddsense_sel/pu_vrtc0sense/pu_vbatsebse
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL_MASK | PMU_RTC1_RTC_RG_PU_VRTC0SENSE | PMU_RTC1_RTC_RG_PU_VBATSENSE));
    MSADC_DEBUG_PRINTF("rd aft wr: [%p] = %08x\n", (&AIC_PMU_RTC1->pmu_pd_ctrl1),
                        psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1)));
    #endif

    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15)));

    msadc_set_diff_mode();
    //msadc_param.mult = 4.0/3.0;
}

void msadc_sel_vbat(void)
{
    uint32_t reg_val;
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL(0) | 0 | PMU_RTC1_RTC_RG_PU_VBATSENSE), // avddsense_sel/pu_vrtc0sense/pu_vbatsebse
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL_MASK | PMU_RTC1_RTC_RG_PU_VRTC0SENSE | PMU_RTC1_RTC_RG_PU_VBATSENSE));
    MSADC_DEBUG_PRINTF("rd aft wr: [%p] = %08x\n", (&AIC_PMU_RTC1->pmu_pd_ctrl1),
                       psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1)));
    #endif

    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15)));

    msadc_set_diff_mode();
    //msadc_param.mult = 5.5;
}

void msadc_input_sel_vtrc0(void)
{
    uint32_t reg_val;
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL(0) | PMU_RTC1_RTC_RG_PU_VRTC0SENSE | 0), // avddsense_sel/pu_vrtc0sense/pu_vbatsebse
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL_MASK | PMU_RTC1_RTC_RG_PU_VRTC0SENSE | PMU_RTC1_RTC_RG_PU_VBATSENSE));
    MSADC_DEBUG_PRINTF("rd aft wr: [%p] = %08x\n", (&AIC_PMU_RTC1->pmu_pd_ctrl1),
                       psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1)));
    #endif

    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(15)));

    msadc_set_diff_mode();
    //msadc_param.mult = 1.0;
}

void msadc_input_sel_vcore(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~(MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK | MSADC_REG_CFG_MSADC_SW_DIFF_MODE);
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | (MSADC_REG_CFG_MSADC_SW_MUX_BITS(11) | 0);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), (MSADC_REG_CFG_MSADC_SW_MUX_BITS(11) | 0));

    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_CHNP_SEL | MSADC_REG_CFG_ANA_MSADC_TEST_MODE);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val | (MSADC_REG_CFG_ANA_MSADC_CHNP_SEL | 0);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_ana_ctrl0), (MSADC_REG_CFG_ANA_MSADC_CHNP_SEL | 0));

    msadc_set_se_p_mode();
    //msadc_param.mult = 1.0;
}

#if 0
void msadc_input_sel_pa_sense(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(13);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), MSADC_REG_CFG_MSADC_SW_MUX_BITS(12));
    msadc_set_diff_mode();
    msadc_param.mult = 1.0;
}
#endif

void msadc_input_sel_gpio23_diff(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(3);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), MSADC_REG_CFG_MSADC_SW_MUX_BITS(2));
    msadc_set_diff_mode();
    //msadc_param.mult = 1.0;
}

void msadc_input_sel_gpio3(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~(MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK|MSADC_REG_CFG_MSADC_SW_DIFF_MODE);
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(2);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), MSADC_REG_CFG_MSADC_SW_MUX_BITS(2));
    msadc_set_se_p_mode();
    //msadc_param.mult = 1.0;
}

void msadc_input_sel_gpio2(void)
{
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~(MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK|MSADC_REG_CFG_MSADC_SW_DIFF_MODE);
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(2);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), MSADC_REG_CFG_MSADC_SW_MUX_BITS(2));
    msadc_set_se_n_mode();
    //msadc_param.mult = 1.0;
}

void msadc_input_sel_ts_pa(void)
{
    wlan_rf_wf_pu_ts_hub_setf(1);
    uint32_t reg_val;
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK;
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val | MSADC_REG_CFG_MSADC_SW_MUX_BITS(1);
    MSADC_DEBUG_PRINTF("wr       : [%p] = %08x\n", (&AIC_MSADC->cfg_msadc_sw_ctrl1), MSADC_REG_CFG_MSADC_SW_MUX_BITS(1));

    msadc_set_diff_mode();
    //msadc_param.mult = 1.0;
}

void msadc_ts_pa5g_on(void)
{
    wlan_rf_wf_pu_ts_hub_setf(1);
    wlan_rf_wf_ts_hub_chn_sel_setf(4);
    wlan_rf_wf_ts_hub_vptat_vbit_setf(2);
}

void msadc_ts_pa24g_on(void)
{
    wlan_rf_wf_pu_ts_hub_setf(1);
    wlan_rf_wf_ts_hub_chn_sel_setf(2);
    wlan_rf_wf_ts_hub_vptat_vbit_setf(2);
}

void msadc_ts_pa_off(void)
{
    wlan_rf_wf_pu_ts_hub_setf(0);
}

#if 0
void msadc_lna_cal_on(void)
{
    bt_rf_bt_rsvd_bit_setf(bt_rf_bt_rsvd_bit_getf() |  0x1);
}

void msadc_lna_cal_off(void)
{
    bt_rf_bt_rsvd_bit_setf(bt_rf_bt_rsvd_bit_getf() & ~0x1);
}

void msadc_pa5g_cal_sel5u(void)
{
    wlan_rf_wf_pa_5g_isense_en_setf(1);
    wlan_rf_wf_pa_5g_isense_sel_ic_5u_setf(1);
}

void msadc_pa5g_cal_sel_core(void)
{
    wlan_rf_wf_pa_5g_isense_en_setf(1);
    wlan_rf_wf_pa_5g_isense_sel_ic_5u_setf(0);
}

void msadc_pa5g_cal_off(void)
{
    wlan_rf_wf_pa_5g_isense_en_setf(0);
}

void msadc_pa24g_cal_sel5u(void)
{
    wlan_rf_wf_pa_24g_isense_en_setf(1);
    wlan_rf_wf_pa_5g_isense_sel_ic_5u_setf(1);
}

void msadc_pa24g_cal_sel_core(void)
{
    wlan_rf_wf_pa_24g_isense_en_setf(1);
    wlan_rf_wf_pa_5g_isense_sel_ic_5u_setf(0);
}

void msadc_pa24g_cal_off(void)
{
    wlan_rf_wf_pa_24g_isense_en_setf(0);
}
#endif

#if (MSADC_SEPARATE_API_EN)
float msadc_ms_volt(float mult)
{
    uint32_t ms_val;
    ms_val = msadc_ms();
    // return uint is mV
    //return (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
    return (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * mult;
}

float msadc_gpio_p_volt(float mult)
{
    uint32_t ms_val;
    ms_val = msadc_ms();
    // return uint is mV
    //dbg("reg_val: %d\n", ms_val);
    //return (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
    return (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * mult;
}

float msadc_gpio_n_volt(float mult)
{
    uint32_t ms_val;
    ms_val = msadc_ms();
    // return uint is mV
    //dbg("reg_val: %d\n", ms_val);
    //return (1 - ms_val / (float)MSADC_DENOM_REC) * 1214 * msadc_param.mult;
    return (1 - ms_val / (float)MSADC_DENOM_REC) * 1214 * mult;
}

// measure examples
float msadc_ms_temp_sense0(void)
{
    uint32_t ms_val;
    msadc_basic_config();
    msadc_ts_config();
    ms_val = msadc_ms();
    return 330.0 * ms_val / (float)MSADC_DENOM_REC - 283;
}

float msadc_ms_temp_sense_pa5g(void)
{
    //uint32_t ms_val;
    float volt;
    msadc_basic_config();
    msadc_ad_config();
    msadc_ts_pa5g_on();
    msadc_input_sel_ts_pa();
    volt = msadc_ms_volt(1.0);
    msadc_ts_pa_off();
    return volt * 547.9 - 275.6;
}

float msadc_ms_temp_sense_pa24g(void)
{
    //uint32_t ms_val;
    float volt;
    msadc_basic_config();
    msadc_ad_config();
    msadc_ts_pa24g_on();
    msadc_input_sel_ts_pa();
    volt = msadc_ms_volt(1.0);
    msadc_ts_pa_off();
    return volt * 547.9 - 275.6;
}

#if 0
float msadc_ms_pa5g_current(void)
{
    float vout0,vout1;
    msadc_init(40, 1);
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_pa_sense();
    msadc_pa5g_cal_sel5u();
    vout0 = msadc_ms_volt();
    msadc_pa5g_cal_sel_core();
    vout1 = msadc_ms_volt();
    msadc_pa5g_cal_off();
    return vout0/vout1 * MSADC_CURR_DIVISOR;
}

float msadc_ms_pa24g_current(void)
{
    float vout0,vout1;
    msadc_init(40, 1);
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_pa_sense();
    msadc_pa24g_cal_sel5u();
    vout0 = msadc_ms_volt();
    msadc_pa24g_cal_sel_core();
    vout1 = msadc_ms_volt();
    msadc_pa24g_cal_off();
    return vout0/vout1 * MSADC_CURR_DIVISOR;
}
#endif

float msadc_ms_vbat(void)
{
    float v_vbat;
    msadc_basic_config();
    msadc_ad_config();
    msadc_sel_vbat();
    v_vbat = msadc_ms_volt(5.5);
    msadc_vddsense_off();
    return v_vbat;
}

float msadc_avdd33(void)
{
    float v_avdd33;
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_avdd33();
    v_avdd33 = msadc_ms_volt(4.0);
    msadc_vddsense_off();
    return v_avdd33;
}

float msadc_avdd18(void)
{
    float v_avdd18;
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_avdd18();
    v_avdd18 = msadc_ms_volt(2.0);
    msadc_vddsense_off();
    return v_avdd18;
}

float msadc_avdd13(void)
{
    float v_avdd13;
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_avdd13();
    v_avdd13 = msadc_ms_volt(4.0/3.0);
    msadc_vddsense_off();
    return v_avdd13;
}

float msadc_ms_vrtc0(void)
{
    float v_vrtc0;
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_vtrc0();
    v_vrtc0 = msadc_ms_volt(1.0);
    msadc_vddsense_off();
    return v_vrtc0;
}

float msadc_ms_vcore(void)
{
    float v_vcore;
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_vcore();
    v_vcore = msadc_ms_volt(1.0);
    return v_vcore;
}

float msadc_gpiob23_diff(void)
{
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_gpio23_diff();
    return msadc_ms_volt(1.0);
}
float msadc_gpiob3(void)
{
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_gpio3();
    return msadc_gpio_p_volt(1.0);
}
float msadc_gpiob2(void)
{
    msadc_basic_config();
    msadc_ad_config();
    msadc_input_sel_gpio2();
    return msadc_gpio_n_volt(1.0);
}
/**    end of separate function version    **/
#endif

/**
 * cal_avdd13 function
 * @ target value is 1400mV
 */
static int msadc_cal_avdd13_algorithm(int volt_init, uint32_t reg_init)
{
    unsigned int reg_val;
    int  v_ref, v_cal, volt_reinit;
    int cal_sign=0, step=0, reg_value_offset=0, reg_value_cal=0;

    // 1. compare target-volt first time
    int diff = volt_init - CAL_AVDD13_TARGET;
    int diff_abs = co_abs(diff);
    // 2. local the step roughly
    if(diff_abs >= 50) {
        // each step is 25 roughly, diff_abs/25 == diff_abs*0.04
        step = (int)(diff_abs*0.04);

        if(diff > 0)
            reg_value_cal = reg_init - step;
        else if(diff < 0)
            reg_value_cal = reg_init + step;

        if(reg_value_cal > CAL_AVDD13_REG_REF_VAL_MAX) {
            MSADC_DEBUG_PRINTF(D_INF "Volt target reaches limited. Set the MAX-VALUE now.\n");
            return CAL_AVDD13_REG_REF_VAL_OFFSET_UP;
        }
        else if(reg_value_cal < CAL_AVDD13_REG_REF_VAL_MIN) {
            MSADC_DEBUG_PRINTF(D_INF "Volt target reaches limited. Set the MIN-VALUE now.\n");
            return CAL_AVDD13_REG_REF_VAL_OFFSET_DOWN;
        }
        #if PLF_PMIC
        psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_dcdc_rf_ctrl1), reg_value_cal, PMU_RTC1_RTC_RG_DCDC_RF_VBIT_NOR_TUNE_MASK);
        MSADC_DEBUG_PRINTF(D_INF "rd aft wr: [%p] = %08x\n", &AIC_PMU_RTC1->pmu_dcdc_rf_ctrl1, psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_dcdc_rf_ctrl1)));
        #endif
        //volt_reinit = (unsigned int)(msadc_ms_volt());
        reg_val = msadc_ms();
        volt_reinit = (int)(reg_val * (1619.0 / 32896) - 1619);
        dbg(D_INF "step=%d, val=%d, volt=%d\n", step, reg_value_cal, volt_reinit);

        // compare target-volt again
        diff = volt_reinit - CAL_AVDD13_TARGET;
        if(diff > 0)
            cal_sign = -1;
        else
            cal_sign = 1;
        v_ref = volt_reinit;
    }
    else if(0 < diff_abs && diff_abs < 50) {
        if(diff > 0)
            cal_sign = -1;
        else
            cal_sign = 1;
        step = 0;
        v_ref = volt_init;
    }
    else {
        // diff_abs == 0;
        return 0;
    }

    // 3. confirm the step precisely
    while(true) {
        reg_value_offset = cal_sign * (step + 1);
        reg_value_cal = reg_init + reg_value_offset;

        if(reg_value_cal<CAL_AVDD13_REG_REF_VAL_MIN || reg_value_cal>CAL_AVDD13_REG_REF_VAL_MAX) {
            MSADC_DEBUG_PRINTF(D_INF "reg value reaches limited\n");
            return cal_sign * step;

        } else {
            #if PLF_PMIC
            psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_dcdc_rf_ctrl1), reg_value_cal, PMU_RTC1_RTC_RG_DCDC_RF_VBIT_NOR_TUNE_MASK);
            MSADC_DEBUG_PRINTF(D_INF "rd aft wr: [%p] = %08x\n", &AIC_PMU_RTC1->pmu_dcdc_rf_ctrl1, psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_dcdc_rf_ctrl1)));
            #endif
            //v_cal = (unsigned int)(msadc_ms_volt());
            reg_val = msadc_ms();
            v_cal = (int)(reg_val * (1619.0 / 32896) - 1619);
            dbg(D_INF "ofst=%d, val=%d, volt=%d\n", reg_value_offset, reg_value_cal, v_cal);

            if((v_cal - CAL_AVDD13_TARGET)*(v_ref - CAL_AVDD13_TARGET)<=0) {
                if(co_abs(v_cal - CAL_AVDD13_TARGET)<=co_abs(v_ref - CAL_AVDD13_TARGET))
                    return reg_value_offset;
                else
                    return reg_value_offset - cal_sign * 1;
            } else {
                v_ref = v_cal;
            }
        }
        step++;
    }
}

void msadc_cal_avdd13(void)
{
    unsigned int reg_val;
    int volt_inital;
    uint32_t reg_inital;
    int reg_value_offset;

    // 1. msadc inital
    //msadc_init(40, 1); // clk_div=40, widow=512, denom=1.0/32896
    //AIC_MSADC->cfg_msadc_mode = 0; // sw mode
    //msadc_basic_config();
    //msadc_ad_config();
    AIC_CPUSYSCTRL->clk_msadc_div = CPU_SYS_CTRL_CFG_CLK_MSADC_DIV_DENOM(40) |
                                    CPU_SYS_CTRL_CFG_CLK_MSADC_DIV_UPDATE;
    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_CHNP_SEL |
                                                 MSADC_REG_CFG_ANA_MSADC_CMP_BIT |
                                                 MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_MODE |
                                                 MSADC_REG_CFG_ANA_MSADC_TEST_MODE |
                                                 MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_CHOP_EN |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_GAIN_BIT |
                                                 MSADC_REG_CFG_ANA_MSADC_DEM_EN_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN |
                                                 MSADC_REG_CFG_ANA_MSADC_TS_MODE |
                                                 MSADC_REG_CFG_ANA_MSADC_RSVD_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_DITHER_MODE_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_VCOM_BIT_MASK);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val |  (0 |    // chnp_sel
                                                 0 |    // cmp_bit
                                                 MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT(0x79) |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_MODE | // sdm_mode
                                                 0 |    // test_mode
                                                 MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT(0x2) |
                                                 MSADC_REG_CFG_ANA_MSADC_CHOP_EN |
                                                 0 |    // sdm_gain_bit
                                                 MSADC_REG_CFG_ANA_MSADC_DEM_EN(0x3) |
                                                 MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN | // adc_ff_en
                                                 0 |    // ts_mode
                                                 MSADC_REG_CFG_ANA_MSADC_RSVD_BIT(0x0) |
                                                 MSADC_REG_CFG_ANA_MSADC_DITHER_MODE(0x1) |
                                                 MSADC_REG_CFG_ANA_MSADC_VCOM_BIT(0x1));
    // 2 set avdd13
    //msadc_input_sel_avdd13();
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL(1) | 0 | 0), // avddsense_sel/pu_vrtc0sense/pu_vbatsebse
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL_MASK | PMU_RTC1_RTC_RG_PU_VRTC0SENSE | PMU_RTC1_RTC_RG_PU_VBATSENSE));
    #endif
    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~(MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK |
                                                MSADC_REG_CFG_MSADC_WINDOW_MASK |
                                                MSADC_REG_CFG_MSADC_SW_DIFF_MODE);
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val |  (MSADC_REG_CFG_MSADC_SW_MUX_BITS(15) | // mux
                                                MSADC_REG_CFG_MSADC_WINDOW(512) | // window
                                                MSADC_REG_CFG_MSADC_SW_DIFF_MODE); // diff_mode
    //volt_inital = (unsigned int)(msadc_ms_volt());
    reg_val = msadc_ms();
    volt_inital = (int)(reg_val * (1619.0 / 32896) - 1619);
    dbg(D_INF "Initial    Volt:  %d mV\n", volt_inital);
    // 3 calibration
    #if PLF_PMIC
    reg_inital = ((psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_dcdc_rf_ctrl1))) & PMU_RTC1_RTC_RG_DCDC_RF_VBIT_NOR_TUNE_MASK)
                                                                                 >> PMU_RTC1_RTC_RG_DCDC_RF_VBIT_NOR_TUNE_LSB;
    #endif
    reg_value_offset = msadc_cal_avdd13_algorithm(volt_inital, reg_inital);
    dbg(D_INF "reg_value_offset: %d\n", reg_value_offset);

    // 4 set value
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_dcdc_rf_ctrl1),
                    (reg_inital + reg_value_offset), PMU_RTC1_RTC_RG_DCDC_RF_VBIT_NOR_TUNE_MASK);
    #endif
    //volt_inital = (unsigned int)(msadc_ms_volt());
    reg_val = msadc_ms();
    volt_inital = (int)(reg_val * (1619.0 / 32896) - 1619);
    dbg(D_INF "Calibrated Volt:  %d mV\n", volt_inital);
    // 5 finish calibration
    //msadc_vddsense_off();
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_pd_ctrl1),
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL(0) | // avddsense_sel
                     0 | // pu_vrtc0sense
                     0), // pu_vbatsense
                    (PMU_RTC1_RTC_RG_AVDDSENSE_SEL_MASK |
                     PMU_RTC1_RTC_RG_PU_VRTC0SENSE |
                     PMU_RTC1_RTC_RG_PU_VBATSENSE));
    #endif
}
/**    end of cal_avdd13 function    **/


/**
 * cal_vcore function
 * @ target value is 800mV
 */
static int msadc_cal_vcore_algorithm(int volt_init, uint32_t reg_init)
{
    unsigned int reg_val;
    int  v_ref, v_cal, volt_reinit;
    int cal_sign=0, step=0, reg_value_offset=0, reg_value_cal=0;

    // 1. compare target-volt first time
    int diff = volt_init - CAL_VCORE_TARGET;
    int diff_abs = co_abs(diff);
    // 2. local the step roughly
    if(diff_abs >= 48) {
        // each step is 18 roughly, diff_abs/18 -> diff_abs*0.055
        step = (int)(diff_abs*0.055);

        if(diff > 0)
            reg_value_cal = reg_init - step;
        else if(diff < 0)
            reg_value_cal = reg_init + step;
        else // diff == 0, don`t happen.
            return 0;

        if(reg_value_cal > CAL_VCORE_REG_REF_VAL_MAX) {
            MSADC_DEBUG_PRINTF(D_INF "Volt target reaches limited. Set the MAX-VALUE now.\n");
            return CAL_VCORE_REG_REF_VAL_OFFSET_UP;
        }
        else if(reg_value_cal < CAL_VCORE_REG_REF_VAL_MIN) {
            MSADC_DEBUG_PRINTF(D_INF "Volt target reaches limited. Set the MIN-VALUE now.\n");
            return CAL_VCORE_REG_REF_VAL_OFFSET_DOWN;
        }
        #if PLF_PMIC
        psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_ldo_vcore08_ctrl), reg_value_cal, PMU_RTC1_RTC_RG_LDO_VCORE08_VOSEL_NOR_TUNE_MASK);
        MSADC_DEBUG_PRINTF(D_INF "rd aft wr: [%p] = %08x\n", &AIC_PMU_RTC1->pmu_ldo_vcore08_ctrl, psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_ldo_vcore08_ctrl)));
        #endif
        reg_val = msadc_ms();
        volt_reinit = (int)(reg_val * 1214.0/32896 - 1214);
        dbg(D_INF "step=%d, val=%d, volt=%d\n", step, reg_value_cal, volt_reinit);

        // compare target-volt again
        diff = volt_reinit - CAL_VCORE_TARGET;
        if(diff > 0)
            cal_sign = -1;
        else
            cal_sign = 1;
        v_ref = volt_reinit;
    }
    else if(0 < diff_abs && diff_abs < 48) {
        if(diff > 0)
            cal_sign = -1;
        else
            cal_sign = 1;
        step = 0;
        v_ref = volt_init;
    }
    else {
        // diff_abs == 0;
        return 0;
    }

    // 3. confirm the step precisely
    while(true) {
        reg_value_offset = cal_sign * (step + 1);
        reg_value_cal = reg_init + reg_value_offset;

        if(reg_value_cal<CAL_VCORE_REG_REF_VAL_MIN || reg_value_cal>CAL_VCORE_REG_REF_VAL_MAX) {
            MSADC_DEBUG_PRINTF(D_INF "reg value reaches limited\n");
            return cal_sign * step;

        } else {
            #if PLF_PMIC
            psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_ldo_vcore08_ctrl), reg_value_cal, PMU_RTC1_RTC_RG_LDO_VCORE08_VOSEL_NOR_TUNE_MASK);
            MSADC_DEBUG_PRINTF(D_INF "rd aft wr: [%p] = %08x\n", &AIC_PMU_RTC1->pmu_ldo_vcore08_ctrl, psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_ldo_vcore08_ctrl)));
            #endif
            reg_val = msadc_ms();
            v_cal = (int)(reg_val * 1214.0/32896 - 1214);
            dbg(D_INF "ofst=%d, val=%d, volt=%d\n", reg_value_offset, reg_value_cal, v_cal);

            if((v_cal - CAL_VCORE_TARGET)*(v_ref - CAL_VCORE_TARGET)<=0) {
                if(co_abs(v_cal - CAL_VCORE_TARGET)<=co_abs(v_ref - CAL_VCORE_TARGET))
                    return reg_value_offset;
                else
                    return reg_value_offset - cal_sign * 1;
            } else {
                v_ref = v_cal;
            }
        }
        step++;
    }


    return 0;
}

void msadc_cal_vcore(void)
{
    uint32_t reg_val, reg_inital;
    int volt_inital, reg_value_offset;

    // 1 msadc inital && 2 set vcore
    //msadc_init(40, 1); // clk_div=40, widow=512, denom=1.0/32896
    //msadc_basic_config();
    //msadc_ad_config();
    //msadc_input_sel_vcore();
    AIC_CPUSYSCTRL->clk_msadc_div = CPU_SYS_CTRL_CFG_CLK_MSADC_DIV_DENOM(40) |
                                    CPU_SYS_CTRL_CFG_CLK_MSADC_DIV_UPDATE;

    reg_val = AIC_MSADC->cfg_msadc_sw_ctrl1 & ~(MSADC_REG_CFG_MSADC_WINDOW_MASK |
                                               MSADC_REG_CFG_MSADC_SW_MUX_BITS_MASK |
                                               MSADC_REG_CFG_MSADC_SW_DIFF_MODE);
    AIC_MSADC->cfg_msadc_sw_ctrl1 = reg_val |  (MSADC_REG_CFG_MSADC_WINDOW(512) |
                                                MSADC_REG_CFG_MSADC_SW_MUX_BITS(11) | 0);


    reg_val = AIC_MSADC->cfg_msadc_ana_ctrl0 & ~(MSADC_REG_CFG_ANA_MSADC_CMP_BIT |
                                                 MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_CHOP_EN |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_GAIN_BIT |
                                                 MSADC_REG_CFG_ANA_MSADC_DEM_EN_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_RSVD_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_DITHER_MODE_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_VCOM_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT_MASK |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_MODE |
                                                 MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN |
                                                 MSADC_REG_CFG_ANA_MSADC_TS_MODE |
                                                 MSADC_REG_CFG_ANA_MSADC_CHNP_SEL |
                                                 MSADC_REG_CFG_ANA_MSADC_TEST_MODE);
    AIC_MSADC->cfg_msadc_ana_ctrl0 = reg_val |  (0 |    // cmp_bit
                                                 MSADC_REG_CFG_ANA_MSADC_IBIAS_BIT(0x2) |
                                                 MSADC_REG_CFG_ANA_MSADC_CHOP_EN |
                                                 0 |    // sdm_gain_bit
                                                 MSADC_REG_CFG_ANA_MSADC_DEM_EN(0x3) |
                                                 MSADC_REG_CFG_ANA_MSADC_RSVD_BIT(0x0) |
                                                 MSADC_REG_CFG_ANA_MSADC_DITHER_MODE(0x1) |
                                                 MSADC_REG_CFG_ANA_MSADC_VCOM_BIT(0x1) |
                                                 MSADC_REG_CFG_ANA_MSADC_VBE_CAL_BIT(0x79) |
                                                 MSADC_REG_CFG_ANA_MSADC_SDM_MODE | // sdm_mode
                                                 MSADC_REG_CFG_ANA_MSADC_ADC_FF_EN | // adc_ff_en
                                                 0 |
                                                 MSADC_REG_CFG_ANA_MSADC_CHNP_SEL |
                                                 0);
    reg_val = msadc_ms();
    volt_inital = (int)(reg_val * 1214.0/32896 - 1214);
    #if PLF_PMIC
    reg_inital = ((psim_read((unsigned int)(&AIC_PMU_RTC1->pmu_ldo_vcore08_ctrl))) & PMU_RTC1_RTC_RG_LDO_VCORE08_VOSEL_NOR_TUNE_MASK)
                                                                                    >> PMU_RTC1_RTC_RG_LDO_VCORE08_VOSEL_NOR_TUNE_LSB;
    #endif
    dbg(D_INF "Initl vcore Volt: %d mV, reg: %x\n", volt_inital, reg_inital);

    // 3 calibration
    reg_value_offset = msadc_cal_vcore_algorithm(volt_inital, reg_inital);
    dbg(D_INF "reg_value_offset: %d\n", reg_value_offset);

    // 4 set value
    #if PLF_PMIC
    psim_mask_write((unsigned int)(&AIC_PMU_RTC1->pmu_ldo_vcore08_ctrl),
                    reg_inital + reg_value_offset, PMU_RTC1_RTC_RG_LDO_VCORE08_VOSEL_NOR_TUNE_MASK);
    #endif
    reg_val = msadc_ms();
    volt_inital = (int)(reg_val * 1214.0/32896 - 1214);
    dbg(D_INF "Calib vcore Volt: %d mV\n", volt_inital);
}
/**    end of cal_vcore function    **/


#if 0
/**
 * cal_ipa function
 */
int msadc_ipa_cal_algorithm(int reg_vl_init)
{
    int num;
    uint32_t diff1, diff2;
    uint32_t reg_val, i_pax, i_pa_max, i_pa_min, i_pa_tmp;
    float v_ref, v_tmp;

    wlan_rf_gain_mem_fetch_reg_set(0x8000 + CAL_IPA_GEAR);
    msadc_pa_cal_sel5u();
    v_ref = (unsigned int)(msadc_ms_volt());
    msadc_pa_cal_sel_core();
    i_pax = (unsigned int)(msadc_ms_volt()/v_ref * MSADC_CURR_DIVISOR);
    dbg("initial   ipa  current: %d mA\n", i_pax);
    //dbg("initial current of pa(mA): %03d, rd [%08x]=%08x\n\n",
    //            i_pax, WLAN_RF_APC_TABLE_OUT_REG0_ADDR, wlan_rf_apc_table_out_reg0_get());

    if(CAL_IPA_TARGET > i_pax) {
        diff1 = CAL_IPA_TARGET - i_pax;
        //dbg("diff1: %d\n", diff1);
        for(num=reg_vl_init+1; num<=CAL_IPA_VL_VALUE_MAX; num++) {
            WF_APC_WR(CAL_IPA_VL_ADDR(CAL_IPA_GEAR), num);
            wlan_rf_gain_mem_fetch_reg_set(0x8000 + CAL_IPA_GEAR);
            i_pa_tmp = (unsigned int)(msadc_ms_volt()/v_ref * MSADC_CURR_DIVISOR);
            //dbg("Mid-CAL current of pa(mA) : %d\n", i_pa_tmp);

            if(i_pa_tmp > CAL_IPA_TARGET) {
                diff2 = i_pa_tmp - CAL_IPA_TARGET;
                return (diff1>diff2) ? num : num-1;
            } else if(i_pa_tmp < CAL_IPA_TARGET) {
                diff1 = CAL_IPA_TARGET - i_pa_tmp;
                // diff1 approach threshold
                if(diff1<2)
                    return num;
            } else {
                // i_pa_tmp == CAL_IPA_TARGET
                return num;
            }
            //dbg("diff1: %d,    diff2: %d\n", diff1, diff2);
        }
        return CAL_IPA_VL_VALUE_MAX;
    }
    else if(CAL_IPA_TARGET < i_pax) {
        diff1 = i_pax - CAL_IPA_TARGET;
        //dbg("diff1: %d\n", diff1);
        for(num=reg_vl_init-1; num>=CAL_IPA_VL_VALUE_MIN; num--) {
            WF_APC_WR(CAL_IPA_VL_ADDR(CAL_IPA_GEAR), num);
            wlan_rf_gain_mem_fetch_reg_set(0x8000 + CAL_IPA_GEAR);
            i_pa_tmp = (unsigned int)(msadc_ms_volt()/v_ref * MSADC_CURR_DIVISOR);
            //dbg("Mid-CAL current of pa(mA) : %d\n", i_pa_tmp);

            if(i_pa_tmp < CAL_IPA_TARGET) {
                diff2 = CAL_IPA_TARGET - i_pa_tmp;
                return (diff1>diff2) ? num : num+1;
            } else if(i_pa_tmp > CAL_IPA_TARGET) {
                diff1 = i_pa_tmp - CAL_IPA_TARGET;
                // diff1 approach threshold
                if(diff1<4)
                    return num;
            } else {
                // i_pa_tmp == CAL_IPA_TARGET
                return num;
            }
            //dbg("diff1: %d,    diff2: %d\n", diff1, diff2);
        }
        return CAL_IPA_VL_VALUE_MIN;
    }
    else {
        // CAL_IPA_TARGET == i_pax
        return reg_vl_init;
    }
}

uint8_t msadc_cal_ipa(void)
{
    uint32_t bit1, bit2, bit3, bit4;
    uint32_t reg_vl_init, reg_vl_update;
    uint32_t reg_val, apc_address, apc_vbit_value;
    float v_ref, v_tmp;

    // 1. msadc initial
    msadc_init(40, 1);
    msadc_basic_config();
    msadc_ad_config();

    // 2. msadc input sel pa sense
    msadc_input_sel_pa_sense();
    msadc_set_diff_mode();

    // 3. tx on
    /* 4-1  [22:19] */
    bit1 = wlan_rf_rxon_reg_getf();
    bit2 = wlan_rf_rxon_dr_getf();
    bit3 = wlan_rf_txon_reg_getf();
    bit4 = wlan_rf_txon_dr_getf();
    /* [22:19] write: 14-1110 */
    wlan_rf_rxon_reg_setf(0);
    wlan_rf_rxon_dr_setf(1);
    wlan_rf_txon_reg_setf(1);
    wlan_rf_txon_dr_setf(1);

    // 4. pa calibration
    // 4.1 change apc ram to sw
#if 1
    wlan_rftable_swmode_enable(RF_TABLE_APC);
#else
    reg_val = wlan_rf_gain_mem_ctrl_reg_get();
    wlan_rf_gain_mem_ctrl_reg_set((reg_val & 0xf0) | 2);
    wlan_rf_gain_mem_ctrl_reg_set((reg_val & 0xf0) | 0);
    wlan_rf_gain_mem_ctrl_reg_set((reg_val & 0xf0) | 4);
    wlan_rf_gain_mem_ctrl_reg_set((reg_val & 0xf0) | 5);
#endif

#if 0
    // Init gear 14
    apc_address = APC_ADDRESS_BASE + 14 * 8;
    apc_vbit_value = 0xFF92203F;
    MEM_WR(apc_address, apc_vbit_value);
    //dbg("rd aft wr: [%08x] = %08x\n", apc_address, MEM_RD(apc_address));
    apc_address = APC_ADDRESS_BASE + 14 * 8 + 4;
    apc_vbit_value = 0x00004035;
    MEM_WR(apc_address, apc_vbit_value);
    //dbg("rd aft wr: [%08x] = %08x\n", apc_address, MEM_RD(apc_address));
#endif

    // 4.2 cal vl
    // read 0x40346c70  [23:21]
    reg_vl_init = WF_APC_RD(CAL_IPA_VL_ADDR(CAL_IPA_GEAR));
    reg_vl_update = msadc_ipa_cal_algorithm(reg_vl_init);
    dbg("reg value initial: %d\n", reg_vl_init);
    dbg("reg value updated: %d\n", reg_vl_update);

    // write vl calibration results to APC
    //WF_APC_WR(CAL_IPA_VL_ADDR(CAL_IPA_GEAR), (reg_vl_init + reg_vl_offset));
    WF_APC_WR(CAL_IPA_VL_ADDR(CAL_IPA_GEAR), reg_vl_update);
    wlan_rf_gain_mem_fetch_reg_set(0x8000 + CAL_IPA_GEAR);

    // measure current
    msadc_pa_cal_sel5u();
    v_ref = msadc_ms_volt();
    msadc_pa_cal_sel_core();
    v_tmp = msadc_ms_volt();
    dbg("Calibrated ipa current: %d mA\n", (unsigned int)(v_tmp/v_ref * MSADC_CURR_DIVISOR));

#if 1
    // 4.3 recovery apc vl bit
    WF_APC_WR(CAL_IPA_VL_ADDR(CAL_IPA_GEAR), reg_vl_init);
    wlan_rf_gain_mem_fetch_reg_set(0x8000 + CAL_IPA_GEAR);
#endif

    #if 0
    // 5. write calibration value in APC table
    //write_reg_value_offset_to_apc(reg_vl_offset);
    reg_vl_offset = reg_vl_update - reg_vl_init;
    for(uint32_t gear=0; gear<15; gear++) {
        apc_address = APC_ADDRESS_BASE + gear * 8;
        apc_vbit_init = WF_APC_RD(apc_address);
        apc_vbit_value = apc_vbit_init + reg_vl_offset;
        if(apc_vbit_value > CAL_IPA_VL_VALUE_MAX)
            apc_vbit_value = CAL_IPA_VL_VALUE_MAX;
        else if(apc_vbit_value < CAL_IPA_VL_VALUE_MIN)
            apc_vbit_value = CAL_IPA_VL_VALUE_MIN;

        WF_APC_WR(apc_address, apc_vbit_value);
        //MSADC_DEBUG_PRINTF("rd aft wr: [%08x] = %08x\n", apc_address, MEM_RD(apc_address));
    }
    #endif

    // 6. change apc ram to hw
#if 1
    wlan_rftable_swmode_disable(RF_TABLE_APC);
#else
    reg_val = wlan_rf_gain_mem_ctrl_reg_get();
    wlan_rf_gain_mem_ctrl_reg_set((reg_val & 0xf0) | 1);
    wlan_rf_gain_mem_ctrl_reg_set((reg_val & 0xf0) | 0);
    wlan_rf_gain_mem_ctrl_reg_set((reg_val & 0xf0) | 2);
    wlan_rf_gain_mem_ctrl_reg_set((reg_val & 0xf0) | 3);
#endif

    // 7. turn off pa cal
    msadc_pa_cal_off();

    // 8. recovery tx man ctrl
    wlan_rf_rxon_reg_setf(bit1);
    wlan_rf_rxon_dr_setf(bit2);
    wlan_rf_txon_reg_setf(bit3);
    wlan_rf_txon_dr_setf(bit4);

    return reg_vl_update;
}
/**    end of cal_ipa function    **/
#endif


/**
 * Functions
 */

int msadc_volt_measure(int vst)
{
    int ret = 0;
    if (vst == MSADC_VOLT_VBAT) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ad_config();
        msadc_sel_vbat();
        // msadc_param.mult = 5.5;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        ms_val = msadc_ms();
        msadc_vddsense_off();
        ret = (int)ms_val * 6677 / MSADC_DENOM_REC - 6677;// Convert to mV
    } else if (vst == MSADC_VOLT_VRTC0) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ad_config();
        msadc_input_sel_vtrc0();
        // msadc_param.mult = 1.0;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        ms_val = msadc_ms();
        msadc_vddsense_off();
        ret = (int)ms_val * 1214 / MSADC_DENOM_REC - 1214;// Convert to mV
    } else if (vst == MSADC_VOLT_VCORE) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ad_config();
        msadc_input_sel_vcore();
        // msadc_param.mult = 1.0;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        ms_val = msadc_ms();
        ret = (int)ms_val * 1214 / MSADC_DENOM_REC - 1214;// Convert to mV
    } else if (vst == MSADC_VOLT_AVDD33) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ad_config();
        msadc_input_sel_avdd33();
        // msadc_param.mult = 4.0;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        ms_val = msadc_ms();
        msadc_vddsense_off();
        ret = (int)ms_val * 4856 / MSADC_DENOM_REC - 4856;// Convert to mV
    } else if (vst == MSADC_VOLT_AVDD18) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ad_config();
        msadc_input_sel_avdd18();
        // msadc_param.mult = 2.0;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        ms_val = msadc_ms();
        msadc_vddsense_off();
        ret = (int)ms_val * 2428 / MSADC_DENOM_REC - 2428;// Convert to mV
    } else if (vst == MSADC_VOLT_AVDD13) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ad_config();
        msadc_input_sel_avdd13();
        // msadc_param.mult = 4.0 / 3.0;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        ms_val = msadc_ms();
        msadc_vddsense_off();
        ret = (int)ms_val * 1618 / MSADC_DENOM_REC - 1618;// Convert to mV
    } else if (vst == MSADC_VOLT_GPB2) {
        unsigned int ms_val;
        #if 1
        msadc_basic_config();
        msadc_ad_config();
        msadc_input_sel_gpio2();
        // msadc_param.mult = 1.0;
        // ms_mV = (1 - ms_val / (float)MSADC_DENOM_REC) * 1214 * msadc_param.mult;
        ms_val = msadc_ms();
        ret = 1214 - (int)ms_val * 1214 / MSADC_DENOM_REC;// Convert to mV
        #else
        unsigned int rdata;
        AIC_MSADC->cfg_msadc_mode = 0; // sw mode
        AIC_IOMUX->pad_gpiob_2_cfg_reg = 0x10030000;

        rdata = AIC_ANAREG1->gpiob_cfg1;
        rdata =  0xffffffbf & rdata;
        AIC_ANAREG1->gpiob_cfg1 = rdata | ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_EN;

        rdata = AIC_MSADC->cfg_msadc_sw_ctrl1;
        rdata =  0xeffffff0 & rdata;
        AIC_MSADC->cfg_msadc_sw_ctrl1 = rdata | MSADC_REG_CFG_MSADC_SW_MUX_BITS(0x2);
        AIC_MSADC->cfg_msadc_sw_ctrl0 = MSADC_REG_CFG_MSADC_SW_START_PULSE;
        while((AIC_MSADC->cfg_msadc_int_raw) != 0x1);
        AIC_MSADC->cfg_msadc_int_raw = 1;
        rdata = AIC_MSADC->cfg_msadc_ro_acc;
        rdata  = 1175 - rdata*1175/32896;
        dbg("MSADC GPIOB2 voltage is %d mV\n", rdata);
        #endif
    } else if (vst == MSADC_VOLT_GPB3) {
        unsigned int ms_val;
        #if 1
        msadc_basic_config();
        msadc_ad_config();
        msadc_input_sel_gpio3();
        // msadc_param.mult = 1.0;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        ms_val = msadc_ms();
        ret = (int)ms_val * 1214 / MSADC_DENOM_REC - 1214;// Convert to mV
        #else
        unsigned int rdata;

        AIC_MSADC->cfg_msadc_mode = 0; // sw mode
        AIC_IOMUX->pad_gpiob_3_cfg_reg =  0x10030000;

        rdata = AIC_ANAREG1->gpiob_cfg1;
        rdata =  0xffffffbf & rdata;
        AIC_ANAREG1->gpiob_cfg1 = rdata | ANALOG_REG1_RF_CFG_ANA_GPIOB_MUX_EN;

        rdata = AIC_MSADC->cfg_msadc_sw_ctrl1;
        rdata =  0xeffffff0 & rdata;
        AIC_MSADC->cfg_msadc_ana_ctrl0 |= MSADC_REG_CFG_ANA_MSADC_CHNP_SEL;
        AIC_MSADC->cfg_msadc_sw_ctrl1 = rdata | MSADC_REG_CFG_MSADC_SW_MUX_BITS(0x2);
        AIC_MSADC->cfg_msadc_sw_ctrl0 = MSADC_REG_CFG_MSADC_SW_START_PULSE;
        while((AIC_MSADC->cfg_msadc_int_raw) != 0x1);
        AIC_MSADC->cfg_msadc_int_raw = 1;
        rdata = AIC_MSADC->cfg_msadc_ro_acc;
        rdata  = rdata*1175/32896 -1175;
        #endif
    } else if (vst == MSADC_VOLT_GPB23DIFF) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ad_config();
        msadc_input_sel_gpio23_diff();
        // msadc_param.mult = 1.0;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        ms_val = msadc_ms();
        ret = (int)ms_val * 1214 / MSADC_DENOM_REC - 1214;// Convert to mV
    }
    return ret;
}

int msadc_temp_measure(int tst)
{
    int ret = 0;
    if (tst == MSADC_TEMP_CHIP) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ts_config();
        ms_val = msadc_ms();
        ret = (int)ms_val * 330 / MSADC_DENOM_REC - 283;
    } else if (tst == MSADC_TEMP_PA5G) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ad_config();
        msadc_ts_pa5g_on();
        msadc_input_sel_ts_pa();
        // msadc_param.mult = 1.0;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        // ms_C = ms_mV * 547.9 - 275.6
        ms_val = msadc_ms();
        msadc_ts_pa_off();
        ret = (int)ms_val * 1214 * 548 / MSADC_DENOM_REC - 1214 * 548 - 276;
    } else if (tst == MSADC_TEMP_PA24G) {
        unsigned int ms_val;
        msadc_basic_config();
        msadc_ad_config();
        msadc_ts_pa24g_on();
        msadc_input_sel_ts_pa();
        // msadc_param.mult = 1.0;
        // ms_mV = (ms_val / (float)MSADC_DENOM_REC - 1) * 1214 * msadc_param.mult;
        // ms_C = ms_mV * 547.9 - 275.6
        ms_val = msadc_ms();
        msadc_ts_pa_off();
        ret = (int)ms_val * 1214 * 548 / MSADC_DENOM_REC - 1214 * 548 - 276;
    }
    return ret;
}
