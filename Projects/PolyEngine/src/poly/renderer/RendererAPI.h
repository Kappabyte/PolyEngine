#pragma once

#include "RenderAPI.h"

namespace Poly {
	namespace RendererAPI {

		void ClearColor(float r, float g, float b, float a);

		void Clear();

		void ClearColorBuffer();

		void ClearDepthBuffer();
	}
}