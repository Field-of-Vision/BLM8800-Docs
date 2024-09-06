#ifndef _AIC_ADP_TWS_
#define _AIC_ADP_TWS_

#include "aic_adp_type.h"

typedef enum {
    TWS_SLAVE = 0,
    TWS_MASTER,
    TWS_NOROLE,
    TWS_NOSUPPORT,
}AIC_ADP_TWS_ROLE;

#ifndef RWIP_TIME_T
#define RWIP_TIME_T
typedef struct
{
    /// Integer part of the time (in half-slot)
    uint32_t hs;
    /// Fractional part of the time (in half-us) (range: 0-624)
    uint32_t hus;
} rwip_time_t;

typedef struct
{
    /// Integer part of the time (in half-slot)
    uint32_t clk_off_hs;
    /// Fractional part of the time (in half-us) (range: 0-624)
    uint32_t clk_off_hus;
} TWS_BT_CLK_INFO_Type;
#endif

typedef enum {
    AIC_IDLE = 0,
    AIC_PENDING,
    AIC_CONNECTED,
    AIC_STOP,
    AIC_START,
    AIC_CALL,
    AIC_STATE_END = 0xff,
}AIC_TWS_STATE;

typedef struct {
    bt_err_type reason;
}Tws_Con_t;

typedef struct {
    bt_err_type reason;
    AIC_ADP_TWS_ROLE last_role;
}Tws_Disc_t;

typedef struct {
    U32 tws_trig_data;//redefined by AppTwsMediaDataStruct
}Tws_TrigNum_t;

typedef struct {
    U32 tws_sync_data;//redefined by AppTwsMediaDataStruct
}Tws_AudSync_t;

typedef struct {
    host_data_struct * buff;
}Tws_DataSend_t;

typedef struct {
    host_data_struct * buff;
}Tws_DataInd_t;


typedef struct _AIC_ADP_TWS_EVENT_{
    BT_ADDR bdaddr;
    union {
        Tws_Con_t conP;
        Tws_Disc_t discP;
        Tws_TrigNum_t trigP;
        Tws_AudSync_t syncP;
        Tws_DataSend_t datasendP;
        Tws_DataInd_t dataindP;
    }p;
}AIC_ADP_TWS_EVENT;

void aic_adp_tws_init(void);
void aic_adp_connect_tws_peer_device(BT_ADDR * bdaddr);
void aic_adp_disconnect_tws(void);
uint8_t aic_tws_get_porttype(void);
BOOL aic_adp_send_data(uint8_t* ptrData, uint16_t length);
BOOL aic_adp_check_cmp_twsaddr(BT_ADDR bdaddr);
AIC_ADP_TWS_ROLE tws_app_get_role(void);
AIC_ADP_TWS_ROLE tws_app_get_flash_role(void);
void aic_adp_update_tws_flash_role(AIC_ADP_TWS_ROLE role);
rwip_time_t aic_adp_get_native_clk_plus_offset(void);
TWS_BT_CLK_INFO_Type aic_adp_get_slave_bt_offset(void);
void aic_adp_set_audio_sync_param(U32 synclk,U32 counternum,U32 samplerate,U32 bt_counter,U32 bt_counter_offset,U32 strb_cycle_offset);
void aic_adp_tws_restart(void);
void aic_adp_host_control_tws_sync_con(BOOL con_or_disc);
void aic_adp_host_m_s_switch(void);
void aic_adp_host_sync_stop(void);

/************************************************
function: aic_adp_tws_set_scan_para
          set ble scan param and then make scan enable,the param was set in adp layer.

          reset: 1:scan allow adv all
                 0:scan allow adv in white list
*************************************************/
void aic_adp_tws_set_scan_para(U8 reset);

/************************************************
function: aic_adp_tws_set_scan_disable
          set ble scan disable
*************************************************/
void aic_adp_tws_set_scan_disable(void);

/************************************************
function: aic_adp_tws_start_adv
          set ble adv enable,the param was set in adp layer.
*************************************************/
void aic_adp_tws_start_adv(BT_ADDR bdaddr);

/************************************************
function: aic_adp_tws_stop_adv
          disable ble adv
*************************************************/
void aic_adp_tws_stop_adv(void);
/************************************************
function: aic_adp_tws_clear_whitelist
          clear whitelist in fw
*************************************************/
void aic_adp_tws_clear_whitelist(void);

#endif

