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
#include "pmic_api.h"
#include "aic1000Lite_spi.h"
#include "aic1000Lite_iomux.h"
#include "gpio_api.h"
#include "sysctrl_api.h"
#include "dbg.h"
#include "rtos_al.h"

#ifdef CFG_TEST_SPI_LCD_4WIRES

void spi_lcd_4wires_init(void)
{
  // spi iomux
  PMIC_MEM_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[1]), AIC1000LITE_IOMUX_PAD_GPIO_1_SEL_FUN_SPI_CS_0_SEL);
  PMIC_MEM_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[2]), AIC1000LITE_IOMUX_PAD_GPIO_2_SEL_FUN_SPI_DIO_0_SEL);
  PMIC_MEM_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[3]), AIC1000LITE_IOMUX_PAD_GPIO_3_SEL_FUN_SPI_CLK_SEL);
  //spi cfg ini
  PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->cfg), AIC1000LITE_SPI_CLOCK_DIVIDER(0x0) | AIC1000LITE_SPI_CS_POLARITY_0 | AIC1000LITE_SPI_CS_POLARITY_1);

  //gpiob0 lcd RS: cmd/data select
  gpiob_init(0);
  gpiob_dir_out(0);

  //gpioa4 lcd RES: resetn
  gpioa_init(4);
  gpioa_dir_out(4);

  gpioa_clr(4);
  rtos_task_suspend(1);
  gpioa_set(4);
}

void spi_lcd_4wires_cmd(unsigned char bit_len, unsigned int spi_wdata)
{
    volatile unsigned int rdata;
    gpiob_clr(0);
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->rxtx_buffer), spi_wdata);
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->ctrl), AIC1000LITE_SPI_FRAME_SIZE(bit_len-1) | AIC1000LITE_SPI_CS_PULSE(0x3) | AIC1000LITE_SPI_CS_DELAY(0x3) | AIC1000LITE_SPI_DI_DELAY(0x3) | AIC1000LITE_SPI_DO_DELAY(0x1) | AIC1000LITE_SPI_CLOCK_DELAY(0x3) | AIC1000LITE_SPI_ENABLE);
    rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    while (rdata & 0x1) {
        rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    }
}

void spi_lcd_4wires_dat(unsigned char bit_len, unsigned int spi_wdata)
{
    volatile unsigned int rdata;
    gpiob_set(0);
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->rxtx_buffer), spi_wdata);
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->ctrl), AIC1000LITE_SPI_FRAME_SIZE(bit_len-1) | AIC1000LITE_SPI_CS_PULSE(0x3) | AIC1000LITE_SPI_CS_DELAY(0x3) | AIC1000LITE_SPI_DI_DELAY(0x3) | AIC1000LITE_SPI_DO_DELAY(0x1) | AIC1000LITE_SPI_CLOCK_DELAY(0x3) | AIC1000LITE_SPI_ENABLE);
    rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    while (rdata & 0x1) {
        rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    }
}



void spi_lcd_4wires_test(void)
{
    spi_lcd_4wires_init();
    spi_lcd_4wires_cmd(24, 0x5a5a5a);
    spi_lcd_4wires_dat(24, 0xa5a5a5);
    spi_lcd_4wires_cmd(24, 0x123456);
    spi_lcd_4wires_dat(24, 0x876543);
}

#endif /* CFG_TEST_SPI_4WIRES_LCD */
