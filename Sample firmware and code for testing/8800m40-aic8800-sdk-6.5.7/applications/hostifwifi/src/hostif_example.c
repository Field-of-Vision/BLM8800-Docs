 /**
 *******************************************************************************
 *
 * @file fhost_example.c
 *
 * @brief Definition of an example application task for Fully Hosted firmware.
 *
 * Copyright (C) RivieraWaves 2019-2019
 *
 *******************************************************************************
 */

#include "rtos_al.h"
#include "hostif.h"
#if PLF_CONSOLE
#include "console.h"
#endif
#include "co_utils.h"
#include "string.h"

/**
 *******************************************************************************
 * @defgroup FHOST_EXAMPLE FHOST_EXAMPLE
 * @ingroup FHOST
 * @{
 *
 * This module contains code of an example application.\n
 * Each application needs to define a few mandatory functions:
 * - fhost_application_init: Called during firmware intialization to prepare
 *   the application task.\n
 *   In this example the function creates a single task.
 *
 * - fhost_config_get_next_item: Used by control task to retrieve runtime
 *   configuration of the wifi firmware.\n
 *   In this example the configuration is read from variable @ref example_config
 *
 * This example application is very basic:
 * - First it connect to an Access Point.
 *   Credentials/config of the AP are hardcoded in @ref example_ap_cfg.
 * - Then a DHCP procedure is started to retrieve an IP address.
 * - Finally it connects to a website (forismatic) to retrieve a random quote
 *
 *******************************************************************************
 */

/// Master message queue
static rtos_queue hostif_queue;

/******************************************************************************
 * Application code:
 *****************************************************************************/

void hostif_post_msg(struct hostif_msg *msg)
{
    int ret;
    //dbg("hostif_post_msg,%x,%p\r\n",msg->id,msg->data);
    ret = rtos_queue_write(hostif_queue, msg, 0, true);
    if (ret) {
        dbg("error: queue is full\n");
    }
}

/*
 * Entry point of this example application
 */
static RTOS_TASK_FCT(hostif_example_task)
{
    struct hostif_msg msg;

    for (;;) {
        rtos_queue_read(hostif_queue, &msg, -1, false);
        //dbg("got msg: %x,%p\r\n",msg.id,msg.data);

        switch (msg.id) {
        case HOSTIF_MSG_RXC:
            process_host_rxc_msg(&msg);
            break;
        case HOSTIF_MSG_TXC:
            process_host_txc_msg(&msg);
            break;
        #if defined(CFG_DEVICE_IPC)
        case DEVIPC_CUST_MSG_RXC:
            process_devipc_rxc_custom_msg(&msg);
            break;
        case DEVIPC_CUST_MSG_IND:
            process_devipc_ind_custom_msg(&msg);
            break;
        #endif
        case HOSTIF_READY:
            process_host_if_ready(&msg);
            break;
        case HOSTIF_INIT_DONE:
            process_host_if_init_done(&msg);
            break;
        default:
            break;
        }
    }

    rtos_task_delete(NULL);
}

#if PLF_CONSOLE
int wifi_poweron(int argc, char * const argv[])
{
    //unsigned int info_id = console_cmd_strtoul(argv[1], NULL, 10);
    host_if_repower();
    dbg("hostif repower\r\n");
    return 0;
}

int wifi_poweroff(int argc, char * const argv[])
{
    host_if_poweroff();
    dbg("hostif poweroff\r\n");
    return 0;
}
#endif

#if defined(CFG_DEVICE_IPC)
int wifi_sayhi(int argc, char * const argv[])
{
    uint8_t cust_msg[offsetof_b(dbg_custom_msg_ind_t, buf) + 32];
    dbg_custom_msg_ind_t *ind = (dbg_custom_msg_ind_t *)cust_msg;
    char *str_name = "8800";
    int name_len;
    if ((argc > 1) && (strlen(argv[1]) <= 28)) {
        str_name = argv[1];
    }
    name_len = strlen(str_name);
    // Fill the ind
    ind->cmd = CUST_IND_SAYHI;
    ind->len = 4 + name_len;
    ind->status = 0x00; // Success
    memcpy(&cust_msg[offsetof_b(dbg_custom_msg_ind_t, buf)], "Hi, ", 4);
    memcpy(&cust_msg[offsetof_b(dbg_custom_msg_ind_t, buf) + 4], str_name, name_len);
    // Trace the action
    dbg("IND STR: Hi, %s\r\n", str_name);
    // Send confirm
    host_if_indicate_custmsg(ind);
    return 0;
}
#endif

/******************************************************************************
 * Hostif interfaces:
 * These are the functions required by the hostif that are specific to the
 * final application.
 *****************************************************************************/
/*
 * hostif_application_init: Must initialize the minimum for the application to
 *                         start.
 * In this example only create a new task with the entry point set to the
 * 'hostif_example_task'. The rest on the initialization will be done in this
 * function.
 */
int hostif_application_init(void)
{
    if (rtos_queue_create(sizeof(struct hostif_msg), 10, &hostif_queue)) {
        return 1;
    }

    if (rtos_task_create(hostif_example_task, "Example task", APPLICATION_TASK,
                         512, NULL, RTOS_TASK_PRIORITY(1), NULL))
        return 2;

    #if PLF_CONSOLE
    console_cmd_add("wpon", "wifi pon",  1, 1, wifi_poweron);
    console_cmd_add("wpof", "wifi poff", 1, 1, wifi_poweroff);
    #endif

    #if defined(CFG_DEVICE_IPC)
    console_cmd_add("hi", "say hi", 1, 2, wifi_sayhi);
    #endif

    return 0;
}


/**
 * @}
 */


