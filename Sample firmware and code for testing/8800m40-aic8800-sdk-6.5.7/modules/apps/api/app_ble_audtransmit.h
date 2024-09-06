#ifndef APP_BLE_AUDTRANSMIT_H_
#define APP_BLE_AUDTRANSMIT_H_
#if (BLE_APP_AUDTRANSMITS || BLE_APP_AUDTRANSMITC)

enum codec_state {
    STATE_IDLE,
    STATE_PLAY,
};

struct aud_state_t {
    uint16_t codec_type;
    enum codec_state state;
};

#define BLE_SENDBUFF_SIZE                240
#define BLE_SENDBUFF_MEMPOOL_NUM         1
#define BLE_DATA_SEND_TIME_INTERVAL      28//29ms


typedef struct {
    uint8_t buffer[BLE_SENDBUFF_SIZE];
    uint16_t len;
}BleSendData_t;

typedef struct {
    BleSendData_t mempool[BLE_SENDBUFF_MEMPOOL_NUM];
    uint8_t idx;
    uint8_t buff_count;
} BleBuff_t;

void app_ble_audtransmit_init(void);
void app_ble_audtransmit_timer_notify_handler(void);
void app_ble_aud_stop(void);

#if BLE_APP_AUDTRANSMITS
void app_ats_send_aud_data(void);
void app_ats_send_aud_info(uint16_t codec_type,uint8_t state);
#endif

#if BLE_APP_AUDTRANSMITC
void app_atc_send_aud_data(void);
void app_atc_send_aud_ctrl(uint16_t codec_type,uint8_t state);
#endif
#endif
#endif
