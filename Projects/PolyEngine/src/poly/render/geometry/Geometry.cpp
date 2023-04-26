#include "Geometry.h"

#include <utility>

#include <utility>

namespace Poly {
    Geometry::Geometry(GeometryData data): m_data(std::move(data)) {
        this->m_vertexArray = VertexBufferArray::create();
        this->m_vertexArray->bind();

        this->m_vertexBuffer = VertexBuffer::create();

        updateBuffers();
    }

    void Geometry::updateBuffers() {
        this->m_vertexArray->bind();
        this->m_vertexBuffer->bind();
        auto vertexData = m_data.m_mesh->getCompiledVertexData();
        this->m_vertexBuffer->data(vertexData.data(), vertexData.size() * sizeof(float));
        Shared<Shader> shader = m_data.m_material->getShader();
        BufferLayout layout;
        for(auto& [name, attribute]: m_data.m_mesh->getVertexAttributes()) {
            auto location = shader->getAttributeLocation(name);
            if(location < 0) continue;
            layout.addElement(location, attribute.m_type, name);
        }
        this->m_vertexBuffer->setLayout(layout);
    }

    Shared<VertexBufferArray> Geometry::getVertexArray() const {
        return m_vertexArray;
    }

    void Geometry::updateGeometry(GeometryData data) {
        this->m_data = std::move(data);
        updateBuffers();
    }
} // Poly