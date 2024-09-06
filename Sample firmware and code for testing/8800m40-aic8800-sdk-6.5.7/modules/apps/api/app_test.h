#ifndef APPTEST_H
#define APPTEST_H
#include "tgt_cfg_bt.h"

#if SCO_CVSD_PLC_TEST == 1

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

extern TimerHandle_t connect_sco_timer;

void app_test_msg_handle(AIC_EVENT *event);
void app_test_connect_default(void);
void app_test_connect_sco( TimerHandle_t xTimer );


#endif
#endif
