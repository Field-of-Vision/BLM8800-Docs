#ifndef _APP_A2DP_H_
#define _APP_A2DP_H_
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC ==1 ||APP_SUPPORT_A2DP_SOURCE == 1


typedef enum {
    A2DP_IDLE,
    A2DP_CONNECTED,
    A2DP_PLAY,
}app_a2dp_state_t;

void app_a2dp_msg_handle(AIC_EVENT *event);
app_a2dp_state_t app_get_a2dp_state(void);
void app_set_a2dp_state(app_a2dp_state_t state);
void app_a2dp_pause(void);

#endif
#endif
