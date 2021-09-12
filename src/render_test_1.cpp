//
// Created by Lage Ragnarsson on 04.09.21.
//

#include "render_test_1.h"
#include "genom/simple_render_system.h"
#include "genom/g_camera.h"
#include "world/plains_chunk_type.h"
#include "world/world.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <chrono>

namespace nomad {

    RenderTest1::RenderTest1() {
        loadGameObjects();
    }

    RenderTest1::~RenderTest1() {}

    void RenderTest1::run() {
        genom::SimpleRenderSystem simpleRenderSystem{gDevice, gRenderer.getSwapChainRenderPass()};
        genom::GCamera camera{};
        camera.setViewTarget(glm::vec3{-1.f, -2.f, 0.f}, glm::vec3{0.f, 0.f, 2.5f});

        auto viewerObject = genom::GGameObject::createGameObject();
        input::KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!gWindow.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;
            //frameTime = glm::min(frameTime, MAX_FRAME_TIME);

            cameraController.moveInPlaneXZ(gWindow.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = gRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 250.f);

            if (auto commandBuffer = gRenderer.beginFrame()) {
                gRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                gRenderer.endSwapChainRenderPass(commandBuffer);
                gRenderer.endFrame();
            }
        }
        vkDeviceWaitIdle(gDevice.device());
    }

    void RenderTest1::loadGameObjects() {
        auto world = world::World();
        world.GetTerrainObjects(0, 0, gDevice, gameObjects);

        std::shared_ptr<genom::GModel> gModel = genom::GModel::createModelFromFile(gDevice,
                                                                                   "/Users/lage/Development/nomad/res/models/flat_vase.obj");
        auto gameObject = genom::GGameObject::createGameObject();
        gameObject.model = gModel;
        gameObject.transform.translation = {0.f, 0.f, 0.f};
        gameObject.transform.scale = glm::vec3{1.f, 1.f, 1.f};
        gameObjects.push_back(std::move(gameObject));
    }
}
