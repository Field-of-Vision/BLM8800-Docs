/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
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

#include <string.h>
#include "bt_hci.h"
#include "bt_user_driver.h"
#include "dbg.h"
#include "rtos_al.h"

#ifdef CFG_TEST_HCI

///Set to 1 to use BT RF, set to 0 to use WIFI RF
#define RF_BT_ONLY    1

///HCI Transport Header length - change if different transport
#define HCI_TRANSPORT_HDR_LEN                       0x01

///UART header: command message type
#define HCI_CMD_MSG_TYPE                            0x01

///UART header: ACL data message type
#define HCI_ACL_MSG_TYPE                            0x02

///UART header: Synchronous data message type
#define HCI_SYNC_MSG_TYPE                           0x03

///UART header: event message type
#define HCI_EVT_MSG_TYPE                            0x04

///HCI Command Opcode byte length
#define HCI_CMD_OPCODE_LEN         (0x02)

///HCI Event code byte length
#define HCI_EVT_CODE_LEN           (0x01)

///HCI Command/Event parameter length field byte length
#define HCI_CMDEVT_PARLEN_LEN      (0x01)

///HCI Command header length
#define HCI_CMD_HDR_LEN            (HCI_CMD_OPCODE_LEN + HCI_CMDEVT_PARLEN_LEN)

///HCI Event header length
#define HCI_EVT_HDR_LEN            (HCI_EVT_CODE_LEN + HCI_CMDEVT_PARLEN_LEN)

#define HCI_CMD_PARM_MAX_LEN       255

struct hci_cmd_t {
    uint8_t trans_header[HCI_TRANSPORT_HDR_LEN];//1 byte, for cmd is 0x01
    uint8_t cmd_header[HCI_CMD_HDR_LEN];//opcode(2 bytes) + param_len(1 byte)
    uint8_t param[HCI_CMD_PARM_MAX_LEN];
};


struct hci_cmd_t hci_cmd_reset = {{0x01}, {0x03, 0x0C, 0x00}, {}};


struct hci_wr_local_name_cmd
{
    ///Name
    uint8_t name[248];
};
struct hci_cmd_t hci_cmd_wr_local_name = {{0x01}, {0x13, 0x0C, 0xF8}, {}};


/*
 * OPCODE:0xFC32
 * return command complete event
 */
struct hci_set_ble_addr_cmd {
    uint8_t ble_addr[6];
};
struct hci_cmd_t hci_cmd_set_ble_addr = {{0x01}, {0x32, 0xFC, 0x06}, {}};


/*
 * OPCODE:0xFC70
 * return command complete event
 */
struct hci_set_bt_addr_cmd {
    uint8_t bt_addr[6];
};
struct hci_cmd_t hci_cmd_set_bt_addr = {{0x01}, {0x70, 0xFC, 0x06}, {}};


/*
 * OPCODE:0xFC53
 * return command complete event
 */
struct hci_wr_rf_mdm_regs_cmd {
    // offset of following data
    uint16_t offset;
    // reserved
    uint8_t reserved;
    // length of following data, 0 ~ 248 bytes per cmd
    uint8_t length;
    // data(addr<32bits> value<32bits> addr<32bits> value<32bits> ...)
    uint8_t data[248];
};
struct hci_cmd_t hci_cmd_wr_rf_mdm_regs = {{0x01}, {0x53, 0xFC, 0x00}, {}};


/*
 * OPCODE:0xFC48
 * return command complete event
 */
struct hci_set_rf_mode_cmd {
    uint8_t rf_mode;
};
#if (RF_BT_ONLY)
struct hci_cmd_t hci_cmd_set_rf_mode = {{0x01}, {0x48, 0xFC, 0x01}, {0x01}};
#else
struct hci_cmd_t hci_cmd_set_rf_mode = {{0x01}, {0x48, 0xFC, 0x01}, {0x02}};
#endif

/*
 * OPCODE:0xFC4B
 * return command complete event
 */
struct hci_rf_calib_req_cmd {
    // identical with rf_mode
    uint8_t calib_type;
    // offset of following data
    uint16_t offset;
    // length of following data, 0 ~ 128 bytes per cmd
    uint8_t length;
    // data
    uint8_t data[128];
};
#if (RF_BT_ONLY)
struct hci_cmd_t hci_cmd_rf_calib_req = {{0x01}, {0x4B, 0xFC, 0x0C}, {0x01, 0x00, 0x00, 0x08, 0x13, 0x42, 0x26, 0x00, 0x0f, 0x30, 0x02, 0x00}};
#else
struct hci_cmd_t hci_cmd_rf_calib_req = {{0x01}, {0x4B, 0xFC, 0x08}, {0x02, 0x00, 0x00, 0x04, 0x03, 0x42, 0x26, 0x00}};
#endif

struct hci_wr_pscan_activity_cmd {
    uint16_t interval;//in slots
    uint16_t window;//in slots
};
// interval:0x400    window:0x24
struct hci_cmd_t hci_cmd_wr_pscan_activity = {{0x01}, {0x1C, 0x0C, 0x04}, {0x00, 0x04, 0x24, 0x00}};


struct hci_wr_iscan_activity_cmd {
    uint16_t interval;//in slots
    uint16_t window;//in slots
};
// interval:0x400    window:0x24
struct hci_cmd_t hci_cmd_wr_iscan_activity = {{0x01}, {0x1E, 0x0C, 0x04}, {0x00, 0x04, 0x24, 0x00}};

struct hci_wr_scan_en_cmd {
    ///Status of the scan enable
    uint8_t scan_en;
};
struct hci_cmd_t hci_cmd_wr_scan_en = {{0x01}, {0x1A, 0x0C, 0x01}, {0x03}};


static uint32_t rf_mdm_table_index = 0;

#if (RF_BT_ONLY)
static const uint32_t rf_mdm_regs_table[][2] =
{
    {0x40580104, 0x000923fb},
    {0x4062201c, 0x0008d000},
    {0x40622028, 0x48912020},
    {0x40622014, 0x00018983},
    {0x40622054, 0x00008f34},
    {0x40620748, 0x021a01a0},
    {0x40620728, 0x00010020},
    {0x40620738, 0x04800fd4},
    {0x4062073c, 0x00c80064},
    {0x4062202c, 0x000cb220},
    {0x4062200c, 0xe9ad2b45},
    {0x40622030, 0x143c30d2},
    {0x40622034, 0x00001602},
    {0x40620754, 0x214220fd},
    {0x40620758, 0x0007f01e},
    {0x4062071c, 0x00000a33},
    {0x40622018, 0x00124124},
    {0x4062000c, 0x04040000},
    {0x40620090, 0x00069082},
    {0x40621034, 0x02003080},
    {0x40621014, 0x0445117a},
    {0x40622024, 0x00001100},
    {0x40622004, 0x0001a9c0},
    {0x4060048c, 0x00500834},
    {0x40600110, 0x027e0058},
    {0x40600880, 0x00500834},
    {0x40600884, 0x00500834},
    {0x40600888, 0x00500834},
    {0x4060088c, 0x00000834},
    {0x4062050c, 0x20202013},
    {0x406205a0, 0x181c0000},
    {0x406205a4, 0x36363636},
    {0x406205f0, 0x0000ff00},
    {0x40620508, 0x54553132},
    {0x40620530, 0x140f0b00},
    {0x406205b0, 0x00005355},
    {0x4062051c, 0x964b5766},
};
#else
const uint32_t rf_mdm_regs_table[][2] =
{
    {0x40580104, 0x000923fb},
    {0x4034402c, 0x5e201884},
    {0x40344030, 0x1a2e5108},
    {0x40344020, 0x00000977},
    {0x40344024, 0x002ec594},
    {0x40344028, 0x00009402},
    {0x4060048c, 0x00500834},
    {0x40600110, 0x027e0058},
    {0x40600880, 0x00500834},
    {0x40600884, 0x00500834},
    {0x40600888, 0x00500834},
    {0x4060088c, 0x00000834},
    {0x4062050c, 0x20202013},
    {0x40620508, 0x54552022},
    {0x406205a0, 0x1c171a03},
    {0x406205a4, 0x36363636},
    {0x406205f0, 0x0000ff00},
    {0x40620530, 0x0c15120f},
    {0x406205b0, 0x00005355},
    {0x4062051c, 0x964b5766},
};
#endif

enum {
    HCI_RESET = 0,
    HCI_WR_LOCAL_NAME,
    HCI_SET_BLE_ADDR,
    HCI_SET_BT_ADDR,
    HCI_WR_RF_MDM_REGS,
    HCI_SET_RF_MODE,
    HCI_RF_CALIB_REQ,
    HCI_WR_PSCAN_ACTIVITY,
    HCI_WR_ISCAN_ACTIVITY,
    HCI_WR_SCAN_EN,
    HCI_END,
};

static uint8_t bt_addr[6] = {
    0x39,0x90,0x00,0x66,0x66,0x11
};
static uint8_t ble_addr[6] = {
    0x39,0x90,0x00,0x12,0x23,0x34
};

static char local_name[32] = "AIC_BT_TEST";

// at least host can send 1 cmd to controller on initialization
static volatile uint8_t num_hci_cmd_pkts = 1;

static volatile bool cmd_tx_done = true;

uint32_t hci_rx_handler(const uint8_t *data, uint32_t len)
{
    dbg("data received:\n");

    for (int i = 0; i < len; i++) {
        dbg("%X ", data[i]);
    }

    dbg("\n");

    //event
    if (data[0] == 0x04) {
        if (data[1] == 0x0E) {//command complete event
            num_hci_cmd_pkts = data[3];
        } else if (data[1] == 0x0F) {//command status event
            num_hci_cmd_pkts = data[4];
        }
    }

    /* data is of no use now */

    bt_hci_rx_done(BT_HCI_CH_0);

    return len;
}

void hci_tx_handler(const uint8_t *data, uint32_t len)
{
    dbg("data sended\n");

    for (int i = 0; i < len; i++) {
        dbg("%X ", data[i]);
    }

    dbg("\n");

    cmd_tx_done = true;

    /* data can be recycled now */
}

void hci_test(void)
{
    dbg("hci test start\n");

    bt_launch();

    bt_hci_open(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, hci_rx_handler, hci_tx_handler, true);

    bt_hci_rx_start(BT_HCI_CH_0);

    int hci_status = HCI_RESET;

    while (hci_status < HCI_END) {
        while ((cmd_tx_done == false) || (num_hci_cmd_pkts < 1));
        GLOBAL_INT_DISABLE();
        num_hci_cmd_pkts--;
        cmd_tx_done = false;
        GLOBAL_INT_RESTORE();
        switch (hci_status) {
        case HCI_RESET:
            bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_reset,
                (hci_cmd_reset.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));
            hci_status = HCI_WR_LOCAL_NAME;
            break;
        case HCI_WR_LOCAL_NAME:
            {
                uint8_t name_len = strlen(local_name);
                memcpy(&hci_cmd_wr_local_name.param[0], local_name, name_len);
                hci_cmd_wr_local_name.param[name_len] = '\0';
                //do not change param_len in hci_cmd_wr_local_name, it must be 248
                bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_wr_local_name,
                    (hci_cmd_wr_local_name.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));
                hci_status = HCI_SET_BLE_ADDR;
            }
            break;
        case HCI_SET_BLE_ADDR:
            memcpy(&hci_cmd_set_ble_addr.param[0], &ble_addr[0], 6);
            // param_len
            hci_cmd_set_ble_addr.cmd_header[2] = 6;
            bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_set_ble_addr,
                (hci_cmd_set_ble_addr.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));
            hci_status = HCI_SET_BT_ADDR;
            break;
        case HCI_SET_BT_ADDR:
            memcpy(&hci_cmd_set_bt_addr.param[0], &bt_addr[0], 6);
            // param_len
            hci_cmd_set_bt_addr.cmd_header[2] = 6;
            bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_set_bt_addr,
                (hci_cmd_set_bt_addr.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));
            hci_status = HCI_WR_RF_MDM_REGS;
            break;
        case HCI_WR_RF_MDM_REGS:
            {
                uint32_t rf_mdm_total_regs = sizeof(rf_mdm_regs_table) / sizeof(rf_mdm_regs_table[0]);

                uint32_t offset = rf_mdm_table_index * 8;
                //hci_wr_rf_mdm_regs_cmd.offset
                hci_cmd_wr_rf_mdm_regs.param[0] = offset & 0xFF;
                hci_cmd_wr_rf_mdm_regs.param[1] = (offset >> 8) & 0xFF;

                //hci_wr_rf_mdm_regs_cmd.reserved
                hci_cmd_wr_rf_mdm_regs.param[2] = 0;

                uint32_t i = 0;
                // consider one cmd carry at most 30 addr-val pair once
                for (i = 0; i < 30; i++) {
                    if (rf_mdm_table_index < rf_mdm_total_regs) {
                        uint32_t reg_addr = rf_mdm_regs_table[rf_mdm_table_index][0];
                        uint32_t reg_val = rf_mdm_regs_table[rf_mdm_table_index][1];

                        //hci_wr_rf_mdm_regs_cmd.data
                        hci_cmd_wr_rf_mdm_regs.param[4 + i * 8 + 0] = reg_addr & 0xFF;
                        hci_cmd_wr_rf_mdm_regs.param[4 + i * 8 + 1] = (reg_addr >> 8) & 0xFF;
                        hci_cmd_wr_rf_mdm_regs.param[4 + i * 8 + 2] = (reg_addr >> 16) & 0xFF;
                        hci_cmd_wr_rf_mdm_regs.param[4 + i * 8 + 3] = (reg_addr >> 24) & 0xFF;

                        hci_cmd_wr_rf_mdm_regs.param[4 + i * 8 + 4] = reg_val & 0xFF;
                        hci_cmd_wr_rf_mdm_regs.param[4 + i * 8 + 5] = (reg_val >> 8) & 0xFF;
                        hci_cmd_wr_rf_mdm_regs.param[4 + i * 8 + 6] = (reg_val >> 16) & 0xFF;
                        hci_cmd_wr_rf_mdm_regs.param[4 + i * 8 + 7] = (reg_val >> 24) & 0xFF;

                        rf_mdm_table_index++;
                    } else {
                        break;
                    }
                }

                //hci_wr_rf_mdm_regs_cmd.length
                hci_cmd_wr_rf_mdm_regs.param[3] = i * 8;

                //param len
                hci_cmd_wr_rf_mdm_regs.cmd_header[2] = hci_cmd_wr_rf_mdm_regs.param[3] + 4;

                bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_wr_rf_mdm_regs,
                    (hci_cmd_wr_rf_mdm_regs.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));

                if (rf_mdm_table_index >= rf_mdm_total_regs) {
                    hci_status = HCI_SET_RF_MODE;
                }
            }
            break;
        case HCI_SET_RF_MODE:
            bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_set_rf_mode,
                (hci_cmd_set_rf_mode.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));
            hci_status = HCI_RF_CALIB_REQ;
            break;
        case HCI_RF_CALIB_REQ:
            bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_rf_calib_req,
                (hci_cmd_rf_calib_req.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));
            hci_status = HCI_WR_PSCAN_ACTIVITY;
            break;
        case HCI_WR_PSCAN_ACTIVITY:
            bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_wr_pscan_activity,
                (hci_cmd_wr_pscan_activity.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));
            hci_status = HCI_WR_ISCAN_ACTIVITY;
            break;
        case HCI_WR_ISCAN_ACTIVITY:
            bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_wr_iscan_activity,
                (hci_cmd_wr_iscan_activity.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));
            hci_status = HCI_WR_SCAN_EN;
            break;
        case HCI_WR_SCAN_EN:
            bt_hci_tx(BT_HCI_CH_0, BT_HCI_PKT_TYPE_HCI_UART, (uint8_t *)&hci_cmd_wr_scan_en,
                (hci_cmd_wr_scan_en.cmd_header[2] + HCI_TRANSPORT_HDR_LEN + HCI_CMD_HDR_LEN));
            hci_status = HCI_END;
            break;
        default:
            break;
        }
    }
}
#endif /*CFG_TEST_HCI*/

