#include "Window.h"

#include <iostream>

namespace Poly {
	Window::Window(uint32_t width, uint32_t height, std::string title) :
		title(title), width(width), height(height) {

		std::cout << "Created Window" << std::endl;

		addChild(layerStack);
	}

	void Window::open() {
		updateThread = std::thread(&Window::internalUpdate, this);
	}

	Window::~Window() {

	}

	void Window::internalUpdate() {
		std::cout << "Update Start " << title << std::endl;
		update();
	}

	void Window::pushLayer(Layer* layer) {
		layerStack->pushLayer(layer);
		layerStack->addChild(layer);
	}

	void Window::close() {
		windowOpen = false;
		updateThread.join();
		delete this;
	}

	void Window::onExampleEvent(ExampleEvent* e) {
		std::cout << e->getText() << std::endl;
	}
}