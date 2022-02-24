#include "LayerStack.h"
#include <algorithm>
#include <iostream>

namespace Poly {
	void LayerStack::updateLayers() {
		for (Layer* layer : layers) {
			layer->update();
		}
	}

	void LayerStack::pushLayer(Layer* layer) {
		layers.insert(std::upper_bound(layers.begin(), layers.end(), layer, [](const Layer* c, const Layer* id) {
			return c->getPriority() < id->getPriority();
		}), layer);
	}
}