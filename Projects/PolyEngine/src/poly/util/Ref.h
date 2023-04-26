#pragma once
#include <memory>

namespace Poly {
    template<typename T>
    using Unique = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Unique<T> makeUnique(Args&& ... args)
    {
        return std::make_unique<T>(args...);
    }

    template<typename T>
    using Shared = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Shared<T> makeShared(Args&& ... args)
    {
        return std::make_shared<T>(args...);
    }
}
