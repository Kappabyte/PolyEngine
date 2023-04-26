#include <stdexcept>
#include <iostream>
#include <utility>
#include "Window.h"
#include "platform/system/windows/WindowsWindow.h"
#include "poly/util/NamespaceId.h"

namespace Poly {
    Window* Window::create(NamespaceId identifier, WindowProps props) {
        #if defined(Poly_Platform_Windows)
            return new Windows::WindowsWindow(std::move(identifier), std::move(props));
        #elif defined(Poly_Platform_Linux)
            return new LinuxWindow(m_props);
        #elif defined(Poly_Platform_MacOS)
            return new MacOSWindow(m_props);
        #else
            throw std::runtime_error("Unsupported platform");
        #endif
    }

    Window::Window(NamespaceId identifier, Poly::WindowProps& props): m_identifier(std::move(identifier)), m_props(props) {}

    void Window::start() {
        m_thread = std::thread(&Window::i_start, this);
    }

    void Window::i_start() {
        init();
        m_state = WindowState::INITIALIZING;

        while(true) {
            setState(WindowState::UPDATING);

            update();

            if(m_state == WindowState::UPDATING) {
                setState(WindowState::IDLE);
            }

            // Wait for the next update
            while(m_state == WindowState::IDLE && !m_shouldClose) {
            }

            if(m_shouldClose) {
                break;
            }
        }
        shutdown();
        std::cout << "Window " << m_identifier.toString() << " closed" << std::endl;
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

    void Window::initializePlatform() {
        #if defined(Poly_Platform_Windows)
        Windows::WindowsWindow::platformInit();
        #endif
    }
} // Poly