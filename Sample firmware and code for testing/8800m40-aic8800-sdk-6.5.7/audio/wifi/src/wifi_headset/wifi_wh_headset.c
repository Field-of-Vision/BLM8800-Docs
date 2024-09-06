#include "plf.h"
#if PLF_WIFI_AUDIO
#include <stdint.h>
#include <stdbool.h>
#include "fhost.h"
#include "netdb.h"
#include "fhost_config.h"
#include "fhost_cntrl.h"
#include "fhost_tx.h"
#include "wlan_if.h"
#include "sleep_api.h"
#include "wifi_voice.h"
#include "wifi_wh_config.h"
#include "wifi_wh_headset.h"
#include "ring_buffer.h"
#include "asio.h"
#include "asio_src.h"
#include "audio_types.h"
#include "app_media.h"
#include "app_media_mgr.h"
#include "audio_config.h"
#include "wifi_voice.h"
#include "pmic_api.h"
#include "co_main.h"

typedef enum {
    WIFI_VOICE_IDLE,
    WIFI_VOICE_OPENED,
    WIFI_VOICE_SWITCHING,
    WIFI_VOICE_STARTED,
    WIFI_VOICE_SUSPEND,
} wifi_voice_state_t;

static uint8_t playback_status = WIFI_VOICE_IDLE;
static uint8_t capture_status  = WIFI_VOICE_IDLE;

static bool usb_tx_ongoing = false;

static uint16_t h2d_air_pkt_size = 0;
static uint16_t h2d_ready_pkt_num = 0;

static uint16_t playback_frame_size = 0;
static uint16_t playback_asio_buffer_size = 0;
static uint32_t playback_ring_buffer_size = 0;
static uint32_t playback_start_level_size = 0;

static uint16_t headset_mic_samprate = 0;
static uint16_t capture_frame_size = 0;
static uint8_t capture_in_ch_num = 0;
static uint8_t capture_out_ch_num = 0;
static uint16_t capture_asio_buffer_size = 0;
static uint32_t capture_ring_buffer_size = 0;

static uint8_t *playback_ring_buffer_storage = NULL;
static ring_buffer_t playback_ring_buffer;
static rtos_mutex playback_ring_buffer_mutex = NULL;

static uint8_t *capture_ring_buffer_storage = NULL;
static ring_buffer_t capture_ring_buffer;
static rtos_mutex capture_ring_buffer_mutex = NULL;

static rtos_task_handle headset_task_handle = NULL;

static wifi_voice_led_handler_t headset_led_handler = NULL;

static uint32_t wifi_pairing_timeout_ms = 0;
static co_timer *co_wifi_pairing_timer = NULL;

static TimerHandle_t data_check_timer = NULL;

#define PLAYBACK_RING_BUFFER_LOCK()      rtos_mutex_recursive_lock(playback_ring_buffer_mutex)
#define PLAYBACK_RING_BUFFER_UNLOCK()    rtos_mutex_recursive_unlock(playback_ring_buffer_mutex)

#define CAPTURE_RING_BUFFER_LOCK()       rtos_mutex_recursive_lock(capture_ring_buffer_mutex)
#define CAPTURE_RING_BUFFER_UNLOCK()     rtos_mutex_recursive_unlock(capture_ring_buffer_mutex)

void wifi_wh_headset_led_handler_register(wifi_voice_led_handler_t handler)
{
    headset_led_handler = handler;
}

int wifi_wh_headset_playback_ring_buffer_lock(void)
{
    return PLAYBACK_RING_BUFFER_LOCK();
}

int wifi_wh_headset_playback_ring_buffer_unlock(void)
{
    return PLAYBACK_RING_BUFFER_UNLOCK();
}

int wifi_wh_headset_capture_ring_buffer_lock(void)
{
    return CAPTURE_RING_BUFFER_LOCK();
}

int wifi_wh_headset_capture_ring_buffer_unlock(void)
{
    return CAPTURE_RING_BUFFER_UNLOCK();
}

ring_buffer_t *wifi_wh_headset_playback_ring_buffer_get(void)
{
    return &playback_ring_buffer;
}

ring_buffer_t *wifi_wh_headset_capture_ring_buffer_get(void)
{
    return &capture_ring_buffer;
}

void wifi_wh_headset_capture_data_ready(int timeout, bool isr)
{
    int res;
    uint32_t bytes_used;
    uint32_t pkt_num;

    CAPTURE_RING_BUFFER_LOCK();
    bytes_used = ring_buffer_bytes_used(&capture_ring_buffer);
    CAPTURE_RING_BUFFER_UNLOCK();

    pkt_num = bytes_used / h2d_air_pkt_size;

    if (pkt_num > h2d_ready_pkt_num) {
        for (uint32_t i = 0; i < (pkt_num - h2d_ready_pkt_num); i++) {
            GLOBAL_INT_DISABLE();
            h2d_ready_pkt_num++;
            GLOBAL_INT_RESTORE();
            res = wifi_voice_data_ready(timeout, false);
            if (0 != res) {
                GLOBAL_INT_DISABLE();
                if (h2d_ready_pkt_num > 0) {
                    h2d_ready_pkt_num--;
                }
                GLOBAL_INT_RESTORE();
            }
        }
    }
}

uint8_t wifi_wh_playback_st_get(void)
{
    return playback_status;
}

void wifi_wh_playback_st_set(uint8_t status)
{
    playback_status = status;
}

uint8_t wifi_wh_capture_st_get(void)
{
    return capture_status;
}

void wifi_wh_capture_st_set(uint8_t status)
{
    capture_status = status;
}

uint8_t wifi_wh_usb_tx_ongoing_get(void)
{
    return usb_tx_ongoing;
}

void wifi_wh_usb_tx_ongoing_set(bool ongoing)
{
    usb_tx_ongoing = ongoing;
}

#if 1
static uint8_t voice_asio_local_speed_mode = 0;
enum{
    VOICE_ASIO_DEFALT_SPEED,
    VOICE_ASIO_SPEED_UP,
    VOICE_ASIO_SPEED_DOWN,
    VOICE_ASIO_SPEED_DIE_LOW,
};

static void voice_asio_set_local_speed_mode(uint8_t speed_mode)
{
    voice_asio_local_speed_mode = speed_mode;
}
static uint8_t voice_asio_get_local_speed_mode(void)
{
    return voice_asio_local_speed_mode;
}

static uint8_t pkt_cnt = 0;
static bool data_check_timer_started = false;
static uint32_t normal_level = 0;
void voice_asio_auto_calibrate_samplerate(uint8_t speed_mode)
{
    uint32_t size = 0;
    int time_delta = 0;
    int sample_delta = 0;
    int sample_delta_signed = 0;
    int sample_delta_die_level = 0;
    static int backup_sample_delta = 0;
    uint32_t one_byte_time = 1 * 1000 * 1000 / AUD_SAMPRATE_48000 / (AUD_BITS_16 * 2 / 8);

    PLAYBACK_RING_BUFFER_LOCK();
    size = ring_buffer_bytes_used(&playback_ring_buffer);
    PLAYBACK_RING_BUFFER_UNLOCK();

    switch(speed_mode)
    {
        case VOICE_ASIO_SPEED_UP:
            {
                sample_delta_signed = ((backup_sample_delta > 0x800000)? (backup_sample_delta -0x1000000): backup_sample_delta);
                if(sample_delta_signed < AUD_DPLL_MAX_SAMP_TIME) {
                    time_delta = (size - normal_level) * one_byte_time;
                    if(time_delta > 0xffff)
                        time_delta = 0xffff;
                    sample_delta = dpll_task(time_delta);
                    if(sample_delta > AUD_DPLL_MAX_SAMP_TIME)
                        sample_delta = AUD_DPLL_MAX_SAMP_TIME;
                    voice_asio_set_local_speed_mode(VOICE_ASIO_SPEED_UP);
                }
            }
            break;
        case VOICE_ASIO_DEFALT_SPEED:
            {
                if(voice_asio_get_local_speed_mode() == VOICE_ASIO_SPEED_DIE_LOW){
                    sample_delta_die_level = backup_sample_delta;
                    //TRACE("decoder:%d %d\n", rtos_now(false), size);
                }
                voice_asio_set_local_speed_mode(VOICE_ASIO_DEFALT_SPEED);
            }
            break;
        case VOICE_ASIO_SPEED_DOWN:
            {
                if(voice_asio_get_local_speed_mode() != VOICE_ASIO_SPEED_DIE_LOW) {
                    sample_delta_signed = ((backup_sample_delta > 0x800000)? (backup_sample_delta -0x1000000): backup_sample_delta);
                    if(sample_delta_signed > AUD_DPLL_MIN_SAMP_TIME) {
                        time_delta = (size - normal_level)*one_byte_time;
                        sample_delta = dpll_task(time_delta);
                        voice_asio_set_local_speed_mode(VOICE_ASIO_SPEED_DOWN);
                    }
                }
            }
            break;
        case VOICE_ASIO_SPEED_DIE_LOW:
            {
                if(voice_asio_get_local_speed_mode() != VOICE_ASIO_SPEED_DIE_LOW){
                    sample_delta_die_level = AUD_DPLL_MIN_SAMP_TIME+0x1000000;
                    voice_asio_set_local_speed_mode(VOICE_ASIO_SPEED_DIE_LOW);
                }
            }
            break;
        default:
            break;
    }
    //dbg("mode %d, %d, %d, %d\n", speed_mode, time_delta, sample_delta, sample_delta_die_level);
    if((sample_delta && (backup_sample_delta !=  sample_delta))||sample_delta_die_level) {
        if(!sample_delta_die_level)
            backup_sample_delta = sample_delta;
        dbg("mode %d, %d, %d, %d\n", speed_mode, time_delta, sample_delta, sample_delta_die_level);
        if(sample_delta_die_level)
            asio_src_change_samplerate_delta(sample_delta_die_level);
        else
            asio_src_change_samplerate_delta(sample_delta);
    }
}

static void data_check_callback(void const *param)
{
    uint16_t bcn_interval = wifi_wh_config_bcn_interval_get();
    uint16_t h2d_air_pkt_size_ms = wifi_wh_config_h2d_air_pkt_size_ms_get();
    normal_level = (playback_start_level_size - 3 * playback_frame_size) + (bcn_interval/ h2d_air_pkt_size_ms) * playback_frame_size;

    PLAYBACK_RING_BUFFER_LOCK();
    uint32_t size = ring_buffer_bytes_used(&playback_ring_buffer);
    PLAYBACK_RING_BUFFER_UNLOCK();
    if (size > normal_level) {
        voice_asio_auto_calibrate_samplerate(VOICE_ASIO_SPEED_UP);
    } else if (size < normal_level) {
        voice_asio_auto_calibrate_samplerate(VOICE_ASIO_SPEED_DOWN);
    }
    data_check_timer_started = false;
    pkt_cnt = 0;
}
#endif

int wifi_wh_playback_data_write(uint8_t *data, uint32_t size)
{
    int rb_st;
    uint32_t bytes_used;
    uint32_t bytes_free;
    uint32_t write_len;
    uint32_t read_len;
    uint32_t drop_len;
    uint8_t playback_st = wifi_wh_playback_st_get();

    if ((playback_st != WIFI_VOICE_SUSPEND) && (AUD_BT_A2DP != app_media_get_playing_mode())) {
        if (!data_check_timer_started) {
            if (0 == rtos_timer_start(data_check_timer, 0, false)) {
                data_check_timer_started = true;
            }
        }
        pkt_cnt ++;
        PLAYBACK_RING_BUFFER_LOCK();
        rb_st = ring_buffer_write(&playback_ring_buffer, (uint8_t *)data, size);
        if (RB_ERR_NONE != rb_st) {
            bytes_free = ring_buffer_bytes_free(&playback_ring_buffer);
            bytes_used = ring_buffer_bytes_used(&playback_ring_buffer);

            if (playback_ring_buffer.size <= size) {
                read_len = bytes_used;
                write_len = playback_ring_buffer.size;
                drop_len = read_len + size - playback_ring_buffer.size;
            } else {
                read_len = size - bytes_free;
                write_len = size;
                drop_len = read_len;
            }

            dbg("PF:%d/%d\n", size, drop_len);
            rb_st = ring_buffer_read(&playback_ring_buffer, NULL, read_len);
            rb_st = ring_buffer_write(&playback_ring_buffer, (uint8_t *)data, write_len);
        }
        bytes_used = ring_buffer_bytes_used(&playback_ring_buffer);
        PLAYBACK_RING_BUFFER_UNLOCK();

        if (playback_st == WIFI_VOICE_IDLE) {
            wifi_wh_playback_st_set(WIFI_VOICE_SWITCHING);

            MediaCommonStruct param = {0};
            param.p.stream_bit = CO_BIT(AUD_STREAM_PLAYBACK);
            app_media_play(AUD_WIFI, MC_OPEN, &param, true);
        }

        if (playback_st == WIFI_VOICE_OPENED) {
            if (bytes_used >= playback_start_level_size) {
                wifi_wh_playback_st_set(WIFI_VOICE_SWITCHING);

                MediaCommonStruct param = {0};
                param.p.stream_bit = CO_BIT(AUD_STREAM_PLAYBACK);
                app_media_play(AUD_WIFI, MC_PLAY, &param, true);
            }
        }
    }

    return 0;
}

int wifi_wh_capture_data_read(uint8_t *buf, uint32_t len)
{
    int ret = 0;
    int rb_st;
    CAPTURE_RING_BUFFER_LOCK();
    rb_st = ring_buffer_read(&capture_ring_buffer, buf, len);
    if (RB_ERR_NONE != rb_st) {
        dbg("CE\n");
        ret = -1;
    }
    CAPTURE_RING_BUFFER_UNLOCK();

    return ret;
}

int wifi_wh_headset(MediaControlType cmd, MediaCommonStruct* param)
{
    int status;
    static uint8_t *playback_buf = NULL;
    static uint8_t *capture_buf = NULL;
    static bool playback_opened = false;
    static bool capture_opened = false;
    static bool playback_started = false;
    static bool capture_started = false;

    bool playback_open = false;
    bool capture_open = false;
    bool playback_start = false;
    bool capture_start = false;
    bool playback_close = false;
    bool capture_close = false;
    bool playback_stop = false;
    bool capture_stop = false;

    dbg("wifi_wh_headset cmd:%d stream_bit:0x%X\n", cmd, param->p.stream_bit);

    if ((cmd == MC_OPEN) || (cmd == MC_PLAY) || (cmd == MC_REPLAY)) {
        if ((cmd == MC_OPEN) || (cmd == MC_PLAY)) {
            if (param->p.stream_bit & CO_BIT(AUD_STREAM_PLAYBACK)) {
                if (playback_opened == false) {
                    playback_open = true;
                }
                if (cmd == MC_PLAY) {
                    if (playback_started == false) {
                        playback_start = true;
                    }
                }
            }
            if (param->p.stream_bit & CO_BIT(AUD_STREAM_CAPTURE)) {
                if (capture_opened == false) {
                    capture_open = true;
                }
                if (cmd == MC_PLAY) {
                    if (capture_started == false) {
                        capture_start = true;
                    }
                }
            }
        } else if (cmd == MC_REPLAY) {
            if (wifi_wh_usb_tx_ongoing_get()) {
                if (capture_opened == false) {
                    capture_open = true;
                }
                if (capture_started == false) {
                    capture_start = true;
                }
            }
            wifi_wh_playback_st_set(WIFI_VOICE_IDLE);
            wifi_wh_capture_st_set(WIFI_VOICE_IDLE);
        }

        if (playback_open == true) {
            // playback
            ASIO_STREAM_CFG_T playback_cfg = {0,};
            playback_cfg.bits = AUD_BITS_16;
            playback_cfg.ch_num = AUD_CH_NUM_2;
            playback_cfg.ch_map = AUD_CH_MAP_CH_0 | AUD_CH_MAP_CH_1;
            playback_cfg.device = audio_config_device_get();
            playback_cfg.samp_rate = AUD_SAMPRATE_48000;
            playback_cfg.src_samp_rate = AUD_SAMPRATE_48000;
            playback_cfg.path = AUD_PATH_TX01;
            playback_cfg.handler = wifi_wh_headset_playback_handler;
            playback_cfg.buf_size = playback_asio_buffer_size;
            playback_cfg.src_en = true;

            if (playback_buf == NULL) {
                playback_buf = (uint8_t *)rtos_malloc(playback_asio_buffer_size);
                if (playback_buf == NULL) {
                    dbg("Err: playback_buf malloc fail\n");
                    return -1;
                }
                dbg("playback_buf %x\n", playback_buf);
            }
            playback_cfg.buf_ptr = (uint8_t *)playback_buf;

            if (0 != asio_stream_open(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK, &playback_cfg)) {
                dbg("ERR: open fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK);
                rtos_free(playback_buf);
                playback_buf = NULL;
                goto exit;
            }
            asio_src_frac_src_init();
            asio_src_set_dpll_param_in_diffmode(AUD_DPLL_NORMAL);

            wifi_wh_playback_st_set(WIFI_VOICE_OPENED);

            playback_opened = true;
        }

        if (capture_open == true) {
            // capture
            ASIO_STREAM_CFG_T capture_cfg;
            memset(&capture_cfg, 0, sizeof(capture_cfg));
            capture_cfg.ch_num = capture_in_ch_num;
            if (capture_in_ch_num == AUD_CH_NUM_2) {
                capture_cfg.ch_map = AUD_CH_MAP_CH_0 | AUD_CH_MAP_CH_1;
            } else {
                capture_cfg.ch_map = AUD_CH_MAP_CH_0;
            }
            capture_cfg.buf_size = capture_asio_buffer_size;
            capture_cfg.samp_rate = headset_mic_samprate;
            capture_cfg.src_samp_rate = AUD_SAMPRATE_48000;
            capture_cfg.src_en = true;
            capture_cfg.bits = AUD_BITS_16;
            capture_cfg.path = AUD_PATH_RX01;
            capture_cfg.device = audio_config_device_get();
            capture_cfg.handler = wifi_wh_headset_capture_handler;

            if (capture_buf == NULL) {
                capture_buf = (uint8_t *)rtos_malloc(capture_cfg.buf_size);
                if(capture_buf == NULL) {
                    dbg("Err: capture_buf(%d) malloc fail\n", capture_cfg.buf_size);
                    return -1;
                }
                dbg("capture_buf %x\n", capture_buf);
            }
            capture_cfg.buf_ptr = capture_buf;
            if (0 != asio_stream_open(AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE, &capture_cfg)) {
                dbg("ERR: open fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE);
                rtos_free(capture_buf);
                capture_buf = NULL;
                goto exit;
            }

            wifi_wh_capture_st_set(WIFI_VOICE_OPENED);

            capture_opened = true;
        }

        if (playback_start == true) {
            asio_stream_preload(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK, true);
            asio_stream_preload(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK, false);
            asio_src_trigger_init((14*26000),0);// 2600000 : 100ms //trigger num 14ms
            if (0 != asio_stream_start(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK)) {
                dbg("ERR: start fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK);
                goto exit;
            }

            wifi_wh_playback_st_set(WIFI_VOICE_STARTED);

            playback_started = true;
        }

        if (capture_start == true) {
            if (0 != asio_stream_start(AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE)) {
                dbg("ERR: start fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE);
                goto exit;
            }

            wifi_wh_capture_st_set(WIFI_VOICE_STARTED);

            capture_started = true;
        }
    } else if ((cmd == MC_STOP) || (cmd == MC_SUSPEND)) {
        if ((param->p.stream_bit & CO_BIT(AUD_STREAM_PLAYBACK)) || (cmd == MC_SUSPEND)) {
            if (playback_started == true) {
                playback_stop = true;
                playback_close = true;
            } else if (playback_opened == true) {
                playback_close = true;
            }
        }

        if ((param->p.stream_bit & CO_BIT(AUD_STREAM_CAPTURE)) || (cmd == MC_SUSPEND)) {
            if (capture_started == true) {
                capture_stop = true;
                capture_close = true;
            } else if (capture_opened == true) {
                capture_close = true;
            }
        }

        if (playback_stop == true) {
            if (cmd == MC_STOP) {
                PLAYBACK_RING_BUFFER_LOCK();
                uint32_t left_bytes = ring_buffer_bytes_used(&playback_ring_buffer);
                PLAYBACK_RING_BUFFER_UNLOCK();

                uint32_t delay_ms = left_bytes / 4 / 48 + 1;
                rtos_task_suspend(delay_ms);
            }

            if (0 != asio_stream_stop(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK)) {
                dbg("ERR: stop fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK);
                goto exit;
            }
            asio_src_frac_src_clear();
            asio_src_clear();
            playback_started = false;
        }

        if (capture_stop == true) {
            if (0 != asio_stream_stop(AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE)) {
                dbg("ERR: stop fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE);
                goto exit;
            }
            capture_started = false;
        }

        if (playback_close == true) {
            if (0 != asio_stream_close(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK)) {
                dbg("ERR: close fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK);
                goto exit;
            }
            if (playback_buf) {
                rtos_free(playback_buf);
                playback_buf = NULL;
            }
            playback_opened = false;
            if (cmd == MC_STOP) {
                if (wifi_wh_playback_st_get() != WIFI_VOICE_SUSPEND) {
                    wifi_wh_playback_st_set(WIFI_VOICE_IDLE);
                }
                PLAYBACK_RING_BUFFER_LOCK();
                ring_buffer_reset(&playback_ring_buffer);
                PLAYBACK_RING_BUFFER_UNLOCK();
            }
        }

        if (capture_close == true) {
            if (0 != asio_stream_close(AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE)) {
                dbg("ERR: close fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE);
                goto exit;
            }
            if (capture_buf) {
                rtos_free(capture_buf);
                capture_buf = NULL;
            }
            capture_opened = false;
            if (cmd == MC_STOP) {
                if (wifi_wh_capture_st_get() != WIFI_VOICE_SUSPEND) {
                    wifi_wh_capture_st_set(WIFI_VOICE_IDLE);
                }
                CAPTURE_RING_BUFFER_LOCK();
                ring_buffer_reset(&capture_ring_buffer);
                CAPTURE_RING_BUFFER_UNLOCK();
            }
        }

        if (cmd == MC_SUSPEND) {
            wifi_wh_playback_st_set(WIFI_VOICE_SUSPEND);
            wifi_wh_capture_st_set(WIFI_VOICE_SUSPEND);
            PLAYBACK_RING_BUFFER_LOCK();
            ring_buffer_reset(&playback_ring_buffer);
            PLAYBACK_RING_BUFFER_UNLOCK();
            CAPTURE_RING_BUFFER_LOCK();
            ring_buffer_reset(&capture_ring_buffer);
            CAPTURE_RING_BUFFER_UNLOCK();
            GLOBAL_INT_DISABLE();
            h2d_ready_pkt_num = 0;
            GLOBAL_INT_RESTORE();
        }

        if ((playback_opened == false) && (playback_started == false) && (capture_opened == false) && (capture_started == false)) {
            app_audio_send_audio_end();
        }
    }

exit:
    status = (playback_opened << 0) | (playback_started << 1) | (capture_opened << 2) | (capture_started << 3);

    return status;
}


static void headset_data_handler(uint8_t *data, uint32_t size, uint8_t index)
{
    //dbg("data@%p(%d): %02X %02X %02X %02X\n",data,size,data[0],data[1],data[2],data[3]);
    wifi_wh_playback_data_write(data, size);

    wifi_voice_data_stop_check_timer_restart(0, false);
}

static void headset_cmd_handler(uint8_t *data, uint32_t size, uint8_t index)
{
    dbg("cmd received %d:%X\n", index, data[0]);

    if (data[0] == VOICE_CMD_START_CAPTURE) {
        dbg("wifi_wh_start_capture\n");

        wifi_wh_usb_tx_ongoing_set(true);

        MediaCommonStruct param = {0};
        param.p.stream_bit |= CO_BIT(AUD_STREAM_CAPTURE);
        app_media_play(AUD_WIFI, MC_PLAY, &param, true);
    }

    if (data[0] == VOICE_CMD_STOP_CAPTURE) {
        dbg("wifi_wh_stop_capture\n");

        wifi_wh_usb_tx_ongoing_set(false);

        MediaCommonStruct param = {0};
        param.p.stream_bit |= CO_BIT(AUD_STREAM_CAPTURE);
        app_media_play(AUD_WIFI, MC_STOP, &param, true);
    }

    if (data[0] == VOICE_CMD_STOP_PLAYBACK) {
        dbg("wifi_wh_stop_playback\n");

        MediaCommonStruct param = {0};
        param.p.stream_bit |= CO_BIT(AUD_STREAM_PLAYBACK);
        app_media_play(AUD_WIFI, MC_STOP, &param, true);
    }
}

static void wifi_wh_get_mac_status(wifi_mac_status_e st)
{
    if (WIFI_MAC_STATUS_DISCONNECTED == st) {
        wifi_voice_msg_queue_write(WIFI_MAC_DISCONNECTED, 10, false);
    } else if (WIFI_MAC_STATUS_IP_OBTAINED == st) {
        wifi_voice_msg_queue_write(WIFI_MAC_CONNECTED, 10, false);
    }
}

static void co_wifi_pairing_to_timer(void *cb_param)
{
    dbg("co_wifi_pairing_to_timer\n");
    pmic_chip_shutdown();
}

static RTOS_TASK_FCT(headset_task)
{
    struct wifi_voice_settings settings;
    uint8_t *send_buf  = NULL;
    char ssid[32] = {0};
    char pw[64]   = {0};

    do {
        uint32_t msg;
        set_mac_address(wifi_wh_config_headset_mac_addr_get());

        //enter paring mode.
        if (headset_led_handler) {
            headset_led_handler(WIFI_VOICE_STA_PAIRING);
        }

        if (co_wifi_pairing_timer == NULL) {
            co_timer_start(&co_wifi_pairing_timer, wifi_pairing_timeout_ms, NULL, co_wifi_pairing_to_timer, 0);
        }
        wlan_sta_auto_pairing((char *)ssid, (char *)pw, 3);

        if (wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, -1)) {
            dbg("ERR: STA connect fail\n");
            break;
        }

        if (co_wifi_pairing_timer) {
            co_timer_stop(co_wifi_pairing_timer);
            co_wifi_pairing_timer = NULL;
        }
        if (headset_led_handler) {
            headset_led_handler(WIFI_VOICE_STA_CONNECTED);
        }

        if (wifi_wh_config_headset_pwr_mode_get() > 0) {
            user_sleep_allow(0);
            sleep_level_set(wifi_wh_config_headset_pwr_mode_get());
        }

        dbg("STA connected, server mode\n");
        fhost_get_mac_status_register(wifi_wh_get_mac_status);

        wifi_voice_data_handler_register(headset_data_handler);
        wifi_voice_cmd_handler_register(headset_cmd_handler);

        memset(&settings, 0, sizeof(struct wifi_voice_settings));
        settings.role = WIFI_VOICE_ROLE_HEADSET;
        settings.is_server = true;
        settings.port    = WIFI_VOICE_DATA_PORT;
        settings.pl_size = h2d_air_pkt_size;

        uint32_t ip_addr = 0;
        uint32_t gateway_addr = 0;
        net_if_get_ip(net_if_find_from_wifi_idx(0), &ip_addr, NULL, &gateway_addr);
        settings.stream_addr = gateway_addr;

        wifi_voice_task_init(&settings);
        wifi_voice_stream_start(&settings);

        send_buf = rtos_malloc(h2d_air_pkt_size);
        if (!send_buf) {
            dbg("ERR: send buf malloc fail\n");
            break;
        }
        dbg("send_buf %x\n", send_buf);

        while (1) {
            wifi_voice_msg_queue_read(&msg, -1, false);
            switch (msg) {
            case VOICE_DATA_READY: {
                uint32_t ready_data_len;
                ready_data_len = h2d_air_pkt_size;
                uint16_t bcn_interval = wifi_wh_config_bcn_interval_get();
                uint16_t h2d_air_pkt_size_ms = wifi_wh_config_h2d_air_pkt_size_ms_get();
                fhost_tx_cntrl_by_timer((bcn_interval / h2d_air_pkt_size_ms * h2d_air_pkt_size_ms), 0);//(bcn_interval / h2d_air_pkt_size_ms)
                if (0 == wifi_wh_capture_data_read(send_buf, ready_data_len)) {
                    settings.data_addr = (uint8_t *)send_buf;
                    settings.data_size = ready_data_len;
                    server_send_voice_packets(&settings, &settings.to);
                }
                GLOBAL_INT_DISABLE();
                if (h2d_ready_pkt_num > 0) {
                    h2d_ready_pkt_num--;
                }
                GLOBAL_INT_RESTORE();
                break;
            }
            #if 0
            case VOICE_STOP_CAPTURE: {
                if (WIFI_VOICE_STARTED == capture_status) {
                    dbg("asio_stream_stop capture\n");
                    MediaCommonStruct param = {0};
                    param.p.stream_bit |= CO_BIT(AUD_STREAM_CAPTURE);
                    app_media_play(AUD_WIFI, MC_STOP, &param, true);
                    // clear data
                    CAPTURE_RING_BUFFER_LOCK();
                    voice_unsent_capture_data_len = ring_buffer_bytes_used(&capture_ring_buffer);
                    voice_unsent_capture_data_len %= h2d_air_pkt_size;
                    if (voice_unsent_capture_data_len) {
                        uint16_t msg = VOICE_DATA_READY;
                        if (rtos_queue_write(voice_msg_queue, &msg, 10, true)) {
                            dbg("rtos_queue_write fail\n");
                        }
                        //voice_capture_temp_cnt = 0;
                    }
                    CAPTURE_RING_BUFFER_UNLOCK();
                }
                break
            }
            #endif
            case VOICE_SOCK_DISCONNECTED: {
                MediaCommonStruct param = {0};
                param.p.stream_bit |= CO_BIT(AUD_STREAM_PLAYBACK);
                app_media_play(AUD_WIFI, MC_STOP, &param, true);
                break;
            }
            case WIFI_MAC_DISCONNECTED: {
                dbg("WIFI MAC DISCONNECTED\n");
                MediaCommonStruct param = {0};
                param.p.stream_bit |= CO_BIT(AUD_STREAM_CAPTURE);
                param.p.stream_bit |= CO_BIT(AUD_STREAM_PLAYBACK);
                app_media_play(AUD_WIFI, MC_STOP, &param, true);
                wifi_voice_stream_stop();
                if (headset_led_handler) {
                    headset_led_handler(WIFI_VOICE_STA_DISCONNECTED);
                }
                if (co_wifi_pairing_timer == NULL){
                    co_timer_start(&co_wifi_pairing_timer, wifi_pairing_timeout_ms, NULL, co_wifi_pairing_to_timer, 0);
                }
                fhost_stop_tx_cntrl_by_timer();

                if (disconnected_by_user) {
                    wlan_disconnect_sta(0);
                    rtos_task_suspend(1000);
                    disconnected_by_user = 0;
                    wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, -1);
                }
                break;
            }
            case WIFI_MAC_CONNECTED: {
                dbg("WIFI MAC CONNECTED\n");
                if (wlan_connected) {
                    if (co_wifi_pairing_timer) {
                        co_timer_stop(co_wifi_pairing_timer);
                        co_wifi_pairing_timer = NULL;
                    }
                    wifi_voice_stream_start(&settings);
                    if (headset_led_handler) {
                        headset_led_handler(WIFI_VOICE_STA_CONNECTED);
                    }
                }
                break;
            }
            default: {
                break;
            }
            }
        }
    } while (0);

    if (send_buf) {
        rtos_free(send_buf);
        send_buf = NULL;
    }
    wifi_voice_task_deinit(&settings);
    wifi_wh_headset_deinit();
    rtos_task_delete(NULL);
}

/*
 * Dongle USB RX PKT--->Dongle USB RX ring buffer--->H2D AIR PKT--->Headset playback ring buffer--->Headset playback asio buffer
 * Headset capture asio buffer--->Headset capture ring buffer--->D2H AIR PKT--->Dongle USB TX ring buffer--->Dongle USB TX PKT
 */
int wifi_wh_headset_init(void)
{
    wifi_pairing_timeout_ms = wifi_wh_config_pariring_timeout_get();
    h2d_air_pkt_size = wifi_wh_config_h2d_air_pkt_size_get();
    playback_frame_size = wifi_wh_config_headset_playback_frame_size_get();

    headset_mic_samprate = wifi_wh_config_headset_mic_samprate_get();
    capture_frame_size = wifi_wh_config_headset_capture_frame_size_get();
    capture_in_ch_num = wifi_wh_config_headset_capture_in_ch_num_get();
    capture_out_ch_num = wifi_wh_config_headset_capture_out_ch_num_get();

    playback_asio_buffer_size = 2 * playback_frame_size;
    playback_ring_buffer_size = wifi_wh_config_headset_playback_ring_buffer_size_get();
    playback_start_level_size = wifi_wh_config_headset_playback_start_level_size_get();
    capture_asio_buffer_size = 2 * capture_frame_size;
    capture_ring_buffer_size = wifi_wh_config_headset_capture_ring_buffer_size_get();

    if (0 != rtos_mutex_recursive_create(&playback_ring_buffer_mutex)) {
        dbg("ERR: playback_ring_buffer_mutex create fail\n");
        return -1;
    }

    if (0 != rtos_mutex_recursive_create(&capture_ring_buffer_mutex)) {
        dbg("ERR: capture_ring_buffer_mutex create fail\n");
        return -1;
    }

    data_check_timer = rtos_timer_create("data_check_timer", pdMS_TO_TICKS(4), pdFALSE, NULL,
                                              (TimerCallbackFunction_t)data_check_callback);
    if (!data_check_timer) {
        dbg("ERR: data_check_timer create fail\n");
        return -1;
    }

    playback_ring_buffer_storage = (uint8_t *)rtos_malloc(playback_ring_buffer_size);
    if (!playback_ring_buffer_storage) {
        dbg("ERR: playback_ring_buffer_storage malloc fail, %d\n", playback_ring_buffer_size);
        return -1;
    }
    dbg("playback_ring_buffer_storage %x\n", playback_ring_buffer_storage);
    ring_buffer_init(&playback_ring_buffer, playback_ring_buffer_storage, playback_ring_buffer_size);

    capture_ring_buffer_storage = rtos_malloc(capture_ring_buffer_size);
    if (!capture_ring_buffer_storage) {
        dbg("ERR: capture_ring_buffer_storage malloc fail, %d\n", capture_ring_buffer_size);
        return -1;
    }
    dbg("capture_ring_buffer_storage %x\n", capture_ring_buffer_storage);
    ring_buffer_init(&capture_ring_buffer, capture_ring_buffer_storage, capture_ring_buffer_size);

    if (rtos_task_create(headset_task, "headset task", APPLICATION_TASK,
                         TASK_STACK_SIZE_WIFI_VOICE, NULL, TASK_PRIORITY_WIFI_VOICE, &headset_task_handle)) {

        dbg("ERR: headset task create fail\n");
        return -1;
    }

    return 0;
}

int wifi_wh_headset_deinit(void)
{
    if (playback_ring_buffer_mutex) {
        rtos_mutex_delete(playback_ring_buffer_mutex);
        playback_ring_buffer_mutex = NULL;
    }

    if (capture_ring_buffer_mutex) {
        rtos_mutex_delete(capture_ring_buffer_mutex);
        capture_ring_buffer_mutex = NULL;
    }

    ring_buffer_deinit(&playback_ring_buffer);
    if (playback_ring_buffer_storage) {
        rtos_free(playback_ring_buffer_storage);
        playback_ring_buffer_storage = NULL;
    }

    ring_buffer_deinit(&capture_ring_buffer);
    if (capture_ring_buffer_storage) {
        rtos_free(capture_ring_buffer_storage);
        capture_ring_buffer_storage = NULL;
    }

    if (data_check_timer) {
        rtos_timer_delete(data_check_timer, 0);
        data_check_timer = NULL;
    }

    return 0;
}
#endif
