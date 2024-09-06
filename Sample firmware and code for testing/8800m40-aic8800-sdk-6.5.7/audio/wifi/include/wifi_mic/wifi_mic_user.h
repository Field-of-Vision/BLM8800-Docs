#ifndef WIFI_MIC_USER_H
#define WIFI_MIC_USER_H

enum {
    WIFI_MIC_USER_MSG_KEY = 0,
};

typedef struct {
    uint32_t msg_id;
    union {
        uint32_t key_id;
    };
} wifi_mic_user_msg_t;

void wifi_mic_send_user_cmd(uint8_t cmd);
int wifi_mic_rx_user_init(void);
int wifi_mic_tx_user_init(void);
int wifi_mic_rx_user_deinit(void);
int wifi_mic_tx_user_deinit(void);

#endif
