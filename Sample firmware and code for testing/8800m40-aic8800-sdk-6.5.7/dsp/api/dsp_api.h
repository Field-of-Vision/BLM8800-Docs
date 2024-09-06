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
#ifndef _DSP_API_H_
#define _DSP_API_H_

#include <stdint.h>
#include <stdbool.h>
#include "co_list.h"

#define DSP_MSG_MAX_LEN    32
#define DSP_MSG_MAX_NB     4
#define DSP_DATA_MAX_NB    8

enum dsp_msg_id {
    DSP_MSG_NULL = 0,
    DSP_MSG_SMLALD_56P,
    DSP_MSG_RESET,
    DSP_MSG_USER = 0x100,
};

enum dsp_data_id {
    DSP_DATA_NULL = 0,
    DSP_DATA_SMLALD_56P,
    DSP_DATA_USER = 0x100,
};

struct dsp_msg_smlald_56p {
    uint16_t a2e_data_len;//input data len, 56 int16_t x + 56 int16_t y
    uint16_t e2a_data_len;//result len, 1 int64_t
};

struct dsp_msg_elt {
    /// List header
    struct co_list_hdr hdr;
    uint16_t id;
    uint16_t seq;
    uint16_t len;
    uint8_t param[DSP_MSG_MAX_LEN];
};

struct dsp_data_elt {
    /// List header
    struct co_list_hdr hdr;
    uint16_t id;
    uint16_t seq;
    uint16_t len;
    uint16_t max_len;
    uint8_t *data_ptr;
};

struct dsp_ipc_env_tag {
    struct co_list a2e_msg_sent;

    struct co_list a2e_msg_free;

    struct co_list a2e_data_sent;

    struct co_list a2e_data_free;

    struct co_list e2a_msg_sent;

    struct co_list e2a_msg_free;

    struct co_list e2a_data_sent;

    struct co_list e2a_data_free;

    uint16_t a2e_msg_cnt;

    uint16_t a2e_data_cnt;

    uint16_t e2a_msg_cnt;

    uint16_t e2a_data_cnt;
};

#ifdef CFG_RTOS
/// Pointer to callback function
typedef void (*rtos_dsp_notify_cb_t)(bool isr);
#endif

void dsp_init(void);
bool dsp_ipc_env_lock(void);
void dsp_ipc_env_unlock(void);
struct dsp_msg_elt *dsp_a2e_msg_malloc(void);
void dsp_a2e_msg_free(struct dsp_msg_elt *msg);
void dsp_e2a_msg_free(struct dsp_msg_elt *msg);
struct dsp_data_elt *dsp_a2e_data_malloc(uint16_t id);
void dsp_a2e_data_free(struct dsp_data_elt *data);
void dsp_e2a_data_free(struct dsp_data_elt *data);
int dsp_a2e_msg_build(struct dsp_msg_elt *msg, uint16_t id, void *param, uint16_t len);
int dsp_a2e_data_build(struct dsp_data_elt *data, uint8_t *buf, uint16_t offset, uint16_t len, bool use_dma);
int dsp_e2a_data_copy(uint8_t *dst, uint8_t *src, uint16_t len, bool use_dma);
int dsp_a2e_msg_send(struct dsp_msg_elt *msg);
int dsp_a2e_data_send(struct dsp_data_elt *data);
void dsp_msg_handler(void);
void dsp_data_handler(void);
void dsp_schedule(void);
void dsp_launch(uint32_t addr);
void dsp_hw_reset(void);
#ifdef CFG_RTOS
void dsp_ntf_register(rtos_dsp_notify_cb_t notify_cb);
#endif

#endif /* _DSP_API_H_ */
