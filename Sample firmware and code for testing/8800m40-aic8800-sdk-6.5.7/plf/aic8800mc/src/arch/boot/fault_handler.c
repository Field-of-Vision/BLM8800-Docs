/* mbed Microcontroller Library
 * Copyright (c) 2006-2018 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "chip.h"
#include "dbg.h"
#include "stdio_uart.h"
#if PLF_CONSOLE
#include "console.h"
#endif
#if (PLF_PMIC)
#include "pmic_api.h"
#endif
#include "wdt_api.h"
#include "reg_ipc_mutex.h"

#define mbed_error_printf dbg

/** MBED_NOINLINE
 *  Declare a function that must not be inlined.
 *
 *  @code
 *  #include "mbed_toolchain.h"
 *
 *  MBED_NOINLINE void foo() {
 *
 *  }
 *  @endcode
 */
#ifndef MBED_NOINLINE
#if defined(__GNUC__) || defined(__clang__) || defined(__CC_ARM)
#define MBED_NOINLINE __attribute__((noinline))
#elif defined(__ICCARM__)
#define MBED_NOINLINE _Pragma("inline=never")
#else
#define MBED_NOINLINE
#endif
#endif

#ifdef CFG_FHDLR
//Fault context struct
//WARNING: DO NOT CHANGE THIS STRUCT WITHOUT MAKING CORRESPONDING CHANGES in except.S files.
//Offset of these registers are used by fault handler in except.S
typedef struct {
  uint32_t R0_reg;
  uint32_t R1_reg;
  uint32_t R2_reg;
  uint32_t R3_reg;
  uint32_t R4_reg;
  uint32_t R5_reg;
  uint32_t R6_reg;
  uint32_t R7_reg;
  uint32_t R8_reg;
  uint32_t R9_reg;
  uint32_t R10_reg;
  uint32_t R11_reg;
  uint32_t R12_reg;
  uint32_t SP_reg;
  uint32_t LR_reg;
  uint32_t PC_reg;
  uint32_t xPSR;
  uint32_t PSP;
  uint32_t MSP;
  uint32_t EXC_RETURN;
  uint32_t CONTROL;
} mbed_fault_context_t;

typedef union {
  struct {
    union {
      struct {
        uint8_t IACCVIOL    :1;
        uint8_t DACCVIOL    :1;
        uint8_t             :1;
        uint8_t MUNSTKERR   :1;
        uint8_t MSTKERR     :1;
        uint8_t MLSPERR     :1;
        uint8_t             :1;
        uint8_t MMARVALID   :1;
      } MMFSR;
      uint8_t BYTE_MMFSR;
    };
    union {
      struct {
        uint8_t IBUSERR     :1;
        uint8_t PRECISERR   :1;
        uint8_t IMPRECISERR :1;
        uint8_t UNSTKERR    :1;
        uint8_t STKERR      :1;
        uint8_t LSPERR      :1;
        uint8_t             :1;
        uint8_t BFARVALID   :1;
      } BFSR;
      uint8_t BYTE_BFSR;
    };
    union {
      struct {
        uint16_t UNDEFINSTR :1;
        uint16_t INVSTATE   :1;
        uint16_t INVPC      :1;
        uint16_t NOCP       :1;
        uint16_t            :4;
        uint16_t UNALIGNED  :1;
        uint16_t DIVBYZERO  :1;
        uint16_t            :6;
      } UFSR;
      uint16_t HALFWORD_UFSR;
    };
  };
  uint32_t WORD;
} SCB_CFSR_REG_t;

//Fault type definitions
//WARNING: DO NOT CHANGE THESE VALUES WITHOUT MAKING CORRESPONDING CHANGES in except.S files.
#define HARD_FAULT_EXCEPTION       (0x10) //Keep some gap between values for any future insertion/expansion
#define MEMMANAGE_FAULT_EXCEPTION  (0x20)
#define BUS_FAULT_EXCEPTION        (0x30)
#define USAGE_FAULT_EXCEPTION      (0x40)

//Functions Prototypes
void print_context_info(void);
void panic(void);

//Global for populating the context in exception handler
mbed_fault_context_t mbed_fault_context = {0,};

//This is a handler function called from Fault handler to print the error information out.
//This runs in fault context and uses special functions(defined in mbed_rtx_fault_handler.c) to print the information without using C-lib support.
void mbed_fault_handler(uint32_t fault_type, void *mbed_fault_context_in)
{
    while (!ipc_mutex_get(IPC_MUTEX_UART_OUTPUT));  // lock mutex

    mbed_error_printf("\n++ CM4 Fault Handler ++\n\nFaultType: ");

    switch (fault_type) {
      case MEMMANAGE_FAULT_EXCEPTION:
        mbed_error_printf("MemManageFault");
        break;

      case BUS_FAULT_EXCEPTION:
        mbed_error_printf("BusFault");
        break;

      case USAGE_FAULT_EXCEPTION:
        mbed_error_printf("UsageFault");
        break;

      //There is no way we can hit this code without getting an exception, so we have the default treated like hardfault
      case HARD_FAULT_EXCEPTION:
      default:
        mbed_error_printf("HardFault");
        break;
    }
    mbed_error_printf("\n\nContext:");
    print_context_info();

    mbed_error_printf("\n\n-- CM4 Fault Handler --\n\n");

    ipc_mutex_set(IPC_MUTEX_UART_OUTPUT, 1);    // unlock mutex

    //Now call panic, to halt the system
    panic();

}

MBED_NOINLINE void print_context_info(void)
{
    SCB_CFSR_REG_t CFSR_reg;

    //Context Regs
    for (int i=0;i<13;i++) {
        mbed_error_printf("\nR%-4d: %08X", i, ((uint32_t *)&mbed_fault_context)[i]);
    }

    mbed_error_printf("\nSP   : %08X"
                      "\nLR   : %08X"
                      "\nPC   : %08X"
                      "\nxPSR : %08X"
                      "\nPSP  : %08X"
                      "\nMSP  : %08X", mbed_fault_context.SP_reg, mbed_fault_context.LR_reg, mbed_fault_context.PC_reg,
                                     mbed_fault_context.xPSR, mbed_fault_context.PSP, mbed_fault_context.MSP );

    //Capture CPUID to get core/cpu info
    mbed_error_printf("\nCPUID: %08X"
                    "\nICSR : %08X"
                    "\nVTOR : %08X"
                    "\nAIRCR: %08X"
                    , SCB->CPUID, SCB->ICSR, SCB->VTOR, SCB->AIRCR);

#if !defined(TARGET_M0) && !defined(TARGET_M0P)
    //Capture fault information registers to infer the cause of exception
    mbed_error_printf("\nSHCSR: %08X"
                    "\nCFSR : %08X"
                    "\nHFSR : %08X"
                    "\nDFSR : %08X"
                    "\nAFSR : %08X"
                    , SCB->SHCSR, SCB->CFSR, SCB->HFSR, SCB->DFSR, SCB->AFSR);

    CFSR_reg.WORD = SCB->CFSR;
    if (CFSR_reg.BYTE_MMFSR) {
        mbed_error_printf("\nMMFSR: %02X"
                        "\n  IACCVIOL :%d\tDACCVIOL :%d"
                        "\n  MUNSTKERR:%d\tMSTKERR  :%d"
                        "\n  MLSPERR  :%d\tMMARVALID:%d"
                        , CFSR_reg.BYTE_MMFSR
                        , CFSR_reg.MMFSR.IACCVIOL,  CFSR_reg.MMFSR.DACCVIOL
                        , CFSR_reg.MMFSR.MUNSTKERR, CFSR_reg.MMFSR.MSTKERR
                        , CFSR_reg.MMFSR.MLSPERR,   CFSR_reg.MMFSR.MMARVALID);
        //Print MMFAR only if its valid as indicated by MMMFSR
        if (CFSR_reg.MMFSR.MMARVALID) {
            mbed_error_printf("\nMMFAR: %08X", SCB->MMFAR);
        }
    }
    if (CFSR_reg.BYTE_BFSR) {
        mbed_error_printf("\nBFSR : %02X"
                        "\n  IBUSERR    :%d\tPRECISERR:%d"
                        "\n  IMPRECISERR:%d\tUNSTKERR :%d"
                        "\n  STKERR     :%d\tLSPERR   :%d"
                        "\n  BFARVALID  :%d"
                        , CFSR_reg.BYTE_BFSR
                        , CFSR_reg.BFSR.IBUSERR,     CFSR_reg.BFSR.PRECISERR
                        , CFSR_reg.BFSR.IMPRECISERR, CFSR_reg.BFSR.UNSTKERR
                        , CFSR_reg.BFSR.STKERR,      CFSR_reg.BFSR.LSPERR
                        , CFSR_reg.BFSR.BFARVALID);
        //Print BFAR only if its valid as indicated by BFSR
        if (CFSR_reg.BFSR.BFARVALID) {
            mbed_error_printf("\nBFAR : %08X", SCB->BFAR);
        }
    }
    if (CFSR_reg.HALFWORD_UFSR) {
        mbed_error_printf("\nUFSR : %04X"
                        "\n  UNDEFINSTR:%d\tINVSTATE :%d"
                        "\n  INVPC     :%d\tNOCP     :%d"
                        "\n  UNALIGNED :%d\tDIVBYZERO:%d"
                        , CFSR_reg.HALFWORD_UFSR
                        , CFSR_reg.UFSR.UNDEFINSTR, CFSR_reg.UFSR.INVSTATE
                        , CFSR_reg.UFSR.INVPC,      CFSR_reg.UFSR.NOCP
                        , CFSR_reg.UFSR.UNALIGNED,  CFSR_reg.UFSR.DIVBYZERO);
        if (CFSR_reg.UFSR.UNDEFINSTR) {
            uint32_t PC_adr0 = mbed_fault_context.PC_reg & ~0x03U;
            uint32_t PC_adr1;
            if ((PC_adr0 >> 24) == (AIC_CACHE_MEM_BASE >> 24)) {
                PC_adr1 = PC_adr0 - (AIC_CACHE_MEM_BASE - AIC_FLASH_MEM_BASE);
            } else {
                PC_adr1 = PC_adr0;
            }
            mbed_error_printf("\nINSTR: [%08X]=%08X, [%08X]=%08X",
                            PC_adr0, *((uint32_t *)PC_adr0), PC_adr1, *((uint32_t *)PC_adr1));
        }
    }
#endif

    //Print Mode
    if (mbed_fault_context.EXC_RETURN & 0x8) {
        mbed_error_printf("\nMode : Thread");
        //Print Priv level in Thread mode - We capture CONTROL reg which reflects the privilege.
        //Note that the CONTROL register captured still reflects the privilege status of the
        //thread mode eventhough we are in Handler mode by the time we capture it.
        if (mbed_fault_context.CONTROL & 0x1) {
            mbed_error_printf("\nPriv : User");
        } else {
            mbed_error_printf("\nPriv : Privileged");
        }
    } else {
        mbed_error_printf("\nMode : Handler");
        mbed_error_printf("\nPriv : Privileged");
    }
    //Print Return Stack
    if (mbed_fault_context.EXC_RETURN & 0x4) {
        mbed_error_printf("\nStack: PSP");
    } else {
        mbed_error_printf("\nStack: MSP");
    }

    mbed_error_printf("\nCNTRL: %08X"
                    "\nPMASK: %08X"
                    "\nFMASK: %08X"
                    "\nBASEP: %08X"
                    , mbed_fault_context.CONTROL, __get_PRIMASK(), __get_FAULTMASK(), __get_BASEPRI());

    if (mbed_fault_context.MSP) {
        int32_t idx;
        uint32_t addr = mbed_fault_context.MSP & ~0x0FUL;
        mbed_error_printf("\nDumpMSP:");
        for (idx = 0; idx < 64; idx++) {
            if (!(addr & 0x0FUL)) {
                mbed_error_printf("\n[%08x]:", addr);
            }
            mbed_error_printf(" %08X", *((uint32_t *)addr));
            addr += 4;
        }
    }

    if (mbed_fault_context.PSP) {
        int32_t idx;
        uint32_t addr = mbed_fault_context.PSP & ~0x0FUL;
        mbed_error_printf("\nDumpPSP:");
        for (idx = 0; idx < 64; idx++) {
            if (!(addr & 0x0FUL)) {
                mbed_error_printf("\n[%08x]:", addr);
            }
            mbed_error_printf(" %08X", *((uint32_t *)addr));
            addr += 4;
        }
    }
}

void panic(void)
{
    unsigned int delay_ticks;
    mbed_error_printf("Panic...\n");
    delay_ticks = wdt_get_pmic_reboot_delay();
    if (delay_ticks) {
        #if (PLF_PMIC)
        mbed_error_printf("pmic_reboot\n");
        pmic_chip_reboot(delay_ticks);
        #endif
    }
    #if PLF_CONSOLE
    while (1) {
        if (stdio_uart_tstc()) {
            char ch = stdio_uart_getc();
            console_handle_char(ch);
            console_schedule();
        }
    }
    #else
    while (1);
    #endif
}

#endif /* CFG_FHDLR */
