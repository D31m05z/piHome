#!/bin/bash -ex

function build {
    echo "----- BUILD AND INSTALL = <$1> -----"

    cmake -DCMAKE_INSTALL_PREFIX=install -H$1 -Bbuild/$1
    cmake --build build/$1 --target install
}

build glm
build glfw
build imgui
build raspicam

