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
    opt=$opt" USE_LIB_DRV=on USE_LIB_BT=on USE_LIB_WIFI=on USE_LIB_WPA=on USE_LIB_AUDIO=on"
  elif [ $var = "-libgen" ]; then
    opt=$opt" GEN_LIB_DRV=on GEN_LIB_BT=on GEN_LIB_WIFI=on GEN_LIB_WPA=on GEN_LIB_AUDIO=on"
  else
    opt=$opt" "$var
  fi
done

python ../../../tools/scons.py -u . PRODUCT=host-wb PLF=aic8800 BT=armgcc_4_8 BUILD_CMD="$0 $*" HW_PLATFORM=asic AON=on \
        TGT_MODE=bt_wifi_audio \
        BT_AUDIO=on WIFI_AUDIO=on AUD_USED=on APPS=on HEAP_SIZE=0x20000\
        AUDIO=on ASIO=on UTILS=on HW_SBC=on AAC=on BT_PROMPT=off \
        CHKSUM=off SOFTAP=on FHOST_APP=wh BAND5G=on TGTNAME=host_wb_combo \
        ROM_VER=auto \
        PMIC_VER=aud LPO_512K=off VCORE_CALIB=on LPIRAM=off DBGINFO=off \
        WIFI_ENGINEERING_MODE=off \
        WIFI_VOICE_ROLE=headset TGTNAME=wifi_bt_combo $opt
