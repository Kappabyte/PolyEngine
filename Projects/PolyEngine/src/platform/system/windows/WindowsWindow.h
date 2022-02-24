#pragma once

#include "poly/core/Window.h"
#include "poly/renderer/RendererContext.h"
#include "poly/layers/LayerStack.h"

#include <iostream>

namespace Poly {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(uint32_t width, uint32_t height, std::string title);

		~WindowsWindow();

		void update() override;
	private:
		void onInit() override;

		RendererContext* context = nullptr;
	};
}