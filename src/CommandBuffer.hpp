
#pragma once

#include "globalDefs.hpp"
#include "globalIncludes.hpp"

class CommandBuffer{
public:
    CommandBuffer();
    ~CommandBuffer();

    void beginSingleTimeCommand();
    void endSingleTimeCommand();

    void submit();
    void waitIdle();
    void destroy();
    static void init(vk::Device &device, vk::CommandPool &commandPool, vk::Queue &graphicsQueue);
private:
    vk::CommandBuffer m_commandBuffer;

    static vk::Device* device;
    static vk::CommandPool* commandPool; 
    static vk::Queue* graphicsQueue;
};