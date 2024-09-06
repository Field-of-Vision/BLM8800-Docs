/**
 * @file reg_bt_rf.h
 * @brief Definitions of the BT_RF HW block registers and register access functions.
 *
 * @defgroup REG_BT_RF REG_BT_RF
 * @ingroup REG
 * @{
 *
 * @brief Definitions of the BT_RF HW block registers and register access functions.
 */
#ifndef _REG_BT_RF_H_
#define _REG_BT_RF_H_

#include "compiler.h"
#include "arch.h"
#include "reg_access.h"

/** @brief Number of registers in the REG_BT_RF peripheral.
 */
#define REG_BT_RF_COUNT 26

/** @brief Decoding mask of the REG_BT_RF peripheral registers from the CPU point of view.
 */
#define REG_BT_RF_DECODING_MASK 0x0000007F

/**
 * @name REG_00 register definitions
 * <table>
 * <caption id="REG_00_BF">REG_00 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>      bt_pu_lna_dr <td>R <td>R/W <td>0
 * <tr><td>30 <td>     bt_pu_lna_reg <td>R <td>R/W <td>0
 * <tr><td>29 <td>bt_trx24g_wf2bt_en_dr <td>R <td>R/W <td>0
 * <tr><td>28 <td>bt_trx24g_wf2bt_en_reg <td>R <td>R/W <td>0
 * <tr><td>27 <td>      bt_pu_rmx_dr <td>R <td>R/W <td>0
 * <tr><td>26 <td>     bt_pu_rmx_reg <td>R <td>R/W <td>0
 * <tr><td>25 <td>      bt_pu_tia_dr <td>R <td>R/W <td>0
 * <tr><td>24 <td>     bt_pu_tia_reg <td>R <td>R/W <td>0
 * <tr><td>23 <td>    bt_tia_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>22 <td>   bt_tia_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>21 <td>  bt_pu_sdm_adc_dr <td>R <td>R/W <td>0
 * <tr><td>20 <td> bt_pu_sdm_adc_reg <td>R <td>R/W <td>0
 * <tr><td>19 <td>bt_sdm_adc_byp_mode_dr <td>R <td>R/W <td>0
 * <tr><td>18 <td>bt_sdm_adc_byp_mode_reg <td>R <td>R/W <td>0
 * <tr><td>17 <td>bt_sdm_adc_dig_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>16 <td>bt_sdm_adc_dig_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>15 <td>  bt_pu_dpa_ldo_dr <td>R <td>R/W <td>0
 * <tr><td>14 <td> bt_pu_dpa_ldo_reg <td>R <td>R/W <td>0
 * <tr><td>13 <td>bt_pu_dly_dpa_ldo_dr <td>R <td>R/W <td>0
 * <tr><td>12 <td>bt_pu_dly_dpa_ldo_reg <td>R <td>R/W <td>0
 * <tr><td>11 <td>      bt_pu_dpa_dr <td>R <td>R/W <td>0
 * <tr><td>10 <td>     bt_pu_dpa_reg <td>R <td>R/W <td>0
 * <tr><td>09 <td>bt_dpa_clk2dac_intf_en_dr <td>R <td>R/W <td>0
 * <tr><td>08 <td>bt_dpa_clk2dac_intf_en_reg <td>R <td>R/W <td>0
 * <tr><td>07 <td>bt_dpa_cdr_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>06 <td>bt_dpa_cdr_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>05 <td>bt_dpa_bt2wf_en_dr <td>R <td>R/W <td>0
 * <tr><td>04 <td>bt_dpa_bt2wf_en_reg <td>R <td>R/W <td>0
 * <tr><td>03 <td>      bt_pu_dco_dr <td>R <td>R/W <td>0
 * <tr><td>02 <td>     bt_pu_dco_reg <td>R <td>R/W <td>0
 * <tr><td>01 <td> bt_dco_rxlo_en_dr <td>R <td>R/W <td>0
 * <tr><td>00 <td>bt_dco_rxlo_en_reg <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_00 register
#define BT_RF_REG_00_ADDR   0x40622000
/// Offset of the REG_00 register from the base address
#define BT_RF_REG_00_OFFSET 0x00000000
/// Index of the REG_00 register
#define BT_RF_REG_00_INDEX  0x00000000
/// Reset value of the REG_00 register
#define BT_RF_REG_00_RESET  0x00000000

/**
 * @brief Returns the current value of the REG_00 register.
 * The REG_00 register will be read and its value returned.
 * @return The current value of the REG_00 register.
 */
__INLINE uint32_t bt_rf_reg_00_get(void)
{
    return REG_PL_RD(BT_RF_REG_00_ADDR);
}

/**
 * @brief Sets the REG_00 register to a value.
 * The REG_00 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_00_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, value);
}

// field definitions
/// BT_PU_LNA_DR field bit
#define BT_RF_BT_PU_LNA_DR_BIT                   ((uint32_t)0x80000000)
/// BT_PU_LNA_DR field position
#define BT_RF_BT_PU_LNA_DR_POS                   31
/// BT_PU_LNA_REG field bit
#define BT_RF_BT_PU_LNA_REG_BIT                  ((uint32_t)0x40000000)
/// BT_PU_LNA_REG field position
#define BT_RF_BT_PU_LNA_REG_POS                  30
/// BT_TRX_24G_WF_2BT_EN_DR field bit
#define BT_RF_BT_TRX_24G_WF_2BT_EN_DR_BIT        ((uint32_t)0x20000000)
/// BT_TRX_24G_WF_2BT_EN_DR field position
#define BT_RF_BT_TRX_24G_WF_2BT_EN_DR_POS        29
/// BT_TRX_24G_WF_2BT_EN_REG field bit
#define BT_RF_BT_TRX_24G_WF_2BT_EN_REG_BIT       ((uint32_t)0x10000000)
/// BT_TRX_24G_WF_2BT_EN_REG field position
#define BT_RF_BT_TRX_24G_WF_2BT_EN_REG_POS       28
/// BT_PU_RMX_DR field bit
#define BT_RF_BT_PU_RMX_DR_BIT                   ((uint32_t)0x08000000)
/// BT_PU_RMX_DR field position
#define BT_RF_BT_PU_RMX_DR_POS                   27
/// BT_PU_RMX_REG field bit
#define BT_RF_BT_PU_RMX_REG_BIT                  ((uint32_t)0x04000000)
/// BT_PU_RMX_REG field position
#define BT_RF_BT_PU_RMX_REG_POS                  26
/// BT_PU_TIA_DR field bit
#define BT_RF_BT_PU_TIA_DR_BIT                   ((uint32_t)0x02000000)
/// BT_PU_TIA_DR field position
#define BT_RF_BT_PU_TIA_DR_POS                   25
/// BT_PU_TIA_REG field bit
#define BT_RF_BT_PU_TIA_REG_BIT                  ((uint32_t)0x01000000)
/// BT_PU_TIA_REG field position
#define BT_RF_BT_PU_TIA_REG_POS                  24
/// BT_TIA_RSTN_DR field bit
#define BT_RF_BT_TIA_RSTN_DR_BIT                 ((uint32_t)0x00800000)
/// BT_TIA_RSTN_DR field position
#define BT_RF_BT_TIA_RSTN_DR_POS                 23
/// BT_TIA_RSTN_REG field bit
#define BT_RF_BT_TIA_RSTN_REG_BIT                ((uint32_t)0x00400000)
/// BT_TIA_RSTN_REG field position
#define BT_RF_BT_TIA_RSTN_REG_POS                22
/// BT_PU_SDM_ADC_DR field bit
#define BT_RF_BT_PU_SDM_ADC_DR_BIT               ((uint32_t)0x00200000)
/// BT_PU_SDM_ADC_DR field position
#define BT_RF_BT_PU_SDM_ADC_DR_POS               21
/// BT_PU_SDM_ADC_REG field bit
#define BT_RF_BT_PU_SDM_ADC_REG_BIT              ((uint32_t)0x00100000)
/// BT_PU_SDM_ADC_REG field position
#define BT_RF_BT_PU_SDM_ADC_REG_POS              20
/// BT_SDM_ADC_BYP_MODE_DR field bit
#define BT_RF_BT_SDM_ADC_BYP_MODE_DR_BIT         ((uint32_t)0x00080000)
/// BT_SDM_ADC_BYP_MODE_DR field position
#define BT_RF_BT_SDM_ADC_BYP_MODE_DR_POS         19
/// BT_SDM_ADC_BYP_MODE_REG field bit
#define BT_RF_BT_SDM_ADC_BYP_MODE_REG_BIT        ((uint32_t)0x00040000)
/// BT_SDM_ADC_BYP_MODE_REG field position
#define BT_RF_BT_SDM_ADC_BYP_MODE_REG_POS        18
/// BT_SDM_ADC_DIG_RSTN_DR field bit
#define BT_RF_BT_SDM_ADC_DIG_RSTN_DR_BIT         ((uint32_t)0x00020000)
/// BT_SDM_ADC_DIG_RSTN_DR field position
#define BT_RF_BT_SDM_ADC_DIG_RSTN_DR_POS         17
/// BT_SDM_ADC_DIG_RSTN_REG field bit
#define BT_RF_BT_SDM_ADC_DIG_RSTN_REG_BIT        ((uint32_t)0x00010000)
/// BT_SDM_ADC_DIG_RSTN_REG field position
#define BT_RF_BT_SDM_ADC_DIG_RSTN_REG_POS        16
/// BT_PU_DPA_LDO_DR field bit
#define BT_RF_BT_PU_DPA_LDO_DR_BIT               ((uint32_t)0x00008000)
/// BT_PU_DPA_LDO_DR field position
#define BT_RF_BT_PU_DPA_LDO_DR_POS               15
/// BT_PU_DPA_LDO_REG field bit
#define BT_RF_BT_PU_DPA_LDO_REG_BIT              ((uint32_t)0x00004000)
/// BT_PU_DPA_LDO_REG field position
#define BT_RF_BT_PU_DPA_LDO_REG_POS              14
/// BT_PU_DLY_DPA_LDO_DR field bit
#define BT_RF_BT_PU_DLY_DPA_LDO_DR_BIT           ((uint32_t)0x00002000)
/// BT_PU_DLY_DPA_LDO_DR field position
#define BT_RF_BT_PU_DLY_DPA_LDO_DR_POS           13
/// BT_PU_DLY_DPA_LDO_REG field bit
#define BT_RF_BT_PU_DLY_DPA_LDO_REG_BIT          ((uint32_t)0x00001000)
/// BT_PU_DLY_DPA_LDO_REG field position
#define BT_RF_BT_PU_DLY_DPA_LDO_REG_POS          12
/// BT_PU_DPA_DR field bit
#define BT_RF_BT_PU_DPA_DR_BIT                   ((uint32_t)0x00000800)
/// BT_PU_DPA_DR field position
#define BT_RF_BT_PU_DPA_DR_POS                   11
/// BT_PU_DPA_REG field bit
#define BT_RF_BT_PU_DPA_REG_BIT                  ((uint32_t)0x00000400)
/// BT_PU_DPA_REG field position
#define BT_RF_BT_PU_DPA_REG_POS                  10
/// BT_DPA_CLK_2DAC_INTF_EN_DR field bit
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_DR_BIT     ((uint32_t)0x00000200)
/// BT_DPA_CLK_2DAC_INTF_EN_DR field position
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_DR_POS     9
/// BT_DPA_CLK_2DAC_INTF_EN_REG field bit
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_REG_BIT    ((uint32_t)0x00000100)
/// BT_DPA_CLK_2DAC_INTF_EN_REG field position
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_REG_POS    8
/// BT_DPA_CDR_RSTN_DR field bit
#define BT_RF_BT_DPA_CDR_RSTN_DR_BIT             ((uint32_t)0x00000080)
/// BT_DPA_CDR_RSTN_DR field position
#define BT_RF_BT_DPA_CDR_RSTN_DR_POS             7
/// BT_DPA_CDR_RSTN_REG field bit
#define BT_RF_BT_DPA_CDR_RSTN_REG_BIT            ((uint32_t)0x00000040)
/// BT_DPA_CDR_RSTN_REG field position
#define BT_RF_BT_DPA_CDR_RSTN_REG_POS            6
/// BT_DPA_BT_2WF_EN_DR field bit
#define BT_RF_BT_DPA_BT_2WF_EN_DR_BIT            ((uint32_t)0x00000020)
/// BT_DPA_BT_2WF_EN_DR field position
#define BT_RF_BT_DPA_BT_2WF_EN_DR_POS            5
/// BT_DPA_BT_2WF_EN_REG field bit
#define BT_RF_BT_DPA_BT_2WF_EN_REG_BIT           ((uint32_t)0x00000010)
/// BT_DPA_BT_2WF_EN_REG field position
#define BT_RF_BT_DPA_BT_2WF_EN_REG_POS           4
/// BT_PU_DCO_DR field bit
#define BT_RF_BT_PU_DCO_DR_BIT                   ((uint32_t)0x00000008)
/// BT_PU_DCO_DR field position
#define BT_RF_BT_PU_DCO_DR_POS                   3
/// BT_PU_DCO_REG field bit
#define BT_RF_BT_PU_DCO_REG_BIT                  ((uint32_t)0x00000004)
/// BT_PU_DCO_REG field position
#define BT_RF_BT_PU_DCO_REG_POS                  2
/// BT_DCO_RXLO_EN_DR field bit
#define BT_RF_BT_DCO_RXLO_EN_DR_BIT              ((uint32_t)0x00000002)
/// BT_DCO_RXLO_EN_DR field position
#define BT_RF_BT_DCO_RXLO_EN_DR_POS              1
/// BT_DCO_RXLO_EN_REG field bit
#define BT_RF_BT_DCO_RXLO_EN_REG_BIT             ((uint32_t)0x00000001)
/// BT_DCO_RXLO_EN_REG field position
#define BT_RF_BT_DCO_RXLO_EN_REG_POS             0

/// BT_PU_LNA_DR field reset value
#define BT_RF_BT_PU_LNA_DR_RST                   0x0
/// BT_PU_LNA_REG field reset value
#define BT_RF_BT_PU_LNA_REG_RST                  0x0
/// BT_TRX_24G_WF_2BT_EN_DR field reset value
#define BT_RF_BT_TRX_24G_WF_2BT_EN_DR_RST        0x0
/// BT_TRX_24G_WF_2BT_EN_REG field reset value
#define BT_RF_BT_TRX_24G_WF_2BT_EN_REG_RST       0x0
/// BT_PU_RMX_DR field reset value
#define BT_RF_BT_PU_RMX_DR_RST                   0x0
/// BT_PU_RMX_REG field reset value
#define BT_RF_BT_PU_RMX_REG_RST                  0x0
/// BT_PU_TIA_DR field reset value
#define BT_RF_BT_PU_TIA_DR_RST                   0x0
/// BT_PU_TIA_REG field reset value
#define BT_RF_BT_PU_TIA_REG_RST                  0x0
/// BT_TIA_RSTN_DR field reset value
#define BT_RF_BT_TIA_RSTN_DR_RST                 0x0
/// BT_TIA_RSTN_REG field reset value
#define BT_RF_BT_TIA_RSTN_REG_RST                0x0
/// BT_PU_SDM_ADC_DR field reset value
#define BT_RF_BT_PU_SDM_ADC_DR_RST               0x0
/// BT_PU_SDM_ADC_REG field reset value
#define BT_RF_BT_PU_SDM_ADC_REG_RST              0x0
/// BT_SDM_ADC_BYP_MODE_DR field reset value
#define BT_RF_BT_SDM_ADC_BYP_MODE_DR_RST         0x0
/// BT_SDM_ADC_BYP_MODE_REG field reset value
#define BT_RF_BT_SDM_ADC_BYP_MODE_REG_RST        0x0
/// BT_SDM_ADC_DIG_RSTN_DR field reset value
#define BT_RF_BT_SDM_ADC_DIG_RSTN_DR_RST         0x0
/// BT_SDM_ADC_DIG_RSTN_REG field reset value
#define BT_RF_BT_SDM_ADC_DIG_RSTN_REG_RST        0x0
/// BT_PU_DPA_LDO_DR field reset value
#define BT_RF_BT_PU_DPA_LDO_DR_RST               0x0
/// BT_PU_DPA_LDO_REG field reset value
#define BT_RF_BT_PU_DPA_LDO_REG_RST              0x0
/// BT_PU_DLY_DPA_LDO_DR field reset value
#define BT_RF_BT_PU_DLY_DPA_LDO_DR_RST           0x0
/// BT_PU_DLY_DPA_LDO_REG field reset value
#define BT_RF_BT_PU_DLY_DPA_LDO_REG_RST          0x0
/// BT_PU_DPA_DR field reset value
#define BT_RF_BT_PU_DPA_DR_RST                   0x0
/// BT_PU_DPA_REG field reset value
#define BT_RF_BT_PU_DPA_REG_RST                  0x0
/// BT_DPA_CLK_2DAC_INTF_EN_DR field reset value
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_DR_RST     0x0
/// BT_DPA_CLK_2DAC_INTF_EN_REG field reset value
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_REG_RST    0x0
/// BT_DPA_CDR_RSTN_DR field reset value
#define BT_RF_BT_DPA_CDR_RSTN_DR_RST             0x0
/// BT_DPA_CDR_RSTN_REG field reset value
#define BT_RF_BT_DPA_CDR_RSTN_REG_RST            0x0
/// BT_DPA_BT_2WF_EN_DR field reset value
#define BT_RF_BT_DPA_BT_2WF_EN_DR_RST            0x0
/// BT_DPA_BT_2WF_EN_REG field reset value
#define BT_RF_BT_DPA_BT_2WF_EN_REG_RST           0x0
/// BT_PU_DCO_DR field reset value
#define BT_RF_BT_PU_DCO_DR_RST                   0x0
/// BT_PU_DCO_REG field reset value
#define BT_RF_BT_PU_DCO_REG_RST                  0x0
/// BT_DCO_RXLO_EN_DR field reset value
#define BT_RF_BT_DCO_RXLO_EN_DR_RST              0x0
/// BT_DCO_RXLO_EN_REG field reset value
#define BT_RF_BT_DCO_RXLO_EN_REG_RST             0x0

/**
 * @brief Constructs a value for the REG_00 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btpulnadr - The value to use for the bt_pu_lna_dr field.
 * @param[in] btpulnareg - The value to use for the bt_pu_lna_reg field.
 * @param[in] bttrx24gwf2btendr - The value to use for the bt_trx24g_wf2bt_en_dr field.
 * @param[in] bttrx24gwf2btenreg - The value to use for the bt_trx24g_wf2bt_en_reg field.
 * @param[in] btpurmxdr - The value to use for the bt_pu_rmx_dr field.
 * @param[in] btpurmxreg - The value to use for the bt_pu_rmx_reg field.
 * @param[in] btputiadr - The value to use for the bt_pu_tia_dr field.
 * @param[in] btputiareg - The value to use for the bt_pu_tia_reg field.
 * @param[in] bttiarstndr - The value to use for the bt_tia_rstn_dr field.
 * @param[in] bttiarstnreg - The value to use for the bt_tia_rstn_reg field.
 * @param[in] btpusdmadcdr - The value to use for the bt_pu_sdm_adc_dr field.
 * @param[in] btpusdmadcreg - The value to use for the bt_pu_sdm_adc_reg field.
 * @param[in] btsdmadcbypmodedr - The value to use for the bt_sdm_adc_byp_mode_dr field.
 * @param[in] btsdmadcbypmodereg - The value to use for the bt_sdm_adc_byp_mode_reg field.
 * @param[in] btsdmadcdigrstndr - The value to use for the bt_sdm_adc_dig_rstn_dr field.
 * @param[in] btsdmadcdigrstnreg - The value to use for the bt_sdm_adc_dig_rstn_reg field.
 * @param[in] btpudpaldodr - The value to use for the bt_pu_dpa_ldo_dr field.
 * @param[in] btpudpaldoreg - The value to use for the bt_pu_dpa_ldo_reg field.
 * @param[in] btpudlydpaldodr - The value to use for the bt_pu_dly_dpa_ldo_dr field.
 * @param[in] btpudlydpaldoreg - The value to use for the bt_pu_dly_dpa_ldo_reg field.
 * @param[in] btpudpadr - The value to use for the bt_pu_dpa_dr field.
 * @param[in] btpudpareg - The value to use for the bt_pu_dpa_reg field.
 * @param[in] btdpaclk2dacintfendr - The value to use for the bt_dpa_clk2dac_intf_en_dr field.
 * @param[in] btdpaclk2dacintfenreg - The value to use for the bt_dpa_clk2dac_intf_en_reg field.
 * @param[in] btdpacdrrstndr - The value to use for the bt_dpa_cdr_rstn_dr field.
 * @param[in] btdpacdrrstnreg - The value to use for the bt_dpa_cdr_rstn_reg field.
 * @param[in] btdpabt2wfendr - The value to use for the bt_dpa_bt2wf_en_dr field.
 * @param[in] btdpabt2wfenreg - The value to use for the bt_dpa_bt2wf_en_reg field.
 * @param[in] btpudcodr - The value to use for the bt_pu_dco_dr field.
 * @param[in] btpudcoreg - The value to use for the bt_pu_dco_reg field.
 * @param[in] btdcorxloendr - The value to use for the bt_dco_rxlo_en_dr field.
 * @param[in] btdcorxloenreg - The value to use for the bt_dco_rxlo_en_reg field.
 */
__INLINE void bt_rf_reg_00_pack(uint8_t btpulnadr, uint8_t btpulnareg, uint8_t bttrx24gwf2btendr, uint8_t bttrx24gwf2btenreg, uint8_t btpurmxdr, uint8_t btpurmxreg, uint8_t btputiadr, uint8_t btputiareg, uint8_t bttiarstndr, uint8_t bttiarstnreg, uint8_t btpusdmadcdr, uint8_t btpusdmadcreg, uint8_t btsdmadcbypmodedr, uint8_t btsdmadcbypmodereg, uint8_t btsdmadcdigrstndr, uint8_t btsdmadcdigrstnreg, uint8_t btpudpaldodr, uint8_t btpudpaldoreg, uint8_t btpudlydpaldodr, uint8_t btpudlydpaldoreg, uint8_t btpudpadr, uint8_t btpudpareg, uint8_t btdpaclk2dacintfendr, uint8_t btdpaclk2dacintfenreg, uint8_t btdpacdrrstndr, uint8_t btdpacdrrstnreg, uint8_t btdpabt2wfendr, uint8_t btdpabt2wfenreg, uint8_t btpudcodr, uint8_t btpudcoreg, uint8_t btdcorxloendr, uint8_t btdcorxloenreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR,  ((uint32_t)btpulnadr << 31) | ((uint32_t)btpulnareg << 30) | ((uint32_t)bttrx24gwf2btendr << 29) | ((uint32_t)bttrx24gwf2btenreg << 28) | ((uint32_t)btpurmxdr << 27) | ((uint32_t)btpurmxreg << 26) | ((uint32_t)btputiadr << 25) | ((uint32_t)btputiareg << 24) | ((uint32_t)bttiarstndr << 23) | ((uint32_t)bttiarstnreg << 22) | ((uint32_t)btpusdmadcdr << 21) | ((uint32_t)btpusdmadcreg << 20) | ((uint32_t)btsdmadcbypmodedr << 19) | ((uint32_t)btsdmadcbypmodereg << 18) | ((uint32_t)btsdmadcdigrstndr << 17) | ((uint32_t)btsdmadcdigrstnreg << 16) | ((uint32_t)btpudpaldodr << 15) | ((uint32_t)btpudpaldoreg << 14) | ((uint32_t)btpudlydpaldodr << 13) | ((uint32_t)btpudlydpaldoreg << 12) | ((uint32_t)btpudpadr << 11) | ((uint32_t)btpudpareg << 10) | ((uint32_t)btdpaclk2dacintfendr << 9) | ((uint32_t)btdpaclk2dacintfenreg << 8) | ((uint32_t)btdpacdrrstndr << 7) | ((uint32_t)btdpacdrrstnreg << 6) | ((uint32_t)btdpabt2wfendr << 5) | ((uint32_t)btdpabt2wfenreg << 4) | ((uint32_t)btpudcodr << 3) | ((uint32_t)btpudcoreg << 2) | ((uint32_t)btdcorxloendr << 1) | ((uint32_t)btdcorxloenreg << 0));
}

/**
 * @brief Unpacks REG_00's fields from current value of the REG_00 register.
 *
 * Reads the REG_00 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btpulnadr - Will be populated with the current value of this field from the register.
 * @param[out] btpulnareg - Will be populated with the current value of this field from the register.
 * @param[out] bttrx24gwf2btendr - Will be populated with the current value of this field from the register.
 * @param[out] bttrx24gwf2btenreg - Will be populated with the current value of this field from the register.
 * @param[out] btpurmxdr - Will be populated with the current value of this field from the register.
 * @param[out] btpurmxreg - Will be populated with the current value of this field from the register.
 * @param[out] btputiadr - Will be populated with the current value of this field from the register.
 * @param[out] btputiareg - Will be populated with the current value of this field from the register.
 * @param[out] bttiarstndr - Will be populated with the current value of this field from the register.
 * @param[out] bttiarstnreg - Will be populated with the current value of this field from the register.
 * @param[out] btpusdmadcdr - Will be populated with the current value of this field from the register.
 * @param[out] btpusdmadcreg - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcbypmodedr - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcbypmodereg - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcdigrstndr - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcdigrstnreg - Will be populated with the current value of this field from the register.
 * @param[out] btpudpaldodr - Will be populated with the current value of this field from the register.
 * @param[out] btpudpaldoreg - Will be populated with the current value of this field from the register.
 * @param[out] btpudlydpaldodr - Will be populated with the current value of this field from the register.
 * @param[out] btpudlydpaldoreg - Will be populated with the current value of this field from the register.
 * @param[out] btpudpadr - Will be populated with the current value of this field from the register.
 * @param[out] btpudpareg - Will be populated with the current value of this field from the register.
 * @param[out] btdpaclk2dacintfendr - Will be populated with the current value of this field from the register.
 * @param[out] btdpaclk2dacintfenreg - Will be populated with the current value of this field from the register.
 * @param[out] btdpacdrrstndr - Will be populated with the current value of this field from the register.
 * @param[out] btdpacdrrstnreg - Will be populated with the current value of this field from the register.
 * @param[out] btdpabt2wfendr - Will be populated with the current value of this field from the register.
 * @param[out] btdpabt2wfenreg - Will be populated with the current value of this field from the register.
 * @param[out] btpudcodr - Will be populated with the current value of this field from the register.
 * @param[out] btpudcoreg - Will be populated with the current value of this field from the register.
 * @param[out] btdcorxloendr - Will be populated with the current value of this field from the register.
 * @param[out] btdcorxloenreg - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_00_unpack(uint8_t* btpulnadr, uint8_t* btpulnareg, uint8_t* bttrx24gwf2btendr, uint8_t* bttrx24gwf2btenreg, uint8_t* btpurmxdr, uint8_t* btpurmxreg, uint8_t* btputiadr, uint8_t* btputiareg, uint8_t* bttiarstndr, uint8_t* bttiarstnreg, uint8_t* btpusdmadcdr, uint8_t* btpusdmadcreg, uint8_t* btsdmadcbypmodedr, uint8_t* btsdmadcbypmodereg, uint8_t* btsdmadcdigrstndr, uint8_t* btsdmadcdigrstnreg, uint8_t* btpudpaldodr, uint8_t* btpudpaldoreg, uint8_t* btpudlydpaldodr, uint8_t* btpudlydpaldoreg, uint8_t* btpudpadr, uint8_t* btpudpareg, uint8_t* btdpaclk2dacintfendr, uint8_t* btdpaclk2dacintfenreg, uint8_t* btdpacdrrstndr, uint8_t* btdpacdrrstnreg, uint8_t* btdpabt2wfendr, uint8_t* btdpabt2wfenreg, uint8_t* btpudcodr, uint8_t* btpudcoreg, uint8_t* btdcorxloendr, uint8_t* btdcorxloenreg)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);

    *btpulnadr = (localVal & ((uint32_t)0x80000000)) >> 31;
    *btpulnareg = (localVal & ((uint32_t)0x40000000)) >> 30;
    *bttrx24gwf2btendr = (localVal & ((uint32_t)0x20000000)) >> 29;
    *bttrx24gwf2btenreg = (localVal & ((uint32_t)0x10000000)) >> 28;
    *btpurmxdr = (localVal & ((uint32_t)0x08000000)) >> 27;
    *btpurmxreg = (localVal & ((uint32_t)0x04000000)) >> 26;
    *btputiadr = (localVal & ((uint32_t)0x02000000)) >> 25;
    *btputiareg = (localVal & ((uint32_t)0x01000000)) >> 24;
    *bttiarstndr = (localVal & ((uint32_t)0x00800000)) >> 23;
    *bttiarstnreg = (localVal & ((uint32_t)0x00400000)) >> 22;
    *btpusdmadcdr = (localVal & ((uint32_t)0x00200000)) >> 21;
    *btpusdmadcreg = (localVal & ((uint32_t)0x00100000)) >> 20;
    *btsdmadcbypmodedr = (localVal & ((uint32_t)0x00080000)) >> 19;
    *btsdmadcbypmodereg = (localVal & ((uint32_t)0x00040000)) >> 18;
    *btsdmadcdigrstndr = (localVal & ((uint32_t)0x00020000)) >> 17;
    *btsdmadcdigrstnreg = (localVal & ((uint32_t)0x00010000)) >> 16;
    *btpudpaldodr = (localVal & ((uint32_t)0x00008000)) >> 15;
    *btpudpaldoreg = (localVal & ((uint32_t)0x00004000)) >> 14;
    *btpudlydpaldodr = (localVal & ((uint32_t)0x00002000)) >> 13;
    *btpudlydpaldoreg = (localVal & ((uint32_t)0x00001000)) >> 12;
    *btpudpadr = (localVal & ((uint32_t)0x00000800)) >> 11;
    *btpudpareg = (localVal & ((uint32_t)0x00000400)) >> 10;
    *btdpaclk2dacintfendr = (localVal & ((uint32_t)0x00000200)) >> 9;
    *btdpaclk2dacintfenreg = (localVal & ((uint32_t)0x00000100)) >> 8;
    *btdpacdrrstndr = (localVal & ((uint32_t)0x00000080)) >> 7;
    *btdpacdrrstnreg = (localVal & ((uint32_t)0x00000040)) >> 6;
    *btdpabt2wfendr = (localVal & ((uint32_t)0x00000020)) >> 5;
    *btdpabt2wfenreg = (localVal & ((uint32_t)0x00000010)) >> 4;
    *btpudcodr = (localVal & ((uint32_t)0x00000008)) >> 3;
    *btpudcoreg = (localVal & ((uint32_t)0x00000004)) >> 2;
    *btdcorxloendr = (localVal & ((uint32_t)0x00000002)) >> 1;
    *btdcorxloenreg = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the bt_pu_lna_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_lna_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_lna_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_lna_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the bt_pu_lna_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpulnadr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_lna_dr_setf(uint8_t btpulnadr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)btpulnadr << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the bt_pu_lna_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_lna_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_lna_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_lna_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the bt_pu_lna_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpulnareg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_lna_reg_setf(uint8_t btpulnareg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)btpulnareg << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the bt_trx24g_wf2bt_en_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_trx24g_wf2bt_en_dr field's value will be returned.
 *
 * @return The current value of the bt_trx24g_wf2bt_en_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_trx_24g_wf_2bt_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the bt_trx24g_wf2bt_en_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttrx24gwf2btendr - The value to set the field to.
 */
__INLINE void bt_rf_bt_trx_24g_wf_2bt_en_dr_setf(uint8_t bttrx24gwf2btendr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)bttrx24gwf2btendr << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the bt_trx24g_wf2bt_en_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_trx24g_wf2bt_en_reg field's value will be returned.
 *
 * @return The current value of the bt_trx24g_wf2bt_en_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_trx_24g_wf_2bt_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the bt_trx24g_wf2bt_en_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttrx24gwf2btenreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_trx_24g_wf_2bt_en_reg_setf(uint8_t bttrx24gwf2btenreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)bttrx24gwf2btenreg << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the bt_pu_rmx_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_rmx_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_rmx_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_rmx_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the bt_pu_rmx_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpurmxdr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_rmx_dr_setf(uint8_t btpurmxdr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)btpurmxdr << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the bt_pu_rmx_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_rmx_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_rmx_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_rmx_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the bt_pu_rmx_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpurmxreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_rmx_reg_setf(uint8_t btpurmxreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)btpurmxreg << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the bt_pu_tia_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_tia_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_tia_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_tia_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the bt_pu_tia_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btputiadr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_tia_dr_setf(uint8_t btputiadr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)btputiadr << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the bt_pu_tia_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_tia_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_tia_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_tia_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the bt_pu_tia_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btputiareg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_tia_reg_setf(uint8_t btputiareg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)btputiareg << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the bt_tia_rstn_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_tia_rstn_dr field's value will be returned.
 *
 * @return The current value of the bt_tia_rstn_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_tia_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the bt_tia_rstn_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiarstndr - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_rstn_dr_setf(uint8_t bttiarstndr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)bttiarstndr << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the bt_tia_rstn_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_tia_rstn_reg field's value will be returned.
 *
 * @return The current value of the bt_tia_rstn_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_tia_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the bt_tia_rstn_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiarstnreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_rstn_reg_setf(uint8_t bttiarstnreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)bttiarstnreg << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the bt_pu_sdm_adc_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_sdm_adc_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_sdm_adc_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_sdm_adc_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Sets the bt_pu_sdm_adc_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpusdmadcdr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_sdm_adc_dr_setf(uint8_t btpusdmadcdr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00200000)) | (((uint32_t)btpusdmadcdr << 21) & ((uint32_t)0x00200000)));
}

/**
 * @brief Returns the current value of the bt_pu_sdm_adc_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_sdm_adc_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_sdm_adc_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_sdm_adc_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the bt_pu_sdm_adc_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpusdmadcreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_sdm_adc_reg_setf(uint8_t btpusdmadcreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)btpusdmadcreg << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_byp_mode_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_sdm_adc_byp_mode_dr field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_byp_mode_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_byp_mode_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the bt_sdm_adc_byp_mode_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcbypmodedr - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_byp_mode_dr_setf(uint8_t btsdmadcbypmodedr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)btsdmadcbypmodedr << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_byp_mode_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_sdm_adc_byp_mode_reg field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_byp_mode_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_byp_mode_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the bt_sdm_adc_byp_mode_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcbypmodereg - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_byp_mode_reg_setf(uint8_t btsdmadcbypmodereg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)btsdmadcbypmodereg << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_dig_rstn_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_sdm_adc_dig_rstn_dr field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_dig_rstn_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_dig_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the bt_sdm_adc_dig_rstn_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcdigrstndr - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_dig_rstn_dr_setf(uint8_t btsdmadcdigrstndr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)btsdmadcdigrstndr << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_dig_rstn_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_sdm_adc_dig_rstn_reg field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_dig_rstn_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_dig_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the bt_sdm_adc_dig_rstn_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcdigrstnreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_dig_rstn_reg_setf(uint8_t btsdmadcdigrstnreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)btsdmadcdigrstnreg << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the bt_pu_dpa_ldo_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_dpa_ldo_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_dpa_ldo_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dpa_ldo_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the bt_pu_dpa_ldo_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudpaldodr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dpa_ldo_dr_setf(uint8_t btpudpaldodr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)btpudpaldodr << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the bt_pu_dpa_ldo_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_dpa_ldo_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_dpa_ldo_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dpa_ldo_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the bt_pu_dpa_ldo_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudpaldoreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dpa_ldo_reg_setf(uint8_t btpudpaldoreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)btpudpaldoreg << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the bt_pu_dly_dpa_ldo_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_dly_dpa_ldo_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_dly_dpa_ldo_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dly_dpa_ldo_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the bt_pu_dly_dpa_ldo_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudlydpaldodr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dly_dpa_ldo_dr_setf(uint8_t btpudlydpaldodr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)btpudlydpaldodr << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the bt_pu_dly_dpa_ldo_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_dly_dpa_ldo_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_dly_dpa_ldo_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dly_dpa_ldo_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the bt_pu_dly_dpa_ldo_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudlydpaldoreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dly_dpa_ldo_reg_setf(uint8_t btpudlydpaldoreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)btpudlydpaldoreg << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the bt_pu_dpa_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_dpa_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_dpa_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dpa_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the bt_pu_dpa_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudpadr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dpa_dr_setf(uint8_t btpudpadr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)btpudpadr << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the bt_pu_dpa_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_dpa_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_dpa_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dpa_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the bt_pu_dpa_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudpareg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dpa_reg_setf(uint8_t btpudpareg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)btpudpareg << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the bt_dpa_clk2dac_intf_en_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_dpa_clk2dac_intf_en_dr field's value will be returned.
 *
 * @return The current value of the bt_dpa_clk2dac_intf_en_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_clk_2dac_intf_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the bt_dpa_clk2dac_intf_en_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaclk2dacintfendr - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_clk_2dac_intf_en_dr_setf(uint8_t btdpaclk2dacintfendr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)btdpaclk2dacintfendr << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the bt_dpa_clk2dac_intf_en_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_dpa_clk2dac_intf_en_reg field's value will be returned.
 *
 * @return The current value of the bt_dpa_clk2dac_intf_en_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_clk_2dac_intf_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the bt_dpa_clk2dac_intf_en_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaclk2dacintfenreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_clk_2dac_intf_en_reg_setf(uint8_t btdpaclk2dacintfenreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)btdpaclk2dacintfenreg << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the bt_dpa_cdr_rstn_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_dpa_cdr_rstn_dr field's value will be returned.
 *
 * @return The current value of the bt_dpa_cdr_rstn_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_cdr_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the bt_dpa_cdr_rstn_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpacdrrstndr - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_cdr_rstn_dr_setf(uint8_t btdpacdrrstndr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)btdpacdrrstndr << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the bt_dpa_cdr_rstn_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_dpa_cdr_rstn_reg field's value will be returned.
 *
 * @return The current value of the bt_dpa_cdr_rstn_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_cdr_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the bt_dpa_cdr_rstn_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpacdrrstnreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_cdr_rstn_reg_setf(uint8_t btdpacdrrstnreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)btdpacdrrstnreg << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the bt_dpa_bt2wf_en_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_dpa_bt2wf_en_dr field's value will be returned.
 *
 * @return The current value of the bt_dpa_bt2wf_en_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_bt_2wf_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the bt_dpa_bt2wf_en_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpabt2wfendr - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_bt_2wf_en_dr_setf(uint8_t btdpabt2wfendr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)btdpabt2wfendr << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the bt_dpa_bt2wf_en_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_dpa_bt2wf_en_reg field's value will be returned.
 *
 * @return The current value of the bt_dpa_bt2wf_en_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_bt_2wf_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the bt_dpa_bt2wf_en_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpabt2wfenreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_bt_2wf_en_reg_setf(uint8_t btdpabt2wfenreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)btdpabt2wfenreg << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the bt_pu_dco_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_dco_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_dco_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dco_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the bt_pu_dco_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudcodr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dco_dr_setf(uint8_t btpudcodr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)btpudcodr << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the bt_pu_dco_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_pu_dco_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_dco_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dco_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the bt_pu_dco_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudcoreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dco_reg_setf(uint8_t btpudcoreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)btpudcoreg << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the bt_dco_rxlo_en_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_dco_rxlo_en_dr field's value will be returned.
 *
 * @return The current value of the bt_dco_rxlo_en_dr field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_dco_rxlo_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the bt_dco_rxlo_en_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcorxloendr - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_rxlo_en_dr_setf(uint8_t btdcorxloendr)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)btdcorxloendr << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the bt_dco_rxlo_en_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the bt_dco_rxlo_en_reg field's value will be returned.
 *
 * @return The current value of the bt_dco_rxlo_en_reg field in the REG_00 register.
 */
__INLINE uint8_t bt_rf_bt_dco_rxlo_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the bt_dco_rxlo_en_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcorxloenreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_rxlo_en_reg_setf(uint8_t btdcorxloenreg)
{
    REG_PL_WR(BT_RF_REG_00_ADDR, (REG_PL_RD(BT_RF_REG_00_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)btdcorxloenreg << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_04 register definitions
 * <table>
 * <caption id="REG_04_BF">REG_04 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td> bt_dco_txlo_en_dr <td>R <td>R/W <td>0
 * <tr><td>30 <td>bt_dco_txlo_en_reg <td>R <td>R/W <td>1
 * <tr><td>29 <td>     bt_pu_dpll_dr <td>R <td>R/W <td>0
 * <tr><td>28 <td>    bt_pu_dpll_reg <td>R <td>R/W <td>0
 * <tr><td>27 <td>bt_dpll_gro_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>26 <td>bt_dpll_gro_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>25 <td>bt_dpll_sdadc_clk_en_dr <td>R <td>R/W <td>0
 * <tr><td>24 <td>bt_dpll_sdadc_clk_en_reg <td>R <td>R/W <td>1
 * <tr><td>23 <td>  bt_pu_chop_bg_dr <td>R <td>R/W <td>0
 * <tr><td>22 <td> bt_pu_chop_bg_reg <td>R <td>R/W <td>0
 * <tr><td>21 <td>  bt_chop_bg_en_dr <td>R <td>R/W <td>0
 * <tr><td>20 <td> bt_chop_bg_en_reg <td>R <td>R/W <td>0
 * <tr><td>19:18 <td>     bt_lna_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>17:16 <td>     bt_rmx_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>15:14 <td>     bt_tia_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>13:12 <td> bt_sdm_adc_pu_bit <td>R <td>R/W <td>0x2
 * <tr><td>11:10 <td>     bt_dpa_pu_bit <td>R <td>R/W <td>0x0
 * <tr><td>09:08 <td> bt_dpa_reg_pu_bit <td>R <td>R/W <td>0x0
 * <tr><td>07:06 <td>     bt_dco_pu_bit <td>R <td>R/W <td>0x3
 * <tr><td>05:04 <td>    bt_dpll_pu_bit <td>R <td>R/W <td>0x0
 * <tr><td>03 <td>bt_dpa_pll_test_mode <td>R <td>R/W <td>0
 * <tr><td>02:00 <td>       bt_test_bit <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the REG_04 register
#define BT_RF_REG_04_ADDR   0x40622004
/// Offset of the REG_04 register from the base address
#define BT_RF_REG_04_OFFSET 0x00000004
/// Index of the REG_04 register
#define BT_RF_REG_04_INDEX  0x00000001
/// Reset value of the REG_04 register
#define BT_RF_REG_04_RESET  0x410560C0

/**
 * @brief Returns the current value of the REG_04 register.
 * The REG_04 register will be read and its value returned.
 * @return The current value of the REG_04 register.
 */
__INLINE uint32_t bt_rf_reg_04_get(void)
{
    return REG_PL_RD(BT_RF_REG_04_ADDR);
}

/**
 * @brief Sets the REG_04 register to a value.
 * The REG_04 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_04_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, value);
}

// field definitions
/// BT_DCO_TXLO_EN_DR field bit
#define BT_RF_BT_DCO_TXLO_EN_DR_BIT           ((uint32_t)0x80000000)
/// BT_DCO_TXLO_EN_DR field position
#define BT_RF_BT_DCO_TXLO_EN_DR_POS           31
/// BT_DCO_TXLO_EN_REG field bit
#define BT_RF_BT_DCO_TXLO_EN_REG_BIT          ((uint32_t)0x40000000)
/// BT_DCO_TXLO_EN_REG field position
#define BT_RF_BT_DCO_TXLO_EN_REG_POS          30
/// BT_PU_DPLL_DR field bit
#define BT_RF_BT_PU_DPLL_DR_BIT               ((uint32_t)0x20000000)
/// BT_PU_DPLL_DR field position
#define BT_RF_BT_PU_DPLL_DR_POS               29
/// BT_PU_DPLL_REG field bit
#define BT_RF_BT_PU_DPLL_REG_BIT              ((uint32_t)0x10000000)
/// BT_PU_DPLL_REG field position
#define BT_RF_BT_PU_DPLL_REG_POS              28
/// BT_DPLL_GRO_RSTN_DR field bit
#define BT_RF_BT_DPLL_GRO_RSTN_DR_BIT         ((uint32_t)0x08000000)
/// BT_DPLL_GRO_RSTN_DR field position
#define BT_RF_BT_DPLL_GRO_RSTN_DR_POS         27
/// BT_DPLL_GRO_RSTN_REG field bit
#define BT_RF_BT_DPLL_GRO_RSTN_REG_BIT        ((uint32_t)0x04000000)
/// BT_DPLL_GRO_RSTN_REG field position
#define BT_RF_BT_DPLL_GRO_RSTN_REG_POS        26
/// BT_DPLL_SDADC_CLK_EN_DR field bit
#define BT_RF_BT_DPLL_SDADC_CLK_EN_DR_BIT     ((uint32_t)0x02000000)
/// BT_DPLL_SDADC_CLK_EN_DR field position
#define BT_RF_BT_DPLL_SDADC_CLK_EN_DR_POS     25
/// BT_DPLL_SDADC_CLK_EN_REG field bit
#define BT_RF_BT_DPLL_SDADC_CLK_EN_REG_BIT    ((uint32_t)0x01000000)
/// BT_DPLL_SDADC_CLK_EN_REG field position
#define BT_RF_BT_DPLL_SDADC_CLK_EN_REG_POS    24
/// BT_PU_CHOP_BG_DR field bit
#define BT_RF_BT_PU_CHOP_BG_DR_BIT            ((uint32_t)0x00800000)
/// BT_PU_CHOP_BG_DR field position
#define BT_RF_BT_PU_CHOP_BG_DR_POS            23
/// BT_PU_CHOP_BG_REG field bit
#define BT_RF_BT_PU_CHOP_BG_REG_BIT           ((uint32_t)0x00400000)
/// BT_PU_CHOP_BG_REG field position
#define BT_RF_BT_PU_CHOP_BG_REG_POS           22
/// BT_CHOP_BG_EN_DR field bit
#define BT_RF_BT_CHOP_BG_EN_DR_BIT            ((uint32_t)0x00200000)
/// BT_CHOP_BG_EN_DR field position
#define BT_RF_BT_CHOP_BG_EN_DR_POS            21
/// BT_CHOP_BG_EN_REG field bit
#define BT_RF_BT_CHOP_BG_EN_REG_BIT           ((uint32_t)0x00100000)
/// BT_CHOP_BG_EN_REG field position
#define BT_RF_BT_CHOP_BG_EN_REG_POS           20
/// BT_LNA_PU_BIT field mask
#define BT_RF_BT_LNA_PU_BIT_MASK              ((uint32_t)0x000C0000)
/// BT_LNA_PU_BIT field LSB position
#define BT_RF_BT_LNA_PU_BIT_LSB               18
/// BT_LNA_PU_BIT field width
#define BT_RF_BT_LNA_PU_BIT_WIDTH             ((uint32_t)0x00000002)
/// BT_RMX_PU_BIT field mask
#define BT_RF_BT_RMX_PU_BIT_MASK              ((uint32_t)0x00030000)
/// BT_RMX_PU_BIT field LSB position
#define BT_RF_BT_RMX_PU_BIT_LSB               16
/// BT_RMX_PU_BIT field width
#define BT_RF_BT_RMX_PU_BIT_WIDTH             ((uint32_t)0x00000002)
/// BT_TIA_PU_BIT field mask
#define BT_RF_BT_TIA_PU_BIT_MASK              ((uint32_t)0x0000C000)
/// BT_TIA_PU_BIT field LSB position
#define BT_RF_BT_TIA_PU_BIT_LSB               14
/// BT_TIA_PU_BIT field width
#define BT_RF_BT_TIA_PU_BIT_WIDTH             ((uint32_t)0x00000002)
/// BT_SDM_ADC_PU_BIT field mask
#define BT_RF_BT_SDM_ADC_PU_BIT_MASK          ((uint32_t)0x00003000)
/// BT_SDM_ADC_PU_BIT field LSB position
#define BT_RF_BT_SDM_ADC_PU_BIT_LSB           12
/// BT_SDM_ADC_PU_BIT field width
#define BT_RF_BT_SDM_ADC_PU_BIT_WIDTH         ((uint32_t)0x00000002)
/// BT_DPA_PU_BIT field mask
#define BT_RF_BT_DPA_PU_BIT_MASK              ((uint32_t)0x00000C00)
/// BT_DPA_PU_BIT field LSB position
#define BT_RF_BT_DPA_PU_BIT_LSB               10
/// BT_DPA_PU_BIT field width
#define BT_RF_BT_DPA_PU_BIT_WIDTH             ((uint32_t)0x00000002)
/// BT_DPA_REG_PU_BIT field mask
#define BT_RF_BT_DPA_REG_PU_BIT_MASK          ((uint32_t)0x00000300)
/// BT_DPA_REG_PU_BIT field LSB position
#define BT_RF_BT_DPA_REG_PU_BIT_LSB           8
/// BT_DPA_REG_PU_BIT field width
#define BT_RF_BT_DPA_REG_PU_BIT_WIDTH         ((uint32_t)0x00000002)
/// BT_DCO_PU_BIT field mask
#define BT_RF_BT_DCO_PU_BIT_MASK              ((uint32_t)0x000000C0)
/// BT_DCO_PU_BIT field LSB position
#define BT_RF_BT_DCO_PU_BIT_LSB               6
/// BT_DCO_PU_BIT field width
#define BT_RF_BT_DCO_PU_BIT_WIDTH             ((uint32_t)0x00000002)
/// BT_DPLL_PU_BIT field mask
#define BT_RF_BT_DPLL_PU_BIT_MASK             ((uint32_t)0x00000030)
/// BT_DPLL_PU_BIT field LSB position
#define BT_RF_BT_DPLL_PU_BIT_LSB              4
/// BT_DPLL_PU_BIT field width
#define BT_RF_BT_DPLL_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// BT_DPA_PLL_TEST_MODE field bit
#define BT_RF_BT_DPA_PLL_TEST_MODE_BIT        ((uint32_t)0x00000008)
/// BT_DPA_PLL_TEST_MODE field position
#define BT_RF_BT_DPA_PLL_TEST_MODE_POS        3
/// BT_TEST_BIT field mask
#define BT_RF_BT_TEST_BIT_MASK                ((uint32_t)0x00000007)
/// BT_TEST_BIT field LSB position
#define BT_RF_BT_TEST_BIT_LSB                 0
/// BT_TEST_BIT field width
#define BT_RF_BT_TEST_BIT_WIDTH               ((uint32_t)0x00000003)

/// BT_DCO_TXLO_EN_DR field reset value
#define BT_RF_BT_DCO_TXLO_EN_DR_RST           0x0
/// BT_DCO_TXLO_EN_REG field reset value
#define BT_RF_BT_DCO_TXLO_EN_REG_RST          0x1
/// BT_PU_DPLL_DR field reset value
#define BT_RF_BT_PU_DPLL_DR_RST               0x0
/// BT_PU_DPLL_REG field reset value
#define BT_RF_BT_PU_DPLL_REG_RST              0x0
/// BT_DPLL_GRO_RSTN_DR field reset value
#define BT_RF_BT_DPLL_GRO_RSTN_DR_RST         0x0
/// BT_DPLL_GRO_RSTN_REG field reset value
#define BT_RF_BT_DPLL_GRO_RSTN_REG_RST        0x0
/// BT_DPLL_SDADC_CLK_EN_DR field reset value
#define BT_RF_BT_DPLL_SDADC_CLK_EN_DR_RST     0x0
/// BT_DPLL_SDADC_CLK_EN_REG field reset value
#define BT_RF_BT_DPLL_SDADC_CLK_EN_REG_RST    0x1
/// BT_PU_CHOP_BG_DR field reset value
#define BT_RF_BT_PU_CHOP_BG_DR_RST            0x0
/// BT_PU_CHOP_BG_REG field reset value
#define BT_RF_BT_PU_CHOP_BG_REG_RST           0x0
/// BT_CHOP_BG_EN_DR field reset value
#define BT_RF_BT_CHOP_BG_EN_DR_RST            0x0
/// BT_CHOP_BG_EN_REG field reset value
#define BT_RF_BT_CHOP_BG_EN_REG_RST           0x0
/// BT_LNA_PU_BIT field reset value
#define BT_RF_BT_LNA_PU_BIT_RST               0x1
/// BT_RMX_PU_BIT field reset value
#define BT_RF_BT_RMX_PU_BIT_RST               0x1
/// BT_TIA_PU_BIT field reset value
#define BT_RF_BT_TIA_PU_BIT_RST               0x1
/// BT_SDM_ADC_PU_BIT field reset value
#define BT_RF_BT_SDM_ADC_PU_BIT_RST           0x2
/// BT_DPA_PU_BIT field reset value
#define BT_RF_BT_DPA_PU_BIT_RST               0x0
/// BT_DPA_REG_PU_BIT field reset value
#define BT_RF_BT_DPA_REG_PU_BIT_RST           0x0
/// BT_DCO_PU_BIT field reset value
#define BT_RF_BT_DCO_PU_BIT_RST               0x3
/// BT_DPLL_PU_BIT field reset value
#define BT_RF_BT_DPLL_PU_BIT_RST              0x0
/// BT_DPA_PLL_TEST_MODE field reset value
#define BT_RF_BT_DPA_PLL_TEST_MODE_RST        0x0
/// BT_TEST_BIT field reset value
#define BT_RF_BT_TEST_BIT_RST                 0x0

/**
 * @brief Constructs a value for the REG_04 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btdcotxloendr - The value to use for the bt_dco_txlo_en_dr field.
 * @param[in] btdcotxloenreg - The value to use for the bt_dco_txlo_en_reg field.
 * @param[in] btpudplldr - The value to use for the bt_pu_dpll_dr field.
 * @param[in] btpudpllreg - The value to use for the bt_pu_dpll_reg field.
 * @param[in] btdpllgrorstndr - The value to use for the bt_dpll_gro_rstn_dr field.
 * @param[in] btdpllgrorstnreg - The value to use for the bt_dpll_gro_rstn_reg field.
 * @param[in] btdpllsdadcclkendr - The value to use for the bt_dpll_sdadc_clk_en_dr field.
 * @param[in] btdpllsdadcclkenreg - The value to use for the bt_dpll_sdadc_clk_en_reg field.
 * @param[in] btpuchopbgdr - The value to use for the bt_pu_chop_bg_dr field.
 * @param[in] btpuchopbgreg - The value to use for the bt_pu_chop_bg_reg field.
 * @param[in] btchopbgendr - The value to use for the bt_chop_bg_en_dr field.
 * @param[in] btchopbgenreg - The value to use for the bt_chop_bg_en_reg field.
 * @param[in] btlnapubit - The value to use for the bt_lna_pu_bit field.
 * @param[in] btrmxpubit - The value to use for the bt_rmx_pu_bit field.
 * @param[in] bttiapubit - The value to use for the bt_tia_pu_bit field.
 * @param[in] btsdmadcpubit - The value to use for the bt_sdm_adc_pu_bit field.
 * @param[in] btdpapubit - The value to use for the bt_dpa_pu_bit field.
 * @param[in] btdparegpubit - The value to use for the bt_dpa_reg_pu_bit field.
 * @param[in] btdcopubit - The value to use for the bt_dco_pu_bit field.
 * @param[in] btdpllpubit - The value to use for the bt_dpll_pu_bit field.
 * @param[in] btdpaplltestmode - The value to use for the bt_dpa_pll_test_mode field.
 * @param[in] bttestbit - The value to use for the bt_test_bit field.
 */
__INLINE void bt_rf_reg_04_pack(uint8_t btdcotxloendr, uint8_t btdcotxloenreg, uint8_t btpudplldr, uint8_t btpudpllreg, uint8_t btdpllgrorstndr, uint8_t btdpllgrorstnreg, uint8_t btdpllsdadcclkendr, uint8_t btdpllsdadcclkenreg, uint8_t btpuchopbgdr, uint8_t btpuchopbgreg, uint8_t btchopbgendr, uint8_t btchopbgenreg, uint8_t btlnapubit, uint8_t btrmxpubit, uint8_t bttiapubit, uint8_t btsdmadcpubit, uint8_t btdpapubit, uint8_t btdparegpubit, uint8_t btdcopubit, uint8_t btdpllpubit, uint8_t btdpaplltestmode, uint8_t bttestbit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR,  ((uint32_t)btdcotxloendr << 31) | ((uint32_t)btdcotxloenreg << 30) | ((uint32_t)btpudplldr << 29) | ((uint32_t)btpudpllreg << 28) | ((uint32_t)btdpllgrorstndr << 27) | ((uint32_t)btdpllgrorstnreg << 26) | ((uint32_t)btdpllsdadcclkendr << 25) | ((uint32_t)btdpllsdadcclkenreg << 24) | ((uint32_t)btpuchopbgdr << 23) | ((uint32_t)btpuchopbgreg << 22) | ((uint32_t)btchopbgendr << 21) | ((uint32_t)btchopbgenreg << 20) | ((uint32_t)btlnapubit << 18) | ((uint32_t)btrmxpubit << 16) | ((uint32_t)bttiapubit << 14) | ((uint32_t)btsdmadcpubit << 12) | ((uint32_t)btdpapubit << 10) | ((uint32_t)btdparegpubit << 8) | ((uint32_t)btdcopubit << 6) | ((uint32_t)btdpllpubit << 4) | ((uint32_t)btdpaplltestmode << 3) | ((uint32_t)bttestbit << 0));
}

/**
 * @brief Unpacks REG_04's fields from current value of the REG_04 register.
 *
 * Reads the REG_04 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btdcotxloendr - Will be populated with the current value of this field from the register.
 * @param[out] btdcotxloenreg - Will be populated with the current value of this field from the register.
 * @param[out] btpudplldr - Will be populated with the current value of this field from the register.
 * @param[out] btpudpllreg - Will be populated with the current value of this field from the register.
 * @param[out] btdpllgrorstndr - Will be populated with the current value of this field from the register.
 * @param[out] btdpllgrorstnreg - Will be populated with the current value of this field from the register.
 * @param[out] btdpllsdadcclkendr - Will be populated with the current value of this field from the register.
 * @param[out] btdpllsdadcclkenreg - Will be populated with the current value of this field from the register.
 * @param[out] btpuchopbgdr - Will be populated with the current value of this field from the register.
 * @param[out] btpuchopbgreg - Will be populated with the current value of this field from the register.
 * @param[out] btchopbgendr - Will be populated with the current value of this field from the register.
 * @param[out] btchopbgenreg - Will be populated with the current value of this field from the register.
 * @param[out] btlnapubit - Will be populated with the current value of this field from the register.
 * @param[out] btrmxpubit - Will be populated with the current value of this field from the register.
 * @param[out] bttiapubit - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcpubit - Will be populated with the current value of this field from the register.
 * @param[out] btdpapubit - Will be populated with the current value of this field from the register.
 * @param[out] btdparegpubit - Will be populated with the current value of this field from the register.
 * @param[out] btdcopubit - Will be populated with the current value of this field from the register.
 * @param[out] btdpllpubit - Will be populated with the current value of this field from the register.
 * @param[out] btdpaplltestmode - Will be populated with the current value of this field from the register.
 * @param[out] bttestbit - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_04_unpack(uint8_t* btdcotxloendr, uint8_t* btdcotxloenreg, uint8_t* btpudplldr, uint8_t* btpudpllreg, uint8_t* btdpllgrorstndr, uint8_t* btdpllgrorstnreg, uint8_t* btdpllsdadcclkendr, uint8_t* btdpllsdadcclkenreg, uint8_t* btpuchopbgdr, uint8_t* btpuchopbgreg, uint8_t* btchopbgendr, uint8_t* btchopbgenreg, uint8_t* btlnapubit, uint8_t* btrmxpubit, uint8_t* bttiapubit, uint8_t* btsdmadcpubit, uint8_t* btdpapubit, uint8_t* btdparegpubit, uint8_t* btdcopubit, uint8_t* btdpllpubit, uint8_t* btdpaplltestmode, uint8_t* bttestbit)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);

    *btdcotxloendr = (localVal & ((uint32_t)0x80000000)) >> 31;
    *btdcotxloenreg = (localVal & ((uint32_t)0x40000000)) >> 30;
    *btpudplldr = (localVal & ((uint32_t)0x20000000)) >> 29;
    *btpudpllreg = (localVal & ((uint32_t)0x10000000)) >> 28;
    *btdpllgrorstndr = (localVal & ((uint32_t)0x08000000)) >> 27;
    *btdpllgrorstnreg = (localVal & ((uint32_t)0x04000000)) >> 26;
    *btdpllsdadcclkendr = (localVal & ((uint32_t)0x02000000)) >> 25;
    *btdpllsdadcclkenreg = (localVal & ((uint32_t)0x01000000)) >> 24;
    *btpuchopbgdr = (localVal & ((uint32_t)0x00800000)) >> 23;
    *btpuchopbgreg = (localVal & ((uint32_t)0x00400000)) >> 22;
    *btchopbgendr = (localVal & ((uint32_t)0x00200000)) >> 21;
    *btchopbgenreg = (localVal & ((uint32_t)0x00100000)) >> 20;
    *btlnapubit = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *btrmxpubit = (localVal & ((uint32_t)0x00030000)) >> 16;
    *bttiapubit = (localVal & ((uint32_t)0x0000C000)) >> 14;
    *btsdmadcpubit = (localVal & ((uint32_t)0x00003000)) >> 12;
    *btdpapubit = (localVal & ((uint32_t)0x00000C00)) >> 10;
    *btdparegpubit = (localVal & ((uint32_t)0x00000300)) >> 8;
    *btdcopubit = (localVal & ((uint32_t)0x000000C0)) >> 6;
    *btdpllpubit = (localVal & ((uint32_t)0x00000030)) >> 4;
    *btdpaplltestmode = (localVal & ((uint32_t)0x00000008)) >> 3;
    *bttestbit = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the bt_dco_txlo_en_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dco_txlo_en_dr field's value will be returned.
 *
 * @return The current value of the bt_dco_txlo_en_dr field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dco_txlo_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the bt_dco_txlo_en_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcotxloendr - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_txlo_en_dr_setf(uint8_t btdcotxloendr)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)btdcotxloendr << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the bt_dco_txlo_en_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dco_txlo_en_reg field's value will be returned.
 *
 * @return The current value of the bt_dco_txlo_en_reg field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dco_txlo_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the bt_dco_txlo_en_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcotxloenreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_txlo_en_reg_setf(uint8_t btdcotxloenreg)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)btdcotxloenreg << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the bt_pu_dpll_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_pu_dpll_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_dpll_dr field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dpll_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the bt_pu_dpll_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudplldr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dpll_dr_setf(uint8_t btpudplldr)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)btpudplldr << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the bt_pu_dpll_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_pu_dpll_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_dpll_reg field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dpll_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the bt_pu_dpll_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudpllreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dpll_reg_setf(uint8_t btpudpllreg)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)btpudpllreg << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the bt_dpll_gro_rstn_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dpll_gro_rstn_dr field's value will be returned.
 *
 * @return The current value of the bt_dpll_gro_rstn_dr field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_gro_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the bt_dpll_gro_rstn_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllgrorstndr - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_gro_rstn_dr_setf(uint8_t btdpllgrorstndr)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)btdpllgrorstndr << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the bt_dpll_gro_rstn_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dpll_gro_rstn_reg field's value will be returned.
 *
 * @return The current value of the bt_dpll_gro_rstn_reg field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_gro_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the bt_dpll_gro_rstn_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllgrorstnreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_gro_rstn_reg_setf(uint8_t btdpllgrorstnreg)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)btdpllgrorstnreg << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the bt_dpll_sdadc_clk_en_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dpll_sdadc_clk_en_dr field's value will be returned.
 *
 * @return The current value of the bt_dpll_sdadc_clk_en_dr field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_sdadc_clk_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the bt_dpll_sdadc_clk_en_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllsdadcclkendr - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_sdadc_clk_en_dr_setf(uint8_t btdpllsdadcclkendr)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)btdpllsdadcclkendr << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the bt_dpll_sdadc_clk_en_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dpll_sdadc_clk_en_reg field's value will be returned.
 *
 * @return The current value of the bt_dpll_sdadc_clk_en_reg field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_sdadc_clk_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the bt_dpll_sdadc_clk_en_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllsdadcclkenreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_sdadc_clk_en_reg_setf(uint8_t btdpllsdadcclkenreg)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)btdpllsdadcclkenreg << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the bt_pu_chop_bg_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_pu_chop_bg_dr field's value will be returned.
 *
 * @return The current value of the bt_pu_chop_bg_dr field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_pu_chop_bg_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the bt_pu_chop_bg_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpuchopbgdr - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_chop_bg_dr_setf(uint8_t btpuchopbgdr)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)btpuchopbgdr << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the bt_pu_chop_bg_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_pu_chop_bg_reg field's value will be returned.
 *
 * @return The current value of the bt_pu_chop_bg_reg field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_pu_chop_bg_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the bt_pu_chop_bg_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpuchopbgreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_chop_bg_reg_setf(uint8_t btpuchopbgreg)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)btpuchopbgreg << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the bt_chop_bg_en_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_chop_bg_en_dr field's value will be returned.
 *
 * @return The current value of the bt_chop_bg_en_dr field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_chop_bg_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Sets the bt_chop_bg_en_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btchopbgendr - The value to set the field to.
 */
__INLINE void bt_rf_bt_chop_bg_en_dr_setf(uint8_t btchopbgendr)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00200000)) | (((uint32_t)btchopbgendr << 21) & ((uint32_t)0x00200000)));
}

/**
 * @brief Returns the current value of the bt_chop_bg_en_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_chop_bg_en_reg field's value will be returned.
 *
 * @return The current value of the bt_chop_bg_en_reg field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_chop_bg_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the bt_chop_bg_en_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btchopbgenreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_chop_bg_en_reg_setf(uint8_t btchopbgenreg)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)btchopbgenreg << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the bt_lna_pu_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_lna_pu_bit field's value will be returned.
 *
 * @return The current value of the bt_lna_pu_bit field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_lna_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the bt_lna_pu_bit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btlnapubit - The value to set the field to.
 */
__INLINE void bt_rf_bt_lna_pu_bit_setf(uint8_t btlnapubit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)btlnapubit << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the bt_rmx_pu_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_rmx_pu_bit field's value will be returned.
 *
 * @return The current value of the bt_rmx_pu_bit field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_rmx_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

/**
 * @brief Sets the bt_rmx_pu_bit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btrmxpubit - The value to set the field to.
 */
__INLINE void bt_rf_bt_rmx_pu_bit_setf(uint8_t btrmxpubit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00030000)) | (((uint32_t)btrmxpubit << 16) & ((uint32_t)0x00030000)));
}

/**
 * @brief Returns the current value of the bt_tia_pu_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_tia_pu_bit field's value will be returned.
 *
 * @return The current value of the bt_tia_pu_bit field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_tia_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x0000C000)) >> 14);
}

/**
 * @brief Sets the bt_tia_pu_bit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiapubit - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_pu_bit_setf(uint8_t bttiapubit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x0000C000)) | (((uint32_t)bttiapubit << 14) & ((uint32_t)0x0000C000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_pu_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_sdm_adc_pu_bit field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_pu_bit field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

/**
 * @brief Sets the bt_sdm_adc_pu_bit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcpubit - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_pu_bit_setf(uint8_t btsdmadcpubit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00003000)) | (((uint32_t)btsdmadcpubit << 12) & ((uint32_t)0x00003000)));
}

/**
 * @brief Returns the current value of the bt_dpa_pu_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dpa_pu_bit field's value will be returned.
 *
 * @return The current value of the bt_dpa_pu_bit field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000C00)) >> 10);
}

/**
 * @brief Sets the bt_dpa_pu_bit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpapubit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_pu_bit_setf(uint8_t btdpapubit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00000C00)) | (((uint32_t)btdpapubit << 10) & ((uint32_t)0x00000C00)));
}

/**
 * @brief Returns the current value of the bt_dpa_reg_pu_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dpa_reg_pu_bit field's value will be returned.
 *
 * @return The current value of the bt_dpa_reg_pu_bit field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_reg_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the bt_dpa_reg_pu_bit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdparegpubit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_reg_pu_bit_setf(uint8_t btdparegpubit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)btdparegpubit << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the bt_dco_pu_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dco_pu_bit field's value will be returned.
 *
 * @return The current value of the bt_dco_pu_bit field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dco_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x000000C0)) >> 6);
}

/**
 * @brief Sets the bt_dco_pu_bit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcopubit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_pu_bit_setf(uint8_t btdcopubit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x000000C0)) | (((uint32_t)btdcopubit << 6) & ((uint32_t)0x000000C0)));
}

/**
 * @brief Returns the current value of the bt_dpll_pu_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dpll_pu_bit field's value will be returned.
 *
 * @return The current value of the bt_dpll_pu_bit field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

/**
 * @brief Sets the bt_dpll_pu_bit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllpubit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_pu_bit_setf(uint8_t btdpllpubit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00000030)) | (((uint32_t)btdpllpubit << 4) & ((uint32_t)0x00000030)));
}

/**
 * @brief Returns the current value of the bt_dpa_pll_test_mode field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_dpa_pll_test_mode field's value will be returned.
 *
 * @return The current value of the bt_dpa_pll_test_mode field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_pll_test_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the bt_dpa_pll_test_mode field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaplltestmode - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_pll_test_mode_setf(uint8_t btdpaplltestmode)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)btdpaplltestmode << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the bt_test_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the bt_test_bit field's value will be returned.
 *
 * @return The current value of the bt_test_bit field in the REG_04 register.
 */
__INLINE uint8_t bt_rf_bt_test_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/**
 * @brief Sets the bt_test_bit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttestbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_test_bit_setf(uint8_t bttestbit)
{
    REG_PL_WR(BT_RF_REG_04_ADDR, (REG_PL_RD(BT_RF_REG_04_ADDR) & ~((uint32_t)0x00000007)) | (((uint32_t)bttestbit << 0) & ((uint32_t)0x00000007)));
}

/// @}

/**
 * @name REG_08 register definitions
 * <table>
 * <caption id="REG_08_BF">REG_08 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>bt_test_enable_lna <td>R <td>R/W <td>0
 * <tr><td>30 <td>bt_test_enable_rmx <td>R <td>R/W <td>0
 * <tr><td>29 <td>bt_test_enable_tia <td>R <td>R/W <td>0
 * <tr><td>28 <td>bt_test_enable_sdm_adc <td>R <td>R/W <td>0
 * <tr><td>27 <td>bt_test_ac_enable_dpll <td>R <td>R/W <td>0
 * <tr><td>26 <td>bt_test_enable_dpa <td>R <td>R/W <td>0
 * <tr><td>25 <td>bt_test_enable_chop_bg <td>R <td>R/W <td>0
 * <tr><td>24 <td>bt_test_enable_dpa_ldo <td>R <td>R/W <td>0
 * <tr><td>23:22 <td> bt_pu_chop_bg_td1 <td>R <td>R/W <td>0x3
 * <tr><td>21:20 <td> bt_chop_bg_en_td1 <td>R <td>R/W <td>0x1
 * <tr><td>19:18 <td> bt_pu_dpa_ldo_td3 <td>R <td>R/W <td>0x1
 * <tr><td>17:15 <td>bt_pu_dly_dpa_ldo_td2 <td>R <td>R/W <td>0x3
 * <tr><td>14:13 <td>     bt_pu_dco_td1 <td>R <td>R/W <td>0x1
 * <tr><td>12:11 <td>bt_dco_rxlo_en_td1 <td>R <td>R/W <td>0x1
 * <tr><td>10:09 <td>bt_dco_txlo_en_td1 <td>R <td>R/W <td>0x1
 * <tr><td>08:07 <td>bt_dpa_clk2dac_intf_en_td1 <td>R <td>R/W <td>0x1
 * <tr><td>06:05 <td>bt_dpll_gro_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>04:02 <td>bt_dpll_gro_rstn_td2 <td>R <td>R/W <td>0x3
 * <tr><td>01:00 <td>     bt_pu_rmx_td1 <td>R <td>R/W <td>0x1
 * </table>
 *
 * @{
 */

/// Address of the REG_08 register
#define BT_RF_REG_08_ADDR   0x40622008
/// Offset of the REG_08 register from the base address
#define BT_RF_REG_08_OFFSET 0x00000008
/// Index of the REG_08 register
#define BT_RF_REG_08_INDEX  0x00000002
/// Reset value of the REG_08 register
#define BT_RF_REG_08_RESET  0x00D5AAAD

/**
 * @brief Returns the current value of the REG_08 register.
 * The REG_08 register will be read and its value returned.
 * @return The current value of the REG_08 register.
 */
__INLINE uint32_t bt_rf_reg_08_get(void)
{
    return REG_PL_RD(BT_RF_REG_08_ADDR);
}

/**
 * @brief Sets the REG_08 register to a value.
 * The REG_08 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_08_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, value);
}

// field definitions
/// BT_TEST_ENABLE_LNA field bit
#define BT_RF_BT_TEST_ENABLE_LNA_BIT              ((uint32_t)0x80000000)
/// BT_TEST_ENABLE_LNA field position
#define BT_RF_BT_TEST_ENABLE_LNA_POS              31
/// BT_TEST_ENABLE_RMX field bit
#define BT_RF_BT_TEST_ENABLE_RMX_BIT              ((uint32_t)0x40000000)
/// BT_TEST_ENABLE_RMX field position
#define BT_RF_BT_TEST_ENABLE_RMX_POS              30
/// BT_TEST_ENABLE_TIA field bit
#define BT_RF_BT_TEST_ENABLE_TIA_BIT              ((uint32_t)0x20000000)
/// BT_TEST_ENABLE_TIA field position
#define BT_RF_BT_TEST_ENABLE_TIA_POS              29
/// BT_TEST_ENABLE_SDM_ADC field bit
#define BT_RF_BT_TEST_ENABLE_SDM_ADC_BIT          ((uint32_t)0x10000000)
/// BT_TEST_ENABLE_SDM_ADC field position
#define BT_RF_BT_TEST_ENABLE_SDM_ADC_POS          28
/// BT_TEST_AC_ENABLE_DPLL field bit
#define BT_RF_BT_TEST_AC_ENABLE_DPLL_BIT          ((uint32_t)0x08000000)
/// BT_TEST_AC_ENABLE_DPLL field position
#define BT_RF_BT_TEST_AC_ENABLE_DPLL_POS          27
/// BT_TEST_ENABLE_DPA field bit
#define BT_RF_BT_TEST_ENABLE_DPA_BIT              ((uint32_t)0x04000000)
/// BT_TEST_ENABLE_DPA field position
#define BT_RF_BT_TEST_ENABLE_DPA_POS              26
/// BT_TEST_ENABLE_CHOP_BG field bit
#define BT_RF_BT_TEST_ENABLE_CHOP_BG_BIT          ((uint32_t)0x02000000)
/// BT_TEST_ENABLE_CHOP_BG field position
#define BT_RF_BT_TEST_ENABLE_CHOP_BG_POS          25
/// BT_TEST_ENABLE_DPA_LDO field bit
#define BT_RF_BT_TEST_ENABLE_DPA_LDO_BIT          ((uint32_t)0x01000000)
/// BT_TEST_ENABLE_DPA_LDO field position
#define BT_RF_BT_TEST_ENABLE_DPA_LDO_POS          24
/// BT_PU_CHOP_BG_TD_1 field mask
#define BT_RF_BT_PU_CHOP_BG_TD_1_MASK             ((uint32_t)0x00C00000)
/// BT_PU_CHOP_BG_TD_1 field LSB position
#define BT_RF_BT_PU_CHOP_BG_TD_1_LSB              22
/// BT_PU_CHOP_BG_TD_1 field width
#define BT_RF_BT_PU_CHOP_BG_TD_1_WIDTH            ((uint32_t)0x00000002)
/// BT_CHOP_BG_EN_TD_1 field mask
#define BT_RF_BT_CHOP_BG_EN_TD_1_MASK             ((uint32_t)0x00300000)
/// BT_CHOP_BG_EN_TD_1 field LSB position
#define BT_RF_BT_CHOP_BG_EN_TD_1_LSB              20
/// BT_CHOP_BG_EN_TD_1 field width
#define BT_RF_BT_CHOP_BG_EN_TD_1_WIDTH            ((uint32_t)0x00000002)
/// BT_PU_DPA_LDO_TD_3 field mask
#define BT_RF_BT_PU_DPA_LDO_TD_3_MASK             ((uint32_t)0x000C0000)
/// BT_PU_DPA_LDO_TD_3 field LSB position
#define BT_RF_BT_PU_DPA_LDO_TD_3_LSB              18
/// BT_PU_DPA_LDO_TD_3 field width
#define BT_RF_BT_PU_DPA_LDO_TD_3_WIDTH            ((uint32_t)0x00000002)
/// BT_PU_DLY_DPA_LDO_TD_2 field mask
#define BT_RF_BT_PU_DLY_DPA_LDO_TD_2_MASK         ((uint32_t)0x00038000)
/// BT_PU_DLY_DPA_LDO_TD_2 field LSB position
#define BT_RF_BT_PU_DLY_DPA_LDO_TD_2_LSB          15
/// BT_PU_DLY_DPA_LDO_TD_2 field width
#define BT_RF_BT_PU_DLY_DPA_LDO_TD_2_WIDTH        ((uint32_t)0x00000003)
/// BT_PU_DCO_TD_1 field mask
#define BT_RF_BT_PU_DCO_TD_1_MASK                 ((uint32_t)0x00006000)
/// BT_PU_DCO_TD_1 field LSB position
#define BT_RF_BT_PU_DCO_TD_1_LSB                  13
/// BT_PU_DCO_TD_1 field width
#define BT_RF_BT_PU_DCO_TD_1_WIDTH                ((uint32_t)0x00000002)
/// BT_DCO_RXLO_EN_TD_1 field mask
#define BT_RF_BT_DCO_RXLO_EN_TD_1_MASK            ((uint32_t)0x00001800)
/// BT_DCO_RXLO_EN_TD_1 field LSB position
#define BT_RF_BT_DCO_RXLO_EN_TD_1_LSB             11
/// BT_DCO_RXLO_EN_TD_1 field width
#define BT_RF_BT_DCO_RXLO_EN_TD_1_WIDTH           ((uint32_t)0x00000002)
/// BT_DCO_TXLO_EN_TD_1 field mask
#define BT_RF_BT_DCO_TXLO_EN_TD_1_MASK            ((uint32_t)0x00000600)
/// BT_DCO_TXLO_EN_TD_1 field LSB position
#define BT_RF_BT_DCO_TXLO_EN_TD_1_LSB             9
/// BT_DCO_TXLO_EN_TD_1 field width
#define BT_RF_BT_DCO_TXLO_EN_TD_1_WIDTH           ((uint32_t)0x00000002)
/// BT_DPA_CLK_2DAC_INTF_EN_TD_1 field mask
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_TD_1_MASK   ((uint32_t)0x00000180)
/// BT_DPA_CLK_2DAC_INTF_EN_TD_1 field LSB position
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_TD_1_LSB    7
/// BT_DPA_CLK_2DAC_INTF_EN_TD_1 field width
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_TD_1_WIDTH  ((uint32_t)0x00000002)
/// BT_DPLL_GRO_RSTN_TD_1 field mask
#define BT_RF_BT_DPLL_GRO_RSTN_TD_1_MASK          ((uint32_t)0x00000060)
/// BT_DPLL_GRO_RSTN_TD_1 field LSB position
#define BT_RF_BT_DPLL_GRO_RSTN_TD_1_LSB           5
/// BT_DPLL_GRO_RSTN_TD_1 field width
#define BT_RF_BT_DPLL_GRO_RSTN_TD_1_WIDTH         ((uint32_t)0x00000002)
/// BT_DPLL_GRO_RSTN_TD_2 field mask
#define BT_RF_BT_DPLL_GRO_RSTN_TD_2_MASK          ((uint32_t)0x0000001C)
/// BT_DPLL_GRO_RSTN_TD_2 field LSB position
#define BT_RF_BT_DPLL_GRO_RSTN_TD_2_LSB           2
/// BT_DPLL_GRO_RSTN_TD_2 field width
#define BT_RF_BT_DPLL_GRO_RSTN_TD_2_WIDTH         ((uint32_t)0x00000003)
/// BT_PU_RMX_TD_1 field mask
#define BT_RF_BT_PU_RMX_TD_1_MASK                 ((uint32_t)0x00000003)
/// BT_PU_RMX_TD_1 field LSB position
#define BT_RF_BT_PU_RMX_TD_1_LSB                  0
/// BT_PU_RMX_TD_1 field width
#define BT_RF_BT_PU_RMX_TD_1_WIDTH                ((uint32_t)0x00000002)

/// BT_TEST_ENABLE_LNA field reset value
#define BT_RF_BT_TEST_ENABLE_LNA_RST              0x0
/// BT_TEST_ENABLE_RMX field reset value
#define BT_RF_BT_TEST_ENABLE_RMX_RST              0x0
/// BT_TEST_ENABLE_TIA field reset value
#define BT_RF_BT_TEST_ENABLE_TIA_RST              0x0
/// BT_TEST_ENABLE_SDM_ADC field reset value
#define BT_RF_BT_TEST_ENABLE_SDM_ADC_RST          0x0
/// BT_TEST_AC_ENABLE_DPLL field reset value
#define BT_RF_BT_TEST_AC_ENABLE_DPLL_RST          0x0
/// BT_TEST_ENABLE_DPA field reset value
#define BT_RF_BT_TEST_ENABLE_DPA_RST              0x0
/// BT_TEST_ENABLE_CHOP_BG field reset value
#define BT_RF_BT_TEST_ENABLE_CHOP_BG_RST          0x0
/// BT_TEST_ENABLE_DPA_LDO field reset value
#define BT_RF_BT_TEST_ENABLE_DPA_LDO_RST          0x0
/// BT_PU_CHOP_BG_TD_1 field reset value
#define BT_RF_BT_PU_CHOP_BG_TD_1_RST              0x3
/// BT_CHOP_BG_EN_TD_1 field reset value
#define BT_RF_BT_CHOP_BG_EN_TD_1_RST              0x1
/// BT_PU_DPA_LDO_TD_3 field reset value
#define BT_RF_BT_PU_DPA_LDO_TD_3_RST              0x1
/// BT_PU_DLY_DPA_LDO_TD_2 field reset value
#define BT_RF_BT_PU_DLY_DPA_LDO_TD_2_RST          0x3
/// BT_PU_DCO_TD_1 field reset value
#define BT_RF_BT_PU_DCO_TD_1_RST                  0x1
/// BT_DCO_RXLO_EN_TD_1 field reset value
#define BT_RF_BT_DCO_RXLO_EN_TD_1_RST             0x1
/// BT_DCO_TXLO_EN_TD_1 field reset value
#define BT_RF_BT_DCO_TXLO_EN_TD_1_RST             0x1
/// BT_DPA_CLK_2DAC_INTF_EN_TD_1 field reset value
#define BT_RF_BT_DPA_CLK_2DAC_INTF_EN_TD_1_RST    0x1
/// BT_DPLL_GRO_RSTN_TD_1 field reset value
#define BT_RF_BT_DPLL_GRO_RSTN_TD_1_RST           0x1
/// BT_DPLL_GRO_RSTN_TD_2 field reset value
#define BT_RF_BT_DPLL_GRO_RSTN_TD_2_RST           0x3
/// BT_PU_RMX_TD_1 field reset value
#define BT_RF_BT_PU_RMX_TD_1_RST                  0x1

/**
 * @brief Constructs a value for the REG_08 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] bttestenablelna - The value to use for the bt_test_enable_lna field.
 * @param[in] bttestenablermx - The value to use for the bt_test_enable_rmx field.
 * @param[in] bttestenabletia - The value to use for the bt_test_enable_tia field.
 * @param[in] bttestenablesdmadc - The value to use for the bt_test_enable_sdm_adc field.
 * @param[in] bttestacenabledpll - The value to use for the bt_test_ac_enable_dpll field.
 * @param[in] bttestenabledpa - The value to use for the bt_test_enable_dpa field.
 * @param[in] bttestenablechopbg - The value to use for the bt_test_enable_chop_bg field.
 * @param[in] bttestenabledpaldo - The value to use for the bt_test_enable_dpa_ldo field.
 * @param[in] btpuchopbgtd1 - The value to use for the bt_pu_chop_bg_td1 field.
 * @param[in] btchopbgentd1 - The value to use for the bt_chop_bg_en_td1 field.
 * @param[in] btpudpaldotd3 - The value to use for the bt_pu_dpa_ldo_td3 field.
 * @param[in] btpudlydpaldotd2 - The value to use for the bt_pu_dly_dpa_ldo_td2 field.
 * @param[in] btpudcotd1 - The value to use for the bt_pu_dco_td1 field.
 * @param[in] btdcorxloentd1 - The value to use for the bt_dco_rxlo_en_td1 field.
 * @param[in] btdcotxloentd1 - The value to use for the bt_dco_txlo_en_td1 field.
 * @param[in] btdpaclk2dacintfentd1 - The value to use for the bt_dpa_clk2dac_intf_en_td1 field.
 * @param[in] btdpllgrorstntd1 - The value to use for the bt_dpll_gro_rstn_td1 field.
 * @param[in] btdpllgrorstntd2 - The value to use for the bt_dpll_gro_rstn_td2 field.
 * @param[in] btpurmxtd1 - The value to use for the bt_pu_rmx_td1 field.
 */
__INLINE void bt_rf_reg_08_pack(uint8_t bttestenablelna, uint8_t bttestenablermx, uint8_t bttestenabletia, uint8_t bttestenablesdmadc, uint8_t bttestacenabledpll, uint8_t bttestenabledpa, uint8_t bttestenablechopbg, uint8_t bttestenabledpaldo, uint8_t btpuchopbgtd1, uint8_t btchopbgentd1, uint8_t btpudpaldotd3, uint8_t btpudlydpaldotd2, uint8_t btpudcotd1, uint8_t btdcorxloentd1, uint8_t btdcotxloentd1, uint8_t btdpaclk2dacintfentd1, uint8_t btdpllgrorstntd1, uint8_t btdpllgrorstntd2, uint8_t btpurmxtd1)
{
    REG_PL_WR(BT_RF_REG_08_ADDR,  ((uint32_t)bttestenablelna << 31) | ((uint32_t)bttestenablermx << 30) | ((uint32_t)bttestenabletia << 29) | ((uint32_t)bttestenablesdmadc << 28) | ((uint32_t)bttestacenabledpll << 27) | ((uint32_t)bttestenabledpa << 26) | ((uint32_t)bttestenablechopbg << 25) | ((uint32_t)bttestenabledpaldo << 24) | ((uint32_t)btpuchopbgtd1 << 22) | ((uint32_t)btchopbgentd1 << 20) | ((uint32_t)btpudpaldotd3 << 18) | ((uint32_t)btpudlydpaldotd2 << 15) | ((uint32_t)btpudcotd1 << 13) | ((uint32_t)btdcorxloentd1 << 11) | ((uint32_t)btdcotxloentd1 << 9) | ((uint32_t)btdpaclk2dacintfentd1 << 7) | ((uint32_t)btdpllgrorstntd1 << 5) | ((uint32_t)btdpllgrorstntd2 << 2) | ((uint32_t)btpurmxtd1 << 0));
}

/**
 * @brief Unpacks REG_08's fields from current value of the REG_08 register.
 *
 * Reads the REG_08 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] bttestenablelna - Will be populated with the current value of this field from the register.
 * @param[out] bttestenablermx - Will be populated with the current value of this field from the register.
 * @param[out] bttestenabletia - Will be populated with the current value of this field from the register.
 * @param[out] bttestenablesdmadc - Will be populated with the current value of this field from the register.
 * @param[out] bttestacenabledpll - Will be populated with the current value of this field from the register.
 * @param[out] bttestenabledpa - Will be populated with the current value of this field from the register.
 * @param[out] bttestenablechopbg - Will be populated with the current value of this field from the register.
 * @param[out] bttestenabledpaldo - Will be populated with the current value of this field from the register.
 * @param[out] btpuchopbgtd1 - Will be populated with the current value of this field from the register.
 * @param[out] btchopbgentd1 - Will be populated with the current value of this field from the register.
 * @param[out] btpudpaldotd3 - Will be populated with the current value of this field from the register.
 * @param[out] btpudlydpaldotd2 - Will be populated with the current value of this field from the register.
 * @param[out] btpudcotd1 - Will be populated with the current value of this field from the register.
 * @param[out] btdcorxloentd1 - Will be populated with the current value of this field from the register.
 * @param[out] btdcotxloentd1 - Will be populated with the current value of this field from the register.
 * @param[out] btdpaclk2dacintfentd1 - Will be populated with the current value of this field from the register.
 * @param[out] btdpllgrorstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] btdpllgrorstntd2 - Will be populated with the current value of this field from the register.
 * @param[out] btpurmxtd1 - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_08_unpack(uint8_t* bttestenablelna, uint8_t* bttestenablermx, uint8_t* bttestenabletia, uint8_t* bttestenablesdmadc, uint8_t* bttestacenabledpll, uint8_t* bttestenabledpa, uint8_t* bttestenablechopbg, uint8_t* bttestenabledpaldo, uint8_t* btpuchopbgtd1, uint8_t* btchopbgentd1, uint8_t* btpudpaldotd3, uint8_t* btpudlydpaldotd2, uint8_t* btpudcotd1, uint8_t* btdcorxloentd1, uint8_t* btdcotxloentd1, uint8_t* btdpaclk2dacintfentd1, uint8_t* btdpllgrorstntd1, uint8_t* btdpllgrorstntd2, uint8_t* btpurmxtd1)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);

    *bttestenablelna = (localVal & ((uint32_t)0x80000000)) >> 31;
    *bttestenablermx = (localVal & ((uint32_t)0x40000000)) >> 30;
    *bttestenabletia = (localVal & ((uint32_t)0x20000000)) >> 29;
    *bttestenablesdmadc = (localVal & ((uint32_t)0x10000000)) >> 28;
    *bttestacenabledpll = (localVal & ((uint32_t)0x08000000)) >> 27;
    *bttestenabledpa = (localVal & ((uint32_t)0x04000000)) >> 26;
    *bttestenablechopbg = (localVal & ((uint32_t)0x02000000)) >> 25;
    *bttestenabledpaldo = (localVal & ((uint32_t)0x01000000)) >> 24;
    *btpuchopbgtd1 = (localVal & ((uint32_t)0x00C00000)) >> 22;
    *btchopbgentd1 = (localVal & ((uint32_t)0x00300000)) >> 20;
    *btpudpaldotd3 = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *btpudlydpaldotd2 = (localVal & ((uint32_t)0x00038000)) >> 15;
    *btpudcotd1 = (localVal & ((uint32_t)0x00006000)) >> 13;
    *btdcorxloentd1 = (localVal & ((uint32_t)0x00001800)) >> 11;
    *btdcotxloentd1 = (localVal & ((uint32_t)0x00000600)) >> 9;
    *btdpaclk2dacintfentd1 = (localVal & ((uint32_t)0x00000180)) >> 7;
    *btdpllgrorstntd1 = (localVal & ((uint32_t)0x00000060)) >> 5;
    *btdpllgrorstntd2 = (localVal & ((uint32_t)0x0000001C)) >> 2;
    *btpurmxtd1 = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the bt_test_enable_lna field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_test_enable_lna field's value will be returned.
 *
 * @return The current value of the bt_test_enable_lna field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_test_enable_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the bt_test_enable_lna field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttestenablelna - The value to set the field to.
 */
__INLINE void bt_rf_bt_test_enable_lna_setf(uint8_t bttestenablelna)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)bttestenablelna << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the bt_test_enable_rmx field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_test_enable_rmx field's value will be returned.
 *
 * @return The current value of the bt_test_enable_rmx field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_test_enable_rmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the bt_test_enable_rmx field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttestenablermx - The value to set the field to.
 */
__INLINE void bt_rf_bt_test_enable_rmx_setf(uint8_t bttestenablermx)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)bttestenablermx << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the bt_test_enable_tia field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_test_enable_tia field's value will be returned.
 *
 * @return The current value of the bt_test_enable_tia field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_test_enable_tia_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the bt_test_enable_tia field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttestenabletia - The value to set the field to.
 */
__INLINE void bt_rf_bt_test_enable_tia_setf(uint8_t bttestenabletia)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)bttestenabletia << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the bt_test_enable_sdm_adc field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_test_enable_sdm_adc field's value will be returned.
 *
 * @return The current value of the bt_test_enable_sdm_adc field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_test_enable_sdm_adc_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the bt_test_enable_sdm_adc field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttestenablesdmadc - The value to set the field to.
 */
__INLINE void bt_rf_bt_test_enable_sdm_adc_setf(uint8_t bttestenablesdmadc)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)bttestenablesdmadc << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the bt_test_ac_enable_dpll field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_test_ac_enable_dpll field's value will be returned.
 *
 * @return The current value of the bt_test_ac_enable_dpll field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_test_ac_enable_dpll_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the bt_test_ac_enable_dpll field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttestacenabledpll - The value to set the field to.
 */
__INLINE void bt_rf_bt_test_ac_enable_dpll_setf(uint8_t bttestacenabledpll)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)bttestacenabledpll << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the bt_test_enable_dpa field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_test_enable_dpa field's value will be returned.
 *
 * @return The current value of the bt_test_enable_dpa field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_test_enable_dpa_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the bt_test_enable_dpa field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttestenabledpa - The value to set the field to.
 */
__INLINE void bt_rf_bt_test_enable_dpa_setf(uint8_t bttestenabledpa)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)bttestenabledpa << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the bt_test_enable_chop_bg field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_test_enable_chop_bg field's value will be returned.
 *
 * @return The current value of the bt_test_enable_chop_bg field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_test_enable_chop_bg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the bt_test_enable_chop_bg field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttestenablechopbg - The value to set the field to.
 */
__INLINE void bt_rf_bt_test_enable_chop_bg_setf(uint8_t bttestenablechopbg)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)bttestenablechopbg << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the bt_test_enable_dpa_ldo field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_test_enable_dpa_ldo field's value will be returned.
 *
 * @return The current value of the bt_test_enable_dpa_ldo field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_test_enable_dpa_ldo_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the bt_test_enable_dpa_ldo field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttestenabledpaldo - The value to set the field to.
 */
__INLINE void bt_rf_bt_test_enable_dpa_ldo_setf(uint8_t bttestenabledpaldo)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)bttestenabledpaldo << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the bt_pu_chop_bg_td1 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_pu_chop_bg_td1 field's value will be returned.
 *
 * @return The current value of the bt_pu_chop_bg_td1 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_pu_chop_bg_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00C00000)) >> 22);
}

/**
 * @brief Sets the bt_pu_chop_bg_td1 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpuchopbgtd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_chop_bg_td_1_setf(uint8_t btpuchopbgtd1)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x00C00000)) | (((uint32_t)btpuchopbgtd1 << 22) & ((uint32_t)0x00C00000)));
}

/**
 * @brief Returns the current value of the bt_chop_bg_en_td1 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_chop_bg_en_td1 field's value will be returned.
 *
 * @return The current value of the bt_chop_bg_en_td1 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_chop_bg_en_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

/**
 * @brief Sets the bt_chop_bg_en_td1 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btchopbgentd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_chop_bg_en_td_1_setf(uint8_t btchopbgentd1)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x00300000)) | (((uint32_t)btchopbgentd1 << 20) & ((uint32_t)0x00300000)));
}

/**
 * @brief Returns the current value of the bt_pu_dpa_ldo_td3 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_pu_dpa_ldo_td3 field's value will be returned.
 *
 * @return The current value of the bt_pu_dpa_ldo_td3 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dpa_ldo_td_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the bt_pu_dpa_ldo_td3 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudpaldotd3 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dpa_ldo_td_3_setf(uint8_t btpudpaldotd3)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)btpudpaldotd3 << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the bt_pu_dly_dpa_ldo_td2 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_pu_dly_dpa_ldo_td2 field's value will be returned.
 *
 * @return The current value of the bt_pu_dly_dpa_ldo_td2 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dly_dpa_ldo_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00038000)) >> 15);
}

/**
 * @brief Sets the bt_pu_dly_dpa_ldo_td2 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudlydpaldotd2 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dly_dpa_ldo_td_2_setf(uint8_t btpudlydpaldotd2)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x00038000)) | (((uint32_t)btpudlydpaldotd2 << 15) & ((uint32_t)0x00038000)));
}

/**
 * @brief Returns the current value of the bt_pu_dco_td1 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_pu_dco_td1 field's value will be returned.
 *
 * @return The current value of the bt_pu_dco_td1 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_pu_dco_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00006000)) >> 13);
}

/**
 * @brief Sets the bt_pu_dco_td1 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudcotd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dco_td_1_setf(uint8_t btpudcotd1)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x00006000)) | (((uint32_t)btpudcotd1 << 13) & ((uint32_t)0x00006000)));
}

/**
 * @brief Returns the current value of the bt_dco_rxlo_en_td1 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_dco_rxlo_en_td1 field's value will be returned.
 *
 * @return The current value of the bt_dco_rxlo_en_td1 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_dco_rxlo_en_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00001800)) >> 11);
}

/**
 * @brief Sets the bt_dco_rxlo_en_td1 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcorxloentd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_rxlo_en_td_1_setf(uint8_t btdcorxloentd1)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x00001800)) | (((uint32_t)btdcorxloentd1 << 11) & ((uint32_t)0x00001800)));
}

/**
 * @brief Returns the current value of the bt_dco_txlo_en_td1 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_dco_txlo_en_td1 field's value will be returned.
 *
 * @return The current value of the bt_dco_txlo_en_td1 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_dco_txlo_en_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000600)) >> 9);
}

/**
 * @brief Sets the bt_dco_txlo_en_td1 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcotxloentd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_txlo_en_td_1_setf(uint8_t btdcotxloentd1)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x00000600)) | (((uint32_t)btdcotxloentd1 << 9) & ((uint32_t)0x00000600)));
}

/**
 * @brief Returns the current value of the bt_dpa_clk2dac_intf_en_td1 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_dpa_clk2dac_intf_en_td1 field's value will be returned.
 *
 * @return The current value of the bt_dpa_clk2dac_intf_en_td1 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_clk_2dac_intf_en_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000180)) >> 7);
}

/**
 * @brief Sets the bt_dpa_clk2dac_intf_en_td1 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaclk2dacintfentd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_clk_2dac_intf_en_td_1_setf(uint8_t btdpaclk2dacintfentd1)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x00000180)) | (((uint32_t)btdpaclk2dacintfentd1 << 7) & ((uint32_t)0x00000180)));
}

/**
 * @brief Returns the current value of the bt_dpll_gro_rstn_td1 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_dpll_gro_rstn_td1 field's value will be returned.
 *
 * @return The current value of the bt_dpll_gro_rstn_td1 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_gro_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000060)) >> 5);
}

/**
 * @brief Sets the bt_dpll_gro_rstn_td1 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllgrorstntd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_gro_rstn_td_1_setf(uint8_t btdpllgrorstntd1)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x00000060)) | (((uint32_t)btdpllgrorstntd1 << 5) & ((uint32_t)0x00000060)));
}

/**
 * @brief Returns the current value of the bt_dpll_gro_rstn_td2 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_dpll_gro_rstn_td2 field's value will be returned.
 *
 * @return The current value of the bt_dpll_gro_rstn_td2 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_gro_rstn_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x0000001C)) >> 2);
}

/**
 * @brief Sets the bt_dpll_gro_rstn_td2 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllgrorstntd2 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_gro_rstn_td_2_setf(uint8_t btdpllgrorstntd2)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x0000001C)) | (((uint32_t)btdpllgrorstntd2 << 2) & ((uint32_t)0x0000001C)));
}

/**
 * @brief Returns the current value of the bt_pu_rmx_td1 field in the REG_08 register.
 *
 * The REG_08 register will be read and the bt_pu_rmx_td1 field's value will be returned.
 *
 * @return The current value of the bt_pu_rmx_td1 field in the REG_08 register.
 */
__INLINE uint8_t bt_rf_bt_pu_rmx_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the bt_pu_rmx_td1 field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpurmxtd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_rmx_td_1_setf(uint8_t btpurmxtd1)
{
    REG_PL_WR(BT_RF_REG_08_ADDR, (REG_PL_RD(BT_RF_REG_08_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)btpurmxtd1 << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_0C register definitions
 * <table>
 * <caption id="REG_0C_BF">REG_0C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:30 <td>     bt_pu_tia_td1 <td>R <td>R/W <td>0x1
 * <tr><td>29:28 <td>   bt_tia_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>27:26 <td> bt_pu_sdm_adc_td1 <td>R <td>R/W <td>0x1
 * <tr><td>25:24 <td>     bt_pu_lna_td1 <td>R <td>R/W <td>0x1
 * <tr><td>23:22 <td>bt_dpa_cdr_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>21:20 <td>bt_dpa_cdr_rstn_off_td1 <td>R <td>R/W <td>0x1
 * <tr><td>19:18 <td> bt_pu_dpa_off_td1 <td>R <td>R/W <td>0x1
 * <tr><td>17 <td>cm_mdll_auto_reset_en <td>R <td>R/W <td>0
 * <tr><td>16 <td>     co_ant_enable <td>R <td>R/W <td>0
 * <tr><td>15 <td> wf_rxon_co_ant_dr <td>R <td>R/W <td>0
 * <tr><td>14 <td>wf_rxon_co_ant_reg <td>R <td>R/W <td>0
 * <tr><td>13 <td> wf_txon_co_ant_dr <td>R <td>R/W <td>0
 * <tr><td>12 <td>wf_txon_co_ant_reg <td>R <td>R/W <td>0
 * <tr><td>11:10 <td>  btcm_pu_mdll_td1 <td>R <td>R/W <td>0x0
 * <tr><td>09:08 <td>btcm_mdll_rstn_td1 <td>R <td>R/W <td>0x3
 * <tr><td>07:05 <td>btcm_mdll_rstn_td2 <td>R <td>R/W <td>0x1
 * <tr><td>04:03 <td>         bt_pd_td0 <td>R <td>R/W <td>0x1
 * <tr><td>02 <td>   bt_lna_iref_sel <td>R <td>R/W <td>0
 * <tr><td>01:00 <td>       bt_lna_gbit <td>W <td>R <td>0x3
 * </table>
 *
 * @{
 */

/// Address of the REG_0C register
#define BT_RF_REG_0C_ADDR   0x4062200C
/// Offset of the REG_0C register from the base address
#define BT_RF_REG_0C_OFFSET 0x0000000C
/// Index of the REG_0C register
#define BT_RF_REG_0C_INDEX  0x00000003
/// Reset value of the REG_0C register
#define BT_RF_REG_0C_RESET  0x5554032B

/**
 * @brief Returns the current value of the REG_0C register.
 * The REG_0C register will be read and its value returned.
 * @return The current value of the REG_0C register.
 */
__INLINE uint32_t bt_rf_reg_0c_get(void)
{
    return REG_PL_RD(BT_RF_REG_0C_ADDR);
}

/**
 * @brief Sets the REG_0C register to a value.
 * The REG_0C register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_0c_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, value);
}

// field definitions
/// BT_PU_TIA_TD_1 field mask
#define BT_RF_BT_PU_TIA_TD_1_MASK             ((uint32_t)0xC0000000)
/// BT_PU_TIA_TD_1 field LSB position
#define BT_RF_BT_PU_TIA_TD_1_LSB              30
/// BT_PU_TIA_TD_1 field width
#define BT_RF_BT_PU_TIA_TD_1_WIDTH            ((uint32_t)0x00000002)
/// BT_TIA_RSTN_TD_1 field mask
#define BT_RF_BT_TIA_RSTN_TD_1_MASK           ((uint32_t)0x30000000)
/// BT_TIA_RSTN_TD_1 field LSB position
#define BT_RF_BT_TIA_RSTN_TD_1_LSB            28
/// BT_TIA_RSTN_TD_1 field width
#define BT_RF_BT_TIA_RSTN_TD_1_WIDTH          ((uint32_t)0x00000002)
/// BT_PU_SDM_ADC_TD_1 field mask
#define BT_RF_BT_PU_SDM_ADC_TD_1_MASK         ((uint32_t)0x0C000000)
/// BT_PU_SDM_ADC_TD_1 field LSB position
#define BT_RF_BT_PU_SDM_ADC_TD_1_LSB          26
/// BT_PU_SDM_ADC_TD_1 field width
#define BT_RF_BT_PU_SDM_ADC_TD_1_WIDTH        ((uint32_t)0x00000002)
/// BT_PU_LNA_TD_1 field mask
#define BT_RF_BT_PU_LNA_TD_1_MASK             ((uint32_t)0x03000000)
/// BT_PU_LNA_TD_1 field LSB position
#define BT_RF_BT_PU_LNA_TD_1_LSB              24
/// BT_PU_LNA_TD_1 field width
#define BT_RF_BT_PU_LNA_TD_1_WIDTH            ((uint32_t)0x00000002)
/// BT_DPA_CDR_RSTN_TD_1 field mask
#define BT_RF_BT_DPA_CDR_RSTN_TD_1_MASK       ((uint32_t)0x00C00000)
/// BT_DPA_CDR_RSTN_TD_1 field LSB position
#define BT_RF_BT_DPA_CDR_RSTN_TD_1_LSB        22
/// BT_DPA_CDR_RSTN_TD_1 field width
#define BT_RF_BT_DPA_CDR_RSTN_TD_1_WIDTH      ((uint32_t)0x00000002)
/// BT_DPA_CDR_RSTN_OFF_TD_1 field mask
#define BT_RF_BT_DPA_CDR_RSTN_OFF_TD_1_MASK   ((uint32_t)0x00300000)
/// BT_DPA_CDR_RSTN_OFF_TD_1 field LSB position
#define BT_RF_BT_DPA_CDR_RSTN_OFF_TD_1_LSB    20
/// BT_DPA_CDR_RSTN_OFF_TD_1 field width
#define BT_RF_BT_DPA_CDR_RSTN_OFF_TD_1_WIDTH  ((uint32_t)0x00000002)
/// BT_PU_DPA_OFF_TD_1 field mask
#define BT_RF_BT_PU_DPA_OFF_TD_1_MASK         ((uint32_t)0x000C0000)
/// BT_PU_DPA_OFF_TD_1 field LSB position
#define BT_RF_BT_PU_DPA_OFF_TD_1_LSB          18
/// BT_PU_DPA_OFF_TD_1 field width
#define BT_RF_BT_PU_DPA_OFF_TD_1_WIDTH        ((uint32_t)0x00000002)
/// CM_MDLL_AUTO_RESET_EN field bit
#define BT_RF_CM_MDLL_AUTO_RESET_EN_BIT       ((uint32_t)0x00020000)
/// CM_MDLL_AUTO_RESET_EN field position
#define BT_RF_CM_MDLL_AUTO_RESET_EN_POS       17
/// CO_ANT_ENABLE field bit
#define BT_RF_CO_ANT_ENABLE_BIT               ((uint32_t)0x00010000)
/// CO_ANT_ENABLE field position
#define BT_RF_CO_ANT_ENABLE_POS               16
/// WF_RXON_CO_ANT_DR field bit
#define BT_RF_WF_RXON_CO_ANT_DR_BIT           ((uint32_t)0x00008000)
/// WF_RXON_CO_ANT_DR field position
#define BT_RF_WF_RXON_CO_ANT_DR_POS           15
/// WF_RXON_CO_ANT_REG field bit
#define BT_RF_WF_RXON_CO_ANT_REG_BIT          ((uint32_t)0x00004000)
/// WF_RXON_CO_ANT_REG field position
#define BT_RF_WF_RXON_CO_ANT_REG_POS          14
/// WF_TXON_CO_ANT_DR field bit
#define BT_RF_WF_TXON_CO_ANT_DR_BIT           ((uint32_t)0x00002000)
/// WF_TXON_CO_ANT_DR field position
#define BT_RF_WF_TXON_CO_ANT_DR_POS           13
/// WF_TXON_CO_ANT_REG field bit
#define BT_RF_WF_TXON_CO_ANT_REG_BIT          ((uint32_t)0x00001000)
/// WF_TXON_CO_ANT_REG field position
#define BT_RF_WF_TXON_CO_ANT_REG_POS          12
/// BTCM_PU_MDLL_TD_1 field mask
#define BT_RF_BTCM_PU_MDLL_TD_1_MASK          ((uint32_t)0x00000C00)
/// BTCM_PU_MDLL_TD_1 field LSB position
#define BT_RF_BTCM_PU_MDLL_TD_1_LSB           10
/// BTCM_PU_MDLL_TD_1 field width
#define BT_RF_BTCM_PU_MDLL_TD_1_WIDTH         ((uint32_t)0x00000002)
/// BTCM_MDLL_RSTN_TD_1 field mask
#define BT_RF_BTCM_MDLL_RSTN_TD_1_MASK        ((uint32_t)0x00000300)
/// BTCM_MDLL_RSTN_TD_1 field LSB position
#define BT_RF_BTCM_MDLL_RSTN_TD_1_LSB         8
/// BTCM_MDLL_RSTN_TD_1 field width
#define BT_RF_BTCM_MDLL_RSTN_TD_1_WIDTH       ((uint32_t)0x00000002)
/// BTCM_MDLL_RSTN_TD_2 field mask
#define BT_RF_BTCM_MDLL_RSTN_TD_2_MASK        ((uint32_t)0x000000E0)
/// BTCM_MDLL_RSTN_TD_2 field LSB position
#define BT_RF_BTCM_MDLL_RSTN_TD_2_LSB         5
/// BTCM_MDLL_RSTN_TD_2 field width
#define BT_RF_BTCM_MDLL_RSTN_TD_2_WIDTH       ((uint32_t)0x00000003)
/// BT_PD_TD_0 field mask
#define BT_RF_BT_PD_TD_0_MASK                 ((uint32_t)0x00000018)
/// BT_PD_TD_0 field LSB position
#define BT_RF_BT_PD_TD_0_LSB                  3
/// BT_PD_TD_0 field width
#define BT_RF_BT_PD_TD_0_WIDTH                ((uint32_t)0x00000002)
/// BT_LNA_IREF_SEL field bit
#define BT_RF_BT_LNA_IREF_SEL_BIT             ((uint32_t)0x00000004)
/// BT_LNA_IREF_SEL field position
#define BT_RF_BT_LNA_IREF_SEL_POS             2
/// BT_LNA_GBIT field mask
#define BT_RF_BT_LNA_GBIT_MASK                ((uint32_t)0x00000003)
/// BT_LNA_GBIT field LSB position
#define BT_RF_BT_LNA_GBIT_LSB                 0
/// BT_LNA_GBIT field width
#define BT_RF_BT_LNA_GBIT_WIDTH               ((uint32_t)0x00000002)

/// BT_PU_TIA_TD_1 field reset value
#define BT_RF_BT_PU_TIA_TD_1_RST              0x1
/// BT_TIA_RSTN_TD_1 field reset value
#define BT_RF_BT_TIA_RSTN_TD_1_RST            0x1
/// BT_PU_SDM_ADC_TD_1 field reset value
#define BT_RF_BT_PU_SDM_ADC_TD_1_RST          0x1
/// BT_PU_LNA_TD_1 field reset value
#define BT_RF_BT_PU_LNA_TD_1_RST              0x1
/// BT_DPA_CDR_RSTN_TD_1 field reset value
#define BT_RF_BT_DPA_CDR_RSTN_TD_1_RST        0x1
/// BT_DPA_CDR_RSTN_OFF_TD_1 field reset value
#define BT_RF_BT_DPA_CDR_RSTN_OFF_TD_1_RST    0x1
/// BT_PU_DPA_OFF_TD_1 field reset value
#define BT_RF_BT_PU_DPA_OFF_TD_1_RST          0x1
/// CM_MDLL_AUTO_RESET_EN field reset value
#define BT_RF_CM_MDLL_AUTO_RESET_EN_RST       0x0
/// CO_ANT_ENABLE field reset value
#define BT_RF_CO_ANT_ENABLE_RST               0x0
/// WF_RXON_CO_ANT_DR field reset value
#define BT_RF_WF_RXON_CO_ANT_DR_RST           0x0
/// WF_RXON_CO_ANT_REG field reset value
#define BT_RF_WF_RXON_CO_ANT_REG_RST          0x0
/// WF_TXON_CO_ANT_DR field reset value
#define BT_RF_WF_TXON_CO_ANT_DR_RST           0x0
/// WF_TXON_CO_ANT_REG field reset value
#define BT_RF_WF_TXON_CO_ANT_REG_RST          0x0
/// BTCM_PU_MDLL_TD_1 field reset value
#define BT_RF_BTCM_PU_MDLL_TD_1_RST           0x0
/// BTCM_MDLL_RSTN_TD_1 field reset value
#define BT_RF_BTCM_MDLL_RSTN_TD_1_RST         0x3
/// BTCM_MDLL_RSTN_TD_2 field reset value
#define BT_RF_BTCM_MDLL_RSTN_TD_2_RST         0x1
/// BT_PD_TD_0 field reset value
#define BT_RF_BT_PD_TD_0_RST                  0x1
/// BT_LNA_IREF_SEL field reset value
#define BT_RF_BT_LNA_IREF_SEL_RST             0x0
/// BT_LNA_GBIT field reset value
#define BT_RF_BT_LNA_GBIT_RST                 0x3

/**
 * @brief Constructs a value for the REG_0C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btputiatd1 - The value to use for the bt_pu_tia_td1 field.
 * @param[in] bttiarstntd1 - The value to use for the bt_tia_rstn_td1 field.
 * @param[in] btpusdmadctd1 - The value to use for the bt_pu_sdm_adc_td1 field.
 * @param[in] btpulnatd1 - The value to use for the bt_pu_lna_td1 field.
 * @param[in] btdpacdrrstntd1 - The value to use for the bt_dpa_cdr_rstn_td1 field.
 * @param[in] btdpacdrrstnofftd1 - The value to use for the bt_dpa_cdr_rstn_off_td1 field.
 * @param[in] btpudpaofftd1 - The value to use for the bt_pu_dpa_off_td1 field.
 * @param[in] cmmdllautoreseten - The value to use for the cm_mdll_auto_reset_en field.
 * @param[in] coantenable - The value to use for the co_ant_enable field.
 * @param[in] wfrxoncoantdr - The value to use for the wf_rxon_co_ant_dr field.
 * @param[in] wfrxoncoantreg - The value to use for the wf_rxon_co_ant_reg field.
 * @param[in] wftxoncoantdr - The value to use for the wf_txon_co_ant_dr field.
 * @param[in] wftxoncoantreg - The value to use for the wf_txon_co_ant_reg field.
 * @param[in] btcmpumdlltd1 - The value to use for the btcm_pu_mdll_td1 field.
 * @param[in] btcmmdllrstntd1 - The value to use for the btcm_mdll_rstn_td1 field.
 * @param[in] btcmmdllrstntd2 - The value to use for the btcm_mdll_rstn_td2 field.
 * @param[in] btpdtd0 - The value to use for the bt_pd_td0 field.
 * @param[in] btlnairefsel - The value to use for the bt_lna_iref_sel field.
 */
__INLINE void bt_rf_reg_0c_pack(uint8_t btputiatd1, uint8_t bttiarstntd1, uint8_t btpusdmadctd1, uint8_t btpulnatd1, uint8_t btdpacdrrstntd1, uint8_t btdpacdrrstnofftd1, uint8_t btpudpaofftd1, uint8_t cmmdllautoreseten, uint8_t coantenable, uint8_t wfrxoncoantdr, uint8_t wfrxoncoantreg, uint8_t wftxoncoantdr, uint8_t wftxoncoantreg, uint8_t btcmpumdlltd1, uint8_t btcmmdllrstntd1, uint8_t btcmmdllrstntd2, uint8_t btpdtd0, uint8_t btlnairefsel)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR,  ((uint32_t)btputiatd1 << 30) | ((uint32_t)bttiarstntd1 << 28) | ((uint32_t)btpusdmadctd1 << 26) | ((uint32_t)btpulnatd1 << 24) | ((uint32_t)btdpacdrrstntd1 << 22) | ((uint32_t)btdpacdrrstnofftd1 << 20) | ((uint32_t)btpudpaofftd1 << 18) | ((uint32_t)cmmdllautoreseten << 17) | ((uint32_t)coantenable << 16) | ((uint32_t)wfrxoncoantdr << 15) | ((uint32_t)wfrxoncoantreg << 14) | ((uint32_t)wftxoncoantdr << 13) | ((uint32_t)wftxoncoantreg << 12) | ((uint32_t)btcmpumdlltd1 << 10) | ((uint32_t)btcmmdllrstntd1 << 8) | ((uint32_t)btcmmdllrstntd2 << 5) | ((uint32_t)btpdtd0 << 3) | ((uint32_t)btlnairefsel << 2));
}

/**
 * @brief Unpacks REG_0C's fields from current value of the REG_0C register.
 *
 * Reads the REG_0C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btputiatd1 - Will be populated with the current value of this field from the register.
 * @param[out] bttiarstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] btpusdmadctd1 - Will be populated with the current value of this field from the register.
 * @param[out] btpulnatd1 - Will be populated with the current value of this field from the register.
 * @param[out] btdpacdrrstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] btdpacdrrstnofftd1 - Will be populated with the current value of this field from the register.
 * @param[out] btpudpaofftd1 - Will be populated with the current value of this field from the register.
 * @param[out] cmmdllautoreseten - Will be populated with the current value of this field from the register.
 * @param[out] coantenable - Will be populated with the current value of this field from the register.
 * @param[out] wfrxoncoantdr - Will be populated with the current value of this field from the register.
 * @param[out] wfrxoncoantreg - Will be populated with the current value of this field from the register.
 * @param[out] wftxoncoantdr - Will be populated with the current value of this field from the register.
 * @param[out] wftxoncoantreg - Will be populated with the current value of this field from the register.
 * @param[out] btcmpumdlltd1 - Will be populated with the current value of this field from the register.
 * @param[out] btcmmdllrstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] btcmmdllrstntd2 - Will be populated with the current value of this field from the register.
 * @param[out] btpdtd0 - Will be populated with the current value of this field from the register.
 * @param[out] btlnairefsel - Will be populated with the current value of this field from the register.
 * @param[out] btlnagbit - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_0c_unpack(uint8_t* btputiatd1, uint8_t* bttiarstntd1, uint8_t* btpusdmadctd1, uint8_t* btpulnatd1, uint8_t* btdpacdrrstntd1, uint8_t* btdpacdrrstnofftd1, uint8_t* btpudpaofftd1, uint8_t* cmmdllautoreseten, uint8_t* coantenable, uint8_t* wfrxoncoantdr, uint8_t* wfrxoncoantreg, uint8_t* wftxoncoantdr, uint8_t* wftxoncoantreg, uint8_t* btcmpumdlltd1, uint8_t* btcmmdllrstntd1, uint8_t* btcmmdllrstntd2, uint8_t* btpdtd0, uint8_t* btlnairefsel, uint8_t* btlnagbit)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);

    *btputiatd1 = (localVal & ((uint32_t)0xC0000000)) >> 30;
    *bttiarstntd1 = (localVal & ((uint32_t)0x30000000)) >> 28;
    *btpusdmadctd1 = (localVal & ((uint32_t)0x0C000000)) >> 26;
    *btpulnatd1 = (localVal & ((uint32_t)0x03000000)) >> 24;
    *btdpacdrrstntd1 = (localVal & ((uint32_t)0x00C00000)) >> 22;
    *btdpacdrrstnofftd1 = (localVal & ((uint32_t)0x00300000)) >> 20;
    *btpudpaofftd1 = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *cmmdllautoreseten = (localVal & ((uint32_t)0x00020000)) >> 17;
    *coantenable = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wfrxoncoantdr = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wfrxoncoantreg = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wftxoncoantdr = (localVal & ((uint32_t)0x00002000)) >> 13;
    *wftxoncoantreg = (localVal & ((uint32_t)0x00001000)) >> 12;
    *btcmpumdlltd1 = (localVal & ((uint32_t)0x00000C00)) >> 10;
    *btcmmdllrstntd1 = (localVal & ((uint32_t)0x00000300)) >> 8;
    *btcmmdllrstntd2 = (localVal & ((uint32_t)0x000000E0)) >> 5;
    *btpdtd0 = (localVal & ((uint32_t)0x00000018)) >> 3;
    *btlnairefsel = (localVal & ((uint32_t)0x00000004)) >> 2;
    *btlnagbit = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the bt_pu_tia_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_pu_tia_td1 field's value will be returned.
 *
 * @return The current value of the bt_pu_tia_td1 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_pu_tia_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0xC0000000)) >> 30);
}

/**
 * @brief Sets the bt_pu_tia_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btputiatd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_tia_td_1_setf(uint8_t btputiatd1)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0xC0000000)) | (((uint32_t)btputiatd1 << 30) & ((uint32_t)0xC0000000)));
}

/**
 * @brief Returns the current value of the bt_tia_rstn_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_tia_rstn_td1 field's value will be returned.
 *
 * @return The current value of the bt_tia_rstn_td1 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_tia_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

/**
 * @brief Sets the bt_tia_rstn_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiarstntd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_rstn_td_1_setf(uint8_t bttiarstntd1)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x30000000)) | (((uint32_t)bttiarstntd1 << 28) & ((uint32_t)0x30000000)));
}

/**
 * @brief Returns the current value of the bt_pu_sdm_adc_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_pu_sdm_adc_td1 field's value will be returned.
 *
 * @return The current value of the bt_pu_sdm_adc_td1 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_pu_sdm_adc_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x0C000000)) >> 26);
}

/**
 * @brief Sets the bt_pu_sdm_adc_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpusdmadctd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_sdm_adc_td_1_setf(uint8_t btpusdmadctd1)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x0C000000)) | (((uint32_t)btpusdmadctd1 << 26) & ((uint32_t)0x0C000000)));
}

/**
 * @brief Returns the current value of the bt_pu_lna_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_pu_lna_td1 field's value will be returned.
 *
 * @return The current value of the bt_pu_lna_td1 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_pu_lna_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

/**
 * @brief Sets the bt_pu_lna_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpulnatd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_lna_td_1_setf(uint8_t btpulnatd1)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x03000000)) | (((uint32_t)btpulnatd1 << 24) & ((uint32_t)0x03000000)));
}

/**
 * @brief Returns the current value of the bt_dpa_cdr_rstn_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_dpa_cdr_rstn_td1 field's value will be returned.
 *
 * @return The current value of the bt_dpa_cdr_rstn_td1 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_dpa_cdr_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00C00000)) >> 22);
}

/**
 * @brief Sets the bt_dpa_cdr_rstn_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpacdrrstntd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_cdr_rstn_td_1_setf(uint8_t btdpacdrrstntd1)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00C00000)) | (((uint32_t)btdpacdrrstntd1 << 22) & ((uint32_t)0x00C00000)));
}

/**
 * @brief Returns the current value of the bt_dpa_cdr_rstn_off_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_dpa_cdr_rstn_off_td1 field's value will be returned.
 *
 * @return The current value of the bt_dpa_cdr_rstn_off_td1 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_dpa_cdr_rstn_off_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

/**
 * @brief Sets the bt_dpa_cdr_rstn_off_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpacdrrstnofftd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_cdr_rstn_off_td_1_setf(uint8_t btdpacdrrstnofftd1)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00300000)) | (((uint32_t)btdpacdrrstnofftd1 << 20) & ((uint32_t)0x00300000)));
}

/**
 * @brief Returns the current value of the bt_pu_dpa_off_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_pu_dpa_off_td1 field's value will be returned.
 *
 * @return The current value of the bt_pu_dpa_off_td1 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_pu_dpa_off_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the bt_pu_dpa_off_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpudpaofftd1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pu_dpa_off_td_1_setf(uint8_t btpudpaofftd1)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)btpudpaofftd1 << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the cm_mdll_auto_reset_en field in the REG_0C register.
 *
 * The REG_0C register will be read and the cm_mdll_auto_reset_en field's value will be returned.
 *
 * @return The current value of the cm_mdll_auto_reset_en field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_cm_mdll_auto_reset_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the cm_mdll_auto_reset_en field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] cmmdllautoreseten - The value to set the field to.
 */
__INLINE void bt_rf_cm_mdll_auto_reset_en_setf(uint8_t cmmdllautoreseten)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)cmmdllautoreseten << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the co_ant_enable field in the REG_0C register.
 *
 * The REG_0C register will be read and the co_ant_enable field's value will be returned.
 *
 * @return The current value of the co_ant_enable field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_co_ant_enable_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the co_ant_enable field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] coantenable - The value to set the field to.
 */
__INLINE void bt_rf_co_ant_enable_setf(uint8_t coantenable)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)coantenable << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_rxon_co_ant_dr field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxon_co_ant_dr field's value will be returned.
 *
 * @return The current value of the wf_rxon_co_ant_dr field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_wf_rxon_co_ant_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the wf_rxon_co_ant_dr field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxoncoantdr - The value to set the field to.
 */
__INLINE void bt_rf_wf_rxon_co_ant_dr_setf(uint8_t wfrxoncoantdr)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)wfrxoncoantdr << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the wf_rxon_co_ant_reg field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxon_co_ant_reg field's value will be returned.
 *
 * @return The current value of the wf_rxon_co_ant_reg field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_wf_rxon_co_ant_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the wf_rxon_co_ant_reg field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxoncoantreg - The value to set the field to.
 */
__INLINE void bt_rf_wf_rxon_co_ant_reg_setf(uint8_t wfrxoncoantreg)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)wfrxoncoantreg << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the wf_txon_co_ant_dr field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_txon_co_ant_dr field's value will be returned.
 *
 * @return The current value of the wf_txon_co_ant_dr field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_wf_txon_co_ant_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the wf_txon_co_ant_dr field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftxoncoantdr - The value to set the field to.
 */
__INLINE void bt_rf_wf_txon_co_ant_dr_setf(uint8_t wftxoncoantdr)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)wftxoncoantdr << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the wf_txon_co_ant_reg field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_txon_co_ant_reg field's value will be returned.
 *
 * @return The current value of the wf_txon_co_ant_reg field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_wf_txon_co_ant_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_txon_co_ant_reg field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftxoncoantreg - The value to set the field to.
 */
__INLINE void bt_rf_wf_txon_co_ant_reg_setf(uint8_t wftxoncoantreg)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wftxoncoantreg << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the btcm_pu_mdll_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the btcm_pu_mdll_td1 field's value will be returned.
 *
 * @return The current value of the btcm_pu_mdll_td1 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_btcm_pu_mdll_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00000C00)) >> 10);
}

/**
 * @brief Sets the btcm_pu_mdll_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btcmpumdlltd1 - The value to set the field to.
 */
__INLINE void bt_rf_btcm_pu_mdll_td_1_setf(uint8_t btcmpumdlltd1)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00000C00)) | (((uint32_t)btcmpumdlltd1 << 10) & ((uint32_t)0x00000C00)));
}

/**
 * @brief Returns the current value of the btcm_mdll_rstn_td1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the btcm_mdll_rstn_td1 field's value will be returned.
 *
 * @return The current value of the btcm_mdll_rstn_td1 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_btcm_mdll_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the btcm_mdll_rstn_td1 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btcmmdllrstntd1 - The value to set the field to.
 */
__INLINE void bt_rf_btcm_mdll_rstn_td_1_setf(uint8_t btcmmdllrstntd1)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)btcmmdllrstntd1 << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the btcm_mdll_rstn_td2 field in the REG_0C register.
 *
 * The REG_0C register will be read and the btcm_mdll_rstn_td2 field's value will be returned.
 *
 * @return The current value of the btcm_mdll_rstn_td2 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_btcm_mdll_rstn_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x000000E0)) >> 5);
}

/**
 * @brief Sets the btcm_mdll_rstn_td2 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btcmmdllrstntd2 - The value to set the field to.
 */
__INLINE void bt_rf_btcm_mdll_rstn_td_2_setf(uint8_t btcmmdllrstntd2)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x000000E0)) | (((uint32_t)btcmmdllrstntd2 << 5) & ((uint32_t)0x000000E0)));
}

/**
 * @brief Returns the current value of the bt_pd_td0 field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_pd_td0 field's value will be returned.
 *
 * @return The current value of the bt_pd_td0 field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_pd_td_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00000018)) >> 3);
}

/**
 * @brief Sets the bt_pd_td0 field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btpdtd0 - The value to set the field to.
 */
__INLINE void bt_rf_bt_pd_td_0_setf(uint8_t btpdtd0)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00000018)) | (((uint32_t)btpdtd0 << 3) & ((uint32_t)0x00000018)));
}

/**
 * @brief Returns the current value of the bt_lna_iref_sel field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_lna_iref_sel field's value will be returned.
 *
 * @return The current value of the bt_lna_iref_sel field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_lna_iref_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the bt_lna_iref_sel field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btlnairefsel - The value to set the field to.
 */
__INLINE void bt_rf_bt_lna_iref_sel_setf(uint8_t btlnairefsel)
{
    REG_PL_WR(BT_RF_REG_0C_ADDR, (REG_PL_RD(BT_RF_REG_0C_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)btlnairefsel << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the bt_lna_gbit field in the REG_0C register.
 *
 * The REG_0C register will be read and the bt_lna_gbit field's value will be returned.
 *
 * @return The current value of the bt_lna_gbit field in the REG_0C register.
 */
__INLINE uint8_t bt_rf_bt_lna_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/// @}

/**
 * @name REG_10 register definitions
 * <table>
 * <caption id="REG_10_BF">REG_10 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>28:25 <td>  bt_lna_ibias_bit <td>W <td>R <td>0xA
 * <tr><td>24:21 <td>    bt_lna_cg_vbit <td>R <td>R/W <td>0x5
 * <tr><td>20 <td>bt_lna_mixer1st_en <td>W <td>R <td>0
 * <tr><td>19:16 <td>       bt_lna_cbit <td>W <td>R <td>0x7
 * <tr><td>15 <td>    bt_lna_cap_sel <td>W <td>R <td>0
 * <tr><td>14:12 <td>bt_rmx_lobias_vbit <td>R <td>R/W <td>0x3
 * <tr><td>11 <td>   bt_tia_lpf_mode <td>R <td>R/W <td>0
 * <tr><td>10 <td>    bt_tia_swap_en <td>R <td>R/W <td>0
 * <tr><td>09:05 <td>     bt_tia_bw_bit <td>W <td>R <td>0x6
 * <tr><td>04:00 <td>     bt_tia_if_bit <td>W <td>R <td>0x13
 * </table>
 *
 * @{
 */

/// Address of the REG_10 register
#define BT_RF_REG_10_ADDR   0x40622010
/// Offset of the REG_10 register from the base address
#define BT_RF_REG_10_OFFSET 0x00000010
/// Index of the REG_10 register
#define BT_RF_REG_10_INDEX  0x00000004
/// Reset value of the REG_10 register
#define BT_RF_REG_10_RESET  0x14A730D3

/**
 * @brief Returns the current value of the REG_10 register.
 * The REG_10 register will be read and its value returned.
 * @return The current value of the REG_10 register.
 */
__INLINE uint32_t bt_rf_reg_10_get(void)
{
    return REG_PL_RD(BT_RF_REG_10_ADDR);
}

/**
 * @brief Sets the REG_10 register to a value.
 * The REG_10 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_10_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_10_ADDR, value);
}

// field definitions
/// BT_LNA_IBIAS_BIT field mask
#define BT_RF_BT_LNA_IBIAS_BIT_MASK      ((uint32_t)0x1E000000)
/// BT_LNA_IBIAS_BIT field LSB position
#define BT_RF_BT_LNA_IBIAS_BIT_LSB       25
/// BT_LNA_IBIAS_BIT field width
#define BT_RF_BT_LNA_IBIAS_BIT_WIDTH     ((uint32_t)0x00000004)
/// BT_LNA_CG_VBIT field mask
#define BT_RF_BT_LNA_CG_VBIT_MASK        ((uint32_t)0x01E00000)
/// BT_LNA_CG_VBIT field LSB position
#define BT_RF_BT_LNA_CG_VBIT_LSB         21
/// BT_LNA_CG_VBIT field width
#define BT_RF_BT_LNA_CG_VBIT_WIDTH       ((uint32_t)0x00000004)
/// BT_LNA_MIXER_1ST_EN field bit
#define BT_RF_BT_LNA_MIXER_1ST_EN_BIT    ((uint32_t)0x00100000)
/// BT_LNA_MIXER_1ST_EN field position
#define BT_RF_BT_LNA_MIXER_1ST_EN_POS    20
/// BT_LNA_CBIT field mask
#define BT_RF_BT_LNA_CBIT_MASK           ((uint32_t)0x000F0000)
/// BT_LNA_CBIT field LSB position
#define BT_RF_BT_LNA_CBIT_LSB            16
/// BT_LNA_CBIT field width
#define BT_RF_BT_LNA_CBIT_WIDTH          ((uint32_t)0x00000004)
/// BT_LNA_CAP_SEL field bit
#define BT_RF_BT_LNA_CAP_SEL_BIT         ((uint32_t)0x00008000)
/// BT_LNA_CAP_SEL field position
#define BT_RF_BT_LNA_CAP_SEL_POS         15
/// BT_RMX_LOBIAS_VBIT field mask
#define BT_RF_BT_RMX_LOBIAS_VBIT_MASK    ((uint32_t)0x00007000)
/// BT_RMX_LOBIAS_VBIT field LSB position
#define BT_RF_BT_RMX_LOBIAS_VBIT_LSB     12
/// BT_RMX_LOBIAS_VBIT field width
#define BT_RF_BT_RMX_LOBIAS_VBIT_WIDTH   ((uint32_t)0x00000003)
/// BT_TIA_LPF_MODE field bit
#define BT_RF_BT_TIA_LPF_MODE_BIT        ((uint32_t)0x00000800)
/// BT_TIA_LPF_MODE field position
#define BT_RF_BT_TIA_LPF_MODE_POS        11
/// BT_TIA_SWAP_EN field bit
#define BT_RF_BT_TIA_SWAP_EN_BIT         ((uint32_t)0x00000400)
/// BT_TIA_SWAP_EN field position
#define BT_RF_BT_TIA_SWAP_EN_POS         10
/// BT_TIA_BW_BIT field mask
#define BT_RF_BT_TIA_BW_BIT_MASK         ((uint32_t)0x000003E0)
/// BT_TIA_BW_BIT field LSB position
#define BT_RF_BT_TIA_BW_BIT_LSB          5
/// BT_TIA_BW_BIT field width
#define BT_RF_BT_TIA_BW_BIT_WIDTH        ((uint32_t)0x00000005)
/// BT_TIA_IF_BIT field mask
#define BT_RF_BT_TIA_IF_BIT_MASK         ((uint32_t)0x0000001F)
/// BT_TIA_IF_BIT field LSB position
#define BT_RF_BT_TIA_IF_BIT_LSB          0
/// BT_TIA_IF_BIT field width
#define BT_RF_BT_TIA_IF_BIT_WIDTH        ((uint32_t)0x00000005)

/// BT_LNA_IBIAS_BIT field reset value
#define BT_RF_BT_LNA_IBIAS_BIT_RST       0xA
/// BT_LNA_CG_VBIT field reset value
#define BT_RF_BT_LNA_CG_VBIT_RST         0x5
/// BT_LNA_MIXER_1ST_EN field reset value
#define BT_RF_BT_LNA_MIXER_1ST_EN_RST    0x0
/// BT_LNA_CBIT field reset value
#define BT_RF_BT_LNA_CBIT_RST            0x7
/// BT_LNA_CAP_SEL field reset value
#define BT_RF_BT_LNA_CAP_SEL_RST         0x0
/// BT_RMX_LOBIAS_VBIT field reset value
#define BT_RF_BT_RMX_LOBIAS_VBIT_RST     0x3
/// BT_TIA_LPF_MODE field reset value
#define BT_RF_BT_TIA_LPF_MODE_RST        0x0
/// BT_TIA_SWAP_EN field reset value
#define BT_RF_BT_TIA_SWAP_EN_RST         0x0
/// BT_TIA_BW_BIT field reset value
#define BT_RF_BT_TIA_BW_BIT_RST          0x6
/// BT_TIA_IF_BIT field reset value
#define BT_RF_BT_TIA_IF_BIT_RST          0x13

/**
 * @brief Constructs a value for the REG_10 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btlnacgvbit - The value to use for the bt_lna_cg_vbit field.
 * @param[in] btrmxlobiasvbit - The value to use for the bt_rmx_lobias_vbit field.
 * @param[in] bttialpfmode - The value to use for the bt_tia_lpf_mode field.
 * @param[in] bttiaswapen - The value to use for the bt_tia_swap_en field.
 */
__INLINE void bt_rf_reg_10_pack(uint8_t btlnacgvbit, uint8_t btrmxlobiasvbit, uint8_t bttialpfmode, uint8_t bttiaswapen)
{
    REG_PL_WR(BT_RF_REG_10_ADDR,  ((uint32_t)btlnacgvbit << 21) | ((uint32_t)btrmxlobiasvbit << 12) | ((uint32_t)bttialpfmode << 11) | ((uint32_t)bttiaswapen << 10));
}

/**
 * @brief Unpacks REG_10's fields from current value of the REG_10 register.
 *
 * Reads the REG_10 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btlnaibiasbit - Will be populated with the current value of this field from the register.
 * @param[out] btlnacgvbit - Will be populated with the current value of this field from the register.
 * @param[out] btlnamixer1sten - Will be populated with the current value of this field from the register.
 * @param[out] btlnacbit - Will be populated with the current value of this field from the register.
 * @param[out] btlnacapsel - Will be populated with the current value of this field from the register.
 * @param[out] btrmxlobiasvbit - Will be populated with the current value of this field from the register.
 * @param[out] bttialpfmode - Will be populated with the current value of this field from the register.
 * @param[out] bttiaswapen - Will be populated with the current value of this field from the register.
 * @param[out] bttiabwbit - Will be populated with the current value of this field from the register.
 * @param[out] bttiaifbit - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_10_unpack(uint8_t* btlnaibiasbit, uint8_t* btlnacgvbit, uint8_t* btlnamixer1sten, uint8_t* btlnacbit, uint8_t* btlnacapsel, uint8_t* btrmxlobiasvbit, uint8_t* bttialpfmode, uint8_t* bttiaswapen, uint8_t* bttiabwbit, uint8_t* bttiaifbit)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);

    *btlnaibiasbit = (localVal & ((uint32_t)0x1E000000)) >> 25;
    *btlnacgvbit = (localVal & ((uint32_t)0x01E00000)) >> 21;
    *btlnamixer1sten = (localVal & ((uint32_t)0x00100000)) >> 20;
    *btlnacbit = (localVal & ((uint32_t)0x000F0000)) >> 16;
    *btlnacapsel = (localVal & ((uint32_t)0x00008000)) >> 15;
    *btrmxlobiasvbit = (localVal & ((uint32_t)0x00007000)) >> 12;
    *bttialpfmode = (localVal & ((uint32_t)0x00000800)) >> 11;
    *bttiaswapen = (localVal & ((uint32_t)0x00000400)) >> 10;
    *bttiabwbit = (localVal & ((uint32_t)0x000003E0)) >> 5;
    *bttiaifbit = (localVal & ((uint32_t)0x0000001F)) >> 0;
}

/**
 * @brief Returns the current value of the bt_lna_ibias_bit field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_lna_ibias_bit field's value will be returned.
 *
 * @return The current value of the bt_lna_ibias_bit field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_lna_ibias_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x1E000000)) >> 25);
}

/**
 * @brief Returns the current value of the bt_lna_cg_vbit field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_lna_cg_vbit field's value will be returned.
 *
 * @return The current value of the bt_lna_cg_vbit field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_lna_cg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x01E00000)) >> 21);
}

/**
 * @brief Sets the bt_lna_cg_vbit field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btlnacgvbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_lna_cg_vbit_setf(uint8_t btlnacgvbit)
{
    REG_PL_WR(BT_RF_REG_10_ADDR, (REG_PL_RD(BT_RF_REG_10_ADDR) & ~((uint32_t)0x01E00000)) | (((uint32_t)btlnacgvbit << 21) & ((uint32_t)0x01E00000)));
}

/**
 * @brief Returns the current value of the bt_lna_mixer1st_en field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_lna_mixer1st_en field's value will be returned.
 *
 * @return The current value of the bt_lna_mixer1st_en field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_lna_mixer_1st_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Returns the current value of the bt_lna_cbit field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_lna_cbit field's value will be returned.
 *
 * @return The current value of the bt_lna_cbit field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_lna_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x000F0000)) >> 16);
}

/**
 * @brief Returns the current value of the bt_lna_cap_sel field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_lna_cap_sel field's value will be returned.
 *
 * @return The current value of the bt_lna_cap_sel field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_lna_cap_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Returns the current value of the bt_rmx_lobias_vbit field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_rmx_lobias_vbit field's value will be returned.
 *
 * @return The current value of the bt_rmx_lobias_vbit field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_rmx_lobias_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

/**
 * @brief Sets the bt_rmx_lobias_vbit field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btrmxlobiasvbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_rmx_lobias_vbit_setf(uint8_t btrmxlobiasvbit)
{
    REG_PL_WR(BT_RF_REG_10_ADDR, (REG_PL_RD(BT_RF_REG_10_ADDR) & ~((uint32_t)0x00007000)) | (((uint32_t)btrmxlobiasvbit << 12) & ((uint32_t)0x00007000)));
}

/**
 * @brief Returns the current value of the bt_tia_lpf_mode field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_tia_lpf_mode field's value will be returned.
 *
 * @return The current value of the bt_tia_lpf_mode field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_tia_lpf_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the bt_tia_lpf_mode field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttialpfmode - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_lpf_mode_setf(uint8_t bttialpfmode)
{
    REG_PL_WR(BT_RF_REG_10_ADDR, (REG_PL_RD(BT_RF_REG_10_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)bttialpfmode << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the bt_tia_swap_en field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_tia_swap_en field's value will be returned.
 *
 * @return The current value of the bt_tia_swap_en field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_tia_swap_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the bt_tia_swap_en field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiaswapen - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_swap_en_setf(uint8_t bttiaswapen)
{
    REG_PL_WR(BT_RF_REG_10_ADDR, (REG_PL_RD(BT_RF_REG_10_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)bttiaswapen << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the bt_tia_bw_bit field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_tia_bw_bit field's value will be returned.
 *
 * @return The current value of the bt_tia_bw_bit field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_tia_bw_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x000003E0)) >> 5);
}

/**
 * @brief Returns the current value of the bt_tia_if_bit field in the REG_10 register.
 *
 * The REG_10 register will be read and the bt_tia_if_bit field's value will be returned.
 *
 * @return The current value of the bt_tia_if_bit field in the REG_10 register.
 */
__INLINE uint8_t bt_rf_bt_tia_if_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x0000001F)) >> 0);
}

/// @}

/**
 * @name REG_14 register definitions
 * <table>
 * <caption id="REG_14_BF">REG_14 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:26 <td>    bt_tia_op_ibit <td>W <td>R <td>0xC
 * <tr><td>25:23 <td>bt_tia_op_mil_cbit <td>W <td>R <td>0x3
 * <tr><td>22:20 <td>bt_tia_op_mil_rbit <td>W <td>R <td>0x3
 * <tr><td>19:17 <td>  bt_tia_op_q_rbit <td>W <td>R <td>0x3
 * <tr><td>16:14 <td>   bt_tia_vcm_vbit <td>R <td>R/W <td>0x4
 * <tr><td>13:11 <td>bt_tia_cal_i_range <td>W <td>R <td>0x3
 * <tr><td>10:08 <td>bt_tia_cal_v_range <td>R <td>R/W <td>0x3
 * <tr><td>07:03 <td>   bt_tia_gain_bit <td>W <td>R <td>0xF
 * <tr><td>02:00 <td>    bt_tia_rin_bit <td>W <td>R <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the REG_14 register
#define BT_RF_REG_14_ADDR   0x40622014
/// Offset of the REG_14 register from the base address
#define BT_RF_REG_14_OFFSET 0x00000014
/// Index of the REG_14 register
#define BT_RF_REG_14_INDEX  0x00000005
/// Reset value of the REG_14 register
#define BT_RF_REG_14_RESET  0x31B71B78

/**
 * @brief Returns the current value of the REG_14 register.
 * The REG_14 register will be read and its value returned.
 * @return The current value of the REG_14 register.
 */
__INLINE uint32_t bt_rf_reg_14_get(void)
{
    return REG_PL_RD(BT_RF_REG_14_ADDR);
}

/**
 * @brief Sets the REG_14 register to a value.
 * The REG_14 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_14_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_14_ADDR, value);
}

// field definitions
/// BT_TIA_OP_IBIT field mask
#define BT_RF_BT_TIA_OP_IBIT_MASK       ((uint32_t)0x3C000000)
/// BT_TIA_OP_IBIT field LSB position
#define BT_RF_BT_TIA_OP_IBIT_LSB        26
/// BT_TIA_OP_IBIT field width
#define BT_RF_BT_TIA_OP_IBIT_WIDTH      ((uint32_t)0x00000004)
/// BT_TIA_OP_MIL_CBIT field mask
#define BT_RF_BT_TIA_OP_MIL_CBIT_MASK   ((uint32_t)0x03800000)
/// BT_TIA_OP_MIL_CBIT field LSB position
#define BT_RF_BT_TIA_OP_MIL_CBIT_LSB    23
/// BT_TIA_OP_MIL_CBIT field width
#define BT_RF_BT_TIA_OP_MIL_CBIT_WIDTH  ((uint32_t)0x00000003)
/// BT_TIA_OP_MIL_RBIT field mask
#define BT_RF_BT_TIA_OP_MIL_RBIT_MASK   ((uint32_t)0x00700000)
/// BT_TIA_OP_MIL_RBIT field LSB position
#define BT_RF_BT_TIA_OP_MIL_RBIT_LSB    20
/// BT_TIA_OP_MIL_RBIT field width
#define BT_RF_BT_TIA_OP_MIL_RBIT_WIDTH  ((uint32_t)0x00000003)
/// BT_TIA_OP_Q_RBIT field mask
#define BT_RF_BT_TIA_OP_Q_RBIT_MASK     ((uint32_t)0x000E0000)
/// BT_TIA_OP_Q_RBIT field LSB position
#define BT_RF_BT_TIA_OP_Q_RBIT_LSB      17
/// BT_TIA_OP_Q_RBIT field width
#define BT_RF_BT_TIA_OP_Q_RBIT_WIDTH    ((uint32_t)0x00000003)
/// BT_TIA_VCM_VBIT field mask
#define BT_RF_BT_TIA_VCM_VBIT_MASK      ((uint32_t)0x0001C000)
/// BT_TIA_VCM_VBIT field LSB position
#define BT_RF_BT_TIA_VCM_VBIT_LSB       14
/// BT_TIA_VCM_VBIT field width
#define BT_RF_BT_TIA_VCM_VBIT_WIDTH     ((uint32_t)0x00000003)
/// BT_TIA_CAL_I_RANGE field mask
#define BT_RF_BT_TIA_CAL_I_RANGE_MASK   ((uint32_t)0x00003800)
/// BT_TIA_CAL_I_RANGE field LSB position
#define BT_RF_BT_TIA_CAL_I_RANGE_LSB    11
/// BT_TIA_CAL_I_RANGE field width
#define BT_RF_BT_TIA_CAL_I_RANGE_WIDTH  ((uint32_t)0x00000003)
/// BT_TIA_CAL_V_RANGE field mask
#define BT_RF_BT_TIA_CAL_V_RANGE_MASK   ((uint32_t)0x00000700)
/// BT_TIA_CAL_V_RANGE field LSB position
#define BT_RF_BT_TIA_CAL_V_RANGE_LSB    8
/// BT_TIA_CAL_V_RANGE field width
#define BT_RF_BT_TIA_CAL_V_RANGE_WIDTH  ((uint32_t)0x00000003)
/// BT_TIA_GAIN_BIT field mask
#define BT_RF_BT_TIA_GAIN_BIT_MASK      ((uint32_t)0x000000F8)
/// BT_TIA_GAIN_BIT field LSB position
#define BT_RF_BT_TIA_GAIN_BIT_LSB       3
/// BT_TIA_GAIN_BIT field width
#define BT_RF_BT_TIA_GAIN_BIT_WIDTH     ((uint32_t)0x00000005)
/// BT_TIA_RIN_BIT field mask
#define BT_RF_BT_TIA_RIN_BIT_MASK       ((uint32_t)0x00000007)
/// BT_TIA_RIN_BIT field LSB position
#define BT_RF_BT_TIA_RIN_BIT_LSB        0
/// BT_TIA_RIN_BIT field width
#define BT_RF_BT_TIA_RIN_BIT_WIDTH      ((uint32_t)0x00000003)

/// BT_TIA_OP_IBIT field reset value
#define BT_RF_BT_TIA_OP_IBIT_RST        0xC
/// BT_TIA_OP_MIL_CBIT field reset value
#define BT_RF_BT_TIA_OP_MIL_CBIT_RST    0x3
/// BT_TIA_OP_MIL_RBIT field reset value
#define BT_RF_BT_TIA_OP_MIL_RBIT_RST    0x3
/// BT_TIA_OP_Q_RBIT field reset value
#define BT_RF_BT_TIA_OP_Q_RBIT_RST      0x3
/// BT_TIA_VCM_VBIT field reset value
#define BT_RF_BT_TIA_VCM_VBIT_RST       0x4
/// BT_TIA_CAL_I_RANGE field reset value
#define BT_RF_BT_TIA_CAL_I_RANGE_RST    0x3
/// BT_TIA_CAL_V_RANGE field reset value
#define BT_RF_BT_TIA_CAL_V_RANGE_RST    0x3
/// BT_TIA_GAIN_BIT field reset value
#define BT_RF_BT_TIA_GAIN_BIT_RST       0xF
/// BT_TIA_RIN_BIT field reset value
#define BT_RF_BT_TIA_RIN_BIT_RST        0x0

/**
 * @brief Constructs a value for the REG_14 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] bttiavcmvbit - The value to use for the bt_tia_vcm_vbit field.
 * @param[in] bttiacalvrange - The value to use for the bt_tia_cal_v_range field.
 */
__INLINE void bt_rf_reg_14_pack(uint8_t bttiavcmvbit, uint8_t bttiacalvrange)
{
    REG_PL_WR(BT_RF_REG_14_ADDR,  ((uint32_t)bttiavcmvbit << 14) | ((uint32_t)bttiacalvrange << 8));
}

/**
 * @brief Unpacks REG_14's fields from current value of the REG_14 register.
 *
 * Reads the REG_14 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] bttiaopibit - Will be populated with the current value of this field from the register.
 * @param[out] bttiaopmilcbit - Will be populated with the current value of this field from the register.
 * @param[out] bttiaopmilrbit - Will be populated with the current value of this field from the register.
 * @param[out] bttiaopqrbit - Will be populated with the current value of this field from the register.
 * @param[out] bttiavcmvbit - Will be populated with the current value of this field from the register.
 * @param[out] bttiacalirange - Will be populated with the current value of this field from the register.
 * @param[out] bttiacalvrange - Will be populated with the current value of this field from the register.
 * @param[out] bttiagainbit - Will be populated with the current value of this field from the register.
 * @param[out] bttiarinbit - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_14_unpack(uint8_t* bttiaopibit, uint8_t* bttiaopmilcbit, uint8_t* bttiaopmilrbit, uint8_t* bttiaopqrbit, uint8_t* bttiavcmvbit, uint8_t* bttiacalirange, uint8_t* bttiacalvrange, uint8_t* bttiagainbit, uint8_t* bttiarinbit)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);

    *bttiaopibit = (localVal & ((uint32_t)0x3C000000)) >> 26;
    *bttiaopmilcbit = (localVal & ((uint32_t)0x03800000)) >> 23;
    *bttiaopmilrbit = (localVal & ((uint32_t)0x00700000)) >> 20;
    *bttiaopqrbit = (localVal & ((uint32_t)0x000E0000)) >> 17;
    *bttiavcmvbit = (localVal & ((uint32_t)0x0001C000)) >> 14;
    *bttiacalirange = (localVal & ((uint32_t)0x00003800)) >> 11;
    *bttiacalvrange = (localVal & ((uint32_t)0x00000700)) >> 8;
    *bttiagainbit = (localVal & ((uint32_t)0x000000F8)) >> 3;
    *bttiarinbit = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the bt_tia_op_ibit field in the REG_14 register.
 *
 * The REG_14 register will be read and the bt_tia_op_ibit field's value will be returned.
 *
 * @return The current value of the bt_tia_op_ibit field in the REG_14 register.
 */
__INLINE uint8_t bt_rf_bt_tia_op_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x3C000000)) >> 26);
}

/**
 * @brief Returns the current value of the bt_tia_op_mil_cbit field in the REG_14 register.
 *
 * The REG_14 register will be read and the bt_tia_op_mil_cbit field's value will be returned.
 *
 * @return The current value of the bt_tia_op_mil_cbit field in the REG_14 register.
 */
__INLINE uint8_t bt_rf_bt_tia_op_mil_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x03800000)) >> 23);
}

/**
 * @brief Returns the current value of the bt_tia_op_mil_rbit field in the REG_14 register.
 *
 * The REG_14 register will be read and the bt_tia_op_mil_rbit field's value will be returned.
 *
 * @return The current value of the bt_tia_op_mil_rbit field in the REG_14 register.
 */
__INLINE uint8_t bt_rf_bt_tia_op_mil_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

/**
 * @brief Returns the current value of the bt_tia_op_q_rbit field in the REG_14 register.
 *
 * The REG_14 register will be read and the bt_tia_op_q_rbit field's value will be returned.
 *
 * @return The current value of the bt_tia_op_q_rbit field in the REG_14 register.
 */
__INLINE uint8_t bt_rf_bt_tia_op_q_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x000E0000)) >> 17);
}

/**
 * @brief Returns the current value of the bt_tia_vcm_vbit field in the REG_14 register.
 *
 * The REG_14 register will be read and the bt_tia_vcm_vbit field's value will be returned.
 *
 * @return The current value of the bt_tia_vcm_vbit field in the REG_14 register.
 */
__INLINE uint8_t bt_rf_bt_tia_vcm_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x0001C000)) >> 14);
}

/**
 * @brief Sets the bt_tia_vcm_vbit field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiavcmvbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_vcm_vbit_setf(uint8_t bttiavcmvbit)
{
    REG_PL_WR(BT_RF_REG_14_ADDR, (REG_PL_RD(BT_RF_REG_14_ADDR) & ~((uint32_t)0x0001C000)) | (((uint32_t)bttiavcmvbit << 14) & ((uint32_t)0x0001C000)));
}

/**
 * @brief Returns the current value of the bt_tia_cal_i_range field in the REG_14 register.
 *
 * The REG_14 register will be read and the bt_tia_cal_i_range field's value will be returned.
 *
 * @return The current value of the bt_tia_cal_i_range field in the REG_14 register.
 */
__INLINE uint8_t bt_rf_bt_tia_cal_i_range_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00003800)) >> 11);
}

/**
 * @brief Returns the current value of the bt_tia_cal_v_range field in the REG_14 register.
 *
 * The REG_14 register will be read and the bt_tia_cal_v_range field's value will be returned.
 *
 * @return The current value of the bt_tia_cal_v_range field in the REG_14 register.
 */
__INLINE uint8_t bt_rf_bt_tia_cal_v_range_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

/**
 * @brief Sets the bt_tia_cal_v_range field of the REG_14 register.
 *
 * The REG_14 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiacalvrange - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_cal_v_range_setf(uint8_t bttiacalvrange)
{
    REG_PL_WR(BT_RF_REG_14_ADDR, (REG_PL_RD(BT_RF_REG_14_ADDR) & ~((uint32_t)0x00000700)) | (((uint32_t)bttiacalvrange << 8) & ((uint32_t)0x00000700)));
}

/**
 * @brief Returns the current value of the bt_tia_gain_bit field in the REG_14 register.
 *
 * The REG_14 register will be read and the bt_tia_gain_bit field's value will be returned.
 *
 * @return The current value of the bt_tia_gain_bit field in the REG_14 register.
 */
__INLINE uint8_t bt_rf_bt_tia_gain_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x000000F8)) >> 3);
}

/**
 * @brief Returns the current value of the bt_tia_rin_bit field in the REG_14 register.
 *
 * The REG_14 register will be read and the bt_tia_rin_bit field's value will be returned.
 *
 * @return The current value of the bt_tia_rin_bit field in the REG_14 register.
 */
__INLINE uint8_t bt_rf_bt_tia_rin_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_14_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/// @}

/**
 * @name REG_18 register definitions
 * <table>
 * <caption id="REG_18_BF">REG_18 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>27 <td>bt_tia_i_cal_bit_dr <td>R <td>R/W <td>0
 * <tr><td>26:20 <td>bt_tia_i_cal_bit_reg <td>R <td>R/W <td>0x40
 * <tr><td>19 <td>bt_tia_q_cal_bit_dr <td>R <td>R/W <td>0
 * <tr><td>18:12 <td>bt_tia_q_cal_bit_reg <td>R <td>R/W <td>0x40
 * <tr><td>11 <td>bt_sdm_adc_clk_sar_div2_en <td>R <td>R/W <td>1
 * <tr><td>10 <td>bt_sdm_adc_dith_en <td>R <td>R/W <td>1
 * <tr><td>09:06 <td>bt_sdm_adc_vcal_bit <td>R <td>R/W <td>0x8
 * <tr><td>05:03 <td>   bt_sdm_adc_cbit <td>R <td>R/W <td>0x3
 * <tr><td>02 <td> bt_sdm_adc_cal_en <td>R <td>R/W <td>1
 * <tr><td>01:00 <td>   bt_sdm_adc_gbit <td>W <td>R <td>0x2
 * </table>
 *
 * @{
 */

/// Address of the REG_18 register
#define BT_RF_REG_18_ADDR   0x40622018
/// Offset of the REG_18 register from the base address
#define BT_RF_REG_18_OFFSET 0x00000018
/// Index of the REG_18 register
#define BT_RF_REG_18_INDEX  0x00000006
/// Reset value of the REG_18 register
#define BT_RF_REG_18_RESET  0x04040E1E

/**
 * @brief Returns the current value of the REG_18 register.
 * The REG_18 register will be read and its value returned.
 * @return The current value of the REG_18 register.
 */
__INLINE uint32_t bt_rf_reg_18_get(void)
{
    return REG_PL_RD(BT_RF_REG_18_ADDR);
}

/**
 * @brief Sets the REG_18 register to a value.
 * The REG_18 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_18_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, value);
}

// field definitions
/// BT_TIA_I_CAL_BIT_DR field bit
#define BT_RF_BT_TIA_I_CAL_BIT_DR_BIT            ((uint32_t)0x08000000)
/// BT_TIA_I_CAL_BIT_DR field position
#define BT_RF_BT_TIA_I_CAL_BIT_DR_POS            27
/// BT_TIA_I_CAL_BIT_REG field mask
#define BT_RF_BT_TIA_I_CAL_BIT_REG_MASK          ((uint32_t)0x07F00000)
/// BT_TIA_I_CAL_BIT_REG field LSB position
#define BT_RF_BT_TIA_I_CAL_BIT_REG_LSB           20
/// BT_TIA_I_CAL_BIT_REG field width
#define BT_RF_BT_TIA_I_CAL_BIT_REG_WIDTH         ((uint32_t)0x00000007)
/// BT_TIA_Q_CAL_BIT_DR field bit
#define BT_RF_BT_TIA_Q_CAL_BIT_DR_BIT            ((uint32_t)0x00080000)
/// BT_TIA_Q_CAL_BIT_DR field position
#define BT_RF_BT_TIA_Q_CAL_BIT_DR_POS            19
/// BT_TIA_Q_CAL_BIT_REG field mask
#define BT_RF_BT_TIA_Q_CAL_BIT_REG_MASK          ((uint32_t)0x0007F000)
/// BT_TIA_Q_CAL_BIT_REG field LSB position
#define BT_RF_BT_TIA_Q_CAL_BIT_REG_LSB           12
/// BT_TIA_Q_CAL_BIT_REG field width
#define BT_RF_BT_TIA_Q_CAL_BIT_REG_WIDTH         ((uint32_t)0x00000007)
/// BT_SDM_ADC_CLK_SAR_DIV_2_EN field bit
#define BT_RF_BT_SDM_ADC_CLK_SAR_DIV_2_EN_BIT    ((uint32_t)0x00000800)
/// BT_SDM_ADC_CLK_SAR_DIV_2_EN field position
#define BT_RF_BT_SDM_ADC_CLK_SAR_DIV_2_EN_POS    11
/// BT_SDM_ADC_DITH_EN field bit
#define BT_RF_BT_SDM_ADC_DITH_EN_BIT             ((uint32_t)0x00000400)
/// BT_SDM_ADC_DITH_EN field position
#define BT_RF_BT_SDM_ADC_DITH_EN_POS             10
/// BT_SDM_ADC_VCAL_BIT field mask
#define BT_RF_BT_SDM_ADC_VCAL_BIT_MASK           ((uint32_t)0x000003C0)
/// BT_SDM_ADC_VCAL_BIT field LSB position
#define BT_RF_BT_SDM_ADC_VCAL_BIT_LSB            6
/// BT_SDM_ADC_VCAL_BIT field width
#define BT_RF_BT_SDM_ADC_VCAL_BIT_WIDTH          ((uint32_t)0x00000004)
/// BT_SDM_ADC_CBIT field mask
#define BT_RF_BT_SDM_ADC_CBIT_MASK               ((uint32_t)0x00000038)
/// BT_SDM_ADC_CBIT field LSB position
#define BT_RF_BT_SDM_ADC_CBIT_LSB                3
/// BT_SDM_ADC_CBIT field width
#define BT_RF_BT_SDM_ADC_CBIT_WIDTH              ((uint32_t)0x00000003)
/// BT_SDM_ADC_CAL_EN field bit
#define BT_RF_BT_SDM_ADC_CAL_EN_BIT              ((uint32_t)0x00000004)
/// BT_SDM_ADC_CAL_EN field position
#define BT_RF_BT_SDM_ADC_CAL_EN_POS              2
/// BT_SDM_ADC_GBIT field mask
#define BT_RF_BT_SDM_ADC_GBIT_MASK               ((uint32_t)0x00000003)
/// BT_SDM_ADC_GBIT field LSB position
#define BT_RF_BT_SDM_ADC_GBIT_LSB                0
/// BT_SDM_ADC_GBIT field width
#define BT_RF_BT_SDM_ADC_GBIT_WIDTH              ((uint32_t)0x00000002)

/// BT_TIA_I_CAL_BIT_DR field reset value
#define BT_RF_BT_TIA_I_CAL_BIT_DR_RST            0x0
/// BT_TIA_I_CAL_BIT_REG field reset value
#define BT_RF_BT_TIA_I_CAL_BIT_REG_RST           0x40
/// BT_TIA_Q_CAL_BIT_DR field reset value
#define BT_RF_BT_TIA_Q_CAL_BIT_DR_RST            0x0
/// BT_TIA_Q_CAL_BIT_REG field reset value
#define BT_RF_BT_TIA_Q_CAL_BIT_REG_RST           0x40
/// BT_SDM_ADC_CLK_SAR_DIV_2_EN field reset value
#define BT_RF_BT_SDM_ADC_CLK_SAR_DIV_2_EN_RST    0x1
/// BT_SDM_ADC_DITH_EN field reset value
#define BT_RF_BT_SDM_ADC_DITH_EN_RST             0x1
/// BT_SDM_ADC_VCAL_BIT field reset value
#define BT_RF_BT_SDM_ADC_VCAL_BIT_RST            0x8
/// BT_SDM_ADC_CBIT field reset value
#define BT_RF_BT_SDM_ADC_CBIT_RST                0x3
/// BT_SDM_ADC_CAL_EN field reset value
#define BT_RF_BT_SDM_ADC_CAL_EN_RST              0x1
/// BT_SDM_ADC_GBIT field reset value
#define BT_RF_BT_SDM_ADC_GBIT_RST                0x2

/**
 * @brief Constructs a value for the REG_18 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] bttiaicalbitdr - The value to use for the bt_tia_i_cal_bit_dr field.
 * @param[in] bttiaicalbitreg - The value to use for the bt_tia_i_cal_bit_reg field.
 * @param[in] bttiaqcalbitdr - The value to use for the bt_tia_q_cal_bit_dr field.
 * @param[in] bttiaqcalbitreg - The value to use for the bt_tia_q_cal_bit_reg field.
 * @param[in] btsdmadcclksardiv2en - The value to use for the bt_sdm_adc_clk_sar_div2_en field.
 * @param[in] btsdmadcdithen - The value to use for the bt_sdm_adc_dith_en field.
 * @param[in] btsdmadcvcalbit - The value to use for the bt_sdm_adc_vcal_bit field.
 * @param[in] btsdmadccbit - The value to use for the bt_sdm_adc_cbit field.
 * @param[in] btsdmadccalen - The value to use for the bt_sdm_adc_cal_en field.
 */
__INLINE void bt_rf_reg_18_pack(uint8_t bttiaicalbitdr, uint8_t bttiaicalbitreg, uint8_t bttiaqcalbitdr, uint8_t bttiaqcalbitreg, uint8_t btsdmadcclksardiv2en, uint8_t btsdmadcdithen, uint8_t btsdmadcvcalbit, uint8_t btsdmadccbit, uint8_t btsdmadccalen)
{
    REG_PL_WR(BT_RF_REG_18_ADDR,  ((uint32_t)bttiaicalbitdr << 27) | ((uint32_t)bttiaicalbitreg << 20) | ((uint32_t)bttiaqcalbitdr << 19) | ((uint32_t)bttiaqcalbitreg << 12) | ((uint32_t)btsdmadcclksardiv2en << 11) | ((uint32_t)btsdmadcdithen << 10) | ((uint32_t)btsdmadcvcalbit << 6) | ((uint32_t)btsdmadccbit << 3) | ((uint32_t)btsdmadccalen << 2));
}

/**
 * @brief Unpacks REG_18's fields from current value of the REG_18 register.
 *
 * Reads the REG_18 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] bttiaicalbitdr - Will be populated with the current value of this field from the register.
 * @param[out] bttiaicalbitreg - Will be populated with the current value of this field from the register.
 * @param[out] bttiaqcalbitdr - Will be populated with the current value of this field from the register.
 * @param[out] bttiaqcalbitreg - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcclksardiv2en - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcdithen - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcvcalbit - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadccbit - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadccalen - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcgbit - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_18_unpack(uint8_t* bttiaicalbitdr, uint8_t* bttiaicalbitreg, uint8_t* bttiaqcalbitdr, uint8_t* bttiaqcalbitreg, uint8_t* btsdmadcclksardiv2en, uint8_t* btsdmadcdithen, uint8_t* btsdmadcvcalbit, uint8_t* btsdmadccbit, uint8_t* btsdmadccalen, uint8_t* btsdmadcgbit)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);

    *bttiaicalbitdr = (localVal & ((uint32_t)0x08000000)) >> 27;
    *bttiaicalbitreg = (localVal & ((uint32_t)0x07F00000)) >> 20;
    *bttiaqcalbitdr = (localVal & ((uint32_t)0x00080000)) >> 19;
    *bttiaqcalbitreg = (localVal & ((uint32_t)0x0007F000)) >> 12;
    *btsdmadcclksardiv2en = (localVal & ((uint32_t)0x00000800)) >> 11;
    *btsdmadcdithen = (localVal & ((uint32_t)0x00000400)) >> 10;
    *btsdmadcvcalbit = (localVal & ((uint32_t)0x000003C0)) >> 6;
    *btsdmadccbit = (localVal & ((uint32_t)0x00000038)) >> 3;
    *btsdmadccalen = (localVal & ((uint32_t)0x00000004)) >> 2;
    *btsdmadcgbit = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the bt_tia_i_cal_bit_dr field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_tia_i_cal_bit_dr field's value will be returned.
 *
 * @return The current value of the bt_tia_i_cal_bit_dr field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_tia_i_cal_bit_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the bt_tia_i_cal_bit_dr field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiaicalbitdr - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_i_cal_bit_dr_setf(uint8_t bttiaicalbitdr)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, (REG_PL_RD(BT_RF_REG_18_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)bttiaicalbitdr << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the bt_tia_i_cal_bit_reg field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_tia_i_cal_bit_reg field's value will be returned.
 *
 * @return The current value of the bt_tia_i_cal_bit_reg field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_tia_i_cal_bit_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x07F00000)) >> 20);
}

/**
 * @brief Sets the bt_tia_i_cal_bit_reg field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiaicalbitreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_i_cal_bit_reg_setf(uint8_t bttiaicalbitreg)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, (REG_PL_RD(BT_RF_REG_18_ADDR) & ~((uint32_t)0x07F00000)) | (((uint32_t)bttiaicalbitreg << 20) & ((uint32_t)0x07F00000)));
}

/**
 * @brief Returns the current value of the bt_tia_q_cal_bit_dr field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_tia_q_cal_bit_dr field's value will be returned.
 *
 * @return The current value of the bt_tia_q_cal_bit_dr field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_tia_q_cal_bit_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the bt_tia_q_cal_bit_dr field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiaqcalbitdr - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_q_cal_bit_dr_setf(uint8_t bttiaqcalbitdr)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, (REG_PL_RD(BT_RF_REG_18_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)bttiaqcalbitdr << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the bt_tia_q_cal_bit_reg field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_tia_q_cal_bit_reg field's value will be returned.
 *
 * @return The current value of the bt_tia_q_cal_bit_reg field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_tia_q_cal_bit_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x0007F000)) >> 12);
}

/**
 * @brief Sets the bt_tia_q_cal_bit_reg field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttiaqcalbitreg - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_q_cal_bit_reg_setf(uint8_t bttiaqcalbitreg)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, (REG_PL_RD(BT_RF_REG_18_ADDR) & ~((uint32_t)0x0007F000)) | (((uint32_t)bttiaqcalbitreg << 12) & ((uint32_t)0x0007F000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_clk_sar_div2_en field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_sdm_adc_clk_sar_div2_en field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_clk_sar_div2_en field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_clk_sar_div_2_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the bt_sdm_adc_clk_sar_div2_en field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcclksardiv2en - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_clk_sar_div_2_en_setf(uint8_t btsdmadcclksardiv2en)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, (REG_PL_RD(BT_RF_REG_18_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)btsdmadcclksardiv2en << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_dith_en field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_sdm_adc_dith_en field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_dith_en field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_dith_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the bt_sdm_adc_dith_en field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcdithen - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_dith_en_setf(uint8_t btsdmadcdithen)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, (REG_PL_RD(BT_RF_REG_18_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)btsdmadcdithen << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_vcal_bit field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_sdm_adc_vcal_bit field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_vcal_bit field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_vcal_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x000003C0)) >> 6);
}

/**
 * @brief Sets the bt_sdm_adc_vcal_bit field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcvcalbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_vcal_bit_setf(uint8_t btsdmadcvcalbit)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, (REG_PL_RD(BT_RF_REG_18_ADDR) & ~((uint32_t)0x000003C0)) | (((uint32_t)btsdmadcvcalbit << 6) & ((uint32_t)0x000003C0)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_cbit field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_sdm_adc_cbit field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_cbit field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00000038)) >> 3);
}

/**
 * @brief Sets the bt_sdm_adc_cbit field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadccbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_cbit_setf(uint8_t btsdmadccbit)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, (REG_PL_RD(BT_RF_REG_18_ADDR) & ~((uint32_t)0x00000038)) | (((uint32_t)btsdmadccbit << 3) & ((uint32_t)0x00000038)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_cal_en field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_sdm_adc_cal_en field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_cal_en field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the bt_sdm_adc_cal_en field of the REG_18 register.
 *
 * The REG_18 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadccalen - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_cal_en_setf(uint8_t btsdmadccalen)
{
    REG_PL_WR(BT_RF_REG_18_ADDR, (REG_PL_RD(BT_RF_REG_18_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)btsdmadccalen << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_gbit field in the REG_18 register.
 *
 * The REG_18 register will be read and the bt_sdm_adc_gbit field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_gbit field in the REG_18 register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_18_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/// @}

/**
 * @name REG_1C register definitions
 * <table>
 * <caption id="REG_1C_BF">REG_1C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:24 <td>   bt_sdm_adc_ibit <td>R <td>R/W <td>0xC
 * <tr><td>23:22 <td>bt_sdm_adc_iq_mode <td>W <td>R <td>0x0
 * <tr><td>21 <td>bt_sdm_adc_iq_swap_en <td>R <td>R/W <td>0
 * <tr><td>20:19 <td>bt_sdm_adc_nr_mode <td>W <td>R <td>0x0
 * <tr><td>18 <td>bt_sdm_adc_clk_phsel <td>R <td>R/W <td>0
 * <tr><td>17 <td> bt_sdm_adc_dwa_en <td>R <td>R/W <td>0
 * <tr><td>16:13 <td>bt_sdm_adc_dly_bit <td>R <td>R/W <td>0x0
 * <tr><td>12:11 <td>bt_sdm_adc_sar_insel <td>R <td>R/W <td>0x0
 * <tr><td>10 <td> bt_sdm_adc_sdm_en <td>R <td>R/W <td>1
 * <tr><td>09:08 <td> bt_sdm_adc_sar_en <td>R <td>R/W <td>0x0
 * <tr><td>07 <td>bt_sdm_adc_ana_rstn <td>R <td>R/W <td>0
 * <tr><td>06:05 <td>bt_sdm_adc_dvdd_pwrsw_bit <td>R <td>R/W <td>0x2
 * <tr><td>04:03 <td>bt_sdm_adc_notch_mode <td>W <td>R <td>0x0
 * <tr><td>02:00 <td>bt_dpa_ldo_sink_current_bit <td>R <td>R/W <td>0x4
 * </table>
 *
 * @{
 */

/// Address of the REG_1C register
#define BT_RF_REG_1C_ADDR   0x4062201C
/// Offset of the REG_1C register from the base address
#define BT_RF_REG_1C_OFFSET 0x0000001C
/// Index of the REG_1C register
#define BT_RF_REG_1C_INDEX  0x00000007
/// Reset value of the REG_1C register
#define BT_RF_REG_1C_RESET  0x0C000444

/**
 * @brief Returns the current value of the REG_1C register.
 * The REG_1C register will be read and its value returned.
 * @return The current value of the REG_1C register.
 */
__INLINE uint32_t bt_rf_reg_1c_get(void)
{
    return REG_PL_RD(BT_RF_REG_1C_ADDR);
}

/**
 * @brief Sets the REG_1C register to a value.
 * The REG_1C register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_1c_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, value);
}

// field definitions
/// BT_SDM_ADC_IBIT field mask
#define BT_RF_BT_SDM_ADC_IBIT_MASK               ((uint32_t)0x3F000000)
/// BT_SDM_ADC_IBIT field LSB position
#define BT_RF_BT_SDM_ADC_IBIT_LSB                24
/// BT_SDM_ADC_IBIT field width
#define BT_RF_BT_SDM_ADC_IBIT_WIDTH              ((uint32_t)0x00000006)
/// BT_SDM_ADC_IQ_MODE field mask
#define BT_RF_BT_SDM_ADC_IQ_MODE_MASK            ((uint32_t)0x00C00000)
/// BT_SDM_ADC_IQ_MODE field LSB position
#define BT_RF_BT_SDM_ADC_IQ_MODE_LSB             22
/// BT_SDM_ADC_IQ_MODE field width
#define BT_RF_BT_SDM_ADC_IQ_MODE_WIDTH           ((uint32_t)0x00000002)
/// BT_SDM_ADC_IQ_SWAP_EN field bit
#define BT_RF_BT_SDM_ADC_IQ_SWAP_EN_BIT          ((uint32_t)0x00200000)
/// BT_SDM_ADC_IQ_SWAP_EN field position
#define BT_RF_BT_SDM_ADC_IQ_SWAP_EN_POS          21
/// BT_SDM_ADC_NR_MODE field mask
#define BT_RF_BT_SDM_ADC_NR_MODE_MASK            ((uint32_t)0x00180000)
/// BT_SDM_ADC_NR_MODE field LSB position
#define BT_RF_BT_SDM_ADC_NR_MODE_LSB             19
/// BT_SDM_ADC_NR_MODE field width
#define BT_RF_BT_SDM_ADC_NR_MODE_WIDTH           ((uint32_t)0x00000002)
/// BT_SDM_ADC_CLK_PHSEL field bit
#define BT_RF_BT_SDM_ADC_CLK_PHSEL_BIT           ((uint32_t)0x00040000)
/// BT_SDM_ADC_CLK_PHSEL field position
#define BT_RF_BT_SDM_ADC_CLK_PHSEL_POS           18
/// BT_SDM_ADC_DWA_EN field bit
#define BT_RF_BT_SDM_ADC_DWA_EN_BIT              ((uint32_t)0x00020000)
/// BT_SDM_ADC_DWA_EN field position
#define BT_RF_BT_SDM_ADC_DWA_EN_POS              17
/// BT_SDM_ADC_DLY_BIT field mask
#define BT_RF_BT_SDM_ADC_DLY_BIT_MASK            ((uint32_t)0x0001E000)
/// BT_SDM_ADC_DLY_BIT field LSB position
#define BT_RF_BT_SDM_ADC_DLY_BIT_LSB             13
/// BT_SDM_ADC_DLY_BIT field width
#define BT_RF_BT_SDM_ADC_DLY_BIT_WIDTH           ((uint32_t)0x00000004)
/// BT_SDM_ADC_SAR_INSEL field mask
#define BT_RF_BT_SDM_ADC_SAR_INSEL_MASK          ((uint32_t)0x00001800)
/// BT_SDM_ADC_SAR_INSEL field LSB position
#define BT_RF_BT_SDM_ADC_SAR_INSEL_LSB           11
/// BT_SDM_ADC_SAR_INSEL field width
#define BT_RF_BT_SDM_ADC_SAR_INSEL_WIDTH         ((uint32_t)0x00000002)
/// BT_SDM_ADC_SDM_EN field bit
#define BT_RF_BT_SDM_ADC_SDM_EN_BIT              ((uint32_t)0x00000400)
/// BT_SDM_ADC_SDM_EN field position
#define BT_RF_BT_SDM_ADC_SDM_EN_POS              10
/// BT_SDM_ADC_SAR_EN field mask
#define BT_RF_BT_SDM_ADC_SAR_EN_MASK             ((uint32_t)0x00000300)
/// BT_SDM_ADC_SAR_EN field LSB position
#define BT_RF_BT_SDM_ADC_SAR_EN_LSB              8
/// BT_SDM_ADC_SAR_EN field width
#define BT_RF_BT_SDM_ADC_SAR_EN_WIDTH            ((uint32_t)0x00000002)
/// BT_SDM_ADC_ANA_RSTN field bit
#define BT_RF_BT_SDM_ADC_ANA_RSTN_BIT            ((uint32_t)0x00000080)
/// BT_SDM_ADC_ANA_RSTN field position
#define BT_RF_BT_SDM_ADC_ANA_RSTN_POS            7
/// BT_SDM_ADC_DVDD_PWRSW_BIT field mask
#define BT_RF_BT_SDM_ADC_DVDD_PWRSW_BIT_MASK     ((uint32_t)0x00000060)
/// BT_SDM_ADC_DVDD_PWRSW_BIT field LSB position
#define BT_RF_BT_SDM_ADC_DVDD_PWRSW_BIT_LSB      5
/// BT_SDM_ADC_DVDD_PWRSW_BIT field width
#define BT_RF_BT_SDM_ADC_DVDD_PWRSW_BIT_WIDTH    ((uint32_t)0x00000002)
/// BT_SDM_ADC_NOTCH_MODE field mask
#define BT_RF_BT_SDM_ADC_NOTCH_MODE_MASK         ((uint32_t)0x00000018)
/// BT_SDM_ADC_NOTCH_MODE field LSB position
#define BT_RF_BT_SDM_ADC_NOTCH_MODE_LSB          3
/// BT_SDM_ADC_NOTCH_MODE field width
#define BT_RF_BT_SDM_ADC_NOTCH_MODE_WIDTH        ((uint32_t)0x00000002)
/// BT_DPA_LDO_SINK_CURRENT_BIT field mask
#define BT_RF_BT_DPA_LDO_SINK_CURRENT_BIT_MASK   ((uint32_t)0x00000007)
/// BT_DPA_LDO_SINK_CURRENT_BIT field LSB position
#define BT_RF_BT_DPA_LDO_SINK_CURRENT_BIT_LSB    0
/// BT_DPA_LDO_SINK_CURRENT_BIT field width
#define BT_RF_BT_DPA_LDO_SINK_CURRENT_BIT_WIDTH  ((uint32_t)0x00000003)

/// BT_SDM_ADC_IBIT field reset value
#define BT_RF_BT_SDM_ADC_IBIT_RST                0xC
/// BT_SDM_ADC_IQ_MODE field reset value
#define BT_RF_BT_SDM_ADC_IQ_MODE_RST             0x0
/// BT_SDM_ADC_IQ_SWAP_EN field reset value
#define BT_RF_BT_SDM_ADC_IQ_SWAP_EN_RST          0x0
/// BT_SDM_ADC_NR_MODE field reset value
#define BT_RF_BT_SDM_ADC_NR_MODE_RST             0x0
/// BT_SDM_ADC_CLK_PHSEL field reset value
#define BT_RF_BT_SDM_ADC_CLK_PHSEL_RST           0x0
/// BT_SDM_ADC_DWA_EN field reset value
#define BT_RF_BT_SDM_ADC_DWA_EN_RST              0x0
/// BT_SDM_ADC_DLY_BIT field reset value
#define BT_RF_BT_SDM_ADC_DLY_BIT_RST             0x0
/// BT_SDM_ADC_SAR_INSEL field reset value
#define BT_RF_BT_SDM_ADC_SAR_INSEL_RST           0x0
/// BT_SDM_ADC_SDM_EN field reset value
#define BT_RF_BT_SDM_ADC_SDM_EN_RST              0x1
/// BT_SDM_ADC_SAR_EN field reset value
#define BT_RF_BT_SDM_ADC_SAR_EN_RST              0x0
/// BT_SDM_ADC_ANA_RSTN field reset value
#define BT_RF_BT_SDM_ADC_ANA_RSTN_RST            0x0
/// BT_SDM_ADC_DVDD_PWRSW_BIT field reset value
#define BT_RF_BT_SDM_ADC_DVDD_PWRSW_BIT_RST      0x2
/// BT_SDM_ADC_NOTCH_MODE field reset value
#define BT_RF_BT_SDM_ADC_NOTCH_MODE_RST          0x0
/// BT_DPA_LDO_SINK_CURRENT_BIT field reset value
#define BT_RF_BT_DPA_LDO_SINK_CURRENT_BIT_RST    0x4

/**
 * @brief Constructs a value for the REG_1C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btsdmadcibit - The value to use for the bt_sdm_adc_ibit field.
 * @param[in] btsdmadciqswapen - The value to use for the bt_sdm_adc_iq_swap_en field.
 * @param[in] btsdmadcclkphsel - The value to use for the bt_sdm_adc_clk_phsel field.
 * @param[in] btsdmadcdwaen - The value to use for the bt_sdm_adc_dwa_en field.
 * @param[in] btsdmadcdlybit - The value to use for the bt_sdm_adc_dly_bit field.
 * @param[in] btsdmadcsarinsel - The value to use for the bt_sdm_adc_sar_insel field.
 * @param[in] btsdmadcsdmen - The value to use for the bt_sdm_adc_sdm_en field.
 * @param[in] btsdmadcsaren - The value to use for the bt_sdm_adc_sar_en field.
 * @param[in] btsdmadcanarstn - The value to use for the bt_sdm_adc_ana_rstn field.
 * @param[in] btsdmadcdvddpwrswbit - The value to use for the bt_sdm_adc_dvdd_pwrsw_bit field.
 * @param[in] btdpaldosinkcurrentbit - The value to use for the bt_dpa_ldo_sink_current_bit field.
 */
__INLINE void bt_rf_reg_1c_pack(uint8_t btsdmadcibit, uint8_t btsdmadciqswapen, uint8_t btsdmadcclkphsel, uint8_t btsdmadcdwaen, uint8_t btsdmadcdlybit, uint8_t btsdmadcsarinsel, uint8_t btsdmadcsdmen, uint8_t btsdmadcsaren, uint8_t btsdmadcanarstn, uint8_t btsdmadcdvddpwrswbit, uint8_t btdpaldosinkcurrentbit)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR,  ((uint32_t)btsdmadcibit << 24) | ((uint32_t)btsdmadciqswapen << 21) | ((uint32_t)btsdmadcclkphsel << 18) | ((uint32_t)btsdmadcdwaen << 17) | ((uint32_t)btsdmadcdlybit << 13) | ((uint32_t)btsdmadcsarinsel << 11) | ((uint32_t)btsdmadcsdmen << 10) | ((uint32_t)btsdmadcsaren << 8) | ((uint32_t)btsdmadcanarstn << 7) | ((uint32_t)btsdmadcdvddpwrswbit << 5) | ((uint32_t)btdpaldosinkcurrentbit << 0));
}

/**
 * @brief Unpacks REG_1C's fields from current value of the REG_1C register.
 *
 * Reads the REG_1C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btsdmadcibit - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadciqmode - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadciqswapen - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcnrmode - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcclkphsel - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcdwaen - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcdlybit - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcsarinsel - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcsdmen - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcsaren - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcanarstn - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcdvddpwrswbit - Will be populated with the current value of this field from the register.
 * @param[out] btsdmadcnotchmode - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldosinkcurrentbit - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_1c_unpack(uint8_t* btsdmadcibit, uint8_t* btsdmadciqmode, uint8_t* btsdmadciqswapen, uint8_t* btsdmadcnrmode, uint8_t* btsdmadcclkphsel, uint8_t* btsdmadcdwaen, uint8_t* btsdmadcdlybit, uint8_t* btsdmadcsarinsel, uint8_t* btsdmadcsdmen, uint8_t* btsdmadcsaren, uint8_t* btsdmadcanarstn, uint8_t* btsdmadcdvddpwrswbit, uint8_t* btsdmadcnotchmode, uint8_t* btdpaldosinkcurrentbit)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);

    *btsdmadcibit = (localVal & ((uint32_t)0x3F000000)) >> 24;
    *btsdmadciqmode = (localVal & ((uint32_t)0x00C00000)) >> 22;
    *btsdmadciqswapen = (localVal & ((uint32_t)0x00200000)) >> 21;
    *btsdmadcnrmode = (localVal & ((uint32_t)0x00180000)) >> 19;
    *btsdmadcclkphsel = (localVal & ((uint32_t)0x00040000)) >> 18;
    *btsdmadcdwaen = (localVal & ((uint32_t)0x00020000)) >> 17;
    *btsdmadcdlybit = (localVal & ((uint32_t)0x0001E000)) >> 13;
    *btsdmadcsarinsel = (localVal & ((uint32_t)0x00001800)) >> 11;
    *btsdmadcsdmen = (localVal & ((uint32_t)0x00000400)) >> 10;
    *btsdmadcsaren = (localVal & ((uint32_t)0x00000300)) >> 8;
    *btsdmadcanarstn = (localVal & ((uint32_t)0x00000080)) >> 7;
    *btsdmadcdvddpwrswbit = (localVal & ((uint32_t)0x00000060)) >> 5;
    *btsdmadcnotchmode = (localVal & ((uint32_t)0x00000018)) >> 3;
    *btdpaldosinkcurrentbit = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the bt_sdm_adc_ibit field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_ibit field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_ibit field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x3F000000)) >> 24);
}

/**
 * @brief Sets the bt_sdm_adc_ibit field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcibit - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_ibit_setf(uint8_t btsdmadcibit)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x3F000000)) | (((uint32_t)btsdmadcibit << 24) & ((uint32_t)0x3F000000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_iq_mode field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_iq_mode field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_iq_mode field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_iq_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00C00000)) >> 22);
}

/**
 * @brief Returns the current value of the bt_sdm_adc_iq_swap_en field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_iq_swap_en field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_iq_swap_en field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_iq_swap_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Sets the bt_sdm_adc_iq_swap_en field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadciqswapen - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_iq_swap_en_setf(uint8_t btsdmadciqswapen)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x00200000)) | (((uint32_t)btsdmadciqswapen << 21) & ((uint32_t)0x00200000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_nr_mode field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_nr_mode field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_nr_mode field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_nr_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00180000)) >> 19);
}

/**
 * @brief Returns the current value of the bt_sdm_adc_clk_phsel field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_clk_phsel field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_clk_phsel field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_clk_phsel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the bt_sdm_adc_clk_phsel field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcclkphsel - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_clk_phsel_setf(uint8_t btsdmadcclkphsel)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)btsdmadcclkphsel << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_dwa_en field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_dwa_en field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_dwa_en field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_dwa_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the bt_sdm_adc_dwa_en field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcdwaen - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_dwa_en_setf(uint8_t btsdmadcdwaen)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)btsdmadcdwaen << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_dly_bit field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_dly_bit field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_dly_bit field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x0001E000)) >> 13);
}

/**
 * @brief Sets the bt_sdm_adc_dly_bit field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcdlybit - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_dly_bit_setf(uint8_t btsdmadcdlybit)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x0001E000)) | (((uint32_t)btsdmadcdlybit << 13) & ((uint32_t)0x0001E000)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_sar_insel field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_sar_insel field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_sar_insel field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_sar_insel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00001800)) >> 11);
}

/**
 * @brief Sets the bt_sdm_adc_sar_insel field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcsarinsel - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_sar_insel_setf(uint8_t btsdmadcsarinsel)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x00001800)) | (((uint32_t)btsdmadcsarinsel << 11) & ((uint32_t)0x00001800)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_sdm_en field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_sdm_en field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_sdm_en field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_sdm_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the bt_sdm_adc_sdm_en field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcsdmen - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_sdm_en_setf(uint8_t btsdmadcsdmen)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)btsdmadcsdmen << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_sar_en field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_sar_en field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_sar_en field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_sar_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the bt_sdm_adc_sar_en field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcsaren - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_sar_en_setf(uint8_t btsdmadcsaren)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)btsdmadcsaren << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_ana_rstn field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_ana_rstn field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_ana_rstn field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_ana_rstn_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the bt_sdm_adc_ana_rstn field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcanarstn - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_ana_rstn_setf(uint8_t btsdmadcanarstn)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)btsdmadcanarstn << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_dvdd_pwrsw_bit field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_dvdd_pwrsw_bit field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_dvdd_pwrsw_bit field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_dvdd_pwrsw_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000060)) >> 5);
}

/**
 * @brief Sets the bt_sdm_adc_dvdd_pwrsw_bit field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btsdmadcdvddpwrswbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_sdm_adc_dvdd_pwrsw_bit_setf(uint8_t btsdmadcdvddpwrswbit)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x00000060)) | (((uint32_t)btsdmadcdvddpwrswbit << 5) & ((uint32_t)0x00000060)));
}

/**
 * @brief Returns the current value of the bt_sdm_adc_notch_mode field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_sdm_adc_notch_mode field's value will be returned.
 *
 * @return The current value of the bt_sdm_adc_notch_mode field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_sdm_adc_notch_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000018)) >> 3);
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_sink_current_bit field in the REG_1C register.
 *
 * The REG_1C register will be read and the bt_dpa_ldo_sink_current_bit field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_sink_current_bit field in the REG_1C register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_sink_current_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_1C_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/**
 * @brief Sets the bt_dpa_ldo_sink_current_bit field of the REG_1C register.
 *
 * The REG_1C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldosinkcurrentbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_sink_current_bit_setf(uint8_t btdpaldosinkcurrentbit)
{
    REG_PL_WR(BT_RF_REG_1C_ADDR, (REG_PL_RD(BT_RF_REG_1C_ADDR) & ~((uint32_t)0x00000007)) | (((uint32_t)btdpaldosinkcurrentbit << 0) & ((uint32_t)0x00000007)));
}

/// @}

/**
 * @name REG_20 register definitions
 * <table>
 * <caption id="REG_20_BF">REG_20 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>28:26 <td>   bt_dpa_ldo_ibit <td>R <td>R/W <td>0x3
 * <tr><td>25:24 <td>   bt_dpa_ldo_rbit <td>R <td>R/W <td>0x3
 * <tr><td>23 <td>bt_dpa_ldo_sink_current_en <td>R <td>R/W <td>1
 * <tr><td>22 <td>bt_dpa_ldo_current_limit_en <td>R <td>R/W <td>0
 * <tr><td>21:19 <td>bt_dpa_ldo_current_limit_bit <td>R <td>R/W <td>0x4
 * <tr><td>18:15 <td>  bt_dpa_ldo_rbit1 <td>R <td>R/W <td>0x8
 * <tr><td>14:07 <td>bt_dpa_ldo_rdac_data_in_rx <td>R <td>R/W <td>0x70
 * <tr><td>06 <td>bt_dpa_ldo_vref_cal_en <td>R <td>R/W <td>0
 * <tr><td>05 <td>bt_dpa_ldo_vref_sel <td>R <td>R/W <td>0
 * <tr><td>04 <td>  bt_dpa_ldo_pull0 <td>R <td>R/W <td>0
 * <tr><td>03 <td>bt_dpa_ldo_bypass_rx <td>R <td>R/W <td>0
 * <tr><td>02 <td>   bt_dpa_div_mode <td>W <td>R <td>0
 * <tr><td>01 <td>bt_dpa_drv_pwr_sel <td>R <td>R/W <td>0
 * <tr><td>00 <td> bt_dpa_reg_bypass <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_20 register
#define BT_RF_REG_20_ADDR   0x40622020
/// Offset of the REG_20 register from the base address
#define BT_RF_REG_20_OFFSET 0x00000020
/// Index of the REG_20 register
#define BT_RF_REG_20_INDEX  0x00000008
/// Reset value of the REG_20 register
#define BT_RF_REG_20_RESET  0x0FA43800

/**
 * @brief Returns the current value of the REG_20 register.
 * The REG_20 register will be read and its value returned.
 * @return The current value of the REG_20 register.
 */
__INLINE uint32_t bt_rf_reg_20_get(void)
{
    return REG_PL_RD(BT_RF_REG_20_ADDR);
}

/**
 * @brief Sets the REG_20 register to a value.
 * The REG_20 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_20_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, value);
}

// field definitions
/// BT_DPA_LDO_IBIT field mask
#define BT_RF_BT_DPA_LDO_IBIT_MASK                ((uint32_t)0x1C000000)
/// BT_DPA_LDO_IBIT field LSB position
#define BT_RF_BT_DPA_LDO_IBIT_LSB                 26
/// BT_DPA_LDO_IBIT field width
#define BT_RF_BT_DPA_LDO_IBIT_WIDTH               ((uint32_t)0x00000003)
/// BT_DPA_LDO_RBIT field mask
#define BT_RF_BT_DPA_LDO_RBIT_MASK                ((uint32_t)0x03000000)
/// BT_DPA_LDO_RBIT field LSB position
#define BT_RF_BT_DPA_LDO_RBIT_LSB                 24
/// BT_DPA_LDO_RBIT field width
#define BT_RF_BT_DPA_LDO_RBIT_WIDTH               ((uint32_t)0x00000002)
/// BT_DPA_LDO_SINK_CURRENT_EN field bit
#define BT_RF_BT_DPA_LDO_SINK_CURRENT_EN_BIT      ((uint32_t)0x00800000)
/// BT_DPA_LDO_SINK_CURRENT_EN field position
#define BT_RF_BT_DPA_LDO_SINK_CURRENT_EN_POS      23
/// BT_DPA_LDO_CURRENT_LIMIT_EN field bit
#define BT_RF_BT_DPA_LDO_CURRENT_LIMIT_EN_BIT     ((uint32_t)0x00400000)
/// BT_DPA_LDO_CURRENT_LIMIT_EN field position
#define BT_RF_BT_DPA_LDO_CURRENT_LIMIT_EN_POS     22
/// BT_DPA_LDO_CURRENT_LIMIT_BIT field mask
#define BT_RF_BT_DPA_LDO_CURRENT_LIMIT_BIT_MASK   ((uint32_t)0x00380000)
/// BT_DPA_LDO_CURRENT_LIMIT_BIT field LSB position
#define BT_RF_BT_DPA_LDO_CURRENT_LIMIT_BIT_LSB    19
/// BT_DPA_LDO_CURRENT_LIMIT_BIT field width
#define BT_RF_BT_DPA_LDO_CURRENT_LIMIT_BIT_WIDTH  ((uint32_t)0x00000003)
/// BT_DPA_LDO_RBIT_1 field mask
#define BT_RF_BT_DPA_LDO_RBIT_1_MASK              ((uint32_t)0x00078000)
/// BT_DPA_LDO_RBIT_1 field LSB position
#define BT_RF_BT_DPA_LDO_RBIT_1_LSB               15
/// BT_DPA_LDO_RBIT_1 field width
#define BT_RF_BT_DPA_LDO_RBIT_1_WIDTH             ((uint32_t)0x00000004)
/// BT_DPA_LDO_RDAC_DATA_IN_RX field mask
#define BT_RF_BT_DPA_LDO_RDAC_DATA_IN_RX_MASK     ((uint32_t)0x00007F80)
/// BT_DPA_LDO_RDAC_DATA_IN_RX field LSB position
#define BT_RF_BT_DPA_LDO_RDAC_DATA_IN_RX_LSB      7
/// BT_DPA_LDO_RDAC_DATA_IN_RX field width
#define BT_RF_BT_DPA_LDO_RDAC_DATA_IN_RX_WIDTH    ((uint32_t)0x00000008)
/// BT_DPA_LDO_VREF_CAL_EN field bit
#define BT_RF_BT_DPA_LDO_VREF_CAL_EN_BIT          ((uint32_t)0x00000040)
/// BT_DPA_LDO_VREF_CAL_EN field position
#define BT_RF_BT_DPA_LDO_VREF_CAL_EN_POS          6
/// BT_DPA_LDO_VREF_SEL field bit
#define BT_RF_BT_DPA_LDO_VREF_SEL_BIT             ((uint32_t)0x00000020)
/// BT_DPA_LDO_VREF_SEL field position
#define BT_RF_BT_DPA_LDO_VREF_SEL_POS             5
/// BT_DPA_LDO_PULL_0 field bit
#define BT_RF_BT_DPA_LDO_PULL_0_BIT               ((uint32_t)0x00000010)
/// BT_DPA_LDO_PULL_0 field position
#define BT_RF_BT_DPA_LDO_PULL_0_POS               4
/// BT_DPA_LDO_BYPASS_RX field bit
#define BT_RF_BT_DPA_LDO_BYPASS_RX_BIT            ((uint32_t)0x00000008)
/// BT_DPA_LDO_BYPASS_RX field position
#define BT_RF_BT_DPA_LDO_BYPASS_RX_POS            3
/// BT_DPA_DIV_MODE field bit
#define BT_RF_BT_DPA_DIV_MODE_BIT                 ((uint32_t)0x00000004)
/// BT_DPA_DIV_MODE field position
#define BT_RF_BT_DPA_DIV_MODE_POS                 2
/// BT_DPA_DRV_PWR_SEL field bit
#define BT_RF_BT_DPA_DRV_PWR_SEL_BIT              ((uint32_t)0x00000002)
/// BT_DPA_DRV_PWR_SEL field position
#define BT_RF_BT_DPA_DRV_PWR_SEL_POS              1
/// BT_DPA_REG_BYPASS field bit
#define BT_RF_BT_DPA_REG_BYPASS_BIT               ((uint32_t)0x00000001)
/// BT_DPA_REG_BYPASS field position
#define BT_RF_BT_DPA_REG_BYPASS_POS               0

/// BT_DPA_LDO_IBIT field reset value
#define BT_RF_BT_DPA_LDO_IBIT_RST                 0x3
/// BT_DPA_LDO_RBIT field reset value
#define BT_RF_BT_DPA_LDO_RBIT_RST                 0x3
/// BT_DPA_LDO_SINK_CURRENT_EN field reset value
#define BT_RF_BT_DPA_LDO_SINK_CURRENT_EN_RST      0x1
/// BT_DPA_LDO_CURRENT_LIMIT_EN field reset value
#define BT_RF_BT_DPA_LDO_CURRENT_LIMIT_EN_RST     0x0
/// BT_DPA_LDO_CURRENT_LIMIT_BIT field reset value
#define BT_RF_BT_DPA_LDO_CURRENT_LIMIT_BIT_RST    0x4
/// BT_DPA_LDO_RBIT_1 field reset value
#define BT_RF_BT_DPA_LDO_RBIT_1_RST               0x8
/// BT_DPA_LDO_RDAC_DATA_IN_RX field reset value
#define BT_RF_BT_DPA_LDO_RDAC_DATA_IN_RX_RST      0x70
/// BT_DPA_LDO_VREF_CAL_EN field reset value
#define BT_RF_BT_DPA_LDO_VREF_CAL_EN_RST          0x0
/// BT_DPA_LDO_VREF_SEL field reset value
#define BT_RF_BT_DPA_LDO_VREF_SEL_RST             0x0
/// BT_DPA_LDO_PULL_0 field reset value
#define BT_RF_BT_DPA_LDO_PULL_0_RST               0x0
/// BT_DPA_LDO_BYPASS_RX field reset value
#define BT_RF_BT_DPA_LDO_BYPASS_RX_RST            0x0
/// BT_DPA_DIV_MODE field reset value
#define BT_RF_BT_DPA_DIV_MODE_RST                 0x0
/// BT_DPA_DRV_PWR_SEL field reset value
#define BT_RF_BT_DPA_DRV_PWR_SEL_RST              0x0
/// BT_DPA_REG_BYPASS field reset value
#define BT_RF_BT_DPA_REG_BYPASS_RST               0x0

/**
 * @brief Constructs a value for the REG_20 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btdpaldoibit - The value to use for the bt_dpa_ldo_ibit field.
 * @param[in] btdpaldorbit - The value to use for the bt_dpa_ldo_rbit field.
 * @param[in] btdpaldosinkcurrenten - The value to use for the bt_dpa_ldo_sink_current_en field.
 * @param[in] btdpaldocurrentlimiten - The value to use for the bt_dpa_ldo_current_limit_en field.
 * @param[in] btdpaldocurrentlimitbit - The value to use for the bt_dpa_ldo_current_limit_bit field.
 * @param[in] btdpaldorbit1 - The value to use for the bt_dpa_ldo_rbit1 field.
 * @param[in] btdpaldordacdatainrx - The value to use for the bt_dpa_ldo_rdac_data_in_rx field.
 * @param[in] btdpaldovrefcalen - The value to use for the bt_dpa_ldo_vref_cal_en field.
 * @param[in] btdpaldovrefsel - The value to use for the bt_dpa_ldo_vref_sel field.
 * @param[in] btdpaldopull0 - The value to use for the bt_dpa_ldo_pull0 field.
 * @param[in] btdpaldobypassrx - The value to use for the bt_dpa_ldo_bypass_rx field.
 * @param[in] btdpadrvpwrsel - The value to use for the bt_dpa_drv_pwr_sel field.
 * @param[in] btdparegbypass - The value to use for the bt_dpa_reg_bypass field.
 */
__INLINE void bt_rf_reg_20_pack(uint8_t btdpaldoibit, uint8_t btdpaldorbit, uint8_t btdpaldosinkcurrenten, uint8_t btdpaldocurrentlimiten, uint8_t btdpaldocurrentlimitbit, uint8_t btdpaldorbit1, uint8_t btdpaldordacdatainrx, uint8_t btdpaldovrefcalen, uint8_t btdpaldovrefsel, uint8_t btdpaldopull0, uint8_t btdpaldobypassrx, uint8_t btdpadrvpwrsel, uint8_t btdparegbypass)
{
    REG_PL_WR(BT_RF_REG_20_ADDR,  ((uint32_t)btdpaldoibit << 26) | ((uint32_t)btdpaldorbit << 24) | ((uint32_t)btdpaldosinkcurrenten << 23) | ((uint32_t)btdpaldocurrentlimiten << 22) | ((uint32_t)btdpaldocurrentlimitbit << 19) | ((uint32_t)btdpaldorbit1 << 15) | ((uint32_t)btdpaldordacdatainrx << 7) | ((uint32_t)btdpaldovrefcalen << 6) | ((uint32_t)btdpaldovrefsel << 5) | ((uint32_t)btdpaldopull0 << 4) | ((uint32_t)btdpaldobypassrx << 3) | ((uint32_t)btdpadrvpwrsel << 1) | ((uint32_t)btdparegbypass << 0));
}

/**
 * @brief Unpacks REG_20's fields from current value of the REG_20 register.
 *
 * Reads the REG_20 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btdpaldoibit - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldorbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldosinkcurrenten - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldocurrentlimiten - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldocurrentlimitbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldorbit1 - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldordacdatainrx - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldovrefcalen - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldovrefsel - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldopull0 - Will be populated with the current value of this field from the register.
 * @param[out] btdpaldobypassrx - Will be populated with the current value of this field from the register.
 * @param[out] btdpadivmode - Will be populated with the current value of this field from the register.
 * @param[out] btdpadrvpwrsel - Will be populated with the current value of this field from the register.
 * @param[out] btdparegbypass - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_20_unpack(uint8_t* btdpaldoibit, uint8_t* btdpaldorbit, uint8_t* btdpaldosinkcurrenten, uint8_t* btdpaldocurrentlimiten, uint8_t* btdpaldocurrentlimitbit, uint8_t* btdpaldorbit1, uint8_t* btdpaldordacdatainrx, uint8_t* btdpaldovrefcalen, uint8_t* btdpaldovrefsel, uint8_t* btdpaldopull0, uint8_t* btdpaldobypassrx, uint8_t* btdpadivmode, uint8_t* btdpadrvpwrsel, uint8_t* btdparegbypass)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);

    *btdpaldoibit = (localVal & ((uint32_t)0x1C000000)) >> 26;
    *btdpaldorbit = (localVal & ((uint32_t)0x03000000)) >> 24;
    *btdpaldosinkcurrenten = (localVal & ((uint32_t)0x00800000)) >> 23;
    *btdpaldocurrentlimiten = (localVal & ((uint32_t)0x00400000)) >> 22;
    *btdpaldocurrentlimitbit = (localVal & ((uint32_t)0x00380000)) >> 19;
    *btdpaldorbit1 = (localVal & ((uint32_t)0x00078000)) >> 15;
    *btdpaldordacdatainrx = (localVal & ((uint32_t)0x00007F80)) >> 7;
    *btdpaldovrefcalen = (localVal & ((uint32_t)0x00000040)) >> 6;
    *btdpaldovrefsel = (localVal & ((uint32_t)0x00000020)) >> 5;
    *btdpaldopull0 = (localVal & ((uint32_t)0x00000010)) >> 4;
    *btdpaldobypassrx = (localVal & ((uint32_t)0x00000008)) >> 3;
    *btdpadivmode = (localVal & ((uint32_t)0x00000004)) >> 2;
    *btdpadrvpwrsel = (localVal & ((uint32_t)0x00000002)) >> 1;
    *btdparegbypass = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_ibit field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_ibit field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_ibit field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x1C000000)) >> 26);
}

/**
 * @brief Sets the bt_dpa_ldo_ibit field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldoibit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_ibit_setf(uint8_t btdpaldoibit)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x1C000000)) | (((uint32_t)btdpaldoibit << 26) & ((uint32_t)0x1C000000)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_rbit field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_rbit field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_rbit field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

/**
 * @brief Sets the bt_dpa_ldo_rbit field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldorbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_rbit_setf(uint8_t btdpaldorbit)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x03000000)) | (((uint32_t)btdpaldorbit << 24) & ((uint32_t)0x03000000)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_sink_current_en field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_sink_current_en field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_sink_current_en field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_sink_current_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the bt_dpa_ldo_sink_current_en field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldosinkcurrenten - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_sink_current_en_setf(uint8_t btdpaldosinkcurrenten)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)btdpaldosinkcurrenten << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_current_limit_en field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_current_limit_en field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_current_limit_en field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_current_limit_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the bt_dpa_ldo_current_limit_en field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldocurrentlimiten - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_current_limit_en_setf(uint8_t btdpaldocurrentlimiten)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)btdpaldocurrentlimiten << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_current_limit_bit field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_current_limit_bit field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_current_limit_bit field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_current_limit_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00380000)) >> 19);
}

/**
 * @brief Sets the bt_dpa_ldo_current_limit_bit field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldocurrentlimitbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_current_limit_bit_setf(uint8_t btdpaldocurrentlimitbit)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00380000)) | (((uint32_t)btdpaldocurrentlimitbit << 19) & ((uint32_t)0x00380000)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_rbit1 field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_rbit1 field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_rbit1 field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_rbit_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00078000)) >> 15);
}

/**
 * @brief Sets the bt_dpa_ldo_rbit1 field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldorbit1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_rbit_1_setf(uint8_t btdpaldorbit1)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00078000)) | (((uint32_t)btdpaldorbit1 << 15) & ((uint32_t)0x00078000)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_rdac_data_in_rx field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_rdac_data_in_rx field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_rdac_data_in_rx field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_rdac_data_in_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00007F80)) >> 7);
}

/**
 * @brief Sets the bt_dpa_ldo_rdac_data_in_rx field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldordacdatainrx - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_rdac_data_in_rx_setf(uint8_t btdpaldordacdatainrx)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00007F80)) | (((uint32_t)btdpaldordacdatainrx << 7) & ((uint32_t)0x00007F80)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_vref_cal_en field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_vref_cal_en field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_vref_cal_en field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_vref_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the bt_dpa_ldo_vref_cal_en field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldovrefcalen - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_vref_cal_en_setf(uint8_t btdpaldovrefcalen)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)btdpaldovrefcalen << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_vref_sel field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_vref_sel field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_vref_sel field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_vref_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the bt_dpa_ldo_vref_sel field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldovrefsel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_vref_sel_setf(uint8_t btdpaldovrefsel)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)btdpaldovrefsel << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_pull0 field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_pull0 field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_pull0 field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_pull_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the bt_dpa_ldo_pull0 field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldopull0 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_pull_0_setf(uint8_t btdpaldopull0)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)btdpaldopull0 << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the bt_dpa_ldo_bypass_rx field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_ldo_bypass_rx field's value will be returned.
 *
 * @return The current value of the bt_dpa_ldo_bypass_rx field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ldo_bypass_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the bt_dpa_ldo_bypass_rx field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaldobypassrx - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ldo_bypass_rx_setf(uint8_t btdpaldobypassrx)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)btdpaldobypassrx << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the bt_dpa_div_mode field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_div_mode field's value will be returned.
 *
 * @return The current value of the bt_dpa_div_mode field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_div_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Returns the current value of the bt_dpa_drv_pwr_sel field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_drv_pwr_sel field's value will be returned.
 *
 * @return The current value of the bt_dpa_drv_pwr_sel field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_drv_pwr_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the bt_dpa_drv_pwr_sel field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpadrvpwrsel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_drv_pwr_sel_setf(uint8_t btdpadrvpwrsel)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)btdpadrvpwrsel << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the bt_dpa_reg_bypass field in the REG_20 register.
 *
 * The REG_20 register will be read and the bt_dpa_reg_bypass field's value will be returned.
 *
 * @return The current value of the bt_dpa_reg_bypass field in the REG_20 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_reg_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_20_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the bt_dpa_reg_bypass field of the REG_20 register.
 *
 * The REG_20 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdparegbypass - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_reg_bypass_setf(uint8_t btdparegbypass)
{
    REG_PL_WR(BT_RF_REG_20_ADDR, (REG_PL_RD(BT_RF_REG_20_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)btdparegbypass << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_24 register definitions
 * <table>
 * <caption id="REG_24_BF">REG_24 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30:27 <td>   bt_dpa_reg_vbit <td>R <td>R/W <td>0x8
 * <tr><td>26 <td>bt_dpa_clk_edge_sel <td>R <td>R/W <td>1
 * <tr><td>25 <td> bt_dpa_retime_sel <td>R <td>R/W <td>0
 * <tr><td>24 <td>  bt_dpa_1p2g_mode <td>R <td>R/W <td>0
 * <tr><td>23 <td>    bt_dpa_sinc_en <td>R <td>R/W <td>1
 * <tr><td>22:21 <td>bt_dpa_sign_dly_sel <td>R <td>R/W <td>0x1
 * <tr><td>20 <td>   bt_dpa_mode_sel <td>R <td>R/W <td>0
 * <tr><td>19:16 <td>  bt_dpa_slice_enp <td>R <td>R/W <td>0xF
 * <tr><td>15:12 <td>  bt_dpa_slice_enn <td>R <td>R/W <td>0xF
 * <tr><td>11:09 <td>bt_dpa_capbank_bit <td>R <td>R/W <td>0x0
 * <tr><td>08 <td>bt_dpa_pm_edge_sel <td>R <td>R/W <td>0
 * <tr><td>07:04 <td> bt_trx_cap_sw_bit <td>W <td>R <td>0x0
 * <tr><td>03:01 <td>   bt_dpa_ant_cbit <td>R <td>R/W <td>0x0
 * <tr><td>00 <td>bt_dpa_auto_pm_sync <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_24 register
#define BT_RF_REG_24_ADDR   0x40622024
/// Offset of the REG_24 register from the base address
#define BT_RF_REG_24_OFFSET 0x00000024
/// Index of the REG_24 register
#define BT_RF_REG_24_INDEX  0x00000009
/// Reset value of the REG_24 register
#define BT_RF_REG_24_RESET  0x44AFF001

/**
 * @brief Returns the current value of the REG_24 register.
 * The REG_24 register will be read and its value returned.
 * @return The current value of the REG_24 register.
 */
__INLINE uint32_t bt_rf_reg_24_get(void)
{
    return REG_PL_RD(BT_RF_REG_24_ADDR);
}

/**
 * @brief Sets the REG_24 register to a value.
 * The REG_24 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_24_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, value);
}

// field definitions
/// BT_DPA_REG_VBIT field mask
#define BT_RF_BT_DPA_REG_VBIT_MASK       ((uint32_t)0x78000000)
/// BT_DPA_REG_VBIT field LSB position
#define BT_RF_BT_DPA_REG_VBIT_LSB        27
/// BT_DPA_REG_VBIT field width
#define BT_RF_BT_DPA_REG_VBIT_WIDTH      ((uint32_t)0x00000004)
/// BT_DPA_CLK_EDGE_SEL field bit
#define BT_RF_BT_DPA_CLK_EDGE_SEL_BIT    ((uint32_t)0x04000000)
/// BT_DPA_CLK_EDGE_SEL field position
#define BT_RF_BT_DPA_CLK_EDGE_SEL_POS    26
/// BT_DPA_RETIME_SEL field bit
#define BT_RF_BT_DPA_RETIME_SEL_BIT      ((uint32_t)0x02000000)
/// BT_DPA_RETIME_SEL field position
#define BT_RF_BT_DPA_RETIME_SEL_POS      25
/// BT_DPA__1P_2G_MODE field bit
#define BT_RF_BT_DPA__1P_2G_MODE_BIT     ((uint32_t)0x01000000)
/// BT_DPA__1P_2G_MODE field position
#define BT_RF_BT_DPA__1P_2G_MODE_POS     24
/// BT_DPA_SINC_EN field bit
#define BT_RF_BT_DPA_SINC_EN_BIT         ((uint32_t)0x00800000)
/// BT_DPA_SINC_EN field position
#define BT_RF_BT_DPA_SINC_EN_POS         23
/// BT_DPA_SIGN_DLY_SEL field mask
#define BT_RF_BT_DPA_SIGN_DLY_SEL_MASK   ((uint32_t)0x00600000)
/// BT_DPA_SIGN_DLY_SEL field LSB position
#define BT_RF_BT_DPA_SIGN_DLY_SEL_LSB    21
/// BT_DPA_SIGN_DLY_SEL field width
#define BT_RF_BT_DPA_SIGN_DLY_SEL_WIDTH  ((uint32_t)0x00000002)
/// BT_DPA_MODE_SEL field bit
#define BT_RF_BT_DPA_MODE_SEL_BIT        ((uint32_t)0x00100000)
/// BT_DPA_MODE_SEL field position
#define BT_RF_BT_DPA_MODE_SEL_POS        20
/// BT_DPA_SLICE_ENP field mask
#define BT_RF_BT_DPA_SLICE_ENP_MASK      ((uint32_t)0x000F0000)
/// BT_DPA_SLICE_ENP field LSB position
#define BT_RF_BT_DPA_SLICE_ENP_LSB       16
/// BT_DPA_SLICE_ENP field width
#define BT_RF_BT_DPA_SLICE_ENP_WIDTH     ((uint32_t)0x00000004)
/// BT_DPA_SLICE_ENN field mask
#define BT_RF_BT_DPA_SLICE_ENN_MASK      ((uint32_t)0x0000F000)
/// BT_DPA_SLICE_ENN field LSB position
#define BT_RF_BT_DPA_SLICE_ENN_LSB       12
/// BT_DPA_SLICE_ENN field width
#define BT_RF_BT_DPA_SLICE_ENN_WIDTH     ((uint32_t)0x00000004)
/// BT_DPA_CAPBANK_BIT field mask
#define BT_RF_BT_DPA_CAPBANK_BIT_MASK    ((uint32_t)0x00000E00)
/// BT_DPA_CAPBANK_BIT field LSB position
#define BT_RF_BT_DPA_CAPBANK_BIT_LSB     9
/// BT_DPA_CAPBANK_BIT field width
#define BT_RF_BT_DPA_CAPBANK_BIT_WIDTH   ((uint32_t)0x00000003)
/// BT_DPA_PM_EDGE_SEL field bit
#define BT_RF_BT_DPA_PM_EDGE_SEL_BIT     ((uint32_t)0x00000100)
/// BT_DPA_PM_EDGE_SEL field position
#define BT_RF_BT_DPA_PM_EDGE_SEL_POS     8
/// BT_TRX_CAP_SW_BIT field mask
#define BT_RF_BT_TRX_CAP_SW_BIT_MASK     ((uint32_t)0x000000F0)
/// BT_TRX_CAP_SW_BIT field LSB position
#define BT_RF_BT_TRX_CAP_SW_BIT_LSB      4
/// BT_TRX_CAP_SW_BIT field width
#define BT_RF_BT_TRX_CAP_SW_BIT_WIDTH    ((uint32_t)0x00000004)
/// BT_DPA_ANT_CBIT field mask
#define BT_RF_BT_DPA_ANT_CBIT_MASK       ((uint32_t)0x0000000E)
/// BT_DPA_ANT_CBIT field LSB position
#define BT_RF_BT_DPA_ANT_CBIT_LSB        1
/// BT_DPA_ANT_CBIT field width
#define BT_RF_BT_DPA_ANT_CBIT_WIDTH      ((uint32_t)0x00000003)
/// BT_DPA_AUTO_PM_SYNC field bit
#define BT_RF_BT_DPA_AUTO_PM_SYNC_BIT    ((uint32_t)0x00000001)
/// BT_DPA_AUTO_PM_SYNC field position
#define BT_RF_BT_DPA_AUTO_PM_SYNC_POS    0

/// BT_DPA_REG_VBIT field reset value
#define BT_RF_BT_DPA_REG_VBIT_RST        0x8
/// BT_DPA_CLK_EDGE_SEL field reset value
#define BT_RF_BT_DPA_CLK_EDGE_SEL_RST    0x1
/// BT_DPA_RETIME_SEL field reset value
#define BT_RF_BT_DPA_RETIME_SEL_RST      0x0
/// BT_DPA__1P_2G_MODE field reset value
#define BT_RF_BT_DPA__1P_2G_MODE_RST     0x0
/// BT_DPA_SINC_EN field reset value
#define BT_RF_BT_DPA_SINC_EN_RST         0x1
/// BT_DPA_SIGN_DLY_SEL field reset value
#define BT_RF_BT_DPA_SIGN_DLY_SEL_RST    0x1
/// BT_DPA_MODE_SEL field reset value
#define BT_RF_BT_DPA_MODE_SEL_RST        0x0
/// BT_DPA_SLICE_ENP field reset value
#define BT_RF_BT_DPA_SLICE_ENP_RST       0xF
/// BT_DPA_SLICE_ENN field reset value
#define BT_RF_BT_DPA_SLICE_ENN_RST       0xF
/// BT_DPA_CAPBANK_BIT field reset value
#define BT_RF_BT_DPA_CAPBANK_BIT_RST     0x0
/// BT_DPA_PM_EDGE_SEL field reset value
#define BT_RF_BT_DPA_PM_EDGE_SEL_RST     0x0
/// BT_TRX_CAP_SW_BIT field reset value
#define BT_RF_BT_TRX_CAP_SW_BIT_RST      0x0
/// BT_DPA_ANT_CBIT field reset value
#define BT_RF_BT_DPA_ANT_CBIT_RST        0x0
/// BT_DPA_AUTO_PM_SYNC field reset value
#define BT_RF_BT_DPA_AUTO_PM_SYNC_RST    0x1

/**
 * @brief Constructs a value for the REG_24 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btdparegvbit - The value to use for the bt_dpa_reg_vbit field.
 * @param[in] btdpaclkedgesel - The value to use for the bt_dpa_clk_edge_sel field.
 * @param[in] btdparetimesel - The value to use for the bt_dpa_retime_sel field.
 * @param[in] btdpa1p2gmode - The value to use for the bt_dpa_1p2g_mode field.
 * @param[in] btdpasincen - The value to use for the bt_dpa_sinc_en field.
 * @param[in] btdpasigndlysel - The value to use for the bt_dpa_sign_dly_sel field.
 * @param[in] btdpamodesel - The value to use for the bt_dpa_mode_sel field.
 * @param[in] btdpasliceenp - The value to use for the bt_dpa_slice_enp field.
 * @param[in] btdpasliceenn - The value to use for the bt_dpa_slice_enn field.
 * @param[in] btdpacapbankbit - The value to use for the bt_dpa_capbank_bit field.
 * @param[in] btdpapmedgesel - The value to use for the bt_dpa_pm_edge_sel field.
 * @param[in] btdpaantcbit - The value to use for the bt_dpa_ant_cbit field.
 * @param[in] btdpaautopmsync - The value to use for the bt_dpa_auto_pm_sync field.
 */
__INLINE void bt_rf_reg_24_pack(uint8_t btdparegvbit, uint8_t btdpaclkedgesel, uint8_t btdparetimesel, uint8_t btdpa1p2gmode, uint8_t btdpasincen, uint8_t btdpasigndlysel, uint8_t btdpamodesel, uint8_t btdpasliceenp, uint8_t btdpasliceenn, uint8_t btdpacapbankbit, uint8_t btdpapmedgesel, uint8_t btdpaantcbit, uint8_t btdpaautopmsync)
{
    REG_PL_WR(BT_RF_REG_24_ADDR,  ((uint32_t)btdparegvbit << 27) | ((uint32_t)btdpaclkedgesel << 26) | ((uint32_t)btdparetimesel << 25) | ((uint32_t)btdpa1p2gmode << 24) | ((uint32_t)btdpasincen << 23) | ((uint32_t)btdpasigndlysel << 21) | ((uint32_t)btdpamodesel << 20) | ((uint32_t)btdpasliceenp << 16) | ((uint32_t)btdpasliceenn << 12) | ((uint32_t)btdpacapbankbit << 9) | ((uint32_t)btdpapmedgesel << 8) | ((uint32_t)btdpaantcbit << 1) | ((uint32_t)btdpaautopmsync << 0));
}

/**
 * @brief Unpacks REG_24's fields from current value of the REG_24 register.
 *
 * Reads the REG_24 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btdparegvbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpaclkedgesel - Will be populated with the current value of this field from the register.
 * @param[out] btdparetimesel - Will be populated with the current value of this field from the register.
 * @param[out] btdpa1p2gmode - Will be populated with the current value of this field from the register.
 * @param[out] btdpasincen - Will be populated with the current value of this field from the register.
 * @param[out] btdpasigndlysel - Will be populated with the current value of this field from the register.
 * @param[out] btdpamodesel - Will be populated with the current value of this field from the register.
 * @param[out] btdpasliceenp - Will be populated with the current value of this field from the register.
 * @param[out] btdpasliceenn - Will be populated with the current value of this field from the register.
 * @param[out] btdpacapbankbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpapmedgesel - Will be populated with the current value of this field from the register.
 * @param[out] bttrxcapswbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpaantcbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpaautopmsync - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_24_unpack(uint8_t* btdparegvbit, uint8_t* btdpaclkedgesel, uint8_t* btdparetimesel, uint8_t* btdpa1p2gmode, uint8_t* btdpasincen, uint8_t* btdpasigndlysel, uint8_t* btdpamodesel, uint8_t* btdpasliceenp, uint8_t* btdpasliceenn, uint8_t* btdpacapbankbit, uint8_t* btdpapmedgesel, uint8_t* bttrxcapswbit, uint8_t* btdpaantcbit, uint8_t* btdpaautopmsync)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);

    *btdparegvbit = (localVal & ((uint32_t)0x78000000)) >> 27;
    *btdpaclkedgesel = (localVal & ((uint32_t)0x04000000)) >> 26;
    *btdparetimesel = (localVal & ((uint32_t)0x02000000)) >> 25;
    *btdpa1p2gmode = (localVal & ((uint32_t)0x01000000)) >> 24;
    *btdpasincen = (localVal & ((uint32_t)0x00800000)) >> 23;
    *btdpasigndlysel = (localVal & ((uint32_t)0x00600000)) >> 21;
    *btdpamodesel = (localVal & ((uint32_t)0x00100000)) >> 20;
    *btdpasliceenp = (localVal & ((uint32_t)0x000F0000)) >> 16;
    *btdpasliceenn = (localVal & ((uint32_t)0x0000F000)) >> 12;
    *btdpacapbankbit = (localVal & ((uint32_t)0x00000E00)) >> 9;
    *btdpapmedgesel = (localVal & ((uint32_t)0x00000100)) >> 8;
    *bttrxcapswbit = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *btdpaantcbit = (localVal & ((uint32_t)0x0000000E)) >> 1;
    *btdpaautopmsync = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the bt_dpa_reg_vbit field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_reg_vbit field's value will be returned.
 *
 * @return The current value of the bt_dpa_reg_vbit field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x78000000)) >> 27);
}

/**
 * @brief Sets the bt_dpa_reg_vbit field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdparegvbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_reg_vbit_setf(uint8_t btdparegvbit)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x78000000)) | (((uint32_t)btdparegvbit << 27) & ((uint32_t)0x78000000)));
}

/**
 * @brief Returns the current value of the bt_dpa_clk_edge_sel field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_clk_edge_sel field's value will be returned.
 *
 * @return The current value of the bt_dpa_clk_edge_sel field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_clk_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the bt_dpa_clk_edge_sel field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaclkedgesel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_clk_edge_sel_setf(uint8_t btdpaclkedgesel)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)btdpaclkedgesel << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the bt_dpa_retime_sel field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_retime_sel field's value will be returned.
 *
 * @return The current value of the bt_dpa_retime_sel field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_retime_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the bt_dpa_retime_sel field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdparetimesel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_retime_sel_setf(uint8_t btdparetimesel)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)btdparetimesel << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the bt_dpa_1p2g_mode field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_1p2g_mode field's value will be returned.
 *
 * @return The current value of the bt_dpa_1p2g_mode field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa__1p_2g_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the bt_dpa_1p2g_mode field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpa1p2gmode - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa__1p_2g_mode_setf(uint8_t btdpa1p2gmode)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)btdpa1p2gmode << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the bt_dpa_sinc_en field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_sinc_en field's value will be returned.
 *
 * @return The current value of the bt_dpa_sinc_en field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_sinc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the bt_dpa_sinc_en field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpasincen - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_sinc_en_setf(uint8_t btdpasincen)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)btdpasincen << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the bt_dpa_sign_dly_sel field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_sign_dly_sel field's value will be returned.
 *
 * @return The current value of the bt_dpa_sign_dly_sel field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_sign_dly_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x00600000)) >> 21);
}

/**
 * @brief Sets the bt_dpa_sign_dly_sel field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpasigndlysel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_sign_dly_sel_setf(uint8_t btdpasigndlysel)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x00600000)) | (((uint32_t)btdpasigndlysel << 21) & ((uint32_t)0x00600000)));
}

/**
 * @brief Returns the current value of the bt_dpa_mode_sel field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_mode_sel field's value will be returned.
 *
 * @return The current value of the bt_dpa_mode_sel field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_mode_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the bt_dpa_mode_sel field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpamodesel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_mode_sel_setf(uint8_t btdpamodesel)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)btdpamodesel << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the bt_dpa_slice_enp field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_slice_enp field's value will be returned.
 *
 * @return The current value of the bt_dpa_slice_enp field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_slice_enp_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x000F0000)) >> 16);
}

/**
 * @brief Sets the bt_dpa_slice_enp field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpasliceenp - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_slice_enp_setf(uint8_t btdpasliceenp)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x000F0000)) | (((uint32_t)btdpasliceenp << 16) & ((uint32_t)0x000F0000)));
}

/**
 * @brief Returns the current value of the bt_dpa_slice_enn field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_slice_enn field's value will be returned.
 *
 * @return The current value of the bt_dpa_slice_enn field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_slice_enn_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x0000F000)) >> 12);
}

/**
 * @brief Sets the bt_dpa_slice_enn field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpasliceenn - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_slice_enn_setf(uint8_t btdpasliceenn)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x0000F000)) | (((uint32_t)btdpasliceenn << 12) & ((uint32_t)0x0000F000)));
}

/**
 * @brief Returns the current value of the bt_dpa_capbank_bit field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_capbank_bit field's value will be returned.
 *
 * @return The current value of the bt_dpa_capbank_bit field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_capbank_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x00000E00)) >> 9);
}

/**
 * @brief Sets the bt_dpa_capbank_bit field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpacapbankbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_capbank_bit_setf(uint8_t btdpacapbankbit)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x00000E00)) | (((uint32_t)btdpacapbankbit << 9) & ((uint32_t)0x00000E00)));
}

/**
 * @brief Returns the current value of the bt_dpa_pm_edge_sel field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_pm_edge_sel field's value will be returned.
 *
 * @return The current value of the bt_dpa_pm_edge_sel field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_pm_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the bt_dpa_pm_edge_sel field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpapmedgesel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_pm_edge_sel_setf(uint8_t btdpapmedgesel)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)btdpapmedgesel << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the bt_trx_cap_sw_bit field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_trx_cap_sw_bit field's value will be returned.
 *
 * @return The current value of the bt_trx_cap_sw_bit field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_trx_cap_sw_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Returns the current value of the bt_dpa_ant_cbit field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_ant_cbit field's value will be returned.
 *
 * @return The current value of the bt_dpa_ant_cbit field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_ant_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x0000000E)) >> 1);
}

/**
 * @brief Sets the bt_dpa_ant_cbit field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaantcbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_ant_cbit_setf(uint8_t btdpaantcbit)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x0000000E)) | (((uint32_t)btdpaantcbit << 1) & ((uint32_t)0x0000000E)));
}

/**
 * @brief Returns the current value of the bt_dpa_auto_pm_sync field in the REG_24 register.
 *
 * The REG_24 register will be read and the bt_dpa_auto_pm_sync field's value will be returned.
 *
 * @return The current value of the bt_dpa_auto_pm_sync field in the REG_24 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_auto_pm_sync_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_24_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the bt_dpa_auto_pm_sync field of the REG_24 register.
 *
 * The REG_24 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpaautopmsync - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_auto_pm_sync_setf(uint8_t btdpaautopmsync)
{
    REG_PL_WR(BT_RF_REG_24_ADDR, (REG_PL_RD(BT_RF_REG_24_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)btdpaautopmsync << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_28 register definitions
 * <table>
 * <caption id="REG_28_BF">REG_28 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:30 <td>bt_dpa_balun_tap_bit <td>R <td>R/W <td>0x3
 * <tr><td>29:28 <td>   bt_dpa_cdr_mode <td>R <td>R/W <td>0x0
 * <tr><td>27:18 <td>       bt_dco_band <td>W <td>R <td>0x1FF
 * <tr><td>17:09 <td>   bt_dco_dvar_din <td>W <td>R <td>0xFF
 * <tr><td>08 <td>bt_dco_dvar_clk_edge_sel <td>R <td>R/W <td>1
 * <tr><td>07:04 <td>bt_dco_reg_vco_bit <td>R <td>R/W <td>0x3
 * <tr><td>03:00 <td>bt_dco_reg_var_bit <td>R <td>R/W <td>0x3
 * </table>
 *
 * @{
 */

/// Address of the REG_28 register
#define BT_RF_REG_28_ADDR   0x40622028
/// Offset of the REG_28 register from the base address
#define BT_RF_REG_28_OFFSET 0x00000028
/// Index of the REG_28 register
#define BT_RF_REG_28_INDEX  0x0000000A
/// Reset value of the REG_28 register
#define BT_RF_REG_28_RESET  0xC7FDFF33

/**
 * @brief Returns the current value of the REG_28 register.
 * The REG_28 register will be read and its value returned.
 * @return The current value of the REG_28 register.
 */
__INLINE uint32_t bt_rf_reg_28_get(void)
{
    return REG_PL_RD(BT_RF_REG_28_ADDR);
}

/**
 * @brief Sets the REG_28 register to a value.
 * The REG_28 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_28_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_28_ADDR, value);
}

// field definitions
/// BT_DPA_BALUN_TAP_BIT field mask
#define BT_RF_BT_DPA_BALUN_TAP_BIT_MASK       ((uint32_t)0xC0000000)
/// BT_DPA_BALUN_TAP_BIT field LSB position
#define BT_RF_BT_DPA_BALUN_TAP_BIT_LSB        30
/// BT_DPA_BALUN_TAP_BIT field width
#define BT_RF_BT_DPA_BALUN_TAP_BIT_WIDTH      ((uint32_t)0x00000002)
/// BT_DPA_CDR_MODE field mask
#define BT_RF_BT_DPA_CDR_MODE_MASK            ((uint32_t)0x30000000)
/// BT_DPA_CDR_MODE field LSB position
#define BT_RF_BT_DPA_CDR_MODE_LSB             28
/// BT_DPA_CDR_MODE field width
#define BT_RF_BT_DPA_CDR_MODE_WIDTH           ((uint32_t)0x00000002)
/// BT_DCO_BAND field mask
#define BT_RF_BT_DCO_BAND_MASK                ((uint32_t)0x0FFC0000)
/// BT_DCO_BAND field LSB position
#define BT_RF_BT_DCO_BAND_LSB                 18
/// BT_DCO_BAND field width
#define BT_RF_BT_DCO_BAND_WIDTH               ((uint32_t)0x0000000A)
/// BT_DCO_DVAR_DIN field mask
#define BT_RF_BT_DCO_DVAR_DIN_MASK            ((uint32_t)0x0003FE00)
/// BT_DCO_DVAR_DIN field LSB position
#define BT_RF_BT_DCO_DVAR_DIN_LSB             9
/// BT_DCO_DVAR_DIN field width
#define BT_RF_BT_DCO_DVAR_DIN_WIDTH           ((uint32_t)0x00000009)
/// BT_DCO_DVAR_CLK_EDGE_SEL field bit
#define BT_RF_BT_DCO_DVAR_CLK_EDGE_SEL_BIT    ((uint32_t)0x00000100)
/// BT_DCO_DVAR_CLK_EDGE_SEL field position
#define BT_RF_BT_DCO_DVAR_CLK_EDGE_SEL_POS    8
/// BT_DCO_REG_VCO_BIT field mask
#define BT_RF_BT_DCO_REG_VCO_BIT_MASK         ((uint32_t)0x000000F0)
/// BT_DCO_REG_VCO_BIT field LSB position
#define BT_RF_BT_DCO_REG_VCO_BIT_LSB          4
/// BT_DCO_REG_VCO_BIT field width
#define BT_RF_BT_DCO_REG_VCO_BIT_WIDTH        ((uint32_t)0x00000004)
/// BT_DCO_REG_VAR_BIT field mask
#define BT_RF_BT_DCO_REG_VAR_BIT_MASK         ((uint32_t)0x0000000F)
/// BT_DCO_REG_VAR_BIT field LSB position
#define BT_RF_BT_DCO_REG_VAR_BIT_LSB          0
/// BT_DCO_REG_VAR_BIT field width
#define BT_RF_BT_DCO_REG_VAR_BIT_WIDTH        ((uint32_t)0x00000004)

/// BT_DPA_BALUN_TAP_BIT field reset value
#define BT_RF_BT_DPA_BALUN_TAP_BIT_RST        0x3
/// BT_DPA_CDR_MODE field reset value
#define BT_RF_BT_DPA_CDR_MODE_RST             0x0
/// BT_DCO_BAND field reset value
#define BT_RF_BT_DCO_BAND_RST                 0x1FF
/// BT_DCO_DVAR_DIN field reset value
#define BT_RF_BT_DCO_DVAR_DIN_RST             0xFF
/// BT_DCO_DVAR_CLK_EDGE_SEL field reset value
#define BT_RF_BT_DCO_DVAR_CLK_EDGE_SEL_RST    0x1
/// BT_DCO_REG_VCO_BIT field reset value
#define BT_RF_BT_DCO_REG_VCO_BIT_RST          0x3
/// BT_DCO_REG_VAR_BIT field reset value
#define BT_RF_BT_DCO_REG_VAR_BIT_RST          0x3

/**
 * @brief Constructs a value for the REG_28 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btdpabaluntapbit - The value to use for the bt_dpa_balun_tap_bit field.
 * @param[in] btdpacdrmode - The value to use for the bt_dpa_cdr_mode field.
 * @param[in] btdcodvarclkedgesel - The value to use for the bt_dco_dvar_clk_edge_sel field.
 * @param[in] btdcoregvcobit - The value to use for the bt_dco_reg_vco_bit field.
 * @param[in] btdcoregvarbit - The value to use for the bt_dco_reg_var_bit field.
 */
__INLINE void bt_rf_reg_28_pack(uint8_t btdpabaluntapbit, uint8_t btdpacdrmode, uint8_t btdcodvarclkedgesel, uint8_t btdcoregvcobit, uint8_t btdcoregvarbit)
{
    REG_PL_WR(BT_RF_REG_28_ADDR,  ((uint32_t)btdpabaluntapbit << 30) | ((uint32_t)btdpacdrmode << 28) | ((uint32_t)btdcodvarclkedgesel << 8) | ((uint32_t)btdcoregvcobit << 4) | ((uint32_t)btdcoregvarbit << 0));
}

/**
 * @brief Unpacks REG_28's fields from current value of the REG_28 register.
 *
 * Reads the REG_28 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btdpabaluntapbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpacdrmode - Will be populated with the current value of this field from the register.
 * @param[out] btdcoband - Will be populated with the current value of this field from the register.
 * @param[out] btdcodvardin - Will be populated with the current value of this field from the register.
 * @param[out] btdcodvarclkedgesel - Will be populated with the current value of this field from the register.
 * @param[out] btdcoregvcobit - Will be populated with the current value of this field from the register.
 * @param[out] btdcoregvarbit - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_28_unpack(uint8_t* btdpabaluntapbit, uint8_t* btdpacdrmode, uint16_t* btdcoband, uint16_t* btdcodvardin, uint8_t* btdcodvarclkedgesel, uint8_t* btdcoregvcobit, uint8_t* btdcoregvarbit)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_28_ADDR);

    *btdpabaluntapbit = (localVal & ((uint32_t)0xC0000000)) >> 30;
    *btdpacdrmode = (localVal & ((uint32_t)0x30000000)) >> 28;
    *btdcoband = (localVal & ((uint32_t)0x0FFC0000)) >> 18;
    *btdcodvardin = (localVal & ((uint32_t)0x0003FE00)) >> 9;
    *btdcodvarclkedgesel = (localVal & ((uint32_t)0x00000100)) >> 8;
    *btdcoregvcobit = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *btdcoregvarbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the bt_dpa_balun_tap_bit field in the REG_28 register.
 *
 * The REG_28 register will be read and the bt_dpa_balun_tap_bit field's value will be returned.
 *
 * @return The current value of the bt_dpa_balun_tap_bit field in the REG_28 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_balun_tap_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0xC0000000)) >> 30);
}

/**
 * @brief Sets the bt_dpa_balun_tap_bit field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpabaluntapbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_balun_tap_bit_setf(uint8_t btdpabaluntapbit)
{
    REG_PL_WR(BT_RF_REG_28_ADDR, (REG_PL_RD(BT_RF_REG_28_ADDR) & ~((uint32_t)0xC0000000)) | (((uint32_t)btdpabaluntapbit << 30) & ((uint32_t)0xC0000000)));
}

/**
 * @brief Returns the current value of the bt_dpa_cdr_mode field in the REG_28 register.
 *
 * The REG_28 register will be read and the bt_dpa_cdr_mode field's value will be returned.
 *
 * @return The current value of the bt_dpa_cdr_mode field in the REG_28 register.
 */
__INLINE uint8_t bt_rf_bt_dpa_cdr_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

/**
 * @brief Sets the bt_dpa_cdr_mode field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpacdrmode - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpa_cdr_mode_setf(uint8_t btdpacdrmode)
{
    REG_PL_WR(BT_RF_REG_28_ADDR, (REG_PL_RD(BT_RF_REG_28_ADDR) & ~((uint32_t)0x30000000)) | (((uint32_t)btdpacdrmode << 28) & ((uint32_t)0x30000000)));
}

/**
 * @brief Returns the current value of the bt_dco_band field in the REG_28 register.
 *
 * The REG_28 register will be read and the bt_dco_band field's value will be returned.
 *
 * @return The current value of the bt_dco_band field in the REG_28 register.
 */
__INLINE uint16_t bt_rf_bt_dco_band_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x0FFC0000)) >> 18);
}

/**
 * @brief Returns the current value of the bt_dco_dvar_din field in the REG_28 register.
 *
 * The REG_28 register will be read and the bt_dco_dvar_din field's value will be returned.
 *
 * @return The current value of the bt_dco_dvar_din field in the REG_28 register.
 */
__INLINE uint16_t bt_rf_bt_dco_dvar_din_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x0003FE00)) >> 9);
}

/**
 * @brief Returns the current value of the bt_dco_dvar_clk_edge_sel field in the REG_28 register.
 *
 * The REG_28 register will be read and the bt_dco_dvar_clk_edge_sel field's value will be returned.
 *
 * @return The current value of the bt_dco_dvar_clk_edge_sel field in the REG_28 register.
 */
__INLINE uint8_t bt_rf_bt_dco_dvar_clk_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the bt_dco_dvar_clk_edge_sel field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcodvarclkedgesel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_dvar_clk_edge_sel_setf(uint8_t btdcodvarclkedgesel)
{
    REG_PL_WR(BT_RF_REG_28_ADDR, (REG_PL_RD(BT_RF_REG_28_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)btdcodvarclkedgesel << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the bt_dco_reg_vco_bit field in the REG_28 register.
 *
 * The REG_28 register will be read and the bt_dco_reg_vco_bit field's value will be returned.
 *
 * @return The current value of the bt_dco_reg_vco_bit field in the REG_28 register.
 */
__INLINE uint8_t bt_rf_bt_dco_reg_vco_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Sets the bt_dco_reg_vco_bit field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcoregvcobit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_reg_vco_bit_setf(uint8_t btdcoregvcobit)
{
    REG_PL_WR(BT_RF_REG_28_ADDR, (REG_PL_RD(BT_RF_REG_28_ADDR) & ~((uint32_t)0x000000F0)) | (((uint32_t)btdcoregvcobit << 4) & ((uint32_t)0x000000F0)));
}

/**
 * @brief Returns the current value of the bt_dco_reg_var_bit field in the REG_28 register.
 *
 * The REG_28 register will be read and the bt_dco_reg_var_bit field's value will be returned.
 *
 * @return The current value of the bt_dco_reg_var_bit field in the REG_28 register.
 */
__INLINE uint8_t bt_rf_bt_dco_reg_var_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_28_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the bt_dco_reg_var_bit field of the REG_28 register.
 *
 * The REG_28 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcoregvarbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_reg_var_bit_setf(uint8_t btdcoregvarbit)
{
    REG_PL_WR(BT_RF_REG_28_ADDR, (REG_PL_RD(BT_RF_REG_28_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)btdcoregvarbit << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name REG_2C register definitions
 * <table>
 * <caption id="REG_2C_BF">REG_2C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>bt_dco_reg_var_bypass <td>R <td>R/W <td>0
 * <tr><td>30:29 <td>bt_dco_dvdd_dec_sel_bit <td>R <td>R/W <td>0x0
 * <tr><td>28 <td>     bt_dco_rot_en <td>R <td>R/W <td>0
 * <tr><td>27:24 <td>    bt_dco_cap_bit <td>R <td>R/W <td>0x0
 * <tr><td>23 <td>    bt_dco_dvdd_en <td>R <td>R/W <td>1
 * <tr><td>22:19 <td>   bt_dco_res0_bit <td>R <td>R/W <td>0x0
 * <tr><td>18:15 <td>   bt_dco_res1_bit <td>R <td>R/W <td>0x0
 * <tr><td>14:11 <td>   bt_dco_band_aux <td>R <td>R/W <td>0x0
 * <tr><td>10 <td>   bt_dco_trx_mode <td>R <td>R/W <td>1
 * <tr><td>09:08 <td>  bt_dpll_dly_sel0 <td>R <td>R/W <td>0x2
 * <tr><td>07:06 <td>  bt_dpll_dly_sel1 <td>R <td>R/W <td>0x2
 * <tr><td>05:04 <td>  bt_dpll_dly_sel2 <td>R <td>R/W <td>0x1
 * <tr><td>03:02 <td>  bt_dpll_dly_sel3 <td>R <td>R/W <td>0x0
 * <tr><td>01:00 <td>  bt_dpll_dly_sel4 <td>R <td>R/W <td>0x2
 * </table>
 *
 * @{
 */

/// Address of the REG_2C register
#define BT_RF_REG_2C_ADDR   0x4062202C
/// Offset of the REG_2C register from the base address
#define BT_RF_REG_2C_OFFSET 0x0000002C
/// Index of the REG_2C register
#define BT_RF_REG_2C_INDEX  0x0000000B
/// Reset value of the REG_2C register
#define BT_RF_REG_2C_RESET  0x00800692

/**
 * @brief Returns the current value of the REG_2C register.
 * The REG_2C register will be read and its value returned.
 * @return The current value of the REG_2C register.
 */
__INLINE uint32_t bt_rf_reg_2c_get(void)
{
    return REG_PL_RD(BT_RF_REG_2C_ADDR);
}

/**
 * @brief Sets the REG_2C register to a value.
 * The REG_2C register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_2c_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, value);
}

// field definitions
/// BT_DCO_REG_VAR_BYPASS field bit
#define BT_RF_BT_DCO_REG_VAR_BYPASS_BIT      ((uint32_t)0x80000000)
/// BT_DCO_REG_VAR_BYPASS field position
#define BT_RF_BT_DCO_REG_VAR_BYPASS_POS      31
/// BT_DCO_DVDD_DEC_SEL_BIT field mask
#define BT_RF_BT_DCO_DVDD_DEC_SEL_BIT_MASK   ((uint32_t)0x60000000)
/// BT_DCO_DVDD_DEC_SEL_BIT field LSB position
#define BT_RF_BT_DCO_DVDD_DEC_SEL_BIT_LSB    29
/// BT_DCO_DVDD_DEC_SEL_BIT field width
#define BT_RF_BT_DCO_DVDD_DEC_SEL_BIT_WIDTH  ((uint32_t)0x00000002)
/// BT_DCO_ROT_EN field bit
#define BT_RF_BT_DCO_ROT_EN_BIT              ((uint32_t)0x10000000)
/// BT_DCO_ROT_EN field position
#define BT_RF_BT_DCO_ROT_EN_POS              28
/// BT_DCO_CAP_BIT field mask
#define BT_RF_BT_DCO_CAP_BIT_MASK            ((uint32_t)0x0F000000)
/// BT_DCO_CAP_BIT field LSB position
#define BT_RF_BT_DCO_CAP_BIT_LSB             24
/// BT_DCO_CAP_BIT field width
#define BT_RF_BT_DCO_CAP_BIT_WIDTH           ((uint32_t)0x00000004)
/// BT_DCO_DVDD_EN field bit
#define BT_RF_BT_DCO_DVDD_EN_BIT             ((uint32_t)0x00800000)
/// BT_DCO_DVDD_EN field position
#define BT_RF_BT_DCO_DVDD_EN_POS             23
/// BT_DCO_RES_0_BIT field mask
#define BT_RF_BT_DCO_RES_0_BIT_MASK          ((uint32_t)0x00780000)
/// BT_DCO_RES_0_BIT field LSB position
#define BT_RF_BT_DCO_RES_0_BIT_LSB           19
/// BT_DCO_RES_0_BIT field width
#define BT_RF_BT_DCO_RES_0_BIT_WIDTH         ((uint32_t)0x00000004)
/// BT_DCO_RES_1_BIT field mask
#define BT_RF_BT_DCO_RES_1_BIT_MASK          ((uint32_t)0x00078000)
/// BT_DCO_RES_1_BIT field LSB position
#define BT_RF_BT_DCO_RES_1_BIT_LSB           15
/// BT_DCO_RES_1_BIT field width
#define BT_RF_BT_DCO_RES_1_BIT_WIDTH         ((uint32_t)0x00000004)
/// BT_DCO_BAND_AUX field mask
#define BT_RF_BT_DCO_BAND_AUX_MASK           ((uint32_t)0x00007800)
/// BT_DCO_BAND_AUX field LSB position
#define BT_RF_BT_DCO_BAND_AUX_LSB            11
/// BT_DCO_BAND_AUX field width
#define BT_RF_BT_DCO_BAND_AUX_WIDTH          ((uint32_t)0x00000004)
/// BT_DCO_TRX_MODE field bit
#define BT_RF_BT_DCO_TRX_MODE_BIT            ((uint32_t)0x00000400)
/// BT_DCO_TRX_MODE field position
#define BT_RF_BT_DCO_TRX_MODE_POS            10
/// BT_DPLL_DLY_SEL_0 field mask
#define BT_RF_BT_DPLL_DLY_SEL_0_MASK         ((uint32_t)0x00000300)
/// BT_DPLL_DLY_SEL_0 field LSB position
#define BT_RF_BT_DPLL_DLY_SEL_0_LSB          8
/// BT_DPLL_DLY_SEL_0 field width
#define BT_RF_BT_DPLL_DLY_SEL_0_WIDTH        ((uint32_t)0x00000002)
/// BT_DPLL_DLY_SEL_1 field mask
#define BT_RF_BT_DPLL_DLY_SEL_1_MASK         ((uint32_t)0x000000C0)
/// BT_DPLL_DLY_SEL_1 field LSB position
#define BT_RF_BT_DPLL_DLY_SEL_1_LSB          6
/// BT_DPLL_DLY_SEL_1 field width
#define BT_RF_BT_DPLL_DLY_SEL_1_WIDTH        ((uint32_t)0x00000002)
/// BT_DPLL_DLY_SEL_2 field mask
#define BT_RF_BT_DPLL_DLY_SEL_2_MASK         ((uint32_t)0x00000030)
/// BT_DPLL_DLY_SEL_2 field LSB position
#define BT_RF_BT_DPLL_DLY_SEL_2_LSB          4
/// BT_DPLL_DLY_SEL_2 field width
#define BT_RF_BT_DPLL_DLY_SEL_2_WIDTH        ((uint32_t)0x00000002)
/// BT_DPLL_DLY_SEL_3 field mask
#define BT_RF_BT_DPLL_DLY_SEL_3_MASK         ((uint32_t)0x0000000C)
/// BT_DPLL_DLY_SEL_3 field LSB position
#define BT_RF_BT_DPLL_DLY_SEL_3_LSB          2
/// BT_DPLL_DLY_SEL_3 field width
#define BT_RF_BT_DPLL_DLY_SEL_3_WIDTH        ((uint32_t)0x00000002)
/// BT_DPLL_DLY_SEL_4 field mask
#define BT_RF_BT_DPLL_DLY_SEL_4_MASK         ((uint32_t)0x00000003)
/// BT_DPLL_DLY_SEL_4 field LSB position
#define BT_RF_BT_DPLL_DLY_SEL_4_LSB          0
/// BT_DPLL_DLY_SEL_4 field width
#define BT_RF_BT_DPLL_DLY_SEL_4_WIDTH        ((uint32_t)0x00000002)

/// BT_DCO_REG_VAR_BYPASS field reset value
#define BT_RF_BT_DCO_REG_VAR_BYPASS_RST      0x0
/// BT_DCO_DVDD_DEC_SEL_BIT field reset value
#define BT_RF_BT_DCO_DVDD_DEC_SEL_BIT_RST    0x0
/// BT_DCO_ROT_EN field reset value
#define BT_RF_BT_DCO_ROT_EN_RST              0x0
/// BT_DCO_CAP_BIT field reset value
#define BT_RF_BT_DCO_CAP_BIT_RST             0x0
/// BT_DCO_DVDD_EN field reset value
#define BT_RF_BT_DCO_DVDD_EN_RST             0x1
/// BT_DCO_RES_0_BIT field reset value
#define BT_RF_BT_DCO_RES_0_BIT_RST           0x0
/// BT_DCO_RES_1_BIT field reset value
#define BT_RF_BT_DCO_RES_1_BIT_RST           0x0
/// BT_DCO_BAND_AUX field reset value
#define BT_RF_BT_DCO_BAND_AUX_RST            0x0
/// BT_DCO_TRX_MODE field reset value
#define BT_RF_BT_DCO_TRX_MODE_RST            0x1
/// BT_DPLL_DLY_SEL_0 field reset value
#define BT_RF_BT_DPLL_DLY_SEL_0_RST          0x2
/// BT_DPLL_DLY_SEL_1 field reset value
#define BT_RF_BT_DPLL_DLY_SEL_1_RST          0x2
/// BT_DPLL_DLY_SEL_2 field reset value
#define BT_RF_BT_DPLL_DLY_SEL_2_RST          0x1
/// BT_DPLL_DLY_SEL_3 field reset value
#define BT_RF_BT_DPLL_DLY_SEL_3_RST          0x0
/// BT_DPLL_DLY_SEL_4 field reset value
#define BT_RF_BT_DPLL_DLY_SEL_4_RST          0x2

/**
 * @brief Constructs a value for the REG_2C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btdcoregvarbypass - The value to use for the bt_dco_reg_var_bypass field.
 * @param[in] btdcodvdddecselbit - The value to use for the bt_dco_dvdd_dec_sel_bit field.
 * @param[in] btdcoroten - The value to use for the bt_dco_rot_en field.
 * @param[in] btdcocapbit - The value to use for the bt_dco_cap_bit field.
 * @param[in] btdcodvdden - The value to use for the bt_dco_dvdd_en field.
 * @param[in] btdcores0bit - The value to use for the bt_dco_res0_bit field.
 * @param[in] btdcores1bit - The value to use for the bt_dco_res1_bit field.
 * @param[in] btdcobandaux - The value to use for the bt_dco_band_aux field.
 * @param[in] btdcotrxmode - The value to use for the bt_dco_trx_mode field.
 * @param[in] btdplldlysel0 - The value to use for the bt_dpll_dly_sel0 field.
 * @param[in] btdplldlysel1 - The value to use for the bt_dpll_dly_sel1 field.
 * @param[in] btdplldlysel2 - The value to use for the bt_dpll_dly_sel2 field.
 * @param[in] btdplldlysel3 - The value to use for the bt_dpll_dly_sel3 field.
 * @param[in] btdplldlysel4 - The value to use for the bt_dpll_dly_sel4 field.
 */
__INLINE void bt_rf_reg_2c_pack(uint8_t btdcoregvarbypass, uint8_t btdcodvdddecselbit, uint8_t btdcoroten, uint8_t btdcocapbit, uint8_t btdcodvdden, uint8_t btdcores0bit, uint8_t btdcores1bit, uint8_t btdcobandaux, uint8_t btdcotrxmode, uint8_t btdplldlysel0, uint8_t btdplldlysel1, uint8_t btdplldlysel2, uint8_t btdplldlysel3, uint8_t btdplldlysel4)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR,  ((uint32_t)btdcoregvarbypass << 31) | ((uint32_t)btdcodvdddecselbit << 29) | ((uint32_t)btdcoroten << 28) | ((uint32_t)btdcocapbit << 24) | ((uint32_t)btdcodvdden << 23) | ((uint32_t)btdcores0bit << 19) | ((uint32_t)btdcores1bit << 15) | ((uint32_t)btdcobandaux << 11) | ((uint32_t)btdcotrxmode << 10) | ((uint32_t)btdplldlysel0 << 8) | ((uint32_t)btdplldlysel1 << 6) | ((uint32_t)btdplldlysel2 << 4) | ((uint32_t)btdplldlysel3 << 2) | ((uint32_t)btdplldlysel4 << 0));
}

/**
 * @brief Unpacks REG_2C's fields from current value of the REG_2C register.
 *
 * Reads the REG_2C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btdcoregvarbypass - Will be populated with the current value of this field from the register.
 * @param[out] btdcodvdddecselbit - Will be populated with the current value of this field from the register.
 * @param[out] btdcoroten - Will be populated with the current value of this field from the register.
 * @param[out] btdcocapbit - Will be populated with the current value of this field from the register.
 * @param[out] btdcodvdden - Will be populated with the current value of this field from the register.
 * @param[out] btdcores0bit - Will be populated with the current value of this field from the register.
 * @param[out] btdcores1bit - Will be populated with the current value of this field from the register.
 * @param[out] btdcobandaux - Will be populated with the current value of this field from the register.
 * @param[out] btdcotrxmode - Will be populated with the current value of this field from the register.
 * @param[out] btdplldlysel0 - Will be populated with the current value of this field from the register.
 * @param[out] btdplldlysel1 - Will be populated with the current value of this field from the register.
 * @param[out] btdplldlysel2 - Will be populated with the current value of this field from the register.
 * @param[out] btdplldlysel3 - Will be populated with the current value of this field from the register.
 * @param[out] btdplldlysel4 - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_2c_unpack(uint8_t* btdcoregvarbypass, uint8_t* btdcodvdddecselbit, uint8_t* btdcoroten, uint8_t* btdcocapbit, uint8_t* btdcodvdden, uint8_t* btdcores0bit, uint8_t* btdcores1bit, uint8_t* btdcobandaux, uint8_t* btdcotrxmode, uint8_t* btdplldlysel0, uint8_t* btdplldlysel1, uint8_t* btdplldlysel2, uint8_t* btdplldlysel3, uint8_t* btdplldlysel4)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);

    *btdcoregvarbypass = (localVal & ((uint32_t)0x80000000)) >> 31;
    *btdcodvdddecselbit = (localVal & ((uint32_t)0x60000000)) >> 29;
    *btdcoroten = (localVal & ((uint32_t)0x10000000)) >> 28;
    *btdcocapbit = (localVal & ((uint32_t)0x0F000000)) >> 24;
    *btdcodvdden = (localVal & ((uint32_t)0x00800000)) >> 23;
    *btdcores0bit = (localVal & ((uint32_t)0x00780000)) >> 19;
    *btdcores1bit = (localVal & ((uint32_t)0x00078000)) >> 15;
    *btdcobandaux = (localVal & ((uint32_t)0x00007800)) >> 11;
    *btdcotrxmode = (localVal & ((uint32_t)0x00000400)) >> 10;
    *btdplldlysel0 = (localVal & ((uint32_t)0x00000300)) >> 8;
    *btdplldlysel1 = (localVal & ((uint32_t)0x000000C0)) >> 6;
    *btdplldlysel2 = (localVal & ((uint32_t)0x00000030)) >> 4;
    *btdplldlysel3 = (localVal & ((uint32_t)0x0000000C)) >> 2;
    *btdplldlysel4 = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the bt_dco_reg_var_bypass field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dco_reg_var_bypass field's value will be returned.
 *
 * @return The current value of the bt_dco_reg_var_bypass field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dco_reg_var_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the bt_dco_reg_var_bypass field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcoregvarbypass - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_reg_var_bypass_setf(uint8_t btdcoregvarbypass)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)btdcoregvarbypass << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the bt_dco_dvdd_dec_sel_bit field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dco_dvdd_dec_sel_bit field's value will be returned.
 *
 * @return The current value of the bt_dco_dvdd_dec_sel_bit field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dco_dvdd_dec_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x60000000)) >> 29);
}

/**
 * @brief Sets the bt_dco_dvdd_dec_sel_bit field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcodvdddecselbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_dvdd_dec_sel_bit_setf(uint8_t btdcodvdddecselbit)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x60000000)) | (((uint32_t)btdcodvdddecselbit << 29) & ((uint32_t)0x60000000)));
}

/**
 * @brief Returns the current value of the bt_dco_rot_en field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dco_rot_en field's value will be returned.
 *
 * @return The current value of the bt_dco_rot_en field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dco_rot_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the bt_dco_rot_en field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcoroten - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_rot_en_setf(uint8_t btdcoroten)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)btdcoroten << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the bt_dco_cap_bit field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dco_cap_bit field's value will be returned.
 *
 * @return The current value of the bt_dco_cap_bit field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dco_cap_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x0F000000)) >> 24);
}

/**
 * @brief Sets the bt_dco_cap_bit field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcocapbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_cap_bit_setf(uint8_t btdcocapbit)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x0F000000)) | (((uint32_t)btdcocapbit << 24) & ((uint32_t)0x0F000000)));
}

/**
 * @brief Returns the current value of the bt_dco_dvdd_en field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dco_dvdd_en field's value will be returned.
 *
 * @return The current value of the bt_dco_dvdd_en field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dco_dvdd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the bt_dco_dvdd_en field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcodvdden - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_dvdd_en_setf(uint8_t btdcodvdden)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)btdcodvdden << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the bt_dco_res0_bit field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dco_res0_bit field's value will be returned.
 *
 * @return The current value of the bt_dco_res0_bit field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dco_res_0_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00780000)) >> 19);
}

/**
 * @brief Sets the bt_dco_res0_bit field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcores0bit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_res_0_bit_setf(uint8_t btdcores0bit)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x00780000)) | (((uint32_t)btdcores0bit << 19) & ((uint32_t)0x00780000)));
}

/**
 * @brief Returns the current value of the bt_dco_res1_bit field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dco_res1_bit field's value will be returned.
 *
 * @return The current value of the bt_dco_res1_bit field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dco_res_1_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00078000)) >> 15);
}

/**
 * @brief Sets the bt_dco_res1_bit field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcores1bit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_res_1_bit_setf(uint8_t btdcores1bit)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x00078000)) | (((uint32_t)btdcores1bit << 15) & ((uint32_t)0x00078000)));
}

/**
 * @brief Returns the current value of the bt_dco_band_aux field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dco_band_aux field's value will be returned.
 *
 * @return The current value of the bt_dco_band_aux field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dco_band_aux_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00007800)) >> 11);
}

/**
 * @brief Sets the bt_dco_band_aux field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcobandaux - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_band_aux_setf(uint8_t btdcobandaux)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x00007800)) | (((uint32_t)btdcobandaux << 11) & ((uint32_t)0x00007800)));
}

/**
 * @brief Returns the current value of the bt_dco_trx_mode field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dco_trx_mode field's value will be returned.
 *
 * @return The current value of the bt_dco_trx_mode field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dco_trx_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the bt_dco_trx_mode field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdcotrxmode - The value to set the field to.
 */
__INLINE void bt_rf_bt_dco_trx_mode_setf(uint8_t btdcotrxmode)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)btdcotrxmode << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the bt_dpll_dly_sel0 field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dpll_dly_sel0 field's value will be returned.
 *
 * @return The current value of the bt_dpll_dly_sel0 field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dpll_dly_sel_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the bt_dpll_dly_sel0 field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdplldlysel0 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_dly_sel_0_setf(uint8_t btdplldlysel0)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)btdplldlysel0 << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the bt_dpll_dly_sel1 field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dpll_dly_sel1 field's value will be returned.
 *
 * @return The current value of the bt_dpll_dly_sel1 field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dpll_dly_sel_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x000000C0)) >> 6);
}

/**
 * @brief Sets the bt_dpll_dly_sel1 field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdplldlysel1 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_dly_sel_1_setf(uint8_t btdplldlysel1)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x000000C0)) | (((uint32_t)btdplldlysel1 << 6) & ((uint32_t)0x000000C0)));
}

/**
 * @brief Returns the current value of the bt_dpll_dly_sel2 field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dpll_dly_sel2 field's value will be returned.
 *
 * @return The current value of the bt_dpll_dly_sel2 field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dpll_dly_sel_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

/**
 * @brief Sets the bt_dpll_dly_sel2 field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdplldlysel2 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_dly_sel_2_setf(uint8_t btdplldlysel2)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x00000030)) | (((uint32_t)btdplldlysel2 << 4) & ((uint32_t)0x00000030)));
}

/**
 * @brief Returns the current value of the bt_dpll_dly_sel3 field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dpll_dly_sel3 field's value will be returned.
 *
 * @return The current value of the bt_dpll_dly_sel3 field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dpll_dly_sel_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x0000000C)) >> 2);
}

/**
 * @brief Sets the bt_dpll_dly_sel3 field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdplldlysel3 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_dly_sel_3_setf(uint8_t btdplldlysel3)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x0000000C)) | (((uint32_t)btdplldlysel3 << 2) & ((uint32_t)0x0000000C)));
}

/**
 * @brief Returns the current value of the bt_dpll_dly_sel4 field in the REG_2C register.
 *
 * The REG_2C register will be read and the bt_dpll_dly_sel4 field's value will be returned.
 *
 * @return The current value of the bt_dpll_dly_sel4 field in the REG_2C register.
 */
__INLINE uint8_t bt_rf_bt_dpll_dly_sel_4_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_2C_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the bt_dpll_dly_sel4 field of the REG_2C register.
 *
 * The REG_2C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdplldlysel4 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_dly_sel_4_setf(uint8_t btdplldlysel4)
{
    REG_PL_WR(BT_RF_REG_2C_ADDR, (REG_PL_RD(BT_RF_REG_2C_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)btdplldlysel4 << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_30 register definitions
 * <table>
 * <caption id="REG_30_BF">REG_30 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:28 <td>  bt_dpll_dly_sel5 <td>R <td>R/W <td>0x1
 * <tr><td>27 <td>  bt_dpll_fref_sel <td>W <td>R <td>1
 * <tr><td>26 <td>   bt_dpll_fbc_sel <td>R <td>R/W <td>0
 * <tr><td>25:24 <td>bt_dpll_gro_ldo_vbit <td>R <td>R/W <td>0x2
 * <tr><td>23:20 <td>bt_dpll_gro_reg_vbit <td>R <td>R/W <td>0x8
 * <tr><td>19:16 <td>bt_dpll_presc_reg_vbit <td>R <td>R/W <td>0x8
 * <tr><td>15 <td>bt_dpll_gro_reg_bypass <td>R <td>R/W <td>0
 * <tr><td>14 <td>bt_dpll_pfd_ldo_bypass <td>R <td>R/W <td>0
 * <tr><td>13 <td>bt_dpll_presc_reg_bypass <td>R <td>R/W <td>0
 * <tr><td>12:11 <td>bt_dpll_switch_rbit <td>R <td>R/W <td>0x0
 * <tr><td>10 <td>bt_dpll_clk_am_sel <td>W <td>R <td>1
 * <tr><td>09 <td>bt_dpll_div_clk_edge_sel <td>R <td>R/W <td>0
 * <tr><td>08 <td>  bt_dpll_div_mode <td>W <td>R <td>0
 * <tr><td>07 <td>bt_dpll_cal_clk_sel <td>R <td>R/W <td>0
 * <tr><td>06 <td>    bt_dpll_cal_en <td>W <td>R <td>0
 * <tr><td>05:04 <td>bt_dpll_vco_cal_sel <td>R <td>R/W <td>0x2
 * <tr><td>03 <td>bt_dpll_sdm_clk_sel <td>W <td>R <td>0
 * <tr><td>02:01 <td>bt_dpll_chopper_clk_sel <td>R <td>R/W <td>0x2
 * <tr><td>00 <td>bt_dpll_fref_div2_en <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_30 register
#define BT_RF_REG_30_ADDR   0x40622030
/// Offset of the REG_30 register from the base address
#define BT_RF_REG_30_OFFSET 0x00000030
/// Index of the REG_30 register
#define BT_RF_REG_30_INDEX  0x0000000C
/// Reset value of the REG_30 register
#define BT_RF_REG_30_RESET  0x1A880424

/**
 * @brief Returns the current value of the REG_30 register.
 * The REG_30 register will be read and its value returned.
 * @return The current value of the REG_30 register.
 */
__INLINE uint32_t bt_rf_reg_30_get(void)
{
    return REG_PL_RD(BT_RF_REG_30_ADDR);
}

/**
 * @brief Sets the REG_30 register to a value.
 * The REG_30 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_30_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, value);
}

// field definitions
/// BT_DPLL_DLY_SEL_5 field mask
#define BT_RF_BT_DPLL_DLY_SEL_5_MASK          ((uint32_t)0x30000000)
/// BT_DPLL_DLY_SEL_5 field LSB position
#define BT_RF_BT_DPLL_DLY_SEL_5_LSB           28
/// BT_DPLL_DLY_SEL_5 field width
#define BT_RF_BT_DPLL_DLY_SEL_5_WIDTH         ((uint32_t)0x00000002)
/// BT_DPLL_FREF_SEL field bit
#define BT_RF_BT_DPLL_FREF_SEL_BIT            ((uint32_t)0x08000000)
/// BT_DPLL_FREF_SEL field position
#define BT_RF_BT_DPLL_FREF_SEL_POS            27
/// BT_DPLL_FBC_SEL field bit
#define BT_RF_BT_DPLL_FBC_SEL_BIT             ((uint32_t)0x04000000)
/// BT_DPLL_FBC_SEL field position
#define BT_RF_BT_DPLL_FBC_SEL_POS             26
/// BT_DPLL_GRO_LDO_VBIT field mask
#define BT_RF_BT_DPLL_GRO_LDO_VBIT_MASK       ((uint32_t)0x03000000)
/// BT_DPLL_GRO_LDO_VBIT field LSB position
#define BT_RF_BT_DPLL_GRO_LDO_VBIT_LSB        24
/// BT_DPLL_GRO_LDO_VBIT field width
#define BT_RF_BT_DPLL_GRO_LDO_VBIT_WIDTH      ((uint32_t)0x00000002)
/// BT_DPLL_GRO_REG_VBIT field mask
#define BT_RF_BT_DPLL_GRO_REG_VBIT_MASK       ((uint32_t)0x00F00000)
/// BT_DPLL_GRO_REG_VBIT field LSB position
#define BT_RF_BT_DPLL_GRO_REG_VBIT_LSB        20
/// BT_DPLL_GRO_REG_VBIT field width
#define BT_RF_BT_DPLL_GRO_REG_VBIT_WIDTH      ((uint32_t)0x00000004)
/// BT_DPLL_PRESC_REG_VBIT field mask
#define BT_RF_BT_DPLL_PRESC_REG_VBIT_MASK     ((uint32_t)0x000F0000)
/// BT_DPLL_PRESC_REG_VBIT field LSB position
#define BT_RF_BT_DPLL_PRESC_REG_VBIT_LSB      16
/// BT_DPLL_PRESC_REG_VBIT field width
#define BT_RF_BT_DPLL_PRESC_REG_VBIT_WIDTH    ((uint32_t)0x00000004)
/// BT_DPLL_GRO_REG_BYPASS field bit
#define BT_RF_BT_DPLL_GRO_REG_BYPASS_BIT      ((uint32_t)0x00008000)
/// BT_DPLL_GRO_REG_BYPASS field position
#define BT_RF_BT_DPLL_GRO_REG_BYPASS_POS      15
/// BT_DPLL_PFD_LDO_BYPASS field bit
#define BT_RF_BT_DPLL_PFD_LDO_BYPASS_BIT      ((uint32_t)0x00004000)
/// BT_DPLL_PFD_LDO_BYPASS field position
#define BT_RF_BT_DPLL_PFD_LDO_BYPASS_POS      14
/// BT_DPLL_PRESC_REG_BYPASS field bit
#define BT_RF_BT_DPLL_PRESC_REG_BYPASS_BIT    ((uint32_t)0x00002000)
/// BT_DPLL_PRESC_REG_BYPASS field position
#define BT_RF_BT_DPLL_PRESC_REG_BYPASS_POS    13
/// BT_DPLL_SWITCH_RBIT field mask
#define BT_RF_BT_DPLL_SWITCH_RBIT_MASK        ((uint32_t)0x00001800)
/// BT_DPLL_SWITCH_RBIT field LSB position
#define BT_RF_BT_DPLL_SWITCH_RBIT_LSB         11
/// BT_DPLL_SWITCH_RBIT field width
#define BT_RF_BT_DPLL_SWITCH_RBIT_WIDTH       ((uint32_t)0x00000002)
/// BT_DPLL_CLK_AM_SEL field bit
#define BT_RF_BT_DPLL_CLK_AM_SEL_BIT          ((uint32_t)0x00000400)
/// BT_DPLL_CLK_AM_SEL field position
#define BT_RF_BT_DPLL_CLK_AM_SEL_POS          10
/// BT_DPLL_DIV_CLK_EDGE_SEL field bit
#define BT_RF_BT_DPLL_DIV_CLK_EDGE_SEL_BIT    ((uint32_t)0x00000200)
/// BT_DPLL_DIV_CLK_EDGE_SEL field position
#define BT_RF_BT_DPLL_DIV_CLK_EDGE_SEL_POS    9
/// BT_DPLL_DIV_MODE field bit
#define BT_RF_BT_DPLL_DIV_MODE_BIT            ((uint32_t)0x00000100)
/// BT_DPLL_DIV_MODE field position
#define BT_RF_BT_DPLL_DIV_MODE_POS            8
/// BT_DPLL_CAL_CLK_SEL field bit
#define BT_RF_BT_DPLL_CAL_CLK_SEL_BIT         ((uint32_t)0x00000080)
/// BT_DPLL_CAL_CLK_SEL field position
#define BT_RF_BT_DPLL_CAL_CLK_SEL_POS         7
/// BT_DPLL_CAL_EN field bit
#define BT_RF_BT_DPLL_CAL_EN_BIT              ((uint32_t)0x00000040)
/// BT_DPLL_CAL_EN field position
#define BT_RF_BT_DPLL_CAL_EN_POS              6
/// BT_DPLL_VCO_CAL_SEL field mask
#define BT_RF_BT_DPLL_VCO_CAL_SEL_MASK        ((uint32_t)0x00000030)
/// BT_DPLL_VCO_CAL_SEL field LSB position
#define BT_RF_BT_DPLL_VCO_CAL_SEL_LSB         4
/// BT_DPLL_VCO_CAL_SEL field width
#define BT_RF_BT_DPLL_VCO_CAL_SEL_WIDTH       ((uint32_t)0x00000002)
/// BT_DPLL_SDM_CLK_SEL field bit
#define BT_RF_BT_DPLL_SDM_CLK_SEL_BIT         ((uint32_t)0x00000008)
/// BT_DPLL_SDM_CLK_SEL field position
#define BT_RF_BT_DPLL_SDM_CLK_SEL_POS         3
/// BT_DPLL_CHOPPER_CLK_SEL field mask
#define BT_RF_BT_DPLL_CHOPPER_CLK_SEL_MASK    ((uint32_t)0x00000006)
/// BT_DPLL_CHOPPER_CLK_SEL field LSB position
#define BT_RF_BT_DPLL_CHOPPER_CLK_SEL_LSB     1
/// BT_DPLL_CHOPPER_CLK_SEL field width
#define BT_RF_BT_DPLL_CHOPPER_CLK_SEL_WIDTH   ((uint32_t)0x00000002)
/// BT_DPLL_FREF_DIV_2_EN field bit
#define BT_RF_BT_DPLL_FREF_DIV_2_EN_BIT       ((uint32_t)0x00000001)
/// BT_DPLL_FREF_DIV_2_EN field position
#define BT_RF_BT_DPLL_FREF_DIV_2_EN_POS       0

/// BT_DPLL_DLY_SEL_5 field reset value
#define BT_RF_BT_DPLL_DLY_SEL_5_RST           0x1
/// BT_DPLL_FREF_SEL field reset value
#define BT_RF_BT_DPLL_FREF_SEL_RST            0x1
/// BT_DPLL_FBC_SEL field reset value
#define BT_RF_BT_DPLL_FBC_SEL_RST             0x0
/// BT_DPLL_GRO_LDO_VBIT field reset value
#define BT_RF_BT_DPLL_GRO_LDO_VBIT_RST        0x2
/// BT_DPLL_GRO_REG_VBIT field reset value
#define BT_RF_BT_DPLL_GRO_REG_VBIT_RST        0x8
/// BT_DPLL_PRESC_REG_VBIT field reset value
#define BT_RF_BT_DPLL_PRESC_REG_VBIT_RST      0x8
/// BT_DPLL_GRO_REG_BYPASS field reset value
#define BT_RF_BT_DPLL_GRO_REG_BYPASS_RST      0x0
/// BT_DPLL_PFD_LDO_BYPASS field reset value
#define BT_RF_BT_DPLL_PFD_LDO_BYPASS_RST      0x0
/// BT_DPLL_PRESC_REG_BYPASS field reset value
#define BT_RF_BT_DPLL_PRESC_REG_BYPASS_RST    0x0
/// BT_DPLL_SWITCH_RBIT field reset value
#define BT_RF_BT_DPLL_SWITCH_RBIT_RST         0x0
/// BT_DPLL_CLK_AM_SEL field reset value
#define BT_RF_BT_DPLL_CLK_AM_SEL_RST          0x1
/// BT_DPLL_DIV_CLK_EDGE_SEL field reset value
#define BT_RF_BT_DPLL_DIV_CLK_EDGE_SEL_RST    0x0
/// BT_DPLL_DIV_MODE field reset value
#define BT_RF_BT_DPLL_DIV_MODE_RST            0x0
/// BT_DPLL_CAL_CLK_SEL field reset value
#define BT_RF_BT_DPLL_CAL_CLK_SEL_RST         0x0
/// BT_DPLL_CAL_EN field reset value
#define BT_RF_BT_DPLL_CAL_EN_RST              0x0
/// BT_DPLL_VCO_CAL_SEL field reset value
#define BT_RF_BT_DPLL_VCO_CAL_SEL_RST         0x2
/// BT_DPLL_SDM_CLK_SEL field reset value
#define BT_RF_BT_DPLL_SDM_CLK_SEL_RST         0x0
/// BT_DPLL_CHOPPER_CLK_SEL field reset value
#define BT_RF_BT_DPLL_CHOPPER_CLK_SEL_RST     0x2
/// BT_DPLL_FREF_DIV_2_EN field reset value
#define BT_RF_BT_DPLL_FREF_DIV_2_EN_RST       0x0

/**
 * @brief Constructs a value for the REG_30 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btdplldlysel5 - The value to use for the bt_dpll_dly_sel5 field.
 * @param[in] btdpllfbcsel - The value to use for the bt_dpll_fbc_sel field.
 * @param[in] btdpllgroldovbit - The value to use for the bt_dpll_gro_ldo_vbit field.
 * @param[in] btdpllgroregvbit - The value to use for the bt_dpll_gro_reg_vbit field.
 * @param[in] btdpllprescregvbit - The value to use for the bt_dpll_presc_reg_vbit field.
 * @param[in] btdpllgroregbypass - The value to use for the bt_dpll_gro_reg_bypass field.
 * @param[in] btdpllpfdldobypass - The value to use for the bt_dpll_pfd_ldo_bypass field.
 * @param[in] btdpllprescregbypass - The value to use for the bt_dpll_presc_reg_bypass field.
 * @param[in] btdpllswitchrbit - The value to use for the bt_dpll_switch_rbit field.
 * @param[in] btdplldivclkedgesel - The value to use for the bt_dpll_div_clk_edge_sel field.
 * @param[in] btdpllcalclksel - The value to use for the bt_dpll_cal_clk_sel field.
 * @param[in] btdpllvcocalsel - The value to use for the bt_dpll_vco_cal_sel field.
 * @param[in] btdpllchopperclksel - The value to use for the bt_dpll_chopper_clk_sel field.
 * @param[in] btdpllfrefdiv2en - The value to use for the bt_dpll_fref_div2_en field.
 */
__INLINE void bt_rf_reg_30_pack(uint8_t btdplldlysel5, uint8_t btdpllfbcsel, uint8_t btdpllgroldovbit, uint8_t btdpllgroregvbit, uint8_t btdpllprescregvbit, uint8_t btdpllgroregbypass, uint8_t btdpllpfdldobypass, uint8_t btdpllprescregbypass, uint8_t btdpllswitchrbit, uint8_t btdplldivclkedgesel, uint8_t btdpllcalclksel, uint8_t btdpllvcocalsel, uint8_t btdpllchopperclksel, uint8_t btdpllfrefdiv2en)
{
    REG_PL_WR(BT_RF_REG_30_ADDR,  ((uint32_t)btdplldlysel5 << 28) | ((uint32_t)btdpllfbcsel << 26) | ((uint32_t)btdpllgroldovbit << 24) | ((uint32_t)btdpllgroregvbit << 20) | ((uint32_t)btdpllprescregvbit << 16) | ((uint32_t)btdpllgroregbypass << 15) | ((uint32_t)btdpllpfdldobypass << 14) | ((uint32_t)btdpllprescregbypass << 13) | ((uint32_t)btdpllswitchrbit << 11) | ((uint32_t)btdplldivclkedgesel << 9) | ((uint32_t)btdpllcalclksel << 7) | ((uint32_t)btdpllvcocalsel << 4) | ((uint32_t)btdpllchopperclksel << 1) | ((uint32_t)btdpllfrefdiv2en << 0));
}

/**
 * @brief Unpacks REG_30's fields from current value of the REG_30 register.
 *
 * Reads the REG_30 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btdplldlysel5 - Will be populated with the current value of this field from the register.
 * @param[out] btdpllfrefsel - Will be populated with the current value of this field from the register.
 * @param[out] btdpllfbcsel - Will be populated with the current value of this field from the register.
 * @param[out] btdpllgroldovbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpllgroregvbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpllprescregvbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpllgroregbypass - Will be populated with the current value of this field from the register.
 * @param[out] btdpllpfdldobypass - Will be populated with the current value of this field from the register.
 * @param[out] btdpllprescregbypass - Will be populated with the current value of this field from the register.
 * @param[out] btdpllswitchrbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpllclkamsel - Will be populated with the current value of this field from the register.
 * @param[out] btdplldivclkedgesel - Will be populated with the current value of this field from the register.
 * @param[out] btdplldivmode - Will be populated with the current value of this field from the register.
 * @param[out] btdpllcalclksel - Will be populated with the current value of this field from the register.
 * @param[out] btdpllcalen - Will be populated with the current value of this field from the register.
 * @param[out] btdpllvcocalsel - Will be populated with the current value of this field from the register.
 * @param[out] btdpllsdmclksel - Will be populated with the current value of this field from the register.
 * @param[out] btdpllchopperclksel - Will be populated with the current value of this field from the register.
 * @param[out] btdpllfrefdiv2en - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_30_unpack(uint8_t* btdplldlysel5, uint8_t* btdpllfrefsel, uint8_t* btdpllfbcsel, uint8_t* btdpllgroldovbit, uint8_t* btdpllgroregvbit, uint8_t* btdpllprescregvbit, uint8_t* btdpllgroregbypass, uint8_t* btdpllpfdldobypass, uint8_t* btdpllprescregbypass, uint8_t* btdpllswitchrbit, uint8_t* btdpllclkamsel, uint8_t* btdplldivclkedgesel, uint8_t* btdplldivmode, uint8_t* btdpllcalclksel, uint8_t* btdpllcalen, uint8_t* btdpllvcocalsel, uint8_t* btdpllsdmclksel, uint8_t* btdpllchopperclksel, uint8_t* btdpllfrefdiv2en)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);

    *btdplldlysel5 = (localVal & ((uint32_t)0x30000000)) >> 28;
    *btdpllfrefsel = (localVal & ((uint32_t)0x08000000)) >> 27;
    *btdpllfbcsel = (localVal & ((uint32_t)0x04000000)) >> 26;
    *btdpllgroldovbit = (localVal & ((uint32_t)0x03000000)) >> 24;
    *btdpllgroregvbit = (localVal & ((uint32_t)0x00F00000)) >> 20;
    *btdpllprescregvbit = (localVal & ((uint32_t)0x000F0000)) >> 16;
    *btdpllgroregbypass = (localVal & ((uint32_t)0x00008000)) >> 15;
    *btdpllpfdldobypass = (localVal & ((uint32_t)0x00004000)) >> 14;
    *btdpllprescregbypass = (localVal & ((uint32_t)0x00002000)) >> 13;
    *btdpllswitchrbit = (localVal & ((uint32_t)0x00001800)) >> 11;
    *btdpllclkamsel = (localVal & ((uint32_t)0x00000400)) >> 10;
    *btdplldivclkedgesel = (localVal & ((uint32_t)0x00000200)) >> 9;
    *btdplldivmode = (localVal & ((uint32_t)0x00000100)) >> 8;
    *btdpllcalclksel = (localVal & ((uint32_t)0x00000080)) >> 7;
    *btdpllcalen = (localVal & ((uint32_t)0x00000040)) >> 6;
    *btdpllvcocalsel = (localVal & ((uint32_t)0x00000030)) >> 4;
    *btdpllsdmclksel = (localVal & ((uint32_t)0x00000008)) >> 3;
    *btdpllchopperclksel = (localVal & ((uint32_t)0x00000006)) >> 1;
    *btdpllfrefdiv2en = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the bt_dpll_dly_sel5 field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_dly_sel5 field's value will be returned.
 *
 * @return The current value of the bt_dpll_dly_sel5 field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_dly_sel_5_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

/**
 * @brief Sets the bt_dpll_dly_sel5 field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdplldlysel5 - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_dly_sel_5_setf(uint8_t btdplldlysel5)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x30000000)) | (((uint32_t)btdplldlysel5 << 28) & ((uint32_t)0x30000000)));
}

/**
 * @brief Returns the current value of the bt_dpll_fref_sel field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_fref_sel field's value will be returned.
 *
 * @return The current value of the bt_dpll_fref_sel field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_fref_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Returns the current value of the bt_dpll_fbc_sel field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_fbc_sel field's value will be returned.
 *
 * @return The current value of the bt_dpll_fbc_sel field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_fbc_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the bt_dpll_fbc_sel field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllfbcsel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_fbc_sel_setf(uint8_t btdpllfbcsel)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)btdpllfbcsel << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the bt_dpll_gro_ldo_vbit field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_gro_ldo_vbit field's value will be returned.
 *
 * @return The current value of the bt_dpll_gro_ldo_vbit field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_gro_ldo_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

/**
 * @brief Sets the bt_dpll_gro_ldo_vbit field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllgroldovbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_gro_ldo_vbit_setf(uint8_t btdpllgroldovbit)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x03000000)) | (((uint32_t)btdpllgroldovbit << 24) & ((uint32_t)0x03000000)));
}

/**
 * @brief Returns the current value of the bt_dpll_gro_reg_vbit field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_gro_reg_vbit field's value will be returned.
 *
 * @return The current value of the bt_dpll_gro_reg_vbit field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_gro_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00F00000)) >> 20);
}

/**
 * @brief Sets the bt_dpll_gro_reg_vbit field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllgroregvbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_gro_reg_vbit_setf(uint8_t btdpllgroregvbit)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00F00000)) | (((uint32_t)btdpllgroregvbit << 20) & ((uint32_t)0x00F00000)));
}

/**
 * @brief Returns the current value of the bt_dpll_presc_reg_vbit field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_presc_reg_vbit field's value will be returned.
 *
 * @return The current value of the bt_dpll_presc_reg_vbit field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_presc_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x000F0000)) >> 16);
}

/**
 * @brief Sets the bt_dpll_presc_reg_vbit field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllprescregvbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_presc_reg_vbit_setf(uint8_t btdpllprescregvbit)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x000F0000)) | (((uint32_t)btdpllprescregvbit << 16) & ((uint32_t)0x000F0000)));
}

/**
 * @brief Returns the current value of the bt_dpll_gro_reg_bypass field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_gro_reg_bypass field's value will be returned.
 *
 * @return The current value of the bt_dpll_gro_reg_bypass field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_gro_reg_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the bt_dpll_gro_reg_bypass field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllgroregbypass - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_gro_reg_bypass_setf(uint8_t btdpllgroregbypass)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)btdpllgroregbypass << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the bt_dpll_pfd_ldo_bypass field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_pfd_ldo_bypass field's value will be returned.
 *
 * @return The current value of the bt_dpll_pfd_ldo_bypass field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_pfd_ldo_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the bt_dpll_pfd_ldo_bypass field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllpfdldobypass - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_pfd_ldo_bypass_setf(uint8_t btdpllpfdldobypass)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)btdpllpfdldobypass << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the bt_dpll_presc_reg_bypass field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_presc_reg_bypass field's value will be returned.
 *
 * @return The current value of the bt_dpll_presc_reg_bypass field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_presc_reg_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the bt_dpll_presc_reg_bypass field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllprescregbypass - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_presc_reg_bypass_setf(uint8_t btdpllprescregbypass)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)btdpllprescregbypass << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the bt_dpll_switch_rbit field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_switch_rbit field's value will be returned.
 *
 * @return The current value of the bt_dpll_switch_rbit field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_switch_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00001800)) >> 11);
}

/**
 * @brief Sets the bt_dpll_switch_rbit field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllswitchrbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_switch_rbit_setf(uint8_t btdpllswitchrbit)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00001800)) | (((uint32_t)btdpllswitchrbit << 11) & ((uint32_t)0x00001800)));
}

/**
 * @brief Returns the current value of the bt_dpll_clk_am_sel field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_clk_am_sel field's value will be returned.
 *
 * @return The current value of the bt_dpll_clk_am_sel field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_clk_am_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Returns the current value of the bt_dpll_div_clk_edge_sel field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_div_clk_edge_sel field's value will be returned.
 *
 * @return The current value of the bt_dpll_div_clk_edge_sel field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_div_clk_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the bt_dpll_div_clk_edge_sel field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdplldivclkedgesel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_div_clk_edge_sel_setf(uint8_t btdplldivclkedgesel)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)btdplldivclkedgesel << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the bt_dpll_div_mode field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_div_mode field's value will be returned.
 *
 * @return The current value of the bt_dpll_div_mode field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_div_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Returns the current value of the bt_dpll_cal_clk_sel field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_cal_clk_sel field's value will be returned.
 *
 * @return The current value of the bt_dpll_cal_clk_sel field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_cal_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the bt_dpll_cal_clk_sel field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllcalclksel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_cal_clk_sel_setf(uint8_t btdpllcalclksel)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)btdpllcalclksel << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the bt_dpll_cal_en field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_cal_en field's value will be returned.
 *
 * @return The current value of the bt_dpll_cal_en field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Returns the current value of the bt_dpll_vco_cal_sel field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_vco_cal_sel field's value will be returned.
 *
 * @return The current value of the bt_dpll_vco_cal_sel field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_vco_cal_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

/**
 * @brief Sets the bt_dpll_vco_cal_sel field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllvcocalsel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_vco_cal_sel_setf(uint8_t btdpllvcocalsel)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00000030)) | (((uint32_t)btdpllvcocalsel << 4) & ((uint32_t)0x00000030)));
}

/**
 * @brief Returns the current value of the bt_dpll_sdm_clk_sel field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_sdm_clk_sel field's value will be returned.
 *
 * @return The current value of the bt_dpll_sdm_clk_sel field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_sdm_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Returns the current value of the bt_dpll_chopper_clk_sel field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_chopper_clk_sel field's value will be returned.
 *
 * @return The current value of the bt_dpll_chopper_clk_sel field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_chopper_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000006)) >> 1);
}

/**
 * @brief Sets the bt_dpll_chopper_clk_sel field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllchopperclksel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_chopper_clk_sel_setf(uint8_t btdpllchopperclksel)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00000006)) | (((uint32_t)btdpllchopperclksel << 1) & ((uint32_t)0x00000006)));
}

/**
 * @brief Returns the current value of the bt_dpll_fref_div2_en field in the REG_30 register.
 *
 * The REG_30 register will be read and the bt_dpll_fref_div2_en field's value will be returned.
 *
 * @return The current value of the bt_dpll_fref_div2_en field in the REG_30 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_fref_div_2_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_30_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the bt_dpll_fref_div2_en field of the REG_30 register.
 *
 * The REG_30 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllfrefdiv2en - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_fref_div_2_en_setf(uint8_t btdpllfrefdiv2en)
{
    REG_PL_WR(BT_RF_REG_30_ADDR, (REG_PL_RD(BT_RF_REG_30_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)btdpllfrefdiv2en << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_34 register definitions
 * <table>
 * <caption id="REG_34_BF">REG_34 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:26 <td>   bt_dpll_drv_bit <td>R <td>R/W <td>0x0
 * <tr><td>25:09 <td>   bt_dpll_cnt_out <td>W <td>R <td>0x0
 * <tr><td>08 <td>bt_dpll_img_cal_mode <td>R <td>R/W <td>0
 * <tr><td>07 <td>bt_dpll2wf_img5g_en <td>R <td>R/W <td>0
 * <tr><td>06 <td>bt_dpll2wf_img24g_en <td>R <td>R/W <td>0
 * <tr><td>05 <td>bt_dpll_chop_clk_en <td>R <td>R/W <td>1
 * <tr><td>04 <td>bt_dpll_sdadc_clk_sel <td>R <td>R/W <td>0
 * <tr><td>03 <td> bt_chop_bg_osc_en <td>R <td>R/W <td>1
 * <tr><td>02:01 <td>bt_chop_bg_osc_bit <td>R <td>R/W <td>0x2
 * <tr><td>00 <td>    bt_tia2gpio_en <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_34 register
#define BT_RF_REG_34_ADDR   0x40622034
/// Offset of the REG_34 register from the base address
#define BT_RF_REG_34_OFFSET 0x00000034
/// Index of the REG_34 register
#define BT_RF_REG_34_INDEX  0x0000000D
/// Reset value of the REG_34 register
#define BT_RF_REG_34_RESET  0x0000002C

/**
 * @brief Returns the current value of the REG_34 register.
 * The REG_34 register will be read and its value returned.
 * @return The current value of the REG_34 register.
 */
__INLINE uint32_t bt_rf_reg_34_get(void)
{
    return REG_PL_RD(BT_RF_REG_34_ADDR);
}

/**
 * @brief Sets the REG_34 register to a value.
 * The REG_34 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_34_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, value);
}

// field definitions
/// BT_DPLL_DRV_BIT field mask
#define BT_RF_BT_DPLL_DRV_BIT_MASK          ((uint32_t)0xFC000000)
/// BT_DPLL_DRV_BIT field LSB position
#define BT_RF_BT_DPLL_DRV_BIT_LSB           26
/// BT_DPLL_DRV_BIT field width
#define BT_RF_BT_DPLL_DRV_BIT_WIDTH         ((uint32_t)0x00000006)
/// BT_DPLL_CNT_OUT field mask
#define BT_RF_BT_DPLL_CNT_OUT_MASK          ((uint32_t)0x03FFFE00)
/// BT_DPLL_CNT_OUT field LSB position
#define BT_RF_BT_DPLL_CNT_OUT_LSB           9
/// BT_DPLL_CNT_OUT field width
#define BT_RF_BT_DPLL_CNT_OUT_WIDTH         ((uint32_t)0x00000011)
/// BT_DPLL_IMG_CAL_MODE field bit
#define BT_RF_BT_DPLL_IMG_CAL_MODE_BIT      ((uint32_t)0x00000100)
/// BT_DPLL_IMG_CAL_MODE field position
#define BT_RF_BT_DPLL_IMG_CAL_MODE_POS      8
/// BT_DPLL_2WF_IMG_5G_EN field bit
#define BT_RF_BT_DPLL_2WF_IMG_5G_EN_BIT     ((uint32_t)0x00000080)
/// BT_DPLL_2WF_IMG_5G_EN field position
#define BT_RF_BT_DPLL_2WF_IMG_5G_EN_POS     7
/// BT_DPLL_2WF_IMG_24G_EN field bit
#define BT_RF_BT_DPLL_2WF_IMG_24G_EN_BIT    ((uint32_t)0x00000040)
/// BT_DPLL_2WF_IMG_24G_EN field position
#define BT_RF_BT_DPLL_2WF_IMG_24G_EN_POS    6
/// BT_DPLL_CHOP_CLK_EN field bit
#define BT_RF_BT_DPLL_CHOP_CLK_EN_BIT       ((uint32_t)0x00000020)
/// BT_DPLL_CHOP_CLK_EN field position
#define BT_RF_BT_DPLL_CHOP_CLK_EN_POS       5
/// BT_DPLL_SDADC_CLK_SEL field bit
#define BT_RF_BT_DPLL_SDADC_CLK_SEL_BIT     ((uint32_t)0x00000010)
/// BT_DPLL_SDADC_CLK_SEL field position
#define BT_RF_BT_DPLL_SDADC_CLK_SEL_POS     4
/// BT_CHOP_BG_OSC_EN field bit
#define BT_RF_BT_CHOP_BG_OSC_EN_BIT         ((uint32_t)0x00000008)
/// BT_CHOP_BG_OSC_EN field position
#define BT_RF_BT_CHOP_BG_OSC_EN_POS         3
/// BT_CHOP_BG_OSC_BIT field mask
#define BT_RF_BT_CHOP_BG_OSC_BIT_MASK       ((uint32_t)0x00000006)
/// BT_CHOP_BG_OSC_BIT field LSB position
#define BT_RF_BT_CHOP_BG_OSC_BIT_LSB        1
/// BT_CHOP_BG_OSC_BIT field width
#define BT_RF_BT_CHOP_BG_OSC_BIT_WIDTH      ((uint32_t)0x00000002)
/// BT_TIA_2GPIO_EN field bit
#define BT_RF_BT_TIA_2GPIO_EN_BIT           ((uint32_t)0x00000001)
/// BT_TIA_2GPIO_EN field position
#define BT_RF_BT_TIA_2GPIO_EN_POS           0

/// BT_DPLL_DRV_BIT field reset value
#define BT_RF_BT_DPLL_DRV_BIT_RST           0x0
/// BT_DPLL_CNT_OUT field reset value
#define BT_RF_BT_DPLL_CNT_OUT_RST           0x0
/// BT_DPLL_IMG_CAL_MODE field reset value
#define BT_RF_BT_DPLL_IMG_CAL_MODE_RST      0x0
/// BT_DPLL_2WF_IMG_5G_EN field reset value
#define BT_RF_BT_DPLL_2WF_IMG_5G_EN_RST     0x0
/// BT_DPLL_2WF_IMG_24G_EN field reset value
#define BT_RF_BT_DPLL_2WF_IMG_24G_EN_RST    0x0
/// BT_DPLL_CHOP_CLK_EN field reset value
#define BT_RF_BT_DPLL_CHOP_CLK_EN_RST       0x1
/// BT_DPLL_SDADC_CLK_SEL field reset value
#define BT_RF_BT_DPLL_SDADC_CLK_SEL_RST     0x0
/// BT_CHOP_BG_OSC_EN field reset value
#define BT_RF_BT_CHOP_BG_OSC_EN_RST         0x1
/// BT_CHOP_BG_OSC_BIT field reset value
#define BT_RF_BT_CHOP_BG_OSC_BIT_RST        0x2
/// BT_TIA_2GPIO_EN field reset value
#define BT_RF_BT_TIA_2GPIO_EN_RST           0x0

/**
 * @brief Constructs a value for the REG_34 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btdplldrvbit - The value to use for the bt_dpll_drv_bit field.
 * @param[in] btdpllimgcalmode - The value to use for the bt_dpll_img_cal_mode field.
 * @param[in] btdpll2wfimg5gen - The value to use for the bt_dpll2wf_img5g_en field.
 * @param[in] btdpll2wfimg24gen - The value to use for the bt_dpll2wf_img24g_en field.
 * @param[in] btdpllchopclken - The value to use for the bt_dpll_chop_clk_en field.
 * @param[in] btdpllsdadcclksel - The value to use for the bt_dpll_sdadc_clk_sel field.
 * @param[in] btchopbgoscen - The value to use for the bt_chop_bg_osc_en field.
 * @param[in] btchopbgoscbit - The value to use for the bt_chop_bg_osc_bit field.
 * @param[in] bttia2gpioen - The value to use for the bt_tia2gpio_en field.
 */
__INLINE void bt_rf_reg_34_pack(uint8_t btdplldrvbit, uint8_t btdpllimgcalmode, uint8_t btdpll2wfimg5gen, uint8_t btdpll2wfimg24gen, uint8_t btdpllchopclken, uint8_t btdpllsdadcclksel, uint8_t btchopbgoscen, uint8_t btchopbgoscbit, uint8_t bttia2gpioen)
{
    REG_PL_WR(BT_RF_REG_34_ADDR,  ((uint32_t)btdplldrvbit << 26) | ((uint32_t)btdpllimgcalmode << 8) | ((uint32_t)btdpll2wfimg5gen << 7) | ((uint32_t)btdpll2wfimg24gen << 6) | ((uint32_t)btdpllchopclken << 5) | ((uint32_t)btdpllsdadcclksel << 4) | ((uint32_t)btchopbgoscen << 3) | ((uint32_t)btchopbgoscbit << 1) | ((uint32_t)bttia2gpioen << 0));
}

/**
 * @brief Unpacks REG_34's fields from current value of the REG_34 register.
 *
 * Reads the REG_34 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btdplldrvbit - Will be populated with the current value of this field from the register.
 * @param[out] btdpllcntout - Will be populated with the current value of this field from the register.
 * @param[out] btdpllimgcalmode - Will be populated with the current value of this field from the register.
 * @param[out] btdpll2wfimg5gen - Will be populated with the current value of this field from the register.
 * @param[out] btdpll2wfimg24gen - Will be populated with the current value of this field from the register.
 * @param[out] btdpllchopclken - Will be populated with the current value of this field from the register.
 * @param[out] btdpllsdadcclksel - Will be populated with the current value of this field from the register.
 * @param[out] btchopbgoscen - Will be populated with the current value of this field from the register.
 * @param[out] btchopbgoscbit - Will be populated with the current value of this field from the register.
 * @param[out] bttia2gpioen - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_34_unpack(uint8_t* btdplldrvbit, uint32_t* btdpllcntout, uint8_t* btdpllimgcalmode, uint8_t* btdpll2wfimg5gen, uint8_t* btdpll2wfimg24gen, uint8_t* btdpllchopclken, uint8_t* btdpllsdadcclksel, uint8_t* btchopbgoscen, uint8_t* btchopbgoscbit, uint8_t* bttia2gpioen)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);

    *btdplldrvbit = (localVal & ((uint32_t)0xFC000000)) >> 26;
    *btdpllcntout = (localVal & ((uint32_t)0x03FFFE00)) >> 9;
    *btdpllimgcalmode = (localVal & ((uint32_t)0x00000100)) >> 8;
    *btdpll2wfimg5gen = (localVal & ((uint32_t)0x00000080)) >> 7;
    *btdpll2wfimg24gen = (localVal & ((uint32_t)0x00000040)) >> 6;
    *btdpllchopclken = (localVal & ((uint32_t)0x00000020)) >> 5;
    *btdpllsdadcclksel = (localVal & ((uint32_t)0x00000010)) >> 4;
    *btchopbgoscen = (localVal & ((uint32_t)0x00000008)) >> 3;
    *btchopbgoscbit = (localVal & ((uint32_t)0x00000006)) >> 1;
    *bttia2gpioen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the bt_dpll_drv_bit field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_dpll_drv_bit field's value will be returned.
 *
 * @return The current value of the bt_dpll_drv_bit field in the REG_34 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_drv_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0xFC000000)) >> 26);
}

/**
 * @brief Sets the bt_dpll_drv_bit field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdplldrvbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_drv_bit_setf(uint8_t btdplldrvbit)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, (REG_PL_RD(BT_RF_REG_34_ADDR) & ~((uint32_t)0xFC000000)) | (((uint32_t)btdplldrvbit << 26) & ((uint32_t)0xFC000000)));
}

/**
 * @brief Returns the current value of the bt_dpll_cnt_out field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_dpll_cnt_out field's value will be returned.
 *
 * @return The current value of the bt_dpll_cnt_out field in the REG_34 register.
 */
__INLINE uint32_t bt_rf_bt_dpll_cnt_out_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x03FFFE00)) >> 9);
}

/**
 * @brief Returns the current value of the bt_dpll_img_cal_mode field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_dpll_img_cal_mode field's value will be returned.
 *
 * @return The current value of the bt_dpll_img_cal_mode field in the REG_34 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_img_cal_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the bt_dpll_img_cal_mode field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllimgcalmode - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_img_cal_mode_setf(uint8_t btdpllimgcalmode)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, (REG_PL_RD(BT_RF_REG_34_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)btdpllimgcalmode << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the bt_dpll2wf_img5g_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_dpll2wf_img5g_en field's value will be returned.
 *
 * @return The current value of the bt_dpll2wf_img5g_en field in the REG_34 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_2wf_img_5g_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the bt_dpll2wf_img5g_en field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpll2wfimg5gen - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_2wf_img_5g_en_setf(uint8_t btdpll2wfimg5gen)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, (REG_PL_RD(BT_RF_REG_34_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)btdpll2wfimg5gen << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the bt_dpll2wf_img24g_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_dpll2wf_img24g_en field's value will be returned.
 *
 * @return The current value of the bt_dpll2wf_img24g_en field in the REG_34 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_2wf_img_24g_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the bt_dpll2wf_img24g_en field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpll2wfimg24gen - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_2wf_img_24g_en_setf(uint8_t btdpll2wfimg24gen)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, (REG_PL_RD(BT_RF_REG_34_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)btdpll2wfimg24gen << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the bt_dpll_chop_clk_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_dpll_chop_clk_en field's value will be returned.
 *
 * @return The current value of the bt_dpll_chop_clk_en field in the REG_34 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_chop_clk_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the bt_dpll_chop_clk_en field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllchopclken - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_chop_clk_en_setf(uint8_t btdpllchopclken)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, (REG_PL_RD(BT_RF_REG_34_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)btdpllchopclken << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the bt_dpll_sdadc_clk_sel field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_dpll_sdadc_clk_sel field's value will be returned.
 *
 * @return The current value of the bt_dpll_sdadc_clk_sel field in the REG_34 register.
 */
__INLINE uint8_t bt_rf_bt_dpll_sdadc_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the bt_dpll_sdadc_clk_sel field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdpllsdadcclksel - The value to set the field to.
 */
__INLINE void bt_rf_bt_dpll_sdadc_clk_sel_setf(uint8_t btdpllsdadcclksel)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, (REG_PL_RD(BT_RF_REG_34_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)btdpllsdadcclksel << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the bt_chop_bg_osc_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_chop_bg_osc_en field's value will be returned.
 *
 * @return The current value of the bt_chop_bg_osc_en field in the REG_34 register.
 */
__INLINE uint8_t bt_rf_bt_chop_bg_osc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the bt_chop_bg_osc_en field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btchopbgoscen - The value to set the field to.
 */
__INLINE void bt_rf_bt_chop_bg_osc_en_setf(uint8_t btchopbgoscen)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, (REG_PL_RD(BT_RF_REG_34_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)btchopbgoscen << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the bt_chop_bg_osc_bit field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_chop_bg_osc_bit field's value will be returned.
 *
 * @return The current value of the bt_chop_bg_osc_bit field in the REG_34 register.
 */
__INLINE uint8_t bt_rf_bt_chop_bg_osc_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000006)) >> 1);
}

/**
 * @brief Sets the bt_chop_bg_osc_bit field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btchopbgoscbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_chop_bg_osc_bit_setf(uint8_t btchopbgoscbit)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, (REG_PL_RD(BT_RF_REG_34_ADDR) & ~((uint32_t)0x00000006)) | (((uint32_t)btchopbgoscbit << 1) & ((uint32_t)0x00000006)));
}

/**
 * @brief Returns the current value of the bt_tia2gpio_en field in the REG_34 register.
 *
 * The REG_34 register will be read and the bt_tia2gpio_en field's value will be returned.
 *
 * @return The current value of the bt_tia2gpio_en field in the REG_34 register.
 */
__INLINE uint8_t bt_rf_bt_tia_2gpio_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_34_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the bt_tia2gpio_en field of the REG_34 register.
 *
 * The REG_34 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] bttia2gpioen - The value to set the field to.
 */
__INLINE void bt_rf_bt_tia_2gpio_en_setf(uint8_t bttia2gpioen)
{
    REG_PL_WR(BT_RF_REG_34_ADDR, (REG_PL_RD(BT_RF_REG_34_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)bttia2gpioen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_38 register definitions
 * <table>
 * <caption id="REG_38_BF">REG_38 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>27:20 <td>       bt_agc_rsvd <td>W <td>R <td>0xF0
 * <tr><td>19:12 <td>       bt_apc_rsvd <td>W <td>R <td>0xF0
 * <tr><td>11:04 <td>       bt_rsvd_bit <td>R <td>R/W <td>0xF0
 * <tr><td>03:00 <td>  bt_rsvd_read_bit <td>W <td>R <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the REG_38 register
#define BT_RF_REG_38_ADDR   0x40622038
/// Offset of the REG_38 register from the base address
#define BT_RF_REG_38_OFFSET 0x00000038
/// Index of the REG_38 register
#define BT_RF_REG_38_INDEX  0x0000000E
/// Reset value of the REG_38 register
#define BT_RF_REG_38_RESET  0x0F0F0F00

/**
 * @brief Returns the current value of the REG_38 register.
 * The REG_38 register will be read and its value returned.
 * @return The current value of the REG_38 register.
 */
__INLINE uint32_t bt_rf_reg_38_get(void)
{
    return REG_PL_RD(BT_RF_REG_38_ADDR);
}

/**
 * @brief Sets the REG_38 register to a value.
 * The REG_38 register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_reg_38_set(uint32_t value)
{
    REG_PL_WR(BT_RF_REG_38_ADDR, value);
}

// field definitions
/// BT_AGC_RSVD field mask
#define BT_RF_BT_AGC_RSVD_MASK        ((uint32_t)0x0FF00000)
/// BT_AGC_RSVD field LSB position
#define BT_RF_BT_AGC_RSVD_LSB         20
/// BT_AGC_RSVD field width
#define BT_RF_BT_AGC_RSVD_WIDTH       ((uint32_t)0x00000008)
/// BT_APC_RSVD field mask
#define BT_RF_BT_APC_RSVD_MASK        ((uint32_t)0x000FF000)
/// BT_APC_RSVD field LSB position
#define BT_RF_BT_APC_RSVD_LSB         12
/// BT_APC_RSVD field width
#define BT_RF_BT_APC_RSVD_WIDTH       ((uint32_t)0x00000008)
/// BT_RSVD_BIT field mask
#define BT_RF_BT_RSVD_BIT_MASK        ((uint32_t)0x00000FF0)
/// BT_RSVD_BIT field LSB position
#define BT_RF_BT_RSVD_BIT_LSB         4
/// BT_RSVD_BIT field width
#define BT_RF_BT_RSVD_BIT_WIDTH       ((uint32_t)0x00000008)
/// BT_RSVD_READ_BIT field mask
#define BT_RF_BT_RSVD_READ_BIT_MASK   ((uint32_t)0x0000000F)
/// BT_RSVD_READ_BIT field LSB position
#define BT_RF_BT_RSVD_READ_BIT_LSB    0
/// BT_RSVD_READ_BIT field width
#define BT_RF_BT_RSVD_READ_BIT_WIDTH  ((uint32_t)0x00000004)

/// BT_AGC_RSVD field reset value
#define BT_RF_BT_AGC_RSVD_RST         0xF0
/// BT_APC_RSVD field reset value
#define BT_RF_BT_APC_RSVD_RST         0xF0
/// BT_RSVD_BIT field reset value
#define BT_RF_BT_RSVD_BIT_RST         0xF0
/// BT_RSVD_READ_BIT field reset value
#define BT_RF_BT_RSVD_READ_BIT_RST    0x0

/**
 * @brief Unpacks REG_38's fields from current value of the REG_38 register.
 *
 * Reads the REG_38 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btagcrsvd - Will be populated with the current value of this field from the register.
 * @param[out] btapcrsvd - Will be populated with the current value of this field from the register.
 * @param[out] btrsvdbit - Will be populated with the current value of this field from the register.
 * @param[out] btrsvdreadbit - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_reg_38_unpack(uint8_t* btagcrsvd, uint8_t* btapcrsvd, uint8_t* btrsvdbit, uint8_t* btrsvdreadbit)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_38_ADDR);

    *btagcrsvd = (localVal & ((uint32_t)0x0FF00000)) >> 20;
    *btapcrsvd = (localVal & ((uint32_t)0x000FF000)) >> 12;
    *btrsvdbit = (localVal & ((uint32_t)0x00000FF0)) >> 4;
    *btrsvdreadbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the bt_agc_rsvd field in the REG_38 register.
 *
 * The REG_38 register will be read and the bt_agc_rsvd field's value will be returned.
 *
 * @return The current value of the bt_agc_rsvd field in the REG_38 register.
 */
__INLINE uint8_t bt_rf_bt_agc_rsvd_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x0FF00000)) >> 20);
}

/**
 * @brief Returns the current value of the bt_apc_rsvd field in the REG_38 register.
 *
 * The REG_38 register will be read and the bt_apc_rsvd field's value will be returned.
 *
 * @return The current value of the bt_apc_rsvd field in the REG_38 register.
 */
__INLINE uint8_t bt_rf_bt_apc_rsvd_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x000FF000)) >> 12);
}

/**
 * @brief Returns the current value of the bt_rsvd_bit field in the REG_38 register.
 *
 * The REG_38 register will be read and the bt_rsvd_bit field's value will be returned.
 *
 * @return The current value of the bt_rsvd_bit field in the REG_38 register.
 */
__INLINE uint8_t bt_rf_bt_rsvd_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x00000FF0)) >> 4);
}

/**
 * @brief Sets the bt_rsvd_bit field of the REG_38 register.
 *
 * The REG_38 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btrsvdbit - The value to set the field to.
 */
__INLINE void bt_rf_bt_rsvd_bit_setf(uint8_t btrsvdbit)
{
    REG_PL_WR(BT_RF_REG_38_ADDR, ((uint32_t)btrsvdbit << 4) & ((uint32_t)0x00000FF0));
}

/**
 * @brief Returns the current value of the bt_rsvd_read_bit field in the REG_38 register.
 *
 * The REG_38 register will be read and the bt_rsvd_read_bit field's value will be returned.
 *
 * @return The current value of the bt_rsvd_read_bit field in the REG_38 register.
 */
__INLINE uint8_t bt_rf_bt_rsvd_read_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_REG_38_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/// @}

/**
 * @name BT_SOFT_RESET_REG register definitions
 * <table>
 * <caption id="BT_SOFT_RESET_REG_BF">BT_SOFT_RESET_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>00 <td>        soft_reset <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the BT_SOFT_RESET_REG register
#define BT_RF_BT_SOFT_RESET_REG_ADDR   0x4062203C
/// Offset of the BT_SOFT_RESET_REG register from the base address
#define BT_RF_BT_SOFT_RESET_REG_OFFSET 0x0000003C
/// Index of the BT_SOFT_RESET_REG register
#define BT_RF_BT_SOFT_RESET_REG_INDEX  0x0000000F
/// Reset value of the BT_SOFT_RESET_REG register
#define BT_RF_BT_SOFT_RESET_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the BT_SOFT_RESET_REG register.
 * The BT_SOFT_RESET_REG register will be read and its value returned.
 * @return The current value of the BT_SOFT_RESET_REG register.
 */
__INLINE uint32_t bt_rf_bt_soft_reset_reg_get(void)
{
    return REG_PL_RD(BT_RF_BT_SOFT_RESET_REG_ADDR);
}

/**
 * @brief Sets the BT_SOFT_RESET_REG register to a value.
 * The BT_SOFT_RESET_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_bt_soft_reset_reg_set(uint32_t value)
{
    REG_PL_WR(BT_RF_BT_SOFT_RESET_REG_ADDR, value);
}

// field definitions
/// SOFT_RESET field bit
#define BT_RF_SOFT_RESET_BIT    ((uint32_t)0x00000001)
/// SOFT_RESET field position
#define BT_RF_SOFT_RESET_POS    0

/// SOFT_RESET field reset value
#define BT_RF_SOFT_RESET_RST    0x0

/**
 * @brief Returns the current value of the soft_reset field in the BT_SOFT_RESET_REG register.
 *
 * The BT_SOFT_RESET_REG register will be read and the soft_reset field's value will be returned.
 *
 * @return The current value of the soft_reset field in the BT_SOFT_RESET_REG register.
 */
__INLINE uint8_t bt_rf_soft_reset_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_SOFT_RESET_REG_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the soft_reset field of the BT_SOFT_RESET_REG register.
 *
 * The BT_SOFT_RESET_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] softreset - The value to set the field to.
 */
__INLINE void bt_rf_soft_reset_setf(uint8_t softreset)
{
    REG_PL_WR(BT_RF_BT_SOFT_RESET_REG_ADDR, ((uint32_t)softreset << 0) & ((uint32_t)0x00000001));
}

/// @}

/**
 * @name BT_MAN_CRTL_REG register definitions
 * <table>
 * <caption id="BT_MAN_CRTL_REG_BF">BT_MAN_CRTL_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>19 <td>   bt_gro_rstn_sel <td>R <td>R/W <td>1
 * <tr><td>18 <td>             pwron <td>R <td>R/W <td>0
 * <tr><td>17 <td>          twson_dr <td>R <td>R/W <td>1
 * <tr><td>16 <td>         twson_reg <td>R <td>R/W <td>0
 * <tr><td>15 <td>           txon_dr <td>R <td>R/W <td>0
 * <tr><td>14 <td>          txon_reg <td>R <td>R/W <td>0
 * <tr><td>13 <td>           rxon_dr <td>R <td>R/W <td>0
 * <tr><td>12 <td>          rxon_reg <td>R <td>R/W <td>0
 * <tr><td>11 <td>  rx_gain_dr_pulse <td>R <td>R/W <td>0
 * <tr><td>10 <td>        rx_gain_dr <td>R <td>R/W <td>0
 * <tr><td>09:06 <td>       rx_gain_reg <td>R <td>R/W <td>0x0
 * <tr><td>05 <td>  tx_gain_dr_pulse <td>R <td>R/W <td>0
 * <tr><td>04 <td>        tx_gain_dr <td>R <td>R/W <td>0
 * <tr><td>03:00 <td>       tx_gain_reg <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the BT_MAN_CRTL_REG register
#define BT_RF_BT_MAN_CRTL_REG_ADDR   0x40622040
/// Offset of the BT_MAN_CRTL_REG register from the base address
#define BT_RF_BT_MAN_CRTL_REG_OFFSET 0x00000040
/// Index of the BT_MAN_CRTL_REG register
#define BT_RF_BT_MAN_CRTL_REG_INDEX  0x00000010
/// Reset value of the BT_MAN_CRTL_REG register
#define BT_RF_BT_MAN_CRTL_REG_RESET  0x000A0000

/**
 * @brief Returns the current value of the BT_MAN_CRTL_REG register.
 * The BT_MAN_CRTL_REG register will be read and its value returned.
 * @return The current value of the BT_MAN_CRTL_REG register.
 */
__INLINE uint32_t bt_rf_bt_man_crtl_reg_get(void)
{
    return REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
}

/**
 * @brief Sets the BT_MAN_CRTL_REG register to a value.
 * The BT_MAN_CRTL_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_bt_man_crtl_reg_set(uint32_t value)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, value);
}

// field definitions
/// BT_GRO_RSTN_SEL field bit
#define BT_RF_BT_GRO_RSTN_SEL_BIT     ((uint32_t)0x00080000)
/// BT_GRO_RSTN_SEL field position
#define BT_RF_BT_GRO_RSTN_SEL_POS     19
/// PWRON field bit
#define BT_RF_PWRON_BIT               ((uint32_t)0x00040000)
/// PWRON field position
#define BT_RF_PWRON_POS               18
/// TWSON_DR field bit
#define BT_RF_TWSON_DR_BIT            ((uint32_t)0x00020000)
/// TWSON_DR field position
#define BT_RF_TWSON_DR_POS            17
/// TWSON_REG field bit
#define BT_RF_TWSON_REG_BIT           ((uint32_t)0x00010000)
/// TWSON_REG field position
#define BT_RF_TWSON_REG_POS           16
/// TXON_DR field bit
#define BT_RF_TXON_DR_BIT             ((uint32_t)0x00008000)
/// TXON_DR field position
#define BT_RF_TXON_DR_POS             15
/// TXON_REG field bit
#define BT_RF_TXON_REG_BIT            ((uint32_t)0x00004000)
/// TXON_REG field position
#define BT_RF_TXON_REG_POS            14
/// RXON_DR field bit
#define BT_RF_RXON_DR_BIT             ((uint32_t)0x00002000)
/// RXON_DR field position
#define BT_RF_RXON_DR_POS             13
/// RXON_REG field bit
#define BT_RF_RXON_REG_BIT            ((uint32_t)0x00001000)
/// RXON_REG field position
#define BT_RF_RXON_REG_POS            12
/// RX_GAIN_DR_PULSE field bit
#define BT_RF_RX_GAIN_DR_PULSE_BIT    ((uint32_t)0x00000800)
/// RX_GAIN_DR_PULSE field position
#define BT_RF_RX_GAIN_DR_PULSE_POS    11
/// RX_GAIN_DR field bit
#define BT_RF_RX_GAIN_DR_BIT          ((uint32_t)0x00000400)
/// RX_GAIN_DR field position
#define BT_RF_RX_GAIN_DR_POS          10
/// RX_GAIN_REG field mask
#define BT_RF_RX_GAIN_REG_MASK        ((uint32_t)0x000003C0)
/// RX_GAIN_REG field LSB position
#define BT_RF_RX_GAIN_REG_LSB         6
/// RX_GAIN_REG field width
#define BT_RF_RX_GAIN_REG_WIDTH       ((uint32_t)0x00000004)
/// TX_GAIN_DR_PULSE field bit
#define BT_RF_TX_GAIN_DR_PULSE_BIT    ((uint32_t)0x00000020)
/// TX_GAIN_DR_PULSE field position
#define BT_RF_TX_GAIN_DR_PULSE_POS    5
/// TX_GAIN_DR field bit
#define BT_RF_TX_GAIN_DR_BIT          ((uint32_t)0x00000010)
/// TX_GAIN_DR field position
#define BT_RF_TX_GAIN_DR_POS          4
/// TX_GAIN_REG field mask
#define BT_RF_TX_GAIN_REG_MASK        ((uint32_t)0x0000000F)
/// TX_GAIN_REG field LSB position
#define BT_RF_TX_GAIN_REG_LSB         0
/// TX_GAIN_REG field width
#define BT_RF_TX_GAIN_REG_WIDTH       ((uint32_t)0x00000004)

/// BT_GRO_RSTN_SEL field reset value
#define BT_RF_BT_GRO_RSTN_SEL_RST     0x1
/// PWRON field reset value
#define BT_RF_PWRON_RST               0x0
/// TWSON_DR field reset value
#define BT_RF_TWSON_DR_RST            0x1
/// TWSON_REG field reset value
#define BT_RF_TWSON_REG_RST           0x0
/// TXON_DR field reset value
#define BT_RF_TXON_DR_RST             0x0
/// TXON_REG field reset value
#define BT_RF_TXON_REG_RST            0x0
/// RXON_DR field reset value
#define BT_RF_RXON_DR_RST             0x0
/// RXON_REG field reset value
#define BT_RF_RXON_REG_RST            0x0
/// RX_GAIN_DR_PULSE field reset value
#define BT_RF_RX_GAIN_DR_PULSE_RST    0x0
/// RX_GAIN_DR field reset value
#define BT_RF_RX_GAIN_DR_RST          0x0
/// RX_GAIN_REG field reset value
#define BT_RF_RX_GAIN_REG_RST         0x0
/// TX_GAIN_DR_PULSE field reset value
#define BT_RF_TX_GAIN_DR_PULSE_RST    0x0
/// TX_GAIN_DR field reset value
#define BT_RF_TX_GAIN_DR_RST          0x0
/// TX_GAIN_REG field reset value
#define BT_RF_TX_GAIN_REG_RST         0x0

/**
 * @brief Constructs a value for the BT_MAN_CRTL_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btgrorstnsel - The value to use for the bt_gro_rstn_sel field.
 * @param[in] pwron - The value to use for the pwron field.
 * @param[in] twsondr - The value to use for the twson_dr field.
 * @param[in] twsonreg - The value to use for the twson_reg field.
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
__INLINE void bt_rf_bt_man_crtl_reg_pack(uint8_t btgrorstnsel, uint8_t pwron, uint8_t twsondr, uint8_t twsonreg, uint8_t txondr, uint8_t txonreg, uint8_t rxondr, uint8_t rxonreg, uint8_t rxgaindrpulse, uint8_t rxgaindr, uint8_t rxgainreg, uint8_t txgaindrpulse, uint8_t txgaindr, uint8_t txgainreg)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR,  ((uint32_t)btgrorstnsel << 19) | ((uint32_t)pwron << 18) | ((uint32_t)twsondr << 17) | ((uint32_t)twsonreg << 16) | ((uint32_t)txondr << 15) | ((uint32_t)txonreg << 14) | ((uint32_t)rxondr << 13) | ((uint32_t)rxonreg << 12) | ((uint32_t)rxgaindrpulse << 11) | ((uint32_t)rxgaindr << 10) | ((uint32_t)rxgainreg << 6) | ((uint32_t)txgaindrpulse << 5) | ((uint32_t)txgaindr << 4) | ((uint32_t)txgainreg << 0));
}

/**
 * @brief Unpacks BT_MAN_CRTL_REG's fields from current value of the BT_MAN_CRTL_REG register.
 *
 * Reads the BT_MAN_CRTL_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btgrorstnsel - Will be populated with the current value of this field from the register.
 * @param[out] pwron - Will be populated with the current value of this field from the register.
 * @param[out] twsondr - Will be populated with the current value of this field from the register.
 * @param[out] twsonreg - Will be populated with the current value of this field from the register.
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
__INLINE void bt_rf_bt_man_crtl_reg_unpack(uint8_t* btgrorstnsel, uint8_t* pwron, uint8_t* twsondr, uint8_t* twsonreg, uint8_t* txondr, uint8_t* txonreg, uint8_t* rxondr, uint8_t* rxonreg, uint8_t* rxgaindrpulse, uint8_t* rxgaindr, uint8_t* rxgainreg, uint8_t* txgaindrpulse, uint8_t* txgaindr, uint8_t* txgainreg)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);

    *btgrorstnsel = (localVal & ((uint32_t)0x00080000)) >> 19;
    *pwron = (localVal & ((uint32_t)0x00040000)) >> 18;
    *twsondr = (localVal & ((uint32_t)0x00020000)) >> 17;
    *twsonreg = (localVal & ((uint32_t)0x00010000)) >> 16;
    *txondr = (localVal & ((uint32_t)0x00008000)) >> 15;
    *txonreg = (localVal & ((uint32_t)0x00004000)) >> 14;
    *rxondr = (localVal & ((uint32_t)0x00002000)) >> 13;
    *rxonreg = (localVal & ((uint32_t)0x00001000)) >> 12;
    *rxgaindrpulse = (localVal & ((uint32_t)0x00000800)) >> 11;
    *rxgaindr = (localVal & ((uint32_t)0x00000400)) >> 10;
    *rxgainreg = (localVal & ((uint32_t)0x000003C0)) >> 6;
    *txgaindrpulse = (localVal & ((uint32_t)0x00000020)) >> 5;
    *txgaindr = (localVal & ((uint32_t)0x00000010)) >> 4;
    *txgainreg = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the bt_gro_rstn_sel field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the bt_gro_rstn_sel field's value will be returned.
 *
 * @return The current value of the bt_gro_rstn_sel field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_bt_gro_rstn_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the bt_gro_rstn_sel field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btgrorstnsel - The value to set the field to.
 */
__INLINE void bt_rf_bt_gro_rstn_sel_setf(uint8_t btgrorstnsel)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)btgrorstnsel << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the pwron field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the pwron field's value will be returned.
 *
 * @return The current value of the pwron field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_pwron_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the pwron field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] pwron - The value to set the field to.
 */
__INLINE void bt_rf_pwron_setf(uint8_t pwron)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)pwron << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the twson_dr field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the twson_dr field's value will be returned.
 *
 * @return The current value of the twson_dr field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_twson_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the twson_dr field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] twsondr - The value to set the field to.
 */
__INLINE void bt_rf_twson_dr_setf(uint8_t twsondr)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)twsondr << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the twson_reg field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the twson_reg field's value will be returned.
 *
 * @return The current value of the twson_reg field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_twson_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the twson_reg field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] twsonreg - The value to set the field to.
 */
__INLINE void bt_rf_twson_reg_setf(uint8_t twsonreg)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)twsonreg << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the txon_dr field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the txon_dr field's value will be returned.
 *
 * @return The current value of the txon_dr field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_txon_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the txon_dr field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txondr - The value to set the field to.
 */
__INLINE void bt_rf_txon_dr_setf(uint8_t txondr)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)txondr << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the txon_reg field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the txon_reg field's value will be returned.
 *
 * @return The current value of the txon_reg field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_txon_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the txon_reg field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txonreg - The value to set the field to.
 */
__INLINE void bt_rf_txon_reg_setf(uint8_t txonreg)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)txonreg << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the rxon_dr field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the rxon_dr field's value will be returned.
 *
 * @return The current value of the rxon_dr field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_rxon_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the rxon_dr field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxondr - The value to set the field to.
 */
__INLINE void bt_rf_rxon_dr_setf(uint8_t rxondr)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)rxondr << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the rxon_reg field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the rxon_reg field's value will be returned.
 *
 * @return The current value of the rxon_reg field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_rxon_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the rxon_reg field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxonreg - The value to set the field to.
 */
__INLINE void bt_rf_rxon_reg_setf(uint8_t rxonreg)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)rxonreg << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the rx_gain_dr_pulse field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the rx_gain_dr_pulse field's value will be returned.
 *
 * @return The current value of the rx_gain_dr_pulse field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_rx_gain_dr_pulse_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the rx_gain_dr_pulse field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgaindrpulse - The value to set the field to.
 */
__INLINE void bt_rf_rx_gain_dr_pulse_setf(uint8_t rxgaindrpulse)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)rxgaindrpulse << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the rx_gain_dr field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the rx_gain_dr field's value will be returned.
 *
 * @return The current value of the rx_gain_dr field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_rx_gain_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the rx_gain_dr field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgaindr - The value to set the field to.
 */
__INLINE void bt_rf_rx_gain_dr_setf(uint8_t rxgaindr)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)rxgaindr << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the rx_gain_reg field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the rx_gain_reg field's value will be returned.
 *
 * @return The current value of the rx_gain_reg field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_rx_gain_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x000003C0)) >> 6);
}

/**
 * @brief Sets the rx_gain_reg field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainreg - The value to set the field to.
 */
__INLINE void bt_rf_rx_gain_reg_setf(uint8_t rxgainreg)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x000003C0)) | (((uint32_t)rxgainreg << 6) & ((uint32_t)0x000003C0)));
}

/**
 * @brief Returns the current value of the tx_gain_dr_pulse field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the tx_gain_dr_pulse field's value will be returned.
 *
 * @return The current value of the tx_gain_dr_pulse field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_tx_gain_dr_pulse_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the tx_gain_dr_pulse field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgaindrpulse - The value to set the field to.
 */
__INLINE void bt_rf_tx_gain_dr_pulse_setf(uint8_t txgaindrpulse)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)txgaindrpulse << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the tx_gain_dr field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the tx_gain_dr field's value will be returned.
 *
 * @return The current value of the tx_gain_dr field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_tx_gain_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the tx_gain_dr field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgaindr - The value to set the field to.
 */
__INLINE void bt_rf_tx_gain_dr_setf(uint8_t txgaindr)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)txgaindr << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the tx_gain_reg field in the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read and the tx_gain_reg field's value will be returned.
 *
 * @return The current value of the tx_gain_reg field in the BT_MAN_CRTL_REG register.
 */
__INLINE uint8_t bt_rf_tx_gain_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the tx_gain_reg field of the BT_MAN_CRTL_REG register.
 *
 * The BT_MAN_CRTL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgainreg - The value to set the field to.
 */
__INLINE void bt_rf_tx_gain_reg_setf(uint8_t txgainreg)
{
    REG_PL_WR(BT_RF_BT_MAN_CRTL_REG_ADDR, (REG_PL_RD(BT_RF_BT_MAN_CRTL_REG_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)txgainreg << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name BT_CALCLK_REG register definitions
 * <table>
 * <caption id="BT_CALCLK_REG_BF">BT_CALCLK_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>13 <td>      debug_clk_en <td>R <td>R/W <td>0
 * <tr><td>12:11 <td>         debug_mux <td>R <td>R/W <td>0x0
 * <tr><td>10 <td>        cal_clk_en <td>R <td>R/W <td>0
 * <tr><td>09:00 <td>   cal_clk_div_num <td>R <td>R/W <td>0x4F
 * </table>
 *
 * @{
 */

/// Address of the BT_CALCLK_REG register
#define BT_RF_BT_CALCLK_REG_ADDR   0x40622044
/// Offset of the BT_CALCLK_REG register from the base address
#define BT_RF_BT_CALCLK_REG_OFFSET 0x00000044
/// Index of the BT_CALCLK_REG register
#define BT_RF_BT_CALCLK_REG_INDEX  0x00000011
/// Reset value of the BT_CALCLK_REG register
#define BT_RF_BT_CALCLK_REG_RESET  0x0000004F

/**
 * @brief Returns the current value of the BT_CALCLK_REG register.
 * The BT_CALCLK_REG register will be read and its value returned.
 * @return The current value of the BT_CALCLK_REG register.
 */
__INLINE uint32_t bt_rf_bt_calclk_reg_get(void)
{
    return REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR);
}

/**
 * @brief Sets the BT_CALCLK_REG register to a value.
 * The BT_CALCLK_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_bt_calclk_reg_set(uint32_t value)
{
    REG_PL_WR(BT_RF_BT_CALCLK_REG_ADDR, value);
}

// field definitions
/// DEBUG_CLK_EN field bit
#define BT_RF_DEBUG_CLK_EN_BIT       ((uint32_t)0x00002000)
/// DEBUG_CLK_EN field position
#define BT_RF_DEBUG_CLK_EN_POS       13
/// DEBUG_MUX field mask
#define BT_RF_DEBUG_MUX_MASK         ((uint32_t)0x00001800)
/// DEBUG_MUX field LSB position
#define BT_RF_DEBUG_MUX_LSB          11
/// DEBUG_MUX field width
#define BT_RF_DEBUG_MUX_WIDTH        ((uint32_t)0x00000002)
/// CAL_CLK_EN field bit
#define BT_RF_CAL_CLK_EN_BIT         ((uint32_t)0x00000400)
/// CAL_CLK_EN field position
#define BT_RF_CAL_CLK_EN_POS         10
/// CAL_CLK_DIV_NUM field mask
#define BT_RF_CAL_CLK_DIV_NUM_MASK   ((uint32_t)0x000003FF)
/// CAL_CLK_DIV_NUM field LSB position
#define BT_RF_CAL_CLK_DIV_NUM_LSB    0
/// CAL_CLK_DIV_NUM field width
#define BT_RF_CAL_CLK_DIV_NUM_WIDTH  ((uint32_t)0x0000000A)

/// DEBUG_CLK_EN field reset value
#define BT_RF_DEBUG_CLK_EN_RST       0x0
/// DEBUG_MUX field reset value
#define BT_RF_DEBUG_MUX_RST          0x0
/// CAL_CLK_EN field reset value
#define BT_RF_CAL_CLK_EN_RST         0x0
/// CAL_CLK_DIV_NUM field reset value
#define BT_RF_CAL_CLK_DIV_NUM_RST    0x4F

/**
 * @brief Constructs a value for the BT_CALCLK_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] debugclken - The value to use for the debug_clk_en field.
 * @param[in] debugmux - The value to use for the debug_mux field.
 * @param[in] calclken - The value to use for the cal_clk_en field.
 * @param[in] calclkdivnum - The value to use for the cal_clk_div_num field.
 */
__INLINE void bt_rf_bt_calclk_reg_pack(uint8_t debugclken, uint8_t debugmux, uint8_t calclken, uint16_t calclkdivnum)
{
    REG_PL_WR(BT_RF_BT_CALCLK_REG_ADDR,  ((uint32_t)debugclken << 13) | ((uint32_t)debugmux << 11) | ((uint32_t)calclken << 10) | ((uint32_t)calclkdivnum << 0));
}

/**
 * @brief Unpacks BT_CALCLK_REG's fields from current value of the BT_CALCLK_REG register.
 *
 * Reads the BT_CALCLK_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] debugclken - Will be populated with the current value of this field from the register.
 * @param[out] debugmux - Will be populated with the current value of this field from the register.
 * @param[out] calclken - Will be populated with the current value of this field from the register.
 * @param[out] calclkdivnum - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_bt_calclk_reg_unpack(uint8_t* debugclken, uint8_t* debugmux, uint8_t* calclken, uint16_t* calclkdivnum)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR);

    *debugclken = (localVal & ((uint32_t)0x00002000)) >> 13;
    *debugmux = (localVal & ((uint32_t)0x00001800)) >> 11;
    *calclken = (localVal & ((uint32_t)0x00000400)) >> 10;
    *calclkdivnum = (localVal & ((uint32_t)0x000003FF)) >> 0;
}

/**
 * @brief Returns the current value of the debug_clk_en field in the BT_CALCLK_REG register.
 *
 * The BT_CALCLK_REG register will be read and the debug_clk_en field's value will be returned.
 *
 * @return The current value of the debug_clk_en field in the BT_CALCLK_REG register.
 */
__INLINE uint8_t bt_rf_debug_clk_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the debug_clk_en field of the BT_CALCLK_REG register.
 *
 * The BT_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] debugclken - The value to set the field to.
 */
__INLINE void bt_rf_debug_clk_en_setf(uint8_t debugclken)
{
    REG_PL_WR(BT_RF_BT_CALCLK_REG_ADDR, (REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)debugclken << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the debug_mux field in the BT_CALCLK_REG register.
 *
 * The BT_CALCLK_REG register will be read and the debug_mux field's value will be returned.
 *
 * @return The current value of the debug_mux field in the BT_CALCLK_REG register.
 */
__INLINE uint8_t bt_rf_debug_mux_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x00001800)) >> 11);
}

/**
 * @brief Sets the debug_mux field of the BT_CALCLK_REG register.
 *
 * The BT_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] debugmux - The value to set the field to.
 */
__INLINE void bt_rf_debug_mux_setf(uint8_t debugmux)
{
    REG_PL_WR(BT_RF_BT_CALCLK_REG_ADDR, (REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR) & ~((uint32_t)0x00001800)) | (((uint32_t)debugmux << 11) & ((uint32_t)0x00001800)));
}

/**
 * @brief Returns the current value of the cal_clk_en field in the BT_CALCLK_REG register.
 *
 * The BT_CALCLK_REG register will be read and the cal_clk_en field's value will be returned.
 *
 * @return The current value of the cal_clk_en field in the BT_CALCLK_REG register.
 */
__INLINE uint8_t bt_rf_cal_clk_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the cal_clk_en field of the BT_CALCLK_REG register.
 *
 * The BT_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] calclken - The value to set the field to.
 */
__INLINE void bt_rf_cal_clk_en_setf(uint8_t calclken)
{
    REG_PL_WR(BT_RF_BT_CALCLK_REG_ADDR, (REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)calclken << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the cal_clk_div_num field in the BT_CALCLK_REG register.
 *
 * The BT_CALCLK_REG register will be read and the cal_clk_div_num field's value will be returned.
 *
 * @return The current value of the cal_clk_div_num field in the BT_CALCLK_REG register.
 */
__INLINE uint16_t bt_rf_cal_clk_div_num_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x000003FF)) >> 0);
}

/**
 * @brief Sets the cal_clk_div_num field of the BT_CALCLK_REG register.
 *
 * The BT_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] calclkdivnum - The value to set the field to.
 */
__INLINE void bt_rf_cal_clk_div_num_setf(uint16_t calclkdivnum)
{
    REG_PL_WR(BT_RF_BT_CALCLK_REG_ADDR, (REG_PL_RD(BT_RF_BT_CALCLK_REG_ADDR) & ~((uint32_t)0x000003FF)) | (((uint32_t)calclkdivnum << 0) & ((uint32_t)0x000003FF)));
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
#define BT_RF_GAIN_MEM_CTRL_REG_ADDR   0x40622048
/// Offset of the GAIN_MEM_CTRL_REG register from the base address
#define BT_RF_GAIN_MEM_CTRL_REG_OFFSET 0x00000048
/// Index of the GAIN_MEM_CTRL_REG register
#define BT_RF_GAIN_MEM_CTRL_REG_INDEX  0x00000012
/// Reset value of the GAIN_MEM_CTRL_REG register
#define BT_RF_GAIN_MEM_CTRL_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the GAIN_MEM_CTRL_REG register.
 * The GAIN_MEM_CTRL_REG register will be read and its value returned.
 * @return The current value of the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint32_t bt_rf_gain_mem_ctrl_reg_get(void)
{
    return REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR);
}

/**
 * @brief Sets the GAIN_MEM_CTRL_REG register to a value.
 * The GAIN_MEM_CTRL_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_gain_mem_ctrl_reg_set(uint32_t value)
{
    REG_PL_WR(BT_RF_GAIN_MEM_CTRL_REG_ADDR, value);
}

// field definitions
/// RXGAIN_MEM_CFG field bit
#define BT_RF_RXGAIN_MEM_CFG_BIT    ((uint32_t)0x00000040)
/// RXGAIN_MEM_CFG field position
#define BT_RF_RXGAIN_MEM_CFG_POS    6
/// CLK_RXGAIN_SEL field bit
#define BT_RF_CLK_RXGAIN_SEL_BIT    ((uint32_t)0x00000020)
/// CLK_RXGAIN_SEL field position
#define BT_RF_CLK_RXGAIN_SEL_POS    5
/// CLK_RXGAIN_EN field bit
#define BT_RF_CLK_RXGAIN_EN_BIT     ((uint32_t)0x00000010)
/// CLK_RXGAIN_EN field position
#define BT_RF_CLK_RXGAIN_EN_POS     4
/// TXGAIN_MEM_CFG field bit
#define BT_RF_TXGAIN_MEM_CFG_BIT    ((uint32_t)0x00000004)
/// TXGAIN_MEM_CFG field position
#define BT_RF_TXGAIN_MEM_CFG_POS    2
/// CLK_TXGAIN_SEL field bit
#define BT_RF_CLK_TXGAIN_SEL_BIT    ((uint32_t)0x00000002)
/// CLK_TXGAIN_SEL field position
#define BT_RF_CLK_TXGAIN_SEL_POS    1
/// CLK_TXGAIN_EN field bit
#define BT_RF_CLK_TXGAIN_EN_BIT     ((uint32_t)0x00000001)
/// CLK_TXGAIN_EN field position
#define BT_RF_CLK_TXGAIN_EN_POS     0

/// RXGAIN_MEM_CFG field reset value
#define BT_RF_RXGAIN_MEM_CFG_RST    0x0
/// CLK_RXGAIN_SEL field reset value
#define BT_RF_CLK_RXGAIN_SEL_RST    0x0
/// CLK_RXGAIN_EN field reset value
#define BT_RF_CLK_RXGAIN_EN_RST     0x0
/// TXGAIN_MEM_CFG field reset value
#define BT_RF_TXGAIN_MEM_CFG_RST    0x0
/// CLK_TXGAIN_SEL field reset value
#define BT_RF_CLK_TXGAIN_SEL_RST    0x0
/// CLK_TXGAIN_EN field reset value
#define BT_RF_CLK_TXGAIN_EN_RST     0x0

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
__INLINE void bt_rf_gain_mem_ctrl_reg_pack(uint8_t rxgainmemcfg, uint8_t clkrxgainsel, uint8_t clkrxgainen, uint8_t txgainmemcfg, uint8_t clktxgainsel, uint8_t clktxgainen)
{
    REG_PL_WR(BT_RF_GAIN_MEM_CTRL_REG_ADDR,  ((uint32_t)rxgainmemcfg << 6) | ((uint32_t)clkrxgainsel << 5) | ((uint32_t)clkrxgainen << 4) | ((uint32_t)txgainmemcfg << 2) | ((uint32_t)clktxgainsel << 1) | ((uint32_t)clktxgainen << 0));
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
__INLINE void bt_rf_gain_mem_ctrl_reg_unpack(uint8_t* rxgainmemcfg, uint8_t* clkrxgainsel, uint8_t* clkrxgainen, uint8_t* txgainmemcfg, uint8_t* clktxgainsel, uint8_t* clktxgainen)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR);

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
__INLINE uint8_t bt_rf_rxgain_mem_cfg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the rxgain_mem_cfg field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainmemcfg - The value to set the field to.
 */
__INLINE void bt_rf_rxgain_mem_cfg_setf(uint8_t rxgainmemcfg)
{
    REG_PL_WR(BT_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)rxgainmemcfg << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the clk_rxgain_sel field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the clk_rxgain_sel field's value will be returned.
 *
 * @return The current value of the clk_rxgain_sel field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t bt_rf_clk_rxgain_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the clk_rxgain_sel field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] clkrxgainsel - The value to set the field to.
 */
__INLINE void bt_rf_clk_rxgain_sel_setf(uint8_t clkrxgainsel)
{
    REG_PL_WR(BT_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)clkrxgainsel << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the clk_rxgain_en field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the clk_rxgain_en field's value will be returned.
 *
 * @return The current value of the clk_rxgain_en field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t bt_rf_clk_rxgain_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the clk_rxgain_en field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] clkrxgainen - The value to set the field to.
 */
__INLINE void bt_rf_clk_rxgain_en_setf(uint8_t clkrxgainen)
{
    REG_PL_WR(BT_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)clkrxgainen << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the txgain_mem_cfg field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the txgain_mem_cfg field's value will be returned.
 *
 * @return The current value of the txgain_mem_cfg field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t bt_rf_txgain_mem_cfg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the txgain_mem_cfg field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgainmemcfg - The value to set the field to.
 */
__INLINE void bt_rf_txgain_mem_cfg_setf(uint8_t txgainmemcfg)
{
    REG_PL_WR(BT_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)txgainmemcfg << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the clk_txgain_sel field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the clk_txgain_sel field's value will be returned.
 *
 * @return The current value of the clk_txgain_sel field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t bt_rf_clk_txgain_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the clk_txgain_sel field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] clktxgainsel - The value to set the field to.
 */
__INLINE void bt_rf_clk_txgain_sel_setf(uint8_t clktxgainsel)
{
    REG_PL_WR(BT_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)clktxgainsel << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the clk_txgain_en field in the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read and the clk_txgain_en field's value will be returned.
 *
 * @return The current value of the clk_txgain_en field in the GAIN_MEM_CTRL_REG register.
 */
__INLINE uint8_t bt_rf_clk_txgain_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the clk_txgain_en field of the GAIN_MEM_CTRL_REG register.
 *
 * The GAIN_MEM_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] clktxgainen - The value to set the field to.
 */
__INLINE void bt_rf_clk_txgain_en_setf(uint8_t clktxgainen)
{
    REG_PL_WR(BT_RF_GAIN_MEM_CTRL_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_CTRL_REG_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)clktxgainen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name GAIN_MEM_FETCH_REG register definitions
 * <table>
 * <caption id="GAIN_MEM_FETCH_REG_BF">GAIN_MEM_FETCH_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>rxgain_mem_fetch_p <td>R <td>R/W <td>0
 * <tr><td>19:16 <td>rxgain_mem_fetch_addr <td>R <td>R/W <td>0x0
 * <tr><td>15 <td>txgain_mem_fetch_p <td>R <td>R/W <td>0
 * <tr><td>03:00 <td>txgain_mem_fetch_addr <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the GAIN_MEM_FETCH_REG register
#define BT_RF_GAIN_MEM_FETCH_REG_ADDR   0x4062204C
/// Offset of the GAIN_MEM_FETCH_REG register from the base address
#define BT_RF_GAIN_MEM_FETCH_REG_OFFSET 0x0000004C
/// Index of the GAIN_MEM_FETCH_REG register
#define BT_RF_GAIN_MEM_FETCH_REG_INDEX  0x00000013
/// Reset value of the GAIN_MEM_FETCH_REG register
#define BT_RF_GAIN_MEM_FETCH_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the GAIN_MEM_FETCH_REG register.
 * The GAIN_MEM_FETCH_REG register will be read and its value returned.
 * @return The current value of the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint32_t bt_rf_gain_mem_fetch_reg_get(void)
{
    return REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR);
}

/**
 * @brief Sets the GAIN_MEM_FETCH_REG register to a value.
 * The GAIN_MEM_FETCH_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_gain_mem_fetch_reg_set(uint32_t value)
{
    REG_PL_WR(BT_RF_GAIN_MEM_FETCH_REG_ADDR, value);
}

// field definitions
/// RXGAIN_MEM_FETCH_P field bit
#define BT_RF_RXGAIN_MEM_FETCH_P_BIT       ((uint32_t)0x80000000)
/// RXGAIN_MEM_FETCH_P field position
#define BT_RF_RXGAIN_MEM_FETCH_P_POS       31
/// RXGAIN_MEM_FETCH_ADDR field mask
#define BT_RF_RXGAIN_MEM_FETCH_ADDR_MASK   ((uint32_t)0x000F0000)
/// RXGAIN_MEM_FETCH_ADDR field LSB position
#define BT_RF_RXGAIN_MEM_FETCH_ADDR_LSB    16
/// RXGAIN_MEM_FETCH_ADDR field width
#define BT_RF_RXGAIN_MEM_FETCH_ADDR_WIDTH  ((uint32_t)0x00000004)
/// TXGAIN_MEM_FETCH_P field bit
#define BT_RF_TXGAIN_MEM_FETCH_P_BIT       ((uint32_t)0x00008000)
/// TXGAIN_MEM_FETCH_P field position
#define BT_RF_TXGAIN_MEM_FETCH_P_POS       15
/// TXGAIN_MEM_FETCH_ADDR field mask
#define BT_RF_TXGAIN_MEM_FETCH_ADDR_MASK   ((uint32_t)0x0000000F)
/// TXGAIN_MEM_FETCH_ADDR field LSB position
#define BT_RF_TXGAIN_MEM_FETCH_ADDR_LSB    0
/// TXGAIN_MEM_FETCH_ADDR field width
#define BT_RF_TXGAIN_MEM_FETCH_ADDR_WIDTH  ((uint32_t)0x00000004)

/// RXGAIN_MEM_FETCH_P field reset value
#define BT_RF_RXGAIN_MEM_FETCH_P_RST       0x0
/// RXGAIN_MEM_FETCH_ADDR field reset value
#define BT_RF_RXGAIN_MEM_FETCH_ADDR_RST    0x0
/// TXGAIN_MEM_FETCH_P field reset value
#define BT_RF_TXGAIN_MEM_FETCH_P_RST       0x0
/// TXGAIN_MEM_FETCH_ADDR field reset value
#define BT_RF_TXGAIN_MEM_FETCH_ADDR_RST    0x0

/**
 * @brief Constructs a value for the GAIN_MEM_FETCH_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] rxgainmemfetchp - The value to use for the rxgain_mem_fetch_p field.
 * @param[in] rxgainmemfetchaddr - The value to use for the rxgain_mem_fetch_addr field.
 * @param[in] txgainmemfetchp - The value to use for the txgain_mem_fetch_p field.
 * @param[in] txgainmemfetchaddr - The value to use for the txgain_mem_fetch_addr field.
 */
__INLINE void bt_rf_gain_mem_fetch_reg_pack(uint8_t rxgainmemfetchp, uint8_t rxgainmemfetchaddr, uint8_t txgainmemfetchp, uint8_t txgainmemfetchaddr)
{
    REG_PL_WR(BT_RF_GAIN_MEM_FETCH_REG_ADDR,  ((uint32_t)rxgainmemfetchp << 31) | ((uint32_t)rxgainmemfetchaddr << 16) | ((uint32_t)txgainmemfetchp << 15) | ((uint32_t)txgainmemfetchaddr << 0));
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
__INLINE void bt_rf_gain_mem_fetch_reg_unpack(uint8_t* rxgainmemfetchp, uint8_t* rxgainmemfetchaddr, uint8_t* txgainmemfetchp, uint8_t* txgainmemfetchaddr)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR);

    *rxgainmemfetchp = (localVal & ((uint32_t)0x80000000)) >> 31;
    *rxgainmemfetchaddr = (localVal & ((uint32_t)0x000F0000)) >> 16;
    *txgainmemfetchp = (localVal & ((uint32_t)0x00008000)) >> 15;
    *txgainmemfetchaddr = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the rxgain_mem_fetch_p field in the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read and the rxgain_mem_fetch_p field's value will be returned.
 *
 * @return The current value of the rxgain_mem_fetch_p field in the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint8_t bt_rf_rxgain_mem_fetch_p_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the rxgain_mem_fetch_p field of the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainmemfetchp - The value to set the field to.
 */
__INLINE void bt_rf_rxgain_mem_fetch_p_setf(uint8_t rxgainmemfetchp)
{
    REG_PL_WR(BT_RF_GAIN_MEM_FETCH_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)rxgainmemfetchp << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the rxgain_mem_fetch_addr field in the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read and the rxgain_mem_fetch_addr field's value will be returned.
 *
 * @return The current value of the rxgain_mem_fetch_addr field in the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint8_t bt_rf_rxgain_mem_fetch_addr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR);
    return ((localVal & ((uint32_t)0x000F0000)) >> 16);
}

/**
 * @brief Sets the rxgain_mem_fetch_addr field of the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainmemfetchaddr - The value to set the field to.
 */
__INLINE void bt_rf_rxgain_mem_fetch_addr_setf(uint8_t rxgainmemfetchaddr)
{
    REG_PL_WR(BT_RF_GAIN_MEM_FETCH_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR) & ~((uint32_t)0x000F0000)) | (((uint32_t)rxgainmemfetchaddr << 16) & ((uint32_t)0x000F0000)));
}

/**
 * @brief Returns the current value of the txgain_mem_fetch_p field in the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read and the txgain_mem_fetch_p field's value will be returned.
 *
 * @return The current value of the txgain_mem_fetch_p field in the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint8_t bt_rf_txgain_mem_fetch_p_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the txgain_mem_fetch_p field of the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgainmemfetchp - The value to set the field to.
 */
__INLINE void bt_rf_txgain_mem_fetch_p_setf(uint8_t txgainmemfetchp)
{
    REG_PL_WR(BT_RF_GAIN_MEM_FETCH_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)txgainmemfetchp << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the txgain_mem_fetch_addr field in the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read and the txgain_mem_fetch_addr field's value will be returned.
 *
 * @return The current value of the txgain_mem_fetch_addr field in the GAIN_MEM_FETCH_REG register.
 */
__INLINE uint8_t bt_rf_txgain_mem_fetch_addr_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the txgain_mem_fetch_addr field of the GAIN_MEM_FETCH_REG register.
 *
 * The GAIN_MEM_FETCH_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] txgainmemfetchaddr - The value to set the field to.
 */
__INLINE void bt_rf_txgain_mem_fetch_addr_setf(uint8_t txgainmemfetchaddr)
{
    REG_PL_WR(BT_RF_GAIN_MEM_FETCH_REG_ADDR, (REG_PL_RD(BT_RF_GAIN_MEM_FETCH_REG_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)txgainmemfetchaddr << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name PU_DONE_REG register definitions
 * <table>
 * <caption id="PU_DONE_REG_BF">PU_DONE_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>02 <td>        pwron_done <td>W <td>R <td>0
 * <tr><td>01 <td>         rxon_done <td>W <td>R <td>0
 * <tr><td>00 <td>         txon_done <td>W <td>R <td>0
 * </table>
 *
 * @{
 */

/// Address of the PU_DONE_REG register
#define BT_RF_PU_DONE_REG_ADDR   0x40622050
/// Offset of the PU_DONE_REG register from the base address
#define BT_RF_PU_DONE_REG_OFFSET 0x00000050
/// Index of the PU_DONE_REG register
#define BT_RF_PU_DONE_REG_INDEX  0x00000014
/// Reset value of the PU_DONE_REG register
#define BT_RF_PU_DONE_REG_RESET  0x00000000

/**
 * @brief Returns the current value of the PU_DONE_REG register.
 * The PU_DONE_REG register will be read and its value returned.
 * @return The current value of the PU_DONE_REG register.
 */
__INLINE uint32_t bt_rf_pu_done_reg_get(void)
{
    return REG_PL_RD(BT_RF_PU_DONE_REG_ADDR);
}

// field definitions
/// PWRON_DONE field bit
#define BT_RF_PWRON_DONE_BIT    ((uint32_t)0x00000004)
/// PWRON_DONE field position
#define BT_RF_PWRON_DONE_POS    2
/// RXON_DONE field bit
#define BT_RF_RXON_DONE_BIT     ((uint32_t)0x00000002)
/// RXON_DONE field position
#define BT_RF_RXON_DONE_POS     1
/// TXON_DONE field bit
#define BT_RF_TXON_DONE_BIT     ((uint32_t)0x00000001)
/// TXON_DONE field position
#define BT_RF_TXON_DONE_POS     0

/// PWRON_DONE field reset value
#define BT_RF_PWRON_DONE_RST    0x0
/// RXON_DONE field reset value
#define BT_RF_RXON_DONE_RST     0x0
/// TXON_DONE field reset value
#define BT_RF_TXON_DONE_RST     0x0

/**
 * @brief Unpacks PU_DONE_REG's fields from current value of the PU_DONE_REG register.
 *
 * Reads the PU_DONE_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] pwrondone - Will be populated with the current value of this field from the register.
 * @param[out] rxondone - Will be populated with the current value of this field from the register.
 * @param[out] txondone - Will be populated with the current value of this field from the register.
 */
__INLINE void bt_rf_pu_done_reg_unpack(uint8_t* pwrondone, uint8_t* rxondone, uint8_t* txondone)
{
    uint32_t localVal = REG_PL_RD(BT_RF_PU_DONE_REG_ADDR);

    *pwrondone = (localVal & ((uint32_t)0x00000004)) >> 2;
    *rxondone = (localVal & ((uint32_t)0x00000002)) >> 1;
    *txondone = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the pwron_done field in the PU_DONE_REG register.
 *
 * The PU_DONE_REG register will be read and the pwron_done field's value will be returned.
 *
 * @return The current value of the pwron_done field in the PU_DONE_REG register.
 */
__INLINE uint8_t bt_rf_pwron_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_PU_DONE_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Returns the current value of the rxon_done field in the PU_DONE_REG register.
 *
 * The PU_DONE_REG register will be read and the rxon_done field's value will be returned.
 *
 * @return The current value of the rxon_done field in the PU_DONE_REG register.
 */
__INLINE uint8_t bt_rf_rxon_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_PU_DONE_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Returns the current value of the txon_done field in the PU_DONE_REG register.
 *
 * The PU_DONE_REG register will be read and the txon_done field's value will be returned.
 *
 * @return The current value of the txon_done field in the PU_DONE_REG register.
 */
__INLINE uint8_t bt_rf_txon_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_PU_DONE_REG_ADDR);
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
#define BT_RF_DIG_RESERVED_REG_ADDR   0x40622054
/// Offset of the DIG_RESERVED_REG register from the base address
#define BT_RF_DIG_RESERVED_REG_OFFSET 0x00000054
/// Index of the DIG_RESERVED_REG register
#define BT_RF_DIG_RESERVED_REG_INDEX  0x00000015
/// Reset value of the DIG_RESERVED_REG register
#define BT_RF_DIG_RESERVED_REG_RESET  0xFFFF0000

/**
 * @brief Returns the current value of the DIG_RESERVED_REG register.
 * The DIG_RESERVED_REG register will be read and its value returned.
 * @return The current value of the DIG_RESERVED_REG register.
 */
__INLINE uint32_t bt_rf_dig_reserved_reg_get(void)
{
    return REG_PL_RD(BT_RF_DIG_RESERVED_REG_ADDR);
}

/**
 * @brief Sets the DIG_RESERVED_REG register to a value.
 * The DIG_RESERVED_REG register will be written.
 * @param value - The value to write.
 */
__INLINE void bt_rf_dig_reserved_reg_set(uint32_t value)
{
    REG_PL_WR(BT_RF_DIG_RESERVED_REG_ADDR, value);
}

// field definitions
/// DIG_RESERVED_REG field mask
#define BT_RF_DIG_RESERVED_REG_MASK   ((uint32_t)0xFFFFFFFF)
/// DIG_RESERVED_REG field LSB position
#define BT_RF_DIG_RESERVED_REG_LSB    0
/// DIG_RESERVED_REG field width
#define BT_RF_DIG_RESERVED_REG_WIDTH  ((uint32_t)0x00000020)

/// DIG_RESERVED_REG field reset value
#define BT_RF_DIG_RESERVED_REG_RST    0xFFFF0000

/**
 * @brief Returns the current value of the dig_reserved_reg field in the DIG_RESERVED_REG register.
 *
 * The DIG_RESERVED_REG register will be read and the dig_reserved_reg field's value will be returned.
 *
 * @return The current value of the dig_reserved_reg field in the DIG_RESERVED_REG register.
 */
__INLINE uint32_t bt_rf_dig_reserved_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_DIG_RESERVED_REG_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the dig_reserved_reg field of the DIG_RESERVED_REG register.
 *
 * The DIG_RESERVED_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] digreservedreg - The value to set the field to.
 */
__INLINE void bt_rf_dig_reserved_reg_setf(uint32_t digreservedreg)
{
    REG_PL_WR(BT_RF_DIG_RESERVED_REG_ADDR, ((uint32_t)digreservedreg << 0) & ((uint32_t)0xFFFFFFFF));
}

/// @}

/**
 * @name AGC_TABLE_OUT_REG0 register definitions
 * <table>
 * <caption id="AGC_TABLE_OUT_REG0_BF">AGC_TABLE_OUT_REG0 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   agc_table_out_0 <td>W <td>R <td>0x6F2663AB
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG0 register
#define BT_RF_AGC_TABLE_OUT_REG0_ADDR   0x40622058
/// Offset of the AGC_TABLE_OUT_REG0 register from the base address
#define BT_RF_AGC_TABLE_OUT_REG0_OFFSET 0x00000058
/// Index of the AGC_TABLE_OUT_REG0 register
#define BT_RF_AGC_TABLE_OUT_REG0_INDEX  0x00000016
/// Reset value of the AGC_TABLE_OUT_REG0 register
#define BT_RF_AGC_TABLE_OUT_REG0_RESET  0x6F2663AB

/**
 * @brief Returns the current value of the AGC_TABLE_OUT_REG0 register.
 * The AGC_TABLE_OUT_REG0 register will be read and its value returned.
 * @return The current value of the AGC_TABLE_OUT_REG0 register.
 */
__INLINE uint32_t bt_rf_agc_table_out_reg0_get(void)
{
    return REG_PL_RD(BT_RF_AGC_TABLE_OUT_REG0_ADDR);
}

// field definitions
/// AGC_TABLE_OUT__0 field mask
#define BT_RF_AGC_TABLE_OUT__0_MASK   ((uint32_t)0xFFFFFFFF)
/// AGC_TABLE_OUT__0 field LSB position
#define BT_RF_AGC_TABLE_OUT__0_LSB    0
/// AGC_TABLE_OUT__0 field width
#define BT_RF_AGC_TABLE_OUT__0_WIDTH  ((uint32_t)0x00000020)

/// AGC_TABLE_OUT__0 field reset value
#define BT_RF_AGC_TABLE_OUT__0_RST    0x6F2663AB

/**
 * @brief Returns the current value of the agc_table_out_0 field in the AGC_TABLE_OUT_REG0 register.
 *
 * The AGC_TABLE_OUT_REG0 register will be read and the agc_table_out_0 field's value will be returned.
 *
 * @return The current value of the agc_table_out_0 field in the AGC_TABLE_OUT_REG0 register.
 */
__INLINE uint32_t bt_rf_agc_table_out__0_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_AGC_TABLE_OUT_REG0_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name AGC_TABLE_OUT_REG1 register definitions
 * <table>
 * <caption id="AGC_TABLE_OUT_REG1_BF">AGC_TABLE_OUT_REG1 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   agc_table_out_1 <td>W <td>R <td>0x83DB
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG1 register
#define BT_RF_AGC_TABLE_OUT_REG1_ADDR   0x4062205C
/// Offset of the AGC_TABLE_OUT_REG1 register from the base address
#define BT_RF_AGC_TABLE_OUT_REG1_OFFSET 0x0000005C
/// Index of the AGC_TABLE_OUT_REG1 register
#define BT_RF_AGC_TABLE_OUT_REG1_INDEX  0x00000017
/// Reset value of the AGC_TABLE_OUT_REG1 register
#define BT_RF_AGC_TABLE_OUT_REG1_RESET  0x000083DB

/**
 * @brief Returns the current value of the AGC_TABLE_OUT_REG1 register.
 * The AGC_TABLE_OUT_REG1 register will be read and its value returned.
 * @return The current value of the AGC_TABLE_OUT_REG1 register.
 */
__INLINE uint32_t bt_rf_agc_table_out_reg1_get(void)
{
    return REG_PL_RD(BT_RF_AGC_TABLE_OUT_REG1_ADDR);
}

// field definitions
/// AGC_TABLE_OUT__1 field mask
#define BT_RF_AGC_TABLE_OUT__1_MASK   ((uint32_t)0xFFFFFFFF)
/// AGC_TABLE_OUT__1 field LSB position
#define BT_RF_AGC_TABLE_OUT__1_LSB    0
/// AGC_TABLE_OUT__1 field width
#define BT_RF_AGC_TABLE_OUT__1_WIDTH  ((uint32_t)0x00000020)

/// AGC_TABLE_OUT__1 field reset value
#define BT_RF_AGC_TABLE_OUT__1_RST    0x83DB

/**
 * @brief Returns the current value of the agc_table_out_1 field in the AGC_TABLE_OUT_REG1 register.
 *
 * The AGC_TABLE_OUT_REG1 register will be read and the agc_table_out_1 field's value will be returned.
 *
 * @return The current value of the agc_table_out_1 field in the AGC_TABLE_OUT_REG1 register.
 */
__INLINE uint32_t bt_rf_agc_table_out__1_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_AGC_TABLE_OUT_REG1_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name AGC_TABLE_OUT_REG2 register definitions
 * <table>
 * <caption id="AGC_TABLE_OUT_REG2_BF">AGC_TABLE_OUT_REG2 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   agc_table_out_2 <td>W <td>R <td>0x81000000
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG2 register
#define BT_RF_AGC_TABLE_OUT_REG2_ADDR   0x40622060
/// Offset of the AGC_TABLE_OUT_REG2 register from the base address
#define BT_RF_AGC_TABLE_OUT_REG2_OFFSET 0x00000060
/// Index of the AGC_TABLE_OUT_REG2 register
#define BT_RF_AGC_TABLE_OUT_REG2_INDEX  0x00000018
/// Reset value of the AGC_TABLE_OUT_REG2 register
#define BT_RF_AGC_TABLE_OUT_REG2_RESET  0x81000000

/**
 * @brief Returns the current value of the AGC_TABLE_OUT_REG2 register.
 * The AGC_TABLE_OUT_REG2 register will be read and its value returned.
 * @return The current value of the AGC_TABLE_OUT_REG2 register.
 */
__INLINE uint32_t bt_rf_agc_table_out_reg2_get(void)
{
    return REG_PL_RD(BT_RF_AGC_TABLE_OUT_REG2_ADDR);
}

// field definitions
/// AGC_TABLE_OUT__2 field mask
#define BT_RF_AGC_TABLE_OUT__2_MASK   ((uint32_t)0xFFFFFFFF)
/// AGC_TABLE_OUT__2 field LSB position
#define BT_RF_AGC_TABLE_OUT__2_LSB    0
/// AGC_TABLE_OUT__2 field width
#define BT_RF_AGC_TABLE_OUT__2_WIDTH  ((uint32_t)0x00000020)

/// AGC_TABLE_OUT__2 field reset value
#define BT_RF_AGC_TABLE_OUT__2_RST    0x81000000

/**
 * @brief Returns the current value of the agc_table_out_2 field in the AGC_TABLE_OUT_REG2 register.
 *
 * The AGC_TABLE_OUT_REG2 register will be read and the agc_table_out_2 field's value will be returned.
 *
 * @return The current value of the agc_table_out_2 field in the AGC_TABLE_OUT_REG2 register.
 */
__INLINE uint32_t bt_rf_agc_table_out__2_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_AGC_TABLE_OUT_REG2_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name APC_TABLE_OUT_REG0 register definitions
 * <table>
 * <caption id="APC_TABLE_OUT_REG0_BF">APC_TABLE_OUT_REG0 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   apc_table_out_0 <td>W <td>R <td>0x15870
 * </table>
 *
 * @{
 */

/// Address of the APC_TABLE_OUT_REG0 register
#define BT_RF_APC_TABLE_OUT_REG0_ADDR   0x40622064
/// Offset of the APC_TABLE_OUT_REG0 register from the base address
#define BT_RF_APC_TABLE_OUT_REG0_OFFSET 0x00000064
/// Index of the APC_TABLE_OUT_REG0 register
#define BT_RF_APC_TABLE_OUT_REG0_INDEX  0x00000019
/// Reset value of the APC_TABLE_OUT_REG0 register
#define BT_RF_APC_TABLE_OUT_REG0_RESET  0x00015870

/**
 * @brief Returns the current value of the APC_TABLE_OUT_REG0 register.
 * The APC_TABLE_OUT_REG0 register will be read and its value returned.
 * @return The current value of the APC_TABLE_OUT_REG0 register.
 */
__INLINE uint32_t bt_rf_apc_table_out_reg0_get(void)
{
    return REG_PL_RD(BT_RF_APC_TABLE_OUT_REG0_ADDR);
}

// field definitions
/// APC_TABLE_OUT__0 field mask
#define BT_RF_APC_TABLE_OUT__0_MASK   ((uint32_t)0xFFFFFFFF)
/// APC_TABLE_OUT__0 field LSB position
#define BT_RF_APC_TABLE_OUT__0_LSB    0
/// APC_TABLE_OUT__0 field width
#define BT_RF_APC_TABLE_OUT__0_WIDTH  ((uint32_t)0x00000020)

/// APC_TABLE_OUT__0 field reset value
#define BT_RF_APC_TABLE_OUT__0_RST    0x15870

/**
 * @brief Returns the current value of the apc_table_out_0 field in the APC_TABLE_OUT_REG0 register.
 *
 * The APC_TABLE_OUT_REG0 register will be read and the apc_table_out_0 field's value will be returned.
 *
 * @return The current value of the apc_table_out_0 field in the APC_TABLE_OUT_REG0 register.
 */
__INLINE uint32_t bt_rf_apc_table_out__0_getf(void)
{
    uint32_t localVal = REG_PL_RD(BT_RF_APC_TABLE_OUT_REG0_ADDR);
    return (localVal >> 0);
}

/// @}


#endif // _REG_BT_RF_H_

/// @}

