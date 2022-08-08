
#include "globalDefs.hpp"
#include "globalIncludes.hpp"
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
