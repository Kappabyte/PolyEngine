#pragma once

#include "RenderAPI.h"

namespace Poly {
	class RendererContext {
	public:
		static RendererContext* create(RendererAPI api);

		virtual void init() = 0;
		virtual void makeContextCurrent(void* windowHandle) = 0;
		virtual void swapBuffers(void* windowHandle) = 0;
	private:
	};
}