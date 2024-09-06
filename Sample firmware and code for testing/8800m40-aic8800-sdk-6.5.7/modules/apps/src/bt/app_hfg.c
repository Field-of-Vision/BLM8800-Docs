#include "tgt_cfg_bt.h"

#if APP_SUPPORT_HFG
#include "rtos.h"
#include "aic_adp_api.h"
#include "app_bt_queue.h"

BT_ADDR test_device = {{0xaa,0xc0,0x00,0x88,0x88,0x33}};
void app_hfg_set_def_device(BT_ADDR bd_device)
{
    test_device = bd_device;
}

void app_hfg_connect_def_device(void)
{
    TRACE("APP:app_hfg_connect_def_device\n");
    app_bt_connect_hfg(&test_device);
}

void app_hfg_connect_sco(void)
{
    TRACE("APP:app_hfg_connect_sco\n");
    app_bt_hfp_connect_sco(&test_device);
}

void app_hfg_disconnect_sco(void)
{
    TRACE("APP:app_hfg_disconnect_sco\n");
    app_bt_hfp_disconnect_sco(&test_device);
}
#endif
