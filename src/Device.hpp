#include "globalDefs.hpp"
#include "globalIncludes.hpp"
#include "GPU.hpp"

namespace VBF   
{
    class Device
    {
    private:
        vk::Device m_device;
        vk::Queue m_graphicsQueue;
        vk::Queue m_presentQueue;
    public:
        Device(VBF::Instance* instance, VBF::GPU* gpu);
        ~Device();

        vk::Queue* getGraphicsQueue() { return &m_graphicsQueue; }
        vk::Queue* getPresentQueue() { return &m_presentQueue; }
        vk::Device* getVkDevice() { return &m_device; }
    };
    
    Device::Device(VBF::Instance* instance, VBF::GPU* gpu)
    {
        QueueFamilyIndices indices = gpu->findQueueFamilies();// findQueueFamilies(gpu);
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            vk::DeviceQueueCreateInfo queueCreateInfo({}, queueFamily, 1, &queuePriority);
            queueCreateInfos.push_back(queueCreateInfo);
        }

        vk::PhysicalDeviceFeatures deviceFeatures;
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        //MacOS portability extension
        std::vector<vk::ExtensionProperties> extensionProperties =  gpu->getPhysicalDevice()->enumerateDeviceExtensionProperties();
        for(auto extensionProperty : extensionProperties){
            if(std::string(extensionProperty.extensionName.data()) == std::string(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME))
                deviceExtensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
        }

        vk::DeviceCreateInfo createInfo;
        if (instance->isValidationEnabled()) {
            createInfo = vk::DeviceCreateInfo({}, queueCreateInfos, validationLayers, deviceExtensions, &deviceFeatures);
        }else{
            createInfo = vk::DeviceCreateInfo({}, queueCreateInfos, {}, deviceExtensions, &deviceFeatures);
        }
        try{
            m_device = gpu->getPhysicalDevice()->createDevice(createInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
        m_graphicsQueue = m_device.getQueue(indices.graphicsFamily.value(), 0);
        m_presentQueue = m_device.getQueue(indices.presentFamily.value(), 0);
    }
    
    Device::~Device()
    {
        m_device.destroy();
    }
    
} // namespace VBF
