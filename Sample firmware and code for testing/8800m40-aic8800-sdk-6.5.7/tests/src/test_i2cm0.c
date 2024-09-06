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
#include "i2cm_api.h"
#include "sysctrl_api.h"
#include "rtos_al.h"
#include "dbg.h"

#ifdef CFG_TEST_I2CM0
#define USER_PRINTF             dbg

#define I2C_DEV_MPU6050         0
#define I2C_DEV_ADXL345         1       // Support Multi byte read test

#define I2CM_DMA_TEST           1       // Multi byte write and read
#define I2CM_DMA_TX_LEN         128     // Can`t longer than 128
#define I2CM_DMA_RX_LEN         128     // Can`t longer than 128

uint32_t i2cm_tx_buff[I2CM_DMA_TX_LEN]; // The buff is defined for DMA transfer, must be defined as 'uint32'.
uint32_t i2cm_rx_buff[I2CM_DMA_RX_LEN]; // The buff is defined for DMA transfer, must be defined as 'uint32'.

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void i2cm0_test(void)
{
    uint8_t reg_addr, reg_val;
    USER_PRINTF("Start test case: i2cm0\n");

    #if (PLF_AIC8800)
    unsigned char tx_data[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xf0};
    unsigned char rx_data[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    i2cm0_init();

    reg_addr = 0x08;
    reg_val  = 0xcd;
    i2cm0_dev_reg_write(reg_addr, reg_val);
    USER_PRINTF("write 0x%2x -> [%x]\n", reg_val, reg_addr);

    i2cm0_dev_reg_read(reg_addr, &reg_val);
    USER_PRINTF("read  0x%2x -> [%x]\n", reg_val, reg_addr);

    reg_addr = 0x00;
    i2cm0_dev_muti_byte_write(reg_addr, tx_data, 15);

    reg_addr = 0x00;
    i2cm0_dev_muti_byte_read(reg_addr, rx_data, 16);
    for(int i=0; i<16; i++)
        dbg("%x\n", rx_data[i]);

    i2cm0_deinit();
    #endif /* PLF_AIC8800 */

    #if (PLF_AIC8800MC) || (PLF_AIC8800M40)
    i2cm_init(I2CM_CHANNAL_1);
    i2cm_clock_setup(80, I2C_SPEED_STANDARD);    // 80 is default. Follow with CONFIG_INITIAL_SYSTEM_CLOCK.
    #if I2C_DEV_MPU6050
    // set i2c device addr
    i2cm_setMode(DEV_ADDR_MPU);

    // MPU6050-init
    reg_addr = 0x6B; reg_val = 0x00;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0x19; reg_val = 0x07;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0x1A; reg_val = 0x06;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0x1C; reg_val = 0x01;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0x1B; reg_val = 0x18;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0x75; reg_val = 0;
    reg_val  = i2cm_byte_rd(reg_addr);
    dbg("Read Dev addr: 0x%02x\n", reg_val);
    #endif /* I2C_DEV_MPU6050 */

    #if I2C_DEV_ADXL345
    // set i2c device addr
    i2cm_setMode(DEV_ADDR_ADXL);

    // ADXL345-Connect
    reg_addr = 0x00; reg_val = 0;
    reg_val  = i2cm_byte_rd(reg_addr);
    dbg("Read Dev addr: 0x%02x, val: %02x\n", reg_addr, reg_val);
    if (reg_val != 0xE5) {
        dbg("ADXL345 is not connected.\n");
        return ;
    }

    // ADXL345-Init
    reg_addr = 0X31; reg_val = 0X2B;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0X2C; reg_val = 0x0A;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0X2D; reg_val = 0x28;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0X2E; reg_val = 0x00;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0X1E; reg_val = 0x00;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0X1F; reg_val = 0x00;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0X20; reg_val = 0x00;
    i2cm_addr_wr(reg_addr, reg_val);
    USER_PRINTF("write 0x%02x -> [%02x]\n", reg_val, reg_addr);

    reg_addr = 0x32; reg_val = 0;
    reg_val  = i2cm_byte_rd(reg_addr);
    dbg("Read Dev addr: 0x%02x, val: %02x\n", reg_addr, reg_val);

    #if I2CM_DMA_TEST
    for(int i=0; i<I2CM_DMA_TX_LEN; i++) {
        i2cm_tx_buff[i] = i & 0xFF;         // write buffer init, prepare the data to write.
        i2cm_rx_buff[i] = 0x100;            // read buffer init, must be set as '0x100'.
    }

    // DMA multi byte read test.
    int len = 7;                            // first is register addr, read 6 byte, len = 1 + 6
    i2cm_rx_buff[0] = 0x32;                 // add read-register addr in first buffer element.
    dbg("i2cm_dma_rd: addr = 0x%02x, len = %d\n", i2cm_rx_buff[0], len);

    i2cm_dma_rd(reg_addr, len, i2cm_rx_buff);
    for (int i=0; i<len-1; i++)             // Later, the read data is began from first buffer element.
        dbg("%02x ", i2cm_rx_buff[i]);
    dbg("\n\n");
    // DMA multi byte read test finish.

    //DMA multi byte write test
    len = 9;
    i2cm_tx_buff[0] = 0x64;                 // add write-register addr in first buffer element.
    dbg("i2cm_dma_wr: addr = 0x%02x, len = %d\n", i2cm_tx_buff[0], len);
    i2cm_dma_wr(len, i2cm_tx_buff);
    rtos_task_suspend(50);
    //DMA multi byte write test finish.
    #endif /* I2CM_DMA_TEST */
    #endif /* I2C_DEV_ADXL345 */
    #endif /* (PLF_AIC8800MC) || (PLF_AIC8800M40) */

    USER_PRINTF("\ni2cm0 test done\n");
}

#endif /* CFG_TEST_I2CM0 */
