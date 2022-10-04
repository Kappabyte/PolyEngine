//
// Created by avery on 2022-09-22.
//

#pragma once

#include <vector>
#include <cstdint>

namespace Poly {
    class SubMesh {
    private:
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> uvs;

        std::vector<uint32_t> indices;
    };
}
