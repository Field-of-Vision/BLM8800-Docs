#!/bin/sh -x

opt=$@

sh build_wifi_wapi_case.sh $opt
if [ $? -eq 0 ]; then
    echo '************************************succeed'
else
    echo '************************************failed'
    exit 1
fi
