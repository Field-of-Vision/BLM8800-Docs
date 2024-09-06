/**
 * @file reg_wcnaon.h
 * @brief Definitions of the WCNAON HW block registers and register access functions.
 *
 * @defgroup REG_WCNAON REG_WCNAON
 * @ingroup REG
 * @{
 *
 * @brief Definitions of the WCNAON HW block registers and register access functions.
 */
#ifndef _REG_WCNAON_H_
#define _REG_WCNAON_H_

#include "compiler.h"
#include "arch.h"
#include "reg_access.h"

/** @brief Number of registers in the REG_WCNAON peripheral.
 */
#define REG_WCNAON_COUNT 20

/** @brief Decoding mask of the REG_WCNAON peripheral registers from the CPU point of view.
 */
#define REG_WCNAON_DECODING_MASK 0x0000007F

/**
 * @name BT_MEM_CFG1 register definitions
 * <table>
 * <caption id="BT_MEM_CFG1_BF">BT_MEM_CFG1 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>20:17 <td>            bt_cfg <td>R <td>R/W <td>0x1
 * <tr><td>16 <td>      btfw_lp_mode <td>R <td>R/W <td>0
 * <tr><td>15:00 <td>        bt_mem_cfg <td>R <td>R/W <td>0x220
 * </table>
 *
 * @{
 */

/// Address of the BT_MEM_CFG1 register
#define WCNAON_BT_MEM_CFG1_ADDR   0x40509000
/// Offset of the BT_MEM_CFG1 register from the base address
#define WCNAON_BT_MEM_CFG1_OFFSET 0x00000000
/// Index of the BT_MEM_CFG1 register
#define WCNAON_BT_MEM_CFG1_INDEX  0x00000000
/// Reset value of the BT_MEM_CFG1 register
#define WCNAON_BT_MEM_CFG1_RESET  0x00020220

/**
 * @brief Returns the current value of the BT_MEM_CFG1 register.
 * The BT_MEM_CFG1 register will be read and its value returned.
 * @return The current value of the BT_MEM_CFG1 register.
 */
__INLINE uint32_t wcnaon_bt_mem_cfg1_get(void)
{
    return REG_PL_RD(WCNAON_BT_MEM_CFG1_ADDR);
}

/**
 * @brief Sets the BT_MEM_CFG1 register to a value.
 * The BT_MEM_CFG1 register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_bt_mem_cfg1_set(uint32_t value)
{
    REG_PL_WR(WCNAON_BT_MEM_CFG1_ADDR, value);
}

// field definitions
/// BT_CFG field mask
#define WCNAON_BT_CFG_MASK         ((uint32_t)0x001E0000)
/// BT_CFG field LSB position
#define WCNAON_BT_CFG_LSB          17
/// BT_CFG field width
#define WCNAON_BT_CFG_WIDTH        ((uint32_t)0x00000004)
/// BTFW_LP_MODE field bit
#define WCNAON_BTFW_LP_MODE_BIT    ((uint32_t)0x00010000)
/// BTFW_LP_MODE field position
#define WCNAON_BTFW_LP_MODE_POS    16
/// BT_MEM_CFG field mask
#define WCNAON_BT_MEM_CFG_MASK     ((uint32_t)0x0000FFFF)
/// BT_MEM_CFG field LSB position
#define WCNAON_BT_MEM_CFG_LSB      0
/// BT_MEM_CFG field width
#define WCNAON_BT_MEM_CFG_WIDTH    ((uint32_t)0x00000010)

/// BT_CFG field reset value
#define WCNAON_BT_CFG_RST          0x1
/// BTFW_LP_MODE field reset value
#define WCNAON_BTFW_LP_MODE_RST    0x0
/// BT_MEM_CFG field reset value
#define WCNAON_BT_MEM_CFG_RST      0x220

/**
 * @brief Constructs a value for the BT_MEM_CFG1 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btcfg - The value to use for the bt_cfg field.
 * @param[in] btfwlpmode - The value to use for the btfw_lp_mode field.
 * @param[in] btmemcfg - The value to use for the bt_mem_cfg field.
 */
__INLINE void wcnaon_bt_mem_cfg1_pack(uint8_t btcfg, uint8_t btfwlpmode, uint16_t btmemcfg)
{
    REG_PL_WR(WCNAON_BT_MEM_CFG1_ADDR,  ((uint32_t)btcfg << 17) | ((uint32_t)btfwlpmode << 16) | ((uint32_t)btmemcfg << 0));
}

/**
 * @brief Unpacks BT_MEM_CFG1's fields from current value of the BT_MEM_CFG1 register.
 *
 * Reads the BT_MEM_CFG1 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btcfg - Will be populated with the current value of this field from the register.
 * @param[out] btfwlpmode - Will be populated with the current value of this field from the register.
 * @param[out] btmemcfg - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_bt_mem_cfg1_unpack(uint8_t* btcfg, uint8_t* btfwlpmode, uint16_t* btmemcfg)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_MEM_CFG1_ADDR);

    *btcfg = (localVal & ((uint32_t)0x001E0000)) >> 17;
    *btfwlpmode = (localVal & ((uint32_t)0x00010000)) >> 16;
    *btmemcfg = (localVal & ((uint32_t)0x0000FFFF)) >> 0;
}

/**
 * @brief Returns the current value of the bt_cfg field in the BT_MEM_CFG1 register.
 *
 * The BT_MEM_CFG1 register will be read and the bt_cfg field's value will be returned.
 *
 * @return The current value of the bt_cfg field in the BT_MEM_CFG1 register.
 */
__INLINE uint8_t wcnaon_bt_cfg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_MEM_CFG1_ADDR);
    return ((localVal & ((uint32_t)0x001E0000)) >> 17);
}

/**
 * @brief Sets the bt_cfg field of the BT_MEM_CFG1 register.
 *
 * The BT_MEM_CFG1 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btcfg - The value to set the field to.
 */
__INLINE void wcnaon_bt_cfg_setf(uint8_t btcfg)
{
    REG_PL_WR(WCNAON_BT_MEM_CFG1_ADDR, (REG_PL_RD(WCNAON_BT_MEM_CFG1_ADDR) & ~((uint32_t)0x001E0000)) | (((uint32_t)btcfg << 17) & ((uint32_t)0x001E0000)));
}

/**
 * @brief Returns the current value of the btfw_lp_mode field in the BT_MEM_CFG1 register.
 *
 * The BT_MEM_CFG1 register will be read and the btfw_lp_mode field's value will be returned.
 *
 * @return The current value of the btfw_lp_mode field in the BT_MEM_CFG1 register.
 */
__INLINE uint8_t wcnaon_btfw_lp_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_MEM_CFG1_ADDR);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

/**
 * @brief Sets the btfw_lp_mode field of the BT_MEM_CFG1 register.
 *
 * The BT_MEM_CFG1 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btfwlpmode - The value to set the field to.
 */
__INLINE void wcnaon_btfw_lp_mode_setf(uint8_t btfwlpmode)
{
    REG_PL_WR(WCNAON_BT_MEM_CFG1_ADDR, (REG_PL_RD(WCNAON_BT_MEM_CFG1_ADDR) & ~((uint32_t)0x00010000)) | (((uint32_t)btfwlpmode << 16) & ((uint32_t)0x00010000)));
}

/**
 * @brief Returns the current value of the bt_mem_cfg field in the BT_MEM_CFG1 register.
 *
 * The BT_MEM_CFG1 register will be read and the bt_mem_cfg field's value will be returned.
 *
 * @return The current value of the bt_mem_cfg field in the BT_MEM_CFG1 register.
 */
__INLINE uint16_t wcnaon_bt_mem_cfg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_MEM_CFG1_ADDR);
    return ((localVal & ((uint32_t)0x0000FFFF)) >> 0);
}

/**
 * @brief Sets the bt_mem_cfg field of the BT_MEM_CFG1 register.
 *
 * The BT_MEM_CFG1 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btmemcfg - The value to set the field to.
 */
__INLINE void wcnaon_bt_mem_cfg_setf(uint16_t btmemcfg)
{
    REG_PL_WR(WCNAON_BT_MEM_CFG1_ADDR, (REG_PL_RD(WCNAON_BT_MEM_CFG1_ADDR) & ~((uint32_t)0x0000FFFF)) | (((uint32_t)btmemcfg << 0) & ((uint32_t)0x0000FFFF)));
}

/// @}

/**
 * @name BT_LP_CFG_ADDR register definitions
 * <table>
 * <caption id="BT_LP_CFG_ADDR_BF">BT_LP_CFG_ADDR bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>02 <td>  bt_wakeup_lp_sel <td>R <td>R/W <td>1
 * <tr><td>01 <td>   bt_cfg_power_en <td>R <td>R/W <td>0
 * <tr><td>00 <td>     bt_cfg_cpu_en <td>R <td>R/W <td>1
 * </table>
 *
 * @{
 */

/// Address of the BT_LP_CFG_ADDR register
#define WCNAON_BT_LP_CFG_ADDR_ADDR   0x40509004
/// Offset of the BT_LP_CFG_ADDR register from the base address
#define WCNAON_BT_LP_CFG_ADDR_OFFSET 0x00000004
/// Index of the BT_LP_CFG_ADDR register
#define WCNAON_BT_LP_CFG_ADDR_INDEX  0x00000001
/// Reset value of the BT_LP_CFG_ADDR register
#define WCNAON_BT_LP_CFG_ADDR_RESET  0x00000005

/**
 * @brief Returns the current value of the BT_LP_CFG_ADDR register.
 * The BT_LP_CFG_ADDR register will be read and its value returned.
 * @return The current value of the BT_LP_CFG_ADDR register.
 */
__INLINE uint32_t wcnaon_bt_lp_cfg_addr_get(void)
{
    return REG_PL_RD(WCNAON_BT_LP_CFG_ADDR_ADDR);
}

/**
 * @brief Sets the BT_LP_CFG_ADDR register to a value.
 * The BT_LP_CFG_ADDR register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_bt_lp_cfg_addr_set(uint32_t value)
{
    REG_PL_WR(WCNAON_BT_LP_CFG_ADDR_ADDR, value);
}

// field definitions
/// BT_WAKEUP_LP_SEL field bit
#define WCNAON_BT_WAKEUP_LP_SEL_BIT    ((uint32_t)0x00000004)
/// BT_WAKEUP_LP_SEL field position
#define WCNAON_BT_WAKEUP_LP_SEL_POS    2
/// BT_CFG_POWER_EN field bit
#define WCNAON_BT_CFG_POWER_EN_BIT     ((uint32_t)0x00000002)
/// BT_CFG_POWER_EN field position
#define WCNAON_BT_CFG_POWER_EN_POS     1
/// BT_CFG_CPU_EN field bit
#define WCNAON_BT_CFG_CPU_EN_BIT       ((uint32_t)0x00000001)
/// BT_CFG_CPU_EN field position
#define WCNAON_BT_CFG_CPU_EN_POS       0

/// BT_WAKEUP_LP_SEL field reset value
#define WCNAON_BT_WAKEUP_LP_SEL_RST    0x1
/// BT_CFG_POWER_EN field reset value
#define WCNAON_BT_CFG_POWER_EN_RST     0x0
/// BT_CFG_CPU_EN field reset value
#define WCNAON_BT_CFG_CPU_EN_RST       0x1

/**
 * @brief Constructs a value for the BT_LP_CFG_ADDR register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btwakeuplpsel - The value to use for the bt_wakeup_lp_sel field.
 * @param[in] btcfgpoweren - The value to use for the bt_cfg_power_en field.
 * @param[in] btcfgcpuen - The value to use for the bt_cfg_cpu_en field.
 */
__INLINE void wcnaon_bt_lp_cfg_addr_pack(uint8_t btwakeuplpsel, uint8_t btcfgpoweren, uint8_t btcfgcpuen)
{
    REG_PL_WR(WCNAON_BT_LP_CFG_ADDR_ADDR,  ((uint32_t)btwakeuplpsel << 2) | ((uint32_t)btcfgpoweren << 1) | ((uint32_t)btcfgcpuen << 0));
}

/**
 * @brief Unpacks BT_LP_CFG_ADDR's fields from current value of the BT_LP_CFG_ADDR register.
 *
 * Reads the BT_LP_CFG_ADDR register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btwakeuplpsel - Will be populated with the current value of this field from the register.
 * @param[out] btcfgpoweren - Will be populated with the current value of this field from the register.
 * @param[out] btcfgcpuen - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_bt_lp_cfg_addr_unpack(uint8_t* btwakeuplpsel, uint8_t* btcfgpoweren, uint8_t* btcfgcpuen)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_LP_CFG_ADDR_ADDR);

    *btwakeuplpsel = (localVal & ((uint32_t)0x00000004)) >> 2;
    *btcfgpoweren = (localVal & ((uint32_t)0x00000002)) >> 1;
    *btcfgcpuen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the bt_wakeup_lp_sel field in the BT_LP_CFG_ADDR register.
 *
 * The BT_LP_CFG_ADDR register will be read and the bt_wakeup_lp_sel field's value will be returned.
 *
 * @return The current value of the bt_wakeup_lp_sel field in the BT_LP_CFG_ADDR register.
 */
__INLINE uint8_t wcnaon_bt_wakeup_lp_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_LP_CFG_ADDR_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the bt_wakeup_lp_sel field of the BT_LP_CFG_ADDR register.
 *
 * The BT_LP_CFG_ADDR register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btwakeuplpsel - The value to set the field to.
 */
__INLINE void wcnaon_bt_wakeup_lp_sel_setf(uint8_t btwakeuplpsel)
{
    REG_PL_WR(WCNAON_BT_LP_CFG_ADDR_ADDR, (REG_PL_RD(WCNAON_BT_LP_CFG_ADDR_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)btwakeuplpsel << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the bt_cfg_power_en field in the BT_LP_CFG_ADDR register.
 *
 * The BT_LP_CFG_ADDR register will be read and the bt_cfg_power_en field's value will be returned.
 *
 * @return The current value of the bt_cfg_power_en field in the BT_LP_CFG_ADDR register.
 */
__INLINE uint8_t wcnaon_bt_cfg_power_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_LP_CFG_ADDR_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the bt_cfg_power_en field of the BT_LP_CFG_ADDR register.
 *
 * The BT_LP_CFG_ADDR register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btcfgpoweren - The value to set the field to.
 */
__INLINE void wcnaon_bt_cfg_power_en_setf(uint8_t btcfgpoweren)
{
    REG_PL_WR(WCNAON_BT_LP_CFG_ADDR_ADDR, (REG_PL_RD(WCNAON_BT_LP_CFG_ADDR_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)btcfgpoweren << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the bt_cfg_cpu_en field in the BT_LP_CFG_ADDR register.
 *
 * The BT_LP_CFG_ADDR register will be read and the bt_cfg_cpu_en field's value will be returned.
 *
 * @return The current value of the bt_cfg_cpu_en field in the BT_LP_CFG_ADDR register.
 */
__INLINE uint8_t wcnaon_bt_cfg_cpu_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_LP_CFG_ADDR_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the bt_cfg_cpu_en field of the BT_LP_CFG_ADDR register.
 *
 * The BT_LP_CFG_ADDR register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btcfgcpuen - The value to set the field to.
 */
__INLINE void wcnaon_bt_cfg_cpu_en_setf(uint8_t btcfgcpuen)
{
    REG_PL_WR(WCNAON_BT_LP_CFG_ADDR_ADDR, (REG_PL_RD(WCNAON_BT_LP_CFG_ADDR_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)btcfgcpuen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name BT_CLK_CFG0 register definitions
 * <table>
 * <caption id="BT_CLK_CFG0_BF">BT_CLK_CFG0 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>     bt_div_num_ld <td>R <td>R/W <td>0
 * <tr><td>24:16 <td>          bt_div_M <td>R <td>R/W <td>0x1
 * <tr><td>09:00 <td>          bt_div_N <td>R <td>R/W <td>0x2
 * </table>
 *
 * @{
 */

/// Address of the BT_CLK_CFG0 register
#define WCNAON_BT_CLK_CFG0_ADDR   0x40509008
/// Offset of the BT_CLK_CFG0 register from the base address
#define WCNAON_BT_CLK_CFG0_OFFSET 0x00000008
/// Index of the BT_CLK_CFG0 register
#define WCNAON_BT_CLK_CFG0_INDEX  0x00000002
/// Reset value of the BT_CLK_CFG0 register
#define WCNAON_BT_CLK_CFG0_RESET  0x00010002

/**
 * @brief Returns the current value of the BT_CLK_CFG0 register.
 * The BT_CLK_CFG0 register will be read and its value returned.
 * @return The current value of the BT_CLK_CFG0 register.
 */
__INLINE uint32_t wcnaon_bt_clk_cfg0_get(void)
{
    return REG_PL_RD(WCNAON_BT_CLK_CFG0_ADDR);
}

/**
 * @brief Sets the BT_CLK_CFG0 register to a value.
 * The BT_CLK_CFG0 register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_bt_clk_cfg0_set(uint32_t value)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG0_ADDR, value);
}

// field definitions
/// BT_DIV_NUM_LD field bit
#define WCNAON_BT_DIV_NUM_LD_BIT    ((uint32_t)0x80000000)
/// BT_DIV_NUM_LD field position
#define WCNAON_BT_DIV_NUM_LD_POS    31
/// BT_DIV_M field mask
#define WCNAON_BT_DIV_M_MASK        ((uint32_t)0x01FF0000)
/// BT_DIV_M field LSB position
#define WCNAON_BT_DIV_M_LSB         16
/// BT_DIV_M field width
#define WCNAON_BT_DIV_M_WIDTH       ((uint32_t)0x00000009)
/// BT_DIV_N field mask
#define WCNAON_BT_DIV_N_MASK        ((uint32_t)0x000003FF)
/// BT_DIV_N field LSB position
#define WCNAON_BT_DIV_N_LSB         0
/// BT_DIV_N field width
#define WCNAON_BT_DIV_N_WIDTH       ((uint32_t)0x0000000A)

/// BT_DIV_NUM_LD field reset value
#define WCNAON_BT_DIV_NUM_LD_RST    0x0
/// BT_DIV_M field reset value
#define WCNAON_BT_DIV_M_RST         0x1
/// BT_DIV_N field reset value
#define WCNAON_BT_DIV_N_RST         0x2

/**
 * @brief Constructs a value for the BT_CLK_CFG0 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btdivnumld - The value to use for the bt_div_num_ld field.
 * @param[in] btdivm - The value to use for the bt_div_M field.
 * @param[in] btdivn - The value to use for the bt_div_N field.
 */
__INLINE void wcnaon_bt_clk_cfg0_pack(uint8_t btdivnumld, uint16_t btdivm, uint16_t btdivn)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG0_ADDR,  ((uint32_t)btdivnumld << 31) | ((uint32_t)btdivm << 16) | ((uint32_t)btdivn << 0));
}

/**
 * @brief Unpacks BT_CLK_CFG0's fields from current value of the BT_CLK_CFG0 register.
 *
 * Reads the BT_CLK_CFG0 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btdivnumld - Will be populated with the current value of this field from the register.
 * @param[out] btdivm - Will be populated with the current value of this field from the register.
 * @param[out] btdivn - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_bt_clk_cfg0_unpack(uint8_t* btdivnumld, uint16_t* btdivm, uint16_t* btdivn)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG0_ADDR);

    *btdivnumld = (localVal & ((uint32_t)0x80000000)) >> 31;
    *btdivm = (localVal & ((uint32_t)0x01FF0000)) >> 16;
    *btdivn = (localVal & ((uint32_t)0x000003FF)) >> 0;
}

/**
 * @brief Returns the current value of the bt_div_num_ld field in the BT_CLK_CFG0 register.
 *
 * The BT_CLK_CFG0 register will be read and the bt_div_num_ld field's value will be returned.
 *
 * @return The current value of the bt_div_num_ld field in the BT_CLK_CFG0 register.
 */
__INLINE uint8_t wcnaon_bt_div_num_ld_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG0_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the bt_div_num_ld field of the BT_CLK_CFG0 register.
 *
 * The BT_CLK_CFG0 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdivnumld - The value to set the field to.
 */
__INLINE void wcnaon_bt_div_num_ld_setf(uint8_t btdivnumld)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG0_ADDR, (REG_PL_RD(WCNAON_BT_CLK_CFG0_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)btdivnumld << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the bt_div_M field in the BT_CLK_CFG0 register.
 *
 * The BT_CLK_CFG0 register will be read and the bt_div_M field's value will be returned.
 *
 * @return The current value of the bt_div_M field in the BT_CLK_CFG0 register.
 */
__INLINE uint16_t wcnaon_bt_div_m_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG0_ADDR);
    return ((localVal & ((uint32_t)0x01FF0000)) >> 16);
}

/**
 * @brief Sets the bt_div_M field of the BT_CLK_CFG0 register.
 *
 * The BT_CLK_CFG0 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdivm - The value to set the field to.
 */
__INLINE void wcnaon_bt_div_m_setf(uint16_t btdivm)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG0_ADDR, (REG_PL_RD(WCNAON_BT_CLK_CFG0_ADDR) & ~((uint32_t)0x01FF0000)) | (((uint32_t)btdivm << 16) & ((uint32_t)0x01FF0000)));
}

/**
 * @brief Returns the current value of the bt_div_N field in the BT_CLK_CFG0 register.
 *
 * The BT_CLK_CFG0 register will be read and the bt_div_N field's value will be returned.
 *
 * @return The current value of the bt_div_N field in the BT_CLK_CFG0 register.
 */
__INLINE uint16_t wcnaon_bt_div_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG0_ADDR);
    return ((localVal & ((uint32_t)0x000003FF)) >> 0);
}

/**
 * @brief Sets the bt_div_N field of the BT_CLK_CFG0 register.
 *
 * The BT_CLK_CFG0 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdivn - The value to set the field to.
 */
__INLINE void wcnaon_bt_div_n_setf(uint16_t btdivn)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG0_ADDR, (REG_PL_RD(WCNAON_BT_CLK_CFG0_ADDR) & ~((uint32_t)0x000003FF)) | (((uint32_t)btdivn << 0) & ((uint32_t)0x000003FF)));
}

/// @}

/**
 * @name BT_CLK_CFG1 register definitions
 * <table>
 * <caption id="BT_CLK_CFG1_BF">BT_CLK_CFG1 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:24 <td>      bt_cfg_rfsel <td>R <td>R/W <td>0x3F
 * <tr><td>22:16 <td>       bt_clkg_cfg <td>R <td>R/W <td>0x7F
 * <tr><td>09 <td>         ll_eq_ahb <td>R <td>R/W <td>0
 * <tr><td>08 <td>    btdm_clk1_fix1 <td>R <td>R/W <td>0
 * <tr><td>05:00 <td>         bt_clksel <td>R <td>R/W <td>0x14
 * </table>
 *
 * @{
 */

/// Address of the BT_CLK_CFG1 register
#define WCNAON_BT_CLK_CFG1_ADDR   0x4050900C
/// Offset of the BT_CLK_CFG1 register from the base address
#define WCNAON_BT_CLK_CFG1_OFFSET 0x0000000C
/// Index of the BT_CLK_CFG1 register
#define WCNAON_BT_CLK_CFG1_INDEX  0x00000003
/// Reset value of the BT_CLK_CFG1 register
#define WCNAON_BT_CLK_CFG1_RESET  0x3F7F0014

/**
 * @brief Returns the current value of the BT_CLK_CFG1 register.
 * The BT_CLK_CFG1 register will be read and its value returned.
 * @return The current value of the BT_CLK_CFG1 register.
 */
__INLINE uint32_t wcnaon_bt_clk_cfg1_get(void)
{
    return REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR);
}

/**
 * @brief Sets the BT_CLK_CFG1 register to a value.
 * The BT_CLK_CFG1 register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_bt_clk_cfg1_set(uint32_t value)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG1_ADDR, value);
}

// field definitions
/// BT_CFG_RFSEL field mask
#define WCNAON_BT_CFG_RFSEL_MASK       ((uint32_t)0x3F000000)
/// BT_CFG_RFSEL field LSB position
#define WCNAON_BT_CFG_RFSEL_LSB        24
/// BT_CFG_RFSEL field width
#define WCNAON_BT_CFG_RFSEL_WIDTH      ((uint32_t)0x00000006)
/// BT_CLKG_CFG field mask
#define WCNAON_BT_CLKG_CFG_MASK        ((uint32_t)0x007F0000)
/// BT_CLKG_CFG field LSB position
#define WCNAON_BT_CLKG_CFG_LSB         16
/// BT_CLKG_CFG field width
#define WCNAON_BT_CLKG_CFG_WIDTH       ((uint32_t)0x00000007)
/// LL_EQ_AHB field bit
#define WCNAON_LL_EQ_AHB_BIT           ((uint32_t)0x00000200)
/// LL_EQ_AHB field position
#define WCNAON_LL_EQ_AHB_POS           9
/// BTDM_CLK_1_FIX_1 field bit
#define WCNAON_BTDM_CLK_1_FIX_1_BIT    ((uint32_t)0x00000100)
/// BTDM_CLK_1_FIX_1 field position
#define WCNAON_BTDM_CLK_1_FIX_1_POS    8
/// BT_CLKSEL field mask
#define WCNAON_BT_CLKSEL_MASK          ((uint32_t)0x0000003F)
/// BT_CLKSEL field LSB position
#define WCNAON_BT_CLKSEL_LSB           0
/// BT_CLKSEL field width
#define WCNAON_BT_CLKSEL_WIDTH         ((uint32_t)0x00000006)

/// BT_CFG_RFSEL field reset value
#define WCNAON_BT_CFG_RFSEL_RST        0x3F
/// BT_CLKG_CFG field reset value
#define WCNAON_BT_CLKG_CFG_RST         0x7F
/// LL_EQ_AHB field reset value
#define WCNAON_LL_EQ_AHB_RST           0x0
/// BTDM_CLK_1_FIX_1 field reset value
#define WCNAON_BTDM_CLK_1_FIX_1_RST    0x0
/// BT_CLKSEL field reset value
#define WCNAON_BT_CLKSEL_RST           0x14

/**
 * @brief Constructs a value for the BT_CLK_CFG1 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btcfgrfsel - The value to use for the bt_cfg_rfsel field.
 * @param[in] btclkgcfg - The value to use for the bt_clkg_cfg field.
 * @param[in] lleqahb - The value to use for the ll_eq_ahb field.
 * @param[in] btdmclk1fix1 - The value to use for the btdm_clk1_fix1 field.
 * @param[in] btclksel - The value to use for the bt_clksel field.
 */
__INLINE void wcnaon_bt_clk_cfg1_pack(uint8_t btcfgrfsel, uint8_t btclkgcfg, uint8_t lleqahb, uint8_t btdmclk1fix1, uint8_t btclksel)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG1_ADDR,  ((uint32_t)btcfgrfsel << 24) | ((uint32_t)btclkgcfg << 16) | ((uint32_t)lleqahb << 9) | ((uint32_t)btdmclk1fix1 << 8) | ((uint32_t)btclksel << 0));
}

/**
 * @brief Unpacks BT_CLK_CFG1's fields from current value of the BT_CLK_CFG1 register.
 *
 * Reads the BT_CLK_CFG1 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btcfgrfsel - Will be populated with the current value of this field from the register.
 * @param[out] btclkgcfg - Will be populated with the current value of this field from the register.
 * @param[out] lleqahb - Will be populated with the current value of this field from the register.
 * @param[out] btdmclk1fix1 - Will be populated with the current value of this field from the register.
 * @param[out] btclksel - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_bt_clk_cfg1_unpack(uint8_t* btcfgrfsel, uint8_t* btclkgcfg, uint8_t* lleqahb, uint8_t* btdmclk1fix1, uint8_t* btclksel)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR);

    *btcfgrfsel = (localVal & ((uint32_t)0x3F000000)) >> 24;
    *btclkgcfg = (localVal & ((uint32_t)0x007F0000)) >> 16;
    *lleqahb = (localVal & ((uint32_t)0x00000200)) >> 9;
    *btdmclk1fix1 = (localVal & ((uint32_t)0x00000100)) >> 8;
    *btclksel = (localVal & ((uint32_t)0x0000003F)) >> 0;
}

/**
 * @brief Returns the current value of the bt_cfg_rfsel field in the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read and the bt_cfg_rfsel field's value will be returned.
 *
 * @return The current value of the bt_cfg_rfsel field in the BT_CLK_CFG1 register.
 */
__INLINE uint8_t wcnaon_bt_cfg_rfsel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR);
    return ((localVal & ((uint32_t)0x3F000000)) >> 24);
}

/**
 * @brief Sets the bt_cfg_rfsel field of the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btcfgrfsel - The value to set the field to.
 */
__INLINE void wcnaon_bt_cfg_rfsel_setf(uint8_t btcfgrfsel)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG1_ADDR, (REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR) & ~((uint32_t)0x3F000000)) | (((uint32_t)btcfgrfsel << 24) & ((uint32_t)0x3F000000)));
}

/**
 * @brief Returns the current value of the bt_clkg_cfg field in the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read and the bt_clkg_cfg field's value will be returned.
 *
 * @return The current value of the bt_clkg_cfg field in the BT_CLK_CFG1 register.
 */
__INLINE uint8_t wcnaon_bt_clkg_cfg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR);
    return ((localVal & ((uint32_t)0x007F0000)) >> 16);
}

/**
 * @brief Sets the bt_clkg_cfg field of the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btclkgcfg - The value to set the field to.
 */
__INLINE void wcnaon_bt_clkg_cfg_setf(uint8_t btclkgcfg)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG1_ADDR, (REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR) & ~((uint32_t)0x007F0000)) | (((uint32_t)btclkgcfg << 16) & ((uint32_t)0x007F0000)));
}

/**
 * @brief Returns the current value of the ll_eq_ahb field in the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read and the ll_eq_ahb field's value will be returned.
 *
 * @return The current value of the ll_eq_ahb field in the BT_CLK_CFG1 register.
 */
__INLINE uint8_t wcnaon_ll_eq_ahb_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the ll_eq_ahb field of the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] lleqahb - The value to set the field to.
 */
__INLINE void wcnaon_ll_eq_ahb_setf(uint8_t lleqahb)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG1_ADDR, (REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)lleqahb << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the btdm_clk1_fix1 field in the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read and the btdm_clk1_fix1 field's value will be returned.
 *
 * @return The current value of the btdm_clk1_fix1 field in the BT_CLK_CFG1 register.
 */
__INLINE uint8_t wcnaon_btdm_clk_1_fix_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the btdm_clk1_fix1 field of the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btdmclk1fix1 - The value to set the field to.
 */
__INLINE void wcnaon_btdm_clk_1_fix_1_setf(uint8_t btdmclk1fix1)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG1_ADDR, (REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)btdmclk1fix1 << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the bt_clksel field in the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read and the bt_clksel field's value will be returned.
 *
 * @return The current value of the bt_clksel field in the BT_CLK_CFG1 register.
 */
__INLINE uint8_t wcnaon_bt_clksel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR);
    return ((localVal & ((uint32_t)0x0000003F)) >> 0);
}

/**
 * @brief Sets the bt_clksel field of the BT_CLK_CFG1 register.
 *
 * The BT_CLK_CFG1 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btclksel - The value to set the field to.
 */
__INLINE void wcnaon_bt_clksel_setf(uint8_t btclksel)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG1_ADDR, (REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR) & ~((uint32_t)0x0000003F)) | (((uint32_t)btclksel << 0) & ((uint32_t)0x0000003F)));
}

/// @}

/**
 * @name WIFI_LP_CFG register definitions
 * <table>
 * <caption id="WIFI_LP_CFG_BF">WIFI_LP_CFG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>07:06 <td>           mon_sel <td>R <td>R/W <td>0x0
 * <tr><td>05 <td>wlan_wakeup_lp_sel <td>R <td>R/W <td>1
 * <tr><td>04 <td>wlan_radio_cg_sleep_en <td>R <td>R/W <td>0
 * <tr><td>03 <td>wlan_cpu_wakeup_en <td>R <td>R/W <td>0
 * <tr><td>02 <td>wlan_radio_sleep_en <td>R <td>R/W <td>0
 * <tr><td>01 <td>wlan_power_sleep_en <td>R <td>R/W <td>0
 * <tr><td>00 <td>wlan_soft_wakeup_req <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the WIFI_LP_CFG register
#define WCNAON_WIFI_LP_CFG_ADDR   0x40509010
/// Offset of the WIFI_LP_CFG register from the base address
#define WCNAON_WIFI_LP_CFG_OFFSET 0x00000010
/// Index of the WIFI_LP_CFG register
#define WCNAON_WIFI_LP_CFG_INDEX  0x00000004
/// Reset value of the WIFI_LP_CFG register
#define WCNAON_WIFI_LP_CFG_RESET  0x00000020

/**
 * @brief Returns the current value of the WIFI_LP_CFG register.
 * The WIFI_LP_CFG register will be read and its value returned.
 * @return The current value of the WIFI_LP_CFG register.
 */
__INLINE uint32_t wcnaon_wifi_lp_cfg_get(void)
{
    return REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR);
}

/**
 * @brief Sets the WIFI_LP_CFG register to a value.
 * The WIFI_LP_CFG register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_wifi_lp_cfg_set(uint32_t value)
{
    REG_PL_WR(WCNAON_WIFI_LP_CFG_ADDR, value);
}

// field definitions
/// MON_SEL field mask
#define WCNAON_MON_SEL_MASK                  ((uint32_t)0x000000C0)
/// MON_SEL field LSB position
#define WCNAON_MON_SEL_LSB                   6
/// MON_SEL field width
#define WCNAON_MON_SEL_WIDTH                 ((uint32_t)0x00000002)
/// WLAN_WAKEUP_LP_SEL field bit
#define WCNAON_WLAN_WAKEUP_LP_SEL_BIT        ((uint32_t)0x00000020)
/// WLAN_WAKEUP_LP_SEL field position
#define WCNAON_WLAN_WAKEUP_LP_SEL_POS        5
/// WLAN_RADIO_CG_SLEEP_EN field bit
#define WCNAON_WLAN_RADIO_CG_SLEEP_EN_BIT    ((uint32_t)0x00000010)
/// WLAN_RADIO_CG_SLEEP_EN field position
#define WCNAON_WLAN_RADIO_CG_SLEEP_EN_POS    4
/// WLAN_CPU_WAKEUP_EN field bit
#define WCNAON_WLAN_CPU_WAKEUP_EN_BIT        ((uint32_t)0x00000008)
/// WLAN_CPU_WAKEUP_EN field position
#define WCNAON_WLAN_CPU_WAKEUP_EN_POS        3
/// WLAN_RADIO_SLEEP_EN field bit
#define WCNAON_WLAN_RADIO_SLEEP_EN_BIT       ((uint32_t)0x00000004)
/// WLAN_RADIO_SLEEP_EN field position
#define WCNAON_WLAN_RADIO_SLEEP_EN_POS       2
/// WLAN_POWER_SLEEP_EN field bit
#define WCNAON_WLAN_POWER_SLEEP_EN_BIT       ((uint32_t)0x00000002)
/// WLAN_POWER_SLEEP_EN field position
#define WCNAON_WLAN_POWER_SLEEP_EN_POS       1
/// WLAN_SOFT_WAKEUP_REQ field bit
#define WCNAON_WLAN_SOFT_WAKEUP_REQ_BIT      ((uint32_t)0x00000001)
/// WLAN_SOFT_WAKEUP_REQ field position
#define WCNAON_WLAN_SOFT_WAKEUP_REQ_POS      0

/// MON_SEL field reset value
#define WCNAON_MON_SEL_RST                   0x0
/// WLAN_WAKEUP_LP_SEL field reset value
#define WCNAON_WLAN_WAKEUP_LP_SEL_RST        0x1
/// WLAN_RADIO_CG_SLEEP_EN field reset value
#define WCNAON_WLAN_RADIO_CG_SLEEP_EN_RST    0x0
/// WLAN_CPU_WAKEUP_EN field reset value
#define WCNAON_WLAN_CPU_WAKEUP_EN_RST        0x0
/// WLAN_RADIO_SLEEP_EN field reset value
#define WCNAON_WLAN_RADIO_SLEEP_EN_RST       0x0
/// WLAN_POWER_SLEEP_EN field reset value
#define WCNAON_WLAN_POWER_SLEEP_EN_RST       0x0
/// WLAN_SOFT_WAKEUP_REQ field reset value
#define WCNAON_WLAN_SOFT_WAKEUP_REQ_RST      0x0

/**
 * @brief Constructs a value for the WIFI_LP_CFG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] monsel - The value to use for the mon_sel field.
 * @param[in] wlanwakeuplpsel - The value to use for the wlan_wakeup_lp_sel field.
 * @param[in] wlanradiocgsleepen - The value to use for the wlan_radio_cg_sleep_en field.
 * @param[in] wlancpuwakeupen - The value to use for the wlan_cpu_wakeup_en field.
 * @param[in] wlanradiosleepen - The value to use for the wlan_radio_sleep_en field.
 * @param[in] wlanpowersleepen - The value to use for the wlan_power_sleep_en field.
 * @param[in] wlansoftwakeupreq - The value to use for the wlan_soft_wakeup_req field.
 */
__INLINE void wcnaon_wifi_lp_cfg_pack(uint8_t monsel, uint8_t wlanwakeuplpsel, uint8_t wlanradiocgsleepen, uint8_t wlancpuwakeupen, uint8_t wlanradiosleepen, uint8_t wlanpowersleepen, uint8_t wlansoftwakeupreq)
{
    REG_PL_WR(WCNAON_WIFI_LP_CFG_ADDR,  ((uint32_t)monsel << 6) | ((uint32_t)wlanwakeuplpsel << 5) | ((uint32_t)wlanradiocgsleepen << 4) | ((uint32_t)wlancpuwakeupen << 3) | ((uint32_t)wlanradiosleepen << 2) | ((uint32_t)wlanpowersleepen << 1) | ((uint32_t)wlansoftwakeupreq << 0));
}

/**
 * @brief Unpacks WIFI_LP_CFG's fields from current value of the WIFI_LP_CFG register.
 *
 * Reads the WIFI_LP_CFG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] monsel - Will be populated with the current value of this field from the register.
 * @param[out] wlanwakeuplpsel - Will be populated with the current value of this field from the register.
 * @param[out] wlanradiocgsleepen - Will be populated with the current value of this field from the register.
 * @param[out] wlancpuwakeupen - Will be populated with the current value of this field from the register.
 * @param[out] wlanradiosleepen - Will be populated with the current value of this field from the register.
 * @param[out] wlanpowersleepen - Will be populated with the current value of this field from the register.
 * @param[out] wlansoftwakeupreq - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_wifi_lp_cfg_unpack(uint8_t* monsel, uint8_t* wlanwakeuplpsel, uint8_t* wlanradiocgsleepen, uint8_t* wlancpuwakeupen, uint8_t* wlanradiosleepen, uint8_t* wlanpowersleepen, uint8_t* wlansoftwakeupreq)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR);

    *monsel = (localVal & ((uint32_t)0x000000C0)) >> 6;
    *wlanwakeuplpsel = (localVal & ((uint32_t)0x00000020)) >> 5;
    *wlanradiocgsleepen = (localVal & ((uint32_t)0x00000010)) >> 4;
    *wlancpuwakeupen = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wlanradiosleepen = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wlanpowersleepen = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wlansoftwakeupreq = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the mon_sel field in the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read and the mon_sel field's value will be returned.
 *
 * @return The current value of the mon_sel field in the WIFI_LP_CFG register.
 */
__INLINE uint8_t wcnaon_mon_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR);
    return ((localVal & ((uint32_t)0x000000C0)) >> 6);
}

/**
 * @brief Sets the mon_sel field of the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] monsel - The value to set the field to.
 */
__INLINE void wcnaon_mon_sel_setf(uint8_t monsel)
{
    REG_PL_WR(WCNAON_WIFI_LP_CFG_ADDR, (REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR) & ~((uint32_t)0x000000C0)) | (((uint32_t)monsel << 6) & ((uint32_t)0x000000C0)));
}

/**
 * @brief Returns the current value of the wlan_wakeup_lp_sel field in the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read and the wlan_wakeup_lp_sel field's value will be returned.
 *
 * @return The current value of the wlan_wakeup_lp_sel field in the WIFI_LP_CFG register.
 */
__INLINE uint8_t wcnaon_wlan_wakeup_lp_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

/**
 * @brief Sets the wlan_wakeup_lp_sel field of the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlanwakeuplpsel - The value to set the field to.
 */
__INLINE void wcnaon_wlan_wakeup_lp_sel_setf(uint8_t wlanwakeuplpsel)
{
    REG_PL_WR(WCNAON_WIFI_LP_CFG_ADDR, (REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR) & ~((uint32_t)0x00000020)) | (((uint32_t)wlanwakeuplpsel << 5) & ((uint32_t)0x00000020)));
}

/**
 * @brief Returns the current value of the wlan_radio_cg_sleep_en field in the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read and the wlan_radio_cg_sleep_en field's value will be returned.
 *
 * @return The current value of the wlan_radio_cg_sleep_en field in the WIFI_LP_CFG register.
 */
__INLINE uint8_t wcnaon_wlan_radio_cg_sleep_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the wlan_radio_cg_sleep_en field of the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlanradiocgsleepen - The value to set the field to.
 */
__INLINE void wcnaon_wlan_radio_cg_sleep_en_setf(uint8_t wlanradiocgsleepen)
{
    REG_PL_WR(WCNAON_WIFI_LP_CFG_ADDR, (REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)wlanradiocgsleepen << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the wlan_cpu_wakeup_en field in the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read and the wlan_cpu_wakeup_en field's value will be returned.
 *
 * @return The current value of the wlan_cpu_wakeup_en field in the WIFI_LP_CFG register.
 */
__INLINE uint8_t wcnaon_wlan_cpu_wakeup_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wlan_cpu_wakeup_en field of the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlancpuwakeupen - The value to set the field to.
 */
__INLINE void wcnaon_wlan_cpu_wakeup_en_setf(uint8_t wlancpuwakeupen)
{
    REG_PL_WR(WCNAON_WIFI_LP_CFG_ADDR, (REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wlancpuwakeupen << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wlan_radio_sleep_en field in the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read and the wlan_radio_sleep_en field's value will be returned.
 *
 * @return The current value of the wlan_radio_sleep_en field in the WIFI_LP_CFG register.
 */
__INLINE uint8_t wcnaon_wlan_radio_sleep_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wlan_radio_sleep_en field of the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlanradiosleepen - The value to set the field to.
 */
__INLINE void wcnaon_wlan_radio_sleep_en_setf(uint8_t wlanradiosleepen)
{
    REG_PL_WR(WCNAON_WIFI_LP_CFG_ADDR, (REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wlanradiosleepen << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wlan_power_sleep_en field in the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read and the wlan_power_sleep_en field's value will be returned.
 *
 * @return The current value of the wlan_power_sleep_en field in the WIFI_LP_CFG register.
 */
__INLINE uint8_t wcnaon_wlan_power_sleep_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wlan_power_sleep_en field of the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlanpowersleepen - The value to set the field to.
 */
__INLINE void wcnaon_wlan_power_sleep_en_setf(uint8_t wlanpowersleepen)
{
    REG_PL_WR(WCNAON_WIFI_LP_CFG_ADDR, (REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wlanpowersleepen << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wlan_soft_wakeup_req field in the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read and the wlan_soft_wakeup_req field's value will be returned.
 *
 * @return The current value of the wlan_soft_wakeup_req field in the WIFI_LP_CFG register.
 */
__INLINE uint8_t wcnaon_wlan_soft_wakeup_req_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wlan_soft_wakeup_req field of the WIFI_LP_CFG register.
 *
 * The WIFI_LP_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlansoftwakeupreq - The value to set the field to.
 */
__INLINE void wcnaon_wlan_soft_wakeup_req_setf(uint8_t wlansoftwakeupreq)
{
    REG_PL_WR(WCNAON_WIFI_LP_CFG_ADDR, (REG_PL_RD(WCNAON_WIFI_LP_CFG_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wlansoftwakeupreq << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name WIFI_WAKEUP_DELAY_TIMER register definitions
 * <table>
 * <caption id="WIFI_WAKEUP_DELAY_TIMER_BF">WIFI_WAKEUP_DELAY_TIMER bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:22 <td>         wlan_twrm <td>R <td>W <td>0x0
 * <tr><td>21:11 <td>        wlan_twpwr <td>R <td>W <td>0x21
 * <tr><td>10:00 <td>        wlan_twext <td>R <td>W <td>0x21
 * </table>
 *
 * @{
 */

/// Address of the WIFI_WAKEUP_DELAY_TIMER register
#define WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR   0x40509014
/// Offset of the WIFI_WAKEUP_DELAY_TIMER register from the base address
#define WCNAON_WIFI_WAKEUP_DELAY_TIMER_OFFSET 0x00000014
/// Index of the WIFI_WAKEUP_DELAY_TIMER register
#define WCNAON_WIFI_WAKEUP_DELAY_TIMER_INDEX  0x00000005
/// Reset value of the WIFI_WAKEUP_DELAY_TIMER register
#define WCNAON_WIFI_WAKEUP_DELAY_TIMER_RESET  0x00010821

/**
 * @brief Sets the WIFI_WAKEUP_DELAY_TIMER register to a value.
 * The WIFI_WAKEUP_DELAY_TIMER register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_wifi_wakeup_delay_timer_set(uint32_t value)
{
    REG_PL_WR(WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR, value);
}

// field definitions
/// WLAN_TWRM field mask
#define WCNAON_WLAN_TWRM_MASK    ((uint32_t)0xFFC00000)
/// WLAN_TWRM field LSB position
#define WCNAON_WLAN_TWRM_LSB     22
/// WLAN_TWRM field width
#define WCNAON_WLAN_TWRM_WIDTH   ((uint32_t)0x0000000A)
/// WLAN_TWPWR field mask
#define WCNAON_WLAN_TWPWR_MASK   ((uint32_t)0x003FF800)
/// WLAN_TWPWR field LSB position
#define WCNAON_WLAN_TWPWR_LSB    11
/// WLAN_TWPWR field width
#define WCNAON_WLAN_TWPWR_WIDTH  ((uint32_t)0x0000000B)
/// WLAN_TWEXT field mask
#define WCNAON_WLAN_TWEXT_MASK   ((uint32_t)0x000007FF)
/// WLAN_TWEXT field LSB position
#define WCNAON_WLAN_TWEXT_LSB    0
/// WLAN_TWEXT field width
#define WCNAON_WLAN_TWEXT_WIDTH  ((uint32_t)0x0000000B)

/// WLAN_TWRM field reset value
#define WCNAON_WLAN_TWRM_RST     0x0
/// WLAN_TWPWR field reset value
#define WCNAON_WLAN_TWPWR_RST    0x21
/// WLAN_TWEXT field reset value
#define WCNAON_WLAN_TWEXT_RST    0x21

/**
 * @brief Constructs a value for the WIFI_WAKEUP_DELAY_TIMER register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wlantwrm - The value to use for the wlan_twrm field.
 * @param[in] wlantwpwr - The value to use for the wlan_twpwr field.
 * @param[in] wlantwext - The value to use for the wlan_twext field.
 */
__INLINE void wcnaon_wifi_wakeup_delay_timer_pack(uint16_t wlantwrm, uint16_t wlantwpwr, uint16_t wlantwext)
{
    REG_PL_WR(WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR,  ((uint32_t)wlantwrm << 22) | ((uint32_t)wlantwpwr << 11) | ((uint32_t)wlantwext << 0));
}

/**
 * @brief Sets the wlan_twrm field of the WIFI_WAKEUP_DELAY_TIMER register.
 *
 * The WIFI_WAKEUP_DELAY_TIMER register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlantwrm - The value to set the field to.
 */
__INLINE void wcnaon_wlan_twrm_setf(uint16_t wlantwrm)
{
    REG_PL_WR(WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR, (REG_PL_RD(WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR) & ~((uint32_t)0xFFC00000)) | (((uint32_t)wlantwrm << 22) & ((uint32_t)0xFFC00000)));
}

/**
 * @brief Sets the wlan_twpwr field of the WIFI_WAKEUP_DELAY_TIMER register.
 *
 * The WIFI_WAKEUP_DELAY_TIMER register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlantwpwr - The value to set the field to.
 */
__INLINE void wcnaon_wlan_twpwr_setf(uint16_t wlantwpwr)
{
    REG_PL_WR(WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR, (REG_PL_RD(WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR) & ~((uint32_t)0x003FF800)) | (((uint32_t)wlantwpwr << 11) & ((uint32_t)0x003FF800)));
}

/**
 * @brief Sets the wlan_twext field of the WIFI_WAKEUP_DELAY_TIMER register.
 *
 * The WIFI_WAKEUP_DELAY_TIMER register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlantwext - The value to set the field to.
 */
__INLINE void wcnaon_wlan_twext_setf(uint16_t wlantwext)
{
    REG_PL_WR(WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR, (REG_PL_RD(WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR) & ~((uint32_t)0x000007FF)) | (((uint32_t)wlantwext << 0) & ((uint32_t)0x000007FF)));
}

/// @}

/**
 * @name WF_RFEN_CTRL register definitions
 * <table>
 * <caption id="WF_RFEN_CTRL_BF">WF_RFEN_CTRL bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>01 <td>        wf_rfen_dr <td>R <td>R/W <td>1
 * <tr><td>00 <td>      wf_rf_en_reg <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the WF_RFEN_CTRL register
#define WCNAON_WF_RFEN_CTRL_ADDR   0x40509018
/// Offset of the WF_RFEN_CTRL register from the base address
#define WCNAON_WF_RFEN_CTRL_OFFSET 0x00000018
/// Index of the WF_RFEN_CTRL register
#define WCNAON_WF_RFEN_CTRL_INDEX  0x00000006
/// Reset value of the WF_RFEN_CTRL register
#define WCNAON_WF_RFEN_CTRL_RESET  0x00000002

/**
 * @brief Returns the current value of the WF_RFEN_CTRL register.
 * The WF_RFEN_CTRL register will be read and its value returned.
 * @return The current value of the WF_RFEN_CTRL register.
 */
__INLINE uint32_t wcnaon_wf_rfen_ctrl_get(void)
{
    return REG_PL_RD(WCNAON_WF_RFEN_CTRL_ADDR);
}

/**
 * @brief Sets the WF_RFEN_CTRL register to a value.
 * The WF_RFEN_CTRL register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_wf_rfen_ctrl_set(uint32_t value)
{
    REG_PL_WR(WCNAON_WF_RFEN_CTRL_ADDR, value);
}

// field definitions
/// WF_RFEN_DR field bit
#define WCNAON_WF_RFEN_DR_BIT      ((uint32_t)0x00000002)
/// WF_RFEN_DR field position
#define WCNAON_WF_RFEN_DR_POS      1
/// WF_RF_EN_REG field bit
#define WCNAON_WF_RF_EN_REG_BIT    ((uint32_t)0x00000001)
/// WF_RF_EN_REG field position
#define WCNAON_WF_RF_EN_REG_POS    0

/// WF_RFEN_DR field reset value
#define WCNAON_WF_RFEN_DR_RST      0x1
/// WF_RF_EN_REG field reset value
#define WCNAON_WF_RF_EN_REG_RST    0x0

/**
 * @brief Constructs a value for the WF_RFEN_CTRL register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrfendr - The value to use for the wf_rfen_dr field.
 * @param[in] wfrfenreg - The value to use for the wf_rf_en_reg field.
 */
__INLINE void wcnaon_wf_rfen_ctrl_pack(uint8_t wfrfendr, uint8_t wfrfenreg)
{
    REG_PL_WR(WCNAON_WF_RFEN_CTRL_ADDR,  ((uint32_t)wfrfendr << 1) | ((uint32_t)wfrfenreg << 0));
}

/**
 * @brief Unpacks WF_RFEN_CTRL's fields from current value of the WF_RFEN_CTRL register.
 *
 * Reads the WF_RFEN_CTRL register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrfendr - Will be populated with the current value of this field from the register.
 * @param[out] wfrfenreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_wf_rfen_ctrl_unpack(uint8_t* wfrfendr, uint8_t* wfrfenreg)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WF_RFEN_CTRL_ADDR);

    *wfrfendr = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wfrfenreg = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rfen_dr field in the WF_RFEN_CTRL register.
 *
 * The WF_RFEN_CTRL register will be read and the wf_rfen_dr field's value will be returned.
 *
 * @return The current value of the wf_rfen_dr field in the WF_RFEN_CTRL register.
 */
__INLINE uint8_t wcnaon_wf_rfen_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WF_RFEN_CTRL_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wf_rfen_dr field of the WF_RFEN_CTRL register.
 *
 * The WF_RFEN_CTRL register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfendr - The value to set the field to.
 */
__INLINE void wcnaon_wf_rfen_dr_setf(uint8_t wfrfendr)
{
    REG_PL_WR(WCNAON_WF_RFEN_CTRL_ADDR, (REG_PL_RD(WCNAON_WF_RFEN_CTRL_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wfrfendr << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wf_rf_en_reg field in the WF_RFEN_CTRL register.
 *
 * The WF_RFEN_CTRL register will be read and the wf_rf_en_reg field's value will be returned.
 *
 * @return The current value of the wf_rf_en_reg field in the WF_RFEN_CTRL register.
 */
__INLINE uint8_t wcnaon_wf_rf_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WF_RFEN_CTRL_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wf_rf_en_reg field of the WF_RFEN_CTRL register.
 *
 * The WF_RFEN_CTRL register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrfenreg - The value to set the field to.
 */
__INLINE void wcnaon_wf_rf_en_reg_setf(uint8_t wfrfenreg)
{
    REG_PL_WR(WCNAON_WF_RFEN_CTRL_ADDR, (REG_PL_RD(WCNAON_WF_RFEN_CTRL_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wfrfenreg << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name BT_RFEN_CTRL register definitions
 * <table>
 * <caption id="BT_RFEN_CTRL_BF">BT_RFEN_CTRL bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>01 <td>        bt_rfen_dr <td>R <td>R/W <td>1
 * <tr><td>00 <td>      bt_rf_en_reg <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the BT_RFEN_CTRL register
#define WCNAON_BT_RFEN_CTRL_ADDR   0x4050901C
/// Offset of the BT_RFEN_CTRL register from the base address
#define WCNAON_BT_RFEN_CTRL_OFFSET 0x0000001C
/// Index of the BT_RFEN_CTRL register
#define WCNAON_BT_RFEN_CTRL_INDEX  0x00000007
/// Reset value of the BT_RFEN_CTRL register
#define WCNAON_BT_RFEN_CTRL_RESET  0x00000002

/**
 * @brief Returns the current value of the BT_RFEN_CTRL register.
 * The BT_RFEN_CTRL register will be read and its value returned.
 * @return The current value of the BT_RFEN_CTRL register.
 */
__INLINE uint32_t wcnaon_bt_rfen_ctrl_get(void)
{
    return REG_PL_RD(WCNAON_BT_RFEN_CTRL_ADDR);
}

/**
 * @brief Sets the BT_RFEN_CTRL register to a value.
 * The BT_RFEN_CTRL register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_bt_rfen_ctrl_set(uint32_t value)
{
    REG_PL_WR(WCNAON_BT_RFEN_CTRL_ADDR, value);
}

// field definitions
/// BT_RFEN_DR field bit
#define WCNAON_BT_RFEN_DR_BIT      ((uint32_t)0x00000002)
/// BT_RFEN_DR field position
#define WCNAON_BT_RFEN_DR_POS      1
/// BT_RF_EN_REG field bit
#define WCNAON_BT_RF_EN_REG_BIT    ((uint32_t)0x00000001)
/// BT_RF_EN_REG field position
#define WCNAON_BT_RF_EN_REG_POS    0

/// BT_RFEN_DR field reset value
#define WCNAON_BT_RFEN_DR_RST      0x1
/// BT_RF_EN_REG field reset value
#define WCNAON_BT_RF_EN_REG_RST    0x0

/**
 * @brief Constructs a value for the BT_RFEN_CTRL register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btrfendr - The value to use for the bt_rfen_dr field.
 * @param[in] btrfenreg - The value to use for the bt_rf_en_reg field.
 */
__INLINE void wcnaon_bt_rfen_ctrl_pack(uint8_t btrfendr, uint8_t btrfenreg)
{
    REG_PL_WR(WCNAON_BT_RFEN_CTRL_ADDR,  ((uint32_t)btrfendr << 1) | ((uint32_t)btrfenreg << 0));
}

/**
 * @brief Unpacks BT_RFEN_CTRL's fields from current value of the BT_RFEN_CTRL register.
 *
 * Reads the BT_RFEN_CTRL register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btrfendr - Will be populated with the current value of this field from the register.
 * @param[out] btrfenreg - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_bt_rfen_ctrl_unpack(uint8_t* btrfendr, uint8_t* btrfenreg)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_RFEN_CTRL_ADDR);

    *btrfendr = (localVal & ((uint32_t)0x00000002)) >> 1;
    *btrfenreg = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the bt_rfen_dr field in the BT_RFEN_CTRL register.
 *
 * The BT_RFEN_CTRL register will be read and the bt_rfen_dr field's value will be returned.
 *
 * @return The current value of the bt_rfen_dr field in the BT_RFEN_CTRL register.
 */
__INLINE uint8_t wcnaon_bt_rfen_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_RFEN_CTRL_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the bt_rfen_dr field of the BT_RFEN_CTRL register.
 *
 * The BT_RFEN_CTRL register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btrfendr - The value to set the field to.
 */
__INLINE void wcnaon_bt_rfen_dr_setf(uint8_t btrfendr)
{
    REG_PL_WR(WCNAON_BT_RFEN_CTRL_ADDR, (REG_PL_RD(WCNAON_BT_RFEN_CTRL_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)btrfendr << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the bt_rf_en_reg field in the BT_RFEN_CTRL register.
 *
 * The BT_RFEN_CTRL register will be read and the bt_rf_en_reg field's value will be returned.
 *
 * @return The current value of the bt_rf_en_reg field in the BT_RFEN_CTRL register.
 */
__INLINE uint8_t wcnaon_bt_rf_en_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_RFEN_CTRL_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the bt_rf_en_reg field of the BT_RFEN_CTRL register.
 *
 * The BT_RFEN_CTRL register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btrfenreg - The value to set the field to.
 */
__INLINE void wcnaon_bt_rf_en_reg_setf(uint8_t btrfenreg)
{
    REG_PL_WR(WCNAON_BT_RFEN_CTRL_ADDR, (REG_PL_RD(WCNAON_BT_RFEN_CTRL_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)btrfenreg << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name MAXIM_SPI register definitions
 * <table>
 * <caption id="MAXIM_SPI_BF">MAXIM_SPI bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>        START_DONE <td>C <td>S <td>0
 * <tr><td>24 <td>                CS <td>R/W <td>R/W <td>0
 * <tr><td>23:20 <td>         PRESCALER <td>R <td>R/W <td>0x0
 * <tr><td>19:16 <td>           ADDRESS <td>R/W <td>R/W <td>0x0
 * <tr><td>13:00 <td>              DATA <td>R/W <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the MAXIM_SPI register
#define WCNAON_MAXIM_SPI_ADDR   0x40509020
/// Offset of the MAXIM_SPI register from the base address
#define WCNAON_MAXIM_SPI_OFFSET 0x00000020
/// Index of the MAXIM_SPI register
#define WCNAON_MAXIM_SPI_INDEX  0x00000008
/// Reset value of the MAXIM_SPI register
#define WCNAON_MAXIM_SPI_RESET  0x00000000

/**
 * @brief Returns the current value of the MAXIM_SPI register.
 * The MAXIM_SPI register will be read and its value returned.
 * @return The current value of the MAXIM_SPI register.
 */
__INLINE uint32_t wcnaon_maxim_spi_get(void)
{
    return REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);
}

/**
 * @brief Sets the MAXIM_SPI register to a value.
 * The MAXIM_SPI register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_maxim_spi_set(uint32_t value)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR, value);
}

// field definitions
/// START_DONE field bit
#define WCNAON_START_DONE_BIT    ((uint32_t)0x80000000)
/// START_DONE field position
#define WCNAON_START_DONE_POS    31
/// CS field bit
#define WCNAON_CS_BIT            ((uint32_t)0x01000000)
/// CS field position
#define WCNAON_CS_POS            24
/// PRESCALER field mask
#define WCNAON_PRESCALER_MASK    ((uint32_t)0x00F00000)
/// PRESCALER field LSB position
#define WCNAON_PRESCALER_LSB     20
/// PRESCALER field width
#define WCNAON_PRESCALER_WIDTH   ((uint32_t)0x00000004)
/// ADDRESS field mask
#define WCNAON_ADDRESS_MASK      ((uint32_t)0x000F0000)
/// ADDRESS field LSB position
#define WCNAON_ADDRESS_LSB       16
/// ADDRESS field width
#define WCNAON_ADDRESS_WIDTH     ((uint32_t)0x00000004)
/// DATA field mask
#define WCNAON_DATA_MASK         ((uint32_t)0x00003FFF)
/// DATA field LSB position
#define WCNAON_DATA_LSB          0
/// DATA field width
#define WCNAON_DATA_WIDTH        ((uint32_t)0x0000000E)

/// START_DONE field reset value
#define WCNAON_START_DONE_RST    0x0
/// CS field reset value
#define WCNAON_CS_RST            0x0
/// PRESCALER field reset value
#define WCNAON_PRESCALER_RST     0x0
/// ADDRESS field reset value
#define WCNAON_ADDRESS_RST       0x0
/// DATA field reset value
#define WCNAON_DATA_RST          0x0

/**
 * @brief Constructs a value for the MAXIM_SPI register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] startdone - The value to use for the START_DONE field.
 * @param[in] cs - The value to use for the CS field.
 * @param[in] prescaler - The value to use for the PRESCALER field.
 * @param[in] address - The value to use for the ADDRESS field.
 * @param[in] data - The value to use for the DATA field.
 */
__INLINE void wcnaon_maxim_spi_pack(uint8_t startdone, uint8_t cs, uint8_t prescaler, uint8_t address, uint16_t data)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR,  ((uint32_t)startdone << 31) | ((uint32_t)cs << 24) | ((uint32_t)prescaler << 20) | ((uint32_t)address << 16) | ((uint32_t)data << 0));
}

/**
 * @brief Unpacks MAXIM_SPI's fields from current value of the MAXIM_SPI register.
 *
 * Reads the MAXIM_SPI register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] startdone - Will be populated with the current value of this field from the register.
 * @param[out] cs - Will be populated with the current value of this field from the register.
 * @param[out] prescaler - Will be populated with the current value of this field from the register.
 * @param[out] address - Will be populated with the current value of this field from the register.
 * @param[out] data - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_maxim_spi_unpack(uint8_t* startdone, uint8_t* cs, uint8_t* prescaler, uint8_t* address, uint16_t* data)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);

    *startdone = (localVal & ((uint32_t)0x80000000)) >> 31;
    *cs = (localVal & ((uint32_t)0x01000000)) >> 24;
    *prescaler = (localVal & ((uint32_t)0x00F00000)) >> 20;
    *address = (localVal & ((uint32_t)0x000F0000)) >> 16;
    *data = (localVal & ((uint32_t)0x00003FFF)) >> 0;
}

/**
 * @brief Returns the current value of the START_DONE field in the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read and the START_DONE field's value will be returned.
 *
 * @return The current value of the START_DONE field in the MAXIM_SPI register.
 */
__INLINE uint8_t wcnaon_start_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

/**
 * @brief Sets the START_DONE field of the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read, modified to contain the new field value, and written.
 *
 * @param[in] startdone - The value to set the field to.
 */
__INLINE void wcnaon_start_done_setf(uint8_t startdone)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_ADDR) & ~((uint32_t)0x80000000)) | (((uint32_t)startdone << 31) & ((uint32_t)0x80000000)));
}

/**
 * @brief Returns the current value of the CS field in the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read and the CS field's value will be returned.
 *
 * @return The current value of the CS field in the MAXIM_SPI register.
 */
__INLINE uint8_t wcnaon_cs_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

/**
 * @brief Sets the CS field of the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read, modified to contain the new field value, and written.
 *
 * @param[in] cs - The value to set the field to.
 */
__INLINE void wcnaon_cs_setf(uint8_t cs)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_ADDR) & ~((uint32_t)0x01000000)) | (((uint32_t)cs << 24) & ((uint32_t)0x01000000)));
}

/**
 * @brief Returns the current value of the PRESCALER field in the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read and the PRESCALER field's value will be returned.
 *
 * @return The current value of the PRESCALER field in the MAXIM_SPI register.
 */
__INLINE uint8_t wcnaon_prescaler_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);
    return ((localVal & ((uint32_t)0x00F00000)) >> 20);
}

/**
 * @brief Sets the PRESCALER field of the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read, modified to contain the new field value, and written.
 *
 * @param[in] prescaler - The value to set the field to.
 */
__INLINE void wcnaon_prescaler_setf(uint8_t prescaler)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_ADDR) & ~((uint32_t)0x00F00000)) | (((uint32_t)prescaler << 20) & ((uint32_t)0x00F00000)));
}

/**
 * @brief Returns the current value of the ADDRESS field in the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read and the ADDRESS field's value will be returned.
 *
 * @return The current value of the ADDRESS field in the MAXIM_SPI register.
 */
__INLINE uint8_t wcnaon_address_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);
    return ((localVal & ((uint32_t)0x000F0000)) >> 16);
}

/**
 * @brief Sets the ADDRESS field of the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read, modified to contain the new field value, and written.
 *
 * @param[in] address - The value to set the field to.
 */
__INLINE void wcnaon_address_setf(uint8_t address)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_ADDR) & ~((uint32_t)0x000F0000)) | (((uint32_t)address << 16) & ((uint32_t)0x000F0000)));
}

/**
 * @brief Returns the current value of the DATA field in the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read and the DATA field's value will be returned.
 *
 * @return The current value of the DATA field in the MAXIM_SPI register.
 */
__INLINE uint16_t wcnaon_data_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);
    return ((localVal & ((uint32_t)0x00003FFF)) >> 0);
}

/**
 * @brief Sets the DATA field of the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read, modified to contain the new field value, and written.
 *
 * @param[in] data - The value to set the field to.
 */
__INLINE void wcnaon_data_setf(uint16_t data)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_ADDR) & ~((uint32_t)0x00003FFF)) | (((uint32_t)data << 0) & ((uint32_t)0x00003FFF)));
}

/// @}

/**
 * @name DEEPSLEEP_WAKEUP_IND register definitions
 * <table>
 * <caption id="DEEPSLEEP_WAKEUP_IND_BF">DEEPSLEEP_WAKEUP_IND bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:04 <td>            hw_eco <td>R <td>R/W <td>0x0
 * <tr><td>03:00 <td>deepsleep_wakeup_ind <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the DEEPSLEEP_WAKEUP_IND register
#define WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR   0x40509048
/// Offset of the DEEPSLEEP_WAKEUP_IND register from the base address
#define WCNAON_DEEPSLEEP_WAKEUP_IND_OFFSET 0x00000048
/// Index of the DEEPSLEEP_WAKEUP_IND register
#define WCNAON_DEEPSLEEP_WAKEUP_IND_INDEX  0x00000012
/// Reset value of the DEEPSLEEP_WAKEUP_IND register
#define WCNAON_DEEPSLEEP_WAKEUP_IND_RESET  0x00000000

/**
 * @brief Returns the current value of the DEEPSLEEP_WAKEUP_IND register.
 * The DEEPSLEEP_WAKEUP_IND register will be read and its value returned.
 * @return The current value of the DEEPSLEEP_WAKEUP_IND register.
 */
__INLINE uint32_t wcnaon_deepsleep_wakeup_ind_get(void)
{
    return REG_PL_RD(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR);
}

/**
 * @brief Sets the DEEPSLEEP_WAKEUP_IND register to a value.
 * The DEEPSLEEP_WAKEUP_IND register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_deepsleep_wakeup_ind_set(uint32_t value)
{
    REG_PL_WR(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR, value);
}

// field definitions
/// HW_ECO field mask
#define WCNAON_HW_ECO_MASK                 ((uint32_t)0xFFFFFFF0)
/// HW_ECO field LSB position
#define WCNAON_HW_ECO_LSB                  4
/// HW_ECO field width
#define WCNAON_HW_ECO_WIDTH                ((uint32_t)0x0000001C)
/// DEEPSLEEP_WAKEUP_IND field mask
#define WCNAON_DEEPSLEEP_WAKEUP_IND_MASK   ((uint32_t)0x0000000F)
/// DEEPSLEEP_WAKEUP_IND field LSB position
#define WCNAON_DEEPSLEEP_WAKEUP_IND_LSB    0
/// DEEPSLEEP_WAKEUP_IND field width
#define WCNAON_DEEPSLEEP_WAKEUP_IND_WIDTH  ((uint32_t)0x00000004)

/// HW_ECO field reset value
#define WCNAON_HW_ECO_RST                  0x0
/// DEEPSLEEP_WAKEUP_IND field reset value
#define WCNAON_DEEPSLEEP_WAKEUP_IND_RST    0x0

/**
 * @brief Constructs a value for the DEEPSLEEP_WAKEUP_IND register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] hweco - The value to use for the hw_eco field.
 * @param[in] deepsleepwakeupind - The value to use for the deepsleep_wakeup_ind field.
 */
__INLINE void wcnaon_deepsleep_wakeup_ind_pack(uint32_t hweco, uint8_t deepsleepwakeupind)
{
    REG_PL_WR(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR,  ((uint32_t)hweco << 4) | ((uint32_t)deepsleepwakeupind << 0));
}

/**
 * @brief Unpacks DEEPSLEEP_WAKEUP_IND's fields from current value of the DEEPSLEEP_WAKEUP_IND register.
 *
 * Reads the DEEPSLEEP_WAKEUP_IND register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] hweco - Will be populated with the current value of this field from the register.
 * @param[out] deepsleepwakeupind - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_deepsleep_wakeup_ind_unpack(uint32_t* hweco, uint8_t* deepsleepwakeupind)
{
    uint32_t localVal = REG_PL_RD(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR);

    *hweco = (localVal & ((uint32_t)0xFFFFFFF0)) >> 4;
    *deepsleepwakeupind = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the hw_eco field in the DEEPSLEEP_WAKEUP_IND register.
 *
 * The DEEPSLEEP_WAKEUP_IND register will be read and the hw_eco field's value will be returned.
 *
 * @return The current value of the hw_eco field in the DEEPSLEEP_WAKEUP_IND register.
 */
__INLINE uint32_t wcnaon_hw_eco_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR);
    return ((localVal & ((uint32_t)0xFFFFFFF0)) >> 4);
}

/**
 * @brief Sets the hw_eco field of the DEEPSLEEP_WAKEUP_IND register.
 *
 * The DEEPSLEEP_WAKEUP_IND register will be read, modified to contain the new field value, and written.
 *
 * @param[in] hweco - The value to set the field to.
 */
__INLINE void wcnaon_hw_eco_setf(uint32_t hweco)
{
    REG_PL_WR(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR, (REG_PL_RD(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR) & ~((uint32_t)0xFFFFFFF0)) | (((uint32_t)hweco << 4) & ((uint32_t)0xFFFFFFF0)));
}

/**
 * @brief Returns the current value of the deepsleep_wakeup_ind field in the DEEPSLEEP_WAKEUP_IND register.
 *
 * The DEEPSLEEP_WAKEUP_IND register will be read and the deepsleep_wakeup_ind field's value will be returned.
 *
 * @return The current value of the deepsleep_wakeup_ind field in the DEEPSLEEP_WAKEUP_IND register.
 */
__INLINE uint8_t wcnaon_deepsleep_wakeup_ind_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief Sets the deepsleep_wakeup_ind field of the DEEPSLEEP_WAKEUP_IND register.
 *
 * The DEEPSLEEP_WAKEUP_IND register will be read, modified to contain the new field value, and written.
 *
 * @param[in] deepsleepwakeupind - The value to set the field to.
 */
__INLINE void wcnaon_deepsleep_wakeup_ind_setf(uint8_t deepsleepwakeupind)
{
    REG_PL_WR(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR, (REG_PL_RD(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR) & ~((uint32_t)0x0000000F)) | (((uint32_t)deepsleepwakeupind << 0) & ((uint32_t)0x0000000F)));
}

/// @}

/**
 * @name BT_RESERVED register definitions
 * <table>
 * <caption id="BT_RESERVED_BF">BT_RESERVED bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>       bt_reserved <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the BT_RESERVED register
#define WCNAON_BT_RESERVED_ADDR   0x4050904C
/// Offset of the BT_RESERVED register from the base address
#define WCNAON_BT_RESERVED_OFFSET 0x0000004C
/// Index of the BT_RESERVED register
#define WCNAON_BT_RESERVED_INDEX  0x00000013
/// Reset value of the BT_RESERVED register
#define WCNAON_BT_RESERVED_RESET  0x00000000

/**
 * @brief Returns the current value of the BT_RESERVED register.
 * The BT_RESERVED register will be read and its value returned.
 * @return The current value of the BT_RESERVED register.
 */
__INLINE uint32_t wcnaon_bt_reserved_get(void)
{
    return REG_PL_RD(WCNAON_BT_RESERVED_ADDR);
}

/**
 * @brief Sets the BT_RESERVED register to a value.
 * The BT_RESERVED register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_bt_reserved_set(uint32_t value)
{
    REG_PL_WR(WCNAON_BT_RESERVED_ADDR, value);
}

// field definitions
/// BT_RESERVED field mask
#define WCNAON_BT_RESERVED_MASK   ((uint32_t)0xFFFFFFFF)
/// BT_RESERVED field LSB position
#define WCNAON_BT_RESERVED_LSB    0
/// BT_RESERVED field width
#define WCNAON_BT_RESERVED_WIDTH  ((uint32_t)0x00000020)

/// BT_RESERVED field reset value
#define WCNAON_BT_RESERVED_RST    0x0

/**
 * @brief Returns the current value of the bt_reserved field in the BT_RESERVED register.
 *
 * The BT_RESERVED register will be read and the bt_reserved field's value will be returned.
 *
 * @return The current value of the bt_reserved field in the BT_RESERVED register.
 */
__INLINE uint32_t wcnaon_bt_reserved_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_RESERVED_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the bt_reserved field of the BT_RESERVED register.
 *
 * The BT_RESERVED register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btreserved - The value to set the field to.
 */
__INLINE void wcnaon_bt_reserved_setf(uint32_t btreserved)
{
    REG_PL_WR(WCNAON_BT_RESERVED_ADDR, ((uint32_t)btreserved << 0) & ((uint32_t)0xFFFFFFFF));
}

/// @}


#endif // _REG_WCNAON_H_

/// @}

