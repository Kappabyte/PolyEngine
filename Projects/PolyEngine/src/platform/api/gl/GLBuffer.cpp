//
// Created by avery on 2022-09-28.
//

#include "GLBuffer.h"

namespace Poly::GL {
    GLVertexBufferArray::GLVertexBufferArray() {
        glGenVertexArrays(1, &arrayID);
    }

    GLVertexBufferArray::~GLVertexBufferArray() {
        glDeleteVertexArrays(1, &arrayID);
    }

    void GLVertexBufferArray::bind() {
        glBindVertexArray(arrayID);
    }

    void GLVertexBufferArray::unbind() {
        glBindVertexArray(0);
    }

    GLVertexBuffer::GLVertexBuffer() {
        glGenBuffers(1, &bufferID);
    }

    GLVertexBuffer::~GLVertexBuffer() {
        glDeleteBuffers(1, &bufferID);
    }

    void GLVertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    }

    void GLVertexBuffer::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLVertexBuffer::data(void *data, uint32_t length) {
        bind();
        glBufferData(GL_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);
    }

    GLint ShaderTypeToGLType(ShaderType type) {
        switch(type){
            case ShaderType::FLOAT:
            case ShaderType::FLOAT2:
            case ShaderType::FLOAT3:
            case ShaderType::FLOAT4:
            case ShaderType::MAT3:
            case ShaderType::MAT4:
                return GL_FLOAT;
            case ShaderType::INT:
            case ShaderType::INT2:
            case ShaderType::INT3:
            case ShaderType::INT4:
                return GL_INT;
            case ShaderType::BOOL:
                return GL_BOOL;
        }
    }

    void GLVertexBuffer::setLayout(std::vector<BufferElement> elements) {
        bind();
        BufferLayout layout(elements);
        for(auto& element : layout.elements) {
            glEnableVertexAttribArray(element.location);
            glVertexAttribPointer(element.location, getShaderTypeCount(element.type), ShaderTypeToGLType(element.type), GL_FALSE, layout.stride, (void*)element.offset);
        }
    }

    GLIndexBuffer::GLIndexBuffer() {
        glGenBuffers(1, &bufferID);
    }

    GLIndexBuffer::~GLIndexBuffer() {
        glDeleteBuffers(1, &bufferID);
    }

    void GLIndexBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    }

    void GLIndexBuffer::unbind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void GLIndexBuffer::data(void *data, uint32_t length) {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);
    }
} // GL