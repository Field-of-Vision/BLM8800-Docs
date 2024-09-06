/**
 ****************************************************************************************
 *
 * @file dma_api_aud.h
 *
 * @brief DMA utility functions
 *
 ****************************************************************************************
 */

#ifndef _DMA_API_AUD_H_
#define _DMA_API_AUD_H_

#include "reg_dma.h"
#include "dma_common.h"
#include "dma_generic.h"

typedef struct {
    uint32_t SAR;           /* Src Addr                     */
    uint32_t DAR;           /* Dest Addr                    */
    uint32_t TBL0CR;        /* Trans Blk Lvl-0 Cnt          */
    uint32_t TBL1CR;        /* Trans Blk Lvl-1 Cnt          */
    uint32_t TBL2CR;        /* Trans Blk Lvl-2 Cnt          */
    uint32_t TSR;           /* Trans Sz                     */
    uint32_t WMAR;          /* Wrp Match Addr               */
    uint32_t WJAR;          /* Wrp Jump Addr                */
    uint32_t LNAR;          /* Lli Node Addr(DWord Align)   */
    uint32_t TBL0SR;        /* Trans Blk Lvl-0 Sz           */
    uint32_t TBL1SSR;       /* Trans Blk Lvl-1 Src Sz       */
    uint32_t TBL1DSR;       /* Trans Blk Lvl-1 Dest Sz      */
} DMA_CX_DESC_T;

void dma_cx_common_irq_handler(uint8_t ch);
void dma_cx_handler_register(uint8_t ch, AIC_DMA_IRQ_HANDLER_T handler);
void dma_cx_halt_set(uint8_t ch, bool pause);
void dma_cx_enable_set(uint8_t ch, bool enable);
void dma_cx_request(uint8_t ch);
void dma_get_default_config(DMA_TYPE_ENUM type, DMA_CFG_T *cfg);
void dma_cx_config(uint8_t ch, DMA_CFG_T *cfg);
void dma_cx_desc_link(DMA_CFG_T *cfg, DMA_CX_DESC_T *desc, DMA_CX_DESC_T *next);
uint32_t dma_cx_get_periph_addr(DMA_CX_PERIPH_ENUM periph);
uint32_t dma_cx_get_addr_rd(uint8_t ch);
uint32_t dma_cx_get_addr_wr(uint8_t ch);
uint16_t dma_cx_get_lli_cntr(uint8_t ch);
void dma_cx_set_lli_cntr(uint8_t ch, uint16_t val);
void dma_cx_free(uint8_t ch);
void dma_cx_reg_dump(uint8_t ch);

#endif
