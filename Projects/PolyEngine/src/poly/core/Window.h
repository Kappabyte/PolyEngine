#pragma once

#include <thread>
#include <list>

#include "poly/events/EventNode.h"
#include "poly/events/ExampleEvent.h"
#include "poly/layers/LayerStack.h"

namespace Poly {
	class Window {
	public:
		Window(uint32_t width, uint32_t height, std::string name = "Poly Engine Window");
		~Window();

		void open();
		void update();
		void close();

		bool inline isOpen() {
			return windowOpen;
		}
	protected:
		virtual void onOpen() = 0;
		virtual void onUpdate() = 0;
		virtual void onClose() = 0;

	protected:
		std::string title;
		int width;
		int height;

		bool windowOpen = true;

		void* windowHandle = nullptr;
	};
}