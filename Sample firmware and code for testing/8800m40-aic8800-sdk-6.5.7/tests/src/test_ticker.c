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
#include "us_ticker_api.h"
#include "lp_ticker_api.h"
#include "time_api.h"
#include "dbg.h"
#include "console.h"

#ifdef CFG_RTOS
#include "rtos_al.h"
#endif /* CFG_RTOS */

#ifdef CFG_TEST_TICKER

/*
 * MACROS
 ****************************************************************************************
 */
#define UART_PRINT              dbg

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
typedef void (*event_cb_t)(uint32_t param);

typedef struct {
    ticker_event_t evt;
    event_cb_t cb;
    uint32_t param;
} event_info_t;

event_info_t g_us_tick_ei;
event_info_t g_lp_tick_ei;

/*
 * FUNCTIONS
 ****************************************************************************************
 */
void common_tick_evt_hndlr(uint32_t id)
{
    event_info_t *evt_info = (event_info_t *)id;
    if (evt_info->cb) {
        evt_info->cb(evt_info->param);
    }
}

void us_tick_evt_cb(uint32_t param)
{
    const ticker_data_t *us_tick_d = get_us_ticker_data();
    uint32_t time_us3 = ticker_read(us_tick_d);
    UART_PRINT("EventHandler: param=%X, time_us3=%dus\n", param, time_us3);
    #ifdef CFG_RTOS
    UART_PRINT("Systick=%dms\n", rtos_now(true));
    #endif /* CFG_RTOS */
}

void lp_tick_evt_cb(uint32_t param)
{
    const ticker_data_t *lp_tick_d = get_lp_ticker_data();
    uint32_t time_us3 = ticker_read(lp_tick_d);
    UART_PRINT("[LP] EventHandler: param=%X, time_us3=%dus\n", param, time_us3);
    #ifdef CFG_RTOS
    UART_PRINT("[LP] Systick=%dms\n", rtos_now(true));
    #endif /* CFG_RTOS */
}

void test_timer_handler(void const *param)
{
    const ticker_data_t *us_tick_d = get_us_ticker_data();
    const ticker_data_t *lp_tick_d = get_lp_ticker_data();
    uint32_t us_time_us = ticker_read(us_tick_d);
    uint32_t lp_time_us = ticker_read(lp_tick_d);
    struct tm tmr = {0,};
    uint32_t sec, usec;
    aic_time_get(SINCE_EPOCH, &sec, &usec);
    uint32_t rtos_tick = rtos_now(false);
    time_t gmt = sec + (usec + 500000) / 1000000;
    gmtime_offset_r(&gmt,&tmr,8);
    dbg("Current time = %d-%02d-%02d %02d:%02d:%02d %d\n",tmr.tm_year+YEAR0,tmr.tm_mon+1,tmr.tm_mday,
            tmr.tm_hour,tmr.tm_min,tmr.tm_sec,(uint32_t)gmt);
    dbg("rtos tick: %d, us: %d, lp: %d\n", rtos_tick, us_time_us, lp_time_us);
}

void test_timer_start(void)
{
    struct tm tmr = {0,};
    time_t gmt;
    tmr.tm_year = 2023-YEAR0;
    tmr.tm_mon = 4-1;
    tmr.tm_mday = 6;
    tmr.tm_hour = 20;
    tmr.tm_min = 59;
    tmr.tm_sec = 10;
    gmt = mk_gmtime_offset_r(&tmr, 8);
    aic_time_update((uint32_t)gmt, 0);
    dbg("Update time = %d-%02d-%02d %02d:%02d:%02d %d\n",tmr.tm_year+YEAR0,tmr.tm_mon+1,tmr.tm_mday,
            tmr.tm_hour,tmr.tm_min,tmr.tm_sec,(uint32_t)gmt);
    TimerHandle_t ttt = rtos_timer_create("tick_timer", 1000, pdTRUE, NULL,
                      (TimerCallbackFunction_t)test_timer_handler);
    if (ttt) {
        rtos_timer_start(ttt,0,false);
    }
}

int cmd_timer_start(int argc, char * const argv[])
{
    test_timer_start();
    return 0;
}

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void ticker_test(void)
{
    const ticker_data_t *us_tick_d;
    const ticker_data_t *lp_tick_d;
    ticker_event_t *us_tick_e = &(g_us_tick_ei.evt);
    ticker_event_t *lp_tick_e = &(g_lp_tick_ei.evt);
    uint32_t time_us0, time_us1, time_us2;
    int i;

    UART_PRINT("\nTicker test start\n");

    console_cmd_add("start",  "- start timer", 1, 1, cmd_timer_start);

    #ifdef CFG_RTOS
    UART_PRINT("Systick:%dms\n", rtos_now(false));
    #endif /* CFG_RTOS */

    // init event info, get data & set handler
    g_us_tick_ei.cb = us_tick_evt_cb;
    g_us_tick_ei.param = 0xA5A5C3C3;
    us_tick_d = get_us_ticker_data();
    ticker_set_handler(us_tick_d, common_tick_evt_hndlr);
    g_lp_tick_ei.cb = lp_tick_evt_cb;
    g_lp_tick_ei.param = 0xB6B6D4D4;
    lp_tick_d = get_lp_ticker_data();
    ticker_set_handler(lp_tick_d, common_tick_evt_hndlr);

    // measure time
    time_us0 = ticker_read(us_tick_d);
    for (i = 0; i < 0x3FF; i++) {  // delay: 0x3FF(about 120~170us)
        __asm("nop");
        __asm("nop");
    }
    time_us1 = ticker_read(us_tick_d);
    // insert event
    time_us2 = time_us1 + 50000;
    ticker_insert_event(us_tick_d, us_tick_e, time_us2, (uint32_t)(&g_us_tick_ei));
    UART_PRINT("time_us0=%dus, time_us1=%dus\n", time_us0, time_us1);
    UART_PRINT("InsertEvent: time_us2=%dus\n", time_us2);

    time_us0 = ticker_read(lp_tick_d);
    for (i = 0; i < 0x3FF; i++) {  // delay: 0x3FF(about 120~170us)
        __asm("nop");
        __asm("nop");
    }
    time_us1 = ticker_read(lp_tick_d);
    time_us2 = time_us1 + 50000;
    ticker_insert_event(lp_tick_d, lp_tick_e, time_us2, (uint32_t)(&g_lp_tick_ei));
    UART_PRINT("[LP] time_us0=%dus, time_us1=%dus\n", time_us0, time_us1);
    UART_PRINT("[LP] InsertEvent: time_us2=%dus\n", time_us2);

    #ifdef CFG_RTOS
    rtos_task_suspend(2000); // make sure tick evt hdlr executed
    #endif

    ticker_free(us_tick_d);

    ticker_set_handler(us_tick_d, common_tick_evt_hndlr);
    time_us1 = ticker_read(us_tick_d);
    // insert event
    time_us2 = time_us1 + 100000;
    ticker_remove_event(us_tick_d, us_tick_e);
    ticker_insert_event(us_tick_d, us_tick_e, time_us2, (uint32_t)(&g_us_tick_ei));
    UART_PRINT("time_us1=%dus\n", time_us1);
    UART_PRINT("InsertEvent: time_us2=%dus\n", time_us2);

    UART_PRINT("\nTicker test done\n\n");
}

#endif /* CFG_TEST_TICKER */
