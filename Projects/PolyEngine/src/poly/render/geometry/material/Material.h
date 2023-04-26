#pragma once

#include <utility>

#include "poly/render/shader/Shader.h"
#include "poly/util/Ref.h"

namespace Poly {
    class Material {
    public:
        explicit Material(Shared<Shader> shader): m_shader(std::move(shader)) {};

        [[nodiscard]] Shared<Shader> getShader() const { return m_shader; }
    private:
        Shared<Shader> m_shader;
    };
}
