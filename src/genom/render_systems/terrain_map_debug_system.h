//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_TERRAIN_MAP_DEBUG_SYSTEM_H
#define NOMAD_TERRAIN_MAP_DEBUG_SYSTEM_H


#include "../g_camera.h"
#include "../g_device.h"
#include "../g_pipeline.h"
#include "../g_model.h"
#include "../g_game_object.h"
#include "../g_frame_info.h"

#include <memory>
#include <vector>

namespace genom {
    class TerrainMapDebugSystem {
    public:

        TerrainMapDebugSystem(GDevice &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);

        ~TerrainMapDebugSystem();

        TerrainMapDebugSystem(const TerrainMapDebugSystem &) = delete;

        TerrainMapDebugSystem &operator=(const TerrainMapDebugSystem &) = delete;

        void update(FrameInfo &frameInfo, GlobalUbo &ubo);

        void render(FrameInfo &frameInfo);

    private:
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        void createPipeline(VkRenderPass renderPass);

        GDevice &gDevice;

        std::unique_ptr<genom::GPipeline> gPipeline;
        VkPipelineLayout pipelineLayout;
    };
}

#endif //NOMAD_TERRAIN_MAP_DEBUG_SYSTEM_H
