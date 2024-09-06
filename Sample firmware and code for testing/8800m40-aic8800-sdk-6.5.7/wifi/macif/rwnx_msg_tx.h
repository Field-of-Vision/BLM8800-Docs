/**
 ****************************************************************************************
 *
 * @file rwnx_msg_tx.h
 *
 * @brief TX function declarations
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ****************************************************************************************
 */

#ifndef _RWNX_MSG_TX_H_
#define _RWNX_MSG_TX_H_

#include "rwnx_defs.h"

typedef struct {
    /// Access Category index
    uint8_t aci;
    /// Arbitration InterFrame Space Number
    uint8_t aifsn;
    /// Contention Window minimum
    uint16_t cwmin;
    /// Contention Window maximum
    uint16_t cwmax;
    /// TXOP (in unit of 32us)
    uint16_t txop;
} rwnx_edca_param_t;

#if (PLF_AIC8800)
typedef struct {
    int8_t pwridx_comp_5g;
} rwnx_txpwr_comp_t;
#endif

int rwnx_send_reset(void);
int rwnx_send_start(struct mm_start_req *start);
int rwnx_send_version_req(struct mm_version_cfm *cfm);
int rwnx_send_add_if(unsigned char *mac, uint8_t iftype, bool p2p, struct mm_add_if_cfm *cfm);
int rwnx_send_remove_if(uint8_t vif_index);
int rwnx_send_me_chan_config_req(struct me_chan_config_req *chan_cfg);
int rwnx_send_me_config_req(struct me_config_req *cfg_req);
int rwnx_set_hw_idle_req(uint8_t idle);
int rwnx_send_set_edca(int fhost_vif_idx, rwnx_edca_param_t *edca_param);
int rwnx_set_disable_agg_req(uint8_t agg_disable, uint8_t agg_disable_rx, uint8_t sta_idx);
int rwnx_set_coex_config_req(uint8_t disable_coexnull, uint8_t enable_periodic_timer, uint8_t enable_nullcts,
                                    uint8_t coex_timeslot_set, uint32_t param1, uint32_t param2);
#if (PLF_AIC8800)
int rwnx_set_rf_config_req(void);
#elif (PLF_AIC8800MC || PLF_AIC8800M40)
int rwnx_set_rf_config_req(uint8_t ofst, uint8_t sel, uint8_t *tbl, uint8_t len);
#endif
int rwnx_set_rf_calib_req(struct mm_set_rf_calib_cfm *cfm);
#if (PLF_AIC8800)
int rwnx_send_txpwr_idx_req(void);
int rwnx_send_txpwr_ofst_req_8800(void);
void rwnx_set_txpwr_comp_8800(rwnx_txpwr_comp_t *txpwr_comp);
void rwnx_enable_tx_adaptivity_8800(void);
#else
int rwnx_send_txpwr_lvl_req(void);
#if (PLF_AIC8800MC)
int rwnx_send_txpwr_ofst_req_8800mc(void);
#elif (PLF_AIC8800M40)
int rwnx_send_txpwr_ofst_req_8800m40(void);
#endif
#endif
int rwnx_send_vendor_ie_req(uint8_t *ies, uint16_t ie_len);
#if (PLF_AIC8800M40) || (PLF_AIC8800MC)
int rwnx_send_vendor_hwconfig_req(void *config_param);
void aic_ipcam_setting(void);
#endif
int rwnx_send_dbg_mem_read_req(uint32_t mem_addr,
                               struct dbg_mem_read_cfm *cfm);
int rwnx_send_dbg_start_app_req(uint32_t boot_addr,
                                uint32_t boot_type);
int rwnx_send_msg_tx(lmac_task_id_t dst_id, lmac_msg_id_t msg_id, uint16_t msg_len, void *msg, int reqcfm, lmac_msg_id_t reqid, void *cfm);
int rwnx_send_get_sta_info_req(uint8_t sta_idx,
                                struct mm_get_sta_info_cfm *cfm);

#endif /* _RWNX_MSG_TX_H_ */
