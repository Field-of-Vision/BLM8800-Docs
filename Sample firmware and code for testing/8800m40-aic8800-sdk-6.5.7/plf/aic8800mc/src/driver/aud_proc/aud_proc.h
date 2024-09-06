#ifndef _AUD_PROC_H_
#define _AUD_PROC_H_

#include "chip.h"

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// AUD_PROC_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_AUD_PROC_BASE          0x40037000

typedef volatile struct
{
    __IO uint32_t                          aud_proc_function_id;         //0x00000000
    __IO uint32_t                          aud_iis_cfg;                  //0x00000004
    __IO uint32_t                          aud_iis_tx_cfg_ch01;          //0x00000008
    __IO uint32_t                          aud_iis_tx_cfg_ch23;          //0x0000000C
    __IO uint32_t                          aud_iis_rx_cfg_ch01;          //0x00000010
    __IO uint32_t                          aud_iis_rx_cfg_ch23;          //0x00000014
    __IO uint32_t Reserved_00000018;                    //0x00000018
    __IO uint32_t                          aud_intf_i2s_cfg0;            //0x0000001C
    __IO uint32_t                          aud_intf_i2s_cfg1;            //0x00000020
    __IO uint32_t                          pcm_cfg_0;                    //0x00000024
    __IO uint32_t                          pcm_cfg_1;                    //0x00000028
} HWP_AUD_PROC_T;

static HWP_AUD_PROC_T * const hwp_audProc = ((HWP_AUD_PROC_T *)REG_AUD_PROC_BASE);


//aud_proc_function_id
#define AUD_PROC_REV_ID(n)              (((n)&0xFFFF)<<0)
#define AUD_PROC_REV_ID_LSB             (0)
#define AUD_PROC_REV_ID_MASK            (0xFFFF<<0)
#define AUD_PROC_FUNC_ID(n)             (((n)&0xFFFF)<<16)
#define AUD_PROC_FUNC_ID_LSB            (16)
#define AUD_PROC_FUNC_ID_MASK           (0xFFFF<<16)

//aud_iis_cfg
#define AUD_PROC_AUD_IIS_ENABLE         (1<<0)
#define AUD_PROC_AUD_IIS_ENABLE_POS     (0)
#define AUD_PROC_AUD_IIS_ADC_PATH_RESET      (1<<1)
#define AUD_PROC_AUD_IIS_ADC_PATH_RESET_POS  (1)
#define AUD_PROC_AUD_IIS_DAC_PATH_RESET      (1<<2)
#define AUD_PROC_AUD_IIS_DAC_PATH_RESET_POS  (2)
#define AUD_PROC_AUTO_CLOCK_GATING_EN      (1<<3)
#define AUD_PROC_AUTO_CLOCK_GATING_EN_POS  (3)
#define AUD_PROC_TX_LR_FIFO_SHARE_EN(n)      (((n)&3)<<4)
#define AUD_PROC_TX_LR_FIFO_SHARE_EN_LSB     (4)
#define AUD_PROC_TX_LR_FIFO_SHARE_EN_MASK    (3<<4)
#define AUD_PROC_RX_LR_FIFO_SHARE_EN(n)      (((n)&3)<<6)
#define AUD_PROC_RX_LR_FIFO_SHARE_EN_LSB     (6)
#define AUD_PROC_RX_LR_FIFO_SHARE_EN_MASK    (3<<6)
#define AUD_PROC_TX_BURST_MODE          (1<<8)
#define AUD_PROC_TX_BURST_MODE_POS      (8)
#define AUD_PROC_RX_BURST_MODE          (1<<9)
#define AUD_PROC_RX_BURST_MODE_POS      (9)
#define AUD_PROC_MONITOR_SEL(n)         (((n)&0x7F)<<25)
#define AUD_PROC_MONITOR_SEL_LSB        (25)
#define AUD_PROC_MONITOR_SEL_MASK       (0x7F<<25)

//aud_iis_tx_cfg_ch01
#define AUD_PROC_TX_EN_CH_01            (1<<0)
#define AUD_PROC_TX_EN_CH_01_POS        (0)
#define AUD_PROC_TX_FIFO_FLUSH_CH_01      (1<<1)
#define AUD_PROC_TX_FIFO_FLUSH_CH_01_POS  (1)
#define AUD_PROC_TX_MODE_CH_01(n)       (((n)&3)<<2)
#define AUD_PROC_TX_MODE_CH_01_LSB      (2)
#define AUD_PROC_TX_MODE_CH_01_MASK     (3<<2)
#define AUD_PROC_TX_FIFO_STAT_CH_01(n)      (((n)&3)<<4)
#define AUD_PROC_TX_FIFO_STAT_CH_01_LSB     (4)
#define AUD_PROC_TX_FIFO_STAT_CH_01_MASK    (3<<4)

//aud_iis_tx_cfg_ch23
#define AUD_PROC_TX_EN_CH_23            (1<<0)
#define AUD_PROC_TX_EN_CH_23_POS        (0)
#define AUD_PROC_TX_FIFO_FLUSH_CH_23      (1<<1)
#define AUD_PROC_TX_FIFO_FLUSH_CH_23_POS  (1)
#define AUD_PROC_TX_MODE_CH_23(n)       (((n)&3)<<2)
#define AUD_PROC_TX_MODE_CH_23_LSB      (2)
#define AUD_PROC_TX_MODE_CH_23_MASK     (3<<2)
#define AUD_PROC_TX_FIFO_STAT_CH_23(n)      (((n)&3)<<4)
#define AUD_PROC_TX_FIFO_STAT_CH_23_LSB     (4)
#define AUD_PROC_TX_FIFO_STAT_CH_23_MASK    (3<<4)

//aud_iis_rx_cfg_ch01
#define AUD_PROC_RX_EN_CH_01            (1<<0)
#define AUD_PROC_RX_EN_CH_01_POS        (0)
#define AUD_PROC_RX_FIFO_FLUSH_CH_01      (1<<1)
#define AUD_PROC_RX_FIFO_FLUSH_CH_01_POS  (1)
#define AUD_PROC_RX_MODE_CH_01(n)       (((n)&3)<<2)
#define AUD_PROC_RX_MODE_CH_01_LSB      (2)
#define AUD_PROC_RX_MODE_CH_01_MASK     (3<<2)
#define AUD_PROC_RX_FIFO_STAT_CH_01(n)      (((n)&3)<<4)
#define AUD_PROC_RX_FIFO_STAT_CH_01_LSB     (4)
#define AUD_PROC_RX_FIFO_STAT_CH_01_MASK    (3<<4)

//aud_iis_rx_cfg_ch23
#define AUD_PROC_RX_EN_CH_23            (1<<0)
#define AUD_PROC_RX_EN_CH_23_POS        (0)
#define AUD_PROC_RX_FIFO_FLUSH_CH_23      (1<<1)
#define AUD_PROC_RX_FIFO_FLUSH_CH_23_POS  (1)
#define AUD_PROC_RX_MODE_CH_23(n)       (((n)&3)<<2)
#define AUD_PROC_RX_MODE_CH_23_LSB      (2)
#define AUD_PROC_RX_MODE_CH_23_MASK     (3<<2)
#define AUD_PROC_RX_FIFO_STAT_CH_23(n)      (((n)&3)<<4)
#define AUD_PROC_RX_FIFO_STAT_CH_23_LSB     (4)
#define AUD_PROC_RX_FIFO_STAT_CH_23_MASK    (3<<4)

//aud_intf_i2s_cfg0
#define AUD_PROC_SWAP_CHLR_0(n)         (((n)&3)<<0)
#define AUD_PROC_SWAP_CHLR_0_LSB        (0)
#define AUD_PROC_SWAP_CHLR_0_MASK       (3<<0)
#define AUD_PROC_TX_DATA_HALF_CYCLE_DLY_0      (1<<2)
#define AUD_PROC_TX_DATA_HALF_CYCLE_DLY_0_POS  (2)
#define AUD_PROC_LSB_0                  (1<<3)
#define AUD_PROC_LSB_0_POS              (3)
#define AUD_PROC_RIGHT_JUSTIFIED_0      (1<<4)
#define AUD_PROC_RIGHT_JUSTIFIED_0_POS  (4)
#define AUD_PROC_BCK_LRCK_0(n)          (((n)&31)<<5)
#define AUD_PROC_BCK_LRCK_0_LSB         (5)
#define AUD_PROC_BCK_LRCK_0_MASK        (31<<5)
#define AUD_PROC_WLEN_0(n)              (((n)&3)<<10)
#define AUD_PROC_WLEN_0_LSB             (10)
#define AUD_PROC_WLEN_0_MASK            (3<<10)
#define AUD_PROC_LRCK_POL_0             (1<<12)
#define AUD_PROC_LRCK_POL_0_POS         (12)
#define AUD_PROC_BCK_POL_0              (1<<13)
#define AUD_PROC_BCK_POL_0_POS          (13)
#define AUD_PROC_BCKOUT_GATE_0          (1<<14)
#define AUD_PROC_BCKOUT_GATE_0_POS      (14)
#define AUD_PROC_RX_HALF_CYCLE_DLY_0      (1<<15)
#define AUD_PROC_RX_HALF_CYCLE_DLY_0_POS  (15)
#define AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_0      (1<<16)
#define AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_0_POS  (16)
#define AUD_PROC_RX_DLY_0(n)            (((n)&3)<<17)
#define AUD_PROC_RX_DLY_0_LSB           (17)
#define AUD_PROC_RX_DLY_0_MASK          (3<<17)
#define AUD_PROC_TX_DLY_S_0             (1<<19)
#define AUD_PROC_TX_DLY_S_0_POS         (19)
#define AUD_PROC_TX_DLY_0               (1<<20)
#define AUD_PROC_TX_DLY_0_POS           (20)
#define AUD_PROC_MASTER_MODE_0          (1<<21)
#define AUD_PROC_MASTER_MODE_0_POS      (21)
#define AUD_PROC_RX_SERIAL_MODE_0(n)      (((n)&7)<<22)
#define AUD_PROC_RX_SERIAL_MODE_0_LSB     (22)
#define AUD_PROC_RX_SERIAL_MODE_0_MASK    (7<<22)
#define AUD_PROC_TX_SERIAL_MODE_0(n)      (((n)&7)<<25)
#define AUD_PROC_TX_SERIAL_MODE_0_LSB     (25)
#define AUD_PROC_TX_SERIAL_MODE_0_MASK    (7<<25)
#define AUD_PROC_TX_OFF_0               (1<<28)
#define AUD_PROC_TX_OFF_0_POS           (28)
#define AUD_PROC_TX_MODE_0(n)           (((n)&3)<<29)
#define AUD_PROC_TX_MODE_0_LSB          (29)
#define AUD_PROC_TX_MODE_0_MASK         (3<<29)
#define AUD_PROC_I2S_ENABLE_0           (1<<31)
#define AUD_PROC_I2S_ENABLE_0_POS       (31)

//aud_intf_i2s_cfg1
#define AUD_PROC_SWAP_CHLR_1(n)         (((n)&3)<<0)
#define AUD_PROC_SWAP_CHLR_1_LSB        (0)
#define AUD_PROC_SWAP_CHLR_1_MASK       (3<<0)
#define AUD_PROC_TX_DATA_HALF_CYCLE_DLY_1      (1<<2)
#define AUD_PROC_TX_DATA_HALF_CYCLE_DLY_1_POS  (2)
#define AUD_PROC_LSB_1                  (1<<3)
#define AUD_PROC_LSB_1_POS              (3)
#define AUD_PROC_RIGHT_JUSTIFIED_1      (1<<4)
#define AUD_PROC_RIGHT_JUSTIFIED_1_POS  (4)
#define AUD_PROC_BCK_LRCK_1(n)          (((n)&31)<<5)
#define AUD_PROC_BCK_LRCK_1_LSB         (5)
#define AUD_PROC_BCK_LRCK_1_MASK        (31<<5)
#define AUD_PROC_WLEN_1(n)              (((n)&3)<<10)
#define AUD_PROC_WLEN_1_LSB             (10)
#define AUD_PROC_WLEN_1_MASK            (3<<10)
#define AUD_PROC_LRCK_POL_1             (1<<12)
#define AUD_PROC_LRCK_POL_1_POS         (12)
#define AUD_PROC_BCK_POL_1              (1<<13)
#define AUD_PROC_BCK_POL_1_POS          (13)
#define AUD_PROC_BCKOUT_GATE_1          (1<<14)
#define AUD_PROC_BCKOUT_GATE_1_POS      (14)
#define AUD_PROC_RX_HALF_CYCLE_DLY_1      (1<<15)
#define AUD_PROC_RX_HALF_CYCLE_DLY_1_POS  (15)
#define AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_1      (1<<16)
#define AUD_PROC_TX_LRCK_HALF_CYCLE_DLY_1_POS  (16)
#define AUD_PROC_RX_DLY_1(n)            (((n)&3)<<17)
#define AUD_PROC_RX_DLY_1_LSB           (17)
#define AUD_PROC_RX_DLY_1_MASK          (3<<17)
#define AUD_PROC_TX_DLY_S_1             (1<<19)
#define AUD_PROC_TX_DLY_S_1_POS         (19)
#define AUD_PROC_TX_DLY_1               (1<<20)
#define AUD_PROC_TX_DLY_1_POS           (20)
#define AUD_PROC_MASTER_MODE_1          (1<<21)
#define AUD_PROC_MASTER_MODE_1_POS      (21)
#define AUD_PROC_RX_SERIAL_MODE_1(n)      (((n)&7)<<22)
#define AUD_PROC_RX_SERIAL_MODE_1_LSB     (22)
#define AUD_PROC_RX_SERIAL_MODE_1_MASK    (7<<22)
#define AUD_PROC_TX_SERIAL_MODE_1(n)      (((n)&7)<<25)
#define AUD_PROC_TX_SERIAL_MODE_1_LSB     (25)
#define AUD_PROC_TX_SERIAL_MODE_1_MASK    (7<<25)
#define AUD_PROC_TX_OFF_1               (1<<28)
#define AUD_PROC_TX_OFF_1_POS           (28)
#define AUD_PROC_TX_MODE_1(n)           (((n)&3)<<29)
#define AUD_PROC_TX_MODE_1_LSB          (29)
#define AUD_PROC_TX_MODE_1_MASK         (3<<29)
#define AUD_PROC_I2S_ENABLE_1           (1<<31)
#define AUD_PROC_I2S_ENABLE_1_POS       (31)

//pcm_cfg_0
#define AUD_PROC_SLOTNUM_0(n)           (((n)&0xFF)<<0)
#define AUD_PROC_SLOTNUM_0_LSB          (0)
#define AUD_PROC_SLOTNUM_0_MASK         (0xFF<<0)
#define AUD_PROC_LONGSYNC_0             (1<<8)
#define AUD_PROC_LONGSYNC_0_POS         (8)
#define AUD_PROC_TX_BIT_MODE_0          (1<<9)
#define AUD_PROC_TX_BIT_MODE_0_POS      (9)
#define AUD_PROC_RX_BIT_MODE_0          (1<<10)
#define AUD_PROC_RX_BIT_MODE_0_POS      (10)
#define AUD_PROC_LRCK_M_DLY_0           (1<<11)
#define AUD_PROC_LRCK_M_DLY_0_POS       (11)
#define AUD_PROC_TX_SYNC_MODE_0         (1<<12)
#define AUD_PROC_TX_SYNC_MODE_0_POS     (12)
#define AUD_PROC_LOOP_BACK_0            (1<<13)
#define AUD_PROC_LOOP_BACK_0_POS        (13)
#define AUD_PROC_BCKOUT_AUTO_GATE_BYPASS_0      (1<<14)
#define AUD_PROC_BCKOUT_AUTO_GATE_BYPASS_0_POS  (14)
#define AUD_PROC_RX_MODE_0(n)           (((n)&3)<<17)
#define AUD_PROC_RX_MODE_0_LSB          (17)
#define AUD_PROC_RX_MODE_0_MASK         (3<<17)
#define AUD_PROC_I2S_CHN_OUT_SEL        (1<<19)
#define AUD_PROC_I2S_CHN_OUT_SEL_POS    (19)
#define AUD_PROC_I2S_CHN_IN_SEL         (1<<20)
#define AUD_PROC_I2S_CHN_IN_SEL_POS     (20)

//pcm_cfg_1
#define AUD_PROC_SLOTNUM_1(n)           (((n)&0xFF)<<0)
#define AUD_PROC_SLOTNUM_1_LSB          (0)
#define AUD_PROC_SLOTNUM_1_MASK         (0xFF<<0)
#define AUD_PROC_LONGSYNC_1             (1<<8)
#define AUD_PROC_LONGSYNC_1_POS         (8)
#define AUD_PROC_TX_BIT_MODE_1          (1<<9)
#define AUD_PROC_TX_BIT_MODE_1_POS      (9)
#define AUD_PROC_RX_BIT_MODE_1          (1<<10)
#define AUD_PROC_RX_BIT_MODE_1_POS      (10)
#define AUD_PROC_LRCK_M_DLY_1           (1<<11)
#define AUD_PROC_LRCK_M_DLY_1_POS       (11)
#define AUD_PROC_TX_SYNC_MODE_1         (1<<12)
#define AUD_PROC_TX_SYNC_MODE_1_POS     (12)
#define AUD_PROC_LOOP_BACK_1            (1<<13)
#define AUD_PROC_LOOP_BACK_1_POS        (13)
#define AUD_PROC_BCKOUT_AUTO_GATE_BYPASS_1      (1<<14)
#define AUD_PROC_BCKOUT_AUTO_GATE_BYPASS_1_POS  (14)
#define AUD_PROC_RX_MODE_1(n)           (((n)&3)<<17)
#define AUD_PROC_RX_MODE_1_LSB          (17)
#define AUD_PROC_RX_MODE_1_MASK         (3<<17)





#endif

