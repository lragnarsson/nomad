//
// Created by Lage Ragnarsson on 04.09.21.
//

#ifndef NOMAD_G_WINDOW_H
#define NOMAD_G_WINDOW_H

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <string>

namespace genom {
    class GWindow {

    public:
        GWindow(int width, int height, std::string windowName);

        ~GWindow();

        GWindow(const GWindow &) = delete;

        GWindow &operator=(const GWindow &) = delete;


        bool shouldClose() { return glfwWindowShouldClose(window); }

        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

        bool wasWindowResized() { return frameBufferResized; }

        void resetWindowResizedFlag() { frameBufferResized = false; }

        GLFWwindow *getGLFWwindow() const { return window; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    private:
        static void frameBufferResizedCallback(GLFWwindow *window, int width, int height);

        void initWindow();

        int width;
        int height;
        bool frameBufferResized = false;

        std::string windowName;
        GLFWwindow *window;
    };
}

#endif //NOMAD_G_WINDOW_H
