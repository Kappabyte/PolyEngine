#pragma once

#include <poly/util/Ref.h>

namespace Poly {

    class RenderCommand {
    public:
        virtual ~RenderCommand() = default;
        
        virtual void setClearColour() = 0;
        
        friend class RenderTarget;
    private:
        virtual void execute() = 0;
    };
    
} // Poly
