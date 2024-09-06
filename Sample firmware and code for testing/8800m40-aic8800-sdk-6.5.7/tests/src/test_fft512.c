/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
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
#include "dma_api.h"
#include "trans_api.h"
#include "arm_common_tables.h"
#include "dbg.h"
#include <stdlib.h>

#if CFG_TEST_FFT512

/*
 * MACROS
 ****************************************************************************************
 */
#define FFT_TEST
#define UART_PRINT              dbg

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
dma_trans_t dma_trans_obj = {0};

fft_state_t fft_obj;

//static uint32_t fft_result[512];
static int16_t fft_result[1024];

/*
 * FUNCTIONS
 ****************************************************************************************
 */

 /**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */

void fft512_test(void)
{
    const int ch = DMA_CHANNEL_CYPT_IDX1;
    uint32_t i,j;
    int16_t      inputQ15[512*2];

    dbg("fft 512_test start\n");
        dma_trans_obj.fft_dir = FFT_DIR;
    //    dma_trans_obj.fft_dir = IFFT_DIR;

    // DMA init
    dma_init();
    dma_trans_obj.trans_chn = ch;
    dma_trans_obj.dma_trans_mode = FFT_MODE;
    dma_trans_obj.fft_len = FFT512_MODE;
    dma_trans_obj.fft_scale = 0;
    dma_trans_obj.fft_in_format_sel = FFT_IN_13B_LOW;
    dma_trans_obj.fft_out_format_sel = FFT_OUT_13B_LOW;

    for(j=0;j<10;j++){
        for (i = 0u; i < APP_FFT_LEN_512; i++)
        {
            inputQ15[2*i  ] = rand() % 0x2000; /* real part. 14 bit*/
            inputQ15[2*i+1] = rand() % 0x2000; /* complex part. 14 bit*/
        }
        fft_obj.fft_data = (uint32_t *)inputQ15;
        fft_obj.length_byte = sizeof(inputQ15);
        dma_trans_init(&dma_trans_obj);
        fft_calc(&dma_trans_obj, &fft_obj, (uint32_t *)fft_result);
#if 0
        dbg("HW Output :\r\n");
        for (i = 0u; i < APP_FFT_LEN_512; i++)
        {
            if(i%4 == 3) {
                dbg("%d: R: %d I: %d\n\r", i, fft_result[2*i], fft_result[2*i+1]);
            } else {
                dbg("%d: R: %d I: %d \t", i, fft_result[2*i], fft_result[2*i+1]);
            }
        }
#endif
        arm_cfft_q15(&arm_cfft_sR_q15_len512, inputQ15, 0, 1);
#if 0
        dbg("SW Output :\r\n");
        for (i = 0u; i < APP_FFT_LEN_512; i++)
        {
            if(i%4 == 3) {
                dbg("%d: R: %d, I %d\n\r", i, inputQ15[2*i], inputQ15[2*i+1]);
            } else {
                dbg("%d: R: %d, I %d \t", i, inputQ15[2*i], inputQ15[2*i+1]);
            }
        }
#endif
        for(i = 0u; i < APP_FFT_LEN_512; i++) {
            if((fft_result[2*i] - inputQ15[2*i] > 8) || (fft_result[2*i] - inputQ15[2*i] < -8)) {
                dbg("REAL deviation at %d: HW %04x, SW %04x\n", i, fft_result[2*i], inputQ15[2*i]);
            }
            if((fft_result[2*i+1] - inputQ15[2*i+1] > 8) || (fft_result[2*i+1] - inputQ15[2*i+1] < -8)) {
                dbg("IMAG deviation at %d: HW %04x, SW %04x\n", i, fft_result[2*i+1], inputQ15[2*i+1]);
            }
        }
    dbg("fft case%d done\n",j);
    }

}

#endif /* CFG_TEST_FFT512 */

