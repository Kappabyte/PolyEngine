#pragma once

#include "poly/events/EventQueue.h"
#include "poly/events/EventNodeBase.h"
#include "LayerStack.h"

namespace Poly {
    class Application: private IEventNode, public LayerStack {
    public:
        /**
         * Get the application. If the application does not uet exist, it will be created.
         * @return The application
         */
        static Application* get();

        [[noreturn]] void start();

        EventChildren getEventNodeChildren() override;

        EventQueue* getEventQueue();
    private:
        Application();
    private:
        static Application* instance;

        EventQueue queue = EventQueue();

        bool isRunning = true;
    };
}
