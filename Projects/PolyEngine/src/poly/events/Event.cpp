#include "Event.h"

namespace Poly {
    void Event::setCancelled(bool cancelled) {
        this->m_cancelled = cancelled;
    }

    bool Event::isCancelled() const {
        return this->m_cancelled;
    }
} // Poly