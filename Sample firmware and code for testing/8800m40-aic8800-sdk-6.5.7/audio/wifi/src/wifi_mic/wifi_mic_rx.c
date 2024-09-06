#include "plf.h"
#if PLF_WIFI_AUDIO
#include "fhost.h"
#include "netdb.h"
#include "fhost_config.h"
#include "fhost_cntrl.h"
#include "rwnx_msg_tx.h"
#include "wlan_if.h"
#include "sleep_api.h"
#include "wifi_voice.h"
#include "ring_buffer.h"
#include "ip.h"
#include "etharp.h"
#include "lwip/prot/ethernet.h"
#include "wlan_if.h"
#include "dhcps.h"
#include "fhost_tx.h"
#include "wifi_mic_config.h"
#include "asio.h"
#include "audio_config.h"
#include "wifi_mic_rx.h"
#include "audio_utils.h"

typedef enum {
    MIC_RX_BUFFER_STATUS_STOP = 0,
    MIC_RX_BUFFER_STATUS_START,
    MIC_RX_BUFFER_STATUS_RESTART,
    MIC_RX_BUFFER_STATUS_REACH_THRESHOLD,
    MIC_RX_BUFFER_STATUS_NUM,
} MIC_RX_BUFFER_STATUS;

#define AUD_SAMPRATE_44100                  44100
#define AUD_SAMPRATE_48000                  48000
#define AUD_SAMPRATE_88200                  88200
#define AUD_SAMPRATE_96000                  96000

#define CURRENT_AUD_SAMPRATE                AUD_SAMPRATE_48000

static rtos_task_handle mic_rx_task_handle = NULL;

static uint8_t wifi_sta_connected_cnt = 0;
static TimerHandle_t wifi_sta_check_timer = NULL;
static uint32_t wifi_sta_check_period_ms = 0;

static uint32_t mic_samprate = 0;
static uint16_t tx2rx_air_pkt_size_ms = 0;
static uint16_t tx2rx_air_pkt_size = 0;

static uint16_t mic_rx_playback_frame_size_ms = 0;
static uint16_t mic_rx_playback_frame_size = 0;
static uint32_t mic_rx_playback_ring_buffer_size = 0;
static uint16_t mic_rx_playback_asio_buffer_size = 0;
static uint32_t mic_rx_playback_start_level_size = 0;
static uint16_t mic_rx_playback_mix_buffer_size = 0;
static uint8_t *mic_rx_playback_mix_buffer[VOICE_MAX_STREAMS] = {NULL};
static uint8_t *mic_rx_playback_ring_buffer_storage[VOICE_MAX_STREAMS] = {NULL};
static ring_buffer_t mic_rx_playback_ring_buffer[VOICE_MAX_STREAMS];
static uint8_t mic_rx_playback_ring_buffer_status[VOICE_MAX_STREAMS] = {0};
static uint8_t mic_rx_playback_ch_num = 0;
static uint8_t mic_tx_capture_out_ch_num = 0;

static rtos_mutex mic_rx_playback_ring_buffer_mutex = NULL;

static bool start_playback_sent = false;
static bool start_capture_sent = false;

static wifi_voice_led_handler_t mic_rx_led_handler = NULL;
static wifi_voice_mix_handler_t mic_rx_mix_handler = NULL;

#define MIC_RX_RING_BUFFER_LOCK()      rtos_mutex_recursive_lock(mic_rx_playback_ring_buffer_mutex)
#define MIC_RX_RING_BUFFER_UNLOCK()    rtos_mutex_recursive_unlock(mic_rx_playback_ring_buffer_mutex)

int wifi_mic_rx_playback_open(void);
int wifi_mic_rx_playback_start(void);
int wifi_mic_rx_playback_stop(void);

void wifi_mic_rx_led_handler_register(wifi_voice_led_handler_t handler)
{
    mic_rx_led_handler = handler;
}

void wifi_mic_rx_mix_handler_register(wifi_voice_mix_handler_t handler)
{
    mic_rx_mix_handler = handler;
}

static void sta_check_callback(void const *param)
{
    if (vif_mgmt_sta_cnt(0) == 0) {
        if (wifi_sta_connected_cnt > 0) {
            dbg("sta_disconnected,now=%d %d\r\n",rtos_now(false), wifi_sta_connected_cnt);
            wifi_voice_client_disconnected(10, false);
        }
    } else {
        if ((wifi_sta_connected_cnt < vif_mgmt_sta_cnt(0)) && (get_client_ip_offered_cnt() == vif_mgmt_sta_cnt(0))) {
            dbg("sta_connected,now=%d\r\n",rtos_now(false));
            wifi_voice_client_connected(10, false);
        }
    }

    static uint8_t last_to_times = 0; // 1/10 TOs per 100ms
    if ((fhost_tx_get_to_times() - last_to_times) >= (wifi_sta_check_period_ms / tx2rx_air_pkt_size_ms / 10)) {
        wifi_voice_do_switch_channel(10, false);
    }
    last_to_times = fhost_tx_get_to_times();
}

static void mic_rx_playback_ring_buffer_reset(void)
{
    MIC_RX_RING_BUFFER_LOCK();
    for (int i = 0; i < wifi_mic_config_mic_tx_num_get(); i++) {
        ring_buffer_reset(&mic_rx_playback_ring_buffer[i]);
        mic_rx_playback_ring_buffer_status[i] = MIC_RX_BUFFER_STATUS_START;
    }
    MIC_RX_RING_BUFFER_UNLOCK();
}

static void mic_rx_data_handler(uint8_t *data, uint32_t size, uint8_t index)
{
    //dbg("data@(%d): %02X %02X %02X %02X\r\n",size,data[0],data[1],data[2],data[3]);

    int rb_st;
    uint32_t bytes_used;
    uint32_t bytes_free;
    uint32_t write_len;
    uint32_t read_len;
    uint32_t drop_len;

    wifi_voice_data_stop_check_timer_restart(0, false);

    MIC_RX_RING_BUFFER_LOCK();
    GLOBAL_INT_DISABLE();

    if (mic_rx_playback_ring_buffer_status[index] >= MIC_RX_BUFFER_STATUS_START) {
        rb_st = ring_buffer_write(&mic_rx_playback_ring_buffer[index], (uint8_t *)data, size);
        //dbg("size %d\r\n", ring_buffer_bytes_used(&mic_rx_playback_ring_buffer[index]));
        if (RB_ERR_NONE != rb_st) {
            bytes_free = ring_buffer_bytes_free(&mic_rx_playback_ring_buffer[index]);
            bytes_used = ring_buffer_bytes_used(&mic_rx_playback_ring_buffer[index]);

            if (mic_rx_playback_ring_buffer[index].size <= size) {
                read_len = bytes_used;
                write_len = mic_rx_playback_ring_buffer[index].size;
                drop_len = read_len + size - mic_rx_playback_ring_buffer[index].size;
            } else {
                read_len = size - bytes_free;
                write_len = size;
                drop_len = read_len;
            }

            ring_buffer_read(&mic_rx_playback_ring_buffer[index], NULL, read_len);
            ring_buffer_write(&mic_rx_playback_ring_buffer[index], data, write_len);
            //mic rx buffer full
            dbg("RPF:%d/%d\n", size, drop_len);
        }

        if (mic_rx_playback_ring_buffer_status[index] == MIC_RX_BUFFER_STATUS_START) {
            bytes_used = ring_buffer_bytes_used(&mic_rx_playback_ring_buffer[index]);
            if (bytes_used >= mic_rx_playback_start_level_size) {
                mic_rx_playback_ring_buffer_status[index] = MIC_RX_BUFFER_STATUS_REACH_THRESHOLD;
                wifi_mic_rx_playback_start();
            }
        }
    } else {
        //mic rx stop, drop frame
        dbg("RPSP:%d\n", size);
    }
    GLOBAL_INT_RESTORE();
    MIC_RX_RING_BUFFER_UNLOCK();
}

static uint32_t mic_rx_playback_handler(uint8_t *buf, uint32_t len)
{
    uint32_t len_want = len;
    uint32_t buffered_size_0, buffered_size_1;
    int16_t *p_buffer = NULL;
    int16_t *buffer_0 = (int16_t *)mic_rx_playback_mix_buffer[0];
    int16_t *buffer_1 = (int16_t *)mic_rx_playback_mix_buffer[1];

    if ((mic_rx_playback_ch_num == AUD_CH_NUM_2) && (mic_tx_capture_out_ch_num == AUD_CH_NUM_1)) {
        len_want = len / mic_rx_playback_ch_num;
    }

    buffered_size_0 = ring_buffer_bytes_used(&mic_rx_playback_ring_buffer[0]);
    buffered_size_1 = ring_buffer_bytes_used(&mic_rx_playback_ring_buffer[1]);
    if((buffered_size_0 >= len_want) && (buffered_size_1 >= len_want)) {
        ring_buffer_read(&mic_rx_playback_ring_buffer[0], (uint8_t *)buffer_0, len_want);
        ring_buffer_read(&mic_rx_playback_ring_buffer[1], (uint8_t *)buffer_1, len_want);
        if (mic_rx_mix_handler) {
            uint8_t *input[VOICE_MAX_STREAMS];
            input[0] = (uint8_t *)buffer_0;
            input[1] = (uint8_t *)buffer_1;
            mic_rx_mix_handler(input, 2, mic_tx_capture_out_ch_num, len_want, (uint8_t *)buf);
        } else {
            p_buffer = (int16_t *)buf;
            for (uint32_t i = 0; i < (len_want / 2); i++) {
                p_buffer[i] = (int16_t)(((int32_t)buffer_0[i] + (int32_t)buffer_1[i]) / 2);
                //dbg("%d,%d,%d\r\n", p_buffer[i], buffer_0[i], buffer_1[i]);
            }
        }
    } else if(buffered_size_0 >= len_want) {
        ring_buffer_read(&mic_rx_playback_ring_buffer[0], (uint8_t *)buf, len_want);
    } else if(buffered_size_1 >= len_want) {
        ring_buffer_read(&mic_rx_playback_ring_buffer[1], (uint8_t *)buf, len_want);
    } else {
        memset((void *)buf, 0, len);
        //mic rx buffer empty
        dbg("RPE %d %d %d\n", len_want, buffered_size_0, buffered_size_1);
    }

    if ((mic_rx_playback_ch_num == AUD_CH_NUM_2) && (mic_tx_capture_out_ch_num == AUD_CH_NUM_1)) {
        // Convert mono data to stereo data
        audio_channel_copy_16bits((int16_t *)buf, (int16_t *)buf, (len_want / 2));
    }

    return len;
}

int wifi_mic_rx_playback(MediaControlType cmd, MediaCommonStruct* param)
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
            playback_cfg.ch_num = mic_rx_playback_ch_num;
            if (mic_rx_playback_ch_num == AUD_CH_NUM_2) {
                playback_cfg.ch_map = AUD_CH_MAP_CH_0 | AUD_CH_MAP_CH_1;
            } else {
                playback_cfg.ch_map = AUD_CH_MAP_CH_0;
            }
            playback_cfg.device = audio_config_device_get();
            playback_cfg.samp_rate = mic_samprate;
            playback_cfg.src_samp_rate = AUD_SAMPRATE_48000;
            playback_cfg.path = AUD_PATH_TX01;
            playback_cfg.handler = mic_rx_playback_handler;
            playback_cfg.buf_size = mic_rx_playback_asio_buffer_size;
            playback_cfg.src_en = true;

            if (playback_buf == NULL) {
                playback_buf = (uint8_t *)rtos_malloc(mic_rx_playback_asio_buffer_size);
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

            MIC_RX_RING_BUFFER_LOCK();
            for (int i = 0; i < wifi_mic_config_mic_tx_num_get(); i++) {
                ring_buffer_reset(&mic_rx_playback_ring_buffer[i]);
            }
            MIC_RX_RING_BUFFER_UNLOCK();
        }
    }

exit:
    status = (playback_opened << 0) | (playback_started << 1);

    return status;
}

int wifi_mic_rx_playback_open(void)
{
    int ret;
    MediaControlType cmd;
    MediaCommonStruct param;

    cmd = MC_OPEN;

    ret = wifi_mic_rx_playback(cmd, &param);

    return ret;
}

int wifi_mic_rx_playback_start(void)
{
    int ret;
    MediaControlType cmd;
    MediaCommonStruct param;

    cmd = MC_PLAY;

    ret = wifi_mic_rx_playback(cmd, &param);

    return ret;
}

int wifi_mic_rx_playback_stop(void)
{
    int ret;
    MediaControlType cmd;
    MediaCommonStruct param;

    cmd = MC_STOP;

    ret = wifi_mic_rx_playback(cmd, &param);

    return ret;
}

void wifi_mic_rx_force_pairing(void)
{
    char ssid[32] = {0};
    char pw[64]   = {0};
    wlan_stop_ap();
    rtos_task_suspend(1000);
    wlan_ap_generate_ssid_pw_for_pairing((char *)ssid, (char *)pw);
    int ret = wlan_start_ap(wifi_mic_config_band_get(), (uint8_t *)ssid, (uint8_t *)pw);
    if (ret) {
        dbg("AP start err: %d\n", ret);
    }
}

static RTOS_TASK_FCT(mic_rx_task)
{
    struct wifi_voice_settings settings;
    char ssid[32] = {0};
    char pw[64]   = {0};

    dbg("mic_rx_task\n");
    do {
        bool em_status = false;
        uint32_t msg;
        uint16_t bcn_interval = wifi_mic_config_bcn_interval_get();

        set_ap_bcn_interval(bcn_interval);
        #ifdef CFG_WIFI_ENGINEERING_MODE
        em_status = wifi_engineering_mode_status_get();
        #endif
        if (!em_status) {
            uint8_t ch_num = wifi_mic_config_channel_get();
            set_ap_channel_num(ch_num);
        }
        set_mac_address(wifi_mic_config_mic_rx_mac_addr_get());
        user_limit_sta_num_set(wifi_mic_config_mic_tx_num_get());
        set_ap_enable_he_rate(1);
        wlan_ap_generate_ssid_pw_for_pairing((char *)ssid, (char *)pw);
        int ret = wlan_start_ap(wifi_mic_config_band_get(), (uint8_t *)ssid, (uint8_t *)pw);
        if (ret) {
            dbg("AP start err: %d\n", ret);
            break;
        }
        dbg("AP started, client mode\r\n");

        rtos_timer_start(wifi_sta_check_timer, 0, false);

        wifi_voice_data_handler_register(mic_rx_data_handler);

        memset(&settings, 0, sizeof(struct wifi_voice_settings));
        settings.role = WIFI_VOICE_ROLE_DONGLE;
        settings.is_server = false;
        settings.pl_size = 0;
        wifi_voice_task_init(&settings);

        while (1) {
            wifi_voice_msg_queue_read(&msg, -1, false);
            //dbg("msg %x\r\n", msg);
            switch (msg) {
            case WIFI_CLIENT_CONNECTED: {
                struct wifi_voice_stream_t *stream = wifi_voice_find_free_stream();
                if (!stream) {
                    dbg("No free stream !\r\n");
                    break;
                }
                uint32_t sta_ip = get_client_ip_by_index(stream->strm_id);
                settings.stream_addr = sta_ip;
                wifi_sta_connected_cnt++;

                wifi_voice_stream_start(&settings);

                wifi_mic_rx_playback_open();
                break;
            }
            case WIFI_CLIENT_DISCONNECTED: {
                rtos_timer_stop(wifi_sta_check_timer, 0);
                if (wifi_sta_connected_cnt > 0) {
                    wifi_voice_stream_stop();
                    wifi_sta_connected_cnt = 0;
                    rtos_timer_start(wifi_sta_check_timer, 0, 0);

                    start_playback_sent = false;
                    start_capture_sent = false;

                    wifi_mic_rx_playback_stop();
                    mic_rx_playback_ring_buffer_reset();
                }
                break;
            }
            case VOICE_SOCK_DISCONNECTED: {
                start_playback_sent = false;
                start_capture_sent = false;
                wifi_voice_stream_stop_by_id(0);// TODO: 1 -> 1
                wifi_mic_rx_playback_stop();
                mic_rx_playback_ring_buffer_reset();
                break;
            }
            case WIFI_SWITCH_CHANNEL: {
                wifi_voice_switch_channel(wifi_mic_config_band_get(), false);
                break;
            }
            default: {
                break;
            }
            }
        }
    } while (0);

    wifi_voice_task_deinit(&settings);
    wifi_mic_rx_deinit();
    rtos_task_delete(NULL);
}

/*
 * Dongle USB RX PKT--->Dongle USB RX ring buffer--->H2D AIR PKT--->Headset playback ring buffer--->Headset playback asio buffer
 * Headset capture asio buffer--->Headset capture ring buffer--->D2H AIR PKT--->Dongle USB TX ring buffer--->Dongle USB TX PKT
 */
int wifi_mic_rx_init(void)
{
    mic_samprate = wifi_mic_config_samprate_get();
    tx2rx_air_pkt_size_ms = wifi_mic_config_tx2rx_air_pkt_size_ms_get();
    tx2rx_air_pkt_size = wifi_mic_config_tx2rx_air_pkt_size_get();

    mic_rx_playback_frame_size_ms = wifi_mic_config_mic_rx_playback_frame_size_ms_get();
    mic_rx_playback_ch_num = wifi_mic_config_mic_rx_playback_ch_num_get();
    mic_tx_capture_out_ch_num = wifi_mic_config_mic_tx_capture_out_ch_num_get();

    mic_rx_playback_ring_buffer_size = wifi_mic_config_mic_rx_playback_ring_buffer_size_get();
    mic_rx_playback_start_level_size = wifi_mic_config_mic_rx_playback_start_level_size_get();
    for (int i = 0; i < wifi_mic_config_mic_tx_num_get(); i++) {
        mic_rx_playback_ring_buffer_status[i] = MIC_RX_BUFFER_STATUS_START;
    }
    wifi_sta_check_period_ms = wifi_mic_config_sta_check_period_ms_get();

    //mic_rx_playback_frame_size = mic_rx_playback_frame_size_ms * mic_samprate / 1000 * mic_rx_playback_ch_num * sizeof(int16_t);
    mic_rx_playback_frame_size = wifi_mic_config_mic_rx_playback_frame_size_get();
    mic_rx_playback_asio_buffer_size = mic_rx_playback_frame_size * 2;

    mic_rx_playback_mix_buffer_size = mic_rx_playback_frame_size_ms * mic_samprate / 1000 * mic_tx_capture_out_ch_num * sizeof(int16_t);

    #if 1
    dbg("mic_samprate:%d\n", mic_samprate);
    dbg("tx2rx_air_pkt_size_ms:%d\n", tx2rx_air_pkt_size_ms);
    dbg("tx2rx_air_pkt_size:%d\n", tx2rx_air_pkt_size);
    dbg("mic_rx_playback_frame_size_ms:%d\n", mic_rx_playback_frame_size_ms);
    dbg("mic_rx_playback_ch_num:%d\n", mic_rx_playback_ch_num);
    dbg("mic_tx_capture_out_ch_num:%d\n", mic_tx_capture_out_ch_num);
    dbg("mic_rx_playback_ring_buffer_size:%d\n", mic_rx_playback_ring_buffer_size);
    dbg("mic_rx_playback_start_level_size:%d\n", mic_rx_playback_start_level_size);
    dbg("wifi_sta_check_period_ms:%d\n", wifi_sta_check_period_ms);
    dbg("mic_rx_playback_frame_size:%d\n", mic_rx_playback_frame_size);
    dbg("mic_rx_playback_asio_buffer_size:%d\n", mic_rx_playback_asio_buffer_size);
    dbg("mic_rx_playback_mix_buffer_size:%d\n", mic_rx_playback_mix_buffer_size);
    #endif

    wifi_sta_check_timer = rtos_timer_create("sta_check_timer", pdMS_TO_TICKS(wifi_sta_check_period_ms), pdTRUE, NULL,
                                              (TimerCallbackFunction_t)sta_check_callback);
    if (!wifi_sta_check_timer) {
        dbg("ERR: wifi_sta_check_timer create fail\n");
        return -1;
    }

    if (0 != rtos_mutex_recursive_create(&mic_rx_playback_ring_buffer_mutex)) {
        dbg("ERR: mic_rx_playback_ring_buffer_mutex create fail!\r\n");
        return -1;
    }

    for (int i = 0; i < wifi_mic_config_mic_tx_num_get(); i++) {
        mic_rx_playback_ring_buffer_storage[i] = rtos_malloc(mic_rx_playback_ring_buffer_size);
        if (!mic_rx_playback_ring_buffer_storage[i]) {
            dbg("ERR: mic_rx_playback_ring_buffer_storage[%d] malloc fail\n", i);
            return -1;
        }
        ring_buffer_init(&mic_rx_playback_ring_buffer[i], mic_rx_playback_ring_buffer_storage[i], mic_rx_playback_ring_buffer_size);

        mic_rx_playback_mix_buffer[i] = rtos_malloc(mic_rx_playback_mix_buffer_size);

        if (!mic_rx_playback_mix_buffer[i]) {
            dbg("ERR: mic_rx_playback_mix_buffer[%d] malloc fail\n", i);
            return -1;
        }
    }

    if (rtos_task_create(mic_rx_task, "mic rx task", APPLICATION_TASK,
                         TASK_STACK_SIZE_WIFI_VOICE, NULL, TASK_PRIORITY_WIFI_VOICE, &mic_rx_task_handle)) {
        dbg("ERR: mic rx task create fail\n");
        return -1;
    }

    return 0;
}

int wifi_mic_rx_deinit(void)
{
    if (wifi_sta_check_timer) {
        rtos_timer_delete(wifi_sta_check_timer, 0);
        wifi_sta_check_timer = NULL;
    }

    if (mic_rx_playback_ring_buffer_mutex) {
        rtos_mutex_delete(mic_rx_playback_ring_buffer_mutex);
        mic_rx_playback_ring_buffer_mutex = NULL;
    }

    for (int i = 0; i < wifi_mic_config_mic_tx_num_get(); i++) {
        ring_buffer_deinit(&mic_rx_playback_ring_buffer[i]);
        if (mic_rx_playback_ring_buffer_storage[i]) {
            rtos_free(mic_rx_playback_ring_buffer_storage[i]);
            mic_rx_playback_ring_buffer_storage[i] = NULL;
        }

        if (mic_rx_playback_mix_buffer[i]) {
            rtos_free(mic_rx_playback_mix_buffer[i]);
            mic_rx_playback_mix_buffer[i] = NULL;
        }
    }

    return 0;
}
#endif

