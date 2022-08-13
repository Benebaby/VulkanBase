#pragma once
#include "globalDefs.hpp"
#include "globalIncludes.hpp"
#include "Device.hpp"

namespace VBF
{
    struct Allocator
    {
        VmaAllocator allocator;

        Allocator(VBF::Instance* instance, VBF::GPU* gpu, VBF::Device* device)
        {
            VmaAllocatorCreateInfo allocatorInfo = {};
            allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_2;
            allocatorInfo.physicalDevice = *gpu->getPhysicalDevice();
            allocatorInfo.device = *device->getVkDevice();
            allocatorInfo.instance = *instance->getVkInstance();
            
            if(vmaCreateAllocator(&allocatorInfo, &allocator) != VK_SUCCESS)
                throw std::runtime_error("failed to create Allocator");
        }
        ~Allocator()
        {
            vmaDestroyAllocator(allocator);
        }

        operator VmaAllocator&(){ return allocator; }
    };
    
} // namespace VBF
