#include "Mesh.h"
#include "poly/render/shader/ShaderType.h"

void Poly::Mesh::addVertexAttribute(const std::string &name, ShaderType type, float data[], size_t size) {
    m_vertexAttributes.insert({name, VertexAttribute(type, data, size)});
    // Construct the compiled vertex data
    m_compiledVertexData.erase(m_compiledVertexData.begin(), m_compiledVertexData.end());

    size_t start = 0;
    while(true) {
        for(auto& [name, attribute]: m_vertexAttributes) {
            size_t count = getShaderTypeCount(attribute.m_type);
            if(start * count + count > attribute.m_size / sizeof(float)) {
                goto end;
            }
            for(size_t i = start * count; i < start * count + count; i++) {
                m_compiledVertexData.push_back(attribute.m_data[i]);
            }
        }
        start++;
    }
    end:
    nullptr;
}

Poly::Mesh::VertexAttribute::VertexAttribute(Poly::ShaderType type, float* data, size_t size): m_type(type), m_data(data), m_size(size) {}
