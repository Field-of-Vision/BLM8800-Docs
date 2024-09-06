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
#include "dbg.h"
#include <stdint.h>

#ifdef CFG_TEST_DMA

/*
 * MACROS
 ****************************************************************************************
 */
#define UART_PRINT              dbg
#define DMA_BUF_LENGTH          1024
#define TRANS_SIZE0             512
#define TRANS_SIZE1             896
#define DMA_IRQ_MODE            (1)

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
static uint8_t bufA[DMA_BUF_LENGTH];
static uint8_t bufB[DMA_BUF_LENGTH];
static uint8_t bufC[DMA_BUF_LENGTH];
static uint8_t bufD[DMA_BUF_LENGTH];

/*
 * FUNCTIONS
 ****************************************************************************************
 */
#if DMA_IRQ_MODE
void DMA10_IRQHandler(void)
{
    dma_ch_int_clear(DMA_CHANNEL_IPC_DBG_DUMP);
}
#endif

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void dma_test(void)
{
    const int ch = DMA_CHANNEL_IPC_DBG_DUMP;
    const uint8_t tbl[4] = {0xAA, 0xBB, 0xCC, 0xDD};
    dma_desc_t dma_desc0, dma_desc1, dma_desc2;
    int i;

    UART_PRINT("\nStart test case: dma\n");
    UART_PRINT("ch=%d\n bufA: %p\n bufB: %p\n bufC: %p\n bufD: %p\n",ch,bufA,bufB,bufC,bufD);

    #if DMA_IRQ_MODE
    NVIC_SetPriority(DMA10_IRQn, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(DMA10_IRQn);
    #endif

    // Init src/dst buf
    for (i = 0; i < DMA_BUF_LENGTH; i++) {
        bufA[i] = bufB[i] = tbl[i & 0x03];
        bufC[i] = bufD[i] = 0;
    }

    // DMA init
    dma_init();

    dma_desc0.SAR = (uint32_t)bufA;
    dma_desc0.DAR = (uint32_t)bufC;
    dma_desc_length_set(&dma_desc0, TRANS_SIZE0);
    dma_desc0.LNAR = (uint32_t)(&dma_desc1);

    dma_desc1.SAR = (uint32_t)(bufB + 3);  // not aligned address
    dma_desc1.DAR = (uint32_t)(bufD + 1);
    dma_desc_length_set(&dma_desc1, TRANS_SIZE1);
    #if DMA_IRQ_MODE
    dma_desc_dedicated_int_en_setb(&dma_desc1);
    #endif
    dma_desc1.LNAR = 0;

    dma_push(&dma_desc0, &dma_desc1, ch);
    #if !DMA_IRQ_MODE
    dma_lli_poll(ch);
    dma_ch_int_clear(ch);
    #endif

    for (i = 0; i < 0x289; i++) {  // delay: 0x3FF(176us), 0x28E(last frag, 96024ns), 0x289(last two frags), 0x1B3(64464ns)
        __asm("nop");
        __asm("nop");
    }

    dma_desc2.SAR = (uint32_t)(bufB + 0);
    dma_desc2.DAR = (uint32_t)(bufD + 0);
    dma_desc_length_set(&dma_desc2, TRANS_SIZE1);
    #if DMA_IRQ_MODE
    dma_desc_dedicated_int_en_setb(&dma_desc2);
    #endif
    dma_desc2.LNAR = 0;

    dma_push(&dma_desc2, &dma_desc2, ch);
    #if !DMA_IRQ_MODE
    dma_lli_poll(ch);
    dma_ch_int_clear(ch);
    #endif

    for (i = 0; i < 0x3FF; i++) {  // delay: 0x3FF(176us)
        __asm("nop");
        __asm("nop");
    }

    UART_PRINT("bufC begin:\n");
    for (i = 0; i < 16; i++) {
        UART_PRINT(" %02x", bufC[i]);
    }
    UART_PRINT("\nbufC end:\n");
    for (i = -16; (i < 16) && (TRANS_SIZE0 + i < DMA_BUF_LENGTH); i++) {
        if (i == 0)
            UART_PRINT("\n");
        UART_PRINT(" %02x", bufC[TRANS_SIZE0 + i]);
    }
    UART_PRINT("\nbufD begin:\n");
    for (i = 0; i < 16; i++) {
        UART_PRINT(" %02x", bufD[i]);
    }
    UART_PRINT("\nbufD end:\n");
    for (i = -16; (i < 16) && (TRANS_SIZE1 + i < DMA_BUF_LENGTH); i++) {
        if (i == 0)
            UART_PRINT("\n");
        UART_PRINT(" %02x", bufD[TRANS_SIZE1 + i]);
    }
    UART_PRINT("\ndma test done\n");
}

#endif /* CFG_TEST_DMA */
