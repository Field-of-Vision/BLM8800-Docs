/*
 * Copyright (C) 2018-2023 AICSemi Ltd.
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

#include "dbg.h"
#include "rtos_al.h"
#include "esp_xmodem.h"
#include "esp_xmodem_transport.h"
#include "string.h"
#include "uart2_api.h"
#include "console.h"
#include "rom_api.h"
#include "sysctrl_api.h"

#if (PLF_OTA)
#include "aic_ota.h"
#include "pmic_api.h"
#endif

#if (PLF_FATFS)
#include "ff.h"
#endif

#include "ring_buffer.h"
#include "co_math.h"
#include "gpio_api.h"

#ifdef CFG_TEST_XMODEM
/*
 * MACROS
 ****************************************************************************************
 */
#define UART_PRINT                  dbg
#define free                        rtos_free
#define OTA_BUF_SIZE                1024
#define isprintable(c)              (((c >= 0x1F) && (c <= 0x7E)) || (c == 0x0A) || (c == 0x0D))

#define CONTROL_STATE_PIN_EN        0
#define PIN_IDLE_STATE_SELECT       1 // 0: low, 1: high
#if (CONTROL_STATE_PIN_EN)
#define CONTROL_PIN_START_GPIDX     0 // in
#define STATE_PIN_BUSY_GPIDX        1 // out
#define STATE_PIN_OK_GPIDX          2 // out
#define STATE_PIN_NG_GPIDX          3 // out
#define START_PULSE_PERIOD_MS       100
#if (PIN_IDLE_STATE_SELECT)
#define PIN_EDGE_1ST                GPIOIRQ_EVENT_EDGE_FALL
#define PIN_EDGE_2ND                GPIOIRQ_EVENT_EDGE_RISE
#else
#define PIN_EDGE_1ST                GPIOIRQ_EVENT_EDGE_RISE
#define PIN_EDGE_2ND                GPIOIRQ_EVENT_EDGE_FALL
#endif
#endif

/*
 * GLOBAL CONSTANTS & VARIABLES
 ****************************************************************************************
 */
static const char *TAG = "xmodem_test";

static char upgrade_data_buf[OTA_BUF_SIZE + 1];
static uint32_t time_ms_rec = 0;
#if (CONTROL_STATE_PIN_EN)
static uint32_t start_time_ms_rec = 0;
rtos_semaphore start_signal_sema = NULL;
#endif
#define READ_START_ADDR     0x08040000
#define READ_LENGTH         0x00200000
#define SDCARD_DRIVE_ID         "SD:"

#define UART_BAUD_10M_EN        0//1//

char file_path[256] = SDCARD_DRIVE_ID "/upgrade/host_wb_8800d80_2023_1019.bin";

/*
 * FUNCTIONS
 ****************************************************************************************
 */
void uart_baud_config(int is_fast);

void xmodem_send_data_task(void *pvParameters)
{
    esp_xmodem_handle_t xmodem_sender = (esp_xmodem_handle_t)pvParameters;
    esp_err_t err;
    uint32_t total_len = 0x400000;//READ_LENGTH;//0x1120;//0x10000;
    uint32_t remain_len, data_len;
    #if (PLF_FATFS)
    //char *fsid      = SDCARD_DRIVE_ID "/";
    //char *upg_dir   = SDCARD_DRIVE_ID "/upgrade";
    //char *upg_file  = SDCARD_DRIVE_ID "/upgrade/host_wb_8800d80_2023_1019.bin";
    char *upg_file  = file_path;
    //FATFS fs;
    FIL fh;
    FILINFO fi;
    #else
    uint32_t read_addr = READ_START_ADDR;
    #endif
    ESP_LOGE(TAG, "Enter xmodem_send_data_task");
    #if (PLF_FATFS)
    do {
        int fs_err;
        uint8_t mode = FA_READ;

        #if 0
        UART_PRINT("mount: %s\n", fsid);
        fs_err = f_mount(&fs, fsid, 0);
        if (fs_err) {
            UART_PRINT("Fail to mount, fs_err=%d\n", fs_err);
            break;
        }
        #endif

        #if 0
        UART_PRINT("stat: %s\n", upg_dir);
        fs_err = f_stat(upg_dir, &fi);
        if (fs_err == FR_NO_FILE) {
            UART_PRINT("Dir %s not exist!\n", upg_dir);
            break;
        } else if (fs_err) {
            UART_PRINT("Fail to stat, fs_err=%d\n", fs_err);
            break;
        }
        #endif

        UART_PRINT("stat: %s\n", upg_file);
        fs_err = f_stat(upg_file, &fi);
        if (fs_err == FR_NO_FILE) {
            UART_PRINT("File %s not Exist\n", upg_file);
            break;
        } else if (fs_err) {
            UART_PRINT("Fail to stat, fs_err=%d\n", fs_err);
            break;
        }

        UART_PRINT("open: %s\n", upg_file);
        fs_err = f_open(&fh, upg_file, mode);
        if (fs_err) {
            UART_PRINT("Fail to open file %s, fs_err=%d\n", upg_file, fs_err);
            break;
        }

        total_len = f_size(&fh);
        UART_PRINT("file size %d\n", total_len);
    } while (0);
    #endif /* PLF_FATFS */
    remain_len = total_len;
    for (;;) {
        if (remain_len > 0) {
            if (remain_len > OTA_BUF_SIZE) {
                data_len = OTA_BUF_SIZE;
            } else {
                data_len = remain_len;
            }
            #if (PLF_FATFS)
            int fs_err;
            unsigned int num;
            //UART_PRINT("read\r\n");
            fs_err = f_read(&fh, upgrade_data_buf, data_len, &num);
            if (fs_err) {
                UART_PRINT("Fail to read, fs_err=%d, num=%d\r\n", fs_err, num);
                break;
            }
            if (num != data_len) {
                UART_PRINT("Read len=%d, num=%d\r\n", data_len, num);
            }
            err = esp_xmodem_sender_send(xmodem_sender, (uint8_t *)upgrade_data_buf, num);
            #else
            err = esp_xmodem_sender_send(xmodem_sender, (uint8_t *)upgrade_data_buf, data_len);
            //err = esp_xmodem_sender_send(xmodem_sender, (uint8_t *)read_addr, data_len);
            read_addr += data_len;
            #endif
            if (err != ESP_OK) {
                ESP_LOGE(TAG, "Error:esp_xmodem_sender_send failed!");
                break;
            }
            remain_len -= data_len;
        } else {
            break;
        }
    }
    if (err) {
        ESP_LOGE(TAG, "Error in receiving complete file");
        esp_xmodem_sender_send_cancel(xmodem_sender);
    } else {
        err = esp_xmodem_sender_send_eot(xmodem_sender);
        uart_baud_config(0);
        uart2_rxirqen_setf(1); //enable rx interrupt
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Error:esp_xmodem_sender_send_eot FAIL!");
        } else {
            ESP_LOGI(TAG, "Send image success");
            esp_xmodem_transport_close(xmodem_sender);
            esp_xmodem_clean(xmodem_sender);
        }
    }
    #if (PLF_FATFS)
    do {
        int fs_err;
        UART_PRINT("close fh\n");
        fs_err = f_close(&fh);
        if (fs_err) {
            UART_PRINT("Fail to open, fs_err=%d\r\n", fs_err);
            break;
        }
        #if 0
        UART_PRINT("unmount: %s\n", fsid);
        fs_err = f_mount(NULL, fsid, 0);
        if (fs_err) {
            UART_PRINT("Fail to unmount, fs_err=%d\r\n", fs_err);
            break;
        }
        #endif
    } while (0);
    #endif
    uint32_t time_ms_cur = rtos_now(false);
    #if (CONTROL_STATE_PIN_EN)
    gpioa_set(STATE_PIN_BUSY_GPIDX);
    gpioa_clr(STATE_PIN_OK_GPIDX);
    #endif
    rtos_task_suspend(10);
    dbg("Transmit end, t=%dms, cost=%dms\n", time_ms_cur, (time_ms_cur - time_ms_rec));
    //uart2_puts("crc 1 4000000 2097152\r");
    uart2_puts("crc 1 8000000 4194304\r");
    ESP_LOGE(TAG, "Exit xmodem_send_data_task");
    #if (CONTROL_STATE_PIN_EN)
    gpioa_set(STATE_PIN_OK_GPIDX); // keep 10ms at least
    #endif
    rtos_task_delete(NULL);
}

esp_err_t xmodem_sender_event_handler(esp_xmodem_event_t *evt)
{
    int total, free, max_used;

    rtos_heap_info(&total, &free, &max_used);
    switch(evt->event_id) {
        case ESP_XMODEM_EVENT_ERROR:
            ESP_LOGI(TAG, "ESP_XMODEM_EVENT_ERROR, err_code is 0x%x, heap size %d", esp_xmodem_get_error_code(evt->handle), free);
            if (esp_xmodem_stop(evt->handle) == ESP_OK) {
                esp_xmodem_start(evt->handle);
            } else {
                ESP_LOGE(TAG, "esp_xmodem_stop fail");
                esp_xmodem_transport_close(evt->handle);
                esp_xmodem_clean(evt->handle);
            }
            break;
        case ESP_XMODEM_EVENT_CONNECTED:
            ESP_LOGI(TAG, "ESP_XMODEM_EVENT_CONNECTED, heap size %d", free);
            if (rtos_task_create(xmodem_send_data_task, "xmdm_send_task", XMDM_SEND_DATA_TASK, 512, evt->handle, 5, NULL)) {
                ESP_LOGE(TAG, "xmodem_send_data_task create fail");
                return ESP_FAIL;
            }
            break;
        case ESP_XMODEM_EVENT_FINISHED:
            ESP_LOGI(TAG, "ESP_XMODEM_EVENT_FINISHED");
            break;
        case ESP_XMODEM_EVENT_ON_SEND_DATA:
            ESP_LOGD(TAG, "ESP_XMODEM_EVENT_ON_SEND_DATA, %d", free);
            break;
        case ESP_XMODEM_EVENT_ON_RECEIVE_DATA:
            ESP_LOGD(TAG, "ESP_XMODEM_EVENT_ON_RECEIVE_DATA, %d", free);
            break;
        default:
            break;
    }
    return ESP_OK;
}

ring_buffer_t rbuf = {NULL,};
uint8_t rbuf_storage[1024];
uint8_t rbuf_tmp[128 + 1] = {'\0',};

#define UART_RX_FLAG_NORMAL     (0x01 << 0)
#define UART_RX_FLAG_CRCMD      (0x01 << 1)

typedef struct {
    uint16_t flags;
    uint16_t cnt;
} uart_rx_msg_t;
rtos_queue uart_rx_queue = NULL;
rtos_semaphore xmdm_crc_sema = NULL;

void uart_rx_handler(void)
{
    ring_buffer_t *p_rbuf = &rbuf;
    int crc_detect = 0;
    static int ch_cnt = 0;
    static unsigned char pre_ch = '\0';
    while (uart2_get_rx_count()) {
        unsigned char c = (unsigned char)uart2_getc();
        int line_end = 0;
        #if 0
        stdio_uart_putc('_');
        if (isprintable(c)) {
            stdio_uart_putc(c);
        } else {
            UART_PRINT("uart rx: %02X\n", c);
        }
        #endif
        if ((c == '\r') || (c == '\n')) {
            if ((pre_ch == '\r') || (pre_ch == '\n')) {
                pre_ch = c;
                continue; // ignore continous "\r\n"
            }
            // line end
            line_end = 1;
        }
        if ((pre_ch == 'C') && (c == 'C')) {
            crc_detect = 1;
        }
        ring_buffer_write(p_rbuf, (uint8_t *)&c, 1);
        ch_cnt++;
        if (line_end || crc_detect) {
            uart_rx_msg_t msg;
            msg.flags = UART_RX_FLAG_NORMAL;
            if (crc_detect) {
                msg.flags |= UART_RX_FLAG_CRCMD;
            }
            msg.cnt = ch_cnt;
            //dbg("wr cnt=%d\n", ch_cnt);
            // notify logger task
            rtos_queue_write(uart_rx_queue, &msg, 0, true);
            ch_cnt = 0;
        }
        pre_ch = c;
    }
}

void uart_baud_config(int is_fast)
{
    if (is_fast) { // fast baud rate
        #if (UART_BAUD_10M_EN)
        uart2_puts("w 40500010 6\r");
        UART_PRINT("cfg clk\n");
        rtos_task_suspend(1);
        uart2_puts("con.b 10000000 1\r");
        #else
        //uart2_puts("con.b 3250000\r");
        //uart2_puts("con.b 1382400\r");
        uart2_puts("con.b 5000000\r");
        #endif
        UART_PRINT("sw dut baud\n");
        rtos_task_suspend(5);
        while (!uart2_tx_dbuf_empty_getf()) {
            __NOP(); __NOP(); __NOP(); __NOP();
        }
        #if (UART_BAUD_10M_EN)
        ROM_SystemClkDivSet(CLK_DIV_TARGET_PCLK, 0x1);
        ROM_SystemClkSelSet(CLK_SEL_TARGET_UART2_PCLK, 0x1);
        uart2_baud_set(10000000);
        #else
        //uart2_baud_set(3250000);
        //uart2_baud_set(1382400);
        uart2_baud_set(5000000);
        #endif
        UART_PRINT("sw self fast baud\n");
    } else { // normal baud rate
        uart2_puts("con.b 921600\r");
        UART_PRINT("sw dut baud\n");
        rtos_task_suspend(5);
        while (!uart2_tx_dbuf_empty_getf()) {
            __NOP(); __NOP(); __NOP(); __NOP();
        }
        uart2_baud_set(921600);
        UART_PRINT("sw self norm baud\n");
    }
}

static void xmodem_logger_task(void *pvParameters)
{
    //esp_xmodem_handle_t xmodem_sender = (esp_xmodem_handle_t)pvParameters;
    uart_rx_msg_t msg;
    ring_buffer_t *p_rbuf = &rbuf;

    while (1) {
        int ret = rtos_queue_read(uart_rx_queue, &msg, -1, false);
        if (ret) {
            dbg("rtos_queue_read fail, ret=%d\n", ret);
            break;
        } else {
            int len, cnt = 0;
            if ((msg.flags & UART_RX_FLAG_CRCMD) && xmdm_crc_sema) {
                rtos_semaphore_signal(xmdm_crc_sema, false);
            }
            while (cnt < msg.cnt) {
                len = co_min(msg.cnt, 128);
                //dbg("rd cnt=%d\n", len);
                ring_buffer_read(p_rbuf, rbuf_tmp, len);
                rbuf_tmp[len + 1] = '\0';
                dbg("[R%d] %s\n", len, rbuf_tmp);
                cnt += len;
            }
        }
    }
    rtos_task_delete(NULL);
}

static int xmodem_sender_start(char * const file_name)
{
    esp_xmodem_transport_config_t transport_config = {
        .baund_rate = 921600,
    };
    esp_xmodem_transport_handle_t transport_handle = esp_xmodem_transport_init(&transport_config);
    if (!transport_handle) {
        ESP_LOGE(TAG, "esp_xmodem_transport_init fail");
        return -1;
    }

    esp_xmodem_config_t config = {
        .role = ESP_XMODEM_SENDER,
        .event_handler = xmodem_sender_event_handler,
        .support_xmodem_1k = true,
    };
    esp_xmodem_handle_t sender = esp_xmodem_init(&config, transport_handle);
    if (sender) {
        int idx;
        for (idx = 0; idx < OTA_BUF_SIZE; idx+=4) {
            uint32_t *ptr = (uint32_t *)&upgrade_data_buf[idx];
            *ptr = 0xC3C3C3C3;
        }
        #if (PLF_FATFS)
        if (file_name) {
            int len = strlen(file_name);
            memcpy(file_path, file_name, len);
            file_path[len] = '\0';
            dbg("Use upgrade file: %s\n", file_path);
        }
        #endif
        #if (CONTROL_STATE_PIN_EN)
        gpioa_clr(STATE_PIN_BUSY_GPIDX);
        #endif
        uart2_puts("r 40038014\r");
        rtos_task_suspend(1);
        uart_baud_config(1);
        rtos_task_suspend(5);
        uart2_puts("r 40038014\r");
        rtos_task_suspend(1);
        time_ms_rec = rtos_now(false);
        dbg("Start transmit, t=%dms\n", time_ms_rec);
        //uart2_puts("x 8000000 200000\r");
        uart2_puts("x 8000000 400000\r");
        //rtos_task_suspend(11800);
        //rtos_task_suspend(22000);
        UART_PRINT("wait 'C' or NAK\n");
        int ret_sema = rtos_semaphore_wait(xmdm_crc_sema, 32000);
        if (ret_sema == 0) {
            uart2_rxirqen_setf(0); //disable rx interrupt
            esp_xmodem_start(sender);
        } else {
            #if (CONTROL_STATE_PIN_EN)
            gpioa_set(STATE_PIN_BUSY_GPIDX);
            gpioa_clr(STATE_PIN_NG_GPIDX);
            #endif
            UART_PRINT("Timed-out, cancel\n");
            #if (CONTROL_STATE_PIN_EN)
            rtos_task_suspend(10);
            gpioa_set(STATE_PIN_NG_GPIDX);
            #endif
        }
    } else {
        ESP_LOGE(TAG, "esp_xmodem_init fail");
        if (transport_handle) {
            free(transport_handle);
            transport_handle = NULL;
        }
        return -1;
    }

    return 0;
}

static int do_xmodem_send(int argc, char * const argv[])
{
    int ret;
    char *file_name = NULL;
    if (argc > 1) {
        file_name = argv[1];
    }
    ret = xmodem_sender_start(file_name);
    return ret;
}

#if (PLF_OTA)
static bool ota_init = false;

static esp_err_t xmodem_ota_init(void)
{
    ESP_LOGI(TAG, "Starting OTA...");
    if (!ota_init) {
        int ret = ota_start(OTA_ADDR, 0x10000); // default 64KB img_len
        if (ret) {
            ESP_LOGE(TAG, "ota_start failed, ret=%d", ret);
            return ESP_FAIL;
        }
        ota_init = true;
    }
    ESP_LOGI(TAG, "esp_ota_begin succeeded");
    ESP_LOGI(TAG, "Please Wait. This may take time");
    return ESP_OK;
}

static esp_err_t xmodem_ota_end(void)
{
    esp_err_t ota_end_err = ota_end();
    if (ota_end_err != ESP_OK) {
        ESP_LOGE(TAG, "Error: ota_end failed! err=%d. Image is invalid", ota_end_err);
        return ota_end_err;
    }

    ESP_LOGI(TAG, "esp_ota_set_boot_partition succeeded");
    return ESP_OK;
}

static esp_err_t xmodem_receiver_event_handler(esp_xmodem_event_t *evt)
{
    int total, free, max_used;

    rtos_heap_info(&total, &free, &max_used);
    switch(evt->event_id) {
        case ESP_XMODEM_EVENT_ERROR:
            ESP_LOGI(TAG, "ESP_XMODEM_EVENT_ERROR, err_code is 0x%x,%d", esp_xmodem_get_error_code(evt->handle), free);
            ota_init = false;
            xmodem_ota_end();
            if (esp_xmodem_stop(evt->handle) == ESP_OK) {
                esp_xmodem_start(evt->handle);
            } else {
                ESP_LOGE(TAG, "esp_xmodem_stop fail");
                esp_xmodem_transport_close(evt->handle);
                esp_xmodem_clean(evt->handle);
            }
            break;
        case ESP_XMODEM_EVENT_CONNECTED:
            ESP_LOGI(TAG, "ESP_XMODEM_EVENT_CONNECTED");
            if (xmodem_ota_init() != ESP_OK) {
                ESP_LOGE(TAG, "xmodem_ota_init fail");
                esp_xmodem_transport_close(evt->handle);
                esp_xmodem_clean(evt->handle);
            }
            break;
        case ESP_XMODEM_EVENT_FINISHED:
            ESP_LOGI(TAG, "ESP_XMODEM_EVENT_FINISHED");
            if (xmodem_ota_end() == ESP_OK) {
                ESP_LOGI(TAG, "OTA successfully, will restart now...");
                rtos_task_suspend(1000);
                pmic_chip_reboot(0x1F);
            } else {
                ESP_LOGE(TAG, "xmodem_ota_end fail");
                esp_xmodem_transport_close(evt->handle);
                esp_xmodem_clean(evt->handle);
            }
            break;
        case ESP_XMODEM_EVENT_ON_SEND_DATA:
            ESP_LOGD(TAG, "ESP_XMODEM_EVENT_ON_SEND_DATA, %d", free);
            break;
        case ESP_XMODEM_EVENT_ON_RECEIVE_DATA:
            ESP_LOGD(TAG, "ESP_XMODEM_EVENT_ON_RECEIVE_DATA, %d, %d", free, evt->data_len);
            break;
        case ESP_XMODEM_EVENT_ON_FILE:
            ESP_LOGI(TAG, "ESP_XMODEM_EVENT_ON_FILE");
            ESP_LOGI(TAG, "file_name is %s, file_length is %u", (char *)evt->data, evt->data_len);
            break;
        default:
            break;
    }
    return ESP_OK;
}

static esp_err_t xmodem_data_recv(uint8_t *data, uint32_t len)
{
    esp_err_t ret = ota_write((const void *)data, len);
    if (ret != ESP_OK) {
        return ESP_FAIL;
    }
    return ESP_OK;
}

static int do_xmodem_recv(int argc, char * const argv[])
{
    esp_xmodem_transport_config_t transport_config = {
        .baund_rate = 921600,
    };
    esp_xmodem_transport_handle_t transport_handle = esp_xmodem_transport_init(&transport_config);
    if (!transport_handle) {
        ESP_LOGE(TAG, "esp_xmodem_transport_init fail");
        return -1;
    }

    esp_xmodem_config_t config = {
        .role = ESP_XMODEM_RECEIVER,
        .crc_type = ESP_XMODEM_CRC16,
        .event_handler = xmodem_receiver_event_handler,
        .recv_cb = xmodem_data_recv,
        .cycle_max_retry = 25,
    };
    esp_xmodem_handle_t receiver = esp_xmodem_init(&config, transport_handle);
    if (!receiver) {
        ESP_LOGE(TAG, "esp_xmodem_init fail");
        if (transport_handle) {
            free(transport_handle);
            transport_handle = NULL;
        }
        return -1;
    }

    ota_init = false;
    esp_xmodem_start(receiver);
    return 0;
}
#endif

#if (CONTROL_STATE_PIN_EN)
void start_pin_irq_handler(int event)
{
    if (GPIOIRQ_CB_EVENT(event) == PIN_EDGE_1ST) {
        UART_PRINT("start 1st edge\n");
        start_time_ms_rec = rtos_now(true);
    }
    else if (GPIOIRQ_CB_EVENT(event) == PIN_EDGE_2ND) {
        UART_PRINT("start 2nd edge\n");
        if (start_time_ms_rec) {
            uint32_t start_2nd_time_ms = rtos_now(true);
            if ((start_2nd_time_ms - start_time_ms_rec) >= START_PULSE_PERIOD_MS) {
                if (start_signal_sema) {
                    rtos_semaphore_signal(start_signal_sema, true);
                }
                start_time_ms_rec = 0;
            } else {
                UART_PRINT("warning: start time 2nd-1st<%dms\n", START_PULSE_PERIOD_MS);
            }
        }
    }
}
#endif

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void xmodem_test(void)
{
    UART_PRINT("\nXModem test start\n");

    // detect "Mcu mode"
    ring_buffer_t *p_rbuf = &rbuf;
    ring_buffer_init(p_rbuf, rbuf_storage, sizeof(rbuf_storage));
    if (rtos_queue_create(sizeof(uart_rx_msg_t), 10, &uart_rx_queue)) {
        ESP_LOGE(TAG, "xmodem_logr_queue create fail");
        //return 1;
    }
    if (rtos_task_create(xmodem_logger_task, "xmdm_logr_task", XMDM_RECV_TASK, 512, NULL, 5, NULL)) {
        ESP_LOGE(TAG, "xmodem_logr_task create fail");
        //return ESP_FAIL;
    }
    if (rtos_semaphore_create(&xmdm_crc_sema, 1, 0)) {
        ESP_LOGE(TAG, "xmodem_crc_sema create fail");
    }
    uart2_init();
    register_uart2_rx_function(uart_rx_handler);
    #if (CONTROL_STATE_PIN_EN)
    // control in pin
    gpioa_irq_init(CONTROL_PIN_START_GPIDX, PIN_EDGE_1ST, start_pin_irq_handler);
    // state out pins
    gpioa_init(STATE_PIN_BUSY_GPIDX);
    gpioa_init(STATE_PIN_OK_GPIDX);
    gpioa_init(STATE_PIN_NG_GPIDX);
    gpioa_dir_out(STATE_PIN_BUSY_GPIDX);
    gpioa_dir_out(STATE_PIN_OK_GPIDX);
    gpioa_dir_out(STATE_PIN_NG_GPIDX);
    gpioa_set(STATE_PIN_BUSY_GPIDX);
    gpioa_set(STATE_PIN_OK_GPIDX);
    gpioa_set(STATE_PIN_NG_GPIDX);
    if (rtos_semaphore_create(&start_signal_sema, 1, 0)) {
        ESP_LOGE(TAG, "start_signal_sema create fail");
    }
    #endif

    #if (PLF_FATFS)
    char *fsid      = SDCARD_DRIVE_ID "/";
    FATFS fs;
    int fs_err;
    UART_PRINT("mount: %s\n", fsid);
    fs_err = f_mount(&fs, fsid, 0);
    if (fs_err) {
        UART_PRINT("Fail to mount, fs_err=%d\n", fs_err);
    }
    #endif

    console_cmd_add("sx", "  send xmodem send",     1, 2, do_xmodem_send);
    #if (PLF_OTA)
    console_cmd_add("rx", "  send xmodem send",     1, 1, do_xmodem_recv);
    #endif

    #if (CONTROL_STATE_PIN_EN)
    while (1) {
        int ret_sema = rtos_semaphore_wait(start_signal_sema, -1);
        if (ret_sema == 0) {
            int err;
            UART_PRINT("xmodem_sender_start\n");
            err = xmodem_sender_start(NULL);
            if (err) {
                UART_PRINT("xmodem_sender_start err=%d\n", err);
            }
        } else {
            UART_PRINT("sema wait ret=%d\n", ret_sema);
        }
    }
    #endif

    UART_PRINT("\nXmodem test done\n");
}

#endif /* CFG_TEST_XMODEM */
