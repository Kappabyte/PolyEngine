//
// Created by avery on 2022-09-28.
//

#pragma once

#include "poly/render/material/Material.h"
#include "poly/render/geometry/Mesh.h"
#include "poly/util/Ref.h"
#include "RenderTarget.h"

namespace Poly {

    class Renderer {
    public:
        static void begin(RenderTarget* pTarget);

        static void command(RenderCommandType type, void* data);
        static void draw(Shared<Mesh> mesh, Shared<Material> material);

        static void end();
    private:
        static RenderTarget* target;
    };

} // Poly
