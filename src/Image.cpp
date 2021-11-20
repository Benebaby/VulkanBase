#include "Image.hpp"
#include "CommandBuffer.hpp"

VmaAllocator* Image::allocator;
vk::Device* Image::device;

void Image::init(VmaAllocator &allocator, vk::Device &device)
{
    Image::allocator = &allocator;
    Image::device = &device;
}
Image::Image(vk::Image image, vk::Format format, vk::Extent2D extent2D)
{
    m_format = format;
    m_extent3D = vk::Extent3D{{extent2D.width, extent2D.height}, 1};
    m_image = image;
}
Image::Image(uint32_t width, uint32_t height, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling)
{
    m_format = format;
    m_extent3D = vk::Extent3D{{width, height}, 1};
    create(vk::ImageType::e2D, imageUsage, memoryUsage, format, tiling);
}
void Image::create(vk::ImageType type, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::Format format, vk::ImageTiling tiling)
{
    vk::ImageCreateInfo imageInfo({}, type, format, m_extent3D, 1, 1, vk::SampleCountFlagBits::e1, tiling, imageUsage, vk::SharingMode::eExclusive, {}, {}, vk::ImageLayout::eUndefined);
    VmaAllocationCreateInfo allocInfoImage = {};
    allocInfoImage.usage = memoryUsage;
    if(vmaCreateImage(*allocator, reinterpret_cast<VkImageCreateInfo*>(&imageInfo), &allocInfoImage, reinterpret_cast<VkImage*>(&m_image), &m_allocation, nullptr) != VK_SUCCESS){
        throw std::runtime_error("Failed to create image!");    
    }
}

void Image::createView(vk::ImageAspectFlags aspectFlags)
{
    vk::ImageViewCreateInfo viewInfo({}, m_image, vk::ImageViewType::e2D, m_format, {}, vk::ImageSubresourceRange(aspectFlags, 0, 1, 0, 1));
    try{
        m_view = Image::device->createImageView(viewInfo);
    }catch(std::exception& e) {
        std::cerr << "Exception Thrown: " << e.what();
    }
}
void Image::destroy()
{
    vmaDestroyImage(*allocator, m_image, m_allocation);
}
void Image::destroyView()
{
   Image::device->destroyImageView(m_view);
}

Image::~Image()
{
    destroy();
    destroyView();
}

vk::Extent3D Image::getExtent3D()
{
    return m_extent3D;
}

vk::Image* Image::getImage()
{
    return &m_image;
}

void Image::copyFrom(Buffer* src)
{
    CommandBuffer* commandBuffer = new CommandBuffer();
    commandBuffer->beginSingleTimeCommand();
    commandBuffer->copyBufferToImage(src, this, vk::ImageLayout::eTransferDstOptimal);    
    commandBuffer->endSingleTimeCommand();
}

void Image::transitionLayout(vk::ImageLayout oldLayout, vk::ImageLayout newLayout){
    CommandBuffer* commandBuffer = new CommandBuffer();
    commandBuffer->beginSingleTimeCommand();

    vk::PipelineStageFlags sourceStage;
    vk::PipelineStageFlags destinationStage;
    vk::AccessFlags srcAccessMask = {};
    vk::AccessFlags dstAccessMask = {};

    if (oldLayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eTransferDstOptimal) {
        srcAccessMask = vk::AccessFlagBits::eNoneKHR;
        dstAccessMask = vk::AccessFlagBits::eTransferWrite;
        sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
        destinationStage = vk::PipelineStageFlagBits::eTransfer;
    } else if (oldLayout == vk::ImageLayout::eTransferDstOptimal && newLayout == vk::ImageLayout::eShaderReadOnlyOptimal) {
        srcAccessMask = vk::AccessFlagBits::eTransferWrite;
        dstAccessMask = vk::AccessFlagBits::eShaderRead;
        sourceStage = vk::PipelineStageFlagBits::eTransfer;
        destinationStage = vk::PipelineStageFlagBits::eFragmentShader;
    } else {
        throw std::invalid_argument("Unsupported layout transition!");
    }

    vk::ImageMemoryBarrier barrier(srcAccessMask, dstAccessMask, oldLayout, newLayout, VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, m_image, vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));

    commandBuffer->pipelineBarrier(sourceStage, destinationStage, &barrier);

    commandBuffer->endSingleTimeCommand();
}

vk::ImageView* Image::getView()
{
    return &m_view;
}