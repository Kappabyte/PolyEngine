#pragma once
#include "Layer.h"
#include <list>

namespace Poly {
	class LayerStack {
	public:
		void updateLayers();

		void pushLayer(Layer* layer);
	private:
		std::list<Layer*> layers;
	};
}