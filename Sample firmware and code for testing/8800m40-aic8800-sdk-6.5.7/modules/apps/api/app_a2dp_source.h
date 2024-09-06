#ifndef _APP_A2DP_SOURCE_H_
#define _APP_A2DP_SOURCE_H_
#include "aic_adp_a2dp.h"

void app_a2dp_source_init(void);
void app_a2dp_source_start(void);
void app_a2dp_source_suspend(void);
void app_a2dp_source_sbc_data_send_timer_begin(void);
void app_a2dp_source_connect_default_device(void);
void app_bt_source_send_a2dp_test_sbc_packet(BT_ADDR default_device );

#endif
