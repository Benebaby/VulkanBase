#pragma once

#define TINYGLTF_USE_CPP14

#include "globalDefs.hpp"
#include "globalIncludes.hpp"
#include "SpirvHelper.h"
//#include "Utils.h"

#include <optional>
#include <set>
#include <stb_image.h>
#include <stb_image_write.h>
#include <tiny_gltf.h>
#include <chrono>

#include "Buffer.hpp"
#include "CommandBuffer.hpp"
#include "Image.hpp"
#include "Allocator.hpp"



const uint32_t WIDTH = 1600;
const uint32_t HEIGHT = 900;
const int MAX_FRAMES_IN_FLIGHT = 2;
//const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
//std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
/*
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
*/
struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 texCoord;

    static std::array<vk::VertexInputBindingDescription, 1> getBindingDescription() {
        std::array<vk::VertexInputBindingDescription, 1> bindingDescriptions = {
            vk::VertexInputBindingDescription(0, sizeof(Vertex), vk::VertexInputRate::eVertex)
        };
        return bindingDescriptions;
    }
    static std::array<vk::VertexInputAttributeDescription, 4> getAttributeDescriptions() {
        std::array<vk::VertexInputAttributeDescription, 4> attributeDescriptions{
            vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, pos)),
            vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, color)),
            vk::VertexInputAttributeDescription(2, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, normal)),
            vk::VertexInputAttributeDescription(3, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, texCoord))
        };
        return attributeDescriptions;
    }
};

std::vector<Vertex> vertices = {
     //Position            //Color            //Normal              //UV
    {{-0.5f,  0.5f,  0.5f},{1.0f, 0.0f, 0.0f},{ 0.0f,  0.0f,  1.0f},{0.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f},{0.0f, 1.0f, 0.0f},{ 0.0f,  0.0f,  1.0f},{1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f},{0.0f, 0.0f, 1.0f},{ 0.0f,  0.0f,  1.0f},{1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f},{1.0f, 1.0f, 1.0f},{ 0.0f,  0.0f,  1.0f},{0.0f, 1.0f}},

    {{-0.5f,  0.5f, -0.5f},{1.0f, 0.0f, 0.0f},{-1.0f,  0.0f,  0.0f},{0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f},{0.0f, 1.0f, 0.0f},{-1.0f,  0.0f,  0.0f},{1.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f},{0.0f, 0.0f, 1.0f},{-1.0f,  0.0f,  0.0f},{1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f},{1.0f, 1.0f, 1.0f},{-1.0f,  0.0f,  0.0f},{0.0f, 1.0f}},

    {{ 0.5f,  0.5f,  0.5f},{1.0f, 0.0f, 0.0f},{ 1.0f,  0.0f,  0.0f},{0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f},{0.0f, 1.0f, 0.0f},{ 1.0f,  0.0f,  0.0f},{1.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f},{0.0f, 0.0f, 1.0f},{ 1.0f,  0.0f,  0.0f},{1.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f},{1.0f, 1.0f, 1.0f},{ 1.0f,  0.0f,  0.0f},{0.0f, 1.0f}},

    {{-0.5f,  0.5f, -0.5f},{1.0f, 0.0f, 0.0f},{ 0.0f,  1.0f,  0.0f},{0.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f},{0.0f, 1.0f, 0.0f},{ 0.0f,  1.0f,  0.0f},{1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f},{0.0f, 0.0f, 1.0f},{ 0.0f,  1.0f,  0.0f},{1.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f},{1.0f, 1.0f, 1.0f},{ 0.0f,  1.0f,  0.0f},{0.0f, 1.0f}},

    {{-0.5f, -0.5f,  0.5f},{1.0f, 0.0f, 0.0f},{ 0.0f, -1.0f,  0.0f},{0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f},{0.0f, 1.0f, 0.0f},{ 0.0f, -1.0f,  0.0f},{1.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f},{0.0f, 0.0f, 1.0f},{ 0.0f, -1.0f,  0.0f},{1.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f},{1.0f, 1.0f, 1.0f},{ 0.0f, -1.0f,  0.0f},{0.0f, 1.0f}},

    {{ 0.5f,  0.5f, -0.5f},{1.0f, 0.0f, 0.0f},{ 0.0f,  0.0f, -1.0f},{0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f},{0.0f, 1.0f, 0.0f},{ 0.0f,  0.0f, -1.0f},{1.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f},{0.0f, 0.0f, 1.0f},{ 0.0f,  0.0f, -1.0f},{1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f},{1.0f, 1.0f, 1.0f},{ 0.0f,  0.0f, -1.0f},{0.0f, 1.0f}}
};

std::vector<uint32_t> indices = {
    0 ,	 1 , 2 ,  0 , 2 , 3 ,
    4 ,	 5 , 6 ,  4 , 6 , 7 ,
    8 ,  9 , 10,  8 , 10, 11,
    12,  13, 14,  12, 14, 15,
    16,  17, 18,  16, 18, 19,
    20,  21, 22,  20, 22, 23
};

struct UniformBufferObject {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    glm::vec2 size = glm::vec2((float) WIDTH, (float) HEIGHT);
};

class VulkanBase {
public:
    void run() {
        //initWindow();
        window = new VBF::Window(1600, 900, "Vulkan Base Framework");
        initVulkan();
        mainLoop();
        cleanup();
    }
private:
    //GLFWwindow* window;
    VBF::Window* window;
    //VmaAllocator allocator;
    VBF::Allocator* allocator;
    //vk::Instance instance;
    VBF::Instance* instance;
    bool enableValidation = true;
    //vk::DebugUtilsMessengerEXT debugMessenger;
    //vk::DebugUtilsMessageSeverityFlagsEXT messageSeverityFlags = vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
    //vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;
    //vk::PhysicalDevice physicalDevice;
    VBF::GPU* gpu;
    //vk::Device device;
    //vk::Queue graphicsQueue;
    //vk::Queue presentQueue;
    //vk::SurfaceKHR surface;
    VBF::Device* device;
    VBF::Surface* surface;

    vk::SwapchainKHR swapChain;
    vk::Format swapChainImageFormat;
    vk::Extent2D swapChainExtent;
    //VBF::SwapChain* swapChain;
    std::vector<Image*> swapChainImages;
    std::vector<vk::Framebuffer> swapChainFramebuffers;
    
    vk::RenderPass renderPass;
    vk::PipelineLayout pipelineLayout;
    vk::DescriptorSetLayout descriptorSetLayout;

    vk::ShaderModule vertShaderModule;
    vk::ShaderModule fragShaderModule;
    vk::Pipeline graphicsPipeline;

    vk::CommandPool commandPool; 

    Image* depthImage;

    std::vector<CommandBuffer*> commandBuffers;

    Buffer* vertexBuffer;
    Buffer* indexBuffer;
    std::vector<Buffer*> uniformBuffers;
    
    Image* textureImage;
    vk::Sampler textureSampler;


    vk::DescriptorPool descriptorPool;
    std::vector<vk::DescriptorSet> descriptorSets;

    std::vector<vk::Semaphore> imageAvailableSemaphores;
    std::vector<vk::Semaphore> renderFinishedSemaphores;
    std::vector<vk::Fence> inFlightFences;
    std::vector<vk::Fence> imagesInFlight;
    size_t currentFrame = 0;
    //bool framebufferResized = false;
    /*
    void initWindow(){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanBase", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }
    */
    void initVulkan(){
        //createInstance();
        instance = new VBF::Instance();
        //if(enableValidation)
            //setupDebugMessenger();
        //createSurface();
        surface = new VBF::Surface(instance, window);
        //pickPhysicalDevice();
        gpu = new VBF::GPU(instance, surface);
        //createLogicalDevice();
        device = new VBF::Device(instance, gpu);

        allocator = new VBF::Allocator(instance, gpu, device);

        CommandBuffer::init(*device->getVkDevice(), commandPool, *device->getGraphicsQueue());
        Buffer::init(*allocator, *device->getVkDevice(), commandPool,  *device->getGraphicsQueue());
        Image::init(*allocator, *device->getVkDevice());

        //createAllocator();
        createSwapChain();
        createImageViews();
        //swapChain = new VBF::SwapChain(surface, gpu, device);
        createRenderPass();
        createDescriptorSetLayout();
        readAndCompileShaders();
        createGraphicsPipeline();
        createCommandPool();
        createDepthResources();
        createFramebuffers();
        createTextureImage();
        createTextureSampler();
        createVertexBuffer();
        createIndexBuffer();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommandBuffers();
        createSyncObjects();
    }
    /*
    void createInstance(){
        if (enableValidation && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        vk::ApplicationInfo applicationInfo("VulkanBase", VK_MAKE_VERSION(0, 0 ,1), "VulkanEngine", 1, VK_API_VERSION_1_1);

        try {
            if(enableValidation){
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
                vk::StructureChain<vk::InstanceCreateInfo, vk::DebugUtilsMessengerCreateInfoEXT> instanceCreateInfoChain{
                    vk::InstanceCreateInfo(vk::InstanceCreateFlags(), &applicationInfo, validationLayers, extensions),
                    vk::DebugUtilsMessengerCreateInfoEXT({}, messageSeverityFlags, messageTypeFlags, debugCallback)
                };
                instance = vk::createInstance(instanceCreateInfoChain.get<vk::InstanceCreateInfo>());
            }else{
                vk::InstanceCreateInfo instanceCreateInfo(vk::InstanceCreateFlags(), &applicationInfo, {}, extensions);
                instance = vk::createInstance(instanceCreateInfo);
            }
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }
    
    void setupDebugMessenger() {
        pfnVkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(instance.getVkInstance()->getProcAddr("vkCreateDebugUtilsMessengerEXT"));
        if (!pfnVkCreateDebugUtilsMessengerEXT){
            throw std::runtime_error("GetInstanceProcAddr: Unable to find pfnVkCreateDebugUtilsMessengerEXT function.");
        }
        pfnVkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(instance.getVkInstance()->getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
        if (!pfnVkDestroyDebugUtilsMessengerEXT){
            throw std::runtime_error("GetInstanceProcAddr: Unable to find pfnVkDestroyDebugUtilsMessengerEXT function.");
        }
        vk::DebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo({}, messageSeverityFlags, messageTypeFlags, debugCallback);
        try{
            debugMessenger = instance.getVkInstance()->createDebugUtilsMessengerEXT(debugMessengerCreateInfo, nullptr);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }
    
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
    */
    /*
    void createSurface() {
        if (glfwCreateWindowSurface(instance->getVkInstance(),window->getGLFWwindow(), nullptr, reinterpret_cast<VkSurfaceKHR*>(&surface)) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void pickPhysicalDevice() {
        std::vector<vk::PhysicalDevice> devices = instance->getVkInstance()->enumeratePhysicalDevices();
        bool deviceFound = false;
        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                deviceFound = true;
                gpu = device;
                break;
            }
        }
        if(!deviceFound){
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    bool isDeviceSuitable(vk::PhysicalDevice pDevice) {
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

    QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice pDevice) {
        QueueFamilyIndices indices;
        std::vector<vk::QueueFamilyProperties> queueFamilies = pDevice.getQueueFamilyProperties();
        for (uint32_t i = 0; i < queueFamilies.size(); i++){
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;
            }
            if (pDevice.getSurfaceSupportKHR(i, *surface->getSurfaceKHR())) {
                indices.presentFamily = i;
            }
            if (indices.isComplete()) {
                break;
            }
        }
        return indices;
    }

    bool checkDeviceExtensionSupport(vk::PhysicalDevice pDevice) {
        std::vector<vk::ExtensionProperties> availableExtensions = pDevice.enumerateDeviceExtensionProperties();
        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }
        return requiredExtensions.empty();
    }
    */
   /*
    void createLogicalDevice(){
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
            device = gpu->getPhysicalDevice()->createDevice(createInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
        graphicsQueue = device.getQueue(indices.graphicsFamily.value(), 0);
        presentQueue = device.getQueue(indices.presentFamily.value(), 0);
    }
    */
    /*
    void createAllocator(){
        VmaAllocatorCreateInfo allocatorInfo = {};
        allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_2;
        allocatorInfo.physicalDevice = *gpu->getPhysicalDevice();
        allocatorInfo.device = *device->getVkDevice();
        allocatorInfo.instance = *instance->getVkInstance();
        
        if(vmaCreateAllocator(&allocatorInfo, &allocator) != VK_SUCCESS)
            throw std::runtime_error("failed to create Allocator");
    }
    */
    vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == vk::Format::eB8G8R8A8Srgb && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                return availableFormat;
            }
        }
        return availableFormats[0];
    }

    vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
                return availablePresentMode;
            }
        }
        return vk::PresentModeKHR::eFifo;
    }

    vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities) {
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
    
    
    SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice pDevice) {
        SwapChainSupportDetails details;
        details.capabilities = pDevice.getSurfaceCapabilitiesKHR(*surface->getSurfaceKHR());
        details.formats = pDevice.getSurfaceFormatsKHR(*surface->getSurfaceKHR());
        details.presentModes = pDevice.getSurfacePresentModesKHR(*surface->getSurfaceKHR());
        return details;
    }
    
    void createSwapChain() {
        SwapChainSupportDetails swapChainSupport = gpu->querySwapChainSupport();

        vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        vk::PresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        vk::Extent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

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
            swapChain = device->getVkDevice()->createSwapchainKHR(createInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }

        auto swapChainImagesKHR = device->getVkDevice()->getSwapchainImagesKHR(swapChain);
        swapChainImages.resize(swapChainImagesKHR.size());
        
        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            swapChainImages[i] = new Image(swapChainImagesKHR[i],swapChainImageFormat,swapChainExtent);
        }
    }
    
    void createImageViews(){
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            swapChainImages[i]->createView(vk::ImageAspectFlagBits::eColor);
        }
    }
    
    vk::ShaderModule createShaderModule(const std::vector<uint32_t> code) {
        vk::ShaderModuleCreateInfo createInfo({}, code);
        vk::ShaderModule shaderModule;
        try{
            shaderModule = device->getVkDevice()->createShaderModule(createInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
        return shaderModule;
    }

    void createRenderPass(){
        vk::AttachmentDescription colorAttachment({}, swapChainImageFormat, vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined, vk::ImageLayout::ePresentSrcKHR);
        vk::AttachmentReference colorAttachmentRef(0, vk::ImageLayout::eColorAttachmentOptimal);

        vk::AttachmentDescription depthAttachment({}, findDepthFormat(), vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eDontCare, vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined, vk::ImageLayout::eDepthStencilAttachmentOptimal);
        vk::AttachmentReference depthAttachmentRef(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

        vk::SubpassDescription subpass({}, vk::PipelineBindPoint::eGraphics, {}, colorAttachmentRef, {}, &depthAttachmentRef);
        vk::SubpassDependency dependency(VK_SUBPASS_EXTERNAL, 0, vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests, vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests, vk::AccessFlagBits::eNoneKHR, vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite);

        std::array<vk::AttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};

        vk::RenderPassCreateInfo renderPassInfo({}, attachments, subpass, dependency);
        try{
            renderPass = device->getVkDevice()->createRenderPass(renderPassInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void createDescriptorSetLayout() {
        vk::DescriptorSetLayoutBinding uboLayoutBinding(0, vk::DescriptorType::eUniformBuffer, 1, vk::ShaderStageFlagBits::eVertex, nullptr);
        vk::DescriptorSetLayoutBinding samplerLayoutBinding(1, vk::DescriptorType::eCombinedImageSampler, 1, vk::ShaderStageFlagBits::eFragment, nullptr);

        std::array<vk::DescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
        vk::DescriptorSetLayoutCreateInfo layoutInfo({}, bindings);

        try{
            descriptorSetLayout = device->getVkDevice()->createDescriptorSetLayout(layoutInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void readAndCompileShaders() {
        glslang::InitializeProcess();
        std::vector<uint32_t> vertShaderCodeSPIRV;
        std::vector<uint32_t> fragShaderCodeSPIRV;
        SpirvHelper::GLSLtoSPV(vk::ShaderStageFlagBits::eVertex, "/shader.vert", vertShaderCodeSPIRV);
        SpirvHelper::GLSLtoSPV(vk::ShaderStageFlagBits::eFragment, "/shader.frag", fragShaderCodeSPIRV);
        try{
            vertShaderModule = createShaderModule(vertShaderCodeSPIRV);
            fragShaderModule = createShaderModule(fragShaderCodeSPIRV);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
        glslang::FinalizeProcess();
    }

    void createGraphicsPipeline(){
        vk::PipelineShaderStageCreateInfo vertShaderStageInfo({}, vk::ShaderStageFlagBits::eVertex, vertShaderModule, "main");
        vk::PipelineShaderStageCreateInfo fragShaderStageInfo({}, vk::ShaderStageFlagBits::eFragment, fragShaderModule, "main");

        std::vector<vk::PipelineShaderStageCreateInfo> shaderStages = {vertShaderStageInfo, fragShaderStageInfo};

        auto bindingDescription = Vertex::getBindingDescription();
        auto attributeDescriptions = Vertex::getAttributeDescriptions();

        vk::PipelineVertexInputStateCreateInfo vertexInputInfo({}, bindingDescription, attributeDescriptions);
        vk::PipelineInputAssemblyStateCreateInfo inputAssembly({}, vk::PrimitiveTopology::eTriangleList, VK_FALSE);
        vk::Viewport viewport(0.0f, 0.0f, (float) swapChainExtent.width, (float) swapChainExtent.height, 0.0f, 1.0f);
        vk::Rect2D scissor(vk::Offset2D(0, 0),swapChainExtent);
        vk::PipelineViewportStateCreateInfo viewportState({}, viewport, scissor);
        vk::PipelineRasterizationStateCreateInfo rasterizer({}, VK_FALSE, VK_FALSE, vk::PolygonMode::eFill, vk::CullModeFlagBits::eBack, vk::FrontFace::eCounterClockwise, VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f);
        vk::PipelineMultisampleStateCreateInfo multisampling({}, vk::SampleCountFlagBits::e1, VK_FALSE);

        vk::PipelineDepthStencilStateCreateInfo depthStencil({}, VK_TRUE, VK_TRUE, vk::CompareOp::eLess, VK_FALSE, VK_FALSE);

        vk::PipelineColorBlendAttachmentState colorBlendAttachment(VK_FALSE, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);
        vk::PipelineColorBlendStateCreateInfo colorBlending({},VK_FALSE, vk::LogicOp::eCopy, colorBlendAttachment);
        vk::PipelineLayoutCreateInfo pipelineLayoutInfo({} ,1 , &descriptorSetLayout);

        try{
            pipelineLayout = device->getVkDevice()->createPipelineLayout(pipelineLayoutInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }

        vk::GraphicsPipelineCreateInfo pipelineInfo({}, shaderStages, &vertexInputInfo, &inputAssembly, {}, &viewportState, &rasterizer, &multisampling, &depthStencil, &colorBlending, {}, pipelineLayout, renderPass);
        
        vk::Result result;
        std::tie(result, graphicsPipeline) = device->getVkDevice()->createGraphicsPipeline( nullptr, pipelineInfo);
        switch ( result ){
            case vk::Result::eSuccess: break;
            default: throw std::runtime_error("failed to create graphics Pipeline!");
        }
    }
    
    void createFramebuffers() {
        swapChainFramebuffers.resize(swapChainImages.size());
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            std::array<vk::ImageView, 2> attachments = {
                *swapChainImages[i]->getView(),
                *depthImage->getView()
            };
            vk::FramebufferCreateInfo framebufferInfo({}, renderPass, attachments, swapChainExtent.width, swapChainExtent.height, 1);
            try{
                swapChainFramebuffers[i] = device->getVkDevice()->createFramebuffer(framebufferInfo);
            }catch(std::exception& e) {
                std::cerr << "Exception Thrown: " << e.what();
            }
        }
    }

    void createCommandPool() {
        QueueFamilyIndices queueFamilyIndices = gpu->findQueueFamilies();
        vk::CommandPoolCreateInfo poolInfo({}, queueFamilyIndices.graphicsFamily.value());
        try{
            commandPool = device->getVkDevice()->createCommandPool(poolInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void  createDepthResources(){
        vk::Format depthFormat = findDepthFormat();
        depthImage = new Image( swapChainExtent.width, swapChainExtent.height, vk::ImageUsageFlagBits::eDepthStencilAttachment,VMA_MEMORY_USAGE_GPU_ONLY,depthFormat, vk::ImageTiling::eOptimal);
        depthImage->createView(vk::ImageAspectFlagBits::eDepth);
    }

    vk::Format findSupportedFormat(const std::vector<vk::Format>& candidates, vk::ImageTiling tiling, vk::FormatFeatureFlags features) {
        for (vk::Format format : candidates) {
            vk::FormatProperties props = gpu->getPhysicalDevice()->getFormatProperties(format);

            if (tiling == vk::ImageTiling::eLinear && (props.linearTilingFeatures & features) == features) {
                return format;
            } else if (tiling == vk::ImageTiling::eOptimal && (props.optimalTilingFeatures & features) == features) {
                return format;
            }
        }
        throw std::runtime_error("failed to find supported format!");
    }

    vk::Format findDepthFormat() {
        return findSupportedFormat({vk::Format::eD32Sfloat, vk::Format::eD32SfloatS8Uint, vk::Format::eD24UnormS8Uint}, vk::ImageTiling::eOptimal, vk::FormatFeatureFlagBits::eDepthStencilAttachment);
    }

    void createTextureImage() {
        int texWidth, texHeight, texChannels;
        stbi_uc* pixels = stbi_load(TEXTURE_PATH "/color_checker.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        vk::DeviceSize imageSize = texWidth * texHeight * 4;

        if (!pixels) {
            throw std::runtime_error("failed to load texture image!");
        }

        Buffer stagingBuffer = Buffer(imageSize, vk::BufferUsageFlagBits::eTransferSrc, VMA_MEMORY_USAGE_CPU_ONLY);

        stagingBuffer.map();
        stagingBuffer.copyTo(pixels);
        stagingBuffer.unmap();

        stbi_image_free(pixels);
        
        textureImage = new Image(texWidth, texHeight, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled, VMA_MEMORY_USAGE_GPU_ONLY, vk::Format::eR8G8B8A8Srgb, vk::ImageTiling::eOptimal);
    
        textureImage->transitionLayout(vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal);
        textureImage->copyFrom(&stagingBuffer);
        textureImage->transitionLayout( vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal);

        textureImage->createView(vk::ImageAspectFlagBits::eColor);
    }

    void createTextureSampler() {
        vk::PhysicalDeviceProperties properties = gpu->getPhysicalDevice()->getProperties();

        vk::SamplerCreateInfo samplerInfo(
            {}, 
            vk::Filter::eLinear, 
            vk::Filter::eLinear, 
            vk::SamplerMipmapMode::eLinear, 
            vk::SamplerAddressMode::eRepeat, 
            vk::SamplerAddressMode::eRepeat, 
            vk::SamplerAddressMode::eRepeat,
            0.0f, 
            VK_TRUE, 
            properties.limits.maxSamplerAnisotropy, 
            VK_FALSE,  
            vk::CompareOp::eAlways, 
            0.0f,
            0.0f, 
            vk::BorderColor::eIntOpaqueBlack, 
            VK_FALSE 
        );
        try{
            textureSampler = device->getVkDevice()->createSampler(samplerInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void createVertexBuffer(){
        vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        Buffer stagingBuffer = Buffer(bufferSize, vk::BufferUsageFlagBits::eTransferSrc, VMA_MEMORY_USAGE_CPU_ONLY);
        stagingBuffer.map();
        stagingBuffer.copyTo(vertices.data());
        stagingBuffer.unmap();

        vertexBuffer = new Buffer(&stagingBuffer, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, VMA_MEMORY_USAGE_GPU_ONLY);
    }

    void createIndexBuffer() {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

        Buffer stagingBuffer = Buffer(bufferSize, vk::BufferUsageFlagBits::eTransferSrc, VMA_MEMORY_USAGE_CPU_ONLY);
        stagingBuffer.map();
        stagingBuffer.copyTo(indices.data());
        stagingBuffer.unmap();

        indexBuffer = new Buffer(&stagingBuffer, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer, VMA_MEMORY_USAGE_GPU_ONLY);
    }

    void createUniformBuffers() {
        vk::DeviceSize bufferSize = sizeof(UniformBufferObject);

        uniformBuffers.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            uniformBuffers[i] = new Buffer(bufferSize, vk::BufferUsageFlagBits::eUniformBuffer, VMA_MEMORY_USAGE_CPU_TO_GPU);
        }
    }

    void createDescriptorPool() {
        vk::DescriptorPoolSize poolSizeUbo(vk::DescriptorType::eUniformBuffer, static_cast<uint32_t>(swapChainImages.size()));
        vk::DescriptorPoolSize poolSizeSampler(vk::DescriptorType::eCombinedImageSampler, static_cast<uint32_t>(swapChainImages.size()));
        std::array<vk::DescriptorPoolSize, 2> poolSizes{poolSizeUbo, poolSizeSampler};

        vk::DescriptorPoolCreateInfo poolInfo({}, static_cast<uint32_t>(swapChainImages.size()), poolSizes);
        try{
            descriptorPool = device->getVkDevice()->createDescriptorPool(poolInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void createDescriptorSets() {
        std::vector<vk::DescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
        vk::DescriptorSetAllocateInfo allocInfo(descriptorPool, static_cast<uint32_t>(swapChainImages.size()), layouts.data());
        descriptorSets.resize(swapChainImages.size());
        try{
            descriptorSets = device->getVkDevice()->allocateDescriptorSets(allocInfo);
        }catch(std::exception& e) {
            std::cerr << "Exception Thrown: " << e.what();
        }

        for (size_t i = 0; i < swapChainImages.size(); i++) {

            vk::DescriptorBufferInfo bufferInfo(uniformBuffers[i]->getHandle(), 0, sizeof(UniformBufferObject));
            vk::DescriptorImageInfo imageInfo(textureSampler, *textureImage->getView(), vk::ImageLayout::eShaderReadOnlyOptimal);

            vk::WriteDescriptorSet descriptorWriteUbo(descriptorSets[i], 0, 0, 1, vk::DescriptorType::eUniformBuffer, {}, &bufferInfo);
            vk::WriteDescriptorSet descriptorWriteSampler(descriptorSets[i], 1, 0, 1, vk::DescriptorType::eCombinedImageSampler, &imageInfo);

            std::array<vk::WriteDescriptorSet, 2> descriptorWrites{descriptorWriteUbo, descriptorWriteSampler};
            
            device->getVkDevice()->updateDescriptorSets(descriptorWrites, nullptr);
        }
    }

    void createCommandBuffers(){
        commandBuffers = CommandBuffer::CommandBuffers(static_cast<uint32_t>(swapChainFramebuffers.size()));
        
        for (size_t i = 0; i < commandBuffers.size(); i++) {
            commandBuffers[i]->begin();

            std::array<vk::ClearValue, 2> clearValues{
                vk::ClearValue(vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f})),
                vk::ClearValue(vk::ClearDepthStencilValue(1.0f, 0))
            };
            
            vk::RenderPassBeginInfo renderPassInfo(renderPass, swapChainFramebuffers[i], vk::Rect2D({0, 0}, swapChainExtent), clearValues);

            commandBuffers[i]->beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);
                commandBuffers[i]->bindPipeline(vk::PipelineBindPoint::eGraphics, graphicsPipeline);
                std::vector<Buffer*> vertexBuffers = {vertexBuffer};
                std::vector<vk::DeviceSize> offsets = {0};
                commandBuffers[i]->bindVertexBuffers(vertexBuffers, offsets);
                commandBuffers[i]->bindIndexBuffer(indexBuffer, vk::IndexType::eUint32);
                commandBuffers[i]->bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipelineLayout, &descriptorSets[i]);
                commandBuffers[i]->drawIndexed(static_cast<uint32_t>(indices.size()));
            commandBuffers[i]->endRenderPass();

            commandBuffers[i]->end();
        }
    }

    void createSyncObjects() {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);
        vk::SemaphoreCreateInfo semaphoreInfo;
        vk::FenceCreateInfo fenceInfo(vk::FenceCreateFlagBits::eSignaled);
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            try{
                imageAvailableSemaphores[i] = device->getVkDevice()->createSemaphore(semaphoreInfo);
                renderFinishedSemaphores[i] = device->getVkDevice()->createSemaphore(semaphoreInfo);
                inFlightFences[i] = device->getVkDevice()->createFence(fenceInfo);
            }catch(std::exception& e) {
                std::cerr << "Exception Thrown: " << e.what();
            }
        }
    }

    void updateUniformBuffer(uint32_t currentImage) {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};
        ubo.model = glm::rotate(glm::mat4(1.0f), time * 0.2f * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.view = glm::lookAt(glm::vec3(1.5f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 10.0f);
        ubo.proj[1][1] *= -1;
        ubo.size = glm::vec2((float) swapChainExtent.width, (float) swapChainExtent.height);
        

        uniformBuffers[currentImage]->map();
        uniformBuffers[currentImage]->copyTo(&ubo);
        uniformBuffers[currentImage]->flush();
        uniformBuffers[currentImage]->unmap();
    }

    void drawFrame(){
        int a = 3;
        vk::Result result1 = device->getVkDevice()->waitForFences(inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
        uint32_t imageIndex;
        vk::Result result = device->getVkDevice()->acquireNextImageKHR(swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        if(result == vk::Result::eErrorOutOfDateKHR){
            recreateSwapChain();
            return;
        }else if(result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
            throw std::runtime_error("failed to acquire swap chain image!");
        updateUniformBuffer(imageIndex);

        if ((VkFence) imagesInFlight[imageIndex] != VK_NULL_HANDLE)
            vk::Result result2 = device->getVkDevice()->waitForFences(imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        imagesInFlight[imageIndex] = inFlightFences[currentFrame];

        std::vector<vk::Semaphore> waitSemaphores = {imageAvailableSemaphores[currentFrame]};
        std::vector<vk::PipelineStageFlags> waitStages = {vk::PipelineStageFlagBits::eColorAttachmentOutput};
        std::vector<vk::Semaphore> signalSemaphores = {renderFinishedSemaphores[currentFrame]};
        vk::SubmitInfo submitInfo(waitSemaphores, waitStages, *commandBuffers[imageIndex]->get(), signalSemaphores);
        device->getVkDevice()->resetFences(inFlightFences[currentFrame]);
        device->getPresentQueue()->submit(submitInfo, inFlightFences[currentFrame]);

        std::vector<vk::SwapchainKHR> swapChains = {swapChain};
        vk::PresentInfoKHR presentInfo(signalSemaphores, swapChains, imageIndex);
        //result = device->getPresentQueue()->presentKHR(presentInfo);
        result = static_cast<vk::Result>(vkQueuePresentKHR(*device->getPresentQueue(), reinterpret_cast<const VkPresentInfoKHR *>(&presentInfo)));
        if(result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR || window->wasResized()){
            //framebufferResized = false;
            window->setResized(false);
            recreateSwapChain();
        }else if(result != vk::Result::eSuccess)
            throw std::runtime_error("queue Present failed!");
        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void mainLoop(){
        double time = glfwGetTime();
        uint32_t fps = 0;
        while (!glfwWindowShouldClose(window->getGLFWwindow())) {
            glfwPollEvents();
            drawFrame();
            fps++;
            if((glfwGetTime() - time) >= 1.0){
                time = glfwGetTime();
                std::string title = "VulkanBase  FPS:"+std::to_string(fps);
                glfwSetWindowTitle(window->getGLFWwindow(), title.c_str());
                fps = 0;
            }
        }
        device->getVkDevice()->waitIdle();
    }

    void cleanupSwapchain(){
        delete depthImage;
        for (auto framebuffer : swapChainFramebuffers) {
            device->getVkDevice()->destroyFramebuffer(framebuffer);
        }
        CommandBuffer::freeCommandBuffers(commandBuffers);

        device->getVkDevice()->destroyPipeline(graphicsPipeline);
        device->getVkDevice()->destroyPipelineLayout(pipelineLayout);
        device->getVkDevice()->destroyRenderPass(renderPass);
        
        for (Image* image : swapChainImages) {
            image->destroyView();
        }

        device->getVkDevice()->destroySwapchainKHR(swapChain);
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            delete uniformBuffers[i];
        }
        
        device->getVkDevice()->destroyDescriptorPool(descriptorPool);
    }

    void cleanup(){
        cleanupSwapchain();
        device->getVkDevice()->destroyShaderModule(fragShaderModule);
        device->getVkDevice()->destroyShaderModule(vertShaderModule);
        device->getVkDevice()->destroySampler(textureSampler);
        delete textureImage;
        device->getVkDevice()->destroyDescriptorSetLayout(descriptorSetLayout);
        
        delete indexBuffer;
        delete vertexBuffer;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            device->getVkDevice()->destroySemaphore(imageAvailableSemaphores[i]);
            device->getVkDevice()->destroySemaphore(renderFinishedSemaphores[i]);
            device->getVkDevice()->destroyFence(inFlightFences[i]);
        }
        device->getVkDevice()->destroyCommandPool(commandPool);
        //vmaDestroyAllocator(allocator);
        delete allocator;
        delete device;
        //device.destroy();
        //if (enableValidation) {
           // instance.getVkInstance()->destroyDebugUtilsMessengerEXT(debugMessenger);
        //}
        //instance->getVkInstance().destroySurfaceKHR(surface);
        delete surface;
        //instance.getVkInstance()->destroy();
        delete instance;
        delete window;
        //glfwDestroyWindow(window);
        //glfwTerminate();
    }

    void recreateSwapChain() {
        int width = 0, height = 0;
        glfwGetFramebufferSize(window->getGLFWwindow(), &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(window->getGLFWwindow(), &width, &height);
            glfwWaitEvents();
        }
        device->getVkDevice()->waitIdle();

        cleanupSwapchain();

        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createDepthResources();
        createFramebuffers();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommandBuffers();

        imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);
    }
    /*
    static void framebufferResizeCallback(GLFWwindow *window, int width, int height){
        auto app = reinterpret_cast<VulkanBase *>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }
    */
};

int main() {
    VulkanBase app;
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}