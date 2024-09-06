#include "tgt_cfg_bt.h"
#if PLF_BT_STACK == 1
#include <string.h>
#include "rtos.h"
#include "flash_api_btdm.h"
#if PLF_BLE_ONLY == 1
#include "ble_task_msg.h"
#endif
#include "app_ble_only.h"
#include "co_main.h"
#if PLF_M2D_BLE
#include "app_m2d_ble.h"
#endif
#include "app_ble_queue.h"
#include "sleep_api.h"
#if PLF_BLE_WAKEUP
#include "app_ble_wakeup.h"
#endif
#if defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF)
#include "hostif.h"
#endif

__WEAK uint8_t bt_addr[6] = {
    0xaa,0xc0,0x22,0x45,0x56,0x67
};//0xaa,0xc0,0x00,0x88,0x88,0x33
__WEAK uint8_t ble_addr[6] = {
    0xaa,0xc0,0x22,0x45,0x56,0x67
};

#if (BLE_APP_SMARTCONFIG)
#define APP_DFLT_DEVICE_NAME            ("BLE_SMARTCONFIG")
#elif (BLE_APP_HID)
#define APP_DFLT_DEVICE_NAME            ("AIC_BLE_HID")
#elif (BLE_APP_AUDTRANSMITS || BLE_APP_AUDTRANSMITC)
#define APP_DFLT_DEVICE_NAME            ("AIC_BLE_AUDTRANSMIT")
#else
#define APP_DFLT_DEVICE_NAME            ("AIC_BLE_2")
#endif
#define APP_DFLT_DEVICE_NAME_LEN        (sizeof(APP_DFLT_DEVICE_NAME))


char ble_local_name[32] = APP_DFLT_DEVICE_NAME;
uint8_t ble_dflt_name_len = APP_DFLT_DEVICE_NAME_LEN;

#if (BLE_APP_HID)
static const uint8_t adv_data_uuid[] = {
    03, GAP_AD_TYPE_COMPLETE_LIST_16_BIT_UUID,
    ATT_SVC_HID & 0xFF,
    ATT_SVC_HID >> 8,
};
#endif //(BLE_APP_HID)

static const uint8_t adv_data_appeareance[] = {
    03, GAP_AD_TYPE_APPEARANCE,
#if (BLE_APP_HID)
    GAPC_APPEARANCE_HID_MOUSE & 0xFF,
    GAPC_APPEARANCE_HID_MOUSE >> 8,
#else
    GAPC_APPEARANCE_UNKNOWN & 0xFF,
    GAPC_APPEARANCE_UNKNOWN >> 8,
#endif //(BLE_APP_HID)
};

#ifdef CFG_BLE_START_CLOSE
static uint8_t ble_first_start = 0;
#endif /* CFG_BLE_START_CLOSE */


static struct gapm_adv_create_param adv_param;
static uint8_t adv_data[ADV_DATA_LEN];
/**
 * Default Scan response data
 * --------------------------------------------------------------------------------------
 * x09                             - Length
 * xFF                             - Vendor specific advertising type
 * x00\x60\x41\x49\x43\x42\x4C\x45 - "AICBLE"
 * --------------------------------------------------------------------------------------
 */
static uint8_t scan_res_data[] = {0x09,0xFF,0x00,0x60,0x41,0x49,0x43,0x42,0x4C,0x45};

typedef void (*app_add_svc_func_t)(void);
/// List of service to add in the database
enum app_svc_list
{
    #if (BLE_APP_BATT)
    APP_SVC_BATT,
    #endif //(BLE_APP_BATT)
    #if (BLE_APP_DIS)
    APP_SVC_DIS,
    #endif //(BLE_APP_DIS)
    #if (BLE_APP_HID)
    APP_SVC_HIDS,
    #endif //(BLE_APP_HID)
    #if (BLE_APP_SMARTCONFIG)
    APP_SVC_SMARTCONFIG,
    #endif //(BLE_APP_SMARTCONFIG)
    #if (BLE_APP_AUDTRANSMITS)
    APP_SVC_AUDTRANSMITS,
    #endif //(BLE_APP_AUDTRANSMITS)
    #if (BLE_APP_AUDTRANSMITC)
    APP_SVC_AUDTRANSMITC,
    #endif //(BLE_APP_AUDTRANSMITC)
    #if (BLE_APP_UDFC)
    APP_SVC_UDFC,
    #endif //(BLE_APP_UDFC)
    APP_SVC_LIST_STOP,
};

/// List of functions used to create the database
static const app_add_svc_func_t app_add_svc_func_list[APP_SVC_LIST_STOP] =
{
    #if (BLE_APP_BATT)
    (app_add_svc_func_t)app_batt_add_bas,
    #endif //(BLE_APP_BATT)
    #if (BLE_APP_DIS)
    (app_add_svc_func_t)app_dis_add_dis,
    #endif //(BLE_APP_DIS)
    #if (BLE_APP_HID)
    (app_add_svc_func_t)app_hid_add_hids,
    #endif //(BLE_APP_HID)
    #if (BLE_APP_SMARTCONFIG)
    (app_add_svc_func_t)app_smartconfig_add_smartconfig,
    #endif //(BLE_APP_SMARTCONFIG)
    #if (BLE_APP_AUDTRANSMITS)
    (app_add_svc_func_t)app_audtransmit_add_audtransmits,
    #endif //(BLE_APP_AUDTRANSMITS)
    #if (BLE_APP_AUDTRANSMITC)
    (app_add_svc_func_t)app_audtransmit_add_audtransmitc,
    #endif //(BLE_APP_AUDTRANSMITC)
    #if (BLE_APP_UDFC)
    (app_add_svc_func_t)app_udf_add_udfc,
    #endif //(BLE_APP_AUDTRANSMITC)
};

static void init_adv_params()
{
    memset(&adv_param, 0, sizeof(adv_param));
    adv_param.type = GAPM_ADV_TYPE_LEGACY;
    adv_param.disc_mode = GAPM_ADV_MODE_GEN_DISC;
    adv_param.prop = GAPM_ADV_PROP_UNDIR_CONN_MASK;
    adv_param.filter_pol = ADV_ALLOW_SCAN_ANY_CON_ANY;
    adv_param.prim_cfg.chnl_map = APP_ADV_CHMAP;
    adv_param.prim_cfg.phy = GAP_PHY_LE_1MBPS;
    adv_param.prim_cfg.adv_intv_min = APP_ADV_INT_MIN;
    adv_param.prim_cfg.adv_intv_max = APP_ADV_INT_MAX;
    adv_param.max_tx_pwr = 10;
}

static uint8_t build_adv_data()
{
    uint8_t i = 0;
    uint8_t *buf = &adv_data[0];
    uint8_t len = 0;

    #if (BLE_APP_HID)
    len = sizeof(adv_data_uuid);
    memcpy(&buf[i], adv_data_uuid, len);
    i += len;
    #endif

    len = sizeof(adv_data_appeareance);
    memcpy(&buf[i], adv_data_appeareance, len);
    i += len;

    buf[i] = ble_dflt_name_len + 1;
    buf[i + 1] = GAP_AD_TYPE_COMPLETE_NAME;
    memcpy(buf + i + 2, ble_local_name, ble_dflt_name_len);
    i += ble_dflt_name_len + 2;

    return i;
}


void ble_user_app_init_cb()
{
#if (BLE_APP_SEC)
    // Security Module
    app_sec_init();
#endif // (BLE_APP_SEC)

#if (BLE_APP_HID)
    // HID Module
    app_hid_init();
#endif //(BLE_APP_HID)

#if (BLE_APP_BATT)
    // Battery Module
    app_batt_init();
#endif //(BLE_APP_BATT)

#if (BLE_APP_DIS)
    // Device Information Module
    app_dis_init();
#endif //(BLE_APP_DIS)

#if (BLE_APP_SMARTCONFIG)
    // Smart Config Module
    app_smartconfig_init();
#endif //(BLE_APP_SMARTVOICE)

#if (BLE_APP_AUDTRANSMITS)
    // Aud Transmit Server Module
    app_audtransmits_init();
#endif //(BLE_APP_AUDTRANSMITS)

#if (BLE_APP_AUDTRANSMITC)
    // Aud Transmit client Module
    app_audtransmitc_init();
#endif //(BLE_APP_AUDTRANSMITS)

#if (BLE_APP_UDFC)
    // User Defined client Module
    app_udfc_init();
#endif //(BLE_APP_UDFC)

#if (BLE_APP_UDFS)
    // User Defined server Module
    app_udfs_init();
#endif //(BLE_APP_UDFS)

}

bool ble_user_app_init_complete_cb()
{
    bool ret = false;
    dbg("!!!!!!!!!!!@@@@@@@@@@@@@@@@@\n");

    #if defined(CONFIG_RWNX_LWIP) && defined(CFG_HOSTIF)
    host_if_ble_init_done_indicate();
    #endif

    #ifdef CFG_BLE_START_CLOSE
    if (!ble_first_start) {
        app_ble_deint_start_msg_send();
        ret = true;
        ble_first_start = 1;
        //dbg("ble_first_start: %d\n", ble_first_start);
    }
    #endif /* CFG_BLE_START_CLOSE */

    #if PLF_M2D_BLE
    app_ble_start_delay_init();
    ret = true;
    #endif
    #if PLF_BLE_WAKEUP
    app_ble_delay_scan_start();
    ret = true;
    #endif
    app_user_cb_poll(APP_STATIC_INIT_DONE,NULL);

    return ret;
}

bool ble_user_add_svc_cb()
{
    // Indicate if more services need to be added in the database
    bool more_svc = false;
    TRACE("BLE: %s\n",__func__);
    // Check if another should be added in the database
    if (app_env.next_svc != APP_SVC_LIST_STOP)
    {
        ASSERT_INFO(app_add_svc_func_list[app_env.next_svc] != NULL, app_env.next_svc, 1);

        // Call the function used to add the required service
        app_add_svc_func_list[app_env.next_svc]();

        // Select following service to add
        app_env.next_svc++;
        more_svc = true;
    }

    return more_svc;

}

void ble_user_enable_prf_cb(uint8_t conidx,uint8_t role)
{
    #if (BLE_APP_BATT)
    // Enable Battery Service
    app_batt_enable_prf(conidx);
    #endif //(BLE_APP_BATT)

    #if (BLE_APP_HID)
    // Enable HID Service
    app_hid_enable_prf(conidx);
    #endif //(BLE_APP_HID)

    #if (BLE_APP_SMARTCONFIG)
    app_smartconfig_enable_prf(conidx);
    #endif //(BLE_APP_SMARTCONFIG)

    #if (BLE_APP_AUDTRANSMITS)
    app_audtransmits_enable_prf(conidx);
    #endif //(BLE_APP_AUDTRANSMITS)

    #if (BLE_APP_AUDTRANSMITC)
    app_audtransmitc_enable_prf(conidx);
    #endif //(BLE_APP_AUDTRANSMITC)

    #if (BLE_APP_UDFC)
    if(role == MASTER_ROLE){
        app_udfc_enable_prf(conidx);
    }
    #endif //(BLE_APP_UDFC)

    #if (BLE_APP_UDFS)
    if(role == SLAVE_ROLE){
        app_udfs_enable_prf(conidx);
    }
    #endif //(BLE_APP_UDFS)
}

void ble_app_connection_cb(uint8_t conidx, struct gapc_connection_req_ind const *param)
{
    user_sleep_allow(0);
    dbg("%s connect %d\r\n", __func__, conidx);
}

void ble_app_disconnect_cb(struct gapc_disconnect_ind const *param,uint8_t conidx)
{
    dbg("%s disconnect %d %d\r\n", __func__, param->conhdl, param->reason);
    #if (BLE_APP_HID)
    app_hid_stop_timer();
    // Restart Advertising
    if (app_env.del_bond) {
        app_env.del_bond = false;
        appm_delete_advertising();
    } else {
        app_ble_start_adv();
    }
    user_sleep_allow(1);
    #endif //(BLE_APP_HID)

    #if BLE_APP_SMARTCONFIG
    app_smartconfig_disconnected();
    appm_delete_advertising();
    #endif

    #if BLE_APP_AUDTRANSMITS
    app_ble_aud_stop();
    app_audtransmits_disconnected();
    appm_delete_advertising();
    #endif

    #if BLE_APP_AUDTRANSMITC
    app_ble_aud_stop();
    app_audtransmitc_disconnected();
    app_ble_scan_msg_start();
    #endif

    #if BLE_APP_UDFS
    app_udfs_disconnected(conidx);
    #endif

    #if BLE_APP_UDFC
    app_udfc_disconnected(conidx);
    #endif
}

void ble_app_update_con_params_cb(struct gapc_param_update_req_ind const *param)
{
    dbg("%s con param update %d %d\r\n", __func__, param->intv_max, param->time_out);

}

void ble_app_adv_stop_cb(struct gapm_activity_stopped_ind *param)
{
    dbg("%s con param update reason %d\r\n", __func__, param->reason);
}

void ble_app_adv_status_cb(struct gapm_cmp_evt const *param)
{
    dbg("%s operation %d, status %d\r\n", __func__, param->operation, param->status);
}

static struct app_callbacks ble_app_callbacks = {
   .app_on_init                        = ble_user_app_init_cb,
   .app_on_init_complete               = ble_user_app_init_complete_cb,
   .app_on_add_svc                     = ble_user_add_svc_cb,
   .app_on_enable_prf                  = ble_user_enable_prf_cb,
   .app_on_connection                  = ble_app_connection_cb,
   .app_on_disconnect                  = ble_app_disconnect_cb,
   .app_on_update_params_request       = ble_app_update_con_params_cb,
   .app_on_adv_status                  = ble_app_adv_status_cb,
};

void app_ble_init(void)
{
    uint8_t null_addr[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t invaild_addr[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
    struct bd_addr user_addr;
    #if FPGA == 0
    bt_factory_info_t bt_factory_info;
    if(flash_btdm_bt_factory_read((void *)&bt_factory_info,sizeof(bt_factory_info_t)) == INFO_READ_DONE){
        uint8_t do_copy = 0;
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
            memcpy(&ble_addr[0], &bt_addr[0], BD_ADDR_LEN);
            //memcpy((uint8_t *)ble_local_name , (uint8_t *)bt_factory_info.local_dev_name ,32);
        }
    }
    #endif
    #if (PLF_CONSOLE)
    app_ble_test_command_add();
    #endif // (PLF_CONSOLE)
    app_ble_only_msg_init();

    if (flash_btdm_le_rand_addr_read(&user_addr.addr[0])) {
        dbg("addr error, use default addr\r\n");
    } else {
        if(memcmp(user_addr.addr,null_addr,6)
        && memcmp(user_addr.addr,invaild_addr,6)){
            memcpy(&ble_addr[0], &user_addr.addr[0], BD_ADDR_LEN);
            memcpy(&bt_addr[0], &ble_addr[0], BD_ADDR_LEN);
            //flash_btdm_le_rand_addr_write(ble_addr); // no need to write
        }
    }
    #if PLF_M2D_BLE
    memcpy(&ble_addr[0], &bt_addr[0], BD_ADDR_LEN);
    TRACE("ble addr :%x,%x,%x,%x,%x,%x\n",ble_addr[0],ble_addr[1],ble_addr[2],ble_addr[3],ble_addr[4],ble_addr[5]);
    #endif
    app_ble_env_init();
    app_ble_register_callbak(&ble_app_callbacks);
    app_ble_addr_init(ble_addr, GAPM_STATIC_ADDR);
    app_ble_set_dev_name(ble_local_name, ble_dflt_name_len);
    app_ble_set_adv_data(adv_data, build_adv_data());
    app_ble_set_scan_response_data(scan_res_data,sizeof(scan_res_data));
    init_adv_params();
    if (app_ble_set_adv_params(&adv_param, 0)){
        TRACE("params error\r\n");
    }
    #if (BLE_APP_AUDTRANSMITS == 1 || BLE_APP_AUDTRANSMITC == 1)
    app_ble_audtransmit_init();
    #endif
    #if PLF_M2D_BLE
    app_ble_m2d_init();
    #endif
    #if PLF_BLE_WAKEUP
    app_ble_wakeup_init();
    #endif
    TRACE("app_ble_init\n");
}
#endif
