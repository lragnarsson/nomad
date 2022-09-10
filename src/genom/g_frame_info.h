//
// Created by Lage Ragnarsson on 10.09.22.
//

#ifndef NOMAD_G_FRAME_INFO_H
#define NOMAD_G_FRAME_INFO_H

#include <vulkan/vulkan.h>
#include "g_camera.h"

namespace genom {
    struct FrameInfo {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        GCamera &camera;
        VkDescriptorSet globalDescriptorSet;
    };
}
#endif //NOMAD_G_FRAME_INFO_H
