#include "EventQueue.h"

namespace Poly {
    uint16_t EventQueue::getQueueSize() {
        lock.lock();
        uint16_t queueSize = queue.size();
        lock.unlock();

        return queueSize;
    }

    std::pair<TypeInfo, Event *> EventQueue::popQueue() {
        lock.lock();
        auto event = queue.front();
        queue.pop();
        lock.unlock();
        return event;
    }
} // Poly