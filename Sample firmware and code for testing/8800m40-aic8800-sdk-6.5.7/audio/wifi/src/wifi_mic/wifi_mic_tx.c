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
#include "wifi_voice_config.h"
#include "wifi_mic_config.h"
#include "ring_buffer.h"
#include "asio.h"
#include "asio_src.h"
#include "audio_types.h"
#include "app_media.h"
#include "app_media_mgr.h"
#include "audio_config.h"
#include "wifi_mic_tx.h"
#include "co_main.h"
#include "pmic_api.h"

typedef enum {
    MIC_TX_BUFFER_STATUS_STOP = 0,
    MIC_TX_BUFFER_STATUS_START,
    MIC_TX_BUFFER_STATUS_RESTART,
    MIC_TX_BUFFER_STATUS_REACH_THRESHOLD,
    MIC_TX_BUFFER_STATUS_NUM,
} MIC_TX_BUFFER_STATUS;

static rtos_task_handle mic_tx_task_handle = NULL;

static uint32_t mic_samprate = 0;
static uint16_t tx2rx_air_pkt_size_ms = 0;
static uint16_t tx2rx_air_pkt_size = 0;
static uint16_t tx2rx_ready_pkt_num = 0;

static uint16_t capture_frame_size_ms = 0;
static uint16_t capture_frame_size = 0;
static uint32_t capture_ring_buffer_size = 0;
static uint16_t capture_asio_buffer_size = 0;
static uint8_t *capture_ring_buffer_storage = NULL;
static ring_buffer_t capture_ring_buffer;
static uint8_t capture_ring_buffer_status = 0;
static uint8_t mic_tx_capture_in_ch_num = 0;
static uint8_t mic_tx_capture_out_ch_num = 0;
static rtos_mutex capture_ring_buffer_mutex = NULL;

static uint16_t playback_frame_size_ms = 0;
static uint16_t playback_frame_size = 0;
static uint32_t playback_ring_buffer_size = 0;
static uint16_t playback_asio_buffer_size = 0;
static uint8_t *playback_ring_buffer_storage = NULL;
static ring_buffer_t playback_ring_buffer;
static uint8_t playback_ring_buffer_status = 0;
static uint8_t mic_tx_playback_ch_num = 0;
static rtos_mutex playback_ring_buffer_mutex = NULL;

static wifi_voice_led_handler_t mic_tx_led_handler = NULL;

static uint32_t wifi_pairing_timeout_ms = 0;
static co_timer *co_wifi_pairing_timer = NULL;
char ssid[32] = {0};
char pw[64]   = {0};

#define PLAYBACK_RING_BUFFER_LOCK()      rtos_mutex_recursive_lock(playback_ring_buffer_mutex)
#define PLAYBACK_RING_BUFFER_UNLOCK()    rtos_mutex_recursive_unlock(playback_ring_buffer_mutex)

#define CAPTURE_RING_BUFFER_LOCK()       rtos_mutex_recursive_lock(capture_ring_buffer_mutex)
#define CAPTURE_RING_BUFFER_UNLOCK()     rtos_mutex_recursive_unlock(capture_ring_buffer_mutex)

void wifi_mic_tx_led_handler_register(wifi_voice_led_handler_t handler)
{
    mic_tx_led_handler = handler;
}

int wifi_mic_tx_playback_ring_buffer_lock(void)
{
    return PLAYBACK_RING_BUFFER_LOCK();
}

int wifi_mic_tx_playback_ring_buffer_unlock(void)
{
    return PLAYBACK_RING_BUFFER_UNLOCK();
}

int wifi_mic_tx_capture_ring_buffer_lock(void)
{
    return CAPTURE_RING_BUFFER_LOCK();
}

int wifi_mic_tx_capture_ring_buffer_unlock(void)
{
    return CAPTURE_RING_BUFFER_UNLOCK();
}

ring_buffer_t *wifi_mic_tx_playback_ring_buffer_get(void)
{
    return &playback_ring_buffer;
}

ring_buffer_t *wifi_mic_tx_capture_ring_buffer_get(void)
{
    return &capture_ring_buffer;
}

void wifi_mic_tx_capture_data_ready(int timeout, bool isr)
{
    uint32_t bytes_used;
    uint32_t pkt_num;

    CAPTURE_RING_BUFFER_LOCK();
    bytes_used = ring_buffer_bytes_used(&capture_ring_buffer);
    CAPTURE_RING_BUFFER_UNLOCK();

    pkt_num = bytes_used / tx2rx_air_pkt_size;

    if (pkt_num > tx2rx_ready_pkt_num) {
        GLOBAL_INT_DISABLE();
        tx2rx_ready_pkt_num++;
        GLOBAL_INT_RESTORE();
        wifi_voice_data_ready(timeout, false);
    }
}

static void wifi_mic_tx_playback_ring_buffer_reset(void)
{
    PLAYBACK_RING_BUFFER_LOCK();
    ring_buffer_reset(&playback_ring_buffer);
    playback_ring_buffer_status = MIC_TX_BUFFER_STATUS_START;
    PLAYBACK_RING_BUFFER_UNLOCK();
}

static void wifi_mic_tx_capture_ring_buffer_reset(void)
{
    CAPTURE_RING_BUFFER_LOCK();
    ring_buffer_reset(&capture_ring_buffer);
    capture_ring_buffer_status = MIC_TX_BUFFER_STATUS_START;
    CAPTURE_RING_BUFFER_UNLOCK();
}

int wifi_mic_tx_playback(MediaControlType cmd, MediaCommonStruct* param)
{
    int status;
    static uint8_t *playback_buf = NULL;
    static bool playback_opened = false;
    static bool playback_started = false;

    bool playback_open = false;
    bool playback_start = false;
    bool playback_close = false;
    bool playback_stop = false;

    if ((cmd == MC_OPEN) || (cmd == MC_PLAY)) {
        if (playback_opened == false) {
            playback_open = true;
        }
        if (cmd == MC_PLAY) {
            if (playback_started == false) {
                playback_start = true;
            }
        }

        if (playback_open == true) {
            // playback
            ASIO_STREAM_CFG_T playback_cfg = {0,};
            playback_cfg.bits = AUD_BITS_16;
            playback_cfg.ch_num = mic_tx_playback_ch_num;
            if (mic_tx_playback_ch_num == AUD_CH_NUM_2) {
                playback_cfg.ch_map = AUD_CH_MAP_CH_0 | AUD_CH_MAP_CH_1;
            } else {
                playback_cfg.ch_map = AUD_CH_MAP_CH_0;
            }
            playback_cfg.device = audio_config_device_get();
            playback_cfg.samp_rate = mic_samprate;
            playback_cfg.src_samp_rate = AUD_SAMPRATE_48000;
            playback_cfg.path = AUD_PATH_TX01;
            playback_cfg.handler = wifi_mic_tx_playback_handler;
            playback_cfg.buf_size = playback_asio_buffer_size;
            playback_cfg.src_en = true;

            if (playback_buf == NULL) {
                playback_buf = (uint8_t *)rtos_malloc(playback_asio_buffer_size);
                if (playback_buf == NULL) {
                    dbg("Err: playback_buf malloc fail!\r\n");
                    return -1;
                }
                dbg("### playback_buf 0x%x\r\n", playback_buf);
            }
            playback_cfg.buf_ptr = (uint8_t *)playback_buf;

            if (0 != asio_stream_open(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK, &playback_cfg)) {
                dbg("ERR: open fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK);
                rtos_free(playback_buf);
                playback_buf = NULL;
                goto exit;
            }

            playback_opened = true;
        }

        if (playback_start == true) {
            asio_stream_preload(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK, true);
            asio_stream_preload(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK, false);
            if (0 != asio_stream_start(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK)) {
                dbg("ERR: start fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK);
                goto exit;
            }

            playback_started = true;
        }
    } else if (cmd == MC_STOP) {
        if (playback_started == true) {
            playback_stop = true;
            playback_close = true;
        } else if (playback_opened == true) {
            playback_close = true;
        }

        if (playback_stop == true) {
            if (0 != asio_stream_stop(AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK)) {
                dbg("ERR: stop fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_PLAYBACK);
                goto exit;
            }
            playback_started = false;
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

            PLAYBACK_RING_BUFFER_LOCK();
            ring_buffer_reset(&playback_ring_buffer);
            PLAYBACK_RING_BUFFER_UNLOCK();
        }
    }

exit:
    status = (playback_opened << 0) | (playback_started << 1);

    return status;
}

int wifi_mic_tx_capture(MediaControlType cmd, MediaCommonStruct* param)
{
    int status;
    static uint8_t *capture_buf = NULL;
    static bool capture_opened = false;
    static bool capture_started = false;

    bool capture_open = false;
    bool capture_start = false;
    bool capture_close = false;
    bool capture_stop = false;

    if ((cmd == MC_OPEN) || (cmd == MC_PLAY)) {
        if (capture_opened == false) {
            capture_open = true;
        }
        if (cmd == MC_PLAY) {
            if (capture_started == false) {
                capture_start = true;
            }
        }

        if (capture_open == true) {
            // capture
            ASIO_STREAM_CFG_T capture_cfg = {0,};
            capture_cfg.bits = AUD_BITS_16;
            capture_cfg.ch_num = mic_tx_capture_in_ch_num;
            if (mic_tx_capture_in_ch_num == AUD_CH_NUM_2) {
                capture_cfg.ch_map = AUD_CH_MAP_CH_0 | AUD_CH_MAP_CH_1;
            } else {
                capture_cfg.ch_map = AUD_CH_MAP_CH_0;
            }
            capture_cfg.device = audio_config_device_get();
            capture_cfg.samp_rate = mic_samprate;
            capture_cfg.src_samp_rate = AUD_SAMPRATE_48000;
            capture_cfg.path = AUD_PATH_RX01;
            capture_cfg.handler = wifi_mic_tx_capture_handler;
            capture_cfg.buf_size = capture_asio_buffer_size;
            capture_cfg.src_en = true;

            if (capture_buf == NULL) {
                capture_buf = (uint8_t *)rtos_malloc(capture_asio_buffer_size);
                if (capture_buf == NULL) {
                    dbg("Err: capture_buf malloc fail!\r\n");
                    return -1;
                }
                dbg("### capture_buf 0x%x\r\n", capture_buf);
            }
            capture_cfg.buf_ptr = (uint8_t *)capture_buf;

            if (0 != asio_stream_open(AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE, &capture_cfg)) {
                dbg("ERR: open fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE);
                rtos_free(capture_buf);
                capture_buf = NULL;
                goto exit;
            }

            capture_opened = true;
        }

        if (capture_start == true) {
            if (0 != asio_stream_start(AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE)) {
                dbg("ERR: start fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE);
                goto exit;
            }

            capture_started = true;
        }
    } else if (cmd == MC_STOP) {
        if (capture_started == true) {
            capture_stop = true;
            capture_close = true;
        } else if (capture_opened == true) {
            capture_close = true;
        }

        if (capture_stop == true) {
            if (0 != asio_stream_stop(AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE)) {
                dbg("ERR: stop fail g:%d s:%d\n", AUD_STREAM_GROUP_0, AUD_STREAM_CAPTURE);
                goto exit;
            }
            capture_started = false;
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

            CAPTURE_RING_BUFFER_LOCK();
            ring_buffer_reset(&capture_ring_buffer);
            CAPTURE_RING_BUFFER_UNLOCK();
        }
    }

exit:
    status = (capture_opened << 0) | (capture_started << 1);

    return status;
}

static int wifi_mic_tx_playback_open(void)
{
    int ret;
    MediaControlType cmd;
    MediaCommonStruct param;

    cmd = MC_OPEN;

    ret = wifi_mic_tx_playback(cmd, &param);

    return ret;
}

static int wifi_mic_tx_playback_start(void)
{
    int ret;
    MediaControlType cmd;
    MediaCommonStruct param;

    cmd = MC_PLAY;

    ret = wifi_mic_tx_playback(cmd, &param);

    return ret;
}

static int wifi_mic_tx_playback_stop(void)
{
    int ret;
    MediaControlType cmd;
    MediaCommonStruct param;

    cmd = MC_STOP;

    ret = wifi_mic_tx_playback(cmd, &param);

    return ret;
}

static int wifi_mic_tx_capture_open(void)
{
    int ret;
    MediaControlType cmd;
    MediaCommonStruct param;

    cmd = MC_OPEN;

    ret = wifi_mic_tx_capture(cmd, &param);

    return ret;
}

static int wifi_mic_tx_capture_start(void)
{
    int ret;
    MediaControlType cmd;
    MediaCommonStruct param;

    cmd = MC_PLAY;

    ret = wifi_mic_tx_capture(cmd, &param);

    return ret;
}

static int wifi_mic_tx_capture_stop(void)
{
    int ret;
    MediaControlType cmd;
    MediaCommonStruct param;

    cmd = MC_STOP;

    ret = wifi_mic_tx_capture(cmd, &param);

    return ret;
}


int wifi_mic_tx_playback_data_write(uint8_t *buf, uint32_t len)
{
    int ret = 0;
    int rb_ret;
    uint32_t bytes_used;

    PLAYBACK_RING_BUFFER_LOCK();
    rb_ret = ring_buffer_write(&playback_ring_buffer, buf, len);
    if (RB_ERR_NONE != rb_ret) {
        dbg("TPF\n");
    }
    PLAYBACK_RING_BUFFER_UNLOCK();

    if (playback_ring_buffer_status == MIC_TX_BUFFER_STATUS_START) {
        PLAYBACK_RING_BUFFER_LOCK();
        bytes_used = ring_buffer_bytes_used(&playback_ring_buffer);
        PLAYBACK_RING_BUFFER_UNLOCK();

        // start playback after storing at least 2 playback frames
        if ((bytes_used / mic_tx_capture_out_ch_num) >= (2 * playback_frame_size / mic_tx_playback_ch_num)) {
            playback_ring_buffer_status = MIC_TX_BUFFER_STATUS_REACH_THRESHOLD;
            //wifi_mic_tx_playback_start();
            wifi_voice_start_playback(10, 0);
        }
    }

    return ret;
}

static int mic_tx_capture_data_read(uint8_t *buf, uint32_t len)
{
    int ret = 0;
    int rb_st;
    CAPTURE_RING_BUFFER_LOCK();
    rb_st = ring_buffer_read(&capture_ring_buffer, buf, len);
    if (RB_ERR_NONE != rb_st) {
        dbg("TCE\n");
        ret = -1;
    }
    CAPTURE_RING_BUFFER_UNLOCK();

    return ret;
}

static void mic_tx_cmd_handler(uint8_t *data, uint32_t size, uint8_t index)
{
    dbg("cmd received %d:%X\n", index, data[0]);
}

static void wifi_mic_get_mac_status(wifi_mac_status_e st)
{
    if (WIFI_MAC_STATUS_DISCONNECTED == st) {
        wifi_voice_mac_disconnected(10, false);
    } else if (WIFI_MAC_STATUS_IP_OBTAINED == st) {
        wifi_voice_mac_connected(10, false);
    }
}

static void co_wifi_pairing_to_timer(void *cb_param)
{
    dbg("co_wifi_pairing_to_timer\r\n");
    pmic_chip_shutdown();
}

static bool mic_tx_force_pairing = false;
void wifi_mic_tx_force_pairing(void)
{
    //enter paring mode.
    if (mic_tx_led_handler) {
        mic_tx_led_handler(WIFI_VOICE_STA_PAIRING);
    }

    mic_tx_force_pairing = true;
    wlan_disconnect_sta(0);
    rtos_task_suspend(1000);

    if (co_wifi_pairing_timer == NULL) {
        co_timer_start(&co_wifi_pairing_timer, wifi_pairing_timeout_ms, NULL, co_wifi_pairing_to_timer, 0);
    }

    wlan_sta_auto_pairing((char *)ssid, (char *)pw, 3);
    disconnected_by_user = 0;
    int ret = wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, -1);
    if (!ret) {
        wifi_voice_mac_connected(10, false);

        if (co_wifi_pairing_timer) {
            co_timer_stop(co_wifi_pairing_timer);
            co_wifi_pairing_timer = NULL;
        }

        if (mic_tx_led_handler) {
            mic_tx_led_handler(WIFI_VOICE_STA_CONNECTED);
        }
    } else {
        disconnected_by_user = 1;
        wifi_voice_mac_disconnected(10, false);
    }
    mic_tx_force_pairing = false;
}

static RTOS_TASK_FCT(mic_tx_task)
{
    struct wifi_voice_settings settings;
    uint8_t *send_buf  = NULL;

    dbg("mic_tx_task\n");
    do {
        uint32_t msg;
        set_mac_address(wifi_mic_config_mic_tx_mac_addr_get());

        //enter paring mode.
        if (mic_tx_led_handler) {
            mic_tx_led_handler(WIFI_VOICE_STA_PAIRING);
        }

        if (co_wifi_pairing_timer == NULL) {
            co_timer_start(&co_wifi_pairing_timer, wifi_pairing_timeout_ms, NULL, co_wifi_pairing_to_timer, 0);
        }
        wlan_sta_auto_pairing((char *)ssid, (char *)pw, 3);

        if (wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, -1)) {
            dbg("STA connect fail\r\n");
            break;
        }

        if (co_wifi_pairing_timer) {
            co_timer_stop(co_wifi_pairing_timer);
            co_wifi_pairing_timer = NULL;
        }
        if (mic_tx_led_handler) {
            mic_tx_led_handler(WIFI_VOICE_STA_CONNECTED);
        }

        if (wifi_mic_config_mic_tx_pwr_mode_get() > 0) {
            user_sleep_allow(0);
            sleep_level_set(wifi_mic_config_mic_tx_pwr_mode_get());
        }

        dbg("STA connected, server mode\r\n");
        fhost_get_mac_status_register(wifi_mic_get_mac_status);

        wifi_voice_cmd_handler_register(mic_tx_cmd_handler);

        memset(&settings, 0, sizeof(struct wifi_voice_settings));
        settings.role = WIFI_VOICE_ROLE_HEADSET;
        settings.is_server = true;
        settings.port    = WIFI_VOICE_DATA_PORT;
        settings.pl_size = tx2rx_air_pkt_size;
        settings.pkt_ms  = tx2rx_air_pkt_size_ms;
        settings.bcn_int = wifi_mic_config_bcn_interval_get();

        uint32_t ip_addr = 0;
        uint32_t gateway_addr = 0;
        net_if_get_ip(net_if_find_from_wifi_idx(0), &ip_addr, NULL, &gateway_addr);
        settings.stream_addr = gateway_addr;

        wifi_voice_task_init(&settings);
        wifi_voice_stream_start(&settings);
        wifi_mic_tx_capture_ring_buffer_reset();
        wifi_mic_tx_playback_ring_buffer_reset();
        wifi_mic_tx_capture_open();
        wifi_mic_tx_playback_open();
        wifi_mic_tx_capture_start();

        send_buf = rtos_malloc(tx2rx_air_pkt_size);
        if (!send_buf) {
            dbg("send buf malloc fail\r\n");
            break;
        }
        dbg("### send_buf %x\r\n", send_buf);

        while (1) {
            wifi_voice_msg_queue_read(&msg, -1, false);
            switch (msg) {
            case VOICE_DATA_READY: {
                uint32_t ready_data_len;
                ready_data_len = tx2rx_air_pkt_size;
                if (0 == mic_tx_capture_data_read(send_buf, ready_data_len)) {
                    settings.data_addr = (uint8_t *)send_buf;
                    settings.data_size = ready_data_len;
                    server_send_voice_packets(&settings, &settings.to);
                }
                GLOBAL_INT_DISABLE();
                if (tx2rx_ready_pkt_num > 0) {
                    tx2rx_ready_pkt_num--;
                }
                GLOBAL_INT_RESTORE();
                break;
            }
            case VOICE_START_PLAYBACK: {
                wifi_mic_tx_playback_start();
                break;
            }
            case WIFI_MAC_DISCONNECTED: {
                dbg("WIFI MAC DISCONNECTED \r\n");
                wifi_mic_tx_capture_stop();
                wifi_mic_tx_playback_stop();
                wifi_mic_tx_capture_ring_buffer_reset();
                wifi_mic_tx_playback_ring_buffer_reset();
                wifi_voice_stream_stop();
                if (mic_tx_led_handler) {
                    mic_tx_led_handler(WIFI_VOICE_STA_DISCONNECTED);
                }

                if (disconnected_by_user && !mic_tx_force_pairing) {
                    wlan_disconnect_sta(0);
                    rtos_task_suspend(1000);
                    disconnected_by_user = 0;
                    wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, -1);
                }
                break;
            }
            case WIFI_MAC_CONNECTED: {
                dbg("WIFI MAC CONNECTED \r\n");
                if (wlan_connected) {
                    wifi_voice_stream_start(&settings);
                    wifi_mic_tx_capture_ring_buffer_reset();
                    wifi_mic_tx_playback_ring_buffer_reset();
                    wifi_mic_tx_capture_open();
                    wifi_mic_tx_playback_open();
                    wifi_mic_tx_capture_start();
                    if (mic_tx_led_handler) {
                        mic_tx_led_handler(WIFI_VOICE_STA_CONNECTED);
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
    wifi_mic_tx_deinit();
    rtos_task_delete(NULL);
}

/*
 * Dongle USB RX PKT--->Dongle USB RX ring buffer--->H2D AIR PKT--->Headset playback ring buffer--->Headset playback asio buffer
 * Headset capture asio buffer--->Headset capture ring buffer--->D2H AIR PKT--->Dongle USB TX ring buffer--->Dongle USB TX PKT
 */
int wifi_mic_tx_init(void)
{
    wifi_pairing_timeout_ms = wifi_mic_config_pariring_timeout_get();
    mic_samprate = wifi_mic_config_samprate_get();
    tx2rx_air_pkt_size_ms = wifi_mic_config_tx2rx_air_pkt_size_ms_get();
    tx2rx_air_pkt_size = wifi_mic_config_tx2rx_air_pkt_size_get();
    tx2rx_ready_pkt_num = 0;

    playback_frame_size_ms = wifi_mic_config_mic_tx_playback_frame_size_ms_get();
    mic_tx_playback_ch_num = wifi_mic_config_mic_tx_playback_ch_num_get();
    playback_ring_buffer_size = wifi_mic_config_mic_tx_playback_ring_buffer_size_get();
    playback_ring_buffer_status = MIC_TX_BUFFER_STATUS_START;
    //playback_frame_size = playback_frame_size_ms * mic_samprate / 1000 * mic_tx_playback_ch_num * sizeof(int16_t);
    playback_frame_size = wifi_mic_config_mic_tx_playback_frame_size_get();
    playback_asio_buffer_size = playback_frame_size * 2;

    capture_frame_size_ms = wifi_mic_config_mic_tx_capture_frame_size_ms_get();
    mic_tx_capture_in_ch_num = wifi_mic_config_mic_tx_capture_in_ch_num_get();
    mic_tx_capture_out_ch_num = wifi_mic_config_mic_tx_capture_out_ch_num_get();
    capture_ring_buffer_size = wifi_mic_config_mic_tx_capture_ring_buffer_size_get();
    capture_ring_buffer_status = MIC_TX_BUFFER_STATUS_START;
    //capture_frame_size = capture_frame_size_ms * mic_samprate / 1000 * mic_tx_capture_in_ch_num * sizeof(int16_t);
    capture_frame_size = wifi_mic_config_mic_tx_capture_frame_size_get();
    capture_asio_buffer_size = capture_frame_size * 2;

    #if 1
    dbg("mic_samprate:%d\n", mic_samprate);
    dbg("tx2rx_air_pkt_size_ms:%d\n", tx2rx_air_pkt_size_ms);
    dbg("tx2rx_air_pkt_size:%d\n", tx2rx_air_pkt_size);
    dbg("playback_frame_size_ms:%d\n", playback_frame_size_ms);
    dbg("mic_tx_playback_ch_num:%d\n", mic_tx_playback_ch_num);
    dbg("playback_ring_buffer_size:%d\n", playback_ring_buffer_size);
    dbg("playback_frame_size:%d\n", playback_frame_size);
    dbg("playback_asio_buffer_size:%d\n", playback_asio_buffer_size);
    dbg("capture_frame_size_ms:%d\n", capture_frame_size_ms);
    dbg("mic_tx_capture_in_ch_num:%d\n", mic_tx_capture_in_ch_num);
    dbg("mic_tx_capture_out_ch_num:%d\n", mic_tx_capture_out_ch_num);
    dbg("capture_ring_buffer_size:%d\n", capture_ring_buffer_size);
    dbg("capture_frame_size:%d\n", capture_frame_size);
    dbg("capture_asio_buffer_size:%d\n", capture_asio_buffer_size);
    #endif

    if (0 != rtos_mutex_recursive_create(&playback_ring_buffer_mutex)) {
        dbg("ERR: playback_ring_buffer_mutex create fail!\r\n");
        return -1;
    }

    if (0 != rtos_mutex_recursive_create(&capture_ring_buffer_mutex)) {
        dbg("ERR: capture_ring_buffer_mutex create fail!\r\n");
        return -1;
    }

    playback_ring_buffer_storage = (uint8_t *)rtos_malloc(playback_ring_buffer_size);
    if (!playback_ring_buffer_storage) {
        dbg("ERR: playback_ring_buffer_storage malloc fail!, %d\r\n", playback_ring_buffer_size);
        return -1;
    }
    dbg("### playback_ring_buffer_storage %x\r\n", playback_ring_buffer_storage);
    ring_buffer_init(&playback_ring_buffer, playback_ring_buffer_storage, playback_ring_buffer_size);

    capture_ring_buffer_storage = rtos_malloc(capture_ring_buffer_size);
    if (!capture_ring_buffer_storage) {
        dbg("ERR: capture_ring_buffer_storage malloc fail\n");
        return -1;
    }
    dbg("### capture_ring_buffer_storage %x\r\n", capture_ring_buffer_storage);
    ring_buffer_init(&capture_ring_buffer, capture_ring_buffer_storage, capture_ring_buffer_size);

    if (rtos_task_create(mic_tx_task, "mic tx task", APPLICATION_TASK,
                         TASK_STACK_SIZE_WIFI_VOICE, NULL, TASK_PRIORITY_WIFI_VOICE, &mic_tx_task_handle)) {

        dbg("ERR: mic tx task create fail\n");
        return -1;
    }

    return 0;
}

int wifi_mic_tx_deinit(void)
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

    return 0;
}
#endif

