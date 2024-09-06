#ifndef _AIC_ADP_TYPE_H_
#define _AIC_ADP_TYPE_H_

#include"bt_types_def.h"
#include"aic_bt_msg.h"


typedef struct{
    U8          *data;
    U16         len;
} host_data_struct;

#define SIZE_OF_LINKKEY 	16


typedef uint8_t AppBtScanMode;

#define BT_NOSCAN           0x00 /* discoverable and connectable are closed*/
#define BT_DISCOVERABLE     0x01 /* discoverable is open but not connectable */
#define BT_CONNECTABLE      0x02 /* connectable is open but not discoverable */
#define BT_ALLSCAN          0x03 /* discoverable and connectable are opened*/
#define BT_LIMITED_ALLSCAN  0x13 /* discoverable and connectable are limited*/


typedef struct AppBtAccessModeInfo
{
    U16 inqInterval;    /* inquiry scan interval */
    U16 inqWindow;      /* inquiry scan window */
    U16 pageInterval;   /* page scan interval */
    U16 pageWindow;     /* page scan window */
} AppBtAccessModeInfo;

typedef U16 AppBtLinkPolicy;

#define BT_DISABLE_ALL         0x0000
#define BT_ALLOW_ROLE_SWITCH   0x0001
#define BT_HOLD_MODE           0x0002
#define BT_SNIFF_MODE          0x0004
#define BT_PARK_MODE           0x0008
#define BT_SCATTER_MODE        0x0010


typedef struct AppBtSniffInfo
{
    U16 maxInterval;
    U16 minInterval;
    U16 attempt;
    U16 timeout;
} AppBtSniffInfo;

#ifndef TimeT
typedef U32 TimeT;
#endif

typedef U32 bt_class_of_device;
/***************************
 * service class fields
 ***************************/
#define BTM_COD_SERVICE_LMTD_DISCOVER       0x00002000
#define BTM_COD_SERVICE_POSITIONING         0x00010000
#define BTM_COD_SERVICE_NETWORKING          0x00020000
#define BTM_COD_SERVICE_RENDERING           0x00040000
#define BTM_COD_SERVICE_CAPTURING           0x00080000
#define BTM_COD_SERVICE_OBJ_TRANSFER        0x00100000
#define BTM_COD_SERVICE_AUDIO               0x00200000
#define BTM_COD_SERVICE_TELEPHONY           0x00400000
#define BTM_COD_SERVICE_INFORMATION         0x00800000
                                            
/***************************                
 * major service class fields. select one   
 ***************************/               
#define BTM_COD_MAJOR_MISCELLANEOUS         0x00000000
#define BTM_COD_MAJOR_COMPUTER              0x00000100
#define BTM_COD_MAJOR_PHONE                 0x00000200
#define BTM_COD_MAJOR_LAN_ACCESS_PT         0x00000300
#define BTM_COD_MAJOR_AUDIO                 0x00000400
#define BTM_COD_MAJOR_PERIPHERAL            0x00000500
#define BTM_COD_MAJOR_IMAGING               0x00000600
#define BTM_COD_MAJOR_WEARABLE              0x00000700
#define BTM_COD_MAJOR_TOY                   0x00000800
#define BTM_COD_MAJOR_HEALTH                0x00000900
#define BTM_COD_MAJOR_UNCLASSIFIED          0x00001F00



/* minor device class field for Computer Major Class */
#define BTM_COD_MINOR_UNCLASSIFIED          0x00000000
#define BTM_COD_MINOR_DESKTOP_WORKSTATION   0x00000004
#define BTM_COD_MINOR_SERVER_COMPUTER       0x00000008
#define BTM_COD_MINOR_LAPTOP                0x0000000C
#define BTM_COD_MINOR_HANDHELD_PC_PDA       0x00000010 /* clam shell */
#define BTM_COD_MINOR_PALM_SIZE_PC_PDA      0x00000014
#define BTM_COD_MINOR_WEARABLE_COMPUTER     0x00000018/* watch sized */


/* minor device class field for Phone Major Class */
#define BTM_COD_MINOR_UNCLASSIFIED          0x00000000
#define BTM_COD_MINOR_CELLULAR              0x00000004
#define BTM_COD_MINOR_CORDLESS              0x00000008
#define BTM_COD_MINOR_SMART_PHONE           0x0000000C
/* wired modem or voice gatway */
#define BTM_COD_MINOR_WIRED_MDM_V_GTWY      0x00000010
#define BTM_COD_MINOR_ISDN_ACCESS           0x00000014


/* minor device class field for LAN Access Point Major Class */
/* Load Factor Field bit 5-7 */
#define BTM_COD_MINOR_FULLY_AVAILABLE       0x00000000
#define BTM_COD_MINOR_1_17_UTILIZED         0x00000020
#define BTM_COD_MINOR_17_33_UTILIZED        0x00000040
#define BTM_COD_MINOR_33_50_UTILIZED        0x00000060
#define BTM_COD_MINOR_50_67_UTILIZED        0x00000080
#define BTM_COD_MINOR_67_83_UTILIZED        0x000000A0
#define BTM_COD_MINOR_83_99_UTILIZED        0x000000C0
#define BTM_COD_MINOR_NO_SERVICE_AVAILABLE  0x000000E0


/* minor device class field for Audio/Video Major Class */
#define BTM_COD_MINOR_UNCLASSIFIED          0x00000000
#define BTM_COD_MINOR_CONFM_HEADSET         0x00000004
#define BTM_COD_MINOR_CONFM_HANDSFREE       0x00000008
#define BTM_COD_MINOR_MICROPHONE            0x00000010
#define BTM_COD_MINOR_LOUDSPEAKER           0x00000014
#define BTM_COD_MINOR_HEADPHONES            0x00000018
#define BTM_COD_MINOR_PORTABLE_AUDIO        0x0000001C
#define BTM_COD_MINOR_CAR_AUDIO             0x00000020
#define BTM_COD_MINOR_SET_TOP_BOX           0x00000024
#define BTM_COD_MINOR_HIFI_AUDIO            0x00000028
#define BTM_COD_MINOR_VCR                   0x0000002C
#define BTM_COD_MINOR_VIDEO_CAMERA          0x00000030
#define BTM_COD_MINOR_CAMCORDER             0x00000034
#define BTM_COD_MINOR_VIDEO_MONITOR         0x00000038
#define BTM_COD_MINOR_VIDDISP_LDSPKR        0x0000003C
#define BTM_COD_MINOR_VIDEO_CONFERENCING    0x00000040
#define BTM_COD_MINOR_GAMING_TOY            0x00000048


/* minor device class field for Peripheral Major Class */
/* Bits 6-7 independently specify mouse, keyboard, or combo mouse/keyboard */
#define BTM_COD_MINOR_KEYBOARD              0x00000040
#define BTM_COD_MINOR_POINTING              0x00000080
#define BTM_COD_MINOR_COMBO                 0x000000C0
/* Bits 2-5 OR'd with selection from bits   6-7 */
#define BTM_COD_MINOR_UNCLASSIFIED          0x00000000
#define BTM_COD_MINOR_JOYSTICK              0x00000004
#define BTM_COD_MINOR_GAMEPAD               0x00000008
#define BTM_COD_MINOR_REMOTE_CONTROL        0x0000000C
#define BTM_COD_MINOR_SENSING_DEVICE        0x00000010
#define BTM_COD_MINOR_DIGITIZING_TABLET     0x00000014
#define BTM_COD_MINOR_CARD_READER           0x00000018 /* e.g. SIM card reader */
#define BTM_COD_MINOR_DIGITAL_PAN           0x0000001c
#define BTM_COD_MINOR_HAND_SCANNER          0x00000020
#define BTM_COD_MINOR_HAND_GESTURAL_INPUT   0x00000024


/* minor device class field for Imaging Major Class */
/* Bits 5-7 independently specify display, camera, scanner, or printer */
#define BTM_COD_MINOR_IMAGE_UNCLASSIFIED    0x00000000
#define BTM_COD_MINOR_IMAGE_DISPLAY         0x00000010
#define BTM_COD_MINOR_IMAGE_CAMERA          0x00000020
#define BTM_COD_MINOR_IMAGE_SCANNER         0x00000040
#define BTM_COD_MINOR_IMAGE_PRINTER         0x00000080

/* class of device masks */
#define BTM_COD_MAJOR_MASK                  0x00001F00
#define BTM_COD_MINOR_MASK                  0x000000FC

/* End of bt_class_of_device */

/*---------------------------------------------------------------------------
 * bt_iocapabilities
 *
 *     Defines the I/O capabilities of a device.  Simple Pairing will
 *     generate different events based on the capabilities of the device.
 */
typedef U8 bt_iocapabilities;

#define DISPLAY_ONLY               0 /* The device is only capable of display     */
#define DISPLAY_YESNO              1 /* The device can display and accept input   */
#define KEYBOARD_ONLY              2 /* The device is a keyboard with no display  */
#define NO_INPUT_NO_OUTPUT         3 /* The device is not capable of I/O          */


typedef U8 bt_mgr_adp_state;
#define APP_MGR_STATE_IDLE         0
#define APP_MGR_STATE_PENDING      1
#define APP_MGR_STATE_CONNECTED    2


typedef U8 bt_err_type;
/*---------------------------------------------------------------------------
 * Bt Error Type
 */

#define BT_NO_ERROR             0x00 
#define BT_UNKNOWN_HCI_CMD      0x01 
#define BT_NO_CONNECTION        0x02 
#define BT_HARDWARE_FAILURE     0x03 
#define BT_PAGE_TIMEOUT         0x04 
#define BT_AUTHENTICATE_FAILURE 0x05 
#define BT_MISSING_KEY          0x06 
#define BT_MEMORY_FULL          0x07 
#define BT_CONNECTION_TIMEOUT   0x08 
#define BT_MAX_CONNECTIONS      0x09 
#define BT_MAX_SCO_CONNECTIONS  0x0a 
#define BT_ACL_ALREADY_EXISTS   0x0b 
#define BT_COMMAND_DISALLOWED   0x0c 
#define BT_LIMITED_RESOURCE     0x0d 
#define BT_SECURITY_ERROR       0x0e 
#define BT_PERSONAL_DEVICE      0x0f 
#define BT_HOST_TIMEOUT         0x10 
#define BT_UNSUPPORTED_FEATURE  0x11 
#define BT_INVALID_HCI_PARM     0x12 
#define BT_USER_TERMINATED      0x13 
#define BT_LOW_RESOURCES        0x14 
#define BT_POWER_OFF            0x15 
#define BT_LOCAL_TERMINATED     0x16 
#define BT_REPEATED_ATTEMPTS    0x17 
#define BT_PAIRING_NOT_ALLOWED  0x18 
#define BT_UNKNOWN_LMP_PDU      0x19 
#define BT_UNSUPPORTED_REMOTE   0x1a 
#define BT_SCO_OFFSET_REJECT    0x1b 
#define BT_SCO_INTERVAL_REJECT  0x1c 
#define BT_SCO_AIR_MODE_REJECT  0x1d 
#define BT_INVALID_LMP_PARM     0x1e 
#define BT_UNSPECIFIED_ERR      0x1f 
#define BT_UNSUPPORTED_LMP_PARM 0x20 
#define BT_ROLE_CHG_NOT_ALLOWED 0x21 
#define BT_LMP_RESPONSE_TIMEOUT 0x22 
#define BT_LMP_TRANS_COLLISION  0x23 
#define BT_LMP_PDU_NOT_ALLOWED  0x24 
#define BT_ENCRYP_MODE_NOT_ACC  0x25 
#define BT_UNIT_KEY_USED        0x26 
#define BT_QOS_NOT_SUPPORTED    0x27 
#define BT_INSTANT_PASSED       0x28 
#define BT_PAIR_UNITKEY_NO_SUPP 0x29 
#define BT_NOT_FOUND            0xf1 
#define BT_REQUEST_CANCELLED    0xf2 
#define BT_INVALID_SDP_PDU      0xd1 
#define BT_SDP_DISCONNECT       0xd2 
#define BT_SDP_NO_RESOURCES     0xd3 
#define BT_SDP_INTERNAL_ERR     0xd4 
#define BT_STORE_LINK_KEY_ERR   0xe0

/* End of Bt Error Type */


#endif
