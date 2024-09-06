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
#include "sysctrl_api.h"

/**
 * Macros
 */
#define FLASH_CDIV_SDLY(div,dly)    (((div) << 8) | ((dly) << 4))
#define FLASH_DIV_DLY(pdiv,div,dly) (((pdiv) << 12) | FLASH_CDIV_SDLY(div,dly))

#define CLK_CFG_CODE(dd,ds,dp,df)   (((dd)<<24)|((ds)<<20)|((dp)<<16)|(df))

/**
 * TypeDefs
 */

/**
 * Variables
 */
const unsigned int clk_cfg_code_tbl[CLK_CFG_MAX] = {
    // cpusys hclk: 240MHz
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,2,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S240P120PS240F120
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_1  ,3,2)|PSRAM_SEL_CLK320M_BIT|PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S240P120PS320F106
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2P5,2,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S240P120PS192F96
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_1  ,4,2)|PSRAM_SEL_CLK320M_BIT|PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S240P120PS320F80
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S240P120PS240F60
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2P5,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S240P120PS192F48
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,6,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S240P120PS240F40
    // cpusys hclk: 192MHz
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|               CLK_DIV_VALUE_2P5),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,2,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S192P96PS240F120
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|               CLK_DIV_VALUE_2P5),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_1  ,3,2)|PSRAM_SEL_CLK320M_BIT|PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S192P96PS320F106
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|               CLK_DIV_VALUE_2P5),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2P5,2,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S192P96PS192F96
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|               CLK_DIV_VALUE_2P5),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_1  ,4,2)|PSRAM_SEL_CLK320M_BIT|PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S192P96PS320F80
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|               CLK_DIV_VALUE_2P5),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S192P96PS240F60
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|               CLK_DIV_VALUE_2P5),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2P5,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S192P96PS192F48
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|               CLK_DIV_VALUE_2P5),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,6,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S192P96PS240F40
    // cpusys hclk: 160MHz
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|CLK_CFG_320M_BIT|CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,2,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S160P80PS240F120
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|CLK_CFG_320M_BIT|CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_1  ,3,2)|PSRAM_SEL_CLK320M_BIT|PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S160P80PS320F106
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|CLK_CFG_320M_BIT|CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2P5,2,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S160P80PS192F96
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|CLK_CFG_320M_BIT|CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_1  ,4,2)|PSRAM_SEL_CLK320M_BIT|PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S160P80PS320F80
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|CLK_CFG_320M_BIT|CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S160P80PS240F60
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|CLK_CFG_320M_BIT|CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2P5,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S160P80PS192F48
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|CLK_CFG_320M_BIT|CLK_DIV_VALUE_2),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,6,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S160P80PS240F40
    // cpusys hclk: 120MHz
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_4),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,2,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S120P60PS240F120
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_4),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_1  ,3,2)|PSRAM_SEL_CLK320M_BIT|PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S120P60PS320F106
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_4),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2P5,2,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S120P60PS192F96
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_4),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_1  ,4,2)|PSRAM_SEL_CLK320M_BIT|PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S120P60PS320F80
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_4),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S120P60PS240F60
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_4),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2P5,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S120P60PS192F48
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_4),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,6,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S120P60PS240F40
    // cpusys hclk: 80MHz
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_6),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_1  ,4,2)|PSRAM_SEL_CLK320M_BIT|PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S80P40PS320F80
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_6),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S80P40PS240F60
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_6),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2P5,4,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S80P40PS192F48
    CLK_CFG_CODE((CLK_CFG_FAST_BIT|                 CLK_DIV_VALUE_6),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,6,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S80P40PS240F40
    // cpusys hclk: 52MHz
    CLK_CFG_CODE((                                  CLK_DIV_VALUE_1),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,6,2)|                      PSRAM_SEL_CLKFAST_BIT|FLASH_SEL_PSRCLK_BIT)), //CLK_CFG_S52P26PS240F40
    CLK_CFG_CODE((                                  CLK_DIV_VALUE_1),1,2,(FLASH_DIV_DLY(CLK_DIV_VALUE_2  ,2,1)                                                                 )), //CLK_CFG_S52P26PS240F26
};

/**
 * Functions
 */
