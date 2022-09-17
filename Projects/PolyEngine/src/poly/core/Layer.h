#pragma once

#include "poly/events/EventNode.h"

namespace Poly {

    class Layer: public EventNode {
    public:
        virtual void init() = 0;
        virtual void update() = 0;
    };

} // Poly
