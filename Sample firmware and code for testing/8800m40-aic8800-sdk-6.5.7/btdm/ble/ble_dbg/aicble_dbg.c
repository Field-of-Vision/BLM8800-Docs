#include "aicble_dbg.h"

uint32_t aicble_dbg_area = 0x0;//(AICBLE_AREA_MASK);
uint32_t aicble_dbg_level = 0x0;//(AICBLE_DBG_MASK );
uint32_t aicble_dump_area = 0x0;

void aicble_set_dbgarea(uint32_t dbg_area)
{
    aicble_dbg_area = dbg_area;
}

void aicble_set_dbglevel(uint32_t dbg_level)
{
    aicble_dbg_level= dbg_level;
}

void aicble_set_dumparea(uint32_t dump_area)
{
    aicble_dump_area= dump_area;
}

uint32_t aicble_get_dbgarea()
{
    return aicble_dbg_area;
}

uint32_t aicble_get_dbglevel()
{
    return aicble_dbg_level;
}

uint32_t aicble_get_dumparea()
{
    return aicble_dump_area;
}

void dump_buf(const uint8_t *buf, uint16_t len)
{
    int i;

    for (i=0;i<len;i++) {
        if((i%8 == 0))
            dbg("  ");
        dbg("%02x ", buf[i]);
        if((i+1)%16 == 0)
            dbg("\n");
    }
    dbg("\n");
}

char *aicble_dbgarea(int dbg_flags)
{
    switch (dbg_flags) {
    case AICBLE_HCI_VAL:
        return "[BLE_HCI]";
    case AICBLE_L2CAP_VAL:
        return "[BLE_L2CAP]";
    case AICBLE_ATT_VAL:
        return "[BLE_ATT]";
    case AICBLE_GATT_VAL:
        return "[BLE_GATT]";
    case AICBLE_SMP_VAL:
        return "[BLE_SMP]";
    case AICBLE_GAP_VAL:
        return "[BLE_GAP]";
    case AICBLE_APP_VAL:
        return "[BLE_APP]";
    case AICBLE_PRF_VAL:
        return "[BLE_PRF]";
    default:
        return "[BLE_UNKNOW]";
    }
}

char *aicble_dumparea(int dump_area)
{
    switch (dump_area) {
    case AICBLE_TX_ACL_AREA:
        return "[TX_ACL]";
    case AICBLE_TX_CMD_AREA:
        return "[TX_CMD]";
    case AICBLE_RX_EVENT_AREA:
        return "[RX_EVENT]";
    case AICBLE_RX_ACL_AREA:
        return "[RX_ACL]";
    case AICBLE_LTK_AREA:
        return "[LTK]";
    default:
        return "[UNKNOW]";
    }
}

void aicble_dbg_hex_dump(int area, const void *data, size_t size)
{
    dbg("%s============== Hex Data Begin ==============\n",
        aicble_dumparea(area));
    dump_buf(data, size);
    dbg("%s============== Hex Data End ================\n",
       aicble_dumparea(area));
}

