
#pragma once

#include "globalDefs.hpp"
#include "globalIncludes.hpp"

#include "Buffer.hpp"

#ifndef IMAGE_H
    #define IMAGE_H
#endif

class CommandBuffer;

class Image
{
public:
    static void init(VmaAllocator &allocator, vk::Device &device);
    //2D Texture
    Image(vk::Image image, vk::Format format, vk::Extent2D extent2D);
    Image(uint32_t width, uint32_t height, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling);
    //3D Texture
    //Image(uint32_t width, uint32_t height, uint32_t depth, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling);
    ~Image();

    void destroy();
    void destroyView();
    void copyFrom(Buffer* src);
    void transitionLayout(vk::ImageLayout oldLayout, vk::ImageLayout newLayout);
    void createView(vk::ImageAspectFlags aspectFlags);

    vk::Extent3D getExtent3D();
    vk::Image* getImage();
    vk::ImageView* getView();

private:
    static VmaAllocator* allocator;
    static vk::Device* device;

    vk::Image m_image;
    vk::Format m_format;
    vk::ImageView m_view;
    VmaAllocation m_allocation;

    vk::Extent3D m_extent3D;

    void create(vk::ImageType type, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling);
};
