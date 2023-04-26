#pragma once

#include <queue>
#include "poly/render/geometry/material/Material.h"
#include "poly/render/geometry/mesh/Mesh.h"
#include "RenderCommand.h"
#include <mutex>

namespace Poly {
    class RenderTarget {
    public:
        RenderTarget() = default;

        void submit(Unique<RenderCommand> command);

        Unique<RenderCommand> pop();
        
        bool getRenderQueueEmpty();

        void flush();

        void executeRenderCommandQueue();
    private:
        std::queue<Unique<RenderCommand>> m_commandQueue;
        std::mutex m_queueMutex;
    };
}
