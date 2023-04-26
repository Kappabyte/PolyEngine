#include "Buffer.h"
#include "poly/core/Application.h"
#include "poly/util/Ref.h"
#include <platform/api/gl/GLBuffer.h>

#include <utility>

namespace Poly {
    Shared<VertexBufferArray> VertexBufferArray::create() {
        switch(Application::get()->getApi()) {
            case RenderAPI::GL: return makeShared<GL::GLVertexBufferArray>();
            default: throw std::runtime_error("Unsupported API");
        }

        throw std::runtime_error("Unknown API");
    }

    Shared<VertexBuffer> VertexBuffer::create() {
        switch(Application::get()->getApi()) {
            case RenderAPI::GL: return makeShared<GL::GLVertexBuffer>();
            default: throw std::runtime_error("Unsupported API");
        }

        throw std::runtime_error("Unknown API");
    }

    BufferLayout::BufferLayout(std::vector<BufferElement> elements): m_elements(std::move(elements)) {
        for(auto& element : this->m_elements) {
            element.m_offset = m_stride;
            m_stride += getShaderTypeSize(element.m_type);
        }
    }

    void BufferLayout::addElement(int32_t location, ShaderType type, std::string name) {
        m_elements.emplace_back(location, type, std::move(name));
        m_stride = 0;
        for(auto& element : this->m_elements) {
            element.m_offset = m_stride;
            m_stride += getShaderTypeSize(element.m_type);
        }
    }

    BufferElement::BufferElement(int32_t location, ShaderType type, std::string name): m_location(location), m_type(type), m_name(std::move(name)) {}

    Shared<IndexBuffer> IndexBuffer::create() {
        switch(Application::get()->getApi()) {
            case RenderAPI::GL: return makeShared<GL::GLIndexBuffer>();
            default: throw std::runtime_error("Unsupported API");
        }

        throw std::runtime_error("Unknown API");
    }
}

