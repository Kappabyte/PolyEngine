//
// Created by avery on 2022-09-20.
//

#pragma once

#include "poly/events/Event.h"

namespace Poly {
    class WindowCloseEvent : public Event {
    public:
        explicit WindowCloseEvent(NamespaceID identifier): identifier(identifier) {};

        NamespaceID identifier;
    };
}
