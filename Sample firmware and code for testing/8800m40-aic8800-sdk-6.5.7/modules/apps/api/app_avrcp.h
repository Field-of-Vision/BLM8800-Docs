#ifndef _APP_AVRCP_H_
#define _APP_AVRCP_H_
#if APP_SUPPORT_AVRCP == 1
void app_set_avrcp_volume(BT_ADDR *bdaddr,S8 volume);
S8 app_get_avrcp_volume(BT_ADDR *bdaddr);
BOOL app_avrcp_key_handle(uint32_t key);
void app_avrcp_msg_handle(AIC_EVENT *event);
#endif
#endif
