//
// Created by avery on 2022-10-05.
//

#include "Geometry.h"

namespace Poly {
    Geometry::Geometry(GeometryData data): data(data) {
        this->vertexArray = VertexBufferArray::create();
        this->vertexArray->bind();

        this->vertexBuffer = VertexBuffer::create();

        updateBuffers();
    }

    void Geometry::updateBuffers() {
        this->vertexArray->bind();
        this->vertexBuffer->bind();
        auto vertexData = data.mesh->getCompiledVertexData();
        this->vertexBuffer->data(vertexData.data(), vertexData.size() * sizeof(float));
        Shared<Shader> shader = data.material->getShader();
        BufferLayout layout;
        for(auto& [name, attribute]: data.mesh->getVertexAttributes()) {
            auto location = shader->getAttributeLocation(name);
            if(location < 0) continue;
            layout.addElement(location, attribute.type, name);
        }
        this->vertexBuffer->setLayout(layout);
    }

    Shared<VertexBufferArray> Geometry::getVertexArray() const {
        return vertexArray;
    }

    void Geometry::updateGeometry(GeometryData data) {
        this->data = data;
        updateBuffers();
    }
} // Poly