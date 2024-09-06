#ifndef AICADPHSP
#define AICADPHSP

#include "bt_types_def.h"


void aic_adp_hsp_init(void);

void aic_adp_hsp_register(   void);
Status_BTDef aic_adp_hsp_send_volume(BT_ADDR bdaddr,uint8_t Gain);
Status_BTDef aic_adp_hsp_send_ckpd_control(BT_ADDR bdaddr);

Status_BTDef aic_adp_hs_connect(BT_ADDR bdaddr);
Status_BTDef aic_adp_hs_sco_connect(BT_ADDR bdaddr);
Status_BTDef aic_adp_hs_sco_disconnect(BT_ADDR bdaddr);
Status_BTDef aic_adp_hs_disconnect(BT_ADDR bdaddr);



#endif
