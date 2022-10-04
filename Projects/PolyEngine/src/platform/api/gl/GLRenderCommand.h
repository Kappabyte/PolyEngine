//
// Created by avery on 2022-10-03.
//

#pragma once

#include "poly/render/RenderCommand.h"

namespace Poly::GL {
    class GLRenderCommandExecutor : public RenderCommandExecutor {
    protected:
        void i_SetClearColor(float r, float g, float b, float a) override;
        void i_Clear(bool colourBuffer, bool depthBuffer) override;
        void i_DrawIndexed() override;
    };
}

