#include "EventNode.h"

namespace Poly {
    void EventNode::addChild(Poly::IEventNode* child, uint16_t priority) {
        children.insert({priority, child});
    }

    EventChildren EventNode::getEventNodeChildren() {
        return this->children;
    }
} // Poly