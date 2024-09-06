/*****************************************************************************
* | File        :   LCD_Driver.h
* | Author      :   Waveshare team
* | Function    :   ILI9486 Drive function
* | Info        :
*   Image scanning:
*      Please use progressive scanning to generate images or fonts
*----------------
* | This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/

/**************************Intermediate driver layer**************************/

#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#include <stdbool.h>
#include "chip.h"

#define COLOR               uint16_t        //The variable type of the color (unsigned short)
#define POINT               uint16_t        //The type of coordinate (unsigned short)
#define LENGTH              uint16_t        //The type of coordinate (unsigned short)

/********************************************************************************
function:
        Define the full screen height length of the display
********************************************************************************/
#define LCD_X_MAXPIXEL  320  //LCD width maximum memory
#define LCD_Y_MAXPIXEL  240 //LCD height maximum memory
#define LCD_X    0
#define LCD_Y    0

#define LCD_WIDTH   LCD_X_MAXPIXEL  //LCD width
#define LCD_HEIGHT  LCD_Y_MAXPIXEL  //LCD height

/********************************************************************************
function:
            scanning method
********************************************************************************/
typedef enum {
//Vertical screen:
    L2R_U2D  = 0,   //The display interface is displayed , left to right, up to down
    L2R_D2U  ,
    R2L_U2D  ,
    R2L_D2U  ,
//Horizontal screen:
    U2D_L2R  ,
    U2D_R2L  ,
    D2U_L2R  ,
    D2U_R2L  ,
} LCD_SCAN_DIR;
#define SCAN_DIR_DFT  U2D_R2L  //Default scan direction = U2D_R2L

/********************************************************************************
function:
    Defines the total number of rows in the display area
********************************************************************************/
typedef struct {
    LENGTH LCD_Dis_Column;  //COLUMN
    LENGTH LCD_Dis_Page;    //PAGE
    LCD_SCAN_DIR LCD_Scan_Dir;
    POINT LCD_X_Adjust;     //LCD x actual display position calibration
    POINT LCD_Y_Adjust;     //LCD y actual display position calibration
} LCD_DIS;

/********************************************************************************
function:
            Macro definition variable name
********************************************************************************/
void LCD_Init(LCD_SCAN_DIR LCD_ScanDir, uint16_t LCD_BLval);
void LCD_SetGramScanWay(LCD_SCAN_DIR Scan_dir);

void LCD_WriteReg(uint8_t Reg, bool cs_end);
void LCD_WriteData(uint8_t Data);

void LCD_SetWindow(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend);
void LCD_SetCursor(POINT Xpoint, POINT Ypoint);
void LCD_SetColor(COLOR Color ,POINT Xpoint, POINT Ypoint);
void LCD_SetPointlColor(POINT Xpoint, POINT Ypoint, COLOR Color);
void LCD_SetArealColor(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend,COLOR  Color);
void LCD_Clear(COLOR  Color);

#endif
