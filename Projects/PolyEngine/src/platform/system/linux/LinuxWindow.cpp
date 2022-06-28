#include "LinuxWindow.h"

#include <GLFW/glfw3.h>
#include <poly/renderer/RenderAPI.h>
#include <poly/renderer/Renderer.h>

namespace Poly {
	LinuxWindow::LinuxWindow(uint32_t width, uint32_t height, std::string title): Window(width, height, title) {
		std::cout << "Created Linux (X11) Window!" << std::endl;
		onInit();
	}

	void LinuxWindow::update() {
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

		while (windowOpen) {
			std::cout << "Update " << title << std::endl;
			layerStack->updateLayers();
			dispatch(new ExampleEvent("test"));
			context->swapBuffers(windowHandle);
			glfwPollEvents();

			// if (glfwWindowShouldClose((GLFWwindow*)windowHandle)) {
			// 	CloseEvent e = CloseEvent();
			// 	dispatch(&e);
			// 	if (!e.isCancelled()) {
			// 		windowOpen = false;
			// 	}
			// }
		}
	}

	void errorCallback(int error, const char* description) {
		std::cout << "GLFW" << error << ": " << description << std::endl;
	}

	void LinuxWindow::onInit() {
		glfwSetErrorCallback(&errorCallback);
	}

	LinuxWindow::~LinuxWindow() {
		glfwTerminate();
	}
}