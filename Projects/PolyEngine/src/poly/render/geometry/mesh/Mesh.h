//
// Created by avery on 2022-09-22.
//

#pragma once

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <string>
#include "poly/render/shader/ShaderType.h"

namespace Poly {
    class Mesh {
    public:
        struct VertexAttribute {
            ShaderType type;
            size_t size;
            float* data;

            VertexAttribute(ShaderType type, float* data, size_t size);
        };

        Mesh() = default;
        void addVertexAttribute(const std::string& name, ShaderType type, float data[], size_t size);

        [[nodiscard]] const std::unordered_map<std::string, VertexAttribute>& getVertexAttributes() const { return vertexAttributes; }
        [[nodiscard]] const std::vector<float>& getCompiledVertexData() const { return compiledVertexData; }
    private:
        std::unordered_map<std::string, VertexAttribute> vertexAttributes;
        std::vector<float> compiledVertexData;
    };
}