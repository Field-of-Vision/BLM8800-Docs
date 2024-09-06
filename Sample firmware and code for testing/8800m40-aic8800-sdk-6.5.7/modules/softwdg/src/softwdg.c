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

/**
 * Includes
 */
#include "rtos_al.h"
#include "wdt_api.h"
#include "softwdg.h"
#include "rtos.h"
#include "dbg.h"
#include "hw_cfg.h"
/**
 * Macros
 */
// wdt timeout in second
#ifndef WDT_TIMEOUT_SEC
#define WDT_TIMEOUT_SEC     (SOFTWDG_BASE_TU / 1000 * 16)
#endif
/**
 * TypeDefs
 */

/**
 * Variables
 */
softwdg_env_t softwdg_env = {{NULL,},};

/**
 * Functions
 */

static void softwdg_schedule(void)
{
    struct co_list_hdr *list_hdr = co_list_pick(&softwdg_env.list);
    while (list_hdr != NULL) {
        softwdg_node_t *node = (softwdg_node_t *)list_hdr;
        if (node->max) {
            node->cnt++;
            if (node->cnt > node->max) {
                dbg("softwdg %s timedout! max=%d, cnt=%d\n", node->name, node->max, node->cnt);
                if (node->cb) {
                    node->cb();
                }
            }
        }
        list_hdr = co_list_next(list_hdr);
    }
}

static RTOS_TASK_FCT(softwdg_task_routine)
{
    for (;;) {
        rtos_task_suspend(SOFTWDG_BASE_TU); // loop every TU
        #if (SOFTWDG_DEBUG_EN)
        dbg("softwdg task loop\n");
        #endif
        wdt_kick(); // kick the hw wdt
        softwdg_schedule(); // check sw wdt
        if (softwdg_env.stop_flag) {
            break;
        }
    }
    // exit & delete the task
    rtos_task_delete(NULL);
}

void softwdg_task_init(void)
{
    co_list_init(&softwdg_env.list);
    softwdg_env.stop_flag = 0;
    // Create the softwdg task
    if (rtos_task_create(softwdg_task_routine, "SOFTWDG", SOFTWDG_TASK,
                         TASK_STACK_SIZE_SOFTWDG, NULL, TASK_PRIORITY_MAX, NULL)) {
        dbg("failed to create softwdg task\n");
        return;
    }
    wdt_init(WDT_TIMEOUT_SEC);
}

void softwdg_task_deinit(void)
{
    wdt_stop();
    softwdg_env.stop_flag = 1;
    if (!co_list_is_empty(&softwdg_env.list)) {
        struct co_list_hdr *list_hdr = co_list_pick(&softwdg_env.list);
        dbg("warning, softwdg list is not empty, nodes:\n");
        while (list_hdr != NULL) {
            softwdg_node_t *node = (softwdg_node_t *)list_hdr;
            dbg(" %s\n", node->name);
            list_hdr = co_list_next(list_hdr);
        }
    }
}

int softwdg_register(softwdg_node_t *node)
{
    if (node == NULL) {
        return -1;
    }
    if (node->max == 0) {
        return -2;
    }
    if (node->name == NULL) {
        return 1;
    }
    co_list_push_back(&softwdg_env.list, &node->hdr);
    return 0;
}

int softwdg_unregister(softwdg_node_t *node)
{
    if (node == NULL) {
        return -1;
    }
    if (!co_list_find(&softwdg_env.list, &node->hdr)) {
        return -2;
    }
    co_list_extract(&softwdg_env.list, &node->hdr);
    return 0;
}

void softwdg_kick(softwdg_node_t *node)
{
    if (node) {
        node->cnt = 0;
    }
}
