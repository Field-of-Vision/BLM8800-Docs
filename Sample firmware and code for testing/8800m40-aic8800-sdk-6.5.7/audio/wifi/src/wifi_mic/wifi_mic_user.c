/*
 * In this file, we provide some implementations of user api, user can modify them according to needs.
 *
 * 1.Transmit user defined cmds between Dongle and Headset
 * see wifi_voice_send_user_cmd, mic_rx_user_cmd_handler, mic_tx_user_cmd_handler.
 *
 * 2.Handle audio/voice data transmitted between Dongle and Headset
 * see mic_rx_user_data_handler, mic_tx_user_data_handler.
 *
 * 3.key
 * See wifi_voice_user_key_init, in this function, we register two keys, GPIOB1 for key_volume_up, GPIOB3 for key_volume_down.
 * when these keys were pressed, a user msg(WIFI_MIC_USER_MSG_KEY) will be sent to user_task,
 * user_task call wifi_voice_user_key_handler to handle key msg.
 *
 * 4.volume control
 * we show you how to control volume up/down for playback/capture
 * see wifi_voice_user_playback_volume_up, wifi_voice_user_playback_volume_down,
 * wifi_voice_user_capture_volume_up, wifi_voice_user_capture_volume_down
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "rtos.h"
#include "wifi_voice.h"
#include "wifi_mic_user.h"
#include "wifi_mic_tx.h"
#include "wifi_mic_rx.h"
#include "dbg.h"
#include "audio_proc_api.h"
#if PLF_KEY_MODULE
#include "key.h"
#include "co_message.h"
#endif
#include "gpio_api.h"
#if PLF_PMIC
#include "pmic_api.h"
#endif
#if PLF_LED_MODULE
#include "led.h"
#endif
#include "reg_sysctrl.h"
#include "sysctrl_api.h"
#include "flash_api_wifi.h"

// set to 1 to use default user key config, GPIOB2 for volume up, GPIOB3 for volume down
#define USE_DEFAULT_USER_KEY_CONFIG    1

#define USER_CMD_NULL    0x00

// set playback volume rage, max +23.5dB, min -25.5dB, step must be multiple of 0.5dB
#define MIC_TX_PLAYBACK_MAX_VOL_DB     (14)
#define MIC_TX_PLAYBACK_MIN_VOL_DB     (-14)
#define MIC_TX_PLAYBACK_VOL_STEP_DB    (2)
static float mic_tx_playback_vol_db = 0;

// set capture volume rage, max +16dB, min -12dB, step must be multiple of 2dB
#define MIC_TX_CAPTURE_MAX_VOL_DB     (16)
#define MIC_TX_CAPTURE_MIN_VOL_DB     (-12)
#define MIC_TX_CAPTURE_VOL_STEP_DB    (2)
static int mic_tx_capture_vol_db = 0;

#define USER_MSG_QUEUE_ELT_NB    10
static rtos_queue user_msg_queue = NULL;
static rtos_task_handle user_task_handle = NULL;

/*
 * User cmd is consist of 2 bytes sync words and user cmd body
 * the max size of user cmd body is defined by USER_CMD_MAX_SIZE in wifi_voice_config.c
 * here is an implementation with cmd body of 1 byte
 */
void wifi_mic_send_user_cmd(uint8_t cmd)
{
    uint8_t user_cmd[WIFI_VOICE_CMD_SYNC_WORD_SIZE + 1];
    user_cmd[0] = WIFI_VOICE_USER_CMD_SYNC_WORD;
    user_cmd[1] = WIFI_VOICE_USER_CMD_SYNC_WORD;
    user_cmd[2] = cmd;
    wifi_voice_send_cmd(&user_cmd[0], sizeof(user_cmd));
}

/*
 * Used by dongle to handle user defined cmds from headset
 * sync words were removed by system api before this function is called
 */
void mic_rx_user_cmd_handler(uint8_t * data, uint32_t size, uint8_t index)
{
    if (data[0] == USER_CMD_NULL) {
        dbg("USER_CMD_NULL received\n");
    }
}

/*
 * Used by headset to handle user defined cmds from dongle
 * sync words were removed by system api before this function is called
 */
void mic_tx_user_cmd_handler(uint8_t * data, uint32_t size, uint8_t index)
{
    if (data[0] == USER_CMD_NULL) {
        dbg("USER_CMD_NULL received\n");
    }
}

/*
 * Used by dongle to handle data from headset before they were handled by system api
 * Note: these data are NOT user defined
 */
void mic_rx_user_data_handler(uint8_t * data, uint32_t size, uint8_t index)
{
}

/*
 * Used by headset to handle data from dongle before they were handled by system api
 * Note: these data are NOT user defined
 */
void mic_tx_user_data_handler(uint8_t * data, uint32_t size, uint8_t index)
{
}

/*
 * Used by dongle to mix data from multi headsets before they were transmitted to USB
 * Note: source data should get from 'mic_rx_user_data_handler'
 * - input:  size
 * - output: data
 */
void mic_rx_user_mix_handler(uint8_t *input[], uint32_t track_num, uint32_t ch_num, uint32_t size, uint8_t *output)
{
}

int wifi_mic_user_msg_send(wifi_mic_user_msg_t msg, int timeout, bool isr)
{
    int res = 0;

    res =  rtos_queue_write(user_msg_queue, &msg, timeout, isr);
    if (res != 0) {
        dbg("ERR: user msg:0x%X write fail\n", msg.msg_id);
    }

    return res;
}

int wifi_mic_user_msg_recv(wifi_mic_user_msg_t *msg, int timeout, bool isr)
{
    return rtos_queue_read(user_msg_queue, msg, timeout, isr);
}

int wifi_mic_tx_user_key_notify(uint32_t key_id)
{
    int res;

    wifi_mic_user_msg_t msg;
    msg.msg_id = WIFI_MIC_USER_MSG_KEY;
    msg.key_id = key_id;
    res = wifi_mic_user_msg_send(msg, 20, false);

    return res;
}

bool wifi_mic_tx_user_playback_volume_up(float step_db)
{
    bool max_vol = false;

    mic_tx_playback_vol_db += step_db;
    if (mic_tx_playback_vol_db >= (float)MIC_TX_PLAYBACK_MAX_VOL_DB) {
        mic_tx_playback_vol_db = MIC_TX_PLAYBACK_MAX_VOL_DB;
        max_vol = true;
    }
    uint8_t vol = audio_proc_dac_volume_convert_db_to_reg(mic_tx_playback_vol_db);
    audio_proc_dac_volume_set(vol);

    dbg("playback vol:%ddB %X\n", (int)mic_tx_playback_vol_db, vol);

    return max_vol;
}

bool wifi_mic_tx_user_playback_volume_down(float step_db)
{
    bool min_vol = false;

    mic_tx_playback_vol_db -= step_db;
    if (mic_tx_playback_vol_db <= (float)MIC_TX_PLAYBACK_MIN_VOL_DB) {
        mic_tx_playback_vol_db = MIC_TX_PLAYBACK_MIN_VOL_DB;
        min_vol = true;
    }
    uint8_t vol = audio_proc_dac_volume_convert_db_to_reg(mic_tx_playback_vol_db);
    audio_proc_dac_volume_set(vol);

    dbg("playback vol:%ddB %X\n", (int)mic_tx_playback_vol_db, vol);

    return min_vol;
}

bool wifi_mic_tx_user_capture_volume_up(int8_t step_db)
{
    bool max_vol = false;

    mic_tx_capture_vol_db += step_db;
    if (mic_tx_capture_vol_db >= MIC_TX_CAPTURE_MAX_VOL_DB) {
        mic_tx_capture_vol_db = MIC_TX_CAPTURE_MAX_VOL_DB;
        max_vol = true;
    }
    uint8_t vol = audio_proc_adc_volume_convert_db_to_reg(mic_tx_capture_vol_db);
    audio_proc_adc_volume_set(vol);

    return max_vol;
}

bool wifi_mic_tx_user_capture_volume_down(int8_t step_db)
{
    bool min_vol = false;

    mic_tx_capture_vol_db -= step_db;
    if (mic_tx_capture_vol_db <= MIC_TX_CAPTURE_MIN_VOL_DB) {
        mic_tx_capture_vol_db = MIC_TX_CAPTURE_MIN_VOL_DB;
        min_vol = true;
    }
    uint8_t vol = audio_proc_adc_volume_convert_db_to_reg(mic_tx_capture_vol_db);
    audio_proc_adc_volume_set(vol);

    return min_vol;
}

void wifi_mic_user_pairing(void)
{
    // clear sta ssid/pw & reboot
    flash_wifi_info_remove_ssidpw();

    wifi_mic_tx_force_pairing();
}

#if PLF_KEY_MODULE
void wifi_mic_tx_user_key_handler(uint32_t key_id)
{
    switch (KEY_NAME_GET(key_id)) {
        case APP_KEY_VOLADD:
            dbg("playback volume up\n");
            wifi_mic_tx_user_playback_volume_up(MIC_TX_PLAYBACK_VOL_STEP_DB);
            break;
        case APP_KEY_VOLSUB:
            dbg("playback volume down\n");
            wifi_mic_tx_user_playback_volume_down(MIC_TX_PLAYBACK_VOL_STEP_DB);
            break;
        case APP_KEY_POWER:
            {
                switch (KEY_FUNC_GET(key_id)) {
                    case APP_KEY_PRESS:
                        //do some thing.like play/pause/disconnect.
                        break;
                    case APP_KEY_DOUBLE_CLICK:
                        dbg("power key double click\r\n");
                        wifi_mic_user_pairing();
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}

void wifi_mic_tx_user_key_init(void)
{
#if USE_DEFAULT_USER_KEY_CONFIG
    // set GPIOB1 as key volume up, set GPIOB3 as key volume down
    uint32_t key_bond_id[][6] = {
        {PIN_PWR , APP_KEY_POWER  , KEY_MAX_HOLD_TYPE , KEY_MAX_CLICK_NUM , DEFAULT_PIN_PULL_DOWN , HW_FILTER},
        {PA_10   , APP_KEY_VOLADD , APP_KEY_PRESS     , KEY_MAX_CLICK_1   , DEFAULT_PIN_PULL_UP   , SFT_FILTER},
        {PA_11   , APP_KEY_VOLSUB , APP_KEY_PRESS     , KEY_MAX_CLICK_1   , DEFAULT_PIN_PULL_UP   , SFT_FILTER},
    };

    // if no external pullup exists, use this code to enable internal pullup, otherwise do not use this code
    // if low level when key pressed, set key_down_value to 0
    // if high level when key pressed, set key_down_value to 1
    key_set_key_config(wifi_mic_tx_user_key_notify,key_bond_id,(sizeof(key_bond_id)/KEY_REG_LIST_ONE_NUM_SIZE));
#endif
}
#endif

#if PLF_LED_MODULE
void mic_tx_user_led_handler(wifi_voice_st_e status)
{
    switch (status) {
    case WIFI_VOICE_STA_DISCONNECTED:
        led_set_pattern(LED_WIFI_IDLE);
        break;
    case WIFI_VOICE_STA_CONNECTED:
        led_set_pattern(LED_WIFI_CONNECT);
        break;
    case WIFI_VOICE_STA_PAIRING:
        led_set_pattern(LED_WIFI_PARING);
        break;
    default:
        break;
    }
}

void wifi_mic_tx_user_led_init(void)
{
    #if 1
    led_register_gpio_pin(PA_12,LED_BULE);
    led_register_gpio_pin(PA_13,LED_RED);
    #else
    #if PLF_PMIC_VER_LITE
        led_register_gpio_pin(PB_3,LED_BULE);
        led_register_gpio_pin(PB_4,LED_RED);
    #endif
    #if PLF_PMIC_VER_AUD
        led_register_gpio_pin(PB_6,LED_BULE);
        led_register_gpio_pin(PB_7,LED_RED);
    #endif
    #endif

    if (pwrctrl_pwrmd_cpusys_sw_record_getf() >= CPU_SYS_POWER_DOWN) {
        led_set_pattern(LED_WIFI_IDLE);
    }
}
#endif

static RTOS_TASK_FCT(mic_tx_user_task)
{
    wifi_mic_user_msg_t msg;
    while (1) {
        wifi_mic_user_msg_recv(&msg, -1, false);
        switch (msg.msg_id) {
        case WIFI_MIC_USER_MSG_KEY:
            #if PLF_KEY_MODULE
            wifi_mic_tx_user_key_handler(msg.key_id);
            #endif
            break;
        default:
            break;
        }
    }
}

int wifi_mic_tx_user_task_init(void)
{
    if (rtos_queue_create(sizeof(wifi_mic_user_msg_t), USER_MSG_QUEUE_ELT_NB, &user_msg_queue)) {
        dbg("ERR: wifi_mic_user_msg_queue create fail\n");
        return -1;
    }

    if (rtos_task_create(mic_tx_user_task, "user task", WIFI_USER_TASK,
                         TASK_STACK_SIZE_WIFI_USER, NULL, TASK_PRIORITY_WIFI_USER, &user_task_handle)) {

        dbg("ERR: user task create fail\n");
        return -1;
    }

    return 0;
}

void wifi_mic_tx_user_task_deinit(void)
{
    if (user_task_handle) {
        rtos_task_delete(user_task_handle);
        user_task_handle = NULL;
    }

    if (user_msg_queue) {
        rtos_queue_delete(user_msg_queue);
        user_msg_queue = NULL;
    }
}

int wifi_mic_rx_user_init(void)
{
    wifi_voice_user_cmd_handler_register(mic_rx_user_cmd_handler);
    wifi_voice_user_data_handler_register(mic_rx_user_data_handler);

    // mix handler, use default algorithm if you do not register it
    //wifi_mic_rx_mix_handler_register(mic_rx_user_mix_handler);

    return 0;
}

int wifi_mic_tx_user_init(void)
{
    wifi_voice_user_cmd_handler_register(mic_tx_user_cmd_handler);
    wifi_voice_user_data_handler_register(mic_tx_user_data_handler);
    wifi_mic_tx_user_task_init();
#if PLF_KEY_MODULE
    wifi_mic_tx_user_key_init();
#endif
#if PLF_LED_MODULE
    wifi_mic_tx_user_led_init();
    wifi_mic_tx_led_handler_register(mic_tx_user_led_handler);
#endif

    return 0;
}

int wifi_mic_rx_user_deinit(void)
{
    wifi_voice_user_cmd_handler_register(NULL);
    wifi_voice_user_data_handler_register(NULL);

    return 0;
}

int wifi_mic_tx_user_deinit(void)
{
    wifi_voice_user_cmd_handler_register(NULL);
    wifi_voice_user_data_handler_register(NULL);
    wifi_mic_tx_user_task_deinit();

    return 0;
}

