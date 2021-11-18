#include "Image.hpp"

VmaAllocator* Image::allocator;
vk::Device* Image::device;

void Image::init(VmaAllocator &allocator, vk::Device &device)
{
    Image::allocator = &allocator;
    Image::device = &device;
}

Image::Image(uint32_t width, uint32_t height, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling)
{
    m_format = format;
    create(width, height, 1, vk::ImageType::e2D, imageUsage, memoryUsage, format, tiling);
}
void Image::create(uint32_t width, uint32_t height, uint32_t depth, vk::ImageType type, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling)
{
    vk::ImageCreateInfo imageInfo({}, type, format, vk::Extent3D{{width, height}, depth}, 1, 1, vk::SampleCountFlagBits::e1, tiling, imageUsage, vk::SharingMode::eExclusive, {}, {}, vk::ImageLayout::eUndefined);
    VmaAllocationCreateInfo allocInfoImage = {};
    allocInfoImage.usage = memoryUsage;
    if(vmaCreateImage(*allocator, reinterpret_cast<VkImageCreateInfo*>(&imageInfo), &allocInfoImage, reinterpret_cast<VkImage*>(&m_image), &m_allocation, nullptr) != VK_SUCCESS){
        throw std::runtime_error("Failed to create image!");    
    }
}

void Image::createView(vk::ImageAspectFlags aspectFlags)
{
    vk::ImageViewCreateInfo viewInfo({}, *m_image, vk::ImageViewType::e2D, m_format, {}, vk::ImageSubresourceRange(aspectFlags, 0, 1, 0, 1));
    vk::ImageView imageView;
    try{
        m_view = &Image::device->createImageView(viewInfo);
    }catch(std::exception& e) {
        std::cerr << "Exception Thrown: " << e.what();
    }
}
void Image::destroy()
{
    vmaDestroyImage(*allocator, *m_image, m_allocation);
}

Image::~Image()
{
    destroy();
}