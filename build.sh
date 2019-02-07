#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=install -H. -Bbuild
cmake --build build
