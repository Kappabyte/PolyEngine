#pragma once
#include "Layer.h"
#include <list>

namespace Poly {
	class LayerStack : public EventNode {
	public:
		LayerStack(): EventNode(2) {}
		void updateLayers();

		void pushLayer(Layer* layer);
	private:
		std::list<Layer*> layers;
	};
}