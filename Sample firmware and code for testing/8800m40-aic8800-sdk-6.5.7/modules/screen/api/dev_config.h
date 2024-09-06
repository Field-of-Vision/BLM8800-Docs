/*****************************************************************************
* | File        :   dev_config.h
* | Author      :   Waveshare team
* | Function    :   Show SDcard BMP picto LCD
* | Info        :
*   Provide the hardware underlying interface
*----------------
* | This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <stdbool.h>
#include "chip.h"
#include "gpio_api.h"

#define USE_SPI_4W  1
#define USE_IIC     0

#define GPIO_IDX_LCD_RST        5
#define GPIO_IDX_TP_CS          7
#define GPIO_IDX_TP_INT         6
#define GET_TP_IRQ              gpioa_get(GPIO_IDX_TP_INT)

typedef enum {
    SPI_CS0 = 0,
    SPI_CS1,
    SPI_CSN_MAX
} SPI_CSN_T;

typedef enum {
    SPI_DC_NONE = 0,
    SPI_DC_DATA,
    SPI_DC_CMD,
    SPI_DC_MAX
} SPI_DC_T;

/*------------------------------------------------------------------------------------------------------*/
void PWM_SetValue(uint16_t value);

void SPI4W_Init(void);
void SPI4W_Write_Byte(SPI_CSN_T cs, SPI_DC_T dc, bool cs_end, uint8_t value);
uint8_t SPI4W_Read_Byte(SPI_CSN_T cs, SPI_DC_T dc, bool cs_end);

void Driver_Delay_us(uint32_t xus);
void Driver_Delay_ms(uint32_t xms);

#endif
