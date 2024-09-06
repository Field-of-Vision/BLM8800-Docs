#include "tgt_cfg_bt.h"

#if APP_SUPPORT_A2DP_SOURCE == 1
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "rtos.h"

#include "app_a2dp_source.h"
#include "aic_adp_api.h"
#include "app_bt_queue.h"

static uint8_t a2dp_test_sbc_packet[] = {
#include "a2dp_source_test.tab"
};
#define A2DP_TEST_SBC_4_FRAME_SIZE 308

TimerHandle_t app_bt_a2dp_source_send_sbcpacket_timer = NULL;

BT_ADDR default_device = {{0xa9,0xc0,0x00,0x88,0x88,0x33}};
void app_a2dp_source_connect_default_device(void)
{
        TRACE("APP:a2dp_source_connect\n");
        app_bt_source_connect_a2dp(&default_device);
}

void app_bt_source_send_a2dp_test_sbc_packet_time_handler( TimerHandle_t xTimer )
{
    app_bt_a2dp_send_data(&default_device);
}

void app_bt_source_send_a2dp_test_sbc_packet(BT_ADDR default_device )
{
    Status_BTDef status = BTDEF_ERROR;
    static uint32_t a2dp_send_sbc_counter = 0;
    static uint32_t a2dp_send_testsbc_data_offset = 0;

    
    a2dp_send_testsbc_data_offset = a2dp_send_sbc_counter * A2DP_TEST_SBC_4_FRAME_SIZE;
    if(a2dp_send_testsbc_data_offset > sizeof(a2dp_test_sbc_packet) - A2DP_TEST_SBC_4_FRAME_SIZE)
    {
        a2dp_send_testsbc_data_offset = 0;
        a2dp_send_sbc_counter = 0;
    }
    
    TRACE("a2dp_sbc_data offset = %d\n",a2dp_send_testsbc_data_offset);

    status = aic_adp_a2dp_send_sbc_data(default_device,(U8 *)a2dp_test_sbc_packet + a2dp_send_testsbc_data_offset,
                                        A2DP_TEST_SBC_4_FRAME_SIZE,4);

    if(status == BTDEF_NOT_DONE){
        TRACE("APP: a2dp send busy\n");
        app_a2dp_source_sbc_data_send_timer_begin();
    }
    else if(status == BTDEF_PENDING){
        a2dp_send_sbc_counter++;
    }
    else{
        TRACE("APP:a2dp send error,status:%d\n",status);
    }
}


void app_a2dp_source_start(void)
{
    TRACE("APP:a2dp_send_start\n");
    app_bt_a2dp_start(&default_device ,1);
}

void app_a2dp_source_suspend(void)
{
    TRACE("APP:a2dp_send_suspend\n");
    app_bt_a2dp_start(&default_device ,0);
}

void app_a2dp_create_source_sbc_data_send_timer(void)
{
    if(app_bt_a2dp_source_send_sbcpacket_timer == NULL)
        app_bt_a2dp_source_send_sbcpacket_timer = rtos_timer_create("A2dp_Source_Start_Timer",      \
                                                     10,      \
                                                     pdFALSE,\
                                                     NULL,\
                                                     app_bt_source_send_a2dp_test_sbc_packet_time_handler);
}

void app_a2dp_source_sbc_data_send_timer_begin(void)
{
    if(rtos_timer_change_period(app_bt_a2dp_source_send_sbcpacket_timer, 10, 0) == 0){

    }
}


void app_a2dp_source_init(void)
{
    app_a2dp_create_source_sbc_data_send_timer();
}

#endif
