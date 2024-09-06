#!/bin/sh -x

opt=$@

sh build_wifi_console_iperf_ping_wapi.sh $opt
if [ $? -eq 0 ]; then
    echo '************************************succeed'
else
    echo '************************************failed'
    exit 1
fi
