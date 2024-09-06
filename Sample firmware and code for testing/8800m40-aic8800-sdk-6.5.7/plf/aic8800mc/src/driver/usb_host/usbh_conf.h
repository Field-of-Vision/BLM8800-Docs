/**
  ******************************************************************************
  * @file    usbh_conf.h
  * @brief   Header file for usbh_conf.c
  ******************************************************************************
  * @attention
  *
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBH_CONF_H
#define __USBH_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"

#define USBH_MAX_NUM_ENDPOINTS                4
#define USBH_MAX_NUM_INTERFACES               10
#define USBH_MAX_NUM_CONFIGURATION            1
#define USBH_KEEP_CFG_DESCRIPTOR              1
#define USBH_MAX_NUM_SUPPORTED_CLASS          1
#define USBH_MAX_SIZE_CONFIGURATION           0x400//0x200//
#define USBH_MAX_DATA_BUFFER                  0x400//0x200//
#define USBH_DEBUG_LEVEL                      2
#ifdef CFG_RTOS
#define USBH_USE_OS                           1
#else
#define USBH_USE_OS                           0
#endif

/** @defgroup USBH_Exported_Macros
  * @{
  */

/* rtos macros */
#if (USBH_USE_OS == 1)
#include "rtos_al.h"
#define   USBH_PROCESS_PRIO          RTOS_TASK_PRIORITY(1)
#define   USBH_PROCESS_STACK_SIZE    (2 * configMINIMAL_STACK_SIZE)
#endif

/* Memory management macros */
#define USBH_malloc               malloc
#define USBH_free                 free
#define USBH_memset               memset
#define USBH_memcpy               memcpy


/* DEBUG macros */
#if (USBH_DEBUG_LEVEL > 0)
#define  USBH_UsrLog(...)   dbg(__VA_ARGS__);\
                            dbg("\n");
#else
#define USBH_UsrLog(...)
#endif

#if (USBH_DEBUG_LEVEL > 1)

#define  USBH_ErrLog(...)   dbg("ERROR: ") ;\
                            dbg(__VA_ARGS__);\
                            dbg("\n");
#else
#define USBH_ErrLog(...)
#endif

#if (USBH_DEBUG_LEVEL > 2)
#define  USBH_DbgLog(...)   dbg("DEBUG : ") ;\
                            dbg(__VA_ARGS__);\
                            dbg("\n");
#define USBH_DbgPrt(...)    dbg(__VA_ARGS__);
#else
#define USBH_DbgLog(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __USBH_CONF_H */
