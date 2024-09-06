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
    opt=$opt" USE_LIB_DRV=on USE_LIB_WIFI=on USE_LIB_WPA=on USE_LIB_AUDIO=on"
  elif [ $var = "-libgen" ]; then
    opt=$opt" GEN_LIB_DRV=on GEN_LIB_WIFI=on GEN_LIB_WPA=on GEN_LIB_AUDIO=on"
  else
    opt=$opt" "$var
  fi
done

python ../../../tools/scons.py -u . PRODUCT=host-wifi PLF=aic8800 BT=armgcc_4_8 BUILD_CMD="$0 $*" \
        TGT_MODE=wifi_audio WIFI_AUD_MEM=on\
        FHOST_APP=wh SOFTAP=on BAND5G=on KEY_MODULE=on LED_MODULE=on\
        PMIC_VER=aud \
        UTILS=on HEAP_SIZE=0x1B800 \
        ROM_VER=3 LPO_512K=off \
        ASIO=on WIFI_AUDIO=on AUDIO=on \
        WIFI_ENGINEERING_MODE=on \
        WIFI_VOICE_ROLE=headset TGTNAME=wifi_wh_headset $opt
