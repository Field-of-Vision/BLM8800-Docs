#ifndef _REG_G1_IPC_MUTEX_H_
#define _REG_G1_IPC_MUTEX_H_

#include "reg_access.h"
#include "chip.h"

/**
 * IPC_MUTEX registers
 */
#define IPC_G1_MUTEX_BASE_ADDR   (AIC_IPCAPP_BASE + 0x0240)

__INLINE uint32_t ipc_g1_mutex_get(int idx)
{
    return REG_PL_RD(IPC_G1_MUTEX_BASE_ADDR + (idx << 2));
}

__INLINE void ipc_g1_mutex_set(int idx, uint32_t value)
{
    REG_PL_WR(IPC_G1_MUTEX_BASE_ADDR + (idx << 2), value);
}

/**
 * IPC_G1_MUTEX ID definition
 */
enum {
    IPC_G1_MUTEX_ID_RF_CTRL        = 0,
    IPC_G1_MUTEX_ID_1              = 1,
    IPC_G1_MUTEX_ID_2              = 2,
    IPC_G1_MUTEX_ID_FLASH_ACCESS   = 3,
    IPC_G1_MUTEX_ID_4              = 4,
    IPC_G1_MUTEX_ID_5              = 5,
    IPC_G1_MUTEX_ID_6              = 6,
    IPC_G1_MUTEX_ID_7              = 7,
    IPC_G1_MUTEX_ID_MAX
};

#endif /* _REG_G1_IPC_MUTEX_H_ */
