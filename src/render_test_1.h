//
// Created by Lage Ragnarsson on 04.09.21.
//

#ifndef NOMAD_RENDER_TEST_1_H
#define NOMAD_RENDER_TEST_1_H

#include "input/keyboard_movement_controller.h"
#include "genom/g_device.h"
#include "genom/g_window.h"
#include "genom/g_game_object.h"
#include "genom/g_renderer.h"
#include "world/plains_chunk_type.h"

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

        genom::GWindow gWindow{WIDTH, HEIGHT, "Nomad"};
        genom::GDevice gDevice{gWindow};
        genom::GRenderer gRenderer{gWindow, gDevice};

        std::vector<genom::GGameObject> gameObjects;
    };
}

#endif //NOMAD_RENDER_TEST_1_H
