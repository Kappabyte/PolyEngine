//
// Created by avery on 2022-09-24.
//

#pragma once

#include <string>
#include <unordered_map>

namespace Poly {

    class Shader {
    public:
        /**
         * Create a shader
         * @param vertexPath The path to the vertex shader
         * @param fragmentPath The path to the fragment shader
         * @return The created Shader.
         */
        static Shader* create(const std::string& vertexPath, const std::string& fragmentPath);
        virtual ~Shader() = default;

        /**
         * Bind the shader
         */
        virtual void bind() const = 0;
        /**
         * Unbind the shader
         */
        virtual void unbind() const = 0;

        /**
         * Get the location of the specified attribute
         * @param name The name of the attribute
         * @return The location of the attribute
         */
        virtual int32_t getAttributeLocation(const std::string& name) = 0;
        /**
         * Get the location of the specified uniform
         * @param name The name of the uniform
         * @return The location of the uniform
         */
        virtual int32_t getUniformLocation(const std::string& name) = 0;
    protected:
        std::unordered_map<std::string, void*> uniformLocationCache = {};
    };

} // Poly
