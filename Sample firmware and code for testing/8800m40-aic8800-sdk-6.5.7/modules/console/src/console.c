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
#if PLF_PMIC
#include "pmic_api.h"
#if (PLF_AIC8800 && PLF_PMIC_VER_LITE && PLF_EXT_AIC1000)
#include "aic1000_psi_api.h"
#endif
#endif


#if CONSOLE_GLOBAL_DEBUG_MODE
#define CMDISR_SUPER_STR    "#6*"
#endif /* CONSOLE_GLOBAL_DEBUG_MODE */

static char console_buffer[CONFIG_SYS_CBSIZE];  /* console I/O buffer   */

static cmd_buf_node_t cmd_buf_tab[CONFIG_CMDBUF_SIZE];
static struct list_head cmd_free_list;
static struct list_head cmd_pend_list;

static cmd_tbl_t cmd_tbl_list[CONFIG_CMDTBL_SIZE];
#if (PLF_PMIC && PLF_AIC8800 && PLF_PMIC_VER_LITE && PLF_EXT_AIC1000)
static unsigned int cmd_tbl_curidx = 7;
#else
static unsigned int cmd_tbl_curidx = 5;
#endif

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
            console_putf("%s %s\r\n", cmdtemp[idx].name, cmdtemp[idx].usage);
        }
    }
    return 0;
}

static int get_rw_data_size(const char *arg)
{
    /* Check for a size specification .b or .h, otherwise use default size 4 (a word). */
    int len = strlen(arg);
    if ((len > 2) && (arg[len - 2] == '.')) {
        switch (arg[len - 1]) {
            case 'b': return 1;
            case 'h': return 2;
            default:  return -1;
        }
    }
    return 4;
}

int do_mem_read(int argc, char * const argv[])
{
    uint32_t addr, cnt;
    int size;
    bool ascii_on = false;

    addr = command_strtoul(argv[1], NULL, 16);
    if (argc > 2) {
        cnt = command_strtoul(argv[2], NULL, 0);
    } else {
        cnt = 1;
    }
    size = get_rw_data_size(argv[0]);
    if (size < 0) {
        console_putf("Unknown data size:%d\r\n", size);
        return -1;
    }

    /* Compatible with previous version which cnt always = 1 */
    if (cnt == 1) {
        #if (PLF_PMIC)
        if (IS_PMIC_MEM_ADDR(addr)) {
            addr &= ~(0x03UL);
            console_putf("[0x%08X] = 0x%08X\r\n", addr, PMIC_MEM_READ(addr));
        } else
        #endif
        if (size == 4) {
            console_putf("[0x%08lX] = 0x%08lX\r\n", addr, *((volatile uint32_t*)addr));
        } else if (size == 2) {
            console_putf("[0x%08lX] = 0x%04X\r\n", addr, *((volatile uint16_t*)addr));
        } else if (size == 1) {
            console_putf("[0x%08lX] = 0x%02X\r\n", addr, *((volatile uint8_t*)addr));
        }
        return 0;
    }

    if ((argv[0][0] == 'R') && (addr < AIC_AHB0_BASE)) {
        ascii_on = true;
    }
    dump_mem(addr, cnt, size, ascii_on);

    return 0;
}

int do_mem_write(int argc, char * const argv[])
{
    uint32_t addr, writeval, cnt;
    int size;

    size = get_rw_data_size(argv[0]);
    if (size < 0) {
        console_putf("Unknown data size:%d\r\n", size);
        return -1;
    }

    addr = command_strtoul(argv[1], NULL, 16);
    writeval = command_strtoul(argv[2], NULL, 16);
    if (argc > 3) {
        cnt = command_strtoul(argv[3], NULL, 0);
    } else {
        cnt = 1;
    }

    while (cnt--) {
        #if (PLF_PMIC)
    if (IS_PMIC_MEM_ADDR(addr)) {
            addr &= ~(0x03UL);
            console_putf("[0x%08X] = 0x%08lX\r\n", addr, writeval);
            PMIC_MEM_WRITE(addr, writeval);
        } else
        #endif
        if (size == 4) {
            console_putf("[0x%08lX] = 0x%08lX\r\n", addr, writeval);
            *((volatile uint32_t*)addr) = writeval;
        } else if (size == 2) {
            console_putf("[0x%08lX] = 0x%04X\r\n", addr, (uint16_t)writeval);
            *((volatile uint16_t*)addr) = (uint16_t)writeval;
        } else if (size == 1) {
            console_putf("[0x%08lX] = 0x%02X\r\n", addr, (uint8_t)writeval);
            *((volatile uint8_t*)addr) = (uint8_t)writeval;
        }
        addr += size;
    }

    return 0;
}

#if (PLF_PMIC && PLF_AIC8800 && PLF_PMIC_VER_LITE && PLF_EXT_AIC1000)
int do_amem_read(int argc, char * const argv[])
{
    uint32_t addr, cnt = 1;
    int size;

    addr = console_cmd_strtoul(argv[1], NULL, 16);

    if(argc > 2) {
        cnt = console_cmd_strtoul(argv[2], NULL, 0);
    }

    if (argc > 3) {
        size = console_cmd_strtoul(argv[3], NULL, 0);
        if ((4 != size) && (2 != size) && (1 != size)) {
            console_putf("Unknown data size:%d\n", size);
            return -2;
        }
    } else {
        size = 4;
    }

    if (!(IS_PMIC_MEM_ADDR(addr))) {
        return -3;
    }

    /* Compatible with previous version which cnt always = 1 */
    if(cnt == 1) {
        if (IS_PMIC_MEM_ADDR(addr)) {
            console_putf("[0x%08X] = 0x%08X\n", addr, psi_read_op(addr));
        }
        return 0;
    }

    dump_amem(addr, cnt, size, false);

    return 0;
}

int do_amem_write(int argc, char * const argv[])
{
    uint32_t addr;
    uint32_t value;

    addr = console_cmd_strtoul(argv[1], NULL, 16);
    console_putf("Addr  = 0x%08lX\n", addr);

    value = console_cmd_strtoul(argv[2], NULL, 16);
    console_putf("Value = 0x%08lX\n", value);

    if (IS_PMIC_MEM_ADDR(addr)) {
        psi_write_op(addr, value);
    } else {
        return -2;
    }
    console_putf("Write Done\n");

    return 0;
}
#endif

int do_dbg_severity_config(int argc, char * const argv[])
{
    int ret = 0;
    unsigned int func = 0;
    if (argc > 1) {
        func = command_strtoul(argv[1], NULL, 0);
    }
    if (func == 0) { // show curr
        console_putf("dbg sev: %d\n", dbg_get_severity());
    } else if (func == 1) { // config sev
        if (argc > 2) {
            unsigned int sev_idx = command_strtoul(argv[2], NULL, 0);
            if (sev_idx < DBG_SEV_IDX_MAX) {
                console_putf("Cfg dbg sev: %d\n", sev_idx);
                dbg_set_severity(sev_idx);
            } else {
                console_putf("invalid sev_idx:%d\n", sev_idx);
                ret = 1;
            }
        } else {
            console_putf("invalid args\n");
            ret = 2;
        }
    } else {
        console_putf("invalid func\n");
        ret = 3;
    }
    return ret;
}

int do_dbg_module_config(int argc, char * const argv[])
{
    int ret = 0;
    unsigned int func = 0;
    if (argc > 1) {
        func = command_strtoul(argv[1], NULL, 0);
    }
    if (func == 0) { // show curr
        console_putf("dbg mod: %08X\n", dbg_get_module());
        #if (PLF_WIFI_STACK && defined(CONFIG_RWNX_LWIP))
        console_putf("wf dm: %04X\n", wifi_debug_mask_get());
        #endif
    } else if (func == 1) { // config mod
        if (argc > 2) {
            unsigned int mod_msk = command_strtoul(argv[2], NULL, 16);
            console_putf("Cfg dbg mod: %08X\n", mod_msk);
            dbg_set_module(mod_msk);
        } else {
            console_putf("invalid args\n");
            ret = 2;
        }
    }
    #if (PLF_WIFI_STACK && defined(CONFIG_RWNX_LWIP))
    else if (func == 2) { // config wifi debug mask
        if (argc > 2) {
            unsigned int dbg_msk = command_strtoul(argv[2], NULL, 16);
            console_putf("Cfg wf dm: %04X\n", dbg_msk);
            wifi_debug_mask_set(dbg_msk);
        } else {
            console_putf("invalid args\n");
            ret = 4;
        }
    }
    #endif
    else {
        console_putf("invalid func\n");
        ret = 3;
    }
    return ret;
}

static cmd_tbl_t cmd_tbl_list[] = {
    {
        "h",    "- help info",
        1, 1,   do_help
    },
    // Memory acess
    {
        "r",    "addr <cnt> <sz> - Read Mem(.b/.h)",
        2, 3,   do_mem_read
    },
    {
        "w",    "addr val <cnt> - Write Mem(.b/.h)",
        3, 4,   do_mem_write
    },
    #if (PLF_PMIC && PLF_AIC8800 && PLF_PMIC_VER_LITE && PLF_EXT_AIC1000)
    {
        "ar",    "addr <cnt> <sz> - Read aMem(.b/.h)",
        2, 3,   do_amem_read
    },
    {
        "aw",    "addr val <cnt> - Write aMem(.b/.h)",
        3, 3,   do_amem_write
    },
    #endif
    {
        "ds",  "0/1 <sev> - Config dbg sev or show curr",
        1, 3,   do_dbg_severity_config
    },
    {
        "dm",  "0/1/2 <mod> - Config dbg mod or show curr",
        1, 3,   do_dbg_module_config
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
            if (!list_empty(&cmd_free_list)) {
                cmd_buf_node_t *buf = list_first_entry(&cmd_free_list, cmd_buf_node_t, entry);
                strcpy(buf->buffer, console_buffer);
                list_move_tail(&(buf->entry), &cmd_pend_list);
            } else {
                console_puts("err: cmd_free_list empty\r\n");
            }
        } else {
            console_puts(CONFIG_SYS_PROMPT);
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
                console_puts("No command\r\n");
                break;    /* no command at all */
            }
            /* Look up command in command table */
            cmdtp = command_find((const char *)argv[0], cmd_tbl_list, CONFIG_CMDTBL_SIZE);
            if (cmdtp == NULL) {
                console_putf("Unknown command '%s'\r\n", argv[0]);
                break;
            }
            /* found - check min/max args */
            if ((argc > cmdtp->maxargs) || (argc < cmdtp->minargs)) {
                console_putf("Usage:\r\n%s %s\r\n", cmdtp->name, cmdtp->usage);
                break;
            }
            /* If OK so far, then do the command */
            ret = command_call(cmdtp, argc, argv);
            if (ret) {
                console_putf("Command fail, ret=%d\r\n", ret);
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
