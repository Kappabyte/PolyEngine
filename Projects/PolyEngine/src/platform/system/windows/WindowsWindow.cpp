#include "WindowsWindow.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <poly/renderer/RenderAPI.h>
#include <poly/renderer/Renderer.h>

namespace Poly {
	WindowsWindow::WindowsWindow(uint32_t width, uint32_t height, std::string title): Window(width, height, title) {
		std::cout << "Created Windows Window!" << std::endl;
	}


	void errorCallback(int error, const char* description) {
		std::cout << "GLFW" << error << ": " << description << std::endl;
	}

	void WindowsWindow::onOpen() {
		windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!windowHandle) {
			delete this;
			return;
		}

		RenderAPI::create(RendererAPI::OPENGL);

		context = RendererContext::create(RendererAPI::OPENGL);

		context->makeContextCurrent(windowHandle);
		context->init();

		glfwSwapInterval(GLFW_TRUE);
		glfwSetErrorCallback(&errorCallback);
	}

	void WindowsWindow::onUpdate() {
		context->swapBuffers(windowHandle);
		glfwPollEvents();

		if (glfwWindowShouldClose((GLFWwindow*)windowHandle)) {
			close();
		}
	}

	void WindowsWindow::onClose() {

	}

	WindowsWindow::~WindowsWindow() {
		glfwTerminate();
	}
}