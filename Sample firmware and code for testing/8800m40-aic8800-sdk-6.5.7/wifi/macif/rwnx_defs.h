#ifndef _RWNX_DEFS_H_
#define _RWNX_DEFS_H_

#include "ipc_host.h"
#include "rwnx_cmds.h"
#include "rwnx_utils.h"

enum survey_info_flags {
    SURVEY_INFO_NOISE_DBM       = BIT(0),
    SURVEY_INFO_IN_USE          = BIT(1),
    SURVEY_INFO_TIME            = BIT(2),
    SURVEY_INFO_TIME_BUSY       = BIT(3),
    SURVEY_INFO_TIME_EXT_BUSY   = BIT(4),
    SURVEY_INFO_TIME_RX         = BIT(5),
    SURVEY_INFO_TIME_TX         = BIT(6),
    SURVEY_INFO_TIME_SCAN       = BIT(7),
};


/* Structure containing channel survey information received from MAC */
struct freq_survey_info {
	unsigned int freq;
    // Filled
    uint32_t filled;
    // Amount of time in ms the radio spent on the channel
    uint32_t chan_time_ms;
    // Amount of time the primary channel was sensed busy
    uint32_t chan_time_busy_ms;
    // Noise in dbm
    int8_t noise_dbm;
};

/* Structure that will contains all RoC information received from cfg80211 */
struct rwnx_roc_elem {
    struct mac_chan_def chan;
    unsigned int duration;
    /* Used to avoid call of CFG80211 callback upon expiration of RoC */
    bool mgmt_roc;
    /* Indicate if we have switch on the RoC channel */
    bool on_chan;
};

//#define ipc_host_env_tag ipc_fhost_host_env_tag;
/**
 * struct rwnx_hw - Main driver data
 *
 * @dev: device structure
 * @plat: Platform info
 * @task: Tasklet used to IRQ bottom half
 * @class: Class used to create device
 * @major: Major number for the driver
 * @term: Term device structure
 * @trace: Trace device structure
 * @cb_lock: Lock used to run message callback
 * @ipc_env: Pointer to IPC shared struture
 * @e2amsgs_pool: Pool of DMA buffer for messages push by FW
 * @dbgmsgs_pool: Pool of DMA buffer for dbg messages push by FW
 * @dbgdump_elem: DMA buffer for FW to upload debug dump (TODO)
 * @cmd_mgr: Command (aka fw message) structure
 * @mod_params: Module parameters used to initialize configuration buffer
 * @config: Configuration buffer passed to FW before start
 * @tv: Time at which we started the firmware
 * @debugfs: debugfs entries configuration
 */
struct rwnx_hw {

    struct ipc_host_env_tag *ipc_env;
    struct rwnx_ipc_elem_pool e2amsgs_pool;
    //struct rwnx_ipc_elem_pool dbgmsgs_pool;
    //struct rwnx_ipc_dbgdump_elem dbgdump_elem;
    //struct rwnx_ipc_elem_pool e2arxdesc_pool;
    #if NX_P2P
    /* RoC Management */
    struct rwnx_roc_elem *roc_elem;             /* Information provided by cfg80211 in its remain on channel request */
    uint32_t roc_cookie_cnt;                         /* Counter used to identify RoC request sent by cfg80211 */
    #endif
    struct rwnx_cmd_mgr cmd_mgr;
    //struct rwnx_mod_params *mod_params;
    //uint32_t config[IPC_CFG_SIZE];
};

struct rwnx_term_stream
{
    //struct list_head list;
    //struct rwnx_term *term;
    //char buf[2 * TERM_BUFFER_SIZE];
    char *read, *write;
    int avail, last_idx;
};
extern struct freq_survey_info survey[];
extern struct rwnx_hw hw_env;

int rwnx_ipc_init(struct rwnx_hw *rwnx_hw, void *shared_ram);
void rwnx_ipc_start(struct rwnx_hw *rwnx_hw);
void rwnx_ipc_msg_push(struct rwnx_hw *rwnx_hw, void *msg_buf, uint16_t len);
int rwnx_host_send_msg(struct rwnx_hw *rwnx_hw, const void *msg_params,
                         int reqcfm, lmac_msg_id_t reqid, void *cfm);
int rwnx_ipc_txdesc_push(struct rwnx_hw *rwnx_hw, void *tx_desc,
                          void *hostid, int hw_queue);
int rwnx_ipc_txdesc_direct(void *tx_desc);
int rwnx_ipc_rxbuf_elem_alloc(struct rwnx_hw *rwnx_hw);
void wifi_patch_prepare(void);

#endif
