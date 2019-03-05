#pragma once

#include <imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#if HAVE_WIRING_PI
#include <wiringPi.h>
#endif

#include <thread>
#include <atomic>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>

#include "sensors/dht11.h"
#include "sensors/mq135.h"
#include "sensors/pir.h"
#include "sensors/camera.h"

class PIHome {
public:
    PIHome();
    ~PIHome();

    void update();
    void draw();
    bool isRunning();

private:
    GLFWwindow* window_;
    std::atomic<bool> exiting_;
    std::vector<Sensor*> sensors_;
    std::thread sensor_thread_;
    int warnStep_;
    GLuint textureID_;
};
