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

    // temporary helper function, creates a 1x1x1 cube centered at offset
    std::unique_ptr<genom::GModel> createCubeModel(genom::GDevice &device, glm::vec3 offset) {
        std::vector<genom::GModel::Vertex> vertices{

                // left face (white)
                {{-.5f, -.5f, -.5f},  {.9f, .9f, .9f}},
                {{-.5f, .5f,  .5f},   {.9f, .9f, .9f}},
                {{-.5f, -.5f, .5f},   {.9f, .9f, .9f}},
                {{-.5f, -.5f, -.5f},  {.9f, .9f, .9f}},
                {{-.5f, .5f,  -.5f},  {.9f, .9f, .9f}},
                {{-.5f, .5f,  .5f},   {.9f, .9f, .9f}},

                // right face (yellow)
                {{.5f,  -.5f, -.5f},  {.8f, .8f, .1f}},
                {{.5f,  .5f,  .5f},   {.8f, .8f, .1f}},
                {{.5f,  -.5f, .5f},   {.8f, .8f, .1f}},
                {{.5f,  -.5f, -.5f},  {.8f, .8f, .1f}},
                {{.5f,  .5f,  -.5f},  {.8f, .8f, .1f}},
                {{.5f,  .5f,  .5f},   {.8f, .8f, .1f}},

                // top face (orange, remember y axis points down)
                {{-.5f, -.5f, -.5f},  {.9f, .6f, .1f}},
                {{.5f,  -.5f, .5f},   {.9f, .6f, .1f}},
                {{-.5f, -.5f, .5f},   {.9f, .6f, .1f}},
                {{-.5f, -.5f, -.5f},  {.9f, .6f, .1f}},
                {{.5f,  -.5f, -.5f},  {.9f, .6f, .1f}},
                {{.5f,  -.5f, .5f},   {.9f, .6f, .1f}},

                // bottom face (red)
                {{-.5f, .5f,  -.5f},  {.8f, .1f, .1f}},
                {{.5f,  .5f,  .5f},   {.8f, .1f, .1f}},
                {{-.5f, .5f,  .5f},   {.8f, .1f, .1f}},
                {{-.5f, .5f,  -.5f},  {.8f, .1f, .1f}},
                {{.5f,  .5f,  -.5f},  {.8f, .1f, .1f}},
                {{.5f,  .5f,  .5f},   {.8f, .1f, .1f}},

                // nose face (blue)
                {{-.5f, -.5f, 0.5f},  {.1f, .1f, .8f}},
                {{.5f,  .5f,  0.5f},  {.1f, .1f, .8f}},
                {{-.5f, .5f,  0.5f},  {.1f, .1f, .8f}},
                {{-.5f, -.5f, 0.5f},  {.1f, .1f, .8f}},
                {{.5f,  -.5f, 0.5f},  {.1f, .1f, .8f}},
                {{.5f,  .5f,  0.5f},  {.1f, .1f, .8f}},

                // tail face (green)
                {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
                {{.5f,  .5f,  -0.5f}, {.1f, .8f, .1f}},
                {{-.5f, .5f,  -0.5f}, {.1f, .8f, .1f}},
                {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
                {{.5f,  -.5f, -0.5f}, {.1f, .8f, .1f}},
                {{.5f,  .5f,  -0.5f}, {.1f, .8f, .1f}},

        };
        for (auto &v: vertices) {
            v.position += offset;
        }
        return std::make_unique<genom::GModel>(device, vertices);
    }


    void RenderTest1::loadGameObjects() {
        std::shared_ptr<genom::GModel> gModel = createCubeModel(gDevice, {0.f, 0.f, 0.f});
        auto cube = genom::GGameObject::createGameObject();
        cube.model = gModel;
        cube.transform.translation = {0.f, 0.f, .5f};
        cube.transform.scale = {.5f, .5f, .5f};
        gameObjects.push_back(std::move(cube));
    }
}
