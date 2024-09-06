#ifndef __LED_H__
#define  __LED_H__
#include "co_main.h"
#include "pinname.h"

#define DIPLOID_NUM             26000000//1s
#define GPIOA_DIPLOID_NUM       0x7F//1s
#define GPIOA_DELAY_DIPLOID     8

enum LED_COLOUR{
    LED_BULE,
    LED_RED,
    LED_MAX_COLOUR,
};

typedef enum{
    LED_NULL,
    LED_POWEROFF,
    LED_POWERON,
    LED_CHARGING,
    LED_LOW_POWER,

    LED_WIFI_IDLE,
    LED_WIFI_PARING,
    LED_WIFI_CONNECT,
    LED_WIFI_STA_CONNECTED,

    LED_BT_IDLE,
    LED_BT_SCAN,
    LED_BT_CONNECT,
}LED_MODE;
void led_register_gpio_pin(PinName pin,enum LED_COLOUR colour_id);
void led_init(void);
void led_set_pattern(LED_MODE mode);

#endif
