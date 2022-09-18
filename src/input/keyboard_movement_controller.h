//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_KEYBOARD_MOVEMENT_CONTROLLER_H
#define NOMAD_KEYBOARD_MOVEMENT_CONTROLLER_H

#include "../genom/g_game_object.h"
#include "../genom/g_window.h"
#include "settings.h"

namespace input {
    class KeyboardMovementController {
    public:
        struct KeyMappings {
            int moveLeft = GLFW_KEY_A;
            int moveRight = GLFW_KEY_D;
            int moveForward = GLFW_KEY_W;
            int moveBackward = GLFW_KEY_S;
            int moveUp = GLFW_KEY_E;
            int moveDown = GLFW_KEY_Q;
            int lookLeft = GLFW_KEY_LEFT;
            int lookRight = GLFW_KEY_RIGHT;
            int lookUp = GLFW_KEY_UP;
            int lookDown = GLFW_KEY_DOWN;
            int showDebugTerrainMaps = GLFW_KEY_U;
        };

        void handleInput(GLFWwindow *window, float dt, genom::GGameObject &gameObject, Settings &settings);

    private:
        void moveInPlaneXZ(GLFWwindow *window, float dt, genom::GGameObject &gameObject);
        void toggleSettings(GLFWwindow *window, Settings &settings);

        KeyMappings keys{};
        float moveSpeed{25.f};
        float lookSpeed{3.5f};
    };
}

#endif //NOMAD_KEYBOARD_MOVEMENT_CONTROLLER_H
