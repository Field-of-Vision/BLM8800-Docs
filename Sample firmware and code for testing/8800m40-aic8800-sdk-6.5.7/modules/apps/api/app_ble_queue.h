/***
 * ble_task_msg.h
 */

#ifndef _APP_BLE_QUEUE_H_
#define _APP_BLE_QUEUE_H_

#include <rtos.h>
#if PLF_AIC8800
#include "bt_aic8800_drvif.h"
#elif PLF_AIC8800MC
#include "bt_aic8800mc_drvif.h"
#elif PLF_AIC8800M40
#include "bt_aic8800m40_drvif.h"
#else
#error "Invalid platform for btdm"
#endif

typedef enum _ble_only_msg {
        BLE_DEINIT_DONE                         = 0,
        BLE_DEINIT_START                           ,
        BLE_SET_LP_LEVEL                           ,
        BLE_TIMER_NOTIFY                           ,
        BLE_DATA_SEND_NOTIFY                       ,
        BLE_DATA_SEND_START                        ,
        BLE_SCAN_START                             ,
        BLE_SCAN_STOP                              ,
        BLE_INIT_START                             ,
        BLE_INIT_STOP                              ,
        BLE_ADV_DATA_SET                           ,
        BLE_ADV_SCAN_RES_SET                       ,
        BLE_ADV_DATA_UPDATE                        ,
        BLE_ADV_SCAN_RES_UPDATE                    ,
        BLE_ADV_PARAM_UPDATE                       ,
        BLE_ADV_STOP                               ,
        BLE_ADV_START                              ,
        BLE_ADV_RESTART                            ,
        BLE_DISCONNECT                             ,
        BLE_CON_PARAM_UPDATE                       ,
        BLE_DELETE_BOND                            ,
        DUT_TEST                                   ,
        DUT_NO_SCAN                                ,
        DUT_ISCAN                                  ,
        DUT_PSCAN                                  ,
        DUT_BOTH_SCAN                              ,
        NON_SIGNALING_TEST                         ,
        BLE_UDFC_CREATE_CONN                       ,
        BLE_UDFC_CONN_CANCEL                       ,
        BLE_UDFC_WRITE                             ,
        BLE_UDFC_WRITE_NO_RESPONSE                 ,
        BLE_UDFC_READ                              ,
        BLE_UDFC_NOTIFICATION_CFG                  ,
        BLE_UDFC_INDICATION_CFG                    ,
        BLE_UDFC_DISCOVER                          ,
        BLE_UDFS_UPDATE_RD_VAL                     ,
        BLE_UDFS_SEND_NOTIFICATION                 ,
        BLE_UDFS_SEND_INDICATION                   ,
        BLE_UDFS_SEND_DBINIT                       ,
        BLE_CON_DISABLED                           ,
        BLE_ADV_DISABLED                           ,
        BLE_SCAN_DISABLED                          ,
        BLE_EXCHANGE_MTU                           ,
        BLE_DBG_PRINT_TOG                          ,
        BLE_START_BONDING                          ,
}ble_only_msg;

typedef struct{
    ///6-byte array address value
    uint8_t  addr[6];
} BdAddr_t;

typedef struct{
    /// BD Address of device
    BdAddr_t addr;
    /// Address type of the device 0=public/1=private random
    uint8_t addr_type;
}GapAddr_t;

typedef struct{
    uint16_t codec_type;
    uint8_t state;
}AudtransmitStruct;

typedef struct{
    uint16_t len;
    uint8_t data[32];
}AdvDataUpdateStruct;

typedef struct{
    uint32_t adv_intv_min;
    uint32_t adv_intv_max;
}AdvParamUpdateStruct;

typedef struct{
    uint8_t conidx;
    uint16_t conn_intv_min;
    uint16_t conn_intv_max;
    uint16_t conn_latency;
    uint16_t time_out;
}ConParamUpdateStruct;

typedef struct{
    uint8_t conidx;
    uint16_t handle;
    bool cfg_en;
    uint32_t len;
    uint8_t *data;
    GapAddr_t addr_t;
}UdfcParamStruct;

typedef struct{
    uint8_t conidx;
    uint16_t prf_user_id;
    uint16_t att_idx;
    uint32_t len;
    uint8_t *data;
}UdfsParamStruct;

typedef struct{
    uint8_t conidx;
    uint16_t mtu;
}ExchangeMtuStruct;

typedef struct _ble_msg_param {
    union {
        uint32_t value;
        AudtransmitStruct audt_cfg;
        AdvDataUpdateStruct adv_data;
        AdvParamUpdateStruct adv_param;
        ConParamUpdateStruct con_param;
        UdfcParamStruct udfc_param;
        UdfsParamStruct udfs_param;
        ExchangeMtuStruct ex_mtu;
    }p;
} ble_msg_param;


typedef struct {
    uint32_t msg_id;
    ble_msg_param param;
} APP_BLE_ONLY_MSG;

int app_ble_only_msg_init(void);
int app_ble_only_msg_deinit(void);
int app_ble_lp_level_msg_send(uint8_t level);
int app_ble_con_disabled_msg_send(uint8_t status);
int app_ble_adv_disabled_msg_send(uint8_t status);
int app_ble_scan_disabled_msg_send(uint8_t status);

int app_ble_deint_start_msg_send(void);
int app_ble_deint_done_msg_send(void);

int app_ble_only_msg_send(APP_BLE_ONLY_MSG* msg);
int app_ble_only_msg_send_isr(APP_BLE_ONLY_MSG* msg);


int app_ble_enter_dut_msg_send(void);
int app_ble_enter_non_signaling_test_msg_send(void);
int app_ble_wr_scan_en(unsigned int scan_en);
int app_ble_scan_msg_start(void);
int app_ble_scan_msg_stop(void);
int app_ble_init_msg_start(void);
int app_ble_init_msg_stop(void);
int app_ble_adv_data_set_msg_send(uint16_t len,uint8_t *data);
int app_ble_adv_scan_res_set_msg_send(uint16_t len,uint8_t *data);
int app_ble_adv_data_update_msg_send(uint16_t len,uint8_t *data);
int app_ble_adv_scan_res_update_msg_send(uint16_t len,uint8_t *data);
int app_ble_adv_param_update_msg_send(uint32_t adv_intv_min, uint32_t adv_intv_max);
int app_ble_adv_stop_msg_send(void);
int app_ble_adv_start_msg_send(void);
int app_ble_adv_restart_msg_send(void);
int app_ble_disconnect_msg_send(uint8_t conidx);
int app_ble_con_param_msg_send(uint8_t conidx, uint16_t conn_intv_min, uint16_t conn_intv_max,
                        uint16_t conn_latency, uint16_t time_out);
int app_ble_del_bond_msg_send(uint8_t conidx);
int app_ble_data_send_timer_notify(void);
int app_ble_data_send_start(uint16_t codec_type, uint8_t state);


int app_ble_udfc_connect(uint8_t *addr, uint8_t addr_type);
int app_ble_udfc_connect_cancel(void);
int app_ble_udfc_write(uint8_t conidx,uint16_t handle, uint32_t len,uint8_t *data);
int app_ble_udfc_write_no_response(uint8_t conidx,uint16_t handle, uint32_t len,uint8_t *data);
int app_ble_udfc_read(uint8_t conidx,uint16_t handle);
int app_ble_udfc_notification_cfg(uint8_t conidx,uint16_t handle, bool cfg_en);
int app_ble_udfc_indication_cfg(uint8_t conidx,uint16_t handle, bool cfg_en);
int app_ble_udfc_discover(uint8_t conidx);

int app_ble_udfs_update_read_value(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length);
int app_ble_udfs_send_notification(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length);
int app_ble_udfs_send_indication(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length);
int app_ble_udfs_send_db_init(void);

int app_ble_exchange_mtu(uint8_t conidx,uint16_t mtu);
int app_ble_set_print(uint32_t en_flag);
int app_ble_start_bonding(uint8_t conidx);

#endif /* _APP_BLE_QUEUE_H_ */
