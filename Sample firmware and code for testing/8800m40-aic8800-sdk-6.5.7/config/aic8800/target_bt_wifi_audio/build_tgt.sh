#!/bin/sh -x

opt=$@

sh build_bt_wifi_combo.sh $opt
if [ $? -eq 0 ]; then
    echo '************************************succeed'
else
    echo '************************************failed'
    exit 1
fi

