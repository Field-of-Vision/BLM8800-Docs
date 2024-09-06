#!/bin/sh

# Get release version of the input lib file
arm-none-eabi-readelf -p LIB_VERSION_STR $1 2> /dev/null | grep git
