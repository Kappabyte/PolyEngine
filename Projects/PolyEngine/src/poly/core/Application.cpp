#include <stdexcept>
#include <iostream>
#include "Application.h"

namespace Poly {

    Application* Application::instance = nullptr;

    Application::Application() {}

    Application *Application::get() {
        if(Application::instance == nullptr) {
            Application::instance = new Application();
        }

        return Application::instance;
    }

    void Application::start() {
        auto children = getLayers();
        auto it = children.begin();
        while(it != children.end()) {
            it->second->init();
            it++;
        }
        while(isRunning) {
            while(queue.getQueueSize() > 0) {
                auto event = queue.popQueue();
                dispatch(event.first, event.second);
            }

            children = getLayers();
            it = children.begin();
            while(it != children.end()) {
                it->second->update();
                it++;
            }
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

    EventQueue* Application::getEventQueue() {
        return &queue;
    }
}