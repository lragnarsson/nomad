//
// Created by Lage Ragnarsson on 05.09.21.
//

#include "billboard_system.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <stdexcept>
#include <array>

namespace genom {

    struct TerrainMapDebugPushConstants {
        glm::vec4 position{};
        glm::vec4 color{};
        alignas(16) glm::vec2 size{};
    };

    BillboardSystem::BillboardSystem(GDevice &device) : gDevice{device} { }

    BillboardSystem::~BillboardSystem() {
        vkDestroyPipelineLayout(gDevice.device(), pipelineLayout, nullptr);
    }

    void BillboardSystem::init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) {
        createPipelineLayout(globalSetLayout);
        createPipeline(renderPass);
    }

    void BillboardSystem::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
       VkPushConstantRange pushConstantRange;
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(TerrainMapDebugPushConstants);

        std::vector<VkDescriptorSetLayout> descriptorSetLayouts{globalSetLayout};

        VkPipelineLayoutCreateInfo
                pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
        pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
        if (vkCreatePipelineLayout(gDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout");
        }
    }

    void BillboardSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        genom::PipelineConfigInfo pipelineConfig{};

        genom::GPipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.attributeDescriptions.clear();
        pipelineConfig.bindingDescriptions.clear();
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        gPipeline = std::make_unique<genom::GPipeline>(gDevice,
                                                       "../cmake-build-debug/shaders/billboard.vert.spv",
                                                       "../cmake-build-debug/shaders/billboard.frag.spv",
                                                       pipelineConfig);
    }

    void BillboardSystem::render(FrameInfo &frameInfo) {
        if (!frameInfo.settings.showDebugTerrainMaps) return;
        gPipeline->bind(frameInfo.commandBuffer);

        vkCmdBindDescriptorSets(
                frameInfo.commandBuffer,
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                pipelineLayout,
                0,
                1,
                &frameInfo.globalDescriptorSet,
                0,
                nullptr);

        for (auto& kv: frameInfo.gameObjects) {
            auto &obj = kv.second;
            if (obj.billboard == nullptr) continue;

            TerrainMapDebugPushConstants push{};
            push.position = glm::vec4(obj.transform.translation, 1.f);
            push.color = glm::vec4(obj.color, 1.f);
            push.size = obj.billboard->size;

            vkCmdPushConstants(
                    frameInfo.commandBuffer,
                    pipelineLayout,
                    VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                    0,
                    sizeof(TerrainMapDebugPushConstants),
                    &push
                    );
            vkCmdDraw(frameInfo.commandBuffer, 6, 1, 0, 0);
        }
    }
}
