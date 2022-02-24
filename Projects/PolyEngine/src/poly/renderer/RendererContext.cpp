#include "RendererContext.h"

#include "platform/system/windows/opengl/WindowsOpenGLContext.h"

namespace Poly {
	RendererContext* RendererContext::create(RendererAPI api) {
		RendererContext* context = nullptr;
		switch (api) {
		case RendererAPI::OPENGL:
			#if defined POLY_PLATFORM_WINDOWS
			context = new WindowsOpenGLContext;
			#elif defined POLY_PLATFORM_LINUX
			#endif
			break;
		}

		return context;
	}
}