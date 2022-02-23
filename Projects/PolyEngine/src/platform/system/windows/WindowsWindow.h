#pragma once

#include "poly/core/Window.h"

#include <iostream>

namespace Poly {

	void errorCallback(int error, const char* description) {
		std::cout << "GLFW" << error << ": " << description << std::endl;
	}

	class WindowsWindow : public Window {
	public:
		WindowsWindow(uint32_t width, uint32_t height, std::string title): Window(width, height, title) {

		}
	private:
		void onInit() override {

			glfwSetErrorCallback(errorCallback);
		}
	};
}