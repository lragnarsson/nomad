#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "render_test_1.h"
#include "ai_test_1.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    nomad::RenderTest1 renderTest1{};
    //nomad::AiTest1 aiTest1{};
    try {
        renderTest1.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
