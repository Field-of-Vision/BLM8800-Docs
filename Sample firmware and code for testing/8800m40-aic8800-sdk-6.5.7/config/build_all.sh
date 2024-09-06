#!/bin/sh

cd aic8800
./build_plf.sh
if [ $? -eq 0 ]; then
    echo 'aic8800 build  succeed'
else
    echo 'aic8800 build  failed'
    cd ..
    exit 1
fi
cd ..
cd aic8800m40
./build_plf.sh
if [ $? -eq 0 ]; then
    echo 'aic8800m40 build  succeed'
else
    echo 'aic8800m40 build  failed'
    cd ..
    exit 1
fi
cd ..
cd aic8800mc
./build_plf.sh
if [ $? -eq 0 ]; then
    echo 'aic8800mc build  succeed'
else
    echo 'aic8800mc build  failed'
    cd ..
    exit 1
fi
cd ..
