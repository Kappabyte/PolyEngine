//
// Created by avery on 2022-09-28.
//

#include "Buffer.h"
#include "poly/core/Application.h"
#include "poly/util/Ref.h"
#include <platform/api/gl/GLBuffer.h>

#include <utility>

namespace Poly {
    Shared<VertexBufferArray> VertexBufferArray::create() {
        switch(Application::get()->getAPI()) {
            case API::GL: return MakeShared<GL::GLVertexBufferArray>();
            default: throw std::runtime_error("Unsupported API");
        }

        throw std::runtime_error("Unknown API");
    }

    Shared<VertexBuffer> VertexBuffer::create() {
        switch(Application::get()->getAPI()) {
            case API::GL: return MakeShared<GL::GLVertexBuffer>();
            default: throw std::runtime_error("Unsupported API");
        }

        throw std::runtime_error("Unknown API");
    }

    BufferLayout::BufferLayout(std::vector<BufferElement> elements): elements(std::move(elements)) {
        for(auto& element : this->elements) {
            element.offset = stride;
            stride += getShaderTypeSize(element.type);
        }
    }

    void BufferLayout::addElement(int32_t location, ShaderType type, std::string name) {
        elements.emplace_back(location, type, std::move(name));
        stride = 0;
        for(auto& element : this->elements) {
            element.offset = stride;
            stride += getShaderTypeSize(element.type);
        }
    }

    BufferElement::BufferElement(int32_t location, ShaderType type, std::string name): location(location), type(type), name(std::move(name)) {}

    Shared<IndexBuffer> IndexBuffer::create() {
        switch(Application::get()->getAPI()) {
            case API::GL: return MakeShared<GL::GLIndexBuffer>();
            default: throw std::runtime_error("Unsupported API");
        }

        throw std::runtime_error("Unknown API");
    }
}

