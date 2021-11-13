#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#define VK_ENABLE_BETA_EXTENSIONS
#define TINYGLTF_USE_CPP14
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define VMA_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <optional>
#include <set>
#include <vk_mem_alloc.h>
#include <tiny_gltf.h>
#include <vulkan/vulkan.hpp>
#include <array>
#include <chrono>

#include "SpirvHelper.h"
#include "Utils.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
const int MAX_FRAMES_IN_FLIGHT = 2;
const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

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

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;
    static std::vector<vk::VertexInputBindingDescription> getBindingDescription() {
        std::vector<vk::VertexInputBindingDescription> bindingDescriptions = {
            vk::VertexInputBindingDescription(0, sizeof(Vertex), vk::VertexInputRate::eVertex)
        };
        return bindingDescriptions;
    }
    static std::vector<vk::VertexInputAttributeDescription> getAttributeDescriptions() {
        std::vector<vk::VertexInputAttributeDescription> attributeDescriptions{
            vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, pos)),
            vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, color))
        };
        return attributeDescriptions;
    }
};

const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};

const std::vector<uint32_t> indices = {
    0, 1, 2, 2, 3, 0
};

struct UniformBufferObject {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
};

class VulkanBase {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }
private:
    GLFWwindow* window;
    VmaAllocator allocator;
    vk::Instance instance;
    bool enableValidation = false;
    vk::DebugUtilsMessengerEXT debugMessenger;
    vk::DebugUtilsMessageSeverityFlagsEXT messageSeverityFlags = vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
    vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;
    vk::PhysicalDevice physicalDevice;
    vk::Device device;
    vk::Queue graphicsQueue;
    vk::Queue presentQueue;
    vk::SurfaceKHR surface;

    vk::SwapchainKHR swapChain;
    vk::Format swapChainImageFormat;
    vk::Extent2D swapChainExtent;
    std::vector<vk::Image> swapChainImages;
    std::vector<vk::ImageView> swapChainImageViews;
    std::vector<vk::Framebuffer> swapChainFramebuffers;
    
    vk::RenderPass renderPass;
    vk::PipelineLayout pipelineLayout;
    vk::DescriptorSetLayout descriptorSetLayout;
    vk::Pipeline graphicsPipeline;

    vk::CommandPool commandPool; 
    std::vector<vk::CommandBuffer> commandBuffers;
    vk::Buffer vertexBuffer;
    VmaAllocation vertexBufferAllocation;
    vk::Buffer indexBuffer;
    VmaAllocation indexBufferAllocation;
    std::vector<vk::Buffer> uniformBuffers;
    std::vector<VmaAllocation> uniformBufferAllocations;

    vk::DescriptorPool descriptorPool;
    std::vector<vk::DescriptorSet> descriptorSets;

    std::vector<vk::Semaphore> imageAvailableSemaphores;
    std::vector<vk::Semaphore> renderFinishedSemaphores;
    std::vector<vk::Fence> inFlightFences;
    std::vector<vk::Fence> imagesInFlight;
    size_t currentFrame = 0;
    bool framebufferResized = false;

    void initWindow(){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanBase", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    void initVulkan(){
        createInstance();
        if(enableValidation)
            setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createAllocator();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createDescriptorSetLayout();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createVertexBuffer();
        createIndexBuffer();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommandBuffers();
        createSyncObjects();
    }

    void createInstance(){
        if (enableValidation && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        vk::ApplicationInfo applicationInfo("VulkanBase", VK_MAKE_VERSION(0, 0 ,1), "VulkanEngine", 1, VK_API_VERSION_1_1);

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
    }

    void setupDebugMessenger() {
        pfnVkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
        if (!pfnVkCreateDebugUtilsMessengerEXT){
            throw std::runtime_error("GetInstanceProcAddr: Unable to find pfnVkCreateDebugUtilsMessengerEXT function.");
        }
        pfnVkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
        if (!pfnVkDestroyDebugUtilsMessengerEXT){
            throw std::runtime_error("GetInstanceProcAddr: Unable to find pfnVkDestroyDebugUtilsMessengerEXT function.");
        }
        vk::DebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo({}, messageSeverityFlags, messageTypeFlags, debugCallback);
        debugMessenger = instance.createDebugUtilsMessengerEXT(debugMessengerCreateInfo, nullptr);
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

    void createSurface() {
        VkSurfaceKHR surfaceKHR;
        if (glfwCreateWindowSurface(instance, window, nullptr, &surfaceKHR) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }else{
            surface = vk::SurfaceKHR(surfaceKHR);
        }
    }

    void pickPhysicalDevice() {
        std::vector<vk::PhysicalDevice> devices = instance.enumeratePhysicalDevices();
        bool deviceFound = false;
        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                deviceFound = true;
                physicalDevice = device;
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
        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice pDevice) {
        QueueFamilyIndices indices;
        std::vector<vk::QueueFamilyProperties> queueFamilies = pDevice.getQueueFamilyProperties();
        for (uint32_t i = 0; i < queueFamilies.size(); i++){
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;
            }
            if (pDevice.getSurfaceSupportKHR(i, surface)) {
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

    void createLogicalDevice(){
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            vk::DeviceQueueCreateInfo queueCreateInfo({}, queueFamily, 1, &queuePriority);
            queueCreateInfos.push_back(queueCreateInfo);
        }

        vk::PhysicalDeviceFeatures deviceFeatures;

        //MacOS portability extension
        std::vector<vk::ExtensionProperties> extensionProperties =  physicalDevice.enumerateDeviceExtensionProperties();
        for(auto extensionProperty : extensionProperties){
            if(std::string(extensionProperty.extensionName.data()) == std::string(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME))
                deviceExtensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
        }

        vk::DeviceCreateInfo createInfo;
        if (enableValidation) {
            createInfo = vk::DeviceCreateInfo({}, queueCreateInfos, validationLayers, deviceExtensions, &deviceFeatures);
        }else{
            createInfo = vk::DeviceCreateInfo({}, queueCreateInfos, {}, deviceExtensions, &deviceFeatures);
        }
        device = physicalDevice.createDevice(createInfo);
        graphicsQueue = device.getQueue(indices.graphicsFamily.value(), 0);
        presentQueue = device.getQueue(indices.presentFamily.value(), 0);
    }

    void createAllocator(){
        VmaAllocatorCreateInfo allocatorInfo = {};
        allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_2;
        allocatorInfo.physicalDevice = physicalDevice;
        allocatorInfo.device = device;
        allocatorInfo.instance = instance;
        
        vmaCreateAllocator(&allocatorInfo, &allocator);
    }

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
        return vk::PresentModeKHR::eImmediate;
    }

    vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != UINT32_MAX) {
            return capabilities.currentExtent;
        } else {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
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
        details.capabilities = pDevice.getSurfaceCapabilitiesKHR(surface);
        details.formats = pDevice.getSurfaceFormatsKHR(surface);
        details.presentModes = pDevice.getSurfacePresentModesKHR(surface);
        return details;
    }

    void createSwapChain() {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

        vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        vk::PresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        vk::Extent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        
        vk::SwapchainCreateInfoKHR createInfo;
        createInfo.flags = {};
        createInfo.surface = surface;
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

        swapChain = device.createSwapchainKHR(createInfo);
        swapChainImages = device.getSwapchainImagesKHR(swapChain);
        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }

    void createImageViews(){ 
        swapChainImageViews.resize(swapChainImages.size());
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            vk::ImageViewCreateInfo imageViewCreateInfo({}, swapChainImages[i], vk::ImageViewType::e2D, swapChainImageFormat, vk::ComponentMapping(), vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
            swapChainImageViews[i] = device.createImageView(imageViewCreateInfo);
        }
    }

    vk::ShaderModule createShaderModule(const std::vector<uint32_t> code) {
        vk::ShaderModuleCreateInfo createInfo({}, code);
        vk::ShaderModule shaderModule = device.createShaderModule(createInfo);
        return shaderModule;
    }

    void createRenderPass(){
        vk::AttachmentDescription colorAttachment({}, swapChainImageFormat, vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined, vk::ImageLayout::ePresentSrcKHR);
        vk::AttachmentReference colorAttachmentRef({}, vk::ImageLayout::eColorAttachmentOptimal);
        vk::SubpassDescription subpass({}, vk::PipelineBindPoint::eGraphics, {}, colorAttachmentRef);
        vk::RenderPassCreateInfo renderPassInfo({}, colorAttachment, subpass);
        renderPass = device.createRenderPass(renderPassInfo);
    }

    void createDescriptorSetLayout() {
        vk::DescriptorSetLayoutBinding uboLayoutBinding(0, vk::DescriptorType::eUniformBuffer, 1, vk::ShaderStageFlagBits::eVertex, nullptr);
        vk::DescriptorSetLayoutCreateInfo layoutInfo({}, 1, &uboLayoutBinding);
        try{
        descriptorSetLayout = device.createDescriptorSetLayout(layoutInfo);
        } catch(std::exception const &e){

        }
    }

    void createGraphicsPipeline(){
        glslang::InitializeProcess();
        std::vector<uint32_t> vertShaderCodeSPIRV;
        std::vector<uint32_t> fragShaderCodeSPIRV;
        SpirvHelper::GLSLtoSPV(vk::ShaderStageFlagBits::eVertex, "/shader.vert", vertShaderCodeSPIRV);
        SpirvHelper::GLSLtoSPV(vk::ShaderStageFlagBits::eFragment, "/shader.frag", fragShaderCodeSPIRV);
        vk::ShaderModule vertShaderModule = createShaderModule(vertShaderCodeSPIRV);
        vk::ShaderModule fragShaderModule = createShaderModule(fragShaderCodeSPIRV);
        glslang::FinalizeProcess();

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
        vk::PipelineColorBlendAttachmentState colorBlendAttachment(VK_FALSE, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);
        vk::PipelineColorBlendStateCreateInfo colorBlending({},VK_FALSE, vk::LogicOp::eCopy, colorBlendAttachment);
        vk::PipelineLayoutCreateInfo pipelineLayoutInfo({} ,1 , &descriptorSetLayout);

        try{
        pipelineLayout = device.createPipelineLayout(pipelineLayoutInfo);
        } catch(std::exception const &e){

        }

        vk::GraphicsPipelineCreateInfo pipelineInfo({}, shaderStages, &vertexInputInfo, &inputAssembly, {}, &viewportState, &rasterizer, &multisampling, {}, &colorBlending, {}, pipelineLayout, renderPass);
        
        vk::Result result;
        std::tie(result, graphicsPipeline) = device.createGraphicsPipeline( nullptr, pipelineInfo);
        switch ( result ){
            case vk::Result::eSuccess: break;
            default: throw std::runtime_error("failed to create graphics Pipeline!");
        }

        device.destroyShaderModule(fragShaderModule);
        device.destroyShaderModule(vertShaderModule);
    }
    
    void createFramebuffers() {
        swapChainFramebuffers.resize(swapChainImageViews.size());
        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            std::vector<vk::ImageView> attachments = {swapChainImageViews[i]};
            vk::FramebufferCreateInfo framebufferInfo({}, renderPass, attachments, swapChainExtent.width, swapChainExtent.height, 1);
            swapChainFramebuffers[i] = device.createFramebuffer(framebufferInfo);
        }
    }

    void createCommandPool() {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);
        vk::CommandPoolCreateInfo poolInfo({}, queueFamilyIndices.graphicsFamily.value());
        commandPool = device.createCommandPool(poolInfo);
    }

    void createBuffer(vk::Buffer& buffer, VmaAllocation& allocation, vk::DeviceSize size, vk::BufferUsageFlags bufferUsage, VmaMemoryUsage memoryUsage){
        vk::BufferCreateInfo bufferInfoStaging({}, size, bufferUsage);
        VmaAllocationCreateInfo allocInfoStaging = {};
        allocInfoStaging.usage = memoryUsage;
        vmaCreateBuffer(allocator, reinterpret_cast<VkBufferCreateInfo*>(&bufferInfoStaging), &allocInfoStaging, reinterpret_cast<VkBuffer*>(&buffer), &allocation, nullptr);
    }

    void copyBuffer(vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size) {
        //transfer staging buffer data into vertexbuffer
        vk::CommandBufferAllocateInfo allocInfo(commandPool, vk::CommandBufferLevel::ePrimary, 1);
        vk::CommandBuffer CommandBuffer = device.allocateCommandBuffers(allocInfo)[0];
        vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

        CommandBuffer.begin(beginInfo);
            vk::BufferCopy copyRegion(0, 0, size);
            CommandBuffer.copyBuffer(srcBuffer, dstBuffer, 1, &copyRegion);
        CommandBuffer.end();

        //submit transfer command buffer
        vk::SubmitInfo submitInfoCopy({}, {}, CommandBuffer, {});
        graphicsQueue.submit(submitInfoCopy, {});
        graphicsQueue.waitIdle();
        device.freeCommandBuffers(commandPool, 1, &CommandBuffer);
    }

    void createVertexBuffer(){
        vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        //temporary staging buffer
        vk::Buffer stagingBuffer;
        VmaAllocation stagingBufferAllocation;
        createBuffer(stagingBuffer, stagingBufferAllocation, bufferSize, vk::BufferUsageFlagBits::eTransferSrc, VMA_MEMORY_USAGE_CPU_ONLY);
        
        void* mappedData;
        vmaMapMemory(allocator, stagingBufferAllocation, &mappedData);
            memcpy(mappedData, vertices.data(), (size_t) bufferSize);
        vmaUnmapMemory(allocator, stagingBufferAllocation);

        //vertexbuffer
        createBuffer(vertexBuffer, vertexBufferAllocation, bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, VMA_MEMORY_USAGE_GPU_ONLY);
        
        //copy staging buffer data to vertexbuffer
        copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

        //destroy staging resources
        vmaDestroyBuffer(allocator, stagingBuffer, stagingBufferAllocation);
    }

    void createIndexBuffer() {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

        //temporary staging buffer
        vk::Buffer stagingBuffer;
        VmaAllocation stagingBufferAllocation;
        createBuffer(stagingBuffer, stagingBufferAllocation, bufferSize, vk::BufferUsageFlagBits::eTransferSrc, VMA_MEMORY_USAGE_CPU_ONLY);

        void* mappedData;
        vmaMapMemory(allocator, stagingBufferAllocation, &mappedData);
            memcpy(mappedData, indices.data(), (size_t) bufferSize);
        vmaUnmapMemory(allocator, stagingBufferAllocation);

        //vertexbuffer
        createBuffer(indexBuffer, indexBufferAllocation, bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer, VMA_MEMORY_USAGE_GPU_ONLY);

        copyBuffer(stagingBuffer, indexBuffer, bufferSize);

        vmaDestroyBuffer(allocator, stagingBuffer, stagingBufferAllocation);
    }

    void createUniformBuffers() {
        vk::DeviceSize bufferSize = sizeof(UniformBufferObject);

        uniformBuffers.resize(swapChainImages.size());
        uniformBufferAllocations.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            createBuffer(uniformBuffers[i], uniformBufferAllocations[i], bufferSize, vk::BufferUsageFlagBits::eUniformBuffer, VMA_MEMORY_USAGE_CPU_ONLY);
        }
    }

    void createDescriptorPool() {
        vk::DescriptorPoolSize poolSize(vk::DescriptorType::eUniformBuffer, static_cast<uint32_t>(swapChainImages.size()));

        vk::DescriptorPoolCreateInfo poolInfo({}, static_cast<uint32_t>(swapChainImages.size()), 1, &poolSize);

        try{
        descriptorPool = device.createDescriptorPool(poolInfo);
        } catch(std::exception const &e){

        }
    }

    void createDescriptorSets() {
        std::vector<vk::DescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
        vk::DescriptorSetAllocateInfo allocInfo(descriptorPool, static_cast<uint32_t>(swapChainImages.size()), layouts.data());
        descriptorSets.resize(swapChainImages.size());

        descriptorSets = device.allocateDescriptorSets(allocInfo);

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            vk::DescriptorBufferInfo bufferInfo(uniformBuffers[i], 0, sizeof(UniformBufferObject));
            vk::WriteDescriptorSet descriptorWrite(descriptorSets[i], 0, 0, 1, vk::DescriptorType::eUniformBuffer, {}, &bufferInfo);
            try{
                device.updateDescriptorSets(1, &descriptorWrite, 0, nullptr);
            } catch(std::exception const &e) {

            }
        }
    }

    void createCommandBuffers(){
        commandBuffers.resize(swapChainFramebuffers.size());
        vk::CommandBufferAllocateInfo allocInfo(commandPool, vk::CommandBufferLevel::ePrimary, (uint32_t) commandBuffers.size());
        commandBuffers = device.allocateCommandBuffers(allocInfo);

        for (size_t i = 0; i < commandBuffers.size(); i++) {
            vk::CommandBufferBeginInfo beginInfo;
            commandBuffers[i].begin(beginInfo);
            std::vector<vk::ClearValue> clearValues = {vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f})};
            vk::RenderPassBeginInfo renderPassInfo(renderPass, swapChainFramebuffers[i], vk::Rect2D({0, 0}, swapChainExtent), clearValues);

            commandBuffers[i].beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);
                commandBuffers[i].bindPipeline(vk::PipelineBindPoint::eGraphics, graphicsPipeline);
                std::vector<vk::Buffer> vertexBuffers = {vertexBuffer};
                std::vector<vk::DeviceSize> offsets = {0};
                commandBuffers[i].bindVertexBuffers(0, vertexBuffers, offsets);
                commandBuffers[i].bindIndexBuffer(indexBuffer, 0, vk::IndexType::eUint32);
                commandBuffers[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);
                commandBuffers[i].drawIndexed(static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
            commandBuffers[i].endRenderPass();

            commandBuffers[i].end();
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
            imageAvailableSemaphores[i] = device.createSemaphore(semaphoreInfo);
            renderFinishedSemaphores[i] = device.createSemaphore(semaphoreInfo);
            inFlightFences[i] = device.createFence(fenceInfo);
        }
    }

    void updateUniformBuffer(uint32_t currentImage) {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};
        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 10.0f);
        ubo.proj[1][1] *= -1;
        
        void* mappedData;
        vmaMapMemory(allocator, uniformBufferAllocations[currentImage], &mappedData);
            memcpy(mappedData, &ubo, (size_t) sizeof(ubo));
        vmaUnmapMemory(allocator, uniformBufferAllocations[currentImage]);
    }

    void drawFrame(){
        vk::Result result1 = device.waitForFences(inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
        uint32_t imageIndex;
        vk::Result result = device.acquireNextImageKHR(swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        if(result == vk::Result::eErrorOutOfDateKHR){
            recreateSwapChain();
            return;
        }else if(result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
            throw std::runtime_error("failed to acquire swap chain image!");
        updateUniformBuffer(imageIndex);

        if ((VkFence) imagesInFlight[imageIndex] != VK_NULL_HANDLE)
            vk::Result result2 = device.waitForFences(imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        imagesInFlight[imageIndex] = inFlightFences[currentFrame];

        std::vector<vk::Semaphore> waitSemaphores = {imageAvailableSemaphores[currentFrame]};
        std::vector<vk::PipelineStageFlags> waitStages = {vk::PipelineStageFlagBits::eColorAttachmentOutput};
        std::vector<vk::Semaphore> signalSemaphores = {renderFinishedSemaphores[currentFrame]};
        vk::SubmitInfo submitInfo(waitSemaphores, waitStages, commandBuffers[imageIndex], signalSemaphores);
        device.resetFences(inFlightFences[currentFrame]);
        graphicsQueue.submit(submitInfo, inFlightFences[currentFrame]);

        std::vector<vk::SwapchainKHR> swapChains = {swapChain};
        vk::PresentInfoKHR presentInfo(signalSemaphores, swapChains, imageIndex);
        result = presentQueue.presentKHR(presentInfo);
        if(result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR || framebufferResized){
            framebufferResized = false;
            recreateSwapChain();
        }else if(result != vk::Result::eSuccess)
            throw std::runtime_error("queue Present failed!");
        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void mainLoop(){
        double time = glfwGetTime();
        uint32_t fps = 0;
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            drawFrame();
            fps++;
            if((glfwGetTime() - time) >= 1.0){
                time = glfwGetTime();
                std::string title = "VulkanBase  FPS:"+std::to_string(fps);
                glfwSetWindowTitle(window, title.c_str());
                fps = 0;
            }
        }
        device.waitIdle();
    }

    void cleanupSwapchain(){
        for (auto framebuffer : swapChainFramebuffers) {
            device.destroyFramebuffer(framebuffer);
        }
        device.freeCommandBuffers(commandPool, commandBuffers);
        device.destroyPipeline(graphicsPipeline);
        device.destroyPipelineLayout(pipelineLayout);
        device.destroyRenderPass(renderPass);
        for (auto imageView : swapChainImageViews) {
            device.destroyImageView(imageView);
        }
        device.destroySwapchainKHR(swapChain);

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            vmaDestroyBuffer(allocator, uniformBuffers[i], uniformBufferAllocations[i]);
        }

        device.destroyDescriptorPool();
    }

    void cleanup(){
        cleanupSwapchain();

        device.destroyDescriptorSetLayout(descriptorSetLayout);
        vmaDestroyBuffer(allocator, indexBuffer, indexBufferAllocation);
        vmaDestroyBuffer(allocator, vertexBuffer, vertexBufferAllocation);
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            device.destroySemaphore(imageAvailableSemaphores[i]);
            device.destroySemaphore(renderFinishedSemaphores[i]);
            device.destroyFence(inFlightFences[i]);
        }
        device.destroyCommandPool(commandPool);
        vmaDestroyAllocator(allocator);
        device.destroy();
        if (enableValidation) {
            instance.destroyDebugUtilsMessengerEXT(debugMessenger);
        }
        instance.destroySurfaceKHR(surface);
        instance.destroy();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void recreateSwapChain() {
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(window, &width, &height);
            glfwWaitEvents();
        }
        device.waitIdle();

        cleanupSwapchain();

        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFramebuffers();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommandBuffers();

        imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);
    }

    static void framebufferResizeCallback(GLFWwindow *window, int width, int height){
        auto app = reinterpret_cast<VulkanBase *>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }
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