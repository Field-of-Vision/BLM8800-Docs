#ifndef _REG_UART1_H_
#define _REG_UART1_H_

#include <stdint.h>
#include "compiler.h"
#include "arch.h"
#include "dbg_assert.h"
#include "reg_access.h"

#define REG_UART1_BASE_ADDR     AIC_UART1_BASE
/// UART index
#define UART1_INDEX             1

/**
 * @brief TXRXD register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  31:08                 RSVD   0x0
 *  07:00             TXRXDATA   0x0
 * </pre>
 */
#define UART1_TXRXD_ADDR   (REG_UART1_BASE_ADDR + 0x0000)
#define UART1_TXRXD_OFFSET 0x00000000
#define UART1_TXRXD_INDEX  0x00000000
#define UART1_TXRXD_RESET  0x00000000

__INLINE uint32_t uart1_txrxd_get(void)
{
    return REG_PL_RD(UART1_TXRXD_ADDR);
}

__INLINE void uart1_txrxd_set(uint32_t value)
{
    REG_PL_WR(UART1_TXRXD_ADDR, value);
}

// field definitions
#define UART1_RXDATA_MASK    ((uint32_t)0x000000FF)
#define UART1_RXDATA_LSB     0
#define UART1_RXDATA_WIDTH   ((uint32_t)0x00000008)
#define UART1_TXDATA_MASK    ((uint32_t)0x000000FF)
#define UART1_TXDATA_LSB     0
#define UART1_TXDATA_WIDTH   ((uint32_t)0x00000008)

#define UART1_RXDATA_RST     0x0
#define UART1_TXDATA_RST     0x0

__INLINE uint8_t uart1_rxdata_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_TXRXD_ADDR);
    return ((localVal & ((uint32_t)0x000000FF)) >> 0);
}

__INLINE void uart1_txdata_setf(uint8_t txdata)
{
    REG_PL_WR(UART1_TXRXD_ADDR, (uint32_t)txdata << 0);
}

/**
 * @brief DIV0 register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  31:08                 RSVD   0x0
 *  07:00                 DIV0   0x0
 * </pre>
 */
#define UART1_DIV0_ADDR   (REG_UART1_BASE_ADDR + 0x0000)
#define UART1_DIV0_OFFSET 0x00000000
#define UART1_DIV0_INDEX  0x00000000
#define UART1_DIV0_RESET  0x00000000

__INLINE uint32_t uart1_div0_get(void)
{
    return REG_PL_RD(UART1_DIV0_ADDR);
}

__INLINE void uart1_div0_set(uint32_t value)
{
    REG_PL_WR(UART1_DIV0_ADDR, value);
}

// field definitions
#define UART1_DIV0_MASK   ((uint32_t)0x000000FF)
#define UART1_DIV0_LSB    0
#define UART1_DIV0_WIDTH  ((uint32_t)0x00000008)

#define UART1_DIV0_RST    0x0

__INLINE uint8_t uart1_div0_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DIV0_ADDR);
    return (localVal >> 0);
}

__INLINE void uart1_div0_setf(uint8_t div0)
{
    REG_PL_WR(UART1_DIV0_ADDR, (uint32_t)div0 << 0);
}

/**
 * @brief IRQCTL register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     07              PTIRQEN   0
 *     05              TOIRQEN   0
 *     03              MSIRQEN   0
 *     02              LSIRQEN   0
 *     01              TXIRQEN   0
 *     00              RXIRQEN   0
 * </pre>
 */
#define UART1_IRQCTL_ADDR   (REG_UART1_BASE_ADDR + 0x0004)
#define UART1_IRQCTL_OFFSET 0x00000004
#define UART1_IRQCTL_INDEX  0x00000001
#define UART1_IRQCTL_RESET  0x00000000

__INLINE uint32_t uart1_irqctl_get(void)
{
    return REG_PL_RD(UART1_IRQCTL_ADDR);
}

__INLINE void uart1_irqctl_set(uint32_t value)
{
    REG_PL_WR(UART1_IRQCTL_ADDR, value);
}

// field definitions
#define UART1_PTIRQEN_BIT  ((uint32_t)0x00000080)
#define UART1_PTIRQEN_POS  7
#define UART1_TOIRQEN_BIT  ((uint32_t)0x00000020)
#define UART1_TOIRQEN_POS  5
#define UART1_MSIRQEN_BIT  ((uint32_t)0x00000008)
#define UART1_MSIRQEN_POS  3
#define UART1_LSIRQEN_BIT  ((uint32_t)0x00000004)
#define UART1_LSIRQEN_POS  2
#define UART1_TXIRQEN_BIT  ((uint32_t)0x00000002)
#define UART1_TXIRQEN_POS  1
#define UART1_RXIRQEN_BIT  ((uint32_t)0x00000001)
#define UART1_RXIRQEN_POS  0

#define UART1_PTIRQEN_RST  0x0
#define UART1_TOIRQEN_RST  0x0
#define UART1_MSIRQEN_RST  0x0
#define UART1_LSIRQEN_RST  0x0
#define UART1_TXIRQEN_RST  0x0
#define UART1_RXIRQEN_RST  0x0

__INLINE void uart1_irqctl_pack(uint8_t ptirqen, uint8_t toirqen, uint8_t msirqen, uint8_t lsirqen, uint8_t txirqen, uint8_t rxirqen)
{
    REG_PL_WR(UART1_IRQCTL_ADDR,  ((uint32_t)ptirqen << 7) | ((uint32_t)toirqen << 5) | ((uint32_t)msirqen << 3) | ((uint32_t)lsirqen << 2) | ((uint32_t)txirqen << 1) | ((uint32_t)rxirqen << 0));
}

__INLINE void uart1_irqctl_unpack(uint8_t* ptirqen, uint8_t *toirqen, uint8_t* msirqen, uint8_t* lsirqen, uint8_t* txirqen, uint8_t* rxirqen)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQCTL_ADDR);

    *ptirqen = (localVal & ((uint32_t)0x00000080)) >> 7;
    *toirqen = (localVal & ((uint32_t)0x00000020)) >> 5;
    *msirqen = (localVal & ((uint32_t)0x00000008)) >> 3;
    *lsirqen = (localVal & ((uint32_t)0x00000004)) >> 2;
    *txirqen = (localVal & ((uint32_t)0x00000002)) >> 1;
    *rxirqen = (localVal & ((uint32_t)0x00000001)) >> 0;
}

__INLINE uint8_t uart1_ptirqen_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQCTL_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

__INLINE void uart1_ptirqen_setf(uint8_t ptirqen)
{
    REG_PL_WR(UART1_IRQCTL_ADDR, (REG_PL_RD(UART1_IRQCTL_ADDR) & ~((uint32_t)0x00000080)) | ((uint32_t)ptirqen << 7));
}

__INLINE uint8_t uart1_toirqen_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQCTL_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

__INLINE void uart1_toirqen_setf(uint8_t toirqen)
{
    REG_PL_WR(UART1_IRQCTL_ADDR, (REG_PL_RD(UART1_IRQCTL_ADDR) & ~((uint32_t)0x00000020)) | ((uint32_t)toirqen << 5));
}

__INLINE uint8_t uart1_msirqen_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQCTL_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

__INLINE void uart1_msirqen_setf(uint8_t msirqen)
{
    REG_PL_WR(UART1_IRQCTL_ADDR, (REG_PL_RD(UART1_IRQCTL_ADDR) & ~((uint32_t)0x00000008)) | ((uint32_t)msirqen << 3));
}

__INLINE uint8_t uart1_lsirqen_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQCTL_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

__INLINE void uart1_lsirqen_setf(uint8_t lsirqen)
{
    REG_PL_WR(UART1_IRQCTL_ADDR, (REG_PL_RD(UART1_IRQCTL_ADDR) & ~((uint32_t)0x00000004)) | ((uint32_t)lsirqen << 2));
}

__INLINE uint8_t uart1_txirqen_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQCTL_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

__INLINE void uart1_txirqen_setf(uint8_t txirqen)
{
    REG_PL_WR(UART1_IRQCTL_ADDR, (REG_PL_RD(UART1_IRQCTL_ADDR) & ~((uint32_t)0x00000002)) | ((uint32_t)txirqen << 1));
}

__INLINE uint8_t uart1_rxirqen_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQCTL_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

__INLINE void uart1_rxirqen_setf(uint8_t rxirqen)
{
    REG_PL_WR(UART1_IRQCTL_ADDR, (REG_PL_RD(UART1_IRQCTL_ADDR) & ~((uint32_t)0x00000001)) | ((uint32_t)rxirqen << 0));
}

/**
 * @brief DIV1 register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  31:08                 RSVD   0x0
 *  07:00                 DIV1   0x0
 * </pre>
 */
#define UART1_DIV1_ADDR   (REG_UART1_BASE_ADDR + 0x0004)
#define UART1_DIV1_OFFSET 0x00000004
#define UART1_DIV1_INDEX  0x00000001
#define UART1_DIV1_RESET  0x00000000

__INLINE uint32_t uart1_div1_get(void)
{
    return REG_PL_RD(UART1_DIV1_ADDR);
}

__INLINE void uart1_div1_set(uint32_t value)
{
    REG_PL_WR(UART1_DIV1_ADDR, value);
}

// field definitions
#define UART1_DIV1_MASK   ((uint32_t)0x000000FF)
#define UART1_DIV1_LSB    0
#define UART1_DIV1_WIDTH  ((uint32_t)0x00000008)

#define UART1_DIV1_RST    0x0

__INLINE uint8_t uart1_div1_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DIV1_ADDR);
    return (localVal >> 0);
}

__INLINE void uart1_div1_setf(uint8_t div1)
{
    REG_PL_WR(UART1_DIV1_ADDR, (uint32_t)div1 << 0);
}

/**
 * @brief IRQTYP register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  03:00               IRQTYP   0x1
 * </pre>
 */
#define UART1_IRQTYP_ADDR   (REG_UART1_BASE_ADDR + 0x0008)
#define UART1_IRQTYP_OFFSET 0x00000008
#define UART1_IRQTYP_INDEX  0x00000002
#define UART1_IRQTYP_RESET  0x00000061

__INLINE uint32_t uart1_irqtyp_get(void)
{
    return REG_PL_RD(UART1_IRQTYP_ADDR);
}

// field definitions
#define UART1_IRQTYP_MASK     ((uint32_t)0x0000000F)
#define UART1_IRQTYP_LSB      0
#define UART1_IRQTYP_WIDTH    ((uint32_t)0x00000004)

#define UART1_IRQTYP_RST      0x1

__INLINE uint8_t uart1_irqtyp_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQTYP_ADDR);
    return ((localVal & ((uint32_t)0x0000000F)) >> 0);
}

/**
 * @brief DBUFCFG register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     02               TXDRST   0
 *     01               RXDRST   0
 *     00               DBUFEN   0
 * </pre>
 */
#define UART1_DBUFCFG_ADDR   (REG_UART1_BASE_ADDR + 0x0008)
#define UART1_DBUFCFG_OFFSET 0x00000008
#define UART1_DBUFCFG_INDEX  0x00000002
#define UART1_DBUFCFG_RESET  0x00000000

__INLINE void uart1_dbufcfg_set(uint32_t value)
{
    REG_PL_WR(UART1_DBUFCFG_ADDR, value);
}

// field definitions
#define UART1_DMAMOD_BIT   ((uint32_t)0x00000008)
#define UART1_DMAMOD_POS   3
#define UART1_TXDRST_BIT   ((uint32_t)0x00000004)
#define UART1_TXDRST_POS   2
#define UART1_RXDRST_BIT   ((uint32_t)0x00000002)
#define UART1_RXDRST_POS   1
#define UART1_DBUFEN_BIT   ((uint32_t)0x00000001)
#define UART1_DBUFEN_POS   0

#define UART1_DMAMOD_RST   0x0
#define UART1_TXDRST_RST   0x0
#define UART1_RXDRST_RST   0x0
#define UART1_DBUFEN_RST   0x0

__INLINE void uart1_dbufcfg_pack(uint8_t dmamod, uint8_t txdrst, uint8_t rxdrst, uint8_t dbufen)
{
    REG_PL_WR(UART1_DBUFCFG_ADDR, ((uint32_t)dmamod << 3) | ((uint32_t)txdrst << 2) | ((uint32_t)rxdrst << 1) | ((uint32_t)dbufen << 0));
}

__INLINE void uart1_dmamod_setf(uint8_t dmamod)
{
    REG_PL_WR(UART1_DBUFCFG_ADDR, (REG_PL_RD(UART1_DBUFCFG_ADDR) & ~((uint32_t)0x00000008)) | ((uint32_t)dmamod << 3));
}

__INLINE void uart1_txdrst_setf(uint8_t txdrst)
{
    REG_PL_WR(UART1_DBUFCFG_ADDR, (REG_PL_RD(UART1_DBUFCFG_ADDR) & ~((uint32_t)0x00000004)) | ((uint32_t)txdrst << 2));
}

__INLINE void uart1_rxdrst_setf(uint8_t rxdrst)
{
    REG_PL_WR(UART1_DBUFCFG_ADDR, (REG_PL_RD(UART1_DBUFCFG_ADDR) & ~((uint32_t)0x00000002)) | ((uint32_t)rxdrst << 1));
}

__INLINE void uart1_dbufen_setf(uint8_t dbufen)
{
    REG_PL_WR(UART1_DBUFCFG_ADDR, (REG_PL_RD(UART1_DBUFCFG_ADDR) & ~((uint32_t)0x00000001)) | ((uint32_t)dbufen << 0));
}

/**
 * @brief DFMTCFG register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     08                DIVMS   0
 *     07                DIVAE   0
 *     06                  BRK   0
 *     04                  EPS   0
 *     03                  PEN   0
 *     02                 STOP   0
 *  01:00                  DLS   0x3
 * </pre>
 */
#define UART1_DFMTCFG_ADDR   (REG_UART1_BASE_ADDR + 0x000C)
#define UART1_DFMTCFG_OFFSET 0x0000000C
#define UART1_DFMTCFG_INDEX  0x00000003
#define UART1_DFMTCFG_RESET  0x00000003

__INLINE uint32_t uart1_dfmtcfg_get(void)
{
    return REG_PL_RD(UART1_DFMTCFG_ADDR);
}

__INLINE void uart1_dfmtcfg_set(uint32_t value)
{
    REG_PL_WR(UART1_DFMTCFG_ADDR, value);
}

// field definitions
#define UART1_DIVMS_BIT       ((uint32_t)0x00000100)
#define UART1_DIVMS_POS       8
#define UART1_DIVAE_BIT       ((uint32_t)0x00000080)
#define UART1_DIVAE_POS       7
#define UART1_BRK_BIT         ((uint32_t)0x00000040)
#define UART1_BRK_POS         6
#define UART1_EPS_BIT         ((uint32_t)0x00000010)
#define UART1_EPS_POS         4
#define UART1_PEN_BIT         ((uint32_t)0x00000008)
#define UART1_PEN_POS         3
#define UART1_STOP_BIT        ((uint32_t)0x00000004)
#define UART1_STOP_POS        2
#define UART1_DLS_MASK        ((uint32_t)0x00000003)
#define UART1_DLS_LSB         0
#define UART1_DLS_WIDTH       ((uint32_t)0x00000002)

#define UART1_DIVMS_RST       0x0
#define UART1_DIVAE_RST       0x0
#define UART1_BRK_RST         0x0
#define UART1_EPS_RST         0x0
#define UART1_PEN_RST         0x0
#define UART1_STOP_RST        0x0
#define UART1_DLS_RST         0x3

__INLINE void uart1_dfmtcfg_pack(uint8_t divms, uint8_t divae, uint8_t brk, uint8_t eps, uint8_t pen, uint8_t stop, uint8_t dls)
{
    ASSERT_ERR((((uint32_t)divms << 8) & ~((uint32_t)0x00000100)) == 0);
    ASSERT_ERR((((uint32_t)divae << 7) & ~((uint32_t)0x00000080)) == 0);
    ASSERT_ERR((((uint32_t)brk << 6) & ~((uint32_t)0x00000040)) == 0);
    ASSERT_ERR((((uint32_t)eps << 4) & ~((uint32_t)0x00000010)) == 0);
    ASSERT_ERR((((uint32_t)pen << 3) & ~((uint32_t)0x00000008)) == 0);
    ASSERT_ERR((((uint32_t)stop << 2) & ~((uint32_t)0x00000004)) == 0);
    ASSERT_ERR((((uint32_t)dls << 0) & ~((uint32_t)0x00000003)) == 0);
    REG_PL_WR(UART1_DFMTCFG_ADDR,  ((uint32_t)divms << 8) | ((uint32_t)divae << 7) | ((uint32_t)brk << 6) | ((uint32_t)eps << 4) | ((uint32_t)pen << 3) | ((uint32_t)stop << 2) | ((uint32_t)dls << 0));
}

__INLINE void uart1_dfmtcfg_unpack(uint8_t* divms, uint8_t* divae, uint8_t* brk, uint8_t* eps, uint8_t* pen, uint8_t* stop, uint8_t* dls)
{
    uint32_t localVal = REG_PL_RD(UART1_DFMTCFG_ADDR);

    *divms = (localVal & ((uint32_t)0x00000100)) >> 8;
    *divae = (localVal & ((uint32_t)0x00000080)) >> 7;
    *brk = (localVal & ((uint32_t)0x00000040)) >> 6;
    *eps = (localVal & ((uint32_t)0x00000010)) >> 4;
    *pen = (localVal & ((uint32_t)0x00000008)) >> 3;
    *stop = (localVal & ((uint32_t)0x00000004)) >> 2;
    *dls = (localVal & ((uint32_t)0x00000003)) >> 0;
}

__INLINE uint8_t uart1_divms_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DFMTCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

__INLINE void uart1_divms_setf(uint8_t divmode)
{
    ASSERT_ERR((((uint32_t)divmode << 8) & ~((uint32_t)0x00000100)) == 0);
    REG_PL_WR(UART1_DFMTCFG_ADDR, (REG_PL_RD(UART1_DFMTCFG_ADDR) & ~((uint32_t)0x00000100)) | ((uint32_t)divmode << 8));
}

__INLINE uint8_t uart1_divae_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DFMTCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

__INLINE void uart1_divae_setf(uint8_t DIVAE)
{
    ASSERT_ERR((((uint32_t)DIVAE << 7) & ~((uint32_t)0x00000080)) == 0);
    REG_PL_WR(UART1_DFMTCFG_ADDR, (REG_PL_RD(UART1_DFMTCFG_ADDR) & ~((uint32_t)0x00000080)) | ((uint32_t)DIVAE << 7));
}

__INLINE uint8_t uart1_brk_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DFMTCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

__INLINE void uart1_brk_setf(uint8_t brk)
{
    ASSERT_ERR((((uint32_t)brk << 6) & ~((uint32_t)0x00000040)) == 0);
    REG_PL_WR(UART1_DFMTCFG_ADDR, (REG_PL_RD(UART1_DFMTCFG_ADDR) & ~((uint32_t)0x00000040)) | ((uint32_t)brk << 6));
}

__INLINE uint8_t uart1_eps_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DFMTCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

__INLINE void uart1_eps_setf(uint8_t eps)
{
    ASSERT_ERR((((uint32_t)eps << 4) & ~((uint32_t)0x00000010)) == 0);
    REG_PL_WR(UART1_DFMTCFG_ADDR, (REG_PL_RD(UART1_DFMTCFG_ADDR) & ~((uint32_t)0x00000010)) | ((uint32_t)eps << 4));
}

__INLINE uint8_t uart1_pen_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DFMTCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

__INLINE void uart1_pen_setf(uint8_t pen)
{
    ASSERT_ERR((((uint32_t)pen << 3) & ~((uint32_t)0x00000008)) == 0);
    REG_PL_WR(UART1_DFMTCFG_ADDR, (REG_PL_RD(UART1_DFMTCFG_ADDR) & ~((uint32_t)0x00000008)) | ((uint32_t)pen << 3));
}

__INLINE uint8_t uart1_stop_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DFMTCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

__INLINE void uart1_stop_setf(uint8_t stop)
{
    ASSERT_ERR((((uint32_t)stop << 2) & ~((uint32_t)0x00000004)) == 0);
    REG_PL_WR(UART1_DFMTCFG_ADDR, (REG_PL_RD(UART1_DFMTCFG_ADDR) & ~((uint32_t)0x00000004)) | ((uint32_t)stop << 2));
}

__INLINE uint8_t uart1_dls_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DFMTCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

__INLINE void uart1_dls_setf(uint8_t dls)
{
    ASSERT_ERR((((uint32_t)dls << 0) & ~((uint32_t)0x00000003)) == 0);
    REG_PL_WR(UART1_DFMTCFG_ADDR, (REG_PL_RD(UART1_DFMTCFG_ADDR) & ~((uint32_t)0x00000003)) | ((uint32_t)dls << 0));
}

/**
 * @brief MDMCFG register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     08                CLK_P   0
 *     07             AUTO_DET   0
 *     06                 SIRE   0
 *     05                 AFCE   0
 *     04             LOOPBACK   0
 *     03                 OUT2   0
 *     02                 OUT1   0
 *     01                  RTS   0
 *     00                  DTR   0
 * </pre>
 */
#define UART1_MDMCFG_ADDR   (REG_UART1_BASE_ADDR + 0x0010)
#define UART1_MDMCFG_OFFSET 0x00000010
#define UART1_MDMCFG_INDEX  0x00000004
#define UART1_MDMCFG_RESET  0x00000000

__INLINE uint32_t uart1_mdmcfg_get(void)
{
    return REG_PL_RD(UART1_MDMCFG_ADDR);
}

__INLINE void uart1_mdmcfg_set(uint32_t value)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, value);
}

// field definitions
#define UART1_CLK_P_BIT       ((uint32_t)0x00000100)
#define UART1_CLK_P_POS       8
#define UART1_AUTO_DET_BIT    ((uint32_t)0x00000080)
#define UART1_AUTO_DET_POS    7
#define UART1_SIRE_BIT        ((uint32_t)0x00000040)
#define UART1_SIRE_POS        6
#define UART1_AFCE_BIT        ((uint32_t)0x00000020)
#define UART1_AFCE_POS        5
#define UART1_LOOPBACK_BIT    ((uint32_t)0x00000010)
#define UART1_LOOPBACK_POS    4
#define UART1_OUT2_BIT        ((uint32_t)0x00000008)
#define UART1_OUT2_POS        3
#define UART1_OUT1_BIT        ((uint32_t)0x00000004)
#define UART1_OUT1_POS        2
#define UART1_RTS_BIT         ((uint32_t)0x00000002)
#define UART1_RTS_POS         1
#define UART1_DTR_BIT         ((uint32_t)0x00000001)
#define UART1_DTR_POS         0

#define UART1_CLK_P_RST       0x0
#define UART1_AUTO_DET_RST    0x0
#define UART1_SIRE_RST        0x0
#define UART1_AFCE_RST        0x0
#define UART1_LOOPBACK_RST    0x0
#define UART1_OUT2_RST        0x0
#define UART1_OUT1_RST        0x0
#define UART1_RTS_RST         0x0
#define UART1_DTR_RST         0x0

__INLINE void uart1_mdmcfg_pack(uint8_t clkp, uint8_t autodet, uint8_t sire, uint8_t afce, uint8_t loopback, uint8_t out2, uint8_t out1, uint8_t rts, uint8_t dtr)
{
    REG_PL_WR(UART1_MDMCFG_ADDR,  ((uint32_t)clkp << 8) | ((uint32_t)autodet << 7) | ((uint32_t)sire << 6) | ((uint32_t)afce << 5) | ((uint32_t)loopback << 4) | ((uint32_t)out2 << 3) | ((uint32_t)out1 << 2) | ((uint32_t)rts << 1) | ((uint32_t)dtr << 0));
}

__INLINE void uart1_mdmcfg_unpack(uint8_t* clkp, uint8_t* autodet, uint8_t* sire, uint8_t* afce, uint8_t* loopback, uint8_t* out2, uint8_t* out1, uint8_t* rts, uint8_t* dtr)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);

    *clkp = (localVal & ((uint32_t)0x00000100)) >> 8;
    *autodet = (localVal & ((uint32_t)0x00000080)) >> 7;
    *sire = (localVal & ((uint32_t)0x00000040)) >> 6;
    *afce = (localVal & ((uint32_t)0x00000020)) >> 5;
    *loopback = (localVal & ((uint32_t)0x00000010)) >> 4;
    *out2 = (localVal & ((uint32_t)0x00000008)) >> 3;
    *out1 = (localVal & ((uint32_t)0x00000004)) >> 2;
    *rts = (localVal & ((uint32_t)0x00000002)) >> 1;
    *dtr = (localVal & ((uint32_t)0x00000001)) >> 0;
}

__INLINE uint8_t uart1_clk_p_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

__INLINE void uart1_clk_p_setf(uint8_t clkp)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, (REG_PL_RD(UART1_MDMCFG_ADDR) & ~((uint32_t)0x00000100)) | ((uint32_t)clkp << 8));
}

__INLINE uint8_t uart1_auto_det_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

__INLINE void uart1_auto_det_setf(uint8_t autodet)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, (REG_PL_RD(UART1_MDMCFG_ADDR) & ~((uint32_t)0x00000080)) | ((uint32_t)autodet << 7));
}

__INLINE uint8_t uart1_sire_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

__INLINE void uart1_sire_setf(uint8_t sire)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, (REG_PL_RD(UART1_MDMCFG_ADDR) & ~((uint32_t)0x00000040)) | ((uint32_t)sire << 6));
}

__INLINE uint8_t uart1_afce_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

__INLINE void uart1_afce_setf(uint8_t afce)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, (REG_PL_RD(UART1_MDMCFG_ADDR) & ~((uint32_t)0x00000020)) | ((uint32_t)afce << 5));
}

__INLINE uint8_t uart1_loopback_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

__INLINE void uart1_loopback_setf(uint8_t loopback)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, (REG_PL_RD(UART1_MDMCFG_ADDR) & ~((uint32_t)0x00000010)) | ((uint32_t)loopback << 4));
}

__INLINE uint8_t uart1_out2_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

__INLINE void uart1_out2_setf(uint8_t out2)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, (REG_PL_RD(UART1_MDMCFG_ADDR) & ~((uint32_t)0x00000008)) | ((uint32_t)out2 << 3));
}

__INLINE uint8_t uart1_out1_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

__INLINE void uart1_out1_setf(uint8_t out1)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, (REG_PL_RD(UART1_MDMCFG_ADDR) & ~((uint32_t)0x00000004)) | ((uint32_t)out1 << 2));
}

__INLINE uint8_t uart1_rts_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

__INLINE void uart1_rts_setf(uint8_t rts)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, (REG_PL_RD(UART1_MDMCFG_ADDR) & ~((uint32_t)0x00000002)) | ((uint32_t)rts << 1));
}

__INLINE uint8_t uart1_dtr_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_MDMCFG_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

__INLINE void uart1_dtr_setf(uint8_t dtr)
{
    REG_PL_WR(UART1_MDMCFG_ADDR, (REG_PL_RD(UART1_MDMCFG_ADDR) & ~((uint32_t)0x00000001)) | ((uint32_t)dtr << 0));
}

/**
 * @brief IRQSTS register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     08                 RTDR   0
 *     07                  RFE   0
 *     06                 TEMT   1
 *     05                 THRE   1
 *     01                   OE   0
 *     00                   DR   0
 * </pre>
 */
#define UART1_IRQSTS_ADDR   (REG_UART1_BASE_ADDR + 0x0014)
#define UART1_IRQSTS_OFFSET 0x00000014
#define UART1_IRQSTS_INDEX  0x00000005
#define UART1_IRQSTS_RESET  0x00000060

__INLINE uint32_t uart1_irqsts_get(void)
{
    return REG_PL_RD(UART1_IRQSTS_ADDR);
}

// field definitions
#define UART1_RTDR_BIT    ((uint32_t)0x00000100)
#define UART1_RTDR_POS    8
#define UART1_RFE_BIT     ((uint32_t)0x00000080)
#define UART1_RFE_POS     7
#define UART1_TEMT_BIT    ((uint32_t)0x00000040)
#define UART1_TEMT_POS    6
#define UART1_THRE_BIT    ((uint32_t)0x00000020)
#define UART1_THRE_POS    5
#define UART1_OE_BIT      ((uint32_t)0x00000002)
#define UART1_OE_POS      1
#define UART1_DR_BIT      ((uint32_t)0x00000001)
#define UART1_DR_POS      0

#define UART1_RTDR_RST    0x0
#define UART1_RFE_RST     0x0
#define UART1_TEMT_RST    0x1
#define UART1_THRE_RST    0x1
#define UART1_OE_RST      0x0
#define UART1_DR_RST      0x0

__INLINE void uart1_irqsts_unpack(uint8_t* rtdr, uint8_t* rfe, uint8_t* temt, uint8_t* thre, uint8_t* oe, uint8_t* dr)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQSTS_ADDR);

    *rtdr = (localVal & ((uint32_t)0x00000100)) >> 8;
    *rfe = (localVal & ((uint32_t)0x00000080)) >> 7;
    *temt = (localVal & ((uint32_t)0x00000040)) >> 6;
    *thre = (localVal & ((uint32_t)0x00000020)) >> 5;
    *oe = (localVal & ((uint32_t)0x00000002)) >> 1;
    *dr = (localVal & ((uint32_t)0x00000001)) >> 0;
}

__INLINE uint8_t uart1_rtdr_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQSTS_ADDR);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

__INLINE uint8_t uart1_rfe_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQSTS_ADDR);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

__INLINE uint8_t uart1_temt_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQSTS_ADDR);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

__INLINE uint8_t uart1_thre_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQSTS_ADDR);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

__INLINE uint8_t uart1_oe_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQSTS_ADDR);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

__INLINE uint8_t uart1_dr_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_IRQSTS_ADDR);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

/**
 * @brief MDMSTS register definition
 */
#define UART1_MDMSTS_ADDR   (REG_UART1_BASE_ADDR + 0x0018)
#define UART1_MDMSTS_OFFSET 0x00000018
#define UART1_MDMSTS_INDEX  0x00000006
#define UART1_MDMSTS_RESET  0x00000060

__INLINE uint32_t uart1_mdmsts_get(void)
{
    return REG_PL_RD(UART1_MDMSTS_ADDR);
}

/**
 * @brief DBUFSTS register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     21         RX_DBUF_FULL   0
 *     20        RX_DBUF_EMPTY   1
 *     19         TX_DBUF_FULL   0
 *     18        TX_DBUF_EMPTY   1
 *  16:09             RX_COUNT   0x0
 *  07:00             TX_COUNT   0x0
 * </pre>
 */
#define UART1_DBUFSTS_ADDR   (REG_UART1_BASE_ADDR + 0x0020)
#define UART1_DBUFSTS_OFFSET 0x00000020
#define UART1_DBUFSTS_INDEX  0x00000008
#define UART1_DBUFSTS_RESET  0x00140000

__INLINE uint32_t uart1_dbufsts_get(void)
{
    return REG_PL_RD(UART1_DBUFSTS_ADDR);
}

// field definitions
#define UART1_RX_DBUF_FULL_BIT     ((uint32_t)0x00200000)
#define UART1_RX_DBUF_FULL_POS     21
#define UART1_RX_DBUF_EMPTY_BIT    ((uint32_t)0x00100000)
#define UART1_RX_DBUF_EMPTY_POS    20
#define UART1_TX_DBUF_FULL_BIT     ((uint32_t)0x00080000)
#define UART1_TX_DBUF_FULL_POS     19
#define UART1_TX_DBUF_EMPTY_BIT    ((uint32_t)0x00040000)
#define UART1_TX_DBUF_EMPTY_POS    18
#define UART1_RX_COUNT_MASK        ((uint32_t)0x0001FE00)
#define UART1_RX_COUNT_LSB         9
#define UART1_RX_COUNT_WIDTH       ((uint32_t)0x00000008)
#define UART1_TX_COUNT_MASK        ((uint32_t)0x000000FF)
#define UART1_TX_COUNT_LSB         0
#define UART1_TX_COUNT_WIDTH       ((uint32_t)0x00000008)

#define UART1_RX_DBUF_FULL_RST     0x0
#define UART1_RX_DBUF_EMPTY_RST    0x1
#define UART1_TX_DBUF_FULL_RST     0x0
#define UART1_TX_DBUF_EMPTY_RST    0x1
#define UART1_RX_COUNT_RST         0x0
#define UART1_TX_COUNT_RST         0x0

__INLINE void uart1_dbufsts_unpack(uint8_t* rxdbuffull, uint8_t* rxdbufempty, uint8_t* txdbuffull, uint8_t* txdbufempty, uint16_t* rxcount, uint16_t* txcount)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFSTS_ADDR);

    *rxdbuffull = (localVal & ((uint32_t)0x00200000)) >> 21;
    *rxdbufempty = (localVal & ((uint32_t)0x00100000)) >> 20;
    *txdbuffull = (localVal & ((uint32_t)0x00080000)) >> 19;
    *txdbufempty = (localVal & ((uint32_t)0x00040000)) >> 18;
    *rxcount = (localVal & ((uint32_t)0x0001FE00)) >> 9;
    *txcount = (localVal & ((uint32_t)0x000000FF)) >> 0;
}

__INLINE uint8_t uart1_rx_dbuf_full_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFSTS_ADDR);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

__INLINE uint8_t uart1_rx_dbuf_empty_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFSTS_ADDR);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

__INLINE uint8_t uart1_tx_dbuf_full_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFSTS_ADDR);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

__INLINE uint8_t uart1_tx_dbuf_empty_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFSTS_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

__INLINE uint16_t uart1_rx_count_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFSTS_ADDR);
    return ((localVal & ((uint32_t)0x0001FE00)) >> 9);
}

__INLINE uint16_t uart1_tx_count_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFSTS_ADDR);
    return ((localVal & ((uint32_t)0x000000FF)) >> 0);
}

/**
 * @brief DBUFTH register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     18             RXTOTRIGEN 0
 *  16:09             TXTRIGTH   0x10
 *  07:00             RXTRIGTH   0x10
 * </pre>
 */
#define UART1_DBUFTH_ADDR   (REG_UART1_BASE_ADDR + 0x0024)
#define UART1_DBUFTH_OFFSET 0x00000024
#define UART1_DBUFTH_INDEX  0x00000009
#define UART1_DBUFTH_RESET  0x00000810

__INLINE uint32_t uart1_dbufth_get(void)
{
    return REG_PL_RD(UART1_DBUFTH_ADDR);
}

__INLINE void uart1_dbufth_set(uint32_t value)
{
    REG_PL_WR(UART1_DBUFTH_ADDR, value);
}

// field definitions
#define UART1_RXTOTRIGEN_BIT   ((uint32_t)0x00040000)
#define UART1_RXTOTRIGEN_POS   18
#define UART1_TXTRIGTH_MASK    ((uint32_t)0x0001FE00)
#define UART1_TXTRIGTH_LSB     9
#define UART1_TXTRIGTH_WIDTH   ((uint32_t)0x00000008)
#define UART1_RXTRIGTH_MASK    ((uint32_t)0x000000FF)
#define UART1_RXTRIGTH_LSB     0
#define UART1_RXTRIGTH_WIDTH   ((uint32_t)0x00000008)

#define UART1_RXTOTRIGEN_RST   0x0
#define UART1_TXTRIGTH_RST     0x10
#define UART1_RXTRIGTH_RST     0x10

__INLINE void uart1_dbufth_pack(uint8_t rxtotrigen, uint8_t txtrigth, uint8_t rxtrigth)
{
    REG_PL_WR(UART1_DBUFTH_ADDR,  ((uint32_t)rxtotrigen << 18) | ((uint32_t)txtrigth << 9) | ((uint32_t)rxtrigth << 0));
}

__INLINE void uart1_dbufth_unpack(uint8_t *rxtotrigen, uint8_t* txtrigth, uint8_t* rxtrigth)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFTH_ADDR);

    *rxtotrigen = (localVal & ((uint32_t)0x00040000)) >> 18;
    *txtrigth = (localVal & ((uint32_t)0x0001FE00)) >> 9;
    *rxtrigth = (localVal & ((uint32_t)0x000000FF)) >> 0;
}

__INLINE uint8_t uart1_rxtotrigen_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFTH_ADDR);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

__INLINE void uart1_rxtotrigen_setf(uint8_t txtrigth)
{
    REG_PL_WR(UART1_DBUFTH_ADDR, (REG_PL_RD(UART1_DBUFTH_ADDR) & ~((uint32_t)0x00040000)) | ((uint32_t)txtrigth << 18));
}

__INLINE uint8_t uart1_txtrigth_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFTH_ADDR);
    return ((localVal & ((uint32_t)0x0001FE00)) >> 9);
}

__INLINE void uart1_txtrigth_setf(uint8_t txtrigth)
{
    REG_PL_WR(UART1_DBUFTH_ADDR, (REG_PL_RD(UART1_DBUFTH_ADDR) & ~((uint32_t)0x0001FE00)) | ((uint32_t)txtrigth << 9));
}

__INLINE uint8_t uart1_rxtrigth_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DBUFTH_ADDR);
    return ((localVal & ((uint32_t)0x000000FF)) >> 0);
}

__INLINE void uart1_rxtrigth_setf(uint8_t rxtrigth)
{
    REG_PL_WR(UART1_DBUFTH_ADDR, (REG_PL_RD(UART1_DBUFTH_ADDR) & ~((uint32_t)0x000000FF)) | ((uint32_t)rxtrigth << 0));
}

/**
 * @brief DIV2 register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  31:08                 RSVD   0x0
 *  07:00                 DIV2   0x0
 * </pre>
 */
#define UART1_DIV2_ADDR   (REG_UART1_BASE_ADDR + 0x0028)
#define UART1_DIV2_OFFSET 0x00000028
#define UART1_DIV2_INDEX  0x0000000A
#define UART1_DIV2_RESET  0x00000000

__INLINE uint32_t uart1_div2_get(void)
{
    return REG_PL_RD(UART1_DIV2_ADDR);
}

__INLINE void uart1_div2_set(uint32_t value)
{
    REG_PL_WR(UART1_DIV2_ADDR, value);
}

// field definitions
#define UART1_DIV2_MASK   ((uint32_t)0x000000FF)
#define UART1_DIV2_LSB    0
#define UART1_DIV2_WIDTH  ((uint32_t)0x00000008)

#define UART1_DIV2_RST    0x0

__INLINE uint8_t uart1_div2_getf(void)
{
    uint32_t localVal = REG_PL_RD(UART1_DIV2_ADDR);
    return (localVal >> 0);
}

__INLINE void uart1_div2_setf(uint8_t div2)
{
    REG_PL_WR(UART1_DIV2_ADDR, (uint32_t)div2 << 0);
}

#endif // _REG_UART1_H_
