/**
 ****************************************************************************************
 *
 * @file i2cm_api.c
 * @Target aic8800mc
 * @brief-channal
 * --------------------------I2CM_CHANNAL_TABLE----------------------
 * |     Select     |   CHAN_1  |   CHAN_2  |   CHAN_3  |   CHAN_4  |
 * |    I2CM_SCL    |    PA0    |    PA2    |    PA6    |    PA14   |
 * |    I2CM_SDA    |    PA1    |    PA3    |    PA7    |    PA15   |
 * ------------------------------------------------------------------
 * The I2CM perihperal has four CHANNAL. Only one can be use at the same time!
 ****************************************************************************************
 */

/*
 * INCLUDES
 ****************************************************************************************
 */
#include "i2cm_api.h"
#include "reg_dma.h"
#include "dma_generic.h"

void i2cm_init(int i2cm_chan)
{
    switch(i2cm_chan) {
        case(I2CM_CHANNAL_1):
            iomux_gpioa_config_sel_setf(0, 2);
            iomux_gpioa_config_sel_setf(1, 2);
            break;
        case(I2CM_CHANNAL_2):
            iomux_gpioa_config_sel_setf(2, 3);
            iomux_gpioa_config_sel_setf(3, 3);
            break;
        case(I2CM_CHANNAL_3):
            iomux_gpioa_config_sel_setf(6, 1);
            iomux_gpioa_config_sel_setf(7, 1);
            break;
        case(I2CM_CHANNAL_4):
            iomux_gpioa_config_sel_setf(14, 1);
            iomux_gpioa_config_sel_setf(15, 1);
            break;
        default:
            I2CM_DEBUG_PRINTF("Param Error!\n");
            break;
    }

    // disable device
    AIC_I2CM0->IC_CON        = 0x0;
    // disable all interrupts
    AIC_I2CM0->IC_INTR_MASK  = 0x0;
    // reset instance variables
    cpusysctrl_pclkrs_set(CPU_SYS_CTRL_PRESETN_I2CM_SET | CPU_SYS_CTRL_PRESETN_MOD_I2CM_SET);
    cpusysctrl_pclkrc_set(CPU_SYS_CTRL_PRESETN_I2CM_CLEAR | CPU_SYS_CTRL_PRESETN_MOD_I2CM_CLEAR);

    #if I2CM_DMA_ISR
    int ret = rtos_semaphore_create(&i2cm_txdma_sema, 1, 0);
    if (ret) {
        dbg("sema create fail: %d\r\n", ret);
    }
    ret = rtos_semaphore_create(&i2cm_rxdma_sema, 1, 0);
    if (ret) {
        dbg("sema create fail: %d\r\n", ret);
    }

    NVIC_SetVector(DMA09_IRQn, (uint32_t)i2cm_txdma_handler);
    NVIC_ClearPendingIRQ(DMA09_IRQn);
    NVIC_SetPriority(DMA09_IRQn, __NVIC_PRIO_LOWEST);
    NVIC_DisableIRQ(DMA09_IRQn);

    NVIC_SetVector(DMA08_IRQn, (uint32_t)i2cm_rxdma_handler);
    NVIC_ClearPendingIRQ(DMA08_IRQn);
    NVIC_SetPriority(DMA08_IRQn, __NVIC_PRIO_LOWEST);
    NVIC_DisableIRQ(DMA08_IRQn);
    #endif
}

void i2cm_clock_setup(uint32_t ic_clk, uint32_t ic_speed_mode)
{
    unsigned int ss_scl_high, ss_scl_low;
    unsigned int fs_scl_high, fs_scl_low;
    unsigned int hs_scl_high, hs_scl_low;

    // ic_clk is the clock speed (in MHz) that is being supplied to the
    // DW_apb_i2c device.  The correct clock count values are determined
    // by using this inconjunction with the minimum high and low signal
    // hold times as per the I2C bus specification.
    ss_scl_high = ((unsigned int) (((SS_MIN_SCL_HIGH * ic_clk) / 1000) + 1));
    ss_scl_low  = ((unsigned int) (((SS_MIN_SCL_LOW * ic_clk) / 1000) + 1));
    fs_scl_high = ((unsigned int) (((FS_MIN_SCL_HIGH * ic_clk) / 1000) + 1));
    fs_scl_low  = ((unsigned int) (((FS_MIN_SCL_LOW * ic_clk) / 1000) + 1));
    hs_scl_high = ((unsigned int) (((HS_MIN_SCL_HIGH_100PF * ic_clk) / 1000) + 1));
    hs_scl_low  = ((unsigned int) (((HS_MIN_SCL_LOW_100PF * ic_clk) / 1000) + 1));

    uint32_t retval;
    retval = AIC_I2CM0->IC_CON;
    if((retval & I2CM_SPEED(0x3)) != I2CM_SPEED(ic_speed_mode)) {
        retval &= ~(I2CM_SPEED(0x3));
        AIC_I2CM0->IC_CON = retval | I2CM_SPEED(ic_speed_mode);
    }

    if(ic_speed_mode == I2C_SPEED_STANDARD) {
        I2CM_DEBUG_PRINTF("set I2C_SPEED_STANDARD\n");
        AIC_I2CM0->IC_SS_SCL_LCNT = I2CM_IC_SS_SCL_LCNT(ss_scl_low);
        AIC_I2CM0->IC_SS_SCL_HCNT = I2CM_IC_SS_SCL_HCNT(ss_scl_high);

    } else if (ic_speed_mode == I2C_SPEED_FAST) {
        I2CM_DEBUG_PRINTF("set I2C_SPEED_FAST\n");
        AIC_I2CM0->IC_FS_SCL_LCNT = I2CM_IC_FS_SCL_LCNT(fs_scl_low);
        AIC_I2CM0->IC_FS_SCL_HCNT = I2CM_IC_FS_SCL_HCNT(fs_scl_high);
    } else if (ic_speed_mode == I2C_SPEED_HIGH) {
        I2CM_DEBUG_PRINTF("set I2C_SPEED_HIGH\n");
        AIC_I2CM0->IC_HS_SCL_HCNT = I2CM_IC_HS_SCL_HCNT(hs_scl_high);
        AIC_I2CM0->IC_HS_SCL_LCNT = I2CM_IC_HS_SCL_LCNT(hs_scl_low);
    } else {
        I2CM_DEBUG_PRINTF("Param Error!\n");
    }
}

void i2cm_setMode(uint32_t ic_device_addr)
{
    uint32_t retval;
    retval = AIC_I2CM0->IC_CON;
    // use 7-bit addressing
    if((retval & I2CM_IC_10BITADDR_SLAVE) == I2CM_IC_10BITADDR_SLAVE) {
        retval &= ~I2CM_IC_10BITADDR_SLAVE;
        AIC_I2CM0->IC_CON = retval;
    }

    // use target address when initiating transfer
    // I2c_tx_target     = 0x0,        // normal transfer using target address
    // I2c_tx_gen_call   = 0x2,        // issue a general call
    // I2c_tx_start_byte = 0x3         // issue a start byte I2C command
    retval = AIC_I2CM0->IC_TAR;
    if((retval & (I2CM_GC_OR_START | I2CM_SPECIAL)) != 0x0) {
        retval &= ~(I2CM_GC_OR_START | I2CM_SPECIAL);
        AIC_I2CM0->IC_TAR = retval;
    }

    if((retval & I2CM_IC_TAR(0x3ff)) != I2CM_IC_TAR(ic_device_addr)) {
        retval &= ~(I2CM_IC_TAR(0x3ff));
        AIC_I2CM0->IC_TAR = retval | I2CM_IC_TAR(ic_device_addr);
    }
}

void delay_about_1ns(uint32_t num)
{
    uint32_t i;
    for(i=0; i<num; i++)
        __NOP();
}

/* i2c single write and read */
uint8_t i2cm_byte_rd(uint8_t raddr)
{
    uint32_t rdata;
    I2CM_DEBUG_PRINTF("i2cm byte read start !!!\n");
    AIC_I2CM0->IC_CON        |= I2CM_IC_RESTART_EN | I2CM_MASTER_MODE;
    AIC_I2CM0->IC_ENABLE     |= I2CM_ENABLE;
    AIC_I2CM0->IC_DATA_CMD    = I2CM_DAT(raddr);
    //delay_about_1ns(50000);

    rdata = 0xffffffff;
    while((rdata & I2CM_MAT_ACTIVITY) == I2CM_MAT_ACTIVITY)
    {
        rdata = AIC_I2CM0->IC_STATUS;
    }

    AIC_I2CM0->IC_DATA_CMD = I2CM_CMD | I2CM_DAT(0x0);
    //delay_about_1ns(50000);

    rdata = 0xffffffff;
    while((rdata & I2CM_MAT_ACTIVITY) == I2CM_MAT_ACTIVITY)
    {
        rdata = AIC_I2CM0->IC_STATUS;
    }
    return(AIC_I2CM0->IC_DATA_CMD);
}

void i2cm_addr_wr(uint8_t waddr, uint8_t wdata)
{
    uint32_t rdata;
    I2CM_DEBUG_PRINTF("i2cm byte write start !!!\n");
    AIC_I2CM0->IC_CON        |= I2CM_IC_RESTART_EN | I2CM_MASTER_MODE;
    AIC_I2CM0->IC_ENABLE     |= I2CM_ENABLE;
    AIC_I2CM0->IC_DATA_CMD    = I2CM_DAT(waddr);
    AIC_I2CM0->IC_DATA_CMD    = I2CM_DAT(wdata);
    //delay_about_1ns(50000);

    rdata=0xffffffff;
    while((rdata & I2CM_MAT_ACTIVITY) == I2CM_MAT_ACTIVITY)
    {
        rdata = AIC_I2CM0->IC_STATUS;
    }
}

/* i2c dma write and read */
#if I2CM_DMA_ISR
void i2cm_txdma_handler(void)
{
    dma_ch_icsr_set(I2CM_TXDMA_CH_IDX, (dma_ch_icsr_get(I2CM_TXDMA_CH_IDX) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    rtos_semaphore_signal(i2cm_txdma_sema, true);
}
void i2cm_rxdma_handler(void)
{
    dma_ch_icsr_set(I2CM_RXDMA_CH_IDX, (dma_ch_icsr_get(I2CM_RXDMA_CH_IDX) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    rtos_semaphore_signal(i2cm_rxdma_sema, true);
}
#endif

void i2cm_dma_wr(uint32_t i2c_wlen, uint32_t *wbuff)
{
    I2CM_DEBUG_PRINTF("i2cm dma write start\n"
                      "7bit device addr + 1bit write + 8bit reg addr + 8 bit wdata ... %d !!!\n", i2c_wlen);

    dma_ch_rqr_erqm_clrb(I2CM_TXDMA_CH_IDX);
    dma_ch_rqr_erql_setb(I2CM_TXDMA_CH_IDX);
    dma_ch_sar_set(I2CM_TXDMA_CH_IDX, (unsigned int)wbuff);
    dma_ch_dar_set(I2CM_TXDMA_CH_IDX, (unsigned int)(&AIC_I2CM0->IC_DATA_CMD));
    dma_ch_tbl0cr_set(I2CM_TXDMA_CH_IDX, (4 | (0 << DMA_CH_RQTYP_LSB) |
                      (2 << DMA_CH_DBUSU_LSB) | (2 << DMA_CH_SBUSU_LSB) | DMA_CH_CONSTDA_BIT));
    dma_ch_tbl1cr_set(I2CM_TXDMA_CH_IDX, ((i2c_wlen<<2)&0x1FFFF));
    dma_ch_tbl2cr_set(I2CM_TXDMA_CH_IDX, ((i2c_wlen<<2)&0xFFFFFFF));
    dma_ch_tsr_set(I2CM_TXDMA_CH_IDX, ((4 << DMA_CH_STRANSZ_LSB) | (4 << DMA_CH_DTRANSZ_LSB)));
    dma_ch_wmar_set(I2CM_TXDMA_CH_IDX, 0);
    dma_ch_wjar_set(I2CM_TXDMA_CH_IDX, 0);
    dma_ch_lnar_set(I2CM_TXDMA_CH_IDX, 0);
    dma_ch_tbl0sr_set(I2CM_TXDMA_CH_IDX, ((0 << DMA_CH_STBL0SZ_LSB) | (0 << DMA_CH_DTBL0SZ_LSB)));
    dma_ch_tbl1ssr_set(I2CM_TXDMA_CH_IDX, 0);
    dma_ch_tbl1dsr_set(I2CM_TXDMA_CH_IDX, 0);
    dma_erqcsr_set(REQ_CID_I2CM_TX, I2CM_TXDMA_CH_IDX);
    AIC_DMA->CH[I2CM_TXDMA_CH_IDX].RQR = DMA_CH_ERQL_BIT;

    #if I2CM_DMA_ISR
    dma_ch_icsr_set(I2CM_TXDMA_CH_IDX, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(I2CM_TXDMA_CH_IDX, (DMA_CH_CHENA_BIT | (0x01UL << DMA_CH_BUSBU_LSB)));

    #if I2CM_DMA_ISR
    NVIC_EnableIRQ(DMA09_IRQn);
    #endif

    // i2c configure, prepare to write multi byte.
    AIC_I2CM0->IC_CON     |= I2CM_IC_RESTART_EN | I2CM_MASTER_MODE;
    AIC_I2CM0->IC_ENABLE  |= I2CM_ENABLE;
    AIC_I2CM0->IC_DMA_CR   = I2CM_TDMAE;
    AIC_I2CM0->IC_DMA_TDLR = I2CM_DMATDL(0x8);

    // Wait dma finish
    #if I2CM_DMA_ISR
    rtos_semaphore_wait(i2cm_txdma_sema, -1);
    #else
    delay_about_1ns(50000);
    while (dma_ch_icsr_tbl2_irst_getb(I2CM_TXDMA_CH_IDX) == 0);
    dma_ch_icsr_set(I2CM_TXDMA_CH_IDX, (dma_ch_icsr_get(I2CM_TXDMA_CH_IDX) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    #endif

    // Wait i2cm finish
    uint32_t rdata = 0xffffffff;
    while((rdata & I2CM_MAT_ACTIVITY) == I2CM_MAT_ACTIVITY) {
        rdata = AIC_I2CM0->IC_STATUS;
    }
    I2CM_DEBUG_PRINTF("I2CM write finish.\n");

    AIC_I2CM0->IC_CON = 0;
    AIC_I2CM0->IC_ENABLE = 0;
    AIC_I2CM0->IC_DMA_CR = 0;
    dma_ch_ctlr_set(I2CM_TXDMA_CH_IDX, 0);

    #if I2CM_DMA_ISR
    NVIC_DisableIRQ(DMA09_IRQn);
    #endif
}

void i2cm_dma_rd(uint32_t i2c_raddr, uint32_t i2c_rlen, uint32_t *rbuff)
{
    I2CM_DEBUG_PRINTF("i2cm dma read start\n"
                      "7bit device addr + 1bit write + 8bit reg addr +  start 7bit device addr + 1bit read + rdata ...!!!\n");

    dma_ch_rqr_erqm_clrb(I2CM_RXDMA_CH_IDX);
    dma_ch_rqr_erql_setb(I2CM_RXDMA_CH_IDX);
    dma_ch_sar_set(I2CM_RXDMA_CH_IDX, (unsigned int)(&AIC_I2CM0->IC_DATA_CMD));
    dma_ch_dar_set(I2CM_RXDMA_CH_IDX, (unsigned int)rbuff);
    dma_ch_tbl0cr_set(I2CM_RXDMA_CH_IDX, (4 | (0 << DMA_CH_RQTYP_LSB) |
                      (2 << DMA_CH_DBUSU_LSB) | (2 << DMA_CH_SBUSU_LSB) | DMA_CH_CONSTDA_BIT));
    dma_ch_tbl1cr_set(I2CM_RXDMA_CH_IDX, ((i2c_rlen<<2)&0x1FFFF));
    dma_ch_tbl2cr_set(I2CM_RXDMA_CH_IDX, ((i2c_rlen<<2)&0xFFFFFFF));
    dma_ch_tsr_set(I2CM_RXDMA_CH_IDX, ((4 << DMA_CH_STRANSZ_LSB) | (4 << DMA_CH_DTRANSZ_LSB)));
    dma_ch_wmar_set(I2CM_RXDMA_CH_IDX, 0);
    dma_ch_wjar_set(I2CM_RXDMA_CH_IDX, 0);
    dma_ch_lnar_set(I2CM_RXDMA_CH_IDX, 0);
    dma_ch_tbl0sr_set(I2CM_RXDMA_CH_IDX, ((0 << DMA_CH_STBL0SZ_LSB) | (0 << DMA_CH_DTBL0SZ_LSB)));
    dma_ch_tbl1ssr_set(I2CM_RXDMA_CH_IDX, 0);
    dma_ch_tbl1dsr_set(I2CM_RXDMA_CH_IDX, 0);
    dma_erqcsr_set(REQ_CID_I2CM_RX, I2CM_RXDMA_CH_IDX);
    AIC_DMA->CH[I2CM_RXDMA_CH_IDX].RQR = DMA_CH_ERQL_BIT;

    #if I2CM_DMA_ISR
    dma_ch_icsr_set(I2CM_RXDMA_CH_IDX, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(I2CM_RXDMA_CH_IDX, (DMA_CH_CHENA_BIT | (0x01UL << DMA_CH_BUSBU_LSB)));

    #if I2CM_DMA_ISR
    NVIC_EnableIRQ(DMA08_IRQn);
    #endif

    // i2c configure, write reg-address which will read.
    AIC_I2CM0->IC_CON        |= I2CM_IC_RESTART_EN | I2CM_MASTER_MODE;
    AIC_I2CM0->IC_ENABLE     |= I2CM_ENABLE;
    AIC_I2CM0->IC_DMA_CR     |= I2CM_RDMAE;
    AIC_I2CM0->IC_DMA_RDLR   |= I2CM_DMARDL(0x0);
    AIC_I2CM0->IC_DATA_CMD    = I2CM_DAT(i2c_raddr);
    //delay_about_1ns(100000);

    uint32_t rdata = 0xffffffff;
    while((rdata & I2CM_MAT_ACTIVITY) == I2CM_MAT_ACTIVITY) {
        rdata = AIC_I2CM0->IC_STATUS;
    }

    // Write cmd to read device.
    AIC_I2CM0->IC_DATA_CMD = I2CM_CMD | I2CM_DAT(0x0);

    // Wait dma finish
    #if I2CM_DMA_ISR
    rtos_semaphore_wait(i2cm_rxdma_sema, -1);
    #else
    while (dma_ch_icsr_tbl2_irst_getb(I2CM_RXDMA_CH_IDX) == 0);
    dma_ch_icsr_set(I2CM_RXDMA_CH_IDX, (dma_ch_icsr_get(I2CM_RXDMA_CH_IDX) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    #endif
    I2CM_DEBUG_PRINTF("I2CM read finish.\n");

    AIC_I2CM0->IC_CON = 0;
    AIC_I2CM0->IC_ENABLE = 0;
    dma_ch_ctlr_set(I2CM_RXDMA_CH_IDX, 0);

    #if I2CM_DMA_ISR
    NVIC_DisableIRQ(DMA08_IRQn);
    #endif
}


