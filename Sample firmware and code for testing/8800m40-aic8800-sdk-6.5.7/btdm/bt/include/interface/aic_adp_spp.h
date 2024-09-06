#ifndef _AIC_ADP_SPP_H_
#define _AIC_ADP_SPP_H_
#include"bt_types_def.h"
#include "aic_adp_dev.h"

typedef struct _AIC_ADP_SPP_EVENT_{
    BT_ADDR bdaddr;
    U8 conidx;
    U32 sppparam[LINK_MAX];
    U32 sppparam1;
}AIC_ADP_SPP_EVENT;


typedef struct
{
    U8*     pTxBuf;
    U16     txDataLength;
} adpspptxdone;

typedef struct
{
    U8*     pRxBuf;
    U16     RxDataLength;
} adpspprxdone;


void aic_adp_spp_init(void);
void aic_adp_spp_connect(uint8_t index, BT_ADDR * bdaddr);
void aic_adp_spp_send_data(uint8_t index, uint8_t* ptrData, uint16_t length);
void aic_adp_spp_given_the_credit(uint8_t index, uint8_t credit);
void aic_adp_spp_set_initial_rx_credit(uint8_t credit);
#endif
