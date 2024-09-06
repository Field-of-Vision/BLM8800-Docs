#ifndef _USB_BT_DONGLE_H_
#define _USB_BT_DONGLE_H_

#include <stdint.h>

uint32_t usb_bt_dongle_data_recv(uint8_t *data, uint32_t size);
uint32_t usb_bt_dongle_data_send(uint8_t *data, uint32_t size);
int usb_bt_dongle_init(void);
int usb_bt_dongle_deinit(void);

#endif
