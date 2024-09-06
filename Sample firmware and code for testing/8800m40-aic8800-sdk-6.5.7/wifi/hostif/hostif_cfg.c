/*
 * Includes
 *******************************************************************************
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef CFG_HOSTIF

#include "hostif.h"
#include "hostif_cfg.h"

/*
 * Global variables
 *******************************************************************************
 */
const hostif_cfg_t hostif_cfg_tag = {
    .if_mode = CONFIG_HOSTIF_MODE,
    .filter_mode = CONFIG_HOSTIF_FILTER_MODE,
    .buf_num_total = CONFIG_HOSTIF_BUF_NUM_TOTAL,
    .rxbuf_num_thres = CONFIG_HOSTIF_RX_BUF_NUM_THRESHOLD,
};

__HOSTIF_BUF_POOL uint8_t hostif_buffer_pool_1[1624 * CONFIG_HOSTIF_BUF_NUM_TOTAL];

/*
 * Functions
 *******************************************************************************
 */

HOST_TYPE_T hostif_type_get(void)
{
    #if defined(CONFIG_SDIO)
    return SDIO_HOST;
    #elif defined(CONFIG_USB)
    return USB_HOST;
    #endif
}

HOST_MODE_T hostif_mode_get(void)
{
    return hostif_cfg_tag.if_mode;
}

uint8_t hostif_filter_type_get(void)
{
    return hostif_cfg_tag.filter_mode;
}

uint8_t hostif_buf_num_total_get(void)
{
    return hostif_cfg_tag.buf_num_total;
}

uint8_t hostif_rxbuf_num_threshold_get(void)
{
    return hostif_cfg_tag.rxbuf_num_thres;
}
#endif /* CFG_HOSTIF */
