//
// Created by Lage Ragnarsson on 10.09.22.
//

#ifndef NOMAD_G_DESCRIPTOR_H
#define NOMAD_G_DESCRIPTOR_H

#include "g_device.h"

// std
#include <memory>
#include <unordered_map>
#include <vector>

namespace genom {

    class GDescriptorSetLayout {
    public:
        class Builder {
        public:
            Builder(GDevice &gDevice) : gDevice{gDevice} {}

            Builder &addBinding(
                    uint32_t binding,
                    VkDescriptorType descriptorType,
                    VkShaderStageFlags stageFlags,
                    uint32_t count = 1);
            std::unique_ptr<GDescriptorSetLayout> build() const;

        private:
            GDevice &gDevice;
            std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
        };

        GDescriptorSetLayout(
                GDevice &gDevice, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
        ~GDescriptorSetLayout();
        GDescriptorSetLayout(const GDescriptorSetLayout &) = delete;
        GDescriptorSetLayout &operator=(const GDescriptorSetLayout &) = delete;

        VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

    private:
        GDevice &gDevice;
        VkDescriptorSetLayout descriptorSetLayout;
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings;

        friend class GDescriptorWriter;
    };

    class GDescriptorPool {
    public:
        class Builder {
        public:
            Builder(GDevice &gDevice) : gDevice{gDevice} {}

            Builder &addPoolSize(VkDescriptorType descriptorType, uint32_t count);
            Builder &setPoolFlags(VkDescriptorPoolCreateFlags flags);
            Builder &setMaxSets(uint32_t count);
            std::unique_ptr<GDescriptorPool> build() const;

        private:
            GDevice &gDevice;
            std::vector<VkDescriptorPoolSize> poolSizes{};
            uint32_t maxSets = 1000;
            VkDescriptorPoolCreateFlags poolFlags = 0;
        };

        GDescriptorPool(
                GDevice &gDevice,
                uint32_t maxSets,
                VkDescriptorPoolCreateFlags poolFlags,
                const std::vector<VkDescriptorPoolSize> &poolSizes);
        ~GDescriptorPool();
        GDescriptorPool(const GDescriptorPool &) = delete;
        GDescriptorPool &operator=(const GDescriptorPool &) = delete;

        bool allocateDescriptor(
                const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet &descriptor) const;

        void freeDescriptors(std::vector<VkDescriptorSet> &descriptors) const;

        void resetPool();

    private:
        GDevice &gDevice;
        VkDescriptorPool descriptorPool;

        friend class GDescriptorWriter;
    };

    class GDescriptorWriter {
    public:
        GDescriptorWriter(GDescriptorSetLayout &setLayout, GDescriptorPool &pool);

        GDescriptorWriter &writeBuffer(uint32_t binding, VkDescriptorBufferInfo *bufferInfo);
        GDescriptorWriter &writeImage(uint32_t binding, VkDescriptorImageInfo *imageInfo);

        bool build(VkDescriptorSet &set);
        void overwrite(VkDescriptorSet &set);

    private:
        GDescriptorSetLayout &setLayout;
        GDescriptorPool &pool;
        std::vector<VkWriteDescriptorSet> writes;
    };

}  // namespace genom

#endif //NOMAD_G_DESCRIPTOR_H
