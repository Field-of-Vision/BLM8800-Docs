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
    opt=$opt" USE_LIB_DRV=on USE_LIB_BT=on USE_LIB_AUDIO=on USE_LIB_AUDIO=on"
  elif [ $var = "-libgen" ]; then
    opt=$opt" GEN_LIB_DRV=on GEN_LIB_BT=on GEN_LIB_AUDIO=on GEN_LIB_AUDIO=on"
  else
    opt=$opt" "$var
  fi
done

python ../../../tools/scons.py -u . PRODUCT=host-bt PLF=aic8800 BT=armgcc_4_8 BUILD_CMD="$0 $*" HW_PLATFORM=asic \
        TGT_MODE=btdm \
        PMIC_VER=aud AON=on \
        BT_BLE=on BTDM=on BT_AUDIO=on APPS=on\
        AUDIO=on UTILS=on HW_SBC=on AAC=on PMIC_MCLK=on BT_PROMPT=off \
        ROM_VER=auto \
        LPO_512K=off VCORE_CALIB=on LPIRAM=off DBGINFO=off $opt
