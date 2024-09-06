/**
 ****************************************************************************************
 *
 * @file ipc_shared.h
 *
 * @brief Shared data between both IPC modules.
 *
 * Copyright (C) RivieraWaves 2011-2019
 *
 ****************************************************************************************
 */

#ifndef _IPC_SHARED_H_
#define _IPC_SHARED_H_

#include "rwnx_utils.h"
/*
 * DEFINES AND MACROS
 ****************************************************************************************
 */
/*
 * Length used in MSGs structures
 */
#define IPC_A2E_MSG_BUF_SIZE    127 // size in 4-byte words
#ifdef CONFIG_RWNX_FULLMAC
#define IPC_E2A_MSG_SIZE_BASE   256 // size in 4-byte words
#endif

#ifdef CONFIG_RWNX_TL4
#define IPC_E2A_MSG_PARAM_SIZE  (IPC_E2A_MSG_SIZE_BASE + (IPC_E2A_MSG_SIZE_BASE / 2))
#else
#define IPC_E2A_MSG_PARAM_SIZE  IPC_E2A_MSG_SIZE_BASE
#endif

/// Message structure for MSGs from Emb to App
struct ipc_e2a_msg
{
    u16_l id;                ///< Message id.
    u16_l dummy_dest_id;
    u16_l dummy_src_id;
    u16_l param_len;         ///< Parameter embedded struct length.
    u32_l pattern;           ///< Used to stamp a valid MSG buffer
    u32_l param[IPC_E2A_MSG_PARAM_SIZE];  ///< Parameter embedded struct. Must be word-aligned.
};

/// Message structure for MSGs from App to Emb.
/// Actually a sub-structure will be used when filling the messages.
struct ipc_a2e_msg
{
    u32_l dummy_word;                // used to cope with kernel message structure
    u32_l msg[IPC_A2E_MSG_BUF_SIZE]; // body of the msg
};

#endif // _IPC_SHARED_H_
