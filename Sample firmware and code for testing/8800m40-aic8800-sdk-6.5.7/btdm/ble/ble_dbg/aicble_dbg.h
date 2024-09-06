#ifndef __AICBLE_DBG_H
#define __AICBLE_DBG_H

#include "rtos.h"
#include "dbg.h"
#include "co_int.h"

enum {
    AICBLE_ERROR_LEVEL  = 0,
    AICBLE_WARN_LEVEL   = 1,
    AICBLE_NOTICE_LEVEL = 2,
    AICBLE_INFO_LEVEL   = 3,
    AICBLE_DEBUG_LEVEL  = 4,
};

#define AICBLE_HCI_VAL                  BIT0
#define AICBLE_L2CAP_VAL                BIT1
#define AICBLE_GAP_VAL                  BIT2
#define AICBLE_GATT_VAL                 BIT3
#define AICBLE_ATT_VAL                  BIT4
#define AICBLE_SMP_VAL                  BIT5
#define AICBLE_APP_VAL                  BIT6
#define AICBLE_PRF_VAL                  BIT7
#define AICBLE_DBG_MASK                 (0xffffffff)
#define AICBLE_NON_DBG                  (0)

#define AICBLE_TX_ACL_AREA              BIT0
#define AICBLE_TX_CMD_AREA              BIT1
#define AICBLE_RX_EVENT_AREA            BIT2
#define AICBLE_RX_ACL_AREA              BIT3
#define AICBLE_LTK_AREA                 BIT4
#define AICBLE_AREA_MASK                 (0xFFFFFFFF)
#define AICBLE_NONE_AREA                (0)

#define TX_ACL                  (aicble_dump_area & AICBLE_TX_ACL_AREA)
#define TX_CMD                  (aicble_dump_area & AICBLE_TX_CMD_AREA)
#define RX_EVENT                (aicble_dump_area & AICBLE_RX_EVENT_AREA)
#define RX_ACL                  (aicble_dump_area & AICBLE_RX_ACL_AREA)
#define LTK                     (aicble_dump_area & AICBLE_LTK_AREA)

extern uint32_t aicble_dbg_area;
extern uint32_t aicble_dbg_level;
extern uint32_t aicble_dump_area;

char *aicble_dbgarea(int dbg_flags);
void aicble_set_dbgarea(uint32_t dbg_area);
void aicble_set_dbgarea(uint32_t dbg_area);
void aicble_set_dumparea(uint32_t dump_area);
uint32_t aicble_get_dbgarea();
uint32_t aicble_get_dbglevel();
uint32_t aicble_get_dumparea();

#ifdef CFG_DBG
#define AICBLE_DBG(area, level, fmt, ...) \
        do { \
            uint32_t dbg_area = AICBLE_##area##_VAL & aicble_dbg_area; \
            uint32_t dbg_level = AICBLE_##level##_LEVEL; \
            if (dbg_area && (dbg_level <= aicble_dbg_level)){ \
                    const char *prefix = NULL; \
                    prefix = aicble_dbgarea(dbg_area); \
                    dbg("%s<%s,%d>", prefix, __func__, __LINE__); \
                    dbg(fmt, ##__VA_ARGS__); \
                    dbg("\n");\
            } \
        } while (0)
#else /* CFG_DBG */
#define AICBLE_DBG(area, level, fmt, ...)
#endif /* CFG_DBG */

#ifdef CFG_DBG
void aicble_dbg_hex_dump(int area, const void *data, size_t size);
#define AICBLE_DUMP(area, data, len)\
        do {\
            if (area){\
                dbg("[BLE_DUMP]:<%s,%d>: (len:%d)\n", __func__, __LINE__,(int)len);\
                aicble_dbg_hex_dump(area, data, len);\
            }\
        } while (0)
#else /* CFG_DBG */
#define AICBLE_DUMP(area, data, len)
#endif /* CFG_DBG */

#endif /* __AICBLE_DBG_H */
