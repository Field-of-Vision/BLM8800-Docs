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

#if (BLE_APP_UDFS)

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app.h"
#include "app_task.h"
#include "app_udfs.h"
#include "udfs_task.h"
#include "co_bt.h"
#include "prf_types.h"
#include "prf_utils.h"
#include "arch.h"
#include "prf.h"
#include "string.h"
#include "ble_utils.h"

/*
 * UDF CMD PROFILE ATTRIBUTES
 ****************************************************************************************
 */
#define udfs_service_uuid_128_content                {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x01,0xfe,0x00,0x00}
#define udfs_wr_uuid_128_content                     {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x02,0xfe,0x00,0x00}
#define udfs_rd_uuid_128_content                     {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x03,0xfe,0x00,0x00}
#define udfs_ntf_uuid_128_content                    {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x04,0xfe,0x00,0x00}
#define udfs_ind_uuid_128_content                    {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x05,0xfe,0x00,0x00}

static const uint8_t UDFS_SERVICE_UUID_128[ATT_UUID_128_LEN]    = udfs_service_uuid_128_content;

#define ATT_DECL_PRIMARY_SERVICE_UUID           {0x00, 0x28}
#define ATT_DECL_CHARACTERISTIC_UUID            {0x03, 0x28}
#define ATT_DESC_CLIENT_CHAR_CFG_UUID           {0x02, 0x29}

/// Full UDFS_SERVICE Database Description - Used to add attributes into the database
static struct attm_desc_128 udfs_att_db[11] =
{
    // Service Declaration
    [0]                  =   {ATT_DECL_PRIMARY_SERVICE_UUID, PERM(RD, ENABLE), 0, 0},

    //  Write/Write noresponce Characteristic Declaration
    [1]        =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    //  Write/Write noresponce Characteristic Value
    [2]         =   {udfs_wr_uuid_128_content,
        PERM(WRITE_REQ, ENABLE)| PERM(WRITE_COMMAND, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), UDFS_MAX_LEN},

    // Data Read Characteristic Declaration
    [3]       =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Data Read Characteristic Value
    [4]        =   {udfs_rd_uuid_128_content,
        PERM(RD, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), UDFS_MAX_LEN},

    // Notification Characteristic Declaration
    [5]        =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Notification Characteristic Value
    [6]         =   {udfs_ntf_uuid_128_content, PERM(NTF, ENABLE) | PERM(RD, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), UDFS_MAX_LEN},
    // Notification Characteristic - Client Characteristic Configuration Descriptor
    [7]     =   {ATT_DESC_CLIENT_CHAR_CFG_UUID, PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE), 0, 0},


    // Indication Characteristic Declaration
    [8]       =   {ATT_DECL_CHARACTERISTIC_UUID, PERM(RD, ENABLE), 0, 0},
    // Indication Characteristic Value
    [9]        =   {udfs_ind_uuid_128_content, PERM(IND, ENABLE) | PERM(RD, ENABLE),
        PERM(RI, ENABLE) | PERM_VAL(UUID_LEN, PERM_UUID_128), UDFS_MAX_LEN},
    // Indication Characteristic - Client Characteristic Configuration Descriptor
    [10]    =   {ATT_DESC_CLIENT_CHAR_CFG_UUID, PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE), 0, 0},
};

struct udfs_db_cfg app_udfs_db_cfg[APP_UDFS_MAX_SERVICE];

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

void app_udfs_event_cb(uint16_t evt, uint8_t *buff)
{
    TRACE("%s, evt 0x%x\n",__func__,evt);
    switch(evt){
        case APP_ADV_STARTED:
            {
                TRACE("Ble Adv Started\n");
            }
            break;
        case APP_ADV_STOPED:
            {
                TRACE("Ble Adv Stoped\n");
            }
            break;
        case APP_ADV_DATA_UPDATED:
            {
                TRACE("Ble Adv Data Updated\n");
            }
            break;
        case APP_ADV_SCAN_RES_UPDATED:
            {
                TRACE("Ble Adv Scan Responce Updated\n");
            }
            break;
        case UDFS_WR_RECEIVED:
            {
                struct udfs_rx_data_ind *cfg = (struct udfs_rx_data_ind *)buff;
                TRACE("%s UDFS_WR_RECEIVED,conidx %d, prf_user_id %d, att_idx %d, length %d\n", __func__,\
                    cfg->conidx,cfg->prf_user_id,cfg->att_idx,cfg->length);
                for(uint8_t i=0;i<cfg->length;i++){
                    TRACE("0x%x ",cfg->data[i]);
                }
                TRACE("\n");
            }
            break;
        case UDFS_RD_VALUE_UPDATE:
            {
                struct udfs_read_data_req *cfg = (struct udfs_read_data_req *)buff;
                TRACE("%s UDFS_RD_VALUE_UPDATE,conidx %d, prf_user_id %d, att_idx %d, length %d\n", __func__,\
                    cfg->conidx,cfg->prf_user_id,cfg->att_idx,cfg->length);
                /// do user read data update
                
                //memcpy(cfg->value, user_data , len);
                cfg->length = 0;//len
                /// do end
                if(cfg->length){
                    for(uint8_t i=0;i<cfg->length;i++){
                        TRACE("0x%x ",cfg->value[i]);
                    }
                    TRACE("\n");
                }
            }
            break;
        case UDFS_NTF_IND_SERVICE_CHANGED:
            {
                struct udfs_ntf_ind_config *cfg = (struct udfs_ntf_ind_config *)buff;
                TRACE("%s UDFS_NTF_IND_SERVICE_CHANGED,conidx %d, prf_user_id %d, att_idx %d, ntf_ind_en %d\n", __func__,\
                    cfg->conidx,cfg->prf_user_id,cfg->att_idx,cfg->ntf_ind_en);

            }
            break;
        case UDFS_NTF_SENT:
            {
                struct udfs_data_sent_ind *cfg = (struct udfs_data_sent_ind *)buff;
                TRACE("%s UDFS_NTF_SENT,conidx %d, prf_user_id %d, att_idx %d, status 0x%x\n", __func__,\
                    cfg->conidx,cfg->prf_user_id,cfg->att_idx,cfg->status);
            }
            break;
        case UDFS_IND_SENT:
            {
                struct udfs_data_sent_ind *cfg = (struct udfs_data_sent_ind *)buff;
                TRACE("%s UDFS_IND_SENT,conidx %d, prf_user_id %d, att_idx %d, status 0x%x\n", __func__,\
                    cfg->conidx,cfg->prf_user_id,cfg->att_idx,cfg->status);
            }
            break;
        default:
            break;
    }
}

void app_udfs_init(void)
{
    TRACE("BLE: %s\n", __func__);
    for(uint8_t i=0;i<APP_UDFS_MAX_SERVICE;i++){
        memset(&app_udfs_db_cfg[i],0,sizeof(struct udfs_db_cfg));
    }
    app_user_set_msg_cb(APP_USER_CB_0,app_udfs_event_cb);
}

void app_udfs_db_cfg_init(void)
{
    app_udfs_db_cfg[0].prf_user_id = 0;
    memcpy(app_udfs_db_cfg[0].uuid,UDFS_SERVICE_UUID_128,ATT_UUID_128_LEN);
    app_udfs_db_cfg[0].start_hdl=0;
    app_udfs_db_cfg[0].svc_perm = PERM(SVC_AUTH, NO_AUTH)|PERM(SVC_MI, ENABLE);//PERM(SVC_AUTH, UNAUTH);
    app_udfs_db_cfg[0].att_num = 11;
    app_udfs_db_cfg[0].att_db = &udfs_att_db[0];
    app_udf_add_udfs(&app_udfs_db_cfg[0]);

    app_udfs_db_cfg[1].prf_user_id = 1;
    memcpy(app_udfs_db_cfg[1].uuid,UDFS_SERVICE_UUID_128,ATT_UUID_128_LEN);
    app_udfs_db_cfg[1].start_hdl=0;
    app_udfs_db_cfg[1].svc_perm = PERM(SVC_AUTH, NO_AUTH)|PERM(SVC_MI, ENABLE);//PERM(SVC_AUTH, UNAUTH);
    app_udfs_db_cfg[1].att_num = 11;
    app_udfs_db_cfg[1].att_db = &udfs_att_db[0];
    app_udf_add_udfs(&app_udfs_db_cfg[1]);

}

void app_udfs_db_cfg_deinit(void)
{

}

int app_udf_add_udfs(struct udfs_db_cfg * database_cfg)
{
    int ret = 0;
    TRACE("BLE: %s\n", __func__);
    if(ke_state_get(TASK_APP) < APPM_CREATE_DB || !database_cfg){
        ret = -1;
        return ret;
    }
    
    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,
                                                  TASK_GAPM, TASK_APP,
                                                  gapm_profile_task_add_cmd, sizeof(struct udfs_db_cfg));

    // Fill message
    req->operation = GAPM_PROFILE_TASK_ADD;
    #if 0
    //req->sec_lvl = PERM(SVC_AUTH, ENABLE);
    req->sec_lvl     = PERM(SVC_AUTH, NO_AUTH);
    #else
    req->sec_lvl = database_cfg->svc_perm;
    #endif
    req->prf_task_id = TASK_ID_UDFS+database_cfg->prf_user_id;
    req->app_task = TASK_APP;
    req->start_hdl = database_cfg->start_hdl;//0
    memcpy(&req->param[0], database_cfg, sizeof(struct udfs_db_cfg));

    // Send the message
    ke_msg_send(req);
    return ret;
}

void app_udfs_enable_prf(uint8_t conidx)
{
    TRACE("BLE: %s,conidx %d\n", __func__,conidx);
}

void app_udfs_disconnected(uint8_t conidx)
{
    TRACE("BLE: %s,conidx %d\n", __func__,conidx);
}

void app_udfs_update_rd_value(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length)
{

}

void app_udfs_send_notification(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length)
{
    TRACE("%s conidx = %d, prf_user_id = %d, att_idx = %d, length = %d\r\n", __func__, conidx,prf_user_id,att_idx,length);

    struct udfs_send_data_req * req = KE_MSG_ALLOC_DYN(UDFS_SEND_NOTIFICATION,
                                                prf_get_task_from_id(TASK_ID_UDFS+prf_user_id),
                                                TASK_APP,
                                                udfs_send_data_req,
                                                length);
    req->conidx = conidx;
    req->prf_user_id = prf_user_id;
    req->att_idx = att_idx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

void app_udfs_send_indication(uint8_t conidx,uint16_t prf_user_id,uint16_t att_idx,uint8_t* data, uint32_t length)
{
    TRACE("%s conidx = %d, prf_user_id = %d, att_idx = %d, length = %d\r\n", __func__, conidx,prf_user_id,att_idx,length);

    struct udfs_send_data_req * req = KE_MSG_ALLOC_DYN(UDFS_SEND_INDICATION,
                                                prf_get_task_from_id(TASK_ID_UDFS+prf_user_id),
                                                TASK_APP,
                                                udfs_send_data_req,
                                                length);
    req->conidx = conidx;
    req->prf_user_id = prf_user_id;
    req->att_idx = att_idx;
    req->length = length;
    memcpy(req->value, data, length);

    ke_msg_send(req);
}

#endif //BLE_APP_UDFS
