#include "CommandBuffer.hpp"
#include "Image.hpp"

vk::Device* CommandBuffer::device;
vk::CommandPool* CommandBuffer::commandPool; 
vk::Queue* CommandBuffer::graphicsQueue;

void CommandBuffer::init(vk::Device &device, vk::CommandPool &commandPool, vk::Queue &graphicsQueue)
{
    CommandBuffer::device = &device;
    CommandBuffer::commandPool = &commandPool;
    CommandBuffer::graphicsQueue = &graphicsQueue;
}

CommandBuffer::CommandBuffer(){
    vk::CommandBufferAllocateInfo allocInfo(*CommandBuffer::commandPool , vk::CommandBufferLevel::ePrimary, 1);
    try{
        m_commandBuffer = CommandBuffer::device->allocateCommandBuffers(allocInfo)[0];
    }catch(std::exception& e) {
        std::cerr << "Exception Thrown: " << e.what();
    }

}
CommandBuffer::CommandBuffer(vk::CommandBuffer commandBuffer){
    m_commandBuffer = commandBuffer;
}
std::vector<CommandBuffer*> CommandBuffer::CommandBuffers(uint32_t count)
{
    std::vector<vk::CommandBuffer> vkcommandBuffers;
    std::vector<CommandBuffer*> commandBuffers;
    commandBuffers.resize(count);
    vk::CommandBufferAllocateInfo allocInfo(*CommandBuffer::commandPool, vk::CommandBufferLevel::ePrimary, (uint32_t) count);
    try{
        vkcommandBuffers = CommandBuffer::device->allocateCommandBuffers(allocInfo);
    }catch(std::exception& e) {
        std::cerr << "Exception Thrown: " << e.what();
    }
    for (size_t i = 0; i < commandBuffers.size(); i++) {
        commandBuffers[i] = new CommandBuffer(vkcommandBuffers[i]);
    }
    return commandBuffers;
}
void CommandBuffer::freeCommandBuffers(std::vector<CommandBuffer*> commandBuffers)
{
    for (size_t i = 0; i < commandBuffers.size(); i++) {
        commandBuffers[i]->destroy();
    }
}

void CommandBuffer::beginSingleTimeCommand()
{
    vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
    try{
        m_commandBuffer.begin(beginInfo);
    }catch(std::exception& e) {
        std::cerr << "Exception Thrown: " << e.what();
    }
}
void CommandBuffer::begin()
{
    vk::CommandBufferBeginInfo beginInfo;
    try{
        m_commandBuffer.begin(beginInfo);
    }catch(std::exception& e) {
        std::cerr << "Exception Thrown: " << e.what();
    }
}
void CommandBuffer::end()
{
    try{
        m_commandBuffer.end();
    }catch(std::exception& e) {
        std::cerr << "Exception Thrown: " << e.what();
    }
}
void CommandBuffer::endSingleTimeCommand()
{
    try{
        m_commandBuffer.end();
    }catch(std::exception& e) {
        std::cerr << "Exception Thrown: " << e.what();
    }
    submit();
    waitIdle();
    destroy();
}

void CommandBuffer::submit(){
    vk::SubmitInfo submitInfoCopy({}, {}, m_commandBuffer, {});
    CommandBuffer::graphicsQueue->submit(submitInfoCopy, {});
}

void CommandBuffer::waitIdle(){
    CommandBuffer::graphicsQueue->waitIdle();
}

void CommandBuffer::destroy(){
    CommandBuffer::device->freeCommandBuffers(*CommandBuffer::commandPool, 1, &m_commandBuffer);
}

void CommandBuffer::copyBufferToImage(Buffer* buffer,Image* image, vk::ImageLayout layout)
{
    vk::BufferImageCopy region(0, 0, 0, vk::ImageSubresourceLayers( vk::ImageAspectFlagBits::eColor, 0, 0, 1), {0, 0, 0}, image->getExtent3D());
    m_commandBuffer.copyBufferToImage(buffer->getHandle(), *image->getImage(), vk::ImageLayout::eTransferDstOptimal, 1, &region);
}

void CommandBuffer::pipelineBarrier(vk::PipelineStageFlags sourceStage, vk::PipelineStageFlags destinationStage, vk::ImageMemoryBarrier* barrier)
{
    m_commandBuffer.pipelineBarrier(sourceStage, destinationStage, {}, {}, {}, {}, {}, 1, barrier);
}

void CommandBuffer::beginRenderPass(vk::RenderPassBeginInfo renderPassInfo, vk::SubpassContents subpassContents)
{
    m_commandBuffer.beginRenderPass(renderPassInfo, subpassContents);
}
void CommandBuffer::endRenderPass()
{
    m_commandBuffer.endRenderPass();
}
void CommandBuffer::bindPipeline(vk::PipelineBindPoint bindPoint, vk::Pipeline pipeline)
{
    m_commandBuffer.bindPipeline(bindPoint, pipeline);
}

void CommandBuffer::bindVertexBuffers(std::vector<Buffer*> vertexBuffers, std::vector<vk::DeviceSize> offsets)
{
    std::vector<vk::Buffer> vkvertexBuffers;
    vkvertexBuffers.resize(vertexBuffers.size());
    for (size_t i = 0; i < vertexBuffers.size(); i++) {
        vkvertexBuffers[i] = vertexBuffers[i]->getHandle();
    }
    m_commandBuffer.bindVertexBuffers(0, vkvertexBuffers, offsets);
}

void CommandBuffer::bindIndexBuffer(Buffer* indexBuffer, vk::IndexType type)
{
    m_commandBuffer.bindIndexBuffer(indexBuffer->getHandle(), 0, type);
}

void CommandBuffer::bindDescriptorSets(vk::PipelineBindPoint bindPoint,vk::PipelineLayout pipelineLayout,vk::DescriptorSet* descriptorSet)
{
    m_commandBuffer.bindDescriptorSets(bindPoint, pipelineLayout, 0, 1, descriptorSet, 0, nullptr);
}

void CommandBuffer::drawIndexed(uint32_t size)
{
    m_commandBuffer.drawIndexed(size, 1, 0, 0, 0);
}

vk::CommandBuffer* CommandBuffer::get()
{
    return &m_commandBuffer;
}
