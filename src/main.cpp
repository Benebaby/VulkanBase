#define TINYGLTF_USE_CPP14

#include "globalDefs.hpp"
#include "globalIncludes.hpp"
#include "SpirvHelper.h"
#include "Utils.h"
#include "Buffer.hpp"
// GDCM

#include <gdcmScanner.h>
#include <gdcmTesting.h>
#include <gdcmIPPSorter.h>
#include <gdcmDirectionCosines.h>
#include <gdcmDirectory.h>
#include <gdcmImageReader.h>
#include <gdcmReader.h>

#include <optional>
#include <set>
#include <stb_image.h>
#include <stb_image_write.h>
#include <tiny_gltf.h>
#include <chrono>
#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>
#include <bitset>


#include <fstream>

const uint32_t WIDTH = 1600;
const uint32_t HEIGHT = 900;
const int MAX_FRAMES_IN_FLIGHT = 2;
const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails
{
    vk::SurfaceCapabilitiesKHR capabilities;
    std::vector<vk::SurfaceFormatKHR> formats;
    std::vector<vk::PresentModeKHR> presentModes;
};

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 texCoord;

    static std::array<vk::VertexInputBindingDescription, 1> getBindingDescription()
    {
        std::array<vk::VertexInputBindingDescription, 1> bindingDescriptions = {
            vk::VertexInputBindingDescription(0, sizeof(Vertex), vk::VertexInputRate::eVertex)};
        return bindingDescriptions;
    }
    static std::array<vk::VertexInputAttributeDescription, 4> getAttributeDescriptions()
    {
        std::array<vk::VertexInputAttributeDescription, 4> attributeDescriptions{
            vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, pos)),
            vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, color)),
            vk::VertexInputAttributeDescription(2, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, normal)),
            vk::VertexInputAttributeDescription(3, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, texCoord))};
        return attributeDescriptions;
    }
};

std::vector<Vertex> vertices = {
    //Position            //Color            //Normal              //UV
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f,  -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{0.5f,   0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

    {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

    {{0.5f,   0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f,  -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f,  -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f,   0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

    {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f,   0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f,   0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f,  -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f,  -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},

    {{0.5f,   0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
    {{0.5f,  -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}}};

std::vector<uint32_t> indices = {
    0, 1, 2, 0, 2, 3,
    4, 5, 6, 4, 6, 7,
    8, 9, 10, 8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
    20, 21, 22, 20, 22, 23};

struct UniformBufferObject
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    glm::vec2 size = glm::vec2((float)WIDTH, (float)HEIGHT);
};

static void check_vk_result(VkResult err)
{
    if (err != VK_SUCCESS)
        throw std::runtime_error("validation layers requested, but not available!");
}

class VulkanBase
{
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow *window;
    VmaAllocator allocator;
    vk::Instance instance;
    bool enableValidation = true;
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

    vk::ShaderModule vertShaderModule;
    vk::ShaderModule fragShaderModule;
    vk::Pipeline graphicsPipeline;

    vk::CommandPool commandPool;

    vk::Image depthImage;
    VmaAllocation depthImageAllocation;
    vk::ImageView depthImageView;

    std::vector<vk::CommandBuffer> commandBuffers;

    Buffer *vertexBuffer;
    Buffer *indexBuffer;
    std::vector<Buffer *> uniformBuffers;

    vk::Image textureImage;
    glm::vec3 textureScale;
    VmaAllocation textureImageAllocation;
    vk::ImageView textureImageView;
    vk::Sampler textureSampler;

    vk::DescriptorPool descriptorPool;
    std::vector<vk::DescriptorSet> descriptorSets;

    std::vector<vk::Semaphore> imageAvailableSemaphores;
    std::vector<vk::Semaphore> renderFinishedSemaphores;
    std::vector<vk::Fence> inFlightFences;
    std::vector<vk::Fence> imagesInFlight;
    size_t currentFrame = 0;
    bool framebufferResized = false;

    vk::DescriptorPool descriptorPoolImgui;
    vk::RenderPass renderPassImgui;
    vk::CommandPool commandPoolImgui;
    std::vector<vk::CommandBuffer> commandBuffersImgui;
    std::vector<vk::Framebuffer> framebuffersImgui;

    void initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanBase", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    void initVulkan()
    {
        createInstance();
        if (enableValidation)
            setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createAllocator();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createDescriptorSetLayout();
        readAndCompileShaders();
        createGraphicsPipeline();
        createCommandPool();
        Buffer::init(allocator, device, commandPool, graphicsQueue);
        createDepthResources();
        createFramebuffers();
        createTextureImage();
        createTextureImageView();
        createTextureSampler();
        createVertexBuffer();
        createIndexBuffer();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommandBuffers();
        createSyncObjects();

        //imgui
        initImGui();
    }

    void createInstance()
    {
        if (enableValidation && !checkValidationLayerSupport())
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        vk::ApplicationInfo applicationInfo("VulkanBase", VK_MAKE_VERSION(0, 0, 1), "VulkanEngine", 1, VK_API_VERSION_1_1);

        try
        {
            if (enableValidation)
            {
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
                vk::StructureChain<vk::InstanceCreateInfo, vk::DebugUtilsMessengerCreateInfoEXT> instanceCreateInfoChain{
                    vk::InstanceCreateInfo(vk::InstanceCreateFlags(), &applicationInfo, validationLayers, extensions),
                    vk::DebugUtilsMessengerCreateInfoEXT({}, messageSeverityFlags, messageTypeFlags, debugCallback)};
                instance = vk::createInstance(instanceCreateInfoChain.get<vk::InstanceCreateInfo>());
            }
            else
            {
                vk::InstanceCreateInfo instanceCreateInfo(vk::InstanceCreateFlags(), &applicationInfo, {}, extensions);
                instance = vk::createInstance(instanceCreateInfo);
            }
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void setupDebugMessenger()
    {
        pfnVkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
        if (!pfnVkCreateDebugUtilsMessengerEXT)
        {
            throw std::runtime_error("GetInstanceProcAddr: Unable to find pfnVkCreateDebugUtilsMessengerEXT function.");
        }
        pfnVkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
        if (!pfnVkDestroyDebugUtilsMessengerEXT)
        {
            throw std::runtime_error("GetInstanceProcAddr: Unable to find pfnVkDestroyDebugUtilsMessengerEXT function.");
        }
        vk::DebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo({}, messageSeverityFlags, messageTypeFlags, debugCallback);
        try
        {
            debugMessenger = instance.createDebugUtilsMessengerEXT(debugMessengerCreateInfo, nullptr);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    bool checkValidationLayerSupport()
    {
        std::vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();
        for (const char *layerName : validationLayers)
        {
            bool layerFound = false;
            for (const auto &layerProperties : availableLayers)
            {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound)
            {
                return false;
            }
        }
        return true;
    }

    void createSurface()
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, reinterpret_cast<VkSurfaceKHR *>(&surface)) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void pickPhysicalDevice()
    {
        std::vector<vk::PhysicalDevice> devices = instance.enumeratePhysicalDevices();
        bool deviceFound = false;
        for (const auto &device : devices)
        {
            if (isDeviceSuitable(device))
            {
                deviceFound = true;
                physicalDevice = device;
                break;
            }
        }
        if (!deviceFound)
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    bool isDeviceSuitable(vk::PhysicalDevice pDevice)
    {
        QueueFamilyIndices indices = findQueueFamilies(pDevice);
        bool extensionsSupported = checkDeviceExtensionSupport(pDevice);
        bool swapChainAdequate = false;

        if (extensionsSupported)
        {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(pDevice);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        vk::PhysicalDeviceFeatures supportedFeatures = pDevice.getFeatures();

        return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    }

    QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice pDevice)
    {
        QueueFamilyIndices indices;
        std::vector<vk::QueueFamilyProperties> queueFamilies = pDevice.getQueueFamilyProperties();
        for (uint32_t i = 0; i < queueFamilies.size(); i++)
        {
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
            {
                indices.graphicsFamily = i;
            }
            if (pDevice.getSurfaceSupportKHR(i, surface))
            {
                indices.presentFamily = i;
            }
            if (indices.isComplete())
            {
                break;
            }
        }
        return indices;
    }

    bool checkDeviceExtensionSupport(vk::PhysicalDevice pDevice)
    {
        std::vector<vk::ExtensionProperties> availableExtensions = pDevice.enumerateDeviceExtensionProperties();
        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
        for (const auto &extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }
        return requiredExtensions.empty();
    }

    void createLogicalDevice()
    {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            vk::DeviceQueueCreateInfo queueCreateInfo({}, queueFamily, 1, &queuePriority);
            queueCreateInfos.push_back(queueCreateInfo);
        }

        vk::PhysicalDeviceFeatures deviceFeatures;
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        //MacOS portability extension
        std::vector<vk::ExtensionProperties> extensionProperties = physicalDevice.enumerateDeviceExtensionProperties();
        for (auto extensionProperty : extensionProperties)
        {
            if (std::string(extensionProperty.extensionName.data()) == std::string(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME))
                deviceExtensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
        }

        vk::DeviceCreateInfo createInfo;
        if (enableValidation)
        {
            createInfo = vk::DeviceCreateInfo({}, queueCreateInfos, validationLayers, deviceExtensions, &deviceFeatures);
        }
        else
        {
            createInfo = vk::DeviceCreateInfo({}, queueCreateInfos, {}, deviceExtensions, &deviceFeatures);
        }
        try
        {
            device = physicalDevice.createDevice(createInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
        graphicsQueue = device.getQueue(indices.graphicsFamily.value(), 0);
        presentQueue = device.getQueue(indices.presentFamily.value(), 0);
    }

    void createAllocator()
    {
        VmaAllocatorCreateInfo allocatorInfo = {};
        allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_2;
        allocatorInfo.physicalDevice = physicalDevice;
        allocatorInfo.device = device;
        allocatorInfo.instance = instance;

        if (vmaCreateAllocator(&allocatorInfo, &allocator) != VK_SUCCESS)
            throw std::runtime_error("failed to create Allocator");
    }

    void initImGui()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();
        ImGui_ImplGlfw_InitForVulkan(window, true);

        std::array<vk::DescriptorPoolSize, 11> poolSizes{
            vk::DescriptorPoolSize{vk::DescriptorType::eSampler, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eCombinedImageSampler, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eSampledImage, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eStorageImage, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eUniformTexelBuffer, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eStorageTexelBuffer, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eUniformBuffer, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eStorageBuffer, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eUniformBufferDynamic, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eStorageBufferDynamic, 1000},
            vk::DescriptorPoolSize{vk::DescriptorType::eInputAttachment, 1000}};

        vk::DescriptorPoolCreateInfo descriptorPoolInfo({}, static_cast<uint32_t>(1000 * poolSizes.size()), poolSizes);

        try
        {
            descriptorPoolImgui = device.createDescriptorPool(descriptorPoolInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }

        vk::AttachmentDescription attachment(
            {},
            swapChainImageFormat,
            vk::SampleCountFlagBits::e1,
            vk::AttachmentLoadOp::eLoad,
            vk::AttachmentStoreOp::eStore,
            vk::AttachmentLoadOp::eDontCare,
            vk::AttachmentStoreOp::eDontCare,
            vk::ImageLayout::eColorAttachmentOptimal,
            vk::ImageLayout::ePresentSrcKHR);
        vk::AttachmentReference attachmentRef(0, vk::ImageLayout::eColorAttachmentOptimal);

        vk::SubpassDescription subpass({}, vk::PipelineBindPoint::eGraphics, {}, attachmentRef, {}, {});

        vk::SubpassDependency dependency(
            VK_SUBPASS_EXTERNAL,
            0,
            vk::PipelineStageFlagBits::eColorAttachmentOutput,
            vk::PipelineStageFlagBits::eColorAttachmentOutput,
            vk::AccessFlagBits::eNoneKHR,
            vk::AccessFlagBits::eColorAttachmentWrite);

        std::array<vk::AttachmentDescription, 1> attachments = {attachment};

        vk::RenderPassCreateInfo renderPassInfo(
            {},
            attachments,
            subpass,
            dependency);
        try
        {
            renderPassImgui = device.createRenderPass(renderPassInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }

        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = instance;
        init_info.PhysicalDevice = physicalDevice;
        init_info.Device = device;
        init_info.QueueFamily = findQueueFamilies(physicalDevice).graphicsFamily.value();
        init_info.Queue = graphicsQueue;
        init_info.PipelineCache = VK_NULL_HANDLE;
        init_info.DescriptorPool = descriptorPoolImgui;
        init_info.Allocator = VK_NULL_HANDLE;
        init_info.MinImageCount = static_cast<uint32_t>(swapChainFramebuffers.size());
        init_info.ImageCount = static_cast<uint32_t>(swapChainFramebuffers.size());
        init_info.CheckVkResultFn = check_vk_result;
        ImGui_ImplVulkan_Init(&init_info, renderPassImgui);

        vk::CommandBuffer command_buffer = beginSingleTimeCommands();
        ImGui_ImplVulkan_CreateFontsTexture(command_buffer);
        endSingleTimeCommands(command_buffer);

        //create command pool
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);
        vk::CommandPoolCreateInfo commandPoolInfo(vk::CommandPoolCreateFlagBits::eResetCommandBuffer, queueFamilyIndices.graphicsFamily.value());
        try
        {
            commandPoolImgui = device.createCommandPool(commandPoolInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }

        //create commandbuffers
        commandBuffersImgui.resize(swapChainFramebuffers.size());
        vk::CommandBufferAllocateInfo allocInfo(commandPoolImgui, vk::CommandBufferLevel::ePrimary, (uint32_t)commandBuffersImgui.size());
        try
        {
            commandBuffersImgui = device.allocateCommandBuffers(allocInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
        //create Framebuffers
        framebuffersImgui.resize(swapChainImageViews.size());
        for (size_t i = 0; i < swapChainImageViews.size(); i++)
        {
            std::array<vk::ImageView, 1> attachments = {
                swapChainImageViews[i]};
            vk::FramebufferCreateInfo framebufferInfo({}, renderPassImgui, attachments, swapChainExtent.width, swapChainExtent.height, 1);
            try
            {
                framebuffersImgui[i] = device.createFramebuffer(framebufferInfo);
            }
            catch (std::exception &e)
            {
                std::cerr << "Exception Thrown: " << e.what();
            }
        }
        //record Command Buffers
    }

    void recreateImGuiFramebuffer()
    {
        //create Framebuffers
        framebuffersImgui.resize(swapChainImageViews.size());
        for (size_t i = 0; i < swapChainImageViews.size(); i++)
        {
            std::array<vk::ImageView, 1> attachments = {
                swapChainImageViews[i]};
            vk::FramebufferCreateInfo framebufferInfo({}, renderPassImgui, attachments, swapChainExtent.width, swapChainExtent.height, 1);
            try
            {
                framebuffersImgui[i] = device.createFramebuffer(framebufferInfo);
            }
            catch (std::exception &e)
            {
                std::cerr << "Exception Thrown: " << e.what();
            }
        }
    }

    vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats)
    {
        for (const auto &availableFormat : availableFormats)
        {
            if (availableFormat.format == vk::Format::eB8G8R8A8Srgb && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
            {
                return availableFormat;
            }
        }
        return availableFormats[0];
    }

    vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR> &availablePresentModes)
    {
        for (const auto &availablePresentMode : availablePresentModes)
        {
            if (availablePresentMode == vk::PresentModeKHR::eFifo)
            {
                return availablePresentMode;
            }
        }
        return vk::PresentModeKHR::eFifo;
    }

    vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities)
    {
        if (capabilities.currentExtent.width != UINT32_MAX)
        {
            return capabilities.currentExtent;
        }
        else
        {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            vk::Extent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)};
            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
            return actualExtent;
        }
    }

    SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice pDevice)
    {
        SwapChainSupportDetails details;
        details.capabilities = pDevice.getSurfaceCapabilitiesKHR(surface);
        details.formats = pDevice.getSurfaceFormatsKHR(surface);
        details.presentModes = pDevice.getSurfacePresentModesKHR(surface);
        return details;
    }

    void createSwapChain()
    {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

        vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        vk::PresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        vk::Extent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
        {
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
        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
            createInfo.imageSharingMode = vk::SharingMode::eExclusive;
        }
        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;
        try
        {
            swapChain = device.createSwapchainKHR(createInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
        swapChainImages = device.getSwapchainImagesKHR(swapChain);
        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }

    void createImageViews()
    {
        swapChainImageViews.resize(swapChainImages.size());
        for (size_t i = 0; i < swapChainImages.size(); i++)
        {
            swapChainImageViews[i] = createImageView(swapChainImages[i], vk::ImageViewType::e2D, swapChainImageFormat, vk::ImageAspectFlagBits::eColor);
        }
    }

    vk::ShaderModule createShaderModule(const std::vector<uint32_t> code)
    {
        vk::ShaderModuleCreateInfo createInfo({}, code);
        vk::ShaderModule shaderModule;
        try
        {
            shaderModule = device.createShaderModule(createInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
        return shaderModule;
    }

    void createRenderPass()
    {
        vk::AttachmentDescription colorAttachment({}, swapChainImageFormat, vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined, vk::ImageLayout::eColorAttachmentOptimal);
        vk::AttachmentReference colorAttachmentRef(0, vk::ImageLayout::eColorAttachmentOptimal);

        vk::AttachmentDescription depthAttachment({}, findDepthFormat(), vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eDontCare, vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined, vk::ImageLayout::eDepthStencilAttachmentOptimal);
        vk::AttachmentReference depthAttachmentRef(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

        vk::SubpassDescription subpass({}, vk::PipelineBindPoint::eGraphics, {}, colorAttachmentRef, {}, &depthAttachmentRef);
        vk::SubpassDependency dependency(
            VK_SUBPASS_EXTERNAL,
            0,
            vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests,
            vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests,
            vk::AccessFlagBits::eNoneKHR,
            vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite);

        std::array<vk::AttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};

        vk::RenderPassCreateInfo renderPassInfo({}, attachments, subpass, dependency);
        try
        {
            renderPass = device.createRenderPass(renderPassInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void createDescriptorSetLayout()
    {
        vk::DescriptorSetLayoutBinding uboLayoutBinding(0, vk::DescriptorType::eUniformBuffer, 1, vk::ShaderStageFlagBits::eVertex, nullptr);
        vk::DescriptorSetLayoutBinding samplerLayoutBinding(1, vk::DescriptorType::eCombinedImageSampler, 1, vk::ShaderStageFlagBits::eFragment, nullptr);

        std::array<vk::DescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
        vk::DescriptorSetLayoutCreateInfo layoutInfo({}, bindings);

        try
        {
            descriptorSetLayout = device.createDescriptorSetLayout(layoutInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void readAndCompileShaders()
    {
        glslang::InitializeProcess();
        std::vector<uint32_t> vertShaderCodeSPIRV;
        std::vector<uint32_t> fragShaderCodeSPIRV;
        SpirvHelper::GLSLtoSPV(vk::ShaderStageFlagBits::eVertex, "/shaderVolume.vert", vertShaderCodeSPIRV);
        SpirvHelper::GLSLtoSPV(vk::ShaderStageFlagBits::eFragment, "/shaderVolume.frag", fragShaderCodeSPIRV);
        try
        {
            vertShaderModule = createShaderModule(vertShaderCodeSPIRV);
            fragShaderModule = createShaderModule(fragShaderCodeSPIRV);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
        glslang::FinalizeProcess();
    }

    void createGraphicsPipeline()
    {
        vk::PipelineShaderStageCreateInfo vertShaderStageInfo({}, vk::ShaderStageFlagBits::eVertex, vertShaderModule, "main");
        vk::PipelineShaderStageCreateInfo fragShaderStageInfo({}, vk::ShaderStageFlagBits::eFragment, fragShaderModule, "main");

        std::vector<vk::PipelineShaderStageCreateInfo> shaderStages = {vertShaderStageInfo, fragShaderStageInfo};

        auto bindingDescription = Vertex::getBindingDescription();
        auto attributeDescriptions = Vertex::getAttributeDescriptions();

        vk::PipelineVertexInputStateCreateInfo vertexInputInfo({}, bindingDescription, attributeDescriptions);
        vk::PipelineInputAssemblyStateCreateInfo inputAssembly({}, vk::PrimitiveTopology::eTriangleList, VK_FALSE);
        vk::Viewport viewport(0.0f, 0.0f, (float)swapChainExtent.width, (float)swapChainExtent.height, 0.0f, 1.0f);
        vk::Rect2D scissor(vk::Offset2D(0, 0), swapChainExtent);
        vk::PipelineViewportStateCreateInfo viewportState({}, viewport, scissor);
        vk::PipelineRasterizationStateCreateInfo rasterizer({}, VK_FALSE, VK_FALSE, vk::PolygonMode::eFill, vk::CullModeFlagBits::eBack, vk::FrontFace::eCounterClockwise, VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f);
        vk::PipelineMultisampleStateCreateInfo multisampling({}, vk::SampleCountFlagBits::e1, VK_FALSE);

        vk::PipelineDepthStencilStateCreateInfo depthStencil({}, VK_TRUE, VK_TRUE, vk::CompareOp::eLess, VK_FALSE, VK_FALSE);

        vk::PipelineColorBlendAttachmentState colorBlendAttachment(VK_FALSE, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);
        vk::PipelineColorBlendStateCreateInfo colorBlending({}, VK_FALSE, vk::LogicOp::eCopy, colorBlendAttachment);
        vk::PipelineLayoutCreateInfo pipelineLayoutInfo({}, 1, &descriptorSetLayout);

        try
        {
            pipelineLayout = device.createPipelineLayout(pipelineLayoutInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }

        vk::GraphicsPipelineCreateInfo pipelineInfo({}, shaderStages, &vertexInputInfo, &inputAssembly, {}, &viewportState, &rasterizer, &multisampling, &depthStencil, &colorBlending, {}, pipelineLayout, renderPass);

        vk::Result result;
        std::tie(result, graphicsPipeline) = device.createGraphicsPipeline(nullptr, pipelineInfo);
        switch (result)
        {
        case vk::Result::eSuccess:
            break;
        default:
            throw std::runtime_error("failed to create graphics Pipeline!");
        }
    }

    void createFramebuffers()
    {
        swapChainFramebuffers.resize(swapChainImageViews.size());
        for (size_t i = 0; i < swapChainImageViews.size(); i++)
        {
            std::array<vk::ImageView, 2> attachments = {
                swapChainImageViews[i],
                depthImageView};
            vk::FramebufferCreateInfo framebufferInfo({}, renderPass, attachments, swapChainExtent.width, swapChainExtent.height, 1);
            try
            {
                swapChainFramebuffers[i] = device.createFramebuffer(framebufferInfo);
            }
            catch (std::exception &e)
            {
                std::cerr << "Exception Thrown: " << e.what();
            }
        }
    }

    void createCommandPool()
    {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);
        vk::CommandPoolCreateInfo poolInfo({}, queueFamilyIndices.graphicsFamily.value());
        try
        {
            commandPool = device.createCommandPool(poolInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void createDepthResources()
    {
        vk::Format depthFormat = findDepthFormat();

        createImage(depthImage, depthImageAllocation, vk::ImageUsageFlagBits::eDepthStencilAttachment, VMA_MEMORY_USAGE_GPU_ONLY, vk::ImageType::e2D, swapChainExtent.width, swapChainExtent.height, 1, depthFormat, vk::ImageTiling::eOptimal);
        depthImageView = createImageView(depthImage, vk::ImageViewType::e2D, depthFormat, vk::ImageAspectFlagBits::eDepth);
    }

    vk::Format findSupportedFormat(const std::vector<vk::Format> &candidates, vk::ImageTiling tiling, vk::FormatFeatureFlags features)
    {
        for (vk::Format format : candidates)
        {
            vk::FormatProperties props = physicalDevice.getFormatProperties(format);

            if (tiling == vk::ImageTiling::eLinear && (props.linearTilingFeatures & features) == features)
            {
                return format;
            }
            else if (tiling == vk::ImageTiling::eOptimal && (props.optimalTilingFeatures & features) == features)
            {
                return format;
            }
        }
        throw std::runtime_error("failed to find supported format!");
    }

    vk::Format findDepthFormat()
    {
        return findSupportedFormat({vk::Format::eD32Sfloat, vk::Format::eD32SfloatS8Uint, vk::Format::eD24UnormS8Uint}, vk::ImageTiling::eOptimal, vk::FormatFeatureFlagBits::eDepthStencilAttachment);
    }

    void createTextureImage()
    {
        std::vector<uint16_t> series(0);

        unsigned int dimx = 0;
        unsigned int dimy = 0;
        unsigned int dimz = 0;

        std::string DICOMDIR_directory_path = ASSET_PATH "/DICOM/Schaedel_Weiser_Kurt/";
        std::string DICOMDIR_file_name = "DICOMDIR";
        std::string DICOMDIR_file_path = DICOMDIR_directory_path+DICOMDIR_file_name;
        uint32_t seriesIndex = 2;
        gdcm::Reader reader;
        reader.SetFileName(DICOMDIR_file_path.c_str());
        if (!reader.Read()){
            std::cerr << "Could not read: " << DICOMDIR_file_path << std::endl;
            return;
        }
        std::stringstream strm;
        gdcm::File &file = reader.GetFile();
        gdcm::DataSet &ds = file.GetDataSet();
        gdcm::FileMetaInformation &fmi = file.GetHeader();

        gdcm::MediaStorage ms;
        ms.SetFromFile(file);
        if( ms != gdcm::MediaStorage::MediaStorageDirectoryStorage )
        {
            std::cout << "This file is not a DICOMDIR" << std::endl;
        }

        if (fmi.FindDataElement( gdcm::Tag (0x0002, 0x0002))) {
            strm.str("");
            fmi.GetDataElement( gdcm::Tag (0x0002, 0x0002) ).GetValue().Print(strm);
        } else {
            std::cerr << " Media Storage Sop Class UID not present" << std::endl;
        }

        if ("1.2.840.10008.1.3.10"!=strm.str()) {
            std::cout << "This file is not a DICOMDIR" << std::endl;
        }

        if(fmi.FindDataElement(gdcm::Tag(0x10, 0x10))){
            strm.str("");
            fmi.GetDataElement( gdcm::Tag (0x10, 0x10) ).GetValue().Print(strm);
            int test = 0;
        }

        gdcm::DataSet::DataElementSet::const_iterator it = ds.GetDES().begin();

        std::vector<std::string> all_paths(0);
        std::vector<std::vector<std::string>> seriespaths(0);

        for (; it != ds.GetDES().end(); ++it)
        {
            if (it->GetTag() == gdcm::Tag(0x0004, 0x1220))
            {
                const gdcm::DataElement &de = (*it);
                // ne pas utiliser GetSequenceOfItems pour extraire les items
                gdcm::SmartPointer<gdcm::SequenceOfItems> sqi = de.GetValueAsSQ();
                unsigned int itemused = 1;
                while (itemused <= sqi->GetNumberOfItems())
                {
                    strm.str("");

                    if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                        sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);

                    //TODO il faut trimer strm.str() avant la comparaison
                    while ((strm.str() == "PATIENT") || ((strm.str() == "PATIENT ")))
                    {
                        std::cout << strm.str() << std::endl;
                        strm.str("");
                        if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0010, 0x0010)))
                            sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0010, 0x0010)).GetValue().Print(strm);
                        std::cout << "PATIENT NAME : " << strm.str() << std::endl;

                        //PATIENT ID
                        strm.str("");
                        if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0010, 0x0020)))
                            sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0010, 0x0020)).GetValue().Print(strm);
                        std::cout << "PATIENT ID : " << strm.str() << std::endl;

                        /*ADD TAG TO READ HERE*/
                        std::cout << "=========================== " << std::endl;
                        itemused++;
                        strm.str("");
                        if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                            sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);

                        //TODO il faut trimer strm.str() avant la comparaison
                        while ((strm.str() == "STUDY") || ((strm.str() == "STUDY ")))
                        {
                            std::cout << "  " << strm.str() << std::endl;
                            //UID
                            strm.str("");
                            if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0020, 0x000d)))
                                sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0020, 0x000d)).GetValue().Print(strm);
                            std::cout << "      STUDY UID : " << strm.str() << std::endl;

                            //STUDY DATE
                            strm.str("");
                            if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0008, 0x0020)))
                                sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0008, 0x0020)).GetValue().Print(strm);
                            std::cout << "      STUDY DATE : " << strm.str() << std::endl;

                            std::cout << "      =========================== " << std::endl;

                            itemused++;
                            strm.str("");
                            if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                                sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);

                            while ((strm.str() == "SERIES") || ((strm.str() == "SERIES ")))
                            {
                                std::cout << "      " << strm.str() << std::endl;
                                strm.str("");
                                if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0020, 0x000e)))
                                    sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0020, 0x000e)).GetValue().Print(strm);

                                //SERIE MODALITY
                                strm.str("");
                                if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0008, 0x0060)))
                                    sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0008, 0x0060)).GetValue().Print(strm);
                                std::cout << "          SERIE MODALITY " << strm.str() << std::endl;

                                itemused++;
                                strm.str("");
                                if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                                    sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);

                                uint32_t imagecount = 0;
                                std::vector<std::string> tempseriespaths(0);

                                while ((strm.str() == "IMAGE") || ((strm.str() == "IMAGE "))) {
                                    imagecount++;
                                    //std::cout << "          " << strm.str() << std::endl;

                                    //IMAGE UID
                                    strm.str("");
                                    if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1511)))
                                        sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1511)).GetValue().Print(strm);

                                    //IMAGE PATH
                                    strm.str("");
                                    if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1500)))
                                        sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1500)).GetValue().Print(strm);

                                    tempseriespaths.push_back(strm.str());

                                    if (itemused < sqi->GetNumberOfItems())
                                        itemused++;
                                    else
                                        break;

                                    strm.str("");
                                    if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                                        sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);
                                }
                                std::cout << "          SERIE IMAGECOUNT " << std::to_string(imagecount) << std::endl;
                                seriespaths.push_back(tempseriespaths);
                            }
                        }
                    }
                    itemused++;
                }
            }
        }
        dimz = (unsigned int)seriespaths[seriesIndex].size();
        std::cout << std::endl;
        if(seriespaths[seriesIndex].size() > 1){
            double spacingx = 1.0;
            double spacingy = 1.0;
            double spacingz = 1.0;
            double positionfirst = 0.0;
            double positionsecond = 1.0;
            {
                std::string imageFileName = DICOMDIR_directory_path;
                imageFileName += seriespaths[seriesIndex][0];
                gdcm::ImageReader reader;
                reader.SetFileName(imageFileName.c_str());
                if (!reader.Read()){
                    std::cerr << "Could not read: " << imageFileName << std::endl;
                    return;
                }
                gdcm::Image image = reader.GetImage();
                const unsigned int *dims = image.GetDimensions();
                dimx = dims[0];
                dimy = dims[1];
                const double *spacing = image.GetSpacing();
                spacingx = spacing[0] * 2.0;
                spacingy = spacing[1] * 2.0;
                gdcm::DataSet ds = reader.GetFile().GetDataSet();
                if(ds.FindDataElement( gdcm::Tag(0x0020, 0x1041))){
                    strm.str("");
                    ds.GetDataElement(gdcm::Tag(0x0020, 0x1041)).GetValue().Print(strm);
                    positionfirst = std::stod(strm.str(), nullptr);

                }
            }
            {
                std::string imageFileName = DICOMDIR_directory_path;
                imageFileName += seriespaths[seriesIndex][1];
                gdcm::ImageReader reader;
                reader.SetFileName(imageFileName.c_str());
                if (!reader.Read()){
                    std::cerr << "Could not read: " << imageFileName << std::endl;
                    return;
                }
                gdcm::DataSet ds = reader.GetFile().GetDataSet();
                if(ds.FindDataElement( gdcm::Tag(0x0020, 0x1041))){
                    strm.str("");
                    ds.GetDataElement(gdcm::Tag(0x0020, 0x1041)).GetValue().Print(strm);
                    positionsecond = std::stod(strm.str(), nullptr);
                }
                if((abs(positionsecond - positionfirst) < 0.3 || abs(positionsecond - positionfirst) > 5) && ds.FindDataElement( gdcm::Tag(0x0018, 0x0050))){
                    strm.str("");
                    ds.GetDataElement(gdcm::Tag(0x0018, 0x1050)).GetValue().Print(strm);
                    spacingz = std::stod(strm.str(), nullptr);
                }else{
                    spacingz = abs(positionsecond - positionfirst);
                }
            }
            std:: cout << "Spacing: " << spacingx << ", " << spacingy << ", " << spacingz << std::endl;
            textureScale = glm::vec3(spacingx * (dimx - 1), spacingy * (dimy - 1), spacingz * (dimz - 1));
            if(textureScale.x >= textureScale.y && textureScale.x >= textureScale.z)
                textureScale = glm::vec3(1.0, textureScale.y / textureScale.x, textureScale.z / textureScale.x);
            else if(textureScale.y >= textureScale.x && textureScale.y >= textureScale.z)
                textureScale = glm::vec3(textureScale.x / textureScale.y, 1.0 ,textureScale.z / textureScale.y);
            else if(textureScale.z >= textureScale.x && textureScale.z >= textureScale.y)
                textureScale = glm::vec3(textureScale.x / textureScale.z, textureScale.y / textureScale.z, 1.0);
            else
                textureScale = glm::vec3(1.0);
            std:: cout << "Relative Spacing: " << textureScale.x << ", " << textureScale.y << ", " << textureScale.z << std::endl;
        }else{
            textureScale = glm::vec3(1.0);
        }

        // std::ofstream myfile;
        // myfile.open (TEXTURE_PATH "/example.pgm");
        // myfile << "P2\n";
        for (size_t i = 0; i < seriespaths[seriesIndex].size(); i++){
            std::string imageFileName = DICOMDIR_directory_path;
            imageFileName += seriespaths[seriesIndex][i];
            gdcm::ImageReader reader;
            reader.SetFileName(imageFileName.c_str());
            if (!reader.Read()){
                std::cerr << "Could not read: " << imageFileName << std::endl;
                return;
            }
            gdcm::Image image = reader.GetImage();
            unsigned long len = image.GetBufferLength();

            // if(i == 12){
            //     myfile << dimx << " " << dimy << "\n";
            //     myfile << "4096\n";
            // }

            std::vector<uint8_t> tempImage8Bit(len, 0x00);
            image.GetBuffer(reinterpret_cast<char*>(tempImage8Bit.data()));
            for (size_t j = 0; j < tempImage8Bit.size(); j += 2)
            {
                uint16_t r = 0x0000;
                uint16_t g = 0x0000;
                r |= tempImage8Bit[j] << 0;
                g |= tempImage8Bit[j+1] << 8;
                uint16_t result = g | r;
                series.push_back(result);
                // if(i == 12){
                //     myfile << std::to_string(result) << " ";
                // }
            }
        }
        // myfile.close();

        vk::DeviceSize dicomSize = (uint64_t) (series.size() * 2);

        Buffer dic_stagingBuffer = Buffer(dicomSize, vk::BufferUsageFlagBits::eTransferSrc, VMA_MEMORY_USAGE_CPU_ONLY);

        dic_stagingBuffer.map();
            dic_stagingBuffer.copyTo(series.data());
        dic_stagingBuffer.unmap();

        createImage(textureImage, textureImageAllocation, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled, VMA_MEMORY_USAGE_GPU_ONLY, vk::ImageType::e3D, dimx, dimy, dimz, vk::Format::eR16Unorm, vk::ImageTiling::eOptimal);

        transitionImageLayout(textureImage, vk::Format::eR16Unorm, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal);
            copyBufferToImage(dic_stagingBuffer.getHandle(), textureImage, dimx, dimy, dimz);
        transitionImageLayout(textureImage, vk::Format::eR16Unorm, vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal);
    }

    void createTextureImageView()
    {
        textureImageView = createImageView(textureImage, vk::ImageViewType::e3D,vk::Format::eR16Unorm, vk::ImageAspectFlagBits::eColor);
    }

    void createTextureSampler()
    {
        vk::PhysicalDeviceProperties properties = physicalDevice.getProperties();

        vk::SamplerCreateInfo samplerInfo(
            {},
            vk::Filter::eLinear,
            vk::Filter::eLinear,
            vk::SamplerMipmapMode::eLinear,
            vk::SamplerAddressMode::eClampToEdge,
            vk::SamplerAddressMode::eClampToEdge,
            vk::SamplerAddressMode::eClampToEdge,
            0.0f,
            VK_TRUE,
            properties.limits.maxSamplerAnisotropy,
            VK_FALSE,
            vk::CompareOp::eNever,
            0.0f,
            0.0f,
            vk::BorderColor::eIntOpaqueBlack,
            VK_FALSE);
        try
        {
            textureSampler = device.createSampler(samplerInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    vk::ImageView createImageView(vk::Image image, vk::ImageViewType type, vk::Format format, vk::ImageAspectFlags aspectFlags)
    {
        vk::ImageViewCreateInfo viewInfo({}, image, type, format, {}, vk::ImageSubresourceRange(aspectFlags, 0, 1, 0, 1));
        vk::ImageView imageView;
        try
        {
            imageView = device.createImageView(viewInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
        return imageView;
    }

    void createImage(vk::Image &image, VmaAllocation &imageAllocation, vk::ImageUsageFlags imageUsage, VmaMemoryUsage memoryUsage, vk::ImageType type, uint32_t width, uint32_t height, uint32_t depth, vk::Format format, vk::ImageTiling tiling)
    {
        vk::ImageCreateInfo imageInfo({}, type, format, vk::Extent3D{width, height, depth}, 1, 1, vk::SampleCountFlagBits::e1, tiling, imageUsage, vk::SharingMode::eExclusive, {}, {}, vk::ImageLayout::eUndefined);
        VmaAllocationCreateInfo allocInfoImage = {};
        allocInfoImage.usage = memoryUsage;
        if (vmaCreateImage(allocator, reinterpret_cast<VkImageCreateInfo *>(&imageInfo), &allocInfoImage, reinterpret_cast<VkImage *>(&image), &imageAllocation, nullptr) != VK_SUCCESS)
            throw std::runtime_error("failed to create image!");
    }

    void transitionImageLayout(vk::Image image, vk::Format format, vk::ImageLayout oldLayout, vk::ImageLayout newLayout)
    {
        vk::CommandBuffer commandBuffer = beginSingleTimeCommands();
        vk::PipelineStageFlags sourceStage;
        vk::PipelineStageFlags destinationStage;
        vk::AccessFlags srcAccessMask = {};
        vk::AccessFlags dstAccessMask = {};

        if (oldLayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eTransferDstOptimal)
        {
            srcAccessMask = vk::AccessFlagBits::eNoneKHR;
            dstAccessMask = vk::AccessFlagBits::eTransferWrite;
            sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
            destinationStage = vk::PipelineStageFlagBits::eTransfer;
        }
        else if (oldLayout == vk::ImageLayout::eTransferDstOptimal && newLayout == vk::ImageLayout::eShaderReadOnlyOptimal)
        {
            srcAccessMask = vk::AccessFlagBits::eTransferWrite;
            dstAccessMask = vk::AccessFlagBits::eShaderRead;
            sourceStage = vk::PipelineStageFlagBits::eTransfer;
            destinationStage = vk::PipelineStageFlagBits::eFragmentShader;
        }
        else
        {
            throw std::invalid_argument("unsupported layout transition!");
        }

        vk::ImageMemoryBarrier barrier(srcAccessMask, dstAccessMask, oldLayout, newLayout, VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, image, vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));

        commandBuffer.pipelineBarrier(sourceStage, destinationStage, {}, {}, {}, {}, {}, 1, &barrier);

        endSingleTimeCommands(commandBuffer);
    }

    void copyBufferToImage(vk::Buffer buffer, vk::Image image, uint32_t width, uint32_t height, uint32_t depth)
    {
        vk::CommandBuffer commandBuffer = beginSingleTimeCommands();

        vk::BufferImageCopy region(0, 0, 0, vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 0, 0, 1), {0, 0, 0}, vk::Extent3D{width, height, depth});

        commandBuffer.copyBufferToImage(buffer, image, vk::ImageLayout::eTransferDstOptimal, 1, &region);

        endSingleTimeCommands(commandBuffer);
    }

    vk::CommandBuffer beginSingleTimeCommands()
    {
        vk::CommandBufferAllocateInfo allocInfo(commandPool, vk::CommandBufferLevel::ePrimary, 1);
        vk::CommandBuffer commandBuffer;
        try
        {
            commandBuffer = device.allocateCommandBuffers(allocInfo)[0];
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }

        vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

        try
        {
            commandBuffer.begin(beginInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
        return commandBuffer;
    }

    void endSingleTimeCommands(vk::CommandBuffer commandBuffer)
    {
        try
        {
            commandBuffer.end();
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }

        vk::SubmitInfo submitInfoCopy({}, {}, commandBuffer, {});
        graphicsQueue.submit(submitInfoCopy, {});
        graphicsQueue.waitIdle();
        device.freeCommandBuffers(commandPool, 1, &commandBuffer);
    }

    void createVertexBuffer()
    {
        vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        Buffer stagingBuffer = Buffer(bufferSize, vk::BufferUsageFlagBits::eTransferSrc, VMA_MEMORY_USAGE_CPU_ONLY);
        stagingBuffer.map();
        stagingBuffer.copyTo(vertices.data());
        stagingBuffer.unmap();

        vertexBuffer = new Buffer(&stagingBuffer, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, VMA_MEMORY_USAGE_GPU_ONLY);
    }

    void createIndexBuffer()
    {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

        Buffer stagingBuffer = Buffer(bufferSize, vk::BufferUsageFlagBits::eTransferSrc, VMA_MEMORY_USAGE_CPU_ONLY);
        stagingBuffer.map();
        stagingBuffer.copyTo(indices.data());
        stagingBuffer.unmap();

        indexBuffer = new Buffer(&stagingBuffer, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer, VMA_MEMORY_USAGE_GPU_ONLY);
    }

    void createUniformBuffers()
    {
        vk::DeviceSize bufferSize = sizeof(UniformBufferObject);

        uniformBuffers.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++)
        {
            uniformBuffers[i] = new Buffer(bufferSize, vk::BufferUsageFlagBits::eUniformBuffer, VMA_MEMORY_USAGE_CPU_TO_GPU);
        }
    }

    void createDescriptorPool()
    {
        vk::DescriptorPoolSize poolSizeUbo(vk::DescriptorType::eUniformBuffer, static_cast<uint32_t>(swapChainImages.size()));
        vk::DescriptorPoolSize poolSizeSampler(vk::DescriptorType::eCombinedImageSampler, static_cast<uint32_t>(swapChainImages.size()));
        std::array<vk::DescriptorPoolSize, 2> poolSizes{poolSizeUbo, poolSizeSampler};

        vk::DescriptorPoolCreateInfo poolInfo({}, static_cast<uint32_t>(swapChainImages.size()), poolSizes);
        try
        {
            descriptorPool = device.createDescriptorPool(poolInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void createDescriptorSets()
    {
        std::vector<vk::DescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
        vk::DescriptorSetAllocateInfo allocInfo(descriptorPool, static_cast<uint32_t>(swapChainImages.size()), layouts.data());
        descriptorSets.resize(swapChainImages.size());
        try
        {
            descriptorSets = device.allocateDescriptorSets(allocInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }

        for (size_t i = 0; i < swapChainImages.size(); i++)
        {

            vk::DescriptorBufferInfo bufferInfo(uniformBuffers[i]->getHandle(), 0, sizeof(UniformBufferObject));
            vk::DescriptorImageInfo imageInfo(textureSampler, textureImageView, vk::ImageLayout::eShaderReadOnlyOptimal);

            vk::WriteDescriptorSet descriptorWriteUbo(descriptorSets[i], 0, 0, 1, vk::DescriptorType::eUniformBuffer, {}, &bufferInfo);
            vk::WriteDescriptorSet descriptorWriteSampler(descriptorSets[i], 1, 0, 1, vk::DescriptorType::eCombinedImageSampler, &imageInfo);

            std::array<vk::WriteDescriptorSet, 2> descriptorWrites{descriptorWriteUbo, descriptorWriteSampler};

            device.updateDescriptorSets(descriptorWrites, nullptr);
        }
    }

    void createCommandBuffers()
    {
        commandBuffers.resize(swapChainFramebuffers.size());
        vk::CommandBufferAllocateInfo allocInfo(commandPool, vk::CommandBufferLevel::ePrimary, (uint32_t)commandBuffers.size());
        try
        {
            commandBuffers = device.allocateCommandBuffers(allocInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }

        for (size_t i = 0; i < commandBuffers.size(); i++)
        {
            vk::CommandBufferBeginInfo beginInfo;
            try
            {
                commandBuffers[i].begin(beginInfo);
            }
            catch (std::exception &e)
            {
                std::cerr << "Exception Thrown: " << e.what();
            }
            std::array<vk::ClearValue, 2> clearValues{
                vk::ClearValue(vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f})),
                vk::ClearValue(vk::ClearDepthStencilValue(1.0f, 0))};
            vk::RenderPassBeginInfo renderPassInfo(renderPass, swapChainFramebuffers[i], vk::Rect2D({0, 0}, swapChainExtent), clearValues);

            commandBuffers[i].beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);
            commandBuffers[i].bindPipeline(vk::PipelineBindPoint::eGraphics, graphicsPipeline);
            std::vector<vk::Buffer> vertexBuffers = {vertexBuffer->getHandle()};
            std::vector<vk::DeviceSize> offsets = {0};
            commandBuffers[i].bindVertexBuffers(0, vertexBuffers, offsets);
            commandBuffers[i].bindIndexBuffer(indexBuffer->getHandle(), 0, vk::IndexType::eUint32);
            commandBuffers[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);
            commandBuffers[i].drawIndexed(static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
            commandBuffers[i].endRenderPass();
            try
            {
                commandBuffers[i].end();
            }
            catch (std::exception &e)
            {
                std::cerr << "Exception Thrown: " << e.what();
            }
        }
    }

    void createSyncObjects()
    {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);
        vk::SemaphoreCreateInfo semaphoreInfo;
        vk::FenceCreateInfo fenceInfo(vk::FenceCreateFlagBits::eSignaled);
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
            try
            {
                imageAvailableSemaphores[i] = device.createSemaphore(semaphoreInfo);
                renderFinishedSemaphores[i] = device.createSemaphore(semaphoreInfo);
                inFlightFences[i] = device.createFence(fenceInfo);
            }
            catch (std::exception &e)
            {
                std::cerr << "Exception Thrown: " << e.what();
            }
        }
    }

    void updateUniformBuffer(uint32_t currentImage)
    {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};
        ubo.model = glm::scale(glm::rotate(glm::mat4(1.0f), time * 0.2f * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), textureScale);
        // ubo.view = glm::lookAt(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // ubo.proj = glm::ortho(((float)swapChainExtent.width / (float)swapChainExtent.height)/1.8f, -((float)swapChainExtent.width / (float)swapChainExtent.height) / 1.8f, -0.55f, 0.55f, -1.f, 1.f);
        // ubo.proj[1][1] *= -1;
        ubo.view = glm::lookAt(glm::vec3(0.7f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);
        ubo.proj[1][1] *= -1;
        ubo.size = glm::vec2((float)swapChainExtent.width, (float)swapChainExtent.height);

        uniformBuffers[currentImage]->map();
        uniformBuffers[currentImage]->copyTo(&ubo);
        uniformBuffers[currentImage]->flush();
        uniformBuffers[currentImage]->unmap();
    }

    void drawFrame()
    {
        vk::Result result1 = device.waitForFences(inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
        uint32_t imageIndex;
        vk::Result result = device.acquireNextImageKHR(swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        if (result == vk::Result::eErrorOutOfDateKHR)
        {
            recreateSwapChain();
            return;
        }
        else if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
            throw std::runtime_error("failed to acquire swap chain image!");

        updateUniformBuffer(imageIndex);
        recordCommandBuffer(imageIndex);

        if ((VkFence)imagesInFlight[imageIndex] != VK_NULL_HANDLE)
            vk::Result result2 = device.waitForFences(imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        imagesInFlight[imageIndex] = inFlightFences[currentFrame];

        std::vector<vk::Semaphore> waitSemaphores = {imageAvailableSemaphores[currentFrame]};
        std::vector<vk::PipelineStageFlags> waitStages = {vk::PipelineStageFlagBits::eColorAttachmentOutput};
        std::vector<vk::Semaphore> signalSemaphores = {renderFinishedSemaphores[currentFrame]};
        std::array<vk::CommandBuffer, 2> submitCommandBuffers = {commandBuffers[imageIndex], commandBuffersImgui[imageIndex]};

        vk::SubmitInfo submitInfo(waitSemaphores, waitStages, submitCommandBuffers, signalSemaphores);
        device.resetFences(inFlightFences[currentFrame]);
        graphicsQueue.submit(submitInfo, inFlightFences[currentFrame]);

        std::vector<vk::SwapchainKHR> swapChains = {swapChain};
        vk::PresentInfoKHR presentInfo(signalSemaphores, swapChains, imageIndex);
        result = presentQueue.presentKHR(presentInfo);
        if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR || framebufferResized)
        {
            framebufferResized = false;
            recreateSwapChain();
        }
        else if (result != vk::Result::eSuccess)
            throw std::runtime_error("queue Present failed!");
        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void recordCommandBuffer(uint32_t imageIndex)
    {
        vk::CommandBufferBeginInfo beginInfo;
        try
        {
            commandBuffersImgui[imageIndex].begin(beginInfo);
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
        std::array<vk::ClearValue, 1> clearValues{
            vk::ClearValue(vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f}))};
        vk::RenderPassBeginInfo renderPassInfo(renderPassImgui, framebuffersImgui[imageIndex], vk::Rect2D({0, 0}, swapChainExtent), clearValues);

        commandBuffersImgui[imageIndex].beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);

        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffersImgui[imageIndex]);

        commandBuffersImgui[imageIndex].endRenderPass();
        try
        {
            commandBuffersImgui[imageIndex].end();
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception Thrown: " << e.what();
        }
    }

    void mainLoop()
    {
        double time = glfwGetTime();
        uint32_t fps = 0;
        bool show_demo_window = true;
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::ShowDemoWindow(&show_demo_window);
            ImGui::Render();

            drawFrame();

            fps++;
            if ((glfwGetTime() - time) >= 1.0)
            {
                time = glfwGetTime();
                std::string title = "VulkanBase  FPS:" + std::to_string(fps);
                glfwSetWindowTitle(window, title.c_str());
                fps = 0;
            }
        }
        device.waitIdle();
    }

    void cleanupSwapchain()
    {
        device.destroyImageView(depthImageView);
        vmaDestroyImage(allocator, depthImage, depthImageAllocation);
        for (auto framebuffer : swapChainFramebuffers)
        {
            device.destroyFramebuffer(framebuffer);
        }
        //imgui
        for (auto framebuffer : framebuffersImgui)
        {
            device.destroyFramebuffer(framebuffer);
        }
        //imgui
        device.freeCommandBuffers(commandPool, commandBuffers);
        device.destroyPipeline(graphicsPipeline);
        device.destroyPipelineLayout(pipelineLayout);
        device.destroyRenderPass(renderPass);
        for (auto imageView : swapChainImageViews)
        {
            device.destroyImageView(imageView);
        }
        device.destroySwapchainKHR(swapChain);
        for (size_t i = 0; i < swapChainImages.size(); i++)
        {
            delete uniformBuffers[i];
        }
        device.destroyDescriptorPool(descriptorPool);
    }

    void cleanup()
    {
        cleanupSwapchain();
        //imgui
        device.freeCommandBuffers(commandPoolImgui, commandBuffersImgui);
        device.destroyRenderPass(renderPassImgui);
        device.destroyDescriptorPool(descriptorPoolImgui);
        //imgui

        device.destroyShaderModule(fragShaderModule);
        device.destroyShaderModule(vertShaderModule);
        device.destroySampler(textureSampler);
        device.destroyImageView(textureImageView);
        vmaDestroyImage(allocator, textureImage, textureImageAllocation);
        device.destroyDescriptorSetLayout(descriptorSetLayout);

        delete indexBuffer;
        delete vertexBuffer;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
            device.destroySemaphore(imageAvailableSemaphores[i]);
            device.destroySemaphore(renderFinishedSemaphores[i]);
            device.destroyFence(inFlightFences[i]);
        }
        device.destroyCommandPool(commandPool);
        //imgui
        device.destroyCommandPool(commandPoolImgui);
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        //imgui
        vmaDestroyAllocator(allocator);
        device.destroy();
        if (enableValidation)
        {
            instance.destroyDebugUtilsMessengerEXT(debugMessenger);
        }
        instance.destroySurfaceKHR(surface);
        instance.destroy();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void recreateSwapChain()
    {
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        while (width == 0 || height == 0)
        {
            glfwGetFramebufferSize(window, &width, &height);
            glfwWaitEvents();
        }

        device.waitIdle();

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

        recreateImGuiFramebuffer();
    }

    static void framebufferResizeCallback(GLFWwindow *window, int width, int height)
    {
        auto app = reinterpret_cast<VulkanBase *>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }
};

int main()
{

    VulkanBase app;
    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}