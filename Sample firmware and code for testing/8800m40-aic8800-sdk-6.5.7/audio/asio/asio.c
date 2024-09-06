#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "plf.h"
#include "rtos.h"
#include "dbg.h"
#include "dbg_assert.h"
#include "asio.h"
#include "asio_src.h"
#include "aud_proc.h"
#include "codec_tlv320aic32.h"
#include "reg_iomux.h"
#include "reg_sysctrl.h"
#include "sysctrl_api.h"
#include "gpio_api.h"
#if PLF_PMIC
#include "pmic_api.h"
#if (PLF_PMIC_VER_AUD || PLF_EXT_AIC1000)
#include "codec_aic1000.h"
#endif
#endif
#include "audio_config.h"
#include "audio_proc_api.h"

#define ASIO_TRACE(fmt, ...)    dbg(fmt, ##__VA_ARGS__)

#define AUDIO_PXP 0

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

static void asio_stream0_playback_dma_irq_handler(void);
static void asio_stream0_capture_dma_irq_handler(void);
static void asio_stream1_playback_dma_irq_handler(void);
static void asio_stream1_capture_dma_irq_handler(void);

static rtos_mutex asio_mutex = NULL;
static rtos_task_handle asio_task_handle = NULL;

__attribute__((aligned(8))) static DMA_CX_DESC_T asio_dma_cx_desc[AUD_STREAM_GROUP_NUM][AUD_STREAM_NUM][2];//DWORD align
static ASIO_STREAM_ENTITY_T asio_entity[AUD_STREAM_GROUP_NUM][AUD_STREAM_NUM];

static bool aud_path_opened[AUD_PATH_NUM];
static bool aud_device_opened[AUD_DEVICE_NUM][AUD_STREAM_NUM];

static const uint8_t asio_dma_ch[AUD_STREAM_GROUP_NUM][AUD_STREAM_NUM] = {
    {DMA_CHANNEL_AUD_STREAM0_PLAYBACK, DMA_CHANNEL_AUD_STREAM0_CAPTURE},
    {DMA_CHANNEL_AUD_STREAM1_PLAYBACK, DMA_CHANNEL_AUD_STREAM1_CAPTURE},
};

static const uint8_t asio_dma_irqn[AUD_STREAM_GROUP_NUM][AUD_STREAM_NUM] = {
    {DMA00_IRQn + DMA_CHANNEL_AUD_STREAM0_PLAYBACK, DMA00_IRQn + DMA_CHANNEL_AUD_STREAM0_CAPTURE},
    {DMA00_IRQn + DMA_CHANNEL_AUD_STREAM1_PLAYBACK, DMA00_IRQn + DMA_CHANNEL_AUD_STREAM1_CAPTURE},
};

static const uint32_t asio_dma_irq_handler[AUD_STREAM_GROUP_NUM][AUD_STREAM_NUM] = {
    {(uint32_t)asio_stream0_playback_dma_irq_handler, (uint32_t)asio_stream0_capture_dma_irq_handler},
    {(uint32_t)asio_stream1_playback_dma_irq_handler, (uint32_t)asio_stream1_capture_dma_irq_handler},
};

#if (PLF_PMIC && (PLF_PMIC_VER_AUD || PLF_EXT_AIC1000))
static bool aic1000_inited = false;
static aic1000_cfg_t aic1000_dac_cfg;
#if PLF_PMIC_VER_AUD
static aic1000_cfg_t aic1000_adc_cfg[2];
#else
static aic1000_cfg_t aic1000_adc_cfg;
static uint8_t aic1000_i2s_idx = 0;
#endif
#endif

#if AUDIO_CFG_TLV320AIC32_UESD
#if (AUDIO_PXP == 0)
static bool tlv320aic32_inited = false;
#else
static bool tlv320aic32_inited = true;
#endif
#endif

static bool asio_inited = false;
static bool asio_stream_handler_running[AUD_STREAM_GROUP_NUM][AUD_STREAM_NUM] =
{
    {false, false},
    {false, false}
};

static const uint8_t dac_mixer_mode[5] = {
    0x00,// left: left channel data
    0x01,// mute: mute
    0x02,// right: right channel data
    0x03,// lprd2: (left channel + right channel) / 2
    0x04,// lmrd2: (left channel - right channel) / 2
};

#if PLF_PMIC
#if PLF_PMIC_VER_AUD
void aic1000_int_init(void)
{
    aic1000_iomux_config();
    aic1000_clk_cfg();
    aic1000_ana_cfg();
#if PLF_AIC1000_MIC_MATRIX
    aic1000_mic_matix_config(PLF_AIC1000_MIC_MATRIX);
#endif
}
#endif
#if (!PLF_PMIC_VER_AUD && PLF_EXT_AIC1000)
void aic1000_ext_init(void)
{
    if (aic1000_i2s_idx == 0) {
        audio_proc_i2s0_iomux_config();
    } else {
        audio_proc_i2s1_iomux_config();
    }
    aic1000_pu();
    aic1000_wait_pu_done(5);
    aic1000_pu_done();
    aic1000_clk_cfg();
    aic1000_iomux_config();
    aic1000_ana_cfg();
#if PLF_AIC1000_MIC_MATRIX
    aic1000_mic_matix_config(PLF_AIC1000_MIC_MATRIX);
#endif
    aic1000_adc_mic_signal_mode_config(AIC1000_MIC_DIFF_MODE);
}
#endif
#endif

void asio_task_lock(void)
{
    rtos_mutex_lock(asio_mutex, -1);
}

void asio_task_unlock(void)
{
    rtos_mutex_unlock(asio_mutex);
}

void asio_stream_handler_running_set(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream, bool running)
{
    asio_stream_handler_running[group][stream] = running;
}

bool asio_stream_handler_running_get(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    return asio_stream_handler_running[group][stream];
}

static inline ASIO_STREAM_ENTITY_T *asio_stream_entity_get(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    ASSERT_ERR(group < AUD_STREAM_GROUP_NUM);
    ASSERT_ERR(stream < AUD_STREAM_NUM);

    return &asio_entity[group][stream];
}

static void asio_stream_status_set(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream, ASIO_STATUS_T status)
{
    ASIO_STREAM_ENTITY_T *entity = NULL;

    entity = asio_stream_entity_get(group, stream);

    entity->ctl.status |= status;
}

static void asio_stream_status_clear(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream, ASIO_STATUS_T status)
{
    ASIO_STREAM_ENTITY_T *entity = NULL;

    entity = asio_stream_entity_get(group, stream);

    entity->ctl.status &= ~status;
}

static inline void asio_stream_handler(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    uint32_t protect;
    ASIO_STREAM_ENTITY_T *entity;
    uint32_t lli_cntr;//link list counter
    uint8_t *buf;
    uint8_t pp_cnt;
    ASIO_PP_T pp_index;

    entity = asio_stream_entity_get(group, stream);

    asio_task_lock();

    if (entity->handler && (entity->ctl.status & ASIO_STATUS_STREAM_START)) {
        protect = rtos_protect();
        pp_cnt = entity->ctl.pp_cnt;
        entity->ctl.pp_cnt = 0;
        rtos_unprotect(protect);

        if (pp_cnt > 1) {
            ASIO_TRACE("asio: %d %d lost %u\n", group, stream, (pp_cnt - 1));
        }

        lli_cntr = asio_stream_current_dma_lli_cntr_get(group, stream);
        {
            if (lli_cntr & 0x01) {
                pp_index = ASIO_PP_PING;
            } else {
                pp_index = ASIO_PP_PANG;
            }

            if (pp_index == ASIO_PP_PING) {
                buf = entity->dma_buf_ptr;
            } else {
                buf = entity->dma_buf_ptr + entity->dma_buf_size / 2;
            }
        }

        if (entity->handler) {
            entity->handler(buf, entity->dma_buf_size / 2);
        }

        if (entity->ctl.pp_cnt) {
            ASIO_TRACE("asio: %d %d timeout (%u)\n", group, stream, entity->ctl.pp_cnt);
        }
    }

    asio_task_unlock();
}

static void asio_dma_irq_callback(uint8_t dma_type, uint8_t ch, uint32_t int_status)
{
    ASIO_STREAM_ENTITY_T *entity = NULL;

    //ASIO_TRACE("asio:c%d %d\n", ch, rtos_now(true));

    for (int group = 0; group < AUD_STREAM_GROUP_NUM; group++) {
        for (int stream = 0; stream < AUD_STREAM_NUM; stream++) {
            entity = asio_stream_entity_get((AUD_STREAM_GROUP_T)group, (AUD_STREAM_T)stream);

            if (entity->dma_cfg.ch == ch) {
                //uint32_t lli_cntr = asio_stream_current_dma_lli_cntr_get(group, stream);
                //ASIO_TRACE("ch:%d lli:0x%X\n", ch, lli_cntr);

                entity->ctl.pp_index = ASIO_PP_NEXT(entity->ctl.pp_index);
                entity->ctl.pp_cnt++;
                rtos_task_notify_setbits(asio_task_handle, (0x01UL << (group * AUD_STREAM_NUM + stream)), true);
                return;
            }
        }
    }
}


static RTOS_TASK_FCT(asio_task_routine)
{
    uint32_t notification = 0;
    AUD_STREAM_GROUP_T group;
    AUD_STREAM_T stream;

    //rtos_task_handle current_handle = rtos_get_task_handle();
    //ASIO_TRACE("current_handle:%p\n", current_handle);

    // Initialize external codec in advance to reduce execution time of asio_stream_open
#if AUDIO_CFG_TLV320AIC32_UESD
    if (!tlv320aic32_inited) {
        #if (AUDIO_PXP == 0)
        tlv320aic32_init();
        #endif
        tlv320aic32_inited = true;
    }
#endif

    while (1) {
        notification = rtos_task_wait_notification(-1);
        //ASIO_TRACE("n:0x%X\n", notification);
        for (uint8_t i = 0; i < AUD_STREAM_GROUP_NUM * AUD_STREAM_NUM; i++) {
            if (notification & (1 << i)) {
                group = (AUD_STREAM_GROUP_T)(i >> 1);
                stream = (AUD_STREAM_T)(i & 1);

                asio_stream_handler_running_set(group, stream, true);
                asio_stream_handler(group, stream);
                asio_stream_handler_running_set(group, stream, false);
            }
        }
    }
}

static void asio_stream0_playback_dma_irq_handler(void)
{
    dma_cx_common_irq_handler(asio_dma_ch[AUD_STREAM_GROUP_0][AUD_STREAM_PLAYBACK]);
}

static void asio_stream0_capture_dma_irq_handler(void)
{
    dma_cx_common_irq_handler(asio_dma_ch[AUD_STREAM_GROUP_0][AUD_STREAM_CAPTURE]);
}

static void asio_stream1_playback_dma_irq_handler(void)
{
    dma_cx_common_irq_handler(asio_dma_ch[AUD_STREAM_GROUP_1][AUD_STREAM_PLAYBACK]);
}

static void asio_stream1_capture_dma_irq_handler(void)
{
    dma_cx_common_irq_handler(asio_dma_ch[AUD_STREAM_GROUP_1][AUD_STREAM_CAPTURE]);
}

int asio_open(void)
{
    ASIO_TRACE("%s\n", __func__);

    int res = 0;
    ASIO_STREAM_ENTITY_T *entity = NULL;

    if (NULL == asio_mutex) {
        res = rtos_mutex_create(&asio_mutex);
        if (0 != res) {
            return ASIO_ERR_FAIL;
        }
    }

    //ASIO_TRACE("asio_mutex:%p\n", asio_mutex);

    for (int group = 0; group < AUD_STREAM_GROUP_NUM; group++) {
        for (int stream = 0; stream < AUD_STREAM_NUM; stream++) {
            entity = asio_stream_entity_get((AUD_STREAM_GROUP_T)group, (AUD_STREAM_T)stream);

            //No need to memset to 0 cause asio_entity is located at bss section
            //memset(entity, 0, sizeof(ASIO_STREAM_ENTITY_T));

            entity->handler = NULL;
            entity->dma_buf_ptr = NULL;
            entity->dma_buf_size = 0;
            entity->dma_cx_desc[0] = &asio_dma_cx_desc[group][stream][0];
            entity->dma_cx_desc[1] = &asio_dma_cx_desc[group][stream][1];
            entity->ctl.pp_index = ASIO_PP_PING;
            entity->ctl.pp_cnt = 0;
            entity->ctl.status = ASIO_STATUS_ASIO_OPEN;
            entity->ctl.device = AUD_DEVICE_NONE;
            entity->ctl.path = AUD_PATH_NONE;
            entity->dma_cfg.ch = DMA_CH_NONE;
        }
    }

    res = rtos_task_create(asio_task_routine, "ASIO", ASIO_TASK,
                         TASK_STACK_SIZE_ASIO, NULL, TASK_PRIORITY_ASIO, &asio_task_handle);
    if (0 != res) {
        return ASIO_ERR_FAIL;
    }

    //ASIO_TRACE("asio_task_handle:%p\n", asio_task_handle);

    return ASIO_ERR_NONE;
}

void asio_stream_update_dma_config(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream, const ASIO_STREAM_CFG_T *cfg)
{
    //ASIO_TRACE("%s\n", __func__);

    ASIO_STREAM_ENTITY_T *entity;
    void *dma_desc, *next_desc;
    DMA_CFG_T *dma_cfg;
    uint32_t desc_trans_size = 0;

    entity = asio_stream_entity_get(group, stream);

    entity->dma_buf_ptr = cfg->buf_ptr;
    entity->dma_buf_size = cfg->buf_size;

    dma_cfg = &entity->dma_cfg;

    if (stream == AUD_STREAM_PLAYBACK) {
#if 1
        if (cfg->path == AUD_PATH_TX01) {
            dma_cfg->dest_periph = DMA_AUD_PROC_TX0;
            dma_cfg->ext_req_cid = REQ_CID_AUD_PROC_TX0;
        } else if (cfg->path == AUD_PATH_TX23) {
            dma_cfg->dest_periph = DMA_AUD_PROC_TX2;
            dma_cfg->ext_req_cid = REQ_CID_AUD_PROC_TX2;
        } else {
            ASSERT_ERR(0);
        }
#endif

        dma_cfg->dest_addr = dma_cx_get_periph_addr(dma_cfg->dest_periph);
        dma_cfg->dest_size = AHB_WORD;
        dma_cfg->addr_fix_type = FIX_ON_DEST;
        dma_cfg->dest_tran_sz = 0;
        switch (cfg->bits) {
            case AUD_BITS_16:
                dma_cfg->src_size = AHB_HWORD;
                dma_cfg->src_tran_sz = 2;
                break;
            case AUD_BITS_24:
                dma_cfg->src_size = AHB_WORD;
                dma_cfg->src_tran_sz = 4;
                break;
            default:
                dma_cfg->src_size = AHB_BYTE;
                dma_cfg->src_tran_sz = 1;
                break;
        }
    } else {
#if 1
        if (cfg->path == AUD_PATH_RX01) {
            if (cfg->src_en) {
                #if PLF_AIC8800 || PLF_AIC8800M40
                dma_cfg->src_periph = DMA_AUD_SRC_RX;
                dma_cfg->ext_req_cid = REQ_CID_AUD_SRC_RX;
                #elif PLF_AIC8800MC
                dma_cfg->src_periph = DMA_AUD_PROC_RX01;
                dma_cfg->ext_req_cid = REQ_CID_AUD_PROC_RX01;
                #endif
            } else {
                dma_cfg->src_periph = DMA_AUD_PROC_RX01;
                dma_cfg->ext_req_cid = REQ_CID_AUD_PROC_RX01;
            }
        } else if (cfg->path == AUD_PATH_RX23) {
            dma_cfg->src_periph = DMA_AUD_PROC_RX23;
            dma_cfg->ext_req_cid = REQ_CID_AUD_PROC_RX23;
        } else {
            ASSERT_ERR(0);
        }
#endif

        dma_cfg->src_addr = dma_cx_get_periph_addr(dma_cfg->src_periph);
        dma_cfg->src_size = AHB_WORD;
        dma_cfg->addr_fix_type = FIX_ON_SRC;
        dma_cfg->src_tran_sz = 0;
        switch (cfg->bits) {
            case AUD_BITS_16:
                dma_cfg->dest_size = AHB_HWORD;
                dma_cfg->dest_tran_sz = 2;
                break;
            case AUD_BITS_24:
                dma_cfg->dest_size = AHB_WORD;
                dma_cfg->dest_tran_sz = 4;
                break;
            default:
                dma_cfg->dest_size = AHB_BYTE;
                dma_cfg->dest_tran_sz = 1;
                break;
        }
    }

    dma_desc = entity->dma_cx_desc[0];

    desc_trans_size = cfg->buf_size / 2;

    /* all dma link list were linked as a closed chain */
    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            next_desc = entity->dma_cx_desc[0];
        } else {
            next_desc = entity->dma_cx_desc[i + 1];
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            dma_cfg->src_addr = (uint32_t)entity->dma_buf_ptr + i * desc_trans_size;
        } else {
            dma_cfg->dest_addr = (uint32_t)entity->dma_buf_ptr + i * desc_trans_size;
        }

        dma_cfg->tbl2_cnt = desc_trans_size;
        dma_cfg->tbl1_cnt = dma_cfg->tbl2_cnt;//set block length equal to transaction length
        dma_cfg->llist_dedicated_int_en = true;

        dma_cx_desc_link(dma_cfg, (DMA_CX_DESC_T *)dma_desc, (DMA_CX_DESC_T *)next_desc);

        dma_desc = next_desc;
    }

    /* Reset src_addr and dest_addr */
    if (stream == AUD_STREAM_PLAYBACK) {
        dma_cfg->src_addr = (uint32_t)entity->dma_buf_ptr;
    } else {
        dma_cfg->dest_addr = (uint32_t)entity->dma_buf_ptr;
    }

    dma_cfg->llist_en = true;

#if 1
    /* force dma to load config from llist_ptr */
    dma_cfg->llist_cfg_valid = false;

    /* llist_ptr point to the 1st dma descriptor */
    dma_cfg->nxt_addr = (uint32_t)entity->dma_cx_desc[0];
#else
    /* use current register config */
    dma_cfg->llist_cfg_valid = true;

    /* llist_ptr point to the 1st dma descriptor */
    dma_cfg->nxt_addr = (uint32_t)entity->dma_cx_desc[1];
#endif

    dma_cx_config(dma_cfg->ch, dma_cfg);

#if 0
    for (int i = 0; i < 2; i++) {
        ASIO_TRACE("SAR:0x%X\n", entity->dma_cx_desc[i]->SAR);
        ASIO_TRACE("DAR:0x%X\n", entity->dma_cx_desc[i]->DAR);
        ASIO_TRACE("TBL1CR:0x%X\n", entity->dma_cx_desc[i]->TBL1CR);
        ASIO_TRACE("LNAR:0x%X\n", entity->dma_cx_desc[i]->LNAR);
    }
#endif
}

int asio_stream_open(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream, const ASIO_STREAM_CFG_T *cfg)
{
    ASIO_TRACE("%s g:%d s:%d\n", __func__, group, stream);

    ASIO_STREAM_ENTITY_T *entity;
    ASIO_ERR_T res;
    AUD_DEVICE_T device;
    AUD_PATH_T path;
    DMA_CFG_T *dma_cfg = NULL;

    entity = asio_stream_entity_get(group, stream);

    ASSERT_ERR(cfg->buf_ptr != NULL);
    ASSERT_ERR(((uint32_t)(cfg->buf_ptr) % 4) == 0);
    ASSERT_ERR(cfg->buf_size != 0);

    asio_task_lock();

    // check if asio is already opened
    if (entity->ctl.status != ASIO_STATUS_ASIO_OPEN) {
        ASIO_TRACE("ERROR: %s, status:%d\n", __func__, entity->ctl.status);
        res = ASIO_ERR_FAIL;
        goto exit;
    }

    entity->cfg = *cfg;

    device = cfg->device;
    entity->ctl.device = device;

    path = cfg->path;
    entity->ctl.path = path;

    ASSERT_ERR(device < AUD_DEVICE_NUM);
    ASSERT_ERR(path < AUD_PATH_NUM);

    dma_cfg = &entity->dma_cfg;
    memset(dma_cfg, 0, sizeof(*dma_cfg));

    #if PLF_AIC8800MC
    if (device == AUD_DEVICE_I2S0 || device == AUD_DEVICE_EXT_CODEC_I2S0) {
        if ((path != AUD_PATH_TX01) && (path != AUD_PATH_RX01)) {
            TRACE("ERROR: 8800MC I2S0 must match with TX01/RX01");
            ASSERT_ERR(0);
        }
    }
    if (device == AUD_DEVICE_I2S1 || device == AUD_DEVICE_EXT_CODEC_I2S1) {
        if ((path != AUD_PATH_TX23) && (path != AUD_PATH_RX23)) {
            TRACE("ERROR: 8800MC I2S1 must match with TX23/RX23");
            ASSERT_ERR(0);
        }
    }
    #endif

    if (stream == AUD_STREAM_PLAYBACK) {
        dma_cfg->dma_type = DMA_CX;

        dma_get_default_config(dma_cfg->dma_type, dma_cfg);

        dma_cfg->src_periph = DMA_MEMORY;
        dma_cfg->trans_type = DMA_TRANS_M2P;

        if (device == AUD_DEVICE_NONE) {
            // nothing to do
        } else if (device <= AUD_DEVICE_EXT_CODEC_I2S1) {
            if ((device == AUD_DEVICE_EXT_CODEC_I2S0) || (device == AUD_DEVICE_EXT_CODEC_I2S1)) {
#if AUDIO_CFG_TLV320AIC32_UESD
                if (!tlv320aic32_inited) {
                    #if (AUDIO_PXP == 0)
                    tlv320aic32_init();
                    #endif
                    tlv320aic32_inited = true;
                }
#endif
            }
        } else if (device <= AUD_DEVICE_EXT_CODEC_PCM) {
            //TODO
        } else if (device <= AUD_DEVICE_EXT_CODEC_SPDIF) {
            //TODO
        } else if (device == AUD_DEVICE_INT_AIC1000) {
#if (PLF_PMIC && PLF_PMIC_VER_AUD)
            if (!aic1000_inited) {
                aic1000_int_init();
                aic1000_inited = true;
            }

            // the count of bits set to 1 in ch_map should be equal to ch_num
            uint32_t ch_map = cfg->ch_map;
            uint8_t ch_num = 0;
            for (int i = 0; i < sizeof(cfg->ch_map) * 8; i++) {
                ch_num += (ch_map & 0x01);
                ch_map >>= 1;
            }
            ASSERT_ERR(ch_num == cfg->ch_num);

            aic1000_dac_cfg.sample_rate = cfg->src_en ? cfg->src_samp_rate : cfg->samp_rate;
            aic1000_dac_cfg.bits = cfg->bits;
            aic1000_dac_cfg.ch_num = cfg->ch_num;
            aic1000_dac_cfg.ch_map = cfg->ch_map;

            aic1000_dac_open(&aic1000_dac_cfg);
#endif
        } else if (device == AUD_DEVICE_EXT_AIC1000) {
#if (PLF_PMIC && !PLF_PMIC_VER_AUD && PLF_EXT_AIC1000)
            if (!aic1000_inited) {
                aic1000_ext_init();
                aic1000_inited = true;
            }

            // the count of bits set to 1 in ch_map should be equal to ch_num
            uint32_t ch_map = cfg->ch_map;
            uint8_t ch_num = 0;
            for (int i = 0; i < sizeof(cfg->ch_map) * 8; i++) {
                ch_num += (ch_map & 0x01);
                ch_map >>= 1;
            }
            ASSERT_ERR(ch_num == cfg->ch_num);

            aic1000_dac_cfg.sample_rate = cfg->src_en ? cfg->src_samp_rate : cfg->samp_rate;
            aic1000_dac_cfg.bits = cfg->bits;
            aic1000_dac_cfg.ch_num = cfg->ch_num;
            aic1000_dac_cfg.ch_map = cfg->ch_map;

            aic1000_dac_open(&aic1000_dac_cfg);
#endif
        }

#if 0
        if (cfg->path == AUD_PATH_TX01) {
            dma_cfg->dest_periph = DMA_AUD_PROC_TX0;
            dma_cfg->ext_req_cid = REQ_CID_AUD_PROC_TX0;
        } else if (cfg->path == AUD_PATH_TX23) {
            dma_cfg->dest_periph = DMA_AUD_PROC_TX2;
            dma_cfg->ext_req_cid = REQ_CID_AUD_PROC_TX2;
        } else {
            ASSERT_ERR(0);
        }
#endif

        dma_cfg->ch = asio_dma_ch[group][stream];
    } else {
        dma_cfg->dma_type = DMA_CX;

        dma_get_default_config(dma_cfg->dma_type, dma_cfg);

        dma_cfg->dest_periph = DMA_MEMORY;
        dma_cfg->trans_type = DMA_TRANS_P2M;

        if (device == AUD_DEVICE_NONE) {
            // nothing to do
        } else if (device <= AUD_DEVICE_EXT_CODEC_I2S1) {
            if ((device == AUD_DEVICE_EXT_CODEC_I2S0) || (device == AUD_DEVICE_EXT_CODEC_I2S1)) {
#if AUDIO_CFG_TLV320AIC32_UESD
                if (!tlv320aic32_inited) {
                    #if (AUDIO_PXP == 0)
                    tlv320aic32_init();
                    #endif
                    tlv320aic32_inited = true;
                }
#endif
            }
        } else if (device <= AUD_DEVICE_EXT_CODEC_PCM) {
            //TODO
        } else if (device <= AUD_DEVICE_EXT_CODEC_SPDIF) {
            //TODO
        } else if (device == AUD_DEVICE_INT_AIC1000) {
            //TODO
#if (PLF_PMIC && PLF_PMIC_VER_AUD)
            if (!aic1000_inited) {
                aic1000_int_init();
                aic1000_inited = true;
            }

            // the count of bits set to 1 in ch_map should be equal to ch_num
            uint32_t ch_map = cfg->ch_map;
            uint8_t ch_num = 0;
            for (int i = 0; i < sizeof(cfg->ch_map) * 8; i++) {
                ch_num += (ch_map & 0x01);
                ch_map >>= 1;
            }
            ASSERT_ERR(ch_num == cfg->ch_num);

            aic1000_adc_cfg[path - AUD_PATH_RX01].sample_rate = cfg->src_en ? cfg->src_samp_rate : cfg->samp_rate;
            aic1000_adc_cfg[path - AUD_PATH_RX01].bits = cfg->bits;
            aic1000_adc_cfg[path - AUD_PATH_RX01].ch_num = cfg->ch_num;
            aic1000_adc_cfg[path - AUD_PATH_RX01].ch_map = cfg->ch_map;

            aic1000_adc_open(&aic1000_adc_cfg[path - AUD_PATH_RX01]);
#endif
        } else if (device == AUD_DEVICE_EXT_AIC1000) {
#if (PLF_PMIC && !PLF_PMIC_VER_AUD && PLF_EXT_AIC1000)
            if (!aic1000_inited) {
                aic1000_ext_init();
                aic1000_inited = true;
            }

            // the count of bits set to 1 in ch_map should be equal to ch_num
            uint32_t ch_map = cfg->ch_map;
            uint8_t ch_num = 0;
            for (int i = 0; i < sizeof(cfg->ch_map) * 8; i++) {
                ch_num += (ch_map & 0x01);
                ch_map >>= 1;
            }
            ASSERT_ERR(ch_num == cfg->ch_num);

            aic1000_adc_cfg.sample_rate = cfg->src_en ? cfg->src_samp_rate : cfg->samp_rate;
            aic1000_adc_cfg.bits = cfg->bits;
            aic1000_adc_cfg.ch_num = cfg->ch_num;
            aic1000_adc_cfg.ch_map = cfg->ch_map;

            aic1000_adc_open(&aic1000_adc_cfg);
#endif
        }


#if 0
        if (cfg->path == AUD_PATH_RX01) {
            if (cfg->src_en) {
                dma_cfg->src_periph = DMA_AUD_SRC_RX;
                dma_cfg->ext_req_cid = REQ_CID_AUD_SRC_RX;
            } else {
                dma_cfg->src_periph = DMA_AUD_PROC_RX01;
                dma_cfg->ext_req_cid = REQ_CID_AUD_PROC_RX01;
            }
        } else if (cfg->path == AUD_PATH_RX23) {
            dma_cfg->src_periph = DMA_AUD_PROC_RX23;
            dma_cfg->ext_req_cid = REQ_CID_AUD_PROC_RX23;
        } else {
            ASSERT_ERR(0);
        }
#endif

        dma_cfg->ch = asio_dma_ch[group][stream];
    }

    dma_cfg->handler = asio_dma_irq_callback;

    /* Config DMA(DMA_CX for playback, ASDMA for capture) */
    asio_stream_update_dma_config(group, stream, cfg);

    entity->handler = cfg->handler;

    asio_stream_status_set(group, stream, ASIO_STATUS_STREAM_OPEN);

    res = ASIO_ERR_NONE;

exit:
    asio_task_unlock();

    if (res == ASIO_ERR_NONE) {
        asio_stream_config(group, stream, &entity->cfg);
    }

    return res;
}

int asio_stream_config(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream, const ASIO_STREAM_CFG_T *cfg)
{
    ASIO_TRACE("%s g:%d s:%d\n", __func__, group, stream);

    ASIO_STREAM_ENTITY_T *entity;
    ASIO_ERR_T res;
    AUD_DEVICE_T device;
    AUD_PATH_T path;
    uint32_t val = 0;

    entity = asio_stream_entity_get(group, stream);

    asio_task_lock();

    // check if stream is already opened
    if ((entity->ctl.status & ASIO_STATUS_STREAM_OPEN) == 0) {
        ASIO_TRACE("ERROR: %s, status:%d", __func__, entity->ctl.status);
        res = ASIO_ERR_FAIL;
        goto exit;
    }

    device = entity->ctl.device;
    path = entity->ctl.path;

    ASSERT_ERR(device < AUD_DEVICE_NUM);
    ASSERT_ERR(path < AUD_PATH_NUM);

    ASIO_TRACE("device:%d path:%d src_en:%d\n", device, path, cfg->src_en);

    // if input param <cfg> is not entity->cfg, it means asio_stream_config is called outside asio_stream_open
    // if you want to update entity->cfg, you must not set entity->cfg as input param <cfg>
    if (&entity->cfg != cfg) {
        bool update_dma = false;

        if (entity->cfg.buf_ptr != cfg->buf_ptr) {
            ASIO_TRACE("Update buf_ptr %p->%p, group:%d stream:%d\n", entity->cfg.buf_ptr, cfg->buf_ptr, group, stream);
            update_dma = true;
        }

        if (entity->cfg.buf_size != cfg->buf_size) {
            ASIO_TRACE("Update buf_size %d->%d, group:%d stream:%d\n", entity->cfg.buf_size, cfg->buf_size, group, stream);
            update_dma = true;
        }

        if (entity->cfg.bits != cfg->bits) {
            ASIO_TRACE("Update bits %d->%d, group:%d stream:%d\n", entity->cfg.bits, cfg->bits, group, stream);
            update_dma = true;
        }

        if (update_dma) {
            // stream must be stopped before updating dma config
            ASSERT_ERR((entity->ctl.status & ASIO_STATUS_STREAM_START) == 0);

            asio_stream_update_dma_config(group, stream, cfg);
        }

        if (entity->cfg.samp_rate != cfg->samp_rate) {
            ASIO_TRACE("Update samp_rate %d->%d, group:%d stream:%d\n", entity->cfg.samp_rate, cfg->samp_rate, group, stream);

            // stream must be stopped before changing sample rate
            ASSERT_ERR((entity->ctl.status & ASIO_STATUS_STREAM_START) == 0);
        }

        entity->cfg = *cfg;
    }

    if (device == AUD_DEVICE_NONE) {
        // nothing to do
    } else if (device <= AUD_DEVICE_EXT_CODEC_I2S1) {
        /* 1st Config I2S */
        AUD_I2S_CFG_T i2s_cfg;
        memset(&i2s_cfg, 0, sizeof(AUD_I2S_CFG_T));

        /* MSB, tx half cycle delay, MSB LRCK 1 cycle delay(I2S), Master mode */
        if ((device == AUD_DEVICE_I2S0) || (device == AUD_DEVICE_EXT_CODEC_I2S0)) {
            i2s_cfg.bits = cfg->bits;
            i2s_cfg.ch_num = cfg->ch_num;
            i2s_cfg.ch_map = cfg->ch_map;
            i2s_cfg.format = AUD_I2S_FORMAT_I2S;
            // for 24bits, i2s should extend to 32bits
            i2s_cfg.bck_extend = (cfg->bits == AUD_BITS_16) ? 0 : 8;
            i2s_cfg.master = false;
            i2s_cfg.samp_rate = (cfg->src_en ? cfg->src_samp_rate : cfg->samp_rate);

#if (AUDIO_PXP == 0)
            audio_proc_i2s0_iomux_config();
            if (i2s_cfg.master) {
                audio_proc_i2s_mclk_iomux_config();
            }
#endif

            audio_proc_i2s0_config(&i2s_cfg);

            if ((path == AUD_PATH_TX01) || (path == AUD_PATH_TX23)) {
                audio_proc_i2s_chn_out_sel_set(0);
            } else if (path == AUD_PATH_RX01) {
                audio_proc_i2s_chn_in_sel_set(0);
            } else {
                audio_proc_i2s_chn_in_sel_set(1);
            }
        } else {
            i2s_cfg.bits = cfg->bits;
            i2s_cfg.ch_num = cfg->ch_num;
            i2s_cfg.ch_map = cfg->ch_map;
            i2s_cfg.format = AUD_I2S_FORMAT_I2S;
            // for 24bits, i2s should extend to 32bits
            i2s_cfg.bck_extend = (cfg->bits == AUD_BITS_16) ? 0 : 8;
            i2s_cfg.master = false;
            i2s_cfg.samp_rate = (cfg->src_en ? cfg->src_samp_rate : cfg->samp_rate);

#if (AUDIO_PXP == 0)
            audio_proc_i2s1_iomux_config();
            if (i2s_cfg.master) {
                audio_proc_i2s_mclk_iomux_config();
            }
#endif

            audio_proc_i2s1_config(&i2s_cfg);

            if ((path == AUD_PATH_TX01) || (path == AUD_PATH_TX23)) {
                audio_proc_i2s_chn_out_sel_set(1);
            } else if (path == AUD_PATH_RX01) {
                audio_proc_i2s_chn_in_sel_set(1);
            } else {
                audio_proc_i2s_chn_in_sel_set(0);
            }
        }

        /* 2nd Config extern codec */
        if ((device == AUD_DEVICE_EXT_CODEC_I2S0) || (device == AUD_DEVICE_EXT_CODEC_I2S1)) {
#if AUDIO_CFG_TLV320AIC32_UESD
            tlv320aic32_cfg_t tlv320aic32_cfg;
            tlv320aic32_cfg.samp_rate = cfg->src_en ? cfg->src_samp_rate : cfg->samp_rate;
            tlv320aic32_cfg.bits = cfg->bits;
            tlv320aic32_cfg.ch_num = cfg->ch_num;
            tlv320aic32_cfg.codec_master = !i2s_cfg.master;
            tlv320aic32_cfg.format = i2s_cfg.format;
#if (AUDIO_PXP == 0)
            ASIO_TRACE("cfg in\n");
            tlv320aic32_config(&tlv320aic32_cfg);
            ASIO_TRACE("cfg exit\n");
#endif
#endif
        }
    } else if (device <= AUD_DEVICE_EXT_CODEC_PCM) {
        //TODO
    } else if (device <= AUD_DEVICE_EXT_CODEC_SPDIF) {
        //TODO
    } else if (device == AUD_DEVICE_INT_AIC1000) {
#if (PLF_PMIC && PLF_PMIC_VER_AUD)
        /* MSB, 24 bits, Left-justified, Slave mode */
        AUD_I2S_CFG_T i2s_cfg;
        memset(&i2s_cfg, 0, sizeof(AUD_I2S_CFG_T));
        i2s_cfg.bits = AUD_BITS_24;
        i2s_cfg.format = AUD_I2S_FORMAT_LEFT_JUSTIFIED;
        i2s_cfg.bck_extend = 0;
        i2s_cfg.master = false;
        i2s_cfg.samp_rate = AUD_SAMPRATE_48000;
        audio_proc_i2s0_config(&i2s_cfg);
        audio_proc_i2s1_config(&i2s_cfg);

        if (stream == AUD_STREAM_PLAYBACK) {
            aic1000_dac_config(&aic1000_dac_cfg);
        } else {
            if ((cfg->ch_map & (AUD_CH_MAP_CH_0 | AUD_CH_MAP_CH_1)) != 0) {
                if (path == AUD_PATH_RX01) {
                    audio_proc_i2s_chn_in_sel_set(1);
                } else {
                    audio_proc_i2s_chn_in_sel_set(0);
                }
            }
            if ((cfg->ch_map & AUD_CH_MAP_CH_2) != 0) {
                if (path == AUD_PATH_RX01) {
                    audio_proc_i2s_chn_in_sel_set(0);
                } else {
                    audio_proc_i2s_chn_in_sel_set(1);
                }
            }

            aic1000_adc_config(&aic1000_adc_cfg[path - AUD_PATH_RX01]);
        }
#endif
    } else if (device == AUD_DEVICE_EXT_AIC1000) {
#if (PLF_PMIC && !PLF_PMIC_VER_AUD && PLF_EXT_AIC1000)
        /* MSB, 24 bits, Left-justified, Slave mode */
        AUD_I2S_CFG_T i2s_cfg;
        memset(&i2s_cfg, 0, sizeof(AUD_I2S_CFG_T));
        i2s_cfg.bits = AUD_BITS_24;
        i2s_cfg.format = AUD_I2S_FORMAT_LEFT_JUSTIFIED;
        i2s_cfg.bck_extend = 0;
        i2s_cfg.master = false;
        i2s_cfg.samp_rate = AUD_SAMPRATE_48000;
        if (aic1000_i2s_idx == 0) {
            audio_proc_i2s0_config(&i2s_cfg);
        } else {
            audio_proc_i2s1_config(&i2s_cfg);
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            if (aic1000_i2s_idx == 0) {
                audio_proc_i2s_chn_out_sel_set(0);
            } else {
                audio_proc_i2s_chn_out_sel_set(1);
            }
            aic1000_dac_config(&aic1000_dac_cfg);
        } else {
            if (aic1000_i2s_idx == 0) {
                if (path == AUD_PATH_RX01) {
                    audio_proc_i2s_chn_in_sel_set(0);
                } else {
                    audio_proc_i2s_chn_in_sel_set(1);
                }
            } else {
                if (path == AUD_PATH_RX01) {
                    audio_proc_i2s_chn_in_sel_set(1);
                } else {
                    audio_proc_i2s_chn_in_sel_set(0);
                }
            }
            aic1000_adc_config(&aic1000_adc_cfg);
        }
#endif
    }


    //ASIO_TRACE("path:%d src_en:%d\n", path, cfg->src_en);
    /* 2nd Config aud_proc */
    if (path == AUD_PATH_TX01) {
        /* DAC SRC enable, mode and filter set */
        audio_proc_src_config(cfg->src_en, cfg->ch_num, cfg->bits, cfg->samp_rate, cfg->src_samp_rate);

        /* DAC mixer mode(default L=L, R=R) set*/
        audio_proc_dac_mixer_mode_set(dac_mixer_mode[PLF_DACL_MIXER_MODE], dac_mixer_mode[PLF_DACR_MIXER_MODE]);

        /* tx01 lr fifo share enable, txrx lr fifo share enable */
        if (cfg->ch_num == AUD_CH_NUM_2) {
            audio_proc_tx_lr_fifo_share_en_set(0, 1);
            audio_proc_txrx_lr_fifo_share_en_set(0, 1);
        } else {
            audio_proc_tx_lr_fifo_share_en_set(0, 0);
            audio_proc_txrx_lr_fifo_share_en_set(0, 0);
        }

        /* Set channel mode(16 bits or 24 bits) */
        if (cfg->bits == AUD_BITS_24) {
            audio_proc_tx_mode_ch_0_set(1);
            audio_proc_tx_mode_ch_1_set(1);
        } else {
            audio_proc_tx_mode_ch_0_set(0);
            audio_proc_tx_mode_ch_1_set(0);
        }
    } else if (path == AUD_PATH_TX23) {
        /* tx mux config, add tx ch2 to L, add tx ch3 to R  */
        audio_proc_tx_mux_mode_set(0, 1);

        /* tx23 lr fifo share enable, txrx lr fifo share enable */
        if (cfg->ch_num == AUD_CH_NUM_2) {
            audio_proc_tx_lr_fifo_share_en_set(1, 1);
            audio_proc_txrx_lr_fifo_share_en_set(1, 1);
        } else {
            audio_proc_tx_lr_fifo_share_en_set(1, 0);
            audio_proc_txrx_lr_fifo_share_en_set(1, 0);
        }

        /* Set channel mode(16 bits or 24 bits) */
        if (cfg->bits == AUD_BITS_24) {
            audio_proc_tx_mode_ch_2_set(1);
            audio_proc_tx_mode_ch_3_set(1);
        } else {
            audio_proc_tx_mode_ch_2_set(0);
            audio_proc_tx_mode_ch_3_set(0);
        }
    } else if (path == AUD_PATH_RX01) {
        /* rx01 lr fifo share enable, rxtx lr fifo share enable */
        if (cfg->ch_num == AUD_CH_NUM_2) {
            audio_proc_rx_lr_fifo_share_en_set(0, 1);
            audio_proc_rxtx_lr_fifo_share_en_set(0, 1);
        } else {
            audio_proc_rx_lr_fifo_share_en_set(0, 0);
            audio_proc_rxtx_lr_fifo_share_en_set(0, 0);
        }

        /* Set channel mode(16 bits or 24 bits) */
        if (cfg->bits == AUD_BITS_24) {
            audio_proc_rx_mode_ch_01_set(1);
        } else {
            audio_proc_rx_mode_ch_01_set(0);
        }

        /* AUD SRC enable, mode, fifo and div config */
        audio_proc_aud_src_config(cfg->src_en, cfg->ch_num, cfg->bits, cfg->src_samp_rate, cfg->samp_rate);
    } else if (path == AUD_PATH_RX23) {
        /* rx01 lr fifo share enable, rxtx lr fifo share enable */
        if (cfg->ch_num == AUD_CH_NUM_2) {
            audio_proc_rx_lr_fifo_share_en_set(1, 1);
            audio_proc_rxtx_lr_fifo_share_en_set(1, 1);
        } else {
            audio_proc_rx_lr_fifo_share_en_set(1, 0);
            audio_proc_rxtx_lr_fifo_share_en_set(1, 0);
        }

        /* Set channel mode(16 bits or 24 bits) */
        if (cfg->bits == AUD_BITS_24) {
            audio_proc_rx_mode_ch_23_set(1);
        } else {
            audio_proc_rx_mode_ch_23_set(0);
        }
    }

    NVIC_SetVector(asio_dma_irqn[group][stream], asio_dma_irq_handler[group][stream]);
    NVIC_SetPriority(asio_dma_irqn[group][stream], __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(asio_dma_irqn[group][stream]);

    res = ASIO_ERR_NONE;

exit:
    asio_task_unlock();

    ASIO_TRACE("%s exit\n", __func__);

    return res;
}

void asio_stream_mute(AUD_STREAM_T stream)
{
    if (stream == AUD_STREAM_PLAYBACK) {
        audio_proc_dac_volume_mute();
    } else {
        audio_proc_adc_volume_mute();
    }
}

/*
 * This function is used to set digital volume
 * for output, volume will be applied before data were sent to other audio devices or audio interfaces
 * for input, volume will be applied after data were received from other audio devices or audio interfaces
 *
 * for output, 8bits
 * if (bit[7:0] != 0) {
 *     volume = bit[5:0] + bit[6] * 6dB + bit[7] * 12dB;
 * } else {
 *     volume = mute;
 * }
 * eg. 8'h33 = -0.5dB + 0 * 6dB + 0 * 12dB = -0.5dB;
 * eg. 8'h74 = 0dB + 1 * 6dB + 0 * 12dB = 6dB;
 * eg. 8'hB5 = 0.5dB + 0 * 6dB + 1 * 12dB = 12.5dB;
 * eg. 8'hff = 5.5dB + 1 * 6dB + 1 * 12dB = 23.5dB;
 *
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h0  | -26dB       |
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h1  | -25.5dB     |
 * |----------|-------|-------------|
 * | bit[5:0] |  ...  | +0.5dB/step |
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h34 |  0dB        |
 * |----------|-------|-------------|
 * | bit[5:0] |  ...  | +0.5dB/step |
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h3e |  5dB        |
 * |----------|-------|-------------|
 * | bit[5:0] | 6'h3f |  5.5dB      |
 * |----------|-------|-------------|
 *
 *
 * for input, 4bits
 * |----------|-------|-------------|
 * | bit[3:0] | 4'h0  |  mute       |
 * |----------|-------|-------------|
 * | bit[3:0] | 4'h1  | -12dB       |
 * |----------|-------|-------------|
 * | bit[3:0] |  ...  | +2dB/step   |
 * |----------|-------|-------------|
 * | bit[3:0] | 4'h7  |  0dB        |
 * |----------|-------|-------------|
 * | bit[3:0] |  ...  | +2dB/step   |
 * |----------|-------|-------------|
 * | bit[3:0] | 4'he  |  14dB       |
 * |----------|-------|-------------|
 * | bit[3:0] | 4'hf  |  16dB       |
 * |----------|-------|-------------|
 */
int asio_stream_raw_digital_volume_set(AUD_STREAM_T stream, uint8_t volume)
{
    int ret;

    if (stream == AUD_STREAM_PLAYBACK) {
        ret = audio_proc_dac_volume_set(volume);
    } else {
        ret = audio_proc_adc_volume_set(volume);
    }

    return (ret == 0) ? ASIO_ERR_NONE : ASIO_ERR_FAIL;
}

uint8_t asio_stream_raw_digital_volume_get(AUD_STREAM_T stream)
{
    uint8_t vol;

    if (stream == AUD_STREAM_PLAYBACK) {
        vol = audio_proc_dac_volume_get();
    } else {
        vol = audio_proc_adc_volume_get();
    }

    return vol;
}

/*
 * for output, 1 step is 0.5dB
 * for input, 1 step is 2dB
 */
bool asio_stream_raw_digital_volume_up(AUD_STREAM_T stream, uint8_t step)
{
    bool max_vol;

    if (stream == AUD_STREAM_PLAYBACK) {
        max_vol = audio_proc_dac_volume_up(step);
    } else {
        max_vol = audio_proc_adc_volume_up(step);
    }

    return max_vol;
}

/*
 * for output, 1 step is 0.5dB
 * for input, 1 step is 2dB
 */
bool asio_stream_raw_digital_volume_down(AUD_STREAM_T stream, uint8_t step)
{
    bool min_vol;

    if (stream == AUD_STREAM_PLAYBACK) {
        min_vol = audio_proc_dac_volume_down(step);
    } else {
        min_vol = audio_proc_adc_volume_down(step);
    }

    return min_vol;
}

int asio_stream_preload(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream, bool ping)
{
    ASIO_TRACE("%s g:%d s:%d ping:%d\n", __func__, group, stream, ping);

    ASIO_STREAM_ENTITY_T *entity;
    ASIO_ERR_T res;
    uint8_t *buf;

    entity = asio_stream_entity_get(group, stream);

    asio_task_lock();

    // check if stream is already opened but not started.
    if (entity->ctl.status != (ASIO_STATUS_ASIO_OPEN | ASIO_STATUS_STREAM_OPEN)) {
        ASIO_TRACE("ERROR: %s, status:%d\n",__func__, entity->ctl.status);
        res = ASIO_ERR_FAIL;
        goto exit;
    }

    if (ping) {
        buf = entity->dma_buf_ptr;
    } else {
        buf = entity->dma_buf_ptr + entity->dma_buf_size / 2;
    }

    if (entity->handler) {
        entity->handler(buf, entity->dma_buf_size / 2);
    }

    res = ASIO_ERR_NONE;

exit:
    asio_task_unlock();

    return res;
}

int asio_stream_start(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    ASIO_TRACE("%s g:%d s:%d\n", __func__, group, stream);

    ASIO_STREAM_ENTITY_T *entity;
    ASIO_ERR_T res;
    AUD_DEVICE_T device;
    AUD_PATH_T path;

    entity = asio_stream_entity_get(group, stream);

    asio_task_lock();

    // check if stream is already opened but not started.
    if (entity->ctl.status != (ASIO_STATUS_ASIO_OPEN | ASIO_STATUS_STREAM_OPEN)) {
        ASIO_TRACE("ERROR: %s, status:%d\n",__func__, entity->ctl.status);
        res = ASIO_ERR_FAIL;
        goto exit;
    }

    device = entity->ctl.device;
    path = entity->ctl.path;

    ASSERT_ERR(device < AUD_DEVICE_NUM);
    ASSERT_ERR(path < AUD_PATH_NUM);

    entity->ctl.pp_index = ASIO_PP_PING;
    entity->ctl.pp_cnt = 0;

    ASIO_TRACE("device:%d path:%d\n", device, path);

    /* 1st Enable DMA_CX */
    dma_cx_halt_set(entity->dma_cfg.ch, false);
    dma_cx_enable_set(entity->dma_cfg.ch, true);

    /* 2nd Enable AUD_PROC */
    if (path == AUD_PATH_TX01) {
        audio_proc_tx_en_ch_0_set(1);
    } else if (path == AUD_PATH_TX23) {
        audio_proc_tx_en_ch_2_set(1);
    } else if (path == AUD_PATH_RX01) {
        audio_proc_rx_en_ch_01_set(1);
    } else if (path == AUD_PATH_RX23) {
        audio_proc_rx_en_ch_23_set(1);
    }

    audio_proc_aud_proc_enable_set(1);
    aud_path_opened[path] = true;

    /* 3rd Enable I2S */
    if (device == AUD_DEVICE_NONE) {
        // nothing to do
    } else if (device <= AUD_DEVICE_EXT_CODEC_I2S1) {
        if ((device == AUD_DEVICE_I2S0) || (device == AUD_DEVICE_EXT_CODEC_I2S0)) {
            audio_proc_i2s0_enable_set(1);
        } else {
            audio_proc_i2s1_enable_set(1);
        }
    } else if (device <= AUD_DEVICE_EXT_CODEC_PCM) {
        //TODO
    } else if (device <= AUD_DEVICE_EXT_CODEC_SPDIF) {
        //TODO
    } else if (device == AUD_DEVICE_INT_AIC1000) {
#if (PLF_PMIC && PLF_PMIC_VER_AUD)
        if ((path == AUD_PATH_TX01) || (path == AUD_PATH_TX23)) {
            audio_proc_i2s0_enable_set(1);
        } else if (path == AUD_PATH_RX01) {
            if (audio_proc_i2s_chn_in_sel_get() == 0) {
                audio_proc_i2s0_enable_set(1);
            } else {
                audio_proc_i2s1_enable_set(1);
            }
        } else {
            if (audio_proc_i2s_chn_in_sel_get() == 0) {
                audio_proc_i2s1_enable_set(1);
            } else {
                audio_proc_i2s0_enable_set(1);
            }
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            aic1000_dac_start(&aic1000_dac_cfg);
        } else {
            aic1000_adc_start(&aic1000_adc_cfg[path - AUD_PATH_RX01]);
        }
#endif
    } else if (device == AUD_DEVICE_EXT_AIC1000) {
#if (PLF_PMIC && !PLF_PMIC_VER_AUD && PLF_EXT_AIC1000)
        if (aic1000_i2s_idx == 0) {
            audio_proc_i2s0_enable_set(1);
        } else {
            audio_proc_i2s1_enable_set(1);
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            aic1000_dac_start(&aic1000_dac_cfg);
        } else {
            aic1000_adc_start(&aic1000_adc_cfg);
        }
#endif
    }


    aud_device_opened[device][stream] = true;

    asio_stream_status_set(group, stream, ASIO_STATUS_STREAM_START);

    res = ASIO_ERR_NONE;

exit:
    asio_task_unlock();

    ASIO_TRACE("%s exit\n", __func__);

    return res;
}

int asio_stream_stop(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    ASIO_TRACE("%s g:%d s:%d\n", __func__, group, stream);

    ASIO_STREAM_ENTITY_T *entity;
    ASIO_STREAM_CFG_T *cfg;
    ASIO_ERR_T res;
    AUD_DEVICE_T device;
    AUD_PATH_T path;
    uint32_t val = 0;
    int i = 0;
    bool aud_path_all_closed = false;

    entity = asio_stream_entity_get(group, stream);

    asio_task_lock();

    cfg = &entity->cfg;
    device = entity->ctl.device;
    path = entity->ctl.path;

    ASSERT_ERR(device < AUD_DEVICE_NUM);
    ASSERT_ERR(path < AUD_PATH_NUM);

    // check if stream is already started
    if (entity->ctl.status != (ASIO_STATUS_ASIO_OPEN | ASIO_STATUS_STREAM_OPEN | ASIO_STATUS_STREAM_START)) {
        ASIO_TRACE("ERROR: %s, status:%d\n",__func__, entity->ctl.status);
        res = ASIO_ERR_FAIL;
        goto exit;
    }

    aud_device_opened[device][stream] = false;

    /* Set aud_path_opened here in order to use it in subsequent steps. */
    aud_path_opened[path] = false;

    for (i = 0; i < AUD_PATH_NUM; i++) {
        if (aud_path_opened[i] == true) {
            break;
        }
    }
    if (i == AUD_PATH_NUM) {
        aud_path_all_closed = true;
    }

    /* 1st Disable I2S */
    if (device == AUD_DEVICE_NONE) {
        // nothing to do
    } else if (device <= AUD_DEVICE_EXT_CODEC_I2S1) {
        bool i2s_chn_out_sel = audio_proc_i2s_chn_out_sel_get() ? true : false;
        bool i2s_chn_in_sel = audio_proc_i2s_chn_in_sel_get() ? true : false;
        bool i2s_disable = true;

        if ((device == AUD_DEVICE_I2S0) || (device == AUD_DEVICE_EXT_CODEC_I2S0)) {
            if (false == i2s_chn_out_sel) {
                if ((false != aud_path_opened[AUD_PATH_TX01]) || (false != aud_path_opened[AUD_PATH_TX23])) {
                    i2s_disable = false;
                }
            }

            if (false == i2s_chn_in_sel) {
                if (false != aud_path_opened[AUD_PATH_RX01]) {
                    i2s_disable = false;
                }
            } else {
                if (false != aud_path_opened[AUD_PATH_RX23]) {
                    i2s_disable = false;
                }
            }

            if (true == i2s_disable) {
                audio_proc_i2s0_enable_set(0);
            }
        } else {
            if (true == i2s_chn_out_sel) {
                if ((false != aud_path_opened[AUD_PATH_TX01]) || (false != aud_path_opened[AUD_PATH_TX23])) {
                    i2s_disable = false;
                }
            }

            if (false == i2s_chn_in_sel) {
                if (false != aud_path_opened[AUD_PATH_RX23]) {
                    i2s_disable = false;
                }
            } else {
                if (false != aud_path_opened[AUD_PATH_RX01]) {
                    i2s_disable = false;
                }
            }

            if (true == i2s_disable) {
                audio_proc_i2s1_enable_set(0);
            }
        }
    } else if (device <= AUD_DEVICE_EXT_CODEC_PCM) {
        //TODO
    } else if (device <= AUD_DEVICE_EXT_CODEC_SPDIF) {
        //TODO
    } else if (device == AUD_DEVICE_INT_AIC1000) {
#if (PLF_PMIC && PLF_PMIC_VER_AUD)
        uint8_t mixer_mode_l = 0;
        uint8_t mixer_mode_r = 0;
        bool i2s_chn_in_sel = audio_proc_i2s_chn_in_sel_get() ? true : false;
        bool i2s0_disable = false;
        bool i2s1_disable = false;

        if ((path == AUD_PATH_TX01) || (path == AUD_PATH_TX23)) {
            if ((aud_path_opened[AUD_PATH_TX01] == false) && (aud_path_opened[AUD_PATH_TX23] == false)) {
                if (i2s_chn_in_sel == false) {
                    if (aud_path_opened[AUD_PATH_RX01] == false) {
                        i2s0_disable = true;
                    }
                } else {
                    if (aud_path_opened[AUD_PATH_RX23] == false) {
                        i2s0_disable = true;
                    }
                }
            }
        } else if (path == AUD_PATH_RX01) {
            if (i2s_chn_in_sel == false) {
                if ((aud_path_opened[AUD_PATH_TX01] == false) && (aud_path_opened[AUD_PATH_TX23] == false)) {
                    i2s0_disable = true;
                }
            } else {
                i2s1_disable = true;
            }
        } else {
            if (i2s_chn_in_sel == false) {
                i2s1_disable = true;
            } else {
                if ((aud_path_opened[AUD_PATH_TX01] == false) && (aud_path_opened[AUD_PATH_TX23] == false)) {
                    i2s0_disable = true;
                }
            }
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            if ((aud_path_opened[AUD_PATH_TX01] == false) && (aud_path_opened[AUD_PATH_TX23] == false)) {
                mixer_mode_l = audio_proc_dac_mixer_mode_l_get();
                mixer_mode_r = audio_proc_dac_mixer_mode_r_get();
                audio_proc_dac_mixer_mode_set(1, 1);

                uint32_t delay = 0;
                uint32_t delay_samples = 20;
                //(HCLK / 1000000) * (1000 / 48) * (delay_samples / 10)
                delay = sysctrl_clock_get(SYS_HCLK) / 1000000 * 1000 / 48 * delay_samples / 10;
                for (uint32_t i = 0; i < delay; i++) {
                    __NOP(); __NOP(); __NOP(); __NOP();
                    __NOP(); __NOP(); __NOP();
                }
            }
        }

        if (i2s0_disable == true) {
            audio_proc_i2s0_enable_set(0);
        }
        if (i2s1_disable == true) {
            audio_proc_i2s1_enable_set(0);
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            aic1000_dac_stop(&aic1000_dac_cfg);
        } else {
            aic1000_adc_stop(&aic1000_adc_cfg[path - AUD_PATH_RX01]);
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            if ((aud_path_opened[AUD_PATH_TX01] == false) && (aud_path_opened[AUD_PATH_TX23] == false)) {
                audio_proc_dac_mixer_mode_set(mixer_mode_l, mixer_mode_r);
            }
        }
#endif
    } else if (device == AUD_DEVICE_EXT_AIC1000) {
#if (PLF_PMIC && !PLF_PMIC_VER_AUD && PLF_EXT_AIC1000)
        uint8_t mixer_mode_l = 0;
        uint8_t mixer_mode_r = 0;
        bool i2s_chn_out_sel = audio_proc_i2s_chn_out_sel_get() ? true : false;
        bool i2s_chn_in_sel = audio_proc_i2s_chn_in_sel_get() ? true : false;
        bool i2s_disable = true;

        if (aic1000_i2s_idx == 0) {
            if (false == i2s_chn_out_sel) {
                if ((false != aud_path_opened[AUD_PATH_TX01]) || (false != aud_path_opened[AUD_PATH_TX23])) {
                    i2s_disable = false;
                }
            }

            if (false == i2s_chn_in_sel) {
                if (false != aud_path_opened[AUD_PATH_RX01]) {
                    i2s_disable = false;
                }
            } else {
                if (false != aud_path_opened[AUD_PATH_RX23]) {
                    i2s_disable = false;
                }
            }
        } else {
            if (true == i2s_chn_out_sel) {
                if ((false != aud_path_opened[AUD_PATH_TX01]) || (false != aud_path_opened[AUD_PATH_TX23])) {
                    i2s_disable = false;
                }
            }

            if (false == i2s_chn_in_sel) {
                if (false != aud_path_opened[AUD_PATH_RX23]) {
                    i2s_disable = false;
                }
            } else {
                if (false != aud_path_opened[AUD_PATH_RX01]) {
                    i2s_disable = false;
                }
            }
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            if ((aud_path_opened[AUD_PATH_TX01] == false) && (aud_path_opened[AUD_PATH_TX23] == false)) {
                mixer_mode_l = audio_proc_dac_mixer_mode_l_get();
                mixer_mode_r = audio_proc_dac_mixer_mode_r_get();
                audio_proc_dac_mixer_mode_set(1, 1);

                uint32_t delay = 0;
                uint32_t delay_samples = 20;
                //(HCLK / 1000000) * (1000 / 48) * (delay_samples / 10)
                delay = sysctrl_clock_get(SYS_HCLK) / 1000000 * 1000 / 48 * delay_samples / 10;
                for (uint32_t i = 0; i < delay; i++) {
                    __NOP(); __NOP(); __NOP(); __NOP();
                    __NOP(); __NOP(); __NOP();
                }
            }
        }

        if (i2s_disable == true) {
            if (aic1000_i2s_idx == 0) {
                audio_proc_i2s0_enable_set(0);
            } else {
                audio_proc_i2s1_enable_set(0);
            }
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            aic1000_dac_stop(&aic1000_dac_cfg);
        } else {
            aic1000_adc_stop(&aic1000_adc_cfg);
        }

        if (stream == AUD_STREAM_PLAYBACK) {
            if ((aud_path_opened[AUD_PATH_TX01] == false) && (aud_path_opened[AUD_PATH_TX23] == false)) {
                audio_proc_dac_mixer_mode_set(mixer_mode_l, mixer_mode_r);
            }
        }
#endif
    }


    ASIO_TRACE("I2S Disabled\n");

    /* 4th Disable AUD_PROC */
    if (path == AUD_PATH_TX01) {
        audio_proc_tx_en_ch_0_set(0);
    } else if (path == AUD_PATH_TX23) {
        audio_proc_tx_en_ch_2_set(0);

        /* disable tx mux  */
        audio_proc_tx_mux_mode_set(3, 3);
    } else if (path == AUD_PATH_RX01) {
        //TODO Enable configs below after AUDIO PATH modified
        audio_proc_rx_en_ch_01_set(0);
    } else if (path == AUD_PATH_RX23) {
        audio_proc_rx_en_ch_23_set(0);
    }

    /* If all path of AUD_PROC were colsed, then close AUD_PROC */
    if (aud_path_all_closed == true) {
        audio_proc_aud_proc_enable_set(0);
    }

    ASIO_TRACE("AUD_PROC Disabled\n");

    /* 5th Disable DMA_CX */
    if (entity->dma_cfg.dma_type == DMA_CX) {
        dma_cx_enable_set(entity->dma_cfg.ch, false);
    } else {
        //RX does not use DMA_CX
    }

    ASIO_TRACE("DMA_CX Disabled\n");

#if 1
    /* Flush AUD_PROC FIFO */
    if (path == AUD_PATH_TX01) {
        audio_proc_tx_fifo_flush_ch_0_set(1);
        audio_proc_tx_fifo_flush_ch_1_set(1);
        if (false == aud_path_opened[AUD_PATH_TX23]) {
            audio_proc_txrx_fifo_flush_ch_0_set(1);
        }
        __NOP();
        audio_proc_tx_fifo_flush_ch_0_set(0);
        audio_proc_tx_fifo_flush_ch_1_set(0);
        if (false ==  aud_path_opened[AUD_PATH_TX23]) {
            audio_proc_txrx_fifo_flush_ch_0_set(0);
        }
    } else if (path == AUD_PATH_TX23) {
        audio_proc_tx_fifo_flush_ch_2_set(1);
        audio_proc_tx_fifo_flush_ch_3_set(1);
        if (false == aud_path_opened[AUD_PATH_TX01]) {
            audio_proc_txrx_fifo_flush_ch_0_set(1);
        }
        __NOP();
        audio_proc_tx_fifo_flush_ch_2_set(0);
        audio_proc_tx_fifo_flush_ch_3_set(0);
        if (false ==  aud_path_opened[AUD_PATH_TX01]) {
            audio_proc_txrx_fifo_flush_ch_0_set(0);
        }
    } else if (path == AUD_PATH_RX01) {
        audio_proc_rx_fifo_flush_ch_01_set(1);
        audio_proc_rxtx_fifo_flush_ch_0_set(1);
        __NOP();
        audio_proc_rx_fifo_flush_ch_01_set(0);
        audio_proc_rxtx_fifo_flush_ch_0_set(0);
    } else if (path == AUD_PATH_RX23) {
        audio_proc_rx_fifo_flush_ch_23_set(1);
        audio_proc_rxtx_fifo_flush_ch_1_set(1);
        __NOP();
        audio_proc_rx_fifo_flush_ch_23_set(0);
        audio_proc_rxtx_fifo_flush_ch_1_set(0);
    }

    /* Flush AUD_PROC DAC/ADC */
    if ((path == AUD_PATH_TX01) || (path == AUD_PATH_TX23)) {
        if ((false == aud_path_opened[AUD_PATH_TX01]) && (false == aud_path_opened[AUD_PATH_TX23])) {
            audio_proc_aud_proc_dac_path_reset_set(1);
            __NOP();
            audio_proc_aud_proc_dac_path_reset_set(0);
        }
    } else if ((path == AUD_PATH_RX01) || (path == AUD_PATH_RX23)) {
        if ((false == aud_path_opened[AUD_PATH_RX01]) && (false == aud_path_opened[AUD_PATH_RX23])) {
            audio_proc_aud_proc_adc_path_reset_set(1);
            __NOP();
            audio_proc_aud_proc_adc_path_reset_set(0);
        }
    }

    /* Flush SRC */
    if (path == AUD_PATH_TX01) {
        if (cfg->src_en == true) {
            audio_proc_src_clr_set(1);
            __NOP();
            audio_proc_src_clr_set(0);
        }
    } else if (path == AUD_PATH_RX01) {
        if (cfg->src_en == true) {
            audio_proc_aud_src_clr_set(1);
            __NOP();
            audio_proc_aud_src_clr_set(0);
        }
    }

    ASIO_TRACE("AUDIO PATH Flushed\n");
#endif

    asio_stream_status_clear(group, stream, ASIO_STATUS_STREAM_START);

    res = ASIO_ERR_NONE;

exit:
    asio_task_unlock();

    ASIO_TRACE("%s exit\n", __func__);

    return res;
}

int asio_stream_pause(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    ASIO_ERR_T res;

    #if 1
    //TODO
    res = ASIO_ERR_NONE;
    #else
    res = asio_stream_stop(group, stream);
    #endif

    return res;
}

int asio_stream_resume(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    ASIO_ERR_T res;

    #if 1
    //TODO
    res = ASIO_ERR_NONE;
    #else
    res = asio_stream_start(group, stream);
    #endif

    return res;
}

int asio_stream_close(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    ASIO_TRACE("%s g:%d s:%d\n", __func__, group, stream);

    ASIO_STREAM_ENTITY_T *entity;
    ASIO_ERR_T res;
    AUD_DEVICE_T device;
    AUD_PATH_T path;

    entity = asio_stream_entity_get(group, stream);

    asio_task_lock();

    // check if stream is already stoped but not closed.
    if (entity->ctl.status != (ASIO_STATUS_ASIO_OPEN | ASIO_STATUS_STREAM_OPEN)) {
        ASIO_TRACE("ERROR: %s, status:%d\n",__func__, entity->ctl.status);
        res = ASIO_ERR_FAIL;
        goto exit;
    }

    device = entity->ctl.device;
    path = entity->ctl.path;

    memset(entity->dma_buf_ptr, 0, entity->dma_buf_size);

    dma_cx_free(entity->dma_cfg.ch);
    dma_cx_set_lli_cntr(entity->dma_cfg.ch, 0);


    entity->handler = NULL;
    entity->ctl.pp_index = ASIO_PP_PING;
    entity->ctl.pp_cnt = 0;
    entity->ctl.device = AUD_DEVICE_NONE;
    entity->ctl.path = AUD_PATH_NONE;
    entity->dma_buf_ptr = NULL;
    entity->dma_buf_size = 0;
    entity->dma_cfg.ch = DMA_CH_NONE;

    if (device == AUD_DEVICE_NONE) {
        // nothing to do
    } else if (device <= AUD_DEVICE_EXT_CODEC_I2S1) {
        //TODO
    } else if (device <= AUD_DEVICE_EXT_CODEC_PCM) {
        //TODO
    } else if (device <= AUD_DEVICE_EXT_CODEC_SPDIF) {
        //TODO
    } else if (device == AUD_DEVICE_INT_AIC1000) {
#if (PLF_PMIC && PLF_PMIC_VER_AUD)
        //TODO eliminate POP noise
        #if 1
        if (stream == AUD_STREAM_PLAYBACK) {
            aic1000_dac_close(&aic1000_dac_cfg);
        } else {
            aic1000_adc_close(&aic1000_adc_cfg[path - AUD_PATH_RX01]);
        }
        #endif
#endif
    } else if (device == AUD_DEVICE_EXT_AIC1000) {
#if (PLF_PMIC && !PLF_PMIC_VER_AUD && PLF_EXT_AIC1000)
        //TODO eliminate POP noise
        #if 1
        if (stream == AUD_STREAM_PLAYBACK) {
            aic1000_dac_close(&aic1000_dac_cfg);
        } else {
            aic1000_adc_close(&aic1000_adc_cfg);
        }
        #endif
#endif
    }

    asio_stream_status_clear(group, stream, ASIO_STATUS_STREAM_OPEN);

    res = ASIO_ERR_NONE;

exit:
    asio_task_unlock();

    return res;
}

int asio_close(void)
{
    ASIO_STREAM_ENTITY_T *entity;

    for (int group = 0; group < AUD_STREAM_GROUP_NUM; group++) {
        for (int stream = 0; stream < AUD_STREAM_NUM; stream++) {
            entity = asio_stream_entity_get((AUD_STREAM_GROUP_T)group, (AUD_STREAM_T)stream);

            if ((entity->ctl.status & ASIO_STATUS_STREAM_START) != 0) {
                asio_stream_stop((AUD_STREAM_GROUP_T)group, (AUD_STREAM_T)stream);
            }

            if ((entity->ctl.status & ASIO_STATUS_STREAM_OPEN) != 0) {
                asio_stream_close((AUD_STREAM_GROUP_T)group, (AUD_STREAM_T)stream);
            }

            memset(entity, 0, sizeof(ASIO_STREAM_ENTITY_T));
        }
    }

    if (asio_mutex) {
        rtos_mutex_delete(asio_mutex);
    }

    if (asio_task_handle) {
        rtos_task_delete(asio_task_handle);
    }

    return ASIO_ERR_NONE;
}

int asio_stream_config_get(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream, ASIO_STREAM_CFG_T *cfg, bool lock_task)
{
    ASIO_STREAM_ENTITY_T *entity;
    ASIO_ERR_T res;

    if (lock_task) {
        asio_task_lock();
    }

    entity = asio_stream_entity_get(group, stream);

    // check if stream is already opened
    if (entity->ctl.status & ASIO_STATUS_STREAM_OPEN) {
        *cfg = entity->cfg;
        res = ASIO_ERR_NONE;
    } else {
        res = ASIO_ERR_FAIL;
    }

    if (lock_task) {
        asio_task_unlock();
    }

    return res;
}

int asio_stream_config_ptr_get(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream, ASIO_STREAM_CFG_T **cfg, bool lock_task)
{
    ASIO_STREAM_ENTITY_T *entity;
    ASIO_ERR_T res;

    if (lock_task) {
        asio_task_lock();
    }

    entity = asio_stream_entity_get(group, stream);

    // check if stream is already opened
    if (entity->ctl.status & ASIO_STATUS_STREAM_OPEN) {
        *cfg = &(entity->cfg);
        res = ASIO_ERR_NONE;
    } else {
        res = ASIO_ERR_FAIL;
    }

    if (lock_task) {
        asio_task_unlock();
    }

    return res;
}

uint8_t *asio_stream_dma_buf_ptr_get(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    ASIO_STREAM_ENTITY_T *entity;

    entity = asio_stream_entity_get(group, stream);

    return entity->cfg.buf_ptr;
}

uint32_t asio_stream_current_dma_addr_get(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    ASIO_STREAM_ENTITY_T *entity;
    uint32_t addr = 0;

    entity = asio_stream_entity_get(group, stream);

    // check if stream is already started
    if (entity->ctl.status == (ASIO_STATUS_ASIO_OPEN | ASIO_STATUS_STREAM_OPEN | ASIO_STATUS_STREAM_START)) {
        if (entity->dma_cfg.ch != DMA_CH_NONE) {
            if (stream == AUD_STREAM_PLAYBACK) {
                addr = dma_cx_get_addr_rd(entity->dma_cfg.ch);
            } else {
                addr = dma_cx_get_addr_wr(entity->dma_cfg.ch);
            }
        } else {
            ASIO_TRACE("%s:ch invalid\n", __func__);
        }
    }else {
        ASIO_TRACE("ERROR: %s, status:%d\n",__func__, entity->ctl.status);
    }

    return addr;
}

uint32_t asio_stream_current_dma_lli_cntr_get(AUD_STREAM_GROUP_T group, AUD_STREAM_T stream)
{
    ASIO_STREAM_ENTITY_T *entity;
    uint32_t lli_cntr = 0;

    entity = asio_stream_entity_get(group, stream);

    // check if stream is already started
    if (entity->ctl.status == (ASIO_STATUS_ASIO_OPEN | ASIO_STATUS_STREAM_OPEN | ASIO_STATUS_STREAM_START)) {
        if (entity->dma_cfg.ch != DMA_CH_NONE) {
            lli_cntr = dma_cx_get_lli_cntr(entity->dma_cfg.ch);
        } else {
            ASIO_TRACE("%s:ch invalid\n", __func__);
        }
    } else {
        ASIO_TRACE("ERROR: %s, status:%d\n",__func__, entity->ctl.status);
    }

    return lli_cntr;
}

void asio_task_priority_set(uint32_t priority)
{
    rtos_task_set_priority(asio_task_handle, priority);
}

uint32_t asio_task_priority_get(void)
{
    return rtos_task_get_priority(asio_task_handle);
}

uint32_t asio_task_default_priority_get(void)
{
    return TASK_PRIORITY_ASIO;
}

void asio_task_priority_reset(void)
{
    rtos_task_set_priority(asio_task_handle, TASK_PRIORITY_ASIO);
}

void asio_init(void)
{
    if (asio_inited)
        return;

    int res = 0;

    //hwp_asdioMst->cclk_ctrl =  ASDIO_MST_CCLK_CTRL_UPDATE | ASDIO_MST_CCLK_OUT_INV | ASDIO_MST_CCLK_SMPL_INV;

    // clk en
#if PLF_AIC8800
    cpusysctrl_hclkme_set(CSC_HCLKME_DMA_EN_BIT | CSC_HCLKME_VPC_EN_BIT);
    cpusysctrl_pclkme_set(CSC_PCLKME_I2CM_EN_BIT);
    cpusysctrl_oclkme_set(CSC_OCLKME_AUDIO_PROC_EN_BIT | CSC_OCLKME_BCK0_EN_BIT | CSC_OCLKME_BCK1_EN_BIT);
#elif PLF_AIC8800MC
    cpusysctrl_hclkme_set(CPU_SYS_CTRL_HCLK_DMA_MANUAL_ENABLE | CPU_SYS_CTRL_HCLK_AUD_PROC_MANUAL_ENABLE);
    //cpusysctrl_pclkme_set(CPU_SYS_CTRL_PCLK_I2CM_MANUAL_ENABLE);
    cpusysctrl_oclkme_set(CPU_SYS_CTRL_OTHERS_AUDIO_PROC_MANUAL_ENABLE | CPU_SYS_CTRL_OTHERS_BCK_0_MANUAL_ENABLE | CPU_SYS_CTRL_OTHERS_BCK_1_MANUAL_ENABLE);
#elif PLF_AIC8800M40
    cpusysctrl_hclkme_set(CPU_SYS_CTRL_HCLK_DMA_MANUAL_ENABLE | CPU_SYS_CTRL_HCLK_AUD_PROC_MANUAL_ENABLE);
    //cpusysctrl_pclkme_set(CPU_SYS_CTRL_PCLK_I2CM_MANUAL_ENABLE);
    cpusysctrl_oclkme_set(CPU_SYS_CTRL_OTHERS_AUDIO_PROC_MANUAL_ENABLE | CPU_SYS_CTRL_OTHERS_BCK_0_MANUAL_ENABLE | CPU_SYS_CTRL_OTHERS_BCK_1_MANUAL_ENABLE);
#endif

#if (PLF_AIC8800 && PLF_HW_FPGA)
    //If I2S in master chip was used, I2C in master chip must be used as well
    hwp_audProc->spdif_userdata_0 |= (0x01UL << 0);
#endif

    audio_proc_i2s_mclk_config();

#if (PLF_PMIC && !PLF_PMIC_VER_AUD && PLF_EXT_AIC1000)
    aic1000_i2s_idx = audio_config_ext_aic1000_i2s_idx_get();
    ASSERT_ERR(aic1000_i2s_idx < 2);
#endif

    audio_proc_init();

    res = asio_open();
    if (0 == res) {
        ASIO_TRACE("asio task init success\n");
    } else {
        ASIO_TRACE("asio task init fail\n");
    }

    asio_src_param_clear();

    asio_inited = true;
}

