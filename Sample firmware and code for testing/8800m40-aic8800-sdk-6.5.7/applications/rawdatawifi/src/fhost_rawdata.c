 /**
 *******************************************************************************
 *
 * @file fhost_rawdata.c
 *
 *
 * Copyright (C) AIC semi 2021-2022
 *
 *******************************************************************************
 */

#include "fhost.h"
#include "fhost_config.h"
#include "fhost_cntrl.h"
#include "rwnx_msg_tx.h"
#include "wlan_if.h"
#include "rawdata_if.h"

/// Master message queue
static rtos_queue rawdata_queue;

#define FHOST_RAWDATA_QUEUE_SIZE    10


enum rawdata_msg_type {
    RAWDATA_INIT = 0,
    RAWDATA_SEND,

    RAWDATA_RECV,

    RAWDATA_POWERDOWN_WIFI,
    RAWDATA_SCAN,

    RAWDATA_LIGHT_SLEEP,

    RAWDTA_MSG_MAX,
};

void dump_b(const uint8_t *buf, uint16_t len)
{
    int i;

    for (i=0;i<len;i++) {
        if((i%8 == 0))
            dbg("  ");
        dbg("%02x ", buf[i]);
        if((i+1)%16 == 0)
            dbg("\n");
    }
    dbg("\n");
}
#if PLF_AIC8800
static void raw_data_handler(uint8_t *data, uint32_t size)
{
    dump_b(data, 8);
}
#endif
#if PLF_AIC8800M40
static void raw_data_monitor_handler(struct fhost_frame_info *info, void *arg)
{
    if (info->payload == NULL) {
        dbg("Unsupported frame: length = %d\r\n", info->length);
    } else {
        struct mac_hdr *hdr = (struct mac_hdr *)info->payload;
        uint8_t *adr1 = ((uint8_t *)(hdr->addr1.array));
        uint8_t *adr2 = ((uint8_t *)(hdr->addr2.array));
        uint8_t *adr3 = ((uint8_t *)(hdr->addr3.array));
        dbg("a1=%02x:%02x:%02x:%02x:%02x:%02x a2=%02x:%02x:%02x:%02x:%02x:%02x "
            "a3=%02x:%02x:%02x:%02x:%02x:%02x fc=%04X SN:%d len=%d\n",
            adr1[0], adr1[1], adr1[2], adr1[3], adr1[4], adr1[5],
            adr2[0], adr2[1], adr2[2], adr2[3], adr2[4], adr2[5],
            adr3[0], adr3[1], adr3[2], adr3[3], adr3[4], adr3[5],
            hdr->fctl, hdr->seq >> 4, info->length);
    }
}
#endif

static int send_rawdata(void)
{
    #if 1
    uint8_t pkt[] = {0x40,0x00,0x64,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,
    0x88, 0x11, 0x22, 0x77, 0xff, 0xa3,  //SA
	0xff,0xff,0xff,0xff,0xff,0xff,
	0xc0,0x00,0x00,0x00,0x01,0x08,0x0c,0x12,0x18,0x24,
	0x30,0x48,0x60,0x6c};
    #else
    uint8_t pkt[] = {0x08,0x01,0x7F,0x00,
    0x0C, 0x83, 0x9A, 0xF3, 0xC7, 0xDC,  //BSSID
    0x88, 0x11, 0x22, 0x77, 0xff, 0xa3,  //SA
    0x0C, 0x83, 0x9A, 0xF3, 0xC7, 0xDC,  //DA
    0x40,0x00,
    0xAA,0xAA,0x03,0x00,0x00,0x00,0x08,0x00,
    0x45,0x00,0x00,0x80,0x00,0x9A,0x00,0x00,0x01,0x11,
    0xF6,0xC7,            //
    0xC0,0xA8,0x01,0x64,  //

    0xFF,0xFF,0xFF,0xFF,
    0xC0,0x03,0x13,0x89,0x00,0x6C,
    0x92,0xA1,  //

    0x00,0x00,0x00,0x42,0x00,0x00,0x00,0x10,0x00,0x0D,
    0xAE,0x2C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};

    #endif

    rawdata_if_tx_data(pkt, sizeof(pkt));

    return 0;
}

static void rawdata_init(void)
{
    int res;

    struct fhost_msg msg;

    msg.id   = FHOST_MSG_ID(RAWDATA_INIT, 0);
    msg.len  = 0;
    msg.data = NULL;

    res = rtos_queue_write(rawdata_queue, &msg, 0, 0);
    ASSERT_ERR(res == 0);
}
static void rawdata_state_set(uint8_t msg_id)
{
    int res;

    struct fhost_msg msg;

    msg.id   = FHOST_MSG_ID(msg_id, 0);
    msg.len  = 0;
    msg.data = NULL;

    res = rtos_queue_write(rawdata_queue, &msg, 0, 0);
    ASSERT_ERR(res == 0);
}

static int raw_scan(void)
{
    int nb_res;
    struct mac_scan_result result;
    unsigned int fvif_idx = 0;
    static struct fhost_cntrl_link *raw_cntrl_link;

    ipc_host_cntrl_start();

    raw_cntrl_link = fhost_cntrl_cfgrwnx_link_open();
    if (raw_cntrl_link == NULL) {
        dbg(D_ERR "Failed to open link with control task\n");
        return -1;
    }
    // Reset STA interface (this will end previous wpa_supplicant task)
    if (fhost_set_vif_type(raw_cntrl_link, fvif_idx, VIF_UNKNOWN, false) ||
        fhost_set_vif_type(raw_cntrl_link, fvif_idx, VIF_STA, false)) {

        fhost_cntrl_cfgrwnx_link_close(raw_cntrl_link);
        return -1;
   }

    nb_res = fhost_scan(raw_cntrl_link, fvif_idx, NULL);
    dbg("Got %d scan results\n", nb_res);

    nb_res = 0;
    while(fhost_get_scan_results(raw_cntrl_link, nb_res++, 1, &result)) {
        result.ssid.array[result.ssid.length] = '\0'; // set ssid string ending
        dbg("(%3d dBm) CH=%3d BSSID=%02x:%02x:%02x:%02x:%02x:%02x AKM=%02x SSID=%s\n",
            (int8_t)result.rssi, phy_freq_to_channel(result.chan->band, result.chan->freq),
            ((uint8_t *)result.bssid.array)[0], ((uint8_t *)result.bssid.array)[1],
            ((uint8_t *)result.bssid.array)[2], ((uint8_t *)result.bssid.array)[3],
            ((uint8_t *)result.bssid.array)[4], ((uint8_t *)result.bssid.array)[5],
            result.akm, (char *)result.ssid.array);
    }

    fhost_cntrl_cfgrwnx_link_close(raw_cntrl_link);
    return 0;
}

/*
 * Entry point of this application
 */
static RTOS_TASK_FCT(fhost_rawdata_task)
{
    struct fhost_msg msg;

    rawdata_init();
    for (;;) {
        rtos_queue_read(rawdata_queue, &msg, -1, false);

        switch (FHOST_MSG_TYPE(msg.id)) {
            case RAWDATA_INIT:
                {
                    rtos_task_suspend(500);

                    uint8_t fhost_mac_addr[] = {0x88, 0x11, 0x22, 0x77, 0xff, 0xa3};
                    rawdata_if_set_mac_addr(fhost_mac_addr);

                    rawdata_if_init();
                    rawdata_if_set_channel(36);

                    uint8_t fhost_bssid_addr[] = {0x0C, 0x83, 0x9A, 0xF3, 0xC7, 0xDC};
                    rawdata_if_set_bssid(fhost_bssid_addr);
                    #if PLF_AIC8800
                    rawdata_if_rx_data_cb_register(raw_data_handler);
                    #endif
                    #if PLF_AIC8800M40
                    fhost_rx_set_monitor_cb(raw_data_monitor_handler, NULL);
                    #endif
                    rawdata_if_set_fixed_rate(2, 0, 0); // 802.11n 6.5M

                    rawdata_state_set(RAWDATA_SEND);
                }
                break;
            case RAWDATA_SEND:
                send_rawdata();
                rtos_task_suspend(2000);
                rawdata_sleep_level_set(1);
                rtos_task_suspend(3000);
                rawdata_sleep_level_set(0);
                rawdata_state_set(RAWDATA_RECV);
                break;
            case RAWDATA_RECV:
                rtos_task_suspend(2000);
                rawdata_state_set(RAWDATA_SEND);
                break;
            #if 0
            case RAWDATA_POWERDOWN_WIFI:
                wifi_fw_powerdown_with_host_alive();
                rtos_task_suspend(3000);
                wifi_fw_powerup_with_host_alive();
                rawdata_if_deinit();
                rawdata_state_set(RAWDATA_INIT);
                break;
            case RAWDATA_SCAN:
                raw_scan();
                break;
            #endif
            default:
                break;
        }
    }

    rtos_task_delete(NULL);
}

/******************************************************************************
 * Fhost FW interfaces:
 * These are the functions required by the fhost FW that are specific to the
 * final application.
 *****************************************************************************/
/*
 * fhost_application_init: Must initialize the minimum for the application to
 *                         start.
 * In this example only create a new task with the entry point set to the
 * 'fhost_example_task'. The rest on the initialization will be done in this
 * function.
 */
int fhost_application_init(void)
{
    if (rtos_queue_create(sizeof(struct fhost_msg), FHOST_RAWDATA_QUEUE_SIZE, &rawdata_queue))
        return 1;

    if (rtos_task_create(fhost_rawdata_task, "Rawdata task", APPLICATION_TASK,
                         512, NULL, RTOS_TASK_PRIORITY(1), NULL))
        return 2;

    return 0;
}


/**
 * @}
 */




