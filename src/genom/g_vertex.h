//
// Created by Lage Ragnarsson on 06.09.21.
//

#ifndef NOMAD_G_VERTEX_H
#define NOMAD_G_VERTEX_H

#include <glm/glm.hpp>
#include <vulkan/vulkan_core.h>

#include <iostream>
#include <vector>


namespace genom {
    struct GVertex {
        glm::vec3 position{};
        glm::vec3 color{};
        glm::vec3 normal{};
        glm::vec2 uv{};

        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

        bool operator==(const GVertex &other) const {
            return position == other.position && color == other.color && normal == other.normal &&
                   uv == other.uv;
        }
    };

    std::ostream &operator<<(std::ostream &strm, const GVertex &v);
}
#endif //NOMAD_G_VERTEX_H
