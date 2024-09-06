#ifndef AICADPHID
#define AICADPHID

#include "bt_types_def.h"


typedef U8 bt_hid_adp_state;
#define HID_ADP_STATE_IDLE                    0
#define HID_ADP_STATE_PENDING                 1
#define HID_ADP_STATE_CONNECTED               2


typedef struct _AIC_ADP_HID_EVENT_{
    BT_ADDR bdaddr;
    U32 hidparam;
}AIC_ADP_HID_EVENT;


void aic_adp_hid_register(   void);

#endif
