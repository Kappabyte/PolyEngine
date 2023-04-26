//
// Created by avery on 2023-03-07.
//

#include "RenderBackend.h"
#include "platform/api/gl/GLRenderBackend.h"
#include "poly/util/Ref.h"
#include "poly/util/Log.h"

namespace Poly {
    void RenderBackend::create(RenderAPI api) {
        m_api = api;
        switch(api) {
            case RenderAPI::GL:
                m_backend = makeShared<GL::GLRenderBackend>();
            default:
                LOG_CRITICAL("Unsupported graphics backend specified.");
        }
    }
    
    Shared<RenderBackend> RenderBackend::getBackend() {
        return m_backend;
    }
    
    [[maybe_unused]] RenderAPI RenderBackend::getAPI() {
        return m_api;
    }
}


