#include "rwnx_utils.h"
#include "fhost_config.h"
#include "fmacfw_api.h"
#include "reg_access.h"
#include "system.h"
#include "plf.h"

typedef struct {
    uint8_t aic_tkip_conf;
    uint8_t send_bar;
    uint8_t new_backoff_bw_rise_en;
    uint8_t wdt_en;
    uint16_t wdt_period_secs; // seconds
    uint8_t wdt_reboot_type;
    uint8_t reserved; // for align
    uint16_t pmic_wdt_cnt_secs; // seconds
    uint16_t reserved1;
} wifi_feature_param_t;

typedef struct {
    uint8_t  beacon_linkloss_thd;
    uint8_t  ps_tx_error_max;
    uint16_t bam_inactivity_to_duration;
    uint32_t mm_keep_alive_period;
    uint32_t default_assocrsp_timeout;
    uint32_t default_authrsp_timeout;
    uint32_t scan_active_duration;
    uint32_t scan_passive_duration;
    uint32_t tx_ac0_timeout;
    uint32_t tx_ac1_timeout;
    uint32_t tx_ac2_timeout;
    uint32_t tx_ac3_timeout;
    uint32_t tx_bcn_timeout;
    uint32_t tx_hiq_timeout;
    uint16_t sdio_rx_buf_num_threshold;
    uint16_t sdio_rx_buf_rep_threshold;
    uint16_t deepsleep_notallowed_offset;
    uint16_t ps_activity_to_us;
    uint16_t ps_activity_bcmc_to_us;
    uint16_t ps_activity_uc_to_us;
    uint16_t lp_wakeup_offset;
    uint8_t  tx_he_tb_prog_time;
    uint8_t  tx_agg_finish_dur;
} thresh_param_t;

typedef struct {
    uint8_t host_type;
    uint16_t sdio_desc_cnt;
    uint16_t pkt_cnt_tx_msg;
    uint16_t pkt_cnt_1600;
    uint16_t pkt_cnt_rx_data;
    uint16_t pkt_cnt_rx_msg;
    uint32_t ipc_base_addr;
    uint32_t buf_base_addr;
    uint32_t desc_base_addr;
    uint32_t desc_size;
    uint32_t pkt_base_addr;
    uint32_t pkt_size;
    uint32_t txdesc_cnt[5];
    uint32_t reord_buf_size;
} host_if_param_t;

typedef struct {
    uint32_t rx_ringbuf_start1;
    uint32_t rx_ringbuf_size1;
    uint32_t rx_ringbuf_start2;
    uint32_t rx_ringbuf_size2;
} rx_ringbuf_conf_t;

typedef struct {
    uint32_t ac_param[4];
} ac_param_conf_t;

typedef struct {
    uint8_t fix_txgain_en;
    int8_t  fix_txgain_val;
    int8_t  fix_txgain_val_5g;
    int8_t  fix_1024qam_txgain;
} txgain_conf_t;

typedef struct {
    int8_t  txgain_max_pwr_capa;
    int8_t  txgain_min_pwr_capa;
    int8_t  txgain_max_pwr_dsss;
    int8_t  txgain_min_pwr_dsss;
    int8_t  txgain_max_pwr_ofdm;
    int8_t  txgain_min_pwr_ofdm;
    int8_t  txgain_max_pwr_ofdm_5g;
    int8_t  txgain_min_pwr_ofdm_5g;
} rf_capa_t;

typedef struct {
    wifi_feature_param_t wifi_feature_param;
    thresh_param_t thresh_param;
    host_if_param_t host_if_param;
    rx_ringbuf_conf_t rx_ringbuf_conf;
    ac_param_conf_t ac_param_conf;
    uint32_t clkgate_en_config;
    uint32_t uart_config;
    uint8_t lp_level;
    uint8_t bt_use_wifi_rf;
    uint16_t debug_mask;
    txgain_conf_t txgain_config;
    uint16_t pwr_close_sysdelay;
    uint16_t pwr_open_sysdelay;
    uint8_t use_5g;
    uint8_t clkgate_use_hwbcn;
    uint8_t poweroff_use_hwbcn;
    //append configuration for u03
    int8_t fix_txgain_val_24g_11b;
    uint8_t sdio_send_ampdu;
    uint8_t sdio_send_ampdu_blkcnt_thresh;
    //append configuration after u03
    uint8_t txgain_enhanced_en;
    int8_t txgain_enhanced_lowrate;
    int8_t txgain_enhanced_highrate;
    txpwr_lvl_conf_t txpwr_lvl;
    txpwr_ofst2x_conf_t txpwr_ofst;
    rf_capa_t rf_capability;
    uint8_t device_ipc_en; // DEVICE_IPC enabled or not
    uint8_t custom_msg_cnt; // DEVICE_IPC customer message count
    uint8_t aon_sram_hi_used;
    uint8_t aon_sram_lo_used;
    uint16_t pkt_size_rx_data;// actual size for pkt_rx_data
    uint16_t pkt_size_rx_msg;// actual size for pkt_rx_msg
    uint32_t usb_bt_ram_base_addr;
    uint32_t usb_bt_ram_size;
    uint8_t usb_wifi_fc_trigger_cnt; //packet count that trigger wifi flow control
    uint8_t usb_wifi_fc_recover_cnt; //packet count that exit wifi flow control
    uint8_t usb_wifi_rx_msg_fc_trigger_cnt; //packet count that trigger wifi rx msg flow control
    uint8_t usb_wifi_rx_msg_fc_recover_cnt; //packet count that exit wifi rx msg flow control
    uint8_t usb_bt_fc_trigger_cnt; //packet count that trigger bt flow control
    uint8_t usb_bt_fc_recover_cnt; //packet count that exit bt flow control
    uint8_t usb_fc_algo; //usb flow control algorithm
    uint8_t usb_bt_bulk_int_tx_cfg; //see bulk_int_tx_cfg in usb_bt.h
    uint16_t usb_wlan_fc_timeout; //wifi flow control timeout in seconds, max 299

    uint16_t usb_bt_acl_rx_pkt_size;
    uint16_t usb_bt_acl_rx_max_size;
    uint16_t usb_bt_acl_tx_pkt_size;
    uint8_t usb_bt_acl_rx_pkt_cnt;
    uint8_t usb_bt_acl_tx_pkt_cnt;
    uint16_t usb_bt_cmd_pkt_size;
    uint16_t usb_bt_evt_pkt_size;
    uint8_t usb_bt_cmd_pkt_cnt;
    uint8_t usb_bt_evt_pkt_cnt;
    uint16_t usb_bt_sync_rx_pkt_size;
    uint16_t usb_bt_sync_tx_pkt_size;
    #if 0//def CFG_USB_WLAN_STREAM_OUT
    uint8_t usb_wlan_stream_out_en;
    uint8_t usb_wlan_stream_aggr_cnt;
    uint8_t usb_wlan_stream_desc_total_cnt;
    uint8_t reserved0[1];
    #endif
    uint32_t usb_reboot_addtional_delay;
    uint8_t usb_global_out_nak;
    uint8_t usb_trans_error_reboot;
    uint8_t usb_trans_error_reboot_delay;
    uint8_t deepsleep_ramret_en;
    uint8_t rc_retry_cnt[4];
    uint8_t tx_retry_cnt;
    uint8_t rts_en;
    uint8_t tx_adaptivity_en;
} wifi_settings_t;

#define WIFI_SETTINGS_OFST(mem) (((uint32_t) &((wifi_settings_t *)0)->mem) & ~0x03UL)

extern const uint32_t __ipc_shd_mem_start__[], __ipc_pkt_mem_start__[], __ipc_pkt_mem_size__[];

uint32_t patch_tbl_wifisetting[][2] =
{
    {WIFI_SETTINGS_OFST(host_if_param.sdio_desc_cnt),   0x00000003}, //host_type=3, sdio_desc_cnt=0
    {WIFI_SETTINGS_OFST(host_if_param.pkt_cnt_tx_msg),  0x00000000}, //pkt_cnt_tx_msg, pkt_cnt_1600
    {WIFI_SETTINGS_OFST(host_if_param.pkt_cnt_rx_data), 0x00000013}, //pkt_cnt_rx_data(Not more than 32*1024/1720), pkt_cnt_rx_msg
    {WIFI_SETTINGS_OFST(host_if_param.ipc_base_addr),   (uint32_t)__ipc_shd_mem_start__}, //ipc_base_addr
    {WIFI_SETTINGS_OFST(host_if_param.desc_base_addr),  0x00000000}, //desc_base_addr
    {WIFI_SETTINGS_OFST(host_if_param.desc_size),       0x00000000}, //desc_size
    {WIFI_SETTINGS_OFST(host_if_param.pkt_base_addr),   (uint32_t)__ipc_pkt_mem_start__}, //pkt_base_addr
    {WIFI_SETTINGS_OFST(host_if_param.pkt_size),        (uint32_t)__ipc_pkt_mem_size__}, //pkt_size
    {WIFI_SETTINGS_OFST(host_if_param.txdesc_cnt[0]),   NX_TXDESC_CNT0},
    {WIFI_SETTINGS_OFST(host_if_param.txdesc_cnt[1]),   NX_TXDESC_CNT1},
    {WIFI_SETTINGS_OFST(host_if_param.txdesc_cnt[2]),   NX_TXDESC_CNT2},
    {WIFI_SETTINGS_OFST(host_if_param.txdesc_cnt[3]),   NX_TXDESC_CNT3},
    {WIFI_SETTINGS_OFST(host_if_param.txdesc_cnt[4]),   NX_TXDESC_CNT4},
    {WIFI_SETTINGS_OFST(host_if_param.reord_buf_size),  NX_REORD_BUF_SIZE},
    {WIFI_SETTINGS_OFST(rx_ringbuf_conf.rx_ringbuf_start1), 0x00000000},
    {WIFI_SETTINGS_OFST(rx_ringbuf_conf.rx_ringbuf_size1), (16 * 1024)},
    {WIFI_SETTINGS_OFST(rx_ringbuf_conf.rx_ringbuf_start2), 0x00000000},
    {WIFI_SETTINGS_OFST(rx_ringbuf_conf.rx_ringbuf_size2), (1024 - 12)},
    #if (CONFIG_WIFI_TX_ADAPTIVITY_ENABLE)
    {WIFI_SETTINGS_OFST(ac_param_conf.ac_param[1]),     0x00000000},
    #elif (CONFIG_WIFI_RF_OPT0)
    {WIFI_SETTINGS_OFST(ac_param_conf.ac_param[1]),     0x0005E432},
    #endif
    #if (CONFIG_WIFI_TX_ADAPTIVITY_ENABLE)
    {WIFI_SETTINGS_OFST(tx_adaptivity_en),              0xf6140001}, //tx_adaptivity_en=1, tx_keep_in_order_en=0, rf_capability.txgain_max_pwr_capa=20, rf_capability.txgain_min_pwr_capa=-10
    #endif
    {WIFI_SETTINGS_OFST(usb_global_out_nak),            0x011e0100}, //usb_global_out_nak=0,usb_trans_error_reboot=1,usb_trans_error_reboot_delay=30,deepsleep_ramret_en=1
    {WIFI_SETTINGS_OFST(lp_level),                      (CONFIG_WIFI_LOG_DEBUG_MASK << 16) | 0x00000103}, // .lp_level = 3, .bt_use_wifi_rf = 1, .debug_mask=0x8d08 //BIT1:ps_bit
    #ifdef CFG_WIFI_HIB
    {WIFI_SETTINGS_OFST(pwr_close_sysdelay),            0x085006d6}, //pwr_close_sysdelay = 1750, pwr_open_sysdelay = 1900 + 150
    #else
    {WIFI_SETTINGS_OFST(pwr_close_sysdelay),            0x0A2806d6}, //pwr_close_sysdelay = 1750, pwr_open_sysdelay = 1900 + 150 + 550
    #endif
    {WIFI_SETTINGS_OFST(thresh_param.beacon_linkloss_thd),  0x00003200 | CONFIG_WIFI_BCN_LINKLOSS_THD}, //beacon_linkloss_thd=10, .ps_tx_error_max=50
    {WIFI_SETTINGS_OFST(thresh_param.mm_keep_alive_period), CONFIG_WIFI_PS_KEEP_ALIVE_TIME_US}, //mm_keep_alive_period=150s
    {WIFI_SETTINGS_OFST(thresh_param.scan_active_duration), CONFIG_WIFI_ACTIVE_SCAN_TIME_US}, //scan_active_duration=30ms
    {WIFI_SETTINGS_OFST(thresh_param.scan_passive_duration),CONFIG_WIFI_PASSIVE_SCAN_TIME_US}, //scan_passive_duration=110ms
    {WIFI_SETTINGS_OFST(thresh_param.lp_wakeup_offset), (0x08050000 | CONFIG_WIFI_LP_WAKEUP_OFFSET_US)}, //lp_wakeup_offset = 900, .tx_he_tb_prog_time = 5,.tx_agg_finish_dur = 8,
    {WIFI_SETTINGS_OFST(thresh_param.deepsleep_notallowed_offset), 0x61a82710}, // .deepsleep_notallowed_offset = 10 * 1000[0x2710], .ps_activity_to_us = 25000[0x61A8]
    #if PLF_BAND5G
    // Attention, GPIOs used by 5g fem maybe conflict with audio I2SM.
    //{WIFI_SETTINGS_OFST(txgain_config.fix_txgain_en),   0xd0eaec03}, // .fix_txgain_en = 3, .fix_txgain_val = 0xec, .fix_txgain_val_5g = 0xea, .fix_1024qam_txgain = 0xd0
    {WIFI_SETTINGS_OFST(use_5g),                        0x10010001}, // .use_5g = 1, .clkgate_use_hwbcn = 0, .poweroff_use_hwbcn = 1, .fix_txgain_val_24g_11b=0x10
    #else
    //{WIFI_SETTINGS_OFST(txgain_config.fix_txgain_en),   0xd0eaec01}, // .fix_txgain_en = 1, .fix_txgain_val = 0xec, .fix_txgain_val_5g = 0xea, .fix_1024qam_txgain = 0xd0
    {WIFI_SETTINGS_OFST(use_5g),                        0x10010000}, // .use_5g = 0, .clkgate_use_hwbcn = 0, .poweroff_use_hwbcn = 1, .fix_txgain_val_24g_11b=0x10
    #endif
};

struct aic_patch_tag rom_patch_obj = {{NULL,},};

void wifi_patch_prepare(void)
{
    rom_patch_obj.wifi_setting.array = patch_tbl_wifisetting;
    rom_patch_obj.wifi_setting.count = sizeof(patch_tbl_wifisetting) / sizeof(uint32_t) / 2;
}

uint32_t wifi_debug_mask_get(void)
{
    const uint32_t cfg_base = FMACFW_CFG_BASE_ADDR;
    uint32_t wifisetting_cfg_addr = REG_PL_RD(cfg_base);
    uint32_t dbg_msk = REG_PL_RD(wifisetting_cfg_addr + WIFI_SETTINGS_OFST(lp_level)) >> 16;
    return dbg_msk;
}

void wifi_debug_mask_set(uint32_t dbg_msk)
{
    const uint32_t cfg_base = FMACFW_CFG_BASE_ADDR;
    uint32_t wifisetting_cfg_addr = REG_PL_RD(cfg_base);
    uint32_t cur_val = REG_PL_RD(wifisetting_cfg_addr + WIFI_SETTINGS_OFST(lp_level)) & 0x0000FFFFUL;
    REG_PL_WR(wifisetting_cfg_addr + WIFI_SETTINGS_OFST(lp_level), cur_val | (dbg_msk << 16));
}
