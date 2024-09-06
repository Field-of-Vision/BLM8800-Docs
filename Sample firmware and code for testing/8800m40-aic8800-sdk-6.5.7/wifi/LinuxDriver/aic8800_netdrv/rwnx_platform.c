/**
 ******************************************************************************
 *
 * @file rwnx_platform.c
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ******************************************************************************
 */
#include <linux/module.h>
#include <linux/firmware.h>
#include <linux/delay.h>

#include "rwnx_platform.h"
#include "rwnx_main.h"
#include "rwnx_tx.h"
#include "virt_net.h"

#ifdef AICWF_SDIO_SUPPORT
#include "aicwf_sdio.h"
#endif
#ifdef AICWF_USB_SUPPORT
#include "aicwf_usb.h"
#endif

struct rwnx_plat *g_rwnx_plat = NULL;
struct rwnx_vif  g_rwnx_vif   = {{0}};

#ifdef CONFIG_VNET_MODE
aicwf_cmd_mgr g_cmd_mgr;
aicwf_custom_msg_vnet g_custom_msg_vnet;
int rwnx_platform_set_mac_addr(void)
{
    struct custom_msg_set_mac_req mac;
    aicwf_custom_msg_cmd_cfm cmd_cfm;
    mac.hdr.cmd_id = CUST_CMD_SET_MAC_ADDR_REQ;
    memcpy(mac.mac_addr, g_custom_msg_vnet.macaddr_cfm.mac_addr, 6);
    printk("mac addr: %02X %02X\r\n",
        g_custom_msg_vnet.macaddr_cfm.mac_addr[0], g_custom_msg_vnet.macaddr_cfm.mac_addr[5]);
    cmd_cfm.waitcfm = AICWF_CMD_NOWAITCFM;
    cmd_cfm.cfm_id = 0;
    rwnx_tx_msg((u8 *)&mac, sizeof(mac), &cmd_cfm, NULL);
    return 0;
}

void rwnx_platform_custom_msg_vnet_init(void)
{
    g_custom_msg_vnet.aic_mode_status          = AIC_MODE_IDLE;
    g_custom_msg_vnet.wlan_status              = WLAN_DISCONNECT;
    g_custom_msg_vnet.ap_status_cfm.status     = AIC_AP_CLOSE;
    g_custom_msg_vnet.ble_status               = BLE_STATUS_DEFAULT;
    g_custom_msg_vnet.comp_sign_get_mac_ready  = false;
    g_custom_msg_vnet.comp_sign_get_wlan_ready = false;
    g_custom_msg_vnet.scan_wifi_cfm_ptr = NULL;
}

void rwnx_platform_get_mac_ready(void)
{
    complete(&g_custom_msg_vnet.platform_get_mac_done);
}
int rwnx_platform_get_mac_addr(void)
{
    struct custom_msg_hdr req;
    aicwf_custom_msg_cmd_cfm cmd_cfm;
    req.cmd_id = CUST_CMD_GET_MAC_ADDR_REQ;
    cmd_cfm.waitcfm = AICWF_CMD_NOWAITCFM;
    cmd_cfm.cfm_id = 0;

    // To avoid complete platform_get_mac_done before init_completion
    init_completion(&g_custom_msg_vnet.platform_get_mac_done);
    rwnx_tx_msg((u8 *)&req, sizeof(req), &cmd_cfm, NULL);

    if ((wait_for_completion_timeout(&g_custom_msg_vnet.platform_get_mac_done,
                                      msecs_to_jiffies(PLATFORM_PREPARE_TIMEOUT)) == 0)) {
        printk("error: platform get mac address timeout\n");
        return -1;
    }
    return 0;
}

void rwnx_platform_get_wlan_ready(void)
{
    complete(&g_custom_msg_vnet.platform_get_wlan_done);
}
int rwnx_platform_get_wlan_status(void)
{
    struct custom_msg_hdr req = {0};
    aicwf_custom_msg_cmd_cfm cmd_cfm;
    req.cmd_id = CUST_CMD_GET_WLAN_STATUS_REQ;
    cmd_cfm.waitcfm = AICWF_CMD_NOWAITCFM;
    cmd_cfm.cfm_id = 0;

    // To avoid complete platform_get_conn_st_done before init_completion
    init_completion(&g_custom_msg_vnet.platform_get_wlan_done);
    rwnx_tx_msg((u8 *)&req, sizeof(req), &cmd_cfm, NULL);

    if ((wait_for_completion_timeout(&g_custom_msg_vnet.platform_get_wlan_done,
                                      msecs_to_jiffies(PLATFORM_PREPARE_TIMEOUT)) == 0)) {
        printk("error: platform get wlan status timeout\n");
        return -1;
    }
    return 0;
}

int rwnx_platform_get_vnet_setting(void)
{
    struct custom_msg_hdr req = {0};
    aicwf_custom_msg_cmd_cfm cmd_cfm;
    req.cmd_id = CUST_CMD_GET_VNET_SETTING_REQ;
    cmd_cfm.waitcfm = AICWF_CMD_NOWAITCFM;
    cmd_cfm.cfm_id = 0;

    rwnx_tx_msg((u8 *)&req, sizeof(req), &cmd_cfm, NULL);
    return 0;
}

#endif

/**
 * rwnx_platform_reset() - Reset the platform
 *
 * @rwnx_plat: platform data
 */
static int rwnx_platform_reset(struct rwnx_plat *rwnx_plat)
{
    u32 regval;

#if defined(AICWF_USB_SUPPORT) || defined(AICWF_SDIO_SUPPORT)
    return 0;
#endif

    /* the doc states that SOFT implies FPGA_B_RESET
     * adding FPGA_B_RESET is clearer */
    RWNX_REG_WRITE(SOFT_RESET | FPGA_B_RESET, rwnx_plat,
                   RWNX_ADDR_SYSTEM, SYSCTRL_MISC_CNTL_ADDR);
    msleep(100);

    regval = RWNX_REG_READ(rwnx_plat, RWNX_ADDR_SYSTEM, SYSCTRL_MISC_CNTL_ADDR);

    if (regval & SOFT_RESET) {
        dev_err(rwnx_platform_get_dev(rwnx_plat), "reset: failed\n");
        return -EIO;
    }

    RWNX_REG_WRITE(regval & ~FPGA_B_RESET, rwnx_plat,
                   RWNX_ADDR_SYSTEM, SYSCTRL_MISC_CNTL_ADDR);
    msleep(100);
    return 0;
}

/**
 * rwmx_platform_save_config() - Save hardware config before reload
 *
 * @rwnx_plat: Pointer to platform data
 *
 * Return configuration registers values.
 */
static void* rwnx_term_save_config(struct rwnx_plat *rwnx_plat)
{
    const u32 *reg_list;
    u32 *reg_value, *res;
    int i, size = 0;

    if (rwnx_plat->get_config_reg) {
        size = rwnx_plat->get_config_reg(rwnx_plat, &reg_list);
    }

    if (size <= 0)
        return NULL;

    res = kmalloc(sizeof(u32) * size, GFP_KERNEL);
    if (!res)
        return NULL;

    reg_value = res;
    for (i = 0; i < size; i++) {
        *reg_value++ = RWNX_REG_READ(rwnx_plat, RWNX_ADDR_SYSTEM, *reg_list++);
    }

    return res;
}

/**
 * rwnx_platform_on() - Start the platform
 *
 * @rwnx_hw: Main driver data
 * @config: Config to restore (NULL if nothing to restore)
 *
 * It starts the platform :
 * - load fw and ucodes
 * - initialize IPC
 * - boot the fw
 * - enable link communication/IRQ
 *
 * Called by 802.11 part
 */
int rwnx_platform_on(struct rwnx_hw *rwnx_hw, void *config)
{
    struct rwnx_plat *rwnx_plat = rwnx_hw->plat;

    RWNX_DBG(RWNX_FN_ENTRY_STR);

    if (rwnx_plat->enabled)
        return 0;

    rwnx_plat->enabled = true;

    return 0;
}

/**
 * rwnx_platform_off() - Stop the platform
 *
 * @rwnx_hw: Main driver data
 * @config: Updated with pointer to config, to be able to restore it with
 * rwnx_platform_on(). It's up to the caller to free the config. Set to NULL
 * if configuration is not needed.
 *
 * Called by 802.11 part
 */
void rwnx_platform_off(struct rwnx_hw *rwnx_hw, void **config)
{
    #if defined(AICWF_USB_SUPPORT) || defined(AICWF_SDIO_SUPPORT)
    rwnx_hw->plat->enabled = false;
    return ;
    #endif

    if (!rwnx_hw->plat->enabled) {
        if (config)
            *config = NULL;
        return;
    }

    if (config)
        *config = rwnx_term_save_config(rwnx_hw->plat);

    rwnx_hw->plat->disable(rwnx_hw);

    tasklet_kill(&rwnx_hw->task);

    rwnx_platform_reset(rwnx_hw->plat);

    rwnx_hw->plat->enabled = false;
}

#ifdef CONFIG_APP_FASYNC
struct rwnx_aic_chardev chardev;
int rwnx_aic_cdev_open(struct inode *inode, struct file *filp)
{
    filp->private_data = &chardev;
    printk("rwnx_aic_cdev_open\r\n");
    return 0;
}

void rwnx_aic_fasync_ready(void)
{
    complete(&chardev.fasync_comp);
}

void rwnx_aic_cdev_fasync_work(struct work_struct *work)
{
    unsigned long flags;
    struct rwnx_fasync_info *fsy_info;

    while(1) {

        spin_lock_irqsave(&chardev.fasync_lock, flags);
        if (list_empty(&chardev.fasync_list)) {
            spin_unlock_irqrestore(&chardev.fasync_lock, flags);
            break;
        }
        fsy_info = list_first_entry(&chardev.fasync_list, struct rwnx_fasync_info, list);
        list_del(&fsy_info->list);
        spin_unlock_irqrestore(&chardev.fasync_lock, flags);

        init_completion(&chardev.fasync_comp);
        memcpy(chardev.fasync_info->mem, fsy_info->mem, CDEV_BUF_MAX);
        if(chardev.async_queue) {
            //printk("Send signal\n");
            kill_fasync(&chardev.async_queue, SIGIO, POLL_IN);
        }
        kfree(fsy_info);

        if ((wait_for_completion_timeout(&chardev.fasync_comp, msecs_to_jiffies(PLATFORM_PREPARE_TIMEOUT)) == 0)) {
            printk("fasync: application confirm timeout\n");
        }
    }
}

int rwnx_aic_cdev_fill_mem(char *buff)
{
    unsigned long flags;
    struct rwnx_fasync_info *fsy_info;

    fsy_info = kzalloc(sizeof(struct rwnx_fasync_info), GFP_KERNEL);
    if (!fsy_info) {
        printk("%s: alloc fail, loss kernel-msg\n", __func__);
        return -1;
    }
    memcpy(fsy_info->mem, buff, CDEV_BUF_MAX);

    spin_lock_irqsave(&chardev.fasync_lock, flags);
    list_add_tail(&fsy_info->list, &chardev.fasync_list);
    spin_unlock_irqrestore(&chardev.fasync_lock, flags);

    schedule_work(&chardev.fasync_work);

    return 0;
}

ssize_t rwnx_aic_cdev_read(struct file* filp, char __user* buf, size_t cnt, loff_t* f_pos)
{
    struct rwnx_aic_chardev *pchardev = filp->private_data;
    //printk("rwnx_aic_cdev_read\r\n");
    if(copy_to_user(buf, pchardev->fasync_info, cnt) < 0) {
        printk("copy kernel data fail\n");
    }
    return 0;
}

ssize_t rwnx_aic_cdev_write(struct file* filp, char const __user* buf, size_t cnt, loff_t* f_pos)
{
    struct rwnx_aic_chardev *pchardev = filp->private_data;
    //printk("rwnx_aic_cdev_write\n");
    if(copy_from_user(&pchardev->fasync_info->mem_status, buf, cnt) < 0) {
        printk("copy data to kernel fail\n");
    }
    rwnx_aic_fasync_ready();
    return 0;
}

int rwnx_aic_cdev_fasync(int fd, struct file *filp, int on)
{
    struct rwnx_aic_chardev *pchardev = filp->private_data;
    fasync_helper(fd, filp, on, &pchardev->async_queue);
    //printk("rwnx_aic_cdev_fasync\r\n");
    return 0;
}

int rwnx_aic_cdev_release(struct inode* inode, struct file* filp)
{
    rwnx_aic_cdev_fasync(-1, filp, 0);
    //printk("rwnx_aic_cdev_release\r\n");
    return 0;
}

static struct file_operations aic_cdev_driver_fops = {
    .owner = THIS_MODULE,
    .open = rwnx_aic_cdev_open,
    .read = rwnx_aic_cdev_read,
    .write = rwnx_aic_cdev_write,
    .fasync = rwnx_aic_cdev_fasync,
    .release = rwnx_aic_cdev_release,
};

#define AIC_CDEV_MINOR    0
int rwnx_aic_cdev_driver_init(void)
{
    int ret = 0;
    struct device *devices;

    // alloc buff for fasync_info
    chardev.fasync_info = kzalloc(sizeof(struct rwnx_fasync_info), GFP_KERNEL);
    if (!chardev.fasync_info) {
        printk("%s fasync_info alloc fail\n", __func__);
        goto exit;
    }

    if (alloc_chrdev_region(&chardev.dev, AIC_CDEV_MINOR, 1, "aic_cdev_ioctl")) {
        printk("%s: alloc_chrdev_region failure\n", __FUNCTION__);
        goto free_fasync_info;
    }
    chardev.major = MAJOR(chardev.dev);

    // add cdev
    chardev.c_cdev = kzalloc(sizeof(struct cdev), GFP_KERNEL);
    if(IS_ERR(chardev.c_cdev)) {
        printk("%s: kmalloc failure\n", __FUNCTION__);
        ret = PTR_ERR(chardev.c_cdev);
        goto free_chrdev_region;
    }
    cdev_init(chardev.c_cdev, &aic_cdev_driver_fops);
    ret = cdev_add(chardev.c_cdev, chardev.dev, 1);
    if(ret < 0) {
        printk("%s: cdev_add failure\n", __FUNCTION__);
        goto free_chrdev_region;
    }

    // create device_class
    chardev.cdev_class = class_create(THIS_MODULE, "aic_cdev_class");
    if(IS_ERR(chardev.cdev_class)) {
        printk("%s: class_create failure\n", __FUNCTION__);
        ret = PTR_ERR(chardev.cdev_class);
        goto free_cdev;
    }

    // create device
    devices = device_create(chardev.cdev_class, NULL, MKDEV(chardev.major, AIC_CDEV_MINOR), NULL, "aic_cdev");
    if(IS_ERR(devices)) {
        printk("%s: device_create failure\n", __FUNCTION__);
        ret = PTR_ERR(devices);
        goto free_device_class;
    }

    printk("Create device: /dev/aic_cdev\n");

    // init fasync lock
    spin_lock_init(&chardev.fasync_lock);

    // init fasync-info
    INIT_LIST_HEAD(&chardev.fasync_list);
    INIT_WORK(&chardev.fasync_work, rwnx_aic_cdev_fasync_work);
    return 0;

free_device_class:
    class_destroy(chardev.cdev_class);
free_cdev:
    cdev_del(chardev.c_cdev);
free_chrdev_region:
    unregister_chrdev_region(chardev.dev, 1);
free_fasync_info:
    kfree(chardev.fasync_info);
exit:
    return ret;
}

void rwnx_aic_cdev_driver_deinit(void)
{
    RWNX_DBG(RWNX_FN_ENTRY_STR);

    if(chardev.c_cdev) {
        device_destroy(chardev.cdev_class, MKDEV(chardev.major,0));
        class_destroy(chardev.cdev_class);

        cdev_del(chardev.c_cdev);
        unregister_chrdev_region(chardev.dev, 1);

        kfree(chardev.fasync_info);
    }
}
#endif

/**
 * rwnx_platform_init() - Initialize the platform
 *
 * @rwnx_plat: platform data (already updated by platform driver)
 * @platform_data: Pointer to store the main driver data pointer (aka rwnx_hw)
 *                That will be set as driver data for the platform driver
 * Return: 0 on success, < 0 otherwise
 *
 * Called by the platform driver after it has been probed
 */
int rwnx_platform_init(struct rwnx_plat *rwnx_plat, void **platform_data)
{
    RWNX_DBG(RWNX_FN_ENTRY_STR);

    rwnx_plat->enabled = true;
    g_rwnx_plat = rwnx_plat;

    #ifdef CONFIG_VNET_MODE
    #ifdef CONFIG_APP_FASYNC
    if (rwnx_aic_cdev_driver_init()) {
        printk("aic_cdev init fail.\n");
        return -1;
    }
    #endif /* CONFIG_APP_FASYNC */

	rwnx_platform_custom_msg_vnet_init();
	#ifndef CONFIG_FAST_INSMOD
    if(rwnx_platform_get_mac_addr() != 0)
        return -1;
    #endif
    if(rwnx_platform_get_wlan_status() != 0)
        return -1;

    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 7, 0)
    memcpy(g_rwnx_vif.wdev.address, g_custom_msg_vnet.macaddr_cfm.mac_addr, 6);
    #else
    memcpy(g_rwnx_vif.address, g_custom_msg_vnet.macaddr_cfm.mac_addr, 6);
    #endif
    if(virt_net_init(&g_rwnx_vif)) {
        printk("vnet_dev init fail.\n");
        return -1;
    }

    // If come here, it indicates that driver will be loaded successfully.
    // Don`t send AICWF_CMD_WAITCFM cmd, so the function aicwf_sdio_probe
    // can return faster.
    rwnx_platform_get_vnet_setting();

    #elif defined(CONFIG_RAWDATA_MODE)
    rwnx_nlaic_init(rwnx_plat, platform_data);
    #endif /* CONFIG_VNET_MODE */

    return 0;
}

/**
 * rwnx_platform_deinit() - Deinitialize the platform
 *
 * @rwnx_hw: main driver data
 *
 * Called by the platform driver after it is removed
 */
void rwnx_platform_deinit(void)
{
    RWNX_DBG(RWNX_FN_ENTRY_STR);
    #ifdef CONFIG_VNET_MODE
    // delete keep alive timer
    if (g_custom_msg_vnet.keep_alive.status != KEEP_ALIVE_DISABLE) {
        if(timer_pending(&g_custom_msg_vnet.keep_alive.timer)) {
            del_timer_sync(&g_custom_msg_vnet.keep_alive.timer);
        }
    }

    // deinit netdevice
    virt_net_exit();

    #ifdef AICWF_SDIO_SUPPORT
    // deinit fasync char device
    #ifdef CONFIG_APP_FASYNC
    rwnx_aic_cdev_driver_deinit();
    #endif
    #endif

    #elif defined(CONFIG_RAWDATA_MODE)
    rwnx_nlaic_deinit();
    #endif
}

/**
 * rwnx_platform_register_drv() - Register all possible platform drivers
 */
int rwnx_platform_register_drv(void)
{
    return 0;//rwnx_pci_register_drv();
}


/**
 * rwnx_platform_unregister_drv() - Unegister all platform drivers
 */
void rwnx_platform_unregister_drv(void)
{
    //return rwnx_pci_unregister_drv();
}

struct device *rwnx_platform_get_dev(struct rwnx_plat *rwnx_plat)
{
#ifdef AICWF_SDIO_SUPPORT
    return rwnx_plat->sdiodev->dev;
#endif
#ifdef AICWF_USB_SUPPORT
    return rwnx_plat->usbdev->dev;
#endif
    return &(rwnx_plat->pci_dev->dev);
}

