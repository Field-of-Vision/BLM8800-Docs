#ifndef __RF_CONFIG_H
#define __RF_CONFIG_H

#include "reg_wlan_rf.h"
//#include "reg_bt_rf.h"
#include "reg_wcnaon.h"

extern int wifi_rf_config(void);
extern void bt_rf_config(void);
extern void common_rf_config(void);
extern void bt_only_mdm_config(void);
extern void bt_combo_mdm_config(void);
extern void rf_pll_recalib(void);


#endif
