/**
 ****************************************************************************************
 *
 * @file devipc_cmd.h
 *
 * @brief Declares the device ipc command parsing and handling functions
 *
 * Copyright (C) AICSemi 2018-2021
 *
 ****************************************************************************************
 */

#ifndef _DEVIPC_CMD_H_
#define _DEVIPC_CMD_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "cmsis_compiler.h"

/*
 * TYPE DEFINITIONS AND MACROS
 ****************************************************************************************
 */

#define SSID_MAX_LEN                32
#define PASSPHRASE_MAX_LEN          64
#define CUSTOM_MSG_IND_BIT_MASK     (0x01UL << 16)

/// Commands related to device custom message
enum custmsg_cmd_tag
{
    CUST_CMD_GET_VERSION = 0,
    CUST_CMD_GET_SSID,
    CUST_CMD_SET_SSID,
    CUST_CMD_GET_PASS,
    CUST_CMD_SET_PASS,
    CUST_CMD_GET_VAR,
    CUST_CMD_SET_VAR,
    CUST_CMD_MAX
};

/// Indications related to device custom message
enum custmsg_ind_tag
{
    CUST_IND_SAYHI = (CUSTOM_MSG_IND_BIT_MASK | 0),
    CUST_IND_MAX
};

/// Structure containing the parameters of the @ref DBG_CUSTOM_MSG_REQ message.
struct dbg_custom_msg_req
{
    uint32_t cmd;
    uint32_t len;
    uint32_t flags;
    uint32_t buf[1];
};

/// Structure containing the parameters of the @ref DBG_CUSTOM_MSG_REQ message.
struct dbg_custom_msg_cfm
{
    uint32_t cmd;
    uint32_t len;
    uint32_t status;
    uint32_t buf[1];
};

/// Structure containing the parameters of the @ref DBG_CUSTOM_MSG_IND message.
typedef struct dbg_custom_msg_cfm dbg_custom_msg_ind_t;

/// @brief Format of a custom message handler function
typedef int (*cust_msg_func_t)(struct dbg_custom_msg_req *req);

/*
 * FUNCTIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Parse the devipc custom message
 *
 * @param[in] cust_msg  Pointer to the custom message
 ****************************************************************************************
 */
void devipc_custmsg_parser(struct dbg_custom_msg_req *cust_msg);

#endif /* _DEVIPC_CMD_H_ */
