/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @LastEditTime: 2020-06-17 19:31:41
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */
#ifndef _MQTT_CONFIG_H_
#define _MQTT_CONFIG_H_

#define     NO_TLS                              0
#define     TLS_ONE_WAY                         1 //Server verity. Need ca.pem
#define     TLS_TWO_WAY                         2 //Server and client verity. Need ca.pem, client-cert.pem, client-key.pem
#define     MQTT_TLS_LOG                        0 //0: don`t print, 1: print
#define     MQTT_NETWORK_TYPE                   NO_TLS

#if (MQTT_NETWORK_TYPE == NO_TLS)
#define     MQTT_NETWORK_TYPE_NO_TLS
#elif (MQTT_NETWORK_TYPE == TLS_TWO_WAY)
#define     MQTT_NETWORK_TYPE_TLS_TWO_WAY
#endif

//#define     MQTT_LOG_IS_SALOF
#define     MQTT_LOG_LEVEL                      MQTT_LOG_INFO_LEVEL   //MQTT_LOG_WARN_LEVEL MQTT_LOG_DEBUG_LEVEL

#ifdef MQTT_LOG_IS_SALOF
#define     SALOF_USING_LOG                     (1U)
#define     SALOF_USING_SALOF                   (1U)
#define     SALOF_LOG_LEVEL                     MQTT_LOG_LEVEL
#define     SALOF_OS                            SALOF_USING_FREERTOS
#define     SALOF_USING_IDLE_HOOK               (0U)
#define     SALOF_LOG_COLOR                     (1U)
#define     SALOF_LOG_TS                        (0U)
#define     SALOF_LOG_TAR                       (0U)
#define     SALOF_BUFF_SIZE                     512
#define     SALOF_FIFO_SIZE                     4096
#define     SALOF_TASK_STACK_SIZE               1024
#define     SALOF_TASK_TICK                     50
#endif

#define     MQTT_MAX_PACKET_ID                  (0xFFFF - 1)
#define     MQTT_TOPIC_LEN_MAX                  64
#define     MQTT_ACK_HANDLER_NUM_MAX            64
#define     MQTT_DEFAULT_BUF_SIZE               1024
#define     MQTT_DEFAULT_CMD_TIMEOUT            30000
#define     MQTT_MAX_CMD_TIMEOUT                20000
#define     MQTT_MIN_CMD_TIMEOUT                1000
#define     MQTT_KEEP_ALIVE_INTERVAL            30          // unit: second
#define     MQTT_VERSION                        4           // 4 is mqtt 3.1.1
#define     MQTT_RECONNECT_DEFAULT_DURATION     1000
#define     MQTT_THREAD_TICK                    50


#if MQTT_KEEP_ALIVE_INTERVAL*1000 < MQTT_DEFAULT_CMD_TIMEOUT
#error MQTT_KEEP_ALIVE_INTERVAL*1000 cannot small than MQTT_DEFAULT_CMD_TIMEOUT
#endif

#endif /* _MQTT_CONFIG_H_ */
