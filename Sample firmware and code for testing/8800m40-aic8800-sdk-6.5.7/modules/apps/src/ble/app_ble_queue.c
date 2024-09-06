#include "tgt_cfg_bt.h"
#if PLF_BT_STACK == 1

#include "rtos.h"
#include "app_ble_only.h"
#if PLF_BLE_ONLY
#include "ble_task_msg.h"
#include "ble_task.h"
#include "aic_ble_adp_api.h"
#endif
#if PLF_BTDM
#include "bt_task_msg.h"
#include "aic_adp_api.h"
#endif
#include "app_ble_queue.h"
#include "flash_api_btdm.h"
#include "aicble.h"
#include "aicble_dbg.h"

#define APP_BLE_ONLY_MSG_MAX (5)
static rtos_queue app_ble_only_msg_queue;
extern uint8_t ble_addr[6];

int app_ble_only_msg_process(APP_BLE_ONLY_MSG* msg)
{
    int status = -1;
    if(BLE_DATA_SEND_NOTIFY != msg->msg_id){
        TRACE("APP:ble_only_msg id:%d \n",msg->msg_id);
    }
    switch (msg->msg_id) {
        case BLE_CON_DISABLED:
            #if PLF_BLE_ONLY
            if (ble_callback) {
                ble_callback(APP_DEINIT_FLAG_CON, msg->param.p.value);
            }
            #endif
            break;
        case BLE_ADV_DISABLED:
            #if PLF_BLE_ONLY
            if (ble_callback) {
                ble_callback(APP_DEINIT_FLAG_ADV,  msg->param.p.value);
            }
            #endif
            break;
        case BLE_SCAN_DISABLED:
            #if PLF_BLE_ONLY
            if (ble_callback) {
                ble_callback(APP_DEINIT_FLAG_SCAN, msg->param.p.value);
            }
            #endif
            break;
        case BLE_DEINIT_DONE:
            #if PLF_BLE_ONLY
            status = ble_task_delete();
            #endif
            break;
        case BLE_DEINIT_START:
            #if PLF_BLE_ONLY
            aic_adp_ble_deinit();
            #endif
            break;
        case BLE_SET_LP_LEVEL:
            #if PLF_BLE_ONLY
            TRACE("APP: ble lp level = %x\n",msg->param.p.value);
            aic_adp_set_lp_level_ble_only((uint8_t)msg->param.p.value);
            #endif
            break;
        case DUT_TEST:
            TRACE("APP: enter dut test\n");
            bt_drv_enable_dut();
            break;
        case DUT_NO_SCAN:
        case DUT_ISCAN:
        case DUT_PSCAN:
        case DUT_BOTH_SCAN:
            {
                bt_drv_scan_en(msg->msg_id - DUT_NO_SCAN);
            }
            break;
        case NON_SIGNALING_TEST:
            #if PLF_BT_TESTMODE
            bt_drv_enter_non_signaling_test();
            #endif
            break;
        case BLE_TIMER_NOTIFY:
            aic_adp_rw_timer_notify();
            break;
        case BLE_SCAN_START:
            app_ble_start_scan();
            break;
        case BLE_SCAN_STOP:
            app_ble_stop_scan();
            break;
        case BLE_INIT_START:
            app_ble_start_init();
            break;
        case BLE_INIT_STOP:
            app_ble_stop_init();
            break;
        case BLE_ADV_DATA_SET:
            {
                uint8_t buf[32];
                if(msg->param.p.adv_data.len){
                    memcpy(buf, msg->param.p.adv_data.data, msg->param.p.adv_data.len);
                    app_ble_set_adv_data(buf, msg->param.p.adv_data.len);
                }
            }
            break;
        case BLE_ADV_SCAN_RES_SET:
            {
                uint8_t buf[32];
                if(msg->param.p.adv_data.len){
                    memcpy(buf, msg->param.p.adv_data.data, msg->param.p.adv_data.len);
                    app_ble_set_scan_response_data(buf, msg->param.p.adv_data.len);
                }
            }
            break;
        case BLE_ADV_DATA_UPDATE:
            {
                uint8_t buf[32];
                if(msg->param.p.adv_data.len){
                    memcpy(buf, msg->param.p.adv_data.data, msg->param.p.adv_data.len);
                    app_ble_set_adv_data(buf, msg->param.p.adv_data.len);
                }else{
                    buf[0] = APP_UPDATE_DATA_LEN + 1;
                    buf[1] = GAP_AD_TYPE_COMPLETE_NAME;
                    memcpy(buf + 2, APP_UPDATE_DATA, APP_UPDATE_DATA_LEN);
                    app_ble_set_adv_data(buf, APP_UPDATE_DATA_LEN + 2);
                }
                app_ble_update_adv_data();
            }
            break;
        case BLE_ADV_SCAN_RES_UPDATE:
            {
                uint8_t buf[32];
                if(msg->param.p.adv_data.len){
                    memcpy(buf, msg->param.p.adv_data.data, msg->param.p.adv_data.len);
                    app_ble_set_scan_response_data(buf, msg->param.p.adv_data.len);
                    app_ble_update_adv_scan_res();
                }
            }
            break;
        case BLE_ADV_PARAM_UPDATE:
            {
                TRACE("ble_adv_param_update interval_min 0x%x, max 0x%x\n",\
                    msg->param.p.adv_param.adv_intv_min,msg->param.p.adv_param.adv_intv_max);
                if (app_ble_update_adv_params(msg->param.p.adv_param.adv_intv_min, msg->param.p.adv_param.adv_intv_max)) {
                    TRACE("ERROR\r\n");
                    return -1;
                }
            }
            break;
        case BLE_ADV_STOP:
            app_ble_stop_adv();
            break;
        case BLE_ADV_START:
            app_ble_start_adv();
            break;
        case BLE_ADV_RESTART:
            app_ble_restart_adv();
            break;
        case BLE_DISCONNECT:
            app_ble_disconnect(msg->param.p.value);
            break;
        case BLE_CON_PARAM_UPDATE:
            TRACE("ble_con_param_update conidx %d, interval_min 0x%x, max 0x%x, latency 0x%x, to 0x%x\n",msg->param.p.con_param.conidx,\
                msg->param.p.con_param.conn_intv_min,msg->param.p.con_param.conn_intv_max,\
                msg->param.p.con_param.conn_latency,msg->param.p.con_param.time_out);
            app_ble_update_con_params(msg->param.p.con_param.conidx,msg->param.p.con_param.conn_intv_min, msg->param.p.con_param.conn_intv_max,
                msg->param.p.con_param.conn_latency,msg->param.p.con_param.time_out);
            break;
        case BLE_DELETE_BOND:
            {
                uint8_t conidx = msg->param.p.value;
                app_env.del_bond = true;
                app_sec_remove_bond();
                ble_addr[0] = co_rand_byte();
                flash_btdm_le_rand_addr_write(&ble_addr[0]);
                app_ble_update_addr(&ble_addr[0]);
                if (app_env.adv_state == APP_ADV_STATE_STARTED) {
                    app_ble_stop_adv();
                    appm_delete_advertising();
                }
                if (ke_state_get(KE_BUILD_ID(TASK_APP,conidx)) == APPM_CONNECTED) {
                    app_ble_disconnect(conidx);
                }
                //app_ble_start_adv();
            }
            break;
        case BLE_DATA_SEND_NOTIFY:
            #if BLE_APP_AUDTRANSMITS || BLE_APP_AUDTRANSMITS
            app_ble_audtransmit_timer_notify_handler();
            #endif
            break;
        case BLE_DATA_SEND_START:
            #if BLE_APP_AUDTRANSMITC
                app_atc_send_aud_ctrl(msg->param.p.audt_cfg.codec_type,msg->param.p.audt_cfg.state);
            #endif
            #if BLE_APP_AUDTRANSMITS
                app_ats_send_aud_info(msg->param.p.audt_cfg.codec_type,msg->param.p.audt_cfg.state);
            #endif
            break;
        case BLE_UDFC_CREATE_CONN:
            {
                #if BLE_APP_UDFC
                app_ble_peer_addr_init(msg->param.p.udfc_param.addr_t.addr.addr,msg->param.p.udfc_param.addr_t.addr_type);
                app_ble_init_msg_start();
                #endif
            }
            break;
        case BLE_UDFC_CONN_CANCEL:
            {
                #if BLE_APP_UDFC
                app_ble_stop_init();
                #endif
            }
            break;
        case BLE_UDFC_WRITE:
            {
                #if BLE_APP_UDFC
                uint8_t conidx = msg->param.p.udfc_param.conidx;
                uint16_t handle = msg->param.p.udfc_param.handle;
                uint32_t len = msg->param.p.udfc_param.len;
                uint8_t *data = msg->param.p.udfc_param.data;
                app_udfc_wr_req(conidx,handle,data,len);
                rtos_free(msg->param.p.udfc_param.data);
                #endif
            }
            break;
        case BLE_UDFC_WRITE_NO_RESPONSE:
            {
                #if BLE_APP_UDFC
                uint8_t conidx = msg->param.p.udfc_param.conidx;
                uint16_t handle = msg->param.p.udfc_param.handle;
                uint32_t len = msg->param.p.udfc_param.len;
                uint8_t *data = msg->param.p.udfc_param.data;
                app_udfc_wr_nores_req(conidx,handle,data,len);
                rtos_free(msg->param.p.udfc_param.data);
                #endif
            }
            break;
        case BLE_UDFC_READ:
            {
                #if BLE_APP_UDFC
                uint8_t conidx = msg->param.p.udfc_param.conidx;
                uint16_t handle = msg->param.p.udfc_param.handle;
                app_udfc_rd_req(conidx,handle);
                #endif
            }
            break;
        case BLE_UDFC_NOTIFICATION_CFG:
            {
                #if BLE_APP_UDFC
                uint8_t conidx = msg->param.p.udfc_param.conidx;
                uint16_t handle = msg->param.p.udfc_param.handle;
                bool cfg_en = msg->param.p.udfc_param.cfg_en;
                app_udfc_ntf_cfg_req(conidx,handle,cfg_en);
                #endif
            }
            break;
        case BLE_UDFC_INDICATION_CFG:
            {
                #if BLE_APP_UDFC
                uint8_t conidx = msg->param.p.udfc_param.conidx;
                uint16_t handle = msg->param.p.udfc_param.handle;
                bool cfg_en = msg->param.p.udfc_param.cfg_en;
                app_udfc_ind_cfg_req(conidx,handle,cfg_en);
                #endif
            }
            break;
        case BLE_UDFC_DISCOVER:
            {
                #if BLE_APP_UDFC
                uint8_t conidx = msg->param.p.udfc_param.conidx;
                app_udfc_discover_svc(conidx);
                #endif
            }
            break;
        case BLE_UDFS_UPDATE_RD_VAL:
            {
                #if BLE_APP_UDFS
                uint8_t conidx = msg->param.p.udfs_param.conidx;
                uint16_t prf_user_id = msg->param.p.udfs_param.prf_user_id;
                uint16_t att_idx = msg->param.p.udfs_param.att_idx;
                uint32_t len = msg->param.p.udfs_param.len;
                uint8_t *data = msg->param.p.udfs_param.data;
                app_udfs_update_rd_value(conidx,prf_user_id,att_idx,data,len);
                rtos_free(msg->param.p.udfs_param.data);
                #endif
            }
            break;
        case BLE_UDFS_SEND_NOTIFICATION:
            {
                #if BLE_APP_UDFS
                uint8_t conidx = msg->param.p.udfs_param.conidx;
                uint16_t prf_user_id = msg->param.p.udfs_param.prf_user_id;
                uint16_t att_idx = msg->param.p.udfs_param.att_idx;
                uint32_t len = msg->param.p.udfs_param.len;
                uint8_t *data = msg->param.p.udfs_param.data;
                app_udfs_send_notification(conidx,prf_user_id,att_idx,data,len);
                rtos_free(msg->param.p.udfs_param.data);
                #endif
            }
            break;
        case BLE_UDFS_SEND_INDICATION:
            {
                #if BLE_APP_UDFS
                uint8_t conidx = msg->param.p.udfs_param.conidx;
                uint16_t prf_user_id = msg->param.p.udfs_param.prf_user_id;
                uint16_t att_idx = msg->param.p.udfs_param.att_idx;
                uint32_t len = msg->param.p.udfs_param.len;
                uint8_t *data = msg->param.p.udfs_param.data;
                app_udfs_send_indication(conidx,prf_user_id,att_idx,data,len);
                rtos_free(msg->param.p.udfs_param.data);
                #endif
            }
            break;
        case BLE_UDFS_SEND_DBINIT:
            #if BLE_APP_UDFS
            app_udfs_db_cfg_init();
            #endif
            break;
        case BLE_EXCHANGE_MTU:
            {
                uint8_t conidx = msg->param.p.ex_mtu.conidx;
                uint16_t max_mtu = msg->param.p.ex_mtu.mtu;
                prf_gatt_send_exchange_mtu(NULL,conidx,max_mtu);
            }
            break;
        case BLE_DBG_PRINT_TOG:
            {
                uint32_t en_flag;
                en_flag = msg->param.p.value;
                if(en_flag & 0x20000000)
                    aicble_set_dbgarea(en_flag&0x0fffffff);
                if(en_flag & 0x40000000)
                    aicble_set_dbglevel(en_flag&0x0fffffff);
                if(en_flag & 0x80000000)
                    aicble_set_dumparea(en_flag&0x0fffffff);
            }
            break;
        case BLE_START_BONDING:
            {
                uint8_t conidx = msg->param.p.value;
                prf_start_smp_bonding(conidx,NULL);
            }
            break;
        default:
            break;
    }
    if(BLE_DATA_SEND_NOTIFY != msg->msg_id){
        TRACE("APP: msg id:%d :status:%d exit\n", msg->msg_id, status);
    }
    return status;
}

int app_ble_only_msg_send(APP_BLE_ONLY_MSG* msg)
{
    if(app_ble_only_msg_queue==NULL)
        return -1;
    if(rtos_queue_write(app_ble_only_msg_queue,(void *)msg,(TickType_t)1,false)){
        ASSERT_ERR(0);
    }
    #if PLF_BLE_ONLY
    ble_task_queue_notify(false);
    #endif
    #if !PLF_BLE_ONLY && PLF_BTDM
    bt_task_queue_notify(false);
    #endif
    return 0;
}

int app_ble_only_msg_send_isr(APP_BLE_ONLY_MSG* msg)
{
    if(rtos_queue_write(app_ble_only_msg_queue,(void *)msg,(TickType_t)1,true)){
        ASSERT_ERR(0);
    }
    #if PLF_BLE_ONLY
    ble_task_queue_notify(true);
    #endif
    #if !PLF_BLE_ONLY && PLF_BTDM
    bt_task_queue_notify(true);
    #endif
    return 0;
}


int app_ble_only_msg_get(APP_BLE_ONLY_MSG* QueueMsg)
{
    if(rtos_queue_read(app_ble_only_msg_queue,(void *)QueueMsg,0,0)) {
        return -1;
    }
    return 0;
}

static void app_ble_only_msg_poll(void)
{
    APP_BLE_ONLY_MSG QueueMsg;
    if (!app_ble_only_msg_get(&QueueMsg)){
        app_ble_only_msg_process(&QueueMsg);
    }
}

int app_ble_only_msg_init(void)
{
    if (rtos_queue_create(sizeof(APP_BLE_ONLY_MSG),APP_BLE_ONLY_MSG_MAX,&app_ble_only_msg_queue)){
        TRACE("APP: Failed to Create app_ble_only_msg_queue\n");
        return -1;
    }
    #if PLF_BLE_ONLY
    app_ble_handler_register(BLE_HANDLER_REG_1, app_ble_only_msg_poll);
    #endif
    #if !PLF_BLE_ONLY && PLF_BTDM
    app_bt_handler_register(HANDLER_REG_4, app_ble_only_msg_poll);
    #endif
    return 0;
}

int app_ble_only_msg_deinit(void)
{
    if(app_ble_only_msg_queue){
        rtos_queue_delete(app_ble_only_msg_queue);
        app_ble_only_msg_queue = NULL;
    }
    #if PLF_BLE_ONLY
    app_ble_handler_register(BLE_HANDLER_REG_1, NULL);
    #endif
    #if !PLF_BLE_ONLY && PLF_BTDM
    app_bt_handler_register(HANDLER_REG_4, NULL);
    #endif
    return 0;
}

int app_ble_con_disabled_msg_send(uint8_t status)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_CON_DISABLED;
    msg.param.p.value = status;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_adv_disabled_msg_send(uint8_t status)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_ADV_DISABLED;
    msg.param.p.value = status;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_scan_disabled_msg_send(uint8_t status)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_SCAN_DISABLED;
    msg.param.p.value = status;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_deint_start_msg_send(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_DEINIT_START;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_deint_done_msg_send(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_DEINIT_DONE;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_lp_level_msg_send(uint8_t level)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_SET_LP_LEVEL;
    msg.param.p.value = (uint32_t)level;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_enter_dut_msg_send(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = DUT_TEST;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_enter_non_signaling_test_msg_send(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = NON_SIGNALING_TEST;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_adv_data_set_msg_send(uint16_t len,uint8_t *data)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_ADV_DATA_SET;
    ASSERT_ERR(len <= 29);
    msg.param.p.adv_data.len = len;
    if(len){
        memcpy(msg.param.p.adv_data.data,data,len);
    }
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_adv_scan_res_set_msg_send(uint16_t len,uint8_t *data)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_ADV_SCAN_RES_SET;
    ASSERT_ERR(len <= 29);
    msg.param.p.adv_data.len = len;
    if(len){
        memcpy(msg.param.p.adv_data.data,data,len);
    }
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_adv_data_update_msg_send(uint16_t len,uint8_t *data)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_ADV_DATA_UPDATE;
    ASSERT_ERR(len <= 29);
    msg.param.p.adv_data.len = len;
    if(len){
        memcpy(msg.param.p.adv_data.data,data,len);
    }
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_adv_scan_res_update_msg_send(uint16_t len,uint8_t *data)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_ADV_SCAN_RES_UPDATE;
    ASSERT_ERR(len <= 29);
    msg.param.p.adv_data.len = len;
    if(len){
        memcpy(msg.param.p.adv_data.data,data,len);
    }
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_adv_param_update_msg_send(uint32_t adv_intv_min, uint32_t adv_intv_max)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_ADV_PARAM_UPDATE;
    msg.param.p.adv_param.adv_intv_min = adv_intv_min;
    msg.param.p.adv_param.adv_intv_max = adv_intv_max;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_adv_stop_msg_send(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_ADV_STOP;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_adv_start_msg_send(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_ADV_START;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_adv_restart_msg_send(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_ADV_RESTART;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_disconnect_msg_send(uint8_t conidx)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_DISCONNECT;
    msg.param.p.value = conidx;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_con_param_msg_send(uint8_t conidx, uint16_t conn_intv_min, uint16_t conn_intv_max,
                        uint16_t conn_latency, uint16_t time_out)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_CON_PARAM_UPDATE;
    msg.param.p.con_param.conidx = conidx;
    msg.param.p.con_param.conn_intv_min = conn_intv_min;
    msg.param.p.con_param.conn_intv_max = conn_intv_max;
    msg.param.p.con_param.conn_latency = conn_latency;
    msg.param.p.con_param.time_out = time_out;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_del_bond_msg_send(uint8_t conidx)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_DELETE_BOND;
    msg.param.p.value = conidx;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_scan_msg_start(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_SCAN_START;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_scan_msg_stop(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_SCAN_STOP;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_init_msg_start(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_INIT_START;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_init_msg_stop(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_INIT_STOP;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_wr_scan_en(unsigned int scan_en)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = DUT_NO_SCAN + scan_en;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_rw_timer_notify(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_TIMER_NOTIFY;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_data_send_timer_notify(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_DATA_SEND_NOTIFY;
    app_ble_only_msg_send(&msg);
    TRACE("BLE_APP:ble_data_send\n");
    return 0;
}

int app_ble_data_send_start(uint16_t codec_type, uint8_t state)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_DATA_SEND_START;
    msg.param.p.audt_cfg.codec_type = codec_type;
    msg.param.p.audt_cfg.state = state;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfc_connect(uint8_t *addr, uint8_t addr_type)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFC_CREATE_CONN;
    msg.param.p.udfc_param.addr_t.addr_type = addr_type;
    memcpy(msg.param.p.udfc_param.addr_t.addr.addr,addr,6);
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfc_connect_cancel(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFC_CONN_CANCEL;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfc_write(uint8_t conidx, uint16_t handle, uint32_t len,uint8_t *data)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFC_WRITE;
    msg.param.p.udfc_param.conidx = conidx;
    msg.param.p.udfc_param.handle = handle;
    msg.param.p.udfc_param.len = len;
    msg.param.p.udfc_param.data = rtos_malloc(len);
    memcpy(msg.param.p.udfc_param.data,data,len);
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfc_write_no_response(uint8_t conidx, uint16_t handle, uint32_t len,uint8_t *data)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFC_WRITE_NO_RESPONSE;
    msg.param.p.udfc_param.conidx = conidx;
    msg.param.p.udfc_param.handle = handle;
    msg.param.p.udfc_param.len = len;
    msg.param.p.udfc_param.data = rtos_malloc(len);
    memcpy(msg.param.p.udfc_param.data,data,len);
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfc_read(uint8_t conidx, uint16_t handle)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFC_READ;
    msg.param.p.udfc_param.conidx = conidx;
    msg.param.p.udfc_param.handle = handle;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfc_notification_cfg(uint8_t conidx, uint16_t handle, bool cfg_en)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFC_NOTIFICATION_CFG;
    msg.param.p.udfc_param.conidx = conidx;
    msg.param.p.udfc_param.handle = handle;
    msg.param.p.udfc_param.cfg_en = cfg_en;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfc_indication_cfg(uint8_t conidx, uint16_t handle, bool cfg_en)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFC_INDICATION_CFG;
    msg.param.p.udfc_param.conidx = conidx;
    msg.param.p.udfc_param.handle = handle;
    msg.param.p.udfc_param.cfg_en = cfg_en;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfc_discover(uint8_t conidx)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFC_DISCOVER;
    msg.param.p.udfc_param.conidx = conidx;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfs_update_read_value(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFS_UPDATE_RD_VAL;
    msg.param.p.udfs_param.conidx = conidx;
    msg.param.p.udfs_param.prf_user_id = prf_user_id;
    msg.param.p.udfs_param.att_idx = att_idx;
    msg.param.p.udfs_param.len = length;
    msg.param.p.udfs_param.data = rtos_malloc(length);
    memcpy(msg.param.p.udfs_param.data,data,length);
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfs_send_notification(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFS_SEND_NOTIFICATION;
    msg.param.p.udfs_param.conidx = conidx;
    msg.param.p.udfs_param.prf_user_id = prf_user_id;
    msg.param.p.udfs_param.att_idx = att_idx;
    msg.param.p.udfs_param.len = length;
    msg.param.p.udfs_param.data = rtos_malloc(length);
    memcpy(msg.param.p.udfs_param.data,data,length);
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfs_send_indication(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFS_SEND_INDICATION;
    msg.param.p.udfs_param.conidx = conidx;
    msg.param.p.udfs_param.prf_user_id = prf_user_id;
    msg.param.p.udfs_param.att_idx = att_idx;
    msg.param.p.udfs_param.len = length;
    msg.param.p.udfs_param.data = rtos_malloc(length);
    memcpy(msg.param.p.udfs_param.data,data,length);
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_udfs_send_db_init(void)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_UDFS_SEND_DBINIT;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_exchange_mtu(uint8_t conidx,uint16_t mtu)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_EXCHANGE_MTU;
    msg.param.p.ex_mtu.conidx = conidx;
    msg.param.p.ex_mtu.mtu = mtu;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_set_print(uint32_t en_flag)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_DBG_PRINT_TOG;
    msg.param.p.value = en_flag;
    app_ble_only_msg_send(&msg);
    return 0;
}

int app_ble_start_bonding(uint8_t conidx)
{
    APP_BLE_ONLY_MSG msg;
    msg.msg_id = BLE_START_BONDING;
    msg.param.p.value = conidx;
    app_ble_only_msg_send(&msg);
    return 0;
}




#endif
