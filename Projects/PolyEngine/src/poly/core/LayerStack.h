#pragma once

#include <vector>
#include "Layer.h"

namespace Poly {

    class LayerStack {
    public:
        void pushLayer(Layer* layer, uint16_t priority);
        void pushOverlayLayer(Layer* layer, uint16_t priority);

        void popLayer(Layer* layer);
        void popOverlayLayer(Layer* layer);
    protected:
        std::set<std::pair<uint32_t, Layer*>> getLayers();
    private:
        std::set<std::pair<uint16_t, Layer*>> layers = {};
        std::set<std::pair<uint16_t, Layer*>> overlayLayers = {};
    };

} // Poly
