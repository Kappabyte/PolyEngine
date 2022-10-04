//
// Created by avery on 2022-09-28.
//

#pragma once

#include <cstdint>
#include <stdexcept>

namespace Poly {
    /**
     * Represents the type of data in the shader
     */
    enum class ShaderType {
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        MAT3,
        MAT4,
        INT,
        INT2,
        INT3,
        INT4,
        BOOL
    };
    /**
     * Gets the size of one element of the specified shader type in bytes
     * @param type The shader type
     * @return The size in bytes
     */
    inline uint16_t getShaderTypeSize(ShaderType type) {
        switch (type) {
            case ShaderType::FLOAT: return sizeof(float) * 1;
            case ShaderType::FLOAT2: return sizeof(float) * 2;
            case ShaderType::FLOAT3: return sizeof(float) * 3;
            case ShaderType::FLOAT4: return sizeof(float) * 4;
            case ShaderType::MAT3: return sizeof(float) * 3 * 3;
            case ShaderType::MAT4: return sizeof(float) * 4 * 4;
            case ShaderType::INT: return sizeof(int) * 1;
            case ShaderType::INT2: return sizeof(int) * 2;
            case ShaderType::INT3: return sizeof(int) * 3;
            case ShaderType::INT4: return sizeof(int) * 4;
            case ShaderType::BOOL: return sizeof(bool);
        }

        throw std::runtime_error("Unknown shader data type!");
    }

    /**
     * Get the number of elements in the shader type
     * @param type The shader type
     * @return The number of elements.
     */
    inline uint8_t getShaderTypeCount(ShaderType type) {
        switch (type) {
            case ShaderType::FLOAT: return 1;
            case ShaderType::FLOAT2: return 2;
            case ShaderType::FLOAT3: return 3;
            case ShaderType::FLOAT4: return 4;
            case ShaderType::MAT3: return 3 * 3;
            case ShaderType::MAT4: return 4 * 4;
            case ShaderType::INT: return 1;
            case ShaderType::INT2: return 2;
            case ShaderType::INT3: return 3;
            case ShaderType::INT4: return 4;
            case ShaderType::BOOL: return 1;
        }
        return 0;
    }

} // Poly
