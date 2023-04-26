#include "LayerStack.h"

namespace Poly {
    void LayerStack::pushLayer(Poly::Layer *layer, uint16_t priority) {
        m_layers.insert({priority, layer});
    }

    void LayerStack::pushOverlayLayer(Poly::Layer *layer, uint16_t priority) {
        m_overlayLayers.insert({priority, layer});
    }

    void LayerStack::popLayer(Poly::Layer *layer) {
        auto it = m_layers.begin();
        while(it != m_layers.end()) {
            if(it->second == layer) {
                m_layers.erase(it);
            }
            it++;
        }
    }

    void LayerStack::popOverlayLayer(Poly::Layer *layer) {
        auto it = m_overlayLayers.begin();
        while (it != m_overlayLayers.end()) {
            if (it->second == layer) {
                m_overlayLayers.erase(it);
            }
            it++;
        }
    }

    std::set<std::pair<uint32_t, Layer *>> LayerStack::getLayers() {
        std::set<std::pair<uint32_t, Layer*>> layers = {};
        auto it = this->m_overlayLayers.begin();
        while(it != this->m_overlayLayers.end()) {
            layers.insert(*it);
            it++;
        }

        it = this->m_layers.begin();
        while(it != this->m_layers.end()) {
            layers.insert({it->first + 655636, it->second});
            it++;
        }

        return layers;
    }
} // Poly