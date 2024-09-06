#ifndef __BT_DRV_INTERFACE_H__
#define  __BT_DRV_INTERFACE_H__

#include "stdint.h"
#include "stdbool.h"
#include "bt_aic8800_driver.h"
#include "tgt_cfg_bt.h"

extern const BtDrvRfModeEnum bt_rf_mode;
extern const bt_drv_rf_calib_req_cmd rf_calib_req;
extern const uint16_t page_timeout_default_value;
extern const uint8_t  local_feature[8];
extern const bt_drv_wr_aon_param *wr_aon_param_ptr;
extern uint32_t aon_debug_level;
extern uint8_t bt_lp_level;
extern uint8_t pwr_ctrl_slave;
extern uint8_t bt_sleep_debug_level;
extern uint8_t bt_power_state;

void aic_bt_start(void);
void aic_bt_close(void);
void bt_drv_clk_en(void);

/********************************************
* ecc encript api
********************************************/
//start
void bt_drv_start_generate_key(void);
void bt_drv_generate_secret_key(void);
void bt_drv_pool_key_complete(void);
int bt_drv_set_BasePoint_y_256_vaule(uint8_t* ptr ,uint16_t len);
int bt_drv_set_BasePoint_x_256_vaule(uint8_t* ptr ,uint16_t len);
//end
TWS_BT_CLK_INFO_Type rwip_clk_offset_read(void);
rwip_time_t rwip_time_read(void);
bool bt_drv_fw_mem_table_isneeded_get(void);
bool bt_drv_fw_mem_table_entry_get(uint32_t *addr, uint32_t *val);
uint32_t bt_drv_get_reg_addr_in_aon(uint32_t reg_addr);
bool bt_drv_rf_mdm_regs_table_isneeded_get(void);
bool bt_drv_rf_mdm_regs_table_entry_get(uint32_t *addr, uint32_t *val);

void bt_drv_fw_patch_table_init(void);
void bt_drv_fw_patch_init_b4_fw_init(void);
void bt_drv_fw_extra_patch_init_b4_fw_init(void);
void bt_drv_fw_patch_init_after_fw_init(void);
void bt_drv_minisys_patch_init_b4_minisys_init(void);
void bt_drv_minisys_extra_patch_init_b4_minisys_init(void);
void bt_drv_minisys_patch_init_after_minisys_init(void);

/**
*   wait for firmware init complete
*   bit 6 : 0:not ready  1:ready
*/
bool bt_get_fw_init_complete(void);
void bt_drv_enable_dut(void);
void bt_drv_scan_en(uint32_t scan_en);
void bt_sleep_entry_init(void);
void bt_prevent_sleep_set(uint32_t prv_slp_bit);
void bt_prevent_sleep_clear(uint32_t prv_slp_bit);
uint32_t bt_prevent_sleep_get(void);
#if PLF_BT_TESTMODE
int bt_drv_enter_non_signaling_test(void);
void bt_drv_non_signaling_test_iram_init(void);
#endif
#endif

