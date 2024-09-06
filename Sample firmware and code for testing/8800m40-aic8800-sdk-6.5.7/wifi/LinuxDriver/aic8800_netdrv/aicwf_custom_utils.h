/**
 * aicwf_custom_utils.c
 *
 * host-ota function declarations
 *
 * Copyright (C) AICSemi 2018-2022
 */


#ifndef _AICWF_CUSTOM_UTILS_H_
#define _AICWF_CUSTOM_UTILS_H_

#include "rwnx_main.h"


#define MCU_OTA_TIMEOUT         2000
#define IMAGE_INFO_SIZE         0x1000

enum OTA_STEP
{
    OTA_STEP_FLASH_ERASE,
    OTA_STEP_FR_PKG_WRITE,
    OTA_STEP_LT_PKG_WRITE,
    OTA_STEP_HEADER_WRITE,
    OTA_STEP_LZMA_CHECK,
};

enum OTA_STEP_STATUS
{
    OTA_STEP_FLASH_ERASE_OK,
    OTA_STEP_FLASH_ERASE_ERR,
    OTA_STEP_FR_PKG_WRITE_OK,
    OTA_STEP_FR_PKG_WRITE_ERR,
    OTA_STEP_LT_PKG_WRITE_OK,
    OTA_STEP_LT_PKG_WRITE_ERR,
    OTA_STEP_BIN_FILE_CRC_ERR,
    OTA_STEP_BIN_VERSION_ERR,
    OTA_STEP_HEADER_WRITE_OK,
    OTA_STEP_HEADER_WRITE_ERR,
    OTA_STEP_LZMA_CRC_CHECK_OK,
    OTA_STEP_LZMA_CRC_CHECK_ERR,
};

void dump_c(u8 *data, u32_l len);
int host_ota_test(const char * file_path);
void aicwf_mcu_ota_confirm_ready(void);

#endif

