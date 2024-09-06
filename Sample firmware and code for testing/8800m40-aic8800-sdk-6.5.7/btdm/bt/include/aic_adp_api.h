#ifndef _AIC_ADP_API_H_
#define _AIC_ADP_API_H_
#include "tgt_cfg_bt.h"
#include "aic_adp_type.h"

#include "aic_adp_mgr.h"
#include "aic_adp_a2dp.h"
#include "aic_adp_avrcp.h"
#include "aic_adp_dev.h"
#include "aic_adp_hfp.h"
#include "aic_adp_hsp.h"
#include "aic_adp_spp.h"
#include "aic_adp_hid.h"
#include "aic_adp_test.h"
#include "aic_adp_tws.h"
#include "flash_api_btdm.h"
#include "aic_host_cfg.h"

void aic_stack_loop(void);
void aic_stack_init(aic_host_cfg_t cfg);
void aic_adp_mgr_init(void);
void aic_adp_register_app_msg_handle(aic_bt_msg_module module,app_msg_handle_cb callback);

APP_BT_MGR *aic_adp_get_app_bt_mgr_ptr(void);
void aic_adp_send_generate_key(void);
void aic_adp_set_cod(bt_class_of_device cod);
void aic_adp_set_pin_code(char * pin_code ,U8 len);
void aic_adp_set_pass_key(char * pass_key ,U8 len);
void aic_adp_set_io_capabilities(bt_iocapabilities io_cap);
void aic_adp_set_lp_level(uint8_t level);
Status_BTDef aic_adp_inquiry_cancel(void);
Status_BTDef aic_adp_inquiry(U8 len, U8 maxResp);
Status_BTDef aic_adp_set_bt_name(const U8 *name, U8 length);
Status_BTDef aic_adp_update_bt_eir(void);
Status_BTDef aic_adp_sco_switch(uint16_t        scohandle);
Status_BTDef aic_adp_role_switch(BT_ADDR bdaddr);
void aic_adp_disconnect_acl(BT_ADDR bdaddr);
Status_BTDef aic_adp_stop_sniff(BT_ADDR bdaddr);
Status_BTDef aic_adp_set_scan_mode(AppBtScanMode mode);
Status_BTDef aic_adp_set_linkpolicy(BT_ADDR bdaddr, AppBtLinkPolicy policy);
Status_BTDef aic_adp_set_sniff_timer(BT_ADDR bdaddr,         AppBtSniffInfo* sniff_info,TimeT Time);
BOOL app_bt_check_invalid_bdaddr(BT_ADDR *bdaddr);
void aic_adp_save_flash(void);
void aic_adp_close_dev(void);
btdev_info* aic_adp_get_devinfo_by_addr(BT_ADDR *bdAddr);
uint8_t aic_adp_get_current_activeCons(void);
BOOL aic_adp_stack_config(void);
void aic_adp_erased_flash(void);
void aic_adp_send_hci_data_direct(const uint8_t *buff,uint8_t len);
APP_DEVLIST *aic_adp_get_a2dp_current_devinfo(void);
APP_DEVLIST *aic_adp_get_hfp_current_devinfo(void);
APP_DEVLIST *aic_adp_get_hsp_current_devinfo(void);
#if PLF_BLE_STACK && PLF_BLE_ONLY == 0
void aic_adp_rw_timer_notify(void);
#endif
void aic_change_host_log_level(BOOL flag,U32 level);
#endif
