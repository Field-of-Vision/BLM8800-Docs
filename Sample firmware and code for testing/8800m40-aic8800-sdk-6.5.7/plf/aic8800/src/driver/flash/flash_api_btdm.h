#ifndef _FLASH_API_BTDM_H_
#define _FLASH_API_BTDM_H_

/**
 * Includes
 */
#include "flash_api.h"
#if PLF_BT_STACK
#include "tgt_cfg_bt.h"
#include "bt_types_def.h"
#include "co_list.h"
#define MAX_BD_MUN    5
#endif

#if PLF_BLE_STACK
#include "app.h"
#include "gap.h"
#include "gapc_task.h"
#include "co_bt_defines.h"
#endif //PLF_BLE_STACK

/**
 * Structs
 */
/* btdm info */
typedef struct
{
    uint8_t bt_flash_erased;
    uint8_t factory_mode_setting;
    uint8_t local_bt_addr[6];
    uint8_t local_ble_addr[6];
    uint16_t reserved;
    char local_dev_name[32];
    uint8_t pincode[16];
} bt_factory_info_t;

#if PLF_BT_STACK == 1
#ifndef BTDEVRECORD
#define BTDEVRECORD
typedef struct _BtDeviceRecord
{
    BT_ADDR  bdAddr;
    bool        trusted;
    uint8_t     linkKey[16];
    uint8_t     keyType;
    uint8_t     pinLen;
} BtDeviceRecord;
#endif

typedef struct {
  list_node_t *head;
  uint8_t length;
} bt_dev_list;

typedef  struct {
    bool hf_state;
    bool a2dp_state;
    uint8_t a2dp_role;
    uint8_t a2dp_codectype;
    int8_t peer_a2dp_vol;
    int8_t peer_hfp_vol;
    uint32_t cod;
}btdev_info;

typedef struct {
    list_node_t node;
    BtDeviceRecord record;
    btdev_info device_info;
} bt_dev_info_t;

typedef struct {
    uint8_t addr_type;
    BT_ADDR bleaddr;
} ble_dev_info_t;

typedef struct {
    uint8_t init_need; // need init when value not equal to 0xEE
    uint8_t flush_need;
#if APP_SUPPORT_TWS == 1
    uint8_t flash_tws_role;
    ble_dev_info_t ble_dev_info;
#endif
    bt_dev_list   bt_list;
    bt_dev_info_t bt_dev_info[MAX_BD_MUN];
} bt_flash_info_t;
#endif

#if PLF_BLE_STACK
// Local key length
#define LOC_KEY_LEN              (0x10)
typedef struct gapc_ltk gapc_ltk_t;
typedef struct ble_ad_filter ble_ad_filter_t;
typedef struct white_list white_list_t;

typedef struct {
    gapc_ltk_t le_ltk;
    uint8_t loc_irk[LOC_KEY_LEN];
    uint8_t bond_status;
    uint16_t ntf_cfg;
    uint8_t ble_rand_add[BD_ADDR_LEN];
    ble_ad_filter_t ad_filter;
    white_list_t wl;
} ble_flash_info_t;

#endif // (PLF_BLE_STACK)

typedef struct {
    unsigned int magic_num; /* "BTDM" */
    unsigned int info_flag;
    unsigned int RESERVED_08;
    unsigned int RESERVED_0C;
    bt_factory_info_t bt_factory;
#if PLF_BT_STACK == 1
    bt_flash_info_t bt_info;
#endif
#if PLF_BLE_STACK
    ble_flash_info_t ble_info;
#endif
} btdm_info_t;

/**
 * btdm info api
 */
int flash_btdm_bt_factory_read(void *buf, unsigned int len);
void flash_btdm_bt_factory_write(const void *buf, unsigned int len);

#if PLF_BT_STACK == 1
bt_flash_info_t * flash_btdm_bt_dev_read(void);
void flash_btdm_bt_dev_write(void);
#endif

#if PLF_BLE_STACK
int flash_btdm_le_ltk_read(gapc_ltk_t *le_ltk);
void flash_btdm_le_ltk_write(gapc_ltk_t *le_ltk);
void flash_btdm_le_ltk_remove(void);

int flash_btdm_le_loc_irk_read(uint8_t *loc_irk);
void flash_btdm_le_loc_irk_write(uint8_t *loc_irk);
void flash_btdm_le_loc_irk_remove(void);

int flash_btdm_le_periph_bonded_read(uint8_t *bond_status);
void flash_btdm_le_periph_bonded_write(uint8_t *bond_status);
void flash_btdm_le_periph_bonded_remove(void);

int flash_btdm_le_mouse_ntf_cfg_read(uint8_t *ntf_cfg);
void flash_btdm_le_mouse_ntf_cfg_write(uint8_t *ntf_cfg);
void flash_btdm_le_mouse_ntf_cfg_remove(void);

int flash_btdm_le_rand_addr_read(uint8_t *le_addr);
void flash_btdm_le_rand_addr_write(uint8_t *le_addr);
void flash_btdm_le_rand_addr_remove(void);

int flash_btdm_le_ad_data_ft_read(ble_ad_filter_t *ad_filter);
void flash_btdm_le_ad_data_ft_write(ble_ad_filter_t *ad_filter);
void flash_btdm_le_ad_data_ft_remove(void);

int flash_btdm_le_whitelist_read(white_list_t *wl);
void flash_btdm_le_whitelist_write(white_list_t *wl);
void flash_btdm_le_whitelist_remove(void);

void flash_btdm_le_info_remove_all(void);
#endif // PLF_BLE_STACK

#endif /* _FLASH_API_BTDM_H_ */
