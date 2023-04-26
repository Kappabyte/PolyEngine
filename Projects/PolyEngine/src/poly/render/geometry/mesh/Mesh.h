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
            ShaderType m_type;
            size_t m_size;
            float* m_data;

            VertexAttribute(ShaderType type, float* data, size_t size);
        };

        Mesh() = default;
        void addVertexAttribute(const std::string& name, ShaderType type, float data[], size_t size);

        [[nodiscard]] const std::unordered_map<std::string, VertexAttribute>& getVertexAttributes() const { return m_vertexAttributes; }
        [[nodiscard]] const std::vector<float>& getCompiledVertexData() const { return m_compiledVertexData; }
    private:
        std::unordered_map<std::string, VertexAttribute> m_vertexAttributes;
        std::vector<float> m_compiledVertexData;
    };
}