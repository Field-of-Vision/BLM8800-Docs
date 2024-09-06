 /**
 *******************************************************************************
 *
 * @file fhost_http_serv.c
 *
 * @brief Definition of an example application task for Fully Hosted firmware.
 *
 * Copyright (C) RivieraWaves 2019-2019
 *
 *******************************************************************************
 */

#include "fhost.h"
#include "wlan_if.h"
#include "http_serv_netconn.h"

#define CONFIG_SOFTAP_HTTP_SERV     0

/******************************************************************************
 * Application code:
 *****************************************************************************/
rtos_task_handle http_serv_task_handle = NULL;

#if (HTTP_FATFS_SELECTION == 2)
#include "usbh_msc.h"
#include "usbh_diskio.h"

#define USBH_APPLICATION_START      (0x01UL << 0)
#define USBH_APPLICATION_STOP       (0x01UL << 1)

#if !(USBH_USE_OS == 1)
typedef enum
{
    APPLICATION_IDLE = 0,
    APPLICATION_START,
    APPLICATION_RUNNING,
    APPLICATION_STOP,
} MSC_ApplicationTypeDef;

MSC_ApplicationTypeDef application_state = APPLICATION_IDLE;
#endif

static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{
    switch (id)
    {
        case HOST_USER_SELECT_CONFIGURATION:
            break;

        case HOST_USER_DISCONNECTION:
            #if (USBH_USE_OS == 1)
            if (http_serv_task_handle) {
                rtos_task_notify_setbits(http_serv_task_handle, USBH_APPLICATION_STOP, true);
            }
            #else
            application_state = APPLICATION_STOP;
            #endif
            break;

        case HOST_USER_CLASS_ACTIVE:
            #if (USBH_USE_OS == 1)
            if (http_serv_task_handle) {
                rtos_task_notify_setbits(http_serv_task_handle, USBH_APPLICATION_START, false);
            }
            #else
            application_state = APPLICATION_START;
            #endif
            break;

        default:
            break;
    }
}
#endif

/*
 * Entry point of this example application
 */
static RTOS_TASK_FCT(fhost_http_serv_task)
{
    do {
        int ret;
        char *ssid = "MySSID", *pw = "password";
        #if CONFIG_SOFTAP_HTTP_SERV
        ret = wlan_start_ap(0, (uint8_t *)ssid, (uint8_t *)pw);
        if (ret) {
            dbg("AP start err: %d\n", ret);
            break;
        }
        dbg("AP started\r\n");
        #else
        ret = wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, 0);
        if (ret) {
            dbg("STA connect fail: %d\r\n", ret);
            break;
        }
        wlan_connected = 1;
        dbg("STA connected\r\n");
        #endif
        #if !(HTTP_FATFS_SELECTION == 2)
        http_server_netconn_init();
        #else
        USBH_disk_init(USBH_UserProcess);
        while (1) {
            #if (USBH_USE_OS == 1)
            unsigned int notification = rtos_task_wait_notification(-1);
            if (notification & USBH_APPLICATION_START) {
                /* Start app */
                http_server_netconn_init();
            }
            if (notification & USBH_APPLICATION_STOP) {
                /* Stop app */
                http_server_netconn_stop();
            }
            #else
            /* USB Host Background task */
            USBH_disk_process();
            /* Mass Storage Application State Machine */
            switch (application_state) {
                case APPLICATION_START:
                    http_server_netconn_init();
                    application_state = APPLICATION_RUNNING;
                    break;

                case APPLICATION_STOP:
                    http_server_netconn_stop();
                    application_state = APPLICATION_IDLE;
                default:
                    break;
            }
            #endif
        }
        #endif
    } while (0);
    rtos_task_delete(NULL);
}

/******************************************************************************
 * Fhost FW interfaces:
 * These are the functions required by the fhost FW that are specific to the
 * final application.
 *****************************************************************************/
/*
 * fhost_application_init: Must initialize the minimum for the application to
 *                         start.
 * In this example only create a new task with the entry point set to the
 * 'fhost_example_task'. The rest on the initialization will be done in this
 * function.
 */
int fhost_application_init(void)
{
    if (rtos_task_create(fhost_http_serv_task, "HTTP serv task", APPLICATION_TASK,
                         512, NULL, RTOS_TASK_PRIORITY(1), &http_serv_task_handle))
        return 1;

    return 0;
}
