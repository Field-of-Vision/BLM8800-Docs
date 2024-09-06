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
#include "reg_spi.h"
#include "reg_iomux.h"
#include "dma_generic.h"
#include "sysctrl_api.h"
#include "dbg.h"
#include "rtos_al.h"

#ifdef CFG_TEST_SPI0

/*
 * MACROS
 ****************************************************************************************
 */
#define USER_PRINTF             dbg
#define SPI_CLK_FREQ            (1000000)

#define SPI_DEMO_SELECT         1//0:spi_rfif, 1:spi_dma, 2:spi_flash
#if (SPI_DEMO_SELECT == 0)
#define SPI_DEMO_RFIF   1
#define SPI_DEMO_DMA    0
#define SPI_DEMO_FLASH  0
#elif (SPI_DEMO_SELECT == 1)
#define SPI_DEMO_RFIF   0
#define SPI_DEMO_DMA    1
#define SPI_DEMO_FLASH  0
#elif (SPI_DEMO_SELECT == 2)
#define SPI_DEMO_RFIF   0
#define SPI_DEMO_DMA    0
#define SPI_DEMO_FLASH  1
#else
#define SPI_DEMO_RFIF   0
#define SPI_DEMO_DMA    0
#define SPI_DEMO_FLASH  0
#endif

// spi_rfif
#define GEN_MEM_ADDR_MASK       (0x00007FFF)
//#define RW_GEN_MEM_DATA         (0x00AAA555)
//#define RW_TXRX_GAIN_MEM_DATA   (0xAAAA5555)
#define RW_GEN_MEM_DATA         (addr)
#define RW_TXRX_GAIN_MEM_DATA   (addr)

// spi_dma
#define SPI0_ISR_ENABLED        (SPI_DEMO_DMA && 1)
#define SPI0_DMA_ISR_ENABLED    (SPI_DEMO_DMA && 1)
#define SPI0_3_WIRE_ENABLED     (0)
#define SPI0_DMA_BYTE_CNT_MAX   (64)
#define SPI0_RXDMA_CH_IDX       DMA_CHANNEL_SPI0_RX
#define SPI0_TXDMA_CH_IDX       DMA_CHANNEL_SPI0_TX
#define SPI0_RXDMA_IRQ_IDX      DMA08_IRQn
#define SPI0_TXDMA_IRQ_IDX      DMA09_IRQn
#define spi0_rxdma_isr          DMA08_IRQHandler
#define spi0_txdma_isr          DMA09_IRQHandler
#if (PLF_AIC8800)
#define spi0_isr                SPI0_IRQHandler
#else
#define spi0_isr                SPI_IRQHandler
#endif

// spi_flash
#if (SPI_DEMO_FLASH)
#include "spi_api.h"
#endif
#define GPIO_IDX_FLS_CS         14

/*
 * GLOBAL CONSTANTS & VARIABLES
 ****************************************************************************************
 */
#if (SPI_DEMO_DMA)
#if SPI0_ISR_ENABLED
rtos_semaphore spi0_txend_sema;
#endif
#if SPI0_DMA_ISR_ENABLED
rtos_semaphore spi0_rxdma_sema;
rtos_semaphore spi0_txdma_sema;
#endif
#endif

/*
 * FUNCTIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief init spi, config iomux & clock div
 ****************************************************************************************
 */
#if (SPI_DEMO_RFIF || SPI_DEMO_DMA)
void spi0_init(void)
{
    uint32_t pclk;
    #if SPI0_DMA_ISR_ENABLED
    int ret;
    #endif

    // clk en
    #if (PLF_AIC8800)
    cpusysctrl_pclkme_set(CSC_PCLKME_SPI_EN_BIT);
    cpusysctrl_oclkme_set(CSC_OCLKME_SPI_EN_BIT);
    #if SPI0_DMA_ISR_ENABLED
    cpusysctrl_hclkme_set(CSC_HCLKME_DMA_EN_BIT);
    #endif
    #else
    cpusysctrl_pclkme_set(CPU_SYS_CTRL_PCLK_SPI_MANUAL_ENABLE);
    cpusysctrl_oclkme_set(CPU_SYS_CTRL_OTHERS_SPI_MANUAL_ENABLE);
    #if SPI0_DMA_ISR_ENABLED
    cpusysctrl_hclkme_set(CPU_SYS_CTRL_HCLK_DMA_MANUAL_ENABLE);
    #endif
    #endif

    pclk = sysctrl_clock_get(SYS_PCLK);
    spi_dr_div_setf(pclk / 2 / SPI_CLK_FREQ - 1);  // pclk/(2*(div+1)) = freq

    // iomux
    #if (PLF_AIC8800)
    iomux_gpio_config_sel_setf(10, 3); // clk
    iomux_gpio_config_sel_setf(11, 3); // cs
    #if !SPI0_3_WIRE_ENABLED
    iomux_gpio_config_sel_setf(12, 3); // di
    #endif
    iomux_gpio_config_sel_setf(13, 3); // do
    #elif (PLF_AIC8800MC)
    iomux_gpioa_config_sel_setf(10, 2); // clk
    iomux_gpioa_config_sel_setf(11, 2); // cs
#if !SPI0_3_WIRE_ENABLED
    iomux_gpioa_config_sel_setf(12, 2); // di
#endif
    iomux_gpioa_config_sel_setf(13, 2); // do
    #elif (PLF_AIC8800M40)
    iomux_gpioa_config_sel_setf(10, 3); // clk
    iomux_gpioa_config_sel_setf(11, 3); // cs
#if !SPI0_3_WIRE_ENABLED
    iomux_gpioa_config_sel_setf(12, 3); // di
#endif
    iomux_gpioa_config_sel_setf(13, 3); // do
    #endif

    #if SPI0_ISR_ENABLED
    AIC_SPI0->IER = (0x01UL << 8); // txend
    ret = rtos_semaphore_create(&spi0_txend_sema, 1, 0);
    if (ret) {
        dbg("sema create fail: %d\r\n", ret);
    }
    NVIC_SetPriority(SPI_IRQn, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(SPI_IRQn);
    #endif

    #if SPI0_DMA_ISR_ENABLED
    ret = rtos_semaphore_create(&spi0_rxdma_sema, 1, 0);
    if (ret) {
        dbg("sema create fail: %d\r\n", ret);
    }
    ret = rtos_semaphore_create(&spi0_txdma_sema, 1, 0);
    if (ret) {
        dbg("sema create fail: %d\r\n", ret);
    }
    NVIC_SetPriority(SPI0_RXDMA_IRQ_IDX, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(SPI0_RXDMA_IRQ_IDX);
    NVIC_SetPriority(SPI0_TXDMA_IRQ_IDX, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(SPI0_TXDMA_IRQ_IDX);
    #endif
}
#endif

#if (SPI_DEMO_RFIF)
/**
 ****************************************************************************************
 * @brief read register of RF interface
 ****************************************************************************************
 */
unsigned short rfif_spi_read(unsigned char addr)
{
    unsigned int rdata;

    AIC_SPI0->OCR   = 1; // out data cnt
    AIC_SPI0->ICR   = 1; // in data cnt
    AIC_SPI0->MR0   = ((0x01UL << 11) | (0x00UL <<  3)); // slave, generic mode
    AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (25 << 2)); // cs, bit count
    spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
    AIC_SPI0->CR[1] = ((0x03UL << 12) | (0x01UL <<  6)
        #if SPI0_3_WIRE_ENABLED
        | (0x01UL << 5)
        #endif
        ); // send and recv, cs, 3-wire
    AIC_SPI0->IOR   = ((0x01UL << 24) | (addr << 16) | 0x0000FFFFUL); // read, addr, dummy data
    AIC_SPI0->TCR   = (0x01UL << 1); // trans start
    for (rdata = 0; rdata < 0x1F; rdata++) { // simple delay
        __NOP();
    }
    do {
        rdata = AIC_SPI0->SR;
    } while (rdata & (0x01UL << 8));
    AIC_SPI0->CR[0] = (0x0FUL << 8);
    rdata = AIC_SPI0->IOR;

    return ((unsigned short)rdata);
}

/**
 ****************************************************************************************
 * @brief write register of RF interface
 ****************************************************************************************
 */
void rfif_spi_write(unsigned char addr, unsigned short data)
{
    unsigned int rdata;

    AIC_SPI0->OCR   = 1; // out data cnt
    AIC_SPI0->MR0   = ((0x01UL << 11) | (0x00UL <<  3)); // slave, generic mode
    AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (25 << 2)); // cs, bit count
    spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
    AIC_SPI0->CR[1] = ((0x02UL << 12) | (0x01UL <<  6)
        #if SPI0_3_WIRE_ENABLED
        | (0x01UL << 5)
        #endif
        ); // send and recv, cs, 3-wire
    AIC_SPI0->IOR   = ((0x00UL << 24) | (addr << 16) | data); // write, addr, data
    AIC_SPI0->TCR   = (0x01UL << 1); // trans start
    for (rdata = 0; rdata < 0x1F; rdata++) { // simple delay
        __NOP();
    }
    do {
        rdata = AIC_SPI0->SR;
    } while (rdata & (0x01UL << 8));
    AIC_SPI0->CR[0] = (0x0FUL << 8);
}

/**
 ****************************************************************************************
 * @brief read/write gen memory of RF interface
 ****************************************************************************************
 */
void rfif_gen_mem_rw(void)
{
    int addr;
    unsigned int data;

    rfif_spi_write(0xD5, 2);
    // write
    for (addr = 0; addr < 0x30000; addr++) {
        rfif_spi_write(0xD6, 0x0FFF & RW_GEN_MEM_DATA);
        //USER_PRINTF("addr=%08X, w 0xD6, ",addr);
        rfif_spi_write(0xD7, 0x0FFF & (RW_GEN_MEM_DATA >> 12));
        //USER_PRINTF("w 0xD7, ");
        rfif_spi_write(0xD8, 0x0000FFFF & addr);
        //USER_PRINTF("w 0xD8, ");
        rfif_spi_write(0xD9, 0x03 & (addr >> 16));
        //USER_PRINTF("w 0xD9, ");
        rfif_spi_write(0xFE, 0x01);
        //USER_PRINTF("w 0xFE\n");
        if ((addr & GEN_MEM_ADDR_MASK) == GEN_MEM_ADDR_MASK) {
            USER_PRINTF("  [%08X ~ %08X] wrote\n", (addr & ~GEN_MEM_ADDR_MASK), addr);
        }
    }
    // read
    for (addr = 0; addr < 0x30000; addr++) {
        rfif_spi_write(0xD8, 0x0000FFFF & addr);
        //USER_PRINTF("addr=%08X, w 0xD8, ",addr);
        rfif_spi_write(0xD9, 0x03 & (addr >> 16));
        //USER_PRINTF("w 0xD9, ");
        rfif_spi_write(0xFE, 0x02);
        //USER_PRINTF("w 0xFE, ");
        data = rfif_spi_read(0xEC);
        //USER_PRINTF("r 0xEC, ");
        data = (rfif_spi_read(0xED) << 12) | data;
        //USER_PRINTF("r 0xED\n");
        if (data != RW_GEN_MEM_DATA) {
            USER_PRINTF("gen mem rw err: addr=%d, w=%08X, r=%08X\n",addr,RW_GEN_MEM_DATA,data);
            break;
        } else if ((addr & GEN_MEM_ADDR_MASK) == GEN_MEM_ADDR_MASK) {
            USER_PRINTF("  [%08X ~ %08X] passed\n", (addr & ~GEN_MEM_ADDR_MASK), addr);
        }
    }
    if (addr == 0x30000) {
        USER_PRINTF("gen mem rw PASS\n");
    }
}

/**
 ****************************************************************************************
 * @brief read/write rxgain memory of RF interface
 ****************************************************************************************
 */
void rfif_rxgain_mem_rw(void)
{
    int addr;
    unsigned int data;

    rfif_spi_write(0x2F, 1);
    // write
    for (addr = 0; addr < 128; addr++) {
        rfif_spi_write(0x30, (addr << 9) | 0x01);
        rfif_spi_write(0x31, 0x0000FFFF & RW_TXRX_GAIN_MEM_DATA);
        rfif_spi_write(0x32, 0x0000FFFF & (RW_TXRX_GAIN_MEM_DATA >> 16));
        rfif_spi_write(0x7E, 0x01);
    }
    // read
    for (addr = 0; addr < 128; addr++) {
        rfif_spi_write(0x30, (addr << 9) | 0x01);
        rfif_spi_write(0x7E, 0x02);
        data = rfif_spi_read(0x64);
        rfif_spi_write(0x30, (addr << 9) | (0x01 << 8) | 0x01);
        rfif_spi_write(0x7E, 0x02);
        data = (rfif_spi_read(0x64) << 16) | data;
        if (data != RW_TXRX_GAIN_MEM_DATA) {
            USER_PRINTF("rxgain mem rw err: addr=%d, w=%08X, r=%08X\n",addr,RW_TXRX_GAIN_MEM_DATA,data);
            break;
        }
    }
    if (addr == 128) {
        USER_PRINTF("rxgain mem rw PASS\n");
    }
}

/**
 ****************************************************************************************
 * @brief read/write txgain memory of RF interface
 ****************************************************************************************
 */
void rfif_txgain_mem_rw(void)
{
    int addr;
    unsigned int data;

    rfif_spi_write(0x2F, 1);
    // write
    for (addr = 0; addr < 32; addr++) {
        rfif_spi_write(0x33, (addr << 9) | 0x01);
        rfif_spi_write(0x34, 0x0000FFFF & RW_TXRX_GAIN_MEM_DATA);
        rfif_spi_write(0x35, 0x0000FFFF & (RW_TXRX_GAIN_MEM_DATA >> 16));
        rfif_spi_write(0x7E, 0x04);
    }
    // read
    for (addr = 0; addr < 32; addr++) {
        rfif_spi_write(0x33, (addr << 9) | 0x01);
        rfif_spi_write(0x7E, 0x08);
        data = rfif_spi_read(0x65);
        rfif_spi_write(0x33, (addr << 9) | (0x01 << 8) | 0x01);
        rfif_spi_write(0x7E, 0x08);
        data = (rfif_spi_read(0x65) << 16) | data;
        if (data != RW_TXRX_GAIN_MEM_DATA) {
            USER_PRINTF("txgain mem rw err: addr=%d, w=%08X, r=%08X\n",addr,RW_TXRX_GAIN_MEM_DATA,data);
            break;
        }
    }
    if (addr == 32) {
        USER_PRINTF("txgain mem rw PASS\n");
    }
}
#endif

#if (SPI_DEMO_DMA)
/**
 ****************************************************************************************
 * @brief read func, blocking type
 ****************************************************************************************
 */
int spi0_dma_write_read_bytes(unsigned char *buff_wr, unsigned int byte_cnt_wr, unsigned char *buff_rd, unsigned int byte_cnt_rd)
{
    int ch = SPI0_TXDMA_CH_IDX;
    byte_cnt_wr = MIN(byte_cnt_wr, SPI0_DMA_BYTE_CNT_MAX);
    dma_erqcsr_set(REQ_CID_SPI_TX, ch);
    dma_ch_rqr_erqm_clrb(ch);
    dma_ch_rqr_erql_setb(ch);
    dma_ch_dar_set(ch, (unsigned int)(&AIC_SPI0->IOR));
    dma_ch_sar_set(ch, (unsigned int)buff_wr);
    dma_ch_tbl0cr_set(ch, ((1) | (REQ_TBL0 << DMA_CH_RQTYP_LSB) | (AHB_BYTE << DMA_CH_DBUSU_LSB) |
                             (AHB_WORD << DMA_CH_SBUSU_LSB) | DMA_CH_CONSTDA_BIT));
    dma_ch_tbl1cr_set(ch, byte_cnt_wr);
    dma_ch_tbl2cr_set(ch, byte_cnt_wr);
    dma_ch_tsr_set(ch, ((4 << DMA_CH_STRANSZ_LSB) | (1 << DMA_CH_DTRANSZ_LSB)));
    dma_ch_wmar_set(ch, 0);
    dma_ch_wjar_set(ch, 0);
    dma_ch_lnar_set(ch, 0);
    dma_ch_tbl0sr_set(ch, ((0 << DMA_CH_STBL0SZ_LSB) | (0 << DMA_CH_DTBL0SZ_LSB)));
    dma_ch_tbl1ssr_set(ch, 0);
    dma_ch_tbl1dsr_set(ch, 0);
    #if SPI0_DMA_ISR_ENABLED
    dma_ch_icsr_set(ch, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(ch, (DMA_CH_CHENA_BIT | (0x01UL << DMA_CH_BUSBU_LSB)));

    ch = SPI0_RXDMA_CH_IDX;
    byte_cnt_rd = MIN(byte_cnt_rd, SPI0_DMA_BYTE_CNT_MAX);
    dma_erqcsr_set(REQ_CID_SPI_RX, ch);
    dma_ch_rqr_erqm_clrb(ch);
    dma_ch_rqr_erql_setb(ch);
    dma_ch_dar_set(ch, (unsigned int)buff_rd);
    dma_ch_sar_set(ch, (unsigned int)(&AIC_SPI0->IOR));
    dma_ch_tbl0cr_set(ch, ((1) | (REQ_TBL0 << DMA_CH_RQTYP_LSB) | (AHB_WORD << DMA_CH_DBUSU_LSB) |
                             (AHB_BYTE << DMA_CH_SBUSU_LSB) | DMA_CH_CONSTSA_BIT));
    dma_ch_tbl1cr_set(ch, byte_cnt_rd);
    dma_ch_tbl2cr_set(ch, byte_cnt_rd);
    dma_ch_tsr_set(ch, ((1 << DMA_CH_STRANSZ_LSB) | (4 << DMA_CH_DTRANSZ_LSB)));
    dma_ch_wmar_set(ch, 0);
    dma_ch_wjar_set(ch, 0);
    dma_ch_lnar_set(ch, 0);
    dma_ch_tbl0sr_set(ch, ((0 << DMA_CH_STBL0SZ_LSB) | (0 << DMA_CH_DTBL0SZ_LSB)));
    dma_ch_tbl1ssr_set(ch, 0);
    dma_ch_tbl1dsr_set(ch, 0);
    #if SPI0_DMA_ISR_ENABLED
    dma_ch_icsr_set(ch, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(ch, (DMA_CH_CHENA_BIT | (0x01UL << DMA_CH_BUSBU_LSB)));

    AIC_SPI0->OCR   = byte_cnt_wr; // out data cnt
    AIC_SPI0->ICR   = byte_cnt_rd; // in data cnt
    AIC_SPI0->MR0   = ((0x01UL << 11) | (0x00UL <<  3)); // slave, generic mode
    AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (8 << 2)); // cs, bit count
    spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
    AIC_SPI0->CR[1] = ((0x03UL << 12) | (0x01UL <<  6)
        #if SPI0_3_WIRE_ENABLED
        | (0x01UL << 5)
        #endif
        ); // send and recv, cs, 3-wire
    AIC_SPI0->CR[2] = (0x01UL <<  6); // en dma
    AIC_SPI0->CR[3] = ((0x02UL << 8) | (0x01UL << 0));
    AIC_SPI0->TCR   = (0x01UL << 1); // trans start

    #if SPI0_DMA_ISR_ENABLED
    rtos_semaphore_wait(spi0_rxdma_sema, -1);
    #else
    while (dma_ch_icsr_tbl2_irst_getb(ch) == 0);
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    #endif

    AIC_SPI0->CR[0] = (0x0FUL << 8); // cs
    AIC_SPI0->CR[2] = 0x00UL;
    AIC_SPI0->TCR   = 0x00UL;

    return 0;
}

int spi0_dma_read_bytes(unsigned char *buff_rd, unsigned int byte_cnt_rd)
{
    int ch = SPI0_RXDMA_CH_IDX;
    byte_cnt_rd = MIN(byte_cnt_rd, SPI0_DMA_BYTE_CNT_MAX);
    dma_erqcsr_set(REQ_CID_SPI_RX, ch);
    dma_ch_rqr_erqm_clrb(ch);
    dma_ch_rqr_erql_setb(ch);
    dma_ch_dar_set(ch, (unsigned int)buff_rd);
    dma_ch_sar_set(ch, (unsigned int)(&AIC_SPI0->IOR));
    dma_ch_tbl0cr_set(ch, ((1) | (REQ_TBL0 << DMA_CH_RQTYP_LSB) | (AHB_WORD << DMA_CH_DBUSU_LSB) |
                             (AHB_BYTE << DMA_CH_SBUSU_LSB) | DMA_CH_CONSTSA_BIT));
    dma_ch_tbl1cr_set(ch, byte_cnt_rd);
    dma_ch_tbl2cr_set(ch, byte_cnt_rd);
    dma_ch_tsr_set(ch, ((1 << DMA_CH_STRANSZ_LSB) | (4 << DMA_CH_DTRANSZ_LSB)));
    dma_ch_wmar_set(ch, 0);
    dma_ch_wjar_set(ch, 0);
    dma_ch_lnar_set(ch, 0);
    dma_ch_tbl0sr_set(ch, ((0 << DMA_CH_STBL0SZ_LSB) | (0 << DMA_CH_DTBL0SZ_LSB)));
    dma_ch_tbl1ssr_set(ch, 0);
    dma_ch_tbl1dsr_set(ch, 0);
    #if SPI0_DMA_ISR_ENABLED
    dma_ch_icsr_set(ch, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(ch, (DMA_CH_CHENA_BIT | (0x01UL << DMA_CH_BUSBU_LSB)));

    AIC_SPI0->OCR   = byte_cnt_rd; // out data cnt
    AIC_SPI0->ICR   = byte_cnt_rd; // in data cnt
    AIC_SPI0->MR0   = ((0x01UL << 11) | (0x00UL <<  3)); // slave, generic mode
    AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (8 << 2)); // cs, bit count
    spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
    AIC_SPI0->CR[1] = ((0x01UL << 12) | (0x01UL <<  6)
        #if SPI0_3_WIRE_ENABLED
        | (0x01UL << 5)
        #endif
        ); // recv, cs, 3-wire
    AIC_SPI0->CR[2] = (0x01UL <<  6); // en dma
    AIC_SPI0->CR[3] = ((0x02UL << 8) | (0x01UL << 0));
    AIC_SPI0->TCR   = (0x01UL << 1); // trans start

    #if SPI0_DMA_ISR_ENABLED
    rtos_semaphore_wait(spi0_rxdma_sema, -1);
    #else
    while (dma_ch_icsr_tbl2_irst_getb(ch) == 0);
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    #endif

    AIC_SPI0->CR[0] = (0x0FUL << 8); // cs
    AIC_SPI0->CR[2] = 0x00UL;
    AIC_SPI0->TCR   = 0x00UL;

    return 0;
}

/**
 ****************************************************************************************
 * @brief write func, blocking type
 ****************************************************************************************
 */
int spi0_dma_write_bytes(unsigned char *buff_wr, unsigned int byte_cnt)
{
    const int ch = SPI0_TXDMA_CH_IDX;
    byte_cnt = MIN(byte_cnt, SPI0_DMA_BYTE_CNT_MAX);

    dma_erqcsr_set(REQ_CID_SPI_TX, ch);
    dma_ch_rqr_erqm_clrb(ch);
    dma_ch_rqr_erql_setb(ch);
    dma_ch_dar_set(ch, (unsigned int)(&AIC_SPI0->IOR));
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
    #if SPI0_DMA_ISR_ENABLED
    dma_ch_icsr_set(ch, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(ch, (DMA_CH_CHENA_BIT | (0x01UL << DMA_CH_BUSBU_LSB)));

    AIC_SPI0->OCR   = byte_cnt; // out data cnt
    AIC_SPI0->MR0   = ((0x01UL << 11) | (0x00UL <<  3)); // slave, generic mode
    AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (8 << 2)); // cs, bit count
    spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
    AIC_SPI0->CR[1] = ((0x02UL << 12) | (0x01UL <<  6)
        #if SPI0_3_WIRE_ENABLED
        | (0x01UL << 5)
        #endif
        ); // send, cs, 3-wire
    AIC_SPI0->CR[2] = (0x01UL <<  6); // en dma
    AIC_SPI0->TCR   = (0x01UL << 1); // trans start

    #if SPI0_DMA_ISR_ENABLED
    rtos_semaphore_wait(spi0_txdma_sema, -1);
    #else
    while (dma_ch_icsr_tbl2_irst_getb(ch) == 0);
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    #endif

    #if SPI0_ISR_ENABLED
    rtos_semaphore_wait(spi0_txend_sema, -1);
    #else
    while (AIC_SPI0->SR & (0x01UL << 8)); // busy
    #endif
    AIC_SPI0->CR[0] = (0x0FUL << 8); // cs
    AIC_SPI0->CR[2] = 0x00UL;
    AIC_SPI0->TCR   = 0x00UL;

    return 0;
}

int spi0_dma_write_words(unsigned int *buff_wr, unsigned int word_cnt)
{
    const int ch = SPI0_TXDMA_CH_IDX;
    unsigned int byte_cnt = MIN(word_cnt * 4, SPI0_DMA_BYTE_CNT_MAX);

    dma_erqcsr_set(REQ_CID_SPI_TX, ch);
    dma_ch_rqr_erqm_clrb(ch);
    dma_ch_rqr_erql_setb(ch);
    dma_ch_dar_set(ch, (unsigned int)(&AIC_SPI0->IOR));
    dma_ch_sar_set(ch, (unsigned int)buff_wr);
    dma_ch_tbl0cr_set(ch, ((4) | (REQ_TBL0 << DMA_CH_RQTYP_LSB) | (AHB_WORD << DMA_CH_DBUSU_LSB) |
                             (AHB_WORD << DMA_CH_SBUSU_LSB) | DMA_CH_CONSTDA_BIT));
    dma_ch_tbl1cr_set(ch, byte_cnt);
    dma_ch_tbl2cr_set(ch, byte_cnt);
    dma_ch_tsr_set(ch, ((4 << DMA_CH_STRANSZ_LSB) | (4 << DMA_CH_DTRANSZ_LSB)));
    dma_ch_wmar_set(ch, 0);
    dma_ch_wjar_set(ch, 0);
    dma_ch_lnar_set(ch, 0);
    dma_ch_tbl0sr_set(ch, ((0 << DMA_CH_STBL0SZ_LSB) | (0 << DMA_CH_DTBL0SZ_LSB)));
    dma_ch_tbl1ssr_set(ch, 0);
    dma_ch_tbl1dsr_set(ch, 0);
    #if SPI0_DMA_ISR_ENABLED
    dma_ch_icsr_set(ch, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(ch, (DMA_CH_CHENA_BIT | (0x01UL << DMA_CH_BUSBU_LSB)));

    AIC_SPI0->OCR   = word_cnt; // out data cnt
    AIC_SPI0->MR0   = ((0x01UL << 11) | (0x00UL <<  3)); // slave, generic mode
    AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (0 << 2)); // cs, bit count
    spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
    AIC_SPI0->CR[1] = ((0x02UL << 12) | (0x01UL <<  6)
        #if SPI0_3_WIRE_ENABLED
        | (0x01UL << 5)
        #endif
        ); // send, cs, 3-wire
    AIC_SPI0->CR[2] = (0x01UL <<  6); // en dma
    AIC_SPI0->TCR   = (0x01UL << 1); // trans start

    #if SPI0_DMA_ISR_ENABLED
    rtos_semaphore_wait(spi0_txdma_sema, -1);
    #else
    while (dma_ch_icsr_tbl2_irst_getb(ch) == 0);
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    #endif

    #if SPI0_ISR_ENABLED
    rtos_semaphore_wait(spi0_txend_sema, -1);
    #else
    while (AIC_SPI0->SR & (0x01UL << 8)); // busy
    #endif
    AIC_SPI0->CR[0] = (0x0FUL << 8); // cs
    AIC_SPI0->CR[2] = 0x00UL;
    AIC_SPI0->TCR   = 0x00UL;

    return 0;
}

#if SPI0_ISR_ENABLED
void spi0_isr(void)
{
    uint32_t int_st = AIC_SPI0->IMSR;
    AIC_SPI0->ICLR = int_st;
    //USER_PRINTF("INT:%x\r\n", int_st);
    if (int_st & (0x01UL << 8)) { // txend
        rtos_semaphore_signal(spi0_txend_sema, true);
    }
}
#endif

#if SPI0_DMA_ISR_ENABLED
void spi0_rxdma_isr(void)
{
    const int ch = SPI0_RXDMA_CH_IDX;
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    rtos_semaphore_signal(spi0_rxdma_sema, true);
}

void spi0_txdma_isr(void)
{
    const int ch = SPI0_TXDMA_CH_IDX;
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    rtos_semaphore_signal(spi0_txdma_sema, true);
}
#endif
#endif

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void spi0_test(void)
{
    #if (SPI_DEMO_DMA)
    static unsigned int test_buf_wr[] = {
        0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x80604020, 0x00e0c0a0, 0x70503010, 0xf0d0b090,
    };
    unsigned char test_buf_rd[8] = {0x0F,0xE0,};
    #endif
    #if (SPI_DEMO_FLASH)
    spim_cfg_t spim_cfg = {
        .cs = SPI_CS1,
        .dc = SPI_DC_NONE,
        .spi_mode = SPI_MODE_GENERIC,
        .clk_freq = SPI_CLK_FREQ,
        .clk_mode = SPI_CR_CLK_MODE_0,
        .bit_cnt = 8,
        .gpa_idx_cs = GPIO_IDX_FLS_CS,
    };
    unsigned char test_buf_rd[8] = {0,};
    #endif

    USER_PRINTF("\nStart test case: spi0\n");

    #if (SPI_DEMO_RFIF || SPI_DEMO_DMA)
    spi0_init();
    #endif

    #if (SPI_DEMO_RFIF)
    // Test RF interface memory through SPI
    USER_PRINTF("gen mem rw:\n");
    rfif_gen_mem_rw();

    USER_PRINTF("rx gain mem rw:\n");
    rfif_rxgain_mem_rw();

    USER_PRINTF("tx gain mem rw:\n");
    rfif_txgain_mem_rw();

    USER_PRINTF("RFIntf Mem R/W Test Done\n");
    #endif

    #if (SPI_DEMO_DMA)
    //spi0_dma_write_bytes((unsigned char *)test_buf_wr, 8);
    spi0_dma_write_words(test_buf_wr, 8);
    spi0_dma_write_read_bytes((unsigned char *)test_buf_wr, 8, test_buf_rd, sizeof(test_buf_rd));
    //spi0_dma_read_bytes((unsigned char *)test_buf_rd, sizeof(test_buf_rd));
    for (int i = 0; i < 8; i++) {
        USER_PRINTF("buf_rd:");
        USER_PRINTF(" %02x\n", test_buf_rd[i]);
    }
    #endif

    #if (SPI_DEMO_FLASH)
    spim_init(&spim_cfg);
    spim_write_byte(&spim_cfg, 0x9F, false);
    test_buf_rd[0] = spim_read_byte(&spim_cfg, false);
    test_buf_rd[1] = spim_read_byte(&spim_cfg, false);
    test_buf_rd[2] = spim_read_byte(&spim_cfg, true);
    USER_PRINTF("buf_rd = %02X, %02X, %02X\n", test_buf_rd[0], test_buf_rd[1], test_buf_rd[2]);
    #endif

    USER_PRINTF("\nspi0 test done\n");
}

#endif /* CFG_TEST_SPI0 */
