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
#include <string.h>
#include "dbg.h"
#include "psram_api.h"
#include "system.h"
#include "console.h"

#ifdef CFG_RTOS
#include "rtos_al.h"
#include "rtos.h"
#endif /* CFG_RTOS */

#ifdef CFG_TEST_PSRAM

/*
 * MACROS
 ****************************************************************************************
 */
#define ICACHE_MEM_SIZE         (0x00000000UL)
#define RAM_1KB_SIZE            (0x01UL << 10)
#define RAM_2KB_SIZE            (0x01UL << 11)
#define RAM_3KB_SIZE            (RAM_1KB_SIZE + RAM_2KB_SIZE)
#define RAM_4KB_SIZE            (0x01UL << 12)
#define RAM_4KB_MASK            (RAM_4KB_SIZE - 1)
#define RAM_64MB_SIZE           (0x01UL << 26) // 0x04000000
#define ARRAY_LENGTH_U1         RAM_1KB_SIZE
#define ARRAY_LENGTH_U2         (RAM_1KB_SIZE / sizeof(uint16_t))
#define ARRAY_LENGTH_U4         (RAM_1KB_SIZE / sizeof(uint32_t))
#define ARRAY_LENGTH_U8         (RAM_1KB_SIZE / sizeof(uint64_t))
#define MAX_CHK_CNT             1000000 // 1 million times
#define RAM_BANK_NUM            2 // number of banks for test
#define UART_PRINT              dbg
#define U1_VAL(i)               ((uint8_t)(i))
#define U2_VAL(i)               ((uint16_t)((uint16_t)(i) << 1))
#define U4_VAL(i)               ((uint32_t)((uint32_t)(i) << 2))
#define U8_VAL(i)               ((uint64_t)((uint64_t)(i) << 3))
#define U1_RAM_VAL(addr,ofst)   (*((uint8_t  *)(addr) + ofst))
#define U2_RAM_VAL(addr,ofst)   (*((uint16_t *)(addr + RAM_1KB_SIZE) + ofst))
#define U4_RAM_VAL(addr,ofst)   (*((uint32_t *)(addr + RAM_2KB_SIZE) + ofst))
#define U8_RAM_VAL(addr,ofst)   (*((uint64_t *)(addr + RAM_3KB_SIZE) + ofst))

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
uint32_t ram_size;
uint32_t ram_bank[RAM_BANK_NUM][2];
uint8_t  u1_arr[ARRAY_LENGTH_U1];
uint16_t u2_arr[ARRAY_LENGTH_U2];
uint32_t u4_arr[ARRAY_LENGTH_U4];
uint64_t u8_arr[ARRAY_LENGTH_U8];
uint64_t rand_num                    __attribute__ ((section (".PSDRAM")));
uint8_t buf_chk_psd[ARRAY_LENGTH_U1] __attribute__ ((section (".PSDRAM")));
uint8_t  u1_arr_psd[ARRAY_LENGTH_U1] __attribute__ ((section (".PSDRAM")));
uint16_t u2_arr_psd[ARRAY_LENGTH_U2] __attribute__ ((section (".PSDRAM")));
uint32_t u4_arr_psd[ARRAY_LENGTH_U4] __attribute__ ((section (".PSDRAM")));
uint64_t u8_arr_psd[ARRAY_LENGTH_U8] __attribute__ ((section (".PSDRAM")));
uint8_t  * const pu1_src[2] = {u1_arr, u1_arr_psd};
uint16_t * const pu2_src[2] = {u2_arr, u2_arr_psd};
uint32_t * const pu4_src[2] = {u4_arr, u4_arr_psd};
uint64_t * const pu8_src[2] = {u8_arr, u8_arr_psd};
extern uint32_t __etext_iram[], __pstext_start__[], __pstext_end__[], __psdata_start__[], __psdata_end__[];

/*
 * FUNCTIONS
 ****************************************************************************************
 */
__attribute__ ((section (".PSIRAM"))) void pstext_task_routine(void *env)
{
    int res = 0;
    int chk_cnt_itr = 0, chk_cnt_4KB = 0;
    int idx;

    UART_PRINT("\n%s started, rand_num=0x%08X%08X\n", __func__, (uint32_t)(rand_num >> 32), (uint32_t)rand_num);

    UART_PRINT("Init arrays\n");
    for (idx = 0; idx < ARRAY_LENGTH_U1; idx++) {
        u1_arr[idx] = U1_VAL(idx);
        if (idx < ARRAY_LENGTH_U2) {
            u2_arr[idx] = U2_VAL(idx);
            if (idx < ARRAY_LENGTH_U4) {
                u4_arr[idx] = U4_VAL(idx);
                if (idx < ARRAY_LENGTH_U8) {
                    u8_arr[idx] = U8_VAL(idx);
                }
            }
        }
    }
    #if 1
    UART_PRINT("Ptr src:\n  u1_arr=0x%p, u2_arr=0x%p, u4_arr=0x%p, u8_arr=0x%p\n"
               "  u1_arr_psd=0x%p, u2_arr_psd=0x%p, u4_arr_psd=0x%p, u8_arr_psd=0x%p\n",
               u1_arr, u2_arr, u4_arr, u8_arr, u1_arr_psd, u2_arr_psd, u4_arr_psd, u8_arr_psd);
    #endif

    while (!res) {
        int bank;
        uint32_t addr;
        for (bank = 0; bank < RAM_BANK_NUM; bank++) {
            dbg("bank=%d\n",bank);
            for (addr = ram_bank[bank][0]; addr < ram_bank[bank][1]; addr += RAM_4KB_SIZE) {
                int srci;
                dbg("addr=%08X\n",addr);
                for (srci = 0; srci < 2; srci++) {
                    dbg("srci=%d\n",srci);
                    uint8_t  *ptr_u1 = pu1_src[srci];
                    uint16_t *ptr_u2 = pu2_src[srci];
                    uint32_t *ptr_u4 = pu4_src[srci];
                    uint64_t *ptr_u8 = pu8_src[srci];
                    // copy 4KB
                    for (idx = 0; idx < ARRAY_LENGTH_U1; idx++) {
                        U1_RAM_VAL(addr, idx) = ptr_u1[idx];
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U2; idx++) {
                        U2_RAM_VAL(addr, idx) = ptr_u2[idx];
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U4; idx++) {
                        U4_RAM_VAL(addr, idx) = ptr_u4[idx];
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U8; idx++) {
                        U8_RAM_VAL(addr, idx) = ptr_u8[idx];
                    }
                    // check copy result
                    for (idx = 0; idx < ARRAY_LENGTH_U1; idx++) {
                        if (ptr_u1[idx] != U1_RAM_VAL(addr, idx)) {
                            UART_PRINT("u1 cp chk err: idx=%d, src_%d[%p]=%02X,dst[%08x]=%02X\n",
                                        idx,srci,&ptr_u1[idx],ptr_u1[idx],&U1_RAM_VAL(addr, idx),U1_RAM_VAL(addr, idx));
                            res = 1;
                            break;
                        }
                        if (idx < ARRAY_LENGTH_U2) {
                            if (ptr_u2[idx] != U2_RAM_VAL(addr, idx)) {
                                UART_PRINT("u2 cp chk err: idx=%d, src_%d[%p]=%04X,dst[%08x]=%04X\n",
                                            idx,srci,&ptr_u2[idx],ptr_u2[idx],&U2_RAM_VAL(addr, idx),U2_RAM_VAL(addr, idx));
                                res = 1;
                                break;
                            }
                            if (idx < ARRAY_LENGTH_U4) {
                                if (ptr_u4[idx] != U4_RAM_VAL(addr, idx)) {
                                    UART_PRINT("u4 cp chk err: idx=%d, src_%d[%p]=%08X,dst[%08x]=%08X\n",
                                                idx,srci,&ptr_u4[idx],ptr_u4[idx],&U4_RAM_VAL(addr, idx),U4_RAM_VAL(addr, idx));
                                    res = 1;
                                    break;
                                }
                                if (idx < ARRAY_LENGTH_U8) {
                                    if (ptr_u8[idx] != U8_RAM_VAL(addr, idx)) {
                                        UART_PRINT("u8 cp chk err: idx=%d, src_%d[%p]=%08X%08X,dst[%08x]=%08X%08X\n",
                                                    idx,srci,&ptr_u8[idx],(uint32_t)(ptr_u8[idx] >> 32),(uint32_t)ptr_u8[idx],
                                                    &U8_RAM_VAL(addr, idx),(uint32_t)(U8_RAM_VAL(addr, idx) >> 32),(uint32_t)U8_RAM_VAL(addr, idx));
                                        res = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (res) { // err detected, end the loop
                        srci = 2;
                        addr = ram_bank[RAM_BANK_NUM - 1][1];
                        bank = RAM_BANK_NUM;
                        break;
                    }

                    // calculate 4KB
                    for (idx = 0; idx < ARRAY_LENGTH_U1; idx++) {
                        ptr_u1[idx] += (uint8_t)rand_num;
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U2; idx++) {
                        ptr_u2[idx] -= (uint16_t)rand_num;
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U4; idx++) {
                        ptr_u4[idx] |= (uint32_t)rand_num;
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U8; idx++) {
                        ptr_u8[idx] ^= (uint64_t)rand_num;
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U1; idx++) {
                        U1_RAM_VAL(addr, idx) += (uint8_t)rand_num;
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U2; idx++) {
                        U2_RAM_VAL(addr, idx) -= (uint16_t)rand_num;
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U4; idx++) {
                        U4_RAM_VAL(addr, idx) |= (uint32_t)rand_num;
                    }
                    for (idx = 0; idx < ARRAY_LENGTH_U8; idx++) {
                        U8_RAM_VAL(addr, idx) ^= (uint64_t)rand_num;
                    }
                    // check calc result
                    for (idx = 0; idx < ARRAY_LENGTH_U1; idx++) {
                        if (ptr_u1[idx] != U1_RAM_VAL(addr, idx)) {
                            UART_PRINT("u1 calc chk err: idx=%d, src_%d[%p]=%02X,dst[%08x]=%02X\n",
                                        idx,srci,&ptr_u1[idx],ptr_u1[idx],&U1_RAM_VAL(addr, idx),U1_RAM_VAL(addr, idx));
                            res = 1;
                            break;
                        }
                        if (idx < ARRAY_LENGTH_U2) {
                            if (ptr_u2[idx] != U2_RAM_VAL(addr, idx)) {
                                UART_PRINT("u2 calc chk err: idx=%d, src_%d[%p]=%04X,dst[%08x]=%04X\n",
                                            idx,srci,&ptr_u2[idx],ptr_u2[idx],&U2_RAM_VAL(addr, idx),U2_RAM_VAL(addr, idx));
                                res = 1;
                                break;
                            }
                            if (idx < ARRAY_LENGTH_U4) {
                                if (ptr_u4[idx] != U4_RAM_VAL(addr, idx)) {
                                    UART_PRINT("u4 calc chk err: idx=%d, src_%d[%p]=%08X,dst[%08x]=%08X\n",
                                                idx,srci,&ptr_u4[idx],ptr_u4[idx],&U4_RAM_VAL(addr, idx),U4_RAM_VAL(addr, idx));
                                    res = 1;
                                    break;
                                }
                                if (idx < ARRAY_LENGTH_U8) {
                                    if (ptr_u8[idx] != U8_RAM_VAL(addr, idx)) {
                                        UART_PRINT("u8 calc chk err: idx=%d, src_%d[%p]=%08X%08X,dst[%08x]=%08X%08X\n",
                                                    idx,srci,&ptr_u8[idx],(uint32_t)(ptr_u8[idx] >> 32),(uint32_t)ptr_u8[idx],
                                                    &U8_RAM_VAL(addr, idx),(uint32_t)(U8_RAM_VAL(addr, idx) >> 32),(uint32_t)U8_RAM_VAL(addr, idx));
                                        res = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (res) { // err detected, end the loop
                        srci = 2;
                        addr = ram_bank[RAM_BANK_NUM - 1][1];
                        bank = RAM_BANK_NUM;
                        break;
                    }
                }
                chk_cnt_4KB++;
            }
        }

        chk_cnt_itr++;
        if (chk_cnt_itr > MAX_CHK_CNT) {
            break;
        } else {
            UART_PRINT("cur_itr=%9d, %10d\n",chk_cnt_itr,chk_cnt_4KB);
        }
    }

    UART_PRINT("pstext exit! total_4KB=%d , total_itr=%d, result=%s\n",chk_cnt_4KB,chk_cnt_itr,res?"FAIL":"OK");
#ifdef CFG_RTOS
    rtos_task_delete(NULL); // delete the task itself while exiting
#endif /* CFG_RTOS */
}

static int cmd_pstext_task_run(int argc, char * const argv[])
{
    #ifdef CFG_RTOS
    // Create the pstext task that located in .PSIRAM
    if (rtos_task_create(pstext_task_routine, "PSTEXT", TEST_TASK,
                         TASK_STACK_SIZE_TEST, NULL, TASK_PRIORITY_TEST, NULL)) {
        UART_PRINT("pstext task create fail!\n");
    }
    #else  /* CFG_RTOS */
    // Call function that located in .PSIRAM
    pstext_task_routine(NULL);
    #endif /* CFG_RTOS */
    return 0;
}

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void psram_test(void)
{
    register uint32_t *dst;
    register uint32_t *src;

    UART_PRINT("\nPSRAM test start\n");

    psram_init(ICACHE_MEM_SIZE);
    UART_PRINT("psram 2x_clk: %d\n", PsramCntrlClock);
    ram_size = psram_size_get();
    UART_PRINT("Size=0x%08X\n", ram_size);
    if (ram_size > RAM_64MB_SIZE) {
        UART_PRINT("Size Error, larger than 64MB\n");
        return;
    }
    UART_PRINT("Memory mapping:\n");
    if (ICACHE_MEM_SIZE) {
        UART_PRINT("  icache: 0x%08X ~ 0x%08X\n", AIC_CACHE1_MEM_BASE - ICACHE_MEM_SIZE, AIC_CACHE1_MEM_BASE);
        UART_PRINT("  dcache: 0x%08X ~ 0x%08X\n", AIC_CACHE1_MEM_BASE, (AIC_CACHE1_MEM_BASE + (ram_size - ICACHE_MEM_SIZE)));
    } else {
        UART_PRINT("  dcache: 0x%08X ~ 0x%08X\n", AIC_CACHE1_MEM_BASE, (AIC_CACHE1_MEM_BASE + ram_size));
    }

    // check psram size
    if (((uint32_t)__pstext_start__ + ram_size) < (uint32_t)__psdata_end__) {
        UART_PRINT("Error: too large psdata_end=0x%p\n", __psdata_end__);
        return;
    }

    ram_bank[0][0] = ((uint32_t)__pstext_end__ + RAM_4KB_MASK) & ~RAM_4KB_MASK;
    ram_bank[0][1] = (uint32_t)__psdata_start__ & ~RAM_4KB_MASK;
    ram_bank[1][0] = ((uint32_t)__psdata_end__ + RAM_4KB_MASK) & ~RAM_4KB_MASK;
    ram_bank[1][1] = ((uint32_t)__pstext_start__ + ram_size) & ~RAM_4KB_MASK;
    UART_PRINT("Code/Data Boarders:\n  0x%08X ~ 0x%08X\n  0x%08X ~ 0x%08X\n",
               (uint32_t)__pstext_start__,(uint32_t)__pstext_end__,(uint32_t)__psdata_start__,(uint32_t)__psdata_end__);
    UART_PRINT("RAM Banks for test:\n  0x%08X ~ 0x%08X\n  0x%08X ~ 0x%08X\n",
               ram_bank[0][0], ram_bank[0][1], ram_bank[1][0], ram_bank[1][1]);

    UART_PRINT("code block from: 0x%p, size: 0x%x\n", __etext_iram, ((uint32_t)__pstext_end__ - (uint32_t)__pstext_start__));
    UART_PRINT("start to copy...\n");
    // copy pstext code from IRAM to PSIRAM
    dst = __pstext_start__;
    src = __etext_iram;
    while (dst < __pstext_end__) {
        //UART_PRINT("cpy [0x%x] -> [0x%x] = 0x%x\n", src, dst, *src);
        *dst++ = *src++;
    }

    UART_PRINT("pstext_task_routine=0x%p\n",pstext_task_routine);

    #if 1
    // check pstext code in PSIRAM
    dst = (uint32_t *)(AIC_PSRAM_MEM_BASE);
    src = __etext_iram;
    while(dst < (uint32_t *)(AIC_PSRAM_MEM_BASE + ((uint32_t)__pstext_end__ - (uint32_t)__pstext_start__))) {
        //UART_PRINT("chk [0x%x]\n", dst);
        if (*dst != *src) {
            UART_PRINT("Err: src:[%x]=%x, dst:[%x]=%x\r\n",(uint32_t)src,*src,(uint32_t)dst,*dst);
            break;
        }
        dst++;
        src++;
    }
    if (dst < (uint32_t *)(AIC_PSRAM_MEM_BASE + ((uint32_t)__pstext_end__ - (uint32_t)__pstext_start__))) {
        UART_PRINT("pstext code err\r\n");
    } else {
        UART_PRINT("pstext code check ok\r\n");
    }
    #endif

    console_cmd_add("ptaskrun", "run pstext task", 1, 1, cmd_pstext_task_run);

    UART_PRINT("\nPSRAM test done\n");
}

#endif /* CFG_TEST_PSRAM */
