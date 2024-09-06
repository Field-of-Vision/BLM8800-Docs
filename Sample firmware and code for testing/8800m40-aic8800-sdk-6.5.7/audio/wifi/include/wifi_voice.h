#ifndef LWIP_TCP_VOICE_H
#define LWIP_TCP_VOICE_H

#include "fhost.h"
#include "rtos_al.h"
#if PLF_AUDIO
#include "app_media.h"
#endif
#include "socket.h"

#ifndef WIFI_VOICE_DATA_PORT
#define WIFI_VOICE_DATA_PORT         5001
#endif

#ifndef WIFI_VOICE_CMD_PORT
#define WIFI_VOICE_CMD_PORT          5002
#endif

/// Maximum number of voice streams
#define VOICE_MAX_STREAMS           3

enum {
    VOICE_CMD_START_CAPTURE = 0,
    VOICE_CMD_STOP_CAPTURE,
    VOICE_CMD_START_PLAYBACK,
    VOICE_CMD_STOP_PLAYBACK,
};

enum {
    WIFI_CLIENT_CONNECTED = 0,
    WIFI_CLIENT_DISCONNECTED,
    WIFI_CLIENT_ADD,
    WIFI_CLIENT_DECREASE,
    WIFI_MAC_CONNECTED,
    WIFI_MAC_DISCONNECTED,
    WIFI_SWITCH_CHANNEL,
    VOICE_SOCK_CONNECTED,
    VOICE_SOCK_DISCONNECTED,
    VOICE_USB_RECV_ITF_STOP,
    VOICE_USB_RECV_ITF_START,
    VOICE_USB_SEND_ITF_STOP,
    VOICE_USB_SEND_ITF_START,
    VOICE_START_PLAYBACK,
    VOICE_STOP_PLAYBACK,
    VOICE_START_CAPTURE,
    VOICE_STOP_CAPTURE,
    VOICE_DATA_READY,
};

#define WIFI_VOICE_CMD_SYNC_WORD_SIZE           2
#define WIFI_VOICE_SYS_CMD_SIZE                 4
#define WIFI_VOICE_SYS_CMD_SYNC_WORD            'S'
#define WIFI_VOICE_USER_CMD_SYNC_WORD           'U'


typedef enum {
    WIFI_VOICE_ROLE_NONE = 0,
    WIFI_VOICE_ROLE_DONGLE,
    WIFI_VOICE_ROLE_HEADSET,
} WIFI_VOICE_ROLE_T;

/// configuration
struct wifi_voice_settings
{
    /// Stream address
    uint32_t stream_addr;
    /// Data to send
    uint8_t  *data_addr;
    /// Data size
    uint32_t data_size;
    /// server port
    uint16_t port;
    /// server mode
    bool is_server;
    /// role
    uint8_t role;
    /// palyload size
    uint16_t pl_size;

    uint8_t bcn_int;
    uint8_t pkt_ms;

    #if LWIP_IPV4
    struct sockaddr_in    to;
    #endif
};

//PACK_STRUCT_BEGIN
struct rtp_hdr {
  PACK_STRUCT_FLD_8(u8_t  version);
  PACK_STRUCT_FLD_8(u8_t  payloadtype);
  PACK_STRUCT_FIELD(u16_t seqNum);
  PACK_STRUCT_FIELD(u32_t timestamp);
  PACK_STRUCT_FIELD(u32_t ssrc);
} PACK_STRUCT_STRUCT;


/// wifi voice stream related info
struct wifi_voice_stream_t
{
    /// State of stream thread (true for active, false for inactive)
    bool active;

    int strm_id;

    uint32_t packet_loss_cnt;
    /// settings
    struct wifi_voice_settings settings;
};

typedef enum {
    WIFI_VOICE_STA_DISCONNECTED,
    WIFI_VOICE_STA_PAIRING,
    WIFI_VOICE_STA_CONNECTED,
} wifi_voice_st_e;

typedef void (*wifi_voice_data_handler_t)(uint8_t *data, uint32_t size, uint8_t index);
typedef void (*wifi_voice_user_data_handler_t)(uint8_t *data, uint32_t size, uint8_t index);
typedef void (*wifi_voice_cmd_handler_t)(uint8_t *data, uint32_t size, uint8_t index);
typedef void (*wifi_voice_user_cmd_handler_t)(uint8_t *data, uint32_t size, uint8_t index);
typedef void (*wifi_voice_mix_handler_t)(uint8_t *input[], uint32_t track_num, uint32_t ch_num, uint32_t size, uint8_t *output);
typedef void (*wifi_voice_led_handler_t)(wifi_voice_st_e status);

#if LWIP_SOCKET && LWIP_IGMP
void wifi_voice_data_handler_register(wifi_voice_data_handler_t handler);
void wifi_voice_user_data_handler_register(wifi_voice_user_data_handler_t handler);
void wifi_voice_cmd_handler_register(wifi_voice_cmd_handler_t handler);
void wifi_voice_user_cmd_handler_register(wifi_voice_user_cmd_handler_t handler);
struct wifi_voice_stream_t * wifi_voice_find_free_stream(void);
void wifi_voice_stream_start(struct wifi_voice_settings *settings);
void wifi_voice_stream_stop(void);
void wifi_voice_stream_stop_by_id(int strm_id);
void wifi_voice_switch_channel(uint8_t band, bool isr);
#endif /* LWIP_SOCKET && LWIP_IGMP */
int wifi_voice_msg_queue_write(uint32_t msg, int timeout, bool isr);
int wifi_voice_msg_queue_read(uint32_t *msg, int timeout, bool isr);
int wifi_voice_msg_queue_cnt_get(void);
int wifi_voice_data_stop_check_timer_restart(uint32_t xTicksToWait, bool isr);
int wifi_voice_do_switch_channel(int timeout, bool isr);
int wifi_voice_sock_connected(int timeout, bool isr);
int wifi_voice_sock_disconnected(int timeout, bool isr);
int wifi_voice_client_decrease(int timeout, bool isr);
int wifi_voice_client_disconnected(int timeout, bool isr);
int wifi_voice_client_connected(int timeout, bool isr);
int wifi_voice_mac_disconnected(int timeout, bool isr);
int wifi_voice_mac_connected(int timeout, bool isr);
int wifi_voice_data_ready(int timeout, bool isr);
int wifi_voice_start_playback(int timeout, bool isr);
int wifi_voice_stop_playback(int timeout, bool isr);
int wifi_voice_start_capture(int timeout, bool isr);
int wifi_voice_stop_capture(int timeout, bool isr);
int wifi_voice_init(void);
int wifi_voice_deinit(void);
#if LWIP_IPV4
void client_send_voice_packets(uint8_t *data_addr, uint32_t data_size);
void server_send_voice_packets(struct wifi_voice_settings *settings, struct sockaddr_in* to);
void wifi_voice_send_sys_cmd(uint8_t cmd);
void wifi_voice_send_cmd(uint8_t *cmd, uint16_t size);
void server_send_voice_rtp_packets(struct wifi_voice_settings *settings, struct sockaddr_in* to);
void client_send_voice_rtp_packets(struct wifi_voice_settings *settings, struct sockaddr_in* to);
#endif
#endif /* LWIP_TCP_VOICE_H */
void wifi_voice_task_init(struct wifi_voice_settings *settings);
void wifi_voice_task_deinit(struct wifi_voice_settings *settings);

