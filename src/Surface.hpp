#pragma once
#include "Instance.hpp"
#include "Window.hpp"
namespace VBF
{
    class Surface
    {
    private:
        vk::SurfaceKHR m_surface;
        VBF::Instance* m_instance;
        VBF::Window* m_window;
    public:
        Surface(VBF::Instance* instance, VBF::Window* window);
        ~Surface();

        VBF::Window* getWindow() { return m_window; }

        vk::SurfaceKHR* getSurfaceKHR() { return &m_surface; }
    };

    Surface::Surface(VBF::Instance* instance, VBF::Window* window)
    {
        m_instance = instance;
        m_window = window;
        if (glfwCreateWindowSurface(*instance->getVkInstance(), window->getGLFWwindow(), nullptr, reinterpret_cast<VkSurfaceKHR*>(&m_surface)) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    Surface::~Surface()
    {
        m_instance->getVkInstance()->destroySurfaceKHR(m_surface);
    }

}