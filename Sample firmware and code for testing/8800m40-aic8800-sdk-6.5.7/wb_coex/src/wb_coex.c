/* create @20200301 by aic*/
#include "plf.h"
#include "wb_coex.h"

#if PLF_WIFI_STACK
extern void wb_coex_open(void);
#endif
static struct coex_controller g_coex_controller;

int wb_coex_wifi_on_get(void)
{
    return g_coex_controller.wifi_on;
}

void wb_coex_wifi_on_set(int on)
{
    g_coex_controller.wifi_on = (uint8_t)on;
}

int wb_coex_bt_on_get(void)
{
    return g_coex_controller.bt_on;
}

void wb_coex_bt_on_set(int on)
{
    g_coex_controller.bt_on = (uint8_t)on;
}

int wb_coex_wifi_connected_get(void)
{
    return g_coex_controller.wifi_connected;
}

void wb_coex_wifi_connected_set(int connected)
{
    g_coex_controller.wifi_connected = (uint8_t)connected;
}

int wb_coex_bt_connected_get(void)
{
    return g_coex_controller.bt_connected;
}

void wb_coex_bt_connected_set(int connected)
{
    g_coex_controller.bt_connected = (uint8_t)connected;
}

int wb_coex_bt_a2dp_on_get(void)
{
    return g_coex_controller.a2dp_on;
}

void wb_coex_bt_a2dp_on_set(int on)
{
    g_coex_controller.a2dp_on = (uint8_t)on;
}

int wb_coex_bt_sco_on_get(void)
{
    return g_coex_controller.sco_on;
}

void wb_coex_bt_sco_on_set(int on)
{
    g_coex_controller.sco_on = (uint8_t)on;
}

void wb_coex_check_status(void)
{
    int wifi_support = 0;
    int bt_support = 0;

    #if PLF_WIFI_STACK
    wifi_support = 1;
    #endif
    #if PLF_BT_STACK
    bt_support = 1;
    #endif
    if(wifi_support && bt_support){
        if(wb_coex_wifi_on_get() && wb_coex_bt_on_get()){
            #if PLF_WIFI_STACK
                wb_coex_open();
            #endif
        }
    }
}

