#include "Renderer.h"

#include <utility>
#include "glm/glm.hpp"
#include "poly/render/geometry/Geometry.h"

namespace Poly {
    RenderTarget* Renderer::m_target = nullptr;

    void Renderer::begin(RenderTarget* pTarget) {
        if(pTarget == nullptr || m_target != nullptr) return;
        m_target = pTarget;
        m_target->flush();
    }

    void Renderer::end() {
        m_target = nullptr;
    }
    
    void Renderer::setClearColour(float r, float g, float b) {
        m_target->submit(makeUnique(SetClearColourRenderCommand(r, g, b)));
    }
    
} // Poly