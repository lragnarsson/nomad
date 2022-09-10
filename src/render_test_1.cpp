//
// Created by Lage Ragnarsson on 04.09.21.
//

#include "render_test_1.h"
#include "genom/simple_render_system.h"
#include "genom/g_camera.h"
#include "world/world.h"
#include "genom/g_buffer.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <chrono>

namespace nomad {

    struct GlobalUbo {
        glm::mat4  projectionView{1.f};
        glm::vec3 lightDirection = glm::normalize(glm::vec3{1.f, -3.f, -1.f});
    };

    RenderTest1::RenderTest1() {
        globalPool = genom::GDescriptorPool::Builder(gDevice)
                .setMaxSets(genom::GSwapChain::MAX_FRAMES_IN_FLIGHT)
                .addPoolSize(VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, genom::GSwapChain::MAX_FRAMES_IN_FLIGHT)
                .build();
        loadGameObjects();
    }

    RenderTest1::~RenderTest1() {}

    void RenderTest1::run() {
        std::vector<std::unique_ptr<genom::GBuffer>> uboBuffers(genom::GSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < uboBuffers.size(); i++) {
            uboBuffers[i] = std::make_unique<genom::GBuffer>(
                    gDevice,
                    sizeof(GlobalUbo),
                    1,
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            uboBuffers[i]->map();
        }

        auto globalSetLayout = genom::GDescriptorSetLayout::Builder(gDevice)
                .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT)
                .build();

        std::vector<VkDescriptorSet> globalDescriptorSets(genom::GSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < globalDescriptorSets.size(); i++){
            auto bufferInfo = uboBuffers[i]->descriptorInfo();
            genom::GDescriptorWriter(*globalSetLayout, *globalPool)
                .writeBuffer(0, &bufferInfo)
                .build(globalDescriptorSets[i]);
        }

        genom::SimpleRenderSystem simpleRenderSystem{gDevice,
                                                     gRenderer.getSwapChainRenderPass(),
                                                     globalSetLayout->getDescriptorSetLayout()};

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
                int frameIndex = gRenderer.getFrameIndex();
                genom::FrameInfo frameInfo{
                    frameIndex,
                    frameTime,
                    commandBuffer,
                    camera,
                    globalDescriptorSets[frameIndex]
                };
                // Update
                GlobalUbo ubo{};
                ubo.projectionView = camera.getProjection() * camera.getView();
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();

                // Render
                gRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(frameInfo, gameObjects);
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
