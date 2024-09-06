#ifndef AICADPMGR
#define AICADPMGR

#include "bt_types_def.h"
#include "aic_adp_type.h"
#include "aic_adp_dev.h"
#include "aic_adp_a2dp.h"
#include "aic_adp_avrcp.h"
#include "aic_adp_hfp.h"
#include "aic_adp_hsp.h"
#include "aic_adp_spp.h"
#include "aic_adp_hid.h"

#define APP_BT_ROLE_SWITCH_LIMIT   2


typedef struct _APP_DEVLIST{
    BT_ADDR bdaddr;
    U8 acl_mode;
    U8 role;
    bt_mgr_adp_state adp_state;
    bt_a2dp_adp_state a2dp_state;
    bt_avrcp_adp_state avrcp_state;
    bt_hid_adp_state hid_state;
    bt_hfp_adp_state hfp_state;
    bt_hfp_adp_call_status hfp_call_status;
    bt_hfp_adp_callhold_status hfp_call_hold;
    bt_hfp_adp_siri_status hfp_siri_status;
    BT_A2DP_ROLE a2dp_role;
    A2DP_AUDIO_CAP a2dp_audio_cap;
    U16 sco_handle;
    U16 negotiated_codec;
    S8 peer_volume_hfp;
    S8 peer_volume_a2dp;
    bt_class_of_device cod;
}APP_DEVLIST;

typedef struct _APP_BT_MGR{
    APP_DEVLIST device_list[LINK_MAX];
    BT_ADDR local_addr;
    BT_ADDR le_addr;
    U8 max_device_num;
    U8 connect_index;
    bt_class_of_device local_cod;
    char pin_code[16];
    U8 pin_code_len;
    U8 io_cap;
    char pass_key[16];
    U8 pass_key_len;
}APP_BT_MGR;

typedef struct _AIC_EVENT_{
    U32 EventId;
    U32 Param;
}AIC_EVENT;

typedef void (*app_msg_handle_cb)(AIC_EVENT *event);

typedef struct _APP_ADP_MSG_HANDLE{
    aic_bt_msg_module module;
    app_msg_handle_cb callback;
}app_adp_msg_handle;

typedef struct {
    bt_class_of_device cod;
    U8   inqMode;
    S8   rssi;
    U8   extInqResp[240];
}Mgr_InquiryResult_t;

typedef struct _AIC_ADP_MGR_EVENT_{
    BT_ADDR bdaddr;
    union {
        bt_err_type reason;
        Mgr_InquiryResult_t inqResultP;
    }p;
}AIC_ADP_MGR_EVENT;

APP_DEVLIST *app_bt_get_mgr_devinfo(BT_ADDR bdaddr);
extern void aic_adp_dispatch_msg(AIC_EVENT *event);


#endif
