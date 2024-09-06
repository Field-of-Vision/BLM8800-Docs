#ifdef CFG_TEST_USBH_VIDEO
#include "usbh_video.h"
#include "usbh_video_stream_parsing.h"
#include "dbg.h"
#if (USBH_USE_OS == 1)
#include "rtos_al.h"
#else
#include "us_ticker_api.h"
#include "ticker_api.h"
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define APPLICATION_STATE_CHANGED           (0x01UL << 0)
#define UVC_FRAMEBUFFER0                    (uvc_fbuf_0)
#define UVC_FRAMEBUFFER1                    (uvc_fbuf_1)

typedef enum {
    APPLICATION_IDLE = 0,
    APPLICATION_START,
    APPLICATION_READY,
    APPLICATION_DISCONNECT,
} ApplicationTypeDef;

/* Private variables ---------------------------------------------------------*/
uint8_t uvc_fbuf_0[UVC_MAX_FRAME_SIZE];
uint8_t uvc_fbuf_1[UVC_MAX_FRAME_SIZE];
USBH_HandleTypeDef hUsbHost;
ApplicationTypeDef Appli_state = APPLICATION_IDLE;
#if (USBH_USE_OS == 1)
static rtos_task_handle test_task_handle = NULL;
#else
const ticker_data_t *us_ticker_data_usbh = NULL;
ticker_event_t us_ticker_event_usbh;
#endif
static rtos_task_handle usb_video_task_handle = NULL;

/* External variables --------------------------------------------------------*/
extern uint8_t uvc_parsing_new_frame_ready;
extern uint8_t* uvc_ready_framebuffer_ptr;
extern uint32_t uvc_ready_frame_length;
extern USBH_VIDEO_TargetFormat_t USBH_VIDEO_Target_Format;


/* Private function prototypes -----------------------------------------------*/
static void USBH_Application(void);
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);


/* Private functions ---------------------------------------------------------*/

/* init function */
void USBH_Test_Init(void)
{
  /* Init Host Library,Add Supported Class and Start the library*/
  USBH_Init(&hUsbHost, USBH_UserProcess, 1); //HOST_FS

  USBH_RegisterClass(&hUsbHost, USBH_VIDEO_CLASS);

  USBH_Start(&hUsbHost);
}

void USBH_Reinit()
{
    USBH_LL_Reinit();
}
void USBH_Test_Task(void)
{
    if (hUsbHost.gState == HOST_CLASS)
    {
        USBH_VIDEO_Process(&hUsbHost);
    }
}

#if (USBH_USE_OS == 0)
/*
 * Background task
*/
static void USBH_Test_Process(void)
{
    /* USB Host Background task */
    USBH_Process(&hUsbHost);

    if (uvc_parsing_new_frame_ready) {
        uvc_parsing_new_frame_ready = 0;
        dbg("frame_len:%d, format:\r\n", uvc_ready_frame_length, USBH_VIDEO_Target_Format);
        dump_mem((uint32_t)uvc_ready_framebuffer_ptr, uvc_ready_frame_length, 1, false);
    }
}

static void usbh_timer_callback(void *param)
{
    USBH_Test_Task();
    ticker_insert_event(us_ticker_data_usbh, &us_ticker_event_usbh, ticker_read(us_ticker_data_usbh) + 100000, 0);
}

#else

static RTOS_TASK_FCT(usbh_task_routine)
{
    while (1) {
        USBH_Test_Task();
        if (uvc_parsing_new_frame_ready) {
            uvc_parsing_new_frame_ready = 0;
            dbg("frame_len:%d, format:%x\r\n", uvc_ready_frame_length, USBH_VIDEO_Target_Format);
            //dump_mem((uint32_t)uvc_ready_framebuffer_ptr, 32, 1, false);
            video_stream_ready_update();
            //rtos_task_suspend(1000);
        }
    }
}

#endif

void usbh_video_test()
{
    #if (USBH_USE_OS == 1)
    test_task_handle = rtos_get_task_handle();
    #else
    #endif

    USBH_Test_Init();
    video_stream_init_buffers((uint8_t*)UVC_FRAMEBUFFER0, (uint8_t*)UVC_FRAMEBUFFER1);

    /*##-5- Run Application (Blocking mode) ##################################*/
    while (1)
    {
        #if (USBH_USE_OS == 1)
        unsigned int notification = rtos_task_wait_notification(-1);
        if (notification & APPLICATION_STATE_CHANGED) {
        dbg("APPLICATION_STATE_CHANGED %d\r\n", Appli_state);
            /* Start app */
            if (APPLICATION_START == Appli_state) {
                USBH_Application();
                //Appli_state = APPLICATION_IDLE;
            } else if (Appli_state == APPLICATION_DISCONNECT) {
                //USBH_Application_deinit();
                USBH_Reinit();
            }
        }
        #else
        /* USB Host Background task */
        USBH_Test_Process();

        /* Mass Storage Application State Machine */
        switch (Appli_state)
        {
            case APPLICATION_START:
                USBH_Application();
                //Appli_state = APPLICATION_IDLE;
                break;

            case APPLICATION_IDLE:
            default:
                break;
        }
        #endif
    }
}

static void USBH_Application(void)
{
    #if (USBH_USE_OS == 1)
    static rtos_task_handle handle = NULL;

    if (handle) {
        return;
    }
    // Create the usbh test task
    if (rtos_task_create(usbh_task_routine, "USBH", 27, 512, NULL, RTOS_TASK_PRIORITY(1), &handle)) {
        dbg("usbh task failed to create\r\n");
        return;
    }
    #else
    // Timer init
    us_ticker_data_usbh = get_us_ticker_data();
    ticker_set_handler(us_ticker_data_usbh, (ticker_event_handler)usbh_timer_callback);
    ticker_insert_event(us_ticker_data_usbh, &us_ticker_event_usbh, ticker_read(us_ticker_data_usbh) + 100000, 0);
    #endif
}

static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{
    switch (id)
    {
        case HOST_USER_SELECT_CONFIGURATION:
            break;

        case HOST_USER_CONNECTION:
            Appli_state = APPLICATION_START;
            #if (USBH_USE_OS == 1)
            if (test_task_handle) {
                rtos_task_notify_setbits(test_task_handle, APPLICATION_STATE_CHANGED, (__get_IPSR() ? true : false));
            }
            #endif
            break;

        case HOST_USER_DISCONNECTION:
            Appli_state = APPLICATION_DISCONNECT;
            #if (USBH_USE_OS == 1)
            if (test_task_handle) {
                rtos_task_notify_setbits(test_task_handle, APPLICATION_STATE_CHANGED, (__get_IPSR() ? true : false));
            }
            #endif
            break;

        case HOST_USER_CLASS_ACTIVE:
            Appli_state = APPLICATION_READY;
            #if (USBH_USE_OS == 1)
            if (test_task_handle) {
                rtos_task_notify_setbits(test_task_handle, APPLICATION_STATE_CHANGED, (__get_IPSR() ? true : false));
            }
            #endif
            break;

        case HOST_USER_CLASS_SELECTED:
            {
                USBH_StatusTypeDef status;
                status = USBH_VS_SetCur(phost, VS_PROBE_CONTROL << 8);
                status = USBH_VS_GetCur(phost, VS_PROBE_CONTROL << 8);
                if (status == USBH_OK)
                {
                    USBH_VS_SetCur(phost, VS_COMMIT_CONTROL << 8);
                    //USBH_VS_GetCur(phost, VS_COMMIT_CONTROL << 8);// not necessary
                }
            }
            break;

        default:
            break;
    }
}

#endif // CFG_TEST_USBH_VIDEO
