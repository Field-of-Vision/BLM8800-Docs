/*
 * Copyright (C) 2018-2023 AICSemi Ltd.
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

/**
 * Includes
 */
#include "spi_api.h"
#include "gpio_api.h"
#include "sysctrl_api.h"
#include "reg_iomux.h"
#include "ll.h"
#include "dbg.h"

/**
 * Macros
 */
#define SPI_DEBUG_PRINTF(fmt, ...)      do {} while(0)//dbg(fmt, ##__VA_ARGS__)//

/**
 * TypeDefs
 */

/**
 * Variables
 */

/**
 * Functions
 */

void spim_init(spim_cfg_t *spim)
{
    uint32_t pclk;

    // clk en
    cpusysctrl_pclkme_set(CSC_PCLKME_SPI_EN_BIT);
    cpusysctrl_oclkme_set(CSC_OCLKME_SPI_EN_BIT);
    // clk freq
    pclk = sysctrl_clock_get(SYS_PCLK);
    spi_dr_div_setf(pclk / 2 / spim->clk_freq - 1);  // pclk/(2*(div+1)) = freq

    // iomux
    iomux_gpio_config_sel_setf(10, 3); // clk
    if (spim->cs == SPI_CS0) {
        iomux_gpio_config_sel_setf(11, 3); // cs
    }
    if ((spim->spi_mode == SPI_MODE_GENERIC) ||
        (spim->spi_mode == SPI_MODE_LCD_3W_DI_DO) ||
        (spim->spi_mode == SPI_MODE_LCD_4W_DI_DO)) {
        iomux_gpio_config_sel_setf(12, 3); // di
    }
    iomux_gpio_config_sel_setf(13, 3); // do

    // gpioa cs
    if ((spim->cs == SPI_CS1) && (spim->gpa_idx_cs <= GPIOA_IDX_MAX)) {
        gpioa_init(spim->gpa_idx_cs);
        gpioa_dir_out(spim->gpa_idx_cs);
        gpioa_set(spim->gpa_idx_cs);
    }
}

void spim_write_byte(spim_cfg_t *spim, uint8_t byte_val, bool cs_end)
{
    unsigned int rdata;
    int idx, rec = 0;
    if (SPI_DC_DATA == spim->dc) {
        AIC_SPI0->MR1 |=  (0x01UL << 15); // data mode
    } else if (SPI_DC_CMD == spim->dc) {
        AIC_SPI0->MR1 &= ~(0x01UL << 15); // cmd mode
    }
    AIC_SPI0->OCR = 1; // out data cnt
    AIC_SPI0->ICR = 0; // in data cnt
    if (SPI_CS0 == spim->cs) {
        AIC_SPI0->MR0   = ((0x01UL << 11) | (spim->spi_mode <<  3)); // slave, spi mode
        AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (spim->bit_cnt << 2)); // cs, bit count
        spi_cr0_clk_mode_setf(spim->clk_mode); // clock edge + phase
    } else if (SPI_CS1 == spim->cs) {
        AIC_SPI0->MR0   = ((0x00UL << 11) | (spim->spi_mode <<  3)); // slave, spi mode
        AIC_SPI0->CR[0] = ((0x0DUL <<  8) | (spim->bit_cnt << 2)); // cs, bit count
        spi_cr0_clk_mode_setf(spim->clk_mode); // clock edge + phase
        if (spim->gpa_idx_cs <= GPIOA_IDX_MAX) {
            gpioa_clr(spim->gpa_idx_cs);
        }
    }
    AIC_SPI0->CR[1] = (0x02UL << 12); // send
    AIC_SPI0->IOR   = byte_val; // tx data
    AIC_SPI0->TCR   = (0x01UL << 1); // trans start
    for (idx = 0; idx < 32; idx++) {
        __NOP(); __NOP();
        __NOP(); __NOP();
        rdata = AIC_SPI0->SR;
        if (rdata & (0x01UL << 8)) {
            rec |= (0x01UL << idx);
        } else if (idx > 4) {
            break;
        }
    }
    if (idx == 32) {
        SPI_DEBUG_PRINTF("%08x\n",rec);
        do {
            __NOP(); __NOP();
            __NOP(); __NOP();
            rdata = AIC_SPI0->SR;
        } while (rdata & (0x01UL << 8));
    }
    if (cs_end) {
        AIC_SPI0->CR[0] = (0x0FUL <<  8);
        if ((SPI_CS1 == spim->cs) && (spim->gpa_idx_cs <= GPIOA_IDX_MAX)) {
            gpioa_set(spim->gpa_idx_cs);
        }
    }
}


uint8_t spim_read_byte(spim_cfg_t *spim, bool cs_end)
{
    unsigned int rdata;
    int idx, rec = 0;
    if (SPI_DC_DATA == spim->dc) {
        AIC_SPI0->MR1 |=  (0x01UL << 15); // data mode
    } else if (SPI_DC_CMD == spim->dc) {
        AIC_SPI0->MR1 &= ~(0x01UL << 15); // cmd mode
    }
    AIC_SPI0->OCR = 1; // out data cnt
    AIC_SPI0->ICR = 1; // in data cnt
    if (SPI_CS0 == spim->cs) {
        AIC_SPI0->MR0   = ((0x01UL << 11) | (spim->spi_mode <<  3)); // slave, spi mode
        AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (spim->bit_cnt << 2)); // cs, bit count
        spi_cr0_clk_mode_setf(spim->clk_mode); // clock edge + phase
    } else if (SPI_CS1 == spim->cs) {
        AIC_SPI0->MR0   = ((0x01UL << 11) | (spim->spi_mode <<  3)); // slave, spi mode
        AIC_SPI0->CR[0] = ((0x0DUL <<  8) | (spim->bit_cnt << 2)); // cs, bit count
        spi_cr0_clk_mode_setf(spim->clk_mode); // clock edge + phase
        if (spim->gpa_idx_cs <= GPIOA_IDX_MAX) {
            gpioa_clr(spim->gpa_idx_cs);
        }
    }
    AIC_SPI0->CR[1] = (0x03UL << 12); // send and recv
    AIC_SPI0->IOR   = 0x00UL;//0xFFUL; // tx dummy data
    AIC_SPI0->TCR   = (0x01UL << 1); // trans start
    for (idx = 0; idx < 32; idx++) {
        __NOP(); __NOP();
        __NOP(); __NOP();
        rdata = AIC_SPI0->SR;
        if (rdata & (0x01UL << 8)) {
            rec |= (0x01UL << idx);
        } else if (idx > 4) {
            break;
        }
    }
    if (idx == 32) {
        SPI_DEBUG_PRINTF("%08x\n",rec);
        do {
            __NOP(); __NOP();
            __NOP(); __NOP();
            rdata = AIC_SPI0->SR;
        } while (rdata & (0x01UL << 8));
    }
    rdata = AIC_SPI0->IOR;
    if (cs_end) {
        AIC_SPI0->CR[0] = (0x0FUL << 8);
        if ((SPI_CS1 == spim->cs) && (spim->gpa_idx_cs <= GPIOA_IDX_MAX)) {
            gpioa_set(spim->gpa_idx_cs);
        }
    }
    return (uint8_t)rdata;
}
