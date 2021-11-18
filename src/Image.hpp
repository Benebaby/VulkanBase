
#pragma once

#include "globalDefs.hpp"
#include "globalIncludes.hpp"

class Image
{
public:
    static void init(VmaAllocator &allocator, vk::Device &device);
    //2D Texture
    Image(uint32_t width, uint32_t height, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling);
    //3D Texture
    //Image(uint32_t width, uint32_t height, uint32_t depth, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling);
    ~Image();

    void destroy();

private:
    static VmaAllocator* allocator;
    static vk::Device* device;

    vk::Image* m_image;
    vk::Format m_format;
    vk::ImageView* m_view;
    VmaAllocation m_allocation;

    void create(uint32_t width, uint32_t height, uint32_t depth, vk::ImageType type, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling);
    void createView(vk::ImageAspectFlags aspectFlags);
};
