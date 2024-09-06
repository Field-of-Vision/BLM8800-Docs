/*****************************************************************************
* | File        :   dev_config.c
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
#include "dev_config.h"
#include "reg_spi.h"
#include "reg_iomux.h"
#include "reg_sysctrl.h"
#include "system.h"
#include "lp_ticker_api.h"
#include "dbg.h"
#ifdef CFG_RTOS
#include "rtos_al.h"
#endif

#define SPI_CLK_FREQ            (1000000)

#ifdef CFG_RTOS
static rtos_mutex spi0_mutex;
#endif

void PWM_SetValue(uint16_t value)
{
    (void)value; /// TBD
}

/**
 ****************************************************************************************
 * @brief init spi, config iomux & clock div
 ****************************************************************************************
 */
void SPI4W_Init(void)
{
    #ifdef CFG_RTOS
    if (rtos_mutex_create(&spi0_mutex)) {
        dbg("failed to create spi0 mutex\n");
    }
    #endif

    // clk en
    cpusysctrl_pclkme_set(CSC_PCLKME_SPI_EN_BIT);
    cpusysctrl_oclkme_set(CSC_OCLKME_SPI_EN_BIT);

    // iomux
    iomux_gpio_config_sel_setf(10, 3); // clk
    iomux_gpio_config_sel_setf(11, 3); // cs
    iomux_gpio_config_sel_setf(12, 3); // di
    iomux_gpio_config_sel_setf(13, 3); // do

    #ifdef CFG_RTOS
    rtos_mutex_lock(spi0_mutex, -1);
    #endif
    spi_dr_div_setf(PeripheralClock / 2 / SPI_CLK_FREQ - 1);  // pclk/(2*(div+1)) = freq
    #ifdef CFG_RTOS
    rtos_mutex_unlock(spi0_mutex);
    #endif
}

/*********************************************
function:   Hardware interface
note:
    SPI4W_Write_Byte(value) :
        Register hardware SPI
*********************************************/
void SPI4W_Write_Byte(SPI_CSN_T cs, SPI_DC_T dc, bool cs_end, uint8_t value)
{
    unsigned int rdata;
    int idx, rec = 0;
    #ifdef CFG_RTOS
    rtos_mutex_lock(spi0_mutex, -1);
    #endif
    if (SPI_DC_DATA == dc) {
        AIC_SPI0->MR1 |=  (0x01UL << 15); // data mode
    } else if (SPI_DC_CMD == dc) {
        AIC_SPI0->MR1 &= ~(0x01UL << 15); // cmd mode
    }
    AIC_SPI0->OCR = 1; // out data cnt
    AIC_SPI0->ICR = 0; // in data cnt
    if (SPI_CS0 == cs) {
        AIC_SPI0->MR0   = ((0x01UL << 11) | (0x04UL <<  3)); // slave, 4-wire mode
        AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (8 << 2)); // cs, bit count
        spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
    } else if (SPI_CS1 == cs) {
        AIC_SPI0->MR0   = ((0x00UL << 11) | (0x00UL <<  3)); // slave, generic mode
        AIC_SPI0->CR[0] = ((0x0DUL <<  8) | (8 << 2)); // cs, bit count
        spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
        gpioa_clr(GPIO_IDX_TP_CS);
    }
    AIC_SPI0->CR[1] = (0x02UL << 12); // send
    AIC_SPI0->IOR   = value; // tx data
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
        dbg("%08x\n",rec);
        do {
            __NOP(); __NOP();
            __NOP(); __NOP();
            rdata = AIC_SPI0->SR;
        } while (rdata & (0x01UL << 8));
    }
    if (cs_end) {
        AIC_SPI0->CR[0] = (0x0FUL <<  8);
        if (SPI_CS1 == cs) {
            gpioa_set(GPIO_IDX_TP_CS);
        }
    }
    #ifdef CFG_RTOS
    rtos_mutex_unlock(spi0_mutex);
    #endif
}

uint8_t SPI4W_Read_Byte(SPI_CSN_T cs, SPI_DC_T dc, bool cs_end)
{
    unsigned int rdata;
    int idx, rec = 0;
    #ifdef CFG_RTOS
    rtos_mutex_lock(spi0_mutex, -1);
    #endif
    if (SPI_DC_DATA == dc) {
        AIC_SPI0->MR1 |=  (0x01UL << 15); // data mode
    } else {
        AIC_SPI0->MR1 &= ~(0x01UL << 15); // cmd mode
    }
    AIC_SPI0->OCR = 1; // out data cnt
    AIC_SPI0->ICR = 1; // in data cnt
    if (SPI_CS0 == cs) {
        AIC_SPI0->MR0   = ((0x01UL << 11) | (0x04UL <<  3)); // slave, 4-wire mode
        AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (8 << 2)); // cs, bit count
        spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
    } else if (SPI_CS1 == cs) {
        AIC_SPI0->MR0   = ((0x01UL << 11) | (0x00UL <<  3)); // slave, generic mode
        AIC_SPI0->CR[0] = ((0x0DUL <<  8) | (8 << 2)); // cs, bit count
        spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
        gpioa_clr(GPIO_IDX_TP_CS);
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
        dbg("%08x\n",rec);
        do {
            __NOP(); __NOP();
            __NOP(); __NOP();
            rdata = AIC_SPI0->SR;
        } while (rdata & (0x01UL << 8));
    }
    if (cs_end) {
        AIC_SPI0->CR[0] = (0x0FUL << 8);
        if (SPI_CS1 == cs) {
            gpioa_set(GPIO_IDX_TP_CS);
        }
    }
    rdata = AIC_SPI0->IOR;
    #ifdef CFG_RTOS
    rtos_mutex_unlock(spi0_mutex);
    #endif
    return (uint8_t)rdata;
}


/********************************************************************************
function:   Delay function
note:
    Driver_Delay_us(xus) : Delay x us
    Driver_Delay_ms(xms) : Delay x ms
********************************************************************************/
void Driver_Delay_us(uint32_t xus)
{
    uint32_t delta_us = xus;
    uint32_t previous_us = lp_ticker_read();
    while ((lp_ticker_read() - previous_us) < delta_us);
}

void Driver_Delay_ms(uint32_t xms)
{
#ifndef CFG_RTOS
    Driver_Delay_us(xms * 1000);
#else
    rtos_task_suspend(xms);
#endif
}
