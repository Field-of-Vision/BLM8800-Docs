#ifndef _USB_BT_H_
#define _USB_BT_H_

#include <stdint.h>
#include <stdbool.h>

enum {
    USB_BT_CONNECT = 0,
    USB_BT_CONNECTED,
    USB_BT_DISCONNECT,
    USB_BT_DISCONNECTED,
    USB_BT_SCO_CONNECT,
    USB_BT_SCO_CONNECTED,
    USB_BT_SCO_DISCONNECT,
    USB_BT_SCO_DISCONNECTED,
    USB_BT_USB_RECV_STOP,
    USB_BT_USB_RECV_START,
    USB_BT_USB_SEND_STOP,
    USB_BT_USB_SEND_START,
};

typedef enum {
    USB_BT_ROLE_NONE = 0,
    USB_BT_ROLE_DONGLE,
    USB_BT_ROLE_SPEAKER,
} USB_BT_ROLE_T;

int usb_bt_msg_queue_write(uint32_t msg, int timeout, bool isr);
int usb_bt_msg_queue_read(uint32_t *msg, int timeout, bool isr);
int usb_bt_msg_queue_cnt_get(void);
int usb_bt_init(void);
int usb_bt_deinit(void);

#endif
