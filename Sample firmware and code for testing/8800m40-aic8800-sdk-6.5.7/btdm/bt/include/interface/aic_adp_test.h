#ifndef AICADPTEST
#define AICADPTEST
#include "aic_adp_hfp.h"
typedef struct _AIC_ADP_TEST_EVENT_{
    BT_ADDR bdaddr;
    U32 testparam;
}AIC_ADP_TEST_EVENT;

typedef struct
{
    U8*     txbuf;
    U16     len;
} TestTxDone;

typedef struct
{
    U8*     rxbuf;
    U16     len;
} TestRxDone;

void aic_adp_test_init(void);
void aic_adp_test_send_sco_data(AIC_ADP_HFP_AUDIO_DATA *buffer);
void aic_adp_test_connect(BT_ADDR *Addr);
void aic_adp_test_disconnect(void);
void aic_adp_test_connect_sco(void);
Status_BTDef aic_adp_test_send_data(U8 *data, U16 len, U8 header);

#endif
