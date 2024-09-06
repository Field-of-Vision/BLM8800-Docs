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

#if CFG_TEST_FIR
/*
 * MACROS
 ****************************************************************************************
 */
#define FLT_TEST
#define FFT_TEST_DATA_LEN    64

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
dma_trans_t dma_trans_obj = {0};
fltr_state_t fltr_obj;
static uint32_t flt_result[FFT_TEST_DATA_LEN];

uint32_t fltr_cof_table[8] = {
    //15bit coff -> 1.14
    //coff generate by matlab,lowpass 200
    //0.00923190608529486 0.0487673526658137  0.164217725496927   0.277783015751964   0.277783015751964   0.164217725496927   0.0487673526658137  0.00923190608529486
    0x00000097, 0x0000031F, 0x00000A82, 0x000011C7,
    0x000011C7, 0x00000A82, 0x0000031F, 0x00000097,
};

uint32_t fltr_test_data[FFT_TEST_DATA_LEN] = {
//19bit data -> 2.17
  0x00000000, 0x00010824, 0x000123E5, 0x00005D4C, 0xFFFFA95F, 0xFFFFE6E1, 0x0000F466, 0x0001D294
, 0x0001AEB6, 0x0000BEB4, 0x00000848, 0x00004EE1, 0x00014706, 0x0001E559, 0x0001768B, 0x00005B51
, 0xFFFFA3A4, 0xFFFFF2BB, 0x0000D4F4, 0x00013993, 0x00009103, 0xFFFF63F9, 0xFFFEC556, 0xFFFF3375
, 0x000014E3, 0x000059D6, 0xFFFF996B, 0xFFFE802B, 0xFFFE1C31, 0xFFFEC313, 0xFFFFB8CA, 0xFFFFF4C1
, 0xFFFF36DD, 0xFFFE4A9D, 0xFFFE3209, 0xFFFF1772, 0x000020C7, 0x0000533F, 0xFFFF9923, 0xFFFED7CF
, 0xFFFEFEDD, 0x00000C90, 0x00010EB9, 0x00011F33, 0x000053C3, 0xFFFFA66A, 0xFFFFEEE7, 0x00010029
, 0x0001D6BE, 0x0001A7AE, 0x0000B45F, 0x000005C3, 0x000056DC, 0x000150F7, 0x0001E669, 0x00016CF4
, 0x0000503A, 0xFFFFA194, 0xFFFFFA9C, 0x0000DD24, 0x00013802, 0x000085C4, 0xFFFF5936, 0xFFFEC4B8
};

/*
 * FUNCTIONS
 ****************************************************************************************
 */

 /**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
 void fir_test(void)
{
    const int ch = DMA_CHANNEL_CYPT_IDX1;
    uint32_t i;

    // DMA init
    dma_init();
    dma_trans_obj.trans_chn = ch;

//fir coff_init
    dma_trans_obj.dma_trans_mode = FLT_MODE;
    dma_trans_obj.flt_sbc_mode_en = FLT_MODE_EN;
    dma_trans_obj.flt_order = 7;
    dma_trans_obj.flt_cofcos_upd_en = FLT_COFFCOS_UPD;
    dma_trans_obj.flt_cof_init_sel = FLT_COF_INIT_ONLY;
    fltr_obj.length_byte =sizeof(fltr_cof_table);
    fltr_obj.fltr_data = (uint32_t *)fltr_cof_table;	

    dma_trans_init(&dma_trans_obj);
    fltr_cof_init(&dma_trans_obj, &fltr_obj);

// fir calc
    dma_trans_obj.flt_cofcos_upd_en = FLT_COFFCOS_NO_UPD;
    dma_trans_obj.flt_cofshw_upd_en = FLT_COFFSHW_NO_UPD;
    dma_trans_obj.flt_cof_init_sel = FLT_COF_INIT_WITHDATA;

    dma_trans_obj.flt_len_without_coff = FFT_TEST_DATA_LEN;
    dma_trans_obj.fltr_in_format_sel = FLTR_IN_17B_LOW;
    dma_trans_obj.fltr_out_format_sel = FLTR_OUT_17B_LOW;
    fltr_obj.length_byte = sizeof(fltr_test_data);
    fltr_obj.fltr_data = (uint32_t *)fltr_test_data;

    dma_trans_init(&dma_trans_obj);
    fltr_calc(&dma_trans_obj, &fltr_obj, flt_result);

    dbg("sbc_res:\n");
    for(i = 0; i < FFT_TEST_DATA_LEN; i++) {
        dbg("%d: %d\n", i, flt_result[i]);
    }
}

#endif /* CFG_TEST_FIR */

