/**
 ****************************************************************************************
 *
 * @file fhost_config.c
 *
 * @brief Definition of configuration for Fully Hosted firmware.
 *
 * Copyright (C) RivieraWaves 2017-2019
 *
 ****************************************************************************************
 */

#include "fhost_config.h"
#include "mac.h"
#include "mac_frame.h"
#include "msg.h"
#include "fhost.h"
#include "ipc_shared.h"
#include "time_api.h"
#include "trng_api.h"
#include "flash_api_wifi.h"
/**
 ****************************************************************************************
 * @addtogroup FHOST_CONFIG
 * @{
 ****************************************************************************************
 */
/// define a channel
#define CHAN(_freq, _band, _flags, _pwr) {         \
        .freq = (_freq),                           \
        .band = (_band),                           \
        .flags = (_flags),                         \
        .tx_power = (_pwr),                        \
    }

/// define a channel in 2.4GHz band
#define CHAN_24(_freq, _flag, _pwr) CHAN(_freq, PHY_BAND_2G4, _flag, _pwr)
/// define a channel in 5GHz band
#define CHAN_5(_freq, _flag, _pwr) CHAN(_freq, PHY_BAND_5G, _flag, _pwr)

/** List of supported Channel */
struct me_chan_config_req fhost_chan = {
    #if PLF_HW_PXP
    .chan2G4_cnt = 1,
    .chan2G4[0] = CHAN_24(2462, 0, 20),
    #else  /* PLF_HW_PXP */
    .chan2G4_cnt = 14,
    .chan2G4[0] = CHAN_24(2412, 0, 20),
    #endif /* PLF_HW_PXP */
    .chan2G4[1] = CHAN_24(2417, 0, 20),
    .chan2G4[2] = CHAN_24(2422, 0, 20),
    .chan2G4[3] = CHAN_24(2427, 0, 20),
    .chan2G4[4] = CHAN_24(2432, 0, 20),
    .chan2G4[5] = CHAN_24(2437, 0, 20),
    .chan2G4[6] = CHAN_24(2442, 0, 20),
    .chan2G4[7] = CHAN_24(2447, 0, 20),
    .chan2G4[8] = CHAN_24(2452, 0, 20),
    .chan2G4[9] = CHAN_24(2457, 0, 20),
    .chan2G4[10] = CHAN_24(2462, 0, 20),
    .chan2G4[11] = CHAN_24(2467, 0, 20),
    .chan2G4[12] = CHAN_24(2472, 0, 20),
    .chan2G4[13] = CHAN_24(2484, 0, 20),

    #if PLF_BAND5G
    #if PLF_HW_PXP
    .chan5G_cnt = 1,
    .chan5G[0] = CHAN_5(5180, 0, 20),
    #else  /* PLF_HW_PXP */
    .chan5G_cnt = 25,
    .chan5G[0] = CHAN_5(5180, 0, 20),
    .chan5G[1] = CHAN_5(5200, 0, 20),
    .chan5G[2] = CHAN_5(5220, 0, 20),
    .chan5G[3] = CHAN_5(5240, 0, 20),
    #if PLF_WIFI_AUDIO
    .chan5G[4] = CHAN_5(5260, 0, 20), //52
    .chan5G[5] = CHAN_5(5280, 0, 20), //56
    .chan5G[6] = CHAN_5(5300, 0, 20), //60
    .chan5G[7] = CHAN_5(5320, 0, 20), //64
    .chan5G[8] = CHAN_5(5500, 0, 20), //100
    .chan5G[9] = CHAN_5(5520, 0, 20), //104
    .chan5G[10] = CHAN_5(5540, 0, 20),//108
    .chan5G[11] = CHAN_5(5560, 0, 20),//112
    .chan5G[12] = CHAN_5(5580, 0, 20),//116
    .chan5G[13] = CHAN_5(5600, 0, 20),//120
    .chan5G[14] = CHAN_5(5620, 0, 20),//124
    .chan5G[15] = CHAN_5(5640, 0, 20),//128
    .chan5G[16] = CHAN_5(5660, 0, 20),//132
    .chan5G[17] = CHAN_5(5680, 0, 20),//136
    .chan5G[18] = CHAN_5(5700, 0, 20),//140
    .chan5G[19] = CHAN_5(5720, 0, 20),//144
    #else
    .chan5G[4] = CHAN_5(5260, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[5] = CHAN_5(5280, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[6] = CHAN_5(5300, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[7] = CHAN_5(5320, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[8] = CHAN_5(5500, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[9] = CHAN_5(5520, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[10] = CHAN_5(5540, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[11] = CHAN_5(5560, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[12] = CHAN_5(5580, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[13] = CHAN_5(5600, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[14] = CHAN_5(5620, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[15] = CHAN_5(5640, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[16] = CHAN_5(5660, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[17] = CHAN_5(5680, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[18] = CHAN_5(5700, CHAN_NO_IR|CHAN_RADAR, 20),
    .chan5G[19] = CHAN_5(5720, CHAN_NO_IR|CHAN_RADAR, 20),
    #endif
    .chan5G[20] = CHAN_5(5745, 0, 20),
    .chan5G[21] = CHAN_5(5765, 0, 20),
    .chan5G[22] = CHAN_5(5785, 0, 20),
    .chan5G[23] = CHAN_5(5805, 0, 20),
    .chan5G[24] = CHAN_5(5825, 0, 20),
    #endif /* PLF_HW_PXP */
    #else
    .chan5G_cnt = 0,
    #endif
};

#undef CHAN_5
#undef CHAN_24
#undef CHAN

static const wifi_regdom_t regdom_00 = {
    .cc = "00",
    #if PLF_BAND5G
    .reg_rules_cnt = 5,
    #else
    .reg_rules_cnt = 1,
    #endif
    .reg_rules_arr = {
        {  1, 14, 20, 0},
        #if PLF_BAND5G
        { 36,  4, 20, 0},
        { 52,  4, 20, CHAN_NO_IR|CHAN_RADAR},
        {100, 12, 20, CHAN_NO_IR|CHAN_RADAR},
        {149,  5, 20, 0},
        #endif
    },
};

static const wifi_regdom_t regdom_CA = {
    .cc = "CA",
    #if PLF_BAND5G
    .reg_rules_cnt = 5,
    #else
    .reg_rules_cnt = 1,
    #endif
    .reg_rules_arr = {
        {  1, 11, 30, 0},
        #if PLF_BAND5G
        { 36,  4, 17, 0},
        { 52,  4, 23, CHAN_NO_IR|CHAN_RADAR},
        {100, 12, 24, CHAN_NO_IR|CHAN_RADAR},
        {149,  5, 30, 0},
        #endif
    },
};

static const wifi_regdom_t regdom_CN = {
    .cc = "CN",
    #if PLF_BAND5G
    .reg_rules_cnt = 4,
    #else
    .reg_rules_cnt = 1,
    #endif
    .reg_rules_arr = {
        {  1, 13, 20, 0},
        #if PLF_BAND5G
        { 36,  4, 23, 0},
        { 52,  4, 23, CHAN_NO_IR|CHAN_RADAR},
        {149,  5, 30, 0},
        #endif
    },
};

static const wifi_regdom_t regdom_US = {
    .cc = "US",
    #if PLF_BAND5G
    .reg_rules_cnt = 5,
    #else
    .reg_rules_cnt = 1,
    #endif
    .reg_rules_arr = {
        {  1, 11, 30, 0},
        #if PLF_BAND5G
        { 36,  4, 17, 0},
        { 52,  4, 23, CHAN_NO_IR|CHAN_RADAR},
        {100, 11, 24, CHAN_NO_IR|CHAN_RADAR},
        {149,  5, 30, 0},
        #endif
    },
};

const wifi_regdom_t *wifi_regdb[] = {
    &regdom_00,
    &regdom_CA,
    &regdom_CN,
    &regdom_US,
};

const int wifi_regdb_size = sizeof(wifi_regdb) / sizeof(wifi_regdom_t *);

fhost_user_cfg_t fhost_usr_cfg = {
    .ipc_irq_prio = __NVIC_PRIO_LOWEST,
    .ipc_e2a_msg_buf_num = IPC_MSGE2A_BUF_CNT,
    .parse_rx_datarate_en = 0,
    .rf_switch_en = CONFIG_WIFI_RF_SWITCH_ENABLE,
    #if defined(CFG_WIFI_RAM_VER)
    .wifi_ram_ver_on = 1,
    #else
    .wifi_ram_ver_on = 0,
    #endif
    #if (PLF_AIC8800)
    .fast_ram_on     = 1,
    #endif
    .retransmit_via_app = 0,
};

/*******************************************************************************
 * FW configuration:
 ******************************************************************************/
/// MAC Address
static uint8_t fhost_mac_addr[6] = CONFIG_DEFAULT_MAC_ADDRESS;
static uint8_t blink_magic_num = 0x00;
/// PHY configuration (This is only valid for KARST radio)
static const uint32_t phy_cfg[] = {0x01000000, 0x01000000, 0x01000000, 0x01000000,
                             0x01000000, 0x01000000, 0x01000000, 0x01000000,
                             0x0};

static const struct {
    bool ps_on;
    #if NX_UAPSD
    uint32_t uapsd_timeout;
    #endif
} ps_cfg = {
    .ps_on = true,
    #if NX_UAPSD
    .uapsd_timeout = 300,
    #endif
};

#if PLF_WIFI_AUDIO
const uint16_t tx_lft_ms = 40;
#else /* PLF_WIFI_AUDIO */
const uint16_t tx_lft_ms = 1000;
#endif /* PLF_WIFI_AUDIO */

bool ht_support  = 1;
#if defined(CFG_BWMODE)
bool ht_40mhz    = 0;
#else
bool ht_40mhz    = 1;
#endif
bool vht_support = 1;
uint8_t vht_mcs  = 2;
#if defined(CFG_BWMODE)
bool he_support  = 0;
#else
bool he_support  = 1;
#endif
uint8_t he_mcs   = 2;
const uint8_t nss      = 1;
bool stbc        = 1;
bool ldpc        = 1;
const bool su_bfmee    = 1;
const bool mu_bfmee    = 0;
uint16_t lp_clk_accurary   = 0;

/// Wifi configuration
const struct fhost_config_item fw_config[] = {
    {FHOST_CFG_MAC_ADDR,    6, (void *)fhost_mac_addr},
    {FHOST_CFG_PHY_KARST,  33, (void *)phy_cfg},
    {FHOST_CFG_PS,          4, (void *)&ps_cfg.ps_on},
    #if NX_UAPSD
    {FHOST_CFG_UAPSD_TIMEOUT,   4, (void *)&ps_cfg.uapsd_timeout},
    #endif
    {FHOST_CFG_TX_LFT,  2, (void *)&tx_lft_ms},
    {FHOST_CFG_NSS,     1, (void *)&nss},
    {FHOST_CFG_LDPC,    1, (void *)&ldpc},
    {FHOST_CFG_STBC,    1, (void *)&stbc},
    {FHOST_CFG_HT,      1, (void *)&ht_support},
    {FHOST_CFG_40MHZ,   1, (void *)&ht_40mhz},
    {FHOST_CFG_VHT,     1, (void *)&vht_support},
    {FHOST_CFG_VHT_MCS, 1, (void *)&vht_mcs},
    {FHOST_CFG_HE,      1, (void *)&he_support},
    {FHOST_CFG_HE_MCS,  1, (void *)&he_mcs},
    {FHOST_CFG_BFMEE,   1, (void *)&su_bfmee},
    {FHOST_CFG_MURX,    1, (void *)&mu_bfmee},
    {FHOST_CFG_LP_CLK_ACCURACY,    2, (void *)&lp_clk_accurary},

    {FHOST_CFG_END, 0, NULL}
};
/*
 * fhost_config_get_next_item: Must return configuration item one by one.
 * In this console confguration is saved in the global varaible fw_config
 */
void fhost_config_get_next_item(struct fhost_config_item *item)
{
    static int index;

    // First call, initialize index
    if (item->data == NULL)
        index = 0;

    // Check that we don't read outside of console_config table
    if (index > (sizeof(fw_config) / sizeof(struct fhost_config_item)))
    {
        item->id = FHOST_CFG_END;
    }

    // Copy one configuration parameter
    *item = fw_config[index];

    // Update index for next call
    index++;
}
static const int mcs_map_to_rate[4][3] = {
    [PHY_CHNL_BW_20][MAC_VHT_MCS_MAP_0_7] = 65,
    [PHY_CHNL_BW_20][MAC_VHT_MCS_MAP_0_8] = 78,
    [PHY_CHNL_BW_20][MAC_VHT_MCS_MAP_0_9] = 78,
    [PHY_CHNL_BW_40][MAC_VHT_MCS_MAP_0_7] = 135,
    [PHY_CHNL_BW_40][MAC_VHT_MCS_MAP_0_8] = 162,
    [PHY_CHNL_BW_40][MAC_VHT_MCS_MAP_0_9] = 180,
    [PHY_CHNL_BW_80][MAC_VHT_MCS_MAP_0_7] = 292,
    [PHY_CHNL_BW_80][MAC_VHT_MCS_MAP_0_8] = 351,
    [PHY_CHNL_BW_80][MAC_VHT_MCS_MAP_0_9] = 390,
    [PHY_CHNL_BW_160][MAC_VHT_MCS_MAP_0_7] = 585,
    [PHY_CHNL_BW_160][MAC_VHT_MCS_MAP_0_8] = 702,
    [PHY_CHNL_BW_160][MAC_VHT_MCS_MAP_0_9] = 780,
};

#define MAX_VHT_RATE(map, nss, bw) (mcs_map_to_rate[bw][map] * (nss))

void fhost_config_prepare(struct me_config_req *me_config, struct mm_start_req *start,
                          struct mac_addr *base_mac_addr, bool init)
{
    struct fhost_config_item item;
    uint32_t phy_ver1, /*phy_ver2, */sec = 0, usec = 0;
    uint8_t nss, vht_mcs;
    bool sgi, sgi80, stbc, ht40, ldpc_rx, bfmee, bfmer, mu_rx, mu_tx, vht80;
    #if NX_HE
    uint8_t he_mcs = 0;
    #endif

    memset(me_config, 0, sizeof(*me_config));
    memset(start, 0, sizeof(*start));
    item.data = NULL;

    /* Default value */
    stbc = true;
    sgi = true;
    ht40 = true;
    vht80 = false;
    sgi80 = false;
    vht_mcs = 0;
    me_config->ht_supp = true;
    me_config->vht_supp = false;
    me_config->he_supp = true;
    nss = 1;
    ldpc_rx = true;
    bfmee = true;
    bfmer = false;
    mu_rx = true;
    mu_tx = false;
    phy_ver1 = 0x00220000;

    fhost_config_get_next_item(&item);
    while (item.id != FHOST_CFG_END)
    {
        switch (item.id)
        {
            case FHOST_CFG_MAC_ADDR:
                {
                    fhost_mac_address_acquire();
                    memcpy(base_mac_addr, item.data, sizeof(*base_mac_addr));
                }
                break;
            case FHOST_CFG_PS:
                me_config->ps_on = *(bool *)item.data;
                break;
            case FHOST_CFG_DPSM:
                me_config->dpsm = *(bool *)item.data;
                break;
            case FHOST_CFG_SGI:
                sgi = *(bool *)item.data;
                break;
            case FHOST_CFG_SGI80:
                if (vht80)
                    sgi80 = *(bool *)item.data;
                break;
            case FHOST_CFG_NSS:
            {
                uint8_t val = *(uint8_t *)item.data;
                if (val && val < nss)
                    nss = val;
            } break;
            case FHOST_CFG_TX_LFT:
                me_config->tx_lft = *(uint16_t *)item.data;
                break;
            case FHOST_CFG_UAPSD_TIMEOUT:
                start->uapsd_timeout = *(uint32_t *)item.data;
                break;
            case FHOST_CFG_UAPSD_QUEUES:
                if (init)
                    fhost_vif_set_uapsd_queues(-1, *(uint8_t *)item.data);
                break;
            case FHOST_CFG_LP_CLK_ACCURACY:
                start->lp_clk_accuracy = *(uint16_t *)item.data;
                break;
            case FHOST_CFG_HT:
                me_config->ht_supp = *(bool *)item.data;
                break;
            case FHOST_CFG_40MHZ:
                if (ht40)
                    ht40 = *(bool *)item.data;
                break;
            case FHOST_CFG_80MHZ:
                if (vht80)
                    vht80 = *(bool *)item.data;
                break;
            case FHOST_CFG_VHT:
                #if NX_VHT
                //if (phy_vht_supported() && (phy_get_bw() >= 2))
                    me_config->vht_supp = *(bool *)item.data;
                //else
                //    me_config->vht_supp = false;
                #endif
                break;
            case FHOST_CFG_VHT_MCS:
                vht_mcs = *(uint8_t *)item.data;
                if (vht_mcs > 2)
                    vht_mcs = 0;
                break;
            #if NX_HE
            case FHOST_CFG_HE:
                //if (hal_machw_he_support())
                    me_config->he_supp = *(bool *)item.data;
                //else
                //    me_config->he_supp = false;
                break;
            case FHOST_CFG_HE_MCS:
                he_mcs = *(uint8_t *)item.data;
                if (he_mcs > 2)
                    he_mcs = 0;
                break;
            #endif
            case FHOST_CFG_LDPC:
                //if (!*(bool *)item.data)
                    ldpc_rx = *(bool *)item.data;
                break;
            case FHOST_CFG_STBC:
                stbc = *(bool *)item.data;
                break;
            case FHOST_CFG_BFMEE:
                if (!*(bool *)item.data)
                    bfmee = false;
                break;
            case FHOST_CFG_BFMER:
                if (!*(bool *)item.data)
                    bfmer = false;
                break;
            case FHOST_CFG_MURX:
                if (!*(bool *)item.data)
                    mu_rx = false;
                break;
            case FHOST_CFG_MUTX:
                if (!*(bool *)item.data)
                    mu_tx = false;
                break;
            case FHOST_CFG_PHY_TRD:
                if (((phy_ver1 & 0x030000) >> 16) == 0) {
                    memcpy(&start->phy_cfg.parameters, item.data, item.len);
                }
                break;
            case FHOST_CFG_PHY_KARST:
                if (((phy_ver1 & 0x030000) >> 16) == 2)
                {
                    memcpy(&start->phy_cfg.parameters, item.data, item.len);
                }
                break;
            case FHOST_CFG_ANT_DIV:
                me_config->ant_div_on = *(bool *)item.data;
                break;
            case FHOST_CFG_EPOCH_SEC:
                sec = *(uint32_t *)item.data;
                break;
            case FHOST_CFG_EPOCH_USEC:
                usec = *(uint32_t *)item.data;
                break;
            default :
                break;
        }
        fhost_config_get_next_item(&item);
    }

    if (init)
    {
        if (sec && usec)
        {
            aic_time_init(sec, usec);
        }

        aic_time_get(SINCE_EPOCH, &sec, &usec);
        co_random_init((sec & 0xffff) * (usec & 0x1ffff));
    }

    if (!ht40)
    {
        vht80 = false;
        sgi80 = false;
    }

    if (me_config->ht_supp)
    {
        int max_rate;
        me_config->ht_cap.ht_capa_info = 0;
        if (ldpc_rx)
            me_config->ht_cap.ht_capa_info |= MAC_HTCAPA_LDPC;
        if (ht40)
            me_config->ht_cap.ht_capa_info |= MAC_HTCAPA_40_MHZ;
        #if !NX_HE
        me_config->ht_cap.ht_capa_info |= MAC_HTCAPA_GREEN_FIELD;
        #endif
        if (sgi)
        {
            me_config->ht_cap.ht_capa_info |= MAC_HTCAPA_SHORTGI_20;
            if (ht40)
                me_config->ht_cap.ht_capa_info |= MAC_HTCAPA_SHORTGI_40;
        }
        if (nss > 1)
            me_config->ht_cap.ht_capa_info |= MAC_HTCAPA_TX_STBC;
        me_config->ht_cap.ht_capa_info |= (1 << MAC_HTCAPA_RX_STBC_OFT);

        me_config->ht_cap.a_mpdu_param = ((3 << MAC_AMPDU_LEN_EXP_OFT) |
                                         (7 << MAC_AMPDU_MIN_SPACING_OFT));
        me_config->ht_cap.mcs_rate[0] = 0xff; /* RX MCS0-7*/
        if (nss > 1)
            me_config->ht_cap.mcs_rate[1] = 0xff; /* RX MCS8-15 */
        if (ht40)
            me_config->ht_cap.mcs_rate[4] = 1; /* RX MCS32 */

        if (sgi && ht40)
            max_rate = 150;
        else if (sgi)
            max_rate = 72;
        else if (ht40)
            max_rate = 135;
        else
            max_rate = 65;

        me_config->ht_cap.mcs_rate[10] = max_rate * nss; /* highest supported rate */
        me_config->ht_cap.mcs_rate[12] = 1;              /* TX mcs same as RX mcs */

        me_config->ht_cap.ht_extended_capa = 0;
        me_config->ht_cap.tx_beamforming_capa = 0;
        me_config->ht_cap.asel_capa = 0;
    }
    else
    {
        ht40 = false;
    }

    if (vht80)
        me_config->phy_bw_max = PHY_CHNL_BW_80;
    else if (ht40)
        me_config->phy_bw_max = PHY_CHNL_BW_40;
    else
        me_config->phy_bw_max = PHY_CHNL_BW_20;

    if (me_config->vht_supp)
    {
        int i;
        me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_MAX_MPDU_LENGTH_3895;
        me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_SUPP_CHAN_WIDTH_80;

        if (ldpc_rx)
            me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_RXLDPC;
        if (sgi80)
            me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_SHORT_GI_80;
        if (nss > 1)
            me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_TXSTBC;
        if (stbc)
            me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_RXSTBC_1;
        if (bfmer)
            me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_SU_BEAMFORMER_CAPABLE;
        if (bfmee)
            me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_SU_BEAMFORMEE_CAPABLE;
        me_config->vht_cap.vht_capa_info |= (nss - 1 ) << MAC_VHTCAPA_SOUNDING_DIMENSIONS_OFT;
        if (mu_tx)
            me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_MU_BEAMFORMER_CAPABLE;
        if (mu_rx)
            me_config->vht_cap.vht_capa_info |= MAC_VHTCAPA_MU_BEAMFORMEE_CAPABLE;

        me_config->vht_cap.vht_capa_info |= (7 << MAC_VHTCAPA_MAX_A_MPDU_LENGTH_EXP_OFT);
        me_config->vht_cap.vht_capa_info |= (3 << MAC_VHTCAPA_BEAMFORMEE_STS_OFT);

        me_config->vht_cap.rx_mcs_map = vht_mcs; /* RX MCS for 1 NSS */
        for (i = 1; i < nss; i++) /* RX MCS for 2 NSS (limit to mcs7) */
            me_config->vht_cap.rx_mcs_map |= MAC_VHT_MCS_MAP_0_7 << (2 * i);
        for (; i < 8; i++) /* RX MCS for non-supported NSS */
            me_config->vht_cap.rx_mcs_map |= MAC_VHT_MCS_MAP_NONE << (2 * i);
        me_config->vht_cap.rx_highest = MAX_VHT_RATE(MAC_VHT_MCS_MAP_0_7, nss, me_config->phy_bw_max);//200 * nss;

        me_config->vht_cap.tx_mcs_map = vht_mcs; /* TX MCS for 1 NSS */
        if (vht_mcs > MAC_VHT_MCS_MAP_0_9)
            vht_mcs = MAC_VHT_MCS_MAP_0_9;
        for (i = 1; i < nss; i++) /* TX MCS for 2 NSS (limit to mcs8) */
            me_config->vht_cap.tx_mcs_map |= vht_mcs << (2 * i);
        for (; i < 8; i++) /* TX MCS for non-supported NSS */
            me_config->vht_cap.tx_mcs_map |= MAC_VHT_MCS_MAP_NONE << (2 * i);
        me_config->vht_cap.tx_highest = MAX_VHT_RATE(MAC_VHT_MCS_MAP_0_9, nss, me_config->phy_bw_max);//200 * nss;
    }
    else
    {
        vht80 = false;
    }

    #if NX_HE
    if (me_config->he_supp)
    {
        int i;
        struct mac_hecapability *he_cap = &me_config->he_cap;

        memset(he_cap, 0, sizeof(*he_cap));

        he_cap->ppe_thres[0] = 0x08;
        he_cap->ppe_thres[1] = 0x1C;
        he_cap->ppe_thres[2] = 0x07;

        HE_MAC_CAPA_BIT_SET(he_cap, ALL_ACK);
        HE_MAC_CAPA_BIT_SET(he_cap, NDP_FB_REP);
        HE_MAC_CAPA_BIT_SET(he_cap, 32BIT_BA_BITMAP);
        HE_MAC_CAPA_BIT_SET(he_cap, MU_CASCADING);
        HE_MAC_CAPA_BIT_SET(he_cap, ACK_EN);
        HE_MAC_CAPA_BIT_SET(he_cap, OM_CONTROL);
        HE_MAC_CAPA_BIT_SET(he_cap, OFDMA_RA);
        HE_MAC_CAPA_BIT_SET(he_cap, HTC_HE);
        HE_MAC_CAPA_BIT_SET(he_cap, TSR);
        HE_MAC_CAPA_BIT_SET(he_cap, BSR); // TBD
        HE_MAC_CAPA_BIT_SET(he_cap, BSRP_BQRP_A_MPDU_AGG);

        HE_PHY_CAPA_BIT_SET(he_cap, HE_SU_PPDU_1x_LTF_AND_GI_0_8US);
        HE_PHY_CAPA_BIT_SET(he_cap, NDP_4x_LTF_AND_3_2US);
        HE_PHY_CAPA_BIT_SET(he_cap, PPE_THRESHOLD_PRESENT);

        HE_PHY_CAPA_BIT_SET(he_cap, NG16_SU_FEEDBACK);
        //HE_PHY_CAPA_BIT_SET(he_cap, NG16_MU_FEEDBACK);
        HE_PHY_CAPA_BIT_SET(he_cap, CODEBOOK_SIZE_42_SU);
        //HE_PHY_CAPA_BIT_SET(he_cap, CODEBOOK_SIZE_75_MU);
        HE_PHY_CAPA_BIT_SET(he_cap, TRIG_SU_BEAMFORMER_FB);
        //HE_PHY_CAPA_BIT_SET(he_cap, TRIG_MU_BEAMFORMER_FB);
        HE_PHY_CAPA_BIT_SET(he_cap, TRIG_CQI_FB);

        HE_PHY_CAPA_BIT_SET(he_cap, FULL_BW_UL_MU_MIMO);

        if (bfmee)
        {
            HE_PHY_CAPA_BIT_SET(he_cap, SU_BEAMFORMEE);
            //HE_PHY_CAPA_VAL_SET(he_cap, BFMEE_MAX_STS_UNDER_80MHZ, 4);
        }

        if (ht40)
        {
            HE_PHY_CAPA_VAL_SET(he_cap, CHAN_WIDTH_SET, 40MHZ_IN_2G);
            he_cap->ppe_thres[0] |= 0x10;
        }
        if (ldpc_rx)
            HE_PHY_CAPA_BIT_SET(he_cap, LDPC_CODING_IN_PAYLOAD);
        else
            // If no LDPC is supported, we have to limit to MCS0_9, as LDPC is mandatory
            // for MCS 10 and 11
            he_mcs = co_min(he_mcs, MAC_HE_MCS_MAP_0_9);

        if (stbc) {
            //HE_PHY_CAPA_BIT_SET(he_cap, STBC_TX_UNDER_80MHZ); // not support
            HE_PHY_CAPA_BIT_SET(he_cap, STBC_RX_UNDER_80MHZ);
        }

        memset(&he_cap->mcs_supp, 0, sizeof(he_cap->mcs_supp));
        #if PLF_AIC8800M40
        he_cap->mcs_supp.rx_mcs_80 = co_min(he_mcs, MAC_HE_MCS_MAP_0_11);
        #else
        he_cap->mcs_supp.rx_mcs_80 = co_min(he_mcs, MAC_HE_MCS_MAP_0_9);
        #endif
        for (i = 1; i < nss; i++) {
            uint16_t unsup_for_ss = MAC_HE_MCS_MAP_NONE << (i*2);
            he_cap->mcs_supp.rx_mcs_80 |= MAC_HE_MCS_MAP_0_7 << (i*2);
            he_cap->mcs_supp.rx_mcs_160 |= unsup_for_ss;
            he_cap->mcs_supp.rx_mcs_80p80 |= unsup_for_ss;
        }
        for (; i < 8; i++) {
            uint16_t unsup_for_ss = MAC_HE_MCS_MAP_NONE << (i*2);
            he_cap->mcs_supp.rx_mcs_80 |= unsup_for_ss;
            he_cap->mcs_supp.rx_mcs_160 |= unsup_for_ss;
            he_cap->mcs_supp.rx_mcs_80p80 |= unsup_for_ss;
        }
        he_cap->mcs_supp.tx_mcs_80 = he_mcs;
        for (i = 1; i < nss; i++) {
            uint16_t unsup_for_ss = MAC_HE_MCS_MAP_NONE << (i*2);
            he_cap->mcs_supp.tx_mcs_80 |= MAC_HE_MCS_MAP_0_7 << (i*2);
            he_cap->mcs_supp.tx_mcs_160 |= unsup_for_ss;
            he_cap->mcs_supp.tx_mcs_80p80 |= unsup_for_ss;
        }
        for (; i < 8; i++) {
            uint16_t unsup_for_ss = MAC_HE_MCS_MAP_NONE << (i*2);
            he_cap->mcs_supp.tx_mcs_80 |= unsup_for_ss;
            he_cap->mcs_supp.tx_mcs_160 |= unsup_for_ss;
            he_cap->mcs_supp.tx_mcs_80p80 |= unsup_for_ss;
        }
    }
    #endif

    // update chan info from country code
    fhost_chan_update(CONFIG_WIFI_COUNTRY_CODE);
}

/**
 ****************************************************************************************
 * @brief Return the channel associated to a given frequency
 *
 * @param[in] freq Channel frequency
 *
 * @return Channel definition whose primary frequency is the requested one and NULL
 * no such channel doesn't exist.
 ****************************************************************************************
 */
struct mac_chan_def *fhost_chan_get(int freq)
{
    int i, nb_chan;
    struct mac_chan_def *chans, *chan = NULL;

    if (freq < PHY_FREQ_5G)
    {
        chans = fhost_chan.chan2G4;
        nb_chan = fhost_chan.chan2G4_cnt;
    }
    else
    {
        chans = fhost_chan.chan5G;
        nb_chan = fhost_chan.chan5G_cnt;
    }

    for (i = 0; i < nb_chan; i++, chans++)
    {
        if (freq == chans->freq)
        {
            chan = chans;
            break;
        }
    }

    return chan;
}

int fhost_chan_update(const char * country_code)
{
    int ret = 0, idx;
    const wifi_regdom_t *usr_regdom = NULL;
    for (idx = 0; idx < wifi_regdb_size; idx++) {
        const wifi_regdom_t *regdom = wifi_regdb[idx];
        if ((regdom->cc[0] == country_code[0]) &&
            (regdom->cc[1] == country_code[1])) {
            usr_regdom = regdom;
            break;
        }
    }
    if (usr_regdom) {
        int ch_cnt[PHY_BAND_MAX] = {0,};
        for (idx = 0; idx < usr_regdom->reg_rules_cnt; idx++) {
            const wifi_regrule_t *regrule = &usr_regdom->reg_rules_arr[idx];
            int band, ch_idx, ch_incr, ch_num;
            uint16_t freq;
            struct mac_chan_def *p_ch_def;
            if (regrule->first_chan <= 14) {
                band = PHY_BAND_2G4;
                ch_incr = 1;
                p_ch_def = &fhost_chan.chan2G4[ch_cnt[PHY_BAND_2G4]];
            } else {
                band = PHY_BAND_5G;
                ch_incr = 4;
                p_ch_def = &fhost_chan.chan5G[ch_cnt[PHY_BAND_5G]];
            }
            ch_num = regrule->first_chan;
            for (ch_idx = 0; ch_idx < regrule->chan_cnt; ch_idx++) {
                freq = phy_channel_to_freq(band, ch_num);
                if (freq) {
                    p_ch_def->freq = freq;
                    p_ch_def->band = band;
                    p_ch_def->flags = regrule->flags;
                    p_ch_def->tx_power = regrule->power;
                    p_ch_def++;
                    ch_cnt[band]++;
                } else {
                    ret++; // invalid freq
                }
                ch_num += ch_incr;
            }
        }
        fhost_chan.chan2G4_cnt = ch_cnt[PHY_BAND_2G4];
        fhost_chan.chan5G_cnt  = ch_cnt[PHY_BAND_5G];
    } else {
        ret = -1; // invalid country code
    }
    return ret;
}

#if (PLF_HW_PXP == 1)
extern uint8_t is_ap;
#endif /* PLF_HW_PXP */

void set_mac_address(uint8_t *addr)
{
    if (!addr) {
        unsigned int ap_config;
        int ret;
        ret = flash_wifi_ap_config_read(&ap_config);
        if (ret) {
            ap_config = 0;
        }
        if (ap_config & WIFI_AP_CONFIG_FORCED_AP_MODE_EN) {
            ret = flash_wifi_ap_macaddr_read(fhost_mac_addr);
        } else {
            ret = flash_wifi_sta_macaddr_read(fhost_mac_addr);
        }
        if (ret) {
            unsigned int rand_wd = trng_get_word();
            fhost_mac_addr[3] = (uint8_t)(rand_wd >> 0);
            fhost_mac_addr[4] = (uint8_t)(rand_wd >> 8);
            fhost_mac_addr[5] = (uint8_t)(rand_wd >> 16);
            flash_wifi_sta_macaddr_write(fhost_mac_addr);
        }
    } else {
        addr[0] &= ~0x01U; // could not be multicast address
        MAC_ADDR_CPY(fhost_mac_addr, addr);
    }

}

void set_blink_magic(uint8_t *addr)
{
	flash_wifi_blink_magic_write(addr);
}

uint8_t* get_mac_address(void)
{
    unsigned int ap_config;
    int ret;
    ret = flash_wifi_ap_config_read(&ap_config);
    if (ret) {
        ap_config = 0;
    }
    if (ap_config & WIFI_AP_CONFIG_FORCED_AP_MODE_EN) {
        ret = flash_wifi_ap_macaddr_read(fhost_mac_addr);
    } else {
        ret = flash_wifi_sta_macaddr_read(fhost_mac_addr);
    }
    return (uint8_t*)fhost_mac_addr;
}

void fhost_mac_address_acquire(void)
{
    int ret;
    unsigned int ap_config;
    ret = flash_wifi_ap_config_read(&ap_config);
    if (ret != INFO_READ_DONE) {
        ap_config = 0;
    }
    if (ap_config & WIFI_AP_CONFIG_FORCED_AP_MODE_EN) {
        ret = flash_wifi_ap_macaddr_read(fhost_mac_addr);
    } else {
        ret = flash_wifi_sta_macaddr_read(fhost_mac_addr);
    }
    if (ret != INFO_READ_DONE) {
        uint8_t default_mac[6] = CONFIG_DEFAULT_MAC_ADDRESS;
        if (MAC_ADDR_CMP(fhost_mac_addr, default_mac)) {
            // no mac addr stored in flash, use random addr
            unsigned int rand_wd = trng_get_word();
            fhost_mac_addr[4] = (uint8_t)(rand_wd >> 0);
            fhost_mac_addr[5] = (uint8_t)(rand_wd >> 8);
        }
    }
}

uint8_t get_blink_magic(void)
{
	flash_wifi_blink_magic_read(&blink_magic_num);
    return blink_magic_num;
}

const char * fhost_config_name_get(enum fhost_config_id id)
{
    switch (id) {
    case FHOST_CFG_MAC_ADDR:
        return "MAC_ADDR";
    case FHOST_CFG_HT:
        return "HT";
    case FHOST_CFG_40MHZ:
        return "HT40";
    case FHOST_CFG_VHT:
        return "VHT";
    case FHOST_CFG_VHT_MCS:
        return "VHT_MCS";
    case FHOST_CFG_HE:
        return "HE";
    case FHOST_CFG_HE_MCS:
        return "HE_MCS";
    case FHOST_CFG_LDPC:
        return "LDPC";
    case FHOST_CFG_STBC:
        return "STBC";
    default:
        return "NOT_SUPPORT_YET";
    }
}

uint32_t fhost_config_value_get(enum fhost_config_id id)
{
    switch (id) {
    case FHOST_CFG_MAC_ADDR:
        return (uint32_t)fhost_mac_addr; // pointer in RAM
    case FHOST_CFG_HT:
        return (uint32_t)ht_support;
    case FHOST_CFG_40MHZ:
        return (uint32_t)ht_40mhz;
    case FHOST_CFG_VHT:
        return (uint32_t)vht_support;
    case FHOST_CFG_VHT_MCS:
        return (uint32_t)vht_mcs;
    case FHOST_CFG_HE:
        return (uint32_t)he_support;
    case FHOST_CFG_HE_MCS:
        return (uint32_t)he_mcs;
    case FHOST_CFG_LDPC:
        return (uint32_t)ldpc;
    case FHOST_CFG_STBC:
        return (uint32_t)stbc;
    default:
        return 0;
    }
}

void fhost_config_value_set(enum fhost_config_id id, uint32_t val)
{
    switch (id) {
    case FHOST_CFG_MAC_ADDR:
        // do nothing
        break;
    case FHOST_CFG_HT:
        ht_support = val;
        break;
    case FHOST_CFG_40MHZ:
        ht_40mhz = val;
        break;
    case FHOST_CFG_VHT:
        vht_support = val;
        break;
    case FHOST_CFG_VHT_MCS:
        vht_mcs = val;
        break;
    case FHOST_CFG_HE:
        he_support = val;
        break;
    case FHOST_CFG_HE_MCS:
        he_mcs = val;
        break;
    case FHOST_CFG_LDPC:
        ldpc = val;
        break;
    case FHOST_CFG_STBC:
        stbc = val;
        break;
    default:
        break;
    }
}

#if (PLF_AIC8800)
void fhost_config_txpwr_idx_get(txpwr_idx_fine_conf_t *conf)
{
    #if (CONFIG_WIFI_TXPWR_IDX_ENABLE == 2)
    const txpwr_idx_fine_conf_t user_conf_fine = {
        .enabled             = 2,
        .pwridx_11b_11ag_2g4 = CONFIG_WIFI_TXPWR_IDX_11B_11AG_2G4,
        .pwridx_11n_11ac_2g4 = CONFIG_WIFI_TXPWR_IDX_11N_11AC_2G4,
        .pwridx_11ax_2g4     = CONFIG_WIFI_TXPWR_IDX_11AX_2G4,
        .pwridx_11ag_5g      = CONFIG_WIFI_TXPWR_IDX_11AG_5G,
        .pwridx_11n_11ac_5g  = CONFIG_WIFI_TXPWR_IDX_11N_11AC_5G,
        .pwridx_11ax_5g      = CONFIG_WIFI_TXPWR_IDX_11AX_5G,
    };
    #elif (CONFIG_WIFI_TXPWR_IDX_ENABLE == 1)
    const txpwr_idx_conf_8800_t user_conf = {
        .enabled         = 1,
        .dsss            = CONFIG_WIFI_TXPWR_IDX_DSSS,
        .ofdmlowrate_2g4 = CONFIG_WIFI_TXPWR_IDX_OFDM_LOWRATE_2G4,
        .ofdm64qam_2g4   = CONFIG_WIFI_TXPWR_IDX_OFDM_64QAM_2G4,
        .ofdm256qam_2g4  = CONFIG_WIFI_TXPWR_IDX_OFDM_256QAM_2G4,
        .ofdm1024qam_2g4 = CONFIG_WIFI_TXPWR_IDX_OFDM_1024QAM_2G4,
        .ofdmlowrate_5g  = CONFIG_WIFI_TXPWR_IDX_OFDM_LOWRATE_5G,
        .ofdm64qam_5g    = CONFIG_WIFI_TXPWR_IDX_OFDM_64QAM_5G,
        .ofdm256qam_5g   = CONFIG_WIFI_TXPWR_IDX_OFDM_256QAM_5G,
        .ofdm1024qam_5g  = CONFIG_WIFI_TXPWR_IDX_OFDM_1024QAM_5G,
    };
    #endif
    if (!conf) {
        return;
    }
    #if (CONFIG_WIFI_TXPWR_IDX_ENABLE == 2)
    *conf = user_conf_fine;
    #elif (CONFIG_WIFI_TXPWR_IDX_ENABLE == 1)
    *((txpwr_idx_conf_8800_t *)conf) = user_conf;
    #endif
}
#endif

#if (PLF_AIC8800MC || PLF_AIC8800M40)
void fhost_config_txpwr_lvl_get(txpwr_lvl_conf_t *conf)
{
    const txpwr_lvl_conf_t user_conf = {
        .enabled             = CONFIG_WIFI_TXPWR_LVL_ENABLE,
        .pwrlvl_11b_11ag_2g4 = CONFIG_WIFI_TXPWR_LVL_11B_11AG_2G4,
        .pwrlvl_11n_11ac_2g4 = CONFIG_WIFI_TXPWR_LVL_11N_11AC_2G4,
        .pwrlvl_11ax_2g4     = CONFIG_WIFI_TXPWR_LVL_11AX_2G4,
        #if (PLF_AIC8800M40)
        .pwrlvl_11a_5g       = CONFIG_WIFI_TXPWR_LVL_11A_5G,
        .pwrlvl_11n_11ac_5g  = CONFIG_WIFI_TXPWR_LVL_11N_11AC_5G,
        .pwrlvl_11ax_5g      = CONFIG_WIFI_TXPWR_LVL_11AX_5G,
        #endif
    };
    if (!conf) {
        return;
    }
    *conf = user_conf;
}

void fhost_config_txpwr_loss_get(txpwr_loss_conf_t *conf)
{
    const txpwr_loss_conf_t user_conf = {
        .loss_enable        = CONFIG_WIFI_TXPWR_LOSS_ENABLE,
        .loss_value         = CONFIG_WIFI_TXPWR_LOSS_VALUE,
    };
    if (!conf) {
        return;
    }
    *conf = user_conf;
}
#endif

void fhost_config_txpwr_ofst_get(txpwr_ofst_conf_t *conf)
{
    const txpwr_ofst_conf_t user_conf = {
        .enabled        = CONFIG_WIFI_TXPWR_OFST_ENABLE,
        .chan_1_4       = CONFIG_WIFI_TXPWR_OFST_CHAN_1_4,
        .chan_5_9       = CONFIG_WIFI_TXPWR_OFST_CHAN_5_9,
        .chan_10_13     = CONFIG_WIFI_TXPWR_OFST_CHAN_10_13,
        .chan_36_64     = CONFIG_WIFI_TXPWR_OFST_CHAN_36_64,
        .chan_100_120   = CONFIG_WIFI_TXPWR_OFST_CHAN_100_120,
        .chan_122_140   = CONFIG_WIFI_TXPWR_OFST_CHAN_122_140,
        .chan_142_165   = CONFIG_WIFI_TXPWR_OFST_CHAN_142_165,
    };
    if (!conf) {
        return;
    }
    *conf = user_conf;
}

void fhost_config_txpwr_ofst2x_get(txpwr_ofst2x_conf_t *conf)
{
    const txpwr_ofst2x_conf_t user_conf = {
        .enabled            = CONFIG_WIFI_TXPWR_OFST_ENABLE,
        .pwrofst2x_tbl_2g4  = CONFIG_WIFI_TXPWR_OFST_BAND_2G4,
        .pwrofst2x_tbl_5g   = CONFIG_WIFI_TXPWR_OFST_BAND_5G,
    };
    if (!conf) {
        return;
    }
    *conf = user_conf;
}

/**
 * @}
 */
