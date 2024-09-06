/**
 ****************************************************************************************
 *
 * @file fhost_config.h
 *
 * @brief Definition of configuration for Fully Hosted firmware.
 *
 * Copyright (C) RivieraWaves 2017-2019
 *
 ****************************************************************************************
 */
#ifndef _FHOST_CONFIG_H_
#define _FHOST_CONFIG_H_

/**
 ****************************************************************************************
 * @addtogroup FHOST
 * @{
 ****************************************************************************************
 */

#include "rwnx_config.h"
#include "msg.h"
#include "fhost_api.h"
#include "tgt_cfg_wifi.h"

#ifndef FHOST_CONSOLE_LOW_POWER_CASE
#define FHOST_CONSOLE_LOW_POWER_CASE 0
#endif
#ifndef FHOST_CONSOLE_MQTT_CASE
#define FHOST_CONSOLE_MQTT_CASE      0
#endif

/**
 * WiFi RF optimization for aic8800mc
 *  RF_OPT0: for anti-interference
 *  RF_OPT1: for long distance
 */
#ifndef CONFIG_WIFI_RF_OPT0
#define CONFIG_WIFI_RF_OPT0 0
#endif
#ifndef CONFIG_WIFI_RF_OPT1
#define CONFIG_WIFI_RF_OPT1 0
#endif

/**
 * WiFi RF configuration for aic8800
 */
#ifndef CONFIG_WIFI_RF_SWITCH_ENABLE
#define CONFIG_WIFI_RF_SWITCH_ENABLE    0
#endif

/**
 * WiFi TX adaptivity enabled or not
 */
#ifndef CONFIG_WIFI_TX_ADAPTIVITY_ENABLE
#define CONFIG_WIFI_TX_ADAPTIVITY_ENABLE    0
#endif

/**
 * WiFi tx power index, 2 methods supported
 * 1) [TXPWR_IDX_ENABLE=1] Rate groups: dsss, lowrate/64qam/256qam/1024qam at 2.4GHz/5GHz
 * 2) [TXPWR_IDX_ENABLE=2] Every rate is controlled accurately
 *  3-group at 2.4GHz: 11b/11ag, 11n/11ac, 11ax
 *  3-group at 5GHz: 11ag, 11n/11ac, 11ax
 */
#ifndef CONFIG_WIFI_TXPWR_IDX_ENABLE
#define CONFIG_WIFI_TXPWR_IDX_ENABLE            2
#endif
// [TXPWR_IDX_ENABLE=1]
#ifndef CONFIG_WIFI_TXPWR_IDX_DSSS
#define CONFIG_WIFI_TXPWR_IDX_DSSS              9
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_OFDM_LOWRATE_2G4
#define CONFIG_WIFI_TXPWR_IDX_OFDM_LOWRATE_2G4  8
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_OFDM_64QAM_2G4
#define CONFIG_WIFI_TXPWR_IDX_OFDM_64QAM_2G4    8
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_OFDM_256QAM_2G4
#define CONFIG_WIFI_TXPWR_IDX_OFDM_256QAM_2G4   8
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_OFDM_1024QAM_2G4
#define CONFIG_WIFI_TXPWR_IDX_OFDM_1024QAM_2G4  8
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_OFDM_LOWRATE_5G
#define CONFIG_WIFI_TXPWR_IDX_OFDM_LOWRATE_5G   10
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_OFDM_64QAM_5G
#define CONFIG_WIFI_TXPWR_IDX_OFDM_64QAM_5G     9
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_OFDM_256QAM_5G
#define CONFIG_WIFI_TXPWR_IDX_OFDM_256QAM_5G    9
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_OFDM_1024QAM_5G
#define CONFIG_WIFI_TXPWR_IDX_OFDM_1024QAM_5G   8
#endif
// [TXPWR_IDX_ENABLE=2]
#ifndef CONFIG_WIFI_TXPWR_IDX_11B_11AG_2G4
#define CONFIG_WIFI_TXPWR_IDX_11B_11AG_2G4 \
    { 9,    9,    9,    9,    8,    8,    8,    8,    8,    8,    8,    8}
    //1M,   2M,   5M5,  11M,  6M,   9M,   12M,  18M,  24M,  36M,  48M,  54M
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_11N_11AC_2G4
#define CONFIG_WIFI_TXPWR_IDX_11N_11AC_2G4 \
    { 8,    8,    8,    8,    8,    8,    8,    8,    8,    8}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_11AX_2G4
#define CONFIG_WIFI_TXPWR_IDX_11AX_2G4 \
    { 8,    8,    8,    8,    8,    8,    8,    8,    8,    8,    8,    8}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9, MCS10,MCS11
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_11AG_5G
#define CONFIG_WIFI_TXPWR_IDX_11AG_5G \
    { 10,   10,   10,   10,   10,   10,   9,    9}
    //6M,   9M,   12M,  18M,  24M,  36M,  48M,  54M
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_11N_11AC_5G
#define CONFIG_WIFI_TXPWR_IDX_11N_11AC_5G \
    { 10,   10,   10,   10,   10,   9,    9,    9,    9,    9}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9
#endif
#ifndef CONFIG_WIFI_TXPWR_IDX_11AX_5G
#define CONFIG_WIFI_TXPWR_IDX_11AX_5G \
    { 10,   10,   10,   10,   10,   9,    9,    9,    9,    9,    8,    8}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9, MCS10,MCS11
#endif

/**
 * WiFi tx power level for aic8800mc
 *  3-group at 2.4GHz: 11b/11ag, 11n/11ac, 11ax
 *  3-group at 5GHz: 11a, 11n/11ac, 11ax
 */
#ifndef CONFIG_WIFI_TXPWR_LVL_ENABLE
#define CONFIG_WIFI_TXPWR_LVL_ENABLE    0
#endif
#ifndef CONFIG_WIFI_TXPWR_LVL_11B_11AG_2G4
#define CONFIG_WIFI_TXPWR_LVL_11B_11AG_2G4 \
    { 17,   17,   17,   17,   15,   15,   15,   15,   15,   15,   14,   14}
    //1M,   2M,   5M5,  11M,  6M,   9M,   12M,  18M,  24M,  36M,  48M,  54M
#endif
#ifndef CONFIG_WIFI_TXPWR_LVL_11N_11AC_2G4
#define CONFIG_WIFI_TXPWR_LVL_11N_11AC_2G4 \
    { 15,   15,   15,   15,   15,   14,   14,   14,   13,   13}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9
#endif
#ifndef CONFIG_WIFI_TXPWR_LVL_11AX_2G4
#define CONFIG_WIFI_TXPWR_LVL_11AX_2G4 \
    { 15,   15,   15,   15,   15,   14,   14,   14,   13,   13,   13,   13}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9, MCS10,MCS11
#endif
#ifndef CONFIG_WIFI_TXPWR_LVL_11A_5G
#define CONFIG_WIFI_TXPWR_LVL_11A_5G \
    { 0x80, 0x80, 0x80, 0x80, 18,   18,   18,   18,   16,   16,   15,   15}
    //NA,   NA,   NA,   NA,   6M,   9M,   12M,  18M,  24M,  36M,  48M,  54M
#endif
#ifndef CONFIG_WIFI_TXPWR_LVL_11N_11AC_5G
#define CONFIG_WIFI_TXPWR_LVL_11N_11AC_5G \
    { 18,   18,   18,   18,   16,   16,   15,   15,   14,   14}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9
#endif
#ifndef CONFIG_WIFI_TXPWR_LVL_11AX_5G
#define CONFIG_WIFI_TXPWR_LVL_11AX_5G \
    { 18,   18,   18,   18,   16,   16,   14,   14,   13,   13,   12,   12}
    //MCS0, MCS1, MCS2, MCS3, MCS4, MCS5, MCS6, MCS7, MCS8, MCS9, MCS10,MCS11
#endif

/**
 * WiFi tx power offset
 *  3-group at 2.4GHz: chan1~4, chan5~9, chan10~13
 *  4-group at 5GHz: chan36~64, chan100~120, chan122~140, chan142~165
 */
#ifndef CONFIG_WIFI_TXPWR_OFST_ENABLE
#define CONFIG_WIFI_TXPWR_OFST_ENABLE       0
#endif
#ifndef CONFIG_WIFI_TXPWR_OFST_CHAN_1_4
#define CONFIG_WIFI_TXPWR_OFST_CHAN_1_4     0
#endif
#ifndef CONFIG_WIFI_TXPWR_OFST_CHAN_5_9
#define CONFIG_WIFI_TXPWR_OFST_CHAN_5_9     0
#endif
#ifndef CONFIG_WIFI_TXPWR_OFST_CHAN_10_13
#define CONFIG_WIFI_TXPWR_OFST_CHAN_10_13   0
#endif
#ifndef CONFIG_WIFI_TXPWR_OFST_CHAN_36_64
#define CONFIG_WIFI_TXPWR_OFST_CHAN_36_64   0
#endif
#ifndef CONFIG_WIFI_TXPWR_OFST_CHAN_100_120
#define CONFIG_WIFI_TXPWR_OFST_CHAN_100_120 0
#endif
#ifndef CONFIG_WIFI_TXPWR_OFST_CHAN_122_140
#define CONFIG_WIFI_TXPWR_OFST_CHAN_122_140 0
#endif
#ifndef CONFIG_WIFI_TXPWR_OFST_CHAN_142_165
#define CONFIG_WIFI_TXPWR_OFST_CHAN_142_165 0
#endif

/**
 * WiFi tx power offset2x for aic8800m40
 *  3-rate_type & 3-channel_group at 2.4GHz: (dsss, high, low)*(ch1-4, ch5-9, ch10-13)
 *  3-rate_type & 6-channel_group at 5GHz: (low, high, mid)*(ch42, ch58, ch106, ch122, ch138, ch155)
 */
#ifndef CONFIG_WIFI_TXPWR_OFST_BAND_2G4
#define CONFIG_WIFI_TXPWR_OFST_BAND_2G4 \
    { /* ch1-4, ch5-9, ch10-13 */ \
        {   0,    0,    0   }, /* 11b           */ \
        {   0,    0,    0   }, /* ofdm_highrate */ \
        {   0,    0,    0   }  /* ofdm_lowrate  */ \
    }
#endif
#ifndef CONFIG_WIFI_TXPWR_OFST_BAND_5G
#define CONFIG_WIFI_TXPWR_OFST_BAND_5G \
    { /* ch42, ch58, ch106, ch122,ch138,ch155 */ \
        {   0,    0,    0,    0,    0,    0   }, /* ofdm_lowrate  */ \
        {   0,    0,    0,    0,    0,    0   }, /* ofdm_highrate */ \
        {   0,    0,    0,    0,    0,    0   }  /* ofdm_midrate  */ \
    }
#endif

/**
 * WiFi tx power loss
 */
#ifndef CONFIG_WIFI_TXPWR_LOSS_ENABLE
#define CONFIG_WIFI_TXPWR_LOSS_ENABLE       0
#endif
#ifndef CONFIG_WIFI_TXPWR_LOSS_VALUE
#define CONFIG_WIFI_TXPWR_LOSS_VALUE        0
#endif

/**
 * WiFi stack params
 *  CONFIG_WIFI_BCN_LINKLOSS_THD: beacon count threshold for linkloss detection
 *  CONFIG_WIFI_PS_KEEP_ALIVE_TIME_US: max tx time interval for keep alive in ps mode
 *  CONFIG_WIFI_ACTIVE_SCAN_TIME_US: active scan time period at a channel
 *  CONFIG_WIFI_PASSIVE_SCAN_TIME_US: passive scan time period at a channel
 *  CONFIG_WIFI_LOG_DEBUG_MASK: fw log debug mask
 */
#ifndef CONFIG_WIFI_BCN_LINKLOSS_THD
#define CONFIG_WIFI_BCN_LINKLOSS_THD        100
#endif
#if (CONFIG_WIFI_TX_ADAPTIVITY_ENABLE)
#undef CONFIG_WIFI_BCN_LINKLOSS_THD
#define CONFIG_WIFI_BCN_LINKLOSS_THD        10
#elif (PLF_WIFI_AUDIO)
#undef CONFIG_WIFI_BCN_LINKLOSS_THD
#define CONFIG_WIFI_BCN_LINKLOSS_THD        32
#endif
#ifndef CONFIG_WIFI_PS_KEEP_ALIVE_TIME_US
#define CONFIG_WIFI_PS_KEEP_ALIVE_TIME_US   60000000
#endif
#ifndef CONFIG_WIFI_ACTIVE_SCAN_TIME_US
#define CONFIG_WIFI_ACTIVE_SCAN_TIME_US     30000
#endif
#ifndef CONFIG_WIFI_PASSIVE_SCAN_TIME_US
#define CONFIG_WIFI_PASSIVE_SCAN_TIME_US    110000
#endif
#ifndef CONFIG_WIFI_LP_WAKEUP_OFFSET_US
#if PLF_AIC8800MC
#define CONFIG_WIFI_LP_WAKEUP_OFFSET_US     700
#elif PLF_AIC8800M40
#define CONFIG_WIFI_LP_WAKEUP_OFFSET_US     900
#endif
#endif
#ifndef CONFIG_WIFI_LOG_DEBUG_MASK
#define CONFIG_WIFI_LOG_DEBUG_MASK          0x8d08
#endif

/**
 * WiFi country code string
 *  Supported country codes: "00", "CA", "CN", "US"
 */
#ifndef CONFIG_WIFI_COUNTRY_CODE
#define CONFIG_WIFI_COUNTRY_CODE            "00"
#endif

/**
 * WiFi default mac address
 */
#ifndef CONFIG_DEFAULT_MAC_ADDRESS
#define CONFIG_DEFAULT_MAC_ADDRESS          {0x88, 0x00, 0x33, 0x77, 0x69, 0xCC}
#endif

typedef struct {
    uint8_t first_chan;
    uint8_t chan_cnt;
    int8_t power;
    uint8_t flags;
} wifi_regrule_t;

typedef struct {
    char cc[3]; // country code string
    uint8_t reg_rules_cnt;
    wifi_regrule_t reg_rules_arr[];
} wifi_regdom_t;

extern struct me_chan_config_req fhost_chan;

/**
 ****************************************************************************************
 * @brief Initialize wifi configuration structure from fhost configuration
 *
 * To be called before initializing the wifi stack.
 * Can also be used to retrieve firmware feature list at run-time. In this case @p init
 * is false.
 *
 * @param[out] me_config     Configuration structure for the UMAC (i.e. ME task)
 * @param[out] start         Configuration structure for the LMAC (i.e. MM task)
 * @param[out] base_mac_addr Base MAC address of the device (from which all VIF MAC
 *                           addresses are computed)
 * @param[in]  init          Whether it is called before firmware initialization or not.
 ****************************************************************************************
 */
void fhost_config_prepare(struct me_config_req *me_config, struct mm_start_req *start,
                          struct mac_addr *base_mac_addr, bool init);

/**
 ****************************************************************************************
 * @brief Return the channel associated to a given frequency
 *
 * @param[in] freq Channel frequency
 *
 * @return Channel definition whose primary frequency is the requested one and NULL if
 * there no such channel.
 ****************************************************************************************
 */
struct mac_chan_def *fhost_chan_get(int freq);

int fhost_chan_update(const char * country_code);

extern void set_mac_address(uint8_t *addr);
extern void set_blink_magic(uint8_t *addr);
extern uint8_t* get_mac_address(void);
extern uint8_t get_blink_magic(void);

void fhost_mac_address_acquire(void);
const char * fhost_config_name_get(enum fhost_config_id id);
uint32_t fhost_config_value_get(enum fhost_config_id id);
void fhost_config_value_set(enum fhost_config_id id, uint32_t val);

#if (PLF_AIC8800)
void fhost_config_txpwr_idx_get(txpwr_idx_fine_conf_t *conf);
#else
void fhost_config_txpwr_lvl_get(txpwr_lvl_conf_t *conf);
#endif
void fhost_config_txpwr_ofst_get(txpwr_ofst_conf_t *conf);
void fhost_config_txpwr_ofst2x_get(txpwr_ofst2x_conf_t *conf);
void fhost_config_txpwr_loss_get(txpwr_loss_conf_t *conf);

/**
 * @}
 */
#endif /* _FHOST_CONFIG_H_ */
