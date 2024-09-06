#ifndef __I2CM_API_H_
#define __I2CM_API_H_

#include "dbg.h"
#ifdef CFG_RTOS
#include "rtos.h"
#endif
#include "reg_i2cm.h"
#include "reg_iomux.h"
#include "sysctrl_api.h"

#define I2C_DEV_ADDR            (0x3c)      //7 bits
#define I2C_CLK_FREQ            (100000)
#define I2C_INT_MODE            0

#define I2CM_DEBUG_PRINTF(fmt, ...)             dbg(fmt, ##__VA_ARGS__)

void i2cm0_init(void);
void i2cm0_deinit(void);
int i2cm0_wait_op_done(int timeout);
int i2cm0_op_done(bool isr);
int i2cm0_dev_reg_read(unsigned char reg_addr, unsigned char *reg_data);
int i2cm0_dev_reg_write(unsigned char reg_addr, unsigned char reg_data);
void i2cm0_dev_muti_byte_write(unsigned char reg_addr, unsigned char reg_data[], unsigned char data_len);
void i2cm0_dev_muti_byte_read(unsigned char reg_addr, unsigned char rev_data[], unsigned char data_len);
void I2CM_IRQHandler(void);

#endif
