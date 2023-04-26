#pragma once

#include "poly/render/geometry/mesh/Mesh.h"
#include "poly/render/geometry/material/Material.h"
#include "poly/render/Buffer.h"

namespace Poly {

    struct GeometryData {
        Shared<Mesh> m_mesh;
        Shared<Material> m_material;
    };

    class Geometry {
    public:
        explicit Geometry(GeometryData data);

        [[nodiscard]] GeometryData getGeometry() const {return m_data;};

        [[nodiscard]] Shared<VertexBufferArray> getVertexArray() const;

        void updateGeometry(GeometryData data);
    private:
        void updateBuffers();
    private:
        GeometryData m_data;

        Shared<VertexBufferArray> m_vertexArray;
        Shared<VertexBuffer> m_vertexBuffer;
        Shared<IndexBuffer> m_indexBuffer;
    };

} // Poly
