//
// Created by avery on 2022-10-03.
//

#include "GLRenderCommand.h"
#include "glad/glad.h"

namespace Poly::GL {

    void GLRenderCommandExecutor::i_SetClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void GLRenderCommandExecutor::i_Clear(bool colourBuffer, bool depthBuffer) {
        GLint flags = 0;
        flags |= colourBuffer ? GL_COLOR_BUFFER_BIT : 0;
        flags |= depthBuffer ? GL_DEPTH_BUFFER_BIT : 0;
        glClear(flags);
    }

    void GLRenderCommandExecutor::i_DrawIndexed() {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}