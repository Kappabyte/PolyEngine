//
// Created by avery on 2022-10-03.
//

#include "RenderCommand.h"
#include "poly/core/Application.h"
#include "platform/api/gl/GLRenderCommand.h"

namespace Poly {
    void RenderCommandExecutor::setClearColor(float r, float g, float b, float a) {
        RenderCommandExecutor::get()->i_SetClearColor(r, g, b, a);
    }

    void RenderCommandExecutor::clear(bool colourBuffer, bool depthBuffer) {
        RenderCommandExecutor::get()->i_Clear(colourBuffer, depthBuffer);
    }

    void RenderCommandExecutor::drawIndexed() {
        RenderCommandExecutor::get()->i_DrawIndexed();
    }

    Unique<RenderCommandExecutor> RenderCommandExecutor::get() {
        switch(Application::get()->getAPI()) {
            case API::GL: return MakeUnique<GL::GLRenderCommandExecutor>();
            default: return nullptr;
        }
    }
} // Poly
