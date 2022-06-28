#pragma once
#include <poly/events/EventNode.h>

namespace Poly {
    class CoreManager {
    public:
        CoreManager(EventNode root): EventNode(1), root(root) {
        }
    private:
        EventNode root;
    }

    class ICoreManager {
    public:
        virtual void init()
    }
}