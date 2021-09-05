//
// Created by Lage Ragnarsson on 04.09.21.
//

#include "render_test_1.h"
#include "genom/simple_render_system.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <array>

namespace nomad {

    RenderTest1::RenderTest1() {
        loadGameObjects();
    }

    RenderTest1::~RenderTest1() {}

    void RenderTest1::run() {

        genom::SimpleRenderSystem simpleRenderSystem{gDevice, gRenderer.getSwapChainRenderPass()};
        while (!gWindow.shouldClose()) {
            glfwPollEvents();

            if (auto commandBuffer = gRenderer.beginFrame()) {
                gRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
                gRenderer.endSwapChainRenderPass(commandBuffer);
                gRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(gDevice.device());
    }

    void RenderTest1::loadGameObjects() {
        std::vector<genom::GModel::Vertex> vertices{
                {{0.0f,  -0.5f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f,  0.5f},  {0.0f, 1.0f, 0.0f}},
                {{-0.5f, 0.5f},  {0.0f, 0.0f, 1.0f}}
        };

        auto gModel = std::make_shared<genom::GModel>(gDevice, vertices);
        auto triangle = genom::GGameObject::createGameObject();
        triangle.model = gModel;
        triangle.color = {0.1f, 0.8f, 0.1f};
        triangle.transform2d.translation.x = .2f;
        triangle.transform2d.scale = {2.f, .5f};
        triangle.transform2d.rotation = .25f * glm::two_pi<float>();

        gameObjects.push_back(std::move(triangle));
    }
}
