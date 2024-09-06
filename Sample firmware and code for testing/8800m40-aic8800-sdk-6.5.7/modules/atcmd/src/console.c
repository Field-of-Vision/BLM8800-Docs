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
#include "console.h"
#include "command.h"
#include "stdio_uart.h"

#if CONSOLE_GLOBAL_DEBUG_MODE
#define CMDISR_SUPER_STR    "#6*"
#endif /* CONSOLE_GLOBAL_DEBUG_MODE */

static char console_buffer[CONFIG_SYS_CBSIZE];  /* console I/O buffer   */

static cmd_buf_node_t cmd_buf_tab[CONFIG_CMDBUF_SIZE];
static struct list_head cmd_free_list;
static struct list_head cmd_pend_list;

static cmd_tbl_t cmd_tbl_list[CONFIG_CMDTBL_SIZE];
static unsigned int cmd_tbl_curidx = 2;

volatile bool cmd_exe_in_irq = false;
#ifdef CFG_RTOS
static rtos_notify_cb_t console_notify_cb = NULL;
#endif

static void console_irq_handler(void)
{
    bool cmd_valid = false;
    while (stdio_uart_get_rx_count()) {
        unsigned char c = (unsigned char)stdio_uart_getc();
        if (console_handle_char(c) > 0) {
            cmd_valid = true;
        }
    }

    if (cmd_valid) {
        /* if cmd_exe_in_irq was true, we check and execute commands here */
        if (cmd_exe_in_irq) {
            console_schedule();
        }
#ifdef CFG_RTOS
        else if (console_notify_cb) {
            console_notify_cb(true);
        }
#endif /* CFG_RTOS */
    }
}

int do_help(int argc, char * const argv[])
{
    int idx;
    const cmd_tbl_t *cmdtemp = &cmd_tbl_list[0];

    for (idx = 0; idx < cmd_tbl_curidx; idx++) {
        if (cmdtemp[idx].usage) {
            ATCMD_RESP(ATCMD_PREFIX "%s:\t%s\n", cmdtemp->name, cmdtemp->usage);
        }
    }
    return ERR_NONE;
}

int do_echo(int argc, char * const argv[])
{
    unsigned int en;

    if(argc < 2) {
        return ERR_WRONG_ARGS;
    }

    en = console_cmd_strtoul(argv[1], NULL, 0);
    if (en) {
        cmd_echo_en = 1;
    } else {
        cmd_echo_en = 0;
    }

    return ERR_NONE;
}

static cmd_tbl_t cmd_tbl_list[] = {
    {
        "H",    "- help info",
        1, 1,   do_help
    },
    {
        "ECHO", "0/1 - Cmd echo enable/disable",
        2, 2,   do_echo
    },
};

void console_init(void)
{
    int i;
    if (!stdio_uart_inited) {
        stdio_uart_init();
    }

    CONSOLE_CRITICAL_START();
    INIT_LIST_HEAD(&cmd_free_list);
    INIT_LIST_HEAD(&cmd_pend_list);
    for (i = 0; i < CONFIG_CMDBUF_SIZE; i++) {
        cmd_buf_node_t *buf = &(cmd_buf_tab[i]);
        list_add(&buf->entry, &cmd_free_list);
    }
    CONSOLE_CRITICAL_END();

    register_stdio_uart_rx_function(console_irq_handler);
}

/**
 * called in isr
 */
int console_handle_char(char ch)
{
    int len = command_char2buffer(ch, console_buffer, 0);
    if (len >= 0) {
        if (len) {
            #if CONSOLE_GLOBAL_DEBUG_MODE
            if ((strlen(CMDISR_SUPER_STR) == len) && !strcmp(CMDISR_SUPER_STR, console_buffer)) {
                uint32_t regCTRL = __get_CONTROL();
                uint32_t regXPSR = __get_xPSR();
                uint32_t regPSP  = __get_PSP();
                uint32_t regMSP  = __get_MSP();
                uint32_t regPMSK = __get_PRIMASK();
                uint32_t regBPRI = __get_BASEPRI();
                console_putf("CONTROL=%08x, xPSR   =%08x\r\n"
                            "PSP    =%08x, MSP    =%08x\r\n"
                            "PRIMASK=%08x, BASEPRI=%08x\r\n",
                            regCTRL, regXPSR, regPSP, regMSP, regPMSK, regBPRI);
                if (regMSP) {
                    int32_t idx;
                    uint32_t addr = regMSP & ~0x0FUL;
                    console_puts("\r\nDumpMSP:");
                    for (idx = 0; idx < 64; idx++) {
                        if (!(addr & 0x0FUL)) {
                            console_putf("\r\n[%08x]:", addr);
                        }
                        console_putf(" %08X", *((uint32_t *)addr));
                        addr += 4;
                    }
                }
                if (regPSP) {
                    int32_t idx;
                    uint32_t addr = regPSP & ~0x0FUL;
                    console_puts("\r\nDumpPSP:");
                    for (idx = 0; idx < 64; idx++) {
                        if (!(addr & 0x0FUL)) {
                            console_putf("\r\n[%08x]:", addr);
                        }
                        console_putf(" %08X", *((uint32_t *)addr));
                        addr += 4;
                    }
                }
                len = 0;
                console_puts("\r\n" CONFIG_SYS_PROMPT);
                console_dbgmode_enter_exit();
            } else
            #endif /* CONSOLE_GLOBAL_DEBUG_MODE */
            if (len > 3 && !strncmp(ATCMD_PREFIX, console_buffer, 3)) {
                if (!list_empty(&cmd_free_list)) {
                    cmd_buf_node_t *buf = list_first_entry(&cmd_free_list, cmd_buf_node_t, entry);
                    strcpy(buf->buffer, &console_buffer[3]);
                    list_move_tail(&(buf->entry), &cmd_pend_list);
                } else {
                    console_puts("err: cmd_free_list empty\r\n");
                }
            } else if ((len == 2) && !strncmp(ATCMD_PREFIX, console_buffer, 2)) {
                ATCMD_RESP_OK();
                len = 0;
            } else {
                console_putf("invalid AT cmd,len=%d\r\n",len);
                console_putf(" %s,%s\r\n",ATCMD_PREFIX,console_buffer);
            }
        }
        command_char2buffer('0', console_buffer, CONFIG_SYS_PROMPT);
    }
    return len;
}

void console_schedule(void)
{
    cmd_buf_node_t *buf;

    CONSOLE_CRITICAL_START();
    buf = list_empty(&cmd_pend_list) ? NULL : list_first_entry(&cmd_pend_list, cmd_buf_node_t, entry);
    CONSOLE_CRITICAL_END();

    while (buf) {
        do {
            char *argv[CONFIG_SYS_MAXARGS + 1];    /* NULL terminated */
            int argc, ret;
            const cmd_tbl_t *cmdtp;
            /* separate into argv */
            argc = command_make_argv(buf->buffer, argv);
            if (argc == 0) {
                ATCMD_RESP_ERR(ERR_WRONG_ARGS);
                break;    /* no command at all */
            }
            /* Look up command in command table */
            cmdtp = command_find((const char *)argv[0], cmd_tbl_list, CONFIG_CMDTBL_SIZE);
            if (cmdtp == NULL) {
                ATCMD_RESP_ERR(ERR_UNKNOWN_CMD);
                break;
            }
            /* found - check min/max args */
            if ((argc > cmdtp->maxargs) || (argc < cmdtp->minargs)) {
                ATCMD_RESP_ERR(ERR_WRONG_ARGS);
                break;
            }
            /* If OK so far, then do the command */
            ret = command_call(cmdtp, argc, argv);
            if (ret != ERR_NONE) {
                ATCMD_RESP_ERR(ret);
            } else {
                ATCMD_RESP_OK();
            }
        } while (0);
        console_puts(CONFIG_SYS_PROMPT);

        CONSOLE_CRITICAL_START();
        list_move_tail(&(buf->entry), &cmd_free_list);
        buf = list_empty(&cmd_pend_list) ? NULL : list_first_entry(&cmd_pend_list, cmd_buf_node_t, entry);
        CONSOLE_CRITICAL_END();
    }
}

int console_cmd_add(const char *name, const char *usage, short minargs, short maxargs, int (*func)(int, char * const []))
{
    cmd_tbl_t *tmp_cmd;
    bool is_register = false;

    if(CONFIG_CMDTBL_SIZE <= cmd_tbl_curidx) {
        console_puts("No more cmds supported.\r\n");
        return -1;
    }

    for(uint8_t i=0;i<cmd_tbl_curidx;i++){
        cmd_tbl_t *check_cmd = &cmd_tbl_list[i];
        if(!strcmp(name,check_cmd->name)){
            is_register = true;
            console_putf("cmd %s is registered.\n", name);
        }
    }

    if(!is_register){
        tmp_cmd = &(cmd_tbl_list[cmd_tbl_curidx]);
        cmd_tbl_curidx++;
        tmp_cmd->name = name;
        tmp_cmd->usage = usage;
        tmp_cmd->minargs = minargs;
        tmp_cmd->maxargs = maxargs;
        tmp_cmd->cmd = func;
    }


    return 0;
}

unsigned int console_cmd_strtoul(const char *cp, char **endp, unsigned int base)
{
    return command_strtoul(cp, endp, base);
}

unsigned int console_buf_empty(void)
{
    int ret;
    CONSOLE_CRITICAL_START();
    ret = list_empty(&cmd_pend_list);
    CONSOLE_CRITICAL_END();
    return ret;
}

#ifdef CFG_RTOS
void console_ntf_register(rtos_notify_cb_t notify_cb)
{
    if (!console_notify_cb) {
        console_notify_cb = notify_cb;
    }
}
#endif /* CFG_RTOS */

#if CONSOLE_GLOBAL_DEBUG_MODE
#include "reg_stdio_uart.h"

void console_dbgmode_enter_exit(void)
{
    if (cmd_exe_in_irq) {
        NVIC_SetPriority(UART_IRQn, __NVIC_PRIO_LOWEST);
        cmd_exe_in_irq = false;
    } else {
        NVIC_SetPriority(UART_IRQn, 0x07UL);
        cmd_exe_in_irq = true;
    }
}
#endif /* CONSOLE_GLOBAL_DEBUG_MODE */
