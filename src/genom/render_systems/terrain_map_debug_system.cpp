//
// Created by Lage Ragnarsson on 05.09.21.
//

#include "terrain_map_debug_system.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <stdexcept>
#include <array>

namespace genom {

    struct PointLightPushConstants {
        glm::vec4 position{};
        glm::vec4 color{};
        float radius;
    };

    TerrainMapDebugSystem::TerrainMapDebugSystem(GDevice &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) : gDevice{device} {
        createPipelineLayout(globalSetLayout);
        createPipeline(renderPass);
    }

    TerrainMapDebugSystem::~TerrainMapDebugSystem() {
        vkDestroyPipelineLayout(gDevice.device(), pipelineLayout, nullptr);
    }

    void TerrainMapDebugSystem::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
       VkPushConstantRange pushConstantRange;
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(PointLightPushConstants);

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

    void TerrainMapDebugSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        genom::PipelineConfigInfo pipelineConfig{};

        genom::GPipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.attributeDescriptions.clear();
        pipelineConfig.bindingDescriptions.clear();
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        gPipeline = std::make_unique<genom::GPipeline>(gDevice,
                                                       "../cmake-build-debug/shaders/point_light.vert.spv",
                                                       "../cmake-build-debug/shaders/point_light.frag.spv",
                                                       pipelineConfig);
    }

    void TerrainMapDebugSystem::render(FrameInfo &frameInfo) {
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
            if (obj.pointLight == nullptr) continue;

            PointLightPushConstants push{};
            push.position = glm::vec4(obj.transform.translation, 1.f);
            push.color = glm::vec4(obj.color, obj.pointLight->lightIntensity);
            push.radius = obj.transform.scale.x;

            vkCmdPushConstants(
                    frameInfo.commandBuffer,
                    pipelineLayout,
                    VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                    0,
                    sizeof(PointLightPushConstants),
                    &push
                    );
            vkCmdDraw(frameInfo.commandBuffer, 6, 1, 0, 0);
        }
    }
}
