/**
 ****************************************************************************************
 *
 * @file chip.h
 *
 ****************************************************************************************
 */

#ifndef _CHIP_H_
#define _CHIP_H_

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M4 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn           = -14,      /*!< 2 Non Maskable Interrupt                         */
  MemoryManagement_IRQn         = -12,      /*!< 4 Memory Management Interrupt                    */
  BusFault_IRQn                 = -11,      /*!< 5 Bus Fault Interrupt                            */
  UsageFault_IRQn               = -10,      /*!< 6 Usage Fault Interrupt                          */
  SVCall_IRQn                   = -5,       /*!< 11 SV Call Interrupt                             */
  DebugMonitor_IRQn             = -4,       /*!< 12 Debug Monitor Interrupt                       */
  PendSV_IRQn                   = -2,       /*!< 14 Pend SV Interrupt                             */
  SysTick_IRQn                  = -1,       /*!< 15 System Tick Interrupt                         */

/******  Chip Specific Interrupt Numbers **********************************************************/
  BTAON_IRQn                    = 0,        /*!< BT AON Interrupt                                 */
  WCNAON_IRQn                   = 1,        /*!< WCN AON Interrupt                                */
  WGEN_IRQn                     = 2,        /*!< WiFi gen Interrupt                               */
  WPROTTRIG_IRQn                = 3,        /*!< WiFi prottrigger Interrupt                       */
  WTXTRIG_IRQn                  = 4,        /*!< WiFi txtrigger Interrupt                         */
  WRXTRIG_IRQn                  = 5,        /*!< WiFi rxtrigger Interrupt                         */
  WTXRXMISC_IRQn                = 6,        /*!< WiFi txrxmisc Interrupt                          */
  WTXRXTIM_IRQn                 = 7,        /*!< WiFi txrtimer Interrupt                          */
  WPHY_IRQn                     = 8,        /*!< WiFi PHY Interrupt                               */
  WRIU_IRQn                     = 9,        /*!< WiFi RIU Interrupt                               */
  BLE_IRQn                      = 10,       /*!< BLE Interrupt                                    */
  BT_IRQn                       = 11,       /*!< BT Interrupt                                     */
  BTDM_IRQn                     = 12,       /*!< BTDM Interrupt                                   */
  FREQ_IRQn                     = 13,       /*!< FREQ Interrupt                                   */
  BTDMA_IRQn                    = 14,       /*!< BT DMA Interrupt                                 */
  UART0_IRQn                    = 15,       /*!< UART Interrupt                                   */
  UART1_IRQn                    = 16,       /*!< UART Interrupt                                   */
  UART2_IRQn                    = 17,       /*!< UART Interrupt                                   */
  MCU2WCN0_G1_IRQn              = 18,       /*!< MCU2WCN Interrupt                                */
  TIMER20_IRQn                  = 19,       /*!< Timer Interrupt                                  */
  TIMER21_IRQn                  = 20,       /*!< Timer Interrupt                                  */
  TIMER22_IRQn                  = 21,       /*!< Timer Interrupt                                  */
  TIMER23_IRQn                  = 22,       /*!< Timer Interrupt                                  */
  GPIOB_IRQn                    = 23,       /*!< GPIO Interrupt                                   */
  WDT2_IRQn                     = 24,       /*!< WDT Interrupt                                    */
  PCIE_HOST_DMA_IRQn            = 25,       /*!< PCIE Host DMA Interrupt                          */
  PWRCTRL_IRQn                  = 26,       /*!< Power Control Interrupt                          */
  AONPWM_IRQn                   = 27,       /*!< AON PWM Interrupt                                */
  PMU_RTC0_IRQn                 = 28,       /*!< PMU RTC Interrupt                                */
  PMU_RTC1_IRQn                 = 29,       /*!< PMU RTC Interrupt                                */
  PMIC_IRQn                     = 30,       /*!< PMIC Interrupt                                   */
  BT_TIMER_IRQn                 = 31,       /*!< BT Timer Interrupt                               */
  BT_UART_IRQn                  = 32,       /*!< BT UART Interrupt                                */
  BT_WDT_IRQn                   = 33,       /*!< BT WDT Interrupt                                 */
  MCU2WCN0_IRQn                 = 34,       /*!< MCU2WCN Interrupt                                */
  MCU2WCN1_IRQn                 = 35,       /*!< MCU2WCN Interrupt                                */
  MCU2WCN2_IRQn                 = 36,       /*!< MCU2WCN Interrupt                                */
  MCU2WCN3_IRQn                 = 37,       /*!< MCU2WCN Interrupt                                */
  WCN2MCU0_IRQn                 = 38,       /*!< WCN2MCU Interrupt                                */
  WCN2MCU1_IRQn                 = 39,       /*!< WCN2MCU Interrupt                                */
  WCN2MCU2_IRQn                 = 40,       /*!< WCN2MCU Interrupt                                */
  WCN2MCU3_IRQn                 = 41,       /*!< WCN2MCU Interrupt                                */
  MCU2WCN1_G1_IRQn              = 42,       /*!< MCU2WCN Interrupt                                */
  MCU2WCN2_G1_IRQn              = 43,       /*!< MCU2WCN Interrupt                                */
  MCU2WCN3_G1_IRQn              = 44,       /*!< MCU2WCN Interrupt                                */
  WCN2MCU0_G1_IRQn              = 45,       /*!< WCN2MCU Interrupt                                */
  WCN2MCU1_G1_IRQn              = 46,       /*!< WCN2MCU Interrupt                                */
  WCN2MCU2_G1_IRQn              = 47,       /*!< WCN2MCU Interrupt                                */
  WCN2MCU3_G1_IRQn              = 48,       /*!< WCN2MCU Interrupt                                */
  DMACOMB_IRQn                  = 49,       /*!< DMA Comb Interrupt                               */
  DMA00_IRQn                    = 50,       /*!< DMA Interrupt                                    */
  DMA01_IRQn                    = 51,       /*!< DMA Interrupt                                    */
  DMA02_IRQn                    = 52,       /*!< DMA Interrupt                                    */
  DMA03_IRQn                    = 53,       /*!< DMA Interrupt                                    */
  DMA04_IRQn                    = 54,       /*!< DMA Interrupt                                    */
  DMA05_IRQn                    = 55,       /*!< DMA Interrupt                                    */
  DMA06_IRQn                    = 56,       /*!< DMA Interrupt                                    */
  DMA07_IRQn                    = 57,       /*!< DMA Interrupt                                    */
  DMA08_IRQn                    = 58,       /*!< DMA Interrupt                                    */
  DMA09_IRQn                    = 59,       /*!< DMA Interrupt                                    */
  DMA10_IRQn                    = 60,       /*!< DMA Interrupt                                    */
  DMA11_IRQn                    = 61,       /*!< DMA Interrupt                                    */
  DMA12_IRQn                    = 62,       /*!< DMA Interrupt                                    */
  DMA13_IRQn                    = 63,       /*!< DMA Interrupt                                    */
  USBDMA_IRQn                   = 64,       /*!< USB DMA Interrupt                                */
  SDIO_IRQn                     = 65,       /*!< SDIO Interrupt                                   */
  AUD_PROC_IRQn                 = 66,       /*!< Audio Process Interrupt                          */
  TIMER00_IRQn                  = 67,       /*!< Timer Interrupt                                  */
  TIMER01_IRQn                  = 68,       /*!< Timer Interrupt                                  */
  TIMER02_IRQn                  = 69,       /*!< Timer Interrupt                                  */
  TIMER10_IRQn                  = 70,       /*!< Timer Interrupt                                  */
  TIMER11_IRQn                  = 71,       /*!< Timer Interrupt                                  */
  TIMER12_IRQn                  = 72,       /*!< Timer Interrupt                                  */
  PWM_IRQn                      = 73,       /*!< PWM Interrupt                                    */
  GPIOA_IRQn                    = 74,       /*!< GPIOA Interrupt                                  */
  WDT0_IRQn                     = 75,       /*!< WDT Interrupt                                    */
  WDT1_IRQn                     = 76,       /*!< WDT Interrupt                                    */
  SPI_IRQn                      = 77,       /*!< SPI Interrupt                                    */
  PCIE_IRQn                     = 78,       /*!< PCIe Interrupt                                   */
  TRNG_IRQn                     = 79,       /*!< TRNG Interrupt                                   */
  I2CM_IRQn                     = 80,       /*!< I2C Master Interrupt                             */
  SDMMC_IRQn                    = 81,       /*!< SDMMC Interrupt                                  */
  PSIM_IRQn                     = 82,       /*!< PSI Master Interrupt                             */
  CACHE_IRQn                    = 83,       /*!< Cache Interrupt                                  */
  USBPHY_IRQn                   = 84,       /*!< USB PHY Interrupt                                */
  CM_RF_INTF_IRQn               = 85,       /*!< CM RF Interface Interrupt                        */
  NVIC_USER_IRQ_NUMBER                      /*!< User Interrupt Number                            */
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M4 Processor and Core Peripherals */
#define __MPU_PRESENT             1         /*!< MPU present or not                               */
#define __FPU_PRESENT             1         /*!< FPU present or not                               */
#define __NVIC_PRIO_BITS          6         /*!< Number of Bits used for Priority Levels          */
#define __NVIC_PRIO_LOWEST        0x3F      /*!< The lowest NVIC priority                         */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */


#include "core_cm4.h"                       /* Cortex-M4 processor and core peripherals           */


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define AIC_ROM_BASE          (0x00000000UL)
#define AIC_FLASH_MEM_BASE    (0x04000000UL)
#define AIC_CACHE_MEM_BASE    (0x08000000UL)
#define AIC_AHB0_BASE         (0x40000000UL)
#define AIC_APB0_BASE         (0x40100000UL)
#define AIC_AHB2_BASE         (0x40200000UL)
#define AIC_WLANREG_BASE      (0x40300000UL)
#define AIC_AHB1_BASE         (0x40500000UL)
#define AIC_APB1_BASE         (AIC_AHB1_BASE)
#define AIC_BTREG_BASE        (0x40600000UL)
#define AIC_PCIE_DBI_BASE     (0x40700000UL)
#define AIC_PCIE_CTRL_BASE    (0x40780000UL)
#define AIC_AUD1K_REG_BASE    (0x50000000UL)
#define AIC_PCIE_SLV_BASE     (0x60000000UL)
#define AIC_PMIC_REG_BASE     (0x70000000UL)

/* AHB0 peripherals                                                           */
#define AIC_CACHE_BASE        (AIC_AHB0_BASE + 0x00000)
#define AIC_DMA_BASE          (AIC_AHB0_BASE + 0x20000)
#define AIC_CPUP_TRAP_BASE    (AIC_AHB0_BASE + 0x30000)
#define AIC_CPUS0_TRAP_BASE   (AIC_AHB0_BASE + 0x31000)
#define AIC_UART0_BASE        (AIC_AHB0_BASE + 0x32000)
#define AIC_UART1_BASE        (AIC_AHB0_BASE + 0x33000)
#define AIC_UART2_BASE        (AIC_AHB0_BASE + 0x34000)
#define AIC_IPCAPP_BASE       (AIC_AHB0_BASE + 0x35000)
#define AIC_IPCEMB_BASE       (AIC_AHB0_BASE + 0x35100)
#define AIC_SDMMC_BASE        (AIC_AHB0_BASE + 0x36000)
#define AIC_AUDPROC_BASE      (AIC_AHB0_BASE + 0x37000)

/* APB0 peripherals                                                           */
#define AIC_CPUSYSCTRL_BASE   (AIC_APB0_BASE + 0x00000)
#define AIC_PWM_BASE          (AIC_APB0_BASE + 0x01000)
#define AIC_I2CM0_BASE        (AIC_APB0_BASE + 0x02000)
#define AIC_WDT0_BASE         (AIC_APB0_BASE + 0x03000)
#define AIC_WDT1_BASE         (AIC_APB0_BASE + 0x04000)
#define AIC_SPI0_BASE         (AIC_APB0_BASE + 0x05000)
#define AIC_TIM0_BASE         (AIC_APB0_BASE + 0x06000)
#define AIC_TIM1_BASE         (AIC_APB0_BASE + 0x07000)
#define AIC_TRNG_BASE         (AIC_APB0_BASE + 0x08000)
#define AIC_ANAR0_BASE        (AIC_APB0_BASE + 0x09000)
#define AIC_PMON_BASE         (AIC_APB0_BASE + 0x0A000)
#define AIC_GPIOA_BASE        (AIC_APB0_BASE + 0x0B000)
#define AIC_MSADC_BASE        (AIC_APB0_BASE + 0x0D000)

/* APB1 peripherals                                                           */
#define AIC_AONSYSCTRL_BASE   (AIC_APB1_BASE + 0x00000)
#define AIC_TIM2_BASE         (AIC_APB1_BASE + 0x01000)
#define AIC_ANAR1_BASE        (AIC_APB1_BASE + 0x02000)
#define AIC_PSIM_BASE         (AIC_APB1_BASE + 0x03000)
#define AIC_IOMUX_BASE        (AIC_APB1_BASE + 0x04000)
#define AIC_GPIOB_BASE        (AIC_APB1_BASE + 0x05000)
#define AIC_PWRCTRL_BASE      (AIC_APB1_BASE + 0x06000)
#define AIC_AONPWM_BASE       (AIC_APB1_BASE + 0x07000)
#define AIC_WDT2_BASE         (AIC_APB1_BASE + 0x08000)
#define AIC_CM_RF_INTF_BASE   (AIC_APB1_BASE + 0x09000)

/* AHB2 peripherals                                                           */
#define AIC_USB_BASE          (AIC_AHB2_BASE + 0x00000)
#define AIC_SDIO_BASE         (AIC_AHB2_BASE + 0x40000)
#define AIC_MMSYS_CTRL_BASE   (AIC_AHB2_BASE + 0x41000)

/* PMIC peripherals                                                           */
#define AIC_PMU_RTC0_BASE       (AIC_PMIC_REG_BASE + 0x00000)
#define AIC_PMU_RTC1_BASE       (AIC_PMIC_REG_BASE + 0x01000)
#define AIC_WDT4_BASE           (AIC_PMIC_REG_BASE + 0x01400)
#define AIC_DCDC_COMMON_BASE    (AIC_PMIC_REG_BASE + 0x02000)
#define AIC_DCDC_RFCTRL_BASE    (AIC_PMIC_REG_BASE + 0x02100)
#define AIC_DCDC_CORECTRL_BASE  (AIC_PMIC_REG_BASE + 0x02200)

#endif // _CHIP_H_
