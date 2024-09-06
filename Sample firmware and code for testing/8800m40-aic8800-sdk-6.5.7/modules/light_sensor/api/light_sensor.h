#ifndef __LED_H__
#define  __LED_H__
#include "co_main.h"

typedef int (*ls_event_send_handler_t)(uint32_t event);

enum WEAR_STATE{
    WEAR_ERROR = 0,
    NOT_TO_WEAR,
    HAVE_TO_WEAR,
};

typedef enum {
    LS_CHECK_ONCE = 1,
    LS_CHECK_PERIOD,
} LS_CHECK_MODE;


void ls_send_start_check(LS_CHECK_MODE check_mode,uint32_t stop_period);
void ls_register_evt_callback(ls_event_send_handler_t callback);
void ls_init(void);
#endif
