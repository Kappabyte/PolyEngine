#pragma once

namespace Poly {
    class BaseListener {};

    template <class EventType>
    class EventListener : public BaseListener {
    public:
        /**
         * Create the event listener
         */
        EventListener() {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType not derived from Event");
        }

        /**
         * Handles events of the type EventType
         * @param event
         */
        virtual void handle(EventType* event) = 0;
    };

    template <class EventType>
    class EventResultListener : public BaseListener {
    public:
        /**
         * Create the event result listener
         */
        EventResultListener() {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType not derived from Event");
        }

        /**
         * Handles event results of the type EventType
         * @param event The event to handle
         * @param shouldPropagate Whether or not to continue propagating the event result (default = true)
         */
        virtual void handleResult(EventType* event, bool& shouldPropagate) = 0;
    };
}
