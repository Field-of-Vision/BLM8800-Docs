/**
 ****************************************************************************************
 *
 * @file rtos.c
 *
 * @brief Entry point for WiFi stack integration within an RTOS.
 *
 ****************************************************************************************
 */
#include "rtos.h"
#include "dbg.h"
#include "plf.h"
#include "hw_cfg_api.h"

#if PLF_CONSOLE
#include "console_task.h"
#endif /* PLF_CONSOLE */

#if PLF_LETTER_SHELL
#include "shell_port.h"
#endif /* PLF_LETTER_SHELL */

#if PLF_MODULE_SOFTWDG
#include "softwdg.h"
#endif

#if PLF_ASIO
#include "asio.h"
#endif /* PLF_ASIO */

#if PLF_AUDIO
#include "app_audio.h"
#include "audio_eq.h"
#include "audio_drc.h"
#endif /* PLF_AUDIO */

#if PLF_TEST
#include "test_main.h"
#endif /* PLF_TEST */

#if PLF_BT_STACK
#if PLF_BLE_ONLY == 0
#include "bt_task.h"
#else
#include "ble_task.h"
#endif
#if PLF_AON_SUPPORT
#include "bt_aon_sram.h"
#endif
#endif /* PLF_BT_STACK */

#if PLF_WIFI_STACK
#ifdef CFG_HOSTIF
#include "hostif.h"
#endif
#ifdef CONFIG_RWNX_LWIP
#include "net_al.h"
#include "fhost.h"
#include "fhost_wpa.h"
#ifdef CFG_HOSTIF
#include "rwnx_defs.h"
struct rwnx_hw hw_env = {NULL,};
#endif /* CFG_HOSTIF */
#endif /* CONFIG_RWNX_LWIP */
#if !defined(CFG_HOSTIF) || defined(CFG_DEVICE_IPC)
#include "rwnx_defs.h"
struct rwnx_hw hw_env = {NULL,};
#endif
#endif /* PLF_WIFI_STACK */

#include "co_main.h"
#include "sysctrl_api.h"
#include "sleep_api.h"

#if PLF_DSP
#include "dsp_task.h"
#endif /* PLF_DSP */

#if PLF_MODULE_TEMP_COMP
#include "temp_comp.h"
#endif

#if PLF_PMIC && (!PLF_AIC8800)
#include "pmic_api.h"
#endif

static co_timer *blink_reboot_timer = NULL;

rtos_task_cfg_st get_task_cfg(uint8_t task_id)
{
    rtos_task_cfg_st cfg = {0, 0};

    switch (task_id) {
        case IPC_CNTRL_TASK:
            cfg.priority   = TASK_PRIORITY_WIFI_IPC;
            cfg.stack_size = TASK_STACK_SIZE_WIFI_IPC;
            break;
        case SUPPLICANT_TASK:
            cfg.priority   = TASK_PRIORITY_WIFI_WPA;
            cfg.stack_size = TASK_STACK_SIZE_WIFI_WPA;
            break;
        case CONTROL_TASK:
            cfg.priority   = TASK_PRIORITY_WIFI_CNTRL;
            cfg.stack_size = TASK_STACK_SIZE_WIFI_CNTRL;
            break;
        case APP_FHOST_TX_TASK:
            cfg.priority   = TASK_PRIORITY_WIFI_TX;
            cfg.stack_size = TASK_STACK_SIZE_WIFI_TX;
            break;
        case HOSTAPD_TASK:
            cfg.priority   = TASK_PRIORITY_WIFI_HOSTAPD;
            cfg.stack_size = TASK_STACK_SIZE_WIFI_HOSTAPD;
            break;
        default:
            break;
    }

    return cfg;
}

/**
 * Save user data that declared with PRIVATE_HOST_*(G3USER)
 */
__WEAK void user_data_save(void)
{
    // VOID
}

/**
 * Restore user data that declared with PRIVATE_HOST_*(G3USER)
 */
__WEAK void user_data_restore(void)
{
    // VOID
}

#ifndef CFG_WAPI
__WEAK void wapi_main(void)
{
    // VOID
}
__WEAK void wapi_eloop_register_read_sock(void)
{
    // VOID
}
int wapi_driver_rwnx_ops = 0;
#endif

int blink_checksum(unsigned char mac, unsigned char encrypt[6])
{	
	unsigned char temp = 0xff, data, n;	
	
	data = mac ^ 0x4c;	
	n = mac & 0x0f;
	n = n % 8;
	temp = ((data >> n) | (data << (8 - n))) & 0xFF;
	encrypt[0] = temp;
	
	return 1;
}

int check_blink_magic(void)
{
	uint8_t *mdata;
	uint8_t get_magic_num;
	unsigned char encrypt[6] = {0};

	get_magic_num = get_blink_magic();

	mdata = get_mac_address();
	blink_checksum(mdata[5], encrypt);

	if(get_magic_num == encrypt[0])
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void blink_timer_handler(void *cb_param)
{
    pmic_chip_reboot(0xF);
    return;
}

void rtos_main(void)
{
    dbg("Enter rtos_main\r\n");

    #if (PLF_HW_PXP == 1)
    dbg("RUNNING IN SIMULATION MODE\r\n");
    #endif

    #if DBG_MUTEX_ENABLED
    dbg_rtos_init();
    #endif

    #if PLF_WIFI_STACK
    #if defined(CONFIG_RWNX_LWIP)
    wifi_patch_prepare();
    rwnx_ipc_init(&hw_env, &ipc_shared_env);
    #endif /* CONFIG_RWNX_LWIP */
    #if defined(CFG_DEVICE_IPC)
    rwnx_ipc_init(&hw_env, &ipc_shared_env);
    #endif
    #endif /* PLF_WIFI_STACK */

    if (rtos_init())
    {
        ASSERT_ERR(0);
    }

    #if PLF_PMIC && (!PLF_AIC8800)
    pmic_boot_check();
    #endif /* PLF_PMIC && (!PLF_AIC8800) */

    #if (PLF_CONSOLE && !(PLF_WIFI_STACK && (defined(CFG_APP_CONSOLEWIFI) || defined(CFG_APP_UARTWIFI))))
    console_task_init();
    #endif /* PLF_CONSOLE && !PLF_WIFI_STACK */

    #if PLF_LETTER_SHELL
    userShellInit();
    #endif

    #if PLF_MODULE_SOFTWDG
    softwdg_task_init();
    #endif

    #if PLF_MODULE_TEMP_COMP
    temp_comp_init();
    temp_comp_start();
    #endif

    #if PLF_AUD_USED
    #if PLF_ASIO
    asio_init();
    #endif

    #if PLF_AUDIO
    app_audio_open((uint32_t)&__HeapLimit[0], (uint32_t)&__StackLimit[0]);
    audio_eq_init();
    audio_drc_init();
    #if PLF_CONSOLE
    audio_eq_cmd_init();
    audio_drc_cmd_init();
    #endif
    #endif
    #endif

    #if PLF_TEST
    test_task_init();
    #endif /* PLF_TEST */

    #if PLF_BT_STACK
    #if !(defined(CFG_TEST_AF) || defined(CFG_TEST_SBC) || defined(CFG_TEST_AAC) || defined(CFG_TEST_SDCARD_AUDIO) || defined(CFG_TEST_HCI))
    #if PLF_AON_SUPPORT
    host_aon_interface_init();
    #endif
    #if PLF_BLE_ONLY == 0
    bt_task_init();
    #else
    ble_task_init(INIT_NORMAL);
    #endif
    #if PLF_AON_SUPPORT
    cpup_ready_set(true);
    #endif
    #endif
    #endif /* PLF_BT_STACK */

    #ifdef CFG_HOSTIF
    init_host(0);
    #endif
    #if PLF_WIFI_STACK
    #ifdef CONFIG_RWNX_LWIP
    net_init();
    // Initialize the FHOST module
    fhost_init(NULL);
    #endif /* CONFIG_RWNX_LWIP */
    #endif /* PLF_WIFI_STACK */

    co_main_init();
    hw_cfg_init();

    #if (PLF_AIC8800)
    if (pwrctrl_pwrmd_cpusys_sw_record_getf() >= CPU_SYS_POWER_DOWN) {
        // restore data
        sleep_data_restore();
        #if PLF_WIFI_STACK
        #ifdef CONFIG_RWNX_LWIP
        aon_mailbox_restore();
        fhost_data_restore();
        lwip_data_restore();
        wpas_data_restore();
        #endif /* CONFIG_RWNX_LWIP */
        #endif /* PLF_WIFI_STACK */
        user_data_restore();
        sys_wakeup_indicate();
        #if PLF_BT_STACK
        #if PLF_BLE_ONLY
        ble_task_restore();
        #endif
        #endif
    }
    #endif

    #if PLF_DSP
    dsp_task_init();
    #endif

	if(check_blink_magic())
	{
		// Timer wakeup
	    if (blink_reboot_timer == NULL) 
		{
	        co_timer_start(&blink_reboot_timer, (120 * 1000), NULL, blink_timer_handler, 0);
	        blink_reboot_timer = NULL;
	    }
	}

    // Start the scheduler
    rtos_start_scheduler();

    // Should never reach here
    for( ;; );
}
