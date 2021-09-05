//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_G_RENDERER_H
#define NOMAD_G_RENDERER_H

#include "g_device.h"
#include "g_window.h"
#include "g_swap_chain.h"

#include <memory>
#include <vector>
#include <cassert>

namespace genom {
    class GRenderer {
    public:

        GRenderer(GWindow &window, GDevice &device);

        ~GRenderer();

        GRenderer(const GRenderer &) = delete;

        GRenderer &operator=(const GRenderer &) = delete;

        VkRenderPass getSwapChainRenderPass() const { return gSwapChain->getRenderPass(); }

        bool isFrameInProgress() const { return isFrameStarted; }

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
            return commandBuffers[currentImageIndex];

        }

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not in progress");
            return currentFrameIndex;
        }

        VkCommandBuffer beginFrame();

        void endFrame();

        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);

        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);


    private:

        void createCommandBuffers();

        void freeCommandBuffers();

        void recreateSwapChain();

        genom::GWindow &gWindow;
        genom::GDevice &gDevice;

        std::unique_ptr<genom::GSwapChain> gSwapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex;
        bool isFrameStarted = false;
    };
}


#endif //NOMAD_G_RENDERER_H
