#include "GLShader.h"
#include <regex>
#include <iostream>

namespace Poly::GL {
    GLShader::GLShader(const std::string &vertexPath, const std::string &fragmentPath) {
        std::string vertexSource = R"(#version 330 core
            layout(location=0)in vec3 a_Pos;
            layout(location=1)in vec3 a_Color;

            out vec3 ourColor;

            void main()
            {
                gl_Position = vec4(a_Pos, 1.0);
                ourColor = a_Color;
            }
        )";
        std::string fragmentSource = R"(#version 330 core
            out vec4 FragColor;

            in vec3 ourColor;

            void main()
            {
                FragColor = vec4(ourColor, 1.0f);
            }
        )";

        m_programId = glCreateProgram();

        m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        const auto *source = (const GLchar *)vertexSource.c_str();
        glShaderSource(m_vertexShaderId, 1, &source, nullptr);
        glCompileShader(m_vertexShaderId);

        GLint isCompiled = 0;
        glGetShaderiv(m_vertexShaderId, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(m_vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
            std::cout << maxLength << std::endl;
            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength + 1);
            glGetShaderInfoLog(m_vertexShaderId, maxLength, &maxLength, &errorLog[0]);
            errorLog[errorLog.size()-1] = '\0';
            std::cout << maxLength << std::endl;

            // Provide the info log in whatever manor you deem best.
            std::cout << "**Failed to compile vertex shader " << vertexPath << "!**" << std::endl;
            std::cout << "Driver provided error details can be found below:\n--BEGIN ERROR LOG--" << std::endl;
            std::cout << errorLog.data() << std::endl;
            std::cout << "--END ERROR LOG--" << std::endl;
            std::cout << "--BEGIN SHADER SOURCE--" << std::endl;
            std::cout << vertexSource << std::endl;
            std::cout << "--END SHADER SOURCE--" << std::endl;
            // Exit with failure.
            glDeleteShader(m_vertexShaderId); // Don't leak the shader.
            return;
        }

        m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        source = (const GLchar *)fragmentSource.c_str();
        glShaderSource(m_fragmentShaderId, 1, &source, nullptr);
        glCompileShader(m_fragmentShaderId);

        isCompiled = 0;
        glGetShaderiv(m_fragmentShaderId, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(m_fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength + 1);
            glGetShaderInfoLog(m_fragmentShaderId, maxLength, &maxLength, &errorLog[0]);
            errorLog[errorLog.size()-1] = '\0';
            std::cout << maxLength << std::endl;

            // Provide the info log in whatever manor you deem best.
            std::cout << "**Failed to compile fragment shader " << fragmentPath << "!**" << std::endl;
            std::cout << "Driver provided error details can be found below:\n--BEGIN ERROR LOG--" << std::endl;
            std::cout << errorLog.data() << std::endl;
            std::cout << "--END ERROR LOG--" << std::endl;
            std::cout << "--BEGIN SHADER SOURCE--" << std::endl;
            std::cout << fragmentSource << std::endl;
            std::cout << "--END SHADER SOURCE--" << std::endl;
            // Exit with failure.
            glDeleteShader(m_fragmentShaderId); // Don't leak the shader.
            return;
        }

        glAttachShader(m_programId, m_vertexShaderId);
        glAttachShader(m_programId, m_fragmentShaderId);

        glLinkProgram(m_programId);

        GLint isLinked = 0;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_programId, maxLength, &maxLength, &infoLog[0]);

            // The program is useless now. So delete it.
            glDeleteProgram(m_programId);

            // Provide the info log in whatever manner you deem best.
            std::cout << "Failed to link shader program!" << std::endl;
            // Exit with failure.
            return;
        }

        glValidateProgram(m_programId);
    }

    void GLShader::bind() const {
        glUseProgram(m_programId);
    }

    void GLShader::unbind() const {
        glUseProgram(0);
    }

    GLShader::~GLShader() {
        glDeleteProgram(m_programId);
    }

    int32_t GLShader::getAttributeLocation(const std::string &name) {
        bind();
        if(m_attributeLocationCache.find(name) != m_attributeLocationCache.end()) {
            return m_attributeLocationCache.at(name);
        }
        m_attributeLocationCache.insert({name, glGetAttribLocation(m_programId, name.c_str())});
        return m_attributeLocationCache[name];
    }

    int32_t GLShader::getUniformLocation(const std::string &name) {
        if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
            return m_uniformLocationCache.at(name);
        }
        m_uniformLocationCache.insert({name, glGetUniformLocation(m_programId, name.c_str())});
        return m_uniformLocationCache[name];
    }
} // GL