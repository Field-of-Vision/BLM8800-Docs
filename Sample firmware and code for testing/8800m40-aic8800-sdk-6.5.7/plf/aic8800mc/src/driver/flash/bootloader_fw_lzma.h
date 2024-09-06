#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_
#include "plf.h"
#include "chip.h"

/*
 *******************************************************************************
 * This bootloader version can support compressing upgrade image. Upgrade both
 * user-image and wifi-fw.
 * Note the following rules:
 * 1. Area about bootloader is fixed, including address and capacity;
 * 2. Area about image_info is fixed, including address and capacity;
 * 3. The capacity of area about image_header is fixed at 4KB, its address
 *    is adjusted depend on xxx_image;
 * 4. Area about cur_image, upg_image and bak_image is adjusted on demand,
 *    including address and capacity;
 * 5. Area about bak_image and its header can be delete on demand;
 * 6. Area about user_data is adjusted on demand;
 * 7. Area about fw_header and wifi_fw is fixed, including address and capacity.
 *******************************************************************************
 */

/**
 * Memory map with bootloader:
 * +--------------+  <--------------- 0x08000000
 * |              |     ^
 * | bootloader   |     |  20KB
 * |              |     v
 * +--------------+  <--------------- 0x08005000
 * |              |     ^
 * | image_info   |     |  4KB
 * |              |     v
 * +--------------+  <--------------- 0x08006000
 * |              |     ^
 * | cur_image    |     |  712KB : current image
 * |              |     v
 * +--------------+  <--------------- 0x080B8000
 * |              |     ^
 * | image_header |     |  4KB
 * |              |     v
 * +--------------+  <--------------- 0x080B9000
 * |              |     ^
 * | bak_image    |     |  500KB : backup image
 * |              |     v
 * +--------------+  <--------------- 0x08136000
 * |              |     ^
 * | image_header |     |  4KB
 * |              |     v
 * +--------------+  <--------------- 0x08137000
 * |              |     ^
 * | upg_image    |     |  500KB : upgrade image
 * |              |     v
 * +--------------+  <--------------- 0x081B4000
 * |              |     ^
 * | user_data    |     |  28KB : user specified
 * |              |     v
 * +--------------+  <--------------- 0x081BB000
 * |              |     ^
 * | fw_header    |     |  4KB
 * |              |     v
 * +--------------+  <--------------- 0x081BC000
 * |              |     ^
 * | wifi_fw      |     |  256KB : fmacfw image
 * |              |     v
 * +--------------+  <--------------- 0x081FC000
 * |              |     ^
 * | bt_ble_info  |     |  4KB
 * |              |     v
 * +--------------+  <--------------- 0x081FD000
 * |              |     ^
 * | wifi_info    |     |  4KB
 * |              |     v
 * +--------------+  <--------------- 0x081FE000
 * |              |     ^
 * | calib_info   |     |  4KB : factory calib(RO)
 * |              |     v
 * +--------------+  <--------------- 0x081FF000
 * |              |     ^
 * | boot_info    |     |  4KB : chip reserved(RO)
 * |              |     v
 * +--------------+  <--------------- 0x08200000
 */

#define IMAGE_INFO_SIZE             0x1000

#define CURRENT_START_ADDR          0x08005000
#define CURRENT_INFO_ADDR           (CURRENT_START_ADDR)
#define CURRENT_IMAGE_ADDR          (CURRENT_START_ADDR + IMAGE_INFO_SIZE)

#define UPGRADE_START_ADDR          0x08136000
#define UPGRADE_INFO_ADDR           (UPGRADE_START_ADDR)
#define UPGRADE_IMAGE_ADDR          (UPGRADE_START_ADDR + IMAGE_INFO_SIZE)

#define BACKUP_START_ADDR           0x080B8000
#define BACKUP_INFO_ADDR            (BACKUP_START_ADDR)
#define BACKUP_IMAGE_ADDR           (BACKUP_START_ADDR + IMAGE_INFO_SIZE)

#define FMACFW_START_ADDR           0x081BB000
#define FMACFW_INFO_ADDR            (FMACFW_START_ADDR)
#define FMACFW_IMAGE_ADDR           (FMACFW_START_ADDR + IMAGE_INFO_SIZE)

#define USERDATA_START_ADDR         0x081B4000

#define CURRENT_IMAGE_MAX_SIZE      (BACKUP_START_ADDR - CURRENT_IMAGE_ADDR)
#define BACKUP_IMAGE_MAX_SIZE       (UPGRADE_START_ADDR - BACKUP_IMAGE_ADDR)
#define UPGRADE_IMAGE_MAX_SIZE      (USERDATA_START_ADDR - UPGRADE_IMAGE_ADDR)

#define IMAGE_INFO_MAGIC            0x49474D49  // "IMGI"
#define IMAGE_HEADER_MAGIC          0x48474D49  // "IMGH"
#define VER_BYTE_CNT                16

#define FLASH_IMAGE_MAGIC_NUM       0x474D4946  /* "FIMG" */
#define FLASH_IMAGE_INFO_OFFSET     ((NVIC_USER_IRQ_OFFSET + NVIC_USER_IRQ_NUMBER) * 4)

typedef enum {
    IMAGE_AREA_CURRENT = 0,
    IMAGE_AREA_UPGRADE = 1,
    IMAGE_AREA_BACKUP  = 2,
    IMAGE_AREA_FMACFW  = 3,
    IMAGE_AREA_MAX_CNT
} flash_image_area_e;

typedef struct {
    unsigned int magic_num;
    unsigned int image_end;
    unsigned int reserved0;
    unsigned int reserved1;
} flash_image_info_t;

typedef enum {
    OTA_USER_IMAGE,
    OTA_WIFI_IMAGE,
    OTA_TYPE_MAX,
} ota_image_t;

struct image_info
{
    uint32_t magic;
    uint32_t addr;
    uint32_t size;
    uint32_t crc32;
    uint8_t  version[VER_BYTE_CNT];
    uint32_t bootaddr;
    uint32_t bootmagic;
};

struct image_header {
    uint32_t magic;
    uint32_t addr;
    uint32_t size;
    uint32_t crc32;
    uint8_t  version[VER_BYTE_CNT];
    uint32_t ota_type;
    uint32_t encrypt_algo;
    uint32_t real_crc32;
    uint32_t real_size;
};

#endif /* _BOOTLOADER_H_ */
