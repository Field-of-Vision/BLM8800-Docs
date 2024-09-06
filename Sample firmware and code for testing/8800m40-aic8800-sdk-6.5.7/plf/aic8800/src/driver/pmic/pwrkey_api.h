#ifndef _PWRKEY_API_H_
#define _PWRKEY_API_H_

#include "chip.h"
#include "plf.h"
#include "pmic_api.h"
#include "hw_cfg.h"

#ifndef CONFIG_PWRKEY_PULLED_UP_ALWAYS
#define CONFIG_PWRKEY_PULLED_UP_ALWAYS  1
#endif

#ifndef CONFIG_PWRKEY_DEV_MODE_PWREN
#define CONFIG_PWRKEY_DEV_MODE_PWREN    0
#endif

#if (CONFIG_PWRKEY_PULLED_UP_ALWAYS)
#define USER_DEFINED_PWRKEY_EN          (0)// pwrkey can be pulled up always
#else
#define USER_DEFINED_PWRKEY_EN          (1)// pwrkey must be pulled down after pulled up for power on process
#endif

#if (PLF_M2D_BLE || PLF_M2D_OTA || CONFIG_PWRKEY_DEV_MODE_PWREN)
#define USER_DEFINED_DEV_MODE_PWRKEY_EN (1)// pwrkey for device mode.
#else
#define USER_DEFINED_DEV_MODE_PWRKEY_EN (0)// pwrkey for device mode.
#endif
#if (USER_DEFINED_PWRKEY_EN == 1) && (USER_DEFINED_DEV_MODE_PWRKEY_EN == 1)
#error USER_DEFINED_PWRKEY_EN and USER_DEFINED_DEV_MODE_PWRKEY_EN can not both be 1
#endif

#define USER_DEFINED_POWERON_TIME_MS    (0)
#define USER_DEFINED_POWEROFF_TIME_MS   (5200)
#define USER_DEFINED_REBOOT_TIME_S      (10)

enum {
    PWRKEY_IRQ_EVENT_KEYDOWN = 0,
    PWRKEY_IRQ_EVENT_KEYUP,
    PWRKEY_IRQ_EVENT_KEYUP_SINGLE,
};

typedef void (*pwrkey_irq_handler_t)(int event);

/**
 * @brief: Enable pwrkey function if necessary
 */
void pwrkey_init(void);

/**
 * @brief: Power-on check, boot to app if got key event as user defined time
 */
void pwrkey_poweron_check(void);

/**
 * @brief: IRQ handler with event
 * @param[in] event: pos or neg
 */
void pwrkey_irq_handler(int event);

/**
 * @brief: Register pwerkey IRQ callback function
 * @param[in] event: pos or neg
 */
void pwrkey_irq_callback_register(pwrkey_irq_handler_t callback);

/**
 * @brief: Get user config
 * @return: Pwrkey enable or not
 */
int user_pwrkey_enabled(void);

/**
 * @brief: Get user config
 * Positive edge of pwrkey will power on, falling edge will power off.
 * @return: Device Mode Pwrkey enable or not
 */
int user_devmode_pwrkey_enabled(void);

/**
 * @brief: Get user defined power-on time
 * @return: Power-on time in ms, 0 or greater than 400
 */
unsigned int user_pwrkey_poweron_time_get(void);

/**
 * @brief: Get user defined power-off time
 * @return: Power-off time in ms
 */
unsigned int user_pwrkey_poweroff_time_get(void);

/**
 * @brief: Get user defined reboot time
 * @return: Reboot time in s
 */
unsigned int user_pwrkey_reboot_time_get(void);

#endif /* _PWRKEY_API_H_ */
