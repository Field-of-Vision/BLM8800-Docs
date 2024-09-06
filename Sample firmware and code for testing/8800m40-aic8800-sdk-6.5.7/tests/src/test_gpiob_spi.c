
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

#ifdef CFG_TEST_GPIOB_SPI
void gpiob_spi_single_wr_dat(unsigned char bit_len, unsigned int spi_wdata)
{
    unsigned volatile int rdata;
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->ctrl), AIC1000LITE_SPI_FRAME_SIZE(bit_len-1) | AIC1000LITE_SPI_CS_PULSE(0x3) | AIC1000LITE_SPI_CS_DELAY(0x3) | AIC1000LITE_SPI_DI_DELAY(0x3) | AIC1000LITE_SPI_DO_DELAY(0x1) | AIC1000LITE_SPI_CLOCK_DELAY(0x3) | AIC1000LITE_SPI_ENABLE);
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->rxtx_buffer), spi_wdata);
    rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    while (rdata & 0x1) {
        rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    }
}

void gpiob_spi_burst_wr_dat(unsigned char bit_len, unsigned char burst_len, unsigned int spi_lwdata[])
{
    unsigned volatile int rdata,i;
    PMIC_MEM_MASK_WRITE((unsigned int)&(aic1000liteSpi->irq), AIC1000LITE_SPI_TX_THRESHOLD(0x0),AIC1000LITE_SPI_TX_THRESHOLD_MASK);
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->ctrl), AIC1000LITE_SPI_FRAME_SIZE(bit_len-1) | AIC1000LITE_SPI_CS_PULSE(0x3) | AIC1000LITE_SPI_CS_DELAY(0x3) | AIC1000LITE_SPI_DI_DELAY(0x3) | AIC1000LITE_SPI_DO_DELAY(0x1) | AIC1000LITE_SPI_CLOCK_DELAY(0x3) | AIC1000LITE_SPI_ENABLE);
    for(i=0; i<burst_len; i=i+1)
    {
        while ((PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status)) & AIC1000LITE_SPI_TX_TH) != AIC1000LITE_SPI_TX_TH)
        {
            dbg("wait spi buffer ready !!!\n");
        }
        PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->rxtx_buffer), spi_lwdata[i]);
    }

    rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    while (rdata & 0x1) {
        rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    }
}

unsigned int gpiob_spi_single_rd_dat(unsigned char bit_len, unsigned int wdata)
{
    unsigned volatile int rdata;
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->ctrl), AIC1000LITE_SPI_FRAME_SIZE(bit_len-1) | AIC1000LITE_SPI_CS_PULSE(0x3) | AIC1000LITE_SPI_CS_DELAY(0x3) | AIC1000LITE_SPI_DI_DELAY(0x3) | AIC1000LITE_SPI_DO_DELAY(0x1) | AIC1000LITE_SPI_CLOCK_DELAY(0x3) | AIC1000LITE_SPI_ENABLE | AIC1000LITE_SPI_INPUT_MODE | AIC1000LITE_SPI_INPUT_SEL(0x1));
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->rxtx_buffer), wdata);
    rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    while (rdata & 0x1) {
        rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->status));
    }
    rdata = PMIC_MEM_READ((unsigned int)&(aic1000liteSpi->rxtx_buffer));
    return(rdata);
}

void gpiob_spi_initial(unsigned int spi_clk_div)
{
    // spi iomux
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[0]), AIC1000LITE_IOMUX_PAD_GPIO_0_SEL_FUN_SPI_DI_1_SEL);
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[1]), AIC1000LITE_IOMUX_PAD_GPIO_1_SEL_FUN_SPI_CS_0_SEL);
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[2]), AIC1000LITE_IOMUX_PAD_GPIO_2_SEL_FUN_SPI_DIO_0_SEL);
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[3]), AIC1000LITE_IOMUX_PAD_GPIO_3_SEL_FUN_SPI_CLK_SEL);
    //spi cfg ini
    PMIC_MEM_WRITE((unsigned int)&(aic1000liteSpi->cfg), AIC1000LITE_SPI_CLOCK_DIVIDER(spi_clk_div>0x1 ? spi_clk_div-0x1 : 0x1) | AIC1000LITE_SPI_CS_POLARITY_0 | AIC1000LITE_SPI_CS_POLARITY_1);
}

void gpiob_spi_test(void)
{
    gpiob_spi_initial(2);
    unsigned int rdata;
    unsigned int spi_lwdata[32] = {0xA5};
    gpiob_spi_single_wr_dat(32,0x12345678);
    gpiob_spi_burst_wr_dat(32,32,spi_lwdata);
    rdata = gpiob_spi_single_rd_dat(32,0x12344321);
    dbg("spi single read data =%x !!!\n",rdata);
    rdata = gpiob_spi_single_rd_dat(32,0x84211248);
    dbg("spi single read data =%x !!!\n",rdata);
    gpiob_spi_single_wr_dat(32,0x12345678);
    rdata = gpiob_spi_single_rd_dat(32,0x12345678);
    dbg("spi single read data =%x !!!\n",rdata);
    rdata = gpiob_spi_single_rd_dat(32,0x87654321);
    dbg("spi single read data =%x !!!\n",rdata);
}
#endif /* CFG_TEST_GPIOB_SPI */

