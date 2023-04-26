#pragma once

#include <string>
#include <unordered_map>
#include "poly/util/Ref.h"

namespace Poly {

    class Shader {
    public:
        /**
         * Create a shader
         * @param vertexPath The path to the vertex shader
         * @param fragmentPath The path to the fragment shader
         * @return The created Shader.
         */
        static Shared<Shader> create(const std::string& vertexPath, const std::string& fragmentPath);
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
         * @return The location of the attribute, or -1 if it doesn't exist.
         */
        virtual int32_t getAttributeLocation(const std::string& name) = 0;
        /**
         * Get the location of the specified uniform
         * @param name The name of the uniform
         * @return The location of the uniform, or -1 if it doesn't exist.
         */
        virtual int32_t getUniformLocation(const std::string& name) = 0;
    protected:
        std::unordered_map<std::string, void*> m_uniformLocationCache = {};
    };

} // Poly
