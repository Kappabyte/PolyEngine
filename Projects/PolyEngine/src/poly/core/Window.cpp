//
// Created by avery on 2022-09-16.
//

#include <stdexcept>
#include <iostream>
#include "Window.h"
#include "platform/system/windows/WindowsWindow.h"
#include "poly/util/NamespaceID.h"
#include "Application.h"

namespace Poly {
    Window* Window::create(NamespaceID identifier, WindowProps props) {
        #if defined(Poly_Platform_Windows)
            return new Windows::WindowsWindow(identifier, props);
        #elif defined(Poly_Platform_Linux)
            return new LinuxWindow(props);
        #elif defined(Poly_Platform_MacOS)
            return new MacOSWindow(props);
        #else
            throw std::runtime_error("Unsupported platform");
        #endif
    }

    Window::Window(NamespaceID identifier, Poly::WindowProps& props): identifier(identifier), props(props) {}

    void Window::start() {
        thread = std::thread(&Window::i_start, this);

        // Wait for the window to initialize
        while(state != WindowState::INITIALIZED) {}
    }

    void Window::close() {
        state = WindowState::CLOSED;
        thread.join();
        Application::get()->removeWindow(identifier);
    }

    void Window::i_start() {
        init();
        state = WindowState::INITIALIZED;
        while(state == WindowState::INITIALIZED) {
            update();
        }
        shutdown();
        std::cout << "Window " << identifier.toString() << " closed" << std::endl;
    }

    WindowState Window::getState() {
        return state;
    }
} // Poly