#include <stdint.h>
#include "wifi_mic_tx.h"
#include "wifi_mic_config.h"
#include "ring_buffer.h"
#include "audio_utils.h"

/*
 * DAM fetch data from the buffer (started from 'buf' with length 'len') and send them to audio devices & interfaces
 * when this function was called, data stored in the buffer has been played, we must refill this buffer with new data
 * before DMA fetching data from this buffer again
 */
uint32_t wifi_mic_tx_playback_handler(uint8_t *buf, uint32_t len)
{
    int rb_st;
    uint32_t len_want = len;
    ring_buffer_t *playback_ring_buffer = wifi_mic_tx_playback_ring_buffer_get();

    if ((wifi_mic_config_mic_tx_playback_ch_num_get() == AUD_CH_NUM_2) && (wifi_mic_config_mic_tx_capture_out_ch_num_get() == AUD_CH_NUM_1)) {
        len_want = len / wifi_mic_config_mic_tx_playback_ch_num_get();
    }

    wifi_mic_tx_playback_ring_buffer_lock();
    rb_st = ring_buffer_read(playback_ring_buffer, buf, len_want);
    if (RB_ERR_NONE != rb_st) {
        uint32_t left_size = ring_buffer_bytes_used(playback_ring_buffer);
        if (left_size) {
            ring_buffer_read(playback_ring_buffer, buf, left_size);
        }
        memset((buf + left_size), 0, (len_want - left_size));
        dbg("TPE:%d/%d\n", len_want, left_size);
    }
    wifi_mic_tx_playback_ring_buffer_unlock();

    if ((wifi_mic_config_mic_tx_playback_ch_num_get() == AUD_CH_NUM_2) && (wifi_mic_config_mic_tx_capture_out_ch_num_get() == AUD_CH_NUM_1)) {
        audio_channel_copy_16bits((int16_t *)buf, (int16_t *)buf, (len_want / 2));
    }

    return len;
}

/*
 * DMA fetch data from audio devices & interfaces and store them in the buffer (started from 'buf' with length 'len')
 * when this function was called, most recently recorded data has been stored in the buffer, we have to copy them to
 * somewhere else before they were overwritten by the following recorded data
 */
uint32_t wifi_mic_tx_capture_handler(uint8_t *buf, uint32_t len)
{
    int rb_st;
    ring_buffer_t *capture_ring_buffer = wifi_mic_tx_capture_ring_buffer_get();

    wifi_mic_tx_playback_data_write(buf, len);

    wifi_mic_tx_capture_ring_buffer_lock();
    rb_st = ring_buffer_write(capture_ring_buffer, buf, len);
    if (RB_ERR_NONE != rb_st) {
        dbg("TCF\n");
        rb_st = ring_buffer_read(capture_ring_buffer, NULL, len);
        rb_st = ring_buffer_write(capture_ring_buffer, (uint8_t *)buf, len);
    }
    wifi_mic_tx_capture_ring_buffer_unlock();

    wifi_mic_tx_capture_data_ready(5, false);

    return len;
}


