#include "rtos.h"
#include "gpio_api.h"
#include "light_sensor.h"
#include "lp_ticker_api.h"

#define LS_DEBUG_PRINTF(fmt, ...)       //dbg(fmt, ##__VA_ARGS__)
#define LS_VCC_GPIO_IDX                 PB_0//GPIOA2
#define LS_IO_GPIO_IDX                  PB_1//GPIOA1
#define LS_VOUT_GPIO_IDX                PB_4//GPIOA3
#define LS_ONCE_CHECK_NUM               1
#define LS_PERIOD_CHECK_TIME            400//ms
static ls_event_send_handler_t ls_evt_callback = NULL;
static co_timer *ls_timer = NULL;

static int ls_start_check(void)
{
    int ret = WEAR_ERROR;
    uint32_t check_num = LS_ONCE_CHECK_NUM;
    uint32_t val_check_1;
    uint32_t val_check_2;
    uint8_t vcc_pin_type = PIN_TYPE(LS_VCC_GPIO_IDX);
    uint8_t vcc_pin_idx = PIN_IDX(LS_VCC_GPIO_IDX);
    uint8_t io_pin_type = PIN_TYPE(LS_IO_GPIO_IDX);
    uint8_t io_pin_idx = PIN_IDX(LS_IO_GPIO_IDX);
    uint8_t vout_pin_type = PIN_TYPE(LS_VOUT_GPIO_IDX);
    uint8_t vout_pin_idx = PIN_IDX(LS_VOUT_GPIO_IDX);

    do{
        if (io_pin_type == PIN_TYPE_A) {
            gpioa_set(io_pin_idx);
        } else if (io_pin_type == PIN_TYPE_B) {
            gpiob_set(io_pin_idx);
        }
        if (vcc_pin_type == PIN_TYPE_A) {
            gpioa_set(vcc_pin_idx);
        } else if (vcc_pin_type == PIN_TYPE_B) {
            gpiob_set(vcc_pin_idx);
        }
        rtos_task_suspend(2);
        if (vout_pin_type == PIN_TYPE_A) {
            val_check_1 = gpioa_get(vout_pin_idx);
        } else if (vout_pin_type == PIN_TYPE_B) {
            val_check_1 = gpiob_get(vout_pin_idx);
        }
        if (io_pin_type == PIN_TYPE_A) {
            gpioa_clr(io_pin_idx);
        } else if (io_pin_type == PIN_TYPE_B) {
            gpiob_clr(io_pin_idx);
        }
        rtos_task_suspend(2);
        if (vout_pin_type == PIN_TYPE_A) {
            val_check_2 = gpioa_get(vout_pin_idx);
        } else if (vout_pin_type == PIN_TYPE_B) {
            val_check_2 = gpiob_get(vout_pin_idx);
        }
        LS_DEBUG_PRINTF("val 1 %x, 2 = %x\n",val_check_1,val_check_2);
        if (vcc_pin_type == PIN_TYPE_A) {
            gpioa_clr(vcc_pin_idx);
        } else if (vcc_pin_type == PIN_TYPE_B) {
            gpiob_clr(vcc_pin_idx);
        }
        if(val_check_1 == 0 && val_check_2 != 0){
            ret = HAVE_TO_WEAR;
            break;
        }else{
            ret = NOT_TO_WEAR;
        }
        rtos_task_suspend(2);
    }while(--check_num);

    return ret;
}

static void ls_timer_handler(void *cb_param)
{
    LS_DEBUG_PRINTF("%s \n",__func__);
    ls_send_start_check(LS_CHECK_ONCE,0);
}

static bool ls_handle_process(CO_EVENT *evt)
{
    int ret = WEAR_ERROR;
    static int last_ret = WEAR_ERROR;

    switch(evt->EvtId){
        case LS_CHECK_ONCE:
            ret = ls_start_check();
            break;
        case LS_CHECK_PERIOD:
            if(evt->Param){
                //stop timer
                if(ls_timer){
                    co_timer_stop(ls_timer);
                    ls_timer = NULL;
                }
            }else{
                //start timer
                if(ls_timer == NULL){
                    co_timer_start(&ls_timer,LS_PERIOD_CHECK_TIME,NULL,ls_timer_handler,1);
                    ret = ls_start_check();
                }
            }
            break;
        default:
            ASSERT_ERR(0);
            break;
    }
    LS_DEBUG_PRINTF("%s ,ret %x,last_ret %x\n",__func__,ret,last_ret);
    if(ret){
        if(last_ret == WEAR_ERROR || last_ret != ret){
            last_ret = ret;
            if(ls_evt_callback){
                if(ret == NOT_TO_WEAR){
                    ls_evt_callback(0);
                }else if(ret == HAVE_TO_WEAR){
                    ls_evt_callback(1);
                }
            }
        }
    }
    return 0;
}

void ls_send_start_check(LS_CHECK_MODE check_mode,uint32_t stop_period)
{
    int res = 0;
    CO_MODUAL_EVENT msg;
    msg.mod_id = CO_MODUAL_LIGHT_SENSOR;
    msg.mod_evt.EvtId = check_mode;
    msg.mod_evt.Param = stop_period;
    res = co_event_send(&msg, false);
    ASSERT_ERR(res == 0 || res == 1);
    LS_DEBUG_PRINTF("%s ,check_mode %x,stop_period %x\n",__func__,check_mode,stop_period);
}

void ls_register_evt_callback(ls_event_send_handler_t callback)
{
    LS_DEBUG_PRINTF("%s\n",__func__);
    ls_evt_callback = callback;
}

void ls_init(void)
{
    uint8_t pin_type = PIN_TYPE(LS_VCC_GPIO_IDX);
    uint8_t pin_idx = PIN_IDX(LS_VCC_GPIO_IDX);
    if (pin_type == PIN_TYPE_A) {
        gpioa_init(pin_idx);
        gpioa_dir_out(pin_idx);
    } else if (pin_type == PIN_TYPE_B) {
        gpiob_init(pin_idx);
        gpiob_dir_out(pin_idx);
    }
    pin_type = PIN_TYPE(LS_IO_GPIO_IDX);
    pin_idx = PIN_IDX(LS_IO_GPIO_IDX);
    if (pin_type == PIN_TYPE_A) {
        gpioa_init(pin_idx);
        gpioa_dir_out(pin_idx);
    } else if (pin_type == PIN_TYPE_B) {
        gpiob_init(pin_idx);
        gpiob_dir_out(pin_idx);
    }
    pin_type = PIN_TYPE(LS_VOUT_GPIO_IDX);
    pin_idx = PIN_IDX(LS_VOUT_GPIO_IDX);
    if (pin_type == PIN_TYPE_A) {
        gpioa_init(pin_idx);
        gpioa_dir_in(pin_idx);
    } else if (pin_type == PIN_TYPE_B) {
        gpiob_init(pin_idx);
        gpiob_dir_in(pin_idx);
    }
    co_main_evt_handler_rigister(CO_MODUAL_LIGHT_SENSOR, ls_handle_process);
}
