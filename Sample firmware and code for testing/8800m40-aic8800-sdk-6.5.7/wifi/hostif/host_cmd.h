/**
 ****************************************************************************************
 *
 * @file host_cmd.h
 *
 * @brief Declares the host command parsing and handling functions
 *
 * Copyright (C) AICSemi 2018-2021
 *
 ****************************************************************************************
 */

#ifndef _HOST_CMD_H_
#define _HOST_CMD_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "cmsis_compiler.h"

#ifdef CFG_DEVICE_IPC
#include "devipc_cmd.h"
#endif
#include "msg.h"

/*
 * TYPE DEFINITIONS AND MACROS
 ****************************************************************************************
 */

/// Task Identifier. Composed by the task type and the task index.
typedef uint16_t ke_task_id_t;

/// Message Identifier. The number of messages is limited to 0xFFFF.
/// The message ID is divided in two parts:
/// - bits[15..10] : task index (no more than 64 tasks supported).
/// - bits[9..0] : message index (no more that 1024 messages per task).
typedef uint16_t ke_msg_id_t;

/// Message structure.
typedef struct {
    void           *hdr;        ///< List header for chaining, reserved
    ke_msg_id_t     id;         ///< Message id.
    ke_task_id_t    dest_id;    ///< Destination kernel identifier.
    ke_task_id_t    src_id;     ///< Source kernel identifier.
    uint16_t        param_len;  ///< Parameter embedded struct length.
    uint32_t        param[1];   ///< Parameter embedded struct. Must be word-aligned.
} ke_msg_t;

#define KE_MSG_HDR_LEN      offsetof(ke_msg_t, param)

/// Status returned by a task when handling a message
enum ke_msg_status_tag
{
    KE_MSG_CONSUMED = 0, ///< consumed, msg and ext are freed by the kernel
    KE_MSG_NO_FREE,      ///< consumed, nothing is freed by the kernel
    KE_MSG_SAVED,        ///< not consumed, will be pushed in the saved queue
};

__INLINE ke_msg_t * ke_param2msg(void const *param_ptr)
{
    return (ke_msg_t *)(((uint8_t *)param_ptr) - KE_MSG_HDR_LEN);
}

__INLINE void * ke_msg2param(ke_msg_t const *msg)
{
    return (void *)(((uint8_t *)msg) + KE_MSG_HDR_LEN);
}

/// Message structure for MSGs from Emb to App
typedef struct
{
    uint16_t id;                ///< Message id.
    uint16_t dummy_dest_id;     ///< Not used
    uint16_t dummy_src_id;      ///< Not used
    uint16_t param_len;         ///< Parameter embedded struct length.
    uint32_t pattern;           ///< Used to stamp a valid MSG buffer
    uint32_t param[1];          ///< Parameter embedded struct. Must be word-aligned.
} e2a_msg_t;

#define E2A_MSG_HDR_LEN     offsetof(e2a_msg_t, param)
/**
 * Define used for MSG buffers validity.
 * This value will be written only when a MSG buffer is used for sending from Emb to App.
 */
#define MSGE2A_VALID_PATTERN    0xADDEDE2A

__INLINE e2a_msg_t * e2a_param2msg(void const *param_ptr)
{
    return (e2a_msg_t *)(((uint8_t *)param_ptr) - E2A_MSG_HDR_LEN);
}

__INLINE void * e2a_msg2param(e2a_msg_t const *msg)
{
    return (void *)(((uint8_t *)msg) + E2A_MSG_HDR_LEN);
}

/// @brief Format of a task message handler function
typedef int (*ke_msg_func_t)(uint16_t const host_type,
                             void const *param,
                             ke_task_id_t const dest_id,
                             ke_task_id_t const src_id);

/// Element of a message handler table.
struct ke_msg_handler
{
    /// Id of the handled message.
    ke_msg_id_t id;
    /// Pointer to the handler function for the msgid above.
    ke_msg_func_t func;
};

/// Element of a state handler table.
struct ke_state_handler
{
    /// Pointer to the message handler table of this state.
    const struct ke_msg_handler *msg_table;
    /// Number of messages handled in this state.
    uint16_t msg_cnt;
};

/*
 * FUNCTIONS
 ****************************************************************************************
 */
void *e2a_msg_alloc(uint16_t const host_type,
                                    ke_msg_id_t const id,
                                    ke_task_id_t const dest_id,
                                    ke_task_id_t const src_id,
                                    uint16_t const param_len);

void e2a_msg_send(uint16_t const host_type, void const *param_ptr);


/**
 ****************************************************************************************
 * @brief Parse the host command
 *
 * @param[in] type  Host type
 * @param[in] cmd   Pointer to the command info
 ****************************************************************************************
 */
void ke_msg_parser(uint16_t host_type, ke_msg_t *ke_msg);

#endif /* _HOST_CMD_H_ */
