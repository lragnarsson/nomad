//
// Created by Lage Ragnarsson on 04.09.21.
//

#ifndef NOMAD_G_MODEL_H
#define NOMAD_G_MODEL_H

#include "g_device.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace genom {
    class GModel {
    public:
        struct Vertex {
            glm::vec3 position{};
            glm::vec3 color{};
            glm::vec3 normal{};
            glm::vec2 uv{};

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

            bool operator==(const Vertex &other) const {
                return position == other.position && color == other.color && normal == other.normal &&
                       uv == other.uv;
            }
        };

        struct Builder {
            std::vector<Vertex> vertices{};
            std::vector<uint32_t> indices{};

            void loadModel(const std::string &filePath);
        };

        GModel(GDevice &device, const GModel::Builder &builder);

        ~GModel();

        GModel(const GModel &) = delete;

        GModel &operator=(const GModel &) = delete;

        static std::unique_ptr<GModel> createModelFromFile(GDevice &device, const std::string &filePath);

        void bind(VkCommandBuffer commandBuffer);

        void draw(VkCommandBuffer commandBuffer);

    private:
        void createVertexBuffers(const std::vector<Vertex> &vertices);

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
