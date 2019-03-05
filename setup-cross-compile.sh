#!/bin/bash

# requirements:
# apt-get install git rsync cmake ia32-libs
# the ia32-libs is not available on Debian, you can use lib32z1 instead

# create rasberrypi folder to cross compile packages
if [ ! -d raspberrypi ];
then
    mkdir raspberrypi

    pushd raspberrypi

    # clone rasberrypi/tools git repo from github
    git clone git://github.com/raspberrypi/tools.git
    popd
fi

# create rootfs folder and copy the entire /lib and /usr directory from rasberrypi
if [ ! -d raspberrypi/rootfs ];
then
    read -p "Pi username: " username
    read -p "Pi address: " address

    pushd raspberrypi
    mkdir rootfs
    rsync -rl --delete-after --safe-links $username@$address:/{lib,usr} $PWD/rootfs
    popd
fi

export PATH=$PATH:$PWD/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin
export TOOLCHAIN_FILE=$PWD/toolchain/pi.cmake
