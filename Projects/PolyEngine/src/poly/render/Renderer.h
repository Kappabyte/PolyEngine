#pragma once

#include "poly/render/geometry/material/Material.h"
#include "poly/render/geometry/mesh/Mesh.h"
#include "poly/util/Ref.h"
#include "RenderTarget.h"

namespace Poly {

    class Renderer {
    public:
        static void begin(RenderTarget* pTarget);

        static void setClearColour(float r, float g, float b);

        static void end();
    private:
        static RenderTarget* m_target;
    };

} // Poly
