#include "Shader.h"
#include "poly/render/RenderBackend.h"
#include "platform/api/gl/shader/GLShader.h"
#include "poly/core/Application.h"

namespace Poly {
    Shared<Shader> Shader::create(const std::string &vertexPath, const std::string &fragmentPath) {
        switch (Application::get()->getApi()) {
            case RenderAPI::GL:
                return Shared<Shader>(new GL::GLShader(vertexPath, fragmentPath));
            default:
                throw std::runtime_error("Unsupported API");
        }
    }
} // Poly