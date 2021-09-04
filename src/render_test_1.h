//
// Created by Lage Ragnarsson on 04.09.21.
//

#ifndef NOMAD_RENDER_TEST_1_H
#define NOMAD_RENDER_TEST_1_H

#include "genom/g_device.h"
#include "genom/g_window.h"
#include "genom/g_pipeline.h"
#include "genom/g_swap_chain.h"
#include "genom/g_model.h"

#include <memory>
#include <vector>

namespace nomad {
    class RenderTest1 {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        RenderTest1();

        ~RenderTest1();

        RenderTest1(const RenderTest1 &) = delete;

        RenderTest1 &operator=(const RenderTest1 &) = delete;

        void run();

    private:
        void loadModels();

        void createPipelineLayout();

        void createPipeline();

        void createCommandBuffers();

        void drawFrame();

        genom::GWindow gWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
        genom::GDevice gDevice{gWindow};
        genom::GSwapChain gSwapChain{gDevice, gWindow.getExtent()};

        std::unique_ptr<genom::GPipeline> gPipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;

        std::unique_ptr<genom::GModel> gModel;
    };
}

#endif //NOMAD_RENDER_TEST_1_H
