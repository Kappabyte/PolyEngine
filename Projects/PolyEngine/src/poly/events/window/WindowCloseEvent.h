#pragma once

#include <utility>

#include "poly/events/Event.h"

namespace Poly {
    class WindowCloseEvent : public Event {
    public:
        explicit WindowCloseEvent(NamespaceId identifier): m_identifier(std::move(identifier)) {};

        NamespaceId m_identifier;
    };
}
