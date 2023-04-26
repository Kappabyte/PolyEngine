#include <stdexcept>
#include <utility>
#include "Application.h"

std::string banner = R"(
@           _____      _
@@          |  __ \    | |
@@@         | |__) |__ | |_   _
@@@@        |  ___/ _ \| | | | |
@@@@@       | |  | (_) | | |_| |
@@@@@@      |_|___\___/|_|\__, |_
@@@@@@@     |  ____|       __/ (_)
@@@@@@@@    | |__   _ __  |___/ _ _ __   ___
@@@@@@@@@   |  __| | '_ \ / _` | | '_ \ / _ \
@@@@@@@@@@  | |____| | | | (_| | | | | |  __/
@@@@@@@     |______|_| |_|\__, |_|_| |_|\___|
@@@@                       __/ |
@                         |___/

)";

namespace Poly {

    Application* Application::m_instance = nullptr;

    Application::Application() {
        addResultListener<WindowCloseEvent>(this, 0);
    }

    Application *Application::get() {
        if(Application::m_instance == nullptr) {
            Application::m_instance = new Application();
        }

        return Application::m_instance;
    }

    void Application::start() {
        m_state = ApplicationState::RUNNING;
    
        std::cout << banner << std::endl;
        LOG_INFO("Version: {}", "dev");
#ifdef Poly_Platform_Windows
        LOG_INFO("System: {}", "Microsoft Windows");
#endif
#ifdef Poly_Platform_Linux
        LOG_INFO("System: {}", "Linux");
#endif
    
        LOG_INFO("API: {}", "OpenGL");

        Window::initializePlatform();

        //Initialize Windows
        for(auto window : m_windows) {
            window.second->start();
        }

        //Initialize Layers
        auto layers = getLayers();
        for(auto layer : layers) {
            layer.second->init();
        }

        while(m_state == ApplicationState::RUNNING) {
            update();
        }
    }

    void Application::update() {
        // Execute the event queue
        for(auto eventQueue : m_eventQueues) {
            eventQueue.second->dispatchEvents(this);
        }

        // Update the window states
        for(auto window = std::begin(m_windows); window != std::end(m_windows);) {
            // If a window is marked as closed, remove the window from the list of windows
            if(window->second->getState() == WindowState::CLOSED) {
                window = m_windows.erase(window);
                continue;
            }

            // If a window is waiting, allow it to update
            if(window->second->getState() == WindowState::IDLE) {
                window->second->setState(WindowState::UPDATING);
            }
            window++;
        }

        auto layers = getLayers();
        for(auto layer : layers) {
            layer.second->update();
        }

        // Wait for all the windows to update
        for(auto& window : m_windows) {
            while(window.second->getState() != WindowState::IDLE && window.second->getState() != WindowState::CLOSED) {}
        }

        // If there are no more windows, close the application
        if(m_windows.empty()) {
            m_state = ApplicationState::STOPPED;
        }
    }

    EventChildren Application::getEventNodeChildren() {
        EventChildren children = {};
        auto layers = getLayers();
        for(auto layer : layers) {
            children.insert(layer);
        }
        return children;
    }

    Window* Application::addWindow(const NamespaceId& identifier) {
        return addWindow(identifier, WindowProps({identifier.toString()}));
    }

    Window* Application::addWindow(const NamespaceId& identifier, WindowProps props) {
        std::unique_lock lk(m_eventQueueMutex);
        Window* window = Window::create(identifier, std::move(props));
        m_windows.insert({identifier, window});
        if(m_state == ApplicationState::RUNNING) window->start();
        return window;
    }

    Window* Application::getWindow(const NamespaceId& identifier) {
        if(m_windows.find(identifier) != m_windows.end()) {
            return m_windows.at(identifier);
        } else {
            return nullptr;
        }
    }

    void Application::handleResult(WindowCloseEvent *event, bool &handled) {
        if(event->isCancelled()) return;

        if(m_windows.find(event->m_identifier) == m_windows.end()) {
            throw std::runtime_error("Window does not exist");
        }

        handled = true;
        removeWindow(event->m_identifier);
    }

    void Application::removeWindow(const NamespaceId& id) {
        if(m_windows.find(id) == m_windows.end()) {
            throw std::runtime_error("Window does not exist");
        }

        m_windows[id]->setShouldClose(true);
    }

    void Application::setApi(RenderAPI api) {
        if(m_state == ApplicationState::RUNNING) {
        }
        this->m_graphicsApi = api;
    }

    RenderAPI Application::getApi() {
        return this->m_graphicsApi;
    }
}