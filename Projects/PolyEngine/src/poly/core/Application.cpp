#include <stdexcept>
#include <utility>
#include "Application.h"

namespace Poly {

    Application* Application::instance = nullptr;

    Application::Application() {
        addResultListener<WindowCloseEvent>(this, 0);
    };

    Application *Application::get() {
        if(Application::instance == nullptr) {
            Application::instance = new Application();
        }

        return Application::instance;
    }

    void Application::start() {
        state = ApplicationState::RUNNING;

        //Initialize Windows
        auto it2 = windows.begin();
        while(it2 != windows.end()) {
            it2->second->start();
            it2++;
        }

        //Initialize Layers
        auto children = getLayers();
        auto it = children.begin();
        while(it != children.end()) {
            it->second->init();
            it++;
        }

        while(state == ApplicationState::RUNNING) {
            mutex.lock();
            auto qit = eventQueues.begin();
            while(qit != eventQueues.end()) {
                qit->second->dispatchEvents(this);
                qit++;
            }
            mutex.unlock();

            for(auto window = std::begin(windows); window != std::end(windows);) {
                if(window->second->getState() == WindowState::CLOSED) {
                    window = windows.erase(window);
                    continue;
                }
                if(window->second->getState() == WindowState::IDLE) {
                    window->second->setState(WindowState::UPDATING);
                }
                window++;
            }

            children = getLayers();
            it = children.begin();
            while(it != children.end()) {
                it->second->update();
                it++;
            }

            mutex.lock();
            if(windows.empty()) {
                state = ApplicationState::STOPPED;
            }
            mutex.unlock();

            // Wait for all windows to be done updating
            for(auto& window : windows) {
                while(window.second->getState() != WindowState::IDLE && window.second->getState() != WindowState::CLOSED) {}
            }
            if(windows.empty()) {
                state = ApplicationState::STOPPED;
            }
        }
        std::cout << "Application stopped" << std::endl;
    }

    EventChildren Application::getEventNodeChildren() {
        EventChildren children = {};
        auto layers = getLayers();
        auto it = layers.begin();
        while(it != layers.end()) {
            children.insert(*it);
            it++;
        }
        return children;
    }

    Window* Application::addWindow(const NamespaceID& identifier) {
        return addWindow(identifier, WindowProps({identifier.toString()}));
    }

    Window* Application::addWindow(const NamespaceID& identifier, WindowProps props) {
        mutex.lock();
        Window* window = Window::create(identifier, std::move(props));
        windows.insert({identifier, window});
        if(state == ApplicationState::RUNNING) window->start();
        mutex.unlock();
        return window;
    }

    Window* Application::getWindow(const NamespaceID& identifier) {
        if(windows.find(identifier) != windows.end()) {
            return windows.at(identifier);
        } else {
            return nullptr;
        }
    }

    void Application::handleResult(WindowCloseEvent *event, bool &handled) {
        if(event->isCancelled()) return;

        if(windows.find(event->identifier) == windows.end()) {
            throw std::runtime_error("Window does not exist");
        }

        handled = true;
        removeWindow(event->identifier);
    }

    void Application::removeWindow(const NamespaceID& id) {
        if(windows.find(id) == windows.end()) {
            throw std::runtime_error("Window does not exist");
        }

        windows[id]->setShouldClose(true);
    }

    void Application::setAPI(API api) {
        if(state == ApplicationState::RUNNING) {
        }
        this->graphicsAPI = api;
    }

    API Application::getAPI() {
        return this->graphicsAPI;
    }
}