//
// Created by avery on 2022-09-28.
//

#include "Renderer.h"
#include "glm/glm.hpp"

namespace Poly {
    RenderTarget* Renderer::target = nullptr;

    void Renderer::begin(RenderTarget* pTarget) {
        if(pTarget == nullptr || target != nullptr) return;
        target = pTarget;
        target->flush();
    }

    void Renderer::draw(Shared<Mesh> mesh, Shared<Material> material) {
        if(target == nullptr) return;
        target->submit(RenderCommand(RenderCommandType::SET_CLEAR_COLOUR, new glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
        target->submit(RenderCommand(RenderCommandType::CLEAR, nullptr));
    }

    void Renderer::command(RenderCommandType type, void *data) {
        if(target == nullptr) return;
        target->submit(RenderCommand(type, data));
    }

    void Renderer::end() {
        if(target == nullptr) return;
    }

} // Poly