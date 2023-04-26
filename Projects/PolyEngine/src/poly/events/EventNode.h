#pragma once

#include "EventNodeBase.h"

namespace Poly {

    class EventNode: public IEventNode {
    public:
        /**
         * Add a child to the event node
         * @param child The child to add
         * @param priority The priority of the child
         */
        void addChild(IEventNode* child, uint16_t priority);

        /**
         * Get the children of the event node
         * @return The children of the event node
         */
        EventChildren getEventNodeChildren() override;
    private:
        EventChildren m_children;
    };

} // Poly
