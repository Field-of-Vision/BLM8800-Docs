#ifndef _APP_HFP_H_
#define _APP_HFP_H_
#if APP_SUPPORT_HFP == 1


typedef enum {
    APP_IDLE,
    APP_CONNECTED,
    APP_CALL_INCOMING,
    APP_CALL_OUTGOING,
    APP_CALL_ACTIVE,
    APP_VOICE_RECOGNITION,
    APP_PLAY_SCO,
}app_hfp_state_t;

#define HF_SENDBUFF_SIZE (320)
#define HF_SENDBUFF_MEMPOOL_NUM (2)

typedef struct {
    uint8_t buffer[HF_SENDBUFF_SIZE];
    uint16_t len;
}ScoSendData_t;

typedef struct {
    ScoSendData_t mempool[HF_SENDBUFF_MEMPOOL_NUM];
    uint8_t idx;
} HF_SENDBUFF_T;

void app_set_hfp_state(app_hfp_state_t state);
app_hfp_state_t app_get_hfp_state(void);
void app_set_hfp_scocodec(uint16_t scocodec);
uint16_t app_get_hfp_scocodec(void);
void app_set_hfp_volume(BT_ADDR *bdaddr,S8 volume);
S8 app_get_hfp_volume(BT_ADDR *bdaddr);
BOOL app_hfp_key_handle(uint32_t key);
void app_hfp_msg_handle(AIC_EVENT *event);
#endif
#endif
