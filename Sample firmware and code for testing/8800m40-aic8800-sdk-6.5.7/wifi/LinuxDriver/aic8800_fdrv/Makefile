RWNX_VERS_NUM := 6.4.3.0
PWD=$(shell pwd)
# Platform support list
CONFIG_PLATFORM_NANOPI_M4 ?= n
CONFIG_PLATFORM_ROCHCHIP ?= n
CONFIG_PLATFORM_ALLWINNER ?= n
CONFIG_PLATFORM_INGENIC_T20 ?= n
CONFIG_PLATFORM_AMLOGIC ?= n
CONFIG_PLATFORM_UBUNTU ?= y

CONFIG_AIC8800_WLAN_SUPPORT = m
MODULE_NAME = aic8800_fdrv

# Support of bootrom start
CONFIG_START_FROM_BOOTROM = y

# Support of pmic setting, new version bootrom avaliable
CONFIG_PMIC_SETTING ?=y

# ROM patch enabled option
CONFIG_ROM_PATCH_EN ?=n

# Support HE on old version kernel
CONFIG_HE_FOR_OLD_KERNEL ?= n
ifeq ($(CONFIG_PLATFORM_ALLWINNER), y)
CONFIG_HE_FOR_OLD_KERNEL = y
endif
ifeq ($(CONFIG_PLATFORM_INGENIC_T20), y)
CONFIG_HE_FOR_OLD_KERNEL = y
endif

# Support chip with mcu
CONFIG_MCU_INTEGRATED ?= n
CONFIG_MCU_MESSAGE ?= n
ifeq ($(CONFIG_MCU_INTEGRATED), y)
CONFIG_PMIC_SETTING = n
else
CONFIG_MCU_MESSAGE ?= n
endif

#
# WAITING FOR KCONFIG {
#
CONFIG_RWNX_FULLMAC ?= y
CONFIG_RWNX_FHOST ?= n

#
# DEBUG OPTIONS
CONFIG_RWNX_UM_HELPER_DFLT ?= "/dini/dini_bin/rwnx_umh.sh"
CONFIG_AIC_FW_PATH = "/vendor/etc/firmware"
export CONFIG_AIC_FW_PATH

#
# FW ARCH:
CONFIG_RWNX_SDM ?= n
CONFIG_RWNX_TL4 ?= n

# IPC version
CONFIG_RWNX_OLD_IPC ?= n

# Support of P2P DebugFS for enabling/disabling NoA and OppPS
CONFIG_RWNX_P2P_DEBUGFS ?= y
CONFIG_DEBUG_FS ?=y

# Support of sysfs
CONFIG_RWNX_SYSFS ?= y

# FW path
ifeq ($(CONFIG_PLATFORM_NANOPI_M4), y) # NANOPI_M4
CONFIG_VENDOR_SPECIFIED_FW_PATH ?= "/vendor/firmware"
else # NANOPI_M4
ifeq ($(CONFIG_PLATFORM_ALLWINNER), y) # ALLWINNER
CONFIG_VENDOR_SPECIFIED_FW_PATH ?= "/vendor/etc/firmware"
else # ALLWINNER
ifeq ($(CONFIG_PLATFORM_INGENIC_T20), y) # INGENTIC_T20
CONFIG_VENDOR_SPECIFIED_FW_PATH ?= "/lib/firmware"
else # INGENTIC_T20
ifeq ($(CONFIG_PLATFORM_UBUNTU), y) # PC
#CONFIG_VENDOR_SPECIFIED_FW_PATH ?= "/lib/firmware"
CONFIG_VENDOR_SUBDIR_NAME ?= "aic8800"
endif # PC
endif # INGENTIC_T20
endif # ALLWINNER
endif # NANOPI_M4
ifneq ($(CONFIG_VENDOR_SPECIFIED_FW_PATH),)
subdir-ccflags-y += -DCONFIG_VENDOR_SPECIFIED_FW_PATH=\"$(CONFIG_VENDOR_SPECIFIED_FW_PATH)\"
endif
ifneq ($(CONFIG_VENDOR_SUBDIR_NAME),)
subdir-ccflags-y += -DCONFIG_VENDOR_SUBDIR_NAME=\"$(CONFIG_VENDOR_SUBDIR_NAME)\"
endif

#
# } // WAITING FOR KCONFIG
#

# Enable A-MSDU support (need FW support)
## Select this if FW is compiled with AMSDU support
CONFIG_RWNX_SPLIT_TX_BUF ?= n
## Select this TO send AMSDU
CONFIG_RWNX_AMSDUS_TX ?= n

# Enable BFMER support (need FW support)
CONFIG_RWNX_BFMER ?= n

CONFIG_SDIO_SUPPORT =n
CONFIG_USB_SUPPORT =y
CONFIG_RX_REORDER ?=y
CONFIG_ARP_OFFLOAD =y
CONFIG_USE_5G =y
CONFIG_RADAR_OR_IR_DETECT =n
CONFIG_DOWNLOAD_FW =y
CONFIG_LOAD_USERCONFIG ?=y
CONFIG_CHIP_REBOOT ?=n
CONFIG_RFTEST=n
CONFIG_USB_BT =n
CONFIG_MAC_RANDOM_IF_NO_MAC_IN_EFUSE=n
CONFIG_SDIO_PWRCTRL ?= n


# Support of MU-MIMO transmission (need FW support)
ifeq ($(CONFIG_RWNX_BFMER), y)
CONFIG_RWNX_MUMIMO_TX ?= n
else
CONFIG_RWNX_MUMIMO_TX = n
endif

# Enable handling of radar event
CONFIG_RWNX_RADAR ?= y

# Enable HW queue for Broadcast/Multicast traffic (need FW support)
CONFIG_RWNX_BCMC ?= y

# Enable Monitor+Data interface support (need FW support)
CONFIG_RWNX_MON_DATA =y
CONFIG_RWNX_MON_XMIT ?= y
CONFIG_RWNX_MON_RXFILTER ?= n

# extra DEBUG config
CONFIG_RWNX_SW_PROFILING ?= n
CONFIG_RWNX_DBG ?= n

obj-$(CONFIG_AIC8800_WLAN_SUPPORT) := $(MODULE_NAME).o
$(MODULE_NAME)-y := \
    rwnx_msg_tx.o          \
    rwnx_msg_rx.o          \
    rwnx_utils.o           \
    rwnx_cmds.o            \
    rwnx_irqs.o            \
    rwnx_cfgfile.o         \
    rwnx_strs.o            \
    rwnx_rx.o              \
    rwnx_tx.o              \
    rwnx_txq.o             \
    rwnx_main.o            \
    rwnx_mod_params.o      \
    rwnx_mesh.o            \
    rwnx_platform.o        \
    rwnx_pci.o             \
    rwnx_dini.o            \
    rwnx_v7.o              \
    ipc_host.o             \
    rwnx_tdls.o

$(MODULE_NAME)-$(CONFIG_RWNX_RADAR)       += rwnx_radar.o
$(MODULE_NAME)-$(CONFIG_DEBUG_FS)         += rwnx_debugfs.o
$(MODULE_NAME)-$(CONFIG_DEBUG_FS)         += rwnx_fw_dump.o
$(MODULE_NAME)-$(CONFIG_DEBUG_FS)         += rwnx_fw_trace.o
$(MODULE_NAME)-$(CONFIG_NL80211_TESTMODE) += rwnx_testmode.o
$(MODULE_NAME)-$(CONFIG_RWNX_BFMER)       += rwnx_bfmer.o
$(MODULE_NAME)-$(CONFIG_RWNX_MUMIMO_TX)   += rwnx_mu_group.o
$(MODULE_NAME)-$(CONFIG_SDIO_SUPPORT)     += sdio_host.o
$(MODULE_NAME)-$(CONFIG_SDIO_SUPPORT)     += aicwf_txrxif.o
$(MODULE_NAME)-$(CONFIG_SDIO_SUPPORT)     += aicwf_sdio.o

$(MODULE_NAME)-$(CONFIG_USB_SUPPORT)     += usb_host.o
$(MODULE_NAME)-$(CONFIG_USB_SUPPORT)     += aicwf_txrxif.o
$(MODULE_NAME)-$(CONFIG_USB_SUPPORT)     += aicwf_usb.o

ccflags-$(CONFIG_DEBUG_FS) += -DCONFIG_RWNX_DEBUGFS
ccflags-$(CONFIG_DEBUG_FS) += -DCONFIG_RWNX_UM_HELPER_DFLT=\"$(CONFIG_RWNX_UM_HELPER_DFLT)\"
ccflags-$(CONFIG_RWNX_P2P_DEBUGFS) += -DCONFIG_RWNX_P2P_DEBUGFS

ccflags-$(CONFIG_RWNX_SYSFS) += -DCONFIG_RWNX_SYSFS

# FW VARS
ccflags-y += -DNX_VIRT_DEV_MAX=4
ccflags-y += -DNX_REMOTE_STA_MAX=10
ccflags-y += -DNX_MU_GROUP_MAX=62
ccflags-y += -DNX_TXDESC_CNT=64
ccflags-y += -DNX_TX_MAX_RATES=4
ccflags-y += -DNX_CHAN_CTXT_CNT=3

# FW ARCH:
ccflags-$(CONFIG_RWNX_SDM) += -DCONFIG_RWNX_SDM
ccflags-$(CONFIG_RWNX_TL4) += -DCONFIG_RWNX_TL4
ccflags-$(CONFIG_RWNX_OLD_IPC) += -DCONFIG_RWNX_OLD_IPC
ccflags-$(CONFIG_PLATFORM_NANOPI_M4) += -DCONFIG_NANOPI_M4
ccflags-$(CONFIG_PLATFORM_INGENIC_T20) += -DCONFIG_INGENIC_T20
ccflags-$(CONFIG_PLATFORM_ALLWINNER) += -DCONFIG_PLATFORM_ALLWINNER
ccflags-$(CONFIG_START_FROM_BOOTROM) += -DCONFIG_START_FROM_BOOTROM
ccflags-$(CONFIG_PMIC_SETTING) += -DCONFIG_PMIC_SETTING
ccflags-$(CONFIG_ROM_PATCH_EN) += -DCONFIG_ROM_PATCH_EN
ccflags-$(CONFIG_HE_FOR_OLD_KERNEL) += -DCONFIG_HE_FOR_OLD_KERNEL
ccflags-$(CONFIG_MCU_INTEGRATED) += -DCONFIG_MCU_INTEGRATED
ccflags-$(CONFIG_MCU_MESSAGE) += -DCONFIG_MCU_MESSAGE
ccflags-$(CONFIG_PLATFORM_ALLWINNER) += -DCONFIG_COEX
ccflags-$(CONFIG_PLATFORM_NANOPI_M4) += -DCONFIG_COEX

ccflags-y += -DCONFIG_RWNX_FULLMAC
ccflags-y += -I$(src)/.
ccflags-$(CONFIG_RWNX_RADAR) += -DCONFIG_RWNX_RADAR
ccflags-$(CONFIG_RWNX_MON_DATA) += -DCONFIG_RWNX_MON_DATA
ccflags-$(CONFIG_RWNX_MON_XMIT) += -DCONFIG_RWNX_MON_XMIT
ccflags-$(CONFIG_RWNX_MON_RXFILTER) += -DCONFIG_RWNX_MON_RXFILTER
ccflags-$(CONFIG_RWNX_BFMER) += -DCONFIG_RWNX_BFMER
ccflags-$(CONFIG_RWNX_SPLIT_TX_BUF) += -DCONFIG_RWNX_SPLIT_TX_BUF
ifeq ($(CONFIG_RWNX_SPLIT_TX_BUF), y)
ccflags-$(CONFIG_RWNX_AMSDUS_TX) += -DCONFIG_RWNX_AMSDUS_TX
endif
ccflags-$(CONFIG_RWNX_DBG) += -DCONFIG_RWNX_DBG
ccflags-$(CONFIG_RWNX_SW_PROFILING) += -DCONFIG_RWNX_SW_PROFILING
ccflags-$(CONFIG_RWNX_MUMIMO_TX) += -DCONFIG_RWNX_MUMIMO_TX
ccflags-$(CONFIG_RFTEST) += -DCONFIG_RFTEST

ifeq ($(CONFIG_SDIO_SUPPORT), y)
ccflags-y += -DAICWF_SDIO_SUPPORT
ccflags-$(CONFIG_SDIO_PWRCTRL) += -DCONFIG_SDIO_PWRCTRL
endif

ifeq ($(CONFIG_USB_SUPPORT), y)
ccflags-y += -DAICWF_USB_SUPPORT
endif

ifeq ($(CONFIG_RWNX_MUMIMO_TX), y)
ccflags-y += -DCONFIG_USER_MAX=2
else
ccflags-y += -DCONFIG_USER_MAX=1
endif

ifeq ($(CONFIG_RWNX_BCMC), y)
ccflags-y += -DNX_TXQ_CNT=5
else
ccflags-y += -DNX_TXQ_CNT=4
endif

# For old kernel (<=3.19)
ifeq ($(shell test $(VERSION) -lt 4 -a "$(CONFIG_VENDOR_RWNX)" = y ; echo $$?),0)
ccflags-y += -DCONFIG_VENDOR_RWNX_VHT_NO80
endif

ccflags-$(CONFIG_RX_REORDER) += -DAICWF_RX_REORDER
ccflags-$(CONFIG_ARP_OFFLOAD) += -DAICWF_ARP_OFFLOAD
ccflags-$(CONFIG_USE_5G) += -DUSE_5G
ccflags-$(CONFIG_RADAR_DETECT) += -DRADAR_OR_IR_DETECT
ccflags-$(CONFIG_DOWNLOAD_FW)  += -DCONFIG_DOWNLOAD_FW
ccflags-$(CONFIG_LOAD_USERCONFIG) += -DCONFIG_LOAD_USERCONFIG
ccflags-$(CONFIG_CHIP_REBOOT) += -DCONFIG_CHIP_REBOOT
ccflags-$(CONFIG_USB_BT)  += -DCONFIG_USB_BT
ccflags-$(CONFIG_MAC_RANDOM_IF_NO_MAC_IN_EFUSE) += -DCONFIG_MAC_RANDOM_IF_NO_MAC_IN_EFUSE

ifeq ($(CONFIG_PLATFORM_ROCHCHIP), y)
KDIR  := /yourlocallocation/Android10/kernel/
ARCH ?= arm
CROSS_COMPILE ?= /Android10/SDK/prebuilts/gcc/linux-x86/arm/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
ccflags-y += -DANDROID_PLATFORM
endif

ifeq ($(CONFIG_PLATFORM_ALLWINNER), y)
ccflags-y += -DANDROID_PLATFORM
endif

ifeq ($(CONFIG_PLATFORM_INGENIC_T20), y)
KDIR := ../../../../../..//kernel
ARCH ?= mips
CROSS_COMPILE ?= $(PWD)/../../../../../../tools/toolchains/mips-gcc540-glibc222-64bit-r3.3.0/bin/mips-linux-uclibc-gnu-
endif

ifeq ($(CONFIG_PLATFORM_AMLOGIC), y)
ccflags-y += -DANDROID_PLATFORM
endif

ifeq ($(CONFIG_PLATFORM_UBUNTU), y)
KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)
KVER := $(shell uname -r)
MODDESTDIR := /lib/modules/$(KVER)/kernel/drivers/net/wireless/
ARCH ?= x86_64
CROSS_COMPILE ?=
endif


all: modules
modules:
	make -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

install:
	mkdir -p $(MODDESTDIR)
	install -p -m 644 $(MODULE_NAME).ko  $(MODDESTDIR)
	/sbin/depmod -a ${KVER}

uninstall:
	rm -rfv $(MODDESTDIR)/$(MODULE_NAME).ko
	/sbin/depmod -a ${KVER}

clean:
	rm -rf *.o *.ko *.o.* *.mod.* modules.* Module.* .a* .o* .*.o.* *.mod .tmp* .cache.mk

