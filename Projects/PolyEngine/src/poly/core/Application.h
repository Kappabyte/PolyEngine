#pragma once
#include "Window.h"
#include "poly/events/EventNode.h"

namespace Poly {
	class Application : public EventNode {
	public:
		Application(std::string title, uint32_t width, uint32_t height);
		virtual ~Application();

		void start();

		void pushLayer(Layer* layer);
	private:
		Window* createWindow(std::string title, uint32_t width, uint32_t height);
	
	private:
		Window* window = nullptr;
		LayerStack* layerStack = new LayerStack();

		std::list<Layer*> layers;
	};
}