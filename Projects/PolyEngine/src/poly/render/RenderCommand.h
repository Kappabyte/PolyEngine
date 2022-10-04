//
// Created by avery on 2022-10-03.
//

#pragma once

#include <poly/util/Ref.h>

namespace Poly {

    enum class RenderCommandType {
        SET_CLEAR_COLOUR,
        CLEAR,
        DRAW_INDEXED
    };

    class RenderCommand {
    public:
        RenderCommand(RenderCommandType type, void* data): type(type), data(data) {};
    public:
        RenderCommandType type;
        void* data;
    };

    class RenderCommandExecutor {
    public:
        virtual ~RenderCommandExecutor() = default;

        /**
         * Set the clear colour of the renderer
         * @param r Red
         * @param g Green
         * @param b Blue
         * @param a Alpha (Opacity)
         */
        static void setClearColor(float r, float g, float b, float a);
        /**
         * Clear the framebuffer
         * @param colourBuffer Should the colour buffer be cleared
         * @param depthBuffer Should the depth buffer be cleared
         */
        static void clear(bool colourBuffer, bool depthBuffer);

        /**
         * Draw the currently bound VertexBufferArray to the framebuffer
         * @see VertexBufferArray
         */
        static void drawIndexed();
    protected:
        virtual void i_SetClearColor(float r, float g, float b, float a) = 0;
        virtual void i_Clear(bool colourBuffer, bool depthBuffer) = 0;
        virtual void i_DrawIndexed() = 0;
    private:
        static Unique<RenderCommandExecutor> get();
    };
} // Poly
