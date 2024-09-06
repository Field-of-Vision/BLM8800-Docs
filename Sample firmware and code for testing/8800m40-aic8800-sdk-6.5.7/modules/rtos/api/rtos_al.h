/**
 ****************************************************************************************
 *
 * @file rtos_al.h
 *
 * @brief Declaration of RTOS abstraction layer.
 * The functions declared here shall be implemented in the RTOS folder and call the RTOS
 * corresponding functions.
 *
 * Copyright (C) RivieraWaves 2017-2019
 *
 ****************************************************************************************
 */

#ifndef RTOS_AL_H_
#define RTOS_AL_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rtos_def.h"
#include "ll.h"
#include "dbg_assert.h"
#include <stdbool.h>
#include "FreeRTOS.h"
#include "timers.h"
#include "plf.h"


/**
 * RTOS task identifier
 */
enum rtos_task_id {
    IDLE_TASK           = 0,
    TMR_DAEMON_TASK     = 1,
    CONSOLE_TASK        = 2,
    TEST_TASK           = 3,
    BT_TASK             = 4,
    INTERSYS_TASK       = 5,
    ASIO_TASK           = 6,
    AUDIO_TASK          = 7,
    WIFI_TASK           = 8,
    CONTROL_TASK        = 9,
    SUPPLICANT_TASK     = 10,
    IP_TASK             = 11,
    APPLICATION_TASK    = 12,
    TG_SEND_TASK        = 13,
    PING_SEND_TASK      = 14,
    IPERF_TASK          = 15,
    SMARTCONF_TASK      = 16,
    IPC_CNTRL_TASK      = 17,
    TCPUDP_FIRST_TASK   = 18,
    TCPUDP_LAST_TASK    = 21,
    RTP_TASK            = 22,
    USBH_TASK           = 23,
    MDNS_TASK           = 24,
    RTCP_TASK           = 25,
    CO_TASK             = 26,
    BLE_TASK            = 27,
    DSP_TASK            = 28,
    WIFI_USER_TASK      = 29,
    APP_HOSTIF_TASK     = 30,
    APP_FHOST_TX_TASK   = 31,
    USB_BT_TASK         = 32,
    SOFTWDG_TASK        = 33,
    HOSTAPD_TASK        = 34,
    TCP_WAKEUP_TASK     = 35,
    WLAN_CONN_TASK      = 36,
    SLEEP_WAKEUP_TASK   = 37,
    NOBLOCK_WIFI_TASK   = 38,
    SLEEP_IRQ_TASK      = 39,
    XMDM_SEND_PROC_TASK = 40,
    XMDM_SEND_DATA_TASK = 41,
    XMDM_RECV_TASK      = 42,
    XMDM_STOP_TASK      = 43,
    MAX_TASK,
    UNDEF_TASK        = 255,
};

/*
 * FUNCTIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Get the current RTOS time, in ms.
 *
 * @param[in] isr  Indicate if this is called from ISR.
 *
 * @return The current RTOS time
 ****************************************************************************************
 */
uint32_t rtos_now(bool isr);

/**
 ****************************************************************************************
 * @brief Allocate memory.
 *
 * @param[in] size Size, in bytes, to allocate.
 *
 * @return Address of allocated memory on success and NULL if error occurred.
 ****************************************************************************************
 */
void *rtos_malloc(uint32_t size);

/**
 ****************************************************************************************
 * @brief Allocate memory and initialize it to 0.
 *
 * @param[in] nb_elt  Number of element to allocate.
 * @param[in] size    Size, in bytes, of each element allocate.
 *
 * @return Address of allocated and initialized memory on success and NULL if error occurred.
 ****************************************************************************************
 */
void *rtos_calloc(uint32_t nb_elt, uint32_t size);

/**
 ****************************************************************************************
 * @brief Free memory.
 *
 * @param[in] ptr Memory buffer to free. MUST have been allocated with @ref rtos_malloc
 ****************************************************************************************
 */
void rtos_free(void *ptr);

/**
 ****************************************************************************************
 * @brief Re-allocate memory and free previous ptr.
 *
 * @param[in] ptr     Previous memory ptr.
 * @param[in] size    Size, in bytes, to allocate new.
 *
 * @return Address of allocated and copied memory on success and NULL if error occurred.
 ****************************************************************************************
 */
void * rtos_realloc(void *ptr, size_t size);

/**
 ****************************************************************************************
 * @brief Get HEAP Memory information. (For debug purpose only)
 *
 * @param[out] total_size    Updated with HEAP memory size.
 * @param[out] free_size     Updated with the currently available memory.
 * @param[out] min_free_size Updated with the lowest level of free memory reached.
 ****************************************************************************************
 */
void rtos_heap_info(int *total_size, int *free_size, int *min_free_size);

/**
 ****************************************************************************************
 * @brief Create a RTOS task.
 *
 * @param[in] func Pointer to the task function
 * @param[in] name Name of the task
 * @param[in] task_id ID of the task
 * @param[in] stack_depth Required stack depth for the task
 * @param[in] params Pointer to private parameters of the task function, if any
 * @param[in] prio Priority of the task
 * @param[out] task_handle Handle of the task, that might be used in subsequent RTOS
 *                         function calls
 *
 * @return 0 on success and != 0 if error occurred.
 ****************************************************************************************
 */
int rtos_task_create(rtos_task_fct func,
                     const char * const name,
                     enum rtos_task_id task_id,
                     const uint16_t stack_depth,
                     void * const params,
                     rtos_prio prio,
                     rtos_task_handle * const task_handle);
/**
 ****************************************************************************************
 * @brief Delete a RTOS task.
 *
 * @param[in] task_handle Handle of the task to delete.
 ****************************************************************************************
 */
void rtos_task_delete(rtos_task_handle task_handle);

/**
 ****************************************************************************************
 * @brief RTOS task suspends itself for a specific duration.
 *
 * @param[in] duration Duration in ms.
 ****************************************************************************************
 */
void rtos_task_suspend(int duration);

/**
 ****************************************************************************************
 * @brief RTOS task suspends, until resume
 *
 * @param[in] task_handle Handle of the task
 ****************************************************************************************
 */
void rtos_task_stop(rtos_task_handle task_handle);

/**
 ****************************************************************************************
 * @brief RTOS task resume
 *
 * @param[in] task_handle Handle of the task
 ****************************************************************************************
 */
void rtos_task_start(rtos_task_handle task_handle);

/**
 ****************************************************************************************
 * @brief List all RTOS tasks in runtime.
 *
 * @param[in] buffer_size Define the size of buffer for receiving tasks message.
 * @return 0 on success and != 0 if error occurred.
 * @
 * @-----------------------------TaskList-Table-brief-------------------------
 * @ Task-Name    Status     Priority    min-remanent-heap    create-sequence
 * @ Name-1         X            0             100                   1
 * @ Name-2         B            1             200                   2
 * @ Name-3         R            2             200                   3
 * @ Name-4         D            3             300                   4
 * @ Name-5         S            2             400                   5
 * @--------------------------------------------------------------------------
 * @ Status brief:
 * @ X: running  B: blocked  R: ready  D: deleted  S: suspended
 ****************************************************************************************
 */
int rtos_task_list(int buffer_size);

#if (configUSE_TRACE_FACILITY == 1)
/**
 ****************************************************************************************
 * @brief Show current task info. (For debug purpose only)
 *
 * --------------- Output format ---------------
 * TaskName     Num     Prio    Stat    StkHWM
 * Name-1       1       1       X       207
 * Name-2       3       0       R       469
 * Name-3       2       1       B       226
 * ---------------------------------------------
 *
 ****************************************************************************************
 */
void rtos_task_info(void);
#endif

/**
 ****************************************************************************************
 * @brief Initialize notification for a FHOST task.
 *
 * If notification are natively supported by the target RTOS, then this function will
 * probably do nothing. If this is not the case this function allows the RTOS_AL
 * implementation to initialize its own notification system for the task (e.g. allocating
 * a binary semaphore for the task).
 *
 * To ensure the maximum compatibility, this function must be called before
 * @ref rtos_task_wait_notification or @ref rtos_task_notify can be used on a task.
 *
 * @param[in] task  Task handle
 * @return 0 on success and != 0 if error occurred.
 ****************************************************************************************
  */
int rtos_task_init_notification(rtos_task_handle task);

/**
 ****************************************************************************************
 * @brief Task suspend itself until it is notified (or timeout expires)
 *
 * The task will be resumed when another task call @ref rtos_task_notify. It another task
 * already call @ref rtos_task_notify then the function will return immediately.
 * On return it clears all pending notification.
 * @ref rtos_task_init_notification must be called first before calling this function.
 *
 * @param[in] timeout Maximum duration to wait, in ms, if no notification is pending.
 *                    0 means do not wait and -1 means wait indefinitely.
 *
 * @return The number of pending notification (0 if timeout was reached)
 ****************************************************************************************
 */
uint32_t rtos_task_wait_notification(int timeout);

/**
 ****************************************************************************************
 * @brief Send notification to a task
 *
 * If the task is suspended, after calling @ref rtos_task_wait_notification, it will
 * resume it. Otherwise the notification will be pending for the task.
 *
 * @param[in] task Task to notify.
 * @param[in] isr  Indicate if this is called from ISR.
 *
 ****************************************************************************************
 */
void rtos_task_notify_increment(rtos_task_handle task_handle, bool isr);

/**
 ****************************************************************************************
 * @brief Send notification to a task
 *
 * If the task is suspended, after calling @ref rtos_task_wait_notification, it will
 * resume it. Otherwise the notification will be pending for the task.
 *
 * @param[in] task_handle  Handle of the task to notify.
 * @param[in] value Value to notify.
 * @param[in] isr   Indicate if this is called from ISR.
 *
 ****************************************************************************************
 */
void rtos_task_notify_setvalue(rtos_task_handle task_handle, uint32_t value, bool isr);

/**
 ****************************************************************************************
 * @brief Send notification to a task, actual notification value is bitwise ORed with
 *        param value
 *
 * If the task is suspended, after calling @ref rtos_task_wait_notification, it will
 * resume it. Otherwise the notification will be pending for the task.
 *
 * @param[in] task_handle  Handle of the task to notify.
 * @param[in] value Value to OR with actual notification value.
 * @param[in] isr   Indicate if this is called from ISR.
 *
 ****************************************************************************************
 */
void rtos_task_notify_setbits(rtos_task_handle task_handle, uint32_t value, bool isr);

/**
 ****************************************************************************************
 * @brief Get priority of a task
 *
 * @param[in] task_handle  Handle of the task to get priority.
 *
 * @return The priority of the task
 ****************************************************************************************
 */
uint32_t rtos_task_get_priority(rtos_task_handle task_handle);

/**
 ****************************************************************************************
 * @brief Set priority of a task
 *
 * If new priority is higher than (configMAX_PRIORITIES - 1), then new priority will be
 * set to (configMAX_PRIORITIES - 1).
 *
 * @param[in] task_handle  Handle of the task to set priority.
 * @param[in] priority New priority.
 *
 ****************************************************************************************
 */
void rtos_task_set_priority(rtos_task_handle task_handle, uint32_t priority);

/**
 ****************************************************************************************
 * @brief Get handle of a task via its name
 *
 * @param[in] name  Task name of the task.
 * @return The Handle of the task if task exist.
 ****************************************************************************************
 */
TaskHandle_t rtos_task_get_handle(const char *name);

/**
 ****************************************************************************************
 * @brief Create a RTOS message queue.
 *
 * @param[in]  elt_size Size, in bytes, of one queue element
 * @param[in]  nb_elt   Number of element to allocate for the queue
 * @param[out] queue    Update with queue handle on success
 *
 * @return 0 on success and != 0 if error occurred.
 ****************************************************************************************
 */
int rtos_queue_create(int elt_size, int nb_elt, rtos_queue *queue);

/**
 ****************************************************************************************
 * @brief Delete a queue previously created by @ref rtos_queue_create.
 * This function does not verify if the queue is empty or not before deleting it.
 *
 * @param[in]  queue   Queue handle
 ****************************************************************************************
 */
void rtos_queue_delete(rtos_queue queue);

/**
 ****************************************************************************************
 * @brief Check if a RTOS message queue is empty or not.
 * This function can be called both from an ISR and a task.
 *
 * @param[in]  queue   Queue handle
 *
 * @return true if queue is empty, false otherwise.
 ****************************************************************************************
 */
bool rtos_queue_is_empty(rtos_queue queue);

/**
 ****************************************************************************************
 * @brief Check if a RTOS message queue is full or not.
 * This function can be called both from an ISR and a task.
 *
 * @param[in]  queue   Queue handle
 *
 * @return true if queue is full, false otherwise.
 ****************************************************************************************
 */
bool rtos_queue_is_full(rtos_queue queue);

/**
 ****************************************************************************************
 * @brief Get the number of messages pending a queue.
 * This function can be called both from an ISR and a task.
 *
 * @param[in]  queue   Queue handle
 *
 * @return The number of messages pending in the queue.
 ****************************************************************************************
 */
int rtos_queue_cnt(rtos_queue queue);

/**
 ****************************************************************************************
 * @brief Write a message at the end of a RTOS message queue.
 *
 * @param[in]  queue   Queue handle
 * @param[in]  msg     Message to copy in the queue. (It is assume that buffer is of the
 *                     size specified in @ref rtos_queue_create)
 * @param[in]  timeout Maximum duration to wait, in ms, if queue is full. 0 means do not
 *                     wait and -1 means wait indefinitely.
 * @param[in]  isr     Indicate if this is called from ISR. If set, @p timeout parameter
 *                     is ignored.
 *
 * @return 0 on success and != 0 if error occurred (i.e queue was full and maximum
 * duration has been reached).
 ****************************************************************************************
 */
int rtos_queue_write(rtos_queue queue, void *msg, int timeout, bool isr);

/**
 ****************************************************************************************
 * @brief Read a message from a RTOS message queue.
 *
 * @param[in]  queue   Queue handle
 * @param[in]  msg     Buffer to copy into. (It is assume that buffer is of the
 *                     size specified in @ref rtos_queue_create)
 * @param[in]  timeout Maximum duration to wait, in ms, if queue is empty. 0 means do not
 *                     wait and -1 means wait indefinitely.
 * @param[in]  isr     Indicate if this is called from ISR. If set, @p timeout parameter
 *                     is ignored.
 *
 * @return 0 on success and != 0 if error occurred (i.e queue was empty and maximum
 * duration has been reached).
 ****************************************************************************************
 */
int rtos_queue_read(rtos_queue queue, void *msg, int timeout, bool isr);

/**
 ****************************************************************************************
 * @brief Peek a message from a RTOS message queue.
 *
 * @param[in]  queue   Queue handle
 * @param[in]  msg     Buffer to copy into. (It is assume that buffer is of the
 *                     size specified in @ref rtos_queue_create)
 * @param[in]  timeout Maximum duration to wait, in ms, if queue is empty. 0 means do not
 *                     wait and -1 means wait indefinitely.
 * @param[in]  isr     Indicate if this is called from ISR. If set, @p timeout parameter
 *                     is ignored.
 *
 * @return 0 on success and != 0 if error occurred (i.e queue was empty and maximum
 * duration has been reached).
 ****************************************************************************************
 */
int rtos_queue_peek(rtos_queue queue, void *msg, int timeout, bool isr);

/**
 ****************************************************************************************
 * @brief Resets a RTOS message queue to its original empty state.
 * Any data contained in the queue at the time it is reset is discarded.
 *
 * @return 1
 ****************************************************************************************
 */

int rtos_queue_reset(rtos_queue queue);

/**
 ****************************************************************************************
 * @brief Creates and returns a new semaphore.
 *
 * @param[out] semaphore Semaphore handle returned by the function
 * @param[in]  max_count The maximum count value that can be reached by the semaphore.
 *             When the semaphore reaches this value it can no longer be 'given'.
 * @param[in]  init_count The count value assigned to the semaphore when it is created.
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_semaphore_create(rtos_semaphore *semaphore, int max_count, int init_count);

/**
 ****************************************************************************************
 * @brief Return a semaphore count.
 *
 * @param[in]  semaphore Semaphore handle
 *
 * @return Semaphore count.
 ****************************************************************************************
 */
int rtos_semaphore_get_count(rtos_semaphore semaphore);

/**
 ****************************************************************************************
 * @brief Delete a semaphore previously created by @ref rtos_semaphore_create.
 *
 * @param[in]  semaphore Semaphore handle
 ****************************************************************************************
 */
void rtos_semaphore_delete(rtos_semaphore semaphore);

/**
 ****************************************************************************************
 * @brief Wait for a semaphore to be available.
 *
 * @param[in]  semaphore Semaphore handle
 * @param[in]  timeout   Maximum duration to wait, in ms. 0 means do not wait and -1 means
 *                       wait indefinitely.
 *
 * @return 0 on success and != 0 if timeout occurred.
 ****************************************************************************************
 */
int rtos_semaphore_wait(rtos_semaphore semaphore, int timeout);

/**
 ****************************************************************************************
 * @brief Signal the semaphore the handle of which is passed as parameter.
 *
 * @param[in]  semaphore Semaphore handle
 * @param[in]  isr       Indicate if this is called from ISR
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_semaphore_signal(rtos_semaphore semaphore, bool isr);

/**
 ****************************************************************************************
 * @brief * Creates a new software timer instance, and returns a handle by which the
 * created software timer can be referenced.
 *
 * @param[out] see xTimerCreate described.
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
TimerHandle_t rtos_timer_create( const char * const pcTimerName,
                            const TickType_t xTimerPeriodInTicks,
                            const UBaseType_t uxAutoReload,
                            void * const pvTimerID,
                            TimerCallbackFunction_t pxCallbackFunction );

/**
 ****************************************************************************************
 * @brief * start timer
 *
 * @param[out] see xTimerStart described.
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_timer_start(TimerHandle_t xTimer,TickType_t xTicksToWait, bool isr);

/**
 ****************************************************************************************
 * @brief * suspend timer
 *
 * @param[out] see xTimerStop described.
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_timer_stop(TimerHandle_t xTimer,TickType_t xTicksToWait);

/**
 ****************************************************************************************
 * @brief * suspend timer
 *
 * @param[out] see xTimerStopFromISR described.
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_timer_stop_isr(TimerHandle_t xTimer);

/**
 ****************************************************************************************
 * @brief * Delete timer
 *
 * @param[out] see xTimerDelete described.
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_timer_delete(TimerHandle_t xTimer,TickType_t xTicksToWait);

/**
 ****************************************************************************************
 * @brief * change timer period and reset timer
 *
 * @param[out] see xTimerChangePeriod described.
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_timer_change_period(TimerHandle_t xTimer, TickType_t xNewPeriod, TickType_t xTicksToWait);

/**
 ****************************************************************************************
 * @brief * change timer period and reset timer, called in isr
 *
 * @param[out] see xTimerChangePeriodFromISR described.
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_timer_change_period_isr(TimerHandle_t xTimer, TickType_t xNewPeriod);

/**
 ****************************************************************************************
 * @brief * restart timer
 *
 * @param[out] see xTimerReset described.
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_timer_restart(TimerHandle_t xTimer,TickType_t xTicksToWait, bool isr);

/**
 ****************************************************************************************
 * @brief * Returns the ID assigned to the timer.
 *
 * @param[out] see pvTimerGetTimerID described.
 *
 * @return The ID assigned to the timer being queried.
 ****************************************************************************************
 */
void *rtos_timer_get_pvTimerID( TimerHandle_t xTimer );

/**
 ****************************************************************************************
 * @brief Creates and returns a new recursive mutex.
 *
 * @param[out] mutex Mutex handle returned by the function
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_mutex_recursive_create(rtos_mutex *mutex);

/**
 ****************************************************************************************
 * @brief Lock a recursive mutex.
 *
 * @param[in]  mutex Mutex handle
 * @param[in]  timeout   Maximum duration to wait, in ms. 0 means do not wait and -1 means
 *                       wait indefinitely.

 * @return 0 on success and != 0 if timeout occurred.
 ****************************************************************************************
 */
int rtos_mutex_recursive_lock(rtos_mutex mutex);

/**
 ****************************************************************************************
 * @brief Unlock a recursive mutex.
 *
 * @param[in]  mutex Mutex handle
 *
 * @return 0 on success and != 0 if timeout occurred.
 ****************************************************************************************
 */
int rtos_mutex_recursive_unlock(rtos_mutex mutex);

/**
 ****************************************************************************************
 * @brief Creates and returns a new mutex.
 *
 * @param[out] mutex Mutex handle returned by the function
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_mutex_create(rtos_mutex *mutex);

/**
 ****************************************************************************************
 * @brief Delete a mutex previously created by @ref rtos_mutex_create.
 *
 * @param[in]  mutex Mutex handle
 ****************************************************************************************
 */
void rtos_mutex_delete(rtos_mutex mutex);

/**
 ****************************************************************************************
 * @brief Lock a mutex.
 *
 * @param[in]  mutex Mutex handle
 * @param[in]  timeout   Maximum duration to wait, in ms. 0 means do not wait and -1 means
 *                       wait indefinitely.

 * @return 0 on success and != 0 if timeout occurred.
 ****************************************************************************************
 */
int rtos_mutex_lock(rtos_mutex mutex, int timeout);

/**
 ****************************************************************************************
 * @brief Unlock a mutex.
 *
 * @param[in]  mutex Mutex handle
 *
 * @return 0 on success and != 0 if timeout occurred.
 ****************************************************************************************
 */
int rtos_mutex_unlock(rtos_mutex mutex);

/**
 ****************************************************************************************
 * @brief Create and returns a new event group.
 *
 * @param[out] event_group Event Group handle returned by the function
 *
 * @return 0 on success and != 0 otherwise.
 ****************************************************************************************
 */
int rtos_event_group_create(rtos_event_group *event_group);

/**
 ****************************************************************************************
 * @brief Delete a event group previously created by @ref rtos_event_group_create.
 *
 * @param[in]  mutex Event Group handle
 ****************************************************************************************
 */
void rtos_event_group_delete(rtos_event_group event_group);

/**
 ****************************************************************************************
 * @brief Get the value of the event bits in the event group.
 *
 * @param[in]  event_group Event Group handle
 * @param[in]  isr       Indicate if this is called from ISR
 *
 * @return The value of the event bits in the event group when the function was called
 ****************************************************************************************
 */
uint32_t rtos_event_group_get_bits(rtos_event_group event_group, bool isr);

/**
 ****************************************************************************************
 * @brief Wait for the event bits in the event group to be available.
 *
 * @param[in]  event_group Event Group handle
 * @param[in]  val       The val of the event bits to wait for
 * @param[in]  clear_on_exit Set true to clear value in the event bits on exit
 * @param[in]  wait_all_bits If set true, then function only return when all bits in the value
 *                       were set(or timeout), otherwise function will return when any bit in the value was
 *                       set(or timeout).
 * @param[in]  timeout   Maximum duration to wait, in ms. 0 means do not wait and -1 means
 *                       wait indefinitely.
 *
 * @return The value of the event bits in the event group
 ****************************************************************************************
 */
uint32_t rtos_event_group_wait_bits(rtos_event_group event_group, const uint32_t val,
    const bool clear_on_exit, const bool wait_all_bits, int timeout);

/**
 ****************************************************************************************
 * @brief Clear the value of the event bits in the event group.
 *
 * @param[in]  event_group Event Group handle
 * @param[in]  value     The val of the event bits to clear
 * @param[in]  isr       Indicate if this is called from ISR
 *
 * @return The value of the event bits in the event group before any bits were cleared
 ****************************************************************************************
 */
uint32_t rtos_event_group_clear_bits(rtos_event_group event_group, const uint32_t val, bool isr);

/**
 ****************************************************************************************
 * @brief Set the value of the event bits in the event group.
 *
 * @param[in]  event_group Event Group handle
 * @param[in]  value     The val of the event bits to set
 * @param[in]  isr       Indicate if this is called from ISR
 *
 * @return The value of the event bits in the event group when the function return
 ****************************************************************************************
 */
uint32_t rtos_event_group_set_bits(rtos_event_group event_group, const uint32_t val, bool isr);

/**
 ****************************************************************************************
 * @brief Enter a critical section.
 * This function returns the previous protection level that is then used in the
 * @ref rtos_unprotect function call in order to put back the correct protection level
 * when exiting the critical section. This allows nesting the critical sections.
 *
 * @return  The previous protection level
 ****************************************************************************************
 */
uint32_t rtos_protect(void);

/**
 ****************************************************************************************
 * @brief Exit a critical section.
 * This function restores the previous protection level.
 *
 * @param[in]  protect The protection level to restore.
 ****************************************************************************************
 */
void rtos_unprotect(uint32_t protect);

/**
 ****************************************************************************************
 * @brief Launch the RTOS scheduler.
 * This function is supposed not to return as RTOS will switch the context to the highest
 * priority task inside this function.
 ****************************************************************************************
 */
void rtos_start_scheduler(void);

/**
 ****************************************************************************************
 * @brief Init RTOS
 *
 * Initialize RTOS layers before start.
 *
 * @return 0 on success and != 0 if error occurred
 ****************************************************************************************
 */
int rtos_init(void);

/**
 ****************************************************************************************
 * @brief Change the priority of a task
 * This function cannot be called from an ISR.
 *
 * @param[in] handle Task handle
 * @param[in] priority New priority to set to the task
 *
 ****************************************************************************************
 */
void rtos_priority_set(rtos_task_handle handle, rtos_prio priority);

/**
 ****************************************************************************************
 * @brief Return RTOS task handle
 *
 * @return current task handle
 ****************************************************************************************
 */
rtos_task_handle rtos_get_task_handle(void);

/**
 ****************************************************************************************
 * @brief Return RTOS scheduler state
 *
 ****************************************************************************************
 */
rtos_sched_state rtos_get_scheduler_state(void);

#if (PLF_AIC8800)
PRIVATE_HOST_EXT_STATEMENT(TickType_t, xTickCount);
#endif

void rtos_data_save(void);

#endif // RTOS_H_
