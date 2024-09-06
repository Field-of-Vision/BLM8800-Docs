 /**
 *******************************************************************************
 *
 * @file fhost_wifi_csi.c
 *
 * @brief Definition of an example application task for Fully Hosted firmware.
 *
 * Copyright (C) AIC semi 2018-2022
 *
 *******************************************************************************
 */

#include "fhost.h"
#include "netdb.h"
#include "fhost_config.h"
#include "fhost_cntrl.h"
#include "rwnx_msg_tx.h"
#include "wlan_if.h"


struct lltf_csi_40m_st {
    uint32_t magci;    //0x41435349[ACSI]
    uint32_t ts;       // timestamp
    int16_t  wi_p[51]; //primary-20M
    int16_t  wq_p[51];
    int16_t  wi_s[51]; //secondary-20M
    int16_t  wq_s[51];
    uint32_t agc_analog;
    uint32_t agc_digit;
    int8_t   rssi;
};

/******************************************************************************
 * Application code:
 *****************************************************************************/

void csi_dump_buf_0(const uint32_t *buf, uint16_t len)
{
    int i;
    //dbg("%s %x\r\n", __func__, buf);
    for (i=0;i<len;i++) {
        if((i)%4 == 0)
            dbg("[%08x]:", &buf[i]);
        dbg("  ");
        dbg("%08X ", buf[i]);
        if((i+1)%4 == 0)
            dbg("\n");
    }
    dbg("\n");
}
void  aic_fhost_rx_csi(struct fhost_frame_info *info, void *arg)
{
    //dbg("%s %d\r\n", __func__, __LINE__);
    struct lltf_csi_40m_st *csi = (struct lltf_csi_40m_st *)info->payload;

    //csi_dump_buf_0(info->payload, info->length/4);
}



/*
 * fhost_application_init: Must initialize the minimum for the application to
 *                         start.
 * In this example only create a new task with the entry point set to the
 * 'fhost_example_task'. The rest on the initialization will be done in this
 * function.
 */
int fhost_application_init(void)
{
    fhost_rx_set_csi_cb(aic_fhost_rx_csi, NULL);

    return 0;
}

void fhost_application_deinit(void)
{
    fhost_rx_set_csi_cb(NULL, NULL);
}

/**
 * @}
 */


