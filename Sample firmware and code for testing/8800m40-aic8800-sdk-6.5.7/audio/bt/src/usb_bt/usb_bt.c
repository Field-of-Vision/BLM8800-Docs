#include <stdint.h>
#include <stdbool.h>
#include "usb_bt_config.h"
#include "rtos.h"
#include "dbg.h"

static rtos_queue usb_bt_msg_queue = NULL;

int usb_bt_msg_queue_write(uint32_t msg, int timeout, bool isr)
{
    int res = 0;

    res =  rtos_queue_write(usb_bt_msg_queue, &msg, timeout, isr);
    if (res != 0) {
        dbg("ERR: msg:0x%X write fail\n", msg);
    }

    return res;
}

int usb_bt_msg_queue_read(uint32_t *msg, int timeout, bool isr)
{
    return rtos_queue_read(usb_bt_msg_queue, msg, timeout, isr);
}

int usb_bt_msg_queue_cnt_get(void)
{
    return rtos_queue_cnt(usb_bt_msg_queue);
}

int usb_bt_init(void)
{
    if (rtos_queue_create(sizeof(uint32_t), usb_bt_config_msg_queue_elt_nb_get(), &usb_bt_msg_queue)) {
        dbg("ERR: usb_bt_msg_queue create fail\n");
        return -1;
    }

    return 0;
}

int usb_bt_deinit(void)
{
    if (usb_bt_msg_queue) {
        rtos_queue_delete(usb_bt_msg_queue);
        usb_bt_msg_queue = NULL;
    }

    return 0;
}
