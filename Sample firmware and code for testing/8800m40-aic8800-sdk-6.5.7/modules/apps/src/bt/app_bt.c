#include "tgt_cfg_bt.h"
#if PLF_BT_STACK == 1
#if PLF_BLE_ONLY == 0
#include "aic_adp_api.h"
#include "app_bt.h"
#include "app_bt_queue.h"

#include "app_a2dp.h"
#include "app_avrcp.h"
#include "app_hfp.h"
#include "app_hsp.h"
#include "app_spp.h"
#include "app_test.h"
#include <string.h>
#include "app_a2dp_source.h"
#include "app_tws.h"
#if (PLF_AIC8800)
#include "pwrkey_api.h"
#endif
#if PLF_BT_OTA
#include "app_ota_box.h"
#endif
#include "reg_sysctrl.h"
#include "sysctrl_api.h"

app_bt_state_t s_bt_state;
char bt_local_name[32] = "AIC_BT";

#if TEST_MODE_ROLE_SEND == 1
uint8_t bt_addr[6] = {
    0xaa,0xc0,0x00,0x88,0x88,0x33
};
uint8_t ble_addr[6] = {
    0xaa,0xc0,0x00,0x88,0x88,0x33//0xa9,0xc0,0x00,0x45,0x56,0x67
};
#else
uint8_t bt_addr[6] = {
    0xaa,0xc0,0x00,0x88,0x88,0x33
};
uint8_t ble_addr[6] = {
    0xaa,0xc0,0x00,0x88,0x88,0x33//0xaa,0xc0,0x00,0x45,0x56,0x67
};
#endif
app_connect_manager app_bt_connect_struct[LINK_MAX];
app_connect_manager *app_con_ptr[LINK_MAX];
app_bt_key_handler app_bt_key[KEY_MAX_MODULE];
AppBtScanMode bt_scan_mode = 0xff;
TimerHandle_t app_bt_pd_timer = NULL;

void app_bt_powerdown_timer( TimerHandle_t xTimer )
{
    pmic_chip_shutdown();
}

void app_bt_create_powerdown_timer(void)
{
    if(app_bt_pd_timer == NULL)
        app_bt_pd_timer = rtos_timer_create("APP_BT_POWERD",100,pdFALSE,NULL,app_bt_powerdown_timer);
}

void app_bt_start_pd_timer(void)
{
    rtos_timer_start(app_bt_pd_timer,0,false);
}


app_bt_state_t app_get_bt_state(void)
{
    return s_bt_state;
}

void app_set_bt_state(app_bt_state_t state)
{
    TRACE("APP:set bt state = %d\n",state);
    s_bt_state = state;
}

void app_bt_set_scan_mode(AppBtScanMode mode)
{
#if APP_SUPPORT_OTA_BOX
    return;
#endif
    if(bt_scan_mode == mode){
        return;
    }
    bt_scan_mode = mode;
    app_bt_setscanmode(mode);
    TRACE("app_bt_set_scan_mode access_mode=%x\n",mode);
    if(mode == BT_ALLSCAN){
        app_media_play_internalaudio(PROMPT_ID_BT_PAIRING);
    }
}

void app_bt_set_pass_key(char * passkey, uint8_t len)
{
    aic_adp_set_pass_key(passkey,len);
}
/*************************************************************/
/*   @func :  app_bt_open_aic_vender_adv                     */
/*   @brief:  only used for two aic device connection process*/
/*            used by AIC Vendor-Defined BLE ADV and SCAN.   */
/*************************************************************/
void app_bt_open_aic_vender_adv(void)
{
#if BLE_VENDOR_SUPPORT == 1
    BT_ADDR temp_bdaddr;
    APP_BT_MGR *app_bt_manager_ptr = aic_adp_get_app_bt_mgr_ptr();

    if(app_bt_manager_ptr->connect_index == 0){
        memcpy(temp_bdaddr.addr,bt_addr,sizeof(BT_ADDR));
        aic_adp_tws_start_adv(temp_bdaddr);
    }
#endif
}

void app_bt_volume_absolute_mute(void)
{
    MediaCommonStruct tmp;
    memset((U8*)&tmp, 0, sizeof(MediaCommonStruct));
    tmp.p.vol_ctrl.vol_in.mute = 1;
    tmp.p.vol_ctrl.vol_out.mute = 1;
    app_media_mgr_set_command(MC_SETVOLUME,&tmp);
}

uint8_t app_bt_local_volume_convert(uint8_t src_vol,uint8_t src_vol_max, uint8_t dst_max)
{
    const uint8_t src_min =  0;
    const uint8_t dst_min = 0;
    uint8_t dst_vol;

    if(src_vol >= src_vol_max){
        dst_vol = dst_max;
    }else if(src_min == src_vol){
        dst_vol = dst_min;
    }else{
        dst_vol = ((uint32_t) src_vol * (dst_max + 1)) / src_vol_max;
        if(dst_vol >= dst_max){
            dst_vol = dst_max - 1;
        }else if(dst_min == dst_vol){
            dst_vol = dst_min + 1;
        }else{
        }
    }
    return dst_vol;
}

void app_bt_local_volume_handle(uint8_t mode, uint8_t volume)
{
    MediaCommonStruct param;
    uint8_t out_vol;
    uint8_t in_vol;
    memset((U8*)&param, 0, sizeof(MediaCommonStruct));
    out_vol = app_bt_local_volume_convert(volume,(AUD_VOLUME_LEVEL_15 - AUD_VOLUME_LEVEL_0),APP_VOLUME_MAX_OUT_LEVEL);
    param.p.vol_ctrl.vol_out.vol_level = out_vol&0x3f;
    if(out_vol & (1<<6))
        param.p.vol_ctrl.vol_out.extera6dB = 1;
    if(out_vol & (1<<7))
        param.p.vol_ctrl.vol_out.extera12dB = 1;
    TRACE("APP: vol out src %x dst %x.\n",volume,out_vol);
    if(mode){
        in_vol = app_bt_local_volume_convert(volume,(AUD_VOLUME_LEVEL_15 - AUD_VOLUME_LEVEL_0),APP_VOLUME_MAX_IN_LEVEL);
        param.p.vol_ctrl.vol_in.vol_level = in_vol&0x0f;
        TRACE("APP: vol in src %x dst %x.\n",volume,in_vol);
    }
    app_media_mgr_set_command(MC_SETVOLUME,&param);
}

void app_bt_local_volume_change(uint32_t key)
{
    uint8_t mode = 0;
    int8_t volume = (AUD_VOLUME_LEVEL_7 - AUD_VOLUME_LEVEL_0);
    APP_DEVLIST * tmp_devinfo = NULL;
    key = key&0xffff0000;


#if APP_SUPPORT_HFP == 1
    if(app_get_hfp_state() > APP_CONNECTED){
        tmp_devinfo = aic_adp_get_hfp_current_devinfo();
        if(tmp_devinfo == NULL){
            return;
        }
        mode = 1;
        volume = tmp_devinfo->peer_volume_hfp;
    }else
#endif
    {
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC ==1 ||APP_SUPPORT_A2DP_SOURCE == 1
        if(app_get_a2dp_state() >= A2DP_CONNECTED){
            tmp_devinfo = aic_adp_get_a2dp_current_devinfo();
            if(tmp_devinfo == NULL){
                return;
            }
            volume = tmp_devinfo->peer_volume_a2dp;
        }
#endif
    }

    if(key == APP_KEY_VOLADD){
        volume++;
        if(volume > (AUD_VOLUME_LEVEL_15 - AUD_VOLUME_LEVEL_0)){
            volume = (AUD_VOLUME_LEVEL_15 - AUD_VOLUME_LEVEL_0);
        }
    }
    if(key == APP_KEY_VOLSUB){
        volume--;
#if APP_SUPPORT_HFP == 1//call volume at least TGT_VOLUME_LEVEL_1,don't mute it.
        if(app_get_hfp_state() > APP_CONNECTED){
            if(volume < (AUD_VOLUME_LEVEL_0 - AUD_VOLUME_LEVEL_0)){
                volume = (AUD_VOLUME_LEVEL_1 - AUD_VOLUME_LEVEL_0);
            }
        }else
#endif
        if(volume < (AUD_VOLUME_LEVEL_0 - AUD_VOLUME_LEVEL_0)){
            volume = (AUD_VOLUME_LEVEL_0 - AUD_VOLUME_LEVEL_0);
        }
    }
    #if APP_SUPPORT_TWS == 1
    #if APP_SUPPORT_TWS_LOCAL_VOL_SYNC == 1
    app_tws_volume_sync_handle(mode,volume);
    app_bt_local_volume_handle(mode,volume);
    #endif
    #else
    //do change local volume reg process in there.
    app_bt_local_volume_handle(mode,volume);
    //do end
    #endif
#if APP_SUPPORT_HFP == 1
    if(app_get_hfp_state() > APP_CONNECTED){
        app_set_hfp_volume(&tmp_devinfo->bdaddr,volume);
    }else
#endif
    {
#if (APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC ==1 ||APP_SUPPORT_A2DP_SOURCE == 1) && APP_SUPPORT_AVRCP == 1
        if(app_get_a2dp_state() >= A2DP_CONNECTED){
            app_set_avrcp_volume(&tmp_devinfo->bdaddr,(8*(volume+1) - 1));
        }
#endif
    }
}

static void app_bt_state_machine(AIC_EVENT *Event)
{
    switch(Event->EventId){
        case AIC_ADP_STACK_INIT:
            if(app_get_bt_state() == BT_ACTIVE_PENDING)
            {
                app_set_bt_state(BT_ACTIVED);
            }
            app_media_play_internalaudio(PROMPT_ID_POWER_ON);
            break;
        case AIC_ADP_ACL_CONNECT_IND:
        case AIC_ADP_ACL_CONNECT_CNF:
            {
                AIC_ADP_MGR_EVENT *aic_mgr_msg = (AIC_ADP_MGR_EVENT *)Event->Param;
                if(aic_mgr_msg->p.reason == BT_NO_ERROR){
                    app_set_bt_state(BT_CONNECTED);
                }else{

                }
            }
            break;
        case AIC_ADP_ACL_DISCONNECT:
            {
                if(app_get_bt_state() > BT_ACTIVE_PENDING){
                    app_set_bt_state(BT_ACTIVED);
                }
            }
            break;
        case AIC_ADP_PAIRING_COMPLETE:
            {
                AIC_ADP_MGR_EVENT *aic_mgr_msg = (AIC_ADP_MGR_EVENT *)Event->Param;
                if(aic_mgr_msg->p.reason == BT_NO_ERROR){
#if APP_SUPPORT_TWS == 1
                    if(tws_app_get_role() != TWS_SLAVE){
                        app_media_play_internalaudio(PROMPT_ID_BT_PAIRING_SUCCESS);
                    }
#else
                    app_media_play_internalaudio(PROMPT_ID_BT_PAIRING_SUCCESS);
#endif
                }else{
#if APP_SUPPORT_TWS == 1
                    if(tws_app_get_role() != TWS_SLAVE){
                        app_media_play_internalaudio(PROMPT_ID_BT_PAIRING_FAIL);
                    }
#else
                    app_media_play_internalaudio(PROMPT_ID_BT_PAIRING_FAIL);
#endif
                }
            }
            break;
        default:
            break;
    }
}

static void app_bt_common_handle(AIC_EVENT *Event)
{
    app_bt_state_machine(Event);
    switch(Event->EventId){
        case AIC_ADP_STACK_INIT:
            if(Event->Param == 0){
                TRACE("APP: bt_stack_init success.\n");
#if 0
                *(volatile uint32_t *)(0x40500028) = 4;
#if 1
                *(volatile uint32_t *)(0x406200f0) = 0x00002222;
                *(volatile uint32_t *)(0x40600450) = 0x92b0e5e4;
#else
                *(volatile uint32_t *)(0x406200f0) = 0x00002222;
                *(volatile uint32_t *)(0x40600450) = 0xdf929b9c;
                *(volatile uint32_t *)(0x40620100) = 0x07060403;
                *(volatile uint32_t *)(0x40620104) = 0x0f0d0c08;
                *(volatile uint32_t *)(0x40620108) = 0x13121110;
                *(volatile uint32_t *)(0x4062010c) = 0x1f1e1d19;

                *(volatile uint32_t *)(0x40620814) = 0x100;
                *(volatile uint32_t *)(0x40620810) = 0x640004;
                *(volatile uint32_t *)(0x40620814) = 0x107;
#endif
                *(volatile uint32_t *)(0x40620508) = 0x54a53013;
                TRACE("BTDRV:write done 0x%x, 0x%x, 0x%x\n",*(volatile uint32_t *)(0x40500028),*(volatile uint32_t *)(0x406200f0),*(volatile uint32_t *)(0x40600450));
#endif
                #if PLF_LS_MODULE
                ls_send_start_check(LS_CHECK_PERIOD,0);
                #endif

#if SCO_CVSD_PLC_TEST == 1 || (APP_SUPPORT_TWS == 1 && PXP == 1)
                #if TEST_MODE_ROLE_SEND == 1
                app_bt_set_scan_mode(BT_NOSCAN);
                #else
                app_bt_set_scan_mode(BT_CONNECTABLE);
                #endif
#else
                app_bt_set_scan_mode(BT_ALLSCAN);
#endif

#if MAX_THROUGHPUT_TEST == 1 && TEST_MODE_ROLE_SEND == 1
                app_spp_connect_test();
#else
        #if APP_SUPPORT_HFG == 1
                #if BLE_VENDOR_SUPPORT == 1
                aic_adp_tws_set_scan_para(1);
                #endif
        #else
                #if APP_SUPPORT_TWS == 0
                app_bt_connect();
                #else
                app_tws_default_connect();
                #endif
        #endif
#endif
            }
        break;
        case AIC_ADP_ACCESSIBLE_CHANGE:
        {
#if SCO_CVSD_PLC_TEST == 1 && TEST_MODE_ROLE_SEND == 1
            static uint8_t flag = 0;
            if(flag == 0 && Event->Param == 0)
            {
                flag = 1;
                app_test_connect_default();
            }
#endif
            TRACE("APP:accessible mode = %d\n",Event->Param);
        }
        break;
        case AIC_ADP_ENCRYPYION_CHANGE:
#if SCO_CVSD_PLC_TEST == 1 && TEST_MODE_ROLE_SEND == 1
        if (connect_sco_timer == NULL)
            connect_sco_timer = rtos_timer_create("Aic_TEST_Timer",      \
                                                         1000,      \
                                                         pdFALSE,\
                                                         NULL,\
                                                         app_test_connect_sco);
        rtos_timer_change_period(connect_sco_timer,10,0);

#endif
        break;
        default:
            break;
    }
}

static void app_bt_manager_handle(AIC_EVENT *Event)
{
    AIC_ADP_MGR_EVENT *aic_mgr_msg = (AIC_ADP_MGR_EVENT *)Event->Param;
    APP_BT_MGR *app_bt_manager_ptr = aic_adp_get_app_bt_mgr_ptr();
    app_bt_state_machine(Event);
    TRACE("APP:app_bt_mgr_handle evt = %d\n",Event->EventId);

    switch (Event->EventId) {
        case AIC_ADP_ACL_CONNECT_IND:
        case AIC_ADP_ACL_CONNECT_CNF:
#if APP_SUPPORT_MULTIPLE_PHONE == 1
            if(app_bt_manager_ptr->connect_index == 0){
                app_bt_set_scan_mode(BT_ALLSCAN);
            }else if(app_bt_manager_ptr->connect_index == 1){
                #if APP_SUPPORT_LINK_ONE_ONLY == 1
                app_bt_set_scan_mode(BT_NOSCAN);
                #else
                app_bt_set_scan_mode(BT_CONNECTABLE);
                #endif
            }else if(app_bt_manager_ptr->connect_index >= 2){
                app_bt_set_scan_mode(BT_NOSCAN);
            }
            #if BLE_VENDOR_SUPPORT == 1
            aic_adp_tws_stop_adv();
            #endif
#else
#if APP_SUPPORT_TWS == 1
            if(app_bt_manager_ptr->connect_index == 0){
                app_bt_set_scan_mode(BT_ALLSCAN);
            }else if(app_bt_manager_ptr->connect_index == 1){
                if(aic_adp_check_cmp_twsaddr(aic_mgr_msg->bdaddr)){
                    if(aic_tws_get_porttype() == TWS_SERVER_PORT){
                        app_bt_set_scan_mode(BT_NOSCAN);
                    }else{
                        #if PXP == 1
                        app_bt_set_scan_mode(BT_NOSCAN);
                        #else
                        app_bt_set_scan_mode(BT_ALLSCAN);
                        #endif
                    }
                }else{
                    #if TWS_BLE_CONNECT == 1
                    app_bt_set_scan_mode(BT_CONNECTABLE);
                    #endif
                }
            }else if(app_bt_manager_ptr->connect_index >= 2){
                app_bt_set_scan_mode(BT_NOSCAN);
            }
#else
            if(app_bt_manager_ptr->connect_index == 0){
                app_bt_set_scan_mode(BT_ALLSCAN);
            }
#if APP_SUPPORT_A2DP_SOURCE == 0
            else if(app_bt_manager_ptr->connect_index >= 1){
                app_bt_set_scan_mode(BT_NOSCAN);
            }
#else
            else if(app_bt_manager_ptr->connect_index == 1){
                app_bt_set_scan_mode(BT_ALLSCAN);
            }else if(app_bt_manager_ptr->connect_index >= 2){
                app_bt_set_scan_mode(BT_NOSCAN);
            }
#endif
#endif
#endif
            break;
        case AIC_ADP_ACL_DISCONNECT:
            TRACE("APP:acl_disconnect reason = %d\n",aic_mgr_msg->p.reason);
#if APP_SUPPORT_MULTIPLE_PHONE == 1
            if(app_bt_manager_ptr->connect_index == 0){
                app_bt_set_scan_mode(BT_ALLSCAN);
                #if APP_SUPPORT_HFG == 1
                    #if BLE_VENDOR_SUPPORT == 1
                    aic_adp_tws_set_scan_para(1);
                    #endif
                #endif
            }else if(app_bt_manager_ptr->connect_index == 1){
                #if APP_SUPPORT_LINK_ONE_ONLY == 1
                app_bt_set_scan_mode(BT_NOSCAN);
                #else
                app_bt_set_scan_mode(BT_CONNECTABLE);
                #endif
            }
#else
#if APP_SUPPORT_TWS == 1
            if(app_bt_manager_ptr->connect_index == 0){
                app_bt_set_scan_mode(BT_ALLSCAN);
            }else if(app_bt_manager_ptr->connect_index == 1){
                if(aic_adp_check_cmp_twsaddr(aic_mgr_msg->bdaddr)){
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC ==1 ||APP_SUPPORT_A2DP_SOURCE == 1
                    if(app_get_a2dp_state() != A2DP_PLAY && app_get_hfp_state() != APP_PLAY_SCO)
#endif
                        app_bt_set_scan_mode(BT_ALLSCAN);
                }else{
                    if(aic_mgr_msg->p.reason == BT_CONNECTION_TIMEOUT)
                        app_bt_set_scan_mode(BT_CONNECTABLE);
                    else
                        app_bt_set_scan_mode(BT_ALLSCAN);
                }
            }
#endif
#endif
            break;
        case AIC_ADP_PASS_KEY_REQ:
            {
                uint8_t delay_num = 15;
                TRACE("APP: wait user input passkey by console CMD : bt_passkey xxxxxx : xxxxxx is the passkey print in phone\n");
                while(delay_num--){
                    TRACE("APP: %d\n",delay_num);
                    rtos_task_suspend(1000);
                }
            }
            break;
        case AIC_ADP_PIN_CODE_REQ:
            {
                aic_adp_set_pin_code("0000",4);
            }
            break;
        case AIC_ADP_PAIRING_COMPLETE:
            if(aic_mgr_msg->p.reason == BT_NO_ERROR){

            }else{

            }
            break;
        case AIC_ADP_SCO_CONNECT_IND:
        case AIC_ADP_SCO_CONNECT_CNF:
                if(aic_mgr_msg->p.reason == BT_NO_ERROR){
#if APP_SUPPORT_TWS == 1
                    if(tws_app_get_role() == TWS_MASTER){
                        app_bt_set_scan_mode(BT_NOSCAN);
                    }else{
                        if (app_bt_manager_ptr->connect_index == 1){
                            app_bt_set_scan_mode(BT_CONNECTABLE);
                        }else if(app_bt_manager_ptr->connect_index >= 2){
                            app_bt_set_scan_mode(BT_NOSCAN);
                        }
                    }
#else
                    app_bt_set_scan_mode(BT_NOSCAN);
#endif
                }
            break;
        case AIC_ADP_SCO_DISCONNECTED:
            if(app_bt_manager_ptr->connect_index == 1){
                app_bt_set_scan_mode(BT_CONNECTABLE);
            }
            break;
        case AIC_ADP_INQUIRY_RESULT:
            {
                bt_class_of_device cod = (bt_class_of_device)aic_mgr_msg->p.inqResultP.cod;
                TRACE("APP: cod = 0x%x ,addr %x %x %x %x %x %x\n",cod ,aic_mgr_msg->bdaddr.addr[0],aic_mgr_msg->bdaddr.addr[1],
                        aic_mgr_msg->bdaddr.addr[2],aic_mgr_msg->bdaddr.addr[3],aic_mgr_msg->bdaddr.addr[4],aic_mgr_msg->bdaddr.addr[5]);
                if(aic_mgr_msg->p.inqResultP.inqMode == 1){
                    TRACE("APP: rssi = %d\n",aic_mgr_msg->p.inqResultP.rssi);
                }
                if(aic_mgr_msg->p.inqResultP.inqMode == 2){
                    char name[240];
                    uint8_t len = 0;
                    uint8_t type = 0;
                    uint8_t *eir = aic_mgr_msg->p.inqResultP.extInqResp;
                    TRACE("APP: rssi = %d\n",aic_mgr_msg->p.inqResultP.rssi);
                    for(uint8_t idx = 0; idx < 240; idx++){
                        len = eir[idx];
                        type = eir[idx+1];
                        if(type==0x09){
                            memcpy((uint8_t *)name,&eir[idx+2],len-1);
                            name[len-1] = '\0';
                            TRACE("APP: complete_name = %s\n",name);
                        }
                        idx += len;
                    }
                }
            }
            break;
        case AIC_ADP_INQUIRY_COMPLETE:

            break;
            /** The Inquiry process is canceled. */
        case AIC_ADP_INQUIRY_CANCELED:

            break;
        case AIC_ADP_BLE_ADV_DATA:
            {
#if BLE_VENDOR_SUPPORT == 1 && APP_SUPPORT_HFG == 1
                host_data_struct *rx_data = (host_data_struct *)Event->Param;
                BT_ADDR remove_addr;

                memcpy(remove_addr.addr, &rx_data->data[26], 6);
                TRACE("APP:remove addr %x,%x,%x,%x,%x,%x\n",remove_addr.addr[0],remove_addr.addr[1],remove_addr.addr[2],\
                                                            remove_addr.addr[3],remove_addr.addr[4],remove_addr.addr[5]);
                if(remove_addr.addr[5] == bt_addr[5]
                && remove_addr.addr[4] == bt_addr[4]
                && remove_addr.addr[3] == bt_addr[3]){
                    aic_adp_tws_set_scan_disable();
                    app_bt_connect_hfg(&remove_addr);
                }
#endif
            }
            break;
        default:
            break;
    }

}

void app_bt_wearing_state_hanlde(uint32_t state)
{
    TRACE("APP: %s,%x\n",__func__,state);
    #if APP_SUPPORT_TWS == 1
    app_tws_wearing_state_handle(state);
    #endif
}

BOOL app_bt_key_handle(uint32_t key)
{
    BOOL ret = FALSE;

    TRACE("APP: key enter 0x%x\n",key);
    switch(key)
    {
        case APP_KEY_VOLADD|APP_KEY_PRESS:
        case APP_KEY_VOLADD|APP_KEY_HOLD:
        case APP_KEY_VOLSUB|APP_KEY_PRESS:
        case APP_KEY_VOLSUB|APP_KEY_HOLD:
            // do local volume change function.
            app_bt_local_volume_change(key);
            break;
        case APP_KEY_VOLADD|APP_KEY_UP:
        case APP_KEY_VOLSUB|APP_KEY_UP:
            // do function after local volume key up
            break;
        case APP_KEY_HOLD_5S:
#if APP_SUPPORT_TWS == 1
            if (tws_app_get_role() >= TWS_NOROLE)
#endif
            {
                app_bt_disconnect_all();
                aic_adp_close_dev();
            }
            break;
        case APP_KEY_POWER|APP_KEY_HOLD_2S:
#if PLF_AIC_VENDOR_ADV
            app_bt_open_aic_vender_adv();
#endif
            break;
        default:
            switch(KEY_NAME_GET(key)){
                case APP_MSG_BATT:
                    {
                        uint32_t batt_level = KEY_FUNC_GET(key);
                        #if APP_SUPPORT_HFP == 1
                            aic_adp_hfp_set_battery_level((uint8_t)batt_level);
                        #endif
                    }
                    break;
                case APP_MSG_POWER_DOWN:
                    app_bt_start_pd_timer();
                case APP_MSG_LOW_POWER:
                    //do some for led or play internal audio.
                    break;
                case APP_KEY_POWER:
                    {
                        #if (PLF_KEY_MODULE) && (PLF_GSENSOR == 0)
                        uint32_t change_key;
                        change_key = APP_KEY_PLAY|KEY_FUNC_GET(key);
                        app_bt_send_key(change_key);
                        #endif
                    }
                    break;
                default:
                    break;
            }
            break;
    }
    for(U8 i = 0;i < KEY_MAX_MODULE ; i++){
        if(app_bt_key[i].callback){
            ret = app_bt_key[i].callback(key);
            if(ret == TRUE)
                break;
        }
    }
    return ret;
}

void app_bt_key_register(aic_bt_key_module module,app_bt_key_handle_cb callback)
{
    TRACE("APP:app_bt_key_register module = %d\n",module);
    for(U8 i = 0;i < KEY_MAX_MODULE ; i++){
        if(app_bt_key[i].callback == NULL){
            app_bt_key[i].callback = callback;
            app_bt_key[i].module = module;
            break;
        }
    }
}

void app_bt_key_register_init(void)
{
#if APP_SUPPORT_TWS == 1
    app_bt_key_register(KEY_TWS   ,app_tws_key_handle);
#endif
#if APP_SUPPORT_HFP == 1
    app_bt_key_register(KEY_HFP   ,app_hfp_key_handle);
#endif
#if APP_SUPPORT_HSP == 1
    app_bt_key_register(KEY_HSP   ,app_hsp_key_handle);
#endif
#if APP_SUPPORT_AVRCP == 1
    app_bt_key_register(KEY_AVRCP ,app_avrcp_key_handle);
#endif
#if APP_SUPPORT_HID == 1
    app_bt_key_register(KEY_HID   ,app_hid_key_handle);
#endif
}

void app_register_app_msg_handle(void)
{
    aic_adp_register_app_msg_handle(AIC_COMMON ,app_bt_common_handle);
    aic_adp_register_app_msg_handle(AIC_MGR    ,app_bt_manager_handle);
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1 || APP_SUPPORT_A2DP_SOURCE == 1
    aic_adp_register_app_msg_handle(AIC_A2DP   ,app_a2dp_msg_handle);
#endif
#if APP_SUPPORT_AVRCP == 1
    aic_adp_register_app_msg_handle(AIC_AVRCP  ,app_avrcp_msg_handle);
#endif
#if APP_SUPPORT_HFP == 1
    aic_adp_register_app_msg_handle(AIC_HFP    ,app_hfp_msg_handle);
#endif
#if APP_SUPPORT_HSP == 1
    aic_adp_register_app_msg_handle(AIC_HSP    ,app_hsp_msg_handle);
#endif
#if APP_SUPPORT_HID == 1
    aic_adp_register_app_msg_handle(AIC_HID    ,app_hid_msg_handle);
#endif
#if APP_SUPPORT_SPP == 1
    aic_adp_register_app_msg_handle(AIC_SPP    ,app_spp_msg_handle);
#endif
#if SCO_CVSD_PLC_TEST == 1
    aic_adp_register_app_msg_handle(AIC_TEST   ,app_test_msg_handle);
#endif
#if APP_SUPPORT_TWS == 1
    aic_adp_register_app_msg_handle(AIC_TWS    ,app_tws_msg_handle);
#endif
#if PLF_BT_OTA == 1
    aic_adp_register_app_msg_handle(AIC_TEST    ,app_ota_msg_handle);
#endif
}

void app_bt_profile_register(void)
{
#if APP_SUPPORT_A2DP_SOURCE == 1
    aic_adp_a2dp_register_source();
#endif
#if APP_SUPPORT_A2DP_CP == 1
    aic_adp_a2dp_support_cb();
#endif
#if APP_SUPPORT_A2DP_SBC == 1
    aic_adp_a2dp_register_sink_sbc();
#endif
#if APP_SUPPORT_A2DP_AAC == 1
    aic_adp_a2dp_register_sink_aac();
#endif
#if APP_SUPPORT_AVRCP == 1
    aic_adp_avrcp_register();
#endif
#if APP_SUPPORT_HFP == 1
    aic_adp_hfp_register();
#endif
#if APP_SUPPORT_HSP == 1
    aic_adp_hsp_register();
#endif
#if APP_SUPPORT_HID == 1
    aic_adp_hid_register();
#endif
}


void app_adp_init(void)
{
#if APP_SUPPORT_A2DP_SOURCE == 1
    aic_adp_a2dp_source_init();
    app_a2dp_source_init();
#endif
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1
    aic_adp_a2dp_init();
#endif
#if APP_SUPPORT_AVRCP == 1
    aic_adp_avrcp_init();
#endif
#if APP_SUPPORT_HFP == 1
    #if APP_SUPPORT_HFG == 1
    aic_adp_hfp_init(HANDSFREE_AG);
    #else
    aic_adp_hfp_init(HANDSFREE);
    #endif
#endif
#if APP_SUPPORT_HSP == 1
    aic_adp_hsp_init();
#endif
#if APP_SUPPORT_SPP == 1
    app_spp_init();
    aic_adp_spp_init();
#endif
#if APP_SUPPORT_TWS == 1
    aic_adp_tws_init();
    app_tws_init();
#endif

#if SCO_CVSD_PLC_TEST == 1 || PLF_BT_OTA == 1
    aic_adp_test_init();
#if APP_SUPPORT_OTA_BOX
    app_ota_init();
#endif
#endif
    aic_adp_mgr_init();


}

void app_bt_init(void)
{
#if FPGA == 0
    bt_factory_info_t bt_factory_info;
    if(flash_btdm_bt_factory_read((void *)&bt_factory_info, sizeof(bt_factory_info_t)) == INFO_READ_DONE){
        uint8_t do_copy = 0;
        uint8_t null_addr[6] = {0x00,0x00,0x00,0x00,0x00,0x00}; 
        uint8_t invaild_addr[6] = {0xff,0xff,0xff,0xff,0xff,0xff}; 
        if(memcmp(bt_factory_info.local_bt_addr,null_addr,6)
        && memcmp(bt_factory_info.local_bt_addr,invaild_addr,6)){
            memcpy(bt_addr , bt_factory_info.local_bt_addr ,6);
            do_copy = 1;
        }
        if(memcmp(bt_factory_info.local_ble_addr,null_addr,6)
        && memcmp(bt_factory_info.local_ble_addr,invaild_addr,6)){
            memcpy(ble_addr , bt_factory_info.local_ble_addr ,6);
            do_copy = 1;
        }
        if(do_copy){
            memcpy((uint8_t *)bt_local_name , (uint8_t *)bt_factory_info.local_dev_name ,32);
        }
        if(bt_factory_info.bt_flash_erased == 0x01){
            app_bt_erased_flash();
            bt_factory_info.bt_flash_erased = 0;
            flash_btdm_bt_factory_write((void *)&bt_factory_info,sizeof(bt_factory_info_t));
        }
    }
#endif
    TRACE("app_bt_init\n");
#if PLF_CONSOLE
    app_console_command_add();
#endif
    app_set_bt_state(BT_ACTIVE_PENDING);
    app_adp_init();
    app_bt_profile_register();
    app_register_app_msg_handle();
    app_bt_queue_init();
    app_bt_key_register_init();
    app_bt_connect_init();
    app_bt_create_powerdown_timer();
#if CO_MAIN_AUTO_POWER_DOWN == 1
    co_main_batt_register_cb(app_bt_send_key);
#endif
        /* bt local name */
    aic_adp_set_bt_name((const unsigned char*)bt_local_name, strlen(bt_local_name) + 1);
    aic_adp_set_cod(BTM_COD_MAJOR_AUDIO|BTM_COD_MINOR_CONFM_HEADSET|BTM_COD_SERVICE_AUDIO|BTM_COD_SERVICE_RENDERING);
    aic_adp_set_io_capabilities(NO_INPUT_NO_OUTPUT);

    TRACE("app_bt_init  success\n");
}





void app_bt_connect_init(void)
{
    uint8_t i=0;

    for (i=0;i<LINK_MAX;i++){
        app_con_ptr[i] = &app_bt_connect_struct[i];
        app_con_ptr[i]->profile.all_connected = FALSE;
        app_con_ptr[i]->profile.hfp_connect = CONNECT_IDLE;
        app_con_ptr[i]->profile.hsp_connect = CONNECT_IDLE;
        app_con_ptr[i]->profile.a2dp_connect = CONNECT_IDLE;

        app_con_ptr[i]->reconnect.connect_retry_cnt = 0;
        app_con_ptr[i]->reconnect.connect_timer_handle = NULL;
        app_con_ptr[i]->reconnect.reconnect_mode = RECONNECT_IDLE;
        app_con_ptr[i]->reconnect.connect_timer_cb = NULL;

        memset(app_con_ptr[i]->remotedev_addr.addr,0 ,BD_ADDR_SIZE);
#if PLF_AON_SUPPORT == 1
        app_con_ptr[i]->reconnect.cb_param = (void *)app_con_ptr[i];
#else
        if (app_con_ptr[i]->reconnect.connect_timer_handle == NULL)
            app_con_ptr[i]->reconnect.connect_timer_handle = rtos_timer_create("Aic_BT_Connect_Timer",      \
                                                     10000,      \
                                                     pdFALSE,\
                                                     (void *)app_con_ptr[i],\
                                                     app_bt_connect_timer);
#endif
    }
    TRACE("APP:app_bt_connect_init success\n");
}

app_connect_manager *app_bt_get_con_ptr_by_addr(BT_ADDR * bdaddr)
{
    for(uint8_t i=0;i<LINK_MAX;i++){
        if(!memcmp(app_con_ptr[i]->remotedev_addr.addr, bdaddr->addr, BD_ADDR_SIZE)){
            return app_con_ptr[i];
        }
    }
    return NULL;
}

app_connect_manager *app_bt_get_unused_con_ptr(void)
{
    for(uint8_t i=0;i<LINK_MAX;i++){
        if(app_con_ptr[i]->profile.a2dp_connect != CONNECTED
           && app_con_ptr[i]->profile.hfp_connect != CONNECTED){
            return app_con_ptr[i];
        }
    }
    return NULL;
}

#if APP_SUPPORT_MULTIPLE_PHONE == 1
void app_bt_connect_multiple_phone(void)
{
    if(app_con_ptr[LINK_2]->reconnect.reconnect_mode == RECONNECT_POWERON){
#if PLF_AON_SUPPORT
        app_bt_start_reconnect(&app_con_ptr[LINK_2]->reconnect.connect_timer_handle,app_con_ptr[LINK_2]->reconnect.cb_param,100);
#else
        app_bt_start_reconnect(app_con_ptr[LINK_2]->reconnect.connect_timer_handle,100);
#endif
    }
}
#endif

void app_bt_report_connect_internal_audio(app_connect_manager * app_bt_con)
{
    if(!app_bt_con->profile.all_connected){
        if(TRUE
#if APP_SUPPORT_A2DP_SBC == 1|| APP_SUPPORT_A2DP_AAC == 1
            && app_bt_con->profile.a2dp_connect == CONNECTED
#endif
#if APP_SUPPORT_HFP == 1
            && app_bt_con->profile.hfp_connect == CONNECTED
#endif
#if APP_SUPPORT_HSP == 1
            && app_bt_con->profile.hsp_connect == CONNECTED
#endif
        ){
            app_bt_con->profile.all_connected = TRUE;
            app_bt_con->reconnect.reconnect_mode = RECONNECT_IDLE;
            //report media connect successful
#if APP_SUPPORT_TWS == 1
            if(tws_app_get_role() != TWS_SLAVE){
                app_media_play_internalaudio(PROMPT_ID_BT_CONNECTED);
            }
#else
            app_media_play_internalaudio(PROMPT_ID_BT_CONNECTED);
#endif
            aic_adp_save_flash();
#if APP_SUPPORT_MULTIPLE_PHONE == 1 && APP_SUPPORT_LINK_ONE_ONLY == 0
            app_bt_connect_multiple_phone();
#endif
        }

    }else{
        if(TRUE
#if APP_SUPPORT_A2DP_SBC == 1|| APP_SUPPORT_A2DP_AAC == 1
            && app_bt_con->profile.a2dp_connect != CONNECTED
#endif
#if APP_SUPPORT_HFP == 1
            && app_bt_con->profile.hfp_connect != CONNECTED
#endif
#if APP_SUPPORT_HSP == 1
            && app_bt_con->profile.hsp_connect != CONNECTED
#endif
        ){
            app_bt_con->profile.all_connected = FALSE;
            //report media disconnect successful
#if APP_SUPPORT_TWS == 1
            if(tws_app_get_role() != TWS_SLAVE){
                app_media_play_internalaudio(PROMPT_ID_BT_DISCONNECT);
            }
#else
            app_media_play_internalaudio(PROMPT_ID_BT_DISCONNECT);
#endif
        }
    }
}

void app_bt_connect(void)
{
#if APP_SUPPORT_TWS == 0
    APP_BT_MGR *app_bt_manager_ptr = aic_adp_get_app_bt_mgr_ptr();
    BT_ADDR *bdaddr = &app_bt_manager_ptr->device_list[LINK_1].bdaddr;
    if(!app_bt_check_invalid_bdaddr(bdaddr)){
        btdev_info* dev_info = aic_adp_get_devinfo_by_addr(bdaddr);
        if(dev_info){
                app_con_ptr[LINK_1]->reconnect.reconnect_mode = RECONNECT_POWERON;
                memcpy(app_con_ptr[LINK_1]->remotedev_addr.addr, bdaddr->addr, BD_ADDR_SIZE);
                TRACE("APP:hf_state = %x,a2dp_state = %x\n",dev_info->hf_state,dev_info->a2dp_state);
                if(0){
                    //do nothing
                }
#if APP_SUPPORT_A2DP_SOURCE == 1
                else if(dev_info->a2dp_role == BT_A2DP_SOURCE){
                    //do nothing
                }
#endif
#if APP_SUPPORT_HFP == 1
                else if(dev_info->hf_state){
                    app_bt_connect_hfp(bdaddr);
                }
#endif
#if APP_SUPPORT_A2DP_SBC == 1|| APP_SUPPORT_A2DP_AAC == 1
                else if(dev_info->a2dp_state){
                    app_bt_connect_a2dp(bdaddr);
                }
#endif
                else{
                    app_con_ptr[LINK_1]->reconnect.reconnect_mode = RECONNECT_IDLE;
                    memset(app_con_ptr[LINK_1]->remotedev_addr.addr,0 ,BD_ADDR_SIZE);
                }
        }
    }
#if APP_SUPPORT_MULTIPLE_PHONE == 1
    bdaddr = &app_bt_manager_ptr->device_list[LINK_2].bdaddr;
    if(!app_bt_check_invalid_bdaddr(bdaddr)){
        btdev_info* dev_info = aic_adp_get_devinfo_by_addr(bdaddr);
        if(dev_info){
                app_con_ptr[LINK_2]->reconnect.reconnect_mode = RECONNECT_POWERON;
                memcpy(app_con_ptr[LINK_2]->remotedev_addr.addr, bdaddr->addr, BD_ADDR_SIZE);
                if(0){
                    //do nothing
                }
#if APP_SUPPORT_HFP == 1
                else if(dev_info->hf_state){

                }
#endif
#if APP_SUPPORT_A2DP_SBC == 1|| APP_SUPPORT_A2DP_AAC == 1
                else if(dev_info->a2dp_state){

                }
#endif
                else{
                    app_con_ptr[LINK_2]->reconnect.reconnect_mode = RECONNECT_IDLE;
                    memset(app_con_ptr[LINK_2]->remotedev_addr.addr,0 ,BD_ADDR_SIZE);
                }
        }
    }
#endif
#else
    APP_BT_MGR *app_bt_manager_ptr = aic_adp_get_app_bt_mgr_ptr();

    for(uint8_t i = 0; i < LINK_MAX; i++){
        BT_ADDR *bdaddr = &app_bt_manager_ptr->device_list[i].bdaddr;
        if(!app_bt_check_invalid_bdaddr(bdaddr)){
            if(!aic_adp_check_cmp_twsaddr(*bdaddr) && app_bt_manager_ptr->device_list[i].adp_state == APP_MGR_STATE_IDLE ){
                btdev_info* dev_info = aic_adp_get_devinfo_by_addr(bdaddr);
                if(dev_info){
                        app_con_ptr[LINK_1]->reconnect.reconnect_mode = RECONNECT_POWERON;
                        memcpy(app_con_ptr[LINK_1]->remotedev_addr.addr, bdaddr->addr, BD_ADDR_SIZE);
                        TRACE("APP:hf_state = %x,a2dp_state = %x\n",dev_info->hf_state,dev_info->a2dp_state);
                        if(0){
                            //do nothing
                        }
#if APP_SUPPORT_A2DP_SOURCE == 1
                        else if(dev_info->a2dp_role == BT_A2DP_SOURCE){
                            //do nothing
                        }
#endif
#if APP_SUPPORT_HFP == 1
                        else if(dev_info->hf_state){
                            app_bt_connect_hfp(bdaddr);
                        }
#endif
#if APP_SUPPORT_A2DP_SBC == 1|| APP_SUPPORT_A2DP_AAC == 1
                        else if(dev_info->a2dp_state){
                            app_bt_connect_a2dp(bdaddr);
                        }
#endif
                        else{
                            app_con_ptr[LINK_1]->reconnect.reconnect_mode = RECONNECT_IDLE;
                            memset(app_con_ptr[LINK_1]->remotedev_addr.addr,0 ,BD_ADDR_SIZE);
                        }
                }
            }
        }
    }
#endif
}




#if PLF_AON_SUPPORT
void app_bt_start_reconnect(co_timer **timer, void *cb_param, uint32_t t)
{
    co_timer_start(timer, t, cb_param, app_bt_connect_timer,0);
}

void app_bt_connect_timer(void *cb_param)
{
    app_connect_manager * app_con_ptr_tmp = NULL;
    app_con_ptr_tmp = (app_connect_manager *)cb_param;

    if(app_con_ptr_tmp->reconnect.connect_timer_cb){
            app_con_ptr_tmp->reconnect.connect_timer_cb(cb_param);
            app_con_ptr_tmp->reconnect.connect_timer_cb = NULL;
    }else{
        if(0){
            //do nothing
        }
#if APP_SUPPORT_HFP == 1
        else if(app_con_ptr_tmp->profile.hfp_connect != CONNECTED){
            app_bt_connect_hfp(&app_con_ptr_tmp->remotedev_addr);
        }
#endif
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1
        else if(app_con_ptr_tmp->profile.a2dp_connect != CONNECTED){
            app_bt_connect_a2dp(&app_con_ptr_tmp->remotedev_addr);
        }
#endif
    }
}
#else
void app_bt_start_reconnect( TimerHandle_t xTimer ,uint32_t t)
{
    rtos_timer_change_period(xTimer,t ,0);
}

void app_bt_connect_timer( TimerHandle_t xTimer )
{
    app_connect_manager * app_con_ptr_tmp = NULL;
    app_con_ptr_tmp = (app_connect_manager *)rtos_timer_get_pvTimerID(xTimer);

    if(app_con_ptr_tmp->reconnect.connect_timer_cb){
            app_con_ptr_tmp->reconnect.connect_timer_cb(xTimer);
            app_con_ptr_tmp->reconnect.connect_timer_cb = NULL;
    }else{
        if(0){
            //do nothing
        }
#if APP_SUPPORT_HFP == 1
        else if(app_con_ptr_tmp->profile.hfp_connect != CONNECTED){
            app_bt_connect_hfp(&app_con_ptr_tmp->remotedev_addr);
        }
#endif
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1
        else if(app_con_ptr_tmp->profile.a2dp_connect != CONNECTED){
            app_bt_connect_a2dp(&app_con_ptr_tmp->remotedev_addr);
        }
#endif
    }
}
#endif

void app_bt_disconnect_all(void)
{
    APP_BT_MGR *app_bt_manager_ptr = aic_adp_get_app_bt_mgr_ptr();

#if APP_SUPPORT_TWS == 1
    switch(tws_app_get_role()){
        case TWS_SLAVE:
        case TWS_MASTER:
            aic_adp_disconnect_tws();
        default:
            if(app_bt_manager_ptr){
                for(U8 i = 0; i < app_bt_manager_ptr->max_device_num ; i++){
                    if(app_bt_manager_ptr->device_list[i].adp_state == APP_MGR_STATE_CONNECTED){
                        aic_adp_disconnect_acl(app_bt_manager_ptr->device_list[i].bdaddr);
                    }
                }
            }
            break;
    }
#else
    if(app_bt_manager_ptr){
        for(U8 i = 0; i < app_bt_manager_ptr->max_device_num ; i++){
#if APP_SUPPORT_TWS == 1
            if(tws_app_get_role() == TWS_SLAVE){
                if(app_bt_manager_ptr->device_list[i].adp_state == APP_MGR_STATE_CONNECTED && aic_adp_check_cmp_twsaddr(app_bt_manager_ptr->device_list[i].bdaddr)){
                    aic_adp_disconnect_acl(app_bt_manager_ptr->device_list[i].bdaddr);
                }
            }else
#endif
            {
                if(app_bt_manager_ptr->device_list[i].adp_state == APP_MGR_STATE_CONNECTED){
                    aic_adp_disconnect_acl(app_bt_manager_ptr->device_list[i].bdaddr);
                }
            }
        }
    }
#endif
}
#endif
#endif
