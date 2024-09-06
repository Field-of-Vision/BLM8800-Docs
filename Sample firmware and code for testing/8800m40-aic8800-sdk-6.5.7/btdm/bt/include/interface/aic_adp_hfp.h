#ifndef AICADPHFP
#define AICADPHFP

#include "aic_adp_type.h"

enum Active_Profile{
    HANDSFREE     = 0,
    HANDSFREE_AG     ,
};

typedef U8 bt_hfp_adp_state;
#define HFP_ADP_STATE_IDLE                    0
#define HFP_ADP_STATE_PENDING                 1
#define HFP_ADP_STATE_CONNECTED               2

typedef U32 bt_hfp_adp_call_status;
#define BT_CALL_STATUS_NONE             0x0000
#define BT_CALL_STATUS_ACTIVE           0x0001
#define BT_CALL_STATUS_INCOMING         0x0010
#define BT_CALL_STATUS_OUTGOING         0x0020
#define BT_CALL_STATUS_ALERT            0x0030

typedef U8 AppHfHoldAction;
#define APP_HF_HOLD_RELEASE_HELD_CALLS   0
#define APP_HF_HOLD_RELEASE_ACTIVE_CALLS 1
#define APP_HF_HOLD_HOLD_ACTIVE_CALLS    2
#define APP_HF_HOLD_ADD_HELD_CALL        3
#define APP_HF_HOLD_CALL_TRANSFER        4

typedef U8 bt_hfp_adp_callhold_status;

#define BT_CALL_HELD_NONE      0
#define BT_CALL_HELD_ACTIVE    1
#define BT_CALL_HELD_NO_ACTIVE 2

typedef U8 bt_hfp_adp_siri_status;

#define BT_CALL_SIRI_OFF       0
#define BT_CALL_SIRI_ON        1

#define MAX_HANDLE_HFP_DATA 32

typedef struct _AIC_ADP_HFP_AUDIO_DATA{
    U16 len;
    U8 *data;
}AIC_ADP_HFP_AUDIO_DATA;

typedef struct {
    bt_err_type reason;
}Hfp_Con_t;

typedef struct {
    bt_err_type reason;
}Hfp_Disc_t;

typedef struct {
    bt_err_type reason;
    U16 negotiated_codec;
}Hfp_Sco_t;

typedef struct {
    AIC_ADP_HFP_AUDIO_DATA * buff;
}Hfp_DataSend_t;

typedef struct {
    AIC_ADP_HFP_AUDIO_DATA * buff;
}Hfp_DataInd_t;

typedef struct {
    bt_hfp_adp_call_status callS;
}Hfp_CallStatus_t;

typedef struct {
    bt_hfp_adp_call_status callS;
}Hfp_CallSetUpStatus_t;

typedef struct {
    bt_hfp_adp_callhold_status callholdS;
}Hfp_CallHold_t;

typedef struct {
    bt_hfp_adp_siri_status siriS;
}Hfp_SiriStatus_t;

typedef struct {
    char phonenum[MAX_HANDLE_HFP_DATA];
}Hfp_CallNum_t;

typedef struct {
    U8 volume;
}Hfp_CallVolume_t;

typedef struct {
    char *at_result;
}Hfp_ComATResult_t;

typedef struct _AIC_ADP_HFP_EVENT_{
    BT_ADDR bdaddr;
    enum Active_Profile role;
    union {
        Hfp_Con_t conP;
        Hfp_Disc_t discP;
        Hfp_Sco_t scoP;
        Hfp_DataSend_t datasendP;
        Hfp_DataInd_t dataindP;
        Hfp_CallStatus_t callP;
        Hfp_CallSetUpStatus_t callsetupP;
        Hfp_CallHold_t callholdP;
        Hfp_SiriStatus_t siriP;
        Hfp_CallNum_t callnumP;
        Hfp_CallVolume_t volP;
        Hfp_ComATResult_t atP;
    }p;
}AIC_ADP_HFP_EVENT;

void aic_adp_hfp_init(enum Active_Profile prf);
enum Active_Profile aic_adp_hfp_get_active_prf(void);
void aic_adp_hfp_register(void);
Status_BTDef aic_adp_hfp_send_siri_report(BT_ADDR bdaddr );
Status_BTDef aic_adp_hfp_send_voice_recognition(BT_ADDR bdaddr , bool en);
Status_BTDef aic_adp_hfp_send_volume(BT_ADDR bdaddr ,uint8_t Gain);
Status_BTDef aic_adp_hfp_disable_NREC(BT_ADDR bdaddr );
Status_BTDef aic_adp_hfp_call_answer(BT_ADDR bdaddr );
Status_BTDef aic_adp_hfp_call_redial(BT_ADDR bdaddr );
void aic_adp_hfp_call_release(BT_ADDR bdaddr);
Status_BTDef aic_adp_hfp_list_current_calls(BT_ADDR bdaddr);

Status_BTDef aic_adp_hfp_call_hold(BT_ADDR bdaddr ,AppHfHoldAction action ,U8 index);
Status_BTDef aic_adp_hfp_send_sco_data(BT_ADDR bdaddr , AIC_ADP_HFP_AUDIO_DATA *buffer);
BOOL aic_adp_hf_sco_state(BT_ADDR bdaddr );
Status_BTDef aic_adp_hfg_connect(BT_ADDR bdaddr);
Status_BTDef aic_adp_hf_connect(BT_ADDR bdaddr);
Status_BTDef aic_adp_hf_disconnect(BT_ADDR bdaddr);
Status_BTDef aic_adp_hf_sco_connect(BT_ADDR bdaddr);
Status_BTDef aic_adp_hf_sco_disconnect(BT_ADDR bdaddr);
U16 aic_adp_hfp_get_scohandle_by_addr(BT_ADDR bdaddr);
U16 aic_adp_hfp_get_negotiated_codec_by_addr(BT_ADDR bdaddr);
void aic_adp_hfp_set_battery_level(uint8_t level);
void aic_adp_hfp_battery_report_proc(void);
BOOL aic_adp_hfp_get_voicerecognition_state(BT_ADDR bdaddr);
Status_BTDef aic_adp_hfp_send_at_cclk(BT_ADDR bdaddr);
Status_BTDef aic_adp_hfp_send_raw_data(BT_ADDR bdaddr,char *at_string);

#endif

