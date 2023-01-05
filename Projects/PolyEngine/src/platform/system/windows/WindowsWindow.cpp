//
// Created by avery on 2022-09-16.
//
#include <iostream>
#include <utility>

#include "WindowsWindow.h"
#include "poly/core/Application.h"
#include "poly/render/Buffer.h"
#include "poly/render/RenderCommand.h"
#include "glm/vec4.hpp"
#include "poly/render/geometry/Geometry.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

namespace Poly::Windows {
    WindowsWindow::WindowsWindow(NamespaceID identifier, Poly::WindowProps props): Poly::Window(std::move(identifier), props) {}
    WindowsWindow::~WindowsWindow() {
    }
    void WindowsWindow::init() {
        std::cout << "Creating window: " << m_props.title << std::endl;
        if(!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwSetErrorCallback(error_callback);
        window = glfwCreateWindow(m_props.width, m_props.height, m_props.title.c_str(), nullptr, nullptr);
        if(!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        std::cout << "Created window: " << m_props.title << std::endl;

        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        std::cout << "Loaded GL" << std::endl;
        std::cout << glfwGetVersionString() << std::endl;

        glfwSwapInterval(1);

        shader = Shader::create("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    }

    void WindowsWindow::update() {
        setState(WindowState::UPDATING);

        unsigned int indices[] = {
                0, 1, 2,
                1,2,3
        };

        glfwSwapBuffers(window);
        while(!getRenderQueueEmpty()) {
            RenderCommand command = pop();
            switch(command.type) {
                case RenderCommandType::SET_CLEAR_COLOUR:
                    {
                        auto colour = (glm::vec4 *) command.data;
                        RenderCommandExecutor::setClearColor(colour->r, colour->g, colour->b, colour->a);
                        delete colour;
                    }
                    break;
                case RenderCommandType::CLEAR:
                    {
                        RenderCommandExecutor::clear(true, true);
                    }
                    break;
                case RenderCommandType::DRAW_INDEXED:
                    {
                        auto data = (GeometryData*) command.data;
                        data->material = MakeShared<Material>(shader);
                        Geometry geometry = Geometry(*data);
                        geometry.getVertexArray()->bind();
                        Shared<IndexBuffer> ibo = IndexBuffer::create();
                        ibo->bind();
                        ibo->data(indices, sizeof(indices));
                        RenderCommandExecutor::drawIndexed();
                        delete data;
                    }
                    break;
            }
        }
        glfwPollEvents();

        if(glfwWindowShouldClose(window) == GLFW_TRUE) {
            //TODO: Window should not be accessing the application
            Application::get()->getEventQueue<WindowCloseEvent>()->addToQueue(new WindowCloseEvent(identifier));
            glfwSetWindowShouldClose(window, GLFW_FALSE);
        }

        if(getState() == WindowState::UPDATING) {
            setState(WindowState::IDLE);
        }

        // Wait for the next update
        while(getState() == WindowState::IDLE) {
            if(m_shouldClose) {
                return;
            }
        }
    }

    void WindowsWindow::shutdown() {
        glfwDestroyWindow(window);
    }
}