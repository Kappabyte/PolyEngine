#pragma once

#include <thread>
#include <list>

#include "poly/events/EventNode.h"
#include "poly/events/ExampleEvent.h"
#include "poly/layers/LayerStack.h"

namespace Poly {
	class Window : public EventNode {
	public:
		Window(uint32_t width, uint32_t height, std::string name = "Poly Engine Window");
		~Window();

		void open();
		void close();

		void pushLayer(Layer* layer);

		virtual void update() = 0;
		void onExampleEvent(ExampleEvent* e);
	protected:
		virtual void onInit() = 0;
	private:
		using EventNode::addChild;
		using EventNode::getPriority;
		using EventNode::getChildren;

		virtual void internalUpdate();

	protected:
		std::string title;
		int width;
		int height;

		std::list<Layer*> layers;

		bool windowOpen = true;

		std::thread updateThread;

		void* windowHandle = nullptr;
		LayerStack* layerStack = new LayerStack();
	};
}