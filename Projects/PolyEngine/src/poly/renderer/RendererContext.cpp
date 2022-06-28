#include "RendererContext.h"

#include "platform/system/windows/opengl/WindowsOpenGLContext.h"
#include "platform/system/linux/opengl/LinuxOpenGLContext.h"

namespace Poly {
	RendererContext* RendererContext::create(RendererAPI api) {
		RendererContext* context = nullptr;
		switch (api) {
		case RendererAPI::OPENGL:
			#if defined POLY_PLATFORM_WINDOWS
			context = new WindowsOpenGLContext;
			#elif defined POLY_PLATFORM_LINUX
			context = new LinuxOpenGLContext;
			#endif
			break;
		}

		return context;
	}
}