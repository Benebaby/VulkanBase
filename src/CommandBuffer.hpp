#pragma once

#ifndef COMMANDBUFFER_H
    #define COMMANDBUFFER_H
#endif

#include "globalDefs.hpp"
#include "globalIncludes.hpp"
#include "Buffer.hpp"

class Image;

class CommandBuffer{
public:
    CommandBuffer();
    CommandBuffer(vk::CommandBuffer commandBuffer);
    ~CommandBuffer();

    void beginSingleTimeCommand();
    void begin();
    void endSingleTimeCommand();
    void end();
    void copyBufferToImage(Buffer* buffer, Image* image, vk::ImageLayout layout);
    void pipelineBarrier(vk::PipelineStageFlags sourceStage, vk::PipelineStageFlags destinationStage, vk::ImageMemoryBarrier *barrier);

    void beginRenderPass(vk::RenderPassBeginInfo renderPassInfo, vk::SubpassContents subpassContents);
    void bindPipeline(vk::PipelineBindPoint bindPoint, vk::Pipeline pipeline);
    void bindVertexBuffers(std::vector<Buffer*> vertexBuffers, std::vector<vk::DeviceSize> offsets);
    void bindIndexBuffer(Buffer* indexBuffer, vk::IndexType type);
    void bindDescriptorSets(vk::PipelineBindPoint bindPoint,vk::PipelineLayout pipelineLayout,vk::DescriptorSet* descriptorSet);
    void drawIndexed(uint32_t size);
    void endRenderPass();

    vk::CommandBuffer* get();

    void submit();
    void waitIdle();
    void destroy();
    
    static void init(vk::Device &device, vk::CommandPool &commandPool, vk::Queue &graphicsQueue);
    static std::vector<CommandBuffer*> CommandBuffers(uint32_t count);
    static void freeCommandBuffers(std::vector<CommandBuffer*> commandBuffers);

private:
    vk::CommandBuffer m_commandBuffer;

    static vk::Device* device;
    static vk::CommandPool* commandPool; 
    static vk::Queue* graphicsQueue;
};
