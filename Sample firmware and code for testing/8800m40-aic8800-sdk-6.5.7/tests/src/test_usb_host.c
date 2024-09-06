#ifdef CFG_TEST_USB_HOST

/* FatFs includes component */
#include "ff.h"
#include "usbh_diskio.h"
#include "usbh_msc.h"
#include "dbg.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define USB_DRIVE_ID                        "USB:"
#define APPLICATION_STATE_CHANGED           (0x01UL << 0)

/* Private variables ---------------------------------------------------------*/
const char *USBDISKPath = USB_DRIVE_ID "/";
FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
FIL MyFile;                   /* File object */
#if (USBH_USE_OS == 1)
static rtos_task_handle test_task_handle = NULL;
#endif

typedef enum
{
    APPLICATION_IDLE = 0,
    APPLICATION_START,
    APPLICATION_RUNNING,
} MSC_ApplicationTypeDef;

MSC_ApplicationTypeDef Appli_state = APPLICATION_IDLE;

/* Private function prototypes -----------------------------------------------*/
//static void SystemClock_Config(void);
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);
static void MSC_Application(void);


/* Private functions ---------------------------------------------------------*/

void usb_host_test()
{
    #if (USBH_USE_OS == 1)
    test_task_handle = rtos_get_task_handle();
    #endif

    USBH_disk_init(USBH_UserProcess);

    /*##-5- Run Application (Blocking mode) ##################################*/
    while (1)
    {
        #if (USBH_USE_OS == 1)
        unsigned int notification = rtos_task_wait_notification(-1);
        if (notification & APPLICATION_STATE_CHANGED) {
            /* Start app */
            if (APPLICATION_START == Appli_state) {
                MSC_Application();
                Appli_state = APPLICATION_IDLE;
            }
        }
        #else
        /* USB Host Background task */
        USBH_disk_process();

        /* Mass Storage Application State Machine */
        switch (Appli_state)
        {
            case APPLICATION_START:
                MSC_Application();
                Appli_state = APPLICATION_IDLE;
                break;

            case APPLICATION_IDLE:
            default:
                break;
        }
        #endif
    }
}

static void MSC_Application(void)
{
    FRESULT res;                                          /* FatFs function common result code */
    uint32_t byteswritten, bytesread;                     /* File write/read counts */
    char wtext[] = "This is test text";                   /* File write buffer */
    char rtext[100];                                      /* File read buffer */
    char *testfile = USB_DRIVE_ID "/testfile.txt";

    /* Create and Open a new text file object with write access */
    if (f_open(&MyFile, testfile, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
    {
        /* 'TXT' file Open for write Error */
        dbg_test_print("f_open err\r\n");
    }
    else
    {
        /* Write data to the text file */
        res = f_write(&MyFile, wtext, sizeof(wtext), (void *)&byteswritten);

        if ((byteswritten == 0) || (res != FR_OK))
        {
            /* 'TXT' file Write or EOF Error */
            dbg_test_print("f_write err\r\n");
        }
        else
        {
            /* Close the open text file */
            f_close(&MyFile);

            /* Open the text file object with read access */
            if (f_open(&MyFile, testfile, FA_READ) != FR_OK)
            {
                /* 'TXT' file Open for read Error */
                dbg_test_print("f_open err %d\r\n", __LINE__);
            }
            else
            {
                /* Read data from the text file */
                res = f_read(&MyFile, rtext, sizeof(rtext), (void *)&bytesread);

                if ((bytesread == 0) || (res != FR_OK))
                {
                    /* 'TXT' file Read or EOF Error */
                    dbg_test_print("f_read err %d\r\n", __LINE__);
                }
                else
                {
                    dbg_test_print("read: %s\r\n", rtext);
                    /* Close the open text file */
                    f_close(&MyFile);

                    /* Compare read data with the expected data */
                    if ((bytesread != byteswritten))
                    {
                        /* Read data is different from the expected data */
                        dbg_test_print("f_close err %d\r\n", __LINE__);
                    }
                    else
                    {
                        /* Success of the demo: no error occurrence */
                        dbg_test_print("success\r\n");
                    }
                }
            }
        }
    }

    /* Unlink the USB disk I/O driver */
    //FATFS_UnLinkDriver(USBDISKPath);
}

static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{
    switch (id)
    {
        case HOST_USER_SELECT_CONFIGURATION:
            break;

        case HOST_USER_DISCONNECTION:
            Appli_state = APPLICATION_IDLE;
            f_mount(NULL, USBDISKPath, 0);
            #if (USBH_USE_OS == 1)
            if (test_task_handle) {
                rtos_task_notify_setbits(test_task_handle, APPLICATION_STATE_CHANGED, true);
            }
            #endif
            break;

        case HOST_USER_CLASS_ACTIVE:
            dbg_test_print("USBDISKPath %s\r\n", USBDISKPath);
            /* Register the file system object to the FatFs module */
            if (f_mount(&USBDISKFatFs, USBDISKPath, 0) != FR_OK)
            {
                /* FatFs Initialization Error */
                dbg_test_print("f_mount err\r\n");
            } else {
                Appli_state = APPLICATION_START;
                #if (USBH_USE_OS == 1)
                if (test_task_handle) {
                    rtos_task_notify_setbits(test_task_handle, APPLICATION_STATE_CHANGED, false);
                }
                #endif
            }
            break;

        default:
            break;
    }
}

#endif // CFG_TEST_USB_HOST
