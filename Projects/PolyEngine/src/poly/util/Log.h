#pragma once
#include <spdlog/spdlog.h>

namespace Poly::Log {
    #define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
    #define LOG_INFO(...) spdlog::info(__VA_ARGS__)
    #define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
    #define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
    #define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)
    #define ASSERT(x, ...) { if(!x) {LOG_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();}}
}