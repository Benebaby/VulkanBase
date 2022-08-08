#include "Instance.hpp"
#include "Window.hpp"
namespace VBF
{
    class Surface
    {
    private:
        vk::SurfaceKHR m_surface;
        VBF::Instance* m_instance;
    public:
        Surface(VBF::Instance* instance, VBF::Window* window);
        ~Surface();

        vk::SurfaceKHR* getSurfaceKHR() { return &m_surface; }
    };

    Surface::Surface(VBF::Instance* instance, VBF::Window* window)
    {
        m_instance = instance;
        if (glfwCreateWindowSurface(*instance->getVkInstance(), window->getGLFWwindow(), nullptr, reinterpret_cast<VkSurfaceKHR*>(&m_surface)) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    Surface::~Surface()
    {
        m_instance->getVkInstance()->destroySurfaceKHR(m_surface);
    }

}