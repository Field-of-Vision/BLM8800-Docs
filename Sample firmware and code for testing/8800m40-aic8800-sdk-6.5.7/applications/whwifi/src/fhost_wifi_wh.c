 /**
 *******************************************************************************
 *
 * @file fhost_voice.c
 *
 * @brief Definition of an example application task for Fully Hosted firmware.
 *
 * Copyright (C) AIC semi 2019-2021
 *
 *******************************************************************************
 */

#include "fhost.h"
#include "netdb.h"
#include "fhost_config.h"
#include "fhost_cntrl.h"
#include "rwnx_msg_tx.h"
#include "wlan_if.h"
#include "sleep_api.h"
#include "wifi_voice.h"
#include "wifi_wh_config.h"
#if defined(CFG_WIFI_VOICE_ROLE_DONGLE)
#define WIFI_VOICE_ROLE_DONGLE    1
#include "wifi_wh_dongle.h"
#elif defined(CFG_WIFI_VOICE_ROLE_HEADSET)
#define WIFI_VOICE_ROLE_DONGLE    0
#include "wifi_wh_headset.h"
#else
#error wifi voice role undefined
#endif
#include "wifi_wh_user.h"


/******************************************************************************
 * Application code:
 *****************************************************************************/



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
    #ifdef CFG_WIFI_ENGINEERING_MODE
    wifi_engineering_mode_status_set(wifi_wh_config_enable_em_chan_get());
    wifi_engineering_mode_channel_index_set(wifi_wh_config_em_chan_index_get());
    #endif

    #if WIFI_VOICE_ROLE_DONGLE
    if (0 != wifi_wh_dongle_init()) {
        return -1;
    }
    if (0 != wifi_wh_dongle_user_init()) {
        return -1;
    }
    #else
    if (0 != wifi_wh_headset_init()) {
        return -1;
    }
    if (0 != wifi_wh_headset_user_init()) {
        return -1;
    }
    #endif

    if (0 != wifi_voice_init()) {
        return -1;
    }

    return 0;
}

void fhost_application_deinit(void)
{
    #if WIFI_VOICE_ROLE_DONGLE
    wifi_wh_dongle_deinit();
    wifi_wh_dongle_user_deinit();
    #else
    wifi_wh_headset_deinit();
    wifi_wh_headset_user_deinit();
    #endif

    wifi_voice_deinit();
}

/**
 * @}
 */


