#include "GLBuffer.h"

namespace Poly::GL {
    GLVertexBufferArray::GLVertexBufferArray() {
        glGenVertexArrays(1, &m_arrayId);
    }

    GLVertexBufferArray::~GLVertexBufferArray() {
        glDeleteVertexArrays(1, &m_arrayId);
    }

    void GLVertexBufferArray::bind() {
        glBindVertexArray(m_arrayId);
    }

    void GLVertexBufferArray::unbind() {
        glBindVertexArray(0);
    }

    GLVertexBuffer::GLVertexBuffer() {
        glGenBuffers(1, &m_bufferId);
    }

    GLVertexBuffer::~GLVertexBuffer() {
        glDeleteBuffers(1, &m_bufferId);
    }

    void GLVertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    }

    void GLVertexBuffer::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLVertexBuffer::data(void *data, uint32_t length) {
        bind();
        glBufferData(GL_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);
    }

    GLint shaderTypeToGLType(ShaderType type) {
        switch(type){
            case ShaderType::FLOAT:
            case ShaderType::FLOAT_2:
            case ShaderType::FLOAT_3:
            case ShaderType::FLOAT_4:
            case ShaderType::MAT_3:
            case ShaderType::MAT_4:
                return GL_FLOAT;
            case ShaderType::INT:
            case ShaderType::INT_2:
            case ShaderType::INT_3:
            case ShaderType::INT_4:
                return GL_INT;
            case ShaderType::BOOL:
                return GL_BOOL;
        }
    }

    void GLVertexBuffer::setLayout(std::vector<BufferElement> elements) {
        bind();
        BufferLayout layout(elements);
        for(auto& element : layout.m_elements) {
            glEnableVertexAttribArray(element.m_location);
            glVertexAttribPointer(element.m_location, getShaderTypeCount(element.m_type),
                                  shaderTypeToGLType(element.m_type), GL_FALSE, layout.m_stride, (void*)element.m_offset);
        }
    }

    void GLVertexBuffer::setLayout(BufferLayout layout) {
        for(auto& element : layout.m_elements) {
            glEnableVertexAttribArray(element.m_location);
            glVertexAttribPointer(element.m_location, getShaderTypeCount(element.m_type),
                                  shaderTypeToGLType(element.m_type), GL_FALSE, layout.m_stride, (void*)element.m_offset);
        }
    }

    GLIndexBuffer::GLIndexBuffer() {
        glGenBuffers(1, &m_bufferId);
    }

    GLIndexBuffer::~GLIndexBuffer() {
        glDeleteBuffers(1, &m_bufferId);
    }

    void GLIndexBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
    }

    void GLIndexBuffer::unbind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void GLIndexBuffer::data(void *data, uint32_t length) {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);
    }
} // GL