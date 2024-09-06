#include "tgt_cfg_bt.h"
#if PLF_BT_STACK == 1
#if PLF_BLE_ONLY == 0
#include "rtos.h"
#include "app_bt.h"
#include "app_bt_queue.h"
#include "aic_adp_api.h"
#include "bt_task_msg.h"
#include "bt_task.h"
#if APP_SUPPORT_A2DP_SOURCE == 1
#include "app_a2dp_source.h"
#endif
#if APP_SUPPORT_TWS == 1
#include "app_tws.h"
#endif
#include "sleep_api.h"
#if APP_SUPPORT_OTA_BOX
#include "app_ota_box.h"
#endif


typedef enum{
    SLEEP = 0,
    ACTIVE,
}BT_USER_SLEEP_STATE;

#define APP_BT_QUEUE_MAX (30)
#define APP_BT_USER_SLEEP_TIME_DELAY  1000
static rtos_queue app_bt_queue;
static TimerHandle_t app_bt_user_sleep_timer = NULL;
static BT_USER_SLEEP_STATE bt_user_sleep_state = SLEEP;

void app_bt_us_timer( TimerHandle_t xTimer )
{
    bt_user_sleep_state = SLEEP;
    bt_prevent_sleep_clear(BT_PRV_SLP_TIMER);
}

void app_bt_create_us_timer(void)
{
    if(app_bt_user_sleep_timer == NULL)
        app_bt_user_sleep_timer = rtos_timer_create("APP_BT_US",APP_BT_USER_SLEEP_TIME_DELAY,pdFALSE,NULL,app_bt_us_timer);
}

void app_bt_update_us_timer(void)
{
    if(bt_user_sleep_state == SLEEP){
        bt_user_sleep_state = ACTIVE;
        bt_prevent_sleep_set(BT_PRV_SLP_TIMER);
    }
    rtos_timer_change_period(app_bt_user_sleep_timer,APP_BT_USER_SLEEP_TIME_DELAY,0);
}

int app_bt_queue_process(APP_BT_MSG* msg)
{
    Status_BTDef status = BTDEF_UNDEFINED;
    if (msg->msg_id != BT_SET_SNIFF_TIMER && msg->msg_id != BT_TWS_SNED_SYNC_PARAM && msg->msg_id != BT_KEY_MSG
#if APP_SUPPORT_A2DP_SOURCE == 1
    && msg->msg_id != BT_A2DP_SOURCE_SEND_DATA
#endif
    ){
        TRACE("APP:msg id:%d \n",msg->msg_id);
    }
    switch (msg->msg_id) {
        case BT_ROLE_SWITCH:
            status = aic_adp_role_switch(msg->param.p.bdaddr);
            break;
        case BT_DISCONNECT_LINK:
            aic_adp_disconnect_acl(msg->param.p.bdaddr);
            status = BTDEF_NO_ERROR;
            break;
        case BT_DISCONNECT_LINK_ALL:
            app_bt_disconnect_all();
            status = BTDEF_NO_ERROR;
            break;
        case BT_STOP_SNIFF:
            status = aic_adp_stop_sniff(msg->param.p.bdaddr);
            break;
        case BT_SET_SCAN_MODE:
            status = aic_adp_set_scan_mode(msg->param.p.mode);
            break;
        case BT_SET_LINK_POLICY:
            status = aic_adp_set_linkpolicy(msg->param.p.linkpolicy_param.bdaddr,
                                      msg->param.p.linkpolicy_param.policy);
            break;
        case BT_SET_SNIFF_TIMER:
            if (msg->param.p.btsniff_param.sniff_info.maxInterval == 0){
                status = aic_adp_set_sniff_timer(msg->param.p.btsniff_param.bdaddr,
                                            NULL,
                                            msg->param.p.btsniff_param.timeout);
            }else{
                status = aic_adp_set_sniff_timer(msg->param.p.btsniff_param.bdaddr,
                                            &msg->param.p.btsniff_param.sniff_info,
                                            msg->param.p.btsniff_param.timeout);
            }
            break;
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1
        case BT_A2DP_CONNECT:
            status = aic_adp_a2dp_connect(msg->param.p.bdaddr);
            break;
        case BT_A2DP_DISCONNECT:
            status = aic_adp_a2dp_disconnect(msg->param.p.bdaddr);
            break;
#endif
#if APP_SUPPORT_HFP == 1
        case BT_HFP_CONNECT:
            status = aic_adp_hf_connect(msg->param.p.bdaddr);
            break;
        case BT_HFP_DISCONNECT:
            status = aic_adp_hf_disconnect(msg->param.p.bdaddr);
            break;
        case BT_HFP_SCO_CONNECT:
            status = aic_adp_hf_sco_connect(msg->param.p.bdaddr);
            break;
        case BT_HFP_SCO_DISCONNECT:
            status = aic_adp_hf_sco_disconnect(msg->param.p.bdaddr);
            break;
#endif
#if APP_SUPPORT_HSP == 1
        case BT_HSP_CONNECT:
            status = aic_adp_hs_connect(msg->param.p.bdaddr);
            break;
        case BT_HSP_SCO_CONNECT:
            status = aic_adp_hs_sco_connect(msg->param.p.bdaddr);
            break;
        case BT_HSP_SCO_DISCONNECT:
            status = aic_adp_hs_sco_disconnect(msg->param.p.bdaddr);
            break;
        case BT_HSP_DISCONNECT:
            status = aic_adp_hs_disconnect(msg->param.p.bdaddr);
            break;
#endif
#if APP_SUPPORT_A2DP_SOURCE == 1
        case BT_A2DP_SOURCE_CONNECT:
            status = aic_adp_a2dp_source_connect(msg->param.p.bdaddr);
            break;
        case BT_A2DP_SOURCE_START:
            if(msg->param.p.a2dp_param.on_off){
                aic_adp_a2dp_source_start();
            }else{
                aic_adp_a2dp_source_suspend();
            }
            break;
        case BT_A2DP_SOURCE_SEND_DATA:
            app_bt_source_send_a2dp_test_sbc_packet(msg->param.p.bdaddr);
            break;
#endif
#if APP_SUPPORT_HFG
        case BT_HFG_CONNECT:
            aic_adp_hfg_connect(msg->param.p.bdaddr);
            break;
#endif
#if APP_SUPPORT_TWS == 1
        case BT_TWS_CONNECT:
            app_connect_tws_test();
            break;
        case BT_TWS_SEND_DATA:
            app_tws_send_data(msg->param.p.buff.data,msg->param.p.buff.len);
            break;
        case BT_TWS_SYNC_CTRL:
            aic_adp_host_control_tws_sync_con((BOOL)msg->param.p.tws_param.tws_sync_ctrl);
            break;
        case BT_TWS_MSS_CTRL:
            app_tws_begin_mss();
            break;
        case BT_TWS_STOP_LOCAL_SYNC_CTRL:
            aic_adp_host_sync_stop();
            break;
        case BT_TWS_SNED_SYNC_PARAM:
            aic_adp_set_audio_sync_param(msg->param.p.sync_param.current_clk,msg->param.p.sync_param.counterNum ,\
                msg->param.p.sync_param.master_current_samplerate,msg->param.p.sync_param.current_bt_counter,\
                msg->param.p.sync_param.current_bt_counter_offset,msg->param.p.sync_param.strb_cycle_offset);
            break;
        case BT_TWS_RESET:
            aic_adp_update_tws_flash_role(TWS_NOROLE);
            app_bt_disconnect_all();
            break;
        case BT_TWS_DISC:
            app_bt_disconnect_tws();
            break;
        case BT_TWS_VISIBLE_REOPEN:
            aic_adp_tws_clear_whitelist();
            switch(app_tws_get_ble_state()){
                case STATE_SCAN_EN:
                    aic_adp_tws_set_scan_disable();
                    break;
                case STATE_ADV_EN:
                    aic_adp_tws_stop_adv();
                    break;
                default:
                    break;
            }
            app_tws_set_ble_state(STATE_IDLE);
            app_tws_default_connect();
            break;
#endif
        case BT_GENERATE_KEY_COMPLETE:
            aic_adp_send_generate_key();
            break;
        case BT_AUDIO_SEND_RESTART:
            aic_adp_tws_restart();
            break;
        case BT_AUDIO_SEND_MODE_REPLAY:
            {
                uint32_t mode = msg->param.p.audio_mode;
                switch(mode){
                    case AUD_BT_A2DP:
                        //check a2dp status and do start process.
                        break;
                    case AUD_BT_SCO:
                        //check hfp sco link status and do start process.
                        break;
                    default:
                        break;
                }
            }
            break;
        case BT_KEY_MSG:
            app_bt_key_handle(msg->param.p.key);
            break;
        case BT_WEARING_STATE:
            app_bt_wearing_state_hanlde(msg->param.p.wearing_state);
            break;
        case BT_SET_LP_LEVEL:
            {
                uint8_t level = ((uint8_t)(msg->param.p.lp_level));
                TRACE("APP:bt lp level = %x",level);
                aic_adp_set_lp_level(level);
            }
            break;
#if FPGA == 0
        case BT_ERASE_FLASH:
            aic_adp_erased_flash();
            break;
#endif
        case BT_DUT_TEST:
#if TWS_BLE_CONNECT == 1 || BLE_VENDOR_SUPPORT == 1
            aic_adp_tws_set_scan_disable();
#endif
            bt_drv_enable_dut();
            break;
        case BT_NO_SCAN:
        case BT_ISCAN:
        case BT_PSCAN:
        case BT_BOTH_SCAN:
            if(msg->param.p.dut == 0){
                app_bt_set_scan_mode((U8)(msg->msg_id - BT_NO_SCAN));
            }else{
                bt_drv_scan_en(msg->msg_id - BT_NO_SCAN);
            }
            break;
        case BT_NON_SIGNALING_TEST:
            #if PLF_BT_TESTMODE
            bt_drv_enter_non_signaling_test();
            #endif
            break;
        case BT_INQUIRY_DEV:
            aic_adp_inquiry(msg->param.p.inquiry_param.len,msg->param.p.inquiry_param.maxResp);
            break;
        case BT_INQUIRY_CANCEL:
            aic_adp_inquiry_cancel();
            break;
#if APP_SUPPORT_OTA_BOX
        case BT_OTA_CONNECT:
            app_ota_connect_device(&msg->param.p.bdaddr);
            break;
        case BT_OTA_CONNECT_ID:
            app_ota_connect_by_list_id((uint8_t)msg->param.p.btota_param.dev_id);
            break;
        case BT_OTA_SEND_DATA:

            break;
#endif
        case BT_CHANGE_LOCAL_NAME:
            {
                memset((uint8_t *)bt_local_name, 0, 32);
                memcpy((uint8_t *)bt_local_name,(uint8_t *)msg->param.p.local_name,strlen(msg->param.p.local_name) + 1);
                aic_adp_set_bt_name((const unsigned char*)bt_local_name, strlen(bt_local_name) + 1);
                aic_adp_update_bt_eir();
            }
            break;
#if MAX_THROUGHPUT_TEST == 1
        case BT_SPP_SEND_START:
            for (uint8_t i=0;i<LINK_MAX;i++) {
                app_spp_send_test_data(i);
            }
            break;
#endif
        default:
            break;
    }

    if (msg->msg_id != BT_SET_SNIFF_TIMER && msg->msg_id != BT_TWS_SNED_SYNC_PARAM && msg->msg_id != BT_KEY_MSG
#if APP_SUPPORT_A2DP_SOURCE == 1
        && msg->msg_id != BT_A2DP_SOURCE_SEND_DATA
#endif
    ){
        TRACE("APP: msg id:%d :status:%d exit\n", msg->msg_id, status);
    }
    return 0;
}


int app_bt_queue_send(APP_BT_MSG* msg)
{
    if(rtos_queue_write(app_bt_queue,(void *)msg,(TickType_t)1,false)){
        ASSERT_ERR(0);
    }
    app_bt_update_us_timer();
    bt_task_queue_notify(false);
    return 0;
}

int app_bt_queue_send_isr(APP_BT_MSG* msg)
{
    if(rtos_queue_write(app_bt_queue,(void *)msg,(TickType_t)1,true)){
        ASSERT_ERR(0);
    }
    bt_task_queue_notify(true);
    return 0;
}


int app_bt_queue_get(APP_BT_MSG* QueueMsg)
{
    if(rtos_queue_read(app_bt_queue,(void *)QueueMsg,0,0)) {
        return -1;
    }
    return 0;
}

static void app_bt_queue_poll(void)
{
	APP_BT_MSG QueueMsg;
	if (!app_bt_queue_get(&QueueMsg)){
        app_bt_queue_process(&QueueMsg);
	}
}

int app_bt_queue_init(void)
{
    if (rtos_queue_create(sizeof(APP_BT_MSG),APP_BT_QUEUE_MAX,&app_bt_queue)){
        TRACE("APP: Failed to Create app_bt_queue\n");
        return -1;
    }
    app_bt_handler_register(HANDLER_REG_1, app_bt_queue_poll);
    app_bt_create_us_timer();
    return 0;
}
#if MAX_THROUGHPUT_TEST == 1
int app_bt_spp_throughput_start(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_SPP_SEND_START;
    app_bt_queue_send(&msg);
    return 0;
}
#endif

int app_bt_change_local_name(   char * name,uint8_t len)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_CHANGE_LOCAL_NAME;
    memcpy((uint8_t *)msg.param.p.local_name,(uint8_t *)name,len);
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_send_wearing_state(   uint32_t state)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_WEARING_STATE;
    msg.param.p.wearing_state = (uint8_t)state;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_send_key(   uint32_t Key)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_KEY_MSG;
    msg.param.p.key = Key;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_send_audio_sync_param(U32 synclk,U32 counternum,U32 samplerate,U32 bt_counter,U32 bt_counter_offset,U32 strb_cycle_offset)
{
    APP_BT_MSG msg;
    msg.param.p.sync_param.counterNum = counternum;
    msg.param.p.sync_param.current_bt_counter = bt_counter;
    msg.param.p.sync_param.current_bt_counter_offset = bt_counter_offset;
    msg.param.p.sync_param.current_clk = synclk;
    msg.param.p.sync_param.master_current_samplerate = samplerate;
    msg.param.p.sync_param.strb_cycle_offset = strb_cycle_offset;
    msg.msg_id = BT_TWS_SNED_SYNC_PARAM;
    app_bt_queue_send_isr(&msg);
    return 0;

}

int app_bt_send_bt_audio_restart(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_AUDIO_SEND_RESTART;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_send_bt_audio_mode_replay(uint32_t mode)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_AUDIO_SEND_MODE_REPLAY;
    msg.param.p.audio_mode = mode;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_generate_key_complete(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_GENERATE_KEY_COMPLETE;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_set_lp_level(uint8_t level)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_SET_LP_LEVEL;
    msg.param.p.lp_level = level;
    app_bt_queue_send(&msg);
    return 0;
}

#if FPGA == 0
int app_bt_erased_flash(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_ERASE_FLASH;
    app_bt_queue_send(&msg);
    return 0;
}
#endif
int app_bt_dut_mode(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_DUT_TEST;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_wr_scan_en(unsigned int scan_en,unsigned int dut)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_NO_SCAN + scan_en;
    msg.param.p.dut = (uint8_t)dut;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_non_signaling_test_mode(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_NON_SIGNALING_TEST;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_inquiry_dev(unsigned int len,unsigned int maxResp)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_INQUIRY_DEV;
    msg.param.p.inquiry_param.len = (uint8_t)len;
    msg.param.p.inquiry_param.maxResp = (uint8_t)maxResp;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_inquiry_cancel(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_INQUIRY_CANCEL;
    app_bt_queue_send(&msg);
    return 0;
}

#if APP_SUPPORT_A2DP_SOURCE == 1
int app_bt_a2dp_start(BT_ADDR* bdaddr,uint32_t on)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_A2DP_SOURCE_START;
    msg.param.p.a2dp_param.on_off = on;
    memcpy(msg.param.p.a2dp_param.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_a2dp_send_data(BT_ADDR* bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_A2DP_SOURCE_SEND_DATA;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}
#endif

#if APP_SUPPORT_TWS == 1
int app_bt_connect_tws(BT_ADDR* bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_TWS_CONNECT;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_tws_send_data(U8 *data,U16 len)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_TWS_SEND_DATA;
    msg.param.p.buff.data = data;
    msg.param.p.buff.len = len;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_tws_sync_control(BOOL on)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_TWS_SYNC_CTRL;
    if(on)
        msg.param.p.tws_param.tws_sync_ctrl = 1;
    else
        msg.param.p.tws_param.tws_sync_ctrl = 0;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_tws_mss_control(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_TWS_MSS_CTRL;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_tws_stop_local_sync_control(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_TWS_STOP_LOCAL_SYNC_CTRL;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_tws_reset(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_TWS_RESET;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_tws_disc(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_TWS_DISC;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_tws_visible_reopen(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_TWS_VISIBLE_REOPEN;
    app_bt_queue_send(&msg);
    return 0;
}
#endif

int app_bt_role_switch(BT_ADDR* bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_ROLE_SWITCH;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}


int app_bt_disconnect_acl(BT_ADDR* bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_DISCONNECT_LINK;
    TRACE("APP:bt disconnect link\n");
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_disconnect_all_acl(void)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_DISCONNECT_LINK_ALL;
    TRACE("APP:bt disconnect all link\n");
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_stop_sniff(BT_ADDR* bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_STOP_SNIFF;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_setscanmode(AppBtScanMode mode)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_SET_SCAN_MODE;
    msg.param.p.mode = mode;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_set_linkpolicy(BT_ADDR* bdaddr, AppBtLinkPolicy policy)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_SET_LINK_POLICY;
    TRACE("APP:set linkpolicy %x\n",policy);
    memcpy(msg.param.p.linkpolicy_param.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    msg.param.p.linkpolicy_param.policy = policy;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_set_sniff_timer(   BT_ADDR *bdaddr,
                                                AppBtSniffInfo* sniff_info,
                                                TimeT Time)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_SET_SNIFF_TIMER;
    memcpy(msg.param.p.btsniff_param.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    if (sniff_info){
        memcpy((uint8_t*)&msg.param.p.btsniff_param.sniff_info, (uint8_t*)sniff_info, sizeof(AppBtSniffInfo));
    }else{
        memcpy((uint8_t*)&msg.param.p.btsniff_param.sniff_info, 0, sizeof(AppBtSniffInfo));
    }
    msg.param.p.btsniff_param.timeout = Time;
    app_bt_queue_send(&msg);
    return 0;
}


int app_bt_connect_a2dp(BT_ADDR *bdaddr)
{
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1
    APP_BT_MSG msg;
    msg.msg_id = BT_A2DP_CONNECT;
    TRACE("APP:a2dp connect addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",bdaddr->addr[0]
        ,bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
#endif
    return 0;
}

int app_bt_source_connect_a2dp(BT_ADDR *bdaddr)
{
#if APP_SUPPORT_A2DP_SOURCE == 1
    APP_BT_MSG msg;
    msg.msg_id = BT_A2DP_SOURCE_CONNECT;
    TRACE("APP:a2dp connect addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",bdaddr->addr[0]
        ,bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
#endif
    return 0;
}

int app_bt_close_a2dp(BT_ADDR *bdaddr)
{
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1 || APP_SUPPORT_A2DP_SOURCE == 1
    APP_BT_MSG msg;
    msg.msg_id = BT_A2DP_DISCONNECT;
    TRACE("APP:a2dp disconnect addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",bdaddr->addr[0]
    ,bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
#endif
    return 0;
}

int app_bt_connect_hfg(BT_ADDR *bdaddr)
{
#if APP_SUPPORT_HFG == 1
    APP_BT_MSG msg;
    msg.msg_id = BT_HFG_CONNECT;
    TRACE("APP:hfg connect addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",bdaddr->addr[0]
        ,bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
#endif
    return 0;
}

int app_bt_connect_hfp(BT_ADDR *bdaddr)
{
#if APP_SUPPORT_HFP == 1
    APP_BT_MSG msg;
    msg.msg_id = BT_HFP_CONNECT;
    TRACE("APP:hfp connect addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",bdaddr->addr[0]
    ,bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
#endif
    return 0;
}

int app_bt_disconnect_hfp(BT_ADDR *bdaddr)
{
#if APP_SUPPORT_HFP == 1
    APP_BT_MSG msg;
    msg.msg_id = BT_HFP_DISCONNECT;
    TRACE("APP:hfp disconnect addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",bdaddr->addr[0]
    ,bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
#endif
    return 0;
}

int app_bt_hfp_connect_sco(BT_ADDR *bdaddr)
{
#if APP_SUPPORT_HFP == 1
    APP_BT_MSG msg;
    msg.msg_id = BT_HFP_SCO_CONNECT;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
#endif
    return 0;
}

int app_bt_hfp_disconnect_sco(BT_ADDR *bdaddr)
{
#if APP_SUPPORT_HFP == 1
    APP_BT_MSG msg;
    msg.msg_id = BT_HFP_SCO_DISCONNECT;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
#endif
    return 0;
}


#if APP_SUPPORT_HSP == 1
int app_bt_connect_hsp(BT_ADDR *bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_HSP_CONNECT;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_hsp_connect_sco(BT_ADDR *bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_HSP_SCO_CONNECT;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}


int app_bt_hsp_disconnect_sco(BT_ADDR *bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_HSP_SCO_DISCONNECT;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_disconnect_hsp(BT_ADDR *bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_HSP_DISCONNECT;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}

#endif
#if APP_SUPPORT_OTA_BOX
int app_bt_ota_connect(BT_ADDR *bdaddr)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_OTA_CONNECT;
    memcpy(msg.param.p.bdaddr.addr, bdaddr->addr, BD_ADDR_SIZE);
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_ota_connect_by_id(uint32_t id)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_OTA_CONNECT_ID;
    msg.param.p.btota_param.dev_id = id;
    app_bt_queue_send(&msg);
    return 0;
}

int app_bt_ota_send_data(uint32_t num)
{
    APP_BT_MSG msg;
    msg.msg_id = BT_OTA_SEND_DATA;
    msg.param.p.btota_param.num = num;
    app_bt_queue_send(&msg);
    return 0;
}
#endif
#endif
#endif
