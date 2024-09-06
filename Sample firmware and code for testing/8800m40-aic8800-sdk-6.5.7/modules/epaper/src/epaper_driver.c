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

/**
 * Includes
 */
#include "epaper_driver.h"
#include "reg_spi.h"
#include "reg_iomux.h"
#include "reg_sysctrl.h"
#include "system.h"
#include "gpio_api.h"
#include "lp_ticker_api.h"
#include "dbg.h"
#ifdef CFG_RTOS
#include "rtos_al.h"
#endif

/**
 * Macros
 */
#define SPI_CLK_FREQ            (1000000)

#define GPIOA_IDX_EPD_RST_OUT   12
#define GPIOA_IDX_EPD_BUSY_IN   15

#define EPD_White   0xFF
#define EPD_Black   0x00

#define EPD_DEBUG_PRINTF(fmt, ...)       do {} while(0) //dbg(fmt, ##__VA_ARGS__)//

/**
 * Global Variables
 */
int epd_inited = 0;

/**
 * Functions
 */
void Driver_Delay_us(unsigned int xus)
{
    unsigned int delta_us = xus;
    unsigned int previous_us = lp_ticker_read();
    while ((lp_ticker_read() - previous_us) < delta_us);
}

void Driver_Delay_ms(unsigned int xms)
{
    #ifndef CFG_RTOS
    Driver_Delay_us(xms * 1000);
    #else
    rtos_task_suspend(xms);
    #endif
}

void EPD_Check_Busy(void)
{
    EPD_DEBUG_PRINTF("busy_0\n");
    while (1) { //=1 BUSY
        if (gpioa_get(GPIOA_IDX_EPD_BUSY_IN) == 0) {
            break;
        }
    }
    EPD_DEBUG_PRINTF("busy_1\n");
}

void EPD_SPI_Write(SPI_DC_T dc, unsigned char value)
{
    unsigned int rdata;
    int idx, rec = 0;
    if (SPI_DC_DATA == dc) {
        AIC_SPI0->MR1 |=  (0x01UL << 15); // data mode
    } else if (SPI_DC_CMD == dc) {
        AIC_SPI0->MR1 &= ~(0x01UL << 15); // cmd mode
    }
    AIC_SPI0->OCR = 1; // out data cnt
    AIC_SPI0->ICR = 0; // in data cnt
    AIC_SPI0->MR0   = ((0x01UL << 11) | (0x04UL <<  3)); // slave, 4-wire mode
    AIC_SPI0->CR[0] = ((0x0EUL <<  8) | (8 << 2)); // cs, bit count
    spi_cr0_clk_mode_setf(SPI_CR_CLK_MODE_0); // clock edge + phase
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
        EPD_DEBUG_PRINTF("%08x\n",rec);
        do {
            __NOP(); __NOP();
            __NOP(); __NOP();
            rdata = AIC_SPI0->SR;
        } while (rdata & (0x01UL << 8));
    }
    AIC_SPI0->CR[0] = (0x0FUL <<  8); // cs
}

#if 0
unsigned char EPD_SPI_Read(void)
{
    unsigned char rdata =0;
    unsigned char i;
    for(i=0;i<8;i++)
    {
        E_Paper_SCK = 0;
        delay_us(2);
        E_Paper_SCK = 1;
        delay_us(2);
        rdata <<= 1;
        if(E_READ_SDI) rdata |=0x01;
            delay_us(2);
    }
    E_Paper_SCK = 0;
    return rdata;
}
#endif

void EPD_WriteCMD(unsigned char command)
{
    EPD_DEBUG_PRINTF("WriteCMD:%x\n",command);
    EPD_SPI_Write(SPI_DC_CMD, command);
}

void EPD_WriteDATA(unsigned char data)
{
    EPD_DEBUG_PRINTF("WriteDATA:%x\n",data);
    EPD_SPI_Write(SPI_DC_DATA, data);
}

void EPD_Part_Update(void)
{
    EPD_WriteCMD(0x22); //Display Update Control
    EPD_WriteDATA(0xFF);
    EPD_WriteCMD(0x20); //Activate Display Update Sequence
    EPD_Check_Busy();
}

void EPD_Update_Fast(void)
{
    EPD_WriteCMD(0x22); //Display Update Control
    EPD_WriteDATA(0xC7);
    EPD_WriteCMD(0x20); //Activate Display Update Sequence
    EPD_Check_Busy();
}

void EPD_Update(void)
{
    EPD_WriteCMD(0x18);     //温度传感器选择
    EPD_WriteDATA(0X80);    //0x80:内部  0x48:外部
    EPD_WriteCMD(0x22);
    EPD_WriteDATA(0XF7);    //不同的值不同操作执行流程
    EPD_WriteCMD(0x20);     //主动激活
    Driver_Delay_ms(10);
    EPD_Check_Busy();       //读取工作状态
}

void EPD_WhiteScreen_ALL_Fast(const unsigned char *datas)
{
    unsigned int i;
    EPD_WriteCMD(0x24);   //write RAM for black(0)/white (1)
    for (i=0;i<4000;i++) {
        EPD_WriteDATA(*datas);
        datas++;
    }
    EPD_Update_Fast();
}

void EPD_IO_Init(void)
{
    EPD_DEBUG_PRINTF("IO_Init\n");
    if (!epd_inited) {
        // clk en
        cpusysctrl_pclkme_set(CSC_PCLKME_SPI_EN_BIT);
        cpusysctrl_oclkme_set(CSC_OCLKME_SPI_EN_BIT);
        // iomux
        iomux_gpio_config_sel_setf(10, 3); // clk
        iomux_gpio_config_sel_setf(11, 3); // cs
        //iomux_gpio_config_sel_setf(12, 3); // di
        iomux_gpio_config_sel_setf(13, 3); // do
        iomux_gpio_config_sel_setf(14, 3); // c/d
        spi_dr_div_setf(PeripheralClock / 2 / SPI_CLK_FREQ - 1);  // pclk/(2*(div+1)) = freq
        // Reset & Busy
        gpioa_init(GPIOA_IDX_EPD_RST_OUT);
        gpioa_dir_out(GPIOA_IDX_EPD_RST_OUT);
        gpioa_set(GPIOA_IDX_EPD_RST_OUT); // EPD_RST
        gpioa_init(GPIOA_IDX_EPD_BUSY_IN);
        gpioa_dir_in(GPIOA_IDX_EPD_BUSY_IN);// EPD_BUSY
        epd_inited = 1;
    }
}

void EPD_HW_Reset(void)
{
    EPD_DEBUG_PRINTF("Reset\n");
    // Module reset
    gpioa_clr(GPIOA_IDX_EPD_RST_OUT); //EPD_RST=0;
    Driver_Delay_ms(50);//At least 10ms delay
    gpioa_set(GPIOA_IDX_EPD_RST_OUT); //EPD_RST=1;
    Driver_Delay_ms(50);//At least 10ms delay
}

void EPD_HW_Init(void)
{
    EPD_DEBUG_PRINTF("HW_Init\n");
    EPD_IO_Init();
    EPD_HW_Reset();

    EPD_Check_Busy();
    EPD_WriteCMD(0x12);  //SWRESET
    EPD_Check_Busy();

    EPD_WriteCMD(0x3C); //BorderWavefrom
    EPD_WriteDATA(0x05);

    EPD_WriteCMD(0x21); //  Display update control
    EPD_WriteDATA(0x00);
    EPD_WriteDATA(0x80);

    EPD_WriteCMD(0x18); //Read built-in temperature sensor
    EPD_WriteDATA(0x80);

    EPD_WriteCMD(0x4E);   // set RAM x address count to 0;

    EPD_Check_Busy();
}

void EPD_HW_Init_Fast(void)
{
    EPD_DEBUG_PRINTF("HW_Init_Fast\n");
    EPD_IO_Init();
    EPD_HW_Reset();

    EPD_WriteCMD(0x12);  //SWRESET
    EPD_Check_Busy();

    EPD_WriteCMD(0x18); //Read built-in temperature sensor
    EPD_WriteDATA(0x80);

    EPD_WriteCMD(0x21); //  Display update control
    EPD_WriteDATA(0x00);
    EPD_WriteDATA(0x80);

    EPD_WriteCMD(0x22); // Load temperature value
    EPD_WriteDATA(0xB1);
    EPD_WriteCMD(0x20);
    EPD_Check_Busy();

    EPD_WriteCMD(0x1A); // Write to temperature register
    EPD_WriteDATA(0x64);
    EPD_WriteDATA(0x00);

    EPD_WriteCMD(0x22); // Load temperature value
    EPD_WriteDATA(0x91);
    EPD_WriteCMD(0x20);
    EPD_Check_Busy();
}


void EPD_Sleep(void)
{
    EPD_WriteCMD(0x10);          //电子纸深度休眠指令*/
    EPD_WriteDATA(0x01);         //00：POR 01：休眠模式1 11：休眠模式2
    Driver_Delay_ms(100);
}

void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
    unsigned int i;
    const unsigned char  *datas_flag;
    datas_flag=datas;
    EPD_WriteCMD(0x24);   //Write Black and White image to RAM
    for(i=0;i<4000;i++)
    {
        EPD_WriteDATA(*datas);
        datas++;
    }
    datas=datas_flag;
    EPD_WriteCMD(0x26);   //Write Black and White image to RAM
    for(i=0;i<4000;i++)
    {
        EPD_WriteDATA(*datas);
        datas++;
    }
    EPD_Update();
}

void EPD_BlackScreen_White(void)
{
    unsigned int i,k;
    EPD_WriteCMD(0x24);   //write RAM for black(0)/white (1)
    for(k=0;k<250;k++)
    {
        for(i=0;i<25;i++)
        {
            EPD_WriteDATA(0x00);
        }
    }
    EPD_Update();
}

void EPD_WhiteScreen_White(void)
{
    unsigned int i,k;
    EPD_WriteCMD(0x24);   //write RAM for black(0)/white (1)
    for(k=0;k<250;k++)
    {
        for(i=0;i<25;i++)
        {
            EPD_WriteDATA(0xff);
        }
    }
    EPD_Update();
}

void EPD_Dis_Part_myself(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
                         unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
                         unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
                         unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
                         unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
                         unsigned int PART_COLUMN,unsigned int PART_LINE)
{
    unsigned int i;
    unsigned int x_end,y_start1,y_start2,y_end1,y_end2;

    //Data A////////////////////////////
    x_startA=x_startA/8;//Convert to byte
    x_end=x_startA+PART_LINE/8-1;

    y_start1=0;
    y_start2=y_startA-1;
    if(y_startA>=256)
    {
        y_start1=y_start2/256;
        y_start2=y_start2%256;
    }
    y_end1=0;
    y_end2=y_startA+PART_COLUMN-1;
    if(y_end2>=256)
    {
        y_end1=y_end2/256;
        y_end2=y_end2%256;
    }
    //Reset
    EPD_HW_Reset();

    EPD_WriteCMD(0x3C); //BorderWavefrom
    EPD_WriteDATA(0x80);
    //
    EPD_WriteCMD(0x44);       // set RAM x address start/end, in page 35
    EPD_WriteDATA(x_startA);    // RAM x address start at 00h;
    EPD_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128
    EPD_WriteCMD(0x45);       // set RAM y address start/end, in page 35
    EPD_WriteDATA(y_start2);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_start1);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_end2);    // RAM y address end at 00h;
    EPD_WriteDATA(y_end1);

    EPD_WriteCMD(0x4E);   // set RAM x address count to 0;
    EPD_WriteDATA(x_startA);
    EPD_WriteCMD(0x4F);   // set RAM y address count to 0X127;
    EPD_WriteDATA(y_start2);
    EPD_WriteDATA(y_start1);


    EPD_WriteCMD(0x24);   //Write Black and White image to RAM
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
    {
        EPD_WriteDATA(*datasA);
        datasA++;
    }
    //Data B/////////////////////////////////////
    x_startB=x_startB/8;//Convert to byte
    x_end=x_startB+PART_LINE/8-1;

    y_start1=0;
    y_start2=y_startB-1;
    if(y_startB>=256)
    {
        y_start1=y_start2/256;
        y_start2=y_start2%256;
    }
    y_end1=0;
    y_end2=y_startB+PART_COLUMN-1;
    if(y_end2>=256)
    {
        y_end1=y_end2/256;
        y_end2=y_end2%256;
    }

    EPD_WriteCMD(0x44);       // set RAM x address start/end, in page 35
    EPD_WriteDATA(x_startB);    // RAM x address start at 00h;
    EPD_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128
    EPD_WriteCMD(0x45);       // set RAM y address start/end, in page 35
    EPD_WriteDATA(y_start2);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_start1);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_end2);    // RAM y address end at 00h;
    EPD_WriteDATA(y_end1);

    EPD_WriteCMD(0x4E);   // set RAM x address count to 0;
    EPD_WriteDATA(x_startB);
    EPD_WriteCMD(0x4F);   // set RAM y address count to 0X127;
    EPD_WriteDATA(y_start2);
    EPD_WriteDATA(y_start1);

    EPD_WriteCMD(0x24);   //Write Black and White image to RAM
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
    {
        EPD_WriteDATA(*datasB);
        datasB++;
    }

    //Data C//////////////////////////////////////
    x_startC=x_startC/8;//Convert to byte
    x_end=x_startC+PART_LINE/8-1;

    y_start1=0;
    y_start2=y_startC-1;
    if(y_startC>=256)
    {
        y_start1=y_start2/256;
        y_start2=y_start2%256;
    }
    y_end1=0;
    y_end2=y_startC+PART_COLUMN-1;
    if(y_end2>=256)
    {
        y_end1=y_end2/256;
        y_end2=y_end2%256;
    }

    EPD_WriteCMD(0x44);       // set RAM x address start/end, in page 35
    EPD_WriteDATA(x_startC);    // RAM x address start at 00h;
    EPD_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128
    EPD_WriteCMD(0x45);       // set RAM y address start/end, in page 35
    EPD_WriteDATA(y_start2);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_start1);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_end2);    // RAM y address end at 00h;
    EPD_WriteDATA(y_end1);

    EPD_WriteCMD(0x4E);   // set RAM x address count to 0;
    EPD_WriteDATA(x_startC);
    EPD_WriteCMD(0x4F);   // set RAM y address count to 0X127;
    EPD_WriteDATA(y_start2);
    EPD_WriteDATA(y_start1);

    EPD_WriteCMD(0x24);   //Write Black and White image to RAM
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
    {
        EPD_WriteDATA(*datasC);
        datasC++;
    }

    //Data D//////////////////////////////////////
    x_startD=x_startD/8;//Convert to byte
    x_end=x_startD+PART_LINE/8-1;

    y_start1=0;
    y_start2=y_startD-1;
    if(y_startD>=256)
    {
        y_start1=y_start2/256;
        y_start2=y_start2%256;
    }
    y_end1=0;
    y_end2=y_startD+PART_COLUMN-1;
    if(y_end2>=256)
    {
        y_end1=y_end2/256;
        y_end2=y_end2%256;
    }

    EPD_WriteCMD(0x44);       // set RAM x address start/end, in page 35
    EPD_WriteDATA(x_startD);    // RAM x address start at 00h;
    EPD_WriteDATA(x_end);        // RAM x address end at 0fh(15+1)*8->128
    EPD_WriteCMD(0x45);       // set RAM y address start/end, in page 35
    EPD_WriteDATA(y_start2);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_start1);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_end2);    // RAM y address end at 00h;
    EPD_WriteDATA(y_end1);

    EPD_WriteCMD(0x4E);   // set RAM x address count to 0;
    EPD_WriteDATA(x_startD);
    EPD_WriteCMD(0x4F);   // set RAM y address count to 0X127;
    EPD_WriteDATA(y_start2);
    EPD_WriteDATA(y_start1);

    EPD_WriteCMD(0x24);   //Write Black and White image to RAM
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
    {
        EPD_WriteDATA(*datasD);
        datasD++;
    }
    //Data E//////////////////////////////////////
    x_startE=x_startE/8;//Convert to byte
    x_end=x_startE+PART_LINE/8-1;

    y_start1=0;
    y_start2=y_startE-1;
    if(y_startE>=256)
    {
        y_start1=y_start2/256;
        y_start2=y_start2%256;
    }
    y_end1=0;
    y_end2=y_startE+PART_COLUMN-1;
    if(y_end2>=256)
    {
        y_end1=y_end2/256;
        y_end2=y_end2%256;
    }

    EPD_WriteCMD(0x44);       // set RAM x address start/end, in page 35
    EPD_WriteDATA(x_startE);    // RAM x address start at 00h;
    EPD_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128
    EPD_WriteCMD(0x45);       // set RAM y address start/end, in page 35
    EPD_WriteDATA(y_start2);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_start1);    // RAM y address start at 0127h;
    EPD_WriteDATA(y_end2);    // RAM y address end at 00h;
    EPD_WriteDATA(y_end1);

    EPD_WriteCMD(0x4E);   // set RAM x address count to 0;
    EPD_WriteDATA(x_startE);
    EPD_WriteCMD(0x4F);   // set RAM y address count to 0X127;
    EPD_WriteDATA(y_start2);
    EPD_WriteDATA(y_start1);
    EPD_WriteCMD(0x24);   //Write Black and White image to RAM
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
    {
        EPD_WriteDATA(*datasE);
        datasE++;
    }
    EPD_Part_Update();
}
