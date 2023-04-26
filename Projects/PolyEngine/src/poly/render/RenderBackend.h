#pragma once

#include <poly/util/Ref.h>

namespace Poly {

    /**
     * The graphics API
     */
    enum class RenderAPI {
        NONE = 0,
        GL
    };
    
    class RenderBackend {
    public:
        static void create(RenderAPI api);
    
        static std::shared_ptr<RenderBackend> getBackend();
    
        static RenderAPI getAPI();
        
    private:
        static RenderAPI m_api;
        static Shared<RenderBackend> m_backend;
    };

} // Poly
