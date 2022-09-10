//
// Created by Lage Ragnarsson on 04.09.21.
//

#ifndef NOMAD_G_PIPELINE_H
#define NOMAD_G_PIPELINE_H

#include "g_device.h"

#include <string>
#include <vector>

namespace genom {
    struct PipelineConfigInfo {
        PipelineConfigInfo() = default;

        PipelineConfigInfo(const PipelineConfigInfo &) = delete;

        PipelineConfigInfo &operator=(const PipelineConfigInfo &) = delete;

        std::vector<VkVertexInputBindingDescription> bindingDescriptions{};
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineDynamicStateCreateInfo dynamicStateInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class GPipeline {
    public:
        GPipeline(GDevice &device,
                  const std::string &vertFilePath,
                  const std::string &fragFilePath,
                  const PipelineConfigInfo &pipelineConfigInfo);

        ~GPipeline();

        GPipeline(const GPipeline &) = delete;

        GPipeline &operator=(const GPipeline &) = delete;

        void bind(VkCommandBuffer commandBuffer);

        static void defaultPipelineConfigInfo(PipelineConfigInfo &configInfo);

    private:
        static std::vector<char> readFile(const std::string &filePath);

        void createGraphicsPipeline(const std::string &vertFilePath,
                                    const std::string &fragFilePath,
                                    const PipelineConfigInfo &configInfo);

        void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

        GDevice &gDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };
}

#endif //NOMAD_G_PIPELINE_H