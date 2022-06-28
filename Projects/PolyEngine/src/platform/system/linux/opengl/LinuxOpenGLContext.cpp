#include "LinuxOpenGLContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Poly {

	void LinuxOpenGLContext::init() {
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
	void LinuxOpenGLContext::makeContextCurrent(void* windowHandle) {
		glfwMakeContextCurrent((GLFWwindow*) windowHandle);
	}

	void LinuxOpenGLContext::swapBuffers(void* windowHandle) {
		glfwSwapBuffers((GLFWwindow*)windowHandle);
	}
}