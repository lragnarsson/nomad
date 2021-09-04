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

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    private:

        void initWindow();

        const int width;
        const int height;

        std::string windowName;
        GLFWwindow *window;
    };
}

#endif //NOMAD_G_WINDOW_H
