#ifndef _APP_HSP_H_
#define _APP_HSP_H_
#if APP_SUPPORT_HSP == 1 

typedef enum {
    HS_IDLE,
    HS_CONNECTED,
    HS_PLAY_SCO,
}app_hsp_state_t;

void app_hsp_msg_handle(AIC_EVENT *event);
#endif
#endif
