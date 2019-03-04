#!/bin/bash -ex

: ${CMAKE_PREFIX_PATH:="$PWD/3rdparty/install"}
: ${PARALLEL:="8"}

if [[ "$USE_CROSS_COMPILE" == true ]];
then
    [ ! -d raspberrypi ] && echo "Cross compile environment is not prepared. Run the setup-cross-compile.sh script first." && exit 1
    [ ! -d raspberrypi/rootfs ] && echo "Rootfs folder is not exists. \
                                         Run the setup-cross-compile.sh script again \
                                         and fill the correct IP address and username." && exit 1

    export PATH=$PATH:$PWD/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin
    export TOOLCHAIN_FILE=$PWD/toolchain/pi.cmake
fi

function build {
    echo "----- BUILD AND INSTALL = <$1> -----"
    PACKAGE=$(basename $1)

    cmake -DCMAKE_INSTALL_PREFIX=install -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE -H$1 -Bbuild/$PACKAGE
    cmake --build build/$PACKAGE --target install --parallel $PARALLEL
}

# build dependencies
build 3rdparty/glm
build 3rdparty/glfw
build 3rdparty/imgui
build 3rdparty/raspicam
#build 3rdparty/wiringpi

# build main project
build piHome