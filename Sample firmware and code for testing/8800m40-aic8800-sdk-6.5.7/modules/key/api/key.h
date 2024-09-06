#ifndef __KEY_H__
#define  __KEY_H__
#include "co_main.h"
#if PLF_GSENSOR
#include "da280.h"
#endif /* PLF_GSENSOR */
#include "pinname.h"

/*****************************************/
//ms
#define KEY_HOLD_5_S           5000
#define KEY_HOLD_3_S           3000
#define KEY_HOLD_2_S           2000
#define KEY_HOLD_1_S           1000
#define KEY_HOLD_500_MS        500
#define KEY_HOLD_200_MS        200
#define KEY_HOLD_100_MS        100

//ms
#define KEY_CLICK_2_5_S        2500
#define KEY_CLICK_1_5_S        1500
#define KEY_CLICK_1_S          1000
#define KEY_CLICK_800_MS       800
#define KEY_CLICK_500_MS       500
#define KEY_CLICK_300_MS       300

#define KEY_BOARD_BONDING   \
{   \
    APP_KEY_NUM0,APP_KEY_NUM1,APP_KEY_NUM2,APP_KEY_NUM3,APP_KEY_NUM4,APP_KEY_NUM5,APP_KEY_NUM6,APP_KEY_NUM7,APP_KEY_NUM8,APP_KEY_NUM9,\
    APP_KEY_POWER,APP_KEY_PLAY,APP_KEY_NEXT,APP_KEY_PREV,APP_KEY_VOLADD,APP_KEY_VOLSUB,APP_KEY_EQ,APP_KEY_MUTE,APP_KEY_GSENSOR,APP_KEY_NULL\
}

enum PWR_DOWN_STATE{
    DEFAULT_POWER_DOWN = 0,
    USER_POWER_DOWN,
};

enum FILTER_TYPE{
    HW_FILTER = 0,     //used for GPIOB key or Gsensor
    SFT_FILTER,    //only used for GPIOA key
};

enum KEY_PD_LEVEL{
    DEFAULT_PIN_PULL_DOWN = 0,
    DEFAULT_PIN_PULL_UP,
};

enum KEY_PRESS_LEVEL{
    NO_PRESS= 0,
    PRESS,
};

/*****************************************************/
/* user defined macro for diffrent APP.              */
/*****************************************************/
#if PLF_BT_STACK
#define KEY_DEFAULT_POWERON_TIME         3000//3s
#define KEY_DEFAULT_POWEROFF_TIME        5000//5s
#elif PLF_WIFI_STACK
#define KEY_DEFAULT_POWERON_TIME         3000//3s
#define KEY_DEFAULT_POWEROFF_TIME        3000//3s
#else
#define KEY_DEFAULT_POWERON_TIME         USER_DEFINED_POWERON_TIME_MS//0s
#define KEY_DEFAULT_POWEROFF_TIME        USER_DEFINED_POWEROFF_TIME_MS//3s
#endif
enum KEY_CLICK_NUM{
    KEY_MAX_CLICK_1 = 1,
    KEY_MAX_CLICK_2 = 2,
    KEY_MAX_CLICK_NUM = 3,  // 3:default max is triple click ,2: default max is double click ,1: only support press.
};
#define KEY_MAX_HOLD_TYPE                APP_KEY_HOLD_5S//default max hold check timer type.
#define MAX_GPIO_KEY_REG_LIST_NUM        8  // Maximum number of users can register
#define KEY_REG_LIST_ONE_NUM_SIZE        24 // sizeof(uint32_t) * 6 = 24
//end

typedef int (*app_key_send_handler_t)(uint32_t key_event);
typedef struct{
    PinName pin_name;
    uint8_t key_name_bond_id;
    uint8_t key_max_hold_type;
    uint8_t key_max_click_num;
    enum KEY_PD_LEVEL key_default_pull_dowm;
    enum FILTER_TYPE soft_filter;
}key_bond_reg_t;

typedef struct{
    app_key_send_handler_t  key_send_handler;
    uint8_t reg_bond_len;
    key_bond_reg_t reg_key_bond_id[MAX_GPIO_KEY_REG_LIST_NUM];
}KEY_CONFIG;

void pwrdown_set_state(enum PWR_DOWN_STATE state);
void key_set_key_config(app_key_send_handler_t key_send_handler, uint32_t(*bond_list)[6], uint8_t bond_list_len);
int key_open(void);
#endif
