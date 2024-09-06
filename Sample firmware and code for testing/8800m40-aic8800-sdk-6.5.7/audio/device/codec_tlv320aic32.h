#ifndef _CODEC_TLV320AIC32_H_
#define _CODEC_TLV320AIC32_H_

#include <stdint.h>
#include <stdbool.h>
#include "audio_types.h"

typedef struct {
    AUD_BITS_T bits;
    AUD_CH_NUM_T ch_num;
    AUD_I2S_FORMAT_T format;
    bool codec_master;
    AUD_SAMPRATE_T samp_rate;
} tlv320aic32_cfg_t;

void tlv320aic32_i2c_init(void);
void tlv320aic32_reg_wr(unsigned char waddr,unsigned char wdata);
unsigned char tlv320aic32_reg_rd(unsigned char raddr);
void tlv320aic32_reset(void);
void tlv320aic32_init(void);
void tlv320aic32_config(tlv320aic32_cfg_t *cfg);
void tlv320aic32_deinit(void);

#endif /* _CODEC_TLV320AIC32_H_ */
