//
// Created by Lage Ragnarsson on 04.09.21.
//

#ifndef NOMAD_RENDER_TEST_1_H
#define NOMAD_RENDER_TEST_1_H

#include "input/keyboard_controller.h"
#include "genom/g_device.h"
#include "genom/g_window.h"
#include "genom/g_game_object.h"
#include "genom/g_renderer.h"
#include "genom/g_descriptor.h"
#include "genom/g_swap_chain.h"
#include "genom/render_systems/point_light_system.h"
#include "genom/render_systems/simple_render_system.h"
#include "genom/render_systems/billboard_system.h"

#include <memory>
#include <vector>

namespace nomad {
    class RenderTest1 {
    public:
        static constexpr int WIDTH = 1200;
        static constexpr int HEIGHT = 700;

        RenderTest1();

        ~RenderTest1();

        RenderTest1(const RenderTest1 &) = delete;

        RenderTest1 &operator=(const RenderTest1 &) = delete;

        void run();

    private:
        void loadGameObjects();
        void initRenderer();

        input::Settings settings;

        genom::GWindow gWindow{WIDTH, HEIGHT, "Nomad"};
        genom::GDevice gDevice{gWindow};
        genom::GRenderer gRenderer{gWindow, gDevice};

        // Note: order of declaration matters
        std::unique_ptr<genom::GDescriptorPool> globalPool{};
        genom::GGameObject::Map gameObjects;
        std::vector<VkDescriptorSet> globalDescriptorSets;
        std::vector<std::unique_ptr<genom::GBuffer>> uboBuffers;

        std::vector<std::unique_ptr<genom::RenderSystem>> renderSystems;
    };
}

#endif //NOMAD_RENDER_TEST_1_H
