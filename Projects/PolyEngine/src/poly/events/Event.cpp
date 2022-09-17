#include "Event.h"

namespace Poly {
    void Event::setCancelled(bool cancelled) {
        this->cancelled = cancelled;
    }

    bool Event::isCancelled() {
        return this->cancelled;
    }
} // Poly