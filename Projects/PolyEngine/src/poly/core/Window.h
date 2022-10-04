//
// Created by avery on 2022-09-16.
//

#pragma once

#include <thread>
#include "poly/events/EventQueue.h"
#include "poly/events/EventNodeBase.h"
#include "poly/util/NamespaceID.h"
#include "poly/render/RenderTarget.h"

namespace Poly {

    struct WindowProps {
        std::string title = "PolyEngine";
        bool fullscreen = false;
        bool vsync = false;
        uint16_t width = 800;
        uint16_t height = 600;
    };

    enum class WindowState {
        CLOSED,
        INITIALIZED
    };

    class Window : public RenderTarget {
    public:
        /**
         * Create a window
         * @param identifier The window identifier
         * @param props The window properties.
         * @return Te created window.
         */
        static Window* create(NamespaceID identifier, WindowProps props = WindowProps());
        virtual ~Window() = default;

        /**
         * Open the window and start rendering everything in the render queue.
         */
        void start();
        /**
         * Close the window.
         */
        void close();

        /**
         * Get the state of the window
         * @return The window state
         */
        WindowState getState();

    protected:
        Window(NamespaceID identifier, WindowProps& props);

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void shutdown() = 0;
    private:
        void i_start();
    public:
        const NamespaceID identifier;
    protected:
        WindowProps props;
    private:
        std::thread thread;

        WindowState state = WindowState::CLOSED;
    };

} // Poly
