
#ifndef _FHOST_COMMAND_COMMON_H_
#define _FHOST_COMMAND_COMMON_H_

/// Network Command result
enum fhost_network_res {
    FHOST_NW_SUCCESS,
    FHOST_NW_ERROR,
    FHOST_NW_UNKWN_CMD,
    FHOST_NW_NO_RESP,
};

extern uint8_t fhost_vif_idx;

int do_sleep_level(int argc, char * const argv[]);
int do_user_wakeup_source(int argc, char * const argv[]);
int do_user_sleep(int argc, char * const argv[]);
int do_restore(int argc, char * const argv[]);
int do_show_heap(int argc, char * const argv[]);
#if (configUSE_TRACE_FACILITY == 1)
int do_show_task(int argc, char * const argv[]);
#endif
int do_set_power(int argc, char * const argv[]);
int do_mac(int argc, char * const argv[]);
int do_blink_magic(int argc, char * const argv[]);
int do_auto_connect (int argc, char * const argv[]);
int do_connect (int argc, char * const argv[]);
int do_connect_cb(int argc, char * const argv[]);
int do_auto_reconnect(int argc, char * const argv[]);
int do_disconnect (int argc, char * const argv[]);
int do_create_ap (int argc, char * const argv[]);
int do_start_ap (int argc, char * const argv[]);
int do_stop_ap (int argc, char * const argv[]);
int do_ap_associated_sta_info(int argc, char * const argv[]);
int do_smartconf(int argc, char * const argv[]);
int do_stop_smartconf(int argc, char * const argv[]);
#ifdef CFG_WPS
int do_wps_pbc (int argc, char * const argv[]);
#endif /* CFG_WPS */
#if defined(CFG_P2P)
int do_start_p2p(int argc, char * const argv[]);
#endif


int fhost_console_ping(char *params);
#if PLF_IPERF
extern rtos_task_handle iperf_task_handle;
int fhost_console_iperf(char *params);
#endif
char *fhost_nw_next_token(char **params);
int sta_auto_connect(void);
int fhost_nw_parse_ip4(char *str, uint32_t *ip, uint32_t *mask);

#endif /* _FHOST_COMMAND_COMMON_H_ */
