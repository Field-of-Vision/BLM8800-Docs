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
#include "test_main.h"
#include "dbg.h"

#ifdef CFG_RTOS
#include "rtos.h"
#endif /* CFG_RTOS */

#ifdef CFG_TEST_DMA
extern void dma_test(void);
#define TEST_MAIN_FUNC()    dma_test()
#endif /* CFG_TEST_DMA */

#ifdef CFG_TEST_SPI0
extern void spi0_test(void);
#define TEST_MAIN_FUNC()    spi0_test()
#endif /* CFG_TEST_SPI0 */

#ifdef CFG_TEST_SPI_SLAVE
extern void spi_slave_test(void);
#define TEST_MAIN_FUNC()    spi_slave_test()
#endif /* CFG_TEST_SPI_SLAVE */

#ifdef CFG_TEST_I2CM0
extern void i2cm0_test(void);
#define TEST_MAIN_FUNC()    i2cm0_test()
#endif /* CFG_TEST_I2CM0 */

#ifdef CFG_TEST_TICKER
extern void ticker_test(void);
#define TEST_MAIN_FUNC()    ticker_test()
#endif /* CFG_TEST_TICKER */

#ifdef CFG_TEST_GPIO
extern void gpio_test(void);
#define TEST_MAIN_FUNC()    gpio_test()
#endif /* CFG_TEST_GPIO */

#ifdef CFG_TEST_GPIO_IRQ
extern void gpio_irq_test(void);
#define TEST_MAIN_FUNC()    gpio_irq_test()
#endif /* CFG_TEST_GPIO_IRQ */

#ifdef CFG_TEST_UART
extern void uart_test(void);
#define TEST_MAIN_FUNC()    uart_test()
#endif /* CFG_TEST_UART */

#ifdef CFG_TEST_CE
extern void ce_test(void);
#define TEST_MAIN_FUNC()    ce_test()
#endif /* CFG_TEST_CE */

#ifdef CFG_TEST_AES
extern void aes_test(void);
#define TEST_MAIN_FUNC()    aes_test()
#endif /* CFG_TEST_AES */

#ifdef CFG_TEST_TRANS
extern void trans_test(void);
#define TEST_MAIN_FUNC()    trans_test()
#endif /* CFG_TEST_TRANS */

#ifdef CFG_TEST_FFT512
extern void fft512_test(void);
#define TEST_MAIN_FUNC()    fft512_test()
#endif /* CFG_TEST_FFT512 */

#ifdef CFG_TEST_FIR
extern void fir_test(void);
#define TEST_MAIN_FUNC()    fir_test()
#endif /* CFG_TEST_FIR */

#ifdef CFG_TEST_MULTADD
extern void multadd_test(void);
#define TEST_MAIN_FUNC()    multadd_test()
#endif /* CFG_TEST_MULTADD */

#ifdef CFG_TEST_ASIO
extern void asio_test(void);
#define TEST_MAIN_FUNC()    asio_test()
#endif /* CFG_TEST_ASIO */

#ifdef CFG_TEST_SBC
extern void sbc_test(void);
#define TEST_MAIN_FUNC()    sbc_test()
#endif /* CFG_TEST_SBC */

#ifdef CFG_TEST_AAC
extern void aac_test(void);
#define TEST_MAIN_FUNC()    aac_test()
#endif /* CFG_TEST_AAC */

#ifdef CFG_TEST_MP3
extern void mp3_test(void);
#define TEST_MAIN_FUNC()    mp3_test()
#endif /* CFG_TEST_MP3 */

#ifdef CFG_TEST_LC3
extern void lc3_test(void);
#define TEST_MAIN_FUNC()    lc3_test()
#endif /* CFG_TEST_LC3 */

#ifdef CFG_TEST_USBD_CDC
extern void usbd_cdc_test(void);
#define TEST_MAIN_FUNC()    usbd_cdc_test()
#endif /*CFG_TEST_USBD_CDC */

#ifdef CFG_TEST_USBD_AUDIO
extern void usbd_audio_test(void);
#define TEST_MAIN_FUNC()    usbd_audio_test()
#endif /*CFG_TEST_USBD_AUDIO */

#ifdef CFG_TEST_USBD_MSC
extern void usbd_msc_test(void);
#define TEST_MAIN_FUNC()    usbd_msc_test()
#endif /*CFG_TEST_USBD_MSC */

#ifdef CFG_TEST_USB_HOST
extern void usb_host_test(void);
#define TEST_MAIN_FUNC()    usb_host_test()
#endif /*CFG_TEST_USB_HOST */

#ifdef CFG_TEST_USBH_VIDEO
extern void usbh_video_test(void);
#define TEST_MAIN_FUNC()    usbh_video_test()
#endif /*CFG_TEST_USBH_VIDEO */

#ifdef CFG_TEST_MEMCPY
extern void memcpy_test(void);
#define TEST_MAIN_FUNC()    memcpy_test()
#endif /*CFG_TEST_MEMCPY */

#ifdef CFG_TEST_UNALIGN
extern void unalign_test(void);
#define TEST_MAIN_FUNC()    unalign_test()
#endif /*CFG_TEST_UNALIGN */

#ifdef CFG_TEST_CHECKSUM
extern void checksum_test(void);
#define TEST_MAIN_FUNC()    checksum_test()
#endif /*CFG_TEST_CHECKSUM */

#ifdef CFG_TEST_CLKSW
extern void clksw_test(void);
#define TEST_MAIN_FUNC()    clksw_test()
#endif /*CFG_TEST_CLKSW */

#ifdef CFG_TEST_PSRAM
extern void psram_test(void);
#define TEST_MAIN_FUNC()    psram_test()
#endif /*CFG_TEST_PSRAM */

#ifdef CFG_TEST_DDR
extern void ddr_test(void);
#define TEST_MAIN_FUNC()    ddr_test()
#endif /*CFG_TEST_DDR */

#ifdef CFG_TEST_FLASH
extern void flash_test(void);
#define TEST_MAIN_FUNC()    flash_test()
#endif /*CFG_TEST_FLASH */

#ifdef CFG_TEST_SDMMC
extern void sdmmc_test(void);
#define TEST_MAIN_FUNC()    sdmmc_test()
#endif /*CFG_TEST_SDMMC */

#ifdef CFG_TEST_SDCARD
extern void sdcard_test(void);
#define TEST_MAIN_FUNC()    sdcard_test()
#endif /*CFG_TEST_SDCARD */

#ifdef CFG_TEST_SDCARD_AUDIO
extern void sdcard_audio_test(void);
#define TEST_MAIN_FUNC()    sdcard_audio_test()
#endif /*CFG_TEST_SDCARD */

#ifdef CFG_TEST_STATICLIB
extern void staticlib_test(void);
#define TEST_MAIN_FUNC()    staticlib_test()
#endif /*CFG_TEST_STATICLIB */

#ifdef CFG_TEST_SLEEP
extern void sleep_test(void);
#define TEST_MAIN_FUNC()    sleep_test()
#endif /*CFG_TEST_SLEEP */

#ifdef CFG_TEST_TRNG
extern void trng_test(void);
#define TEST_MAIN_FUNC()    trng_test()
#endif /*CFG_TEST_SLEEP */

#ifdef CFG_TEST_PSIM
extern void psim_test(void);
#define TEST_MAIN_FUNC()    psim_test()
#endif /*CFG_TEST_PSIM */

#ifdef CFG_TEST_WDT
extern void wdt_test(void);
#define TEST_MAIN_FUNC()    wdt_test()
#endif /*CFG_TEST_WDT */

#ifdef CFG_TEST_MSADC
extern void msadc_test(void);
#define TEST_MAIN_FUNC()    msadc_test()
#endif /*CFG_TEST_MSADC */

#ifdef CFG_TEST_GPADC
extern void gpadc_test(void);
#define TEST_MAIN_FUNC()    gpadc_test()
#endif /*CFG_TEST_GPADC */

#ifdef CFG_TEST_PROCMON
extern void procmon_test(void);
#define TEST_MAIN_FUNC()    procmon_test()
#endif /* CFG_TEST_PROCMON */

#ifdef CFG_TEST_GSENSOR
extern void gsensor_test(void);
#define TEST_MAIN_FUNC()    gsensor_test()
#endif /*CFG_TEST_GSENSOR */

#ifdef CFG_TEST_SCREEN
extern void screen_test(void);
#define TEST_MAIN_FUNC()    screen_test()
#endif /*CFG_TEST_SCREEN */

#ifdef CFG_TEST_EPAPER
extern void epaper_test(void);
#define TEST_MAIN_FUNC()    epaper_test()
#endif /*CFG_TEST_EPAPER */

#ifdef CFG_TEST_HCI
extern void hci_test(void);
#define TEST_MAIN_FUNC()    hci_test()
#endif /*CFG_TEST_HCI */

#ifdef CFG_TEST_DSP
extern void dsp_test(void);
#define TEST_MAIN_FUNC()    dsp_test()
#endif /*CFG_TEST_DSP */

#ifdef CFG_TEST_UPGRADE
extern void upgrade_test(void);
#define TEST_MAIN_FUNC()    upgrade_test()
#endif /* CFG_TEST_UPGRADE */

#ifdef CFG_TEST_PWM
extern void pwm_test(void);
#define TEST_MAIN_FUNC()    pwm_test()
#endif /*CFG_TEST_PWM */

#ifdef CFG_TEST_MISC
extern void misc_test(void);
#define TEST_MAIN_FUNC()    misc_test()
#endif /*CFG_TEST_MISC */

#ifdef CFG_TEST_SPI_LCD_4WIRES
extern void spi_lcd_4wires_test(void);
#define TEST_MAIN_FUNC()    spi_lcd_4wires_test()
#endif /*CFG_TEST_SPI_LCD_4WIRES */

#ifdef CFG_TEST_AUDIO_MT
extern void audio_mt_test(void);
#define TEST_MAIN_FUNC()    audio_mt_test()
#endif /*CFG_TEST_AUDIO_MT */

#ifdef CFG_TEST_USB_BT
extern void usb_bt_test(void);
#define TEST_MAIN_FUNC()    usb_bt_test()
#endif /*CFG_TEST_USB_BT */

#ifdef CFG_TEST_BOOTLOADER
extern void bootloader_test(void);
#define TEST_MAIN_FUNC()    bootloader_test()
#endif /* CFG_TEST_BOOTLOADER */

#ifdef CFG_TEST_MICROHOST
extern void microhost_test(void);
#define TEST_MAIN_FUNC()    microhost_test()
#endif /* CFG_TEST_MICROHOST */

#ifdef CFG_TEST_GPIOB_SPI
extern void gpiob_spi_test(void);
#define TEST_MAIN_FUNC()    gpiob_spi_test()
#endif /*CFG_TEST_GPIOB_SPI */

#ifdef CFG_TEST_GPIOB_I2CM
extern void gpiob_i2cm_test(void);
#define TEST_MAIN_FUNC()    gpiob_i2cm_test()
#endif /*CFG_TEST_GPIOB_I2CM */

#ifdef CFG_TEST_PRESS_BUTTON
extern void press_button_test(void);
#define TEST_MAIN_FUNC()    press_button_test()
#endif /*CFG_TEST_PRESS_BUTTON */

#ifdef CFG_TEST_CJSON
extern void cjson_test(void);
#define TEST_MAIN_FUNC()    cjson_test()
#endif /*CFG_TEST_CJSON */

#ifdef CFG_TEST_XMODEM
extern void xmodem_test(void);
#define TEST_MAIN_FUNC()    xmodem_test()
#endif /*CFG_TEST_XMODEM */

#ifdef CFG_TEST_MINILZO
extern void minilzo_test(void);
#define TEST_MAIN_FUNC()    minilzo_test()
#endif /*CFG_TEST_MINILZO */

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTIONS
 ****************************************************************************************
 */
#ifndef CFG_RTOS
/**
 ****************************************************************************************
 * @brief test main function
 ****************************************************************************************
 */
void test_main(void)
{
    dbg("start test...\r\n");
    TEST_MAIN_FUNC();
}

#else  /* CFG_RTOS */

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
static RTOS_TASK_FCT(test_task_routine)
{
    uint32_t notification = 0;
    dbg("start test...\n");
    TEST_MAIN_FUNC();

    while (1) {
        notification = rtos_task_wait_notification(-1);
        dbg("recv notif:%x\n",notification);
    }
}

int test_task_init(void)
{
    // Create the test task
    if (rtos_task_create(test_task_routine, "TEST", TEST_TASK,
                         TASK_STACK_SIZE_TEST, NULL, TASK_PRIORITY_TEST, NULL)) {
        return 1;
    }

    return 0;
}

#endif /* CFG_RTOS */
