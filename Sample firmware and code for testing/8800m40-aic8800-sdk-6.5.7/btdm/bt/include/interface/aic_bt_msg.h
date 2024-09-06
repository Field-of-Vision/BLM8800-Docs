#ifndef __AICBTMSG_H
#define __AICBTMSG_H

/* aic msg base module id */
typedef enum AIC_MSG_MODULE{
    AIC_COMMON = 1,
    AIC_MGR,
    AIC_A2DP,
    AIC_AVRCP,
    AIC_HFP,
    AIC_HSP,
    AIC_HID,
    AIC_SPP,
    AIC_TEST,
    AIC_TWS,
    AIC_MAX_MODULE
}aic_bt_msg_module;



/*aic adp msg base module id */
enum{
    AIC_ADP_COMMON      = (AIC_COMMON    <<8 ),
    AIC_ADP_MGR         = (AIC_MGR       <<8 ),
    AIC_ADP_A2DP        = (AIC_A2DP      <<8 ),
    AIC_ADP_AVRCP       = (AIC_AVRCP     <<8 ),
    AIC_ADP_HFP         = (AIC_HFP       <<8 ),
    AIC_ADP_HSP         = (AIC_HSP       <<8 ),
    AIC_ADP_HID         = (AIC_HID       <<8 ),
    AIC_ADP_SPP         = (AIC_SPP       <<8 ),
    AIC_ADP_TEST        = (AIC_TEST      <<8 ),
    AIC_ADP_TWS         = (AIC_TWS       <<8 ),
    AIC_ADP_MAX_MODULE  = (AIC_MAX_MODULE<<8 )
};

#define AIC_ADP_MSG_OFFSET  0

/*aic adp msg */
enum{
    AIC_ADP_FIRST_COMMON_MSG = (AIC_ADP_MSG_OFFSET + AIC_ADP_COMMON),
    AIC_ADP_STACK_INIT,
    AIC_ADP_ACCESSIBLE_CHANGE,
    AIC_ADP_ENCRYPYION_CHANGE,
    AIC_ADP_LAST_COMMON_MSG,

    AIC_ADP_FIRST_MGR_MSG    = (AIC_ADP_MSG_OFFSET + AIC_ADP_MGR),
    AIC_ADP_ACL_CONNECT_IND,
    AIC_ADP_ACL_CONNECT_CNF,
    AIC_ADP_ACL_DISCONNECT,
    AIC_ADP_SCO_CONNECT_IND,
    AIC_ADP_SCO_CONNECT_CNF,
    AIC_ADP_SCO_DISCONNECTED,
    AIC_ADP_PIN_CODE_REQ,
    AIC_ADP_PASS_KEY_REQ,
    AIC_ADP_PAIRING_COMPLETE,
    AIC_ADP_INQUIRY_RESULT,
    AIC_ADP_INQUIRY_COMPLETE,
    AIC_ADP_INQUIRY_CANCELED,
    AIC_ADP_BLE_ADV_DATA,
    AIC_ADP_LAST_MGR_MSG,

    AIC_ADP_FIRST_A2DP_MSG   = (AIC_ADP_MSG_OFFSET + AIC_ADP_A2DP),
    AIC_ADP_A2DP_STREAM_OPEN,
    AIC_ADP_A2DP_STREAM_STARTED,
    AIC_ADP_A2DP_STREAM_SUSPENDED,
    AIC_ADP_A2DP_STREAM_CLOSED,
    AIC_ADP_A2DP_STREAM_DATA_IND,
    AIC_ADP_A2DP_STREAM_PACKET_SENT,
    AIC_ADP_LAST_A2DP_MSG,

    AIC_ADP_FIRST_AVRCP_MSG  = (AIC_ADP_MSG_OFFSET + AIC_ADP_AVRCP),
    AIC_ADP_AVRCP_CONNECT,
    AIC_ADP_AVRCP_DISCONNECT,
    AIC_ADP_AVRCP_PANEL_PRESS,
    AIC_ADP_AVRCP_ADV_VOLUME_CHANGE,
    AIC_ADP_AVRCP_ADV_PLAYSTAUTS_CHANGE,
    AIC_ADP_LAST_AVRCP_MSG,

    AIC_ADP_FIRST_HFP_MSG    = (AIC_ADP_MSG_OFFSET + AIC_ADP_HFP),
    AIC_ADP_HFP_CONNECTED,
    AIC_ADP_HFP_DISCONNECTED,
    AIC_ADP_HFP_AUDIO_CONNECTED,
    AIC_ADP_HFP_AUDIO_DISCONNECTED,
    AIC_ADP_HFP_AUDIO_DATA_SENT,
    AIC_ADP_HFP_AUDIO_DATA_IND,
    AIC_ADP_HFP_CALL_STATUS_IND,
    AIC_ADP_HFP_CALLSETUP_STATUS_IND,
    AIC_ADP_HFP_CALLHOLD_STATUS_IND,
    AIC_ADP_HFP_RING_IND,
    AIC_ADP_HFP_CURRENT_CALL_NUM,
    AIC_ADP_HFP_SPEAKER_VOLUME,
    AIC_ADP_HFP_SIRI_STATUS,
    AIC_ADP_HFP_AG_INDICATORS_STATUS,
    AIC_ADP_HFP_COMMON_AT_RESULT_IND,
    AIC_ADP_LAST_HFP_MSG,

    AIC_ADP_FIRST_HSP_MSG    = (AIC_ADP_MSG_OFFSET + AIC_ADP_HSP),
    AIC_ADP_HSP_CONNECTED,
    AIC_ADP_HSP_DISCONNECTED,
    AIC_ADP_HSP_AUDIO_CONNECTED,
    AIC_ADP_HSP_AUDIO_DISCONNECTED,
    AIC_ADP_HSP_AUDIO_DATA_SENT,
    AIC_ADP_HSP_AUDIO_DATA_IND,
    AIC_ADP_HSP_RING_IND,
    AIC_ADP_HSP_SPEAKER_VOLUME,
    AIC_ADP_LAST_HSP_MSG,

    AIC_ADP_FIRST_HID_MSG    = (AIC_ADP_MSG_OFFSET + AIC_ADP_HID),
    AIC_ADP_HID_CONNECTED,
    AIC_ADP_HID_DISCONNECTED,
    AIC_ADP_LAST_HID_MSG,

    AIC_ADP_FIRST_SPP_MSG    = (AIC_ADP_MSG_OFFSET + AIC_ADP_SPP),
    AIC_ADP_SPP_CONNECTED_IND,
    AIC_ADP_SPP_CONNECTED_CNF,
    AIC_ADP_SPP_DISCONNECTED,
    AIC_ADP_SPP_DATA_SENT,
    AIC_ADP_SPP_DATA_IND,
    AIC_ADP_LAST_SPP_MSG,

    AIC_ADP_FIRST_TEST_MSG   = (AIC_ADP_MSG_OFFSET + AIC_ADP_TEST),
    AIC_ADP_TEST_CONNECTED_CNF,
    AIC_ADP_TEST_DISCONNECTED,
    AIC_ADP_TEST_SCO_CONNECT,
    AIC_ADP_TEST_SCO_DISCONNECT,
    AIC_ADP_TEST_SCO_DATA_SENT,
    AIC_ADP_TEST_SCO_DATA_IND,
    AIC_ADP_TEST_INQUIRY_RESULT,
    AIC_ADP_TEST_INQUIRY_COMPLETE,
    AIC_ADP_TEST_INQUIRY_CANCELED,
    AIC_ADP_TEST_L2CAP_CONNECTD,
    AIC_ADP_TEST_L2CAP_DISCONNECTD,
    AIC_ADP_TEST_L2CAP_DATA_SENT,
    AIC_ADP_TEST_L2CAP_DATA_IND,
    AIC_ADP_LAST_TEST_MSG,

    AIC_ADP_FIRST_TWS_MSG    = (AIC_ADP_MSG_OFFSET + AIC_ADP_TWS),
    AIC_ADP_TWS_CONNECTED_IND,
    AIC_ADP_TWS_CONNECTED_CNF,
    AIC_ADP_TWS_DISCONNECTED,
    AIC_ADP_TWS_STREAM_STARTED,
    AIC_ADP_TWS_STREAM_SUSPENDED,
    AIC_ADP_TWS_STREAM_DATA_IND,
    AIC_ADP_TWS_SCO_CONNECT,
    AIC_ADP_TWS_SCO_DISCONNECT,
    AIC_ADP_TWS_SCO_DATA_IND,
    AIC_ADP_TWS_DATA_IND,
    AIC_ADP_TWS_DATA_SEND,
    AIC_ADP_TWS_TRIG_NUM,
    AIC_ADP_TWS_AUDIO_SYNC_MSG,
    AIC_ADP_TWS_ADV_DATA,
    AIC_ADP_TWS_LOST_SEQUENCE,
    AIC_ADP_TWS_MSS_COMPLETE,
    AIC_ADP_LAST_TWS_MSG,
};

#endif
