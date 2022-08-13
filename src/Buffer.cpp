#include "Buffer.hpp"

VmaAllocator* Buffer::allocator;
vk::Device* Buffer::device;
vk::CommandPool* Buffer::commandPool;
vk::Queue* Buffer::queue;

void Buffer::init(VmaAllocator &allocator, vk::Device &device, vk::CommandPool &commandPool, vk::Queue &queue)
{
    Buffer::allocator = &allocator;
    Buffer::device = &device;
    Buffer::commandPool = &commandPool;
    Buffer::queue = &queue;
}

Buffer::Buffer(vk::DeviceSize size, vk::BufferUsageFlags bufferUsage, VmaMemoryUsage memoryUsage)
{
    m_size = size;
    vk::BufferCreateInfo bufferInfoStaging({}, m_size, bufferUsage);
    VmaAllocationCreateInfo allocInfoStaging = {};
    allocInfoStaging.usage = memoryUsage;
    vmaCreateBuffer(*Buffer::allocator, reinterpret_cast<VkBufferCreateInfo*>(&bufferInfoStaging), &allocInfoStaging, reinterpret_cast<VkBuffer*>(&m_handle), &m_allocation, nullptr);
}

Buffer::Buffer(Buffer* src, vk::BufferUsageFlags bufferUsage, VmaMemoryUsage memoryUsage)
{
    m_size = src->getSize();
    vk::BufferCreateInfo bufferInfoStaging({}, m_size, bufferUsage);
    VmaAllocationCreateInfo allocInfoStaging = {};
    allocInfoStaging.usage = memoryUsage;
    vmaCreateBuffer(*Buffer::allocator, reinterpret_cast<VkBufferCreateInfo*>(&bufferInfoStaging), &allocInfoStaging, reinterpret_cast<VkBuffer*>(&m_handle), &m_allocation, nullptr);
    copyFrom(src);
}

Buffer::~Buffer()
{
    vmaDestroyBuffer(*Buffer::allocator, m_handle, m_allocation);
}

vk::Buffer Buffer::getHandle()
{
    return m_handle;
}

vk::DeviceSize Buffer::getSize()
{
    return m_size;
};

void Buffer::map()
{
   vmaMapMemory(*Buffer::allocator, m_allocation, &m_mappedData);
}
void Buffer::copyTo(void* data)
{
    memcpy(m_mappedData, data, (size_t) m_size);
}
void Buffer::flush()
{
    vmaFlushAllocation(*Buffer::allocator, m_allocation, 0, (size_t) m_size);
}

void Buffer::unmap()
{
    vmaUnmapMemory(*Buffer::allocator, m_allocation);
}

void Buffer::copyFrom(Buffer* src)
{
    vk::CommandBufferAllocateInfo allocInfo(*Buffer::commandPool, vk::CommandBufferLevel::ePrimary, 1);
    vk::CommandBuffer CommandBuffer = Buffer::device->allocateCommandBuffers(allocInfo)[0];
    vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

    CommandBuffer.begin(beginInfo);
    vk::BufferCopy copyRegion(0, 0, src->getSize());
    CommandBuffer.copyBuffer(src->getHandle(), m_handle, 1, &copyRegion);
    CommandBuffer.end();

    vk::SubmitInfo submitInfoCopy({}, {}, CommandBuffer, {});
    Buffer::queue->submit(submitInfoCopy, {});
    Buffer::queue->waitIdle();
    Buffer::device->freeCommandBuffers(*Buffer::commandPool, 1, &CommandBuffer);
}

VmaAllocation* Buffer::getAllocation()
{
    return &m_allocation;
}