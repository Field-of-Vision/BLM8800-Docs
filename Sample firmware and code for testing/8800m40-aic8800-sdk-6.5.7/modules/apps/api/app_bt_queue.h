#ifndef __APP_BT_FUNC_H__
#define __APP_BT_FUNC_H__

#include "aic_adp_api.h"

#if PLF_AIC8800
#include "bt_aic8800_drvif.h"
#elif PLF_AIC8800MC
#include "bt_aic8800mc_drvif.h"
#elif PLF_AIC8800M40
#include "bt_aic8800m40_drvif.h"
#else
#error "Invalid platform for btdm"
#endif

typedef enum _bt_queue_req {
        BT_INQUIRY_DEV                                = 0,
        BT_INQUIRY_CANCEL                             ,
        BT_SET_SCAN_MODE                              ,
        BT_SET_LINK_POLICY                            ,
        BT_SET_SNIFF_TIMER                            ,
        BT_STOP_SNIFF                                 ,
        BT_ROLE_SWITCH                                ,
        BT_DISCONNECT_LINK                            ,
        BT_DISCONNECT_LINK_ALL                        ,
        BT_A2DP_CONNECT                               ,
        BT_A2DP_DISCONNECT                            ,
        BT_HFP_CONNECT                                ,
        BT_HFP_DISCONNECT                             ,
        BT_HFP_SCO_CONNECT                            ,
        BT_HFP_SCO_DISCONNECT                         ,
#if APP_SUPPORT_HSP == 1
        BT_HSP_CONNECT                                ,
        BT_HSP_DISCONNECT                             ,
        BT_HSP_SCO_CONNECT                            ,
        BT_HSP_SCO_DISCONNECT                         ,
#endif
#if APP_SUPPORT_A2DP_SOURCE == 1
        BT_A2DP_SOURCE_CONNECT                        ,
        BT_A2DP_SOURCE_START                          ,
        BT_A2DP_SOURCE_SEND_DATA                      ,
#endif
#if APP_SUPPORT_HFG == 1
        BT_HFG_CONNECT                                ,
#endif
#if APP_SUPPORT_TWS == 1
        BT_TWS_CONNECT                                ,
        BT_TWS_SEND_DATA                              ,
        BT_TWS_SYNC_CTRL                              ,
        BT_TWS_MSS_CTRL                               ,
        BT_TWS_STOP_LOCAL_SYNC_CTRL                   ,
        BT_TWS_RESET                                  ,
        BT_TWS_DISC                                   ,
        BT_TWS_VISIBLE_REOPEN                         ,
#endif
        BT_GENERATE_KEY_COMPLETE                      ,
        BT_TWS_SNED_SYNC_PARAM                        ,
        BT_AUDIO_SEND_RESTART                         ,
        BT_AUDIO_SEND_MODE_REPLAY                     ,
        BT_KEY_MSG                                    ,
        BT_WEARING_STATE                              ,
        BT_SET_LP_LEVEL                               ,
#if FPGA == 0
        BT_ERASE_FLASH                                ,
#endif
        BT_DUT_TEST                                   ,
        BT_NO_SCAN                                    ,
        BT_ISCAN                                      ,
        BT_PSCAN                                      ,
        BT_BOTH_SCAN                                  ,
#if APP_SUPPORT_OTA_BOX
        BT_OTA_CONNECT                                ,
        BT_OTA_CONNECT_ID                             ,
        BT_OTA_SEND_DATA                              ,
#endif
        BT_NON_SIGNALING_TEST                         ,
        BT_CHANGE_LOCAL_NAME                          ,
#if MAX_THROUGHPUT_TEST == 1
        BT_SPP_SEND_START                             ,
#endif
}bt_queue_req;

typedef struct{
    U32 current_clk;
    U32 counterNum;
    U32 master_current_samplerate;
    U32 current_bt_counter;
    U32 current_bt_counter_offset;
    U32 strb_cycle_offset;
}AppTwsMediaDataStruct;

typedef struct {
    uint8_t len;
    uint8_t maxResp;
}AppBtInquiryP;

typedef struct {
    BT_ADDR bdaddr;
    uint8_t on_off;
}AppA2dpP;

typedef struct {
    uint8_t tws_sync_ctrl;
}AppTwsP;

typedef struct {
    BT_ADDR bdaddr;
    AppBtLinkPolicy policy;
}AppBtLinkPolicyP;

typedef struct {
    BT_ADDR bdaddr;
    AppBtSniffInfo sniff_info;
    uint32_t timeout;
}AppBtSniffP;

typedef struct {
    uint8_t dev_id;
    uint32_t num;
}AppBtOtaP;

typedef struct _bt_msg_param {
    union {
        BT_ADDR bdaddr;
        host_data_struct buff;
        AppA2dpP a2dp_param;
        AppBtInquiryP inquiry_param;
        AppTwsP tws_param;
        AppBtLinkPolicyP linkpolicy_param;
        AppBtSniffP btsniff_param;
        AppBtOtaP btota_param;
        AppBtScanMode mode;
        uint8_t dut;
        uint8_t lp_level;
        uint8_t audio_mode;
        AppTwsMediaDataStruct sync_param;
        uint32_t key;
        uint8_t wearing_state;
        char local_name[32];
    }p;
} bt_msg_param;

typedef struct {
    uint32_t msg_id;
    bt_msg_param param;
} APP_BT_MSG;

int app_bt_queue_init(void);

int app_bt_role_switch(BT_ADDR* bdaddr);

int app_bt_disconnect_acl(BT_ADDR* bdaddr);

int app_bt_disconnect_all_acl(void);

int app_bt_stop_sniff(BT_ADDR* bdaddr);

int app_bt_setscanmode(AppBtScanMode mode);

int app_bt_set_linkpolicy(BT_ADDR* bdaddr, AppBtLinkPolicy policy);

int app_bt_set_sniff_timer(BT_ADDR *bdaddr,
                                        AppBtSniffInfo* sniff_info,
                                        TimeT Time);

int app_bt_connect_a2dp(BT_ADDR *bdaddr);

int app_bt_source_connect_a2dp(BT_ADDR *bdaddr);

int app_bt_close_a2dp(BT_ADDR *bdaddr);

int app_bt_connect_hfg(BT_ADDR *bdaddr);

int app_bt_connect_hfp(BT_ADDR *bdaddr);

int app_bt_disconnect_hfp(BT_ADDR *bdaddr);

int app_bt_hfp_connect_sco(BT_ADDR *bdaddr);

int app_bt_hfp_disconnect_sco(BT_ADDR *bdaddr);

#if APP_SUPPORT_HSP == 1
int app_bt_connect_hsp(BT_ADDR *bdaddr);

int app_bt_hsp_connect_sco(BT_ADDR *bdaddr);

int app_bt_hsp_disconnect_sco(BT_ADDR *bdaddr);

int app_bt_disconnect_hsp(BT_ADDR *bdaddr);

#endif

#if APP_SUPPORT_A2DP_SOURCE == 1
int app_bt_a2dp_start(BT_ADDR* bdaddr,uint32_t on);

int app_bt_a2dp_send_data(BT_ADDR* bdaddr);

#endif
#if APP_SUPPORT_TWS == 1
int app_bt_connect_tws(BT_ADDR* bdaddr);

int app_bt_tws_send_data(U8 *data,U16 len);

int app_bt_tws_sync_control(BOOL on);

int app_bt_tws_mss_control(void);

int app_bt_tws_stop_local_sync_control(void);

int app_bt_tws_reset(void);

int app_bt_tws_disc(void);

int app_bt_tws_visible_reopen(void);
#endif
int app_bt_send_wearing_state(   uint32_t state);

int app_bt_send_key(   uint32_t Key);

int app_bt_send_audio_sync_param(U32 synclk,U32 counternum,U32 samplerate,U32 bt_counter,U32 bt_counter_offset,U32 strb_cycle_offset);

int app_bt_send_bt_audio_restart(void);

int app_bt_send_bt_audio_mode_replay(uint32_t mode);

int app_bt_generate_key_complete(void);

int app_bt_set_lp_level(uint8_t level);
#if FPGA == 0
int app_bt_erased_flash(void);
#endif
int app_bt_dut_mode(void);
int app_bt_wr_scan_en(unsigned int scan_en,unsigned int dut);
int app_bt_non_signaling_test_mode(void);
int app_bt_inquiry_dev(unsigned int len,unsigned int maxResp);
int app_bt_inquiry_cancel(void);
#if APP_SUPPORT_OTA_BOX
int app_bt_ota_connect(BT_ADDR *bdaddr);
int app_bt_ota_connect_by_id(uint32_t id);
int app_bt_ota_send_data(uint32_t num);
#endif
int app_bt_change_local_name(   char * name,uint8_t len);
#if MAX_THROUGHPUT_TEST == 1
int app_bt_spp_throughput_start(void);
#endif
#endif /* __APP_BT_FUNC_H__ */

