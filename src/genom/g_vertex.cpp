//
// Created by Lage Ragnarsson on 06.09.21.
//

#include "g_vertex.h"

#include <vector>

namespace genom {

    std::vector<VkVertexInputBindingDescription> GVertex::getBindingDescriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(GVertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> GVertex::getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
        attributeDescriptions.push_back({0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GVertex, position)});
        attributeDescriptions.push_back({1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GVertex, color)});
        attributeDescriptions.push_back({2, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GVertex, normal)});
        attributeDescriptions.push_back({3, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(GVertex, uv)});
        return attributeDescriptions;
    }

    std::ostream &operator<<(std::ostream &strm, const GVertex &v) {
        return strm << "GVertex(P=[" << v.position.x << "," << v.position.y << "," << v.position.z << "])";
    }
}