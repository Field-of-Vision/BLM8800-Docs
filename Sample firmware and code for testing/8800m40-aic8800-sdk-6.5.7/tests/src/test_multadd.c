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
#include "dbg.h"
#include <string.h>
#include <stdlib.h>

#if CFG_TEST_MULTADD
/*
 * MACROS
 ****************************************************************************************
 */
#define MULTADD_TEST
#define MULTADD_TEST_DATA_LEN    32
//MULTADD_GROUP_LEN only support 8
#define MULTADD_GROUP_LEN 8

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
dma_trans_t dma_trans_obj = {0};
fltr_state_t multadd_obj;
static uint32_t multadd_result[MULTADD_TEST_DATA_LEN];
static uint32_t multadd_result_sw;
static uint32_t multadd_result_hw;

uint32_t multadd_cof_table[MULTADD_TEST_DATA_LEN] = {
};

uint32_t multadd_test_data[MULTADD_TEST_DATA_LEN] = {
};

uint32_t multadd_test_data_reverse[MULTADD_TEST_DATA_LEN] = {
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
 void multadd_test(void)
{
    const int ch = DMA_CHANNEL_CYPT_IDX1;
    uint32_t i,j;
    uint32_t multadd_result_tmp = 0;

    memset((void*)hw_sbc4_cof_table,0,4*72);

    for(i=0;i<MULTADD_TEST_DATA_LEN;i++) {
        multadd_cof_table[i] = i;
        multadd_test_data[i] = i;
    }

    for(j=0;j<(MULTADD_TEST_DATA_LEN/MULTADD_GROUP_LEN);j++) {
        for(i=0;i<MULTADD_GROUP_LEN;i++){
            multadd_result_tmp += (8*j+i) * (8*j+i);
        }
        dbg("multadd loop %d, res:%d\n",j,multadd_result_tmp);
        multadd_result_sw += multadd_result_tmp;
        multadd_result_tmp = 0;
    }

    for(j=0;j<(MULTADD_TEST_DATA_LEN/MULTADD_GROUP_LEN);j++) {
        for(i=0;i<MULTADD_GROUP_LEN;i++){
            multadd_test_data_reverse[8*j+i] = multadd_test_data[8*j+7-i];
        }
    }

    // DMA init
    dma_init();
    dma_trans_obj.trans_chn = ch;

    for(j=0;j<(MULTADD_TEST_DATA_LEN/MULTADD_GROUP_LEN);j++) {
    //fir coff_init
        dma_trans_obj.dma_trans_mode = FLT_MODE;
        dma_trans_obj.flt_sbc_mode_en = FLT_MODE_EN;
        dma_trans_obj.flt_order = (MULTADD_GROUP_LEN - 1);
        dma_trans_obj.flt_cofcos_upd_en = FLT_COFFCOS_UPD;
        dma_trans_obj.flt_cof_init_sel = FLT_COF_INIT_ONLY;
        multadd_obj.length_byte = 4*MULTADD_GROUP_LEN;
        multadd_obj.fltr_data = (uint32_t *)(multadd_cof_table + 8*j);

        dma_trans_init(&dma_trans_obj);
        fltr_cof_init(&dma_trans_obj, &multadd_obj);

    // fir calc
        dma_trans_obj.flt_cofcos_upd_en = FLT_COFFCOS_NO_UPD;
        dma_trans_obj.flt_cofshw_upd_en = FLT_COFFSHW_NO_UPD;
        dma_trans_obj.flt_cof_init_sel = FLT_COF_INIT_WITHDATA;

        dma_trans_obj.flt_len_without_coff = MULTADD_GROUP_LEN;
        dma_trans_obj.fltr_in_format_sel = FLTR_IN_17B_LOW;
    //    dma_trans_obj.fltr_out_format_sel = FLTR_OUT_17B_LOW;
        dma_trans_obj.fltr_out_format_sel = FLTR_OUT_17B_HIGH;

        multadd_obj.length_byte = 4*MULTADD_GROUP_LEN;
        multadd_obj.fltr_data = (uint32_t *)(multadd_test_data_reverse+ 8*j);

        dma_trans_init(&dma_trans_obj);
        fltr_calc(&dma_trans_obj, &multadd_obj, multadd_result);
#if 0
        dbg("multadd_res loop %d:\n",j);
        for(i = 0; i < MULTADD_GROUP_LEN; i++) {
            dbg("%d: %d\n", i, multadd_result[i]);
        }
#endif
        multadd_result_hw += multadd_result[MULTADD_GROUP_LEN-1];
    }
    dbg("multadd result: SW:%d, HW:%d\n", multadd_result_sw,multadd_result_hw);
}

#endif /* CFG_TEST_MULTADD */



