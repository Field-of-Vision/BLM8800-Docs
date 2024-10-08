/**
 ******************************************************************************
 *
 * @file rwnx_platorm.h
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ******************************************************************************
 */

#ifndef _RWNX_PLATFORM_H_
#define _RWNX_PLATFORM_H_

#include <linux/pci.h>

#define RWNX_CONFIG_FW_NAME             "rwnx_settings.ini"

#define CDEV_BUF_MAX    256
struct rwnx_fasync_info
{
    int mem_status;
    char mem[CDEV_BUF_MAX];
    struct list_head list;
};

struct rwnx_aic_chardev {
    dev_t dev;
    int major;
    int fasync_wait;
    struct cdev *c_cdev;
    struct class *cdev_class;
    spinlock_t fasync_lock;
    struct list_head fasync_list;
    struct completion fasync_comp;
    struct work_struct fasync_work;
    struct fasync_struct *async_queue;
    struct rwnx_fasync_info *fasync_info;
};

struct rwnx_hw;
enum rwnx_platform_addr {
    RWNX_ADDR_CPU,
    RWNX_ADDR_SYSTEM,
    RWNX_ADDR_MAX,
};

/**
 * struct rwnx_plat - Operation pointers for RWNX PCI platform
 *
 * @pci_dev: pointer to pci dev
 * @enabled: Set if embedded platform has been enabled (i.e. fw loaded and
 *          ipc started)
 * @enable: Configure communication with the fw (i.e. configure the transfers
 *         enable and register interrupt)
 * @disable: Stop communication with the fw
 * @deinit: Free all ressources allocated for the embedded platform
 * @get_address: Return the virtual address to access the requested address on
 *              the platform.
 * @ack_irq: Acknowledge the irq at link level.
 * @get_config_reg: Return the list (size + pointer) of registers to restore in
 * order to reload the platform while keeping the current configuration.
 *
 * @priv Private data for the link driver
 */
struct rwnx_plat {
    struct pci_dev *pci_dev;

#ifdef AICWF_SDIO_SUPPORT
	struct aic_sdio_dev *sdiodev;
#endif

#ifdef AICWF_USB_SUPPORT
    struct aic_usb_dev *usbdev;
#endif
    bool enabled;

    int (*enable)(struct rwnx_hw *rwnx_hw);
    int (*disable)(struct rwnx_hw *rwnx_hw);
    void (*deinit)(struct rwnx_plat *rwnx_plat);
    u8* (*get_address)(struct rwnx_plat *rwnx_plat, int addr_name,
                       unsigned int offset);
    void (*ack_irq)(struct rwnx_plat *rwnx_plat);
    int (*get_config_reg)(struct rwnx_plat *rwnx_plat, const u32 **list);

    u8 priv[0] __aligned(sizeof(void *));
};

#define RWNX_ADDR(plat, base, offset)           \
    plat->get_address(plat, base, offset)

#define RWNX_REG_READ(plat, base, offset)               \
    readl(plat->get_address(plat, base, offset))

#define RWNX_REG_WRITE(val, plat, base, offset)         \
    writel(val, plat->get_address(plat, base, offset))

extern struct rwnx_plat *g_rwnx_plat;
int rwnx_platform_init(struct rwnx_plat *rwnx_plat, void **platform_data);
void rwnx_platform_deinit(void);
int rwnx_platform_on(struct rwnx_hw *rwnx_hw, void *config);
void rwnx_platform_off(struct rwnx_hw *rwnx_hw, void **config);
int rwnx_platform_register_drv(void);
void rwnx_platform_unregister_drv(void);
extern struct device *rwnx_platform_get_dev(struct rwnx_plat *rwnx_plat);
static inline unsigned int rwnx_platform_get_irq(struct rwnx_plat *rwnx_plat)
{
    return rwnx_plat->pci_dev->irq;
}

void rwnx_platform_custom_msg_vnet_init(void);
void rwnx_platform_get_mac_ready(void);
void rwnx_platform_get_wlan_ready(void);
int rwnx_platform_set_mac_addr(void);
int rwnx_aic_cdev_fill_mem(char *buff);

#ifdef CONFIG_VNET_MODE
extern struct net_device *vnet_dev;
#endif

#endif /* _RWNX_PLATFORM_H_ */
