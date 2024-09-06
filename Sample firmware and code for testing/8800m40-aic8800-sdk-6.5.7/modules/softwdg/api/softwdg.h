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
#ifndef _SOFTWDG_H_
#define _SOFTWDG_H_

/**
 * Includes
 */
#include "co_list.h"

/**
 * Macros
 */
// Base time unit in ms
#define SOFTWDG_BASE_TU         2000
// TU count to ms value
#define SOFTWDG_TUCNT2MS(cnt)   (SOFTWDG_BASE_TU * cnt)
// Debug softwdg with more log
#define SOFTWDG_DEBUG_EN        0

/**
 * TypeDefs
 */

typedef struct {
    struct co_list list;
    uint8_t stop_flag;
} softwdg_env_t;

typedef void (*softwdt_callback_t)(void);

typedef struct {
    struct co_list_hdr hdr; // must be first element
    char *name;
    uint16_t cnt; // current TU count
    uint16_t max; // max TU count
    softwdt_callback_t cb; // callback function
} softwdg_node_t;

/**
 * Functions
 */

/**
 * @brief       Init softwdg task
 */
void softwdg_task_init(void);

/**
 * @brief       De-init softwdg task
 */
void softwdg_task_deinit(void);

/**
 * @brief       Register softwdg
 * @param[in]   node with necessary info
 * @return      0 if succeeded, else non-zero
 */
int softwdg_register(softwdg_node_t *node);

/**
 * @brief       Un-register softwdg
 * @param[in]   node with necessary info
 * @return      0 if succeeded, else non-zero
 */
int softwdg_unregister(softwdg_node_t *node);

/**
 * @brief       Kick softwdg
 * @param[in]   node with necessary info
 */
void softwdg_kick(softwdg_node_t *node);

#endif /* _SOFTWDG_H_ */
