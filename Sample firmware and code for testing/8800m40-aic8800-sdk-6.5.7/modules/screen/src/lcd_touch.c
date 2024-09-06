/*****************************************************************************
* | File        :   LCD_Touch.c
* | Author      :   Waveshare team
* | Function    :   LCD Touch Pad Driver and Draw
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* | This version:   V2.0
* | Date        :   2018-01-29
* | Info        :   Basic version
* |
******************************************************************************/
#include "lcd_touch.h"
#include "dbg.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

extern LCD_DIS sLCD_DIS;
static TP_DEV sTP_DEV;
static TP_DRAW sTP_Draw;
/*******************************************************************************
function:
        Read the ADC of the channel
parameter:
    Channel_Cmd :   0x90: Read channel Y +, select the ADC resolution is 12 bits, set to differential mode
                    0xd0: Read channel x +, select the ADC resolution is 12 bits, set to differential mode
*******************************************************************************/
static uint16_t TP_Read_ADC(uint8_t CMD)
{
    uint16_t Data = 0;
    uint16_t Data1;

    //A cycle of at least 400ns.
    //hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    //HAL_SPI_Init(&hspi1);

    //TP_CS_0;

    SPI4W_Write_Byte(SPI_CS1, SPI_DC_NONE, false, CMD);
    //Driver_Delay_us(200);
    Driver_Delay_us(75);

    Data = SPI4W_Read_Byte(SPI_CS1, SPI_DC_NONE, false);
    Data <<= 8;
    //Data |= SPI4W_Read_Byte(SPI_CS1, SPI_DC_NONE, true);
    Data1 = SPI4W_Read_Byte(SPI_CS1, SPI_DC_NONE, true);
    dbg("r:%04X,%04x\n",Data,Data1);
    Data |= Data1;
    Data >>= 3;

    //TP_CS_1;

    //LCD SPI speed = 18 MHz
    //hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    //HAL_SPI_Init(&hspi1);

    return Data;
}

/*******************************************************************************
function:
        Read the 5th channel value and exclude the maximum and minimum returns the average
parameter:
    Channel_Cmd :   0x90 :Read channel Y +
                    0xd0 :Read channel x +
*******************************************************************************/
#define READ_TIMES  5   //Number of readings
#define LOST_NUM    1   //Discard value
static uint16_t TP_Read_ADC_Average(uint8_t Channel_Cmd)
{
    uint8_t i, j;
    uint16_t Read_Buff[READ_TIMES];
    uint16_t Read_Sum = 0, Read_Temp = 0;

    //Read and save multiple samples
    for(i = 0; i < READ_TIMES; i++){
        Read_Buff[i] = TP_Read_ADC(Channel_Cmd);
        Driver_Delay_us(200);
    }

    //Sort from small to large
    for (i = 0; i < READ_TIMES  -  1; i ++) {
        for (j = i + 1; j < READ_TIMES; j ++) {
            if (Read_Buff[i] > Read_Buff[j]) {
                Read_Temp = Read_Buff[i];
                Read_Buff[i] = Read_Buff[j];
                Read_Buff[j] = Read_Temp;
            }
        }
    }

    //Exclude the largest and the smallest
    for (i = LOST_NUM; i < READ_TIMES - LOST_NUM; i ++)
        Read_Sum += Read_Buff[i];

    //Averaging
    Read_Temp = Read_Sum / (READ_TIMES - 2 * LOST_NUM);

    return Read_Temp;
}

/*******************************************************************************
function:
        Read X channel and Y channel AD value
parameter:
    Channel_Cmd :   0x90 :Read channel Y +
                    0xd0 :Read channel x +
*******************************************************************************/
static void TP_Read_ADC_XY(uint16_t *pXCh_Adc, uint16_t  *pYCh_Adc )
{
    *pXCh_Adc = TP_Read_ADC_Average(0xD0);
    *pYCh_Adc = TP_Read_ADC_Average(0x90);
}

/*******************************************************************************
function:
        2 times to read the touch screen IC, and the two can not exceed the deviation,
        ERR_RANGE, meet the conditions, then that the correct reading, otherwise the reading error.
parameter:
    Channel_Cmd :   pYCh_Adc = 0x90 :Read channel Y +
                    pXCh_Adc = 0xd0 :Read channel x +
*******************************************************************************/
#define ERR_RANGE 50    //tolerance scope
static bool TP_Read_TwiceADC(uint16_t *pXCh_Adc, uint16_t  *pYCh_Adc )
{
    uint16_t XCh_Adc1, YCh_Adc1, XCh_Adc2, YCh_Adc2;

    //Read the ADC values Read the ADC values twice
    TP_Read_ADC_XY(&XCh_Adc1, &YCh_Adc1);
    dbg("1.(%04x,%04x)\n", XCh_Adc1, YCh_Adc1);
    TP_Read_ADC_XY(&XCh_Adc2, &YCh_Adc2);
    dbg("2.(%04x,%04x)\n", XCh_Adc2, YCh_Adc2);

    //The ADC error used twice is greater than ERR_RANGE to take the average
    if( ((XCh_Adc2 <= XCh_Adc1 && XCh_Adc1 < XCh_Adc2 + ERR_RANGE) ||
         (XCh_Adc1 <= XCh_Adc2 && XCh_Adc2 < XCh_Adc1 + ERR_RANGE))
        && ((YCh_Adc2 <= YCh_Adc1 && YCh_Adc1 < YCh_Adc2 + ERR_RANGE) ||
            (YCh_Adc1 <= YCh_Adc2 && YCh_Adc2 < YCh_Adc1 + ERR_RANGE))) {
        *pXCh_Adc = (XCh_Adc1 + XCh_Adc2) / 2;
        *pYCh_Adc = (YCh_Adc1 + YCh_Adc2) / 2;
        return true;
    }

    //The ADC error used twice is less than ERR_RANGE returns failed
    return false;
}

/*******************************************************************************
function:
        Draw Cross
parameter:
            Xpoint :    The x coordinate of the point
            Ypoint :    The y coordinate of the point
            Color  :    Set color
*******************************************************************************/
static void TP_DrawCross(POINT Xpoint, POINT Ypoint, COLOR Color)
{
    GUI_DrawLine(Xpoint  -  12, Ypoint, Xpoint + 12, Ypoint,
                 Color, LINE_SOLID, DOT_PIXEL_1X1);
    GUI_DrawLine(Xpoint, Ypoint  -  12, Xpoint, Ypoint + 12,
                 Color, LINE_SOLID, DOT_PIXEL_1X1);
    GUI_DrawPoint(Xpoint, Ypoint, Color, DOT_PIXEL_2X2 , DOT_FILL_AROUND);
    GUI_DrawCircle(Xpoint, Ypoint, 6, Color, DRAW_EMPTY, DOT_PIXEL_1X1);
}

/*******************************************************************************
function:
        The corresponding ADC value is displayed on the LC
parameter:
            (Xpoint0 ,Xpoint0): The coordinates of the first point
            (Xpoint1 ,Xpoint1): The coordinates of the second point
            (Xpoint2 ,Xpoint2): The coordinates of the third point
            (Xpoint3 ,Xpoint3): The coordinates of the fourth point
            hwFac   :   Percentage of error
*******************************************************************************/
static void TP_ShowInfo(POINT Xpoint0, POINT Ypoint0,
                        POINT Xpoint1, POINT Ypoint1,
                        POINT Xpoint2, POINT Ypoint2,
                        POINT Xpoint3, POINT Ypoint3,
                        POINT hwFac)
{

    sFONT* TP_Font = &Font12;  //1207
    LENGTH Dx = 3 * (TP_Font->Width);
    LENGTH Dy = TP_Font->Height + 5;

    POINT Xstart = 80;
    POINT Ystart = 120;

    GUI_DrawRectangle(Xstart - 1, Ystart - 1, 320, 240, WHITE, DRAW_FULL, DOT_PIXEL_1X1);

    GUI_DisString_EN(Xstart, Ystart, "x1", TP_Font, FONT_BACKGROUND, RED);
    GUI_DisString_EN(Xstart + 4 * Dx, Ystart, "y1", TP_Font, FONT_BACKGROUND, RED);

    GUI_DisString_EN(Xstart, Ystart + Dy, "x2", TP_Font, FONT_BACKGROUND, RED);
    GUI_DisString_EN(Xstart + 4 * Dx, Ystart + Dy, "y2", TP_Font, FONT_BACKGROUND, RED);

    GUI_DisString_EN(Xstart, Ystart + 2 * Dy, "x3", TP_Font, FONT_BACKGROUND, RED);
    GUI_DisString_EN(Xstart + 4 * Dx, Ystart + 2 * Dy, "y3", TP_Font, FONT_BACKGROUND, RED);

    GUI_DisString_EN(Xstart, Ystart + 3 * Dy, "x4", TP_Font, FONT_BACKGROUND, RED);
    GUI_DisString_EN(Xstart + 4 * Dx, Ystart + 3 * Dy, "y4", TP_Font, FONT_BACKGROUND, RED);

    GUI_DisString_EN(Xstart, Ystart + 4 * Dy, "fac is : ", TP_Font, FONT_BACKGROUND, RED);

    GUI_DisNum(Xstart + Dx, Ystart, Xpoint0, TP_Font, FONT_BACKGROUND, RED);
    GUI_DisNum(Xstart + Dx + 4 * Dx, Ystart, Ypoint0, TP_Font, FONT_BACKGROUND, RED);

    GUI_DisNum(Xstart + Dx, Ystart + Dy, Xpoint1, TP_Font, FONT_BACKGROUND, RED);
    GUI_DisNum(Xstart + Dx + 4 * Dx, Ystart + Dy, Ypoint1, TP_Font, FONT_BACKGROUND, RED);

    GUI_DisNum(Xstart + Dx, Ystart + 2 * Dy, Xpoint2, TP_Font, FONT_BACKGROUND, RED);
    GUI_DisNum(Xstart + Dx + 4 * Dx, Ystart + 2 * Dy, Ypoint2, TP_Font, FONT_BACKGROUND, RED);

    GUI_DisNum(Xstart + Dx, Ystart + 3 * Dy, Xpoint3, TP_Font, FONT_BACKGROUND, RED);
    GUI_DisNum(Xstart + Dx + 4 * Dx, Ystart + 3 * Dy, Ypoint3, TP_Font, FONT_BACKGROUND, RED);

    GUI_DisNum(Xstart + 4 * Dx , Ystart + 4 * Dy, hwFac, TP_Font, FONT_BACKGROUND, RED);
}

/*******************************************************************************
function:
        Calculation
parameter:
        chCoordType:
                    1 : calibration
                    0 : relative position
*******************************************************************************/
static uint8_t TP_Scan(uint8_t chCoordType)
{
    //In X, Y coordinate measurement, IRQ is disabled and output is low
    if (!GET_TP_IRQ) {//Press the button to press
        dbg("TP_IRQ\n");
        //Read the physical coordinates
        if (chCoordType) {
            TP_Read_TwiceADC(&sTP_DEV.Xpoint, &sTP_DEV.Ypoint);
            //Read the screen coordinates
        } else if (TP_Read_TwiceADC(&sTP_DEV.Xpoint, &sTP_DEV.Ypoint)) {
            dbg("(Xad,Yad) = %d,%d\r\n",sTP_DEV.Xpoint,sTP_DEV.Ypoint);
            if(sTP_DEV.TP_Scan_Dir == R2L_D2U) {        //Converts the result to screen coordinates
                sTP_Draw.Xpoint = sTP_DEV.fXfac * sTP_DEV.Xpoint +
                                  sTP_DEV.iXoff;
                sTP_Draw.Ypoint = sTP_DEV.fYfac * sTP_DEV.Ypoint +
                                  sTP_DEV.iYoff;
            } else if(sTP_DEV.TP_Scan_Dir == L2R_U2D) {
                sTP_Draw.Xpoint = sLCD_DIS.LCD_Dis_Column -
                                  sTP_DEV.fXfac * sTP_DEV.Xpoint -
                                  sTP_DEV.iXoff;
                sTP_Draw.Ypoint = sLCD_DIS.LCD_Dis_Page -
                                  sTP_DEV.fYfac * sTP_DEV.Ypoint -
                                  sTP_DEV.iYoff;
            } else if(sTP_DEV.TP_Scan_Dir == U2D_R2L) {
                sTP_Draw.Xpoint = sTP_DEV.fXfac * sTP_DEV.Ypoint +
                                  sTP_DEV.iXoff;
                sTP_Draw.Ypoint = sTP_DEV.fYfac * sTP_DEV.Xpoint +
                                  sTP_DEV.iYoff;
            } else {
                sTP_Draw.Xpoint = sLCD_DIS.LCD_Dis_Column -
                                  sTP_DEV.fXfac * sTP_DEV.Ypoint -
                                  sTP_DEV.iXoff;
                sTP_Draw.Ypoint = sLCD_DIS.LCD_Dis_Page -
                                  sTP_DEV.fYfac * sTP_DEV.Xpoint -
                                  sTP_DEV.iYoff;
            }
            dbg("( x , y ) = %d,%d\r\n",sTP_Draw.Xpoint,sTP_Draw.Ypoint);
        }
        if (0 == (sTP_DEV.chStatus & TP_PRESS_DOWN)) {  //Not being pressed
            sTP_DEV.chStatus = TP_PRESS_DOWN | TP_PRESSED;
            sTP_DEV.Xpoint0 = sTP_DEV.Xpoint;
            sTP_DEV.Ypoint0 = sTP_DEV.Ypoint;
        }
    } else {
        if (sTP_DEV.chStatus & TP_PRESS_DOWN) { //0x80
            sTP_DEV.chStatus &= ~(1 << 7);      //0x00
        } else {
            sTP_DEV.Xpoint0 = 0;
            sTP_DEV.Ypoint0 = 0;
            sTP_DEV.Xpoint = 0xffff;
            sTP_DEV.Ypoint = 0xffff;
        }
    }

    return (sTP_DEV.chStatus & TP_PRESS_DOWN);
}

/*******************************************************************************
function:
        Use the default calibration factor
*******************************************************************************/
void TP_GetAdFac(void)
{
    if (sTP_DEV.TP_Scan_Dir == D2U_L2R ) { //SCAN_DIR_DFT = D2U_L2R
        sTP_DEV.fXfac = 0.092011F ;
        sTP_DEV.fYfac = -0.069320F ;
        sTP_DEV.iXoff = -18L ;
        sTP_DEV.iYoff = 256L ;
    } else if( sTP_DEV.TP_Scan_Dir == L2R_U2D ) {
        sTP_DEV.fXfac = -0.066852F ;
        sTP_DEV.fYfac = -0.090079F ;
        sTP_DEV.iXoff = 251L ;
        sTP_DEV.iYoff = 336L ;
    } else if( sTP_DEV.TP_Scan_Dir == R2L_D2U ) {
        sTP_DEV.fXfac = -0.069076F ;
        sTP_DEV.fYfac = -0.090437F ;
        sTP_DEV.iXoff = 257L  ;
        sTP_DEV.iYoff = 340L ;
    } else if( sTP_DEV.TP_Scan_Dir == U2D_R2L ) {
        sTP_DEV.fXfac = 0.089670F ;
        sTP_DEV.fYfac = -0.067081F ;
        sTP_DEV.iXoff = -17L ;
        sTP_DEV.iYoff = 259L ;
    } else {
        LCD_Clear(LCD_BACKGROUND);
        GUI_DisString_EN(0, 60, "Does not support touch-screen" \
                        "calibration in this direction",
                         &Font16, FONT_BACKGROUND, RED);
    }
}

/*******************************************************************************
function:
        Touch screen adjust
*******************************************************************************/
void TP_Adjust(void)
{
    uint8_t  cnt = 0;
    uint16_t XYpoint_Arr[4][2];
    uint32_t Dx, Dy;
    uint16_t Sqrt1, Sqrt2;
    float Dsqrt;

    LCD_Clear(LCD_BACKGROUND);
    GUI_DisString_EN(10, 60, "Please use the stylus click the cross on "\
                    "the screen. The cross will always move until"\
                    " the screen adjustment is completed.",
                     &Font12, FONT_BACKGROUND, RED);

    uint8_t Mar_Val = 12;
    TP_DrawCross(Mar_Val, Mar_Val, RED);

    sTP_DEV.chStatus = 0;

    while (1) {
        TP_Scan(1);
        if((sTP_DEV.chStatus & 0xC0) == TP_PRESSED) {
            sTP_DEV.chStatus &= ~(1 << 6);
            XYpoint_Arr[cnt][0] = sTP_DEV.Xpoint;
            XYpoint_Arr[cnt][1] = sTP_DEV.Ypoint;
//            dbg("X%d,Y%d = %d,%d\r\n", cnt, cnt, XYpoint_Arr[cnt][0], XYpoint_Arr[cnt][1]);
            cnt ++;
            Driver_Delay_ms(500);

            switch(cnt) {
            case 1:
                TP_DrawCross(Mar_Val, Mar_Val, WHITE);
                TP_DrawCross(sLCD_DIS.LCD_Dis_Column - Mar_Val, Mar_Val, RED);
                break;
            case 2:
                TP_DrawCross(sLCD_DIS.LCD_Dis_Column - Mar_Val, Mar_Val, WHITE);
                TP_DrawCross(Mar_Val, sLCD_DIS.LCD_Dis_Page - Mar_Val, RED);
                break;
            case 3:
                TP_DrawCross(Mar_Val, sLCD_DIS.LCD_Dis_Page - Mar_Val, WHITE);
                TP_DrawCross(sLCD_DIS.LCD_Dis_Column - Mar_Val, sLCD_DIS.LCD_Dis_Page - Mar_Val, RED);
                break;
            case 4:

                // 1.Compare the X direction
                Dx = abs((int16_t)(XYpoint_Arr[0][0] - XYpoint_Arr[1][0]));//x1 - x2
                Dy = abs((int16_t)(XYpoint_Arr[0][1] - XYpoint_Arr[1][1]));//y1 - y2
                Dx *= Dx;
                Dy *= Dy;
                Sqrt1 = sqrt(Dx + Dy);

                Dx = abs((int16_t)(XYpoint_Arr[2][0] - XYpoint_Arr[3][0]));//x3 - x4
                Dy = abs((int16_t)(XYpoint_Arr[2][1] - XYpoint_Arr[3][1]));//y3 - y4
                Dx *= Dx;
                Dy *= Dy;
                Sqrt2 = sqrt(Dx + Dy);

                Dsqrt = (float)Sqrt1 / Sqrt2;
                if(Dsqrt < 0.95 || Dsqrt > 1.05 || Sqrt1 == 0 || Sqrt2 == 0) {
                    dbg("Adjust X direction \r\n");
                    cnt = 0;
                    TP_ShowInfo(XYpoint_Arr[0][0], XYpoint_Arr[0][1],
                                XYpoint_Arr[1][0], XYpoint_Arr[1][1],
                                XYpoint_Arr[2][0], XYpoint_Arr[2][1],
                                XYpoint_Arr[3][0], XYpoint_Arr[3][1],
                                Dsqrt * 100);
                    Driver_Delay_ms(1000);
                    TP_DrawCross(sLCD_DIS.LCD_Dis_Column - Mar_Val,
                                 sLCD_DIS.LCD_Dis_Page - Mar_Val, WHITE);
                    TP_DrawCross(Mar_Val, Mar_Val, RED);
                    continue;
                }

                // 2.Compare the Y direction
                Dx = abs((int16_t)(XYpoint_Arr[0][0] - XYpoint_Arr[2][0])); //x1 - x3
                Dy = abs((int16_t)(XYpoint_Arr[0][1] - XYpoint_Arr[2][1])); //y1 - y3
                Dx *= Dx;
                Dy *= Dy;
                Sqrt1 = sqrt(Dx + Dy);

                Dx = abs((int16_t)(XYpoint_Arr[1][0] - XYpoint_Arr[3][0]));//x2 - x4
                Dy = abs((int16_t)(XYpoint_Arr[1][1] - XYpoint_Arr[3][1]));//y2 - y4
                Dx *= Dx;
                Dy *= Dy;
                Sqrt2 = sqrt(Dx + Dy);//

                Dsqrt = (float)Sqrt1 / Sqrt2;
                if(Dsqrt < 0.95 || Dsqrt > 1.05) {
                    dbg("Adjust Y direction \r\n");
                    cnt = 0;
                    TP_ShowInfo(XYpoint_Arr[0][0], XYpoint_Arr[0][1],
                                XYpoint_Arr[1][0], XYpoint_Arr[1][1],
                                XYpoint_Arr[2][0], XYpoint_Arr[2][1],
                                XYpoint_Arr[3][0], XYpoint_Arr[3][1],
                                Dsqrt * 100);
                    Driver_Delay_ms(1000);
                    TP_DrawCross(sLCD_DIS.LCD_Dis_Column - Mar_Val, sLCD_DIS.LCD_Dis_Page - Mar_Val, WHITE);
                    TP_DrawCross(Mar_Val, Mar_Val, RED);
                    continue;
                }//

                //3.Compare diagonal
                Dx = abs((int16_t)(XYpoint_Arr[1][0] - XYpoint_Arr[2][0]));//x1 - x3
                Dy = abs((int16_t)(XYpoint_Arr[1][1] - XYpoint_Arr[2][1]));//y1 - y3
                Dx *= Dx;
                Dy *= Dy;
                Sqrt1 = sqrt(Dx + Dy);//;

                Dx = abs((int16_t)(XYpoint_Arr[0][0] - XYpoint_Arr[3][0]));//x2 - x4
                Dy = abs((int16_t)(XYpoint_Arr[0][1] - XYpoint_Arr[3][1]));//y2 - y4
                Dx *= Dx;
                Dy *= Dy;
                Sqrt2 = sqrt(Dx + Dy);//

                Dsqrt = (float)Sqrt1 / Sqrt2;
                if(Dsqrt < 0.95 || Dsqrt > 1.05) {
                    dbg("Adjust diagonal direction\r\n");
                    cnt = 0;
                    TP_ShowInfo(XYpoint_Arr[0][0], XYpoint_Arr[0][1],
                                XYpoint_Arr[1][0], XYpoint_Arr[1][1],
                                XYpoint_Arr[2][0], XYpoint_Arr[2][1],
                                XYpoint_Arr[3][0], XYpoint_Arr[3][1],
                                Dsqrt * 100);
                    Driver_Delay_ms(1000);
                    TP_DrawCross(sLCD_DIS.LCD_Dis_Column - Mar_Val, sLCD_DIS.LCD_Dis_Page - Mar_Val, WHITE);
                    TP_DrawCross(Mar_Val, Mar_Val, RED);
                    continue;
                }

                //4.Get the scale factor and offset
                //Get the scanning direction of the touch screen
                sTP_DEV.fXfac = 0;

                //According to the display direction to get the corresponding scale factor and offset
                if(sTP_DEV.TP_Scan_Dir == R2L_D2U) {
                    dbg("R2L_D2U\r\n");

                    sTP_DEV.fXfac = (float)(sLCD_DIS.LCD_Dis_Column - 2 * Mar_Val) /
                                    (int16_t)(XYpoint_Arr[1][0] -
                                              XYpoint_Arr[0][0]);
                    sTP_DEV.fYfac = (float)(sLCD_DIS.LCD_Dis_Page - 2 * Mar_Val) /
                                    (int16_t)(XYpoint_Arr[2][1] -
                                              XYpoint_Arr[0][1]);

                    sTP_DEV.iXoff = (sLCD_DIS.LCD_Dis_Column -
                                     sTP_DEV.fXfac * (XYpoint_Arr[1][0] +
                                                      XYpoint_Arr[0][0])
                                    ) / 2;
                    sTP_DEV.iYoff = (sLCD_DIS.LCD_Dis_Page -
                                     sTP_DEV.fYfac * (XYpoint_Arr[2][1] +
                                                      XYpoint_Arr[0][1])
                                    ) / 2;
                } else if(sTP_DEV.TP_Scan_Dir == L2R_U2D) {
                    dbg("L2R_U2D\r\n");

                    sTP_DEV.fXfac = (float)(sLCD_DIS.LCD_Dis_Column - 2 * Mar_Val) /
                                    (int16_t)(XYpoint_Arr[0][0] -
                                              XYpoint_Arr[1][0]);
                    sTP_DEV.fYfac = (float)(sLCD_DIS.LCD_Dis_Page - 2 * Mar_Val) /
                                    (int16_t)(XYpoint_Arr[0][1] -
                                              XYpoint_Arr[2][1]);

                    sTP_DEV.iXoff = (sLCD_DIS.LCD_Dis_Column -
                                     sTP_DEV.fXfac * (XYpoint_Arr[0][0] +
                                                      XYpoint_Arr[1][0])
                                    ) / 2;
                    sTP_DEV.iYoff = (sLCD_DIS.LCD_Dis_Page - sTP_DEV.fYfac *
                                     (XYpoint_Arr[0][1] + XYpoint_Arr[2][1])) / 2;
                } else if (sTP_DEV.TP_Scan_Dir == U2D_R2L) {
                    dbg("U2D_R2L\r\n");

                    sTP_DEV.fXfac = (float)(sLCD_DIS.LCD_Dis_Column - 2 * Mar_Val) /
                                    (int16_t)(XYpoint_Arr[1][1] - XYpoint_Arr[0][1]);
                    sTP_DEV.fYfac = (float)(sLCD_DIS.LCD_Dis_Page - 2 * Mar_Val) /
                                    (int16_t)(XYpoint_Arr[2][0] - XYpoint_Arr[0][0]);

                    sTP_DEV.iXoff = (sLCD_DIS.LCD_Dis_Column -
                                     sTP_DEV.fXfac * (XYpoint_Arr[1][1] +
                                                      XYpoint_Arr[0][1])
                                    ) / 2;
                    sTP_DEV.iYoff = (sLCD_DIS.LCD_Dis_Page -
                                     sTP_DEV.fYfac * (XYpoint_Arr[2][0] +
                                                      XYpoint_Arr[0][0])
                                    ) / 2;
                } else {
                    dbg("D2U_L2R\r\n");

                    sTP_DEV.fXfac = (float)(sLCD_DIS.LCD_Dis_Column - 2 * Mar_Val) /
                                    (int16_t)(XYpoint_Arr[0][1] -
                                              XYpoint_Arr[1][1]);
                    sTP_DEV.fYfac = (float)(sLCD_DIS.LCD_Dis_Page - 2 * Mar_Val) /
                                    (int16_t)(XYpoint_Arr[0][0] -
                                              XYpoint_Arr[2][0]);

                    sTP_DEV.iXoff = (sLCD_DIS.LCD_Dis_Column -
                                     sTP_DEV.fXfac * (XYpoint_Arr[0][1] +
                                                      XYpoint_Arr[1][1])
                                    ) / 2;
                    sTP_DEV.iYoff = (sLCD_DIS.LCD_Dis_Page -
                                     sTP_DEV.fYfac * (XYpoint_Arr[0][0] +
                                                      XYpoint_Arr[2][0])
                                    ) / 2;
                }

                dbg("sTP_DEV.fXfac = %f \r\n", sTP_DEV.fXfac);
                dbg("sTP_DEV.fYfac = %f \r\n", sTP_DEV.fYfac);
                dbg("sTP_DEV.iXoff = %d \r\n", sTP_DEV.iXoff);
                dbg("sTP_DEV.iYoff = %d \r\n", sTP_DEV.iYoff);

                //6.Calibration is successful
                dbg("Adjust OK\r\n");
                LCD_Clear(LCD_BACKGROUND);
                GUI_DisString_EN(15, 110, "Touch Screen Adjust OK!",
                                 &Font16 , FONT_BACKGROUND , RED);
                Driver_Delay_ms(1000);
                LCD_Clear(LCD_BACKGROUND);
                return;
                //Exception handling,Reset  Initial value
            default :
                cnt = 0;
                TP_DrawCross(sLCD_DIS.LCD_Dis_Column - Mar_Val,
                             sLCD_DIS.LCD_Dis_Page - Mar_Val, WHITE);
                TP_DrawCross(Mar_Val, Mar_Val, RED);
                GUI_DisString_EN(40, 26, "TP Need readjust!",
                                 &Font16 , FONT_BACKGROUND , RED);
                break;
            }
        }

    }
}

/*******************************************************************************
function:
        Paint the Delete key and paint color choose area
*******************************************************************************/
void TP_Dialog(void)
{
    LCD_Clear(WHITE);
    dbg("Drawing...\r\n");
    //Horizontal screen display
    if(sLCD_DIS.LCD_Dis_Column > sLCD_DIS.LCD_Dis_Page) {
        //Clear screen
        GUI_DisString_EN(sLCD_DIS.LCD_Dis_Column - 60, 0,
                         "CLEAR", &Font16, RED, BLUE);
        //adjustment
        GUI_DisString_EN(sLCD_DIS.LCD_Dis_Column - 120, 0,
                         "AD", &Font16, RED, BLUE);
        //choose the color
        GUI_DrawRectangle(sLCD_DIS.LCD_Dis_Column - 50, 20,
                          sLCD_DIS.LCD_Dis_Column, 50,
                          BLUE, DRAW_FULL, DOT_PIXEL_1X1);
        GUI_DrawRectangle(sLCD_DIS.LCD_Dis_Column - 50,
                          60, sLCD_DIS.LCD_Dis_Column, 90,
                          GREEN, DRAW_FULL, DOT_PIXEL_1X1);
        GUI_DrawRectangle(sLCD_DIS.LCD_Dis_Column - 50, 100,
                          sLCD_DIS.LCD_Dis_Column, 130,
                          RED, DRAW_FULL, DOT_PIXEL_1X1);
        GUI_DrawRectangle(sLCD_DIS.LCD_Dis_Column - 50, 140,
                          sLCD_DIS.LCD_Dis_Column, 170,
                          YELLOW, DRAW_FULL, DOT_PIXEL_1X1);
        GUI_DrawRectangle(sLCD_DIS.LCD_Dis_Column - 50, 180,
                          sLCD_DIS.LCD_Dis_Column, 210,
                          BLACK, DRAW_FULL, DOT_PIXEL_1X1);

    } else { //Vertical screen display
        GUI_DisString_EN(sLCD_DIS.LCD_Dis_Column - 60, 0,
                         "CLEAR", &Font16, RED, BLUE);
        GUI_DisString_EN(sLCD_DIS.LCD_Dis_Column - 120, 0,
                         "AD", &Font16, RED, BLUE);
        GUI_DrawRectangle(20, 20, 50, 70, BLUE, DRAW_FULL, DOT_PIXEL_1X1);
        GUI_DrawRectangle(60, 20, 90, 70, GREEN, DRAW_FULL, DOT_PIXEL_1X1);
        GUI_DrawRectangle(100, 20, 130, 70, RED, DRAW_FULL, DOT_PIXEL_1X1);
        GUI_DrawRectangle(140, 20, 170, 70, YELLOW, DRAW_FULL, DOT_PIXEL_1X1);
        GUI_DrawRectangle(180, 20, 210, 70, BLACK, DRAW_FULL, DOT_PIXEL_1X1);
    }
}


/*******************************************************************************
function:
        Draw Board
*******************************************************************************/
void TP_DrawBoard(void)
{
//  sTP_DEV.chStatus &= ~(1 << 6);
    TP_Scan(0);
    if (sTP_DEV.chStatus & TP_PRESS_DOWN) {     //Press the button
        if (sTP_Draw.Xpoint < sLCD_DIS.LCD_Dis_Column &&
            sTP_Draw.Ypoint < sLCD_DIS.LCD_Dis_Page) {  //Determine whether the law is legal
            //Horizontal screen
            if(sLCD_DIS.LCD_Dis_Column > sLCD_DIS.LCD_Dis_Page) {       //Judgment is horizontal screen
                if (sTP_Draw.Xpoint > (sLCD_DIS.LCD_Dis_Column - 60) &&
                    sTP_Draw.Ypoint < 16) {     //Clear Board
                    TP_Dialog();
                } else if(sTP_Draw.Xpoint > (sLCD_DIS.LCD_Dis_Column - 120) &&
                          sTP_Draw.Xpoint < (sLCD_DIS.LCD_Dis_Column - 80) &&
                          sTP_Draw.Ypoint < 24) { //afresh adjustment
                    TP_Adjust();
                    TP_Dialog();
                } else if(sTP_Draw.Xpoint > (sLCD_DIS.LCD_Dis_Column - 50 ) &&
                          sTP_Draw.Xpoint < sLCD_DIS.LCD_Dis_Column &&
                          sTP_Draw.Ypoint > 20 &&
                          sTP_Draw.Ypoint < 50) {
                    sTP_Draw.Color = BLUE;
                } else if(sTP_Draw.Xpoint > (sLCD_DIS.LCD_Dis_Column - 50 ) &&
                          sTP_Draw.Xpoint < sLCD_DIS.LCD_Dis_Column &&
                          sTP_Draw.Ypoint > 60 &&
                          sTP_Draw.Ypoint < 90) {
                    sTP_Draw.Color = GREEN;
                } else if(sTP_Draw.Xpoint > (sLCD_DIS.LCD_Dis_Column - 50 ) &&
                          sTP_Draw.Xpoint < sLCD_DIS.LCD_Dis_Column &&
                          sTP_Draw.Ypoint > 100 &&
                          sTP_Draw.Ypoint < 130) {
                    sTP_Draw.Color = RED;
                } else if(sTP_Draw.Xpoint > (sLCD_DIS.LCD_Dis_Column - 50 ) &&
                          sTP_Draw.Xpoint < sLCD_DIS.LCD_Dis_Column &&
                          sTP_Draw.Ypoint > 140 &&
                          sTP_Draw.Ypoint < 170) {
                    sTP_Draw.Color = YELLOW;
                } else if(sTP_Draw.Xpoint > (sLCD_DIS.LCD_Dis_Column - 50 ) &&
                          sTP_Draw.Xpoint < sLCD_DIS.LCD_Dis_Column &&
                          sTP_Draw.Ypoint > 180 &&
                          sTP_Draw.Ypoint < 210) {
                    sTP_Draw.Color = BLACK;
                } else {
                    GUI_DrawPoint(sTP_Draw.Xpoint, sTP_Draw.Ypoint,
                                  sTP_Draw.Color, DOT_PIXEL_1X1, DOT_FILL_AROUND );
                    GUI_DrawPoint(sTP_Draw.Xpoint + 1, sTP_Draw.Ypoint,
                                  sTP_Draw.Color, DOT_PIXEL_1X1, DOT_FILL_AROUND );
                    GUI_DrawPoint(sTP_Draw.Xpoint, sTP_Draw.Ypoint + 1,
                                  sTP_Draw.Color, DOT_PIXEL_1X1, DOT_FILL_AROUND );
                    GUI_DrawPoint(sTP_Draw.Xpoint + 1, sTP_Draw.Ypoint + 1,
                                  sTP_Draw.Color, DOT_PIXEL_1X1, DOT_FILL_AROUND );
                }
                //Vertical screen
            } else {
                if (sTP_Draw.Xpoint > (sLCD_DIS.LCD_Dis_Column - 60) &&
                    sTP_Draw.Ypoint < 16) {//Clear Board
                    TP_Dialog();
                } else if(sTP_Draw.Xpoint > (sLCD_DIS.LCD_Dis_Column - 120) &&
                          sTP_Draw.Xpoint < (sLCD_DIS.LCD_Dis_Column - 80) &&
                          sTP_Draw.Ypoint < 24) { //afresh adjustment
                    TP_Adjust();
                    TP_Dialog();
                } else if(sTP_Draw.Xpoint > 20 && sTP_Draw.Xpoint < 50 &&
                          sTP_Draw.Ypoint > 20 &&
                          sTP_Draw.Ypoint < 70) {
                    sTP_Draw.Color = BLUE;
                } else if(sTP_Draw.Xpoint > 60 &&
                          sTP_Draw.Xpoint < 90 &&
                          sTP_Draw.Ypoint > 20 &&
                          sTP_Draw.Ypoint < 70) {
                    sTP_Draw.Color = GREEN;
                } else if(sTP_Draw.Xpoint > 100 &&
                          sTP_Draw.Xpoint < 130 &&
                          sTP_Draw.Ypoint > 20 &&
                          sTP_Draw.Ypoint < 70) {
                    sTP_Draw.Color = RED;
                } else if(sTP_Draw.Xpoint > 140 &&
                          sTP_Draw.Xpoint < 170 &&
                          sTP_Draw.Ypoint > 20 &&
                          sTP_Draw.Ypoint < 70) {
                    sTP_Draw.Color = YELLOW;
                } else if(sTP_Draw.Xpoint > 180 &&
                          sTP_Draw.Xpoint < 210 &&
                          sTP_Draw.Ypoint > 20 &&
                          sTP_Draw.Ypoint < 70) {
                    sTP_Draw.Color = BLACK;
                } else {
                    GUI_DrawPoint(sTP_Draw.Xpoint, sTP_Draw.Ypoint,
                                  sTP_Draw.Color, DOT_PIXEL_1X1, DOT_FILL_AROUND );
                    GUI_DrawPoint(sTP_Draw.Xpoint + 1, sTP_Draw.Ypoint,
                                  sTP_Draw.Color, DOT_PIXEL_1X1, DOT_FILL_AROUND );
                    GUI_DrawPoint(sTP_Draw.Xpoint, sTP_Draw.Ypoint + 1,
                                  sTP_Draw.Color, DOT_PIXEL_1X1, DOT_FILL_AROUND );
                    GUI_DrawPoint(sTP_Draw.Xpoint + 1, sTP_Draw.Ypoint + 1,
                                  sTP_Draw.Color, DOT_PIXEL_1X1, DOT_FILL_AROUND );
                }
            }
        }
    }
}

void TP_Read_XY_From_Console(void)
{
    TP_Read_ADC_XY(&sTP_DEV.Xpoint, &sTP_DEV.Ypoint);
    dbg("Xpoint:%04x, Ypoint:%04x\n",sTP_DEV.Xpoint,sTP_DEV.Ypoint);
}

/*******************************************************************************
function:
        Touch pad initialization
*******************************************************************************/
void TP_Init( LCD_SCAN_DIR Lcd_ScanDir )
{
    //TP_CS_1;
    gpioa_init(GPIO_IDX_TP_CS);
    gpioa_dir_out(GPIO_IDX_TP_CS);
    gpioa_set(GPIO_IDX_TP_CS);

    //TP_INT
    gpioa_init(GPIO_IDX_TP_INT);
    gpioa_dir_in(GPIO_IDX_TP_INT);

    sTP_DEV.TP_Scan_Dir = Lcd_ScanDir;

    TP_Read_ADC_XY(&sTP_DEV.Xpoint, &sTP_DEV.Ypoint);
    dbg("Xpoint:%04x, Ypoint:%04x\n",sTP_DEV.Xpoint,sTP_DEV.Ypoint);

    TP_Read_ADC_XY(&sTP_DEV.Xpoint, &sTP_DEV.Ypoint);
    dbg("Xpoint:%04x, Ypoint:%04x\n",sTP_DEV.Xpoint,sTP_DEV.Ypoint);
}
