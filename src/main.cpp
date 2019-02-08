
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

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}
std::atomic<bool> exiting(false);

void sensor_thread_func(const std::vector<Sensor*> sensors)
{
    while(!exiting.load(std::memory_order_relaxed)) {
        for(int i=0; i < sensors.size(); i++) {
            sensors[i]->update();
        }

        usleep(100000); // 10fps
        //delay( 1000 ); /* wait 1 second before next read */
    }
}

int main(int, char**)
{
    printf( "piHome initializing ...\n" );

    // initialize wiringPiSetupGpio
    if ( wiringPiSetupGpio() == -1 ) {
        printf( "[E] wiringPiSetupGpio failed\n" );
        return 1;
    }

    // initialize sensors
    // TODO: move to member
    std::vector<Sensor*> sensors;
    //sensors.push_back(new DHT11Sensor("Raspberry Pi DHT11/DHT22 temperature/humidity", 4, 85));
    //sensors.push_back(new MQ135Sensor("Raspberry Pi MQ-135 Gas sensor", 19));
    sensors.push_back(new PIRSensor("Raspberry Pi PIR Motion decetor sensor", 20));

    printf( "SENSORS: \n" );
    for(int i=0; i < sensors.size(); i++) {
        printf("%s", sensors[i]->name().c_str());
    }

    // start sensors
    std::thread sensor_thread = std::thread{ sensor_thread_func, sensors };

    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        printf( "[E] glfwInit failed\n" );
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "piHome", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Setup ImGui binding
    ImGui_ImplGlfw_Init(window, true);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // imgui
        glfwPollEvents();
        ImGui_ImplGlfw_NewFrame();
        ImGui::Begin("piHome");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Begin("profile");
        if(ImGui::Button("zero")) {
        }
        ImGui::End();

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    exiting.store(true, std::memory_order_relaxed);

    if(sensor_thread.joinable()) {
        sensor_thread.join();
    }

    // Cleanup
    for(int i=0; i < sensors.size(); i++) {
        delete sensors[i];
    }

    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();

    return 0;
}
