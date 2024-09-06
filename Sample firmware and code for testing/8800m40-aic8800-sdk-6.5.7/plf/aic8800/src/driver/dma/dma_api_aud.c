#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "dma_api_aud.h"
#include "chip.h"
#include "dbg.h"

#define USE_DEPRECATED_DMA_API 0

static AIC_DMA_IRQ_HANDLER_T dma_cx_irq_handler[DMA_CHANNEL_MAX];

static uint32_t dma_cx_periph_addr[DMA_CX_PERIPH_QTY] = {
    AIC_UART0_BASE,
    AIC_UART0_BASE,
    AIC_UART1_BASE,
    AIC_UART1_BASE,
    AIC_UART2_BASE,
    AIC_UART2_BASE,
    AIC_I2CM0_BASE + 0x0C,
    AIC_I2CM0_BASE + 0x10,
    AIC_SPI0_BASE,
    AIC_SPI0_BASE,
    AIC_SDMMC_BASE + 0x0C,
    AIC_SDMMC_BASE + 0x08,
    AIC_AUDPROC_BASE + (0x05 << 8) + (0x00 << 4),//AUD_PROC_RX01
    AIC_AUDPROC_BASE + (0x05 << 8) + (0x01 << 4),//AUD_PROC_RX23
    AIC_AUDPROC_BASE + (0x04 << 8) + (0x00 << 4),//AUD_PROC_TX0
    AIC_AUDPROC_BASE + (0x04 << 8) + (0x01 << 4),//AUD_PROC_TX1
    AIC_AUDPROC_BASE + (0x04 << 8) + (0x02 << 4),//AUD_PROC_TX2
    AIC_AUDPROC_BASE + (0x04 << 8) + (0x03 << 4),//AUD_PROC_TX3
    AIC_AUDPROC_BASE + (0x04 << 8) + (0x05 << 4),//AUD_PROC_RXTX0
    AIC_AUDPROC_BASE + (0x04 << 8) + (0x06 << 4),//AUD_PROC_RXTX1
    AIC_AUDPROC_BASE + (0x05 << 8) + (0x02 << 4),//AUD_PROC_TXRX0
    AIC_AUDPROC_BASE + (0x05 << 8) + (0x03 << 4),//AUD_PROC_TXRX1
    AIC_AUDPROC_BASE + (0x06 << 8) + (0x00 << 4),//AUD_SRC_TX
    AIC_AUDPROC_BASE + (0x06 << 8) + (0x02 << 4),//AUD_SRC_RX
};

void dma_cx_common_irq_handler(uint8_t ch)
{
    uint32_t int_status;

    /* Get int mask status */
    #if USE_DEPRECATED_DMA_API
    int_status = AIC_DMA->CH[ch].ICSR & DMA_CH_ALL_IMST_SET;
    #else
    int_status = AIC_DMA->CH[ch].ICSR & (DMA_CH_TBL0_IMST_BIT | DMA_CH_TBL1_IMST_BIT |
        DMA_CH_TBL2_IMST_BIT | DMA_CH_TLL_IMST_BIT | DMA_CH_CE_IMST_BIT);
    #endif

    if (int_status) {
        /* Clear all pending interrupts */
        #if USE_DEPRECATED_DMA_API
        AIC_DMA->CH[ch].ICSR |= (int_status << (DMA_CH_TBL0_ICLR_OFFSET - DMA_CH_TBL0_IMST_OFFSET));
        #else
        AIC_DMA->CH[ch].ICSR |= (int_status << (DMA_CH_TBL0_ICLR_POS - DMA_CH_TBL0_IMST_POS));
        #endif

        if (dma_cx_irq_handler[ch]) {
            dma_cx_irq_handler[ch](DMA_CX, ch, int_status);
        }
    }
}

void dma_cx_handler_register(uint8_t ch, AIC_DMA_IRQ_HANDLER_T handler)
{
    dma_cx_irq_handler[ch] = handler;
}

void dma_cx_halt_set(uint8_t ch, bool halt)
{
    //ASSERT(ch < DMA_CH_QTY, err_invalid_ch, ch);

#if USE_DEPRECATED_DMA_API
    if (halt) {
        AIC_DMA->CH[ch].HLTR |= DMA_CH_HALT_SET_SET;
    } else {
        AIC_DMA->CH[ch].HLTR &= ~DMA_CH_HALT_SET_SET;
    }
#else
    if (halt) {
        dma_ch_hltr_halt_set_setb(ch);
    } else {
        dma_ch_hltr_halt_set_clrb(ch);
    }
#endif
}

void dma_cx_enable_set(uint8_t ch, bool enable)
{
    //ASSERT(ch < DMA_CH_QTY, err_invalid_ch, ch);

#if USE_DEPRECATED_DMA_API
    if (enable) {
        AIC_DMA->CH[ch].CTLR |= DMA_CH_CHENA_SET;
    } else {
        AIC_DMA->CH[ch].CTLR &= ~DMA_CH_CHENA_SET;
    }
#else
    if (enable) {
        dma_ch_ctlr_chena_setb(ch);
    } else {
        dma_ch_ctlr_chena_clrb(ch);
    }
#endif
}

void dma_cx_request(uint8_t ch)
{
    //ASSERT(ch < DMA_CH_QTY, err_invalid_ch, ch);

#if USE_DEPRECATED_DMA_API
    AIC_DMA->CH[ch].RQR |= DMA_CH_SRQ_SET;
#else
    dma_ch_rqr_srq_setb(ch);
#endif
}

void dma_get_default_config(DMA_TYPE_ENUM type, DMA_CFG_T *cfg)
{
    cfg->dma_type = type;
    cfg->ch = DMA_CH_NONE;
    if (type == DMA_CX) {
        cfg->exreq_type = EXREQ_HIGH_LEVEL;
    } else {
        cfg->exreq_type = EXREQ_RISING_EDGE;
    }
    cfg->llist_en = false; //llist is disabled
    cfg->llist_cfg_valid = false; // current llist cfg invalid, DMA should obtain cfg from llist_ptr
    cfg->llist_end = false; //not the last llist
    cfg->priority = DMA_PRIO_LOWEST;
    cfg->ahb_burst_sel = AHB_BURST_INCR4;
#if USE_DEPRECATED_DMA_API
    if (type == DMA_CX) {
        cfg->int_mask  = DMA_CH_TBL2_IENA_SET | DMA_CH_CE_IENA_SET;
        //cfg->int_mask  = DMA_CH_TBL1_IENA_SET | DMA_CH_CE_IENA_SET;
    } else {
        cfg->int_mask  = DMA_CH_TBL1_IENA_SET | DMA_CH_CE_IENA_SET;
    }
#else
    if (type == DMA_CX) {
        cfg->int_mask  = DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT;
        //cfg->int_mask  = DMA_CH_TBL1_IENA_BIT | DMA_CH_CE_IENA_BIT;
    } else {
        cfg->int_mask  = DMA_CH_TBL1_IENA_BIT | DMA_CH_CE_IENA_BIT;
    }
#endif
    cfg->src_addr = DMA_INVALID_ADDR;
    cfg->dest_addr = DMA_INVALID_ADDR;
    cfg->tbl0_cnt = 4; //frag len should not be too long, 4 is recommended
    cfg->tbl1_cnt_rh = 0;
    cfg->tbl1_cnt = 0;
    cfg->tbl2_cnt = 0;
    cfg->src_tran_sz = 4; //src transfer step is related to src size, but should be 0 if src addr is fixed
    cfg->dest_tran_sz = 4; //dest transfer step is related to dest size, but should be 0 if dest addr is fixed
    cfg->wrp_maddr = 0;
    cfg->wrp_jaddr = 0;
    cfg->nxt_addr = 0;
    cfg->src_tbl0_sz = 0;
    cfg->dest_tbl0_sz = 0;
    cfg->src_tbl1_sz = 0;
    cfg->dest_tbl1_sz = 0;
    cfg->ext_req_cid = REQ_CID_MEMORY; //if trans from memory to memory, software request(set REQ[0] to 1) should be used
    cfg->llist_dedicated_int_en = false; //disable all interrupts(frag, blk, trsc, list) within the llist
    cfg->addr_fix_type = FIX_ON_NONE;
    cfg->addr_wrap_type = WRAP_ON_NONE;
    cfg->req_mode = REQ_TBL0; //request a fragment trans each time, 4 is recommended
    cfg->swt_mode = SWT_ABCD_ABCD;
    cfg->src_size = AHB_WORD;
    cfg->dest_size = AHB_WORD;
    cfg->handler = NULL;
    cfg->src_periph = DMA_MEMORY;
    cfg->dest_periph = DMA_MEMORY;
    cfg->trans_type = DMA_TRANS_M2M;
    cfg->ch_en = false;
}

void dma_cx_config(uint8_t ch, DMA_CFG_T *cfg)
{
    //ASSERT(ch < DMA_CH_QTY, err_invalid_ch, ch);

#if USE_DEPRECATED_DMA_API
    /* Channel Request Config */
    AIC_DMA->CH[ch].RQR = (cfg->exreq_type << DMA_CH_ERQM_OFFSET);
    /* Channel Request Config End */

    /* Channel Config */
    AIC_DMA->CH[ch].CTLR = (cfg->llist_en << DMA_CH_LSTENA_OFFSET) |
        (cfg->llist_cfg_valid << DMA_CH_LSTCV_OFFSET) |
        (cfg->priority << DMA_CH_RQPLVL_OFFSET) |
        (cfg->ahb_burst_sel << DMA_CH_BUSBU_OFFSET);
    /* Channel Config End */

    /* Interrupt Config */
    AIC_DMA->CH[ch].ICSR = cfg->int_mask;
    /* Interrupt Config End */

    AIC_DMA->CH[ch].SAR = cfg->src_addr;
    AIC_DMA->CH[ch].DAR = cfg->dest_addr;
    AIC_DMA->CH[ch].TBL0CR = (cfg->tbl0_cnt << DMA_CH_TBL0_CNT_OFFSET) |
        (((cfg->tbl1_cnt_rh & 0x18000) >> 15) << DMA_CH_TBL1_CNT_RH_OFFSET) |
        (cfg->llist_end << DMA_CH_LASTLLI_OFFSET) |
        ((cfg->addr_fix_type & FIX_ON_SRC) ? DMA_CH_CONSTSA_SET : 0) |
        ((cfg->addr_fix_type & FIX_ON_DEST) ? DMA_CH_CONSTDA_SET : 0) |
        ((cfg->addr_wrap_type & 0x01) ? DMA_CH_WRPADR_SET : 0) |
        ((cfg->addr_wrap_type & 0x02) ? DMA_CH_WRPDADR_SET : 0) |
        (cfg->req_mode << DMA_CH_RQTYP_OFFSET) |
        (cfg->swt_mode << DMA_CH_SWT_MODE_OFFSET) |
        (cfg->dest_size << DMA_CH_DBUSU_OFFSET) |
        (cfg->src_size << DMA_CH_SBUSU_OFFSET);
    AIC_DMA->CH[ch].TBL1CR = (cfg->tbl1_cnt << DMA_CH_TBL1_CNT_OFFSET) |
        ((cfg->tbl1_cnt_rh & 0x7FFF) << DMA_CH_TBL1_CNT_RL_OFFSET);
    AIC_DMA->CH[ch].TBL2CR = (cfg->tbl2_cnt << DMA_CH_TBL2_CNT_OFFSET) |
        (cfg->llist_dedicated_int_en << DMA_CH_LLI_DEDIC_INT_EN_OFFSET) |
        (1 << DMA_CH_LLI_DEDIC_COUNT_EN_OFFSET); //Enable ch lli node counter
    AIC_DMA->CH[ch].TSR = (cfg->src_tran_sz << DMA_CH_STRANSZ_OFFSET) |
        (cfg->dest_tran_sz << DMA_CH_DTRANSZ_OFFSET);
    AIC_DMA->CH[ch].WMAR = cfg->wrp_maddr << DMA_CH_WRPMADR_OFFSET;
    AIC_DMA->CH[ch].WJAR = cfg->wrp_jaddr << DMA_CH_WRPJADR_OFFSET;
    AIC_DMA->CH[ch].LNAR = cfg->nxt_addr << DMA_CH_LLINADR_OFFSET;
    AIC_DMA->CH[ch].TBL0SR = (cfg->src_tbl0_sz << DMA_CH_STBL0SZ_OFFSET) |
        (cfg->dest_tbl0_sz << DMA_CH_DTBL0SZ_OFFSET);
    AIC_DMA->CH[ch].TBL1SSR = cfg->src_tbl1_sz << DMA_CH_TBL1_SSZ_OFFSET;
    AIC_DMA->CH[ch].TBL1DSR = cfg->dest_tbl1_sz << DMA_CH_TBL1_DSZ_OFFSET;

    /* In REQ_CID, Channel Count From 1 */
    if (cfg->ext_req_cid < REQ_CID_QTY) {
        AIC_DMA->ERQCSR[cfg->ext_req_cid] = ch + 1;
    }

    dma_cx_irq_handler[ch] = cfg->handler;

    /* In the end, enable DMA as required */
    if (cfg->ch_en) {
        AIC_DMA->CH[ch].CTLR |= DMA_CH_CHENA_SET;
    }
#else
    /* Channel Request Config */
    AIC_DMA->CH[ch].RQR = (cfg->exreq_type << DMA_CH_ERQM_POS);
    /* Channel Request Config End */

    /* Channel Config */
    AIC_DMA->CH[ch].CTLR = (cfg->llist_en << DMA_CH_LSTENA_POS) |
        (cfg->llist_cfg_valid << DMA_CH_LSTCV_POS) |
        (cfg->priority << DMA_CH_RQPLVL_LSB) |
        (cfg->ahb_burst_sel << DMA_CH_BUSBU_LSB);
    /* Channel Config End */

    /* Interrupt Config */
    AIC_DMA->CH[ch].ICSR = cfg->int_mask;
    /* Interrupt Config End */

    AIC_DMA->CH[ch].SAR = cfg->src_addr;
    AIC_DMA->CH[ch].DAR = cfg->dest_addr;
    AIC_DMA->CH[ch].TBL0CR = (cfg->tbl0_cnt << DMA_CH_TBL0_CNT_LSB) |
        (((cfg->tbl1_cnt_rh & 0x18000) >> 15) << DMA_CH_TBL1_CNT_RH_LSB) |
        (cfg->llist_end << DMA_CH_LASTLLI_POS) |
        ((cfg->addr_fix_type & FIX_ON_SRC) ? DMA_CH_CONSTSA_BIT : 0) |
        ((cfg->addr_fix_type & FIX_ON_DEST) ? DMA_CH_CONSTDA_BIT : 0) |
        ((cfg->addr_wrap_type & 0x01) ? DMA_CH_WRPADR_BIT : 0) |
        ((cfg->addr_wrap_type & 0x02) ? DMA_CH_WRPDADR_BIT : 0) |
        (cfg->req_mode << DMA_CH_RQTYP_LSB) |
        (cfg->swt_mode << DMA_CH_SWT_MODE_LSB) |
        (cfg->dest_size << DMA_CH_DBUSU_LSB) |
        (cfg->src_size << DMA_CH_SBUSU_LSB);
    AIC_DMA->CH[ch].TBL1CR = (cfg->tbl1_cnt << DMA_CH_TBL1_CNT_LSB) |
        ((cfg->tbl1_cnt_rh & 0x7FFF) << DMA_CH_TBL1_CNT_RL_LSB);
    AIC_DMA->CH[ch].TBL2CR = (cfg->tbl2_cnt << DMA_CH_TBL2_CNT_LSB) |
        (cfg->llist_dedicated_int_en << DMA_CH_LLI_DEDIC_INT_EN_POS) |
        (1 << DMA_CH_LLI_DEDIC_COUNTER_EN_POS); //Enable ch lli node counter
    AIC_DMA->CH[ch].TSR = (cfg->src_tran_sz << DMA_CH_STRANSZ_LSB) |
        (cfg->dest_tran_sz << DMA_CH_DTRANSZ_LSB);
    AIC_DMA->CH[ch].WMAR = cfg->wrp_maddr << DMA_CH_WRPMADR_LSB;
    AIC_DMA->CH[ch].WJAR = cfg->wrp_jaddr << DMA_CH_WRPJADR_LSB;
    AIC_DMA->CH[ch].LNAR = cfg->nxt_addr << DMA_CH_LLINADR_LSB;
    AIC_DMA->CH[ch].TBL0SR = (cfg->src_tbl0_sz << DMA_CH_STBL0SZ_LSB) |
        (cfg->dest_tbl0_sz << DMA_CH_DTBL0SZ_LSB);
    AIC_DMA->CH[ch].TBL1SSR = cfg->src_tbl1_sz << DMA_CH_TBL1_SSZ_LSB;
    AIC_DMA->CH[ch].TBL1DSR = cfg->dest_tbl1_sz << DMA_CH_TBL1_DSZ_LSB;

    /* In REQ_CID, Channel Count From 1 */
    if (cfg->ext_req_cid < REQ_CID_QTY) {
        AIC_DMA->ERQCSR[cfg->ext_req_cid] = ch + 1;
    }

    dma_cx_irq_handler[ch] = cfg->handler;

    /* In the end, enable DMA as required */
    if (cfg->ch_en) {
        dma_ch_ctlr_chena_setb(ch);
    }
#endif
}

void dma_cx_desc_link(DMA_CFG_T *cfg, DMA_CX_DESC_T *desc, DMA_CX_DESC_T *next)
{
#if USE_DEPRECATED_DMA_API
    desc->SAR = cfg->src_addr;
    desc->DAR = cfg->dest_addr;
    desc->TBL0CR = (cfg->tbl0_cnt << DMA_CH_TBL0_CNT_OFFSET) |
        (((cfg->tbl1_cnt_rh & 0x18000) >> 15) << DMA_CH_TBL1_CNT_RH_OFFSET) |
        (cfg->llist_end << DMA_CH_LASTLLI_OFFSET) |
        ((cfg->addr_fix_type & FIX_ON_SRC) ? DMA_CH_CONSTSA_SET : 0) |
        ((cfg->addr_fix_type & FIX_ON_DEST) ? DMA_CH_CONSTDA_SET : 0) |
        ((cfg->addr_wrap_type & 0x01) ? DMA_CH_WRPADR_SET : 0) |
        ((cfg->addr_wrap_type & 0x02) ? DMA_CH_WRPDADR_SET : 0) |
        (cfg->req_mode << DMA_CH_RQTYP_OFFSET) |
        (cfg->swt_mode << DMA_CH_SWT_MODE_OFFSET) |
        (cfg->dest_size << DMA_CH_DBUSU_OFFSET) |
        (cfg->src_size << DMA_CH_SBUSU_OFFSET);
    desc->TBL1CR = (cfg->tbl1_cnt << DMA_CH_TBL1_CNT_OFFSET) |
        ((cfg->tbl1_cnt_rh & 0x7FFF) << DMA_CH_TBL1_CNT_RL_OFFSET);
    desc->TBL2CR = (cfg->tbl2_cnt << DMA_CH_TBL2_CNT_OFFSET) |
        (cfg->llist_dedicated_int_en << DMA_CH_LLI_DEDIC_INT_EN_OFFSET) |
        (1 << DMA_CH_LLI_DEDIC_COUNT_EN_OFFSET); //Enable ch lli node counter
    desc->TSR = (cfg->src_tran_sz << DMA_CH_STRANSZ_OFFSET) |
        (cfg->dest_tran_sz << DMA_CH_DTRANSZ_OFFSET);
    desc->WMAR = cfg->wrp_maddr << DMA_CH_WRPMADR_OFFSET;
    desc->WJAR = cfg->wrp_jaddr << DMA_CH_WRPJADR_OFFSET;
    //lli->LNAR = cfg->llist_ptr << DMA_CH_LLINADR_OFFSET;
    desc->LNAR = (uint32_t)next;
    desc->TBL0SR = (cfg->src_tbl0_sz << DMA_CH_STBL0SZ_OFFSET) |
        (cfg->dest_tbl0_sz << DMA_CH_DTBL0SZ_OFFSET);
    desc->TBL1SSR = cfg->src_tbl1_sz << DMA_CH_TBL1_SSZ_OFFSET;
    desc->TBL1DSR = cfg->dest_tbl1_sz << DMA_CH_TBL1_DSZ_OFFSET;

    if (NULL == next) {
        desc->TBL0CR |= DMA_CH_LASTLLI_SET;
    } else {
        desc->TBL0CR &= ~DMA_CH_LASTLLI_SET;
    }
#else
    desc->SAR = cfg->src_addr;
    desc->DAR = cfg->dest_addr;
    desc->TBL0CR = (cfg->tbl0_cnt << DMA_CH_TBL0_CNT_LSB) |
        (((cfg->tbl1_cnt_rh & 0x18000) >> 15) << DMA_CH_TBL1_CNT_RH_LSB) |
        (cfg->llist_end << DMA_CH_LASTLLI_POS) |
        ((cfg->addr_fix_type & FIX_ON_SRC) ? DMA_CH_CONSTSA_BIT : 0) |
        ((cfg->addr_fix_type & FIX_ON_DEST) ? DMA_CH_CONSTDA_BIT : 0) |
        ((cfg->addr_wrap_type & 0x01) ? DMA_CH_WRPADR_BIT : 0) |
        ((cfg->addr_wrap_type & 0x02) ? DMA_CH_WRPDADR_BIT : 0) |
        (cfg->req_mode << DMA_CH_RQTYP_LSB) |
        (cfg->swt_mode << DMA_CH_SWT_MODE_LSB) |
        (cfg->dest_size << DMA_CH_DBUSU_LSB) |
        (cfg->src_size << DMA_CH_SBUSU_LSB);
    desc->TBL1CR = (cfg->tbl1_cnt << DMA_CH_TBL1_CNT_LSB) |
        ((cfg->tbl1_cnt_rh & 0x7FFF) << DMA_CH_TBL1_CNT_RL_LSB);
    desc->TBL2CR = (cfg->tbl2_cnt << DMA_CH_TBL2_CNT_LSB) |
        (cfg->llist_dedicated_int_en << DMA_CH_LLI_DEDIC_INT_EN_POS) |
        (1 << DMA_CH_LLI_DEDIC_COUNTER_EN_POS); //Enable ch lli node counter
    desc->TSR = (cfg->src_tran_sz << DMA_CH_STRANSZ_LSB) |
        (cfg->dest_tran_sz << DMA_CH_DTRANSZ_LSB);
    desc->WMAR = cfg->wrp_maddr << DMA_CH_WRPMADR_LSB;
    desc->WJAR = cfg->wrp_jaddr << DMA_CH_WRPJADR_LSB;
    //lli->LNAR = cfg->llist_ptr << DMA_CH_LLINADR_LSB;
    desc->LNAR = (uint32_t)next;
    desc->TBL0SR = (cfg->src_tbl0_sz << DMA_CH_STBL0SZ_LSB) |
        (cfg->dest_tbl0_sz << DMA_CH_DTBL0SZ_LSB);
    desc->TBL1SSR = cfg->src_tbl1_sz << DMA_CH_TBL1_SSZ_LSB;
    desc->TBL1DSR = cfg->dest_tbl1_sz << DMA_CH_TBL1_DSZ_LSB;

    if (NULL == next) {
        desc->TBL0CR |= DMA_CH_LASTLLI_BIT;
    } else {
        desc->TBL0CR &= ~DMA_CH_LASTLLI_BIT;
    }
#endif
}

uint32_t dma_cx_get_periph_addr(DMA_CX_PERIPH_ENUM periph)
{
    return dma_cx_periph_addr[periph];
}

uint32_t dma_cx_get_addr_rd(uint8_t ch)
{
    return AIC_DMA->CH_ADDR[ch].RDMR;
}

uint32_t dma_cx_get_addr_wr(uint8_t ch)
{
    return AIC_DMA->CH_ADDR[ch].WRMR;
}

uint16_t dma_cx_get_lli_cntr(uint8_t ch)
{
    return (AIC_DMA->LLINCR[ch] & 0xFFFF);
}

void dma_cx_set_lli_cntr(uint8_t ch, uint16_t val)
{
    AIC_DMA->LLINCR[ch] = (AIC_DMA->LLINCR[ch] & (~0xFFFF)) | val;
}

void dma_cx_free(uint8_t ch)
{
#if USE_DEPRECATED_DMA_API
    AIC_DMA->CH[ch].CTLR &= ~DMA_CH_CHENA_SET;
    AIC_DMA->CH[ch].ICSR &= ~DMA_CH_ALL_IENA_SET;
    AIC_DMA->CH[ch].ICSR |= DMA_CH_ALL_ICLR_SET;
#else
    dma_ch_ctlr_chena_clrb(ch);
    AIC_DMA->CH[ch].ICSR &= ~(DMA_CH_TBL0_IENA_BIT | DMA_CH_TBL1_IENA_BIT |
        DMA_CH_TBL2_IENA_BIT | DMA_CH_TLL_IENA_BIT | DMA_CH_CE_IENA_BIT);
    AIC_DMA->CH[ch].ICSR |= (DMA_CH_TBL0_ICLR_BIT | DMA_CH_TBL1_ICLR_BIT |
        DMA_CH_TBL2_ICLR_BIT | DMA_CH_TLL_ICLR_BIT | DMA_CH_CE_ICLR_BIT);
#endif

    /* If DMA channel was bound with any peripheral, unbind it */
    for (int i = 0; i < REQ_CID_QTY; i++) {
        if ((ch + 1) == AIC_DMA->ERQCSR[i]) {
            AIC_DMA->ERQCSR[i] = 0;
        }
    }
}

void dma_cx_reg_dump(uint8_t ch)
{
    dbg("aic_dma_reg_dump: ch %d", ch);
    dbg("HLTR:%X", AIC_DMA->CH[ch].HLTR);
    dbg("RQR:%X", AIC_DMA->CH[ch].RQR);
    dbg("CTLR:%X", AIC_DMA->CH[ch].CTLR);
    dbg("ICSR:%X", AIC_DMA->CH[ch].ICSR);
    dbg("SAR:%X", AIC_DMA->CH[ch].SAR);
    dbg("DAR:%X", AIC_DMA->CH[ch].DAR);
    dbg("TBL0R:%X", AIC_DMA->CH[ch].TBL0CR);
    dbg("TBL1R:%X", AIC_DMA->CH[ch].TBL1CR);
    dbg("TBL2R:%X", AIC_DMA->CH[ch].TBL2CR);
    dbg("TSR:%X", AIC_DMA->CH[ch].TSR);
    dbg("WMAR:%X", AIC_DMA->CH[ch].WMAR);
    dbg("WJAR:%X", AIC_DMA->CH[ch].WJAR);
    dbg("LNAR:%X", AIC_DMA->CH[ch].LNAR);
    dbg("TBL0SR:%X", AIC_DMA->CH[ch].TBL0SR);
    dbg("TBL1SSR:%X", AIC_DMA->CH[ch].TBL1SSR);
    dbg("TBL1DSR:%X", AIC_DMA->CH[ch].TBL1DSR);
    for (int i = 0; i < REQ_CID_QTY; i++) {
        dbg("ERQCSR[%d]:%d", i, AIC_DMA->ERQCSR[i]);
    }
}

