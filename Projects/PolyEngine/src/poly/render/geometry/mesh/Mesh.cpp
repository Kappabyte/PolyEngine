//
// Created by avery on 2022-09-22.
//

#include "Mesh.h"
#include "poly/render/shader/ShaderType.h"

void Poly::Mesh::addVertexAttribute(const std::string &name, ShaderType type, float data[], size_t size) {
    vertexAttributes.insert({name, VertexAttribute(type, data, size)});
    // Construct the compiled vertex data
    compiledVertexData.erase(compiledVertexData.begin(), compiledVertexData.end());

    size_t start = 0;
    while(true) {
        for(auto& [name, attribute]: vertexAttributes) {
            size_t count = getShaderTypeCount(attribute.type);
            if(start * count + count > attribute.size / sizeof(float)) {
                goto end;
            }
            for(size_t i = start * count; i < start * count + count; i++) {
                compiledVertexData.push_back(attribute.data[i]);
            }
        }
        start++;
    }
    end:
    nullptr;
}

Poly::Mesh::VertexAttribute::VertexAttribute(Poly::ShaderType type, float* data, size_t size): type(type), data(data), size(size) {}
