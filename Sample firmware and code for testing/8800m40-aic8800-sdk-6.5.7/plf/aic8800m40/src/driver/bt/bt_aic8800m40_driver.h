#ifndef __BT_AIC8800_DRIVER_H__
#define  __BT_AIC8800_DRIVER_H__
#include "compiler.h"
#include "reg_access.h"

#define BT_POWERON            1
#define BT_POWEROFF           0


/// 8 bit access types
#define _8_Bit                              8
/// 16 bit access types
#define _16_Bit                             16
/// 32 bit access types
#define _32_Bit                             32

#ifndef RWIP_TIME_T
#define RWIP_TIME_T
typedef struct
{
    /// Integer part of the time (in half-slot)
    uint32_t hs;
    /// Fractional part of the time (in half-us) (range: 0-624)
    uint32_t hus;
} rwip_time_t;

typedef struct
{
    /// Integer part of the time (in half-slot)
    uint32_t clk_off_hs;
    /// Fractional part of the time (in half-us) (range: 0-624)
    uint32_t clk_off_hus;
} TWS_BT_CLK_INFO_Type;
#endif

#define CLK_ADD_2(clock_a, clock_b)     ((uint32_t)(((clock_a) + (clock_b)) & RWIP_MAX_CLOCK_TIME))
#define CLK_SUB(clock_a, clock_b)     ((uint32_t)(((clock_a) - (clock_b)) & RWIP_MAX_CLOCK_TIME))
#define RWIP_MAX_CLOCK_TIME              ((1L<<28) - 1)


typedef enum {
    DRV_RF_MODE_NULL          = 0x00,
    DRV_RF_MODE_BT_ONLY       = 0x01,
    DRV_RF_MODE_BT_COMBO      = 0x02,
    DRV_RF_MODE_BTWIFI_COMBO  = 0x03,
    DRV_RF_MODE_NUM           = 0x04
}BtDrvRfModeEnum;

enum {
    BT_LP_LEVEL_POWER_OFF  = 0x00,//BT CORE power off, CPUSYS power off, VCORE power off
    BT_LP_LEVEL_CLOCK_GATE = 0x01,//BT CORE clock gate, CPUSYS clock gate, VCORE clock_gate
};

enum {
    BT_LP_LEVEL_ACTIVE      = 0x00,//BT CORE active, CPUSYS active, VCORE active
    BT_LP_LEVEL_CLOCK_GATE1 = 0x01,//BT CORE clock gate, CPUSYS active, VCORE active
    BT_LP_LEVEL_CLOCK_GATE2 = 0x02,//BT CORE clock gate, CPUSYS clock gate, VCORE active
    BT_LP_LEVEL_CLOCK_GATE3 = 0x03,//BT CORE clock gate, CPUSYS clock gate, VCORE clock_gate
    BT_LP_LEVEL_POWER_OFF1  = 0x04,//BT CORE power off, CPUSYS active, VCORE active
    BT_LP_LEVEL_POWER_OFF2  = 0x05,//BT CORE power off, CPUSYS clock gate, VCORE active
    BT_LP_LEVEL_POWER_OFF3  = 0x06,//BT CORE power off, CPUSYS power off, VCORE active
    BT_LP_LEVEL_HIBERNATE   = 0x07,//BT CORE power off, CPUSYS power off, VCORE power off
    BT_LP_LEVEL_NUM         = 0x08,
};

enum {
    BT_PRV_SLP_TIMER       = (0x01UL << 0),
    BT_STACK_SLP_DISALLOW  = (0x01UL << 1),
    BLE_STACK_SLP_DISALLOW = (0x01UL << 2),
};


enum aicbt_btport_type {
    AICBT_BTPORT_NULL,
    AICBT_BTPORT_MB,
    AICBT_BTPORT_UART,
};

/*  btmode
 * used for force bt mode,if not AICBSP_MODE_NULL
 * efuse valid and vendor_info will be invalid, even has beed set valid
*/
#if 0
enum aicbt_btmode_type {
    AICBT_BTMODE_BT_ONLY_SW = 0x0,    // bt only mode with switch
    AICBT_BTMODE_BT_WIFI_COMBO,       // wifi/bt combo mode
    AICBT_BTMODE_BT_ONLY,             // bt only mode without switch
    AICBT_BTMODE_BT_ONLY_TEST,        // bt only test mode
    AICBT_BTMODE_BT_WIFI_COMBO_TEST,  // wifi/bt combo test mode
    AICBT_BTMODE_BT_ONLY_COANT,       // bt only mode with no external switch
    AICBT_MODE_NULL = 0xFF,           // invalid value
};
#endif
#define AICBT_BTMODE_BT_ONLY_SW          0// bt only mode with switch
#define AICBT_BTMODE_BT_WIFI_COMBO       1// wifi/bt combo mode
#define AICBT_BTMODE_BT_ONLY             2// bt only mode without switch
#define AICBT_BTMODE_BT_ONLY_TEST        3// bt only test mode
#define AICBT_BTMODE_BT_WIFI_COMBO_TEST  4// wifi/bt combo test mode
#define AICBT_BTMODE_BT_ONLY_COANT       5// bt only mode with no external switch
#define AICBT_MODE_NULL                  0xFF// invalid value


/*  uart_baud
 * used for config uart baud when btport set to uart,
 * otherwise meaningless
*/
enum aicbt_uart_baud_type {
    AICBT_UART_BAUD_115200     = 115200,
    AICBT_UART_BAUD_921600     = 921600,
    AICBT_UART_BAUD_1_5M       = 1500000,
    AICBT_UART_BAUD_3_25M      = 3250000,
};

enum aicbt_uart_flowctrl_type {
    AICBT_UART_FLOWCTRL_DISABLE = 0x0,    // uart without flow ctrl
    AICBT_UART_FLOWCTRL_ENABLE,           // uart with flow ctrl
};

enum aicbsp_cpmode_type {
    AICBSP_CPMODE_WORK,
    AICBSP_CPMODE_TEST,
    AICBSP_CPMODE_MAX,
};

///aic bt tx pwr lvl :lsb->msb: first byte, min pwr lvl; second byte, max pwr lvl;
///pwr lvl:20(min), 30 , 40 , 50 , 60(max)
#define AICBT_TXPWR_LVL                   0x00006020
#define AICBT_TXPWR_LVL_8800dc            0x00006f2f
#define AICBT_TXPWR_LVL_8800d80           0x00003f3f

struct aicbsp_info_t {
    int hwinfo;
    int hwinfo_r;
    uint32_t cpmode;
    uint32_t chip_rev;
    bool fwlog_en;
};

struct aicbt_info_t {
    uint32_t btmode;
    uint32_t btport;
    uint32_t uart_baud;
    uint32_t uart_flowctrl;
    uint32_t lpm_enable;
    uint32_t txpwr_lvl;
};

typedef struct
{
    /// Em save start address
    uint32_t em_save_start_addr;
    /// Em save end address
    uint32_t em_save_end_addr;
    /// Minimum time that allow power off (in hs)
    int32_t aon_min_power_off_duration;
    /// Maximum aon params
    uint16_t aon_max_nb_params;
    /// RF config const time on cpus side (in hus)
    int16_t aon_rf_config_time_cpus;
    /// RF config const time on aon side (in hus)
    int16_t aon_rf_config_time_aon;
    /// Maximum active acl link supported by aon
    uint16_t aon_max_nb_active_acl;
    /// Maximum ble activity supported by aon
    uint16_t aon_ble_activity_max;
    /// Maximum bt rxdesc field supported by aon
    uint16_t aon_max_bt_rxdesc_field;
    /// Maximum ble rxdesc field supported by aon
    uint16_t aon_max_ble_rxdesc_field;
    /// Maximum regs supported by aon
    uint16_t aon_max_nb_regs;
    /// Maximum length of ke_env supported by aon
    uint16_t aon_max_ke_env_len;
    /// Maximum elements of sch_arb_env supported by aon
    uint16_t aon_max_nb_sch_arb_elt;
    /// Maximun elements of sch_plan_env supported by aon
    uint16_t aon_max_nb_sch_plan_elt;
    /// Maximun elements of sch_alarm_env supported by aon
    uint16_t aon_max_nb_sch_alarm_elt;
    /// Minimum advertising interval in slots(625 us) supported by aon
    uint32_t aon_min_ble_adv_intv;
    /// Minimum connection interval in 2-slots(1.25 ms) supported by aon
    uint32_t aon_min_ble_con_intv;
    /// Extra sleep duration for cpus(in hs), may be negative
    int32_t aon_extra_sleep_duration_cpus;
    /// Extra sleep duration for aon cpu(in hs), may be negative
    int32_t aon_extra_sleep_duration_aon;
    /// Minimum time that allow host to power off (in us)
    int32_t aon_min_power_off_duration_cpup;
    /// aon debug level for cpus
    uint32_t aon_debug_level;
    /// aon debug level for aon cpu
    uint32_t aon_debug_level_aon;
    /// Power on delay of bt core on when cpu_sys alive on cpus side(in lp cycles)
    uint16_t aon_bt_pwr_on_dly1;
    /// Power on delay of bt core when cpu_sys clock gate on cpus side(in lp cycles)
    uint16_t aon_bt_pwr_on_dly2;
    /// Power on delay of bt core when cpu_sys power off on cpus side(in lp cycles)
    uint16_t aon_bt_pwr_on_dly3;
    /// Power on delay of bt core on aon side(in lp cycles)
    uint16_t aon_bt_pwr_on_dly_aon;
    /// Time to cancel sch arbiter elements in advance when switching to cpus (in hus)
    uint16_t aon_sch_arb_cancel_in_advance_time;
    /// Duration of sleep and wake-up algorithm (depends on CPU speed) expressed in half us on cpus side
    /// should also contian deep_sleep_on rising edge to finecnt halt (max 4 lp cycles) and finecnt resume to dm_slp_irq (0.5 lp cycles)
    uint16_t aon_sleep_algo_dur_cpus;
    /// Duration of sleep and wake-up algorithm (depends on CPU speed) expressed in half us on aon side
    /// should also contian deep_sleep_on rising edge to finecnt halt (max 4 lp cycles) and finecnt resume to dm_slp_irq (0.5 lp cycles)
    uint16_t aon_sleep_algo_dur_aon;
    /// Threshold that treat fractional part of restore time (in hus) as 1hs on cpus side
    uint16_t aon_restore_time_ceil_cpus;
    /// Threshold that treat fractional part of restore time (in hus) as 1hs on aon side
    uint16_t aon_restore_time_ceil_aon;
    /// Minimum time that allow deep sleep on cpus side (in hs)
    uint16_t aon_min_sleep_duration_cpus;
    /// Minimum time that allow deep sleep on aon side (in hs)
    uint16_t aon_min_sleep_duration_aon;
    /// Difference of restore time and save time on cpus side (in hus)
    int16_t aon_restore_save_time_diff_cpus;
    /// Difference of restore time and save time on aon side (in hus)
    int16_t aon_restore_save_time_diff_aon;
    /// Difference of restore time on aon side and save time on cpus side (in hus)
    int16_t aon_restore_save_time_diff_cpus_aon;
    /// Minimum time that allow clock gate (in hs)
    int32_t aon_min_clock_gate_duration;
    /// Minimum time that allow host to clock gate (in us)
    int32_t aon_min_clock_gate_duration_cpup;
    /// Maximum rf & mdm regs supported by aon
    uint16_t aon_max_nb_rf_mdm_regs;
}bt_drv_wr_aon_param;

/// Buffer structure
struct bt_buffer_tag
{
    /// length of buffer
    uint8_t length;
    /// data of 128 bytes length
    uint8_t data[128];
};

typedef struct
{
    uint8_t calib_type;
    uint16_t offset;
    struct bt_buffer_tag buf;
}bt_drv_rf_calib_req_cmd;

///HCI Debug wr rf mdm regs command parameters - vendor specific
typedef struct
{
    /// offset
    uint16_t offset;
    // reserved
    uint8_t reserved;
    /// length
    uint8_t length;
    /// data (addr<32bits> value<32bits> addr<32bits> value<32bits> ...)
    uint8_t data[248];
}hci_dbg_wr_rf_mdm_regs_cmd;

#define RF_MDM_REGS_MAX_DATA_SIZE  30// (248/8 = 31)-1


/**
 * @brief CLKNCNTRAW register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  27:00           CLKNCNTRAW   0x0
 * </pre>
 */
#define IP_CLKNCNTRAW_ADDR   0x40600048
#define IP_CLKNCNTRAW_OFFSET 0x00000048
#define IP_CLKNCNTRAW_INDEX  0x00000012
#define IP_CLKNCNTRAW_RESET  0x00000000

__INLINE uint32_t ip_clkncntraw_get(void)
{
    return REG_IP_RD(IP_CLKNCNTRAW_ADDR);
}
/**
 * @brief FINECNTRAW register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  09:00           FINECNTRAW   0x0
 * </pre>
 */
#define IP_FINECNTRAW_ADDR   0x4060004C
#define IP_FINECNTRAW_OFFSET 0x0000004C
#define IP_FINECNTRAW_INDEX  0x00000013
#define IP_FINECNTRAW_RESET  0x00000000

__INLINE uint32_t ip_finecntraw_get(void)
{
    return REG_IP_RD(IP_FINECNTRAW_ADDR);
}

#endif
