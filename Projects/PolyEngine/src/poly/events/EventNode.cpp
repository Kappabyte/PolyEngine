#include "EventNode.h"

namespace Poly {
    void EventNode::addChild(Poly::IEventNode* child, uint16_t priority) {
        m_children.insert({priority, child});
    }

    EventChildren EventNode::getEventNodeChildren() {
        return this->m_children;
    }
} // Poly