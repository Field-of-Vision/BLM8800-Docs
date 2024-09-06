#ifndef _DA230_H_
#define _DA230_H_

#define DTA_REG_SPI_I2C                 0x00
#define DTA_REG_WHO_AM_I                0x01
#define DTA_REG_ACC_X_LSB               0x02
#define DTA_REG_ACC_X_MSB               0x03
#define DTA_REG_ACC_Y_LSB               0x04
#define DTA_REG_ACC_Y_MSB               0x05
#define DTA_REG_ACC_Z_LSB               0x06
#define DTA_REG_ACC_Z_MSB               0x07
#define DTA_REG_MOTION_FLAG             0x09
#define DTA_REG_G_RANGE                 0x0f
#define DTA_REG_ODR_AXIS_DISABLE        0x10
#define DTA_REG_POWERMODE_BW            0x11
#define DTA_REG_SWAP_POLARITY           0x12
#define DTA_REG_FIFO_CTRL               0x14
#define DTA_REG_INTERRUPT_SETTINGS0     0x15
#define DTA_REG_INTERRUPT_SETTINGS1     0x16
#define DTA_REG_INTERRUPT_SETTINGS2     0x17
#define DTA_REG_INTERRUPT_MAPPING1      0x19
#define DTA_REG_INTERRUPT_MAPPING2      0x1a
#define DTA_REG_INTERRUPT_MAPPING3      0x1b
#define DTA_REG_INT_PIN_CONFIG          0x20
#define DTA_REG_INT_LATCH               0x21
#define DTA_REG_ACTIVE_DURATION         0x27
#define DTA_REG_ACTIVE_THRESHOLD        0x28
#define DTA_REG_TAP_DURATION            0x2A
#define DTA_REG_TAP_THRESHOLD           0x2B
#define DTA_REG_Z_BLOCK                 0x2D
#define DTA_REG_CUSTOM_OFFSET_X         0x38
#define DTA_REG_CUSTOM_OFFSET_Y         0x39
#define DTA_REG_CUSTOM_OFFSET_Z         0x3a
#define DTA_REG_ENGINEERING_MODE        0x7f
#define DTA_REG_SENSITIVITY_TRIM_X      0x80
#define DTA_REG_SENSITIVITY_TRIM_Y      0x81
#define DTA_REG_SENSITIVITY_TRIM_Z      0x82
#define DTA_REG_COARSE_OFFSET_TRIM_X    0x83
#define DTA_REG_COARSE_OFFSET_TRIM_Y    0x84
#define DTA_REG_COARSE_OFFSET_TRIM_Z    0x85
#define DTA_REG_FINE_OFFSET_TRIM_X      0x86
#define DTA_REG_FINE_OFFSET_TRIM_Y      0x87
#define DTA_REG_FINE_OFFSET_TRIM_Z      0x88
#define DTA_REG_SENS_COMP               0x8c
#define DTA_REG_CHIP_INFO_SECOND        0xc1
#define DTA_REG_SENS_COARSE_TRIM        0xd1

enum {
    TAP_DETECTION_SINGLE = 3,
    TAP_DETECTION_DOUBLE
};

int da230_init(void);
int da230_set_enable(char enable);
int da230_read_data(short *x, short *y, short *z);
int da230_open_interrupt(void);
int da230_close_interrupt(void);
int da230_set_interrupt_level(int level);
void da230_enable_interrupt_temp(char en);
int da230_parse_interrupt_type(void);
int da230_get_chip_id(void);
void da230_standby_mode(void);
void da230_normal_mode(void);
void da230_open_interrupt_test();
int da230_read_data_test(short *x, short *y, short *z);
int da230_i2c_open( void );
int da230_reset(void);


#endif
