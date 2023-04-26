#pragma once

#include "poly/render/shader/Shader.h"
#include <glad/glad.h>

namespace Poly::GL {
    class GLShader : public Poly::Shader {
    public:
        GLShader(const std::string &vertexPath, const std::string &fragmentPath);
        ~GLShader() override;

        void bind() const override;
        void unbind() const override;

        int32_t getAttributeLocation(const std::string& name) override;
        int32_t getUniformLocation(const std::string& name) override;
    private:
        GLuint m_programId;
        GLuint m_vertexShaderId;
        GLuint m_fragmentShaderId;

        std::unordered_map<std::string, int32_t> m_attributeLocationCache = {};
        std::unordered_map<std::string, int32_t> m_uniformLocationCache = {};
    };
} // Poly::GL
