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
            queueMutex.lock();
            auto qit = eventQueues.begin();
            while(qit != eventQueues.end()) {
                qit->second->dispatchEvents(this);
                qit++;
            }
            queueMutex.unlock();

            children = getLayers();
            it = children.begin();
            while(it != children.end()) {
                it->second->update();
                it++;
            }

            if(windows.empty()) {
                state = ApplicationState::STOPPED;
            }
            std::cout << "MAIN: Arrived" << std::endl;
            sync_point.arrive_and_wait();
            std::cout << "MAIN: Proceeding" << std::endl;
        }
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
        Window* window = Window::create(identifier, std::move(props));
        windows.insert({identifier, window});
        if(state == ApplicationState::RUNNING) window->start();
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
        getWindow(event->identifier)->close();
    }

    void Application::removeWindow(const NamespaceID id) {
        if(windows.find(id) == windows.end()) {
            throw std::runtime_error("Window does not exist");
        }

        if(windows[id]->getState() == WindowState::INITIALIZED) {
            windows[id]->close();
        }
        delete windows[id];
        windows.erase(id);
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