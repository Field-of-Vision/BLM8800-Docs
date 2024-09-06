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
#include "flash_api.h"
#include "string.h"
#ifdef CFG_LZMA
#include "Lzma.h"
#endif /* CFG_LZMA */

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


#ifdef CFG_TEST_BOOTLOADER
/*
 * MACROS
 ****************************************************************************************
 */
#define UART_PRINT                  dbg

/*
 * GLOBAL CONSTANTS & VARIABLES
 ****************************************************************************************
 */
typedef struct {
    uint32_t image_info_current_base;
    uint32_t image_body_current_base;
    uint32_t image_header_upgrade_base;
    uint32_t image_body_upgrade_base;
    uint32_t image_header_backup_base;
    uint32_t image_body_backup_base;
    #if defined(CFG_FLASH_FW)
    uint32_t image_info_fmacfw_base;
    uint32_t image_body_fmacfw_base;
    #endif
} image_layout_t;

const image_layout_t g_image_layout = {
    .image_info_current_base    = CURRENT_INFO_ADDR,
    .image_body_current_base    = CURRENT_IMAGE_ADDR,
    .image_header_upgrade_base  = UPGRADE_INFO_ADDR,
    .image_body_upgrade_base    = UPGRADE_IMAGE_ADDR,
    .image_header_backup_base   = BACKUP_INFO_ADDR,
    .image_body_backup_base     = BACKUP_IMAGE_ADDR,
    #if defined(CFG_FLASH_FW)
    .image_info_fmacfw_base     = FMACFW_INFO_ADDR,
    .image_body_fmacfw_base     = FMACFW_IMAGE_ADDR,
    #endif
};

/*
 * FUNCTIONS
 ****************************************************************************************
 */
typedef void (*boot_func_t)(void);

void boot_to(unsigned int addr)
{
    __disable_irq();
    ((boot_func_t)addr)();
}

void * image_info_hdr_get(flash_image_area_e area)
{
    void *ret = NULL;
    if (area == IMAGE_AREA_CURRENT) {
        ret = (void *)g_image_layout.image_info_current_base;
    } else if (area == IMAGE_AREA_UPGRADE) {
        ret = (void *)g_image_layout.image_header_upgrade_base;
    } else if (area == IMAGE_AREA_BACKUP) {
        ret = (void *)g_image_layout.image_header_backup_base;
    }
    #if defined(CFG_FLASH_FW)
    else if (area == IMAGE_AREA_FMACFW) {
        ret = (void *)g_image_layout.image_info_fmacfw_base;
    }
    #endif
    return ret;
}

int image_valid_check(flash_image_area_e area)
{
    int ret = 0;
    if (area < IMAGE_AREA_MAX_CNT) {
        void *info_hdr = image_info_hdr_get(area);
        if (info_hdr) {
            #if !defined(CFG_FLASH_FW)
            if (area == IMAGE_AREA_CURRENT)
            #else
            if (area == IMAGE_AREA_CURRENT || area == IMAGE_AREA_FMACFW)
            #endif
            {
                struct image_info *info = (struct image_info *)info_hdr;
                if (info->magic == IMAGE_INFO_MAGIC) {
                    #if !defined(CFG_FLASH_FW)
                    if (info->addr == g_image_layout.image_body_current_base)
                    #else
                    if (info->addr == g_image_layout.image_body_current_base ||
                        info->addr == g_image_layout.image_body_fmacfw_base )
                    #endif
                    {
                        if (info->size) {
                            uint32_t crc32 = flash_crc32((void *)info->addr, (unsigned int)info->size);
                            if (crc32 != info->crc32) {
                                ret = -6;
                            }
                        } else {
                            ret = -5;
                        }
                    } else {
                        ret = -4;
                    }
                } else {
                    ret = -3;
                }
            } else {
                struct image_header *header = (struct image_header *)info_hdr;
                if (header->magic == IMAGE_HEADER_MAGIC) {
                    uint32_t image_body_base = (area == IMAGE_AREA_UPGRADE) ?
                        g_image_layout.image_body_upgrade_base : g_image_layout.image_body_backup_base;
                    if (header->addr == image_body_base) {
                        if (header->size) {
                            uint32_t crc32 = flash_crc32((void *)header->addr, (unsigned int)header->size);
                            if (crc32 != header->crc32) {
                                ret = -10;
                            }
                        } else {
                            ret = -9;
                        }
                    } else {
                        ret = -8;
                    }
                } else {
                    ret = -7;
                }
            }
        } else {
            ret = -2;
        }
    } else {
        ret = -1;
    }
    return ret;
}

bool image_is_newver(struct image_info *info, struct image_header *header)
{
    bool ret = true;
    if (strcmp((const char *)info->version, (const char *)header->version) == 0) {
        ret = false; // already updated
    }
    return ret;
}

void image_copy(struct image_header *header)
{
    struct image_info info = {0,};
    uint32_t inf_addr, bdy_addr, src_addr, size, cpy_size;
    int ver_len, ret;
    #if !defined(CFG_FLASH_FW)
    inf_addr = g_image_layout.image_info_current_base;
    bdy_addr = g_image_layout.image_body_current_base;
    #else
    if (header->ota_type == OTA_USER_IMAGE) {
        inf_addr = g_image_layout.image_info_current_base;
        bdy_addr = g_image_layout.image_body_current_base;
    } else if(header->ota_type == OTA_WIFI_IMAGE) {
        inf_addr = g_image_layout.image_info_fmacfw_base;
        bdy_addr = g_image_layout.image_body_fmacfw_base;
    } else {
        UART_PRINT("OTA_TYPE err\n");
        return ;
    }
    #endif
    src_addr = header->addr;
    size = header->size;
#ifdef CFG_LZMA
    if (header->encrypt_algo == 0) {
#endif /*CFG_LZMA*/
        cpy_size = (header->size & 0xFFF) ? ((header->size + 0xFFF) & ~0xFFF) : header->size;
        // copy image body
        flash_erase((void *)bdy_addr, cpy_size);
        flash_write((void *)bdy_addr, cpy_size, (void *)src_addr);
        flash_cache_invalid_range((void *)bdy_addr, cpy_size);
        // fill image info
        info.magic   = IMAGE_INFO_MAGIC;
        info.addr    = bdy_addr;
        info.size    = size;
        info.crc32   = flash_crc32((void *)bdy_addr, size);
        ver_len = strlen((const char *)header->version) + 1;
        memcpy(info.version, header->version, (ver_len < VER_BYTE_CNT) ? ver_len : VER_BYTE_CNT);
        ret = flash_erase((void *)inf_addr, IMAGE_INFO_SIZE);
        if (ret)
            dbg("Err: erase header %d\r\n", ret);
        ret = flash_write((void *)inf_addr, sizeof(struct image_info), (void *)(&info));
        if (ret)
            dbg("Err: write header %d\r\n", ret);
        flash_cache_invalid_range((void *)inf_addr, sizeof(struct image_info));
#ifdef CFG_LZMA
    } else if (header->encrypt_algo == 1) {//lzma
        cpy_size = (header->real_size & 0xFFF) ? ((header->real_size + 0xFFF) & ~0xFFF) : header->real_size;

        if (0 == (flash_erase((void *)bdy_addr, cpy_size))) {
            if (0 == (lzma_upgrade((uint32_t)g_image_layout.image_body_upgrade_base, (uint32_t)header->size,
                                    (uint32_t)bdy_addr, (uint32_t)header->real_size))) {
                /*verify crc*/
                uint32_t crc32 = flash_crc32((void *)(bdy_addr), header->real_size);
                uint8_t  status = (crc32 == header->real_crc32)? 0 : 1;
                if(status != 0) {
                    UART_PRINT("upgrade flash operation failed in copy upgrade firmware\r\n");
                } else {
                    UART_PRINT("upgrade complete\r\n");
                }
            }
        }
        flash_cache_invalid_range((void *)bdy_addr, cpy_size);
        // fill image info
        info.magic   = IMAGE_INFO_MAGIC;
        info.addr    = bdy_addr;
        info.size    = header->real_size;
        info.crc32   = flash_crc32((void *)bdy_addr, header->real_size);
        ver_len = strlen((const char *)header->version) + 1;
        memcpy(info.version, header->version, (ver_len < VER_BYTE_CNT) ? ver_len : VER_BYTE_CNT);
        ret = flash_erase((void *)inf_addr, IMAGE_INFO_SIZE);
        if (ret)
            dbg("LErr: erase header %d\r\n", ret);
        ret = flash_write((void *)inf_addr, sizeof(struct image_info), (void *)(&info));
        if (ret)
            dbg("LErr: write header %d\r\n", ret);
        flash_cache_invalid_range((void *)inf_addr, sizeof(struct image_info));
    } else {
        UART_PRINT("unsupport encrypt algo:%d\n", header->encrypt_algo);
    }
#endif /*CFG_LZMA*/
}

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void bootloader_test(void)
{
    #if !defined(CFG_FLASH_FW)
    int res[IMAGE_AREA_MAX_CNT] = {0xFF, 0xFF, 0xFF};
    unsigned int image_body_base = 0;
    UART_PRINT("\nBootloader test start\n");

    res[IMAGE_AREA_CURRENT] = image_valid_check(IMAGE_AREA_CURRENT);
    res[IMAGE_AREA_UPGRADE] = image_valid_check(IMAGE_AREA_UPGRADE);
    if (0 == res[IMAGE_AREA_CURRENT]) {
        struct image_info *info = image_info_hdr_get(IMAGE_AREA_CURRENT);
        struct image_header *header = image_info_hdr_get(IMAGE_AREA_UPGRADE);
        if ((0 == res[IMAGE_AREA_UPGRADE]) && (image_is_newver(info, header))) {
            UART_PRINT("update img ver: %s -> %s\n", info->version, header->version);
            image_copy(header);
        } else {
            image_body_base = info->addr;
        }
    } else if (0 == res[IMAGE_AREA_UPGRADE]) {
        struct image_header *header = image_info_hdr_get(IMAGE_AREA_UPGRADE);
        image_copy(header);
        UART_PRINT("cur invalid, use upg: %s\n", header->version);
    } else {
        res[IMAGE_AREA_BACKUP] = image_valid_check(IMAGE_AREA_BACKUP);
        if (0 == res[IMAGE_AREA_BACKUP]) {
            struct image_header *header = image_info_hdr_get(IMAGE_AREA_BACKUP);
            image_copy(header);
            UART_PRINT("cur/upg invalid, use bak: %s\n", header->version);
        }
    }
    if ((0 == image_body_base) && (0 == image_valid_check(IMAGE_AREA_CURRENT))) {
        struct image_info *info = image_info_hdr_get(IMAGE_AREA_CURRENT);
        image_body_base = info->addr;
    }
    if (image_body_base) {
        uint32_t boot_stack = *(uint32_t *)image_body_base;
        uint32_t boot_addr = *(uint32_t *)(image_body_base + 4);
        UART_PRINT("base=%x,stack=%x,addr=%x\n", image_body_base, boot_stack, boot_addr);
        __set_MSP(boot_stack);
        boot_to(boot_addr);
    } else {
        UART_PRINT("bootloader corrupt, res:%d(%d),%d,%d\n",res[IMAGE_AREA_CURRENT],image_valid_check(IMAGE_AREA_CURRENT),
            res[IMAGE_AREA_UPGRADE], res[IMAGE_AREA_BACKUP]);
    }

    #else /* CFG_FLASH_FW */
    int res[IMAGE_AREA_MAX_CNT] = {0xFF, 0xFF, 0xFF, 0xFF};
    unsigned int image_body_base = 0;
    UART_PRINT("\nBootloader test start\n");

    res[IMAGE_AREA_CURRENT] = image_valid_check(IMAGE_AREA_CURRENT);
    res[IMAGE_AREA_UPGRADE] = image_valid_check(IMAGE_AREA_UPGRADE);
    res[IMAGE_AREA_FMACFW]  = image_valid_check(IMAGE_AREA_FMACFW);
    struct image_header *header_type = image_info_hdr_get(IMAGE_AREA_UPGRADE);
    if (header_type->ota_type == OTA_USER_IMAGE) {
        if (0 == res[IMAGE_AREA_CURRENT]) {
            struct image_info *info = image_info_hdr_get(IMAGE_AREA_CURRENT);
            struct image_header *header = image_info_hdr_get(IMAGE_AREA_UPGRADE);
            if ((0 == res[IMAGE_AREA_UPGRADE]) && (image_is_newver(info, header))) {
                UART_PRINT("update img ver: %s -> %s\n", info->version, header->version);
                image_copy(header);
            } else {
                image_body_base = info->addr;
            }
        } else if (0 == res[IMAGE_AREA_UPGRADE]) {
            struct image_header *header = image_info_hdr_get(IMAGE_AREA_UPGRADE);
            image_copy(header);
            UART_PRINT("cur invalid, use upg: %s\n", header->version);
        } else {
            res[IMAGE_AREA_BACKUP] = image_valid_check(IMAGE_AREA_BACKUP);
            if (0 == res[IMAGE_AREA_BACKUP]) {
                struct image_header *header = image_info_hdr_get(IMAGE_AREA_BACKUP);
                image_copy(header);
                UART_PRINT("cur/upg invalid, use bak: %s\n", header->version);
            }
        }
    }else if (header_type->ota_type == OTA_WIFI_IMAGE) {

        if (0 == res[IMAGE_AREA_FMACFW]) {
            struct image_info *info = image_info_hdr_get(IMAGE_AREA_FMACFW);
            struct image_header *header_upg = image_info_hdr_get(IMAGE_AREA_UPGRADE);
            if ((0 == res[IMAGE_AREA_UPGRADE]) && (image_is_newver(info, header_upg))) {
                UART_PRINT("update fw-ver: %s -> %s\n", info->version, header_upg->version);
                image_copy(header_upg);
            }
        } else if (0 == res[IMAGE_AREA_UPGRADE]) {
            struct image_header *header_upg = image_info_hdr_get(IMAGE_AREA_UPGRADE);
            image_copy(header_upg);
            UART_PRINT("cur-fw invalid, use upg: %s\n", header_upg->version);
        } else {
            //
        }
    } else {
        UART_PRINT("OTA_TYPE_MAX\n");
    }

    // Prepare to restart.
    if ((0 == image_body_base) && (0 == image_valid_check(IMAGE_AREA_CURRENT))) {
        struct image_info *info = image_info_hdr_get(IMAGE_AREA_CURRENT);
        image_body_base = info->addr;
    }
    if (image_body_base) {
        uint32_t boot_stack = *(uint32_t *)image_body_base;
        uint32_t boot_addr = *(uint32_t *)(image_body_base + 4);
        UART_PRINT("base=%x,stack=%x,addr=%x\n", image_body_base, boot_stack, boot_addr);
        __set_MSP(boot_stack);
        boot_to(boot_addr);
    } else {
        UART_PRINT("bootloader corrupt, res:%d(%d),%d,%d,%d\n",
            res[IMAGE_AREA_CURRENT],image_valid_check(IMAGE_AREA_CURRENT),
            res[IMAGE_AREA_UPGRADE], res[IMAGE_AREA_BACKUP], res[IMAGE_AREA_FMACFW]);
    }
    #endif /* CFG_FLASH_FW */

    UART_PRINT("\nBootloader test done\n");
}

#endif /* CFG_TEST_BOOTLOADER */
