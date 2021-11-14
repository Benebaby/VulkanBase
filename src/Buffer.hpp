#pragma once

#include "globalDefs.hpp"
#include "globalIncludes.hpp"

class Buffer
{
private:
    vk::DeviceSize m_size;
    vk::Buffer m_buffer;
    VmaAllocation m_allocation;

    void* m_mappedData = (void*) nullptr;

    static VmaAllocator* allocator;
    static vk::Device* device;
    static vk::CommandPool* commandPool;
    static vk::Queue* queue;

public:
    Buffer(vk::DeviceSize size, vk::BufferUsageFlags bufferUsage, VmaMemoryUsage memoryUsage);
    Buffer(Buffer* src, vk::BufferUsageFlags bufferUsage, VmaMemoryUsage memoryUsage);
    ~Buffer();

    void map();
    void unmap();

    void copyFrom(Buffer* src);
    void copyTo(void* data);

    static void init(VmaAllocator &allocator, vk::Device &device, vk::CommandPool &commandPool, vk::Queue &queue);

    vk::Buffer getHandle();
    vk::DeviceSize getSize();
    VmaAllocation* getAllocation();
    
};