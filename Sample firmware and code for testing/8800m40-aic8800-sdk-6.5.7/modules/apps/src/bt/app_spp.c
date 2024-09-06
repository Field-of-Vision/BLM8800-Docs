#include "tgt_cfg_bt.h"
#if APP_SUPPORT_SPP == 1
#include "aic_adp_api.h"
#include "rtos.h"
#include "app_spp.h"
#include "app_test.h"
#include "app_bt.h"

static app_spp_tx_done_t app_spp_tx_done_func = NULL;
#if MAX_THROUGHPUT_TEST == 1
uint32_t first_time = 0;
uint32_t send_count = 0;
uint8_t spp_test_buffer[663] = {0x1,};

void app_spp_send_test_data(uint8_t index)
{
    //TRACE("APP:spp_send_test_data\n");
    app_spp_send_data(index, spp_test_buffer, 663);
}

void app_spp_connect_test(void)
{
    BT_ADDR temp_bdaddr1 = {0xa1,0xc0,0x00,0x45,0x56,0x67};
    BT_ADDR temp_bdaddr2 = {0xa2,0xc0,0x00,0x45,0x56,0x67};
    //0x77,0xEE,0xAE,0x77,0xAE,0xAE
    //0xAE,0xAE,0x77,0xAE,0xEE,0x77
    // app_spp_connect(0, &temp_bdaddr1);
}

#endif


void app_spp_send_data(uint8_t index, uint8_t* ptrData, uint16_t length)
{
    aic_adp_spp_send_data(index, ptrData, length);
}


void app_spp_register_tx_done(app_spp_tx_done_t callback)
{
    TRACE("APP:register tx done cb = 0x%x\n",callback);
    app_spp_tx_done_func = callback;
#if MAX_THROUGHPUT_TEST == 1
    if(app_spp_tx_done_func){
        first_time = rtos_now(false);
        send_count = 0;
    }
#endif
}

void app_spp_init(void)
{
    TRACE("APP:app_spp_init\n");
    aic_adp_spp_set_initial_rx_credit(1);
#if MAX_THROUGHPUT_TEST == 1
    app_spp_register_tx_done(app_spp_send_test_data);
#endif
}

void app_spp_connect(uint8_t index, BT_ADDR * bdaddr)
{
    TRACE("APP:app_spp_connect %d\n",index);
    aic_adp_spp_connect(index, bdaddr);
}

void app_spp_msg_handle(AIC_EVENT *event)
{
    AIC_ADP_SPP_EVENT *aic_spp_msg = (AIC_ADP_SPP_EVENT *)event->Param;
    uint8_t conidx = aic_spp_msg->conidx;
    U32 sppparam = aic_spp_msg->sppparam[conidx];

    switch(event->EventId){
        case AIC_ADP_SPP_CONNECTED_IND:
            if(sppparam == 0){
                TRACE("APP:spp connect ind %d\n",conidx);
#if MAX_THROUGHPUT_TEST == 1
                app_spp_send_test_data(conidx);
#endif
            }
        break;
        case AIC_ADP_SPP_CONNECTED_CNF:
            if(sppparam == 0){
                TRACE("APP:spp connect cnf %d\n",conidx);
#if MAX_THROUGHPUT_TEST == 1 && TEST_MODE_ROLE_SEND == 1
                app_spp_send_test_data(conidx);
#endif
#if SCO_CVSD_PLC_TEST == 1 && TEST_MODE_ROLE_SEND == 1
                app_test_connect_sco(NULL);
#endif
            }else{
            
            }
        break;
        case AIC_ADP_SPP_DISCONNECTED:
            TRACE("APP:spp disconnected %d reason = %d",conidx, sppparam);
            if(sppparam == 0){
                //   app_spp_tx_done_func = NULL;
            }else{
            
            }
        break;
        case AIC_ADP_SPP_DATA_SENT:
            {
#if MAX_THROUGHPUT_TEST == 1
                send_count++;
                if(send_count%100){
                    uint32_t time = rtos_now(false);
                    uint32_t spp_speed;
                    spp_speed = (send_count * 663 * 1000)/(time - first_time);
                    TRACE("SPP speed is %d Byte/s\n",spp_speed);
                }
#endif
                //adpspptxdone *tx_done = (adpspptxdone *)sppparam;
                if(app_spp_tx_done_func)
                {
                    app_spp_tx_done_func(conidx);
                }
            }
        break;
        case AIC_ADP_SPP_DATA_IND:
            {
                adpspprxdone *rx_done = (adpspprxdone *)sppparam;
                aic_adp_spp_given_the_credit(conidx, 1);
                if(*rx_done->pRxBuf != 0)
                {
                    TRACE("APP:spp_receive_data %d len = %d\n",conidx, rx_done->RxDataLength);
                    TRACE("  data: ");
                    for (int i=0;i<rx_done->RxDataLength;i++) {
                        TRACE("%02x ", rx_done->pRxBuf[i]);
                    }
                    TRACE("\n");
                    //TRACE("data :%x,%x,%x,%x,%x,%x\n",rx_done->pRxBuf[0],rx_done->pRxBuf[1],rx_done->pRxBuf[2],\
                        //rx_done->pRxBuf[3],rx_done->pRxBuf[4],rx_done->pRxBuf[5]);
                }
            }
        break;
        default:
        break;
    }
}

#endif
