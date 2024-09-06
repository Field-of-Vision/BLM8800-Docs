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

python ../../../tools/scons.py -u . PRODUCT=host-wifi PLF=aic8800 BT=armgcc_4_8 BUILD_CMD="$0 $*" PMIC_VER=lite \
        TGT_MODE=m2d \
        TGTNAME=m2d_mcu_wifi \
        M2D=wifi M2D_OTA=on CONSOLE=on PMIC_LP=off \
        ROM_VER=auto REMAIN_ON_MCU=off CODE_START_ADDR=0x08004000 SOFTWDG=on\
        HOSTIF=usb FHOST_APP=hostif $opt
