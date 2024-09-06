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
#ifndef _SPI_API_H_
#define _SPI_API_H_

/**
 * Includes
 */
#include <stdbool.h>
#include "chip.h"
#include "reg_spi.h"

/**
 * Macros
 */

/**
 * TypeDefs
 */
typedef enum {
    SPI_CS0 = 0, // hw default csn pin
    SPI_CS1,     // user defined gpioa
    SPI_CSN_MAX
} SPI_CSN_T;

typedef enum {
    SPI_DC_NONE = 0,
    SPI_DC_DATA,
    SPI_DC_CMD,
    SPI_DC_MAX
} SPI_DC_T;

typedef enum {
    SPI_MODE_GENERIC      = 0,
    SPI_MODE_LCD_3W_DIO   = 1,
    SPI_MODE_LCD_3W_DI_DO = 2,
    SPI_MODE_LCD_4W_DIO   = 3,
    SPI_MODE_LCD_4W_DI_DO = 4,
    SPI_MODE_MAX
} SPI_MODE_T;

typedef struct {
    SPI_CSN_T cs;
    SPI_DC_T dc;
    SPI_MODE_T spi_mode;
    uint32_t clk_freq;
    uint16_t clk_mode;
    uint8_t bit_cnt;
    uint8_t gpa_idx_cs;
} spim_cfg_t;

/**
 * Functions
 */

/**
 * @brief: Initialize SPI master
 */
void spim_init(spim_cfg_t *spim);

/**
 * @brief: SPI master write byte value
 */
void spim_write_byte(spim_cfg_t *spim, uint8_t byte_val, bool cs_end);

/**
 * @brief: SPI master read byte value
 * @return: Pwrkey enable or not
 */
uint8_t spim_read_byte(spim_cfg_t *spim, bool cs_end);

#endif /* _SPI_API_H_ */
