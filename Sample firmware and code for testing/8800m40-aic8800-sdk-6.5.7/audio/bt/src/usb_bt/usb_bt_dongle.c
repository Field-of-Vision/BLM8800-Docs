#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "plf.h"
#include "rtos.h"
#include "usb_bt.h"
#include "usb_bt_config.h"
#include "usb_bt_dongle.h"
#include "usbd_audio.h"
#include "audio_types.h"
#include "audio_utils.h"
#include "ring_buffer.h"

typedef enum {
    USB_BUFFER_STATUS_STOP = 0,
    USB_BUFFER_STATUS_START,
    USB_BUFFER_STATUS_RESTART,
    USB_BUFFER_STATUS_REACH_THRESHOLD,
    USB_BUFFER_STATUS_NUM,
} USB_BUFFER_STATUS;

static rtos_task_handle dongle_task_handle = NULL;

static uint16_t usb_audio_pkt_size = 0;

static uint8_t *usb_rx_ring_buffer_storage = NULL;
static ring_buffer_t usb_rx_ring_buffer;
static uint32_t usb_rx_ring_buffer_size = 0;
static uint32_t usb_rx_start_level_size = 0;
static uint8_t usb_rx_ring_buffer_status;

static uint8_t *usb_tx_ring_buffer_storage = NULL;
static ring_buffer_t usb_tx_ring_buffer;
static uint32_t usb_tx_ring_buffer_size = 0;
static uint32_t usb_tx_start_level_size = 0;
static uint8_t usb_tx_ring_buffer_status;

static uint16_t usb_rx_buffer_size = 0;
static uint16_t usb_tx_buffer_size = 0;
static uint8_t *usb_rx_buffer = NULL;
static uint8_t *usb_tx_buffer = NULL;

static uint8_t *usb_rx_src_buffer = NULL;
static uint8_t *usb_tx_src_buffer = NULL;

//static uint16_t d2h_pcm_pkt_size = 0;
//static uint16_t h2d_pcm_pkt_size = 0;
//static uint16_t d2h_encoded_pkt_size = 0;
//static uint16_t h2d_encoded_pkt_size = 0;

static uint8_t usb_audio_ch_num;
static uint8_t headset_capture_out_ch_num;
static uint8_t headset_playback_in_ch_num;

static uint32_t usb_audio_samprate;
static uint32_t headset_voice_samprate;

//static bool bt_acl_connected = false;
//static bool bt_sco_connected = false;

uint64_t Resample_s16(int16_t *input, int16_t *output, int inSampleRate, int outSampleRate, uint64_t inputSize, uint32_t channels)
{
    if (input == NULL)
        return 0;
    uint64_t outputSize = (uint64_t) (inputSize * (double) outSampleRate / (double) inSampleRate);
    outputSize -= outputSize % channels;
    if (output == NULL)
        return outputSize;
    double stepDist = ((double) inSampleRate / (double) outSampleRate);
    const uint64_t fixedFraction = (1LL << 32);
    const double normFixed = (1.0 / (1LL << 32));
    uint64_t step = ((uint64_t) (stepDist * fixedFraction + 0.5));
    uint64_t curOffset = 0;
    for (uint32_t i = 0; i < outputSize; i += 1) {
        for (uint32_t c = 0; c < channels; c += 1) {
            *output++ = (int16_t) (input[c] + (input[c + channels] - input[c]) *
                ((double) (curOffset >> 32) + ((curOffset & (fixedFraction - 1)) * normFixed)));
        }
        curOffset += step;
        input += (curOffset >> 32) * channels;
        curOffset &= (fixedFraction - 1);
    }
    return outputSize;
}

static void set_rx_itf_handler(enum usbd_audio_itf itf)
{
    //dbg("rx_itf:%d\n", itf);
    if (itf == USBD_AUDIO_ITF_NONE) {
        usbd_audio_rxbuf_release();
        usb_rx_ring_buffer_status = USB_BUFFER_STATUS_STOP;
        usb_bt_msg_queue_write(USB_BT_USB_RECV_STOP, 0, true);
    } else {
        usbd_audio_rxbuf_config((uint8_t *)usb_rx_buffer, 0, usb_rx_buffer_size);
        usb_rx_ring_buffer_status = USB_BUFFER_STATUS_START;
        usb_bt_msg_queue_write(USB_BT_USB_RECV_START, 0, true);
    }
}

static void set_tx_itf_handler(enum usbd_audio_itf itf)
{
    //dbg("tx_itf:%d\n", itf);
    if (itf == USBD_AUDIO_ITF_NONE) {
        usbd_audio_txbuf_release();
        usb_tx_ring_buffer_status = USB_BUFFER_STATUS_STOP;
        usb_bt_msg_queue_write(USB_BT_USB_SEND_STOP, 0, true);
    } else {
        memset(usb_tx_buffer, 0, usb_tx_buffer_size);
        usbd_audio_txbuf_config((uint8_t *)usb_tx_buffer, 0, usb_tx_buffer_size);
        usb_tx_ring_buffer_status = USB_BUFFER_STATUS_START;
        usb_bt_msg_queue_write(USB_BT_USB_SEND_START, 0, true);
    }
}

static void data_rx_handler(const struct usbd_audio_data_xfer *xfer)
{
    int rb_ret;
    uint8_t *data = (uint8_t *)xfer->data;
    uint8_t size = xfer->size;
    uint32_t bytes_used;

    // 1st, do channel merge
    if ((headset_playback_in_ch_num == AUD_CH_NUM_1) && (usb_audio_ch_num == AUD_CH_NUM_2)) {
        audio_channel_merge_16bits((int16_t *)data, (int16_t *)data, size / sizeof(int16_t) / 2);
        size = size / 2;
    }

    // 2nd, do src
    if (usb_audio_samprate != headset_voice_samprate) {
        //TODO add better SRC
        Resample_s16((int16_t *)data, (int16_t *)usb_rx_src_buffer, usb_audio_samprate, headset_voice_samprate, size / sizeof(int16_t), headset_playback_in_ch_num);
        data = usb_rx_src_buffer;
        size = size * headset_voice_samprate / usb_audio_samprate;
    }

    rb_ret = ring_buffer_write(&usb_rx_ring_buffer, data, size);
    if (RB_ERR_NONE != rb_ret) {
        ring_buffer_read(&usb_rx_ring_buffer, NULL, size);
        ring_buffer_write(&usb_rx_ring_buffer, data, size);
        dbg("URF\n");
    }

    if (usb_rx_ring_buffer_status == USB_BUFFER_STATUS_START) {
        bytes_used = ring_buffer_bytes_used(&usb_rx_ring_buffer);
        if (bytes_used >= usb_rx_start_level_size) {
            usb_rx_ring_buffer_status = USB_BUFFER_STATUS_REACH_THRESHOLD;
        }
    }
}

static void data_tx_handler(const struct usbd_audio_data_xfer *xfer)
{
    int rb_ret;
    uint8_t *data = (uint8_t *)xfer->data;
    uint32_t size = xfer->size;

    if (usb_tx_ring_buffer_status >= USB_BUFFER_STATUS_RESTART) {
        size = xfer->size * headset_voice_samprate / usb_audio_samprate * headset_capture_out_ch_num / usb_audio_ch_num;
        rb_ret = ring_buffer_read(&usb_tx_ring_buffer, data, size);
        if (RB_ERR_NONE == rb_ret) {
            // 1st, do src
            if (usb_audio_samprate != headset_voice_samprate) {
                //TODO add better SRC
                Resample_s16((int16_t *)data, (int16_t *)usb_tx_src_buffer, headset_voice_samprate, usb_audio_samprate, size / sizeof(int16_t), headset_capture_out_ch_num);
                size = size * usb_audio_samprate / headset_voice_samprate;
                memcpy(data, usb_tx_src_buffer, size);
            }

            // 2nd, do channel copy
            if ((headset_capture_out_ch_num == AUD_CH_NUM_1) && (usb_audio_ch_num == AUD_CH_NUM_2)) {
                audio_channel_copy_16bits((int16_t *)data, (int16_t *)data, size / sizeof(int16_t));
            }
        } else {
            memset((void *)xfer->data, 0, xfer->size);
            //usb tx buffer empty
            dbg("UTE\n");
        }
    } else {
        memset((void *)xfer->data, 0, xfer->size);
        //usb tx buffer caching
        dbg("UTC\n");
    }
}

static void set_volume_handler(uint32_t percent)
{
    dbg("set_volume_handler, percent:%d\n", percent);
}

static struct usbd_audio_cfg usb_audio_cfg = {
    .rx_sampling_freq = 48000,
    .tx_sampling_freq = 48000,
    .set_rx_itf = set_rx_itf_handler,
    .set_tx_itf = set_tx_itf_handler,
    .data_rx_done = data_rx_handler,
    .data_tx_done = data_tx_handler,
    .set_volume = set_volume_handler,
};

uint32_t usb_bt_dongle_data_recv(uint8_t *data, uint32_t size)
{
    uint32_t bytes_free;
    uint32_t bytes_used;
    uint32_t bytes_drop = 0;

    if (usb_tx_ring_buffer_status >= USB_BUFFER_STATUS_START) {
        // TODO add mSBC decode
        GLOBAL_INT_DISABLE();
        bytes_free = ring_buffer_bytes_free(&usb_tx_ring_buffer);
        if (bytes_free >= size) {
            ring_buffer_write(&usb_tx_ring_buffer, data, size);
        } else {
            bytes_drop = size - bytes_free;
            ring_buffer_read(&usb_tx_ring_buffer, NULL, bytes_drop);
            ring_buffer_write(&usb_tx_ring_buffer, data, size);
        }
        if (usb_tx_ring_buffer_status == USB_BUFFER_STATUS_START) {
            bytes_used = ring_buffer_bytes_used(&usb_tx_ring_buffer);
            if (bytes_used >= usb_tx_start_level_size) {
                usb_tx_ring_buffer_status = USB_BUFFER_STATUS_REACH_THRESHOLD;
            }
        }
        GLOBAL_INT_RESTORE();

        if (bytes_drop) {
            dbg("UTF\n");
        }
    } else {
        dbg("UTSP\n");
    }

    return size;
}

uint32_t usb_bt_dongle_data_send(uint8_t *data, uint32_t size)
{
    int rb_ret;

    if (usb_rx_ring_buffer_status >= USB_BUFFER_STATUS_START) {
        if (usb_rx_ring_buffer_status >= USB_BUFFER_STATUS_RESTART) {
            // TODO add mSBC encode
            GLOBAL_INT_DISABLE();
            rb_ret = ring_buffer_read(&usb_rx_ring_buffer, data, size);
            GLOBAL_INT_RESTORE();
            if (RB_ERR_NONE != rb_ret) {
                memset(data, 0, size);
                dbg("URE\n");
            }
        } else {
            memset(data, 0, size);
            dbg("URC\n");
        }
    } else {
        memset(data, 0, size);
        dbg("URSP\n");
    }

    return size;
}

static RTOS_TASK_FCT(dongle_task)
{
    do {
        uint32_t msg;
        while (1) {
            usb_bt_msg_queue_read(&msg, -1, false);
            switch (msg) {
            case USB_BT_CONNECT: {
                // do acl connect
                break;
            }
            case USB_BT_CONNECTED: {
                usbd_audio_init(&usb_audio_cfg);
                break;
            }
            case USB_BT_DISCONNECT: {
                //do acl disconnect
                break;
            }
            case USB_BT_DISCONNECTED: {
                usbd_audio_deinit();
                break;
            }
            case USB_BT_SCO_CONNECT: {
                // do sco connect
                break;
            }
            case USB_BT_SCO_CONNECTED: {
                break;
            }
            case USB_BT_SCO_DISCONNECT: {
                // do sco disconnect
                break;
            }
            case USB_BT_SCO_DISCONNECTED: {
                break;
            }
            case USB_BT_USB_RECV_STOP: {
                break;
            }
            case USB_BT_USB_RECV_START: {
                break;
            }
            case USB_BT_USB_SEND_STOP: {
                break;
            }
            case USB_BT_USB_SEND_START: {
                break;
            }
            default: {
                break;
            }
            }
        }
    } while (0);

    usb_bt_dongle_deinit();
    rtos_task_delete(NULL);
}

int usb_bt_dongle_init(void)
{
    usb_audio_samprate = usb_bt_config_usb_audio_samprate_get();
    usb_audio_ch_num = usb_bt_config_usb_audio_ch_num_get();
    usb_audio_pkt_size = usb_bt_config_usb_audio_pkt_size_get();
    headset_voice_samprate = usb_bt_config_headset_voice_samprate_get();
    headset_capture_out_ch_num = usb_bt_config_headset_capture_out_ch_num_get();
    headset_playback_in_ch_num = usb_bt_config_headset_playback_in_ch_num_get();

    usb_rx_ring_buffer_size = usb_bt_config_usb_rx_ring_buffer_size_get();
    usb_rx_start_level_size = usb_bt_config_usb_rx_start_level_size_get();
    usb_tx_ring_buffer_size = usb_bt_config_usb_tx_ring_buffer_size_get();
    usb_tx_start_level_size = usb_bt_config_usb_tx_start_level_size_get();
    usb_rx_buffer_size = 2 * usb_audio_pkt_size;
    usb_tx_buffer_size = 2 * usb_audio_pkt_size;

    usb_rx_ring_buffer_status = USB_BUFFER_STATUS_STOP;
    usb_tx_ring_buffer_status = USB_BUFFER_STATUS_STOP;

    usb_audio_cfg.rx_sampling_freq = usb_audio_samprate;
    usb_audio_cfg.tx_sampling_freq = usb_audio_samprate;

    usb_rx_buffer = rtos_malloc(usb_rx_buffer_size);
    if (!usb_rx_buffer) {
        dbg("ERR: usb_rx_buffer malloc fail\n");
        return -1;
    }

    usb_tx_buffer = rtos_malloc(usb_tx_buffer_size);
    if (!usb_tx_buffer) {
        dbg("ERR: usb_tx_buffer malloc fail\n");
        return -1;
    }

    if (usb_audio_samprate != headset_voice_samprate) {
        usb_rx_src_buffer = rtos_malloc(usb_audio_pkt_size);
        if (!usb_rx_src_buffer) {
            dbg("ERR: usb_rx_src_buffer malloc fail\n");
            return -1;
        }

        usb_tx_src_buffer = rtos_malloc(usb_audio_pkt_size);
        if (!usb_tx_src_buffer) {
            dbg("ERR: usb_tx_src_buffer malloc fail\n");
            return -1;
        }
    }

    usb_rx_ring_buffer_storage = rtos_malloc(usb_rx_ring_buffer_size);
    if (!usb_rx_ring_buffer_storage) {
        dbg("ERR: usb_rx_ring_buffer_storage malloc fail\n");
        return -1;
    }
    ring_buffer_init(&usb_rx_ring_buffer, usb_rx_ring_buffer_storage, usb_rx_ring_buffer_size);

    usb_tx_ring_buffer_storage = rtos_malloc(usb_tx_ring_buffer_size);
    if (!usb_tx_ring_buffer_storage) {
        dbg("ERR: usb_tx_ring_buffer_storage malloc fail\n");
        return -1;
    }
    ring_buffer_init(&usb_tx_ring_buffer, usb_tx_ring_buffer_storage, usb_tx_ring_buffer_size);

    if (rtos_task_create(dongle_task, "dongle task", USB_BT_TASK,
                         TASK_STACK_SIZE_USB_BT, NULL, TASK_PRIORITY_USB_BT, &dongle_task_handle)) {
        dbg("ERR: dongle task create fail\n");
        return -1;
    }

    return 0;
}

int usb_bt_dongle_deinit(void)
{
    if (usb_rx_buffer) {
        rtos_free(usb_rx_buffer);
        usb_rx_buffer = NULL;
    }

    if (usb_tx_buffer) {
        rtos_free(usb_tx_buffer);
        usb_tx_buffer = NULL;
    }

    ring_buffer_deinit(&usb_rx_ring_buffer);
    if (usb_rx_ring_buffer_storage) {
        rtos_free(usb_rx_ring_buffer_storage);
        usb_rx_ring_buffer_storage = NULL;
    }

    ring_buffer_deinit(&usb_tx_ring_buffer);
    if (usb_tx_ring_buffer_storage) {
        rtos_free(usb_tx_ring_buffer_storage);
        usb_tx_ring_buffer_storage = NULL;
    }

    return 0;
}
