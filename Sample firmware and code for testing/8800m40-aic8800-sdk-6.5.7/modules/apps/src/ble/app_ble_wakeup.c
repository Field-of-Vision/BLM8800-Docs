#include "tgt_cfg_bt.h"
#if PLF_BT_STACK == 1
#if PLF_BLE_ONLY == 1 && PLF_BLE_WAKEUP == 1
#include <string.h>
#include "rtos.h"
#include "ble_task_msg.h"
#include "app_ble_only.h"
#include "co_main.h"
#include "app_ble_queue.h"
#include "gpio_api.h"
#include "pmic_api.h"
#include "ble_task_msg.h"
#include "app_ble_wakeup.h"

#define BLE_WAKEUP_GPIO                 2
#define CONFIG_DEFAULT_PULLED_UP        0


ble_wakeup_param_t * ble_wakeup_input_param = (ble_wakeup_param_t *)(BLE_WAKEUP_INPUT_PARAM_ADDR);
ble_wakeup_param_t ble_wakeup_user = {
    .delay_scan_to = 1000,
    .reboot_to = 1000,
};
co_timer *ble_wakeup_timer = NULL;
uint8_t ble_combo_num[MAX_ROLE_COMBO_IDX_NUM] = {0,};
static co_timer *scan_start_timer = NULL;

static void app_ble_scan_start_timer(void *cb_param)
{
    app_ble_scan_msg_start();
}

void app_ble_delay_scan_start(void)
{
    uint32_t delay_time = ble_wakeup_user.delay_scan_to;
    dbg("%s, time %d\n",__func__,delay_time);
    if(scan_start_timer == NULL){
        co_timer_start(&scan_start_timer,delay_time,NULL,app_ble_scan_start_timer,0);
    }
}

ble_wakeup_param_t *app_ble_wakeup_get_param(void)
{
    return &ble_wakeup_user;
}

void app_ble_wakeup_notify(uint8_t gpio_num_idx)
{
    CO_MODUAL_EVENT msg;
    int res = 0;
    msg.mod_id = CO_MODUAL_BLE_WAKEUP;
    msg.mod_evt.EvtId = gpio_num_idx;
    res = co_event_send(&msg, false);
    ASSERT_ERR(res == 0 || res == 1);
}


static void app_ble_wakeup_timer(void *cb_param)
{
    int func = (int)cb_param;
    if (func == 1) { // start recv adv
        
    } else if (func == 2) {
        dbg("exec reboot!\n");
        pmic_chip_reboot(100); // reboot
    } else {
        dbg("wrong func\r\n");
    }
}

static void app_ble_trigger_gpio_by_idx(uint8_t gpio_num_idx)
{
    if(gpio_num_idx & TG_IDX_0){
        switch(ble_wakeup_input_param->gpio_dft_lvl[0]){
            case 0:
                gpiob_set(ble_wakeup_user.gpio_num[0]); // high after trigger
                dbg("wakeup matched, set gpio %d\r\n",ble_wakeup_user.gpio_num[0]);
                break;
            case 1:
                gpiob_clr(ble_wakeup_user.gpio_num[0]); // high after trigger
                dbg("wakeup matched, clr gpio %d\r\n",ble_wakeup_user.gpio_num[0]);
                break;
            default:
                dbg("gpio_dft_lvl error\n");
                break;
        }
    }
    if(gpio_num_idx & TG_IDX_1){
        switch(ble_wakeup_input_param->gpio_dft_lvl[1]){
            case 0:
                gpiob_set(ble_wakeup_user.gpio_num[1]); // high after trigger
                dbg("wakeup matched, set gpio %d\r\n",ble_wakeup_user.gpio_num[1]);
                break;
            case 1:
                gpiob_clr(ble_wakeup_user.gpio_num[1]); // high after trigger
                dbg("wakeup matched, clr gpio %d\r\n",ble_wakeup_user.gpio_num[1]);
                break;
            default:
                dbg("gpio_dft_lvl error\n");
                break;
        }
    }
}

static bool app_ble_wakeup_handle_process(CO_EVENT *evt)
{
    uint8_t gpio_num_idx = (uint8_t)evt->EvtId;
    dbg("%s, gpio_num_idx %d\n",__func__,gpio_num_idx);
    app_ble_trigger_gpio_by_idx(gpio_num_idx);
    app_ble_scan_msg_stop();
    dbg("delay %dms & reboot\r\n", ble_wakeup_user.reboot_to);
    if (ble_wakeup_timer == NULL) {
        co_timer_start(&ble_wakeup_timer, ble_wakeup_user.reboot_to, (void *)2, app_ble_wakeup_timer, 0);
    }
    return true;
}

void app_ble_wakeup_init(void)
{
    dbg("%s ram_size = %d\n",__func__,sizeof(ble_wakeup_param_t));
    dbg("[%p]=%08X\n",&ble_wakeup_input_param->magic_num,ble_wakeup_input_param->magic_num);
    dbg("[%p]=%08X\n",&ble_wakeup_input_param->delay_scan_to,ble_wakeup_input_param->delay_scan_to);
    dbg("[%p]=%08X\n",&ble_wakeup_input_param->reboot_to,ble_wakeup_input_param->reboot_to);
    for(uint8_t i=0;i<MAX_GPIO_TRIGGER_NUM;i++){
        dbg("gpio_num idx[%d] [%p]=%x\n",i,&ble_wakeup_input_param->gpio_num[i],ble_wakeup_input_param->gpio_num[i]);
        dbg("gpio_dft_lvl idx[%d] [%p]=%x\n",i,&ble_wakeup_input_param->gpio_dft_lvl[i],ble_wakeup_input_param->gpio_dft_lvl[i]);
    }
    for(uint8_t i=0;i<BLE_AD_FILTER_NUM_MAX;i++){
        dbg("ad_data_mask [%p]=%08X\n",&ble_wakeup_input_param->ad_filter[i].ad_data_mask,ble_wakeup_input_param->ad_filter[i].ad_data_mask);
        dbg("gpio_trigger_idx [%p]=%x\n",&ble_wakeup_input_param->ad_filter[i].gpio_trigger_idx,ble_wakeup_input_param->ad_filter[i].gpio_trigger_idx);
        dbg("ad_role [%p]=%x\n",&ble_wakeup_input_param->ad_filter[i].ad_role,ble_wakeup_input_param->ad_filter[i].ad_role);
        dbg("ad_len [%p]=%x\n",&ble_wakeup_input_param->ad_filter[i].ad_len,ble_wakeup_input_param->ad_filter[i].ad_len);
        dbg("ad_type [%p]=%x\n",&ble_wakeup_input_param->ad_filter[i].ad_type,ble_wakeup_input_param->ad_filter[i].ad_type);
    }
    if (ble_wakeup_input_param->magic_num == BLE_WAKEUP_MAGIC_NUM) {
        ble_wakeup_user.magic_num = ble_wakeup_input_param->magic_num;
        ble_wakeup_user.delay_scan_to = ble_wakeup_input_param->delay_scan_to;
        ble_wakeup_user.reboot_to = ble_wakeup_input_param->reboot_to;
        for(uint8_t i=0;i<MAX_GPIO_TRIGGER_NUM;i++){
            if(ble_wakeup_input_param->gpio_num[i] != 0xff){
                ble_wakeup_user.gpio_num[i] = ble_wakeup_input_param->gpio_num[i];
            }
            if(ble_wakeup_input_param->gpio_dft_lvl[i] != 0xff){
                ble_wakeup_user.gpio_dft_lvl[i] = ble_wakeup_input_param->gpio_dft_lvl[i];
            }
        }

        for(uint8_t idx=0;idx<BLE_AD_FILTER_NUM_MAX;idx++){
            ble_wakeup_user.ad_filter[idx].ad_data_mask = ble_wakeup_input_param->ad_filter[idx].ad_data_mask;
            ble_wakeup_user.ad_filter[idx].gpio_trigger_idx = ble_wakeup_input_param->ad_filter[idx].gpio_trigger_idx;
            ble_wakeup_user.ad_filter[idx].ad_role = ble_wakeup_input_param->ad_filter[idx].ad_role;
            ble_wakeup_user.ad_filter[idx].ad_len = ble_wakeup_input_param->ad_filter[idx].ad_len;
            ble_wakeup_user.ad_filter[idx].ad_type = ble_wakeup_input_param->ad_filter[idx].ad_type;
            dbg("idx %d find valid ad_data:\n",idx);
            for (uint8_t i = 0; i < ble_wakeup_user.ad_filter[idx].ad_len-1; i++) {
                ble_wakeup_user.ad_filter[idx].ad_data[i] = ble_wakeup_input_param->ad_filter[idx].ad_data[i];
                dbg(" 0x%x ", ble_wakeup_user.ad_filter[idx].ad_data[i]);
            }
            dbg("\n");
            if(ble_wakeup_user.ad_filter[idx].ad_len >0 && ((ble_wakeup_user.ad_filter[idx].ad_role & AD_ROLE_FLAG) == ROLE_COMBO)){
                uint8_t trigger_idx = (ble_wakeup_user.ad_filter[idx].ad_role & ROLE_COMBO_IDX_FLAG)>>4;
                dbg("ad_role: %d, trigger_idx %d\n",ble_wakeup_user.ad_filter[idx].ad_role,trigger_idx);
                ble_combo_num[trigger_idx]++;
            }
        }
        for(uint8_t i=0;i<MAX_ROLE_COMBO_IDX_NUM;i++){
            dbg("ble_combo_num idx %d: %d\n", i,ble_combo_num[i]);
        }
        dbg("reboot timeout: %dms\n", ble_wakeup_user.reboot_to);
    } else {
        dbg("no filter ad_data set\n");
    }
    for(uint8_t i=0;i<MAX_GPIO_TRIGGER_NUM;i++){
        switch(ble_wakeup_input_param->gpio_dft_lvl[i]){
            case 0:
                gpiob_init(ble_wakeup_user.gpio_num[i]);
                gpiob_clr(ble_wakeup_user.gpio_num[i]); // low by default
                gpiob_dir_out(ble_wakeup_user.gpio_num[i]);
                gpiob_clr(ble_wakeup_user.gpio_num[i]); // low by default
                dbg("idx %d ,gpiob %d set\r\n",i,ble_wakeup_user.gpio_num[i]);
                break;
            case 1:
                gpiob_force_pull_up_enable(ble_wakeup_user.gpio_num[i]);
                gpiob_init(ble_wakeup_user.gpio_num[i]);
                gpiob_set(ble_wakeup_user.gpio_num[i]); // high by default
                gpiob_dir_out(ble_wakeup_user.gpio_num[i]);
                gpiob_set(ble_wakeup_user.gpio_num[i]); // high by default
                dbg("idx %d ,gpiob %d set\r\n",i,ble_wakeup_user.gpio_num[i]);
                break;
            default:
            #if 0
            #if CONFIG_DEFAULT_PULLED_UP == 1
                gpiob_force_pull_up_enable(BLE_WAKEUP_GPIO);
                gpiob_init(BLE_WAKEUP_GPIO);
                gpiob_set(BLE_WAKEUP_GPIO); // high by default
                gpiob_dir_out(BLE_WAKEUP_GPIO);
                gpiob_set(BLE_WAKEUP_GPIO); // high by default
            #else
                gpiob_init(BLE_WAKEUP_GPIO);
                gpiob_clr(BLE_WAKEUP_GPIO); // low by default
                gpiob_dir_out(BLE_WAKEUP_GPIO);
                gpiob_clr(BLE_WAKEUP_GPIO); // low by default
            #endif
                dbg("gpiob %d set\r\n",BLE_WAKEUP_GPIO);
            #endif
                dbg("idx %d no set\r\n",i);
                break;
        }
    }

    co_main_evt_handler_rigister(CO_MODUAL_BLE_WAKEUP,app_ble_wakeup_handle_process);
}

#endif//PLF_BLE_ONLY == 1 && PLF_BLE_WAKEUP == 1
#endif//PLF_BT_STACK == 1
