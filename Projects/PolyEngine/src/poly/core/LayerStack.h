#pragma once

#include <vector>
#include "Layer.h"

namespace Poly {

    class LayerStack {
    public:
        /**
         * Add a layer to the layer stack. Layers with a higher priority will be executed later, but receive events
         * earlier. Regular layers are updated before overlay layers, but receive events after overlay layers.
         * @param layer The layer to add to the layer stack
         * @param priority The priority of the layer.
         */
        void pushLayer(Layer* layer, uint16_t priority);
        /**
         * Add an overlay layer to the layer stack. Layers with a higher priority will be executed later, but receive events
         * earlier. Regular layers are updated before overlay layers, but receive events after overlay layers.
         * @param layer The layer to add to the layer stack
         * @param priority The priority of the layer.
         */
        void pushOverlayLayer(Layer* layer, uint16_t priority);

        /**
         * Remove a layer from the layer stack.
         * @param layer The layer to remove
         */
        void popLayer(Layer* layer);

        /**
         * Remove an overlay layer from the layer stack.
         * @param layer The layer to remove.
         */
        void popOverlayLayer(Layer* layer);
    protected:
        std::set<std::pair<uint32_t, Layer*>> getLayers();
    private:
        std::set<std::pair<uint16_t, Layer*>> layers = {};
        std::set<std::pair<uint16_t, Layer*>> overlayLayers = {};
    };

} // Poly
