/**
  ******************************************************************************
  * @file    usbh_ioreq.h
  * @author  MCD Application Team
  * @brief   Header file for usbh_ioreq.c
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

/* Define to prevent recursive  ----------------------------------------------*/
#ifndef __USBH_IOREQ_H
#define __USBH_IOREQ_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"

/** @defgroup USBH_IOREQ_Exported_Defines
  * @{
  */

#define USBH_PID_SETUP                            0
#define USBH_PID_DATA                             1

#define USBH_EP_CONTROL                           0
#define USBH_EP_ISO                               1
#define USBH_EP_BULK                              2
#define USBH_EP_INTERRUPT                         3

#define USBH_SETUP_PKT_SIZE                       8

/** @defgroup USBH_IOREQ_Exported_FunctionsPrototype
  * @{
  */
USBH_StatusTypeDef USBH_CtlSendSetup(USBH_HandleTypeDef *phost,
                                     uint8_t *buff,
                                     uint8_t hc_num);

USBH_StatusTypeDef USBH_CtlSendData(USBH_HandleTypeDef *phost,
                                    uint8_t *buff,
                                    uint16_t length,
                                    uint8_t hc_num,
                                    uint8_t do_ping);

USBH_StatusTypeDef USBH_CtlReceiveData(USBH_HandleTypeDef *phost,
                                       uint8_t *buff,
                                       uint16_t length,
                                       uint8_t hc_num);

USBH_StatusTypeDef USBH_BulkReceiveData(USBH_HandleTypeDef *phost,
                                        uint8_t *buff,
                                        uint16_t length,
                                        uint8_t hc_num);

USBH_StatusTypeDef USBH_BulkSendData(USBH_HandleTypeDef *phost,
                                     uint8_t *buff,
                                     uint16_t length,
                                     uint8_t hc_num,
                                     uint8_t do_ping);

USBH_StatusTypeDef USBH_InterruptReceiveData(USBH_HandleTypeDef *phost,
        uint8_t             *buff,
        uint8_t             length,
        uint8_t             hc_num);

USBH_StatusTypeDef USBH_InterruptSendData(USBH_HandleTypeDef *phost,
        uint8_t *buff,
        uint8_t length,
        uint8_t hc_num);


USBH_StatusTypeDef USBH_IsocReceiveData(USBH_HandleTypeDef *phost,
                                        uint8_t *buff,
                                        uint32_t length,
                                        uint8_t hc_num);


USBH_StatusTypeDef USBH_IsocSendData(USBH_HandleTypeDef *phost,
                                     uint8_t *buff,
                                     uint32_t length,
                                     uint8_t hc_num);

#ifdef __cplusplus
}
#endif

#endif /* __USBH_IOREQ_H */
