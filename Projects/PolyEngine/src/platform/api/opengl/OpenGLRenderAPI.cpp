#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Poly {
	void OpenGLRenderAPI::init() {

	}

	void OpenGLRenderAPI::clearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void OpenGLRenderAPI::clearColorBuffer() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderAPI::clearDepthBuffer() {
		glClear(GL_DEPTH_BUFFER_BIT);
	}
}