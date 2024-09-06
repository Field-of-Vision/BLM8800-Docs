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
#ifndef _EPAPER_DRIVER_H_
#define _EPAPER_DRIVER_H_

/**
 * Includes
 */

/**
 * TypeDefs
 */

typedef enum {
    SPI_DC_NONE = 0,
    SPI_DC_DATA,
    SPI_DC_CMD,
    SPI_DC_MAX
} SPI_DC_T;

/**
 * Functions
 */

void EPD_WhiteScreen_ALL_Fast(const unsigned char *datas);
void EPD_HW_Init(void);
void EPD_HW_Init_Fast(void);
void EPD_Sleep(void);
void EPD_SetRAMValue_BaseMap( const unsigned char * datas);
void EPD_WhiteScreen_White(void);
void EPD_Dis_Part_myself(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
                         unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
                         unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
                         unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
                         unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
                         unsigned int PART_COLUMN,unsigned int PART_LINE);

#endif
