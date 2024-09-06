/*
 * Copyright (C) 2018-2021 AICSemi Ltd.
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

#include "dbg.h"
#include "rtos_al.h"
#include "flash_api.h"
#include "xyzModem.h"
#include "string.h"
#include "uart1_api.h"
#include "console.h"

#if !defined(CFG_BOOT_AGO)
#if defined(CFG_FLASH_FW) && (defined(CFG_LZMA) || defined(CFG_LZMA_APP))
#include "bootloader_fw_lzma.h"
#elif defined(CFG_FLASH_FW) && (!defined(CFG_LZMA) && !defined(CFG_LZMA_APP))
#include "bootloader_fw.h"
#elif !defined(CFG_FLASH_FW) && (defined(CFG_LZMA) || defined(CFG_LZMA_APP))
#include "bootloader_lzma.h"
#else
#include "bootloader.h"
#endif
#else
#include "bootloader_ago.h"
#endif


#ifdef CFG_TEST_UPGRADE
/*
 * MACROS
 ****************************************************************************************
 */
#define UART_PRINT                  dbg

#define CURRENT_VER                 "v0.1.0"
#define UPGRADE_VER                 "v0.1.1"

/*
 * GLOBAL CONSTANTS & VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTIONS
 ****************************************************************************************
 */

static int do_write_image_info(int argc, char * const argv[])
{
    struct image_info img_info = {0,};
    char *ver_str;
    int ver_len;
    unsigned int addr, size;

    if (argc < 3) {
        return -1;
    }

    ver_str = argv[1];
    addr = console_cmd_strtoul(argv[2], NULL, 16);
    if (!IS_FLASH_MEM_VALID(addr)) {
        return -2;
    }
    if (argc > 3) {
        size = console_cmd_strtoul(argv[3], NULL, 16);
    } else {
        flash_image_info_t *info = (flash_image_info_t *)(addr + FLASH_IMAGE_INFO_OFFSET);
        if (info->magic_num != FLASH_IMAGE_MAGIC_NUM) {
            return -3;
        }
        size = info->image_end - CURRENT_IMAGE_ADDR;
    }
    if (!size) {
        return -4;
    }

    img_info.magic   = IMAGE_INFO_MAGIC;
    img_info.addr    = addr;
    img_info.size    = size;
    img_info.crc32   = flash_crc32((void *)addr, size);
    ver_len = strlen(ver_str) + 1;
    memcpy(img_info.version, ver_str, (ver_len < VER_BYTE_CNT) ? ver_len : VER_BYTE_CNT);
    flash_erase((void *)(addr - IMAGE_INFO_SIZE), IMAGE_INFO_SIZE);
    flash_write((void *)(addr - IMAGE_INFO_SIZE), sizeof(struct image_info), (char *)(&img_info));
    flash_cache_invalid_range((void *)(addr - IMAGE_INFO_SIZE), sizeof(struct image_info));
    return 0;
}

static int do_write_image_header(int argc, char * const argv[])
{
    struct image_header img_hdr = {0,};
    char *ver_str;
    int ver_len;
    unsigned int addr, size;

    if (argc < 3) {
        return -1;
    }

    ver_str = argv[1];
    addr = console_cmd_strtoul(argv[2], NULL, 16);
    if (!IS_FLASH_MEM_VALID(addr)) {
        return -2;
    }
    if (argc > 3) {
        size = console_cmd_strtoul(argv[3], NULL, 16);
    } else {
        flash_image_info_t *info = (flash_image_info_t *)(addr + FLASH_IMAGE_INFO_OFFSET);
        if (info->magic_num != FLASH_IMAGE_MAGIC_NUM) {
            return -3;
        }
        size = info->image_end - CURRENT_IMAGE_ADDR;
    }
    if (!size) {
        return -4;
    }

    img_hdr.magic   = IMAGE_HEADER_MAGIC;
    img_hdr.addr    = addr;
    img_hdr.size    = size;
    img_hdr.crc32   = flash_crc32((void *)addr, size);
    ver_len = strlen(ver_str) + 1;
    memcpy(img_hdr.version, ver_str, (ver_len < VER_BYTE_CNT) ? ver_len : VER_BYTE_CNT);
    flash_erase((void *)(addr - IMAGE_INFO_SIZE), IMAGE_INFO_SIZE);
    flash_write((void *)(addr - IMAGE_INFO_SIZE), sizeof(struct image_header), (char *)(&img_hdr));
    flash_cache_invalid_range((void *)(addr - IMAGE_INFO_SIZE), sizeof(struct image_header));
    return 0;
}

static int do_write_image_body(int argc, char * const argv[])
{
    int err, res;
    uint32_t base_addr, store_addr;
    uint32_t erase_sz = 0x10000UL; // default 64KB
    connection_info_t info;
    char modemBuf[1024];
    uint32_t offset = 0;

    if (argc < 2) {
        return -1;
    }

    base_addr = console_cmd_strtoul(argv[1], NULL, 16);
    if (!IS_FLASH_MEM_VALID(base_addr)) {
        return -2;
    }
    if (argc > 2) {
        erase_sz = console_cmd_strtoul(argv[2], NULL, 16);
    } else {
        flash_image_info_t *info = (flash_image_info_t *)(base_addr + FLASH_IMAGE_INFO_OFFSET);
        if (info->magic_num != FLASH_IMAGE_MAGIC_NUM) {
            return -3;
        }
        erase_sz = info->image_end - CURRENT_IMAGE_ADDR;
    }
    if (!erase_sz) {
        return -4;
    }

    UART_PRINT("Write img to 0x%08x, size:%08x\r\n", base_addr, erase_sz);

    err = flash_erase((void *)base_addr, erase_sz);
    if (err < 0) {
        UART_PRINT("erase err: %d\r\n", err);
        return -3;
    } else if (err == 1) {
        UART_PRINT("warn: not 4KB aligned erase_sz\r\n");
    }

    info.mode = xyzModem_xmodem;
    info.ops.putc = uart1_putc;
    info.ops.getc = uart1_getc;
    info.ops.tstc = uart1_tstc;

    critical_section_start();

    res = xyzModem_stream_open(&info, &err);
    if (!res)
    {
        while ((res = xyzModem_stream_read(modemBuf, 1024, &err)) > 0)
        {
            store_addr = offset + base_addr;
            offset += res;
            flash_write((void *)store_addr, res, (void *)modemBuf);
        }
    }
    else
    {
        UART_PRINT ("%s\r\n", xyzModem_error (err));
    }

    flash_cache_invalid_range((void *)base_addr, offset);
    xyzModem_stream_terminate(false);
    xyzModem_stream_close(&err);

    critical_section_end();

    UART_PRINT("%d (0x%08X) bytes received\r\n", offset, offset);
    return 0;
}

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void upgrade_test(void)
{
    UART_PRINT("\nUpgrade test start\n");

    uart1_init();

    console_cmd_add("wii", "  wr img info",     3, 4, do_write_image_info);
    console_cmd_add("wih", "  wr img header",   3, 4, do_write_image_header);
    console_cmd_add("wib", "  wr img body",     2, 3, do_write_image_body);

    UART_PRINT("\nUpgrade test done\n");
}


#endif /* CFG_TEST_UPGRADE */
