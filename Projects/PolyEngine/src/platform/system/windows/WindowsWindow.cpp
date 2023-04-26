#include <utility>

#include "WindowsWindow.h"
#include "poly/core/Application.h"
#include "poly/render/Buffer.h"
#include "poly/render/RenderCommand.h"
#include "glm/vec4.hpp"
#include "poly/render/geometry/Geometry.h"

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

namespace Poly::Windows {
    WindowsWindow::WindowsWindow(NamespaceId identifier, Poly::WindowProps props): Poly::Window(std::move(identifier), props) {}
    WindowsWindow::~WindowsWindow() = default;
    void WindowsWindow::init() {
        // Hack: sometimes crashes when all windows are created at once. Waiting for a window to finish fixes the issue.
        auto lock = std::unique_lock(m_mutex);
    
        m_window = glfwCreateWindow(m_props.m_width, m_props.m_height, m_props.m_title.c_str(), nullptr, nullptr);
        if(!m_window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(m_window);

        //TODO: Create Abstraction
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(m_props.m_vsync ? 1 : 0);
    }

    void WindowsWindow::update() {

        unsigned int indices[] = {
                0, 1, 2,
                1,2,3
        };

        glfwSwapBuffers(m_window);
        executeRenderCommandQueue();
        
        glfwPollEvents();

        if(glfwWindowShouldClose(m_window) == GLFW_TRUE) {
            Application::get()->getEventQueue<WindowCloseEvent>()->addToQueue(new WindowCloseEvent(m_identifier));
            glfwSetWindowShouldClose(m_window, GLFW_FALSE);
        }
    }

    void WindowsWindow::shutdown() {
        glfwDestroyWindow(m_window);
    }

    void WindowsWindow::platformInit() {
        if(!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwSetErrorCallback(errorCallback);
    }

    std::mutex WindowsWindow::m_mutex = std::mutex();
}