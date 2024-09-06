/**
  ******************************************************************************
  * @file    usbh_diskio.h
  * @author  MCD Application Team
  * @brief   Header for usbh_diskio.c module
  ******************************************************************************
  * @attention
  *
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBH_DISKIO_H
#define __USBH_DISKIO_H
#include "ff.h"
#include "diskio.h"
#include "usbh_def.h"

#define _USE_WRITE   1
#define _USE_IOCTL   1
#define _USE_BUFF_WO_ALIGNMENT 0

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
DSTATUS USB_disk_initialize();
DRESULT USB_disk_read(BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
DRESULT USB_disk_write(const BYTE *buff, DWORD sector, UINT count);
#endif
DSTATUS USBH_disk_init(void (*pUsrFunc)(USBH_HandleTypeDef *phost, uint8_t));
USBH_StatusTypeDef  USBH_disk_process(void);

#endif /* __USBH_DISKIO_H */

