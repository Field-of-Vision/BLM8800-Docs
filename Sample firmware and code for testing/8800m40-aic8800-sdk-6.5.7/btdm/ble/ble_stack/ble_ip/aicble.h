#ifndef _AICBLE_H_
#define _AICBLE_H_

typedef void (*BleDeInitCallback)(uint8_t flag, uint8_t status);
extern BleDeInitCallback ble_callback;

void aic_ble_init(void);
void aic_ble_deinit(void);
void aic_ble_reset(void);
void aic_ble_schedule(void);
bool aic_ble_tx_rx_allow_sleep(void);
bool aic_ble_stack_allow_sleep(void);
#endif
