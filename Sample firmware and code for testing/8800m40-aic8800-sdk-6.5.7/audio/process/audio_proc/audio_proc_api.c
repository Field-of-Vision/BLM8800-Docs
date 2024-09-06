#include <stdint.h>
#include <stdbool.h>
#include "plf.h"
#include "audio_types.h"
#include "aud_proc.h"
#if (PLF_AIC8800 && PLF_PMIC && PLF_PMIC_VER_LITE && PLF_PMIC_MCLK)
#include "pmic_api.h"
#endif
#include "reg_iomux.h"
#include "sysctrl_api.h"
#include "dbg.h"
#include "dbg_assert.h"

#define I2S_MCLK 12288000
#define SRC_MODE_NB       9
#define AUD_SRC_DIV_NB    6

// 100000 * out_samp_rate / in_samp_rate
// divider: 1
static const uint32_t dac_src_mode_ratio[SRC_MODE_NB] = {
    (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_8000)),
    (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_11025)),
    (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_12000)),
    (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_16000)),
    (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_22050)),
    (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_24000)),
    (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_32000)),
    (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_44100)),
    (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_48000)),
};

// 100000 * out_samp_rate / in_samp_rate
// divider: 1 2 3 4 6 12
static const uint32_t aud_src_mode_ratio[AUD_SRC_DIV_NB][SRC_MODE_NB] = {
    {
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_8000)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_11025)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_12000)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_16000)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_22050)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_24000)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_32000)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_44100)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_48000)),
    },
    {
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_8000 / 2)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_11025 / 2)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_12000 / 2)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_16000 / 2)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_22050 / 2)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_24000 / 2)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_32000 / 2)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_44100 / 2)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_48000 / 2)),
    },
    {
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_8000 / 3)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_11025 / 3)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_12000 / 3)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_16000 / 3)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_22050 / 3)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_24000 / 3)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_32000 / 3)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_44100 / 3)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_48000 / 3)),
    },
    {
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_8000 / 4)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_11025 / 4)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_12000 / 4)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_16000 / 4)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_22050 / 4)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_24000 / 4)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_32000 / 4)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_44100 / 4)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_48000 / 4)),
    },
    {
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_8000 / 6)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_11025 / 6)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_12000 / 6)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_16000 / 6)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_22050 / 6)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_24000 / 6)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_32000 / 6)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_44100 / 6)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_48000 / 6)),
    },
    {
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_8000 / 12)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_11025 / 12)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_12000 / 12)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_16000 / 12)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_22050 / 12)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_24000 / 12)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_32000 / 12)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_44100 / 12)),
        (uint32_t)(100000 * ((float)AUD_SAMPRATE_48000 / (float)AUD_SAMPRATE_48000 / 12)),
    },
};

// 1st row is real divider
// 2nd row is corresponding vaule in aud_src_ctrl2[16:13]
static const uint8_t aud_src_div[2][AUD_SRC_DIV_NB] = {
    {1, 2, 3, 4, 6, 12},
    {0x0A, 0x09, 0x06, 0x08, 0x05, 0x04},
};

/*
 * for dac, 8bits
 * if (bit[7:0] != 0) {
 *     volume = bit[5:0] + bit[6] * 6dB + bit[7] * 12dB;
 * } else {
 *     volume = mute;
 * }
 * eg. 8'h33 = -0.5dB + 0 * 6dB + 0 * 12dB = -0.5dB;
 * eg. 8'h74 = 0dB + 1 * 6dB + 0 * 12dB = 6dB;
 * eg. 8'hB5 = 0.5dB + 0 * 6dB + 1 * 12dB = 12.5dB;
 * eg. 8'hff = 5.5dB + 1 * 6dB + 1 * 12dB = 23.5dB;
 *
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h0  | -26dB       |
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h1  | -25.5dB     |
 * |----------|-------|-------------|
 * | bit[5:0] |  ...  | +0.5dB/step |
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h34 |  0dB        |
 * |----------|-------|-------------|
 * | bit[5:0] |  ...  | +0.5dB/step |
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h3e |  5dB        |
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h3f |  5.5dB      |
 * |----------|-------|-------------|
 */
int audio_proc_dac_volume_set(uint8_t volume)
{
#if PLF_AIC8800
    uint32_t val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~(AUD_PROC_DAC_VOLUME_L_MASK | AUD_PROC_DAC_VOLUME_R_MASK)) |
        (AUD_PROC_DAC_VOLUME_L(volume) | AUD_PROC_DAC_VOLUME_R(volume));
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~(AUD_PROC_DAC_VOLUME_L_MASK | AUD_PROC_DAC_VOLUME_R_MASK)) |
        (AUD_PROC_DAC_VOLUME_L(volume) | AUD_PROC_DAC_VOLUME_R(volume));
#endif

    return 0;
}

/*
 * for adc, 4bits
 * |----------|-------|-------------|
 * | bit[3:0] | 4'h0  |  mute       |
 * |----------|-------|-------------|
 * | bit[3:0] | 4'h1  | -12dB       |
 * |----------|-------|-------------|
 * | bit[3:0] |  ...  | +2dB/step   |
 * |----------|-------|-------------|
 * | bit[3:0] | 4'h7  |  0dB        |
 * |----------|-------|-------------|
 * | bit[3:0] |  ...  | +2dB/step   |
 * |----------|-------|-------------|
 * | bit[3:0] | 4'he  |  14dB       |
 * |----------|-------|-------------|
 * | bit[3:0] | 4'hf  |  16dB       |
 * |----------|-------|-------------|
 */
int audio_proc_adc_volume_set(uint8_t volume)
{
#if PLF_AIC8800
    if (volume > 0x0F) {
        dbg("ERR: adc volume out of range\n");
        return -1;
    } else {
        uint32_t val = hwp_audProc->aud_proc_adc_cfg1;
        hwp_audProc->aud_proc_adc_cfg1 = (val & ~(AUD_PROC_ADC_VOLUME_L_MASK | AUD_PROC_ADC_VOLUME_R_MASK)) |
            (AUD_PROC_ADC_VOLUME_L(volume) | AUD_PROC_ADC_VOLUME_R(volume));
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (volume > 0x0F) {
        dbg("ERR: adc volume out of range\n");
        return -1;
    } else {
        uint32_t val = hwp_audProc->aud_proc_adc_cfg1;
        hwp_audProc->aud_proc_adc_cfg1 = (val & ~(AUD_PROC_ADC01_VOLUME_L_MASK | AUD_PROC_ADC01_VOLUME_R_MASK)) |
            (AUD_PROC_ADC01_VOLUME_L(volume) | AUD_PROC_ADC01_VOLUME_R(volume));
    }
#endif

    return 0;
}

uint8_t audio_proc_dac_volume_get(void)
{
    uint8_t vol;

#if PLF_AIC8800
    vol = (uint8_t)((hwp_audProc->aud_proc_dac_cfg1 & AUD_PROC_DAC_VOLUME_L_MASK) >> AUD_PROC_DAC_VOLUME_L_LSB);
#elif PLF_AIC8800MC
    vol = 0;
#elif PLF_AIC8800M40
    vol = (uint8_t)((hwp_audProc->aud_proc_dac_cfg1 & AUD_PROC_DAC_VOLUME_L_MASK) >> AUD_PROC_DAC_VOLUME_L_LSB);
#endif

    return vol;
}

uint8_t audio_proc_adc_volume_get(void)
{
    uint8_t vol;

#if PLF_AIC8800
    vol = (uint8_t)((hwp_audProc->aud_proc_adc_cfg1 & AUD_PROC_ADC_VOLUME_L_MASK) >> AUD_PROC_ADC_VOLUME_L_LSB);
#elif PLF_AIC8800MC
    vol = 0;
#elif PLF_AIC8800M40
    vol = (uint8_t)((hwp_audProc->aud_proc_adc_cfg1 & AUD_PROC_ADC01_VOLUME_L_MASK) >> AUD_PROC_ADC01_VOLUME_L_LSB);
#endif

    return vol;
}

/*
 *
 convert dac volume, from dB to reg valule
 * any value that > +23.5dB is regarded as +23.5dB, any value that < -25.5dB is regarded as mute
 * eg. input:-25dB      output:0x02
 * eg. input:0dB        output:0x34
 * eg. input:+6.5dB     output:0x75
 */
uint8_t audio_proc_dac_volume_convert_db_to_reg(float dB)
{
    uint8_t vol;

    if (dB < -25.5f) {
        vol = 0;
    } else if (dB <= 5.5f) {
        // (dB - (-25.5f)) / 0.5f + 1
        vol = (uint8_t)((int)(dB * 2) + 51) + 1;;
    } else if (dB <= 23.5f) {
        uint8_t vol_frac = 0;
        uint8_t vol_int = 0;

        while (dB >= 6) {
            dB -= 6;
            vol_int += 1;
        }
        vol_frac = (uint8_t)((int)(dB * 2)) + 0x34;
        vol = (vol_int << 6) | vol_frac;
    } else {
        vol = 0xFF;
    }

    return vol;
}

/*
 *
 convert adc volume, from dB to reg valule
 * any value that > +16dB is regarded as +16dB, any value that < -12dB is regarded as mute
 * eg. input:-12dB      output:0x01
 * eg. input:0dB        output:0x07
 * eg. input:+12dB      output:0x0D
 */
uint8_t audio_proc_adc_volume_convert_db_to_reg(int8_t dB)
{
    uint8_t vol;

    if (dB < -12) {
        vol = 0;
    } else if (dB > 16) {
        vol = 0x0F;
    } else {
        vol = (uint8_t)(dB + 12) / 2 + 1;
    }

    return vol;
}

/*
 *
 convert dac volume step, from dB to reg valule, dB must be multiple of 0.5dB
 * eg. input:0.5dB    output:1
 * eg. input:1dB      output:2
 * eg. input:3dB      output:6
 */
uint8_t audio_proc_dac_volume_step_convert_db_to_reg(float dB)
{
    uint8_t step;

    if (dB < 0) {
        dB = 0.0f - dB;
    }

    if (dB > 49.5f) {
        step = 99;
    } else {
        step = (uint8_t)(dB * 2);
    }

    return step;
}

/*
 *
 convert adc volume step, from dB to reg valule, dB must be multiple of 2dB
 * eg. input:2dB    output:1
 * eg. input:4dB    output:2
 * eg. input:6dB    output:3
 */
uint8_t audio_proc_adc_volume_step_convert_db_to_reg(uint8_t dB)
{
    uint8_t step;

    if (dB > 28) {
        step = 15;
    } else {
        step = dB / 2;
    }

    return step;
}

/*
 * for dac, 1 step is 0.5dB
 */
bool audio_proc_dac_volume_up(uint8_t step)
{
    uint8_t vol;
    uint8_t vol_frac;
    uint8_t vol_int;
    bool max_vol = false;

    vol = audio_proc_dac_volume_get();
    vol_frac = vol & 0x3F;
    vol_int = (vol & 0xC0) >> 6;

    while (step > 0) {
        if (step >= 0xC) {
            vol_frac += 0xC;
            step -= 0xC;
        } else {
            vol_frac += step;
            step = 0;
        }

        if (vol_frac > 0x3F) {
            vol_int += 1;
            vol_frac = (vol_frac & 0x3F) + 0x34;
        }

        if ((vol_int > 3) || ((vol_int == 3) && (vol_frac == 0x3F))) {
            max_vol = true;
            break;
        }
    }

    if (max_vol == true) {
        vol_int = 0x03;
        vol_frac =0x3F;
    }

    vol = (vol_int << 6) | vol_frac;

    audio_proc_dac_volume_set(vol);

    return max_vol;
}

/*
 * for dac, 1 step is 0.5dB
 */
bool audio_proc_dac_volume_down(uint8_t step)
{
    uint8_t vol;
    uint8_t vol_frac;
    uint8_t vol_int;
    bool min_vol = false;

    vol = audio_proc_dac_volume_get();
    vol_frac = vol & 0x3F;
    vol_int = (vol & 0xC0) >> 6;

    while (step > 0) {
        if (step >= 0xC) {
            if (vol_int > 0) {
                vol_int -= 1;
                step -= 0x0C;
            } else {
                if (vol_frac > step) {
                    vol_frac -= step;
                } else {
                    min_vol = true;
                }
                step = 0;
            }
        } else {
            // if vol_int > 0, vol_frac must >= 0x34, else vol_frac must <= 0x3F
            if (vol_int > 0) {
                vol_frac -= step;
                if (vol_frac < 0x34) {
                    vol_int -= 1;
                    vol_frac += 0x0C;
                }
            } else {
                if (vol_frac > step) {
                    vol_frac -= step;
                } else {
                    min_vol = true;
                }
            }
            step = 0;
        }
    }

    if (min_vol == true) {
        vol_int = 0;
        vol_frac = 0;
    }

    vol = (vol_int << 6) | vol_frac;

    audio_proc_dac_volume_set(vol);

    return min_vol;
}

/*
 * for adc, 1 step is 2dB
 */
bool audio_proc_adc_volume_up(uint8_t step)
{
    uint8_t vol;
    bool max_vol = false;

    vol = audio_proc_adc_volume_get();

    vol += step;
    if (vol >= 0x0F) {
        max_vol = true;
        vol = 0x0F;
    }

    audio_proc_adc_volume_set(vol);

    return max_vol;
}

/*
 * for adc, 1 step is 2dB
 */
bool audio_proc_adc_volume_down(uint8_t step)
{
    uint8_t vol;
    bool min_vol = false;

    vol = audio_proc_adc_volume_get();

    if (vol > step) {
        vol -= step;
    } else {
        min_vol = true;
        vol = 0;
    }

    audio_proc_adc_volume_set(vol);

    return min_vol;
}

void audio_proc_dac_volume_mute(void)
{
    audio_proc_dac_volume_set(0);
}

void audio_proc_adc_volume_mute(void)
{
    audio_proc_adc_volume_set(0);
}

/*
 * reset dac volume to 0dB
 */
void audio_proc_dac_volume_reset(void)
{
    audio_proc_dac_volume_set(0x34);
}

/*
 * reset adc volume to 0dB
 */
void audio_proc_adc_volume_reset(void)
{
    audio_proc_adc_volume_set(0x07);
}

static uint32_t audio_proc_get_src_mode(uint32_t in_samp_rate, uint32_t out_samp_rate)
{
    int i = 0;
    bool found = false;

    uint32_t ratio = 0;

    ASSERT_ERR(in_samp_rate <= out_samp_rate);

    ratio = (uint32_t)(100000 * ((float)out_samp_rate / (float)in_samp_rate));

    for (i = 0; i < SRC_MODE_NB; i++) {
        if (ratio == dac_src_mode_ratio[i]) {
            dbg("dac_src mode:%d\n", i);
            found = true;
            break;
        }
    }

    if (found == false) {
        dbg("ERROR, DAC_SRC unsupported %d to %d\n", in_samp_rate, out_samp_rate);
        ASSERT_ERR(0);
    }

    return i;
}

//return audio src mode | audio src div
//bit[7:4] correspond to aud_src_ctrl2[7:4](audio_src_mode)
//bit[16:13] correspong to aud_src_ctrl2[16:13](audio_src_div)
static uint32_t audio_proc_get_aud_src_mode(uint32_t in_samp_rate, uint32_t out_samp_rate)
{
    int i = 0;
    int j = 0;
    uint32_t src_mode = 0;
    bool found = false;
    uint32_t ratio = 0;

    ratio = (uint32_t)(100000 * ((float)out_samp_rate / (float)in_samp_rate));

    for (i = 0; i < AUD_SRC_DIV_NB; i++) {
        if ((ratio > aud_src_mode_ratio[i][0]) || (ratio < aud_src_mode_ratio[i][SRC_MODE_NB - 1])) {
            continue;
        } else {
            for (j = 0; j < SRC_MODE_NB; j++) {
                if (ratio == aud_src_mode_ratio[i][j]) {
                    found = true;
                    break;
                }
            }
            if (found == true) {
                src_mode = (j << 4) | (aud_src_div[1][i] << 13);
                dbg("aud_src mode:%d div:%d\n", j, aud_src_div[0][i]);
                return src_mode;
            }
        }
    }

    if (found == false) {
        dbg("ERROR, AUD_SRC unsupported %d to %d\n", in_samp_rate, out_samp_rate);
        ASSERT_ERR(0);
    }

    return src_mode;
}

/*
 * src for playback
 */
void audio_proc_src_config(uint8_t en, uint8_t ch_num, uint8_t bits, uint32_t in_samp_rate, uint32_t out_samp_rate)
{
#if PLF_AIC8800
    uint8_t src_ch_en = 0x03;
    uint8_t src_mode = 8;
    uint32_t val;

    src_mode = audio_proc_get_src_mode(in_samp_rate, out_samp_rate);

    if (ch_num == AUD_CH_NUM_1) {
        src_ch_en = 0x01;
    }

    val = hwp_audProc->aud_proc_dac_cfg1;
    val &= ~(AUD_PROC_SRC_MODE(0xF) | AUD_PROC_SRC_CH_EN(0x03));
    val |= ((en? AUD_PROC_SRC_MODE(src_mode) : AUD_PROC_SRC_MODE(8)) | AUD_PROC_SRC_CH_EN(src_ch_en));
    hwp_audProc->aud_proc_dac_cfg1 = val;

    val = hwp_audProc->aud_proc_dac_cfg2;
    val &= ~(AUD_PROC_SRC_FLT_BYPASS(0x0F));
    val |= (en? AUD_PROC_SRC_FLT_BYPASS(0) : AUD_PROC_SRC_FLT_BYPASS(0x0F));
    hwp_audProc->aud_proc_dac_cfg2 = val;
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint8_t src_ch_en = 0x03;
    uint8_t src_mode = 8;
    uint32_t val;

    src_mode = audio_proc_get_src_mode(in_samp_rate, out_samp_rate);

    if (ch_num == AUD_CH_NUM_1) {
        src_ch_en = 0x01;
    }

    val = hwp_audProc->aud_proc_dac_cfg1;
    val &= ~(AUD_PROC_SRC_MODE(0xF) | AUD_PROC_SRC_CH_EN(0x03));
    val |= ((en? AUD_PROC_SRC_MODE(src_mode) : AUD_PROC_SRC_MODE(8)) | AUD_PROC_SRC_CH_EN(src_ch_en));
    hwp_audProc->aud_proc_dac_cfg1 = val;

    val = hwp_audProc->aud_proc_dac_cfg2;
    val &= ~(AUD_PROC_SRC_FLT_BYPASS(0x0F));
    val |= (en? AUD_PROC_SRC_FLT_BYPASS(0) : AUD_PROC_SRC_FLT_BYPASS(0x0F));
    hwp_audProc->aud_proc_dac_cfg2 = val;
#endif
}

/*
 * src for capture
 */
void audio_proc_aud_src_config(uint8_t en, uint8_t ch_num, uint8_t bits, uint32_t in_samp_rate, uint32_t out_samp_rate)
{
#if PLF_AIC8800
    uint8_t src_ch_en = 0x03;
    uint32_t src_mod_div = 0;
    uint32_t val;

    if (en) {
        val = AUD_PROC_AUD_SRC_ENABLE | AUD_PROC_AUD_SRC_TXRX_EN_CH_0 | AUD_PROC_AUD_SRC_AUTO_CLOCK_GATING_EN | AUD_PROC_AUD_SRC_ADC_IN_EN | AUD_PROC_AUD_SRC_TXRX_BURST_MODE | AUD_PROC_AUD_SRC_TX_BURST_MODE;
        if (ch_num == AUD_CH_NUM_2) {
            val |= AUD_PROC_AUD_SRC_TXRX_LR_FIFO_SHARE_EN | AUD_PROC_AUD_SRC_TX_LR_FIFO_SHARE_EN | AUD_PROC_AUD_SRC_TXRX_EN_CH_1;
        }
        if (bits == AUD_BITS_24) {
            val |= AUD_PROC_AUD_SRC_TXRX_MODE_CH | AUD_PROC_AUD_SRC_TX_MODE_CH;
        }
        hwp_audProc->aud_src_ctrl0 = val;

        src_mod_div = audio_proc_get_aud_src_mode(in_samp_rate, out_samp_rate);
        hwp_audProc->aud_src_ctrl2 = AUD_PROC_AUD_SRC_CH_EN(src_ch_en) | src_mod_div;
    } else {
        hwp_audProc->aud_src_ctrl2 &= ~(AUD_PROC_AUD_SRC_CH_EN(src_ch_en));
        hwp_audProc->aud_src_ctrl0 &= ~AUD_PROC_AUD_SRC_ENABLE;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint8_t src_ch_en = 0x03;
    uint32_t src_mod_div = 0;
    uint32_t val;

    if (en) {
        val = AUD_PROC_AUD_SRC_ENABLE | AUD_PROC_AUD_SRC_TXRX_EN_CH_0 | AUD_PROC_AUD_SRC_AUTO_CLOCK_GATING_EN | AUD_PROC_AUD_SRC_ADC_IN_EN | AUD_PROC_AUD_SRC_TXRX_BURST_MODE | AUD_PROC_AUD_SRC_TX_BURST_MODE;
        if (ch_num == AUD_CH_NUM_2) {
            val |= AUD_PROC_AUD_SRC_TXRX_LR_FIFO_SHARE_EN | AUD_PROC_AUD_SRC_TX_LR_FIFO_SHARE_EN | AUD_PROC_AUD_SRC_TXRX_EN_CH_1;
        }
        if (bits == AUD_BITS_24) {
            val |= AUD_PROC_AUD_SRC_TXRX_MODE_CH | AUD_PROC_AUD_SRC_TX_MODE_CH;
        }
        hwp_audProc->aud_src_ctrl0 = val;

        src_mod_div = audio_proc_get_aud_src_mode(in_samp_rate, out_samp_rate);
        hwp_audProc->aud_src_ctrl2 = AUD_PROC_AUD_SRC_CH_EN(src_ch_en) | src_mod_div;
    } else {
        hwp_audProc->aud_src_ctrl2 &= ~(AUD_PROC_AUD_SRC_CH_EN(src_ch_en));
        hwp_audProc->aud_src_ctrl0 &= ~AUD_PROC_AUD_SRC_ENABLE;
    }
#endif
}

void audio_proc_init(void)
{
#if PLF_AIC8800
    uint32_t val;

    /* high speed mode, auto clock gating enable, txrx burst mode, tx burst mode, rxtx burst mode, rx burst mode */
    val = hwp_audProc->aud_proc_cfg;
    hwp_audProc->aud_proc_cfg = val | AUD_PROC_HIGH_SPEED_MODE | AUD_PROC_AUTO_CLOCK_GATING_EN |
        AUD_PROC_TXRX_BURST_MODE | AUD_PROC_TX_BURST_MODE |
        AUD_PROC_RXTX_BURST_MODE | AUD_PROC_RX_BURST_MODE;
#elif PLF_AIC8800MC
    uint32_t val;

    val = hwp_audProc->aud_iis_cfg;
    hwp_audProc->aud_iis_cfg = val | AUD_PROC_AUTO_CLOCK_GATING_EN |
        AUD_PROC_TX_BURST_MODE |
        AUD_PROC_RX_BURST_MODE;
#elif PLF_AIC8800M40
    uint32_t val;

    /* high speed mode, auto clock gating enable, txrx burst mode, tx burst mode, rxtx burst mode, rx burst mode */
    val = hwp_audProc->aud_proc_cfg;
    hwp_audProc->aud_proc_cfg = val | AUD_PROC_HIGH_SPEED_MODE | AUD_PROC_AUTO_CLOCK_GATING_EN |
        AUD_PROC_TXRX_BURST_MODE | AUD_PROC_TX_BURST_MODE |
        AUD_PROC_RXTX_BURST_MODE | AUD_PROC_RX_BURST_MODE;
#endif
}

void audio_proc_i2s_mclk_config(void)
{
#if (PLF_AIC8800 && PLF_PMIC && !PLF_PMIC_VER_AUD && PLF_PMIC_MCLK && !PLF_EXT_AIC1000)
    // use aic1000Lite MCLK
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[4]),
        (AIC1000LITE_IOMUX_PAD_GPIO_SEL(0x6)),
        (AIC1000LITE_IOMUX_PAD_GPIO_SEL(0xF)));
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteSysctrl->TPORTS_SEL),
        (AIC1000LITE_SYS_CTRL_CFG_TOP_TPORTS_SEL(28) | AIC1000LITE_SYS_CTRL_CFG_CLK_TPORTS_SEL(10)),
        (AIC1000LITE_SYS_CTRL_CFG_TOP_TPORTS_SEL(0xFF) | AIC1000LITE_SYS_CTRL_CFG_CLK_TPORTS_SEL(0xF)));
    // usb_pll on
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteAnalogReg->por_ctrl),
        (AIC1000LITE_ANALOG_REG_CFG_RTC_USB_PLL_PU | AIC1000LITE_ANALOG_REG_CFG_RTC_USBPLL_CLK_EN),
        (AIC1000LITE_ANALOG_REG_CFG_RTC_USB_PLL_PU | AIC1000LITE_ANALOG_REG_CFG_RTC_USBPLL_CLK_EN));
    // usb_pll freq 12.288M * 16
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteAnalogReg->cfg_ana_usb_pll_ctrl),
        (AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_REF_MULTI2_EN | AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_NOTCH_EN |
        0 | AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_REG_VBIT(5) |
        AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_CP_IBIT(0x3) | 0 |
        AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_PU_BIT(0x3)),
        (AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_REF_MULTI2_EN | AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_NOTCH_EN |
        AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_BAND_SEL | AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_REG_VBIT(0xF) |
        AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_CP_IBIT(0x7) | AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_PFD_RST_DLY_BIT(0x7) |
        AIC1000LITE_ANALOG_REG_CFG_ANA_USBPLL_PU_BIT(0x3)));
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteAnalogReg->cfg_usb_pll_freq),
        (AIC1000LITE_ANALOG_REG_CFG_USBPLL_SDM_FREQ(0x1E3F549) | AIC1000LITE_ANALOG_REG_CFG_USBPLL_SDM_FREQ_UPDATE),
        (AIC1000LITE_ANALOG_REG_CFG_USBPLL_SDM_FREQ(0xFFFFFFF) | AIC1000LITE_ANALOG_REG_CFG_USBPLL_SDM_FREQ_UPDATE));
    // mclk divier 16
    PMIC_MEM_MASK_WRITE((unsigned int)(&aic1000liteSysctrl->mclk_div),
        (AIC1000LITE_SYS_CTRL_CFG_CLK_MCLK_DIV_DENOM(0x10) | AIC1000LITE_SYS_CTRL_CFG_CLK_MCLK_DIV_UPDATE),
        (AIC1000LITE_SYS_CTRL_CFG_CLK_MCLK_DIV_DENOM(0xFF) | AIC1000LITE_SYS_CTRL_CFG_CLK_MCLK_DIV_UPDATE));
#endif
#if (PLF_AIC8800M40 && PLF_HCLK_MCLK)
    /*
     * for MCLK 12288000, we can get accurate numerator with denominator 3125 under any supported HCLK
     * for MCLK 11289600, we can get accurate numerator with denominator 3125 under HCLK 240M, 120M and 80M
     */
    uint32_t numerator = 0;
    uint32_t denominator = 3125;
    uint32_t hclk = sysctrl_clock_get(SYS_HCLK);

    numerator = (uint32_t)((uint64_t)I2S_MCLK * denominator / hclk);

    AIC_AONSYSCTRL->pcm_clk_div = SYS_CTRL_CFG_TOP_PCM_CLK_DIV_DENOM(denominator) | SYS_CTRL_CFG_TOP_PCM_CLK_DIV_NUM(numerator) |
        SYS_CTRL_CFG_TOP_PCM_CLK_DIV_UPDATE | SYS_CTRL_CFG_TOP_PCM_CLK_SEL;
#endif
}

void audio_proc_i2s_mclk_iomux_config(void)
{
#if PLF_HW_ASIC
    //MCLK
    #if PLF_AIC8800
    iomux_gpio_config_sel_setf(15, 8);
    //iomux_gpio_config_sel_setf(4, 6);
    #elif PLF_AIC8800MC
    iomux_gpioa_config_sel_setf(13, 5);
    //iomux_gpioa_config_sel_setf(4, 4);
    #elif PLF_AIC8800M40
    #if !PLF_HCLK_MCLK
    iomux_gpioa_config_sel_setf(13, 8);
    //iomux_gpioa_config_sel_setf(4, 6);
    #endif
    #endif
#endif
}

void audio_proc_i2s0_iomux_config(void)
{
    uint8_t func_sel;

    #if PLF_AIC8800
    func_sel = 6;
    //LRCK
    iomux_gpio_config_sel_setf(0, func_sel);
    //BCK
    iomux_gpio_config_sel_setf(1, func_sel);
    //DIN
    iomux_gpio_config_sel_setf(2, func_sel);
    //DOUT
    iomux_gpio_config_sel_setf(3, func_sel);
    #elif PLF_AIC8800MC
    func_sel = 4;
    //LRCK
    iomux_gpioa_config_sel_setf(0, func_sel);
    //BCK
    iomux_gpioa_config_sel_setf(1, func_sel);
    //DIN
    iomux_gpioa_config_sel_setf(2, func_sel);
    //DOUT
    iomux_gpioa_config_sel_setf(3, func_sel);
    #elif PLF_AIC8800M40
    func_sel = 6;
    //LRCK
    iomux_gpioa_config_sel_setf(0, func_sel);
    //BCK
    iomux_gpioa_config_sel_setf(1, func_sel);
    //DIN
    iomux_gpioa_config_sel_setf(2, func_sel);
    //DOUT
    iomux_gpioa_config_sel_setf(3, func_sel);
    #endif
}

void audio_proc_i2s1_iomux_config(void)
{
    uint8_t func_sel;

    #if PLF_AIC8800
    func_sel = 8;
    //LRCK
    iomux_gpio_config_sel_setf(11, func_sel);
    //BCK
    iomux_gpio_config_sel_setf(10, func_sel);
    //DIN
    iomux_gpio_config_sel_setf(14, func_sel);
    //DOUT
    iomux_gpio_config_sel_setf(12, func_sel);
    #elif PLF_AIC8800MC
    func_sel = 5;
    //LRCK
    iomux_gpioa_config_sel_setf(11, func_sel);
    //BCK
    iomux_gpioa_config_sel_setf(10, func_sel);
    //DIN
    iomux_gpioa_config_sel_setf(12, func_sel);
    //DOUT
    iomux_gpioa_config_sel_setf(14, func_sel);
    #elif PLF_AIC8800M40
    func_sel = 8;
    //LRCK
    iomux_gpioa_config_sel_setf(11, func_sel);
    //BCK
    iomux_gpioa_config_sel_setf(10, func_sel);
    //DIN
    iomux_gpioa_config_sel_setf(12, func_sel);
    //DOUT
    iomux_gpioa_config_sel_setf(14, func_sel);
    #endif
}

void audio_proc_i2s0_config(AUD_I2S_CFG_T *cfg)
{
#if PLF_AIC8800
    uint8_t wlen = 0;
    uint8_t bck_per_lrck = 16 * 2;
    uint32_t mclk_div = 0;
    uint32_t i2s_cfg = 0;

    if (cfg->bits == AUD_BITS_16) {
        bck_per_lrck = (16 + cfg->bck_extend) * 2;
    } else if (cfg->bits == AUD_BITS_24) {
        wlen = 2;
        bck_per_lrck = (24 + cfg->bck_extend) * 2;
    }

    if (cfg->master) {
        mclk_div = I2S_MCLK / bck_per_lrck / cfg->samp_rate;
        AIC_CPUSYSCTRL->CMCLKDIV = (mclk_div << 0) | (0x01UL << 8);
    }

    if ((cfg->bits == AUD_BITS_16) && (cfg->bck_extend == 0)) {
        hwp_audProc->pcm_cfg_0 |= AUD_PROC_RX_BIT_MODE_0;
    }

    // only config I2S when it's not enabled
    if ((hwp_audProc->aud_intf_i2s_cfg0 & AUD_PROC_I2S_ENABLE_0) == 0) {
        if (cfg->format == AUD_I2S_FORMAT_I2S) {
            i2s_cfg = AUD_PROC_WLEN_0(wlen) | AUD_PROC_TX_HALF_CYCLE_DLY_0 | AUD_PROC_BCK_LRCK_0(cfg->bck_extend) | AUD_PROC_LRCK_POL_0;
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_RX_DLY_0(1) | AUD_PROC_MASTER_MODE_0;
            } else {
                i2s_cfg |= AUD_PROC_TX_DLY_S_0;
            }
        } else if (cfg->format == AUD_I2S_FORMAT_LEFT_JUSTIFIED) {
            i2s_cfg = AUD_PROC_WLEN_0(wlen) | AUD_PROC_BCK_LRCK_0(cfg->bck_extend) | AUD_PROC_LRCK_POL_0;
            if (cfg->master) {
                dbg("Error: AIC8800 I2S can not work as master with left-justified format\n");
                ASSERT_ERR(0);
            }
        } else {
            ASSERT_ERR(0);
        }
        hwp_audProc->aud_intf_i2s_cfg0 = i2s_cfg;

        if (cfg->master) {
            // I2S0 bck source select mclk divider
            AIC_CPUSYSCTRL->CBCLKSEL |= (0x01UL << 0);
        } else {
            // I2S0 bck source select pad i2s bck
            AIC_CPUSYSCTRL->CBCLKSEL &= ~(0x01UL << 0);
        }
    }
#elif PLF_AIC8800MC
    uint8_t wlen = 0;
    uint8_t bck_per_lrck = 16 * 2;
    uint32_t mclk_div = 0;
    uint32_t i2s_cfg = 0;

    if (cfg->bits == AUD_BITS_16) {
        bck_per_lrck = (16 + cfg->bck_extend) * 2;
    } else if (cfg->bits == AUD_BITS_24) {
        wlen = 2;
        bck_per_lrck = (24 + cfg->bck_extend) * 2;
    }

    if (cfg->master) {
        mclk_div = I2S_MCLK / bck_per_lrck / cfg->samp_rate;
        AIC_CPUSYSCTRL->codec_mclk_div = (mclk_div << 0) | (0x01UL << 8);
    }

    // only config I2S when it's not enabled
    if ((hwp_audProc->aud_intf_i2s_cfg0 & AUD_PROC_I2S_ENABLE_0) == 0) {
        if (cfg->format == AUD_I2S_FORMAT_I2S) {
            i2s_cfg = AUD_PROC_WLEN_0(wlen) | AUD_PROC_TX_DATA_HALF_CYCLE_DLY_0 | AUD_PROC_BCK_LRCK_0(cfg->bck_extend) | AUD_PROC_LRCK_POL_0;
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_0 | AUD_PROC_TX_DLY_0 | AUD_PROC_RX_DLY_0(1) | AUD_PROC_MASTER_MODE_0;
            } else {
                i2s_cfg |= AUD_PROC_TX_DLY_S_0;
            }
        } else if (cfg->format == AUD_I2S_FORMAT_LEFT_JUSTIFIED) {
            i2s_cfg = AUD_PROC_WLEN_0(wlen) | AUD_PROC_TX_DATA_HALF_CYCLE_DLY_0 | AUD_PROC_BCK_LRCK_0(cfg->bck_extend);
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_0 | AUD_PROC_MASTER_MODE_0;
            } else {
                i2s_cfg |= 0;
            }
        } else {
            ASSERT_ERR(0);
        }
        hwp_audProc->aud_intf_i2s_cfg0 = i2s_cfg;

        if (cfg->master) {
            // I2S0 bck source select mclk divider
            AIC_CPUSYSCTRL->bclk_sel |= (0x01UL << 0);
        } else {
            // I2S0 bck source select pad i2s bck
            AIC_CPUSYSCTRL->bclk_sel &= ~(0x01UL << 0);
        }
    }
#elif PLF_AIC8800M40
    uint8_t wlen = 0;
    uint8_t bck_per_lrck = 16 * 2;
    uint32_t mclk_div = 0;
    uint32_t i2s_cfg = 0;

    if (cfg->bits == AUD_BITS_16) {
        bck_per_lrck = (16 + cfg->bck_extend) * 2;
    } else if (cfg->bits == AUD_BITS_24) {
        wlen = 2;
        bck_per_lrck = (24 + cfg->bck_extend) * 2;
    }

    if (cfg->master) {
        mclk_div = I2S_MCLK / bck_per_lrck / cfg->samp_rate;
        AIC_CPUSYSCTRL->codec_mclk_div = (mclk_div << 0) | (0x01UL << 8);
    }

    // only config I2S when it's not enabled
    if ((hwp_audProc->aud_intf_i2s_cfg0 & AUD_PROC_I2S_ENABLE_0) == 0) {
        if (cfg->format == AUD_I2S_FORMAT_I2S) {
            i2s_cfg = AUD_PROC_WLEN_0(wlen) | AUD_PROC_TX_DATA_HALF_CYCLE_DLY_0 | AUD_PROC_BCK_LRCK_0(cfg->bck_extend) | AUD_PROC_LRCK_POL_0;
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_0 | AUD_PROC_TX_DLY_0 | AUD_PROC_RX_DLY_0(1) | AUD_PROC_MASTER_MODE_0;
            } else {
                i2s_cfg |= AUD_PROC_TX_DLY_S_0;
            }
        } else if (cfg->format == AUD_I2S_FORMAT_LEFT_JUSTIFIED) {
            i2s_cfg = AUD_PROC_WLEN_0(wlen) | AUD_PROC_TX_DATA_HALF_CYCLE_DLY_0 | AUD_PROC_BCK_LRCK_0(cfg->bck_extend);
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_0 | AUD_PROC_MASTER_MODE_0;
            } else {
                i2s_cfg |= 0;
            }
        } else {
            ASSERT_ERR(0);
        }
        hwp_audProc->aud_intf_i2s_cfg0 = i2s_cfg;

        if (cfg->master) {
            // I2S0 bck source select mclk divider
            AIC_CPUSYSCTRL->bclk_sel |= (0x01UL << 0);
        } else {
            // I2S0 bck source select pad i2s bck
            AIC_CPUSYSCTRL->bclk_sel &= ~(0x01UL << 0);
        }
    }
#endif
}

void audio_proc_i2s1_config(AUD_I2S_CFG_T *cfg)
{
#if PLF_AIC8800
    uint8_t wlen = 0;
    uint8_t bck_per_lrck = 16 * 2;
    uint32_t mclk_div = 0;
    uint32_t i2s_cfg = 0;

    if (cfg->bits == AUD_BITS_16) {
        bck_per_lrck = (16 + cfg->bck_extend) * 2;
    } else if (cfg->bits == AUD_BITS_24) {
        wlen = 2;
        bck_per_lrck = (24 + cfg->bck_extend) * 2;
    }

    if (cfg->master) {
        mclk_div = I2S_MCLK / bck_per_lrck / cfg->samp_rate;
        AIC_CPUSYSCTRL->CMCLKDIV = (mclk_div << 0) | (0x01UL << 8);
    }

    if ((cfg->bits == AUD_BITS_16) && (cfg->bck_extend == 0)) {
        hwp_audProc->pcm_cfg_1 |= AUD_PROC_RX_BIT_MODE_1;
    }

    // only config I2S when it's not enabled
    if ((hwp_audProc->aud_intf_i2s_cfg1 & AUD_PROC_I2S_ENABLE_1) == 0) {
        if (cfg->format == AUD_I2S_FORMAT_I2S) {
            i2s_cfg = AUD_PROC_WLEN_1(wlen) | AUD_PROC_TX_HALF_CYCLE_DLY_1 | AUD_PROC_BCK_LRCK_1(cfg->bck_extend) | AUD_PROC_LRCK_POL_1;
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_RX_DLY_1(1) | AUD_PROC_MASTER_MODE_1;
            } else {
                i2s_cfg |= AUD_PROC_TX_DLY_S_1;
            }
        } else if (cfg->format == AUD_I2S_FORMAT_LEFT_JUSTIFIED) {
            i2s_cfg = AUD_PROC_WLEN_1(wlen) | AUD_PROC_BCK_LRCK_1(cfg->bck_extend) | AUD_PROC_LRCK_POL_1;
            if (cfg->master) {
                dbg("Error: AIC8800 I2S can not work as master with left-justified format\n");
                ASSERT_ERR(0);
            }
        } else {
            ASSERT_ERR(0);
        }
        hwp_audProc->aud_intf_i2s_cfg1 = i2s_cfg;

        if (cfg->master) {
            // I2S1 bck source select mclk divider
            AIC_CPUSYSCTRL->CBCLKSEL |= (0x01UL << 2);
        } else {
            // I2S1 bck source select pad i2s bck
            AIC_CPUSYSCTRL->CBCLKSEL &= ~(0x01UL << 2);
        }
    }
#elif PLF_AIC8800MC
    uint8_t wlen = 0;
    uint8_t bck_per_lrck = 16 * 2;
    uint32_t mclk_div = 0;
    uint32_t i2s_cfg = 0;

    if (cfg->bits == AUD_BITS_16) {
        bck_per_lrck = (16 + cfg->bck_extend) * 2;
    } else if (cfg->bits == AUD_BITS_24) {
        wlen = 2;
        bck_per_lrck = (24 + cfg->bck_extend) * 2;
    }

    if (cfg->master) {
        mclk_div = I2S_MCLK / bck_per_lrck / cfg->samp_rate;
        AIC_CPUSYSCTRL->codec_mclk_div = (mclk_div << 0) | (0x01UL << 8);
    }

    // only config I2S when it's not enabled
    if ((hwp_audProc->aud_intf_i2s_cfg1 & AUD_PROC_I2S_ENABLE_1) == 0) {
        if (cfg->format == AUD_I2S_FORMAT_I2S) {
            i2s_cfg = AUD_PROC_WLEN_1(wlen) | AUD_PROC_TX_DATA_HALF_CYCLE_DLY_1 | AUD_PROC_BCK_LRCK_1(cfg->bck_extend) | AUD_PROC_LRCK_POL_1;
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_1 | AUD_PROC_TX_DLY_1 | AUD_PROC_RX_DLY_1(1) | AUD_PROC_MASTER_MODE_1;
            } else {
                i2s_cfg |= AUD_PROC_TX_DLY_S_1;
            }
        } else if (cfg->format == AUD_I2S_FORMAT_LEFT_JUSTIFIED) {
            i2s_cfg = AUD_PROC_WLEN_1(wlen) | AUD_PROC_TX_DATA_HALF_CYCLE_DLY_1 | AUD_PROC_BCK_LRCK_1(cfg->bck_extend);
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_1 | AUD_PROC_MASTER_MODE_1;
            } else {
                i2s_cfg |= 0;
            }
        } else {
            ASSERT_ERR(0);
        }
        hwp_audProc->aud_intf_i2s_cfg1 = i2s_cfg;

        if (cfg->master) {
            // I2S1 bck source select mclk divider
            AIC_CPUSYSCTRL->bclk_sel |= (0x01UL << 2);
        } else {
            // I2S1 bck source select pad i2s bck
            AIC_CPUSYSCTRL->bclk_sel &= ~(0x01UL << 2);
        }
    }
#elif PLF_AIC8800M40
    uint8_t wlen = 0;
    uint8_t bck_per_lrck = 16 * 2;
    uint32_t mclk_div = 0;
    uint32_t i2s_cfg = 0;

    if (cfg->bits == AUD_BITS_16) {
        bck_per_lrck = (16 + cfg->bck_extend) * 2;
    } else if (cfg->bits == AUD_BITS_24) {
        wlen = 2;
        bck_per_lrck = (24 + cfg->bck_extend) * 2;
    }

    if (cfg->master) {
        mclk_div = I2S_MCLK / bck_per_lrck / cfg->samp_rate;
        AIC_CPUSYSCTRL->codec_mclk_div = (mclk_div << 0) | (0x01UL << 8);
    }

    // only config I2S when it's not enabled
    if ((hwp_audProc->aud_intf_i2s_cfg1 & AUD_PROC_I2S_ENABLE_1) == 0) {
        if (cfg->format == AUD_I2S_FORMAT_I2S) {
            i2s_cfg = AUD_PROC_WLEN_1(wlen) | AUD_PROC_TX_DATA_HALF_CYCLE_DLY_1 | AUD_PROC_BCK_LRCK_1(cfg->bck_extend) | AUD_PROC_LRCK_POL_1;
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_1 | AUD_PROC_TX_DLY_1 | AUD_PROC_RX_DLY_1(1) | AUD_PROC_MASTER_MODE_1;
            } else {
                i2s_cfg |= AUD_PROC_TX_DLY_S_1;
            }
        } else if (cfg->format == AUD_I2S_FORMAT_LEFT_JUSTIFIED) {
            i2s_cfg = AUD_PROC_WLEN_1(wlen) | AUD_PROC_TX_DATA_HALF_CYCLE_DLY_1 | AUD_PROC_BCK_LRCK_1(cfg->bck_extend);
            if (cfg->master) {
                i2s_cfg |= AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_1 | AUD_PROC_MASTER_MODE_1;
            } else {
                i2s_cfg |= 0;
            }
        } else {
            ASSERT_ERR(0);
        }
        hwp_audProc->aud_intf_i2s_cfg1 = i2s_cfg;

        if (cfg->master) {
            // I2S1 bck source select mclk divider
            AIC_CPUSYSCTRL->bclk_sel |= (0x01UL << 2);
        } else {
            // I2S1 bck source select pad i2s bck
            AIC_CPUSYSCTRL->bclk_sel &= ~(0x01UL << 2);
        }
    }
#endif
}

