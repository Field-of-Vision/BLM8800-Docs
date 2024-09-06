#include "hw_cfg.h"
#include <string.h>
#include <stdint.h>
#include "gpio_api.h"
#if PLF_KEY_MODULE
#include "key.h"
#endif
#if PLF_LED_MODULE
#include "led.h"
#endif
#if PLF_LS_MODULE
#include "light_sensor.h"
#endif
#include "app_bt_queue.h"
#include "reg_sysctrl.h"
#include "sysctrl_api.h"
#include "dbg.h"

void app_key_driver_init(void)
{
#if (PLF_KEY_MODULE)
    #if PLF_GSENSOR
    int ret;
    uint32_t key_bond_id[MAX_GPIO_KEY_REG_LIST_NUM][6] = {
        {PB_3 , APP_KEY_GSENSOR , KEY_MAX_HOLD_TYPE , KEY_MAX_CLICK_2 , DEFAULT_PIN_PULL_DOWN , HW_FILTER},
    };
    uint32_t pwrmd = pwrctrl_pwrmd_cpusys_sw_record_getf();
    TRACE("APP: app_bt_key_driver_init %x\n",pwrmd);
    if (pwrmd < CPU_SYS_POWER_DOWN) {
        TRACE("APP: da280_i2c_open\n");
        da280_i2c_open();
        ret = da280_init();
        if (!ret) {
            ret = da280_open_interrupt();
            if (ret) {
                TRACE("APP: fail to open da280 irq\n");
                da280_close_interrupt();
            }
        } else {
            da280_reset();
            TRACE("APP: fail to init da280\n");
        }
    }
    key_set_key_config(app_bt_send_key,key_bond_id,(sizeof(key_bond_id)/KEY_REG_LIST_ONE_NUM_SIZE));
    #else
    uint32_t key_bond_id[][6] = {
        {PIN_PWR, APP_KEY_POWER  , KEY_MAX_HOLD_TYPE , KEY_MAX_CLICK_NUM , DEFAULT_PIN_PULL_DOWN , HW_FILTER},
        //{PA_1,    APP_KEY_VOLADD , APP_KEY_PRESS     , KEY_MAX_CLICK_1   , DEFAULT_PIN_PULL_DOWN , SFT_FILTER},
        //{PA_2,    APP_KEY_VOLSUB , APP_KEY_PRESS     , KEY_MAX_CLICK_1   , DEFAULT_PIN_PULL_DOWN , SFT_FILTER},
    };
    key_set_key_config(app_bt_send_key,key_bond_id,(sizeof(key_bond_id)/KEY_REG_LIST_ONE_NUM_SIZE));
    #endif
#endif
}


void app_led_init(void)
{
#if PLF_LED_MODULE
    #if PLF_PMIC_VER_LITE
    led_register_gpio_pin(PB_3,LED_BULE);
    led_register_gpio_pin(PB_4,LED_RED);
    #endif
    #if PLF_PMIC_VER_AUD
    led_register_gpio_pin(PB_6,LED_BULE);
    led_register_gpio_pin(PB_7,LED_RED);
    #endif
#endif
}


void hw_cfg_init(void)
{
#if PLF_KEY_MODULE
    key_open();
#endif

#if PLF_LED_MODULE
    led_init();
#endif

#if PLF_LS_MODULE
    ls_init();
#endif

    app_key_driver_init();
    app_led_init();
#if PLF_LS_MODULE
    ls_register_evt_callback(app_bt_send_wearing_state);
#endif

}
