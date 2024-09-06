#ifndef __HOSTIF_CFG_H__
#define __HOSTIF_CFG_H__

/*
 * Includes
 *******************************************************************************
 */
#include <stdint.h>
#include "hostif.h"
#include "plf.h"
#if PLF_WIFI_STACK
#include "tgt_cfg_wifi.h"
#endif

/*
 * Macro defines
 *******************************************************************************
 */

/**
 * Hostif mode selection, match with host driver
 */
#ifndef CONFIG_HOSTIF_MODE
#define CONFIG_HOSTIF_MODE  HOST_VNET_MODE
#endif

/**
 * Hostif rx pkt filter mode
 */
#ifndef CONFIG_HOSTIF_FILTER_MODE
#define CONFIG_HOSTIF_FILTER_MODE VNET_FILTER_DIRECT
#endif

/**
 * Hostif total buf number
 */
#ifndef CONFIG_HOSTIF_BUF_NUM_TOTAL
#define CONFIG_HOSTIF_BUF_NUM_TOTAL         10
#endif

/**
 * Hostif rx buf number threshhold
 */
#ifndef CONFIG_HOSTIF_RX_BUF_NUM_THRESHOLD
#define CONFIG_HOSTIF_RX_BUF_NUM_THRESHOLD  4
#endif

/*
 * Data types
 *******************************************************************************
 */

/**
 * Structs
 */
typedef struct {
    uint8_t if_mode;
    uint8_t filter_mode;
    uint8_t buf_num_total;
    uint8_t rxbuf_num_thres;
} hostif_cfg_t;

/*
 * Functions
 *******************************************************************************
 */

/**
 * Get hostif type
 */
HOST_TYPE_T hostif_type_get(void);

/**
 * Get hostif mode
 */
HOST_MODE_T hostif_mode_get(void);

/**
 * Get hostif filter mode
 */
uint8_t hostif_filter_type_get(void);

/**
 * Get hostif total buf num
 */
uint8_t hostif_buf_num_total_get(void);

/**
 * Get hostif rxbuf num threshold
 */
uint8_t hostif_rxbuf_num_threshold_get(void);

#endif /* __HOSTIF_CFG_H__ */
