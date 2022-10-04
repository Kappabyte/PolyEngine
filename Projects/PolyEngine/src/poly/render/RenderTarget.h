//
// Created by avery on 2022-09-22.
//

#pragma once

#include <queue>
#include "poly/render/material/Material.h"
#include "poly/render/geometry/Mesh.h"
#include "RenderCommand.h"

namespace Poly {
    class RenderTarget {
    public:
        RenderTarget() = default;

        void submit(const RenderCommand& command);

        RenderCommand pop();
        bool getRenderQueueEmpty();

        void flush();

        std::queue<RenderCommand> getCommandQueue() const {
            return commandQueue;
        }
    private:
        std::queue<RenderCommand> commandQueue;
        std::mutex queueMutex;
    };
}
