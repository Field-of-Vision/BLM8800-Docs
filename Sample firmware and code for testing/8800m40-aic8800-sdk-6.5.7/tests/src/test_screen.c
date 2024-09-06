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
#include "dev_config.h"
#include "lcd_driver.h"
#include "lcd_gui.h"
#include "lcd_touch.h"
#include "dbg.h"
#include "console.h"

#ifdef CFG_TEST_SCREEN

/*
 * MACROS
 ****************************************************************************************
 */
#define USER_PRINTF             dbg

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTIONS
 ****************************************************************************************
 */
static int tp_read_xy(int argc, char * const argv[])
{
    TP_Read_XY_From_Console();
    return ERR_NONE;
}

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void screen_test(void)
{
    LCD_SCAN_DIR LCD_ScanDir = U2D_R2L;
    USER_PRINTF("\nStart test case: screen\n");

    console_cmd_add("tp", "tp_read_xy", 1, 1, tp_read_xy);
    SPI4W_Init();

#if 1
    USER_PRINTF("LCD init\n");
    LCD_Init(LCD_ScanDir, 800);
#endif

    USER_PRINTF("Init TouchPad...\n");
    TP_Init(LCD_ScanDir);

#if 1
    USER_PRINTF("LCD GUI show\n");
    GUI_Show();
    Driver_Delay_ms(2000);

    USER_PRINTF("Touch Draw Board\n");
    TP_GetAdFac();//Get the default calibration factor
    TP_Dialog();//initialize the drawing board
#endif

    //DEV_TIME sDev_time;
    //sDev_time.Hour = 23;
    //sDev_time.Min = 50;
    //sDev_time.Sec = 56;
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    USER_PRINTF("bef while\n");
    while (1) {
        TP_DrawBoard();

        //sDev_time.Sec++;
        //GUI_Showtime(200, 150, 327, 197, &sDev_time, RED);
        //Driver_Delay_ms(50);//Analog clock 1s
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    /* USER CODE END 3 */

    USER_PRINTF("\nscreen test done\n");
}

#endif /* CFG_TEST_SCREEN */
