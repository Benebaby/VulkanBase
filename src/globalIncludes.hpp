#pragma once

#define VMA_IMPLEMENTATION

#ifdef _WIN32
    #include <windows.h>
#endif
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vk_mem_alloc.h>