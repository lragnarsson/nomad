//
// Created by Lage Ragnarsson on 04.09.21.
//

#include "render_test_1.h"

#include <stdexcept>

namespace nomad {

    RenderTest1::RenderTest1() {
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    RenderTest1::~RenderTest1() {
        vkDestroyPipelineLayout(gDevice.device(), pipelineLayout, nullptr);
    }

    void RenderTest1::run() {
        while (!gWindow.shouldClose()) {
            glfwPollEvents();
        }
    }

    void RenderTest1::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;
        if (vkCreatePipelineLayout(gDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout");
        }
    }

    void RenderTest1::createPipeline() {
        auto pipelineConfig = genom::GPipeline::defaultPipelineConfigInfo(gSwapChain.width(), gSwapChain.height());
        pipelineConfig.renderPass = gSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        gPipeline = std::make_unique<genom::GPipeline>(gDevice,
                                                       "../cmake-build-debug/shaders/simple_shader.vert.spv",
                                                       "../cmake-build-debug/shaders/simple_shader.frag.spv",
                                                       pipelineConfig);
    }

    void RenderTest1::createCommandBuffers() {

    }

    void RenderTest1::drawFrame() {

    }
}
