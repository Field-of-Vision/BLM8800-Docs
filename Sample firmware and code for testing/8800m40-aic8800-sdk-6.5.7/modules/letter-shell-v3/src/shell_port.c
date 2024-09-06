/**
 * @file shell_port.c
 * @author Letter (NevermindZZT@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-02-22
 *
 * @copyright (c) 2019 Letter
 *
 */

#include "shell.h"
#include "stdio_uart.h"


Shell shell;
char shellBuffer[512];
#if SHELL_USING_CMD_SEMAPORE
rtos_semaphore hasCandidateCmd;
#endif

/**
 * @brief 用户shell写
 *
 * @param data 数据
 */
void userShellWrite(char data)
{
    stdio_uart_putc(data);
}


/**
 * @brief 用户shell读
 *
 * @param data 数据
 * @return char 状态
 */
signed char userShellRead(char *data)
{
    *data = stdio_uart_getc();
    return 0;
}

#if SHELL_USING_CMD_SEMAPORE
void userShellWait(void)
{
    rtos_semaphore_wait(hasCandidateCmd, -1);
}

void userShellIndicate(void)
{
    rtos_semaphore_signal(hasCandidateCmd, true); // called in isr
}

void userShellRecvHandler(void)
{
    while (stdio_uart_get_rx_count()) {
        unsigned char c = (unsigned char)stdio_uart_rxdata_getf();
        shellHandler(&shell, c);
    }
}
#endif

/**
 * @brief 用户shell初始化
 *
 */
void userShellInit(void)
{
    shell.write = userShellWrite;
    shell.read = userShellRead;
#if SHELL_USING_CMD_SEMAPORE
    shell.wait = userShellWait;
    shell.indicate = userShellIndicate;
#endif
    shellInit(&shell, shellBuffer, 512);

    // Initialize uart
    if (!stdio_uart_inited) {
        stdio_uart_init();
    }
#if SHELL_USING_CMD_SEMAPORE
    register_stdio_uart_rx_function(userShellRecvHandler);
#else
    stdio_uart_rxirqen_setf(0); //disable rx interrupt
#endif

#if SHELL_USING_CMD_SEMAPORE
    // create the shell semaphore
    if (rtos_semaphore_create(&hasCandidateCmd, 1, 0)) {
        shellPrint(&shell, "create shell sema fail\r\n");
        return;
    }
#endif
    // Create the shell task
    if (rtos_task_create(shellTask, "SHELL", CONSOLE_TASK,
                         512, &shell, RTOS_TASK_PRIORITY(1), NULL)) {
        shellPrint(&shell, "create shell task fail\r\n");
        return;
    }
}
