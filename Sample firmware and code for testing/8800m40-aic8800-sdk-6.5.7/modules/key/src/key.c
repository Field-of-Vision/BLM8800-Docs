#include "rtos.h"
#include "pmic_api.h"
#include "co_message.h"
#include "key.h"
#include "lp_ticker_api.h"
#include "dbg.h"
#include "dbg_assert.h"
#include "pwrkey_api.h"
#include "co_main.h"
#include "gpio_api.h"

#if PLF_BT_STACK
#if PLF_BLE_ONLY == 0
#include "app_bt_queue.h"
#endif
#endif
enum {
    KEY_DOWN,
    KEY_UP,
    KEY_POWERON
};
#define KEY_DEBUG_PRINTF(fmt, ...)       //dbg(fmt, ##__VA_ARGS__)
#define HW_ANTI_SHAKE_TIME               100  //ms

static KEY_CONFIG key_config;
static uint8_t gpio_key_status[MAX_GPIO_KEY_REG_LIST_NUM] = {0,};

static TimerHandle_t key_timer = NULL;
static uint32_t key_timer_param;
static TimerHandle_t multiclick_key_timer = NULL;
static uint32_t multiclick_key_timer_param;
static uint8_t key_hold_state = 0;
static uint32_t key_hold_time = 0;
static uint32_t key_times_down = 0;
static uint32_t key_times_up = 0;
static uint8_t multiclick_key_cnt = 0;
static enum PWR_DOWN_STATE pwrdown_state = DEFAULT_POWER_DOWN;
const uint32_t key_board_bond[] = KEY_BOARD_BONDING;

extern int pwrkey_released;
extern uint32_t pwrkey_ponchk_time_ms;
#if 0
unsigned int user_pwrkey_poweron_time_get(void)
{
    return KEY_DEFAULT_POWERON_TIME;
}

unsigned int user_pwrkey_poweroff_time_get(void)
{
    return (KEY_DEFAULT_POWEROFF_TIME+100);//add 100ms for wait app that can handle POWERDOWN msg.
}
#endif
void pwrdown_set_state(enum PWR_DOWN_STATE state)
{
    pwrdown_state = state;
}

enum PWR_DOWN_STATE pwrdown_get_state(void)
{
    return pwrdown_state;
}

static uint8_t key_board_get_bondid_by_value(uint32_t value)
{
    uint8_t bond_id = 0xff;
    for(uint8_t i = 0;i< (sizeof(key_board_bond)/4);i++){
        if(value == key_board_bond[i]){
            bond_id = i;
            break;
        }
    }
    return bond_id;
}

static uint32_t key_board_get_value_by_pin_name(PinName pin_name)
{
    uint8_t bond_id = 0xff;

    for(uint8_t i = 0; i < key_config.reg_bond_len; i++){
        if(pin_name == key_config.reg_key_bond_id[i].pin_name && key_config.reg_key_bond_id[i].key_name_bond_id){
            bond_id = key_config.reg_key_bond_id[i].key_name_bond_id;
            break;
        }
    }
    if(bond_id == 0xff){
        ASSERT_ERR(0);
    }
    if(bond_id >= (sizeof(key_board_bond)/4)){
        ASSERT_ERR(0);
    }
    return key_board_bond[bond_id];
}

static uint32_t key_get_hold_type_by_pin_name(PinName pin_name)
{
    uint32_t hold_type = APP_KEY_PRESS;
    for(uint8_t i = 0; i < key_config.reg_bond_len; i++){
        if(pin_name == key_config.reg_key_bond_id[i].pin_name && key_config.reg_key_bond_id[i].key_max_hold_type){
            hold_type = key_config.reg_key_bond_id[i].key_max_hold_type;
            break;
        }
    }
    return hold_type;
}

static uint32_t key_get_max_click_num_by_pin_name(PinName pin_name)
{
    uint32_t max_click_num = 1;
    for(uint8_t i = 0; i < key_config.reg_bond_len; i++){
        if(pin_name == key_config.reg_key_bond_id[i].pin_name && key_config.reg_key_bond_id[i].key_max_click_num){
            max_click_num = key_config.reg_key_bond_id[i].key_max_click_num;
            break;
        }
    }
    return max_click_num;
}

static enum FILTER_TYPE key_get_soft_filter_by_pin_name(PinName pin_name)
{
    enum FILTER_TYPE filter_type = HW_FILTER;
    for(uint8_t i = 0; i < key_config.reg_bond_len; i++){
        if(pin_name == key_config.reg_key_bond_id[i].pin_name){
            filter_type = key_config.reg_key_bond_id[i].soft_filter;
            break;
        }
    }
    return filter_type;
}

/*
    return ms
*/
static uint32_t key_get_interval_by_type(uint32_t type)
{
    uint32_t intarval = 0;
    switch(type) {
        case APP_KEY_PRESS:
            intarval = KEY_HOLD_200_MS;
            break;
        case APP_KEY_HOLD_2S:
            intarval = KEY_HOLD_2_S;
            break;
        case APP_KEY_HOLD_3S:
            intarval = KEY_HOLD_3_S;
            break;
        case APP_KEY_HOLD_5S:
            intarval = KEY_HOLD_5_S;
            break;
        case APP_KEY_DOUBLE_CLICK:
            intarval = KEY_CLICK_500_MS;
            break;
        case APP_KEY_TRIPLE_CLICK:
            intarval = KEY_CLICK_800_MS;
            break;
        default:
            ASSERT_ERR(0);
            break;
    }
    return intarval;
}

static void key_timeout( TimerHandle_t xTimer )
{
    TickType_t residual_delay = 0;
    uint32_t key = 0;
    uint32_t * pin_name = NULL;
    uint32_t key_hold_type;
    const ticker_data_t *lp_tick_d = get_lp_ticker_data();

    if(xTimer)
        pin_name = (uint32_t *)rtos_timer_get_pvTimerID(xTimer);
    else
        pin_name = &key_timer_param;

    key_hold_type = key_get_hold_type_by_pin_name(*pin_name);

    if(key_times_down) {
        key_hold_time = ((ticker_read(lp_tick_d) / 1000) - key_times_down );
        if(*pin_name == PIN_PWR) {
            key_hold_time += HW_ANTI_SHAKE_TIME;
        }
    }
    if(PIN_TYPE(*pin_name) == PIN_TYPE_A) {
        if(key_get_soft_filter_by_pin_name(*pin_name) == SFT_FILTER) {
            int bit = PIN_IDX(*pin_name);
            gpioa_irq_en_set(bit,1);
        }
    }

    KEY_DEBUG_PRINTF("key_timeout id %x key_hold_time %d\n",*pin_name,key_hold_time);
    if(key_hold_time < KEY_HOLD_1_S && key_hold_type != APP_KEY_PRESS) {
        KEY_DEBUG_PRINTF("key_timeout return\n");
        return;
    }

    if(key_get_soft_filter_by_pin_name(*pin_name) == SFT_FILTER) {
        key = APP_KEY_PRESS;
    } else {
        if(key_hold_time >= KEY_HOLD_5_S) {
            key = APP_KEY_HOLD_5S;
            residual_delay = key_get_interval_by_type(key_hold_type);
        } else if(key_hold_time >= KEY_HOLD_2_S) {
            key = APP_KEY_HOLD_2S;
            residual_delay = key_get_interval_by_type(key_hold_type);
        } else {
            return;
        }
    }

    if(key != APP_KEY_PRESS){
        key_hold_state = 1;
    }else{
        rtos_timer_delete(key_timer, 0);
        key_timer = NULL;
    }

    if(key) {
        uint32_t key_bond_name;
        key_bond_name = key_board_get_value_by_pin_name((*pin_name));
        if(key_config.key_send_handler){
            key_config.key_send_handler(key_bond_name|key);
        }
    }
    if(key_timer && key != APP_KEY_PRESS) {
        rtos_timer_change_period(key_timer,residual_delay,0);
    }
}

static uint32_t multiclick_key_get_type(uint32_t max_click_num)
{
    uint32_t key_type = 0;
    if(max_click_num == 1)
        key_type = APP_KEY_PRESS;
    else if(max_click_num == 2)
        key_type = APP_KEY_DOUBLE_CLICK;
    else if(max_click_num == 3)
        key_type = APP_KEY_TRIPLE_CLICK;
    else
        ASSERT_ERR(0);
    return key_type;
}

static void multiclick_key_timeout( TimerHandle_t xTimer )
{
    uint32_t key = 0;
    uint32_t * pin_name = NULL;

    if(xTimer)
        pin_name = (uint32_t *)rtos_timer_get_pvTimerID(xTimer);
    else
        pin_name = &multiclick_key_timer_param;
    KEY_DEBUG_PRINTF("id %x key_hold_state %x\n",*pin_name,key_hold_state);
    if(key_hold_state == 0) {
        KEY_DEBUG_PRINTF("multiclick_key_cnt %x\n",multiclick_key_cnt);
        switch(multiclick_key_cnt) {
            case 1:
                key = APP_KEY_PRESS;
                break;
            case 2:
                key = APP_KEY_DOUBLE_CLICK;
                break;
            case 3:
                key = APP_KEY_TRIPLE_CLICK;
                break;
            default :
                break;
        }
        multiclick_key_cnt = 0;
        if(key) {
            uint32_t key_bond_name;
            key_bond_name = key_board_get_value_by_pin_name((*pin_name));
            if(key_config.key_send_handler){
                key_config.key_send_handler(key_bond_name|key);
            }
        }
        if(multiclick_key_timer){
            rtos_timer_stop(multiclick_key_timer, 0);
            rtos_timer_delete(multiclick_key_timer, 0);
            multiclick_key_timer = NULL;
        }
    }
}

static bool key_handle_process(CO_EVENT *evt)
{
    TickType_t key_delay = 0;
    TickType_t multiclick_key_delay = 0;
    static PinName processing_pin_name = PIN_NC;
    uint32_t pin_name = ((evt->EvtId & 0xffff0000)>>16);
    KEY_DEBUG_PRINTF("key_handle_process %x ,id %x\n",(evt->EvtId & 0x0000ffff),processing_pin_name);
    switch(evt->EvtId & 0x0000ffff) {
        case KEY_DOWN:
            {
                if(processing_pin_name == PIN_NC){
                    uint32_t key_hold_type = key_get_hold_type_by_pin_name(pin_name);
                    uint32_t is_period;
                    processing_pin_name = pin_name;
                    key_times_down = evt->Param;
                    if(key_hold_type == APP_KEY_PRESS){
                        key_delay = key_get_interval_by_type(key_hold_type);
                        is_period = pdFALSE;
                    }else{
                        key_delay = key_get_interval_by_type(key_hold_type) - HW_ANTI_SHAKE_TIME;
                        is_period = pdTRUE;
                    }
                    if(key_timer == NULL) {
                        key_timer_param = processing_pin_name;
                        key_timer = rtos_timer_create("KEY",key_delay,is_period,(void *)&key_timer_param,key_timeout);
                        rtos_timer_start(key_timer, 0, false);
                    }
                    if(key_hold_type == APP_KEY_PRESS){
                        processing_pin_name = PIN_NC;
                    }
                }
            }
            break;
        case KEY_UP:
            {
                if(processing_pin_name == pin_name){
                    uint32_t key_max_click_num = key_get_max_click_num_by_pin_name(pin_name);
                    key_times_up = evt->Param;

                    if(key_max_click_num > 1){
                        key_hold_time = 0;

                        if(key_timer) {
                            rtos_timer_stop(key_timer, 0);
                            rtos_timer_delete(key_timer, 0);
                            key_timer = NULL;
                            if(!key_hold_state)
                                key_timeout(NULL);
                        }

                        if(key_hold_state) {
                            key_hold_state = 0;
                        } else {

                            if(multiclick_key_cnt == 0){
                                multiclick_key_cnt = 1;
                                multiclick_key_delay = key_get_interval_by_type(multiclick_key_get_type(key_max_click_num));
                                if(multiclick_key_timer == NULL) {
                                    multiclick_key_timer_param = processing_pin_name;
                                    multiclick_key_timer = rtos_timer_create("MILTICLICK_KEY",multiclick_key_delay,pdFALSE,(void *)&multiclick_key_timer_param,multiclick_key_timeout);
                                    rtos_timer_start(multiclick_key_timer, 0, false);
                                }
                            } else {
                                multiclick_key_cnt++;
                                if(multiclick_key_cnt >= key_max_click_num) {
                                    multiclick_key_timeout(NULL);
                                }
                            }
                        }
                    }
                    processing_pin_name = PIN_NC;
                }
            }
            break;
        case KEY_POWERON:
            {
                KEY_DEBUG_PRINTF("key_single %d\n",evt->Param);
            }
            break;
        default :
            break;
    }
    return 0;
}

static void pwrkey_irq_evt_handler(int evt)
{
    static int edge_recorded = 0;
    static uint32_t pwrkey_times_down = 0;
    static uint32_t pwrkey_times_up = 0;
    CO_MODUAL_EVENT msg;
    int res = 0;
    const ticker_data_t *lp_tick_d = get_lp_ticker_data();
    if (evt == PWRKEY_IRQ_EVENT_KEYDOWN) {
        pwrkey_times_down = ticker_read(lp_tick_d) / 1000;
    } else if (evt == PWRKEY_IRQ_EVENT_KEYUP) {
        pwrkey_times_up = ticker_read(lp_tick_d) / 1000;
    }
    if ((pwrkey_times_down > pwrkey_ponchk_time_ms) && (pwrkey_times_up > pwrkey_times_down) &&
        ((pwrkey_times_up - pwrkey_times_down) > user_pwrkey_poweroff_time_get()) && !pwrdown_get_state()) {
        pmic_chip_shutdown();
    }
    KEY_DEBUG_PRINTF("pkey:%x\n",evt);
    if ((evt == PWRKEY_IRQ_EVENT_KEYUP) ||
        (evt == PWRKEY_IRQ_EVENT_KEYUP_SINGLE)) {
        pwrkey_released = 1;
    }
    msg.mod_id = CO_MODUAL_KEY;
    switch(evt) {
        case PWRKEY_IRQ_EVENT_KEYDOWN:
            edge_recorded = 1;
            msg.mod_evt.EvtId = KEY_DOWN;
            msg.mod_evt.Param = pwrkey_times_down;
            break;
        case PWRKEY_IRQ_EVENT_KEYUP:
            if(edge_recorded) {
                msg.mod_evt.EvtId = KEY_UP;
                msg.mod_evt.Param = pwrkey_times_up;
                edge_recorded = 0;
            } else {
                msg.mod_evt.EvtId = KEY_POWERON;
                msg.mod_evt.Param = (pwrkey_times_up - pwrkey_ponchk_time_ms);
            }
            break;
        case PWRKEY_IRQ_EVENT_KEYUP_SINGLE:
            msg.mod_evt.EvtId = KEY_POWERON;
            msg.mod_evt.Param = ((ticker_read(lp_tick_d) / 1000) - pwrkey_ponchk_time_ms);
            break;
        default :
            ASSERT_ERR(0);
            break;
    }
    msg.mod_evt.EvtId |= (PIN_PWR<<16);
    res = co_event_send(&msg, true);
    ASSERT_ERR(res == 0 || res == 1);
}

static void key_gpiob_irq_handler(int event)
{
    const ticker_data_t *lp_tick_d = get_lp_ticker_data();
    int bit = GPIOIRQ_CB_INDEX(event);
    int val = 0;
    int res = 0;
    int pin_name = PIN(PIN_TYPE_B, bit);

    val = gpiob_get(bit);
    if (GPIOIRQ_CB_EVENT(event) == GPIOIRQ_EVENT_EDGE_BOTH) {
        CO_MODUAL_EVENT msg;
        uint8_t key_up_down = 0;//down is 1,up is 0.

        msg.mod_id = CO_MODUAL_KEY;
        KEY_DEBUG_PRINTF("key_index %x,value %x\n",bit,val);
        for(uint32_t i = 0; i < key_config.reg_bond_len; i++) {
            if(key_config.reg_key_bond_id[i].pin_name == pin_name){
                if(val == key_config.reg_key_bond_id[i].key_default_pull_dowm)
                    key_up_down = NO_PRESS;
                else
                    key_up_down = PRESS;
                if(key_up_down != gpio_key_status[i]){
                    gpio_key_status[i] = key_up_down;
                    if(key_up_down)
                        msg.mod_evt.EvtId = KEY_DOWN;
                    else
                        msg.mod_evt.EvtId = KEY_UP;
                    msg.mod_evt.Param = ticker_read(lp_tick_d) / 1000;
                    msg.mod_evt.EvtId |= (0xffff0000 & (pin_name<<16));
                    res = co_event_send(&msg, true);
                    ASSERT_ERR(res == 0 || res == 1);
                }
            }
        }
    }
}

static void key_gpioa_irq_handler(int event)
{
    const ticker_data_t *lp_tick_d = get_lp_ticker_data();
    int bit = GPIOIRQ_CB_INDEX(event);
    int val = 0;
    int res = 0;
    int pin_name = PIN(PIN_TYPE_A, bit);

    val = gpioa_get(bit);
    if (GPIOIRQ_CB_EVENT(event) == GPIOIRQ_EVENT_EDGE_BOTH) {
        CO_MODUAL_EVENT msg;
        uint8_t key_up_down = 0;//down is 1,up is 0.

        msg.mod_id = CO_MODUAL_KEY;
        KEY_DEBUG_PRINTF("Akey_index %x,value %x\n",bit,val);
        for(uint32_t i = 0; i < key_config.reg_bond_len; i++) {
            if(key_config.reg_key_bond_id[i].pin_name == pin_name){
                if(val == key_config.reg_key_bond_id[i].key_default_pull_dowm)
                    key_up_down = NO_PRESS;
                else
                    key_up_down = PRESS;
                if(key_up_down != gpio_key_status[i]){
                    gpio_key_status[i] = key_up_down;
                    if(key_up_down) {
                        if(key_config.reg_key_bond_id[i].soft_filter == SFT_FILTER) {
                            gpioa_irq_en_set(bit,0);
                        }
                        msg.mod_evt.EvtId = KEY_DOWN;
                    } else {
                        msg.mod_evt.EvtId = KEY_UP;
                    }
                    msg.mod_evt.Param = ticker_read(lp_tick_d) / 1000;
                    msg.mod_evt.EvtId |= (0xffff0000 & (pin_name<<16));
                    res = co_event_send(&msg, true);
                    ASSERT_ERR(res == 0 || res == 1);
                }
            }
        }
    }
}

static void key_register_gpiob_key(int gpiob_index)
{
#if PLF_GSENSOR
    gpiob_irq_init(gpiob_index, GPIOIRQ_TYPE_EDGE_BOTH, key_gpiob_irq_handler,0);
#else
    #if PLF_AIC8800
    gpiob_irq_init(gpiob_index, GPIOIRQ_TYPE_EDGE_BOTH, key_gpiob_irq_handler,0x700);
    #else
    gpiob_irq_init(gpiob_index, GPIOIRQ_TYPE_EDGE_BOTH, key_gpiob_irq_handler);
    #endif
#endif
}

static void key_register_gpioa_key(int gpioa_index)
{
    gpioa_irq_init(gpioa_index, GPIOIRQ_TYPE_EDGE_BOTH, key_gpioa_irq_handler);
}

static void key_register_gpio_pin(PinName pin)
{
    uint8_t pin_type = PIN_TYPE(pin);
    uint8_t pin_idx = PIN_IDX(pin);

    KEY_DEBUG_PRINTF("key_register type %x,idx %x\n",pin_type,pin_idx);
    if (pin_type == PIN_TYPE_A) {
        key_register_gpioa_key(pin_idx);
    } else if (pin_type == PIN_TYPE_B) {
        key_register_gpiob_key(pin_idx);
    }
}

static void key_gpio_force_pull_up_down(PinName pin , enum KEY_PD_LEVEL level)
{
    uint8_t pin_type = PIN_TYPE(pin);
    uint8_t pin_idx = PIN_IDX(pin);

    if (pin_type == PIN_TYPE_A) {
        if(level == DEFAULT_PIN_PULL_UP){
            gpioa_force_pull_up_enable(pin_idx);
        }
    } else if (pin_type == PIN_TYPE_B) {
        if(level == DEFAULT_PIN_PULL_UP){
            gpiob_force_pull_up_enable(pin_idx);
        }
    }
}

void key_set_key_config(app_key_send_handler_t key_send_handler, uint32_t(*bond_list)[6], uint8_t bond_list_len)
{
    key_config.key_send_handler = key_send_handler;
    if(bond_list_len > MAX_GPIO_KEY_REG_LIST_NUM){
        TRACE("%s init len error\n",__func__);
        return;
    }
    key_config.reg_bond_len = bond_list_len;
    for(uint8_t i=0;i<bond_list_len;i++){
        if(bond_list[i][0] != PIN_NC && bond_list[i][1]){
            key_config.reg_key_bond_id[i].pin_name = (uint16_t)bond_list[i][0];
            key_config.reg_key_bond_id[i].key_name_bond_id = key_board_get_bondid_by_value(bond_list[i][1]);
            key_config.reg_key_bond_id[i].key_max_hold_type = (uint8_t)bond_list[i][2];
            key_config.reg_key_bond_id[i].key_max_click_num = (uint8_t)bond_list[i][3];
            key_config.reg_key_bond_id[i].key_default_pull_dowm = (uint8_t)bond_list[i][4];
            key_config.reg_key_bond_id[i].soft_filter = (uint8_t)bond_list[i][5];
            KEY_DEBUG_PRINTF("%s,bond_list_len %x,pin_name %x,key_name %x,key_name bond_id %x,key_max_hold_type %x,key_max_click_num %x,key_default_pull_dowm %x,soft_filter %x\n",__func__,\
                bond_list_len,bond_list[i][0],bond_list[i][1],key_config.reg_key_bond_id[i].key_name_bond_id,bond_list[i][2],bond_list[i][3],bond_list[i][4],bond_list[i][5]);
            if(key_config.reg_key_bond_id[i].pin_name != PIN_PWR){
                key_register_gpio_pin(key_config.reg_key_bond_id[i].pin_name);
                key_gpio_force_pull_up_down(key_config.reg_key_bond_id[i].pin_name, key_config.reg_key_bond_id[i].key_default_pull_dowm);
            }
        }
    }
}

int key_open(void)
{
    int ret = 0;
    co_main_evt_handler_rigister(CO_MODUAL_KEY, key_handle_process);
    pwrkey_irq_callback_register(pwrkey_irq_evt_handler);
    return ret;
}

