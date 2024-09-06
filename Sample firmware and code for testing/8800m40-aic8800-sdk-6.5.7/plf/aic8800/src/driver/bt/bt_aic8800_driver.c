#include "rtos.h"
#include "bt_aic8800_drvif.h"
#if PLF_BLE_ONLY == 0
#include "bt_task.h"
#include "bt_task_msg.h"
#include "aic_adp_api.h"
#include "app_bt_queue.h"
#else
#include "ble_task.h"
#include "ble_task_msg.h"
#include "aic_ble_adp_api.h"
#include "app_ble_queue.h"
#endif
#include "dma_api.h"
#include "ce_api.h"
#include "reg_sysctrl.h"
#include <string.h>
#include "stdlib.h"
#if AON_SUPPORT == 1
#include "bt_aon_sram.h"
#endif
#include "sysctrl_api.h"
#if (PLF_BT_STACK || PLF_BLE_STACK) && (PLF_WIFI_STACK) && defined(CONFIG_RWNX_LWIP)
#include "wb_coex.h"
#endif
#include "reg_access.h"
#include "reg_iomux.h"
#include "reg_ipc_comreg.h"
#include "reg_ipc_app.h"
#include "sleep_api.h"
#include "bt_patch_table.h"
#include "compiler.h"
#include "system.h"
#include "psim_api.h"

extern void bt_drv_poweron(uint8_t en);


/************************************************************
   bt driver default param config

************************************************************/
#define AICBT_BTMODE_DEFAULT        AICBT_BTMODE_BT_ONLY
#define AICBT_BTPORT_DEFAULT        AICBT_BTPORT_MB
#define AICBT_UART_BAUD_DEFAULT     AICBT_UART_BAUD_1_5M
#define AICBT_UART_FC_DEFAULT       AICBT_UART_FLOWCTRL_ENABLE
#define AICBT_LPM_ENABLE_DEFAULT    0
#define AICBT_TXPWR_LVL_DEFAULT     AICBT_TXPWR_LVL

#define AICBSP_HWINFO_DEFAULT       (-1)
#define AICBSP_CPMODE_DEFAULT       AICBSP_CPMODE_WORK
#define AICBSP_FWLOG_EN_DEFAULT     0

struct aicbt_info_t aicbt_info = {
    .btmode        = AICBT_BTMODE_DEFAULT,
    .btport        = AICBT_BTPORT_DEFAULT,
    .uart_baud     = AICBT_UART_BAUD_DEFAULT,
    .uart_flowctrl = AICBT_UART_FC_DEFAULT,
    .lpm_enable    = AICBT_LPM_ENABLE_DEFAULT,
    .txpwr_lvl     = AICBT_TXPWR_LVL_DEFAULT,
};

struct aicbsp_info_t aicbsp_info = {
    .hwinfo_r = AICBSP_HWINFO_DEFAULT,
    .hwinfo   = AICBSP_HWINFO_DEFAULT,
    .cpmode   = AICBSP_CPMODE_DEFAULT,
    .fwlog_en = AICBSP_FWLOG_EN_DEFAULT,
};


static uint8_t table_index = 0;
uint32_t fw_mem_wr_table[][2] =
{
    //disble uart1 irq in fw
    //{0xe000e180,0x00020000},
};

#define GWB_AGC    0
#define GEN_ACI    0

static uint16_t mdm_table_index = 0;

const uint32_t rf_mdm_regs_table_bt_only[][2] =
{
#if (PLF_HW_ASIC == 1)
    //@ btrf
#if (PLF_WIFI_STACK == 0)
    {0x40580104, 0x000923FB},//for product bt only
#else
    {0x40580104, 0x000933FB},//for product bt+wifi
#endif
    {0x4062201C, 0x0008D000},
    {0x40622028, 0x48912020},//dvdd=1.18v
    {0x40622014, 0x00018983},
    {0x40622054, 0x00008F34},
    {0x40620748, 0x021A01A0},
    {0x40620728, 0x00010020},
    {0x40620738, 0x04800FD4},
    {0x4062073C, 0x00C80064},
    {0x4062202C, 0x000CB220},
    {0x4062200C, 0xE9AD2B45},
    #if (APP_SUPPORT_TWS == 1)
    // dpll for rx = 208m, (tws slave must use this config)
    {0x40622030, 0x143C30D2},
    #else
    // dpll for rx = 52m
    {0x40622030, 0x140C30D2},
    #endif
    //{0x40622000, 0x00000000},//default value
    {0x40622034, 0x00001602},
    {0x40620754, 0x214220FD},
    {0x40620758, 0x0007F01E},
    {0x4062071C, 0x00000A33},
    {0x40622018, 0x00124124},
    {0x4062000C, 0x04040000},
    //@ btrf tx
    {0x40620090, 0x00069082},
    {0x40621034, 0x02003080},
    {0x40621014, 0x0445117A},
    {0x40622024, 0x00001100},
    {0x40622004, 0x0001A9C0},

    //@ pwr up time
    {0x4060048C, 0x00500834},
    {0x40600110, 0x027E0058},
    {0x40600880, 0x00500834},
    {0x40600884, 0x00500834},
    {0x40600888, 0x00500834},
    {0x4060088C, 0x00000834},

#if GWB_AGC
    //@ wb agc
    {0x40620518, 0x3090880A},
    {0x40620514, 0xA80C1A10},
    {0x40620510, 0x1466FF0A},
    {0x406205B8, 0x00000000},
    {0x4062050C, 0x0A202013},

    {0x406205A0, 0x12140505},
    {0x406205A4, 0x42302E24},
#else
    //@ nb agc
    {0x40620518, 0x3692880A},// rsten_srrc
    {0x40620514, 0xA80C1A10},// dagc=0
    {0x4062052C, 0x9C0C1403},// dagc=3, lr
    {0x4062050C, 0x20202013},
    {0x406205A0, 0x14150C00},
    {0x406205A4, 0x362D3624},
    {0x406205F0, 0x0000FF00},
#endif
    //@ cm agc
    {0x40620508, 0x54553132},
    {0x40620530, 0x13171200},
    {0x40620534, 0x00000074},
    {0x406205B0, 0x00005355},
    //@ dc
    {0x4062051C, 0x964B5766},
#if GEN_ACI
    {0x40621878, 0x00000002},
    {0x4062157C, 0x00000040},
    {0x40621580, 0x00000040},
    {0x40621560, 0x051B1200},
    {0x40621564, 0x051B2200},
    {0x40621560, 0x09145640},
    {0x40621564, 0x051B1201},
#endif
#endif
};

const uint32_t rf_mdm_regs_table_bt_combo[][2] =
{
#if (PLF_HW_ASIC == 1)
    //@ btrf
#if (PLF_WIFI_STACK == 0)
    {0x40580104, 0x000923FB},//for product bt only
#else
    {0x40580104, 0x000933FB},//for product bt+wifi
#endif
    {0x40344020, 0x00000B77},
    {0x40344024, 0x006EC594},
    {0x40344028, 0x00009402},
    {0x4034402C, 0x56201884},
    {0x40344030, 0x1A2E5168},

    //@ pwr up time
    {0x4060048C, 0x00500834},
    {0x40600110, 0x027E0058},
    {0x40600880, 0x00500834},
    {0x40600884, 0x00500834},
    {0x40600888, 0x00500834},
    {0x4060088C, 0x00000834},

#if GWB_AGC
    //@ wb agc
    {0x40620518, 0x3090880A},
    {0x40620514, 0xA80C1A10},
    {0x40620510, 0x1466FF0A},
    {0x406205B8, 0x00000000},
    {0x4062050C, 0x0A202013},

    {0x40620508, 0x54553032},
    {0x406205A0, 0x1810120F},
    {0x406205A4, 0x372E2F2E},
    {0x406205F0, 0x00000077},
#else
    //@ nb agc
    {0x40620518, 0x3692880A},// rsten_srrc
    {0x40620514, 0xA80C1A10},// dagc=0
    {0x4062052C, 0x9C0C1403},// dagc=3, lr
    {0x4062050C, 0x20202013},
    {0x40620508, 0x54553132},
    {0x406205A0, 0x0F171600},
    {0x406205A4, 0x36283636},
    {0x406205F0, 0x0000FF00},
#endif
    //@ cm agc
    {0x40620530, 0x13171A00},
    {0x40620534, 0x00000076},
    {0x406205B0, 0x00005355},
    //@ dc
    {0x4062051C, 0x964B5766},
    //@ 26m cic
    {0x40620090, 0x00050032},
    //@ srrc rolloff = 0.305
    {0x40621010, 0x12000143},
#if GEN_ACI
    {0x40621878, 0x00000002},
    {0x4062157C, 0x00000040},
    {0x40621580, 0x00000040},
    {0x40621560, 0x051B1200},
    {0x40621564, 0x051B2200},
    {0x40621560, 0x09145640},
    {0x40621564, 0x051B1201},
#endif
#endif
};
#if PLF_RF_MODE_BT_COMBO
const BtDrvRfModeEnum bt_rf_mode = DRV_RF_MODE_BT_COMBO;
const bt_drv_rf_calib_req_cmd rf_calib_req = {DRV_RF_MODE_BT_COMBO, 0x0000, {0x04, {0x03,0x42,0x26,0x00}}};
#elif PLF_RF_MODE_BTWIFI_COMBO
const BtDrvRfModeEnum bt_rf_mode = DRV_RF_MODE_BTWIFI_COMBO;
const bt_drv_rf_calib_req_cmd rf_calib_req = {DRV_RF_MODE_BTWIFI_COMBO, 0x0000, {0x04, {0x03,0x42,0x26,0x00}}};
#else
const BtDrvRfModeEnum bt_rf_mode = DRV_RF_MODE_BT_ONLY;
const bt_drv_rf_calib_req_cmd rf_calib_req = {DRV_RF_MODE_BT_ONLY, 0x0000, {0x08, {0x03,0x42,0x26,0x00,0x0f,0x30,0x02,0x00}}};
#endif
const uint16_t page_timeout_default_value = 0x2000;
const uint8_t  local_feature[8] = {0xbf,0xee,0xcd,0xfa,0xd8,0x3f,0x7b,0x87};
#ifdef CFG_BTDM_RAM_VER
#if PLF_PMIC
#define AON_BT_PWR_ON_DLY1       (1 + 5)//+5 for safe(not necessary)
#define AON_BT_PWR_ON_DLY2       (10 + 48 + 5)//+48 for dp_open_delay, +5 for safe
#define AON_BT_PWR_ON_DLY3       (12 + 48 + 8 + 5)//+8 for more dp_open_delay than AON_BT_PWR_ON_DLY2, +5 for safe
#define AON_BT_PWR_ON_DLY_AON    (11 + 48 + 8 + 5)//+8 for more dp_open_delay than AON_BT_PWR_ON_DLY2, +5 for safe
#else
#define AON_BT_PWR_ON_DLY1       (1)
#define AON_BT_PWR_ON_DLY2       (10)
#define AON_BT_PWR_ON_DLY3       (12)
#define AON_BT_PWR_ON_DLY_AON    (11)
#endif
const bt_drv_wr_aon_param wr_aon_param =
{
    0x18D700, 0x18F700, 64, 40, 400, 400, 3, 2,
    3, 2, 40, 512, 20, 21, 20, 32,
    8, 0, 0, 20000, 0x101, 0x20067302, AON_BT_PWR_ON_DLY1, AON_BT_PWR_ON_DLY2,
    AON_BT_PWR_ON_DLY3, AON_BT_PWR_ON_DLY_AON, 32, 360, 420, 100, 100, 8,
    24, 40, 140, 0, 64, 20000, 50
};
#else
#if PLF_PMIC
#define AON_BT_PWR_ON_DLY1_U02      (1 + 5)//+5 for safe(not necessary)
#define AON_BT_PWR_ON_DLY2_U02      (10 + 48 + 5)//+48 for dp_open_delay, +5 for safe
#define AON_BT_PWR_ON_DLY3_U02      (12 + 48 + 8 + 5)//+8 for more dp_open_delay than AON_BT_PWR_ON_DLY2, +5 for safe
#define AON_BT_PWR_ON_DLY_AON_U02   (11 + 48 + 8 + 5)//+8 for more dp_open_delay than AON_BT_PWR_ON_DLY2, +5 for safe
#define AON_BT_PWR_ON_DLY1_U03      (1 + 5)//+5 for safe(not necessary)
#define AON_BT_PWR_ON_DLY2_U03      (10 + 48 + 5)//+48 for dp_open_delay, +5 for safe
#define AON_BT_PWR_ON_DLY3_U03      (12 + 48 + 8 + 5)//+8 for more dp_open_delay than AON_BT_PWR_ON_DLY2, +5 for safe
#define AON_BT_PWR_ON_DLY_AON_U03   (11 + 48 + 8 + 5)//+8 for more dp_open_delay than AON_BT_PWR_ON_DLY2, +5 for safe

#define AON_BT_PWR_ON_DLY1x(v)      MCAT(AON_BT_PWR_ON_DLY1_U0, v)
#define AON_BT_PWR_ON_DLY1          AON_BT_PWR_ON_DLY1x(CFG_ROM_VER)
#define AON_BT_PWR_ON_DLY2x(v)      MCAT(AON_BT_PWR_ON_DLY2_U0, v)
#define AON_BT_PWR_ON_DLY2          AON_BT_PWR_ON_DLY2x(CFG_ROM_VER)
#define AON_BT_PWR_ON_DLY3x(v)      MCAT(AON_BT_PWR_ON_DLY3_U0, v)
#define AON_BT_PWR_ON_DLY3          AON_BT_PWR_ON_DLY3x(CFG_ROM_VER)
#define AON_BT_PWR_ON_DLY_AONx(v)   MCAT(AON_BT_PWR_ON_DLY_AON_U0, v)
#define AON_BT_PWR_ON_DLY_AON       AON_BT_PWR_ON_DLY_AONx(CFG_ROM_VER)
#else
#define AON_BT_PWR_ON_DLY1          (1)
#define AON_BT_PWR_ON_DLY1x(v)      AON_BT_PWR_ON_DLY1
#define AON_BT_PWR_ON_DLY2          (10)
#define AON_BT_PWR_ON_DLY2x(v)      AON_BT_PWR_ON_DLY2
#define AON_BT_PWR_ON_DLY3          (12)
#define AON_BT_PWR_ON_DLY2x(v)      AON_BT_PWR_ON_DLY3
#define AON_BT_PWR_ON_DLY_AON       (11)
#define AON_BT_PWR_ON_DLY_AONx(v)   AON_BT_PWR_ON_DLY_AON
#endif

const bt_drv_wr_aon_param VAR_WITH_VERx(wr_aon_param, 2) =
{
    0x16D700, 0x16F680, 64, 40, 400, 400, 3, 2,
    3, 2, 40, 512, 20, 21, 20, 32,
    8, -2, 0, 20000, 0x101, 0x20067302, AON_BT_PWR_ON_DLY1x(2), AON_BT_PWR_ON_DLY2x(2),
    AON_BT_PWR_ON_DLY3x(2), AON_BT_PWR_ON_DLY_AONx(2), 32, 360, 420, 100, 100, 8,
    24, 40, 140, 0, 64, 20000, 50
};

const bt_drv_wr_aon_param VAR_WITH_VERx(wr_aon_param, 3) =
{
    0x16D700, 0x16F680, 64, 40, 400, 400, 3, 2,
    3, 2, 40, 512, 20, 21, 20, 32,
    8, -2, 0, 20000, 0x101, 0x20067302, AON_BT_PWR_ON_DLY1x(3), AON_BT_PWR_ON_DLY2x(3),
    AON_BT_PWR_ON_DLY3x(3), AON_BT_PWR_ON_DLY_AONx(3), 32, 360, 420, 100, 100, 8,
    24, 40, 140, 0, 64, 20000, 50
};
#endif

const bt_drv_wr_aon_param *wr_aon_param_ptr;
uint32_t aon_debug_level;

/*
 *
 *   BT_LP_LEVEL_ACTIVE      = 0x00,//BT CORE active, CPUSYS active, VCORE active
 *   BT_LP_LEVEL_CLOCK_GATE1 = 0x01,//BT CORE clock gate, CPUSYS active, VCORE active
 *   BT_LP_LEVEL_CLOCK_GATE2 = 0x02,//BT CORE clock gate, CPUSYS clock gate, VCORE active
 *   BT_LP_LEVEL_CLOCK_GATE3 = 0x03,//BT CORE clock gate, CPUSYS clock gate, VCORE clock_gate
 *   BT_LP_LEVEL_POWER_OFF1  = 0x04,//BT CORE power off, CPUSYS active, VCORE active
 *   BT_LP_LEVEL_POWER_OFF2  = 0x05,//BT CORE power off, CPUSYS clock gate, VCORE active
 *   BT_LP_LEVEL_POWER_OFF3  = 0x06,//BT CORE power off, CPUSYS power off, VCORE active
 *   BT_LP_LEVEL_HIBERNATE   = 0x07,//BT CORE power off, CPUSYS power off, VCORE power off
 *   BT_LP_LEVEL_NUM         = 0x08,
 */
#if APP_SLEEP_LEVEL == 0
uint8_t bt_lp_level = BT_LP_LEVEL_ACTIVE;
#elif APP_SLEEP_LEVEL == 1
uint8_t bt_lp_level = BT_LP_LEVEL_CLOCK_GATE2;
#elif APP_SLEEP_LEVEL == 2
uint8_t bt_lp_level = BT_LP_LEVEL_POWER_OFF3;
#elif APP_SLEEP_LEVEL == 3
uint8_t bt_lp_level = BT_LP_LEVEL_HIBERNATE;
#else
uint8_t bt_lp_level = BT_LP_LEVEL_ACTIVE;
#endif

uint8_t pwr_ctrl_slave = 1;

uint8_t bt_sleep_debug_level = 0xFF;

uint8_t bt_power_state = BT_POWEROFF;

/************************************************************/

//bt default param set

bool bt_drv_fw_mem_table_isneeded_get(void)
{
    bool ret = false;
    uint32_t remain_size = 0;
    remain_size = sizeof(fw_mem_wr_table)/sizeof(fw_mem_wr_table[0]) - table_index;
    if(remain_size)
        ret = true;
    return ret;
}


bool bt_drv_fw_mem_table_entry_get(uint32_t *addr, uint32_t *val)
{
    bool ret = false;
    if (sizeof(fw_mem_wr_table) == 0 || table_index > (sizeof(fw_mem_wr_table)/sizeof(fw_mem_wr_table[0])-1))
        return ret;
    *addr = fw_mem_wr_table[table_index][0];
    *val  = fw_mem_wr_table[table_index][1];
    table_index++;
    ret = true;
    return ret;
}



bool bt_drv_rf_mdm_regs_table_isneeded_get(void)
{
    bool ret = false;
    uint32_t remain_size = 0;

    if (bt_rf_mode == DRV_RF_MODE_BT_ONLY) {
        remain_size = sizeof(rf_mdm_regs_table_bt_only)/sizeof(rf_mdm_regs_table_bt_only[0]) - mdm_table_index;
    } else if ((bt_rf_mode == DRV_RF_MODE_BT_COMBO) || (bt_rf_mode == DRV_RF_MODE_BTWIFI_COMBO)) {
        remain_size = sizeof(rf_mdm_regs_table_bt_combo)/sizeof(rf_mdm_regs_table_bt_combo[0]) - mdm_table_index;
    }

    if(remain_size)
        ret = true;

    return ret;
}

bool bt_drv_rf_mdm_regs_table_entry_get(uint32_t *addr, uint32_t *val)
{
    bool ret = false;

    if (bt_rf_mode == DRV_RF_MODE_BT_ONLY) {
        if (sizeof(rf_mdm_regs_table_bt_only) == 0 || mdm_table_index > (sizeof(rf_mdm_regs_table_bt_only)/sizeof(rf_mdm_regs_table_bt_only[0])-1))
            return ret;
        *addr = rf_mdm_regs_table_bt_only[mdm_table_index][0];
        *val  = rf_mdm_regs_table_bt_only[mdm_table_index][1];
    } else if ((bt_rf_mode == DRV_RF_MODE_BT_COMBO) || (bt_rf_mode == DRV_RF_MODE_BTWIFI_COMBO)) {
        if (sizeof(rf_mdm_regs_table_bt_combo) == 0 || mdm_table_index > (sizeof(rf_mdm_regs_table_bt_combo)/sizeof(rf_mdm_regs_table_bt_combo[0])-1))
            return ret;
        *addr = rf_mdm_regs_table_bt_combo[mdm_table_index][0];
        *val  = rf_mdm_regs_table_bt_combo[mdm_table_index][1];
    } else {
        return ret;
    }

    mdm_table_index++;

    ret = true;

    return ret;
}


void aic_bt_start(void)
{
    if (!bt_get_fw_init_complete()) {
        #ifdef CFG_BTDM_RAM_VER
        wr_aon_param_ptr = &wr_aon_param;
        #else
        #if (CFG_ROM_VER == 255)
        uint8_t chip_id = ChipIdGet(0);
        if (chip_id == 0x03) {
            wr_aon_param_ptr = &VAR_WITH_VERx(wr_aon_param, 2);
        } else if (chip_id == 0x07) {
            wr_aon_param_ptr = &VAR_WITH_VERx(wr_aon_param, 3);
        }
        #else
        wr_aon_param_ptr = &VAR_WITH_VER(wr_aon_param);
        #endif
        bt_patch_prepare();
        #endif
        aon_debug_level = wr_aon_param_ptr->aon_debug_level;
        psim_init();
        bt_drv_poweron(BT_POWERON);
    }
}

void aic_bt_close(void)
{
    if (bt_get_fw_init_complete()) {
        bt_drv_poweron(BT_POWEROFF);
        mdm_table_index = 0;
        table_index = 0;
    }
}
/************************************************************
*
*  bt driver api which is diffrent for bt or (ble only) mode.
*
************************************************************/
void bt_drv_ecc_key_complete_notify(void)
{
    #if PLF_BLE_ONLY == 0
    app_bt_generate_key_complete();
    #else
    aic_adp_send_generate_key_ble_only();
    #endif
}

void bt_drv_task_notify(bool isr)
{
    #if PLF_BLE_ONLY == 0
    bt_task_queue_notify(isr);
    #else
    ble_task_queue_notify(isr);
    #endif
}

/************************************************************
*
*  bt driver send hci cmd directly
*
************************************************************/
void bt_drv_send_data(const uint8_t *buff,uint8_t len)
{
#if PLF_BLE_ONLY == 0
    aic_adp_send_hci_data_direct(buff, len);
#else
    aic_adp_send_hci_data_direct_ble_only(buff, len);
#endif
}

void bt_drv_lp_level_set(uint8_t level)
{
#if PLF_BLE_ONLY == 0
    app_bt_set_lp_level(level);
#else
    app_ble_lp_level_msg_send(level);
#endif
}

const uint8_t hci_dbg_evt_filter[] =
{
    0x01,0x05, 0x0c, 0x03, 0x02, 0x00, 0x02
};//auto accept connect

const uint8_t hci_dbg_enable_dut[] =
{
    0x01,0x03, 0x18, 0x00
};
const uint8_t hci_dbg_enable_allscan[] =
{
    0x01, 0x1a, 0x0c, 0x01, 0x03
};
const uint8_t hci_dbg_enable_pagescan[] =
{
    0x01, 0x1a, 0x0c, 0x01, 0x02
};

const uint8_t hci_dbg_enable_inquiryscan[] =
{
    0x01, 0x1a, 0x0c, 0x01, 0x01
};

const uint8_t hci_dbg_enable_noscan[] =
{
    0x01, 0x1a, 0x0c, 0x01, 0x00
};

void bt_drv_enable_dut(void)
{
    bt_drv_send_data(hci_dbg_evt_filter, sizeof(hci_dbg_evt_filter));
    bt_drv_send_data(hci_dbg_enable_allscan, sizeof(hci_dbg_enable_allscan));
    bt_drv_send_data(hci_dbg_enable_dut, sizeof(hci_dbg_enable_dut));
}

void bt_drv_scan_en(uint32_t scan_en)
{
    if (scan_en == 0) {
        bt_drv_send_data(hci_dbg_enable_noscan, sizeof(hci_dbg_enable_noscan));
    } else if (scan_en == 1) {
        bt_drv_send_data(hci_dbg_enable_inquiryscan, sizeof(hci_dbg_enable_inquiryscan));
    } else if (scan_en == 2) {
        bt_drv_send_data(hci_dbg_enable_pagescan, sizeof(hci_dbg_enable_pagescan));
    } else if (scan_en == 3) {
        bt_drv_send_data(hci_dbg_enable_allscan, sizeof(hci_dbg_enable_allscan));
    }
}

#if PLF_BT_TESTMODE
int bt_drv_enter_non_signaling_test(void)
{
    PMIC_MEM_MASK_WRITE((unsigned int)0x50018c00, 0x80100000, 0xffffffff);
    pmic_chip_reboot(0xFF);
    return 0;
}
/**
 * Functions
 */
void bt_drv_non_signaling_test_iram_init(void)
{
    uint32_t *dst = (uint32_t *)0x00100000;
    uint32_t *src;
    uint32_t idx,len;
    #if AICBT_BTMODE_DEFAULT == AICBT_BTMODE_BT_ONLY
    #if PLF_PMIC_VER_LITE == 1
    #include "bt_only_lite_555.h"
    src = bt_only_lite_555;
    len = AICBT_BT_ONLY_LITE_555_SIZE / sizeof(uint32_t);
    #elif PLF_PMIC_VER_AUD == 1
    #include "bt_only_aud_434.h"
    src = bt_only_aud_434;
    len = AICBT_BT_ONLY_AUD_434_SIZE / sizeof(uint32_t);
    #else
    #error "Invalid aic8800m PMIC VER"
    #endif
    #elif AICBT_BTMODE_DEFAULT == AICBT_BTMODE_BT_WIFI_COMBO
    #if PLF_PMIC_VER_LITE == 1
    #include "bt_combo_lite_555.h"
    src = bt_combo_lite_555;
    len = AICBT_BT_COMBO_LITE_555_SIZE / sizeof(uint32_t);
    #elif PLF_PMIC_VER_AUD == 1
    #include "bt_combo_aud_555.h"
    src = bt_combo_aud_555;
    len = AICBT_BT_COMBO_AUD_555_SIZE / sizeof(uint32_t);
    #else
    #error "Invalid aic8800m PMIC VER"
    #endif
    #else
    #error "Invalid aic8800m40 bt mode"
    #endif
    for (idx = 0; idx < len; idx++) {
        *dst = *src;
        dst++;
        src++;
    }
}


#endif
