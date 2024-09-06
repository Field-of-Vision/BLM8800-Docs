#include "rtos.h"
#include "bt_aic8800mc_drvif.h"
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
#include "pmic_api.h"

extern void bt_drv_poweron(uint8_t en);


/************************************************************
   bt driver default param config

************************************************************/
#define AICBT_BTMODE_DEFAULT        AICBT_BTMODE_BT_WIFI_COMBO
#define AICBT_BTPORT_DEFAULT        AICBT_BTPORT_MB
#define AICBT_UART_BAUD_DEFAULT     AICBT_UART_BAUD_1_5M
#define AICBT_UART_FC_DEFAULT       AICBT_UART_FLOWCTRL_ENABLE
#define AICBT_LPM_ENABLE_DEFAULT    0
#define AICBT_TXPWR_LVL_DEFAULT     AICBT_TXPWR_LVL_8800dc

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
};

const uint32_t rf_mdm_regs_table_bt_combo[][2] =
{
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
    uint32_t pwrmd = pwrctrl_pwrmd_cpusys_sw_record_getf();
    pwrctrl_pwrmd_cpusys_sw_record_setf(CPU_SYS_POWER_ON_RESET);
    bt_drv_poweron(BT_POWERON);
    pwrctrl_pwrmd_cpusys_sw_record_setf(pwrmd);
}
/************************************************************
*
*  bt driver api which is diffrent for bt or (ble only) mode.
*
************************************************************/

void bt_drv_task_notify(bool isr)
{
    #if PLF_BLE_ONLY == 0
    bt_task_queue_notify(isr);
    #else
    ble_task_queue_notify(isr);
    #endif
}

void aic_bt_close(void)
{
    if (bt_get_fw_init_complete()) {
        bt_drv_poweron(BT_POWEROFF);
    }
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
    PMIC_MEM_WRITE((unsigned int)&AIC_PMU_RTC0->rtc_rg_reserved0, 0x80100000);
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
    #if AICBT_BTMODE_DEFAULT == AICBT_BTMODE_BT_WIFI_COMBO
    #include "testmode18_bt_20230104.h"
    src = testmode18_bt_20230104;
    len = AICBT_TESTMODE18_BT_20230104_SIZE / sizeof(uint32_t);
    #else
    #error "Invalid aic8800mc bt mode"
    #endif
    for (idx = 0; idx < len; idx++) {
        *dst = *src;
        dst++;
        src++;
    }
}

#endif

