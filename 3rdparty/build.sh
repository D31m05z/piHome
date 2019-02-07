#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=install -Hglm -Bbuild/glm
cmake --build build/glm --target install

cmake -DCMAKE_INSTALL_PREFIX=install -DGLFW_USE_EGL=true -DGLFW_CLIENT_LIBRARY="glesv2" -Hglfw -Bbuild/glfw
cmake --build build/glfw --target install

cmake -DCMAKE_INSTALL_PREFIX=install -DGLFW_USE_EGL=true -DGLFW_CLIENT_LIBRARY="glesv2" -Himgui -Bbuild/imgui
cmake --build build/imgui --target install
