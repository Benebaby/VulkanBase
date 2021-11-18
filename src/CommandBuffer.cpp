#include "CommandBuffer.hpp"

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

void CommandBuffer::beginSingleTimeCommand()
{
    vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
    try{
        m_commandBuffer.begin(beginInfo);
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