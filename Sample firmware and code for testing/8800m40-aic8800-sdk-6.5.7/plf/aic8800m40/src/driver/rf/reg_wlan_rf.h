/**
 * @file reg_wlan_rf.h
 * @brief Definitions of the WLAN_RF HW block registers and register access functions.
 *
 * @defgroup REG_WLAN_RF REG_WLAN_RF
 * @ingroup REG
 * @{
 *
 * @brief Definitions of the WLAN_RF HW block registers and register access functions.
 */
#ifndef _REG_WLAN_RF_H_
#define _REG_WLAN_RF_H_

#include "compiler.h"
#include "arch.h"
#include "reg_access.h"

/** @brief Number of registers in the REG_WLAN_RF peripheral.
 */
#define REG_WLAN_RF_COUNT 54

/** @brief Decoding mask of the REG_WLAN_RF peripheral registers from the CPU point of view.
 */
#define REG_WLAN_RF_DECODING_MASK 0x000000FF

/**
 * @name REG_00 register definitions
 * <table>
 * <caption id="REG_00_BF">REG_00 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>wf_pu_lna5g_preamp_dr <td>R <td>R/W <td>0
 * <tr><td>30 <td>wf_pu_lna5g_preamp_reg <td>R <td>R/W <td>0
 * <tr><td>29 <td>      wf_pu_lna_dr <td>R <td>R/W <td>0
 * <tr><td>28 <td>     wf_pu_lna_reg <td>R <td>R/W <td>0
 * <tr><td>27 <td>      wf_pu_rmx_dr <td>R <td>R/W <td>0
 * <tr><td>26 <td>     wf_pu_rmx_reg <td>R <td>R/W <td>0
 * <tr><td>25 <td>wf_rmx_logen_dll_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>24 <td>wf_rmx_logen_dll_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>23 <td>      wf_pu_tia_dr <td>R <td>R/W <td>0
 * <tr><td>22 <td>     wf_pu_tia_reg <td>R <td>R/W <td>0
 * <tr><td>21 <td>    wf_tia_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>20 <td>   wf_tia_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>19 <td>       wf_pu_pa_dr <td>R <td>R/W <td>0
 * <tr><td>18 <td>      wf_pu_pa_reg <td>R <td>R/W <td>0
 * <tr><td>17 <td>wf_pa24g_bt_mode_en_dr <td>R <td>R/W <td>0
 * <tr><td>16 <td>wf_pa24g_bt_mode_en_reg <td>R <td>R/W <td>0
 * <tr><td>15 <td>wf_pa5g_gain_en_dr <td>R <td>R/W <td>0
 * <tr><td>14 <td>wf_pa5g_gain_en_reg <td>R <td>R/W <td>1
 * <tr><td>13 <td>wf_pa24g_gain_en_dr <td>R <td>R/W <td>0
 * <tr><td>12 <td>wf_pa24g_gain_en_reg <td>R <td>R/W <td>1
 * <tr><td>11 <td>wf_pu_trx5g_capsw_dr <td>R <td>R/W <td>0
 * <tr><td>10 <td>wf_pu_trx5g_capsw_reg <td>R <td>R/W <td>0
 * <tr><td>09 <td>wf_trx5g_sw_sel_avdd13_dr <td>R <td>R/W <td>0
 * <tr><td>08 <td>wf_trx5g_sw_sel_avdd13_reg <td>R <td>R/W <td>0
 * <tr><td>07 <td>wf_pu_trx24g_capsw_dr <td>R <td>R/W <td>0
 * <tr><td>06 <td>wf_pu_trx24g_capsw_reg <td>R <td>R/W <td>0
 * <tr><td>05 <td>wf_trx24g_sw_sel_avdd13_dr <td>R <td>R/W <td>0
 * <tr><td>04 <td>wf_trx24g_sw_sel_avdd13_reg <td>R <td>R/W <td>0
 * <tr><td>03 <td>wf_trx24g_wf2bt_rx_en_dr <td>R <td>R/W <td>0
 * <tr><td>02 <td>wf_trx24g_wf2bt_rx_en_reg <td>R <td>R/W <td>0
 * <tr><td>01 <td>wf_pa_pkdet_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>00 <td>wf_pa_pkdet_rstn_reg <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_00 register
#define WLAN_RF_REG_00_ADDR   0x40344000
/// Offset of the REG_00 register from the base address
#define WLAN_RF_REG_00_OFFSET 0x00000000
/// Index of the REG_00 register
#define WLAN_RF_REG_00_INDEX  0x00000000
/// Reset value of the REG_00 register
#define WLAN_RF_REG_00_RESET  0x00005000

/**
 * @brief Returns the current value of the REG_00 register.
 * The REG_00 register will be read and its value returned.
 * @return The current value of the REG_00 register.
 */
__INLINE uint32_t wlan_rf_reg_00_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_00_ADDR);
}

/**
 * @brief Sets the REG_00 register to a value.
 * The REG_00 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_00_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, value);
}

// field definitions
/// WF_PU_LNA_5G_PREAMP_DR field bit
#define WLAN_RF_WF_PU_LNA_5G_PREAMP_DR_BIT           ((uint32_t)0x80000000)
/// WF_PU_LNA_5G_PREAMP_DR field position
#define WLAN_RF_WF_PU_LNA_5G_PREAMP_DR_POS           31
/// WF_PU_LNA_5G_PREAMP_REG field bit
#define WLAN_RF_WF_PU_LNA_5G_PREAMP_REG_BIT          ((uint32_t)0x40000000)
/// WF_PU_LNA_5G_PREAMP_REG field position
#define WLAN_RF_WF_PU_LNA_5G_PREAMP_REG_POS          30
/// WF_PU_LNA_DR field bit
#define WLAN_RF_WF_PU_LNA_DR_BIT                     ((uint32_t)0x20000000)
/// WF_PU_LNA_DR field position
#define WLAN_RF_WF_PU_LNA_DR_POS                     29
/// WF_PU_LNA_REG field bit
#define WLAN_RF_WF_PU_LNA_REG_BIT                    ((uint32_t)0x10000000)
/// WF_PU_LNA_REG field position
#define WLAN_RF_WF_PU_LNA_REG_POS                    28
/// WF_PU_RMX_DR field bit
#define WLAN_RF_WF_PU_RMX_DR_BIT                     ((uint32_t)0x08000000)
/// WF_PU_RMX_DR field position
#define WLAN_RF_WF_PU_RMX_DR_POS                     27
/// WF_PU_RMX_REG field bit
#define WLAN_RF_WF_PU_RMX_REG_BIT                    ((uint32_t)0x04000000)
/// WF_PU_RMX_REG field position
#define WLAN_RF_WF_PU_RMX_REG_POS                    26
/// WF_RMX_LOGEN_DLL_RSTN_DR field bit
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_DR_BIT         ((uint32_t)0x02000000)
/// WF_RMX_LOGEN_DLL_RSTN_DR field position
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_DR_POS         25
/// WF_RMX_LOGEN_DLL_RSTN_REG field bit
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_REG_BIT        ((uint32_t)0x01000000)
/// WF_RMX_LOGEN_DLL_RSTN_REG field position
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_REG_POS        24
/// WF_PU_TIA_DR field bit
#define WLAN_RF_WF_PU_TIA_DR_BIT                     ((uint32_t)0x00800000)
/// WF_PU_TIA_DR field position
#define WLAN_RF_WF_PU_TIA_DR_POS                     23
/// WF_PU_TIA_REG field bit
#define WLAN_RF_WF_PU_TIA_REG_BIT                    ((uint32_t)0x00400000)
/// WF_PU_TIA_REG field position
#define WLAN_RF_WF_PU_TIA_REG_POS                    22
/// WF_TIA_RSTN_DR field bit
#define WLAN_RF_WF_TIA_RSTN_DR_BIT                   ((uint32_t)0x00200000)
/// WF_TIA_RSTN_DR field position
#define WLAN_RF_WF_TIA_RSTN_DR_POS                   21
/// WF_TIA_RSTN_REG field bit
#define WLAN_RF_WF_TIA_RSTN_REG_BIT                  ((uint32_t)0x00100000)
/// WF_TIA_RSTN_REG field position
#define WLAN_RF_WF_TIA_RSTN_REG_POS                  20
/// WF_PU_PA_DR field bit
#define WLAN_RF_WF_PU_PA_DR_BIT                      ((uint32_t)0x00080000)
/// WF_PU_PA_DR field position
#define WLAN_RF_WF_PU_PA_DR_POS                      19
/// WF_PU_PA_REG field bit
#define WLAN_RF_WF_PU_PA_REG_BIT                     ((uint32_t)0x00040000)
/// WF_PU_PA_REG field position
#define WLAN_RF_WF_PU_PA_REG_POS                     18
/// WF_PA_24G_BT_MODE_EN_DR field bit
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_DR_BIT          ((uint32_t)0x00020000)
/// WF_PA_24G_BT_MODE_EN_DR field position
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_DR_POS          17
/// WF_PA_24G_BT_MODE_EN_REG field bit
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_REG_BIT         ((uint32_t)0x00010000)
/// WF_PA_24G_BT_MODE_EN_REG field position
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_REG_POS         16
/// WF_PA_5G_GAIN_EN_DR field bit
#define WLAN_RF_WF_PA_5G_GAIN_EN_DR_BIT              ((uint32_t)0x00008000)
/// WF_PA_5G_GAIN_EN_DR field position
#define WLAN_RF_WF_PA_5G_GAIN_EN_DR_POS              15
/// WF_PA_5G_GAIN_EN_REG field bit
#define WLAN_RF_WF_PA_5G_GAIN_EN_REG_BIT             ((uint32_t)0x00004000)
/// WF_PA_5G_GAIN_EN_REG field position
#define WLAN_RF_WF_PA_5G_GAIN_EN_REG_POS             14
/// WF_PA_24G_GAIN_EN_DR field bit
#define WLAN_RF_WF_PA_24G_GAIN_EN_DR_BIT             ((uint32_t)0x00002000)
/// WF_PA_24G_GAIN_EN_DR field position
#define WLAN_RF_WF_PA_24G_GAIN_EN_DR_POS             13
/// WF_PA_24G_GAIN_EN_REG field bit
#define WLAN_RF_WF_PA_24G_GAIN_EN_REG_BIT            ((uint32_t)0x00001000)
/// WF_PA_24G_GAIN_EN_REG field position
#define WLAN_RF_WF_PA_24G_GAIN_EN_REG_POS            12
/// WF_PU_TRX_5G_CAPSW_DR field bit
#define WLAN_RF_WF_PU_TRX_5G_CAPSW_DR_BIT            ((uint32_t)0x00000800)
/// WF_PU_TRX_5G_CAPSW_DR field position
#define WLAN_RF_WF_PU_TRX_5G_CAPSW_DR_POS            11
/// WF_PU_TRX_5G_CAPSW_REG field bit
#define WLAN_RF_WF_PU_TRX_5G_CAPSW_REG_BIT           ((uint32_t)0x00000400)
/// WF_PU_TRX_5G_CAPSW_REG field position
#define WLAN_RF_WF_PU_TRX_5G_CAPSW_REG_POS           10
/// WF_TRX_5G_SW_SEL_AVDD_13_DR field bit
#define WLAN_RF_WF_TRX_5G_SW_SEL_AVDD_13_DR_BIT      ((uint32_t)0x00000200)
/// WF_TRX_5G_SW_SEL_AVDD_13_DR field position
#define WLAN_RF_WF_TRX_5G_SW_SEL_AVDD_13_DR_POS      9
/// WF_TRX_5G_SW_SEL_AVDD_13_REG field bit
#define WLAN_RF_WF_TRX_5G_SW_SEL_AVDD_13_REG_BIT     ((uint32_t)0x00000100)
/// WF_TRX_5G_SW_SEL_AVDD_13_REG field position
#define WLAN_RF_WF_TRX_5G_SW_SEL_AVDD_13_REG_POS     8
/// WF_PU_TRX_24G_CAPSW_DR field bit
#define WLAN_RF_WF_PU_TRX_24G_CAPSW_DR_BIT           ((uint32_t)0x00000080)
/// WF_PU_TRX_24G_CAPSW_DR field position
#define WLAN_RF_WF_PU_TRX_24G_CAPSW_DR_POS           7
/// WF_PU_TRX_24G_CAPSW_REG field bit
#define WLAN_RF_WF_PU_TRX_24G_CAPSW_REG_BIT          ((uint32_t)0x00000040)
/// WF_PU_TRX_24G_CAPSW_REG field position
#define WLAN_RF_WF_PU_TRX_24G_CAPSW_REG_POS          6
/// WF_TRX_24G_SW_SEL_AVDD_13_DR field bit
#define WLAN_RF_WF_TRX_24G_SW_SEL_AVDD_13_DR_BIT     ((uint32_t)0x00000020)
/// WF_TRX_24G_SW_SEL_AVDD_13_DR field position
#define WLAN_RF_WF_TRX_24G_SW_SEL_AVDD_13_DR_POS     5
/// WF_TRX_24G_SW_SEL_AVDD_13_REG field bit
#define WLAN_RF_WF_TRX_24G_SW_SEL_AVDD_13_REG_BIT    ((uint32_t)0x00000010)
/// WF_TRX_24G_SW_SEL_AVDD_13_REG field position
#define WLAN_RF_WF_TRX_24G_SW_SEL_AVDD_13_REG_POS    4
/// WF_TRX_24G_WF_2BT_RX_EN_DR field bit
#define WLAN_RF_WF_TRX_24G_WF_2BT_RX_EN_DR_BIT       ((uint32_t)0x00000008)
/// WF_TRX_24G_WF_2BT_RX_EN_DR field position
#define WLAN_RF_WF_TRX_24G_WF_2BT_RX_EN_DR_POS       3
/// WF_TRX_24G_WF_2BT_RX_EN_REG field bit
#define WLAN_RF_WF_TRX_24G_WF_2BT_RX_EN_REG_BIT      ((uint32_t)0x00000004)
/// WF_TRX_24G_WF_2BT_RX_EN_REG field position
#define WLAN_RF_WF_TRX_24G_WF_2BT_RX_EN_REG_POS      2
/// WF_PA_PKDET_RSTN_DR field bit
#define WLAN_RF_WF_PA_PKDET_RSTN_DR_BIT              ((uint32_t)0x00000002)
/// WF_PA_PKDET_RSTN_DR field position
#define WLAN_RF_WF_PA_PKDET_RSTN_DR_POS              1
/// WF_PA_PKDET_RSTN_REG field bit
#define WLAN_RF_WF_PA_PKDET_RSTN_REG_BIT             ((uint32_t)0x00000001)
/// WF_PA_PKDET_RSTN_REG field position
#define WLAN_RF_WF_PA_PKDET_RSTN_REG_POS             0

/// WF_PU_LNA_5G_PREAMP_DR field reset value
#define WLAN_RF_WF_PU_LNA_5G_PREAMP_DR_RST           0x0
/// WF_PU_LNA_5G_PREAMP_REG field reset value
#define WLAN_RF_WF_PU_LNA_5G_PREAMP_REG_RST          0x0
/// WF_PU_LNA_DR field reset value
#define WLAN_RF_WF_PU_LNA_DR_RST                     0x0
/// WF_PU_LNA_REG field reset value
#define WLAN_RF_WF_PU_LNA_REG_RST                    0x0
/// WF_PU_RMX_DR field reset value
#define WLAN_RF_WF_PU_RMX_DR_RST                     0x0
/// WF_PU_RMX_REG field reset value
#define WLAN_RF_WF_PU_RMX_REG_RST                    0x0
/// WF_RMX_LOGEN_DLL_RSTN_DR field reset value
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_DR_RST         0x0
/// WF_RMX_LOGEN_DLL_RSTN_REG field reset value
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_REG_RST        0x0
/// WF_PU_TIA_DR field reset value
#define WLAN_RF_WF_PU_TIA_DR_RST                     0x0
/// WF_PU_TIA_REG field reset value
#define WLAN_RF_WF_PU_TIA_REG_RST                    0x0
/// WF_TIA_RSTN_DR field reset value
#define WLAN_RF_WF_TIA_RSTN_DR_RST                   0x0
/// WF_TIA_RSTN_REG field reset value
#define WLAN_RF_WF_TIA_RSTN_REG_RST                  0x0
/// WF_PU_PA_DR field reset value
#define WLAN_RF_WF_PU_PA_DR_RST                      0x0
/// WF_PU_PA_REG field reset value
#define WLAN_RF_WF_PU_PA_REG_RST                     0x0
/// WF_PA_24G_BT_MODE_EN_DR field reset value
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_DR_RST          0x0
/// WF_PA_24G_BT_MODE_EN_REG field reset value
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_REG_RST         0x0
/// WF_PA_5G_GAIN_EN_DR field reset value
#define WLAN_RF_WF_PA_5G_GAIN_EN_DR_RST              0x0
/// WF_PA_5G_GAIN_EN_REG field reset value
#define WLAN_RF_WF_PA_5G_GAIN_EN_REG_RST             0x1
/// WF_PA_24G_GAIN_EN_DR field reset value
#define WLAN_RF_WF_PA_24G_GAIN_EN_DR_RST             0x0
/// WF_PA_24G_GAIN_EN_REG field reset value
#define WLAN_RF_WF_PA_24G_GAIN_EN_REG_RST            0x1
/// WF_PU_TRX_5G_CAPSW_DR field reset value
#define WLAN_RF_WF_PU_TRX_5G_CAPSW_DR_RST            0x0
/// WF_PU_TRX_5G_CAPSW_REG field reset value
#define WLAN_RF_WF_PU_TRX_5G_CAPSW_REG_RST           0x0
/// WF_TRX_5G_SW_SEL_AVDD_13_DR field reset value
#define WLAN_RF_WF_TRX_5G_SW_SEL_AVDD_13_DR_RST      0x0
/// WF_TRX_5G_SW_SEL_AVDD_13_REG field reset value
#define WLAN_RF_WF_TRX_5G_SW_SEL_AVDD_13_REG_RST     0x0
/// WF_PU_TRX_24G_CAPSW_DR field reset value
#define WLAN_RF_WF_PU_TRX_24G_CAPSW_DR_RST           0x0
/// WF_PU_TRX_24G_CAPSW_REG field reset value
#define WLAN_RF_WF_PU_TRX_24G_CAPSW_REG_RST          0x0
/// WF_TRX_24G_SW_SEL_AVDD_13_DR field reset value
#define WLAN_RF_WF_TRX_24G_SW_SEL_AVDD_13_DR_RST     0x0
/// WF_TRX_24G_SW_SEL_AVDD_13_REG field reset value
#define WLAN_RF_WF_TRX_24G_SW_SEL_AVDD_13_REG_RST    0x0
/// WF_TRX_24G_WF_2BT_RX_EN_DR field reset value
#define WLAN_RF_WF_TRX_24G_WF_2BT_RX_EN_DR_RST       0x0
/// WF_TRX_24G_WF_2BT_RX_EN_REG field reset value
#define WLAN_RF_WF_TRX_24G_WF_2BT_RX_EN_REG_RST      0x0
/// WF_PA_PKDET_RSTN_DR field reset value
#define WLAN_RF_WF_PA_PKDET_RSTN_DR_RST              0x0
/// WF_PA_PKDET_RSTN_REG field reset value
#define WLAN_RF_WF_PA_PKDET_RSTN_REG_RST             0x0

/**
 * @brief Constructs a value for the REG_00 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpulna5gpreampdr - The value to use for the wf_pu_lna5g_preamp_dr field.
 * @param[in] wfpulna5gpreampreg - The value to use for the wf_pu_lna5g_preamp_reg field.
 * @param[in] wfpulnadr - The value to use for the wf_pu_lna_dr field.
 * @param[in] wfpulnareg - The value to use for the wf_pu_lna_reg field.
 * @param[in] wfpurmxdr - The value to use for the wf_pu_rmx_dr field.
 * @param[in] wfpurmxreg - The value to use for the wf_pu_rmx_reg field.
 * @param[in] wfrmxlogendllrstndr - The value to use for the wf_rmx_logen_dll_rstn_dr field.
 * @param[in] wfrmxlogendllrstnreg - The value to use for the wf_rmx_logen_dll_rstn_reg field.
 * @param[in] wfputiadr - The value to use for the wf_pu_tia_dr field.
 * @param[in] wfputiareg - The value to use for the wf_pu_tia_reg field.
 * @param[in] wftiarstndr - The value to use for the wf_tia_rstn_dr field.
 * @param[in] wftiarstnreg - The value to use for the wf_tia_rstn_reg field.
 * @param[in] wfpupadr - The value to use for the wf_pu_pa_dr field.
 * @param[in] wfpupareg - The value to use for the wf_pu_pa_reg field.
 * @param[in] wfpa24gbtmodeendr - The value to use for the wf_pa24g_bt_mode_en_dr field.
 * @param[in] wfpa24gbtmodeenreg - The value to use for the wf_pa24g_bt_mode_en_reg field.
 * @param[in] wfpa5ggainendr - The value to use for the wf_pa5g_gain_en_dr field.
 * @param[in] wfpa5ggainenreg - The value to use for the wf_pa5g_gain_en_reg field.
 * @param[in] wfpa24ggainendr - The value to use for the wf_pa24g_gain_en_dr field.
 * @param[in] wfpa24ggainenreg - The value to use for the wf_pa24g_gain_en_reg field.
 * @param[in] wfputrx5gcapswdr - The value to use for the wf_pu_trx5g_capsw_dr field.
 * @param[in] wfputrx5gcapswreg - The value to use for the wf_pu_trx5g_capsw_reg field.
 * @param[in] wftrx5gswselavdd13dr - The value to use for the wf_trx5g_sw_sel_avdd13_dr field.
 * @param[in] wftrx5gswselavdd13reg - The value to use for the wf_trx5g_sw_sel_avdd13_reg field.
 * @param[in] wfputrx24gcapswdr - The value to use for the wf_pu_trx24g_capsw_dr field.
 * @param[in] wfputrx24gcapswreg - The value to use for the wf_pu_trx24g_capsw_reg field.
 * @param[in] wftrx24gswselavdd13dr - The value to use for the wf_trx24g_sw_sel_avdd13_dr field.
 * @param[in] wftrx24gswselavdd13reg - The value to use for the wf_trx24g_sw_sel_avdd13_reg field.
 * @param[in] wftrx24gwf2btrxendr - The value to use for the wf_trx24g_wf2bt_rx_en_dr field.
 * @param[in] wftrx24gwf2btrxenreg - The value to use for the wf_trx24g_wf2bt_rx_en_reg field.
 * @param[in] wfpapkdetrstndr - The value to use for the wf_pa_pkdet_rstn_dr field.
 * @param[in] wfpapkdetrstnreg - The value to use for the wf_pa_pkdet_rstn_reg field.
 */
__INLINE void wlan_rf_reg_00_pack(uint8_t wfpulna5gpreampdr, uint8_t wfpulna5gpreampreg, uint8_t wfpulnadr, uint8_t wfpulnareg, uint8_t wfpurmxdr, uint8_t wfpurmxreg, uint8_t wfrmxlogendllrstndr, uint8_t wfrmxlogendllrstnreg, uint8_t wfputiadr, uint8_t wfputiareg, uint8_t wftiarstndr, uint8_t wftiarstnreg, uint8_t wfpupadr, uint8_t wfpupareg, uint8_t wfpa24gbtmodeendr, uint8_t wfpa24gbtmodeenreg, uint8_t wfpa5ggainendr, uint8_t wfpa5ggainenreg, uint8_t wfpa24ggainendr, uint8_t wfpa24ggainenreg, uint8_t wfputrx5gcapswdr, uint8_t wfputrx5gcapswreg, uint8_t wftrx5gswselavdd13dr, uint8_t wftrx5gswselavdd13reg, uint8_t wfputrx24gcapswdr, uint8_t wfputrx24gcapswreg, uint8_t wftrx24gswselavdd13dr, uint8_t wftrx24gswselavdd13reg, uint8_t wftrx24gwf2btrxendr, uint8_t wftrx24gwf2btrxenreg, uint8_t wfpapkdetrstndr, uint8_t wfpapkdetrstnreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR,  ((uint32_t)wfpulna5gpreampdr << 31) | ((uint32_t)wfpulna5gpreampreg << 30) | ((uint32_t)wfpulnadr << 29) | ((uint32_t)wfpulnareg << 28) | ((uint32_t)wfpurmxdr << 27) | ((uint32_t)wfpurmxreg << 26) | ((uint32_t)wfrmxlogendllrstndr << 25) | ((uint32_t)wfrmxlogendllrstnreg << 24) | ((uint32_t)wfputiadr << 23) | ((uint32_t)wfputiareg << 22) | ((uint32_t)wftiarstndr << 21) | ((uint32_t)wftiarstnreg << 20) | ((uint32_t)wfpupadr << 19) | ((uint32_t)wfpupareg << 18) | ((uint32_t)wfpa24gbtmodeendr << 17) | ((uint32_t)wfpa24gbtmodeenreg << 16) | ((uint32_t)wfpa5ggainendr << 15) | ((uint32_t)wfpa5ggainenreg << 14) | ((uint32_t)wfpa24ggainendr << 13) | ((uint32_t)wfpa24ggainenreg << 12) | ((uint32_t)wfputrx5gcapswdr << 11) | ((uint32_t)wfputrx5gcapswreg << 10) | ((uint32_t)wftrx5gswselavdd13dr << 9) | ((uint32_t)wftrx5gswselavdd13reg << 8) | ((uint32_t)wfputrx24gcapswdr << 7) | ((uint32_t)wfputrx24gcapswreg << 6) | ((uint32_t)wftrx24gswselavdd13dr << 5) | ((uint32_t)wftrx24gswselavdd13reg << 4) | ((uint32_t)wftrx24gwf2btrxendr << 3) | ((uint32_t)wftrx24gwf2btrxenreg << 2) | ((uint32_t)wfpapkdetrstndr << 1) | ((uint32_t)wfpapkdetrstnreg << 0));
}

/**
 * @brief Unpacks REG_00's fields from current value of the REG_00 register.
 *
 * Reads the REG_00 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpulna5gpreampdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpulna5gpreampreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpulnadr - Will be populated with the current value of this field from the register.
 * @param[out] wfpulnareg - Will be populated with the current value of this field from the register.
 * @param[out] wfpurmxdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpurmxreg - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogendllrstndr - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogendllrstnreg - Will be populated with the current value of this field from the register.
 * @param[out] wfputiadr - Will be populated with the current value of this field from the register.
 * @param[out] wfputiareg - Will be populated with the current value of this field from the register.
 * @param[out] wftiarstndr - Will be populated with the current value of this field from the register.
 * @param[out] wftiarstnreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpupadr - Will be populated with the current value of this field from the register.
 * @param[out] wfpupareg - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gbtmodeendr - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gbtmodeenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5ggainendr - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5ggainenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24ggainendr - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24ggainenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfputrx5gcapswdr - Will be populated with the current value of this field from the register.
 * @param[out] wfputrx5gcapswreg - Will be populated with the current value of this field from the register.
 * @param[out] wftrx5gswselavdd13dr - Will be populated with the current value of this field from the register.
 * @param[out] wftrx5gswselavdd13reg - Will be populated with the current value of this field from the register.
 * @param[out] wfputrx24gcapswdr - Will be populated with the current value of this field from the register.
 * @param[out] wfputrx24gcapswreg - Will be populated with the current value of this field from the register.
 * @param[out] wftrx24gswselavdd13dr - Will be populated with the current value of this field from the register.
 * @param[out] wftrx24gswselavdd13reg - Will be populated with the current value of this field from the register.
 * @param[out] wftrx24gwf2btrxendr - Will be populated with the current value of this field from the register.
 * @param[out] wftrx24gwf2btrxenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetrstndr - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetrstnreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_00_unpack(uint8_t* wfpulna5gpreampdr, uint8_t* wfpulna5gpreampreg, uint8_t* wfpulnadr, uint8_t* wfpulnareg, uint8_t* wfpurmxdr, uint8_t* wfpurmxreg, uint8_t* wfrmxlogendllrstndr, uint8_t* wfrmxlogendllrstnreg, uint8_t* wfputiadr, uint8_t* wfputiareg, uint8_t* wftiarstndr, uint8_t* wftiarstnreg, uint8_t* wfpupadr, uint8_t* wfpupareg, uint8_t* wfpa24gbtmodeendr, uint8_t* wfpa24gbtmodeenreg, uint8_t* wfpa5ggainendr, uint8_t* wfpa5ggainenreg, uint8_t* wfpa24ggainendr, uint8_t* wfpa24ggainenreg, uint8_t* wfputrx5gcapswdr, uint8_t* wfputrx5gcapswreg, uint8_t* wftrx5gswselavdd13dr, uint8_t* wftrx5gswselavdd13reg, uint8_t* wfputrx24gcapswdr, uint8_t* wfputrx24gcapswreg, uint8_t* wftrx24gswselavdd13dr, uint8_t* wftrx24gswselavdd13reg, uint8_t* wftrx24gwf2btrxendr, uint8_t* wftrx24gwf2btrxenreg, uint8_t* wfpapkdetrstndr, uint8_t* wfpapkdetrstnreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);

    *wfpulna5gpreampdr = (localVal & ((uint32_t)0x80000000)) >> 31;
    *wfpulna5gpreampreg = (localVal & ((uint32_t)0x40000000)) >> 30;
    *wfpulnadr = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wfpulnareg = (localVal & ((uint32_t)0x10000000)) >> 28;
    *wfpurmxdr = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfpurmxreg = (localVal & ((uint32_t)0x04000000)) >> 26;
    *wfrmxlogendllrstndr = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wfrmxlogendllrstnreg = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wfputiadr = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfputiareg = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wftiarstndr = (localVal & ((uint32_t)0x00200000)) >> 21;
    *wftiarstnreg = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wfpupadr = (localVal & ((uint32_t)0x00080000)) >> 19;
    *wfpupareg = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfpa24gbtmodeendr = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wfpa24gbtmodeenreg = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wfpa5ggainendr = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wfpa5ggainenreg = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wfpa24ggainendr = (localVal & ((uint32_t)0x00002000)) >> 13;
    *wfpa24ggainenreg = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wfputrx5gcapswdr = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wfputrx5gcapswreg = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wftrx5gswselavdd13dr = (localVal & ((uint32_t)0x00000200)) >> 9;
    *wftrx5gswselavdd13reg = (localVal & ((uint32_t)0x00000100)) >> 8;
    *wfputrx24gcapswdr = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wfputrx24gcapswreg = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wftrx24gswselavdd13dr = (localVal & ((uint32_t)0x00000020)) >> 5;
    *wftrx24gswselavdd13reg = (localVal & ((uint32_t)0x00000010)) >> 4;
    *wftrx24gwf2btrxendr = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wftrx24gwf2btrxenreg = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wfpapkdetrstndr = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfpapkdetrstnreg = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pu_lna5g_preamp_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_lna5g_preamp_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_lna5g_preamp_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_lna_5g_preamp_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the wf_pu_lna5g_preamp_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpulna5gpreampdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_lna_5g_preamp_dr_setf(uint8_t wfpulna5gpreampdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)wfpulna5gpreampdr << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the wf_pu_lna5g_preamp_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_lna5g_preamp_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_lna5g_preamp_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_lna_5g_preamp_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the wf_pu_lna5g_preamp_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpulna5gpreampreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_lna_5g_preamp_reg_setf(uint8_t wfpulna5gpreampreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)wfpulna5gpreampreg << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the wf_pu_lna_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_lna_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_lna_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_lna_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the wf_pu_lna_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpulnadr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_lna_dr_setf(uint8_t wfpulnadr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wfpulnadr << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the wf_pu_lna_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_lna_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_lna_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_lna_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the wf_pu_lna_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpulnareg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_lna_reg_setf(uint8_t wfpulnareg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)wfpulnareg << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the wf_pu_rmx_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_rmx_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_rmx_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rmx_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_pu_rmx_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurmxdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rmx_dr_setf(uint8_t wfpurmxdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wfpurmxdr << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_pu_rmx_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_rmx_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_rmx_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rmx_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the wf_pu_rmx_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurmxreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rmx_reg_setf(uint8_t wfpurmxreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)wfpurmxreg << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_dll_rstn_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_rmx_logen_dll_rstn_dr field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_dll_rstn_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_dll_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_rmx_logen_dll_rstn_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogendllrstndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_dll_rstn_dr_setf(uint8_t wfrmxlogendllrstndr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wfrmxlogendllrstndr << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_dll_rstn_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_rmx_logen_dll_rstn_reg field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_dll_rstn_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_dll_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the wf_rmx_logen_dll_rstn_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogendllrstnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_dll_rstn_reg_setf(uint8_t wfrmxlogendllrstnreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wfrmxlogendllrstnreg << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the wf_pu_tia_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_tia_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_tia_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_tia_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_pu_tia_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputiadr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_tia_dr_setf(uint8_t wfputiadr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wfputiadr << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_pu_tia_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_tia_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_tia_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_tia_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the wf_pu_tia_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputiareg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_tia_reg_setf(uint8_t wfputiareg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)wfputiareg << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the wf_tia_rstn_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_tia_rstn_dr field's value will be returned.
 *
 * @return The current value of the wf_tia_rstn_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Sets the wf_tia_rstn_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiarstndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_rstn_dr_setf(uint8_t wftiarstndr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00200000)) | (((uint32_t)wftiarstndr << 21) & ((uint32_t)0x00200000)));
}

/**
 * @brief Returns the current value of the wf_tia_rstn_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_tia_rstn_reg field's value will be returned.
 *
 * @return The current value of the wf_tia_rstn_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_tia_rstn_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiarstnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_rstn_reg_setf(uint8_t wftiarstnreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wftiarstnreg << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the wf_pu_pa_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_pa_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_pa_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_pa_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the wf_pu_pa_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpupadr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_pa_dr_setf(uint8_t wfpupadr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)wfpupadr << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the wf_pu_pa_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_pa_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_pa_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_pa_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_pu_pa_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpupareg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_pa_reg_setf(uint8_t wfpupareg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wfpupareg << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_pa24g_bt_mode_en_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa24g_bt_mode_en_dr field's value will be returned.
 *
 * @return The current value of the wf_pa24g_bt_mode_en_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_bt_mode_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_pa24g_bt_mode_en_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24gbtmodeendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_bt_mode_en_dr_setf(uint8_t wfpa24gbtmodeendr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wfpa24gbtmodeendr << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_pa24g_bt_mode_en_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa24g_bt_mode_en_reg field's value will be returned.
 *
 * @return The current value of the wf_pa24g_bt_mode_en_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_bt_mode_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_pa24g_bt_mode_en_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24gbtmodeenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_bt_mode_en_reg_setf(uint8_t wfpa24gbtmodeenreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wfpa24gbtmodeenreg << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_pa5g_gain_en_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa5g_gain_en_dr field's value will be returned.
 *
 * @return The current value of the wf_pa5g_gain_en_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_gain_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the wf_pa5g_gain_en_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5ggainendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_gain_en_dr_setf(uint8_t wfpa5ggainendr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)wfpa5ggainendr << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the wf_pa5g_gain_en_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa5g_gain_en_reg field's value will be returned.
 *
 * @return The current value of the wf_pa5g_gain_en_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_gain_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the wf_pa5g_gain_en_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5ggainenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_gain_en_reg_setf(uint8_t wfpa5ggainenreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)wfpa5ggainenreg << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the wf_pa24g_gain_en_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa24g_gain_en_dr field's value will be returned.
 *
 * @return The current value of the wf_pa24g_gain_en_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_gain_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the wf_pa24g_gain_en_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24ggainendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_gain_en_dr_setf(uint8_t wfpa24ggainendr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)wfpa24ggainendr << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the wf_pa24g_gain_en_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa24g_gain_en_reg field's value will be returned.
 *
 * @return The current value of the wf_pa24g_gain_en_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_gain_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_pa24g_gain_en_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24ggainenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_gain_en_reg_setf(uint8_t wfpa24ggainenreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wfpa24ggainenreg << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the wf_pu_trx5g_capsw_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_trx5g_capsw_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_trx5g_capsw_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_trx_5g_capsw_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_pu_trx5g_capsw_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputrx5gcapswdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_trx_5g_capsw_dr_setf(uint8_t wfputrx5gcapswdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wfputrx5gcapswdr << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_pu_trx5g_capsw_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_trx5g_capsw_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_trx5g_capsw_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_trx_5g_capsw_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_pu_trx5g_capsw_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputrx5gcapswreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_trx_5g_capsw_reg_setf(uint8_t wfputrx5gcapswreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfputrx5gcapswreg << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_trx5g_sw_sel_avdd13_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_trx5g_sw_sel_avdd13_dr field's value will be returned.
 *
 * @return The current value of the wf_trx5g_sw_sel_avdd13_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_5g_sw_sel_avdd_13_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the wf_trx5g_sw_sel_avdd13_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftrx5gswselavdd13dr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_trx_5g_sw_sel_avdd_13_dr_setf(uint8_t wftrx5gswselavdd13dr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)wftrx5gswselavdd13dr << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the wf_trx5g_sw_sel_avdd13_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_trx5g_sw_sel_avdd13_reg field's value will be returned.
 *
 * @return The current value of the wf_trx5g_sw_sel_avdd13_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_5g_sw_sel_avdd_13_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the wf_trx5g_sw_sel_avdd13_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftrx5gswselavdd13reg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_trx_5g_sw_sel_avdd_13_reg_setf(uint8_t wftrx5gswselavdd13reg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)wftrx5gswselavdd13reg << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the wf_pu_trx24g_capsw_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_trx24g_capsw_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_trx24g_capsw_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_trx_24g_capsw_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_pu_trx24g_capsw_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputrx24gcapswdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_trx_24g_capsw_dr_setf(uint8_t wfputrx24gcapswdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wfputrx24gcapswdr << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_pu_trx24g_capsw_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_trx24g_capsw_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_trx24g_capsw_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_trx_24g_capsw_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the wf_pu_trx24g_capsw_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputrx24gcapswreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_trx_24g_capsw_reg_setf(uint8_t wfputrx24gcapswreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)wfputrx24gcapswreg << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the wf_trx24g_sw_sel_avdd13_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_trx24g_sw_sel_avdd13_dr field's value will be returned.
 *
 * @return The current value of the wf_trx24g_sw_sel_avdd13_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_24g_sw_sel_avdd_13_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the wf_trx24g_sw_sel_avdd13_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftrx24gswselavdd13dr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_trx_24g_sw_sel_avdd_13_dr_setf(uint8_t wftrx24gswselavdd13dr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)wftrx24gswselavdd13dr << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the wf_trx24g_sw_sel_avdd13_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_trx24g_sw_sel_avdd13_reg field's value will be returned.
 *
 * @return The current value of the wf_trx24g_sw_sel_avdd13_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_24g_sw_sel_avdd_13_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the wf_trx24g_sw_sel_avdd13_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftrx24gswselavdd13reg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_trx_24g_sw_sel_avdd_13_reg_setf(uint8_t wftrx24gswselavdd13reg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)wftrx24gswselavdd13reg << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the wf_trx24g_wf2bt_rx_en_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_trx24g_wf2bt_rx_en_dr field's value will be returned.
 *
 * @return The current value of the wf_trx24g_wf2bt_rx_en_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_24g_wf_2bt_rx_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wf_trx24g_wf2bt_rx_en_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftrx24gwf2btrxendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_trx_24g_wf_2bt_rx_en_dr_setf(uint8_t wftrx24gwf2btrxendr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wftrx24gwf2btrxendr << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wf_trx24g_wf2bt_rx_en_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_trx24g_wf2bt_rx_en_reg field's value will be returned.
 *
 * @return The current value of the wf_trx24g_wf2bt_rx_en_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_24g_wf_2bt_rx_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wf_trx24g_wf2bt_rx_en_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftrx24gwf2btrxenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_trx_24g_wf_2bt_rx_en_reg_setf(uint8_t wftrx24gwf2btrxenreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wftrx24gwf2btrxenreg << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_rstn_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa_pkdet_rstn_dr field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_rstn_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_pa_pkdet_rstn_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkdetrstndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkdet_rstn_dr_setf(uint8_t wfpapkdetrstndr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfpapkdetrstndr << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_rstn_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa_pkdet_rstn_reg field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_rstn_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_pa_pkdet_rstn_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkdetrstnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkdet_rstn_reg_setf(uint8_t wfpapkdetrstnreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfpapkdetrstnreg << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_04 register definitions
 * <table>
 * <caption id="REG_04_BF">REG_04 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>     wf_pu_dtmx_dr <td>R <td>R/W <td>0
 * <tr><td>30 <td>    wf_pu_dtmx_reg <td>R <td>R/W <td>0
 * <tr><td>29 <td>wf_dtmx_bt2wf_tx_en_dr <td>R <td>R/W <td>0
 * <tr><td>28 <td>wf_dtmx_bt2wf_tx_en_reg <td>R <td>R/W <td>0
 * <tr><td>27 <td>wf_dtmx_logen_dll_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>26 <td>wf_dtmx_logen_dll_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>25 <td>wf_dtmx_cdr_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>24 <td>wf_dtmx_cdr_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>23 <td>     wf_pu_iref_dr <td>R <td>R/W <td>0
 * <tr><td>22 <td>    wf_pu_iref_reg <td>R <td>R/W <td>0
 * <tr><td>21 <td>    wf_pu_rxflt_dr <td>R <td>R/W <td>0
 * <tr><td>20 <td>   wf_pu_rxflt_reg <td>R <td>R/W <td>0
 * <tr><td>19 <td>  wf_rxflt_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>18 <td> wf_rxflt_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>17 <td>      wf_pu_adc_dr <td>R <td>R/W <td>0
 * <tr><td>16 <td>     wf_pu_adc_reg <td>R <td>R/W <td>0
 * <tr><td>15 <td>wf_pu_adc_vreg_com_dr <td>R <td>R/W <td>0
 * <tr><td>14 <td>wf_pu_adc_vreg_com_reg <td>R <td>R/W <td>0
 * <tr><td>13 <td>    wf_pu_pdadc_dr <td>R <td>R/W <td>0
 * <tr><td>12 <td>   wf_pu_pdadc_reg <td>R <td>R/W <td>0
 * <tr><td>11 <td>    wf_pu_rfpll_dr <td>R <td>R/W <td>0
 * <tr><td>10 <td>   wf_pu_rfpll_reg <td>R <td>R/W <td>0
 * <tr><td>09 <td>wf_rfpll_adc_clk_en_dr <td>R <td>R/W <td>0
 * <tr><td>08 <td>wf_rfpll_adc_clk_en_reg <td>R <td>R/W <td>0
 * <tr><td>07 <td>wf_rfpll_vctrl_det_en_dr <td>R <td>R/W <td>0
 * <tr><td>06 <td>wf_rfpll_vctrl_det_en_reg <td>R <td>R/W <td>0
 * <tr><td>05 <td>wf_logen_phase_mux_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>04 <td>wf_logen_phase_mux_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>03 <td>      wf_pu_vco_dr <td>R <td>R/W <td>0
 * <tr><td>02 <td>     wf_pu_vco_reg <td>R <td>R/W <td>0
 * <tr><td>01 <td> wf_vco_txlo_en_dr <td>R <td>R/W <td>0
 * <tr><td>00 <td>wf_vco_txlo_en_reg <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_04 register
#define WLAN_RF_REG_04_ADDR   0x40344004
/// Offset of the REG_04 register from the base address
#define WLAN_RF_REG_04_OFFSET 0x00000004
/// Index of the REG_04 register
#define WLAN_RF_REG_04_INDEX  0x00000001
/// Reset value of the REG_04 register
#define WLAN_RF_REG_04_RESET  0x00000001

/**
 * @brief Returns the current value of the REG_04 register.
 * The REG_04 register will be read and its value returned.
 * @return The current value of the REG_04 register.
 */
__INLINE uint32_t wlan_rf_reg_04_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_04_ADDR);
}

/**
 * @brief Sets the REG_04 register to a value.
 * The REG_04 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_04_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, value);
}

// field definitions
/// WF_PU_DTMX_DR field bit
#define WLAN_RF_WF_PU_DTMX_DR_BIT                  ((uint32_t)0x80000000)
/// WF_PU_DTMX_DR field position
#define WLAN_RF_WF_PU_DTMX_DR_POS                  31
/// WF_PU_DTMX_REG field bit
#define WLAN_RF_WF_PU_DTMX_REG_BIT                 ((uint32_t)0x40000000)
/// WF_PU_DTMX_REG field position
#define WLAN_RF_WF_PU_DTMX_REG_POS                 30
/// WF_DTMX_BT_2WF_TX_EN_DR field bit
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_DR_BIT        ((uint32_t)0x20000000)
/// WF_DTMX_BT_2WF_TX_EN_DR field position
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_DR_POS        29
/// WF_DTMX_BT_2WF_TX_EN_REG field bit
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_REG_BIT       ((uint32_t)0x10000000)
/// WF_DTMX_BT_2WF_TX_EN_REG field position
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_REG_POS       28
/// WF_DTMX_LOGEN_DLL_RSTN_DR field bit
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_DR_BIT      ((uint32_t)0x08000000)
/// WF_DTMX_LOGEN_DLL_RSTN_DR field position
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_DR_POS      27
/// WF_DTMX_LOGEN_DLL_RSTN_REG field bit
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_REG_BIT     ((uint32_t)0x04000000)
/// WF_DTMX_LOGEN_DLL_RSTN_REG field position
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_REG_POS     26
/// WF_DTMX_CDR_RSTN_DR field bit
#define WLAN_RF_WF_DTMX_CDR_RSTN_DR_BIT            ((uint32_t)0x02000000)
/// WF_DTMX_CDR_RSTN_DR field position
#define WLAN_RF_WF_DTMX_CDR_RSTN_DR_POS            25
/// WF_DTMX_CDR_RSTN_REG field bit
#define WLAN_RF_WF_DTMX_CDR_RSTN_REG_BIT           ((uint32_t)0x01000000)
/// WF_DTMX_CDR_RSTN_REG field position
#define WLAN_RF_WF_DTMX_CDR_RSTN_REG_POS           24
/// WF_PU_IREF_DR field bit
#define WLAN_RF_WF_PU_IREF_DR_BIT                  ((uint32_t)0x00800000)
/// WF_PU_IREF_DR field position
#define WLAN_RF_WF_PU_IREF_DR_POS                  23
/// WF_PU_IREF_REG field bit
#define WLAN_RF_WF_PU_IREF_REG_BIT                 ((uint32_t)0x00400000)
/// WF_PU_IREF_REG field position
#define WLAN_RF_WF_PU_IREF_REG_POS                 22
/// WF_PU_RXFLT_DR field bit
#define WLAN_RF_WF_PU_RXFLT_DR_BIT                 ((uint32_t)0x00200000)
/// WF_PU_RXFLT_DR field position
#define WLAN_RF_WF_PU_RXFLT_DR_POS                 21
/// WF_PU_RXFLT_REG field bit
#define WLAN_RF_WF_PU_RXFLT_REG_BIT                ((uint32_t)0x00100000)
/// WF_PU_RXFLT_REG field position
#define WLAN_RF_WF_PU_RXFLT_REG_POS                20
/// WF_RXFLT_RSTN_DR field bit
#define WLAN_RF_WF_RXFLT_RSTN_DR_BIT               ((uint32_t)0x00080000)
/// WF_RXFLT_RSTN_DR field position
#define WLAN_RF_WF_RXFLT_RSTN_DR_POS               19
/// WF_RXFLT_RSTN_REG field bit
#define WLAN_RF_WF_RXFLT_RSTN_REG_BIT              ((uint32_t)0x00040000)
/// WF_RXFLT_RSTN_REG field position
#define WLAN_RF_WF_RXFLT_RSTN_REG_POS              18
/// WF_PU_ADC_DR field bit
#define WLAN_RF_WF_PU_ADC_DR_BIT                   ((uint32_t)0x00020000)
/// WF_PU_ADC_DR field position
#define WLAN_RF_WF_PU_ADC_DR_POS                   17
/// WF_PU_ADC_REG field bit
#define WLAN_RF_WF_PU_ADC_REG_BIT                  ((uint32_t)0x00010000)
/// WF_PU_ADC_REG field position
#define WLAN_RF_WF_PU_ADC_REG_POS                  16
/// WF_PU_ADC_VREG_COM_DR field bit
#define WLAN_RF_WF_PU_ADC_VREG_COM_DR_BIT          ((uint32_t)0x00008000)
/// WF_PU_ADC_VREG_COM_DR field position
#define WLAN_RF_WF_PU_ADC_VREG_COM_DR_POS          15
/// WF_PU_ADC_VREG_COM_REG field bit
#define WLAN_RF_WF_PU_ADC_VREG_COM_REG_BIT         ((uint32_t)0x00004000)
/// WF_PU_ADC_VREG_COM_REG field position
#define WLAN_RF_WF_PU_ADC_VREG_COM_REG_POS         14
/// WF_PU_PDADC_DR field bit
#define WLAN_RF_WF_PU_PDADC_DR_BIT                 ((uint32_t)0x00002000)
/// WF_PU_PDADC_DR field position
#define WLAN_RF_WF_PU_PDADC_DR_POS                 13
/// WF_PU_PDADC_REG field bit
#define WLAN_RF_WF_PU_PDADC_REG_BIT                ((uint32_t)0x00001000)
/// WF_PU_PDADC_REG field position
#define WLAN_RF_WF_PU_PDADC_REG_POS                12
/// WF_PU_RFPLL_DR field bit
#define WLAN_RF_WF_PU_RFPLL_DR_BIT                 ((uint32_t)0x00000800)
/// WF_PU_RFPLL_DR field position
#define WLAN_RF_WF_PU_RFPLL_DR_POS                 11
/// WF_PU_RFPLL_REG field bit
#define WLAN_RF_WF_PU_RFPLL_REG_BIT                ((uint32_t)0x00000400)
/// WF_PU_RFPLL_REG field position
#define WLAN_RF_WF_PU_RFPLL_REG_POS                10
/// WF_RFPLL_ADC_CLK_EN_DR field bit
#define WLAN_RF_WF_RFPLL_ADC_CLK_EN_DR_BIT         ((uint32_t)0x00000200)
/// WF_RFPLL_ADC_CLK_EN_DR field position
#define WLAN_RF_WF_RFPLL_ADC_CLK_EN_DR_POS         9
/// WF_RFPLL_ADC_CLK_EN_REG field bit
#define WLAN_RF_WF_RFPLL_ADC_CLK_EN_REG_BIT        ((uint32_t)0x00000100)
/// WF_RFPLL_ADC_CLK_EN_REG field position
#define WLAN_RF_WF_RFPLL_ADC_CLK_EN_REG_POS        8
/// WF_RFPLL_VCTRL_DET_EN_DR field bit
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_DR_BIT       ((uint32_t)0x00000080)
/// WF_RFPLL_VCTRL_DET_EN_DR field position
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_DR_POS       7
/// WF_RFPLL_VCTRL_DET_EN_REG field bit
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_REG_BIT      ((uint32_t)0x00000040)
/// WF_RFPLL_VCTRL_DET_EN_REG field position
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_REG_POS      6
/// WF_LOGEN_PHASE_MUX_RSTN_DR field bit
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_DR_BIT     ((uint32_t)0x00000020)
/// WF_LOGEN_PHASE_MUX_RSTN_DR field position
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_DR_POS     5
/// WF_LOGEN_PHASE_MUX_RSTN_REG field bit
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_REG_BIT    ((uint32_t)0x00000010)
/// WF_LOGEN_PHASE_MUX_RSTN_REG field position
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_REG_POS    4
/// WF_PU_VCO_DR field bit
#define WLAN_RF_WF_PU_VCO_DR_BIT                   ((uint32_t)0x00000008)
/// WF_PU_VCO_DR field position
#define WLAN_RF_WF_PU_VCO_DR_POS                   3
/// WF_PU_VCO_REG field bit
#define WLAN_RF_WF_PU_VCO_REG_BIT                  ((uint32_t)0x00000004)
/// WF_PU_VCO_REG field position
#define WLAN_RF_WF_PU_VCO_REG_POS                  2
/// WF_VCO_TXLO_EN_DR field bit
#define WLAN_RF_WF_VCO_TXLO_EN_DR_BIT              ((uint32_t)0x00000002)
/// WF_VCO_TXLO_EN_DR field position
#define WLAN_RF_WF_VCO_TXLO_EN_DR_POS              1
/// WF_VCO_TXLO_EN_REG field bit
#define WLAN_RF_WF_VCO_TXLO_EN_REG_BIT             ((uint32_t)0x00000001)
/// WF_VCO_TXLO_EN_REG field position
#define WLAN_RF_WF_VCO_TXLO_EN_REG_POS             0

/// WF_PU_DTMX_DR field reset value
#define WLAN_RF_WF_PU_DTMX_DR_RST                  0x0
/// WF_PU_DTMX_REG field reset value
#define WLAN_RF_WF_PU_DTMX_REG_RST                 0x0
/// WF_DTMX_BT_2WF_TX_EN_DR field reset value
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_DR_RST        0x0
/// WF_DTMX_BT_2WF_TX_EN_REG field reset value
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_REG_RST       0x0
/// WF_DTMX_LOGEN_DLL_RSTN_DR field reset value
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_DR_RST      0x0
/// WF_DTMX_LOGEN_DLL_RSTN_REG field reset value
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_REG_RST     0x0
/// WF_DTMX_CDR_RSTN_DR field reset value
#define WLAN_RF_WF_DTMX_CDR_RSTN_DR_RST            0x0
/// WF_DTMX_CDR_RSTN_REG field reset value
#define WLAN_RF_WF_DTMX_CDR_RSTN_REG_RST           0x0
/// WF_PU_IREF_DR field reset value
#define WLAN_RF_WF_PU_IREF_DR_RST                  0x0
/// WF_PU_IREF_REG field reset value
#define WLAN_RF_WF_PU_IREF_REG_RST                 0x0
/// WF_PU_RXFLT_DR field reset value
#define WLAN_RF_WF_PU_RXFLT_DR_RST                 0x0
/// WF_PU_RXFLT_REG field reset value
#define WLAN_RF_WF_PU_RXFLT_REG_RST                0x0
/// WF_RXFLT_RSTN_DR field reset value
#define WLAN_RF_WF_RXFLT_RSTN_DR_RST               0x0
/// WF_RXFLT_RSTN_REG field reset value
#define WLAN_RF_WF_RXFLT_RSTN_REG_RST              0x0
/// WF_PU_ADC_DR field reset value
#define WLAN_RF_WF_PU_ADC_DR_RST                   0x0
/// WF_PU_ADC_REG field reset value
#define WLAN_RF_WF_PU_ADC_REG_RST                  0x0
/// WF_PU_ADC_VREG_COM_DR field reset value
#define WLAN_RF_WF_PU_ADC_VREG_COM_DR_RST          0x0
/// WF_PU_ADC_VREG_COM_REG field reset value
#define WLAN_RF_WF_PU_ADC_VREG_COM_REG_RST         0x0
/// WF_PU_PDADC_DR field reset value
#define WLAN_RF_WF_PU_PDADC_DR_RST                 0x0
/// WF_PU_PDADC_REG field reset value
#define WLAN_RF_WF_PU_PDADC_REG_RST                0x0
/// WF_PU_RFPLL_DR field reset value
#define WLAN_RF_WF_PU_RFPLL_DR_RST                 0x0
/// WF_PU_RFPLL_REG field reset value
#define WLAN_RF_WF_PU_RFPLL_REG_RST                0x0
/// WF_RFPLL_ADC_CLK_EN_DR field reset value
#define WLAN_RF_WF_RFPLL_ADC_CLK_EN_DR_RST         0x0
/// WF_RFPLL_ADC_CLK_EN_REG field reset value
#define WLAN_RF_WF_RFPLL_ADC_CLK_EN_REG_RST        0x0
/// WF_RFPLL_VCTRL_DET_EN_DR field reset value
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_DR_RST       0x0
/// WF_RFPLL_VCTRL_DET_EN_REG field reset value
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_REG_RST      0x0
/// WF_LOGEN_PHASE_MUX_RSTN_DR field reset value
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_DR_RST     0x0
/// WF_LOGEN_PHASE_MUX_RSTN_REG field reset value
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_REG_RST    0x0
/// WF_PU_VCO_DR field reset value
#define WLAN_RF_WF_PU_VCO_DR_RST                   0x0
/// WF_PU_VCO_REG field reset value
#define WLAN_RF_WF_PU_VCO_REG_RST                  0x0
/// WF_VCO_TXLO_EN_DR field reset value
#define WLAN_RF_WF_VCO_TXLO_EN_DR_RST              0x0
/// WF_VCO_TXLO_EN_REG field reset value
#define WLAN_RF_WF_VCO_TXLO_EN_REG_RST             0x1

/**
 * @brief Constructs a value for the REG_04 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpudtmxdr - The value to use for the wf_pu_dtmx_dr field.
 * @param[in] wfpudtmxreg - The value to use for the wf_pu_dtmx_reg field.
 * @param[in] wfdtmxbt2wftxendr - The value to use for the wf_dtmx_bt2wf_tx_en_dr field.
 * @param[in] wfdtmxbt2wftxenreg - The value to use for the wf_dtmx_bt2wf_tx_en_reg field.
 * @param[in] wfdtmxlogendllrstndr - The value to use for the wf_dtmx_logen_dll_rstn_dr field.
 * @param[in] wfdtmxlogendllrstnreg - The value to use for the wf_dtmx_logen_dll_rstn_reg field.
 * @param[in] wfdtmxcdrrstndr - The value to use for the wf_dtmx_cdr_rstn_dr field.
 * @param[in] wfdtmxcdrrstnreg - The value to use for the wf_dtmx_cdr_rstn_reg field.
 * @param[in] wfpuirefdr - The value to use for the wf_pu_iref_dr field.
 * @param[in] wfpuirefreg - The value to use for the wf_pu_iref_reg field.
 * @param[in] wfpurxfltdr - The value to use for the wf_pu_rxflt_dr field.
 * @param[in] wfpurxfltreg - The value to use for the wf_pu_rxflt_reg field.
 * @param[in] wfrxfltrstndr - The value to use for the wf_rxflt_rstn_dr field.
 * @param[in] wfrxfltrstnreg - The value to use for the wf_rxflt_rstn_reg field.
 * @param[in] wfpuadcdr - The value to use for the wf_pu_adc_dr field.
 * @param[in] wfpuadcreg - The value to use for the wf_pu_adc_reg field.
 * @param[in] wfpuadcvregcomdr - The value to use for the wf_pu_adc_vreg_com_dr field.
 * @param[in] wfpuadcvregcomreg - The value to use for the wf_pu_adc_vreg_com_reg field.
 * @param[in] wfpupdadcdr - The value to use for the wf_pu_pdadc_dr field.
 * @param[in] wfpupdadcreg - The value to use for the wf_pu_pdadc_reg field.
 * @param[in] wfpurfplldr - The value to use for the wf_pu_rfpll_dr field.
 * @param[in] wfpurfpllreg - The value to use for the wf_pu_rfpll_reg field.
 * @param[in] wfrfplladcclkendr - The value to use for the wf_rfpll_adc_clk_en_dr field.
 * @param[in] wfrfplladcclkenreg - The value to use for the wf_rfpll_adc_clk_en_reg field.
 * @param[in] wfrfpllvctrldetendr - The value to use for the wf_rfpll_vctrl_det_en_dr field.
 * @param[in] wfrfpllvctrldetenreg - The value to use for the wf_rfpll_vctrl_det_en_reg field.
 * @param[in] wflogenphasemuxrstndr - The value to use for the wf_logen_phase_mux_rstn_dr field.
 * @param[in] wflogenphasemuxrstnreg - The value to use for the wf_logen_phase_mux_rstn_reg field.
 * @param[in] wfpuvcodr - The value to use for the wf_pu_vco_dr field.
 * @param[in] wfpuvcoreg - The value to use for the wf_pu_vco_reg field.
 * @param[in] wfvcotxloendr - The value to use for the wf_vco_txlo_en_dr field.
 * @param[in] wfvcotxloenreg - The value to use for the wf_vco_txlo_en_reg field.
 */
__INLINE void wlan_rf_reg_04_pack(uint8_t wfpudtmxdr, uint8_t wfpudtmxreg, uint8_t wfdtmxbt2wftxendr, uint8_t wfdtmxbt2wftxenreg, uint8_t wfdtmxlogendllrstndr, uint8_t wfdtmxlogendllrstnreg, uint8_t wfdtmxcdrrstndr, uint8_t wfdtmxcdrrstnreg, uint8_t wfpuirefdr, uint8_t wfpuirefreg, uint8_t wfpurxfltdr, uint8_t wfpurxfltreg, uint8_t wfrxfltrstndr, uint8_t wfrxfltrstnreg, uint8_t wfpuadcdr, uint8_t wfpuadcreg, uint8_t wfpuadcvregcomdr, uint8_t wfpuadcvregcomreg, uint8_t wfpupdadcdr, uint8_t wfpupdadcreg, uint8_t wfpurfplldr, uint8_t wfpurfpllreg, uint8_t wfrfplladcclkendr, uint8_t wfrfplladcclkenreg, uint8_t wfrfpllvctrldetendr, uint8_t wfrfpllvctrldetenreg, uint8_t wflogenphasemuxrstndr, uint8_t wflogenphasemuxrstnreg, uint8_t wfpuvcodr, uint8_t wfpuvcoreg, uint8_t wfvcotxloendr, uint8_t wfvcotxloenreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR,  ((uint32_t)wfpudtmxdr << 31) | ((uint32_t)wfpudtmxreg << 30) | ((uint32_t)wfdtmxbt2wftxendr << 29) | ((uint32_t)wfdtmxbt2wftxenreg << 28) | ((uint32_t)wfdtmxlogendllrstndr << 27) | ((uint32_t)wfdtmxlogendllrstnreg << 26) | ((uint32_t)wfdtmxcdrrstndr << 25) | ((uint32_t)wfdtmxcdrrstnreg << 24) | ((uint32_t)wfpuirefdr << 23) | ((uint32_t)wfpuirefreg << 22) | ((uint32_t)wfpurxfltdr << 21) | ((uint32_t)wfpurxfltreg << 20) | ((uint32_t)wfrxfltrstndr << 19) | ((uint32_t)wfrxfltrstnreg << 18) | ((uint32_t)wfpuadcdr << 17) | ((uint32_t)wfpuadcreg << 16) | ((uint32_t)wfpuadcvregcomdr << 15) | ((uint32_t)wfpuadcvregcomreg << 14) | ((uint32_t)wfpupdadcdr << 13) | ((uint32_t)wfpupdadcreg << 12) | ((uint32_t)wfpurfplldr << 11) | ((uint32_t)wfpurfpllreg << 10) | ((uint32_t)wfrfplladcclkendr << 9) | ((uint32_t)wfrfplladcclkenreg << 8) | ((uint32_t)wfrfpllvctrldetendr << 7) | ((uint32_t)wfrfpllvctrldetenreg << 6) | ((uint32_t)wflogenphasemuxrstndr << 5) | ((uint32_t)wflogenphasemuxrstnreg << 4) | ((uint32_t)wfpuvcodr << 3) | ((uint32_t)wfpuvcoreg << 2) | ((uint32_t)wfvcotxloendr << 1) | ((uint32_t)wfvcotxloenreg << 0));
}

/**
 * @brief Unpacks REG_04's fields from current value of the REG_04 register.
 *
 * Reads the REG_04 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpudtmxdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpudtmxreg - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxbt2wftxendr - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxbt2wftxenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogendllrstndr - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogendllrstnreg - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrrstndr - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrrstnreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpuirefdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpuirefreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpurxfltdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpurxfltreg - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltrstndr - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltrstnreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpuadcdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpuadcreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpuadcvregcomdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpuadcvregcomreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpupdadcdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpupdadcreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpurfplldr - Will be populated with the current value of this field from the register.
 * @param[out] wfpurfpllreg - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplladcclkendr - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplladcclkenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllvctrldetendr - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllvctrldetenreg - Will be populated with the current value of this field from the register.
 * @param[out] wflogenphasemuxrstndr - Will be populated with the current value of this field from the register.
 * @param[out] wflogenphasemuxrstnreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpuvcodr - Will be populated with the current value of this field from the register.
 * @param[out] wfpuvcoreg - Will be populated with the current value of this field from the register.
 * @param[out] wfvcotxloendr - Will be populated with the current value of this field from the register.
 * @param[out] wfvcotxloenreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_04_unpack(uint8_t* wfpudtmxdr, uint8_t* wfpudtmxreg, uint8_t* wfdtmxbt2wftxendr, uint8_t* wfdtmxbt2wftxenreg, uint8_t* wfdtmxlogendllrstndr, uint8_t* wfdtmxlogendllrstnreg, uint8_t* wfdtmxcdrrstndr, uint8_t* wfdtmxcdrrstnreg, uint8_t* wfpuirefdr, uint8_t* wfpuirefreg, uint8_t* wfpurxfltdr, uint8_t* wfpurxfltreg, uint8_t* wfrxfltrstndr, uint8_t* wfrxfltrstnreg, uint8_t* wfpuadcdr, uint8_t* wfpuadcreg, uint8_t* wfpuadcvregcomdr, uint8_t* wfpuadcvregcomreg, uint8_t* wfpupdadcdr, uint8_t* wfpupdadcreg, uint8_t* wfpurfplldr, uint8_t* wfpurfpllreg, uint8_t* wfrfplladcclkendr, uint8_t* wfrfplladcclkenreg, uint8_t* wfrfpllvctrldetendr, uint8_t* wfrfpllvctrldetenreg, uint8_t* wflogenphasemuxrstndr, uint8_t* wflogenphasemuxrstnreg, uint8_t* wfpuvcodr, uint8_t* wfpuvcoreg, uint8_t* wfvcotxloendr, uint8_t* wfvcotxloenreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);

    *wfpudtmxdr = (localVal & ((uint32_t)0x80000000)) >> 31;
    *wfpudtmxreg = (localVal & ((uint32_t)0x40000000)) >> 30;
    *wfdtmxbt2wftxendr = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wfdtmxbt2wftxenreg = (localVal & ((uint32_t)0x10000000)) >> 28;
    *wfdtmxlogendllrstndr = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfdtmxlogendllrstnreg = (localVal & ((uint32_t)0x04000000)) >> 26;
    *wfdtmxcdrrstndr = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wfdtmxcdrrstnreg = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wfpuirefdr = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfpuirefreg = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wfpurxfltdr = (localVal & ((uint32_t)0x00200000)) >> 21;
    *wfpurxfltreg = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wfrxfltrstndr = (localVal & ((uint32_t)0x00080000)) >> 19;
    *wfrxfltrstnreg = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfpuadcdr = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wfpuadcreg = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wfpuadcvregcomdr = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wfpuadcvregcomreg = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wfpupdadcdr = (localVal & ((uint32_t)0x00002000)) >> 13;
    *wfpupdadcreg = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wfpurfplldr = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wfpurfpllreg = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfrfplladcclkendr = (localVal & ((uint32_t)0x00000200)) >> 9;
    *wfrfplladcclkenreg = (localVal & ((uint32_t)0x00000100)) >> 8;
    *wfrfpllvctrldetendr = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wfrfpllvctrldetenreg = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wflogenphasemuxrstndr = (localVal & ((uint32_t)0x00000020)) >> 5;
    *wflogenphasemuxrstnreg = (localVal & ((uint32_t)0x00000010)) >> 4;
    *wfpuvcodr = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wfpuvcoreg = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wfvcotxloendr = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfvcotxloenreg = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pu_dtmx_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_dtmx_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_dtmx_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_dtmx_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the wf_pu_dtmx_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpudtmxdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_dtmx_dr_setf(uint8_t wfpudtmxdr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)wfpudtmxdr << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the wf_pu_dtmx_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_dtmx_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_dtmx_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_dtmx_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the wf_pu_dtmx_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpudtmxreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_dtmx_reg_setf(uint8_t wfpudtmxreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)wfpudtmxreg << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_bt2wf_tx_en_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_dtmx_bt2wf_tx_en_dr field's value will be returned.
 *
 * @return The current value of the wf_dtmx_bt2wf_tx_en_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_bt_2wf_tx_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the wf_dtmx_bt2wf_tx_en_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxbt2wftxendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_bt_2wf_tx_en_dr_setf(uint8_t wfdtmxbt2wftxendr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wfdtmxbt2wftxendr << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_bt2wf_tx_en_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_dtmx_bt2wf_tx_en_reg field's value will be returned.
 *
 * @return The current value of the wf_dtmx_bt2wf_tx_en_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_bt_2wf_tx_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the wf_dtmx_bt2wf_tx_en_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxbt2wftxenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_bt_2wf_tx_en_reg_setf(uint8_t wfdtmxbt2wftxenreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)wfdtmxbt2wftxenreg << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_dll_rstn_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_dtmx_logen_dll_rstn_dr field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_dll_rstn_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_dll_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_dtmx_logen_dll_rstn_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogendllrstndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_dll_rstn_dr_setf(uint8_t wfdtmxlogendllrstndr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wfdtmxlogendllrstndr << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_dll_rstn_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_dtmx_logen_dll_rstn_reg field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_dll_rstn_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_dll_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the wf_dtmx_logen_dll_rstn_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogendllrstnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_dll_rstn_reg_setf(uint8_t wfdtmxlogendllrstnreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)wfdtmxlogendllrstnreg << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_rstn_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_dtmx_cdr_rstn_dr field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_rstn_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_dtmx_cdr_rstn_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdrrstndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_rstn_dr_setf(uint8_t wfdtmxcdrrstndr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wfdtmxcdrrstndr << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_rstn_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_dtmx_cdr_rstn_reg field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_rstn_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the wf_dtmx_cdr_rstn_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdrrstnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_rstn_reg_setf(uint8_t wfdtmxcdrrstnreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wfdtmxcdrrstnreg << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the wf_pu_iref_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_iref_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_iref_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_iref_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_pu_iref_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuirefdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_iref_dr_setf(uint8_t wfpuirefdr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wfpuirefdr << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_pu_iref_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_iref_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_iref_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_iref_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the wf_pu_iref_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuirefreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_iref_reg_setf(uint8_t wfpuirefreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)wfpuirefreg << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the wf_pu_rxflt_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_rxflt_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_rxflt_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rxflt_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Sets the wf_pu_rxflt_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurxfltdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rxflt_dr_setf(uint8_t wfpurxfltdr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00200000)) | (((uint32_t)wfpurxfltdr << 21) & ((uint32_t)0x00200000)));
}

/**
 * @brief Returns the current value of the wf_pu_rxflt_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_rxflt_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_rxflt_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rxflt_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_pu_rxflt_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurxfltreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rxflt_reg_setf(uint8_t wfpurxfltreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wfpurxfltreg << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the wf_rxflt_rstn_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_rxflt_rstn_dr field's value will be returned.
 *
 * @return The current value of the wf_rxflt_rstn_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the wf_rxflt_rstn_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltrstndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_rstn_dr_setf(uint8_t wfrxfltrstndr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)wfrxfltrstndr << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the wf_rxflt_rstn_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_rxflt_rstn_reg field's value will be returned.
 *
 * @return The current value of the wf_rxflt_rstn_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_rxflt_rstn_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltrstnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_rstn_reg_setf(uint8_t wfrxfltrstnreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wfrxfltrstnreg << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_adc_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_pu_adc_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_dr_setf(uint8_t wfpuadcdr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wfpuadcdr << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_adc_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_pu_adc_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_reg_setf(uint8_t wfpuadcreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wfpuadcreg << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_vreg_com_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_adc_vreg_com_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_vreg_com_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_vreg_com_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the wf_pu_adc_vreg_com_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcvregcomdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_vreg_com_dr_setf(uint8_t wfpuadcvregcomdr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)wfpuadcvregcomdr << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_vreg_com_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_adc_vreg_com_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_vreg_com_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_vreg_com_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the wf_pu_adc_vreg_com_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcvregcomreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_vreg_com_reg_setf(uint8_t wfpuadcvregcomreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)wfpuadcvregcomreg << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the wf_pu_pdadc_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_pdadc_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_pdadc_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_pdadc_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the wf_pu_pdadc_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpupdadcdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_pdadc_dr_setf(uint8_t wfpupdadcdr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)wfpupdadcdr << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the wf_pu_pdadc_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_pdadc_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_pdadc_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_pdadc_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_pu_pdadc_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpupdadcreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_pdadc_reg_setf(uint8_t wfpupdadcreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wfpupdadcreg << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the wf_pu_rfpll_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_rfpll_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_rfpll_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rfpll_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_pu_rfpll_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurfplldr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rfpll_dr_setf(uint8_t wfpurfplldr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wfpurfplldr << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_pu_rfpll_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_rfpll_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_rfpll_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rfpll_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_pu_rfpll_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurfpllreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rfpll_reg_setf(uint8_t wfpurfpllreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfpurfpllreg << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_rfpll_adc_clk_en_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_rfpll_adc_clk_en_dr field's value will be returned.
 *
 * @return The current value of the wf_rfpll_adc_clk_en_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_adc_clk_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the wf_rfpll_adc_clk_en_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplladcclkendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_adc_clk_en_dr_setf(uint8_t wfrfplladcclkendr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)wfrfplladcclkendr << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the wf_rfpll_adc_clk_en_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_rfpll_adc_clk_en_reg field's value will be returned.
 *
 * @return The current value of the wf_rfpll_adc_clk_en_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_adc_clk_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the wf_rfpll_adc_clk_en_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplladcclkenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_adc_clk_en_reg_setf(uint8_t wfrfplladcclkenreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)wfrfplladcclkenreg << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the wf_rfpll_vctrl_det_en_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_rfpll_vctrl_det_en_dr field's value will be returned.
 *
 * @return The current value of the wf_rfpll_vctrl_det_en_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_vctrl_det_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_rfpll_vctrl_det_en_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllvctrldetendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_vctrl_det_en_dr_setf(uint8_t wfrfpllvctrldetendr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wfrfpllvctrldetendr << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_rfpll_vctrl_det_en_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_rfpll_vctrl_det_en_reg field's value will be returned.
 *
 * @return The current value of the wf_rfpll_vctrl_det_en_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_vctrl_det_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the wf_rfpll_vctrl_det_en_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllvctrldetenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_vctrl_det_en_reg_setf(uint8_t wfrfpllvctrldetenreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)wfrfpllvctrldetenreg << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the wf_logen_phase_mux_rstn_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_logen_phase_mux_rstn_dr field's value will be returned.
 *
 * @return The current value of the wf_logen_phase_mux_rstn_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_logen_phase_mux_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the wf_logen_phase_mux_rstn_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflogenphasemuxrstndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_logen_phase_mux_rstn_dr_setf(uint8_t wflogenphasemuxrstndr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)wflogenphasemuxrstndr << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the wf_logen_phase_mux_rstn_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_logen_phase_mux_rstn_reg field's value will be returned.
 *
 * @return The current value of the wf_logen_phase_mux_rstn_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_logen_phase_mux_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the wf_logen_phase_mux_rstn_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflogenphasemuxrstnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_logen_phase_mux_rstn_reg_setf(uint8_t wflogenphasemuxrstnreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)wflogenphasemuxrstnreg << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the wf_pu_vco_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_vco_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_vco_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_vco_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wf_pu_vco_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuvcodr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_vco_dr_setf(uint8_t wfpuvcodr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wfpuvcodr << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wf_pu_vco_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_pu_vco_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_vco_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_vco_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wf_pu_vco_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuvcoreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_vco_reg_setf(uint8_t wfpuvcoreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wfpuvcoreg << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wf_vco_txlo_en_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_vco_txlo_en_dr field's value will be returned.
 *
 * @return The current value of the wf_vco_txlo_en_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_txlo_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_vco_txlo_en_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcotxloendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_txlo_en_dr_setf(uint8_t wfvcotxloendr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfvcotxloendr << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_vco_txlo_en_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_vco_txlo_en_reg field's value will be returned.
 *
 * @return The current value of the wf_vco_txlo_en_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_txlo_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_vco_txlo_en_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcotxloenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_txlo_en_reg_setf(uint8_t wfvcotxloenreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfvcotxloenreg << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_08 register definitions
 * <table>
 * <caption id="REG_08_BF">REG_08 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td> wf_vco_rxlo_en_dr <td>R <td>R/W <td>0
 * <tr><td>30 <td>wf_vco_rxlo_en_reg <td>R <td>R/W <td>0
 * <tr><td>29 <td>   wf_pu_lo_psw_dr <td>R <td>R/W <td>0
 * <tr><td>28 <td>  wf_pu_lo_psw_reg <td>R <td>R/W <td>0
 * <tr><td>27 <td>      wf_pu_ts_hub <td>R <td>R/W <td>0
 * <tr><td>26 <td>wf_pu_vco_test_buf <td>R <td>R/W <td>0
 * <tr><td>25:24 <td>wf_lna5g_preamp_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>23:22 <td>     wf_lna_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>21:20 <td>     wf_rmx_pu_bit <td>R <td>R/W <td>0x3
 * <tr><td>19:18 <td>     wf_tia_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>17:16 <td>wf_dtmx_pu_bit_avdd33 <td>R <td>R/W <td>0x2
 * <tr><td>15:14 <td>wf_dtmx_pu_bit_avdd13 <td>R <td>R/W <td>0x2
 * <tr><td>13:12 <td>wf_dtmx_logen_pu_bit <td>R <td>R/W <td>0x2
 * <tr><td>11:10 <td>   wf_rxflt_pu_bit <td>R <td>R/W <td>0x2
 * <tr><td>09:08 <td>     wf_adc_pu_bit <td>R <td>R/W <td>0x2
 * <tr><td>07:06 <td>   wf_rfpll_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>05:04 <td>  wf_lo_psw_pu_bit <td>R <td>R/W <td>0x3
 * <tr><td>03 <td>  wf_dtmx_pll_test <td>R <td>R/W <td>0
 * <tr><td>02:00 <td>       wf_test_bit <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the REG_08 register
#define WLAN_RF_REG_08_ADDR   0x40344008
/// Offset of the REG_08 register from the base address
#define WLAN_RF_REG_08_OFFSET 0x00000008
/// Index of the REG_08 register
#define WLAN_RF_REG_08_INDEX  0x00000002
/// Reset value of the REG_08 register
#define WLAN_RF_REG_08_RESET  0x0176AA70

/**
 * @brief Returns the current value of the REG_08 register.
 * The REG_08 register will be read and its value returned.
 * @return The current value of the REG_08 register.
 */
__INLINE uint32_t wlan_rf_reg_08_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_08_ADDR);
}

/**
 * @brief Sets the REG_08 register to a value.
 * The REG_08 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_08_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, value);
}

// field definitions
/// WF_VCO_RXLO_EN_DR field bit
#define WLAN_RF_WF_VCO_RXLO_EN_DR_BIT          ((uint32_t)0x80000000)
/// WF_VCO_RXLO_EN_DR field position
#define WLAN_RF_WF_VCO_RXLO_EN_DR_POS          31
/// WF_VCO_RXLO_EN_REG field bit
#define WLAN_RF_WF_VCO_RXLO_EN_REG_BIT         ((uint32_t)0x40000000)
/// WF_VCO_RXLO_EN_REG field position
#define WLAN_RF_WF_VCO_RXLO_EN_REG_POS         30
/// WF_PU_LO_PSW_DR field bit
#define WLAN_RF_WF_PU_LO_PSW_DR_BIT            ((uint32_t)0x20000000)
/// WF_PU_LO_PSW_DR field position
#define WLAN_RF_WF_PU_LO_PSW_DR_POS            29
/// WF_PU_LO_PSW_REG field bit
#define WLAN_RF_WF_PU_LO_PSW_REG_BIT           ((uint32_t)0x10000000)
/// WF_PU_LO_PSW_REG field position
#define WLAN_RF_WF_PU_LO_PSW_REG_POS           28
/// WF_PU_TS_HUB field bit
#define WLAN_RF_WF_PU_TS_HUB_BIT               ((uint32_t)0x08000000)
/// WF_PU_TS_HUB field position
#define WLAN_RF_WF_PU_TS_HUB_POS               27
/// WF_PU_VCO_TEST_BUF field bit
#define WLAN_RF_WF_PU_VCO_TEST_BUF_BIT         ((uint32_t)0x04000000)
/// WF_PU_VCO_TEST_BUF field position
#define WLAN_RF_WF_PU_VCO_TEST_BUF_POS         26
/// WF_LNA_5G_PREAMP_PU_BIT field mask
#define WLAN_RF_WF_LNA_5G_PREAMP_PU_BIT_MASK   ((uint32_t)0x03000000)
/// WF_LNA_5G_PREAMP_PU_BIT field LSB position
#define WLAN_RF_WF_LNA_5G_PREAMP_PU_BIT_LSB    24
/// WF_LNA_5G_PREAMP_PU_BIT field width
#define WLAN_RF_WF_LNA_5G_PREAMP_PU_BIT_WIDTH  ((uint32_t)0x00000002)
/// WF_LNA_PU_BIT field mask
#define WLAN_RF_WF_LNA_PU_BIT_MASK             ((uint32_t)0x00C00000)
/// WF_LNA_PU_BIT field LSB position
#define WLAN_RF_WF_LNA_PU_BIT_LSB              22
/// WF_LNA_PU_BIT field width
#define WLAN_RF_WF_LNA_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// WF_RMX_PU_BIT field mask
#define WLAN_RF_WF_RMX_PU_BIT_MASK             ((uint32_t)0x00300000)
/// WF_RMX_PU_BIT field LSB position
#define WLAN_RF_WF_RMX_PU_BIT_LSB              20
/// WF_RMX_PU_BIT field width
#define WLAN_RF_WF_RMX_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// WF_TIA_PU_BIT field mask
#define WLAN_RF_WF_TIA_PU_BIT_MASK             ((uint32_t)0x000C0000)
/// WF_TIA_PU_BIT field LSB position
#define WLAN_RF_WF_TIA_PU_BIT_LSB              18
/// WF_TIA_PU_BIT field width
#define WLAN_RF_WF_TIA_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// WF_DTMX_PU_BIT_AVDD_33 field mask
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_33_MASK    ((uint32_t)0x00030000)
/// WF_DTMX_PU_BIT_AVDD_33 field LSB position
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_33_LSB     16
/// WF_DTMX_PU_BIT_AVDD_33 field width
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_33_WIDTH   ((uint32_t)0x00000002)
/// WF_DTMX_PU_BIT_AVDD_13 field mask
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_13_MASK    ((uint32_t)0x0000C000)
/// WF_DTMX_PU_BIT_AVDD_13 field LSB position
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_13_LSB     14
/// WF_DTMX_PU_BIT_AVDD_13 field width
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_13_WIDTH   ((uint32_t)0x00000002)
/// WF_DTMX_LOGEN_PU_BIT field mask
#define WLAN_RF_WF_DTMX_LOGEN_PU_BIT_MASK      ((uint32_t)0x00003000)
/// WF_DTMX_LOGEN_PU_BIT field LSB position
#define WLAN_RF_WF_DTMX_LOGEN_PU_BIT_LSB       12
/// WF_DTMX_LOGEN_PU_BIT field width
#define WLAN_RF_WF_DTMX_LOGEN_PU_BIT_WIDTH     ((uint32_t)0x00000002)
/// WF_RXFLT_PU_BIT field mask
#define WLAN_RF_WF_RXFLT_PU_BIT_MASK           ((uint32_t)0x00000C00)
/// WF_RXFLT_PU_BIT field LSB position
#define WLAN_RF_WF_RXFLT_PU_BIT_LSB            10
/// WF_RXFLT_PU_BIT field width
#define WLAN_RF_WF_RXFLT_PU_BIT_WIDTH          ((uint32_t)0x00000002)
/// WF_ADC_PU_BIT field mask
#define WLAN_RF_WF_ADC_PU_BIT_MASK             ((uint32_t)0x00000300)
/// WF_ADC_PU_BIT field LSB position
#define WLAN_RF_WF_ADC_PU_BIT_LSB              8
/// WF_ADC_PU_BIT field width
#define WLAN_RF_WF_ADC_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// WF_RFPLL_PU_BIT field mask
#define WLAN_RF_WF_RFPLL_PU_BIT_MASK           ((uint32_t)0x000000C0)
/// WF_RFPLL_PU_BIT field LSB position
#define WLAN_RF_WF_RFPLL_PU_BIT_LSB            6
/// WF_RFPLL_PU_BIT field width
#define WLAN_RF_WF_RFPLL_PU_BIT_WIDTH          ((uint32_t)0x00000002)
/// WF_LO_PSW_PU_BIT field mask
#define WLAN_RF_WF_LO_PSW_PU_BIT_MASK          ((uint32_t)0x00000030)
/// WF_LO_PSW_PU_BIT field LSB position
#define WLAN_RF_WF_LO_PSW_PU_BIT_LSB           4
/// WF_LO_PSW_PU_BIT field width
#define WLAN_RF_WF_LO_PSW_PU_BIT_WIDTH         ((uint32_t)0x00000002)
/// WF_DTMX_PLL_TEST field bit
#define WLAN_RF_WF_DTMX_PLL_TEST_BIT           ((uint32_t)0x00000008)
/// WF_DTMX_PLL_TEST field position
#define WLAN_RF_WF_DTMX_PLL_TEST_POS           3
/// WF_TEST_BIT field mask
#define WLAN_RF_WF_TEST_BIT_MASK               ((uint32_t)0x00000007)
/// WF_TEST_BIT field LSB position
#define WLAN_RF_WF_TEST_BIT_LSB                0
/// WF_TEST_BIT field width
#define WLAN_RF_WF_TEST_BIT_WIDTH              ((uint32_t)0x00000003)

/// WF_VCO_RXLO_EN_DR field reset value
#define WLAN_RF_WF_VCO_RXLO_EN_DR_RST          0x0
/// WF_VCO_RXLO_EN_REG field reset value
#define WLAN_RF_WF_VCO_RXLO_EN_REG_RST         0x0
/// WF_PU_LO_PSW_DR field reset value
#define WLAN_RF_WF_PU_LO_PSW_DR_RST            0x0
/// WF_PU_LO_PSW_REG field reset value
#define WLAN_RF_WF_PU_LO_PSW_REG_RST           0x0
/// WF_PU_TS_HUB field reset value
#define WLAN_RF_WF_PU_TS_HUB_RST               0x0
/// WF_PU_VCO_TEST_BUF field reset value
#define WLAN_RF_WF_PU_VCO_TEST_BUF_RST         0x0
/// WF_LNA_5G_PREAMP_PU_BIT field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_PU_BIT_RST    0x1
/// WF_LNA_PU_BIT field reset value
#define WLAN_RF_WF_LNA_PU_BIT_RST              0x1
/// WF_RMX_PU_BIT field reset value
#define WLAN_RF_WF_RMX_PU_BIT_RST              0x3
/// WF_TIA_PU_BIT field reset value
#define WLAN_RF_WF_TIA_PU_BIT_RST              0x1
/// WF_DTMX_PU_BIT_AVDD_33 field reset value
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_33_RST     0x2
/// WF_DTMX_PU_BIT_AVDD_13 field reset value
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_13_RST     0x2
/// WF_DTMX_LOGEN_PU_BIT field reset value
#define WLAN_RF_WF_DTMX_LOGEN_PU_BIT_RST       0x2
/// WF_RXFLT_PU_BIT field reset value
#define WLAN_RF_WF_RXFLT_PU_BIT_RST            0x2
/// WF_ADC_PU_BIT field reset value
#define WLAN_RF_WF_ADC_PU_BIT_RST              0x2
/// WF_RFPLL_PU_BIT field reset value
#define WLAN_RF_WF_RFPLL_PU_BIT_RST            0x1
/// WF_LO_PSW_PU_BIT field reset value
#define WLAN_RF_WF_LO_PSW_PU_BIT_RST           0x3
/// WF_DTMX_PLL_TEST field reset value
#define WLAN_RF_WF_DTMX_PLL_TEST_RST           0x0
/// WF_TEST_BIT field reset value
#define WLAN_RF_WF_TEST_BIT_RST                0x0

/**
 * @brief Constructs a value for the REG_08 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfvcorxloendr - The value to use for the wf_vco_rxlo_en_dr field.
 * @param[in] wfvcorxloenreg - The value to use for the wf_vco_rxlo_en_reg field.
 * @param[in] wfpulopswdr - The value to use for the wf_pu_lo_psw_dr field.
 * @param[in] wfpulopswreg - The value to use for the wf_pu_lo_psw_reg field.
 * @param[in] wfputshub - The value to use for the wf_pu_ts_hub field.
 * @param[in] wfpuvcotestbuf - The value to use for the wf_pu_vco_test_buf field.
 * @param[in] wflna5gpreamppubit - The value to use for the wf_lna5g_preamp_pu_bit field.
 * @param[in] wflnapubit - The value to use for the wf_lna_pu_bit field.
 * @param[in] wfrmxpubit - The value to use for the wf_rmx_pu_bit field.
 * @param[in] wftiapubit - The value to use for the wf_tia_pu_bit field.
 * @param[in] wfdtmxpubitavdd33 - The value to use for the wf_dtmx_pu_bit_avdd33 field.
 * @param[in] wfdtmxpubitavdd13 - The value to use for the wf_dtmx_pu_bit_avdd13 field.
 * @param[in] wfdtmxlogenpubit - The value to use for the wf_dtmx_logen_pu_bit field.
 * @param[in] wfrxfltpubit - The value to use for the wf_rxflt_pu_bit field.
 * @param[in] wfadcpubit - The value to use for the wf_adc_pu_bit field.
 * @param[in] wfrfpllpubit - The value to use for the wf_rfpll_pu_bit field.
 * @param[in] wflopswpubit - The value to use for the wf_lo_psw_pu_bit field.
 * @param[in] wfdtmxplltest - The value to use for the wf_dtmx_pll_test field.
 * @param[in] wftestbit - The value to use for the wf_test_bit field.
 */
__INLINE void wlan_rf_reg_08_pack(uint8_t wfvcorxloendr, uint8_t wfvcorxloenreg, uint8_t wfpulopswdr, uint8_t wfpulopswreg, uint8_t wfputshub, uint8_t wfpuvcotestbuf, uint8_t wflna5gpreamppubit, uint8_t wflnapubit, uint8_t wfrmxpubit, uint8_t wftiapubit, uint8_t wfdtmxpubitavdd33, uint8_t wfdtmxpubitavdd13, uint8_t wfdtmxlogenpubit, uint8_t wfrxfltpubit, uint8_t wfadcpubit, uint8_t wfrfpllpubit, uint8_t wflopswpubit, uint8_t wfdtmxplltest, uint8_t wftestbit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR,  ((uint32_t)wfvcorxloendr << 31) | ((uint32_t)wfvcorxloenreg << 30) | ((uint32_t)wfpulopswdr << 29) | ((uint32_t)wfpulopswreg << 28) | ((uint32_t)wfputshub << 27) | ((uint32_t)wfpuvcotestbuf << 26) | ((uint32_t)wflna5gpreamppubit << 24) | ((uint32_t)wflnapubit << 22) | ((uint32_t)wfrmxpubit << 20) | ((uint32_t)wftiapubit << 18) | ((uint32_t)wfdtmxpubitavdd33 << 16) | ((uint32_t)wfdtmxpubitavdd13 << 14) | ((uint32_t)wfdtmxlogenpubit << 12) | ((uint32_t)wfrxfltpubit << 10) | ((uint32_t)wfadcpubit << 8) | ((uint32_t)wfrfpllpubit << 6) | ((uint32_t)wflopswpubit << 4) | ((uint32_t)wfdtmxplltest << 3) | ((uint32_t)wftestbit << 0));
}

/**
 * @brief Unpacks REG_08's fields from current value of the REG_08 register.
 *
 * Reads the REG_08 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfvcorxloendr - Will be populated with the current value of this field from the register.
 * @param[out] wfvcorxloenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpulopswdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpulopswreg - Will be populated with the current value of this field from the register.
 * @param[out] wfputshub - Will be populated with the current value of this field from the register.
 * @param[out] wfpuvcotestbuf - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gpreamppubit - Will be populated with the current value of this field from the register.
 * @param[out] wflnapubit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxpubit - Will be populated with the current value of this field from the register.
 * @param[out] wftiapubit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxpubitavdd33 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxpubitavdd13 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogenpubit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltpubit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcpubit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllpubit - Will be populated with the current value of this field from the register.
 * @param[out] wflopswpubit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxplltest - Will be populated with the current value of this field from the register.
 * @param[out] wftestbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_08_unpack(uint8_t* wfvcorxloendr, uint8_t* wfvcorxloenreg, uint8_t* wfpulopswdr, uint8_t* wfpulopswreg, uint8_t* wfputshub, uint8_t* wfpuvcotestbuf, uint8_t* wflna5gpreamppubit, uint8_t* wflnapubit, uint8_t* wfrmxpubit, uint8_t* wftiapubit, uint8_t* wfdtmxpubitavdd33, uint8_t* wfdtmxpubitavdd13, uint8_t* wfdtmxlogenpubit, uint8_t* wfrxfltpubit, uint8_t* wfadcpubit, uint8_t* wfrfpllpubit, uint8_t* wflopswpubit, uint8_t* wfdtmxplltest, uint8_t* wftestbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);

    *wfvcorxloendr = (localVal & ((uint32_t)0x80000000)) >> 31;
    *wfvcorxloenreg = (localVal & ((uint32_t)0x40000000)) >> 30;
    *wfpulopswdr = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wfpulopswreg = (localVal & ((uint32_t)0x10000000)) >> 28;
    *wfputshub = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfpuvcotestbuf = (localVal & ((uint32_t)0x04000000)) >> 26;
    *wflna5gpreamppubit = (localVal & ((uint32_t)0x03000000)) >> 24;
    *wflnapubit = (localVal & ((uint32_t)0x00C00000)) >> 22;
    *wfrmxpubit = (localVal & ((uint32_t)0x00300000)) >> 20;
    *wftiapubit = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *wfdtmxpubitavdd33 = (localVal & ((uint32_t)0x00030000)) >> 16;
    *wfdtmxpubitavdd13 = (localVal & ((uint32_t)0x0000C000)) >> 14;
    *wfdtmxlogenpubit = (localVal & ((uint32_t)0x00003000)) >> 12;
    *wfrxfltpubit = (localVal & ((uint32_t)0x00000C00)) >> 10;
    *wfadcpubit = (localVal & ((uint32_t)0x00000300)) >> 8;
    *wfrfpllpubit = (localVal & ((uint32_t)0x000000C0)) >> 6;
    *wflopswpubit = (localVal & ((uint32_t)0x00000030)) >> 4;
    *wfdtmxplltest = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wftestbit = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the wf_vco_rxlo_en_dr field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_vco_rxlo_en_dr field's value will be returned.
 *
 * @return The current value of the wf_vco_rxlo_en_dr field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_rxlo_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the wf_vco_rxlo_en_dr field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcorxloendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_rxlo_en_dr_setf(uint8_t wfvcorxloendr)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)wfvcorxloendr << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the wf_vco_rxlo_en_reg field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_vco_rxlo_en_reg field's value will be returned.
 *
 * @return The current value of the wf_vco_rxlo_en_reg field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_rxlo_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the wf_vco_rxlo_en_reg field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcorxloenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_rxlo_en_reg_setf(uint8_t wfvcorxloenreg)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)wfvcorxloenreg << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the wf_pu_lo_psw_dr field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pu_lo_psw_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_lo_psw_dr field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_lo_psw_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the wf_pu_lo_psw_dr field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpulopswdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_lo_psw_dr_setf(uint8_t wfpulopswdr)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wfpulopswdr << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the wf_pu_lo_psw_reg field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pu_lo_psw_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_lo_psw_reg field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_lo_psw_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the wf_pu_lo_psw_reg field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpulopswreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_lo_psw_reg_setf(uint8_t wfpulopswreg)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)wfpulopswreg << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the wf_pu_ts_hub field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pu_ts_hub field's value will be returned.
 *
 * @return The current value of the wf_pu_ts_hub field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_ts_hub_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_pu_ts_hub field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputshub - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_ts_hub_setf(uint8_t wfputshub)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wfputshub << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_pu_vco_test_buf field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pu_vco_test_buf field's value will be returned.
 *
 * @return The current value of the wf_pu_vco_test_buf field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_vco_test_buf_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the wf_pu_vco_test_buf field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuvcotestbuf - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_vco_test_buf_setf(uint8_t wfpuvcotestbuf)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)wfpuvcotestbuf << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_pu_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_lna5g_preamp_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_pu_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

/**
 * @brief Sets the wf_lna5g_preamp_pu_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflna5gpreamppubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_5g_preamp_pu_bit_setf(uint8_t wflna5gpreamppubit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x03000000)) | (((uint32_t)wflna5gpreamppubit << 24) & ((uint32_t)0x03000000)));
}

/**
 * @brief Returns the current value of the wf_lna_pu_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_lna_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_lna_pu_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00C00000)) >> 22);
}

/**
 * @brief Sets the wf_lna_pu_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnapubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_pu_bit_setf(uint8_t wflnapubit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00C00000)) | (((uint32_t)wflnapubit << 22) & ((uint32_t)0x00C00000)));
}

/**
 * @brief Returns the current value of the wf_rmx_pu_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_rmx_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_rmx_pu_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

/**
 * @brief Sets the wf_rmx_pu_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_pu_bit_setf(uint8_t wfrmxpubit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00300000)) | (((uint32_t)wfrmxpubit << 20) & ((uint32_t)0x00300000)));
}

/**
 * @brief Returns the current value of the wf_tia_pu_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_tia_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_tia_pu_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the wf_tia_pu_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiapubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_pu_bit_setf(uint8_t wftiapubit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)wftiapubit << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_pu_bit_avdd33 field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_dtmx_pu_bit_avdd33 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_pu_bit_avdd33 field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_pu_bit_avdd_33_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

/**
 * @brief Sets the wf_dtmx_pu_bit_avdd33 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxpubitavdd33 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_pu_bit_avdd_33_setf(uint8_t wfdtmxpubitavdd33)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00030000)) | (((uint32_t)wfdtmxpubitavdd33 << 16) & ((uint32_t)0x00030000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_pu_bit_avdd13 field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_dtmx_pu_bit_avdd13 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_pu_bit_avdd13 field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_pu_bit_avdd_13_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x0000C000)) >> 14);
}

/**
 * @brief Sets the wf_dtmx_pu_bit_avdd13 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxpubitavdd13 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_pu_bit_avdd_13_setf(uint8_t wfdtmxpubitavdd13)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x0000C000)) | (((uint32_t)wfdtmxpubitavdd13 << 14) & ((uint32_t)0x0000C000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_pu_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_dtmx_logen_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_pu_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

/**
 * @brief Sets the wf_dtmx_logen_pu_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogenpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_pu_bit_setf(uint8_t wfdtmxlogenpubit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00003000)) | (((uint32_t)wfdtmxlogenpubit << 12) & ((uint32_t)0x00003000)));
}

/**
 * @brief Returns the current value of the wf_rxflt_pu_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_rxflt_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_pu_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000C00)) >> 10);
}

/**
 * @brief Sets the wf_rxflt_pu_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_pu_bit_setf(uint8_t wfrxfltpubit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00000C00)) | (((uint32_t)wfrxfltpubit << 10) & ((uint32_t)0x00000C00)));
}

/**
 * @brief Returns the current value of the wf_adc_pu_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_adc_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_adc_pu_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the wf_adc_pu_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_pu_bit_setf(uint8_t wfadcpubit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)wfadcpubit << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the wf_rfpll_pu_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_rfpll_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_pu_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x000000C0)) >> 6);
}

/**
 * @brief Sets the wf_rfpll_pu_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_pu_bit_setf(uint8_t wfrfpllpubit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x000000C0)) | (((uint32_t)wfrfpllpubit << 6) & ((uint32_t)0x000000C0)));
}

/**
 * @brief Returns the current value of the wf_lo_psw_pu_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_lo_psw_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_lo_psw_pu_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_lo_psw_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

/**
 * @brief Sets the wf_lo_psw_pu_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflopswpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lo_psw_pu_bit_setf(uint8_t wflopswpubit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00000030)) | (((uint32_t)wflopswpubit << 4) & ((uint32_t)0x00000030)));
}

/**
 * @brief Returns the current value of the wf_dtmx_pll_test field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_dtmx_pll_test field's value will be returned.
 *
 * @return The current value of the wf_dtmx_pll_test field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_pll_test_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wf_dtmx_pll_test field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxplltest - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_pll_test_setf(uint8_t wfdtmxplltest)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wfdtmxplltest << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wf_test_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_test_bit field's value will be returned.
 *
 * @return The current value of the wf_test_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_test_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/**
 * @brief Sets the wf_test_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_bit_setf(uint8_t wftestbit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00000007)) | (((uint32_t)wftestbit << 0) & ((uint32_t)0x00000007)));
}

/// @}

/**
 * @name REG_0C register definitions
 * <table>
 * <caption id="REG_0C_BF">REG_0C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30 <td>wf_test_enable_lna5g_preamp <td>R <td>R/W <td>0
 * <tr><td>29 <td>wf_test_enable_lna <td>R <td>R/W <td>0
 * <tr><td>28 <td>wf_test_enable_rmx <td>R <td>R/W <td>0
 * <tr><td>27:26 <td>wf_test_enable_tia <td>R <td>R/W <td>0x0
 * <tr><td>25 <td> wf_test_enable_pa <td>R <td>R/W <td>0
 * <tr><td>24 <td>wf_test_enable_dtmx <td>R <td>R/W <td>0
 * <tr><td>23 <td>wf_test_enable_iref <td>R <td>R/W <td>0
 * <tr><td>22 <td>wf_rxflt_test2gpio_en <td>R <td>R/W <td>0
 * <tr><td>21:20 <td>wf_test_enable_rxflt <td>R <td>R/W <td>0x0
 * <tr><td>19 <td>wf_test_enable_adc <td>R <td>R/W <td>0
 * <tr><td>18 <td>wf_test_enable_ts_hub <td>R <td>R/W <td>0
 * <tr><td>17 <td>wf_vco_test_buf_en <td>R <td>R/W <td>0
 * <tr><td>16 <td>wf_test_enable_rfpll <td>R <td>R/W <td>0
 * <tr><td>15 <td>wf_test_enable_vco <td>R <td>R/W <td>0
 * <tr><td>14:13 <td>  wf_pu_lo_psw_td2 <td>R <td>R/W <td>0x1
 * <tr><td>12:11 <td>     wf_pu_vco_td2 <td>R <td>R/W <td>0x1
 * <tr><td>10:08 <td>   wf_pu_rfpll_td3 <td>R <td>R/W <td>0x5
 * <tr><td>07:06 <td>     wf_pu_rmx_td1 <td>R <td>R/W <td>0x1
 * <tr><td>05:04 <td>wf_logen_phase_mux_rstn_td4 <td>R <td>R/W <td>0x2
 * <tr><td>03:02 <td>wf_rmx_logen_dll_rstn_td4 <td>R <td>R/W <td>0x1
 * <tr><td>01:00 <td>     wf_pu_tia_td1 <td>R <td>R/W <td>0x1
 * </table>
 *
 * @{
 */

/// Address of the REG_0C register
#define WLAN_RF_REG_0C_ADDR   0x4034400C
/// Offset of the REG_0C register from the base address
#define WLAN_RF_REG_0C_OFFSET 0x0000000C
/// Index of the REG_0C register
#define WLAN_RF_REG_0C_INDEX  0x00000003
/// Reset value of the REG_0C register
#define WLAN_RF_REG_0C_RESET  0x00002D65

/**
 * @brief Returns the current value of the REG_0C register.
 * The REG_0C register will be read and its value returned.
 * @return The current value of the REG_0C register.
 */
__INLINE uint32_t wlan_rf_reg_0c_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_0C_ADDR);
}

/**
 * @brief Sets the REG_0C register to a value.
 * The REG_0C register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_0c_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, value);
}

// field definitions
/// WF_TEST_ENABLE_LNA_5G_PREAMP field bit
#define WLAN_RF_WF_TEST_ENABLE_LNA_5G_PREAMP_BIT    ((uint32_t)0x40000000)
/// WF_TEST_ENABLE_LNA_5G_PREAMP field position
#define WLAN_RF_WF_TEST_ENABLE_LNA_5G_PREAMP_POS    30
/// WF_TEST_ENABLE_LNA field bit
#define WLAN_RF_WF_TEST_ENABLE_LNA_BIT              ((uint32_t)0x20000000)
/// WF_TEST_ENABLE_LNA field position
#define WLAN_RF_WF_TEST_ENABLE_LNA_POS              29
/// WF_TEST_ENABLE_RMX field bit
#define WLAN_RF_WF_TEST_ENABLE_RMX_BIT              ((uint32_t)0x10000000)
/// WF_TEST_ENABLE_RMX field position
#define WLAN_RF_WF_TEST_ENABLE_RMX_POS              28
/// WF_TEST_ENABLE_TIA field mask
#define WLAN_RF_WF_TEST_ENABLE_TIA_MASK             ((uint32_t)0x0C000000)
/// WF_TEST_ENABLE_TIA field LSB position
#define WLAN_RF_WF_TEST_ENABLE_TIA_LSB              26
/// WF_TEST_ENABLE_TIA field width
#define WLAN_RF_WF_TEST_ENABLE_TIA_WIDTH            ((uint32_t)0x00000002)
/// WF_TEST_ENABLE_PA field bit
#define WLAN_RF_WF_TEST_ENABLE_PA_BIT               ((uint32_t)0x02000000)
/// WF_TEST_ENABLE_PA field position
#define WLAN_RF_WF_TEST_ENABLE_PA_POS               25
/// WF_TEST_ENABLE_DTMX field bit
#define WLAN_RF_WF_TEST_ENABLE_DTMX_BIT             ((uint32_t)0x01000000)
/// WF_TEST_ENABLE_DTMX field position
#define WLAN_RF_WF_TEST_ENABLE_DTMX_POS             24
/// WF_TEST_ENABLE_IREF field bit
#define WLAN_RF_WF_TEST_ENABLE_IREF_BIT             ((uint32_t)0x00800000)
/// WF_TEST_ENABLE_IREF field position
#define WLAN_RF_WF_TEST_ENABLE_IREF_POS             23
/// WF_RXFLT_TEST_2GPIO_EN field bit
#define WLAN_RF_WF_RXFLT_TEST_2GPIO_EN_BIT          ((uint32_t)0x00400000)
/// WF_RXFLT_TEST_2GPIO_EN field position
#define WLAN_RF_WF_RXFLT_TEST_2GPIO_EN_POS          22
/// WF_TEST_ENABLE_RXFLT field mask
#define WLAN_RF_WF_TEST_ENABLE_RXFLT_MASK           ((uint32_t)0x00300000)
/// WF_TEST_ENABLE_RXFLT field LSB position
#define WLAN_RF_WF_TEST_ENABLE_RXFLT_LSB            20
/// WF_TEST_ENABLE_RXFLT field width
#define WLAN_RF_WF_TEST_ENABLE_RXFLT_WIDTH          ((uint32_t)0x00000002)
/// WF_TEST_ENABLE_ADC field bit
#define WLAN_RF_WF_TEST_ENABLE_ADC_BIT              ((uint32_t)0x00080000)
/// WF_TEST_ENABLE_ADC field position
#define WLAN_RF_WF_TEST_ENABLE_ADC_POS              19
/// WF_TEST_ENABLE_TS_HUB field bit
#define WLAN_RF_WF_TEST_ENABLE_TS_HUB_BIT           ((uint32_t)0x00040000)
/// WF_TEST_ENABLE_TS_HUB field position
#define WLAN_RF_WF_TEST_ENABLE_TS_HUB_POS           18
/// WF_VCO_TEST_BUF_EN field bit
#define WLAN_RF_WF_VCO_TEST_BUF_EN_BIT              ((uint32_t)0x00020000)
/// WF_VCO_TEST_BUF_EN field position
#define WLAN_RF_WF_VCO_TEST_BUF_EN_POS              17
/// WF_TEST_ENABLE_RFPLL field bit
#define WLAN_RF_WF_TEST_ENABLE_RFPLL_BIT            ((uint32_t)0x00010000)
/// WF_TEST_ENABLE_RFPLL field position
#define WLAN_RF_WF_TEST_ENABLE_RFPLL_POS            16
/// WF_TEST_ENABLE_VCO field bit
#define WLAN_RF_WF_TEST_ENABLE_VCO_BIT              ((uint32_t)0x00008000)
/// WF_TEST_ENABLE_VCO field position
#define WLAN_RF_WF_TEST_ENABLE_VCO_POS              15
/// WF_PU_LO_PSW_TD_2 field mask
#define WLAN_RF_WF_PU_LO_PSW_TD_2_MASK              ((uint32_t)0x00006000)
/// WF_PU_LO_PSW_TD_2 field LSB position
#define WLAN_RF_WF_PU_LO_PSW_TD_2_LSB               13
/// WF_PU_LO_PSW_TD_2 field width
#define WLAN_RF_WF_PU_LO_PSW_TD_2_WIDTH             ((uint32_t)0x00000002)
/// WF_PU_VCO_TD_2 field mask
#define WLAN_RF_WF_PU_VCO_TD_2_MASK                 ((uint32_t)0x00001800)
/// WF_PU_VCO_TD_2 field LSB position
#define WLAN_RF_WF_PU_VCO_TD_2_LSB                  11
/// WF_PU_VCO_TD_2 field width
#define WLAN_RF_WF_PU_VCO_TD_2_WIDTH                ((uint32_t)0x00000002)
/// WF_PU_RFPLL_TD_3 field mask
#define WLAN_RF_WF_PU_RFPLL_TD_3_MASK               ((uint32_t)0x00000700)
/// WF_PU_RFPLL_TD_3 field LSB position
#define WLAN_RF_WF_PU_RFPLL_TD_3_LSB                8
/// WF_PU_RFPLL_TD_3 field width
#define WLAN_RF_WF_PU_RFPLL_TD_3_WIDTH              ((uint32_t)0x00000003)
/// WF_PU_RMX_TD_1 field mask
#define WLAN_RF_WF_PU_RMX_TD_1_MASK                 ((uint32_t)0x000000C0)
/// WF_PU_RMX_TD_1 field LSB position
#define WLAN_RF_WF_PU_RMX_TD_1_LSB                  6
/// WF_PU_RMX_TD_1 field width
#define WLAN_RF_WF_PU_RMX_TD_1_WIDTH                ((uint32_t)0x00000002)
/// WF_LOGEN_PHASE_MUX_RSTN_TD_4 field mask
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_TD_4_MASK   ((uint32_t)0x00000030)
/// WF_LOGEN_PHASE_MUX_RSTN_TD_4 field LSB position
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_TD_4_LSB    4
/// WF_LOGEN_PHASE_MUX_RSTN_TD_4 field width
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_TD_4_WIDTH  ((uint32_t)0x00000002)
/// WF_RMX_LOGEN_DLL_RSTN_TD_4 field mask
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_TD_4_MASK     ((uint32_t)0x0000000C)
/// WF_RMX_LOGEN_DLL_RSTN_TD_4 field LSB position
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_TD_4_LSB      2
/// WF_RMX_LOGEN_DLL_RSTN_TD_4 field width
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_TD_4_WIDTH    ((uint32_t)0x00000002)
/// WF_PU_TIA_TD_1 field mask
#define WLAN_RF_WF_PU_TIA_TD_1_MASK                 ((uint32_t)0x00000003)
/// WF_PU_TIA_TD_1 field LSB position
#define WLAN_RF_WF_PU_TIA_TD_1_LSB                  0
/// WF_PU_TIA_TD_1 field width
#define WLAN_RF_WF_PU_TIA_TD_1_WIDTH                ((uint32_t)0x00000002)

/// WF_TEST_ENABLE_LNA_5G_PREAMP field reset value
#define WLAN_RF_WF_TEST_ENABLE_LNA_5G_PREAMP_RST    0x0
/// WF_TEST_ENABLE_LNA field reset value
#define WLAN_RF_WF_TEST_ENABLE_LNA_RST              0x0
/// WF_TEST_ENABLE_RMX field reset value
#define WLAN_RF_WF_TEST_ENABLE_RMX_RST              0x0
/// WF_TEST_ENABLE_TIA field reset value
#define WLAN_RF_WF_TEST_ENABLE_TIA_RST              0x0
/// WF_TEST_ENABLE_PA field reset value
#define WLAN_RF_WF_TEST_ENABLE_PA_RST               0x0
/// WF_TEST_ENABLE_DTMX field reset value
#define WLAN_RF_WF_TEST_ENABLE_DTMX_RST             0x0
/// WF_TEST_ENABLE_IREF field reset value
#define WLAN_RF_WF_TEST_ENABLE_IREF_RST             0x0
/// WF_RXFLT_TEST_2GPIO_EN field reset value
#define WLAN_RF_WF_RXFLT_TEST_2GPIO_EN_RST          0x0
/// WF_TEST_ENABLE_RXFLT field reset value
#define WLAN_RF_WF_TEST_ENABLE_RXFLT_RST            0x0
/// WF_TEST_ENABLE_ADC field reset value
#define WLAN_RF_WF_TEST_ENABLE_ADC_RST              0x0
/// WF_TEST_ENABLE_TS_HUB field reset value
#define WLAN_RF_WF_TEST_ENABLE_TS_HUB_RST           0x0
/// WF_VCO_TEST_BUF_EN field reset value
#define WLAN_RF_WF_VCO_TEST_BUF_EN_RST              0x0
/// WF_TEST_ENABLE_RFPLL field reset value
#define WLAN_RF_WF_TEST_ENABLE_RFPLL_RST            0x0
/// WF_TEST_ENABLE_VCO field reset value
#define WLAN_RF_WF_TEST_ENABLE_VCO_RST              0x0
/// WF_PU_LO_PSW_TD_2 field reset value
#define WLAN_RF_WF_PU_LO_PSW_TD_2_RST               0x1
/// WF_PU_VCO_TD_2 field reset value
#define WLAN_RF_WF_PU_VCO_TD_2_RST                  0x1
/// WF_PU_RFPLL_TD_3 field reset value
#define WLAN_RF_WF_PU_RFPLL_TD_3_RST                0x5
/// WF_PU_RMX_TD_1 field reset value
#define WLAN_RF_WF_PU_RMX_TD_1_RST                  0x1
/// WF_LOGEN_PHASE_MUX_RSTN_TD_4 field reset value
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_TD_4_RST    0x2
/// WF_RMX_LOGEN_DLL_RSTN_TD_4 field reset value
#define WLAN_RF_WF_RMX_LOGEN_DLL_RSTN_TD_4_RST      0x1
/// WF_PU_TIA_TD_1 field reset value
#define WLAN_RF_WF_PU_TIA_TD_1_RST                  0x1

/**
 * @brief Constructs a value for the REG_0C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wftestenablelna5gpreamp - The value to use for the wf_test_enable_lna5g_preamp field.
 * @param[in] wftestenablelna - The value to use for the wf_test_enable_lna field.
 * @param[in] wftestenablermx - The value to use for the wf_test_enable_rmx field.
 * @param[in] wftestenabletia - The value to use for the wf_test_enable_tia field.
 * @param[in] wftestenablepa - The value to use for the wf_test_enable_pa field.
 * @param[in] wftestenabledtmx - The value to use for the wf_test_enable_dtmx field.
 * @param[in] wftestenableiref - The value to use for the wf_test_enable_iref field.
 * @param[in] wfrxflttest2gpioen - The value to use for the wf_rxflt_test2gpio_en field.
 * @param[in] wftestenablerxflt - The value to use for the wf_test_enable_rxflt field.
 * @param[in] wftestenableadc - The value to use for the wf_test_enable_adc field.
 * @param[in] wftestenabletshub - The value to use for the wf_test_enable_ts_hub field.
 * @param[in] wfvcotestbufen - The value to use for the wf_vco_test_buf_en field.
 * @param[in] wftestenablerfpll - The value to use for the wf_test_enable_rfpll field.
 * @param[in] wftestenablevco - The value to use for the wf_test_enable_vco field.
 * @param[in] wfpulopswtd2 - The value to use for the wf_pu_lo_psw_td2 field.
 * @param[in] wfpuvcotd2 - The value to use for the wf_pu_vco_td2 field.
 * @param[in] wfpurfplltd3 - The value to use for the wf_pu_rfpll_td3 field.
 * @param[in] wfpurmxtd1 - The value to use for the wf_pu_rmx_td1 field.
 * @param[in] wflogenphasemuxrstntd4 - The value to use for the wf_logen_phase_mux_rstn_td4 field.
 * @param[in] wfrmxlogendllrstntd4 - The value to use for the wf_rmx_logen_dll_rstn_td4 field.
 * @param[in] wfputiatd1 - The value to use for the wf_pu_tia_td1 field.
 */
__INLINE void wlan_rf_reg_0c_pack(uint8_t wftestenablelna5gpreamp, uint8_t wftestenablelna, uint8_t wftestenablermx, uint8_t wftestenabletia, uint8_t wftestenablepa, uint8_t wftestenabledtmx, uint8_t wftestenableiref, uint8_t wfrxflttest2gpioen, uint8_t wftestenablerxflt, uint8_t wftestenableadc, uint8_t wftestenabletshub, uint8_t wfvcotestbufen, uint8_t wftestenablerfpll, uint8_t wftestenablevco, uint8_t wfpulopswtd2, uint8_t wfpuvcotd2, uint8_t wfpurfplltd3, uint8_t wfpurmxtd1, uint8_t wflogenphasemuxrstntd4, uint8_t wfrmxlogendllrstntd4, uint8_t wfputiatd1)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR,  ((uint32_t)wftestenablelna5gpreamp << 30) | ((uint32_t)wftestenablelna << 29) | ((uint32_t)wftestenablermx << 28) | ((uint32_t)wftestenabletia << 26) | ((uint32_t)wftestenablepa << 25) | ((uint32_t)wftestenabledtmx << 24) | ((uint32_t)wftestenableiref << 23) | ((uint32_t)wfrxflttest2gpioen << 22) | ((uint32_t)wftestenablerxflt << 20) | ((uint32_t)wftestenableadc << 19) | ((uint32_t)wftestenabletshub << 18) | ((uint32_t)wfvcotestbufen << 17) | ((uint32_t)wftestenablerfpll << 16) | ((uint32_t)wftestenablevco << 15) | ((uint32_t)wfpulopswtd2 << 13) | ((uint32_t)wfpuvcotd2 << 11) | ((uint32_t)wfpurfplltd3 << 8) | ((uint32_t)wfpurmxtd1 << 6) | ((uint32_t)wflogenphasemuxrstntd4 << 4) | ((uint32_t)wfrmxlogendllrstntd4 << 2) | ((uint32_t)wfputiatd1 << 0));
}

/**
 * @brief Unpacks REG_0C's fields from current value of the REG_0C register.
 *
 * Reads the REG_0C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wftestenablelna5gpreamp - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablelna - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablermx - Will be populated with the current value of this field from the register.
 * @param[out] wftestenabletia - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablepa - Will be populated with the current value of this field from the register.
 * @param[out] wftestenabledtmx - Will be populated with the current value of this field from the register.
 * @param[out] wftestenableiref - Will be populated with the current value of this field from the register.
 * @param[out] wfrxflttest2gpioen - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablerxflt - Will be populated with the current value of this field from the register.
 * @param[out] wftestenableadc - Will be populated with the current value of this field from the register.
 * @param[out] wftestenabletshub - Will be populated with the current value of this field from the register.
 * @param[out] wfvcotestbufen - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablerfpll - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablevco - Will be populated with the current value of this field from the register.
 * @param[out] wfpulopswtd2 - Will be populated with the current value of this field from the register.
 * @param[out] wfpuvcotd2 - Will be populated with the current value of this field from the register.
 * @param[out] wfpurfplltd3 - Will be populated with the current value of this field from the register.
 * @param[out] wfpurmxtd1 - Will be populated with the current value of this field from the register.
 * @param[out] wflogenphasemuxrstntd4 - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogendllrstntd4 - Will be populated with the current value of this field from the register.
 * @param[out] wfputiatd1 - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_0c_unpack(uint8_t* wftestenablelna5gpreamp, uint8_t* wftestenablelna, uint8_t* wftestenablermx, uint8_t* wftestenabletia, uint8_t* wftestenablepa, uint8_t* wftestenabledtmx, uint8_t* wftestenableiref, uint8_t* wfrxflttest2gpioen, uint8_t* wftestenablerxflt, uint8_t* wftestenableadc, uint8_t* wftestenabletshub, uint8_t* wfvcotestbufen, uint8_t* wftestenablerfpll, uint8_t* wftestenablevco, uint8_t* wfpulopswtd2, uint8_t* wfpuvcotd2, uint8_t* wfpurfplltd3, uint8_t* wfpurmxtd1, uint8_t* wflogenphasemuxrstntd4, uint8_t* wfrmxlogendllrstntd4, uint8_t* wfputiatd1)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);

    *wftestenablelna5gpreamp = (localVal & ((uint32_t)0x40000000)) >> 30;
    *wftestenablelna = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wftestenablermx = (localVal & ((uint32_t)0x10000000)) >> 28;
    *wftestenabletia = (localVal & ((uint32_t)0x0C000000)) >> 26;
    *wftestenablepa = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wftestenabledtmx = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wftestenableiref = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfrxflttest2gpioen = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wftestenablerxflt = (localVal & ((uint32_t)0x00300000)) >> 20;
    *wftestenableadc = (localVal & ((uint32_t)0x00080000)) >> 19;
    *wftestenabletshub = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfvcotestbufen = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wftestenablerfpll = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wftestenablevco = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wfpulopswtd2 = (localVal & ((uint32_t)0x00006000)) >> 13;
    *wfpuvcotd2 = (localVal & ((uint32_t)0x00001800)) >> 11;
    *wfpurfplltd3 = (localVal & ((uint32_t)0x00000700)) >> 8;
    *wfpurmxtd1 = (localVal & ((uint32_t)0x000000C0)) >> 6;
    *wflogenphasemuxrstntd4 = (localVal & ((uint32_t)0x00000030)) >> 4;
    *wfrmxlogendllrstntd4 = (localVal & ((uint32_t)0x0000000C)) >> 2;
    *wfputiatd1 = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_test_enable_lna5g_preamp field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_lna5g_preamp field's value will be returned.
 *
 * @return The current value of the wf_test_enable_lna5g_preamp field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_lna_5g_preamp_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the wf_test_enable_lna5g_preamp field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablelna5gpreamp - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_lna_5g_preamp_setf(uint8_t wftestenablelna5gpreamp)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)wftestenablelna5gpreamp << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_lna field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_lna field's value will be returned.
 *
 * @return The current value of the wf_test_enable_lna field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the wf_test_enable_lna field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablelna - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_lna_setf(uint8_t wftestenablelna)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wftestenablelna << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_rmx field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_rmx field's value will be returned.
 *
 * @return The current value of the wf_test_enable_rmx field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_rmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the wf_test_enable_rmx field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablermx - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_rmx_setf(uint8_t wftestenablermx)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)wftestenablermx << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_tia field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_tia field's value will be returned.
 *
 * @return The current value of the wf_test_enable_tia field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_tia_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x0C000000)) >> 26);
}

/**
 * @brief Sets the wf_test_enable_tia field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenabletia - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_tia_setf(uint8_t wftestenabletia)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x0C000000)) | (((uint32_t)wftestenabletia << 26) & ((uint32_t)0x0C000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_pa field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_pa field's value will be returned.
 *
 * @return The current value of the wf_test_enable_pa field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_pa_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_test_enable_pa field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablepa - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_pa_setf(uint8_t wftestenablepa)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wftestenablepa << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_dtmx field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_dtmx field's value will be returned.
 *
 * @return The current value of the wf_test_enable_dtmx field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_dtmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the wf_test_enable_dtmx field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenabledtmx - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_dtmx_setf(uint8_t wftestenabledtmx)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wftestenabledtmx << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_iref field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_iref field's value will be returned.
 *
 * @return The current value of the wf_test_enable_iref field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_iref_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_test_enable_iref field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenableiref - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_iref_setf(uint8_t wftestenableiref)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wftestenableiref << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_rxflt_test2gpio_en field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxflt_test2gpio_en field's value will be returned.
 *
 * @return The current value of the wf_rxflt_test2gpio_en field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_test_2gpio_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the wf_rxflt_test2gpio_en field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxflttest2gpioen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_test_2gpio_en_setf(uint8_t wfrxflttest2gpioen)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)wfrxflttest2gpioen << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_rxflt field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_rxflt field's value will be returned.
 *
 * @return The current value of the wf_test_enable_rxflt field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_rxflt_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

/**
 * @brief Sets the wf_test_enable_rxflt field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablerxflt - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_rxflt_setf(uint8_t wftestenablerxflt)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00300000)) | (((uint32_t)wftestenablerxflt << 20) & ((uint32_t)0x00300000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_adc field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_adc field's value will be returned.
 *
 * @return The current value of the wf_test_enable_adc field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_adc_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the wf_test_enable_adc field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenableadc - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_adc_setf(uint8_t wftestenableadc)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)wftestenableadc << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_ts_hub field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_ts_hub field's value will be returned.
 *
 * @return The current value of the wf_test_enable_ts_hub field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_ts_hub_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_test_enable_ts_hub field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenabletshub - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_ts_hub_setf(uint8_t wftestenabletshub)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wftestenabletshub << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_vco_test_buf_en field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_vco_test_buf_en field's value will be returned.
 *
 * @return The current value of the wf_vco_test_buf_en field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_vco_test_buf_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_vco_test_buf_en field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcotestbufen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_test_buf_en_setf(uint8_t wfvcotestbufen)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wfvcotestbufen << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_rfpll field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_rfpll field's value will be returned.
 *
 * @return The current value of the wf_test_enable_rfpll field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_rfpll_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_test_enable_rfpll field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablerfpll - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_rfpll_setf(uint8_t wftestenablerfpll)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wftestenablerfpll << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_vco field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_test_enable_vco field's value will be returned.
 *
 * @return The current value of the wf_test_enable_vco field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_vco_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the wf_test_enable_vco field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablevco - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_vco_setf(uint8_t wftestenablevco)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)wftestenablevco << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the wf_pu_lo_psw_td2 field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_pu_lo_psw_td2 field's value will be returned.
 *
 * @return The current value of the wf_pu_lo_psw_td2 field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_pu_lo_psw_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00006000)) >> 13);
}

/**
 * @brief Sets the wf_pu_lo_psw_td2 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpulopswtd2 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_lo_psw_td_2_setf(uint8_t wfpulopswtd2)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00006000)) | (((uint32_t)wfpulopswtd2 << 13) & ((uint32_t)0x00006000)));
}

/**
 * @brief Returns the current value of the wf_pu_vco_td2 field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_pu_vco_td2 field's value will be returned.
 *
 * @return The current value of the wf_pu_vco_td2 field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_pu_vco_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00001800)) >> 11);
}

/**
 * @brief Sets the wf_pu_vco_td2 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuvcotd2 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_vco_td_2_setf(uint8_t wfpuvcotd2)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00001800)) | (((uint32_t)wfpuvcotd2 << 11) & ((uint32_t)0x00001800)));
}

/**
 * @brief Returns the current value of the wf_pu_rfpll_td3 field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_pu_rfpll_td3 field's value will be returned.
 *
 * @return The current value of the wf_pu_rfpll_td3 field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rfpll_td_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

/**
 * @brief Sets the wf_pu_rfpll_td3 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurfplltd3 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rfpll_td_3_setf(uint8_t wfpurfplltd3)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00000700)) | (((uint32_t)wfpurfplltd3 << 8) & ((uint32_t)0x00000700)));
}

/**
 * @brief Returns the current value of the wf_pu_rmx_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_pu_rmx_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_rmx_td1 field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rmx_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x000000C0)) >> 6);
}

/**
 * @brief Sets the wf_pu_rmx_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurmxtd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rmx_td_1_setf(uint8_t wfpurmxtd1)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x000000C0)) | (((uint32_t)wfpurmxtd1 << 6) & ((uint32_t)0x000000C0)));
}

/**
 * @brief Returns the current value of the wf_logen_phase_mux_rstn_td4 field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_logen_phase_mux_rstn_td4 field's value will be returned.
 *
 * @return The current value of the wf_logen_phase_mux_rstn_td4 field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_logen_phase_mux_rstn_td_4_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

/**
 * @brief Sets the wf_logen_phase_mux_rstn_td4 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflogenphasemuxrstntd4 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_logen_phase_mux_rstn_td_4_setf(uint8_t wflogenphasemuxrstntd4)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00000030)) | (((uint32_t)wflogenphasemuxrstntd4 << 4) & ((uint32_t)0x00000030)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_dll_rstn_td4 field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rmx_logen_dll_rstn_td4 field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_dll_rstn_td4 field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_dll_rstn_td_4_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x0000000C)) >> 2);
}

/**
 * @brief Sets the wf_rmx_logen_dll_rstn_td4 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogendllrstntd4 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_dll_rstn_td_4_setf(uint8_t wfrmxlogendllrstntd4)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x0000000C)) | (((uint32_t)wfrmxlogendllrstntd4 << 2) & ((uint32_t)0x0000000C)));
}

/**
 * @brief Returns the current value of the wf_pu_tia_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_pu_tia_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_tia_td1 field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_pu_tia_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the wf_pu_tia_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputiatd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_tia_td_1_setf(uint8_t wfputiatd1)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)wfputiatd1 << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_10 register definitions
 * <table>
 * <caption id="REG_10_BF">REG_10 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:28 <td>   wf_pu_rxflt_td1 <td>R <td>R/W <td>0x1
 * <tr><td>27:26 <td>     wf_pu_adc_td1 <td>R <td>R/W <td>0x1
 * <tr><td>25:24 <td>     wf_pu_lna_td1 <td>R <td>R/W <td>0x1
 * <tr><td>23:22 <td>    wf_pu_dtmx_td1 <td>R <td>R/W <td>0x1
 * <tr><td>21:20 <td>wf_dtmx_logen_dll_rstn_td4 <td>R <td>R/W <td>0x1
 * <tr><td>19:18 <td>wf_logen_phase_mux_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>17:16 <td>wf_dtmx_cdr_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>15:14 <td>      wf_pu_pa_td1 <td>R <td>R/W <td>0x1
 * <tr><td>13:12 <td>wf_pa_pkdet_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>11:10 <td>wf_pa_pkdet_rstn_td2 <td>R <td>R/W <td>0x1
 * <tr><td>09:08 <td>wf_vco_band_temp_bit_td2 <td>R <td>R/W <td>0x1
 * <tr><td>07:06 <td>wf_rfpll_vctrl_det_en_td2 <td>R <td>R/W <td>0x1
 * <tr><td>05:04 <td>wf_dtmx_bt2wf_tx_en_td1 <td>R <td>R/W <td>0x1
 * <tr><td>03:02 <td>wf_pa24g_bt_mode_en_td1 <td>R <td>R/W <td>0x1
 * <tr><td>01 <td>cm_mdll_auto_reset_en <td>R <td>R/W <td>0
 * <tr><td>00 <td>wf_rfpll_temp_comp_en <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_10 register
#define WLAN_RF_REG_10_ADDR   0x40344010
/// Offset of the REG_10 register from the base address
#define WLAN_RF_REG_10_OFFSET 0x00000010
/// Index of the REG_10 register
#define WLAN_RF_REG_10_INDEX  0x00000004
/// Reset value of the REG_10 register
#define WLAN_RF_REG_10_RESET  0x15555555

/**
 * @brief Returns the current value of the REG_10 register.
 * The REG_10 register will be read and its value returned.
 * @return The current value of the REG_10 register.
 */
__INLINE uint32_t wlan_rf_reg_10_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_10_ADDR);
}

/**
 * @brief Sets the REG_10 register to a value.
 * The REG_10 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_10_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, value);
}

// field definitions
/// WF_PU_RXFLT_TD_1 field mask
#define WLAN_RF_WF_PU_RXFLT_TD_1_MASK               ((uint32_t)0x30000000)
/// WF_PU_RXFLT_TD_1 field LSB position
#define WLAN_RF_WF_PU_RXFLT_TD_1_LSB                28
/// WF_PU_RXFLT_TD_1 field width
#define WLAN_RF_WF_PU_RXFLT_TD_1_WIDTH              ((uint32_t)0x00000002)
/// WF_PU_ADC_TD_1 field mask
#define WLAN_RF_WF_PU_ADC_TD_1_MASK                 ((uint32_t)0x0C000000)
/// WF_PU_ADC_TD_1 field LSB position
#define WLAN_RF_WF_PU_ADC_TD_1_LSB                  26
/// WF_PU_ADC_TD_1 field width
#define WLAN_RF_WF_PU_ADC_TD_1_WIDTH                ((uint32_t)0x00000002)
/// WF_PU_LNA_TD_1 field mask
#define WLAN_RF_WF_PU_LNA_TD_1_MASK                 ((uint32_t)0x03000000)
/// WF_PU_LNA_TD_1 field LSB position
#define WLAN_RF_WF_PU_LNA_TD_1_LSB                  24
/// WF_PU_LNA_TD_1 field width
#define WLAN_RF_WF_PU_LNA_TD_1_WIDTH                ((uint32_t)0x00000002)
/// WF_PU_DTMX_TD_1 field mask
#define WLAN_RF_WF_PU_DTMX_TD_1_MASK                ((uint32_t)0x00C00000)
/// WF_PU_DTMX_TD_1 field LSB position
#define WLAN_RF_WF_PU_DTMX_TD_1_LSB                 22
/// WF_PU_DTMX_TD_1 field width
#define WLAN_RF_WF_PU_DTMX_TD_1_WIDTH               ((uint32_t)0x00000002)
/// WF_DTMX_LOGEN_DLL_RSTN_TD_4 field mask
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_TD_4_MASK    ((uint32_t)0x00300000)
/// WF_DTMX_LOGEN_DLL_RSTN_TD_4 field LSB position
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_TD_4_LSB     20
/// WF_DTMX_LOGEN_DLL_RSTN_TD_4 field width
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_TD_4_WIDTH   ((uint32_t)0x00000002)
/// WF_LOGEN_PHASE_MUX_RSTN_TD_1 field mask
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_TD_1_MASK   ((uint32_t)0x000C0000)
/// WF_LOGEN_PHASE_MUX_RSTN_TD_1 field LSB position
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_TD_1_LSB    18
/// WF_LOGEN_PHASE_MUX_RSTN_TD_1 field width
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_TD_1_WIDTH  ((uint32_t)0x00000002)
/// WF_DTMX_CDR_RSTN_TD_1 field mask
#define WLAN_RF_WF_DTMX_CDR_RSTN_TD_1_MASK          ((uint32_t)0x00030000)
/// WF_DTMX_CDR_RSTN_TD_1 field LSB position
#define WLAN_RF_WF_DTMX_CDR_RSTN_TD_1_LSB           16
/// WF_DTMX_CDR_RSTN_TD_1 field width
#define WLAN_RF_WF_DTMX_CDR_RSTN_TD_1_WIDTH         ((uint32_t)0x00000002)
/// WF_PU_PA_TD_1 field mask
#define WLAN_RF_WF_PU_PA_TD_1_MASK                  ((uint32_t)0x0000C000)
/// WF_PU_PA_TD_1 field LSB position
#define WLAN_RF_WF_PU_PA_TD_1_LSB                   14
/// WF_PU_PA_TD_1 field width
#define WLAN_RF_WF_PU_PA_TD_1_WIDTH                 ((uint32_t)0x00000002)
/// WF_PA_PKDET_RSTN_TD_1 field mask
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_1_MASK          ((uint32_t)0x00003000)
/// WF_PA_PKDET_RSTN_TD_1 field LSB position
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_1_LSB           12
/// WF_PA_PKDET_RSTN_TD_1 field width
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_1_WIDTH         ((uint32_t)0x00000002)
/// WF_PA_PKDET_RSTN_TD_2 field mask
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_2_MASK          ((uint32_t)0x00000C00)
/// WF_PA_PKDET_RSTN_TD_2 field LSB position
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_2_LSB           10
/// WF_PA_PKDET_RSTN_TD_2 field width
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_2_WIDTH         ((uint32_t)0x00000002)
/// WF_VCO_BAND_TEMP_BIT_TD_2 field mask
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_TD_2_MASK      ((uint32_t)0x00000300)
/// WF_VCO_BAND_TEMP_BIT_TD_2 field LSB position
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_TD_2_LSB       8
/// WF_VCO_BAND_TEMP_BIT_TD_2 field width
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_TD_2_WIDTH     ((uint32_t)0x00000002)
/// WF_RFPLL_VCTRL_DET_EN_TD_2 field mask
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_TD_2_MASK     ((uint32_t)0x000000C0)
/// WF_RFPLL_VCTRL_DET_EN_TD_2 field LSB position
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_TD_2_LSB      6
/// WF_RFPLL_VCTRL_DET_EN_TD_2 field width
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_TD_2_WIDTH    ((uint32_t)0x00000002)
/// WF_DTMX_BT_2WF_TX_EN_TD_1 field mask
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_TD_1_MASK      ((uint32_t)0x00000030)
/// WF_DTMX_BT_2WF_TX_EN_TD_1 field LSB position
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_TD_1_LSB       4
/// WF_DTMX_BT_2WF_TX_EN_TD_1 field width
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_TD_1_WIDTH     ((uint32_t)0x00000002)
/// WF_PA_24G_BT_MODE_EN_TD_1 field mask
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_TD_1_MASK      ((uint32_t)0x0000000C)
/// WF_PA_24G_BT_MODE_EN_TD_1 field LSB position
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_TD_1_LSB       2
/// WF_PA_24G_BT_MODE_EN_TD_1 field width
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_TD_1_WIDTH     ((uint32_t)0x00000002)
/// CM_MDLL_AUTO_RESET_EN field bit
#define WLAN_RF_CM_MDLL_AUTO_RESET_EN_BIT           ((uint32_t)0x00000002)
/// CM_MDLL_AUTO_RESET_EN field position
#define WLAN_RF_CM_MDLL_AUTO_RESET_EN_POS           1
/// WF_RFPLL_TEMP_COMP_EN field bit
#define WLAN_RF_WF_RFPLL_TEMP_COMP_EN_BIT           ((uint32_t)0x00000001)
/// WF_RFPLL_TEMP_COMP_EN field position
#define WLAN_RF_WF_RFPLL_TEMP_COMP_EN_POS           0

/// WF_PU_RXFLT_TD_1 field reset value
#define WLAN_RF_WF_PU_RXFLT_TD_1_RST                0x1
/// WF_PU_ADC_TD_1 field reset value
#define WLAN_RF_WF_PU_ADC_TD_1_RST                  0x1
/// WF_PU_LNA_TD_1 field reset value
#define WLAN_RF_WF_PU_LNA_TD_1_RST                  0x1
/// WF_PU_DTMX_TD_1 field reset value
#define WLAN_RF_WF_PU_DTMX_TD_1_RST                 0x1
/// WF_DTMX_LOGEN_DLL_RSTN_TD_4 field reset value
#define WLAN_RF_WF_DTMX_LOGEN_DLL_RSTN_TD_4_RST     0x1
/// WF_LOGEN_PHASE_MUX_RSTN_TD_1 field reset value
#define WLAN_RF_WF_LOGEN_PHASE_MUX_RSTN_TD_1_RST    0x1
/// WF_DTMX_CDR_RSTN_TD_1 field reset value
#define WLAN_RF_WF_DTMX_CDR_RSTN_TD_1_RST           0x1
/// WF_PU_PA_TD_1 field reset value
#define WLAN_RF_WF_PU_PA_TD_1_RST                   0x1
/// WF_PA_PKDET_RSTN_TD_1 field reset value
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_1_RST           0x1
/// WF_PA_PKDET_RSTN_TD_2 field reset value
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_2_RST           0x1
/// WF_VCO_BAND_TEMP_BIT_TD_2 field reset value
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_TD_2_RST       0x1
/// WF_RFPLL_VCTRL_DET_EN_TD_2 field reset value
#define WLAN_RF_WF_RFPLL_VCTRL_DET_EN_TD_2_RST      0x1
/// WF_DTMX_BT_2WF_TX_EN_TD_1 field reset value
#define WLAN_RF_WF_DTMX_BT_2WF_TX_EN_TD_1_RST       0x1
/// WF_PA_24G_BT_MODE_EN_TD_1 field reset value
#define WLAN_RF_WF_PA_24G_BT_MODE_EN_TD_1_RST       0x1
/// CM_MDLL_AUTO_RESET_EN field reset value
#define WLAN_RF_CM_MDLL_AUTO_RESET_EN_RST           0x0
/// WF_RFPLL_TEMP_COMP_EN field reset value
#define WLAN_RF_WF_RFPLL_TEMP_COMP_EN_RST           0x1

/**
 * @brief Constructs a value for the REG_10 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpurxflttd1 - The value to use for the wf_pu_rxflt_td1 field.
 * @param[in] wfpuadctd1 - The value to use for the wf_pu_adc_td1 field.
 * @param[in] wfpulnatd1 - The value to use for the wf_pu_lna_td1 field.
 * @param[in] wfpudtmxtd1 - The value to use for the wf_pu_dtmx_td1 field.
 * @param[in] wfdtmxlogendllrstntd4 - The value to use for the wf_dtmx_logen_dll_rstn_td4 field.
 * @param[in] wflogenphasemuxrstntd1 - The value to use for the wf_logen_phase_mux_rstn_td1 field.
 * @param[in] wfdtmxcdrrstntd1 - The value to use for the wf_dtmx_cdr_rstn_td1 field.
 * @param[in] wfpupatd1 - The value to use for the wf_pu_pa_td1 field.
 * @param[in] wfpapkdetrstntd1 - The value to use for the wf_pa_pkdet_rstn_td1 field.
 * @param[in] wfpapkdetrstntd2 - The value to use for the wf_pa_pkdet_rstn_td2 field.
 * @param[in] wfvcobandtempbittd2 - The value to use for the wf_vco_band_temp_bit_td2 field.
 * @param[in] wfrfpllvctrldetentd2 - The value to use for the wf_rfpll_vctrl_det_en_td2 field.
 * @param[in] wfdtmxbt2wftxentd1 - The value to use for the wf_dtmx_bt2wf_tx_en_td1 field.
 * @param[in] wfpa24gbtmodeentd1 - The value to use for the wf_pa24g_bt_mode_en_td1 field.
 * @param[in] cmmdllautoreseten - The value to use for the cm_mdll_auto_reset_en field.
 * @param[in] wfrfplltempcompen - The value to use for the wf_rfpll_temp_comp_en field.
 */
__INLINE void wlan_rf_reg_10_pack(uint8_t wfpurxflttd1, uint8_t wfpuadctd1, uint8_t wfpulnatd1, uint8_t wfpudtmxtd1, uint8_t wfdtmxlogendllrstntd4, uint8_t wflogenphasemuxrstntd1, uint8_t wfdtmxcdrrstntd1, uint8_t wfpupatd1, uint8_t wfpapkdetrstntd1, uint8_t wfpapkdetrstntd2, uint8_t wfvcobandtempbittd2, uint8_t wfrfpllvctrldetentd2, uint8_t wfdtmxbt2wftxentd1, uint8_t wfpa24gbtmodeentd1, uint8_t cmmdllautoreseten, uint8_t wfrfplltempcompen)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR,  ((uint32_t)wfpurxflttd1 << 28) | ((uint32_t)wfpuadctd1 << 26) | ((uint32_t)wfpulnatd1 << 24) | ((uint32_t)wfpudtmxtd1 << 22) | ((uint32_t)wfdtmxlogendllrstntd4 << 20) | ((uint32_t)wflogenphasemuxrstntd1 << 18) | ((uint32_t)wfdtmxcdrrstntd1 << 16) | ((uint32_t)wfpupatd1 << 14) | ((uint32_t)wfpapkdetrstntd1 << 12) | ((uint32_t)wfpapkdetrstntd2 << 10) | ((uint32_t)wfvcobandtempbittd2 << 8) | ((uint32_t)wfrfpllvctrldetentd2 << 6) | ((uint32_t)wfdtmxbt2wftxentd1 << 4) | ((uint32_t)wfpa24gbtmodeentd1 << 2) | ((uint32_t)cmmdllautoreseten << 1) | ((uint32_t)wfrfplltempcompen << 0));
}

/**
 * @brief Unpacks REG_10's fields from current value of the REG_10 register.
 *
 * Reads the REG_10 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpurxflttd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpuadctd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpulnatd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpudtmxtd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogendllrstntd4 - Will be populated with the current value of this field from the register.
 * @param[out] wflogenphasemuxrstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrrstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpupatd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetrstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetrstntd2 - Will be populated with the current value of this field from the register.
 * @param[out] wfvcobandtempbittd2 - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllvctrldetentd2 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxbt2wftxentd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gbtmodeentd1 - Will be populated with the current value of this field from the register.
 * @param[out] cmmdllautoreseten - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplltempcompen - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_10_unpack(uint8_t* wfpurxflttd1, uint8_t* wfpuadctd1, uint8_t* wfpulnatd1, uint8_t* wfpudtmxtd1, uint8_t* wfdtmxlogendllrstntd4, uint8_t* wflogenphasemuxrstntd1, uint8_t* wfdtmxcdrrstntd1, uint8_t* wfpupatd1, uint8_t* wfpapkdetrstntd1, uint8_t* wfpapkdetrstntd2, uint8_t* wfvcobandtempbittd2, uint8_t* wfrfpllvctrldetentd2, uint8_t* wfdtmxbt2wftxentd1, uint8_t* wfpa24gbtmodeentd1, uint8_t* cmmdllautoreseten, uint8_t* wfrfplltempcompen)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);

    *wfpurxflttd1 = (localVal & ((uint32_t)0x30000000)) >> 28;
    *wfpuadctd1 = (localVal & ((uint32_t)0x0C000000)) >> 26;
    *wfpulnatd1 = (localVal & ((uint32_t)0x03000000)) >> 24;
    *wfpudtmxtd1 = (localVal & ((uint32_t)0x00C00000)) >> 22;
    *wfdtmxlogendllrstntd4 = (localVal & ((uint32_t)0x00300000)) >> 20;
    *wflogenphasemuxrstntd1 = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *wfdtmxcdrrstntd1 = (localVal & ((uint32_t)0x00030000)) >> 16;
    *wfpupatd1 = (localVal & ((uint32_t)0x0000C000)) >> 14;
    *wfpapkdetrstntd1 = (localVal & ((uint32_t)0x00003000)) >> 12;
    *wfpapkdetrstntd2 = (localVal & ((uint32_t)0x00000C00)) >> 10;
    *wfvcobandtempbittd2 = (localVal & ((uint32_t)0x00000300)) >> 8;
    *wfrfpllvctrldetentd2 = (localVal & ((uint32_t)0x000000C0)) >> 6;
    *wfdtmxbt2wftxentd1 = (localVal & ((uint32_t)0x00000030)) >> 4;
    *wfpa24gbtmodeentd1 = (localVal & ((uint32_t)0x0000000C)) >> 2;
    *cmmdllautoreseten = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfrfplltempcompen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pu_rxflt_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_pu_rxflt_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_rxflt_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rxflt_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

/**
 * @brief Sets the wf_pu_rxflt_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurxflttd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rxflt_td_1_setf(uint8_t wfpurxflttd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x30000000)) | (((uint32_t)wfpurxflttd1 << 28) & ((uint32_t)0x30000000)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_pu_adc_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x0C000000)) >> 26);
}

/**
 * @brief Sets the wf_pu_adc_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadctd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_td_1_setf(uint8_t wfpuadctd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x0C000000)) | (((uint32_t)wfpuadctd1 << 26) & ((uint32_t)0x0C000000)));
}

/**
 * @brief Returns the current value of the wf_pu_lna_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_pu_lna_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_lna_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_lna_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

/**
 * @brief Sets the wf_pu_lna_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpulnatd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_lna_td_1_setf(uint8_t wfpulnatd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x03000000)) | (((uint32_t)wfpulnatd1 << 24) & ((uint32_t)0x03000000)));
}

/**
 * @brief Returns the current value of the wf_pu_dtmx_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_pu_dtmx_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_dtmx_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_dtmx_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00C00000)) >> 22);
}

/**
 * @brief Sets the wf_pu_dtmx_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpudtmxtd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_dtmx_td_1_setf(uint8_t wfpudtmxtd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00C00000)) | (((uint32_t)wfpudtmxtd1 << 22) & ((uint32_t)0x00C00000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_dll_rstn_td4 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_dtmx_logen_dll_rstn_td4 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_dll_rstn_td4 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_dll_rstn_td_4_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

/**
 * @brief Sets the wf_dtmx_logen_dll_rstn_td4 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogendllrstntd4 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_dll_rstn_td_4_setf(uint8_t wfdtmxlogendllrstntd4)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00300000)) | (((uint32_t)wfdtmxlogendllrstntd4 << 20) & ((uint32_t)0x00300000)));
}

/**
 * @brief Returns the current value of the wf_logen_phase_mux_rstn_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_logen_phase_mux_rstn_td1 field's value will be returned.
 *
 * @return The current value of the wf_logen_phase_mux_rstn_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_logen_phase_mux_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the wf_logen_phase_mux_rstn_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflogenphasemuxrstntd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_logen_phase_mux_rstn_td_1_setf(uint8_t wflogenphasemuxrstntd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)wflogenphasemuxrstntd1 << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_rstn_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_dtmx_cdr_rstn_td1 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_rstn_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

/**
 * @brief Sets the wf_dtmx_cdr_rstn_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdrrstntd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_rstn_td_1_setf(uint8_t wfdtmxcdrrstntd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00030000)) | (((uint32_t)wfdtmxcdrrstntd1 << 16) & ((uint32_t)0x00030000)));
}

/**
 * @brief Returns the current value of the wf_pu_pa_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_pu_pa_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_pa_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_pa_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x0000C000)) >> 14);
}

/**
 * @brief Sets the wf_pu_pa_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpupatd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_pa_td_1_setf(uint8_t wfpupatd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x0000C000)) | (((uint32_t)wfpupatd1 << 14) & ((uint32_t)0x0000C000)));
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_rstn_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_pa_pkdet_rstn_td1 field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_rstn_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

/**
 * @brief Sets the wf_pa_pkdet_rstn_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkdetrstntd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkdet_rstn_td_1_setf(uint8_t wfpapkdetrstntd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00003000)) | (((uint32_t)wfpapkdetrstntd1 << 12) & ((uint32_t)0x00003000)));
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_rstn_td2 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_pa_pkdet_rstn_td2 field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_rstn_td2 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_rstn_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00000C00)) >> 10);
}

/**
 * @brief Sets the wf_pa_pkdet_rstn_td2 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkdetrstntd2 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkdet_rstn_td_2_setf(uint8_t wfpapkdetrstntd2)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00000C00)) | (((uint32_t)wfpapkdetrstntd2 << 10) & ((uint32_t)0x00000C00)));
}

/**
 * @brief Returns the current value of the wf_vco_band_temp_bit_td2 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_vco_band_temp_bit_td2 field's value will be returned.
 *
 * @return The current value of the wf_vco_band_temp_bit_td2 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_band_temp_bit_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the wf_vco_band_temp_bit_td2 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcobandtempbittd2 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_band_temp_bit_td_2_setf(uint8_t wfvcobandtempbittd2)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)wfvcobandtempbittd2 << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the wf_rfpll_vctrl_det_en_td2 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_vctrl_det_en_td2 field's value will be returned.
 *
 * @return The current value of the wf_rfpll_vctrl_det_en_td2 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_vctrl_det_en_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x000000C0)) >> 6);
}

/**
 * @brief Sets the wf_rfpll_vctrl_det_en_td2 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllvctrldetentd2 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_vctrl_det_en_td_2_setf(uint8_t wfrfpllvctrldetentd2)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x000000C0)) | (((uint32_t)wfrfpllvctrldetentd2 << 6) & ((uint32_t)0x000000C0)));
}

/**
 * @brief Returns the current value of the wf_dtmx_bt2wf_tx_en_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_dtmx_bt2wf_tx_en_td1 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_bt2wf_tx_en_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_bt_2wf_tx_en_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

/**
 * @brief Sets the wf_dtmx_bt2wf_tx_en_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxbt2wftxentd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_bt_2wf_tx_en_td_1_setf(uint8_t wfdtmxbt2wftxentd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00000030)) | (((uint32_t)wfdtmxbt2wftxentd1 << 4) & ((uint32_t)0x00000030)));
}

/**
 * @brief Returns the current value of the wf_pa24g_bt_mode_en_td1 field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_pa24g_bt_mode_en_td1 field's value will be returned.
 *
 * @return The current value of the wf_pa24g_bt_mode_en_td1 field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_bt_mode_en_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x0000000C)) >> 2);
}

/**
 * @brief Sets the wf_pa24g_bt_mode_en_td1 field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24gbtmodeentd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_bt_mode_en_td_1_setf(uint8_t wfpa24gbtmodeentd1)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x0000000C)) | (((uint32_t)wfpa24gbtmodeentd1 << 2) & ((uint32_t)0x0000000C)));
}

/**
 * @brief Returns the current value of the cm_mdll_auto_reset_en field in the REG_10 register.
 *
 * The REG_10 register will be read and the cm_mdll_auto_reset_en field's value will be returned.
 *
 * @return The current value of the cm_mdll_auto_reset_en field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_cm_mdll_auto_reset_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the cm_mdll_auto_reset_en field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] cmmdllautoreseten - The value to set the field to.
 */
__INLINE void wlan_rf_cm_mdll_auto_reset_en_setf(uint8_t cmmdllautoreseten)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)cmmdllautoreseten << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_rfpll_temp_comp_en field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_temp_comp_en field's value will be returned.
 *
 * @return The current value of the wf_rfpll_temp_comp_en field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_temp_comp_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_rfpll_temp_comp_en field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplltempcompen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_temp_comp_en_setf(uint8_t wfrfplltempcompen)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfrfplltempcompen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_14 register definitions
 * <table>
 * <caption id="REG_14_BF">REG_14 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:26 <td>wf_rfpll_vctrl_THH <td>R <td>R/W <td>0x30
 * <tr><td>25:20 <td>wf_rfpll_vctrl_THL <td>R <td>R/W <td>0xF
 * <tr><td>19:18 <td>  wfcm_pu_mdll_td2 <td>R <td>R/W <td>0x2
 * <tr><td>17:16 <td>wfcm_mdll_rstn_td2 <td>R <td>R/W <td>0x3
 * <tr><td>15:13 <td>wfcm_mdll_rstn_td3 <td>R <td>R/W <td>0x1
 * <tr><td>12:11 <td>         wf_pd_td0 <td>R <td>R/W <td>0x1
 * <tr><td>10 <td>wf_lna5g_preamp_main_en <td>R <td>R/W <td>1
 * <tr><td>09 <td>wf_lna5g_preamp_gbit <td>W <td>R <td>1
 * <tr><td>08 <td>wf_lna5g_preamp_bypass_en <td>W <td>R <td>0
 * <tr><td>07 <td>wf_lna5g_img_cal_en <td>R <td>R/W <td>0
 * <tr><td>06:04 <td>wf_lna5g_preamp_reg_vbit <td>R <td>R/W <td>0x4
 * <tr><td>03:00 <td>wf_lna5g_preamp_cg_vbit <td>R <td>R/W <td>0x6
 * </table>
 *
 * @{
 */

/// Address of the REG_14 register
#define WLAN_RF_REG_14_ADDR   0x40344014
/// Offset of the REG_14 register from the base address
#define WLAN_RF_REG_14_OFFSET 0x00000014
/// Index of the REG_14 register
#define WLAN_RF_REG_14_INDEX  0x00000005
/// Reset value of the REG_14 register
#define WLAN_RF_REG_14_RESET  0xC0FB2E46

/**
 * @brief Returns the current value of the REG_14 register.
 * The REG_14 register will be read and its value returned.
 * @return The current value of the REG_14 register.
 */
__INLINE uint32_t wlan_rf_reg_14_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_14_ADDR);
}

/**
 * @brief Sets the REG_14 register to a value.
 * The REG_14 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_14_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, value);
}

// field definitions
/// WF_RFPLL_VCTRL_THH field mask
#define WLAN_RF_WF_RFPLL_VCTRL_THH_MASK           ((uint32_t)0xFC000000)
/// WF_RFPLL_VCTRL_THH field LSB position
#define WLAN_RF_WF_RFPLL_VCTRL_THH_LSB            26
/// WF_RFPLL_VCTRL_THH field width
#define WLAN_RF_WF_RFPLL_VCTRL_THH_WIDTH          ((uint32_t)0x00000006)
/// WF_RFPLL_VCTRL_THL field mask
#define WLAN_RF_WF_RFPLL_VCTRL_THL_MASK           ((uint32_t)0x03F00000)
/// WF_RFPLL_VCTRL_THL field LSB position
#define WLAN_RF_WF_RFPLL_VCTRL_THL_LSB            20
/// WF_RFPLL_VCTRL_THL field width
#define WLAN_RF_WF_RFPLL_VCTRL_THL_WIDTH          ((uint32_t)0x00000006)
/// WFCM_PU_MDLL_TD_2 field mask
#define WLAN_RF_WFCM_PU_MDLL_TD_2_MASK            ((uint32_t)0x000C0000)
/// WFCM_PU_MDLL_TD_2 field LSB position
#define WLAN_RF_WFCM_PU_MDLL_TD_2_LSB             18
/// WFCM_PU_MDLL_TD_2 field width
#define WLAN_RF_WFCM_PU_MDLL_TD_2_WIDTH           ((uint32_t)0x00000002)
/// WFCM_MDLL_RSTN_TD_2 field mask
#define WLAN_RF_WFCM_MDLL_RSTN_TD_2_MASK          ((uint32_t)0x00030000)
/// WFCM_MDLL_RSTN_TD_2 field LSB position
#define WLAN_RF_WFCM_MDLL_RSTN_TD_2_LSB           16
/// WFCM_MDLL_RSTN_TD_2 field width
#define WLAN_RF_WFCM_MDLL_RSTN_TD_2_WIDTH         ((uint32_t)0x00000002)
/// WFCM_MDLL_RSTN_TD_3 field mask
#define WLAN_RF_WFCM_MDLL_RSTN_TD_3_MASK          ((uint32_t)0x0000E000)
/// WFCM_MDLL_RSTN_TD_3 field LSB position
#define WLAN_RF_WFCM_MDLL_RSTN_TD_3_LSB           13
/// WFCM_MDLL_RSTN_TD_3 field width
#define WLAN_RF_WFCM_MDLL_RSTN_TD_3_WIDTH         ((uint32_t)0x00000003)
/// WF_PD_TD_0 field mask
#define WLAN_RF_WF_PD_TD_0_MASK                   ((uint32_t)0x00001800)
/// WF_PD_TD_0 field LSB position
#define WLAN_RF_WF_PD_TD_0_LSB                    11
/// WF_PD_TD_0 field width
#define WLAN_RF_WF_PD_TD_0_WIDTH                  ((uint32_t)0x00000002)
/// WF_LNA_5G_PREAMP_MAIN_EN field bit
#define WLAN_RF_WF_LNA_5G_PREAMP_MAIN_EN_BIT      ((uint32_t)0x00000400)
/// WF_LNA_5G_PREAMP_MAIN_EN field position
#define WLAN_RF_WF_LNA_5G_PREAMP_MAIN_EN_POS      10
/// WF_LNA_5G_PREAMP_GBIT field bit
#define WLAN_RF_WF_LNA_5G_PREAMP_GBIT_BIT         ((uint32_t)0x00000200)
/// WF_LNA_5G_PREAMP_GBIT field position
#define WLAN_RF_WF_LNA_5G_PREAMP_GBIT_POS         9
/// WF_LNA_5G_PREAMP_BYPASS_EN field bit
#define WLAN_RF_WF_LNA_5G_PREAMP_BYPASS_EN_BIT    ((uint32_t)0x00000100)
/// WF_LNA_5G_PREAMP_BYPASS_EN field position
#define WLAN_RF_WF_LNA_5G_PREAMP_BYPASS_EN_POS    8
/// WF_LNA_5G_IMG_CAL_EN field bit
#define WLAN_RF_WF_LNA_5G_IMG_CAL_EN_BIT          ((uint32_t)0x00000080)
/// WF_LNA_5G_IMG_CAL_EN field position
#define WLAN_RF_WF_LNA_5G_IMG_CAL_EN_POS          7
/// WF_LNA_5G_PREAMP_REG_VBIT field mask
#define WLAN_RF_WF_LNA_5G_PREAMP_REG_VBIT_MASK    ((uint32_t)0x00000070)
/// WF_LNA_5G_PREAMP_REG_VBIT field LSB position
#define WLAN_RF_WF_LNA_5G_PREAMP_REG_VBIT_LSB     4
/// WF_LNA_5G_PREAMP_REG_VBIT field width
#define WLAN_RF_WF_LNA_5G_PREAMP_REG_VBIT_WIDTH   ((uint32_t)0x00000003)
/// WF_LNA_5G_PREAMP_CG_VBIT field mask
#define WLAN_RF_WF_LNA_5G_PREAMP_CG_VBIT_MASK     ((uint32_t)0x0000000F)
/// WF_LNA_5G_PREAMP_CG_VBIT field LSB position
#define WLAN_RF_WF_LNA_5G_PREAMP_CG_VBIT_LSB      0
/// WF_LNA_5G_PREAMP_CG_VBIT field width
#define WLAN_RF_WF_LNA_5G_PREAMP_CG_VBIT_WIDTH    ((uint32_t)0x00000004)

/// WF_RFPLL_VCTRL_THH field reset value
#define WLAN_RF_WF_RFPLL_VCTRL_THH_RST            0x30
/// WF_RFPLL_VCTRL_THL field reset value
#define WLAN_RF_WF_RFPLL_VCTRL_THL_RST            0xF
/// WFCM_PU_MDLL_TD_2 field reset value
#define WLAN_RF_WFCM_PU_MDLL_TD_2_RST             0x2
/// WFCM_MDLL_RSTN_TD_2 field reset value
#define WLAN_RF_WFCM_MDLL_RSTN_TD_2_RST           0x3
/// WFCM_MDLL_RSTN_TD_3 field reset value
#define WLAN_RF_WFCM_MDLL_RSTN_TD_3_RST           0x1
/// WF_PD_TD_0 field reset value
#define WLAN_RF_WF_PD_TD_0_RST                    0x1
/// WF_LNA_5G_PREAMP_MAIN_EN field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_MAIN_EN_RST      0x1
/// WF_LNA_5G_PREAMP_GBIT field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_GBIT_RST         0x1
/// WF_LNA_5G_PREAMP_BYPASS_EN field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_BYPASS_EN_RST    0x0
/// WF_LNA_5G_IMG_CAL_EN field reset value
#define WLAN_RF_WF_LNA_5G_IMG_CAL_EN_RST          0x0
/// WF_LNA_5G_PREAMP_REG_VBIT field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_REG_VBIT_RST     0x4
/// WF_LNA_5G_PREAMP_CG_VBIT field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_CG_VBIT_RST      0x6

/**
 * @brief Constructs a value for the REG_14 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrfpllvctrlthh - The value to use for the wf_rfpll_vctrl_THH field.
 * @param[in] wfrfpllvctrlthl - The value to use for the wf_rfpll_vctrl_THL field.
 * @param[in] wfcmpumdlltd2 - The value to use for the wfcm_pu_mdll_td2 field.
 * @param[in] wfcmmdllrstntd2 - The value to use for the wfcm_mdll_rstn_td2 field.
 * @param[in] wfcmmdllrstntd3 - The value to use for the wfcm_mdll_rstn_td3 field.
 * @param[in] wfpdtd0 - The value to use for the wf_pd_td0 field.
 * @param[in] wflna5gpreampmainen - The value to use for the wf_lna5g_preamp_main_en field.
 * @param[in] wflna5gimgcalen - The value to use for the wf_lna5g_img_cal_en field.
 * @param[in] wflna5gpreampregvbit - The value to use for the wf_lna5g_preamp_reg_vbit field.
 * @param[in] wflna5gpreampcgvbit - The value to use for the wf_lna5g_preamp_cg_vbit field.
 */
__INLINE void wlan_rf_reg_14_pack(uint8_t wfrfpllvctrlthh, uint8_t wfrfpllvctrlthl, uint8_t wfcmpumdlltd2, uint8_t wfcmmdllrstntd2, uint8_t wfcmmdllrstntd3, uint8_t wfpdtd0, uint8_t wflna5gpreampmainen, uint8_t wflna5gimgcalen, uint8_t wflna5gpreampregvbit, uint8_t wflna5gpreampcgvbit)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR,  ((uint32_t)wfrfpllvctrlthh << 26) | ((uint32_t)wfrfpllvctrlthl << 20) | ((uint32_t)wfcmpumdlltd2 << 18) | ((uint32_t)wfcmmdllrstntd2 << 16) | ((uint32_t)wfcmmdllrstntd3 << 13) | ((uint32_t)wfpdtd0 << 11) | ((uint32_t)wflna5gpreampmainen << 10) | ((uint32_t)wflna5gimgcalen << 7) | ((uint32_t)wflna5gpreampregvbit << 4) | ((uint32_t)wflna5gpreampcgvbit << 0));
}

/**
 * @brief Unpacks REG_14's fields from current value of the REG_14 register.
 *
 * Reads the REG_14 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrfpllvctrlthh - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllvctrlthl - Will be populated with the current value of this field from the register.
 * @param[out] wfcmpumdlltd2 - Will be populated with the current value of this field from the register.
 * @param[out] wfcmmdllrstntd2 - Will be populated with the current value of this field from the register.
 * @param[out] wfcmmdllrstntd3 - Will be populated with the current value of this field from the register.
 * @param[out] wfpdtd0 - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gpreampmainen - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gpreampgbit - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gpreampbypassen - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gimgcalen - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gpreampregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gpreampcgvbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_14_unpack(uint8_t* wfrfpllvctrlthh, uint8_t* wfrfpllvctrlthl, uint8_t* wfcmpumdlltd2, uint8_t* wfcmmdllrstntd2, uint8_t* wfcmmdllrstntd3, uint8_t* wfpdtd0, uint8_t* wflna5gpreampmainen, uint8_t* wflna5gpreampgbit, uint8_t* wflna5gpreampbypassen, uint8_t* wflna5gimgcalen, uint8_t* wflna5gpreampregvbit, uint8_t* wflna5gpreampcgvbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);

    *wfrfpllvctrlthh = (localVal & ((uint32_t)0xFC000000)) >> 26;
    *wfrfpllvctrlthl = (localVal & ((uint32_t)0x03F00000)) >> 20;
    *wfcmpumdlltd2 = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *wfcmmdllrstntd2 = (localVal & ((uint32_t)0x00030000)) >> 16;
    *wfcmmdllrstntd3 = (localVal & ((uint32_t)0x0000E000)) >> 13;
    *wfpdtd0 = (localVal & ((uint32_t)0x00001800)) >> 11;
    *wflna5gpreampmainen = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wflna5gpreampgbit = (localVal & ((uint32_t)0x00000200)) >> 9;
    *wflna5gpreampbypassen = (localVal & ((uint32_t)0x00000100)) >> 8;
    *wflna5gimgcalen = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wflna5gpreampregvbit = (localVal & ((uint32_t)0x00000070)) >> 4;
    *wflna5gpreampcgvbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rfpll_vctrl_THH field in the REG_14 register.
 *
 * The REG_14 register will be read and the wf_rfpll_vctrl_THH field's value will be returned.
 *
 * @return The current value of the wf_rfpll_vctrl_THH field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_vctrl_thh_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0xFC000000)) >> 26);
}

/**
 * @brief Sets the wf_rfpll_vctrl_THH field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllvctrlthh - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_vctrl_thh_setf(uint8_t wfrfpllvctrlthh)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0xFC000000)) | (((uint32_t)wfrfpllvctrlthh << 26) & ((uint32_t)0xFC000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_vctrl_THL field in the REG_14 register.
 *
 * The REG_14 register will be read and the wf_rfpll_vctrl_THL field's value will be returned.
 *
 * @return The current value of the wf_rfpll_vctrl_THL field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_vctrl_thl_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x03F00000)) >> 20);
}

/**
 * @brief Sets the wf_rfpll_vctrl_THL field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllvctrlthl - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_vctrl_thl_setf(uint8_t wfrfpllvctrlthl)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0x03F00000)) | (((uint32_t)wfrfpllvctrlthl << 20) & ((uint32_t)0x03F00000)));
}

/**
 * @brief Returns the current value of the wfcm_pu_mdll_td2 field in the REG_14 register.
 *
 * The REG_14 register will be read and the wfcm_pu_mdll_td2 field's value will be returned.
 *
 * @return The current value of the wfcm_pu_mdll_td2 field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wfcm_pu_mdll_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the wfcm_pu_mdll_td2 field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfcmpumdlltd2 - The value to set the field to.
 */
__INLINE void wlan_rf_wfcm_pu_mdll_td_2_setf(uint8_t wfcmpumdlltd2)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)wfcmpumdlltd2 << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the wfcm_mdll_rstn_td2 field in the REG_14 register.
 *
 * The REG_14 register will be read and the wfcm_mdll_rstn_td2 field's value will be returned.
 *
 * @return The current value of the wfcm_mdll_rstn_td2 field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wfcm_mdll_rstn_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

/**
 * @brief Sets the wfcm_mdll_rstn_td2 field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfcmmdllrstntd2 - The value to set the field to.
 */
__INLINE void wlan_rf_wfcm_mdll_rstn_td_2_setf(uint8_t wfcmmdllrstntd2)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0x00030000)) | (((uint32_t)wfcmmdllrstntd2 << 16) & ((uint32_t)0x00030000)));
}

/**
 * @brief Returns the current value of the wfcm_mdll_rstn_td3 field in the REG_14 register.
 *
 * The REG_14 register will be read and the wfcm_mdll_rstn_td3 field's value will be returned.
 *
 * @return The current value of the wfcm_mdll_rstn_td3 field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wfcm_mdll_rstn_td_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x0000E000)) >> 13);
}

/**
 * @brief Sets the wfcm_mdll_rstn_td3 field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfcmmdllrstntd3 - The value to set the field to.
 */
__INLINE void wlan_rf_wfcm_mdll_rstn_td_3_setf(uint8_t wfcmmdllrstntd3)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0x0000E000)) | (((uint32_t)wfcmmdllrstntd3 << 13) & ((uint32_t)0x0000E000)));
}

/**
 * @brief Returns the current value of the wf_pd_td0 field in the REG_14 register.
 *
 * The REG_14 register will be read and the wf_pd_td0 field's value will be returned.
 *
 * @return The current value of the wf_pd_td0 field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wf_pd_td_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00001800)) >> 11);
}

/**
 * @brief Sets the wf_pd_td0 field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpdtd0 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pd_td_0_setf(uint8_t wfpdtd0)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0x00001800)) | (((uint32_t)wfpdtd0 << 11) & ((uint32_t)0x00001800)));
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_main_en field in the REG_14 register.
 *
 * The REG_14 register will be read and the wf_lna5g_preamp_main_en field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_main_en field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_main_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_lna5g_preamp_main_en field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflna5gpreampmainen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_5g_preamp_main_en_setf(uint8_t wflna5gpreampmainen)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wflna5gpreampmainen << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_gbit field in the REG_14 register.
 *
 * The REG_14 register will be read and the wf_lna5g_preamp_gbit field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_gbit field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_bypass_en field in the REG_14 register.
 *
 * The REG_14 register will be read and the wf_lna5g_preamp_bypass_en field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_bypass_en field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_bypass_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Returns the current value of the wf_lna5g_img_cal_en field in the REG_14 register.
 *
 * The REG_14 register will be read and the wf_lna5g_img_cal_en field's value will be returned.
 *
 * @return The current value of the wf_lna5g_img_cal_en field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_img_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_lna5g_img_cal_en field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflna5gimgcalen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_5g_img_cal_en_setf(uint8_t wflna5gimgcalen)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wflna5gimgcalen << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_reg_vbit field in the REG_14 register.
 *
 * The REG_14 register will be read and the wf_lna5g_preamp_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_reg_vbit field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

/**
 * @brief Sets the wf_lna5g_preamp_reg_vbit field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflna5gpreampregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_5g_preamp_reg_vbit_setf(uint8_t wflna5gpreampregvbit)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0x00000070)) | (((uint32_t)wflna5gpreampregvbit << 4) & ((uint32_t)0x00000070)));
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_cg_vbit field in the REG_14 register.
 *
 * The REG_14 register will be read and the wf_lna5g_preamp_cg_vbit field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_cg_vbit field in the REG_14 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_cg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the wf_lna5g_preamp_cg_vbit field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflna5gpreampcgvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_5g_preamp_cg_vbit_setf(uint8_t wflna5gpreampcgvbit)
{
    REG_PL_WR(WLAN_RF_REG_14_ADDR, (REG_PL_RD(WLAN_RF_REG_14_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)wflna5gpreampcgvbit << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name REG_18 register definitions
 * <table>
 * <caption id="REG_18_BF">REG_18 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:28 <td>wf_lna5g_preamp_ibias_bit <td>W <td>R <td>0xA
 * <tr><td>27 <td>wf_lna5g_preamp_aux_en <td>R <td>R/W <td>0
 * <tr><td>26:22 <td>wf_lna5g_preamp_aux_atten_bit <td>W <td>R <td>0x0
 * <tr><td>21 <td>wf_lna5g_preamp_lna_bias_en <td>R <td>R/W <td>1
 * <tr><td>20 <td>      wf_lna24g_en <td>R <td>R/W <td>1
 * <tr><td>19 <td>       wf_lna5g_en <td>R <td>R/W <td>0
 * <tr><td>18:17 <td>       wf_lna_gbit <td>W <td>R <td>0x3
 * <tr><td>16:13 <td>  wf_lna_ibias_bit <td>W <td>R <td>0xA
 * <tr><td>12:09 <td>    wf_lna_cg_vbit <td>R <td>R/W <td>0x5
 * <tr><td>08 <td>     wf_rmx_1st_en <td>W <td>R <td>0
 * <tr><td>07:04 <td>     wf_lna5g_cbit <td>W <td>R <td>0x7
 * <tr><td>03:00 <td>    wf_lna24g_cbit <td>W <td>R <td>0x7
 * </table>
 *
 * @{
 */

/// Address of the REG_18 register
#define WLAN_RF_REG_18_ADDR   0x40344018
/// Offset of the REG_18 register from the base address
#define WLAN_RF_REG_18_OFFSET 0x00000018
/// Index of the REG_18 register
#define WLAN_RF_REG_18_INDEX  0x00000006
/// Reset value of the REG_18 register
#define WLAN_RF_REG_18_RESET  0xA0374A77

/**
 * @brief Returns the current value of the REG_18 register.
 * The REG_18 register will be read and its value returned.
 * @return The current value of the REG_18 register.
 */
__INLINE uint32_t wlan_rf_reg_18_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_18_ADDR);
}

/**
 * @brief Sets the REG_18 register to a value.
 * The REG_18 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_18_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_18_ADDR, value);
}

// field definitions
/// WF_LNA_5G_PREAMP_IBIAS_BIT field mask
#define WLAN_RF_WF_LNA_5G_PREAMP_IBIAS_BIT_MASK       ((uint32_t)0xF0000000)
/// WF_LNA_5G_PREAMP_IBIAS_BIT field LSB position
#define WLAN_RF_WF_LNA_5G_PREAMP_IBIAS_BIT_LSB        28
/// WF_LNA_5G_PREAMP_IBIAS_BIT field width
#define WLAN_RF_WF_LNA_5G_PREAMP_IBIAS_BIT_WIDTH      ((uint32_t)0x00000004)
/// WF_LNA_5G_PREAMP_AUX_EN field bit
#define WLAN_RF_WF_LNA_5G_PREAMP_AUX_EN_BIT           ((uint32_t)0x08000000)
/// WF_LNA_5G_PREAMP_AUX_EN field position
#define WLAN_RF_WF_LNA_5G_PREAMP_AUX_EN_POS           27
/// WF_LNA_5G_PREAMP_AUX_ATTEN_BIT field mask
#define WLAN_RF_WF_LNA_5G_PREAMP_AUX_ATTEN_BIT_MASK   ((uint32_t)0x07C00000)
/// WF_LNA_5G_PREAMP_AUX_ATTEN_BIT field LSB position
#define WLAN_RF_WF_LNA_5G_PREAMP_AUX_ATTEN_BIT_LSB    22
/// WF_LNA_5G_PREAMP_AUX_ATTEN_BIT field width
#define WLAN_RF_WF_LNA_5G_PREAMP_AUX_ATTEN_BIT_WIDTH  ((uint32_t)0x00000005)
/// WF_LNA_5G_PREAMP_LNA_BIAS_EN field bit
#define WLAN_RF_WF_LNA_5G_PREAMP_LNA_BIAS_EN_BIT      ((uint32_t)0x00200000)
/// WF_LNA_5G_PREAMP_LNA_BIAS_EN field position
#define WLAN_RF_WF_LNA_5G_PREAMP_LNA_BIAS_EN_POS      21
/// WF_LNA_24G_EN field bit
#define WLAN_RF_WF_LNA_24G_EN_BIT                     ((uint32_t)0x00100000)
/// WF_LNA_24G_EN field position
#define WLAN_RF_WF_LNA_24G_EN_POS                     20
/// WF_LNA_5G_EN field bit
#define WLAN_RF_WF_LNA_5G_EN_BIT                      ((uint32_t)0x00080000)
/// WF_LNA_5G_EN field position
#define WLAN_RF_WF_LNA_5G_EN_POS                      19
/// WF_LNA_GBIT field mask
#define WLAN_RF_WF_LNA_GBIT_MASK                      ((uint32_t)0x00060000)
/// WF_LNA_GBIT field LSB position
#define WLAN_RF_WF_LNA_GBIT_LSB                       17
/// WF_LNA_GBIT field width
#define WLAN_RF_WF_LNA_GBIT_WIDTH                     ((uint32_t)0x00000002)
/// WF_LNA_IBIAS_BIT field mask
#define WLAN_RF_WF_LNA_IBIAS_BIT_MASK                 ((uint32_t)0x0001E000)
/// WF_LNA_IBIAS_BIT field LSB position
#define WLAN_RF_WF_LNA_IBIAS_BIT_LSB                  13
/// WF_LNA_IBIAS_BIT field width
#define WLAN_RF_WF_LNA_IBIAS_BIT_WIDTH                ((uint32_t)0x00000004)
/// WF_LNA_CG_VBIT field mask
#define WLAN_RF_WF_LNA_CG_VBIT_MASK                   ((uint32_t)0x00001E00)
/// WF_LNA_CG_VBIT field LSB position
#define WLAN_RF_WF_LNA_CG_VBIT_LSB                    9
/// WF_LNA_CG_VBIT field width
#define WLAN_RF_WF_LNA_CG_VBIT_WIDTH                  ((uint32_t)0x00000004)
/// WF_RMX__1ST_EN field bit
#define WLAN_RF_WF_RMX__1ST_EN_BIT                    ((uint32_t)0x00000100)
/// WF_RMX__1ST_EN field position
#define WLAN_RF_WF_RMX__1ST_EN_POS                    8
/// WF_LNA_5G_CBIT field mask
#define WLAN_RF_WF_LNA_5G_CBIT_MASK                   ((uint32_t)0x000000F0)
/// WF_LNA_5G_CBIT field LSB position
#define WLAN_RF_WF_LNA_5G_CBIT_LSB                    4
/// WF_LNA_5G_CBIT field width
#define WLAN_RF_WF_LNA_5G_CBIT_WIDTH                  ((uint32_t)0x00000004)
/// WF_LNA_24G_CBIT field mask
#define WLAN_RF_WF_LNA_24G_CBIT_MASK                  ((uint32_t)0x0000000F)
/// WF_LNA_24G_CBIT field LSB position
#define WLAN_RF_WF_LNA_24G_CBIT_LSB                   0
/// WF_LNA_24G_CBIT field width
#define WLAN_RF_WF_LNA_24G_CBIT_WIDTH                 ((uint32_t)0x00000004)

/// WF_LNA_5G_PREAMP_IBIAS_BIT field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_IBIAS_BIT_RST        0xA
/// WF_LNA_5G_PREAMP_AUX_EN field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_AUX_EN_RST           0x0
/// WF_LNA_5G_PREAMP_AUX_ATTEN_BIT field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_AUX_ATTEN_BIT_RST    0x0
/// WF_LNA_5G_PREAMP_LNA_BIAS_EN field reset value
#define WLAN_RF_WF_LNA_5G_PREAMP_LNA_BIAS_EN_RST      0x1
/// WF_LNA_24G_EN field reset value
#define WLAN_RF_WF_LNA_24G_EN_RST                     0x1
/// WF_LNA_5G_EN field reset value
#define WLAN_RF_WF_LNA_5G_EN_RST                      0x0
/// WF_LNA_GBIT field reset value
#define WLAN_RF_WF_LNA_GBIT_RST                       0x3
/// WF_LNA_IBIAS_BIT field reset value
#define WLAN_RF_WF_LNA_IBIAS_BIT_RST                  0xA
/// WF_LNA_CG_VBIT field reset value
#define WLAN_RF_WF_LNA_CG_VBIT_RST                    0x5
/// WF_RMX__1ST_EN field reset value
#define WLAN_RF_WF_RMX__1ST_EN_RST                    0x0
/// WF_LNA_5G_CBIT field reset value
#define WLAN_RF_WF_LNA_5G_CBIT_RST                    0x7
/// WF_LNA_24G_CBIT field reset value
#define WLAN_RF_WF_LNA_24G_CBIT_RST                   0x7

/**
 * @brief Constructs a value for the REG_18 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wflna5gpreampauxen - The value to use for the wf_lna5g_preamp_aux_en field.
 * @param[in] wflna5gpreamplnabiasen - The value to use for the wf_lna5g_preamp_lna_bias_en field.
 * @param[in] wflna24gen - The value to use for the wf_lna24g_en field.
 * @param[in] wflna5gen - The value to use for the wf_lna5g_en field.
 * @param[in] wflnacgvbit - The value to use for the wf_lna_cg_vbit field.
 */
__INLINE void wlan_rf_reg_18_pack(uint8_t wflna5gpreampauxen, uint8_t wflna5gpreamplnabiasen, uint8_t wflna24gen, uint8_t wflna5gen, uint8_t wflnacgvbit)
{
    REG_PL_WR(WLAN_RF_REG_18_ADDR,  ((uint32_t)wflna5gpreampauxen << 27) | ((uint32_t)wflna5gpreamplnabiasen << 21) | ((uint32_t)wflna24gen << 20) | ((uint32_t)wflna5gen << 19) | ((uint32_t)wflnacgvbit << 9));
}

/**
 * @brief Unpacks REG_18's fields from current value of the REG_18 register.
 *
 * Reads the REG_18 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wflna5gpreampibiasbit - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gpreampauxen - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gpreampauxattenbit - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gpreamplnabiasen - Will be populated with the current value of this field from the register.
 * @param[out] wflna24gen - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gen - Will be populated with the current value of this field from the register.
 * @param[out] wflnagbit - Will be populated with the current value of this field from the register.
 * @param[out] wflnaibiasbit - Will be populated with the current value of this field from the register.
 * @param[out] wflnacgvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmx1sten - Will be populated with the current value of this field from the register.
 * @param[out] wflna5gcbit - Will be populated with the current value of this field from the register.
 * @param[out] wflna24gcbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_18_unpack(uint8_t* wflna5gpreampibiasbit, uint8_t* wflna5gpreampauxen, uint8_t* wflna5gpreampauxattenbit, uint8_t* wflna5gpreamplnabiasen, uint8_t* wflna24gen, uint8_t* wflna5gen, uint8_t* wflnagbit, uint8_t* wflnaibiasbit, uint8_t* wflnacgvbit, uint8_t* wfrmx1sten, uint8_t* wflna5gcbit, uint8_t* wflna24gcbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);

    *wflna5gpreampibiasbit = (localVal & ((uint32_t)0xF0000000)) >> 28;
    *wflna5gpreampauxen = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wflna5gpreampauxattenbit = (localVal & ((uint32_t)0x07C00000)) >> 22;
    *wflna5gpreamplnabiasen = (localVal & ((uint32_t)0x00200000)) >> 21;
    *wflna24gen = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wflna5gen = (localVal & ((uint32_t)0x00080000)) >> 19;
    *wflnagbit = (localVal & ((uint32_t)0x00060000)) >> 17;
    *wflnaibiasbit = (localVal & ((uint32_t)0x0001E000)) >> 13;
    *wflnacgvbit = (localVal & ((uint32_t)0x00001E00)) >> 9;
    *wfrmx1sten = (localVal & ((uint32_t)0x00000100)) >> 8;
    *wflna5gcbit = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *wflna24gcbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_ibias_bit field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna5g_preamp_ibias_bit field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_ibias_bit field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_ibias_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0xF0000000)) >> 28);
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_aux_en field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna5g_preamp_aux_en field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_aux_en field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_aux_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_lna5g_preamp_aux_en field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflna5gpreampauxen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_5g_preamp_aux_en_setf(uint8_t wflna5gpreampauxen)
{
    REG_PL_WR(WLAN_RF_REG_18_ADDR, (REG_PL_RD(WLAN_RF_REG_18_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wflna5gpreampauxen << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_aux_atten_bit field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna5g_preamp_aux_atten_bit field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_aux_atten_bit field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_aux_atten_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x07C00000)) >> 22);
}

/**
 * @brief Returns the current value of the wf_lna5g_preamp_lna_bias_en field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna5g_preamp_lna_bias_en field's value will be returned.
 *
 * @return The current value of the wf_lna5g_preamp_lna_bias_en field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_preamp_lna_bias_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Sets the wf_lna5g_preamp_lna_bias_en field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflna5gpreamplnabiasen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_5g_preamp_lna_bias_en_setf(uint8_t wflna5gpreamplnabiasen)
{
    REG_PL_WR(WLAN_RF_REG_18_ADDR, (REG_PL_RD(WLAN_RF_REG_18_ADDR) & ~((uint32_t)0x00200000)) | (((uint32_t)wflna5gpreamplnabiasen << 21) & ((uint32_t)0x00200000)));
}

/**
 * @brief Returns the current value of the wf_lna24g_en field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna24g_en field's value will be returned.
 *
 * @return The current value of the wf_lna24g_en field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_24g_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_lna24g_en field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflna24gen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_24g_en_setf(uint8_t wflna24gen)
{
    REG_PL_WR(WLAN_RF_REG_18_ADDR, (REG_PL_RD(WLAN_RF_REG_18_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wflna24gen << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the wf_lna5g_en field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna5g_en field's value will be returned.
 *
 * @return The current value of the wf_lna5g_en field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the wf_lna5g_en field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflna5gen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_5g_en_setf(uint8_t wflna5gen)
{
    REG_PL_WR(WLAN_RF_REG_18_ADDR, (REG_PL_RD(WLAN_RF_REG_18_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)wflna5gen << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the wf_lna_gbit field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna_gbit field's value will be returned.
 *
 * @return The current value of the wf_lna_gbit field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00060000)) >> 17);
}

/**
 * @brief Returns the current value of the wf_lna_ibias_bit field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna_ibias_bit field's value will be returned.
 *
 * @return The current value of the wf_lna_ibias_bit field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_ibias_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x0001E000)) >> 13);
}

/**
 * @brief Returns the current value of the wf_lna_cg_vbit field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna_cg_vbit field's value will be returned.
 *
 * @return The current value of the wf_lna_cg_vbit field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_cg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00001E00)) >> 9);
}

/**
 * @brief Sets the wf_lna_cg_vbit field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnacgvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_cg_vbit_setf(uint8_t wflnacgvbit)
{
    REG_PL_WR(WLAN_RF_REG_18_ADDR, (REG_PL_RD(WLAN_RF_REG_18_ADDR) & ~((uint32_t)0x00001E00)) | (((uint32_t)wflnacgvbit << 9) & ((uint32_t)0x00001E00)));
}

/**
 * @brief Returns the current value of the wf_rmx_1st_en field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_rmx_1st_en field's value will be returned.
 *
 * @return The current value of the wf_rmx_1st_en field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx__1st_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Returns the current value of the wf_lna5g_cbit field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna5g_cbit field's value will be returned.
 *
 * @return The current value of the wf_lna5g_cbit field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_5g_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Returns the current value of the wf_lna24g_cbit field in the REG_18 register.
 *
 * The REG_18 register will be read and the wf_lna24g_cbit field's value will be returned.
 *
 * @return The current value of the wf_lna24g_cbit field in the REG_18 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_24g_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/// @}

/**
 * @name REG_1C register definitions
 * <table>
 * <caption id="REG_1C_BF">REG_1C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>28 <td> wf_lna24g_cap_sel <td>W <td>R <td>0
 * <tr><td>27 <td>   wf_lna_iref_sel <td>R <td>R/W <td>0
 * <tr><td>26:24 <td>   wf_lna_reg_vbit <td>R <td>R/W <td>0x3
 * <tr><td>23:17 <td>wf_rmx_logen_sf_avdd_sw_bit <td>R <td>R/W <td>0x19
 * <tr><td>16 <td>wf_rmx_logen_vref_sel_self_bias <td>R <td>R/W <td>1
 * <tr><td>15:13 <td>wf_rmx_logen_reg_vbit <td>R <td>R/W <td>0x4
 * <tr><td>12 <td>wf_rmx_logen_psw_mode <td>R <td>R/W <td>1
 * <tr><td>11 <td>wf_rmx_logen_sf_mode <td>R <td>R/W <td>0
 * <tr><td>10 <td>       wf_rmx5g_en <td>R <td>R/W <td>0
 * <tr><td>09 <td>   wf_rmx5g_dir_en <td>W <td>R <td>0
 * <tr><td>08 <td>      wf_rmx24g_en <td>R <td>R/W <td>1
 * <tr><td>07 <td>wf_rmx_logen_band_sel <td>R <td>R/W <td>0
 * <tr><td>06 <td>  wf_rmx_lobias_en <td>R <td>R/W <td>1
 * <tr><td>05:03 <td>wf_rmx_lobias_vbit <td>R <td>R/W <td>0x3
 * <tr><td>02:00 <td>  wf_rmx_cload_bit <td>W <td>R <td>0x2
 * </table>
 *
 * @{
 */

/// Address of the REG_1C register
#define WLAN_RF_REG_1C_ADDR   0x4034401C
/// Offset of the REG_1C register from the base address
#define WLAN_RF_REG_1C_OFFSET 0x0000001C
/// Index of the REG_1C register
#define WLAN_RF_REG_1C_INDEX  0x00000007
/// Reset value of the REG_1C register
#define WLAN_RF_REG_1C_RESET  0x0333915A

/**
 * @brief Returns the current value of the REG_1C register.
 * The REG_1C register will be read and its value returned.
 * @return The current value of the REG_1C register.
 */
__INLINE uint32_t wlan_rf_reg_1c_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_1C_ADDR);
}

/**
 * @brief Sets the REG_1C register to a value.
 * The REG_1C register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_1c_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, value);
}

// field definitions
/// WF_LNA_24G_CAP_SEL field bit
#define WLAN_RF_WF_LNA_24G_CAP_SEL_BIT                 ((uint32_t)0x10000000)
/// WF_LNA_24G_CAP_SEL field position
#define WLAN_RF_WF_LNA_24G_CAP_SEL_POS                 28
/// WF_LNA_IREF_SEL field bit
#define WLAN_RF_WF_LNA_IREF_SEL_BIT                    ((uint32_t)0x08000000)
/// WF_LNA_IREF_SEL field position
#define WLAN_RF_WF_LNA_IREF_SEL_POS                    27
/// WF_LNA_REG_VBIT field mask
#define WLAN_RF_WF_LNA_REG_VBIT_MASK                   ((uint32_t)0x07000000)
/// WF_LNA_REG_VBIT field LSB position
#define WLAN_RF_WF_LNA_REG_VBIT_LSB                    24
/// WF_LNA_REG_VBIT field width
#define WLAN_RF_WF_LNA_REG_VBIT_WIDTH                  ((uint32_t)0x00000003)
/// WF_RMX_LOGEN_SF_AVDD_SW_BIT field mask
#define WLAN_RF_WF_RMX_LOGEN_SF_AVDD_SW_BIT_MASK       ((uint32_t)0x00FE0000)
/// WF_RMX_LOGEN_SF_AVDD_SW_BIT field LSB position
#define WLAN_RF_WF_RMX_LOGEN_SF_AVDD_SW_BIT_LSB        17
/// WF_RMX_LOGEN_SF_AVDD_SW_BIT field width
#define WLAN_RF_WF_RMX_LOGEN_SF_AVDD_SW_BIT_WIDTH      ((uint32_t)0x00000007)
/// WF_RMX_LOGEN_VREF_SEL_SELF_BIAS field bit
#define WLAN_RF_WF_RMX_LOGEN_VREF_SEL_SELF_BIAS_BIT    ((uint32_t)0x00010000)
/// WF_RMX_LOGEN_VREF_SEL_SELF_BIAS field position
#define WLAN_RF_WF_RMX_LOGEN_VREF_SEL_SELF_BIAS_POS    16
/// WF_RMX_LOGEN_REG_VBIT field mask
#define WLAN_RF_WF_RMX_LOGEN_REG_VBIT_MASK             ((uint32_t)0x0000E000)
/// WF_RMX_LOGEN_REG_VBIT field LSB position
#define WLAN_RF_WF_RMX_LOGEN_REG_VBIT_LSB              13
/// WF_RMX_LOGEN_REG_VBIT field width
#define WLAN_RF_WF_RMX_LOGEN_REG_VBIT_WIDTH            ((uint32_t)0x00000003)
/// WF_RMX_LOGEN_PSW_MODE field bit
#define WLAN_RF_WF_RMX_LOGEN_PSW_MODE_BIT              ((uint32_t)0x00001000)
/// WF_RMX_LOGEN_PSW_MODE field position
#define WLAN_RF_WF_RMX_LOGEN_PSW_MODE_POS              12
/// WF_RMX_LOGEN_SF_MODE field bit
#define WLAN_RF_WF_RMX_LOGEN_SF_MODE_BIT               ((uint32_t)0x00000800)
/// WF_RMX_LOGEN_SF_MODE field position
#define WLAN_RF_WF_RMX_LOGEN_SF_MODE_POS               11
/// WF_RMX_5G_EN field bit
#define WLAN_RF_WF_RMX_5G_EN_BIT                       ((uint32_t)0x00000400)
/// WF_RMX_5G_EN field position
#define WLAN_RF_WF_RMX_5G_EN_POS                       10
/// WF_RMX_5G_DIR_EN field bit
#define WLAN_RF_WF_RMX_5G_DIR_EN_BIT                   ((uint32_t)0x00000200)
/// WF_RMX_5G_DIR_EN field position
#define WLAN_RF_WF_RMX_5G_DIR_EN_POS                   9
/// WF_RMX_24G_EN field bit
#define WLAN_RF_WF_RMX_24G_EN_BIT                      ((uint32_t)0x00000100)
/// WF_RMX_24G_EN field position
#define WLAN_RF_WF_RMX_24G_EN_POS                      8
/// WF_RMX_LOGEN_BAND_SEL field bit
#define WLAN_RF_WF_RMX_LOGEN_BAND_SEL_BIT              ((uint32_t)0x00000080)
/// WF_RMX_LOGEN_BAND_SEL field position
#define WLAN_RF_WF_RMX_LOGEN_BAND_SEL_POS              7
/// WF_RMX_LOBIAS_EN field bit
#define WLAN_RF_WF_RMX_LOBIAS_EN_BIT                   ((uint32_t)0x00000040)
/// WF_RMX_LOBIAS_EN field position
#define WLAN_RF_WF_RMX_LOBIAS_EN_POS                   6
/// WF_RMX_LOBIAS_VBIT field mask
#define WLAN_RF_WF_RMX_LOBIAS_VBIT_MASK                ((uint32_t)0x00000038)
/// WF_RMX_LOBIAS_VBIT field LSB position
#define WLAN_RF_WF_RMX_LOBIAS_VBIT_LSB                 3
/// WF_RMX_LOBIAS_VBIT field width
#define WLAN_RF_WF_RMX_LOBIAS_VBIT_WIDTH               ((uint32_t)0x00000003)
/// WF_RMX_CLOAD_BIT field mask
#define WLAN_RF_WF_RMX_CLOAD_BIT_MASK                  ((uint32_t)0x00000007)
/// WF_RMX_CLOAD_BIT field LSB position
#define WLAN_RF_WF_RMX_CLOAD_BIT_LSB                   0
/// WF_RMX_CLOAD_BIT field width
#define WLAN_RF_WF_RMX_CLOAD_BIT_WIDTH                 ((uint32_t)0x00000003)

/// WF_LNA_24G_CAP_SEL field reset value
#define WLAN_RF_WF_LNA_24G_CAP_SEL_RST                 0x0
/// WF_LNA_IREF_SEL field reset value
#define WLAN_RF_WF_LNA_IREF_SEL_RST                    0x0
/// WF_LNA_REG_VBIT field reset value
#define WLAN_RF_WF_LNA_REG_VBIT_RST                    0x3
/// WF_RMX_LOGEN_SF_AVDD_SW_BIT field reset value
#define WLAN_RF_WF_RMX_LOGEN_SF_AVDD_SW_BIT_RST        0x19
/// WF_RMX_LOGEN_VREF_SEL_SELF_BIAS field reset value
#define WLAN_RF_WF_RMX_LOGEN_VREF_SEL_SELF_BIAS_RST    0x1
/// WF_RMX_LOGEN_REG_VBIT field reset value
#define WLAN_RF_WF_RMX_LOGEN_REG_VBIT_RST              0x4
/// WF_RMX_LOGEN_PSW_MODE field reset value
#define WLAN_RF_WF_RMX_LOGEN_PSW_MODE_RST              0x1
/// WF_RMX_LOGEN_SF_MODE field reset value
#define WLAN_RF_WF_RMX_LOGEN_SF_MODE_RST               0x0
/// WF_RMX_5G_EN field reset value
#define WLAN_RF_WF_RMX_5G_EN_RST                       0x0
/// WF_RMX_5G_DIR_EN field reset value
#define WLAN_RF_WF_RMX_5G_DIR_EN_RST                   0x0
/// WF_RMX_24G_EN field reset value
#define WLAN_RF_WF_RMX_24G_EN_RST                      0x1
/// WF_RMX_LOGEN_BAND_SEL field reset value
#define WLAN_RF_WF_RMX_LOGEN_BAND_SEL_RST              0x0
/// WF_RMX_LOBIAS_EN field reset value
#define WLAN_RF_WF_RMX_LOBIAS_EN_RST                   0x1
/// WF_RMX_LOBIAS_VBIT field reset value
#define WLAN_RF_WF_RMX_LOBIAS_VBIT_RST                 0x3
/// WF_RMX_CLOAD_BIT field reset value
#define WLAN_RF_WF_RMX_CLOAD_BIT_RST                   0x2

/**
 * @brief Constructs a value for the REG_1C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wflnairefsel - The value to use for the wf_lna_iref_sel field.
 * @param[in] wflnaregvbit - The value to use for the wf_lna_reg_vbit field.
 * @param[in] wfrmxlogensfavddswbit - The value to use for the wf_rmx_logen_sf_avdd_sw_bit field.
 * @param[in] wfrmxlogenvrefselselfbias - The value to use for the wf_rmx_logen_vref_sel_self_bias field.
 * @param[in] wfrmxlogenregvbit - The value to use for the wf_rmx_logen_reg_vbit field.
 * @param[in] wfrmxlogenpswmode - The value to use for the wf_rmx_logen_psw_mode field.
 * @param[in] wfrmxlogensfmode - The value to use for the wf_rmx_logen_sf_mode field.
 * @param[in] wfrmx5gen - The value to use for the wf_rmx5g_en field.
 * @param[in] wfrmx24gen - The value to use for the wf_rmx24g_en field.
 * @param[in] wfrmxlogenbandsel - The value to use for the wf_rmx_logen_band_sel field.
 * @param[in] wfrmxlobiasen - The value to use for the wf_rmx_lobias_en field.
 * @param[in] wfrmxlobiasvbit - The value to use for the wf_rmx_lobias_vbit field.
 */
__INLINE void wlan_rf_reg_1c_pack(uint8_t wflnairefsel, uint8_t wflnaregvbit, uint8_t wfrmxlogensfavddswbit, uint8_t wfrmxlogenvrefselselfbias, uint8_t wfrmxlogenregvbit, uint8_t wfrmxlogenpswmode, uint8_t wfrmxlogensfmode, uint8_t wfrmx5gen, uint8_t wfrmx24gen, uint8_t wfrmxlogenbandsel, uint8_t wfrmxlobiasen, uint8_t wfrmxlobiasvbit)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR,  ((uint32_t)wflnairefsel << 27) | ((uint32_t)wflnaregvbit << 24) | ((uint32_t)wfrmxlogensfavddswbit << 17) | ((uint32_t)wfrmxlogenvrefselselfbias << 16) | ((uint32_t)wfrmxlogenregvbit << 13) | ((uint32_t)wfrmxlogenpswmode << 12) | ((uint32_t)wfrmxlogensfmode << 11) | ((uint32_t)wfrmx5gen << 10) | ((uint32_t)wfrmx24gen << 8) | ((uint32_t)wfrmxlogenbandsel << 7) | ((uint32_t)wfrmxlobiasen << 6) | ((uint32_t)wfrmxlobiasvbit << 3));
}

/**
 * @brief Unpacks REG_1C's fields from current value of the REG_1C register.
 *
 * Reads the REG_1C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wflna24gcapsel - Will be populated with the current value of this field from the register.
 * @param[out] wflnairefsel - Will be populated with the current value of this field from the register.
 * @param[out] wflnaregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogensfavddswbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogenvrefselselfbias - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogenregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogenpswmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogensfmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrmx5gen - Will be populated with the current value of this field from the register.
 * @param[out] wfrmx5gdiren - Will be populated with the current value of this field from the register.
 * @param[out] wfrmx24gen - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogenbandsel - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlobiasen - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlobiasvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxcloadbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_1c_unpack(uint8_t* wflna24gcapsel, uint8_t* wflnairefsel, uint8_t* wflnaregvbit, uint8_t* wfrmxlogensfavddswbit, uint8_t* wfrmxlogenvrefselselfbias, uint8_t* wfrmxlogenregvbit, uint8_t* wfrmxlogenpswmode, uint8_t* wfrmxlogensfmode, uint8_t* wfrmx5gen, uint8_t* wfrmx5gdiren, uint8_t* wfrmx24gen, uint8_t* wfrmxlogenbandsel, uint8_t* wfrmxlobiasen, uint8_t* wfrmxlobiasvbit, uint8_t* wfrmxcloadbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);

    *wflna24gcapsel = (localVal & ((uint32_t)0x10000000)) >> 28;
    *wflnairefsel = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wflnaregvbit = (localVal & ((uint32_t)0x07000000)) >> 24;
    *wfrmxlogensfavddswbit = (localVal & ((uint32_t)0x00FE0000)) >> 17;
    *wfrmxlogenvrefselselfbias = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wfrmxlogenregvbit = (localVal & ((uint32_t)0x0000E000)) >> 13;
    *wfrmxlogenpswmode = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wfrmxlogensfmode = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wfrmx5gen = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfrmx5gdiren = (localVal & ((uint32_t)0x00000200)) >> 9;
    *wfrmx24gen = (localVal & ((uint32_t)0x00000100)) >> 8;
    *wfrmxlogenbandsel = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wfrmxlobiasen = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wfrmxlobiasvbit = (localVal & ((uint32_t)0x00000038)) >> 3;
    *wfrmxcloadbit = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the wf_lna24g_cap_sel field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_lna24g_cap_sel field's value will be returned.
 *
 * @return The current value of the wf_lna24g_cap_sel field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_lna_24g_cap_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Returns the current value of the wf_lna_iref_sel field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_lna_iref_sel field's value will be returned.
 *
 * @return The current value of the wf_lna_iref_sel field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_lna_iref_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_lna_iref_sel field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnairefsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_iref_sel_setf(uint8_t wflnairefsel)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wflnairefsel << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_lna_reg_vbit field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_lna_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_lna_reg_vbit field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_lna_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

/**
 * @brief Sets the wf_lna_reg_vbit field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnaregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_reg_vbit_setf(uint8_t wflnaregvbit)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x07000000)) | (((uint32_t)wflnaregvbit << 24) & ((uint32_t)0x07000000)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_sf_avdd_sw_bit field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx_logen_sf_avdd_sw_bit field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_sf_avdd_sw_bit field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_sf_avdd_sw_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00FE0000)) >> 17);
}

/**
 * @brief Sets the wf_rmx_logen_sf_avdd_sw_bit field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogensfavddswbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_sf_avdd_sw_bit_setf(uint8_t wfrmxlogensfavddswbit)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x00FE0000)) | (((uint32_t)wfrmxlogensfavddswbit << 17) & ((uint32_t)0x00FE0000)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_vref_sel_self_bias field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx_logen_vref_sel_self_bias field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_vref_sel_self_bias field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_vref_sel_self_bias_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_rmx_logen_vref_sel_self_bias field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogenvrefselselfbias - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_vref_sel_self_bias_setf(uint8_t wfrmxlogenvrefselselfbias)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wfrmxlogenvrefselselfbias << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_reg_vbit field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx_logen_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_reg_vbit field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x0000E000)) >> 13);
}

/**
 * @brief Sets the wf_rmx_logen_reg_vbit field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogenregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_reg_vbit_setf(uint8_t wfrmxlogenregvbit)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x0000E000)) | (((uint32_t)wfrmxlogenregvbit << 13) & ((uint32_t)0x0000E000)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_psw_mode field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx_logen_psw_mode field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_psw_mode field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_psw_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_rmx_logen_psw_mode field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogenpswmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_psw_mode_setf(uint8_t wfrmxlogenpswmode)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wfrmxlogenpswmode << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_sf_mode field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx_logen_sf_mode field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_sf_mode field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_sf_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_rmx_logen_sf_mode field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogensfmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_sf_mode_setf(uint8_t wfrmxlogensfmode)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wfrmxlogensfmode << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_rmx5g_en field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx5g_en field's value will be returned.
 *
 * @return The current value of the wf_rmx5g_en field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_5g_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_rmx5g_en field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmx5gen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_5g_en_setf(uint8_t wfrmx5gen)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfrmx5gen << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_rmx5g_dir_en field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx5g_dir_en field's value will be returned.
 *
 * @return The current value of the wf_rmx5g_dir_en field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_5g_dir_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Returns the current value of the wf_rmx24g_en field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx24g_en field's value will be returned.
 *
 * @return The current value of the wf_rmx24g_en field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_24g_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the wf_rmx24g_en field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmx24gen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_24g_en_setf(uint8_t wfrmx24gen)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)wfrmx24gen << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_band_sel field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx_logen_band_sel field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_band_sel field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_band_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_rmx_logen_band_sel field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogenbandsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_band_sel_setf(uint8_t wfrmxlogenbandsel)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wfrmxlogenbandsel << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_rmx_lobias_en field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx_lobias_en field's value will be returned.
 *
 * @return The current value of the wf_rmx_lobias_en field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_lobias_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the wf_rmx_lobias_en field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlobiasen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_lobias_en_setf(uint8_t wfrmxlobiasen)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)wfrmxlobiasen << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the wf_rmx_lobias_vbit field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx_lobias_vbit field's value will be returned.
 *
 * @return The current value of the wf_rmx_lobias_vbit field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_lobias_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000038)) >> 3);
}

/**
 * @brief Sets the wf_rmx_lobias_vbit field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlobiasvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_lobias_vbit_setf(uint8_t wfrmxlobiasvbit)
{
    REG_PL_WR(WLAN_RF_REG_1C_ADDR, (REG_PL_RD(WLAN_RF_REG_1C_ADDR) & ~((uint32_t)0x00000038)) | (((uint32_t)wfrmxlobiasvbit << 3) & ((uint32_t)0x00000038)));
}

/**
 * @brief Returns the current value of the wf_rmx_cload_bit field in the REG_1C register.
 *
 * The REG_1C register will be read and the wf_rmx_cload_bit field's value will be returned.
 *
 * @return The current value of the wf_rmx_cload_bit field in the REG_1C register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_cload_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/// @}

/**
 * @name REG_20 register definitions
 * <table>
 * <caption id="REG_20_BF">REG_20 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:28 <td>wf_rmx_logen_dll_reg_bit <td>R <td>R/W <td>0x7
 * <tr><td>27:24 <td>wf_rmx_logen_dll_fref_dly_bit <td>R <td>R/W <td>0x0
 * <tr><td>23:20 <td>wf_rmx_logen_dll_fbc_dly_bit <td>R <td>R/W <td>0x0
 * <tr><td>19 <td>         wf_tia_en <td>R <td>R/W <td>1
 * <tr><td>18 <td>     wf_tia_aux_en <td>R <td>R/W <td>0
 * <tr><td>17:15 <td>       wf_tia_gbit <td>W <td>R <td>0x7
 * <tr><td>14:10 <td>       wf_tia_ibit <td>W <td>R <td>0x19
 * <tr><td>09:07 <td>    wf_tia_bw_rbit <td>W <td>R <td>0x4
 * <tr><td>06:02 <td>    wf_tia_bw_cbit <td>W <td>R <td>0x1C
 * <tr><td>01 <td> wf_tia_op_lb_mode <td>W <td>R <td>0
 * <tr><td>00 <td> wf_tia_op_hp_mode <td>W <td>R <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_20 register
#define WLAN_RF_REG_20_ADDR   0x40344020
/// Offset of the REG_20 register from the base address
#define WLAN_RF_REG_20_OFFSET 0x00000020
/// Index of the REG_20 register
#define WLAN_RF_REG_20_INDEX  0x00000008
/// Reset value of the REG_20 register
#define WLAN_RF_REG_20_RESET  0x700BE670

/**
 * @brief Returns the current value of the REG_20 register.
 * The REG_20 register will be read and its value returned.
 * @return The current value of the REG_20 register.
 */
__INLINE uint32_t wlan_rf_reg_20_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_20_ADDR);
}

/**
 * @brief Sets the REG_20 register to a value.
 * The REG_20 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_20_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_20_ADDR, value);
}

// field definitions
/// WF_RMX_LOGEN_DLL_REG_BIT field mask
#define WLAN_RF_WF_RMX_LOGEN_DLL_REG_BIT_MASK        ((uint32_t)0xF0000000)
/// WF_RMX_LOGEN_DLL_REG_BIT field LSB position
#define WLAN_RF_WF_RMX_LOGEN_DLL_REG_BIT_LSB         28
/// WF_RMX_LOGEN_DLL_REG_BIT field width
#define WLAN_RF_WF_RMX_LOGEN_DLL_REG_BIT_WIDTH       ((uint32_t)0x00000004)
/// WF_RMX_LOGEN_DLL_FREF_DLY_BIT field mask
#define WLAN_RF_WF_RMX_LOGEN_DLL_FREF_DLY_BIT_MASK   ((uint32_t)0x0F000000)
/// WF_RMX_LOGEN_DLL_FREF_DLY_BIT field LSB position
#define WLAN_RF_WF_RMX_LOGEN_DLL_FREF_DLY_BIT_LSB    24
/// WF_RMX_LOGEN_DLL_FREF_DLY_BIT field width
#define WLAN_RF_WF_RMX_LOGEN_DLL_FREF_DLY_BIT_WIDTH  ((uint32_t)0x00000004)
/// WF_RMX_LOGEN_DLL_FBC_DLY_BIT field mask
#define WLAN_RF_WF_RMX_LOGEN_DLL_FBC_DLY_BIT_MASK    ((uint32_t)0x00F00000)
/// WF_RMX_LOGEN_DLL_FBC_DLY_BIT field LSB position
#define WLAN_RF_WF_RMX_LOGEN_DLL_FBC_DLY_BIT_LSB     20
/// WF_RMX_LOGEN_DLL_FBC_DLY_BIT field width
#define WLAN_RF_WF_RMX_LOGEN_DLL_FBC_DLY_BIT_WIDTH   ((uint32_t)0x00000004)
/// WF_TIA_EN field bit
#define WLAN_RF_WF_TIA_EN_BIT                        ((uint32_t)0x00080000)
/// WF_TIA_EN field position
#define WLAN_RF_WF_TIA_EN_POS                        19
/// WF_TIA_AUX_EN field bit
#define WLAN_RF_WF_TIA_AUX_EN_BIT                    ((uint32_t)0x00040000)
/// WF_TIA_AUX_EN field position
#define WLAN_RF_WF_TIA_AUX_EN_POS                    18
/// WF_TIA_GBIT field mask
#define WLAN_RF_WF_TIA_GBIT_MASK                     ((uint32_t)0x00038000)
/// WF_TIA_GBIT field LSB position
#define WLAN_RF_WF_TIA_GBIT_LSB                      15
/// WF_TIA_GBIT field width
#define WLAN_RF_WF_TIA_GBIT_WIDTH                    ((uint32_t)0x00000003)
/// WF_TIA_IBIT field mask
#define WLAN_RF_WF_TIA_IBIT_MASK                     ((uint32_t)0x00007C00)
/// WF_TIA_IBIT field LSB position
#define WLAN_RF_WF_TIA_IBIT_LSB                      10
/// WF_TIA_IBIT field width
#define WLAN_RF_WF_TIA_IBIT_WIDTH                    ((uint32_t)0x00000005)
/// WF_TIA_BW_RBIT field mask
#define WLAN_RF_WF_TIA_BW_RBIT_MASK                  ((uint32_t)0x00000380)
/// WF_TIA_BW_RBIT field LSB position
#define WLAN_RF_WF_TIA_BW_RBIT_LSB                   7
/// WF_TIA_BW_RBIT field width
#define WLAN_RF_WF_TIA_BW_RBIT_WIDTH                 ((uint32_t)0x00000003)
/// WF_TIA_BW_CBIT field mask
#define WLAN_RF_WF_TIA_BW_CBIT_MASK                  ((uint32_t)0x0000007C)
/// WF_TIA_BW_CBIT field LSB position
#define WLAN_RF_WF_TIA_BW_CBIT_LSB                   2
/// WF_TIA_BW_CBIT field width
#define WLAN_RF_WF_TIA_BW_CBIT_WIDTH                 ((uint32_t)0x00000005)
/// WF_TIA_OP_LB_MODE field bit
#define WLAN_RF_WF_TIA_OP_LB_MODE_BIT                ((uint32_t)0x00000002)
/// WF_TIA_OP_LB_MODE field position
#define WLAN_RF_WF_TIA_OP_LB_MODE_POS                1
/// WF_TIA_OP_HP_MODE field bit
#define WLAN_RF_WF_TIA_OP_HP_MODE_BIT                ((uint32_t)0x00000001)
/// WF_TIA_OP_HP_MODE field position
#define WLAN_RF_WF_TIA_OP_HP_MODE_POS                0

/// WF_RMX_LOGEN_DLL_REG_BIT field reset value
#define WLAN_RF_WF_RMX_LOGEN_DLL_REG_BIT_RST         0x7
/// WF_RMX_LOGEN_DLL_FREF_DLY_BIT field reset value
#define WLAN_RF_WF_RMX_LOGEN_DLL_FREF_DLY_BIT_RST    0x0
/// WF_RMX_LOGEN_DLL_FBC_DLY_BIT field reset value
#define WLAN_RF_WF_RMX_LOGEN_DLL_FBC_DLY_BIT_RST     0x0
/// WF_TIA_EN field reset value
#define WLAN_RF_WF_TIA_EN_RST                        0x1
/// WF_TIA_AUX_EN field reset value
#define WLAN_RF_WF_TIA_AUX_EN_RST                    0x0
/// WF_TIA_GBIT field reset value
#define WLAN_RF_WF_TIA_GBIT_RST                      0x7
/// WF_TIA_IBIT field reset value
#define WLAN_RF_WF_TIA_IBIT_RST                      0x19
/// WF_TIA_BW_RBIT field reset value
#define WLAN_RF_WF_TIA_BW_RBIT_RST                   0x4
/// WF_TIA_BW_CBIT field reset value
#define WLAN_RF_WF_TIA_BW_CBIT_RST                   0x1C
/// WF_TIA_OP_LB_MODE field reset value
#define WLAN_RF_WF_TIA_OP_LB_MODE_RST                0x0
/// WF_TIA_OP_HP_MODE field reset value
#define WLAN_RF_WF_TIA_OP_HP_MODE_RST                0x0

/**
 * @brief Constructs a value for the REG_20 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrmxlogendllregbit - The value to use for the wf_rmx_logen_dll_reg_bit field.
 * @param[in] wfrmxlogendllfrefdlybit - The value to use for the wf_rmx_logen_dll_fref_dly_bit field.
 * @param[in] wfrmxlogendllfbcdlybit - The value to use for the wf_rmx_logen_dll_fbc_dly_bit field.
 * @param[in] wftiaen - The value to use for the wf_tia_en field.
 * @param[in] wftiaauxen - The value to use for the wf_tia_aux_en field.
 */
__INLINE void wlan_rf_reg_20_pack(uint8_t wfrmxlogendllregbit, uint8_t wfrmxlogendllfrefdlybit, uint8_t wfrmxlogendllfbcdlybit, uint8_t wftiaen, uint8_t wftiaauxen)
{
    REG_PL_WR(WLAN_RF_REG_20_ADDR,  ((uint32_t)wfrmxlogendllregbit << 28) | ((uint32_t)wfrmxlogendllfrefdlybit << 24) | ((uint32_t)wfrmxlogendllfbcdlybit << 20) | ((uint32_t)wftiaen << 19) | ((uint32_t)wftiaauxen << 18));
}

/**
 * @brief Unpacks REG_20's fields from current value of the REG_20 register.
 *
 * Reads the REG_20 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrmxlogendllregbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogendllfrefdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlogendllfbcdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaen - Will be populated with the current value of this field from the register.
 * @param[out] wftiaauxen - Will be populated with the current value of this field from the register.
 * @param[out] wftiagbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaibit - Will be populated with the current value of this field from the register.
 * @param[out] wftiabwrbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiabwcbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaoplbmode - Will be populated with the current value of this field from the register.
 * @param[out] wftiaophpmode - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_20_unpack(uint8_t* wfrmxlogendllregbit, uint8_t* wfrmxlogendllfrefdlybit, uint8_t* wfrmxlogendllfbcdlybit, uint8_t* wftiaen, uint8_t* wftiaauxen, uint8_t* wftiagbit, uint8_t* wftiaibit, uint8_t* wftiabwrbit, uint8_t* wftiabwcbit, uint8_t* wftiaoplbmode, uint8_t* wftiaophpmode)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);

    *wfrmxlogendllregbit = (localVal & ((uint32_t)0xF0000000)) >> 28;
    *wfrmxlogendllfrefdlybit = (localVal & ((uint32_t)0x0F000000)) >> 24;
    *wfrmxlogendllfbcdlybit = (localVal & ((uint32_t)0x00F00000)) >> 20;
    *wftiaen = (localVal & ((uint32_t)0x00080000)) >> 19;
    *wftiaauxen = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wftiagbit = (localVal & ((uint32_t)0x00038000)) >> 15;
    *wftiaibit = (localVal & ((uint32_t)0x00007C00)) >> 10;
    *wftiabwrbit = (localVal & ((uint32_t)0x00000380)) >> 7;
    *wftiabwcbit = (localVal & ((uint32_t)0x0000007C)) >> 2;
    *wftiaoplbmode = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wftiaophpmode = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rmx_logen_dll_reg_bit field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_rmx_logen_dll_reg_bit field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_dll_reg_bit field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_dll_reg_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0xF0000000)) >> 28);
}

/**
 * @brief Sets the wf_rmx_logen_dll_reg_bit field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogendllregbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_dll_reg_bit_setf(uint8_t wfrmxlogendllregbit)
{
    REG_PL_WR(WLAN_RF_REG_20_ADDR, (REG_PL_RD(WLAN_RF_REG_20_ADDR) & ~((uint32_t)0xF0000000)) | (((uint32_t)wfrmxlogendllregbit << 28) & ((uint32_t)0xF0000000)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_dll_fref_dly_bit field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_rmx_logen_dll_fref_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_dll_fref_dly_bit field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_dll_fref_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x0F000000)) >> 24);
}

/**
 * @brief Sets the wf_rmx_logen_dll_fref_dly_bit field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogendllfrefdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_dll_fref_dly_bit_setf(uint8_t wfrmxlogendllfrefdlybit)
{
    REG_PL_WR(WLAN_RF_REG_20_ADDR, (REG_PL_RD(WLAN_RF_REG_20_ADDR) & ~((uint32_t)0x0F000000)) | (((uint32_t)wfrmxlogendllfrefdlybit << 24) & ((uint32_t)0x0F000000)));
}

/**
 * @brief Returns the current value of the wf_rmx_logen_dll_fbc_dly_bit field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_rmx_logen_dll_fbc_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_rmx_logen_dll_fbc_dly_bit field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_logen_dll_fbc_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00F00000)) >> 20);
}

/**
 * @brief Sets the wf_rmx_logen_dll_fbc_dly_bit field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlogendllfbcdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_logen_dll_fbc_dly_bit_setf(uint8_t wfrmxlogendllfbcdlybit)
{
    REG_PL_WR(WLAN_RF_REG_20_ADDR, (REG_PL_RD(WLAN_RF_REG_20_ADDR) & ~((uint32_t)0x00F00000)) | (((uint32_t)wfrmxlogendllfbcdlybit << 20) & ((uint32_t)0x00F00000)));
}

/**
 * @brief Returns the current value of the wf_tia_en field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_tia_en field's value will be returned.
 *
 * @return The current value of the wf_tia_en field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the wf_tia_en field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_en_setf(uint8_t wftiaen)
{
    REG_PL_WR(WLAN_RF_REG_20_ADDR, (REG_PL_RD(WLAN_RF_REG_20_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)wftiaen << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the wf_tia_aux_en field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_tia_aux_en field's value will be returned.
 *
 * @return The current value of the wf_tia_aux_en field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_aux_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_tia_aux_en field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaauxen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_aux_en_setf(uint8_t wftiaauxen)
{
    REG_PL_WR(WLAN_RF_REG_20_ADDR, (REG_PL_RD(WLAN_RF_REG_20_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wftiaauxen << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_tia_gbit field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_tia_gbit field's value will be returned.
 *
 * @return The current value of the wf_tia_gbit field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00038000)) >> 15);
}

/**
 * @brief Returns the current value of the wf_tia_ibit field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_tia_ibit field's value will be returned.
 *
 * @return The current value of the wf_tia_ibit field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00007C00)) >> 10);
}

/**
 * @brief Returns the current value of the wf_tia_bw_rbit field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_tia_bw_rbit field's value will be returned.
 *
 * @return The current value of the wf_tia_bw_rbit field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_bw_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000380)) >> 7);
}

/**
 * @brief Returns the current value of the wf_tia_bw_cbit field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_tia_bw_cbit field's value will be returned.
 *
 * @return The current value of the wf_tia_bw_cbit field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_bw_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x0000007C)) >> 2);
}

/**
 * @brief Returns the current value of the wf_tia_op_lb_mode field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_tia_op_lb_mode field's value will be returned.
 *
 * @return The current value of the wf_tia_op_lb_mode field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_op_lb_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Returns the current value of the wf_tia_op_hp_mode field in the REG_20 register.
 *
 * The REG_20 register will be read and the wf_tia_op_hp_mode field's value will be returned.
 *
 * @return The current value of the wf_tia_op_hp_mode field in the REG_20 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_op_hp_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/// @}

/**
 * @name REG_24 register definitions
 * <table>
 * <caption id="REG_24_BF">REG_24 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:27 <td>   wf_tia_vcm_vbit <td>R <td>R/W <td>0x3
 * <tr><td>26:24 <td>wf_tia_aux_input_sel <td>R <td>R/W <td>0x0
 * <tr><td>23:21 <td>   wf_tia_aux_gbit <td>W <td>R <td>0x3
 * <tr><td>20:16 <td>   wf_tia_aux_ibit <td>W <td>R <td>0x19
 * <tr><td>15:11 <td> wf_tia_aux_bw_bit <td>W <td>R <td>0x1D
 * <tr><td>10:08 <td>wf_tia_aux_mil_cbit <td>W <td>R <td>0x4
 * <tr><td>07:05 <td>wf_tia_aux_mil_rbit <td>W <td>R <td>0x4
 * <tr><td>04:02 <td> wf_tia_aux_q_rbit <td>W <td>R <td>0x3
 * <tr><td>01:00 <td>wf_tia_vcm_ldo_vbit <td>R <td>R/W <td>0x1
 * </table>
 *
 * @{
 */

/// Address of the REG_24 register
#define WLAN_RF_REG_24_ADDR   0x40344024
/// Offset of the REG_24 register from the base address
#define WLAN_RF_REG_24_OFFSET 0x00000024
/// Index of the REG_24 register
#define WLAN_RF_REG_24_INDEX  0x00000009
/// Reset value of the REG_24 register
#define WLAN_RF_REG_24_RESET  0x1879EC8D

/**
 * @brief Returns the current value of the REG_24 register.
 * The REG_24 register will be read and its value returned.
 * @return The current value of the REG_24 register.
 */
__INLINE uint32_t wlan_rf_reg_24_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_24_ADDR);
}

/**
 * @brief Sets the REG_24 register to a value.
 * The REG_24 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_24_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_24_ADDR, value);
}

// field definitions
/// WF_TIA_VCM_VBIT field mask
#define WLAN_RF_WF_TIA_VCM_VBIT_MASK        ((uint32_t)0x38000000)
/// WF_TIA_VCM_VBIT field LSB position
#define WLAN_RF_WF_TIA_VCM_VBIT_LSB         27
/// WF_TIA_VCM_VBIT field width
#define WLAN_RF_WF_TIA_VCM_VBIT_WIDTH       ((uint32_t)0x00000003)
/// WF_TIA_AUX_INPUT_SEL field mask
#define WLAN_RF_WF_TIA_AUX_INPUT_SEL_MASK   ((uint32_t)0x07000000)
/// WF_TIA_AUX_INPUT_SEL field LSB position
#define WLAN_RF_WF_TIA_AUX_INPUT_SEL_LSB    24
/// WF_TIA_AUX_INPUT_SEL field width
#define WLAN_RF_WF_TIA_AUX_INPUT_SEL_WIDTH  ((uint32_t)0x00000003)
/// WF_TIA_AUX_GBIT field mask
#define WLAN_RF_WF_TIA_AUX_GBIT_MASK        ((uint32_t)0x00E00000)
/// WF_TIA_AUX_GBIT field LSB position
#define WLAN_RF_WF_TIA_AUX_GBIT_LSB         21
/// WF_TIA_AUX_GBIT field width
#define WLAN_RF_WF_TIA_AUX_GBIT_WIDTH       ((uint32_t)0x00000003)
/// WF_TIA_AUX_IBIT field mask
#define WLAN_RF_WF_TIA_AUX_IBIT_MASK        ((uint32_t)0x001F0000)
/// WF_TIA_AUX_IBIT field LSB position
#define WLAN_RF_WF_TIA_AUX_IBIT_LSB         16
/// WF_TIA_AUX_IBIT field width
#define WLAN_RF_WF_TIA_AUX_IBIT_WIDTH       ((uint32_t)0x00000005)
/// WF_TIA_AUX_BW_BIT field mask
#define WLAN_RF_WF_TIA_AUX_BW_BIT_MASK      ((uint32_t)0x0000F800)
/// WF_TIA_AUX_BW_BIT field LSB position
#define WLAN_RF_WF_TIA_AUX_BW_BIT_LSB       11
/// WF_TIA_AUX_BW_BIT field width
#define WLAN_RF_WF_TIA_AUX_BW_BIT_WIDTH     ((uint32_t)0x00000005)
/// WF_TIA_AUX_MIL_CBIT field mask
#define WLAN_RF_WF_TIA_AUX_MIL_CBIT_MASK    ((uint32_t)0x00000700)
/// WF_TIA_AUX_MIL_CBIT field LSB position
#define WLAN_RF_WF_TIA_AUX_MIL_CBIT_LSB     8
/// WF_TIA_AUX_MIL_CBIT field width
#define WLAN_RF_WF_TIA_AUX_MIL_CBIT_WIDTH   ((uint32_t)0x00000003)
/// WF_TIA_AUX_MIL_RBIT field mask
#define WLAN_RF_WF_TIA_AUX_MIL_RBIT_MASK    ((uint32_t)0x000000E0)
/// WF_TIA_AUX_MIL_RBIT field LSB position
#define WLAN_RF_WF_TIA_AUX_MIL_RBIT_LSB     5
/// WF_TIA_AUX_MIL_RBIT field width
#define WLAN_RF_WF_TIA_AUX_MIL_RBIT_WIDTH   ((uint32_t)0x00000003)
/// WF_TIA_AUX_Q_RBIT field mask
#define WLAN_RF_WF_TIA_AUX_Q_RBIT_MASK      ((uint32_t)0x0000001C)
/// WF_TIA_AUX_Q_RBIT field LSB position
#define WLAN_RF_WF_TIA_AUX_Q_RBIT_LSB       2
/// WF_TIA_AUX_Q_RBIT field width
#define WLAN_RF_WF_TIA_AUX_Q_RBIT_WIDTH     ((uint32_t)0x00000003)
/// WF_TIA_VCM_LDO_VBIT field mask
#define WLAN_RF_WF_TIA_VCM_LDO_VBIT_MASK    ((uint32_t)0x00000003)
/// WF_TIA_VCM_LDO_VBIT field LSB position
#define WLAN_RF_WF_TIA_VCM_LDO_VBIT_LSB     0
/// WF_TIA_VCM_LDO_VBIT field width
#define WLAN_RF_WF_TIA_VCM_LDO_VBIT_WIDTH   ((uint32_t)0x00000002)

/// WF_TIA_VCM_VBIT field reset value
#define WLAN_RF_WF_TIA_VCM_VBIT_RST         0x3
/// WF_TIA_AUX_INPUT_SEL field reset value
#define WLAN_RF_WF_TIA_AUX_INPUT_SEL_RST    0x0
/// WF_TIA_AUX_GBIT field reset value
#define WLAN_RF_WF_TIA_AUX_GBIT_RST         0x3
/// WF_TIA_AUX_IBIT field reset value
#define WLAN_RF_WF_TIA_AUX_IBIT_RST         0x19
/// WF_TIA_AUX_BW_BIT field reset value
#define WLAN_RF_WF_TIA_AUX_BW_BIT_RST       0x1D
/// WF_TIA_AUX_MIL_CBIT field reset value
#define WLAN_RF_WF_TIA_AUX_MIL_CBIT_RST     0x4
/// WF_TIA_AUX_MIL_RBIT field reset value
#define WLAN_RF_WF_TIA_AUX_MIL_RBIT_RST     0x4
/// WF_TIA_AUX_Q_RBIT field reset value
#define WLAN_RF_WF_TIA_AUX_Q_RBIT_RST       0x3
/// WF_TIA_VCM_LDO_VBIT field reset value
#define WLAN_RF_WF_TIA_VCM_LDO_VBIT_RST     0x1

/**
 * @brief Constructs a value for the REG_24 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wftiavcmvbit - The value to use for the wf_tia_vcm_vbit field.
 * @param[in] wftiaauxinputsel - The value to use for the wf_tia_aux_input_sel field.
 * @param[in] wftiavcmldovbit - The value to use for the wf_tia_vcm_ldo_vbit field.
 */
__INLINE void wlan_rf_reg_24_pack(uint8_t wftiavcmvbit, uint8_t wftiaauxinputsel, uint8_t wftiavcmldovbit)
{
    REG_PL_WR(WLAN_RF_REG_24_ADDR,  ((uint32_t)wftiavcmvbit << 27) | ((uint32_t)wftiaauxinputsel << 24) | ((uint32_t)wftiavcmldovbit << 0));
}

/**
 * @brief Unpacks REG_24's fields from current value of the REG_24 register.
 *
 * Reads the REG_24 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wftiavcmvbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaauxinputsel - Will be populated with the current value of this field from the register.
 * @param[out] wftiaauxgbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaauxibit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaauxbwbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaauxmilcbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaauxmilrbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaauxqrbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiavcmldovbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_24_unpack(uint8_t* wftiavcmvbit, uint8_t* wftiaauxinputsel, uint8_t* wftiaauxgbit, uint8_t* wftiaauxibit, uint8_t* wftiaauxbwbit, uint8_t* wftiaauxmilcbit, uint8_t* wftiaauxmilrbit, uint8_t* wftiaauxqrbit, uint8_t* wftiavcmldovbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);

    *wftiavcmvbit = (localVal & ((uint32_t)0x38000000)) >> 27;
    *wftiaauxinputsel = (localVal & ((uint32_t)0x07000000)) >> 24;
    *wftiaauxgbit = (localVal & ((uint32_t)0x00E00000)) >> 21;
    *wftiaauxibit = (localVal & ((uint32_t)0x001F0000)) >> 16;
    *wftiaauxbwbit = (localVal & ((uint32_t)0x0000F800)) >> 11;
    *wftiaauxmilcbit = (localVal & ((uint32_t)0x00000700)) >> 8;
    *wftiaauxmilrbit = (localVal & ((uint32_t)0x000000E0)) >> 5;
    *wftiaauxqrbit = (localVal & ((uint32_t)0x0000001C)) >> 2;
    *wftiavcmldovbit = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_tia_vcm_vbit field in the REG_24 register.
 *
 * The REG_24 register will be read and the wf_tia_vcm_vbit field's value will be returned.
 *
 * @return The current value of the wf_tia_vcm_vbit field in the REG_24 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_vcm_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x38000000)) >> 27);
}

/**
 * @brief Sets the wf_tia_vcm_vbit field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiavcmvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_vcm_vbit_setf(uint8_t wftiavcmvbit)
{
    REG_PL_WR(WLAN_RF_REG_24_ADDR, (REG_PL_RD(WLAN_RF_REG_24_ADDR) & ~((uint32_t)0x38000000)) | (((uint32_t)wftiavcmvbit << 27) & ((uint32_t)0x38000000)));
}

/**
 * @brief Returns the current value of the wf_tia_aux_input_sel field in the REG_24 register.
 *
 * The REG_24 register will be read and the wf_tia_aux_input_sel field's value will be returned.
 *
 * @return The current value of the wf_tia_aux_input_sel field in the REG_24 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_aux_input_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

/**
 * @brief Sets the wf_tia_aux_input_sel field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaauxinputsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_aux_input_sel_setf(uint8_t wftiaauxinputsel)
{
    REG_PL_WR(WLAN_RF_REG_24_ADDR, (REG_PL_RD(WLAN_RF_REG_24_ADDR) & ~((uint32_t)0x07000000)) | (((uint32_t)wftiaauxinputsel << 24) & ((uint32_t)0x07000000)));
}

/**
 * @brief Returns the current value of the wf_tia_aux_gbit field in the REG_24 register.
 *
 * The REG_24 register will be read and the wf_tia_aux_gbit field's value will be returned.
 *
 * @return The current value of the wf_tia_aux_gbit field in the REG_24 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_aux_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x00E00000)) >> 21);
}

/**
 * @brief Returns the current value of the wf_tia_aux_ibit field in the REG_24 register.
 *
 * The REG_24 register will be read and the wf_tia_aux_ibit field's value will be returned.
 *
 * @return The current value of the wf_tia_aux_ibit field in the REG_24 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_aux_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x001F0000)) >> 16);
}

/**
 * @brief Returns the current value of the wf_tia_aux_bw_bit field in the REG_24 register.
 *
 * The REG_24 register will be read and the wf_tia_aux_bw_bit field's value will be returned.
 *
 * @return The current value of the wf_tia_aux_bw_bit field in the REG_24 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_aux_bw_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x0000F800)) >> 11);
}

/**
 * @brief Returns the current value of the wf_tia_aux_mil_cbit field in the REG_24 register.
 *
 * The REG_24 register will be read and the wf_tia_aux_mil_cbit field's value will be returned.
 *
 * @return The current value of the wf_tia_aux_mil_cbit field in the REG_24 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_aux_mil_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

/**
 * @brief Returns the current value of the wf_tia_aux_mil_rbit field in the REG_24 register.
 *
 * The REG_24 register will be read and the wf_tia_aux_mil_rbit field's value will be returned.
 *
 * @return The current value of the wf_tia_aux_mil_rbit field in the REG_24 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_aux_mil_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x000000E0)) >> 5);
}

/**
 * @brief Returns the current value of the wf_tia_aux_q_rbit field in the REG_24 register.
 *
 * The REG_24 register will be read and the wf_tia_aux_q_rbit field's value will be returned.
 *
 * @return The current value of the wf_tia_aux_q_rbit field in the REG_24 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_aux_q_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x0000001C)) >> 2);
}

/**
 * @brief Returns the current value of the wf_tia_vcm_ldo_vbit field in the REG_24 register.
 *
 * The REG_24 register will be read and the wf_tia_vcm_ldo_vbit field's value will be returned.
 *
 * @return The current value of the wf_tia_vcm_ldo_vbit field in the REG_24 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_vcm_ldo_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the wf_tia_vcm_ldo_vbit field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiavcmldovbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_vcm_ldo_vbit_setf(uint8_t wftiavcmldovbit)
{
    REG_PL_WR(WLAN_RF_REG_24_ADDR, (REG_PL_RD(WLAN_RF_REG_24_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)wftiavcmldovbit << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_28 register definitions
 * <table>
 * <caption id="REG_28_BF">REG_28 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>28:26 <td>wf_tia_dc_cal_ibit <td>W <td>R <td>0x3
 * <tr><td>25 <td>wf_tia_i_cal_bit_dr <td>R <td>R/W <td>0
 * <tr><td>24:17 <td>wf_tia_i_cal_bit_reg <td>R <td>R/W <td>0x80
 * <tr><td>16 <td>wf_tia_q_cal_bit_dr <td>R <td>R/W <td>0
 * <tr><td>15:08 <td>wf_tia_q_cal_bit_reg <td>R <td>R/W <td>0x80
 * <tr><td>07 <td>          wf_pa_ms <td>R <td>R/W <td>0
 * <tr><td>06 <td>wf_pa5g_wf_mode_en <td>R <td>R/W <td>1
 * <tr><td>05:00 <td>      wf_pa5g_gbit <td>W <td>R <td>0x3F
 * </table>
 *
 * @{
 */

/// Address of the REG_28 register
#define WLAN_RF_REG_28_ADDR   0x40344028
/// Offset of the REG_28 register from the base address
#define WLAN_RF_REG_28_OFFSET 0x00000028
/// Index of the REG_28 register
#define WLAN_RF_REG_28_INDEX  0x0000000A
/// Reset value of the REG_28 register
#define WLAN_RF_REG_28_RESET  0x0D00807F

/**
 * @brief Returns the current value of the REG_28 register.
 * The REG_28 register will be read and its value returned.
 * @return The current value of the REG_28 register.
 */
__INLINE uint32_t wlan_rf_reg_28_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_28_ADDR);
}

/**
 * @brief Sets the REG_28 register to a value.
 * The REG_28 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_28_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_28_ADDR, value);
}

// field definitions
/// WF_TIA_DC_CAL_IBIT field mask
#define WLAN_RF_WF_TIA_DC_CAL_IBIT_MASK     ((uint32_t)0x1C000000)
/// WF_TIA_DC_CAL_IBIT field LSB position
#define WLAN_RF_WF_TIA_DC_CAL_IBIT_LSB      26
/// WF_TIA_DC_CAL_IBIT field width
#define WLAN_RF_WF_TIA_DC_CAL_IBIT_WIDTH    ((uint32_t)0x00000003)
/// WF_TIA_I_CAL_BIT_DR field bit
#define WLAN_RF_WF_TIA_I_CAL_BIT_DR_BIT     ((uint32_t)0x02000000)
/// WF_TIA_I_CAL_BIT_DR field position
#define WLAN_RF_WF_TIA_I_CAL_BIT_DR_POS     25
/// WF_TIA_I_CAL_BIT_REG field mask
#define WLAN_RF_WF_TIA_I_CAL_BIT_REG_MASK   ((uint32_t)0x01FE0000)
/// WF_TIA_I_CAL_BIT_REG field LSB position
#define WLAN_RF_WF_TIA_I_CAL_BIT_REG_LSB    17
/// WF_TIA_I_CAL_BIT_REG field width
#define WLAN_RF_WF_TIA_I_CAL_BIT_REG_WIDTH  ((uint32_t)0x00000008)
/// WF_TIA_Q_CAL_BIT_DR field bit
#define WLAN_RF_WF_TIA_Q_CAL_BIT_DR_BIT     ((uint32_t)0x00010000)
/// WF_TIA_Q_CAL_BIT_DR field position
#define WLAN_RF_WF_TIA_Q_CAL_BIT_DR_POS     16
/// WF_TIA_Q_CAL_BIT_REG field mask
#define WLAN_RF_WF_TIA_Q_CAL_BIT_REG_MASK   ((uint32_t)0x0000FF00)
/// WF_TIA_Q_CAL_BIT_REG field LSB position
#define WLAN_RF_WF_TIA_Q_CAL_BIT_REG_LSB    8
/// WF_TIA_Q_CAL_BIT_REG field width
#define WLAN_RF_WF_TIA_Q_CAL_BIT_REG_WIDTH  ((uint32_t)0x00000008)
/// WF_PA_MS field bit
#define WLAN_RF_WF_PA_MS_BIT                ((uint32_t)0x00000080)
/// WF_PA_MS field position
#define WLAN_RF_WF_PA_MS_POS                7
/// WF_PA_5G_WF_MODE_EN field bit
#define WLAN_RF_WF_PA_5G_WF_MODE_EN_BIT     ((uint32_t)0x00000040)
/// WF_PA_5G_WF_MODE_EN field position
#define WLAN_RF_WF_PA_5G_WF_MODE_EN_POS     6
/// WF_PA_5G_GBIT field mask
#define WLAN_RF_WF_PA_5G_GBIT_MASK          ((uint32_t)0x0000003F)
/// WF_PA_5G_GBIT field LSB position
#define WLAN_RF_WF_PA_5G_GBIT_LSB           0
/// WF_PA_5G_GBIT field width
#define WLAN_RF_WF_PA_5G_GBIT_WIDTH         ((uint32_t)0x00000006)

/// WF_TIA_DC_CAL_IBIT field reset value
#define WLAN_RF_WF_TIA_DC_CAL_IBIT_RST      0x3
/// WF_TIA_I_CAL_BIT_DR field reset value
#define WLAN_RF_WF_TIA_I_CAL_BIT_DR_RST     0x0
/// WF_TIA_I_CAL_BIT_REG field reset value
#define WLAN_RF_WF_TIA_I_CAL_BIT_REG_RST    0x80
/// WF_TIA_Q_CAL_BIT_DR field reset value
#define WLAN_RF_WF_TIA_Q_CAL_BIT_DR_RST     0x0
/// WF_TIA_Q_CAL_BIT_REG field reset value
#define WLAN_RF_WF_TIA_Q_CAL_BIT_REG_RST    0x80
/// WF_PA_MS field reset value
#define WLAN_RF_WF_PA_MS_RST                0x0
/// WF_PA_5G_WF_MODE_EN field reset value
#define WLAN_RF_WF_PA_5G_WF_MODE_EN_RST     0x1
/// WF_PA_5G_GBIT field reset value
#define WLAN_RF_WF_PA_5G_GBIT_RST           0x3F

/**
 * @brief Constructs a value for the REG_28 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wftiaicalbitdr - The value to use for the wf_tia_i_cal_bit_dr field.
 * @param[in] wftiaicalbitreg - The value to use for the wf_tia_i_cal_bit_reg field.
 * @param[in] wftiaqcalbitdr - The value to use for the wf_tia_q_cal_bit_dr field.
 * @param[in] wftiaqcalbitreg - The value to use for the wf_tia_q_cal_bit_reg field.
 * @param[in] wfpams - The value to use for the wf_pa_ms field.
 * @param[in] wfpa5gwfmodeen - The value to use for the wf_pa5g_wf_mode_en field.
 */
__INLINE void wlan_rf_reg_28_pack(uint8_t wftiaicalbitdr, uint8_t wftiaicalbitreg, uint8_t wftiaqcalbitdr, uint8_t wftiaqcalbitreg, uint8_t wfpams, uint8_t wfpa5gwfmodeen)
{
    REG_PL_WR(WLAN_RF_REG_28_ADDR,  ((uint32_t)wftiaicalbitdr << 25) | ((uint32_t)wftiaicalbitreg << 17) | ((uint32_t)wftiaqcalbitdr << 16) | ((uint32_t)wftiaqcalbitreg << 8) | ((uint32_t)wfpams << 7) | ((uint32_t)wfpa5gwfmodeen << 6));
}

/**
 * @brief Unpacks REG_28's fields from current value of the REG_28 register.
 *
 * Reads the REG_28 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wftiadccalibit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaicalbitdr - Will be populated with the current value of this field from the register.
 * @param[out] wftiaicalbitreg - Will be populated with the current value of this field from the register.
 * @param[out] wftiaqcalbitdr - Will be populated with the current value of this field from the register.
 * @param[out] wftiaqcalbitreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpams - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gwfmodeen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5ggbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_28_unpack(uint8_t* wftiadccalibit, uint8_t* wftiaicalbitdr, uint8_t* wftiaicalbitreg, uint8_t* wftiaqcalbitdr, uint8_t* wftiaqcalbitreg, uint8_t* wfpams, uint8_t* wfpa5gwfmodeen, uint8_t* wfpa5ggbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_28_ADDR);

    *wftiadccalibit = (localVal & ((uint32_t)0x1C000000)) >> 26;
    *wftiaicalbitdr = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wftiaicalbitreg = (localVal & ((uint32_t)0x01FE0000)) >> 17;
    *wftiaqcalbitdr = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wftiaqcalbitreg = (localVal & ((uint32_t)0x0000FF00)) >> 8;
    *wfpams = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wfpa5gwfmodeen = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wfpa5ggbit = (localVal & ((uint32_t)0x0000003F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_tia_dc_cal_ibit field in the REG_28 register.
 *
 * The REG_28 register will be read and the wf_tia_dc_cal_ibit field's value will be returned.
 *
 * @return The current value of the wf_tia_dc_cal_ibit field in the REG_28 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_dc_cal_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x1C000000)) >> 26);
}

/**
 * @brief Returns the current value of the wf_tia_i_cal_bit_dr field in the REG_28 register.
 *
 * The REG_28 register will be read and the wf_tia_i_cal_bit_dr field's value will be returned.
 *
 * @return The current value of the wf_tia_i_cal_bit_dr field in the REG_28 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_i_cal_bit_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_tia_i_cal_bit_dr field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaicalbitdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_i_cal_bit_dr_setf(uint8_t wftiaicalbitdr)
{
    REG_PL_WR(WLAN_RF_REG_28_ADDR, (REG_PL_RD(WLAN_RF_REG_28_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wftiaicalbitdr << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_tia_i_cal_bit_reg field in the REG_28 register.
 *
 * The REG_28 register will be read and the wf_tia_i_cal_bit_reg field's value will be returned.
 *
 * @return The current value of the wf_tia_i_cal_bit_reg field in the REG_28 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_i_cal_bit_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x01FE0000)) >> 17);
}

/**
 * @brief Sets the wf_tia_i_cal_bit_reg field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaicalbitreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_i_cal_bit_reg_setf(uint8_t wftiaicalbitreg)
{
    REG_PL_WR(WLAN_RF_REG_28_ADDR, (REG_PL_RD(WLAN_RF_REG_28_ADDR) & ~((uint32_t)0x01FE0000)) | (((uint32_t)wftiaicalbitreg << 17) & ((uint32_t)0x01FE0000)));
}

/**
 * @brief Returns the current value of the wf_tia_q_cal_bit_dr field in the REG_28 register.
 *
 * The REG_28 register will be read and the wf_tia_q_cal_bit_dr field's value will be returned.
 *
 * @return The current value of the wf_tia_q_cal_bit_dr field in the REG_28 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_q_cal_bit_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_tia_q_cal_bit_dr field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaqcalbitdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_q_cal_bit_dr_setf(uint8_t wftiaqcalbitdr)
{
    REG_PL_WR(WLAN_RF_REG_28_ADDR, (REG_PL_RD(WLAN_RF_REG_28_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wftiaqcalbitdr << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_tia_q_cal_bit_reg field in the REG_28 register.
 *
 * The REG_28 register will be read and the wf_tia_q_cal_bit_reg field's value will be returned.
 *
 * @return The current value of the wf_tia_q_cal_bit_reg field in the REG_28 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_q_cal_bit_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x0000FF00)) >> 8);
}

/**
 * @brief Sets the wf_tia_q_cal_bit_reg field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaqcalbitreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_q_cal_bit_reg_setf(uint8_t wftiaqcalbitreg)
{
    REG_PL_WR(WLAN_RF_REG_28_ADDR, (REG_PL_RD(WLAN_RF_REG_28_ADDR) & ~((uint32_t)0x0000FF00)) | (((uint32_t)wftiaqcalbitreg << 8) & ((uint32_t)0x0000FF00)));
}

/**
 * @brief Returns the current value of the wf_pa_ms field in the REG_28 register.
 *
 * The REG_28 register will be read and the wf_pa_ms field's value will be returned.
 *
 * @return The current value of the wf_pa_ms field in the REG_28 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_ms_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_pa_ms field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpams - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_ms_setf(uint8_t wfpams)
{
    REG_PL_WR(WLAN_RF_REG_28_ADDR, (REG_PL_RD(WLAN_RF_REG_28_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wfpams << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_pa5g_wf_mode_en field in the REG_28 register.
 *
 * The REG_28 register will be read and the wf_pa5g_wf_mode_en field's value will be returned.
 *
 * @return The current value of the wf_pa5g_wf_mode_en field in the REG_28 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_wf_mode_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the wf_pa5g_wf_mode_en field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gwfmodeen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_wf_mode_en_setf(uint8_t wfpa5gwfmodeen)
{
    REG_PL_WR(WLAN_RF_REG_28_ADDR, (REG_PL_RD(WLAN_RF_REG_28_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)wfpa5gwfmodeen << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the wf_pa5g_gbit field in the REG_28 register.
 *
 * The REG_28 register will be read and the wf_pa5g_gbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_gbit field in the REG_28 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x0000003F)) >> 0);
}

/// @}

/**
 * @name REG_2C register definitions
 * <table>
 * <caption id="REG_2C_BF">REG_2C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>26:21 <td>     wf_pa24g_gbit <td>W <td>R <td>0x3F
 * <tr><td>20:18 <td>wf_pa24g_input_cbit <td>W <td>R <td>0x0
 * <tr><td>17:16 <td>  wf_pa_vbg_tc_bit <td>R <td>R/W <td>0x2
 * <tr><td>15:14 <td>    wf_pa_vbg_vbit <td>R <td>R/W <td>0x2
 * <tr><td>13:11 <td>     wf_pa_vh_vbit <td>R <td>R/W <td>0x6
 * <tr><td>10 <td>wf_pa_vh_ref_sel_bg <td>R <td>R/W <td>1
 * <tr><td>09 <td>       wf_pa_vm_en <td>R <td>R/W <td>1
 * <tr><td>08 <td>   wf_pa_vm_dyn_en <td>W <td>R <td>0
 * <tr><td>07 <td>wf_pa_vm_opam_ibit <td>R <td>R/W <td>1
 * <tr><td>06:04 <td> wf_pa_vm_ref_vbit <td>W <td>R <td>0x4
 * <tr><td>03:00 <td>    wf_pa_vm_vbit1 <td>W <td>R <td>0xB
 * </table>
 *
 * @{
 */

/// Address of the REG_2C register
#define WLAN_RF_REG_2C_ADDR   0x4034402C
/// Offset of the REG_2C register from the base address
#define WLAN_RF_REG_2C_OFFSET 0x0000002C
/// Index of the REG_2C register
#define WLAN_RF_REG_2C_INDEX  0x0000000B
/// Reset value of the REG_2C register
#define WLAN_RF_REG_2C_RESET  0x07E2B6CB

/**
 * @brief Returns the current value of the REG_2C register.
 * The REG_2C register will be read and its value returned.
 * @return The current value of the REG_2C register.
 */
__INLINE uint32_t wlan_rf_reg_2c_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_2C_ADDR);
}

/**
 * @brief Sets the REG_2C register to a value.
 * The REG_2C register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_2c_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_2C_ADDR, value);
}

// field definitions
/// WF_PA_24G_GBIT field mask
#define WLAN_RF_WF_PA_24G_GBIT_MASK         ((uint32_t)0x07E00000)
/// WF_PA_24G_GBIT field LSB position
#define WLAN_RF_WF_PA_24G_GBIT_LSB          21
/// WF_PA_24G_GBIT field width
#define WLAN_RF_WF_PA_24G_GBIT_WIDTH        ((uint32_t)0x00000006)
/// WF_PA_24G_INPUT_CBIT field mask
#define WLAN_RF_WF_PA_24G_INPUT_CBIT_MASK   ((uint32_t)0x001C0000)
/// WF_PA_24G_INPUT_CBIT field LSB position
#define WLAN_RF_WF_PA_24G_INPUT_CBIT_LSB    18
/// WF_PA_24G_INPUT_CBIT field width
#define WLAN_RF_WF_PA_24G_INPUT_CBIT_WIDTH  ((uint32_t)0x00000003)
/// WF_PA_VBG_TC_BIT field mask
#define WLAN_RF_WF_PA_VBG_TC_BIT_MASK       ((uint32_t)0x00030000)
/// WF_PA_VBG_TC_BIT field LSB position
#define WLAN_RF_WF_PA_VBG_TC_BIT_LSB        16
/// WF_PA_VBG_TC_BIT field width
#define WLAN_RF_WF_PA_VBG_TC_BIT_WIDTH      ((uint32_t)0x00000002)
/// WF_PA_VBG_VBIT field mask
#define WLAN_RF_WF_PA_VBG_VBIT_MASK         ((uint32_t)0x0000C000)
/// WF_PA_VBG_VBIT field LSB position
#define WLAN_RF_WF_PA_VBG_VBIT_LSB          14
/// WF_PA_VBG_VBIT field width
#define WLAN_RF_WF_PA_VBG_VBIT_WIDTH        ((uint32_t)0x00000002)
/// WF_PA_VH_VBIT field mask
#define WLAN_RF_WF_PA_VH_VBIT_MASK          ((uint32_t)0x00003800)
/// WF_PA_VH_VBIT field LSB position
#define WLAN_RF_WF_PA_VH_VBIT_LSB           11
/// WF_PA_VH_VBIT field width
#define WLAN_RF_WF_PA_VH_VBIT_WIDTH         ((uint32_t)0x00000003)
/// WF_PA_VH_REF_SEL_BG field bit
#define WLAN_RF_WF_PA_VH_REF_SEL_BG_BIT     ((uint32_t)0x00000400)
/// WF_PA_VH_REF_SEL_BG field position
#define WLAN_RF_WF_PA_VH_REF_SEL_BG_POS     10
/// WF_PA_VM_EN field bit
#define WLAN_RF_WF_PA_VM_EN_BIT             ((uint32_t)0x00000200)
/// WF_PA_VM_EN field position
#define WLAN_RF_WF_PA_VM_EN_POS             9
/// WF_PA_VM_DYN_EN field bit
#define WLAN_RF_WF_PA_VM_DYN_EN_BIT         ((uint32_t)0x00000100)
/// WF_PA_VM_DYN_EN field position
#define WLAN_RF_WF_PA_VM_DYN_EN_POS         8
/// WF_PA_VM_OPAM_IBIT field bit
#define WLAN_RF_WF_PA_VM_OPAM_IBIT_BIT      ((uint32_t)0x00000080)
/// WF_PA_VM_OPAM_IBIT field position
#define WLAN_RF_WF_PA_VM_OPAM_IBIT_POS      7
/// WF_PA_VM_REF_VBIT field mask
#define WLAN_RF_WF_PA_VM_REF_VBIT_MASK      ((uint32_t)0x00000070)
/// WF_PA_VM_REF_VBIT field LSB position
#define WLAN_RF_WF_PA_VM_REF_VBIT_LSB       4
/// WF_PA_VM_REF_VBIT field width
#define WLAN_RF_WF_PA_VM_REF_VBIT_WIDTH     ((uint32_t)0x00000003)
/// WF_PA_VM_VBIT_1 field mask
#define WLAN_RF_WF_PA_VM_VBIT_1_MASK        ((uint32_t)0x0000000F)
/// WF_PA_VM_VBIT_1 field LSB position
#define WLAN_RF_WF_PA_VM_VBIT_1_LSB         0
/// WF_PA_VM_VBIT_1 field width
#define WLAN_RF_WF_PA_VM_VBIT_1_WIDTH       ((uint32_t)0x00000004)

/// WF_PA_24G_GBIT field reset value
#define WLAN_RF_WF_PA_24G_GBIT_RST          0x3F
/// WF_PA_24G_INPUT_CBIT field reset value
#define WLAN_RF_WF_PA_24G_INPUT_CBIT_RST    0x0
/// WF_PA_VBG_TC_BIT field reset value
#define WLAN_RF_WF_PA_VBG_TC_BIT_RST        0x2
/// WF_PA_VBG_VBIT field reset value
#define WLAN_RF_WF_PA_VBG_VBIT_RST          0x2
/// WF_PA_VH_VBIT field reset value
#define WLAN_RF_WF_PA_VH_VBIT_RST           0x6
/// WF_PA_VH_REF_SEL_BG field reset value
#define WLAN_RF_WF_PA_VH_REF_SEL_BG_RST     0x1
/// WF_PA_VM_EN field reset value
#define WLAN_RF_WF_PA_VM_EN_RST             0x1
/// WF_PA_VM_DYN_EN field reset value
#define WLAN_RF_WF_PA_VM_DYN_EN_RST         0x0
/// WF_PA_VM_OPAM_IBIT field reset value
#define WLAN_RF_WF_PA_VM_OPAM_IBIT_RST      0x1
/// WF_PA_VM_REF_VBIT field reset value
#define WLAN_RF_WF_PA_VM_REF_VBIT_RST       0x4
/// WF_PA_VM_VBIT_1 field reset value
#define WLAN_RF_WF_PA_VM_VBIT_1_RST         0xB

/**
 * @brief Constructs a value for the REG_2C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpavbgtcbit - The value to use for the wf_pa_vbg_tc_bit field.
 * @param[in] wfpavbgvbit - The value to use for the wf_pa_vbg_vbit field.
 * @param[in] wfpavhvbit - The value to use for the wf_pa_vh_vbit field.
 * @param[in] wfpavhrefselbg - The value to use for the wf_pa_vh_ref_sel_bg field.
 * @param[in] wfpavmen - The value to use for the wf_pa_vm_en field.
 * @param[in] wfpavmopamibit - The value to use for the wf_pa_vm_opam_ibit field.
 */
__INLINE void wlan_rf_reg_2c_pack(uint8_t wfpavbgtcbit, uint8_t wfpavbgvbit, uint8_t wfpavhvbit, uint8_t wfpavhrefselbg, uint8_t wfpavmen, uint8_t wfpavmopamibit)
{
    REG_PL_WR(WLAN_RF_REG_2C_ADDR,  ((uint32_t)wfpavbgtcbit << 16) | ((uint32_t)wfpavbgvbit << 14) | ((uint32_t)wfpavhvbit << 11) | ((uint32_t)wfpavhrefselbg << 10) | ((uint32_t)wfpavmen << 9) | ((uint32_t)wfpavmopamibit << 7));
}

/**
 * @brief Unpacks REG_2C's fields from current value of the REG_2C register.
 *
 * Reads the REG_2C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpa24ggbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24ginputcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavbgtcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavbgvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavhvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavhrefselbg - Will be populated with the current value of this field from the register.
 * @param[out] wfpavmen - Will be populated with the current value of this field from the register.
 * @param[out] wfpavmdynen - Will be populated with the current value of this field from the register.
 * @param[out] wfpavmopamibit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavmrefvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavmvbit1 - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_2c_unpack(uint8_t* wfpa24ggbit, uint8_t* wfpa24ginputcbit, uint8_t* wfpavbgtcbit, uint8_t* wfpavbgvbit, uint8_t* wfpavhvbit, uint8_t* wfpavhrefselbg, uint8_t* wfpavmen, uint8_t* wfpavmdynen, uint8_t* wfpavmopamibit, uint8_t* wfpavmrefvbit, uint8_t* wfpavmvbit1)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);

    *wfpa24ggbit = (localVal & ((uint32_t)0x07E00000)) >> 21;
    *wfpa24ginputcbit = (localVal & ((uint32_t)0x001C0000)) >> 18;
    *wfpavbgtcbit = (localVal & ((uint32_t)0x00030000)) >> 16;
    *wfpavbgvbit = (localVal & ((uint32_t)0x0000C000)) >> 14;
    *wfpavhvbit = (localVal & ((uint32_t)0x00003800)) >> 11;
    *wfpavhrefselbg = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfpavmen = (localVal & ((uint32_t)0x00000200)) >> 9;
    *wfpavmdynen = (localVal & ((uint32_t)0x00000100)) >> 8;
    *wfpavmopamibit = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wfpavmrefvbit = (localVal & ((uint32_t)0x00000070)) >> 4;
    *wfpavmvbit1 = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pa24g_gbit field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa24g_gbit field's value will be returned.
 *
 * @return The current value of the wf_pa24g_gbit field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x07E00000)) >> 21);
}

/**
 * @brief Returns the current value of the wf_pa24g_input_cbit field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa24g_input_cbit field's value will be returned.
 *
 * @return The current value of the wf_pa24g_input_cbit field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_input_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x001C0000)) >> 18);
}

/**
 * @brief Returns the current value of the wf_pa_vbg_tc_bit field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa_vbg_tc_bit field's value will be returned.
 *
 * @return The current value of the wf_pa_vbg_tc_bit field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vbg_tc_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

/**
 * @brief Sets the wf_pa_vbg_tc_bit field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavbgtcbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vbg_tc_bit_setf(uint8_t wfpavbgtcbit)
{
    REG_PL_WR(WLAN_RF_REG_2C_ADDR, (REG_PL_RD(WLAN_RF_REG_2C_ADDR) & ~((uint32_t)0x00030000)) | (((uint32_t)wfpavbgtcbit << 16) & ((uint32_t)0x00030000)));
}

/**
 * @brief Returns the current value of the wf_pa_vbg_vbit field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa_vbg_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa_vbg_vbit field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vbg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x0000C000)) >> 14);
}

/**
 * @brief Sets the wf_pa_vbg_vbit field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavbgvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vbg_vbit_setf(uint8_t wfpavbgvbit)
{
    REG_PL_WR(WLAN_RF_REG_2C_ADDR, (REG_PL_RD(WLAN_RF_REG_2C_ADDR) & ~((uint32_t)0x0000C000)) | (((uint32_t)wfpavbgvbit << 14) & ((uint32_t)0x0000C000)));
}

/**
 * @brief Returns the current value of the wf_pa_vh_vbit field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa_vh_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa_vh_vbit field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vh_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00003800)) >> 11);
}

/**
 * @brief Sets the wf_pa_vh_vbit field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavhvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vh_vbit_setf(uint8_t wfpavhvbit)
{
    REG_PL_WR(WLAN_RF_REG_2C_ADDR, (REG_PL_RD(WLAN_RF_REG_2C_ADDR) & ~((uint32_t)0x00003800)) | (((uint32_t)wfpavhvbit << 11) & ((uint32_t)0x00003800)));
}

/**
 * @brief Returns the current value of the wf_pa_vh_ref_sel_bg field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa_vh_ref_sel_bg field's value will be returned.
 *
 * @return The current value of the wf_pa_vh_ref_sel_bg field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vh_ref_sel_bg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_pa_vh_ref_sel_bg field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavhrefselbg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vh_ref_sel_bg_setf(uint8_t wfpavhrefselbg)
{
    REG_PL_WR(WLAN_RF_REG_2C_ADDR, (REG_PL_RD(WLAN_RF_REG_2C_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfpavhrefselbg << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_pa_vm_en field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa_vm_en field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_en field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the wf_pa_vm_en field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavmen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vm_en_setf(uint8_t wfpavmen)
{
    REG_PL_WR(WLAN_RF_REG_2C_ADDR, (REG_PL_RD(WLAN_RF_REG_2C_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)wfpavmen << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the wf_pa_vm_dyn_en field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa_vm_dyn_en field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_dyn_en field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_dyn_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Returns the current value of the wf_pa_vm_opam_ibit field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa_vm_opam_ibit field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_opam_ibit field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_opam_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_pa_vm_opam_ibit field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavmopamibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vm_opam_ibit_setf(uint8_t wfpavmopamibit)
{
    REG_PL_WR(WLAN_RF_REG_2C_ADDR, (REG_PL_RD(WLAN_RF_REG_2C_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wfpavmopamibit << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_pa_vm_ref_vbit field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa_vm_ref_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_ref_vbit field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_ref_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

/**
 * @brief Returns the current value of the wf_pa_vm_vbit1 field in the REG_2C register.
 *
 * The REG_2C register will be read and the wf_pa_vm_vbit1 field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_vbit1 field in the REG_2C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_vbit_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/// @}

/**
 * @name REG_30 register definitions
 * <table>
 * <caption id="REG_30_BF">REG_30 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30:25 <td>    wf_pa_vm_vbit2 <td>W <td>R <td>0x20
 * <tr><td>24:23 <td>wf_pa5g_input1_cbit <td>W <td>R <td>0x2
 * <tr><td>22:21 <td>wf_pa5g_input2_cbit <td>W <td>R <td>0x2
 * <tr><td>20 <td>wf_pa5g_vm_rfdyn_en <td>W <td>R <td>0
 * <tr><td>19:17 <td>wf_pa5g_vm_rfdyn_vthbit <td>R <td>R/W <td>0x4
 * <tr><td>16:15 <td> wf_pa5g_vl_en_bit <td>W <td>R <td>0x3
 * <tr><td>14 <td>wf_pa5g_vl_sel_vl1 <td>R <td>R/W <td>1
 * <tr><td>13 <td>wf_pa5g_vl1_opam_en <td>R <td>R/W <td>1
 * <tr><td>12:10 <td>wf_pa5g_vl1_ic_sel_bit <td>R <td>R/W <td>0x1
 * <tr><td>09:07 <td>  wf_pa5g_vl1_vbit <td>W <td>R <td>0x4
 * <tr><td>06:03 <td>wf_pa5g_vl1_cgm_ibit <td>R <td>R/W <td>0x8
 * <tr><td>02:00 <td>wf_pa5g_vl1_rfdyn_vthbit <td>R <td>R/W <td>0x4
 * </table>
 *
 * @{
 */

/// Address of the REG_30 register
#define WLAN_RF_REG_30_ADDR   0x40344030
/// Offset of the REG_30 register from the base address
#define WLAN_RF_REG_30_OFFSET 0x00000030
/// Index of the REG_30 register
#define WLAN_RF_REG_30_INDEX  0x0000000C
/// Reset value of the REG_30 register
#define WLAN_RF_REG_30_RESET  0x4149E644

/**
 * @brief Returns the current value of the REG_30 register.
 * The REG_30 register will be read and its value returned.
 * @return The current value of the REG_30 register.
 */
__INLINE uint32_t wlan_rf_reg_30_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_30_ADDR);
}

/**
 * @brief Sets the REG_30 register to a value.
 * The REG_30 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_30_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_30_ADDR, value);
}

// field definitions
/// WF_PA_VM_VBIT_2 field mask
#define WLAN_RF_WF_PA_VM_VBIT_2_MASK              ((uint32_t)0x7E000000)
/// WF_PA_VM_VBIT_2 field LSB position
#define WLAN_RF_WF_PA_VM_VBIT_2_LSB               25
/// WF_PA_VM_VBIT_2 field width
#define WLAN_RF_WF_PA_VM_VBIT_2_WIDTH             ((uint32_t)0x00000006)
/// WF_PA_5G_INPUT_1_CBIT field mask
#define WLAN_RF_WF_PA_5G_INPUT_1_CBIT_MASK        ((uint32_t)0x01800000)
/// WF_PA_5G_INPUT_1_CBIT field LSB position
#define WLAN_RF_WF_PA_5G_INPUT_1_CBIT_LSB         23
/// WF_PA_5G_INPUT_1_CBIT field width
#define WLAN_RF_WF_PA_5G_INPUT_1_CBIT_WIDTH       ((uint32_t)0x00000002)
/// WF_PA_5G_INPUT_2_CBIT field mask
#define WLAN_RF_WF_PA_5G_INPUT_2_CBIT_MASK        ((uint32_t)0x00600000)
/// WF_PA_5G_INPUT_2_CBIT field LSB position
#define WLAN_RF_WF_PA_5G_INPUT_2_CBIT_LSB         21
/// WF_PA_5G_INPUT_2_CBIT field width
#define WLAN_RF_WF_PA_5G_INPUT_2_CBIT_WIDTH       ((uint32_t)0x00000002)
/// WF_PA_5G_VM_RFDYN_EN field bit
#define WLAN_RF_WF_PA_5G_VM_RFDYN_EN_BIT          ((uint32_t)0x00100000)
/// WF_PA_5G_VM_RFDYN_EN field position
#define WLAN_RF_WF_PA_5G_VM_RFDYN_EN_POS          20
/// WF_PA_5G_VM_RFDYN_VTHBIT field mask
#define WLAN_RF_WF_PA_5G_VM_RFDYN_VTHBIT_MASK     ((uint32_t)0x000E0000)
/// WF_PA_5G_VM_RFDYN_VTHBIT field LSB position
#define WLAN_RF_WF_PA_5G_VM_RFDYN_VTHBIT_LSB      17
/// WF_PA_5G_VM_RFDYN_VTHBIT field width
#define WLAN_RF_WF_PA_5G_VM_RFDYN_VTHBIT_WIDTH    ((uint32_t)0x00000003)
/// WF_PA_5G_VL_EN_BIT field mask
#define WLAN_RF_WF_PA_5G_VL_EN_BIT_MASK           ((uint32_t)0x00018000)
/// WF_PA_5G_VL_EN_BIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_EN_BIT_LSB            15
/// WF_PA_5G_VL_EN_BIT field width
#define WLAN_RF_WF_PA_5G_VL_EN_BIT_WIDTH          ((uint32_t)0x00000002)
/// WF_PA_5G_VL_SEL_VL_1 field bit
#define WLAN_RF_WF_PA_5G_VL_SEL_VL_1_BIT          ((uint32_t)0x00004000)
/// WF_PA_5G_VL_SEL_VL_1 field position
#define WLAN_RF_WF_PA_5G_VL_SEL_VL_1_POS          14
/// WF_PA_5G_VL_1_OPAM_EN field bit
#define WLAN_RF_WF_PA_5G_VL_1_OPAM_EN_BIT         ((uint32_t)0x00002000)
/// WF_PA_5G_VL_1_OPAM_EN field position
#define WLAN_RF_WF_PA_5G_VL_1_OPAM_EN_POS         13
/// WF_PA_5G_VL_1_IC_SEL_BIT field mask
#define WLAN_RF_WF_PA_5G_VL_1_IC_SEL_BIT_MASK     ((uint32_t)0x00001C00)
/// WF_PA_5G_VL_1_IC_SEL_BIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_1_IC_SEL_BIT_LSB      10
/// WF_PA_5G_VL_1_IC_SEL_BIT field width
#define WLAN_RF_WF_PA_5G_VL_1_IC_SEL_BIT_WIDTH    ((uint32_t)0x00000003)
/// WF_PA_5G_VL_1_VBIT field mask
#define WLAN_RF_WF_PA_5G_VL_1_VBIT_MASK           ((uint32_t)0x00000380)
/// WF_PA_5G_VL_1_VBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_1_VBIT_LSB            7
/// WF_PA_5G_VL_1_VBIT field width
#define WLAN_RF_WF_PA_5G_VL_1_VBIT_WIDTH          ((uint32_t)0x00000003)
/// WF_PA_5G_VL_1_CGM_IBIT field mask
#define WLAN_RF_WF_PA_5G_VL_1_CGM_IBIT_MASK       ((uint32_t)0x00000078)
/// WF_PA_5G_VL_1_CGM_IBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_1_CGM_IBIT_LSB        3
/// WF_PA_5G_VL_1_CGM_IBIT field width
#define WLAN_RF_WF_PA_5G_VL_1_CGM_IBIT_WIDTH      ((uint32_t)0x00000004)
/// WF_PA_5G_VL_1_RFDYN_VTHBIT field mask
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_VTHBIT_MASK   ((uint32_t)0x00000007)
/// WF_PA_5G_VL_1_RFDYN_VTHBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_VTHBIT_LSB    0
/// WF_PA_5G_VL_1_RFDYN_VTHBIT field width
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_VTHBIT_WIDTH  ((uint32_t)0x00000003)

/// WF_PA_VM_VBIT_2 field reset value
#define WLAN_RF_WF_PA_VM_VBIT_2_RST               0x20
/// WF_PA_5G_INPUT_1_CBIT field reset value
#define WLAN_RF_WF_PA_5G_INPUT_1_CBIT_RST         0x2
/// WF_PA_5G_INPUT_2_CBIT field reset value
#define WLAN_RF_WF_PA_5G_INPUT_2_CBIT_RST         0x2
/// WF_PA_5G_VM_RFDYN_EN field reset value
#define WLAN_RF_WF_PA_5G_VM_RFDYN_EN_RST          0x0
/// WF_PA_5G_VM_RFDYN_VTHBIT field reset value
#define WLAN_RF_WF_PA_5G_VM_RFDYN_VTHBIT_RST      0x4
/// WF_PA_5G_VL_EN_BIT field reset value
#define WLAN_RF_WF_PA_5G_VL_EN_BIT_RST            0x3
/// WF_PA_5G_VL_SEL_VL_1 field reset value
#define WLAN_RF_WF_PA_5G_VL_SEL_VL_1_RST          0x1
/// WF_PA_5G_VL_1_OPAM_EN field reset value
#define WLAN_RF_WF_PA_5G_VL_1_OPAM_EN_RST         0x1
/// WF_PA_5G_VL_1_IC_SEL_BIT field reset value
#define WLAN_RF_WF_PA_5G_VL_1_IC_SEL_BIT_RST      0x1
/// WF_PA_5G_VL_1_VBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_1_VBIT_RST            0x4
/// WF_PA_5G_VL_1_CGM_IBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_1_CGM_IBIT_RST        0x8
/// WF_PA_5G_VL_1_RFDYN_VTHBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_VTHBIT_RST    0x4

/**
 * @brief Constructs a value for the REG_30 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpa5gvmrfdynvthbit - The value to use for the wf_pa5g_vm_rfdyn_vthbit field.
 * @param[in] wfpa5gvlselvl1 - The value to use for the wf_pa5g_vl_sel_vl1 field.
 * @param[in] wfpa5gvl1opamen - The value to use for the wf_pa5g_vl1_opam_en field.
 * @param[in] wfpa5gvl1icselbit - The value to use for the wf_pa5g_vl1_ic_sel_bit field.
 * @param[in] wfpa5gvl1cgmibit - The value to use for the wf_pa5g_vl1_cgm_ibit field.
 * @param[in] wfpa5gvl1rfdynvthbit - The value to use for the wf_pa5g_vl1_rfdyn_vthbit field.
 */
__INLINE void wlan_rf_reg_30_pack(uint8_t wfpa5gvmrfdynvthbit, uint8_t wfpa5gvlselvl1, uint8_t wfpa5gvl1opamen, uint8_t wfpa5gvl1icselbit, uint8_t wfpa5gvl1cgmibit, uint8_t wfpa5gvl1rfdynvthbit)
{
    REG_PL_WR(WLAN_RF_REG_30_ADDR,  ((uint32_t)wfpa5gvmrfdynvthbit << 17) | ((uint32_t)wfpa5gvlselvl1 << 14) | ((uint32_t)wfpa5gvl1opamen << 13) | ((uint32_t)wfpa5gvl1icselbit << 10) | ((uint32_t)wfpa5gvl1cgmibit << 3) | ((uint32_t)wfpa5gvl1rfdynvthbit << 0));
}

/**
 * @brief Unpacks REG_30's fields from current value of the REG_30 register.
 *
 * Reads the REG_30 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpavmvbit2 - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5ginput1cbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5ginput2cbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvmrfdynen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvmrfdynvthbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvlenbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvlselvl1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl1opamen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl1icselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl1vbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl1cgmibit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl1rfdynvthbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_30_unpack(uint8_t* wfpavmvbit2, uint8_t* wfpa5ginput1cbit, uint8_t* wfpa5ginput2cbit, uint8_t* wfpa5gvmrfdynen, uint8_t* wfpa5gvmrfdynvthbit, uint8_t* wfpa5gvlenbit, uint8_t* wfpa5gvlselvl1, uint8_t* wfpa5gvl1opamen, uint8_t* wfpa5gvl1icselbit, uint8_t* wfpa5gvl1vbit, uint8_t* wfpa5gvl1cgmibit, uint8_t* wfpa5gvl1rfdynvthbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);

    *wfpavmvbit2 = (localVal & ((uint32_t)0x7E000000)) >> 25;
    *wfpa5ginput1cbit = (localVal & ((uint32_t)0x01800000)) >> 23;
    *wfpa5ginput2cbit = (localVal & ((uint32_t)0x00600000)) >> 21;
    *wfpa5gvmrfdynen = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wfpa5gvmrfdynvthbit = (localVal & ((uint32_t)0x000E0000)) >> 17;
    *wfpa5gvlenbit = (localVal & ((uint32_t)0x00018000)) >> 15;
    *wfpa5gvlselvl1 = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wfpa5gvl1opamen = (localVal & ((uint32_t)0x00002000)) >> 13;
    *wfpa5gvl1icselbit = (localVal & ((uint32_t)0x00001C00)) >> 10;
    *wfpa5gvl1vbit = (localVal & ((uint32_t)0x00000380)) >> 7;
    *wfpa5gvl1cgmibit = (localVal & ((uint32_t)0x00000078)) >> 3;
    *wfpa5gvl1rfdynvthbit = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pa_vm_vbit2 field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa_vm_vbit2 field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_vbit2 field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_vbit_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x7E000000)) >> 25);
}

/**
 * @brief Returns the current value of the wf_pa5g_input1_cbit field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_input1_cbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_input1_cbit field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_input_1_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x01800000)) >> 23);
}

/**
 * @brief Returns the current value of the wf_pa5g_input2_cbit field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_input2_cbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_input2_cbit field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_input_2_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00600000)) >> 21);
}

/**
 * @brief Returns the current value of the wf_pa5g_vm_rfdyn_en field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_vm_rfdyn_en field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vm_rfdyn_en field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vm_rfdyn_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Returns the current value of the wf_pa5g_vm_rfdyn_vthbit field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_vm_rfdyn_vthbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vm_rfdyn_vthbit field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vm_rfdyn_vthbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x000E0000)) >> 17);
}

/**
 * @brief Sets the wf_pa5g_vm_rfdyn_vthbit field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvmrfdynvthbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vm_rfdyn_vthbit_setf(uint8_t wfpa5gvmrfdynvthbit)
{
    REG_PL_WR(WLAN_RF_REG_30_ADDR, (REG_PL_RD(WLAN_RF_REG_30_ADDR) & ~((uint32_t)0x000E0000)) | (((uint32_t)wfpa5gvmrfdynvthbit << 17) & ((uint32_t)0x000E0000)));
}

/**
 * @brief Returns the current value of the wf_pa5g_vl_en_bit field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_vl_en_bit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl_en_bit field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_en_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00018000)) >> 15);
}

/**
 * @brief Returns the current value of the wf_pa5g_vl_sel_vl1 field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_vl_sel_vl1 field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl_sel_vl1 field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_sel_vl_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the wf_pa5g_vl_sel_vl1 field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvlselvl1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vl_sel_vl_1_setf(uint8_t wfpa5gvlselvl1)
{
    REG_PL_WR(WLAN_RF_REG_30_ADDR, (REG_PL_RD(WLAN_RF_REG_30_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)wfpa5gvlselvl1 << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the wf_pa5g_vl1_opam_en field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_vl1_opam_en field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl1_opam_en field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_1_opam_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the wf_pa5g_vl1_opam_en field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvl1opamen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vl_1_opam_en_setf(uint8_t wfpa5gvl1opamen)
{
    REG_PL_WR(WLAN_RF_REG_30_ADDR, (REG_PL_RD(WLAN_RF_REG_30_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)wfpa5gvl1opamen << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the wf_pa5g_vl1_ic_sel_bit field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_vl1_ic_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl1_ic_sel_bit field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_1_ic_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00001C00)) >> 10);
}

/**
 * @brief Sets the wf_pa5g_vl1_ic_sel_bit field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvl1icselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vl_1_ic_sel_bit_setf(uint8_t wfpa5gvl1icselbit)
{
    REG_PL_WR(WLAN_RF_REG_30_ADDR, (REG_PL_RD(WLAN_RF_REG_30_ADDR) & ~((uint32_t)0x00001C00)) | (((uint32_t)wfpa5gvl1icselbit << 10) & ((uint32_t)0x00001C00)));
}

/**
 * @brief Returns the current value of the wf_pa5g_vl1_vbit field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_vl1_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl1_vbit field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_1_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000380)) >> 7);
}

/**
 * @brief Returns the current value of the wf_pa5g_vl1_cgm_ibit field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_vl1_cgm_ibit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl1_cgm_ibit field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_1_cgm_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000078)) >> 3);
}

/**
 * @brief Sets the wf_pa5g_vl1_cgm_ibit field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvl1cgmibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vl_1_cgm_ibit_setf(uint8_t wfpa5gvl1cgmibit)
{
    REG_PL_WR(WLAN_RF_REG_30_ADDR, (REG_PL_RD(WLAN_RF_REG_30_ADDR) & ~((uint32_t)0x00000078)) | (((uint32_t)wfpa5gvl1cgmibit << 3) & ((uint32_t)0x00000078)));
}

/**
 * @brief Returns the current value of the wf_pa5g_vl1_rfdyn_vthbit field in the REG_30 register.
 *
 * The REG_30 register will be read and the wf_pa5g_vl1_rfdyn_vthbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl1_rfdyn_vthbit field in the REG_30 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_1_rfdyn_vthbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/**
 * @brief Sets the wf_pa5g_vl1_rfdyn_vthbit field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvl1rfdynvthbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vl_1_rfdyn_vthbit_setf(uint8_t wfpa5gvl1rfdynvthbit)
{
    REG_PL_WR(WLAN_RF_REG_30_ADDR, (REG_PL_RD(WLAN_RF_REG_30_ADDR) & ~((uint32_t)0x00000007)) | (((uint32_t)wfpa5gvl1rfdynvthbit << 0) & ((uint32_t)0x00000007)));
}

/// @}

/**
 * @name REG_34 register definitions
 * <table>
 * <caption id="REG_34_BF">REG_34 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30:28 <td>wf_pa5g_vl1_rfdyn_gbit <td>W <td>R <td>0x4
 * <tr><td>27 <td>wf_pa5g_vl1_rfdyn_en <td>W <td>R <td>0
 * <tr><td>26 <td>wf_pa5g_vl2_opam_en <td>R <td>R/W <td>1
 * <tr><td>25:23 <td>wf_pa5g_vl2_ic_sel_bit <td>R <td>R/W <td>0x1
 * <tr><td>22 <td>wf_pa5g_vl2_rfdyn_en <td>W <td>R <td>0
 * <tr><td>21:19 <td>  wf_pa5g_vl2_vbit <td>W <td>R <td>0x4
 * <tr><td>18:15 <td>wf_pa5g_vl2_cgm_ibit <td>R <td>R/W <td>0x8
 * <tr><td>14:12 <td>wf_pa5g_vl2_rfdyn_vthbit <td>R <td>R/W <td>0x4
 * <tr><td>11:09 <td>wf_pa5g_vl2_rfdyn_gbit <td>W <td>R <td>0x4
 * <tr><td>08:07 <td>wf_pa5g_vl1_resbit <td>W <td>R <td>0x3
 * <tr><td>06:05 <td>wf_pa5g_vl2_resbit <td>W <td>R <td>0x3
 * <tr><td>04 <td>wf_pa24g_vm_rfdyn_en <td>W <td>R <td>0
 * <tr><td>03:01 <td>wf_pa24g_vm_rfdyn_vthbit <td>R <td>R/W <td>0x4
 * <tr><td>00 <td>wf_pa24g_vl_rfdyn_en <td>W <td>R <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_34 register
#define WLAN_RF_REG_34_ADDR   0x40344034
/// Offset of the REG_34 register from the base address
#define WLAN_RF_REG_34_OFFSET 0x00000034
/// Index of the REG_34 register
#define WLAN_RF_REG_34_INDEX  0x0000000D
/// Reset value of the REG_34 register
#define WLAN_RF_REG_34_RESET  0x44A449E8

/**
 * @brief Returns the current value of the REG_34 register.
 * The REG_34 register will be read and its value returned.
 * @return The current value of the REG_34 register.
 */
__INLINE uint32_t wlan_rf_reg_34_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_34_ADDR);
}

/**
 * @brief Sets the REG_34 register to a value.
 * The REG_34 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_34_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_34_ADDR, value);
}

// field definitions
/// WF_PA_5G_VL_1_RFDYN_GBIT field mask
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_GBIT_MASK     ((uint32_t)0x70000000)
/// WF_PA_5G_VL_1_RFDYN_GBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_GBIT_LSB      28
/// WF_PA_5G_VL_1_RFDYN_GBIT field width
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_GBIT_WIDTH    ((uint32_t)0x00000003)
/// WF_PA_5G_VL_1_RFDYN_EN field bit
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_EN_BIT        ((uint32_t)0x08000000)
/// WF_PA_5G_VL_1_RFDYN_EN field position
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_EN_POS        27
/// WF_PA_5G_VL_2_OPAM_EN field bit
#define WLAN_RF_WF_PA_5G_VL_2_OPAM_EN_BIT         ((uint32_t)0x04000000)
/// WF_PA_5G_VL_2_OPAM_EN field position
#define WLAN_RF_WF_PA_5G_VL_2_OPAM_EN_POS         26
/// WF_PA_5G_VL_2_IC_SEL_BIT field mask
#define WLAN_RF_WF_PA_5G_VL_2_IC_SEL_BIT_MASK     ((uint32_t)0x03800000)
/// WF_PA_5G_VL_2_IC_SEL_BIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_2_IC_SEL_BIT_LSB      23
/// WF_PA_5G_VL_2_IC_SEL_BIT field width
#define WLAN_RF_WF_PA_5G_VL_2_IC_SEL_BIT_WIDTH    ((uint32_t)0x00000003)
/// WF_PA_5G_VL_2_RFDYN_EN field bit
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_EN_BIT        ((uint32_t)0x00400000)
/// WF_PA_5G_VL_2_RFDYN_EN field position
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_EN_POS        22
/// WF_PA_5G_VL_2_VBIT field mask
#define WLAN_RF_WF_PA_5G_VL_2_VBIT_MASK           ((uint32_t)0x00380000)
/// WF_PA_5G_VL_2_VBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_2_VBIT_LSB            19
/// WF_PA_5G_VL_2_VBIT field width
#define WLAN_RF_WF_PA_5G_VL_2_VBIT_WIDTH          ((uint32_t)0x00000003)
/// WF_PA_5G_VL_2_CGM_IBIT field mask
#define WLAN_RF_WF_PA_5G_VL_2_CGM_IBIT_MASK       ((uint32_t)0x00078000)
/// WF_PA_5G_VL_2_CGM_IBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_2_CGM_IBIT_LSB        15
/// WF_PA_5G_VL_2_CGM_IBIT field width
#define WLAN_RF_WF_PA_5G_VL_2_CGM_IBIT_WIDTH      ((uint32_t)0x00000004)
/// WF_PA_5G_VL_2_RFDYN_VTHBIT field mask
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_VTHBIT_MASK   ((uint32_t)0x00007000)
/// WF_PA_5G_VL_2_RFDYN_VTHBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_VTHBIT_LSB    12
/// WF_PA_5G_VL_2_RFDYN_VTHBIT field width
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_VTHBIT_WIDTH  ((uint32_t)0x00000003)
/// WF_PA_5G_VL_2_RFDYN_GBIT field mask
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_GBIT_MASK     ((uint32_t)0x00000E00)
/// WF_PA_5G_VL_2_RFDYN_GBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_GBIT_LSB      9
/// WF_PA_5G_VL_2_RFDYN_GBIT field width
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_GBIT_WIDTH    ((uint32_t)0x00000003)
/// WF_PA_5G_VL_1_RESBIT field mask
#define WLAN_RF_WF_PA_5G_VL_1_RESBIT_MASK         ((uint32_t)0x00000180)
/// WF_PA_5G_VL_1_RESBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_1_RESBIT_LSB          7
/// WF_PA_5G_VL_1_RESBIT field width
#define WLAN_RF_WF_PA_5G_VL_1_RESBIT_WIDTH        ((uint32_t)0x00000002)
/// WF_PA_5G_VL_2_RESBIT field mask
#define WLAN_RF_WF_PA_5G_VL_2_RESBIT_MASK         ((uint32_t)0x00000060)
/// WF_PA_5G_VL_2_RESBIT field LSB position
#define WLAN_RF_WF_PA_5G_VL_2_RESBIT_LSB          5
/// WF_PA_5G_VL_2_RESBIT field width
#define WLAN_RF_WF_PA_5G_VL_2_RESBIT_WIDTH        ((uint32_t)0x00000002)
/// WF_PA_24G_VM_RFDYN_EN field bit
#define WLAN_RF_WF_PA_24G_VM_RFDYN_EN_BIT         ((uint32_t)0x00000010)
/// WF_PA_24G_VM_RFDYN_EN field position
#define WLAN_RF_WF_PA_24G_VM_RFDYN_EN_POS         4
/// WF_PA_24G_VM_RFDYN_VTHBIT field mask
#define WLAN_RF_WF_PA_24G_VM_RFDYN_VTHBIT_MASK    ((uint32_t)0x0000000E)
/// WF_PA_24G_VM_RFDYN_VTHBIT field LSB position
#define WLAN_RF_WF_PA_24G_VM_RFDYN_VTHBIT_LSB     1
/// WF_PA_24G_VM_RFDYN_VTHBIT field width
#define WLAN_RF_WF_PA_24G_VM_RFDYN_VTHBIT_WIDTH   ((uint32_t)0x00000003)
/// WF_PA_24G_VL_RFDYN_EN field bit
#define WLAN_RF_WF_PA_24G_VL_RFDYN_EN_BIT         ((uint32_t)0x00000001)
/// WF_PA_24G_VL_RFDYN_EN field position
#define WLAN_RF_WF_PA_24G_VL_RFDYN_EN_POS         0

/// WF_PA_5G_VL_1_RFDYN_GBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_GBIT_RST      0x4
/// WF_PA_5G_VL_1_RFDYN_EN field reset value
#define WLAN_RF_WF_PA_5G_VL_1_RFDYN_EN_RST        0x0
/// WF_PA_5G_VL_2_OPAM_EN field reset value
#define WLAN_RF_WF_PA_5G_VL_2_OPAM_EN_RST         0x1
/// WF_PA_5G_VL_2_IC_SEL_BIT field reset value
#define WLAN_RF_WF_PA_5G_VL_2_IC_SEL_BIT_RST      0x1
/// WF_PA_5G_VL_2_RFDYN_EN field reset value
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_EN_RST        0x0
/// WF_PA_5G_VL_2_VBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_2_VBIT_RST            0x4
/// WF_PA_5G_VL_2_CGM_IBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_2_CGM_IBIT_RST        0x8
/// WF_PA_5G_VL_2_RFDYN_VTHBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_VTHBIT_RST    0x4
/// WF_PA_5G_VL_2_RFDYN_GBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_2_RFDYN_GBIT_RST      0x4
/// WF_PA_5G_VL_1_RESBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_1_RESBIT_RST          0x3
/// WF_PA_5G_VL_2_RESBIT field reset value
#define WLAN_RF_WF_PA_5G_VL_2_RESBIT_RST          0x3
/// WF_PA_24G_VM_RFDYN_EN field reset value
#define WLAN_RF_WF_PA_24G_VM_RFDYN_EN_RST         0x0
/// WF_PA_24G_VM_RFDYN_VTHBIT field reset value
#define WLAN_RF_WF_PA_24G_VM_RFDYN_VTHBIT_RST     0x4
/// WF_PA_24G_VL_RFDYN_EN field reset value
#define WLAN_RF_WF_PA_24G_VL_RFDYN_EN_RST         0x0

/**
 * @brief Constructs a value for the REG_34 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpa5gvl2opamen - The value to use for the wf_pa5g_vl2_opam_en field.
 * @param[in] wfpa5gvl2icselbit - The value to use for the wf_pa5g_vl2_ic_sel_bit field.
 * @param[in] wfpa5gvl2cgmibit - The value to use for the wf_pa5g_vl2_cgm_ibit field.
 * @param[in] wfpa5gvl2rfdynvthbit - The value to use for the wf_pa5g_vl2_rfdyn_vthbit field.
 * @param[in] wfpa24gvmrfdynvthbit - The value to use for the wf_pa24g_vm_rfdyn_vthbit field.
 */
__INLINE void wlan_rf_reg_34_pack(uint8_t wfpa5gvl2opamen, uint8_t wfpa5gvl2icselbit, uint8_t wfpa5gvl2cgmibit, uint8_t wfpa5gvl2rfdynvthbit, uint8_t wfpa24gvmrfdynvthbit)
{
    REG_PL_WR(WLAN_RF_REG_34_ADDR,  ((uint32_t)wfpa5gvl2opamen << 26) | ((uint32_t)wfpa5gvl2icselbit << 23) | ((uint32_t)wfpa5gvl2cgmibit << 15) | ((uint32_t)wfpa5gvl2rfdynvthbit << 12) | ((uint32_t)wfpa24gvmrfdynvthbit << 1));
}

/**
 * @brief Unpacks REG_34's fields from current value of the REG_34 register.
 *
 * Reads the REG_34 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpa5gvl1rfdyngbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl1rfdynen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl2opamen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl2icselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl2rfdynen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl2vbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl2cgmibit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl2rfdynvthbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl2rfdyngbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl1resbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gvl2resbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gvmrfdynen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gvmrfdynvthbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gvlrfdynen - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_34_unpack(uint8_t* wfpa5gvl1rfdyngbit, uint8_t* wfpa5gvl1rfdynen, uint8_t* wfpa5gvl2opamen, uint8_t* wfpa5gvl2icselbit, uint8_t* wfpa5gvl2rfdynen, uint8_t* wfpa5gvl2vbit, uint8_t* wfpa5gvl2cgmibit, uint8_t* wfpa5gvl2rfdynvthbit, uint8_t* wfpa5gvl2rfdyngbit, uint8_t* wfpa5gvl1resbit, uint8_t* wfpa5gvl2resbit, uint8_t* wfpa24gvmrfdynen, uint8_t* wfpa24gvmrfdynvthbit, uint8_t* wfpa24gvlrfdynen)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);

    *wfpa5gvl1rfdyngbit = (localVal & ((uint32_t)0x70000000)) >> 28;
    *wfpa5gvl1rfdynen = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfpa5gvl2opamen = (localVal & ((uint32_t)0x04000000)) >> 26;
    *wfpa5gvl2icselbit = (localVal & ((uint32_t)0x03800000)) >> 23;
    *wfpa5gvl2rfdynen = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wfpa5gvl2vbit = (localVal & ((uint32_t)0x00380000)) >> 19;
    *wfpa5gvl2cgmibit = (localVal & ((uint32_t)0x00078000)) >> 15;
    *wfpa5gvl2rfdynvthbit = (localVal & ((uint32_t)0x00007000)) >> 12;
    *wfpa5gvl2rfdyngbit = (localVal & ((uint32_t)0x00000E00)) >> 9;
    *wfpa5gvl1resbit = (localVal & ((uint32_t)0x00000180)) >> 7;
    *wfpa5gvl2resbit = (localVal & ((uint32_t)0x00000060)) >> 5;
    *wfpa24gvmrfdynen = (localVal & ((uint32_t)0x00000010)) >> 4;
    *wfpa24gvmrfdynvthbit = (localVal & ((uint32_t)0x0000000E)) >> 1;
    *wfpa24gvlrfdynen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pa5g_vl1_rfdyn_gbit field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl1_rfdyn_gbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl1_rfdyn_gbit field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_1_rfdyn_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

/**
 * @brief Returns the current value of the wf_pa5g_vl1_rfdyn_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl1_rfdyn_en field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl1_rfdyn_en field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_1_rfdyn_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Returns the current value of the wf_pa5g_vl2_opam_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl2_opam_en field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl2_opam_en field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_2_opam_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the wf_pa5g_vl2_opam_en field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvl2opamen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vl_2_opam_en_setf(uint8_t wfpa5gvl2opamen)
{
    REG_PL_WR(WLAN_RF_REG_34_ADDR, (REG_PL_RD(WLAN_RF_REG_34_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)wfpa5gvl2opamen << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the wf_pa5g_vl2_ic_sel_bit field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl2_ic_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl2_ic_sel_bit field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_2_ic_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x03800000)) >> 23);
}

/**
 * @brief Sets the wf_pa5g_vl2_ic_sel_bit field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvl2icselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vl_2_ic_sel_bit_setf(uint8_t wfpa5gvl2icselbit)
{
    REG_PL_WR(WLAN_RF_REG_34_ADDR, (REG_PL_RD(WLAN_RF_REG_34_ADDR) & ~((uint32_t)0x03800000)) | (((uint32_t)wfpa5gvl2icselbit << 23) & ((uint32_t)0x03800000)));
}

/**
 * @brief Returns the current value of the wf_pa5g_vl2_rfdyn_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl2_rfdyn_en field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl2_rfdyn_en field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_2_rfdyn_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Returns the current value of the wf_pa5g_vl2_vbit field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl2_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl2_vbit field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_2_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00380000)) >> 19);
}

/**
 * @brief Returns the current value of the wf_pa5g_vl2_cgm_ibit field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl2_cgm_ibit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl2_cgm_ibit field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_2_cgm_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00078000)) >> 15);
}

/**
 * @brief Sets the wf_pa5g_vl2_cgm_ibit field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvl2cgmibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vl_2_cgm_ibit_setf(uint8_t wfpa5gvl2cgmibit)
{
    REG_PL_WR(WLAN_RF_REG_34_ADDR, (REG_PL_RD(WLAN_RF_REG_34_ADDR) & ~((uint32_t)0x00078000)) | (((uint32_t)wfpa5gvl2cgmibit << 15) & ((uint32_t)0x00078000)));
}

/**
 * @brief Returns the current value of the wf_pa5g_vl2_rfdyn_vthbit field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl2_rfdyn_vthbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl2_rfdyn_vthbit field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_2_rfdyn_vthbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

/**
 * @brief Sets the wf_pa5g_vl2_rfdyn_vthbit field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gvl2rfdynvthbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_vl_2_rfdyn_vthbit_setf(uint8_t wfpa5gvl2rfdynvthbit)
{
    REG_PL_WR(WLAN_RF_REG_34_ADDR, (REG_PL_RD(WLAN_RF_REG_34_ADDR) & ~((uint32_t)0x00007000)) | (((uint32_t)wfpa5gvl2rfdynvthbit << 12) & ((uint32_t)0x00007000)));
}

/**
 * @brief Returns the current value of the wf_pa5g_vl2_rfdyn_gbit field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl2_rfdyn_gbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl2_rfdyn_gbit field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_2_rfdyn_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000E00)) >> 9);
}

/**
 * @brief Returns the current value of the wf_pa5g_vl1_resbit field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl1_resbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl1_resbit field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_1_resbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000180)) >> 7);
}

/**
 * @brief Returns the current value of the wf_pa5g_vl2_resbit field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa5g_vl2_resbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_vl2_resbit field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_vl_2_resbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000060)) >> 5);
}

/**
 * @brief Returns the current value of the wf_pa24g_vm_rfdyn_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa24g_vm_rfdyn_en field's value will be returned.
 *
 * @return The current value of the wf_pa24g_vm_rfdyn_en field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_vm_rfdyn_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Returns the current value of the wf_pa24g_vm_rfdyn_vthbit field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa24g_vm_rfdyn_vthbit field's value will be returned.
 *
 * @return The current value of the wf_pa24g_vm_rfdyn_vthbit field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_vm_rfdyn_vthbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x0000000E)) >> 1);
}

/**
 * @brief Sets the wf_pa24g_vm_rfdyn_vthbit field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24gvmrfdynvthbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_vm_rfdyn_vthbit_setf(uint8_t wfpa24gvmrfdynvthbit)
{
    REG_PL_WR(WLAN_RF_REG_34_ADDR, (REG_PL_RD(WLAN_RF_REG_34_ADDR) & ~((uint32_t)0x0000000E)) | (((uint32_t)wfpa24gvmrfdynvthbit << 1) & ((uint32_t)0x0000000E)));
}

/**
 * @brief Returns the current value of the wf_pa24g_vl_rfdyn_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the wf_pa24g_vl_rfdyn_en field's value will be returned.
 *
 * @return The current value of the wf_pa24g_vl_rfdyn_en field in the REG_34 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_vl_rfdyn_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/// @}

/**
 * @name REG_38 register definitions
 * <table>
 * <caption id="REG_38_BF">REG_38 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>28:26 <td>wf_pa24g_vl_rfdyn_vthbit <td>R <td>R/W <td>0x4
 * <tr><td>25:23 <td>wf_pa24g_vl_rfdyn_gbit <td>W <td>R <td>0x4
 * <tr><td>22:19 <td>wf_pa24g_vl_cgm_ibit <td>W <td>R <td>0x8
 * <tr><td>18:16 <td>wf_pa24g_vl_ic_sel_bit <td>R <td>R/W <td>0x1
 * <tr><td>15 <td>wf_pa24g_vl_opam_en <td>R <td>R/W <td>1
 * <tr><td>14:12 <td>  wf_pa24g_vl_vbit <td>W <td>R <td>0x4
 * <tr><td>11:08 <td>  wf_trx5g_sw_cbit <td>W <td>R <td>0x8
 * <tr><td>07:04 <td> wf_trx24g_sw_cbit <td>W <td>R <td>0x8
 * <tr><td>03:00 <td>wf_pa5g_avss_hd1_cbit <td>R <td>R/W <td>0x8
 * </table>
 *
 * @{
 */

/// Address of the REG_38 register
#define WLAN_RF_REG_38_ADDR   0x40344038
/// Offset of the REG_38 register from the base address
#define WLAN_RF_REG_38_OFFSET 0x00000038
/// Index of the REG_38 register
#define WLAN_RF_REG_38_INDEX  0x0000000E
/// Reset value of the REG_38 register
#define WLAN_RF_REG_38_RESET  0x1241C888

/**
 * @brief Returns the current value of the REG_38 register.
 * The REG_38 register will be read and its value returned.
 * @return The current value of the REG_38 register.
 */
__INLINE uint32_t wlan_rf_reg_38_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_38_ADDR);
}

/**
 * @brief Sets the REG_38 register to a value.
 * The REG_38 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_38_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_38_ADDR, value);
}

// field definitions
/// WF_PA_24G_VL_RFDYN_VTHBIT field mask
#define WLAN_RF_WF_PA_24G_VL_RFDYN_VTHBIT_MASK   ((uint32_t)0x1C000000)
/// WF_PA_24G_VL_RFDYN_VTHBIT field LSB position
#define WLAN_RF_WF_PA_24G_VL_RFDYN_VTHBIT_LSB    26
/// WF_PA_24G_VL_RFDYN_VTHBIT field width
#define WLAN_RF_WF_PA_24G_VL_RFDYN_VTHBIT_WIDTH  ((uint32_t)0x00000003)
/// WF_PA_24G_VL_RFDYN_GBIT field mask
#define WLAN_RF_WF_PA_24G_VL_RFDYN_GBIT_MASK     ((uint32_t)0x03800000)
/// WF_PA_24G_VL_RFDYN_GBIT field LSB position
#define WLAN_RF_WF_PA_24G_VL_RFDYN_GBIT_LSB      23
/// WF_PA_24G_VL_RFDYN_GBIT field width
#define WLAN_RF_WF_PA_24G_VL_RFDYN_GBIT_WIDTH    ((uint32_t)0x00000003)
/// WF_PA_24G_VL_CGM_IBIT field mask
#define WLAN_RF_WF_PA_24G_VL_CGM_IBIT_MASK       ((uint32_t)0x00780000)
/// WF_PA_24G_VL_CGM_IBIT field LSB position
#define WLAN_RF_WF_PA_24G_VL_CGM_IBIT_LSB        19
/// WF_PA_24G_VL_CGM_IBIT field width
#define WLAN_RF_WF_PA_24G_VL_CGM_IBIT_WIDTH      ((uint32_t)0x00000004)
/// WF_PA_24G_VL_IC_SEL_BIT field mask
#define WLAN_RF_WF_PA_24G_VL_IC_SEL_BIT_MASK     ((uint32_t)0x00070000)
/// WF_PA_24G_VL_IC_SEL_BIT field LSB position
#define WLAN_RF_WF_PA_24G_VL_IC_SEL_BIT_LSB      16
/// WF_PA_24G_VL_IC_SEL_BIT field width
#define WLAN_RF_WF_PA_24G_VL_IC_SEL_BIT_WIDTH    ((uint32_t)0x00000003)
/// WF_PA_24G_VL_OPAM_EN field bit
#define WLAN_RF_WF_PA_24G_VL_OPAM_EN_BIT         ((uint32_t)0x00008000)
/// WF_PA_24G_VL_OPAM_EN field position
#define WLAN_RF_WF_PA_24G_VL_OPAM_EN_POS         15
/// WF_PA_24G_VL_VBIT field mask
#define WLAN_RF_WF_PA_24G_VL_VBIT_MASK           ((uint32_t)0x00007000)
/// WF_PA_24G_VL_VBIT field LSB position
#define WLAN_RF_WF_PA_24G_VL_VBIT_LSB            12
/// WF_PA_24G_VL_VBIT field width
#define WLAN_RF_WF_PA_24G_VL_VBIT_WIDTH          ((uint32_t)0x00000003)
/// WF_TRX_5G_SW_CBIT field mask
#define WLAN_RF_WF_TRX_5G_SW_CBIT_MASK           ((uint32_t)0x00000F00)
/// WF_TRX_5G_SW_CBIT field LSB position
#define WLAN_RF_WF_TRX_5G_SW_CBIT_LSB            8
/// WF_TRX_5G_SW_CBIT field width
#define WLAN_RF_WF_TRX_5G_SW_CBIT_WIDTH          ((uint32_t)0x00000004)
/// WF_TRX_24G_SW_CBIT field mask
#define WLAN_RF_WF_TRX_24G_SW_CBIT_MASK          ((uint32_t)0x000000F0)
/// WF_TRX_24G_SW_CBIT field LSB position
#define WLAN_RF_WF_TRX_24G_SW_CBIT_LSB           4
/// WF_TRX_24G_SW_CBIT field width
#define WLAN_RF_WF_TRX_24G_SW_CBIT_WIDTH         ((uint32_t)0x00000004)
/// WF_PA_5G_AVSS_HD_1_CBIT field mask
#define WLAN_RF_WF_PA_5G_AVSS_HD_1_CBIT_MASK     ((uint32_t)0x0000000F)
/// WF_PA_5G_AVSS_HD_1_CBIT field LSB position
#define WLAN_RF_WF_PA_5G_AVSS_HD_1_CBIT_LSB      0
/// WF_PA_5G_AVSS_HD_1_CBIT field width
#define WLAN_RF_WF_PA_5G_AVSS_HD_1_CBIT_WIDTH    ((uint32_t)0x00000004)

/// WF_PA_24G_VL_RFDYN_VTHBIT field reset value
#define WLAN_RF_WF_PA_24G_VL_RFDYN_VTHBIT_RST    0x4
/// WF_PA_24G_VL_RFDYN_GBIT field reset value
#define WLAN_RF_WF_PA_24G_VL_RFDYN_GBIT_RST      0x4
/// WF_PA_24G_VL_CGM_IBIT field reset value
#define WLAN_RF_WF_PA_24G_VL_CGM_IBIT_RST        0x8
/// WF_PA_24G_VL_IC_SEL_BIT field reset value
#define WLAN_RF_WF_PA_24G_VL_IC_SEL_BIT_RST      0x1
/// WF_PA_24G_VL_OPAM_EN field reset value
#define WLAN_RF_WF_PA_24G_VL_OPAM_EN_RST         0x1
/// WF_PA_24G_VL_VBIT field reset value
#define WLAN_RF_WF_PA_24G_VL_VBIT_RST            0x4
/// WF_TRX_5G_SW_CBIT field reset value
#define WLAN_RF_WF_TRX_5G_SW_CBIT_RST            0x8
/// WF_TRX_24G_SW_CBIT field reset value
#define WLAN_RF_WF_TRX_24G_SW_CBIT_RST           0x8
/// WF_PA_5G_AVSS_HD_1_CBIT field reset value
#define WLAN_RF_WF_PA_5G_AVSS_HD_1_CBIT_RST      0x8

/**
 * @brief Constructs a value for the REG_38 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpa24gvlrfdynvthbit - The value to use for the wf_pa24g_vl_rfdyn_vthbit field.
 * @param[in] wfpa24gvlicselbit - The value to use for the wf_pa24g_vl_ic_sel_bit field.
 * @param[in] wfpa24gvlopamen - The value to use for the wf_pa24g_vl_opam_en field.
 * @param[in] wfpa5gavsshd1cbit - The value to use for the wf_pa5g_avss_hd1_cbit field.
 */
__INLINE void wlan_rf_reg_38_pack(uint8_t wfpa24gvlrfdynvthbit, uint8_t wfpa24gvlicselbit, uint8_t wfpa24gvlopamen, uint8_t wfpa5gavsshd1cbit)
{
    REG_PL_WR(WLAN_RF_REG_38_ADDR,  ((uint32_t)wfpa24gvlrfdynvthbit << 26) | ((uint32_t)wfpa24gvlicselbit << 16) | ((uint32_t)wfpa24gvlopamen << 15) | ((uint32_t)wfpa5gavsshd1cbit << 0));
}

/**
 * @brief Unpacks REG_38's fields from current value of the REG_38 register.
 *
 * Reads the REG_38 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpa24gvlrfdynvthbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gvlrfdyngbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gvlcgmibit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gvlicselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gvlopamen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gvlvbit - Will be populated with the current value of this field from the register.
 * @param[out] wftrx5gswcbit - Will be populated with the current value of this field from the register.
 * @param[out] wftrx24gswcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gavsshd1cbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_38_unpack(uint8_t* wfpa24gvlrfdynvthbit, uint8_t* wfpa24gvlrfdyngbit, uint8_t* wfpa24gvlcgmibit, uint8_t* wfpa24gvlicselbit, uint8_t* wfpa24gvlopamen, uint8_t* wfpa24gvlvbit, uint8_t* wftrx5gswcbit, uint8_t* wftrx24gswcbit, uint8_t* wfpa5gavsshd1cbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);

    *wfpa24gvlrfdynvthbit = (localVal & ((uint32_t)0x1C000000)) >> 26;
    *wfpa24gvlrfdyngbit = (localVal & ((uint32_t)0x03800000)) >> 23;
    *wfpa24gvlcgmibit = (localVal & ((uint32_t)0x00780000)) >> 19;
    *wfpa24gvlicselbit = (localVal & ((uint32_t)0x00070000)) >> 16;
    *wfpa24gvlopamen = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wfpa24gvlvbit = (localVal & ((uint32_t)0x00007000)) >> 12;
    *wftrx5gswcbit = (localVal & ((uint32_t)0x00000F00)) >> 8;
    *wftrx24gswcbit = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *wfpa5gavsshd1cbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pa24g_vl_rfdyn_vthbit field in the REG_38 register.
 *
 * The REG_38 register will be read and the wf_pa24g_vl_rfdyn_vthbit field's value will be returned.
 *
 * @return The current value of the wf_pa24g_vl_rfdyn_vthbit field in the REG_38 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_vl_rfdyn_vthbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x1C000000)) >> 26);
}

/**
 * @brief Sets the wf_pa24g_vl_rfdyn_vthbit field of the REG_38 register.
 *
 * The REG_38 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24gvlrfdynvthbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_vl_rfdyn_vthbit_setf(uint8_t wfpa24gvlrfdynvthbit)
{
    REG_PL_WR(WLAN_RF_REG_38_ADDR, (REG_PL_RD(WLAN_RF_REG_38_ADDR) & ~((uint32_t)0x1C000000)) | (((uint32_t)wfpa24gvlrfdynvthbit << 26) & ((uint32_t)0x1C000000)));
}

/**
 * @brief Returns the current value of the wf_pa24g_vl_rfdyn_gbit field in the REG_38 register.
 *
 * The REG_38 register will be read and the wf_pa24g_vl_rfdyn_gbit field's value will be returned.
 *
 * @return The current value of the wf_pa24g_vl_rfdyn_gbit field in the REG_38 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_vl_rfdyn_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x03800000)) >> 23);
}

/**
 * @brief Returns the current value of the wf_pa24g_vl_cgm_ibit field in the REG_38 register.
 *
 * The REG_38 register will be read and the wf_pa24g_vl_cgm_ibit field's value will be returned.
 *
 * @return The current value of the wf_pa24g_vl_cgm_ibit field in the REG_38 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_vl_cgm_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x00780000)) >> 19);
}

/**
 * @brief Returns the current value of the wf_pa24g_vl_ic_sel_bit field in the REG_38 register.
 *
 * The REG_38 register will be read and the wf_pa24g_vl_ic_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_pa24g_vl_ic_sel_bit field in the REG_38 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_vl_ic_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x00070000)) >> 16);
}

/**
 * @brief Sets the wf_pa24g_vl_ic_sel_bit field of the REG_38 register.
 *
 * The REG_38 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24gvlicselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_vl_ic_sel_bit_setf(uint8_t wfpa24gvlicselbit)
{
    REG_PL_WR(WLAN_RF_REG_38_ADDR, (REG_PL_RD(WLAN_RF_REG_38_ADDR) & ~((uint32_t)0x00070000)) | (((uint32_t)wfpa24gvlicselbit << 16) & ((uint32_t)0x00070000)));
}

/**
 * @brief Returns the current value of the wf_pa24g_vl_opam_en field in the REG_38 register.
 *
 * The REG_38 register will be read and the wf_pa24g_vl_opam_en field's value will be returned.
 *
 * @return The current value of the wf_pa24g_vl_opam_en field in the REG_38 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_vl_opam_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the wf_pa24g_vl_opam_en field of the REG_38 register.
 *
 * The REG_38 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24gvlopamen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_vl_opam_en_setf(uint8_t wfpa24gvlopamen)
{
    REG_PL_WR(WLAN_RF_REG_38_ADDR, (REG_PL_RD(WLAN_RF_REG_38_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)wfpa24gvlopamen << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the wf_pa24g_vl_vbit field in the REG_38 register.
 *
 * The REG_38 register will be read and the wf_pa24g_vl_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa24g_vl_vbit field in the REG_38 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_vl_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

/**
 * @brief Returns the current value of the wf_trx5g_sw_cbit field in the REG_38 register.
 *
 * The REG_38 register will be read and the wf_trx5g_sw_cbit field's value will be returned.
 *
 * @return The current value of the wf_trx5g_sw_cbit field in the REG_38 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_5g_sw_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x00000F00)) >> 8);
}

/**
 * @brief Returns the current value of the wf_trx24g_sw_cbit field in the REG_38 register.
 *
 * The REG_38 register will be read and the wf_trx24g_sw_cbit field's value will be returned.
 *
 * @return The current value of the wf_trx24g_sw_cbit field in the REG_38 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_24g_sw_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Returns the current value of the wf_pa5g_avss_hd1_cbit field in the REG_38 register.
 *
 * The REG_38 register will be read and the wf_pa5g_avss_hd1_cbit field's value will be returned.
 *
 * @return The current value of the wf_pa5g_avss_hd1_cbit field in the REG_38 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_avss_hd_1_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the wf_pa5g_avss_hd1_cbit field of the REG_38 register.
 *
 * The REG_38 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gavsshd1cbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_avss_hd_1_cbit_setf(uint8_t wfpa5gavsshd1cbit)
{
    REG_PL_WR(WLAN_RF_REG_38_ADDR, (REG_PL_RD(WLAN_RF_REG_38_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)wfpa5gavsshd1cbit << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name REG_3C register definitions
 * <table>
 * <caption id="REG_3C_BF">REG_3C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>23:20 <td>wf_pa24g_rfop_hd2_cbit_tx <td>R <td>R/W <td>0x8
 * <tr><td>19:16 <td>wf_pa24g_rfop_hd2_cbit_rx <td>R <td>R/W <td>0x8
 * <tr><td>15 <td>     wf_pa_loft_en <td>R <td>R/W <td>0
 * <tr><td>14:12 <td>   wf_pa_loft_gbit <td>R <td>R/W <td>0x4
 * <tr><td>11 <td>wf_pa_loft_sel_lowpass <td>R <td>R/W <td>0
 * <tr><td>10 <td>    wf_pa_pkdet_en <td>R <td>R/W <td>0
 * <tr><td>09:07 <td>wf_pa_pkdet_vth_bit <td>R <td>R/W <td>0x4
 * <tr><td>06 <td>     wf_pa_pkd_out <td>W <td>R <td>0
 * <tr><td>05 <td>      wf_pa_dpd_en <td>R <td>R/W <td>0
 * <tr><td>04:02 <td>    wf_pa_dpd_cbit <td>R <td>R/W <td>0x4
 * <tr><td>01 <td> wf_pa5g_isense_en <td>R <td>R/W <td>0
 * <tr><td>00 <td>wf_pa5g_isense_sel_ic5u <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_3C register
#define WLAN_RF_REG_3C_ADDR   0x4034403C
/// Offset of the REG_3C register from the base address
#define WLAN_RF_REG_3C_OFFSET 0x0000003C
/// Index of the REG_3C register
#define WLAN_RF_REG_3C_INDEX  0x0000000F
/// Reset value of the REG_3C register
#define WLAN_RF_REG_3C_RESET  0x00884210

/**
 * @brief Returns the current value of the REG_3C register.
 * The REG_3C register will be read and its value returned.
 * @return The current value of the REG_3C register.
 */
__INLINE uint32_t wlan_rf_reg_3c_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_3C_ADDR);
}

/**
 * @brief Sets the REG_3C register to a value.
 * The REG_3C register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_3c_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, value);
}

// field definitions
/// WF_PA_24G_RFOP_HD_2_CBIT_TX field mask
#define WLAN_RF_WF_PA_24G_RFOP_HD_2_CBIT_TX_MASK   ((uint32_t)0x00F00000)
/// WF_PA_24G_RFOP_HD_2_CBIT_TX field LSB position
#define WLAN_RF_WF_PA_24G_RFOP_HD_2_CBIT_TX_LSB    20
/// WF_PA_24G_RFOP_HD_2_CBIT_TX field width
#define WLAN_RF_WF_PA_24G_RFOP_HD_2_CBIT_TX_WIDTH  ((uint32_t)0x00000004)
/// WF_PA_24G_RFOP_HD_2_CBIT_RX field mask
#define WLAN_RF_WF_PA_24G_RFOP_HD_2_CBIT_RX_MASK   ((uint32_t)0x000F0000)
/// WF_PA_24G_RFOP_HD_2_CBIT_RX field LSB position
#define WLAN_RF_WF_PA_24G_RFOP_HD_2_CBIT_RX_LSB    16
/// WF_PA_24G_RFOP_HD_2_CBIT_RX field width
#define WLAN_RF_WF_PA_24G_RFOP_HD_2_CBIT_RX_WIDTH  ((uint32_t)0x00000004)
/// WF_PA_LOFT_EN field bit
#define WLAN_RF_WF_PA_LOFT_EN_BIT                  ((uint32_t)0x00008000)
/// WF_PA_LOFT_EN field position
#define WLAN_RF_WF_PA_LOFT_EN_POS                  15
/// WF_PA_LOFT_GBIT field mask
#define WLAN_RF_WF_PA_LOFT_GBIT_MASK               ((uint32_t)0x00007000)
/// WF_PA_LOFT_GBIT field LSB position
#define WLAN_RF_WF_PA_LOFT_GBIT_LSB                12
/// WF_PA_LOFT_GBIT field width
#define WLAN_RF_WF_PA_LOFT_GBIT_WIDTH              ((uint32_t)0x00000003)
/// WF_PA_LOFT_SEL_LOWPASS field bit
#define WLAN_RF_WF_PA_LOFT_SEL_LOWPASS_BIT         ((uint32_t)0x00000800)
/// WF_PA_LOFT_SEL_LOWPASS field position
#define WLAN_RF_WF_PA_LOFT_SEL_LOWPASS_POS         11
/// WF_PA_PKDET_EN field bit
#define WLAN_RF_WF_PA_PKDET_EN_BIT                 ((uint32_t)0x00000400)
/// WF_PA_PKDET_EN field position
#define WLAN_RF_WF_PA_PKDET_EN_POS                 10
/// WF_PA_PKDET_VTH_BIT field mask
#define WLAN_RF_WF_PA_PKDET_VTH_BIT_MASK           ((uint32_t)0x00000380)
/// WF_PA_PKDET_VTH_BIT field LSB position
#define WLAN_RF_WF_PA_PKDET_VTH_BIT_LSB            7
/// WF_PA_PKDET_VTH_BIT field width
#define WLAN_RF_WF_PA_PKDET_VTH_BIT_WIDTH          ((uint32_t)0x00000003)
/// WF_PA_PKD_OUT field bit
#define WLAN_RF_WF_PA_PKD_OUT_BIT                  ((uint32_t)0x00000040)
/// WF_PA_PKD_OUT field position
#define WLAN_RF_WF_PA_PKD_OUT_POS                  6
/// WF_PA_DPD_EN field bit
#define WLAN_RF_WF_PA_DPD_EN_BIT                   ((uint32_t)0x00000020)
/// WF_PA_DPD_EN field position
#define WLAN_RF_WF_PA_DPD_EN_POS                   5
/// WF_PA_DPD_CBIT field mask
#define WLAN_RF_WF_PA_DPD_CBIT_MASK                ((uint32_t)0x0000001C)
/// WF_PA_DPD_CBIT field LSB position
#define WLAN_RF_WF_PA_DPD_CBIT_LSB                 2
/// WF_PA_DPD_CBIT field width
#define WLAN_RF_WF_PA_DPD_CBIT_WIDTH               ((uint32_t)0x00000003)
/// WF_PA_5G_ISENSE_EN field bit
#define WLAN_RF_WF_PA_5G_ISENSE_EN_BIT             ((uint32_t)0x00000002)
/// WF_PA_5G_ISENSE_EN field position
#define WLAN_RF_WF_PA_5G_ISENSE_EN_POS             1
/// WF_PA_5G_ISENSE_SEL_IC_5U field bit
#define WLAN_RF_WF_PA_5G_ISENSE_SEL_IC_5U_BIT      ((uint32_t)0x00000001)
/// WF_PA_5G_ISENSE_SEL_IC_5U field position
#define WLAN_RF_WF_PA_5G_ISENSE_SEL_IC_5U_POS      0

/// WF_PA_24G_RFOP_HD_2_CBIT_TX field reset value
#define WLAN_RF_WF_PA_24G_RFOP_HD_2_CBIT_TX_RST    0x8
/// WF_PA_24G_RFOP_HD_2_CBIT_RX field reset value
#define WLAN_RF_WF_PA_24G_RFOP_HD_2_CBIT_RX_RST    0x8
/// WF_PA_LOFT_EN field reset value
#define WLAN_RF_WF_PA_LOFT_EN_RST                  0x0
/// WF_PA_LOFT_GBIT field reset value
#define WLAN_RF_WF_PA_LOFT_GBIT_RST                0x4
/// WF_PA_LOFT_SEL_LOWPASS field reset value
#define WLAN_RF_WF_PA_LOFT_SEL_LOWPASS_RST         0x0
/// WF_PA_PKDET_EN field reset value
#define WLAN_RF_WF_PA_PKDET_EN_RST                 0x0
/// WF_PA_PKDET_VTH_BIT field reset value
#define WLAN_RF_WF_PA_PKDET_VTH_BIT_RST            0x4
/// WF_PA_PKD_OUT field reset value
#define WLAN_RF_WF_PA_PKD_OUT_RST                  0x0
/// WF_PA_DPD_EN field reset value
#define WLAN_RF_WF_PA_DPD_EN_RST                   0x0
/// WF_PA_DPD_CBIT field reset value
#define WLAN_RF_WF_PA_DPD_CBIT_RST                 0x4
/// WF_PA_5G_ISENSE_EN field reset value
#define WLAN_RF_WF_PA_5G_ISENSE_EN_RST             0x0
/// WF_PA_5G_ISENSE_SEL_IC_5U field reset value
#define WLAN_RF_WF_PA_5G_ISENSE_SEL_IC_5U_RST      0x0

/**
 * @brief Constructs a value for the REG_3C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpa24grfophd2cbittx - The value to use for the wf_pa24g_rfop_hd2_cbit_tx field.
 * @param[in] wfpa24grfophd2cbitrx - The value to use for the wf_pa24g_rfop_hd2_cbit_rx field.
 * @param[in] wfpaloften - The value to use for the wf_pa_loft_en field.
 * @param[in] wfpaloftgbit - The value to use for the wf_pa_loft_gbit field.
 * @param[in] wfpaloftsellowpass - The value to use for the wf_pa_loft_sel_lowpass field.
 * @param[in] wfpapkdeten - The value to use for the wf_pa_pkdet_en field.
 * @param[in] wfpapkdetvthbit - The value to use for the wf_pa_pkdet_vth_bit field.
 * @param[in] wfpadpden - The value to use for the wf_pa_dpd_en field.
 * @param[in] wfpadpdcbit - The value to use for the wf_pa_dpd_cbit field.
 * @param[in] wfpa5gisenseen - The value to use for the wf_pa5g_isense_en field.
 * @param[in] wfpa5gisenseselic5u - The value to use for the wf_pa5g_isense_sel_ic5u field.
 */
__INLINE void wlan_rf_reg_3c_pack(uint8_t wfpa24grfophd2cbittx, uint8_t wfpa24grfophd2cbitrx, uint8_t wfpaloften, uint8_t wfpaloftgbit, uint8_t wfpaloftsellowpass, uint8_t wfpapkdeten, uint8_t wfpapkdetvthbit, uint8_t wfpadpden, uint8_t wfpadpdcbit, uint8_t wfpa5gisenseen, uint8_t wfpa5gisenseselic5u)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR,  ((uint32_t)wfpa24grfophd2cbittx << 20) | ((uint32_t)wfpa24grfophd2cbitrx << 16) | ((uint32_t)wfpaloften << 15) | ((uint32_t)wfpaloftgbit << 12) | ((uint32_t)wfpaloftsellowpass << 11) | ((uint32_t)wfpapkdeten << 10) | ((uint32_t)wfpapkdetvthbit << 7) | ((uint32_t)wfpadpden << 5) | ((uint32_t)wfpadpdcbit << 2) | ((uint32_t)wfpa5gisenseen << 1) | ((uint32_t)wfpa5gisenseselic5u << 0));
}

/**
 * @brief Unpacks REG_3C's fields from current value of the REG_3C register.
 *
 * Reads the REG_3C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpa24grfophd2cbittx - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24grfophd2cbitrx - Will be populated with the current value of this field from the register.
 * @param[out] wfpaloften - Will be populated with the current value of this field from the register.
 * @param[out] wfpaloftgbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpaloftsellowpass - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdeten - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetvthbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdout - Will be populated with the current value of this field from the register.
 * @param[out] wfpadpden - Will be populated with the current value of this field from the register.
 * @param[out] wfpadpdcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gisenseen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa5gisenseselic5u - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_3c_unpack(uint8_t* wfpa24grfophd2cbittx, uint8_t* wfpa24grfophd2cbitrx, uint8_t* wfpaloften, uint8_t* wfpaloftgbit, uint8_t* wfpaloftsellowpass, uint8_t* wfpapkdeten, uint8_t* wfpapkdetvthbit, uint8_t* wfpapkdout, uint8_t* wfpadpden, uint8_t* wfpadpdcbit, uint8_t* wfpa5gisenseen, uint8_t* wfpa5gisenseselic5u)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);

    *wfpa24grfophd2cbittx = (localVal & ((uint32_t)0x00F00000)) >> 20;
    *wfpa24grfophd2cbitrx = (localVal & ((uint32_t)0x000F0000)) >> 16;
    *wfpaloften = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wfpaloftgbit = (localVal & ((uint32_t)0x00007000)) >> 12;
    *wfpaloftsellowpass = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wfpapkdeten = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfpapkdetvthbit = (localVal & ((uint32_t)0x00000380)) >> 7;
    *wfpapkdout = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wfpadpden = (localVal & ((uint32_t)0x00000020)) >> 5;
    *wfpadpdcbit = (localVal & ((uint32_t)0x0000001C)) >> 2;
    *wfpa5gisenseen = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfpa5gisenseselic5u = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pa24g_rfop_hd2_cbit_tx field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa24g_rfop_hd2_cbit_tx field's value will be returned.
 *
 * @return The current value of the wf_pa24g_rfop_hd2_cbit_tx field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_rfop_hd_2_cbit_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00F00000)) >> 20);
}

/**
 * @brief Sets the wf_pa24g_rfop_hd2_cbit_tx field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24grfophd2cbittx - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_rfop_hd_2_cbit_tx_setf(uint8_t wfpa24grfophd2cbittx)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x00F00000)) | (((uint32_t)wfpa24grfophd2cbittx << 20) & ((uint32_t)0x00F00000)));
}

/**
 * @brief Returns the current value of the wf_pa24g_rfop_hd2_cbit_rx field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa24g_rfop_hd2_cbit_rx field's value will be returned.
 *
 * @return The current value of the wf_pa24g_rfop_hd2_cbit_rx field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_rfop_hd_2_cbit_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x000F0000)) >> 16);
}

/**
 * @brief Sets the wf_pa24g_rfop_hd2_cbit_rx field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24grfophd2cbitrx - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_rfop_hd_2_cbit_rx_setf(uint8_t wfpa24grfophd2cbitrx)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x000F0000)) | (((uint32_t)wfpa24grfophd2cbitrx << 16) & ((uint32_t)0x000F0000)));
}

/**
 * @brief Returns the current value of the wf_pa_loft_en field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa_loft_en field's value will be returned.
 *
 * @return The current value of the wf_pa_loft_en field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_loft_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the wf_pa_loft_en field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpaloften - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_loft_en_setf(uint8_t wfpaloften)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)wfpaloften << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the wf_pa_loft_gbit field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa_loft_gbit field's value will be returned.
 *
 * @return The current value of the wf_pa_loft_gbit field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_loft_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

/**
 * @brief Sets the wf_pa_loft_gbit field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpaloftgbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_loft_gbit_setf(uint8_t wfpaloftgbit)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x00007000)) | (((uint32_t)wfpaloftgbit << 12) & ((uint32_t)0x00007000)));
}

/**
 * @brief Returns the current value of the wf_pa_loft_sel_lowpass field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa_loft_sel_lowpass field's value will be returned.
 *
 * @return The current value of the wf_pa_loft_sel_lowpass field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_loft_sel_lowpass_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_pa_loft_sel_lowpass field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpaloftsellowpass - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_loft_sel_lowpass_setf(uint8_t wfpaloftsellowpass)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wfpaloftsellowpass << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_en field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa_pkdet_en field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_en field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_pa_pkdet_en field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkdeten - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkdet_en_setf(uint8_t wfpapkdeten)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfpapkdeten << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_vth_bit field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa_pkdet_vth_bit field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_vth_bit field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_vth_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00000380)) >> 7);
}

/**
 * @brief Sets the wf_pa_pkdet_vth_bit field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkdetvthbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkdet_vth_bit_setf(uint8_t wfpapkdetvthbit)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x00000380)) | (((uint32_t)wfpapkdetvthbit << 7) & ((uint32_t)0x00000380)));
}

/**
 * @brief Returns the current value of the wf_pa_pkd_out field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa_pkd_out field's value will be returned.
 *
 * @return The current value of the wf_pa_pkd_out field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkd_out_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Returns the current value of the wf_pa_dpd_en field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa_dpd_en field's value will be returned.
 *
 * @return The current value of the wf_pa_dpd_en field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_dpd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the wf_pa_dpd_en field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpadpden - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_dpd_en_setf(uint8_t wfpadpden)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)wfpadpden << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the wf_pa_dpd_cbit field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa_dpd_cbit field's value will be returned.
 *
 * @return The current value of the wf_pa_dpd_cbit field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_dpd_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x0000001C)) >> 2);
}

/**
 * @brief Sets the wf_pa_dpd_cbit field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpadpdcbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_dpd_cbit_setf(uint8_t wfpadpdcbit)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x0000001C)) | (((uint32_t)wfpadpdcbit << 2) & ((uint32_t)0x0000001C)));
}

/**
 * @brief Returns the current value of the wf_pa5g_isense_en field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa5g_isense_en field's value will be returned.
 *
 * @return The current value of the wf_pa5g_isense_en field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_isense_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_pa5g_isense_en field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gisenseen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_isense_en_setf(uint8_t wfpa5gisenseen)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfpa5gisenseen << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_pa5g_isense_sel_ic5u field in the REG_3C register.
 *
 * The REG_3C register will be read and the wf_pa5g_isense_sel_ic5u field's value will be returned.
 *
 * @return The current value of the wf_pa5g_isense_sel_ic5u field in the REG_3C register.
 */
__INLINE uint8_t wlan_rf_wf_pa_5g_isense_sel_ic_5u_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_3C_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_pa5g_isense_sel_ic5u field of the REG_3C register.
 *
 * The REG_3C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa5gisenseselic5u - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_5g_isense_sel_ic_5u_setf(uint8_t wfpa5gisenseselic5u)
{
    REG_PL_WR(WLAN_RF_REG_3C_ADDR, (REG_PL_RD(WLAN_RF_REG_3C_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfpa5gisenseselic5u << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_40 register definitions
 * <table>
 * <caption id="REG_40_BF">REG_40 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29 <td>wf_pa24g_isense_en <td>R <td>R/W <td>0
 * <tr><td>28 <td>wf_pa24g_isense_sel_ic5u <td>R <td>R/W <td>0
 * <tr><td>27:26 <td>  wf_trx5g_rx_cbit <td>W <td>R <td>0x0
 * <tr><td>25:24 <td> wf_trx24g_rx_cbit <td>W <td>R <td>0x0
 * <tr><td>23 <td>wf_dtmx_din0_sel_half_lsb <td>R <td>R/W <td>1
 * <tr><td>22:20 <td>wf_dtmx_btbias_vl_bit <td>R <td>R/W <td>0x4
 * <tr><td>19:17 <td> wf_dtmx_dvdd_vbit <td>R <td>R/W <td>0x2
 * <tr><td>16 <td>        wf_dtmx_ms <td>R <td>R/W <td>0
 * <tr><td>15 <td> wf_dtmx_lo5g_mode <td>R <td>R/W <td>1
 * <tr><td>14:13 <td>wf_dtmx_path_mode_bit <td>R <td>R/W <td>0x3
 * <tr><td>12:10 <td>   wf_dtmx_vh_vbit <td>R <td>R/W <td>0x2
 * <tr><td>09:07 <td>  wf_dtmx_vlo_vbit <td>R <td>R/W <td>0x2
 * <tr><td>06:03 <td>wf_dtmx_dac_cscd_vbit <td>R <td>R/W <td>0x8
 * <tr><td>02:00 <td> wf_dtmx_dac_gbit1 <td>W <td>R <td>0x4
 * </table>
 *
 * @{
 */

/// Address of the REG_40 register
#define WLAN_RF_REG_40_ADDR   0x40344040
/// Offset of the REG_40 register from the base address
#define WLAN_RF_REG_40_OFFSET 0x00000040
/// Index of the REG_40 register
#define WLAN_RF_REG_40_INDEX  0x00000010
/// Reset value of the REG_40 register
#define WLAN_RF_REG_40_RESET  0x00C4E944

/**
 * @brief Returns the current value of the REG_40 register.
 * The REG_40 register will be read and its value returned.
 * @return The current value of the REG_40 register.
 */
__INLINE uint32_t wlan_rf_reg_40_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_40_ADDR);
}

/**
 * @brief Sets the REG_40 register to a value.
 * The REG_40 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_40_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, value);
}

// field definitions
/// WF_PA_24G_ISENSE_EN field bit
#define WLAN_RF_WF_PA_24G_ISENSE_EN_BIT           ((uint32_t)0x20000000)
/// WF_PA_24G_ISENSE_EN field position
#define WLAN_RF_WF_PA_24G_ISENSE_EN_POS           29
/// WF_PA_24G_ISENSE_SEL_IC_5U field bit
#define WLAN_RF_WF_PA_24G_ISENSE_SEL_IC_5U_BIT    ((uint32_t)0x10000000)
/// WF_PA_24G_ISENSE_SEL_IC_5U field position
#define WLAN_RF_WF_PA_24G_ISENSE_SEL_IC_5U_POS    28
/// WF_TRX_5G_RX_CBIT field mask
#define WLAN_RF_WF_TRX_5G_RX_CBIT_MASK            ((uint32_t)0x0C000000)
/// WF_TRX_5G_RX_CBIT field LSB position
#define WLAN_RF_WF_TRX_5G_RX_CBIT_LSB             26
/// WF_TRX_5G_RX_CBIT field width
#define WLAN_RF_WF_TRX_5G_RX_CBIT_WIDTH           ((uint32_t)0x00000002)
/// WF_TRX_24G_RX_CBIT field mask
#define WLAN_RF_WF_TRX_24G_RX_CBIT_MASK           ((uint32_t)0x03000000)
/// WF_TRX_24G_RX_CBIT field LSB position
#define WLAN_RF_WF_TRX_24G_RX_CBIT_LSB            24
/// WF_TRX_24G_RX_CBIT field width
#define WLAN_RF_WF_TRX_24G_RX_CBIT_WIDTH          ((uint32_t)0x00000002)
/// WF_DTMX_DIN_0_SEL_HALF_LSB field bit
#define WLAN_RF_WF_DTMX_DIN_0_SEL_HALF_LSB_BIT    ((uint32_t)0x00800000)
/// WF_DTMX_DIN_0_SEL_HALF_LSB field position
#define WLAN_RF_WF_DTMX_DIN_0_SEL_HALF_LSB_POS    23
/// WF_DTMX_BTBIAS_VL_BIT field mask
#define WLAN_RF_WF_DTMX_BTBIAS_VL_BIT_MASK        ((uint32_t)0x00700000)
/// WF_DTMX_BTBIAS_VL_BIT field LSB position
#define WLAN_RF_WF_DTMX_BTBIAS_VL_BIT_LSB         20
/// WF_DTMX_BTBIAS_VL_BIT field width
#define WLAN_RF_WF_DTMX_BTBIAS_VL_BIT_WIDTH       ((uint32_t)0x00000003)
/// WF_DTMX_DVDD_VBIT field mask
#define WLAN_RF_WF_DTMX_DVDD_VBIT_MASK            ((uint32_t)0x000E0000)
/// WF_DTMX_DVDD_VBIT field LSB position
#define WLAN_RF_WF_DTMX_DVDD_VBIT_LSB             17
/// WF_DTMX_DVDD_VBIT field width
#define WLAN_RF_WF_DTMX_DVDD_VBIT_WIDTH           ((uint32_t)0x00000003)
/// WF_DTMX_MS field bit
#define WLAN_RF_WF_DTMX_MS_BIT                    ((uint32_t)0x00010000)
/// WF_DTMX_MS field position
#define WLAN_RF_WF_DTMX_MS_POS                    16
/// WF_DTMX_LO_5G_MODE field bit
#define WLAN_RF_WF_DTMX_LO_5G_MODE_BIT            ((uint32_t)0x00008000)
/// WF_DTMX_LO_5G_MODE field position
#define WLAN_RF_WF_DTMX_LO_5G_MODE_POS            15
/// WF_DTMX_PATH_MODE_BIT field mask
#define WLAN_RF_WF_DTMX_PATH_MODE_BIT_MASK        ((uint32_t)0x00006000)
/// WF_DTMX_PATH_MODE_BIT field LSB position
#define WLAN_RF_WF_DTMX_PATH_MODE_BIT_LSB         13
/// WF_DTMX_PATH_MODE_BIT field width
#define WLAN_RF_WF_DTMX_PATH_MODE_BIT_WIDTH       ((uint32_t)0x00000002)
/// WF_DTMX_VH_VBIT field mask
#define WLAN_RF_WF_DTMX_VH_VBIT_MASK              ((uint32_t)0x00001C00)
/// WF_DTMX_VH_VBIT field LSB position
#define WLAN_RF_WF_DTMX_VH_VBIT_LSB               10
/// WF_DTMX_VH_VBIT field width
#define WLAN_RF_WF_DTMX_VH_VBIT_WIDTH             ((uint32_t)0x00000003)
/// WF_DTMX_VLO_VBIT field mask
#define WLAN_RF_WF_DTMX_VLO_VBIT_MASK             ((uint32_t)0x00000380)
/// WF_DTMX_VLO_VBIT field LSB position
#define WLAN_RF_WF_DTMX_VLO_VBIT_LSB              7
/// WF_DTMX_VLO_VBIT field width
#define WLAN_RF_WF_DTMX_VLO_VBIT_WIDTH            ((uint32_t)0x00000003)
/// WF_DTMX_DAC_CSCD_VBIT field mask
#define WLAN_RF_WF_DTMX_DAC_CSCD_VBIT_MASK        ((uint32_t)0x00000078)
/// WF_DTMX_DAC_CSCD_VBIT field LSB position
#define WLAN_RF_WF_DTMX_DAC_CSCD_VBIT_LSB         3
/// WF_DTMX_DAC_CSCD_VBIT field width
#define WLAN_RF_WF_DTMX_DAC_CSCD_VBIT_WIDTH       ((uint32_t)0x00000004)
/// WF_DTMX_DAC_GBIT_1 field mask
#define WLAN_RF_WF_DTMX_DAC_GBIT_1_MASK           ((uint32_t)0x00000007)
/// WF_DTMX_DAC_GBIT_1 field LSB position
#define WLAN_RF_WF_DTMX_DAC_GBIT_1_LSB            0
/// WF_DTMX_DAC_GBIT_1 field width
#define WLAN_RF_WF_DTMX_DAC_GBIT_1_WIDTH          ((uint32_t)0x00000003)

/// WF_PA_24G_ISENSE_EN field reset value
#define WLAN_RF_WF_PA_24G_ISENSE_EN_RST           0x0
/// WF_PA_24G_ISENSE_SEL_IC_5U field reset value
#define WLAN_RF_WF_PA_24G_ISENSE_SEL_IC_5U_RST    0x0
/// WF_TRX_5G_RX_CBIT field reset value
#define WLAN_RF_WF_TRX_5G_RX_CBIT_RST             0x0
/// WF_TRX_24G_RX_CBIT field reset value
#define WLAN_RF_WF_TRX_24G_RX_CBIT_RST            0x0
/// WF_DTMX_DIN_0_SEL_HALF_LSB field reset value
#define WLAN_RF_WF_DTMX_DIN_0_SEL_HALF_LSB_RST    0x1
/// WF_DTMX_BTBIAS_VL_BIT field reset value
#define WLAN_RF_WF_DTMX_BTBIAS_VL_BIT_RST         0x4
/// WF_DTMX_DVDD_VBIT field reset value
#define WLAN_RF_WF_DTMX_DVDD_VBIT_RST             0x2
/// WF_DTMX_MS field reset value
#define WLAN_RF_WF_DTMX_MS_RST                    0x0
/// WF_DTMX_LO_5G_MODE field reset value
#define WLAN_RF_WF_DTMX_LO_5G_MODE_RST            0x1
/// WF_DTMX_PATH_MODE_BIT field reset value
#define WLAN_RF_WF_DTMX_PATH_MODE_BIT_RST         0x3
/// WF_DTMX_VH_VBIT field reset value
#define WLAN_RF_WF_DTMX_VH_VBIT_RST               0x2
/// WF_DTMX_VLO_VBIT field reset value
#define WLAN_RF_WF_DTMX_VLO_VBIT_RST              0x2
/// WF_DTMX_DAC_CSCD_VBIT field reset value
#define WLAN_RF_WF_DTMX_DAC_CSCD_VBIT_RST         0x8
/// WF_DTMX_DAC_GBIT_1 field reset value
#define WLAN_RF_WF_DTMX_DAC_GBIT_1_RST            0x4

/**
 * @brief Constructs a value for the REG_40 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpa24gisenseen - The value to use for the wf_pa24g_isense_en field.
 * @param[in] wfpa24gisenseselic5u - The value to use for the wf_pa24g_isense_sel_ic5u field.
 * @param[in] wfdtmxdin0selhalflsb - The value to use for the wf_dtmx_din0_sel_half_lsb field.
 * @param[in] wfdtmxbtbiasvlbit - The value to use for the wf_dtmx_btbias_vl_bit field.
 * @param[in] wfdtmxdvddvbit - The value to use for the wf_dtmx_dvdd_vbit field.
 * @param[in] wfdtmxms - The value to use for the wf_dtmx_ms field.
 * @param[in] wfdtmxlo5gmode - The value to use for the wf_dtmx_lo5g_mode field.
 * @param[in] wfdtmxpathmodebit - The value to use for the wf_dtmx_path_mode_bit field.
 * @param[in] wfdtmxvhvbit - The value to use for the wf_dtmx_vh_vbit field.
 * @param[in] wfdtmxvlovbit - The value to use for the wf_dtmx_vlo_vbit field.
 * @param[in] wfdtmxdaccscdvbit - The value to use for the wf_dtmx_dac_cscd_vbit field.
 */
__INLINE void wlan_rf_reg_40_pack(uint8_t wfpa24gisenseen, uint8_t wfpa24gisenseselic5u, uint8_t wfdtmxdin0selhalflsb, uint8_t wfdtmxbtbiasvlbit, uint8_t wfdtmxdvddvbit, uint8_t wfdtmxms, uint8_t wfdtmxlo5gmode, uint8_t wfdtmxpathmodebit, uint8_t wfdtmxvhvbit, uint8_t wfdtmxvlovbit, uint8_t wfdtmxdaccscdvbit)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR,  ((uint32_t)wfpa24gisenseen << 29) | ((uint32_t)wfpa24gisenseselic5u << 28) | ((uint32_t)wfdtmxdin0selhalflsb << 23) | ((uint32_t)wfdtmxbtbiasvlbit << 20) | ((uint32_t)wfdtmxdvddvbit << 17) | ((uint32_t)wfdtmxms << 16) | ((uint32_t)wfdtmxlo5gmode << 15) | ((uint32_t)wfdtmxpathmodebit << 13) | ((uint32_t)wfdtmxvhvbit << 10) | ((uint32_t)wfdtmxvlovbit << 7) | ((uint32_t)wfdtmxdaccscdvbit << 3));
}

/**
 * @brief Unpacks REG_40's fields from current value of the REG_40 register.
 *
 * Reads the REG_40 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpa24gisenseen - Will be populated with the current value of this field from the register.
 * @param[out] wfpa24gisenseselic5u - Will be populated with the current value of this field from the register.
 * @param[out] wftrx5grxcbit - Will be populated with the current value of this field from the register.
 * @param[out] wftrx24grxcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdin0selhalflsb - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxbtbiasvlbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdvddvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxms - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlo5gmode - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxpathmodebit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxvhvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxvlovbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdaccscdvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdacgbit1 - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_40_unpack(uint8_t* wfpa24gisenseen, uint8_t* wfpa24gisenseselic5u, uint8_t* wftrx5grxcbit, uint8_t* wftrx24grxcbit, uint8_t* wfdtmxdin0selhalflsb, uint8_t* wfdtmxbtbiasvlbit, uint8_t* wfdtmxdvddvbit, uint8_t* wfdtmxms, uint8_t* wfdtmxlo5gmode, uint8_t* wfdtmxpathmodebit, uint8_t* wfdtmxvhvbit, uint8_t* wfdtmxvlovbit, uint8_t* wfdtmxdaccscdvbit, uint8_t* wfdtmxdacgbit1)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);

    *wfpa24gisenseen = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wfpa24gisenseselic5u = (localVal & ((uint32_t)0x10000000)) >> 28;
    *wftrx5grxcbit = (localVal & ((uint32_t)0x0C000000)) >> 26;
    *wftrx24grxcbit = (localVal & ((uint32_t)0x03000000)) >> 24;
    *wfdtmxdin0selhalflsb = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfdtmxbtbiasvlbit = (localVal & ((uint32_t)0x00700000)) >> 20;
    *wfdtmxdvddvbit = (localVal & ((uint32_t)0x000E0000)) >> 17;
    *wfdtmxms = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wfdtmxlo5gmode = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wfdtmxpathmodebit = (localVal & ((uint32_t)0x00006000)) >> 13;
    *wfdtmxvhvbit = (localVal & ((uint32_t)0x00001C00)) >> 10;
    *wfdtmxvlovbit = (localVal & ((uint32_t)0x00000380)) >> 7;
    *wfdtmxdaccscdvbit = (localVal & ((uint32_t)0x00000078)) >> 3;
    *wfdtmxdacgbit1 = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pa24g_isense_en field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_pa24g_isense_en field's value will be returned.
 *
 * @return The current value of the wf_pa24g_isense_en field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_isense_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the wf_pa24g_isense_en field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24gisenseen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_isense_en_setf(uint8_t wfpa24gisenseen)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wfpa24gisenseen << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the wf_pa24g_isense_sel_ic5u field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_pa24g_isense_sel_ic5u field's value will be returned.
 *
 * @return The current value of the wf_pa24g_isense_sel_ic5u field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_24g_isense_sel_ic_5u_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the wf_pa24g_isense_sel_ic5u field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpa24gisenseselic5u - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_24g_isense_sel_ic_5u_setf(uint8_t wfpa24gisenseselic5u)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)wfpa24gisenseselic5u << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the wf_trx5g_rx_cbit field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_trx5g_rx_cbit field's value will be returned.
 *
 * @return The current value of the wf_trx5g_rx_cbit field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_5g_rx_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x0C000000)) >> 26);
}

/**
 * @brief Returns the current value of the wf_trx24g_rx_cbit field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_trx24g_rx_cbit field's value will be returned.
 *
 * @return The current value of the wf_trx24g_rx_cbit field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_24g_rx_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

/**
 * @brief Returns the current value of the wf_dtmx_din0_sel_half_lsb field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_din0_sel_half_lsb field's value will be returned.
 *
 * @return The current value of the wf_dtmx_din0_sel_half_lsb field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_din_0_sel_half_lsb_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_dtmx_din0_sel_half_lsb field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdin0selhalflsb - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_din_0_sel_half_lsb_setf(uint8_t wfdtmxdin0selhalflsb)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wfdtmxdin0selhalflsb << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_btbias_vl_bit field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_btbias_vl_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_btbias_vl_bit field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_btbias_vl_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

/**
 * @brief Sets the wf_dtmx_btbias_vl_bit field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxbtbiasvlbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_btbias_vl_bit_setf(uint8_t wfdtmxbtbiasvlbit)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x00700000)) | (((uint32_t)wfdtmxbtbiasvlbit << 20) & ((uint32_t)0x00700000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dvdd_vbit field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_dvdd_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dvdd_vbit field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dvdd_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x000E0000)) >> 17);
}

/**
 * @brief Sets the wf_dtmx_dvdd_vbit field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdvddvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dvdd_vbit_setf(uint8_t wfdtmxdvddvbit)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x000E0000)) | (((uint32_t)wfdtmxdvddvbit << 17) & ((uint32_t)0x000E0000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_ms field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_ms field's value will be returned.
 *
 * @return The current value of the wf_dtmx_ms field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_ms_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_dtmx_ms field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxms - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_ms_setf(uint8_t wfdtmxms)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wfdtmxms << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_lo5g_mode field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_lo5g_mode field's value will be returned.
 *
 * @return The current value of the wf_dtmx_lo5g_mode field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_lo_5g_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the wf_dtmx_lo5g_mode field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlo5gmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_lo_5g_mode_setf(uint8_t wfdtmxlo5gmode)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)wfdtmxlo5gmode << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_path_mode_bit field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_path_mode_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_path_mode_bit field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_path_mode_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x00006000)) >> 13);
}

/**
 * @brief Sets the wf_dtmx_path_mode_bit field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxpathmodebit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_path_mode_bit_setf(uint8_t wfdtmxpathmodebit)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x00006000)) | (((uint32_t)wfdtmxpathmodebit << 13) & ((uint32_t)0x00006000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_vh_vbit field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_vh_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_vh_vbit field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_vh_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x00001C00)) >> 10);
}

/**
 * @brief Sets the wf_dtmx_vh_vbit field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxvhvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_vh_vbit_setf(uint8_t wfdtmxvhvbit)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x00001C00)) | (((uint32_t)wfdtmxvhvbit << 10) & ((uint32_t)0x00001C00)));
}

/**
 * @brief Returns the current value of the wf_dtmx_vlo_vbit field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_vlo_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_vlo_vbit field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_vlo_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x00000380)) >> 7);
}

/**
 * @brief Sets the wf_dtmx_vlo_vbit field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxvlovbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_vlo_vbit_setf(uint8_t wfdtmxvlovbit)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x00000380)) | (((uint32_t)wfdtmxvlovbit << 7) & ((uint32_t)0x00000380)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dac_cscd_vbit field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_dac_cscd_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dac_cscd_vbit field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dac_cscd_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x00000078)) >> 3);
}

/**
 * @brief Sets the wf_dtmx_dac_cscd_vbit field of the REG_40 register.
 *
 * The REG_40 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdaccscdvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dac_cscd_vbit_setf(uint8_t wfdtmxdaccscdvbit)
{
    REG_PL_WR(WLAN_RF_REG_40_ADDR, (REG_PL_RD(WLAN_RF_REG_40_ADDR) & ~((uint32_t)0x00000078)) | (((uint32_t)wfdtmxdaccscdvbit << 3) & ((uint32_t)0x00000078)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dac_gbit1 field in the REG_40 register.
 *
 * The REG_40 register will be read and the wf_dtmx_dac_gbit1 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dac_gbit1 field in the REG_40 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dac_gbit_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_40_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/// @}

/**
 * @name REG_44 register definitions
 * <table>
 * <caption id="REG_44_BF">REG_44 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>26:23 <td> wf_dtmx_dac_gbit2 <td>W <td>R <td>0x7
 * <tr><td>22:19 <td> wf_dtmx_dac_gbit3 <td>W <td>R <td>0x7
 * <tr><td>18:15 <td>wf_dtmx_tuning_cbit <td>W <td>R <td>0x8
 * <tr><td>14 <td>wf_dtmx_lb_ext_cap_en <td>W <td>R <td>0
 * <tr><td>13:12 <td>wf_dtmx_vbg_tc_bit <td>R <td>R/W <td>0x2
 * <tr><td>11:10 <td>wf_dtmx_vbg_b_vbit <td>R <td>R/W <td>0x2
 * <tr><td>09 <td>wf_dtmx_logen_reg_en <td>R <td>R/W <td>1
 * <tr><td>08:06 <td>wf_dtmx_logen_reg_vbit <td>R <td>R/W <td>0x4
 * <tr><td>05 <td>wf_dtmx_logen_sf_sel_ldo18 <td>R <td>R/W <td>0
 * <tr><td>04 <td>wf_dtmx_logen_lo_en <td>R <td>R/W <td>1
 * <tr><td>03 <td>wf_dtmx_logen_psw_mode <td>R <td>R/W <td>1
 * <tr><td>02 <td>wf_dtmx_logen_sf_mode <td>R <td>R/W <td>0
 * <tr><td>01 <td>wf_dtmx_logen_vco_div2_en <td>R <td>R/W <td>0
 * <tr><td>00 <td>wf_dtmx_logen_band <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_44 register
#define WLAN_RF_REG_44_ADDR   0x40344044
/// Offset of the REG_44 register from the base address
#define WLAN_RF_REG_44_OFFSET 0x00000044
/// Index of the REG_44 register
#define WLAN_RF_REG_44_INDEX  0x00000011
/// Reset value of the REG_44 register
#define WLAN_RF_REG_44_RESET  0x03BC2B19

/**
 * @brief Returns the current value of the REG_44 register.
 * The REG_44 register will be read and its value returned.
 * @return The current value of the REG_44 register.
 */
__INLINE uint32_t wlan_rf_reg_44_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_44_ADDR);
}

/**
 * @brief Sets the REG_44 register to a value.
 * The REG_44 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_44_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, value);
}

// field definitions
/// WF_DTMX_DAC_GBIT_2 field mask
#define WLAN_RF_WF_DTMX_DAC_GBIT_2_MASK            ((uint32_t)0x07800000)
/// WF_DTMX_DAC_GBIT_2 field LSB position
#define WLAN_RF_WF_DTMX_DAC_GBIT_2_LSB             23
/// WF_DTMX_DAC_GBIT_2 field width
#define WLAN_RF_WF_DTMX_DAC_GBIT_2_WIDTH           ((uint32_t)0x00000004)
/// WF_DTMX_DAC_GBIT_3 field mask
#define WLAN_RF_WF_DTMX_DAC_GBIT_3_MASK            ((uint32_t)0x00780000)
/// WF_DTMX_DAC_GBIT_3 field LSB position
#define WLAN_RF_WF_DTMX_DAC_GBIT_3_LSB             19
/// WF_DTMX_DAC_GBIT_3 field width
#define WLAN_RF_WF_DTMX_DAC_GBIT_3_WIDTH           ((uint32_t)0x00000004)
/// WF_DTMX_TUNING_CBIT field mask
#define WLAN_RF_WF_DTMX_TUNING_CBIT_MASK           ((uint32_t)0x00078000)
/// WF_DTMX_TUNING_CBIT field LSB position
#define WLAN_RF_WF_DTMX_TUNING_CBIT_LSB            15
/// WF_DTMX_TUNING_CBIT field width
#define WLAN_RF_WF_DTMX_TUNING_CBIT_WIDTH          ((uint32_t)0x00000004)
/// WF_DTMX_LB_EXT_CAP_EN field bit
#define WLAN_RF_WF_DTMX_LB_EXT_CAP_EN_BIT          ((uint32_t)0x00004000)
/// WF_DTMX_LB_EXT_CAP_EN field position
#define WLAN_RF_WF_DTMX_LB_EXT_CAP_EN_POS          14
/// WF_DTMX_VBG_TC_BIT field mask
#define WLAN_RF_WF_DTMX_VBG_TC_BIT_MASK            ((uint32_t)0x00003000)
/// WF_DTMX_VBG_TC_BIT field LSB position
#define WLAN_RF_WF_DTMX_VBG_TC_BIT_LSB             12
/// WF_DTMX_VBG_TC_BIT field width
#define WLAN_RF_WF_DTMX_VBG_TC_BIT_WIDTH           ((uint32_t)0x00000002)
/// WF_DTMX_VBG_B_VBIT field mask
#define WLAN_RF_WF_DTMX_VBG_B_VBIT_MASK            ((uint32_t)0x00000C00)
/// WF_DTMX_VBG_B_VBIT field LSB position
#define WLAN_RF_WF_DTMX_VBG_B_VBIT_LSB             10
/// WF_DTMX_VBG_B_VBIT field width
#define WLAN_RF_WF_DTMX_VBG_B_VBIT_WIDTH           ((uint32_t)0x00000002)
/// WF_DTMX_LOGEN_REG_EN field bit
#define WLAN_RF_WF_DTMX_LOGEN_REG_EN_BIT           ((uint32_t)0x00000200)
/// WF_DTMX_LOGEN_REG_EN field position
#define WLAN_RF_WF_DTMX_LOGEN_REG_EN_POS           9
/// WF_DTMX_LOGEN_REG_VBIT field mask
#define WLAN_RF_WF_DTMX_LOGEN_REG_VBIT_MASK        ((uint32_t)0x000001C0)
/// WF_DTMX_LOGEN_REG_VBIT field LSB position
#define WLAN_RF_WF_DTMX_LOGEN_REG_VBIT_LSB         6
/// WF_DTMX_LOGEN_REG_VBIT field width
#define WLAN_RF_WF_DTMX_LOGEN_REG_VBIT_WIDTH       ((uint32_t)0x00000003)
/// WF_DTMX_LOGEN_SF_SEL_LDO_18 field bit
#define WLAN_RF_WF_DTMX_LOGEN_SF_SEL_LDO_18_BIT    ((uint32_t)0x00000020)
/// WF_DTMX_LOGEN_SF_SEL_LDO_18 field position
#define WLAN_RF_WF_DTMX_LOGEN_SF_SEL_LDO_18_POS    5
/// WF_DTMX_LOGEN_LO_EN field bit
#define WLAN_RF_WF_DTMX_LOGEN_LO_EN_BIT            ((uint32_t)0x00000010)
/// WF_DTMX_LOGEN_LO_EN field position
#define WLAN_RF_WF_DTMX_LOGEN_LO_EN_POS            4
/// WF_DTMX_LOGEN_PSW_MODE field bit
#define WLAN_RF_WF_DTMX_LOGEN_PSW_MODE_BIT         ((uint32_t)0x00000008)
/// WF_DTMX_LOGEN_PSW_MODE field position
#define WLAN_RF_WF_DTMX_LOGEN_PSW_MODE_POS         3
/// WF_DTMX_LOGEN_SF_MODE field bit
#define WLAN_RF_WF_DTMX_LOGEN_SF_MODE_BIT          ((uint32_t)0x00000004)
/// WF_DTMX_LOGEN_SF_MODE field position
#define WLAN_RF_WF_DTMX_LOGEN_SF_MODE_POS          2
/// WF_DTMX_LOGEN_VCO_DIV_2_EN field bit
#define WLAN_RF_WF_DTMX_LOGEN_VCO_DIV_2_EN_BIT     ((uint32_t)0x00000002)
/// WF_DTMX_LOGEN_VCO_DIV_2_EN field position
#define WLAN_RF_WF_DTMX_LOGEN_VCO_DIV_2_EN_POS     1
/// WF_DTMX_LOGEN_BAND field bit
#define WLAN_RF_WF_DTMX_LOGEN_BAND_BIT             ((uint32_t)0x00000001)
/// WF_DTMX_LOGEN_BAND field position
#define WLAN_RF_WF_DTMX_LOGEN_BAND_POS             0

/// WF_DTMX_DAC_GBIT_2 field reset value
#define WLAN_RF_WF_DTMX_DAC_GBIT_2_RST             0x7
/// WF_DTMX_DAC_GBIT_3 field reset value
#define WLAN_RF_WF_DTMX_DAC_GBIT_3_RST             0x7
/// WF_DTMX_TUNING_CBIT field reset value
#define WLAN_RF_WF_DTMX_TUNING_CBIT_RST            0x8
/// WF_DTMX_LB_EXT_CAP_EN field reset value
#define WLAN_RF_WF_DTMX_LB_EXT_CAP_EN_RST          0x0
/// WF_DTMX_VBG_TC_BIT field reset value
#define WLAN_RF_WF_DTMX_VBG_TC_BIT_RST             0x2
/// WF_DTMX_VBG_B_VBIT field reset value
#define WLAN_RF_WF_DTMX_VBG_B_VBIT_RST             0x2
/// WF_DTMX_LOGEN_REG_EN field reset value
#define WLAN_RF_WF_DTMX_LOGEN_REG_EN_RST           0x1
/// WF_DTMX_LOGEN_REG_VBIT field reset value
#define WLAN_RF_WF_DTMX_LOGEN_REG_VBIT_RST         0x4
/// WF_DTMX_LOGEN_SF_SEL_LDO_18 field reset value
#define WLAN_RF_WF_DTMX_LOGEN_SF_SEL_LDO_18_RST    0x0
/// WF_DTMX_LOGEN_LO_EN field reset value
#define WLAN_RF_WF_DTMX_LOGEN_LO_EN_RST            0x1
/// WF_DTMX_LOGEN_PSW_MODE field reset value
#define WLAN_RF_WF_DTMX_LOGEN_PSW_MODE_RST         0x1
/// WF_DTMX_LOGEN_SF_MODE field reset value
#define WLAN_RF_WF_DTMX_LOGEN_SF_MODE_RST          0x0
/// WF_DTMX_LOGEN_VCO_DIV_2_EN field reset value
#define WLAN_RF_WF_DTMX_LOGEN_VCO_DIV_2_EN_RST     0x0
/// WF_DTMX_LOGEN_BAND field reset value
#define WLAN_RF_WF_DTMX_LOGEN_BAND_RST             0x1

/**
 * @brief Constructs a value for the REG_44 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfdtmxvbgtcbit - The value to use for the wf_dtmx_vbg_tc_bit field.
 * @param[in] wfdtmxvbgbvbit - The value to use for the wf_dtmx_vbg_b_vbit field.
 * @param[in] wfdtmxlogenregen - The value to use for the wf_dtmx_logen_reg_en field.
 * @param[in] wfdtmxlogenregvbit - The value to use for the wf_dtmx_logen_reg_vbit field.
 * @param[in] wfdtmxlogensfselldo18 - The value to use for the wf_dtmx_logen_sf_sel_ldo18 field.
 * @param[in] wfdtmxlogenloen - The value to use for the wf_dtmx_logen_lo_en field.
 * @param[in] wfdtmxlogenpswmode - The value to use for the wf_dtmx_logen_psw_mode field.
 * @param[in] wfdtmxlogensfmode - The value to use for the wf_dtmx_logen_sf_mode field.
 * @param[in] wfdtmxlogenvcodiv2en - The value to use for the wf_dtmx_logen_vco_div2_en field.
 * @param[in] wfdtmxlogenband - The value to use for the wf_dtmx_logen_band field.
 */
__INLINE void wlan_rf_reg_44_pack(uint8_t wfdtmxvbgtcbit, uint8_t wfdtmxvbgbvbit, uint8_t wfdtmxlogenregen, uint8_t wfdtmxlogenregvbit, uint8_t wfdtmxlogensfselldo18, uint8_t wfdtmxlogenloen, uint8_t wfdtmxlogenpswmode, uint8_t wfdtmxlogensfmode, uint8_t wfdtmxlogenvcodiv2en, uint8_t wfdtmxlogenband)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR,  ((uint32_t)wfdtmxvbgtcbit << 12) | ((uint32_t)wfdtmxvbgbvbit << 10) | ((uint32_t)wfdtmxlogenregen << 9) | ((uint32_t)wfdtmxlogenregvbit << 6) | ((uint32_t)wfdtmxlogensfselldo18 << 5) | ((uint32_t)wfdtmxlogenloen << 4) | ((uint32_t)wfdtmxlogenpswmode << 3) | ((uint32_t)wfdtmxlogensfmode << 2) | ((uint32_t)wfdtmxlogenvcodiv2en << 1) | ((uint32_t)wfdtmxlogenband << 0));
}

/**
 * @brief Unpacks REG_44's fields from current value of the REG_44 register.
 *
 * Reads the REG_44 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfdtmxdacgbit2 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdacgbit3 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxtuningcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlbextcapen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxvbgtcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxvbgbvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogenregen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogenregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogensfselldo18 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogenloen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogenpswmode - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogensfmode - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogenvcodiv2en - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogenband - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_44_unpack(uint8_t* wfdtmxdacgbit2, uint8_t* wfdtmxdacgbit3, uint8_t* wfdtmxtuningcbit, uint8_t* wfdtmxlbextcapen, uint8_t* wfdtmxvbgtcbit, uint8_t* wfdtmxvbgbvbit, uint8_t* wfdtmxlogenregen, uint8_t* wfdtmxlogenregvbit, uint8_t* wfdtmxlogensfselldo18, uint8_t* wfdtmxlogenloen, uint8_t* wfdtmxlogenpswmode, uint8_t* wfdtmxlogensfmode, uint8_t* wfdtmxlogenvcodiv2en, uint8_t* wfdtmxlogenband)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);

    *wfdtmxdacgbit2 = (localVal & ((uint32_t)0x07800000)) >> 23;
    *wfdtmxdacgbit3 = (localVal & ((uint32_t)0x00780000)) >> 19;
    *wfdtmxtuningcbit = (localVal & ((uint32_t)0x00078000)) >> 15;
    *wfdtmxlbextcapen = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wfdtmxvbgtcbit = (localVal & ((uint32_t)0x00003000)) >> 12;
    *wfdtmxvbgbvbit = (localVal & ((uint32_t)0x00000C00)) >> 10;
    *wfdtmxlogenregen = (localVal & ((uint32_t)0x00000200)) >> 9;
    *wfdtmxlogenregvbit = (localVal & ((uint32_t)0x000001C0)) >> 6;
    *wfdtmxlogensfselldo18 = (localVal & ((uint32_t)0x00000020)) >> 5;
    *wfdtmxlogenloen = (localVal & ((uint32_t)0x00000010)) >> 4;
    *wfdtmxlogenpswmode = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wfdtmxlogensfmode = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wfdtmxlogenvcodiv2en = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfdtmxlogenband = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_dtmx_dac_gbit2 field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_dac_gbit2 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dac_gbit2 field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dac_gbit_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x07800000)) >> 23);
}

/**
 * @brief Returns the current value of the wf_dtmx_dac_gbit3 field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_dac_gbit3 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dac_gbit3 field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dac_gbit_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00780000)) >> 19);
}

/**
 * @brief Returns the current value of the wf_dtmx_tuning_cbit field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_tuning_cbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_tuning_cbit field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_tuning_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00078000)) >> 15);
}

/**
 * @brief Returns the current value of the wf_dtmx_lb_ext_cap_en field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_lb_ext_cap_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_lb_ext_cap_en field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_lb_ext_cap_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Returns the current value of the wf_dtmx_vbg_tc_bit field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_vbg_tc_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_vbg_tc_bit field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_vbg_tc_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

/**
 * @brief Sets the wf_dtmx_vbg_tc_bit field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxvbgtcbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_vbg_tc_bit_setf(uint8_t wfdtmxvbgtcbit)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x00003000)) | (((uint32_t)wfdtmxvbgtcbit << 12) & ((uint32_t)0x00003000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_vbg_b_vbit field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_vbg_b_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_vbg_b_vbit field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_vbg_b_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00000C00)) >> 10);
}

/**
 * @brief Sets the wf_dtmx_vbg_b_vbit field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxvbgbvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_vbg_b_vbit_setf(uint8_t wfdtmxvbgbvbit)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x00000C00)) | (((uint32_t)wfdtmxvbgbvbit << 10) & ((uint32_t)0x00000C00)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_reg_en field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_logen_reg_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_reg_en field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_reg_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the wf_dtmx_logen_reg_en field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogenregen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_reg_en_setf(uint8_t wfdtmxlogenregen)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)wfdtmxlogenregen << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_reg_vbit field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_logen_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_reg_vbit field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x000001C0)) >> 6);
}

/**
 * @brief Sets the wf_dtmx_logen_reg_vbit field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogenregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_reg_vbit_setf(uint8_t wfdtmxlogenregvbit)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x000001C0)) | (((uint32_t)wfdtmxlogenregvbit << 6) & ((uint32_t)0x000001C0)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_sf_sel_ldo18 field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_logen_sf_sel_ldo18 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_sf_sel_ldo18 field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_sf_sel_ldo_18_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the wf_dtmx_logen_sf_sel_ldo18 field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogensfselldo18 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_sf_sel_ldo_18_setf(uint8_t wfdtmxlogensfselldo18)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)wfdtmxlogensfselldo18 << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_lo_en field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_logen_lo_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_lo_en field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_lo_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the wf_dtmx_logen_lo_en field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogenloen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_lo_en_setf(uint8_t wfdtmxlogenloen)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)wfdtmxlogenloen << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_psw_mode field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_logen_psw_mode field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_psw_mode field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_psw_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wf_dtmx_logen_psw_mode field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogenpswmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_psw_mode_setf(uint8_t wfdtmxlogenpswmode)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wfdtmxlogenpswmode << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_sf_mode field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_logen_sf_mode field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_sf_mode field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_sf_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wf_dtmx_logen_sf_mode field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogensfmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_sf_mode_setf(uint8_t wfdtmxlogensfmode)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wfdtmxlogensfmode << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_vco_div2_en field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_logen_vco_div2_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_vco_div2_en field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_vco_div_2_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_dtmx_logen_vco_div2_en field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogenvcodiv2en - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_vco_div_2_en_setf(uint8_t wfdtmxlogenvcodiv2en)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfdtmxlogenvcodiv2en << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_band field in the REG_44 register.
 *
 * The REG_44 register will be read and the wf_dtmx_logen_band field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_band field in the REG_44 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_band_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_44_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_dtmx_logen_band field of the REG_44 register.
 *
 * The REG_44 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogenband - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_band_setf(uint8_t wfdtmxlogenband)
{
    REG_PL_WR(WLAN_RF_REG_44_ADDR, (REG_PL_RD(WLAN_RF_REG_44_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfdtmxlogenband << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_48 register definitions
 * <table>
 * <caption id="REG_48_BF">REG_48 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:25 <td>wf_dtmx_logen_sf_avdd_sw_bit <td>R <td>R/W <td>0x19
 * <tr><td>24 <td>wf_dtmx_logen_vref_sel_self_bias <td>R <td>R/W <td>1
 * <tr><td>23 <td>wf_dtmx_clk2cdr_en <td>R <td>R/W <td>1
 * <tr><td>22:19 <td>wf_dtmx_logen_dll_reg_vbit <td>R <td>R/W <td>0x8
 * <tr><td>18:15 <td>wf_dtmx_logen_dll_fref_dly_bit <td>R <td>R/W <td>0x8
 * <tr><td>14:11 <td>wf_dtmx_logen_dll_fbc_dly_bit <td>R <td>R/W <td>0x8
 * <tr><td>10:06 <td>wf_dtmx_offset_bit <td>R <td>R/W <td>0x0
 * <tr><td>05 <td>wf_dtmx_clk_edge_sel <td>R <td>R/W <td>1
 * <tr><td>04:02 <td>wf_dtmx_clk_phase_sel_bit <td>R <td>R/W <td>0x1
 * <tr><td>01 <td>wf_dtmx_clk_iq_dly_en <td>R <td>R/W <td>1
 * <tr><td>00 <td>wf_dtmx_clk_path0_45_dly_en <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_48 register
#define WLAN_RF_REG_48_ADDR   0x40344048
/// Offset of the REG_48 register from the base address
#define WLAN_RF_REG_48_OFFSET 0x00000048
/// Index of the REG_48 register
#define WLAN_RF_REG_48_INDEX  0x00000012
/// Reset value of the REG_48 register
#define WLAN_RF_REG_48_RESET  0x33C44027

/**
 * @brief Returns the current value of the REG_48 register.
 * The REG_48 register will be read and its value returned.
 * @return The current value of the REG_48 register.
 */
__INLINE uint32_t wlan_rf_reg_48_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_48_ADDR);
}

/**
 * @brief Sets the REG_48 register to a value.
 * The REG_48 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_48_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, value);
}

// field definitions
/// WF_DTMX_LOGEN_SF_AVDD_SW_BIT field mask
#define WLAN_RF_WF_DTMX_LOGEN_SF_AVDD_SW_BIT_MASK       ((uint32_t)0xFE000000)
/// WF_DTMX_LOGEN_SF_AVDD_SW_BIT field LSB position
#define WLAN_RF_WF_DTMX_LOGEN_SF_AVDD_SW_BIT_LSB        25
/// WF_DTMX_LOGEN_SF_AVDD_SW_BIT field width
#define WLAN_RF_WF_DTMX_LOGEN_SF_AVDD_SW_BIT_WIDTH      ((uint32_t)0x00000007)
/// WF_DTMX_LOGEN_VREF_SEL_SELF_BIAS field bit
#define WLAN_RF_WF_DTMX_LOGEN_VREF_SEL_SELF_BIAS_BIT    ((uint32_t)0x01000000)
/// WF_DTMX_LOGEN_VREF_SEL_SELF_BIAS field position
#define WLAN_RF_WF_DTMX_LOGEN_VREF_SEL_SELF_BIAS_POS    24
/// WF_DTMX_CLK_2CDR_EN field bit
#define WLAN_RF_WF_DTMX_CLK_2CDR_EN_BIT                 ((uint32_t)0x00800000)
/// WF_DTMX_CLK_2CDR_EN field position
#define WLAN_RF_WF_DTMX_CLK_2CDR_EN_POS                 23
/// WF_DTMX_LOGEN_DLL_REG_VBIT field mask
#define WLAN_RF_WF_DTMX_LOGEN_DLL_REG_VBIT_MASK         ((uint32_t)0x00780000)
/// WF_DTMX_LOGEN_DLL_REG_VBIT field LSB position
#define WLAN_RF_WF_DTMX_LOGEN_DLL_REG_VBIT_LSB          19
/// WF_DTMX_LOGEN_DLL_REG_VBIT field width
#define WLAN_RF_WF_DTMX_LOGEN_DLL_REG_VBIT_WIDTH        ((uint32_t)0x00000004)
/// WF_DTMX_LOGEN_DLL_FREF_DLY_BIT field mask
#define WLAN_RF_WF_DTMX_LOGEN_DLL_FREF_DLY_BIT_MASK     ((uint32_t)0x00078000)
/// WF_DTMX_LOGEN_DLL_FREF_DLY_BIT field LSB position
#define WLAN_RF_WF_DTMX_LOGEN_DLL_FREF_DLY_BIT_LSB      15
/// WF_DTMX_LOGEN_DLL_FREF_DLY_BIT field width
#define WLAN_RF_WF_DTMX_LOGEN_DLL_FREF_DLY_BIT_WIDTH    ((uint32_t)0x00000004)
/// WF_DTMX_LOGEN_DLL_FBC_DLY_BIT field mask
#define WLAN_RF_WF_DTMX_LOGEN_DLL_FBC_DLY_BIT_MASK      ((uint32_t)0x00007800)
/// WF_DTMX_LOGEN_DLL_FBC_DLY_BIT field LSB position
#define WLAN_RF_WF_DTMX_LOGEN_DLL_FBC_DLY_BIT_LSB       11
/// WF_DTMX_LOGEN_DLL_FBC_DLY_BIT field width
#define WLAN_RF_WF_DTMX_LOGEN_DLL_FBC_DLY_BIT_WIDTH     ((uint32_t)0x00000004)
/// WF_DTMX_OFFSET_BIT field mask
#define WLAN_RF_WF_DTMX_OFFSET_BIT_MASK                 ((uint32_t)0x000007C0)
/// WF_DTMX_OFFSET_BIT field LSB position
#define WLAN_RF_WF_DTMX_OFFSET_BIT_LSB                  6
/// WF_DTMX_OFFSET_BIT field width
#define WLAN_RF_WF_DTMX_OFFSET_BIT_WIDTH                ((uint32_t)0x00000005)
/// WF_DTMX_CLK_EDGE_SEL field bit
#define WLAN_RF_WF_DTMX_CLK_EDGE_SEL_BIT                ((uint32_t)0x00000020)
/// WF_DTMX_CLK_EDGE_SEL field position
#define WLAN_RF_WF_DTMX_CLK_EDGE_SEL_POS                5
/// WF_DTMX_CLK_PHASE_SEL_BIT field mask
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_BIT_MASK          ((uint32_t)0x0000001C)
/// WF_DTMX_CLK_PHASE_SEL_BIT field LSB position
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_BIT_LSB           2
/// WF_DTMX_CLK_PHASE_SEL_BIT field width
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_BIT_WIDTH         ((uint32_t)0x00000003)
/// WF_DTMX_CLK_IQ_DLY_EN field bit
#define WLAN_RF_WF_DTMX_CLK_IQ_DLY_EN_BIT               ((uint32_t)0x00000002)
/// WF_DTMX_CLK_IQ_DLY_EN field position
#define WLAN_RF_WF_DTMX_CLK_IQ_DLY_EN_POS               1
/// WF_DTMX_CLK_PATH_0__45_DLY_EN field bit
#define WLAN_RF_WF_DTMX_CLK_PATH_0__45_DLY_EN_BIT       ((uint32_t)0x00000001)
/// WF_DTMX_CLK_PATH_0__45_DLY_EN field position
#define WLAN_RF_WF_DTMX_CLK_PATH_0__45_DLY_EN_POS       0

/// WF_DTMX_LOGEN_SF_AVDD_SW_BIT field reset value
#define WLAN_RF_WF_DTMX_LOGEN_SF_AVDD_SW_BIT_RST        0x19
/// WF_DTMX_LOGEN_VREF_SEL_SELF_BIAS field reset value
#define WLAN_RF_WF_DTMX_LOGEN_VREF_SEL_SELF_BIAS_RST    0x1
/// WF_DTMX_CLK_2CDR_EN field reset value
#define WLAN_RF_WF_DTMX_CLK_2CDR_EN_RST                 0x1
/// WF_DTMX_LOGEN_DLL_REG_VBIT field reset value
#define WLAN_RF_WF_DTMX_LOGEN_DLL_REG_VBIT_RST          0x8
/// WF_DTMX_LOGEN_DLL_FREF_DLY_BIT field reset value
#define WLAN_RF_WF_DTMX_LOGEN_DLL_FREF_DLY_BIT_RST      0x8
/// WF_DTMX_LOGEN_DLL_FBC_DLY_BIT field reset value
#define WLAN_RF_WF_DTMX_LOGEN_DLL_FBC_DLY_BIT_RST       0x8
/// WF_DTMX_OFFSET_BIT field reset value
#define WLAN_RF_WF_DTMX_OFFSET_BIT_RST                  0x0
/// WF_DTMX_CLK_EDGE_SEL field reset value
#define WLAN_RF_WF_DTMX_CLK_EDGE_SEL_RST                0x1
/// WF_DTMX_CLK_PHASE_SEL_BIT field reset value
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_BIT_RST           0x1
/// WF_DTMX_CLK_IQ_DLY_EN field reset value
#define WLAN_RF_WF_DTMX_CLK_IQ_DLY_EN_RST               0x1
/// WF_DTMX_CLK_PATH_0__45_DLY_EN field reset value
#define WLAN_RF_WF_DTMX_CLK_PATH_0__45_DLY_EN_RST       0x1

/**
 * @brief Constructs a value for the REG_48 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfdtmxlogensfavddswbit - The value to use for the wf_dtmx_logen_sf_avdd_sw_bit field.
 * @param[in] wfdtmxlogenvrefselselfbias - The value to use for the wf_dtmx_logen_vref_sel_self_bias field.
 * @param[in] wfdtmxclk2cdren - The value to use for the wf_dtmx_clk2cdr_en field.
 * @param[in] wfdtmxlogendllregvbit - The value to use for the wf_dtmx_logen_dll_reg_vbit field.
 * @param[in] wfdtmxlogendllfrefdlybit - The value to use for the wf_dtmx_logen_dll_fref_dly_bit field.
 * @param[in] wfdtmxlogendllfbcdlybit - The value to use for the wf_dtmx_logen_dll_fbc_dly_bit field.
 * @param[in] wfdtmxoffsetbit - The value to use for the wf_dtmx_offset_bit field.
 * @param[in] wfdtmxclkedgesel - The value to use for the wf_dtmx_clk_edge_sel field.
 * @param[in] wfdtmxclkphaseselbit - The value to use for the wf_dtmx_clk_phase_sel_bit field.
 * @param[in] wfdtmxclkiqdlyen - The value to use for the wf_dtmx_clk_iq_dly_en field.
 * @param[in] wfdtmxclkpath045dlyen - The value to use for the wf_dtmx_clk_path0_45_dly_en field.
 */
__INLINE void wlan_rf_reg_48_pack(uint8_t wfdtmxlogensfavddswbit, uint8_t wfdtmxlogenvrefselselfbias, uint8_t wfdtmxclk2cdren, uint8_t wfdtmxlogendllregvbit, uint8_t wfdtmxlogendllfrefdlybit, uint8_t wfdtmxlogendllfbcdlybit, uint8_t wfdtmxoffsetbit, uint8_t wfdtmxclkedgesel, uint8_t wfdtmxclkphaseselbit, uint8_t wfdtmxclkiqdlyen, uint8_t wfdtmxclkpath045dlyen)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR,  ((uint32_t)wfdtmxlogensfavddswbit << 25) | ((uint32_t)wfdtmxlogenvrefselselfbias << 24) | ((uint32_t)wfdtmxclk2cdren << 23) | ((uint32_t)wfdtmxlogendllregvbit << 19) | ((uint32_t)wfdtmxlogendllfrefdlybit << 15) | ((uint32_t)wfdtmxlogendllfbcdlybit << 11) | ((uint32_t)wfdtmxoffsetbit << 6) | ((uint32_t)wfdtmxclkedgesel << 5) | ((uint32_t)wfdtmxclkphaseselbit << 2) | ((uint32_t)wfdtmxclkiqdlyen << 1) | ((uint32_t)wfdtmxclkpath045dlyen << 0));
}

/**
 * @brief Unpacks REG_48's fields from current value of the REG_48 register.
 *
 * Reads the REG_48 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfdtmxlogensfavddswbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogenvrefselselfbias - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclk2cdren - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogendllregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogendllfrefdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlogendllfbcdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxoffsetbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkedgesel - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkphaseselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkiqdlyen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkpath045dlyen - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_48_unpack(uint8_t* wfdtmxlogensfavddswbit, uint8_t* wfdtmxlogenvrefselselfbias, uint8_t* wfdtmxclk2cdren, uint8_t* wfdtmxlogendllregvbit, uint8_t* wfdtmxlogendllfrefdlybit, uint8_t* wfdtmxlogendllfbcdlybit, uint8_t* wfdtmxoffsetbit, uint8_t* wfdtmxclkedgesel, uint8_t* wfdtmxclkphaseselbit, uint8_t* wfdtmxclkiqdlyen, uint8_t* wfdtmxclkpath045dlyen)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);

    *wfdtmxlogensfavddswbit = (localVal & ((uint32_t)0xFE000000)) >> 25;
    *wfdtmxlogenvrefselselfbias = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wfdtmxclk2cdren = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfdtmxlogendllregvbit = (localVal & ((uint32_t)0x00780000)) >> 19;
    *wfdtmxlogendllfrefdlybit = (localVal & ((uint32_t)0x00078000)) >> 15;
    *wfdtmxlogendllfbcdlybit = (localVal & ((uint32_t)0x00007800)) >> 11;
    *wfdtmxoffsetbit = (localVal & ((uint32_t)0x000007C0)) >> 6;
    *wfdtmxclkedgesel = (localVal & ((uint32_t)0x00000020)) >> 5;
    *wfdtmxclkphaseselbit = (localVal & ((uint32_t)0x0000001C)) >> 2;
    *wfdtmxclkiqdlyen = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfdtmxclkpath045dlyen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_sf_avdd_sw_bit field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_logen_sf_avdd_sw_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_sf_avdd_sw_bit field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_sf_avdd_sw_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0xFE000000)) >> 25);
}

/**
 * @brief Sets the wf_dtmx_logen_sf_avdd_sw_bit field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogensfavddswbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_sf_avdd_sw_bit_setf(uint8_t wfdtmxlogensfavddswbit)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0xFE000000)) | (((uint32_t)wfdtmxlogensfavddswbit << 25) & ((uint32_t)0xFE000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_vref_sel_self_bias field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_logen_vref_sel_self_bias field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_vref_sel_self_bias field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_vref_sel_self_bias_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the wf_dtmx_logen_vref_sel_self_bias field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogenvrefselselfbias - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_vref_sel_self_bias_setf(uint8_t wfdtmxlogenvrefselselfbias)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wfdtmxlogenvrefselselfbias << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk2cdr_en field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_clk2cdr_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk2cdr_en field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_2cdr_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_dtmx_clk2cdr_en field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclk2cdren - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_2cdr_en_setf(uint8_t wfdtmxclk2cdren)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wfdtmxclk2cdren << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_dll_reg_vbit field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_logen_dll_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_dll_reg_vbit field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_dll_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x00780000)) >> 19);
}

/**
 * @brief Sets the wf_dtmx_logen_dll_reg_vbit field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogendllregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_dll_reg_vbit_setf(uint8_t wfdtmxlogendllregvbit)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x00780000)) | (((uint32_t)wfdtmxlogendllregvbit << 19) & ((uint32_t)0x00780000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_dll_fref_dly_bit field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_logen_dll_fref_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_dll_fref_dly_bit field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_dll_fref_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x00078000)) >> 15);
}

/**
 * @brief Sets the wf_dtmx_logen_dll_fref_dly_bit field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogendllfrefdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_dll_fref_dly_bit_setf(uint8_t wfdtmxlogendllfrefdlybit)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x00078000)) | (((uint32_t)wfdtmxlogendllfrefdlybit << 15) & ((uint32_t)0x00078000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_logen_dll_fbc_dly_bit field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_logen_dll_fbc_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_logen_dll_fbc_dly_bit field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_logen_dll_fbc_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x00007800)) >> 11);
}

/**
 * @brief Sets the wf_dtmx_logen_dll_fbc_dly_bit field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlogendllfbcdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_logen_dll_fbc_dly_bit_setf(uint8_t wfdtmxlogendllfbcdlybit)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x00007800)) | (((uint32_t)wfdtmxlogendllfbcdlybit << 11) & ((uint32_t)0x00007800)));
}

/**
 * @brief Returns the current value of the wf_dtmx_offset_bit field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_offset_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_offset_bit field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_offset_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x000007C0)) >> 6);
}

/**
 * @brief Sets the wf_dtmx_offset_bit field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxoffsetbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_offset_bit_setf(uint8_t wfdtmxoffsetbit)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x000007C0)) | (((uint32_t)wfdtmxoffsetbit << 6) & ((uint32_t)0x000007C0)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_edge_sel field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_clk_edge_sel field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_edge_sel field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the wf_dtmx_clk_edge_sel field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkedgesel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_edge_sel_setf(uint8_t wfdtmxclkedgesel)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)wfdtmxclkedgesel << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_phase_sel_bit field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_clk_phase_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_phase_sel_bit field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_phase_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x0000001C)) >> 2);
}

/**
 * @brief Sets the wf_dtmx_clk_phase_sel_bit field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkphaseselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_phase_sel_bit_setf(uint8_t wfdtmxclkphaseselbit)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x0000001C)) | (((uint32_t)wfdtmxclkphaseselbit << 2) & ((uint32_t)0x0000001C)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_iq_dly_en field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_clk_iq_dly_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_iq_dly_en field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_iq_dly_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_dtmx_clk_iq_dly_en field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkiqdlyen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_iq_dly_en_setf(uint8_t wfdtmxclkiqdlyen)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfdtmxclkiqdlyen << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_path0_45_dly_en field in the REG_48 register.
 *
 * The REG_48 register will be read and the wf_dtmx_clk_path0_45_dly_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_path0_45_dly_en field in the REG_48 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_path_0__45_dly_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_48_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_dtmx_clk_path0_45_dly_en field of the REG_48 register.
 *
 * The REG_48 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkpath045dlyen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_path_0__45_dly_en_setf(uint8_t wfdtmxclkpath045dlyen)
{
    REG_PL_WR(WLAN_RF_REG_48_ADDR, (REG_PL_RD(WLAN_RF_REG_48_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfdtmxclkpath045dlyen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_4C register definitions
 * <table>
 * <caption id="REG_4C_BF">REG_4C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>27:25 <td>wf_dtmx_clk_freq_sel_bit <td>R <td>R/W <td>0x4
 * <tr><td>24:20 <td>wf_dtmx_clk2dig_dly_bit <td>R <td>R/W <td>0x0
 * <tr><td>19:18 <td>wf_dtmx_cdr_div_freq_sel_bit <td>R <td>R/W <td>0x1
 * <tr><td>17 <td>wf_dtmx_clk2dac_sel_dig <td>R <td>R/W <td>0
 * <tr><td>16:14 <td>wf_dtmx_clk2dac_dly_bit <td>R <td>R/W <td>0x0
 * <tr><td>13 <td>wf_dtmx_cdr_sel_en <td>R <td>R/W <td>1
 * <tr><td>12 <td>  wf_dtmx_cdr_lock <td>W <td>R <td>0
 * <tr><td>11:10 <td>wf_dtmx_cdr_dly_lck_bit <td>W <td>R <td>0x0
 * <tr><td>09:07 <td>wf_dtmx_cdr_phase_lck_bit <td>W <td>R <td>0x0
 * <tr><td>06 <td>    wf_dtmx_dpd_en <td>R <td>R/W <td>0
 * <tr><td>05:03 <td>wf_dtmx_dpd_tia_gbit <td>R <td>R/W <td>0x4
 * <tr><td>02:00 <td>wf_dtmx_dpd_tia_miller_cbit <td>R <td>R/W <td>0x4
 * </table>
 *
 * @{
 */

/// Address of the REG_4C register
#define WLAN_RF_REG_4C_ADDR   0x4034404C
/// Offset of the REG_4C register from the base address
#define WLAN_RF_REG_4C_OFFSET 0x0000004C
/// Index of the REG_4C register
#define WLAN_RF_REG_4C_INDEX  0x00000013
/// Reset value of the REG_4C register
#define WLAN_RF_REG_4C_RESET  0x08042024

/**
 * @brief Returns the current value of the REG_4C register.
 * The REG_4C register will be read and its value returned.
 * @return The current value of the REG_4C register.
 */
__INLINE uint32_t wlan_rf_reg_4c_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_4C_ADDR);
}

/**
 * @brief Sets the REG_4C register to a value.
 * The REG_4C register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_4c_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, value);
}

// field definitions
/// WF_DTMX_CLK_FREQ_SEL_BIT field mask
#define WLAN_RF_WF_DTMX_CLK_FREQ_SEL_BIT_MASK       ((uint32_t)0x0E000000)
/// WF_DTMX_CLK_FREQ_SEL_BIT field LSB position
#define WLAN_RF_WF_DTMX_CLK_FREQ_SEL_BIT_LSB        25
/// WF_DTMX_CLK_FREQ_SEL_BIT field width
#define WLAN_RF_WF_DTMX_CLK_FREQ_SEL_BIT_WIDTH      ((uint32_t)0x00000003)
/// WF_DTMX_CLK_2DIG_DLY_BIT field mask
#define WLAN_RF_WF_DTMX_CLK_2DIG_DLY_BIT_MASK       ((uint32_t)0x01F00000)
/// WF_DTMX_CLK_2DIG_DLY_BIT field LSB position
#define WLAN_RF_WF_DTMX_CLK_2DIG_DLY_BIT_LSB        20
/// WF_DTMX_CLK_2DIG_DLY_BIT field width
#define WLAN_RF_WF_DTMX_CLK_2DIG_DLY_BIT_WIDTH      ((uint32_t)0x00000005)
/// WF_DTMX_CDR_DIV_FREQ_SEL_BIT field mask
#define WLAN_RF_WF_DTMX_CDR_DIV_FREQ_SEL_BIT_MASK   ((uint32_t)0x000C0000)
/// WF_DTMX_CDR_DIV_FREQ_SEL_BIT field LSB position
#define WLAN_RF_WF_DTMX_CDR_DIV_FREQ_SEL_BIT_LSB    18
/// WF_DTMX_CDR_DIV_FREQ_SEL_BIT field width
#define WLAN_RF_WF_DTMX_CDR_DIV_FREQ_SEL_BIT_WIDTH  ((uint32_t)0x00000002)
/// WF_DTMX_CLK_2DAC_SEL_DIG field bit
#define WLAN_RF_WF_DTMX_CLK_2DAC_SEL_DIG_BIT        ((uint32_t)0x00020000)
/// WF_DTMX_CLK_2DAC_SEL_DIG field position
#define WLAN_RF_WF_DTMX_CLK_2DAC_SEL_DIG_POS        17
/// WF_DTMX_CLK_2DAC_DLY_BIT field mask
#define WLAN_RF_WF_DTMX_CLK_2DAC_DLY_BIT_MASK       ((uint32_t)0x0001C000)
/// WF_DTMX_CLK_2DAC_DLY_BIT field LSB position
#define WLAN_RF_WF_DTMX_CLK_2DAC_DLY_BIT_LSB        14
/// WF_DTMX_CLK_2DAC_DLY_BIT field width
#define WLAN_RF_WF_DTMX_CLK_2DAC_DLY_BIT_WIDTH      ((uint32_t)0x00000003)
/// WF_DTMX_CDR_SEL_EN field bit
#define WLAN_RF_WF_DTMX_CDR_SEL_EN_BIT              ((uint32_t)0x00002000)
/// WF_DTMX_CDR_SEL_EN field position
#define WLAN_RF_WF_DTMX_CDR_SEL_EN_POS              13
/// WF_DTMX_CDR_LOCK field bit
#define WLAN_RF_WF_DTMX_CDR_LOCK_BIT                ((uint32_t)0x00001000)
/// WF_DTMX_CDR_LOCK field position
#define WLAN_RF_WF_DTMX_CDR_LOCK_POS                12
/// WF_DTMX_CDR_DLY_LCK_BIT field mask
#define WLAN_RF_WF_DTMX_CDR_DLY_LCK_BIT_MASK        ((uint32_t)0x00000C00)
/// WF_DTMX_CDR_DLY_LCK_BIT field LSB position
#define WLAN_RF_WF_DTMX_CDR_DLY_LCK_BIT_LSB         10
/// WF_DTMX_CDR_DLY_LCK_BIT field width
#define WLAN_RF_WF_DTMX_CDR_DLY_LCK_BIT_WIDTH       ((uint32_t)0x00000002)
/// WF_DTMX_CDR_PHASE_LCK_BIT field mask
#define WLAN_RF_WF_DTMX_CDR_PHASE_LCK_BIT_MASK      ((uint32_t)0x00000380)
/// WF_DTMX_CDR_PHASE_LCK_BIT field LSB position
#define WLAN_RF_WF_DTMX_CDR_PHASE_LCK_BIT_LSB       7
/// WF_DTMX_CDR_PHASE_LCK_BIT field width
#define WLAN_RF_WF_DTMX_CDR_PHASE_LCK_BIT_WIDTH     ((uint32_t)0x00000003)
/// WF_DTMX_DPD_EN field bit
#define WLAN_RF_WF_DTMX_DPD_EN_BIT                  ((uint32_t)0x00000040)
/// WF_DTMX_DPD_EN field position
#define WLAN_RF_WF_DTMX_DPD_EN_POS                  6
/// WF_DTMX_DPD_TIA_GBIT field mask
#define WLAN_RF_WF_DTMX_DPD_TIA_GBIT_MASK           ((uint32_t)0x00000038)
/// WF_DTMX_DPD_TIA_GBIT field LSB position
#define WLAN_RF_WF_DTMX_DPD_TIA_GBIT_LSB            3
/// WF_DTMX_DPD_TIA_GBIT field width
#define WLAN_RF_WF_DTMX_DPD_TIA_GBIT_WIDTH          ((uint32_t)0x00000003)
/// WF_DTMX_DPD_TIA_MILLER_CBIT field mask
#define WLAN_RF_WF_DTMX_DPD_TIA_MILLER_CBIT_MASK    ((uint32_t)0x00000007)
/// WF_DTMX_DPD_TIA_MILLER_CBIT field LSB position
#define WLAN_RF_WF_DTMX_DPD_TIA_MILLER_CBIT_LSB     0
/// WF_DTMX_DPD_TIA_MILLER_CBIT field width
#define WLAN_RF_WF_DTMX_DPD_TIA_MILLER_CBIT_WIDTH   ((uint32_t)0x00000003)

/// WF_DTMX_CLK_FREQ_SEL_BIT field reset value
#define WLAN_RF_WF_DTMX_CLK_FREQ_SEL_BIT_RST        0x4
/// WF_DTMX_CLK_2DIG_DLY_BIT field reset value
#define WLAN_RF_WF_DTMX_CLK_2DIG_DLY_BIT_RST        0x0
/// WF_DTMX_CDR_DIV_FREQ_SEL_BIT field reset value
#define WLAN_RF_WF_DTMX_CDR_DIV_FREQ_SEL_BIT_RST    0x1
/// WF_DTMX_CLK_2DAC_SEL_DIG field reset value
#define WLAN_RF_WF_DTMX_CLK_2DAC_SEL_DIG_RST        0x0
/// WF_DTMX_CLK_2DAC_DLY_BIT field reset value
#define WLAN_RF_WF_DTMX_CLK_2DAC_DLY_BIT_RST        0x0
/// WF_DTMX_CDR_SEL_EN field reset value
#define WLAN_RF_WF_DTMX_CDR_SEL_EN_RST              0x1
/// WF_DTMX_CDR_LOCK field reset value
#define WLAN_RF_WF_DTMX_CDR_LOCK_RST                0x0
/// WF_DTMX_CDR_DLY_LCK_BIT field reset value
#define WLAN_RF_WF_DTMX_CDR_DLY_LCK_BIT_RST         0x0
/// WF_DTMX_CDR_PHASE_LCK_BIT field reset value
#define WLAN_RF_WF_DTMX_CDR_PHASE_LCK_BIT_RST       0x0
/// WF_DTMX_DPD_EN field reset value
#define WLAN_RF_WF_DTMX_DPD_EN_RST                  0x0
/// WF_DTMX_DPD_TIA_GBIT field reset value
#define WLAN_RF_WF_DTMX_DPD_TIA_GBIT_RST            0x4
/// WF_DTMX_DPD_TIA_MILLER_CBIT field reset value
#define WLAN_RF_WF_DTMX_DPD_TIA_MILLER_CBIT_RST     0x4

/**
 * @brief Constructs a value for the REG_4C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfdtmxclkfreqselbit - The value to use for the wf_dtmx_clk_freq_sel_bit field.
 * @param[in] wfdtmxclk2digdlybit - The value to use for the wf_dtmx_clk2dig_dly_bit field.
 * @param[in] wfdtmxcdrdivfreqselbit - The value to use for the wf_dtmx_cdr_div_freq_sel_bit field.
 * @param[in] wfdtmxclk2dacseldig - The value to use for the wf_dtmx_clk2dac_sel_dig field.
 * @param[in] wfdtmxclk2dacdlybit - The value to use for the wf_dtmx_clk2dac_dly_bit field.
 * @param[in] wfdtmxcdrselen - The value to use for the wf_dtmx_cdr_sel_en field.
 * @param[in] wfdtmxdpden - The value to use for the wf_dtmx_dpd_en field.
 * @param[in] wfdtmxdpdtiagbit - The value to use for the wf_dtmx_dpd_tia_gbit field.
 * @param[in] wfdtmxdpdtiamillercbit - The value to use for the wf_dtmx_dpd_tia_miller_cbit field.
 */
__INLINE void wlan_rf_reg_4c_pack(uint8_t wfdtmxclkfreqselbit, uint8_t wfdtmxclk2digdlybit, uint8_t wfdtmxcdrdivfreqselbit, uint8_t wfdtmxclk2dacseldig, uint8_t wfdtmxclk2dacdlybit, uint8_t wfdtmxcdrselen, uint8_t wfdtmxdpden, uint8_t wfdtmxdpdtiagbit, uint8_t wfdtmxdpdtiamillercbit)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR,  ((uint32_t)wfdtmxclkfreqselbit << 25) | ((uint32_t)wfdtmxclk2digdlybit << 20) | ((uint32_t)wfdtmxcdrdivfreqselbit << 18) | ((uint32_t)wfdtmxclk2dacseldig << 17) | ((uint32_t)wfdtmxclk2dacdlybit << 14) | ((uint32_t)wfdtmxcdrselen << 13) | ((uint32_t)wfdtmxdpden << 6) | ((uint32_t)wfdtmxdpdtiagbit << 3) | ((uint32_t)wfdtmxdpdtiamillercbit << 0));
}

/**
 * @brief Unpacks REG_4C's fields from current value of the REG_4C register.
 *
 * Reads the REG_4C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfdtmxclkfreqselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclk2digdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrdivfreqselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclk2dacseldig - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclk2dacdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrselen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrlock - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrdlylckbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrphaselckbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdpden - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdpdtiagbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdpdtiamillercbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_4c_unpack(uint8_t* wfdtmxclkfreqselbit, uint8_t* wfdtmxclk2digdlybit, uint8_t* wfdtmxcdrdivfreqselbit, uint8_t* wfdtmxclk2dacseldig, uint8_t* wfdtmxclk2dacdlybit, uint8_t* wfdtmxcdrselen, uint8_t* wfdtmxcdrlock, uint8_t* wfdtmxcdrdlylckbit, uint8_t* wfdtmxcdrphaselckbit, uint8_t* wfdtmxdpden, uint8_t* wfdtmxdpdtiagbit, uint8_t* wfdtmxdpdtiamillercbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);

    *wfdtmxclkfreqselbit = (localVal & ((uint32_t)0x0E000000)) >> 25;
    *wfdtmxclk2digdlybit = (localVal & ((uint32_t)0x01F00000)) >> 20;
    *wfdtmxcdrdivfreqselbit = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *wfdtmxclk2dacseldig = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wfdtmxclk2dacdlybit = (localVal & ((uint32_t)0x0001C000)) >> 14;
    *wfdtmxcdrselen = (localVal & ((uint32_t)0x00002000)) >> 13;
    *wfdtmxcdrlock = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wfdtmxcdrdlylckbit = (localVal & ((uint32_t)0x00000C00)) >> 10;
    *wfdtmxcdrphaselckbit = (localVal & ((uint32_t)0x00000380)) >> 7;
    *wfdtmxdpden = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wfdtmxdpdtiagbit = (localVal & ((uint32_t)0x00000038)) >> 3;
    *wfdtmxdpdtiamillercbit = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_freq_sel_bit field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_clk_freq_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_freq_sel_bit field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_freq_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x0E000000)) >> 25);
}

/**
 * @brief Sets the wf_dtmx_clk_freq_sel_bit field of the REG_4C register.
 *
 * The REG_4C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkfreqselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_freq_sel_bit_setf(uint8_t wfdtmxclkfreqselbit)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, (REG_PL_RD(WLAN_RF_REG_4C_ADDR) & ~((uint32_t)0x0E000000)) | (((uint32_t)wfdtmxclkfreqselbit << 25) & ((uint32_t)0x0E000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk2dig_dly_bit field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_clk2dig_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk2dig_dly_bit field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_2dig_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x01F00000)) >> 20);
}

/**
 * @brief Sets the wf_dtmx_clk2dig_dly_bit field of the REG_4C register.
 *
 * The REG_4C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclk2digdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_2dig_dly_bit_setf(uint8_t wfdtmxclk2digdlybit)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, (REG_PL_RD(WLAN_RF_REG_4C_ADDR) & ~((uint32_t)0x01F00000)) | (((uint32_t)wfdtmxclk2digdlybit << 20) & ((uint32_t)0x01F00000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_div_freq_sel_bit field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_cdr_div_freq_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_div_freq_sel_bit field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_div_freq_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the wf_dtmx_cdr_div_freq_sel_bit field of the REG_4C register.
 *
 * The REG_4C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdrdivfreqselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_div_freq_sel_bit_setf(uint8_t wfdtmxcdrdivfreqselbit)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, (REG_PL_RD(WLAN_RF_REG_4C_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)wfdtmxcdrdivfreqselbit << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk2dac_sel_dig field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_clk2dac_sel_dig field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk2dac_sel_dig field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_2dac_sel_dig_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_dtmx_clk2dac_sel_dig field of the REG_4C register.
 *
 * The REG_4C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclk2dacseldig - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_2dac_sel_dig_setf(uint8_t wfdtmxclk2dacseldig)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, (REG_PL_RD(WLAN_RF_REG_4C_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wfdtmxclk2dacseldig << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk2dac_dly_bit field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_clk2dac_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk2dac_dly_bit field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_2dac_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x0001C000)) >> 14);
}

/**
 * @brief Sets the wf_dtmx_clk2dac_dly_bit field of the REG_4C register.
 *
 * The REG_4C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclk2dacdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_2dac_dly_bit_setf(uint8_t wfdtmxclk2dacdlybit)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, (REG_PL_RD(WLAN_RF_REG_4C_ADDR) & ~((uint32_t)0x0001C000)) | (((uint32_t)wfdtmxclk2dacdlybit << 14) & ((uint32_t)0x0001C000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_sel_en field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_cdr_sel_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_sel_en field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_sel_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the wf_dtmx_cdr_sel_en field of the REG_4C register.
 *
 * The REG_4C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdrselen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_sel_en_setf(uint8_t wfdtmxcdrselen)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, (REG_PL_RD(WLAN_RF_REG_4C_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)wfdtmxcdrselen << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_lock field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_cdr_lock field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_lock field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_lock_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_dly_lck_bit field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_cdr_dly_lck_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_dly_lck_bit field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_dly_lck_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x00000C00)) >> 10);
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_phase_lck_bit field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_cdr_phase_lck_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_phase_lck_bit field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_phase_lck_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x00000380)) >> 7);
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_en field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_dpd_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_en field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the wf_dtmx_dpd_en field of the REG_4C register.
 *
 * The REG_4C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpden - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_en_setf(uint8_t wfdtmxdpden)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, (REG_PL_RD(WLAN_RF_REG_4C_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)wfdtmxdpden << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_tia_gbit field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_dpd_tia_gbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_tia_gbit field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_tia_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x00000038)) >> 3);
}

/**
 * @brief Sets the wf_dtmx_dpd_tia_gbit field of the REG_4C register.
 *
 * The REG_4C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdtiagbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_tia_gbit_setf(uint8_t wfdtmxdpdtiagbit)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, (REG_PL_RD(WLAN_RF_REG_4C_ADDR) & ~((uint32_t)0x00000038)) | (((uint32_t)wfdtmxdpdtiagbit << 3) & ((uint32_t)0x00000038)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_tia_miller_cbit field in the REG_4C register.
 *
 * The REG_4C register will be read and the wf_dtmx_dpd_tia_miller_cbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_tia_miller_cbit field in the REG_4C register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_tia_miller_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_4C_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/**
 * @brief Sets the wf_dtmx_dpd_tia_miller_cbit field of the REG_4C register.
 *
 * The REG_4C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdtiamillercbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_tia_miller_cbit_setf(uint8_t wfdtmxdpdtiamillercbit)
{
    REG_PL_WR(WLAN_RF_REG_4C_ADDR, (REG_PL_RD(WLAN_RF_REG_4C_ADDR) & ~((uint32_t)0x00000007)) | (((uint32_t)wfdtmxdpdtiamillercbit << 0) & ((uint32_t)0x00000007)));
}

/// @}

/**
 * @name REG_50 register definitions
 * <table>
 * <caption id="REG_50_BF">REG_50 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:26 <td>wf_dtmx_dpd_tia_miller_rbit <td>R <td>R/W <td>0x1F
 * <tr><td>25:19 <td>wf_dtmx_dpd_tia_q_rbit <td>R <td>R/W <td>0x3F
 * <tr><td>18 <td>wf_dtmx_dpd_tia_rstn <td>R <td>R/W <td>0
 * <tr><td>17:15 <td>wf_dtmx_dpd_tia_vcm_vbit <td>R <td>R/W <td>0x4
 * <tr><td>14:12 <td>wf_dtmx_dpd_lobias_vbit <td>R <td>R/W <td>0x4
 * <tr><td>11 <td>wf_dtmx_dpd_img_cal_en <td>R <td>R/W <td>0
 * <tr><td>10 <td>wf_dtmx_idac_ic_sel_dtmx <td>R <td>R/W <td>0
 * <tr><td>09 <td>wf_dtmx_idac_padyn_clk_sel_pos_edge <td>R <td>R/W <td>0
 * <tr><td>08 <td>wf_dtmx_idac_padyn_en <td>W <td>R <td>0
 * <tr><td>07:04 <td>wf_dtmx_idac_padyn_offset_bit <td>R <td>R/W <td>0x0
 * <tr><td>03:00 <td>wf_dtmx_rfdyn_gbit <td>W <td>R <td>0x8
 * </table>
 *
 * @{
 */

/// Address of the REG_50 register
#define WLAN_RF_REG_50_ADDR   0x40344050
/// Offset of the REG_50 register from the base address
#define WLAN_RF_REG_50_OFFSET 0x00000050
/// Index of the REG_50 register
#define WLAN_RF_REG_50_INDEX  0x00000014
/// Reset value of the REG_50 register
#define WLAN_RF_REG_50_RESET  0x7DFA4008

/**
 * @brief Returns the current value of the REG_50 register.
 * The REG_50 register will be read and its value returned.
 * @return The current value of the REG_50 register.
 */
__INLINE uint32_t wlan_rf_reg_50_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_50_ADDR);
}

/**
 * @brief Sets the REG_50 register to a value.
 * The REG_50 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_50_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, value);
}

// field definitions
/// WF_DTMX_DPD_TIA_MILLER_RBIT field mask
#define WLAN_RF_WF_DTMX_DPD_TIA_MILLER_RBIT_MASK           ((uint32_t)0xFC000000)
/// WF_DTMX_DPD_TIA_MILLER_RBIT field LSB position
#define WLAN_RF_WF_DTMX_DPD_TIA_MILLER_RBIT_LSB            26
/// WF_DTMX_DPD_TIA_MILLER_RBIT field width
#define WLAN_RF_WF_DTMX_DPD_TIA_MILLER_RBIT_WIDTH          ((uint32_t)0x00000006)
/// WF_DTMX_DPD_TIA_Q_RBIT field mask
#define WLAN_RF_WF_DTMX_DPD_TIA_Q_RBIT_MASK                ((uint32_t)0x03F80000)
/// WF_DTMX_DPD_TIA_Q_RBIT field LSB position
#define WLAN_RF_WF_DTMX_DPD_TIA_Q_RBIT_LSB                 19
/// WF_DTMX_DPD_TIA_Q_RBIT field width
#define WLAN_RF_WF_DTMX_DPD_TIA_Q_RBIT_WIDTH               ((uint32_t)0x00000007)
/// WF_DTMX_DPD_TIA_RSTN field bit
#define WLAN_RF_WF_DTMX_DPD_TIA_RSTN_BIT                   ((uint32_t)0x00040000)
/// WF_DTMX_DPD_TIA_RSTN field position
#define WLAN_RF_WF_DTMX_DPD_TIA_RSTN_POS                   18
/// WF_DTMX_DPD_TIA_VCM_VBIT field mask
#define WLAN_RF_WF_DTMX_DPD_TIA_VCM_VBIT_MASK              ((uint32_t)0x00038000)
/// WF_DTMX_DPD_TIA_VCM_VBIT field LSB position
#define WLAN_RF_WF_DTMX_DPD_TIA_VCM_VBIT_LSB               15
/// WF_DTMX_DPD_TIA_VCM_VBIT field width
#define WLAN_RF_WF_DTMX_DPD_TIA_VCM_VBIT_WIDTH             ((uint32_t)0x00000003)
/// WF_DTMX_DPD_LOBIAS_VBIT field mask
#define WLAN_RF_WF_DTMX_DPD_LOBIAS_VBIT_MASK               ((uint32_t)0x00007000)
/// WF_DTMX_DPD_LOBIAS_VBIT field LSB position
#define WLAN_RF_WF_DTMX_DPD_LOBIAS_VBIT_LSB                12
/// WF_DTMX_DPD_LOBIAS_VBIT field width
#define WLAN_RF_WF_DTMX_DPD_LOBIAS_VBIT_WIDTH              ((uint32_t)0x00000003)
/// WF_DTMX_DPD_IMG_CAL_EN field bit
#define WLAN_RF_WF_DTMX_DPD_IMG_CAL_EN_BIT                 ((uint32_t)0x00000800)
/// WF_DTMX_DPD_IMG_CAL_EN field position
#define WLAN_RF_WF_DTMX_DPD_IMG_CAL_EN_POS                 11
/// WF_DTMX_IDAC_IC_SEL_DTMX field bit
#define WLAN_RF_WF_DTMX_IDAC_IC_SEL_DTMX_BIT               ((uint32_t)0x00000400)
/// WF_DTMX_IDAC_IC_SEL_DTMX field position
#define WLAN_RF_WF_DTMX_IDAC_IC_SEL_DTMX_POS               10
/// WF_DTMX_IDAC_PADYN_CLK_SEL_POS_EDGE field bit
#define WLAN_RF_WF_DTMX_IDAC_PADYN_CLK_SEL_POS_EDGE_BIT    ((uint32_t)0x00000200)
/// WF_DTMX_IDAC_PADYN_CLK_SEL_POS_EDGE field position
#define WLAN_RF_WF_DTMX_IDAC_PADYN_CLK_SEL_POS_EDGE_POS    9
/// WF_DTMX_IDAC_PADYN_EN field bit
#define WLAN_RF_WF_DTMX_IDAC_PADYN_EN_BIT                  ((uint32_t)0x00000100)
/// WF_DTMX_IDAC_PADYN_EN field position
#define WLAN_RF_WF_DTMX_IDAC_PADYN_EN_POS                  8
/// WF_DTMX_IDAC_PADYN_OFFSET_BIT field mask
#define WLAN_RF_WF_DTMX_IDAC_PADYN_OFFSET_BIT_MASK         ((uint32_t)0x000000F0)
/// WF_DTMX_IDAC_PADYN_OFFSET_BIT field LSB position
#define WLAN_RF_WF_DTMX_IDAC_PADYN_OFFSET_BIT_LSB          4
/// WF_DTMX_IDAC_PADYN_OFFSET_BIT field width
#define WLAN_RF_WF_DTMX_IDAC_PADYN_OFFSET_BIT_WIDTH        ((uint32_t)0x00000004)
/// WF_DTMX_RFDYN_GBIT field mask
#define WLAN_RF_WF_DTMX_RFDYN_GBIT_MASK                    ((uint32_t)0x0000000F)
/// WF_DTMX_RFDYN_GBIT field LSB position
#define WLAN_RF_WF_DTMX_RFDYN_GBIT_LSB                     0
/// WF_DTMX_RFDYN_GBIT field width
#define WLAN_RF_WF_DTMX_RFDYN_GBIT_WIDTH                   ((uint32_t)0x00000004)

/// WF_DTMX_DPD_TIA_MILLER_RBIT field reset value
#define WLAN_RF_WF_DTMX_DPD_TIA_MILLER_RBIT_RST            0x1F
/// WF_DTMX_DPD_TIA_Q_RBIT field reset value
#define WLAN_RF_WF_DTMX_DPD_TIA_Q_RBIT_RST                 0x3F
/// WF_DTMX_DPD_TIA_RSTN field reset value
#define WLAN_RF_WF_DTMX_DPD_TIA_RSTN_RST                   0x0
/// WF_DTMX_DPD_TIA_VCM_VBIT field reset value
#define WLAN_RF_WF_DTMX_DPD_TIA_VCM_VBIT_RST               0x4
/// WF_DTMX_DPD_LOBIAS_VBIT field reset value
#define WLAN_RF_WF_DTMX_DPD_LOBIAS_VBIT_RST                0x4
/// WF_DTMX_DPD_IMG_CAL_EN field reset value
#define WLAN_RF_WF_DTMX_DPD_IMG_CAL_EN_RST                 0x0
/// WF_DTMX_IDAC_IC_SEL_DTMX field reset value
#define WLAN_RF_WF_DTMX_IDAC_IC_SEL_DTMX_RST               0x0
/// WF_DTMX_IDAC_PADYN_CLK_SEL_POS_EDGE field reset value
#define WLAN_RF_WF_DTMX_IDAC_PADYN_CLK_SEL_POS_EDGE_RST    0x0
/// WF_DTMX_IDAC_PADYN_EN field reset value
#define WLAN_RF_WF_DTMX_IDAC_PADYN_EN_RST                  0x0
/// WF_DTMX_IDAC_PADYN_OFFSET_BIT field reset value
#define WLAN_RF_WF_DTMX_IDAC_PADYN_OFFSET_BIT_RST          0x0
/// WF_DTMX_RFDYN_GBIT field reset value
#define WLAN_RF_WF_DTMX_RFDYN_GBIT_RST                     0x8

/**
 * @brief Constructs a value for the REG_50 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfdtmxdpdtiamillerrbit - The value to use for the wf_dtmx_dpd_tia_miller_rbit field.
 * @param[in] wfdtmxdpdtiaqrbit - The value to use for the wf_dtmx_dpd_tia_q_rbit field.
 * @param[in] wfdtmxdpdtiarstn - The value to use for the wf_dtmx_dpd_tia_rstn field.
 * @param[in] wfdtmxdpdtiavcmvbit - The value to use for the wf_dtmx_dpd_tia_vcm_vbit field.
 * @param[in] wfdtmxdpdlobiasvbit - The value to use for the wf_dtmx_dpd_lobias_vbit field.
 * @param[in] wfdtmxdpdimgcalen - The value to use for the wf_dtmx_dpd_img_cal_en field.
 * @param[in] wfdtmxidacicseldtmx - The value to use for the wf_dtmx_idac_ic_sel_dtmx field.
 * @param[in] wfdtmxidacpadynclkselposedge - The value to use for the wf_dtmx_idac_padyn_clk_sel_pos_edge field.
 * @param[in] wfdtmxidacpadynoffsetbit - The value to use for the wf_dtmx_idac_padyn_offset_bit field.
 */
__INLINE void wlan_rf_reg_50_pack(uint8_t wfdtmxdpdtiamillerrbit, uint8_t wfdtmxdpdtiaqrbit, uint8_t wfdtmxdpdtiarstn, uint8_t wfdtmxdpdtiavcmvbit, uint8_t wfdtmxdpdlobiasvbit, uint8_t wfdtmxdpdimgcalen, uint8_t wfdtmxidacicseldtmx, uint8_t wfdtmxidacpadynclkselposedge, uint8_t wfdtmxidacpadynoffsetbit)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR,  ((uint32_t)wfdtmxdpdtiamillerrbit << 26) | ((uint32_t)wfdtmxdpdtiaqrbit << 19) | ((uint32_t)wfdtmxdpdtiarstn << 18) | ((uint32_t)wfdtmxdpdtiavcmvbit << 15) | ((uint32_t)wfdtmxdpdlobiasvbit << 12) | ((uint32_t)wfdtmxdpdimgcalen << 11) | ((uint32_t)wfdtmxidacicseldtmx << 10) | ((uint32_t)wfdtmxidacpadynclkselposedge << 9) | ((uint32_t)wfdtmxidacpadynoffsetbit << 4));
}

/**
 * @brief Unpacks REG_50's fields from current value of the REG_50 register.
 *
 * Reads the REG_50 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfdtmxdpdtiamillerrbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdpdtiaqrbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdpdtiarstn - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdpdtiavcmvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdpdlobiasvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdpdimgcalen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxidacicseldtmx - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxidacpadynclkselposedge - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxidacpadynen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxidacpadynoffsetbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxrfdyngbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_50_unpack(uint8_t* wfdtmxdpdtiamillerrbit, uint8_t* wfdtmxdpdtiaqrbit, uint8_t* wfdtmxdpdtiarstn, uint8_t* wfdtmxdpdtiavcmvbit, uint8_t* wfdtmxdpdlobiasvbit, uint8_t* wfdtmxdpdimgcalen, uint8_t* wfdtmxidacicseldtmx, uint8_t* wfdtmxidacpadynclkselposedge, uint8_t* wfdtmxidacpadynen, uint8_t* wfdtmxidacpadynoffsetbit, uint8_t* wfdtmxrfdyngbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);

    *wfdtmxdpdtiamillerrbit = (localVal & ((uint32_t)0xFC000000)) >> 26;
    *wfdtmxdpdtiaqrbit = (localVal & ((uint32_t)0x03F80000)) >> 19;
    *wfdtmxdpdtiarstn = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfdtmxdpdtiavcmvbit = (localVal & ((uint32_t)0x00038000)) >> 15;
    *wfdtmxdpdlobiasvbit = (localVal & ((uint32_t)0x00007000)) >> 12;
    *wfdtmxdpdimgcalen = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wfdtmxidacicseldtmx = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfdtmxidacpadynclkselposedge = (localVal & ((uint32_t)0x00000200)) >> 9;
    *wfdtmxidacpadynen = (localVal & ((uint32_t)0x00000100)) >> 8;
    *wfdtmxidacpadynoffsetbit = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *wfdtmxrfdyngbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_tia_miller_rbit field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_dpd_tia_miller_rbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_tia_miller_rbit field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_tia_miller_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0xFC000000)) >> 26);
}

/**
 * @brief Sets the wf_dtmx_dpd_tia_miller_rbit field of the REG_50 register.
 *
 * The REG_50 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdtiamillerrbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_tia_miller_rbit_setf(uint8_t wfdtmxdpdtiamillerrbit)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, (REG_PL_RD(WLAN_RF_REG_50_ADDR) & ~((uint32_t)0xFC000000)) | (((uint32_t)wfdtmxdpdtiamillerrbit << 26) & ((uint32_t)0xFC000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_tia_q_rbit field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_dpd_tia_q_rbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_tia_q_rbit field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_tia_q_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x03F80000)) >> 19);
}

/**
 * @brief Sets the wf_dtmx_dpd_tia_q_rbit field of the REG_50 register.
 *
 * The REG_50 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdtiaqrbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_tia_q_rbit_setf(uint8_t wfdtmxdpdtiaqrbit)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, (REG_PL_RD(WLAN_RF_REG_50_ADDR) & ~((uint32_t)0x03F80000)) | (((uint32_t)wfdtmxdpdtiaqrbit << 19) & ((uint32_t)0x03F80000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_tia_rstn field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_dpd_tia_rstn field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_tia_rstn field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_tia_rstn_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_dtmx_dpd_tia_rstn field of the REG_50 register.
 *
 * The REG_50 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdtiarstn - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_tia_rstn_setf(uint8_t wfdtmxdpdtiarstn)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, (REG_PL_RD(WLAN_RF_REG_50_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wfdtmxdpdtiarstn << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_tia_vcm_vbit field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_dpd_tia_vcm_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_tia_vcm_vbit field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_tia_vcm_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x00038000)) >> 15);
}

/**
 * @brief Sets the wf_dtmx_dpd_tia_vcm_vbit field of the REG_50 register.
 *
 * The REG_50 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdtiavcmvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_tia_vcm_vbit_setf(uint8_t wfdtmxdpdtiavcmvbit)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, (REG_PL_RD(WLAN_RF_REG_50_ADDR) & ~((uint32_t)0x00038000)) | (((uint32_t)wfdtmxdpdtiavcmvbit << 15) & ((uint32_t)0x00038000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_lobias_vbit field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_dpd_lobias_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_lobias_vbit field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_lobias_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

/**
 * @brief Sets the wf_dtmx_dpd_lobias_vbit field of the REG_50 register.
 *
 * The REG_50 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdlobiasvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_lobias_vbit_setf(uint8_t wfdtmxdpdlobiasvbit)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, (REG_PL_RD(WLAN_RF_REG_50_ADDR) & ~((uint32_t)0x00007000)) | (((uint32_t)wfdtmxdpdlobiasvbit << 12) & ((uint32_t)0x00007000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_img_cal_en field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_dpd_img_cal_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_img_cal_en field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_img_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_dtmx_dpd_img_cal_en field of the REG_50 register.
 *
 * The REG_50 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdimgcalen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_img_cal_en_setf(uint8_t wfdtmxdpdimgcalen)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, (REG_PL_RD(WLAN_RF_REG_50_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wfdtmxdpdimgcalen << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_dtmx_idac_ic_sel_dtmx field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_idac_ic_sel_dtmx field's value will be returned.
 *
 * @return The current value of the wf_dtmx_idac_ic_sel_dtmx field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_idac_ic_sel_dtmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_dtmx_idac_ic_sel_dtmx field of the REG_50 register.
 *
 * The REG_50 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxidacicseldtmx - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_idac_ic_sel_dtmx_setf(uint8_t wfdtmxidacicseldtmx)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, (REG_PL_RD(WLAN_RF_REG_50_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfdtmxidacicseldtmx << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_dtmx_idac_padyn_clk_sel_pos_edge field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_idac_padyn_clk_sel_pos_edge field's value will be returned.
 *
 * @return The current value of the wf_dtmx_idac_padyn_clk_sel_pos_edge field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_idac_padyn_clk_sel_pos_edge_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the wf_dtmx_idac_padyn_clk_sel_pos_edge field of the REG_50 register.
 *
 * The REG_50 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxidacpadynclkselposedge - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_idac_padyn_clk_sel_pos_edge_setf(uint8_t wfdtmxidacpadynclkselposedge)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, (REG_PL_RD(WLAN_RF_REG_50_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)wfdtmxidacpadynclkselposedge << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the wf_dtmx_idac_padyn_en field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_idac_padyn_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_idac_padyn_en field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_idac_padyn_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Returns the current value of the wf_dtmx_idac_padyn_offset_bit field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_idac_padyn_offset_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_idac_padyn_offset_bit field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_idac_padyn_offset_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Sets the wf_dtmx_idac_padyn_offset_bit field of the REG_50 register.
 *
 * The REG_50 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxidacpadynoffsetbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_idac_padyn_offset_bit_setf(uint8_t wfdtmxidacpadynoffsetbit)
{
    REG_PL_WR(WLAN_RF_REG_50_ADDR, (REG_PL_RD(WLAN_RF_REG_50_ADDR) & ~((uint32_t)0x000000F0)) | (((uint32_t)wfdtmxidacpadynoffsetbit << 4) & ((uint32_t)0x000000F0)));
}

/**
 * @brief Returns the current value of the wf_dtmx_rfdyn_gbit field in the REG_50 register.
 *
 * The REG_50 register will be read and the wf_dtmx_rfdyn_gbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_rfdyn_gbit field in the REG_50 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_rfdyn_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_50_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/// @}

/**
 * @name REG_54 register definitions
 * <table>
 * <caption id="REG_54_BF">REG_54 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>27:25 <td>wf_dtmx_rfdyn_vthbit <td>R <td>R/W <td>0x4
 * <tr><td>24:21 <td>wf_dtmx_rfdyn_ref_vbit <td>W <td>R <td>0x8
 * <tr><td>20 <td>wf_dtmx_dynbias_sel_dig <td>R <td>R/W <td>0
 * <tr><td>19 <td>wf_dtmx_dynbias_sel_rf <td>R <td>R/W <td>0
 * <tr><td>18 <td>wf_dtmx_dynbias_en <td>W <td>R <td>0
 * <tr><td>17 <td> wf_iref_start_enb <td>R <td>R/W <td>1
 * <tr><td>16:13 <td>   wf_trx_rsvd_bit <td>R <td>R/W <td>0xC
 * <tr><td>12:09 <td>wf_trx_rsvd_read_bit <td>W <td>R <td>0x0
 * <tr><td>08:07 <td>wf_rxflt_pwres_bit <td>R <td>R/W <td>0x2
 * <tr><td>06 <td> wf_rxflt_cal_mode <td>R <td>R/W <td>0
 * <tr><td>05:04 <td>wf_rxflt_notch_mode <td>W <td>R <td>0x0
 * <tr><td>03 <td>  wf_rxflt_iq_swap <td>R <td>R/W <td>0
 * <tr><td>02:00 <td>  wf_rxflt_bw_rbit <td>W <td>R <td>0x4
 * </table>
 *
 * @{
 */

/// Address of the REG_54 register
#define WLAN_RF_REG_54_ADDR   0x40344054
/// Offset of the REG_54 register from the base address
#define WLAN_RF_REG_54_OFFSET 0x00000054
/// Index of the REG_54 register
#define WLAN_RF_REG_54_INDEX  0x00000015
/// Reset value of the REG_54 register
#define WLAN_RF_REG_54_RESET  0x09038104

/**
 * @brief Returns the current value of the REG_54 register.
 * The REG_54 register will be read and its value returned.
 * @return The current value of the REG_54 register.
 */
__INLINE uint32_t wlan_rf_reg_54_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_54_ADDR);
}

/**
 * @brief Sets the REG_54 register to a value.
 * The REG_54 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_54_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR, value);
}

// field definitions
/// WF_DTMX_RFDYN_VTHBIT field mask
#define WLAN_RF_WF_DTMX_RFDYN_VTHBIT_MASK      ((uint32_t)0x0E000000)
/// WF_DTMX_RFDYN_VTHBIT field LSB position
#define WLAN_RF_WF_DTMX_RFDYN_VTHBIT_LSB       25
/// WF_DTMX_RFDYN_VTHBIT field width
#define WLAN_RF_WF_DTMX_RFDYN_VTHBIT_WIDTH     ((uint32_t)0x00000003)
/// WF_DTMX_RFDYN_REF_VBIT field mask
#define WLAN_RF_WF_DTMX_RFDYN_REF_VBIT_MASK    ((uint32_t)0x01E00000)
/// WF_DTMX_RFDYN_REF_VBIT field LSB position
#define WLAN_RF_WF_DTMX_RFDYN_REF_VBIT_LSB     21
/// WF_DTMX_RFDYN_REF_VBIT field width
#define WLAN_RF_WF_DTMX_RFDYN_REF_VBIT_WIDTH   ((uint32_t)0x00000004)
/// WF_DTMX_DYNBIAS_SEL_DIG field bit
#define WLAN_RF_WF_DTMX_DYNBIAS_SEL_DIG_BIT    ((uint32_t)0x00100000)
/// WF_DTMX_DYNBIAS_SEL_DIG field position
#define WLAN_RF_WF_DTMX_DYNBIAS_SEL_DIG_POS    20
/// WF_DTMX_DYNBIAS_SEL_RF field bit
#define WLAN_RF_WF_DTMX_DYNBIAS_SEL_RF_BIT     ((uint32_t)0x00080000)
/// WF_DTMX_DYNBIAS_SEL_RF field position
#define WLAN_RF_WF_DTMX_DYNBIAS_SEL_RF_POS     19
/// WF_DTMX_DYNBIAS_EN field bit
#define WLAN_RF_WF_DTMX_DYNBIAS_EN_BIT         ((uint32_t)0x00040000)
/// WF_DTMX_DYNBIAS_EN field position
#define WLAN_RF_WF_DTMX_DYNBIAS_EN_POS         18
/// WF_IREF_START_ENB field bit
#define WLAN_RF_WF_IREF_START_ENB_BIT          ((uint32_t)0x00020000)
/// WF_IREF_START_ENB field position
#define WLAN_RF_WF_IREF_START_ENB_POS          17
/// WF_TRX_RSVD_BIT field mask
#define WLAN_RF_WF_TRX_RSVD_BIT_MASK           ((uint32_t)0x0001E000)
/// WF_TRX_RSVD_BIT field LSB position
#define WLAN_RF_WF_TRX_RSVD_BIT_LSB            13
/// WF_TRX_RSVD_BIT field width
#define WLAN_RF_WF_TRX_RSVD_BIT_WIDTH          ((uint32_t)0x00000004)
/// WF_TRX_RSVD_READ_BIT field mask
#define WLAN_RF_WF_TRX_RSVD_READ_BIT_MASK      ((uint32_t)0x00001E00)
/// WF_TRX_RSVD_READ_BIT field LSB position
#define WLAN_RF_WF_TRX_RSVD_READ_BIT_LSB       9
/// WF_TRX_RSVD_READ_BIT field width
#define WLAN_RF_WF_TRX_RSVD_READ_BIT_WIDTH     ((uint32_t)0x00000004)
/// WF_RXFLT_PWRES_BIT field mask
#define WLAN_RF_WF_RXFLT_PWRES_BIT_MASK        ((uint32_t)0x00000180)
/// WF_RXFLT_PWRES_BIT field LSB position
#define WLAN_RF_WF_RXFLT_PWRES_BIT_LSB         7
/// WF_RXFLT_PWRES_BIT field width
#define WLAN_RF_WF_RXFLT_PWRES_BIT_WIDTH       ((uint32_t)0x00000002)
/// WF_RXFLT_CAL_MODE field bit
#define WLAN_RF_WF_RXFLT_CAL_MODE_BIT          ((uint32_t)0x00000040)
/// WF_RXFLT_CAL_MODE field position
#define WLAN_RF_WF_RXFLT_CAL_MODE_POS          6
/// WF_RXFLT_NOTCH_MODE field mask
#define WLAN_RF_WF_RXFLT_NOTCH_MODE_MASK       ((uint32_t)0x00000030)
/// WF_RXFLT_NOTCH_MODE field LSB position
#define WLAN_RF_WF_RXFLT_NOTCH_MODE_LSB        4
/// WF_RXFLT_NOTCH_MODE field width
#define WLAN_RF_WF_RXFLT_NOTCH_MODE_WIDTH      ((uint32_t)0x00000002)
/// WF_RXFLT_IQ_SWAP field bit
#define WLAN_RF_WF_RXFLT_IQ_SWAP_BIT           ((uint32_t)0x00000008)
/// WF_RXFLT_IQ_SWAP field position
#define WLAN_RF_WF_RXFLT_IQ_SWAP_POS           3
/// WF_RXFLT_BW_RBIT field mask
#define WLAN_RF_WF_RXFLT_BW_RBIT_MASK          ((uint32_t)0x00000007)
/// WF_RXFLT_BW_RBIT field LSB position
#define WLAN_RF_WF_RXFLT_BW_RBIT_LSB           0
/// WF_RXFLT_BW_RBIT field width
#define WLAN_RF_WF_RXFLT_BW_RBIT_WIDTH         ((uint32_t)0x00000003)

/// WF_DTMX_RFDYN_VTHBIT field reset value
#define WLAN_RF_WF_DTMX_RFDYN_VTHBIT_RST       0x4
/// WF_DTMX_RFDYN_REF_VBIT field reset value
#define WLAN_RF_WF_DTMX_RFDYN_REF_VBIT_RST     0x8
/// WF_DTMX_DYNBIAS_SEL_DIG field reset value
#define WLAN_RF_WF_DTMX_DYNBIAS_SEL_DIG_RST    0x0
/// WF_DTMX_DYNBIAS_SEL_RF field reset value
#define WLAN_RF_WF_DTMX_DYNBIAS_SEL_RF_RST     0x0
/// WF_DTMX_DYNBIAS_EN field reset value
#define WLAN_RF_WF_DTMX_DYNBIAS_EN_RST         0x0
/// WF_IREF_START_ENB field reset value
#define WLAN_RF_WF_IREF_START_ENB_RST          0x1
/// WF_TRX_RSVD_BIT field reset value
#define WLAN_RF_WF_TRX_RSVD_BIT_RST            0xC
/// WF_TRX_RSVD_READ_BIT field reset value
#define WLAN_RF_WF_TRX_RSVD_READ_BIT_RST       0x0
/// WF_RXFLT_PWRES_BIT field reset value
#define WLAN_RF_WF_RXFLT_PWRES_BIT_RST         0x2
/// WF_RXFLT_CAL_MODE field reset value
#define WLAN_RF_WF_RXFLT_CAL_MODE_RST          0x0
/// WF_RXFLT_NOTCH_MODE field reset value
#define WLAN_RF_WF_RXFLT_NOTCH_MODE_RST        0x0
/// WF_RXFLT_IQ_SWAP field reset value
#define WLAN_RF_WF_RXFLT_IQ_SWAP_RST           0x0
/// WF_RXFLT_BW_RBIT field reset value
#define WLAN_RF_WF_RXFLT_BW_RBIT_RST           0x4

/**
 * @brief Constructs a value for the REG_54 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfdtmxrfdynvthbit - The value to use for the wf_dtmx_rfdyn_vthbit field.
 * @param[in] wfdtmxdynbiasseldig - The value to use for the wf_dtmx_dynbias_sel_dig field.
 * @param[in] wfdtmxdynbiasselrf - The value to use for the wf_dtmx_dynbias_sel_rf field.
 * @param[in] wfirefstartenb - The value to use for the wf_iref_start_enb field.
 * @param[in] wftrxrsvdbit - The value to use for the wf_trx_rsvd_bit field.
 * @param[in] wfrxfltpwresbit - The value to use for the wf_rxflt_pwres_bit field.
 * @param[in] wfrxfltcalmode - The value to use for the wf_rxflt_cal_mode field.
 * @param[in] wfrxfltiqswap - The value to use for the wf_rxflt_iq_swap field.
 */
__INLINE void wlan_rf_reg_54_pack(uint8_t wfdtmxrfdynvthbit, uint8_t wfdtmxdynbiasseldig, uint8_t wfdtmxdynbiasselrf, uint8_t wfirefstartenb, uint8_t wftrxrsvdbit, uint8_t wfrxfltpwresbit, uint8_t wfrxfltcalmode, uint8_t wfrxfltiqswap)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR,  ((uint32_t)wfdtmxrfdynvthbit << 25) | ((uint32_t)wfdtmxdynbiasseldig << 20) | ((uint32_t)wfdtmxdynbiasselrf << 19) | ((uint32_t)wfirefstartenb << 17) | ((uint32_t)wftrxrsvdbit << 13) | ((uint32_t)wfrxfltpwresbit << 7) | ((uint32_t)wfrxfltcalmode << 6) | ((uint32_t)wfrxfltiqswap << 3));
}

/**
 * @brief Unpacks REG_54's fields from current value of the REG_54 register.
 *
 * Reads the REG_54 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfdtmxrfdynvthbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxrfdynrefvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdynbiasseldig - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdynbiasselrf - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdynbiasen - Will be populated with the current value of this field from the register.
 * @param[out] wfirefstartenb - Will be populated with the current value of this field from the register.
 * @param[out] wftrxrsvdbit - Will be populated with the current value of this field from the register.
 * @param[out] wftrxrsvdreadbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltpwresbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltcalmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltnotchmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltiqswap - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltbwrbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_54_unpack(uint8_t* wfdtmxrfdynvthbit, uint8_t* wfdtmxrfdynrefvbit, uint8_t* wfdtmxdynbiasseldig, uint8_t* wfdtmxdynbiasselrf, uint8_t* wfdtmxdynbiasen, uint8_t* wfirefstartenb, uint8_t* wftrxrsvdbit, uint8_t* wftrxrsvdreadbit, uint8_t* wfrxfltpwresbit, uint8_t* wfrxfltcalmode, uint8_t* wfrxfltnotchmode, uint8_t* wfrxfltiqswap, uint8_t* wfrxfltbwrbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);

    *wfdtmxrfdynvthbit = (localVal & ((uint32_t)0x0E000000)) >> 25;
    *wfdtmxrfdynrefvbit = (localVal & ((uint32_t)0x01E00000)) >> 21;
    *wfdtmxdynbiasseldig = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wfdtmxdynbiasselrf = (localVal & ((uint32_t)0x00080000)) >> 19;
    *wfdtmxdynbiasen = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfirefstartenb = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wftrxrsvdbit = (localVal & ((uint32_t)0x0001E000)) >> 13;
    *wftrxrsvdreadbit = (localVal & ((uint32_t)0x00001E00)) >> 9;
    *wfrxfltpwresbit = (localVal & ((uint32_t)0x00000180)) >> 7;
    *wfrxfltcalmode = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wfrxfltnotchmode = (localVal & ((uint32_t)0x00000030)) >> 4;
    *wfrxfltiqswap = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wfrxfltbwrbit = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the wf_dtmx_rfdyn_vthbit field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_dtmx_rfdyn_vthbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_rfdyn_vthbit field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_rfdyn_vthbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x0E000000)) >> 25);
}

/**
 * @brief Sets the wf_dtmx_rfdyn_vthbit field of the REG_54 register.
 *
 * The REG_54 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxrfdynvthbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_rfdyn_vthbit_setf(uint8_t wfdtmxrfdynvthbit)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR, (REG_PL_RD(WLAN_RF_REG_54_ADDR) & ~((uint32_t)0x0E000000)) | (((uint32_t)wfdtmxrfdynvthbit << 25) & ((uint32_t)0x0E000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_rfdyn_ref_vbit field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_dtmx_rfdyn_ref_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_rfdyn_ref_vbit field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_rfdyn_ref_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x01E00000)) >> 21);
}

/**
 * @brief Returns the current value of the wf_dtmx_dynbias_sel_dig field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_dtmx_dynbias_sel_dig field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dynbias_sel_dig field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dynbias_sel_dig_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_dtmx_dynbias_sel_dig field of the REG_54 register.
 *
 * The REG_54 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdynbiasseldig - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dynbias_sel_dig_setf(uint8_t wfdtmxdynbiasseldig)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR, (REG_PL_RD(WLAN_RF_REG_54_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wfdtmxdynbiasseldig << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dynbias_sel_rf field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_dtmx_dynbias_sel_rf field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dynbias_sel_rf field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dynbias_sel_rf_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the wf_dtmx_dynbias_sel_rf field of the REG_54 register.
 *
 * The REG_54 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdynbiasselrf - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dynbias_sel_rf_setf(uint8_t wfdtmxdynbiasselrf)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR, (REG_PL_RD(WLAN_RF_REG_54_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)wfdtmxdynbiasselrf << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dynbias_en field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_dtmx_dynbias_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dynbias_en field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dynbias_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Returns the current value of the wf_iref_start_enb field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_iref_start_enb field's value will be returned.
 *
 * @return The current value of the wf_iref_start_enb field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_iref_start_enb_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_iref_start_enb field of the REG_54 register.
 *
 * The REG_54 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfirefstartenb - The value to set the field to.
 */
__INLINE void wlan_rf_wf_iref_start_enb_setf(uint8_t wfirefstartenb)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR, (REG_PL_RD(WLAN_RF_REG_54_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wfirefstartenb << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_trx_rsvd_bit field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_trx_rsvd_bit field's value will be returned.
 *
 * @return The current value of the wf_trx_rsvd_bit field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_rsvd_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x0001E000)) >> 13);
}

/**
 * @brief Sets the wf_trx_rsvd_bit field of the REG_54 register.
 *
 * The REG_54 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftrxrsvdbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_trx_rsvd_bit_setf(uint8_t wftrxrsvdbit)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR, (REG_PL_RD(WLAN_RF_REG_54_ADDR) & ~((uint32_t)0x0001E000)) | (((uint32_t)wftrxrsvdbit << 13) & ((uint32_t)0x0001E000)));
}

/**
 * @brief Returns the current value of the wf_trx_rsvd_read_bit field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_trx_rsvd_read_bit field's value will be returned.
 *
 * @return The current value of the wf_trx_rsvd_read_bit field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_trx_rsvd_read_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00001E00)) >> 9);
}

/**
 * @brief Returns the current value of the wf_rxflt_pwres_bit field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_rxflt_pwres_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_pwres_bit field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_pwres_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00000180)) >> 7);
}

/**
 * @brief Sets the wf_rxflt_pwres_bit field of the REG_54 register.
 *
 * The REG_54 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltpwresbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_pwres_bit_setf(uint8_t wfrxfltpwresbit)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR, (REG_PL_RD(WLAN_RF_REG_54_ADDR) & ~((uint32_t)0x00000180)) | (((uint32_t)wfrxfltpwresbit << 7) & ((uint32_t)0x00000180)));
}

/**
 * @brief Returns the current value of the wf_rxflt_cal_mode field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_rxflt_cal_mode field's value will be returned.
 *
 * @return The current value of the wf_rxflt_cal_mode field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_cal_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the wf_rxflt_cal_mode field of the REG_54 register.
 *
 * The REG_54 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltcalmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_cal_mode_setf(uint8_t wfrxfltcalmode)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR, (REG_PL_RD(WLAN_RF_REG_54_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)wfrxfltcalmode << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the wf_rxflt_notch_mode field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_rxflt_notch_mode field's value will be returned.
 *
 * @return The current value of the wf_rxflt_notch_mode field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_notch_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

/**
 * @brief Returns the current value of the wf_rxflt_iq_swap field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_rxflt_iq_swap field's value will be returned.
 *
 * @return The current value of the wf_rxflt_iq_swap field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_iq_swap_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wf_rxflt_iq_swap field of the REG_54 register.
 *
 * The REG_54 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltiqswap - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_iq_swap_setf(uint8_t wfrxfltiqswap)
{
    REG_PL_WR(WLAN_RF_REG_54_ADDR, (REG_PL_RD(WLAN_RF_REG_54_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wfrxfltiqswap << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wf_rxflt_bw_rbit field in the REG_54 register.
 *
 * The REG_54 register will be read and the wf_rxflt_bw_rbit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_bw_rbit field in the REG_54 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_bw_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_54_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/// @}

/**
 * @name REG_58 register definitions
 * <table>
 * <caption id="REG_58_BF">REG_58 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>27:22 <td> wf_rxflt_bw_cbit1 <td>W <td>R <td>0x11
 * <tr><td>21:16 <td> wf_rxflt_bw_cbit2 <td>W <td>R <td>0x11
 * <tr><td>15:11 <td>    wf_rxflt_gbit1 <td>W <td>R <td>0x0
 * <tr><td>10:08 <td>    wf_rxflt_gbit2 <td>W <td>R <td>0x0
 * <tr><td>07:05 <td>  wf_rxflt_vcm_bit <td>R <td>R/W <td>0x5
 * <tr><td>04:00 <td> wf_rxflt_i_calbit <td>R <td>R/W <td>0x10
 * </table>
 *
 * @{
 */

/// Address of the REG_58 register
#define WLAN_RF_REG_58_ADDR   0x40344058
/// Offset of the REG_58 register from the base address
#define WLAN_RF_REG_58_OFFSET 0x00000058
/// Index of the REG_58 register
#define WLAN_RF_REG_58_INDEX  0x00000016
/// Reset value of the REG_58 register
#define WLAN_RF_REG_58_RESET  0x045100B0

/**
 * @brief Returns the current value of the REG_58 register.
 * The REG_58 register will be read and its value returned.
 * @return The current value of the REG_58 register.
 */
__INLINE uint32_t wlan_rf_reg_58_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_58_ADDR);
}

/**
 * @brief Sets the REG_58 register to a value.
 * The REG_58 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_58_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_58_ADDR, value);
}

// field definitions
/// WF_RXFLT_BW_CBIT_1 field mask
#define WLAN_RF_WF_RXFLT_BW_CBIT_1_MASK   ((uint32_t)0x0FC00000)
/// WF_RXFLT_BW_CBIT_1 field LSB position
#define WLAN_RF_WF_RXFLT_BW_CBIT_1_LSB    22
/// WF_RXFLT_BW_CBIT_1 field width
#define WLAN_RF_WF_RXFLT_BW_CBIT_1_WIDTH  ((uint32_t)0x00000006)
/// WF_RXFLT_BW_CBIT_2 field mask
#define WLAN_RF_WF_RXFLT_BW_CBIT_2_MASK   ((uint32_t)0x003F0000)
/// WF_RXFLT_BW_CBIT_2 field LSB position
#define WLAN_RF_WF_RXFLT_BW_CBIT_2_LSB    16
/// WF_RXFLT_BW_CBIT_2 field width
#define WLAN_RF_WF_RXFLT_BW_CBIT_2_WIDTH  ((uint32_t)0x00000006)
/// WF_RXFLT_GBIT_1 field mask
#define WLAN_RF_WF_RXFLT_GBIT_1_MASK      ((uint32_t)0x0000F800)
/// WF_RXFLT_GBIT_1 field LSB position
#define WLAN_RF_WF_RXFLT_GBIT_1_LSB       11
/// WF_RXFLT_GBIT_1 field width
#define WLAN_RF_WF_RXFLT_GBIT_1_WIDTH     ((uint32_t)0x00000005)
/// WF_RXFLT_GBIT_2 field mask
#define WLAN_RF_WF_RXFLT_GBIT_2_MASK      ((uint32_t)0x00000700)
/// WF_RXFLT_GBIT_2 field LSB position
#define WLAN_RF_WF_RXFLT_GBIT_2_LSB       8
/// WF_RXFLT_GBIT_2 field width
#define WLAN_RF_WF_RXFLT_GBIT_2_WIDTH     ((uint32_t)0x00000003)
/// WF_RXFLT_VCM_BIT field mask
#define WLAN_RF_WF_RXFLT_VCM_BIT_MASK     ((uint32_t)0x000000E0)
/// WF_RXFLT_VCM_BIT field LSB position
#define WLAN_RF_WF_RXFLT_VCM_BIT_LSB      5
/// WF_RXFLT_VCM_BIT field width
#define WLAN_RF_WF_RXFLT_VCM_BIT_WIDTH    ((uint32_t)0x00000003)
/// WF_RXFLT_I_CALBIT field mask
#define WLAN_RF_WF_RXFLT_I_CALBIT_MASK    ((uint32_t)0x0000001F)
/// WF_RXFLT_I_CALBIT field LSB position
#define WLAN_RF_WF_RXFLT_I_CALBIT_LSB     0
/// WF_RXFLT_I_CALBIT field width
#define WLAN_RF_WF_RXFLT_I_CALBIT_WIDTH   ((uint32_t)0x00000005)

/// WF_RXFLT_BW_CBIT_1 field reset value
#define WLAN_RF_WF_RXFLT_BW_CBIT_1_RST    0x11
/// WF_RXFLT_BW_CBIT_2 field reset value
#define WLAN_RF_WF_RXFLT_BW_CBIT_2_RST    0x11
/// WF_RXFLT_GBIT_1 field reset value
#define WLAN_RF_WF_RXFLT_GBIT_1_RST       0x0
/// WF_RXFLT_GBIT_2 field reset value
#define WLAN_RF_WF_RXFLT_GBIT_2_RST       0x0
/// WF_RXFLT_VCM_BIT field reset value
#define WLAN_RF_WF_RXFLT_VCM_BIT_RST      0x5
/// WF_RXFLT_I_CALBIT field reset value
#define WLAN_RF_WF_RXFLT_I_CALBIT_RST     0x10

/**
 * @brief Constructs a value for the REG_58 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrxfltvcmbit - The value to use for the wf_rxflt_vcm_bit field.
 * @param[in] wfrxflticalbit - The value to use for the wf_rxflt_i_calbit field.
 */
__INLINE void wlan_rf_reg_58_pack(uint8_t wfrxfltvcmbit, uint8_t wfrxflticalbit)
{
    REG_PL_WR(WLAN_RF_REG_58_ADDR,  ((uint32_t)wfrxfltvcmbit << 5) | ((uint32_t)wfrxflticalbit << 0));
}

/**
 * @brief Unpacks REG_58's fields from current value of the REG_58 register.
 *
 * Reads the REG_58 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrxfltbwcbit1 - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltbwcbit2 - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltgbit1 - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltgbit2 - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltvcmbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxflticalbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_58_unpack(uint8_t* wfrxfltbwcbit1, uint8_t* wfrxfltbwcbit2, uint8_t* wfrxfltgbit1, uint8_t* wfrxfltgbit2, uint8_t* wfrxfltvcmbit, uint8_t* wfrxflticalbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_58_ADDR);

    *wfrxfltbwcbit1 = (localVal & ((uint32_t)0x0FC00000)) >> 22;
    *wfrxfltbwcbit2 = (localVal & ((uint32_t)0x003F0000)) >> 16;
    *wfrxfltgbit1 = (localVal & ((uint32_t)0x0000F800)) >> 11;
    *wfrxfltgbit2 = (localVal & ((uint32_t)0x00000700)) >> 8;
    *wfrxfltvcmbit = (localVal & ((uint32_t)0x000000E0)) >> 5;
    *wfrxflticalbit = (localVal & ((uint32_t)0x0000001F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rxflt_bw_cbit1 field in the REG_58 register.
 *
 * The REG_58 register will be read and the wf_rxflt_bw_cbit1 field's value will be returned.
 *
 * @return The current value of the wf_rxflt_bw_cbit1 field in the REG_58 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_bw_cbit_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_58_ADDR);
    return ((localVal & ((uint32_t)0x0FC00000)) >> 22);
}

/**
 * @brief Returns the current value of the wf_rxflt_bw_cbit2 field in the REG_58 register.
 *
 * The REG_58 register will be read and the wf_rxflt_bw_cbit2 field's value will be returned.
 *
 * @return The current value of the wf_rxflt_bw_cbit2 field in the REG_58 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_bw_cbit_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_58_ADDR);
    return ((localVal & ((uint32_t)0x003F0000)) >> 16);
}

/**
 * @brief Returns the current value of the wf_rxflt_gbit1 field in the REG_58 register.
 *
 * The REG_58 register will be read and the wf_rxflt_gbit1 field's value will be returned.
 *
 * @return The current value of the wf_rxflt_gbit1 field in the REG_58 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_gbit_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_58_ADDR);
    return ((localVal & ((uint32_t)0x0000F800)) >> 11);
}

/**
 * @brief Returns the current value of the wf_rxflt_gbit2 field in the REG_58 register.
 *
 * The REG_58 register will be read and the wf_rxflt_gbit2 field's value will be returned.
 *
 * @return The current value of the wf_rxflt_gbit2 field in the REG_58 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_gbit_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_58_ADDR);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

/**
 * @brief Returns the current value of the wf_rxflt_vcm_bit field in the REG_58 register.
 *
 * The REG_58 register will be read and the wf_rxflt_vcm_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_vcm_bit field in the REG_58 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_vcm_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_58_ADDR);
    return ((localVal & ((uint32_t)0x000000E0)) >> 5);
}

/**
 * @brief Sets the wf_rxflt_vcm_bit field of the REG_58 register.
 *
 * The REG_58 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltvcmbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_vcm_bit_setf(uint8_t wfrxfltvcmbit)
{
    REG_PL_WR(WLAN_RF_REG_58_ADDR, (REG_PL_RD(WLAN_RF_REG_58_ADDR) & ~((uint32_t)0x000000E0)) | (((uint32_t)wfrxfltvcmbit << 5) & ((uint32_t)0x000000E0)));
}

/**
 * @brief Returns the current value of the wf_rxflt_i_calbit field in the REG_58 register.
 *
 * The REG_58 register will be read and the wf_rxflt_i_calbit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_i_calbit field in the REG_58 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_i_calbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_58_ADDR);
    return ((localVal & ((uint32_t)0x0000001F)) >> 0);
}

/**
 * @brief Sets the wf_rxflt_i_calbit field of the REG_58 register.
 *
 * The REG_58 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxflticalbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_i_calbit_setf(uint8_t wfrxflticalbit)
{
    REG_PL_WR(WLAN_RF_REG_58_ADDR, (REG_PL_RD(WLAN_RF_REG_58_ADDR) & ~((uint32_t)0x0000001F)) | (((uint32_t)wfrxflticalbit << 0) & ((uint32_t)0x0000001F)));
}

/// @}

/**
 * @name REG_5C register definitions
 * <table>
 * <caption id="REG_5C_BF">REG_5C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:25 <td> wf_rxflt_q_calbit <td>R <td>R/W <td>0x10
 * <tr><td>24:19 <td>  wf_rxflt_op_ibit <td>W <td>R <td>0x20
 * <tr><td>18:16 <td>wf_rxflt_op_cm_bit <td>W <td>R <td>0x4
 * <tr><td>15:12 <td>wf_rxflt_op_rm_bit <td>W <td>R <td>0xC
 * <tr><td>11:08 <td>wf_rxflt_op_rq_bit <td>W <td>R <td>0xC
 * <tr><td>07:04 <td>    wf_rxflt_insel <td>R <td>R/W <td>0x3
 * <tr><td>03 <td>    wf_adc_core_en <td>R <td>R/W <td>0
 * <tr><td>02 <td>     wf_adc_aux_en <td>R <td>R/W <td>0
 * <tr><td>01:00 <td>wf_adc_clk_sel_bit <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the REG_5C register
#define WLAN_RF_REG_5C_ADDR   0x4034405C
/// Offset of the REG_5C register from the base address
#define WLAN_RF_REG_5C_OFFSET 0x0000005C
/// Index of the REG_5C register
#define WLAN_RF_REG_5C_INDEX  0x00000017
/// Reset value of the REG_5C register
#define WLAN_RF_REG_5C_RESET  0x2104CC30

/**
 * @brief Returns the current value of the REG_5C register.
 * The REG_5C register will be read and its value returned.
 * @return The current value of the REG_5C register.
 */
__INLINE uint32_t wlan_rf_reg_5c_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_5C_ADDR);
}

/**
 * @brief Sets the REG_5C register to a value.
 * The REG_5C register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_5c_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_5C_ADDR, value);
}

// field definitions
/// WF_RXFLT_Q_CALBIT field mask
#define WLAN_RF_WF_RXFLT_Q_CALBIT_MASK    ((uint32_t)0x3E000000)
/// WF_RXFLT_Q_CALBIT field LSB position
#define WLAN_RF_WF_RXFLT_Q_CALBIT_LSB     25
/// WF_RXFLT_Q_CALBIT field width
#define WLAN_RF_WF_RXFLT_Q_CALBIT_WIDTH   ((uint32_t)0x00000005)
/// WF_RXFLT_OP_IBIT field mask
#define WLAN_RF_WF_RXFLT_OP_IBIT_MASK     ((uint32_t)0x01F80000)
/// WF_RXFLT_OP_IBIT field LSB position
#define WLAN_RF_WF_RXFLT_OP_IBIT_LSB      19
/// WF_RXFLT_OP_IBIT field width
#define WLAN_RF_WF_RXFLT_OP_IBIT_WIDTH    ((uint32_t)0x00000006)
/// WF_RXFLT_OP_CM_BIT field mask
#define WLAN_RF_WF_RXFLT_OP_CM_BIT_MASK   ((uint32_t)0x00070000)
/// WF_RXFLT_OP_CM_BIT field LSB position
#define WLAN_RF_WF_RXFLT_OP_CM_BIT_LSB    16
/// WF_RXFLT_OP_CM_BIT field width
#define WLAN_RF_WF_RXFLT_OP_CM_BIT_WIDTH  ((uint32_t)0x00000003)
/// WF_RXFLT_OP_RM_BIT field mask
#define WLAN_RF_WF_RXFLT_OP_RM_BIT_MASK   ((uint32_t)0x0000F000)
/// WF_RXFLT_OP_RM_BIT field LSB position
#define WLAN_RF_WF_RXFLT_OP_RM_BIT_LSB    12
/// WF_RXFLT_OP_RM_BIT field width
#define WLAN_RF_WF_RXFLT_OP_RM_BIT_WIDTH  ((uint32_t)0x00000004)
/// WF_RXFLT_OP_RQ_BIT field mask
#define WLAN_RF_WF_RXFLT_OP_RQ_BIT_MASK   ((uint32_t)0x00000F00)
/// WF_RXFLT_OP_RQ_BIT field LSB position
#define WLAN_RF_WF_RXFLT_OP_RQ_BIT_LSB    8
/// WF_RXFLT_OP_RQ_BIT field width
#define WLAN_RF_WF_RXFLT_OP_RQ_BIT_WIDTH  ((uint32_t)0x00000004)
/// WF_RXFLT_INSEL field mask
#define WLAN_RF_WF_RXFLT_INSEL_MASK       ((uint32_t)0x000000F0)
/// WF_RXFLT_INSEL field LSB position
#define WLAN_RF_WF_RXFLT_INSEL_LSB        4
/// WF_RXFLT_INSEL field width
#define WLAN_RF_WF_RXFLT_INSEL_WIDTH      ((uint32_t)0x00000004)
/// WF_ADC_CORE_EN field bit
#define WLAN_RF_WF_ADC_CORE_EN_BIT        ((uint32_t)0x00000008)
/// WF_ADC_CORE_EN field position
#define WLAN_RF_WF_ADC_CORE_EN_POS        3
/// WF_ADC_AUX_EN field bit
#define WLAN_RF_WF_ADC_AUX_EN_BIT         ((uint32_t)0x00000004)
/// WF_ADC_AUX_EN field position
#define WLAN_RF_WF_ADC_AUX_EN_POS         2
/// WF_ADC_CLK_SEL_BIT field mask
#define WLAN_RF_WF_ADC_CLK_SEL_BIT_MASK   ((uint32_t)0x00000003)
/// WF_ADC_CLK_SEL_BIT field LSB position
#define WLAN_RF_WF_ADC_CLK_SEL_BIT_LSB    0
/// WF_ADC_CLK_SEL_BIT field width
#define WLAN_RF_WF_ADC_CLK_SEL_BIT_WIDTH  ((uint32_t)0x00000002)

/// WF_RXFLT_Q_CALBIT field reset value
#define WLAN_RF_WF_RXFLT_Q_CALBIT_RST     0x10
/// WF_RXFLT_OP_IBIT field reset value
#define WLAN_RF_WF_RXFLT_OP_IBIT_RST      0x20
/// WF_RXFLT_OP_CM_BIT field reset value
#define WLAN_RF_WF_RXFLT_OP_CM_BIT_RST    0x4
/// WF_RXFLT_OP_RM_BIT field reset value
#define WLAN_RF_WF_RXFLT_OP_RM_BIT_RST    0xC
/// WF_RXFLT_OP_RQ_BIT field reset value
#define WLAN_RF_WF_RXFLT_OP_RQ_BIT_RST    0xC
/// WF_RXFLT_INSEL field reset value
#define WLAN_RF_WF_RXFLT_INSEL_RST        0x3
/// WF_ADC_CORE_EN field reset value
#define WLAN_RF_WF_ADC_CORE_EN_RST        0x0
/// WF_ADC_AUX_EN field reset value
#define WLAN_RF_WF_ADC_AUX_EN_RST         0x0
/// WF_ADC_CLK_SEL_BIT field reset value
#define WLAN_RF_WF_ADC_CLK_SEL_BIT_RST    0x0

/**
 * @brief Constructs a value for the REG_5C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrxfltqcalbit - The value to use for the wf_rxflt_q_calbit field.
 * @param[in] wfrxfltinsel - The value to use for the wf_rxflt_insel field.
 * @param[in] wfadccoreen - The value to use for the wf_adc_core_en field.
 * @param[in] wfadcauxen - The value to use for the wf_adc_aux_en field.
 * @param[in] wfadcclkselbit - The value to use for the wf_adc_clk_sel_bit field.
 */
__INLINE void wlan_rf_reg_5c_pack(uint8_t wfrxfltqcalbit, uint8_t wfrxfltinsel, uint8_t wfadccoreen, uint8_t wfadcauxen, uint8_t wfadcclkselbit)
{
    REG_PL_WR(WLAN_RF_REG_5C_ADDR,  ((uint32_t)wfrxfltqcalbit << 25) | ((uint32_t)wfrxfltinsel << 4) | ((uint32_t)wfadccoreen << 3) | ((uint32_t)wfadcauxen << 2) | ((uint32_t)wfadcclkselbit << 0));
}

/**
 * @brief Unpacks REG_5C's fields from current value of the REG_5C register.
 *
 * Reads the REG_5C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrxfltqcalbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltopibit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltopcmbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltoprmbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltoprqbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltinsel - Will be populated with the current value of this field from the register.
 * @param[out] wfadccoreen - Will be populated with the current value of this field from the register.
 * @param[out] wfadcauxen - Will be populated with the current value of this field from the register.
 * @param[out] wfadcclkselbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_5c_unpack(uint8_t* wfrxfltqcalbit, uint8_t* wfrxfltopibit, uint8_t* wfrxfltopcmbit, uint8_t* wfrxfltoprmbit, uint8_t* wfrxfltoprqbit, uint8_t* wfrxfltinsel, uint8_t* wfadccoreen, uint8_t* wfadcauxen, uint8_t* wfadcclkselbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);

    *wfrxfltqcalbit = (localVal & ((uint32_t)0x3E000000)) >> 25;
    *wfrxfltopibit = (localVal & ((uint32_t)0x01F80000)) >> 19;
    *wfrxfltopcmbit = (localVal & ((uint32_t)0x00070000)) >> 16;
    *wfrxfltoprmbit = (localVal & ((uint32_t)0x0000F000)) >> 12;
    *wfrxfltoprqbit = (localVal & ((uint32_t)0x00000F00)) >> 8;
    *wfrxfltinsel = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *wfadccoreen = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wfadcauxen = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wfadcclkselbit = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rxflt_q_calbit field in the REG_5C register.
 *
 * The REG_5C register will be read and the wf_rxflt_q_calbit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_q_calbit field in the REG_5C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_q_calbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);
    return ((localVal & ((uint32_t)0x3E000000)) >> 25);
}

/**
 * @brief Sets the wf_rxflt_q_calbit field of the REG_5C register.
 *
 * The REG_5C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltqcalbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_q_calbit_setf(uint8_t wfrxfltqcalbit)
{
    REG_PL_WR(WLAN_RF_REG_5C_ADDR, (REG_PL_RD(WLAN_RF_REG_5C_ADDR) & ~((uint32_t)0x3E000000)) | (((uint32_t)wfrxfltqcalbit << 25) & ((uint32_t)0x3E000000)));
}

/**
 * @brief Returns the current value of the wf_rxflt_op_ibit field in the REG_5C register.
 *
 * The REG_5C register will be read and the wf_rxflt_op_ibit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_op_ibit field in the REG_5C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_op_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);
    return ((localVal & ((uint32_t)0x01F80000)) >> 19);
}

/**
 * @brief Returns the current value of the wf_rxflt_op_cm_bit field in the REG_5C register.
 *
 * The REG_5C register will be read and the wf_rxflt_op_cm_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_op_cm_bit field in the REG_5C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_op_cm_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);
    return ((localVal & ((uint32_t)0x00070000)) >> 16);
}

/**
 * @brief Returns the current value of the wf_rxflt_op_rm_bit field in the REG_5C register.
 *
 * The REG_5C register will be read and the wf_rxflt_op_rm_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_op_rm_bit field in the REG_5C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_op_rm_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);
    return ((localVal & ((uint32_t)0x0000F000)) >> 12);
}

/**
 * @brief Returns the current value of the wf_rxflt_op_rq_bit field in the REG_5C register.
 *
 * The REG_5C register will be read and the wf_rxflt_op_rq_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_op_rq_bit field in the REG_5C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_op_rq_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);
    return ((localVal & ((uint32_t)0x00000F00)) >> 8);
}

/**
 * @brief Returns the current value of the wf_rxflt_insel field in the REG_5C register.
 *
 * The REG_5C register will be read and the wf_rxflt_insel field's value will be returned.
 *
 * @return The current value of the wf_rxflt_insel field in the REG_5C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_insel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Sets the wf_rxflt_insel field of the REG_5C register.
 *
 * The REG_5C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltinsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_insel_setf(uint8_t wfrxfltinsel)
{
    REG_PL_WR(WLAN_RF_REG_5C_ADDR, (REG_PL_RD(WLAN_RF_REG_5C_ADDR) & ~((uint32_t)0x000000F0)) | (((uint32_t)wfrxfltinsel << 4) & ((uint32_t)0x000000F0)));
}

/**
 * @brief Returns the current value of the wf_adc_core_en field in the REG_5C register.
 *
 * The REG_5C register will be read and the wf_adc_core_en field's value will be returned.
 *
 * @return The current value of the wf_adc_core_en field in the REG_5C register.
 */
__INLINE uint8_t wlan_rf_wf_adc_core_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wf_adc_core_en field of the REG_5C register.
 *
 * The REG_5C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadccoreen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_core_en_setf(uint8_t wfadccoreen)
{
    REG_PL_WR(WLAN_RF_REG_5C_ADDR, (REG_PL_RD(WLAN_RF_REG_5C_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wfadccoreen << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wf_adc_aux_en field in the REG_5C register.
 *
 * The REG_5C register will be read and the wf_adc_aux_en field's value will be returned.
 *
 * @return The current value of the wf_adc_aux_en field in the REG_5C register.
 */
__INLINE uint8_t wlan_rf_wf_adc_aux_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wf_adc_aux_en field of the REG_5C register.
 *
 * The REG_5C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcauxen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_aux_en_setf(uint8_t wfadcauxen)
{
    REG_PL_WR(WLAN_RF_REG_5C_ADDR, (REG_PL_RD(WLAN_RF_REG_5C_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wfadcauxen << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wf_adc_clk_sel_bit field in the REG_5C register.
 *
 * The REG_5C register will be read and the wf_adc_clk_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_adc_clk_sel_bit field in the REG_5C register.
 */
__INLINE uint8_t wlan_rf_wf_adc_clk_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_5C_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the wf_adc_clk_sel_bit field of the REG_5C register.
 *
 * The REG_5C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcclkselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_clk_sel_bit_setf(uint8_t wfadcclkselbit)
{
    REG_PL_WR(WLAN_RF_REG_5C_ADDR, (REG_PL_RD(WLAN_RF_REG_5C_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)wfadcclkselbit << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_60 register definitions
 * <table>
 * <caption id="REG_60_BF">REG_60 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:28 <td>   wf_adc_cmp_ibit <td>R <td>R/W <td>0x4
 * <tr><td>27 <td>  wf_adc_slice_sel <td>R <td>R/W <td>0
 * <tr><td>26 <td>    wf_adc_ti_mode <td>R <td>R/W <td>1
 * <tr><td>25 <td>wf_adc_clk_edge_sel <td>R <td>R/W <td>0
 * <tr><td>24:21 <td>    wf_adc_dly_bit <td>R <td>R/W <td>0x0
 * <tr><td>20:18 <td>   wf_adc_reg_vbit <td>R <td>R/W <td>0x5
 * <tr><td>17:14 <td>   wf_adc_reg_ibit <td>R <td>R/W <td>0x3
 * <tr><td>13:11 <td>   wf_adc_vcm_vbit <td>R <td>R/W <td>0x3
 * <tr><td>10:06 <td>  wf_adc_vref_ibit <td>R <td>R/W <td>0x8
 * <tr><td>05:01 <td>  wf_adc_vref_vbit <td>R <td>R/W <td>0x8
 * <tr><td>00 <td>    wf_adc_lp_mode <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_60 register
#define WLAN_RF_REG_60_ADDR   0x40344060
/// Offset of the REG_60 register from the base address
#define WLAN_RF_REG_60_OFFSET 0x00000060
/// Index of the REG_60 register
#define WLAN_RF_REG_60_INDEX  0x00000018
/// Reset value of the REG_60 register
#define WLAN_RF_REG_60_RESET  0x4414DA10

/**
 * @brief Returns the current value of the REG_60 register.
 * The REG_60 register will be read and its value returned.
 * @return The current value of the REG_60 register.
 */
__INLINE uint32_t wlan_rf_reg_60_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_60_ADDR);
}

/**
 * @brief Sets the REG_60 register to a value.
 * The REG_60 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_60_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, value);
}

// field definitions
/// WF_ADC_CMP_IBIT field mask
#define WLAN_RF_WF_ADC_CMP_IBIT_MASK       ((uint32_t)0xF0000000)
/// WF_ADC_CMP_IBIT field LSB position
#define WLAN_RF_WF_ADC_CMP_IBIT_LSB        28
/// WF_ADC_CMP_IBIT field width
#define WLAN_RF_WF_ADC_CMP_IBIT_WIDTH      ((uint32_t)0x00000004)
/// WF_ADC_SLICE_SEL field bit
#define WLAN_RF_WF_ADC_SLICE_SEL_BIT       ((uint32_t)0x08000000)
/// WF_ADC_SLICE_SEL field position
#define WLAN_RF_WF_ADC_SLICE_SEL_POS       27
/// WF_ADC_TI_MODE field bit
#define WLAN_RF_WF_ADC_TI_MODE_BIT         ((uint32_t)0x04000000)
/// WF_ADC_TI_MODE field position
#define WLAN_RF_WF_ADC_TI_MODE_POS         26
/// WF_ADC_CLK_EDGE_SEL field bit
#define WLAN_RF_WF_ADC_CLK_EDGE_SEL_BIT    ((uint32_t)0x02000000)
/// WF_ADC_CLK_EDGE_SEL field position
#define WLAN_RF_WF_ADC_CLK_EDGE_SEL_POS    25
/// WF_ADC_DLY_BIT field mask
#define WLAN_RF_WF_ADC_DLY_BIT_MASK        ((uint32_t)0x01E00000)
/// WF_ADC_DLY_BIT field LSB position
#define WLAN_RF_WF_ADC_DLY_BIT_LSB         21
/// WF_ADC_DLY_BIT field width
#define WLAN_RF_WF_ADC_DLY_BIT_WIDTH       ((uint32_t)0x00000004)
/// WF_ADC_REG_VBIT field mask
#define WLAN_RF_WF_ADC_REG_VBIT_MASK       ((uint32_t)0x001C0000)
/// WF_ADC_REG_VBIT field LSB position
#define WLAN_RF_WF_ADC_REG_VBIT_LSB        18
/// WF_ADC_REG_VBIT field width
#define WLAN_RF_WF_ADC_REG_VBIT_WIDTH      ((uint32_t)0x00000003)
/// WF_ADC_REG_IBIT field mask
#define WLAN_RF_WF_ADC_REG_IBIT_MASK       ((uint32_t)0x0003C000)
/// WF_ADC_REG_IBIT field LSB position
#define WLAN_RF_WF_ADC_REG_IBIT_LSB        14
/// WF_ADC_REG_IBIT field width
#define WLAN_RF_WF_ADC_REG_IBIT_WIDTH      ((uint32_t)0x00000004)
/// WF_ADC_VCM_VBIT field mask
#define WLAN_RF_WF_ADC_VCM_VBIT_MASK       ((uint32_t)0x00003800)
/// WF_ADC_VCM_VBIT field LSB position
#define WLAN_RF_WF_ADC_VCM_VBIT_LSB        11
/// WF_ADC_VCM_VBIT field width
#define WLAN_RF_WF_ADC_VCM_VBIT_WIDTH      ((uint32_t)0x00000003)
/// WF_ADC_VREF_IBIT field mask
#define WLAN_RF_WF_ADC_VREF_IBIT_MASK      ((uint32_t)0x000007C0)
/// WF_ADC_VREF_IBIT field LSB position
#define WLAN_RF_WF_ADC_VREF_IBIT_LSB       6
/// WF_ADC_VREF_IBIT field width
#define WLAN_RF_WF_ADC_VREF_IBIT_WIDTH     ((uint32_t)0x00000005)
/// WF_ADC_VREF_VBIT field mask
#define WLAN_RF_WF_ADC_VREF_VBIT_MASK      ((uint32_t)0x0000003E)
/// WF_ADC_VREF_VBIT field LSB position
#define WLAN_RF_WF_ADC_VREF_VBIT_LSB       1
/// WF_ADC_VREF_VBIT field width
#define WLAN_RF_WF_ADC_VREF_VBIT_WIDTH     ((uint32_t)0x00000005)
/// WF_ADC_LP_MODE field bit
#define WLAN_RF_WF_ADC_LP_MODE_BIT         ((uint32_t)0x00000001)
/// WF_ADC_LP_MODE field position
#define WLAN_RF_WF_ADC_LP_MODE_POS         0

/// WF_ADC_CMP_IBIT field reset value
#define WLAN_RF_WF_ADC_CMP_IBIT_RST        0x4
/// WF_ADC_SLICE_SEL field reset value
#define WLAN_RF_WF_ADC_SLICE_SEL_RST       0x0
/// WF_ADC_TI_MODE field reset value
#define WLAN_RF_WF_ADC_TI_MODE_RST         0x1
/// WF_ADC_CLK_EDGE_SEL field reset value
#define WLAN_RF_WF_ADC_CLK_EDGE_SEL_RST    0x0
/// WF_ADC_DLY_BIT field reset value
#define WLAN_RF_WF_ADC_DLY_BIT_RST         0x0
/// WF_ADC_REG_VBIT field reset value
#define WLAN_RF_WF_ADC_REG_VBIT_RST        0x5
/// WF_ADC_REG_IBIT field reset value
#define WLAN_RF_WF_ADC_REG_IBIT_RST        0x3
/// WF_ADC_VCM_VBIT field reset value
#define WLAN_RF_WF_ADC_VCM_VBIT_RST        0x3
/// WF_ADC_VREF_IBIT field reset value
#define WLAN_RF_WF_ADC_VREF_IBIT_RST       0x8
/// WF_ADC_VREF_VBIT field reset value
#define WLAN_RF_WF_ADC_VREF_VBIT_RST       0x8
/// WF_ADC_LP_MODE field reset value
#define WLAN_RF_WF_ADC_LP_MODE_RST         0x0

/**
 * @brief Constructs a value for the REG_60 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfadccmpibit - The value to use for the wf_adc_cmp_ibit field.
 * @param[in] wfadcslicesel - The value to use for the wf_adc_slice_sel field.
 * @param[in] wfadctimode - The value to use for the wf_adc_ti_mode field.
 * @param[in] wfadcclkedgesel - The value to use for the wf_adc_clk_edge_sel field.
 * @param[in] wfadcdlybit - The value to use for the wf_adc_dly_bit field.
 * @param[in] wfadcregvbit - The value to use for the wf_adc_reg_vbit field.
 * @param[in] wfadcregibit - The value to use for the wf_adc_reg_ibit field.
 * @param[in] wfadcvcmvbit - The value to use for the wf_adc_vcm_vbit field.
 * @param[in] wfadcvrefibit - The value to use for the wf_adc_vref_ibit field.
 * @param[in] wfadcvrefvbit - The value to use for the wf_adc_vref_vbit field.
 * @param[in] wfadclpmode - The value to use for the wf_adc_lp_mode field.
 */
__INLINE void wlan_rf_reg_60_pack(uint8_t wfadccmpibit, uint8_t wfadcslicesel, uint8_t wfadctimode, uint8_t wfadcclkedgesel, uint8_t wfadcdlybit, uint8_t wfadcregvbit, uint8_t wfadcregibit, uint8_t wfadcvcmvbit, uint8_t wfadcvrefibit, uint8_t wfadcvrefvbit, uint8_t wfadclpmode)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR,  ((uint32_t)wfadccmpibit << 28) | ((uint32_t)wfadcslicesel << 27) | ((uint32_t)wfadctimode << 26) | ((uint32_t)wfadcclkedgesel << 25) | ((uint32_t)wfadcdlybit << 21) | ((uint32_t)wfadcregvbit << 18) | ((uint32_t)wfadcregibit << 14) | ((uint32_t)wfadcvcmvbit << 11) | ((uint32_t)wfadcvrefibit << 6) | ((uint32_t)wfadcvrefvbit << 1) | ((uint32_t)wfadclpmode << 0));
}

/**
 * @brief Unpacks REG_60's fields from current value of the REG_60 register.
 *
 * Reads the REG_60 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfadccmpibit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcslicesel - Will be populated with the current value of this field from the register.
 * @param[out] wfadctimode - Will be populated with the current value of this field from the register.
 * @param[out] wfadcclkedgesel - Will be populated with the current value of this field from the register.
 * @param[out] wfadcdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcregibit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcvcmvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcvrefibit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcvrefvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfadclpmode - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_60_unpack(uint8_t* wfadccmpibit, uint8_t* wfadcslicesel, uint8_t* wfadctimode, uint8_t* wfadcclkedgesel, uint8_t* wfadcdlybit, uint8_t* wfadcregvbit, uint8_t* wfadcregibit, uint8_t* wfadcvcmvbit, uint8_t* wfadcvrefibit, uint8_t* wfadcvrefvbit, uint8_t* wfadclpmode)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);

    *wfadccmpibit = (localVal & ((uint32_t)0xF0000000)) >> 28;
    *wfadcslicesel = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfadctimode = (localVal & ((uint32_t)0x04000000)) >> 26;
    *wfadcclkedgesel = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wfadcdlybit = (localVal & ((uint32_t)0x01E00000)) >> 21;
    *wfadcregvbit = (localVal & ((uint32_t)0x001C0000)) >> 18;
    *wfadcregibit = (localVal & ((uint32_t)0x0003C000)) >> 14;
    *wfadcvcmvbit = (localVal & ((uint32_t)0x00003800)) >> 11;
    *wfadcvrefibit = (localVal & ((uint32_t)0x000007C0)) >> 6;
    *wfadcvrefvbit = (localVal & ((uint32_t)0x0000003E)) >> 1;
    *wfadclpmode = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_adc_cmp_ibit field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_cmp_ibit field's value will be returned.
 *
 * @return The current value of the wf_adc_cmp_ibit field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_cmp_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0xF0000000)) >> 28);
}

/**
 * @brief Sets the wf_adc_cmp_ibit field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadccmpibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_cmp_ibit_setf(uint8_t wfadccmpibit)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0xF0000000)) | (((uint32_t)wfadccmpibit << 28) & ((uint32_t)0xF0000000)));
}

/**
 * @brief Returns the current value of the wf_adc_slice_sel field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_slice_sel field's value will be returned.
 *
 * @return The current value of the wf_adc_slice_sel field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_slice_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_adc_slice_sel field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcslicesel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_slice_sel_setf(uint8_t wfadcslicesel)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wfadcslicesel << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_adc_ti_mode field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_ti_mode field's value will be returned.
 *
 * @return The current value of the wf_adc_ti_mode field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_ti_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the wf_adc_ti_mode field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadctimode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_ti_mode_setf(uint8_t wfadctimode)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)wfadctimode << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the wf_adc_clk_edge_sel field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_clk_edge_sel field's value will be returned.
 *
 * @return The current value of the wf_adc_clk_edge_sel field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_clk_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_adc_clk_edge_sel field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcclkedgesel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_clk_edge_sel_setf(uint8_t wfadcclkedgesel)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wfadcclkedgesel << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_adc_dly_bit field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_adc_dly_bit field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x01E00000)) >> 21);
}

/**
 * @brief Sets the wf_adc_dly_bit field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_dly_bit_setf(uint8_t wfadcdlybit)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x01E00000)) | (((uint32_t)wfadcdlybit << 21) & ((uint32_t)0x01E00000)));
}

/**
 * @brief Returns the current value of the wf_adc_reg_vbit field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_adc_reg_vbit field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x001C0000)) >> 18);
}

/**
 * @brief Sets the wf_adc_reg_vbit field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_reg_vbit_setf(uint8_t wfadcregvbit)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x001C0000)) | (((uint32_t)wfadcregvbit << 18) & ((uint32_t)0x001C0000)));
}

/**
 * @brief Returns the current value of the wf_adc_reg_ibit field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_reg_ibit field's value will be returned.
 *
 * @return The current value of the wf_adc_reg_ibit field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_reg_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x0003C000)) >> 14);
}

/**
 * @brief Sets the wf_adc_reg_ibit field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcregibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_reg_ibit_setf(uint8_t wfadcregibit)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x0003C000)) | (((uint32_t)wfadcregibit << 14) & ((uint32_t)0x0003C000)));
}

/**
 * @brief Returns the current value of the wf_adc_vcm_vbit field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_vcm_vbit field's value will be returned.
 *
 * @return The current value of the wf_adc_vcm_vbit field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_vcm_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x00003800)) >> 11);
}

/**
 * @brief Sets the wf_adc_vcm_vbit field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcvcmvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_vcm_vbit_setf(uint8_t wfadcvcmvbit)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x00003800)) | (((uint32_t)wfadcvcmvbit << 11) & ((uint32_t)0x00003800)));
}

/**
 * @brief Returns the current value of the wf_adc_vref_ibit field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_vref_ibit field's value will be returned.
 *
 * @return The current value of the wf_adc_vref_ibit field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_vref_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x000007C0)) >> 6);
}

/**
 * @brief Sets the wf_adc_vref_ibit field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcvrefibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_vref_ibit_setf(uint8_t wfadcvrefibit)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x000007C0)) | (((uint32_t)wfadcvrefibit << 6) & ((uint32_t)0x000007C0)));
}

/**
 * @brief Returns the current value of the wf_adc_vref_vbit field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_vref_vbit field's value will be returned.
 *
 * @return The current value of the wf_adc_vref_vbit field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_vref_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x0000003E)) >> 1);
}

/**
 * @brief Sets the wf_adc_vref_vbit field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcvrefvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_vref_vbit_setf(uint8_t wfadcvrefvbit)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x0000003E)) | (((uint32_t)wfadcvrefvbit << 1) & ((uint32_t)0x0000003E)));
}

/**
 * @brief Returns the current value of the wf_adc_lp_mode field in the REG_60 register.
 *
 * The REG_60 register will be read and the wf_adc_lp_mode field's value will be returned.
 *
 * @return The current value of the wf_adc_lp_mode field in the REG_60 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_lp_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_60_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_adc_lp_mode field of the REG_60 register.
 *
 * The REG_60 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadclpmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_lp_mode_setf(uint8_t wfadclpmode)
{
    REG_PL_WR(WLAN_RF_REG_60_ADDR, (REG_PL_RD(WLAN_RF_REG_60_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfadclpmode << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_64 register definitions
 * <table>
 * <caption id="REG_64_BF">REG_64 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:28 <td>   wf_adc_clk_cbit <td>R <td>R/W <td>0x8
 * <tr><td>27 <td>wf_pdadc_clk_edge_sel <td>R <td>R/W <td>0
 * <tr><td>26:23 <td>  wf_pdadc_dly_bit <td>R <td>R/W <td>0x2
 * <tr><td>22 <td>    wf_ts_hub_chop <td>R <td>R/W <td>0
 * <tr><td>21:18 <td> wf_ts_hub_chn_sel <td>R <td>R/W <td>0x1
 * <tr><td>17:16 <td>wf_ts_hub_vptat_vbit <td>R <td>R/W <td>0x2
 * <tr><td>15:14 <td>wf_ts_hub_vref_vbit <td>R <td>R/W <td>0x2
 * <tr><td>13:11 <td>  wf_rx_iq2gpio_en <td>R <td>R/W <td>0x0
 * <tr><td>10:07 <td>   wf_abb_rsvd_bit <td>R <td>R/W <td>0xC
 * <tr><td>06:03 <td>wf_abb_rsvd_read_bit <td>W <td>R <td>0x0
 * <tr><td>02 <td>wf_rfpll_sel_avdd12_sf <td>R <td>R/W <td>0
 * <tr><td>01 <td>  wf_rfpll_loop_en <td>R <td>R/W <td>1
 * <tr><td>00 <td> wf_rfpll_presc_en <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_64 register
#define WLAN_RF_REG_64_ADDR   0x40344064
/// Offset of the REG_64 register from the base address
#define WLAN_RF_REG_64_OFFSET 0x00000064
/// Index of the REG_64 register
#define WLAN_RF_REG_64_INDEX  0x00000019
/// Reset value of the REG_64 register
#define WLAN_RF_REG_64_RESET  0x81068603

/**
 * @brief Returns the current value of the REG_64 register.
 * The REG_64 register will be read and its value returned.
 * @return The current value of the REG_64 register.
 */
__INLINE uint32_t wlan_rf_reg_64_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_64_ADDR);
}

/**
 * @brief Sets the REG_64 register to a value.
 * The REG_64 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_64_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, value);
}

// field definitions
/// WF_ADC_CLK_CBIT field mask
#define WLAN_RF_WF_ADC_CLK_CBIT_MASK           ((uint32_t)0xF0000000)
/// WF_ADC_CLK_CBIT field LSB position
#define WLAN_RF_WF_ADC_CLK_CBIT_LSB            28
/// WF_ADC_CLK_CBIT field width
#define WLAN_RF_WF_ADC_CLK_CBIT_WIDTH          ((uint32_t)0x00000004)
/// WF_PDADC_CLK_EDGE_SEL field bit
#define WLAN_RF_WF_PDADC_CLK_EDGE_SEL_BIT      ((uint32_t)0x08000000)
/// WF_PDADC_CLK_EDGE_SEL field position
#define WLAN_RF_WF_PDADC_CLK_EDGE_SEL_POS      27
/// WF_PDADC_DLY_BIT field mask
#define WLAN_RF_WF_PDADC_DLY_BIT_MASK          ((uint32_t)0x07800000)
/// WF_PDADC_DLY_BIT field LSB position
#define WLAN_RF_WF_PDADC_DLY_BIT_LSB           23
/// WF_PDADC_DLY_BIT field width
#define WLAN_RF_WF_PDADC_DLY_BIT_WIDTH         ((uint32_t)0x00000004)
/// WF_TS_HUB_CHOP field bit
#define WLAN_RF_WF_TS_HUB_CHOP_BIT             ((uint32_t)0x00400000)
/// WF_TS_HUB_CHOP field position
#define WLAN_RF_WF_TS_HUB_CHOP_POS             22
/// WF_TS_HUB_CHN_SEL field mask
#define WLAN_RF_WF_TS_HUB_CHN_SEL_MASK         ((uint32_t)0x003C0000)
/// WF_TS_HUB_CHN_SEL field LSB position
#define WLAN_RF_WF_TS_HUB_CHN_SEL_LSB          18
/// WF_TS_HUB_CHN_SEL field width
#define WLAN_RF_WF_TS_HUB_CHN_SEL_WIDTH        ((uint32_t)0x00000004)
/// WF_TS_HUB_VPTAT_VBIT field mask
#define WLAN_RF_WF_TS_HUB_VPTAT_VBIT_MASK      ((uint32_t)0x00030000)
/// WF_TS_HUB_VPTAT_VBIT field LSB position
#define WLAN_RF_WF_TS_HUB_VPTAT_VBIT_LSB       16
/// WF_TS_HUB_VPTAT_VBIT field width
#define WLAN_RF_WF_TS_HUB_VPTAT_VBIT_WIDTH     ((uint32_t)0x00000002)
/// WF_TS_HUB_VREF_VBIT field mask
#define WLAN_RF_WF_TS_HUB_VREF_VBIT_MASK       ((uint32_t)0x0000C000)
/// WF_TS_HUB_VREF_VBIT field LSB position
#define WLAN_RF_WF_TS_HUB_VREF_VBIT_LSB        14
/// WF_TS_HUB_VREF_VBIT field width
#define WLAN_RF_WF_TS_HUB_VREF_VBIT_WIDTH      ((uint32_t)0x00000002)
/// WF_RX_IQ_2GPIO_EN field mask
#define WLAN_RF_WF_RX_IQ_2GPIO_EN_MASK         ((uint32_t)0x00003800)
/// WF_RX_IQ_2GPIO_EN field LSB position
#define WLAN_RF_WF_RX_IQ_2GPIO_EN_LSB          11
/// WF_RX_IQ_2GPIO_EN field width
#define WLAN_RF_WF_RX_IQ_2GPIO_EN_WIDTH        ((uint32_t)0x00000003)
/// WF_ABB_RSVD_BIT field mask
#define WLAN_RF_WF_ABB_RSVD_BIT_MASK           ((uint32_t)0x00000780)
/// WF_ABB_RSVD_BIT field LSB position
#define WLAN_RF_WF_ABB_RSVD_BIT_LSB            7
/// WF_ABB_RSVD_BIT field width
#define WLAN_RF_WF_ABB_RSVD_BIT_WIDTH          ((uint32_t)0x00000004)
/// WF_ABB_RSVD_READ_BIT field mask
#define WLAN_RF_WF_ABB_RSVD_READ_BIT_MASK      ((uint32_t)0x00000078)
/// WF_ABB_RSVD_READ_BIT field LSB position
#define WLAN_RF_WF_ABB_RSVD_READ_BIT_LSB       3
/// WF_ABB_RSVD_READ_BIT field width
#define WLAN_RF_WF_ABB_RSVD_READ_BIT_WIDTH     ((uint32_t)0x00000004)
/// WF_RFPLL_SEL_AVDD_12_SF field bit
#define WLAN_RF_WF_RFPLL_SEL_AVDD_12_SF_BIT    ((uint32_t)0x00000004)
/// WF_RFPLL_SEL_AVDD_12_SF field position
#define WLAN_RF_WF_RFPLL_SEL_AVDD_12_SF_POS    2
/// WF_RFPLL_LOOP_EN field bit
#define WLAN_RF_WF_RFPLL_LOOP_EN_BIT           ((uint32_t)0x00000002)
/// WF_RFPLL_LOOP_EN field position
#define WLAN_RF_WF_RFPLL_LOOP_EN_POS           1
/// WF_RFPLL_PRESC_EN field bit
#define WLAN_RF_WF_RFPLL_PRESC_EN_BIT          ((uint32_t)0x00000001)
/// WF_RFPLL_PRESC_EN field position
#define WLAN_RF_WF_RFPLL_PRESC_EN_POS          0

/// WF_ADC_CLK_CBIT field reset value
#define WLAN_RF_WF_ADC_CLK_CBIT_RST            0x8
/// WF_PDADC_CLK_EDGE_SEL field reset value
#define WLAN_RF_WF_PDADC_CLK_EDGE_SEL_RST      0x0
/// WF_PDADC_DLY_BIT field reset value
#define WLAN_RF_WF_PDADC_DLY_BIT_RST           0x2
/// WF_TS_HUB_CHOP field reset value
#define WLAN_RF_WF_TS_HUB_CHOP_RST             0x0
/// WF_TS_HUB_CHN_SEL field reset value
#define WLAN_RF_WF_TS_HUB_CHN_SEL_RST          0x1
/// WF_TS_HUB_VPTAT_VBIT field reset value
#define WLAN_RF_WF_TS_HUB_VPTAT_VBIT_RST       0x2
/// WF_TS_HUB_VREF_VBIT field reset value
#define WLAN_RF_WF_TS_HUB_VREF_VBIT_RST        0x2
/// WF_RX_IQ_2GPIO_EN field reset value
#define WLAN_RF_WF_RX_IQ_2GPIO_EN_RST          0x0
/// WF_ABB_RSVD_BIT field reset value
#define WLAN_RF_WF_ABB_RSVD_BIT_RST            0xC
/// WF_ABB_RSVD_READ_BIT field reset value
#define WLAN_RF_WF_ABB_RSVD_READ_BIT_RST       0x0
/// WF_RFPLL_SEL_AVDD_12_SF field reset value
#define WLAN_RF_WF_RFPLL_SEL_AVDD_12_SF_RST    0x0
/// WF_RFPLL_LOOP_EN field reset value
#define WLAN_RF_WF_RFPLL_LOOP_EN_RST           0x1
/// WF_RFPLL_PRESC_EN field reset value
#define WLAN_RF_WF_RFPLL_PRESC_EN_RST          0x1

/**
 * @brief Constructs a value for the REG_64 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfadcclkcbit - The value to use for the wf_adc_clk_cbit field.
 * @param[in] wfpdadcclkedgesel - The value to use for the wf_pdadc_clk_edge_sel field.
 * @param[in] wfpdadcdlybit - The value to use for the wf_pdadc_dly_bit field.
 * @param[in] wftshubchop - The value to use for the wf_ts_hub_chop field.
 * @param[in] wftshubchnsel - The value to use for the wf_ts_hub_chn_sel field.
 * @param[in] wftshubvptatvbit - The value to use for the wf_ts_hub_vptat_vbit field.
 * @param[in] wftshubvrefvbit - The value to use for the wf_ts_hub_vref_vbit field.
 * @param[in] wfrxiq2gpioen - The value to use for the wf_rx_iq2gpio_en field.
 * @param[in] wfabbrsvdbit - The value to use for the wf_abb_rsvd_bit field.
 * @param[in] wfrfpllselavdd12sf - The value to use for the wf_rfpll_sel_avdd12_sf field.
 * @param[in] wfrfpllloopen - The value to use for the wf_rfpll_loop_en field.
 * @param[in] wfrfpllprescen - The value to use for the wf_rfpll_presc_en field.
 */
__INLINE void wlan_rf_reg_64_pack(uint8_t wfadcclkcbit, uint8_t wfpdadcclkedgesel, uint8_t wfpdadcdlybit, uint8_t wftshubchop, uint8_t wftshubchnsel, uint8_t wftshubvptatvbit, uint8_t wftshubvrefvbit, uint8_t wfrxiq2gpioen, uint8_t wfabbrsvdbit, uint8_t wfrfpllselavdd12sf, uint8_t wfrfpllloopen, uint8_t wfrfpllprescen)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR,  ((uint32_t)wfadcclkcbit << 28) | ((uint32_t)wfpdadcclkedgesel << 27) | ((uint32_t)wfpdadcdlybit << 23) | ((uint32_t)wftshubchop << 22) | ((uint32_t)wftshubchnsel << 18) | ((uint32_t)wftshubvptatvbit << 16) | ((uint32_t)wftshubvrefvbit << 14) | ((uint32_t)wfrxiq2gpioen << 11) | ((uint32_t)wfabbrsvdbit << 7) | ((uint32_t)wfrfpllselavdd12sf << 2) | ((uint32_t)wfrfpllloopen << 1) | ((uint32_t)wfrfpllprescen << 0));
}

/**
 * @brief Unpacks REG_64's fields from current value of the REG_64 register.
 *
 * Reads the REG_64 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfadcclkcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpdadcclkedgesel - Will be populated with the current value of this field from the register.
 * @param[out] wfpdadcdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wftshubchop - Will be populated with the current value of this field from the register.
 * @param[out] wftshubchnsel - Will be populated with the current value of this field from the register.
 * @param[out] wftshubvptatvbit - Will be populated with the current value of this field from the register.
 * @param[out] wftshubvrefvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxiq2gpioen - Will be populated with the current value of this field from the register.
 * @param[out] wfabbrsvdbit - Will be populated with the current value of this field from the register.
 * @param[out] wfabbrsvdreadbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllselavdd12sf - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllloopen - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllprescen - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_64_unpack(uint8_t* wfadcclkcbit, uint8_t* wfpdadcclkedgesel, uint8_t* wfpdadcdlybit, uint8_t* wftshubchop, uint8_t* wftshubchnsel, uint8_t* wftshubvptatvbit, uint8_t* wftshubvrefvbit, uint8_t* wfrxiq2gpioen, uint8_t* wfabbrsvdbit, uint8_t* wfabbrsvdreadbit, uint8_t* wfrfpllselavdd12sf, uint8_t* wfrfpllloopen, uint8_t* wfrfpllprescen)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);

    *wfadcclkcbit = (localVal & ((uint32_t)0xF0000000)) >> 28;
    *wfpdadcclkedgesel = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfpdadcdlybit = (localVal & ((uint32_t)0x07800000)) >> 23;
    *wftshubchop = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wftshubchnsel = (localVal & ((uint32_t)0x003C0000)) >> 18;
    *wftshubvptatvbit = (localVal & ((uint32_t)0x00030000)) >> 16;
    *wftshubvrefvbit = (localVal & ((uint32_t)0x0000C000)) >> 14;
    *wfrxiq2gpioen = (localVal & ((uint32_t)0x00003800)) >> 11;
    *wfabbrsvdbit = (localVal & ((uint32_t)0x00000780)) >> 7;
    *wfabbrsvdreadbit = (localVal & ((uint32_t)0x00000078)) >> 3;
    *wfrfpllselavdd12sf = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wfrfpllloopen = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfrfpllprescen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_adc_clk_cbit field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_adc_clk_cbit field's value will be returned.
 *
 * @return The current value of the wf_adc_clk_cbit field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_clk_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0xF0000000)) >> 28);
}

/**
 * @brief Sets the wf_adc_clk_cbit field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcclkcbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_clk_cbit_setf(uint8_t wfadcclkcbit)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0xF0000000)) | (((uint32_t)wfadcclkcbit << 28) & ((uint32_t)0xF0000000)));
}

/**
 * @brief Returns the current value of the wf_pdadc_clk_edge_sel field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_pdadc_clk_edge_sel field's value will be returned.
 *
 * @return The current value of the wf_pdadc_clk_edge_sel field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_pdadc_clk_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_pdadc_clk_edge_sel field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpdadcclkedgesel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pdadc_clk_edge_sel_setf(uint8_t wfpdadcclkedgesel)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wfpdadcclkedgesel << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_pdadc_dly_bit field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_pdadc_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_pdadc_dly_bit field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_pdadc_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x07800000)) >> 23);
}

/**
 * @brief Sets the wf_pdadc_dly_bit field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpdadcdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pdadc_dly_bit_setf(uint8_t wfpdadcdlybit)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x07800000)) | (((uint32_t)wfpdadcdlybit << 23) & ((uint32_t)0x07800000)));
}

/**
 * @brief Returns the current value of the wf_ts_hub_chop field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_ts_hub_chop field's value will be returned.
 *
 * @return The current value of the wf_ts_hub_chop field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_ts_hub_chop_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the wf_ts_hub_chop field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftshubchop - The value to set the field to.
 */
__INLINE void wlan_rf_wf_ts_hub_chop_setf(uint8_t wftshubchop)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)wftshubchop << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the wf_ts_hub_chn_sel field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_ts_hub_chn_sel field's value will be returned.
 *
 * @return The current value of the wf_ts_hub_chn_sel field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_ts_hub_chn_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x003C0000)) >> 18);
}

/**
 * @brief Sets the wf_ts_hub_chn_sel field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftshubchnsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_ts_hub_chn_sel_setf(uint8_t wftshubchnsel)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x003C0000)) | (((uint32_t)wftshubchnsel << 18) & ((uint32_t)0x003C0000)));
}

/**
 * @brief Returns the current value of the wf_ts_hub_vptat_vbit field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_ts_hub_vptat_vbit field's value will be returned.
 *
 * @return The current value of the wf_ts_hub_vptat_vbit field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_ts_hub_vptat_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

/**
 * @brief Sets the wf_ts_hub_vptat_vbit field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftshubvptatvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_ts_hub_vptat_vbit_setf(uint8_t wftshubvptatvbit)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x00030000)) | (((uint32_t)wftshubvptatvbit << 16) & ((uint32_t)0x00030000)));
}

/**
 * @brief Returns the current value of the wf_ts_hub_vref_vbit field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_ts_hub_vref_vbit field's value will be returned.
 *
 * @return The current value of the wf_ts_hub_vref_vbit field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_ts_hub_vref_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x0000C000)) >> 14);
}

/**
 * @brief Sets the wf_ts_hub_vref_vbit field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftshubvrefvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_ts_hub_vref_vbit_setf(uint8_t wftshubvrefvbit)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x0000C000)) | (((uint32_t)wftshubvrefvbit << 14) & ((uint32_t)0x0000C000)));
}

/**
 * @brief Returns the current value of the wf_rx_iq2gpio_en field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_rx_iq2gpio_en field's value will be returned.
 *
 * @return The current value of the wf_rx_iq2gpio_en field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_rx_iq_2gpio_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x00003800)) >> 11);
}

/**
 * @brief Sets the wf_rx_iq2gpio_en field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxiq2gpioen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rx_iq_2gpio_en_setf(uint8_t wfrxiq2gpioen)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x00003800)) | (((uint32_t)wfrxiq2gpioen << 11) & ((uint32_t)0x00003800)));
}

/**
 * @brief Returns the current value of the wf_abb_rsvd_bit field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_abb_rsvd_bit field's value will be returned.
 *
 * @return The current value of the wf_abb_rsvd_bit field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_abb_rsvd_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x00000780)) >> 7);
}

/**
 * @brief Sets the wf_abb_rsvd_bit field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfabbrsvdbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_abb_rsvd_bit_setf(uint8_t wfabbrsvdbit)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x00000780)) | (((uint32_t)wfabbrsvdbit << 7) & ((uint32_t)0x00000780)));
}

/**
 * @brief Returns the current value of the wf_abb_rsvd_read_bit field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_abb_rsvd_read_bit field's value will be returned.
 *
 * @return The current value of the wf_abb_rsvd_read_bit field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_abb_rsvd_read_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x00000078)) >> 3);
}

/**
 * @brief Returns the current value of the wf_rfpll_sel_avdd12_sf field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_rfpll_sel_avdd12_sf field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sel_avdd12_sf field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sel_avdd_12_sf_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wf_rfpll_sel_avdd12_sf field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllselavdd12sf - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_sel_avdd_12_sf_setf(uint8_t wfrfpllselavdd12sf)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wfrfpllselavdd12sf << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wf_rfpll_loop_en field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_rfpll_loop_en field's value will be returned.
 *
 * @return The current value of the wf_rfpll_loop_en field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_loop_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_rfpll_loop_en field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllloopen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_loop_en_setf(uint8_t wfrfpllloopen)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfrfpllloopen << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_rfpll_presc_en field in the REG_64 register.
 *
 * The REG_64 register will be read and the wf_rfpll_presc_en field's value will be returned.
 *
 * @return The current value of the wf_rfpll_presc_en field in the REG_64 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_presc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_64_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_rfpll_presc_en field of the REG_64 register.
 *
 * The REG_64 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllprescen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_presc_en_setf(uint8_t wfrfpllprescen)
{
    REG_PL_WR(WLAN_RF_REG_64_ADDR, (REG_PL_RD(WLAN_RF_REG_64_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfrfpllprescen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_68 register definitions
 * <table>
 * <caption id="REG_68_BF">REG_68 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:26 <td>wf_rfpll_pdt_reg_vbit <td>R <td>R/W <td>0x8
 * <tr><td>25:24 <td>wf_rfpll_dvdd_ldo_vbit <td>R <td>R/W <td>0x2
 * <tr><td>23:20 <td>wf_rfpll_presc_reg_vbit <td>R <td>R/W <td>0x8
 * <tr><td>19 <td> wf_rfpll_fref_sel <td>R <td>R/W <td>1
 * <tr><td>18 <td>wf_rfpll_frefx2_en <td>R <td>R/W <td>0
 * <tr><td>17 <td>wf_rfpll_loop_mode <td>R <td>R/W <td>0
 * <tr><td>16:15 <td>wf_rfpll_sinc_mode <td>R <td>R/W <td>0x1
 * <tr><td>14 <td>wf_rfpll_lpf_notch_bypass <td>R <td>R/W <td>0
 * <tr><td>13:10 <td> wf_rfpll_vco_gbit <td>R <td>R/W <td>0xF
 * <tr><td>09:08 <td>  wf_rfpll_cp_rbit <td>R <td>R/W <td>0x0
 * <tr><td>07:04 <td>  wf_rfpll_cp_ibit <td>R <td>R/W <td>0x8
 * <tr><td>03:02 <td> wf_rfpll_lpf_rbit <td>R <td>R/W <td>0x1
 * <tr><td>01:00 <td> wf_rfpll_lpf_gbit <td>R <td>R/W <td>0x3
 * </table>
 *
 * @{
 */

/// Address of the REG_68 register
#define WLAN_RF_REG_68_ADDR   0x40344068
/// Offset of the REG_68 register from the base address
#define WLAN_RF_REG_68_OFFSET 0x00000068
/// Index of the REG_68 register
#define WLAN_RF_REG_68_INDEX  0x0000001A
/// Reset value of the REG_68 register
#define WLAN_RF_REG_68_RESET  0x2288BC87

/**
 * @brief Returns the current value of the REG_68 register.
 * The REG_68 register will be read and its value returned.
 * @return The current value of the REG_68 register.
 */
__INLINE uint32_t wlan_rf_reg_68_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_68_ADDR);
}

/**
 * @brief Sets the REG_68 register to a value.
 * The REG_68 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_68_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, value);
}

// field definitions
/// WF_RFPLL_PDT_REG_VBIT field mask
#define WLAN_RF_WF_RFPLL_PDT_REG_VBIT_MASK       ((uint32_t)0x3C000000)
/// WF_RFPLL_PDT_REG_VBIT field LSB position
#define WLAN_RF_WF_RFPLL_PDT_REG_VBIT_LSB        26
/// WF_RFPLL_PDT_REG_VBIT field width
#define WLAN_RF_WF_RFPLL_PDT_REG_VBIT_WIDTH      ((uint32_t)0x00000004)
/// WF_RFPLL_DVDD_LDO_VBIT field mask
#define WLAN_RF_WF_RFPLL_DVDD_LDO_VBIT_MASK      ((uint32_t)0x03000000)
/// WF_RFPLL_DVDD_LDO_VBIT field LSB position
#define WLAN_RF_WF_RFPLL_DVDD_LDO_VBIT_LSB       24
/// WF_RFPLL_DVDD_LDO_VBIT field width
#define WLAN_RF_WF_RFPLL_DVDD_LDO_VBIT_WIDTH     ((uint32_t)0x00000002)
/// WF_RFPLL_PRESC_REG_VBIT field mask
#define WLAN_RF_WF_RFPLL_PRESC_REG_VBIT_MASK     ((uint32_t)0x00F00000)
/// WF_RFPLL_PRESC_REG_VBIT field LSB position
#define WLAN_RF_WF_RFPLL_PRESC_REG_VBIT_LSB      20
/// WF_RFPLL_PRESC_REG_VBIT field width
#define WLAN_RF_WF_RFPLL_PRESC_REG_VBIT_WIDTH    ((uint32_t)0x00000004)
/// WF_RFPLL_FREF_SEL field bit
#define WLAN_RF_WF_RFPLL_FREF_SEL_BIT            ((uint32_t)0x00080000)
/// WF_RFPLL_FREF_SEL field position
#define WLAN_RF_WF_RFPLL_FREF_SEL_POS            19
/// WF_RFPLL_FREFX_2_EN field bit
#define WLAN_RF_WF_RFPLL_FREFX_2_EN_BIT          ((uint32_t)0x00040000)
/// WF_RFPLL_FREFX_2_EN field position
#define WLAN_RF_WF_RFPLL_FREFX_2_EN_POS          18
/// WF_RFPLL_LOOP_MODE field bit
#define WLAN_RF_WF_RFPLL_LOOP_MODE_BIT           ((uint32_t)0x00020000)
/// WF_RFPLL_LOOP_MODE field position
#define WLAN_RF_WF_RFPLL_LOOP_MODE_POS           17
/// WF_RFPLL_SINC_MODE field mask
#define WLAN_RF_WF_RFPLL_SINC_MODE_MASK          ((uint32_t)0x00018000)
/// WF_RFPLL_SINC_MODE field LSB position
#define WLAN_RF_WF_RFPLL_SINC_MODE_LSB           15
/// WF_RFPLL_SINC_MODE field width
#define WLAN_RF_WF_RFPLL_SINC_MODE_WIDTH         ((uint32_t)0x00000002)
/// WF_RFPLL_LPF_NOTCH_BYPASS field bit
#define WLAN_RF_WF_RFPLL_LPF_NOTCH_BYPASS_BIT    ((uint32_t)0x00004000)
/// WF_RFPLL_LPF_NOTCH_BYPASS field position
#define WLAN_RF_WF_RFPLL_LPF_NOTCH_BYPASS_POS    14
/// WF_RFPLL_VCO_GBIT field mask
#define WLAN_RF_WF_RFPLL_VCO_GBIT_MASK           ((uint32_t)0x00003C00)
/// WF_RFPLL_VCO_GBIT field LSB position
#define WLAN_RF_WF_RFPLL_VCO_GBIT_LSB            10
/// WF_RFPLL_VCO_GBIT field width
#define WLAN_RF_WF_RFPLL_VCO_GBIT_WIDTH          ((uint32_t)0x00000004)
/// WF_RFPLL_CP_RBIT field mask
#define WLAN_RF_WF_RFPLL_CP_RBIT_MASK            ((uint32_t)0x00000300)
/// WF_RFPLL_CP_RBIT field LSB position
#define WLAN_RF_WF_RFPLL_CP_RBIT_LSB             8
/// WF_RFPLL_CP_RBIT field width
#define WLAN_RF_WF_RFPLL_CP_RBIT_WIDTH           ((uint32_t)0x00000002)
/// WF_RFPLL_CP_IBIT field mask
#define WLAN_RF_WF_RFPLL_CP_IBIT_MASK            ((uint32_t)0x000000F0)
/// WF_RFPLL_CP_IBIT field LSB position
#define WLAN_RF_WF_RFPLL_CP_IBIT_LSB             4
/// WF_RFPLL_CP_IBIT field width
#define WLAN_RF_WF_RFPLL_CP_IBIT_WIDTH           ((uint32_t)0x00000004)
/// WF_RFPLL_LPF_RBIT field mask
#define WLAN_RF_WF_RFPLL_LPF_RBIT_MASK           ((uint32_t)0x0000000C)
/// WF_RFPLL_LPF_RBIT field LSB position
#define WLAN_RF_WF_RFPLL_LPF_RBIT_LSB            2
/// WF_RFPLL_LPF_RBIT field width
#define WLAN_RF_WF_RFPLL_LPF_RBIT_WIDTH          ((uint32_t)0x00000002)
/// WF_RFPLL_LPF_GBIT field mask
#define WLAN_RF_WF_RFPLL_LPF_GBIT_MASK           ((uint32_t)0x00000003)
/// WF_RFPLL_LPF_GBIT field LSB position
#define WLAN_RF_WF_RFPLL_LPF_GBIT_LSB            0
/// WF_RFPLL_LPF_GBIT field width
#define WLAN_RF_WF_RFPLL_LPF_GBIT_WIDTH          ((uint32_t)0x00000002)

/// WF_RFPLL_PDT_REG_VBIT field reset value
#define WLAN_RF_WF_RFPLL_PDT_REG_VBIT_RST        0x8
/// WF_RFPLL_DVDD_LDO_VBIT field reset value
#define WLAN_RF_WF_RFPLL_DVDD_LDO_VBIT_RST       0x2
/// WF_RFPLL_PRESC_REG_VBIT field reset value
#define WLAN_RF_WF_RFPLL_PRESC_REG_VBIT_RST      0x8
/// WF_RFPLL_FREF_SEL field reset value
#define WLAN_RF_WF_RFPLL_FREF_SEL_RST            0x1
/// WF_RFPLL_FREFX_2_EN field reset value
#define WLAN_RF_WF_RFPLL_FREFX_2_EN_RST          0x0
/// WF_RFPLL_LOOP_MODE field reset value
#define WLAN_RF_WF_RFPLL_LOOP_MODE_RST           0x0
/// WF_RFPLL_SINC_MODE field reset value
#define WLAN_RF_WF_RFPLL_SINC_MODE_RST           0x1
/// WF_RFPLL_LPF_NOTCH_BYPASS field reset value
#define WLAN_RF_WF_RFPLL_LPF_NOTCH_BYPASS_RST    0x0
/// WF_RFPLL_VCO_GBIT field reset value
#define WLAN_RF_WF_RFPLL_VCO_GBIT_RST            0xF
/// WF_RFPLL_CP_RBIT field reset value
#define WLAN_RF_WF_RFPLL_CP_RBIT_RST             0x0
/// WF_RFPLL_CP_IBIT field reset value
#define WLAN_RF_WF_RFPLL_CP_IBIT_RST             0x8
/// WF_RFPLL_LPF_RBIT field reset value
#define WLAN_RF_WF_RFPLL_LPF_RBIT_RST            0x1
/// WF_RFPLL_LPF_GBIT field reset value
#define WLAN_RF_WF_RFPLL_LPF_GBIT_RST            0x3

/**
 * @brief Constructs a value for the REG_68 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrfpllpdtregvbit - The value to use for the wf_rfpll_pdt_reg_vbit field.
 * @param[in] wfrfplldvddldovbit - The value to use for the wf_rfpll_dvdd_ldo_vbit field.
 * @param[in] wfrfpllprescregvbit - The value to use for the wf_rfpll_presc_reg_vbit field.
 * @param[in] wfrfpllfrefsel - The value to use for the wf_rfpll_fref_sel field.
 * @param[in] wfrfpllfrefx2en - The value to use for the wf_rfpll_frefx2_en field.
 * @param[in] wfrfpllloopmode - The value to use for the wf_rfpll_loop_mode field.
 * @param[in] wfrfpllsincmode - The value to use for the wf_rfpll_sinc_mode field.
 * @param[in] wfrfplllpfnotchbypass - The value to use for the wf_rfpll_lpf_notch_bypass field.
 * @param[in] wfrfpllvcogbit - The value to use for the wf_rfpll_vco_gbit field.
 * @param[in] wfrfpllcprbit - The value to use for the wf_rfpll_cp_rbit field.
 * @param[in] wfrfpllcpibit - The value to use for the wf_rfpll_cp_ibit field.
 * @param[in] wfrfplllpfrbit - The value to use for the wf_rfpll_lpf_rbit field.
 * @param[in] wfrfplllpfgbit - The value to use for the wf_rfpll_lpf_gbit field.
 */
__INLINE void wlan_rf_reg_68_pack(uint8_t wfrfpllpdtregvbit, uint8_t wfrfplldvddldovbit, uint8_t wfrfpllprescregvbit, uint8_t wfrfpllfrefsel, uint8_t wfrfpllfrefx2en, uint8_t wfrfpllloopmode, uint8_t wfrfpllsincmode, uint8_t wfrfplllpfnotchbypass, uint8_t wfrfpllvcogbit, uint8_t wfrfpllcprbit, uint8_t wfrfpllcpibit, uint8_t wfrfplllpfrbit, uint8_t wfrfplllpfgbit)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR,  ((uint32_t)wfrfpllpdtregvbit << 26) | ((uint32_t)wfrfplldvddldovbit << 24) | ((uint32_t)wfrfpllprescregvbit << 20) | ((uint32_t)wfrfpllfrefsel << 19) | ((uint32_t)wfrfpllfrefx2en << 18) | ((uint32_t)wfrfpllloopmode << 17) | ((uint32_t)wfrfpllsincmode << 15) | ((uint32_t)wfrfplllpfnotchbypass << 14) | ((uint32_t)wfrfpllvcogbit << 10) | ((uint32_t)wfrfpllcprbit << 8) | ((uint32_t)wfrfpllcpibit << 4) | ((uint32_t)wfrfplllpfrbit << 2) | ((uint32_t)wfrfplllpfgbit << 0));
}

/**
 * @brief Unpacks REG_68's fields from current value of the REG_68 register.
 *
 * Reads the REG_68 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrfpllpdtregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplldvddldovbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllprescregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllfrefsel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllfrefx2en - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllloopmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllsincmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplllpfnotchbypass - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllvcogbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllcprbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllcpibit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplllpfrbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplllpfgbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_68_unpack(uint8_t* wfrfpllpdtregvbit, uint8_t* wfrfplldvddldovbit, uint8_t* wfrfpllprescregvbit, uint8_t* wfrfpllfrefsel, uint8_t* wfrfpllfrefx2en, uint8_t* wfrfpllloopmode, uint8_t* wfrfpllsincmode, uint8_t* wfrfplllpfnotchbypass, uint8_t* wfrfpllvcogbit, uint8_t* wfrfpllcprbit, uint8_t* wfrfpllcpibit, uint8_t* wfrfplllpfrbit, uint8_t* wfrfplllpfgbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);

    *wfrfpllpdtregvbit = (localVal & ((uint32_t)0x3C000000)) >> 26;
    *wfrfplldvddldovbit = (localVal & ((uint32_t)0x03000000)) >> 24;
    *wfrfpllprescregvbit = (localVal & ((uint32_t)0x00F00000)) >> 20;
    *wfrfpllfrefsel = (localVal & ((uint32_t)0x00080000)) >> 19;
    *wfrfpllfrefx2en = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfrfpllloopmode = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wfrfpllsincmode = (localVal & ((uint32_t)0x00018000)) >> 15;
    *wfrfplllpfnotchbypass = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wfrfpllvcogbit = (localVal & ((uint32_t)0x00003C00)) >> 10;
    *wfrfpllcprbit = (localVal & ((uint32_t)0x00000300)) >> 8;
    *wfrfpllcpibit = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *wfrfplllpfrbit = (localVal & ((uint32_t)0x0000000C)) >> 2;
    *wfrfplllpfgbit = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rfpll_pdt_reg_vbit field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_pdt_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_pdt_reg_vbit field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_pdt_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x3C000000)) >> 26);
}

/**
 * @brief Sets the wf_rfpll_pdt_reg_vbit field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllpdtregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_pdt_reg_vbit_setf(uint8_t wfrfpllpdtregvbit)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x3C000000)) | (((uint32_t)wfrfpllpdtregvbit << 26) & ((uint32_t)0x3C000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_dvdd_ldo_vbit field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_dvdd_ldo_vbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_dvdd_ldo_vbit field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_dvdd_ldo_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

/**
 * @brief Sets the wf_rfpll_dvdd_ldo_vbit field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplldvddldovbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_dvdd_ldo_vbit_setf(uint8_t wfrfplldvddldovbit)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x03000000)) | (((uint32_t)wfrfplldvddldovbit << 24) & ((uint32_t)0x03000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_presc_reg_vbit field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_presc_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_presc_reg_vbit field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_presc_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x00F00000)) >> 20);
}

/**
 * @brief Sets the wf_rfpll_presc_reg_vbit field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllprescregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_presc_reg_vbit_setf(uint8_t wfrfpllprescregvbit)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x00F00000)) | (((uint32_t)wfrfpllprescregvbit << 20) & ((uint32_t)0x00F00000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_fref_sel field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_fref_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_fref_sel field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_fref_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the wf_rfpll_fref_sel field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllfrefsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_fref_sel_setf(uint8_t wfrfpllfrefsel)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)wfrfpllfrefsel << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_frefx2_en field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_frefx2_en field's value will be returned.
 *
 * @return The current value of the wf_rfpll_frefx2_en field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_frefx_2_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_rfpll_frefx2_en field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllfrefx2en - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_frefx_2_en_setf(uint8_t wfrfpllfrefx2en)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wfrfpllfrefx2en << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_loop_mode field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_loop_mode field's value will be returned.
 *
 * @return The current value of the wf_rfpll_loop_mode field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_loop_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_rfpll_loop_mode field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllloopmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_loop_mode_setf(uint8_t wfrfpllloopmode)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wfrfpllloopmode << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_sinc_mode field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_sinc_mode field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sinc_mode field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sinc_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x00018000)) >> 15);
}

/**
 * @brief Sets the wf_rfpll_sinc_mode field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllsincmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_sinc_mode_setf(uint8_t wfrfpllsincmode)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x00018000)) | (((uint32_t)wfrfpllsincmode << 15) & ((uint32_t)0x00018000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_lpf_notch_bypass field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_lpf_notch_bypass field's value will be returned.
 *
 * @return The current value of the wf_rfpll_lpf_notch_bypass field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_lpf_notch_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the wf_rfpll_lpf_notch_bypass field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplllpfnotchbypass - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_lpf_notch_bypass_setf(uint8_t wfrfplllpfnotchbypass)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)wfrfplllpfnotchbypass << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_vco_gbit field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_vco_gbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_vco_gbit field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_vco_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x00003C00)) >> 10);
}

/**
 * @brief Sets the wf_rfpll_vco_gbit field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllvcogbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_vco_gbit_setf(uint8_t wfrfpllvcogbit)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x00003C00)) | (((uint32_t)wfrfpllvcogbit << 10) & ((uint32_t)0x00003C00)));
}

/**
 * @brief Returns the current value of the wf_rfpll_cp_rbit field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_cp_rbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cp_rbit field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_cp_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the wf_rfpll_cp_rbit field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllcprbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_cp_rbit_setf(uint8_t wfrfpllcprbit)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)wfrfpllcprbit << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the wf_rfpll_cp_ibit field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_cp_ibit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cp_ibit field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_cp_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Sets the wf_rfpll_cp_ibit field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllcpibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_cp_ibit_setf(uint8_t wfrfpllcpibit)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x000000F0)) | (((uint32_t)wfrfpllcpibit << 4) & ((uint32_t)0x000000F0)));
}

/**
 * @brief Returns the current value of the wf_rfpll_lpf_rbit field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_lpf_rbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_lpf_rbit field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_lpf_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x0000000C)) >> 2);
}

/**
 * @brief Sets the wf_rfpll_lpf_rbit field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplllpfrbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_lpf_rbit_setf(uint8_t wfrfplllpfrbit)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x0000000C)) | (((uint32_t)wfrfplllpfrbit << 2) & ((uint32_t)0x0000000C)));
}

/**
 * @brief Returns the current value of the wf_rfpll_lpf_gbit field in the REG_68 register.
 *
 * The REG_68 register will be read and the wf_rfpll_lpf_gbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_lpf_gbit field in the REG_68 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_lpf_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_68_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the wf_rfpll_lpf_gbit field of the REG_68 register.
 *
 * The REG_68 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplllpfgbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_lpf_gbit_setf(uint8_t wfrfplllpfgbit)
{
    REG_PL_WR(WLAN_RF_REG_68_ADDR, (REG_PL_RD(WLAN_RF_REG_68_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)wfrfplllpfgbit << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_6C register definitions
 * <table>
 * <caption id="REG_6C_BF">REG_6C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:26 <td> wf_rfpll_pdt_rbit <td>R <td>R/W <td>0x0
 * <tr><td>25 <td>wf_rfpll_sdm_clk_sel <td>W <td>R <td>0
 * <tr><td>24 <td>  wf_rfpll_fbc_sel <td>R <td>R/W <td>0
 * <tr><td>23 <td>wf_rfpll_cal_clk_edge_sel <td>R <td>R/W <td>0
 * <tr><td>22 <td>   wf_rfpll_cal_en <td>W <td>R <td>0
 * <tr><td>21:20 <td>  wf_rfpll_cal_bit <td>R <td>R/W <td>0x2
 * <tr><td>19:18 <td>wf_rfpll_vco_cal_sel <td>R <td>R/W <td>0x2
 * <tr><td>17:01 <td>  wf_rfpll_cnt_out <td>W <td>R <td>0x0
 * <tr><td>00 <td> wf_rfpll_lock_out <td>W <td>R <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_6C register
#define WLAN_RF_REG_6C_ADDR   0x4034406C
/// Offset of the REG_6C register from the base address
#define WLAN_RF_REG_6C_OFFSET 0x0000006C
/// Index of the REG_6C register
#define WLAN_RF_REG_6C_INDEX  0x0000001B
/// Reset value of the REG_6C register
#define WLAN_RF_REG_6C_RESET  0x00280000

/**
 * @brief Returns the current value of the REG_6C register.
 * The REG_6C register will be read and its value returned.
 * @return The current value of the REG_6C register.
 */
__INLINE uint32_t wlan_rf_reg_6c_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_6C_ADDR);
}

/**
 * @brief Sets the REG_6C register to a value.
 * The REG_6C register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_6c_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_6C_ADDR, value);
}

// field definitions
/// WF_RFPLL_PDT_RBIT field mask
#define WLAN_RF_WF_RFPLL_PDT_RBIT_MASK           ((uint32_t)0xFC000000)
/// WF_RFPLL_PDT_RBIT field LSB position
#define WLAN_RF_WF_RFPLL_PDT_RBIT_LSB            26
/// WF_RFPLL_PDT_RBIT field width
#define WLAN_RF_WF_RFPLL_PDT_RBIT_WIDTH          ((uint32_t)0x00000006)
/// WF_RFPLL_SDM_CLK_SEL field bit
#define WLAN_RF_WF_RFPLL_SDM_CLK_SEL_BIT         ((uint32_t)0x02000000)
/// WF_RFPLL_SDM_CLK_SEL field position
#define WLAN_RF_WF_RFPLL_SDM_CLK_SEL_POS         25
/// WF_RFPLL_FBC_SEL field bit
#define WLAN_RF_WF_RFPLL_FBC_SEL_BIT             ((uint32_t)0x01000000)
/// WF_RFPLL_FBC_SEL field position
#define WLAN_RF_WF_RFPLL_FBC_SEL_POS             24
/// WF_RFPLL_CAL_CLK_EDGE_SEL field bit
#define WLAN_RF_WF_RFPLL_CAL_CLK_EDGE_SEL_BIT    ((uint32_t)0x00800000)
/// WF_RFPLL_CAL_CLK_EDGE_SEL field position
#define WLAN_RF_WF_RFPLL_CAL_CLK_EDGE_SEL_POS    23
/// WF_RFPLL_CAL_EN field bit
#define WLAN_RF_WF_RFPLL_CAL_EN_BIT              ((uint32_t)0x00400000)
/// WF_RFPLL_CAL_EN field position
#define WLAN_RF_WF_RFPLL_CAL_EN_POS              22
/// WF_RFPLL_CAL_BIT field mask
#define WLAN_RF_WF_RFPLL_CAL_BIT_MASK            ((uint32_t)0x00300000)
/// WF_RFPLL_CAL_BIT field LSB position
#define WLAN_RF_WF_RFPLL_CAL_BIT_LSB             20
/// WF_RFPLL_CAL_BIT field width
#define WLAN_RF_WF_RFPLL_CAL_BIT_WIDTH           ((uint32_t)0x00000002)
/// WF_RFPLL_VCO_CAL_SEL field mask
#define WLAN_RF_WF_RFPLL_VCO_CAL_SEL_MASK        ((uint32_t)0x000C0000)
/// WF_RFPLL_VCO_CAL_SEL field LSB position
#define WLAN_RF_WF_RFPLL_VCO_CAL_SEL_LSB         18
/// WF_RFPLL_VCO_CAL_SEL field width
#define WLAN_RF_WF_RFPLL_VCO_CAL_SEL_WIDTH       ((uint32_t)0x00000002)
/// WF_RFPLL_CNT_OUT field mask
#define WLAN_RF_WF_RFPLL_CNT_OUT_MASK            ((uint32_t)0x0003FFFE)
/// WF_RFPLL_CNT_OUT field LSB position
#define WLAN_RF_WF_RFPLL_CNT_OUT_LSB             1
/// WF_RFPLL_CNT_OUT field width
#define WLAN_RF_WF_RFPLL_CNT_OUT_WIDTH           ((uint32_t)0x00000011)
/// WF_RFPLL_LOCK_OUT field bit
#define WLAN_RF_WF_RFPLL_LOCK_OUT_BIT            ((uint32_t)0x00000001)
/// WF_RFPLL_LOCK_OUT field position
#define WLAN_RF_WF_RFPLL_LOCK_OUT_POS            0

/// WF_RFPLL_PDT_RBIT field reset value
#define WLAN_RF_WF_RFPLL_PDT_RBIT_RST            0x0
/// WF_RFPLL_SDM_CLK_SEL field reset value
#define WLAN_RF_WF_RFPLL_SDM_CLK_SEL_RST         0x0
/// WF_RFPLL_FBC_SEL field reset value
#define WLAN_RF_WF_RFPLL_FBC_SEL_RST             0x0
/// WF_RFPLL_CAL_CLK_EDGE_SEL field reset value
#define WLAN_RF_WF_RFPLL_CAL_CLK_EDGE_SEL_RST    0x0
/// WF_RFPLL_CAL_EN field reset value
#define WLAN_RF_WF_RFPLL_CAL_EN_RST              0x0
/// WF_RFPLL_CAL_BIT field reset value
#define WLAN_RF_WF_RFPLL_CAL_BIT_RST             0x2
/// WF_RFPLL_VCO_CAL_SEL field reset value
#define WLAN_RF_WF_RFPLL_VCO_CAL_SEL_RST         0x2
/// WF_RFPLL_CNT_OUT field reset value
#define WLAN_RF_WF_RFPLL_CNT_OUT_RST             0x0
/// WF_RFPLL_LOCK_OUT field reset value
#define WLAN_RF_WF_RFPLL_LOCK_OUT_RST            0x0

/**
 * @brief Constructs a value for the REG_6C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrfpllpdtrbit - The value to use for the wf_rfpll_pdt_rbit field.
 * @param[in] wfrfpllfbcsel - The value to use for the wf_rfpll_fbc_sel field.
 * @param[in] wfrfpllcalclkedgesel - The value to use for the wf_rfpll_cal_clk_edge_sel field.
 * @param[in] wfrfpllcalbit - The value to use for the wf_rfpll_cal_bit field.
 * @param[in] wfrfpllvcocalsel - The value to use for the wf_rfpll_vco_cal_sel field.
 */
__INLINE void wlan_rf_reg_6c_pack(uint8_t wfrfpllpdtrbit, uint8_t wfrfpllfbcsel, uint8_t wfrfpllcalclkedgesel, uint8_t wfrfpllcalbit, uint8_t wfrfpllvcocalsel)
{
    REG_PL_WR(WLAN_RF_REG_6C_ADDR,  ((uint32_t)wfrfpllpdtrbit << 26) | ((uint32_t)wfrfpllfbcsel << 24) | ((uint32_t)wfrfpllcalclkedgesel << 23) | ((uint32_t)wfrfpllcalbit << 20) | ((uint32_t)wfrfpllvcocalsel << 18));
}

/**
 * @brief Unpacks REG_6C's fields from current value of the REG_6C register.
 *
 * Reads the REG_6C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrfpllpdtrbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllsdmclksel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllfbcsel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllcalclkedgesel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllcalen - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllcalbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllvcocalsel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllcntout - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplllockout - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_6c_unpack(uint8_t* wfrfpllpdtrbit, uint8_t* wfrfpllsdmclksel, uint8_t* wfrfpllfbcsel, uint8_t* wfrfpllcalclkedgesel, uint8_t* wfrfpllcalen, uint8_t* wfrfpllcalbit, uint8_t* wfrfpllvcocalsel, uint32_t* wfrfpllcntout, uint8_t* wfrfplllockout)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);

    *wfrfpllpdtrbit = (localVal & ((uint32_t)0xFC000000)) >> 26;
    *wfrfpllsdmclksel = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wfrfpllfbcsel = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wfrfpllcalclkedgesel = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfrfpllcalen = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wfrfpllcalbit = (localVal & ((uint32_t)0x00300000)) >> 20;
    *wfrfpllvcocalsel = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *wfrfpllcntout = (localVal & ((uint32_t)0x0003FFFE)) >> 1;
    *wfrfplllockout = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rfpll_pdt_rbit field in the REG_6C register.
 *
 * The REG_6C register will be read and the wf_rfpll_pdt_rbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_pdt_rbit field in the REG_6C register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_pdt_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);
    return ((localVal & ((uint32_t)0xFC000000)) >> 26);
}

/**
 * @brief Sets the wf_rfpll_pdt_rbit field of the REG_6C register.
 *
 * The REG_6C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllpdtrbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_pdt_rbit_setf(uint8_t wfrfpllpdtrbit)
{
    REG_PL_WR(WLAN_RF_REG_6C_ADDR, (REG_PL_RD(WLAN_RF_REG_6C_ADDR) & ~((uint32_t)0xFC000000)) | (((uint32_t)wfrfpllpdtrbit << 26) & ((uint32_t)0xFC000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_sdm_clk_sel field in the REG_6C register.
 *
 * The REG_6C register will be read and the wf_rfpll_sdm_clk_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sdm_clk_sel field in the REG_6C register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sdm_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Returns the current value of the wf_rfpll_fbc_sel field in the REG_6C register.
 *
 * The REG_6C register will be read and the wf_rfpll_fbc_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_fbc_sel field in the REG_6C register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_fbc_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the wf_rfpll_fbc_sel field of the REG_6C register.
 *
 * The REG_6C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllfbcsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_fbc_sel_setf(uint8_t wfrfpllfbcsel)
{
    REG_PL_WR(WLAN_RF_REG_6C_ADDR, (REG_PL_RD(WLAN_RF_REG_6C_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wfrfpllfbcsel << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_cal_clk_edge_sel field in the REG_6C register.
 *
 * The REG_6C register will be read and the wf_rfpll_cal_clk_edge_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cal_clk_edge_sel field in the REG_6C register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_cal_clk_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_rfpll_cal_clk_edge_sel field of the REG_6C register.
 *
 * The REG_6C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllcalclkedgesel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_cal_clk_edge_sel_setf(uint8_t wfrfpllcalclkedgesel)
{
    REG_PL_WR(WLAN_RF_REG_6C_ADDR, (REG_PL_RD(WLAN_RF_REG_6C_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wfrfpllcalclkedgesel << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_cal_en field in the REG_6C register.
 *
 * The REG_6C register will be read and the wf_rfpll_cal_en field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cal_en field in the REG_6C register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Returns the current value of the wf_rfpll_cal_bit field in the REG_6C register.
 *
 * The REG_6C register will be read and the wf_rfpll_cal_bit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cal_bit field in the REG_6C register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_cal_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

/**
 * @brief Sets the wf_rfpll_cal_bit field of the REG_6C register.
 *
 * The REG_6C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllcalbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_cal_bit_setf(uint8_t wfrfpllcalbit)
{
    REG_PL_WR(WLAN_RF_REG_6C_ADDR, (REG_PL_RD(WLAN_RF_REG_6C_ADDR) & ~((uint32_t)0x00300000)) | (((uint32_t)wfrfpllcalbit << 20) & ((uint32_t)0x00300000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_vco_cal_sel field in the REG_6C register.
 *
 * The REG_6C register will be read and the wf_rfpll_vco_cal_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_vco_cal_sel field in the REG_6C register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_vco_cal_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the wf_rfpll_vco_cal_sel field of the REG_6C register.
 *
 * The REG_6C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllvcocalsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_vco_cal_sel_setf(uint8_t wfrfpllvcocalsel)
{
    REG_PL_WR(WLAN_RF_REG_6C_ADDR, (REG_PL_RD(WLAN_RF_REG_6C_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)wfrfpllvcocalsel << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_cnt_out field in the REG_6C register.
 *
 * The REG_6C register will be read and the wf_rfpll_cnt_out field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cnt_out field in the REG_6C register.
 */
__INLINE uint32_t wlan_rf_wf_rfpll_cnt_out_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);
    return ((localVal & ((uint32_t)0x0003FFFE)) >> 1);
}

/**
 * @brief Returns the current value of the wf_rfpll_lock_out field in the REG_6C register.
 *
 * The REG_6C register will be read and the wf_rfpll_lock_out field's value will be returned.
 *
 * @return The current value of the wf_rfpll_lock_out field in the REG_6C register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_lock_out_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_6C_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/// @}

/**
 * @name REG_70 register definitions
 * <table>
 * <caption id="REG_70_BF">REG_70 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>22 <td>wf_rfpll_notch_sel_4p2G <td>R <td>R/W <td>1
 * <tr><td>21:13 <td>wf_rfpll_adc_clk_div <td>R <td>R/W <td>0x18
 * <tr><td>12 <td>wf_rfpll_div_clk_edge_sel <td>R <td>R/W <td>0
 * <tr><td>11:10 <td>wf_rfpll_sinc_clk_div <td>R <td>R/W <td>0x0
 * <tr><td>09:08 <td>wf_rfpll_sinc_clk_sel <td>R <td>R/W <td>0x0
 * <tr><td>07 <td>wf_rfpll_notch_bypass <td>R <td>R/W <td>0
 * <tr><td>06 <td>wf_logen_phase_sync_clk_sel <td>R <td>R/W <td>0
 * <tr><td>05 <td>wf_logen_phase_sync1_clk_sel <td>R <td>R/W <td>0
 * <tr><td>04 <td>wf_vco_avdd18_reg_bypass <td>R <td>R/W <td>1
 * <tr><td>03:01 <td>wf_vco_avdd18_reg_bit <td>R <td>R/W <td>0x3
 * <tr><td>00 <td>wf_vco_avdd18_reg_en <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_70 register
#define WLAN_RF_REG_70_ADDR   0x40344070
/// Offset of the REG_70 register from the base address
#define WLAN_RF_REG_70_OFFSET 0x00000070
/// Index of the REG_70 register
#define WLAN_RF_REG_70_INDEX  0x0000001C
/// Reset value of the REG_70 register
#define WLAN_RF_REG_70_RESET  0x00430017

/**
 * @brief Returns the current value of the REG_70 register.
 * The REG_70 register will be read and its value returned.
 * @return The current value of the REG_70 register.
 */
__INLINE uint32_t wlan_rf_reg_70_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_70_ADDR);
}

/**
 * @brief Sets the REG_70 register to a value.
 * The REG_70 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_70_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, value);
}

// field definitions
/// WF_RFPLL_NOTCH_SEL__4P_2G field bit
#define WLAN_RF_WF_RFPLL_NOTCH_SEL__4P_2G_BIT        ((uint32_t)0x00400000)
/// WF_RFPLL_NOTCH_SEL__4P_2G field position
#define WLAN_RF_WF_RFPLL_NOTCH_SEL__4P_2G_POS        22
/// WF_RFPLL_ADC_CLK_DIV field mask
#define WLAN_RF_WF_RFPLL_ADC_CLK_DIV_MASK            ((uint32_t)0x003FE000)
/// WF_RFPLL_ADC_CLK_DIV field LSB position
#define WLAN_RF_WF_RFPLL_ADC_CLK_DIV_LSB             13
/// WF_RFPLL_ADC_CLK_DIV field width
#define WLAN_RF_WF_RFPLL_ADC_CLK_DIV_WIDTH           ((uint32_t)0x00000009)
/// WF_RFPLL_DIV_CLK_EDGE_SEL field bit
#define WLAN_RF_WF_RFPLL_DIV_CLK_EDGE_SEL_BIT        ((uint32_t)0x00001000)
/// WF_RFPLL_DIV_CLK_EDGE_SEL field position
#define WLAN_RF_WF_RFPLL_DIV_CLK_EDGE_SEL_POS        12
/// WF_RFPLL_SINC_CLK_DIV field mask
#define WLAN_RF_WF_RFPLL_SINC_CLK_DIV_MASK           ((uint32_t)0x00000C00)
/// WF_RFPLL_SINC_CLK_DIV field LSB position
#define WLAN_RF_WF_RFPLL_SINC_CLK_DIV_LSB            10
/// WF_RFPLL_SINC_CLK_DIV field width
#define WLAN_RF_WF_RFPLL_SINC_CLK_DIV_WIDTH          ((uint32_t)0x00000002)
/// WF_RFPLL_SINC_CLK_SEL field mask
#define WLAN_RF_WF_RFPLL_SINC_CLK_SEL_MASK           ((uint32_t)0x00000300)
/// WF_RFPLL_SINC_CLK_SEL field LSB position
#define WLAN_RF_WF_RFPLL_SINC_CLK_SEL_LSB            8
/// WF_RFPLL_SINC_CLK_SEL field width
#define WLAN_RF_WF_RFPLL_SINC_CLK_SEL_WIDTH          ((uint32_t)0x00000002)
/// WF_RFPLL_NOTCH_BYPASS field bit
#define WLAN_RF_WF_RFPLL_NOTCH_BYPASS_BIT            ((uint32_t)0x00000080)
/// WF_RFPLL_NOTCH_BYPASS field position
#define WLAN_RF_WF_RFPLL_NOTCH_BYPASS_POS            7
/// WF_LOGEN_PHASE_SYNC_CLK_SEL field bit
#define WLAN_RF_WF_LOGEN_PHASE_SYNC_CLK_SEL_BIT      ((uint32_t)0x00000040)
/// WF_LOGEN_PHASE_SYNC_CLK_SEL field position
#define WLAN_RF_WF_LOGEN_PHASE_SYNC_CLK_SEL_POS      6
/// WF_LOGEN_PHASE_SYNC_1_CLK_SEL field bit
#define WLAN_RF_WF_LOGEN_PHASE_SYNC_1_CLK_SEL_BIT    ((uint32_t)0x00000020)
/// WF_LOGEN_PHASE_SYNC_1_CLK_SEL field position
#define WLAN_RF_WF_LOGEN_PHASE_SYNC_1_CLK_SEL_POS    5
/// WF_VCO_AVDD_18_REG_BYPASS field bit
#define WLAN_RF_WF_VCO_AVDD_18_REG_BYPASS_BIT        ((uint32_t)0x00000010)
/// WF_VCO_AVDD_18_REG_BYPASS field position
#define WLAN_RF_WF_VCO_AVDD_18_REG_BYPASS_POS        4
/// WF_VCO_AVDD_18_REG_BIT field mask
#define WLAN_RF_WF_VCO_AVDD_18_REG_BIT_MASK          ((uint32_t)0x0000000E)
/// WF_VCO_AVDD_18_REG_BIT field LSB position
#define WLAN_RF_WF_VCO_AVDD_18_REG_BIT_LSB           1
/// WF_VCO_AVDD_18_REG_BIT field width
#define WLAN_RF_WF_VCO_AVDD_18_REG_BIT_WIDTH         ((uint32_t)0x00000003)
/// WF_VCO_AVDD_18_REG_EN field bit
#define WLAN_RF_WF_VCO_AVDD_18_REG_EN_BIT            ((uint32_t)0x00000001)
/// WF_VCO_AVDD_18_REG_EN field position
#define WLAN_RF_WF_VCO_AVDD_18_REG_EN_POS            0

/// WF_RFPLL_NOTCH_SEL__4P_2G field reset value
#define WLAN_RF_WF_RFPLL_NOTCH_SEL__4P_2G_RST        0x1
/// WF_RFPLL_ADC_CLK_DIV field reset value
#define WLAN_RF_WF_RFPLL_ADC_CLK_DIV_RST             0x18
/// WF_RFPLL_DIV_CLK_EDGE_SEL field reset value
#define WLAN_RF_WF_RFPLL_DIV_CLK_EDGE_SEL_RST        0x0
/// WF_RFPLL_SINC_CLK_DIV field reset value
#define WLAN_RF_WF_RFPLL_SINC_CLK_DIV_RST            0x0
/// WF_RFPLL_SINC_CLK_SEL field reset value
#define WLAN_RF_WF_RFPLL_SINC_CLK_SEL_RST            0x0
/// WF_RFPLL_NOTCH_BYPASS field reset value
#define WLAN_RF_WF_RFPLL_NOTCH_BYPASS_RST            0x0
/// WF_LOGEN_PHASE_SYNC_CLK_SEL field reset value
#define WLAN_RF_WF_LOGEN_PHASE_SYNC_CLK_SEL_RST      0x0
/// WF_LOGEN_PHASE_SYNC_1_CLK_SEL field reset value
#define WLAN_RF_WF_LOGEN_PHASE_SYNC_1_CLK_SEL_RST    0x0
/// WF_VCO_AVDD_18_REG_BYPASS field reset value
#define WLAN_RF_WF_VCO_AVDD_18_REG_BYPASS_RST        0x1
/// WF_VCO_AVDD_18_REG_BIT field reset value
#define WLAN_RF_WF_VCO_AVDD_18_REG_BIT_RST           0x3
/// WF_VCO_AVDD_18_REG_EN field reset value
#define WLAN_RF_WF_VCO_AVDD_18_REG_EN_RST            0x1

/**
 * @brief Constructs a value for the REG_70 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrfpllnotchsel4p2g - The value to use for the wf_rfpll_notch_sel_4p2G field.
 * @param[in] wfrfplladcclkdiv - The value to use for the wf_rfpll_adc_clk_div field.
 * @param[in] wfrfplldivclkedgesel - The value to use for the wf_rfpll_div_clk_edge_sel field.
 * @param[in] wfrfpllsincclkdiv - The value to use for the wf_rfpll_sinc_clk_div field.
 * @param[in] wfrfpllsincclksel - The value to use for the wf_rfpll_sinc_clk_sel field.
 * @param[in] wfrfpllnotchbypass - The value to use for the wf_rfpll_notch_bypass field.
 * @param[in] wflogenphasesyncclksel - The value to use for the wf_logen_phase_sync_clk_sel field.
 * @param[in] wflogenphasesync1clksel - The value to use for the wf_logen_phase_sync1_clk_sel field.
 * @param[in] wfvcoavdd18regbypass - The value to use for the wf_vco_avdd18_reg_bypass field.
 * @param[in] wfvcoavdd18regbit - The value to use for the wf_vco_avdd18_reg_bit field.
 * @param[in] wfvcoavdd18regen - The value to use for the wf_vco_avdd18_reg_en field.
 */
__INLINE void wlan_rf_reg_70_pack(uint8_t wfrfpllnotchsel4p2g, uint16_t wfrfplladcclkdiv, uint8_t wfrfplldivclkedgesel, uint8_t wfrfpllsincclkdiv, uint8_t wfrfpllsincclksel, uint8_t wfrfpllnotchbypass, uint8_t wflogenphasesyncclksel, uint8_t wflogenphasesync1clksel, uint8_t wfvcoavdd18regbypass, uint8_t wfvcoavdd18regbit, uint8_t wfvcoavdd18regen)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR,  ((uint32_t)wfrfpllnotchsel4p2g << 22) | ((uint32_t)wfrfplladcclkdiv << 13) | ((uint32_t)wfrfplldivclkedgesel << 12) | ((uint32_t)wfrfpllsincclkdiv << 10) | ((uint32_t)wfrfpllsincclksel << 8) | ((uint32_t)wfrfpllnotchbypass << 7) | ((uint32_t)wflogenphasesyncclksel << 6) | ((uint32_t)wflogenphasesync1clksel << 5) | ((uint32_t)wfvcoavdd18regbypass << 4) | ((uint32_t)wfvcoavdd18regbit << 1) | ((uint32_t)wfvcoavdd18regen << 0));
}

/**
 * @brief Unpacks REG_70's fields from current value of the REG_70 register.
 *
 * Reads the REG_70 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrfpllnotchsel4p2g - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplladcclkdiv - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplldivclkedgesel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllsincclkdiv - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllsincclksel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllnotchbypass - Will be populated with the current value of this field from the register.
 * @param[out] wflogenphasesyncclksel - Will be populated with the current value of this field from the register.
 * @param[out] wflogenphasesync1clksel - Will be populated with the current value of this field from the register.
 * @param[out] wfvcoavdd18regbypass - Will be populated with the current value of this field from the register.
 * @param[out] wfvcoavdd18regbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcoavdd18regen - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_70_unpack(uint8_t* wfrfpllnotchsel4p2g, uint16_t* wfrfplladcclkdiv, uint8_t* wfrfplldivclkedgesel, uint8_t* wfrfpllsincclkdiv, uint8_t* wfrfpllsincclksel, uint8_t* wfrfpllnotchbypass, uint8_t* wflogenphasesyncclksel, uint8_t* wflogenphasesync1clksel, uint8_t* wfvcoavdd18regbypass, uint8_t* wfvcoavdd18regbit, uint8_t* wfvcoavdd18regen)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);

    *wfrfpllnotchsel4p2g = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wfrfplladcclkdiv = (localVal & ((uint32_t)0x003FE000)) >> 13;
    *wfrfplldivclkedgesel = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wfrfpllsincclkdiv = (localVal & ((uint32_t)0x00000C00)) >> 10;
    *wfrfpllsincclksel = (localVal & ((uint32_t)0x00000300)) >> 8;
    *wfrfpllnotchbypass = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wflogenphasesyncclksel = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wflogenphasesync1clksel = (localVal & ((uint32_t)0x00000020)) >> 5;
    *wfvcoavdd18regbypass = (localVal & ((uint32_t)0x00000010)) >> 4;
    *wfvcoavdd18regbit = (localVal & ((uint32_t)0x0000000E)) >> 1;
    *wfvcoavdd18regen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rfpll_notch_sel_4p2G field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_rfpll_notch_sel_4p2G field's value will be returned.
 *
 * @return The current value of the wf_rfpll_notch_sel_4p2G field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_notch_sel__4p_2g_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the wf_rfpll_notch_sel_4p2G field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllnotchsel4p2g - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_notch_sel__4p_2g_setf(uint8_t wfrfpllnotchsel4p2g)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)wfrfpllnotchsel4p2g << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_adc_clk_div field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_rfpll_adc_clk_div field's value will be returned.
 *
 * @return The current value of the wf_rfpll_adc_clk_div field in the REG_70 register.
 */
__INLINE uint16_t wlan_rf_wf_rfpll_adc_clk_div_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x003FE000)) >> 13);
}

/**
 * @brief Sets the wf_rfpll_adc_clk_div field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplladcclkdiv - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_adc_clk_div_setf(uint16_t wfrfplladcclkdiv)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x003FE000)) | (((uint32_t)wfrfplladcclkdiv << 13) & ((uint32_t)0x003FE000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_div_clk_edge_sel field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_rfpll_div_clk_edge_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_div_clk_edge_sel field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_div_clk_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_rfpll_div_clk_edge_sel field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplldivclkedgesel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_div_clk_edge_sel_setf(uint8_t wfrfplldivclkedgesel)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wfrfplldivclkedgesel << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_sinc_clk_div field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_rfpll_sinc_clk_div field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sinc_clk_div field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sinc_clk_div_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x00000C00)) >> 10);
}

/**
 * @brief Sets the wf_rfpll_sinc_clk_div field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllsincclkdiv - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_sinc_clk_div_setf(uint8_t wfrfpllsincclkdiv)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x00000C00)) | (((uint32_t)wfrfpllsincclkdiv << 10) & ((uint32_t)0x00000C00)));
}

/**
 * @brief Returns the current value of the wf_rfpll_sinc_clk_sel field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_rfpll_sinc_clk_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sinc_clk_sel field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sinc_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the wf_rfpll_sinc_clk_sel field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllsincclksel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_sinc_clk_sel_setf(uint8_t wfrfpllsincclksel)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)wfrfpllsincclksel << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the wf_rfpll_notch_bypass field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_rfpll_notch_bypass field's value will be returned.
 *
 * @return The current value of the wf_rfpll_notch_bypass field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_notch_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_rfpll_notch_bypass field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllnotchbypass - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_notch_bypass_setf(uint8_t wfrfpllnotchbypass)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wfrfpllnotchbypass << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_logen_phase_sync_clk_sel field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_logen_phase_sync_clk_sel field's value will be returned.
 *
 * @return The current value of the wf_logen_phase_sync_clk_sel field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_logen_phase_sync_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the wf_logen_phase_sync_clk_sel field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflogenphasesyncclksel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_logen_phase_sync_clk_sel_setf(uint8_t wflogenphasesyncclksel)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)wflogenphasesyncclksel << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the wf_logen_phase_sync1_clk_sel field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_logen_phase_sync1_clk_sel field's value will be returned.
 *
 * @return The current value of the wf_logen_phase_sync1_clk_sel field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_logen_phase_sync_1_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the wf_logen_phase_sync1_clk_sel field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflogenphasesync1clksel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_logen_phase_sync_1_clk_sel_setf(uint8_t wflogenphasesync1clksel)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)wflogenphasesync1clksel << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the wf_vco_avdd18_reg_bypass field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_vco_avdd18_reg_bypass field's value will be returned.
 *
 * @return The current value of the wf_vco_avdd18_reg_bypass field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_avdd_18_reg_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the wf_vco_avdd18_reg_bypass field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcoavdd18regbypass - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_avdd_18_reg_bypass_setf(uint8_t wfvcoavdd18regbypass)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)wfvcoavdd18regbypass << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the wf_vco_avdd18_reg_bit field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_vco_avdd18_reg_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_avdd18_reg_bit field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_avdd_18_reg_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x0000000E)) >> 1);
}

/**
 * @brief Sets the wf_vco_avdd18_reg_bit field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcoavdd18regbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_avdd_18_reg_bit_setf(uint8_t wfvcoavdd18regbit)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x0000000E)) | (((uint32_t)wfvcoavdd18regbit << 1) & ((uint32_t)0x0000000E)));
}

/**
 * @brief Returns the current value of the wf_vco_avdd18_reg_en field in the REG_70 register.
 *
 * The REG_70 register will be read and the wf_vco_avdd18_reg_en field's value will be returned.
 *
 * @return The current value of the wf_vco_avdd18_reg_en field in the REG_70 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_avdd_18_reg_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_70_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_vco_avdd18_reg_en field of the REG_70 register.
 *
 * The REG_70 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcoavdd18regen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_avdd_18_reg_en_setf(uint8_t wfvcoavdd18regen)
{
    REG_PL_WR(WLAN_RF_REG_70_ADDR, (REG_PL_RD(WLAN_RF_REG_70_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfvcoavdd18regen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_74 register definitions
 * <table>
 * <caption id="REG_74_BF">REG_74 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:19 <td>   wf_vco_band_bit <td>W <td>R <td>0xBB8
 * <tr><td>18:17 <td>wf_vco_band_aux_bit <td>R <td>R/W <td>0x1
 * <tr><td>16:13 <td>wf_vco_band_temp_bit <td>R <td>R/W <td>0x7
 * <tr><td>12:08 <td>wf_vco_band_tail_bit <td>R <td>R/W <td>0x0
 * <tr><td>07:04 <td>wf_vco_core_reg_bit <td>R <td>R/W <td>0x8
 * <tr><td>03:00 <td>wf_vco_buf_reg_bit <td>R <td>R/W <td>0x8
 * </table>
 *
 * @{
 */

/// Address of the REG_74 register
#define WLAN_RF_REG_74_ADDR   0x40344074
/// Offset of the REG_74 register from the base address
#define WLAN_RF_REG_74_OFFSET 0x00000074
/// Index of the REG_74 register
#define WLAN_RF_REG_74_INDEX  0x0000001D
/// Reset value of the REG_74 register
#define WLAN_RF_REG_74_RESET  0x5DC2E088

/**
 * @brief Returns the current value of the REG_74 register.
 * The REG_74 register will be read and its value returned.
 * @return The current value of the REG_74 register.
 */
__INLINE uint32_t wlan_rf_reg_74_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_74_ADDR);
}

/**
 * @brief Sets the REG_74 register to a value.
 * The REG_74 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_74_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_74_ADDR, value);
}

// field definitions
/// WF_VCO_BAND_BIT field mask
#define WLAN_RF_WF_VCO_BAND_BIT_MASK        ((uint32_t)0xFFF80000)
/// WF_VCO_BAND_BIT field LSB position
#define WLAN_RF_WF_VCO_BAND_BIT_LSB         19
/// WF_VCO_BAND_BIT field width
#define WLAN_RF_WF_VCO_BAND_BIT_WIDTH       ((uint32_t)0x0000000D)
/// WF_VCO_BAND_AUX_BIT field mask
#define WLAN_RF_WF_VCO_BAND_AUX_BIT_MASK    ((uint32_t)0x00060000)
/// WF_VCO_BAND_AUX_BIT field LSB position
#define WLAN_RF_WF_VCO_BAND_AUX_BIT_LSB     17
/// WF_VCO_BAND_AUX_BIT field width
#define WLAN_RF_WF_VCO_BAND_AUX_BIT_WIDTH   ((uint32_t)0x00000002)
/// WF_VCO_BAND_TEMP_BIT field mask
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_MASK   ((uint32_t)0x0001E000)
/// WF_VCO_BAND_TEMP_BIT field LSB position
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_LSB    13
/// WF_VCO_BAND_TEMP_BIT field width
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_WIDTH  ((uint32_t)0x00000004)
/// WF_VCO_BAND_TAIL_BIT field mask
#define WLAN_RF_WF_VCO_BAND_TAIL_BIT_MASK   ((uint32_t)0x00001F00)
/// WF_VCO_BAND_TAIL_BIT field LSB position
#define WLAN_RF_WF_VCO_BAND_TAIL_BIT_LSB    8
/// WF_VCO_BAND_TAIL_BIT field width
#define WLAN_RF_WF_VCO_BAND_TAIL_BIT_WIDTH  ((uint32_t)0x00000005)
/// WF_VCO_CORE_REG_BIT field mask
#define WLAN_RF_WF_VCO_CORE_REG_BIT_MASK    ((uint32_t)0x000000F0)
/// WF_VCO_CORE_REG_BIT field LSB position
#define WLAN_RF_WF_VCO_CORE_REG_BIT_LSB     4
/// WF_VCO_CORE_REG_BIT field width
#define WLAN_RF_WF_VCO_CORE_REG_BIT_WIDTH   ((uint32_t)0x00000004)
/// WF_VCO_BUF_REG_BIT field mask
#define WLAN_RF_WF_VCO_BUF_REG_BIT_MASK     ((uint32_t)0x0000000F)
/// WF_VCO_BUF_REG_BIT field LSB position
#define WLAN_RF_WF_VCO_BUF_REG_BIT_LSB      0
/// WF_VCO_BUF_REG_BIT field width
#define WLAN_RF_WF_VCO_BUF_REG_BIT_WIDTH    ((uint32_t)0x00000004)

/// WF_VCO_BAND_BIT field reset value
#define WLAN_RF_WF_VCO_BAND_BIT_RST         0xBB8
/// WF_VCO_BAND_AUX_BIT field reset value
#define WLAN_RF_WF_VCO_BAND_AUX_BIT_RST     0x1
/// WF_VCO_BAND_TEMP_BIT field reset value
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_RST    0x7
/// WF_VCO_BAND_TAIL_BIT field reset value
#define WLAN_RF_WF_VCO_BAND_TAIL_BIT_RST    0x0
/// WF_VCO_CORE_REG_BIT field reset value
#define WLAN_RF_WF_VCO_CORE_REG_BIT_RST     0x8
/// WF_VCO_BUF_REG_BIT field reset value
#define WLAN_RF_WF_VCO_BUF_REG_BIT_RST      0x8

/**
 * @brief Constructs a value for the REG_74 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfvcobandauxbit - The value to use for the wf_vco_band_aux_bit field.
 * @param[in] wfvcobandtempbit - The value to use for the wf_vco_band_temp_bit field.
 * @param[in] wfvcobandtailbit - The value to use for the wf_vco_band_tail_bit field.
 * @param[in] wfvcocoreregbit - The value to use for the wf_vco_core_reg_bit field.
 * @param[in] wfvcobufregbit - The value to use for the wf_vco_buf_reg_bit field.
 */
__INLINE void wlan_rf_reg_74_pack(uint8_t wfvcobandauxbit, uint8_t wfvcobandtempbit, uint8_t wfvcobandtailbit, uint8_t wfvcocoreregbit, uint8_t wfvcobufregbit)
{
    REG_PL_WR(WLAN_RF_REG_74_ADDR,  ((uint32_t)wfvcobandauxbit << 17) | ((uint32_t)wfvcobandtempbit << 13) | ((uint32_t)wfvcobandtailbit << 8) | ((uint32_t)wfvcocoreregbit << 4) | ((uint32_t)wfvcobufregbit << 0));
}

/**
 * @brief Unpacks REG_74's fields from current value of the REG_74 register.
 *
 * Reads the REG_74 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfvcobandbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcobandauxbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcobandtempbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcobandtailbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcocoreregbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcobufregbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_74_unpack(uint16_t* wfvcobandbit, uint8_t* wfvcobandauxbit, uint8_t* wfvcobandtempbit, uint8_t* wfvcobandtailbit, uint8_t* wfvcocoreregbit, uint8_t* wfvcobufregbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_74_ADDR);

    *wfvcobandbit = (localVal & ((uint32_t)0xFFF80000)) >> 19;
    *wfvcobandauxbit = (localVal & ((uint32_t)0x00060000)) >> 17;
    *wfvcobandtempbit = (localVal & ((uint32_t)0x0001E000)) >> 13;
    *wfvcobandtailbit = (localVal & ((uint32_t)0x00001F00)) >> 8;
    *wfvcocoreregbit = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *wfvcobufregbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_vco_band_bit field in the REG_74 register.
 *
 * The REG_74 register will be read and the wf_vco_band_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_band_bit field in the REG_74 register.
 */
__INLINE uint16_t wlan_rf_wf_vco_band_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_74_ADDR);
    return ((localVal & ((uint32_t)0xFFF80000)) >> 19);
}

/**
 * @brief Returns the current value of the wf_vco_band_aux_bit field in the REG_74 register.
 *
 * The REG_74 register will be read and the wf_vco_band_aux_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_band_aux_bit field in the REG_74 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_band_aux_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_74_ADDR);
    return ((localVal & ((uint32_t)0x00060000)) >> 17);
}

/**
 * @brief Sets the wf_vco_band_aux_bit field of the REG_74 register.
 *
 * The REG_74 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcobandauxbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_band_aux_bit_setf(uint8_t wfvcobandauxbit)
{
    REG_PL_WR(WLAN_RF_REG_74_ADDR, (REG_PL_RD(WLAN_RF_REG_74_ADDR) & ~((uint32_t)0x00060000)) | (((uint32_t)wfvcobandauxbit << 17) & ((uint32_t)0x00060000)));
}

/**
 * @brief Returns the current value of the wf_vco_band_temp_bit field in the REG_74 register.
 *
 * The REG_74 register will be read and the wf_vco_band_temp_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_band_temp_bit field in the REG_74 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_band_temp_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_74_ADDR);
    return ((localVal & ((uint32_t)0x0001E000)) >> 13);
}

/**
 * @brief Sets the wf_vco_band_temp_bit field of the REG_74 register.
 *
 * The REG_74 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcobandtempbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_band_temp_bit_setf(uint8_t wfvcobandtempbit)
{
    REG_PL_WR(WLAN_RF_REG_74_ADDR, (REG_PL_RD(WLAN_RF_REG_74_ADDR) & ~((uint32_t)0x0001E000)) | (((uint32_t)wfvcobandtempbit << 13) & ((uint32_t)0x0001E000)));
}

/**
 * @brief Returns the current value of the wf_vco_band_tail_bit field in the REG_74 register.
 *
 * The REG_74 register will be read and the wf_vco_band_tail_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_band_tail_bit field in the REG_74 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_band_tail_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_74_ADDR);
    return ((localVal & ((uint32_t)0x00001F00)) >> 8);
}

/**
 * @brief Sets the wf_vco_band_tail_bit field of the REG_74 register.
 *
 * The REG_74 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcobandtailbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_band_tail_bit_setf(uint8_t wfvcobandtailbit)
{
    REG_PL_WR(WLAN_RF_REG_74_ADDR, (REG_PL_RD(WLAN_RF_REG_74_ADDR) & ~((uint32_t)0x00001F00)) | (((uint32_t)wfvcobandtailbit << 8) & ((uint32_t)0x00001F00)));
}

/**
 * @brief Returns the current value of the wf_vco_core_reg_bit field in the REG_74 register.
 *
 * The REG_74 register will be read and the wf_vco_core_reg_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_core_reg_bit field in the REG_74 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_core_reg_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_74_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Sets the wf_vco_core_reg_bit field of the REG_74 register.
 *
 * The REG_74 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcocoreregbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_core_reg_bit_setf(uint8_t wfvcocoreregbit)
{
    REG_PL_WR(WLAN_RF_REG_74_ADDR, (REG_PL_RD(WLAN_RF_REG_74_ADDR) & ~((uint32_t)0x000000F0)) | (((uint32_t)wfvcocoreregbit << 4) & ((uint32_t)0x000000F0)));
}

/**
 * @brief Returns the current value of the wf_vco_buf_reg_bit field in the REG_74 register.
 *
 * The REG_74 register will be read and the wf_vco_buf_reg_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_buf_reg_bit field in the REG_74 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_buf_reg_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_74_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the wf_vco_buf_reg_bit field of the REG_74 register.
 *
 * The REG_74 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcobufregbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_buf_reg_bit_setf(uint8_t wfvcobufregbit)
{
    REG_PL_WR(WLAN_RF_REG_74_ADDR, (REG_PL_RD(WLAN_RF_REG_74_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)wfvcobufregbit << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name REG_78 register definitions
 * <table>
 * <caption id="REG_78_BF">REG_78 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>28:24 <td>wf_vco_vctrl_biasp_bit <td>R <td>R/W <td>0xF
 * <tr><td>23:19 <td>wf_vco_vctrl_biasn_bit <td>R <td>R/W <td>0xF
 * <tr><td>18 <td>    wf_vco_lp_mode <td>R <td>R/W <td>0
 * <tr><td>17 <td> wf_vco_presclo_en <td>R <td>R/W <td>1
 * <tr><td>16 <td>   wf_vco_trx_mode <td>R <td>R/W <td>1
 * <tr><td>15 <td>    wf_vco_div2_en <td>R <td>R/W <td>0
 * <tr><td>14 <td> wf_vco_mux_sel_4g <td>R <td>R/W <td>1
 * <tr><td>13 <td>    wf_lo_psw_mode <td>R <td>R/W <td>1
 * <tr><td>12 <td> wf_lo_psw_sf_mode <td>R <td>R/W <td>0
 * <tr><td>11 <td>wf_lo_psw_vref_sel_self_bias <td>R <td>R/W <td>1
 * <tr><td>10:04 <td>wf_lo_psw_sf_avdd_sw_bit <td>R <td>R/W <td>0x20
 * <tr><td>03:00 <td>    wf_lo_rsvd_bit <td>R <td>R/W <td>0xC
 * </table>
 *
 * @{
 */

/// Address of the REG_78 register
#define WLAN_RF_REG_78_ADDR   0x40344078
/// Offset of the REG_78 register from the base address
#define WLAN_RF_REG_78_OFFSET 0x00000078
/// Index of the REG_78 register
#define WLAN_RF_REG_78_INDEX  0x0000001E
/// Reset value of the REG_78 register
#define WLAN_RF_REG_78_RESET  0x0F7B6A0C

/**
 * @brief Returns the current value of the REG_78 register.
 * The REG_78 register will be read and its value returned.
 * @return The current value of the REG_78 register.
 */
__INLINE uint32_t wlan_rf_reg_78_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_78_ADDR);
}

/**
 * @brief Sets the REG_78 register to a value.
 * The REG_78 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_78_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, value);
}

// field definitions
/// WF_VCO_VCTRL_BIASP_BIT field mask
#define WLAN_RF_WF_VCO_VCTRL_BIASP_BIT_MASK         ((uint32_t)0x1F000000)
/// WF_VCO_VCTRL_BIASP_BIT field LSB position
#define WLAN_RF_WF_VCO_VCTRL_BIASP_BIT_LSB          24
/// WF_VCO_VCTRL_BIASP_BIT field width
#define WLAN_RF_WF_VCO_VCTRL_BIASP_BIT_WIDTH        ((uint32_t)0x00000005)
/// WF_VCO_VCTRL_BIASN_BIT field mask
#define WLAN_RF_WF_VCO_VCTRL_BIASN_BIT_MASK         ((uint32_t)0x00F80000)
/// WF_VCO_VCTRL_BIASN_BIT field LSB position
#define WLAN_RF_WF_VCO_VCTRL_BIASN_BIT_LSB          19
/// WF_VCO_VCTRL_BIASN_BIT field width
#define WLAN_RF_WF_VCO_VCTRL_BIASN_BIT_WIDTH        ((uint32_t)0x00000005)
/// WF_VCO_LP_MODE field bit
#define WLAN_RF_WF_VCO_LP_MODE_BIT                  ((uint32_t)0x00040000)
/// WF_VCO_LP_MODE field position
#define WLAN_RF_WF_VCO_LP_MODE_POS                  18
/// WF_VCO_PRESCLO_EN field bit
#define WLAN_RF_WF_VCO_PRESCLO_EN_BIT               ((uint32_t)0x00020000)
/// WF_VCO_PRESCLO_EN field position
#define WLAN_RF_WF_VCO_PRESCLO_EN_POS               17
/// WF_VCO_TRX_MODE field bit
#define WLAN_RF_WF_VCO_TRX_MODE_BIT                 ((uint32_t)0x00010000)
/// WF_VCO_TRX_MODE field position
#define WLAN_RF_WF_VCO_TRX_MODE_POS                 16
/// WF_VCO_DIV_2_EN field bit
#define WLAN_RF_WF_VCO_DIV_2_EN_BIT                 ((uint32_t)0x00008000)
/// WF_VCO_DIV_2_EN field position
#define WLAN_RF_WF_VCO_DIV_2_EN_POS                 15
/// WF_VCO_MUX_SEL__4G field bit
#define WLAN_RF_WF_VCO_MUX_SEL__4G_BIT              ((uint32_t)0x00004000)
/// WF_VCO_MUX_SEL__4G field position
#define WLAN_RF_WF_VCO_MUX_SEL__4G_POS              14
/// WF_LO_PSW_MODE field bit
#define WLAN_RF_WF_LO_PSW_MODE_BIT                  ((uint32_t)0x00002000)
/// WF_LO_PSW_MODE field position
#define WLAN_RF_WF_LO_PSW_MODE_POS                  13
/// WF_LO_PSW_SF_MODE field bit
#define WLAN_RF_WF_LO_PSW_SF_MODE_BIT               ((uint32_t)0x00001000)
/// WF_LO_PSW_SF_MODE field position
#define WLAN_RF_WF_LO_PSW_SF_MODE_POS               12
/// WF_LO_PSW_VREF_SEL_SELF_BIAS field bit
#define WLAN_RF_WF_LO_PSW_VREF_SEL_SELF_BIAS_BIT    ((uint32_t)0x00000800)
/// WF_LO_PSW_VREF_SEL_SELF_BIAS field position
#define WLAN_RF_WF_LO_PSW_VREF_SEL_SELF_BIAS_POS    11
/// WF_LO_PSW_SF_AVDD_SW_BIT field mask
#define WLAN_RF_WF_LO_PSW_SF_AVDD_SW_BIT_MASK       ((uint32_t)0x000007F0)
/// WF_LO_PSW_SF_AVDD_SW_BIT field LSB position
#define WLAN_RF_WF_LO_PSW_SF_AVDD_SW_BIT_LSB        4
/// WF_LO_PSW_SF_AVDD_SW_BIT field width
#define WLAN_RF_WF_LO_PSW_SF_AVDD_SW_BIT_WIDTH      ((uint32_t)0x00000007)
/// WF_LO_RSVD_BIT field mask
#define WLAN_RF_WF_LO_RSVD_BIT_MASK                 ((uint32_t)0x0000000F)
/// WF_LO_RSVD_BIT field LSB position
#define WLAN_RF_WF_LO_RSVD_BIT_LSB                  0
/// WF_LO_RSVD_BIT field width
#define WLAN_RF_WF_LO_RSVD_BIT_WIDTH                ((uint32_t)0x00000004)

/// WF_VCO_VCTRL_BIASP_BIT field reset value
#define WLAN_RF_WF_VCO_VCTRL_BIASP_BIT_RST          0xF
/// WF_VCO_VCTRL_BIASN_BIT field reset value
#define WLAN_RF_WF_VCO_VCTRL_BIASN_BIT_RST          0xF
/// WF_VCO_LP_MODE field reset value
#define WLAN_RF_WF_VCO_LP_MODE_RST                  0x0
/// WF_VCO_PRESCLO_EN field reset value
#define WLAN_RF_WF_VCO_PRESCLO_EN_RST               0x1
/// WF_VCO_TRX_MODE field reset value
#define WLAN_RF_WF_VCO_TRX_MODE_RST                 0x1
/// WF_VCO_DIV_2_EN field reset value
#define WLAN_RF_WF_VCO_DIV_2_EN_RST                 0x0
/// WF_VCO_MUX_SEL__4G field reset value
#define WLAN_RF_WF_VCO_MUX_SEL__4G_RST              0x1
/// WF_LO_PSW_MODE field reset value
#define WLAN_RF_WF_LO_PSW_MODE_RST                  0x1
/// WF_LO_PSW_SF_MODE field reset value
#define WLAN_RF_WF_LO_PSW_SF_MODE_RST               0x0
/// WF_LO_PSW_VREF_SEL_SELF_BIAS field reset value
#define WLAN_RF_WF_LO_PSW_VREF_SEL_SELF_BIAS_RST    0x1
/// WF_LO_PSW_SF_AVDD_SW_BIT field reset value
#define WLAN_RF_WF_LO_PSW_SF_AVDD_SW_BIT_RST        0x20
/// WF_LO_RSVD_BIT field reset value
#define WLAN_RF_WF_LO_RSVD_BIT_RST                  0xC

/**
 * @brief Constructs a value for the REG_78 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfvcovctrlbiaspbit - The value to use for the wf_vco_vctrl_biasp_bit field.
 * @param[in] wfvcovctrlbiasnbit - The value to use for the wf_vco_vctrl_biasn_bit field.
 * @param[in] wfvcolpmode - The value to use for the wf_vco_lp_mode field.
 * @param[in] wfvcoprescloen - The value to use for the wf_vco_presclo_en field.
 * @param[in] wfvcotrxmode - The value to use for the wf_vco_trx_mode field.
 * @param[in] wfvcodiv2en - The value to use for the wf_vco_div2_en field.
 * @param[in] wfvcomuxsel4g - The value to use for the wf_vco_mux_sel_4g field.
 * @param[in] wflopswmode - The value to use for the wf_lo_psw_mode field.
 * @param[in] wflopswsfmode - The value to use for the wf_lo_psw_sf_mode field.
 * @param[in] wflopswvrefselselfbias - The value to use for the wf_lo_psw_vref_sel_self_bias field.
 * @param[in] wflopswsfavddswbit - The value to use for the wf_lo_psw_sf_avdd_sw_bit field.
 * @param[in] wflorsvdbit - The value to use for the wf_lo_rsvd_bit field.
 */
__INLINE void wlan_rf_reg_78_pack(uint8_t wfvcovctrlbiaspbit, uint8_t wfvcovctrlbiasnbit, uint8_t wfvcolpmode, uint8_t wfvcoprescloen, uint8_t wfvcotrxmode, uint8_t wfvcodiv2en, uint8_t wfvcomuxsel4g, uint8_t wflopswmode, uint8_t wflopswsfmode, uint8_t wflopswvrefselselfbias, uint8_t wflopswsfavddswbit, uint8_t wflorsvdbit)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR,  ((uint32_t)wfvcovctrlbiaspbit << 24) | ((uint32_t)wfvcovctrlbiasnbit << 19) | ((uint32_t)wfvcolpmode << 18) | ((uint32_t)wfvcoprescloen << 17) | ((uint32_t)wfvcotrxmode << 16) | ((uint32_t)wfvcodiv2en << 15) | ((uint32_t)wfvcomuxsel4g << 14) | ((uint32_t)wflopswmode << 13) | ((uint32_t)wflopswsfmode << 12) | ((uint32_t)wflopswvrefselselfbias << 11) | ((uint32_t)wflopswsfavddswbit << 4) | ((uint32_t)wflorsvdbit << 0));
}

/**
 * @brief Unpacks REG_78's fields from current value of the REG_78 register.
 *
 * Reads the REG_78 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfvcovctrlbiaspbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcovctrlbiasnbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcolpmode - Will be populated with the current value of this field from the register.
 * @param[out] wfvcoprescloen - Will be populated with the current value of this field from the register.
 * @param[out] wfvcotrxmode - Will be populated with the current value of this field from the register.
 * @param[out] wfvcodiv2en - Will be populated with the current value of this field from the register.
 * @param[out] wfvcomuxsel4g - Will be populated with the current value of this field from the register.
 * @param[out] wflopswmode - Will be populated with the current value of this field from the register.
 * @param[out] wflopswsfmode - Will be populated with the current value of this field from the register.
 * @param[out] wflopswvrefselselfbias - Will be populated with the current value of this field from the register.
 * @param[out] wflopswsfavddswbit - Will be populated with the current value of this field from the register.
 * @param[out] wflorsvdbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_78_unpack(uint8_t* wfvcovctrlbiaspbit, uint8_t* wfvcovctrlbiasnbit, uint8_t* wfvcolpmode, uint8_t* wfvcoprescloen, uint8_t* wfvcotrxmode, uint8_t* wfvcodiv2en, uint8_t* wfvcomuxsel4g, uint8_t* wflopswmode, uint8_t* wflopswsfmode, uint8_t* wflopswvrefselselfbias, uint8_t* wflopswsfavddswbit, uint8_t* wflorsvdbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);

    *wfvcovctrlbiaspbit = (localVal & ((uint32_t)0x1F000000)) >> 24;
    *wfvcovctrlbiasnbit = (localVal & ((uint32_t)0x00F80000)) >> 19;
    *wfvcolpmode = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfvcoprescloen = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wfvcotrxmode = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wfvcodiv2en = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wfvcomuxsel4g = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wflopswmode = (localVal & ((uint32_t)0x00002000)) >> 13;
    *wflopswsfmode = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wflopswvrefselselfbias = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wflopswsfavddswbit = (localVal & ((uint32_t)0x000007F0)) >> 4;
    *wflorsvdbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_vco_vctrl_biasp_bit field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_vco_vctrl_biasp_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_vctrl_biasp_bit field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_vctrl_biasp_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x1F000000)) >> 24);
}

/**
 * @brief Sets the wf_vco_vctrl_biasp_bit field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcovctrlbiaspbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_vctrl_biasp_bit_setf(uint8_t wfvcovctrlbiaspbit)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x1F000000)) | (((uint32_t)wfvcovctrlbiaspbit << 24) & ((uint32_t)0x1F000000)));
}

/**
 * @brief Returns the current value of the wf_vco_vctrl_biasn_bit field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_vco_vctrl_biasn_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_vctrl_biasn_bit field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_vctrl_biasn_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x00F80000)) >> 19);
}

/**
 * @brief Sets the wf_vco_vctrl_biasn_bit field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcovctrlbiasnbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_vctrl_biasn_bit_setf(uint8_t wfvcovctrlbiasnbit)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x00F80000)) | (((uint32_t)wfvcovctrlbiasnbit << 19) & ((uint32_t)0x00F80000)));
}

/**
 * @brief Returns the current value of the wf_vco_lp_mode field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_vco_lp_mode field's value will be returned.
 *
 * @return The current value of the wf_vco_lp_mode field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_lp_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_vco_lp_mode field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcolpmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_lp_mode_setf(uint8_t wfvcolpmode)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wfvcolpmode << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_vco_presclo_en field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_vco_presclo_en field's value will be returned.
 *
 * @return The current value of the wf_vco_presclo_en field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_presclo_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_vco_presclo_en field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcoprescloen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_presclo_en_setf(uint8_t wfvcoprescloen)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wfvcoprescloen << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_vco_trx_mode field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_vco_trx_mode field's value will be returned.
 *
 * @return The current value of the wf_vco_trx_mode field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_trx_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_vco_trx_mode field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcotrxmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_trx_mode_setf(uint8_t wfvcotrxmode)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wfvcotrxmode << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_vco_div2_en field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_vco_div2_en field's value will be returned.
 *
 * @return The current value of the wf_vco_div2_en field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_div_2_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the wf_vco_div2_en field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcodiv2en - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_div_2_en_setf(uint8_t wfvcodiv2en)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)wfvcodiv2en << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the wf_vco_mux_sel_4g field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_vco_mux_sel_4g field's value will be returned.
 *
 * @return The current value of the wf_vco_mux_sel_4g field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_mux_sel__4g_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the wf_vco_mux_sel_4g field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcomuxsel4g - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_mux_sel__4g_setf(uint8_t wfvcomuxsel4g)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)wfvcomuxsel4g << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the wf_lo_psw_mode field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_lo_psw_mode field's value will be returned.
 *
 * @return The current value of the wf_lo_psw_mode field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_lo_psw_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the wf_lo_psw_mode field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflopswmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lo_psw_mode_setf(uint8_t wflopswmode)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)wflopswmode << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the wf_lo_psw_sf_mode field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_lo_psw_sf_mode field's value will be returned.
 *
 * @return The current value of the wf_lo_psw_sf_mode field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_lo_psw_sf_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_lo_psw_sf_mode field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflopswsfmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lo_psw_sf_mode_setf(uint8_t wflopswsfmode)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wflopswsfmode << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the wf_lo_psw_vref_sel_self_bias field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_lo_psw_vref_sel_self_bias field's value will be returned.
 *
 * @return The current value of the wf_lo_psw_vref_sel_self_bias field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_lo_psw_vref_sel_self_bias_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_lo_psw_vref_sel_self_bias field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflopswvrefselselfbias - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lo_psw_vref_sel_self_bias_setf(uint8_t wflopswvrefselselfbias)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wflopswvrefselselfbias << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_lo_psw_sf_avdd_sw_bit field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_lo_psw_sf_avdd_sw_bit field's value will be returned.
 *
 * @return The current value of the wf_lo_psw_sf_avdd_sw_bit field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_lo_psw_sf_avdd_sw_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x000007F0)) >> 4);
}

/**
 * @brief Sets the wf_lo_psw_sf_avdd_sw_bit field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflopswsfavddswbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lo_psw_sf_avdd_sw_bit_setf(uint8_t wflopswsfavddswbit)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x000007F0)) | (((uint32_t)wflopswsfavddswbit << 4) & ((uint32_t)0x000007F0)));
}

/**
 * @brief Returns the current value of the wf_lo_rsvd_bit field in the REG_78 register.
 *
 * The REG_78 register will be read and the wf_lo_rsvd_bit field's value will be returned.
 *
 * @return The current value of the wf_lo_rsvd_bit field in the REG_78 register.
 */
__INLINE uint8_t wlan_rf_wf_lo_rsvd_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_78_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the wf_lo_rsvd_bit field of the REG_78 register.
 *
 * The REG_78 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflorsvdbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lo_rsvd_bit_setf(uint8_t wflorsvdbit)
{
    REG_PL_WR(WLAN_RF_REG_78_ADDR, (REG_PL_RD(WLAN_RF_REG_78_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)wflorsvdbit << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name REG_7C register definitions
 * <table>
 * <caption id="REG_7C_BF">REG_7C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>19:16 <td>wf_lo_rsvd_read_bit <td>W <td>R <td>0x0
 * <tr><td>15:08 <td>       wf_agc_rsvd <td>W <td>R <td>0xF0
 * <tr><td>07:00 <td>       wf_apc_rsvd <td>W <td>R <td>0xF0
 * </table>
 *
 * @{
 */

/// Address of the REG_7C register
#define WLAN_RF_REG_7C_ADDR   0x4034407C
/// Offset of the REG_7C register from the base address
#define WLAN_RF_REG_7C_OFFSET 0x0000007C
/// Index of the REG_7C register
#define WLAN_RF_REG_7C_INDEX  0x0000001F
/// Reset value of the REG_7C register
#define WLAN_RF_REG_7C_RESET  0x0000F0F0

/**
 * @brief Returns the current value of the REG_7C register.
 * The REG_7C register will be read and its value returned.
 * @return The current value of the REG_7C register.
 */
__INLINE uint32_t wlan_rf_reg_7c_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_7C_ADDR);
}

// field definitions
/// WF_LO_RSVD_READ_BIT field mask
#define WLAN_RF_WF_LO_RSVD_READ_BIT_MASK   ((uint32_t)0x000F0000)
/// WF_LO_RSVD_READ_BIT field LSB position
#define WLAN_RF_WF_LO_RSVD_READ_BIT_LSB    16
/// WF_LO_RSVD_READ_BIT field width
#define WLAN_RF_WF_LO_RSVD_READ_BIT_WIDTH  ((uint32_t)0x00000004)
/// WF_AGC_RSVD field mask
#define WLAN_RF_WF_AGC_RSVD_MASK           ((uint32_t)0x0000FF00)
/// WF_AGC_RSVD field LSB position
#define WLAN_RF_WF_AGC_RSVD_LSB            8
/// WF_AGC_RSVD field width
#define WLAN_RF_WF_AGC_RSVD_WIDTH          ((uint32_t)0x00000008)
/// WF_APC_RSVD field mask
#define WLAN_RF_WF_APC_RSVD_MASK           ((uint32_t)0x000000FF)
/// WF_APC_RSVD field LSB position
#define WLAN_RF_WF_APC_RSVD_LSB            0
/// WF_APC_RSVD field width
#define WLAN_RF_WF_APC_RSVD_WIDTH          ((uint32_t)0x00000008)

/// WF_LO_RSVD_READ_BIT field reset value
#define WLAN_RF_WF_LO_RSVD_READ_BIT_RST    0x0
/// WF_AGC_RSVD field reset value
#define WLAN_RF_WF_AGC_RSVD_RST            0xF0
/// WF_APC_RSVD field reset value
#define WLAN_RF_WF_APC_RSVD_RST            0xF0

/**
 * @brief Unpacks REG_7C's fields from current value of the REG_7C register.
 *
 * Reads the REG_7C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wflorsvdreadbit - Will be populated with the current value of this field from the register.
 * @param[out] wfagcrsvd - Will be populated with the current value of this field from the register.
 * @param[out] wfapcrsvd - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_7c_unpack(uint8_t* wflorsvdreadbit, uint8_t* wfagcrsvd, uint8_t* wfapcrsvd)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_7C_ADDR);

    *wflorsvdreadbit = (localVal & ((uint32_t)0x000F0000)) >> 16;
    *wfagcrsvd = (localVal & ((uint32_t)0x0000FF00)) >> 8;
    *wfapcrsvd = (localVal & ((uint32_t)0x000000FF)) >> 0;
}

/**
 * @brief Returns the current value of the wf_lo_rsvd_read_bit field in the REG_7C register.
 *
 * The REG_7C register will be read and the wf_lo_rsvd_read_bit field's value will be returned.
 *
 * @return The current value of the wf_lo_rsvd_read_bit field in the REG_7C register.
 */
__INLINE uint8_t wlan_rf_wf_lo_rsvd_read_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_7C_ADDR);
    return ((localVal & ((uint32_t)0x000F0000)) >> 16);
}

/**
 * @brief Returns the current value of the wf_agc_rsvd field in the REG_7C register.
 *
 * The REG_7C register will be read and the wf_agc_rsvd field's value will be returned.
 *
 * @return The current value of the wf_agc_rsvd field in the REG_7C register.
 */
__INLINE uint8_t wlan_rf_wf_agc_rsvd_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_7C_ADDR);
    return ((localVal & ((uint32_t)0x0000FF00)) >> 8);
}

/**
 * @brief Returns the current value of the wf_apc_rsvd field in the REG_7C register.
 *
 * The REG_7C register will be read and the wf_apc_rsvd field's value will be returned.
 *
 * @return The current value of the wf_apc_rsvd field in the REG_7C register.
 */
__INLINE uint8_t wlan_rf_wf_apc_rsvd_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_7C_ADDR);
    return ((localVal & ((uint32_t)0x000000FF)) >> 0);
}

/// @}

/**
 * @name WF_SOFT_RESET_REG register definitions
 * <table>
 * <caption id="WF_SOFT_RESET_REG_BF">WF_SOFT_RESET_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>00 <td>        soft_reset <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the WF_SOFT_RESET_REG register
#define WLAN_RF_WF_SOFT_RESET_REG_ADDR   0x40344080
/// Offset of the WF_SOFT_RESET_REG register from the base address
#define WLAN_RF_WF_SOFT_RESET_REG_OFFSET 0x00000080
/// Index of the WF_SOFT_RESET_REG register
#define WLAN_RF_WF_SOFT_RESET_REG_INDEX  0x00000020
/// Reset value of the WF_SOFT_RESET_REG register
#define WLAN_RF_WF_SOFT_RESET_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the WF_SOFT_RESET_REG register.
 * The WF_SOFT_RESET_REG register will be read and its value returned.
 * @return The current value of the WF_SOFT_RESET_REG register.
 */
__INLINE uint32_t wlan_rf_wf_soft_reset_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_WF_SOFT_RESET_REG_ADDR);
}

/**
 * @brief Sets the WF_SOFT_RESET_REG register to a value.
 * The WF_SOFT_RESET_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_wf_soft_reset_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_WF_SOFT_RESET_REG_ADDR, value);
}

// field definitions
/// SOFT_RESET field bit
#define WLAN_RF_SOFT_RESET_BIT    ((uint32_t)0x00000001)
/// SOFT_RESET field position
#define WLAN_RF_SOFT_RESET_POS    0

/// SOFT_RESET field reset value
#define WLAN_RF_SOFT_RESET_RST    0x0

/**
 * @brief Returns the current value of the soft_reset field in the WF_SOFT_RESET_REG register.
 *
 * The WF_SOFT_RESET_REG register will be read and the soft_reset field's value will be returned.
 *
 * @return The current value of the soft_reset field in the WF_SOFT_RESET_REG register.
 */
__INLINE uint8_t wlan_rf_soft_reset_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_SOFT_RESET_REG_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the soft_reset field of the WF_SOFT_RESET_REG register.
 *
 * The WF_SOFT_RESET_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] softreset - The value to set the field to.
 */
__INLINE void wlan_rf_soft_reset_setf(uint8_t softreset)
{
    REG_PL_WR(WLAN_RF_WF_SOFT_RESET_REG_ADDR, ((uint32_t)softreset << 0) & ((uint32_t)0x00000001));
}

/// @}

/**
 * @name WF_MISC_CRTL_REG register definitions
 * <table>
 * <caption id="WF_MISC_CRTL_REG_BF">WF_MISC_CRTL_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>16 <td>no_sim_rx_coant_tx <td>R <td>R/W <td>1
 * <tr><td>15:14 <td>  temp_bit_adj_dir <td>R <td>R/W <td>0x1
 * <tr><td>13 <td> wf_pllon_sleep_en <td>R <td>R/W <td>1
 * <tr><td>12 <td>adj_dc_info_mask_clear <td>R <td>R/W <td>0
 * <tr><td>11 <td>adj_dc_update_table <td>R <td>R/W <td>0
 * <tr><td>10:08 <td>       adj_dc_page <td>R <td>R/W <td>0x0
 * <tr><td>07 <td> rxgain_mem_sw_ack <td>W <td>R <td>0
 * <tr><td>06 <td> rxgain_mem_sw_req <td>R <td>R/W <td>0
 * <tr><td>05:03 <td>       rxgain_page <td>R <td>R/W <td>0x1
 * <tr><td>02 <td>       rf_band_sel <td>R <td>R/W <td>0
 * <tr><td>01 <td>         pllon_trx <td>R <td>R/W <td>1
 * <tr><td>00 <td>         pllon_reg <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the WF_MISC_CRTL_REG register
#define WLAN_RF_WF_MISC_CRTL_REG_ADDR   0x40344084
/// Offset of the WF_MISC_CRTL_REG register from the base address
#define WLAN_RF_WF_MISC_CRTL_REG_OFFSET 0x00000084
/// Index of the WF_MISC_CRTL_REG register
#define WLAN_RF_WF_MISC_CRTL_REG_INDEX  0x00000021
/// Reset value of the WF_MISC_CRTL_REG register
#define WLAN_RF_WF_MISC_CRTL_REG_RESET  0x0001600A

/**
 * @brief Returns the current value of the WF_MISC_CRTL_REG register.
 * The WF_MISC_CRTL_REG register will be read and its value returned.
 * @return The current value of the WF_MISC_CRTL_REG register.
 */
__INLINE uint32_t wlan_rf_wf_misc_crtl_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
}

/**
 * @brief Sets the WF_MISC_CRTL_REG register to a value.
 * The WF_MISC_CRTL_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_wf_misc_crtl_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, value);
}

// field definitions
/// NO_SIM_RX_COANT_TX field bit
#define WLAN_RF_NO_SIM_RX_COANT_TX_BIT        ((uint32_t)0x00010000)
/// NO_SIM_RX_COANT_TX field position
#define WLAN_RF_NO_SIM_RX_COANT_TX_POS        16
/// TEMP_BIT_ADJ_DIR field mask
#define WLAN_RF_TEMP_BIT_ADJ_DIR_MASK         ((uint32_t)0x0000C000)
/// TEMP_BIT_ADJ_DIR field LSB position
#define WLAN_RF_TEMP_BIT_ADJ_DIR_LSB          14
/// TEMP_BIT_ADJ_DIR field width
#define WLAN_RF_TEMP_BIT_ADJ_DIR_WIDTH        ((uint32_t)0x00000002)
/// WF_PLLON_SLEEP_EN field bit
#define WLAN_RF_WF_PLLON_SLEEP_EN_BIT         ((uint32_t)0x00002000)
/// WF_PLLON_SLEEP_EN field position
#define WLAN_RF_WF_PLLON_SLEEP_EN_POS         13
/// ADJ_DC_INFO_MASK_CLEAR field bit
#define WLAN_RF_ADJ_DC_INFO_MASK_CLEAR_BIT    ((uint32_t)0x00001000)
/// ADJ_DC_INFO_MASK_CLEAR field position
#define WLAN_RF_ADJ_DC_INFO_MASK_CLEAR_POS    12
/// ADJ_DC_UPDATE_TABLE field bit
#define WLAN_RF_ADJ_DC_UPDATE_TABLE_BIT       ((uint32_t)0x00000800)
/// ADJ_DC_UPDATE_TABLE field position
#define WLAN_RF_ADJ_DC_UPDATE_TABLE_POS       11
/// ADJ_DC_PAGE field mask
#define WLAN_RF_ADJ_DC_PAGE_MASK              ((uint32_t)0x00000700)
/// ADJ_DC_PAGE field LSB position
#define WLAN_RF_ADJ_DC_PAGE_LSB               8
/// ADJ_DC_PAGE field width
#define WLAN_RF_ADJ_DC_PAGE_WIDTH             ((uint32_t)0x00000003)
/// RXGAIN_MEM_SW_ACK field bit
#define WLAN_RF_RXGAIN_MEM_SW_ACK_BIT         ((uint32_t)0x00000080)
/// RXGAIN_MEM_SW_ACK field position
#define WLAN_RF_RXGAIN_MEM_SW_ACK_POS         7
/// RXGAIN_MEM_SW_REQ field bit
#define WLAN_RF_RXGAIN_MEM_SW_REQ_BIT         ((uint32_t)0x00000040)
/// RXGAIN_MEM_SW_REQ field position
#define WLAN_RF_RXGAIN_MEM_SW_REQ_POS         6
/// RXGAIN_PAGE field mask
#define WLAN_RF_RXGAIN_PAGE_MASK              ((uint32_t)0x00000038)
/// RXGAIN_PAGE field LSB position
#define WLAN_RF_RXGAIN_PAGE_LSB               3
/// RXGAIN_PAGE field width
#define WLAN_RF_RXGAIN_PAGE_WIDTH             ((uint32_t)0x00000003)
/// RF_BAND_SEL field bit
#define WLAN_RF_RF_BAND_SEL_BIT               ((uint32_t)0x00000004)
/// RF_BAND_SEL field position
#define WLAN_RF_RF_BAND_SEL_POS               2
/// PLLON_TRX field bit
#define WLAN_RF_PLLON_TRX_BIT                 ((uint32_t)0x00000002)
/// PLLON_TRX field position
#define WLAN_RF_PLLON_TRX_POS                 1
/// PLLON_REG field bit
#define WLAN_RF_PLLON_REG_BIT                 ((uint32_t)0x00000001)
/// PLLON_REG field position
#define WLAN_RF_PLLON_REG_POS                 0

/// NO_SIM_RX_COANT_TX field reset value
#define WLAN_RF_NO_SIM_RX_COANT_TX_RST        0x1
/// TEMP_BIT_ADJ_DIR field reset value
#define WLAN_RF_TEMP_BIT_ADJ_DIR_RST          0x1
/// WF_PLLON_SLEEP_EN field reset value
#define WLAN_RF_WF_PLLON_SLEEP_EN_RST         0x1
/// ADJ_DC_INFO_MASK_CLEAR field reset value
#define WLAN_RF_ADJ_DC_INFO_MASK_CLEAR_RST    0x0
/// ADJ_DC_UPDATE_TABLE field reset value
#define WLAN_RF_ADJ_DC_UPDATE_TABLE_RST       0x0
/// ADJ_DC_PAGE field reset value
#define WLAN_RF_ADJ_DC_PAGE_RST               0x0
/// RXGAIN_MEM_SW_ACK field reset value
#define WLAN_RF_RXGAIN_MEM_SW_ACK_RST         0x0
/// RXGAIN_MEM_SW_REQ field reset value
#define WLAN_RF_RXGAIN_MEM_SW_REQ_RST         0x0
/// RXGAIN_PAGE field reset value
#define WLAN_RF_RXGAIN_PAGE_RST               0x1
/// RF_BAND_SEL field reset value
#define WLAN_RF_RF_BAND_SEL_RST               0x0
/// PLLON_TRX field reset value
#define WLAN_RF_PLLON_TRX_RST                 0x1
/// PLLON_REG field reset value
#define WLAN_RF_PLLON_REG_RST                 0x0

/**
 * @brief Constructs a value for the WF_MISC_CRTL_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] nosimrxcoanttx - The value to use for the no_sim_rx_coant_tx field.
 * @param[in] tempbitadjdir - The value to use for the temp_bit_adj_dir field.
 * @param[in] wfpllonsleepen - The value to use for the wf_pllon_sleep_en field.
 * @param[in] adjdcinfomaskclear - The value to use for the adj_dc_info_mask_clear field.
 * @param[in] adjdcupdatetable - The value to use for the adj_dc_update_table field.
 * @param[in] adjdcpage - The value to use for the adj_dc_page field.
 * @param[in] rxgainmemswreq - The value to use for the rxgain_mem_sw_req field.
 * @param[in] rxgainpage - The value to use for the rxgain_page field.
 * @param[in] rfbandsel - The value to use for the rf_band_sel field.
 * @param[in] pllontrx - The value to use for the pllon_trx field.
 * @param[in] pllonreg - The value to use for the pllon_reg field.
 */
__INLINE void wlan_rf_wf_misc_crtl_reg_pack(uint8_t nosimrxcoanttx, uint8_t tempbitadjdir, uint8_t wfpllonsleepen, uint8_t adjdcinfomaskclear, uint8_t adjdcupdatetable, uint8_t adjdcpage, uint8_t rxgainmemswreq, uint8_t rxgainpage, uint8_t rfbandsel, uint8_t pllontrx, uint8_t pllonreg)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR,  ((uint32_t)nosimrxcoanttx << 16) | ((uint32_t)tempbitadjdir << 14) | ((uint32_t)wfpllonsleepen << 13) | ((uint32_t)adjdcinfomaskclear << 12) | ((uint32_t)adjdcupdatetable << 11) | ((uint32_t)adjdcpage << 8) | ((uint32_t)rxgainmemswreq << 6) | ((uint32_t)rxgainpage << 3) | ((uint32_t)rfbandsel << 2) | ((uint32_t)pllontrx << 1) | ((uint32_t)pllonreg << 0));
}

/**
 * @brief Unpacks WF_MISC_CRTL_REG's fields from current value of the WF_MISC_CRTL_REG register.
 *
 * Reads the WF_MISC_CRTL_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] nosimrxcoanttx - Will be populated with the current value of this field from the register.
 * @param[out] tempbitadjdir - Will be populated with the current value of this field from the register.
 * @param[out] wfpllonsleepen - Will be populated with the current value of this field from the register.
 * @param[out] adjdcinfomaskclear - Will be populated with the current value of this field from the register.
 * @param[out] adjdcupdatetable - Will be populated with the current value of this field from the register.
 * @param[out] adjdcpage - Will be populated with the current value of this field from the register.
 * @param[out] rxgainmemswack - Will be populated with the current value of this field from the register.
 * @param[out] rxgainmemswreq - Will be populated with the current value of this field from the register.
 * @param[out] rxgainpage - Will be populated with the current value of this field from the register.
 * @param[out] rfbandsel - Will be populated with the current value of this field from the register.
 * @param[out] pllontrx - Will be populated with the current value of this field from the register.
 * @param[out] pllonreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_wf_misc_crtl_reg_unpack(uint8_t* nosimrxcoanttx, uint8_t* tempbitadjdir, uint8_t* wfpllonsleepen, uint8_t* adjdcinfomaskclear, uint8_t* adjdcupdatetable, uint8_t* adjdcpage, uint8_t* rxgainmemswack, uint8_t* rxgainmemswreq, uint8_t* rxgainpage, uint8_t* rfbandsel, uint8_t* pllontrx, uint8_t* pllonreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);

    *nosimrxcoanttx = (localVal & ((uint32_t)0x00010000)) >> 16;
    *tempbitadjdir = (localVal & ((uint32_t)0x0000C000)) >> 14;
    *wfpllonsleepen = (localVal & ((uint32_t)0x00002000)) >> 13;
    *adjdcinfomaskclear = (localVal & ((uint32_t)0x00001000)) >> 12;
    *adjdcupdatetable = (localVal & ((uint32_t)0x00000800)) >> 11;
    *adjdcpage = (localVal & ((uint32_t)0x00000700)) >> 8;
    *rxgainmemswack = (localVal & ((uint32_t)0x00000080)) >> 7;
    *rxgainmemswreq = (localVal & ((uint32_t)0x00000040)) >> 6;
    *rxgainpage = (localVal & ((uint32_t)0x00000038)) >> 3;
    *rfbandsel = (localVal & ((uint32_t)0x00000004)) >> 2;
    *pllontrx = (localVal & ((uint32_t)0x00000002)) >> 1;
    *pllonreg = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the no_sim_rx_coant_tx field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the no_sim_rx_coant_tx field's value will be returned.
 *
 * @return The current value of the no_sim_rx_coant_tx field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_no_sim_rx_coant_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the no_sim_rx_coant_tx field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] nosimrxcoanttx - The value to set the field to.
 */
__INLINE void wlan_rf_no_sim_rx_coant_tx_setf(uint8_t nosimrxcoanttx)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)nosimrxcoanttx << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the temp_bit_adj_dir field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the temp_bit_adj_dir field's value will be returned.
 *
 * @return The current value of the temp_bit_adj_dir field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_temp_bit_adj_dir_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000C000)) >> 14);
}

/**
 * @brief Sets the temp_bit_adj_dir field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] tempbitadjdir - The value to set the field to.
 */
__INLINE void wlan_rf_temp_bit_adj_dir_setf(uint8_t tempbitadjdir)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x0000C000)) | (((uint32_t)tempbitadjdir << 14) & ((uint32_t)0x0000C000)));
}

/**
 * @brief Returns the current value of the wf_pllon_sleep_en field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the wf_pllon_sleep_en field's value will be returned.
 *
 * @return The current value of the wf_pllon_sleep_en field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_pllon_sleep_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the wf_pllon_sleep_en field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpllonsleepen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pllon_sleep_en_setf(uint8_t wfpllonsleepen)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)wfpllonsleepen << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the adj_dc_info_mask_clear field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the adj_dc_info_mask_clear field's value will be returned.
 *
 * @return The current value of the adj_dc_info_mask_clear field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_adj_dc_info_mask_clear_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the adj_dc_info_mask_clear field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] adjdcinfomaskclear - The value to set the field to.
 */
__INLINE void wlan_rf_adj_dc_info_mask_clear_setf(uint8_t adjdcinfomaskclear)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)adjdcinfomaskclear << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the adj_dc_update_table field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the adj_dc_update_table field's value will be returned.
 *
 * @return The current value of the adj_dc_update_table field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_adj_dc_update_table_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the adj_dc_update_table field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] adjdcupdatetable - The value to set the field to.
 */
__INLINE void wlan_rf_adj_dc_update_table_setf(uint8_t adjdcupdatetable)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)adjdcupdatetable << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the adj_dc_page field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the adj_dc_page field's value will be returned.
 *
 * @return The current value of the adj_dc_page field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_adj_dc_page_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

/**
 * @brief Sets the adj_dc_page field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] adjdcpage - The value to set the field to.
 */
__INLINE void wlan_rf_adj_dc_page_setf(uint8_t adjdcpage)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00000700)) | (((uint32_t)adjdcpage << 8) & ((uint32_t)0x00000700)));
}

/**
 * @brief Returns the current value of the rxgain_mem_sw_ack field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the rxgain_mem_sw_ack field's value will be returned.
 *
 * @return The current value of the rxgain_mem_sw_ack field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_rxgain_mem_sw_ack_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Returns the current value of the rxgain_mem_sw_req field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the rxgain_mem_sw_req field's value will be returned.
 *
 * @return The current value of the rxgain_mem_sw_req field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_rxgain_mem_sw_req_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the rxgain_mem_sw_req field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainmemswreq - The value to set the field to.
 */
__INLINE void wlan_rf_rxgain_mem_sw_req_setf(uint8_t rxgainmemswreq)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)rxgainmemswreq << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the rxgain_page field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the rxgain_page field's value will be returned.
 *
 * @return The current value of the rxgain_page field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_rxgain_page_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000038)) >> 3);
}

/**
 * @brief Sets the rxgain_page field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainpage - The value to set the field to.
 */
__INLINE void wlan_rf_rxgain_page_setf(uint8_t rxgainpage)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00000038)) | (((uint32_t)rxgainpage << 3) & ((uint32_t)0x00000038)));
}

/**
 * @brief Returns the current value of the rf_band_sel field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the rf_band_sel field's value will be returned.
 *
 * @return The current value of the rf_band_sel field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_rf_band_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the rf_band_sel field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rfbandsel - The value to set the field to.
 */
__INLINE void wlan_rf_rf_band_sel_setf(uint8_t rfbandsel)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)rfbandsel << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the pllon_trx field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the pllon_trx field's value will be returned.
 *
 * @return The current value of the pllon_trx field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_pllon_trx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the pllon_trx field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] pllontrx - The value to set the field to.
 */
__INLINE void wlan_rf_pllon_trx_setf(uint8_t pllontrx)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)pllontrx << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the pllon_reg field in the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read and the pllon_reg field's value will be returned.
 *
 * @return The current value of the pllon_reg field in the WF_MISC_CRTL_REG register.
 */
__INLINE uint8_t wlan_rf_pllon_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the pllon_reg field of the WF_MISC_CRTL_REG register.
 *
 * The WF_MISC_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] pllonreg - The value to set the field to.
 */
__INLINE void wlan_rf_pllon_reg_setf(uint8_t pllonreg)
{
    REG_PL_WR(WLAN_RF_WF_MISC_CRTL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MISC_CRTL_REG_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)pllonreg << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name WF_MAN_CTRL_REG register definitions
 * <table>
 * <caption id="WF_MAN_CTRL_REG_BF">WF_MAN_CTRL_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>26 <td>          bttws_dr <td>R <td>R/W <td>0
 * <tr><td>25 <td>         bttws_reg <td>R <td>R/W <td>0
 * <tr><td>24 <td>           bton_dr <td>R <td>R/W <td>1
 * <tr><td>23 <td>          bton_reg <td>R <td>R/W <td>0
 * <tr><td>22 <td>           txon_dr <td>R <td>R/W <td>0
 * <tr><td>21 <td>          txon_reg <td>R <td>R/W <td>0
 * <tr><td>20 <td>           rxon_dr <td>R <td>R/W <td>0
 * <tr><td>19 <td>          rxon_reg <td>R <td>R/W <td>0
 * <tr><td>18 <td>  rx_gain_dr_pulse <td>R <td>R/W <td>0
 * <tr><td>17 <td>        rx_gain_dr <td>R <td>R/W <td>0
 * <tr><td>16:08 <td>       rx_gain_reg <td>R <td>R/W <td>0x0
 * <tr><td>07 <td>  tx_gain_dr_pulse <td>R <td>R/W <td>0
 * <tr><td>06 <td>        tx_gain_dr <td>R <td>R/W <td>0
 * <tr><td>05:00 <td>       tx_gain_reg <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the WF_MAN_CTRL_REG register
#define WLAN_RF_WF_MAN_CTRL_REG_ADDR   0x40344088
/// Offset of the WF_MAN_CTRL_REG register from the base address
#define WLAN_RF_WF_MAN_CTRL_REG_OFFSET 0x00000088
/// Index of the WF_MAN_CTRL_REG register
#define WLAN_RF_WF_MAN_CTRL_REG_INDEX  0x00000022
/// Reset value of the WF_MAN_CTRL_REG register
#define WLAN_RF_WF_MAN_CTRL_REG_RESET  0x01000000

/**
 * @brief Returns the current value of the WF_MAN_CTRL_REG register.
 * The WF_MAN_CTRL_REG register will be read and its value returned.
 * @return The current value of the WF_MAN_CTRL_REG register.
 */
__INLINE uint32_t wlan_rf_wf_man_ctrl_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
}

/**
 * @brief Sets the WF_MAN_CTRL_REG register to a value.
 * The WF_MAN_CTRL_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_wf_man_ctrl_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, value);
}

// field definitions
/// BTTWS_DR field bit
#define WLAN_RF_BTTWS_DR_BIT            ((uint32_t)0x04000000)
/// BTTWS_DR field position
#define WLAN_RF_BTTWS_DR_POS            26
/// BTTWS_REG field bit
#define WLAN_RF_BTTWS_REG_BIT           ((uint32_t)0x02000000)
/// BTTWS_REG field position
#define WLAN_RF_BTTWS_REG_POS           25
/// BTON_DR field bit
#define WLAN_RF_BTON_DR_BIT             ((uint32_t)0x01000000)
/// BTON_DR field position
#define WLAN_RF_BTON_DR_POS             24
/// BTON_REG field bit
#define WLAN_RF_BTON_REG_BIT            ((uint32_t)0x00800000)
/// BTON_REG field position
#define WLAN_RF_BTON_REG_POS            23
/// TXON_DR field bit
#define WLAN_RF_TXON_DR_BIT             ((uint32_t)0x00400000)
/// TXON_DR field position
#define WLAN_RF_TXON_DR_POS             22
/// TXON_REG field bit
#define WLAN_RF_TXON_REG_BIT            ((uint32_t)0x00200000)
/// TXON_REG field position
#define WLAN_RF_TXON_REG_POS            21
/// RXON_DR field bit
#define WLAN_RF_RXON_DR_BIT             ((uint32_t)0x00100000)
/// RXON_DR field position
#define WLAN_RF_RXON_DR_POS             20
/// RXON_REG field bit
#define WLAN_RF_RXON_REG_BIT            ((uint32_t)0x00080000)
/// RXON_REG field position
#define WLAN_RF_RXON_REG_POS            19
/// RX_GAIN_DR_PULSE field bit
#define WLAN_RF_RX_GAIN_DR_PULSE_BIT    ((uint32_t)0x00040000)
/// RX_GAIN_DR_PULSE field position
#define WLAN_RF_RX_GAIN_DR_PULSE_POS    18
/// RX_GAIN_DR field bit
#define WLAN_RF_RX_GAIN_DR_BIT          ((uint32_t)0x00020000)
/// RX_GAIN_DR field position
#define WLAN_RF_RX_GAIN_DR_POS          17
/// RX_GAIN_REG field mask
#define WLAN_RF_RX_GAIN_REG_MASK        ((uint32_t)0x0001FF00)
/// RX_GAIN_REG field LSB position
#define WLAN_RF_RX_GAIN_REG_LSB         8
/// RX_GAIN_REG field width
#define WLAN_RF_RX_GAIN_REG_WIDTH       ((uint32_t)0x00000009)
/// TX_GAIN_DR_PULSE field bit
#define WLAN_RF_TX_GAIN_DR_PULSE_BIT    ((uint32_t)0x00000080)
/// TX_GAIN_DR_PULSE field position
#define WLAN_RF_TX_GAIN_DR_PULSE_POS    7
/// TX_GAIN_DR field bit
#define WLAN_RF_TX_GAIN_DR_BIT          ((uint32_t)0x00000040)
/// TX_GAIN_DR field position
#define WLAN_RF_TX_GAIN_DR_POS          6
/// TX_GAIN_REG field mask
#define WLAN_RF_TX_GAIN_REG_MASK        ((uint32_t)0x0000003F)
/// TX_GAIN_REG field LSB position
#define WLAN_RF_TX_GAIN_REG_LSB         0
/// TX_GAIN_REG field width
#define WLAN_RF_TX_GAIN_REG_WIDTH       ((uint32_t)0x00000006)

/// BTTWS_DR field reset value
#define WLAN_RF_BTTWS_DR_RST            0x0
/// BTTWS_REG field reset value
#define WLAN_RF_BTTWS_REG_RST           0x0
/// BTON_DR field reset value
#define WLAN_RF_BTON_DR_RST             0x1
/// BTON_REG field reset value
#define WLAN_RF_BTON_REG_RST            0x0
/// TXON_DR field reset value
#define WLAN_RF_TXON_DR_RST             0x0
/// TXON_REG field reset value
#define WLAN_RF_TXON_REG_RST            0x0
/// RXON_DR field reset value
#define WLAN_RF_RXON_DR_RST             0x0
/// RXON_REG field reset value
#define WLAN_RF_RXON_REG_RST            0x0
/// RX_GAIN_DR_PULSE field reset value
#define WLAN_RF_RX_GAIN_DR_PULSE_RST    0x0
/// RX_GAIN_DR field reset value
#define WLAN_RF_RX_GAIN_DR_RST          0x0
/// RX_GAIN_REG field reset value
#define WLAN_RF_RX_GAIN_REG_RST         0x0
/// TX_GAIN_DR_PULSE field reset value
#define WLAN_RF_TX_GAIN_DR_PULSE_RST    0x0
/// TX_GAIN_DR field reset value
#define WLAN_RF_TX_GAIN_DR_RST          0x0
/// TX_GAIN_REG field reset value
#define WLAN_RF_TX_GAIN_REG_RST         0x0

/**
 * @brief Constructs a value for the WF_MAN_CTRL_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] bttwsdr - The value to use for the bttws_dr field.
 * @param[in] bttwsreg - The value to use for the bttws_reg field.
 * @param[in] btondr - The value to use for the bton_dr field.
 * @param[in] btonreg - The value to use for the bton_reg field.
 * @param[in] txondr - The value to use for the txon_dr field.
 * @param[in] txonreg - The value to use for the txon_reg field.
 * @param[in] rxondr - The value to use for the rxon_dr field.
 * @param[in] rxonreg - The value to use for the rxon_reg field.
 * @param[in] rxgaindrpulse - The value to use for the rx_gain_dr_pulse field.
 * @param[in] rxgaindr - The value to use for the rx_gain_dr field.
 * @param[in] rxgainreg - The value to use for the rx_gain_reg field.
 * @param[in] txgaindrpulse - The value to use for the tx_gain_dr_pulse field.
 * @param[in] txgaindr - The value to use for the tx_gain_dr field.
 * @param[in] txgainreg - The value to use for the tx_gain_reg field.
 */
__INLINE void wlan_rf_wf_man_ctrl_reg_pack(uint8_t bttwsdr, uint8_t bttwsreg, uint8_t btondr, uint8_t btonreg, uint8_t txondr, uint8_t txonreg, uint8_t rxondr, uint8_t rxonreg, uint8_t rxgaindrpulse, uint8_t rxgaindr, uint16_t rxgainreg, uint8_t txgaindrpulse, uint8_t txgaindr, uint8_t txgainreg)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR,  ((uint32_t)bttwsdr << 26) | ((uint32_t)bttwsreg << 25) | ((uint32_t)btondr << 24) | ((uint32_t)btonreg << 23) | ((uint32_t)txondr << 22) | ((uint32_t)txonreg << 21) | ((uint32_t)rxondr << 20) | ((uint32_t)rxonreg << 19) | ((uint32_t)rxgaindrpulse << 18) | ((uint32_t)rxgaindr << 17) | ((uint32_t)rxgainreg << 8) | ((uint32_t)txgaindrpulse << 7) | ((uint32_t)txgaindr << 6) | ((uint32_t)txgainreg << 0));
}

/**
 * @brief Unpacks WF_MAN_CTRL_REG's fields from current value of the WF_MAN_CTRL_REG register.
 *
 * Reads the WF_MAN_CTRL_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] bttwsdr - Will be populated with the current value of this field from the register.
 * @param[out] bttwsreg - Will be populated with the current value of this field from the register.
 * @param[out] btondr - Will be populated with the current value of this field from the register.
 * @param[out] btonreg - Will be populated with the current value of this field from the register.
 * @param[out] txondr - Will be populated with the current value of this field from the register.
 * @param[out] txonreg - Will be populated with the current value of this field from the register.
 * @param[out] rxondr - Will be populated with the current value of this field from the register.
 * @param[out] rxonreg - Will be populated with the current value of this field from the register.
 * @param[out] rxgaindrpulse - Will be populated with the current value of this field from the register.
 * @param[out] rxgaindr - Will be populated with the current value of this field from the register.
 * @param[out] rxgainreg - Will be populated with the current value of this field from the register.
 * @param[out] txgaindrpulse - Will be populated with the current value of this field from the register.
 * @param[out] txgaindr - Will be populated with the current value of this field from the register.
 * @param[out] txgainreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_wf_man_ctrl_reg_unpack(uint8_t* bttwsdr, uint8_t* bttwsreg, uint8_t* btondr, uint8_t* btonreg, uint8_t* txondr, uint8_t* txonreg, uint8_t* rxondr, uint8_t* rxonreg, uint8_t* rxgaindrpulse, uint8_t* rxgaindr, uint16_t* rxgainreg, uint8_t* txgaindrpulse, uint8_t* txgaindr, uint8_t* txgainreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);

    *bttwsdr = (localVal & ((uint32_t)0x04000000)) >> 26;
    *bttwsreg = (localVal & ((uint32_t)0x02000000)) >> 25;
    *btondr = (localVal & ((uint32_t)0x01000000)) >> 24;
    *btonreg = (localVal & ((uint32_t)0x00800000)) >> 23;
    *txondr = (localVal & ((uint32_t)0x00400000)) >> 22;
    *txonreg = (localVal & ((uint32_t)0x00200000)) >> 21;
    *rxondr = (localVal & ((uint32_t)0x00100000)) >> 20;
    *rxonreg = (localVal & ((uint32_t)0x00080000)) >> 19;
    *rxgaindrpulse = (localVal & ((uint32_t)0x00040000)) >> 18;
    *rxgaindr = (localVal & ((uint32_t)0x00020000)) >> 17;
    *rxgainreg = (localVal & ((uint32_t)0x0001FF00)) >> 8;
    *txgaindrpulse = (localVal & ((uint32_t)0x00000080)) >> 7;
    *txgaindr = (localVal & ((uint32_t)0x00000040)) >> 6;
    *txgainreg = (localVal & ((uint32_t)0x0000003F)) >> 0;
}

/**
 * @brief Returns the current value of the bttws_dr field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the bttws_dr field's value will be returned.
 *
 * @return The current value of the bttws_dr field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_bttws_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the bttws_dr field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttwsdr - The value to set the field to.
 */
__INLINE void wlan_rf_bttws_dr_setf(uint8_t bttwsdr)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)bttwsdr << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the bttws_reg field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the bttws_reg field's value will be returned.
 *
 * @return The current value of the bttws_reg field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_bttws_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the bttws_reg field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttwsreg - The value to set the field to.
 */
__INLINE void wlan_rf_bttws_reg_setf(uint8_t bttwsreg)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)bttwsreg << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the bton_dr field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the bton_dr field's value will be returned.
 *
 * @return The current value of the bton_dr field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_bton_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the bton_dr field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btondr - The value to set the field to.
 */
__INLINE void wlan_rf_bton_dr_setf(uint8_t btondr)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)btondr << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the bton_reg field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the bton_reg field's value will be returned.
 *
 * @return The current value of the bton_reg field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_bton_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the bton_reg field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btonreg - The value to set the field to.
 */
__INLINE void wlan_rf_bton_reg_setf(uint8_t btonreg)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)btonreg << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the txon_dr field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the txon_dr field's value will be returned.
 *
 * @return The current value of the txon_dr field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_txon_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the txon_dr field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txondr - The value to set the field to.
 */
__INLINE void wlan_rf_txon_dr_setf(uint8_t txondr)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)txondr << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the txon_reg field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the txon_reg field's value will be returned.
 *
 * @return The current value of the txon_reg field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_txon_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Sets the txon_reg field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txonreg - The value to set the field to.
 */
__INLINE void wlan_rf_txon_reg_setf(uint8_t txonreg)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x00200000)) | (((uint32_t)txonreg << 21) & ((uint32_t)0x00200000)));
}

/**
 * @brief Returns the current value of the rxon_dr field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the rxon_dr field's value will be returned.
 *
 * @return The current value of the rxon_dr field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_rxon_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the rxon_dr field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxondr - The value to set the field to.
 */
__INLINE void wlan_rf_rxon_dr_setf(uint8_t rxondr)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)rxondr << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the rxon_reg field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the rxon_reg field's value will be returned.
 *
 * @return The current value of the rxon_reg field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_rxon_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the rxon_reg field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxonreg - The value to set the field to.
 */
__INLINE void wlan_rf_rxon_reg_setf(uint8_t rxonreg)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)rxonreg << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the rx_gain_dr_pulse field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the rx_gain_dr_pulse field's value will be returned.
 *
 * @return The current value of the rx_gain_dr_pulse field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_rx_gain_dr_pulse_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the rx_gain_dr_pulse field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgaindrpulse - The value to set the field to.
 */
__INLINE void wlan_rf_rx_gain_dr_pulse_setf(uint8_t rxgaindrpulse)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)rxgaindrpulse << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the rx_gain_dr field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the rx_gain_dr field's value will be returned.
 *
 * @return The current value of the rx_gain_dr field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_rx_gain_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the rx_gain_dr field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgaindr - The value to set the field to.
 */
__INLINE void wlan_rf_rx_gain_dr_setf(uint8_t rxgaindr)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)rxgaindr << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the rx_gain_reg field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the rx_gain_reg field's value will be returned.
 *
 * @return The current value of the rx_gain_reg field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint16_t wlan_rf_rx_gain_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x0001FF00)) >> 8);
}

/**
 * @brief Sets the rx_gain_reg field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainreg - The value to set the field to.
 */
__INLINE void wlan_rf_rx_gain_reg_setf(uint16_t rxgainreg)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x0001FF00)) | (((uint32_t)rxgainreg << 8) & ((uint32_t)0x0001FF00)));
}

/**
 * @brief Returns the current value of the tx_gain_dr_pulse field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the tx_gain_dr_pulse field's value will be returned.
 *
 * @return The current value of the tx_gain_dr_pulse field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_tx_gain_dr_pulse_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the tx_gain_dr_pulse field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgaindrpulse - The value to set the field to.
 */
__INLINE void wlan_rf_tx_gain_dr_pulse_setf(uint8_t txgaindrpulse)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)txgaindrpulse << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the tx_gain_dr field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the tx_gain_dr field's value will be returned.
 *
 * @return The current value of the tx_gain_dr field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_tx_gain_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the tx_gain_dr field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgaindr - The value to set the field to.
 */
__INLINE void wlan_rf_tx_gain_dr_setf(uint8_t txgaindr)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)txgaindr << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the tx_gain_reg field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the tx_gain_reg field's value will be returned.
 *
 * @return The current value of the tx_gain_reg field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_tx_gain_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000003F)) >> 0);
}

/**
 * @brief Sets the tx_gain_reg field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgainreg - The value to set the field to.
 */
__INLINE void wlan_rf_tx_gain_reg_setf(uint8_t txgainreg)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x0000003F)) | (((uint32_t)txgainreg << 0) & ((uint32_t)0x0000003F)));
}

/// @}

/**
 * @name WF_CALCLK_REG register definitions
 * <table>
 * <caption id="WF_CALCLK_REG_BF">WF_CALCLK_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>23 <td>     vco_loen_ctrl <td>R <td>R/W <td>0
 * <tr><td>22:17 <td>cal_clk_div_num_p2 <td>R <td>R/W <td>0x13
 * <tr><td>16:11 <td>cal_clk_div_num_p1 <td>R <td>R/W <td>0x6
 * <tr><td>10 <td>        cal_clk_en <td>R <td>R/W <td>0
 * <tr><td>09:00 <td>   cal_clk_div_num <td>R <td>R/W <td>0x4F
 * </table>
 *
 * @{
 */

/// Address of the WF_CALCLK_REG register
#define WLAN_RF_WF_CALCLK_REG_ADDR   0x4034408C
/// Offset of the WF_CALCLK_REG register from the base address
#define WLAN_RF_WF_CALCLK_REG_OFFSET 0x0000008C
/// Index of the WF_CALCLK_REG register
#define WLAN_RF_WF_CALCLK_REG_INDEX  0x00000023
/// Reset value of the WF_CALCLK_REG register
#define WLAN_RF_WF_CALCLK_REG_RESET  0x0026304F

/**
 * @brief Returns the current value of the WF_CALCLK_REG register.
 * The WF_CALCLK_REG register will be read and its value returned.
 * @return The current value of the WF_CALCLK_REG register.
 */
__INLINE uint32_t wlan_rf_wf_calclk_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);
}

/**
 * @brief Sets the WF_CALCLK_REG register to a value.
 * The WF_CALCLK_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_wf_calclk_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR, value);
}

// field definitions
/// VCO_LOEN_CTRL field bit
#define WLAN_RF_VCO_LOEN_CTRL_BIT          ((uint32_t)0x00800000)
/// VCO_LOEN_CTRL field position
#define WLAN_RF_VCO_LOEN_CTRL_POS          23
/// CAL_CLK_DIV_NUM_P_2 field mask
#define WLAN_RF_CAL_CLK_DIV_NUM_P_2_MASK   ((uint32_t)0x007E0000)
/// CAL_CLK_DIV_NUM_P_2 field LSB position
#define WLAN_RF_CAL_CLK_DIV_NUM_P_2_LSB    17
/// CAL_CLK_DIV_NUM_P_2 field width
#define WLAN_RF_CAL_CLK_DIV_NUM_P_2_WIDTH  ((uint32_t)0x00000006)
/// CAL_CLK_DIV_NUM_P_1 field mask
#define WLAN_RF_CAL_CLK_DIV_NUM_P_1_MASK   ((uint32_t)0x0001F800)
/// CAL_CLK_DIV_NUM_P_1 field LSB position
#define WLAN_RF_CAL_CLK_DIV_NUM_P_1_LSB    11
/// CAL_CLK_DIV_NUM_P_1 field width
#define WLAN_RF_CAL_CLK_DIV_NUM_P_1_WIDTH  ((uint32_t)0x00000006)
/// CAL_CLK_EN field bit
#define WLAN_RF_CAL_CLK_EN_BIT             ((uint32_t)0x00000400)
/// CAL_CLK_EN field position
#define WLAN_RF_CAL_CLK_EN_POS             10
/// CAL_CLK_DIV_NUM field mask
#define WLAN_RF_CAL_CLK_DIV_NUM_MASK       ((uint32_t)0x000003FF)
/// CAL_CLK_DIV_NUM field LSB position
#define WLAN_RF_CAL_CLK_DIV_NUM_LSB        0
/// CAL_CLK_DIV_NUM field width
#define WLAN_RF_CAL_CLK_DIV_NUM_WIDTH      ((uint32_t)0x0000000A)

/// VCO_LOEN_CTRL field reset value
#define WLAN_RF_VCO_LOEN_CTRL_RST          0x0
/// CAL_CLK_DIV_NUM_P_2 field reset value
#define WLAN_RF_CAL_CLK_DIV_NUM_P_2_RST    0x13
/// CAL_CLK_DIV_NUM_P_1 field reset value
#define WLAN_RF_CAL_CLK_DIV_NUM_P_1_RST    0x6
/// CAL_CLK_EN field reset value
#define WLAN_RF_CAL_CLK_EN_RST             0x0
/// CAL_CLK_DIV_NUM field reset value
#define WLAN_RF_CAL_CLK_DIV_NUM_RST        0x4F

/**
 * @brief Constructs a value for the WF_CALCLK_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] vcoloenctrl - The value to use for the vco_loen_ctrl field.
 * @param[in] calclkdivnump2 - The value to use for the cal_clk_div_num_p2 field.
 * @param[in] calclkdivnump1 - The value to use for the cal_clk_div_num_p1 field.
 * @param[in] calclken - The value to use for the cal_clk_en field.
 * @param[in] calclkdivnum - The value to use for the cal_clk_div_num field.
 */
__INLINE void wlan_rf_wf_calclk_reg_pack(uint8_t vcoloenctrl, uint8_t calclkdivnump2, uint8_t calclkdivnump1, uint8_t calclken, uint16_t calclkdivnum)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR,  ((uint32_t)vcoloenctrl << 23) | ((uint32_t)calclkdivnump2 << 17) | ((uint32_t)calclkdivnump1 << 11) | ((uint32_t)calclken << 10) | ((uint32_t)calclkdivnum << 0));
}

/**
 * @brief Unpacks WF_CALCLK_REG's fields from current value of the WF_CALCLK_REG register.
 *
 * Reads the WF_CALCLK_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] vcoloenctrl - Will be populated with the current value of this field from the register.
 * @param[out] calclkdivnump2 - Will be populated with the current value of this field from the register.
 * @param[out] calclkdivnump1 - Will be populated with the current value of this field from the register.
 * @param[out] calclken - Will be populated with the current value of this field from the register.
 * @param[out] calclkdivnum - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_wf_calclk_reg_unpack(uint8_t* vcoloenctrl, uint8_t* calclkdivnump2, uint8_t* calclkdivnump1, uint8_t* calclken, uint16_t* calclkdivnum)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);

    *vcoloenctrl = (localVal & ((uint32_t)0x00800000)) >> 23;
    *calclkdivnump2 = (localVal & ((uint32_t)0x007E0000)) >> 17;
    *calclkdivnump1 = (localVal & ((uint32_t)0x0001F800)) >> 11;
    *calclken = (localVal & ((uint32_t)0x00000400)) >> 10;
    *calclkdivnum = (localVal & ((uint32_t)0x000003FF)) >> 0;
}

/**
 * @brief Returns the current value of the vco_loen_ctrl field in the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read and the vco_loen_ctrl field's value will be returned.
 *
 * @return The current value of the vco_loen_ctrl field in the WF_CALCLK_REG register.
 */
__INLINE uint8_t wlan_rf_vco_loen_ctrl_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the vco_loen_ctrl field of the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] vcoloenctrl - The value to set the field to.
 */
__INLINE void wlan_rf_vco_loen_ctrl_setf(uint8_t vcoloenctrl)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)vcoloenctrl << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the cal_clk_div_num_p2 field in the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read and the cal_clk_div_num_p2 field's value will be returned.
 *
 * @return The current value of the cal_clk_div_num_p2 field in the WF_CALCLK_REG register.
 */
__INLINE uint8_t wlan_rf_cal_clk_div_num_p_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x007E0000)) >> 17);
}

/**
 * @brief Sets the cal_clk_div_num_p2 field of the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] calclkdivnump2 - The value to set the field to.
 */
__INLINE void wlan_rf_cal_clk_div_num_p_2_setf(uint8_t calclkdivnump2)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR) & ~((uint32_t)0x007E0000)) | (((uint32_t)calclkdivnump2 << 17) & ((uint32_t)0x007E0000)));
}

/**
 * @brief Returns the current value of the cal_clk_div_num_p1 field in the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read and the cal_clk_div_num_p1 field's value will be returned.
 *
 * @return The current value of the cal_clk_div_num_p1 field in the WF_CALCLK_REG register.
 */
__INLINE uint8_t wlan_rf_cal_clk_div_num_p_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x0001F800)) >> 11);
}

/**
 * @brief Sets the cal_clk_div_num_p1 field of the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] calclkdivnump1 - The value to set the field to.
 */
__INLINE void wlan_rf_cal_clk_div_num_p_1_setf(uint8_t calclkdivnump1)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR) & ~((uint32_t)0x0001F800)) | (((uint32_t)calclkdivnump1 << 11) & ((uint32_t)0x0001F800)));
}

/**
 * @brief Returns the current value of the cal_clk_en field in the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read and the cal_clk_en field's value will be returned.
 *
 * @return The current value of the cal_clk_en field in the WF_CALCLK_REG register.
 */
__INLINE uint8_t wlan_rf_cal_clk_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the cal_clk_en field of the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] calclken - The value to set the field to.
 */
__INLINE void wlan_rf_cal_clk_en_setf(uint8_t calclken)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)calclken << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the cal_clk_div_num field in the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read and the cal_clk_div_num field's value will be returned.
 *
 * @return The current value of the cal_clk_div_num field in the WF_CALCLK_REG register.
 */
__INLINE uint16_t wlan_rf_cal_clk_div_num_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x000003FF)) >> 0);
}

/**
 * @brief Sets the cal_clk_div_num field of the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] calclkdivnum - The value to set the field to.
 */
__INLINE void wlan_rf_cal_clk_div_num_setf(uint16_t calclkdivnum)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR) & ~((uint32_t)0x000003FF)) | (((uint32_t)calclkdivnum << 0) & ((uint32_t)0x000003FF)));
}

/// @}

/**
 * @name WF_EXT_TRXON_DELAY_REG register definitions
 * <table>
 * <caption id="WF_EXT_TRXON_DELAY_REG_BF">WF_EXT_TRXON_DELAY_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30 <td>  ext_pa_ctrl_mode <td>R <td>R/W <td>0
 * <tr><td>29:21 <td>    ext_rxon_delay <td>R <td>R/W <td>0x87
 * <tr><td>20:12 <td>    ext_txon_delay <td>R <td>R/W <td>0x41
 * <tr><td>11:08 <td>ext_pa_rx_ctrl_reg <td>R <td>R/W <td>0x5
 * <tr><td>07:04 <td>ext_pa_tx_ctrl_reg <td>R <td>R/W <td>0x2
 * <tr><td>03:00 <td>ext_pa_idle_ctrl_reg <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the WF_EXT_TRXON_DELAY_REG register
#define WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR   0x40344090
/// Offset of the WF_EXT_TRXON_DELAY_REG register from the base address
#define WLAN_RF_WF_EXT_TRXON_DELAY_REG_OFFSET 0x00000090
/// Index of the WF_EXT_TRXON_DELAY_REG register
#define WLAN_RF_WF_EXT_TRXON_DELAY_REG_INDEX  0x00000024
/// Reset value of the WF_EXT_TRXON_DELAY_REG register
#define WLAN_RF_WF_EXT_TRXON_DELAY_REG_RESET  0x10E41520

/**
 * @brief Returns the current value of the WF_EXT_TRXON_DELAY_REG register.
 * The WF_EXT_TRXON_DELAY_REG register will be read and its value returned.
 * @return The current value of the WF_EXT_TRXON_DELAY_REG register.
 */
__INLINE uint32_t wlan_rf_wf_ext_trxon_delay_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR);
}

/**
 * @brief Sets the WF_EXT_TRXON_DELAY_REG register to a value.
 * The WF_EXT_TRXON_DELAY_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_wf_ext_trxon_delay_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR, value);
}

// field definitions
/// EXT_PA_CTRL_MODE field bit
#define WLAN_RF_EXT_PA_CTRL_MODE_BIT        ((uint32_t)0x40000000)
/// EXT_PA_CTRL_MODE field position
#define WLAN_RF_EXT_PA_CTRL_MODE_POS        30
/// EXT_RXON_DELAY field mask
#define WLAN_RF_EXT_RXON_DELAY_MASK         ((uint32_t)0x3FE00000)
/// EXT_RXON_DELAY field LSB position
#define WLAN_RF_EXT_RXON_DELAY_LSB          21
/// EXT_RXON_DELAY field width
#define WLAN_RF_EXT_RXON_DELAY_WIDTH        ((uint32_t)0x00000009)
/// EXT_TXON_DELAY field mask
#define WLAN_RF_EXT_TXON_DELAY_MASK         ((uint32_t)0x001FF000)
/// EXT_TXON_DELAY field LSB position
#define WLAN_RF_EXT_TXON_DELAY_LSB          12
/// EXT_TXON_DELAY field width
#define WLAN_RF_EXT_TXON_DELAY_WIDTH        ((uint32_t)0x00000009)
/// EXT_PA_RX_CTRL_REG field mask
#define WLAN_RF_EXT_PA_RX_CTRL_REG_MASK     ((uint32_t)0x00000F00)
/// EXT_PA_RX_CTRL_REG field LSB position
#define WLAN_RF_EXT_PA_RX_CTRL_REG_LSB      8
/// EXT_PA_RX_CTRL_REG field width
#define WLAN_RF_EXT_PA_RX_CTRL_REG_WIDTH    ((uint32_t)0x00000004)
/// EXT_PA_TX_CTRL_REG field mask
#define WLAN_RF_EXT_PA_TX_CTRL_REG_MASK     ((uint32_t)0x000000F0)
/// EXT_PA_TX_CTRL_REG field LSB position
#define WLAN_RF_EXT_PA_TX_CTRL_REG_LSB      4
/// EXT_PA_TX_CTRL_REG field width
#define WLAN_RF_EXT_PA_TX_CTRL_REG_WIDTH    ((uint32_t)0x00000004)
/// EXT_PA_IDLE_CTRL_REG field mask
#define WLAN_RF_EXT_PA_IDLE_CTRL_REG_MASK   ((uint32_t)0x0000000F)
/// EXT_PA_IDLE_CTRL_REG field LSB position
#define WLAN_RF_EXT_PA_IDLE_CTRL_REG_LSB    0
/// EXT_PA_IDLE_CTRL_REG field width
#define WLAN_RF_EXT_PA_IDLE_CTRL_REG_WIDTH  ((uint32_t)0x00000004)

/// EXT_PA_CTRL_MODE field reset value
#define WLAN_RF_EXT_PA_CTRL_MODE_RST        0x0
/// EXT_RXON_DELAY field reset value
#define WLAN_RF_EXT_RXON_DELAY_RST          0x87
/// EXT_TXON_DELAY field reset value
#define WLAN_RF_EXT_TXON_DELAY_RST          0x41
/// EXT_PA_RX_CTRL_REG field reset value
#define WLAN_RF_EXT_PA_RX_CTRL_REG_RST      0x5
/// EXT_PA_TX_CTRL_REG field reset value
#define WLAN_RF_EXT_PA_TX_CTRL_REG_RST      0x2
/// EXT_PA_IDLE_CTRL_REG field reset value
#define WLAN_RF_EXT_PA_IDLE_CTRL_REG_RST    0x0

/**
 * @brief Constructs a value for the WF_EXT_TRXON_DELAY_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] extpactrlmode - The value to use for the ext_pa_ctrl_mode field.
 * @param[in] extrxondelay - The value to use for the ext_rxon_delay field.
 * @param[in] exttxondelay - The value to use for the ext_txon_delay field.
 * @param[in] extparxctrlreg - The value to use for the ext_pa_rx_ctrl_reg field.
 * @param[in] extpatxctrlreg - The value to use for the ext_pa_tx_ctrl_reg field.
 * @param[in] extpaidlectrlreg - The value to use for the ext_pa_idle_ctrl_reg field.
 */
__INLINE void wlan_rf_wf_ext_trxon_delay_reg_pack(uint8_t extpactrlmode, uint16_t extrxondelay, uint16_t exttxondelay, uint8_t extparxctrlreg, uint8_t extpatxctrlreg, uint8_t extpaidlectrlreg)
{
    REG_PL_WR(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR,  ((uint32_t)extpactrlmode << 30) | ((uint32_t)extrxondelay << 21) | ((uint32_t)exttxondelay << 12) | ((uint32_t)extparxctrlreg << 8) | ((uint32_t)extpatxctrlreg << 4) | ((uint32_t)extpaidlectrlreg << 0));
}

/**
 * @brief Unpacks WF_EXT_TRXON_DELAY_REG's fields from current value of the WF_EXT_TRXON_DELAY_REG register.
 *
 * Reads the WF_EXT_TRXON_DELAY_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] extpactrlmode - Will be populated with the current value of this field from the register.
 * @param[out] extrxondelay - Will be populated with the current value of this field from the register.
 * @param[out] exttxondelay - Will be populated with the current value of this field from the register.
 * @param[out] extparxctrlreg - Will be populated with the current value of this field from the register.
 * @param[out] extpatxctrlreg - Will be populated with the current value of this field from the register.
 * @param[out] extpaidlectrlreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_wf_ext_trxon_delay_reg_unpack(uint8_t* extpactrlmode, uint16_t* extrxondelay, uint16_t* exttxondelay, uint8_t* extparxctrlreg, uint8_t* extpatxctrlreg, uint8_t* extpaidlectrlreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR);

    *extpactrlmode = (localVal & ((uint32_t)0x40000000)) >> 30;
    *extrxondelay = (localVal & ((uint32_t)0x3FE00000)) >> 21;
    *exttxondelay = (localVal & ((uint32_t)0x001FF000)) >> 12;
    *extparxctrlreg = (localVal & ((uint32_t)0x00000F00)) >> 8;
    *extpatxctrlreg = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *extpaidlectrlreg = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the ext_pa_ctrl_mode field in the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read and the ext_pa_ctrl_mode field's value will be returned.
 *
 * @return The current value of the ext_pa_ctrl_mode field in the WF_EXT_TRXON_DELAY_REG register.
 */
__INLINE uint8_t wlan_rf_ext_pa_ctrl_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the ext_pa_ctrl_mode field of the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] extpactrlmode - The value to set the field to.
 */
__INLINE void wlan_rf_ext_pa_ctrl_mode_setf(uint8_t extpactrlmode)
{
    REG_PL_WR(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)extpactrlmode << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the ext_rxon_delay field in the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read and the ext_rxon_delay field's value will be returned.
 *
 * @return The current value of the ext_rxon_delay field in the WF_EXT_TRXON_DELAY_REG register.
 */
__INLINE uint16_t wlan_rf_ext_rxon_delay_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR);
    return ((localVal & ((uint32_t)0x3FE00000)) >> 21);
}

/**
 * @brief Sets the ext_rxon_delay field of the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] extrxondelay - The value to set the field to.
 */
__INLINE void wlan_rf_ext_rxon_delay_setf(uint16_t extrxondelay)
{
    REG_PL_WR(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR) & ~((uint32_t)0x3FE00000)) | (((uint32_t)extrxondelay << 21) & ((uint32_t)0x3FE00000)));
}

/**
 * @brief Returns the current value of the ext_txon_delay field in the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read and the ext_txon_delay field's value will be returned.
 *
 * @return The current value of the ext_txon_delay field in the WF_EXT_TRXON_DELAY_REG register.
 */
__INLINE uint16_t wlan_rf_ext_txon_delay_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR);
    return ((localVal & ((uint32_t)0x001FF000)) >> 12);
}

/**
 * @brief Sets the ext_txon_delay field of the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] exttxondelay - The value to set the field to.
 */
__INLINE void wlan_rf_ext_txon_delay_setf(uint16_t exttxondelay)
{
    REG_PL_WR(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR) & ~((uint32_t)0x001FF000)) | (((uint32_t)exttxondelay << 12) & ((uint32_t)0x001FF000)));
}

/**
 * @brief Returns the current value of the ext_pa_rx_ctrl_reg field in the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read and the ext_pa_rx_ctrl_reg field's value will be returned.
 *
 * @return The current value of the ext_pa_rx_ctrl_reg field in the WF_EXT_TRXON_DELAY_REG register.
 */
__INLINE uint8_t wlan_rf_ext_pa_rx_ctrl_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000F00)) >> 8);
}

/**
 * @brief Sets the ext_pa_rx_ctrl_reg field of the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] extparxctrlreg - The value to set the field to.
 */
__INLINE void wlan_rf_ext_pa_rx_ctrl_reg_setf(uint8_t extparxctrlreg)
{
    REG_PL_WR(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR) & ~((uint32_t)0x00000F00)) | (((uint32_t)extparxctrlreg << 8) & ((uint32_t)0x00000F00)));
}

/**
 * @brief Returns the current value of the ext_pa_tx_ctrl_reg field in the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read and the ext_pa_tx_ctrl_reg field's value will be returned.
 *
 * @return The current value of the ext_pa_tx_ctrl_reg field in the WF_EXT_TRXON_DELAY_REG register.
 */
__INLINE uint8_t wlan_rf_ext_pa_tx_ctrl_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Sets the ext_pa_tx_ctrl_reg field of the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] extpatxctrlreg - The value to set the field to.
 */
__INLINE void wlan_rf_ext_pa_tx_ctrl_reg_setf(uint8_t extpatxctrlreg)
{
    REG_PL_WR(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR) & ~((uint32_t)0x000000F0)) | (((uint32_t)extpatxctrlreg << 4) & ((uint32_t)0x000000F0)));
}

/**
 * @brief Returns the current value of the ext_pa_idle_ctrl_reg field in the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read and the ext_pa_idle_ctrl_reg field's value will be returned.
 *
 * @return The current value of the ext_pa_idle_ctrl_reg field in the WF_EXT_TRXON_DELAY_REG register.
 */
__INLINE uint8_t wlan_rf_ext_pa_idle_ctrl_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the ext_pa_idle_ctrl_reg field of the WF_EXT_TRXON_DELAY_REG register.
 *
 * The WF_EXT_TRXON_DELAY_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] extpaidlectrlreg - The value to set the field to.
 */
__INLINE void wlan_rf_ext_pa_idle_ctrl_reg_setf(uint8_t extpaidlectrlreg)
{
    REG_PL_WR(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)extpaidlectrlreg << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name GAIN_MEM_CTRL_REG register definitions
 * <table>
 * <caption id="GAIN_MEM_CTRL_REG_BF">GAIN_MEM_CTRL_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>06 <td>    rxgain_mem_cfg <td>R <td>R/W <td>0
 * <tr><td>05 <td>    clk_rxgain_sel <td>R <td>R/W <td>0
 * <tr><td>04 <td>     clk_rxgain_en <td>R <td>R/W <td>0
 * <tr><td>02 <td>    txgain_mem_cfg <td>R <td>R/W <td>0
 * <tr><td>01 <td>    clk_txgain_sel <td>R <td>R/W <td>0
 * <tr><td>00 <td>     clk_txgain_en <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the GAIN_MEM_CTRL_REG register
#define WLAN_RF_GAIN_MEM_CTRL_REG_ADDR   0x40344094
/// Offset of the GAIN_MEM_CTRL_REG register from the base address
#define WLAN_RF_GAIN_MEM_CTRL_REG_OFFSET 0x00000094
/// Index of the GAIN_MEM_CTRL_REG register
#define WLAN_RF_GAIN_MEM_CTRL_REG_INDEX  0x00000025
/// Reset value of the GAIN_MEM_CTRL_REG register
#define WLAN_RF_GAIN_MEM_CTRL_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the GAIN_MEM_CTRL_REG register.
 * The GAIN_MEM_CTRL_REG register will be read and its value returned.
 * @return The current value of the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint32_t wlan_rf_gain_mem_ctrl_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR);
}

/**
 * @brief Sets the GAIN_MEM_CTRL_REG register to a value.
 * The GAIN_MEM_CTRL_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_gain_mem_ctrl_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR, value);
}

// field definitions
/// RXGAIN_MEM_CFG field bit
#define WLAN_RF_RXGAIN_MEM_CFG_BIT    ((uint32_t)0x00000040)
/// RXGAIN_MEM_CFG field position
#define WLAN_RF_RXGAIN_MEM_CFG_POS    6
/// CLK_RXGAIN_SEL field bit
#define WLAN_RF_CLK_RXGAIN_SEL_BIT    ((uint32_t)0x00000020)
/// CLK_RXGAIN_SEL field position
#define WLAN_RF_CLK_RXGAIN_SEL_POS    5
/// CLK_RXGAIN_EN field bit
#define WLAN_RF_CLK_RXGAIN_EN_BIT     ((uint32_t)0x00000010)
/// CLK_RXGAIN_EN field position
#define WLAN_RF_CLK_RXGAIN_EN_POS     4
/// TXGAIN_MEM_CFG field bit
#define WLAN_RF_TXGAIN_MEM_CFG_BIT    ((uint32_t)0x00000004)
/// TXGAIN_MEM_CFG field position
#define WLAN_RF_TXGAIN_MEM_CFG_POS    2
/// CLK_TXGAIN_SEL field bit
#define WLAN_RF_CLK_TXGAIN_SEL_BIT    ((uint32_t)0x00000002)
/// CLK_TXGAIN_SEL field position
#define WLAN_RF_CLK_TXGAIN_SEL_POS    1
/// CLK_TXGAIN_EN field bit
#define WLAN_RF_CLK_TXGAIN_EN_BIT     ((uint32_t)0x00000001)
/// CLK_TXGAIN_EN field position
#define WLAN_RF_CLK_TXGAIN_EN_POS     0

/// RXGAIN_MEM_CFG field reset value
#define WLAN_RF_RXGAIN_MEM_CFG_RST    0x0
/// CLK_RXGAIN_SEL field reset value
#define WLAN_RF_CLK_RXGAIN_SEL_RST    0x0
/// CLK_RXGAIN_EN field reset value
#define WLAN_RF_CLK_RXGAIN_EN_RST     0x0
/// TXGAIN_MEM_CFG field reset value
#define WLAN_RF_TXGAIN_MEM_CFG_RST    0x0
/// CLK_TXGAIN_SEL field reset value
#define WLAN_RF_CLK_TXGAIN_SEL_RST    0x0
/// CLK_TXGAIN_EN field reset value
#define WLAN_RF_CLK_TXGAIN_EN_RST     0x0

/**
 * @brief Constructs a value for the GAIN_MEM_CTRL_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] rxgainmemcfg - The value to use for the rxgain_mem_cfg field.
 * @param[in] clkrxgainsel - The value to use for the clk_rxgain_sel field.
 * @param[in] clkrxgainen - The value to use for the clk_rxgain_en field.
 * @param[in] txgainmemcfg - The value to use for the txgain_mem_cfg field.
 * @param[in] clktxgainsel - The value to use for the clk_txgain_sel field.
 * @param[in] clktxgainen - The value to use for the clk_txgain_en field.
 */
__INLINE void wlan_rf_gain_mem_ctrl_reg_pack(uint8_t rxgainmemcfg, uint8_t clkrxgainsel, uint8_t clkrxgainen, uint8_t txgainmemcfg, uint8_t clktxgainsel, uint8_t clktxgainen)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR,  ((uint32_t)rxgainmemcfg << 6) | ((uint32_t)clkrxgainsel << 5) | ((uint32_t)clkrxgainen << 4) | ((uint32_t)txgainmemcfg << 2) | ((uint32_t)clktxgainsel << 1) | ((uint32_t)clktxgainen << 0));
}

/**
 * @brief Unpacks GAIN_MEM_CTRL_REG's fields from current value of the GAIN_MEM_CTRL_REG register.
 *
 * Reads the GAIN_MEM_CTRL_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] rxgainmemcfg - Will be populated with the current value of this field from the register.
 * @param[out] clkrxgainsel - Will be populated with the current value of this field from the register.
 * @param[out] clkrxgainen - Will be populated with the current value of this field from the register.
 * @param[out] txgainmemcfg - Will be populated with the current value of this field from the register.
 * @param[out] clktxgainsel - Will be populated with the current value of this field from the register.
 * @param[out] clktxgainen - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_gain_mem_ctrl_reg_unpack(uint8_t* rxgainmemcfg, uint8_t* clkrxgainsel, uint8_t* clkrxgainen, uint8_t* txgainmemcfg, uint8_t* clktxgainsel, uint8_t* clktxgainen)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR);

    *rxgainmemcfg = (localVal & ((uint32_t)0x00000040)) >> 6;
    *clkrxgainsel = (localVal & ((uint32_t)0x00000020)) >> 5;
    *clkrxgainen = (localVal & ((uint32_t)0x00000010)) >> 4;
    *txgainmemcfg = (localVal & ((uint32_t)0x00000004)) >> 2;
    *clktxgainsel = (localVal & ((uint32_t)0x00000002)) >> 1;
    *clktxgainen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the rxgain_mem_cfg field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the rxgain_mem_cfg field's value will be returned.
 *
 * @return The current value of the rxgain_mem_cfg field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_rxgain_mem_cfg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the rxgain_mem_cfg field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainmemcfg - The value to set the field to.
 */
__INLINE void wlan_rf_rxgain_mem_cfg_setf(uint8_t rxgainmemcfg)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)rxgainmemcfg << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the clk_rxgain_sel field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the clk_rxgain_sel field's value will be returned.
 *
 * @return The current value of the clk_rxgain_sel field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_clk_rxgain_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the clk_rxgain_sel field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] clkrxgainsel - The value to set the field to.
 */
__INLINE void wlan_rf_clk_rxgain_sel_setf(uint8_t clkrxgainsel)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)clkrxgainsel << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the clk_rxgain_en field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the clk_rxgain_en field's value will be returned.
 *
 * @return The current value of the clk_rxgain_en field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_clk_rxgain_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the clk_rxgain_en field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] clkrxgainen - The value to set the field to.
 */
__INLINE void wlan_rf_clk_rxgain_en_setf(uint8_t clkrxgainen)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)clkrxgainen << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the txgain_mem_cfg field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the txgain_mem_cfg field's value will be returned.
 *
 * @return The current value of the txgain_mem_cfg field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_txgain_mem_cfg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the txgain_mem_cfg field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgainmemcfg - The value to set the field to.
 */
__INLINE void wlan_rf_txgain_mem_cfg_setf(uint8_t txgainmemcfg)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)txgainmemcfg << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the clk_txgain_sel field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the clk_txgain_sel field's value will be returned.
 *
 * @return The current value of the clk_txgain_sel field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_clk_txgain_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the clk_txgain_sel field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] clktxgainsel - The value to set the field to.
 */
__INLINE void wlan_rf_clk_txgain_sel_setf(uint8_t clktxgainsel)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)clktxgainsel << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the clk_txgain_en field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the clk_txgain_en field's value will be returned.
 *
 * @return The current value of the clk_txgain_en field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_clk_txgain_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the clk_txgain_en field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] clktxgainen - The value to set the field to.
 */
__INLINE void wlan_rf_clk_txgain_en_setf(uint8_t clktxgainen)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)clktxgainen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name GAIN_MEM_FETCH_REG register definitions
 * <table>
 * <caption id="GAIN_MEM_FETCH_REG_BF">GAIN_MEM_FETCH_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>rxgain_mem_fetch_p <td>R <td>R/W <td>0
 * <tr><td>22:16 <td>rxgain_mem_fetch_addr <td>R <td>R/W <td>0x0
 * <tr><td>15 <td>txgain_mem_fetch_p <td>R <td>R/W <td>0
 * <tr><td>05:00 <td>txgain_mem_fetch_addr <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the GAIN_MEM_FETCH_REG register
#define WLAN_RF_GAIN_MEM_FETCH_REG_ADDR   0x40344098
/// Offset of the GAIN_MEM_FETCH_REG register from the base address
#define WLAN_RF_GAIN_MEM_FETCH_REG_OFFSET 0x00000098
/// Index of the GAIN_MEM_FETCH_REG register
#define WLAN_RF_GAIN_MEM_FETCH_REG_INDEX  0x00000026
/// Reset value of the GAIN_MEM_FETCH_REG register
#define WLAN_RF_GAIN_MEM_FETCH_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the GAIN_MEM_FETCH_REG register.
 * The GAIN_MEM_FETCH_REG register will be read and its value returned.
 * @return The current value of the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint32_t wlan_rf_gain_mem_fetch_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR);
}

/**
 * @brief Sets the GAIN_MEM_FETCH_REG register to a value.
 * The GAIN_MEM_FETCH_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_gain_mem_fetch_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR, value);
}

// field definitions
/// RXGAIN_MEM_FETCH_P field bit
#define WLAN_RF_RXGAIN_MEM_FETCH_P_BIT       ((uint32_t)0x80000000)
/// RXGAIN_MEM_FETCH_P field position
#define WLAN_RF_RXGAIN_MEM_FETCH_P_POS       31
/// RXGAIN_MEM_FETCH_ADDR field mask
#define WLAN_RF_RXGAIN_MEM_FETCH_ADDR_MASK   ((uint32_t)0x007F0000)
/// RXGAIN_MEM_FETCH_ADDR field LSB position
#define WLAN_RF_RXGAIN_MEM_FETCH_ADDR_LSB    16
/// RXGAIN_MEM_FETCH_ADDR field width
#define WLAN_RF_RXGAIN_MEM_FETCH_ADDR_WIDTH  ((uint32_t)0x00000007)
/// TXGAIN_MEM_FETCH_P field bit
#define WLAN_RF_TXGAIN_MEM_FETCH_P_BIT       ((uint32_t)0x00008000)
/// TXGAIN_MEM_FETCH_P field position
#define WLAN_RF_TXGAIN_MEM_FETCH_P_POS       15
/// TXGAIN_MEM_FETCH_ADDR field mask
#define WLAN_RF_TXGAIN_MEM_FETCH_ADDR_MASK   ((uint32_t)0x0000003F)
/// TXGAIN_MEM_FETCH_ADDR field LSB position
#define WLAN_RF_TXGAIN_MEM_FETCH_ADDR_LSB    0
/// TXGAIN_MEM_FETCH_ADDR field width
#define WLAN_RF_TXGAIN_MEM_FETCH_ADDR_WIDTH  ((uint32_t)0x00000006)

/// RXGAIN_MEM_FETCH_P field reset value
#define WLAN_RF_RXGAIN_MEM_FETCH_P_RST       0x0
/// RXGAIN_MEM_FETCH_ADDR field reset value
#define WLAN_RF_RXGAIN_MEM_FETCH_ADDR_RST    0x0
/// TXGAIN_MEM_FETCH_P field reset value
#define WLAN_RF_TXGAIN_MEM_FETCH_P_RST       0x0
/// TXGAIN_MEM_FETCH_ADDR field reset value
#define WLAN_RF_TXGAIN_MEM_FETCH_ADDR_RST    0x0

/**
 * @brief Constructs a value for the GAIN_MEM_FETCH_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] rxgainmemfetchp - The value to use for the rxgain_mem_fetch_p field.
 * @param[in] rxgainmemfetchaddr - The value to use for the rxgain_mem_fetch_addr field.
 * @param[in] txgainmemfetchp - The value to use for the txgain_mem_fetch_p field.
 * @param[in] txgainmemfetchaddr - The value to use for the txgain_mem_fetch_addr field.
 */
__INLINE void wlan_rf_gain_mem_fetch_reg_pack(uint8_t rxgainmemfetchp, uint8_t rxgainmemfetchaddr, uint8_t txgainmemfetchp, uint8_t txgainmemfetchaddr)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR,  ((uint32_t)rxgainmemfetchp << 31) | ((uint32_t)rxgainmemfetchaddr << 16) | ((uint32_t)txgainmemfetchp << 15) | ((uint32_t)txgainmemfetchaddr << 0));
}

/**
 * @brief Unpacks GAIN_MEM_FETCH_REG's fields from current value of the GAIN_MEM_FETCH_REG register.
 *
 * Reads the GAIN_MEM_FETCH_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] rxgainmemfetchp - Will be populated with the current value of this field from the register.
 * @param[out] rxgainmemfetchaddr - Will be populated with the current value of this field from the register.
 * @param[out] txgainmemfetchp - Will be populated with the current value of this field from the register.
 * @param[out] txgainmemfetchaddr - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_gain_mem_fetch_reg_unpack(uint8_t* rxgainmemfetchp, uint8_t* rxgainmemfetchaddr, uint8_t* txgainmemfetchp, uint8_t* txgainmemfetchaddr)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR);

    *rxgainmemfetchp = (localVal & ((uint32_t)0x80000000)) >> 31;
    *rxgainmemfetchaddr = (localVal & ((uint32_t)0x007F0000)) >> 16;
    *txgainmemfetchp = (localVal & ((uint32_t)0x00008000)) >> 15;
    *txgainmemfetchaddr = (localVal & ((uint32_t)0x0000003F)) >> 0;
}

/**
 * @brief Returns the current value of the rxgain_mem_fetch_p field in the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read and the rxgain_mem_fetch_p field's value will be returned.
 *
 * @return The current value of the rxgain_mem_fetch_p field in the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint8_t wlan_rf_rxgain_mem_fetch_p_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the rxgain_mem_fetch_p field of the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainmemfetchp - The value to set the field to.
 */
__INLINE void wlan_rf_rxgain_mem_fetch_p_setf(uint8_t rxgainmemfetchp)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)rxgainmemfetchp << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the rxgain_mem_fetch_addr field in the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read and the rxgain_mem_fetch_addr field's value will be returned.
 *
 * @return The current value of the rxgain_mem_fetch_addr field in the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint8_t wlan_rf_rxgain_mem_fetch_addr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR);
    return ((localVal & ((uint32_t)0x007F0000)) >> 16);
}

/**
 * @brief Sets the rxgain_mem_fetch_addr field of the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainmemfetchaddr - The value to set the field to.
 */
__INLINE void wlan_rf_rxgain_mem_fetch_addr_setf(uint8_t rxgainmemfetchaddr)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR) & ~((uint32_t)0x007F0000)) | (((uint32_t)rxgainmemfetchaddr << 16) & ((uint32_t)0x007F0000)));
}

/**
 * @brief Returns the current value of the txgain_mem_fetch_p field in the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read and the txgain_mem_fetch_p field's value will be returned.
 *
 * @return The current value of the txgain_mem_fetch_p field in the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint8_t wlan_rf_txgain_mem_fetch_p_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the txgain_mem_fetch_p field of the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgainmemfetchp - The value to set the field to.
 */
__INLINE void wlan_rf_txgain_mem_fetch_p_setf(uint8_t txgainmemfetchp)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)txgainmemfetchp << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the txgain_mem_fetch_addr field in the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read and the txgain_mem_fetch_addr field's value will be returned.
 *
 * @return The current value of the txgain_mem_fetch_addr field in the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint8_t wlan_rf_txgain_mem_fetch_addr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000003F)) >> 0);
}

/**
 * @brief Sets the txgain_mem_fetch_addr field of the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgainmemfetchaddr - The value to set the field to.
 */
__INLINE void wlan_rf_txgain_mem_fetch_addr_setf(uint8_t txgainmemfetchaddr)
{
    REG_PL_WR(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR, (REG_PL_RD(WLAN_RF_GAIN_MEM_FETCH_REG_ADDR) & ~((uint32_t)0x0000003F)) | (((uint32_t)txgainmemfetchaddr << 0) & ((uint32_t)0x0000003F)));
}

/// @}

/**
 * @name WF_DPD_TXCAL_CTRL_REG register definitions
 * <table>
 * <caption id="WF_DPD_TXCAL_CTRL_REG_BF">WF_DPD_TXCAL_CTRL_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>10 <td> wf_rxflt_gbit2_dr <td>R <td>R/W <td>0
 * <tr><td>09:08 <td>wf_rxflt_gbit2_reg <td>R <td>R/W <td>0x0
 * <tr><td>07 <td> wf_rxflt_gbit1_dr <td>R <td>R/W <td>0
 * <tr><td>06:04 <td>wf_rxflt_gbit1_reg <td>R <td>R/W <td>0x0
 * <tr><td>03 <td>    wf_tia_gbit_dr <td>R <td>R/W <td>0
 * <tr><td>02:00 <td>   wf_tia_gbit_reg <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the WF_DPD_TXCAL_CTRL_REG register
#define WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR   0x4034409C
/// Offset of the WF_DPD_TXCAL_CTRL_REG register from the base address
#define WLAN_RF_WF_DPD_TXCAL_CTRL_REG_OFFSET 0x0000009C
/// Index of the WF_DPD_TXCAL_CTRL_REG register
#define WLAN_RF_WF_DPD_TXCAL_CTRL_REG_INDEX  0x00000027
/// Reset value of the WF_DPD_TXCAL_CTRL_REG register
#define WLAN_RF_WF_DPD_TXCAL_CTRL_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the WF_DPD_TXCAL_CTRL_REG register.
 * The WF_DPD_TXCAL_CTRL_REG register will be read and its value returned.
 * @return The current value of the WF_DPD_TXCAL_CTRL_REG register.
 */
__INLINE uint32_t wlan_rf_wf_dpd_txcal_ctrl_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);
}

/**
 * @brief Sets the WF_DPD_TXCAL_CTRL_REG register to a value.
 * The WF_DPD_TXCAL_CTRL_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_wf_dpd_txcal_ctrl_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR, value);
}

// field definitions
/// WF_RXFLT_GBIT_2_DR field bit
#define WLAN_RF_WF_RXFLT_GBIT_2_DR_BIT     ((uint32_t)0x00000400)
/// WF_RXFLT_GBIT_2_DR field position
#define WLAN_RF_WF_RXFLT_GBIT_2_DR_POS     10
/// WF_RXFLT_GBIT_2_REG field mask
#define WLAN_RF_WF_RXFLT_GBIT_2_REG_MASK   ((uint32_t)0x00000300)
/// WF_RXFLT_GBIT_2_REG field LSB position
#define WLAN_RF_WF_RXFLT_GBIT_2_REG_LSB    8
/// WF_RXFLT_GBIT_2_REG field width
#define WLAN_RF_WF_RXFLT_GBIT_2_REG_WIDTH  ((uint32_t)0x00000002)
/// WF_RXFLT_GBIT_1_DR field bit
#define WLAN_RF_WF_RXFLT_GBIT_1_DR_BIT     ((uint32_t)0x00000080)
/// WF_RXFLT_GBIT_1_DR field position
#define WLAN_RF_WF_RXFLT_GBIT_1_DR_POS     7
/// WF_RXFLT_GBIT_1_REG field mask
#define WLAN_RF_WF_RXFLT_GBIT_1_REG_MASK   ((uint32_t)0x00000070)
/// WF_RXFLT_GBIT_1_REG field LSB position
#define WLAN_RF_WF_RXFLT_GBIT_1_REG_LSB    4
/// WF_RXFLT_GBIT_1_REG field width
#define WLAN_RF_WF_RXFLT_GBIT_1_REG_WIDTH  ((uint32_t)0x00000003)
/// WF_TIA_GBIT_DR field bit
#define WLAN_RF_WF_TIA_GBIT_DR_BIT         ((uint32_t)0x00000008)
/// WF_TIA_GBIT_DR field position
#define WLAN_RF_WF_TIA_GBIT_DR_POS         3
/// WF_TIA_GBIT_REG field mask
#define WLAN_RF_WF_TIA_GBIT_REG_MASK       ((uint32_t)0x00000007)
/// WF_TIA_GBIT_REG field LSB position
#define WLAN_RF_WF_TIA_GBIT_REG_LSB        0
/// WF_TIA_GBIT_REG field width
#define WLAN_RF_WF_TIA_GBIT_REG_WIDTH      ((uint32_t)0x00000003)

/// WF_RXFLT_GBIT_2_DR field reset value
#define WLAN_RF_WF_RXFLT_GBIT_2_DR_RST     0x0
/// WF_RXFLT_GBIT_2_REG field reset value
#define WLAN_RF_WF_RXFLT_GBIT_2_REG_RST    0x0
/// WF_RXFLT_GBIT_1_DR field reset value
#define WLAN_RF_WF_RXFLT_GBIT_1_DR_RST     0x0
/// WF_RXFLT_GBIT_1_REG field reset value
#define WLAN_RF_WF_RXFLT_GBIT_1_REG_RST    0x0
/// WF_TIA_GBIT_DR field reset value
#define WLAN_RF_WF_TIA_GBIT_DR_RST         0x0
/// WF_TIA_GBIT_REG field reset value
#define WLAN_RF_WF_TIA_GBIT_REG_RST        0x0

/**
 * @brief Constructs a value for the WF_DPD_TXCAL_CTRL_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrxfltgbit2dr - The value to use for the wf_rxflt_gbit2_dr field.
 * @param[in] wfrxfltgbit2reg - The value to use for the wf_rxflt_gbit2_reg field.
 * @param[in] wfrxfltgbit1dr - The value to use for the wf_rxflt_gbit1_dr field.
 * @param[in] wfrxfltgbit1reg - The value to use for the wf_rxflt_gbit1_reg field.
 * @param[in] wftiagbitdr - The value to use for the wf_tia_gbit_dr field.
 * @param[in] wftiagbitreg - The value to use for the wf_tia_gbit_reg field.
 */
__INLINE void wlan_rf_wf_dpd_txcal_ctrl_reg_pack(uint8_t wfrxfltgbit2dr, uint8_t wfrxfltgbit2reg, uint8_t wfrxfltgbit1dr, uint8_t wfrxfltgbit1reg, uint8_t wftiagbitdr, uint8_t wftiagbitreg)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR,  ((uint32_t)wfrxfltgbit2dr << 10) | ((uint32_t)wfrxfltgbit2reg << 8) | ((uint32_t)wfrxfltgbit1dr << 7) | ((uint32_t)wfrxfltgbit1reg << 4) | ((uint32_t)wftiagbitdr << 3) | ((uint32_t)wftiagbitreg << 0));
}

/**
 * @brief Unpacks WF_DPD_TXCAL_CTRL_REG's fields from current value of the WF_DPD_TXCAL_CTRL_REG register.
 *
 * Reads the WF_DPD_TXCAL_CTRL_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrxfltgbit2dr - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltgbit2reg - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltgbit1dr - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltgbit1reg - Will be populated with the current value of this field from the register.
 * @param[out] wftiagbitdr - Will be populated with the current value of this field from the register.
 * @param[out] wftiagbitreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_wf_dpd_txcal_ctrl_reg_unpack(uint8_t* wfrxfltgbit2dr, uint8_t* wfrxfltgbit2reg, uint8_t* wfrxfltgbit1dr, uint8_t* wfrxfltgbit1reg, uint8_t* wftiagbitdr, uint8_t* wftiagbitreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);

    *wfrxfltgbit2dr = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfrxfltgbit2reg = (localVal & ((uint32_t)0x00000300)) >> 8;
    *wfrxfltgbit1dr = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wfrxfltgbit1reg = (localVal & ((uint32_t)0x00000070)) >> 4;
    *wftiagbitdr = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wftiagbitreg = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rxflt_gbit2_dr field in the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read and the wf_rxflt_gbit2_dr field's value will be returned.
 *
 * @return The current value of the wf_rxflt_gbit2_dr field in the WF_DPD_TXCAL_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_gbit_2_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_rxflt_gbit2_dr field of the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltgbit2dr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_gbit_2_dr_setf(uint8_t wfrxfltgbit2dr)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfrxfltgbit2dr << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_rxflt_gbit2_reg field in the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read and the wf_rxflt_gbit2_reg field's value will be returned.
 *
 * @return The current value of the wf_rxflt_gbit2_reg field in the WF_DPD_TXCAL_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_gbit_2_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the wf_rxflt_gbit2_reg field of the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltgbit2reg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_gbit_2_reg_setf(uint8_t wfrxfltgbit2reg)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)wfrxfltgbit2reg << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the wf_rxflt_gbit1_dr field in the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read and the wf_rxflt_gbit1_dr field's value will be returned.
 *
 * @return The current value of the wf_rxflt_gbit1_dr field in the WF_DPD_TXCAL_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_gbit_1_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_rxflt_gbit1_dr field of the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltgbit1dr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_gbit_1_dr_setf(uint8_t wfrxfltgbit1dr)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wfrxfltgbit1dr << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_rxflt_gbit1_reg field in the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read and the wf_rxflt_gbit1_reg field's value will be returned.
 *
 * @return The current value of the wf_rxflt_gbit1_reg field in the WF_DPD_TXCAL_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_gbit_1_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

/**
 * @brief Sets the wf_rxflt_gbit1_reg field of the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltgbit1reg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_gbit_1_reg_setf(uint8_t wfrxfltgbit1reg)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR) & ~((uint32_t)0x00000070)) | (((uint32_t)wfrxfltgbit1reg << 4) & ((uint32_t)0x00000070)));
}

/**
 * @brief Returns the current value of the wf_tia_gbit_dr field in the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read and the wf_tia_gbit_dr field's value will be returned.
 *
 * @return The current value of the wf_tia_gbit_dr field in the WF_DPD_TXCAL_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_tia_gbit_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wf_tia_gbit_dr field of the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiagbitdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_gbit_dr_setf(uint8_t wftiagbitdr)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wftiagbitdr << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wf_tia_gbit_reg field in the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read and the wf_tia_gbit_reg field's value will be returned.
 *
 * @return The current value of the wf_tia_gbit_reg field in the WF_DPD_TXCAL_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_tia_gbit_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/**
 * @brief Sets the wf_tia_gbit_reg field of the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiagbitreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_gbit_reg_setf(uint8_t wftiagbitreg)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR) & ~((uint32_t)0x00000007)) | (((uint32_t)wftiagbitreg << 0) & ((uint32_t)0x00000007)));
}

/// @}

/**
 * @name CO_ANT_TXGAIN_REG register definitions
 * <table>
 * <caption id="CO_ANT_TXGAIN_REG_BF">CO_ANT_TXGAIN_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>15:13 <td>co_ant_pa24g_vl_ic_sel_bit <td>R <td>R/W <td>0x1
 * <tr><td>12:10 <td>co_ant_pa24g_vl_vbit <td>R <td>R/W <td>0x4
 * <tr><td>09:06 <td>co_ant_pa24g_vl_cgm_ibit <td>R <td>R/W <td>0x8
 * <tr><td>05:00 <td> co_ant_pa24g_gbit <td>R <td>R/W <td>0x3F
 * </table>
 *
 * @{
 */

/// Address of the CO_ANT_TXGAIN_REG register
#define WLAN_RF_CO_ANT_TXGAIN_REG_ADDR   0x403440A0
/// Offset of the CO_ANT_TXGAIN_REG register from the base address
#define WLAN_RF_CO_ANT_TXGAIN_REG_OFFSET 0x000000A0
/// Index of the CO_ANT_TXGAIN_REG register
#define WLAN_RF_CO_ANT_TXGAIN_REG_INDEX  0x00000028
/// Reset value of the CO_ANT_TXGAIN_REG register
#define WLAN_RF_CO_ANT_TXGAIN_REG_RESET  0x0000323F

/**
 * @brief Returns the current value of the CO_ANT_TXGAIN_REG register.
 * The CO_ANT_TXGAIN_REG register will be read and its value returned.
 * @return The current value of the CO_ANT_TXGAIN_REG register.
 */
__INLINE uint32_t wlan_rf_co_ant_txgain_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR);
}

/**
 * @brief Sets the CO_ANT_TXGAIN_REG register to a value.
 * The CO_ANT_TXGAIN_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_co_ant_txgain_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR, value);
}

// field definitions
/// CO_ANT_PA_24G_VL_IC_SEL_BIT field mask
#define WLAN_RF_CO_ANT_PA_24G_VL_IC_SEL_BIT_MASK   ((uint32_t)0x0000E000)
/// CO_ANT_PA_24G_VL_IC_SEL_BIT field LSB position
#define WLAN_RF_CO_ANT_PA_24G_VL_IC_SEL_BIT_LSB    13
/// CO_ANT_PA_24G_VL_IC_SEL_BIT field width
#define WLAN_RF_CO_ANT_PA_24G_VL_IC_SEL_BIT_WIDTH  ((uint32_t)0x00000003)
/// CO_ANT_PA_24G_VL_VBIT field mask
#define WLAN_RF_CO_ANT_PA_24G_VL_VBIT_MASK         ((uint32_t)0x00001C00)
/// CO_ANT_PA_24G_VL_VBIT field LSB position
#define WLAN_RF_CO_ANT_PA_24G_VL_VBIT_LSB          10
/// CO_ANT_PA_24G_VL_VBIT field width
#define WLAN_RF_CO_ANT_PA_24G_VL_VBIT_WIDTH        ((uint32_t)0x00000003)
/// CO_ANT_PA_24G_VL_CGM_IBIT field mask
#define WLAN_RF_CO_ANT_PA_24G_VL_CGM_IBIT_MASK     ((uint32_t)0x000003C0)
/// CO_ANT_PA_24G_VL_CGM_IBIT field LSB position
#define WLAN_RF_CO_ANT_PA_24G_VL_CGM_IBIT_LSB      6
/// CO_ANT_PA_24G_VL_CGM_IBIT field width
#define WLAN_RF_CO_ANT_PA_24G_VL_CGM_IBIT_WIDTH    ((uint32_t)0x00000004)
/// CO_ANT_PA_24G_GBIT field mask
#define WLAN_RF_CO_ANT_PA_24G_GBIT_MASK            ((uint32_t)0x0000003F)
/// CO_ANT_PA_24G_GBIT field LSB position
#define WLAN_RF_CO_ANT_PA_24G_GBIT_LSB             0
/// CO_ANT_PA_24G_GBIT field width
#define WLAN_RF_CO_ANT_PA_24G_GBIT_WIDTH           ((uint32_t)0x00000006)

/// CO_ANT_PA_24G_VL_IC_SEL_BIT field reset value
#define WLAN_RF_CO_ANT_PA_24G_VL_IC_SEL_BIT_RST    0x1
/// CO_ANT_PA_24G_VL_VBIT field reset value
#define WLAN_RF_CO_ANT_PA_24G_VL_VBIT_RST          0x4
/// CO_ANT_PA_24G_VL_CGM_IBIT field reset value
#define WLAN_RF_CO_ANT_PA_24G_VL_CGM_IBIT_RST      0x8
/// CO_ANT_PA_24G_GBIT field reset value
#define WLAN_RF_CO_ANT_PA_24G_GBIT_RST             0x3F

/**
 * @brief Constructs a value for the CO_ANT_TXGAIN_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] coantpa24gvlicselbit - The value to use for the co_ant_pa24g_vl_ic_sel_bit field.
 * @param[in] coantpa24gvlvbit - The value to use for the co_ant_pa24g_vl_vbit field.
 * @param[in] coantpa24gvlcgmibit - The value to use for the co_ant_pa24g_vl_cgm_ibit field.
 * @param[in] coantpa24ggbit - The value to use for the co_ant_pa24g_gbit field.
 */
__INLINE void wlan_rf_co_ant_txgain_reg_pack(uint8_t coantpa24gvlicselbit, uint8_t coantpa24gvlvbit, uint8_t coantpa24gvlcgmibit, uint8_t coantpa24ggbit)
{
    REG_PL_WR(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR,  ((uint32_t)coantpa24gvlicselbit << 13) | ((uint32_t)coantpa24gvlvbit << 10) | ((uint32_t)coantpa24gvlcgmibit << 6) | ((uint32_t)coantpa24ggbit << 0));
}

/**
 * @brief Unpacks CO_ANT_TXGAIN_REG's fields from current value of the CO_ANT_TXGAIN_REG register.
 *
 * Reads the CO_ANT_TXGAIN_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] coantpa24gvlicselbit - Will be populated with the current value of this field from the register.
 * @param[out] coantpa24gvlvbit - Will be populated with the current value of this field from the register.
 * @param[out] coantpa24gvlcgmibit - Will be populated with the current value of this field from the register.
 * @param[out] coantpa24ggbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_co_ant_txgain_reg_unpack(uint8_t* coantpa24gvlicselbit, uint8_t* coantpa24gvlvbit, uint8_t* coantpa24gvlcgmibit, uint8_t* coantpa24ggbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR);

    *coantpa24gvlicselbit = (localVal & ((uint32_t)0x0000E000)) >> 13;
    *coantpa24gvlvbit = (localVal & ((uint32_t)0x00001C00)) >> 10;
    *coantpa24gvlcgmibit = (localVal & ((uint32_t)0x000003C0)) >> 6;
    *coantpa24ggbit = (localVal & ((uint32_t)0x0000003F)) >> 0;
}

/**
 * @brief Returns the current value of the co_ant_pa24g_vl_ic_sel_bit field in the CO_ANT_TXGAIN_REG register.
 *
 * The CO_ANT_TXGAIN_REG register will be read and the co_ant_pa24g_vl_ic_sel_bit field's value will be returned.
 *
 * @return The current value of the co_ant_pa24g_vl_ic_sel_bit field in the CO_ANT_TXGAIN_REG register.
 */
__INLINE uint8_t wlan_rf_co_ant_pa_24g_vl_ic_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000E000)) >> 13);
}

/**
 * @brief Sets the co_ant_pa24g_vl_ic_sel_bit field of the CO_ANT_TXGAIN_REG register.
 *
 * The CO_ANT_TXGAIN_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] coantpa24gvlicselbit - The value to set the field to.
 */
__INLINE void wlan_rf_co_ant_pa_24g_vl_ic_sel_bit_setf(uint8_t coantpa24gvlicselbit)
{
    REG_PL_WR(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR, (REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR) & ~((uint32_t)0x0000E000)) | (((uint32_t)coantpa24gvlicselbit << 13) & ((uint32_t)0x0000E000)));
}

/**
 * @brief Returns the current value of the co_ant_pa24g_vl_vbit field in the CO_ANT_TXGAIN_REG register.
 *
 * The CO_ANT_TXGAIN_REG register will be read and the co_ant_pa24g_vl_vbit field's value will be returned.
 *
 * @return The current value of the co_ant_pa24g_vl_vbit field in the CO_ANT_TXGAIN_REG register.
 */
__INLINE uint8_t wlan_rf_co_ant_pa_24g_vl_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR);
    return ((localVal & ((uint32_t)0x00001C00)) >> 10);
}

/**
 * @brief Sets the co_ant_pa24g_vl_vbit field of the CO_ANT_TXGAIN_REG register.
 *
 * The CO_ANT_TXGAIN_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] coantpa24gvlvbit - The value to set the field to.
 */
__INLINE void wlan_rf_co_ant_pa_24g_vl_vbit_setf(uint8_t coantpa24gvlvbit)
{
    REG_PL_WR(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR, (REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR) & ~((uint32_t)0x00001C00)) | (((uint32_t)coantpa24gvlvbit << 10) & ((uint32_t)0x00001C00)));
}

/**
 * @brief Returns the current value of the co_ant_pa24g_vl_cgm_ibit field in the CO_ANT_TXGAIN_REG register.
 *
 * The CO_ANT_TXGAIN_REG register will be read and the co_ant_pa24g_vl_cgm_ibit field's value will be returned.
 *
 * @return The current value of the co_ant_pa24g_vl_cgm_ibit field in the CO_ANT_TXGAIN_REG register.
 */
__INLINE uint8_t wlan_rf_co_ant_pa_24g_vl_cgm_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR);
    return ((localVal & ((uint32_t)0x000003C0)) >> 6);
}

/**
 * @brief Sets the co_ant_pa24g_vl_cgm_ibit field of the CO_ANT_TXGAIN_REG register.
 *
 * The CO_ANT_TXGAIN_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] coantpa24gvlcgmibit - The value to set the field to.
 */
__INLINE void wlan_rf_co_ant_pa_24g_vl_cgm_ibit_setf(uint8_t coantpa24gvlcgmibit)
{
    REG_PL_WR(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR, (REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR) & ~((uint32_t)0x000003C0)) | (((uint32_t)coantpa24gvlcgmibit << 6) & ((uint32_t)0x000003C0)));
}

/**
 * @brief Returns the current value of the co_ant_pa24g_gbit field in the CO_ANT_TXGAIN_REG register.
 *
 * The CO_ANT_TXGAIN_REG register will be read and the co_ant_pa24g_gbit field's value will be returned.
 *
 * @return The current value of the co_ant_pa24g_gbit field in the CO_ANT_TXGAIN_REG register.
 */
__INLINE uint8_t wlan_rf_co_ant_pa_24g_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000003F)) >> 0);
}

/**
 * @brief Sets the co_ant_pa24g_gbit field of the CO_ANT_TXGAIN_REG register.
 *
 * The CO_ANT_TXGAIN_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] coantpa24ggbit - The value to set the field to.
 */
__INLINE void wlan_rf_co_ant_pa_24g_gbit_setf(uint8_t coantpa24ggbit)
{
    REG_PL_WR(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR, (REG_PL_RD(WLAN_RF_CO_ANT_TXGAIN_REG_ADDR) & ~((uint32_t)0x0000003F)) | (((uint32_t)coantpa24ggbit << 0) & ((uint32_t)0x0000003F)));
}

/// @}

/**
 * @name WF_DEBUG_REG register definitions
 * <table>
 * <caption id="WF_DEBUG_REG_BF">WF_DEBUG_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>16 <td>      debug_clk_en <td>R <td>R/W <td>0
 * <tr><td>15:12 <td>        debug_sel3 <td>R <td>R/W <td>0x3
 * <tr><td>11:08 <td>        debug_sel2 <td>R <td>R/W <td>0x2
 * <tr><td>07:04 <td>        debug_sel1 <td>R <td>R/W <td>0x1
 * <tr><td>03:00 <td>        debug_sel0 <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the WF_DEBUG_REG register
#define WLAN_RF_WF_DEBUG_REG_ADDR   0x403440A4
/// Offset of the WF_DEBUG_REG register from the base address
#define WLAN_RF_WF_DEBUG_REG_OFFSET 0x000000A4
/// Index of the WF_DEBUG_REG register
#define WLAN_RF_WF_DEBUG_REG_INDEX  0x00000029
/// Reset value of the WF_DEBUG_REG register
#define WLAN_RF_WF_DEBUG_REG_RESET  0x00003210

/**
 * @brief Returns the current value of the WF_DEBUG_REG register.
 * The WF_DEBUG_REG register will be read and its value returned.
 * @return The current value of the WF_DEBUG_REG register.
 */
__INLINE uint32_t wlan_rf_wf_debug_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR);
}

/**
 * @brief Sets the WF_DEBUG_REG register to a value.
 * The WF_DEBUG_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_wf_debug_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_WF_DEBUG_REG_ADDR, value);
}

// field definitions
/// DEBUG_CLK_EN field bit
#define WLAN_RF_DEBUG_CLK_EN_BIT    ((uint32_t)0x00010000)
/// DEBUG_CLK_EN field position
#define WLAN_RF_DEBUG_CLK_EN_POS    16
/// DEBUG_SEL_3 field mask
#define WLAN_RF_DEBUG_SEL_3_MASK    ((uint32_t)0x0000F000)
/// DEBUG_SEL_3 field LSB position
#define WLAN_RF_DEBUG_SEL_3_LSB     12
/// DEBUG_SEL_3 field width
#define WLAN_RF_DEBUG_SEL_3_WIDTH   ((uint32_t)0x00000004)
/// DEBUG_SEL_2 field mask
#define WLAN_RF_DEBUG_SEL_2_MASK    ((uint32_t)0x00000F00)
/// DEBUG_SEL_2 field LSB position
#define WLAN_RF_DEBUG_SEL_2_LSB     8
/// DEBUG_SEL_2 field width
#define WLAN_RF_DEBUG_SEL_2_WIDTH   ((uint32_t)0x00000004)
/// DEBUG_SEL_1 field mask
#define WLAN_RF_DEBUG_SEL_1_MASK    ((uint32_t)0x000000F0)
/// DEBUG_SEL_1 field LSB position
#define WLAN_RF_DEBUG_SEL_1_LSB     4
/// DEBUG_SEL_1 field width
#define WLAN_RF_DEBUG_SEL_1_WIDTH   ((uint32_t)0x00000004)
/// DEBUG_SEL_0 field mask
#define WLAN_RF_DEBUG_SEL_0_MASK    ((uint32_t)0x0000000F)
/// DEBUG_SEL_0 field LSB position
#define WLAN_RF_DEBUG_SEL_0_LSB     0
/// DEBUG_SEL_0 field width
#define WLAN_RF_DEBUG_SEL_0_WIDTH   ((uint32_t)0x00000004)

/// DEBUG_CLK_EN field reset value
#define WLAN_RF_DEBUG_CLK_EN_RST    0x0
/// DEBUG_SEL_3 field reset value
#define WLAN_RF_DEBUG_SEL_3_RST     0x3
/// DEBUG_SEL_2 field reset value
#define WLAN_RF_DEBUG_SEL_2_RST     0x2
/// DEBUG_SEL_1 field reset value
#define WLAN_RF_DEBUG_SEL_1_RST     0x1
/// DEBUG_SEL_0 field reset value
#define WLAN_RF_DEBUG_SEL_0_RST     0x0

/**
 * @brief Constructs a value for the WF_DEBUG_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] debugclken - The value to use for the debug_clk_en field.
 * @param[in] debugsel3 - The value to use for the debug_sel3 field.
 * @param[in] debugsel2 - The value to use for the debug_sel2 field.
 * @param[in] debugsel1 - The value to use for the debug_sel1 field.
 * @param[in] debugsel0 - The value to use for the debug_sel0 field.
 */
__INLINE void wlan_rf_wf_debug_reg_pack(uint8_t debugclken, uint8_t debugsel3, uint8_t debugsel2, uint8_t debugsel1, uint8_t debugsel0)
{
    REG_PL_WR(WLAN_RF_WF_DEBUG_REG_ADDR,  ((uint32_t)debugclken << 16) | ((uint32_t)debugsel3 << 12) | ((uint32_t)debugsel2 << 8) | ((uint32_t)debugsel1 << 4) | ((uint32_t)debugsel0 << 0));
}

/**
 * @brief Unpacks WF_DEBUG_REG's fields from current value of the WF_DEBUG_REG register.
 *
 * Reads the WF_DEBUG_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] debugclken - Will be populated with the current value of this field from the register.
 * @param[out] debugsel3 - Will be populated with the current value of this field from the register.
 * @param[out] debugsel2 - Will be populated with the current value of this field from the register.
 * @param[out] debugsel1 - Will be populated with the current value of this field from the register.
 * @param[out] debugsel0 - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_wf_debug_reg_unpack(uint8_t* debugclken, uint8_t* debugsel3, uint8_t* debugsel2, uint8_t* debugsel1, uint8_t* debugsel0)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR);

    *debugclken = (localVal & ((uint32_t)0x00010000)) >> 16;
    *debugsel3 = (localVal & ((uint32_t)0x0000F000)) >> 12;
    *debugsel2 = (localVal & ((uint32_t)0x00000F00)) >> 8;
    *debugsel1 = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *debugsel0 = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the debug_clk_en field in the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read and the debug_clk_en field's value will be returned.
 *
 * @return The current value of the debug_clk_en field in the WF_DEBUG_REG register.
 */
__INLINE uint8_t wlan_rf_debug_clk_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the debug_clk_en field of the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] debugclken - The value to set the field to.
 */
__INLINE void wlan_rf_debug_clk_en_setf(uint8_t debugclken)
{
    REG_PL_WR(WLAN_RF_WF_DEBUG_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)debugclken << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the debug_sel3 field in the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read and the debug_sel3 field's value will be returned.
 *
 * @return The current value of the debug_sel3 field in the WF_DEBUG_REG register.
 */
__INLINE uint8_t wlan_rf_debug_sel_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000F000)) >> 12);
}

/**
 * @brief Sets the debug_sel3 field of the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] debugsel3 - The value to set the field to.
 */
__INLINE void wlan_rf_debug_sel_3_setf(uint8_t debugsel3)
{
    REG_PL_WR(WLAN_RF_WF_DEBUG_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR) & ~((uint32_t)0x0000F000)) | (((uint32_t)debugsel3 << 12) & ((uint32_t)0x0000F000)));
}

/**
 * @brief Returns the current value of the debug_sel2 field in the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read and the debug_sel2 field's value will be returned.
 *
 * @return The current value of the debug_sel2 field in the WF_DEBUG_REG register.
 */
__INLINE uint8_t wlan_rf_debug_sel_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000F00)) >> 8);
}

/**
 * @brief Sets the debug_sel2 field of the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] debugsel2 - The value to set the field to.
 */
__INLINE void wlan_rf_debug_sel_2_setf(uint8_t debugsel2)
{
    REG_PL_WR(WLAN_RF_WF_DEBUG_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR) & ~((uint32_t)0x00000F00)) | (((uint32_t)debugsel2 << 8) & ((uint32_t)0x00000F00)));
}

/**
 * @brief Returns the current value of the debug_sel1 field in the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read and the debug_sel1 field's value will be returned.
 *
 * @return The current value of the debug_sel1 field in the WF_DEBUG_REG register.
 */
__INLINE uint8_t wlan_rf_debug_sel_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Sets the debug_sel1 field of the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] debugsel1 - The value to set the field to.
 */
__INLINE void wlan_rf_debug_sel_1_setf(uint8_t debugsel1)
{
    REG_PL_WR(WLAN_RF_WF_DEBUG_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR) & ~((uint32_t)0x000000F0)) | (((uint32_t)debugsel1 << 4) & ((uint32_t)0x000000F0)));
}

/**
 * @brief Returns the current value of the debug_sel0 field in the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read and the debug_sel0 field's value will be returned.
 *
 * @return The current value of the debug_sel0 field in the WF_DEBUG_REG register.
 */
__INLINE uint8_t wlan_rf_debug_sel_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the debug_sel0 field of the WF_DEBUG_REG register.
 *
 * The WF_DEBUG_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] debugsel0 - The value to set the field to.
 */
__INLINE void wlan_rf_debug_sel_0_setf(uint8_t debugsel0)
{
    REG_PL_WR(WLAN_RF_WF_DEBUG_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DEBUG_REG_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)debugsel0 << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name PU_DONE_REG register definitions
 * <table>
 * <caption id="PU_DONE_REG_BF">PU_DONE_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>04 <td>        pllon_done <td>W <td>R <td>0
 * <tr><td>03 <td>         rxon_done <td>W <td>R <td>0
 * <tr><td>02 <td>         txon_done <td>W <td>R <td>0
 * <tr><td>01 <td>  rxon_co_ant_done <td>W <td>R <td>0
 * <tr><td>00 <td>  txon_co_ant_done <td>W <td>R <td>0
 * </table>
 *
 * @{
 */

/// Address of the PU_DONE_REG register
#define WLAN_RF_PU_DONE_REG_ADDR   0x403440A8
/// Offset of the PU_DONE_REG register from the base address
#define WLAN_RF_PU_DONE_REG_OFFSET 0x000000A8
/// Index of the PU_DONE_REG register
#define WLAN_RF_PU_DONE_REG_INDEX  0x0000002A
/// Reset value of the PU_DONE_REG register
#define WLAN_RF_PU_DONE_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the PU_DONE_REG register.
 * The PU_DONE_REG register will be read and its value returned.
 * @return The current value of the PU_DONE_REG register.
 */
__INLINE uint32_t wlan_rf_pu_done_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_PU_DONE_REG_ADDR);
}

// field definitions
/// PLLON_DONE field bit
#define WLAN_RF_PLLON_DONE_BIT          ((uint32_t)0x00000010)
/// PLLON_DONE field position
#define WLAN_RF_PLLON_DONE_POS          4
/// RXON_DONE field bit
#define WLAN_RF_RXON_DONE_BIT           ((uint32_t)0x00000008)
/// RXON_DONE field position
#define WLAN_RF_RXON_DONE_POS           3
/// TXON_DONE field bit
#define WLAN_RF_TXON_DONE_BIT           ((uint32_t)0x00000004)
/// TXON_DONE field position
#define WLAN_RF_TXON_DONE_POS           2
/// RXON_CO_ANT_DONE field bit
#define WLAN_RF_RXON_CO_ANT_DONE_BIT    ((uint32_t)0x00000002)
/// RXON_CO_ANT_DONE field position
#define WLAN_RF_RXON_CO_ANT_DONE_POS    1
/// TXON_CO_ANT_DONE field bit
#define WLAN_RF_TXON_CO_ANT_DONE_BIT    ((uint32_t)0x00000001)
/// TXON_CO_ANT_DONE field position
#define WLAN_RF_TXON_CO_ANT_DONE_POS    0

/// PLLON_DONE field reset value
#define WLAN_RF_PLLON_DONE_RST          0x0
/// RXON_DONE field reset value
#define WLAN_RF_RXON_DONE_RST           0x0
/// TXON_DONE field reset value
#define WLAN_RF_TXON_DONE_RST           0x0
/// RXON_CO_ANT_DONE field reset value
#define WLAN_RF_RXON_CO_ANT_DONE_RST    0x0
/// TXON_CO_ANT_DONE field reset value
#define WLAN_RF_TXON_CO_ANT_DONE_RST    0x0

/**
 * @brief Unpacks PU_DONE_REG's fields from current value of the PU_DONE_REG register.
 *
 * Reads the PU_DONE_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] pllondone - Will be populated with the current value of this field from the register.
 * @param[out] rxondone - Will be populated with the current value of this field from the register.
 * @param[out] txondone - Will be populated with the current value of this field from the register.
 * @param[out] rxoncoantdone - Will be populated with the current value of this field from the register.
 * @param[out] txoncoantdone - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_pu_done_reg_unpack(uint8_t* pllondone, uint8_t* rxondone, uint8_t* txondone, uint8_t* rxoncoantdone, uint8_t* txoncoantdone)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_PU_DONE_REG_ADDR);

    *pllondone = (localVal & ((uint32_t)0x00000010)) >> 4;
    *rxondone = (localVal & ((uint32_t)0x00000008)) >> 3;
    *txondone = (localVal & ((uint32_t)0x00000004)) >> 2;
    *rxoncoantdone = (localVal & ((uint32_t)0x00000002)) >> 1;
    *txoncoantdone = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the pllon_done field in the PU_DONE_REG register.
 *
 * The PU_DONE_REG register will be read and the pllon_done field's value will be returned.
 *
 * @return The current value of the pllon_done field in the PU_DONE_REG register.
 */
__INLINE uint8_t wlan_rf_pllon_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_PU_DONE_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Returns the current value of the rxon_done field in the PU_DONE_REG register.
 *
 * The PU_DONE_REG register will be read and the rxon_done field's value will be returned.
 *
 * @return The current value of the rxon_done field in the PU_DONE_REG register.
 */
__INLINE uint8_t wlan_rf_rxon_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_PU_DONE_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Returns the current value of the txon_done field in the PU_DONE_REG register.
 *
 * The PU_DONE_REG register will be read and the txon_done field's value will be returned.
 *
 * @return The current value of the txon_done field in the PU_DONE_REG register.
 */
__INLINE uint8_t wlan_rf_txon_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_PU_DONE_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Returns the current value of the rxon_co_ant_done field in the PU_DONE_REG register.
 *
 * The PU_DONE_REG register will be read and the rxon_co_ant_done field's value will be returned.
 *
 * @return The current value of the rxon_co_ant_done field in the PU_DONE_REG register.
 */
__INLINE uint8_t wlan_rf_rxon_co_ant_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_PU_DONE_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Returns the current value of the txon_co_ant_done field in the PU_DONE_REG register.
 *
 * The PU_DONE_REG register will be read and the txon_co_ant_done field's value will be returned.
 *
 * @return The current value of the txon_co_ant_done field in the PU_DONE_REG register.
 */
__INLINE uint8_t wlan_rf_txon_co_ant_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_PU_DONE_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/// @}

/**
 * @name DIG_RESERVED_REG register definitions
 * <table>
 * <caption id="DIG_RESERVED_REG_BF">DIG_RESERVED_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>  dig_reserved_reg <td>R <td>R/W <td>0xFFFF0000
 * </table>
 *
 * @{
 */

/// Address of the DIG_RESERVED_REG register
#define WLAN_RF_DIG_RESERVED_REG_ADDR   0x403440AC
/// Offset of the DIG_RESERVED_REG register from the base address
#define WLAN_RF_DIG_RESERVED_REG_OFFSET 0x000000AC
/// Index of the DIG_RESERVED_REG register
#define WLAN_RF_DIG_RESERVED_REG_INDEX  0x0000002B
/// Reset value of the DIG_RESERVED_REG register
#define WLAN_RF_DIG_RESERVED_REG_RESET  0xFFFF0000

/**
 * @brief Returns the current value of the DIG_RESERVED_REG register.
 * The DIG_RESERVED_REG register will be read and its value returned.
 * @return The current value of the DIG_RESERVED_REG register.
 */
__INLINE uint32_t wlan_rf_dig_reserved_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_DIG_RESERVED_REG_ADDR);
}

/**
 * @brief Sets the DIG_RESERVED_REG register to a value.
 * The DIG_RESERVED_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_dig_reserved_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_DIG_RESERVED_REG_ADDR, value);
}

// field definitions
/// DIG_RESERVED_REG field mask
#define WLAN_RF_DIG_RESERVED_REG_MASK   ((uint32_t)0xFFFFFFFF)
/// DIG_RESERVED_REG field LSB position
#define WLAN_RF_DIG_RESERVED_REG_LSB    0
/// DIG_RESERVED_REG field width
#define WLAN_RF_DIG_RESERVED_REG_WIDTH  ((uint32_t)0x00000020)

/// DIG_RESERVED_REG field reset value
#define WLAN_RF_DIG_RESERVED_REG_RST    0xFFFF0000

/**
 * @brief Returns the current value of the dig_reserved_reg field in the DIG_RESERVED_REG register.
 *
 * The DIG_RESERVED_REG register will be read and the dig_reserved_reg field's value will be returned.
 *
 * @return The current value of the dig_reserved_reg field in the DIG_RESERVED_REG register.
 */
__INLINE uint32_t wlan_rf_dig_reserved_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_DIG_RESERVED_REG_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the dig_reserved_reg field of the DIG_RESERVED_REG register.
 *
 * The DIG_RESERVED_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] digreservedreg - The value to set the field to.
 */
__INLINE void wlan_rf_dig_reserved_reg_setf(uint32_t digreservedreg)
{
    REG_PL_WR(WLAN_RF_DIG_RESERVED_REG_ADDR, ((uint32_t)digreservedreg << 0) & ((uint32_t)0xFFFFFFFF));
}

/// @}

/**
 * @name AGC_RESERVED_REG register definitions
 * <table>
 * <caption id="AGC_RESERVED_REG_BF">AGC_RESERVED_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>02:00 <td>   wf_agc_rsvd_reg <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the AGC_RESERVED_REG register
#define WLAN_RF_AGC_RESERVED_REG_ADDR   0x403440B0
/// Offset of the AGC_RESERVED_REG register from the base address
#define WLAN_RF_AGC_RESERVED_REG_OFFSET 0x000000B0
/// Index of the AGC_RESERVED_REG register
#define WLAN_RF_AGC_RESERVED_REG_INDEX  0x0000002C
/// Reset value of the AGC_RESERVED_REG register
#define WLAN_RF_AGC_RESERVED_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the AGC_RESERVED_REG register.
 * The AGC_RESERVED_REG register will be read and its value returned.
 * @return The current value of the AGC_RESERVED_REG register.
 */
__INLINE uint32_t wlan_rf_agc_reserved_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_AGC_RESERVED_REG_ADDR);
}

/**
 * @brief Sets the AGC_RESERVED_REG register to a value.
 * The AGC_RESERVED_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_agc_reserved_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_AGC_RESERVED_REG_ADDR, value);
}

// field definitions
/// WF_AGC_RSVD_REG field mask
#define WLAN_RF_WF_AGC_RSVD_REG_MASK   ((uint32_t)0x00000007)
/// WF_AGC_RSVD_REG field LSB position
#define WLAN_RF_WF_AGC_RSVD_REG_LSB    0
/// WF_AGC_RSVD_REG field width
#define WLAN_RF_WF_AGC_RSVD_REG_WIDTH  ((uint32_t)0x00000003)

/// WF_AGC_RSVD_REG field reset value
#define WLAN_RF_WF_AGC_RSVD_REG_RST    0x0

/**
 * @brief Returns the current value of the wf_agc_rsvd_reg field in the AGC_RESERVED_REG register.
 *
 * The AGC_RESERVED_REG register will be read and the wf_agc_rsvd_reg field's value will be returned.
 *
 * @return The current value of the wf_agc_rsvd_reg field in the AGC_RESERVED_REG register.
 */
__INLINE uint8_t wlan_rf_wf_agc_rsvd_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_AGC_RESERVED_REG_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the wf_agc_rsvd_reg field of the AGC_RESERVED_REG register.
 *
 * The AGC_RESERVED_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfagcrsvdreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_agc_rsvd_reg_setf(uint8_t wfagcrsvdreg)
{
    REG_PL_WR(WLAN_RF_AGC_RESERVED_REG_ADDR, ((uint32_t)wfagcrsvdreg << 0) & ((uint32_t)0x00000007));
}

/// @}

/**
 * @name AGC_TABLE_OUT_REG0 register definitions
 * <table>
 * <caption id="AGC_TABLE_OUT_REG0_BF">AGC_TABLE_OUT_REG0 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   agc_table_out_0 <td>W <td>R <td>0xA1DD5829
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG0 register
#define WLAN_RF_AGC_TABLE_OUT_REG0_ADDR   0x403440B4
/// Offset of the AGC_TABLE_OUT_REG0 register from the base address
#define WLAN_RF_AGC_TABLE_OUT_REG0_OFFSET 0x000000B4
/// Index of the AGC_TABLE_OUT_REG0 register
#define WLAN_RF_AGC_TABLE_OUT_REG0_INDEX  0x0000002D
/// Reset value of the AGC_TABLE_OUT_REG0 register
#define WLAN_RF_AGC_TABLE_OUT_REG0_RESET  0xA1DD5829

/**
 * @brief Returns the current value of the AGC_TABLE_OUT_REG0 register.
 * The AGC_TABLE_OUT_REG0 register will be read and its value returned.
 * @return The current value of the AGC_TABLE_OUT_REG0 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out_reg0_get(void)
{
    return REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG0_ADDR);
}

// field definitions
/// AGC_TABLE_OUT__0 field mask
#define WLAN_RF_AGC_TABLE_OUT__0_MASK   ((uint32_t)0xFFFFFFFF)
/// AGC_TABLE_OUT__0 field LSB position
#define WLAN_RF_AGC_TABLE_OUT__0_LSB    0
/// AGC_TABLE_OUT__0 field width
#define WLAN_RF_AGC_TABLE_OUT__0_WIDTH  ((uint32_t)0x00000020)

/// AGC_TABLE_OUT__0 field reset value
#define WLAN_RF_AGC_TABLE_OUT__0_RST    0xA1DD5829

/**
 * @brief Returns the current value of the agc_table_out_0 field in the AGC_TABLE_OUT_REG0 register.
 *
 * The AGC_TABLE_OUT_REG0 register will be read and the agc_table_out_0 field's value will be returned.
 *
 * @return The current value of the agc_table_out_0 field in the AGC_TABLE_OUT_REG0 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out__0_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG0_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name AGC_TABLE_OUT_REG1 register definitions
 * <table>
 * <caption id="AGC_TABLE_OUT_REG1_BF">AGC_TABLE_OUT_REG1 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   agc_table_out_1 <td>W <td>R <td>0x3B967267
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG1 register
#define WLAN_RF_AGC_TABLE_OUT_REG1_ADDR   0x403440B8
/// Offset of the AGC_TABLE_OUT_REG1 register from the base address
#define WLAN_RF_AGC_TABLE_OUT_REG1_OFFSET 0x000000B8
/// Index of the AGC_TABLE_OUT_REG1 register
#define WLAN_RF_AGC_TABLE_OUT_REG1_INDEX  0x0000002E
/// Reset value of the AGC_TABLE_OUT_REG1 register
#define WLAN_RF_AGC_TABLE_OUT_REG1_RESET  0x3B967267

/**
 * @brief Returns the current value of the AGC_TABLE_OUT_REG1 register.
 * The AGC_TABLE_OUT_REG1 register will be read and its value returned.
 * @return The current value of the AGC_TABLE_OUT_REG1 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out_reg1_get(void)
{
    return REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG1_ADDR);
}

// field definitions
/// AGC_TABLE_OUT__1 field mask
#define WLAN_RF_AGC_TABLE_OUT__1_MASK   ((uint32_t)0xFFFFFFFF)
/// AGC_TABLE_OUT__1 field LSB position
#define WLAN_RF_AGC_TABLE_OUT__1_LSB    0
/// AGC_TABLE_OUT__1 field width
#define WLAN_RF_AGC_TABLE_OUT__1_WIDTH  ((uint32_t)0x00000020)

/// AGC_TABLE_OUT__1 field reset value
#define WLAN_RF_AGC_TABLE_OUT__1_RST    0x3B967267

/**
 * @brief Returns the current value of the agc_table_out_1 field in the AGC_TABLE_OUT_REG1 register.
 *
 * The AGC_TABLE_OUT_REG1 register will be read and the agc_table_out_1 field's value will be returned.
 *
 * @return The current value of the agc_table_out_1 field in the AGC_TABLE_OUT_REG1 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out__1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG1_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name AGC_TABLE_OUT_REG2 register definitions
 * <table>
 * <caption id="AGC_TABLE_OUT_REG2_BF">AGC_TABLE_OUT_REG2 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   agc_table_out_2 <td>W <td>R <td>0x8C0221B9
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG2 register
#define WLAN_RF_AGC_TABLE_OUT_REG2_ADDR   0x403440BC
/// Offset of the AGC_TABLE_OUT_REG2 register from the base address
#define WLAN_RF_AGC_TABLE_OUT_REG2_OFFSET 0x000000BC
/// Index of the AGC_TABLE_OUT_REG2 register
#define WLAN_RF_AGC_TABLE_OUT_REG2_INDEX  0x0000002F
/// Reset value of the AGC_TABLE_OUT_REG2 register
#define WLAN_RF_AGC_TABLE_OUT_REG2_RESET  0x8C0221B9

/**
 * @brief Returns the current value of the AGC_TABLE_OUT_REG2 register.
 * The AGC_TABLE_OUT_REG2 register will be read and its value returned.
 * @return The current value of the AGC_TABLE_OUT_REG2 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out_reg2_get(void)
{
    return REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG2_ADDR);
}

// field definitions
/// AGC_TABLE_OUT__2 field mask
#define WLAN_RF_AGC_TABLE_OUT__2_MASK   ((uint32_t)0xFFFFFFFF)
/// AGC_TABLE_OUT__2 field LSB position
#define WLAN_RF_AGC_TABLE_OUT__2_LSB    0
/// AGC_TABLE_OUT__2 field width
#define WLAN_RF_AGC_TABLE_OUT__2_WIDTH  ((uint32_t)0x00000020)

/// AGC_TABLE_OUT__2 field reset value
#define WLAN_RF_AGC_TABLE_OUT__2_RST    0x8C0221B9

/**
 * @brief Returns the current value of the agc_table_out_2 field in the AGC_TABLE_OUT_REG2 register.
 *
 * The AGC_TABLE_OUT_REG2 register will be read and the agc_table_out_2 field's value will be returned.
 *
 * @return The current value of the agc_table_out_2 field in the AGC_TABLE_OUT_REG2 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out__2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG2_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name AGC_TABLE_OUT_REG3 register definitions
 * <table>
 * <caption id="AGC_TABLE_OUT_REG3_BF">AGC_TABLE_OUT_REG3 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   agc_table_out_3 <td>W <td>R <td>0x40000022
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG3 register
#define WLAN_RF_AGC_TABLE_OUT_REG3_ADDR   0x403440C0
/// Offset of the AGC_TABLE_OUT_REG3 register from the base address
#define WLAN_RF_AGC_TABLE_OUT_REG3_OFFSET 0x000000C0
/// Index of the AGC_TABLE_OUT_REG3 register
#define WLAN_RF_AGC_TABLE_OUT_REG3_INDEX  0x00000030
/// Reset value of the AGC_TABLE_OUT_REG3 register
#define WLAN_RF_AGC_TABLE_OUT_REG3_RESET  0x40000022

/**
 * @brief Returns the current value of the AGC_TABLE_OUT_REG3 register.
 * The AGC_TABLE_OUT_REG3 register will be read and its value returned.
 * @return The current value of the AGC_TABLE_OUT_REG3 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out_reg3_get(void)
{
    return REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG3_ADDR);
}

// field definitions
/// AGC_TABLE_OUT__3 field mask
#define WLAN_RF_AGC_TABLE_OUT__3_MASK   ((uint32_t)0xFFFFFFFF)
/// AGC_TABLE_OUT__3 field LSB position
#define WLAN_RF_AGC_TABLE_OUT__3_LSB    0
/// AGC_TABLE_OUT__3 field width
#define WLAN_RF_AGC_TABLE_OUT__3_WIDTH  ((uint32_t)0x00000020)

/// AGC_TABLE_OUT__3 field reset value
#define WLAN_RF_AGC_TABLE_OUT__3_RST    0x40000022

/**
 * @brief Returns the current value of the agc_table_out_3 field in the AGC_TABLE_OUT_REG3 register.
 *
 * The AGC_TABLE_OUT_REG3 register will be read and the agc_table_out_3 field's value will be returned.
 *
 * @return The current value of the agc_table_out_3 field in the AGC_TABLE_OUT_REG3 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out__3_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG3_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name AGC_TABLE_OUT_REG4 register definitions
 * <table>
 * <caption id="AGC_TABLE_OUT_REG4_BF">AGC_TABLE_OUT_REG4 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   agc_table_out_4 <td>W <td>R <td>0x4040732
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG4 register
#define WLAN_RF_AGC_TABLE_OUT_REG4_ADDR   0x403440C4
/// Offset of the AGC_TABLE_OUT_REG4 register from the base address
#define WLAN_RF_AGC_TABLE_OUT_REG4_OFFSET 0x000000C4
/// Index of the AGC_TABLE_OUT_REG4 register
#define WLAN_RF_AGC_TABLE_OUT_REG4_INDEX  0x00000031
/// Reset value of the AGC_TABLE_OUT_REG4 register
#define WLAN_RF_AGC_TABLE_OUT_REG4_RESET  0x04040732

/**
 * @brief Returns the current value of the AGC_TABLE_OUT_REG4 register.
 * The AGC_TABLE_OUT_REG4 register will be read and its value returned.
 * @return The current value of the AGC_TABLE_OUT_REG4 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out_reg4_get(void)
{
    return REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG4_ADDR);
}

// field definitions
/// AGC_TABLE_OUT__4 field mask
#define WLAN_RF_AGC_TABLE_OUT__4_MASK   ((uint32_t)0xFFFFFFFF)
/// AGC_TABLE_OUT__4 field LSB position
#define WLAN_RF_AGC_TABLE_OUT__4_LSB    0
/// AGC_TABLE_OUT__4 field width
#define WLAN_RF_AGC_TABLE_OUT__4_WIDTH  ((uint32_t)0x00000020)

/// AGC_TABLE_OUT__4 field reset value
#define WLAN_RF_AGC_TABLE_OUT__4_RST    0x4040732

/**
 * @brief Returns the current value of the agc_table_out_4 field in the AGC_TABLE_OUT_REG4 register.
 *
 * The AGC_TABLE_OUT_REG4 register will be read and the agc_table_out_4 field's value will be returned.
 *
 * @return The current value of the agc_table_out_4 field in the AGC_TABLE_OUT_REG4 register.
 */
__INLINE uint32_t wlan_rf_agc_table_out__4_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_AGC_TABLE_OUT_REG4_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name APC_RESERVED_REG register definitions
 * <table>
 * <caption id="APC_RESERVED_REG_BF">APC_RESERVED_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>06:00 <td>   wf_apc_rsvd_reg <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the APC_RESERVED_REG register
#define WLAN_RF_APC_RESERVED_REG_ADDR   0x403440C8
/// Offset of the APC_RESERVED_REG register from the base address
#define WLAN_RF_APC_RESERVED_REG_OFFSET 0x000000C8
/// Index of the APC_RESERVED_REG register
#define WLAN_RF_APC_RESERVED_REG_INDEX  0x00000032
/// Reset value of the APC_RESERVED_REG register
#define WLAN_RF_APC_RESERVED_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the APC_RESERVED_REG register.
 * The APC_RESERVED_REG register will be read and its value returned.
 * @return The current value of the APC_RESERVED_REG register.
 */
__INLINE uint32_t wlan_rf_apc_reserved_reg_get(void)
{
    return REG_PL_RD(WLAN_RF_APC_RESERVED_REG_ADDR);
}

/**
 * @brief Sets the APC_RESERVED_REG register to a value.
 * The APC_RESERVED_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_apc_reserved_reg_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_APC_RESERVED_REG_ADDR, value);
}

// field definitions
/// WF_APC_RSVD_REG field mask
#define WLAN_RF_WF_APC_RSVD_REG_MASK   ((uint32_t)0x0000007F)
/// WF_APC_RSVD_REG field LSB position
#define WLAN_RF_WF_APC_RSVD_REG_LSB    0
/// WF_APC_RSVD_REG field width
#define WLAN_RF_WF_APC_RSVD_REG_WIDTH  ((uint32_t)0x00000007)

/// WF_APC_RSVD_REG field reset value
#define WLAN_RF_WF_APC_RSVD_REG_RST    0x0

/**
 * @brief Returns the current value of the wf_apc_rsvd_reg field in the APC_RESERVED_REG register.
 *
 * The APC_RESERVED_REG register will be read and the wf_apc_rsvd_reg field's value will be returned.
 *
 * @return The current value of the wf_apc_rsvd_reg field in the APC_RESERVED_REG register.
 */
__INLINE uint8_t wlan_rf_wf_apc_rsvd_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_APC_RESERVED_REG_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the wf_apc_rsvd_reg field of the APC_RESERVED_REG register.
 *
 * The APC_RESERVED_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfapcrsvdreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_apc_rsvd_reg_setf(uint8_t wfapcrsvdreg)
{
    REG_PL_WR(WLAN_RF_APC_RESERVED_REG_ADDR, ((uint32_t)wfapcrsvdreg << 0) & ((uint32_t)0x0000007F));
}

/// @}

/**
 * @name APC_TABLE_OUT_REG0 register definitions
 * <table>
 * <caption id="APC_TABLE_OUT_REG0_BF">APC_TABLE_OUT_REG0 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   apc_table_out_0 <td>W <td>R <td>0x505C0FFF
 * </table>
 *
 * @{
 */

/// Address of the APC_TABLE_OUT_REG0 register
#define WLAN_RF_APC_TABLE_OUT_REG0_ADDR   0x403440CC
/// Offset of the APC_TABLE_OUT_REG0 register from the base address
#define WLAN_RF_APC_TABLE_OUT_REG0_OFFSET 0x000000CC
/// Index of the APC_TABLE_OUT_REG0 register
#define WLAN_RF_APC_TABLE_OUT_REG0_INDEX  0x00000033
/// Reset value of the APC_TABLE_OUT_REG0 register
#define WLAN_RF_APC_TABLE_OUT_REG0_RESET  0x505C0FFF

/**
 * @brief Returns the current value of the APC_TABLE_OUT_REG0 register.
 * The APC_TABLE_OUT_REG0 register will be read and its value returned.
 * @return The current value of the APC_TABLE_OUT_REG0 register.
 */
__INLINE uint32_t wlan_rf_apc_table_out_reg0_get(void)
{
    return REG_PL_RD(WLAN_RF_APC_TABLE_OUT_REG0_ADDR);
}

// field definitions
/// APC_TABLE_OUT__0 field mask
#define WLAN_RF_APC_TABLE_OUT__0_MASK   ((uint32_t)0xFFFFFFFF)
/// APC_TABLE_OUT__0 field LSB position
#define WLAN_RF_APC_TABLE_OUT__0_LSB    0
/// APC_TABLE_OUT__0 field width
#define WLAN_RF_APC_TABLE_OUT__0_WIDTH  ((uint32_t)0x00000020)

/// APC_TABLE_OUT__0 field reset value
#define WLAN_RF_APC_TABLE_OUT__0_RST    0x505C0FFF

/**
 * @brief Returns the current value of the apc_table_out_0 field in the APC_TABLE_OUT_REG0 register.
 *
 * The APC_TABLE_OUT_REG0 register will be read and the apc_table_out_0 field's value will be returned.
 *
 * @return The current value of the apc_table_out_0 field in the APC_TABLE_OUT_REG0 register.
 */
__INLINE uint32_t wlan_rf_apc_table_out__0_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_APC_TABLE_OUT_REG0_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name APC_TABLE_OUT_REG1 register definitions
 * <table>
 * <caption id="APC_TABLE_OUT_REG1_BF">APC_TABLE_OUT_REG1 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   apc_table_out_1 <td>W <td>R <td>0x443E424D
 * </table>
 *
 * @{
 */

/// Address of the APC_TABLE_OUT_REG1 register
#define WLAN_RF_APC_TABLE_OUT_REG1_ADDR   0x403440D0
/// Offset of the APC_TABLE_OUT_REG1 register from the base address
#define WLAN_RF_APC_TABLE_OUT_REG1_OFFSET 0x000000D0
/// Index of the APC_TABLE_OUT_REG1 register
#define WLAN_RF_APC_TABLE_OUT_REG1_INDEX  0x00000034
/// Reset value of the APC_TABLE_OUT_REG1 register
#define WLAN_RF_APC_TABLE_OUT_REG1_RESET  0x443E424D

/**
 * @brief Returns the current value of the APC_TABLE_OUT_REG1 register.
 * The APC_TABLE_OUT_REG1 register will be read and its value returned.
 * @return The current value of the APC_TABLE_OUT_REG1 register.
 */
__INLINE uint32_t wlan_rf_apc_table_out_reg1_get(void)
{
    return REG_PL_RD(WLAN_RF_APC_TABLE_OUT_REG1_ADDR);
}

// field definitions
/// APC_TABLE_OUT__1 field mask
#define WLAN_RF_APC_TABLE_OUT__1_MASK   ((uint32_t)0xFFFFFFFF)
/// APC_TABLE_OUT__1 field LSB position
#define WLAN_RF_APC_TABLE_OUT__1_LSB    0
/// APC_TABLE_OUT__1 field width
#define WLAN_RF_APC_TABLE_OUT__1_WIDTH  ((uint32_t)0x00000020)

/// APC_TABLE_OUT__1 field reset value
#define WLAN_RF_APC_TABLE_OUT__1_RST    0x443E424D

/**
 * @brief Returns the current value of the apc_table_out_1 field in the APC_TABLE_OUT_REG1 register.
 *
 * The APC_TABLE_OUT_REG1 register will be read and the apc_table_out_1 field's value will be returned.
 *
 * @return The current value of the apc_table_out_1 field in the APC_TABLE_OUT_REG1 register.
 */
__INLINE uint32_t wlan_rf_apc_table_out__1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_APC_TABLE_OUT_REG1_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name APC_TABLE_OUT_REG2 register definitions
 * <table>
 * <caption id="APC_TABLE_OUT_REG2_BF">APC_TABLE_OUT_REG2 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   apc_table_out_2 <td>W <td>R <td>0x4410EF2
 * </table>
 *
 * @{
 */

/// Address of the APC_TABLE_OUT_REG2 register
#define WLAN_RF_APC_TABLE_OUT_REG2_ADDR   0x403440D4
/// Offset of the APC_TABLE_OUT_REG2 register from the base address
#define WLAN_RF_APC_TABLE_OUT_REG2_OFFSET 0x000000D4
/// Index of the APC_TABLE_OUT_REG2 register
#define WLAN_RF_APC_TABLE_OUT_REG2_INDEX  0x00000035
/// Reset value of the APC_TABLE_OUT_REG2 register
#define WLAN_RF_APC_TABLE_OUT_REG2_RESET  0x04410EF2

/**
 * @brief Returns the current value of the APC_TABLE_OUT_REG2 register.
 * The APC_TABLE_OUT_REG2 register will be read and its value returned.
 * @return The current value of the APC_TABLE_OUT_REG2 register.
 */
__INLINE uint32_t wlan_rf_apc_table_out_reg2_get(void)
{
    return REG_PL_RD(WLAN_RF_APC_TABLE_OUT_REG2_ADDR);
}

// field definitions
/// APC_TABLE_OUT__2 field mask
#define WLAN_RF_APC_TABLE_OUT__2_MASK   ((uint32_t)0xFFFFFFFF)
/// APC_TABLE_OUT__2 field LSB position
#define WLAN_RF_APC_TABLE_OUT__2_LSB    0
/// APC_TABLE_OUT__2 field width
#define WLAN_RF_APC_TABLE_OUT__2_WIDTH  ((uint32_t)0x00000020)

/// APC_TABLE_OUT__2 field reset value
#define WLAN_RF_APC_TABLE_OUT__2_RST    0x4410EF2

/**
 * @brief Returns the current value of the apc_table_out_2 field in the APC_TABLE_OUT_REG2 register.
 *
 * The APC_TABLE_OUT_REG2 register will be read and the apc_table_out_2 field's value will be returned.
 *
 * @return The current value of the apc_table_out_2 field in the APC_TABLE_OUT_REG2 register.
 */
__INLINE uint32_t wlan_rf_apc_table_out__2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_APC_TABLE_OUT_REG2_ADDR);
    return (localVal >> 0);
}

/// @}


#endif // _REG_WLAN_RF_H_

/// @}

