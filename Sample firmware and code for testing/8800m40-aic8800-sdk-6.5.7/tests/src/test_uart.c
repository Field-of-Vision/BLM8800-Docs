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
#include "uart1_api.h"
#include "dma_generic.h"
#include "sysctrl_api.h"
#include "dbg.h"
#include "rtos_al.h"

#ifdef CFG_TEST_UART

/*
 * MACROS
 ****************************************************************************************
 */
#define USER_PRINTF             dbg
#define UART_DMA_TEST_ENABLED   (1)
#define UART_DMA_ISR_ENABLED    (1)
#define UART_DMA_BYTE_CNT_MAX   (64)
#define UART_RXDMA_CH_IDX       DMA_CHANNEL_UART_RX
#define UART_TXDMA_CH_IDX       DMA_CHANNEL_UART_TX
#define UART_RXDMA_IRQ_IDX      DMA08_IRQn
#define UART_TXDMA_IRQ_IDX      DMA09_IRQn
#define uart_rxdma_isr          DMA08_IRQHandler
#define uart_txdma_isr          DMA09_IRQHandler

/*
 * GLOBAL CONSTANTS & VARIABLES
 ****************************************************************************************
 */
#if (UART_DMA_TEST_ENABLED)
rtos_semaphore uart_rd_sema;
rtos_semaphore uart_wr_sema;
#endif

/*
 * FUNCTIONS
 ****************************************************************************************
 */
#if (UART_DMA_TEST_ENABLED)
/**
 ****************************************************************************************
 * @brief init func
 ****************************************************************************************
 */
void uart_dma_init(void)
{
    int ret;
    ret = rtos_semaphore_create(&uart_rd_sema, 1, 0);
    if (ret) {
        dbg("sema create fail: %d\r\n", ret);
    }
    ret = rtos_semaphore_create(&uart_wr_sema, 1, 0);
    if (ret) {
        dbg("sema create fail: %d\r\n", ret);
    }
    // clk en
    #if (PLF_AIC8800)
    cpusysctrl_hclkme_set(CSC_HCLKME_DMA_EN_BIT);
    #else
    uart1_dmamod_setf(1);
    #endif
    NVIC_SetPriority(UART_RXDMA_IRQ_IDX, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(UART_RXDMA_IRQ_IDX);
    NVIC_SetPriority(UART_TXDMA_IRQ_IDX, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(UART_TXDMA_IRQ_IDX);
}

/**
 ****************************************************************************************
 * @brief read func, blocking type
 ****************************************************************************************
 */
int uart_dma_read(unsigned int *buff_rd, unsigned int byte_cnt)
{
    const int ch = UART_RXDMA_CH_IDX;
    byte_cnt = MIN(byte_cnt, UART_DMA_BYTE_CNT_MAX);

    dma_erqcsr_set(REQ_CID_UART1_RX, ch);
    dma_ch_rqr_erqm_clrb(ch);
    dma_ch_rqr_erql_setb(ch);
    dma_ch_dar_set(ch, (unsigned int)buff_rd);
    dma_ch_sar_set(ch, (unsigned int)(UART1_TXRXD_ADDR));
    dma_ch_tbl0cr_set(ch, ((1) | (REQ_TBL0 << DMA_CH_RQTYP_LSB) | (AHB_WORD << DMA_CH_DBUSU_LSB) |
                             (AHB_BYTE << DMA_CH_SBUSU_LSB) | DMA_CH_CONSTSA_BIT));
    dma_ch_tbl1cr_set(ch, byte_cnt);
    dma_ch_tbl2cr_set(ch, byte_cnt);
    dma_ch_tsr_set(ch, ((1 << DMA_CH_STRANSZ_LSB) | (4 << DMA_CH_DTRANSZ_LSB)));
    dma_ch_wmar_set(ch, 0);
    dma_ch_wjar_set(ch, 0);
    dma_ch_lnar_set(ch, 0);
    dma_ch_tbl0sr_set(ch, ((0 << DMA_CH_STBL0SZ_LSB) | (0 << DMA_CH_DTBL0SZ_LSB)));
    dma_ch_tbl1ssr_set(ch, 0);
    dma_ch_tbl1dsr_set(ch, 0);
    #if UART_DMA_ISR_ENABLED
    dma_ch_icsr_set(ch, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(ch, (DMA_CH_CHENA_BIT | (0x01UL << DMA_CH_BUSBU_LSB)));
    #if UART_DMA_ISR_ENABLED
    rtos_semaphore_wait(uart_rd_sema, -1);
    #else
    while (dma_ch_icsr_tbl2_irst_getb(ch) == 0);
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    #endif

    return 0;
}

/**
 ****************************************************************************************
 * @brief write func, blocking type
 ****************************************************************************************
 */
int uart_dma_write(unsigned int *buff_wr, unsigned int byte_cnt)
{
    const int ch = UART_TXDMA_CH_IDX;
    byte_cnt = MIN(byte_cnt, UART_DMA_BYTE_CNT_MAX);

    dma_erqcsr_set(REQ_CID_UART1_TX, ch);
    dma_ch_rqr_erqm_setb(ch);
    dma_ch_rqr_erql_setb(ch);
    dma_ch_dar_set(ch, (unsigned int)UART1_TXRXD_ADDR);
    dma_ch_sar_set(ch, (unsigned int)buff_wr);
    dma_ch_tbl0cr_set(ch, ((1) | (REQ_TBL0 << DMA_CH_RQTYP_LSB) | (AHB_BYTE << DMA_CH_DBUSU_LSB) |
                             (AHB_WORD << DMA_CH_SBUSU_LSB) | DMA_CH_CONSTDA_BIT));
    dma_ch_tbl1cr_set(ch, byte_cnt);
    dma_ch_tbl2cr_set(ch, byte_cnt);
    dma_ch_tsr_set(ch, ((4 << DMA_CH_STRANSZ_LSB) | (1 << DMA_CH_DTRANSZ_LSB)));
    dma_ch_wmar_set(ch, 0);
    dma_ch_wjar_set(ch, 0);
    dma_ch_lnar_set(ch, 0);
    dma_ch_tbl0sr_set(ch, ((0 << DMA_CH_STBL0SZ_LSB) | (0 << DMA_CH_DTBL0SZ_LSB)));
    dma_ch_tbl1ssr_set(ch, 0);
    dma_ch_tbl1dsr_set(ch, 0);
    #if UART_DMA_ISR_ENABLED
    dma_ch_icsr_set(ch, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(ch, (DMA_CH_CHENA_BIT | (0x01UL << DMA_CH_BUSBU_LSB)));
    #if UART_DMA_ISR_ENABLED
    rtos_semaphore_wait(uart_wr_sema, -1);
    #else
    while (dma_ch_icsr_tbl2_irst_getb(ch) == 0);
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    #endif

    return 0;
}

#if UART_DMA_ISR_ENABLED
void uart_rxdma_isr(void)
{
    const int ch = UART_RXDMA_CH_IDX;
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    rtos_semaphore_signal(uart_rd_sema, true);
}

void uart_txdma_isr(void)
{
    const int ch = UART_TXDMA_CH_IDX;
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    rtos_semaphore_signal(uart_wr_sema, true);
}
#endif
#else  /* UART_DMA_TEST_ENABLED */
void uart_rx_handler(void)
{
    while (uart1_get_rx_count()) {
        unsigned char c = (unsigned char)uart1_getc();
        USER_PRINTF("uart rx: %02X\n", c);
    }
}
#endif /* UART_DMA_TEST_ENABLED */

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void uart_test(void)
{
    unsigned char test_buf[] = {
        0x30, 0x30, 0x30, 0x31, 0x30, 0x32, 0x30, 0x33, 0x30, 0x34,
        0x30, 0x35, 0x30, 0x36, 0x30, 0x37, 0x30, 0x38, 0x30, 0x39,
        0x31, 0x30, 0x31, 0x31, 0x31, 0x32, 0x31, 0x33, 0x31, 0x34,
        0x31, 0x35, 0x31, 0x36, 0x31, 0x37, 0x31, 0x38, 0x31, 0x39,
        0x32, 0x30, 0x32, 0x31, 0x32, 0x32, 0x32, 0x33, 0x32, 0x34,
        0x32, 0x35, 0x32, 0x36, 0x32, 0x37, 0x32, 0x38, 0x32, 0x39,
        0x33, 0x30, 0x33, 0x31,/* 0x33, 0x32, 0x33, 0x33, 0x33, 0x34,
        0x33, 0x35, 0x33, 0x36, 0x33, 0x37, 0x33, 0x38, 0x33, 0x39,*/
    };
    unsigned int idx;
    USER_PRINTF("\nStart test case: uart\n");

    uart1_init();

    #if (UART_DMA_TEST_ENABLED)
    uart1_rxirqen_setf(0); //disable rx interrupt
    uart_dma_init();

    do {
        #if 1
        USER_PRINTF("\n\nbef read\n");
        // Read data
        uart_dma_read((unsigned int *)test_buf, sizeof(test_buf));
        USER_PRINTF("read size=%d\n", sizeof(test_buf));
        for (idx = 0; idx < sizeof(test_buf); idx++) {
            USER_PRINTF(" %02x", test_buf[idx]);
        }
        #endif

        USER_PRINTF("\n\nbef write\n");
        idx = 0;
        while (idx < 0x02) {
            unsigned char tmp = test_buf[0] & 0xF0;
            test_buf[0] = tmp | (0x0F & idx++);
            // Write data
            uart_dma_write((unsigned int *)test_buf, sizeof(test_buf));
        }
        USER_PRINTF("write size=%d\n", sizeof(test_buf));
        for (idx = 0; idx < sizeof(test_buf); idx++) {
            USER_PRINTF(" %02x", test_buf[idx]);
        }
    } while (1);
    #else  /* UART_DMA_TEST_ENABLED */
    uart1_puts("Hi uart!\r\n");
    register_uart1_rx_function(uart_rx_handler);
    for (idx = 0; idx < sizeof(test_buf); idx++) {
        uart1_putc(test_buf[idx]);
    }
    #endif /* UART_DMA_TEST_ENABLED */

    USER_PRINTF("\nuart test done\n");
}

#endif /* CFG_TEST_UART */
