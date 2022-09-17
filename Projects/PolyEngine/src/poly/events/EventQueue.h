#pragma once

#include <utility>
#include <mutex>
#include <queue>
#include "poly/util/TypeInfo.h"
#include "Event.h"

namespace Poly {

    class EventQueue {
    public:
        /**
         * Add an event to the event queue
         * @tparam EventType The type of event to add
         * @param event The event to add
         */
        template <class EventType>
        void addToQueue(EventType* event) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType not derived from Event");
            lock.lock();
            queue.push({TypeInfo(&typeid(EventType)), event});
            lock.unlock();
        }

        /**
         * Get and remove the first item from the queue
         * @return The popped event
         */
        std::pair<TypeInfo, Event*> popQueue();

        /**
         * Get how many events are in the queue
         * @return The queue size
         */
        uint16_t getQueueSize();
    private:
        std::mutex lock;
        std::queue<std::pair<TypeInfo, Event*>> queue = {};
    };

} // Poly
