//
// Created by Lage Ragnarsson on 04.09.21.
//

#ifndef NOMAD_G_MODEL_H
#define NOMAD_G_MODEL_H

#include "g_device.h"
#include "g_vertex.h"
#include "../world/chunk.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace genom {
    class GModel {
    public:
        struct Builder {
            std::vector<GVertex> vertices{};
            std::vector<uint32_t> indices{};

            void loadModel(const std::string &filePath);

            void loadTerrain(const world::Chunk &terrain);
        };

        GModel(GDevice &device, const GModel::Builder &builder);

        ~GModel();

        GModel(const GModel &) = delete;

        GModel &operator=(const GModel &) = delete;

        static std::unique_ptr<GModel> createModelFromFile(GDevice &device, const std::string &filePath);

        static std::unique_ptr<GModel> createModelFromTerrain(GDevice &device, const world::Chunk &terrain);

        void bind(VkCommandBuffer commandBuffer);

        void draw(VkCommandBuffer commandBuffer);

    private:
        void createVertexBuffers(const std::vector<GVertex> &vertices);

        void createIndexBuffers(const std::vector<uint32_t> &indices);

        GDevice &gDevice;

        VkBuffer vertexBuffer{};
        VkDeviceMemory vertexBufferMemory{};
        uint32_t vertexCount{};

        bool hasIndexBuffer = false;
        VkBuffer indexBuffer{};
        VkDeviceMemory indexBufferMemory{};
        uint32_t indexCount{};
    };
}
#endif //NOMAD_G_MODEL_H
