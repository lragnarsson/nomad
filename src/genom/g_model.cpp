//
// Created by Lage Ragnarsson on 04.09.21.
//

#include "g_model.h"

#include <cassert>
#include <cstring>
#include <vector>


namespace genom {
    GModel::GModel(GDevice &device, const GModel::Builder &builder)
            : gDevice{device} {
        createVertexBuffers(builder.vertices);
        createIndexBuffers(builder.indices);
    }

    GModel::~GModel() {
        vkDestroyBuffer(gDevice.device(), vertexBuffer, nullptr);
        vkFreeMemory(gDevice.device(), vertexBufferMemory, nullptr);

        if (hasIndexBuffer) {
            vkDestroyBuffer(gDevice.device(), indexBuffer, nullptr);
            vkFreeMemory(gDevice.device(), indexBufferMemory, nullptr);
        }
    }


    void GModel::createVertexBuffers(const std::vector<GVertex> &vertices) {
        vertexCount = static_cast<glm::uint32_t>(vertices.size());
        assert(vertexCount >= 3 && "GVertex count must be at least 3");
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;

        // Staging
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        gDevice.createBuffer(
                bufferSize,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                stagingBuffer,
                stagingBufferMemory);
        void *data;
        vkMapMemory(gDevice.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
        vkUnmapMemory(gDevice.device(), stagingBufferMemory);

        // Transfer to device local memory:
        gDevice.createBuffer(
                bufferSize,
                VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                vertexBuffer,
                vertexBufferMemory);

        gDevice.copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

        vkDestroyBuffer(gDevice.device(), stagingBuffer, nullptr);
        vkFreeMemory(gDevice.device(), stagingBufferMemory, nullptr);
    }

    // TODO: Create generic function
    void GModel::createIndexBuffers(const std::vector<uint32_t> &indices) {
        indexCount = static_cast<glm::uint32_t>(indices.size());
        hasIndexBuffer = indexCount > 0;
        if (!hasIndexBuffer) {
            return;
        }

        VkDeviceSize bufferSize = sizeof(indices[0]) * indexCount;
        // Staging
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        gDevice.createBuffer(
                bufferSize,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                stagingBuffer,
                stagingBufferMemory);
        void *data;
        vkMapMemory(gDevice.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), static_cast<size_t>(bufferSize));
        vkUnmapMemory(gDevice.device(), stagingBufferMemory);

        // Transfer to device local memory:
        gDevice.createBuffer(
                bufferSize,
                VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                indexBuffer,
                indexBufferMemory);

        gDevice.copyBuffer(stagingBuffer, indexBuffer, bufferSize);

        vkDestroyBuffer(gDevice.device(), stagingBuffer, nullptr);
        vkFreeMemory(gDevice.device(), stagingBufferMemory, nullptr);
    }

    void GModel::draw(VkCommandBuffer commandBuffer) {
        if (hasIndexBuffer) {
            vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
        } else {
            vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
        }
    }

    void GModel::bind(VkCommandBuffer commandBuffer) {
        VkBuffer buffers[] = {vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

        if (hasIndexBuffer) {
            vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
        }
    }
}

