#!/bin/sh -x

opt=$@

sh build_btdm.sh $opt
if [ $? -eq 0 ]; then
    echo '************************************succeed'
else
    echo '************************************failed'
    exit 1
fi
