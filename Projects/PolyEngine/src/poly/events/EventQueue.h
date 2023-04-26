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
            auto lock = std::lock_guard(m_lock);
            ASSERT((std::is_base_of<Event, EventType>::value), "EventType not derived from Event");
            m_queue.push(event);
        }

        /**
         * Dispatch all the events in the event queue to the event node
         * @param eventNode The event node to dispatch the events to.
         */
        void dispatchEvents(IEventNode* eventNode) override {
            auto lock = std::lock_guard(m_lock);
            while(!m_queue.empty()) {
                std::cout << "Handling event: " << typeid(EventType).name() << std::endl;
                auto event = m_queue.front();
                m_queue.pop();
                eventNode->dispatch<EventType>(event);
            }
        }
    private:
        std::mutex m_lock;
        std::queue<EventType*> m_queue = {};
    };



} // Poly
