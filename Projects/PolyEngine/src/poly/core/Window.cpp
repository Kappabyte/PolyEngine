#include "Window.h"

#include <iostream>

#include <poly/renderer/Renderer.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Poly {
	Window::Window(uint32_t width, uint32_t height, std::string title) :
		title(title), width(width), height(height) {

		updateThread = std::thread(&Window::update, this);

		onInit();
	}

	Window::~Window() {
		glfwTerminate();
	}

	void Window::close() {
		windowOpen = false;
		updateThread.join();
		delete this;
	}

	void Window::update() {
		windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!windowHandle) {
			delete this;
			return;
		}

		RenderAPI::create(RendererAPI::OPENGL);

		glfwMakeContextCurrent((GLFWwindow*)windowHandle);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSwapInterval(GLFW_TRUE);

		while (windowOpen) {
			Renderer::ClearColor(0.0f, 0.5f, 0.5f, 1.0f);
			Renderer::Clear();
			glfwSwapBuffers((GLFWwindow*)windowHandle);
			glfwPollEvents();
		}
	}

	void Window::onExampleEvent(ExampleEvent* e) {
		std::cout << e->getText() << std::endl;
	}
}