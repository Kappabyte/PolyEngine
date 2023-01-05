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
            return new LinuxWindow(m_props);
        #elif defined(Poly_Platform_MacOS)
            return new MacOSWindow(m_props);
        #else
            throw std::runtime_error("Unsupported platform");
        #endif
    }

    Window::Window(NamespaceID identifier, Poly::WindowProps& props): identifier(identifier), m_props(props) {}

    void Window::start() {
        m_thread = std::thread(&Window::i_start, this);
    }

    void Window::i_start() {
        init();
        m_state = WindowState::INITIALIZING;

        while(true) {
            update();
            if(m_shouldClose) {
                break;
            }
        }
        shutdown();
        std::cout << "Window " << identifier.toString() << " closed" << std::endl;
        setState(WindowState::CLOSED);
    }

    WindowState Window::getState() {
        return m_state;
    }

    void Window::setState(WindowState state) {
        m_stateMutex.lock();
        this->m_state = state;
        m_stateMutex.unlock();
    }

    void Window::setShouldClose(bool shouldClose) {
        m_stateMutex.lock();
        this->m_shouldClose = shouldClose;
        m_stateMutex.unlock();
    }
} // Poly