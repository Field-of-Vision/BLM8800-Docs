/*****************************************************************************
* | File        :   lcd_driver.c
* | Author      :   Waveshare team
* | Function    :   ILI9486 Drive function
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* | This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/

/**************************Intermediate driver layer**************************/
#include "lcd_driver.h"
#include "dev_config.h"
#include "dbg.h"

LCD_DIS sLCD_DIS;

/*******************************************************************************
function:
    Hardware reset
*******************************************************************************/
static void LCD_Reset(void)
{
    /* Set iomux & direction */
    gpioa_init(GPIO_IDX_LCD_RST);
    gpioa_dir_out(GPIO_IDX_LCD_RST);
    gpioa_set(GPIO_IDX_LCD_RST); //LCD_RST_1;
    Driver_Delay_ms(20);//500
    gpioa_clr(GPIO_IDX_LCD_RST); //LCD_RST_0;
    Driver_Delay_ms(20);//500
    gpioa_set(GPIO_IDX_LCD_RST); //LCD_RST_1;
    Driver_Delay_ms(20);//500
}

static void LCD_SetBackLight(uint16_t value)
{
    if(value > 1000)
        value = 1000;
    PWM_SetValue(value);
    dbg("BackLight Proportion = %d%% \r\n",value / 10);
}

/*******************************************************************************
function:
        Write register address and data
*******************************************************************************/
void LCD_WriteReg(uint8_t Reg, bool cs_end)
{
    SPI4W_Write_Byte(SPI_CS0, SPI_DC_CMD, cs_end, Reg);
}

void LCD_WriteData(uint8_t Data)
{
    SPI4W_Write_Byte(SPI_CS0, SPI_DC_DATA, true, Data);
}

uint8_t LCD_ReadData(bool cs_end)
{
    return SPI4W_Read_Byte(SPI_CS0, SPI_DC_DATA, cs_end); // dummy data
}

/*******************************************************************************
function:
        Write register data
*******************************************************************************/
static void LCD_Write_AllData(uint16_t Data, uint32_t DataLen)
{
    uint32_t i;
    for(i = 0; i < DataLen; i++) {
        SPI4W_Write_Byte(SPI_CS0, SPI_DC_DATA, true, (uint8_t)(Data >> 8));
        SPI4W_Write_Byte(SPI_CS0, SPI_DC_DATA, true, (uint8_t)(Data & 0XFF));
    }
}

/*******************************************************************************
function:
        Common register initialization
*******************************************************************************/
static void LCD_InitReg(void)
{
    LCD_WriteReg(0xCB, true);//
    LCD_WriteData(0x39);
    LCD_WriteData(0x2C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x34);
    LCD_WriteData(0x02);

    LCD_WriteReg(0xCF, true);
    LCD_WriteData(0x00);
    LCD_WriteData(0XC1);
    LCD_WriteData(0X30);

    LCD_WriteReg(0xE8, true);
    LCD_WriteData(0x85);
    LCD_WriteData(0x00);
    LCD_WriteData(0x78);

    LCD_WriteReg(0xEA, true);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);

    LCD_WriteReg(0xED, true);
    LCD_WriteData(0x64);
    LCD_WriteData(0x03);
    LCD_WriteData(0X12);
    LCD_WriteData(0X81);

    LCD_WriteReg(0xF7, true);// Memory Access Control
    LCD_WriteData(0x20);

    LCD_WriteReg(0xC0, true);//Power Control 1
    LCD_WriteData(0x23);

    LCD_WriteReg(0xC1, true);//Power Control 2
    LCD_WriteData(0x10);

    LCD_WriteReg(0xC5, true);//VCOM Control 1
    LCD_WriteData(0x3e);
    LCD_WriteData(0x28);

    LCD_WriteReg(0xC7, true);//VCOM Control 2
    LCD_WriteData(0x86);

    LCD_WriteReg(0xB1, true);//Frame Rate Control (In Normal Mode/Full Colors)
    LCD_WriteData(0x00);
    LCD_WriteData(0x18);

    LCD_WriteReg(0xF2, true);
    LCD_WriteData(0x00);

    LCD_WriteReg(0x26, true);//Gamma Set
    LCD_WriteData(0x01);

    LCD_WriteReg(0xE0, true);
    LCD_WriteData(0x0F);
    LCD_WriteData(0x31);
    LCD_WriteData(0x2B);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x0E);
    LCD_WriteData(0x08);
    LCD_WriteData(0x4E);
    LCD_WriteData(0xF1);
    LCD_WriteData(0x37);
    LCD_WriteData(0x07);
    LCD_WriteData(0x10);
    LCD_WriteData(0x03);
    LCD_WriteData(0x0E);
    LCD_WriteData(0x09);
    LCD_WriteData(0x00);

    LCD_WriteReg(0XE1, true);
    LCD_WriteData(0x00);
    LCD_WriteData(0x0E);
    LCD_WriteData(0x14);
    LCD_WriteData(0x03);
    LCD_WriteData(0x11);
    LCD_WriteData(0x07);
    LCD_WriteData(0x31);
    LCD_WriteData(0xC1);
    LCD_WriteData(0x48);
    LCD_WriteData(0x08);
    LCD_WriteData(0x0F);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x31);
    LCD_WriteData(0x36);
    LCD_WriteData(0x0F);

    LCD_WriteReg(0x3A, true);// Pixel Format Set
    LCD_WriteData(0x55);

}

/********************************************************************************
function:   Set the display scan and color transfer modes
parameter:
        Scan_dir   :   Scan direction
        Colorchose :   RGB or GBR color format
********************************************************************************/
void LCD_SetGramScanWay(LCD_SCAN_DIR Scan_dir)
{
    uint16_t MemoryAccessReg_Data = 0; //addr:0x36
    uint16_t DisFunReg_Data = 0; //addr:0xB6

    // Gets the scan direction of GRAM
    switch (Scan_dir) {
    case L2R_U2D:
        MemoryAccessReg_Data = 0x08;//0x08 | 0X8
        DisFunReg_Data = 0x22;
        break;
    case L2R_D2U:
        MemoryAccessReg_Data = 0x08;
        DisFunReg_Data = 0x62;
        break;
    case R2L_U2D: //0X4
        MemoryAccessReg_Data = 0x08;
        DisFunReg_Data = 0x02;
        break;
    case R2L_D2U: //0XC
        MemoryAccessReg_Data = 0x08;
        DisFunReg_Data = 0x42;
        break;
    case U2D_L2R: //0X2
        MemoryAccessReg_Data = 0x28;
        DisFunReg_Data = 0x22;
        break;
    case U2D_R2L: //0X6
        MemoryAccessReg_Data = 0x28;
        DisFunReg_Data = 0x02;
        break;
    case D2U_L2R: //0XA
        MemoryAccessReg_Data = 0x28;
        DisFunReg_Data = 0x62;
        break;
    case D2U_R2L: //0XE
        MemoryAccessReg_Data = 0x28;
        DisFunReg_Data = 0x42;
        break;
    default:
        break;
    }

    //Get the screen scan direction
    sLCD_DIS.LCD_Scan_Dir = Scan_dir;

    //Get GRAM and LCD width and height
    if(Scan_dir == L2R_U2D || Scan_dir == L2R_D2U || Scan_dir == R2L_U2D || Scan_dir == R2L_D2U) {
        dbg("Vertical screen...\r\n");
        sLCD_DIS.LCD_Dis_Column = LCD_HEIGHT ;
        sLCD_DIS.LCD_Dis_Page = LCD_WIDTH ;
    } else {
        dbg("Horizontal screen...\r\n");
        sLCD_DIS.LCD_Dis_Column = LCD_WIDTH ;
        sLCD_DIS.LCD_Dis_Page = LCD_HEIGHT ;
    }

    // Set the read / write scan direction of the frame memory
    LCD_WriteReg(0xB6, true);
    LCD_WriteData(0X00);
    LCD_WriteData(DisFunReg_Data | 0x80);
    LCD_WriteData(0x3B);

    LCD_WriteReg(0x36, true);
    LCD_WriteData(MemoryAccessReg_Data);
}

/********************************************************************************
function:
    initialization
********************************************************************************/
void LCD_Init(LCD_SCAN_DIR LCD_ScanDir, uint16_t LCD_BLval)
{
#if 1
    //Hardware reset
    LCD_Reset();
#else
    //Software reset
    LCD_WriteReg(0x01);
    Driver_Delay_ms(5);
    LCD_WriteReg(0x28);//display off
#endif

    #if 0
    uint8_t dummy, id[3];
    LCD_WriteReg(0x04, false);
    dummy = LCD_ReadData(false);
    id[0] = LCD_ReadData(false);
    id[1] = LCD_ReadData(false);
    id[2] = LCD_ReadData(true);
    dbg("read id: %02x, id0=%02x, id1=%02x, id2=%02x\n", dummy, id[0], id[1], id[2]);
    #endif

#if 1
    //BackLight
    LCD_SetBackLight(LCD_BLval);

    //Set the initialization register
    LCD_InitReg();

    //Set the display scan and color transfer modes
    LCD_SetGramScanWay( LCD_ScanDir);
    Driver_Delay_ms(200);

    //sleep out
    LCD_WriteReg(0x11, true);
    Driver_Delay_ms(120);

    //Turn on the LCD display
    LCD_WriteReg(0x29, true);
#else
    LCD_WriteReg(0xCF, true);
    LCD_WriteData(0x00);
    LCD_WriteData(0x83);
    LCD_WriteData(0x30);
    LCD_WriteReg(0xED, true);
    LCD_WriteData(0x64);
    LCD_WriteData(0x03);
    LCD_WriteData(0x12);
    LCD_WriteData(0x81);
    LCD_WriteReg(0xE8, true);
    LCD_WriteData(0x85);
    LCD_WriteData(0x01);
    LCD_WriteData(0x79);
    LCD_WriteReg(0xCB, true);
    LCD_WriteData(0x39);
    LCD_WriteData(0x2C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x34);
    LCD_WriteData(0x02);
    LCD_WriteReg(0xF7, true);
    LCD_WriteData(0x20);
    LCD_WriteReg(0xEA, true);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);

    LCD_WriteReg(0xC0, true);//Power Control 1
    LCD_WriteData(0x26);

    LCD_WriteReg(0xC1, true);//Power Control 2
    LCD_WriteData(0x11);

    LCD_WriteReg(0xC5);//VCOM Control 1
    LCD_WriteData(0x35);
    LCD_WriteData(0x3E);

    LCD_WriteReg(0xC7, true);//VCOM Control 2
    LCD_WriteData(0xBE);

    LCD_WriteReg(0x3A, true);//
    LCD_WriteData(0x55);

    LCD_WriteReg(0xB1, true);//Frame Rate Control (In Normal Mode/Full Colors)
    LCD_WriteData(0x00);
    LCD_WriteData(0x1B);

    //LCD_WriteReg(0xF2, true);//Gamma function disable
    //LCD_WriteData(0x08);
    LCD_WriteReg(0x26, true);//Gamma Set
    LCD_WriteData(0x01);

    //Get the screen scan direction
    sLCD_DIS.LCD_Scan_Dir = LCD_ScanDir;

    //Get GRAM and LCD width and height
    if(LCD_ScanDir == L2R_U2D || LCD_ScanDir == L2R_D2U || LCD_ScanDir == R2L_U2D || LCD_ScanDir == R2L_D2U) {
        dbg("Vertical screen...\r\n");
        sLCD_DIS.LCD_Dis_Column = LCD_HEIGHT ;
        sLCD_DIS.LCD_Dis_Page = LCD_WIDTH ;
    } else {
        dbg("Horizontal screen...\r\n");
        sLCD_DIS.LCD_Dis_Column = LCD_WIDTH ;
        sLCD_DIS.LCD_Dis_Page = LCD_HEIGHT ;
    }
    LCD_WriteReg(0xB7, true);//Entry mode set
    LCD_WriteData(0x07);
    LCD_WriteReg(0xB6, true);//
    LCD_WriteData(0x0A);
    LCD_WriteData(0x82);
    LCD_WriteData(0x27);
    LCD_WriteData(0x00);

    LCD_WriteReg(0x11, true);//sleep out
    Driver_Delay_ms(100);
    LCD_WriteReg(0x29, true);//display on
    Driver_Delay_ms(20);
#endif
}

/********************************************************************************
function:   Sets the start position and size of the display area
parameter:
    Xstart  :   X direction Start coordinates
    Ystart  :   Y direction Start coordinates
    Xend    :   X direction end coordinates
    Yend    :   Y direction end coordinates
********************************************************************************/
void LCD_SetWindow(POINT Xstart, POINT Ystart,  POINT Xend, POINT Yend)
{
    //set the X coordinates
    LCD_WriteReg(0x2A, true);
    LCD_WriteData(Xstart >> 8);                 //Set the horizontal starting point to the high octet
    LCD_WriteData(Xstart & 0xff);                   //Set the horizontal starting point to the low octet
    LCD_WriteData((Xend - 1) >> 8); //Set the horizontal end to the high octet
    LCD_WriteData((Xend - 1) & 0xff);   //Set the horizontal end to the low octet

    //set the Y coordinates
    LCD_WriteReg(0x2B, true);
    LCD_WriteData(Ystart >> 8);
    LCD_WriteData(Ystart & 0xff );
    LCD_WriteData((Yend - 1) >> 8);
    LCD_WriteData((Yend - 1) & 0xff);

    LCD_WriteReg(0x2C, true);
}

/********************************************************************************
function:   Set the display point (Xpoint, Ypoint)
parameter:
    xStart :   X direction Start coordinates
    xEnd   :   X direction end coordinates
********************************************************************************/
void LCD_SetCursor(POINT Xpoint, POINT Ypoint)
{
    LCD_SetWindow(Xpoint, Ypoint, Xpoint, Ypoint);
}

/********************************************************************************
function:   Set show color
parameter:
        Color  :   Set show color,16-bit depth
********************************************************************************/
//static void LCD_SetColor(LENGTH Dis_Width, LENGTH Dis_Height, COLOR Color ){
void LCD_SetColor(COLOR Color , POINT Xpoint, POINT Ypoint)
{
    LCD_Write_AllData(Color , (uint32_t)Xpoint * (uint32_t)Ypoint);
}

/********************************************************************************
function:   Point (Xpoint, Ypoint) Fill the color
parameter:
    Xpoint :   The x coordinate of the point
    Ypoint :   The y coordinate of the point
    Color  :   Set the color
********************************************************************************/
void LCD_SetPointlColor( POINT Xpoint, POINT Ypoint, COLOR Color)
{
    if ((Xpoint <= sLCD_DIS.LCD_Dis_Column) && (Ypoint <= sLCD_DIS.LCD_Dis_Page)) {
        LCD_SetCursor (Xpoint, Ypoint);
        LCD_SetColor(Color, 1, 1);
    }
}

/********************************************************************************
function:   Fill the area with the color
parameter:
    Xstart :   Start point x coordinate
    Ystart :   Start point y coordinate
    Xend   :   End point coordinates
    Yend   :   End point coordinates
    Color  :   Set the color
********************************************************************************/
void LCD_SetArealColor(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend,  COLOR Color)
{
    if((Xend > Xstart) && (Yend > Ystart)) {
        LCD_SetWindow(Xstart , Ystart , Xend , Yend  );
        LCD_SetColor ( Color , Xend - Xstart, Yend - Ystart);
    }
}

/********************************************************************************
function:
            Clear screen
********************************************************************************/
void LCD_Clear(COLOR  Color)
{
    LCD_SetArealColor(0, 0, sLCD_DIS.LCD_Dis_Column , sLCD_DIS.LCD_Dis_Page , Color);
}
