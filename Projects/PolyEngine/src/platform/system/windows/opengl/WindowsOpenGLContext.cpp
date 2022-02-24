#include "WindowsOpenGLContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Poly {

	void WindowsOpenGLContext::init() {
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
	void WindowsOpenGLContext::makeContextCurrent(void* windowHandle) {
		glfwMakeContextCurrent((GLFWwindow*) windowHandle);
	}

	void WindowsOpenGLContext::swapBuffers(void* windowHandle) {
		glfwSwapBuffers((GLFWwindow*)windowHandle);
	}
}