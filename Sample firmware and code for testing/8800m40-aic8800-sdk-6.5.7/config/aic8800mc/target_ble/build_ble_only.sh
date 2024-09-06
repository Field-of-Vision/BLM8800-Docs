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
# BLE_DFT_STATE       : adv/scan/init/none
# BLE_APP_AUDTRANSMIT : client/server/none
# BLE_APP_SMARTCONFIG : off/on
# BLE_APP_HID         : off/on
# BLE_APP_UDF         : client/server/all_role/none
python ../../../tools/scons.py -u . PRODUCT=host-bt PLF=aic8800mc BT=armgcc_4_8 BUILD_CMD="$0 $*" AON=off \
        TGT_MODE=ble \
        BT_BLE=on BT_AUDIO=off APPS=on BLE_ONLY=on BT_USER=on \
        BLE_DFT_STATE=adv BLE_APP_AUDTRANSMIT=none BLE_APP_SMARTCONFIG=off BLE_APP_HID=off BLE_APP_UDF=all_role \
        AUDIO=off UTILS=on HW_SBC=off AAC=off BT_PROMPT=off CONSOLE=on \
        ROM_VER=auto HEAP_SIZE=0xc000 $opt
