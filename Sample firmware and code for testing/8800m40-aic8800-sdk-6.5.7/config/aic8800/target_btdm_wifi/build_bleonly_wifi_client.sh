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
# BLE_DFT_STATE       : adv/scan/init/none
# BLE_APP_AUDTRANSMIT : client/server/none
# BLE_APP_SMARTCONFIG : off/on
# BLE_APP_HID         : off/on
python ../../../tools/scons.py -u . PRODUCT=host-wb PLF=aic8800 BT=armgcc_4_8 BUILD_CMD="$0 $*" PMIC_VER=aud AON=on \
        TGT_MODE=btdm_wifi BAND5G=on \
        BT_BLE=on BTDM=off APPS=on BLE_ONLY=on\
        BLE_DFT_STATE=scan BLE_APP_AUDTRANSMIT=client BLE_APP_SMARTCONFIG=off BLE_APP_HID=off\
        BT_AUDIO=on AUD_USED=on \
        AUDIO=on ASIO=on UTILS=on HW_SBC=on AAC=off BT_PROMPT=off \
        ROM_VER=auto FHOST_APP=console  MQTT=on HEAP_SIZE=0x20000 \
        TGTNAME=btdm_wifi $opt
