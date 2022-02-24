#include "Application.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <platform/system/windows/WindowsWindow.h>

namespace Poly {
	Application::Application() {
		glfwInit();
	}

	void Application::start() {
		while (true) {

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

		windows.push_back(window);
		return window;
	}
}