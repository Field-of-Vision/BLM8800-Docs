/**
 ****************************************************************************************
 *
 * @file app.h
 *
 * @brief Application entry point
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef APP_H_
#define APP_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup RICOW
 *
 * @brief Application entry point.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW configuration
#if (BLE_APP_PRESENT)

#include <stdint.h>          // Standard Integer Definition
#include "co_bt.h"           // Common BT Definitions
#include "arch.h"            // Platform Definitions
#include "gapc.h"            // GAPC Definitions

#include "gapm_task.h"
#include "gattc_task.h"
#include "app_task.h"

/*
 * DEFINES
 ****************************************************************************************
 */
/// Maximal length of the Device Name value
#define APP_DEVICE_NAME_MAX_LEN      (32)
/*
 * MACROS
 ****************************************************************************************
 */

#define APP_HANDLERS(subtask)    {&subtask##_msg_handler_list[0], ARRAY_LEN(subtask##_msg_handler_list)}

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/// Scan Initiating machine
enum app_init_state
{
    ///
    APP_INIT_STATE_IDLE = 0,
    ///
    APP_INIT_STATE_CREATING,
    ///
    APP_INIT_STATE_CREATED,
    ///
    APP_INIT_STATE_STARING,
    ///
    APP_INIT_STATE_STARTED,
    ///
    APP_INIT_STATE_STOPPING,
};

/// Advertising state machine
enum app_adv_state
{
    /// Advertising activity does not exists
    APP_ADV_STATE_IDLE = 0,
    /// Creating advertising activity
    APP_ADV_STATE_CREATING,
    /// Setting advertising data
    APP_ADV_STATE_SETTING_ADV_DATA,
    /// Setting scan response data
    APP_ADV_STATE_SETTING_SCAN_RSP_DATA,

    /// Advertising activity created
    APP_ADV_STATE_CREATED,
    /// Starting advertising activity
    APP_ADV_STATE_STARTING,
    /// Advertising activity started
    APP_ADV_STATE_STARTED,
    /// Stopping advertising activity
    APP_ADV_STATE_STOPPING,
    /// Upddate advertising data
    APP_ADV_STATE_UPDATE_ADV_DATA,
    /// Upddate advertising scan responce data
    APP_ADV_STATE_UPDATE_ADV_SCAN_RES,
};

/// Scan state machine
enum app_scan_state
{
    ///
    APP_SCAN_STATE_IDLE = 0,
    ///
    APP_SCAN_STATE_CREATING,
    ///
    APP_SCAN_STATE_CREATED,
    ///
    APP_SCAN_STATE_STARTING,
    ///
    APP_SCAN_STATE_STARTED,
    ///
    APP_SCAN_STATE_STOPPING,
};

enum app_deinit_flag
{
    APP_DEINIT_FLAG_ADV = BIT0,
    APP_DEINIT_FLAG_SCAN = BIT1,
    APP_DEINIT_FLAG_CON = BIT2,
};

enum APP_USER_CB_REG_T {
    APP_USER_CB_0 = 0,
    APP_USER_CB_1,
    APP_USER_CB_2,
    APP_USER_CB_3,
    APP_USER_CB_MAX
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Structure containing information about the handlers for an application subtask
struct app_subtask_handlers
{
    /// Pointer to the message handler table
    const struct ke_msg_handler *p_msg_handler_tab;
    /// Number of messages handled
    uint16_t msg_cnt;
};

/// Application environment structure
struct app_env_tag
{
    /// Connection handle
    uint16_t conhdl[APP_IDX_MAX];//conhdl[conidx]

    /// Advertising activity index
    uint8_t adv_actv_idx;
    /// Previous advertising state (@see enum app_adv_state)
    uint8_t adv_state_prv;

    /// Current advertising state (@see enum app_adv_state)
    uint8_t adv_state;
    /// Next expected operation completed event
    uint8_t adv_op;

    /// Last initialized profile
    uint8_t next_svc;

    /// Bonding status
    bool bonded;

    /// Device Name length
    uint8_t dev_name_len;
    /// Device Name
    uint8_t dev_name[APP_DEVICE_NAME_MAX_LEN];

    /// Appearance
    uint16_t appearance;

    /// Local device IRK
    uint8_t loc_irk[KEY_LEN];

    /// Secure Connections on current link
    bool sec_con_enabled;

    /// Counter used to generate IRK
    uint8_t rand_cnt;

    /// Delete bonding
    bool del_bond;

    /// Scan activity index
    uint8_t scan_actv_idx;
    /// Current scan state (@see enum app_scan_state)
    uint8_t scan_state;
    /// Next expected operation completed event
    uint8_t scan_op;

    /// Initiating State
    uint8_t init_state;
    /// Initiating activity index
    uint8_t init_actv_idx;
    /// Next expected operation completed event
    uint8_t init_op;
};

typedef struct app_env_tag AonBleAppEnv;

struct ble_ad_filter
{
    uint8_t len;
    uint8_t ad_type;
    uint8_t data[ADV_DATA_LEN-1];
};

struct ble_app_user_info
{
    /// Device Name length
    uint16_t dev_name_len;
    /// Device Name
    uint8_t dev_name[32];
    /// Advertising Data length
    uint16_t adv_data_len;
    /// Advertising data
    uint8_t adv_data[ADV_DATA_LEN];
    /// Scan Response Data length
    uint16_t scan_res_len;
    /// Scan Response Data
    uint8_t scan_res[ADV_DATA_LEN];
    /// Advertising parameters
    bool user_adv_param;
    /// Own address type (@see enum gapm_own_addr)
    uint8_t own_addr_type;
    /// BD Address of device
    bd_addr_t own_addr;
    /// Own address type (@see enum gapm_own_addr)
    uint8_t peer_addr_type;
    /// BD Address of device
    bd_addr_t peer_addr;
    /// Advertising duration (in unit of 10ms). 0 means that advertising continues
    /// until the host disable it
    uint16_t adv_duration;
    /// For prop parameter, @see enum gapm_leg_adv_prop, @see enum gapm_ext_adv_prop and @see enum gapm_per_adv_prop for help
    struct gapm_adv_create_param adv_param;
    struct gapm_scan_param scan_param;
    uint16_t scan_duration;
    /// app_user_callback
    struct app_callbacks *user_app_callback;
    /// adv ad_len ,ad_type ,ad_len filter by user
    struct ble_ad_filter ad_data_filter;
};

typedef struct ble_app_user_info AonBleAppUserInfo;

/// APP callbacks
struct app_callbacks
{
    /// Callback app init
    void (*app_on_init)(void);

    /// Callback app init complete
    bool (*app_on_init_complete)(void);

    /// Callback app add svc
    bool (*app_on_add_svc)(void);

    /// Callback app enable prf
    void (*app_on_enable_prf)(uint8_t, uint8_t);

    /// Callback connect
    void (*app_on_connection)(const uint8_t, struct gapc_connection_req_ind const *);

    /// Callback disconnect
    void (*app_on_disconnect)(struct gapc_disconnect_ind const *,uint8_t);

    /// Callback con param update
    void (*app_on_update_params_request)(struct gapc_param_update_req_ind const *);

    /// Callback adv operation status
    void (*app_on_adv_status)(struct gapm_cmp_evt const *);

};

typedef struct _BleAppOp {
    list_node_t   node;
    uint8_t       opType;
    uint8_t       adv_state;
    uint8_t       adv_state_prv;
} BleAppOp;

struct ble_param_update_req_ind {
    uint8_t conidx;
    struct gapc_param_update_req_ind rmt_req;
    struct gapc_param_update_cfm usr_cfm;
};

struct ble_param_updated_ind {
    uint8_t conidx;
    struct gapc_param_updated_ind ind;
};

struct ble_connection_ind
{
    uint8_t conidx;
    struct gapc_connection_req_ind ind;
};


struct ble_disconnect_ind
{
    uint8_t conidx;
     struct gapc_disconnect_ind ind;
};


struct ble_le_pkt_size_ind
{
    uint8_t conidx;
    struct gapc_le_pkt_size_ind ind;
};


struct ble_mtu_changed_ind
{
    uint8_t conidx;
    struct gattc_mtu_changed_ind mtu_ind;
};

typedef void(*app_user_msg_cb)(uint16_t event,uint8_t *buff);

/*
 * GLOBAL VARIABLE DECLARATION
 ****************************************************************************************
 */

/// Application environment
extern struct app_env_tag app_env;
extern struct ble_app_user_info ble_user_info;
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
void app_user_set_msg_cb(enum APP_USER_CB_REG_T user_id,app_user_msg_cb func);
void app_user_cb_poll(uint16_t event,uint8_t *buff);

void appm_set_phy(uint8_t conidx);
void appm_set_pkt_len(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Initialize the BLE demo application.
 ****************************************************************************************
 */
void appm_init(void);

/**
 ****************************************************************************************
 * @brief Add a required service in the database
 ****************************************************************************************
 */
bool appm_add_svc(void);


/**
 ****************************************************************************************
 * @brief
 ****************************************************************************************
 */
void appm_adv_fsm_next(void);

/**
 ****************************************************************************************
 * @brief
 ****************************************************************************************
 */
void appm_scan_fsm_next(void);

/**
 ****************************************************************************************
 * @brief
 ****************************************************************************************
 */
void appm_init_fsm_next(void);

/**
 ****************************************************************************************
 * @brief Send to request to update the connection parameters
 ****************************************************************************************
 */
void appm_update_param(struct gapc_conn_param *conn_param,uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Send a disconnection request
 ****************************************************************************************
 */
void appm_disconnect(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Retrieve device name
 *
 * @param[out] device name
 *
 * @return name length
 ****************************************************************************************
 */
uint8_t appm_get_dev_name(uint8_t* name);

/**
 ****************************************************************************************
 * @brief Start/stop advertising
 *
 * @param[in] start     True if advertising has to be started, else false
 ****************************************************************************************
 */
void appm_update_adv_state(bool start);

/**
 ****************************************************************************************
 * @brief Start/stop scan
 *
 * @param[in] start     True if scan has to be started, else false
 ****************************************************************************************
 */
void appm_update_scan_state(bool start);

/**
 ****************************************************************************************
 * @brief Start/stop initiating
 *
 * @param[in] none
 ****************************************************************************************
 */
void appm_update_init_state(bool start);

/**
 ****************************************************************************************
 * @brief delete advertising
 *
 * @param[in] none
 ****************************************************************************************
 */

void appm_delete_advertising(void);
/**
 ****************************************************************************************
 * @brief Return if the device is currently bonded
 ****************************************************************************************
 */
bool app_sec_get_bond_status(void);

uint8_t appm_set_dev_name(char* name, uint8_t len);
void appm_set_dev_appearance(uint16_t appearance);
void appm_set_dev_info(struct gapc_set_dev_info_req_ind const *param, uint8_t* status);
void appm_set_whitelist(struct white_list* wl ,uint8_t num);

void ble_enable(void);
void ble_disable(void);
void ble_disabled(void);
bool ble_activity_enabled(void);
void app_ble_env_init();
void app_ble_addr_init(uint8_t *addr, uint8_t own_addr_type);
void app_ble_peer_addr_init(uint8_t *addr, uint8_t peer_addr_type);
void app_ble_set_dev_name(char* name, uint8_t len);
void app_ble_set_adv_data(uint8_t *buf, uint16_t buf_len);
void app_ble_set_scan_response_data(uint8_t *buf, uint16_t buf_len);
void app_ble_set_ad_filter(struct ble_ad_filter *ad_filter);
uint8_t app_ble_set_adv_params(struct gapm_adv_create_param* params, uint16_t adv_duration);
uint8_t app_ble_update_adv_data();
uint8_t app_ble_update_adv_params(uint32_t adv_intv_min, uint32_t adv_intv_max);
uint8_t app_ble_update_adv_scan_res(void);
uint8_t app_ble_restart_adv(void);
uint8_t app_ble_update_con_params(uint8_t conidx,uint16_t conn_intv_min, uint16_t conn_intv_max,uint16_t conn_latency, uint16_t time_out);
uint8_t app_ble_start_init();
uint8_t app_ble_stop_init();
uint8_t app_ble_start_scan();
uint8_t app_ble_stop_scan();
uint8_t app_ble_start_adv();
uint8_t app_ble_stop_adv();
uint8_t app_ble_disconnect(uint8_t conidx);
void app_ble_register_callbak(struct app_callbacks *ble_app_callbak);
void app_ble_update_addr(uint8_t *addr);
void app_ble_oplist_init(void);
void app_ble_check_oplist(void);
void app_ble_oplist_insert(uint8_t optype ,uint8_t adv_state ,uint8_t adv_state_prv ,void *cmdptr);
bool app_env_check(void);

/// @} APP

#endif //(BLE_APP_PRESENT)

#endif // APP_H_
