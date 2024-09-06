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
#include "usbd_audio.h"
#include "wifi_wh_config.h"
#include "wifi_wh_dongle.h"
#include "audio_utils.h"
#include "asio_dsd.h"
#include "asio_src.h"

typedef enum {
    USB_BUFFER_STATUS_STOP = 0,
    USB_BUFFER_STATUS_START,
    USB_BUFFER_STATUS_RESTART,
    USB_BUFFER_STATUS_REACH_THRESHOLD,
    USB_BUFFER_STATUS_NUM,
} USB_BUFFER_STATUS;

#define USB_AUTO_BUFF0_EN       1
#define USB_AUTO_BUFF1_EN       1
#define QUALIFIED_RSSI          -60
#define QUALIFIED_RSSI_COUNT    1000

#define USB_AUDIO_DATA_EN       1

#define AUD_SAMPRATE_44100                  44100
#define AUD_SAMPRATE_48000                  48000
#define AUD_SAMPRATE_88200                  88200
#define AUD_SAMPRATE_96000                  96000

#define CURRENT_AUD_SAMPRATE                AUD_SAMPRATE_48000

static rtos_task_handle dongle_task_handle = NULL;

static uint8_t wifi_sta_connected_cnt = 0;
static TimerHandle_t wifi_sta_check_timer = NULL;
static uint32_t wifi_sta_check_period_ms = 0;

static uint16_t usb_audio_pkt_size = 0;

static uint16_t d2h_air_pkt_size_ms = 0;
static uint16_t d2h_air_pkt_size = 0;

static uint8_t *usb_rx_ring_buffer_storage = NULL;
static ring_buffer_t usb_rx_ring_buffer;
static uint32_t usb_rx_ring_buffer_size = 0;

static uint16_t usb_tx_mix_buffer_size = 0;
static uint8_t *usb_tx_mix_buffer[VOICE_MAX_STREAMS] = {NULL};
static uint8_t *usb_tx_ring_buffer_storage[VOICE_MAX_STREAMS] = {NULL};
static ring_buffer_t usb_tx_ring_buffer[VOICE_MAX_STREAMS];
static uint32_t usb_tx_ring_buffer_size = 0;
static uint32_t usb_tx_start_level_size[2] = {0,0};
static uint8_t usb_tx_ring_buffer_status[2] = {0,0};

static uint16_t usb_rx_buffer_size = 0;
static uint16_t usb_tx_buffer_size = 0;
static uint8_t *usb_rx_buffer = NULL;
static uint8_t *usb_tx_buffer = NULL;
static uint16_t usb_rx_pkt_cnt = 0;

static bool usb_send_started = false;

static uint16_t headset_mic_samprate = 0;
static uint8_t headset_capture_out_ch_num = 0;

static bool start_playback_sent = false;
static bool start_capture_sent = false;

static wifi_voice_led_handler_t dongle_led_handler = NULL;
static wifi_voice_mix_handler_t dongle_mix_handler = NULL;

static uint8_t *usb_dsd_buffer[4] = {NULL,NULL,NULL,NULL};


static TimerHandle_t data_check_timer[2] = {NULL,NULL};
static bool data_check_timer_started[2] = {false,false};
static uint32_t pkt_cnt[2] = {0,0};
static uint32_t mute_pkt_size[2] = {0,0};
static uint32_t drop_pkt_size[2] = {0,0};
static bool data_rx_done[2] = {false,false};
static uint8_t pp_index[2] = {0,0};
static bool auto_buffer_status_en[2] = {false,false};
static bool auto_buffer_recover_en[2] = {false,false};
static uint32_t auto_mute_pkt_size[2] = {0,0};
static int rssi_check_num[2] = {0,0};

void wifi_wh_dongle_led_handler_register(wifi_voice_led_handler_t handler)
{
    dongle_led_handler = handler;
}

void wifi_wh_dongle_mix_handler_register(wifi_voice_mix_handler_t handler)
{
    dongle_mix_handler = handler;
}

static void data_param_clean(void)
{
    for(uint8_t i = 0 ;i < 2;i++){
        data_check_timer_started[i] = false;
        pkt_cnt[i] = 0;
        mute_pkt_size[i] = 0;
        drop_pkt_size[i] = 0;
        data_rx_done[i] = false;
        pp_index[i] = 0;
        auto_buffer_status_en[i] = false;
        auto_buffer_recover_en[i] = false;
        auto_mute_pkt_size[i] = 0;
        rssi_check_num[i] = 0;
        usb_tx_start_level_size[i] = wifi_wh_config_usb_tx_start_level_size_get();
    }
}

static void data0_rx_asio_dsd_cb(void *param)
{
    data_rx_done[0] = true;
}

static void data1_rx_asio_dsd_cb(void *param)
{
    data_rx_done[1] = true;
}

static void data0_tx_asio_dsd_cb(void *param)
{
    uint32_t len_want = usb_tx_mix_buffer_size;
    uint32_t buffered_size_0;

    //dbg("data:%p,size:%d %d\n",xfer->data,xfer->size, rtos_now(true));
    //memset(usb_dsd_buffer[0],0,usb_tx_mix_buffer_size*7);
    if (usb_tx_ring_buffer_status[0] > USB_BUFFER_STATUS_RESTART) {
        // audio mixing
        int8_t rssi = data_pkt_rssi_get();
        buffered_size_0 = ring_buffer_bytes_used(&usb_tx_ring_buffer[0]);
        //dbg("rssi 0 %d ",rssi);
        if(rssi >= QUALIFIED_RSSI){
            rssi_check_num[0]++;
        }else{
            rssi_check_num[0] = 0;
        }
        if(buffered_size_0 >= len_want) {
            if(buffered_size_0 >= len_want*7){
                ring_buffer_read(&usb_tx_ring_buffer[0], (uint8_t *)usb_dsd_buffer[pp_index[0]], len_want*7);
                #if USB_AUTO_BUFF0_EN
                if(auto_buffer_status_en[0]){
                    if(rssi_check_num[0] >= QUALIFIED_RSSI_COUNT){
                        auto_buffer_status_en[0] = false;
                        auto_buffer_recover_en[0] = true;
                        rssi_check_num[0] = 0;
                        dbg("auto buf 0 disable\n");
                        usb_tx_start_level_size[0] = wifi_wh_config_usb_tx_start_level_size_get();
                    }
                }
                #endif
            } else {
                ring_buffer_read(&usb_tx_ring_buffer[0], (uint8_t *)usb_dsd_buffer[pp_index[0]], buffered_size_0);
                mute_pkt_size[0] += (len_want*7 - buffered_size_0);
                rssi_check_num[0] = 0;
                dbg("UTE0_0\n");
            }
        } else {
            #if USB_AUTO_BUFF0_EN
            if(!auto_buffer_status_en[0]){
                auto_buffer_status_en[0] = true;
                usb_tx_ring_buffer_status[0] = USB_BUFFER_STATUS_RESTART;
                usb_tx_start_level_size[0] = wifi_wh_config_usb_tx_auto_start_level_size_get();
                rssi_check_num[0] = 0;
                dbg("auto buf 0 enable\n");
            }
            #endif
            ring_buffer_read(&usb_tx_ring_buffer[0], (uint8_t *)usb_dsd_buffer[pp_index[0]], buffered_size_0);
            mute_pkt_size[0] += (len_want*7 - buffered_size_0);
            rssi_check_num[0] = 0;
            dbg("UTE0\n");
        }
        if (headset_capture_out_ch_num == AUD_CH_NUM_1) {
            // Convert mono data to stereo data
            audio_channel_copy_16bits((int16_t *)usb_dsd_buffer[pp_index[0]], (int16_t *)usb_dsd_buffer[pp_index[0]], (len_want*7 / 2));
        }
    }
#if USB_AUTO_BUFF0_EN
    else {
        auto_mute_pkt_size[0] += (len_want*7);
        rssi_check_num[0] = 0;
    }
#endif
    pp_index[0]++;
    pp_index[0]=pp_index[0]%2;
}

static void data1_tx_asio_dsd_cb(void *param)
{
    uint32_t len_want = usb_tx_mix_buffer_size;
    uint32_t buffered_size_1;

    //dbg("data:%p,size:%d %d\n",xfer->data,xfer->size, rtos_now(true));
    //memset(usb_dsd_buffer[1],0,usb_tx_mix_buffer_size*7);
    if (usb_tx_ring_buffer_status[1] > USB_BUFFER_STATUS_RESTART) {
        // audio mixing
        int8_t rssi = data_pkt_rssi_get();
        buffered_size_1 = ring_buffer_bytes_used(&usb_tx_ring_buffer[1]);
        //dbg("rssi 1 %d ",rssi);
        if(rssi >= QUALIFIED_RSSI){
            rssi_check_num[1]++;
        }else{
            rssi_check_num[1] = 0;
        }
        if(buffered_size_1 >= len_want) {
            if(buffered_size_1 >= len_want*7){
                ring_buffer_read(&usb_tx_ring_buffer[1], (uint8_t *)usb_dsd_buffer[pp_index[1]+2], len_want*7);
                #if USB_AUTO_BUFF0_EN
                if(auto_buffer_status_en[1]){
                    if(rssi_check_num[1] >= QUALIFIED_RSSI_COUNT){
                        auto_buffer_status_en[1] = false;
                        auto_buffer_recover_en[1] = true;
                        rssi_check_num[1] = 0;
                        dbg("auto buf 0 disable\n");
                        usb_tx_start_level_size[1] = wifi_wh_config_usb_tx_start_level_size_get();
                    }
                }
                #endif
            } else {
                ring_buffer_read(&usb_tx_ring_buffer[1], (uint8_t *)usb_dsd_buffer[pp_index[1]+2], buffered_size_1);
                mute_pkt_size[1] += (len_want*7 - buffered_size_1);
                rssi_check_num[1] = 0;
                dbg("UTE1_0\n");
            }
        } else {
            #if USB_AUTO_BUFF1_EN
            if(!auto_buffer_status_en[1]){
                auto_buffer_status_en[1] = true;
                usb_tx_ring_buffer_status[1] = USB_BUFFER_STATUS_RESTART;
                usb_tx_start_level_size[1] = wifi_wh_config_usb_tx_auto_start_level_size_get();
                rssi_check_num[1] = 0;
                dbg("auto buf 1 enable\n");
            }
            #endif
            ring_buffer_read(&usb_tx_ring_buffer[1], (uint8_t *)usb_dsd_buffer[pp_index[1]+2], buffered_size_1);
            mute_pkt_size[1] += (len_want*7 - buffered_size_1);
            dbg("UTE1\n");
        }
        if (headset_capture_out_ch_num == AUD_CH_NUM_1) {
            // Convert mono data to stereo data
            audio_channel_copy_16bits((int16_t *)usb_dsd_buffer[pp_index[1]+2], (int16_t *)usb_dsd_buffer[pp_index[1]+2], (len_want*7 / 2));
        }
    }
#if USB_AUTO_BUFF1_EN
    else {
        auto_mute_pkt_size[1] += (len_want*7);
        rssi_check_num[1] = 0;
    }
#endif
    pp_index[1]++;
    pp_index[1]=pp_index[1]%2;
}

static void data0_check_callback(void const *param)
{
    uint32_t p_s0,p_s1,p_s2,p_s3;
    uint32_t size;
    int sync_size = 0;
    bool do_it = true;

    GLOBAL_INT_DISABLE();
    sync_size = usb_tx_start_level_size[0]-1344;
    size = ring_buffer_bytes_used(&usb_tx_ring_buffer[0]);
    p_s0 = size;
    p_s1 = mute_pkt_size[0];
    p_s2 = drop_pkt_size[0];
    if (mute_pkt_size[0]) {
        if (drop_pkt_size[0]) {
            if (mute_pkt_size[0] >= drop_pkt_size[0] && (mute_pkt_size[0]-drop_pkt_size[0]) < size) {
                ring_buffer_read(&usb_tx_ring_buffer[0], NULL, (mute_pkt_size[0]-drop_pkt_size[0]));
                drop_pkt_size[0] = 0;
                mute_pkt_size[0] = 0;
            }
        } else {
            if (mute_pkt_size[0] < size) {
                ring_buffer_read(&usb_tx_ring_buffer[0], NULL, mute_pkt_size[0]);
                mute_pkt_size[0] = 0;
            }
        }
    }
    if (auto_buffer_recover_en[0]) {
        size = ring_buffer_bytes_used(&usb_tx_ring_buffer[0]);
        dbg("0 auto_mute_pkt_size %d/%d\n",auto_mute_pkt_size[0],size);
        if(auto_mute_pkt_size[0]< size){
            auto_buffer_recover_en[0] = false;
            ring_buffer_read(&usb_tx_ring_buffer[0], NULL, auto_mute_pkt_size[0]);
            auto_mute_pkt_size[0] = 0;
        }else{
            do_it = false;
        }
    }
    size = ring_buffer_bytes_used(&usb_tx_ring_buffer[0]);
    p_s3 = size;
    GLOBAL_INT_RESTORE();
    dbg("0 size %d/%d,pkt %d,m %d,d %d\n",p_s0,p_s3,pkt_cnt[0],p_s1,p_s2);
    if(do_it){
        asio_adc_src_process(size,sync_size);
    }
    data_check_timer_started[0] = false;
    pkt_cnt[0] = 0;
}

static void data1_check_callback(void const *param)
{
    uint32_t p_s0,p_s1,p_s2,p_s3;
    uint32_t size;
    int sync_size = 0;
    bool do_it = true;

    GLOBAL_INT_DISABLE();
    sync_size = usb_tx_start_level_size[1]-1344;
    size = ring_buffer_bytes_used(&usb_tx_ring_buffer[1]);
    p_s0 = size;
    p_s1 = mute_pkt_size[1];
    p_s2 = drop_pkt_size[1];
    if (mute_pkt_size[1]) {
        if (drop_pkt_size[1]) {
            if (mute_pkt_size[1] >= drop_pkt_size[1] && (mute_pkt_size[1]-drop_pkt_size[1]) < size) {
                ring_buffer_read(&usb_tx_ring_buffer[1], NULL, (mute_pkt_size[1]-drop_pkt_size[1]));
                drop_pkt_size[1] = 0;
                mute_pkt_size[1] = 0;
            }
        } else {
            if (mute_pkt_size[1] < size) {
                ring_buffer_read(&usb_tx_ring_buffer[1], NULL, mute_pkt_size[1]);
                mute_pkt_size[1] = 0;
            }
        }
    }
    if (auto_buffer_recover_en[1]) {
        size = ring_buffer_bytes_used(&usb_tx_ring_buffer[1]);
        dbg("0 auto_mute_pkt_size %d/%d\n",auto_mute_pkt_size[1],size);
        if(auto_mute_pkt_size[1]< size){
            auto_buffer_recover_en[1] = false;
            ring_buffer_read(&usb_tx_ring_buffer[1], NULL, auto_mute_pkt_size[1]);
            auto_mute_pkt_size[1] = 0;
        }else{
            do_it = false;
        }
    }
    size = ring_buffer_bytes_used(&usb_tx_ring_buffer[1]);
    p_s3 = size;
    GLOBAL_INT_RESTORE();
    dbg("1 size %d/%d,pkt %d,m %d,d %d\n",p_s0,p_s3,pkt_cnt[1],p_s1,p_s2);
    if(do_it){
        asio_dac_src_process(size,sync_size);
    }
    data_check_timer_started[1] = false;
    pkt_cnt[1] = 0;
}

static void sta_check_callback(void const *param)
{
    if (vif_mgmt_sta_cnt(0) == 0) {
        if (wifi_sta_connected_cnt > 0) {
            dbg("sta_disconnected,now=%d %d\n",rtos_now(false), wifi_sta_connected_cnt);
            wifi_voice_client_disconnected(10, false);

            //enter paring mode.
            if (dongle_led_handler) {
                dongle_led_handler(WIFI_VOICE_STA_PAIRING);
            }
        }
    } else {
        if ((wifi_sta_connected_cnt < vif_mgmt_sta_cnt(0)) && (get_client_ip_offered_cnt() == vif_mgmt_sta_cnt(0))) {
            dbg("sta_connected,now=%d\n",rtos_now(false));

            wifi_voice_msg_queue_write(WIFI_CLIENT_CONNECTED, 10, false);

            //enter paring mode.
            if (dongle_led_handler) {
                dongle_led_handler(WIFI_VOICE_STA_CONNECTED);
            }
        }
    }

    static uint8_t last_to_times = 0; // 1/10 TOs per 100ms
    if ((fhost_tx_get_to_times() - last_to_times) >= (wifi_sta_check_period_ms / d2h_air_pkt_size_ms / 10)) {
        wifi_voice_msg_queue_write(WIFI_SWITCH_CHANNEL, 10, false);
    }
    last_to_times = fhost_tx_get_to_times();
}

static void dongle_data_handler(uint8_t *data, uint32_t size, uint8_t index)
{
    //dbg("data@(%d): %02X %02X %02X %02X\n",size,data[0],data[1],data[2],data[3]);

    int rb_st;
    uint32_t bytes_used;
    uint32_t bytes_free;
    uint32_t write_len;
    uint32_t read_len;
    uint32_t drop_len;

    if(!usb_send_started)
        return;

#if 1
    if (usb_tx_ring_buffer_status[index] > USB_BUFFER_STATUS_RESTART)
    {
        if (!data_check_timer_started[index]) {
            if (0 == rtos_timer_start(data_check_timer[index], 0, false)) {
                data_check_timer_started[index] = true;
            }
        }
        pkt_cnt[index] ++;
    }
#endif
    GLOBAL_INT_DISABLE();
    if (usb_tx_ring_buffer_status[index] >= USB_BUFFER_STATUS_START) {
        rb_st = ring_buffer_write(&usb_tx_ring_buffer[index], (uint8_t *)data, size);
        //dbg("size %d, t %d\n", ring_buffer_bytes_used(&usb_tx_ring_buffer),rtos_now(false));
        if (RB_ERR_NONE != rb_st) {
            bytes_free = ring_buffer_bytes_free(&usb_tx_ring_buffer[index]);
            bytes_used = ring_buffer_bytes_used(&usb_tx_ring_buffer[index]);

            if (usb_tx_ring_buffer[index].size <= size) {
                read_len = bytes_used;
                write_len = usb_tx_ring_buffer[index].size;
                drop_len = read_len + size - usb_tx_ring_buffer[index].size;
            } else {
                read_len = size - bytes_free;
                write_len = size;
                drop_len = read_len;
            }

            ring_buffer_read(&usb_tx_ring_buffer[index], NULL, read_len);
            ring_buffer_write(&usb_tx_ring_buffer[index], data, write_len);
            //usb tx buffer full
            dbg("UTF:%d/%d ,idx %d\n", size, drop_len,index);
            drop_pkt_size[index] += drop_len;
        }

        if (usb_tx_ring_buffer_status[index] == USB_BUFFER_STATUS_START || usb_tx_ring_buffer_status[index] == USB_BUFFER_STATUS_RESTART) {
            bytes_used = ring_buffer_bytes_used(&usb_tx_ring_buffer[index]);
            if (bytes_used >= usb_tx_start_level_size[index]) {
                usb_tx_ring_buffer_status[index] = USB_BUFFER_STATUS_REACH_THRESHOLD;
            }
        }
    } else {
        //usb tx stop, drop frame
        dbg("UTSP:%d ,idx %d\n", size,index);
    }
    GLOBAL_INT_RESTORE();
}

static void set_rx_itf_handler(enum usbd_audio_itf itf)
{
    dbg("rx_itf:%d\n", itf);
    if (itf == USBD_AUDIO_ITF_NONE) {
        usbd_audio_rxbuf_release();
        uint32_t frag_size = ring_buffer_bytes_used(&usb_rx_ring_buffer) % d2h_air_pkt_size;
        if (frag_size != 0) {
            wifi_voice_data_ready(0, true);
            usb_rx_pkt_cnt = 0;
        }
        wifi_voice_msg_queue_write(VOICE_USB_RECV_ITF_STOP, 0, true);
    } else {
        usbd_audio_rxbuf_config((uint8_t *)usb_rx_buffer, 0, usb_rx_buffer_size);
        wifi_voice_msg_queue_write(VOICE_USB_RECV_ITF_START, 0, true);
    }
}

static void set_tx_itf_handler(enum usbd_audio_itf itf)
{
    dbg("tx_itf:%d\n", itf);
    if (itf == USBD_AUDIO_ITF_NONE) {
        usbd_audio_txbuf_release();

        if (usb_send_started) {
            wifi_voice_msg_queue_write(VOICE_USB_SEND_ITF_STOP, 0, true);
            usb_send_started = false;
        }

        usb_tx_ring_buffer_status[0] = USB_BUFFER_STATUS_STOP;
        usb_tx_ring_buffer_status[1] = USB_BUFFER_STATUS_STOP;
    } else {
        memset(usb_tx_buffer, 0, usb_tx_buffer_size);

        usbd_audio_txbuf_config((uint8_t *)usb_tx_buffer, 0, usb_tx_buffer_size);
        //usb_tx_ring_buffer_status[0] = USB_BUFFER_STATUS_START;
        //usb_tx_ring_buffer_status[1] = USB_BUFFER_STATUS_START;
    }
}

static uint32_t w_cnt = 0;
static uint32_t r_cnt = 0;
static void data_rx_handler(const struct usbd_audio_data_xfer *xfer)
{
    //dbg("data:%p,recv(%d):%02X,%02X,%02X,%02X\n",
    //    xfer->data, xfer->size, xfer->data[0], xfer->data[1], xfer->data[2], xfer->data[3]);
    //dbg("data:%p,recv(%d),now=%d\n",
    //    xfer->data, xfer->size, rtos_now(true));

    int rb_st = 0;
    static uint16_t consecutive_of_cnt = 0;
    rb_st = ring_buffer_write(&usb_rx_ring_buffer, (uint8_t *)xfer->data, xfer->size);
    if (RB_ERR_NONE != rb_st) {
        dbg("URF:%d/%d\n", ring_buffer_bytes_used(&usb_rx_ring_buffer), wifi_voice_msg_queue_cnt_get());
        dbg("w %d,r %d\n", w_cnt, r_cnt);
        rb_st = ring_buffer_read(&usb_rx_ring_buffer, NULL, xfer->size);
        rb_st = ring_buffer_write(&usb_rx_ring_buffer, (uint8_t *)xfer->data, xfer->size);
        consecutive_of_cnt++;
        if (consecutive_of_cnt == 20) {
            wifi_voice_msg_queue_write(WIFI_SWITCH_CHANNEL, 0, true);
        }
        if (consecutive_of_cnt == 300) {
            wifi_voice_client_disconnected(0, true);
        }
        return;
    }
    consecutive_of_cnt = 0;
    usb_rx_pkt_cnt++;
    if ((usb_rx_pkt_cnt * usb_audio_pkt_size) == d2h_air_pkt_size) {
        wifi_voice_data_ready(0, true);
        w_cnt++;
        usb_rx_pkt_cnt = 0;
    }

    wifi_voice_data_stop_check_timer_restart(0, true);
}

void data_tx_handler(const struct usbd_audio_data_xfer *xfer)
{
    uint32_t len_want = usb_tx_mix_buffer_size;
    int16_t *p_buffer = NULL;
    int16_t *buffer_0 = NULL;
    int16_t *buffer_1 = NULL;

    //dbg("data:%p,size:%d %d\n",xfer->data,xfer->size, rtos_now(true));

    if (!usb_send_started) {
        wifi_voice_msg_queue_write(VOICE_USB_SEND_ITF_START, 0, true);
        usb_send_started = true;
    }

    if (usb_tx_ring_buffer_status[0] < USB_BUFFER_STATUS_RESTART && (usb_tx_ring_buffer_status[1] < USB_BUFFER_STATUS_RESTART)) {
        memset((void *)xfer->data, 0, xfer->size);
        //usb tx buffer caching
        dbg("UTC\n");
        return;
    }

    if (usb_tx_ring_buffer_status[0] >= USB_BUFFER_STATUS_RESTART) {
        // audio mixing
        buffer_0 = (int16_t *)usb_tx_mix_buffer[0];
        //asio_dsd_out(0,(unsigned int *)buffer_0);
    }
    if (usb_tx_ring_buffer_status[1] >= USB_BUFFER_STATUS_RESTART) {
        // audio mixing
        buffer_1 = (int16_t *)usb_tx_mix_buffer[1];
        //asio_dsd_out(1,(unsigned int *)buffer_1);
    }

    if(buffer_0 && buffer_1){
        if(data_rx_done[0] && data_rx_done[1]){
            data_rx_done[0] = false;
            data_rx_done[1] = false;
            if (dongle_mix_handler) {
                uint8_t *input[VOICE_MAX_STREAMS];
                input[0] = (uint8_t *)buffer_0;
                input[1] = (uint8_t *)buffer_1;
                dongle_mix_handler(input, 2, headset_capture_out_ch_num, len_want, (uint8_t *)xfer->data);
            } else {
                p_buffer = (int16_t *)xfer->data;
                for (uint16_t i = 0; i < (len_want / 2); i++) {
                p_buffer[i] = (int16_t)(((int32_t)buffer_0[i] + (int32_t)buffer_1[i]) / 2);
                //dbg("%d,%d,%d\n", p_buffer[i], buffer_0[i], buffer_1[i]);
                }
            }
        }else{
            dbg("mix_rx err,%d,%d\n",data_rx_done[0],data_rx_done[1]);
            memset((void *)xfer->data, 0, xfer->size);
        }
    }else if(buffer_0){
        if(data_rx_done[0]){
            data_rx_done[0] = false;
            memcpy((void *)xfer->data,(void *)buffer_0,xfer->size);
        }else{
            dbg("0_rx err\n");
            memset((void *)xfer->data, 0, xfer->size);
        }
    }else if(buffer_1){
        if(data_rx_done[1]){
            data_rx_done[1] = false;
            memcpy((void *)xfer->data,(void *)buffer_1,xfer->size);
        }else{
            dbg("1_rx err\n");
            memset((void *)xfer->data, 0, xfer->size);
        }
    }else{
        ASSERT_ERR(0);
    }

    if (headset_mic_samprate != AUD_SAMPRATE_48000) {
        //TDOO, add SRC
    }

    if (usb_tx_ring_buffer_status[0] >= USB_BUFFER_STATUS_RESTART) {
        asio_dsd_out(0,(unsigned int *)buffer_0);
    }
    if (usb_tx_ring_buffer_status[1] >= USB_BUFFER_STATUS_RESTART) {
        asio_dsd_out(1,(unsigned int *)buffer_1);
    }
}
#if 0
static void data_tx_handler(const struct usbd_audio_data_xfer *xfer)
{
    uint32_t len_want = usb_tx_mix_buffer_size;
    uint32_t buffered_size_0, buffered_size_1;
    int16_t *p_buffer = NULL;
    int16_t *buffer_0 = (int16_t *)usb_tx_mix_buffer[0];
    int16_t *buffer_1 = (int16_t *)usb_tx_mix_buffer[1];

    //dbg("data:%p,size:%d %d\n",xfer->data,xfer->size, rtos_now(true));

    if (!usb_send_started) {
        wifi_voice_msg_queue_write(VOICE_USB_SEND_ITF_START, 0, true);
        usb_send_started = true;
    }

    if (usb_tx_ring_buffer_status[0] >= USB_BUFFER_STATUS_RESTART && (usb_tx_ring_buffer_status[1] >= USB_BUFFER_STATUS_RESTART)) {
        // audio mixing
        buffered_size_0 = ring_buffer_bytes_used(&usb_tx_ring_buffer[0]);
        buffered_size_1 = ring_buffer_bytes_used(&usb_tx_ring_buffer[1]);

        if ((buffered_size_0 >= len_want) || (buffered_size_1 >= len_want)) {
            if((buffered_size_0 >= len_want) && (buffered_size_1 >= len_want)) {
                ring_buffer_read(&usb_tx_ring_buffer[0], (uint8_t *)buffer_0, len_want);
                ring_buffer_read(&usb_tx_ring_buffer[1], (uint8_t *)buffer_1, len_want);
                if (dongle_mix_handler) {
                    uint8_t *input[VOICE_MAX_STREAMS];
                    input[0] = (uint8_t *)buffer_0;
                    input[1] = (uint8_t *)buffer_1;
                    dongle_mix_handler(input, 2, headset_capture_out_ch_num, len_want, (uint8_t *)xfer->data);
                } else {
                    p_buffer = (int16_t *)xfer->data;
                    for (uint16_t i = 0; i < (len_want / 2); i++) {
                        p_buffer[i] = (int16_t)(((int32_t)buffer_0[i] + (int32_t)buffer_1[i]) / 2);
                        //dbg("%d,%d,%d\n", p_buffer[i], buffer_0[i], buffer_1[i]);
                    }
                }
            } else if(buffered_size_0 >= len_want) {
                asio_dsd_out(0,xfer->data);
            } else if(buffered_size_1 >= len_want) {
                //ring_buffer_read(&usb_tx_ring_buffer[1], (uint8_t *)xfer->data, len_want);
                asio_dsd_out(1,xfer->data);
            }

            if (headset_mic_samprate != AUD_SAMPRATE_48000) {
                //TDOO, add SRC
            }

            if (headset_capture_out_ch_num == AUD_CH_NUM_1) {
                // Convert mono data to stereo data
                audio_channel_copy_16bits((int16_t *)xfer->data, (int16_t *)xfer->data, (xfer->size / 2));
            }
        } else {
            memset((void *)xfer->data, 0, xfer->size);
            //usb tx buffer empty
            dbg("UTE\n");
            mute_pkt_size += usb_audio_pkt_size;
        }
    } else if (usb_tx_ring_buffer_status[0] >= USB_BUFFER_STATUS_RESTART) {
        // audio mixing
        buffered_size_0 = ring_buffer_bytes_used(&usb_tx_ring_buffer[0]);

        if ((buffered_size_0 >= len_want) ) {
            if(buffered_size_0 >= len_want) {
                asio_dsd_out(0,xfer->data);
            }

            if (headset_mic_samprate != AUD_SAMPRATE_48000) {
                //TDOO, add SRC
            }
        } else {
            memset((void *)xfer->data, 0, xfer->size);
            //usb tx buffer empty
            dbg("UTE\n");
            mute_pkt_size[0] += usb_audio_pkt_size;
        }
    } else if (usb_tx_ring_buffer_status[1] >= USB_BUFFER_STATUS_RESTART) {
        // audio mixing
        buffered_size_1 = ring_buffer_bytes_used(&usb_tx_ring_buffer[1]);

        if ((buffered_size_1 >= len_want)) {
            if(buffered_size_1 >= len_want) {
                //ring_buffer_read(&usb_tx_ring_buffer[1], (uint8_t *)xfer->data, len_want);
                asio_dsd_out(1,xfer->data);
            }

            if (headset_mic_samprate != AUD_SAMPRATE_48000) {
                //TDOO, add SRC
            }
        } else {
            memset((void *)xfer->data, 0, xfer->size);
            //usb tx buffer empty
            dbg("UTE\n");
            mute_pkt_size[1] += usb_audio_pkt_size;
        }
    } else {
        memset((void *)xfer->data, 0, xfer->size);
        //usb tx buffer caching
        dbg("UTC\n");
    }
}
#endif
static void set_volume_handler(uint32_t percent)
{
    dbg("set_volume_handler, percent:%d\n", percent);
}

static struct usbd_audio_cfg usb_audio_cfg = {
    .rx_sampling_freq = CURRENT_AUD_SAMPRATE,
    .tx_sampling_freq = CURRENT_AUD_SAMPRATE,
    .set_rx_itf = set_rx_itf_handler,
    .set_tx_itf = set_tx_itf_handler,
    .data_rx_done = data_rx_handler,
    .data_tx_done = data_tx_handler,
    .set_volume = set_volume_handler,
};

static RTOS_TASK_FCT(dongle_task)
{
    struct wifi_voice_settings settings;
    uint8_t *send_buf  = NULL;
    char ssid[32] = {0};
    char pw[64]   = {0};

    do {
        bool em_status = false;
        uint32_t msg;
        static bool usb_initialized = 0;
        uint16_t bcn_interval = wifi_wh_config_bcn_interval_get();

        set_ap_allow_sta_inactivity_s(2);
        set_ap_bcn_interval(bcn_interval);
        #ifdef CFG_WIFI_ENGINEERING_MODE
        em_status = wifi_engineering_mode_status_get();
        #endif
        if (!em_status) {
            uint8_t ch_num = wifi_wh_config_channel_get();
            set_ap_channel_num(ch_num);
        }
        set_mac_address(wifi_wh_config_dongle_mac_addr_get());
        user_limit_sta_num_set(wifi_wh_config_headset_num_get());
        set_ap_enable_he_rate(1);
        wlan_ap_generate_ssid_pw_for_pairing((char *)ssid, (char *)pw);
        int ret = wlan_start_ap(wifi_wh_config_band_get(), (uint8_t *)ssid, (uint8_t *)pw);
        if (ret) {
            dbg("AP start err: %d\n", ret);
            break;
        }
        dbg("AP started, client mode\n");

        //enter paring mode.
        if (dongle_led_handler) {
            dongle_led_handler(WIFI_VOICE_STA_PAIRING);
        }
        send_buf = rtos_malloc(d2h_air_pkt_size);
        if (!send_buf) {
            dbg("ERR: send buf malloc fail\n");
            break;
        }

        rtos_timer_start(wifi_sta_check_timer, 0, false);

        wifi_voice_data_handler_register(dongle_data_handler);

        memset(&settings, 0, sizeof(struct wifi_voice_settings));
        settings.role = WIFI_VOICE_ROLE_DONGLE;
        settings.is_server = false;
        settings.pl_size = d2h_air_pkt_size;
        wifi_voice_task_init(&settings);

        while (1) {
            wifi_voice_msg_queue_read(&msg, -1, false);
            //dbg("msg %x\n", msg);
            switch (msg) {
            case WIFI_CLIENT_CONNECTED: {
                struct wifi_voice_stream_t *stream = wifi_voice_find_free_stream();
                if (!stream) {
                    dbg("ERR: No free stream\n");
                    break;
                }
                uint32_t sta_ip = get_client_ip_by_index(stream->strm_id);
                settings.stream_addr = sta_ip;
                wifi_sta_connected_cnt++;
                #if USB_AUDIO_DATA_EN
                if (!usb_initialized) {
                    usbd_audio_init(&usb_audio_cfg);
                    usb_initialized = true;
                }
                #endif

                if (user_limit_sta_num_get() == wifi_sta_connected_cnt) {
                    fhost_tx_cntrl_by_timer((bcn_interval / d2h_air_pkt_size_ms * d2h_air_pkt_size_ms), (bcn_interval / d2h_air_pkt_size_ms));
                }

                wifi_voice_stream_start(&settings);
                break;
            }
            case WIFI_CLIENT_DISCONNECTED: {
                rtos_timer_stop(wifi_sta_check_timer, 0);
                if (wifi_sta_connected_cnt > 0) {
                    wifi_voice_stream_stop();
                    wifi_sta_connected_cnt = 0;
                    rtos_timer_start(wifi_sta_check_timer, 0, 0);

                    if (usb_initialized) {
                        GLOBAL_INT_DISABLE();
                        ring_buffer_reset(&usb_rx_ring_buffer);
                        GLOBAL_INT_RESTORE();
                        usbd_audio_deinit();
                        usb_initialized = false;
                        usb_send_started = false;
                        start_playback_sent = false;
                        start_capture_sent = false;
                    }
                }
                fhost_stop_tx_cntrl_by_timer();
                break;
            }
            case WIFI_CLIENT_DECREASE: {
                if (wifi_sta_connected_cnt > 0) {
                    wifi_sta_connected_cnt --;
                    if (0 == wifi_sta_connected_cnt) {
                        GLOBAL_INT_DISABLE();
                        ring_buffer_reset(&usb_rx_ring_buffer);
                        GLOBAL_INT_RESTORE();
                        usbd_audio_deinit();
                        usb_initialized = false;
                        usb_send_started = false;
                        start_playback_sent = false;
                        start_capture_sent = false;
                    }
                }
                fhost_stop_tx_cntrl_by_timer();
                break;
            }
            case VOICE_DATA_READY: {
                if (wifi_sta_connected_cnt > 0) {
                    r_cnt++;
                    #if USB_AUDIO_DATA_EN
                    uint32_t ready_data_len = d2h_air_pkt_size;
                    uint32_t bytes_used;
                    GLOBAL_INT_DISABLE();
                    bytes_used = ring_buffer_bytes_used(&usb_rx_ring_buffer);
                    if (bytes_used < d2h_air_pkt_size) {
                        ready_data_len = bytes_used;
                    }
                    ring_buffer_read(&usb_rx_ring_buffer, send_buf, ready_data_len);
                    GLOBAL_INT_RESTORE();
                    if (ready_data_len != 0) {
                        client_send_voice_packets(send_buf, ready_data_len);
                    }
                    if (bytes_used < d2h_air_pkt_size) {
                        dbg("URE:%d/%d\n", d2h_air_pkt_size, ready_data_len);
                    }
                    #endif
                }
                break;
            }
            case WIFI_SWITCH_CHANNEL: {
                wifi_voice_switch_channel(wifi_wh_config_band_get(), false);
                break;
            }
            case VOICE_USB_RECV_ITF_START: {
                if (wifi_sta_connected_cnt > 0) {
                    dbg("VOICE_USB_RECV_ITF_START\n");
                    if (start_playback_sent == false) {
                        start_playback_sent = true;
                    }
                }
                break;
            }
            case VOICE_USB_RECV_ITF_STOP: {
                if (wifi_sta_connected_cnt > 0) {
                    dbg("VOICE_USB_RECV_ITF_STOP\n");
                    GLOBAL_INT_DISABLE();
                    ring_buffer_reset(&usb_rx_ring_buffer);
                    GLOBAL_INT_RESTORE();
                    if (start_playback_sent == true) {
                        wifi_voice_send_sys_cmd(VOICE_CMD_STOP_PLAYBACK);
                        start_playback_sent = false;
                    }
                }
                break;
            }
            case VOICE_USB_SEND_ITF_START: {
                if (wifi_sta_connected_cnt > 0) {
                    if (start_capture_sent == false) {
                        wifi_voice_send_sys_cmd(VOICE_CMD_START_CAPTURE);
                        start_capture_sent = true;
                        for (uint8_t i = 0; i < wifi_wh_config_headset_num_get(); i++) {
                            ring_buffer_reset(&usb_tx_ring_buffer[i]);
                        }
                        asio_adc_src_init();
                        asio_src_set_sft_dpll_param_in_diffmode(AUD_DPLL_TWS);
                        asio_src_frac_src_init();
                        asio_src_set_dpll_param_in_diffmode(AUD_DPLL_TWS);
                        data_param_clean();
                        usb_tx_ring_buffer_status[0] = USB_BUFFER_STATUS_START;
                        usb_tx_ring_buffer_status[1] = USB_BUFFER_STATUS_START;
                    }
                }
                break;
            }
            case VOICE_USB_SEND_ITF_STOP: {
                if (wifi_sta_connected_cnt > 0) {
                    if (start_capture_sent == true) {
                        wifi_voice_send_sys_cmd(VOICE_CMD_STOP_CAPTURE);
                        start_capture_sent = false;
                        asio_adc_src_clear();
                        asio_src_sft_dpll_clear();
                        asio_dsd_cnt_clean();
                        asio_src_frac_src_clear();
                    }
                }
                break;
            }
            #if 0
            case VOICE_SOCK_DISCONNECTED: {
                if (client_sock_connected) {
                    client_sock_connected = 0;
                    dbg("VOICE_SOCK_DISCONNECTED \n");

                    // reset usb rx data buffer
                    GLOBAL_INT_DISABLE();
                    ring_buffer_reset(&usb_rx_ring_buffer);
                    GLOBAL_INT_RESTORE();
                }
                break;
            }
            #endif
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
    wifi_wh_dongle_deinit();
    rtos_task_delete(NULL);
}


/*
 * Dongle USB RX PKT--->Dongle USB RX ring buffer--->H2D AIR PKT--->Headset playback ring buffer--->Headset playback asio buffer
 * Headset capture asio buffer--->Headset capture ring buffer--->D2H AIR PKT--->Dongle USB TX ring buffer--->Dongle USB TX PKT
 */
int wifi_wh_dongle_init(void)
{
    usb_audio_pkt_size = wifi_wh_config_usb_audio_pkt_size_get();
    d2h_air_pkt_size_ms = wifi_wh_config_d2h_air_pkt_size_ms_get();
    d2h_air_pkt_size = wifi_wh_config_d2h_air_pkt_size_get();
    usb_rx_ring_buffer_size = wifi_wh_config_usb_rx_ring_buffer_size_get();
    usb_tx_ring_buffer_size = wifi_wh_config_usb_tx_ring_buffer_size_get();
    usb_tx_start_level_size[0] = wifi_wh_config_usb_tx_start_level_size_get();
    usb_tx_start_level_size[1] = wifi_wh_config_usb_tx_start_level_size_get();
    usb_tx_ring_buffer_status[0] = USB_BUFFER_STATUS_STOP;
    usb_tx_ring_buffer_status[1] = USB_BUFFER_STATUS_STOP;
    headset_mic_samprate = wifi_wh_config_headset_mic_samprate_get();
    headset_capture_out_ch_num = wifi_wh_config_headset_capture_out_ch_num_get();
    wifi_sta_check_period_ms = wifi_wh_config_sta_check_period_ms_get();

    usb_dsd_buffer[0] = rtos_malloc(usb_audio_pkt_size*7);
    usb_dsd_buffer[1] = rtos_malloc(usb_audio_pkt_size*7);
    usb_dsd_buffer[2] = rtos_malloc(usb_audio_pkt_size*7);
    usb_dsd_buffer[3] = rtos_malloc(usb_audio_pkt_size*7);
    if (!usb_dsd_buffer[0]||!usb_dsd_buffer[1]||!usb_dsd_buffer[2]||!usb_dsd_buffer[3]) {
        dbg("ERR: usb_rx_buffer malloc fail\n");
        return -1;
    } else {
        dbg("dsd buff len %d\n",usb_audio_pkt_size*7);
    }
    asio_dsd_init((unsigned int *)usb_dsd_buffer[0],(unsigned int *)usb_dsd_buffer[1],
                  (unsigned int *)usb_dsd_buffer[2],(unsigned int *)usb_dsd_buffer[3]);

    usb_tx_mix_buffer_size = 1 * headset_mic_samprate / 1000 * headset_capture_out_ch_num * sizeof(int16_t);

    wifi_sta_check_timer = rtos_timer_create("sta_check_timer", pdMS_TO_TICKS(wifi_sta_check_period_ms), pdTRUE, NULL,
                                              (TimerCallbackFunction_t)sta_check_callback);
    if (!wifi_sta_check_timer) {
        dbg("ERR: wifi_sta_check_timer create fail\n");
        return -1;
    }

    usb_rx_buffer_size = 2 * usb_audio_pkt_size;
    usb_tx_buffer_size = 2 * usb_audio_pkt_size;

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

    usb_rx_ring_buffer_storage = rtos_malloc(usb_rx_ring_buffer_size);
    if (!usb_rx_ring_buffer_storage) {
        dbg("ERR: usb_rx_ring_buffer_storage malloc fail\n");
        return -1;
    }
    ring_buffer_init(&usb_rx_ring_buffer, usb_rx_ring_buffer_storage, usb_rx_ring_buffer_size);
    dbg("usb_rx_ring_buffer_storage %x\n", usb_rx_ring_buffer_storage);

    for (uint8_t i = 0; i < wifi_wh_config_headset_num_get(); i++) {
        usb_tx_ring_buffer_storage[i] = rtos_malloc(usb_tx_ring_buffer_size);
        if (!usb_tx_ring_buffer_storage[i]) {
            dbg("ERR: usb_tx_ring_buffer_storage[%d] malloc fail\n", i);
            return -1;
        }
        ring_buffer_init(&usb_tx_ring_buffer[i], usb_tx_ring_buffer_storage[i], usb_tx_ring_buffer_size);

        usb_tx_mix_buffer[i] = rtos_malloc(usb_tx_mix_buffer_size);
        if (!usb_tx_mix_buffer[i]) {
            dbg("ERR: usb_tx_mix_buffer[%d] malloc fail\n", i);
            return -1;
        }
    }
    asio_dsd_tx_cb_register(0,data0_tx_asio_dsd_cb);
    asio_dsd_tx_cb_register(1,data1_tx_asio_dsd_cb);
    asio_dsd_rx_cb_register(0,data0_rx_asio_dsd_cb);
    asio_dsd_rx_cb_register(1,data1_rx_asio_dsd_cb);

#if 1
    data_check_timer[0] = rtos_timer_create("data0_check_timer", pdMS_TO_TICKS(4), pdFALSE, NULL,
                                              (TimerCallbackFunction_t)data0_check_callback);
    if (!data_check_timer[0]) {
        dbg("ERR: data0_check_timer create fail\n");
        return -1;
    }
    data_check_timer[1] = rtos_timer_create("data1_check_timer", pdMS_TO_TICKS(4), pdFALSE, NULL,
                                              (TimerCallbackFunction_t)data1_check_callback);
    if (!data_check_timer[1]) {
        dbg("ERR: data1_check_timer create fail\n");
        return -1;
    }
#endif
    if (rtos_task_create(dongle_task, "dongle task", APPLICATION_TASK,
                         TASK_STACK_SIZE_WIFI_VOICE, NULL, TASK_PRIORITY_WIFI_VOICE, &dongle_task_handle)) {
        dbg("ERR: dongle task create fail\n");
        return -1;
    }

    return 0;
}

int wifi_wh_dongle_deinit(void)
{
    if (wifi_sta_check_timer) {
        rtos_timer_delete(wifi_sta_check_timer, 0);
        wifi_sta_check_timer = NULL;
    }

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

    for (uint8_t i = 0; i < wifi_wh_config_headset_num_get(); i++) {
        ring_buffer_deinit(&usb_tx_ring_buffer[i]);
        if (usb_tx_ring_buffer_storage[i]) {
            rtos_free(usb_tx_ring_buffer_storage[i]);
            usb_tx_ring_buffer_storage[i] = NULL;
        }

        if (usb_tx_mix_buffer[i]) {
            rtos_free(usb_tx_mix_buffer[i]);
            usb_tx_mix_buffer[i] = NULL;
        }
    }

    if (usb_dsd_buffer[0]) {
        rtos_free(usb_dsd_buffer[0]);
        usb_dsd_buffer[0] = NULL;
    }
    if (usb_dsd_buffer[1]) {
        rtos_free(usb_dsd_buffer[1]);
        usb_dsd_buffer[1] = NULL;
    }
    if (data_check_timer[0]) {
        rtos_timer_delete(data_check_timer[0], 0);
        data_check_timer[0] = NULL;
    }
    if (data_check_timer[1]) {
        rtos_timer_delete(data_check_timer[1], 0);
        data_check_timer[1] = NULL;
    }
    return 0;
}
#endif
