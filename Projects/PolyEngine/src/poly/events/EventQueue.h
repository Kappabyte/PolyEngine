#pragma once

#include <utility>
#include <mutex>
#include <queue>
#include "poly/util/TypeInfo.h"
#include "Event.h"
#include "EventNodeBase.h"

#include <iostream>

namespace Poly {

    class EventQueueBase {
    public:
        /**
         * Dispatch all the events in the event queue to the event node
         * @param eventNode The event node to dispatch the events to.
         */
        virtual void dispatchEvents(IEventNode* eventNode) = 0;
    };

    template <class EventType>
    class EventQueue : public EventQueueBase {
    public:
        /**
         * Add an event to the event queue
         * @tparam EventType The type of event to add
         * @param event The event to add
         */
        void addToQueue(EventType* event) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType not derived from Event");
            std::cout << "Adding event: " << typeid(EventType).name() << std::endl;
            lock.lock();
            std::cout << "Adding event to queue" << std::endl;
            queue.push(event);
            lock.unlock();
        }

        /**
         * Dispatch all the events in the event queue to the event node
         * @param eventNode The event node to dispatch the events to.
         */
        void dispatchEvents(IEventNode* eventNode) override {
            lock.lock();
            while(!queue.empty()) {
                std::cout << "Handling event: " << typeid(EventType).name() << std::endl;
                auto event = queue.front();
                queue.pop();
                eventNode->dispatch<EventType>(event);
            }
            lock.unlock();
        }
    private:
        std::mutex lock;
        std::queue<EventType*> queue = {};
    };



} // Poly
