/**
 ****************************************************************************************
 *
 * @file app_smartconfig.c
 *
 * @brief Smartconfig Application entry point
 *
 * Copyright (C) AIC
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APP
 * @{
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW configuration

#if (BLE_APP_UDFC)

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app.h"
#include "app_task.h"
#include "app_udfc.h"
#include "udfc_task.h"
#include "co_bt.h"
#include "prf_types.h"
#include "prf_utils.h"
#include "arch.h"
#include "prf.h"
#include "string.h"
#include "ble_utils.h"

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
static struct app_udfc_env_tag app_udfc_env;

void app_udfc_event_cb(uint16_t evt, uint8_t *buff)
{
    TRACE("%s, evt 0x%x\n",__func__,evt);
    switch(evt){
        case APP_STATIC_INIT_DONE:
            {
                TRACE("Ble Statck Init Done\n");
            }
            break;
        case APP_SCAN_STARTED:
            {
                TRACE("Ble Scan Started\n");
            }
            break;
        case APP_SCAN_STOPED:
            {
                TRACE("Ble Scan Stoped\n");
            }
            break;
        case APP_INIT_STARTED:
            {
                TRACE("Ble Initiating Start\n");
            }
            break;
        case APP_INIT_CACELED:
            {
                TRACE("Ble Initiating Cancel\n");
            }
            break;
        case UDFC_ENABLE_RSP:
            {
                struct udfc_enable_rsp *param = (struct udfc_enable_rsp *)buff;
            }
            break;
        case UDFC_REG_NTF_PROCESS_DONE:
            {
                struct udfc_data_sent_ind *param = (struct udfc_data_sent_ind *)buff;
            }
            break;
        case UDFC_WR_RSP:
            {
                struct udfc_data_sent_ind *param = (struct udfc_data_sent_ind *)buff;
            }
            break;
        case UDFC_WR_NORES_RSP:
            {
                struct udfc_data_sent_ind *param = (struct udfc_data_sent_ind *)buff;
            }
            break;
        case UDFC_RD_RSP:
            {
                struct gattc_read_ind *param = (struct gattc_read_ind *)buff;
            }
            break;
        case UDFC_NTF_CFG_RSP:
            {
                struct udfc_data_sent_ind *param = (struct udfc_data_sent_ind *)buff;
            }
            break;
        case UDFC_INDICATION_CFG_RSP:
            {
                struct udfc_data_sent_ind *param = (struct udfc_data_sent_ind *)buff;
            }
            break;
        case UDFC_NTF_IND:
            {
                struct udfc_rx_data_ind *param = (struct udfc_rx_data_ind *)buff;
            }
            break;
        case UDFC_INDICATION_IND:
            {
                struct udfc_rx_data_ind *param = (struct udfc_rx_data_ind *)buff;
            }
            break;
        case GATTC_MTU_CHANGED_IND:
            {
                struct ble_mtu_changed_ind *param = (struct ble_mtu_changed_ind *)buff;
            }
            break;
        case GAPC_LE_PKT_SIZE_IND:
            {
                struct ble_le_pkt_size_ind *param = (struct ble_le_pkt_size_ind *)buff;
            }
            break;
        case GAPM_EXT_ADV_REPORT_IND:
            {
                struct gapm_ext_adv_report_ind *param = (struct gapm_ext_adv_report_ind *)buff;
                #if BLE_APP_UDFC
                dbg("%s \n",__func__);
                dbg("actv_idx %x, info %x\n",param->actv_idx,param->info);
                dbg("trans_addr.addr_type %x, addr %x,%x,%x,%x,%x,%x \n",param->trans_addr.addr_type,param->trans_addr.addr.addr[0],param->trans_addr.addr.addr[1]\
                    ,param->trans_addr.addr.addr[2],param->trans_addr.addr.addr[3],param->trans_addr.addr.addr[4],param->trans_addr.addr.addr[5]);
                dbg("target_addr.addr_type %x, addr %x,%x,%x,%x,%x,%x \n",param->target_addr.addr_type,param->target_addr.addr.addr[0],param->target_addr.addr.addr[1]\
                    ,param->target_addr.addr.addr[2],param->target_addr.addr.addr[3],param->target_addr.addr.addr[4],param->target_addr.addr.addr[5]);
                dbg("tx_pwr %x, rssi %d,phy_prim %x, phy_prim %x,phy_second %x,adv_sid %x,period_adv_intv %x\n"\
                    ,param->tx_pwr,param->rssi,param->phy_prim,param->phy_second,param->adv_sid,param->period_adv_intv);
                dbg("length %d,data ",param->length);
                for(uint8_t i=0;i<param->length;i++){
                    dbg("%x, ",param->data[i]);
                }
                dbg("\n ");
                #endif
                uint16_t total_len = param->length;
                uint8_t *data;
                uint8_t ele_len;
                uint8_t ele_type;
                uint8_t *ele_data;
                data = param->data;
                while(total_len){
                    ele_len = data[0];
                    ele_type = data[1];
                    ele_data = &data[2];
                    //dbg("ele_type=0x%x,ele_len=%d\n",ele_type,ele_len);
                    //do user process
                    if(total_len >= (ele_len+1)){
                        total_len -= (ele_len+1);
                        data += (ele_len+1);
                    }else{
                        break;
                    }
                }
            }
            break;
        case GAPC_DISCONNECT_IND:
            {
                struct ble_disconnect_ind *param = (struct ble_disconnect_ind *)buff;
            }
            break;
        case GAPC_CONNECTION_REQ_IND:
            {
                struct ble_connection_ind *param = (struct ble_connection_ind *)buff;
            }
            break;
        case GAPC_PARAM_UPDATE_REQ_IND:
            {
                struct ble_param_update_req_ind *param = (struct ble_param_update_req_ind *)buff;

                param->usr_cfm.accept = true;
                param->usr_cfm.ce_len_min = 2;
                param->usr_cfm.ce_len_max = 4;
            }
            break;
        case GAPC_PARAM_UPDATED_IND:
            {
                struct ble_param_updated_ind *param = (struct ble_param_updated_ind *)buff;
            }
            break;
        default:
            break;
    }
}


bool app_udfc_check_conidx(uint8_t conidx)
{
    bool conidx_find = false;

    for(uint8_t i = 0; i < UDFC_IDX_MAX; i++){
        if(app_udfc_env.conidx[i] == conidx){
            conidx_find = true;
        }
    }
    return conidx_find;
}

void app_udfc_init(void)
{
    TRACE("BLE: %s\n", __func__);
    memset(&app_udfc_env, 0, sizeof(app_udfc_env));
    for(uint8_t i =  0; i < UDFC_IDX_MAX; i++){
        app_udfc_env.conidx[i] = INVALID_CONNECTION_INDEX;
        TRACE("idx %d, conidx %d\n",i,app_udfc_env.conidx[i]);
    }
    app_user_set_msg_cb(APP_USER_CB_1,app_udfc_event_cb);
}

void app_udf_add_udfc(void)
{
    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,
                                                  TASK_GAPM, TASK_APP,
                                                  gapm_profile_task_add_cmd, 0);

    // Fill message
    req->operation = GAPM_PROFILE_TASK_ADD;
    #if 1
    req->sec_lvl = PERM(SVC_AUTH, UNAUTH);
    #else
    req->sec_lvl     = PERM(SVC_AUTH, NO_AUTH)|PERM(SVC_MI, ENABLE);
    #endif
    req->prf_task_id = TASK_ID_UDFC;
    req->app_task = TASK_APP;
    req->start_hdl = 0;
    TRACE("BLE: %s  ,sec_lvl = 0x%x\n", __func__,req->sec_lvl);
    // Send the message
    ke_msg_send(req);
}

void app_udfc_enable_prf(uint8_t conidx)
{
    bool conidx_find = false;
    TRACE("BLE: %s,%x\n", __func__,conidx);

    for(uint8_t i = 0; i < UDFC_IDX_MAX; i++){
        TRACE("idx %d, conidx %d\n",i,app_udfc_env.conidx[i]);
        if(app_udfc_env.conidx[i] == INVALID_CONNECTION_INDEX){
            app_udfc_env.conidx[i] = conidx;
            conidx_find = true;
            break;
        }
    }
    if(!conidx_find){
        TRACE("BLE: conidx is overflow\n");
        return;
    }
    // Allocate the message
    struct udfc_enable_req * req = KE_MSG_ALLOC(UDFC_ENABLE_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_UDFC), conidx),
                                                TASK_APP,
                                                udfc_enable_req);

    req->con_type = PRF_CON_DISCOVERY;
    // Send the message
    ke_msg_send(req);
}

void app_udfc_discover_svc(uint8_t conidx)
{
    TRACE("BLE: %s,%x\n", __func__,conidx);

    if(!app_udfc_check_conidx(conidx)){
        dbg("%s,conidx is error\n",__func__);
        return;
    }

    // Allocate the message
    struct udfc_enable_req * req = KE_MSG_ALLOC(UDFC_DISCOVER_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_UDFC), conidx),
                                                TASK_APP,
                                                udfc_enable_req);

    req->con_type = PRF_CON_DISCOVERY;
    // Send the message
    ke_msg_send(req);
}

void app_udfc_disconnected(uint8_t conidx)
{
    bool conidx_find = false;

    for(uint8_t i = 0; i < UDFC_IDX_MAX; i++){
        if(app_udfc_env.conidx[i] == conidx){
            app_udfc_env.conidx[i] = INVALID_CONNECTION_INDEX;
            TRACE("BLE: %s\n", __func__);
            conidx_find = true;
        }
    }
    if(!conidx_find){
        TRACE("BLE: %s ,conidx is error\n",__func__);
    }
}


void app_udfc_wr_req(uint8_t conidx, uint16_t handle, uint8_t* data, uint32_t length)
{
    dbg("%s %d\r\n", __func__, length);
    if(!app_udfc_check_conidx(conidx)){
        dbg("%s,conidx is error\n",__func__);
        return;
    }
    struct udfc_send_data_req * req = KE_MSG_ALLOC_DYN(UDFC_WR_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_UDFC), conidx),
                                                TASK_APP,
                                                udfc_send_data_req,
                                                length);
    req->handle = handle;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_udfc_wr_nores_req(uint8_t conidx, uint16_t handle, uint8_t* data, uint32_t length)
{
    if(!app_udfc_check_conidx(conidx)){
        dbg("%s,conidx is error\n",__func__);
        return;
    }
    struct udfc_send_data_req * req = KE_MSG_ALLOC_DYN(UDFC_WR_NORES_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_UDFC), conidx),
                                                TASK_APP,
                                                udfc_send_data_req,
                                                length);
    req->handle = handle;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_udfc_rd_req(uint8_t conidx, uint16_t handle)
{
    if(!app_udfc_check_conidx(conidx)){
        dbg("%s,conidx is error\n",__func__);
        return;
    }
    struct udfc_send_data_req * req = KE_MSG_ALLOC(UDFC_RD_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_UDFC), conidx),
                                                TASK_APP,
                                                udfc_send_data_req);
    req->handle = handle;
    ke_msg_send(req);
}

void app_udfc_ntf_cfg_req(uint8_t conidx, uint16_t handle, bool ntf_en)
{
    if(!app_udfc_check_conidx(conidx)){
        dbg("%s,conidx is error\n",__func__);
        return;
    }
    struct udfc_notif_config * req = KE_MSG_ALLOC(UDFC_NTF_CFG_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_UDFC), conidx),
                                                TASK_APP,
                                                udfc_notif_config);
    req->ntf_en = ntf_en;
    req->handle = handle;
    ke_msg_send(req);
}

void app_udfc_ind_cfg_req(uint8_t conidx, uint16_t handle, bool ind_en)
{
    if(!app_udfc_check_conidx(conidx)){
        dbg("%s,conidx is error\n",__func__);
        return;
    }
    struct udfc_indication_config * req = KE_MSG_ALLOC(UDFC_INDICATION_CFG_REQ,
                                                KE_BUILD_ID(prf_get_task_from_id(TASK_ID_UDFC), conidx),
                                                TASK_APP,
                                                udfc_indication_config);
    req->ind_en = ind_en;
    req->handle = handle;
    ke_msg_send(req);
}

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */
void app_udfc_print_val_prop(uint8_t prop)
{
    if(prop & ATT_CHAR_PROP_BCAST){
        TRACE("Value property : Boardcast Permitted\n");
    }
    if(prop & ATT_CHAR_PROP_RD){
        TRACE("Value property : Read Permitted\n");
    }
    if(prop & ATT_CHAR_PROP_WR_NO_RESP){
        TRACE("Value property : Write Without Response Permitted\n");
    }
    if(prop & ATT_CHAR_PROP_WR){
        TRACE("Value property : Write Permitted\n");
    }
    if(prop & ATT_CHAR_PROP_NTF){
        TRACE("Value property : Notify Permitted\n");
    }
    if(prop & ATT_CHAR_PROP_IND){
        TRACE("Value property : Indicate Permitted\n");
    }
    if(prop & ATT_CHAR_PROP_AUTH){
        TRACE("Value property : Authenticated Signed Writes Permitted\n");
    }
    if(prop & ATT_CHAR_PROP_EXT_PROP){
        TRACE("Value property : Extended Properties Permitted\n");
    }

}

static int app_udfc_enable_rsp_handler(ke_msg_id_t const msgid,
                              struct udfc_enable_rsp *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);
    param->conidx = conidx;

    TRACE("%s ,%x, conidx = %x, status = %x\n\n", __func__,param->status,conidx,param->status);
    if(param->status == 0){
        for(uint8_t svc_idx = 0; svc_idx < param->ats->nb_svc; svc_idx++){
            struct prf_disc_sdp_svc_info *scv_info = param->ats->scv_info[svc_idx];
            TRACE("service start_hdl %d, end_hdl %d, uuid_len %d uuid: ",scv_info->start_hdl,scv_info->end_hdl,scv_info->uuid_len);
            for(uint8_t i = 0; i < scv_info->uuid_len; i++){
                TRACE("0x%x ",scv_info->uuid[i]);
            }
            TRACE("\n");
            for(uint8_t i = 0; i < scv_info->num_of_char; i++){
                TRACE("char_hdl %d, val_hdl %d, val_prop 0x%x, val_uuid_len %d, val_uuid:",
                scv_info->info[i].char_hdl,
                scv_info->info[i].val_hdl,
                scv_info->info[i].val_prop,
                scv_info->info[i].val_uuid_len);
                for(uint8_t j = 0; j < scv_info->info[i].val_uuid_len; j++){
                    TRACE("0x%x ",scv_info->info[i].val_uuid[j]);
                }
                TRACE("\n");
                app_udfc_print_val_prop(scv_info->info[i].val_prop);
                if(scv_info->info[i].desc_hdl){
                    TRACE("desc_hdl %d, desc_uuid_len %d, desc_uuid:",
                    scv_info->info[i].desc_hdl,
                    scv_info->info[i].desc_uuid_len);
                    for(uint8_t j = 0; j < scv_info->info[i].desc_uuid_len; j++){
                        TRACE("0x%x ",scv_info->info[i].desc_uuid[j]);
                    }
                    TRACE("\n");
                }
            }
        }
    }

    app_user_cb_poll(UDFC_ENABLE_RSP,(uint8_t *)param);
    for(uint8_t i = 0; i < MAX_DISCOVERD_SCV_NUM; i++){
        if(param->ats->scv_info[i] != NULL){
            ke_free(param->ats->scv_info[i]);
            param->ats->scv_info[i] = NULL;
        }
    }
    return (KE_MSG_CONSUMED);
}

static int app_udfc_wr_rsp_handler(ke_msg_id_t const msgid,
                              struct udfc_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    TRACE("%s ,%x, conidx = %x\n", __func__,param->status,conidx);
    app_user_cb_poll(UDFC_WR_RSP,(uint8_t *)param);
    return (KE_MSG_CONSUMED);
}

static int app_udfc_wr_nores_rsp_handler(ke_msg_id_t const msgid,
                              struct udfc_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    TRACE("%s ,%x, conidx = %x\n", __func__,param->status,conidx);
    app_user_cb_poll(UDFC_WR_NORES_RSP,(uint8_t *)param);
    return (KE_MSG_CONSUMED);
}

static int app_udfc_rd_rsp_handler(ke_msg_id_t const msgid,
                              struct gattc_read_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    TRACE("%s ,0x%x, conidx = %x\n", __func__,param->handle,conidx);
    if(param->handle){
        TRACE("offset = %d\n",param->offset);
        for(uint8_t i = 0; i < param->length; i++){
            TRACE("0x%x\n",param->value[i]);
        }
        TRACE("\n");
    }else{
        TRACE("state error 0x%x\n", param->offset);
    }
    app_user_cb_poll(UDFC_RD_RSP,(uint8_t *)param);
    return (KE_MSG_CONSUMED);
}

static int app_udfc_ntf_cfg_rsp_handler(ke_msg_id_t const msgid,
                              struct udfc_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    TRACE("%s ,%x, conidx = %x\n", __func__,param->status,conidx);
    app_user_cb_poll(UDFC_NTF_CFG_RSP,(uint8_t *)param);
    return (KE_MSG_CONSUMED);
}

static int app_udfc_ind_cfg_rsp_handler(ke_msg_id_t const msgid,
                              struct udfc_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    TRACE("%s ,%x, conidx = %x\n", __func__,param->status,conidx);
    app_user_cb_poll(UDFC_INDICATION_CFG_RSP,(uint8_t *)param);
    return (KE_MSG_CONSUMED);
}

static int app_udfc_reg_ntf_done_handler(ke_msg_id_t const msgid,
                              struct udfc_data_sent_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    TRACE("%s ,%x, conidx = %x\n", __func__,param->status,conidx);
    //app_udfc_ntf_cfg_req(true);
    //app_udfc_ind_cfg_req(true);

    app_user_cb_poll(UDFC_REG_NTF_PROCESS_DONE,(uint8_t *)param);
    return (KE_MSG_CONSUMED);
}

static int app_udfc_ntf_recv_handler(ke_msg_id_t const msgid,
                              struct udfc_rx_data_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    TRACE("%s ,handle %d,len %d, conidx = %x\n", __func__,param->handle,param->length,conidx);
    if(param->length){
        for(uint8_t i = 0; i < param->length; i++){
            TRACE("0x%x ",param->data[i]);
        }
        TRACE("\n");
    }
    app_user_cb_poll(UDFC_NTF_IND,(uint8_t *)param);
    return (KE_MSG_CONSUMED);
}

static int app_udfc_ind_recv_handler(ke_msg_id_t const msgid,
                              struct udfc_rx_data_ind *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);

    TRACE("%s ,handle %d,len %d, conidx = %x\n", __func__,param->handle,param->length,conidx);
    if(param->length){
        for(uint8_t i = 0; i < param->length; i++){
            TRACE("0x%x ", param->data[i]);
        }
        TRACE("\n");
    }
    app_user_cb_poll(UDFC_INDICATION_IND,(uint8_t *)param);
    return (KE_MSG_CONSUMED);
}


static int app_udfc_dflt_msg_handler(ke_msg_id_t const msgid,
                              void const *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    // Do nothing
    return (KE_MSG_CONSUMED);
}

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler app_udfc_msg_handler_list[] =
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,                    (ke_msg_func_t)app_udfc_dflt_msg_handler},
    {UDFC_ENABLE_RSP,                           (ke_msg_func_t)app_udfc_enable_rsp_handler},
    {UDFC_REG_NTF_PROCESS_DONE,                 (ke_msg_func_t)app_udfc_reg_ntf_done_handler},
    {UDFC_WR_RSP,                               (ke_msg_func_t)app_udfc_wr_rsp_handler},
    {UDFC_WR_NORES_RSP,                         (ke_msg_func_t)app_udfc_wr_nores_rsp_handler},
    {UDFC_RD_RSP,                               (ke_msg_func_t)app_udfc_rd_rsp_handler},
    {UDFC_NTF_CFG_RSP,                          (ke_msg_func_t)app_udfc_ntf_cfg_rsp_handler},
    {UDFC_INDICATION_CFG_RSP,                   (ke_msg_func_t)app_udfc_ind_cfg_rsp_handler},
    {UDFC_NTF_IND,                              (ke_msg_func_t)app_udfc_ntf_recv_handler},
    {UDFC_INDICATION_IND,                       (ke_msg_func_t)app_udfc_ind_recv_handler},
};

const struct app_subtask_handlers app_udfc_handlers = APP_HANDLERS(app_udfc);

#endif //BLE_APP_SMARTCONFIG

/// @} APP
