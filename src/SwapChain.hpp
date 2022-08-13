#pragma once
#include "globalDefs.hpp"
#include "globalIncludes.hpp"
#include "Device.hpp"
#include "Surface.hpp"
#include "Image.hpp"

namespace VBF
{
    class SwapChain
    {
    private:
        VBF::Device* m_device;

        vk::SwapchainKHR m_swapChain;
        vk::Format m_swapChainImageFormat;
        vk::Extent2D m_swapChainExtent;

        std::vector<Image*> m_swapChainImages;

        static vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) {
            for (const auto& availableFormat : availableFormats) {
                if (availableFormat.format == vk::Format::eB8G8R8A8Srgb && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                    return availableFormat;
                }
            }
            return availableFormats[0];
        }

        static vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) {
            for (const auto& availablePresentMode : availablePresentModes) {
                if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
                    return availablePresentMode;
                }
            }
            return vk::PresentModeKHR::eFifo;
        }

        static vk::Extent2D SwapChain::chooseSwapExtent(VBF::Window* window, const vk::SurfaceCapabilitiesKHR& capabilities) {
            if (capabilities.currentExtent.width != UINT32_MAX) {
                return capabilities.currentExtent;
            } else {
                int width, height;
                glfwGetFramebufferSize(window->getGLFWwindow(), &width, &height);
                vk::Extent2D actualExtent = {
                    static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)
                };
                actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
                actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
                return actualExtent;
            }
        }
        
    public:
        SwapChain(VBF::Surface* surface, VBF::GPU* gpu, VBF::Device* device);
        ~SwapChain();

        void createImageViews();
        void destroyImageViews();

        void recreate();

        vk::Format getSwapChainImageFormat() { return m_swapChainImageFormat; }
        vk::Extent2D getSwapChainExtent() { return m_swapChainExtent; }
        size_t getSwapChainImageCount() { return m_swapChainImages.size(); }
        Image* getSwapChainImage(size_t index) { return m_swapChainImages[index]; }
        vk::SwapchainKHR* getVkSwapChain() { return &m_swapChain; }
    };

    void SwapChain::recreate(){
        destroyImageViews();
        device->getVkDevice()->destroySwapchainKHR(m_swapChain);
    }
    
    SwapChain::SwapChain(VBF::Surface* surface, VBF::GPU* gpu, VBF::Device* device)
    {
        m_device = device;
        
        SwapChainSupportDetails swapChainSupport = gpu->querySwapChainSupport();

        vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        vk::PresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        vk::Extent2D extent = chooseSwapExtent(surface->getWindow() ,swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        QueueFamilyIndices indices = gpu->findQueueFamilies();
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        
        vk::SwapchainCreateInfoKHR createInfo;
        createInfo.flags = {};
        createInfo.surface = *surface->getSurfaceKHR();
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = vk::SharingMode::eExclusive;
        }
        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;
        try{
            m_swapChain = device->getVkDevice()->createSwapchainKHR(createInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }

        auto swapChainImagesKHR = device->getVkDevice()->getSwapchainImagesKHR(m_swapChain);
        m_swapChainImages.resize(swapChainImagesKHR.size());
        
        m_swapChainImageFormat = surfaceFormat.format;
        m_swapChainExtent = extent;

        for (size_t i = 0; i < m_swapChainImages.size(); i++) {
            m_swapChainImages[i] = new Image(swapChainImagesKHR[i],m_swapChainImageFormat,m_swapChainExtent);
        }
    }

    void SwapChain::createImageViews(){
        for (size_t i = 0; i < m_swapChainImages.size(); i++) {
            m_swapChainImages[i]->createView(vk::ImageAspectFlagBits::eColor);
        }
    }
    
    void SwapChain::destroyImageViews(){
        for (size_t i = 0; i < m_swapChainImages.size(); i++) {
            m_swapChainImages[i]->destroyView();
        }
    }

    SwapChain::~SwapChain()
    {
        for (Image* image : m_swapChainImages) {
            image->destroyView();
            delete image;
        }
        m_device->getVkDevice()->destroySwapchainKHR(m_swapChain);
    }
    
} // namespace VBF
