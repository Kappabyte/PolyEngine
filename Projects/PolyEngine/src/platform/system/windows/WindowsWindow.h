//
// Created by avery on 2022-09-16.
//

#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "poly/core/Window.h"
#include "platform/api/gl/shader/GLShader.h"

namespace Poly::Windows {
    class WindowsWindow: public Poly::Window {
    public:
        explicit WindowsWindow(NamespaceID identifier, Poly::WindowProps props);
        ~WindowsWindow() override;

        void init() override;
        void update() override;
        void shutdown() override;
    private:
        GLFWwindow* window = nullptr;
        GL::GLShader* shader;
    };
}
