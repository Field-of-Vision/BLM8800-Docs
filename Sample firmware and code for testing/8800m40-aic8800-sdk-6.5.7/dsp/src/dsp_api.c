/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "reg_ipc_app.h"
#include "reg_ipc_emb.h"
#include "reg_ipc_mutex.h"
#include "reg_ipc_comreg.h"
#include "co_math.h"
#include "co_list.h"
#include "co_pool.h"
#include "dsp_event.h"
#include "dsp_api.h"
#include "dsp_image.h"
#include "dma_api.h"
#include "dbg_assert.h"
#include "dbg.h"

#define __SHARED_DSP __attribute__((section("SHAREDDSP")))

#define IPC_DSP_A2E_MSG_POS        24
#define IPC_DSP_A2E_MSG_BIT        CO_BIT(IPC_DSP_A2E_MSG_POS)
#define IPC_DSP_A2E_DATA_POS       25
#define IPC_DSP_A2E_DATA_BIT       CO_BIT(IPC_DSP_A2E_DATA_POS)
#define IPC_DSP_A2E_MSG_ACK_POS    26
#define IPC_DSP_A2E_MSG_ACK_BIT    CO_BIT(IPC_DSP_A2E_MSG_ACK_POS)
#define IPC_DSP_A2E_DATA_ACK_POS   27
#define IPC_DSP_A2E_DATA_ACK_BIT   CO_BIT(IPC_DSP_A2E_DATA_ACK_POS)

#define IPC_DSP_E2A_MSG_POS        24
#define IPC_DSP_E2A_MSG_BIT        CO_BIT(IPC_DSP_E2A_MSG_POS)
#define IPC_DSP_E2A_DATA_POS       25
#define IPC_DSP_E2A_DATA_BIT       CO_BIT(IPC_DSP_E2A_DATA_POS)
#define IPC_DSP_E2A_MSG_ACK_POS    26
#define IPC_DSP_E2A_MSG_ACK_BIT    CO_BIT(IPC_DSP_E2A_MSG_ACK_POS)
#define IPC_DSP_E2A_DATA_ACK_POS   27
#define IPC_DSP_E2A_DATA_ACK_BIT   CO_BIT(IPC_DSP_E2A_DATA_ACK_POS)

/// 3-part macro to function/variable/enum string
#define M2STR_P3_I(p0,p1,p2)    p0##p1##p2
#define M2STR_P3(p0,p1,p2)      M2STR_P3_I(p0, p1, p2)

/// IPC IRQ selection
#define IPC_IRQ_SELECT(ipc,idx)  M2STR_P3(ipc_emb2app, ipc, _sel_setf)(idx)

#define DMA_CH_DSP_A2E           DMA_CHANNEL_SDMMC_TX
#define DMA_CH_DSP_E2A           DMA_CHANNEL_SDMMC_RX

__SHARED_DSP static struct dsp_ipc_env_tag dsp_ipc_env;

static bool dsp_inited = false;

static uint16_t dsp_a2e_msg_seq = 0;
static uint16_t dsp_a2e_data_seq = 0;

#ifdef CFG_RTOS
static rtos_dsp_notify_cb_t dsp_notify_cb = NULL;
#endif

void dsp_init(void)
{
    TRACE("dsp init start\n");

    if (dsp_inited == true) {
        return;
    }

    dsp_event_init();
    dsp_event_callback_set(DSP_EVENT_MSG, dsp_msg_handler);
    dsp_event_callback_set(DSP_EVENT_DATA, dsp_data_handler);

    IPC_IRQ_SELECT(IPC_DSP_E2A_MSG_POS, 1);
    IPC_IRQ_SELECT(IPC_DSP_E2A_DATA_POS, 1);
    IPC_IRQ_SELECT(IPC_DSP_E2A_MSG_ACK_POS, 1);
    IPC_IRQ_SELECT(IPC_DSP_E2A_DATA_ACK_POS, 1);

    ipc_emb2app_ack_clear(IPC_DSP_E2A_MSG_BIT | IPC_DSP_E2A_DATA_BIT | IPC_DSP_E2A_MSG_ACK_BIT | IPC_DSP_E2A_DATA_ACK_BIT);
    ipc_emb2app_unmask_set(IPC_DSP_E2A_MSG_BIT | IPC_DSP_E2A_DATA_BIT | IPC_DSP_E2A_MSG_ACK_BIT | IPC_DSP_E2A_DATA_ACK_BIT);

    NVIC_SetPriority(WCN2MCU1_IRQn, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(WCN2MCU1_IRQn);

    dsp_image_load(0x100000, false, DMA_CH_DSP_A2E, true);
    dsp_launch(0x100000);

    dsp_inited = true;

    TRACE("dsp init done\n");
}

bool dsp_ipc_env_lock(void)
{
    return ipc_mutex_get(IPC_MUTEX_ID_DSP_IPC_ENV);
}

void dsp_ipc_env_unlock(void)
{
    ipc_mutex_set(IPC_MUTEX_ID_DSP_IPC_ENV, 1);
}

struct dsp_msg_elt *dsp_a2e_msg_malloc(void)
{
    struct dsp_msg_elt *msg = NULL;

    while (!dsp_ipc_env_lock());
    msg = (struct dsp_msg_elt *)co_list_pop_front(&dsp_ipc_env.a2e_msg_free);
    dsp_ipc_env_unlock();

    return msg;
}

void dsp_a2e_msg_free(struct dsp_msg_elt *msg)
{
    while (!dsp_ipc_env_lock());
    co_list_push_back(&dsp_ipc_env.a2e_msg_free, &msg->hdr);
    dsp_ipc_env_unlock();
}

void dsp_e2a_msg_free(struct dsp_msg_elt *msg)
{
    while (!dsp_ipc_env_lock());
    co_list_push_back(&dsp_ipc_env.e2a_msg_free, &msg->hdr);
    dsp_ipc_env_unlock();
}

struct dsp_data_elt *dsp_a2e_data_malloc(uint16_t id)
{
    struct dsp_data_elt *data = NULL;

    while (!dsp_ipc_env_lock());
    uint32_t cnt = co_list_cnt(&dsp_ipc_env.a2e_data_free);
    for (int i = 0; i < cnt; i++) {
        data = (struct dsp_data_elt *)co_list_pop_front(&dsp_ipc_env.a2e_data_free);
        if (data == NULL) {
            break;
        } else {
            if (data->id == id) {
                data->len = 0;
                break;
            } else {
                co_list_push_back(&dsp_ipc_env.a2e_data_free, &data->hdr);
            }
        }
    }
    dsp_ipc_env_unlock();

    return data;
}

void dsp_a2e_data_free(struct dsp_data_elt *data)
{
    while (!dsp_ipc_env_lock());
    co_list_push_back(&dsp_ipc_env.a2e_data_free, &data->hdr);
    dsp_ipc_env_unlock();
}

void dsp_e2a_data_free(struct dsp_data_elt *data)
{
    while (!dsp_ipc_env_lock());
    co_list_push_back(&dsp_ipc_env.e2a_data_free, &data->hdr);
    dsp_ipc_env_unlock();
}

int dsp_a2e_msg_build(struct dsp_msg_elt *msg, uint16_t id, void *param, uint16_t len)
{
    msg->id = id;
    msg->len = len;
    memcpy(&msg->param[0], param, len);

    return 0;
}

int dsp_a2e_data_build(struct dsp_data_elt *data, uint8_t *buf, uint16_t offset, uint16_t len, bool use_dma)
{
    if (use_dma) {
        dma_desc_t dma_desc0;
        dma_desc0.SAR = (uint32_t)buf;
        dma_desc0.DAR = (uint32_t)(data->data_ptr + offset);
        dma_desc_length_set(&dma_desc0, len);
        dma_desc0.LNAR = (uint32_t)0;
        dma_push(&dma_desc0, &dma_desc0, DMA_CH_DSP_A2E);
        dma_lli_poll(DMA_CH_DSP_A2E);
        dma_ch_int_clear(DMA_CH_DSP_A2E);
    } else {
        memcpy((void *)(data->data_ptr + offset), (void *)buf, len);
    }

    data->len += len;

    return 0;
}

int dsp_e2a_data_copy(uint8_t *dst, uint8_t *src, uint16_t len, bool use_dma)
{
    if (use_dma) {
        dma_desc_t dma_desc0;
        dma_desc0.SAR = (uint32_t)src;
        dma_desc0.DAR = (uint32_t)dst;
        dma_desc_length_set(&dma_desc0, len);
        dma_desc0.LNAR = (uint32_t)0;
        dma_push(&dma_desc0, &dma_desc0, DMA_CH_DSP_E2A);
        dma_lli_poll(DMA_CH_DSP_E2A);
        dma_ch_int_clear(DMA_CH_DSP_E2A);
    } else {
        memcpy((void *)dst, (void *)src, len);
    }

    return 0;
}

int dsp_a2e_msg_send(struct dsp_msg_elt *msg)
{
    while (!dsp_ipc_env_lock());
    msg->seq = dsp_a2e_msg_seq;
    dsp_a2e_msg_seq++;
    co_list_push_back(&dsp_ipc_env.a2e_msg_sent, &msg->hdr);
    dsp_ipc_env.a2e_msg_cnt++;
    dsp_ipc_env_unlock();
    ipc_app2emb_trigger_set(IPC_DSP_A2E_MSG_BIT);

    return 0;
}

int dsp_a2e_data_send(struct dsp_data_elt *data)
{
    while (!dsp_ipc_env_lock());
    data->seq = dsp_a2e_data_seq;
    dsp_a2e_data_seq++;
    co_list_push_back(&dsp_ipc_env.a2e_data_sent, &data->hdr);
    dsp_ipc_env.a2e_data_cnt++;
    dsp_ipc_env_unlock();
    ipc_app2emb_trigger_set(IPC_DSP_A2E_DATA_BIT);

    return 0;
}

void dsp_msg_handler(void)
{
    TRACE("host msg handler\n");

    struct dsp_msg_elt msg_recv;
    struct dsp_msg_elt *msg_ptr = NULL;
    bool msg_valid = false;

    while (!dsp_ipc_env_lock());
    msg_ptr = (struct dsp_msg_elt *)co_list_pop_front(&dsp_ipc_env.e2a_msg_sent);
    if (msg_ptr != NULL) {
        msg_recv = *msg_ptr;
        dsp_ipc_env.a2e_msg_cnt--;
        co_list_push_back(&dsp_ipc_env.e2a_msg_free, &msg_ptr->hdr);
        msg_valid = true;
    }
    dsp_ipc_env_unlock();

    if (msg_valid) {
        TRACE("e2a_msg:%d %d %d\n", msg_recv.id, msg_recv.seq, msg_recv.len);
        switch (msg_recv.id) {
        case DSP_MSG_NULL: {
            //TODO
        }
        break;
        case DSP_MSG_SMLALD_56P: {
            //TODO
        }
        break;
        case DSP_MSG_RESET: {
            //TODO
        }
        break;
        case DSP_MSG_USER: {
            //TODO
        }
        break;
        default: {
        }
        break;
        }
    }

    while (!dsp_ipc_env_lock());
    GLOBAL_INT_DISABLE();
    if (!co_list_is_empty(&dsp_ipc_env.e2a_msg_sent)) {
        dsp_event_set(DSP_EVENT_MSG);
    } else {
        dsp_event_clear(DSP_EVENT_MSG);
    }
    GLOBAL_INT_RESTORE();
    dsp_ipc_env_unlock();
}

void dsp_data_handler(void)
{
    TRACE("host data handler\n");

    struct dsp_data_elt *data_recv = NULL;

    while (!dsp_ipc_env_lock());
    data_recv = (struct dsp_data_elt *)co_list_pop_front(&dsp_ipc_env.e2a_data_sent);
    if (data_recv != NULL) {
        dsp_ipc_env.e2a_data_cnt--;
    }
    dsp_ipc_env_unlock();

    if (data_recv != NULL) {
        TRACE("e2a_data:%d %d %d\n", data_recv->id, data_recv->seq, data_recv->len);
        switch (data_recv->id) {
        case DSP_DATA_NULL: {
            //TODO
        }
        break;
        case DSP_DATA_SMLALD_56P: {
            int64_t result;
            result = *((int64_t *)data_recv->data_ptr);
            TRACE("data_recv->data_ptr:%X\n", (uint32_t)data_recv->data_ptr);
            TRACE("SMLALD_56P result:%016X\n", result);
        }
        break;
        case DSP_DATA_USER: {
            //TODO
        }
        break;
        default: {
        }
        break;
        }

        while (!dsp_ipc_env_lock());
        co_list_push_back(&dsp_ipc_env.e2a_data_free, &data_recv->hdr);
        dsp_ipc_env_unlock();
    }

    while (!dsp_ipc_env_lock());
    GLOBAL_INT_DISABLE();
    if (!co_list_is_empty(&dsp_ipc_env.e2a_data_sent)) {
        dsp_event_set(DSP_EVENT_DATA);
    } else {
        dsp_event_clear(DSP_EVENT_DATA);
    }
    GLOBAL_INT_RESTORE();
    dsp_ipc_env_unlock();
}

void WCN2MCU1_IRQHandler(void)
{
    uint32_t stat = ipc_emb2app_status_get();

    if (stat & IPC_DSP_E2A_MSG_BIT) {
        ipc_emb2app_ack_clear(IPC_DSP_E2A_MSG_BIT);
        dsp_event_set(DSP_EVENT_MSG);
    } else if (stat & IPC_DSP_E2A_DATA_BIT) {
        ipc_emb2app_ack_clear(IPC_DSP_E2A_DATA_BIT);
        dsp_event_set(DSP_EVENT_DATA);
    } else if (stat & IPC_DSP_E2A_MSG_ACK_BIT) {
        ipc_emb2app_ack_clear(IPC_DSP_E2A_MSG_ACK_BIT);
        //TODO
    } else if (stat & IPC_DSP_E2A_DATA_ACK_BIT) {
        ipc_emb2app_ack_clear(IPC_DSP_E2A_DATA_ACK_BIT);
        //TODO
    }

#ifdef CFG_RTOS
    if (dsp_notify_cb) {
        dsp_notify_cb(true);
    }
#endif
}

void dsp_schedule(void)
{
    dsp_event_schedule();
}

#ifdef CFG_RTOS
void dsp_ntf_register(rtos_dsp_notify_cb_t notify_cb)
{
    dsp_notify_cb = notify_cb;
}
#endif /* CFG_RTOS */

