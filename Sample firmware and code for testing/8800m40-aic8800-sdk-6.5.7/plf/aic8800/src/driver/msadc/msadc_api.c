/*
 * Copyright (C) 2018-2023 AICSemi Ltd.
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

/**
 * Includes
 */

#include "msadc_api.h"


/**
 * Macros
 */

#define MSADC_DEBUG_PRINTF(fmt, ...)        do {} while(0) //dbg(fmt, ##__VA_ARGS__)//

/**
 * Functions
 */

int msadc_volt_measure(int vst)
{
    int ret = 0;
    if (vst == MSADC_VOLT_VBAT) {
        unsigned int rdata;
        #if PLF_PMIC_VER_LITE
        //PU VBAT sense and VRTC sense
        PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteRtcCore->rtc_rg_por_ctrl_cfg1),
            (AIC1000LITE_RTC_CORE_RTC_RG_PU_VRTC_SENSE | AIC1000LITE_RTC_CORE_RTC_RG_PU_VBAT_SENSE),
            (AIC1000LITE_RTC_CORE_RTC_RG_PU_VRTC_SENSE | AIC1000LITE_RTC_CORE_RTC_RG_PU_VBAT_SENSE));
        PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_sw_ctrl1),
            (AIC1000LITE_MSADC_CFG_MSADC_SW_MUX_BITS(0xD) | AIC1000LITE_MSADC_CFG_MSADC_SW_DIFF_MODE),
            (AIC1000LITE_MSADC_CFG_MSADC_SW_MUX_BITS(0xF) | AIC1000LITE_MSADC_CFG_MSADC_SW_DIFF_MODE));
        PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_ana_ctrl0),
            (0 | 0 | AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_MODE | AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_GAIN_BIT |
            AIC1000LITE_MSADC_CFG_ANA_MSADC_ADC_FF_EN),
            (AIC1000LITE_MSADC_CFG_ANA_MSADC_CHNP_SEL | AIC1000LITE_MSADC_CFG_ANA_MSADC_TS_MODE |
            AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_MODE | AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_GAIN_BIT |
            AIC1000LITE_MSADC_CFG_ANA_MSADC_ADC_FF_EN));
        PMIC_MEM_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_sw_ctrl0),
            AIC1000LITE_MSADC_CFG_MSADC_SW_START_PULSE);
        while(PMIC_MEM_READ((unsigned int)(&aic1000liteMsadc->cfg_msadc_int_raw)) != 0x1);
        PMIC_MEM_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_int_raw), 0x1);
        rdata  = PMIC_MEM_READ((unsigned int)(&aic1000liteMsadc->cfg_msadc_ro_acc));
        #endif
        #if PLF_PMIC_VER_AUD
        //PU VBAT sense and VRTC sense
        rdata  = PMIC_MEM_READ((unsigned int)(&aic1000audRtcCore->rtc_rg_por_ctrl_cfg1));
        PMIC_MEM_WRITE((unsigned int)(&aic1000audRtcCore->rtc_rg_por_ctrl_cfg1),
            rdata | AIC1000AUD_RTC_CORE_RTC_RG_PU_VRTC_SENSE | AIC1000AUD_RTC_CORE_RTC_RG_PU_VBAT_SENSE);
        PMIC_MEM_WRITE((unsigned int)(&aic1000audMsadc->cfg_msadc_mode), 0);

        rdata  = PMIC_MEM_READ((unsigned int)(&aic1000audMsadc->cfg_msadc_sw_ctrl1));
        PMIC_MEM_WRITE((unsigned int)(&aic1000audMsadc->cfg_msadc_sw_ctrl1),
            rdata | AIC1000AUD_MSADC_CFG_MSADC_SW_DIFF_MODE | AIC1000AUD_MSADC_CFG_MSADC_SW_MUX_BITS(0xF));

        rdata  = PMIC_MEM_READ((unsigned int)(&aic1000audMsadc->cfg_msadc_sw_ctrl1));
        rdata  = 0xfffffff0 & rdata;
        PMIC_MEM_WRITE((unsigned int)(&aic1000audMsadc->cfg_msadc_sw_ctrl1),
            rdata | AIC1000AUD_MSADC_CFG_MSADC_SW_DIFF_MODE | AIC1000AUD_MSADC_CFG_MSADC_SW_MUX_BITS(0xc));
        PMIC_MEM_WRITE((unsigned int)(&aic1000audMsadc->cfg_msadc_sw_ctrl0),
            AIC1000AUD_MSADC_CFG_MSADC_SW_START_PULSE);
        while(PMIC_MEM_READ((unsigned int)(&aic1000audMsadc->cfg_msadc_int_raw)) != 0x1);
        PMIC_MEM_WRITE((unsigned int)(&aic1000audMsadc->cfg_msadc_int_raw), 0x1);
        rdata  = PMIC_MEM_READ((unsigned int)(&aic1000audMsadc->cfg_msadc_ro_acc));
        #endif
        ret = ((int)rdata * 1175 / 32896 - 1175) * 42 / 10;// Convert to mV
    } else if (vst == MSADC_VOLT_VIO) {
        (void)0; //TODO:
    } else if (vst == MSADC_VOLT_DCDC_VCORE) {
        unsigned int rdata;
        #if PLF_PMIC_VER_LITE
        //PU VBAT sense and VRTC sense
        PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteRtcCore->rtc_rg_por_ctrl_cfg1),
            (AIC1000LITE_RTC_CORE_RTC_RG_PU_VRTC_SENSE | AIC1000LITE_RTC_CORE_RTC_RG_PU_VBAT_SENSE),
            (AIC1000LITE_RTC_CORE_RTC_RG_PU_VRTC_SENSE | AIC1000LITE_RTC_CORE_RTC_RG_PU_VBAT_SENSE));
        PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_sw_ctrl1),
            (AIC1000LITE_MSADC_CFG_MSADC_SW_MUX_BITS(0xA) | 0),
            (AIC1000LITE_MSADC_CFG_MSADC_SW_MUX_BITS(0xF) | AIC1000LITE_MSADC_CFG_MSADC_SW_DIFF_MODE));
        PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_ana_ctrl0),
            (0 | 0 | AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_MODE | AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_GAIN_BIT |
            AIC1000LITE_MSADC_CFG_ANA_MSADC_ADC_FF_EN),
            (AIC1000LITE_MSADC_CFG_ANA_MSADC_CHNP_SEL | AIC1000LITE_MSADC_CFG_ANA_MSADC_TS_MODE |
            AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_MODE | AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_GAIN_BIT |
            AIC1000LITE_MSADC_CFG_ANA_MSADC_ADC_FF_EN));
        PMIC_MEM_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_sw_ctrl0),
            AIC1000LITE_MSADC_CFG_MSADC_SW_START_PULSE);
        while(PMIC_MEM_READ((unsigned int)(&aic1000liteMsadc->cfg_msadc_int_raw)) != 0x1);
        PMIC_MEM_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_int_raw), 0x1);
        rdata  = PMIC_MEM_READ((unsigned int)(&aic1000liteMsadc->cfg_msadc_ro_acc));
        #endif
        ret = ((int)rdata * 1175 / 32896 - 1175) * 42 / 10;// Convert to mV
    }
    return ret;
}

int msadc_temp_measure(int tst)
{
    int ret = 0;
    if (tst == MSADC_TEMP_CHIP) {
        unsigned int rdata;
        #if PLF_PMIC_VER_LITE
        PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_sw_ctrl1),
            (AIC1000LITE_MSADC_CFG_MSADC_SW_MUX_BITS(0x0) | AIC1000LITE_MSADC_CFG_MSADC_SW_DIFF_MODE),
            (AIC1000LITE_MSADC_CFG_MSADC_SW_MUX_BITS(0xF) | AIC1000LITE_MSADC_CFG_MSADC_SW_DIFF_MODE));
        PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_ana_ctrl0),
            (0 | AIC1000LITE_MSADC_CFG_ANA_MSADC_TS_MODE | 0 | 0 | 0),
            (AIC1000LITE_MSADC_CFG_ANA_MSADC_CHNP_SEL | AIC1000LITE_MSADC_CFG_ANA_MSADC_TS_MODE |
            AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_MODE | AIC1000LITE_MSADC_CFG_ANA_MSADC_SDM_GAIN_BIT |
            AIC1000LITE_MSADC_CFG_ANA_MSADC_ADC_FF_EN));
        PMIC_MEM_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_sw_ctrl0),
            AIC1000LITE_MSADC_CFG_MSADC_SW_START_PULSE);
        while(PMIC_MEM_READ((unsigned int)(&aic1000liteMsadc->cfg_msadc_int_raw)) != 0x1);
        PMIC_MEM_WRITE((unsigned int)(&aic1000liteMsadc->cfg_msadc_int_raw), 0x1);
        rdata  = PMIC_MEM_READ((unsigned int)(&aic1000liteMsadc->cfg_msadc_ro_acc));
        #endif
        #if PLF_PMIC_VER_AUD
        rdata = 0; //TBD:
        #endif
        ret = (int)rdata * 659 / 65792 - 281;
    } else if (tst == MSADC_TEMP_PA) {
        (void)0; //TODO:
    }
    return ret;
}
