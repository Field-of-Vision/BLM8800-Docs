#ifndef _PMIC_API_H_
#define _PMIC_API_H_

#include "pmu_rtc0.h"
#include "pmu_rtc1.h"
#include "dual_dcdc_common.h"
#include "dual_dcdc_ctrl.h"
#include "reg_wdt.h" // for WDT4
#include "psim_api.h"
#include "sleep_api.h"

typedef enum {
    PMIC_PWRKEY_POS_IRQn        = 0,
    PMIC_PWRKEY_NEG_IRQn        = 1,
    PMIC_GPIO_C_1_0_POS_IRQn    = 2,
    PMIC_GPIO_C_1_0_NEG_IRQn    = 3,
    PMIC_IRQ_NUMBER
} PMIC_IRQ_T;

typedef enum {
    PMIC_POR_SRC_RESEVERD0          = (0x01 << 0),
    PMIC_POR_SRC_RESEVERD1          = (0x01 << 1),
    PMIC_POR_SRC_BOR_PWR_ON         = (0x01 << 2),
    PMIC_POR_SRC_WDG_PWR_ON         = (0x01 << 3),
    PMIC_POR_SRC_ALM_INT_SET        = (0x01 << 4),
    PMIC_POR_SRC_PB_INT_7S_SET      = (0x01 << 5),
    PMIC_POR_SRC_PB_INT_DEBC        = (0x01 << 6),
    PMIC_POR_SRC_PWRKEY_STATUS      = (0x01 << 7),
} PMIC_POR_SRC_T;

typedef enum {
    PMIC_GPIO_HOLD_BIT_A0_6         = (0x01 << 0),
    PMIC_GPIO_HOLD_BIT_A7_9         = (0x01 << 1),
    PMIC_GPIO_HOLD_BIT_A10_15       = (0x01 << 2),
    PMIC_GPIO_HOLD_BIT_B0_3         = (0x01 << 3),
} PMIC_GPIO_HOLD_BIT_T;

#define PMIC_GPIO_HOLD_ALL_BITS     (PMIC_GPIO_HOLD_BIT_A0_6 | \
                                     PMIC_GPIO_HOLD_BIT_A7_9 | \
                                     PMIC_GPIO_HOLD_BIT_A10_15 | \
                                     PMIC_GPIO_HOLD_BIT_B0_3)

#define PMIC_ITF_INIT(...)          psim_init(__VA_ARGS__)
#define PMIC_MEM_READ(...)          psim_read(__VA_ARGS__)
#define PMIC_MEM_WRITE(...)         psim_write(__VA_ARGS__)
#define PMIC_MEM_MASK_WRITE(...)    psim_mask_write(__VA_ARGS__)

void pmic_pmu_rtc0_irq_enable(uint32_t int_en);
void pmic_pmu_rtc0_irq_enable_local(void);
int pmic_powerkey_enable(unsigned int reb_sec);
void pmic_powerkey_devmode_enable(void);

/**
 * @brief: Sw shutdown
 */
void pmic_chip_shutdown(void);

/**
 * @brief: Sw reboot
 */
void pmic_chip_reboot(unsigned int dly_ticks);

void pmic_wdt_init(unsigned int seconds);
void pmic_wdt_kick(void);
void pmic_wdt_pause(void);
void pmic_wdt_continue(void);

unsigned int pmic_xtal_cap_get(void);
void pmic_xtal_cap_set(unsigned int xtal_cap);

/**
 * set pmic dcdc_rf / ldo_vrtc08 / ldo_vcore08
 */
void pmic_dcdc_rf_set(POWER_MODE_LEVEL_T level);
void pmic_ldo_vrtc08_set(POWER_MODE_LEVEL_T level);
void pmic_ldo_vcore08_set(POWER_MODE_LEVEL_T level);

void pmic_vflash_init(int vflash_sel);
void pmic_pmu_init(void);
void pmic_lpmode_init(void);
void pmic_lpo_256k_calib_init(void);
void pmic_lpo_256k_calib_start(void);
void pmic_lpo_256k_calib_done_check(void);
void pmic_frc_ccm_en(int en);

/**
 * @brief       Config GPIO wakeup
 * @param[in]   en Enable or not
*/
void pmic_gpio_wakeup_config(int en);

/**
 * @brief       Config GPIO hold
 * @param[in]   hold_en: Enable or not
*/
void pmic_gpio_hold_config(int hold_en);

/**
 * @brief       Get GPIO hold bits value
 * @return:     hold value
*/
uint8_t pmic_gpio_hold_get(void);

/**
 * @brief       Set GPIO hold bits value
 * @param[in]   hold_bits: Hold bits value, refer to PMIC_GPIO_HOLD_BIT_T
*/
void pmic_gpio_hold_set(uint8_t hold_bits);

/**
 * set pmic sleep level
 */
void pmic_sleep_level_set(POWER_MODE_LEVEL_T level);

/**
 * @brief:      Get POR source
 * @return:     POR source bit map, refer to PMIC_POR_SRC_T
 */
uint8_t pmic_por_source_get(void);

/**
 * @brief       Check pmic config when boot
*/
void pmic_boot_check(void);

#endif /* _PMIC_API_H_ */
