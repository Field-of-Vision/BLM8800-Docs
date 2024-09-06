#ifndef _AUDIO_PROC_API_H_
#define _AUDIO_PROC_API_H_

#include <stdint.h>
#include <stdbool.h>
#include "plf.h"
#include "aud_proc.h"

int audio_proc_dac_volume_set(uint8_t volume);
int audio_proc_adc_volume_set(uint8_t volume);
uint8_t audio_proc_dac_volume_get(void);
uint8_t audio_proc_adc_volume_get(void);
uint8_t audio_proc_dac_volume_convert_db_to_reg(float dB);
uint8_t audio_proc_adc_volume_convert_db_to_reg(int8_t dB);
uint8_t audio_proc_dac_volume_step_convert_db_to_reg(float dB);
uint8_t audio_proc_adc_volume_step_convert_db_to_reg(uint8_t dB);
bool audio_proc_dac_volume_up(uint8_t step);
bool audio_proc_dac_volume_down(uint8_t step);
bool audio_proc_adc_volume_up(uint8_t step);
bool audio_proc_adc_volume_down(uint8_t step);
void audio_proc_dac_volume_mute(void);
void audio_proc_adc_volume_mute(void);
void audio_proc_dac_volume_reset(void);
void audio_proc_adc_volume_reset(void);

void audio_proc_src_config(uint8_t en, uint8_t ch_num, uint8_t bits, uint32_t in_samp_rate, uint32_t out_samp_rate);
void audio_proc_aud_src_config(uint8_t en, uint8_t ch_num, uint8_t bits, uint32_t in_samp_rate, uint32_t out_samp_rate);

__STATIC_INLINE void audio_proc_src_clr_set(uint8_t clr)
{
#if PLF_AIC8800
    if (clr) {
        hwp_audProc->aud_proc_dac_cfg2 |= AUD_PROC_SRC_CLR;
    } else {
        hwp_audProc->aud_proc_dac_cfg2 &= ~AUD_PROC_SRC_CLR;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (clr) {
        hwp_audProc->aud_proc_dac_cfg2 |= AUD_PROC_SRC_CLR;
    } else {
        hwp_audProc->aud_proc_dac_cfg2 &= ~AUD_PROC_SRC_CLR;
    }
#endif
}

__STATIC_INLINE void audio_proc_aud_src_clr_set(uint8_t clr)
{
#if PLF_AIC8800
    if (clr) {
        hwp_audProc->aud_src_ctrl2 |= AUD_PROC_AUD_SRC_CLR;
    } else {
        hwp_audProc->aud_src_ctrl2 &= ~AUD_PROC_AUD_SRC_CLR;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (clr) {
        hwp_audProc->aud_src_ctrl2 |= AUD_PROC_AUD_SRC_CLR;
    } else {
        hwp_audProc->aud_src_ctrl2 &= ~AUD_PROC_AUD_SRC_CLR;
    }
#endif
}

__STATIC_INLINE void audio_proc_tx_mux_mode_l_set(uint8_t mode)
{
#if PLF_AIC8800
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~AUD_PROC_TX_MUX_MODE_L_MASK) | AUD_PROC_TX_MUX_MODE_L(mode);
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~AUD_PROC_TX_MUX_MODE_L_MASK) | AUD_PROC_TX_MUX_MODE_L(mode);
#endif
}

__STATIC_INLINE void audio_proc_tx_mux_mode_r_set(uint8_t mode)
{
#if PLF_AIC8800
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~AUD_PROC_TX_MUX_MODE_R_MASK) | AUD_PROC_TX_MUX_MODE_R(mode);
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~AUD_PROC_TX_MUX_MODE_R_MASK) | AUD_PROC_TX_MUX_MODE_R(mode);
#endif
}

__STATIC_INLINE void audio_proc_tx_mux_mode_set(uint8_t mode_l, uint8_t mode_r)
{
#if PLF_AIC8800
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~(AUD_PROC_TX_MUX_MODE_L_MASK | AUD_PROC_TX_MUX_MODE_R_MASK)) |
        AUD_PROC_TX_MUX_MODE_L(mode_l) | AUD_PROC_TX_MUX_MODE_R(mode_r);
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~(AUD_PROC_TX_MUX_MODE_L_MASK | AUD_PROC_TX_MUX_MODE_R_MASK)) |
        AUD_PROC_TX_MUX_MODE_L(mode_l) | AUD_PROC_TX_MUX_MODE_R(mode_r);
#endif
}

__STATIC_INLINE void audio_proc_rx_mux_mode_l_set(uint8_t mode)
{
#if PLF_AIC8800
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~AUD_PROC_RX_MUX_MODE_L_MASK) | AUD_PROC_RX_MUX_MODE_L(mode);
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~AUD_PROC_RX_MUX_MODE_L_MASK) | AUD_PROC_RX_MUX_MODE_L(mode);
#endif
}

__STATIC_INLINE void audio_proc_rx_mux_mode_r_set(uint8_t mode)
{
#if PLF_AIC8800
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~AUD_PROC_RX_MUX_MODE_R_MASK) | AUD_PROC_RX_MUX_MODE_R(mode);
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~AUD_PROC_RX_MUX_MODE_R_MASK) | AUD_PROC_RX_MUX_MODE_R(mode);
#endif
}

__STATIC_INLINE void audio_proc_rx_mux_mode_set(uint8_t mode_l, uint8_t mode_r)
{
#if PLF_AIC8800
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~(AUD_PROC_RX_MUX_MODE_L_MASK | AUD_PROC_RX_MUX_MODE_R_MASK)) |
        AUD_PROC_RX_MUX_MODE_L(mode_l) | AUD_PROC_RX_MUX_MODE_R(mode_r);
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg1;
    hwp_audProc->aud_proc_dac_cfg1 = (val & ~(AUD_PROC_RX_MUX_MODE_L_MASK | AUD_PROC_RX_MUX_MODE_R_MASK)) |
        AUD_PROC_RX_MUX_MODE_L(mode_l) | AUD_PROC_RX_MUX_MODE_R(mode_r);
#endif
}

__STATIC_INLINE void audio_proc_dac_mixer_mode_l_set(uint8_t mode)
{
#if PLF_AIC8800
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg2;
    hwp_audProc->aud_proc_dac_cfg2 = (val & ~AUD_PROC_DAC_MIXER_MODE_L_MASK) | AUD_PROC_DAC_MIXER_MODE_L(mode);
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg2;
    hwp_audProc->aud_proc_dac_cfg2 = (val & ~AUD_PROC_DAC_MIXER_MODE_L_MASK) | AUD_PROC_DAC_MIXER_MODE_L(mode);
#endif
}

__STATIC_INLINE void audio_proc_dac_mixer_mode_r_set(uint8_t mode)
{
#if PLF_AIC8800
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg2;
    hwp_audProc->aud_proc_dac_cfg2 = (val & ~AUD_PROC_DAC_MIXER_MODE_R_MASK) | AUD_PROC_DAC_MIXER_MODE_R(mode);
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg2;
    hwp_audProc->aud_proc_dac_cfg2 = (val & ~AUD_PROC_DAC_MIXER_MODE_R_MASK) | AUD_PROC_DAC_MIXER_MODE_R(mode);
#endif
}

__STATIC_INLINE void audio_proc_dac_mixer_mode_set(uint8_t mode_l, uint8_t mode_r)
{
#if PLF_AIC8800
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg2;
    hwp_audProc->aud_proc_dac_cfg2 = (val & ~(AUD_PROC_DAC_MIXER_MODE_L_MASK | AUD_PROC_DAC_MIXER_MODE_R_MASK)) |
        AUD_PROC_DAC_MIXER_MODE_L(mode_l) | AUD_PROC_DAC_MIXER_MODE_R(mode_r);
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    uint32_t val;
    val = hwp_audProc->aud_proc_dac_cfg2;
    hwp_audProc->aud_proc_dac_cfg2 = (val & ~(AUD_PROC_DAC_MIXER_MODE_L_MASK | AUD_PROC_DAC_MIXER_MODE_R_MASK)) |
        AUD_PROC_DAC_MIXER_MODE_L(mode_l) | AUD_PROC_DAC_MIXER_MODE_R(mode_r);
#endif
}

__STATIC_INLINE uint8_t audio_proc_dac_mixer_mode_l_get(void)
{
#if PLF_AIC8800
    return (hwp_audProc->aud_proc_dac_cfg2 & AUD_PROC_DAC_MIXER_MODE_L_MASK) >> AUD_PROC_DAC_MIXER_MODE_L_LSB;
#elif PLF_AIC8800MC
    return 0;
#elif PLF_AIC8800M40
    return (hwp_audProc->aud_proc_dac_cfg2 & AUD_PROC_DAC_MIXER_MODE_L_MASK) >> AUD_PROC_DAC_MIXER_MODE_L_LSB;
#endif
}

__STATIC_INLINE uint8_t audio_proc_dac_mixer_mode_r_get(void)
{
#if PLF_AIC8800
    return (hwp_audProc->aud_proc_dac_cfg2 & AUD_PROC_DAC_MIXER_MODE_R_MASK) >> AUD_PROC_DAC_MIXER_MODE_R_LSB;
#elif PLF_AIC8800MC
    return 0;
#elif PLF_AIC8800M40
    return (hwp_audProc->aud_proc_dac_cfg2 & AUD_PROC_DAC_MIXER_MODE_R_MASK) >> AUD_PROC_DAC_MIXER_MODE_R_LSB;
#endif
}

void audio_proc_init(void);

__STATIC_INLINE void audio_proc_aud_proc_enable_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_AUD_PROC_ENABLE;
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_AUD_PROC_ENABLE);
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_iis_cfg |= AUD_PROC_AUD_IIS_ENABLE;
    } else {
        hwp_audProc->aud_iis_cfg &= ~(AUD_PROC_AUD_IIS_ENABLE);
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_AUD_PROC_ENABLE;
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_AUD_PROC_ENABLE);
    }
#endif
}

__STATIC_INLINE void audio_proc_aud_proc_adc_path_reset_set(uint8_t reset)
{
#if PLF_AIC8800
    if (reset) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_AUD_PROC_ADC_PATH_RESET;
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_AUD_PROC_ADC_PATH_RESET);
    }
#elif PLF_AIC8800MC
    if (reset) {
        hwp_audProc->aud_iis_cfg |= AUD_PROC_AUD_IIS_ADC_PATH_RESET;
    } else {
        hwp_audProc->aud_iis_cfg &= ~(AUD_PROC_AUD_IIS_ADC_PATH_RESET);
    }
#elif PLF_AIC8800M40
    if (reset) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_AUD_PROC_ADC_PATH_RESET;
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_AUD_PROC_ADC_PATH_RESET);
    }
#endif
}

__STATIC_INLINE void audio_proc_aud_proc_dac_path_reset_set(uint8_t reset)
{
#if PLF_AIC8800
    if (reset) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_AUD_PROC_DAC_PATH_RESET;
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_AUD_PROC_DAC_PATH_RESET);
    }
#elif PLF_AIC8800MC
    if (reset) {
        hwp_audProc->aud_iis_cfg |= AUD_PROC_AUD_IIS_DAC_PATH_RESET;
    } else {
        hwp_audProc->aud_iis_cfg &= ~(AUD_PROC_AUD_IIS_DAC_PATH_RESET);
    }
#elif PLF_AIC8800M40
    if (reset) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_AUD_PROC_DAC_PATH_RESET;
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_AUD_PROC_DAC_PATH_RESET);
    }
#endif
}

/*
 * @brief set tx lr fifo share en
 *
 * @param idx, 0 for tx_ch01, 1 for tx_ch_23
 * @param en, 1 enable, 0 disable
 *
 */
__STATIC_INLINE void audio_proc_tx_lr_fifo_share_en_set(uint8_t idx, uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_TX_LR_FIFO_SHARE_EN(0x01 << idx);
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_TX_LR_FIFO_SHARE_EN(0x01 << idx));
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_iis_cfg |= AUD_PROC_TX_LR_FIFO_SHARE_EN(0x01 << idx);
    } else {
        hwp_audProc->aud_iis_cfg &= ~(AUD_PROC_TX_LR_FIFO_SHARE_EN(0x01 << idx));
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_TX_LR_FIFO_SHARE_EN(0x01 << idx);
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_TX_LR_FIFO_SHARE_EN(0x01 << idx));
    }
#endif
}

/*
 * @brief set rx lr fifo share en
 *
 * @param idx, 0 for rx_ch01, 1 for rx_ch_23
 * @param en, 1 enable, 0 disable
 *
 */
__STATIC_INLINE void audio_proc_rx_lr_fifo_share_en_set(uint8_t idx, uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_RX_LR_FIFO_SHARE_EN(0x01 << idx);
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_RX_LR_FIFO_SHARE_EN(0x01 << idx));
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_iis_cfg |= AUD_PROC_RX_LR_FIFO_SHARE_EN(0x01 << idx);
    } else {
        hwp_audProc->aud_iis_cfg &= ~(AUD_PROC_RX_LR_FIFO_SHARE_EN(0x01 << idx));
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_RX_LR_FIFO_SHARE_EN(0x01 << idx);
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_RX_LR_FIFO_SHARE_EN(0x01 << idx));
    }
#endif
}

/*
 * @brief set txrx lr fifo share en
 *
 * @param idx, not used, all txrx use one enable
 * @param en, 1 enable, 0 disable
 *
 */
__STATIC_INLINE void audio_proc_txrx_lr_fifo_share_en_set(uint8_t idx, uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_TXRX_LR_FIFO_SHARE_EN;
    } else {
        hwp_audProc->aud_proc_cfg &= ~AUD_PROC_TXRX_LR_FIFO_SHARE_EN;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_TXRX_LR_FIFO_SHARE_EN;
    } else {
        hwp_audProc->aud_proc_cfg &= ~AUD_PROC_TXRX_LR_FIFO_SHARE_EN;
    }
#endif
}

/*
 * @brief set rxtx lr fifo share en
 *
 * @param idx, 0 for rxtx_ch01, 1 for rxtx_ch_23
 * @param en, 1 enable, 0 disable
 *
 */
__STATIC_INLINE void audio_proc_rxtx_lr_fifo_share_en_set(uint8_t idx, uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_RXTX_LR_FIFO_SHARE_EN(0x01 << idx);
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_RXTX_LR_FIFO_SHARE_EN(0x01 << idx));
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_RXTX_LR_FIFO_SHARE_EN(0x01 << idx);
    } else {
        hwp_audProc->aud_proc_cfg &= ~(AUD_PROC_RXTX_LR_FIFO_SHARE_EN(0x01 << idx));
    }
#endif
}

__STATIC_INLINE void audio_proc_tx_en_ch_0_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_tx_cfg_ch0 |= AUD_PROC_TX_EN_CH_0;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch0 &= ~AUD_PROC_TX_EN_CH_0;
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_iis_tx_cfg_ch01 |= AUD_PROC_TX_EN_CH_01;
    } else {
        hwp_audProc->aud_iis_tx_cfg_ch01 &= ~AUD_PROC_TX_EN_CH_01;
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_tx_cfg_ch0 |= AUD_PROC_TX_EN_CH_0;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch0 &= ~AUD_PROC_TX_EN_CH_0;
    }
#endif
}

__STATIC_INLINE void audio_proc_tx_fifo_flush_ch_0_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_tx_cfg_ch0 |= AUD_PROC_TX_FIFO_FLUSH_CH_0;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch0 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_0;
    }
#elif PLF_AIC8800MC
    if (flush) {
        hwp_audProc->aud_iis_tx_cfg_ch01 |= AUD_PROC_TX_FIFO_FLUSH_CH_01;
    } else {
        hwp_audProc->aud_iis_tx_cfg_ch01 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_01;
    }
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_tx_cfg_ch0 |= AUD_PROC_TX_FIFO_FLUSH_CH_0;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch0 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_0;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode, 2: 32bits mode(8800mc/8800m40)
 */
__STATIC_INLINE void audio_proc_tx_mode_ch_0_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_tx_cfg_ch0 |= AUD_PROC_TX_MODE_CH_0;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch0 &= ~AUD_PROC_TX_MODE_CH_0;
    }
#elif PLF_AIC8800MC
    uint32_t val = hwp_audProc->aud_iis_tx_cfg_ch01;
    hwp_audProc->aud_iis_tx_cfg_ch01 = (val & ~AUD_PROC_TX_MODE_CH_01_MASK) | AUD_PROC_TX_MODE_CH_01(mode);
#elif PLF_AIC8800M40
    uint32_t val = hwp_audProc->aud_proc_tx_cfg_ch0;
    hwp_audProc->aud_proc_tx_cfg_ch0 = (val & ~AUD_PROC_TX_MODE_CH_01_MASK) | AUD_PROC_TX_MODE_CH_01(mode);
#endif
}

__STATIC_INLINE void audio_proc_tx_en_ch_1_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_tx_cfg_ch1 |= AUD_PROC_TX_EN_CH_1;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch1 &= ~AUD_PROC_TX_EN_CH_1;
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_iis_tx_cfg_ch01 |= AUD_PROC_TX_EN_CH_01;
    } else {
        hwp_audProc->aud_iis_tx_cfg_ch01 &= ~AUD_PROC_TX_EN_CH_01;
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_tx_cfg_ch1 |= AUD_PROC_TX_EN_CH_1;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch1 &= ~AUD_PROC_TX_EN_CH_1;
    }
#endif
}

__STATIC_INLINE void audio_proc_tx_fifo_flush_ch_1_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_tx_cfg_ch1 |= AUD_PROC_TX_FIFO_FLUSH_CH_1;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch1 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_1;
    }
#elif PLF_AIC8800MC
    if (flush) {
        hwp_audProc->aud_iis_tx_cfg_ch01 |= AUD_PROC_TX_FIFO_FLUSH_CH_01;
    } else {
        hwp_audProc->aud_iis_tx_cfg_ch01 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_01;
    }
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_tx_cfg_ch1 |= AUD_PROC_TX_FIFO_FLUSH_CH_1;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch1 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_1;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode, 2: 32bits mode(8800mc/8800m40)
 */
__STATIC_INLINE void audio_proc_tx_mode_ch_1_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_tx_cfg_ch1 |= AUD_PROC_TX_MODE_CH_1;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch1 &= ~AUD_PROC_TX_MODE_CH_1;
    }
#elif PLF_AIC8800MC
    uint32_t val = hwp_audProc->aud_iis_tx_cfg_ch01;
    hwp_audProc->aud_iis_tx_cfg_ch01 = (val & ~AUD_PROC_TX_MODE_CH_01_MASK) | AUD_PROC_TX_MODE_CH_01(mode);
#elif PLF_AIC8800M40
    uint32_t val = hwp_audProc->aud_proc_tx_cfg_ch0;
    hwp_audProc->aud_proc_tx_cfg_ch0 = (val & ~AUD_PROC_TX_MODE_CH_01_MASK) | AUD_PROC_TX_MODE_CH_01(mode);
#endif
}

__STATIC_INLINE void audio_proc_tx_en_ch_2_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_tx_cfg_ch2 |= AUD_PROC_TX_EN_CH_2;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch2 &= ~AUD_PROC_TX_EN_CH_2;
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_iis_tx_cfg_ch23 |= AUD_PROC_TX_EN_CH_23;
    } else {
        hwp_audProc->aud_iis_tx_cfg_ch23 &= ~AUD_PROC_TX_EN_CH_23;
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_tx_cfg_ch2 |= AUD_PROC_TX_EN_CH_2;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch2 &= ~AUD_PROC_TX_EN_CH_2;
    }
#endif
}

__STATIC_INLINE void audio_proc_tx_fifo_flush_ch_2_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_tx_cfg_ch2 |= AUD_PROC_TX_FIFO_FLUSH_CH_2;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch2 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_2;
    }
#elif PLF_AIC8800MC
    if (flush) {
        hwp_audProc->aud_iis_tx_cfg_ch23 |= AUD_PROC_TX_FIFO_FLUSH_CH_23;
    } else {
        hwp_audProc->aud_iis_tx_cfg_ch23 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_23;
    }
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_tx_cfg_ch2 |= AUD_PROC_TX_FIFO_FLUSH_CH_2;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch2 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_2;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode, 2: 32bits mode(8800mc/8800m40)
 */
__STATIC_INLINE void audio_proc_tx_mode_ch_2_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_tx_cfg_ch2 |= AUD_PROC_TX_MODE_CH_2;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch2 &= ~AUD_PROC_TX_MODE_CH_2;
    }
#elif PLF_AIC8800MC
    uint32_t val = hwp_audProc->aud_iis_tx_cfg_ch23;
    hwp_audProc->aud_iis_tx_cfg_ch23 = (val & ~AUD_PROC_TX_MODE_CH_23_MASK) | AUD_PROC_TX_MODE_CH_23(mode);
#elif PLF_AIC8800M40
    uint32_t val = hwp_audProc->aud_proc_tx_cfg_ch2;
    hwp_audProc->aud_proc_tx_cfg_ch2 = (val & ~AUD_PROC_TX_MODE_CH_23_MASK) | AUD_PROC_TX_MODE_CH_23(mode);
#endif
}

__STATIC_INLINE void audio_proc_tx_en_ch_3_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_tx_cfg_ch3 |= AUD_PROC_TX_EN_CH_3;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch3 &= ~AUD_PROC_TX_EN_CH_3;
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_iis_tx_cfg_ch23 |= AUD_PROC_TX_EN_CH_23;
    } else {
        hwp_audProc->aud_iis_tx_cfg_ch23 &= ~AUD_PROC_TX_EN_CH_23;
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_tx_cfg_ch3 |= AUD_PROC_TX_EN_CH_3;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch3 &= ~AUD_PROC_TX_EN_CH_3;
    }
#endif
}

__STATIC_INLINE void audio_proc_tx_fifo_flush_ch_3_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_tx_cfg_ch3 |= AUD_PROC_TX_FIFO_FLUSH_CH_3;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch3 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_3;
    }
#elif PLF_AIC8800MC
    if (flush) {
        hwp_audProc->aud_iis_tx_cfg_ch23 |= AUD_PROC_TX_FIFO_FLUSH_CH_23;
    } else {
        hwp_audProc->aud_iis_tx_cfg_ch23 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_23;
    }
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_tx_cfg_ch3 |= AUD_PROC_TX_FIFO_FLUSH_CH_3;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch3 &= ~AUD_PROC_TX_FIFO_FLUSH_CH_3;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode, 2: 32bits mode(8800mc/8800m40)
 */
__STATIC_INLINE void audio_proc_tx_mode_ch_3_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_tx_cfg_ch3 |= AUD_PROC_TX_MODE_CH_3;
    } else {
        hwp_audProc->aud_proc_tx_cfg_ch3 &= ~AUD_PROC_TX_MODE_CH_3;
    }
#elif PLF_AIC8800MC
    uint32_t val = hwp_audProc->aud_iis_tx_cfg_ch23;
    hwp_audProc->aud_iis_tx_cfg_ch23 = (val & ~AUD_PROC_TX_MODE_CH_23_MASK) | AUD_PROC_TX_MODE_CH_23(mode);
#elif PLF_AIC8800M40
    uint32_t val = hwp_audProc->aud_proc_tx_cfg_ch2;
    hwp_audProc->aud_proc_tx_cfg_ch2 = (val & ~AUD_PROC_TX_MODE_CH_23_MASK) | AUD_PROC_TX_MODE_CH_23(mode);
#endif
}

__STATIC_INLINE void audio_proc_rx_en_ch_01_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_rx_cfg_ch01 |= AUD_PROC_RX_EN_CH_0;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch01 &= ~AUD_PROC_RX_EN_CH_0;
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_iis_rx_cfg_ch01 |= AUD_PROC_RX_EN_CH_01;
    } else {
        hwp_audProc->aud_iis_rx_cfg_ch01 &= ~AUD_PROC_RX_EN_CH_01;
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_rx_cfg_ch01 |= AUD_PROC_RX_EN_CH_0;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch01 &= ~AUD_PROC_RX_EN_CH_0;
    }
#endif
}

__STATIC_INLINE void audio_proc_rx_fifo_flush_ch_01_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_rx_cfg_ch01 |= AUD_PROC_RX_FIFO_FLUSH_CH_01;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch01 &= ~AUD_PROC_RX_FIFO_FLUSH_CH_01;
    }
#elif PLF_AIC8800MC
    if (flush) {
        hwp_audProc->aud_iis_rx_cfg_ch01 |= AUD_PROC_RX_FIFO_FLUSH_CH_01;
    } else {
        hwp_audProc->aud_iis_rx_cfg_ch01 &= ~AUD_PROC_RX_FIFO_FLUSH_CH_01;
    }
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_rx_cfg_ch01 |= AUD_PROC_RX_FIFO_FLUSH_CH_01;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch01 &= ~AUD_PROC_RX_FIFO_FLUSH_CH_01;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode, 2: 32bits mode(8800mc/8800m40)
 */
__STATIC_INLINE void audio_proc_rx_mode_ch_01_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_rx_cfg_ch01 |= AUD_PROC_RX_MODE_CH_01;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch01 &= ~AUD_PROC_RX_MODE_CH_01;
    }
#elif PLF_AIC8800MC
    uint32_t val = hwp_audProc->aud_iis_rx_cfg_ch01;
    hwp_audProc->aud_iis_rx_cfg_ch01 = (val & ~AUD_PROC_RX_MODE_CH_01_MASK) | AUD_PROC_RX_MODE_CH_01(mode);
#elif PLF_AIC8800M40
    uint32_t val = hwp_audProc->aud_proc_rx_cfg_ch01;
    hwp_audProc->aud_proc_rx_cfg_ch01 = (val & ~AUD_PROC_RX_MODE_CH_01_MASK) | AUD_PROC_RX_MODE_CH_01(mode);
#endif
}

__STATIC_INLINE void audio_proc_rx_en_ch_23_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_rx_cfg_ch23 |= AUD_PROC_RX_EN_CH_2;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch23 &= ~AUD_PROC_RX_EN_CH_2;
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_iis_rx_cfg_ch23 |= AUD_PROC_RX_EN_CH_23;
    } else {
        hwp_audProc->aud_iis_rx_cfg_ch23 &= ~AUD_PROC_RX_EN_CH_23;
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_rx_cfg_ch23 |= AUD_PROC_RX_EN_CH_2;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch23 &= ~AUD_PROC_RX_EN_CH_2;
    }
#endif
}

__STATIC_INLINE void audio_proc_rx_fifo_flush_ch_23_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_rx_cfg_ch23 |= AUD_PROC_RX_FIFO_FLUSH_CH_23;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch23 &= ~AUD_PROC_RX_FIFO_FLUSH_CH_23;
    }
#elif PLF_AIC8800MC
    if (flush) {
        hwp_audProc->aud_iis_rx_cfg_ch23 |= AUD_PROC_RX_FIFO_FLUSH_CH_23;
    } else {
        hwp_audProc->aud_iis_rx_cfg_ch23 &= ~AUD_PROC_RX_FIFO_FLUSH_CH_23;
    }
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_rx_cfg_ch23 |= AUD_PROC_RX_FIFO_FLUSH_CH_23;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch23 &= ~AUD_PROC_RX_FIFO_FLUSH_CH_23;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode, 2: 32bits mode(8800mc/8800m40)
 */
__STATIC_INLINE void audio_proc_rx_mode_ch_23_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_rx_cfg_ch23 |= AUD_PROC_RX_MODE_CH_23;
    } else {
        hwp_audProc->aud_proc_rx_cfg_ch23 &= ~AUD_PROC_RX_MODE_CH_23;
    }
#elif PLF_AIC8800MC
    uint32_t val = hwp_audProc->aud_iis_rx_cfg_ch23;
    hwp_audProc->aud_iis_rx_cfg_ch23 = (val & ~AUD_PROC_RX_MODE_CH_23_MASK) | AUD_PROC_RX_MODE_CH_23(mode);
#elif PLF_AIC8800M40
    uint32_t val = hwp_audProc->aud_proc_rx_cfg_ch23;
    hwp_audProc->aud_proc_rx_cfg_ch23 = (val & ~AUD_PROC_RX_MODE_CH_23_MASK) | AUD_PROC_RX_MODE_CH_23(mode);
#endif
}

__STATIC_INLINE void audio_proc_txrx_en_ch_0_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_txrx_cfg_ch0 |= AUD_PROC_TXRX_EN_CH_0;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch0 &= ~AUD_PROC_TXRX_EN_CH_0;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_txrx_cfg_ch0 |= AUD_PROC_TXRX_EN_CH_0;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch0 &= ~AUD_PROC_TXRX_EN_CH_0;
    }
#endif
}

__STATIC_INLINE void audio_proc_txrx_fifo_flush_ch_0_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_txrx_cfg_ch0 |= AUD_PROC_TXRX_FIFO_FLUSH_CH_0;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch0 &= ~AUD_PROC_TXRX_FIFO_FLUSH_CH_0;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_txrx_cfg_ch0 |= AUD_PROC_TXRX_FIFO_FLUSH_CH_0;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch0 &= ~AUD_PROC_TXRX_FIFO_FLUSH_CH_0;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode
 */
__STATIC_INLINE void audio_proc_txrx_mode_ch_0_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_txrx_cfg_ch0 |= AUD_PROC_TXRX_MODE_CH_0;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch0 &= ~AUD_PROC_TXRX_MODE_CH_0;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (mode) {
        hwp_audProc->aud_proc_txrx_cfg_ch0 |= AUD_PROC_TXRX_MODE_CH_0;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch0 &= ~AUD_PROC_TXRX_MODE_CH_0;
    }
#endif
}

__STATIC_INLINE void audio_proc_txrx_en_ch_1_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_txrx_cfg_ch1 |= AUD_PROC_TXRX_EN_CH_1;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch1 &= ~AUD_PROC_TXRX_EN_CH_1;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_txrx_cfg_ch1 |= AUD_PROC_TXRX_EN_CH_1;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch1 &= ~AUD_PROC_TXRX_EN_CH_1;
    }
#endif
}

__STATIC_INLINE void audio_proc_txrx_fifo_flush_ch_1_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_txrx_cfg_ch1 |= AUD_PROC_TXRX_FIFO_FLUSH_CH_1;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch1 &= ~AUD_PROC_TXRX_FIFO_FLUSH_CH_1;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_txrx_cfg_ch1 |= AUD_PROC_TXRX_FIFO_FLUSH_CH_1;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch1 &= ~AUD_PROC_TXRX_FIFO_FLUSH_CH_1;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode
 */
__STATIC_INLINE void audio_proc_txrx_mode_ch_1_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_txrx_cfg_ch1 |= AUD_PROC_TXRX_MODE_CH_1;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch1 &= ~AUD_PROC_TXRX_MODE_CH_1;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (mode) {
        hwp_audProc->aud_proc_txrx_cfg_ch1 |= AUD_PROC_TXRX_MODE_CH_1;
    } else {
        hwp_audProc->aud_proc_txrx_cfg_ch1 &= ~AUD_PROC_TXRX_MODE_CH_1;
    }
#endif
}

__STATIC_INLINE void audio_proc_rxtx_en_ch_0_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 |= AUD_PROC_RXTX_EN_CH_0;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 &= ~AUD_PROC_RXTX_EN_CH_0;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 |= AUD_PROC_RXTX_EN_CH_0;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 &= ~AUD_PROC_RXTX_EN_CH_0;
    }
#endif
}

__STATIC_INLINE void audio_proc_rxtx_fifo_flush_ch_0_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 |= AUD_PROC_RXTX_FIFO_FLUSH_CH_0;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 &= ~AUD_PROC_RXTX_FIFO_FLUSH_CH_0;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 |= AUD_PROC_RXTX_FIFO_FLUSH_CH_0;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 &= ~AUD_PROC_RXTX_FIFO_FLUSH_CH_0;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode
 */
__STATIC_INLINE void audio_proc_rxtx_mode_ch_0_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 |= AUD_PROC_RXTX_MODE_CH_0;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 &= ~AUD_PROC_RXTX_MODE_CH_0;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (mode) {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 |= AUD_PROC_RXTX_MODE_CH_0;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch0 &= ~AUD_PROC_RXTX_MODE_CH_0;
    }
#endif
}

__STATIC_INLINE void audio_proc_rxtx_en_ch_1_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 |= AUD_PROC_RXTX_EN_CH_1;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 &= ~AUD_PROC_RXTX_EN_CH_1;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 |= AUD_PROC_RXTX_EN_CH_1;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 &= ~AUD_PROC_RXTX_EN_CH_1;
    }
#endif
}

__STATIC_INLINE void audio_proc_rxtx_fifo_flush_ch_1_set(uint8_t flush)
{
#if PLF_AIC8800
    if (flush) {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 |= AUD_PROC_RXTX_FIFO_FLUSH_CH_1;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 &= ~AUD_PROC_RXTX_FIFO_FLUSH_CH_1;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (flush) {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 |= AUD_PROC_RXTX_FIFO_FLUSH_CH_1;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 &= ~AUD_PROC_RXTX_FIFO_FLUSH_CH_1;
    }
#endif
}

/*
 * @param mode, 0: 16bits mode, 1: 24bits mode
 */
__STATIC_INLINE void audio_proc_rxtx_mode_ch_1_set(uint8_t mode)
{
#if PLF_AIC8800
    if (mode) {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 |= AUD_PROC_RXTX_MODE_CH_1;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 &= ~AUD_PROC_RXTX_MODE_CH_1;
    }
#elif PLF_AIC8800MC
    //TODO
#elif PLF_AIC8800M40
    if (mode) {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 |= AUD_PROC_RXTX_MODE_CH_1;
    } else {
        hwp_audProc->aud_proc_rxtx_cfg_ch1 &= ~AUD_PROC_RXTX_MODE_CH_1;
    }
#endif
}

void audio_proc_i2s_mclk_config(void);
void audio_proc_i2s_mclk_iomux_config(void);
void audio_proc_i2s0_iomux_config(void);
void audio_proc_i2s1_iomux_config(void);
void audio_proc_i2s0_config(AUD_I2S_CFG_T *cfg);
void audio_proc_i2s1_config(AUD_I2S_CFG_T *cfg);

__STATIC_INLINE void audio_proc_i2s_chn_out_sel_set(uint8_t sel)
{
#if PLF_AIC8800
    if (sel) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_I2S_CHN_OUT_SEL;
    } else {
        hwp_audProc->aud_proc_cfg &= ~AUD_PROC_I2S_CHN_OUT_SEL;
    }
#elif PLF_AIC8800MC
    if (sel) {
        hwp_audProc->pcm_cfg_0 |= AUD_PROC_I2S_CHN_OUT_SEL;
    } else {
        hwp_audProc->pcm_cfg_0 &= ~AUD_PROC_I2S_CHN_OUT_SEL;
    }
#elif PLF_AIC8800M40
    if (sel) {
        hwp_audProc->pcm_cfg_0 |= AUD_PROC_I2S_CHN_OUT_SEL;
    } else {
        hwp_audProc->pcm_cfg_0 &= ~AUD_PROC_I2S_CHN_OUT_SEL;
    }
#endif
}

__STATIC_INLINE uint8_t audio_proc_i2s_chn_out_sel_get(void)
{
#if PLF_AIC8800
    return (hwp_audProc->aud_proc_cfg & AUD_PROC_I2S_CHN_OUT_SEL) >> AUD_PROC_I2S_CHN_OUT_SEL_POS;
#elif PLF_AIC8800MC
    return (hwp_audProc->pcm_cfg_0 & AUD_PROC_I2S_CHN_OUT_SEL) >> AUD_PROC_I2S_CHN_OUT_SEL_POS;
#elif PLF_AIC8800M40
    return (hwp_audProc->pcm_cfg_0 & AUD_PROC_I2S_CHN_OUT_SEL) >> AUD_PROC_I2S_CHN_OUT_SEL_POS;
#endif
}

__STATIC_INLINE void audio_proc_i2s_chn_in_sel_set(uint8_t sel)
{
#if PLF_AIC8800
    if (sel) {
        hwp_audProc->aud_proc_cfg |= AUD_PROC_I2S_CHN_IN_SEL;
    } else {
        hwp_audProc->aud_proc_cfg &= ~AUD_PROC_I2S_CHN_IN_SEL;
    }
#elif PLF_AIC8800MC
    if (sel) {
        hwp_audProc->pcm_cfg_0 |= AUD_PROC_I2S_CHN_IN_SEL;
    } else {
        hwp_audProc->pcm_cfg_0 &= ~AUD_PROC_I2S_CHN_IN_SEL;
    }
#elif PLF_AIC8800M40
    if (sel) {
        hwp_audProc->pcm_cfg_0 |= AUD_PROC_I2S_CHN_IN_SEL;
    } else {
        hwp_audProc->pcm_cfg_0 &= ~AUD_PROC_I2S_CHN_IN_SEL;
    }
#endif
}

__STATIC_INLINE uint8_t audio_proc_i2s_chn_in_sel_get(void)
{
#if PLF_AIC8800
    return (hwp_audProc->aud_proc_cfg & AUD_PROC_I2S_CHN_IN_SEL) >> AUD_PROC_I2S_CHN_IN_SEL_POS;
#elif PLF_AIC8800MC
    return (hwp_audProc->pcm_cfg_0 & AUD_PROC_I2S_CHN_IN_SEL) >> AUD_PROC_I2S_CHN_IN_SEL_POS;
#elif PLF_AIC8800M40
    return (hwp_audProc->pcm_cfg_0 & AUD_PROC_I2S_CHN_IN_SEL) >> AUD_PROC_I2S_CHN_IN_SEL_POS;
#endif
}

__STATIC_INLINE void audio_proc_i2s0_enable_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_intf_i2s_cfg0 |= AUD_PROC_I2S_ENABLE_0;
    } else {
        hwp_audProc->aud_intf_i2s_cfg0 &= ~AUD_PROC_I2S_ENABLE_0;
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_intf_i2s_cfg0 |= AUD_PROC_I2S_ENABLE_0;
    } else {
        hwp_audProc->aud_intf_i2s_cfg0 &= ~AUD_PROC_I2S_ENABLE_0;
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_intf_i2s_cfg0 |= AUD_PROC_I2S_ENABLE_0;
    } else {
        hwp_audProc->aud_intf_i2s_cfg0 &= ~AUD_PROC_I2S_ENABLE_0;
    }
#endif
}

__STATIC_INLINE uint8_t audio_proc_i2s0_enable_get(uint8_t en)
{
#if PLF_AIC8800
    return (hwp_audProc->aud_intf_i2s_cfg0 & AUD_PROC_I2S_ENABLE_0) >> AUD_PROC_I2S_ENABLE_0_POS;
#elif PLF_AIC8800MC
    return (hwp_audProc->aud_intf_i2s_cfg0 & AUD_PROC_I2S_ENABLE_0) >> AUD_PROC_I2S_ENABLE_0_POS;
#elif PLF_AIC8800M40
    return (hwp_audProc->aud_intf_i2s_cfg0 & AUD_PROC_I2S_ENABLE_0) >> AUD_PROC_I2S_ENABLE_0_POS;
#endif
}

__STATIC_INLINE void audio_proc_i2s1_enable_set(uint8_t en)
{
#if PLF_AIC8800
    if (en) {
        hwp_audProc->aud_intf_i2s_cfg1 |= AUD_PROC_I2S_ENABLE_1;
    } else {
        hwp_audProc->aud_intf_i2s_cfg1 &= ~AUD_PROC_I2S_ENABLE_1;
    }
#elif PLF_AIC8800MC
    if (en) {
        hwp_audProc->aud_intf_i2s_cfg1 |= AUD_PROC_I2S_ENABLE_1;
    } else {
        hwp_audProc->aud_intf_i2s_cfg1 &= ~AUD_PROC_I2S_ENABLE_1;
    }
#elif PLF_AIC8800M40
    if (en) {
        hwp_audProc->aud_intf_i2s_cfg1 |= AUD_PROC_I2S_ENABLE_1;
    } else {
        hwp_audProc->aud_intf_i2s_cfg1 &= ~AUD_PROC_I2S_ENABLE_1;
    }
#endif
}

__STATIC_INLINE uint8_t audio_proc_i2s1_enable_get(uint8_t en)
{
#if PLF_AIC8800
    return (hwp_audProc->aud_intf_i2s_cfg1 & AUD_PROC_I2S_ENABLE_1) >> AUD_PROC_I2S_ENABLE_1_POS;
#elif PLF_AIC8800MC
    return (hwp_audProc->aud_intf_i2s_cfg1 & AUD_PROC_I2S_ENABLE_1) >> AUD_PROC_I2S_ENABLE_1_POS;
#elif PLF_AIC8800M40
    return (hwp_audProc->aud_intf_i2s_cfg1 & AUD_PROC_I2S_ENABLE_1) >> AUD_PROC_I2S_ENABLE_1_POS;
#endif
}

#endif
