#pragma once
#include "Window.h"
#include "poly/events/EventNode.h"

namespace Poly {
	class Application {
	public:
		Application();
		virtual ~Application();

		Window* createWindow(std::string title, uint32_t width, uint32_t height);

		void start();
	private:
		std::list<Window*> windows;
	};

	extern Application* CreateApplication();
}