#pragma once


#include <cstdint>
#include <string>
#include <vector>
#include "poly/render/shader/ShaderType.h"
#include "poly/util/Ref.h"

namespace Poly {

    /**
     * An element in the vertex buffer.
     */
    struct BufferElement {
        /**
         * The shader data type
         */
        ShaderType m_type;
        /**
         * The location of the element in the shader
         */
        int32_t m_location;
        /**
         * The name of the element
         */
        std::string m_name;
        /**
         * The offset of this element (in bytes) in each vertex.
         */
        uint64_t m_offset = 0;

        BufferElement(int32_t location, ShaderType type, std::string name);
    };

    /**
     * The layout of a vertex buffer.
     */
    struct BufferLayout {
        /**
         * The number of bytes between vertices in the buffer.
         */
        uint16_t m_stride = 0;
        /**
         * The buffer elements in the layout.
         */
        std::vector<BufferElement> m_elements;
        explicit BufferLayout(std::vector<BufferElement> elements);
        explicit BufferLayout(): BufferLayout(std::vector<BufferElement>()) {};

        void addElement(int32_t location, ShaderType type, std::string name);
    };

    class VertexBufferArray {
    public:
        /**
         * Create a Vertex Buffer Array
         * @return
         */
        static Shared<VertexBufferArray> create();
        virtual ~VertexBufferArray() = default;

        /**
         * Bind the array
         */
        virtual void bind() = 0;
        /**
         * Unbind the array.
         */
        virtual void unbind() = 0;;
    protected:
        VertexBufferArray() = default;
    };

    class VertexBuffer {
    public:
        /**
         * Create a Vertex Buffer
         * @return The vertex buffer
         */
        static Shared<VertexBuffer> create();
        VertexBuffer() = default;

        /**
         * Set the layout of the vertex buffer.
         * @param bufferLayout
         */
        virtual void setLayout(std::vector<BufferElement> bufferLayout) = 0;
        virtual void setLayout(BufferLayout layout) = 0;

        /**
         * Bind the buffer
         */
        virtual void bind() = 0;

        /**
         * Unbind the buffer
         */
        virtual void unbind() = 0;

        /**
         * Set the buffer data
         * @param data The buffer data
         * @param dataLength The length of the buffer data
         */
        virtual void data(void* data, uint32_t dataLength) = 0;
    protected:
        virtual ~VertexBuffer() = default;
    };
    class IndexBuffer {
    public:
        /**
         * Create an index buffer
         * @return The created index buffer.
         */
        static Shared<IndexBuffer> create();
        virtual ~IndexBuffer() = default;

        /**
         * Bind the buffer
         */
        virtual void bind() = 0;
        /**
         * Unbind the buffer
         */
        virtual void unbind() = 0;
        /**
         * Set the buffer data
         * @param data The buffer data
         * @param dataLength The length of the buffer data
         */
        virtual void data(void* data, uint32_t dataLength) = 0;
    protected:
        IndexBuffer() = default;
    };

}
