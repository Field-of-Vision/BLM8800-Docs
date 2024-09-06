#ifndef __I2CM_API_H_
#define __I2CM_API_H_

#include "reg_sysctrl.h"
#include "reg_i2cm.h"
#include "reg_iomux.h"
#include "dbg.h"

#define I2CM_DEBUG_PRINTF(fmt, ...)             //dbg(fmt, ##__VA_ARGS__)

/*
 * These minimum high and low times are in nanoseconds.  They represent
 * the minimum amount of time a bus signal must remain either high or
 * low to be interpreted as a logical high or low as per the I2C bus
 * protocol.  These values are used in conjunction with an I2C input
 * clock frequency to determine the correct values to be written to the
 * clock count registers.
 */
#define SS_MIN_SCL_HIGH         4000
#define SS_MIN_SCL_LOW          5910
#define FS_MIN_SCL_HIGH         600
#define FS_MIN_SCL_LOW          1810
#define HS_MIN_SCL_HIGH_100PF   70
#define HS_MIN_SCL_LOW_100PF    134

#define I2CM_DMA_ISR            (1 && defined(CFG_RTOS))
#define I2CM_RXDMA_CH_IDX       DMA_CHANNEL_I2CM_RX
#define I2CM_TXDMA_CH_IDX       DMA_CHANNEL_I2CM_TX

#define DEV_ADDR_MPU            (0x68)   // Use MPU-6050 as I2C_DEVICE
#define DEV_ADDR_ADXL           (0x53)   // Use ADXL345 as I2C_DEVICE

#if I2CM_DMA_ISR
#include "rtos_al.h"
rtos_semaphore i2cm_txdma_sema;
rtos_semaphore i2cm_rxdma_sema;
#endif

enum I2CM_CHANNAL {
    I2CM_CHANNAL_1,
    I2CM_CHANNAL_2,
    I2CM_CHANNAL_3,
    I2CM_CHANNAL_4
};

enum I2CM_SPEED {
    I2C_SPEED_STANDARD = 1, // standard speed (100 kbps)
    I2C_SPEED_FAST     = 2, // fast speed     (400 kbps)
    I2C_SPEED_HIGH     = 3, // high speed     (3.4 Mbps)
};

void i2cm_init(int i2cm_chan);
void i2cm_clock_setup(uint32_t ic_clk, uint32_t ic_speed_mode);
void i2cm_setMode(uint32_t ic_device_addr);

uint8_t i2cm_byte_rd(uint8_t raddr);
void i2cm_addr_wr(uint8_t waddr, uint8_t wdata);
void i2cm_dma_rd(uint32_t i2c_raddr, uint32_t i2c_rlen, uint32_t *rbuff);
void i2cm_dma_wr(uint32_t i2c_wlen, uint32_t *wbuff);

#if I2CM_DMA_ISR
void i2cm_txdma_handler(void);
void i2cm_rxdma_handler(void);
#endif

#endif
