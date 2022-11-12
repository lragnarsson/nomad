//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_POINT_LIGHT_SYSTEM_H
#define NOMAD_POINT_LIGHT_SYSTEM_H


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
    class PointLightSystem : public RenderSystem {
    public:

        explicit PointLightSystem(GDevice &device);

        ~PointLightSystem();

        PointLightSystem(const PointLightSystem &) = delete;

        PointLightSystem &operator=(const PointLightSystem &) = delete;

        void init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) override;

        void update(FrameInfo &frameInfo, GlobalUbo &ubo) override;

        void render(FrameInfo &frameInfo) override;

    private:
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        void createPipeline(VkRenderPass renderPass);

        GDevice &gDevice;

        std::unique_ptr<genom::GPipeline> gPipeline;
        VkPipelineLayout pipelineLayout;
    };
}

#endif //NOMAD_POINT_LIGHT_SYSTEM_H
