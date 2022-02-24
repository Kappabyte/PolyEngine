#pragma once

#include "../events/EventNode.h"

namespace Poly {
	class Layer : public EventNode {
	public:
		Layer(uint16_t priority) : EventNode(priority) {}
		virtual void update() = 0;
	};
}