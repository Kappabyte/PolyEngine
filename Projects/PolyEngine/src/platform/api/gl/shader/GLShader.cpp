//
// Created by avery on 2022-09-24.
//

#include "GLShader.h"
#include <regex>
#include <iostream>

namespace Poly {
    namespace GL {
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

            programID = glCreateProgram();

            vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            const auto *source = (const GLchar *)vertexSource.c_str();
            glShaderSource(vertexShaderID, 1, &source, 0);
            glCompileShader(vertexShaderID);

            GLint isCompiled = 0;
            glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);
                std::cout << maxLength << std::endl;
                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength + 1);
                glGetShaderInfoLog(vertexShaderID, maxLength, &maxLength, &errorLog[0]);
                errorLog[errorLog.size()-1] = '\0';
                std::cout << maxLength << std::endl;

                // Provide the infolog in whatever manor you deem best.
                std::cout << "**Failed to compile vertex shader " << vertexPath << "!**" << std::endl;
                std::cout << "Driver provided error details can be found below:\n--BEGIN ERROR LOG--" << std::endl;
                std::cout << errorLog.data() << std::endl;
                std::cout << "--END ERROR LOG--" << std::endl;
                std::cout << "--BEGIN SHADER SOURCE--" << std::endl;
                std::cout << vertexSource << std::endl;
                std::cout << "--END SHADER SOURCE--" << std::endl;
                // Exit with failure.
                glDeleteShader(vertexShaderID); // Don't leak the shader.
                return;
            }

            fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
            source = (const GLchar *)fragmentSource.c_str();
            glShaderSource(fragmentShaderID, 1, &source, 0);
            glCompileShader(fragmentShaderID);

            isCompiled = 0;
            glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength + 1);
                glGetShaderInfoLog(fragmentShaderID, maxLength, &maxLength, &errorLog[0]);
                errorLog[errorLog.size()-1] = '\0';
                std::cout << maxLength << std::endl;

                // Provide the infolog in whatever manor you deem best.
                std::cout << "**Failed to compile fragment shader " << fragmentPath << "!**" << std::endl;
                std::cout << "Driver provided error details can be found below:\n--BEGIN ERROR LOG--" << std::endl;
                std::cout << errorLog.data() << std::endl;
                std::cout << "--END ERROR LOG--" << std::endl;
                std::cout << "--BEGIN SHADER SOURCE--" << std::endl;
                std::cout << fragmentSource << std::endl;
                std::cout << "--END SHADER SOURCE--" << std::endl;
                // Exit with failure.
                glDeleteShader(fragmentShaderID); // Don't leak the shader.
                return;
            }

            glAttachShader(programID, vertexShaderID);
            glAttachShader(programID, fragmentShaderID);

            glLinkProgram(programID);

            GLint isLinked = 0;
            glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
            if (isLinked == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

                // The program is useless now. So delete it.
                glDeleteProgram(programID);

                // Provide the infolog in whatever manner you deem best.
                std::cout << "Failed to link shader program!" << std::endl;
                // Exit with failure.
                return;
            }

            glValidateProgram(programID);
        }

        void GLShader::bind() const {
            glUseProgram(programID);
        }

        void GLShader::unbind() const {
            glUseProgram(0);
        }

        GLShader::~GLShader() {
            glDeleteProgram(programID);
        }

        int32_t GLShader::getAttributeLocation(const std::string &name) {
            bind();
            if(attributeLocationCache.find(name) != attributeLocationCache.end()) {
                return attributeLocationCache.at(name);
            }
            attributeLocationCache.insert({name, glGetAttribLocation(programID, name.c_str())});
            return attributeLocationCache[name];
        }

        int32_t GLShader::getUniformLocation(const std::string &name) {
            if(uniformLocationCache.find(name) != uniformLocationCache.end()) {
                return uniformLocationCache.at(name);
            }
            uniformLocationCache.insert({name, glGetUniformLocation(programID, name.c_str())});
            return uniformLocationCache[name];
        }
    } // Poly
} // GL