/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "sdmmc_api.h"
#include "usbh_diskio.h"
#include "time_api.h"
#include "dbg.h"
//#include <time.h>
#ifdef CFG_FLASH_FAT
#include "flash_api.h"
#endif

#ifdef CFG_FLASH_FAT
#define FLASH_BASE_ADDR				0x08000000
#define FLASH_START_OFFSET			0x20000 //128k for bin file
#define FLASH_INFO_SIZE				0X4000 //last 16k for factory info
#endif

/* Definitions of physical drive number for each drive */
#define DEV_MMC		0	/* Example: Map MMC/SD card to physical drive 0 */
#define DEV_USB		1	/* Example: Map USB MSD to physical drive 1 */
#ifdef CFG_FLASH_FAT
#define DEV_FLASH	2	/* Example: Map flash to physical drive 2 */
#define DEV_RAM		3	/* Example: Map Ramdisk to physical drive 3 */
#else
#define DEV_RAM		2	/* Example: Map Ramdisk to physical drive 2 */
#endif

#ifdef CFG_FLASH_FAT
static int is_dev_inited[4] = {0,0,0,0};
#else
static int is_dev_inited[3] = {0,0,0};
#endif

DWORD get_fattime(void)
{
    DWORD sec, usec;
    //struct tm *ptm;
    aic_time_get(SINCE_EPOCH, &sec, &usec);
    //dbg("t:%d\n",sec);
    /* ptm = localtime(&sec);
    return (DWORD)(ptm->tm_year - 80) << 25
           | (DWORD)(ptm->tm_mon + 1) << 21
           | (DWORD)(ptm->tm_mday) << 16
           | (DWORD)(ptm->tm_hour) << 11
           | (DWORD)(ptm->tm_min) << 5
           | (DWORD)(ptm->tm_sec / 2); */
    return sec;
}

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		//result = RAM_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		//result = MMC_disk_status();
		result = is_dev_inited[DEV_MMC];

		// translate the reslut code here
		stat = result ? 0 : STA_NOINIT;

		return stat;

	case DEV_USB :
		//result = USB_disk_status();

		// translate the reslut code here
		result = is_dev_inited[DEV_USB];

		// translate the reslut code here
		stat = result ? 0 : STA_NOINIT;

		return stat;
#ifdef CFG_FLASH_FAT
	case DEV_FLASH:
		result = is_dev_inited[DEV_FLASH];
		// translate the reslut code here
		stat = result ? 0 : STA_NOINIT;
		return stat;
#endif
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		//result = RAM_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		//result = MMC_disk_initialize();
        sdmmc_init();
        result = sdmmc_open();

		// translate the reslut code here
        if (result) {
            stat = STA_NODISK;
            //dbg("i:%d\n",result);
        } else {
            is_dev_inited[DEV_MMC] = 1;
            stat = 0;
        }

		return stat;

	case DEV_USB :
		result = USB_disk_initialize();
		// translate the reslut code here
		if (result) {
			stat = STA_NODISK;
		} else {
			is_dev_inited[DEV_USB] = 1;
			stat = 0;
		}

		return stat;
#ifdef CFG_FLASH_FAT
	case DEV_FLASH:
		result = 0;
		// translate the reslut code here
		if (result) {
		stat = STA_NODISK;
		} else {
			is_dev_inited[DEV_FLASH] = 1;
			stat = 0;
		}
		return stat;
#endif
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		//result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		//result = MMC_disk_read(buff, sector, count);
        result = sdmmc_read_blocks(buff, sector, count);

		// translate the reslut code here
        if (result == 0) {
            res = RES_OK;
        } else {
            res = RES_ERROR;
            //dbg("r:%d\n",result);
        }

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here
		if (result == 0) {
			res = RES_OK;
		} else {
			res = RES_ERROR;
		}

		return res;
#ifdef CFG_FLASH_FAT
	case DEV_FLASH:
	{
		unsigned int offset = sector << FLASH_OFFSET;
		unsigned int write_addr = FLASH_BASE_ADDR + FLASH_START_OFFSET + offset;
		result = flash_read(write_addr, count<<FLASH_OFFSET, buff);
		// translate the reslut code here
		if (result == 0) {
			res = RES_OK;
		} else {
			res = RES_ERROR;
		}

		return res;
	}
#endif
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0
#ifdef CFG_FLASH_FAT
uint8_t flash_write_buf[8192 + 4096] = {0};
#endif

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		//result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		//result = MMC_disk_write(buff, sector, count);
        result = sdmmc_write_blocks(buff, sector, count);

		// translate the reslut code here
        if (result == 0) {
            res = RES_OK;
        } else {
            res = RES_ERROR;
            //dbg("w:%d\n",result);
        }

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_write(buff, sector, count);
		if (result == 0) {
			res = RES_OK;
		} else {
			res = RES_ERROR;
		}

		// translate the reslut code here

		return res;
#ifdef CFG_FLASH_FAT
	case DEV_FLASH:
	{
		// (0X200000 - FLASH_OFFSET - FLASH_INFO_SIZE) / FF_MAX_SS
		if (sector > 3808) {
			dbg("sector error 0x%x\n", sector);
			return RES_ERROR;
		}

		unsigned int cal_offset = 0;
		unsigned int cal_sector = 0;
		uint8_t read_count = 0;
		if (sector % 8) {
			cal_sector = sector - (sector % 8);
			cal_offset = cal_sector << FLASH_OFFSET;
			read_count = 8;
		} else {
			cal_sector = sector;
			cal_offset = cal_sector << FLASH_OFFSET;
		}

		unsigned int cal_write_addr = FLASH_BASE_ADDR + FLASH_START_OFFSET + cal_offset;
		unsigned int offset = sector << FLASH_OFFSET;
		unsigned int write_offset = (sector - cal_sector) << 9;
		unsigned int write_addr = FLASH_BASE_ADDR + FLASH_START_OFFSET + offset;
		memset(flash_write_buf, 0, sizeof(flash_write_buf));
		if (count < 8) {
			read_count = 8;
		} else if (count <= 16) {
			read_count += 16;
		} else {
			dbg("!!!! %s count err %d\n", __func__, count);
			read_count += 16;
		}

		result = flash_read(cal_write_addr, read_count<<FLASH_OFFSET, flash_write_buf);
		memcpy(flash_write_buf + write_offset , buff, count<<FLASH_OFFSET);

		flash_erase(cal_write_addr, read_count<<FLASH_OFFSET);
		result = flash_write(cal_write_addr, read_count<<FLASH_OFFSET, flash_write_buf);

		if (result == 0) {
			flash_cache_invalid_range((void *)(write_addr), read_count<<FLASH_OFFSET);
			res = RES_OK;
		} else {
			dbg("%s flash write err %d\n", __func__, result);
			res = RES_ERROR;
		}
		// translate the reslut code here
		return res;
	}
#endif
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	//int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card
		switch (cmd) {
            case CTRL_SYNC:
                res = RES_OK;
                break;
            case GET_SECTOR_COUNT: {
                DWORD sector_count, sector_size;
                sdmmc_info(&sector_count, &sector_size);
                if (sector_count > 0) {
                    *((DWORD *)buff) = sector_count;
                    res = RES_OK;
                } else {
                    res = RES_ERROR;
                }
                break;
            }
            case GET_BLOCK_SIZE:
                *((DWORD *)buff) = 1; // default when not known
                res = RES_OK;
                break;
        }

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
#ifdef CFG_FLASH_FAT
	case DEV_FLASH:
		switch (cmd) {
		case CTRL_SYNC:
			res = RES_OK;
			break;
		case GET_SECTOR_COUNT: {
			DWORD flash_size = 0;
			flash_size = flash_chip_size_get();
			flash_size -= (FLASH_START_OFFSET + FLASH_INFO_SIZE);
			*((DWORD *)buff) = flash_size / FF_MAX_SS; // default when not known
			res = RES_OK;
			break;
		}
		case GET_SECTOR_SIZE:
			*((DWORD *)buff) = FF_MAX_SS; // default when not known
			res = RES_OK;
			break;
		case GET_BLOCK_SIZE:
			*((DWORD *)buff) = 1; // default when not known
			res = RES_OK;
			break;
		default:
			res = RES_PARERR;
		break;
		}
		dbg("%s ret %d\n", __func__, res);
		return res;
#endif
	}

	return RES_PARERR;
}

