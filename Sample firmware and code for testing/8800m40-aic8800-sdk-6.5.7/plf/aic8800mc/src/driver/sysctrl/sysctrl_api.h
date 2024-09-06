/**
 ****************************************************************************************
 *
 * @file sysctrl_api.h
 *
 * @brief SYSCTRL utility functions
 *
 ****************************************************************************************
 */

#ifndef _SYSCTRL_API_H_
#define _SYSCTRL_API_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "reg_sysctrl.h"
#include "hw_cfg.h"

#define SYS_CLK_FREQUENCY_52M       ( 52000000UL)
#define SYS_CLK_FREQUENCY_40M       ( 40000000UL)

/* Flag to indicate fast clk */
#define CLK_CFG_FAST_POS            (7)
#define CLK_CFG_FAST_BIT            (0x01U << CLK_CFG_FAST_POS)
/* Flag to indicate 320m clk */
#define CLK_CFG_320M_POS            (6)
#define CLK_CFG_320M_BIT            (0x01U << CLK_CFG_320M_POS)
/* Flag to indicate flash selects fclk */
#define FLASH_SEL_PSRCLK_POS        (0)
#define FLASH_SEL_PSRCLK_BIT        (0x01U << FLASH_SEL_PSRCLK_POS)
/* Flag to indicate psram selects pll320m clk */
#define PSRAM_SEL_CLKFAST_POS       (1)
#define PSRAM_SEL_CLKFAST_BIT       (0x01U << PSRAM_SEL_CLKFAST_POS)
#define PSRAM_SEL_CLK320M_POS       (2)
#define PSRAM_SEL_CLK320M_BIT       (0x01U << PSRAM_SEL_CLK320M_POS)

enum {
    SYS_FCLK = 0,
    SYS_HCLK,
    SYS_PCLK,
    PER_UART0,
    PER_UART1,
    PER_UART2,
    PER_PSRCLK,
    PER_FLASH,
    PER_PWM,
};

/* For fclk_div/psram_clk_div only */
enum {
    CLK_DIV_VALUE_24  = 0x0,
    CLK_DIV_VALUE_16  = 0x1,
    CLK_DIV_VALUE_12  = 0x2,
    CLK_DIV_VALUE_8   = 0x3,
    CLK_DIV_VALUE_7   = 0x4,
    CLK_DIV_VALUE_6   = 0x5,
    CLK_DIV_VALUE_5P5 = 0x6,
    CLK_DIV_VALUE_5   = 0x7,
    CLK_DIV_VALUE_4P5 = 0x8,
    CLK_DIV_VALUE_4   = 0x9,
    CLK_DIV_VALUE_3P5 = 0xA,
    CLK_DIV_VALUE_3   = 0xB,
    CLK_DIV_VALUE_2P5 = 0xC,
    CLK_DIV_VALUE_2   = 0xD,
    CLK_DIV_VALUE_24D = 0xE,
    CLK_DIV_VALUE_1   = 0xF,
    CLK_DIV_VALUE_MAX
};

/* Clock divider targets */
enum {
    CLK_DIV_TARGET_FCLK = 0,
    CLK_DIV_TARGET_PSRAM,
    CLK_DIV_TARGET_HCLK,
    CLK_DIV_TARGET_PCLK,
    CLK_DIV_TARGET_MAX
};

/* Clock selection targets */
enum {
    CLK_SEL_TARGET_FCLK_FAST = 0,
    CLK_SEL_TARGET_FCLK_PLL320M,
    CLK_SEL_TARGET_PSRAM_FAST,
    CLK_SEL_TARGET_PSRAM_PLL320M,
    CLK_SEL_TARGET_UART0_PCLK,
    CLK_SEL_TARGET_UART1_PCLK,
    CLK_SEL_TARGET_UART2_PCLK,
    CLK_SEL_TARGET_FLASH_PSRCLK,
    CLK_SEL_TARGET_MAX
};

enum {
    CLK_CFG_S240P120PS240F120 = 0,
    CLK_CFG_S240P120PS320F106 = 1,
    CLK_CFG_S240P120PS192F96  = 2,
    CLK_CFG_S240P120PS320F80  = 3,
    CLK_CFG_S240P120PS240F60  = 4,
    CLK_CFG_S240P120PS192F48  = 5,
    CLK_CFG_S240P120PS240F40  = 6,
    CLK_CFG_S192P96PS240F120  = 7,
    CLK_CFG_S192P96PS320F106  = 8,
    CLK_CFG_S192P96PS192F96   = 9,
    CLK_CFG_S192P96PS320F80   = 10,
    CLK_CFG_S192P96PS240F60   = 11,
    CLK_CFG_S192P96PS192F48   = 12,
    CLK_CFG_S192P96PS240F40   = 13,
    CLK_CFG_S160P80PS240F120  = 14,
    CLK_CFG_S160P80PS320F106  = 15,
    CLK_CFG_S160P80PS192F96   = 16,
    CLK_CFG_S160P80PS320F80   = 17,
    CLK_CFG_S160P80PS240F60   = 18,
    CLK_CFG_S160P80PS192F48   = 19,
    CLK_CFG_S160P80PS240F40   = 20,
    CLK_CFG_S120P60PS240F120  = 21,
    CLK_CFG_S120P60PS320F106  = 22,
    CLK_CFG_S120P60PS192F96   = 23,
    CLK_CFG_S120P60PS320F80   = 24,
    CLK_CFG_S120P60PS240F60   = 25,
    CLK_CFG_S120P60PS192F48   = 26,
    CLK_CFG_S120P60PS240F40   = 27,
    CLK_CFG_S80P40PS320F80    = 28,
    CLK_CFG_S80P40PS240F60    = 29,
    CLK_CFG_S80P40PS192F48    = 30,
    CLK_CFG_S80P40PS240F40    = 31,
    CLK_CFG_S52P26PS240F40    = 32,
    CLK_CFG_S52P26PS240F26    = 33,
    CLK_CFG_MAX,
    CLK_CFG_RAW = CLK_CFG_MAX,
};

enum {
    PLL_CFG_OFF = 0,
    PLL_CFG_320,
    PLL_CFG_480,
    PLL_CFG_320_480,
};

/*
 * cpu_sys pwr_ctrl_mode
 *  1) set by host idle task
 *  2) get by fw/host other task
 */
enum {
    CPU_SYS_POWER_ON_RESET  = 0x00,
    CPU_SYS_CLOCK_GATE      = 0x01,
    CPU_SYS_POWER_DOWN      = 0x02,
    CPU_SYS_HIBERNATE       = 0x03
};

/*
 * wifi_core sw_ctrl_mode
 *  1) set by fw/aon
 *  2) get by fw/aon
 */
enum {
    WIFI_CORE_CONTROLLED_BY_FW  = 0x00,
    WIFI_CORE_RELEASED_BY_FW    = 0x01,
    WIFI_CORE_CONTROLLED_BY_AON = 0x02,
    WIFI_CORE_RELEASED_BY_AON   = 0x03
};

/*
 * bt_core sw_ctrl_mode
 *  1) set by fw/aon
 *  2) get by fw/aon
 */
enum {
    BT_CORE_CONTROLLED_BY_FW    = 0x00,
    BT_CORE_RELEASED_BY_FW      = 0x01,
    BT_CORE_CONTROLLED_BY_AON   = 0x02,
    BT_CORE_RELEASED_BY_AON     = 0x03
};

enum {
    PWRCTRL_POWERUP = 0,
    PWRCTRL_POWERDOWN,
};

enum {
    LPCLK_SEL_RC_256K   = 0,
    LPCLK_SEL_LPO_26M   = 1,
};

enum {
    VIO_SEL_1V8_LDO_AVDD18  = 0,
    VIO_SEL_3V3_LDO_PA      = 1,
    VIO_SEL_EXTERNAL        = 2,
};

enum {
    VFLASH_SEL_HIGH_VOLT    = 0, // 2.7~3.6V
    VFLASH_SEL_LOW_VOLT     = 1, // 1.6~2.1V
};

enum {
    VRF_SEL_DCDC_MODE   = 0,
    VRF_SEL_LDO_MODE    = 1,
};

/**
 * System initial clock configure
 */
#ifndef CONFIG_INITIAL_SYSTEM_CLOCK
#define CONFIG_INITIAL_SYSTEM_CLOCK     CLK_CFG_S160P80PS320F80
#endif

/**
 * Low power clock selection
 */
#ifndef CONFIG_LPCLK_SELECT
#define CONFIG_LPCLK_SELECT             LPCLK_SEL_LPO_26M
#endif

/**
 * Chip VIO selection
 */
#ifndef CONFIG_VIO_SELECT
#define CONFIG_VIO_SELECT               VIO_SEL_3V3_LDO_PA
#endif

/**
 * Chip VFLASH selection
 */
#ifndef CONFIG_VFLASH_SELECT
#define CONFIG_VFLASH_SELECT            VFLASH_SEL_HIGH_VOLT
#endif

/**
 * Chip VRF selection
 */
#ifndef CONFIG_VRF_SELECT
#define CONFIG_VRF_SELECT               VRF_SEL_DCDC_MODE
#endif

/**
 * Low power voltage configure
 */
#ifndef CONFIG_LP_PMIC_VCORE_DROP_ENABLE
#define CONFIG_LP_PMIC_VCORE_DROP_ENABLE    0
#endif
#ifndef CONFIG_LP_PMIC_VIO_SLP_PD_ENABLE
#define CONFIG_LP_PMIC_VIO_SLP_PD_ENABLE    1
#endif

/**
 * USB dm volt calibration
 */
#ifndef CONFIG_USB_DM_VOLT_CALIB_ENABLE
#define CONFIG_USB_DM_VOLT_CALIB_ENABLE     0
#endif

/**
 * clock config table
 */
extern const unsigned int clk_cfg_code_tbl[CLK_CFG_MAX];

/**
 * get HCLK/PCLK/PER_CLK
 */
uint32_t sysctrl_clock_get(int sys_per);

/**
 * cfg DSP_CLK/SYS_CLK/PERI_CLK/FLSH_CLK
 */
void sysctrl_clock_cfg(int cfg);

/**
 * cfg pll
 */
void sysctrl_pll_cfg(int cfg);

/**
 * reset dig
 */
void sysctrl_dig_reset(void);

/**
 * sw reboot chip without pwrsys & pmic
 */
void sysctrl_chip_reboot(void);

/**
 * get bt power state
 */
int pwrctrl_bt_get(void);

/**
 * set bt power up/down
 */
void pwrctrl_bt_set(int ctrl);

/**
 * get wifi power state
 */
int pwrctrl_wifi_get(void);

/**
 * set wifi power up/down
 */
void pwrctrl_wifi_set(int ctrl);

/**
 * set mmsys power up/down
 */
void pwrctrl_mmsys_set(int ctrl);

/**
 * @brief   Update pwrctrl awake state
 */
void pwrctrl_awake_state_update(void);

/**
 * @brief   Get software record irq status
 * @return  Value of irq status
 */
uint32_t pwrctrl_sw_rec_irqstatus_get(void);

#endif /* _SYSCTRL_API_H_ */
