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

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

namespace Poly::Windows {
    WindowsWindow::WindowsWindow(NamespaceID identifier, Poly::WindowProps props): Poly::Window(std::move(identifier), props) {}
    WindowsWindow::~WindowsWindow() {
    }
    void WindowsWindow::init() {
        std::cout << "Creating window: " << props.title << std::endl;
        if(!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwSetErrorCallback(error_callback);
        window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
        if(!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        std::cout << "Created window: " << props.title << std::endl;

        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        std::cout << "Loaded GL" << std::endl;
        std::cout << glfwGetVersionString() << std::endl;

        glfwSwapInterval(1);

        shader = new GL::GLShader("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    }

    void WindowsWindow::update() {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << "OpenGL error: " << err << std::endl;
        }

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
                    break;
            }
        }
        glfwPollEvents();

        if(glfwWindowShouldClose(window) == GLFW_TRUE) {
            Application::get()->getEventQueue<WindowCloseEvent>()->addToQueue(new WindowCloseEvent(identifier));
            glfwSetWindowShouldClose(window, GLFW_FALSE);
        }
        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
                0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f
        };
        unsigned int indices[] = {
                0, 1, 2,
                1, 2, 3
        };

        shader->bind();
        Shared<VertexBufferArray> vao = VertexBufferArray::create();
        vao->bind();

        Shared<VertexBuffer> vbo = VertexBuffer::create();
        vbo->bind();
        vbo->data(vertices, sizeof(vertices));

        Shared<IndexBuffer> ibo = IndexBuffer::create();
        ibo->bind();
        ibo->data(indices, sizeof(indices));

        vbo->setLayout({
            {shader->getAttributeLocation("aPos"), ShaderType::FLOAT3, "aPos"},
            {shader->getAttributeLocation("aColor"), ShaderType::FLOAT3, "aColor"}
        });

        RenderCommandExecutor::drawIndexed();

        vao->unbind();

        shader->unbind();
        std::cout << identifier.toString() << ": Arrived" << std::endl;
        Application::get()->sync_point.arrive_and_wait();
        std::cout << identifier.toString() << ": Proceeding" << std::endl;
    }

    void WindowsWindow::shutdown() {
        delete shader;
        glfwDestroyWindow(window);
    }
}