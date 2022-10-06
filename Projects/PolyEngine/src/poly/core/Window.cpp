#include "Window.h"

#include <iostream>

namespace Poly {
	Window::Window(uint32_t width, uint32_t height, std::string title) :
		title(title), width(width), height(height) {

		std::cout << "Created Window" << std::endl;
	}

	Window::~Window() {

	}

	void Window::open() {
		onOpen();
	}

	void Window::update() {
		onUpdate();
	}

	void Window::close() {
		onClose();
		windowOpen = false;
		std::cout << "Window Closed" << std::endl;
	}
}