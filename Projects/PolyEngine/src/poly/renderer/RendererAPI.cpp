#include "RendererAPI.h"

namespace Poly {
	namespace RendererAPI {

		void ClearColor(float r, float g, float b, float a) {
			RenderAPI::getAPI()->clearColor(r, g, b, a);
		}

		void Clear() {
			RenderAPI::getAPI()->clearDepthBuffer();
			RenderAPI::getAPI()->clearColorBuffer();
		}

		void ClearColorBuffer() {
			RenderAPI::getAPI()->clearColorBuffer();
		}

		void ClearDepthBuffer() {
			RenderAPI::getAPI()->clearDepthBuffer();
		}
	}
}