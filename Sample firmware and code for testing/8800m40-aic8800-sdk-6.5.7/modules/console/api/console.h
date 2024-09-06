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
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "arch.h"
#include "lnx_list.h"
#include "stdio_uart.h"
#include "dbg.h"
#include <stdbool.h>

#define console_putc(args...)       stdio_uart_putc(args)
#define console_puts(args...)       stdio_uart_puts(args)
#define console_putf(args...)       dbg(args)
#define CONSOLE_CRITICAL_START()    GLOBAL_INT_DISABLE()
#define CONSOLE_CRITICAL_END()      GLOBAL_INT_RESTORE()

#define CONSOLE_GLOBAL_DEBUG_MODE   1

#define CONFIG_SYS_CBSIZE   64
#define CONFIG_SYS_PROMPT   "aic> "

#if !defined(CFG_RAM_OPT)
#if (PLF_AIC8800M40) && defined(CFG_BLE_STACK) && (PLF_WIFI_STACK)
#define CONFIG_CMDTBL_SIZE  90
#else
#define CONFIG_CMDTBL_SIZE  48
#endif
#define CONFIG_CMDBUF_SIZE  4
#else
#if defined(CFG_BLE_STACK)
#define CONFIG_CMDTBL_SIZE  30
#else
#define CONFIG_CMDTBL_SIZE  10
#endif
#define CONFIG_CMDBUF_SIZE  2
#endif

typedef struct {
    struct list_head entry;
    char buffer[CONFIG_SYS_CBSIZE];
} cmd_buf_node_t;

typedef enum {
    ERR_NONE        =  0,
    ERR_UNKNOWN_CMD = -1,
    ERR_WRONG_ARGS  = -2,
    ERR_CMD_ABORT   = -3,
    ERR_CMD_FAIL    = -4,
} CONSOLE_ERR_CODE_T;

#ifdef CFG_RTOS
/// Pointer to callback function
typedef void (*rtos_notify_cb_t)(bool isr);
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern volatile bool cmd_exe_in_irq;

void console_init(void);
void console_putc(char c);
void console_puts(const char *s);
int console_handle_char(char ch);
void console_schedule(void);
int console_cmd_add(const char *name, const char *usage, short minargs, short maxargs, int (*func)(int, char * const []));
unsigned int console_cmd_strtoul(const char *cp, char **endp, unsigned int base);
unsigned int console_buf_empty(void);
#ifdef CFG_RTOS
void console_ntf_register(rtos_notify_cb_t notify_cb);
#endif /* CFG_RTOS */
#if CONSOLE_GLOBAL_DEBUG_MODE
void console_dbgmode_enter_exit(void);
#endif /* CONSOLE_GLOBAL_DEBUG_MODE */

#ifdef __cplusplus
}
#endif


#endif /* _CONSOLE_H_ */
