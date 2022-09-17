#include "LayerStack.h"

namespace Poly {
    void LayerStack::pushLayer(Poly::Layer *layer, uint16_t priority) {
        layers.insert({priority, layer});
    }

    void LayerStack::pushOverlayLayer(Poly::Layer *layer, uint16_t priority) {
        overlayLayers.insert({priority, layer});
    }

    void LayerStack::popLayer(Poly::Layer *layer) {
        auto it = layers.begin();
        while(it != layers.end()) {
            if(it->second == layer) {
                layers.erase(it);
            }
            it++;
        }
    }

    void LayerStack::popOverlayLayer(Poly::Layer *layer) {
        auto it = overlayLayers.begin();
        while (it != overlayLayers.end()) {
            if (it->second == layer) {
                overlayLayers.erase(it);
            }
            it++;
        }
    }

    std::set<std::pair<uint32_t, Layer *>> LayerStack::getLayers() {
        std::set<std::pair<uint32_t, Layer*>> layers = {};
        auto it = this->overlayLayers.begin();
        while(it != this->overlayLayers.end()) {
            layers.insert(*it);
            it++;
        }

        it = this->layers.begin();
        while(it != this->layers.end()) {
            layers.insert({it->first + 655636, it->second});
            it++;
        }

        return layers;
    }
} // Poly