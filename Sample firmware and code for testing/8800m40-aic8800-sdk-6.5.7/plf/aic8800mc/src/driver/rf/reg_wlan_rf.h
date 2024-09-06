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
#define REG_WLAN_RF_COUNT 35

/** @brief Decoding mask of the REG_WLAN_RF peripheral registers from the CPU point of view.
 */
#define REG_WLAN_RF_DECODING_MASK 0x000000FF

/**
 * @name REG_00 register definitions
 * <table>
 * <caption id="REG_00_BF">REG_00 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>      wf_pu_lna_dr <td>R <td>R/W <td>0
 * <tr><td>30 <td>     wf_pu_lna_reg <td>R <td>R/W <td>0
 * <tr><td>29 <td>      wf_pu_rmx_dr <td>R <td>R/W <td>0
 * <tr><td>28 <td>     wf_pu_rmx_reg <td>R <td>R/W <td>0
 * <tr><td>27 <td>      wf_pu_tia_dr <td>R <td>R/W <td>0
 * <tr><td>26 <td>     wf_pu_tia_reg <td>R <td>R/W <td>0
 * <tr><td>25 <td>    wf_tia_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>24 <td>   wf_tia_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>23 <td>       wf_pu_pa_dr <td>R <td>R/W <td>0
 * <tr><td>22 <td>      wf_pu_pa_reg <td>R <td>R/W <td>0
 * <tr><td>21 <td>  wf_pa_gain_en_dr <td>R <td>R/W <td>0
 * <tr><td>20 <td> wf_pa_gain_en_reg <td>R <td>R/W <td>0
 * <tr><td>19 <td>wf_pa_pkdet_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>18 <td>wf_pa_pkdet_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>17 <td>wf_pu_trx_capsw_dr <td>R <td>R/W <td>0
 * <tr><td>16 <td>wf_pu_trx_capsw_reg <td>R <td>R/W <td>0
 * <tr><td>15 <td>wf_pa_trxsw_sel_avdd13_dr <td>R <td>R/W <td>0
 * <tr><td>14 <td>wf_pa_trxsw_sel_avdd13_reg <td>R <td>R/W <td>0
 * <tr><td>13 <td>     wf_pu_dtmx_dr <td>R <td>R/W <td>0
 * <tr><td>12 <td>    wf_pu_dtmx_reg <td>R <td>R/W <td>0
 * <tr><td>11 <td>wf_dtmx_cdr_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>10 <td>wf_dtmx_cdr_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>09 <td>     wf_pu_iref_dr <td>R <td>R/W <td>0
 * <tr><td>08 <td>    wf_pu_iref_reg <td>R <td>R/W <td>0
 * <tr><td>07 <td>    wf_pu_rxflt_dr <td>R <td>R/W <td>0
 * <tr><td>06 <td>   wf_pu_rxflt_reg <td>R <td>R/W <td>0
 * <tr><td>05 <td>  wf_rxflt_rstn_dr <td>R <td>R/W <td>0
 * <tr><td>04 <td> wf_rxflt_rstn_reg <td>R <td>R/W <td>0
 * <tr><td>03 <td>      wf_pu_adc_dr <td>R <td>R/W <td>0
 * <tr><td>02 <td>     wf_pu_adc_reg <td>R <td>R/W <td>0
 * <tr><td>01 <td>wf_pu_adc_vreg_com_dr <td>R <td>R/W <td>0
 * <tr><td>00 <td>wf_pu_adc_vreg_com_reg <td>R <td>R/W <td>0
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
#define WLAN_RF_REG_00_RESET  0x00000000

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
/// WF_PU_LNA_DR field bit
#define WLAN_RF_WF_PU_LNA_DR_BIT                   ((uint32_t)0x80000000)
/// WF_PU_LNA_DR field position
#define WLAN_RF_WF_PU_LNA_DR_POS                   31
/// WF_PU_LNA_REG field bit
#define WLAN_RF_WF_PU_LNA_REG_BIT                  ((uint32_t)0x40000000)
/// WF_PU_LNA_REG field position
#define WLAN_RF_WF_PU_LNA_REG_POS                  30
/// WF_PU_RMX_DR field bit
#define WLAN_RF_WF_PU_RMX_DR_BIT                   ((uint32_t)0x20000000)
/// WF_PU_RMX_DR field position
#define WLAN_RF_WF_PU_RMX_DR_POS                   29
/// WF_PU_RMX_REG field bit
#define WLAN_RF_WF_PU_RMX_REG_BIT                  ((uint32_t)0x10000000)
/// WF_PU_RMX_REG field position
#define WLAN_RF_WF_PU_RMX_REG_POS                  28
/// WF_PU_TIA_DR field bit
#define WLAN_RF_WF_PU_TIA_DR_BIT                   ((uint32_t)0x08000000)
/// WF_PU_TIA_DR field position
#define WLAN_RF_WF_PU_TIA_DR_POS                   27
/// WF_PU_TIA_REG field bit
#define WLAN_RF_WF_PU_TIA_REG_BIT                  ((uint32_t)0x04000000)
/// WF_PU_TIA_REG field position
#define WLAN_RF_WF_PU_TIA_REG_POS                  26
/// WF_TIA_RSTN_DR field bit
#define WLAN_RF_WF_TIA_RSTN_DR_BIT                 ((uint32_t)0x02000000)
/// WF_TIA_RSTN_DR field position
#define WLAN_RF_WF_TIA_RSTN_DR_POS                 25
/// WF_TIA_RSTN_REG field bit
#define WLAN_RF_WF_TIA_RSTN_REG_BIT                ((uint32_t)0x01000000)
/// WF_TIA_RSTN_REG field position
#define WLAN_RF_WF_TIA_RSTN_REG_POS                24
/// WF_PU_PA_DR field bit
#define WLAN_RF_WF_PU_PA_DR_BIT                    ((uint32_t)0x00800000)
/// WF_PU_PA_DR field position
#define WLAN_RF_WF_PU_PA_DR_POS                    23
/// WF_PU_PA_REG field bit
#define WLAN_RF_WF_PU_PA_REG_BIT                   ((uint32_t)0x00400000)
/// WF_PU_PA_REG field position
#define WLAN_RF_WF_PU_PA_REG_POS                   22
/// WF_PA_GAIN_EN_DR field bit
#define WLAN_RF_WF_PA_GAIN_EN_DR_BIT               ((uint32_t)0x00200000)
/// WF_PA_GAIN_EN_DR field position
#define WLAN_RF_WF_PA_GAIN_EN_DR_POS               21
/// WF_PA_GAIN_EN_REG field bit
#define WLAN_RF_WF_PA_GAIN_EN_REG_BIT              ((uint32_t)0x00100000)
/// WF_PA_GAIN_EN_REG field position
#define WLAN_RF_WF_PA_GAIN_EN_REG_POS              20
/// WF_PA_PKDET_RSTN_DR field bit
#define WLAN_RF_WF_PA_PKDET_RSTN_DR_BIT            ((uint32_t)0x00080000)
/// WF_PA_PKDET_RSTN_DR field position
#define WLAN_RF_WF_PA_PKDET_RSTN_DR_POS            19
/// WF_PA_PKDET_RSTN_REG field bit
#define WLAN_RF_WF_PA_PKDET_RSTN_REG_BIT           ((uint32_t)0x00040000)
/// WF_PA_PKDET_RSTN_REG field position
#define WLAN_RF_WF_PA_PKDET_RSTN_REG_POS           18
/// WF_PU_TRX_CAPSW_DR field bit
#define WLAN_RF_WF_PU_TRX_CAPSW_DR_BIT             ((uint32_t)0x00020000)
/// WF_PU_TRX_CAPSW_DR field position
#define WLAN_RF_WF_PU_TRX_CAPSW_DR_POS             17
/// WF_PU_TRX_CAPSW_REG field bit
#define WLAN_RF_WF_PU_TRX_CAPSW_REG_BIT            ((uint32_t)0x00010000)
/// WF_PU_TRX_CAPSW_REG field position
#define WLAN_RF_WF_PU_TRX_CAPSW_REG_POS            16
/// WF_PA_TRXSW_SEL_AVDD_13_DR field bit
#define WLAN_RF_WF_PA_TRXSW_SEL_AVDD_13_DR_BIT     ((uint32_t)0x00008000)
/// WF_PA_TRXSW_SEL_AVDD_13_DR field position
#define WLAN_RF_WF_PA_TRXSW_SEL_AVDD_13_DR_POS     15
/// WF_PA_TRXSW_SEL_AVDD_13_REG field bit
#define WLAN_RF_WF_PA_TRXSW_SEL_AVDD_13_REG_BIT    ((uint32_t)0x00004000)
/// WF_PA_TRXSW_SEL_AVDD_13_REG field position
#define WLAN_RF_WF_PA_TRXSW_SEL_AVDD_13_REG_POS    14
/// WF_PU_DTMX_DR field bit
#define WLAN_RF_WF_PU_DTMX_DR_BIT                  ((uint32_t)0x00002000)
/// WF_PU_DTMX_DR field position
#define WLAN_RF_WF_PU_DTMX_DR_POS                  13
/// WF_PU_DTMX_REG field bit
#define WLAN_RF_WF_PU_DTMX_REG_BIT                 ((uint32_t)0x00001000)
/// WF_PU_DTMX_REG field position
#define WLAN_RF_WF_PU_DTMX_REG_POS                 12
/// WF_DTMX_CDR_RSTN_DR field bit
#define WLAN_RF_WF_DTMX_CDR_RSTN_DR_BIT            ((uint32_t)0x00000800)
/// WF_DTMX_CDR_RSTN_DR field position
#define WLAN_RF_WF_DTMX_CDR_RSTN_DR_POS            11
/// WF_DTMX_CDR_RSTN_REG field bit
#define WLAN_RF_WF_DTMX_CDR_RSTN_REG_BIT           ((uint32_t)0x00000400)
/// WF_DTMX_CDR_RSTN_REG field position
#define WLAN_RF_WF_DTMX_CDR_RSTN_REG_POS           10
/// WF_PU_IREF_DR field bit
#define WLAN_RF_WF_PU_IREF_DR_BIT                  ((uint32_t)0x00000200)
/// WF_PU_IREF_DR field position
#define WLAN_RF_WF_PU_IREF_DR_POS                  9
/// WF_PU_IREF_REG field bit
#define WLAN_RF_WF_PU_IREF_REG_BIT                 ((uint32_t)0x00000100)
/// WF_PU_IREF_REG field position
#define WLAN_RF_WF_PU_IREF_REG_POS                 8
/// WF_PU_RXFLT_DR field bit
#define WLAN_RF_WF_PU_RXFLT_DR_BIT                 ((uint32_t)0x00000080)
/// WF_PU_RXFLT_DR field position
#define WLAN_RF_WF_PU_RXFLT_DR_POS                 7
/// WF_PU_RXFLT_REG field bit
#define WLAN_RF_WF_PU_RXFLT_REG_BIT                ((uint32_t)0x00000040)
/// WF_PU_RXFLT_REG field position
#define WLAN_RF_WF_PU_RXFLT_REG_POS                6
/// WF_RXFLT_RSTN_DR field bit
#define WLAN_RF_WF_RXFLT_RSTN_DR_BIT               ((uint32_t)0x00000020)
/// WF_RXFLT_RSTN_DR field position
#define WLAN_RF_WF_RXFLT_RSTN_DR_POS               5
/// WF_RXFLT_RSTN_REG field bit
#define WLAN_RF_WF_RXFLT_RSTN_REG_BIT              ((uint32_t)0x00000010)
/// WF_RXFLT_RSTN_REG field position
#define WLAN_RF_WF_RXFLT_RSTN_REG_POS              4
/// WF_PU_ADC_DR field bit
#define WLAN_RF_WF_PU_ADC_DR_BIT                   ((uint32_t)0x00000008)
/// WF_PU_ADC_DR field position
#define WLAN_RF_WF_PU_ADC_DR_POS                   3
/// WF_PU_ADC_REG field bit
#define WLAN_RF_WF_PU_ADC_REG_BIT                  ((uint32_t)0x00000004)
/// WF_PU_ADC_REG field position
#define WLAN_RF_WF_PU_ADC_REG_POS                  2
/// WF_PU_ADC_VREG_COM_DR field bit
#define WLAN_RF_WF_PU_ADC_VREG_COM_DR_BIT          ((uint32_t)0x00000002)
/// WF_PU_ADC_VREG_COM_DR field position
#define WLAN_RF_WF_PU_ADC_VREG_COM_DR_POS          1
/// WF_PU_ADC_VREG_COM_REG field bit
#define WLAN_RF_WF_PU_ADC_VREG_COM_REG_BIT         ((uint32_t)0x00000001)
/// WF_PU_ADC_VREG_COM_REG field position
#define WLAN_RF_WF_PU_ADC_VREG_COM_REG_POS         0

/// WF_PU_LNA_DR field reset value
#define WLAN_RF_WF_PU_LNA_DR_RST                   0x0
/// WF_PU_LNA_REG field reset value
#define WLAN_RF_WF_PU_LNA_REG_RST                  0x0
/// WF_PU_RMX_DR field reset value
#define WLAN_RF_WF_PU_RMX_DR_RST                   0x0
/// WF_PU_RMX_REG field reset value
#define WLAN_RF_WF_PU_RMX_REG_RST                  0x0
/// WF_PU_TIA_DR field reset value
#define WLAN_RF_WF_PU_TIA_DR_RST                   0x0
/// WF_PU_TIA_REG field reset value
#define WLAN_RF_WF_PU_TIA_REG_RST                  0x0
/// WF_TIA_RSTN_DR field reset value
#define WLAN_RF_WF_TIA_RSTN_DR_RST                 0x0
/// WF_TIA_RSTN_REG field reset value
#define WLAN_RF_WF_TIA_RSTN_REG_RST                0x0
/// WF_PU_PA_DR field reset value
#define WLAN_RF_WF_PU_PA_DR_RST                    0x0
/// WF_PU_PA_REG field reset value
#define WLAN_RF_WF_PU_PA_REG_RST                   0x0
/// WF_PA_GAIN_EN_DR field reset value
#define WLAN_RF_WF_PA_GAIN_EN_DR_RST               0x0
/// WF_PA_GAIN_EN_REG field reset value
#define WLAN_RF_WF_PA_GAIN_EN_REG_RST              0x0
/// WF_PA_PKDET_RSTN_DR field reset value
#define WLAN_RF_WF_PA_PKDET_RSTN_DR_RST            0x0
/// WF_PA_PKDET_RSTN_REG field reset value
#define WLAN_RF_WF_PA_PKDET_RSTN_REG_RST           0x0
/// WF_PU_TRX_CAPSW_DR field reset value
#define WLAN_RF_WF_PU_TRX_CAPSW_DR_RST             0x0
/// WF_PU_TRX_CAPSW_REG field reset value
#define WLAN_RF_WF_PU_TRX_CAPSW_REG_RST            0x0
/// WF_PA_TRXSW_SEL_AVDD_13_DR field reset value
#define WLAN_RF_WF_PA_TRXSW_SEL_AVDD_13_DR_RST     0x0
/// WF_PA_TRXSW_SEL_AVDD_13_REG field reset value
#define WLAN_RF_WF_PA_TRXSW_SEL_AVDD_13_REG_RST    0x0
/// WF_PU_DTMX_DR field reset value
#define WLAN_RF_WF_PU_DTMX_DR_RST                  0x0
/// WF_PU_DTMX_REG field reset value
#define WLAN_RF_WF_PU_DTMX_REG_RST                 0x0
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

/**
 * @brief Constructs a value for the REG_00 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpulnadr - The value to use for the wf_pu_lna_dr field.
 * @param[in] wfpulnareg - The value to use for the wf_pu_lna_reg field.
 * @param[in] wfpurmxdr - The value to use for the wf_pu_rmx_dr field.
 * @param[in] wfpurmxreg - The value to use for the wf_pu_rmx_reg field.
 * @param[in] wfputiadr - The value to use for the wf_pu_tia_dr field.
 * @param[in] wfputiareg - The value to use for the wf_pu_tia_reg field.
 * @param[in] wftiarstndr - The value to use for the wf_tia_rstn_dr field.
 * @param[in] wftiarstnreg - The value to use for the wf_tia_rstn_reg field.
 * @param[in] wfpupadr - The value to use for the wf_pu_pa_dr field.
 * @param[in] wfpupareg - The value to use for the wf_pu_pa_reg field.
 * @param[in] wfpagainendr - The value to use for the wf_pa_gain_en_dr field.
 * @param[in] wfpagainenreg - The value to use for the wf_pa_gain_en_reg field.
 * @param[in] wfpapkdetrstndr - The value to use for the wf_pa_pkdet_rstn_dr field.
 * @param[in] wfpapkdetrstnreg - The value to use for the wf_pa_pkdet_rstn_reg field.
 * @param[in] wfputrxcapswdr - The value to use for the wf_pu_trx_capsw_dr field.
 * @param[in] wfputrxcapswreg - The value to use for the wf_pu_trx_capsw_reg field.
 * @param[in] wfpatrxswselavdd13dr - The value to use for the wf_pa_trxsw_sel_avdd13_dr field.
 * @param[in] wfpatrxswselavdd13reg - The value to use for the wf_pa_trxsw_sel_avdd13_reg field.
 * @param[in] wfpudtmxdr - The value to use for the wf_pu_dtmx_dr field.
 * @param[in] wfpudtmxreg - The value to use for the wf_pu_dtmx_reg field.
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
 */
__INLINE void wlan_rf_reg_00_pack(uint8_t wfpulnadr, uint8_t wfpulnareg, uint8_t wfpurmxdr, uint8_t wfpurmxreg, uint8_t wfputiadr, uint8_t wfputiareg, uint8_t wftiarstndr, uint8_t wftiarstnreg, uint8_t wfpupadr, uint8_t wfpupareg, uint8_t wfpagainendr, uint8_t wfpagainenreg, uint8_t wfpapkdetrstndr, uint8_t wfpapkdetrstnreg, uint8_t wfputrxcapswdr, uint8_t wfputrxcapswreg, uint8_t wfpatrxswselavdd13dr, uint8_t wfpatrxswselavdd13reg, uint8_t wfpudtmxdr, uint8_t wfpudtmxreg, uint8_t wfdtmxcdrrstndr, uint8_t wfdtmxcdrrstnreg, uint8_t wfpuirefdr, uint8_t wfpuirefreg, uint8_t wfpurxfltdr, uint8_t wfpurxfltreg, uint8_t wfrxfltrstndr, uint8_t wfrxfltrstnreg, uint8_t wfpuadcdr, uint8_t wfpuadcreg, uint8_t wfpuadcvregcomdr, uint8_t wfpuadcvregcomreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR,  ((uint32_t)wfpulnadr << 31) | ((uint32_t)wfpulnareg << 30) | ((uint32_t)wfpurmxdr << 29) | ((uint32_t)wfpurmxreg << 28) | ((uint32_t)wfputiadr << 27) | ((uint32_t)wfputiareg << 26) | ((uint32_t)wftiarstndr << 25) | ((uint32_t)wftiarstnreg << 24) | ((uint32_t)wfpupadr << 23) | ((uint32_t)wfpupareg << 22) | ((uint32_t)wfpagainendr << 21) | ((uint32_t)wfpagainenreg << 20) | ((uint32_t)wfpapkdetrstndr << 19) | ((uint32_t)wfpapkdetrstnreg << 18) | ((uint32_t)wfputrxcapswdr << 17) | ((uint32_t)wfputrxcapswreg << 16) | ((uint32_t)wfpatrxswselavdd13dr << 15) | ((uint32_t)wfpatrxswselavdd13reg << 14) | ((uint32_t)wfpudtmxdr << 13) | ((uint32_t)wfpudtmxreg << 12) | ((uint32_t)wfdtmxcdrrstndr << 11) | ((uint32_t)wfdtmxcdrrstnreg << 10) | ((uint32_t)wfpuirefdr << 9) | ((uint32_t)wfpuirefreg << 8) | ((uint32_t)wfpurxfltdr << 7) | ((uint32_t)wfpurxfltreg << 6) | ((uint32_t)wfrxfltrstndr << 5) | ((uint32_t)wfrxfltrstnreg << 4) | ((uint32_t)wfpuadcdr << 3) | ((uint32_t)wfpuadcreg << 2) | ((uint32_t)wfpuadcvregcomdr << 1) | ((uint32_t)wfpuadcvregcomreg << 0));
}

/**
 * @brief Unpacks REG_00's fields from current value of the REG_00 register.
 *
 * Reads the REG_00 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpulnadr - Will be populated with the current value of this field from the register.
 * @param[out] wfpulnareg - Will be populated with the current value of this field from the register.
 * @param[out] wfpurmxdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpurmxreg - Will be populated with the current value of this field from the register.
 * @param[out] wfputiadr - Will be populated with the current value of this field from the register.
 * @param[out] wfputiareg - Will be populated with the current value of this field from the register.
 * @param[out] wftiarstndr - Will be populated with the current value of this field from the register.
 * @param[out] wftiarstnreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpupadr - Will be populated with the current value of this field from the register.
 * @param[out] wfpupareg - Will be populated with the current value of this field from the register.
 * @param[out] wfpagainendr - Will be populated with the current value of this field from the register.
 * @param[out] wfpagainenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetrstndr - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetrstnreg - Will be populated with the current value of this field from the register.
 * @param[out] wfputrxcapswdr - Will be populated with the current value of this field from the register.
 * @param[out] wfputrxcapswreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpatrxswselavdd13dr - Will be populated with the current value of this field from the register.
 * @param[out] wfpatrxswselavdd13reg - Will be populated with the current value of this field from the register.
 * @param[out] wfpudtmxdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpudtmxreg - Will be populated with the current value of this field from the register.
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
 */
__INLINE void wlan_rf_reg_00_unpack(uint8_t* wfpulnadr, uint8_t* wfpulnareg, uint8_t* wfpurmxdr, uint8_t* wfpurmxreg, uint8_t* wfputiadr, uint8_t* wfputiareg, uint8_t* wftiarstndr, uint8_t* wftiarstnreg, uint8_t* wfpupadr, uint8_t* wfpupareg, uint8_t* wfpagainendr, uint8_t* wfpagainenreg, uint8_t* wfpapkdetrstndr, uint8_t* wfpapkdetrstnreg, uint8_t* wfputrxcapswdr, uint8_t* wfputrxcapswreg, uint8_t* wfpatrxswselavdd13dr, uint8_t* wfpatrxswselavdd13reg, uint8_t* wfpudtmxdr, uint8_t* wfpudtmxreg, uint8_t* wfdtmxcdrrstndr, uint8_t* wfdtmxcdrrstnreg, uint8_t* wfpuirefdr, uint8_t* wfpuirefreg, uint8_t* wfpurxfltdr, uint8_t* wfpurxfltreg, uint8_t* wfrxfltrstndr, uint8_t* wfrxfltrstnreg, uint8_t* wfpuadcdr, uint8_t* wfpuadcreg, uint8_t* wfpuadcvregcomdr, uint8_t* wfpuadcvregcomreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);

    *wfpulnadr = (localVal & ((uint32_t)0x80000000)) >> 31;
    *wfpulnareg = (localVal & ((uint32_t)0x40000000)) >> 30;
    *wfpurmxdr = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wfpurmxreg = (localVal & ((uint32_t)0x10000000)) >> 28;
    *wfputiadr = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfputiareg = (localVal & ((uint32_t)0x04000000)) >> 26;
    *wftiarstndr = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wftiarstnreg = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wfpupadr = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfpupareg = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wfpagainendr = (localVal & ((uint32_t)0x00200000)) >> 21;
    *wfpagainenreg = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wfpapkdetrstndr = (localVal & ((uint32_t)0x00080000)) >> 19;
    *wfpapkdetrstnreg = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfputrxcapswdr = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wfputrxcapswreg = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wfpatrxswselavdd13dr = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wfpatrxswselavdd13reg = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wfpudtmxdr = (localVal & ((uint32_t)0x00002000)) >> 13;
    *wfpudtmxreg = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wfdtmxcdrrstndr = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wfdtmxcdrrstnreg = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfpuirefdr = (localVal & ((uint32_t)0x00000200)) >> 9;
    *wfpuirefreg = (localVal & ((uint32_t)0x00000100)) >> 8;
    *wfpurxfltdr = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wfpurxfltreg = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wfrxfltrstndr = (localVal & ((uint32_t)0x00000020)) >> 5;
    *wfrxfltrstnreg = (localVal & ((uint32_t)0x00000010)) >> 4;
    *wfpuadcdr = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wfpuadcreg = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wfpuadcvregcomdr = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfpuadcvregcomreg = (localVal & ((uint32_t)0x00000001)) >> 0;
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
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)wfpulnadr << 31) & ((uint32_t)0x80000000)));
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
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)wfpulnareg << 30) & ((uint32_t)0x40000000)));
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
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wfpurmxdr << 29) & ((uint32_t)0x20000000)));
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
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)wfpurmxreg << 28) & ((uint32_t)0x10000000)));
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
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wfputiadr << 27) & ((uint32_t)0x08000000)));
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
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)wfputiareg << 26) & ((uint32_t)0x04000000)));
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
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wftiarstndr << 25) & ((uint32_t)0x02000000)));
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
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wftiarstnreg << 24) & ((uint32_t)0x01000000)));
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
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wfpupadr << 23) & ((uint32_t)0x00800000)));
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
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)wfpupareg << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the wf_pa_gain_en_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa_gain_en_dr field's value will be returned.
 *
 * @return The current value of the wf_pa_gain_en_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_gain_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Sets the wf_pa_gain_en_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpagainendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_gain_en_dr_setf(uint8_t wfpagainendr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00200000)) | (((uint32_t)wfpagainendr << 21) & ((uint32_t)0x00200000)));
}

/**
 * @brief Returns the current value of the wf_pa_gain_en_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa_gain_en_reg field's value will be returned.
 *
 * @return The current value of the wf_pa_gain_en_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_gain_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_pa_gain_en_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpagainenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_gain_en_reg_setf(uint8_t wfpagainenreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wfpagainenreg << 20) & ((uint32_t)0x00100000)));
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
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)wfpapkdetrstndr << 19) & ((uint32_t)0x00080000)));
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
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
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
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wfpapkdetrstnreg << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_pu_trx_capsw_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_trx_capsw_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_trx_capsw_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_trx_capsw_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_pu_trx_capsw_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputrxcapswdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_trx_capsw_dr_setf(uint8_t wfputrxcapswdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wfputrxcapswdr << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_pu_trx_capsw_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_trx_capsw_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_trx_capsw_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_trx_capsw_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_pu_trx_capsw_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputrxcapswreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_trx_capsw_reg_setf(uint8_t wfputrxcapswreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wfputrxcapswreg << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_pa_trxsw_sel_avdd13_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa_trxsw_sel_avdd13_dr field's value will be returned.
 *
 * @return The current value of the wf_pa_trxsw_sel_avdd13_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_trxsw_sel_avdd_13_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the wf_pa_trxsw_sel_avdd13_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpatrxswselavdd13dr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_trxsw_sel_avdd_13_dr_setf(uint8_t wfpatrxswselavdd13dr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)wfpatrxswselavdd13dr << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the wf_pa_trxsw_sel_avdd13_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pa_trxsw_sel_avdd13_reg field's value will be returned.
 *
 * @return The current value of the wf_pa_trxsw_sel_avdd13_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_trxsw_sel_avdd_13_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the wf_pa_trxsw_sel_avdd13_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpatrxswselavdd13reg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_trxsw_sel_avdd_13_reg_setf(uint8_t wfpatrxswselavdd13reg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)wfpatrxswselavdd13reg << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the wf_pu_dtmx_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_dtmx_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_dtmx_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_dtmx_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the wf_pu_dtmx_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpudtmxdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_dtmx_dr_setf(uint8_t wfpudtmxdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)wfpudtmxdr << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the wf_pu_dtmx_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_dtmx_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_dtmx_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_dtmx_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_pu_dtmx_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpudtmxreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_dtmx_reg_setf(uint8_t wfpudtmxreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wfpudtmxreg << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_rstn_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_dtmx_cdr_rstn_dr field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_rstn_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_dtmx_cdr_rstn_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdrrstndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_rstn_dr_setf(uint8_t wfdtmxcdrrstndr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wfdtmxcdrrstndr << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_rstn_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_dtmx_cdr_rstn_reg field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_rstn_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_dtmx_cdr_rstn_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdrrstnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_rstn_reg_setf(uint8_t wfdtmxcdrrstnreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfdtmxcdrrstnreg << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_pu_iref_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_iref_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_iref_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_iref_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the wf_pu_iref_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuirefdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_iref_dr_setf(uint8_t wfpuirefdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)wfpuirefdr << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the wf_pu_iref_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_iref_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_iref_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_iref_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the wf_pu_iref_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuirefreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_iref_reg_setf(uint8_t wfpuirefreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)wfpuirefreg << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the wf_pu_rxflt_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_rxflt_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_rxflt_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rxflt_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_pu_rxflt_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurxfltdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rxflt_dr_setf(uint8_t wfpurxfltdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wfpurxfltdr << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_pu_rxflt_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_rxflt_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_rxflt_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rxflt_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the wf_pu_rxflt_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurxfltreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rxflt_reg_setf(uint8_t wfpurxfltreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)wfpurxfltreg << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the wf_rxflt_rstn_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_rxflt_rstn_dr field's value will be returned.
 *
 * @return The current value of the wf_rxflt_rstn_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_rstn_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the wf_rxflt_rstn_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltrstndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_rstn_dr_setf(uint8_t wfrxfltrstndr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)wfrxfltrstndr << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the wf_rxflt_rstn_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_rxflt_rstn_reg field's value will be returned.
 *
 * @return The current value of the wf_rxflt_rstn_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_rstn_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the wf_rxflt_rstn_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltrstnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_rstn_reg_setf(uint8_t wfrxfltrstnreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)wfrxfltrstnreg << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_adc_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wf_pu_adc_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_dr_setf(uint8_t wfpuadcdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wfpuadcdr << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_adc_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wf_pu_adc_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_reg_setf(uint8_t wfpuadcreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wfpuadcreg << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_vreg_com_dr field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_adc_vreg_com_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_vreg_com_dr field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_vreg_com_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_pu_adc_vreg_com_dr field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcvregcomdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_vreg_com_dr_setf(uint8_t wfpuadcvregcomdr)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfpuadcvregcomdr << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_vreg_com_reg field in the REG_00 register.
 *
 * The REG_00 register will be read and the wf_pu_adc_vreg_com_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_vreg_com_reg field in the REG_00 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_vreg_com_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_00_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_pu_adc_vreg_com_reg field of the REG_00 register.
 *
 * The REG_00 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcvregcomreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_vreg_com_reg_setf(uint8_t wfpuadcvregcomreg)
{
    REG_PL_WR(WLAN_RF_REG_00_ADDR, (REG_PL_RD(WLAN_RF_REG_00_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfpuadcvregcomreg << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_01 register definitions
 * <table>
 * <caption id="REG_01_BF">REG_01 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30 <td>wf_pu_adc_vref_pdt_dr <td>R <td>R/W <td>0
 * <tr><td>29 <td>wf_pu_adc_vref_pdt_reg <td>R <td>R/W <td>0
 * <tr><td>28 <td>    wf_pu_pdadc_dr <td>R <td>R/W <td>0
 * <tr><td>27 <td>   wf_pu_pdadc_reg <td>R <td>R/W <td>0
 * <tr><td>26 <td>    wf_pu_rfpll_dr <td>R <td>R/W <td>0
 * <tr><td>25 <td>   wf_pu_rfpll_reg <td>R <td>R/W <td>0
 * <tr><td>24 <td>wf_rfpll_sar_clk_en_dr <td>R <td>R/W <td>0
 * <tr><td>23 <td>wf_rfpll_sar_clk_en_reg <td>R <td>R/W <td>0
 * <tr><td>22 <td>      wf_pu_vco_dr <td>R <td>R/W <td>0
 * <tr><td>21 <td>     wf_pu_vco_reg <td>R <td>R/W <td>0
 * <tr><td>20 <td> wf_vco_txlo_en_dr <td>R <td>R/W <td>0
 * <tr><td>19 <td>wf_vco_txlo_en_reg <td>R <td>R/W <td>0
 * <tr><td>18 <td> wf_vco_rxlo_en_dr <td>R <td>R/W <td>0
 * <tr><td>17 <td>wf_vco_rxlo_en_reg <td>R <td>R/W <td>0
 * <tr><td>16 <td>      wf_pu_ts_hub <td>R <td>R/W <td>0
 * <tr><td>15:14 <td>     wf_lna_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>13:12 <td>     wf_rmx_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>11:10 <td>     wf_tia_pu_bit <td>R <td>R/W <td>0x1
 * <tr><td>09:08 <td>wf_dtmx_pu_bit_avdd33 <td>R <td>R/W <td>0x2
 * <tr><td>07:06 <td>wf_dtmx_pu_bit_avdd13 <td>R <td>R/W <td>0x2
 * <tr><td>05:04 <td>   wf_rxflt_pu_bit <td>R <td>R/W <td>0x2
 * <tr><td>03:02 <td>     wf_adc_pu_bit <td>R <td>R/W <td>0x2
 * <tr><td>01:00 <td>   wf_rfpll_pu_bit <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the REG_01 register
#define WLAN_RF_REG_01_ADDR   0x40344004
/// Offset of the REG_01 register from the base address
#define WLAN_RF_REG_01_OFFSET 0x00000004
/// Index of the REG_01 register
#define WLAN_RF_REG_01_INDEX  0x00000001
/// Reset value of the REG_01 register
#define WLAN_RF_REG_01_RESET  0x000056A8

/**
 * @brief Returns the current value of the REG_01 register.
 * The REG_01 register will be read and its value returned.
 * @return The current value of the REG_01 register.
 */
__INLINE uint32_t wlan_rf_reg_01_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_01_ADDR);
}

/**
 * @brief Sets the REG_01 register to a value.
 * The REG_01 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_01_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, value);
}

// field definitions
/// WF_PU_ADC_VREF_PDT_DR field bit
#define WLAN_RF_WF_PU_ADC_VREF_PDT_DR_BIT      ((uint32_t)0x40000000)
/// WF_PU_ADC_VREF_PDT_DR field position
#define WLAN_RF_WF_PU_ADC_VREF_PDT_DR_POS      30
/// WF_PU_ADC_VREF_PDT_REG field bit
#define WLAN_RF_WF_PU_ADC_VREF_PDT_REG_BIT     ((uint32_t)0x20000000)
/// WF_PU_ADC_VREF_PDT_REG field position
#define WLAN_RF_WF_PU_ADC_VREF_PDT_REG_POS     29
/// WF_PU_PDADC_DR field bit
#define WLAN_RF_WF_PU_PDADC_DR_BIT             ((uint32_t)0x10000000)
/// WF_PU_PDADC_DR field position
#define WLAN_RF_WF_PU_PDADC_DR_POS             28
/// WF_PU_PDADC_REG field bit
#define WLAN_RF_WF_PU_PDADC_REG_BIT            ((uint32_t)0x08000000)
/// WF_PU_PDADC_REG field position
#define WLAN_RF_WF_PU_PDADC_REG_POS            27
/// WF_PU_RFPLL_DR field bit
#define WLAN_RF_WF_PU_RFPLL_DR_BIT             ((uint32_t)0x04000000)
/// WF_PU_RFPLL_DR field position
#define WLAN_RF_WF_PU_RFPLL_DR_POS             26
/// WF_PU_RFPLL_REG field bit
#define WLAN_RF_WF_PU_RFPLL_REG_BIT            ((uint32_t)0x02000000)
/// WF_PU_RFPLL_REG field position
#define WLAN_RF_WF_PU_RFPLL_REG_POS            25
/// WF_RFPLL_SAR_CLK_EN_DR field bit
#define WLAN_RF_WF_RFPLL_SAR_CLK_EN_DR_BIT     ((uint32_t)0x01000000)
/// WF_RFPLL_SAR_CLK_EN_DR field position
#define WLAN_RF_WF_RFPLL_SAR_CLK_EN_DR_POS     24
/// WF_RFPLL_SAR_CLK_EN_REG field bit
#define WLAN_RF_WF_RFPLL_SAR_CLK_EN_REG_BIT    ((uint32_t)0x00800000)
/// WF_RFPLL_SAR_CLK_EN_REG field position
#define WLAN_RF_WF_RFPLL_SAR_CLK_EN_REG_POS    23
/// WF_PU_VCO_DR field bit
#define WLAN_RF_WF_PU_VCO_DR_BIT               ((uint32_t)0x00400000)
/// WF_PU_VCO_DR field position
#define WLAN_RF_WF_PU_VCO_DR_POS               22
/// WF_PU_VCO_REG field bit
#define WLAN_RF_WF_PU_VCO_REG_BIT              ((uint32_t)0x00200000)
/// WF_PU_VCO_REG field position
#define WLAN_RF_WF_PU_VCO_REG_POS              21
/// WF_VCO_TXLO_EN_DR field bit
#define WLAN_RF_WF_VCO_TXLO_EN_DR_BIT          ((uint32_t)0x00100000)
/// WF_VCO_TXLO_EN_DR field position
#define WLAN_RF_WF_VCO_TXLO_EN_DR_POS          20
/// WF_VCO_TXLO_EN_REG field bit
#define WLAN_RF_WF_VCO_TXLO_EN_REG_BIT         ((uint32_t)0x00080000)
/// WF_VCO_TXLO_EN_REG field position
#define WLAN_RF_WF_VCO_TXLO_EN_REG_POS         19
/// WF_VCO_RXLO_EN_DR field bit
#define WLAN_RF_WF_VCO_RXLO_EN_DR_BIT          ((uint32_t)0x00040000)
/// WF_VCO_RXLO_EN_DR field position
#define WLAN_RF_WF_VCO_RXLO_EN_DR_POS          18
/// WF_VCO_RXLO_EN_REG field bit
#define WLAN_RF_WF_VCO_RXLO_EN_REG_BIT         ((uint32_t)0x00020000)
/// WF_VCO_RXLO_EN_REG field position
#define WLAN_RF_WF_VCO_RXLO_EN_REG_POS         17
/// WF_PU_TS_HUB field bit
#define WLAN_RF_WF_PU_TS_HUB_BIT               ((uint32_t)0x00010000)
/// WF_PU_TS_HUB field position
#define WLAN_RF_WF_PU_TS_HUB_POS               16
/// WF_LNA_PU_BIT field mask
#define WLAN_RF_WF_LNA_PU_BIT_MASK             ((uint32_t)0x0000C000)
/// WF_LNA_PU_BIT field LSB position
#define WLAN_RF_WF_LNA_PU_BIT_LSB              14
/// WF_LNA_PU_BIT field width
#define WLAN_RF_WF_LNA_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// WF_RMX_PU_BIT field mask
#define WLAN_RF_WF_RMX_PU_BIT_MASK             ((uint32_t)0x00003000)
/// WF_RMX_PU_BIT field LSB position
#define WLAN_RF_WF_RMX_PU_BIT_LSB              12
/// WF_RMX_PU_BIT field width
#define WLAN_RF_WF_RMX_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// WF_TIA_PU_BIT field mask
#define WLAN_RF_WF_TIA_PU_BIT_MASK             ((uint32_t)0x00000C00)
/// WF_TIA_PU_BIT field LSB position
#define WLAN_RF_WF_TIA_PU_BIT_LSB              10
/// WF_TIA_PU_BIT field width
#define WLAN_RF_WF_TIA_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// WF_DTMX_PU_BIT_AVDD_33 field mask
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_33_MASK    ((uint32_t)0x00000300)
/// WF_DTMX_PU_BIT_AVDD_33 field LSB position
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_33_LSB     8
/// WF_DTMX_PU_BIT_AVDD_33 field width
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_33_WIDTH   ((uint32_t)0x00000002)
/// WF_DTMX_PU_BIT_AVDD_13 field mask
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_13_MASK    ((uint32_t)0x000000C0)
/// WF_DTMX_PU_BIT_AVDD_13 field LSB position
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_13_LSB     6
/// WF_DTMX_PU_BIT_AVDD_13 field width
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_13_WIDTH   ((uint32_t)0x00000002)
/// WF_RXFLT_PU_BIT field mask
#define WLAN_RF_WF_RXFLT_PU_BIT_MASK           ((uint32_t)0x00000030)
/// WF_RXFLT_PU_BIT field LSB position
#define WLAN_RF_WF_RXFLT_PU_BIT_LSB            4
/// WF_RXFLT_PU_BIT field width
#define WLAN_RF_WF_RXFLT_PU_BIT_WIDTH          ((uint32_t)0x00000002)
/// WF_ADC_PU_BIT field mask
#define WLAN_RF_WF_ADC_PU_BIT_MASK             ((uint32_t)0x0000000C)
/// WF_ADC_PU_BIT field LSB position
#define WLAN_RF_WF_ADC_PU_BIT_LSB              2
/// WF_ADC_PU_BIT field width
#define WLAN_RF_WF_ADC_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// WF_RFPLL_PU_BIT field mask
#define WLAN_RF_WF_RFPLL_PU_BIT_MASK           ((uint32_t)0x00000003)
/// WF_RFPLL_PU_BIT field LSB position
#define WLAN_RF_WF_RFPLL_PU_BIT_LSB            0
/// WF_RFPLL_PU_BIT field width
#define WLAN_RF_WF_RFPLL_PU_BIT_WIDTH          ((uint32_t)0x00000002)

/// WF_PU_ADC_VREF_PDT_DR field reset value
#define WLAN_RF_WF_PU_ADC_VREF_PDT_DR_RST      0x0
/// WF_PU_ADC_VREF_PDT_REG field reset value
#define WLAN_RF_WF_PU_ADC_VREF_PDT_REG_RST     0x0
/// WF_PU_PDADC_DR field reset value
#define WLAN_RF_WF_PU_PDADC_DR_RST             0x0
/// WF_PU_PDADC_REG field reset value
#define WLAN_RF_WF_PU_PDADC_REG_RST            0x0
/// WF_PU_RFPLL_DR field reset value
#define WLAN_RF_WF_PU_RFPLL_DR_RST             0x0
/// WF_PU_RFPLL_REG field reset value
#define WLAN_RF_WF_PU_RFPLL_REG_RST            0x0
/// WF_RFPLL_SAR_CLK_EN_DR field reset value
#define WLAN_RF_WF_RFPLL_SAR_CLK_EN_DR_RST     0x0
/// WF_RFPLL_SAR_CLK_EN_REG field reset value
#define WLAN_RF_WF_RFPLL_SAR_CLK_EN_REG_RST    0x0
/// WF_PU_VCO_DR field reset value
#define WLAN_RF_WF_PU_VCO_DR_RST               0x0
/// WF_PU_VCO_REG field reset value
#define WLAN_RF_WF_PU_VCO_REG_RST              0x0
/// WF_VCO_TXLO_EN_DR field reset value
#define WLAN_RF_WF_VCO_TXLO_EN_DR_RST          0x0
/// WF_VCO_TXLO_EN_REG field reset value
#define WLAN_RF_WF_VCO_TXLO_EN_REG_RST         0x0
/// WF_VCO_RXLO_EN_DR field reset value
#define WLAN_RF_WF_VCO_RXLO_EN_DR_RST          0x0
/// WF_VCO_RXLO_EN_REG field reset value
#define WLAN_RF_WF_VCO_RXLO_EN_REG_RST         0x0
/// WF_PU_TS_HUB field reset value
#define WLAN_RF_WF_PU_TS_HUB_RST               0x0
/// WF_LNA_PU_BIT field reset value
#define WLAN_RF_WF_LNA_PU_BIT_RST              0x1
/// WF_RMX_PU_BIT field reset value
#define WLAN_RF_WF_RMX_PU_BIT_RST              0x1
/// WF_TIA_PU_BIT field reset value
#define WLAN_RF_WF_TIA_PU_BIT_RST              0x1
/// WF_DTMX_PU_BIT_AVDD_33 field reset value
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_33_RST     0x2
/// WF_DTMX_PU_BIT_AVDD_13 field reset value
#define WLAN_RF_WF_DTMX_PU_BIT_AVDD_13_RST     0x2
/// WF_RXFLT_PU_BIT field reset value
#define WLAN_RF_WF_RXFLT_PU_BIT_RST            0x2
/// WF_ADC_PU_BIT field reset value
#define WLAN_RF_WF_ADC_PU_BIT_RST              0x2
/// WF_RFPLL_PU_BIT field reset value
#define WLAN_RF_WF_RFPLL_PU_BIT_RST            0x0

/**
 * @brief Constructs a value for the REG_01 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpuadcvrefpdtdr - The value to use for the wf_pu_adc_vref_pdt_dr field.
 * @param[in] wfpuadcvrefpdtreg - The value to use for the wf_pu_adc_vref_pdt_reg field.
 * @param[in] wfpupdadcdr - The value to use for the wf_pu_pdadc_dr field.
 * @param[in] wfpupdadcreg - The value to use for the wf_pu_pdadc_reg field.
 * @param[in] wfpurfplldr - The value to use for the wf_pu_rfpll_dr field.
 * @param[in] wfpurfpllreg - The value to use for the wf_pu_rfpll_reg field.
 * @param[in] wfrfpllsarclkendr - The value to use for the wf_rfpll_sar_clk_en_dr field.
 * @param[in] wfrfpllsarclkenreg - The value to use for the wf_rfpll_sar_clk_en_reg field.
 * @param[in] wfpuvcodr - The value to use for the wf_pu_vco_dr field.
 * @param[in] wfpuvcoreg - The value to use for the wf_pu_vco_reg field.
 * @param[in] wfvcotxloendr - The value to use for the wf_vco_txlo_en_dr field.
 * @param[in] wfvcotxloenreg - The value to use for the wf_vco_txlo_en_reg field.
 * @param[in] wfvcorxloendr - The value to use for the wf_vco_rxlo_en_dr field.
 * @param[in] wfvcorxloenreg - The value to use for the wf_vco_rxlo_en_reg field.
 * @param[in] wfputshub - The value to use for the wf_pu_ts_hub field.
 * @param[in] wflnapubit - The value to use for the wf_lna_pu_bit field.
 * @param[in] wfrmxpubit - The value to use for the wf_rmx_pu_bit field.
 * @param[in] wftiapubit - The value to use for the wf_tia_pu_bit field.
 * @param[in] wfdtmxpubitavdd33 - The value to use for the wf_dtmx_pu_bit_avdd33 field.
 * @param[in] wfdtmxpubitavdd13 - The value to use for the wf_dtmx_pu_bit_avdd13 field.
 * @param[in] wfrxfltpubit - The value to use for the wf_rxflt_pu_bit field.
 * @param[in] wfadcpubit - The value to use for the wf_adc_pu_bit field.
 * @param[in] wfrfpllpubit - The value to use for the wf_rfpll_pu_bit field.
 */
__INLINE void wlan_rf_reg_01_pack(uint8_t wfpuadcvrefpdtdr, uint8_t wfpuadcvrefpdtreg, uint8_t wfpupdadcdr, uint8_t wfpupdadcreg, uint8_t wfpurfplldr, uint8_t wfpurfpllreg, uint8_t wfrfpllsarclkendr, uint8_t wfrfpllsarclkenreg, uint8_t wfpuvcodr, uint8_t wfpuvcoreg, uint8_t wfvcotxloendr, uint8_t wfvcotxloenreg, uint8_t wfvcorxloendr, uint8_t wfvcorxloenreg, uint8_t wfputshub, uint8_t wflnapubit, uint8_t wfrmxpubit, uint8_t wftiapubit, uint8_t wfdtmxpubitavdd33, uint8_t wfdtmxpubitavdd13, uint8_t wfrxfltpubit, uint8_t wfadcpubit, uint8_t wfrfpllpubit)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR,  ((uint32_t)wfpuadcvrefpdtdr << 30) | ((uint32_t)wfpuadcvrefpdtreg << 29) | ((uint32_t)wfpupdadcdr << 28) | ((uint32_t)wfpupdadcreg << 27) | ((uint32_t)wfpurfplldr << 26) | ((uint32_t)wfpurfpllreg << 25) | ((uint32_t)wfrfpllsarclkendr << 24) | ((uint32_t)wfrfpllsarclkenreg << 23) | ((uint32_t)wfpuvcodr << 22) | ((uint32_t)wfpuvcoreg << 21) | ((uint32_t)wfvcotxloendr << 20) | ((uint32_t)wfvcotxloenreg << 19) | ((uint32_t)wfvcorxloendr << 18) | ((uint32_t)wfvcorxloenreg << 17) | ((uint32_t)wfputshub << 16) | ((uint32_t)wflnapubit << 14) | ((uint32_t)wfrmxpubit << 12) | ((uint32_t)wftiapubit << 10) | ((uint32_t)wfdtmxpubitavdd33 << 8) | ((uint32_t)wfdtmxpubitavdd13 << 6) | ((uint32_t)wfrxfltpubit << 4) | ((uint32_t)wfadcpubit << 2) | ((uint32_t)wfrfpllpubit << 0));
}

/**
 * @brief Unpacks REG_01's fields from current value of the REG_01 register.
 *
 * Reads the REG_01 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpuadcvrefpdtdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpuadcvrefpdtreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpupdadcdr - Will be populated with the current value of this field from the register.
 * @param[out] wfpupdadcreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpurfplldr - Will be populated with the current value of this field from the register.
 * @param[out] wfpurfpllreg - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllsarclkendr - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllsarclkenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpuvcodr - Will be populated with the current value of this field from the register.
 * @param[out] wfpuvcoreg - Will be populated with the current value of this field from the register.
 * @param[out] wfvcotxloendr - Will be populated with the current value of this field from the register.
 * @param[out] wfvcotxloenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfvcorxloendr - Will be populated with the current value of this field from the register.
 * @param[out] wfvcorxloenreg - Will be populated with the current value of this field from the register.
 * @param[out] wfputshub - Will be populated with the current value of this field from the register.
 * @param[out] wflnapubit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxpubit - Will be populated with the current value of this field from the register.
 * @param[out] wftiapubit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxpubitavdd33 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxpubitavdd13 - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltpubit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcpubit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllpubit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_01_unpack(uint8_t* wfpuadcvrefpdtdr, uint8_t* wfpuadcvrefpdtreg, uint8_t* wfpupdadcdr, uint8_t* wfpupdadcreg, uint8_t* wfpurfplldr, uint8_t* wfpurfpllreg, uint8_t* wfrfpllsarclkendr, uint8_t* wfrfpllsarclkenreg, uint8_t* wfpuvcodr, uint8_t* wfpuvcoreg, uint8_t* wfvcotxloendr, uint8_t* wfvcotxloenreg, uint8_t* wfvcorxloendr, uint8_t* wfvcorxloenreg, uint8_t* wfputshub, uint8_t* wflnapubit, uint8_t* wfrmxpubit, uint8_t* wftiapubit, uint8_t* wfdtmxpubitavdd33, uint8_t* wfdtmxpubitavdd13, uint8_t* wfrxfltpubit, uint8_t* wfadcpubit, uint8_t* wfrfpllpubit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);

    *wfpuadcvrefpdtdr = (localVal & ((uint32_t)0x40000000)) >> 30;
    *wfpuadcvrefpdtreg = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wfpupdadcdr = (localVal & ((uint32_t)0x10000000)) >> 28;
    *wfpupdadcreg = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfpurfplldr = (localVal & ((uint32_t)0x04000000)) >> 26;
    *wfpurfpllreg = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wfrfpllsarclkendr = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wfrfpllsarclkenreg = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfpuvcodr = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wfpuvcoreg = (localVal & ((uint32_t)0x00200000)) >> 21;
    *wfvcotxloendr = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wfvcotxloenreg = (localVal & ((uint32_t)0x00080000)) >> 19;
    *wfvcorxloendr = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfvcorxloenreg = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wfputshub = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wflnapubit = (localVal & ((uint32_t)0x0000C000)) >> 14;
    *wfrmxpubit = (localVal & ((uint32_t)0x00003000)) >> 12;
    *wftiapubit = (localVal & ((uint32_t)0x00000C00)) >> 10;
    *wfdtmxpubitavdd33 = (localVal & ((uint32_t)0x00000300)) >> 8;
    *wfdtmxpubitavdd13 = (localVal & ((uint32_t)0x000000C0)) >> 6;
    *wfrxfltpubit = (localVal & ((uint32_t)0x00000030)) >> 4;
    *wfadcpubit = (localVal & ((uint32_t)0x0000000C)) >> 2;
    *wfrfpllpubit = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pu_adc_vref_pdt_dr field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_pu_adc_vref_pdt_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_vref_pdt_dr field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_vref_pdt_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the wf_pu_adc_vref_pdt_dr field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcvrefpdtdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_vref_pdt_dr_setf(uint8_t wfpuadcvrefpdtdr)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)wfpuadcvrefpdtdr << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_vref_pdt_reg field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_pu_adc_vref_pdt_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_vref_pdt_reg field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_vref_pdt_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the wf_pu_adc_vref_pdt_reg field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcvrefpdtreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_vref_pdt_reg_setf(uint8_t wfpuadcvrefpdtreg)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wfpuadcvrefpdtreg << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the wf_pu_pdadc_dr field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_pu_pdadc_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_pdadc_dr field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_pdadc_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the wf_pu_pdadc_dr field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpupdadcdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_pdadc_dr_setf(uint8_t wfpupdadcdr)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)wfpupdadcdr << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the wf_pu_pdadc_reg field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_pu_pdadc_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_pdadc_reg field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_pdadc_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_pu_pdadc_reg field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpupdadcreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_pdadc_reg_setf(uint8_t wfpupdadcreg)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wfpupdadcreg << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_pu_rfpll_dr field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_pu_rfpll_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_rfpll_dr field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rfpll_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the wf_pu_rfpll_dr field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurfplldr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rfpll_dr_setf(uint8_t wfpurfplldr)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)wfpurfplldr << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the wf_pu_rfpll_reg field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_pu_rfpll_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_rfpll_reg field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rfpll_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_pu_rfpll_reg field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurfpllreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rfpll_reg_setf(uint8_t wfpurfpllreg)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wfpurfpllreg << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_sar_clk_en_dr field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_rfpll_sar_clk_en_dr field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sar_clk_en_dr field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sar_clk_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the wf_rfpll_sar_clk_en_dr field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllsarclkendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_sar_clk_en_dr_setf(uint8_t wfrfpllsarclkendr)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wfrfpllsarclkendr << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_sar_clk_en_reg field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_rfpll_sar_clk_en_reg field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sar_clk_en_reg field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sar_clk_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_rfpll_sar_clk_en_reg field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllsarclkenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_sar_clk_en_reg_setf(uint8_t wfrfpllsarclkenreg)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wfrfpllsarclkenreg << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_pu_vco_dr field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_pu_vco_dr field's value will be returned.
 *
 * @return The current value of the wf_pu_vco_dr field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_vco_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the wf_pu_vco_dr field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuvcodr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_vco_dr_setf(uint8_t wfpuvcodr)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)wfpuvcodr << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the wf_pu_vco_reg field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_pu_vco_reg field's value will be returned.
 *
 * @return The current value of the wf_pu_vco_reg field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_vco_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Sets the wf_pu_vco_reg field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuvcoreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_vco_reg_setf(uint8_t wfpuvcoreg)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00200000)) | (((uint32_t)wfpuvcoreg << 21) & ((uint32_t)0x00200000)));
}

/**
 * @brief Returns the current value of the wf_vco_txlo_en_dr field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_vco_txlo_en_dr field's value will be returned.
 *
 * @return The current value of the wf_vco_txlo_en_dr field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_txlo_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_vco_txlo_en_dr field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcotxloendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_txlo_en_dr_setf(uint8_t wfvcotxloendr)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wfvcotxloendr << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the wf_vco_txlo_en_reg field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_vco_txlo_en_reg field's value will be returned.
 *
 * @return The current value of the wf_vco_txlo_en_reg field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_txlo_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

/**
 * @brief Sets the wf_vco_txlo_en_reg field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcotxloenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_txlo_en_reg_setf(uint8_t wfvcotxloenreg)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00080000)) | (((uint32_t)wfvcotxloenreg << 19) & ((uint32_t)0x00080000)));
}

/**
 * @brief Returns the current value of the wf_vco_rxlo_en_dr field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_vco_rxlo_en_dr field's value will be returned.
 *
 * @return The current value of the wf_vco_rxlo_en_dr field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_rxlo_en_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_vco_rxlo_en_dr field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcorxloendr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_rxlo_en_dr_setf(uint8_t wfvcorxloendr)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wfvcorxloendr << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_vco_rxlo_en_reg field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_vco_rxlo_en_reg field's value will be returned.
 *
 * @return The current value of the wf_vco_rxlo_en_reg field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_rxlo_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_vco_rxlo_en_reg field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcorxloenreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_rxlo_en_reg_setf(uint8_t wfvcorxloenreg)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wfvcorxloenreg << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_pu_ts_hub field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_pu_ts_hub field's value will be returned.
 *
 * @return The current value of the wf_pu_ts_hub field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_ts_hub_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_pu_ts_hub field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfputshub - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_ts_hub_setf(uint8_t wfputshub)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wfputshub << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_lna_pu_bit field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_lna_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_lna_pu_bit field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x0000C000)) >> 14);
}

/**
 * @brief Sets the wf_lna_pu_bit field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnapubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_pu_bit_setf(uint8_t wflnapubit)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x0000C000)) | (((uint32_t)wflnapubit << 14) & ((uint32_t)0x0000C000)));
}

/**
 * @brief Returns the current value of the wf_rmx_pu_bit field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_rmx_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_rmx_pu_bit field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

/**
 * @brief Sets the wf_rmx_pu_bit field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_pu_bit_setf(uint8_t wfrmxpubit)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00003000)) | (((uint32_t)wfrmxpubit << 12) & ((uint32_t)0x00003000)));
}

/**
 * @brief Returns the current value of the wf_tia_pu_bit field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_tia_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_tia_pu_bit field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00000C00)) >> 10);
}

/**
 * @brief Sets the wf_tia_pu_bit field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiapubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_pu_bit_setf(uint8_t wftiapubit)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00000C00)) | (((uint32_t)wftiapubit << 10) & ((uint32_t)0x00000C00)));
}

/**
 * @brief Returns the current value of the wf_dtmx_pu_bit_avdd33 field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_dtmx_pu_bit_avdd33 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_pu_bit_avdd33 field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_pu_bit_avdd_33_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the wf_dtmx_pu_bit_avdd33 field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxpubitavdd33 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_pu_bit_avdd_33_setf(uint8_t wfdtmxpubitavdd33)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)wfdtmxpubitavdd33 << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the wf_dtmx_pu_bit_avdd13 field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_dtmx_pu_bit_avdd13 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_pu_bit_avdd13 field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_pu_bit_avdd_13_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x000000C0)) >> 6);
}

/**
 * @brief Sets the wf_dtmx_pu_bit_avdd13 field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxpubitavdd13 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_pu_bit_avdd_13_setf(uint8_t wfdtmxpubitavdd13)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x000000C0)) | (((uint32_t)wfdtmxpubitavdd13 << 6) & ((uint32_t)0x000000C0)));
}

/**
 * @brief Returns the current value of the wf_rxflt_pu_bit field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_rxflt_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_pu_bit field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

/**
 * @brief Sets the wf_rxflt_pu_bit field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_pu_bit_setf(uint8_t wfrxfltpubit)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00000030)) | (((uint32_t)wfrxfltpubit << 4) & ((uint32_t)0x00000030)));
}

/**
 * @brief Returns the current value of the wf_adc_pu_bit field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_adc_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_adc_pu_bit field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_adc_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x0000000C)) >> 2);
}

/**
 * @brief Sets the wf_adc_pu_bit field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_pu_bit_setf(uint8_t wfadcpubit)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x0000000C)) | (((uint32_t)wfadcpubit << 2) & ((uint32_t)0x0000000C)));
}

/**
 * @brief Returns the current value of the wf_rfpll_pu_bit field in the REG_01 register.
 *
 * The REG_01 register will be read and the wf_rfpll_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_pu_bit field in the REG_01 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_01_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the wf_rfpll_pu_bit field of the REG_01 register.
 *
 * The REG_01 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllpubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_pu_bit_setf(uint8_t wfrfpllpubit)
{
    REG_PL_WR(WLAN_RF_REG_01_ADDR, (REG_PL_RD(WLAN_RF_REG_01_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)wfrfpllpubit << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_02 register definitions
 * <table>
 * <caption id="REG_02_BF">REG_02 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:30 <td>     wf_vco_pu_bit <td>R <td>R/W <td>0x3
 * <tr><td>29 <td>  wf_dtmx_pll_test <td>R <td>R/W <td>0
 * <tr><td>28 <td>wf_test_enable_lna <td>R <td>R/W <td>0
 * <tr><td>27 <td>wf_test_enable_rmx <td>R <td>R/W <td>0
 * <tr><td>26:25 <td>wf_test_enable_tia <td>R <td>R/W <td>0x0
 * <tr><td>24 <td>wf_test_enable_dtmx <td>R <td>R/W <td>0
 * <tr><td>23 <td>wf_test_enable_iref <td>R <td>R/W <td>0
 * <tr><td>22:21 <td>wf_rxflt_test_mode <td>R <td>R/W <td>0x0
 * <tr><td>20 <td>wf_rxflt_test2gpio_en <td>R <td>R/W <td>0
 * <tr><td>19:18 <td>wf_test_enable_rxflt <td>R <td>R/W <td>0x0
 * <tr><td>17 <td>wf_test_enable_adc <td>R <td>R/W <td>0
 * <tr><td>16 <td>wf_test_enable_ts_hub <td>R <td>R/W <td>0
 * <tr><td>15:13 <td>       wf_test_bit <td>R <td>R/W <td>0x0
 * <tr><td>12 <td>wf_test_enable_rfpll <td>R <td>R/W <td>0
 * <tr><td>11 <td>wf_test_enable_vco <td>R <td>R/W <td>0
 * <tr><td>10:09 <td>     wf_pu_vco_td2 <td>R <td>R/W <td>0x1
 * <tr><td>08:06 <td>   wf_pu_rfpll_td3 <td>R <td>R/W <td>0x5
 * <tr><td>05:04 <td>   wf_tia_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>03:02 <td> wf_rxflt_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>01:00 <td>wf_pu_adc_vref_pdt_td1 <td>R <td>R/W <td>0x1
 * </table>
 *
 * @{
 */

/// Address of the REG_02 register
#define WLAN_RF_REG_02_ADDR   0x40344008
/// Offset of the REG_02 register from the base address
#define WLAN_RF_REG_02_OFFSET 0x00000008
/// Index of the REG_02 register
#define WLAN_RF_REG_02_INDEX  0x00000002
/// Reset value of the REG_02 register
#define WLAN_RF_REG_02_RESET  0xC0000355

/**
 * @brief Returns the current value of the REG_02 register.
 * The REG_02 register will be read and its value returned.
 * @return The current value of the REG_02 register.
 */
__INLINE uint32_t wlan_rf_reg_02_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_02_ADDR);
}

/**
 * @brief Sets the REG_02 register to a value.
 * The REG_02 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_02_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, value);
}

// field definitions
/// WF_VCO_PU_BIT field mask
#define WLAN_RF_WF_VCO_PU_BIT_MASK             ((uint32_t)0xC0000000)
/// WF_VCO_PU_BIT field LSB position
#define WLAN_RF_WF_VCO_PU_BIT_LSB              30
/// WF_VCO_PU_BIT field width
#define WLAN_RF_WF_VCO_PU_BIT_WIDTH            ((uint32_t)0x00000002)
/// WF_DTMX_PLL_TEST field bit
#define WLAN_RF_WF_DTMX_PLL_TEST_BIT           ((uint32_t)0x20000000)
/// WF_DTMX_PLL_TEST field position
#define WLAN_RF_WF_DTMX_PLL_TEST_POS           29
/// WF_TEST_ENABLE_LNA field bit
#define WLAN_RF_WF_TEST_ENABLE_LNA_BIT         ((uint32_t)0x10000000)
/// WF_TEST_ENABLE_LNA field position
#define WLAN_RF_WF_TEST_ENABLE_LNA_POS         28
/// WF_TEST_ENABLE_RMX field bit
#define WLAN_RF_WF_TEST_ENABLE_RMX_BIT         ((uint32_t)0x08000000)
/// WF_TEST_ENABLE_RMX field position
#define WLAN_RF_WF_TEST_ENABLE_RMX_POS         27
/// WF_TEST_ENABLE_TIA field mask
#define WLAN_RF_WF_TEST_ENABLE_TIA_MASK        ((uint32_t)0x06000000)
/// WF_TEST_ENABLE_TIA field LSB position
#define WLAN_RF_WF_TEST_ENABLE_TIA_LSB         25
/// WF_TEST_ENABLE_TIA field width
#define WLAN_RF_WF_TEST_ENABLE_TIA_WIDTH       ((uint32_t)0x00000002)
/// WF_TEST_ENABLE_DTMX field bit
#define WLAN_RF_WF_TEST_ENABLE_DTMX_BIT        ((uint32_t)0x01000000)
/// WF_TEST_ENABLE_DTMX field position
#define WLAN_RF_WF_TEST_ENABLE_DTMX_POS        24
/// WF_TEST_ENABLE_IREF field bit
#define WLAN_RF_WF_TEST_ENABLE_IREF_BIT        ((uint32_t)0x00800000)
/// WF_TEST_ENABLE_IREF field position
#define WLAN_RF_WF_TEST_ENABLE_IREF_POS        23
/// WF_RXFLT_TEST_MODE field mask
#define WLAN_RF_WF_RXFLT_TEST_MODE_MASK        ((uint32_t)0x00600000)
/// WF_RXFLT_TEST_MODE field LSB position
#define WLAN_RF_WF_RXFLT_TEST_MODE_LSB         21
/// WF_RXFLT_TEST_MODE field width
#define WLAN_RF_WF_RXFLT_TEST_MODE_WIDTH       ((uint32_t)0x00000002)
/// WF_RXFLT_TEST_2GPIO_EN field bit
#define WLAN_RF_WF_RXFLT_TEST_2GPIO_EN_BIT     ((uint32_t)0x00100000)
/// WF_RXFLT_TEST_2GPIO_EN field position
#define WLAN_RF_WF_RXFLT_TEST_2GPIO_EN_POS     20
/// WF_TEST_ENABLE_RXFLT field mask
#define WLAN_RF_WF_TEST_ENABLE_RXFLT_MASK      ((uint32_t)0x000C0000)
/// WF_TEST_ENABLE_RXFLT field LSB position
#define WLAN_RF_WF_TEST_ENABLE_RXFLT_LSB       18
/// WF_TEST_ENABLE_RXFLT field width
#define WLAN_RF_WF_TEST_ENABLE_RXFLT_WIDTH     ((uint32_t)0x00000002)
/// WF_TEST_ENABLE_ADC field bit
#define WLAN_RF_WF_TEST_ENABLE_ADC_BIT         ((uint32_t)0x00020000)
/// WF_TEST_ENABLE_ADC field position
#define WLAN_RF_WF_TEST_ENABLE_ADC_POS         17
/// WF_TEST_ENABLE_TS_HUB field bit
#define WLAN_RF_WF_TEST_ENABLE_TS_HUB_BIT      ((uint32_t)0x00010000)
/// WF_TEST_ENABLE_TS_HUB field position
#define WLAN_RF_WF_TEST_ENABLE_TS_HUB_POS      16
/// WF_TEST_BIT field mask
#define WLAN_RF_WF_TEST_BIT_MASK               ((uint32_t)0x0000E000)
/// WF_TEST_BIT field LSB position
#define WLAN_RF_WF_TEST_BIT_LSB                13
/// WF_TEST_BIT field width
#define WLAN_RF_WF_TEST_BIT_WIDTH              ((uint32_t)0x00000003)
/// WF_TEST_ENABLE_RFPLL field bit
#define WLAN_RF_WF_TEST_ENABLE_RFPLL_BIT       ((uint32_t)0x00001000)
/// WF_TEST_ENABLE_RFPLL field position
#define WLAN_RF_WF_TEST_ENABLE_RFPLL_POS       12
/// WF_TEST_ENABLE_VCO field bit
#define WLAN_RF_WF_TEST_ENABLE_VCO_BIT         ((uint32_t)0x00000800)
/// WF_TEST_ENABLE_VCO field position
#define WLAN_RF_WF_TEST_ENABLE_VCO_POS         11
/// WF_PU_VCO_TD_2 field mask
#define WLAN_RF_WF_PU_VCO_TD_2_MASK            ((uint32_t)0x00000600)
/// WF_PU_VCO_TD_2 field LSB position
#define WLAN_RF_WF_PU_VCO_TD_2_LSB             9
/// WF_PU_VCO_TD_2 field width
#define WLAN_RF_WF_PU_VCO_TD_2_WIDTH           ((uint32_t)0x00000002)
/// WF_PU_RFPLL_TD_3 field mask
#define WLAN_RF_WF_PU_RFPLL_TD_3_MASK          ((uint32_t)0x000001C0)
/// WF_PU_RFPLL_TD_3 field LSB position
#define WLAN_RF_WF_PU_RFPLL_TD_3_LSB           6
/// WF_PU_RFPLL_TD_3 field width
#define WLAN_RF_WF_PU_RFPLL_TD_3_WIDTH         ((uint32_t)0x00000003)
/// WF_TIA_RSTN_TD_1 field mask
#define WLAN_RF_WF_TIA_RSTN_TD_1_MASK          ((uint32_t)0x00000030)
/// WF_TIA_RSTN_TD_1 field LSB position
#define WLAN_RF_WF_TIA_RSTN_TD_1_LSB           4
/// WF_TIA_RSTN_TD_1 field width
#define WLAN_RF_WF_TIA_RSTN_TD_1_WIDTH         ((uint32_t)0x00000002)
/// WF_RXFLT_RSTN_TD_1 field mask
#define WLAN_RF_WF_RXFLT_RSTN_TD_1_MASK        ((uint32_t)0x0000000C)
/// WF_RXFLT_RSTN_TD_1 field LSB position
#define WLAN_RF_WF_RXFLT_RSTN_TD_1_LSB         2
/// WF_RXFLT_RSTN_TD_1 field width
#define WLAN_RF_WF_RXFLT_RSTN_TD_1_WIDTH       ((uint32_t)0x00000002)
/// WF_PU_ADC_VREF_PDT_TD_1 field mask
#define WLAN_RF_WF_PU_ADC_VREF_PDT_TD_1_MASK   ((uint32_t)0x00000003)
/// WF_PU_ADC_VREF_PDT_TD_1 field LSB position
#define WLAN_RF_WF_PU_ADC_VREF_PDT_TD_1_LSB    0
/// WF_PU_ADC_VREF_PDT_TD_1 field width
#define WLAN_RF_WF_PU_ADC_VREF_PDT_TD_1_WIDTH  ((uint32_t)0x00000002)

/// WF_VCO_PU_BIT field reset value
#define WLAN_RF_WF_VCO_PU_BIT_RST              0x3
/// WF_DTMX_PLL_TEST field reset value
#define WLAN_RF_WF_DTMX_PLL_TEST_RST           0x0
/// WF_TEST_ENABLE_LNA field reset value
#define WLAN_RF_WF_TEST_ENABLE_LNA_RST         0x0
/// WF_TEST_ENABLE_RMX field reset value
#define WLAN_RF_WF_TEST_ENABLE_RMX_RST         0x0
/// WF_TEST_ENABLE_TIA field reset value
#define WLAN_RF_WF_TEST_ENABLE_TIA_RST         0x0
/// WF_TEST_ENABLE_DTMX field reset value
#define WLAN_RF_WF_TEST_ENABLE_DTMX_RST        0x0
/// WF_TEST_ENABLE_IREF field reset value
#define WLAN_RF_WF_TEST_ENABLE_IREF_RST        0x0
/// WF_RXFLT_TEST_MODE field reset value
#define WLAN_RF_WF_RXFLT_TEST_MODE_RST         0x0
/// WF_RXFLT_TEST_2GPIO_EN field reset value
#define WLAN_RF_WF_RXFLT_TEST_2GPIO_EN_RST     0x0
/// WF_TEST_ENABLE_RXFLT field reset value
#define WLAN_RF_WF_TEST_ENABLE_RXFLT_RST       0x0
/// WF_TEST_ENABLE_ADC field reset value
#define WLAN_RF_WF_TEST_ENABLE_ADC_RST         0x0
/// WF_TEST_ENABLE_TS_HUB field reset value
#define WLAN_RF_WF_TEST_ENABLE_TS_HUB_RST      0x0
/// WF_TEST_BIT field reset value
#define WLAN_RF_WF_TEST_BIT_RST                0x0
/// WF_TEST_ENABLE_RFPLL field reset value
#define WLAN_RF_WF_TEST_ENABLE_RFPLL_RST       0x0
/// WF_TEST_ENABLE_VCO field reset value
#define WLAN_RF_WF_TEST_ENABLE_VCO_RST         0x0
/// WF_PU_VCO_TD_2 field reset value
#define WLAN_RF_WF_PU_VCO_TD_2_RST             0x1
/// WF_PU_RFPLL_TD_3 field reset value
#define WLAN_RF_WF_PU_RFPLL_TD_3_RST           0x5
/// WF_TIA_RSTN_TD_1 field reset value
#define WLAN_RF_WF_TIA_RSTN_TD_1_RST           0x1
/// WF_RXFLT_RSTN_TD_1 field reset value
#define WLAN_RF_WF_RXFLT_RSTN_TD_1_RST         0x1
/// WF_PU_ADC_VREF_PDT_TD_1 field reset value
#define WLAN_RF_WF_PU_ADC_VREF_PDT_TD_1_RST    0x1

/**
 * @brief Constructs a value for the REG_02 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfvcopubit - The value to use for the wf_vco_pu_bit field.
 * @param[in] wfdtmxplltest - The value to use for the wf_dtmx_pll_test field.
 * @param[in] wftestenablelna - The value to use for the wf_test_enable_lna field.
 * @param[in] wftestenablermx - The value to use for the wf_test_enable_rmx field.
 * @param[in] wftestenabletia - The value to use for the wf_test_enable_tia field.
 * @param[in] wftestenabledtmx - The value to use for the wf_test_enable_dtmx field.
 * @param[in] wftestenableiref - The value to use for the wf_test_enable_iref field.
 * @param[in] wfrxflttestmode - The value to use for the wf_rxflt_test_mode field.
 * @param[in] wfrxflttest2gpioen - The value to use for the wf_rxflt_test2gpio_en field.
 * @param[in] wftestenablerxflt - The value to use for the wf_test_enable_rxflt field.
 * @param[in] wftestenableadc - The value to use for the wf_test_enable_adc field.
 * @param[in] wftestenabletshub - The value to use for the wf_test_enable_ts_hub field.
 * @param[in] wftestbit - The value to use for the wf_test_bit field.
 * @param[in] wftestenablerfpll - The value to use for the wf_test_enable_rfpll field.
 * @param[in] wftestenablevco - The value to use for the wf_test_enable_vco field.
 * @param[in] wfpuvcotd2 - The value to use for the wf_pu_vco_td2 field.
 * @param[in] wfpurfplltd3 - The value to use for the wf_pu_rfpll_td3 field.
 * @param[in] wftiarstntd1 - The value to use for the wf_tia_rstn_td1 field.
 * @param[in] wfrxfltrstntd1 - The value to use for the wf_rxflt_rstn_td1 field.
 * @param[in] wfpuadcvrefpdttd1 - The value to use for the wf_pu_adc_vref_pdt_td1 field.
 */
__INLINE void wlan_rf_reg_02_pack(uint8_t wfvcopubit, uint8_t wfdtmxplltest, uint8_t wftestenablelna, uint8_t wftestenablermx, uint8_t wftestenabletia, uint8_t wftestenabledtmx, uint8_t wftestenableiref, uint8_t wfrxflttestmode, uint8_t wfrxflttest2gpioen, uint8_t wftestenablerxflt, uint8_t wftestenableadc, uint8_t wftestenabletshub, uint8_t wftestbit, uint8_t wftestenablerfpll, uint8_t wftestenablevco, uint8_t wfpuvcotd2, uint8_t wfpurfplltd3, uint8_t wftiarstntd1, uint8_t wfrxfltrstntd1, uint8_t wfpuadcvrefpdttd1)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR,  ((uint32_t)wfvcopubit << 30) | ((uint32_t)wfdtmxplltest << 29) | ((uint32_t)wftestenablelna << 28) | ((uint32_t)wftestenablermx << 27) | ((uint32_t)wftestenabletia << 25) | ((uint32_t)wftestenabledtmx << 24) | ((uint32_t)wftestenableiref << 23) | ((uint32_t)wfrxflttestmode << 21) | ((uint32_t)wfrxflttest2gpioen << 20) | ((uint32_t)wftestenablerxflt << 18) | ((uint32_t)wftestenableadc << 17) | ((uint32_t)wftestenabletshub << 16) | ((uint32_t)wftestbit << 13) | ((uint32_t)wftestenablerfpll << 12) | ((uint32_t)wftestenablevco << 11) | ((uint32_t)wfpuvcotd2 << 9) | ((uint32_t)wfpurfplltd3 << 6) | ((uint32_t)wftiarstntd1 << 4) | ((uint32_t)wfrxfltrstntd1 << 2) | ((uint32_t)wfpuadcvrefpdttd1 << 0));
}

/**
 * @brief Unpacks REG_02's fields from current value of the REG_02 register.
 *
 * Reads the REG_02 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfvcopubit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxplltest - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablelna - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablermx - Will be populated with the current value of this field from the register.
 * @param[out] wftestenabletia - Will be populated with the current value of this field from the register.
 * @param[out] wftestenabledtmx - Will be populated with the current value of this field from the register.
 * @param[out] wftestenableiref - Will be populated with the current value of this field from the register.
 * @param[out] wfrxflttestmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrxflttest2gpioen - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablerxflt - Will be populated with the current value of this field from the register.
 * @param[out] wftestenableadc - Will be populated with the current value of this field from the register.
 * @param[out] wftestenabletshub - Will be populated with the current value of this field from the register.
 * @param[out] wftestbit - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablerfpll - Will be populated with the current value of this field from the register.
 * @param[out] wftestenablevco - Will be populated with the current value of this field from the register.
 * @param[out] wfpuvcotd2 - Will be populated with the current value of this field from the register.
 * @param[out] wfpurfplltd3 - Will be populated with the current value of this field from the register.
 * @param[out] wftiarstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltrstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpuadcvrefpdttd1 - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_02_unpack(uint8_t* wfvcopubit, uint8_t* wfdtmxplltest, uint8_t* wftestenablelna, uint8_t* wftestenablermx, uint8_t* wftestenabletia, uint8_t* wftestenabledtmx, uint8_t* wftestenableiref, uint8_t* wfrxflttestmode, uint8_t* wfrxflttest2gpioen, uint8_t* wftestenablerxflt, uint8_t* wftestenableadc, uint8_t* wftestenabletshub, uint8_t* wftestbit, uint8_t* wftestenablerfpll, uint8_t* wftestenablevco, uint8_t* wfpuvcotd2, uint8_t* wfpurfplltd3, uint8_t* wftiarstntd1, uint8_t* wfrxfltrstntd1, uint8_t* wfpuadcvrefpdttd1)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);

    *wfvcopubit = (localVal & ((uint32_t)0xC0000000)) >> 30;
    *wfdtmxplltest = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wftestenablelna = (localVal & ((uint32_t)0x10000000)) >> 28;
    *wftestenablermx = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wftestenabletia = (localVal & ((uint32_t)0x06000000)) >> 25;
    *wftestenabledtmx = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wftestenableiref = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfrxflttestmode = (localVal & ((uint32_t)0x00600000)) >> 21;
    *wfrxflttest2gpioen = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wftestenablerxflt = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *wftestenableadc = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wftestenabletshub = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wftestbit = (localVal & ((uint32_t)0x0000E000)) >> 13;
    *wftestenablerfpll = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wftestenablevco = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wfpuvcotd2 = (localVal & ((uint32_t)0x00000600)) >> 9;
    *wfpurfplltd3 = (localVal & ((uint32_t)0x000001C0)) >> 6;
    *wftiarstntd1 = (localVal & ((uint32_t)0x00000030)) >> 4;
    *wfrxfltrstntd1 = (localVal & ((uint32_t)0x0000000C)) >> 2;
    *wfpuadcvrefpdttd1 = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_vco_pu_bit field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_vco_pu_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_pu_bit field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_pu_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0xC0000000)) >> 30);
}

/**
 * @brief Sets the wf_vco_pu_bit field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcopubit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_pu_bit_setf(uint8_t wfvcopubit)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0xC0000000)) | (((uint32_t)wfvcopubit << 30) & ((uint32_t)0xC0000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_pll_test field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_dtmx_pll_test field's value will be returned.
 *
 * @return The current value of the wf_dtmx_pll_test field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_pll_test_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the wf_dtmx_pll_test field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxplltest - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_pll_test_setf(uint8_t wfdtmxplltest)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wfdtmxplltest << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_lna field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_lna field's value will be returned.
 *
 * @return The current value of the wf_test_enable_lna field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the wf_test_enable_lna field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablelna - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_lna_setf(uint8_t wftestenablelna)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)wftestenablelna << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_rmx field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_rmx field's value will be returned.
 *
 * @return The current value of the wf_test_enable_rmx field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_rmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_test_enable_rmx field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablermx - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_rmx_setf(uint8_t wftestenablermx)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wftestenablermx << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_tia field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_tia field's value will be returned.
 *
 * @return The current value of the wf_test_enable_tia field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_tia_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x06000000)) >> 25);
}

/**
 * @brief Sets the wf_test_enable_tia field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenabletia - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_tia_setf(uint8_t wftestenabletia)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x06000000)) | (((uint32_t)wftestenabletia << 25) & ((uint32_t)0x06000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_dtmx field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_dtmx field's value will be returned.
 *
 * @return The current value of the wf_test_enable_dtmx field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_dtmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the wf_test_enable_dtmx field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenabledtmx - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_dtmx_setf(uint8_t wftestenabledtmx)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wftestenabledtmx << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_iref field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_iref field's value will be returned.
 *
 * @return The current value of the wf_test_enable_iref field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_iref_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_test_enable_iref field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenableiref - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_iref_setf(uint8_t wftestenableiref)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wftestenableiref << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_rxflt_test_mode field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_rxflt_test_mode field's value will be returned.
 *
 * @return The current value of the wf_rxflt_test_mode field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_test_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00600000)) >> 21);
}

/**
 * @brief Sets the wf_rxflt_test_mode field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxflttestmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_test_mode_setf(uint8_t wfrxflttestmode)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00600000)) | (((uint32_t)wfrxflttestmode << 21) & ((uint32_t)0x00600000)));
}

/**
 * @brief Returns the current value of the wf_rxflt_test2gpio_en field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_rxflt_test2gpio_en field's value will be returned.
 *
 * @return The current value of the wf_rxflt_test2gpio_en field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_test_2gpio_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_rxflt_test2gpio_en field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxflttest2gpioen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_test_2gpio_en_setf(uint8_t wfrxflttest2gpioen)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wfrxflttest2gpioen << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_rxflt field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_rxflt field's value will be returned.
 *
 * @return The current value of the wf_test_enable_rxflt field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_rxflt_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the wf_test_enable_rxflt field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablerxflt - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_rxflt_setf(uint8_t wftestenablerxflt)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)wftestenablerxflt << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_adc field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_adc field's value will be returned.
 *
 * @return The current value of the wf_test_enable_adc field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_adc_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_test_enable_adc field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenableadc - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_adc_setf(uint8_t wftestenableadc)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wftestenableadc << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_ts_hub field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_ts_hub field's value will be returned.
 *
 * @return The current value of the wf_test_enable_ts_hub field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_ts_hub_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_test_enable_ts_hub field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenabletshub - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_ts_hub_setf(uint8_t wftestenabletshub)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wftestenabletshub << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_test_bit field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_bit field's value will be returned.
 *
 * @return The current value of the wf_test_bit field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x0000E000)) >> 13);
}

/**
 * @brief Sets the wf_test_bit field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_bit_setf(uint8_t wftestbit)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x0000E000)) | (((uint32_t)wftestbit << 13) & ((uint32_t)0x0000E000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_rfpll field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_rfpll field's value will be returned.
 *
 * @return The current value of the wf_test_enable_rfpll field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_rfpll_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_test_enable_rfpll field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablerfpll - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_rfpll_setf(uint8_t wftestenablerfpll)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wftestenablerfpll << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the wf_test_enable_vco field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_test_enable_vco field's value will be returned.
 *
 * @return The current value of the wf_test_enable_vco field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_test_enable_vco_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_test_enable_vco field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftestenablevco - The value to set the field to.
 */
__INLINE void wlan_rf_wf_test_enable_vco_setf(uint8_t wftestenablevco)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wftestenablevco << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_pu_vco_td2 field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_pu_vco_td2 field's value will be returned.
 *
 * @return The current value of the wf_pu_vco_td2 field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_vco_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00000600)) >> 9);
}

/**
 * @brief Sets the wf_pu_vco_td2 field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuvcotd2 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_vco_td_2_setf(uint8_t wfpuvcotd2)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00000600)) | (((uint32_t)wfpuvcotd2 << 9) & ((uint32_t)0x00000600)));
}

/**
 * @brief Returns the current value of the wf_pu_rfpll_td3 field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_pu_rfpll_td3 field's value will be returned.
 *
 * @return The current value of the wf_pu_rfpll_td3 field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rfpll_td_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x000001C0)) >> 6);
}

/**
 * @brief Sets the wf_pu_rfpll_td3 field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurfplltd3 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rfpll_td_3_setf(uint8_t wfpurfplltd3)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x000001C0)) | (((uint32_t)wfpurfplltd3 << 6) & ((uint32_t)0x000001C0)));
}

/**
 * @brief Returns the current value of the wf_tia_rstn_td1 field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_tia_rstn_td1 field's value will be returned.
 *
 * @return The current value of the wf_tia_rstn_td1 field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

/**
 * @brief Sets the wf_tia_rstn_td1 field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiarstntd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_rstn_td_1_setf(uint8_t wftiarstntd1)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00000030)) | (((uint32_t)wftiarstntd1 << 4) & ((uint32_t)0x00000030)));
}

/**
 * @brief Returns the current value of the wf_rxflt_rstn_td1 field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_rxflt_rstn_td1 field's value will be returned.
 *
 * @return The current value of the wf_rxflt_rstn_td1 field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x0000000C)) >> 2);
}

/**
 * @brief Sets the wf_rxflt_rstn_td1 field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltrstntd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_rstn_td_1_setf(uint8_t wfrxfltrstntd1)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x0000000C)) | (((uint32_t)wfrxfltrstntd1 << 2) & ((uint32_t)0x0000000C)));
}

/**
 * @brief Returns the current value of the wf_pu_adc_vref_pdt_td1 field in the REG_02 register.
 *
 * The REG_02 register will be read and the wf_pu_adc_vref_pdt_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_adc_vref_pdt_td1 field in the REG_02 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_adc_vref_pdt_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_02_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the wf_pu_adc_vref_pdt_td1 field of the REG_02 register.
 *
 * The REG_02 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpuadcvrefpdttd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_adc_vref_pdt_td_1_setf(uint8_t wfpuadcvrefpdttd1)
{
    REG_PL_WR(WLAN_RF_REG_02_ADDR, (REG_PL_RD(WLAN_RF_REG_02_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)wfpuadcvrefpdttd1 << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_03 register definitions
 * <table>
 * <caption id="REG_03_BF">REG_03 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:30 <td>     wf_pu_rmx_td1 <td>R <td>R/W <td>0x1
 * <tr><td>29:28 <td>     wf_pu_lna_td1 <td>R <td>R/W <td>0x1
 * <tr><td>27:26 <td>    wf_pu_dtmx_td1 <td>R <td>R/W <td>0x1
 * <tr><td>25:24 <td>wf_dtmx_cdr_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>23:22 <td>      wf_pu_pa_td1 <td>R <td>R/W <td>0x1
 * <tr><td>21:20 <td>wf_pa_pkdet_rstn_td1 <td>R <td>R/W <td>0x1
 * <tr><td>19:18 <td>wf_pa_pkdet_rstn_td2 <td>R <td>R/W <td>0x1
 * <tr><td>17:16 <td> wf_pa_gain_en_td1 <td>R <td>R/W <td>0x1
 * <tr><td>15:14 <td>         wf_pd_td0 <td>R <td>R/W <td>0x1
 * <tr><td>13:11 <td>   wf_lna_reg_vbit <td>R <td>R/W <td>0x4
 * <tr><td>10 <td>wf_lna_mixer1st_en <td>W <td>R <td>0
 * <tr><td>09:08 <td>       wf_lna_gbit <td>W <td>R <td>0x3
 * <tr><td>07:04 <td>  wf_lna_ibias_bit <td>W <td>R <td>0x8
 * <tr><td>03:00 <td>    wf_lna_cg_vbit <td>R <td>R/W <td>0x5
 * </table>
 *
 * @{
 */

/// Address of the REG_03 register
#define WLAN_RF_REG_03_ADDR   0x4034400C
/// Offset of the REG_03 register from the base address
#define WLAN_RF_REG_03_OFFSET 0x0000000C
/// Index of the REG_03 register
#define WLAN_RF_REG_03_INDEX  0x00000003
/// Reset value of the REG_03 register
#define WLAN_RF_REG_03_RESET  0x55556385

/**
 * @brief Returns the current value of the REG_03 register.
 * The REG_03 register will be read and its value returned.
 * @return The current value of the REG_03 register.
 */
__INLINE uint32_t wlan_rf_reg_03_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_03_ADDR);
}

/**
 * @brief Sets the REG_03 register to a value.
 * The REG_03 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_03_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, value);
}

// field definitions
/// WF_PU_RMX_TD_1 field mask
#define WLAN_RF_WF_PU_RMX_TD_1_MASK          ((uint32_t)0xC0000000)
/// WF_PU_RMX_TD_1 field LSB position
#define WLAN_RF_WF_PU_RMX_TD_1_LSB           30
/// WF_PU_RMX_TD_1 field width
#define WLAN_RF_WF_PU_RMX_TD_1_WIDTH         ((uint32_t)0x00000002)
/// WF_PU_LNA_TD_1 field mask
#define WLAN_RF_WF_PU_LNA_TD_1_MASK          ((uint32_t)0x30000000)
/// WF_PU_LNA_TD_1 field LSB position
#define WLAN_RF_WF_PU_LNA_TD_1_LSB           28
/// WF_PU_LNA_TD_1 field width
#define WLAN_RF_WF_PU_LNA_TD_1_WIDTH         ((uint32_t)0x00000002)
/// WF_PU_DTMX_TD_1 field mask
#define WLAN_RF_WF_PU_DTMX_TD_1_MASK         ((uint32_t)0x0C000000)
/// WF_PU_DTMX_TD_1 field LSB position
#define WLAN_RF_WF_PU_DTMX_TD_1_LSB          26
/// WF_PU_DTMX_TD_1 field width
#define WLAN_RF_WF_PU_DTMX_TD_1_WIDTH        ((uint32_t)0x00000002)
/// WF_DTMX_CDR_RSTN_TD_1 field mask
#define WLAN_RF_WF_DTMX_CDR_RSTN_TD_1_MASK   ((uint32_t)0x03000000)
/// WF_DTMX_CDR_RSTN_TD_1 field LSB position
#define WLAN_RF_WF_DTMX_CDR_RSTN_TD_1_LSB    24
/// WF_DTMX_CDR_RSTN_TD_1 field width
#define WLAN_RF_WF_DTMX_CDR_RSTN_TD_1_WIDTH  ((uint32_t)0x00000002)
/// WF_PU_PA_TD_1 field mask
#define WLAN_RF_WF_PU_PA_TD_1_MASK           ((uint32_t)0x00C00000)
/// WF_PU_PA_TD_1 field LSB position
#define WLAN_RF_WF_PU_PA_TD_1_LSB            22
/// WF_PU_PA_TD_1 field width
#define WLAN_RF_WF_PU_PA_TD_1_WIDTH          ((uint32_t)0x00000002)
/// WF_PA_PKDET_RSTN_TD_1 field mask
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_1_MASK   ((uint32_t)0x00300000)
/// WF_PA_PKDET_RSTN_TD_1 field LSB position
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_1_LSB    20
/// WF_PA_PKDET_RSTN_TD_1 field width
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_1_WIDTH  ((uint32_t)0x00000002)
/// WF_PA_PKDET_RSTN_TD_2 field mask
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_2_MASK   ((uint32_t)0x000C0000)
/// WF_PA_PKDET_RSTN_TD_2 field LSB position
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_2_LSB    18
/// WF_PA_PKDET_RSTN_TD_2 field width
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_2_WIDTH  ((uint32_t)0x00000002)
/// WF_PA_GAIN_EN_TD_1 field mask
#define WLAN_RF_WF_PA_GAIN_EN_TD_1_MASK      ((uint32_t)0x00030000)
/// WF_PA_GAIN_EN_TD_1 field LSB position
#define WLAN_RF_WF_PA_GAIN_EN_TD_1_LSB       16
/// WF_PA_GAIN_EN_TD_1 field width
#define WLAN_RF_WF_PA_GAIN_EN_TD_1_WIDTH     ((uint32_t)0x00000002)
/// WF_PD_TD_0 field mask
#define WLAN_RF_WF_PD_TD_0_MASK              ((uint32_t)0x0000C000)
/// WF_PD_TD_0 field LSB position
#define WLAN_RF_WF_PD_TD_0_LSB               14
/// WF_PD_TD_0 field width
#define WLAN_RF_WF_PD_TD_0_WIDTH             ((uint32_t)0x00000002)
/// WF_LNA_REG_VBIT field mask
#define WLAN_RF_WF_LNA_REG_VBIT_MASK         ((uint32_t)0x00003800)
/// WF_LNA_REG_VBIT field LSB position
#define WLAN_RF_WF_LNA_REG_VBIT_LSB          11
/// WF_LNA_REG_VBIT field width
#define WLAN_RF_WF_LNA_REG_VBIT_WIDTH        ((uint32_t)0x00000003)
/// WF_LNA_MIXER_1ST_EN field bit
#define WLAN_RF_WF_LNA_MIXER_1ST_EN_BIT      ((uint32_t)0x00000400)
/// WF_LNA_MIXER_1ST_EN field position
#define WLAN_RF_WF_LNA_MIXER_1ST_EN_POS      10
/// WF_LNA_GBIT field mask
#define WLAN_RF_WF_LNA_GBIT_MASK             ((uint32_t)0x00000300)
/// WF_LNA_GBIT field LSB position
#define WLAN_RF_WF_LNA_GBIT_LSB              8
/// WF_LNA_GBIT field width
#define WLAN_RF_WF_LNA_GBIT_WIDTH            ((uint32_t)0x00000002)
/// WF_LNA_IBIAS_BIT field mask
#define WLAN_RF_WF_LNA_IBIAS_BIT_MASK        ((uint32_t)0x000000F0)
/// WF_LNA_IBIAS_BIT field LSB position
#define WLAN_RF_WF_LNA_IBIAS_BIT_LSB         4
/// WF_LNA_IBIAS_BIT field width
#define WLAN_RF_WF_LNA_IBIAS_BIT_WIDTH       ((uint32_t)0x00000004)
/// WF_LNA_CG_VBIT field mask
#define WLAN_RF_WF_LNA_CG_VBIT_MASK          ((uint32_t)0x0000000F)
/// WF_LNA_CG_VBIT field LSB position
#define WLAN_RF_WF_LNA_CG_VBIT_LSB           0
/// WF_LNA_CG_VBIT field width
#define WLAN_RF_WF_LNA_CG_VBIT_WIDTH         ((uint32_t)0x00000004)

/// WF_PU_RMX_TD_1 field reset value
#define WLAN_RF_WF_PU_RMX_TD_1_RST           0x1
/// WF_PU_LNA_TD_1 field reset value
#define WLAN_RF_WF_PU_LNA_TD_1_RST           0x1
/// WF_PU_DTMX_TD_1 field reset value
#define WLAN_RF_WF_PU_DTMX_TD_1_RST          0x1
/// WF_DTMX_CDR_RSTN_TD_1 field reset value
#define WLAN_RF_WF_DTMX_CDR_RSTN_TD_1_RST    0x1
/// WF_PU_PA_TD_1 field reset value
#define WLAN_RF_WF_PU_PA_TD_1_RST            0x1
/// WF_PA_PKDET_RSTN_TD_1 field reset value
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_1_RST    0x1
/// WF_PA_PKDET_RSTN_TD_2 field reset value
#define WLAN_RF_WF_PA_PKDET_RSTN_TD_2_RST    0x1
/// WF_PA_GAIN_EN_TD_1 field reset value
#define WLAN_RF_WF_PA_GAIN_EN_TD_1_RST       0x1
/// WF_PD_TD_0 field reset value
#define WLAN_RF_WF_PD_TD_0_RST               0x1
/// WF_LNA_REG_VBIT field reset value
#define WLAN_RF_WF_LNA_REG_VBIT_RST          0x4
/// WF_LNA_MIXER_1ST_EN field reset value
#define WLAN_RF_WF_LNA_MIXER_1ST_EN_RST      0x0
/// WF_LNA_GBIT field reset value
#define WLAN_RF_WF_LNA_GBIT_RST              0x3
/// WF_LNA_IBIAS_BIT field reset value
#define WLAN_RF_WF_LNA_IBIAS_BIT_RST         0x8
/// WF_LNA_CG_VBIT field reset value
#define WLAN_RF_WF_LNA_CG_VBIT_RST           0x5

/**
 * @brief Constructs a value for the REG_03 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpurmxtd1 - The value to use for the wf_pu_rmx_td1 field.
 * @param[in] wfpulnatd1 - The value to use for the wf_pu_lna_td1 field.
 * @param[in] wfpudtmxtd1 - The value to use for the wf_pu_dtmx_td1 field.
 * @param[in] wfdtmxcdrrstntd1 - The value to use for the wf_dtmx_cdr_rstn_td1 field.
 * @param[in] wfpupatd1 - The value to use for the wf_pu_pa_td1 field.
 * @param[in] wfpapkdetrstntd1 - The value to use for the wf_pa_pkdet_rstn_td1 field.
 * @param[in] wfpapkdetrstntd2 - The value to use for the wf_pa_pkdet_rstn_td2 field.
 * @param[in] wfpagainentd1 - The value to use for the wf_pa_gain_en_td1 field.
 * @param[in] wfpdtd0 - The value to use for the wf_pd_td0 field.
 * @param[in] wflnaregvbit - The value to use for the wf_lna_reg_vbit field.
 * @param[in] wflnacgvbit - The value to use for the wf_lna_cg_vbit field.
 */
__INLINE void wlan_rf_reg_03_pack(uint8_t wfpurmxtd1, uint8_t wfpulnatd1, uint8_t wfpudtmxtd1, uint8_t wfdtmxcdrrstntd1, uint8_t wfpupatd1, uint8_t wfpapkdetrstntd1, uint8_t wfpapkdetrstntd2, uint8_t wfpagainentd1, uint8_t wfpdtd0, uint8_t wflnaregvbit, uint8_t wflnacgvbit)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR,  ((uint32_t)wfpurmxtd1 << 30) | ((uint32_t)wfpulnatd1 << 28) | ((uint32_t)wfpudtmxtd1 << 26) | ((uint32_t)wfdtmxcdrrstntd1 << 24) | ((uint32_t)wfpupatd1 << 22) | ((uint32_t)wfpapkdetrstntd1 << 20) | ((uint32_t)wfpapkdetrstntd2 << 18) | ((uint32_t)wfpagainentd1 << 16) | ((uint32_t)wfpdtd0 << 14) | ((uint32_t)wflnaregvbit << 11) | ((uint32_t)wflnacgvbit << 0));
}

/**
 * @brief Unpacks REG_03's fields from current value of the REG_03 register.
 *
 * Reads the REG_03 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpurmxtd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpulnatd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpudtmxtd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrrstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpupatd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetrstntd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetrstntd2 - Will be populated with the current value of this field from the register.
 * @param[out] wfpagainentd1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpdtd0 - Will be populated with the current value of this field from the register.
 * @param[out] wflnaregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wflnamixer1sten - Will be populated with the current value of this field from the register.
 * @param[out] wflnagbit - Will be populated with the current value of this field from the register.
 * @param[out] wflnaibiasbit - Will be populated with the current value of this field from the register.
 * @param[out] wflnacgvbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_03_unpack(uint8_t* wfpurmxtd1, uint8_t* wfpulnatd1, uint8_t* wfpudtmxtd1, uint8_t* wfdtmxcdrrstntd1, uint8_t* wfpupatd1, uint8_t* wfpapkdetrstntd1, uint8_t* wfpapkdetrstntd2, uint8_t* wfpagainentd1, uint8_t* wfpdtd0, uint8_t* wflnaregvbit, uint8_t* wflnamixer1sten, uint8_t* wflnagbit, uint8_t* wflnaibiasbit, uint8_t* wflnacgvbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);

    *wfpurmxtd1 = (localVal & ((uint32_t)0xC0000000)) >> 30;
    *wfpulnatd1 = (localVal & ((uint32_t)0x30000000)) >> 28;
    *wfpudtmxtd1 = (localVal & ((uint32_t)0x0C000000)) >> 26;
    *wfdtmxcdrrstntd1 = (localVal & ((uint32_t)0x03000000)) >> 24;
    *wfpupatd1 = (localVal & ((uint32_t)0x00C00000)) >> 22;
    *wfpapkdetrstntd1 = (localVal & ((uint32_t)0x00300000)) >> 20;
    *wfpapkdetrstntd2 = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *wfpagainentd1 = (localVal & ((uint32_t)0x00030000)) >> 16;
    *wfpdtd0 = (localVal & ((uint32_t)0x0000C000)) >> 14;
    *wflnaregvbit = (localVal & ((uint32_t)0x00003800)) >> 11;
    *wflnamixer1sten = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wflnagbit = (localVal & ((uint32_t)0x00000300)) >> 8;
    *wflnaibiasbit = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *wflnacgvbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pu_rmx_td1 field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_pu_rmx_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_rmx_td1 field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_rmx_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0xC0000000)) >> 30);
}

/**
 * @brief Sets the wf_pu_rmx_td1 field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpurmxtd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_rmx_td_1_setf(uint8_t wfpurmxtd1)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0xC0000000)) | (((uint32_t)wfpurmxtd1 << 30) & ((uint32_t)0xC0000000)));
}

/**
 * @brief Returns the current value of the wf_pu_lna_td1 field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_pu_lna_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_lna_td1 field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_lna_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

/**
 * @brief Sets the wf_pu_lna_td1 field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpulnatd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_lna_td_1_setf(uint8_t wfpulnatd1)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x30000000)) | (((uint32_t)wfpulnatd1 << 28) & ((uint32_t)0x30000000)));
}

/**
 * @brief Returns the current value of the wf_pu_dtmx_td1 field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_pu_dtmx_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_dtmx_td1 field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_dtmx_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x0C000000)) >> 26);
}

/**
 * @brief Sets the wf_pu_dtmx_td1 field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpudtmxtd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_dtmx_td_1_setf(uint8_t wfpudtmxtd1)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x0C000000)) | (((uint32_t)wfpudtmxtd1 << 26) & ((uint32_t)0x0C000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_rstn_td1 field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_dtmx_cdr_rstn_td1 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_rstn_td1 field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

/**
 * @brief Sets the wf_dtmx_cdr_rstn_td1 field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdrrstntd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_rstn_td_1_setf(uint8_t wfdtmxcdrrstntd1)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x03000000)) | (((uint32_t)wfdtmxcdrrstntd1 << 24) & ((uint32_t)0x03000000)));
}

/**
 * @brief Returns the current value of the wf_pu_pa_td1 field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_pu_pa_td1 field's value will be returned.
 *
 * @return The current value of the wf_pu_pa_td1 field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_pu_pa_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x00C00000)) >> 22);
}

/**
 * @brief Sets the wf_pu_pa_td1 field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpupatd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pu_pa_td_1_setf(uint8_t wfpupatd1)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x00C00000)) | (((uint32_t)wfpupatd1 << 22) & ((uint32_t)0x00C00000)));
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_rstn_td1 field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_pa_pkdet_rstn_td1 field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_rstn_td1 field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_rstn_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

/**
 * @brief Sets the wf_pa_pkdet_rstn_td1 field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkdetrstntd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkdet_rstn_td_1_setf(uint8_t wfpapkdetrstntd1)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x00300000)) | (((uint32_t)wfpapkdetrstntd1 << 20) & ((uint32_t)0x00300000)));
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_rstn_td2 field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_pa_pkdet_rstn_td2 field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_rstn_td2 field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_rstn_td_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the wf_pa_pkdet_rstn_td2 field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkdetrstntd2 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkdet_rstn_td_2_setf(uint8_t wfpapkdetrstntd2)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)wfpapkdetrstntd2 << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the wf_pa_gain_en_td1 field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_pa_gain_en_td1 field's value will be returned.
 *
 * @return The current value of the wf_pa_gain_en_td1 field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_gain_en_td_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

/**
 * @brief Sets the wf_pa_gain_en_td1 field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpagainentd1 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_gain_en_td_1_setf(uint8_t wfpagainentd1)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x00030000)) | (((uint32_t)wfpagainentd1 << 16) & ((uint32_t)0x00030000)));
}

/**
 * @brief Returns the current value of the wf_pd_td0 field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_pd_td0 field's value will be returned.
 *
 * @return The current value of the wf_pd_td0 field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_pd_td_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x0000C000)) >> 14);
}

/**
 * @brief Sets the wf_pd_td0 field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpdtd0 - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pd_td_0_setf(uint8_t wfpdtd0)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x0000C000)) | (((uint32_t)wfpdtd0 << 14) & ((uint32_t)0x0000C000)));
}

/**
 * @brief Returns the current value of the wf_lna_reg_vbit field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_lna_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_lna_reg_vbit field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x00003800)) >> 11);
}

/**
 * @brief Sets the wf_lna_reg_vbit field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnaregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_reg_vbit_setf(uint8_t wflnaregvbit)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x00003800)) | (((uint32_t)wflnaregvbit << 11) & ((uint32_t)0x00003800)));
}

/**
 * @brief Returns the current value of the wf_lna_mixer1st_en field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_lna_mixer1st_en field's value will be returned.
 *
 * @return The current value of the wf_lna_mixer1st_en field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_mixer_1st_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Returns the current value of the wf_lna_gbit field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_lna_gbit field's value will be returned.
 *
 * @return The current value of the wf_lna_gbit field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Returns the current value of the wf_lna_ibias_bit field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_lna_ibias_bit field's value will be returned.
 *
 * @return The current value of the wf_lna_ibias_bit field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_ibias_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Returns the current value of the wf_lna_cg_vbit field in the REG_03 register.
 *
 * The REG_03 register will be read and the wf_lna_cg_vbit field's value will be returned.
 *
 * @return The current value of the wf_lna_cg_vbit field in the REG_03 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_cg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_03_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the wf_lna_cg_vbit field of the REG_03 register.
 *
 * The REG_03 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnacgvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_cg_vbit_setf(uint8_t wflnacgvbit)
{
    REG_PL_WR(WLAN_RF_REG_03_ADDR, (REG_PL_RD(WLAN_RF_REG_03_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)wflnacgvbit << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name REG_04 register definitions
 * <table>
 * <caption id="REG_04_BF">REG_04 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30 <td>   wf_lna_iref_sel <td>R <td>R/W <td>0
 * <tr><td>29 <td>   wf_lna_vcm_p_dr <td>R <td>R/W <td>0
 * <tr><td>28:24 <td>  wf_lna_vcm_p_reg <td>R <td>R/W <td>0x10
 * <tr><td>23 <td>   wf_lna_vcm_n_dr <td>R <td>R/W <td>0
 * <tr><td>22:18 <td>  wf_lna_vcm_n_reg <td>R <td>R/W <td>0x10
 * <tr><td>17 <td>     wf_lna_cal_en <td>R <td>R/W <td>0
 * <tr><td>16 <td>wf_lna_cal_clk_edge <td>R <td>R/W <td>0
 * <tr><td>15 <td>   wf_lna_comp_vop <td>W <td>R <td>0
 * <tr><td>14 <td>   wf_lna_comp_von <td>W <td>R <td>0
 * <tr><td>13 <td>  wf_lna_pwrdet_en <td>R <td>R/W <td>0
 * <tr><td>12:11 <td>wf_lna_pwrdet_level <td>R <td>R/W <td>0x0
 * <tr><td>10:08 <td>   wf_rmx_reg_vbit <td>R <td>R/W <td>0x3
 * <tr><td>07:05 <td>wf_rmx_lobias_vbit <td>R <td>R/W <td>0x2
 * <tr><td>04:02 <td>  wf_rmx_cload_bit <td>W <td>R <td>0x2
 * <tr><td>01:00 <td>   wf_tia_reg_vbit <td>R <td>R/W <td>0x1
 * </table>
 *
 * @{
 */

/// Address of the REG_04 register
#define WLAN_RF_REG_04_ADDR   0x40344010
/// Offset of the REG_04 register from the base address
#define WLAN_RF_REG_04_OFFSET 0x00000010
/// Index of the REG_04 register
#define WLAN_RF_REG_04_INDEX  0x00000004
/// Reset value of the REG_04 register
#define WLAN_RF_REG_04_RESET  0x10400349

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
/// WF_LNA_IREF_SEL field bit
#define WLAN_RF_WF_LNA_IREF_SEL_BIT        ((uint32_t)0x40000000)
/// WF_LNA_IREF_SEL field position
#define WLAN_RF_WF_LNA_IREF_SEL_POS        30
/// WF_LNA_VCM_P_DR field bit
#define WLAN_RF_WF_LNA_VCM_P_DR_BIT        ((uint32_t)0x20000000)
/// WF_LNA_VCM_P_DR field position
#define WLAN_RF_WF_LNA_VCM_P_DR_POS        29
/// WF_LNA_VCM_P_REG field mask
#define WLAN_RF_WF_LNA_VCM_P_REG_MASK      ((uint32_t)0x1F000000)
/// WF_LNA_VCM_P_REG field LSB position
#define WLAN_RF_WF_LNA_VCM_P_REG_LSB       24
/// WF_LNA_VCM_P_REG field width
#define WLAN_RF_WF_LNA_VCM_P_REG_WIDTH     ((uint32_t)0x00000005)
/// WF_LNA_VCM_N_DR field bit
#define WLAN_RF_WF_LNA_VCM_N_DR_BIT        ((uint32_t)0x00800000)
/// WF_LNA_VCM_N_DR field position
#define WLAN_RF_WF_LNA_VCM_N_DR_POS        23
/// WF_LNA_VCM_N_REG field mask
#define WLAN_RF_WF_LNA_VCM_N_REG_MASK      ((uint32_t)0x007C0000)
/// WF_LNA_VCM_N_REG field LSB position
#define WLAN_RF_WF_LNA_VCM_N_REG_LSB       18
/// WF_LNA_VCM_N_REG field width
#define WLAN_RF_WF_LNA_VCM_N_REG_WIDTH     ((uint32_t)0x00000005)
/// WF_LNA_CAL_EN field bit
#define WLAN_RF_WF_LNA_CAL_EN_BIT          ((uint32_t)0x00020000)
/// WF_LNA_CAL_EN field position
#define WLAN_RF_WF_LNA_CAL_EN_POS          17
/// WF_LNA_CAL_CLK_EDGE field bit
#define WLAN_RF_WF_LNA_CAL_CLK_EDGE_BIT    ((uint32_t)0x00010000)
/// WF_LNA_CAL_CLK_EDGE field position
#define WLAN_RF_WF_LNA_CAL_CLK_EDGE_POS    16
/// WF_LNA_COMP_VOP field bit
#define WLAN_RF_WF_LNA_COMP_VOP_BIT        ((uint32_t)0x00008000)
/// WF_LNA_COMP_VOP field position
#define WLAN_RF_WF_LNA_COMP_VOP_POS        15
/// WF_LNA_COMP_VON field bit
#define WLAN_RF_WF_LNA_COMP_VON_BIT        ((uint32_t)0x00004000)
/// WF_LNA_COMP_VON field position
#define WLAN_RF_WF_LNA_COMP_VON_POS        14
/// WF_LNA_PWRDET_EN field bit
#define WLAN_RF_WF_LNA_PWRDET_EN_BIT       ((uint32_t)0x00002000)
/// WF_LNA_PWRDET_EN field position
#define WLAN_RF_WF_LNA_PWRDET_EN_POS       13
/// WF_LNA_PWRDET_LEVEL field mask
#define WLAN_RF_WF_LNA_PWRDET_LEVEL_MASK   ((uint32_t)0x00001800)
/// WF_LNA_PWRDET_LEVEL field LSB position
#define WLAN_RF_WF_LNA_PWRDET_LEVEL_LSB    11
/// WF_LNA_PWRDET_LEVEL field width
#define WLAN_RF_WF_LNA_PWRDET_LEVEL_WIDTH  ((uint32_t)0x00000002)
/// WF_RMX_REG_VBIT field mask
#define WLAN_RF_WF_RMX_REG_VBIT_MASK       ((uint32_t)0x00000700)
/// WF_RMX_REG_VBIT field LSB position
#define WLAN_RF_WF_RMX_REG_VBIT_LSB        8
/// WF_RMX_REG_VBIT field width
#define WLAN_RF_WF_RMX_REG_VBIT_WIDTH      ((uint32_t)0x00000003)
/// WF_RMX_LOBIAS_VBIT field mask
#define WLAN_RF_WF_RMX_LOBIAS_VBIT_MASK    ((uint32_t)0x000000E0)
/// WF_RMX_LOBIAS_VBIT field LSB position
#define WLAN_RF_WF_RMX_LOBIAS_VBIT_LSB     5
/// WF_RMX_LOBIAS_VBIT field width
#define WLAN_RF_WF_RMX_LOBIAS_VBIT_WIDTH   ((uint32_t)0x00000003)
/// WF_RMX_CLOAD_BIT field mask
#define WLAN_RF_WF_RMX_CLOAD_BIT_MASK      ((uint32_t)0x0000001C)
/// WF_RMX_CLOAD_BIT field LSB position
#define WLAN_RF_WF_RMX_CLOAD_BIT_LSB       2
/// WF_RMX_CLOAD_BIT field width
#define WLAN_RF_WF_RMX_CLOAD_BIT_WIDTH     ((uint32_t)0x00000003)
/// WF_TIA_REG_VBIT field mask
#define WLAN_RF_WF_TIA_REG_VBIT_MASK       ((uint32_t)0x00000003)
/// WF_TIA_REG_VBIT field LSB position
#define WLAN_RF_WF_TIA_REG_VBIT_LSB        0
/// WF_TIA_REG_VBIT field width
#define WLAN_RF_WF_TIA_REG_VBIT_WIDTH      ((uint32_t)0x00000002)

/// WF_LNA_IREF_SEL field reset value
#define WLAN_RF_WF_LNA_IREF_SEL_RST        0x0
/// WF_LNA_VCM_P_DR field reset value
#define WLAN_RF_WF_LNA_VCM_P_DR_RST        0x0
/// WF_LNA_VCM_P_REG field reset value
#define WLAN_RF_WF_LNA_VCM_P_REG_RST       0x10
/// WF_LNA_VCM_N_DR field reset value
#define WLAN_RF_WF_LNA_VCM_N_DR_RST        0x0
/// WF_LNA_VCM_N_REG field reset value
#define WLAN_RF_WF_LNA_VCM_N_REG_RST       0x10
/// WF_LNA_CAL_EN field reset value
#define WLAN_RF_WF_LNA_CAL_EN_RST          0x0
/// WF_LNA_CAL_CLK_EDGE field reset value
#define WLAN_RF_WF_LNA_CAL_CLK_EDGE_RST    0x0
/// WF_LNA_COMP_VOP field reset value
#define WLAN_RF_WF_LNA_COMP_VOP_RST        0x0
/// WF_LNA_COMP_VON field reset value
#define WLAN_RF_WF_LNA_COMP_VON_RST        0x0
/// WF_LNA_PWRDET_EN field reset value
#define WLAN_RF_WF_LNA_PWRDET_EN_RST       0x0
/// WF_LNA_PWRDET_LEVEL field reset value
#define WLAN_RF_WF_LNA_PWRDET_LEVEL_RST    0x0
/// WF_RMX_REG_VBIT field reset value
#define WLAN_RF_WF_RMX_REG_VBIT_RST        0x3
/// WF_RMX_LOBIAS_VBIT field reset value
#define WLAN_RF_WF_RMX_LOBIAS_VBIT_RST     0x2
/// WF_RMX_CLOAD_BIT field reset value
#define WLAN_RF_WF_RMX_CLOAD_BIT_RST       0x2
/// WF_TIA_REG_VBIT field reset value
#define WLAN_RF_WF_TIA_REG_VBIT_RST        0x1

/**
 * @brief Constructs a value for the REG_04 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wflnairefsel - The value to use for the wf_lna_iref_sel field.
 * @param[in] wflnavcmpdr - The value to use for the wf_lna_vcm_p_dr field.
 * @param[in] wflnavcmpreg - The value to use for the wf_lna_vcm_p_reg field.
 * @param[in] wflnavcmndr - The value to use for the wf_lna_vcm_n_dr field.
 * @param[in] wflnavcmnreg - The value to use for the wf_lna_vcm_n_reg field.
 * @param[in] wflnacalen - The value to use for the wf_lna_cal_en field.
 * @param[in] wflnacalclkedge - The value to use for the wf_lna_cal_clk_edge field.
 * @param[in] wflnapwrdeten - The value to use for the wf_lna_pwrdet_en field.
 * @param[in] wflnapwrdetlevel - The value to use for the wf_lna_pwrdet_level field.
 * @param[in] wfrmxregvbit - The value to use for the wf_rmx_reg_vbit field.
 * @param[in] wfrmxlobiasvbit - The value to use for the wf_rmx_lobias_vbit field.
 * @param[in] wftiaregvbit - The value to use for the wf_tia_reg_vbit field.
 */
__INLINE void wlan_rf_reg_04_pack(uint8_t wflnairefsel, uint8_t wflnavcmpdr, uint8_t wflnavcmpreg, uint8_t wflnavcmndr, uint8_t wflnavcmnreg, uint8_t wflnacalen, uint8_t wflnacalclkedge, uint8_t wflnapwrdeten, uint8_t wflnapwrdetlevel, uint8_t wfrmxregvbit, uint8_t wfrmxlobiasvbit, uint8_t wftiaregvbit)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR,  ((uint32_t)wflnairefsel << 30) | ((uint32_t)wflnavcmpdr << 29) | ((uint32_t)wflnavcmpreg << 24) | ((uint32_t)wflnavcmndr << 23) | ((uint32_t)wflnavcmnreg << 18) | ((uint32_t)wflnacalen << 17) | ((uint32_t)wflnacalclkedge << 16) | ((uint32_t)wflnapwrdeten << 13) | ((uint32_t)wflnapwrdetlevel << 11) | ((uint32_t)wfrmxregvbit << 8) | ((uint32_t)wfrmxlobiasvbit << 5) | ((uint32_t)wftiaregvbit << 0));
}

/**
 * @brief Unpacks REG_04's fields from current value of the REG_04 register.
 *
 * Reads the REG_04 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wflnairefsel - Will be populated with the current value of this field from the register.
 * @param[out] wflnavcmpdr - Will be populated with the current value of this field from the register.
 * @param[out] wflnavcmpreg - Will be populated with the current value of this field from the register.
 * @param[out] wflnavcmndr - Will be populated with the current value of this field from the register.
 * @param[out] wflnavcmnreg - Will be populated with the current value of this field from the register.
 * @param[out] wflnacalen - Will be populated with the current value of this field from the register.
 * @param[out] wflnacalclkedge - Will be populated with the current value of this field from the register.
 * @param[out] wflnacompvop - Will be populated with the current value of this field from the register.
 * @param[out] wflnacompvon - Will be populated with the current value of this field from the register.
 * @param[out] wflnapwrdeten - Will be populated with the current value of this field from the register.
 * @param[out] wflnapwrdetlevel - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxlobiasvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrmxcloadbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaregvbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_04_unpack(uint8_t* wflnairefsel, uint8_t* wflnavcmpdr, uint8_t* wflnavcmpreg, uint8_t* wflnavcmndr, uint8_t* wflnavcmnreg, uint8_t* wflnacalen, uint8_t* wflnacalclkedge, uint8_t* wflnacompvop, uint8_t* wflnacompvon, uint8_t* wflnapwrdeten, uint8_t* wflnapwrdetlevel, uint8_t* wfrmxregvbit, uint8_t* wfrmxlobiasvbit, uint8_t* wfrmxcloadbit, uint8_t* wftiaregvbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);

    *wflnairefsel = (localVal & ((uint32_t)0x40000000)) >> 30;
    *wflnavcmpdr = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wflnavcmpreg = (localVal & ((uint32_t)0x1F000000)) >> 24;
    *wflnavcmndr = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wflnavcmnreg = (localVal & ((uint32_t)0x007C0000)) >> 18;
    *wflnacalen = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wflnacalclkedge = (localVal & ((uint32_t)0x00010000)) >> 16;
    *wflnacompvop = (localVal & ((uint32_t)0x00008000)) >> 15;
    *wflnacompvon = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wflnapwrdeten = (localVal & ((uint32_t)0x00002000)) >> 13;
    *wflnapwrdetlevel = (localVal & ((uint32_t)0x00001800)) >> 11;
    *wfrmxregvbit = (localVal & ((uint32_t)0x00000700)) >> 8;
    *wfrmxlobiasvbit = (localVal & ((uint32_t)0x000000E0)) >> 5;
    *wfrmxcloadbit = (localVal & ((uint32_t)0x0000001C)) >> 2;
    *wftiaregvbit = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_lna_iref_sel field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_iref_sel field's value will be returned.
 *
 * @return The current value of the wf_lna_iref_sel field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_iref_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the wf_lna_iref_sel field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnairefsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_iref_sel_setf(uint8_t wflnairefsel)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)wflnairefsel << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the wf_lna_vcm_p_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_vcm_p_dr field's value will be returned.
 *
 * @return The current value of the wf_lna_vcm_p_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_vcm_p_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the wf_lna_vcm_p_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnavcmpdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_vcm_p_dr_setf(uint8_t wflnavcmpdr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wflnavcmpdr << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the wf_lna_vcm_p_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_vcm_p_reg field's value will be returned.
 *
 * @return The current value of the wf_lna_vcm_p_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_vcm_p_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x1F000000)) >> 24);
}

/**
 * @brief Sets the wf_lna_vcm_p_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnavcmpreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_vcm_p_reg_setf(uint8_t wflnavcmpreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x1F000000)) | (((uint32_t)wflnavcmpreg << 24) & ((uint32_t)0x1F000000)));
}

/**
 * @brief Returns the current value of the wf_lna_vcm_n_dr field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_vcm_n_dr field's value will be returned.
 *
 * @return The current value of the wf_lna_vcm_n_dr field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_vcm_n_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_lna_vcm_n_dr field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnavcmndr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_vcm_n_dr_setf(uint8_t wflnavcmndr)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wflnavcmndr << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_lna_vcm_n_reg field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_vcm_n_reg field's value will be returned.
 *
 * @return The current value of the wf_lna_vcm_n_reg field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_vcm_n_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x007C0000)) >> 18);
}

/**
 * @brief Sets the wf_lna_vcm_n_reg field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnavcmnreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_vcm_n_reg_setf(uint8_t wflnavcmnreg)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x007C0000)) | (((uint32_t)wflnavcmnreg << 18) & ((uint32_t)0x007C0000)));
}

/**
 * @brief Returns the current value of the wf_lna_cal_en field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_cal_en field's value will be returned.
 *
 * @return The current value of the wf_lna_cal_en field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Sets the wf_lna_cal_en field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnacalen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_cal_en_setf(uint8_t wflnacalen)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00020000)) | (((uint32_t)wflnacalen << 17) & ((uint32_t)0x00020000)));
}

/**
 * @brief Returns the current value of the wf_lna_cal_clk_edge field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_cal_clk_edge field's value will be returned.
 *
 * @return The current value of the wf_lna_cal_clk_edge field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_cal_clk_edge_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the wf_lna_cal_clk_edge field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnacalclkedge - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_cal_clk_edge_setf(uint8_t wflnacalclkedge)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)wflnacalclkedge << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the wf_lna_comp_vop field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_comp_vop field's value will be returned.
 *
 * @return The current value of the wf_lna_comp_vop field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_comp_vop_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Returns the current value of the wf_lna_comp_von field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_comp_von field's value will be returned.
 *
 * @return The current value of the wf_lna_comp_von field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_comp_von_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Returns the current value of the wf_lna_pwrdet_en field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_pwrdet_en field's value will be returned.
 *
 * @return The current value of the wf_lna_pwrdet_en field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_pwrdet_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the wf_lna_pwrdet_en field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnapwrdeten - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_pwrdet_en_setf(uint8_t wflnapwrdeten)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)wflnapwrdeten << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the wf_lna_pwrdet_level field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_lna_pwrdet_level field's value will be returned.
 *
 * @return The current value of the wf_lna_pwrdet_level field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_lna_pwrdet_level_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00001800)) >> 11);
}

/**
 * @brief Sets the wf_lna_pwrdet_level field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflnapwrdetlevel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lna_pwrdet_level_setf(uint8_t wflnapwrdetlevel)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00001800)) | (((uint32_t)wflnapwrdetlevel << 11) & ((uint32_t)0x00001800)));
}

/**
 * @brief Returns the current value of the wf_rmx_reg_vbit field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_rmx_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_rmx_reg_vbit field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

/**
 * @brief Sets the wf_rmx_reg_vbit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_reg_vbit_setf(uint8_t wfrmxregvbit)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000700)) | (((uint32_t)wfrmxregvbit << 8) & ((uint32_t)0x00000700)));
}

/**
 * @brief Returns the current value of the wf_rmx_lobias_vbit field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_rmx_lobias_vbit field's value will be returned.
 *
 * @return The current value of the wf_rmx_lobias_vbit field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_lobias_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x000000E0)) >> 5);
}

/**
 * @brief Sets the wf_rmx_lobias_vbit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrmxlobiasvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rmx_lobias_vbit_setf(uint8_t wfrmxlobiasvbit)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x000000E0)) | (((uint32_t)wfrmxlobiasvbit << 5) & ((uint32_t)0x000000E0)));
}

/**
 * @brief Returns the current value of the wf_rmx_cload_bit field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_rmx_cload_bit field's value will be returned.
 *
 * @return The current value of the wf_rmx_cload_bit field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_rmx_cload_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x0000001C)) >> 2);
}

/**
 * @brief Returns the current value of the wf_tia_reg_vbit field in the REG_04 register.
 *
 * The REG_04 register will be read and the wf_tia_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_tia_reg_vbit field in the REG_04 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_04_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the wf_tia_reg_vbit field of the REG_04 register.
 *
 * The REG_04 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_reg_vbit_setf(uint8_t wftiaregvbit)
{
    REG_PL_WR(WLAN_RF_REG_04_ADDR, (REG_PL_RD(WLAN_RF_REG_04_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)wftiaregvbit << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_05 register definitions
 * <table>
 * <caption id="REG_05_BF">REG_05 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:30 <td>  wf_tia_input_sel <td>R <td>R/W <td>0x0
 * <tr><td>29:25 <td>   wf_tia_bw_c_bit <td>W <td>R <td>0x14
 * <tr><td>24:22 <td>   wf_tia_bw_r_bit <td>W <td>R <td>0x4
 * <tr><td>21 <td> wf_tia_op_lb_mode <td>W <td>R <td>0
 * <tr><td>20 <td> wf_tia_op_hp_mode <td>W <td>R <td>0
 * <tr><td>19:17 <td>   wf_tia_vcm_vbit <td>R <td>R/W <td>0x4
 * <tr><td>16:12 <td>    wf_tia_op_ibit <td>W <td>R <td>0x19
 * <tr><td>11:09 <td>wf_tia_op_mil_cbit <td>R <td>R/W <td>0x3
 * <tr><td>08:06 <td>wf_tia_op_mil_rbit <td>R <td>R/W <td>0x3
 * <tr><td>05:03 <td>wf_tia_dccal_rdac_range <td>R <td>R/W <td>0x2
 * <tr><td>02:00 <td>   wf_tia_gain_bit <td>W <td>R <td>0x7
 * </table>
 *
 * @{
 */

/// Address of the REG_05 register
#define WLAN_RF_REG_05_ADDR   0x40344014
/// Offset of the REG_05 register from the base address
#define WLAN_RF_REG_05_OFFSET 0x00000014
/// Index of the REG_05 register
#define WLAN_RF_REG_05_INDEX  0x00000005
/// Reset value of the REG_05 register
#define WLAN_RF_REG_05_RESET  0x290996D7

/**
 * @brief Returns the current value of the REG_05 register.
 * The REG_05 register will be read and its value returned.
 * @return The current value of the REG_05 register.
 */
__INLINE uint32_t wlan_rf_reg_05_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_05_ADDR);
}

/**
 * @brief Sets the REG_05 register to a value.
 * The REG_05 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_05_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_05_ADDR, value);
}

// field definitions
/// WF_TIA_INPUT_SEL field mask
#define WLAN_RF_WF_TIA_INPUT_SEL_MASK          ((uint32_t)0xC0000000)
/// WF_TIA_INPUT_SEL field LSB position
#define WLAN_RF_WF_TIA_INPUT_SEL_LSB           30
/// WF_TIA_INPUT_SEL field width
#define WLAN_RF_WF_TIA_INPUT_SEL_WIDTH         ((uint32_t)0x00000002)
/// WF_TIA_BW_C_BIT field mask
#define WLAN_RF_WF_TIA_BW_C_BIT_MASK           ((uint32_t)0x3E000000)
/// WF_TIA_BW_C_BIT field LSB position
#define WLAN_RF_WF_TIA_BW_C_BIT_LSB            25
/// WF_TIA_BW_C_BIT field width
#define WLAN_RF_WF_TIA_BW_C_BIT_WIDTH          ((uint32_t)0x00000005)
/// WF_TIA_BW_R_BIT field mask
#define WLAN_RF_WF_TIA_BW_R_BIT_MASK           ((uint32_t)0x01C00000)
/// WF_TIA_BW_R_BIT field LSB position
#define WLAN_RF_WF_TIA_BW_R_BIT_LSB            22
/// WF_TIA_BW_R_BIT field width
#define WLAN_RF_WF_TIA_BW_R_BIT_WIDTH          ((uint32_t)0x00000003)
/// WF_TIA_OP_LB_MODE field bit
#define WLAN_RF_WF_TIA_OP_LB_MODE_BIT          ((uint32_t)0x00200000)
/// WF_TIA_OP_LB_MODE field position
#define WLAN_RF_WF_TIA_OP_LB_MODE_POS          21
/// WF_TIA_OP_HP_MODE field bit
#define WLAN_RF_WF_TIA_OP_HP_MODE_BIT          ((uint32_t)0x00100000)
/// WF_TIA_OP_HP_MODE field position
#define WLAN_RF_WF_TIA_OP_HP_MODE_POS          20
/// WF_TIA_VCM_VBIT field mask
#define WLAN_RF_WF_TIA_VCM_VBIT_MASK           ((uint32_t)0x000E0000)
/// WF_TIA_VCM_VBIT field LSB position
#define WLAN_RF_WF_TIA_VCM_VBIT_LSB            17
/// WF_TIA_VCM_VBIT field width
#define WLAN_RF_WF_TIA_VCM_VBIT_WIDTH          ((uint32_t)0x00000003)
/// WF_TIA_OP_IBIT field mask
#define WLAN_RF_WF_TIA_OP_IBIT_MASK            ((uint32_t)0x0001F000)
/// WF_TIA_OP_IBIT field LSB position
#define WLAN_RF_WF_TIA_OP_IBIT_LSB             12
/// WF_TIA_OP_IBIT field width
#define WLAN_RF_WF_TIA_OP_IBIT_WIDTH           ((uint32_t)0x00000005)
/// WF_TIA_OP_MIL_CBIT field mask
#define WLAN_RF_WF_TIA_OP_MIL_CBIT_MASK        ((uint32_t)0x00000E00)
/// WF_TIA_OP_MIL_CBIT field LSB position
#define WLAN_RF_WF_TIA_OP_MIL_CBIT_LSB         9
/// WF_TIA_OP_MIL_CBIT field width
#define WLAN_RF_WF_TIA_OP_MIL_CBIT_WIDTH       ((uint32_t)0x00000003)
/// WF_TIA_OP_MIL_RBIT field mask
#define WLAN_RF_WF_TIA_OP_MIL_RBIT_MASK        ((uint32_t)0x000001C0)
/// WF_TIA_OP_MIL_RBIT field LSB position
#define WLAN_RF_WF_TIA_OP_MIL_RBIT_LSB         6
/// WF_TIA_OP_MIL_RBIT field width
#define WLAN_RF_WF_TIA_OP_MIL_RBIT_WIDTH       ((uint32_t)0x00000003)
/// WF_TIA_DCCAL_RDAC_RANGE field mask
#define WLAN_RF_WF_TIA_DCCAL_RDAC_RANGE_MASK   ((uint32_t)0x00000038)
/// WF_TIA_DCCAL_RDAC_RANGE field LSB position
#define WLAN_RF_WF_TIA_DCCAL_RDAC_RANGE_LSB    3
/// WF_TIA_DCCAL_RDAC_RANGE field width
#define WLAN_RF_WF_TIA_DCCAL_RDAC_RANGE_WIDTH  ((uint32_t)0x00000003)
/// WF_TIA_GAIN_BIT field mask
#define WLAN_RF_WF_TIA_GAIN_BIT_MASK           ((uint32_t)0x00000007)
/// WF_TIA_GAIN_BIT field LSB position
#define WLAN_RF_WF_TIA_GAIN_BIT_LSB            0
/// WF_TIA_GAIN_BIT field width
#define WLAN_RF_WF_TIA_GAIN_BIT_WIDTH          ((uint32_t)0x00000003)

/// WF_TIA_INPUT_SEL field reset value
#define WLAN_RF_WF_TIA_INPUT_SEL_RST           0x0
/// WF_TIA_BW_C_BIT field reset value
#define WLAN_RF_WF_TIA_BW_C_BIT_RST            0x14
/// WF_TIA_BW_R_BIT field reset value
#define WLAN_RF_WF_TIA_BW_R_BIT_RST            0x4
/// WF_TIA_OP_LB_MODE field reset value
#define WLAN_RF_WF_TIA_OP_LB_MODE_RST          0x0
/// WF_TIA_OP_HP_MODE field reset value
#define WLAN_RF_WF_TIA_OP_HP_MODE_RST          0x0
/// WF_TIA_VCM_VBIT field reset value
#define WLAN_RF_WF_TIA_VCM_VBIT_RST            0x4
/// WF_TIA_OP_IBIT field reset value
#define WLAN_RF_WF_TIA_OP_IBIT_RST             0x19
/// WF_TIA_OP_MIL_CBIT field reset value
#define WLAN_RF_WF_TIA_OP_MIL_CBIT_RST         0x3
/// WF_TIA_OP_MIL_RBIT field reset value
#define WLAN_RF_WF_TIA_OP_MIL_RBIT_RST         0x3
/// WF_TIA_DCCAL_RDAC_RANGE field reset value
#define WLAN_RF_WF_TIA_DCCAL_RDAC_RANGE_RST    0x2
/// WF_TIA_GAIN_BIT field reset value
#define WLAN_RF_WF_TIA_GAIN_BIT_RST            0x7

/**
 * @brief Constructs a value for the REG_05 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wftiainputsel - The value to use for the wf_tia_input_sel field.
 * @param[in] wftiavcmvbit - The value to use for the wf_tia_vcm_vbit field.
 * @param[in] wftiaopmilcbit - The value to use for the wf_tia_op_mil_cbit field.
 * @param[in] wftiaopmilrbit - The value to use for the wf_tia_op_mil_rbit field.
 * @param[in] wftiadccalrdacrange - The value to use for the wf_tia_dccal_rdac_range field.
 */
__INLINE void wlan_rf_reg_05_pack(uint8_t wftiainputsel, uint8_t wftiavcmvbit, uint8_t wftiaopmilcbit, uint8_t wftiaopmilrbit, uint8_t wftiadccalrdacrange)
{
    REG_PL_WR(WLAN_RF_REG_05_ADDR,  ((uint32_t)wftiainputsel << 30) | ((uint32_t)wftiavcmvbit << 17) | ((uint32_t)wftiaopmilcbit << 9) | ((uint32_t)wftiaopmilrbit << 6) | ((uint32_t)wftiadccalrdacrange << 3));
}

/**
 * @brief Unpacks REG_05's fields from current value of the REG_05 register.
 *
 * Reads the REG_05 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wftiainputsel - Will be populated with the current value of this field from the register.
 * @param[out] wftiabwcbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiabwrbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaoplbmode - Will be populated with the current value of this field from the register.
 * @param[out] wftiaophpmode - Will be populated with the current value of this field from the register.
 * @param[out] wftiavcmvbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaopibit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaopmilcbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiaopmilrbit - Will be populated with the current value of this field from the register.
 * @param[out] wftiadccalrdacrange - Will be populated with the current value of this field from the register.
 * @param[out] wftiagainbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_05_unpack(uint8_t* wftiainputsel, uint8_t* wftiabwcbit, uint8_t* wftiabwrbit, uint8_t* wftiaoplbmode, uint8_t* wftiaophpmode, uint8_t* wftiavcmvbit, uint8_t* wftiaopibit, uint8_t* wftiaopmilcbit, uint8_t* wftiaopmilrbit, uint8_t* wftiadccalrdacrange, uint8_t* wftiagainbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);

    *wftiainputsel = (localVal & ((uint32_t)0xC0000000)) >> 30;
    *wftiabwcbit = (localVal & ((uint32_t)0x3E000000)) >> 25;
    *wftiabwrbit = (localVal & ((uint32_t)0x01C00000)) >> 22;
    *wftiaoplbmode = (localVal & ((uint32_t)0x00200000)) >> 21;
    *wftiaophpmode = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wftiavcmvbit = (localVal & ((uint32_t)0x000E0000)) >> 17;
    *wftiaopibit = (localVal & ((uint32_t)0x0001F000)) >> 12;
    *wftiaopmilcbit = (localVal & ((uint32_t)0x00000E00)) >> 9;
    *wftiaopmilrbit = (localVal & ((uint32_t)0x000001C0)) >> 6;
    *wftiadccalrdacrange = (localVal & ((uint32_t)0x00000038)) >> 3;
    *wftiagainbit = (localVal & ((uint32_t)0x00000007)) >> 0;
}

/**
 * @brief Returns the current value of the wf_tia_input_sel field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_input_sel field's value will be returned.
 *
 * @return The current value of the wf_tia_input_sel field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_input_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0xC0000000)) >> 30);
}

/**
 * @brief Sets the wf_tia_input_sel field of the REG_05 register.
 *
 * The REG_05 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiainputsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_input_sel_setf(uint8_t wftiainputsel)
{
    REG_PL_WR(WLAN_RF_REG_05_ADDR, (REG_PL_RD(WLAN_RF_REG_05_ADDR) & ~((uint32_t)0xC0000000)) | (((uint32_t)wftiainputsel << 30) & ((uint32_t)0xC0000000)));
}

/**
 * @brief Returns the current value of the wf_tia_bw_c_bit field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_bw_c_bit field's value will be returned.
 *
 * @return The current value of the wf_tia_bw_c_bit field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_bw_c_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x3E000000)) >> 25);
}

/**
 * @brief Returns the current value of the wf_tia_bw_r_bit field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_bw_r_bit field's value will be returned.
 *
 * @return The current value of the wf_tia_bw_r_bit field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_bw_r_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x01C00000)) >> 22);
}

/**
 * @brief Returns the current value of the wf_tia_op_lb_mode field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_op_lb_mode field's value will be returned.
 *
 * @return The current value of the wf_tia_op_lb_mode field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_op_lb_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

/**
 * @brief Returns the current value of the wf_tia_op_hp_mode field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_op_hp_mode field's value will be returned.
 *
 * @return The current value of the wf_tia_op_hp_mode field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_op_hp_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Returns the current value of the wf_tia_vcm_vbit field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_vcm_vbit field's value will be returned.
 *
 * @return The current value of the wf_tia_vcm_vbit field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_vcm_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x000E0000)) >> 17);
}

/**
 * @brief Sets the wf_tia_vcm_vbit field of the REG_05 register.
 *
 * The REG_05 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiavcmvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_vcm_vbit_setf(uint8_t wftiavcmvbit)
{
    REG_PL_WR(WLAN_RF_REG_05_ADDR, (REG_PL_RD(WLAN_RF_REG_05_ADDR) & ~((uint32_t)0x000E0000)) | (((uint32_t)wftiavcmvbit << 17) & ((uint32_t)0x000E0000)));
}

/**
 * @brief Returns the current value of the wf_tia_op_ibit field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_op_ibit field's value will be returned.
 *
 * @return The current value of the wf_tia_op_ibit field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_op_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x0001F000)) >> 12);
}

/**
 * @brief Returns the current value of the wf_tia_op_mil_cbit field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_op_mil_cbit field's value will be returned.
 *
 * @return The current value of the wf_tia_op_mil_cbit field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_op_mil_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x00000E00)) >> 9);
}

/**
 * @brief Sets the wf_tia_op_mil_cbit field of the REG_05 register.
 *
 * The REG_05 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaopmilcbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_op_mil_cbit_setf(uint8_t wftiaopmilcbit)
{
    REG_PL_WR(WLAN_RF_REG_05_ADDR, (REG_PL_RD(WLAN_RF_REG_05_ADDR) & ~((uint32_t)0x00000E00)) | (((uint32_t)wftiaopmilcbit << 9) & ((uint32_t)0x00000E00)));
}

/**
 * @brief Returns the current value of the wf_tia_op_mil_rbit field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_op_mil_rbit field's value will be returned.
 *
 * @return The current value of the wf_tia_op_mil_rbit field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_op_mil_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x000001C0)) >> 6);
}

/**
 * @brief Sets the wf_tia_op_mil_rbit field of the REG_05 register.
 *
 * The REG_05 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaopmilrbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_op_mil_rbit_setf(uint8_t wftiaopmilrbit)
{
    REG_PL_WR(WLAN_RF_REG_05_ADDR, (REG_PL_RD(WLAN_RF_REG_05_ADDR) & ~((uint32_t)0x000001C0)) | (((uint32_t)wftiaopmilrbit << 6) & ((uint32_t)0x000001C0)));
}

/**
 * @brief Returns the current value of the wf_tia_dccal_rdac_range field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_dccal_rdac_range field's value will be returned.
 *
 * @return The current value of the wf_tia_dccal_rdac_range field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_dccal_rdac_range_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x00000038)) >> 3);
}

/**
 * @brief Sets the wf_tia_dccal_rdac_range field of the REG_05 register.
 *
 * The REG_05 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiadccalrdacrange - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_dccal_rdac_range_setf(uint8_t wftiadccalrdacrange)
{
    REG_PL_WR(WLAN_RF_REG_05_ADDR, (REG_PL_RD(WLAN_RF_REG_05_ADDR) & ~((uint32_t)0x00000038)) | (((uint32_t)wftiadccalrdacrange << 3) & ((uint32_t)0x00000038)));
}

/**
 * @brief Returns the current value of the wf_tia_gain_bit field in the REG_05 register.
 *
 * The REG_05 register will be read and the wf_tia_gain_bit field's value will be returned.
 *
 * @return The current value of the wf_tia_gain_bit field in the REG_05 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_gain_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_05_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/// @}

/**
 * @name REG_06 register definitions
 * <table>
 * <caption id="REG_06_BF">REG_06 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29 <td>wf_tia_i_calbit_dr <td>R <td>R/W <td>0
 * <tr><td>28:21 <td>wf_tia_i_calbit_reg <td>R <td>R/W <td>0x80
 * <tr><td>20 <td>wf_tia_q_calbit_dr <td>R <td>R/W <td>0
 * <tr><td>19:12 <td>wf_tia_q_calbit_reg <td>R <td>R/W <td>0x80
 * <tr><td>11 <td>          wf_pa_ms <td>R <td>R/W <td>0
 * <tr><td>10:05 <td>        wf_pa_gbit <td>W <td>R <td>0x3F
 * <tr><td>04:03 <td>    wf_pa_vbg_vbit <td>R <td>R/W <td>0x3
 * <tr><td>02:01 <td>  wf_pa_vbg_tc_bit <td>R <td>R/W <td>0x1
 * <tr><td>00 <td> wf_pa_iref_sel_bg <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_06 register
#define WLAN_RF_REG_06_ADDR   0x40344018
/// Offset of the REG_06 register from the base address
#define WLAN_RF_REG_06_OFFSET 0x00000018
/// Index of the REG_06 register
#define WLAN_RF_REG_06_INDEX  0x00000006
/// Reset value of the REG_06 register
#define WLAN_RF_REG_06_RESET  0x100807FB

/**
 * @brief Returns the current value of the REG_06 register.
 * The REG_06 register will be read and its value returned.
 * @return The current value of the REG_06 register.
 */
__INLINE uint32_t wlan_rf_reg_06_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_06_ADDR);
}

/**
 * @brief Sets the REG_06 register to a value.
 * The REG_06 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_06_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR, value);
}

// field definitions
/// WF_TIA_I_CALBIT_DR field bit
#define WLAN_RF_WF_TIA_I_CALBIT_DR_BIT     ((uint32_t)0x20000000)
/// WF_TIA_I_CALBIT_DR field position
#define WLAN_RF_WF_TIA_I_CALBIT_DR_POS     29
/// WF_TIA_I_CALBIT_REG field mask
#define WLAN_RF_WF_TIA_I_CALBIT_REG_MASK   ((uint32_t)0x1FE00000)
/// WF_TIA_I_CALBIT_REG field LSB position
#define WLAN_RF_WF_TIA_I_CALBIT_REG_LSB    21
/// WF_TIA_I_CALBIT_REG field width
#define WLAN_RF_WF_TIA_I_CALBIT_REG_WIDTH  ((uint32_t)0x00000008)
/// WF_TIA_Q_CALBIT_DR field bit
#define WLAN_RF_WF_TIA_Q_CALBIT_DR_BIT     ((uint32_t)0x00100000)
/// WF_TIA_Q_CALBIT_DR field position
#define WLAN_RF_WF_TIA_Q_CALBIT_DR_POS     20
/// WF_TIA_Q_CALBIT_REG field mask
#define WLAN_RF_WF_TIA_Q_CALBIT_REG_MASK   ((uint32_t)0x000FF000)
/// WF_TIA_Q_CALBIT_REG field LSB position
#define WLAN_RF_WF_TIA_Q_CALBIT_REG_LSB    12
/// WF_TIA_Q_CALBIT_REG field width
#define WLAN_RF_WF_TIA_Q_CALBIT_REG_WIDTH  ((uint32_t)0x00000008)
/// WF_PA_MS field bit
#define WLAN_RF_WF_PA_MS_BIT               ((uint32_t)0x00000800)
/// WF_PA_MS field position
#define WLAN_RF_WF_PA_MS_POS               11
/// WF_PA_GBIT field mask
#define WLAN_RF_WF_PA_GBIT_MASK            ((uint32_t)0x000007E0)
/// WF_PA_GBIT field LSB position
#define WLAN_RF_WF_PA_GBIT_LSB             5
/// WF_PA_GBIT field width
#define WLAN_RF_WF_PA_GBIT_WIDTH           ((uint32_t)0x00000006)
/// WF_PA_VBG_VBIT field mask
#define WLAN_RF_WF_PA_VBG_VBIT_MASK        ((uint32_t)0x00000018)
/// WF_PA_VBG_VBIT field LSB position
#define WLAN_RF_WF_PA_VBG_VBIT_LSB         3
/// WF_PA_VBG_VBIT field width
#define WLAN_RF_WF_PA_VBG_VBIT_WIDTH       ((uint32_t)0x00000002)
/// WF_PA_VBG_TC_BIT field mask
#define WLAN_RF_WF_PA_VBG_TC_BIT_MASK      ((uint32_t)0x00000006)
/// WF_PA_VBG_TC_BIT field LSB position
#define WLAN_RF_WF_PA_VBG_TC_BIT_LSB       1
/// WF_PA_VBG_TC_BIT field width
#define WLAN_RF_WF_PA_VBG_TC_BIT_WIDTH     ((uint32_t)0x00000002)
/// WF_PA_IREF_SEL_BG field bit
#define WLAN_RF_WF_PA_IREF_SEL_BG_BIT      ((uint32_t)0x00000001)
/// WF_PA_IREF_SEL_BG field position
#define WLAN_RF_WF_PA_IREF_SEL_BG_POS      0

/// WF_TIA_I_CALBIT_DR field reset value
#define WLAN_RF_WF_TIA_I_CALBIT_DR_RST     0x0
/// WF_TIA_I_CALBIT_REG field reset value
#define WLAN_RF_WF_TIA_I_CALBIT_REG_RST    0x80
/// WF_TIA_Q_CALBIT_DR field reset value
#define WLAN_RF_WF_TIA_Q_CALBIT_DR_RST     0x0
/// WF_TIA_Q_CALBIT_REG field reset value
#define WLAN_RF_WF_TIA_Q_CALBIT_REG_RST    0x80
/// WF_PA_MS field reset value
#define WLAN_RF_WF_PA_MS_RST               0x0
/// WF_PA_GBIT field reset value
#define WLAN_RF_WF_PA_GBIT_RST             0x3F
/// WF_PA_VBG_VBIT field reset value
#define WLAN_RF_WF_PA_VBG_VBIT_RST         0x3
/// WF_PA_VBG_TC_BIT field reset value
#define WLAN_RF_WF_PA_VBG_TC_BIT_RST       0x1
/// WF_PA_IREF_SEL_BG field reset value
#define WLAN_RF_WF_PA_IREF_SEL_BG_RST      0x1

/**
 * @brief Constructs a value for the REG_06 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wftiaicalbitdr - The value to use for the wf_tia_i_calbit_dr field.
 * @param[in] wftiaicalbitreg - The value to use for the wf_tia_i_calbit_reg field.
 * @param[in] wftiaqcalbitdr - The value to use for the wf_tia_q_calbit_dr field.
 * @param[in] wftiaqcalbitreg - The value to use for the wf_tia_q_calbit_reg field.
 * @param[in] wfpams - The value to use for the wf_pa_ms field.
 * @param[in] wfpavbgvbit - The value to use for the wf_pa_vbg_vbit field.
 * @param[in] wfpavbgtcbit - The value to use for the wf_pa_vbg_tc_bit field.
 * @param[in] wfpairefselbg - The value to use for the wf_pa_iref_sel_bg field.
 */
__INLINE void wlan_rf_reg_06_pack(uint8_t wftiaicalbitdr, uint8_t wftiaicalbitreg, uint8_t wftiaqcalbitdr, uint8_t wftiaqcalbitreg, uint8_t wfpams, uint8_t wfpavbgvbit, uint8_t wfpavbgtcbit, uint8_t wfpairefselbg)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR,  ((uint32_t)wftiaicalbitdr << 29) | ((uint32_t)wftiaicalbitreg << 21) | ((uint32_t)wftiaqcalbitdr << 20) | ((uint32_t)wftiaqcalbitreg << 12) | ((uint32_t)wfpams << 11) | ((uint32_t)wfpavbgvbit << 3) | ((uint32_t)wfpavbgtcbit << 1) | ((uint32_t)wfpairefselbg << 0));
}

/**
 * @brief Unpacks REG_06's fields from current value of the REG_06 register.
 *
 * Reads the REG_06 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wftiaicalbitdr - Will be populated with the current value of this field from the register.
 * @param[out] wftiaicalbitreg - Will be populated with the current value of this field from the register.
 * @param[out] wftiaqcalbitdr - Will be populated with the current value of this field from the register.
 * @param[out] wftiaqcalbitreg - Will be populated with the current value of this field from the register.
 * @param[out] wfpams - Will be populated with the current value of this field from the register.
 * @param[out] wfpagbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavbgvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavbgtcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpairefselbg - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_06_unpack(uint8_t* wftiaicalbitdr, uint8_t* wftiaicalbitreg, uint8_t* wftiaqcalbitdr, uint8_t* wftiaqcalbitreg, uint8_t* wfpams, uint8_t* wfpagbit, uint8_t* wfpavbgvbit, uint8_t* wfpavbgtcbit, uint8_t* wfpairefselbg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);

    *wftiaicalbitdr = (localVal & ((uint32_t)0x20000000)) >> 29;
    *wftiaicalbitreg = (localVal & ((uint32_t)0x1FE00000)) >> 21;
    *wftiaqcalbitdr = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wftiaqcalbitreg = (localVal & ((uint32_t)0x000FF000)) >> 12;
    *wfpams = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wfpagbit = (localVal & ((uint32_t)0x000007E0)) >> 5;
    *wfpavbgvbit = (localVal & ((uint32_t)0x00000018)) >> 3;
    *wfpavbgtcbit = (localVal & ((uint32_t)0x00000006)) >> 1;
    *wfpairefselbg = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_tia_i_calbit_dr field in the REG_06 register.
 *
 * The REG_06 register will be read and the wf_tia_i_calbit_dr field's value will be returned.
 *
 * @return The current value of the wf_tia_i_calbit_dr field in the REG_06 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_i_calbit_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the wf_tia_i_calbit_dr field of the REG_06 register.
 *
 * The REG_06 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaicalbitdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_i_calbit_dr_setf(uint8_t wftiaicalbitdr)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR, (REG_PL_RD(WLAN_RF_REG_06_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)wftiaicalbitdr << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the wf_tia_i_calbit_reg field in the REG_06 register.
 *
 * The REG_06 register will be read and the wf_tia_i_calbit_reg field's value will be returned.
 *
 * @return The current value of the wf_tia_i_calbit_reg field in the REG_06 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_i_calbit_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);
    return ((localVal & ((uint32_t)0x1FE00000)) >> 21);
}

/**
 * @brief Sets the wf_tia_i_calbit_reg field of the REG_06 register.
 *
 * The REG_06 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaicalbitreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_i_calbit_reg_setf(uint8_t wftiaicalbitreg)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR, (REG_PL_RD(WLAN_RF_REG_06_ADDR) & ~((uint32_t)0x1FE00000)) | (((uint32_t)wftiaicalbitreg << 21) & ((uint32_t)0x1FE00000)));
}

/**
 * @brief Returns the current value of the wf_tia_q_calbit_dr field in the REG_06 register.
 *
 * The REG_06 register will be read and the wf_tia_q_calbit_dr field's value will be returned.
 *
 * @return The current value of the wf_tia_q_calbit_dr field in the REG_06 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_q_calbit_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_tia_q_calbit_dr field of the REG_06 register.
 *
 * The REG_06 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaqcalbitdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_q_calbit_dr_setf(uint8_t wftiaqcalbitdr)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR, (REG_PL_RD(WLAN_RF_REG_06_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wftiaqcalbitdr << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the wf_tia_q_calbit_reg field in the REG_06 register.
 *
 * The REG_06 register will be read and the wf_tia_q_calbit_reg field's value will be returned.
 *
 * @return The current value of the wf_tia_q_calbit_reg field in the REG_06 register.
 */
__INLINE uint8_t wlan_rf_wf_tia_q_calbit_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);
    return ((localVal & ((uint32_t)0x000FF000)) >> 12);
}

/**
 * @brief Sets the wf_tia_q_calbit_reg field of the REG_06 register.
 *
 * The REG_06 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiaqcalbitreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_q_calbit_reg_setf(uint8_t wftiaqcalbitreg)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR, (REG_PL_RD(WLAN_RF_REG_06_ADDR) & ~((uint32_t)0x000FF000)) | (((uint32_t)wftiaqcalbitreg << 12) & ((uint32_t)0x000FF000)));
}

/**
 * @brief Returns the current value of the wf_pa_ms field in the REG_06 register.
 *
 * The REG_06 register will be read and the wf_pa_ms field's value will be returned.
 *
 * @return The current value of the wf_pa_ms field in the REG_06 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_ms_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_pa_ms field of the REG_06 register.
 *
 * The REG_06 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpams - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_ms_setf(uint8_t wfpams)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR, (REG_PL_RD(WLAN_RF_REG_06_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wfpams << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_pa_gbit field in the REG_06 register.
 *
 * The REG_06 register will be read and the wf_pa_gbit field's value will be returned.
 *
 * @return The current value of the wf_pa_gbit field in the REG_06 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);
    return ((localVal & ((uint32_t)0x000007E0)) >> 5);
}

/**
 * @brief Returns the current value of the wf_pa_vbg_vbit field in the REG_06 register.
 *
 * The REG_06 register will be read and the wf_pa_vbg_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa_vbg_vbit field in the REG_06 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vbg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);
    return ((localVal & ((uint32_t)0x00000018)) >> 3);
}

/**
 * @brief Sets the wf_pa_vbg_vbit field of the REG_06 register.
 *
 * The REG_06 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavbgvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vbg_vbit_setf(uint8_t wfpavbgvbit)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR, (REG_PL_RD(WLAN_RF_REG_06_ADDR) & ~((uint32_t)0x00000018)) | (((uint32_t)wfpavbgvbit << 3) & ((uint32_t)0x00000018)));
}

/**
 * @brief Returns the current value of the wf_pa_vbg_tc_bit field in the REG_06 register.
 *
 * The REG_06 register will be read and the wf_pa_vbg_tc_bit field's value will be returned.
 *
 * @return The current value of the wf_pa_vbg_tc_bit field in the REG_06 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vbg_tc_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);
    return ((localVal & ((uint32_t)0x00000006)) >> 1);
}

/**
 * @brief Sets the wf_pa_vbg_tc_bit field of the REG_06 register.
 *
 * The REG_06 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavbgtcbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vbg_tc_bit_setf(uint8_t wfpavbgtcbit)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR, (REG_PL_RD(WLAN_RF_REG_06_ADDR) & ~((uint32_t)0x00000006)) | (((uint32_t)wfpavbgtcbit << 1) & ((uint32_t)0x00000006)));
}

/**
 * @brief Returns the current value of the wf_pa_iref_sel_bg field in the REG_06 register.
 *
 * The REG_06 register will be read and the wf_pa_iref_sel_bg field's value will be returned.
 *
 * @return The current value of the wf_pa_iref_sel_bg field in the REG_06 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_iref_sel_bg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_06_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_pa_iref_sel_bg field of the REG_06 register.
 *
 * The REG_06 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpairefselbg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_iref_sel_bg_setf(uint8_t wfpairefselbg)
{
    REG_PL_WR(WLAN_RF_REG_06_ADDR, (REG_PL_RD(WLAN_RF_REG_06_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfpairefselbg << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_07 register definitions
 * <table>
 * <caption id="REG_07_BF">REG_07 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30:28 <td>  wf_pa_input_cbit <td>W <td>R <td>0x0
 * <tr><td>27:25 <td>wf_pa_bias_vh_vbit <td>R <td>R/W <td>0x6
 * <tr><td>24 <td>   wf_pa_vm_dym_en <td>W <td>R <td>0
 * <tr><td>23:20 <td>    wf_pa_vm_vbit1 <td>W <td>R <td>0x8
 * <tr><td>19:16 <td>    wf_pa_vm_vbit2 <td>W <td>R <td>0x8
 * <tr><td>15:13 <td>     wf_pa_vm_vbit <td>W <td>R <td>0x4
 * <tr><td>12 <td>  wf_pa_vl_opam_en <td>R <td>R/W <td>1
 * <tr><td>11:09 <td>wf_pa_vl_ic_sel_bit <td>R <td>R/W <td>0x1
 * <tr><td>08:05 <td> wf_pa_vl_cgm_ibit <td>R <td>R/W <td>0x8
 * <tr><td>04:02 <td>     wf_pa_vl_vbit <td>W <td>R <td>0x4
 * <tr><td>01 <td>     wf_pa_loft_en <td>R <td>R/W <td>0
 * <tr><td>00 <td>wf_pa_loft_lowpass_en <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_07 register
#define WLAN_RF_REG_07_ADDR   0x4034401C
/// Offset of the REG_07 register from the base address
#define WLAN_RF_REG_07_OFFSET 0x0000001C
/// Index of the REG_07 register
#define WLAN_RF_REG_07_INDEX  0x00000007
/// Reset value of the REG_07 register
#define WLAN_RF_REG_07_RESET  0x0C889311

/**
 * @brief Returns the current value of the REG_07 register.
 * The REG_07 register will be read and its value returned.
 * @return The current value of the REG_07 register.
 */
__INLINE uint32_t wlan_rf_reg_07_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_07_ADDR);
}

/**
 * @brief Sets the REG_07 register to a value.
 * The REG_07 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_07_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_07_ADDR, value);
}

// field definitions
/// WF_PA_INPUT_CBIT field mask
#define WLAN_RF_WF_PA_INPUT_CBIT_MASK        ((uint32_t)0x70000000)
/// WF_PA_INPUT_CBIT field LSB position
#define WLAN_RF_WF_PA_INPUT_CBIT_LSB         28
/// WF_PA_INPUT_CBIT field width
#define WLAN_RF_WF_PA_INPUT_CBIT_WIDTH       ((uint32_t)0x00000003)
/// WF_PA_BIAS_VH_VBIT field mask
#define WLAN_RF_WF_PA_BIAS_VH_VBIT_MASK      ((uint32_t)0x0E000000)
/// WF_PA_BIAS_VH_VBIT field LSB position
#define WLAN_RF_WF_PA_BIAS_VH_VBIT_LSB       25
/// WF_PA_BIAS_VH_VBIT field width
#define WLAN_RF_WF_PA_BIAS_VH_VBIT_WIDTH     ((uint32_t)0x00000003)
/// WF_PA_VM_DYM_EN field bit
#define WLAN_RF_WF_PA_VM_DYM_EN_BIT          ((uint32_t)0x01000000)
/// WF_PA_VM_DYM_EN field position
#define WLAN_RF_WF_PA_VM_DYM_EN_POS          24
/// WF_PA_VM_VBIT_1 field mask
#define WLAN_RF_WF_PA_VM_VBIT_1_MASK         ((uint32_t)0x00F00000)
/// WF_PA_VM_VBIT_1 field LSB position
#define WLAN_RF_WF_PA_VM_VBIT_1_LSB          20
/// WF_PA_VM_VBIT_1 field width
#define WLAN_RF_WF_PA_VM_VBIT_1_WIDTH        ((uint32_t)0x00000004)
/// WF_PA_VM_VBIT_2 field mask
#define WLAN_RF_WF_PA_VM_VBIT_2_MASK         ((uint32_t)0x000F0000)
/// WF_PA_VM_VBIT_2 field LSB position
#define WLAN_RF_WF_PA_VM_VBIT_2_LSB          16
/// WF_PA_VM_VBIT_2 field width
#define WLAN_RF_WF_PA_VM_VBIT_2_WIDTH        ((uint32_t)0x00000004)
/// WF_PA_VM_VBIT field mask
#define WLAN_RF_WF_PA_VM_VBIT_MASK           ((uint32_t)0x0000E000)
/// WF_PA_VM_VBIT field LSB position
#define WLAN_RF_WF_PA_VM_VBIT_LSB            13
/// WF_PA_VM_VBIT field width
#define WLAN_RF_WF_PA_VM_VBIT_WIDTH          ((uint32_t)0x00000003)
/// WF_PA_VL_OPAM_EN field bit
#define WLAN_RF_WF_PA_VL_OPAM_EN_BIT         ((uint32_t)0x00001000)
/// WF_PA_VL_OPAM_EN field position
#define WLAN_RF_WF_PA_VL_OPAM_EN_POS         12
/// WF_PA_VL_IC_SEL_BIT field mask
#define WLAN_RF_WF_PA_VL_IC_SEL_BIT_MASK     ((uint32_t)0x00000E00)
/// WF_PA_VL_IC_SEL_BIT field LSB position
#define WLAN_RF_WF_PA_VL_IC_SEL_BIT_LSB      9
/// WF_PA_VL_IC_SEL_BIT field width
#define WLAN_RF_WF_PA_VL_IC_SEL_BIT_WIDTH    ((uint32_t)0x00000003)
/// WF_PA_VL_CGM_IBIT field mask
#define WLAN_RF_WF_PA_VL_CGM_IBIT_MASK       ((uint32_t)0x000001E0)
/// WF_PA_VL_CGM_IBIT field LSB position
#define WLAN_RF_WF_PA_VL_CGM_IBIT_LSB        5
/// WF_PA_VL_CGM_IBIT field width
#define WLAN_RF_WF_PA_VL_CGM_IBIT_WIDTH      ((uint32_t)0x00000004)
/// WF_PA_VL_VBIT field mask
#define WLAN_RF_WF_PA_VL_VBIT_MASK           ((uint32_t)0x0000001C)
/// WF_PA_VL_VBIT field LSB position
#define WLAN_RF_WF_PA_VL_VBIT_LSB            2
/// WF_PA_VL_VBIT field width
#define WLAN_RF_WF_PA_VL_VBIT_WIDTH          ((uint32_t)0x00000003)
/// WF_PA_LOFT_EN field bit
#define WLAN_RF_WF_PA_LOFT_EN_BIT            ((uint32_t)0x00000002)
/// WF_PA_LOFT_EN field position
#define WLAN_RF_WF_PA_LOFT_EN_POS            1
/// WF_PA_LOFT_LOWPASS_EN field bit
#define WLAN_RF_WF_PA_LOFT_LOWPASS_EN_BIT    ((uint32_t)0x00000001)
/// WF_PA_LOFT_LOWPASS_EN field position
#define WLAN_RF_WF_PA_LOFT_LOWPASS_EN_POS    0

/// WF_PA_INPUT_CBIT field reset value
#define WLAN_RF_WF_PA_INPUT_CBIT_RST         0x0
/// WF_PA_BIAS_VH_VBIT field reset value
#define WLAN_RF_WF_PA_BIAS_VH_VBIT_RST       0x6
/// WF_PA_VM_DYM_EN field reset value
#define WLAN_RF_WF_PA_VM_DYM_EN_RST          0x0
/// WF_PA_VM_VBIT_1 field reset value
#define WLAN_RF_WF_PA_VM_VBIT_1_RST          0x8
/// WF_PA_VM_VBIT_2 field reset value
#define WLAN_RF_WF_PA_VM_VBIT_2_RST          0x8
/// WF_PA_VM_VBIT field reset value
#define WLAN_RF_WF_PA_VM_VBIT_RST            0x4
/// WF_PA_VL_OPAM_EN field reset value
#define WLAN_RF_WF_PA_VL_OPAM_EN_RST         0x1
/// WF_PA_VL_IC_SEL_BIT field reset value
#define WLAN_RF_WF_PA_VL_IC_SEL_BIT_RST      0x1
/// WF_PA_VL_CGM_IBIT field reset value
#define WLAN_RF_WF_PA_VL_CGM_IBIT_RST        0x8
/// WF_PA_VL_VBIT field reset value
#define WLAN_RF_WF_PA_VL_VBIT_RST            0x4
/// WF_PA_LOFT_EN field reset value
#define WLAN_RF_WF_PA_LOFT_EN_RST            0x0
/// WF_PA_LOFT_LOWPASS_EN field reset value
#define WLAN_RF_WF_PA_LOFT_LOWPASS_EN_RST    0x1

/**
 * @brief Constructs a value for the REG_07 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpabiasvhvbit - The value to use for the wf_pa_bias_vh_vbit field.
 * @param[in] wfpavlopamen - The value to use for the wf_pa_vl_opam_en field.
 * @param[in] wfpavlicselbit - The value to use for the wf_pa_vl_ic_sel_bit field.
 * @param[in] wfpavlcgmibit - The value to use for the wf_pa_vl_cgm_ibit field.
 * @param[in] wfpaloften - The value to use for the wf_pa_loft_en field.
 * @param[in] wfpaloftlowpassen - The value to use for the wf_pa_loft_lowpass_en field.
 */
__INLINE void wlan_rf_reg_07_pack(uint8_t wfpabiasvhvbit, uint8_t wfpavlopamen, uint8_t wfpavlicselbit, uint8_t wfpavlcgmibit, uint8_t wfpaloften, uint8_t wfpaloftlowpassen)
{
    REG_PL_WR(WLAN_RF_REG_07_ADDR,  ((uint32_t)wfpabiasvhvbit << 25) | ((uint32_t)wfpavlopamen << 12) | ((uint32_t)wfpavlicselbit << 9) | ((uint32_t)wfpavlcgmibit << 5) | ((uint32_t)wfpaloften << 1) | ((uint32_t)wfpaloftlowpassen << 0));
}

/**
 * @brief Unpacks REG_07's fields from current value of the REG_07 register.
 *
 * Reads the REG_07 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpainputcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpabiasvhvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavmdymen - Will be populated with the current value of this field from the register.
 * @param[out] wfpavmvbit1 - Will be populated with the current value of this field from the register.
 * @param[out] wfpavmvbit2 - Will be populated with the current value of this field from the register.
 * @param[out] wfpavmvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavlopamen - Will be populated with the current value of this field from the register.
 * @param[out] wfpavlicselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavlcgmibit - Will be populated with the current value of this field from the register.
 * @param[out] wfpavlvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpaloften - Will be populated with the current value of this field from the register.
 * @param[out] wfpaloftlowpassen - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_07_unpack(uint8_t* wfpainputcbit, uint8_t* wfpabiasvhvbit, uint8_t* wfpavmdymen, uint8_t* wfpavmvbit1, uint8_t* wfpavmvbit2, uint8_t* wfpavmvbit, uint8_t* wfpavlopamen, uint8_t* wfpavlicselbit, uint8_t* wfpavlcgmibit, uint8_t* wfpavlvbit, uint8_t* wfpaloften, uint8_t* wfpaloftlowpassen)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);

    *wfpainputcbit = (localVal & ((uint32_t)0x70000000)) >> 28;
    *wfpabiasvhvbit = (localVal & ((uint32_t)0x0E000000)) >> 25;
    *wfpavmdymen = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wfpavmvbit1 = (localVal & ((uint32_t)0x00F00000)) >> 20;
    *wfpavmvbit2 = (localVal & ((uint32_t)0x000F0000)) >> 16;
    *wfpavmvbit = (localVal & ((uint32_t)0x0000E000)) >> 13;
    *wfpavlopamen = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wfpavlicselbit = (localVal & ((uint32_t)0x00000E00)) >> 9;
    *wfpavlcgmibit = (localVal & ((uint32_t)0x000001E0)) >> 5;
    *wfpavlvbit = (localVal & ((uint32_t)0x0000001C)) >> 2;
    *wfpaloften = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfpaloftlowpassen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pa_input_cbit field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_input_cbit field's value will be returned.
 *
 * @return The current value of the wf_pa_input_cbit field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_input_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

/**
 * @brief Returns the current value of the wf_pa_bias_vh_vbit field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_bias_vh_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa_bias_vh_vbit field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_bias_vh_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x0E000000)) >> 25);
}

/**
 * @brief Sets the wf_pa_bias_vh_vbit field of the REG_07 register.
 *
 * The REG_07 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpabiasvhvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_bias_vh_vbit_setf(uint8_t wfpabiasvhvbit)
{
    REG_PL_WR(WLAN_RF_REG_07_ADDR, (REG_PL_RD(WLAN_RF_REG_07_ADDR) & ~((uint32_t)0x0E000000)) | (((uint32_t)wfpabiasvhvbit << 25) & ((uint32_t)0x0E000000)));
}

/**
 * @brief Returns the current value of the wf_pa_vm_dym_en field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_vm_dym_en field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_dym_en field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_dym_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Returns the current value of the wf_pa_vm_vbit1 field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_vm_vbit1 field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_vbit1 field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_vbit_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x00F00000)) >> 20);
}

/**
 * @brief Returns the current value of the wf_pa_vm_vbit2 field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_vm_vbit2 field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_vbit2 field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_vbit_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x000F0000)) >> 16);
}

/**
 * @brief Returns the current value of the wf_pa_vm_vbit field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_vm_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa_vm_vbit field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vm_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x0000E000)) >> 13);
}

/**
 * @brief Returns the current value of the wf_pa_vl_opam_en field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_vl_opam_en field's value will be returned.
 *
 * @return The current value of the wf_pa_vl_opam_en field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vl_opam_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_pa_vl_opam_en field of the REG_07 register.
 *
 * The REG_07 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavlopamen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vl_opam_en_setf(uint8_t wfpavlopamen)
{
    REG_PL_WR(WLAN_RF_REG_07_ADDR, (REG_PL_RD(WLAN_RF_REG_07_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wfpavlopamen << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the wf_pa_vl_ic_sel_bit field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_vl_ic_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_pa_vl_ic_sel_bit field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vl_ic_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x00000E00)) >> 9);
}

/**
 * @brief Sets the wf_pa_vl_ic_sel_bit field of the REG_07 register.
 *
 * The REG_07 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavlicselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vl_ic_sel_bit_setf(uint8_t wfpavlicselbit)
{
    REG_PL_WR(WLAN_RF_REG_07_ADDR, (REG_PL_RD(WLAN_RF_REG_07_ADDR) & ~((uint32_t)0x00000E00)) | (((uint32_t)wfpavlicselbit << 9) & ((uint32_t)0x00000E00)));
}

/**
 * @brief Returns the current value of the wf_pa_vl_cgm_ibit field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_vl_cgm_ibit field's value will be returned.
 *
 * @return The current value of the wf_pa_vl_cgm_ibit field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vl_cgm_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x000001E0)) >> 5);
}

/**
 * @brief Sets the wf_pa_vl_cgm_ibit field of the REG_07 register.
 *
 * The REG_07 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpavlcgmibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_vl_cgm_ibit_setf(uint8_t wfpavlcgmibit)
{
    REG_PL_WR(WLAN_RF_REG_07_ADDR, (REG_PL_RD(WLAN_RF_REG_07_ADDR) & ~((uint32_t)0x000001E0)) | (((uint32_t)wfpavlcgmibit << 5) & ((uint32_t)0x000001E0)));
}

/**
 * @brief Returns the current value of the wf_pa_vl_vbit field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_vl_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa_vl_vbit field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_vl_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x0000001C)) >> 2);
}

/**
 * @brief Returns the current value of the wf_pa_loft_en field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_loft_en field's value will be returned.
 *
 * @return The current value of the wf_pa_loft_en field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_loft_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_pa_loft_en field of the REG_07 register.
 *
 * The REG_07 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpaloften - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_loft_en_setf(uint8_t wfpaloften)
{
    REG_PL_WR(WLAN_RF_REG_07_ADDR, (REG_PL_RD(WLAN_RF_REG_07_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfpaloften << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_pa_loft_lowpass_en field in the REG_07 register.
 *
 * The REG_07 register will be read and the wf_pa_loft_lowpass_en field's value will be returned.
 *
 * @return The current value of the wf_pa_loft_lowpass_en field in the REG_07 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_loft_lowpass_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_07_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_pa_loft_lowpass_en field of the REG_07 register.
 *
 * The REG_07 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpaloftlowpassen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_loft_lowpass_en_setf(uint8_t wfpaloftlowpassen)
{
    REG_PL_WR(WLAN_RF_REG_07_ADDR, (REG_PL_RD(WLAN_RF_REG_07_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfpaloftlowpassen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_08 register definitions
 * <table>
 * <caption id="REG_08_BF">REG_08 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30:28 <td>   wf_pa_loft_gbit <td>R <td>R/W <td>0x4
 * <tr><td>27 <td>      wf_pa_pkd_en <td>R <td>R/W <td>0
 * <tr><td>26:24 <td>wf_pa_pkdet_vth_vbit <td>R <td>R/W <td>0x4
 * <tr><td>23 <td>   wf_pa_isense_en <td>R <td>R/W <td>0
 * <tr><td>22 <td>wf_pa_isense_icsel_bit <td>R <td>R/W <td>0
 * <tr><td>21:19 <td>wf_pa_isense_resbit <td>R <td>R/W <td>0x4
 * <tr><td>18 <td>      wf_pa_dpd_en <td>R <td>R/W <td>0
 * <tr><td>17:15 <td>wf_pa_dpd_att_cbit <td>R <td>R/W <td>0x4
 * <tr><td>14:11 <td>wf_pa_trx_cap_sw_bit <td>W <td>R <td>0x8
 * <tr><td>10 <td>   wf_pa_pkdet_out <td>W <td>R <td>0
 * <tr><td>09:06 <td>wf_pa_rfop_hd2_cbit <td>R <td>R/W <td>0x8
 * <tr><td>05:03 <td> wf_dtmx_dvdd_vbit <td>R <td>R/W <td>0x4
 * <tr><td>02 <td>        wf_dtmx_ms <td>R <td>R/W <td>0
 * <tr><td>01:00 <td>wf_dtmx_path_mode_bit <td>R <td>R/W <td>0x3
 * </table>
 *
 * @{
 */

/// Address of the REG_08 register
#define WLAN_RF_REG_08_ADDR   0x40344020
/// Offset of the REG_08 register from the base address
#define WLAN_RF_REG_08_OFFSET 0x00000020
/// Index of the REG_08 register
#define WLAN_RF_REG_08_INDEX  0x00000008
/// Reset value of the REG_08 register
#define WLAN_RF_REG_08_RESET  0x44224223

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
/// WF_PA_LOFT_GBIT field mask
#define WLAN_RF_WF_PA_LOFT_GBIT_MASK          ((uint32_t)0x70000000)
/// WF_PA_LOFT_GBIT field LSB position
#define WLAN_RF_WF_PA_LOFT_GBIT_LSB           28
/// WF_PA_LOFT_GBIT field width
#define WLAN_RF_WF_PA_LOFT_GBIT_WIDTH         ((uint32_t)0x00000003)
/// WF_PA_PKD_EN field bit
#define WLAN_RF_WF_PA_PKD_EN_BIT              ((uint32_t)0x08000000)
/// WF_PA_PKD_EN field position
#define WLAN_RF_WF_PA_PKD_EN_POS              27
/// WF_PA_PKDET_VTH_VBIT field mask
#define WLAN_RF_WF_PA_PKDET_VTH_VBIT_MASK     ((uint32_t)0x07000000)
/// WF_PA_PKDET_VTH_VBIT field LSB position
#define WLAN_RF_WF_PA_PKDET_VTH_VBIT_LSB      24
/// WF_PA_PKDET_VTH_VBIT field width
#define WLAN_RF_WF_PA_PKDET_VTH_VBIT_WIDTH    ((uint32_t)0x00000003)
/// WF_PA_ISENSE_EN field bit
#define WLAN_RF_WF_PA_ISENSE_EN_BIT           ((uint32_t)0x00800000)
/// WF_PA_ISENSE_EN field position
#define WLAN_RF_WF_PA_ISENSE_EN_POS           23
/// WF_PA_ISENSE_ICSEL_BIT field bit
#define WLAN_RF_WF_PA_ISENSE_ICSEL_BIT_BIT    ((uint32_t)0x00400000)
/// WF_PA_ISENSE_ICSEL_BIT field position
#define WLAN_RF_WF_PA_ISENSE_ICSEL_BIT_POS    22
/// WF_PA_ISENSE_RESBIT field mask
#define WLAN_RF_WF_PA_ISENSE_RESBIT_MASK      ((uint32_t)0x00380000)
/// WF_PA_ISENSE_RESBIT field LSB position
#define WLAN_RF_WF_PA_ISENSE_RESBIT_LSB       19
/// WF_PA_ISENSE_RESBIT field width
#define WLAN_RF_WF_PA_ISENSE_RESBIT_WIDTH     ((uint32_t)0x00000003)
/// WF_PA_DPD_EN field bit
#define WLAN_RF_WF_PA_DPD_EN_BIT              ((uint32_t)0x00040000)
/// WF_PA_DPD_EN field position
#define WLAN_RF_WF_PA_DPD_EN_POS              18
/// WF_PA_DPD_ATT_CBIT field mask
#define WLAN_RF_WF_PA_DPD_ATT_CBIT_MASK       ((uint32_t)0x00038000)
/// WF_PA_DPD_ATT_CBIT field LSB position
#define WLAN_RF_WF_PA_DPD_ATT_CBIT_LSB        15
/// WF_PA_DPD_ATT_CBIT field width
#define WLAN_RF_WF_PA_DPD_ATT_CBIT_WIDTH      ((uint32_t)0x00000003)
/// WF_PA_TRX_CAP_SW_BIT field mask
#define WLAN_RF_WF_PA_TRX_CAP_SW_BIT_MASK     ((uint32_t)0x00007800)
/// WF_PA_TRX_CAP_SW_BIT field LSB position
#define WLAN_RF_WF_PA_TRX_CAP_SW_BIT_LSB      11
/// WF_PA_TRX_CAP_SW_BIT field width
#define WLAN_RF_WF_PA_TRX_CAP_SW_BIT_WIDTH    ((uint32_t)0x00000004)
/// WF_PA_PKDET_OUT field bit
#define WLAN_RF_WF_PA_PKDET_OUT_BIT           ((uint32_t)0x00000400)
/// WF_PA_PKDET_OUT field position
#define WLAN_RF_WF_PA_PKDET_OUT_POS           10
/// WF_PA_RFOP_HD_2_CBIT field mask
#define WLAN_RF_WF_PA_RFOP_HD_2_CBIT_MASK     ((uint32_t)0x000003C0)
/// WF_PA_RFOP_HD_2_CBIT field LSB position
#define WLAN_RF_WF_PA_RFOP_HD_2_CBIT_LSB      6
/// WF_PA_RFOP_HD_2_CBIT field width
#define WLAN_RF_WF_PA_RFOP_HD_2_CBIT_WIDTH    ((uint32_t)0x00000004)
/// WF_DTMX_DVDD_VBIT field mask
#define WLAN_RF_WF_DTMX_DVDD_VBIT_MASK        ((uint32_t)0x00000038)
/// WF_DTMX_DVDD_VBIT field LSB position
#define WLAN_RF_WF_DTMX_DVDD_VBIT_LSB         3
/// WF_DTMX_DVDD_VBIT field width
#define WLAN_RF_WF_DTMX_DVDD_VBIT_WIDTH       ((uint32_t)0x00000003)
/// WF_DTMX_MS field bit
#define WLAN_RF_WF_DTMX_MS_BIT                ((uint32_t)0x00000004)
/// WF_DTMX_MS field position
#define WLAN_RF_WF_DTMX_MS_POS                2
/// WF_DTMX_PATH_MODE_BIT field mask
#define WLAN_RF_WF_DTMX_PATH_MODE_BIT_MASK    ((uint32_t)0x00000003)
/// WF_DTMX_PATH_MODE_BIT field LSB position
#define WLAN_RF_WF_DTMX_PATH_MODE_BIT_LSB     0
/// WF_DTMX_PATH_MODE_BIT field width
#define WLAN_RF_WF_DTMX_PATH_MODE_BIT_WIDTH   ((uint32_t)0x00000002)

/// WF_PA_LOFT_GBIT field reset value
#define WLAN_RF_WF_PA_LOFT_GBIT_RST           0x4
/// WF_PA_PKD_EN field reset value
#define WLAN_RF_WF_PA_PKD_EN_RST              0x0
/// WF_PA_PKDET_VTH_VBIT field reset value
#define WLAN_RF_WF_PA_PKDET_VTH_VBIT_RST      0x4
/// WF_PA_ISENSE_EN field reset value
#define WLAN_RF_WF_PA_ISENSE_EN_RST           0x0
/// WF_PA_ISENSE_ICSEL_BIT field reset value
#define WLAN_RF_WF_PA_ISENSE_ICSEL_BIT_RST    0x0
/// WF_PA_ISENSE_RESBIT field reset value
#define WLAN_RF_WF_PA_ISENSE_RESBIT_RST       0x4
/// WF_PA_DPD_EN field reset value
#define WLAN_RF_WF_PA_DPD_EN_RST              0x0
/// WF_PA_DPD_ATT_CBIT field reset value
#define WLAN_RF_WF_PA_DPD_ATT_CBIT_RST        0x4
/// WF_PA_TRX_CAP_SW_BIT field reset value
#define WLAN_RF_WF_PA_TRX_CAP_SW_BIT_RST      0x8
/// WF_PA_PKDET_OUT field reset value
#define WLAN_RF_WF_PA_PKDET_OUT_RST           0x0
/// WF_PA_RFOP_HD_2_CBIT field reset value
#define WLAN_RF_WF_PA_RFOP_HD_2_CBIT_RST      0x8
/// WF_DTMX_DVDD_VBIT field reset value
#define WLAN_RF_WF_DTMX_DVDD_VBIT_RST         0x4
/// WF_DTMX_MS field reset value
#define WLAN_RF_WF_DTMX_MS_RST                0x0
/// WF_DTMX_PATH_MODE_BIT field reset value
#define WLAN_RF_WF_DTMX_PATH_MODE_BIT_RST     0x3

/**
 * @brief Constructs a value for the REG_08 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpaloftgbit - The value to use for the wf_pa_loft_gbit field.
 * @param[in] wfpapkden - The value to use for the wf_pa_pkd_en field.
 * @param[in] wfpapkdetvthvbit - The value to use for the wf_pa_pkdet_vth_vbit field.
 * @param[in] wfpaisenseen - The value to use for the wf_pa_isense_en field.
 * @param[in] wfpaisenseicselbit - The value to use for the wf_pa_isense_icsel_bit field.
 * @param[in] wfpaisenseresbit - The value to use for the wf_pa_isense_resbit field.
 * @param[in] wfpadpden - The value to use for the wf_pa_dpd_en field.
 * @param[in] wfpadpdattcbit - The value to use for the wf_pa_dpd_att_cbit field.
 * @param[in] wfparfophd2cbit - The value to use for the wf_pa_rfop_hd2_cbit field.
 * @param[in] wfdtmxdvddvbit - The value to use for the wf_dtmx_dvdd_vbit field.
 * @param[in] wfdtmxms - The value to use for the wf_dtmx_ms field.
 * @param[in] wfdtmxpathmodebit - The value to use for the wf_dtmx_path_mode_bit field.
 */
__INLINE void wlan_rf_reg_08_pack(uint8_t wfpaloftgbit, uint8_t wfpapkden, uint8_t wfpapkdetvthvbit, uint8_t wfpaisenseen, uint8_t wfpaisenseicselbit, uint8_t wfpaisenseresbit, uint8_t wfpadpden, uint8_t wfpadpdattcbit, uint8_t wfparfophd2cbit, uint8_t wfdtmxdvddvbit, uint8_t wfdtmxms, uint8_t wfdtmxpathmodebit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR,  ((uint32_t)wfpaloftgbit << 28) | ((uint32_t)wfpapkden << 27) | ((uint32_t)wfpapkdetvthvbit << 24) | ((uint32_t)wfpaisenseen << 23) | ((uint32_t)wfpaisenseicselbit << 22) | ((uint32_t)wfpaisenseresbit << 19) | ((uint32_t)wfpadpden << 18) | ((uint32_t)wfpadpdattcbit << 15) | ((uint32_t)wfparfophd2cbit << 6) | ((uint32_t)wfdtmxdvddvbit << 3) | ((uint32_t)wfdtmxms << 2) | ((uint32_t)wfdtmxpathmodebit << 0));
}

/**
 * @brief Unpacks REG_08's fields from current value of the REG_08 register.
 *
 * Reads the REG_08 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpaloftgbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkden - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetvthvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpaisenseen - Will be populated with the current value of this field from the register.
 * @param[out] wfpaisenseicselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpaisenseresbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpadpden - Will be populated with the current value of this field from the register.
 * @param[out] wfpadpdattcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpatrxcapswbit - Will be populated with the current value of this field from the register.
 * @param[out] wfpapkdetout - Will be populated with the current value of this field from the register.
 * @param[out] wfparfophd2cbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdvddvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxms - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxpathmodebit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_08_unpack(uint8_t* wfpaloftgbit, uint8_t* wfpapkden, uint8_t* wfpapkdetvthvbit, uint8_t* wfpaisenseen, uint8_t* wfpaisenseicselbit, uint8_t* wfpaisenseresbit, uint8_t* wfpadpden, uint8_t* wfpadpdattcbit, uint8_t* wfpatrxcapswbit, uint8_t* wfpapkdetout, uint8_t* wfparfophd2cbit, uint8_t* wfdtmxdvddvbit, uint8_t* wfdtmxms, uint8_t* wfdtmxpathmodebit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);

    *wfpaloftgbit = (localVal & ((uint32_t)0x70000000)) >> 28;
    *wfpapkden = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfpapkdetvthvbit = (localVal & ((uint32_t)0x07000000)) >> 24;
    *wfpaisenseen = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfpaisenseicselbit = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wfpaisenseresbit = (localVal & ((uint32_t)0x00380000)) >> 19;
    *wfpadpden = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfpadpdattcbit = (localVal & ((uint32_t)0x00038000)) >> 15;
    *wfpatrxcapswbit = (localVal & ((uint32_t)0x00007800)) >> 11;
    *wfpapkdetout = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfparfophd2cbit = (localVal & ((uint32_t)0x000003C0)) >> 6;
    *wfdtmxdvddvbit = (localVal & ((uint32_t)0x00000038)) >> 3;
    *wfdtmxms = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wfdtmxpathmodebit = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pa_loft_gbit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_loft_gbit field's value will be returned.
 *
 * @return The current value of the wf_pa_loft_gbit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_loft_gbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

/**
 * @brief Sets the wf_pa_loft_gbit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpaloftgbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_loft_gbit_setf(uint8_t wfpaloftgbit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x70000000)) | (((uint32_t)wfpaloftgbit << 28) & ((uint32_t)0x70000000)));
}

/**
 * @brief Returns the current value of the wf_pa_pkd_en field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_pkd_en field's value will be returned.
 *
 * @return The current value of the wf_pa_pkd_en field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_pa_pkd_en field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkden - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkd_en_setf(uint8_t wfpapkden)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wfpapkden << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_vth_vbit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_pkdet_vth_vbit field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_vth_vbit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_vth_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

/**
 * @brief Sets the wf_pa_pkdet_vth_vbit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpapkdetvthvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_pkdet_vth_vbit_setf(uint8_t wfpapkdetvthvbit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x07000000)) | (((uint32_t)wfpapkdetvthvbit << 24) & ((uint32_t)0x07000000)));
}

/**
 * @brief Returns the current value of the wf_pa_isense_en field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_isense_en field's value will be returned.
 *
 * @return The current value of the wf_pa_isense_en field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_isense_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_pa_isense_en field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpaisenseen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_isense_en_setf(uint8_t wfpaisenseen)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wfpaisenseen << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_pa_isense_icsel_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_isense_icsel_bit field's value will be returned.
 *
 * @return The current value of the wf_pa_isense_icsel_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_isense_icsel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the wf_pa_isense_icsel_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpaisenseicselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_isense_icsel_bit_setf(uint8_t wfpaisenseicselbit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)wfpaisenseicselbit << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the wf_pa_isense_resbit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_isense_resbit field's value will be returned.
 *
 * @return The current value of the wf_pa_isense_resbit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_isense_resbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00380000)) >> 19);
}

/**
 * @brief Sets the wf_pa_isense_resbit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpaisenseresbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_isense_resbit_setf(uint8_t wfpaisenseresbit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00380000)) | (((uint32_t)wfpaisenseresbit << 19) & ((uint32_t)0x00380000)));
}

/**
 * @brief Returns the current value of the wf_pa_dpd_en field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_dpd_en field's value will be returned.
 *
 * @return The current value of the wf_pa_dpd_en field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_dpd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_pa_dpd_en field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpadpden - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_dpd_en_setf(uint8_t wfpadpden)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wfpadpden << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_pa_dpd_att_cbit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_dpd_att_cbit field's value will be returned.
 *
 * @return The current value of the wf_pa_dpd_att_cbit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_dpd_att_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00038000)) >> 15);
}

/**
 * @brief Sets the wf_pa_dpd_att_cbit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpadpdattcbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_dpd_att_cbit_setf(uint8_t wfpadpdattcbit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00038000)) | (((uint32_t)wfpadpdattcbit << 15) & ((uint32_t)0x00038000)));
}

/**
 * @brief Returns the current value of the wf_pa_trx_cap_sw_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_trx_cap_sw_bit field's value will be returned.
 *
 * @return The current value of the wf_pa_trx_cap_sw_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_trx_cap_sw_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00007800)) >> 11);
}

/**
 * @brief Returns the current value of the wf_pa_pkdet_out field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_pkdet_out field's value will be returned.
 *
 * @return The current value of the wf_pa_pkdet_out field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_pkdet_out_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Returns the current value of the wf_pa_rfop_hd2_cbit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_pa_rfop_hd2_cbit field's value will be returned.
 *
 * @return The current value of the wf_pa_rfop_hd2_cbit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_pa_rfop_hd_2_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x000003C0)) >> 6);
}

/**
 * @brief Sets the wf_pa_rfop_hd2_cbit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfparfophd2cbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pa_rfop_hd_2_cbit_setf(uint8_t wfparfophd2cbit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x000003C0)) | (((uint32_t)wfparfophd2cbit << 6) & ((uint32_t)0x000003C0)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dvdd_vbit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_dtmx_dvdd_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dvdd_vbit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dvdd_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000038)) >> 3);
}

/**
 * @brief Sets the wf_dtmx_dvdd_vbit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdvddvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dvdd_vbit_setf(uint8_t wfdtmxdvddvbit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00000038)) | (((uint32_t)wfdtmxdvddvbit << 3) & ((uint32_t)0x00000038)));
}

/**
 * @brief Returns the current value of the wf_dtmx_ms field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_dtmx_ms field's value will be returned.
 *
 * @return The current value of the wf_dtmx_ms field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_ms_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wf_dtmx_ms field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxms - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_ms_setf(uint8_t wfdtmxms)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wfdtmxms << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wf_dtmx_path_mode_bit field in the REG_08 register.
 *
 * The REG_08 register will be read and the wf_dtmx_path_mode_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_path_mode_bit field in the REG_08 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_path_mode_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_08_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the wf_dtmx_path_mode_bit field of the REG_08 register.
 *
 * The REG_08 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxpathmodebit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_path_mode_bit_setf(uint8_t wfdtmxpathmodebit)
{
    REG_PL_WR(WLAN_RF_REG_08_ADDR, (REG_PL_RD(WLAN_RF_REG_08_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)wfdtmxpathmodebit << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_09 register definitions
 * <table>
 * <caption id="REG_09_BF">REG_09 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:29 <td>wf_dtmx_cscd_hbias_vbit <td>R <td>R/W <td>0x6
 * <tr><td>28:26 <td>wf_dtmx_lobias_vbit <td>R <td>R/W <td>0x1
 * <tr><td>25:23 <td> wf_dtmx_dac_gbit1 <td>W <td>R <td>0x4
 * <tr><td>22:19 <td> wf_dtmx_dac_gbit2 <td>W <td>R <td>0x7
 * <tr><td>18:15 <td>wf_dtmx_dac_vcasd_vbit1 <td>W <td>R <td>0xB
 * <tr><td>14:12 <td>wf_dtmx_dac_vcasd_vbit2 <td>W <td>R <td>0x4
 * <tr><td>11 <td>   wf_dtmx_idac_en <td>W <td>R <td>0
 * <tr><td>10 <td>wf_dtmx_idac_clk_sel_pos_edge <td>R <td>R/W <td>1
 * <tr><td>09:06 <td>wf_dtmx_idac_offset_bit <td>W <td>R <td>0x0
 * <tr><td>05:02 <td>wf_dtmx_tuning_cbit <td>W <td>R <td>0x8
 * <tr><td>01 <td>wf_dtmx_capbit_h_en <td>R <td>R/W <td>0
 * <tr><td>00 <td>wf_dtmx_lo_div4_en <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the REG_09 register
#define WLAN_RF_REG_09_ADDR   0x40344024
/// Offset of the REG_09 register from the base address
#define WLAN_RF_REG_09_OFFSET 0x00000024
/// Index of the REG_09 register
#define WLAN_RF_REG_09_INDEX  0x00000009
/// Reset value of the REG_09 register
#define WLAN_RF_REG_09_RESET  0xC63DC421

/**
 * @brief Returns the current value of the REG_09 register.
 * The REG_09 register will be read and its value returned.
 * @return The current value of the REG_09 register.
 */
__INLINE uint32_t wlan_rf_reg_09_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_09_ADDR);
}

/**
 * @brief Sets the REG_09 register to a value.
 * The REG_09 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_09_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_09_ADDR, value);
}

// field definitions
/// WF_DTMX_CSCD_HBIAS_VBIT field mask
#define WLAN_RF_WF_DTMX_CSCD_HBIAS_VBIT_MASK         ((uint32_t)0xE0000000)
/// WF_DTMX_CSCD_HBIAS_VBIT field LSB position
#define WLAN_RF_WF_DTMX_CSCD_HBIAS_VBIT_LSB          29
/// WF_DTMX_CSCD_HBIAS_VBIT field width
#define WLAN_RF_WF_DTMX_CSCD_HBIAS_VBIT_WIDTH        ((uint32_t)0x00000003)
/// WF_DTMX_LOBIAS_VBIT field mask
#define WLAN_RF_WF_DTMX_LOBIAS_VBIT_MASK             ((uint32_t)0x1C000000)
/// WF_DTMX_LOBIAS_VBIT field LSB position
#define WLAN_RF_WF_DTMX_LOBIAS_VBIT_LSB              26
/// WF_DTMX_LOBIAS_VBIT field width
#define WLAN_RF_WF_DTMX_LOBIAS_VBIT_WIDTH            ((uint32_t)0x00000003)
/// WF_DTMX_DAC_GBIT_1 field mask
#define WLAN_RF_WF_DTMX_DAC_GBIT_1_MASK              ((uint32_t)0x03800000)
/// WF_DTMX_DAC_GBIT_1 field LSB position
#define WLAN_RF_WF_DTMX_DAC_GBIT_1_LSB               23
/// WF_DTMX_DAC_GBIT_1 field width
#define WLAN_RF_WF_DTMX_DAC_GBIT_1_WIDTH             ((uint32_t)0x00000003)
/// WF_DTMX_DAC_GBIT_2 field mask
#define WLAN_RF_WF_DTMX_DAC_GBIT_2_MASK              ((uint32_t)0x00780000)
/// WF_DTMX_DAC_GBIT_2 field LSB position
#define WLAN_RF_WF_DTMX_DAC_GBIT_2_LSB               19
/// WF_DTMX_DAC_GBIT_2 field width
#define WLAN_RF_WF_DTMX_DAC_GBIT_2_WIDTH             ((uint32_t)0x00000004)
/// WF_DTMX_DAC_VCASD_VBIT_1 field mask
#define WLAN_RF_WF_DTMX_DAC_VCASD_VBIT_1_MASK        ((uint32_t)0x00078000)
/// WF_DTMX_DAC_VCASD_VBIT_1 field LSB position
#define WLAN_RF_WF_DTMX_DAC_VCASD_VBIT_1_LSB         15
/// WF_DTMX_DAC_VCASD_VBIT_1 field width
#define WLAN_RF_WF_DTMX_DAC_VCASD_VBIT_1_WIDTH       ((uint32_t)0x00000004)
/// WF_DTMX_DAC_VCASD_VBIT_2 field mask
#define WLAN_RF_WF_DTMX_DAC_VCASD_VBIT_2_MASK        ((uint32_t)0x00007000)
/// WF_DTMX_DAC_VCASD_VBIT_2 field LSB position
#define WLAN_RF_WF_DTMX_DAC_VCASD_VBIT_2_LSB         12
/// WF_DTMX_DAC_VCASD_VBIT_2 field width
#define WLAN_RF_WF_DTMX_DAC_VCASD_VBIT_2_WIDTH       ((uint32_t)0x00000003)
/// WF_DTMX_IDAC_EN field bit
#define WLAN_RF_WF_DTMX_IDAC_EN_BIT                  ((uint32_t)0x00000800)
/// WF_DTMX_IDAC_EN field position
#define WLAN_RF_WF_DTMX_IDAC_EN_POS                  11
/// WF_DTMX_IDAC_CLK_SEL_POS_EDGE field bit
#define WLAN_RF_WF_DTMX_IDAC_CLK_SEL_POS_EDGE_BIT    ((uint32_t)0x00000400)
/// WF_DTMX_IDAC_CLK_SEL_POS_EDGE field position
#define WLAN_RF_WF_DTMX_IDAC_CLK_SEL_POS_EDGE_POS    10
/// WF_DTMX_IDAC_OFFSET_BIT field mask
#define WLAN_RF_WF_DTMX_IDAC_OFFSET_BIT_MASK         ((uint32_t)0x000003C0)
/// WF_DTMX_IDAC_OFFSET_BIT field LSB position
#define WLAN_RF_WF_DTMX_IDAC_OFFSET_BIT_LSB          6
/// WF_DTMX_IDAC_OFFSET_BIT field width
#define WLAN_RF_WF_DTMX_IDAC_OFFSET_BIT_WIDTH        ((uint32_t)0x00000004)
/// WF_DTMX_TUNING_CBIT field mask
#define WLAN_RF_WF_DTMX_TUNING_CBIT_MASK             ((uint32_t)0x0000003C)
/// WF_DTMX_TUNING_CBIT field LSB position
#define WLAN_RF_WF_DTMX_TUNING_CBIT_LSB              2
/// WF_DTMX_TUNING_CBIT field width
#define WLAN_RF_WF_DTMX_TUNING_CBIT_WIDTH            ((uint32_t)0x00000004)
/// WF_DTMX_CAPBIT_H_EN field bit
#define WLAN_RF_WF_DTMX_CAPBIT_H_EN_BIT              ((uint32_t)0x00000002)
/// WF_DTMX_CAPBIT_H_EN field position
#define WLAN_RF_WF_DTMX_CAPBIT_H_EN_POS              1
/// WF_DTMX_LO_DIV_4_EN field bit
#define WLAN_RF_WF_DTMX_LO_DIV_4_EN_BIT              ((uint32_t)0x00000001)
/// WF_DTMX_LO_DIV_4_EN field position
#define WLAN_RF_WF_DTMX_LO_DIV_4_EN_POS              0

/// WF_DTMX_CSCD_HBIAS_VBIT field reset value
#define WLAN_RF_WF_DTMX_CSCD_HBIAS_VBIT_RST          0x6
/// WF_DTMX_LOBIAS_VBIT field reset value
#define WLAN_RF_WF_DTMX_LOBIAS_VBIT_RST              0x1
/// WF_DTMX_DAC_GBIT_1 field reset value
#define WLAN_RF_WF_DTMX_DAC_GBIT_1_RST               0x4
/// WF_DTMX_DAC_GBIT_2 field reset value
#define WLAN_RF_WF_DTMX_DAC_GBIT_2_RST               0x7
/// WF_DTMX_DAC_VCASD_VBIT_1 field reset value
#define WLAN_RF_WF_DTMX_DAC_VCASD_VBIT_1_RST         0xB
/// WF_DTMX_DAC_VCASD_VBIT_2 field reset value
#define WLAN_RF_WF_DTMX_DAC_VCASD_VBIT_2_RST         0x4
/// WF_DTMX_IDAC_EN field reset value
#define WLAN_RF_WF_DTMX_IDAC_EN_RST                  0x0
/// WF_DTMX_IDAC_CLK_SEL_POS_EDGE field reset value
#define WLAN_RF_WF_DTMX_IDAC_CLK_SEL_POS_EDGE_RST    0x1
/// WF_DTMX_IDAC_OFFSET_BIT field reset value
#define WLAN_RF_WF_DTMX_IDAC_OFFSET_BIT_RST          0x0
/// WF_DTMX_TUNING_CBIT field reset value
#define WLAN_RF_WF_DTMX_TUNING_CBIT_RST              0x8
/// WF_DTMX_CAPBIT_H_EN field reset value
#define WLAN_RF_WF_DTMX_CAPBIT_H_EN_RST              0x0
/// WF_DTMX_LO_DIV_4_EN field reset value
#define WLAN_RF_WF_DTMX_LO_DIV_4_EN_RST              0x1

/**
 * @brief Constructs a value for the REG_09 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfdtmxcscdhbiasvbit - The value to use for the wf_dtmx_cscd_hbias_vbit field.
 * @param[in] wfdtmxlobiasvbit - The value to use for the wf_dtmx_lobias_vbit field.
 * @param[in] wfdtmxidacclkselposedge - The value to use for the wf_dtmx_idac_clk_sel_pos_edge field.
 * @param[in] wfdtmxcapbithen - The value to use for the wf_dtmx_capbit_h_en field.
 * @param[in] wfdtmxlodiv4en - The value to use for the wf_dtmx_lo_div4_en field.
 */
__INLINE void wlan_rf_reg_09_pack(uint8_t wfdtmxcscdhbiasvbit, uint8_t wfdtmxlobiasvbit, uint8_t wfdtmxidacclkselposedge, uint8_t wfdtmxcapbithen, uint8_t wfdtmxlodiv4en)
{
    REG_PL_WR(WLAN_RF_REG_09_ADDR,  ((uint32_t)wfdtmxcscdhbiasvbit << 29) | ((uint32_t)wfdtmxlobiasvbit << 26) | ((uint32_t)wfdtmxidacclkselposedge << 10) | ((uint32_t)wfdtmxcapbithen << 1) | ((uint32_t)wfdtmxlodiv4en << 0));
}

/**
 * @brief Unpacks REG_09's fields from current value of the REG_09 register.
 *
 * Reads the REG_09 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfdtmxcscdhbiasvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlobiasvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdacgbit1 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdacgbit2 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdacvcasdvbit1 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdacvcasdvbit2 - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxidacen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxidacclkselposedge - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxidacoffsetbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxtuningcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcapbithen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlodiv4en - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_09_unpack(uint8_t* wfdtmxcscdhbiasvbit, uint8_t* wfdtmxlobiasvbit, uint8_t* wfdtmxdacgbit1, uint8_t* wfdtmxdacgbit2, uint8_t* wfdtmxdacvcasdvbit1, uint8_t* wfdtmxdacvcasdvbit2, uint8_t* wfdtmxidacen, uint8_t* wfdtmxidacclkselposedge, uint8_t* wfdtmxidacoffsetbit, uint8_t* wfdtmxtuningcbit, uint8_t* wfdtmxcapbithen, uint8_t* wfdtmxlodiv4en)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);

    *wfdtmxcscdhbiasvbit = (localVal & ((uint32_t)0xE0000000)) >> 29;
    *wfdtmxlobiasvbit = (localVal & ((uint32_t)0x1C000000)) >> 26;
    *wfdtmxdacgbit1 = (localVal & ((uint32_t)0x03800000)) >> 23;
    *wfdtmxdacgbit2 = (localVal & ((uint32_t)0x00780000)) >> 19;
    *wfdtmxdacvcasdvbit1 = (localVal & ((uint32_t)0x00078000)) >> 15;
    *wfdtmxdacvcasdvbit2 = (localVal & ((uint32_t)0x00007000)) >> 12;
    *wfdtmxidacen = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wfdtmxidacclkselposedge = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfdtmxidacoffsetbit = (localVal & ((uint32_t)0x000003C0)) >> 6;
    *wfdtmxtuningcbit = (localVal & ((uint32_t)0x0000003C)) >> 2;
    *wfdtmxcapbithen = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfdtmxlodiv4en = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_dtmx_cscd_hbias_vbit field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_cscd_hbias_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cscd_hbias_vbit field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cscd_hbias_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0xE0000000)) >> 29);
}

/**
 * @brief Sets the wf_dtmx_cscd_hbias_vbit field of the REG_09 register.
 *
 * The REG_09 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcscdhbiasvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cscd_hbias_vbit_setf(uint8_t wfdtmxcscdhbiasvbit)
{
    REG_PL_WR(WLAN_RF_REG_09_ADDR, (REG_PL_RD(WLAN_RF_REG_09_ADDR) & ~((uint32_t)0xE0000000)) | (((uint32_t)wfdtmxcscdhbiasvbit << 29) & ((uint32_t)0xE0000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_lobias_vbit field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_lobias_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_lobias_vbit field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_lobias_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x1C000000)) >> 26);
}

/**
 * @brief Sets the wf_dtmx_lobias_vbit field of the REG_09 register.
 *
 * The REG_09 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlobiasvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_lobias_vbit_setf(uint8_t wfdtmxlobiasvbit)
{
    REG_PL_WR(WLAN_RF_REG_09_ADDR, (REG_PL_RD(WLAN_RF_REG_09_ADDR) & ~((uint32_t)0x1C000000)) | (((uint32_t)wfdtmxlobiasvbit << 26) & ((uint32_t)0x1C000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dac_gbit1 field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_dac_gbit1 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dac_gbit1 field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dac_gbit_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x03800000)) >> 23);
}

/**
 * @brief Returns the current value of the wf_dtmx_dac_gbit2 field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_dac_gbit2 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dac_gbit2 field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dac_gbit_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x00780000)) >> 19);
}

/**
 * @brief Returns the current value of the wf_dtmx_dac_vcasd_vbit1 field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_dac_vcasd_vbit1 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dac_vcasd_vbit1 field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dac_vcasd_vbit_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x00078000)) >> 15);
}

/**
 * @brief Returns the current value of the wf_dtmx_dac_vcasd_vbit2 field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_dac_vcasd_vbit2 field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dac_vcasd_vbit2 field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dac_vcasd_vbit_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

/**
 * @brief Returns the current value of the wf_dtmx_idac_en field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_idac_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_idac_en field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_idac_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Returns the current value of the wf_dtmx_idac_clk_sel_pos_edge field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_idac_clk_sel_pos_edge field's value will be returned.
 *
 * @return The current value of the wf_dtmx_idac_clk_sel_pos_edge field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_idac_clk_sel_pos_edge_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_dtmx_idac_clk_sel_pos_edge field of the REG_09 register.
 *
 * The REG_09 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxidacclkselposedge - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_idac_clk_sel_pos_edge_setf(uint8_t wfdtmxidacclkselposedge)
{
    REG_PL_WR(WLAN_RF_REG_09_ADDR, (REG_PL_RD(WLAN_RF_REG_09_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfdtmxidacclkselposedge << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_dtmx_idac_offset_bit field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_idac_offset_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_idac_offset_bit field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_idac_offset_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x000003C0)) >> 6);
}

/**
 * @brief Returns the current value of the wf_dtmx_tuning_cbit field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_tuning_cbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_tuning_cbit field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_tuning_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x0000003C)) >> 2);
}

/**
 * @brief Returns the current value of the wf_dtmx_capbit_h_en field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_capbit_h_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_capbit_h_en field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_capbit_h_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_dtmx_capbit_h_en field of the REG_09 register.
 *
 * The REG_09 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcapbithen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_capbit_h_en_setf(uint8_t wfdtmxcapbithen)
{
    REG_PL_WR(WLAN_RF_REG_09_ADDR, (REG_PL_RD(WLAN_RF_REG_09_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfdtmxcapbithen << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_dtmx_lo_div4_en field in the REG_09 register.
 *
 * The REG_09 register will be read and the wf_dtmx_lo_div4_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_lo_div4_en field in the REG_09 register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_lo_div_4_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_09_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_dtmx_lo_div4_en field of the REG_09 register.
 *
 * The REG_09 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlodiv4en - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_lo_div_4_en_setf(uint8_t wfdtmxlodiv4en)
{
    REG_PL_WR(WLAN_RF_REG_09_ADDR, (REG_PL_RD(WLAN_RF_REG_09_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfdtmxlodiv4en << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_0A register definitions
 * <table>
 * <caption id="REG_0A_BF">REG_0A bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30:28 <td>wf_dtmx_lo_reg_vbit <td>R <td>R/W <td>0x4
 * <tr><td>27:26 <td>wf_dtmx_lo_path_phase_sel <td>R <td>R/W <td>0x3
 * <tr><td>25 <td>wf_dtmx_clk2cdr_en <td>R <td>R/W <td>1
 * <tr><td>24 <td>  wf_dtmx_div_rstn <td>R <td>R/W <td>1
 * <tr><td>23 <td>wf_dtmx_clk2dac_sel_dig <td>R <td>R/W <td>0
 * <tr><td>22:21 <td>wf_dtmx_cdr_div_mode_bit <td>R <td>R/W <td>0x2
 * <tr><td>20 <td>    wf_dtmx_cdr_en <td>R <td>R/W <td>1
 * <tr><td>19:15 <td>wf_dtmx_offset_bits <td>R <td>R/W <td>0x0
 * <tr><td>14 <td>wf_dtmx_clk_sel_pos_edge <td>R <td>R/W <td>1
 * <tr><td>13:11 <td>wf_dtmx_clk_phase_sel_bit <td>R <td>R/W <td>0x4
 * <tr><td>10 <td>wf_dtmx_clk_iq_delay_en <td>R <td>R/W <td>1
 * <tr><td>09 <td>wf_dtmx_clk_path0_45_delay_en <td>R <td>R/W <td>1
 * <tr><td>08:06 <td>wf_dtmx_clk_freq_sel_bit <td>R <td>R/W <td>0x4
 * <tr><td>05:01 <td>wf_dtmx_clk2dig_dly_bit <td>R <td>R/W <td>0x0
 * <tr><td>00 <td>wf_dtmx_dpd_cal_en <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_0A register
#define WLAN_RF_REG_0A_ADDR   0x40344028
/// Offset of the REG_0A register from the base address
#define WLAN_RF_REG_0A_OFFSET 0x00000028
/// Index of the REG_0A register
#define WLAN_RF_REG_0A_INDEX  0x0000000A
/// Reset value of the REG_0A register
#define WLAN_RF_REG_0A_RESET  0x4F506700

/**
 * @brief Returns the current value of the REG_0A register.
 * The REG_0A register will be read and its value returned.
 * @return The current value of the REG_0A register.
 */
__INLINE uint32_t wlan_rf_reg_0a_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_0A_ADDR);
}

/**
 * @brief Sets the REG_0A register to a value.
 * The REG_0A register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_0a_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, value);
}

// field definitions
/// WF_DTMX_LO_REG_VBIT field mask
#define WLAN_RF_WF_DTMX_LO_REG_VBIT_MASK               ((uint32_t)0x70000000)
/// WF_DTMX_LO_REG_VBIT field LSB position
#define WLAN_RF_WF_DTMX_LO_REG_VBIT_LSB                28
/// WF_DTMX_LO_REG_VBIT field width
#define WLAN_RF_WF_DTMX_LO_REG_VBIT_WIDTH              ((uint32_t)0x00000003)
/// WF_DTMX_LO_PATH_PHASE_SEL field mask
#define WLAN_RF_WF_DTMX_LO_PATH_PHASE_SEL_MASK         ((uint32_t)0x0C000000)
/// WF_DTMX_LO_PATH_PHASE_SEL field LSB position
#define WLAN_RF_WF_DTMX_LO_PATH_PHASE_SEL_LSB          26
/// WF_DTMX_LO_PATH_PHASE_SEL field width
#define WLAN_RF_WF_DTMX_LO_PATH_PHASE_SEL_WIDTH        ((uint32_t)0x00000002)
/// WF_DTMX_CLK_2CDR_EN field bit
#define WLAN_RF_WF_DTMX_CLK_2CDR_EN_BIT                ((uint32_t)0x02000000)
/// WF_DTMX_CLK_2CDR_EN field position
#define WLAN_RF_WF_DTMX_CLK_2CDR_EN_POS                25
/// WF_DTMX_DIV_RSTN field bit
#define WLAN_RF_WF_DTMX_DIV_RSTN_BIT                   ((uint32_t)0x01000000)
/// WF_DTMX_DIV_RSTN field position
#define WLAN_RF_WF_DTMX_DIV_RSTN_POS                   24
/// WF_DTMX_CLK_2DAC_SEL_DIG field bit
#define WLAN_RF_WF_DTMX_CLK_2DAC_SEL_DIG_BIT           ((uint32_t)0x00800000)
/// WF_DTMX_CLK_2DAC_SEL_DIG field position
#define WLAN_RF_WF_DTMX_CLK_2DAC_SEL_DIG_POS           23
/// WF_DTMX_CDR_DIV_MODE_BIT field mask
#define WLAN_RF_WF_DTMX_CDR_DIV_MODE_BIT_MASK          ((uint32_t)0x00600000)
/// WF_DTMX_CDR_DIV_MODE_BIT field LSB position
#define WLAN_RF_WF_DTMX_CDR_DIV_MODE_BIT_LSB           21
/// WF_DTMX_CDR_DIV_MODE_BIT field width
#define WLAN_RF_WF_DTMX_CDR_DIV_MODE_BIT_WIDTH         ((uint32_t)0x00000002)
/// WF_DTMX_CDR_EN field bit
#define WLAN_RF_WF_DTMX_CDR_EN_BIT                     ((uint32_t)0x00100000)
/// WF_DTMX_CDR_EN field position
#define WLAN_RF_WF_DTMX_CDR_EN_POS                     20
/// WF_DTMX_OFFSET_BITS field mask
#define WLAN_RF_WF_DTMX_OFFSET_BITS_MASK               ((uint32_t)0x000F8000)
/// WF_DTMX_OFFSET_BITS field LSB position
#define WLAN_RF_WF_DTMX_OFFSET_BITS_LSB                15
/// WF_DTMX_OFFSET_BITS field width
#define WLAN_RF_WF_DTMX_OFFSET_BITS_WIDTH              ((uint32_t)0x00000005)
/// WF_DTMX_CLK_SEL_POS_EDGE field bit
#define WLAN_RF_WF_DTMX_CLK_SEL_POS_EDGE_BIT           ((uint32_t)0x00004000)
/// WF_DTMX_CLK_SEL_POS_EDGE field position
#define WLAN_RF_WF_DTMX_CLK_SEL_POS_EDGE_POS           14
/// WF_DTMX_CLK_PHASE_SEL_BIT field mask
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_BIT_MASK         ((uint32_t)0x00003800)
/// WF_DTMX_CLK_PHASE_SEL_BIT field LSB position
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_BIT_LSB          11
/// WF_DTMX_CLK_PHASE_SEL_BIT field width
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_BIT_WIDTH        ((uint32_t)0x00000003)
/// WF_DTMX_CLK_IQ_DELAY_EN field bit
#define WLAN_RF_WF_DTMX_CLK_IQ_DELAY_EN_BIT            ((uint32_t)0x00000400)
/// WF_DTMX_CLK_IQ_DELAY_EN field position
#define WLAN_RF_WF_DTMX_CLK_IQ_DELAY_EN_POS            10
/// WF_DTMX_CLK_PATH_0__45_DELAY_EN field bit
#define WLAN_RF_WF_DTMX_CLK_PATH_0__45_DELAY_EN_BIT    ((uint32_t)0x00000200)
/// WF_DTMX_CLK_PATH_0__45_DELAY_EN field position
#define WLAN_RF_WF_DTMX_CLK_PATH_0__45_DELAY_EN_POS    9
/// WF_DTMX_CLK_FREQ_SEL_BIT field mask
#define WLAN_RF_WF_DTMX_CLK_FREQ_SEL_BIT_MASK          ((uint32_t)0x000001C0)
/// WF_DTMX_CLK_FREQ_SEL_BIT field LSB position
#define WLAN_RF_WF_DTMX_CLK_FREQ_SEL_BIT_LSB           6
/// WF_DTMX_CLK_FREQ_SEL_BIT field width
#define WLAN_RF_WF_DTMX_CLK_FREQ_SEL_BIT_WIDTH         ((uint32_t)0x00000003)
/// WF_DTMX_CLK_2DIG_DLY_BIT field mask
#define WLAN_RF_WF_DTMX_CLK_2DIG_DLY_BIT_MASK          ((uint32_t)0x0000003E)
/// WF_DTMX_CLK_2DIG_DLY_BIT field LSB position
#define WLAN_RF_WF_DTMX_CLK_2DIG_DLY_BIT_LSB           1
/// WF_DTMX_CLK_2DIG_DLY_BIT field width
#define WLAN_RF_WF_DTMX_CLK_2DIG_DLY_BIT_WIDTH         ((uint32_t)0x00000005)
/// WF_DTMX_DPD_CAL_EN field bit
#define WLAN_RF_WF_DTMX_DPD_CAL_EN_BIT                 ((uint32_t)0x00000001)
/// WF_DTMX_DPD_CAL_EN field position
#define WLAN_RF_WF_DTMX_DPD_CAL_EN_POS                 0

/// WF_DTMX_LO_REG_VBIT field reset value
#define WLAN_RF_WF_DTMX_LO_REG_VBIT_RST                0x4
/// WF_DTMX_LO_PATH_PHASE_SEL field reset value
#define WLAN_RF_WF_DTMX_LO_PATH_PHASE_SEL_RST          0x3
/// WF_DTMX_CLK_2CDR_EN field reset value
#define WLAN_RF_WF_DTMX_CLK_2CDR_EN_RST                0x1
/// WF_DTMX_DIV_RSTN field reset value
#define WLAN_RF_WF_DTMX_DIV_RSTN_RST                   0x1
/// WF_DTMX_CLK_2DAC_SEL_DIG field reset value
#define WLAN_RF_WF_DTMX_CLK_2DAC_SEL_DIG_RST           0x0
/// WF_DTMX_CDR_DIV_MODE_BIT field reset value
#define WLAN_RF_WF_DTMX_CDR_DIV_MODE_BIT_RST           0x2
/// WF_DTMX_CDR_EN field reset value
#define WLAN_RF_WF_DTMX_CDR_EN_RST                     0x1
/// WF_DTMX_OFFSET_BITS field reset value
#define WLAN_RF_WF_DTMX_OFFSET_BITS_RST                0x0
/// WF_DTMX_CLK_SEL_POS_EDGE field reset value
#define WLAN_RF_WF_DTMX_CLK_SEL_POS_EDGE_RST           0x1
/// WF_DTMX_CLK_PHASE_SEL_BIT field reset value
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_BIT_RST          0x4
/// WF_DTMX_CLK_IQ_DELAY_EN field reset value
#define WLAN_RF_WF_DTMX_CLK_IQ_DELAY_EN_RST            0x1
/// WF_DTMX_CLK_PATH_0__45_DELAY_EN field reset value
#define WLAN_RF_WF_DTMX_CLK_PATH_0__45_DELAY_EN_RST    0x1
/// WF_DTMX_CLK_FREQ_SEL_BIT field reset value
#define WLAN_RF_WF_DTMX_CLK_FREQ_SEL_BIT_RST           0x4
/// WF_DTMX_CLK_2DIG_DLY_BIT field reset value
#define WLAN_RF_WF_DTMX_CLK_2DIG_DLY_BIT_RST           0x0
/// WF_DTMX_DPD_CAL_EN field reset value
#define WLAN_RF_WF_DTMX_DPD_CAL_EN_RST                 0x0

/**
 * @brief Constructs a value for the REG_0A register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfdtmxloregvbit - The value to use for the wf_dtmx_lo_reg_vbit field.
 * @param[in] wfdtmxlopathphasesel - The value to use for the wf_dtmx_lo_path_phase_sel field.
 * @param[in] wfdtmxclk2cdren - The value to use for the wf_dtmx_clk2cdr_en field.
 * @param[in] wfdtmxdivrstn - The value to use for the wf_dtmx_div_rstn field.
 * @param[in] wfdtmxclk2dacseldig - The value to use for the wf_dtmx_clk2dac_sel_dig field.
 * @param[in] wfdtmxcdrdivmodebit - The value to use for the wf_dtmx_cdr_div_mode_bit field.
 * @param[in] wfdtmxcdren - The value to use for the wf_dtmx_cdr_en field.
 * @param[in] wfdtmxoffsetbits - The value to use for the wf_dtmx_offset_bits field.
 * @param[in] wfdtmxclkselposedge - The value to use for the wf_dtmx_clk_sel_pos_edge field.
 * @param[in] wfdtmxclkphaseselbit - The value to use for the wf_dtmx_clk_phase_sel_bit field.
 * @param[in] wfdtmxclkiqdelayen - The value to use for the wf_dtmx_clk_iq_delay_en field.
 * @param[in] wfdtmxclkpath045delayen - The value to use for the wf_dtmx_clk_path0_45_delay_en field.
 * @param[in] wfdtmxclkfreqselbit - The value to use for the wf_dtmx_clk_freq_sel_bit field.
 * @param[in] wfdtmxclk2digdlybit - The value to use for the wf_dtmx_clk2dig_dly_bit field.
 * @param[in] wfdtmxdpdcalen - The value to use for the wf_dtmx_dpd_cal_en field.
 */
__INLINE void wlan_rf_reg_0a_pack(uint8_t wfdtmxloregvbit, uint8_t wfdtmxlopathphasesel, uint8_t wfdtmxclk2cdren, uint8_t wfdtmxdivrstn, uint8_t wfdtmxclk2dacseldig, uint8_t wfdtmxcdrdivmodebit, uint8_t wfdtmxcdren, uint8_t wfdtmxoffsetbits, uint8_t wfdtmxclkselposedge, uint8_t wfdtmxclkphaseselbit, uint8_t wfdtmxclkiqdelayen, uint8_t wfdtmxclkpath045delayen, uint8_t wfdtmxclkfreqselbit, uint8_t wfdtmxclk2digdlybit, uint8_t wfdtmxdpdcalen)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR,  ((uint32_t)wfdtmxloregvbit << 28) | ((uint32_t)wfdtmxlopathphasesel << 26) | ((uint32_t)wfdtmxclk2cdren << 25) | ((uint32_t)wfdtmxdivrstn << 24) | ((uint32_t)wfdtmxclk2dacseldig << 23) | ((uint32_t)wfdtmxcdrdivmodebit << 21) | ((uint32_t)wfdtmxcdren << 20) | ((uint32_t)wfdtmxoffsetbits << 15) | ((uint32_t)wfdtmxclkselposedge << 14) | ((uint32_t)wfdtmxclkphaseselbit << 11) | ((uint32_t)wfdtmxclkiqdelayen << 10) | ((uint32_t)wfdtmxclkpath045delayen << 9) | ((uint32_t)wfdtmxclkfreqselbit << 6) | ((uint32_t)wfdtmxclk2digdlybit << 1) | ((uint32_t)wfdtmxdpdcalen << 0));
}

/**
 * @brief Unpacks REG_0A's fields from current value of the REG_0A register.
 *
 * Reads the REG_0A register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfdtmxloregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxlopathphasesel - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclk2cdren - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdivrstn - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclk2dacseldig - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrdivmodebit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdren - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxoffsetbits - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkselposedge - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkphaseselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkiqdelayen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkpath045delayen - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkfreqselbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclk2digdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxdpdcalen - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_0a_unpack(uint8_t* wfdtmxloregvbit, uint8_t* wfdtmxlopathphasesel, uint8_t* wfdtmxclk2cdren, uint8_t* wfdtmxdivrstn, uint8_t* wfdtmxclk2dacseldig, uint8_t* wfdtmxcdrdivmodebit, uint8_t* wfdtmxcdren, uint8_t* wfdtmxoffsetbits, uint8_t* wfdtmxclkselposedge, uint8_t* wfdtmxclkphaseselbit, uint8_t* wfdtmxclkiqdelayen, uint8_t* wfdtmxclkpath045delayen, uint8_t* wfdtmxclkfreqselbit, uint8_t* wfdtmxclk2digdlybit, uint8_t* wfdtmxdpdcalen)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);

    *wfdtmxloregvbit = (localVal & ((uint32_t)0x70000000)) >> 28;
    *wfdtmxlopathphasesel = (localVal & ((uint32_t)0x0C000000)) >> 26;
    *wfdtmxclk2cdren = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wfdtmxdivrstn = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wfdtmxclk2dacseldig = (localVal & ((uint32_t)0x00800000)) >> 23;
    *wfdtmxcdrdivmodebit = (localVal & ((uint32_t)0x00600000)) >> 21;
    *wfdtmxcdren = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wfdtmxoffsetbits = (localVal & ((uint32_t)0x000F8000)) >> 15;
    *wfdtmxclkselposedge = (localVal & ((uint32_t)0x00004000)) >> 14;
    *wfdtmxclkphaseselbit = (localVal & ((uint32_t)0x00003800)) >> 11;
    *wfdtmxclkiqdelayen = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfdtmxclkpath045delayen = (localVal & ((uint32_t)0x00000200)) >> 9;
    *wfdtmxclkfreqselbit = (localVal & ((uint32_t)0x000001C0)) >> 6;
    *wfdtmxclk2digdlybit = (localVal & ((uint32_t)0x0000003E)) >> 1;
    *wfdtmxdpdcalen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_dtmx_lo_reg_vbit field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_lo_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_lo_reg_vbit field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_lo_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

/**
 * @brief Sets the wf_dtmx_lo_reg_vbit field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxloregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_lo_reg_vbit_setf(uint8_t wfdtmxloregvbit)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x70000000)) | (((uint32_t)wfdtmxloregvbit << 28) & ((uint32_t)0x70000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_lo_path_phase_sel field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_lo_path_phase_sel field's value will be returned.
 *
 * @return The current value of the wf_dtmx_lo_path_phase_sel field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_lo_path_phase_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x0C000000)) >> 26);
}

/**
 * @brief Sets the wf_dtmx_lo_path_phase_sel field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxlopathphasesel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_lo_path_phase_sel_setf(uint8_t wfdtmxlopathphasesel)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x0C000000)) | (((uint32_t)wfdtmxlopathphasesel << 26) & ((uint32_t)0x0C000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk2cdr_en field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_clk2cdr_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk2cdr_en field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_2cdr_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_dtmx_clk2cdr_en field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclk2cdren - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_2cdr_en_setf(uint8_t wfdtmxclk2cdren)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wfdtmxclk2cdren << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_div_rstn field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_div_rstn field's value will be returned.
 *
 * @return The current value of the wf_dtmx_div_rstn field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_div_rstn_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the wf_dtmx_div_rstn field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdivrstn - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_div_rstn_setf(uint8_t wfdtmxdivrstn)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wfdtmxdivrstn << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk2dac_sel_dig field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_clk2dac_sel_dig field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk2dac_sel_dig field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_2dac_sel_dig_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

/**
 * @brief Sets the wf_dtmx_clk2dac_sel_dig field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclk2dacseldig - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_2dac_sel_dig_setf(uint8_t wfdtmxclk2dacseldig)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x00800000)) | (((uint32_t)wfdtmxclk2dacseldig << 23) & ((uint32_t)0x00800000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_div_mode_bit field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_cdr_div_mode_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_div_mode_bit field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_div_mode_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x00600000)) >> 21);
}

/**
 * @brief Sets the wf_dtmx_cdr_div_mode_bit field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdrdivmodebit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_div_mode_bit_setf(uint8_t wfdtmxcdrdivmodebit)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x00600000)) | (((uint32_t)wfdtmxcdrdivmodebit << 21) & ((uint32_t)0x00600000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_en field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_cdr_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_en field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_dtmx_cdr_en field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxcdren - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_cdr_en_setf(uint8_t wfdtmxcdren)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wfdtmxcdren << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_offset_bits field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_offset_bits field's value will be returned.
 *
 * @return The current value of the wf_dtmx_offset_bits field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_offset_bits_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x000F8000)) >> 15);
}

/**
 * @brief Sets the wf_dtmx_offset_bits field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxoffsetbits - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_offset_bits_setf(uint8_t wfdtmxoffsetbits)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x000F8000)) | (((uint32_t)wfdtmxoffsetbits << 15) & ((uint32_t)0x000F8000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_sel_pos_edge field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_clk_sel_pos_edge field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_sel_pos_edge field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_sel_pos_edge_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the wf_dtmx_clk_sel_pos_edge field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkselposedge - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_sel_pos_edge_setf(uint8_t wfdtmxclkselposedge)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)wfdtmxclkselposedge << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_phase_sel_bit field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_clk_phase_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_phase_sel_bit field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_phase_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x00003800)) >> 11);
}

/**
 * @brief Sets the wf_dtmx_clk_phase_sel_bit field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkphaseselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_phase_sel_bit_setf(uint8_t wfdtmxclkphaseselbit)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x00003800)) | (((uint32_t)wfdtmxclkphaseselbit << 11) & ((uint32_t)0x00003800)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_iq_delay_en field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_clk_iq_delay_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_iq_delay_en field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_iq_delay_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wf_dtmx_clk_iq_delay_en field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkiqdelayen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_iq_delay_en_setf(uint8_t wfdtmxclkiqdelayen)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wfdtmxclkiqdelayen << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_path0_45_delay_en field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_clk_path0_45_delay_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_path0_45_delay_en field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_path_0__45_delay_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the wf_dtmx_clk_path0_45_delay_en field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkpath045delayen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_path_0__45_delay_en_setf(uint8_t wfdtmxclkpath045delayen)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)wfdtmxclkpath045delayen << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_freq_sel_bit field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_clk_freq_sel_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_freq_sel_bit field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_freq_sel_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x000001C0)) >> 6);
}

/**
 * @brief Sets the wf_dtmx_clk_freq_sel_bit field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclkfreqselbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_freq_sel_bit_setf(uint8_t wfdtmxclkfreqselbit)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x000001C0)) | (((uint32_t)wfdtmxclkfreqselbit << 6) & ((uint32_t)0x000001C0)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk2dig_dly_bit field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_clk2dig_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk2dig_dly_bit field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_2dig_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x0000003E)) >> 1);
}

/**
 * @brief Sets the wf_dtmx_clk2dig_dly_bit field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxclk2digdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_clk_2dig_dly_bit_setf(uint8_t wfdtmxclk2digdlybit)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x0000003E)) | (((uint32_t)wfdtmxclk2digdlybit << 1) & ((uint32_t)0x0000003E)));
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_cal_en field in the REG_0A register.
 *
 * The REG_0A register will be read and the wf_dtmx_dpd_cal_en field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_cal_en field in the REG_0A register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0A_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_dtmx_dpd_cal_en field of the REG_0A register.
 *
 * The REG_0A register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdcalen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_cal_en_setf(uint8_t wfdtmxdpdcalen)
{
    REG_PL_WR(WLAN_RF_REG_0A_ADDR, (REG_PL_RD(WLAN_RF_REG_0A_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfdtmxdpdcalen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_0B register definitions
 * <table>
 * <caption id="REG_0B_BF">REG_0B bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>27:25 <td>wf_dtmx_dpd_lobias_vbit <td>R <td>R/W <td>0x4
 * <tr><td>24 <td>wf_dtmx_clk2dig_phase_lock <td>W <td>R <td>0
 * <tr><td>23:22 <td>wf_dtmx_cdr_dly_lck_bit <td>W <td>R <td>0x0
 * <tr><td>21:19 <td>wf_dtmx_clk_phase_sel_lck_bit <td>W <td>R <td>0x0
 * <tr><td>18:17 <td>   wf_dtmx_att_bit <td>W <td>R <td>0x0
 * <tr><td>16:15 <td>wf_dtmx_vbg_tc_bit <td>R <td>R/W <td>0x1
 * <tr><td>14:13 <td>  wf_dtmx_vbg_vbit <td>R <td>R/W <td>0x3
 * <tr><td>12 <td>wf_dtmx_bias_ref_sel_bg <td>R <td>R/W <td>1
 * <tr><td>11 <td>wf_iref_current_start_enb <td>R <td>R/W <td>1
 * <tr><td>10:07 <td>   wf_trx_rsvd_bit <td>R <td>R/W <td>0xC
 * <tr><td>06:05 <td>wf_rxflt_pwres_bit <td>R <td>R/W <td>0x2
 * <tr><td>04:03 <td>wf_rxflt_notch_mode <td>W <td>R <td>0x0
 * <tr><td>02 <td>  wf_rxflt_iq_swap <td>R <td>R/W <td>0
 * <tr><td>01:00 <td>  wf_rxflt_bw_mode <td>W <td>R <td>0x2
 * </table>
 *
 * @{
 */

/// Address of the REG_0B register
#define WLAN_RF_REG_0B_ADDR   0x4034402C
/// Offset of the REG_0B register from the base address
#define WLAN_RF_REG_0B_OFFSET 0x0000002C
/// Index of the REG_0B register
#define WLAN_RF_REG_0B_INDEX  0x0000000B
/// Reset value of the REG_0B register
#define WLAN_RF_REG_0B_RESET  0x0800FE42

/**
 * @brief Returns the current value of the REG_0B register.
 * The REG_0B register will be read and its value returned.
 * @return The current value of the REG_0B register.
 */
__INLINE uint32_t wlan_rf_reg_0b_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_0B_ADDR);
}

/**
 * @brief Sets the REG_0B register to a value.
 * The REG_0B register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_0b_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR, value);
}

// field definitions
/// WF_DTMX_DPD_LOBIAS_VBIT field mask
#define WLAN_RF_WF_DTMX_DPD_LOBIAS_VBIT_MASK         ((uint32_t)0x0E000000)
/// WF_DTMX_DPD_LOBIAS_VBIT field LSB position
#define WLAN_RF_WF_DTMX_DPD_LOBIAS_VBIT_LSB          25
/// WF_DTMX_DPD_LOBIAS_VBIT field width
#define WLAN_RF_WF_DTMX_DPD_LOBIAS_VBIT_WIDTH        ((uint32_t)0x00000003)
/// WF_DTMX_CLK_2DIG_PHASE_LOCK field bit
#define WLAN_RF_WF_DTMX_CLK_2DIG_PHASE_LOCK_BIT      ((uint32_t)0x01000000)
/// WF_DTMX_CLK_2DIG_PHASE_LOCK field position
#define WLAN_RF_WF_DTMX_CLK_2DIG_PHASE_LOCK_POS      24
/// WF_DTMX_CDR_DLY_LCK_BIT field mask
#define WLAN_RF_WF_DTMX_CDR_DLY_LCK_BIT_MASK         ((uint32_t)0x00C00000)
/// WF_DTMX_CDR_DLY_LCK_BIT field LSB position
#define WLAN_RF_WF_DTMX_CDR_DLY_LCK_BIT_LSB          22
/// WF_DTMX_CDR_DLY_LCK_BIT field width
#define WLAN_RF_WF_DTMX_CDR_DLY_LCK_BIT_WIDTH        ((uint32_t)0x00000002)
/// WF_DTMX_CLK_PHASE_SEL_LCK_BIT field mask
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_LCK_BIT_MASK   ((uint32_t)0x00380000)
/// WF_DTMX_CLK_PHASE_SEL_LCK_BIT field LSB position
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_LCK_BIT_LSB    19
/// WF_DTMX_CLK_PHASE_SEL_LCK_BIT field width
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_LCK_BIT_WIDTH  ((uint32_t)0x00000003)
/// WF_DTMX_ATT_BIT field mask
#define WLAN_RF_WF_DTMX_ATT_BIT_MASK                 ((uint32_t)0x00060000)
/// WF_DTMX_ATT_BIT field LSB position
#define WLAN_RF_WF_DTMX_ATT_BIT_LSB                  17
/// WF_DTMX_ATT_BIT field width
#define WLAN_RF_WF_DTMX_ATT_BIT_WIDTH                ((uint32_t)0x00000002)
/// WF_DTMX_VBG_TC_BIT field mask
#define WLAN_RF_WF_DTMX_VBG_TC_BIT_MASK              ((uint32_t)0x00018000)
/// WF_DTMX_VBG_TC_BIT field LSB position
#define WLAN_RF_WF_DTMX_VBG_TC_BIT_LSB               15
/// WF_DTMX_VBG_TC_BIT field width
#define WLAN_RF_WF_DTMX_VBG_TC_BIT_WIDTH             ((uint32_t)0x00000002)
/// WF_DTMX_VBG_VBIT field mask
#define WLAN_RF_WF_DTMX_VBG_VBIT_MASK                ((uint32_t)0x00006000)
/// WF_DTMX_VBG_VBIT field LSB position
#define WLAN_RF_WF_DTMX_VBG_VBIT_LSB                 13
/// WF_DTMX_VBG_VBIT field width
#define WLAN_RF_WF_DTMX_VBG_VBIT_WIDTH               ((uint32_t)0x00000002)
/// WF_DTMX_BIAS_REF_SEL_BG field bit
#define WLAN_RF_WF_DTMX_BIAS_REF_SEL_BG_BIT          ((uint32_t)0x00001000)
/// WF_DTMX_BIAS_REF_SEL_BG field position
#define WLAN_RF_WF_DTMX_BIAS_REF_SEL_BG_POS          12
/// WF_IREF_CURRENT_START_ENB field bit
#define WLAN_RF_WF_IREF_CURRENT_START_ENB_BIT        ((uint32_t)0x00000800)
/// WF_IREF_CURRENT_START_ENB field position
#define WLAN_RF_WF_IREF_CURRENT_START_ENB_POS        11
/// WF_TRX_RSVD_BIT field mask
#define WLAN_RF_WF_TRX_RSVD_BIT_MASK                 ((uint32_t)0x00000780)
/// WF_TRX_RSVD_BIT field LSB position
#define WLAN_RF_WF_TRX_RSVD_BIT_LSB                  7
/// WF_TRX_RSVD_BIT field width
#define WLAN_RF_WF_TRX_RSVD_BIT_WIDTH                ((uint32_t)0x00000004)
/// WF_RXFLT_PWRES_BIT field mask
#define WLAN_RF_WF_RXFLT_PWRES_BIT_MASK              ((uint32_t)0x00000060)
/// WF_RXFLT_PWRES_BIT field LSB position
#define WLAN_RF_WF_RXFLT_PWRES_BIT_LSB               5
/// WF_RXFLT_PWRES_BIT field width
#define WLAN_RF_WF_RXFLT_PWRES_BIT_WIDTH             ((uint32_t)0x00000002)
/// WF_RXFLT_NOTCH_MODE field mask
#define WLAN_RF_WF_RXFLT_NOTCH_MODE_MASK             ((uint32_t)0x00000018)
/// WF_RXFLT_NOTCH_MODE field LSB position
#define WLAN_RF_WF_RXFLT_NOTCH_MODE_LSB              3
/// WF_RXFLT_NOTCH_MODE field width
#define WLAN_RF_WF_RXFLT_NOTCH_MODE_WIDTH            ((uint32_t)0x00000002)
/// WF_RXFLT_IQ_SWAP field bit
#define WLAN_RF_WF_RXFLT_IQ_SWAP_BIT                 ((uint32_t)0x00000004)
/// WF_RXFLT_IQ_SWAP field position
#define WLAN_RF_WF_RXFLT_IQ_SWAP_POS                 2
/// WF_RXFLT_BW_MODE field mask
#define WLAN_RF_WF_RXFLT_BW_MODE_MASK                ((uint32_t)0x00000003)
/// WF_RXFLT_BW_MODE field LSB position
#define WLAN_RF_WF_RXFLT_BW_MODE_LSB                 0
/// WF_RXFLT_BW_MODE field width
#define WLAN_RF_WF_RXFLT_BW_MODE_WIDTH               ((uint32_t)0x00000002)

/// WF_DTMX_DPD_LOBIAS_VBIT field reset value
#define WLAN_RF_WF_DTMX_DPD_LOBIAS_VBIT_RST          0x4
/// WF_DTMX_CLK_2DIG_PHASE_LOCK field reset value
#define WLAN_RF_WF_DTMX_CLK_2DIG_PHASE_LOCK_RST      0x0
/// WF_DTMX_CDR_DLY_LCK_BIT field reset value
#define WLAN_RF_WF_DTMX_CDR_DLY_LCK_BIT_RST          0x0
/// WF_DTMX_CLK_PHASE_SEL_LCK_BIT field reset value
#define WLAN_RF_WF_DTMX_CLK_PHASE_SEL_LCK_BIT_RST    0x0
/// WF_DTMX_ATT_BIT field reset value
#define WLAN_RF_WF_DTMX_ATT_BIT_RST                  0x0
/// WF_DTMX_VBG_TC_BIT field reset value
#define WLAN_RF_WF_DTMX_VBG_TC_BIT_RST               0x1
/// WF_DTMX_VBG_VBIT field reset value
#define WLAN_RF_WF_DTMX_VBG_VBIT_RST                 0x3
/// WF_DTMX_BIAS_REF_SEL_BG field reset value
#define WLAN_RF_WF_DTMX_BIAS_REF_SEL_BG_RST          0x1
/// WF_IREF_CURRENT_START_ENB field reset value
#define WLAN_RF_WF_IREF_CURRENT_START_ENB_RST        0x1
/// WF_TRX_RSVD_BIT field reset value
#define WLAN_RF_WF_TRX_RSVD_BIT_RST                  0xC
/// WF_RXFLT_PWRES_BIT field reset value
#define WLAN_RF_WF_RXFLT_PWRES_BIT_RST               0x2
/// WF_RXFLT_NOTCH_MODE field reset value
#define WLAN_RF_WF_RXFLT_NOTCH_MODE_RST              0x0
/// WF_RXFLT_IQ_SWAP field reset value
#define WLAN_RF_WF_RXFLT_IQ_SWAP_RST                 0x0
/// WF_RXFLT_BW_MODE field reset value
#define WLAN_RF_WF_RXFLT_BW_MODE_RST                 0x2

/**
 * @brief Constructs a value for the REG_0B register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfdtmxdpdlobiasvbit - The value to use for the wf_dtmx_dpd_lobias_vbit field.
 * @param[in] wfdtmxvbgtcbit - The value to use for the wf_dtmx_vbg_tc_bit field.
 * @param[in] wfdtmxvbgvbit - The value to use for the wf_dtmx_vbg_vbit field.
 * @param[in] wfdtmxbiasrefselbg - The value to use for the wf_dtmx_bias_ref_sel_bg field.
 * @param[in] wfirefcurrentstartenb - The value to use for the wf_iref_current_start_enb field.
 * @param[in] wftrxrsvdbit - The value to use for the wf_trx_rsvd_bit field.
 * @param[in] wfrxfltpwresbit - The value to use for the wf_rxflt_pwres_bit field.
 * @param[in] wfrxfltiqswap - The value to use for the wf_rxflt_iq_swap field.
 */
__INLINE void wlan_rf_reg_0b_pack(uint8_t wfdtmxdpdlobiasvbit, uint8_t wfdtmxvbgtcbit, uint8_t wfdtmxvbgvbit, uint8_t wfdtmxbiasrefselbg, uint8_t wfirefcurrentstartenb, uint8_t wftrxrsvdbit, uint8_t wfrxfltpwresbit, uint8_t wfrxfltiqswap)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR,  ((uint32_t)wfdtmxdpdlobiasvbit << 25) | ((uint32_t)wfdtmxvbgtcbit << 15) | ((uint32_t)wfdtmxvbgvbit << 13) | ((uint32_t)wfdtmxbiasrefselbg << 12) | ((uint32_t)wfirefcurrentstartenb << 11) | ((uint32_t)wftrxrsvdbit << 7) | ((uint32_t)wfrxfltpwresbit << 5) | ((uint32_t)wfrxfltiqswap << 2));
}

/**
 * @brief Unpacks REG_0B's fields from current value of the REG_0B register.
 *
 * Reads the REG_0B register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfdtmxdpdlobiasvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclk2digphaselock - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxcdrdlylckbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxclkphasesellckbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxattbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxvbgtcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxvbgvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfdtmxbiasrefselbg - Will be populated with the current value of this field from the register.
 * @param[out] wfirefcurrentstartenb - Will be populated with the current value of this field from the register.
 * @param[out] wftrxrsvdbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltpwresbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltnotchmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltiqswap - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltbwmode - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_0b_unpack(uint8_t* wfdtmxdpdlobiasvbit, uint8_t* wfdtmxclk2digphaselock, uint8_t* wfdtmxcdrdlylckbit, uint8_t* wfdtmxclkphasesellckbit, uint8_t* wfdtmxattbit, uint8_t* wfdtmxvbgtcbit, uint8_t* wfdtmxvbgvbit, uint8_t* wfdtmxbiasrefselbg, uint8_t* wfirefcurrentstartenb, uint8_t* wftrxrsvdbit, uint8_t* wfrxfltpwresbit, uint8_t* wfrxfltnotchmode, uint8_t* wfrxfltiqswap, uint8_t* wfrxfltbwmode)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);

    *wfdtmxdpdlobiasvbit = (localVal & ((uint32_t)0x0E000000)) >> 25;
    *wfdtmxclk2digphaselock = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wfdtmxcdrdlylckbit = (localVal & ((uint32_t)0x00C00000)) >> 22;
    *wfdtmxclkphasesellckbit = (localVal & ((uint32_t)0x00380000)) >> 19;
    *wfdtmxattbit = (localVal & ((uint32_t)0x00060000)) >> 17;
    *wfdtmxvbgtcbit = (localVal & ((uint32_t)0x00018000)) >> 15;
    *wfdtmxvbgvbit = (localVal & ((uint32_t)0x00006000)) >> 13;
    *wfdtmxbiasrefselbg = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wfirefcurrentstartenb = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wftrxrsvdbit = (localVal & ((uint32_t)0x00000780)) >> 7;
    *wfrxfltpwresbit = (localVal & ((uint32_t)0x00000060)) >> 5;
    *wfrxfltnotchmode = (localVal & ((uint32_t)0x00000018)) >> 3;
    *wfrxfltiqswap = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wfrxfltbwmode = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_dtmx_dpd_lobias_vbit field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_dtmx_dpd_lobias_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_dpd_lobias_vbit field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_dpd_lobias_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x0E000000)) >> 25);
}

/**
 * @brief Sets the wf_dtmx_dpd_lobias_vbit field of the REG_0B register.
 *
 * The REG_0B register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxdpdlobiasvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_dpd_lobias_vbit_setf(uint8_t wfdtmxdpdlobiasvbit)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR, (REG_PL_RD(WLAN_RF_REG_0B_ADDR) & ~((uint32_t)0x0E000000)) | (((uint32_t)wfdtmxdpdlobiasvbit << 25) & ((uint32_t)0x0E000000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_clk2dig_phase_lock field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_dtmx_clk2dig_phase_lock field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk2dig_phase_lock field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_2dig_phase_lock_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Returns the current value of the wf_dtmx_cdr_dly_lck_bit field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_dtmx_cdr_dly_lck_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_cdr_dly_lck_bit field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_cdr_dly_lck_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00C00000)) >> 22);
}

/**
 * @brief Returns the current value of the wf_dtmx_clk_phase_sel_lck_bit field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_dtmx_clk_phase_sel_lck_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_clk_phase_sel_lck_bit field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_clk_phase_sel_lck_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00380000)) >> 19);
}

/**
 * @brief Returns the current value of the wf_dtmx_att_bit field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_dtmx_att_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_att_bit field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_att_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00060000)) >> 17);
}

/**
 * @brief Returns the current value of the wf_dtmx_vbg_tc_bit field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_dtmx_vbg_tc_bit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_vbg_tc_bit field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_vbg_tc_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00018000)) >> 15);
}

/**
 * @brief Sets the wf_dtmx_vbg_tc_bit field of the REG_0B register.
 *
 * The REG_0B register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxvbgtcbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_vbg_tc_bit_setf(uint8_t wfdtmxvbgtcbit)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR, (REG_PL_RD(WLAN_RF_REG_0B_ADDR) & ~((uint32_t)0x00018000)) | (((uint32_t)wfdtmxvbgtcbit << 15) & ((uint32_t)0x00018000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_vbg_vbit field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_dtmx_vbg_vbit field's value will be returned.
 *
 * @return The current value of the wf_dtmx_vbg_vbit field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_vbg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00006000)) >> 13);
}

/**
 * @brief Sets the wf_dtmx_vbg_vbit field of the REG_0B register.
 *
 * The REG_0B register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxvbgvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_vbg_vbit_setf(uint8_t wfdtmxvbgvbit)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR, (REG_PL_RD(WLAN_RF_REG_0B_ADDR) & ~((uint32_t)0x00006000)) | (((uint32_t)wfdtmxvbgvbit << 13) & ((uint32_t)0x00006000)));
}

/**
 * @brief Returns the current value of the wf_dtmx_bias_ref_sel_bg field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_dtmx_bias_ref_sel_bg field's value will be returned.
 *
 * @return The current value of the wf_dtmx_bias_ref_sel_bg field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_dtmx_bias_ref_sel_bg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_dtmx_bias_ref_sel_bg field of the REG_0B register.
 *
 * The REG_0B register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfdtmxbiasrefselbg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_dtmx_bias_ref_sel_bg_setf(uint8_t wfdtmxbiasrefselbg)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR, (REG_PL_RD(WLAN_RF_REG_0B_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)wfdtmxbiasrefselbg << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the wf_iref_current_start_enb field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_iref_current_start_enb field's value will be returned.
 *
 * @return The current value of the wf_iref_current_start_enb field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_iref_current_start_enb_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the wf_iref_current_start_enb field of the REG_0B register.
 *
 * The REG_0B register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfirefcurrentstartenb - The value to set the field to.
 */
__INLINE void wlan_rf_wf_iref_current_start_enb_setf(uint8_t wfirefcurrentstartenb)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR, (REG_PL_RD(WLAN_RF_REG_0B_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)wfirefcurrentstartenb << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wf_trx_rsvd_bit field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_trx_rsvd_bit field's value will be returned.
 *
 * @return The current value of the wf_trx_rsvd_bit field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_trx_rsvd_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00000780)) >> 7);
}

/**
 * @brief Sets the wf_trx_rsvd_bit field of the REG_0B register.
 *
 * The REG_0B register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftrxrsvdbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_trx_rsvd_bit_setf(uint8_t wftrxrsvdbit)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR, (REG_PL_RD(WLAN_RF_REG_0B_ADDR) & ~((uint32_t)0x00000780)) | (((uint32_t)wftrxrsvdbit << 7) & ((uint32_t)0x00000780)));
}

/**
 * @brief Returns the current value of the wf_rxflt_pwres_bit field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_rxflt_pwres_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_pwres_bit field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_pwres_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00000060)) >> 5);
}

/**
 * @brief Sets the wf_rxflt_pwres_bit field of the REG_0B register.
 *
 * The REG_0B register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltpwresbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_pwres_bit_setf(uint8_t wfrxfltpwresbit)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR, (REG_PL_RD(WLAN_RF_REG_0B_ADDR) & ~((uint32_t)0x00000060)) | (((uint32_t)wfrxfltpwresbit << 5) & ((uint32_t)0x00000060)));
}

/**
 * @brief Returns the current value of the wf_rxflt_notch_mode field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_rxflt_notch_mode field's value will be returned.
 *
 * @return The current value of the wf_rxflt_notch_mode field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_notch_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00000018)) >> 3);
}

/**
 * @brief Returns the current value of the wf_rxflt_iq_swap field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_rxflt_iq_swap field's value will be returned.
 *
 * @return The current value of the wf_rxflt_iq_swap field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_iq_swap_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wf_rxflt_iq_swap field of the REG_0B register.
 *
 * The REG_0B register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltiqswap - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_iq_swap_setf(uint8_t wfrxfltiqswap)
{
    REG_PL_WR(WLAN_RF_REG_0B_ADDR, (REG_PL_RD(WLAN_RF_REG_0B_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wfrxfltiqswap << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wf_rxflt_bw_mode field in the REG_0B register.
 *
 * The REG_0B register will be read and the wf_rxflt_bw_mode field's value will be returned.
 *
 * @return The current value of the wf_rxflt_bw_mode field in the REG_0B register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_bw_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0B_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/// @}

/**
 * @name REG_0C register definitions
 * <table>
 * <caption id="REG_0C_BF">REG_0C bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:27 <td>  wf_rxflt_bw_cbit <td>W <td>R <td>0xC
 * <tr><td>26:24 <td>    wf_rxflt_gbit1 <td>W <td>R <td>0x0
 * <tr><td>23:22 <td>    wf_rxflt_gbit2 <td>W <td>R <td>0x0
 * <tr><td>21:19 <td>  wf_rxflt_vcm_bit <td>R <td>R/W <td>0x5
 * <tr><td>18:13 <td>  wf_rxflt_op_ibit <td>W <td>R <td>0x20
 * <tr><td>12:09 <td>wf_rxflt_op_cm_bit <td>W <td>R <td>0x4
 * <tr><td>08:05 <td>wf_rxflt_op_rm_bit <td>W <td>R <td>0x6
 * <tr><td>04:01 <td>wf_rxflt_op_rq_bit <td>W <td>R <td>0x6
 * <tr><td>00 <td>    wf_adc_en_core <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_0C register
#define WLAN_RF_REG_0C_ADDR   0x40344030
/// Offset of the REG_0C register from the base address
#define WLAN_RF_REG_0C_OFFSET 0x00000030
/// Index of the REG_0C register
#define WLAN_RF_REG_0C_INDEX  0x0000000C
/// Reset value of the REG_0C register
#define WLAN_RF_REG_0C_RESET  0x602C08CC

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
/// WF_RXFLT_BW_CBIT field mask
#define WLAN_RF_WF_RXFLT_BW_CBIT_MASK     ((uint32_t)0xF8000000)
/// WF_RXFLT_BW_CBIT field LSB position
#define WLAN_RF_WF_RXFLT_BW_CBIT_LSB      27
/// WF_RXFLT_BW_CBIT field width
#define WLAN_RF_WF_RXFLT_BW_CBIT_WIDTH    ((uint32_t)0x00000005)
/// WF_RXFLT_GBIT_1 field mask
#define WLAN_RF_WF_RXFLT_GBIT_1_MASK      ((uint32_t)0x07000000)
/// WF_RXFLT_GBIT_1 field LSB position
#define WLAN_RF_WF_RXFLT_GBIT_1_LSB       24
/// WF_RXFLT_GBIT_1 field width
#define WLAN_RF_WF_RXFLT_GBIT_1_WIDTH     ((uint32_t)0x00000003)
/// WF_RXFLT_GBIT_2 field mask
#define WLAN_RF_WF_RXFLT_GBIT_2_MASK      ((uint32_t)0x00C00000)
/// WF_RXFLT_GBIT_2 field LSB position
#define WLAN_RF_WF_RXFLT_GBIT_2_LSB       22
/// WF_RXFLT_GBIT_2 field width
#define WLAN_RF_WF_RXFLT_GBIT_2_WIDTH     ((uint32_t)0x00000002)
/// WF_RXFLT_VCM_BIT field mask
#define WLAN_RF_WF_RXFLT_VCM_BIT_MASK     ((uint32_t)0x00380000)
/// WF_RXFLT_VCM_BIT field LSB position
#define WLAN_RF_WF_RXFLT_VCM_BIT_LSB      19
/// WF_RXFLT_VCM_BIT field width
#define WLAN_RF_WF_RXFLT_VCM_BIT_WIDTH    ((uint32_t)0x00000003)
/// WF_RXFLT_OP_IBIT field mask
#define WLAN_RF_WF_RXFLT_OP_IBIT_MASK     ((uint32_t)0x0007E000)
/// WF_RXFLT_OP_IBIT field LSB position
#define WLAN_RF_WF_RXFLT_OP_IBIT_LSB      13
/// WF_RXFLT_OP_IBIT field width
#define WLAN_RF_WF_RXFLT_OP_IBIT_WIDTH    ((uint32_t)0x00000006)
/// WF_RXFLT_OP_CM_BIT field mask
#define WLAN_RF_WF_RXFLT_OP_CM_BIT_MASK   ((uint32_t)0x00001E00)
/// WF_RXFLT_OP_CM_BIT field LSB position
#define WLAN_RF_WF_RXFLT_OP_CM_BIT_LSB    9
/// WF_RXFLT_OP_CM_BIT field width
#define WLAN_RF_WF_RXFLT_OP_CM_BIT_WIDTH  ((uint32_t)0x00000004)
/// WF_RXFLT_OP_RM_BIT field mask
#define WLAN_RF_WF_RXFLT_OP_RM_BIT_MASK   ((uint32_t)0x000001E0)
/// WF_RXFLT_OP_RM_BIT field LSB position
#define WLAN_RF_WF_RXFLT_OP_RM_BIT_LSB    5
/// WF_RXFLT_OP_RM_BIT field width
#define WLAN_RF_WF_RXFLT_OP_RM_BIT_WIDTH  ((uint32_t)0x00000004)
/// WF_RXFLT_OP_RQ_BIT field mask
#define WLAN_RF_WF_RXFLT_OP_RQ_BIT_MASK   ((uint32_t)0x0000001E)
/// WF_RXFLT_OP_RQ_BIT field LSB position
#define WLAN_RF_WF_RXFLT_OP_RQ_BIT_LSB    1
/// WF_RXFLT_OP_RQ_BIT field width
#define WLAN_RF_WF_RXFLT_OP_RQ_BIT_WIDTH  ((uint32_t)0x00000004)
/// WF_ADC_EN_CORE field bit
#define WLAN_RF_WF_ADC_EN_CORE_BIT        ((uint32_t)0x00000001)
/// WF_ADC_EN_CORE field position
#define WLAN_RF_WF_ADC_EN_CORE_POS        0

/// WF_RXFLT_BW_CBIT field reset value
#define WLAN_RF_WF_RXFLT_BW_CBIT_RST      0xC
/// WF_RXFLT_GBIT_1 field reset value
#define WLAN_RF_WF_RXFLT_GBIT_1_RST       0x0
/// WF_RXFLT_GBIT_2 field reset value
#define WLAN_RF_WF_RXFLT_GBIT_2_RST       0x0
/// WF_RXFLT_VCM_BIT field reset value
#define WLAN_RF_WF_RXFLT_VCM_BIT_RST      0x5
/// WF_RXFLT_OP_IBIT field reset value
#define WLAN_RF_WF_RXFLT_OP_IBIT_RST      0x20
/// WF_RXFLT_OP_CM_BIT field reset value
#define WLAN_RF_WF_RXFLT_OP_CM_BIT_RST    0x4
/// WF_RXFLT_OP_RM_BIT field reset value
#define WLAN_RF_WF_RXFLT_OP_RM_BIT_RST    0x6
/// WF_RXFLT_OP_RQ_BIT field reset value
#define WLAN_RF_WF_RXFLT_OP_RQ_BIT_RST    0x6
/// WF_ADC_EN_CORE field reset value
#define WLAN_RF_WF_ADC_EN_CORE_RST        0x0

/**
 * @brief Constructs a value for the REG_0C register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrxfltvcmbit - The value to use for the wf_rxflt_vcm_bit field.
 * @param[in] wfadcencore - The value to use for the wf_adc_en_core field.
 */
__INLINE void wlan_rf_reg_0c_pack(uint8_t wfrxfltvcmbit, uint8_t wfadcencore)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR,  ((uint32_t)wfrxfltvcmbit << 19) | ((uint32_t)wfadcencore << 0));
}

/**
 * @brief Unpacks REG_0C's fields from current value of the REG_0C register.
 *
 * Reads the REG_0C register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrxfltbwcbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltgbit1 - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltgbit2 - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltvcmbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltopibit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltopcmbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltoprmbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxfltoprqbit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcencore - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_0c_unpack(uint8_t* wfrxfltbwcbit, uint8_t* wfrxfltgbit1, uint8_t* wfrxfltgbit2, uint8_t* wfrxfltvcmbit, uint8_t* wfrxfltopibit, uint8_t* wfrxfltopcmbit, uint8_t* wfrxfltoprmbit, uint8_t* wfrxfltoprqbit, uint8_t* wfadcencore)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);

    *wfrxfltbwcbit = (localVal & ((uint32_t)0xF8000000)) >> 27;
    *wfrxfltgbit1 = (localVal & ((uint32_t)0x07000000)) >> 24;
    *wfrxfltgbit2 = (localVal & ((uint32_t)0x00C00000)) >> 22;
    *wfrxfltvcmbit = (localVal & ((uint32_t)0x00380000)) >> 19;
    *wfrxfltopibit = (localVal & ((uint32_t)0x0007E000)) >> 13;
    *wfrxfltopcmbit = (localVal & ((uint32_t)0x00001E00)) >> 9;
    *wfrxfltoprmbit = (localVal & ((uint32_t)0x000001E0)) >> 5;
    *wfrxfltoprqbit = (localVal & ((uint32_t)0x0000001E)) >> 1;
    *wfadcencore = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rxflt_bw_cbit field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxflt_bw_cbit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_bw_cbit field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_bw_cbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0xF8000000)) >> 27);
}

/**
 * @brief Returns the current value of the wf_rxflt_gbit1 field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxflt_gbit1 field's value will be returned.
 *
 * @return The current value of the wf_rxflt_gbit1 field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_gbit_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

/**
 * @brief Returns the current value of the wf_rxflt_gbit2 field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxflt_gbit2 field's value will be returned.
 *
 * @return The current value of the wf_rxflt_gbit2 field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_gbit_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00C00000)) >> 22);
}

/**
 * @brief Returns the current value of the wf_rxflt_vcm_bit field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxflt_vcm_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_vcm_bit field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_vcm_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00380000)) >> 19);
}

/**
 * @brief Sets the wf_rxflt_vcm_bit field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxfltvcmbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rxflt_vcm_bit_setf(uint8_t wfrxfltvcmbit)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00380000)) | (((uint32_t)wfrxfltvcmbit << 19) & ((uint32_t)0x00380000)));
}

/**
 * @brief Returns the current value of the wf_rxflt_op_ibit field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxflt_op_ibit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_op_ibit field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_op_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x0007E000)) >> 13);
}

/**
 * @brief Returns the current value of the wf_rxflt_op_cm_bit field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxflt_op_cm_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_op_cm_bit field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_op_cm_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00001E00)) >> 9);
}

/**
 * @brief Returns the current value of the wf_rxflt_op_rm_bit field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxflt_op_rm_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_op_rm_bit field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_op_rm_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x000001E0)) >> 5);
}

/**
 * @brief Returns the current value of the wf_rxflt_op_rq_bit field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_rxflt_op_rq_bit field's value will be returned.
 *
 * @return The current value of the wf_rxflt_op_rq_bit field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_rxflt_op_rq_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x0000001E)) >> 1);
}

/**
 * @brief Returns the current value of the wf_adc_en_core field in the REG_0C register.
 *
 * The REG_0C register will be read and the wf_adc_en_core field's value will be returned.
 *
 * @return The current value of the wf_adc_en_core field in the REG_0C register.
 */
__INLINE uint8_t wlan_rf_wf_adc_en_core_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0C_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_adc_en_core field of the REG_0C register.
 *
 * The REG_0C register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcencore - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_en_core_setf(uint8_t wfadcencore)
{
    REG_PL_WR(WLAN_RF_REG_0C_ADDR, (REG_PL_RD(WLAN_RF_REG_0C_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfadcencore << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_0D register definitions
 * <table>
 * <caption id="REG_0D_BF">REG_0D bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:30 <td>    wf_adc_clk_sel <td>R <td>R/W <td>0x0
 * <tr><td>29:26 <td>   wf_adc_cmp_ibit <td>R <td>R/W <td>0x4
 * <tr><td>25 <td>   wf_adc_clk_edge <td>R <td>R/W <td>0
 * <tr><td>24:21 <td>    wf_adc_dly_bit <td>R <td>R/W <td>0x1
 * <tr><td>20:18 <td>  wf_adc_vreg_vbit <td>R <td>R/W <td>0x3
 * <tr><td>17:14 <td>  wf_adc_vreg_ibit <td>R <td>R/W <td>0x3
 * <tr><td>13:11 <td>   wf_adc_vcm_vbit <td>R <td>R/W <td>0x2
 * <tr><td>10:06 <td>  wf_adc_vref_ibit <td>R <td>R/W <td>0x3
 * <tr><td>05:01 <td>  wf_adc_vref_vbit <td>R <td>R/W <td>0x3
 * <tr><td>00 <td>wf_adc_dac_lp_mode <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_0D register
#define WLAN_RF_REG_0D_ADDR   0x40344034
/// Offset of the REG_0D register from the base address
#define WLAN_RF_REG_0D_OFFSET 0x00000034
/// Index of the REG_0D register
#define WLAN_RF_REG_0D_INDEX  0x0000000D
/// Reset value of the REG_0D register
#define WLAN_RF_REG_0D_RESET  0x102CD0C6

/**
 * @brief Returns the current value of the REG_0D register.
 * The REG_0D register will be read and its value returned.
 * @return The current value of the REG_0D register.
 */
__INLINE uint32_t wlan_rf_reg_0d_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_0D_ADDR);
}

/**
 * @brief Sets the REG_0D register to a value.
 * The REG_0D register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_0d_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, value);
}

// field definitions
/// WF_ADC_CLK_SEL field mask
#define WLAN_RF_WF_ADC_CLK_SEL_MASK       ((uint32_t)0xC0000000)
/// WF_ADC_CLK_SEL field LSB position
#define WLAN_RF_WF_ADC_CLK_SEL_LSB        30
/// WF_ADC_CLK_SEL field width
#define WLAN_RF_WF_ADC_CLK_SEL_WIDTH      ((uint32_t)0x00000002)
/// WF_ADC_CMP_IBIT field mask
#define WLAN_RF_WF_ADC_CMP_IBIT_MASK      ((uint32_t)0x3C000000)
/// WF_ADC_CMP_IBIT field LSB position
#define WLAN_RF_WF_ADC_CMP_IBIT_LSB       26
/// WF_ADC_CMP_IBIT field width
#define WLAN_RF_WF_ADC_CMP_IBIT_WIDTH     ((uint32_t)0x00000004)
/// WF_ADC_CLK_EDGE field bit
#define WLAN_RF_WF_ADC_CLK_EDGE_BIT       ((uint32_t)0x02000000)
/// WF_ADC_CLK_EDGE field position
#define WLAN_RF_WF_ADC_CLK_EDGE_POS       25
/// WF_ADC_DLY_BIT field mask
#define WLAN_RF_WF_ADC_DLY_BIT_MASK       ((uint32_t)0x01E00000)
/// WF_ADC_DLY_BIT field LSB position
#define WLAN_RF_WF_ADC_DLY_BIT_LSB        21
/// WF_ADC_DLY_BIT field width
#define WLAN_RF_WF_ADC_DLY_BIT_WIDTH      ((uint32_t)0x00000004)
/// WF_ADC_VREG_VBIT field mask
#define WLAN_RF_WF_ADC_VREG_VBIT_MASK     ((uint32_t)0x001C0000)
/// WF_ADC_VREG_VBIT field LSB position
#define WLAN_RF_WF_ADC_VREG_VBIT_LSB      18
/// WF_ADC_VREG_VBIT field width
#define WLAN_RF_WF_ADC_VREG_VBIT_WIDTH    ((uint32_t)0x00000003)
/// WF_ADC_VREG_IBIT field mask
#define WLAN_RF_WF_ADC_VREG_IBIT_MASK     ((uint32_t)0x0003C000)
/// WF_ADC_VREG_IBIT field LSB position
#define WLAN_RF_WF_ADC_VREG_IBIT_LSB      14
/// WF_ADC_VREG_IBIT field width
#define WLAN_RF_WF_ADC_VREG_IBIT_WIDTH    ((uint32_t)0x00000004)
/// WF_ADC_VCM_VBIT field mask
#define WLAN_RF_WF_ADC_VCM_VBIT_MASK      ((uint32_t)0x00003800)
/// WF_ADC_VCM_VBIT field LSB position
#define WLAN_RF_WF_ADC_VCM_VBIT_LSB       11
/// WF_ADC_VCM_VBIT field width
#define WLAN_RF_WF_ADC_VCM_VBIT_WIDTH     ((uint32_t)0x00000003)
/// WF_ADC_VREF_IBIT field mask
#define WLAN_RF_WF_ADC_VREF_IBIT_MASK     ((uint32_t)0x000007C0)
/// WF_ADC_VREF_IBIT field LSB position
#define WLAN_RF_WF_ADC_VREF_IBIT_LSB      6
/// WF_ADC_VREF_IBIT field width
#define WLAN_RF_WF_ADC_VREF_IBIT_WIDTH    ((uint32_t)0x00000005)
/// WF_ADC_VREF_VBIT field mask
#define WLAN_RF_WF_ADC_VREF_VBIT_MASK     ((uint32_t)0x0000003E)
/// WF_ADC_VREF_VBIT field LSB position
#define WLAN_RF_WF_ADC_VREF_VBIT_LSB      1
/// WF_ADC_VREF_VBIT field width
#define WLAN_RF_WF_ADC_VREF_VBIT_WIDTH    ((uint32_t)0x00000005)
/// WF_ADC_DAC_LP_MODE field bit
#define WLAN_RF_WF_ADC_DAC_LP_MODE_BIT    ((uint32_t)0x00000001)
/// WF_ADC_DAC_LP_MODE field position
#define WLAN_RF_WF_ADC_DAC_LP_MODE_POS    0

/// WF_ADC_CLK_SEL field reset value
#define WLAN_RF_WF_ADC_CLK_SEL_RST        0x0
/// WF_ADC_CMP_IBIT field reset value
#define WLAN_RF_WF_ADC_CMP_IBIT_RST       0x4
/// WF_ADC_CLK_EDGE field reset value
#define WLAN_RF_WF_ADC_CLK_EDGE_RST       0x0
/// WF_ADC_DLY_BIT field reset value
#define WLAN_RF_WF_ADC_DLY_BIT_RST        0x1
/// WF_ADC_VREG_VBIT field reset value
#define WLAN_RF_WF_ADC_VREG_VBIT_RST      0x3
/// WF_ADC_VREG_IBIT field reset value
#define WLAN_RF_WF_ADC_VREG_IBIT_RST      0x3
/// WF_ADC_VCM_VBIT field reset value
#define WLAN_RF_WF_ADC_VCM_VBIT_RST       0x2
/// WF_ADC_VREF_IBIT field reset value
#define WLAN_RF_WF_ADC_VREF_IBIT_RST      0x3
/// WF_ADC_VREF_VBIT field reset value
#define WLAN_RF_WF_ADC_VREF_VBIT_RST      0x3
/// WF_ADC_DAC_LP_MODE field reset value
#define WLAN_RF_WF_ADC_DAC_LP_MODE_RST    0x0

/**
 * @brief Constructs a value for the REG_0D register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfadcclksel - The value to use for the wf_adc_clk_sel field.
 * @param[in] wfadccmpibit - The value to use for the wf_adc_cmp_ibit field.
 * @param[in] wfadcclkedge - The value to use for the wf_adc_clk_edge field.
 * @param[in] wfadcdlybit - The value to use for the wf_adc_dly_bit field.
 * @param[in] wfadcvregvbit - The value to use for the wf_adc_vreg_vbit field.
 * @param[in] wfadcvregibit - The value to use for the wf_adc_vreg_ibit field.
 * @param[in] wfadcvcmvbit - The value to use for the wf_adc_vcm_vbit field.
 * @param[in] wfadcvrefibit - The value to use for the wf_adc_vref_ibit field.
 * @param[in] wfadcvrefvbit - The value to use for the wf_adc_vref_vbit field.
 * @param[in] wfadcdaclpmode - The value to use for the wf_adc_dac_lp_mode field.
 */
__INLINE void wlan_rf_reg_0d_pack(uint8_t wfadcclksel, uint8_t wfadccmpibit, uint8_t wfadcclkedge, uint8_t wfadcdlybit, uint8_t wfadcvregvbit, uint8_t wfadcvregibit, uint8_t wfadcvcmvbit, uint8_t wfadcvrefibit, uint8_t wfadcvrefvbit, uint8_t wfadcdaclpmode)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR,  ((uint32_t)wfadcclksel << 30) | ((uint32_t)wfadccmpibit << 26) | ((uint32_t)wfadcclkedge << 25) | ((uint32_t)wfadcdlybit << 21) | ((uint32_t)wfadcvregvbit << 18) | ((uint32_t)wfadcvregibit << 14) | ((uint32_t)wfadcvcmvbit << 11) | ((uint32_t)wfadcvrefibit << 6) | ((uint32_t)wfadcvrefvbit << 1) | ((uint32_t)wfadcdaclpmode << 0));
}

/**
 * @brief Unpacks REG_0D's fields from current value of the REG_0D register.
 *
 * Reads the REG_0D register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfadcclksel - Will be populated with the current value of this field from the register.
 * @param[out] wfadccmpibit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcclkedge - Will be populated with the current value of this field from the register.
 * @param[out] wfadcdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcvregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcvregibit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcvcmvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcvrefibit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcvrefvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfadcdaclpmode - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_0d_unpack(uint8_t* wfadcclksel, uint8_t* wfadccmpibit, uint8_t* wfadcclkedge, uint8_t* wfadcdlybit, uint8_t* wfadcvregvbit, uint8_t* wfadcvregibit, uint8_t* wfadcvcmvbit, uint8_t* wfadcvrefibit, uint8_t* wfadcvrefvbit, uint8_t* wfadcdaclpmode)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);

    *wfadcclksel = (localVal & ((uint32_t)0xC0000000)) >> 30;
    *wfadccmpibit = (localVal & ((uint32_t)0x3C000000)) >> 26;
    *wfadcclkedge = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wfadcdlybit = (localVal & ((uint32_t)0x01E00000)) >> 21;
    *wfadcvregvbit = (localVal & ((uint32_t)0x001C0000)) >> 18;
    *wfadcvregibit = (localVal & ((uint32_t)0x0003C000)) >> 14;
    *wfadcvcmvbit = (localVal & ((uint32_t)0x00003800)) >> 11;
    *wfadcvrefibit = (localVal & ((uint32_t)0x000007C0)) >> 6;
    *wfadcvrefvbit = (localVal & ((uint32_t)0x0000003E)) >> 1;
    *wfadcdaclpmode = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_adc_clk_sel field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_clk_sel field's value will be returned.
 *
 * @return The current value of the wf_adc_clk_sel field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0xC0000000)) >> 30);
}

/**
 * @brief Sets the wf_adc_clk_sel field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcclksel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_clk_sel_setf(uint8_t wfadcclksel)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0xC0000000)) | (((uint32_t)wfadcclksel << 30) & ((uint32_t)0xC0000000)));
}

/**
 * @brief Returns the current value of the wf_adc_cmp_ibit field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_cmp_ibit field's value will be returned.
 *
 * @return The current value of the wf_adc_cmp_ibit field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_cmp_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0x3C000000)) >> 26);
}

/**
 * @brief Sets the wf_adc_cmp_ibit field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadccmpibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_cmp_ibit_setf(uint8_t wfadccmpibit)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0x3C000000)) | (((uint32_t)wfadccmpibit << 26) & ((uint32_t)0x3C000000)));
}

/**
 * @brief Returns the current value of the wf_adc_clk_edge field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_clk_edge field's value will be returned.
 *
 * @return The current value of the wf_adc_clk_edge field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_clk_edge_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_adc_clk_edge field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcclkedge - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_clk_edge_setf(uint8_t wfadcclkedge)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wfadcclkedge << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_adc_dly_bit field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_adc_dly_bit field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0x01E00000)) >> 21);
}

/**
 * @brief Sets the wf_adc_dly_bit field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_dly_bit_setf(uint8_t wfadcdlybit)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0x01E00000)) | (((uint32_t)wfadcdlybit << 21) & ((uint32_t)0x01E00000)));
}

/**
 * @brief Returns the current value of the wf_adc_vreg_vbit field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_vreg_vbit field's value will be returned.
 *
 * @return The current value of the wf_adc_vreg_vbit field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_vreg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0x001C0000)) >> 18);
}

/**
 * @brief Sets the wf_adc_vreg_vbit field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcvregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_vreg_vbit_setf(uint8_t wfadcvregvbit)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0x001C0000)) | (((uint32_t)wfadcvregvbit << 18) & ((uint32_t)0x001C0000)));
}

/**
 * @brief Returns the current value of the wf_adc_vreg_ibit field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_vreg_ibit field's value will be returned.
 *
 * @return The current value of the wf_adc_vreg_ibit field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_vreg_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0x0003C000)) >> 14);
}

/**
 * @brief Sets the wf_adc_vreg_ibit field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcvregibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_vreg_ibit_setf(uint8_t wfadcvregibit)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0x0003C000)) | (((uint32_t)wfadcvregibit << 14) & ((uint32_t)0x0003C000)));
}

/**
 * @brief Returns the current value of the wf_adc_vcm_vbit field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_vcm_vbit field's value will be returned.
 *
 * @return The current value of the wf_adc_vcm_vbit field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_vcm_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0x00003800)) >> 11);
}

/**
 * @brief Sets the wf_adc_vcm_vbit field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcvcmvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_vcm_vbit_setf(uint8_t wfadcvcmvbit)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0x00003800)) | (((uint32_t)wfadcvcmvbit << 11) & ((uint32_t)0x00003800)));
}

/**
 * @brief Returns the current value of the wf_adc_vref_ibit field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_vref_ibit field's value will be returned.
 *
 * @return The current value of the wf_adc_vref_ibit field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_vref_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0x000007C0)) >> 6);
}

/**
 * @brief Sets the wf_adc_vref_ibit field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcvrefibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_vref_ibit_setf(uint8_t wfadcvrefibit)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0x000007C0)) | (((uint32_t)wfadcvrefibit << 6) & ((uint32_t)0x000007C0)));
}

/**
 * @brief Returns the current value of the wf_adc_vref_vbit field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_vref_vbit field's value will be returned.
 *
 * @return The current value of the wf_adc_vref_vbit field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_vref_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0x0000003E)) >> 1);
}

/**
 * @brief Sets the wf_adc_vref_vbit field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcvrefvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_vref_vbit_setf(uint8_t wfadcvrefvbit)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0x0000003E)) | (((uint32_t)wfadcvrefvbit << 1) & ((uint32_t)0x0000003E)));
}

/**
 * @brief Returns the current value of the wf_adc_dac_lp_mode field in the REG_0D register.
 *
 * The REG_0D register will be read and the wf_adc_dac_lp_mode field's value will be returned.
 *
 * @return The current value of the wf_adc_dac_lp_mode field in the REG_0D register.
 */
__INLINE uint8_t wlan_rf_wf_adc_dac_lp_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0D_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_adc_dac_lp_mode field of the REG_0D register.
 *
 * The REG_0D register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfadcdaclpmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_adc_dac_lp_mode_setf(uint8_t wfadcdaclpmode)
{
    REG_PL_WR(WLAN_RF_REG_0D_ADDR, (REG_PL_RD(WLAN_RF_REG_0D_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfadcdaclpmode << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_0E register definitions
 * <table>
 * <caption id="REG_0E_BF">REG_0E bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:26 <td>  wf_pdadc_dly_bit <td>R <td>R/W <td>0x2
 * <tr><td>25 <td>wf_pdadc_clk_edge_sel <td>R <td>R/W <td>0
 * <tr><td>24 <td>wf_ts_hub_chopper_fq <td>R <td>R/W <td>0
 * <tr><td>23:20 <td>wf_ts_hub_channel_sel <td>R <td>R/W <td>0x1
 * <tr><td>19:18 <td>wf_ts_hub_vptat_vbit <td>R <td>R/W <td>0x2
 * <tr><td>17:16 <td>wf_ts_hub_vref_vbit <td>R <td>R/W <td>0x2
 * <tr><td>15:13 <td>  wf_rx_iq2gpio_en <td>R <td>R/W <td>0x0
 * <tr><td>12:09 <td>   wf_abb_rsvd_bit <td>R <td>R/W <td>0xC
 * <tr><td>08 <td>wf_rfpll_enable_loop <td>R <td>R/W <td>1
 * <tr><td>07 <td>wf_rfpll_enable_presc <td>R <td>R/W <td>1
 * <tr><td>06 <td>wf_rfpll_enable_dpll_mode <td>R <td>R/W <td>0
 * <tr><td>05:02 <td>wf_rfpll_pll_reg_vbit <td>R <td>R/W <td>0x8
 * <tr><td>01:00 <td> wf_rfpll_ldo_vbit <td>R <td>R/W <td>0x2
 * </table>
 *
 * @{
 */

/// Address of the REG_0E register
#define WLAN_RF_REG_0E_ADDR   0x40344038
/// Offset of the REG_0E register from the base address
#define WLAN_RF_REG_0E_OFFSET 0x00000038
/// Index of the REG_0E register
#define WLAN_RF_REG_0E_INDEX  0x0000000E
/// Reset value of the REG_0E register
#define WLAN_RF_REG_0E_RESET  0x081A19A2

/**
 * @brief Returns the current value of the REG_0E register.
 * The REG_0E register will be read and its value returned.
 * @return The current value of the REG_0E register.
 */
__INLINE uint32_t wlan_rf_reg_0e_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_0E_ADDR);
}

/**
 * @brief Sets the REG_0E register to a value.
 * The REG_0E register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_0e_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, value);
}

// field definitions
/// WF_PDADC_DLY_BIT field mask
#define WLAN_RF_WF_PDADC_DLY_BIT_MASK            ((uint32_t)0x3C000000)
/// WF_PDADC_DLY_BIT field LSB position
#define WLAN_RF_WF_PDADC_DLY_BIT_LSB             26
/// WF_PDADC_DLY_BIT field width
#define WLAN_RF_WF_PDADC_DLY_BIT_WIDTH           ((uint32_t)0x00000004)
/// WF_PDADC_CLK_EDGE_SEL field bit
#define WLAN_RF_WF_PDADC_CLK_EDGE_SEL_BIT        ((uint32_t)0x02000000)
/// WF_PDADC_CLK_EDGE_SEL field position
#define WLAN_RF_WF_PDADC_CLK_EDGE_SEL_POS        25
/// WF_TS_HUB_CHOPPER_FQ field bit
#define WLAN_RF_WF_TS_HUB_CHOPPER_FQ_BIT         ((uint32_t)0x01000000)
/// WF_TS_HUB_CHOPPER_FQ field position
#define WLAN_RF_WF_TS_HUB_CHOPPER_FQ_POS         24
/// WF_TS_HUB_CHANNEL_SEL field mask
#define WLAN_RF_WF_TS_HUB_CHANNEL_SEL_MASK       ((uint32_t)0x00F00000)
/// WF_TS_HUB_CHANNEL_SEL field LSB position
#define WLAN_RF_WF_TS_HUB_CHANNEL_SEL_LSB        20
/// WF_TS_HUB_CHANNEL_SEL field width
#define WLAN_RF_WF_TS_HUB_CHANNEL_SEL_WIDTH      ((uint32_t)0x00000004)
/// WF_TS_HUB_VPTAT_VBIT field mask
#define WLAN_RF_WF_TS_HUB_VPTAT_VBIT_MASK        ((uint32_t)0x000C0000)
/// WF_TS_HUB_VPTAT_VBIT field LSB position
#define WLAN_RF_WF_TS_HUB_VPTAT_VBIT_LSB         18
/// WF_TS_HUB_VPTAT_VBIT field width
#define WLAN_RF_WF_TS_HUB_VPTAT_VBIT_WIDTH       ((uint32_t)0x00000002)
/// WF_TS_HUB_VREF_VBIT field mask
#define WLAN_RF_WF_TS_HUB_VREF_VBIT_MASK         ((uint32_t)0x00030000)
/// WF_TS_HUB_VREF_VBIT field LSB position
#define WLAN_RF_WF_TS_HUB_VREF_VBIT_LSB          16
/// WF_TS_HUB_VREF_VBIT field width
#define WLAN_RF_WF_TS_HUB_VREF_VBIT_WIDTH        ((uint32_t)0x00000002)
/// WF_RX_IQ_2GPIO_EN field mask
#define WLAN_RF_WF_RX_IQ_2GPIO_EN_MASK           ((uint32_t)0x0000E000)
/// WF_RX_IQ_2GPIO_EN field LSB position
#define WLAN_RF_WF_RX_IQ_2GPIO_EN_LSB            13
/// WF_RX_IQ_2GPIO_EN field width
#define WLAN_RF_WF_RX_IQ_2GPIO_EN_WIDTH          ((uint32_t)0x00000003)
/// WF_ABB_RSVD_BIT field mask
#define WLAN_RF_WF_ABB_RSVD_BIT_MASK             ((uint32_t)0x00001E00)
/// WF_ABB_RSVD_BIT field LSB position
#define WLAN_RF_WF_ABB_RSVD_BIT_LSB              9
/// WF_ABB_RSVD_BIT field width
#define WLAN_RF_WF_ABB_RSVD_BIT_WIDTH            ((uint32_t)0x00000004)
/// WF_RFPLL_ENABLE_LOOP field bit
#define WLAN_RF_WF_RFPLL_ENABLE_LOOP_BIT         ((uint32_t)0x00000100)
/// WF_RFPLL_ENABLE_LOOP field position
#define WLAN_RF_WF_RFPLL_ENABLE_LOOP_POS         8
/// WF_RFPLL_ENABLE_PRESC field bit
#define WLAN_RF_WF_RFPLL_ENABLE_PRESC_BIT        ((uint32_t)0x00000080)
/// WF_RFPLL_ENABLE_PRESC field position
#define WLAN_RF_WF_RFPLL_ENABLE_PRESC_POS        7
/// WF_RFPLL_ENABLE_DPLL_MODE field bit
#define WLAN_RF_WF_RFPLL_ENABLE_DPLL_MODE_BIT    ((uint32_t)0x00000040)
/// WF_RFPLL_ENABLE_DPLL_MODE field position
#define WLAN_RF_WF_RFPLL_ENABLE_DPLL_MODE_POS    6
/// WF_RFPLL_PLL_REG_VBIT field mask
#define WLAN_RF_WF_RFPLL_PLL_REG_VBIT_MASK       ((uint32_t)0x0000003C)
/// WF_RFPLL_PLL_REG_VBIT field LSB position
#define WLAN_RF_WF_RFPLL_PLL_REG_VBIT_LSB        2
/// WF_RFPLL_PLL_REG_VBIT field width
#define WLAN_RF_WF_RFPLL_PLL_REG_VBIT_WIDTH      ((uint32_t)0x00000004)
/// WF_RFPLL_LDO_VBIT field mask
#define WLAN_RF_WF_RFPLL_LDO_VBIT_MASK           ((uint32_t)0x00000003)
/// WF_RFPLL_LDO_VBIT field LSB position
#define WLAN_RF_WF_RFPLL_LDO_VBIT_LSB            0
/// WF_RFPLL_LDO_VBIT field width
#define WLAN_RF_WF_RFPLL_LDO_VBIT_WIDTH          ((uint32_t)0x00000002)

/// WF_PDADC_DLY_BIT field reset value
#define WLAN_RF_WF_PDADC_DLY_BIT_RST             0x2
/// WF_PDADC_CLK_EDGE_SEL field reset value
#define WLAN_RF_WF_PDADC_CLK_EDGE_SEL_RST        0x0
/// WF_TS_HUB_CHOPPER_FQ field reset value
#define WLAN_RF_WF_TS_HUB_CHOPPER_FQ_RST         0x0
/// WF_TS_HUB_CHANNEL_SEL field reset value
#define WLAN_RF_WF_TS_HUB_CHANNEL_SEL_RST        0x1
/// WF_TS_HUB_VPTAT_VBIT field reset value
#define WLAN_RF_WF_TS_HUB_VPTAT_VBIT_RST         0x2
/// WF_TS_HUB_VREF_VBIT field reset value
#define WLAN_RF_WF_TS_HUB_VREF_VBIT_RST          0x2
/// WF_RX_IQ_2GPIO_EN field reset value
#define WLAN_RF_WF_RX_IQ_2GPIO_EN_RST            0x0
/// WF_ABB_RSVD_BIT field reset value
#define WLAN_RF_WF_ABB_RSVD_BIT_RST              0xC
/// WF_RFPLL_ENABLE_LOOP field reset value
#define WLAN_RF_WF_RFPLL_ENABLE_LOOP_RST         0x1
/// WF_RFPLL_ENABLE_PRESC field reset value
#define WLAN_RF_WF_RFPLL_ENABLE_PRESC_RST        0x1
/// WF_RFPLL_ENABLE_DPLL_MODE field reset value
#define WLAN_RF_WF_RFPLL_ENABLE_DPLL_MODE_RST    0x0
/// WF_RFPLL_PLL_REG_VBIT field reset value
#define WLAN_RF_WF_RFPLL_PLL_REG_VBIT_RST        0x8
/// WF_RFPLL_LDO_VBIT field reset value
#define WLAN_RF_WF_RFPLL_LDO_VBIT_RST            0x2

/**
 * @brief Constructs a value for the REG_0E register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpdadcdlybit - The value to use for the wf_pdadc_dly_bit field.
 * @param[in] wfpdadcclkedgesel - The value to use for the wf_pdadc_clk_edge_sel field.
 * @param[in] wftshubchopperfq - The value to use for the wf_ts_hub_chopper_fq field.
 * @param[in] wftshubchannelsel - The value to use for the wf_ts_hub_channel_sel field.
 * @param[in] wftshubvptatvbit - The value to use for the wf_ts_hub_vptat_vbit field.
 * @param[in] wftshubvrefvbit - The value to use for the wf_ts_hub_vref_vbit field.
 * @param[in] wfrxiq2gpioen - The value to use for the wf_rx_iq2gpio_en field.
 * @param[in] wfabbrsvdbit - The value to use for the wf_abb_rsvd_bit field.
 * @param[in] wfrfpllenableloop - The value to use for the wf_rfpll_enable_loop field.
 * @param[in] wfrfpllenablepresc - The value to use for the wf_rfpll_enable_presc field.
 * @param[in] wfrfpllenabledpllmode - The value to use for the wf_rfpll_enable_dpll_mode field.
 * @param[in] wfrfpllpllregvbit - The value to use for the wf_rfpll_pll_reg_vbit field.
 * @param[in] wfrfpllldovbit - The value to use for the wf_rfpll_ldo_vbit field.
 */
__INLINE void wlan_rf_reg_0e_pack(uint8_t wfpdadcdlybit, uint8_t wfpdadcclkedgesel, uint8_t wftshubchopperfq, uint8_t wftshubchannelsel, uint8_t wftshubvptatvbit, uint8_t wftshubvrefvbit, uint8_t wfrxiq2gpioen, uint8_t wfabbrsvdbit, uint8_t wfrfpllenableloop, uint8_t wfrfpllenablepresc, uint8_t wfrfpllenabledpllmode, uint8_t wfrfpllpllregvbit, uint8_t wfrfpllldovbit)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR,  ((uint32_t)wfpdadcdlybit << 26) | ((uint32_t)wfpdadcclkedgesel << 25) | ((uint32_t)wftshubchopperfq << 24) | ((uint32_t)wftshubchannelsel << 20) | ((uint32_t)wftshubvptatvbit << 18) | ((uint32_t)wftshubvrefvbit << 16) | ((uint32_t)wfrxiq2gpioen << 13) | ((uint32_t)wfabbrsvdbit << 9) | ((uint32_t)wfrfpllenableloop << 8) | ((uint32_t)wfrfpllenablepresc << 7) | ((uint32_t)wfrfpllenabledpllmode << 6) | ((uint32_t)wfrfpllpllregvbit << 2) | ((uint32_t)wfrfpllldovbit << 0));
}

/**
 * @brief Unpacks REG_0E's fields from current value of the REG_0E register.
 *
 * Reads the REG_0E register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpdadcdlybit - Will be populated with the current value of this field from the register.
 * @param[out] wfpdadcclkedgesel - Will be populated with the current value of this field from the register.
 * @param[out] wftshubchopperfq - Will be populated with the current value of this field from the register.
 * @param[out] wftshubchannelsel - Will be populated with the current value of this field from the register.
 * @param[out] wftshubvptatvbit - Will be populated with the current value of this field from the register.
 * @param[out] wftshubvrefvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrxiq2gpioen - Will be populated with the current value of this field from the register.
 * @param[out] wfabbrsvdbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllenableloop - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllenablepresc - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllenabledpllmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllpllregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllldovbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_0e_unpack(uint8_t* wfpdadcdlybit, uint8_t* wfpdadcclkedgesel, uint8_t* wftshubchopperfq, uint8_t* wftshubchannelsel, uint8_t* wftshubvptatvbit, uint8_t* wftshubvrefvbit, uint8_t* wfrxiq2gpioen, uint8_t* wfabbrsvdbit, uint8_t* wfrfpllenableloop, uint8_t* wfrfpllenablepresc, uint8_t* wfrfpllenabledpllmode, uint8_t* wfrfpllpllregvbit, uint8_t* wfrfpllldovbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);

    *wfpdadcdlybit = (localVal & ((uint32_t)0x3C000000)) >> 26;
    *wfpdadcclkedgesel = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wftshubchopperfq = (localVal & ((uint32_t)0x01000000)) >> 24;
    *wftshubchannelsel = (localVal & ((uint32_t)0x00F00000)) >> 20;
    *wftshubvptatvbit = (localVal & ((uint32_t)0x000C0000)) >> 18;
    *wftshubvrefvbit = (localVal & ((uint32_t)0x00030000)) >> 16;
    *wfrxiq2gpioen = (localVal & ((uint32_t)0x0000E000)) >> 13;
    *wfabbrsvdbit = (localVal & ((uint32_t)0x00001E00)) >> 9;
    *wfrfpllenableloop = (localVal & ((uint32_t)0x00000100)) >> 8;
    *wfrfpllenablepresc = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wfrfpllenabledpllmode = (localVal & ((uint32_t)0x00000040)) >> 6;
    *wfrfpllpllregvbit = (localVal & ((uint32_t)0x0000003C)) >> 2;
    *wfrfpllldovbit = (localVal & ((uint32_t)0x00000003)) >> 0;
}

/**
 * @brief Returns the current value of the wf_pdadc_dly_bit field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_pdadc_dly_bit field's value will be returned.
 *
 * @return The current value of the wf_pdadc_dly_bit field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_pdadc_dly_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x3C000000)) >> 26);
}

/**
 * @brief Sets the wf_pdadc_dly_bit field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpdadcdlybit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pdadc_dly_bit_setf(uint8_t wfpdadcdlybit)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x3C000000)) | (((uint32_t)wfpdadcdlybit << 26) & ((uint32_t)0x3C000000)));
}

/**
 * @brief Returns the current value of the wf_pdadc_clk_edge_sel field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_pdadc_clk_edge_sel field's value will be returned.
 *
 * @return The current value of the wf_pdadc_clk_edge_sel field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_pdadc_clk_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_pdadc_clk_edge_sel field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpdadcclkedgesel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pdadc_clk_edge_sel_setf(uint8_t wfpdadcclkedgesel)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wfpdadcclkedgesel << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_ts_hub_chopper_fq field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_ts_hub_chopper_fq field's value will be returned.
 *
 * @return The current value of the wf_ts_hub_chopper_fq field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_ts_hub_chopper_fq_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the wf_ts_hub_chopper_fq field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftshubchopperfq - The value to set the field to.
 */
__INLINE void wlan_rf_wf_ts_hub_chopper_fq_setf(uint8_t wftshubchopperfq)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)wftshubchopperfq << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the wf_ts_hub_channel_sel field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_ts_hub_channel_sel field's value will be returned.
 *
 * @return The current value of the wf_ts_hub_channel_sel field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_ts_hub_channel_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x00F00000)) >> 20);
}

/**
 * @brief Sets the wf_ts_hub_channel_sel field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftshubchannelsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_ts_hub_channel_sel_setf(uint8_t wftshubchannelsel)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x00F00000)) | (((uint32_t)wftshubchannelsel << 20) & ((uint32_t)0x00F00000)));
}

/**
 * @brief Returns the current value of the wf_ts_hub_vptat_vbit field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_ts_hub_vptat_vbit field's value will be returned.
 *
 * @return The current value of the wf_ts_hub_vptat_vbit field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_ts_hub_vptat_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x000C0000)) >> 18);
}

/**
 * @brief Sets the wf_ts_hub_vptat_vbit field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftshubvptatvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_ts_hub_vptat_vbit_setf(uint8_t wftshubvptatvbit)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x000C0000)) | (((uint32_t)wftshubvptatvbit << 18) & ((uint32_t)0x000C0000)));
}

/**
 * @brief Returns the current value of the wf_ts_hub_vref_vbit field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_ts_hub_vref_vbit field's value will be returned.
 *
 * @return The current value of the wf_ts_hub_vref_vbit field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_ts_hub_vref_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

/**
 * @brief Sets the wf_ts_hub_vref_vbit field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftshubvrefvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_ts_hub_vref_vbit_setf(uint8_t wftshubvrefvbit)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x00030000)) | (((uint32_t)wftshubvrefvbit << 16) & ((uint32_t)0x00030000)));
}

/**
 * @brief Returns the current value of the wf_rx_iq2gpio_en field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_rx_iq2gpio_en field's value will be returned.
 *
 * @return The current value of the wf_rx_iq2gpio_en field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_rx_iq_2gpio_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x0000E000)) >> 13);
}

/**
 * @brief Sets the wf_rx_iq2gpio_en field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrxiq2gpioen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rx_iq_2gpio_en_setf(uint8_t wfrxiq2gpioen)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x0000E000)) | (((uint32_t)wfrxiq2gpioen << 13) & ((uint32_t)0x0000E000)));
}

/**
 * @brief Returns the current value of the wf_abb_rsvd_bit field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_abb_rsvd_bit field's value will be returned.
 *
 * @return The current value of the wf_abb_rsvd_bit field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_abb_rsvd_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x00001E00)) >> 9);
}

/**
 * @brief Sets the wf_abb_rsvd_bit field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfabbrsvdbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_abb_rsvd_bit_setf(uint8_t wfabbrsvdbit)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x00001E00)) | (((uint32_t)wfabbrsvdbit << 9) & ((uint32_t)0x00001E00)));
}

/**
 * @brief Returns the current value of the wf_rfpll_enable_loop field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_rfpll_enable_loop field's value will be returned.
 *
 * @return The current value of the wf_rfpll_enable_loop field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_enable_loop_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the wf_rfpll_enable_loop field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllenableloop - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_enable_loop_setf(uint8_t wfrfpllenableloop)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)wfrfpllenableloop << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the wf_rfpll_enable_presc field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_rfpll_enable_presc field's value will be returned.
 *
 * @return The current value of the wf_rfpll_enable_presc field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_enable_presc_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

/**
 * @brief Sets the wf_rfpll_enable_presc field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllenablepresc - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_enable_presc_setf(uint8_t wfrfpllenablepresc)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x00000080)) | (((uint32_t)wfrfpllenablepresc << 7) & ((uint32_t)0x00000080)));
}

/**
 * @brief Returns the current value of the wf_rfpll_enable_dpll_mode field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_rfpll_enable_dpll_mode field's value will be returned.
 *
 * @return The current value of the wf_rfpll_enable_dpll_mode field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_enable_dpll_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

/**
 * @brief Sets the wf_rfpll_enable_dpll_mode field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllenabledpllmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_enable_dpll_mode_setf(uint8_t wfrfpllenabledpllmode)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x00000040)) | (((uint32_t)wfrfpllenabledpllmode << 6) & ((uint32_t)0x00000040)));
}

/**
 * @brief Returns the current value of the wf_rfpll_pll_reg_vbit field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_rfpll_pll_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_pll_reg_vbit field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_pll_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x0000003C)) >> 2);
}

/**
 * @brief Sets the wf_rfpll_pll_reg_vbit field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllpllregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_pll_reg_vbit_setf(uint8_t wfrfpllpllregvbit)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x0000003C)) | (((uint32_t)wfrfpllpllregvbit << 2) & ((uint32_t)0x0000003C)));
}

/**
 * @brief Returns the current value of the wf_rfpll_ldo_vbit field in the REG_0E register.
 *
 * The REG_0E register will be read and the wf_rfpll_ldo_vbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_ldo_vbit field in the REG_0E register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_ldo_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0E_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

/**
 * @brief Sets the wf_rfpll_ldo_vbit field of the REG_0E register.
 *
 * The REG_0E register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllldovbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_ldo_vbit_setf(uint8_t wfrfpllldovbit)
{
    REG_PL_WR(WLAN_RF_REG_0E_ADDR, (REG_PL_RD(WLAN_RF_REG_0E_ADDR) & ~((uint32_t)0x00000003)) | (((uint32_t)wfrfpllldovbit << 0) & ((uint32_t)0x00000003)));
}

/// @}

/**
 * @name REG_0F register definitions
 * <table>
 * <caption id="REG_0F_BF">REG_0F bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:28 <td>wf_rfpll_pll_presc_reg_vbit <td>R <td>R/W <td>0x8
 * <tr><td>27 <td> wf_rfpll_fref_sel <td>R <td>R/W <td>1
 * <tr><td>26 <td>wf_rfpll_ref_multi2_en <td>R <td>R/W <td>0
 * <tr><td>25 <td>wf_rfpll_loop_mode <td>R <td>R/W <td>0
 * <tr><td>24:23 <td>wf_rfpll_sinc_mode <td>R <td>R/W <td>0x1
 * <tr><td>22 <td>wf_rfpll_lpf_notch_bypass <td>R <td>R/W <td>0
 * <tr><td>21:18 <td> wf_rfpll_vco_gain <td>R <td>R/W <td>0xF
 * <tr><td>17:16 <td>  wf_rfpll_cp_rbit <td>R <td>R/W <td>0x0
 * <tr><td>15:12 <td>  wf_rfpll_cp_ibit <td>R <td>R/W <td>0x4
 * <tr><td>11:10 <td> wf_rfpll_lpf_rbit <td>R <td>R/W <td>0x2
 * <tr><td>09:08 <td>wf_rfpll_lpf_gain_bit <td>R <td>R/W <td>0x3
 * <tr><td>07:02 <td>wf_rfpll_pdt_res_bit <td>R <td>R/W <td>0x0
 * <tr><td>01 <td>wf_rfpll_sdm_clk_sel <td>W <td>R <td>0
 * <tr><td>00 <td>  wf_rfpll_fbc_sel <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_0F register
#define WLAN_RF_REG_0F_ADDR   0x4034403C
/// Offset of the REG_0F register from the base address
#define WLAN_RF_REG_0F_OFFSET 0x0000003C
/// Index of the REG_0F register
#define WLAN_RF_REG_0F_INDEX  0x0000000F
/// Reset value of the REG_0F register
#define WLAN_RF_REG_0F_RESET  0x88BC4B00

/**
 * @brief Returns the current value of the REG_0F register.
 * The REG_0F register will be read and its value returned.
 * @return The current value of the REG_0F register.
 */
__INLINE uint32_t wlan_rf_reg_0f_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_0F_ADDR);
}

/**
 * @brief Sets the REG_0F register to a value.
 * The REG_0F register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_0f_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, value);
}

// field definitions
/// WF_RFPLL_PLL_PRESC_REG_VBIT field mask
#define WLAN_RF_WF_RFPLL_PLL_PRESC_REG_VBIT_MASK   ((uint32_t)0xF0000000)
/// WF_RFPLL_PLL_PRESC_REG_VBIT field LSB position
#define WLAN_RF_WF_RFPLL_PLL_PRESC_REG_VBIT_LSB    28
/// WF_RFPLL_PLL_PRESC_REG_VBIT field width
#define WLAN_RF_WF_RFPLL_PLL_PRESC_REG_VBIT_WIDTH  ((uint32_t)0x00000004)
/// WF_RFPLL_FREF_SEL field bit
#define WLAN_RF_WF_RFPLL_FREF_SEL_BIT              ((uint32_t)0x08000000)
/// WF_RFPLL_FREF_SEL field position
#define WLAN_RF_WF_RFPLL_FREF_SEL_POS              27
/// WF_RFPLL_REF_MULTI_2_EN field bit
#define WLAN_RF_WF_RFPLL_REF_MULTI_2_EN_BIT        ((uint32_t)0x04000000)
/// WF_RFPLL_REF_MULTI_2_EN field position
#define WLAN_RF_WF_RFPLL_REF_MULTI_2_EN_POS        26
/// WF_RFPLL_LOOP_MODE field bit
#define WLAN_RF_WF_RFPLL_LOOP_MODE_BIT             ((uint32_t)0x02000000)
/// WF_RFPLL_LOOP_MODE field position
#define WLAN_RF_WF_RFPLL_LOOP_MODE_POS             25
/// WF_RFPLL_SINC_MODE field mask
#define WLAN_RF_WF_RFPLL_SINC_MODE_MASK            ((uint32_t)0x01800000)
/// WF_RFPLL_SINC_MODE field LSB position
#define WLAN_RF_WF_RFPLL_SINC_MODE_LSB             23
/// WF_RFPLL_SINC_MODE field width
#define WLAN_RF_WF_RFPLL_SINC_MODE_WIDTH           ((uint32_t)0x00000002)
/// WF_RFPLL_LPF_NOTCH_BYPASS field bit
#define WLAN_RF_WF_RFPLL_LPF_NOTCH_BYPASS_BIT      ((uint32_t)0x00400000)
/// WF_RFPLL_LPF_NOTCH_BYPASS field position
#define WLAN_RF_WF_RFPLL_LPF_NOTCH_BYPASS_POS      22
/// WF_RFPLL_VCO_GAIN field mask
#define WLAN_RF_WF_RFPLL_VCO_GAIN_MASK             ((uint32_t)0x003C0000)
/// WF_RFPLL_VCO_GAIN field LSB position
#define WLAN_RF_WF_RFPLL_VCO_GAIN_LSB              18
/// WF_RFPLL_VCO_GAIN field width
#define WLAN_RF_WF_RFPLL_VCO_GAIN_WIDTH            ((uint32_t)0x00000004)
/// WF_RFPLL_CP_RBIT field mask
#define WLAN_RF_WF_RFPLL_CP_RBIT_MASK              ((uint32_t)0x00030000)
/// WF_RFPLL_CP_RBIT field LSB position
#define WLAN_RF_WF_RFPLL_CP_RBIT_LSB               16
/// WF_RFPLL_CP_RBIT field width
#define WLAN_RF_WF_RFPLL_CP_RBIT_WIDTH             ((uint32_t)0x00000002)
/// WF_RFPLL_CP_IBIT field mask
#define WLAN_RF_WF_RFPLL_CP_IBIT_MASK              ((uint32_t)0x0000F000)
/// WF_RFPLL_CP_IBIT field LSB position
#define WLAN_RF_WF_RFPLL_CP_IBIT_LSB               12
/// WF_RFPLL_CP_IBIT field width
#define WLAN_RF_WF_RFPLL_CP_IBIT_WIDTH             ((uint32_t)0x00000004)
/// WF_RFPLL_LPF_RBIT field mask
#define WLAN_RF_WF_RFPLL_LPF_RBIT_MASK             ((uint32_t)0x00000C00)
/// WF_RFPLL_LPF_RBIT field LSB position
#define WLAN_RF_WF_RFPLL_LPF_RBIT_LSB              10
/// WF_RFPLL_LPF_RBIT field width
#define WLAN_RF_WF_RFPLL_LPF_RBIT_WIDTH            ((uint32_t)0x00000002)
/// WF_RFPLL_LPF_GAIN_BIT field mask
#define WLAN_RF_WF_RFPLL_LPF_GAIN_BIT_MASK         ((uint32_t)0x00000300)
/// WF_RFPLL_LPF_GAIN_BIT field LSB position
#define WLAN_RF_WF_RFPLL_LPF_GAIN_BIT_LSB          8
/// WF_RFPLL_LPF_GAIN_BIT field width
#define WLAN_RF_WF_RFPLL_LPF_GAIN_BIT_WIDTH        ((uint32_t)0x00000002)
/// WF_RFPLL_PDT_RES_BIT field mask
#define WLAN_RF_WF_RFPLL_PDT_RES_BIT_MASK          ((uint32_t)0x000000FC)
/// WF_RFPLL_PDT_RES_BIT field LSB position
#define WLAN_RF_WF_RFPLL_PDT_RES_BIT_LSB           2
/// WF_RFPLL_PDT_RES_BIT field width
#define WLAN_RF_WF_RFPLL_PDT_RES_BIT_WIDTH         ((uint32_t)0x00000006)
/// WF_RFPLL_SDM_CLK_SEL field bit
#define WLAN_RF_WF_RFPLL_SDM_CLK_SEL_BIT           ((uint32_t)0x00000002)
/// WF_RFPLL_SDM_CLK_SEL field position
#define WLAN_RF_WF_RFPLL_SDM_CLK_SEL_POS           1
/// WF_RFPLL_FBC_SEL field bit
#define WLAN_RF_WF_RFPLL_FBC_SEL_BIT               ((uint32_t)0x00000001)
/// WF_RFPLL_FBC_SEL field position
#define WLAN_RF_WF_RFPLL_FBC_SEL_POS               0

/// WF_RFPLL_PLL_PRESC_REG_VBIT field reset value
#define WLAN_RF_WF_RFPLL_PLL_PRESC_REG_VBIT_RST    0x8
/// WF_RFPLL_FREF_SEL field reset value
#define WLAN_RF_WF_RFPLL_FREF_SEL_RST              0x1
/// WF_RFPLL_REF_MULTI_2_EN field reset value
#define WLAN_RF_WF_RFPLL_REF_MULTI_2_EN_RST        0x0
/// WF_RFPLL_LOOP_MODE field reset value
#define WLAN_RF_WF_RFPLL_LOOP_MODE_RST             0x0
/// WF_RFPLL_SINC_MODE field reset value
#define WLAN_RF_WF_RFPLL_SINC_MODE_RST             0x1
/// WF_RFPLL_LPF_NOTCH_BYPASS field reset value
#define WLAN_RF_WF_RFPLL_LPF_NOTCH_BYPASS_RST      0x0
/// WF_RFPLL_VCO_GAIN field reset value
#define WLAN_RF_WF_RFPLL_VCO_GAIN_RST              0xF
/// WF_RFPLL_CP_RBIT field reset value
#define WLAN_RF_WF_RFPLL_CP_RBIT_RST               0x0
/// WF_RFPLL_CP_IBIT field reset value
#define WLAN_RF_WF_RFPLL_CP_IBIT_RST               0x4
/// WF_RFPLL_LPF_RBIT field reset value
#define WLAN_RF_WF_RFPLL_LPF_RBIT_RST              0x2
/// WF_RFPLL_LPF_GAIN_BIT field reset value
#define WLAN_RF_WF_RFPLL_LPF_GAIN_BIT_RST          0x3
/// WF_RFPLL_PDT_RES_BIT field reset value
#define WLAN_RF_WF_RFPLL_PDT_RES_BIT_RST           0x0
/// WF_RFPLL_SDM_CLK_SEL field reset value
#define WLAN_RF_WF_RFPLL_SDM_CLK_SEL_RST           0x0
/// WF_RFPLL_FBC_SEL field reset value
#define WLAN_RF_WF_RFPLL_FBC_SEL_RST               0x0

/**
 * @brief Constructs a value for the REG_0F register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrfpllpllprescregvbit - The value to use for the wf_rfpll_pll_presc_reg_vbit field.
 * @param[in] wfrfpllfrefsel - The value to use for the wf_rfpll_fref_sel field.
 * @param[in] wfrfpllrefmulti2en - The value to use for the wf_rfpll_ref_multi2_en field.
 * @param[in] wfrfpllloopmode - The value to use for the wf_rfpll_loop_mode field.
 * @param[in] wfrfpllsincmode - The value to use for the wf_rfpll_sinc_mode field.
 * @param[in] wfrfplllpfnotchbypass - The value to use for the wf_rfpll_lpf_notch_bypass field.
 * @param[in] wfrfpllvcogain - The value to use for the wf_rfpll_vco_gain field.
 * @param[in] wfrfpllcprbit - The value to use for the wf_rfpll_cp_rbit field.
 * @param[in] wfrfpllcpibit - The value to use for the wf_rfpll_cp_ibit field.
 * @param[in] wfrfplllpfrbit - The value to use for the wf_rfpll_lpf_rbit field.
 * @param[in] wfrfplllpfgainbit - The value to use for the wf_rfpll_lpf_gain_bit field.
 * @param[in] wfrfpllpdtresbit - The value to use for the wf_rfpll_pdt_res_bit field.
 * @param[in] wfrfpllfbcsel - The value to use for the wf_rfpll_fbc_sel field.
 */
__INLINE void wlan_rf_reg_0f_pack(uint8_t wfrfpllpllprescregvbit, uint8_t wfrfpllfrefsel, uint8_t wfrfpllrefmulti2en, uint8_t wfrfpllloopmode, uint8_t wfrfpllsincmode, uint8_t wfrfplllpfnotchbypass, uint8_t wfrfpllvcogain, uint8_t wfrfpllcprbit, uint8_t wfrfpllcpibit, uint8_t wfrfplllpfrbit, uint8_t wfrfplllpfgainbit, uint8_t wfrfpllpdtresbit, uint8_t wfrfpllfbcsel)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR,  ((uint32_t)wfrfpllpllprescregvbit << 28) | ((uint32_t)wfrfpllfrefsel << 27) | ((uint32_t)wfrfpllrefmulti2en << 26) | ((uint32_t)wfrfpllloopmode << 25) | ((uint32_t)wfrfpllsincmode << 23) | ((uint32_t)wfrfplllpfnotchbypass << 22) | ((uint32_t)wfrfpllvcogain << 18) | ((uint32_t)wfrfpllcprbit << 16) | ((uint32_t)wfrfpllcpibit << 12) | ((uint32_t)wfrfplllpfrbit << 10) | ((uint32_t)wfrfplllpfgainbit << 8) | ((uint32_t)wfrfpllpdtresbit << 2) | ((uint32_t)wfrfpllfbcsel << 0));
}

/**
 * @brief Unpacks REG_0F's fields from current value of the REG_0F register.
 *
 * Reads the REG_0F register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrfpllpllprescregvbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllfrefsel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllrefmulti2en - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllloopmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllsincmode - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplllpfnotchbypass - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllvcogain - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllcprbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllcpibit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplllpfrbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplllpfgainbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllpdtresbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllsdmclksel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllfbcsel - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_0f_unpack(uint8_t* wfrfpllpllprescregvbit, uint8_t* wfrfpllfrefsel, uint8_t* wfrfpllrefmulti2en, uint8_t* wfrfpllloopmode, uint8_t* wfrfpllsincmode, uint8_t* wfrfplllpfnotchbypass, uint8_t* wfrfpllvcogain, uint8_t* wfrfpllcprbit, uint8_t* wfrfpllcpibit, uint8_t* wfrfplllpfrbit, uint8_t* wfrfplllpfgainbit, uint8_t* wfrfpllpdtresbit, uint8_t* wfrfpllsdmclksel, uint8_t* wfrfpllfbcsel)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);

    *wfrfpllpllprescregvbit = (localVal & ((uint32_t)0xF0000000)) >> 28;
    *wfrfpllfrefsel = (localVal & ((uint32_t)0x08000000)) >> 27;
    *wfrfpllrefmulti2en = (localVal & ((uint32_t)0x04000000)) >> 26;
    *wfrfpllloopmode = (localVal & ((uint32_t)0x02000000)) >> 25;
    *wfrfpllsincmode = (localVal & ((uint32_t)0x01800000)) >> 23;
    *wfrfplllpfnotchbypass = (localVal & ((uint32_t)0x00400000)) >> 22;
    *wfrfpllvcogain = (localVal & ((uint32_t)0x003C0000)) >> 18;
    *wfrfpllcprbit = (localVal & ((uint32_t)0x00030000)) >> 16;
    *wfrfpllcpibit = (localVal & ((uint32_t)0x0000F000)) >> 12;
    *wfrfplllpfrbit = (localVal & ((uint32_t)0x00000C00)) >> 10;
    *wfrfplllpfgainbit = (localVal & ((uint32_t)0x00000300)) >> 8;
    *wfrfpllpdtresbit = (localVal & ((uint32_t)0x000000FC)) >> 2;
    *wfrfpllsdmclksel = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfrfpllfbcsel = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rfpll_pll_presc_reg_vbit field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_pll_presc_reg_vbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_pll_presc_reg_vbit field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_pll_presc_reg_vbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0xF0000000)) >> 28);
}

/**
 * @brief Sets the wf_rfpll_pll_presc_reg_vbit field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllpllprescregvbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_pll_presc_reg_vbit_setf(uint8_t wfrfpllpllprescregvbit)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0xF0000000)) | (((uint32_t)wfrfpllpllprescregvbit << 28) & ((uint32_t)0xF0000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_fref_sel field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_fref_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_fref_sel field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_fref_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the wf_rfpll_fref_sel field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllfrefsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_fref_sel_setf(uint8_t wfrfpllfrefsel)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)wfrfpllfrefsel << 27) & ((uint32_t)0x08000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_ref_multi2_en field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_ref_multi2_en field's value will be returned.
 *
 * @return The current value of the wf_rfpll_ref_multi2_en field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_ref_multi_2_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the wf_rfpll_ref_multi2_en field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllrefmulti2en - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_ref_multi_2_en_setf(uint8_t wfrfpllrefmulti2en)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)wfrfpllrefmulti2en << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_loop_mode field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_loop_mode field's value will be returned.
 *
 * @return The current value of the wf_rfpll_loop_mode field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_loop_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

/**
 * @brief Sets the wf_rfpll_loop_mode field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllloopmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_loop_mode_setf(uint8_t wfrfpllloopmode)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x02000000)) | (((uint32_t)wfrfpllloopmode << 25) & ((uint32_t)0x02000000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_sinc_mode field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_sinc_mode field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sinc_mode field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sinc_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x01800000)) >> 23);
}

/**
 * @brief Sets the wf_rfpll_sinc_mode field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllsincmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_sinc_mode_setf(uint8_t wfrfpllsincmode)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x01800000)) | (((uint32_t)wfrfpllsincmode << 23) & ((uint32_t)0x01800000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_lpf_notch_bypass field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_lpf_notch_bypass field's value will be returned.
 *
 * @return The current value of the wf_rfpll_lpf_notch_bypass field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_lpf_notch_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

/**
 * @brief Sets the wf_rfpll_lpf_notch_bypass field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplllpfnotchbypass - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_lpf_notch_bypass_setf(uint8_t wfrfplllpfnotchbypass)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x00400000)) | (((uint32_t)wfrfplllpfnotchbypass << 22) & ((uint32_t)0x00400000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_vco_gain field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_vco_gain field's value will be returned.
 *
 * @return The current value of the wf_rfpll_vco_gain field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_vco_gain_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x003C0000)) >> 18);
}

/**
 * @brief Sets the wf_rfpll_vco_gain field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllvcogain - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_vco_gain_setf(uint8_t wfrfpllvcogain)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x003C0000)) | (((uint32_t)wfrfpllvcogain << 18) & ((uint32_t)0x003C0000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_cp_rbit field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_cp_rbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cp_rbit field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_cp_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

/**
 * @brief Sets the wf_rfpll_cp_rbit field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllcprbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_cp_rbit_setf(uint8_t wfrfpllcprbit)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x00030000)) | (((uint32_t)wfrfpllcprbit << 16) & ((uint32_t)0x00030000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_cp_ibit field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_cp_ibit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cp_ibit field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_cp_ibit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x0000F000)) >> 12);
}

/**
 * @brief Sets the wf_rfpll_cp_ibit field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllcpibit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_cp_ibit_setf(uint8_t wfrfpllcpibit)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x0000F000)) | (((uint32_t)wfrfpllcpibit << 12) & ((uint32_t)0x0000F000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_lpf_rbit field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_lpf_rbit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_lpf_rbit field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_lpf_rbit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x00000C00)) >> 10);
}

/**
 * @brief Sets the wf_rfpll_lpf_rbit field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplllpfrbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_lpf_rbit_setf(uint8_t wfrfplllpfrbit)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x00000C00)) | (((uint32_t)wfrfplllpfrbit << 10) & ((uint32_t)0x00000C00)));
}

/**
 * @brief Returns the current value of the wf_rfpll_lpf_gain_bit field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_lpf_gain_bit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_lpf_gain_bit field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_lpf_gain_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

/**
 * @brief Sets the wf_rfpll_lpf_gain_bit field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplllpfgainbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_lpf_gain_bit_setf(uint8_t wfrfplllpfgainbit)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x00000300)) | (((uint32_t)wfrfplllpfgainbit << 8) & ((uint32_t)0x00000300)));
}

/**
 * @brief Returns the current value of the wf_rfpll_pdt_res_bit field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_pdt_res_bit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_pdt_res_bit field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_pdt_res_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x000000FC)) >> 2);
}

/**
 * @brief Sets the wf_rfpll_pdt_res_bit field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllpdtresbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_pdt_res_bit_setf(uint8_t wfrfpllpdtresbit)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x000000FC)) | (((uint32_t)wfrfpllpdtresbit << 2) & ((uint32_t)0x000000FC)));
}

/**
 * @brief Returns the current value of the wf_rfpll_sdm_clk_sel field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_sdm_clk_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sdm_clk_sel field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sdm_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Returns the current value of the wf_rfpll_fbc_sel field in the REG_0F register.
 *
 * The REG_0F register will be read and the wf_rfpll_fbc_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_fbc_sel field in the REG_0F register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_fbc_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_0F_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_rfpll_fbc_sel field of the REG_0F register.
 *
 * The REG_0F register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllfbcsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_fbc_sel_setf(uint8_t wfrfpllfbcsel)
{
    REG_PL_WR(WLAN_RF_REG_0F_ADDR, (REG_PL_RD(WLAN_RF_REG_0F_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfrfpllfbcsel << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_10 register definitions
 * <table>
 * <caption id="REG_10_BF">REG_10 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>18 <td>wf_rfpll_cal_clk_sel <td>R <td>R/W <td>0
 * <tr><td>17 <td>wf_rfpll_pll_cal_en <td>W <td>R <td>0
 * <tr><td>16:15 <td>  wf_rfpll_cal_bit <td>R <td>R/W <td>0x2
 * <tr><td>14:13 <td>wf_rfpll_pll_vco_cal_sel <td>R <td>R/W <td>0x1
 * <tr><td>12:11 <td>wf_rfpll_sinc_clk_sel <td>R <td>R/W <td>0x0
 * <tr><td>10:02 <td>wf_rfpll_div_clk_gen <td>R <td>R/W <td>0x3B
 * <tr><td>01 <td>wf_rfpll_div_edge_sel <td>R <td>R/W <td>0
 * <tr><td>00 <td>wf_rfpll_vctrl_detect_en <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the REG_10 register
#define WLAN_RF_REG_10_ADDR   0x40344040
/// Offset of the REG_10 register from the base address
#define WLAN_RF_REG_10_OFFSET 0x00000040
/// Index of the REG_10 register
#define WLAN_RF_REG_10_INDEX  0x00000010
/// Reset value of the REG_10 register
#define WLAN_RF_REG_10_RESET  0x000120EC

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
/// WF_RFPLL_CAL_CLK_SEL field bit
#define WLAN_RF_WF_RFPLL_CAL_CLK_SEL_BIT        ((uint32_t)0x00040000)
/// WF_RFPLL_CAL_CLK_SEL field position
#define WLAN_RF_WF_RFPLL_CAL_CLK_SEL_POS        18
/// WF_RFPLL_PLL_CAL_EN field bit
#define WLAN_RF_WF_RFPLL_PLL_CAL_EN_BIT         ((uint32_t)0x00020000)
/// WF_RFPLL_PLL_CAL_EN field position
#define WLAN_RF_WF_RFPLL_PLL_CAL_EN_POS         17
/// WF_RFPLL_CAL_BIT field mask
#define WLAN_RF_WF_RFPLL_CAL_BIT_MASK           ((uint32_t)0x00018000)
/// WF_RFPLL_CAL_BIT field LSB position
#define WLAN_RF_WF_RFPLL_CAL_BIT_LSB            15
/// WF_RFPLL_CAL_BIT field width
#define WLAN_RF_WF_RFPLL_CAL_BIT_WIDTH          ((uint32_t)0x00000002)
/// WF_RFPLL_PLL_VCO_CAL_SEL field mask
#define WLAN_RF_WF_RFPLL_PLL_VCO_CAL_SEL_MASK   ((uint32_t)0x00006000)
/// WF_RFPLL_PLL_VCO_CAL_SEL field LSB position
#define WLAN_RF_WF_RFPLL_PLL_VCO_CAL_SEL_LSB    13
/// WF_RFPLL_PLL_VCO_CAL_SEL field width
#define WLAN_RF_WF_RFPLL_PLL_VCO_CAL_SEL_WIDTH  ((uint32_t)0x00000002)
/// WF_RFPLL_SINC_CLK_SEL field mask
#define WLAN_RF_WF_RFPLL_SINC_CLK_SEL_MASK      ((uint32_t)0x00001800)
/// WF_RFPLL_SINC_CLK_SEL field LSB position
#define WLAN_RF_WF_RFPLL_SINC_CLK_SEL_LSB       11
/// WF_RFPLL_SINC_CLK_SEL field width
#define WLAN_RF_WF_RFPLL_SINC_CLK_SEL_WIDTH     ((uint32_t)0x00000002)
/// WF_RFPLL_DIV_CLK_GEN field mask
#define WLAN_RF_WF_RFPLL_DIV_CLK_GEN_MASK       ((uint32_t)0x000007FC)
/// WF_RFPLL_DIV_CLK_GEN field LSB position
#define WLAN_RF_WF_RFPLL_DIV_CLK_GEN_LSB        2
/// WF_RFPLL_DIV_CLK_GEN field width
#define WLAN_RF_WF_RFPLL_DIV_CLK_GEN_WIDTH      ((uint32_t)0x00000009)
/// WF_RFPLL_DIV_EDGE_SEL field bit
#define WLAN_RF_WF_RFPLL_DIV_EDGE_SEL_BIT       ((uint32_t)0x00000002)
/// WF_RFPLL_DIV_EDGE_SEL field position
#define WLAN_RF_WF_RFPLL_DIV_EDGE_SEL_POS       1
/// WF_RFPLL_VCTRL_DETECT_EN field bit
#define WLAN_RF_WF_RFPLL_VCTRL_DETECT_EN_BIT    ((uint32_t)0x00000001)
/// WF_RFPLL_VCTRL_DETECT_EN field position
#define WLAN_RF_WF_RFPLL_VCTRL_DETECT_EN_POS    0

/// WF_RFPLL_CAL_CLK_SEL field reset value
#define WLAN_RF_WF_RFPLL_CAL_CLK_SEL_RST        0x0
/// WF_RFPLL_PLL_CAL_EN field reset value
#define WLAN_RF_WF_RFPLL_PLL_CAL_EN_RST         0x0
/// WF_RFPLL_CAL_BIT field reset value
#define WLAN_RF_WF_RFPLL_CAL_BIT_RST            0x2
/// WF_RFPLL_PLL_VCO_CAL_SEL field reset value
#define WLAN_RF_WF_RFPLL_PLL_VCO_CAL_SEL_RST    0x1
/// WF_RFPLL_SINC_CLK_SEL field reset value
#define WLAN_RF_WF_RFPLL_SINC_CLK_SEL_RST       0x0
/// WF_RFPLL_DIV_CLK_GEN field reset value
#define WLAN_RF_WF_RFPLL_DIV_CLK_GEN_RST        0x3B
/// WF_RFPLL_DIV_EDGE_SEL field reset value
#define WLAN_RF_WF_RFPLL_DIV_EDGE_SEL_RST       0x0
/// WF_RFPLL_VCTRL_DETECT_EN field reset value
#define WLAN_RF_WF_RFPLL_VCTRL_DETECT_EN_RST    0x0

/**
 * @brief Constructs a value for the REG_10 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrfpllcalclksel - The value to use for the wf_rfpll_cal_clk_sel field.
 * @param[in] wfrfpllcalbit - The value to use for the wf_rfpll_cal_bit field.
 * @param[in] wfrfpllpllvcocalsel - The value to use for the wf_rfpll_pll_vco_cal_sel field.
 * @param[in] wfrfpllsincclksel - The value to use for the wf_rfpll_sinc_clk_sel field.
 * @param[in] wfrfplldivclkgen - The value to use for the wf_rfpll_div_clk_gen field.
 * @param[in] wfrfplldivedgesel - The value to use for the wf_rfpll_div_edge_sel field.
 * @param[in] wfrfpllvctrldetecten - The value to use for the wf_rfpll_vctrl_detect_en field.
 */
__INLINE void wlan_rf_reg_10_pack(uint8_t wfrfpllcalclksel, uint8_t wfrfpllcalbit, uint8_t wfrfpllpllvcocalsel, uint8_t wfrfpllsincclksel, uint16_t wfrfplldivclkgen, uint8_t wfrfplldivedgesel, uint8_t wfrfpllvctrldetecten)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR,  ((uint32_t)wfrfpllcalclksel << 18) | ((uint32_t)wfrfpllcalbit << 15) | ((uint32_t)wfrfpllpllvcocalsel << 13) | ((uint32_t)wfrfpllsincclksel << 11) | ((uint32_t)wfrfplldivclkgen << 2) | ((uint32_t)wfrfplldivedgesel << 1) | ((uint32_t)wfrfpllvctrldetecten << 0));
}

/**
 * @brief Unpacks REG_10's fields from current value of the REG_10 register.
 *
 * Reads the REG_10 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrfpllcalclksel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllpllcalen - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllcalbit - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllpllvcocalsel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllsincclksel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplldivclkgen - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplldivedgesel - Will be populated with the current value of this field from the register.
 * @param[out] wfrfpllvctrldetecten - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_10_unpack(uint8_t* wfrfpllcalclksel, uint8_t* wfrfpllpllcalen, uint8_t* wfrfpllcalbit, uint8_t* wfrfpllpllvcocalsel, uint8_t* wfrfpllsincclksel, uint16_t* wfrfplldivclkgen, uint8_t* wfrfplldivedgesel, uint8_t* wfrfpllvctrldetecten)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);

    *wfrfpllcalclksel = (localVal & ((uint32_t)0x00040000)) >> 18;
    *wfrfpllpllcalen = (localVal & ((uint32_t)0x00020000)) >> 17;
    *wfrfpllcalbit = (localVal & ((uint32_t)0x00018000)) >> 15;
    *wfrfpllpllvcocalsel = (localVal & ((uint32_t)0x00006000)) >> 13;
    *wfrfpllsincclksel = (localVal & ((uint32_t)0x00001800)) >> 11;
    *wfrfplldivclkgen = (localVal & ((uint32_t)0x000007FC)) >> 2;
    *wfrfplldivedgesel = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfrfpllvctrldetecten = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rfpll_cal_clk_sel field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_cal_clk_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cal_clk_sel field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_cal_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

/**
 * @brief Sets the wf_rfpll_cal_clk_sel field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllcalclksel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_cal_clk_sel_setf(uint8_t wfrfpllcalclksel)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00040000)) | (((uint32_t)wfrfpllcalclksel << 18) & ((uint32_t)0x00040000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_pll_cal_en field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_pll_cal_en field's value will be returned.
 *
 * @return The current value of the wf_rfpll_pll_cal_en field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_pll_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

/**
 * @brief Returns the current value of the wf_rfpll_cal_bit field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_cal_bit field's value will be returned.
 *
 * @return The current value of the wf_rfpll_cal_bit field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_cal_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00018000)) >> 15);
}

/**
 * @brief Sets the wf_rfpll_cal_bit field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllcalbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_cal_bit_setf(uint8_t wfrfpllcalbit)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00018000)) | (((uint32_t)wfrfpllcalbit << 15) & ((uint32_t)0x00018000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_pll_vco_cal_sel field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_pll_vco_cal_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_pll_vco_cal_sel field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_pll_vco_cal_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00006000)) >> 13);
}

/**
 * @brief Sets the wf_rfpll_pll_vco_cal_sel field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllpllvcocalsel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_pll_vco_cal_sel_setf(uint8_t wfrfpllpllvcocalsel)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00006000)) | (((uint32_t)wfrfpllpllvcocalsel << 13) & ((uint32_t)0x00006000)));
}

/**
 * @brief Returns the current value of the wf_rfpll_sinc_clk_sel field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_sinc_clk_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_sinc_clk_sel field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_sinc_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00001800)) >> 11);
}

/**
 * @brief Sets the wf_rfpll_sinc_clk_sel field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllsincclksel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_sinc_clk_sel_setf(uint8_t wfrfpllsincclksel)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00001800)) | (((uint32_t)wfrfpllsincclksel << 11) & ((uint32_t)0x00001800)));
}

/**
 * @brief Returns the current value of the wf_rfpll_div_clk_gen field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_div_clk_gen field's value will be returned.
 *
 * @return The current value of the wf_rfpll_div_clk_gen field in the REG_10 register.
 */
__INLINE uint16_t wlan_rf_wf_rfpll_div_clk_gen_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x000007FC)) >> 2);
}

/**
 * @brief Sets the wf_rfpll_div_clk_gen field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplldivclkgen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_div_clk_gen_setf(uint16_t wfrfplldivclkgen)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x000007FC)) | (((uint32_t)wfrfplldivclkgen << 2) & ((uint32_t)0x000007FC)));
}

/**
 * @brief Returns the current value of the wf_rfpll_div_edge_sel field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_div_edge_sel field's value will be returned.
 *
 * @return The current value of the wf_rfpll_div_edge_sel field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_div_edge_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_rfpll_div_edge_sel field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfplldivedgesel - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_div_edge_sel_setf(uint8_t wfrfplldivedgesel)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfrfplldivedgesel << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_rfpll_vctrl_detect_en field in the REG_10 register.
 *
 * The REG_10 register will be read and the wf_rfpll_vctrl_detect_en field's value will be returned.
 *
 * @return The current value of the wf_rfpll_vctrl_detect_en field in the REG_10 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_vctrl_detect_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_10_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_rfpll_vctrl_detect_en field of the REG_10 register.
 *
 * The REG_10 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfpllvctrldetecten - The value to set the field to.
 */
__INLINE void wlan_rf_wf_rfpll_vctrl_detect_en_setf(uint8_t wfrfpllvctrldetecten)
{
    REG_PL_WR(WLAN_RF_REG_10_ADDR, (REG_PL_RD(WLAN_RF_REG_10_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfrfpllvctrldetecten << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name REG_11 register definitions
 * <table>
 * <caption id="REG_11_BF">REG_11 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30:14 <td>     wf_rfpll_dout <td>W <td>R <td>0x0
 * <tr><td>13 <td>     wf_rfpll_lock <td>W <td>R <td>0
 * <tr><td>12 <td>     wf_vco_buf_en <td>R <td>R/W <td>1
 * <tr><td>11:00 <td>   wf_vco_band_bit <td>W <td>R <td>0x200
 * </table>
 *
 * @{
 */

/// Address of the REG_11 register
#define WLAN_RF_REG_11_ADDR   0x40344044
/// Offset of the REG_11 register from the base address
#define WLAN_RF_REG_11_OFFSET 0x00000044
/// Index of the REG_11 register
#define WLAN_RF_REG_11_INDEX  0x00000011
/// Reset value of the REG_11 register
#define WLAN_RF_REG_11_RESET  0x00001200

/**
 * @brief Returns the current value of the REG_11 register.
 * The REG_11 register will be read and its value returned.
 * @return The current value of the REG_11 register.
 */
__INLINE uint32_t wlan_rf_reg_11_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_11_ADDR);
}

/**
 * @brief Sets the REG_11 register to a value.
 * The REG_11 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_11_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_11_ADDR, value);
}

// field definitions
/// WF_RFPLL_DOUT field mask
#define WLAN_RF_WF_RFPLL_DOUT_MASK     ((uint32_t)0x7FFFC000)
/// WF_RFPLL_DOUT field LSB position
#define WLAN_RF_WF_RFPLL_DOUT_LSB      14
/// WF_RFPLL_DOUT field width
#define WLAN_RF_WF_RFPLL_DOUT_WIDTH    ((uint32_t)0x00000011)
/// WF_RFPLL_LOCK field bit
#define WLAN_RF_WF_RFPLL_LOCK_BIT      ((uint32_t)0x00002000)
/// WF_RFPLL_LOCK field position
#define WLAN_RF_WF_RFPLL_LOCK_POS      13
/// WF_VCO_BUF_EN field bit
#define WLAN_RF_WF_VCO_BUF_EN_BIT      ((uint32_t)0x00001000)
/// WF_VCO_BUF_EN field position
#define WLAN_RF_WF_VCO_BUF_EN_POS      12
/// WF_VCO_BAND_BIT field mask
#define WLAN_RF_WF_VCO_BAND_BIT_MASK   ((uint32_t)0x00000FFF)
/// WF_VCO_BAND_BIT field LSB position
#define WLAN_RF_WF_VCO_BAND_BIT_LSB    0
/// WF_VCO_BAND_BIT field width
#define WLAN_RF_WF_VCO_BAND_BIT_WIDTH  ((uint32_t)0x0000000C)

/// WF_RFPLL_DOUT field reset value
#define WLAN_RF_WF_RFPLL_DOUT_RST      0x0
/// WF_RFPLL_LOCK field reset value
#define WLAN_RF_WF_RFPLL_LOCK_RST      0x0
/// WF_VCO_BUF_EN field reset value
#define WLAN_RF_WF_VCO_BUF_EN_RST      0x1
/// WF_VCO_BAND_BIT field reset value
#define WLAN_RF_WF_VCO_BAND_BIT_RST    0x200

/**
 * @brief Unpacks REG_11's fields from current value of the REG_11 register.
 *
 * Reads the REG_11 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrfplldout - Will be populated with the current value of this field from the register.
 * @param[out] wfrfplllock - Will be populated with the current value of this field from the register.
 * @param[out] wfvcobufen - Will be populated with the current value of this field from the register.
 * @param[out] wfvcobandbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_11_unpack(uint32_t* wfrfplldout, uint8_t* wfrfplllock, uint8_t* wfvcobufen, uint16_t* wfvcobandbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_11_ADDR);

    *wfrfplldout = (localVal & ((uint32_t)0x7FFFC000)) >> 14;
    *wfrfplllock = (localVal & ((uint32_t)0x00002000)) >> 13;
    *wfvcobufen = (localVal & ((uint32_t)0x00001000)) >> 12;
    *wfvcobandbit = (localVal & ((uint32_t)0x00000FFF)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rfpll_dout field in the REG_11 register.
 *
 * The REG_11 register will be read and the wf_rfpll_dout field's value will be returned.
 *
 * @return The current value of the wf_rfpll_dout field in the REG_11 register.
 */
__INLINE uint32_t wlan_rf_wf_rfpll_dout_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_11_ADDR);
    return ((localVal & ((uint32_t)0x7FFFC000)) >> 14);
}

/**
 * @brief Returns the current value of the wf_rfpll_lock field in the REG_11 register.
 *
 * The REG_11 register will be read and the wf_rfpll_lock field's value will be returned.
 *
 * @return The current value of the wf_rfpll_lock field in the REG_11 register.
 */
__INLINE uint8_t wlan_rf_wf_rfpll_lock_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_11_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Returns the current value of the wf_vco_buf_en field in the REG_11 register.
 *
 * The REG_11 register will be read and the wf_vco_buf_en field's value will be returned.
 *
 * @return The current value of the wf_vco_buf_en field in the REG_11 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_buf_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_11_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the wf_vco_buf_en field of the REG_11 register.
 *
 * The REG_11 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcobufen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_buf_en_setf(uint8_t wfvcobufen)
{
    REG_PL_WR(WLAN_RF_REG_11_ADDR, ((uint32_t)wfvcobufen << 12) & ((uint32_t)0x00001000));
}

/**
 * @brief Returns the current value of the wf_vco_band_bit field in the REG_11 register.
 *
 * The REG_11 register will be read and the wf_vco_band_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_band_bit field in the REG_11 register.
 */
__INLINE uint16_t wlan_rf_wf_vco_band_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_11_ADDR);
    return ((localVal & ((uint32_t)0x00000FFF)) >> 0);
}

/// @}

/**
 * @name REG_12 register definitions
 * <table>
 * <caption id="REG_12_BF">REG_12 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>28:25 <td>wf_vco_band_temp_bit <td>R <td>R/W <td>0x7
 * <tr><td>24:21 <td>wf_vco_core_reg_bit <td>W <td>R <td>0x8
 * <tr><td>20 <td>wf_vco_core_reg_imode <td>R <td>R/W <td>0
 * <tr><td>19:16 <td>wf_vco_buf_reg_bit <td>R <td>R/W <td>0x8
 * <tr><td>15:11 <td>wf_vco_vctrl_biasp_bit <td>R <td>R/W <td>0x19
 * <tr><td>10:06 <td>wf_vco_vctrl_biasn_bit <td>R <td>R/W <td>0x7
 * <tr><td>05 <td> wf_vco_presclo_en <td>R <td>R/W <td>1
 * <tr><td>04 <td>   wf_vco_trx_mode <td>R <td>R/W <td>1
 * <tr><td>03:00 <td>    wf_lo_rsvd_bit <td>R <td>R/W <td>0xC
 * </table>
 *
 * @{
 */

/// Address of the REG_12 register
#define WLAN_RF_REG_12_ADDR   0x40344048
/// Offset of the REG_12 register from the base address
#define WLAN_RF_REG_12_OFFSET 0x00000048
/// Index of the REG_12 register
#define WLAN_RF_REG_12_INDEX  0x00000012
/// Reset value of the REG_12 register
#define WLAN_RF_REG_12_RESET  0x0F08C9FC

/**
 * @brief Returns the current value of the REG_12 register.
 * The REG_12 register will be read and its value returned.
 * @return The current value of the REG_12 register.
 */
__INLINE uint32_t wlan_rf_reg_12_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_12_ADDR);
}

/**
 * @brief Sets the REG_12 register to a value.
 * The REG_12 register will be written.
 * @param value - The value to write.
 */
__INLINE void wlan_rf_reg_12_set(uint32_t value)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR, value);
}

// field definitions
/// WF_VCO_BAND_TEMP_BIT field mask
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_MASK     ((uint32_t)0x1E000000)
/// WF_VCO_BAND_TEMP_BIT field LSB position
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_LSB      25
/// WF_VCO_BAND_TEMP_BIT field width
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_WIDTH    ((uint32_t)0x00000004)
/// WF_VCO_CORE_REG_BIT field mask
#define WLAN_RF_WF_VCO_CORE_REG_BIT_MASK      ((uint32_t)0x01E00000)
/// WF_VCO_CORE_REG_BIT field LSB position
#define WLAN_RF_WF_VCO_CORE_REG_BIT_LSB       21
/// WF_VCO_CORE_REG_BIT field width
#define WLAN_RF_WF_VCO_CORE_REG_BIT_WIDTH     ((uint32_t)0x00000004)
/// WF_VCO_CORE_REG_IMODE field bit
#define WLAN_RF_WF_VCO_CORE_REG_IMODE_BIT     ((uint32_t)0x00100000)
/// WF_VCO_CORE_REG_IMODE field position
#define WLAN_RF_WF_VCO_CORE_REG_IMODE_POS     20
/// WF_VCO_BUF_REG_BIT field mask
#define WLAN_RF_WF_VCO_BUF_REG_BIT_MASK       ((uint32_t)0x000F0000)
/// WF_VCO_BUF_REG_BIT field LSB position
#define WLAN_RF_WF_VCO_BUF_REG_BIT_LSB        16
/// WF_VCO_BUF_REG_BIT field width
#define WLAN_RF_WF_VCO_BUF_REG_BIT_WIDTH      ((uint32_t)0x00000004)
/// WF_VCO_VCTRL_BIASP_BIT field mask
#define WLAN_RF_WF_VCO_VCTRL_BIASP_BIT_MASK   ((uint32_t)0x0000F800)
/// WF_VCO_VCTRL_BIASP_BIT field LSB position
#define WLAN_RF_WF_VCO_VCTRL_BIASP_BIT_LSB    11
/// WF_VCO_VCTRL_BIASP_BIT field width
#define WLAN_RF_WF_VCO_VCTRL_BIASP_BIT_WIDTH  ((uint32_t)0x00000005)
/// WF_VCO_VCTRL_BIASN_BIT field mask
#define WLAN_RF_WF_VCO_VCTRL_BIASN_BIT_MASK   ((uint32_t)0x000007C0)
/// WF_VCO_VCTRL_BIASN_BIT field LSB position
#define WLAN_RF_WF_VCO_VCTRL_BIASN_BIT_LSB    6
/// WF_VCO_VCTRL_BIASN_BIT field width
#define WLAN_RF_WF_VCO_VCTRL_BIASN_BIT_WIDTH  ((uint32_t)0x00000005)
/// WF_VCO_PRESCLO_EN field bit
#define WLAN_RF_WF_VCO_PRESCLO_EN_BIT         ((uint32_t)0x00000020)
/// WF_VCO_PRESCLO_EN field position
#define WLAN_RF_WF_VCO_PRESCLO_EN_POS         5
/// WF_VCO_TRX_MODE field bit
#define WLAN_RF_WF_VCO_TRX_MODE_BIT           ((uint32_t)0x00000010)
/// WF_VCO_TRX_MODE field position
#define WLAN_RF_WF_VCO_TRX_MODE_POS           4
/// WF_LO_RSVD_BIT field mask
#define WLAN_RF_WF_LO_RSVD_BIT_MASK           ((uint32_t)0x0000000F)
/// WF_LO_RSVD_BIT field LSB position
#define WLAN_RF_WF_LO_RSVD_BIT_LSB            0
/// WF_LO_RSVD_BIT field width
#define WLAN_RF_WF_LO_RSVD_BIT_WIDTH          ((uint32_t)0x00000004)

/// WF_VCO_BAND_TEMP_BIT field reset value
#define WLAN_RF_WF_VCO_BAND_TEMP_BIT_RST      0x7
/// WF_VCO_CORE_REG_BIT field reset value
#define WLAN_RF_WF_VCO_CORE_REG_BIT_RST       0x8
/// WF_VCO_CORE_REG_IMODE field reset value
#define WLAN_RF_WF_VCO_CORE_REG_IMODE_RST     0x0
/// WF_VCO_BUF_REG_BIT field reset value
#define WLAN_RF_WF_VCO_BUF_REG_BIT_RST        0x8
/// WF_VCO_VCTRL_BIASP_BIT field reset value
#define WLAN_RF_WF_VCO_VCTRL_BIASP_BIT_RST    0x19
/// WF_VCO_VCTRL_BIASN_BIT field reset value
#define WLAN_RF_WF_VCO_VCTRL_BIASN_BIT_RST    0x7
/// WF_VCO_PRESCLO_EN field reset value
#define WLAN_RF_WF_VCO_PRESCLO_EN_RST         0x1
/// WF_VCO_TRX_MODE field reset value
#define WLAN_RF_WF_VCO_TRX_MODE_RST           0x1
/// WF_LO_RSVD_BIT field reset value
#define WLAN_RF_WF_LO_RSVD_BIT_RST            0xC

/**
 * @brief Constructs a value for the REG_12 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfvcobandtempbit - The value to use for the wf_vco_band_temp_bit field.
 * @param[in] wfvcocoreregimode - The value to use for the wf_vco_core_reg_imode field.
 * @param[in] wfvcobufregbit - The value to use for the wf_vco_buf_reg_bit field.
 * @param[in] wfvcovctrlbiaspbit - The value to use for the wf_vco_vctrl_biasp_bit field.
 * @param[in] wfvcovctrlbiasnbit - The value to use for the wf_vco_vctrl_biasn_bit field.
 * @param[in] wfvcoprescloen - The value to use for the wf_vco_presclo_en field.
 * @param[in] wfvcotrxmode - The value to use for the wf_vco_trx_mode field.
 * @param[in] wflorsvdbit - The value to use for the wf_lo_rsvd_bit field.
 */
__INLINE void wlan_rf_reg_12_pack(uint8_t wfvcobandtempbit, uint8_t wfvcocoreregimode, uint8_t wfvcobufregbit, uint8_t wfvcovctrlbiaspbit, uint8_t wfvcovctrlbiasnbit, uint8_t wfvcoprescloen, uint8_t wfvcotrxmode, uint8_t wflorsvdbit)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR,  ((uint32_t)wfvcobandtempbit << 25) | ((uint32_t)wfvcocoreregimode << 20) | ((uint32_t)wfvcobufregbit << 16) | ((uint32_t)wfvcovctrlbiaspbit << 11) | ((uint32_t)wfvcovctrlbiasnbit << 6) | ((uint32_t)wfvcoprescloen << 5) | ((uint32_t)wfvcotrxmode << 4) | ((uint32_t)wflorsvdbit << 0));
}

/**
 * @brief Unpacks REG_12's fields from current value of the REG_12 register.
 *
 * Reads the REG_12 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfvcobandtempbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcocoreregbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcocoreregimode - Will be populated with the current value of this field from the register.
 * @param[out] wfvcobufregbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcovctrlbiaspbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcovctrlbiasnbit - Will be populated with the current value of this field from the register.
 * @param[out] wfvcoprescloen - Will be populated with the current value of this field from the register.
 * @param[out] wfvcotrxmode - Will be populated with the current value of this field from the register.
 * @param[out] wflorsvdbit - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_12_unpack(uint8_t* wfvcobandtempbit, uint8_t* wfvcocoreregbit, uint8_t* wfvcocoreregimode, uint8_t* wfvcobufregbit, uint8_t* wfvcovctrlbiaspbit, uint8_t* wfvcovctrlbiasnbit, uint8_t* wfvcoprescloen, uint8_t* wfvcotrxmode, uint8_t* wflorsvdbit)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);

    *wfvcobandtempbit = (localVal & ((uint32_t)0x1E000000)) >> 25;
    *wfvcocoreregbit = (localVal & ((uint32_t)0x01E00000)) >> 21;
    *wfvcocoreregimode = (localVal & ((uint32_t)0x00100000)) >> 20;
    *wfvcobufregbit = (localVal & ((uint32_t)0x000F0000)) >> 16;
    *wfvcovctrlbiaspbit = (localVal & ((uint32_t)0x0000F800)) >> 11;
    *wfvcovctrlbiasnbit = (localVal & ((uint32_t)0x000007C0)) >> 6;
    *wfvcoprescloen = (localVal & ((uint32_t)0x00000020)) >> 5;
    *wfvcotrxmode = (localVal & ((uint32_t)0x00000010)) >> 4;
    *wflorsvdbit = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_vco_band_temp_bit field in the REG_12 register.
 *
 * The REG_12 register will be read and the wf_vco_band_temp_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_band_temp_bit field in the REG_12 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_band_temp_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);
    return ((localVal & ((uint32_t)0x1E000000)) >> 25);
}

/**
 * @brief Sets the wf_vco_band_temp_bit field of the REG_12 register.
 *
 * The REG_12 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcobandtempbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_band_temp_bit_setf(uint8_t wfvcobandtempbit)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR, (REG_PL_RD(WLAN_RF_REG_12_ADDR) & ~((uint32_t)0x1E000000)) | (((uint32_t)wfvcobandtempbit << 25) & ((uint32_t)0x1E000000)));
}

/**
 * @brief Returns the current value of the wf_vco_core_reg_bit field in the REG_12 register.
 *
 * The REG_12 register will be read and the wf_vco_core_reg_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_core_reg_bit field in the REG_12 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_core_reg_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);
    return ((localVal & ((uint32_t)0x01E00000)) >> 21);
}

/**
 * @brief Returns the current value of the wf_vco_core_reg_imode field in the REG_12 register.
 *
 * The REG_12 register will be read and the wf_vco_core_reg_imode field's value will be returned.
 *
 * @return The current value of the wf_vco_core_reg_imode field in the REG_12 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_core_reg_imode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

/**
 * @brief Sets the wf_vco_core_reg_imode field of the REG_12 register.
 *
 * The REG_12 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcocoreregimode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_core_reg_imode_setf(uint8_t wfvcocoreregimode)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR, (REG_PL_RD(WLAN_RF_REG_12_ADDR) & ~((uint32_t)0x00100000)) | (((uint32_t)wfvcocoreregimode << 20) & ((uint32_t)0x00100000)));
}

/**
 * @brief Returns the current value of the wf_vco_buf_reg_bit field in the REG_12 register.
 *
 * The REG_12 register will be read and the wf_vco_buf_reg_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_buf_reg_bit field in the REG_12 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_buf_reg_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);
    return ((localVal & ((uint32_t)0x000F0000)) >> 16);
}

/**
 * @brief Sets the wf_vco_buf_reg_bit field of the REG_12 register.
 *
 * The REG_12 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcobufregbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_buf_reg_bit_setf(uint8_t wfvcobufregbit)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR, (REG_PL_RD(WLAN_RF_REG_12_ADDR) & ~((uint32_t)0x000F0000)) | (((uint32_t)wfvcobufregbit << 16) & ((uint32_t)0x000F0000)));
}

/**
 * @brief Returns the current value of the wf_vco_vctrl_biasp_bit field in the REG_12 register.
 *
 * The REG_12 register will be read and the wf_vco_vctrl_biasp_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_vctrl_biasp_bit field in the REG_12 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_vctrl_biasp_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);
    return ((localVal & ((uint32_t)0x0000F800)) >> 11);
}

/**
 * @brief Sets the wf_vco_vctrl_biasp_bit field of the REG_12 register.
 *
 * The REG_12 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcovctrlbiaspbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_vctrl_biasp_bit_setf(uint8_t wfvcovctrlbiaspbit)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR, (REG_PL_RD(WLAN_RF_REG_12_ADDR) & ~((uint32_t)0x0000F800)) | (((uint32_t)wfvcovctrlbiaspbit << 11) & ((uint32_t)0x0000F800)));
}

/**
 * @brief Returns the current value of the wf_vco_vctrl_biasn_bit field in the REG_12 register.
 *
 * The REG_12 register will be read and the wf_vco_vctrl_biasn_bit field's value will be returned.
 *
 * @return The current value of the wf_vco_vctrl_biasn_bit field in the REG_12 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_vctrl_biasn_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);
    return ((localVal & ((uint32_t)0x000007C0)) >> 6);
}

/**
 * @brief Sets the wf_vco_vctrl_biasn_bit field of the REG_12 register.
 *
 * The REG_12 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcovctrlbiasnbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_vctrl_biasn_bit_setf(uint8_t wfvcovctrlbiasnbit)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR, (REG_PL_RD(WLAN_RF_REG_12_ADDR) & ~((uint32_t)0x000007C0)) | (((uint32_t)wfvcovctrlbiasnbit << 6) & ((uint32_t)0x000007C0)));
}

/**
 * @brief Returns the current value of the wf_vco_presclo_en field in the REG_12 register.
 *
 * The REG_12 register will be read and the wf_vco_presclo_en field's value will be returned.
 *
 * @return The current value of the wf_vco_presclo_en field in the REG_12 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_presclo_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the wf_vco_presclo_en field of the REG_12 register.
 *
 * The REG_12 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcoprescloen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_presclo_en_setf(uint8_t wfvcoprescloen)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR, (REG_PL_RD(WLAN_RF_REG_12_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)wfvcoprescloen << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the wf_vco_trx_mode field in the REG_12 register.
 *
 * The REG_12 register will be read and the wf_vco_trx_mode field's value will be returned.
 *
 * @return The current value of the wf_vco_trx_mode field in the REG_12 register.
 */
__INLINE uint8_t wlan_rf_wf_vco_trx_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the wf_vco_trx_mode field of the REG_12 register.
 *
 * The REG_12 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfvcotrxmode - The value to set the field to.
 */
__INLINE void wlan_rf_wf_vco_trx_mode_setf(uint8_t wfvcotrxmode)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR, (REG_PL_RD(WLAN_RF_REG_12_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)wfvcotrxmode << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the wf_lo_rsvd_bit field in the REG_12 register.
 *
 * The REG_12 register will be read and the wf_lo_rsvd_bit field's value will be returned.
 *
 * @return The current value of the wf_lo_rsvd_bit field in the REG_12 register.
 */
__INLINE uint8_t wlan_rf_wf_lo_rsvd_bit_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_12_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the wf_lo_rsvd_bit field of the REG_12 register.
 *
 * The REG_12 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wflorsvdbit - The value to set the field to.
 */
__INLINE void wlan_rf_wf_lo_rsvd_bit_setf(uint8_t wflorsvdbit)
{
    REG_PL_WR(WLAN_RF_REG_12_ADDR, (REG_PL_RD(WLAN_RF_REG_12_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)wflorsvdbit << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name REG_13 register definitions
 * <table>
 * <caption id="REG_13_BF">REG_13 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>15:08 <td>       wf_agc_rsvd <td>W <td>R <td>0xF0
 * <tr><td>07:00 <td>       wf_apc_rsvd <td>W <td>R <td>0xF0
 * </table>
 *
 * @{
 */

/// Address of the REG_13 register
#define WLAN_RF_REG_13_ADDR   0x4034404C
/// Offset of the REG_13 register from the base address
#define WLAN_RF_REG_13_OFFSET 0x0000004C
/// Index of the REG_13 register
#define WLAN_RF_REG_13_INDEX  0x00000013
/// Reset value of the REG_13 register
#define WLAN_RF_REG_13_RESET  0x0000F0F0

/**
 * @brief Returns the current value of the REG_13 register.
 * The REG_13 register will be read and its value returned.
 * @return The current value of the REG_13 register.
 */
__INLINE uint32_t wlan_rf_reg_13_get(void)
{
    return REG_PL_RD(WLAN_RF_REG_13_ADDR);
}

// field definitions
/// WF_AGC_RSVD field mask
#define WLAN_RF_WF_AGC_RSVD_MASK   ((uint32_t)0x0000FF00)
/// WF_AGC_RSVD field LSB position
#define WLAN_RF_WF_AGC_RSVD_LSB    8
/// WF_AGC_RSVD field width
#define WLAN_RF_WF_AGC_RSVD_WIDTH  ((uint32_t)0x00000008)
/// WF_APC_RSVD field mask
#define WLAN_RF_WF_APC_RSVD_MASK   ((uint32_t)0x000000FF)
/// WF_APC_RSVD field LSB position
#define WLAN_RF_WF_APC_RSVD_LSB    0
/// WF_APC_RSVD field width
#define WLAN_RF_WF_APC_RSVD_WIDTH  ((uint32_t)0x00000008)

/// WF_AGC_RSVD field reset value
#define WLAN_RF_WF_AGC_RSVD_RST    0xF0
/// WF_APC_RSVD field reset value
#define WLAN_RF_WF_APC_RSVD_RST    0xF0

/**
 * @brief Unpacks REG_13's fields from current value of the REG_13 register.
 *
 * Reads the REG_13 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfagcrsvd - Will be populated with the current value of this field from the register.
 * @param[out] wfapcrsvd - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_reg_13_unpack(uint8_t* wfagcrsvd, uint8_t* wfapcrsvd)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_13_ADDR);

    *wfagcrsvd = (localVal & ((uint32_t)0x0000FF00)) >> 8;
    *wfapcrsvd = (localVal & ((uint32_t)0x000000FF)) >> 0;
}

/**
 * @brief Returns the current value of the wf_agc_rsvd field in the REG_13 register.
 *
 * The REG_13 register will be read and the wf_agc_rsvd field's value will be returned.
 *
 * @return The current value of the wf_agc_rsvd field in the REG_13 register.
 */
__INLINE uint8_t wlan_rf_wf_agc_rsvd_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_13_ADDR);
    return ((localVal & ((uint32_t)0x0000FF00)) >> 8);
}

/**
 * @brief Returns the current value of the wf_apc_rsvd field in the REG_13 register.
 *
 * The REG_13 register will be read and the wf_apc_rsvd field's value will be returned.
 *
 * @return The current value of the wf_apc_rsvd field in the REG_13 register.
 */
__INLINE uint8_t wlan_rf_wf_apc_rsvd_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_REG_13_ADDR);
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
#define WLAN_RF_WF_SOFT_RESET_REG_ADDR   0x40344050
/// Offset of the WF_SOFT_RESET_REG register from the base address
#define WLAN_RF_WF_SOFT_RESET_REG_OFFSET 0x00000050
/// Index of the WF_SOFT_RESET_REG register
#define WLAN_RF_WF_SOFT_RESET_REG_INDEX  0x00000014
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
 * @name WF_MAN_CTRL_REG register definitions
 * <table>
 * <caption id="WF_MAN_CTRL_REG_BF">WF_MAN_CTRL_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>30 <td> wf_pllon_sleep_en <td>R <td>R/W <td>1
 * <tr><td>29 <td>       rxgain_page <td>R <td>R/W <td>0
 * <tr><td>28 <td>         pllon_trx <td>R <td>R/W <td>1
 * <tr><td>27 <td>         pllon_reg <td>R <td>R/W <td>0
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
#define WLAN_RF_WF_MAN_CTRL_REG_ADDR   0x40344054
/// Offset of the WF_MAN_CTRL_REG register from the base address
#define WLAN_RF_WF_MAN_CTRL_REG_OFFSET 0x00000054
/// Index of the WF_MAN_CTRL_REG register
#define WLAN_RF_WF_MAN_CTRL_REG_INDEX  0x00000015
/// Reset value of the WF_MAN_CTRL_REG register
#define WLAN_RF_WF_MAN_CTRL_REG_RESET  0x51000000

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
/// WF_PLLON_SLEEP_EN field bit
#define WLAN_RF_WF_PLLON_SLEEP_EN_BIT    ((uint32_t)0x40000000)
/// WF_PLLON_SLEEP_EN field position
#define WLAN_RF_WF_PLLON_SLEEP_EN_POS    30
/// RXGAIN_PAGE field bit
#define WLAN_RF_RXGAIN_PAGE_BIT          ((uint32_t)0x20000000)
/// RXGAIN_PAGE field position
#define WLAN_RF_RXGAIN_PAGE_POS          29
/// PLLON_TRX field bit
#define WLAN_RF_PLLON_TRX_BIT            ((uint32_t)0x10000000)
/// PLLON_TRX field position
#define WLAN_RF_PLLON_TRX_POS            28
/// PLLON_REG field bit
#define WLAN_RF_PLLON_REG_BIT            ((uint32_t)0x08000000)
/// PLLON_REG field position
#define WLAN_RF_PLLON_REG_POS            27
/// BTTWS_DR field bit
#define WLAN_RF_BTTWS_DR_BIT             ((uint32_t)0x04000000)
/// BTTWS_DR field position
#define WLAN_RF_BTTWS_DR_POS             26
/// BTTWS_REG field bit
#define WLAN_RF_BTTWS_REG_BIT            ((uint32_t)0x02000000)
/// BTTWS_REG field position
#define WLAN_RF_BTTWS_REG_POS            25
/// BTON_DR field bit
#define WLAN_RF_BTON_DR_BIT              ((uint32_t)0x01000000)
/// BTON_DR field position
#define WLAN_RF_BTON_DR_POS              24
/// BTON_REG field bit
#define WLAN_RF_BTON_REG_BIT             ((uint32_t)0x00800000)
/// BTON_REG field position
#define WLAN_RF_BTON_REG_POS             23
/// TXON_DR field bit
#define WLAN_RF_TXON_DR_BIT              ((uint32_t)0x00400000)
/// TXON_DR field position
#define WLAN_RF_TXON_DR_POS              22
/// TXON_REG field bit
#define WLAN_RF_TXON_REG_BIT             ((uint32_t)0x00200000)
/// TXON_REG field position
#define WLAN_RF_TXON_REG_POS             21
/// RXON_DR field bit
#define WLAN_RF_RXON_DR_BIT              ((uint32_t)0x00100000)
/// RXON_DR field position
#define WLAN_RF_RXON_DR_POS              20
/// RXON_REG field bit
#define WLAN_RF_RXON_REG_BIT             ((uint32_t)0x00080000)
/// RXON_REG field position
#define WLAN_RF_RXON_REG_POS             19
/// RX_GAIN_DR_PULSE field bit
#define WLAN_RF_RX_GAIN_DR_PULSE_BIT     ((uint32_t)0x00040000)
/// RX_GAIN_DR_PULSE field position
#define WLAN_RF_RX_GAIN_DR_PULSE_POS     18
/// RX_GAIN_DR field bit
#define WLAN_RF_RX_GAIN_DR_BIT           ((uint32_t)0x00020000)
/// RX_GAIN_DR field position
#define WLAN_RF_RX_GAIN_DR_POS           17
/// RX_GAIN_REG field mask
#define WLAN_RF_RX_GAIN_REG_MASK         ((uint32_t)0x0001FF00)
/// RX_GAIN_REG field LSB position
#define WLAN_RF_RX_GAIN_REG_LSB          8
/// RX_GAIN_REG field width
#define WLAN_RF_RX_GAIN_REG_WIDTH        ((uint32_t)0x00000009)
/// TX_GAIN_DR_PULSE field bit
#define WLAN_RF_TX_GAIN_DR_PULSE_BIT     ((uint32_t)0x00000080)
/// TX_GAIN_DR_PULSE field position
#define WLAN_RF_TX_GAIN_DR_PULSE_POS     7
/// TX_GAIN_DR field bit
#define WLAN_RF_TX_GAIN_DR_BIT           ((uint32_t)0x00000040)
/// TX_GAIN_DR field position
#define WLAN_RF_TX_GAIN_DR_POS           6
/// TX_GAIN_REG field mask
#define WLAN_RF_TX_GAIN_REG_MASK         ((uint32_t)0x0000003F)
/// TX_GAIN_REG field LSB position
#define WLAN_RF_TX_GAIN_REG_LSB          0
/// TX_GAIN_REG field width
#define WLAN_RF_TX_GAIN_REG_WIDTH        ((uint32_t)0x00000006)

/// WF_PLLON_SLEEP_EN field reset value
#define WLAN_RF_WF_PLLON_SLEEP_EN_RST    0x1
/// RXGAIN_PAGE field reset value
#define WLAN_RF_RXGAIN_PAGE_RST          0x0
/// PLLON_TRX field reset value
#define WLAN_RF_PLLON_TRX_RST            0x1
/// PLLON_REG field reset value
#define WLAN_RF_PLLON_REG_RST            0x0
/// BTTWS_DR field reset value
#define WLAN_RF_BTTWS_DR_RST             0x0
/// BTTWS_REG field reset value
#define WLAN_RF_BTTWS_REG_RST            0x0
/// BTON_DR field reset value
#define WLAN_RF_BTON_DR_RST              0x1
/// BTON_REG field reset value
#define WLAN_RF_BTON_REG_RST             0x0
/// TXON_DR field reset value
#define WLAN_RF_TXON_DR_RST              0x0
/// TXON_REG field reset value
#define WLAN_RF_TXON_REG_RST             0x0
/// RXON_DR field reset value
#define WLAN_RF_RXON_DR_RST              0x0
/// RXON_REG field reset value
#define WLAN_RF_RXON_REG_RST             0x0
/// RX_GAIN_DR_PULSE field reset value
#define WLAN_RF_RX_GAIN_DR_PULSE_RST     0x0
/// RX_GAIN_DR field reset value
#define WLAN_RF_RX_GAIN_DR_RST           0x0
/// RX_GAIN_REG field reset value
#define WLAN_RF_RX_GAIN_REG_RST          0x0
/// TX_GAIN_DR_PULSE field reset value
#define WLAN_RF_TX_GAIN_DR_PULSE_RST     0x0
/// TX_GAIN_DR field reset value
#define WLAN_RF_TX_GAIN_DR_RST           0x0
/// TX_GAIN_REG field reset value
#define WLAN_RF_TX_GAIN_REG_RST          0x0

/**
 * @brief Constructs a value for the WF_MAN_CTRL_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfpllonsleepen - The value to use for the wf_pllon_sleep_en field.
 * @param[in] rxgainpage - The value to use for the rxgain_page field.
 * @param[in] pllontrx - The value to use for the pllon_trx field.
 * @param[in] pllonreg - The value to use for the pllon_reg field.
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
__INLINE void wlan_rf_wf_man_ctrl_reg_pack(uint8_t wfpllonsleepen, uint8_t rxgainpage, uint8_t pllontrx, uint8_t pllonreg, uint8_t bttwsdr, uint8_t bttwsreg, uint8_t btondr, uint8_t btonreg, uint8_t txondr, uint8_t txonreg, uint8_t rxondr, uint8_t rxonreg, uint8_t rxgaindrpulse, uint8_t rxgaindr, uint16_t rxgainreg, uint8_t txgaindrpulse, uint8_t txgaindr, uint8_t txgainreg)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR,  ((uint32_t)wfpllonsleepen << 30) | ((uint32_t)rxgainpage << 29) | ((uint32_t)pllontrx << 28) | ((uint32_t)pllonreg << 27) | ((uint32_t)bttwsdr << 26) | ((uint32_t)bttwsreg << 25) | ((uint32_t)btondr << 24) | ((uint32_t)btonreg << 23) | ((uint32_t)txondr << 22) | ((uint32_t)txonreg << 21) | ((uint32_t)rxondr << 20) | ((uint32_t)rxonreg << 19) | ((uint32_t)rxgaindrpulse << 18) | ((uint32_t)rxgaindr << 17) | ((uint32_t)rxgainreg << 8) | ((uint32_t)txgaindrpulse << 7) | ((uint32_t)txgaindr << 6) | ((uint32_t)txgainreg << 0));
}

/**
 * @brief Unpacks WF_MAN_CTRL_REG's fields from current value of the WF_MAN_CTRL_REG register.
 *
 * Reads the WF_MAN_CTRL_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfpllonsleepen - Will be populated with the current value of this field from the register.
 * @param[out] rxgainpage - Will be populated with the current value of this field from the register.
 * @param[out] pllontrx - Will be populated with the current value of this field from the register.
 * @param[out] pllonreg - Will be populated with the current value of this field from the register.
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
__INLINE void wlan_rf_wf_man_ctrl_reg_unpack(uint8_t* wfpllonsleepen, uint8_t* rxgainpage, uint8_t* pllontrx, uint8_t* pllonreg, uint8_t* bttwsdr, uint8_t* bttwsreg, uint8_t* btondr, uint8_t* btonreg, uint8_t* txondr, uint8_t* txonreg, uint8_t* rxondr, uint8_t* rxonreg, uint8_t* rxgaindrpulse, uint8_t* rxgaindr, uint16_t* rxgainreg, uint8_t* txgaindrpulse, uint8_t* txgaindr, uint8_t* txgainreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);

    *wfpllonsleepen = (localVal & ((uint32_t)0x40000000)) >> 30;
    *rxgainpage = (localVal & ((uint32_t)0x20000000)) >> 29;
    *pllontrx = (localVal & ((uint32_t)0x10000000)) >> 28;
    *pllonreg = (localVal & ((uint32_t)0x08000000)) >> 27;
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
 * @brief Returns the current value of the wf_pllon_sleep_en field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the wf_pllon_sleep_en field's value will be returned.
 *
 * @return The current value of the wf_pllon_sleep_en field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_pllon_sleep_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the wf_pllon_sleep_en field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfpllonsleepen - The value to set the field to.
 */
__INLINE void wlan_rf_wf_pllon_sleep_en_setf(uint8_t wfpllonsleepen)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)wfpllonsleepen << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the rxgain_page field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the rxgain_page field's value will be returned.
 *
 * @return The current value of the rxgain_page field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_rxgain_page_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the rxgain_page field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] rxgainpage - The value to set the field to.
 */
__INLINE void wlan_rf_rxgain_page_setf(uint8_t rxgainpage)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)rxgainpage << 29) & ((uint32_t)0x20000000)));
}

/**
 * @brief Returns the current value of the pllon_trx field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the pllon_trx field's value will be returned.
 *
 * @return The current value of the pllon_trx field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_pllon_trx_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

/**
 * @brief Sets the pllon_trx field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] pllontrx - The value to set the field to.
 */
__INLINE void wlan_rf_pllon_trx_setf(uint8_t pllontrx)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x10000000)) | (((uint32_t)pllontrx << 28) & ((uint32_t)0x10000000)));
}

/**
 * @brief Returns the current value of the pllon_reg field in the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read and the pllon_reg field's value will be returned.
 *
 * @return The current value of the pllon_reg field in the WF_MAN_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_pllon_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

/**
 * @brief Sets the pllon_reg field of the WF_MAN_CTRL_REG register.
 *
 * The WF_MAN_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] pllonreg - The value to set the field to.
 */
__INLINE void wlan_rf_pllon_reg_setf(uint8_t pllonreg)
{
    REG_PL_WR(WLAN_RF_WF_MAN_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_MAN_CTRL_REG_ADDR) & ~((uint32_t)0x08000000)) | (((uint32_t)pllonreg << 27) & ((uint32_t)0x08000000)));
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
 * <tr><td>26 <td>      debug_clk_en <td>R <td>R/W <td>0
 * <tr><td>25:24 <td>         debug_mux <td>R <td>R/W <td>0x0
 * <tr><td>23 <td>     vco_loen_ctrl <td>R <td>R/W <td>0
 * <tr><td>22:17 <td>cal_clk_div_num_p2 <td>R <td>R/W <td>0x13
 * <tr><td>16:11 <td>cal_clk_div_num_p1 <td>R <td>R/W <td>0x6
 * <tr><td>10 <td>        cal_clk_en <td>R <td>R/W <td>0
 * <tr><td>09:00 <td>   cal_clk_div_num <td>R <td>R/W <td>0x18F
 * </table>
 *
 * @{
 */

/// Address of the WF_CALCLK_REG register
#define WLAN_RF_WF_CALCLK_REG_ADDR   0x40344058
/// Offset of the WF_CALCLK_REG register from the base address
#define WLAN_RF_WF_CALCLK_REG_OFFSET 0x00000058
/// Index of the WF_CALCLK_REG register
#define WLAN_RF_WF_CALCLK_REG_INDEX  0x00000016
/// Reset value of the WF_CALCLK_REG register
#define WLAN_RF_WF_CALCLK_REG_RESET  0x0026318F

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
/// DEBUG_CLK_EN field bit
#define WLAN_RF_DEBUG_CLK_EN_BIT           ((uint32_t)0x04000000)
/// DEBUG_CLK_EN field position
#define WLAN_RF_DEBUG_CLK_EN_POS           26
/// DEBUG_MUX field mask
#define WLAN_RF_DEBUG_MUX_MASK             ((uint32_t)0x03000000)
/// DEBUG_MUX field LSB position
#define WLAN_RF_DEBUG_MUX_LSB              24
/// DEBUG_MUX field width
#define WLAN_RF_DEBUG_MUX_WIDTH            ((uint32_t)0x00000002)
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

/// DEBUG_CLK_EN field reset value
#define WLAN_RF_DEBUG_CLK_EN_RST           0x0
/// DEBUG_MUX field reset value
#define WLAN_RF_DEBUG_MUX_RST              0x0
/// VCO_LOEN_CTRL field reset value
#define WLAN_RF_VCO_LOEN_CTRL_RST          0x0
/// CAL_CLK_DIV_NUM_P_2 field reset value
#define WLAN_RF_CAL_CLK_DIV_NUM_P_2_RST    0x13
/// CAL_CLK_DIV_NUM_P_1 field reset value
#define WLAN_RF_CAL_CLK_DIV_NUM_P_1_RST    0x6
/// CAL_CLK_EN field reset value
#define WLAN_RF_CAL_CLK_EN_RST             0x0
/// CAL_CLK_DIV_NUM field reset value
#define WLAN_RF_CAL_CLK_DIV_NUM_RST        0x18F

/**
 * @brief Constructs a value for the WF_CALCLK_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] debugclken - The value to use for the debug_clk_en field.
 * @param[in] debugmux - The value to use for the debug_mux field.
 * @param[in] vcoloenctrl - The value to use for the vco_loen_ctrl field.
 * @param[in] calclkdivnump2 - The value to use for the cal_clk_div_num_p2 field.
 * @param[in] calclkdivnump1 - The value to use for the cal_clk_div_num_p1 field.
 * @param[in] calclken - The value to use for the cal_clk_en field.
 * @param[in] calclkdivnum - The value to use for the cal_clk_div_num field.
 */
__INLINE void wlan_rf_wf_calclk_reg_pack(uint8_t debugclken, uint8_t debugmux, uint8_t vcoloenctrl, uint8_t calclkdivnump2, uint8_t calclkdivnump1, uint8_t calclken, uint16_t calclkdivnum)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR,  ((uint32_t)debugclken << 26) | ((uint32_t)debugmux << 24) | ((uint32_t)vcoloenctrl << 23) | ((uint32_t)calclkdivnump2 << 17) | ((uint32_t)calclkdivnump1 << 11) | ((uint32_t)calclken << 10) | ((uint32_t)calclkdivnum << 0));
}

/**
 * @brief Unpacks WF_CALCLK_REG's fields from current value of the WF_CALCLK_REG register.
 *
 * Reads the WF_CALCLK_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] debugclken - Will be populated with the current value of this field from the register.
 * @param[out] debugmux - Will be populated with the current value of this field from the register.
 * @param[out] vcoloenctrl - Will be populated with the current value of this field from the register.
 * @param[out] calclkdivnump2 - Will be populated with the current value of this field from the register.
 * @param[out] calclkdivnump1 - Will be populated with the current value of this field from the register.
 * @param[out] calclken - Will be populated with the current value of this field from the register.
 * @param[out] calclkdivnum - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_wf_calclk_reg_unpack(uint8_t* debugclken, uint8_t* debugmux, uint8_t* vcoloenctrl, uint8_t* calclkdivnump2, uint8_t* calclkdivnump1, uint8_t* calclken, uint16_t* calclkdivnum)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);

    *debugclken = (localVal & ((uint32_t)0x04000000)) >> 26;
    *debugmux = (localVal & ((uint32_t)0x03000000)) >> 24;
    *vcoloenctrl = (localVal & ((uint32_t)0x00800000)) >> 23;
    *calclkdivnump2 = (localVal & ((uint32_t)0x007E0000)) >> 17;
    *calclkdivnump1 = (localVal & ((uint32_t)0x0001F800)) >> 11;
    *calclken = (localVal & ((uint32_t)0x00000400)) >> 10;
    *calclkdivnum = (localVal & ((uint32_t)0x000003FF)) >> 0;
}

/**
 * @brief Returns the current value of the debug_clk_en field in the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read and the debug_clk_en field's value will be returned.
 *
 * @return The current value of the debug_clk_en field in the WF_CALCLK_REG register.
 */
__INLINE uint8_t wlan_rf_debug_clk_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

/**
 * @brief Sets the debug_clk_en field of the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] debugclken - The value to set the field to.
 */
__INLINE void wlan_rf_debug_clk_en_setf(uint8_t debugclken)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR) & ~((uint32_t)0x04000000)) | (((uint32_t)debugclken << 26) & ((uint32_t)0x04000000)));
}

/**
 * @brief Returns the current value of the debug_mux field in the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read and the debug_mux field's value will be returned.
 *
 * @return The current value of the debug_mux field in the WF_CALCLK_REG register.
 */
__INLINE uint8_t wlan_rf_debug_mux_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

/**
 * @brief Sets the debug_mux field of the WF_CALCLK_REG register.
 *
 * The WF_CALCLK_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] debugmux - The value to set the field to.
 */
__INLINE void wlan_rf_debug_mux_setf(uint8_t debugmux)
{
    REG_PL_WR(WLAN_RF_WF_CALCLK_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_CALCLK_REG_ADDR) & ~((uint32_t)0x03000000)) | (((uint32_t)debugmux << 24) & ((uint32_t)0x03000000)));
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
#define WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR   0x4034405C
/// Offset of the WF_EXT_TRXON_DELAY_REG register from the base address
#define WLAN_RF_WF_EXT_TRXON_DELAY_REG_OFFSET 0x0000005C
/// Index of the WF_EXT_TRXON_DELAY_REG register
#define WLAN_RF_WF_EXT_TRXON_DELAY_REG_INDEX  0x00000017
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
 * @param[in] extrxondelay - The value to use for the ext_rxon_delay field.
 * @param[in] exttxondelay - The value to use for the ext_txon_delay field.
 * @param[in] extparxctrlreg - The value to use for the ext_pa_rx_ctrl_reg field.
 * @param[in] extpatxctrlreg - The value to use for the ext_pa_tx_ctrl_reg field.
 * @param[in] extpaidlectrlreg - The value to use for the ext_pa_idle_ctrl_reg field.
 */
__INLINE void wlan_rf_wf_ext_trxon_delay_reg_pack(uint16_t extrxondelay, uint16_t exttxondelay, uint8_t extparxctrlreg, uint8_t extpatxctrlreg, uint8_t extpaidlectrlreg)
{
    REG_PL_WR(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR,  ((uint32_t)extrxondelay << 21) | ((uint32_t)exttxondelay << 12) | ((uint32_t)extparxctrlreg << 8) | ((uint32_t)extpatxctrlreg << 4) | ((uint32_t)extpaidlectrlreg << 0));
}

/**
 * @brief Unpacks WF_EXT_TRXON_DELAY_REG's fields from current value of the WF_EXT_TRXON_DELAY_REG register.
 *
 * Reads the WF_EXT_TRXON_DELAY_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] extrxondelay - Will be populated with the current value of this field from the register.
 * @param[out] exttxondelay - Will be populated with the current value of this field from the register.
 * @param[out] extparxctrlreg - Will be populated with the current value of this field from the register.
 * @param[out] extpatxctrlreg - Will be populated with the current value of this field from the register.
 * @param[out] extpaidlectrlreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_wf_ext_trxon_delay_reg_unpack(uint16_t* extrxondelay, uint16_t* exttxondelay, uint8_t* extparxctrlreg, uint8_t* extpatxctrlreg, uint8_t* extpaidlectrlreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_EXT_TRXON_DELAY_REG_ADDR);

    *extrxondelay = (localVal & ((uint32_t)0x3FE00000)) >> 21;
    *exttxondelay = (localVal & ((uint32_t)0x001FF000)) >> 12;
    *extparxctrlreg = (localVal & ((uint32_t)0x00000F00)) >> 8;
    *extpatxctrlreg = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *extpaidlectrlreg = (localVal & ((uint32_t)0x0000000F)) >> 0;
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
#define WLAN_RF_GAIN_MEM_CTRL_REG_ADDR   0x40344060
/// Offset of the GAIN_MEM_CTRL_REG register from the base address
#define WLAN_RF_GAIN_MEM_CTRL_REG_OFFSET 0x00000060
/// Index of the GAIN_MEM_CTRL_REG register
#define WLAN_RF_GAIN_MEM_CTRL_REG_INDEX  0x00000018
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
#define WLAN_RF_GAIN_MEM_FETCH_REG_ADDR   0x40344064
/// Offset of the GAIN_MEM_FETCH_REG register from the base address
#define WLAN_RF_GAIN_MEM_FETCH_REG_OFFSET 0x00000064
/// Index of the GAIN_MEM_FETCH_REG register
#define WLAN_RF_GAIN_MEM_FETCH_REG_INDEX  0x00000019
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
 * <tr><td>03 <td>wf_tia_gain_bit_dr <td>R <td>R/W <td>0
 * <tr><td>02:00 <td>wf_tia_gain_bit_reg <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the WF_DPD_TXCAL_CTRL_REG register
#define WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR   0x40344068
/// Offset of the WF_DPD_TXCAL_CTRL_REG register from the base address
#define WLAN_RF_WF_DPD_TXCAL_CTRL_REG_OFFSET 0x00000068
/// Index of the WF_DPD_TXCAL_CTRL_REG register
#define WLAN_RF_WF_DPD_TXCAL_CTRL_REG_INDEX  0x0000001A
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
/// WF_TIA_GAIN_BIT_DR field bit
#define WLAN_RF_WF_TIA_GAIN_BIT_DR_BIT     ((uint32_t)0x00000008)
/// WF_TIA_GAIN_BIT_DR field position
#define WLAN_RF_WF_TIA_GAIN_BIT_DR_POS     3
/// WF_TIA_GAIN_BIT_REG field mask
#define WLAN_RF_WF_TIA_GAIN_BIT_REG_MASK   ((uint32_t)0x00000007)
/// WF_TIA_GAIN_BIT_REG field LSB position
#define WLAN_RF_WF_TIA_GAIN_BIT_REG_LSB    0
/// WF_TIA_GAIN_BIT_REG field width
#define WLAN_RF_WF_TIA_GAIN_BIT_REG_WIDTH  ((uint32_t)0x00000003)

/// WF_RXFLT_GBIT_2_DR field reset value
#define WLAN_RF_WF_RXFLT_GBIT_2_DR_RST     0x0
/// WF_RXFLT_GBIT_2_REG field reset value
#define WLAN_RF_WF_RXFLT_GBIT_2_REG_RST    0x0
/// WF_RXFLT_GBIT_1_DR field reset value
#define WLAN_RF_WF_RXFLT_GBIT_1_DR_RST     0x0
/// WF_RXFLT_GBIT_1_REG field reset value
#define WLAN_RF_WF_RXFLT_GBIT_1_REG_RST    0x0
/// WF_TIA_GAIN_BIT_DR field reset value
#define WLAN_RF_WF_TIA_GAIN_BIT_DR_RST     0x0
/// WF_TIA_GAIN_BIT_REG field reset value
#define WLAN_RF_WF_TIA_GAIN_BIT_REG_RST    0x0

/**
 * @brief Constructs a value for the WF_DPD_TXCAL_CTRL_REG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrxfltgbit2dr - The value to use for the wf_rxflt_gbit2_dr field.
 * @param[in] wfrxfltgbit2reg - The value to use for the wf_rxflt_gbit2_reg field.
 * @param[in] wfrxfltgbit1dr - The value to use for the wf_rxflt_gbit1_dr field.
 * @param[in] wfrxfltgbit1reg - The value to use for the wf_rxflt_gbit1_reg field.
 * @param[in] wftiagainbitdr - The value to use for the wf_tia_gain_bit_dr field.
 * @param[in] wftiagainbitreg - The value to use for the wf_tia_gain_bit_reg field.
 */
__INLINE void wlan_rf_wf_dpd_txcal_ctrl_reg_pack(uint8_t wfrxfltgbit2dr, uint8_t wfrxfltgbit2reg, uint8_t wfrxfltgbit1dr, uint8_t wfrxfltgbit1reg, uint8_t wftiagainbitdr, uint8_t wftiagainbitreg)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR,  ((uint32_t)wfrxfltgbit2dr << 10) | ((uint32_t)wfrxfltgbit2reg << 8) | ((uint32_t)wfrxfltgbit1dr << 7) | ((uint32_t)wfrxfltgbit1reg << 4) | ((uint32_t)wftiagainbitdr << 3) | ((uint32_t)wftiagainbitreg << 0));
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
 * @param[out] wftiagainbitdr - Will be populated with the current value of this field from the register.
 * @param[out] wftiagainbitreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_wf_dpd_txcal_ctrl_reg_unpack(uint8_t* wfrxfltgbit2dr, uint8_t* wfrxfltgbit2reg, uint8_t* wfrxfltgbit1dr, uint8_t* wfrxfltgbit1reg, uint8_t* wftiagainbitdr, uint8_t* wftiagainbitreg)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);

    *wfrxfltgbit2dr = (localVal & ((uint32_t)0x00000400)) >> 10;
    *wfrxfltgbit2reg = (localVal & ((uint32_t)0x00000300)) >> 8;
    *wfrxfltgbit1dr = (localVal & ((uint32_t)0x00000080)) >> 7;
    *wfrxfltgbit1reg = (localVal & ((uint32_t)0x00000070)) >> 4;
    *wftiagainbitdr = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wftiagainbitreg = (localVal & ((uint32_t)0x00000007)) >> 0;
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
 * @brief Returns the current value of the wf_tia_gain_bit_dr field in the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read and the wf_tia_gain_bit_dr field's value will be returned.
 *
 * @return The current value of the wf_tia_gain_bit_dr field in the WF_DPD_TXCAL_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_tia_gain_bit_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wf_tia_gain_bit_dr field of the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiagainbitdr - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_gain_bit_dr_setf(uint8_t wftiagainbitdr)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wftiagainbitdr << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wf_tia_gain_bit_reg field in the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read and the wf_tia_gain_bit_reg field's value will be returned.
 *
 * @return The current value of the wf_tia_gain_bit_reg field in the WF_DPD_TXCAL_CTRL_REG register.
 */
__INLINE uint8_t wlan_rf_wf_tia_gain_bit_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

/**
 * @brief Sets the wf_tia_gain_bit_reg field of the WF_DPD_TXCAL_CTRL_REG register.
 *
 * The WF_DPD_TXCAL_CTRL_REG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wftiagainbitreg - The value to set the field to.
 */
__INLINE void wlan_rf_wf_tia_gain_bit_reg_setf(uint8_t wftiagainbitreg)
{
    REG_PL_WR(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR, (REG_PL_RD(WLAN_RF_WF_DPD_TXCAL_CTRL_REG_ADDR) & ~((uint32_t)0x00000007)) | (((uint32_t)wftiagainbitreg << 0) & ((uint32_t)0x00000007)));
}

/// @}

/**
 * @name PU_DONE_REG register definitions
 * <table>
 * <caption id="PU_DONE_REG_BF">PU_DONE_REG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>02 <td>        pllon_done <td>W <td>R <td>0
 * <tr><td>01 <td>         rxon_done <td>W <td>R <td>0
 * <tr><td>00 <td>         txon_done <td>W <td>R <td>0
 * </table>
 *
 * @{
 */

/// Address of the PU_DONE_REG register
#define WLAN_RF_PU_DONE_REG_ADDR   0x4034406C
/// Offset of the PU_DONE_REG register from the base address
#define WLAN_RF_PU_DONE_REG_OFFSET 0x0000006C
/// Index of the PU_DONE_REG register
#define WLAN_RF_PU_DONE_REG_INDEX  0x0000001B
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
#define WLAN_RF_PLLON_DONE_BIT    ((uint32_t)0x00000004)
/// PLLON_DONE field position
#define WLAN_RF_PLLON_DONE_POS    2
/// RXON_DONE field bit
#define WLAN_RF_RXON_DONE_BIT     ((uint32_t)0x00000002)
/// RXON_DONE field position
#define WLAN_RF_RXON_DONE_POS     1
/// TXON_DONE field bit
#define WLAN_RF_TXON_DONE_BIT     ((uint32_t)0x00000001)
/// TXON_DONE field position
#define WLAN_RF_TXON_DONE_POS     0

/// PLLON_DONE field reset value
#define WLAN_RF_PLLON_DONE_RST    0x0
/// RXON_DONE field reset value
#define WLAN_RF_RXON_DONE_RST     0x0
/// TXON_DONE field reset value
#define WLAN_RF_TXON_DONE_RST     0x0

/**
 * @brief Unpacks PU_DONE_REG's fields from current value of the PU_DONE_REG register.
 *
 * Reads the PU_DONE_REG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] pllondone - Will be populated with the current value of this field from the register.
 * @param[out] rxondone - Will be populated with the current value of this field from the register.
 * @param[out] txondone - Will be populated with the current value of this field from the register.
 */
__INLINE void wlan_rf_pu_done_reg_unpack(uint8_t* pllondone, uint8_t* rxondone, uint8_t* txondone)
{
    uint32_t localVal = REG_PL_RD(WLAN_RF_PU_DONE_REG_ADDR);

    *pllondone = (localVal & ((uint32_t)0x00000004)) >> 2;
    *rxondone = (localVal & ((uint32_t)0x00000002)) >> 1;
    *txondone = (localVal & ((uint32_t)0x00000001)) >> 0;
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
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
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
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
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
#define WLAN_RF_DIG_RESERVED_REG_ADDR   0x40344070
/// Offset of the DIG_RESERVED_REG register from the base address
#define WLAN_RF_DIG_RESERVED_REG_OFFSET 0x00000070
/// Index of the DIG_RESERVED_REG register
#define WLAN_RF_DIG_RESERVED_REG_INDEX  0x0000001C
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
 * @name AGC_TABLE_OUT_REG0 register definitions
 * <table>
 * <caption id="AGC_TABLE_OUT_REG0_BF">AGC_TABLE_OUT_REG0 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   agc_table_out_0 <td>W <td>R <td>0x8F925146
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG0 register
#define WLAN_RF_AGC_TABLE_OUT_REG0_ADDR   0x40344074
/// Offset of the AGC_TABLE_OUT_REG0 register from the base address
#define WLAN_RF_AGC_TABLE_OUT_REG0_OFFSET 0x00000074
/// Index of the AGC_TABLE_OUT_REG0 register
#define WLAN_RF_AGC_TABLE_OUT_REG0_INDEX  0x0000001D
/// Reset value of the AGC_TABLE_OUT_REG0 register
#define WLAN_RF_AGC_TABLE_OUT_REG0_RESET  0x8F925146

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
#define WLAN_RF_AGC_TABLE_OUT__0_RST    0x8F925146

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
 * <tr><td>31:00 <td>   agc_table_out_1 <td>W <td>R <td>0x920000C8
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG1 register
#define WLAN_RF_AGC_TABLE_OUT_REG1_ADDR   0x40344078
/// Offset of the AGC_TABLE_OUT_REG1 register from the base address
#define WLAN_RF_AGC_TABLE_OUT_REG1_OFFSET 0x00000078
/// Index of the AGC_TABLE_OUT_REG1 register
#define WLAN_RF_AGC_TABLE_OUT_REG1_INDEX  0x0000001E
/// Reset value of the AGC_TABLE_OUT_REG1 register
#define WLAN_RF_AGC_TABLE_OUT_REG1_RESET  0x920000C8

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
#define WLAN_RF_AGC_TABLE_OUT__1_RST    0x920000C8

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
 * <tr><td>31:00 <td>   agc_table_out_2 <td>W <td>R <td>0x80808419
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG2 register
#define WLAN_RF_AGC_TABLE_OUT_REG2_ADDR   0x4034407C
/// Offset of the AGC_TABLE_OUT_REG2 register from the base address
#define WLAN_RF_AGC_TABLE_OUT_REG2_OFFSET 0x0000007C
/// Index of the AGC_TABLE_OUT_REG2 register
#define WLAN_RF_AGC_TABLE_OUT_REG2_INDEX  0x0000001F
/// Reset value of the AGC_TABLE_OUT_REG2 register
#define WLAN_RF_AGC_TABLE_OUT_REG2_RESET  0x80808419

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
#define WLAN_RF_AGC_TABLE_OUT__2_RST    0x80808419

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
 * <tr><td>31:00 <td>   agc_table_out_3 <td>W <td>R <td>0xF0
 * </table>
 *
 * @{
 */

/// Address of the AGC_TABLE_OUT_REG3 register
#define WLAN_RF_AGC_TABLE_OUT_REG3_ADDR   0x40344080
/// Offset of the AGC_TABLE_OUT_REG3 register from the base address
#define WLAN_RF_AGC_TABLE_OUT_REG3_OFFSET 0x00000080
/// Index of the AGC_TABLE_OUT_REG3 register
#define WLAN_RF_AGC_TABLE_OUT_REG3_INDEX  0x00000020
/// Reset value of the AGC_TABLE_OUT_REG3 register
#define WLAN_RF_AGC_TABLE_OUT_REG3_RESET  0x000000F0

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
#define WLAN_RF_AGC_TABLE_OUT__3_RST    0xF0

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
 * @name APC_TABLE_OUT_REG0 register definitions
 * <table>
 * <caption id="APC_TABLE_OUT_REG0_BF">APC_TABLE_OUT_REG0 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>   apc_table_out_0 <td>W <td>R <td>0xBC92203F
 * </table>
 *
 * @{
 */

/// Address of the APC_TABLE_OUT_REG0 register
#define WLAN_RF_APC_TABLE_OUT_REG0_ADDR   0x40344084
/// Offset of the APC_TABLE_OUT_REG0 register from the base address
#define WLAN_RF_APC_TABLE_OUT_REG0_OFFSET 0x00000084
/// Index of the APC_TABLE_OUT_REG0 register
#define WLAN_RF_APC_TABLE_OUT_REG0_INDEX  0x00000021
/// Reset value of the APC_TABLE_OUT_REG0 register
#define WLAN_RF_APC_TABLE_OUT_REG0_RESET  0xBC92203F

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
#define WLAN_RF_APC_TABLE_OUT__0_RST    0xBC92203F

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
 * <tr><td>31:00 <td>   apc_table_out_1 <td>W <td>R <td>0x4025
 * </table>
 *
 * @{
 */

/// Address of the APC_TABLE_OUT_REG1 register
#define WLAN_RF_APC_TABLE_OUT_REG1_ADDR   0x40344088
/// Offset of the APC_TABLE_OUT_REG1 register from the base address
#define WLAN_RF_APC_TABLE_OUT_REG1_OFFSET 0x00000088
/// Index of the APC_TABLE_OUT_REG1 register
#define WLAN_RF_APC_TABLE_OUT_REG1_INDEX  0x00000022
/// Reset value of the APC_TABLE_OUT_REG1 register
#define WLAN_RF_APC_TABLE_OUT_REG1_RESET  0x00004025

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
#define WLAN_RF_APC_TABLE_OUT__1_RST    0x4025

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


#endif // _REG_WLAN_RF_H_

/// @}

