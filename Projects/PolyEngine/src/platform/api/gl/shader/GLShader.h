//
// Created by avery on 2022-09-24.
//

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
        GLuint programID;
        GLuint vertexShaderID;
        GLuint fragmentShaderID;

        std::unordered_map<std::string, int32_t> attributeLocationCache = {};
        std::unordered_map<std::string, int32_t> uniformLocationCache = {};
    };
} // Poly::GL
