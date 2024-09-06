/**
 ****************************************************************************************
 *
 * @file fhost_iperf.h
 *
 * @brief Definitions of the fully hosted Iperf task.
 *
 * Copyright (C) RivieraWaves 2017-2018
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @defgroup FHOST_IPERF FHOST_IPERF
 * @ingroup FHOST
 * @brief IPERF task for fully hosted firmware
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "co_int.h"
#include "co_bool.h"
#include "lwip/sockets.h"

#if PLF_IPERF
/*
 * DEFINITIONS
 ****************************************************************************************
 */
/// Maximum number of iperf streams
#define FHOST_IPERF_MAX_STREAMS 1

/// UDP Rate
#define FHOST_IPERF_DEFAULT_UDPRATE     1024 * 1024     // 1 Mbit/sec (-u)
/// UDP buffer length
#define FHOST_IPERF_DEFAULT_UDPBUFLEN   1470            // read/write 1470 bytes (-u)
/// Invalid socket id
#define FHOST_IPERF_INVALID_SOCKET      -1
/// Time to travel
#define FHOST_IPERF_TTL                 1
/// Number of IPERF send buffers (credits)
#define FHOST_IPERF_SEND_BUF_CNT        8

/// Type of traffic generation
enum test_mode
{
    /// Unidirectional test
    FHOST_IPERF_TEST_NORMAL = 0,
    /// Bidirectional test simultaneously
    FHOST_IPERF_TEST_DUALTEST,
    /// Unkwnow test mode
    FHOST_IPERF_TEST_UNKNOWN
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Datagram for UDP packets
struct iperf_UDP_datagram
{
    /// Datagram ID
    int32_t     id;
    /// Sending time (seconds)
    uint32_t    sec;
    /// Sending time (microseconds)
    uint32_t    usec;
};

/// Iperf timer
struct iperf_time
{
    /// Second
    uint32_t sec;
    /// Microsecond
    uint32_t usec;
};

/// Iperf configuration flags
struct fhost_iperf_flags
{
    /// Command option: buffer len option set (-l)
    bool is_buf_len_set :1;
    /// Command option: udp mode enable (-u)
    bool is_udp         :1;
    /// Command option: time mode option set (-t)
    bool is_time_mode   :1;
    /// Command option: bandwidth option set (-b)
    bool is_bw_set      :1;
    /// Command option: server mode enable (-s)
    bool is_server      :1;
    /// Command option:  peer version detect option set(-X)
    bool is_peer_ver    :1;
};

/// Iperf configuration
struct fhost_iperf_settings
{
    /// Iperf server IP (-c)
    uint32_t host_ip;
    /// Iperf UDP buffer length (-l)
    uint32_t buf_len;
    /// Iperf test mode
    enum test_mode test_mode;
    /// Iperf printing format (-f): Possible values are: 'a', 'A', 'b', 'B', 'k', 'K', 'g', 'G'
    char format;
    /// Iperf TCP client listen port (-L)
    uint16_t listen_port;
    /// Iperf server port (-p)
    uint16_t port;
    /// IP type-of-service (-S)
    uint16_t tos;
    /// Time to live (-T)
    uint16_t ttl;
    /// Iperf udp rate (-b)
    uint64_t udprate;
    /// Iperf amount of data to send
    uint64_t amount;
    /// Iperf interval
    struct iperf_time interval;
    /// Setting flags
    struct fhost_iperf_flags flags;
};

/// Iperf statistics
struct iperf_stats
{
    /// Transferred bytes
    uint64_t bytes;
    /// Number of transferred datagrams
    uint32_t nb_datagrams;
    /// Number of errors
    uint32_t nb_error;
    /// Number of out of order datagrams
    uint32_t nb_out_of_orded;
    /// Jitter in microseconds
    uint32_t jitter_us;
};

/// Report for TCP and UDP client/server
struct iperf_report
{
    /// Packet ID
    int32_t packet_id;
    /// Current statistics
    struct iperf_stats stats;
    /// Statistics at the last interval
    struct iperf_stats last_stats;
    /// Timestamp of the last sent/received packet
    struct iperf_time packet_time;
    /// Timestamp of the first packet
    struct iperf_time start_time;
    /// End of reception/transmission time
    struct iperf_time end_time;
    /// Sending time included in the received UDP datagram
    struct iperf_time sent_time;
    /// Transit time (RX time - TX time) of last received UDP datagram
    struct iperf_time last_transit;
    /// Last interval time
    struct iperf_time last_interval;
    /// Target interval timestamp
    struct iperf_time interval_target;
    /// UDP client IP address
    ip_addr_t addr;
    /// UDP client port
    u16_t port;
};

/// Iperf stream related info
struct fhost_iperf_stream
{
    /// Ping thread ID
    uint32_t id;
    /// State of ping thread (true for active, false for inactive)
    bool active;
    /// Iperf settings
    struct fhost_iperf_settings iperf_settings;
    /// Handle of iperf send task
    rtos_task_handle iperf_handle;
    /// Iperf semaphore used to wake up the iperf thread to close the task
    rtos_semaphore iperf_task_semaphore;
    /// Semaphore used to protect Iperf buffer pool
    rtos_semaphore send_buf_semaphore;
    /// Iperf timeout semaphore
    rtos_semaphore to_semaphore;
    /// Iperf mutex used when we modify the credits for sending process
    rtos_mutex iperf_mutex;
    /// Param pointer for NET IPERF AL
    void *arg;
    /// TCP/UDP report
    struct iperf_report report;
};

/* Macros for timers */

/// Timer addition
#define iperf_timeradd(a, b, result) \
    (result)->sec = (a)->sec + (b)->sec; \
    (result)->usec = (a)->usec + (b)->usec; \
    while ((result)->usec > 1000000) \
    { \
        (result)->usec -= 1000000; \
        (result)->sec++; \
    }

/// Timer subtraction
#define iperf_timersub(a, b, result) \
    do { \
        int32_t usec; \
        (result)->sec = (a)->sec - (b)->sec; \
        usec = (a)->usec - (b)->usec; \
        (result)->usec = usec; \
        if (usec < 0) { \
            --(result)->sec; \
            (result)->usec = usec + 1000000; \
        } \
    } while (0)

/// Check if timer a is before timer b
#define iperf_timerbefore(a, b) \
    (((a)->sec < (b)->sec) || \
    ((a)->sec == (b)->sec && \
    (a)->usec < (b)->usec))

/// Check if timer a is after timer b
#define iperf_after(a, b) iperf_timerbefore(b, a)

/// Extract timer seconds
#define iperf_timersec(a) ((a)->sec + ((a)->usec / 1000000))

/// Extract timer microseconds
#define iperf_timerusec(a) (((a)->sec * 1000000) + (a)->usec)

/// Extract timer microseconds
#define iperf_timermsec(a) (((a)->sec * 1000) + (a)->usec / 1000)

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
extern const char iperf_short_help[], iperf_long_help[];
extern struct fhost_iperf_stream i_streams[FHOST_IPERF_MAX_STREAMS];

/*
 * FUNCTIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize iperf settings
 *
 * @param[in] iperf_settings    Pointer to iperf settings to initialize
 ****************************************************************************************
 **/
void fhost_iperf_settings_init(struct fhost_iperf_settings *iperf_settings);

/**
 ****************************************************************************************
 * @brief Start iperf command with certain configuration options
 * This function creates the RTOS task dedicated to the iperf command.
 *
 * @param[in] args          Iperf configuration pointer
 * @param[out] args         task handle of the created task
 *
 * @return
 ****************************************************************************************
 */
int fhost_iperf_start(void *args, rtos_task_handle *handle);

/**
 ****************************************************************************************
 * @brief Print interval statistics for UDP client
 *
 * @param[in] stream        Pointer to iperf stream
 ****************************************************************************************
 **/
void fhost_iperf_udp_print_interv_stats(struct fhost_iperf_stream *stream);

/**
 ****************************************************************************************
 * @brief Print iperf statistics with a different format for TCP/UDP Server and Client.
 * Statistics are printed in the task buffer.
 *
 * @param[in] stream     Pointer to iperf stream
 * @param[in] start_time Pointer to beginning time
 * @param[in] end_time   Pointer to ending time
 * @param[in] stats      Pointer to statistics
 ****************************************************************************************
 **/
void fhost_iperf_print_stats(const struct fhost_iperf_stream *stream,
                             struct iperf_time *start_time,
                             struct iperf_time *end_time,
                             const struct iperf_stats *stats);

/**
 ****************************************************************************************
 * @brief Iperf sigkill handler. Closes TCP/UDP Server and Client connection.
 *
 * @param[in] iperf_handle      Iperf task handle
 *
 * @return FHOST_IPC_SUCCESS if successful, FHOST_IPC_ERROR otherwise
 ****************************************************************************************
 **/
int fhost_iperf_sigkill_handler(rtos_task_handle iperf_handle);

#endif /* PLF_IPERF */
