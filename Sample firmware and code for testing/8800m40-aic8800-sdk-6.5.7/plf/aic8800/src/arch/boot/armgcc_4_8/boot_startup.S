/* File: startup_ARMCM4.s
 * Purpose: startup file for Cortex-M3/M4 devices. Should use with
 *   GNU Tools for ARM Embedded Processors
 * Version: V1.1
 * Date: 17 June 2011
 *
 * Copyright (C) 2011 ARM Limited. All rights reserved.
 * ARM Limited (ARM) is supplying this software for use with Cortex-M3/M4
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */
    .syntax unified
    .arch armv7-m

/* Memory Model
   The HEAP starts at the end of the DATA section and grows upward.

   The STACK starts at the end of the RAM and grows downward.

   The HEAP and stack STACK are only checked at compile time:
   (DATA_SIZE + HEAP_SIZE + STACK_SIZE) < RAM_SIZE

   This is just a check for the bare minimum for the Heap+Stack area before
   aborting compilation, it is not the run time limit:
   Heap_Size + Stack_Size = 0x80 + 0x80 = 0x100
 */
    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0x800
#endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0x10000
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .space    Heap_Size
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

    .section .isr_vector
    .align 2
    .globl __isr_vector
__isr_vector:
    .long    __StackTop            /* Top of Stack */
    .long    Reset_Handler         /* Reset Handler */
    .long    NMI_Handler           /* NMI Handler */
    .long    HardFault_Handler     /* Hard Fault Handler */
    .long    MemManage_Handler     /* MPU Fault Handler */
    .long    BusFault_Handler      /* Bus Fault Handler */
    .long    UsageFault_Handler    /* Usage Fault Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    SVC_Handler           /* SVCall Handler */
    .long    DebugMon_Handler      /* Debug Monitor Handler */
    .long    0                     /* Reserved */
    .long    PendSV_Handler        /* PendSV Handler */
    .long    SysTick_Handler       /* SysTick Handler */

    /* External interrupts */
    .long   BTAON_IRQHandler            /* 16: BT AON                       */
    .long   WCNAON_IRQHandler           /* 17: WCN AON                      */
    .long   WGEN_IRQHandler             /* 18: WGEN                         */
    .long   WPROTTRIG_IRQHandler        /* 19: WPROTTRIG                    */
    .long   WTXTRIG_IRQHandler          /* 20: WTXTRIG                      */
    .long   WRXTRIG_IRQHandler          /* 21: WRXTRIG                      */
    .long   WTXRXMISC_IRQHandler        /* 22: WTXRXMISC                    */
    .long   WTXRXTIM_IRQHandler         /* 23: WTXRXTIM                     */
    .long   WPHY_IRQHandler             /* 24: WPHY                         */
    .long   BLE_IRQHandler              /* 25: BLE                          */
    .long   BT_IRQHandler               /* 26: BT                           */
    .long   BTDM_IRQHandler             /* 27: BTDM                         */
    .long   FREQ_IRQHandler             /* 28: FREQ                         */
    .long   DMACOMB_IRQHandler          /* 29: DMA Comb                     */
    .long   SDIO_IRQHandler             /* 30: SDIO                         */
    .long   USBDMA_IRQHandler           /* 31: USB DMA                      */
    .long   UART0_IRQHandler            /* 32: UART0                        */
    .long   UART1_IRQHandler            /* 33: UART1                        */
    .long   UART2_IRQHandler            /* 34: UART2                        */
    .long   MCU2WCN0_IRQHandler         /* 35: MCU2WCN                      */
    .long   MCU2WCN1_IRQHandler         /* 36: MCU2WCN                      */
    .long   WCN2MCU0_IRQHandler         /* 37: WCN2MCU                      */
    .long   WCN2MCU1_IRQHandler         /* 38: WCN2MCU                      */
    .long   MCU2WCN0_G1_IRQHandler      /* 39: MCU2WCN G1                   */
    .long   MCU2WCN1_G1_IRQHandler      /* 40: MCU2WCN G1                   */
    .long   WCN2MCU0_G1_IRQHandler      /* 41: WCN2MCU G1                   */
    .long   WCN2MCU1_G1_IRQHandler      /* 42: WCN2MCU G1                   */
    .long   TIMER20_IRQHandler          /* 43: Timer                        */
    .long   TIMER21_IRQHandler          /* 44: Timer                        */
    .long   TIMER22_IRQHandler          /* 45: Timer                        */
    .long   WDT3_IRQHandler             /* 46: WDT                          */
    .long   ASDMA_CMN_IRQHandler        /* 47: ASDMA Common                 */
    .long   ASDMA_GE_SW_IRQHandler      /* 48: ASDMA Generic SW             */
    .long   ASDMA_AUDIO_IRQHandler      /* 49: ASDMA Audio Channel          */
    .long   ASDMA_GE_HW_IRQHandler      /* 50: ASDMA Generic HW             */
    .long   ASDMA_DMAC_IRQHandler       /* 51: ASDMA Dmac                   */
    .long   AUD_PROC_IRQHandler         /* 52: Audio Process                */
    .long   DMA00_IRQHandler            /* 53: DMA                          */
    .long   DMA01_IRQHandler            /* 54: DMA                          */
    .long   DMA02_IRQHandler            /* 55: DMA                          */
    .long   DMA03_IRQHandler            /* 56: DMA                          */
    .long   DMA04_IRQHandler            /* 57: DMA                          */
    .long   DMA05_IRQHandler            /* 58: DMA                          */
    .long   DMA06_IRQHandler            /* 59: DMA                          */
    .long   DMA07_IRQHandler            /* 60: DMA                          */
    .long   DMA08_IRQHandler            /* 61: DMA                          */
    .long   DMA09_IRQHandler            /* 62: DMA                          */
    .long   DMA10_IRQHandler            /* 63: DMA                          */
    .long   DMA11_IRQHandler            /* 64: DMA                          */
    .long   DMA12_IRQHandler            /* 65: DMA                          */
    .long   DMA13_IRQHandler            /* 66: DMA                          */
    .long   MCU2WCN2_IRQHandler         /* 67: MCU2WCN                      */
    .long   MCU2WCN3_IRQHandler         /* 68: MCU2WCN                      */
    .long   WCN2MCU2_IRQHandler         /* 69: WCN2MCU                      */
    .long   WCN2MCU3_IRQHandler         /* 70: WCN2MCU                      */
    .long   MCU2WCN2_G1_IRQHandler      /* 71: MCU2WCN G1                   */
    .long   MCU2WCN3_G1_IRQHandler      /* 72: MCU2WCN G1                   */
    .long   WCN2MCU2_G1_IRQHandler      /* 73: WCN2MCU G1                   */
    .long   WCN2MCU3_G1_IRQHandler      /* 74: WCN2MCU G1                   */
    .long   TIMER00_IRQHandler          /* 75: Timer                        */
    .long   TIMER01_IRQHandler          /* 76: Timer                        */
    .long   TIMER02_IRQHandler          /* 77: Timer                        */
    .long   TIMER10_IRQHandler          /* 78: Timer                        */
    .long   TIMER11_IRQHandler          /* 79: Timer                        */
    .long   TIMER12_IRQHandler          /* 80: Timer                        */
    .long   GPIO_IRQHandler             /* 81: GPIO                         */
    .long   WDT0_IRQHandler             /* 82: WDT                          */
    .long   WDT1_IRQHandler             /* 83: WDT                          */
    .long   WDT2_IRQHandler             /* 84: WDT                          */
    .long   SPI0_IRQHandler             /* 85: SPI                          */
    .long   TRNG_IRQHandler             /* 86: TRNG                         */
    .long   I2CM_IRQHandler             /* 87: I2CM                         */
    .long   I2CS_IRQHandler             /* 88: I2CS                         */
    .long   CACHE0_IRQHandler           /* 89: CACHE                        */
    .long   CACHE1_IRQHandler           /* 90: CACHE                        */
    .long   PSRAM_IRQHandler            /* 91: PSRAM                        */
    .long   SDMMC_IRQHandler            /* 92: SDMMC                        */
    .long   PSIM_IRQHandler             /* 93: PSIM                         */
    .long   PWRCTRL_IRQHandler          /* 94: PWRCTRL                      */
    .long   PMIC_IRQHandler             /* 95: PMIC                         */


    .size   __isr_vector, . - __isr_vector

    .text
    .thumb
    .align 2
    .globl Image_Info
Image_Info:
    .long   0x474D4946                  /* Magic number, "FIMG" */
    .long   __image_end__               /* End address of flash image */
    #ifdef CFG_VER_STR
    .long   __code_start__              /* Start address of flash image */
    .long   usr_build_date              /* Start Address of SDK version string */
    #else
    #ifdef CFG_M2D_OTA
    .long   __code_start__              /* Start address of flash image */
    .long   usr_build_date              /* Start Address of SDK version string */
    #else
    .long   0xFFFFFFFF
    .long   0xFFFFFFFF
    #endif
    #endif
    .size   Image_Info, . - Image_Info

    .text
    .thumb
    .thumb_func
    .align 2
    .globl  Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      _etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr     r0, =__StackTop
    msr     msp, r0

/* text copy start */
    ldr     r1, =__etext_irom
    ldr     r2, =__ramtext_start__
    ldr     r3, =__ramtext_end__

.Lirom_to_iram_loop:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .Lirom_to_iram_loop

/* data copy start */
    ldr     r1, =__etext
    ldr     r2, =__data_start__
    ldr     r3, =__data_end__

.Lirom_to_dram_loop:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .Lirom_to_dram_loop

/* bss clear start */
    mov     r1, #0
    ldr     r2, =__bss_start__
    ldr     r3, =__bss_end__

.Lclear_bss_loop:
    cmp     r2, r3
    itt     lt
    strlt   r1, [r2], #4
    blt    .Lclear_bss_loop
/* bss clear end */

#ifdef CFG_USB_MEM
    ldr     r1, =__etext_plus_data_end__
    ldr     r2, =__usb_data_start__
    ldr     r3, =__usb_data_end__

.Liram_to_usb_dram_loop:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .Liram_to_usb_dram_loop

/* usb bss clear start */
    mov     r1, #0
    ldr     r2, =__usb_bss_start__
    ldr     r3, =__usb_bss_end__

.Lclear_usb_bss_loop:
    cmp     r2, r3
    itt     lt
    strlt   r1, [r2], #4
    blt    .Lclear_usb_bss_loop
/* usb bss clear end */
#endif /* CFG_USB_MEM */
    ldr     r0, =NVIC_Vectors_Init
    blx     r0
    ldr     r0, =SystemInit
    blx     r0
    #if defined(CFG_STDLIB)
    ldr     r0, =_start
    #else
    ldr     r0, =rw_main
    #endif
    bx      r0

    .pool
    .size Reset_Handler, . - Reset_Handler

    .text
/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_default_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
    b    .
    .size    \handler_name, . - \handler_name
    .endm

    def_default_handler    NMI_Handler
    def_default_handler    HardFault_Handler
    def_default_handler    MemManage_Handler
    def_default_handler    BusFault_Handler
    def_default_handler    UsageFault_Handler
    def_default_handler    SVC_Handler
    def_default_handler    DebugMon_Handler
    def_default_handler    PendSV_Handler
    def_default_handler    SysTick_Handler
    def_default_handler    Default_Handler

    .macro    def_irq_default_handler    handler_name
    .weak     \handler_name
    .set      \handler_name, Default_Handler
    .endm

    def_irq_default_handler     BTAON_IRQHandler
    def_irq_default_handler     WCNAON_IRQHandler
    def_irq_default_handler     WGEN_IRQHandler
    def_irq_default_handler     WPROTTRIG_IRQHandler
    def_irq_default_handler     WTXTRIG_IRQHandler
    def_irq_default_handler     WRXTRIG_IRQHandler
    def_irq_default_handler     WTXRXMISC_IRQHandler
    def_irq_default_handler     WTXRXTIM_IRQHandler
    def_irq_default_handler     WPHY_IRQHandler
    def_irq_default_handler     BLE_IRQHandler
    def_irq_default_handler     BT_IRQHandler
    def_irq_default_handler     BTDM_IRQHandler
    def_irq_default_handler     FREQ_IRQHandler
    def_irq_default_handler     DMACOMB_IRQHandler
    def_irq_default_handler     SDIO_IRQHandler
    def_irq_default_handler     USBDMA_IRQHandler
    def_irq_default_handler     UART0_IRQHandler
    def_irq_default_handler     UART1_IRQHandler
    def_irq_default_handler     UART2_IRQHandler
    def_irq_default_handler     MCU2WCN0_IRQHandler
    def_irq_default_handler     MCU2WCN1_IRQHandler
    def_irq_default_handler     WCN2MCU0_IRQHandler
    def_irq_default_handler     WCN2MCU1_IRQHandler
    def_irq_default_handler     MCU2WCN0_G1_IRQHandler
    def_irq_default_handler     MCU2WCN1_G1_IRQHandler
    def_irq_default_handler     WCN2MCU0_G1_IRQHandler
    def_irq_default_handler     WCN2MCU1_G1_IRQHandler
    def_irq_default_handler     TIMER20_IRQHandler
    def_irq_default_handler     TIMER21_IRQHandler
    def_irq_default_handler     TIMER22_IRQHandler
    def_irq_default_handler     WDT3_IRQHandler
    def_irq_default_handler     ASDMA_CMN_IRQHandler
    def_irq_default_handler     ASDMA_GE_SW_IRQHandler
    def_irq_default_handler     ASDMA_AUDIO_IRQHandler
    def_irq_default_handler     ASDMA_GE_HW_IRQHandler
    def_irq_default_handler     ASDMA_DMAC_IRQHandler
    def_irq_default_handler     AUD_PROC_IRQHandler
    def_irq_default_handler     DMA00_IRQHandler
    def_irq_default_handler     DMA01_IRQHandler
    def_irq_default_handler     DMA02_IRQHandler
    def_irq_default_handler     DMA03_IRQHandler
    def_irq_default_handler     DMA04_IRQHandler
    def_irq_default_handler     DMA05_IRQHandler
    def_irq_default_handler     DMA06_IRQHandler
    def_irq_default_handler     DMA07_IRQHandler
    def_irq_default_handler     DMA08_IRQHandler
    def_irq_default_handler     DMA09_IRQHandler
    def_irq_default_handler     DMA10_IRQHandler
    def_irq_default_handler     DMA11_IRQHandler
    def_irq_default_handler     DMA12_IRQHandler
    def_irq_default_handler     DMA13_IRQHandler
    def_irq_default_handler     MCU2WCN2_IRQHandler
    def_irq_default_handler     MCU2WCN3_IRQHandler
    def_irq_default_handler     WCN2MCU2_IRQHandler
    def_irq_default_handler     WCN2MCU3_IRQHandler
    def_irq_default_handler     MCU2WCN2_G1_IRQHandler
    def_irq_default_handler     MCU2WCN3_G1_IRQHandler
    def_irq_default_handler     WCN2MCU2_G1_IRQHandler
    def_irq_default_handler     WCN2MCU3_G1_IRQHandler
    def_irq_default_handler     TIMER00_IRQHandler
    def_irq_default_handler     TIMER01_IRQHandler
    def_irq_default_handler     TIMER02_IRQHandler
    def_irq_default_handler     TIMER10_IRQHandler
    def_irq_default_handler     TIMER11_IRQHandler
    def_irq_default_handler     TIMER12_IRQHandler
    def_irq_default_handler     GPIO_IRQHandler
    def_irq_default_handler     WDT0_IRQHandler
    def_irq_default_handler     WDT1_IRQHandler
    def_irq_default_handler     WDT2_IRQHandler
    def_irq_default_handler     SPI0_IRQHandler
    def_irq_default_handler     TRNG_IRQHandler
    def_irq_default_handler     I2CM_IRQHandler
    def_irq_default_handler     I2CS_IRQHandler
    def_irq_default_handler     CACHE0_IRQHandler
    def_irq_default_handler     CACHE1_IRQHandler
    def_irq_default_handler     PSRAM_IRQHandler
    def_irq_default_handler     SDMMC_IRQHandler
    def_irq_default_handler     PSIM_IRQHandler
    def_irq_default_handler     PWRCTRL_IRQHandler
    def_irq_default_handler     PMIC_IRQHandler

    .end
