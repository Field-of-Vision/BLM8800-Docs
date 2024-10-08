#ifndef __RF_CONFIG_H
#define __RF_CONFIG_H

#include "reg_wlan_rf.h"
#include "reg_bt_rf.h"
#include "reg_wcnaon.h"

extern uint32_t wifi_rxgain_table_24g[48][4];
extern uint32_t wifi_rxgain_table_5g[32][4];
extern uint32_t wifi_txgain_table_24g[32];
extern uint32_t wifi_txgain_table_5g[16];

extern void wlan_rf_config(uint8_t band);
extern void bt_rf_config(void);
extern void common_rf_config(void);
extern void bt_only_mdm_config(void);
extern void bt_combo_mdm_config(void);
extern void init_aon_ram(void);
extern void update_rxgain_table(uint32_t wifi_rxgain_2g4_addr, uint32_t wifi_rxgain_5g_addr);
extern void rf_pll_recalib(void);
extern void rf_switch_config(void);


#endif
