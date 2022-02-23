#pragma once

#include <thread>

#include "poly/events/EventNode.h"
#include "poly/events/ExampleEvent.h"
#include "poly/layers/Layer.h"

namespace Poly {
	class Window : public EventNode {
	public:
		Window(uint32_t width, uint32_t height, std::string name = "Poly Engine Window");
		~Window();

		void close();

		void update();
		void onExampleEvent(ExampleEvent* e);
	protected:
		virtual void onInit() = 0;
	private:
		using EventNode::addChild;
		using EventNode::getChildren;
		using EventNode::getPriority;
	private:
		std::string title;
		int width;
		int height;

		std::list<Layer*> layers;

		bool windowOpen = true;

		std::thread updateThread;

		void* windowHandle;
	};
}