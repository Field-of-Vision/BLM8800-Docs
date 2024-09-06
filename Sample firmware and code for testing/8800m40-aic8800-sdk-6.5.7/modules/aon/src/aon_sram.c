#include "plf.h"
#if PLF_AON_SUPPORT == 1

#include "aon_sram.h"

void pm_app_static_save(void *aon_app_static)
{
    AppStatic app_static;
    AonAppStatic *save_app_static = (AonAppStatic *)aon_app_static;
#if PLF_BLE_ONLY == 0
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1 || APP_SUPPORT_A2DP_SOURCE == 1
    app_static.btstatic.t_a2dp_state =t_a2dp_state;
#endif
#if APP_SUPPORT_HFP == 1
    app_static.btstatic.s_hfp_state =s_hfp_state;
    app_static.btstatic.s_hfp_scocodec = s_hfp_scocodec;
#endif
    for(uint8_t i = 0; i<HANDLER_REG_MAX;i++){
        app_static.btstatic.handler_register_list[i] = handler_register_list[i];
    }
    for(uint8_t i = 0; i<LINK_MAX;i++){
        app_static.btstatic.app_bt_connect_struct[i] = app_bt_connect_struct[i];
        //app_static.btstatic.app_bt_connect_struct[i].reconnect.reconnect_mode = RECONNECT_IDLE;
        app_static.btstatic.app_con_ptr[i] = app_con_ptr[i];
    }
    app_static.btstatic.s_bt_state =s_bt_state;
    app_static.btstatic.bt_scan_mode = bt_scan_mode;
    app_static.btstatic.aic_host_log = aic_host_log;
#if APP_SUPPORT_AES == 1
    for(uint8_t i = 0; i < 8;i++){
        app_static.btstatic.secret_key[i] = secret_key[i];
    }
#endif
#endif
#if PLF_BLE_STACK == 1
    app_static.blestatic.aon_ble_enabled = ble_enabled;
    app_static.blestatic.aon_ble_app_env = app_env;
    app_static.blestatic.aon_ble_app_user_info = ble_user_info;
    AppBlePrfEnv *app_ble_prf_env = &app_static.ble_prf_env;
    memcpy((uint8_t *)&app_ble_prf_env->prf_env, (uint8_t *)&prf_env, sizeof(struct prf_env_tag));
    uint8_t i =0;
#if BLE_APP_HID
    if (prf_env.prf[i].env != NULL) {
        struct bass_env_tag *bass_env = PRF_ENV_GET(BASS, bass);
        memcpy((uint8_t *)&app_ble_prf_env->bass_env, (uint8_t *)bass_env, sizeof(app_ble_prf_env->bass_env));
        i++;
    }
    if (prf_env.prf[i].env != NULL) {
        struct hogpd_env_tag *hogpd_env = PRF_ENV_GET(HOGPD, hogpd);
        //dbg("hogpd_env->state %x\n",hogpd_env->state[0]);
        //dbg("0x%x,%x, %x, %x,0x%x",prf_env.prf[i].desc.state,prf_env.prf[i].desc.state[0],prf_env.prf[i].desc.idx_max,prf_env.prf[i].desc.msg_cnt,prf_env.prf[i].desc.msg_handler_tab);
        memcpy((uint8_t *)&app_ble_prf_env->hogpd_env, (uint8_t *)hogpd_env, sizeof(app_ble_prf_env->hogpd_env));
        i++;
    }
#endif //(BLE_APP_HID)
#if BLE_APP_SMARTCONFIG
    if (prf_env.prf[i].env != NULL) {
        struct smartconfig_env_tag *smartconfig_env = PRF_ENV_GET(SMARTCONFIG, smartconfig);
        memcpy((uint8_t *)&app_ble_prf_env->smartconfig_env, (uint8_t *)smartconfig_env, sizeof(app_ble_prf_env->smartconfig_env));

        i++;
    }
#endif // (BLE_APP_SMARTCONFIG)
#endif //(PLF_BLE_STACK == 1)
    app_static.bt_lp_level = bt_lp_level;
    app_static.bt_power_state = bt_power_state;
    save_app_static->len = sizeof(app_static);
    memset(save_app_static->app_static, 0, save_app_static->len);
    memcpy(save_app_static->app_static, (uint8_t *)&app_static, save_app_static->len);

    //TRACE("AON:app static save len = %d ,addr 0x%x\n",save_app_static->len,save_app_static);
}

void pm_app_static_restore(void *aon_app_static)
{
    AppStatic app_static;
    AonAppStatic *restore_app_static = (AonAppStatic *)aon_app_static;

    if(restore_app_static->len == sizeof(app_static)){
        memcpy((uint8_t *)&app_static, restore_app_static->app_static, restore_app_static->len);
    }else{
        TRACE("AON:app static restore error!\n");
        return;
    }
#if PLF_BLE_ONLY == 0
#if APP_SUPPORT_A2DP_SBC == 1 || APP_SUPPORT_A2DP_AAC == 1 || APP_SUPPORT_A2DP_SOURCE == 1
    t_a2dp_state = app_static.btstatic.t_a2dp_state;
#endif
#if APP_SUPPORT_HFP == 1
    s_hfp_state = app_static.btstatic.s_hfp_state;
    s_hfp_scocodec = app_static.btstatic.s_hfp_scocodec;
#endif
    for(uint8_t i = 0; i<HANDLER_REG_MAX;i++){
        handler_register_list[i] = app_static.btstatic.handler_register_list[i];
    }
    for(uint8_t i = 0; i<LINK_MAX;i++){
        app_bt_connect_struct[i] = app_static.btstatic.app_bt_connect_struct[i];
        app_con_ptr[i] = app_static.btstatic.app_con_ptr[i];
    }
    s_bt_state = app_static.btstatic.s_bt_state;
    bt_scan_mode = app_static.btstatic.bt_scan_mode;
    aic_host_log = app_static.btstatic.aic_host_log;
#if APP_SUPPORT_AES == 1
    for(uint8_t i = 0; i < 8;i++){
        secret_key[i] = app_static.btstatic.secret_key[i];
    }
#endif
#endif
#if PLF_BLE_STACK == 1
    ble_enabled = app_static.blestatic.aon_ble_enabled;
    app_env = app_static.blestatic.aon_ble_app_env;
    ble_user_info = app_static.blestatic.aon_ble_app_user_info;
    AppBlePrfEnv *app_ble_prf_env = NULL;
    app_ble_prf_env = &app_static.ble_prf_env;

    memcpy((uint8_t *)&prf_env, (uint8_t *)&app_ble_prf_env->prf_env, sizeof(struct prf_env_tag));
    uint8_t i =0;
#if BLE_APP_HID
    if (prf_env.prf[i].env != NULL) {
        struct bass_env_tag* bass_env = NULL;
        bass_env = (struct bass_env_tag* ) ke_malloc(sizeof(struct bass_env_tag), KE_MEM_ATT_DB);
        memcpy((uint8_t *)bass_env, (uint8_t *)&app_ble_prf_env->bass_env, sizeof(app_ble_prf_env->bass_env));
        prf_env.prf[i].env = (prf_env_t*) bass_env;
        prf_env.prf[i].desc.state = bass_env->state;
        i++;
    }
    if (prf_env.prf[i].env != NULL) {
        struct hogpd_env_tag *hogpd_env = NULL;
        hogpd_env = (struct hogpd_env_tag* ) ke_malloc(sizeof(struct hogpd_env_tag), KE_MEM_ATT_DB);
        memcpy((uint8_t *)hogpd_env, (uint8_t *)&app_ble_prf_env->hogpd_env, sizeof(app_ble_prf_env->hogpd_env));
        prf_env.prf[i].env = (prf_env_t*) hogpd_env;
        prf_env.prf[i].desc.state = hogpd_env->state;
        //dbg("hogpd_env->state %x\n",hogpd_env->state[0]);
        //dbg("0x%x,%x, %x, %x,0x%x",prf_env.prf[i].desc.state,prf_env.prf[i].desc.state[0],prf_env.prf[i].desc.idx_max,prf_env.prf[i].desc.msg_cnt,prf_env.prf[i].desc.msg_handler_tab);
        i++;
    }
#endif // (BLE_APP_HID)
#if BLE_APP_SMARTCONFIG
    if (prf_env.prf[i].env != NULL) {
        struct smartconfig_env_tag* smartconfig_env =
                (struct smartconfig_env_tag* ) ke_malloc(sizeof(struct smartconfig_env_tag), KE_MEM_ATT_DB);
        memcpy((uint8_t*)smartconfig_env, (uint8_t*)&app_ble_prf_env->smartconfig_env, sizeof(app_ble_prf_env->smartconfig_env));
        prf_env.prf[i].env = (prf_env_t*) smartconfig_env;
        prf_env.prf[i].desc.state = &smartconfig_env->state;
        i++;
    }
#endif // (BLE_APP_SMARTCONFIG)
#endif  //(PLF_BLE_STACK == 1)
    bt_lp_level = app_static.bt_lp_level;
    bt_power_state = app_static.bt_power_state;
    //TRACE("AON:app static restore\n");
}

#endif
