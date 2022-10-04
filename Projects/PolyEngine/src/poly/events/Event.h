#pragma once

#include "string"

namespace Poly {
    class Event {
    public:
        /**
         * Set the event cancellation state
         * @param cancelled The event cancellation state
         */
        void setCancelled(bool cancelled);

        /**
         * Check if the event is cancelled
         * @return Whether the event is cancelled
         */
        bool isCancelled();
    public:
        bool cancelled = false;
    };

} // Poly
