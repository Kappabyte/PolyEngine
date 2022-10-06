//
// Created by avery on 2022-09-28.
//

#pragma once

#include "poly/render/Buffer.h"
#include "glad/glad.h"

namespace Poly::GL {

    class GLVertexBufferArray: public VertexBufferArray {
    public:
        GLVertexBufferArray();
        ~GLVertexBufferArray() override;

        void bind() override;
        void unbind() override;
    private:
        GLuint arrayID{};
    };

    class GLVertexBuffer: public VertexBuffer {
    public:
        GLVertexBuffer();
        ~GLVertexBuffer() override;

        void setLayout(std::vector<BufferElement> elements) override;
        void setLayout(BufferLayout layout) override;

        void bind() override;
        void unbind() override;
        void data(void* data, uint32_t length) override;
    private:
        GLuint bufferID{};
    };

    class GLIndexBuffer: public IndexBuffer {
    public:
        GLIndexBuffer();
        ~GLIndexBuffer() override;

        void bind() override;
        void unbind() override;
        void data(void* data, uint32_t length) override;
    private:
        GLuint bufferID;
    };

} // GL
