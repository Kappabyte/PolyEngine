#pragma once

#include "poly/events/EventNode.h"

namespace Poly {

    class Layer: public EventNode {
    public:
        /**
         * Called when the layer is initialized.
         */
        virtual void init() = 0;
        /**
         * Called when the layer is upated.
         */
        virtual void update() = 0;
    };

} // Poly
