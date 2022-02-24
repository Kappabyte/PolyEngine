#pragma once

#include "platform/api/opengl/OpenGLContext.h"

namespace Poly {
	class WindowsOpenGLContext : public OpenGLContext {
	public:
		void init() override;
		void makeContextCurrent(void* windowHandle) override;
		void swapBuffers(void* windowHandle) override;
	};
}