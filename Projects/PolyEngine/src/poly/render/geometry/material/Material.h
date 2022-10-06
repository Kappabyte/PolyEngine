//
// Created by avery on 2022-09-22.
//

#pragma once

#include <utility>

#include "poly/render/shader/Shader.h"
#include "poly/util/Ref.h"

namespace Poly {
    class Material {
    public:
        explicit Material(Shared<Shader> shader): shader(std::move(shader)) {};

        [[nodiscard]] Shared<Shader> getShader() const { return shader; }
    private:
        Shared<Shader> shader;
    };
}
