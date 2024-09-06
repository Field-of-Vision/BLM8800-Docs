/**
 ****************************************************************************************
 *
 * @file dma_generic.h
 *
 * @brief DMA generic header file
 *
 ****************************************************************************************
 */

#ifndef _DMA_GENERIC_H_
#define _DMA_GENERIC_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "reg_dma.h"
#include "dma_common.h"

/// DMA channel indexes
enum {
    /// Channels for Wi-Fi Host to Fw
    DMA_CHANNEL_IPC_DATA_TX          = 0,

    /// Channels for audio
    DMA_CHANNEL_AUD_STREAM0_PLAYBACK = 1,
    DMA_CHANNEL_AUD_STREAM0_CAPTURE  = 2,
    DMA_CHANNEL_AUD_STREAM1_PLAYBACK = 3,
    DMA_CHANNEL_AUD_STREAM1_CAPTURE  = 4,

    ///Channels for Wi-Fi fw to host data rx[FW Fixed]
    DMA_CHANNEL_IPC_DATA_RX0         = 5,
    ///Channels for Wi-Fi data transfer
    DMA_CHANNEL_WIFI_DATA_TX         = 6,
    ///Channels for Wi-Fi data transfer[with HostIf USB/SDIO]
    DMA_CHANNEL_WIFI_DATA_RX         = 7,

    DMA_CHANNEL_IPC_DBG_DUMP         = 10,

    /// Channels for UART
    DMA_CHANNEL_UART_RX              = 8,
    DMA_CHANNEL_UART_TX              = 9,
    /// Channels for SPI0
    DMA_CHANNEL_SPI0_RX              = 8,
    DMA_CHANNEL_SPI0_TX              = 9,
    /// Channels for I2CM0
    DMA_CHANNEL_I2CM_RX              = 8,
    DMA_CHANNEL_I2CM_TX              = 9,

    /// Channels for SDMMC
    DMA_CHANNEL_SDMMC_RX             = 10,
    DMA_CHANNEL_SDMMC_TX             = 11,

    DMA_CHANNEL_MAX                  = 12
};

/// DMA descriptors
typedef struct {
    uint32_t SAR;               /* Src Addr             */
    uint32_t DAR;               /* Dest Addr            */
    uint32_t TBL0CR;            /* Trans Blk Lvl-0 Cnt  */
    uint32_t TBL1CR;            /* Trans Blk Lvl-1 Cnt  */
    uint32_t TBL2CR;            /* Trans Blk Lvl-2 Cnt  */
    uint32_t TSR;               /* Trans Sz             */
    uint32_t RESERVED0[2];
    uint32_t LNAR;              /* Lli Node Addr        */
    uint32_t RESERVED1[3];
}dma_desc_t;

#endif // _DMA_GENERIC_H_
