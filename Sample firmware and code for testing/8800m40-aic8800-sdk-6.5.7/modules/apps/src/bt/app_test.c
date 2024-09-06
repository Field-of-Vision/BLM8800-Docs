#include "app_test.h"
#if SCO_CVSD_PLC_TEST == 1
#include "aic_adp_api.h"

#define VOICE_FREQ_100HZ 1

#if (VOICE_FREQ_100HZ)
static uint8_t test_sco_packet[] = {
#include "100Sin_1CH_8K_16BIT.tab"
};
#else
static uint8_t test_sco_packet[] = {
#include "1KSin_1CH_8K_16BIT.tab"
};
#endif
#include "app_spp.h"
#include "app_media.h"
ScoSendData_t testdata;

TimerHandle_t connect_sco_timer = NULL;
BT_ADDR temp_bdaddr = {{0xaa,0xc0,0x00,0x88,0x88,0x33}};
HF_SENDBUFF_T test_sendbuff;

void app_test_connect_sco( TimerHandle_t xTimer )
{
    aic_adp_test_connect_sco();
}

void app_test_send_1K_sco_data(U16 len)
{
    AIC_ADP_HFP_AUDIO_DATA sendaudiodata;
    static uint32_t send_sco_counter = 0;
    static uint32_t send_testsco_data_offset = 0;

#if (VOICE_FREQ_100HZ)
    static uint32_t offset = 0;
    static uint32_t total_len = sizeof(test_sco_packet);
    uint32_t len1 = 0;
    uint32_t len2 = 0;

    ASSERT_ERR(total_len > len);
    if ((offset + len) <= total_len) {
        memcpy(testdata.buffer, test_sco_packet+offset ,len);
        offset += len;
        if (offset == total_len) {
            offset = 0;
        }
    } else {
        len1 = total_len - offset;
        len2 = len - len1;
        memcpy(testdata.buffer, test_sco_packet+offset ,len1);
        offset = 0;
        memcpy(testdata.buffer + len1, test_sco_packet+offset ,len2);
        offset += len2;
    }
#else
    send_testsco_data_offset = send_sco_counter*len;
    if(send_testsco_data_offset > sizeof(test_sco_packet) - len){
        send_testsco_data_offset = 0;
        send_sco_counter = 0;
    }

    memcpy(testdata.buffer, test_sco_packet+send_testsco_data_offset ,len);
#endif
    testdata.len = len;
    sendaudiodata.data = testdata.buffer;
    sendaudiodata.len = testdata.len;
    TRACE("APP:test sco send data = 0x%x ,len = %d\n",sendaudiodata.data,sendaudiodata.len);
    aic_adp_test_send_sco_data(&sendaudiodata);
    send_sco_counter++;
}

void app_test_msg_handle(AIC_EVENT *event)
{
    AIC_ADP_TEST_EVENT *aic_test_msg = (AIC_ADP_TEST_EVENT *)event->Param;
    switch(event->EventId){
        case AIC_ADP_TEST_CONNECTED_CNF:
            TRACE("APP:test_connect_cnf status = %d\n",aic_test_msg->testparam);
#if APP_SUPPORT_SPP == 1
            app_spp_connect(&temp_bdaddr);
#endif
            break;
        case AIC_ADP_TEST_DISCONNECTED:
            TRACE("APP:test_disconnect status = %d\n",aic_test_msg->testparam);
            break;
        case AIC_ADP_TEST_SCO_CONNECT:
            {
                TRACE("APP:test_sco_connect status = %d\n",aic_test_msg->testparam);
#if SCO_LOOPBACK_TEST == 0
                MediaCommonStruct tmp;
                TRACE("APP:app_test_play.\n");
                memset((U8*)&tmp, 0, sizeof(MediaCommonStruct));
                tmp.p.voc_ctrl.scocodec = MEDIA_SCO_CODEC_CVSD;
                AppSend_Mode_MediaCommand(AUD_BT_SCO,MC_PLAY,&tmp);
#endif
            }
            break;
        case AIC_ADP_TEST_SCO_DISCONNECT:
            TRACE("APP:test_sco_disconnect status = %d\n",aic_test_msg->testparam);
            break;
        case AIC_ADP_TEST_SCO_DATA_SENT:
            TRACE("APP:test sco send ok\n");
            break;
        case AIC_ADP_TEST_SCO_DATA_IND:
            {
                AIC_ADP_HFP_AUDIO_DATA *audiodata = (AIC_ADP_HFP_AUDIO_DATA *)aic_test_msg->testparam;
                AIC_ADP_HFP_AUDIO_DATA sendaudiodata;

                TRACE("APP:sco data ind data = 0x%x ,len = %d\n",audiodata->data,audiodata->len);

                AppReceive_ScoData(audiodata->data ,audiodata->len);
#if SCO_LOOPBACK_TEST == 1
                memcpy(tmpdata.buffer, audiodata->data ,audiodata->len);
                tmpdata.len = audiodata->len;
                sendaudiodata.data = tmpdata.buffer;
                sendaudiodata.len = tmpdata.len;
                TRACE("APP:sco send data = 0x%x ,len = %d\n",sendaudiodata.data,sendaudiodata.len);
                if(sendaudiodata.len){
#if TEST_MODE_ROLE_SEND == 1
                    app_test_send_1K_sco_data(sendaudiodata.len);
#else
                    aic_adp_test_send_sco_data(&sendaudiodata);
#endif
                }
#else
                uint32_t idx = test_sendbuff.idx % HF_SENDBUFF_MEMPOOL_NUM;
                AppPrepareSend_ScoData(&test_sendbuff.mempool[idx].buffer[0], audiodata->len);
                test_sendbuff.mempool[idx].len = audiodata->len;
                sendaudiodata.data = test_sendbuff.mempool[idx].buffer;
                sendaudiodata.len = test_sendbuff.mempool[idx].len;
                TRACE("APP:sco send data = 0x%x ,len = %d\n",sendaudiodata.data,sendaudiodata.len);
                if(sendaudiodata.len){
#if TEST_MODE_ROLE_SEND == 1
                    app_test_send_1K_sco_data(sendaudiodata.len);
#else
                    aic_adp_test_send_sco_data(&sendaudiodata);
#endif
                }

                test_sendbuff.idx++;
#endif
            }
            break;
        default:
            break;
    }
}


void app_test_connect_device(BT_ADDR * bdaddr)
{
    TRACE("APP:test connect addr 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",bdaddr->addr[0],bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
    aic_adp_test_connect(bdaddr);
}
void app_test_connect_default(void)
{
    app_test_connect_device(&temp_bdaddr);
}

#endif
