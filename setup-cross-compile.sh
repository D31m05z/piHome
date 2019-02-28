#!/bin/bash

# apt-get install git rsync cmake ia32-libs
# the ia32-libs is not available on Debian, you can use lib32z1 instead

# create rasberrypi folder to cross compile packages
mkdir raspberrypi
pushd raspberrypi

# clone rasberrypi/tools git repo from github
git clone git://github.com/raspberrypi/tools.git

#export PATH=$PATH:$HOME/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin

# create rootfs folder and copy the entire /lib and /usr directory from rasberrypi

mkdir rootfs
rsync -rl --delete-after --safe-links pi@192.168.0.52:/{lib,usr} $PWD/raspberrypi/rootfs

