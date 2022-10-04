//
// Created by avery on 2022-09-22.
//

#include <iostream>
#include "RenderTarget.h"

void Poly::RenderTarget::submit(const Poly::RenderCommand& command) {
    queueMutex.lock();
    commandQueue.push(command);
    queueMutex.unlock();
}

void Poly::RenderTarget::flush() {
    std::cout << "Flushing...." << std::endl;
    queueMutex.lock();
    std::cout << "Flushing...." << std::endl;
    commandQueue = std::queue<RenderCommand>();
    queueMutex.unlock();
}

Poly::RenderCommand Poly::RenderTarget::pop() {
    queueMutex.lock();
    RenderCommand command = commandQueue.front();
    commandQueue.pop();
    queueMutex.unlock();
    return command;
}

bool Poly::RenderTarget::getRenderQueueEmpty() {
    queueMutex.lock();
    bool e = commandQueue.size() < 1;
    queueMutex.unlock();
    return e;
}
