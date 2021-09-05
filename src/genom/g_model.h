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

namespace genom {
    class GModel {
    public:
        struct Vertex {
            glm::vec3 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        GModel(GDevice &device, const std::vector<Vertex> &vertices);

        ~GModel();

        GModel(const GModel &) = delete;

        GModel &operator=(const GModel &) = delete;

        void bind(VkCommandBuffer commandBuffer);

        void draw(VkCommandBuffer commandBuffer);

    private:
        void createVertexBuffers(const std::vector<Vertex> &vertices);

        GDevice &gDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
    };
}
#endif //NOMAD_G_MODEL_H
