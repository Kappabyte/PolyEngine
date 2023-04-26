#include "RenderTarget.h"

namespace Poly {
    void RenderTarget::submit(Unique<RenderCommand> command) {
        auto lock = std::unique_lock(m_queueMutex);
        m_commandQueue.push(std::move(command));
    }
    
    void RenderTarget::flush() {
        auto lock = std::unique_lock(m_queueMutex);
        m_commandQueue = std::queue<Unique<RenderCommand>>();
    }
    
    Unique<RenderCommand> RenderTarget::pop() {
        auto lock = std::unique_lock(m_queueMutex);
        Unique<RenderCommand> command = std::move(m_commandQueue.front());
        m_commandQueue.pop();
        return command;
    }
    
    bool Poly::RenderTarget::getRenderQueueEmpty() {
        auto lock = std::unique_lock(m_queueMutex);
        bool e = m_commandQueue.empty();
        return e;
    }
    
    void Poly::RenderTarget::executeRenderCommandQueue() {
        auto lock = std::unique_lock(m_queueMutex);
        while(!getRenderQueueEmpty()) {
            pop()->execute();
        }
    }
}
