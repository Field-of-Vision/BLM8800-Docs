#!/bin/sh -x

opt=$@

sh build_wifi_case_8800mc.sh $opt
if [ $? -eq 0 ]; then
    echo '************************************succeed'
else
    echo '************************************failed'
    exit 1
fi

sh build_wifi_console_iperf_ping.sh $opt
if [ $? -eq 0 ]; then
    echo '************************************succeed'
else
    echo '************************************failed'
    exit 1
fi

