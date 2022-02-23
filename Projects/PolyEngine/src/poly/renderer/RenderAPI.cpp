#include "RenderAPI.h"

#include <platform/api/opengl/OpenGLRenderAPI.h>

namespace Poly {
	void RenderAPI::create(RendererAPI api) {
		switch (api) {
		case RendererAPI::OPENGL:
			RenderAPI::api = new OpenGLRenderAPI;
			break;
		case RendererAPI::NULL:
		}
	}

	RenderAPI* RenderAPI::getAPI() {
		return api;
	}
}