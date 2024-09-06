#ifndef __APP_SPP_H__
#define __APP_SPP_H__
#if APP_SUPPORT_SPP == 1

#include "aic_adp_api.h"


typedef void(*app_spp_tx_done_t)(uint8_t);
void app_spp_register_tx_done(app_spp_tx_done_t callback);
void app_spp_msg_handle(AIC_EVENT *event);
void app_spp_connect(uint8_t index, BT_ADDR * bdaddr);
void app_spp_send_data(uint8_t index, uint8_t* ptrData, uint16_t length);

#if MAX_THROUGHPUT_TEST == 1
void app_spp_connect_test(void);
void app_spp_send_test_data(uint8_t index);
#endif
void app_spp_init(void);
#endif
#endif
