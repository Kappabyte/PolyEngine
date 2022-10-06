#include "Application.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <platform/system/windows/WindowsWindow.h>

namespace Poly {
	Application::Application(std::string title, uint32_t width, uint32_t height) {
		window = createWindow(title, width, height);
		glfwInit();
	}

	void Application::start() {
		//Open the window
		window->open();
		
		//Update the window
		while (window->isOpen()) {
			window->update();
			layerStack->updateLayers();
		}
	}

	Application::~Application() {

	}

	Window* Application::createWindow(std::string title, uint32_t width, uint32_t height) {
		Window* window;
		#ifdef POLY_PLATFORM_WINDOWS
		std::cout << "Platform: Windows" << std::endl;
			window = new WindowsWindow(width, height, title);

		#else
		std::cout << "Platform: Unknown" << std::endl;
		#endif
		return window;
	}

	void Application::pushLayer(Layer* layer) {
		layerStack->pushLayer(layer);
		addChild(layer);
	}
}