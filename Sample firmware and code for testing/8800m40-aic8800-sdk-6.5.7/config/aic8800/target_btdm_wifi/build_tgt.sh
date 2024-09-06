#!/bin/sh -x

opt=$@

sh build_bleonly_wifi.sh $opt
if [ $? -eq 0 ]; then
    echo '************************************succeed'
else
    echo '************************************failed'
    exit 1
fi

sh build_btdm_wifi.sh $opt
if [ $? -eq 0 ]; then
    echo '************************************succeed'
else
    echo '************************************failed'
    exit 1
fi
