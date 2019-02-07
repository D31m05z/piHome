
#define GLFW_INCLUDE_ES2
#include <imgui.h>
#include <imgui/imgui_glfw.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    std::vector<int> PINS = { 0, 2, 3, 4 };

    if(PINS.size() < 4) {
        printf("You need to define 4 GPIO pin for softPWM.\n");
        return 1;
    }

    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "S3cur1ty Home", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Setup ImGui binding
    ImGui_ImplGlfw_Init(window, true);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplGlfw_NewFrame();
        ImGui::Begin("P1 S3cur1ty Home");
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
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();

    return 0;
}
