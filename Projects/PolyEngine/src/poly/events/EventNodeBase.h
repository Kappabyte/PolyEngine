#pragma once

#include "Event.h"
#include "EventListener.h"

#include "poly/util/TypeInfo.h"

#include <unordered_map>
#include <set>

#define EventChildren std::set<std::pair<uint32_t, IEventNode*>>

namespace Poly {
    /**
     * A Generic event node in the application
     *
     * The event tree way look as follows:
     * ----------------------------------------<br>
     * (1) EventNode<br>
     *  - (1.1) Listener (Priority 0)<br>
     *  - (1.2) Listener (Priority 1)<br>
     *  - (1.3) Event Node (Priority 0)<br>
     *  &nbsp; - (1.3.1) Listener (Priority 0)<br>
     *  &nbsp; - (1.3.2) Listener (Priority 1)<br>
     *  - (1.4) Event Node (Priority 1)<br>
     *  &nbsp; - (1.4.1) Listener (Priority 0)<br>
     */
    class IEventNode {
    public:
        /**
         * Create the generic event node
         */
        IEventNode() = default;

        /**
         * Dispatch an event to the event tree.
         *
         * Assuming an event tree that looks like the following:
         * ----------------------------------------<br>
         * (1) EventNode<br>
         *  - (1.1) Listener (Priority 0)<br>
         *  - (1.2) Listener (Priority 1)<br>
         *  - (1.3) Event Node (Priority 0)<br>
         *  &nbsp; - (1.3.1) Listener (Priority 0)<br>
         *  &nbsp; - (1.3.2) Listener (Priority 1)<br>
         *  - (1.4) Event Node (Priority 1)<br>
         *  &nbsp; - (1.4.1) Listener (Priority 0)<br>
         * -----------------------------------------<br>
         * The order of execution of listeners is as follows:
         *  1.1, 1.2, 1.3.1, 1.3.2, 1.4.1
         *
         *  Listeners on the current event node are executed first. If the event is cancelled, no further propagation wil occur.
         *  After all listeners on the current node have been run, the event will propagate to each child node.
         * @tparam EventType The type of event to be dispatched
         * @param event The event to dispatch
         */
        template <class EventType>
        inline void dispatch(EventType* event) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType not derived from Event");

            bool propagateResult = true;
            dispatch(TypeInfo(&typeid(*event)), event, propagateResult, this);
        }
    protected:
        /**
         * Add an event listener to the current node. The event listener will be called whenever an uncanceled
         * event is dispatched to a node
         * @tparam EventType The type of event to listen to
         * @param listener The listener to register
         * @param priority The priority of the listener. Lower priorities take precedence over higher priorities.
         */
        template <class EventType>
        inline void addListener(EventListener<EventType>* listener, uint16_t priority) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType not derived from Event");

            if (listeners.find(TypeInfo(&typeid(EventType))) == listeners.end()) {
                listeners.insert({TypeInfo(&typeid(EventType)), new std::multiset<std::pair<uint16_t, BaseListener*>>});
            }

            std::multiset<std::pair<uint16_t, BaseListener*>>* eventHandlers = listeners.find(TypeInfo(&typeid(EventType)))->second;
            eventHandlers->insert({priority, listener});
        }

        /**
         * Add a result listener to the current node. The result listener will be called once an event has finished propagating through
         * the event tree.
         * @tparam EventType The type of event to listen for the result of
         * @param listener The listener to register
         * @param priority The priority of the result listener. Lower priorities take precedence over higher priorities.
         */
        template <class EventType>
        inline void addResultListener(EventResultListener<EventType>* listener, uint16_t priority) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType not derived from Event");

            if (resultListeners.find(TypeInfo(&typeid(EventType))) == resultListeners.end()) {
                resultListeners.insert({TypeInfo(&typeid(EventType)), new std::multiset<std::pair<uint16_t, BaseListener*>>});
            }

            std::multiset<std::pair<uint16_t, BaseListener*>>* eventHandlers = resultListeners.find(TypeInfo(&typeid(EventType)))->second;
            eventHandlers->insert({priority, listener});
        }

        /**
         * Get the children of the event node
         * @return the children of the event node
         */
        virtual EventChildren getEventNodeChildren() = 0;

        bool dispatch(TypeInfo info, Event* event);
    private:
        bool dispatch(TypeInfo info, Event* event, bool &propagateResult, IEventNode* root);
        void dispatchResult(TypeInfo info, Event* event, bool& propagateResult);

    private:
        std::unordered_map<TypeInfo, std::multiset<std::pair<uint16_t, BaseListener*>>*, TypeInfo::HashFunction> listeners = {};
        std::unordered_map<TypeInfo, std::multiset<std::pair<uint16_t, BaseListener*>>*, TypeInfo::HashFunction> resultListeners = {};
    };

} // PolyEngine