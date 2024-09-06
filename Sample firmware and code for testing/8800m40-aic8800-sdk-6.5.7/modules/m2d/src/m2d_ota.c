#include "plf.h"
#if PLF_M2D_OTA
#include <string.h>
#include "aic_ota.h"
#include "dbg.h"
#include "flash_api.h"


#define M2D_OTA_ALIGNED_LEN          0x100
#define M2D_OTA_INFO_ADDR            0x88000020//used for check ota process.
#define M2D_OTA_DATA_ADDR            0x88000040//used for check ota process.


static uint8_t m2d_ota_going = 0;
static unsigned int m2d_ota_len = 0;
static unsigned int m2d_ota_total_len = 0;

void m2d_ota_info_handle(unsigned int len, uint8_t *buf)
{
    if(len == 4){
        uint32_t ota_addr;
        m2d_ota_going = 1;
        m2d_ota_total_len = (unsigned int)(buf[0]) | ((unsigned int)(buf[1])<<8)
                             | ((unsigned int)(buf[2])<<16) | ((unsigned int)(buf[3])<<24);
        TRACE("%s,total len =  %d\n",__func__,m2d_ota_total_len);
        #ifndef CFG_LZMA_APP
        ota_addr = OTA_ADDR + OTA_INFO_SIZE;
        #else
        ota_addr = OTA_ADDR;
        #endif
        ota_start(ota_addr, m2d_ota_total_len);
    }else{
        TRACE("%s len error\n",__func__);
    }
}

int m2d_ota_data_handle(unsigned int len, uint8_t *buf)
{
    int ret = 0;
    unsigned int i = 0;
    if(m2d_ota_going){
        if(len > M2D_OTA_ALIGNED_LEN){
            for(i = 0; i < (len-M2D_OTA_ALIGNED_LEN); i += M2D_OTA_ALIGNED_LEN){
                ret = ota_write((const uint8_t *)(buf+i), M2D_OTA_ALIGNED_LEN);
            }
        }
        if(!ret && i < len){
            ret = ota_write((const uint8_t *)(buf+i), len-i);
        }

        m2d_ota_len+=len;
        if(m2d_ota_len == m2d_ota_total_len){
            TRACE("%s, ota received success\n",__func__);
            m2d_ota_going = 0;
            m2d_ota_total_len = 0;
            m2d_ota_len = 0;
            ota_end();
        }
    }
    return ret;
}

int m2d_ota_addr_check(unsigned int addr,unsigned int len, void *buf)
{
    int ret = 0;
    switch(addr )
    {
        case M2D_OTA_INFO_ADDR:
            ret = 1;
            m2d_ota_info_handle(len,(uint8_t *)buf);
            break;
        case M2D_OTA_DATA_ADDR:
            ret = 1;
            m2d_ota_data_handle(len,(uint8_t *)buf);
            break;
        default:
            break;
    }
    return ret;
}

extern uint32_t __image_end__[];

int m2d_ota_updata_img_info(void)
{
    int ret = 0;
    // Save current img info for bootloader
    struct image_info info;
    info.magic   = IMAGE_INFO_MAGIC;
    info.size    = (uint32_t)__image_end__ - OTA_IMG_ADDR;
    info.addr    = OTA_IMG_ADDR;
    info.crc32   = flash_crc32((void *)OTA_IMG_ADDR, info.size);
    memcpy(info.version, OTA_CURRENT_VER, sizeof(OTA_CURRENT_VER));
    //dbg("Image_Info %x end %x size %d crc %x\r\n", img_info->magic, img_info->img_end, info.size, info.crc32);
    ret = flash_erase((void *)OTA_INFO_ADDR, OTA_INFO_SIZE);
    if (ret) {
        dbg("erase fail %d\r\n",ret);
    }

    ret = flash_write((void *)OTA_INFO_ADDR, OTA_INFO_SIZE, (char *)(&info));
    if (ret) {
        dbg("write fail %d\r\n",ret);
    }
    flash_cache_invalid_range((void *)OTA_INFO_ADDR, OTA_INFO_SIZE);
    return 0;
}

#endif
