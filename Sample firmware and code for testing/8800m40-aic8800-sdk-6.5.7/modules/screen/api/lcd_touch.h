/*****************************************************************************
* | File        :   lcd_touch.h
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
#ifndef _LCD_TOUCH_H_
#define _LCD_TOUCH_H_

#include "dev_config.h"

#include "lcd_driver.h"
#include "lcd_gui.h"

#define TP_PRESS_DOWN           0x80
#define TP_PRESSED              0x40

//Touch screen structure
typedef struct {
    POINT Xpoint0;
    POINT Ypoint0;
    POINT Xpoint;
    POINT Ypoint;
    uint8_t chStatus;
    uint8_t chType;
    int16_t iXoff;
    int16_t iYoff;
    float fXfac;
    float fYfac;
    //Select the coordinates of the XPT2046 touch screen relative to what scan direction
    LCD_SCAN_DIR TP_Scan_Dir;
}TP_DEV;

//Brush structure
typedef struct{
    POINT Xpoint;
    POINT Ypoint;
    COLOR Color;
    DOT_PIXEL DotPixel;
}TP_DRAW;


void TP_GetAdFac(void);
void TP_Adjust(void);
void TP_Dialog(void);
void TP_DrawBoard(void);
void TP_Read_XY_From_Console(void);
void TP_Init(LCD_SCAN_DIR Lcd_ScanDir);
#endif
