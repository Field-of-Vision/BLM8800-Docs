#ifndef WIFI_WH_USER_H
#define WIFI_WH_USER_H

enum {
    WIFI_WH_USER_MSG_KEY = 0,
};

typedef struct {
    uint32_t msg_id;
    union {
        uint32_t key_id;
    };
} wifi_wh_user_msg_t;

void wifi_wh_send_user_cmd(uint8_t cmd);
int wifi_wh_dongle_user_init(void);
int wifi_wh_headset_user_init(void);
int wifi_wh_dongle_user_deinit(void);
int wifi_wh_headset_user_deinit(void);

#endif
