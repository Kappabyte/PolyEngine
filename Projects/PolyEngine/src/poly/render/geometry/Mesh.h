//
// Created by avery on 2022-09-22.
//

#pragma once

#include <vector>
#include <cstdint>
#include "SubMesh.h"

namespace Poly {
    class Mesh {
    public:
    private:
        std::vector<SubMesh> subMeshes;
    };
}