/**
 ****************************************************************************************
 *
 * @file sleep_api.h
 *
 * @brief SLEEP utility functions
 *
 ****************************************************************************************
 */

#ifndef _SLEEP_API_H_
#define _SLEEP_API_H_

#include "plf.h"

/*
 * ENUMS
 ****************************************************************************************
 */
typedef enum {
    PM_LEVEL_ACTIVE       = 0,  // cpu active/wfi,              peripheral active,              dig_top power up           , ram retention,            aon_sys power up
    PM_LEVEL_LIGHT_SLEEP  = 1,  // cpu active/wfi/clock gating, peripheral active/clock gating, dig_top power up           , ram retention,            aon_sys power up
    PM_LEVEL_DEEP_SLEEP   = 2,  // cpu active/wfi/power down,   peripheral active/power down,   dig_top power up/power down, ram retention,            aon_sys power up
    PM_LEVEL_HIBERNATE    = 3,  // cpu active/wfi/power down,   peripheral active/power down,   dig_top power up/power down, ram retention/power down, aon_sys power up
    PM_LEVEL_POWER_OFF    = 4,  // cpu active/wfi/power down,   peripheral active/power down,   dig_top power up/power down, ram retention/power down, aon_sys power up/power down
    PM_LEVEL_LEVEL_NUM
} POWER_MODE_LEVEL_T;

typedef enum {
    PML_WIFISYS_ACTIVE  = 0,
    PML_WIFISYS_CLKGATE = 1,
    PML_WIFISYS_PWROFF  = 2,
    PML_WIFISYS_LEVEL_NUM
} POWER_MODE_LEVEL_WIFISYS_T;

typedef enum {
    WAKESRC_GPIOA       = 0,
    WAKESRC_GPIOB       = 1,
    WAKESRC_TIMER       = 2,
    WAKESRC_NUM_MAX
} WAKEUP_SOURCE_T;

typedef enum {
    WAKEGPIO_MUX_0  = 0,
    WAKEGPIO_MUX_1  = 1,
    WAKEGPIO_MUX_2  = 2,
    WAKEGPIO_MUX_NUM_MAX
} WAKEUP_GPIO_MUX_T;

#define WAKEGPIO_ARG(mux,idx)   ((mux << 8) | (idx))

typedef enum {
    SLEEP_PREVENT_WPAS_ASSOC      = (0x1UL << 0),
    SLEEP_PREVENT_LWIP_DHCP       = (0x1UL << 1),
    SLEEP_PREVENT_MSG             = (0x1UL << 2),
    SLEEP_PREVENT_WAIT_FW         = (0x1UL << 3),
    SLEEP_PREVENT_TCP             = (0x1UL << 4),
} SLEEP_PREVENT_T;

typedef struct {
    void (*set_sleep_level) (POWER_MODE_LEVEL_T level);
    int  (*is_sleep_allowed)(void);
    void (*indicate_sleep) (POWER_MODE_LEVEL_T level);
    void (*indicate_wakeup) (void);
} sleep_entry_t;

/**
 * register sleep entry
 */
void sleep_entry_register(sleep_entry_t *entry);

/**
 * sleep manager
 */
int sleep_management(unsigned int time_ms);

/**
 * get sleep level
 */
POWER_MODE_LEVEL_T sleep_level_get(void);

/**
 * set sleep level
 */
void sleep_level_set(POWER_MODE_LEVEL_T level);

/**
 * get sleep prevent bits
 */
unsigned int sleep_prevent_get(void);

/**
 * set sleep prevent bits
 */
void sleep_prevent_set(SLEEP_PREVENT_T flag);

/**
 * clear sleep prevent bits
 */
void sleep_prevent_clr(SLEEP_PREVENT_T flag);

/**
 * allow user sleep or not
 */
void user_sleep_allow(int yes);

/**
 * indicate powerkey is pressed
 */
void user_powerkey_pressed(void);

/**
 * set user wakeup source
 * @param src  The wakeup source type, GPIOA/GPIOB/TIMER supported
 * @param en   To enable or not, non-zero means enable
 * @param arg  The input argument, GPIO index(use WAKEGPIO_ARG macro) or time interval
 */
void user_sleep_wakesrc_set(WAKEUP_SOURCE_T src, int en, unsigned int arg);

void sys_wakeup_indicate(void);

#endif /* _SLEEP_API_H_ */
