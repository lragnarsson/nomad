//
// Created by Lage Ragnarsson on 04.09.21.
//

#include "g_window.h"

namespace genom {
    GWindow::GWindow(int width, int height, std::string windowName) : width{width}, height{height},
                                                                      windowName{windowName} {
        initWindow();
    }

    GWindow::~GWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void GWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, frameBufferResizedCallback);
    }

    void GWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface");
        }
    }

    void GWindow::frameBufferResizedCallback(GLFWwindow *window, int width, int height) {
        auto gWindow = reinterpret_cast<GWindow *>(glfwGetWindowUserPointer(window));
        gWindow->frameBufferResized = true;
        gWindow->width = width;
        gWindow->height = height;
    }
}
