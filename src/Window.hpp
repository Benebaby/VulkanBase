#include "globalDefs.hpp"
#include "globalIncludes.hpp"

namespace VBF
{

    class Window
    {
    private:
        GLFWwindow* m_window;
        bool m_resized;

        static void framebufferResizeCallback(GLFWwindow *window, int width, int height){
            auto w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
            w->setResized(true);
        };

    public:
        Window(uint32_t width, uint32_t height, std::string title);
        ~Window();
        
        GLFWwindow* getGLFWwindow(){ return m_window; };
        bool wasResized(){ return m_resized; }
        void setResized(bool resized){ m_resized = resized; }
    };

    Window::Window(uint32_t width, uint32_t height, std::string title)
    {
        m_resized = false;
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(m_window, this);
        glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
    }

    Window::~Window()
    {
    }  

  
}



