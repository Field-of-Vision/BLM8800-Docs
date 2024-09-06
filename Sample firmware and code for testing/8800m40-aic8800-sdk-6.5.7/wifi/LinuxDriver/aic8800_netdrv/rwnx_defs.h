/**
 ******************************************************************************
 *
 * @file rwnx_defs.h
 *
 * @brief Main driver structure declarations for fullmac driver
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ******************************************************************************
 */

#ifndef _RWNX_DEFS_H_
#define _RWNX_DEFS_H_

#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/dmapool.h>
#include <linux/skbuff.h>
#include <net/cfg80211.h>
#include <linux/slab.h>

#include "rwnx_tx.h"
#include "rwnx_rx.h"
#include "rwnx_utils.h"
#include "rwnx_platform.h"

#ifdef AICWF_SDIO_SUPPORT
#include "aicwf_sdio.h"
#include "sdio_host.h"
#endif

#ifdef AICWF_USB_SUPPORT
#include "usb_host.h"
#endif

#define TERM_BUFFER_SIZE 4096

/**
 * struct rwnx_term - Term device data
 *
 * @semaphore: Semaphore to ensure that no msg will be sent until previous one
 * is acknowledged by fw. Acknowledge is done in tasklet so cannot use mutex.
 * @cdev: Check device structure
 * @dev: device structure
 * @buf_lock: Lock to read/write debug msg buffer
 * @buf: Share buffer to store debug msg reported by fw
 * @buf_idx: Total number of bytes written in the share buffer since
 * device creation
 * @queue: Wait queue for readers
 * @stream_list: List of streams opened on this terminal
 */
struct rwnx_term {
    struct semaphore sem;
    struct cdev cdev;
    struct device *dev;

    spinlock_t buf_lock;
    char buf[TERM_BUFFER_SIZE];
    int buf_idx;
    wait_queue_head_t queue;
    struct list_head stream_list;
};

/**
 * struct rwnx_term_stream - Private structure for one stream
 *
 * @list: Node for term->stream_list
 * @term: Pointer to &struct rwnx_term structure
 * @buf: Private buffer for the stream
 * @read: Read pointer on private buffer
 * @write: Write pointer on private buffer
 * @avail: Number of bytes availalbe in private buffer
 * @last_idx: Value of &struct rwnx_term.buf_idx at last read
 */
struct rwnx_term_stream
{
    struct list_head list;
    struct rwnx_term *term;
    char buf[2 * TERM_BUFFER_SIZE];
    char *read, *write;
    int avail, last_idx;
};

/**
 * struct rwnx_trace - Trace device data
 *
 * @cdev: Check device structure
 * @dev: device structure
 * @fw: Fw trace control structure
 */
struct rwnx_trace {
    struct cdev cdev;
    struct device *dev;
};

/**
 * struct rwnx_key - Key information
 *
 * @hw_idx: Idx of the key from hardware point of view
 */
struct rwnx_key {
    u8 hw_idx;
};

/*
 * Structure used to save information relative to the managed interfaces.
 * This is also linked within the rwnx_hw vifs list.
 *
 */
struct rwnx_vif {
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 7, 0)
    u8 address[ETH_ALEN] __aligned(sizeof(u16));
#endif
    struct list_head list;
    struct rwnx_hw *rwnx_hw;
    struct wireless_dev wdev;
    struct net_device *ndev;
    struct net_device_stats net_stats;
    struct rwnx_key key[6];
    u8 drv_vif_index;           /* Identifier of the VIF in driver */
    u8 vif_index;               /* Identifier of the station in FW */
    bool up;                    /* Indicate if associated netdev is up
                                   (i.e. Interface is created at fw level) */
};

struct rwnx_hw {
    struct device *dev;
    struct rwnx_plat *plat;
    struct tasklet_struct task;
    struct class* class;

    struct rwnx_term term;
    struct rwnx_trace trace;

    spinlock_t cb_lock;

    //struct device *dev;
    #ifdef AICWF_SDIO_SUPPORT
    struct aic_sdio_dev *sdiodev;
    #endif
    #ifdef AICWF_USB_SUPPORT
    struct aic_usb_dev *usbdev;
    #endif

    struct rwnx_vif *vif_table[NX_VIRT_DEV_MAX + NX_REMOTE_STA_MAX]; /* indexed with fw id */
    struct rwnx_cmd_mgr *cmd_mgr;
};

void rwnx_term_stream_write_mod(struct rwnx_term_stream *stream, char *src, unsigned int size);
void rwnx_term_write_shared(struct rwnx_term *term, char *data, size_t size);
void rwnx_term_ops_exit(void);
int rwnx_trace_pre_reload(struct rwnx_hw *rwnx_hw);
void rwnx_trace_post_reload(struct rwnx_hw *rwnx_hw);
int rwnx_fhost_send_msg(struct rwnx_hw *rwnx_hw, struct rwnx_term_stream *stream, const char *msg, char *resp);

#endif /* _RWNX_DEFS_H_ */
