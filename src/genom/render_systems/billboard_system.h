//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_BILLBOARD_SYSTEM_H
#define NOMAD_BILLBOARD_SYSTEM_H


#include "../g_camera.h"
#include "../g_device.h"
#include "../g_pipeline.h"
#include "../g_model.h"
#include "../g_game_object.h"
#include "../g_frame_info.h"
#include "render_system.h"

#include <memory>
#include <vector>

namespace genom {
    class BillboardSystem : public RenderSystem {
    public:

        explicit BillboardSystem(GDevice &device);

        ~BillboardSystem();

        BillboardSystem(const BillboardSystem &) = delete;

        BillboardSystem &operator=(const BillboardSystem &) = delete;

        void init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) override;

        void update(FrameInfo &frameInfo, GlobalUbo &ubo) override { }

        void render(FrameInfo &frameInfo) override;

    private:
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        void createPipeline(VkRenderPass renderPass);

        GDevice &gDevice;

        std::unique_ptr<genom::GPipeline> gPipeline;
        VkPipelineLayout pipelineLayout;
    };
}

#endif //NOMAD_BILLBOARD_SYSTEM_H
