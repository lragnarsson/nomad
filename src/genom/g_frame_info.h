//
// Created by Lage Ragnarsson on 10.09.22.
//

#ifndef NOMAD_G_FRAME_INFO_H
#define NOMAD_G_FRAME_INFO_H

#include <vulkan/vulkan.h>
#include "g_camera.h"
#include "g_game_object.h"

namespace genom {
    #define MAX_LIGHTS 10

    struct PointLight {
        glm::vec4 position{};
        glm::vec4 color{};
    };

    struct GlobalUbo {
        glm::mat4 projection{1.f};
        glm::mat4 view{1.f};
        glm::mat4 inverseView{1.f};
        glm::vec4 ambientLightColor{1.f, 1.f, 1.f, .1f};
        PointLight pointLights[MAX_LIGHTS];
        int numLights;
    };

    struct FrameInfo {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        GCamera &camera;
        VkDescriptorSet globalDescriptorSet;
        GGameObject::Map &gameObjects;
    };
}
#endif //NOMAD_G_FRAME_INFO_H
