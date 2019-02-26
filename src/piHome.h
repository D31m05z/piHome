#pragma once

#define GLFW_INCLUDE_ES2
#include <imgui.h>
#include <imgui/imgui_glfw.h>
#include <GLFW/glfw3.h>

#include <wiringPi.h>
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
