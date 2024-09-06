/**
 ****************************************************************************************
 *
 * @file boot.h
 *
 * @brief This file contains the declarations of the boot related variables.
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 *
 ****************************************************************************************
 */

#ifndef _BOOT_H_
#define _BOOT_H_

extern const uint32_t   __end__[];
extern const uint32_t   __HeapLimit[];
#define HEAP_BASE       __end__
#define HEAP_LIMIT      __HeapLimit

extern const uint32_t   __StackLimit[];
extern const uint32_t   __StackTop[];

#endif // _BOOT_H_
