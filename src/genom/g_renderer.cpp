//
// Created by Lage Ragnarsson on 05.09.21.
//

#include "g_renderer.h"

#include <stdexcept>
#include <array>

namespace genom {

    GRenderer::GRenderer(GWindow &window, GDevice &device) : gWindow{window}, gDevice{device} {
        recreateSwapChain();
        createCommandBuffers();
    }

    GRenderer::~GRenderer() { freeCommandBuffers(); }

    void GRenderer::recreateSwapChain() {
        auto extent = gWindow.getExtent();
        while (extent.width == 0 || extent.height == 0) {
            extent = gWindow.getExtent();
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(gDevice.device());

        if (gSwapChain == nullptr) {
            gSwapChain = std::make_unique<genom::GSwapChain>(gDevice, extent);
        } else {
            std::shared_ptr<GSwapChain> oldSwapChain = std::move(gSwapChain);
            gSwapChain = std::make_unique<genom::GSwapChain>(gDevice, extent, oldSwapChain);

            if (!oldSwapChain->compareSwapFormats(*gSwapChain.get())) {
                throw std::runtime_error("swap chain image (or depth) format has changed");
            }
        }
        // TODO: foo
    }

    void GRenderer::createCommandBuffers() {
        commandBuffers.resize(GSwapChain::MAX_FRAMES_IN_FLIGHT);

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = gDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(gDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers");
        }
    }

    void GRenderer::freeCommandBuffers() {
        vkFreeCommandBuffers(
                gDevice.device(),
                gDevice.getCommandPool(),
                static_cast<uint32_t>(commandBuffers.size()),
                commandBuffers.data());
        commandBuffers.clear();
    }

    VkCommandBuffer GRenderer::beginFrame() {
        assert(!isFrameStarted && "Cant' call beginFrame while already in progress ");

        auto result = gSwapChain->acquireNextImage(&currentImageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return nullptr;
        }

        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("fialed to acquire swap chain image");
        }

        isFrameStarted = true;

        auto commandBuffer = getCurrentCommandBuffer();

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer");
        }

        return commandBuffer;
    }

    void GRenderer::endFrame() {
        assert(isFrameStarted && "Can't call endFrame while frame is not in progress");
        auto commandBuffer = getCurrentCommandBuffer();
        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }

        auto result = gSwapChain->submitCommandBuffers(&commandBuffer, &currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
            gWindow.wasWindowResized()) {
            gWindow.resetWindowResizedFlag();
            recreateSwapChain();
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        isFrameStarted = false;
        currentFrameIndex = (currentFrameIndex + 1) % GSwapChain::MAX_FRAMES_IN_FLIGHT;
    }

    void GRenderer::beginSwapChainRenderPass(VkCommandBuffer commandBuffer) {
        assert(isFrameStarted && "Cant' call beginSwapChainRenderPass while not in progress");
        assert(commandBuffer == getCurrentCommandBuffer() &&
               "Cant' call beginSwapChainRenderPass on a different frame");

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = gSwapChain->getRenderPass();
        renderPassInfo.framebuffer = gSwapChain->getFrameBuffer(currentImageIndex);

        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = gSwapChain->getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {0.01f, 0.01f, 0.01f, 1.0f};
        clearValues[1].depthStencil = {1.0f, 0};
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(gSwapChain->getSwapChainExtent().width);
        viewport.height = static_cast<float>(gSwapChain->getSwapChainExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        VkRect2D scissor{{0, 0}, gSwapChain->getSwapChainExtent()};
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    }

    void GRenderer::endSwapChainRenderPass(VkCommandBuffer commandBuffer) {
        assert(isFrameStarted && "Cant' call endSwapChainRenderPass while not in progress");
        assert(commandBuffer == getCurrentCommandBuffer() &&
               "Cant' call endSwapChainRenderPass on a different frame");
        vkCmdEndRenderPass(commandBuffer);
    }
}