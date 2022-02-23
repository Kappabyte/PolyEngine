#pragma once

#include <poly/renderer/RenderAPI.h>

namespace Poly {
	class OpenGLRenderAPI : public RenderAPI {
	public:
		void init() override;

		void clearColorBuffer() override;
		void clearDepthBuffer() override;
		void clearColor(float r, float g, float b, float a) override;
	};
}