#!/bin/bash

if [[ "$USE_CROSS_COMPILE" == true ]];
then
    export PATH=$PATH:$HOME/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin

    # configure
    cmake -DCMAKE_INSTALL_PREFIX=install -DCMAKE_TOOLCHAIN_FILE=$HOME/raspberrypi/pi.cmake -H. -Bbuild
else
    # configure
    cmake -DCMAKE_INSTALL_PREFIX=install -H. -Bbuild
fi

# build
cmake --build build
