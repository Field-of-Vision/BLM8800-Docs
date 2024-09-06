/**
 ****************************************************************************************
 *
 * @file devipc_cmd.c
 *
 * @brief Implements the device ipc command parsing and handling functions
 *
 * Copyright (C) AICSemi 2018-2021
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "string.h"
#include "devipc_cmd.h"
#include "hostif.h"
//#include "boot.h"
#include "dbg.h"
//#include "sysctrl_api.h"
#include "co_utils.h"
#include "ipc_host.h"

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

uint8_t devipc_apssid[SSID_MAX_LEN]       = {0,};
uint8_t devipc_passwd[PASSPHRASE_MAX_LEN] = {0,};

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief This function handles the @ref CUST_CMD_GET_VERSION command
 *
 * @param[in]    req        Pointer to the custom message request
 * @return       Error id
 ****************************************************************************************
 */
static int
custmsg_get_version_handler(struct dbg_custom_msg_req const *req)
{
    char cur_version[] = "v0.0.1";
    uint8_t cust_msg[offsetof_b(struct dbg_custom_msg_cfm, buf) + sizeof(cur_version)];
    struct dbg_custom_msg_cfm *cfm = (struct dbg_custom_msg_cfm *)cust_msg;
    // Fill the cfm
    cfm->cmd = CUST_CMD_GET_VERSION;
    cfm->len = sizeof(cur_version);
    cfm->status = 0x00; // Success
    memcpy(cfm->buf, cur_version, sizeof(cur_version));
    // Trace the action
    dbg("GET VER: %s\r\n", cur_version);
    // Send confirm
    devipc_custom_msg_push(cfm);
    return 0;
}

/**
 ****************************************************************************************
 * @brief This function handles the @ref CUST_CMD_GET_SSID command
 *
 * @param[in]    req        Pointer to the custom message request
 * @return       Error id
 ****************************************************************************************
 */
static int
custmsg_get_ssid_handler(struct dbg_custom_msg_req const *req)
{
    int ssid_len = strlen((char *)devipc_apssid);
    uint8_t cust_msg[offsetof_b(struct dbg_custom_msg_cfm, buf) + SSID_MAX_LEN];
    struct dbg_custom_msg_cfm *cfm = (struct dbg_custom_msg_cfm *)cust_msg;
    // Fill the cfm
    cfm->cmd = CUST_CMD_GET_SSID;
    cfm->len = ssid_len;
    cfm->status = 0x00; // Success
    memcpy(cfm->buf, devipc_apssid, ssid_len);
    // Trace the action
    dbg("GET SSID: %s\r\n", devipc_apssid);
    // Send confirm
    devipc_custom_msg_push(cfm);
    return 0;
}

/**
 ****************************************************************************************
 * @brief This function handles the @ref CUST_CMD_SET_SSID command
 *
 * @param[in]    req        Pointer to the custom message request
 * @return       Error id
 ****************************************************************************************
 */
static int
custmsg_set_ssid_handler(struct dbg_custom_msg_req const *req)
{
    unsigned int ssid_len = req->len;
    uint8_t cust_msg[offsetof_b(struct dbg_custom_msg_cfm, buf)];
    struct dbg_custom_msg_cfm *cfm = (struct dbg_custom_msg_cfm *)cust_msg;
    // Fill the cfm
    cfm->cmd = CUST_CMD_SET_SSID;
    cfm->len = 0;
    if (ssid_len) {
        memcpy(devipc_apssid, req->buf, ssid_len);
        devipc_apssid[ssid_len] = '\0';
        cfm->status = 0x00; // Success
    } else {
        cfm->status = (0x01UL << 0); // len err
    }
    // Trace the action
    dbg("SET SSID: %s\r\n", devipc_apssid);
    // Send confirm
    devipc_custom_msg_push(cfm);
    return 0;
}

/**
 ****************************************************************************************
 * @brief This function handles the @ref CUST_CMD_GET_PASS command
 *
 * @param[in]    req        Pointer to the custom message request
 * @return       Error id
 ****************************************************************************************
 */
static int
custmsg_get_pass_handler(struct dbg_custom_msg_req const *req)
{
    int pass_len = strlen((char *)devipc_passwd);
    uint8_t cust_msg[offsetof_b(struct dbg_custom_msg_cfm, buf) + PASSPHRASE_MAX_LEN];
    struct dbg_custom_msg_cfm *cfm = (struct dbg_custom_msg_cfm *)cust_msg;
    // Fill the cfm
    cfm->cmd = CUST_CMD_GET_PASS;
    cfm->len = pass_len;
    cfm->status = 0x00; // Success
    memcpy(cfm->buf, devipc_passwd, pass_len);
    // Trace the action
    dbg("GET PASS: %s\r\n", devipc_passwd);
    // Send confirm
    devipc_custom_msg_push(cfm);
    return 0;
}

/**
 ****************************************************************************************
 * @brief This function handles the @ref CUST_CMD_SET_PASS command
 *
 * @param[in]    req        Pointer to the custom message request
 * @return       Error id
 ****************************************************************************************
 */
static int
custmsg_set_pass_handler(struct dbg_custom_msg_req const *req)
{
    unsigned int pass_len = req->len;
    uint8_t cust_msg[offsetof_b(struct dbg_custom_msg_cfm, buf)];
    struct dbg_custom_msg_cfm *cfm = (struct dbg_custom_msg_cfm *)cust_msg;
    // Fill the cfm
    cfm->cmd = CUST_CMD_SET_PASS;
    cfm->len = 0;
    if (pass_len) {
        memcpy(devipc_passwd, req->buf, pass_len);
        devipc_passwd[pass_len] = '\0';
        cfm->status = 0x00; // Success
    } else {
        cfm->status = (0x01UL << 0); // len err
    }
    // Trace the action
    dbg("SET PASS: %s\r\n", devipc_passwd);
    // Send confirm
    devipc_custom_msg_push(cfm);
    return 0;
}

/**
 ****************************************************************************************
 * @brief This function handles the @ref CUST_CMD_GET_VAR command
 *
 * @param[in]    req        Pointer to the custom message request
 * @return       Error id
 ****************************************************************************************
 */
static int
custmsg_get_var_handler(struct dbg_custom_msg_req const *req)
{
    uint8_t cust_msg[offsetof_b(struct dbg_custom_msg_cfm, buf) + 0];
    struct dbg_custom_msg_cfm *cfm = (struct dbg_custom_msg_cfm *)cust_msg;
    // Fill the cfm
    cfm->cmd = CUST_CMD_GET_VAR;
    cfm->len = 0;
    cfm->status = 0x00; // Success
    // TODO:
    // Trace the action
    dbg("GET VAR\r\n");
    // Send confirm
    devipc_custom_msg_push(cfm);
    return 0;
}

/**
 ****************************************************************************************
 * @brief This function handles the @ref CUST_CMD_SET_VAR command
 *
 * @param[in]    req        Pointer to the custom message request
 * @return       Error id
 ****************************************************************************************
 */
static int
custmsg_set_var_handler(struct dbg_custom_msg_req const *req)
{
    uint8_t cust_msg[offsetof_b(struct dbg_custom_msg_cfm, buf)];
    struct dbg_custom_msg_cfm *cfm = (struct dbg_custom_msg_cfm *)cust_msg;
    // Fill the cfm
    cfm->cmd = CUST_CMD_SET_PASS;
    cfm->len = 0;
    cfm->status = 0x00; // Success
    // TODO:
    // Trace the action
    dbg("SET VAR\r\n");
    // Send confirm
    devipc_custom_msg_push(cfm);
    return 0;
}

/*
 * Command handler table
 ****************************************************************************************
 */
const cust_msg_func_t custmsg_handler_table[] = {
    [CUST_CMD_GET_VERSION]  = (cust_msg_func_t)custmsg_get_version_handler,
    [CUST_CMD_GET_SSID]     = (cust_msg_func_t)custmsg_get_ssid_handler,
    [CUST_CMD_SET_SSID]     = (cust_msg_func_t)custmsg_set_ssid_handler,
    [CUST_CMD_GET_PASS]     = (cust_msg_func_t)custmsg_get_pass_handler,
    [CUST_CMD_SET_PASS]     = (cust_msg_func_t)custmsg_set_pass_handler,
    [CUST_CMD_GET_VAR]      = (cust_msg_func_t)custmsg_get_var_handler,
    [CUST_CMD_SET_VAR]      = (cust_msg_func_t)custmsg_set_var_handler,
};

/**
 ****************************************************************************************
 * @brief Search message handler function matching the command
 *
 * @param[in] cmd   Message command
 *
 * @return          Pointer to the message handler (NULL if not found)
 ****************************************************************************************
 */
static cust_msg_func_t custmsg_handler_search(uint32_t cmd)
{
    cust_msg_func_t func = NULL;
    if (cmd < CUST_CMD_MAX) {
        func = custmsg_handler_table[cmd];
    }
    return func;
}

void devipc_custmsg_parser(struct dbg_custom_msg_req *cust_msg)
{
    cust_msg_func_t func = custmsg_handler_search(cust_msg->cmd);
    //dbg("devipc_custmsg_parser, cmd=%08x\r\n", cust_msg->cmd);
    if (func != NULL) {
        int err = func(cust_msg);
        if (err) {
            dbg(D_CRT "cust msg err:%x\r\n", err);
        }
    } else {
        dbg(D_CRT "No handler found for cmd:%x\r\n", cust_msg->cmd);
    }
}
