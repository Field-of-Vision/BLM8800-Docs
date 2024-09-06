#include <stdint.h>
#include <stdbool.h>
#include "plf.h"

// for Dongle
#define USB_RX_RING_BUFFER_SIZE_MS     60
#define USB_RX_START_LEVEL_SIZE_MS     30
#define USB_TX_RING_BUFFER_SIZE_MS     60
#define USB_TX_START_LEVEL_SIZE_MS     30

#if defined(CFG_USB_AUDIO_FREQ_48K)
#define USB_AUDIO_SAMPRATE             48000
#elif defined(CFG_USB_AUDIO_FREQ_16K)
#define USB_AUDIO_SAMPRATE             16000
#else
#error "unsupported audio sample rate"
#endif
#define USB_AUDIO_CH_NUM                    2
#define USB_AUDIO_PKT_SIZE_MS               1

#define HEADSET_VOICE_SAMPRATE         8000
#define HEADSET_CAPTURE_IN_CH_NUM      1
#define HEADSET_CAPTURE_OUT_CH_NUM     1
#define HEADSET_PLAYBACK_IN_CH_NUM     1
#define HEADSET_PLAYBACK_OUT_CH_NUM    2

#define D2H_PKT_SIZE_MS              7.5f
#define H2D_PKT_SIZE_MS              7.5f

#define USB_AUDIO_PKT_SIZE         (USB_AUDIO_PKT_SIZE_MS * USB_AUDIO_SAMPRATE / 1000 * USB_AUDIO_CH_NUM * sizeof(int16_t))
#define USB_RX_RING_BUFFER_SIZE    (USB_RX_RING_BUFFER_SIZE_MS * HEADSET_VOICE_SAMPRATE / 1000 * HEADSET_PLAYBACK_IN_CH_NUM * sizeof(int16_t))
#define USB_RX_START_LEVEL_SIZE    (USB_RX_START_LEVEL_SIZE_MS * HEADSET_VOICE_SAMPRATE / 1000 * HEADSET_PLAYBACK_IN_CH_NUM * sizeof(int16_t))
#define USB_TX_RING_BUFFER_SIZE    (USB_TX_RING_BUFFER_SIZE_MS * HEADSET_VOICE_SAMPRATE / 1000 * HEADSET_CAPTURE_OUT_CH_NUM * sizeof(int16_t))
#define USB_TX_START_LEVEL_SIZE    (USB_TX_START_LEVEL_SIZE_MS * HEADSET_VOICE_SAMPRATE / 1000 * HEADSET_CAPTURE_OUT_CH_NUM * sizeof(int16_t))


#define MSG_QUEUE_ELT_NB                    20

uint32_t usb_bt_config_usb_audio_samprate_get(void)
{
    return USB_AUDIO_SAMPRATE;
}

uint8_t usb_bt_config_usb_audio_ch_num_get(void)
{
    return USB_AUDIO_CH_NUM;
}

uint16_t usb_bt_config_usb_audio_pkt_size_get(void)
{
    return USB_AUDIO_PKT_SIZE;
}

uint32_t usb_bt_config_headset_voice_samprate_get(void)
{
    return HEADSET_VOICE_SAMPRATE;
}

uint8_t usb_bt_config_headset_capture_in_ch_num_get(void)
{
    return HEADSET_CAPTURE_IN_CH_NUM;
}

uint8_t usb_bt_config_headset_capture_out_ch_num_get(void)
{
    return HEADSET_CAPTURE_OUT_CH_NUM;
}

uint8_t usb_bt_config_headset_playback_in_ch_num_get(void)
{
    return HEADSET_PLAYBACK_IN_CH_NUM;
}

uint8_t usb_bt_config_headset_playback_out_ch_num_get(void)
{
    return HEADSET_PLAYBACK_OUT_CH_NUM;
}

float usb_bt_config_d2h_pkt_size_ms_get(void)
{
    return D2H_PKT_SIZE_MS;
}

float usb_bt_config_h2d_pkt_size_ms_get(void)
{
    return H2D_PKT_SIZE_MS;
}

uint16_t usb_bt_config_usb_rx_ring_buffer_size_ms_get(void)
{
    return USB_RX_RING_BUFFER_SIZE_MS;
}

uint16_t usb_bt_config_usb_rx_start_level_size_ms_get(void)
{
    return USB_RX_START_LEVEL_SIZE_MS;
}

uint16_t usb_bt_config_usb_tx_ring_buffer_size_ms_get(void)
{
    return USB_TX_RING_BUFFER_SIZE_MS;
}

uint16_t usb_bt_config_usb_tx_start_level_size_ms_get(void)
{
    return USB_TX_START_LEVEL_SIZE_MS;
}

uint32_t usb_bt_config_usb_rx_ring_buffer_size_get(void)
{
    return USB_RX_RING_BUFFER_SIZE;
}

uint32_t usb_bt_config_usb_rx_start_level_size_get(void)
{
    return USB_RX_START_LEVEL_SIZE;
}

uint32_t usb_bt_config_usb_tx_ring_buffer_size_get(void)
{
    return USB_TX_RING_BUFFER_SIZE;
}

uint32_t usb_bt_config_usb_tx_start_level_size_get(void)
{
    return USB_TX_START_LEVEL_SIZE;
}

uint8_t usb_bt_config_msg_queue_elt_nb_get(void)
{
    return MSG_QUEUE_ELT_NB;
}

