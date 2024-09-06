#ifndef AICADPMGR
#define AICADPMGR
#include "bt_types_def.h"
#include "aic_host_cfg.h"

void aic_stack_init_ble_only(aic_host_cfg_t cfg);
BOOL aic_adp_stack_config_ble_only(void);
void aic_stack_loop_ble_only(void);
void aic_adp_send_hci_data_direct_ble_only(const uint8_t *buff,uint8_t len);
void aic_adp_send_generate_key_ble_only(void);
void aic_adp_set_lp_level_ble_only(uint8_t level);
void aic_adp_ble_deinit(void);
void aic_adp_free_stack_memory_ble_only(void);
void aic_adp_rw_timer_notify(void);
#endif
