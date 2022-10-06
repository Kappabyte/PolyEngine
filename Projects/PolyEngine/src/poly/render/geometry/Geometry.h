//
// Created by avery on 2022-10-05.
//

#pragma once

#include "poly/render/geometry/mesh/Mesh.h"
#include "poly/render/geometry/material/Material.h"
#include "poly/render/Buffer.h"

namespace Poly {

    struct GeometryData {
        Shared<Mesh> mesh;
        Shared<Material> material;
    };

    class Geometry {
    public:
        explicit Geometry(GeometryData data);

        [[nodiscard]] GeometryData getGeometry() const {return data;};

        [[nodiscard]] Shared<VertexBufferArray> getVertexArray() const;

        void updateGeometry(GeometryData data);
    private:
        void updateBuffers();
    private:
        GeometryData data;

        Shared<VertexBufferArray> vertexArray;
        Shared<VertexBuffer> vertexBuffer;
        Shared<IndexBuffer> indexBuffer;
    };

} // Poly
