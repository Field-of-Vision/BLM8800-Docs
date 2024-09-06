#ifndef AICADPAVRCP
#define AICADPAVRCP
#include "bt_types_def.h"

//#define AVRCP_TRACK_CHANGED


typedef U8 bt_avrcp_adp_state;
#define AVRCP_ADP_STATE_IDLE                    0
#define AVRCP_ADP_STATE_PENDING                 1
#define AVRCP_ADP_STATE_CONNECTED               2
#define AVRCP_ADP_STATE_PLAY                    3
#define AVRCP_ADP_STATE_PAUSE                   5
#define AVRCP_ADP_STATE_STOP                    6

typedef U16 bt_avrcpPanelOp;

#define APP_AVRCP_PANEL_SELECT            0x0000
#define APP_AVRCP_PANEL_UP                0x0001
#define APP_AVRCP_PANEL_DOWN              0x0002
#define APP_AVRCP_PANEL_LEFT              0x0003
#define APP_AVRCP_PANEL_RIGHT             0x0004
#define APP_AVRCP_PANEL_RIGHT_UP          0x0005
#define APP_AVRCP_PANEL_RIGHT_DOWN        0x0006
#define APP_AVRCP_PANEL_LEFT_UP           0x0007
#define APP_AVRCP_PANEL_LEFT_DOWN         0x0008
#define APP_AVRCP_PANEL_ROOT_MENU         0x0009
#define APP_AVRCP_PANEL_SETUP_MENU        0x000A
#define APP_AVRCP_PANEL_CONTENTS_MENU     0x000B
#define APP_AVRCP_PANEL_FAVORITE_MENU     0x000C
#define APP_AVRCP_PANEL_EXIT              0x000D

#define APP_AVRCP_PANEL_0                 0x0020
#define APP_AVRCP_PANEL_1                 0x0021
#define APP_AVRCP_PANEL_2                 0x0022
#define APP_AVRCP_PANEL_3                 0x0023
#define APP_AVRCP_PANEL_4                 0x0024
#define APP_AVRCP_PANEL_5                 0x0025
#define APP_AVRCP_PANEL_6                 0x0026
#define APP_AVRCP_PANEL_7                 0x0027
#define APP_AVRCP_PANEL_8                 0x0028
#define APP_AVRCP_PANEL_9                 0x0029
#define APP_AVRCP_PANEL_DOT               0x002A
#define APP_AVRCP_PANEL_ENTER             0x002B
#define APP_AVRCP_PANEL_CLEAR             0x002C

#define APP_AVRCP_PANEL_CHANNEL_UP        0x0030
#define APP_AVRCP_PANEL_CHANNEL_DOWN      0x0031
#define APP_AVRCP_PANEL_PREVIOUS_CHANNEL  0x0032
#define APP_AVRCP_PANEL_SOUND_SELECT      0x0033
#define APP_AVRCP_PANEL_INPUT_SELECT      0x0034
#define APP_AVRCP_PANEL_DISPLAY_INFO      0x0035
#define APP_AVRCP_PANEL_HELP              0x0036
#define APP_AVRCP_PANEL_PAGE_UP           0x0037
#define APP_AVRCP_PANEL_PAGE_DOWN         0x0038

#define APP_AVRCP_PANEL_POWER             0x0040
#define APP_AVRCP_PANEL_VOLUME_UP         0x0041
#define APP_AVRCP_PANEL_VOLUME_DOWN       0x0042
#define APP_AVRCP_PANEL_MUTE              0x0043
#define APP_AVRCP_PANEL_PLAY              0x0044
#define APP_AVRCP_PANEL_STOP              0x0045
#define APP_AVRCP_PANEL_PAUSE             0x0046
#define APP_AVRCP_PANEL_RECORD            0x0047
#define APP_AVRCP_PANEL_REWIND            0x0048
#define APP_AVRCP_PANEL_FAST_FORWARD      0x0049
#define APP_AVRCP_PANEL_EJECT             0x004A
#define APP_AVRCP_PANEL_FORWARD           0x004B
#define APP_AVRCP_PANEL_BACKWARD          0x004C

#define APP_AVRCP_PANEL_ANGLE             0x0050
#define APP_AVRCP_PANEL_SUBPICTURE        0x0051

#define APP_AVRCP_PANEL_F1                0x0071
#define APP_AVRCP_PANEL_F2                0x0072
#define APP_AVRCP_PANEL_F3                0x0073
#define APP_AVRCP_PANEL_F4                0x0074
#define APP_AVRCP_PANEL_F5                0x0075

#define APP_AVRCP_PANEL_VENDOR_UNIQUE     0x007E

#define APP_AVRCP_PANEL_NEXT_GROUP        0x017E
#define APP_AVRCP_PANEL_PREV_GROUP        0x027E

#define APP_AVRCP_PANEL_RESERVED          0x007F


typedef struct _AIC_ADP_AVRCP_EVENT_{
    BT_ADDR bdaddr;
    U32 avrcpparam;
}AIC_ADP_AVRCP_EVENT;

Status_BTDef aic_adp_avrcp_connect(BT_ADDR bdaddr);
void aic_adp_avrcp_send_key_stop(BT_ADDR bdaddr);
void aic_adp_avrcp_send_key_play(BT_ADDR bdaddr);
void aic_adp_avrcp_send_key_pause(BT_ADDR bdaddr);
void aic_adp_avrcp_send_key_forward(BT_ADDR bdaddr);
void aic_adp_avrcp_send_key_backward(BT_ADDR bdaddr);
void aic_adp_avrcp_send_key_volume_up(BT_ADDR bdaddr);
void aic_adp_avrcp_send_key_volume_down(BT_ADDR bdaddr);
Status_BTDef aic_adp_avrcp_send_volume_report(BT_ADDR bdaddr,                U8 volume);
void aic_adp_avrcp_register(   void);
void aic_adp_avrcp_init(void);
void aic_adp_avrcp_support_volume_sync(BOOL support);
#endif

