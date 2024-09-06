#ifndef _REG_I2CM_H_
#define _REG_I2CM_H_

#include "chip.h"

/* ========================================================================== */
/* ===============       Inter-Integrated Circuit (I2C)       =============== */
/* ========================================================================== */
typedef struct {
  __IO uint32_t                          IC_CON;                       //0x00000000
  __IO uint32_t                          IC_TAR;                       //0x00000004
  __IO uint32_t                          IC_SAR;                       //0x00000008
  __IO uint32_t                          IC_HS_MADDR;                  //0x0000000C
  __IO uint32_t                          IC_DATA_CMD;                  //0x00000010
  __IO uint32_t                          IC_SS_SCL_HCNT;               //0x00000014
  __IO uint32_t                          IC_SS_SCL_LCNT;               //0x00000018
  __IO uint32_t                          IC_FS_SCL_HCNT;               //0x0000001C
  __IO uint32_t                          IC_FS_SCL_LCNT;               //0x00000020
  __IO uint32_t                          IC_HS_SCL_HCNT;               //0x00000024
  __IO uint32_t                          IC_HS_SCL_LCNT;               //0x00000028
  __IO uint32_t                          IC_INTR_STAT;                 //0x0000002C
  __IO uint32_t                          IC_INTR_MASK;                 //0x00000030
  __IO uint32_t                          IC_RAW_INTR_STAT;             //0x00000034
  __IO uint32_t                          IC_RX_TL;                     //0x00000038
  __IO uint32_t                          IC_TX_TL;                     //0x0000003C
  __IO uint32_t                          IC_CLR_INTR;                  //0x00000040
  __IO uint32_t                          IC_CLR_RX_UNDER;              //0x00000044
  __IO uint32_t                          IC_CLR_RX_OVER;               //0x00000048
  __IO uint32_t                          IC_CLR_TX_OVER;               //0x0000004C
  __IO uint32_t                          IC_CLR_RD_REQ;                //0x00000050
  __IO uint32_t                          IC_CLR_TX_ABRT;               //0x00000054
  __IO uint32_t                          IC_CLR_RX_DONE;               //0x00000058
  __IO uint32_t                          IC_CLR_ACTIVITY;              //0x0000005C
  __IO uint32_t                          IC_CLR_STOP_DET;              //0x00000060
  __IO uint32_t                          IC_CLR_START_DET;             //0x00000064
  __IO uint32_t                          IC_CLR_GEN_CALL;              //0x00000068
  __IO uint32_t                          IC_ENABLE;                    //0x0000006C
  __IO uint32_t                          IC_STATUS;                    //0x00000070
  __IO uint32_t                          IC_TXFLR;                     //0x00000074
  __IO uint32_t                          IC_RXFLR;                     //0x00000078
  __IO uint32_t                          IC_SDA_HOLD;                  //0x0000007C
  __IO uint32_t                          IC_TX_ABRT_SOURCE;            //0x00000080
  __IO uint32_t Reserved_00000084;                    //0x00000084
  __IO uint32_t                          IC_DMA_CR;                    //0x00000088
  __IO uint32_t                          IC_DMA_TDLR;                  //0x0000008C
  __IO uint32_t                          IC_DMA_RDLR;                  //0x00000090
  __IO uint32_t                          IC_SDA_SETUP;                 //0x00000094
  __IO uint32_t                          IC_ACK_GENERAL_CALL;          //0x00000098
  __IO uint32_t                          IC_ENABLE_STATUS;             //0x0000009C
  __IO uint32_t                          IC_FS_SPKLEN;                 //0x000000A0
  __IO uint32_t                          IC_HS_SPKLEN;                 //0x000000A4
  __IO uint32_t                          IC_CLR_RESTART_DET;           //0x000000A8
  __IO uint32_t Reserved_000000AC[18];                //0x000000AC
  __IO uint32_t                          IC_COMP_PARAM_1;              //0x000000F4
  __IO uint32_t                          IC_COMP_VERSION;              //0x000000F8
  __IO uint32_t                          IC_COMP_TYPE;                 //0x000000FC
} AIC_I2CM_TypeDef;

static AIC_I2CM_TypeDef * const AIC_I2CM0 = ((AIC_I2CM_TypeDef *)AIC_I2CM0_BASE);

//IC_CON
#define I2CM_MASTER_MODE                (1<<0)
#define I2CM_MASTER_MODE_POS            (0)
#define I2CM_SPEED(n)                   (((n)&3)<<1)
#define I2CM_SPEED_LSB                  (1)
#define I2CM_SPEED_MASK                 (3<<1)
#define I2CM_IC_10BITADDR_SLAVE         (1<<3)
#define I2CM_IC_10BITADDR_SLAVE_POS     (3)
#define I2CM_IC_RESTART_EN              (1<<5)
#define I2CM_IC_RESTART_EN_POS          (5)
#define I2CM_IC_SLAVE_DISABLE           (1<<6)
#define I2CM_IC_SLAVE_DISABLE_POS       (6)
#define I2CM_STOP_DET_IFADDRESSED       (1<<7)
#define I2CM_STOP_DET_IFADDRESSED_POS   (7)
#define I2CM_TX_EMPTY_CTRL              (1<<8)
#define I2CM_TX_EMPTY_CTRL_POS          (8)

//IC_TAR
#define I2CM_IC_TAR(n)                  (((n)&0x3FF)<<0)
#define I2CM_IC_TAR_LSB                 (0)
#define I2CM_IC_TAR_MASK                (0x3FF<<0)
#define I2CM_GC_OR_START                (1<<10)
#define I2CM_GC_OR_START_POS            (10)
#define I2CM_SPECIAL                    (1<<11)
#define I2CM_SPECIAL_POS                (11)
#define I2CM_IC_10BITADDR_MASTER        (1<<12)
#define I2CM_IC_10BITADDR_MASTER_POS    (12)

//IC_SAR
#define I2CM_IC_SAR(n)                  (((n)&0x3FF)<<0)
#define I2CM_IC_SAR_LSB                 (0)
#define I2CM_IC_SAR_MASK                (0x3FF<<0)

//IC_HS_MADDR
#define I2CM_IC_HS_MAR(n)               (((n)&7)<<0)
#define I2CM_IC_HS_MAR_LSB              (0)
#define I2CM_IC_HS_MAR_MASK             (7<<0)

//IC_DATA_CMD
#define I2CM_DAT(n)                     (((n)&0xFF)<<0)
#define I2CM_DAT_LSB                    (0)
#define I2CM_DAT_MASK                   (0xFF<<0)
#define I2CM_CMD                        (1<<8)
#define I2CM_CMD_POS                    (8)

//IC_SS_SCL_HCNT
#define I2CM_IC_SS_SCL_HCNT(n)          (((n)&0xFFFF)<<0)
#define I2CM_IC_SS_SCL_HCNT_LSB         (0)
#define I2CM_IC_SS_SCL_HCNT_MASK        (0xFFFF<<0)

//IC_SS_SCL_LCNT
#define I2CM_IC_SS_SCL_LCNT(n)          (((n)&0xFFFF)<<0)
#define I2CM_IC_SS_SCL_LCNT_LSB         (0)
#define I2CM_IC_SS_SCL_LCNT_MASK        (0xFFFF<<0)

//IC_FS_SCL_HCNT
#define I2CM_IC_FS_SCL_HCNT(n)          (((n)&0xFFFF)<<0)
#define I2CM_IC_FS_SCL_HCNT_LSB         (0)
#define I2CM_IC_FS_SCL_HCNT_MASK        (0xFFFF<<0)

//IC_FS_SCL_LCNT
#define I2CM_IC_FS_SCL_LCNT(n)          (((n)&0xFFFF)<<0)
#define I2CM_IC_FS_SCL_LCNT_LSB         (0)
#define I2CM_IC_FS_SCL_LCNT_MASK        (0xFFFF<<0)

//IC_HS_SCl_HCNT
#define I2CM_IC_HS_SCL_HCNT(n)          (((n)&0xFFFF)<<0)
#define I2CM_IC_HS_SCL_HCNT_LSB         (0)
#define I2CM_IC_HS_SCL_HCNT_MASK        (0xFFFF<<0)

//IC_HS_SCL_LCNT
#define I2CM_IC_HS_SCL_LCNT(n)          (((n)&0xFFFF)<<0)
#define I2CM_IC_HS_SCL_LCNT_LSB         (0)
#define I2CM_IC_HS_SCL_LCNT_MASK        (0xFFFF<<0)

//IC_INTR_STAT
#define I2CM_R_RX_UNDER                 (1<<0)
#define I2CM_R_RX_UNDER_POS             (0)
#define I2CM_R_RX_OVER                  (1<<1)
#define I2CM_R_RX_OVER_POS              (1)
#define I2CM_R_RX_FULL                  (1<<2)
#define I2CM_R_RX_FULL_POS              (2)
#define I2CM_R_TX_OVER                  (1<<3)
#define I2CM_R_TX_OVER_POS              (3)
#define I2CM_R_TX_EMPTY                 (1<<4)
#define I2CM_R_TX_EMPTY_POS             (4)
#define I2CM_R_RD_REQ                   (1<<5)
#define I2CM_R_RD_REQ_POS               (5)
#define I2CM_R_TX_ABRT                  (1<<6)
#define I2CM_R_TX_ABRT_POS              (6)
#define I2CM_R_RX_DONE                  (1<<7)
#define I2CM_R_RX_DONE_POS              (7)
#define I2CM_R_ACTIVITY                 (1<<8)
#define I2CM_R_ACTIVITY_POS             (8)
#define I2CM_R_STOP_DET                 (1<<9)
#define I2CM_R_STOP_DET_POS             (9)
#define I2CM_R_START_DET                (1<<10)
#define I2CM_R_START_DET_POS            (10)
#define I2CM_R_GEN_CALL                 (1<<11)
#define I2CM_R_GEN_CALL_POS             (11)
#define I2CM_R_RESTART_DET              (1<<12)
#define I2CM_R_RESTART_DET_POS          (12)
#define I2CM_R_MASTER_ON_HOLD           (1<<13)
#define I2CM_R_MASTER_ON_HOLD_POS       (13)

//IC_INTR_MASK
#define I2CM_M_RX_UNDER                 (1<<0)
#define I2CM_M_RX_UNDER_POS             (0)
#define I2CM_M_RX_OVER                  (1<<1)
#define I2CM_M_RX_OVER_POS              (1)
#define I2CM_M_RX_FULL                  (1<<2)
#define I2CM_M_RX_FULL_POS              (2)
#define I2CM_M_TX_OVER                  (1<<3)
#define I2CM_M_TX_OVER_POS              (3)
#define I2CM_M_TX_EMPTY                 (1<<4)
#define I2CM_M_TX_EMPTY_POS             (4)
#define I2CM_M_RD_REQ                   (1<<5)
#define I2CM_M_RD_REQ_POS               (5)
#define I2CM_M_TX_ABRT                  (1<<6)
#define I2CM_M_TX_ABRT_POS              (6)
#define I2CM_M_RX_DONE                  (1<<7)
#define I2CM_M_RX_DONE_POS              (7)
#define I2CM_M_ACTIVITY                 (1<<8)
#define I2CM_M_ACTIVITY_POS             (8)
#define I2CM_M_STOP_DET                 (1<<9)
#define I2CM_M_STOP_DET_POS             (9)
#define I2CM_M_START_DET                (1<<10)
#define I2CM_M_START_DET_POS            (10)
#define I2CM_M_GEN_CALL                 (1<<11)
#define I2CM_M_GEN_CALL_POS             (11)
#define I2CM_M_RESTART_DET              (1<<12)
#define I2CM_M_RESTART_DET_POS          (12)
#define I2CM_M_MASTER_ON_HOLD           (1<<13)
#define I2CM_M_MASTER_ON_HOLD_POS       (13)

//IC_RAW_INTR_STAT
#define I2CM_RX_UNDER                   (1<<0)
#define I2CM_RX_UNDER_POS               (0)
#define I2CM_RX_OVER                    (1<<1)
#define I2CM_RX_OVER_POS                (1)
#define I2CM_RX_FULL                    (1<<2)
#define I2CM_RX_FULL_POS                (2)
#define I2CM_TX_OVER                    (1<<3)
#define I2CM_TX_OVER_POS                (3)
#define I2CM_TX_EMPTY                   (1<<4)
#define I2CM_TX_EMPTY_POS               (4)
#define I2CM_RD_REQ                     (1<<5)
#define I2CM_RD_REQ_POS                 (5)
#define I2CM_TX_ABRT                    (1<<6)
#define I2CM_TX_ABRT_POS                (6)
#define I2CM_RX_DONE                    (1<<7)
#define I2CM_RX_DONE_POS                (7)
#define I2CM_ACTIVITY                   (1<<8)
#define I2CM_ACTIVITY_POS               (8)
#define I2CM_STOP_DET                   (1<<9)
#define I2CM_STOP_DET_POS               (9)
#define I2CM_START_DET                  (1<<10)
#define I2CM_START_DET_POS              (10)
#define I2CM_GEN_CALL                   (1<<11)
#define I2CM_GEN_CALL_POS               (11)
#define I2CM_RESTART_DET                (1<<12)
#define I2CM_RESTART_DET_POS            (12)
#define I2CM_MASTER_ON_HOLD             (1<<13)
#define I2CM_MASTER_ON_HOLD_POS         (13)

//IC_RX_TL
#define I2CM_RX_TL(n)                   (((n)&0xFF)<<0)
#define I2CM_RX_TL_LSB                  (0)
#define I2CM_RX_TL_MASK                 (0xFF<<0)

//IC_TX_TL
#define I2CM_TX_TL(n)                   (((n)&0xFF)<<0)
#define I2CM_TX_TL_LSB                  (0)
#define I2CM_TX_TL_MASK                 (0xFF<<0)

//IC_CLR_INTR
#define I2CM_CLR_INTR                   (1<<0)
#define I2CM_CLR_INTR_POS               (0)

//IC_CLR_RX_UNDER
#define I2CM_CLR_RX_UNDER               (1<<0)
#define I2CM_CLR_RX_UNDER_POS           (0)

//IC_CLR_RX_OVER
#define I2CM_CLR_RX_OVER                (1<<0)
#define I2CM_CLR_RX_OVER_POS            (0)

//IC_CLR_TX_OVER
#define I2CM_CLR_TX_OVER                (1<<0)
#define I2CM_CLR_TX_OVER_POS            (0)

//IC_CLR_RD_REQ
#define I2CM_CLR_RD_REQ                 (1<<0)
#define I2CM_CLR_RD_REQ_POS             (0)

//IC_CLR_TX_ABRT
#define I2CM_CLR_TX_ABRT                (1<<0)
#define I2CM_CLR_TX_ABRT_POS            (0)

//IC_CLR_RX_DONE
#define I2CM_CLR_TX_DONE                (1<<0)
#define I2CM_CLR_TX_DONE_POS            (0)

//IC_CLR_ACTIVITY
#define I2CM_CLR_ACTIVITY               (1<<0)
#define I2CM_CLR_ACTIVITY_POS           (0)

//IC_CLR_STOP_DET
#define I2CM_CLR_STOP_DET               (1<<0)
#define I2CM_CLR_STOP_DET_POS           (0)

//IC_CLR_START_DET
#define I2CM_CLR_START_DET              (1<<0)
#define I2CM_CLR_START_DET_POS          (0)

//IC_CLR_GEN_CALL
#define I2CM_CLR_GEN_CALL               (1<<0)
#define I2CM_CLR_GEN_CALL_POS           (0)

//IC_ENABLE
#define I2CM_ENABLE                     (1<<0)
#define I2CM_ENABLE_POS                 (0)
#define I2CM_ABORT                      (1<<1)
#define I2CM_ABORT_POS                  (1)
#define I2CM_TX_CMD_BLOCK               (1<<2)
#define I2CM_TX_CMD_BLOCK_POS           (2)

//IC_STATUS
#define I2CM_ACTIVITY_X1                (1<<0)
#define I2CM_ACTIVITY_X1_POS            (0)
#define I2CM_TFNF                       (1<<1)
#define I2CM_TFNF_POS                   (1)
#define I2CM_TFE                        (1<<2)
#define I2CM_TFE_POS                    (2)
#define I2CM_RFNE                       (1<<3)
#define I2CM_RFNE_POS                   (3)
#define I2CM_RFF                        (1<<4)
#define I2CM_RFF_POS                    (4)
#define I2CM_MAT_ACTIVITY               (1<<5)
#define I2CM_MAT_ACTIVITY_POS           (5)
#define I2CM_SLV_ACTIVITY               (1<<6)
#define I2CM_SLV_ACTIVITY_POS           (6)

//IC_TXFLR
#define I2CM_TXFLR(n)                   (((n)&31)<<0)
#define I2CM_TXFLR_LSB                  (0)
#define I2CM_TXFLR_MASK                 (31<<0)

//IC_RXFLR
#define I2CM_RXFLR(n)                   (((n)&31)<<0)
#define I2CM_RXFLR_LSB                  (0)
#define I2CM_RXFLR_MASK                 (31<<0)

//IC_SDA_HOLD
#define I2CM_IC_SDA_TX_HOLD(n)          (((n)&0xFFFF)<<0)
#define I2CM_IC_SDA_TX_HOLD_LSB         (0)
#define I2CM_IC_SDA_TX_HOLD_MASK        (0xFFFF<<0)
#define I2CM_IC_SDA_RX_HOLD(n)          (((n)&0xFF)<<16)
#define I2CM_IC_SDA_RX_HOLD_LSB         (16)
#define I2CM_IC_SDA_RX_HOLD_MASK        (0xFF<<16)

//IC_TX_ABRT_SOURCE
#define I2CM_ABRT_7B_ADDR_NOACK         (1<<0)
#define I2CM_ABRT_7B_ADDR_NOACK_POS     (0)
#define I2CM_ABRT_10ADDR1_NOACK         (1<<1)
#define I2CM_ABRT_10ADDR1_NOACK_POS     (1)
#define I2CM_ABRT_10ADDR2_NOACK         (1<<2)
#define I2CM_ABRT_10ADDR2_NOACK_POS     (2)
#define I2CM_ABRT_TXDATA_NOACK          (1<<3)
#define I2CM_ABRT_TXDATA_NOACK_POS      (3)
#define I2CM_ABRT_GCALL_NOACK           (1<<4)
#define I2CM_ABRT_GCALL_NOACK_POS       (4)
#define I2CM_ABRT_GCALL_READ            (1<<5)
#define I2CM_ABRT_GCALL_READ_POS        (5)
#define I2CM_ABRT_HS_ACKDET             (1<<6)
#define I2CM_ABRT_HS_ACKDET_POS         (6)
#define I2CM_ABRT_SBYTE_ACKDET          (1<<7)
#define I2CM_ABRT_SBYTE_ACKDET_POS      (7)
#define I2CM_ABRT_HS_NORSTRT            (1<<8)
#define I2CM_ABRT_HS_NORSTRT_POS        (8)
#define I2CM_ABRT_SBYTE_NORSTRT         (1<<9)
#define I2CM_ABRT_SBYTE_NORSTRT_POS     (9)
#define I2CM_ABRT_10B_RD_NORSTRT        (1<<10)
#define I2CM_ABRT_10B_RD_NORSTRT_POS    (10)
#define I2CM_ABRT_MASTER_DIS            (1<<11)
#define I2CM_ABRT_MASTER_DIS_POS        (11)
#define I2CM_ARB_LOST                   (1<<12)
#define I2CM_ARB_LOST_POS               (12)
#define I2CM_ABRT_SLVFLUSH_TXFIFO       (1<<13)
#define I2CM_ABRT_SLVFLUSH_TXFIFO_POS   (13)
#define I2CM_ABRT_SLV_ARBLOST           (1<<14)
#define I2CM_ABRT_SLV_ARBLOST_POS       (14)
#define I2CM_ABRT_SLVRD_INTX            (1<<15)
#define I2CM_ABRT_SLVRD_INTX_POS        (15)
#define I2CM_ABRT_USER_ABRT             (1<<16)
#define I2CM_ABRT_USER_ABRT_POS         (16)
#define I2CM_TX_FLUSH_CNT(n)            (((n)&0x1FF)<<23)
#define I2CM_TX_FLUSH_CNT_LSB           (23)
#define I2CM_TX_FLUSH_CNT_MASK          (0x1FF<<23)

//IC_DMA_CR
#define I2CM_RDMAE                      (1<<0)
#define I2CM_RDMAE_POS                  (0)
#define I2CM_TDMAE                      (1<<1)
#define I2CM_TDMAE_POS                  (1)

//IC_DMA_TDLR
#define I2CM_DMATDL(n)                  (((n)&15)<<0)
#define I2CM_DMATDL_LSB                 (0)
#define I2CM_DMATDL_MASK                (15<<0)

//IC_DMA_RDLR
#define I2CM_DMARDL(n)                  (((n)&15)<<0)
#define I2CM_DMARDL_LSB                 (0)
#define I2CM_DMARDL_MASK                (15<<0)

//IC_SDA_SETUP
#define I2CM_SDA_SETUP(n)               (((n)&0xFF)<<0)
#define I2CM_SDA_SETUP_LSB              (0)
#define I2CM_SDA_SETUP_MASK             (0xFF<<0)

//IC_ACK_GENERAL_CALL
#define I2CM_ACK_GEN_CALL               (1<<0)
#define I2CM_ACK_GEN_CALL_POS           (0)

//IC_ENABLE_STATUS
#define I2CM_IC_EN                      (1<<0)
#define I2CM_IC_EN_POS                  (0)
#define I2CM_SLV_DISABLED_WHILE_BUSY      (1<<1)
#define I2CM_SLV_DISABLED_WHILE_BUSY_POS  (1)
#define I2CM_SLV_RX_DATA_LOST           (1<<2)
#define I2CM_SLV_RX_DATA_LOST_POS       (2)

//IC_FS_SPKLEN
#define I2CM_IC_FS_SPKLEN(n)            (((n)&0xFF)<<0)
#define I2CM_IC_FS_SPKLEN_LSB           (0)
#define I2CM_IC_FS_SPKLEN_MASK          (0xFF<<0)

//IC_HS_SPKLEN
#define I2CM_IC_HS_SPKLEN(n)            (((n)&0xFF)<<0)
#define I2CM_IC_HS_SPKLEN_LSB           (0)
#define I2CM_IC_HS_SPKLEN_MASK          (0xFF<<0)

//IC_CLR_RESTART_DET
#define I2CM_CLR_RESTART_DET            (1<<0)
#define I2CM_CLR_RESTART_DET_POS        (0)

//IC_COMP_PARAM_1
#define I2CM_APB_DATA_WIDTH(n)          (((n)&3)<<0)
#define I2CM_APB_DATA_WIDTH_LSB         (0)
#define I2CM_APB_DATA_WIDTH_MASK        (3<<0)
#define I2CM_MAX_SPEED_MODE(n)          (((n)&3)<<2)
#define I2CM_MAX_SPEED_MODE_LSB         (2)
#define I2CM_MAX_SPEED_MODE_MASK        (3<<2)
#define I2CM_HC_COUNT_VALUES            (1<<4)
#define I2CM_HC_COUNT_VALUES_POS        (4)
#define I2CM_INTR_IO                    (1<<5)
#define I2CM_INTR_IO_POS                (5)
#define I2CM_HAS_DMA                    (1<<6)
#define I2CM_HAS_DMA_POS                (6)
#define I2CM_ADD_ENCODED_PARAMS         (1<<7)
#define I2CM_ADD_ENCODED_PARAMS_POS     (7)
#define I2CM_RX_BUFFER_DEPTH(n)         (((n)&0xFF)<<8)
#define I2CM_RX_BUFFER_DEPTH_LSB        (8)
#define I2CM_RX_BUFFER_DEPTH_MASK       (0xFF<<8)
#define I2CM_TX_BUFFER_DEPTH(n)         (((n)&0xFF)<<16)
#define I2CM_TX_BUFFER_DEPTH_LSB        (16)
#define I2CM_TX_BUFFER_DEPTH_MASK       (0xFF<<16)

//IC_COMP_VERSION
#define I2CM_IC_COMP_VERSION(n)         (((n)&0xFFFFFFFF)<<0)
#define I2CM_IC_COMP_VERSION_LSB        (0)
#define I2CM_IC_COMP_VERSION_MASK       (0xFFFFFFFF<<0)

//IC_COMP_TYPE
#define I2CM_IC_COMP_TYPE(n)            (((n)&0xFFFFFFFF)<<0)
#define I2CM_IC_COMP_TYPE_LSB           (0)
#define I2CM_IC_COMP_TYPE_MASK          (0xFFFFFFFF<<0)

#endif /* _REG_I2CM_H_ */
