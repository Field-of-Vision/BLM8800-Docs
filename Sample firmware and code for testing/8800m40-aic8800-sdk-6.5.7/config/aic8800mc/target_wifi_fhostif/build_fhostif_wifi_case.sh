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
    opt=$opt" USE_LIB_DRV=on USE_LIB_WIFI=on USE_LIB_WPA=on"
  elif [ $var = "-libgen" ]; then
    opt=$opt" GEN_LIB_DRV=on GEN_LIB_WIFI=on GEN_LIB_WPA=on"
  else
    opt=$opt" "$var
  fi
done

python ../../../tools/scons.py -u . PRODUCT=host-wifi PLF=aic8800mc BT=armgcc_4_8 BUILD_CMD="$0 $*" \
    SOFTAP=off FHOST_APP=fhostif AON=on BAND5G=off ROM_VER=auto PING=on IPERF=on \
    TGT_MODE=wifi_fhostif CHKSUM=off WIFI_RAM_VER=off HOSTIF=usb HEAP_SIZE=0xf800 $opt