#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "poly/core/Window.h"
#include "platform/api/gl/shader/GLShader.h"

namespace Poly::Windows {
    class WindowsWindow: public Poly::Window {
    public:
        explicit WindowsWindow(NamespaceId identifier, Poly::WindowProps props);
        ~WindowsWindow() override;

        void init() override;
        void update() override;
        void shutdown() override;

        static void platformInit();

    private:
        GLFWwindow* m_window = nullptr;

        static std::mutex m_mutex;
    };
}
