#include "RenderAPI.h"

#include <platform/api/opengl/OpenGLRenderAPI.h>

namespace Poly {

	RenderAPI* RenderAPI::renderAPI = nullptr;

	void RenderAPI::create(RendererAPI api) {
		switch (api) {
		case RendererAPI::OPENGL:
			renderAPI = new OpenGLRenderAPI;
			break;
		}
	}

	RenderAPI* RenderAPI::getAPI() {
		return renderAPI;
	}
}