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
#include "ff.h"
#include "dbg.h"
#include "system.h"
#include "sysctrl_api.h"

#ifdef CFG_RTOS
#include "rtos_al.h"
#endif /* CFG_RTOS */

#ifdef CFG_TEST_SDCARD

/*
 * MACROS
 ****************************************************************************************
 */

#define RW_BUFF_SIZE            2508
#define UART_PRINT              dbg
#define SDCARD_DRIVE_ID         "SD:"

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
char wr_buf[RW_BUFF_SIZE];
char rd_buf[RW_BUFF_SIZE + 4];

/*
 * FUNCTIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void sdcard_test(void)
{
    uint16_t idx;
    int err;
    char *fsid      = SDCARD_DRIVE_ID "/";
    char *testdir   = SDCARD_DRIVE_ID "/testdir1";
    char *testfile0 = SDCARD_DRIVE_ID "/testdir1/testfile.txt";
    //char *testfile0 = SDCARD_DRIVE_ID "/testfile4.txt";
    char *testfile1 = SDCARD_DRIVE_ID "/testdir1/testfile_multi.txt";
    char filetext[]  = "Test line 0.\r\nTest line 1.\r\n";
    char read_text[64];
    FATFS fs;
    FIL fh;
    FILINFO fi;

    UART_PRINT("\nSDCard test start\n");
    #if (PLF_AIC8800)
    UART_PRINT("F:%dM,H:%dM,P:%dM,FL:%dM\n",
               DSPSysCoreClock/1000000,SystemCoreClock/1000000,PeripheralClock/1000000,sysctrl_clock_get(PER_FLASH)/1000000);
    #else
    UART_PRINT("H:%dM,P:%dM,PSR:%dM,FL:%dM\n",
        SystemCoreClock/1000000,PeripheralClock/1000000,FlashMem2XClock/1000000,sysctrl_clock_get(PER_FLASH)/1000000);
    #endif

    do {
        uint32_t num;
        uint8_t mode = FA_READ | FA_WRITE;

        UART_PRINT("mount: %s\r\n",fsid);
        err = f_mount(&fs, fsid, 0);
        if (err) {
            UART_PRINT("Fail to mount, err=%d\r\n", err);
            break;
        }

        UART_PRINT("stat: %s\r\n",testdir);
        err = f_stat(testdir, &fi);
        if (err == FR_NO_FILE) {
            UART_PRINT("mkdir: %s\r\n",testdir);
            err = f_mkdir(testdir);
            if (err) {
                UART_PRINT("Fail to mkdir, err=%d\r\n", err);
                break;
            }
        } else if (err) {
            UART_PRINT("Fail to stat, err=%d\r\n", err);
            break;
        }

        UART_PRINT("stat: %s\r\n",testfile0);
        err = f_stat(testfile0, &fi);
        if (err == FR_NO_FILE) {
            UART_PRINT("Not Exist\r\n");
            mode |= FA_CREATE_NEW;
        } else if (err) {
            UART_PRINT("Fail to stat, err=%d\r\n", err);
            break;
        }

        UART_PRINT("open: %s\r\n",testfile0);
        err = f_open(&fh, testfile0, mode);
        if (err) {
            UART_PRINT("Fail to open, err=%d\r\n", err);
            break;
        }

        UART_PRINT("write\r\n");
        err = f_write(&fh, filetext, sizeof(filetext), &num);
        if (err) {
            UART_PRINT("Fail to write, err=%d, num=%d\r\n", err, num);
            break;
        }

        UART_PRINT("lseek to 0, cur=%d\r\n",f_tell(&fh));
        err = f_lseek(&fh, 0);
        if (err) {
            UART_PRINT("Fail to lseek, err=%d\r\n", err);
            break;
        }
        UART_PRINT("cur=%d\r\n",f_tell(&fh));

        UART_PRINT("read\r\n");
        err = f_read(&fh, read_text, 64, &num);
        if (err) {
            UART_PRINT("Fail to read, err=%d, num=%d\r\n", err, num);
            break;
        }
        UART_PRINT("Read text from file: %s\r\n%s\r\n", testfile0, read_text);

        UART_PRINT("close\r\n");
        err = f_close(&fh);
        if (err) {
            UART_PRINT("Fail to open, err=%d\r\n", err);
            break;
        }

        for (idx = 0; idx < RW_BUFF_SIZE; idx++) {
            wr_buf[idx] = '0' + (idx & 0x3F);
        }

        UART_PRINT("stat: %s\r\n",testfile1);
        err = f_stat(testfile1, &fi);
        if (err == FR_NO_FILE) {
            UART_PRINT("Not Exist\r\n");
            mode |= FA_CREATE_NEW;
        } else if (err) {
            UART_PRINT("Fail to stat, err=%d\r\n", err);
            break;
        }

        UART_PRINT("open: %s\r\n",testfile1);
        err = f_open(&fh, testfile1, mode);
        if (err) {
            UART_PRINT("Fail to open, err=%d\r\n", err);
            break;
        }

        UART_PRINT("write\r\n");
        err = f_write(&fh, wr_buf, sizeof(wr_buf), &num);
        if (err) {
            UART_PRINT("Fail to write, err=%d, num=%d\r\n", err, num);
            break;
        }

        UART_PRINT("lseek to 0, cur=%d\r\n",f_tell(&fh));
        err = f_lseek(&fh, 0);
        if (err) {
            UART_PRINT("Fail to lseek, err=%d\r\n", err);
            break;
        }
        UART_PRINT("cur=%d\r\n",f_tell(&fh));

        UART_PRINT("read\r\n");
        err = f_read(&fh, rd_buf, sizeof(rd_buf), &num);
        if (err) {
            UART_PRINT("Fail to read, err=%d, num=%d\r\n", err, num);
            break;
        }
        UART_PRINT("Read %d bytes from file: %s,\r\n",num,testfile1);
        for (idx = 0; idx < num; idx++) {
            UART_PRINT(" %c",rd_buf[idx]);
            if ((idx & 0x1F) == 0x1F) {
                UART_PRINT("\r\n");
            }
        }
        if (idx & 0x1F) {
            UART_PRINT("\r\n");
        }

        UART_PRINT("close\r\n");
        err = f_close(&fh);
        if (err) {
            UART_PRINT("Fail to open, err=%d\r\n", err);
            break;
        }

        UART_PRINT("unmount: %s\r\n",fsid);
        err = f_mount(NULL, fsid, 0);
        if (err) {
            UART_PRINT("Fail to unmount, err=%d\r\n", err);
            break;
        }
    } while (0);

    UART_PRINT("\nSDCard test done\n");
}

#endif /* CFG_TEST_SDCARD */
