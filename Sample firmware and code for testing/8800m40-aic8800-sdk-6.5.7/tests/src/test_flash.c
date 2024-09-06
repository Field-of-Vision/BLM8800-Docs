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
#include <string.h>
#include "dbg.h"
#include "flash_api_wifi.h"
#include "flash_api_btdm.h"
#include "sysctrl_api.h"
#include "dma_generic.h"
#include "console.h"
#include "system.h"
#include "sysctrl_api.h"
#if (PLF_PMIC)
#include "pmic_api.h"
#endif

#ifdef CFG_RTOS
#include "rtos_al.h"
#endif /* CFG_RTOS */

#ifdef CFG_TEST_FLASH

/*
 * MACROS
 ****************************************************************************************
 */
#define FLASH_RD_ADDR           0x800F000
#define FLASH_RD_LEN            128
#define UART_PRINT              dbg
#define RAM_DST_ADDR            0x110000
#define FLASH_DMA_CH_IDX        DMA_CHANNEL_IPC_DBG_DUMP
#define FLASH_DMA_IRQ_IDX       DMA10_IRQn
#define FLASH_DMA_ISR_ENABLED   (1)
#define FLASH_OTP_MEM_RD_ADDR   0x00001000
#define FLASH_OTP_MEM_RD_LEN    64

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
#if FLASH_DMA_ISR_ENABLED
rtos_semaphore flash_rd_sema;
#endif

/*
 * FUNCTIONS
 ****************************************************************************************
 */
#if FLASH_DMA_ISR_ENABLED
void DMA10_IRQHandler(void)
{
    const int ch = FLASH_DMA_CH_IDX;
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    rtos_semaphore_signal(flash_rd_sema, true);
}
#endif

void flash_dma_init(void)
{
    #if FLASH_DMA_ISR_ENABLED
    int ret;
    ret = rtos_semaphore_create(&flash_rd_sema, 1, 0);
    if (ret) {
        UART_PRINT("sema create fail: %d\r\n", ret);
    }
    #endif
    // clk en
    #if (PLF_AIC8800)
    cpusysctrl_hclkme_set(CSC_HCLKME_DMA_EN_BIT);
    cpusysctrl_cachebp_burst_incr_only_en_clrb();
    #endif
    NVIC_SetPriority(FLASH_DMA_IRQ_IDX, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(FLASH_DMA_IRQ_IDX);
}

int flash_dma_read(void *adr, unsigned int len, void *buf)
{
    const int ch = FLASH_DMA_CH_IDX;
    unsigned int addr = (unsigned int)adr - 0x04000000UL;

    dma_ch_dar_set(ch, (unsigned int)buf);
    dma_ch_sar_set(ch, addr);
    dma_ch_tbl0cr_set(ch, ((1024) | (REQ_TBL2 << DMA_CH_RQTYP_LSB) | (AHB_WORD << DMA_CH_DBUSU_LSB) |
                             (AHB_WORD << DMA_CH_SBUSU_LSB)));
    dma_ch_tbl1cr_set(ch, len);
    dma_ch_tbl2cr_set(ch, len);
    dma_ch_tsr_set(ch, ((4 << DMA_CH_STRANSZ_LSB) | (4 << DMA_CH_DTRANSZ_LSB)));
    dma_ch_wmar_set(ch, 0);
    dma_ch_wjar_set(ch, 0);
    dma_ch_lnar_set(ch, 0);
    dma_ch_tbl0sr_set(ch, ((0 << DMA_CH_STBL0SZ_LSB) | (0 << DMA_CH_DTBL0SZ_LSB)));
    dma_ch_tbl1ssr_set(ch, 0);
    dma_ch_tbl1dsr_set(ch, 0);
    #if FLASH_DMA_ISR_ENABLED
    dma_ch_icsr_set(ch, (DMA_CH_TBL2_IENA_BIT | DMA_CH_CE_IENA_BIT));
    #endif
    dma_ch_ctlr_set(ch, (DMA_CH_CHENA_BIT | (0x02UL << DMA_CH_BUSBU_LSB)));
    dma_ch_rqr_srq_setb(ch);
    #if FLASH_DMA_ISR_ENABLED
    rtos_semaphore_wait(flash_rd_sema, -1);
    #else
    while (dma_ch_icsr_tbl2_irst_getb(ch) == 0);
    dma_ch_icsr_set(ch, (dma_ch_icsr_get(ch) | DMA_CH_TBL2_ICLR_BIT | DMA_CH_CE_ICLR_BIT));
    #endif

    return 0;
}

static int cmd_flash_dma_read(int argc, char * const argv[])
{
    // dma read 16KB
    flash_dma_init();
    flash_dma_read((void *)FLASH_RD_ADDR, 0x4000, (void *)RAM_DST_ADDR);
    return 0;
}

static int cmd_flash_calib_info_read(int argc, char * const argv[])
{
    xtal_cap_info_t xtal_cap;
    wifi2g4_txpwr_info_t wifi2g4_txpwr;
    #if (PLF_AIC8800 || PLF_AIC8800M40)
    wifi5g_txpwr_info_t wifi5g_txpwr;
    #endif
    int ret;
    ret = flash_calib_xtal_cap_read(&xtal_cap);
    if (ret == INFO_READ_DONE) {
        dbg("calib xtal cap read: cap=0x%x, cap_fine=0x%x\r\n", xtal_cap.cap, xtal_cap.cap_fine);
    } else if (ret == INFO_FLAG_INVALID) {
        dbg("calib xtal cap info flag is invalid\r\n");
    } else {
        dbg("calib xtal cap read err=%d\r\n", ret);
    }
    ret = flash_calib_wifi2g4_txpwr_read(&wifi2g4_txpwr);
    if (ret == INFO_READ_DONE) {
        #if (PLF_AIC8800M40)
        int idx;
        dbg("calib wifi 2.4g txpwr ofst2x read:\n");
        for (idx = 0; idx < 3; idx++) {
            dbg("  %d, %d, %d\n", wifi2g4_txpwr.ofst2x[idx][0],
                wifi2g4_txpwr.ofst2x[idx][1], wifi2g4_txpwr.ofst2x[idx][2]);
        }
        #else
        dbg("calib wifi 2.4g txpwr ofst read:\r\n"
            "  [0] = %d\r\n"
            "  [1] = %d\r\n"
            "  [2] = %d\r\n",
            wifi2g4_txpwr.ofst[0],
            wifi2g4_txpwr.ofst[1],
            wifi2g4_txpwr.ofst[2]);
        #endif
    } else if (ret == INFO_FLAG_INVALID) {
        dbg("calib wifi 2.4g txpwr info flag is invalid\r\n");
    } else {
        dbg("calib wifi 2.4g txpwr read err=%d\r\n", ret);
    }
    #if (PLF_AIC8800 || PLF_AIC8800M40)
    ret = flash_calib_wifi5g_txpwr_read(&wifi5g_txpwr);
    if (ret == INFO_READ_DONE) {
        #if (PLF_AIC8800M40)
        int idx;
        dbg("calib wifi 5g txpwr ofst2x read:\n");
        for (idx = 0; idx < 3; idx++) {
            dbg(D_INF "  %d, %d, %d, %d, %d, %d\n",
                wifi5g_txpwr.ofst2x[idx][0], wifi5g_txpwr.ofst2x[idx][1], wifi5g_txpwr.ofst2x[idx][2],
                wifi5g_txpwr.ofst2x[idx][3], wifi5g_txpwr.ofst2x[idx][4], wifi5g_txpwr.ofst2x[idx][5]);
        }
        #else
        dbg("calib wifi 5g txpwr read:\r\n"
            "  [0] = %d\r\n"
            "  [1] = %d\r\n"
            "  [2] = %d\r\n"
            "  [3] = %d\r\n",
            wifi5g_txpwr.ofst[0],
            wifi5g_txpwr.ofst[1],
            wifi5g_txpwr.ofst[2],
            wifi5g_txpwr.ofst[3]);
        #endif
    } else if (ret == INFO_FLAG_INVALID) {
        dbg("calib wifi 5g txpwr info flag is invalid\r\n");
    } else {
        dbg("calib wifi 5g txpwr read err=%d\r\n", ret);
    }
    #endif
    return 0;
}

static int cmd_flash_wifi_info_access(int argc, char * const argv[])
{
    unsigned int info_id = console_cmd_strtoul(argv[1], NULL, 10);
    unsigned int rdwr    = console_cmd_strtoul(argv[2], NULL, 10);
    int ret;
    if ((rdwr == 1) && (argc < 4)) {
        return -1;
    }
    switch (info_id) {
        case 0: {  // sta config
            unsigned int sta_config;
            if (rdwr == 0) {  // read
                ret = flash_wifi_sta_config_read(&sta_config);
                if (ret == INFO_READ_DONE) {
                    dbg("sta config read value=0x%08x\r\n", sta_config);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("sta config info flag is invalid\r\n");
                } else {
                    dbg("sta config read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                sta_config = console_cmd_strtoul(argv[3], NULL, 16);
                flash_wifi_sta_config_write(&sta_config);
                dbg("sta config write value=0x%08x\r\n", sta_config);
            }
        }
        break;
        case 1: {  // sta mac addr
            unsigned char macaddr_flash[6];
            if (rdwr == 0) {  // read
                ret = flash_wifi_sta_macaddr_read(macaddr_flash);
                if (ret == INFO_READ_DONE) {
                    dbg("sta mac addr read: %02x%02x%02x%02x%02x%02x\r\n",
                        macaddr_flash[0], macaddr_flash[1], macaddr_flash[2],
                        macaddr_flash[3], macaddr_flash[4], macaddr_flash[5]);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("sta mac addr info flag is invalid\r\n");
                } else {
                    dbg("sta mac addr read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                unsigned int hex_first4b, hex_last2b;
                char *str_first4b = &argv[3][0];
                char str_last2b[4 + 1];
                memcpy(str_last2b, &argv[3][8], 4);
                str_first4b[8] = '\0';
                str_last2b[4]  = '\0';
                hex_first4b = console_cmd_strtoul(str_first4b, NULL, 16);
                hex_last2b  = console_cmd_strtoul(str_last2b,  NULL, 16);
                macaddr_flash[0] = (unsigned char)((hex_first4b >> 24) & 0xFF);
                macaddr_flash[1] = (unsigned char)((hex_first4b >> 16) & 0xFF);
                macaddr_flash[2] = (unsigned char)((hex_first4b >>  8) & 0xFF);
                macaddr_flash[3] = (unsigned char)((hex_first4b >>  0) & 0xFF);
                macaddr_flash[4] = (unsigned char)((hex_last2b >> 8) & 0xFF);
                macaddr_flash[5] = (unsigned char)((hex_last2b >> 0) & 0xFF);
                flash_wifi_sta_macaddr_write(macaddr_flash);
                dbg("sta mac addr write value=%08x%02x\r\n", hex_first4b, hex_last2b);
            }
        }
        break;
        case 2: { // sta ssid + passwd
            if (rdwr == 0) {  // read
                char ssid[48], pw[64];
                ret = flash_wifi_sta_ssidpw_read(ssid, pw);
                if (ret == INFO_READ_DONE) {
                    dbg("sta ssid/pw read: ssid=%s, passwd=%s\r\n", ssid, pw);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("sta ssid/pw info flag is invalid\r\n");
                } else {
                    dbg("sta ssid/pw read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                char *str_ssid = &argv[3][0];
                char *str_pw   = &argv[4][0];
                flash_wifi_sta_ssidpw_write(str_ssid, str_pw);
                dbg("sta ssid/pw write: ssid=%s, passwd=%s\r\n", str_ssid, str_pw);
            }
        }
        break;
        case 8: {  // ap config
            unsigned int ap_config;
            if (rdwr == 0) {  // read
                ret = flash_wifi_ap_config_read(&ap_config);
                if (ret == INFO_READ_DONE) {
                    dbg("ap config read value=0x%08x\r\n", ap_config);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("ap config info flag is invalid\r\n");
                } else {
                    dbg("ap config read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                ap_config = console_cmd_strtoul(argv[3], NULL, 16);
                flash_wifi_ap_config_write(&ap_config);
                dbg("ap config write value=0x%08x\r\n", ap_config);
            }
        }
        break;
        case 9: {  // ap mac addr
            unsigned char macaddr_flash[6];
            if (rdwr == 0) {  // read
                ret = flash_wifi_ap_macaddr_read(macaddr_flash);
                if (ret == INFO_READ_DONE) {
                    dbg("ap mac addr read: %02x%02x%02x%02x%02x%02x\r\n",
                        macaddr_flash[0], macaddr_flash[1], macaddr_flash[2],
                        macaddr_flash[3], macaddr_flash[4], macaddr_flash[5]);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("ap mac addr info flag is invalid\r\n");
                } else {
                    dbg("ap mac addr read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                unsigned int hex_first4b, hex_last2b;
                char *str_first4b = &argv[3][0];
                char str_last2b[4 + 1];
                memcpy(str_last2b, &argv[3][8], 4);
                str_first4b[8] = '\0';
                str_last2b[4]  = '\0';
                hex_first4b = console_cmd_strtoul(str_first4b, NULL, 16);
                hex_last2b  = console_cmd_strtoul(str_last2b,  NULL, 16);
                macaddr_flash[0] = (unsigned char)((hex_first4b >> 24) & 0xFF);
                macaddr_flash[1] = (unsigned char)((hex_first4b >> 16) & 0xFF);
                macaddr_flash[2] = (unsigned char)((hex_first4b >>  8) & 0xFF);
                macaddr_flash[3] = (unsigned char)((hex_first4b >>  0) & 0xFF);
                macaddr_flash[4] = (unsigned char)((hex_last2b >> 8) & 0xFF);
                macaddr_flash[5] = (unsigned char)((hex_last2b >> 0) & 0xFF);
                flash_wifi_ap_macaddr_write(macaddr_flash);
                dbg("ap mac addr write value=%08x%02x\r\n", hex_first4b, hex_last2b);
            }
        }
        break;
        case 10: { // ap ssid + passwd
            if (rdwr == 0) {  // read
                char ssid[48], pw[64];
                ret = flash_wifi_ap_ssidpw_read(ssid, pw);
                if (ret == INFO_READ_DONE) {
                    dbg("ap ssid/pw read: ssid=%s, passwd=%s\r\n", ssid, pw);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("ap ssid/pw info flag is invalid\r\n");
                } else {
                    dbg("ap ssid/pw read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                char *str_ssid = &argv[3][0];
                char *str_pw   = &argv[4][0];
                flash_wifi_ap_ssidpw_write(str_ssid, str_pw);
                dbg("ap ssid/pw write: ssid=%s, passwd=%s\r\n", str_ssid, str_pw);
            }
        }
        break;
        case 11: { // ap channel
            unsigned int channel;
            if (rdwr == 0) {  // read
                ret = flash_wifi_ap_channel_read(&channel);
                if (ret == INFO_READ_DONE) {
                    dbg("ap channel read value=%d\r\n", channel);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("ap channel info flag is invalid\r\n");
                } else {
                    dbg("ap channel read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                channel = console_cmd_strtoul(argv[3], NULL, 10);
                flash_wifi_ap_channel_write(channel);
                dbg("ap channel write value=%d\r\n", channel);
            }
        }
        break;
        case 16: {  // lwip config
            unsigned int lwip_config;
            if (rdwr == 0) {  // read
                ret = flash_wifi_lwip_config_read(&lwip_config);
                if (ret == INFO_READ_DONE) {
                    dbg("lwip config read value=0x%08x\r\n", lwip_config);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("lwip config info flag is invalid\r\n");
                } else {
                    dbg("lwip config read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                lwip_config = console_cmd_strtoul(argv[3], NULL, 16);
                flash_wifi_lwip_config_write(&lwip_config);
                dbg("lwip config write value=0x%08x\r\n", lwip_config);
            }
        }
        break;
        case 17: {  // lwip dhcps
            unsigned int ap_lease_time;
            unsigned int ap_dhcp_start;
            unsigned int ap_dhcp_end;
            if (rdwr == 0) {  // read
                ret = flash_wifi_lwip_dhcps_read(&ap_lease_time, &ap_dhcp_start, &ap_dhcp_end);
                if (ret == INFO_READ_DONE) {
                    dbg("lwip dhcps read: lease_time=%d, start=%x, end=%x\r\n",
                        ap_lease_time, ap_dhcp_start, ap_dhcp_end);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("lwip dhcps info flag is invalid\r\n");
                } else {
                    dbg("lwip dhcps read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                ap_lease_time = console_cmd_strtoul(argv[3], NULL, 10);
                ap_dhcp_start = console_cmd_strtoul(argv[4], NULL, 16);
                ap_dhcp_end   = console_cmd_strtoul(argv[5], NULL, 16);
                flash_wifi_lwip_dhcps_write(ap_lease_time, ap_dhcp_start, ap_dhcp_end);
                dbg("lwip dhcps write: lease_time=%d, start=%x, end=%x\r\n",
                    ap_lease_time, ap_dhcp_start, ap_dhcp_end);
            }
        }
        break;
        case 18: {  // lwip dns server
            unsigned int dns_server;
            if (rdwr == 0) {  // read
                ret = flash_wifi_lwip_dnsserv_read(&dns_server);
                if (ret == INFO_READ_DONE) {
                    dbg("lwip dns server read value=0x%08x\r\n", dns_server);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("lwip dns server info flag is invalid\r\n");
                } else {
                    dbg("lwip dns server read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                dns_server = console_cmd_strtoul(argv[3], NULL, 16);
                flash_wifi_lwip_dnsserv_write(dns_server);
                dbg("lwip dns server write value=0x%08x\r\n", dns_server);
            }
        }
        break;
        case 19: {  // lwip sntp
            signed int time_zone;
            if (rdwr == 0) {  // read
                ret = flash_wifi_lwip_sntp_read(&time_zone);
                if (ret == INFO_READ_DONE) {
                    dbg("lwip sntp read: time_zone=%d\r\n", time_zone);
                } else if (ret == INFO_FLAG_INVALID) {
                    dbg("lwip sntp info flag is invalid\r\n");
                } else {
                    dbg("lwip sntp read err=%d\r\n", ret);
                }
            } else if (rdwr == 1) {  //write
                time_zone = (signed int)console_cmd_strtoul(argv[3], NULL, 10);
                flash_wifi_lwip_sntp_write(time_zone);
                dbg("lwip sntp write time_zone=%d\r\n", time_zone);
            }
        }
        break;
        default:
        dbg("undefined flash wifi info\r\n");
        break;
    }
    return 0;
}

static int cmd_flash_btdm_info_access(int argc, char * const argv[])
{
    /// TODO:
    return 0;
}

static int cmd_flash_otp_mem_read(int argc, char * const argv[])
{
    unsigned char otp_rd_buf[FLASH_OTP_MEM_RD_LEN];
    // read OTP memory
    int ret = flash_otp_memory_read((void *)FLASH_OTP_MEM_RD_ADDR,
                        FLASH_OTP_MEM_RD_LEN, (void *)otp_rd_buf);
    if (ret) {
        UART_PRINT("OTP read err=%d\r\n", ret);
        return -1;
    }
    dump_mem((uint32_t)otp_rd_buf, FLASH_OTP_MEM_RD_LEN, 1, false);
    return 0;
}

static int cmd_flash_bp_cfg(int argc, char * const argv[])
{
    #if 0 // [DEPRECATED] Used as CONFIG_FLASH_BLOCK_PROTECT_VER=1
    unsigned int en = console_cmd_strtoul(argv[1], NULL, 0);
    flash_block_protect_all_config(en);
    if (en) {
        UART_PRINT("enable block protect\n");
    } else {
        UART_PRINT("disable block protect\n");
    }
    #else
    int bp_protected;
    unsigned int rd = console_cmd_strtoul(argv[1], NULL, 0);
    if (rd == 0) {
        bp_protected = flash_block_protect_all_get();
        UART_PRINT("get block protect: %d\n", bp_protected);
    } else {
        unsigned int en = console_cmd_strtoul(argv[2], NULL, 0);
        flash_block_protect_all_set(en);
        if (en) {
            UART_PRINT("enable block protect\n");
        } else {
            UART_PRINT("disable block protect\n");
        }
        bp_protected = flash_block_protect_all_get();
        UART_PRINT("get block protect: %d\n", bp_protected);
    }
    #endif
    return 0;
}

void print_clk_info(void)
{
    #if (PLF_AIC8800)
    UART_PRINT("F:%dM,H:%dM,P:%dM,FL:%dM\n",
               DSPSysCoreClock/1000000,SystemCoreClock/1000000,PeripheralClock/1000000,sysctrl_clock_get(PER_FLASH)/1000000);
    #elif (PLF_AIC8800MC || PLF_AIC8800M40)
    UART_PRINT("H:%dM,P:%dM,PSR:%dM,FL:%dM\n",
               SystemCoreClock/1000000,PeripheralClock/1000000,FlashMem2XClock/1000000,sysctrl_clock_get(PER_FLASH)/1000000);
    #endif
}

void print_clk_cfgs(void)
{
    int idx;
    const char *p_clk_cfg_strs[CLK_CFG_MAX] = {
        #if (PLF_AIC8800)
        "CLK_CFG_D480S240P120F120", // 0
        "CLK_CFG_D480S240P120F80",  // 1
        "CLK_CFG_D480S240P120F60",  // 2
        "CLK_CFG_D480S240P120F40",  // 3
        "CLK_CFG_D480S240P60F120",  // 4
        "CLK_CFG_D480S240P60F80",   // 5
        "CLK_CFG_D480S240P60F60",   // 6
        "CLK_CFG_D480S240P60F40",   // 7
        "CLK_CFG_D240S240P120F120", // 8
        "CLK_CFG_D240S240P120F60",  // 9
        "CLK_CFG_D240S240P120F40",  // 10
        "CLK_CFG_D240S240P60F60",   // 11
        "CLK_CFG_D240S240P60F40",   // 12
        "CLK_CFG_D240S120P60F120",  // 13
        "CLK_CFG_D240S120P60F60",   // 14
        "CLK_CFG_D240S120P60F40",   // 15
        "CLK_CFG_D240S120P30F60",   // 16
        "CLK_CFG_D240S120P30F40",   // 17
        "CLK_CFG_D192S192P96F96",   // 18
        "CLK_CFG_D192S192P96F48",   // 19
        "CLK_CFG_D192S192P48F96",   // 20
        "CLK_CFG_D192S192P48F48",   // 21
        "CLK_CFG_D120S120P60F60",   // 22
        "CLK_CFG_D120S120P60F30",   // 23
        "CLK_CFG_D120S120P30F60",   // 24
        "CLK_CFG_D120S120P30F30",   // 25
        "CLK_CFG_D80S80P40F40",     // 26
        "CLK_CFG_D52S52P26F26",     // 27
        #elif (PLF_AIC8800MC || PLF_AIC8800M40)
        "CLK_CFG_S240P120PS240F120",// 0
        "CLK_CFG_S240P120PS320F106",// 1
        "CLK_CFG_S240P120PS192F96", // 2
        "CLK_CFG_S240P120PS320F80", // 3
        "CLK_CFG_S240P120PS240F60", // 4
        "CLK_CFG_S240P120PS192F48", // 5
        "CLK_CFG_S240P120PS240F40", // 6
        "CLK_CFG_S192P96PS240F120", // 7
        "CLK_CFG_S192P96PS320F106", // 8
        "CLK_CFG_S192P96PS192F96",  // 9
        "CLK_CFG_S192P96PS320F80",  // 10
        "CLK_CFG_S192P96PS240F60",  // 11
        "CLK_CFG_S192P96PS192F48",  // 12
        "CLK_CFG_S192P96PS240F40",  // 13
        "CLK_CFG_S160P80PS240F120", // 14
        "CLK_CFG_S160P80PS320F106", // 15
        "CLK_CFG_S160P80PS192F96",  // 16
        "CLK_CFG_S160P80PS320F80",  // 17
        "CLK_CFG_S160P80PS240F60",  // 18
        "CLK_CFG_S160P80PS192F48",  // 19
        "CLK_CFG_S160P80PS240F40",  // 20
        "CLK_CFG_S120P60PS240F120", // 21
        "CLK_CFG_S120P60PS320F106", // 22
        "CLK_CFG_S120P60PS192F96",  // 23
        "CLK_CFG_S120P60PS320F80",  // 24
        "CLK_CFG_S120P60PS240F60",  // 25
        "CLK_CFG_S120P60PS192F48",  // 26
        "CLK_CFG_S120P60PS240F40",  // 27
        "CLK_CFG_S80P40PS320F80",   // 28
        "CLK_CFG_S80P40PS240F60",   // 29
        "CLK_CFG_S80P40PS192F48",   // 30
        "CLK_CFG_S80P40PS240F40",   // 31
        #if (PLF_AIC8800MC)
        "CLK_CFG_S52P26PS240F40",   // 32
        "CLK_CFG_S52P26PS240F20",   // 33
        #elif (PLF_AIC8800M40)
        "CLK_CFG_S80P40PS80F40",    // 32
        "CLK_CFG_S80P40PS80F20",    // 33
        #endif
        #endif
    };
    UART_PRINT("clk cfg supported:\n");
    for (idx = 0; idx < CLK_CFG_MAX; idx++) {
        UART_PRINT("  [%2d]: %s\n", idx, p_clk_cfg_strs[idx]);
    }
}

static int cmd_clock_switch(int argc, char * const argv[])
{
    int ret = 0;
    unsigned int func = console_cmd_strtoul(argv[1], NULL, 0);
    if (func == 0) { // read current
        print_clk_info();
        print_clk_cfgs();
    } else if (func == 1) { // set clk
        int clk_cfg_idx = (int)console_cmd_strtoul(argv[2], NULL, 0);
        sysctrl_clock_cfg(clk_cfg_idx);
        SystemCoreClockUpdate();
    } else {
        UART_PRINT("err func: %d\n", func);
        print_clk_cfgs();
        ret = -1;
    }
    return ret;
}

/**
 * Note: locate the test code in RAM
 */
static int cmd_flash_scratch_test(int argc, char * const argv[])
{
    unsigned char buf_pattern[256 + 32] = {0,};
    int idx;
    #if (PLF_AIC8800)
    unsigned int addr = AIC_CACHE0_MEM_BASE;
    #elif (PLF_AIC8800MC || PLF_AIC8800M40)
    unsigned int addr = AIC_CACHE_MEM_BASE;
    #endif
    unsigned int addr_end;
    UART_PRINT("scratch test start\n");
    // prepare buf
    for (idx = 0; idx < sizeof(buf_pattern); idx += 4) {
        if ((idx >> 5) & 0x01UL) {
            *((unsigned int *)&buf_pattern[idx]) = 0xAAAAAAAAUL;
        } else {
            *((unsigned int *)&buf_pattern[idx]) = 0x55555555UL;
        }
    }
    //dump_mem((uint32_t)buf_pattern, 72, 1, false);
    addr_end = addr + flash_chip_size_get();
    for (; addr < addr_end; addr += 0x100000UL) { // test every 1MB
        flash_erase((void *)addr, 4096); // erase 1 sector
        flash_cache_invalid_range((void *)addr, 4096);
        for (idx = 0; idx < 4096; idx += 4) {
            if (*((unsigned int *)(addr + idx)) != 0xFFFFFFFFUL) {
                break;
            }
        }
        if (idx < 4096) {
            UART_PRINT("sector erase fail: [%x]=%08x\n", addr + idx, *((unsigned int *)(addr + idx)));
            break;
        }
        flash_write((void *)addr, 256, (void *)(&buf_pattern[0]));
        flash_write((void *)(addr + 256), 256, (void *)(&buf_pattern[32]));
        flash_cache_invalid_range((void *)addr, 512);
        for (idx = 0; idx < 256; idx += 4) {
            if (*((unsigned int *)(addr + idx)) != *((unsigned int *)(&buf_pattern[idx]))) {
                break;
            }
        }
        if (idx < 256) {
            UART_PRINT("page 0 write fail: [%x]=%08x, %08x wrote\n", addr + idx,
                *((unsigned int *)(addr + idx)), *((unsigned int *)(&buf_pattern[idx])));
            break;
        }
        for (idx = 0; idx < 256; idx += 4) {
            if (*((unsigned int *)(addr + 256 + idx)) != *((unsigned int *)(&buf_pattern[32 + idx]))) {
                break;
            }
        }
        if (idx < 256) {
            UART_PRINT("page 1 write fail: [%x]=%08x, %08x wrote\n", addr + 256 + idx,
                *((unsigned int *)(addr + 256 + idx)), *((unsigned int *)(&buf_pattern[32 + idx])));
            break;
        }
    }
    UART_PRINT("scratch test done: %s\n", (addr < addr_end) ? "fail" : "success");
    return 0;
}

/**
 * Note: flash read write test
 */
#define FLASH_TEST_SIZE  (256)
static int cmd_flash_rdwr_test(int argc, char * const argv[])
{
    unsigned int pattern = 0;
    unsigned int test_count = 10;
    unsigned int debug_on = 0;
    int idx, i = 0;
    unsigned int pattern_reverse = 0;
    unsigned int start_addr = 0x8000000;
    unsigned int flash_size = 0;
    unsigned char format_read_buf[FLASH_TEST_SIZE] = {0,};
    unsigned char read_buf[FLASH_TEST_SIZE] = {0,};
    unsigned char write_buf[FLASH_TEST_SIZE] = {0,};
    unsigned char write_buf_reverse[FLASH_TEST_SIZE] = {0,};
    unsigned char *write_buf_ptr = NULL;
    int ret = 0;

    if (IS_CODE_IN_FLASH()) {
        dbg("err, code in flash\n");
        return -1;
    }

    if (argc >= 2) {
        pattern = console_cmd_strtoul(argv[1], NULL, 16);
        if (argc > 2) {
            test_count = console_cmd_strtoul(argv[2], NULL, 10);
        }
        if (argc == 4) {
            debug_on = console_cmd_strtoul(argv[3], NULL, 10);
        }
    }

    dbg("pattern 0x%x, test_count %d\n", pattern, test_count);
    if (test_count > 100000) {
        UART_PRINT("test_count error, %d is too big\n", test_count);
        return -1;
    }

    if (pattern) {
        pattern_reverse = ~pattern;
        dbg("pattern reverse 0x%x\n", pattern_reverse);
    }

    print_clk_info();

    memset(format_read_buf, 0xff, sizeof(format_read_buf));
    // prepare write buf
    for (idx = 0; idx < sizeof(write_buf); idx += 4) {
        *((unsigned int *)&write_buf[idx]) = pattern;
        if (pattern_reverse) {
            *((unsigned int *)&write_buf_reverse[idx]) = pattern_reverse;
        }
    }

    UART_PRINT("flash read write test start\n");
    flash_size = flash_chip_size_get();

    for (i = 0; i < test_count; i++) {
        if (debug_on) {
            dbg("count %d start\n", i+1);
        }
        //erase and read
        flash_erase((void *)start_addr, flash_size);
        flash_cache_invalid_range((void *)start_addr, flash_size);
        for (idx = 0; idx < flash_size; idx += FLASH_TEST_SIZE) {
            memset(read_buf, 0, sizeof(read_buf));
            flash_read((void *)(start_addr + idx), FLASH_TEST_SIZE, read_buf);
            if (memcmp(format_read_buf, read_buf, FLASH_TEST_SIZE)) {
                dbg("erase err, flash read write test failed at round %d\n", i + 1);
                return -1;
            }
        }

        if (pattern && (i % 2)) {
            write_buf_ptr = &write_buf_reverse[0];
        } else {
            write_buf_ptr = &write_buf[0];
        }

        // write and read
        for (idx = 0; idx < flash_size; idx += FLASH_TEST_SIZE) {
            ret = flash_write((void *)(start_addr + idx), FLASH_TEST_SIZE, (void *)write_buf_ptr);
            if (ret == 0) {
                flash_cache_invalid_range((void *)(start_addr + idx), FLASH_TEST_SIZE);
                memset(read_buf, 0, sizeof(read_buf));
                flash_read((void *)(start_addr + idx), FLASH_TEST_SIZE, (void *)(&read_buf[0]));
                if (memcmp(write_buf_ptr, read_buf, FLASH_TEST_SIZE)) {
                    dbg("read err, flash read write test failed at round %d\n", i + 1);
                    return -1;
                }
            } else {
                dbg("write err, flash read write test failed at round %d\n", i + 1);
                return -1;
            }
        }
        if (debug_on) {
            dbg("count %d end\n", i+1);
        }
    }

    dbg("flash read write test passed, test count %d\n", i);
    return 0;
}

static int cmd_sys_reboot(int argc, char * const argv[])
{
    #if PLF_PMIC && (!PLF_AIC8800)
    uint8_t hold_bits;
    #if (PLF_AIC8800MC)
    hold_bits = PMIC_GPIO_HOLD_BIT_A0_6 | PMIC_GPIO_HOLD_BIT_A10_15 | PMIC_GPIO_HOLD_BIT_B0_3;
    #elif (PLF_AIC8800M40)
    hold_bits = PMIC_GPIO_HOLD_BIT_A0_3 | PMIC_GPIO_HOLD_BIT_A10_15 | PMIC_GPIO_HOLD_BIT_B0_7;
    #else
    #error "invalid plf"
    #endif
    pmic_gpio_hold_set(hold_bits);
    #endif
    sysctrl_chip_reboot();
    return 0;
}

#if (PLF_PMIC)
int cmd_pmic_reboot(int argc, char * const argv[])
{
    pmic_chip_reboot(0xF);
    return 0;
}
#endif

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void flash_test(void)
{
    UART_PRINT("\nFlash test start\n");

    UART_PRINT("Flash size=%08X\n", flash_chip_size_get());

    console_cmd_add("dmaread",      "read flash with dma",    1, 1, cmd_flash_dma_read);
    console_cmd_add("calibinford",  "read flash calib info",  1, 1, cmd_flash_calib_info_read);
    console_cmd_add("wifiinfoacc",  "access flash wifi info", 3, 6, cmd_flash_wifi_info_access);
    console_cmd_add("btdminfoacc",  "access flash btdm info", 3, 6, cmd_flash_btdm_info_access);
    console_cmd_add("otpread",      "read otp memory",        1, 1, cmd_flash_otp_mem_read);
    console_cmd_add("cfgbp",        "cfg block protect",      2, 3, cmd_flash_bp_cfg);
    console_cmd_add("clksw",        "0/1 <cfg> - Print/switch clock", 2, 3, cmd_clock_switch);
    console_cmd_add("scratch",      "- Scratch test",         1, 1, cmd_flash_scratch_test);
    console_cmd_add("flashtest",    "- read write test",      1, 4, cmd_flash_rdwr_test);

    console_cmd_add("sysreb",       "- sys reboot",           1, 1, cmd_sys_reboot);
    #if (PLF_PMIC)
    console_cmd_add("pmicreb",      "- pmic reboot",          1, 1, cmd_pmic_reboot);
    #endif

    UART_PRINT("\nFlash test done\n");
}

#endif /* CFG_TEST_FLASH */
