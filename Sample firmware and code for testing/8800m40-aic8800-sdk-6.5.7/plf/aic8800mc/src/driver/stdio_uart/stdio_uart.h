/**
 ****************************************************************************************
 *
 * @file stdio_uart.h
 *
 * @brief UART Driver for stdio and console.
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 *
 ****************************************************************************************
 */

#ifndef _STDIO_UART_H_
#define _STDIO_UART_H_

/**
 ****************************************************************************************
 * @defgroup UART UART
 * @ingroup DRIVERS
 * @brief UART driver
 *
 * @{
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdbool.h>          // standard boolean definitions
#include <stdint.h>           // standard integer functions
#include "reg_stdio_uart.h"   // uart register
#include "reg_ipc_mutex.h"
#include "chip.h"

#define IPC_MUTEX_UART_OUTPUT   (IPC_MUTEX_ID_UART0_OUTPUT + UART_INDEX)

/// 3-part macro to function/variable/enum string
#define M2STR_P3_I(p0,p1,p2)    p0##p1##p2
#define M2STR_P3(p0,p1,p2)      M2STR_P3_I(p0, p1, p2)

/// Replace WEAK function in startup.S
#define stdio_uart_isr      M2STR_P3(UART, UART_INDEX, _IRQHandler)

typedef void (*stdio_uart_rx_func_t)(void);

extern int stdio_uart_inited;

__STATIC_INLINE void stdio_uart_puthex(uint32_t val)
{
    uint8_t clz = __CLZ(val);
    while (stdio_uart_tx_dbuf_full_getf());
    stdio_uart_txdata_setf('0');
    while (stdio_uart_tx_dbuf_full_getf());
    stdio_uart_txdata_setf('x');
    if (clz == 32) {
        while (stdio_uart_tx_dbuf_full_getf());
        stdio_uart_txdata_setf('0');
    } else {
        int ofst = (31 - clz) & ~0x3;
        for (; ofst >= 0; ofst -= 4) {
            uint8_t ch = (val >> ofst) & 0x0F;
            ch = (ch >= 0xA) ? ('A' + (ch - 0xA)) : ('0' + ch);
            while (stdio_uart_tx_dbuf_full_getf());
            stdio_uart_txdata_setf(ch);
        }
    }
    while (stdio_uart_tx_dbuf_full_getf());
    stdio_uart_txdata_setf('\r');
    while (stdio_uart_tx_dbuf_full_getf());
    stdio_uart_txdata_setf('\n');
}

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

void stdio_uart_init(void);
void stdio_uart_recover(void);
uint32_t stdio_uart_baud_get(void);
void stdio_uart_baud_set(uint32_t baud);
void stdio_uart_format_get(uint32_t *bits, uint32_t *parity, uint32_t *stop);
void stdio_uart_format_set(uint32_t bits, uint32_t parity, uint32_t stop);
void stdio_uart_putc(char ch);
void stdio_uart_puts(const char* str);
void stdio_uart_nputs(const char* str, int len);
char stdio_uart_getc(void);
bool stdio_uart_tstc(void);
int  stdio_uart_get_rx_count(void);
void register_stdio_uart_rx_function(stdio_uart_rx_func_t func);
void stdio_uart_isr(void);

/// @} STDIO_UART
#endif /* _STDIO_UART_H_ */
