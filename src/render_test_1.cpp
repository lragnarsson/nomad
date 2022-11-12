//
// Created by Lage Ragnarsson on 04.09.21.
//

#include "render_test_1.h"
#include "genom/g_camera.h"
#include "world/world.h"
#include "genom/g_buffer.h"
#include "genom/render_systems/simple_render_system.h"
#include "genom/render_systems/point_light_system.h"
#include "genom/render_systems/billboard_system.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <chrono>

namespace nomad {

    RenderTest1::RenderTest1() {
        globalPool = genom::GDescriptorPool::Builder(gDevice)
                .setMaxSets(genom::GSwapChain::MAX_FRAMES_IN_FLIGHT)
                .addPoolSize(VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, genom::GSwapChain::MAX_FRAMES_IN_FLIGHT)
                .build();
        loadGameObjects();
    }

    RenderTest1::~RenderTest1() {}

    void RenderTest1::run() {
        initRenderer();
        genom::GCamera camera{};
        camera.setViewTarget(glm::vec3{-1.f, -2.f, 0.f}, glm::vec3{0.f, 0.f, 2.5f});

        auto viewerObject = genom::GGameObject::createGameObject();
        input::KeyboardController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!gWindow.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;
            //frameTime = glm::min(frameTime, MAX_FRAME_TIME);

            cameraController.handleInput(gWindow.getGLFWwindow(), frameTime, viewerObject, settings);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = gRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 5000.f);

            if (auto commandBuffer = gRenderer.beginFrame()) {
                int frameIndex = gRenderer.getFrameIndex();
                genom::FrameInfo frameInfo{
                    frameIndex,
                    frameTime,
                    commandBuffer,
                    camera,
                    globalDescriptorSets[frameIndex],
                    gameObjects,
                    settings
                };

                // Update
                genom::GlobalUbo ubo{};
                ubo.projection = camera.getProjection();
                ubo.view = camera.getView();
                ubo.inverseView = camera.getInverseView();

                for (auto &rs : renderSystems) {
                    rs->update(frameInfo, ubo);
                }

                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();

                // Render
                gRenderer.beginSwapChainRenderPass(commandBuffer);

                for (auto &rs : renderSystems) {
                    rs->render(frameInfo);
                }

                gRenderer.endSwapChainRenderPass(commandBuffer);
                gRenderer.endFrame();
            }
        }
        vkDeviceWaitIdle(gDevice.device());
    }

    void RenderTest1::initRenderer() {
        std::vector<std::unique_ptr<genom::GBuffer>> uboBuffers(genom::GSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < uboBuffers.size(); i++) {
            uboBuffers[i] = std::make_unique<genom::GBuffer>(
                    gDevice,
                    sizeof(genom::GlobalUbo),
                    1,
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            uboBuffers[i]->map();
        }

        auto globalSetLayout = genom::GDescriptorSetLayout::Builder(gDevice)
                .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
                .build();

        globalDescriptorSets = std::vector<VkDescriptorSet>(genom::GSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < globalDescriptorSets.size(); i++){
            auto bufferInfo = uboBuffers[i]->descriptorInfo();
            genom::GDescriptorWriter(*globalSetLayout, *globalPool)
                    .writeBuffer(0, &bufferInfo)
                    .build(globalDescriptorSets[i]);
        }

        renderSystems.emplace_back(std::make_unique<genom::SimpleRenderSystem>(gDevice));
        renderSystems.emplace_back(std::make_unique<genom::PointLightSystem>(gDevice));
        renderSystems.emplace_back(std::make_unique<genom::BillboardSystem>(gDevice));

        for (auto &rs : renderSystems) {
            rs->init(gRenderer.getSwapChainRenderPass(),
                     globalSetLayout->getDescriptorSetLayout());
        }
    }

    void RenderTest1::loadGameObjects() {
        auto world = world::World();
        world.GetTerrainObjects(0, 0, gDevice, gameObjects);
        /*world.GetTerrainObjects(0, -world::CHUNK_LENGTH, gDevice, gameObjects);
        world.GetTerrainObjects(-world::CHUNK_WIDTH, 0, gDevice, gameObjects);
        world.GetTerrainObjects(-world::CHUNK_WIDTH, -world::CHUNK_LENGTH, gDevice, gameObjects);*/


        std::shared_ptr<genom::GModel> gModel = genom::GModel::createModelFromFile(gDevice,
                                                                                   "/Users/lage/Development/nomad/res/models/flat_vase.obj");
        auto gameObject = genom::GGameObject::createGameObject();
        gameObject.model = gModel;
        gameObject.transform.translation = {0.f, 0.f, 0.f};
        gameObject.transform.scale = glm::vec3{1.f, 1.f, 1.f};
        gameObjects.emplace(gameObject.getId(), std::move(gameObject));

        auto pointLight = genom::GGameObject::makePointLight(0.5f, 0.5f, glm::vec3{1.0f, .1f, 0.1f}, 0.001f);
        pointLight.transform.translation  = {50.f, -5.f, 40.f};
        gameObjects.emplace(pointLight.getId(), std::move(pointLight));

        auto sun = genom::GGameObject::makePointLight(.9f, 15.f, glm::vec3{.9f, .8f, 0.75f}, 0.f);
        sun.transform.translation  = {1000.f, -700.f, 1000.f};
        gameObjects.emplace(sun.getId(), std::move(sun));

    }
}
