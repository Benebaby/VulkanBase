#pragma once
#include "globalDefs.hpp"
#include "globalIncludes.hpp"
#include "Utils.h"

const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
vk::DebugUtilsMessageSeverityFlagsEXT messageSeverityFlags = vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;
std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

bool checkValidationLayerSupport() {
    std::vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();
    for (const char* layerName : validationLayers) {
        bool layerFound = false;
        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            return false;
        }
    }
    return true;
}

namespace VBF {
    class Instance
    {
    private:
        vk::Instance m_instance;
        vk::DebugUtilsMessengerEXT m_debugMessenger;
        
        bool m_enableValidation = true;
    public:
        Instance();
        ~Instance();

        vk::Instance* getVkInstance() { return &m_instance; }
        bool isValidationEnabled() { return m_enableValidation; }

        void setupDebugMessenger();
        //operator vk::Instance& () { return m_instance; }
    };

    Instance::Instance()
    {
        if (m_enableValidation && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        vk::ApplicationInfo applicationInfo("VulkanBase", VK_MAKE_VERSION(0, 0 ,1), "VulkanEngine", 1, VK_API_VERSION_1_1);

        try {
            if(m_enableValidation){
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
                vk::StructureChain<vk::InstanceCreateInfo, vk::DebugUtilsMessengerCreateInfoEXT> instanceCreateInfoChain{
                    vk::InstanceCreateInfo(vk::InstanceCreateFlags(), &applicationInfo, validationLayers, extensions),
                    vk::DebugUtilsMessengerCreateInfoEXT({}, messageSeverityFlags, messageTypeFlags, debugCallback)
                };
                m_instance = vk::createInstance(instanceCreateInfoChain.get<vk::InstanceCreateInfo>());
            }else{
                vk::InstanceCreateInfo instanceCreateInfo(vk::InstanceCreateFlags(), &applicationInfo, {}, extensions);
                m_instance = vk::createInstance(instanceCreateInfo);
            }
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }

        if (m_enableValidation) {
            setupDebugMessenger();
        }
        
    }

    Instance::~Instance()
    {
        if (m_enableValidation) {
            m_instance.destroyDebugUtilsMessengerEXT(m_debugMessenger);
        }
        m_instance.destroy();
    }

    void Instance::setupDebugMessenger() {
        pfnVkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(m_instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
        if (!pfnVkCreateDebugUtilsMessengerEXT){
            throw std::runtime_error("GetInstanceProcAddr: Unable to find pfnVkCreateDebugUtilsMessengerEXT function.");
        }
        pfnVkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(m_instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
        if (!pfnVkDestroyDebugUtilsMessengerEXT){
            throw std::runtime_error("GetInstanceProcAddr: Unable to find pfnVkDestroyDebugUtilsMessengerEXT function.");
        }
        vk::DebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo({}, messageSeverityFlags, messageTypeFlags, debugCallback);
        try{
            m_debugMessenger = m_instance.createDebugUtilsMessengerEXT(debugMessengerCreateInfo, nullptr);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }
}

