#!/bin/bash -ex

export CMAKE_PREFIX_PATH=$PWD/3rdparty/install

if [[ "$USE_CROSS_COMPILE" == true ]];
then
    export PATH=$PATH:$HOME/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin
    export TOOLCHAIN_FILE=$HOME/raspberrypi/pi.cmake
fi

function build {
    echo "----- BUILD AND INSTALL = <$1> -----"
    PACKAGE=$(basename $1)

    cmake -DCMAKE_INSTALL_PREFIX=install -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE -H$1 -Bbuild/$PACKAGE
    cmake --build build/$PACKAGE --target install --parallel 8
}

# build dependencies
build 3rdparty/glm
build 3rdparty/glfw
build 3rdparty/imgui
build 3rdparty/raspicam
#build 3rdparty/wiringpi

# build main project
build piHome