#include "hw_cfg.h"
#include <string.h>
#include <stdint.h>
#include "gpio_api.h"
#include "pinname.h"
#include "dbg.h"
#include "rtos.h"

#if PLF_M2D_BLE
#define M2D_WAKEUP_GPIO  PIN_IDX(PB_3)
#define M2D_TRIGGER_PENDING_TIME  500//500ms

static TimerHandle_t m2d_trigger_timer = NULL;

static void m2d_trigger_timer_cb( TimerHandle_t xTimer )
{
    #if CONFIG_M2D_DEFAULT_PULLED_UP == 1
    gpiob_set(M2D_WAKEUP_GPIO);
    #else
    gpiob_clr(M2D_WAKEUP_GPIO);
    #endif
}

void m2d_wakeup_trigger(void)
{
    TRACE("gpiob set\n");
    TRACE("BLE: m2d trigger\n");
    #if CONFIG_M2D_DEFAULT_PULLED_UP == 1
    gpiob_clr(M2D_WAKEUP_GPIO); //low after trigger
    #else
    gpiob_set(M2D_WAKEUP_GPIO); // high after trigger
    #endif
    rtos_timer_change_period(m2d_trigger_timer, M2D_TRIGGER_PENDING_TIME, 1);
}
#endif

void hw_cfg_init(void)
{
#if PLF_M2D_BLE
    TRACE("%s\n",__func__);
    #if CONFIG_M2D_DEFAULT_PULLED_UP == 1
    gpiob_force_pull_up_enable(M2D_WAKEUP_GPIO);
    gpiob_init(M2D_WAKEUP_GPIO);
    gpiob_set(M2D_WAKEUP_GPIO); // high by default
    gpiob_dir_out(M2D_WAKEUP_GPIO);
    gpiob_set(M2D_WAKEUP_GPIO); // high by default
    #else
    gpiob_init(M2D_WAKEUP_GPIO);
    gpiob_clr(M2D_WAKEUP_GPIO); // low by default
    gpiob_dir_out(M2D_WAKEUP_GPIO);
    gpiob_clr(M2D_WAKEUP_GPIO); // low by default
    #endif
    if (m2d_trigger_timer == NULL){
        m2d_trigger_timer = rtos_timer_create("m2d_trigger_timer",\
                        M2D_TRIGGER_PENDING_TIME,pdFALSE,NULL,m2d_trigger_timer_cb);
    }
#endif
}
