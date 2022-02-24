#pragma once

namespace Poly {

	enum class RendererAPI {
		OPENGL
	};

	class RenderAPI {
	public:
		static void create(RendererAPI api);
		static RenderAPI* getAPI();

		virtual void init() = 0;

		virtual void clearColorBuffer() = 0;
		virtual void clearDepthBuffer() = 0;
		virtual void clearColor(float r, float g, float b, float a) = 0;
	private:
		static RenderAPI* renderAPI;
	};
}