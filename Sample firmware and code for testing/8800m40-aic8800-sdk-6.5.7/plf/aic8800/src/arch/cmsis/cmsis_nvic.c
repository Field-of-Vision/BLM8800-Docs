/* mbed Microcontroller Library
 * CMSIS-style functionality to support dynamic vectors
 *******************************************************************************
 * Copyright (c) 2011 ARM Limited. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of ARM Limited nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include "cmsis_nvic.h"

#if defined(__ARMCC_VERSION)
extern uint32_t Image$$EXEC_VECTORS$$Base;
extern uint32_t Image$$RAM_VECTORS$$ZI$$Base;
#elif defined(__GNUC__)
extern uint32_t __code_start__;
extern uint32_t __vectors_start__;
#endif

void NVIC_Vectors_Init(void)
{
#if defined(__ARMCC_VERSION)
    uint32_t *old_vectors = (uint32_t *)&Image$$EXEC_VECTORS$$Base;
    uint32_t *new_vectors = (uint32_t *)&Image$$RAM_VECTORS$$ZI$$Base;
#elif defined(__GNUC__)
    uint32_t *old_vectors = (uint32_t *)&__code_start__;
    uint32_t *new_vectors = (uint32_t *)&__vectors_start__;
#endif
    uint32_t i;

    for (i = 0; i < NVIC_NUM_VECTORS; i++) {
        new_vectors[i] = old_vectors[i];
    }

    SCB->VTOR = (uint32_t)new_vectors;
}

