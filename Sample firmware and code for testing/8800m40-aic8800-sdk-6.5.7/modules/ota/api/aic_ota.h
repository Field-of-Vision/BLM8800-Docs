#ifndef __AIC_OTA_H__
#define __AIC_OTA_H__

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

#define OTA_ADDR          UPGRADE_START_ADDR
#define OTA_INFO_SIZE     IMAGE_INFO_SIZE
#define OTA_INFO_ADDR     CURRENT_INFO_ADDR
#define OTA_IMG_ADDR      CURRENT_IMAGE_ADDR

#define OTA_CURRENT_VER   "v0.1.0"
#define OTA_NEW_VER       "v0.1.1"

#define OTA_A_VER         "v0.0.0"
#define OTA_B_VER         "v1.1.1"

uint32_t aic_crc32(const uint8_t *p, size_t len, uint32_t crc);
int ota_start(uint32_t addr, uint32_t img_len);
int ota_write( const uint8_t *buf, uint32_t len);
int ota_end(void);
#if defined(CFG_FLASH_FW)  // If use flash fw, need to use this function.
int ota_type_end(ota_image_t type);
#endif /* CFG_FLASH_FW */

#endif /* __AIC_OTA_H__ */
