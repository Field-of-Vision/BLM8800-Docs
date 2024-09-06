#ifndef _USBD_AUDIO_H_
#define _USBD_AUDIO_H_

#include <stdint.h>
#include <stdbool.h>


/*
 * USBD_AUDIO_DIR_RX means Host to Device
 * USBD_AUDIO_DIR_TX means Device to Host
 */
enum usbd_audio_dir {
    USBD_AUDIO_DIR_RX = 0,
    USBD_AUDIO_DIR_TX,
    USBD_AUDIO_DIR_NB,
};

/*
 * select USBD_AUDIO_ITF_NONE means to close USB AUDIO
 */
enum usbd_audio_itf {
    USBD_AUDIO_ITF_NONE = 0,
    USBD_AUDIO_ITF_16BIT,
    USBD_AUDIO_ITF_24BIT,
    USBD_AUDIO_ITF_32BIT,
    USBD_AUDIO_ITF_NB,
};

enum usbd_audio_event {
    USBD_AUDIO_EVENT_RESET = 0,
    USBD_AUDIO_EVENT_DISCONNECT,
    USBD_AUDIO_EVENT_SLEEP,
    USBD_AUDIO_EVENT_WAKEUP,
    USBD_AUDIO_EVENT_CONFIG,
    USBD_AUDIO_EVENT_RX_PAUSE,
    USBD_AUDIO_EVENT_RX_RESUME,
    USBD_AUDIO_EVENT_NB,
};

enum usbd_audio_hid_usage {
    USBD_AUDIO_HID_FAST_FWD      = (1 << 0),
    USBD_AUDIO_HID_REWIND        = (1 << 1),
    USBD_AUDIO_HID_SCAN_NEXT     = (1 << 2),
    USBD_AUDIO_HID_SCAN_PREV     = (1 << 3),
    USBD_AUDIO_HID_STOP          = (1 << 4),
    USBD_AUDIO_HID_PLAY_PAUSE    = (1 << 5),
    USBD_AUDIO_HID_VOL_MUTE      = (1 << 6),
    USBD_AUDIO_HID_VOL_INC       = (1 << 7),
    USBD_AUDIO_HID_VOL_DEC       = (1 << 8),
};

struct usbd_audio_data_xfer {
    const uint8_t *data;
    uint32_t size;
};

struct usbd_audio_cfg {
    uint32_t rx_sampling_freq;
    uint32_t tx_sampling_freq;
    void (*set_rx_itf)(enum usbd_audio_itf itf);
    void (*set_tx_itf)(enum usbd_audio_itf itf);
    void (*data_rx_done)(const struct usbd_audio_data_xfer *xfer);
    void (*data_tx_done)(const struct usbd_audio_data_xfer *xfer);
    void (*mute)(uint8_t mute);
    void (*set_volume)(uint32_t percent);
    uint32_t (*get_volume)(void);
    void (*set_freq)(enum usbd_audio_dir dir, uint32_t freq);
    void (*handle_event)(enum usbd_audio_event event, uint32_t param);
    void (*hid_tx_done)(enum usbd_audio_hid_usage usage, int status);
};

int usbd_audio_init(const struct usbd_audio_cfg *cfg);
void usbd_audio_deinit(void);
int usbd_audio_rxbuf_config(uint8_t *buf, uint32_t offset, uint32_t size);
void usbd_audio_rxbuf_release(void);
int usbd_audio_txbuf_config(const uint8_t *buf, uint32_t offset, uint32_t size);
void usbd_audio_txbuf_release(void);
void usbd_audio_set_hid_usage(enum usbd_audio_hid_usage usage, bool set);

#endif
