//
// Created by Lage Ragnarsson on 16.10.22.
//

#ifndef NOMAD_RENDER_SYSTEM_H
#define NOMAD_RENDER_SYSTEM_H

#include "../g_device.h"
#include "../g_frame_info.h"

namespace genom {
    class RenderSystem {
    public:
        virtual void init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) = 0;
        virtual void update(FrameInfo &frameInfo, GlobalUbo &ubo) = 0;
        virtual void render(FrameInfo &frameInfo) = 0;
    };
}
#endif //NOMAD_RENDER_SYSTEM_H
