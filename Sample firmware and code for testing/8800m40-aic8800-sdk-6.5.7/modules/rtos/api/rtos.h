/**
 ****************************************************************************************
 *
 * @file rtos.h
 *
 * @brief Declarations related to the WiFi stack integration within an RTOS.
 *
 * Copyright (C) RivieraWaves 2017-2019
 *
 ****************************************************************************************
 */

#ifndef RTOS_H_
#define RTOS_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rtos_al.h"

/*
 * DEFINITIONS
 ****************************************************************************************
 */
/// Definitions of the different FHOST task priorities
enum
{
    TASK_PRIORITY_CONSOLE              = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_TEST                 = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_BT_TASK              = RTOS_TASK_PRIORITY(2),
    TASK_PRIORITY_INTERSYS_TASK        = RTOS_TASK_PRIORITY(2),
    TASK_PRIORITY_ASIO                 = RTOS_TASK_PRIORITY(3),
    TASK_PRIORITY_AUDIO                = RTOS_TASK_PRIORITY(3),
    TASK_PRIORITY_DSP                  = RTOS_TASK_PRIORITY(2),
    TASK_PRIORITY_WIFI_VOICE           = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_WIFI_TCPIP           = RTOS_TASK_PRIORITY(3),
    TASK_PRIORITY_WIFI_CNTRL           = RTOS_TASK_PRIORITY(2),
    TASK_PRIORITY_WIFI_IPC             = RTOS_TASK_PRIORITY(4),
    TASK_PRIORITY_WIFI_WPA             = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_WIFI_TG_SEND         = RTOS_TASK_PRIORITY(2),
    TASK_PRIORITY_WIFI_PING_SEND       = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_WIFI_IPERF           = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_WIFI_SMARTCONF       = RTOS_TASK_PRIORITY(2),
    TASK_PRIORITY_WIFI_TX              = RTOS_TASK_PRIORITY(4),
    TASK_PRIORITY_WIFI_HOSTAPD         = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_CO_MAIN              = RTOS_TASK_PRIORITY(2),
    TASK_PRIORITY_WIFI_USER            = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_USB_BT               = RTOS_TASK_PRIORITY(2),
    TASK_PRIORITY_MQTT                 = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_WLAN_CONN            = RTOS_TASK_PRIORITY(1),
    TASK_PRIORITY_MAX                  = RTOS_TASK_PRIORITY(configMAX_PRIORITIES - 1),
};

/// Definitions of the different FHOST task stack size requirements
enum
{
    TASK_STACK_SIZE_CONSOLE              = 512,
    TASK_STACK_SIZE_TEST                 = 2048,
    TASK_STACK_SIZE_BT_TASK              = 1024,
    TASK_STACK_SIZE_ASIO                 = 2048,
    TASK_STACK_SIZE_AUDIO                = 2048,
    TASK_STACK_SIZE_BLE_TASK_ONLY        = 512,
    TASK_STACK_SIZE_BT_BLE_TASK          = 1536,
    TASK_STACK_SIZE_DSP                  = 512,
    TASK_STACK_SIZE_WIFI_VOICE           = 512,
    TASK_STACK_SIZE_WIFI_TCPIP           = 384,
    TASK_STACK_SIZE_WIFI_CNTRL           = 384,
    #ifdef CFG_WAPI
    TASK_STACK_SIZE_WIFI_IPC             = 1024,
    #else
    TASK_STACK_SIZE_WIFI_IPC             = 512,
    #endif
    #ifdef CFG_SOFTAP
    TASK_STACK_SIZE_WIFI_WPA             = 1024,
    #else
    TASK_STACK_SIZE_WIFI_WPA             = 896,
    #endif
    TASK_STACK_SIZE_WIFI_TG_SEND         = 1024,
    TASK_STACK_SIZE_WIFI_PING_SEND       = 512,
    TASK_STACK_SIZE_WIFI_IPERF           = 384,
    TASK_STACK_SIZE_WIFI_SMARTCONF       = 512,
    TASK_STACK_SIZE_WIFI_TX              = 512,
    TASK_STACK_SIZE_WIFI_HOSTAPD         = 1536,
    TASK_STACK_SIZE_CO_MAIN              = 256,
    TASK_STACK_SIZE_WIFI_USER            = 512,
    TASK_STACK_SIZE_USB_BT               = 512,
    TASK_STACK_SIZE_MQTT                 = 2048,
    TASK_STACK_SIZE_SOFTWDG              = 256,
    TASK_STACK_SIZE_WLAN_CONN            = 1024,
};

typedef struct {
    int priority;
    int stack_size;
} rtos_task_cfg_st;
rtos_task_cfg_st get_task_cfg(uint8_t task_id);

/*
 * FUNCTIONS
 ****************************************************************************************
 */

/**
 * Save user data that declared with PRIVATE_HOST_*(G3USER)
 */
void user_data_save(void);

/**
 * Restore user data that declared with PRIVATE_HOST_*(G3USER)
 */
void user_data_restore(void);

/**
 ****************************************************************************************
 * @brief Main function of the RTOS
 *
 * Called after hardware initialization to create all RTOS tasks and start the scheduler.
 ****************************************************************************************
 */
void rtos_main(void);

extern uint8_t get_blink_magic(void);
extern uint8_t* get_mac_address(void);

#endif // RTOS_H_
