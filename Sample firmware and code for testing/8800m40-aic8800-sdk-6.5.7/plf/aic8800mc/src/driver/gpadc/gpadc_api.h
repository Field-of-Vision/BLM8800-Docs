#ifndef _GPADC_API_H_
#define _GPADC_API_H_

#include "plf.h"

enum {
    GPADC_SAMPLERATE_DFLT   = 0x02,
    GPADC_SAMPLERATE_HIGH   = 0x40,
    GPADC_SAMPLERATE_MID    = 0x80,
    GPADC_SAMPLERATE_LOW    = 0xF0,
};

/**
 * GPADC diff channel definitions:
 * +------+------+------+
 * | Idx  | Ch_p | Ch_n |
 * +------+------+------+
 * |  0   | gpb2 | gpb3 |
 * +------+------+------+
 * Default (that negflag equals 0) diff voltage value = (vol_p - vol_n)
 */
enum {
    GPADC_DIFF_CH_0 = 1,
};

enum {
    GPADC_DIFF_P2N,
    GPADC_DIFF_N2P
};

/**
 * @brief       Init gpadc func
 * @param[in]   Gpiob index
 */
void gpadc_init(int gpbidx);

/**
 * @brief       Free gpadc func
 * @param[in]   Gpiob index
 */
void gpadc_free(int gpbidx);

/**
 * @brief       Read voltage from gpiob pin
 * @param[in]   Gpiob index
 * @return      Voltage value, range: 0 ~ 1175mV
 */
int gpadc_read(int gpbidx);

/**
 * @brief       Init gpadc diff chan
 * @param[in]   Gpadc diff chan index
 */
void gpadc_diff_init();

/**
 * @brief       Free gpadc diff chan
 * @param[in]   Gpadc diff chan index
 */
void gpadc_diff_free();

/**
 * @brief       Read voltage from gpadc diff chan, both pin must connect voltage.
 * @param[in]   Negtive flag for diff chan, 0: (p - n), 1: (n - p)
 * @return      Voltage value, range: -1175 ~ 1175mV
 */
int gpadc_diff_read(int negflag);

#endif /* _GPADC_API_H_ */
