#ifndef __AIC_M2D_BLE_H__
#define __AIC_M2D_BLE_H__
#if PLF_M2D_BLE
#include "stdint.h"
#include "gap.h"

void m2d_flash_block_bit_read(void *buf, unsigned int len);
void m2d_flash_block_bit_write(void *buf, unsigned int len);
void m2d_flash_block_bit_erase(void);
void m2d_flash_block_data_read(void *buf, unsigned int len, unsigned int addr_offset);
void m2d_flash_block_data_write(void *buf, unsigned int len, unsigned int addr_offset);
void m2d_flash_block_data_erase(void);
uint8_t *m2d_get_tmall_genie_wakeup_word(void);
int app_m2d_wl_addr_check(bd_addr_t bdaddr);
void app_ble_start_delay_init(void);
void app_ble_m2d_init(void);
#endif
#endif /* __AIC_M2D_BLE_H__ */
