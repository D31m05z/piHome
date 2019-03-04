#!/bin/bash

# requirements:
# apt-get install git rsync cmake ia32-libs
# the ia32-libs is not available on Debian, you can use lib32z1 instead

read -s -p "Pi username: " username
read -s -p "Pi address: " address

# create rasberrypi folder to cross compile packages
[ -d raspberrypi ] || mkdir raspberrypi
pushd raspberrypi

# clone rasberrypi/tools git repo from github
git clone git://github.com/raspberrypi/tools.git

# create rootfs folder and copy the entire /lib and /usr directory from rasberrypi
if [ ! -d rootfs ];
then
    mkdir rootfs
    rsync -rl --delete-after --safe-links $username@$address:/{lib,usr} $PWD/raspberrypi/rootfs
fi

popd    # raspberrypi

export PATH=$PATH:$PWD/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin
