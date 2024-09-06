/**
 ****************************************************************************************
 *
 * @file rtos_al.c
 *
 * @brief Implementation of the FreeRTOS abstraction layer.
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rtos_def.h"
#include "rtos_al.h"
#include "rtos.h"
#include "plf.h"
#include <string.h>
#include "boot.h"
#include "sleep_api.h"
#include "lp_ticker_api.h"
#if (PLF_STDLIB)
#include <malloc.h>
#endif

#if PLF_WIFI_STACK
#ifdef CONFIG_RWNX_LWIP
#include "fhost.h"
#include "fhost_wpa.h"
#endif /* CONFIG_RWNX_LWIP */
#endif /* PLF_WIFI_STACK */

#if PLF_AON_SUPPORT
#include "co_main.h"
#endif

#if PLF_BT_STACK
#if PLF_BLE_ONLY
#include "ble_task.h"
#endif
#endif

#define OSAL_TRACE_TASK 0
#define OSAL_TRACE_MEM  0

#define OSAL_TRACE      (OSAL_TRACE_TASK | OSAL_TRACE_MEM)

#if OSAL_TRACE
/// conversion table between task handles and task ID (for trace purpose)
static rtos_task_handle task_table[MAX_TASK];
/// ID of the task that is currently being created.
/// (Needed as traceTASK_CREATE hook is called before task_table is update)
static enum rtos_task_id creating_task_id = UNDEF_TASK;
#endif

#if (!PLF_STDLIB)
#if configAPPLICATION_ALLOCATED_HEAP
/// Pointer to the start of the HEAP
uint8_t *ucHeap = (uint8_t *)HEAP_BASE;
#endif
#endif

/*
 * FUNCTIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Convert ms to ticks
 *
 * @param[in] timeout_ms Timeout value in ms (use -1 for no timeout).
 * @return number of ticks for the specified timeout value.
 *
 ****************************************************************************************
 */

__INLINE TickType_t rtos_timeout_2_tickcount(int timeout_ms)
{
    if (timeout_ms < 0)
    {
        return portMAX_DELAY;
    }
    else
    {
        return pdMS_TO_TICKS(timeout_ms);
    }
}

uint32_t rtos_now(bool isr)
{
    if (isr)
    {
        return xTaskGetTickCountFromISR();
    }
    else
    {
        return xTaskGetTickCount();
    }
}

void *rtos_malloc(uint32_t size)
{
    return pvPortMalloc(size);
}

void *rtos_calloc(uint32_t nb_elt, uint32_t size)
{
    void * res = pvPortMalloc(nb_elt * size);
    if (res)
        memset(res, 0, nb_elt * size);

    return res;
}

void rtos_free(void *ptr)
{
    vPortFree(ptr);
}

void * rtos_realloc(void *ptr, size_t size)
{
    void *res;

    if (!ptr)
        return rtos_malloc(size);

    if (!size) {
        rtos_free(ptr);
        return NULL;
    }

    res = rtos_malloc(size);
    if (res) {
        if (size)
            memcpy(res, ptr, size);
        rtos_free(ptr);
    }

    return res;
}

void rtos_heap_info(int *total_size, int *free_size, int *min_free_size)
{
    *total_size = configTOTAL_HEAP_SIZE;
    #if (PLF_STDLIB)
    struct mallinfo info = mallinfo();
    *free_size = info.fordblks + (configTOTAL_HEAP_SIZE - info.arena);
    *min_free_size = configTOTAL_HEAP_SIZE - info.arena;
    #else
    *free_size = xPortGetFreeHeapSize();
    *min_free_size = xPortGetMinimumEverFreeHeapSize();
    #endif
}

int rtos_task_create(rtos_task_fct func,
                     const char * const name,
                     enum rtos_task_id task_id,
                     const uint16_t stack_depth,
                     void * const params,
                     rtos_prio prio,
                     rtos_task_handle * const task_handle)
{
    BaseType_t res;
    rtos_task_handle handle;

    #if OSAL_TRACE
    creating_task_id = task_id;
    #endif

    if (strlen(name) >= configMAX_TASK_NAME_LEN)
        return 2;

    res = xTaskCreate(func, name, stack_depth, params, prio, &handle);

    if (res != pdPASS)
        return 1;

    #if ( configUSE_TRACE_FACILITY == 1 ) || ( configUSE_RW_TASK_ID == 1 )
    vTaskSetTaskNumber(handle, task_id);
    #endif

    if (task_handle)
        *task_handle = handle;

    return 0;
}

void rtos_task_delete(rtos_task_handle task_handle)
{
    if (!task_handle)
        task_handle = xTaskGetCurrentTaskHandle();
    if (eTaskGetState(task_handle) != eDeleted)
        vTaskDelete(task_handle);
}

void rtos_task_suspend(int duration)
{
    if (duration <= 0)
        return;
    vTaskDelay(pdMS_TO_TICKS(duration));
}

void rtos_task_stop(rtos_task_handle task_handle)
{
    vTaskSuspend(task_handle);
}

void rtos_task_start(rtos_task_handle task_handle)
{
    vTaskResume(task_handle);
}

int rtos_task_list(int buffer_size)
{
    int total_size, free_size, min_free_size;
    rtos_heap_info(&total_size, &free_size, &min_free_size);

    if(free_size < buffer_size) {
        dbg("Heap size is not enough!\n");
        return -1;
    }

    #if (configUSE_STATS_FORMATTING_FUNCTIONS > 0)
    char *pbuf= (char *)rtos_calloc(1, buffer_size);
    vTaskList(pbuf);
    dbg("TaskList:\n");
    dbg("%s\n", pbuf);
    rtos_free(pbuf);
    #endif
    return 0;
}

#if (configUSE_TRACE_FACILITY == 1)
void rtos_task_info(void)
{
    UBaseType_t array_size = uxTaskGetNumberOfTasks();
    TaskStatus_t *task_status_array = rtos_malloc(array_size * sizeof(TaskStatus_t));
    if (task_status_array) {
        const char task_st_ch[] = {'X', 'R', 'B', 'S', 'D'};
        UBaseType_t idx;
        array_size = uxTaskGetSystemState(task_status_array, array_size, NULL);
        dbg("TaskName\tNum\tPrio\tStat\tStkHWM\tHdl\tStkBA\n");
        for (idx = 0; idx < array_size; idx++) {
            dbg("%s%s%d\t%d\t%c\t%d\t%x\t%x\n",
                task_status_array[idx].pcTaskName,
                (strlen(task_status_array[idx].pcTaskName) < (configMAX_TASK_NAME_LEN - 8)) ? "\t\t" : "\t", task_status_array[idx].xTaskNumber,
                task_status_array[idx].uxCurrentPriority, task_st_ch[task_status_array[idx].eCurrentState],
                task_status_array[idx].usStackHighWaterMark, (uint32_t)task_status_array[idx].xHandle, (uint32_t)task_status_array[idx].pxStackBase);
        }
        rtos_free(task_status_array);
    }
}
#endif

int rtos_task_init_notification(rtos_task_handle task)
{
    return 0;
}

uint32_t rtos_task_wait_notification(int timeout)
{
    return ulTaskNotifyTake(pdTRUE, rtos_timeout_2_tickcount(timeout));
}

void rtos_task_notify_increment(rtos_task_handle task_handle, bool isr)
{
    if (isr)
    {
        BaseType_t task_woken = pdFALSE;

        vTaskNotifyGiveFromISR(task_handle, &task_woken);
        portYIELD_FROM_ISR(task_woken);
    }
    else
    {
        xTaskNotifyGive(task_handle);
    }
}

void rtos_task_notify_setvalue(rtos_task_handle task_handle, uint32_t value, bool isr)
{
    if (isr)
    {
        BaseType_t task_woken = pdFALSE;

        xTaskNotifyFromISR(task_handle, value, eSetValueWithOverwrite, &task_woken);
        portYIELD_FROM_ISR(task_woken);
    }
    else
    {
        xTaskNotify(task_handle, value, eSetValueWithOverwrite);
    }
}

void rtos_task_notify_setbits(rtos_task_handle task_handle, uint32_t value, bool isr)
{
    if (isr)
    {
        BaseType_t task_woken = pdFALSE;

        xTaskNotifyFromISR(task_handle, value, eSetBits, &task_woken);
        portYIELD_FROM_ISR(task_woken);
    }
    else
    {
        xTaskNotify(task_handle, value, eSetBits);
    }
}

uint32_t rtos_task_get_priority(rtos_task_handle task_handle)
{
    return uxTaskPriorityGet(task_handle);
}

void rtos_task_set_priority(rtos_task_handle task_handle, uint32_t priority)
{
    vTaskPrioritySet(task_handle, priority);
}

TaskHandle_t rtos_task_get_handle(const char *name)
{
    return xTaskGetHandle(name);
}

int rtos_queue_create(int elt_size, int nb_elt, rtos_queue *queue)
{
    *queue = xQueueCreate(nb_elt, elt_size);

    if ( *queue == NULL )
        return -1;

    return 0;
}

void rtos_queue_delete(rtos_queue queue)
{
    vQueueDelete(queue);
}

bool rtos_queue_is_empty(rtos_queue queue)
{
    BaseType_t res;

    GLOBAL_INT_DISABLE();
    res = xQueueIsQueueEmptyFromISR(queue);
    GLOBAL_INT_RESTORE();

    return (res == pdTRUE);
}

bool rtos_queue_is_full(rtos_queue queue)
{
    BaseType_t res;

    GLOBAL_INT_DISABLE();
    res = xQueueIsQueueFullFromISR(queue);
    GLOBAL_INT_RESTORE();

    return (res == pdTRUE);
}

int rtos_queue_cnt(rtos_queue queue)
{
    UBaseType_t res;

    GLOBAL_INT_DISABLE();
    res = uxQueueMessagesWaitingFromISR(queue);
    GLOBAL_INT_RESTORE();

    return ((int)res);
}

int rtos_queue_write(rtos_queue queue, void *msg, int timeout, bool isr)
{
    BaseType_t res;

    if (isr)
    {
        BaseType_t task_woken = pdFALSE;

        res = xQueueSendToBackFromISR(queue, msg, &task_woken);
        portYIELD_FROM_ISR(task_woken);
    }
    else
    {
        res = xQueueSendToBack(queue, msg, rtos_timeout_2_tickcount(timeout));
    }

    return (res == errQUEUE_FULL);
}

int rtos_queue_read(rtos_queue queue, void *msg, int timeout, bool isr)
{
    BaseType_t res = pdPASS;

    if (isr)
    {
        BaseType_t task_woken = pdFALSE;

        res = xQueueReceiveFromISR(queue, msg, &task_woken);
        portYIELD_FROM_ISR(task_woken);
    }
    else
    {
        res = xQueueReceive(queue, msg, rtos_timeout_2_tickcount(timeout));
    }

    return (res == errQUEUE_EMPTY);
}

int rtos_queue_peek(rtos_queue queue, void *msg, int timeout, bool isr)
{
    BaseType_t res = pdPASS;

    if (isr)
    {
        res = xQueuePeekFromISR(queue, msg);
    }
    else
    {
        res = xQueuePeek(queue, msg, rtos_timeout_2_tickcount(timeout));
    }

    return (res == errQUEUE_EMPTY);
}

int rtos_queue_reset(rtos_queue queue)
{
    BaseType_t res = pdPASS;

    res = xQueueReset(queue);

    return (res == pdPASS);
}

int rtos_semaphore_create(rtos_semaphore *semaphore, int max_count, int init_count)
{
    int res = -1;

    if (max_count == 1)
    {
        *semaphore = xSemaphoreCreateBinary();

        if (*semaphore != 0)
        {
            if (init_count)
            {
                xSemaphoreGive(*semaphore);
            }
            res = 0;
        }
    }
    else
    {
        *semaphore = xSemaphoreCreateCounting(max_count, init_count);

        if (*semaphore != 0)
        {
            res = 0;
        }
    }

    return res;
}

void rtos_semaphore_delete(rtos_semaphore semaphore)
{
    vSemaphoreDelete(semaphore);
}

int rtos_semaphore_get_count(rtos_semaphore semaphore)
{
    return uxSemaphoreGetCount(semaphore);
}

int rtos_semaphore_wait(rtos_semaphore semaphore, int timeout)
{
    BaseType_t res = pdPASS;

    res = xSemaphoreTake(semaphore, rtos_timeout_2_tickcount(timeout));

    return (res == errQUEUE_EMPTY);
}

int rtos_semaphore_signal(rtos_semaphore semaphore, bool isr)
{
    BaseType_t res;

    if (isr)
    {
        BaseType_t task_woken = pdFALSE;

        res = xSemaphoreGiveFromISR(semaphore, &task_woken);
        portYIELD_FROM_ISR(task_woken);
    }
    else
    {
        res = xSemaphoreGive(semaphore);
    }

    return (res == errQUEUE_FULL);
}


TimerHandle_t rtos_timer_create( const char * const pcTimerName,
                            const TickType_t xTimerPeriodInTicks,
                            const UBaseType_t uxAutoReload,
                            void * const pvTimerID,
                            TimerCallbackFunction_t pxCallbackFunction )
{
    return xTimerCreate(pcTimerName , xTimerPeriodInTicks , uxAutoReload , pvTimerID , pxCallbackFunction);
}

int rtos_timer_start(TimerHandle_t xTimer,TickType_t xTicksToWait, bool isr)
{
    BaseType_t res = pdPASS;
    if (!isr) {
        res = xTimerStart(xTimer, xTicksToWait);
    } else {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        res = xTimerStartFromISR(xTimer, &xHigherPriorityTaskWoken);
        if (xHigherPriorityTaskWoken) {
            taskYIELD();
        }
    }
    return (res == pdFAIL);
}

int rtos_timer_stop(TimerHandle_t xTimer,TickType_t xTicksToWait)
{
    BaseType_t res = pdPASS;
    res = xTimerStop(xTimer,xTicksToWait);

    return (res == pdFAIL);
}

int rtos_timer_stop_isr(TimerHandle_t xTimer)
{
    BaseType_t res = pdPASS;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    res = xTimerStopFromISR(xTimer, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
        taskYIELD();
    }
    return (res == pdFAIL);
}

int rtos_timer_delete(TimerHandle_t xTimer,TickType_t xTicksToWait)
{
    BaseType_t res = pdPASS;
    res = xTimerDelete(xTimer,xTicksToWait);

    return (res == pdFAIL);
}

int rtos_timer_change_period(TimerHandle_t xTimer, TickType_t xNewPeriod,TickType_t xTicksToWait)
{
    BaseType_t res = pdPASS;

    res = xTimerChangePeriod(xTimer, xNewPeriod, xTicksToWait);

    return (res == pdFAIL);
}

int rtos_timer_change_period_isr(TimerHandle_t xTimer, TickType_t xNewPeriod)
{
    BaseType_t res = pdPASS;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    res = xTimerChangePeriodFromISR(xTimer, xNewPeriod, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
        taskYIELD();
    }
    return (res == pdFAIL);
}

int rtos_timer_restart(TimerHandle_t xTimer,TickType_t xTicksToWait, bool isr)
{
    BaseType_t res = pdPASS;
    if (!isr) {
        res = xTimerReset(xTimer, xTicksToWait);
    } else {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        res = xTimerResetFromISR(xTimer, &xHigherPriorityTaskWoken);
        if (xHigherPriorityTaskWoken) {
            taskYIELD();
        }
    }
    return (res == pdFAIL);
}

void *rtos_timer_get_pvTimerID( TimerHandle_t xTimer )
{
    return pvTimerGetTimerID(xTimer);
}


int rtos_mutex_recursive_create(rtos_mutex *mutex)
{
    int res = -1;

    *mutex = xSemaphoreCreateRecursiveMutex();
    if (*mutex != 0)
    {
        res = 0;
    }

    return res;
}

int rtos_mutex_recursive_lock(rtos_mutex mutex)
{
    BaseType_t res = pdPASS;

    res =  xSemaphoreTakeRecursive(mutex, portMAX_DELAY);

    return (res == pdFAIL);
}

int rtos_mutex_recursive_unlock(rtos_mutex mutex)
{
    BaseType_t res = pdPASS;

    res =  xSemaphoreGiveRecursive(mutex);

    return (res == pdFAIL);
}

int rtos_mutex_create(rtos_mutex *mutex)
{
    int res = -1;

    *mutex = xSemaphoreCreateMutex();
    if (*mutex != 0)
    {
        res = 0;
    }

    return res;
}

void rtos_mutex_delete(rtos_mutex mutex)
{
    ASSERT_ERR(xSemaphoreGetMutexHolder(mutex) == NULL);
    vSemaphoreDelete(mutex);
}

int rtos_mutex_lock(rtos_mutex mutex, int timeout)
{
    BaseType_t res = pdPASS;

    res = xSemaphoreTake(mutex, rtos_timeout_2_tickcount(timeout));

    return (res == pdFAIL);
}

int rtos_mutex_unlock(rtos_mutex mutex)
{
    BaseType_t res = pdPASS;

    res = xSemaphoreGive(mutex);

    return (res == pdFAIL);
}

int rtos_event_group_create(rtos_event_group *event_group)
{
    int res = -1;

    *event_group = xEventGroupCreate();
    if (*event_group != 0)
    {
        res = 0;
    }

    return res;
}

void rtos_event_group_delete(rtos_event_group event_group)
{
    vEventGroupDelete(event_group);
}

uint32_t rtos_event_group_get_bits(rtos_event_group event_group, bool isr)
{
    if (isr) {
        return xEventGroupGetBitsFromISR(event_group);
    } else {
        return xEventGroupGetBits(event_group);
    }
}

uint32_t rtos_event_group_wait_bits(rtos_event_group event_group, const uint32_t val,
    const bool clear_on_exit, const bool wait_all_bits, int timeout)
{
    return xEventGroupWaitBits(event_group, val, clear_on_exit, wait_all_bits, rtos_timeout_2_tickcount(timeout));
}

uint32_t rtos_event_group_clear_bits(rtos_event_group event_group, const uint32_t val, bool isr)
{
    if (isr) {
        return xEventGroupClearBitsFromISR(event_group, val);
    } else {
        return xEventGroupClearBits(event_group, val);
    }
}

uint32_t rtos_event_group_set_bits(rtos_event_group event_group, const uint32_t val, bool isr)
{
    uint32_t res;

    if (isr) {
        BaseType_t task_woken = pdFALSE;

        res = xEventGroupSetBitsFromISR(event_group, val, &task_woken);
        portYIELD_FROM_ISR(task_woken);
    } else {
        res = xEventGroupSetBits(event_group, val);
    }

    return res;
}

uint32_t rtos_protect(void)
{
    taskENTER_CRITICAL();
    return 1;
}

void rtos_unprotect(uint32_t protect)
{
    (void) protect;
    taskEXIT_CRITICAL();
}

void rtos_start_scheduler(void)
{
    vTaskStartScheduler();
}

int rtos_init(void)
{
    #if OSAL_TRACE
    memset(task_table, 0, sizeof(task_table));
    #endif

    return 0;
}

#if OSAL_TRACE
/**
 ****************************************************************************************
 * @brief Get task id from task handle
 *
 * @param[in] task Task handle. If NULL use curretn task handle
 * @return id of the task within @ref rtos_task_id.
 ****************************************************************************************
 */
__INLINE int rtos_trace_task_id(void *task)
{
    if (!task)
        task = xTaskGetCurrentTaskHandle();
    int i;

    for (i = 0; i < MAX_TASK; i++)
    {
        if (task == task_table[i])
        {
            return i;
        }
    }

    return UNDEF_TASK;
}
#endif

rtos_task_handle rtos_get_task_handle(void)
{
    return xTaskGetCurrentTaskHandle();
}

rtos_sched_state rtos_get_scheduler_state(void)
{
    return xTaskGetSchedulerState();
}

void rtos_trace_task(int id, void *task)
{
    #if OSAL_TRACE_TASK
    enum rtos_task_id task_id = rtos_trace_task_id(task);

    if (id == RTOS_TRACE_SWITCH_IN)
    {
        dbg("Enter Task %d,%d\n", task_id, rtos_now(false));
    }
    else if (id == RTOS_TRACE_SWITCH_OUT)
    {
        dbg("Exit Task %d,%d\n", task_id, rtos_now(false));
    }
    else if (id == RTOS_TRACE_DELETE)
    {
        dbg("Delete task %d\n", task_id);
    }
    else if (id == RTOS_TRACE_SUSPEND)
    {
        dbg("Suspend task %d\n", task_id);
    }
    else if (id == RTOS_TRACE_RESUME)
    {
        dbg("Resume task %d\n", task_id);
    }
    else if (id == RTOS_TRACE_RESUME_FROM_ISR)
    {
        dbg("Resume from ISR task %d\n", task_id);
    }
    else if (id == RTOS_TRACE_CREATE)
    {
        if ((creating_task_id == UNDEF_TASK) &&
            (task_table[IDLE_TASK] == NULL)
            #if( configSUPPORT_STATIC_ALLOCATION == 0 )
            && (task == xTaskGetIdleTaskHandle())
            #endif
            )
        {
            task_table[IDLE_TASK] = task;
            creating_task_id = IDLE_TASK;
        }
        else if ((creating_task_id == UNDEF_TASK) &&
            (task_table[TMR_DAEMON_TASK] == NULL)
        #if( configSUPPORT_STATIC_ALLOCATION == 0 )
            && (task == xTimerGetTimerDaemonTaskHandle())
        #endif
            )
        {
            task_table[TMR_DAEMON_TASK] = task;
            creating_task_id = TMR_DAEMON_TASK;
        }
        else if (creating_task_id < MAX_TASK)
        {
            task_table[creating_task_id] = task;
        }

        dbg("Create task %d\n", creating_task_id);
        creating_task_id = UNDEF_TASK;
    }
    #endif
}

void rtos_trace_mem(int id, void *ptr, int size, int free_size)
{
    #if OSAL_TRACE_MEM
    enum rtos_task_id task_id = rtos_trace_task_id(NULL);

    if (id == RTOS_TRACE_ALLOC)
    {
        if (ptr == NULL)
        {
            dbg("[%d] Failed to allocate %d bytes. (free_size = %d)\n",
                  task_id, size, free_size);
        }
        #if RTOS_MALLOC_TRACE_LEVEL > 0
        else
        {
            dbg("[%d] Allocate %d bytes at %p. (free_size = %d)\n",
                       task_id, size, (ptr), free_size);
        }
        #endif
    }
    else if (id == RTOS_TRACE_FREE)
    {

        dbg("[%d] Free %d bytes at %p. (free_size = %d)\n",
                   task_id, size, (ptr), free_size);
    }
    #endif
}

void rtos_priority_set(rtos_task_handle handle, rtos_prio priority)
{
    vTaskPrioritySet(handle, priority);
}

#if (configCHECK_FOR_STACK_OVERFLOW > 0)
void vApplicationStackOverflowHook(TaskHandle_t *pxTask, signed char *pcTaskName)
{
    dbg("Stack overflow detected for task "
        #if OSAL_TRACE
        "%d"
        #endif
        "(%x)\n",
            #if OSAL_TRACE
            rtos_trace_task_id(pxTask),
            #endif
            (uint32_t)pxTask);
    dump_mem((uint32_t)pxTask, 20, 4, true);
    ASSERT_ERR(0);
}
#endif /* (configCHECK_FOR_STACK_OVERFLOW > 0) */

#if (PLF_AIC8800)
PRIVATE_HOST_DECLARE(G0RTOS, TickType_t, xTickCount);
#endif

void rtos_data_save(void)
{
    #if (PLF_AIC8800)
    // backup data
    backup_xTickCount = xTaskGetTickCount();
    sleep_data_save();
    #if PLF_AON_SUPPORT
    co_timer_save();
    #endif
    #if PLF_WIFI_STACK
    #ifdef CONFIG_RWNX_LWIP
    fhost_data_save();
    lwip_data_save();
    wpas_data_save();
    ipc_host_flag_save();
    #endif /* CONFIG_RWNX_LWIP */
    #endif /* PLF_WIFI_STACK */
    user_data_save();
    lp_ticker_data_save();
    #if PLF_BT_STACK
    #if PLF_BLE_ONLY
    ble_task_save();
    #endif
    #endif
    #endif
}
