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
    opt=$opt" USE_LIB_DRV=on USE_LIB_BT=on"
  elif [ $var = "-libgen" ]; then
    opt=$opt" GEN_LIB_DRV=on GEN_LIB_BT=on"
  else
    opt=$opt" "$var
  fi
done

python ../../../tools/scons.py -u . PRODUCT=host-bt PLF=aic8800mc BT=armgcc_4_8 BUILD_CMD="$0 $*" AON=off \
        TGT_MODE=bt \
        APPS=on A2DP=off A2DP_SOURCE=off HFP_AG=on LINK_ONE=on TGTNAME=bt_ag_dongle CONSOLE=on AUD_USED=off \
        ROM_VER=auto HEAP_SIZE=0xc000 $opt
