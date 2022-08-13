#pragma once
#include "globalDefs.hpp"
#include "globalIncludes.hpp"
#include "Surface.hpp"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    vk::SurfaceCapabilitiesKHR capabilities;
    std::vector<vk::SurfaceFormatKHR> formats;
    std::vector<vk::PresentModeKHR> presentModes;
};

namespace VBF
{
    class GPU
    {
    private:
        vk::PhysicalDevice m_physicalDevice;
        VBF::Surface* m_surface;

        bool GPU::checkDeviceExtensionSupport(vk::PhysicalDevice pDevice);
        SwapChainSupportDetails GPU::querySwapChainSupport(vk::PhysicalDevice pDevice);
        bool GPU::isDeviceSuitable(vk::PhysicalDevice pDevice);
        QueueFamilyIndices GPU::findQueueFamilies(vk::PhysicalDevice pDevice);

    public:
        GPU(VBF::Instance* instance, VBF::Surface* surface);
        ~GPU();

        vk::PhysicalDevice* getPhysicalDevice() { return &m_physicalDevice; }
        
        QueueFamilyIndices GPU::findQueueFamilies() { return findQueueFamilies(m_physicalDevice); }
        SwapChainSupportDetails GPU::querySwapChainSupport() { return querySwapChainSupport(m_physicalDevice); }
    };
    
    GPU::GPU(VBF::Instance* instance, VBF::Surface* surface)
    {
        m_surface = surface;
        std::vector<vk::PhysicalDevice> devices = instance->getVkInstance()->enumeratePhysicalDevices();
        bool deviceFound = false;
        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                deviceFound = true;
                m_physicalDevice = device;
                break;
            }
        }
        if(!deviceFound){
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }
    
    GPU::~GPU()
    {
    }

    QueueFamilyIndices GPU::findQueueFamilies(vk::PhysicalDevice pDevice) {
        QueueFamilyIndices indices;
        std::vector<vk::QueueFamilyProperties> queueFamilies = pDevice.getQueueFamilyProperties();
        for (uint32_t i = 0; i < queueFamilies.size(); i++){
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;
            }
            if (pDevice.getSurfaceSupportKHR(i, *m_surface->getSurfaceKHR())) {
                indices.presentFamily = i;
            }
            if (indices.isComplete()) {
                break;
            }
        }
        return indices;
    }
    bool GPU::checkDeviceExtensionSupport(vk::PhysicalDevice pDevice) {
        std::vector<vk::ExtensionProperties> availableExtensions = pDevice.enumerateDeviceExtensionProperties();
        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }
        return requiredExtensions.empty();
    }

    SwapChainSupportDetails GPU::querySwapChainSupport(vk::PhysicalDevice pDevice) {
        SwapChainSupportDetails details;
        details.capabilities = pDevice.getSurfaceCapabilitiesKHR(*m_surface->getSurfaceKHR());
        details.formats = pDevice.getSurfaceFormatsKHR(*m_surface->getSurfaceKHR());
        details.presentModes = pDevice.getSurfacePresentModesKHR(*m_surface->getSurfaceKHR());
        return details;
    }

    bool GPU::isDeviceSuitable(vk::PhysicalDevice pDevice) {
        QueueFamilyIndices indices = findQueueFamilies(pDevice);
        bool extensionsSupported = checkDeviceExtensionSupport(pDevice);
        bool swapChainAdequate = false;
        
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(pDevice);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        vk::PhysicalDeviceFeatures supportedFeatures = pDevice.getFeatures();

        return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    }
    
} // namespace VBF
