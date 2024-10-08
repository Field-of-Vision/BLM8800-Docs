#ifndef _PROMPT_H_
#define _PROMPT_H_

typedef enum {
    PROMPT_ID_NUM_0 = 0,
    PROMPT_ID_NUM_1,
    PROMPT_ID_NUM_2,
    PROMPT_ID_NUM_3,
    PROMPT_ID_NUM_4,
    PROMPT_ID_NUM_5,
    PROMPT_ID_NUM_6,
    PROMPT_ID_NUM_7,
    PROMPT_ID_NUM_8,
    PROMPT_ID_NUM_9,

    PROMPT_ID_POWER_ON,
    PROMPT_ID_POWER_OFF,
    PROMPT_ID_LANGUAGE_SWITCH,
    PROMPT_ID_CHARGE_PLEASE,
    PROMPT_ID_CHARGE_FINISH,

    PROMPT_ID_BT_PAIR_ENABLE,
    PROMPT_ID_BT_PAIRING,
    PROMPT_ID_BT_PAIRING_SUCCESS,
    PROMPT_ID_BT_PAIRING_FAIL,
    PROMPT_ID_BT_CALL_REFUSE,
    PROMPT_ID_BT_CALL_OVER,
    PROMPT_ID_BT_CALL_ANSWER,
    PROMPT_ID_BT_CALL_HUNG_UP,
    PROMPT_ID_BT_CALL_INCOMING_CALL,
    PROMPT_ID_BT_CALL_INCOMING_NUMBER,
    PROMPT_ID_BT_CONNECTED,
    PROMPT_ID_BT_DISCONNECT,
    PROMPT_ID_BT_WARNING,
    PROMPT_ID_BT_ALEXA_START,
    PROMPT_ID_BT_ALEXA_STOP,

    PROMPT_ID_NUM
} PROMPT_ID_ENUM;

#endif
