#!/bin/sh

# check toolchain version & libary path
ver=`arm-none-eabi-gcc --version | grep release | cut -d ')' -f2 | awk '{print $1}'`
if [ "$ver" != "9.2.1" ]; then
  echo "WRONG toolchain: $ver"
  exit 1
fi
ver=`echo $GNUARM_4_8_LIB | awk -F"/" '{print $NF}'`
if [ "$ver" != "9.2.1" ]; then
  echo "WRONG libary path: $GNUARM_4_8_LIB"
  exit 1
fi

# build rom files
opt=""
if [ -f ./build_tgt.sh ]; then
  arg=$@" -libuse"
else
  arg=$@
fi
for var in $arg
do
  if [ $var = "-libuse" ]; then
    opt=$opt" USE_LIB_DRV=on USE_LIB_WIFI=on USE_LIB_BT=on"
  elif [ $var = "-libgen" ]; then
    opt=$opt" GEN_LIB_DRV=on GEN_LIB_WIFI=on GEN_LIB_BT=on"
  else
    opt=$opt" "$var
  fi
done

python ../../../tools/scons.py -u . PRODUCT=host-dwb PLF=aic8800 BT=armgcc_4_8 BUILD_CMD="$0 $*" PMIC_VER=lite AON=on \
        TGT_MODE=dwb \
        BT_BLE=on BT_AUDIO=off APPS=on BLE_ONLY=on \
        AUDIO=off UTILS=on HW_SBC=off AAC=off BT_PROMPT=off CONSOLE=on \
        BT_USER=on BLE_APP_SMARTCONFIG=off BLE_APP_HID=on \
        LPO_512K=off VCORE_CALIB=on HOSTIF=usb FHOST_APP=hostif $opt
