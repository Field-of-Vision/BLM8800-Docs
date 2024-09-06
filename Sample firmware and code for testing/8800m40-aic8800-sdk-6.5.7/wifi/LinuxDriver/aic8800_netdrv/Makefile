RWNX_VERS_NUM := 6.5.2.7

# MODULE
CONFIG_AIC8800_WLAN_SUPPORT = m
MODULE_NAME = aic8800_netdrv

# Platform support list
CONFIG_PLATFORM_NANOPI_M4 ?= n
CONFIG_PLATFORM_ALLWINNER ?= n
CONFIG_PLATFORM_INGENIC_T31 ?= n
CONFIG_PLATFORM_INGENIC_T40 ?= n
CONFIG_PLATFORM_INGENIC_T41 ?= n
CONFIG_PLATFORM_FH8852v201L ?= n
CONFIG_PLATFORM_UBUNTU ?= y

# Driver mode support list
CONFIG_VNET_MODE    ?= y
CONFIG_RAWDATA_MODE ?= n

# Insmod mode
CONFIG_FAST_INSMOD ?= n

# Msg Callback setting
CONFIG_APP_FASYNC ?= n

# Set thread priority
CONFIG_TXRX_THREAD_PRIO = y

CONFIG_USB_SUPPORT   = y
CONFIG_SDIO_SUPPORT  = n
CONFIG_RX_REORDER   ?= y
CONFIG_SDIO_PWRCTRL ?= y
ifeq ($(CONFIG_VNET_MODE), y)
CONFIG_TX_NETIF_FLOWCTRL = y
endif
ifeq ($(CONFIG_RAWDATA_MODE), y)
CONFIG_TX_NETIF_FLOWCTRL = n
endif

# FW ARCH:
CONFIG_RWNX_TL4 ?= n
CONFIG_RWNX_FULLMAC ?= y

# Enable HW queue for Broadcast/Multicast traffic (need FW support)
CONFIG_RWNX_BCMC ?= y

# Enable A-MSDU support (need FW support)
## Select this if FW is compiled with AMSDU support
CONFIG_RWNX_SPLIT_TX_BUF ?= n
## Select this TO send AMSDU
CONFIG_RWNX_AMSDUS_TX ?= n

# FW VARS
ccflags-y += -DNX_VIRT_DEV_MAX=4
ccflags-y += -DNX_REMOTE_STA_MAX=10
ccflags-y += -DNX_MU_GROUP_MAX=62
ccflags-y += -DNX_TXDESC_CNT=64
ccflags-y += -DNX_TX_MAX_RATES=4
ccflags-y += -DNX_CHAN_CTXT_CNT=3

ccflags-$(CONFIG_PLATFORM_NANOPI_M4)   += -DCONFIG_NANOPI_M4
ccflags-$(CONFIG_PLATFORM_INGENIC_T31) += -DCONFIG_INGENIC_T31
ccflags-$(CONFIG_PLATFORM_INGENIC_T40) += -DCONFIG_INGENIC_T40
ccflags-$(CONFIG_PLATFORM_ALLWINNER)   += -DCONFIG_PLATFORM_ALLWINNER

ccflags-$(CONFIG_VNET_MODE)    += -DCONFIG_VNET_MODE
ccflags-$(CONFIG_RAWDATA_MODE) += -DCONFIG_RAWDATA_MODE
ccflags-$(CONFIG_FAST_INSMOD)  += -DCONFIG_FAST_INSMOD
ccflags-$(CONFIG_APP_FASYNC)   += -DCONFIG_APP_FASYNC
ccflags-$(CONFIG_RX_REORDER)   += -DAICWF_RX_REORDER

ccflags-y += -I$(src)/.
ccflags-y += -DCONFIG_RWNX_FULLMAC
ccflags-$(CONFIG_RWNX_TL4) += -DCONFIG_RWNX_TL4
ccflags-$(CONFIG_RWNX_SPLIT_TX_BUF) += -DCONFIG_RWNX_SPLIT_TX_BUF
ccflags-$(CONFIG_TX_NETIF_FLOWCTRL) += -DCONFIG_TX_NETIF_FLOWCTRL
ccflags-$(CONFIG_TXRX_THREAD_PRIO)  += -DCONFIG_TXRX_THREAD_PRIO

ifeq ($(CONFIG_RWNX_SPLIT_TX_BUF), y)
ccflags-$(CONFIG_RWNX_AMSDUS_TX) += -DCONFIG_RWNX_AMSDUS_TX
endif

ifeq ($(CONFIG_SDIO_SUPPORT), y)
ccflags-y += -DAICWF_SDIO_SUPPORT
ccflags-$(CONFIG_SDIO_PWRCTRL) += -DCONFIG_SDIO_PWRCTRL
endif

ifeq ($(CONFIG_USB_SUPPORT), y)
ccflags-y += -DAICWF_USB_SUPPORT
endif

ifeq ($(CONFIG_RWNX_BCMC), y)
ccflags-y += -DNX_TXQ_CNT=5
else
ccflags-y += -DNX_TXQ_CNT=4
endif

obj-$(CONFIG_AIC8800_WLAN_SUPPORT) := $(MODULE_NAME).o
$(MODULE_NAME)-y :=       \
	rwnx_main.o           \
	rwnx_rx.o             \
	rwnx_tx.o             \
	rwnx_platform.o       \
	rwnx_term_ops.o       \
	virt_net.o            \
	aicwf_custom_utils.o

$(MODULE_NAME)-$(CONFIG_SDIO_SUPPORT)    += sdio_host.o
$(MODULE_NAME)-$(CONFIG_SDIO_SUPPORT)    += aicwf_txrxif.o
$(MODULE_NAME)-$(CONFIG_SDIO_SUPPORT)    += aicwf_sdio.o

$(MODULE_NAME)-$(CONFIG_USB_SUPPORT)     += usb_host.o
$(MODULE_NAME)-$(CONFIG_USB_SUPPORT)     += aicwf_txrxif.o
$(MODULE_NAME)-$(CONFIG_USB_SUPPORT)     += aicwf_usb.o


ifeq ($(CONFIG_PLATFORM_ROCHCHIP), y)
KDIR  := /your_kernel_dir/kernel
ARCH ?= arm
CROSS_COMPILE ?= /your_cross_compile_dir/arm-linux-gnueabihf-
ccflags-y += -DANDROID_PLATFORM
endif

ifeq ($(CONFIG_PLATFORM_ALLWINNER), y)
ccflags-y += -DANDROID_PLATFORM
endif

ifeq ($(CONFIG_PLATFORM_UBUNTU), y)
KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)
KVER := $(shell uname -r)
MODDESTDIR := /lib/modules/$(KVER)/kernel/drivers/net/wireless/aic8800
ARCH ?= x86_64
CROSS_COMPILE ?=
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
endif

ifeq ($(CONFIG_PLATFORM_INGENIC_T31), y)
ARCH ?= mips
CROSS_COMPILE ?=mips-linux-gnu-
PWD ?= .
#KERNELDIR depends on the location of t31 kernel code
KERNELDIR ?=/your_kernel_dir/kernel
all: modules
modules clean:
	@$(PWD)/mklink.sh
	$(MAKE) -C $(KERNELDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $@
	@$(PWD)/mklink.sh clean
endif

ifeq ($(CONFIG_PLATFORM_INGENIC_T40), y)
ARCH ?= mips
CROSS_COMPILE ?=mips-linux-gnu-
PWD ?= .
#KERNELDIR depends on the location of t40 kernel code
KERNELDIR ?=/your_kernel_dir/kernel-4.4.94
all: modules
modules clean:
	@$(PWD)/mklink.sh
	$(MAKE) -C $(KERNELDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $@
	@$(PWD)/mklink.sh clean
endif

ifeq ($(CONFIG_PLATFORM_INGENIC_T41), y)
ARCH ?= mips
CROSS_COMPILE ?=mips-linux-gnu-
PWD ?= .
#KERNELDIR depends on the location of t41 kernel code
KERNELDIR ?=/your_kernel_dir/kernel-4.4.94
all: modules
modules clean:
	@$(PWD)/mklink.sh
	$(MAKE) -C $(KERNELDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $@
	@$(PWD)/mklink.sh clean
endif

ifeq ($(CONFIG_PLATFORM_FH8852v201L), y)
ARCH ?= arm
CROSS_COMPILE ?= arm-fullhanv3-linux-uclibcgnueabi-
PWD ?= .
#KDIR depends on the location of FH8852v201L kernel code
KDIR  := /your_kernel_dir/kernel
all: modules
modules:
	make -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	rm -rf *.o *.ko *.o.* *.mod.* modules.* Module.* .a* .o* .*.o.* *.mod .tmp* .cache.mk
endif

