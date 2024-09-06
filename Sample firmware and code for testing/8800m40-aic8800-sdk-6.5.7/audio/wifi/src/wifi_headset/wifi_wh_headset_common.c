#include <stdint.h>
#include "wifi_wh_headset.h"
#include "wifi_voice.h"
#include "ring_buffer.h"
#include "dbg.h"

/*
 * DAM fetch data from the buffer (started from 'buf' with length 'len') and send them to audio devices & interfaces
 * when this function was called, data stored in the buffer has been played, we must refill this buffer with new data
 * before DMA fetching data from this buffer again
 */
uint32_t wifi_wh_headset_playback_handler(uint8_t *buf, uint32_t len)
{
    int rb_st;
    ring_buffer_t *playback_ring_buffer = wifi_wh_headset_playback_ring_buffer_get();

    wifi_wh_headset_playback_ring_buffer_lock();
    rb_st = ring_buffer_read(playback_ring_buffer, buf, len);
    wifi_wh_headset_playback_ring_buffer_unlock();
    if (RB_ERR_NONE != rb_st) {
        wifi_wh_headset_playback_ring_buffer_lock();
        uint32_t left_size = ring_buffer_bytes_used(playback_ring_buffer);
        if (left_size) {
            ring_buffer_read(playback_ring_buffer, buf, left_size);
        }
        wifi_wh_headset_playback_ring_buffer_unlock();
        memset((buf + left_size), 0, (len - left_size));
        dbg("PE:%d/%d\n", len, left_size);
        //voice_asio_auto_calibrate_samplerate(VOICE_ASIO_SPEED_DOWN);
    }

    return len;
}

/*
 * DMA fetch data from audio devices & interfaces and store them in the buffer (started from 'buf' with length 'len')
 * when this function was called, most recently recorded data has been stored in the buffer, we have to copy them to
 * somewhere else before they were overwritten by the following recorded data
 */
uint32_t wifi_wh_headset_capture_handler(uint8_t *buf, uint32_t len)
{
    int rb_st;
    ring_buffer_t *capture_ring_buffer = wifi_wh_headset_capture_ring_buffer_get();

    wifi_wh_headset_capture_ring_buffer_lock();
    rb_st = ring_buffer_write(capture_ring_buffer, buf, len);
    if (RB_ERR_NONE != rb_st) {
        dbg("CF\n");
        rb_st = ring_buffer_read(capture_ring_buffer, NULL, len);
        rb_st = ring_buffer_write(capture_ring_buffer, (uint8_t *)buf, len);
    }
    wifi_wh_headset_capture_ring_buffer_unlock();

    wifi_wh_headset_capture_data_ready(10, false);

    return len;
}

