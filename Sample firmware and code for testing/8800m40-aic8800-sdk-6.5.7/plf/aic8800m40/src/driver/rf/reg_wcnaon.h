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
#define WCNAON_BT_MEM_CFG1_ADDR   0x40580000
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
 * @name WIFI_MEM_CFG register definitions
 * <table>
 * <caption id="WIFI_MEM_CFG_BF">WIFI_MEM_CFG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>15:00 <td>      wifi_mem_cfg <td>R <td>R/W <td>0x220
 * </table>
 *
 * @{
 */

/// Address of the WIFI_MEM_CFG register
#define WCNAON_WIFI_MEM_CFG_ADDR   0x40580004
/// Offset of the WIFI_MEM_CFG register from the base address
#define WCNAON_WIFI_MEM_CFG_OFFSET 0x00000004
/// Index of the WIFI_MEM_CFG register
#define WCNAON_WIFI_MEM_CFG_INDEX  0x00000001
/// Reset value of the WIFI_MEM_CFG register
#define WCNAON_WIFI_MEM_CFG_RESET  0x00000220

/**
 * @brief Returns the current value of the WIFI_MEM_CFG register.
 * The WIFI_MEM_CFG register will be read and its value returned.
 * @return The current value of the WIFI_MEM_CFG register.
 */
__INLINE uint32_t wcnaon_wifi_mem_cfg_get(void)
{
    return REG_PL_RD(WCNAON_WIFI_MEM_CFG_ADDR);
}

/**
 * @brief Sets the WIFI_MEM_CFG register to a value.
 * The WIFI_MEM_CFG register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_wifi_mem_cfg_set(uint32_t value)
{
    REG_PL_WR(WCNAON_WIFI_MEM_CFG_ADDR, value);
}

// field definitions
/// WIFI_MEM_CFG field mask
#define WCNAON_WIFI_MEM_CFG_MASK   ((uint32_t)0x0000FFFF)
/// WIFI_MEM_CFG field LSB position
#define WCNAON_WIFI_MEM_CFG_LSB    0
/// WIFI_MEM_CFG field width
#define WCNAON_WIFI_MEM_CFG_WIDTH  ((uint32_t)0x00000010)

/// WIFI_MEM_CFG field reset value
#define WCNAON_WIFI_MEM_CFG_RST    0x220

/**
 * @brief Returns the current value of the wifi_mem_cfg field in the WIFI_MEM_CFG register.
 *
 * The WIFI_MEM_CFG register will be read and the wifi_mem_cfg field's value will be returned.
 *
 * @return The current value of the wifi_mem_cfg field in the WIFI_MEM_CFG register.
 */
__INLINE uint16_t wcnaon_wifi_mem_cfg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_MEM_CFG_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the wifi_mem_cfg field of the WIFI_MEM_CFG register.
 *
 * The WIFI_MEM_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wifimemcfg - The value to set the field to.
 */
__INLINE void wcnaon_wifi_mem_cfg_setf(uint16_t wifimemcfg)
{
    REG_PL_WR(WCNAON_WIFI_MEM_CFG_ADDR, ((uint32_t)wifimemcfg << 0) & ((uint32_t)0x0000FFFF));
}

/// @}

/**
 * @name BT_CLK_CFG0 register definitions
 * <table>
 * <caption id="BT_CLK_CFG0_BF">BT_CLK_CFG0 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31 <td>     bt_div_num_ld <td>R <td>R/W <td>0
 * <tr><td>24:16 <td>          bt_div_M <td>R <td>R/W <td>0x1
 * <tr><td>15:00 <td>          bt_div_N <td>R <td>R/W <td>0x2
 * </table>
 *
 * @{
 */

/// Address of the BT_CLK_CFG0 register
#define WCNAON_BT_CLK_CFG0_ADDR   0x40580008
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
#define WCNAON_BT_DIV_N_MASK        ((uint32_t)0x0000FFFF)
/// BT_DIV_N field LSB position
#define WCNAON_BT_DIV_N_LSB         0
/// BT_DIV_N field width
#define WCNAON_BT_DIV_N_WIDTH       ((uint32_t)0x00000010)

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
    *btdivn = (localVal & ((uint32_t)0x0000FFFF)) >> 0;
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
    return ((localVal & ((uint32_t)0x0000FFFF)) >> 0);
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
    REG_PL_WR(WCNAON_BT_CLK_CFG0_ADDR, (REG_PL_RD(WCNAON_BT_CLK_CFG0_ADDR) & ~((uint32_t)0x0000FFFF)) | (((uint32_t)btdivn << 0) & ((uint32_t)0x0000FFFF)));
}

/// @}

/**
 * @name BT_CLK_CFG1 register definitions
 * <table>
 * <caption id="BT_CLK_CFG1_BF">BT_CLK_CFG1 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>29:24 <td>      bt_cfg_rfsel <td>R <td>R/W <td>0x0
 * <tr><td>22:16 <td>       bt_clkg_cfg <td>R <td>R/W <td>0x0
 * <tr><td>05:00 <td>         bt_clksel <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the BT_CLK_CFG1 register
#define WCNAON_BT_CLK_CFG1_ADDR   0x4058000C
/// Offset of the BT_CLK_CFG1 register from the base address
#define WCNAON_BT_CLK_CFG1_OFFSET 0x0000000C
/// Index of the BT_CLK_CFG1 register
#define WCNAON_BT_CLK_CFG1_INDEX  0x00000003
/// Reset value of the BT_CLK_CFG1 register
#define WCNAON_BT_CLK_CFG1_RESET  0x00000000

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
#define WCNAON_BT_CFG_RFSEL_MASK   ((uint32_t)0x3F000000)
/// BT_CFG_RFSEL field LSB position
#define WCNAON_BT_CFG_RFSEL_LSB    24
/// BT_CFG_RFSEL field width
#define WCNAON_BT_CFG_RFSEL_WIDTH  ((uint32_t)0x00000006)
/// BT_CLKG_CFG field mask
#define WCNAON_BT_CLKG_CFG_MASK    ((uint32_t)0x007F0000)
/// BT_CLKG_CFG field LSB position
#define WCNAON_BT_CLKG_CFG_LSB     16
/// BT_CLKG_CFG field width
#define WCNAON_BT_CLKG_CFG_WIDTH   ((uint32_t)0x00000007)
/// BT_CLKSEL field mask
#define WCNAON_BT_CLKSEL_MASK      ((uint32_t)0x0000003F)
/// BT_CLKSEL field LSB position
#define WCNAON_BT_CLKSEL_LSB       0
/// BT_CLKSEL field width
#define WCNAON_BT_CLKSEL_WIDTH     ((uint32_t)0x00000006)

/// BT_CFG_RFSEL field reset value
#define WCNAON_BT_CFG_RFSEL_RST    0x0
/// BT_CLKG_CFG field reset value
#define WCNAON_BT_CLKG_CFG_RST     0x0
/// BT_CLKSEL field reset value
#define WCNAON_BT_CLKSEL_RST       0x0

/**
 * @brief Constructs a value for the BT_CLK_CFG1 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btcfgrfsel - The value to use for the bt_cfg_rfsel field.
 * @param[in] btclkgcfg - The value to use for the bt_clkg_cfg field.
 * @param[in] btclksel - The value to use for the bt_clksel field.
 */
__INLINE void wcnaon_bt_clk_cfg1_pack(uint8_t btcfgrfsel, uint8_t btclkgcfg, uint8_t btclksel)
{
    REG_PL_WR(WCNAON_BT_CLK_CFG1_ADDR,  ((uint32_t)btcfgrfsel << 24) | ((uint32_t)btclkgcfg << 16) | ((uint32_t)btclksel << 0));
}

/**
 * @brief Unpacks BT_CLK_CFG1's fields from current value of the BT_CLK_CFG1 register.
 *
 * Reads the BT_CLK_CFG1 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btcfgrfsel - Will be populated with the current value of this field from the register.
 * @param[out] btclkgcfg - Will be populated with the current value of this field from the register.
 * @param[out] btclksel - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_bt_clk_cfg1_unpack(uint8_t* btcfgrfsel, uint8_t* btclkgcfg, uint8_t* btclksel)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_CLK_CFG1_ADDR);

    *btcfgrfsel = (localVal & ((uint32_t)0x3F000000)) >> 24;
    *btclkgcfg = (localVal & ((uint32_t)0x007F0000)) >> 16;
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
 * @name WIFI_SOFT_WAKEUP_REQ register definitions
 * <table>
 * <caption id="WIFI_SOFT_WAKEUP_REQ_BF">WIFI_SOFT_WAKEUP_REQ bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>11 <td>  bt_wakeup_lp_sel <td>R <td>R/W <td>0
 * <tr><td>10 <td>wlan_wakeup_lp_sel <td>R <td>R/W <td>0
 * <tr><td>09 <td>   bt_cfg_power_en <td>R <td>R/W <td>0
 * <tr><td>08 <td>     bt_cfg_cpu_en <td>R <td>R/W <td>1
 * <tr><td>06:05 <td>           mon_sel <td>R <td>R/W <td>0x0
 * <tr><td>04 <td>wlan_radio_cg_sleep_en <td>R <td>R/W <td>0
 * <tr><td>03 <td>wlan_cpu_wakeup_en <td>R <td>R/W <td>0
 * <tr><td>02 <td>wlan_radio_sleep_en <td>R <td>R/W <td>0
 * <tr><td>01 <td>wlan_power_sleep_en <td>R <td>R/W <td>0
 * <tr><td>00 <td>wlan_soft_wakeup_req <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the WIFI_SOFT_WAKEUP_REQ register
#define WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR   0x40580010
/// Offset of the WIFI_SOFT_WAKEUP_REQ register from the base address
#define WCNAON_WIFI_SOFT_WAKEUP_REQ_OFFSET 0x00000010
/// Index of the WIFI_SOFT_WAKEUP_REQ register
#define WCNAON_WIFI_SOFT_WAKEUP_REQ_INDEX  0x00000004
/// Reset value of the WIFI_SOFT_WAKEUP_REQ register
#define WCNAON_WIFI_SOFT_WAKEUP_REQ_RESET  0x00000100

/**
 * @brief Returns the current value of the WIFI_SOFT_WAKEUP_REQ register.
 * The WIFI_SOFT_WAKEUP_REQ register will be read and its value returned.
 * @return The current value of the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint32_t wcnaon_wifi_soft_wakeup_req_get(void)
{
    return REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
}

/**
 * @brief Sets the WIFI_SOFT_WAKEUP_REQ register to a value.
 * The WIFI_SOFT_WAKEUP_REQ register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_wifi_soft_wakeup_req_set(uint32_t value)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, value);
}

// field definitions
/// BT_WAKEUP_LP_SEL field bit
#define WCNAON_BT_WAKEUP_LP_SEL_BIT          ((uint32_t)0x00000800)
/// BT_WAKEUP_LP_SEL field position
#define WCNAON_BT_WAKEUP_LP_SEL_POS          11
/// WLAN_WAKEUP_LP_SEL field bit
#define WCNAON_WLAN_WAKEUP_LP_SEL_BIT        ((uint32_t)0x00000400)
/// WLAN_WAKEUP_LP_SEL field position
#define WCNAON_WLAN_WAKEUP_LP_SEL_POS        10
/// BT_CFG_POWER_EN field bit
#define WCNAON_BT_CFG_POWER_EN_BIT           ((uint32_t)0x00000200)
/// BT_CFG_POWER_EN field position
#define WCNAON_BT_CFG_POWER_EN_POS           9
/// BT_CFG_CPU_EN field bit
#define WCNAON_BT_CFG_CPU_EN_BIT             ((uint32_t)0x00000100)
/// BT_CFG_CPU_EN field position
#define WCNAON_BT_CFG_CPU_EN_POS             8
/// MON_SEL field mask
#define WCNAON_MON_SEL_MASK                  ((uint32_t)0x00000060)
/// MON_SEL field LSB position
#define WCNAON_MON_SEL_LSB                   5
/// MON_SEL field width
#define WCNAON_MON_SEL_WIDTH                 ((uint32_t)0x00000002)
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

/// BT_WAKEUP_LP_SEL field reset value
#define WCNAON_BT_WAKEUP_LP_SEL_RST          0x0
/// WLAN_WAKEUP_LP_SEL field reset value
#define WCNAON_WLAN_WAKEUP_LP_SEL_RST        0x0
/// BT_CFG_POWER_EN field reset value
#define WCNAON_BT_CFG_POWER_EN_RST           0x0
/// BT_CFG_CPU_EN field reset value
#define WCNAON_BT_CFG_CPU_EN_RST             0x1
/// MON_SEL field reset value
#define WCNAON_MON_SEL_RST                   0x0
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
 * @brief Constructs a value for the WIFI_SOFT_WAKEUP_REQ register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btwakeuplpsel - The value to use for the bt_wakeup_lp_sel field.
 * @param[in] wlanwakeuplpsel - The value to use for the wlan_wakeup_lp_sel field.
 * @param[in] btcfgpoweren - The value to use for the bt_cfg_power_en field.
 * @param[in] btcfgcpuen - The value to use for the bt_cfg_cpu_en field.
 * @param[in] monsel - The value to use for the mon_sel field.
 * @param[in] wlanradiocgsleepen - The value to use for the wlan_radio_cg_sleep_en field.
 * @param[in] wlancpuwakeupen - The value to use for the wlan_cpu_wakeup_en field.
 * @param[in] wlanradiosleepen - The value to use for the wlan_radio_sleep_en field.
 * @param[in] wlanpowersleepen - The value to use for the wlan_power_sleep_en field.
 * @param[in] wlansoftwakeupreq - The value to use for the wlan_soft_wakeup_req field.
 */
__INLINE void wcnaon_wifi_soft_wakeup_req_pack(uint8_t btwakeuplpsel, uint8_t wlanwakeuplpsel, uint8_t btcfgpoweren, uint8_t btcfgcpuen, uint8_t monsel, uint8_t wlanradiocgsleepen, uint8_t wlancpuwakeupen, uint8_t wlanradiosleepen, uint8_t wlanpowersleepen, uint8_t wlansoftwakeupreq)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR,  ((uint32_t)btwakeuplpsel << 11) | ((uint32_t)wlanwakeuplpsel << 10) | ((uint32_t)btcfgpoweren << 9) | ((uint32_t)btcfgcpuen << 8) | ((uint32_t)monsel << 5) | ((uint32_t)wlanradiocgsleepen << 4) | ((uint32_t)wlancpuwakeupen << 3) | ((uint32_t)wlanradiosleepen << 2) | ((uint32_t)wlanpowersleepen << 1) | ((uint32_t)wlansoftwakeupreq << 0));
}

/**
 * @brief Unpacks WIFI_SOFT_WAKEUP_REQ's fields from current value of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * Reads the WIFI_SOFT_WAKEUP_REQ register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] btwakeuplpsel - Will be populated with the current value of this field from the register.
 * @param[out] wlanwakeuplpsel - Will be populated with the current value of this field from the register.
 * @param[out] btcfgpoweren - Will be populated with the current value of this field from the register.
 * @param[out] btcfgcpuen - Will be populated with the current value of this field from the register.
 * @param[out] monsel - Will be populated with the current value of this field from the register.
 * @param[out] wlanradiocgsleepen - Will be populated with the current value of this field from the register.
 * @param[out] wlancpuwakeupen - Will be populated with the current value of this field from the register.
 * @param[out] wlanradiosleepen - Will be populated with the current value of this field from the register.
 * @param[out] wlanpowersleepen - Will be populated with the current value of this field from the register.
 * @param[out] wlansoftwakeupreq - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_wifi_soft_wakeup_req_unpack(uint8_t* btwakeuplpsel, uint8_t* wlanwakeuplpsel, uint8_t* btcfgpoweren, uint8_t* btcfgcpuen, uint8_t* monsel, uint8_t* wlanradiocgsleepen, uint8_t* wlancpuwakeupen, uint8_t* wlanradiosleepen, uint8_t* wlanpowersleepen, uint8_t* wlansoftwakeupreq)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);

    *btwakeuplpsel = (localVal & ((uint32_t)0x00000800)) >> 11;
    *wlanwakeuplpsel = (localVal & ((uint32_t)0x00000400)) >> 10;
    *btcfgpoweren = (localVal & ((uint32_t)0x00000200)) >> 9;
    *btcfgcpuen = (localVal & ((uint32_t)0x00000100)) >> 8;
    *monsel = (localVal & ((uint32_t)0x00000060)) >> 5;
    *wlanradiocgsleepen = (localVal & ((uint32_t)0x00000010)) >> 4;
    *wlancpuwakeupen = (localVal & ((uint32_t)0x00000008)) >> 3;
    *wlanradiosleepen = (localVal & ((uint32_t)0x00000004)) >> 2;
    *wlanpowersleepen = (localVal & ((uint32_t)0x00000002)) >> 1;
    *wlansoftwakeupreq = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the bt_wakeup_lp_sel field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the bt_wakeup_lp_sel field's value will be returned.
 *
 * @return The current value of the bt_wakeup_lp_sel field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_bt_wakeup_lp_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

/**
 * @brief Sets the bt_wakeup_lp_sel field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btwakeuplpsel - The value to set the field to.
 */
__INLINE void wcnaon_bt_wakeup_lp_sel_setf(uint8_t btwakeuplpsel)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000800)) | (((uint32_t)btwakeuplpsel << 11) & ((uint32_t)0x00000800)));
}

/**
 * @brief Returns the current value of the wlan_wakeup_lp_sel field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the wlan_wakeup_lp_sel field's value will be returned.
 *
 * @return The current value of the wlan_wakeup_lp_sel field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_wlan_wakeup_lp_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

/**
 * @brief Sets the wlan_wakeup_lp_sel field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlanwakeuplpsel - The value to set the field to.
 */
__INLINE void wcnaon_wlan_wakeup_lp_sel_setf(uint8_t wlanwakeuplpsel)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000400)) | (((uint32_t)wlanwakeuplpsel << 10) & ((uint32_t)0x00000400)));
}

/**
 * @brief Returns the current value of the bt_cfg_power_en field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the bt_cfg_power_en field's value will be returned.
 *
 * @return The current value of the bt_cfg_power_en field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_bt_cfg_power_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

/**
 * @brief Sets the bt_cfg_power_en field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btcfgpoweren - The value to set the field to.
 */
__INLINE void wcnaon_bt_cfg_power_en_setf(uint8_t btcfgpoweren)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000200)) | (((uint32_t)btcfgpoweren << 9) & ((uint32_t)0x00000200)));
}

/**
 * @brief Returns the current value of the bt_cfg_cpu_en field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the bt_cfg_cpu_en field's value will be returned.
 *
 * @return The current value of the bt_cfg_cpu_en field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_bt_cfg_cpu_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

/**
 * @brief Sets the bt_cfg_cpu_en field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btcfgcpuen - The value to set the field to.
 */
__INLINE void wcnaon_bt_cfg_cpu_en_setf(uint8_t btcfgcpuen)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000100)) | (((uint32_t)btcfgcpuen << 8) & ((uint32_t)0x00000100)));
}

/**
 * @brief Returns the current value of the mon_sel field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the mon_sel field's value will be returned.
 *
 * @return The current value of the mon_sel field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_mon_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000060)) >> 5);
}

/**
 * @brief Sets the mon_sel field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] monsel - The value to set the field to.
 */
__INLINE void wcnaon_mon_sel_setf(uint8_t monsel)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000060)) | (((uint32_t)monsel << 5) & ((uint32_t)0x00000060)));
}

/**
 * @brief Returns the current value of the wlan_radio_cg_sleep_en field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the wlan_radio_cg_sleep_en field's value will be returned.
 *
 * @return The current value of the wlan_radio_cg_sleep_en field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_wlan_radio_cg_sleep_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

/**
 * @brief Sets the wlan_radio_cg_sleep_en field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlanradiocgsleepen - The value to set the field to.
 */
__INLINE void wcnaon_wlan_radio_cg_sleep_en_setf(uint8_t wlanradiocgsleepen)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000010)) | (((uint32_t)wlanradiocgsleepen << 4) & ((uint32_t)0x00000010)));
}

/**
 * @brief Returns the current value of the wlan_cpu_wakeup_en field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the wlan_cpu_wakeup_en field's value will be returned.
 *
 * @return The current value of the wlan_cpu_wakeup_en field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_wlan_cpu_wakeup_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

/**
 * @brief Sets the wlan_cpu_wakeup_en field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlancpuwakeupen - The value to set the field to.
 */
__INLINE void wcnaon_wlan_cpu_wakeup_en_setf(uint8_t wlancpuwakeupen)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000008)) | (((uint32_t)wlancpuwakeupen << 3) & ((uint32_t)0x00000008)));
}

/**
 * @brief Returns the current value of the wlan_radio_sleep_en field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the wlan_radio_sleep_en field's value will be returned.
 *
 * @return The current value of the wlan_radio_sleep_en field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_wlan_radio_sleep_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the wlan_radio_sleep_en field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlanradiosleepen - The value to set the field to.
 */
__INLINE void wcnaon_wlan_radio_sleep_en_setf(uint8_t wlanradiosleepen)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)wlanradiosleepen << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the wlan_power_sleep_en field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the wlan_power_sleep_en field's value will be returned.
 *
 * @return The current value of the wlan_power_sleep_en field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_wlan_power_sleep_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the wlan_power_sleep_en field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlanpowersleepen - The value to set the field to.
 */
__INLINE void wcnaon_wlan_power_sleep_en_setf(uint8_t wlanpowersleepen)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)wlanpowersleepen << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the wlan_soft_wakeup_req field in the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read and the wlan_soft_wakeup_req field's value will be returned.
 *
 * @return The current value of the wlan_soft_wakeup_req field in the WIFI_SOFT_WAKEUP_REQ register.
 */
__INLINE uint8_t wcnaon_wlan_soft_wakeup_req_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the wlan_soft_wakeup_req field of the WIFI_SOFT_WAKEUP_REQ register.
 *
 * The WIFI_SOFT_WAKEUP_REQ register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wlansoftwakeupreq - The value to set the field to.
 */
__INLINE void wcnaon_wlan_soft_wakeup_req_setf(uint8_t wlansoftwakeupreq)
{
    REG_PL_WR(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR, (REG_PL_RD(WCNAON_WIFI_SOFT_WAKEUP_REQ_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)wlansoftwakeupreq << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name WIFI_WAKEUP_DELAY_TIMER register definitions
 * <table>
 * <caption id="WIFI_WAKEUP_DELAY_TIMER_BF">WIFI_WAKEUP_DELAY_TIMER bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:22 <td>         wlan_twrm <td>R <td>W <td>0x0
 * <tr><td>21:11 <td>        wlan_twpwr <td>R <td>W <td>0x0
 * <tr><td>10:00 <td>        wlan_twext <td>R <td>W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the WIFI_WAKEUP_DELAY_TIMER register
#define WCNAON_WIFI_WAKEUP_DELAY_TIMER_ADDR   0x40580014
/// Offset of the WIFI_WAKEUP_DELAY_TIMER register from the base address
#define WCNAON_WIFI_WAKEUP_DELAY_TIMER_OFFSET 0x00000014
/// Index of the WIFI_WAKEUP_DELAY_TIMER register
#define WCNAON_WIFI_WAKEUP_DELAY_TIMER_INDEX  0x00000005
/// Reset value of the WIFI_WAKEUP_DELAY_TIMER register
#define WCNAON_WIFI_WAKEUP_DELAY_TIMER_RESET  0x00000000

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
#define WCNAON_WLAN_TWPWR_RST    0x0
/// WLAN_TWEXT field reset value
#define WCNAON_WLAN_TWEXT_RST    0x0

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
 * <tr><td>01 <td>        wf_rfen_dr <td>R <td>R/W <td>0
 * <tr><td>00 <td>      wf_rf_en_reg <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the WF_RFEN_CTRL register
#define WCNAON_WF_RFEN_CTRL_ADDR   0x40580018
/// Offset of the WF_RFEN_CTRL register from the base address
#define WCNAON_WF_RFEN_CTRL_OFFSET 0x00000018
/// Index of the WF_RFEN_CTRL register
#define WCNAON_WF_RFEN_CTRL_INDEX  0x00000006
/// Reset value of the WF_RFEN_CTRL register
#define WCNAON_WF_RFEN_CTRL_RESET  0x00000000

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
#define WCNAON_WF_RFEN_DR_RST      0x0
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
 * <tr><td>01 <td>        bt_rfen_dr <td>R <td>R/W <td>0
 * <tr><td>00 <td>       bt_rfen_reg <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the BT_RFEN_CTRL register
#define WCNAON_BT_RFEN_CTRL_ADDR   0x4058001C
/// Offset of the BT_RFEN_CTRL register from the base address
#define WCNAON_BT_RFEN_CTRL_OFFSET 0x0000001C
/// Index of the BT_RFEN_CTRL register
#define WCNAON_BT_RFEN_CTRL_INDEX  0x00000007
/// Reset value of the BT_RFEN_CTRL register
#define WCNAON_BT_RFEN_CTRL_RESET  0x00000000

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
#define WCNAON_BT_RFEN_DR_BIT     ((uint32_t)0x00000002)
/// BT_RFEN_DR field position
#define WCNAON_BT_RFEN_DR_POS     1
/// BT_RFEN_REG field bit
#define WCNAON_BT_RFEN_REG_BIT    ((uint32_t)0x00000001)
/// BT_RFEN_REG field position
#define WCNAON_BT_RFEN_REG_POS    0

/// BT_RFEN_DR field reset value
#define WCNAON_BT_RFEN_DR_RST     0x0
/// BT_RFEN_REG field reset value
#define WCNAON_BT_RFEN_REG_RST    0x0

/**
 * @brief Constructs a value for the BT_RFEN_CTRL register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] btrfendr - The value to use for the bt_rfen_dr field.
 * @param[in] btrfenreg - The value to use for the bt_rfen_reg field.
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
 * @brief Returns the current value of the bt_rfen_reg field in the BT_RFEN_CTRL register.
 *
 * The BT_RFEN_CTRL register will be read and the bt_rfen_reg field's value will be returned.
 *
 * @return The current value of the bt_rfen_reg field in the BT_RFEN_CTRL register.
 */
__INLINE uint8_t wcnaon_bt_rfen_reg_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_RFEN_CTRL_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the bt_rfen_reg field of the BT_RFEN_CTRL register.
 *
 * The BT_RFEN_CTRL register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btrfenreg - The value to set the field to.
 */
__INLINE void wcnaon_bt_rfen_reg_setf(uint8_t btrfenreg)
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
 * <tr><td>30 <td>             MODE1 <td>R <td>R/W <td>0
 * <tr><td>29 <td>     SPI_READ_FLAG <td>R <td>R/W <td>0
 * <tr><td>24 <td>                CS <td>R/W <td>R/W <td>1
 * <tr><td>23:20 <td>         PRESCALER <td>R <td>R/W <td>0x0
 * <tr><td>19:16 <td>           ADDRESS <td>R/W <td>R/W <td>0x0
 * <tr><td>13:00 <td>              DATA <td>R/W <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the MAXIM_SPI register
#define WCNAON_MAXIM_SPI_ADDR   0x40580020
/// Offset of the MAXIM_SPI register from the base address
#define WCNAON_MAXIM_SPI_OFFSET 0x00000020
/// Index of the MAXIM_SPI register
#define WCNAON_MAXIM_SPI_INDEX  0x00000008
/// Reset value of the MAXIM_SPI register
#define WCNAON_MAXIM_SPI_RESET  0x01000000

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
#define WCNAON_START_DONE_BIT       ((uint32_t)0x80000000)
/// START_DONE field position
#define WCNAON_START_DONE_POS       31
/// MODE1 field bit
#define WCNAON_MODE1_BIT            ((uint32_t)0x40000000)
/// MODE1 field position
#define WCNAON_MODE1_POS            30
/// SPI_READ_FLAG field bit
#define WCNAON_SPI_READ_FLAG_BIT    ((uint32_t)0x20000000)
/// SPI_READ_FLAG field position
#define WCNAON_SPI_READ_FLAG_POS    29
/// CS field bit
#define WCNAON_CS_BIT               ((uint32_t)0x01000000)
/// CS field position
#define WCNAON_CS_POS               24
/// PRESCALER field mask
#define WCNAON_PRESCALER_MASK       ((uint32_t)0x00F00000)
/// PRESCALER field LSB position
#define WCNAON_PRESCALER_LSB        20
/// PRESCALER field width
#define WCNAON_PRESCALER_WIDTH      ((uint32_t)0x00000004)
/// ADDRESS field mask
#define WCNAON_ADDRESS_MASK         ((uint32_t)0x000F0000)
/// ADDRESS field LSB position
#define WCNAON_ADDRESS_LSB          16
/// ADDRESS field width
#define WCNAON_ADDRESS_WIDTH        ((uint32_t)0x00000004)
/// DATA field mask
#define WCNAON_DATA_MASK            ((uint32_t)0x00003FFF)
/// DATA field LSB position
#define WCNAON_DATA_LSB             0
/// DATA field width
#define WCNAON_DATA_WIDTH           ((uint32_t)0x0000000E)

/// START_DONE field reset value
#define WCNAON_START_DONE_RST       0x0
/// MODE1 field reset value
#define WCNAON_MODE1_RST            0x0
/// SPI_READ_FLAG field reset value
#define WCNAON_SPI_READ_FLAG_RST    0x0
/// CS field reset value
#define WCNAON_CS_RST               0x1
/// PRESCALER field reset value
#define WCNAON_PRESCALER_RST        0x0
/// ADDRESS field reset value
#define WCNAON_ADDRESS_RST          0x0
/// DATA field reset value
#define WCNAON_DATA_RST             0x0

/**
 * @brief Constructs a value for the MAXIM_SPI register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] startdone - The value to use for the START_DONE field.
 * @param[in] mode1 - The value to use for the MODE1 field.
 * @param[in] spireadflag - The value to use for the SPI_READ_FLAG field.
 * @param[in] cs - The value to use for the CS field.
 * @param[in] prescaler - The value to use for the PRESCALER field.
 * @param[in] address - The value to use for the ADDRESS field.
 * @param[in] data - The value to use for the DATA field.
 */
__INLINE void wcnaon_maxim_spi_pack(uint8_t startdone, uint8_t mode1, uint8_t spireadflag, uint8_t cs, uint8_t prescaler, uint8_t address, uint16_t data)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR,  ((uint32_t)startdone << 31) | ((uint32_t)mode1 << 30) | ((uint32_t)spireadflag << 29) | ((uint32_t)cs << 24) | ((uint32_t)prescaler << 20) | ((uint32_t)address << 16) | ((uint32_t)data << 0));
}

/**
 * @brief Unpacks MAXIM_SPI's fields from current value of the MAXIM_SPI register.
 *
 * Reads the MAXIM_SPI register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] startdone - Will be populated with the current value of this field from the register.
 * @param[out] mode1 - Will be populated with the current value of this field from the register.
 * @param[out] spireadflag - Will be populated with the current value of this field from the register.
 * @param[out] cs - Will be populated with the current value of this field from the register.
 * @param[out] prescaler - Will be populated with the current value of this field from the register.
 * @param[out] address - Will be populated with the current value of this field from the register.
 * @param[out] data - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_maxim_spi_unpack(uint8_t* startdone, uint8_t* mode1, uint8_t* spireadflag, uint8_t* cs, uint8_t* prescaler, uint8_t* address, uint16_t* data)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);

    *startdone = (localVal & ((uint32_t)0x80000000)) >> 31;
    *mode1 = (localVal & ((uint32_t)0x40000000)) >> 30;
    *spireadflag = (localVal & ((uint32_t)0x20000000)) >> 29;
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
 * @brief Returns the current value of the MODE1 field in the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read and the MODE1 field's value will be returned.
 *
 * @return The current value of the MODE1 field in the MAXIM_SPI register.
 */
__INLINE uint8_t wcnaon_mode1_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

/**
 * @brief Sets the MODE1 field of the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read, modified to contain the new field value, and written.
 *
 * @param[in] mode1 - The value to set the field to.
 */
__INLINE void wcnaon_mode1_setf(uint8_t mode1)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_ADDR) & ~((uint32_t)0x40000000)) | (((uint32_t)mode1 << 30) & ((uint32_t)0x40000000)));
}

/**
 * @brief Returns the current value of the SPI_READ_FLAG field in the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read and the SPI_READ_FLAG field's value will be returned.
 *
 * @return The current value of the SPI_READ_FLAG field in the MAXIM_SPI register.
 */
__INLINE uint8_t wcnaon_spi_read_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_ADDR);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

/**
 * @brief Sets the SPI_READ_FLAG field of the MAXIM_SPI register.
 *
 * The MAXIM_SPI register will be read, modified to contain the new field value, and written.
 *
 * @param[in] spireadflag - The value to set the field to.
 */
__INLINE void wcnaon_spi_read_flag_setf(uint8_t spireadflag)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_ADDR) & ~((uint32_t)0x20000000)) | (((uint32_t)spireadflag << 29) & ((uint32_t)0x20000000)));
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
 * @name MAXIM_SPI_CONFIG1 register definitions
 * <table>
 * <caption id="MAXIM_SPI_CONFIG1_BF">MAXIM_SPI_CONFIG1 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>          SPI_CMD2 <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the MAXIM_SPI_CONFIG1 register
#define WCNAON_MAXIM_SPI_CONFIG1_ADDR   0x40580024
/// Offset of the MAXIM_SPI_CONFIG1 register from the base address
#define WCNAON_MAXIM_SPI_CONFIG1_OFFSET 0x00000024
/// Index of the MAXIM_SPI_CONFIG1 register
#define WCNAON_MAXIM_SPI_CONFIG1_INDEX  0x00000009
/// Reset value of the MAXIM_SPI_CONFIG1 register
#define WCNAON_MAXIM_SPI_CONFIG1_RESET  0x00000000

/**
 * @brief Returns the current value of the MAXIM_SPI_CONFIG1 register.
 * The MAXIM_SPI_CONFIG1 register will be read and its value returned.
 * @return The current value of the MAXIM_SPI_CONFIG1 register.
 */
__INLINE uint32_t wcnaon_maxim_spi_config1_get(void)
{
    return REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG1_ADDR);
}

/**
 * @brief Sets the MAXIM_SPI_CONFIG1 register to a value.
 * The MAXIM_SPI_CONFIG1 register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_maxim_spi_config1_set(uint32_t value)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG1_ADDR, value);
}

// field definitions
/// SPI_CMD2 field mask
#define WCNAON_SPI_CMD2_MASK   ((uint32_t)0xFFFFFFFF)
/// SPI_CMD2 field LSB position
#define WCNAON_SPI_CMD2_LSB    0
/// SPI_CMD2 field width
#define WCNAON_SPI_CMD2_WIDTH  ((uint32_t)0x00000020)

/// SPI_CMD2 field reset value
#define WCNAON_SPI_CMD2_RST    0x0

/**
 * @brief Returns the current value of the SPI_CMD2 field in the MAXIM_SPI_CONFIG1 register.
 *
 * The MAXIM_SPI_CONFIG1 register will be read and the SPI_CMD2 field's value will be returned.
 *
 * @return The current value of the SPI_CMD2 field in the MAXIM_SPI_CONFIG1 register.
 */
__INLINE uint32_t wcnaon_spi_cmd2_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG1_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the SPI_CMD2 field of the MAXIM_SPI_CONFIG1 register.
 *
 * The MAXIM_SPI_CONFIG1 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] spicmd2 - The value to set the field to.
 */
__INLINE void wcnaon_spi_cmd2_setf(uint32_t spicmd2)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG1_ADDR, ((uint32_t)spicmd2 << 0) & ((uint32_t)0xFFFFFFFF));
}

/// @}

/**
 * @name MAXIM_SPI_CONFIG2 register definitions
 * <table>
 * <caption id="MAXIM_SPI_CONFIG2_BF">MAXIM_SPI_CONFIG2 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:00 <td>       SPI_DATA_RD <td>W <td>R <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the MAXIM_SPI_CONFIG2 register
#define WCNAON_MAXIM_SPI_CONFIG2_ADDR   0x40580028
/// Offset of the MAXIM_SPI_CONFIG2 register from the base address
#define WCNAON_MAXIM_SPI_CONFIG2_OFFSET 0x00000028
/// Index of the MAXIM_SPI_CONFIG2 register
#define WCNAON_MAXIM_SPI_CONFIG2_INDEX  0x0000000A
/// Reset value of the MAXIM_SPI_CONFIG2 register
#define WCNAON_MAXIM_SPI_CONFIG2_RESET  0x00000000

/**
 * @brief Returns the current value of the MAXIM_SPI_CONFIG2 register.
 * The MAXIM_SPI_CONFIG2 register will be read and its value returned.
 * @return The current value of the MAXIM_SPI_CONFIG2 register.
 */
__INLINE uint32_t wcnaon_maxim_spi_config2_get(void)
{
    return REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG2_ADDR);
}

/**
 * @brief Sets the MAXIM_SPI_CONFIG2 register to a value.
 * The MAXIM_SPI_CONFIG2 register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_maxim_spi_config2_set(uint32_t value)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG2_ADDR, value);
}

// field definitions
/// SPI_DATA_RD field mask
#define WCNAON_SPI_DATA_RD_MASK   ((uint32_t)0xFFFFFFFF)
/// SPI_DATA_RD field LSB position
#define WCNAON_SPI_DATA_RD_LSB    0
/// SPI_DATA_RD field width
#define WCNAON_SPI_DATA_RD_WIDTH  ((uint32_t)0x00000020)

/// SPI_DATA_RD field reset value
#define WCNAON_SPI_DATA_RD_RST    0x0

/**
 * @brief Returns the current value of the SPI_DATA_RD field in the MAXIM_SPI_CONFIG2 register.
 *
 * The MAXIM_SPI_CONFIG2 register will be read and the SPI_DATA_RD field's value will be returned.
 *
 * @return The current value of the SPI_DATA_RD field in the MAXIM_SPI_CONFIG2 register.
 */
__INLINE uint32_t wcnaon_spi_data_rd_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG2_ADDR);
    return (localVal >> 0);
}

/// @}

/**
 * @name MAXIM_SPI_CONFIG3 register definitions
 * <table>
 * <caption id="MAXIM_SPI_CONFIG3_BF">MAXIM_SPI_CONFIG3 bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>20:16 <td>        SPI_RD_LEN <td>R <td>R/W <td>0x0
 * <tr><td>15 <td>    SPI_SEL_AD9371 <td>R <td>R/W <td>0
 * <tr><td>14 <td>    SPI_SEL_AD9528 <td>R <td>R/W <td>0
 * <tr><td>13 <td>      SPI_SEL_PORT <td>R <td>R/W <td>1
 * <tr><td>12 <td>     SPI_SEL_MAXIM <td>R <td>R/W <td>0
 * <tr><td>10:04 <td>           SPI_LEN <td>R <td>R/W <td>0x0
 * <tr><td>00 <td>    SPI_LEN_CFG_EN <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the MAXIM_SPI_CONFIG3 register
#define WCNAON_MAXIM_SPI_CONFIG3_ADDR   0x4058002C
/// Offset of the MAXIM_SPI_CONFIG3 register from the base address
#define WCNAON_MAXIM_SPI_CONFIG3_OFFSET 0x0000002C
/// Index of the MAXIM_SPI_CONFIG3 register
#define WCNAON_MAXIM_SPI_CONFIG3_INDEX  0x0000000B
/// Reset value of the MAXIM_SPI_CONFIG3 register
#define WCNAON_MAXIM_SPI_CONFIG3_RESET  0x00002000

/**
 * @brief Returns the current value of the MAXIM_SPI_CONFIG3 register.
 * The MAXIM_SPI_CONFIG3 register will be read and its value returned.
 * @return The current value of the MAXIM_SPI_CONFIG3 register.
 */
__INLINE uint32_t wcnaon_maxim_spi_config3_get(void)
{
    return REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR);
}

/**
 * @brief Sets the MAXIM_SPI_CONFIG3 register to a value.
 * The MAXIM_SPI_CONFIG3 register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_maxim_spi_config3_set(uint32_t value)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG3_ADDR, value);
}

// field definitions
/// SPI_RD_LEN field mask
#define WCNAON_SPI_RD_LEN_MASK       ((uint32_t)0x001F0000)
/// SPI_RD_LEN field LSB position
#define WCNAON_SPI_RD_LEN_LSB        16
/// SPI_RD_LEN field width
#define WCNAON_SPI_RD_LEN_WIDTH      ((uint32_t)0x00000005)
/// SPI_SEL_AD9371 field bit
#define WCNAON_SPI_SEL_AD9371_BIT    ((uint32_t)0x00008000)
/// SPI_SEL_AD9371 field position
#define WCNAON_SPI_SEL_AD9371_POS    15
/// SPI_SEL_AD9528 field bit
#define WCNAON_SPI_SEL_AD9528_BIT    ((uint32_t)0x00004000)
/// SPI_SEL_AD9528 field position
#define WCNAON_SPI_SEL_AD9528_POS    14
/// SPI_SEL_PORT field bit
#define WCNAON_SPI_SEL_PORT_BIT      ((uint32_t)0x00002000)
/// SPI_SEL_PORT field position
#define WCNAON_SPI_SEL_PORT_POS      13
/// SPI_SEL_MAXIM field bit
#define WCNAON_SPI_SEL_MAXIM_BIT     ((uint32_t)0x00001000)
/// SPI_SEL_MAXIM field position
#define WCNAON_SPI_SEL_MAXIM_POS     12
/// SPI_LEN field mask
#define WCNAON_SPI_LEN_MASK          ((uint32_t)0x000007F0)
/// SPI_LEN field LSB position
#define WCNAON_SPI_LEN_LSB           4
/// SPI_LEN field width
#define WCNAON_SPI_LEN_WIDTH         ((uint32_t)0x00000007)
/// SPI_LEN_CFG_EN field bit
#define WCNAON_SPI_LEN_CFG_EN_BIT    ((uint32_t)0x00000001)
/// SPI_LEN_CFG_EN field position
#define WCNAON_SPI_LEN_CFG_EN_POS    0

/// SPI_RD_LEN field reset value
#define WCNAON_SPI_RD_LEN_RST        0x0
/// SPI_SEL_AD9371 field reset value
#define WCNAON_SPI_SEL_AD9371_RST    0x0
/// SPI_SEL_AD9528 field reset value
#define WCNAON_SPI_SEL_AD9528_RST    0x0
/// SPI_SEL_PORT field reset value
#define WCNAON_SPI_SEL_PORT_RST      0x1
/// SPI_SEL_MAXIM field reset value
#define WCNAON_SPI_SEL_MAXIM_RST     0x0
/// SPI_LEN field reset value
#define WCNAON_SPI_LEN_RST           0x0
/// SPI_LEN_CFG_EN field reset value
#define WCNAON_SPI_LEN_CFG_EN_RST    0x0

/**
 * @brief Constructs a value for the MAXIM_SPI_CONFIG3 register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] spirdlen - The value to use for the SPI_RD_LEN field.
 * @param[in] spiselad9371 - The value to use for the SPI_SEL_AD9371 field.
 * @param[in] spiselad9528 - The value to use for the SPI_SEL_AD9528 field.
 * @param[in] spiselport - The value to use for the SPI_SEL_PORT field.
 * @param[in] spiselmaxim - The value to use for the SPI_SEL_MAXIM field.
 * @param[in] spilen - The value to use for the SPI_LEN field.
 * @param[in] spilencfgen - The value to use for the SPI_LEN_CFG_EN field.
 */
__INLINE void wcnaon_maxim_spi_config3_pack(uint8_t spirdlen, uint8_t spiselad9371, uint8_t spiselad9528, uint8_t spiselport, uint8_t spiselmaxim, uint8_t spilen, uint8_t spilencfgen)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG3_ADDR,  ((uint32_t)spirdlen << 16) | ((uint32_t)spiselad9371 << 15) | ((uint32_t)spiselad9528 << 14) | ((uint32_t)spiselport << 13) | ((uint32_t)spiselmaxim << 12) | ((uint32_t)spilen << 4) | ((uint32_t)spilencfgen << 0));
}

/**
 * @brief Unpacks MAXIM_SPI_CONFIG3's fields from current value of the MAXIM_SPI_CONFIG3 register.
 *
 * Reads the MAXIM_SPI_CONFIG3 register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] spirdlen - Will be populated with the current value of this field from the register.
 * @param[out] spiselad9371 - Will be populated with the current value of this field from the register.
 * @param[out] spiselad9528 - Will be populated with the current value of this field from the register.
 * @param[out] spiselport - Will be populated with the current value of this field from the register.
 * @param[out] spiselmaxim - Will be populated with the current value of this field from the register.
 * @param[out] spilen - Will be populated with the current value of this field from the register.
 * @param[out] spilencfgen - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_maxim_spi_config3_unpack(uint8_t* spirdlen, uint8_t* spiselad9371, uint8_t* spiselad9528, uint8_t* spiselport, uint8_t* spiselmaxim, uint8_t* spilen, uint8_t* spilencfgen)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR);

    *spirdlen = (localVal & ((uint32_t)0x001F0000)) >> 16;
    *spiselad9371 = (localVal & ((uint32_t)0x00008000)) >> 15;
    *spiselad9528 = (localVal & ((uint32_t)0x00004000)) >> 14;
    *spiselport = (localVal & ((uint32_t)0x00002000)) >> 13;
    *spiselmaxim = (localVal & ((uint32_t)0x00001000)) >> 12;
    *spilen = (localVal & ((uint32_t)0x000007F0)) >> 4;
    *spilencfgen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the SPI_RD_LEN field in the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read and the SPI_RD_LEN field's value will be returned.
 *
 * @return The current value of the SPI_RD_LEN field in the MAXIM_SPI_CONFIG3 register.
 */
__INLINE uint8_t wcnaon_spi_rd_len_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR);
    return ((localVal & ((uint32_t)0x001F0000)) >> 16);
}

/**
 * @brief Sets the SPI_RD_LEN field of the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] spirdlen - The value to set the field to.
 */
__INLINE void wcnaon_spi_rd_len_setf(uint8_t spirdlen)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG3_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR) & ~((uint32_t)0x001F0000)) | (((uint32_t)spirdlen << 16) & ((uint32_t)0x001F0000)));
}

/**
 * @brief Returns the current value of the SPI_SEL_AD9371 field in the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read and the SPI_SEL_AD9371 field's value will be returned.
 *
 * @return The current value of the SPI_SEL_AD9371 field in the MAXIM_SPI_CONFIG3 register.
 */
__INLINE uint8_t wcnaon_spi_sel_ad9371_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

/**
 * @brief Sets the SPI_SEL_AD9371 field of the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] spiselad9371 - The value to set the field to.
 */
__INLINE void wcnaon_spi_sel_ad9371_setf(uint8_t spiselad9371)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG3_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR) & ~((uint32_t)0x00008000)) | (((uint32_t)spiselad9371 << 15) & ((uint32_t)0x00008000)));
}

/**
 * @brief Returns the current value of the SPI_SEL_AD9528 field in the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read and the SPI_SEL_AD9528 field's value will be returned.
 *
 * @return The current value of the SPI_SEL_AD9528 field in the MAXIM_SPI_CONFIG3 register.
 */
__INLINE uint8_t wcnaon_spi_sel_ad9528_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

/**
 * @brief Sets the SPI_SEL_AD9528 field of the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] spiselad9528 - The value to set the field to.
 */
__INLINE void wcnaon_spi_sel_ad9528_setf(uint8_t spiselad9528)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG3_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR) & ~((uint32_t)0x00004000)) | (((uint32_t)spiselad9528 << 14) & ((uint32_t)0x00004000)));
}

/**
 * @brief Returns the current value of the SPI_SEL_PORT field in the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read and the SPI_SEL_PORT field's value will be returned.
 *
 * @return The current value of the SPI_SEL_PORT field in the MAXIM_SPI_CONFIG3 register.
 */
__INLINE uint8_t wcnaon_spi_sel_port_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

/**
 * @brief Sets the SPI_SEL_PORT field of the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] spiselport - The value to set the field to.
 */
__INLINE void wcnaon_spi_sel_port_setf(uint8_t spiselport)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG3_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR) & ~((uint32_t)0x00002000)) | (((uint32_t)spiselport << 13) & ((uint32_t)0x00002000)));
}

/**
 * @brief Returns the current value of the SPI_SEL_MAXIM field in the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read and the SPI_SEL_MAXIM field's value will be returned.
 *
 * @return The current value of the SPI_SEL_MAXIM field in the MAXIM_SPI_CONFIG3 register.
 */
__INLINE uint8_t wcnaon_spi_sel_maxim_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Sets the SPI_SEL_MAXIM field of the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] spiselmaxim - The value to set the field to.
 */
__INLINE void wcnaon_spi_sel_maxim_setf(uint8_t spiselmaxim)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG3_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR) & ~((uint32_t)0x00001000)) | (((uint32_t)spiselmaxim << 12) & ((uint32_t)0x00001000)));
}

/**
 * @brief Returns the current value of the SPI_LEN field in the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read and the SPI_LEN field's value will be returned.
 *
 * @return The current value of the SPI_LEN field in the MAXIM_SPI_CONFIG3 register.
 */
__INLINE uint8_t wcnaon_spi_len_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR);
    return ((localVal & ((uint32_t)0x000007F0)) >> 4);
}

/**
 * @brief Sets the SPI_LEN field of the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] spilen - The value to set the field to.
 */
__INLINE void wcnaon_spi_len_setf(uint8_t spilen)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG3_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR) & ~((uint32_t)0x000007F0)) | (((uint32_t)spilen << 4) & ((uint32_t)0x000007F0)));
}

/**
 * @brief Returns the current value of the SPI_LEN_CFG_EN field in the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read and the SPI_LEN_CFG_EN field's value will be returned.
 *
 * @return The current value of the SPI_LEN_CFG_EN field in the MAXIM_SPI_CONFIG3 register.
 */
__INLINE uint8_t wcnaon_spi_len_cfg_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the SPI_LEN_CFG_EN field of the MAXIM_SPI_CONFIG3 register.
 *
 * The MAXIM_SPI_CONFIG3 register will be read, modified to contain the new field value, and written.
 *
 * @param[in] spilencfgen - The value to set the field to.
 */
__INLINE void wcnaon_spi_len_cfg_en_setf(uint8_t spilencfgen)
{
    REG_PL_WR(WCNAON_MAXIM_SPI_CONFIG3_ADDR, (REG_PL_RD(WCNAON_MAXIM_SPI_CONFIG3_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)spilencfgen << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name UART_CFG register definitions
 * <table>
 * <caption id="UART_CFG_BF">UART_CFG bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>12 <td>     UART_BUF_FULL <td>W <td>R <td>0
 * <tr><td>11:08 <td>             DIV_C <td>R <td>R/W <td>0x7
 * <tr><td>07:04 <td>             DIV_B <td>R <td>R/W <td>0x7
 * <tr><td>02 <td>       PARITY_EVEN <td>R <td>R/W <td>1
 * <tr><td>01 <td>         PARITY_EN <td>R <td>R/W <td>1
 * <tr><td>00 <td>           UART_EN <td>R <td>R/W <td>0
 * </table>
 *
 * @{
 */

/// Address of the UART_CFG register
#define WCNAON_UART_CFG_ADDR   0x40580040
/// Offset of the UART_CFG register from the base address
#define WCNAON_UART_CFG_OFFSET 0x00000040
/// Index of the UART_CFG register
#define WCNAON_UART_CFG_INDEX  0x00000010
/// Reset value of the UART_CFG register
#define WCNAON_UART_CFG_RESET  0x00000776

/**
 * @brief Returns the current value of the UART_CFG register.
 * The UART_CFG register will be read and its value returned.
 * @return The current value of the UART_CFG register.
 */
__INLINE uint32_t wcnaon_uart_cfg_get(void)
{
    return REG_PL_RD(WCNAON_UART_CFG_ADDR);
}

/**
 * @brief Sets the UART_CFG register to a value.
 * The UART_CFG register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_uart_cfg_set(uint32_t value)
{
    REG_PL_WR(WCNAON_UART_CFG_ADDR, value);
}

// field definitions
/// UART_BUF_FULL field bit
#define WCNAON_UART_BUF_FULL_BIT    ((uint32_t)0x00001000)
/// UART_BUF_FULL field position
#define WCNAON_UART_BUF_FULL_POS    12
/// DIV_C field mask
#define WCNAON_DIV_C_MASK           ((uint32_t)0x00000F00)
/// DIV_C field LSB position
#define WCNAON_DIV_C_LSB            8
/// DIV_C field width
#define WCNAON_DIV_C_WIDTH          ((uint32_t)0x00000004)
/// DIV_B field mask
#define WCNAON_DIV_B_MASK           ((uint32_t)0x000000F0)
/// DIV_B field LSB position
#define WCNAON_DIV_B_LSB            4
/// DIV_B field width
#define WCNAON_DIV_B_WIDTH          ((uint32_t)0x00000004)
/// PARITY_EVEN field bit
#define WCNAON_PARITY_EVEN_BIT      ((uint32_t)0x00000004)
/// PARITY_EVEN field position
#define WCNAON_PARITY_EVEN_POS      2
/// PARITY_EN field bit
#define WCNAON_PARITY_EN_BIT        ((uint32_t)0x00000002)
/// PARITY_EN field position
#define WCNAON_PARITY_EN_POS        1
/// UART_EN field bit
#define WCNAON_UART_EN_BIT          ((uint32_t)0x00000001)
/// UART_EN field position
#define WCNAON_UART_EN_POS          0

/// UART_BUF_FULL field reset value
#define WCNAON_UART_BUF_FULL_RST    0x0
/// DIV_C field reset value
#define WCNAON_DIV_C_RST            0x7
/// DIV_B field reset value
#define WCNAON_DIV_B_RST            0x7
/// PARITY_EVEN field reset value
#define WCNAON_PARITY_EVEN_RST      0x1
/// PARITY_EN field reset value
#define WCNAON_PARITY_EN_RST        0x1
/// UART_EN field reset value
#define WCNAON_UART_EN_RST          0x0

/**
 * @brief Constructs a value for the UART_CFG register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] divc - The value to use for the DIV_C field.
 * @param[in] divb - The value to use for the DIV_B field.
 * @param[in] parityeven - The value to use for the PARITY_EVEN field.
 * @param[in] parityen - The value to use for the PARITY_EN field.
 * @param[in] uarten - The value to use for the UART_EN field.
 */
__INLINE void wcnaon_uart_cfg_pack(uint8_t divc, uint8_t divb, uint8_t parityeven, uint8_t parityen, uint8_t uarten)
{
    REG_PL_WR(WCNAON_UART_CFG_ADDR,  ((uint32_t)divc << 8) | ((uint32_t)divb << 4) | ((uint32_t)parityeven << 2) | ((uint32_t)parityen << 1) | ((uint32_t)uarten << 0));
}

/**
 * @brief Unpacks UART_CFG's fields from current value of the UART_CFG register.
 *
 * Reads the UART_CFG register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] uartbuffull - Will be populated with the current value of this field from the register.
 * @param[out] divc - Will be populated with the current value of this field from the register.
 * @param[out] divb - Will be populated with the current value of this field from the register.
 * @param[out] parityeven - Will be populated with the current value of this field from the register.
 * @param[out] parityen - Will be populated with the current value of this field from the register.
 * @param[out] uarten - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_uart_cfg_unpack(uint8_t* uartbuffull, uint8_t* divc, uint8_t* divb, uint8_t* parityeven, uint8_t* parityen, uint8_t* uarten)
{
    uint32_t localVal = REG_PL_RD(WCNAON_UART_CFG_ADDR);

    *uartbuffull = (localVal & ((uint32_t)0x00001000)) >> 12;
    *divc = (localVal & ((uint32_t)0x00000F00)) >> 8;
    *divb = (localVal & ((uint32_t)0x000000F0)) >> 4;
    *parityeven = (localVal & ((uint32_t)0x00000004)) >> 2;
    *parityen = (localVal & ((uint32_t)0x00000002)) >> 1;
    *uarten = (localVal & ((uint32_t)0x00000001)) >> 0;
}

/**
 * @brief Returns the current value of the UART_BUF_FULL field in the UART_CFG register.
 *
 * The UART_CFG register will be read and the UART_BUF_FULL field's value will be returned.
 *
 * @return The current value of the UART_BUF_FULL field in the UART_CFG register.
 */
__INLINE uint8_t wcnaon_uart_buf_full_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_UART_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

/**
 * @brief Returns the current value of the DIV_C field in the UART_CFG register.
 *
 * The UART_CFG register will be read and the DIV_C field's value will be returned.
 *
 * @return The current value of the DIV_C field in the UART_CFG register.
 */
__INLINE uint8_t wcnaon_div_c_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_UART_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000F00)) >> 8);
}

/**
 * @brief Sets the DIV_C field of the UART_CFG register.
 *
 * The UART_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] divc - The value to set the field to.
 */
__INLINE void wcnaon_div_c_setf(uint8_t divc)
{
    REG_PL_WR(WCNAON_UART_CFG_ADDR, (REG_PL_RD(WCNAON_UART_CFG_ADDR) & ~((uint32_t)0x00000F00)) | (((uint32_t)divc << 8) & ((uint32_t)0x00000F00)));
}

/**
 * @brief Returns the current value of the DIV_B field in the UART_CFG register.
 *
 * The UART_CFG register will be read and the DIV_B field's value will be returned.
 *
 * @return The current value of the DIV_B field in the UART_CFG register.
 */
__INLINE uint8_t wcnaon_div_b_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_UART_CFG_ADDR);
    return ((localVal & ((uint32_t)0x000000F0)) >> 4);
}

/**
 * @brief Sets the DIV_B field of the UART_CFG register.
 *
 * The UART_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] divb - The value to set the field to.
 */
__INLINE void wcnaon_div_b_setf(uint8_t divb)
{
    REG_PL_WR(WCNAON_UART_CFG_ADDR, (REG_PL_RD(WCNAON_UART_CFG_ADDR) & ~((uint32_t)0x000000F0)) | (((uint32_t)divb << 4) & ((uint32_t)0x000000F0)));
}

/**
 * @brief Returns the current value of the PARITY_EVEN field in the UART_CFG register.
 *
 * The UART_CFG register will be read and the PARITY_EVEN field's value will be returned.
 *
 * @return The current value of the PARITY_EVEN field in the UART_CFG register.
 */
__INLINE uint8_t wcnaon_parity_even_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_UART_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

/**
 * @brief Sets the PARITY_EVEN field of the UART_CFG register.
 *
 * The UART_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] parityeven - The value to set the field to.
 */
__INLINE void wcnaon_parity_even_setf(uint8_t parityeven)
{
    REG_PL_WR(WCNAON_UART_CFG_ADDR, (REG_PL_RD(WCNAON_UART_CFG_ADDR) & ~((uint32_t)0x00000004)) | (((uint32_t)parityeven << 2) & ((uint32_t)0x00000004)));
}

/**
 * @brief Returns the current value of the PARITY_EN field in the UART_CFG register.
 *
 * The UART_CFG register will be read and the PARITY_EN field's value will be returned.
 *
 * @return The current value of the PARITY_EN field in the UART_CFG register.
 */
__INLINE uint8_t wcnaon_parity_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_UART_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

/**
 * @brief Sets the PARITY_EN field of the UART_CFG register.
 *
 * The UART_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] parityen - The value to set the field to.
 */
__INLINE void wcnaon_parity_en_setf(uint8_t parityen)
{
    REG_PL_WR(WCNAON_UART_CFG_ADDR, (REG_PL_RD(WCNAON_UART_CFG_ADDR) & ~((uint32_t)0x00000002)) | (((uint32_t)parityen << 1) & ((uint32_t)0x00000002)));
}

/**
 * @brief Returns the current value of the UART_EN field in the UART_CFG register.
 *
 * The UART_CFG register will be read and the UART_EN field's value will be returned.
 *
 * @return The current value of the UART_EN field in the UART_CFG register.
 */
__INLINE uint8_t wcnaon_uart_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_UART_CFG_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief Sets the UART_EN field of the UART_CFG register.
 *
 * The UART_CFG register will be read, modified to contain the new field value, and written.
 *
 * @param[in] uarten - The value to set the field to.
 */
__INLINE void wcnaon_uart_en_setf(uint8_t uarten)
{
    REG_PL_WR(WCNAON_UART_CFG_ADDR, (REG_PL_RD(WCNAON_UART_CFG_ADDR) & ~((uint32_t)0x00000001)) | (((uint32_t)uarten << 0) & ((uint32_t)0x00000001)));
}

/// @}

/**
 * @name UART_DATA register definitions
 * <table>
 * <caption id="UART_DATA_BF">UART_DATA bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>07:00 <td>         UART_DATA <td>R <td>R/W <td>0x70
 * </table>
 *
 * @{
 */

/// Address of the UART_DATA register
#define WCNAON_UART_DATA_ADDR   0x40580044
/// Offset of the UART_DATA register from the base address
#define WCNAON_UART_DATA_OFFSET 0x00000044
/// Index of the UART_DATA register
#define WCNAON_UART_DATA_INDEX  0x00000011
/// Reset value of the UART_DATA register
#define WCNAON_UART_DATA_RESET  0x00000070

/**
 * @brief Returns the current value of the UART_DATA register.
 * The UART_DATA register will be read and its value returned.
 * @return The current value of the UART_DATA register.
 */
__INLINE uint32_t wcnaon_uart_data_get(void)
{
    return REG_PL_RD(WCNAON_UART_DATA_ADDR);
}

/**
 * @brief Sets the UART_DATA register to a value.
 * The UART_DATA register will be written.
 * @param value - The value to write.
 */
__INLINE void wcnaon_uart_data_set(uint32_t value)
{
    REG_PL_WR(WCNAON_UART_DATA_ADDR, value);
}

// field definitions
/// UART_DATA field mask
#define WCNAON_UART_DATA_MASK   ((uint32_t)0x000000FF)
/// UART_DATA field LSB position
#define WCNAON_UART_DATA_LSB    0
/// UART_DATA field width
#define WCNAON_UART_DATA_WIDTH  ((uint32_t)0x00000008)

/// UART_DATA field reset value
#define WCNAON_UART_DATA_RST    0x70

/**
 * @brief Returns the current value of the UART_DATA field in the UART_DATA register.
 *
 * The UART_DATA register will be read and the UART_DATA field's value will be returned.
 *
 * @return The current value of the UART_DATA field in the UART_DATA register.
 */
__INLINE uint8_t wcnaon_uart_data_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_UART_DATA_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the UART_DATA field of the UART_DATA register.
 *
 * The UART_DATA register will be read, modified to contain the new field value, and written.
 *
 * @param[in] uartdata - The value to set the field to.
 */
__INLINE void wcnaon_uart_data_setf(uint8_t uartdata)
{
    REG_PL_WR(WCNAON_UART_DATA_ADDR, ((uint32_t)uartdata << 0) & ((uint32_t)0x000000FF));
}

/// @}

/**
 * @name DEEPSLEEP_WAKEUP_IND register definitions
 * <table>
 * <caption id="DEEPSLEEP_WAKEUP_IND_BF">DEEPSLEEP_WAKEUP_IND bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td>31:04 <td>           wf_rsvd <td>R <td>R/W <td>0x0
 * <tr><td>03:00 <td>deepsleep_wakeup_ind <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the DEEPSLEEP_WAKEUP_IND register
#define WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR   0x40580048
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
/// WF_RSVD field mask
#define WCNAON_WF_RSVD_MASK                ((uint32_t)0xFFFFFFF0)
/// WF_RSVD field LSB position
#define WCNAON_WF_RSVD_LSB                 4
/// WF_RSVD field width
#define WCNAON_WF_RSVD_WIDTH               ((uint32_t)0x0000001C)
/// DEEPSLEEP_WAKEUP_IND field mask
#define WCNAON_DEEPSLEEP_WAKEUP_IND_MASK   ((uint32_t)0x0000000F)
/// DEEPSLEEP_WAKEUP_IND field LSB position
#define WCNAON_DEEPSLEEP_WAKEUP_IND_LSB    0
/// DEEPSLEEP_WAKEUP_IND field width
#define WCNAON_DEEPSLEEP_WAKEUP_IND_WIDTH  ((uint32_t)0x00000004)

/// WF_RSVD field reset value
#define WCNAON_WF_RSVD_RST                 0x0
/// DEEPSLEEP_WAKEUP_IND field reset value
#define WCNAON_DEEPSLEEP_WAKEUP_IND_RST    0x0

/**
 * @brief Constructs a value for the DEEPSLEEP_WAKEUP_IND register given values for its fields
 * and writes the value to the register.
 *
 * @param[in] wfrsvd - The value to use for the wf_rsvd field.
 * @param[in] deepsleepwakeupind - The value to use for the deepsleep_wakeup_ind field.
 */
__INLINE void wcnaon_deepsleep_wakeup_ind_pack(uint32_t wfrsvd, uint8_t deepsleepwakeupind)
{
    REG_PL_WR(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR,  ((uint32_t)wfrsvd << 4) | ((uint32_t)deepsleepwakeupind << 0));
}

/**
 * @brief Unpacks DEEPSLEEP_WAKEUP_IND's fields from current value of the DEEPSLEEP_WAKEUP_IND register.
 *
 * Reads the DEEPSLEEP_WAKEUP_IND register and populates all the _field variables with the corresponding
 * values from the register.
 *
 * @param[out] wfrsvd - Will be populated with the current value of this field from the register.
 * @param[out] deepsleepwakeupind - Will be populated with the current value of this field from the register.
 */
__INLINE void wcnaon_deepsleep_wakeup_ind_unpack(uint32_t* wfrsvd, uint8_t* deepsleepwakeupind)
{
    uint32_t localVal = REG_PL_RD(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR);

    *wfrsvd = (localVal & ((uint32_t)0xFFFFFFF0)) >> 4;
    *deepsleepwakeupind = (localVal & ((uint32_t)0x0000000F)) >> 0;
}

/**
 * @brief Returns the current value of the wf_rsvd field in the DEEPSLEEP_WAKEUP_IND register.
 *
 * The DEEPSLEEP_WAKEUP_IND register will be read and the wf_rsvd field's value will be returned.
 *
 * @return The current value of the wf_rsvd field in the DEEPSLEEP_WAKEUP_IND register.
 */
__INLINE uint32_t wcnaon_wf_rsvd_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR);
    return ((localVal & ((uint32_t)0xFFFFFFF0)) >> 4);
}

/**
 * @brief Sets the wf_rsvd field of the DEEPSLEEP_WAKEUP_IND register.
 *
 * The DEEPSLEEP_WAKEUP_IND register will be read, modified to contain the new field value, and written.
 *
 * @param[in] wfrsvd - The value to set the field to.
 */
__INLINE void wcnaon_wf_rsvd_setf(uint32_t wfrsvd)
{
    REG_PL_WR(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR, (REG_PL_RD(WCNAON_DEEPSLEEP_WAKEUP_IND_ADDR) & ~((uint32_t)0xFFFFFFF0)) | (((uint32_t)wfrsvd << 4) & ((uint32_t)0xFFFFFFF0)));
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
 * <tr><td>31:00 <td>           bt_rsvd <td>R <td>R/W <td>0x0
 * </table>
 *
 * @{
 */

/// Address of the BT_RESERVED register
#define WCNAON_BT_RESERVED_ADDR   0x4058004C
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
/// BT_RSVD field mask
#define WCNAON_BT_RSVD_MASK   ((uint32_t)0xFFFFFFFF)
/// BT_RSVD field LSB position
#define WCNAON_BT_RSVD_LSB    0
/// BT_RSVD field width
#define WCNAON_BT_RSVD_WIDTH  ((uint32_t)0x00000020)

/// BT_RSVD field reset value
#define WCNAON_BT_RSVD_RST    0x0

/**
 * @brief Returns the current value of the bt_rsvd field in the BT_RESERVED register.
 *
 * The BT_RESERVED register will be read and the bt_rsvd field's value will be returned.
 *
 * @return The current value of the bt_rsvd field in the BT_RESERVED register.
 */
__INLINE uint32_t wcnaon_bt_rsvd_getf(void)
{
    uint32_t localVal = REG_PL_RD(WCNAON_BT_RESERVED_ADDR);
    return (localVal >> 0);
}

/**
 * @brief Sets the bt_rsvd field of the BT_RESERVED register.
 *
 * The BT_RESERVED register will be read, modified to contain the new field value, and written.
 *
 * @param[in] btrsvd - The value to set the field to.
 */
__INLINE void wcnaon_bt_rsvd_setf(uint32_t btrsvd)
{
    REG_PL_WR(WCNAON_BT_RESERVED_ADDR, ((uint32_t)btrsvd << 0) & ((uint32_t)0xFFFFFFFF));
}

/// @}


#endif // _REG_WCNAON_H_

/// @}

