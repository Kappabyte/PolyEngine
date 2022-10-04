#pragma once

#include <barrier>
#include "poly/events/EventQueue.h"
#include "poly/events/EventNodeBase.h"
#include "LayerStack.h"
#include "Window.h"
#include "poly/events/window/WindowCloseEvent.h"
#include "poly/util/NamespaceID.h"
#include "poly/render/API.h"

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
        void setAPI(API api);

        /**
         * Get the graphics API
         * @return The Graphics API
         */
        API getAPI();

        /**
         * Add a window to the application
         * @param identifier The identifier of the window. Used to fetch the window at a later point.
         * @param props The properties of the created window.
         * @return The created window.
         */
        Window* addWindow(const NamespaceID& identifier, WindowProps props);
        /**
         * Add a window to the application with the default window properties.
         * @param identifier The identifier of the window. Used to fetch the window at a later point.
         * @return The created the window.
         */
        Window* addWindow(const NamespaceID& identifier);
        /**
         * Get a window based on the window identifier.
         * @param identifier The window identifier.
         * @return The window associated with the identifier, or nullptr if the window could not be found.
         */
        Window* getWindow(const NamespaceID& identifier);

        /**
         * Get an event queue of the specified type. Any events added to any of the queues will be executed on the root
         * event node at the start of each application update tick.
         * @tparam EventType The type of event to get the event queue for.
         * @return The event queue.
         */
        template <class EventType>
        EventQueue<EventType>* getEventQueue() {
            queueMutex.lock();
            if(eventQueues.find(TypeInfo(&typeid(EventType))) == eventQueues.end()) {
                EventQueueBase* queue = new EventQueue<EventType>();
                eventQueues.insert({TypeInfo(&typeid(EventType)), queue});
            }
            EventQueue<EventType>* queue = (EventQueue<EventType>*)eventQueues[TypeInfo(&typeid(EventType))];
            queueMutex.unlock();
            return queue;
        }
        /**
         * Remove a window from the application.
         * @param id The window identifier.
         */
        void removeWindow(NamespaceID id);

    protected:
        EventChildren getEventNodeChildren() override;
    private:
        Application();
        void handleResult(WindowCloseEvent* event, bool& handled) override;
    public:
        std::barrier<std::__empty_completion> sync_point = std::barrier(2);
    private:
        static Application* instance;

        ApplicationState state = ApplicationState::STOPPED;
        API graphicsAPI = API::NONE;

        std::unordered_map<TypeInfo, EventQueueBase*, TypeInfo::HashFunction> eventQueues = {};
        std::unordered_map<NamespaceID, Window*> windows = {};

        std::mutex queueMutex = std::mutex();
    };
}
