#pragma once

#include "RenderAPI.h"

namespace Poly {
	namespace Renderer {

		void ClearColor(float r, float g, float b, float a);

		void Clear();

		void ClearColorBuffer();

		void ClearDepthBuffer();
	}
}