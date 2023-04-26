#pragma once

#include <barrier>
#include "poly/events/EventQueue.h"
#include "poly/events/EventNodeBase.h"
#include "LayerStack.h"
#include "Window.h"
#include "poly/events/window/WindowCloseEvent.h"
#include "poly/util/NamespaceId.h"
#include "poly/render/RenderBackend.h"

namespace Poly {

    enum class ApplicationState {
        RUNNING,
        STOPPED
    };

    class Application: private IEventNode, public LayerStack, private EventResultListener<WindowCloseEvent> {
    public:
        /**
         * Get the application. If the application does not uet exist, it will be created.
         * @return The application
         */
        static Application* get();

        /**
         * Start the application and open all registered windows.
         */
        void start();
        /**
         * Set the graphics API to be used
         * @param api The API to use
         */
        void setApi(RenderAPI api);

        /**
         * Get the graphics API
         * @return The Graphics API
         */
        RenderAPI getApi();

        /**
         * Add a window to the application
         * @param identifier The identifier of the window. Used to fetch the window at a later point.
         * @param props The properties of the created window.
         * @return The created window.
         */
        Window* addWindow(const NamespaceId& identifier, WindowProps props);
        /**
         * Add a window to the application with the default window properties.
         * @param identifier The identifier of the window. Used to fetch the window at a later point.
         * @return The created the window.
         */
        Window* addWindow(const NamespaceId& identifier);
        /**
         * Get a window based on the window identifier.
         * @param identifier The window identifier.
         * @return The window associated with the identifier, or nullptr if the window could not be found.
         */
        Window* getWindow(const NamespaceId& identifier);

        /**
         * Get an event queue of the specified type. Any events added to any of the queues will be executed on the root
         * event node at the start of each application update tick.
         * @tparam EventType The type of event to get the event queue for.
         * @return The event queue.
         */
        template <class EventType>
        EventQueue<EventType>* getEventQueue() {
            std::unique_lock lk(m_eventQueueMutex);
            if(m_eventQueues.find(TypeInfo(&typeid(EventType))) == m_eventQueues.end()) {
                EventQueueBase* queue = new EventQueue<EventType>();
                m_eventQueues.insert({Type(EventType), queue});
            }
            EventQueue<EventType>* queue = (EventQueue<EventType>*)m_eventQueues[TypeInfo(&typeid(EventType))];
            return queue;
        }

        /**
         * Remove a window from the application.
         * @param id The window identifier.
         */
        void removeWindow(const NamespaceId& id);

    protected:
        EventChildren getEventNodeChildren() override;
    private:
        Application();

        void update();

        void handleResult(WindowCloseEvent* event, bool& handled) override;
    private:
        static Application* m_instance;

        ApplicationState m_state = ApplicationState::STOPPED;
        RenderAPI m_graphicsApi = RenderAPI::NONE;

        std::unordered_map<NamespaceId, Window*> m_windows = {};
        std::unordered_map<TypeInfo, EventQueueBase*, TypeInfo::HashFunction> m_eventQueues = {};

        std::mutex m_windowMutex = std::mutex();
        std::mutex m_eventQueueMutex = std::mutex();
    };
}
